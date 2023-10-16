--- src/EditresCom.c.orig	2019-03-16 11:42:32.000000000 -0700
+++ src/EditresCom.c	2023-10-15 22:30:42.077670000 -0700
@@ -48,6 +48,11 @@
 #include <stdlib.h>
 #include <string.h>
 
+//#define DEBUG 0 // remove this line before any upstream merge
+#if defined(DEBUG)
+#include <assert.h>
+#endif
+
 #define _XEditResPutBool _XEditResPut8
 #define _XEditResPutResourceType _XEditResPut8
 
@@ -115,11 +120,90 @@
     FindChildEvent find_child_event;
 } EditresEvent;
 
+/*
+ * Two-way mapping between Widgets's addresses and 32-bit WidgetIDs.
+ */
+typedef unsigned int WidgetID;
+
+typedef enum {
+    /* This value is only used internally as the distinguished value
+     * for widgets that haven't got IDs at some moment. It is
+     * issued to a Resource Editor only if there's been some
+     * unrecoverable error. Whenever a Resource Editor sends this
+     * value in a request, the request must error. */
+    WidgetIDNull,
+    /* Reserve some WidgetIDs as invalid, to be handed out in case the
+       client has used up the valid WidgetID space over time. The
+       right number to reserve is the maximum number of widgets that
+       might need to be sent to a resource editor in response to a
+       single SendWidgetTree request, i.e., the maximum number that
+       might exist at a single time (as distinct from the total number
+       ever created); four million is almost certainly sufficient. */
+    WidgetIDFirstInvalid,
+    /* Everything from here up to WidgetIDExhausted is valid. */
+    WidgetIDFirstValid = 0x400000,
+    /* How to exercise the WidgetIDExhaustion recovery mechanism: set
+       this to some low-ish number greater than WidgetIDFirstValid,
+       find or write a client that creates and destroys lots of
+       widgets, and repeatedly retrieve its widget tree between
+       creation/destruction. Eventually you should start seeing IDs in
+       the invalid range. Try any request on those widgets (e.g.,
+       GetGeometry), then refresh the widget tree. */
+    // WidgetIDExhausted = 150 + 0x400000;
+    WidgetIDExhausted  = 0xFFFFFFFF
+} WidgetIDMagics;
+
+typedef struct _WidgetIDCell {
+    Widget widget;
+    WidgetID id;
+} WidgetIDCell;
+
+/* List of shells that have handled EditRes events, needed for
+ * the (improbable) case of running out of WidgetIDs. */
+typedef struct _ShellNode {
+    struct _ShellNode *next;
+    Widget shell;
+} ShellNode;
+
+/* All the bookkeeping needed for Widget<->WidgetID
+   correspondence. There's only one of these per process, instantiated
+   as a side effect of the _XEditResPutWidgetInfoUnresolve or
+   _XEditResPutWidgetUnresolve call. */
+typedef struct _WidgetIDTable {
+    /* A 32-bit serial number, incremented for each new Widget put
+       onto the ProtocolStream. */
+    WidgetID next_id;
+    /* A different serial number, incremented when next_id is
+       WidgetIDExhausted. */
+    WidgetID next_invalid;
+    /* A position in an array of primes used to initialize the size
+       of the hash arrays, widget_hash and id_hash. */
+    int size_factor;
+    /* The number of WidgetIDCells in each of widget_hash and id_hash. */
+    int size;
+    /* The number of WidgetIDCells in use in each of widget_hash and
+       id_hash, for triggering rehashing. */
+    int used;
+    /* When used/size is greater than this percentage, interning a
+       Widget triggers a rehash that increases size. */
+    float overflow_rehash;
+    /* Array of WidgetIDCells ordered for lookups keyed by Widget. */
+    WidgetIDCell *widget_hash;
+    /* Array of WidgetIDCells ordered for lookups keyed by WidgetID. */
+    WidgetIDCell *id_hash;
+    /* These are the root widgets for rebuilding. */
+    ShellNode *shells;
+    /* A dummy value that's never the child of any shell, for
+       recovery after exhausting the valid WidgetID space. */
+    Widget orphan_widget;
+} WidgetIDTable;
+
 typedef struct _Globals {
     EditresBlock block;
     SVErrorInfo error_info;
     ProtocolStream stream;
     ProtocolStream *command_stream;	/* command stream */
+    // TODO: can this just go away?
 #if defined(LONG64) || defined(WORD64)
     unsigned long base_address;
 #endif
@@ -170,6 +254,23 @@
 static void SendFailure(Widget, Atom, ResIdent, _Xconst char*);
 static _Xconst char *VerifyWidget(Widget, WidgetInfo*);
 
+/* WidgetIDTable API (internal). */
+static WidgetIDTable *MakeWidgetIDTable(int);
+static Boolean InitializeWidgetIDTable(WidgetIDTable *, int);
+static Boolean RehashWidgetIDTable(WidgetIDTable *, int);
+static Boolean RebuildWidgetIDTable(WidgetIDTable *);
+static WidgetID InternWidget(Widget, WidgetIDTable *);
+static void UninternWidget(Widget, WidgetIDTable *);
+static Widget FindWidgetByID(WidgetID, WidgetIDTable *);
+static Boolean WidgetIsHashed(Widget, WidgetIDTable *);
+static void _ValidateTable(WidgetIDTable *, char *);
+
+/* Idempotent initializer for the static widget_id_table (internal). */
+static Boolean EnsureWidgetIDTable(void);
+
+/* WidgetIDTable cleanup callback (internal) */
+static void DestroyWidgetIDsForShell(Widget, XtPointer, XtPointer);
+
 /*
  * External
  */
@@ -180,6 +281,11 @@
  */
 static Atom res_editor_command, res_editor_protocol, client_value;
 static Globals globals;
+/* libXmu clients can't access this directly, and may not call
+   _XEditResCheckMessages (e.g., Motif doesn't). So this must be
+   initialized to NULL here. A real WidgetIDTable gets created the
+   first time the process acts as an editee. */
+static WidgetIDTable *widget_id_table = NULL;
 
 /************************************************************
  * Resource Editor Communication Code
@@ -343,7 +449,7 @@
 		XtCalloc(sizeof(WidgetInfo), sv_event->num_entries);
 
 	    for (i = 0; i < sv_event->num_entries; i++)
-		if (!_XEditResGetWidgetInfo(stream, sv_event->widgets + i))
+		if (!_XEditResGetWidgetInfoResolve(stream, sv_event->widgets + i))
 		    goto done;
 	}
 	break;
@@ -353,7 +459,7 @@
 
 	    find_event->widgets = (WidgetInfo *)XtCalloc(sizeof(WidgetInfo), 1);
 
-	    if (!(_XEditResGetWidgetInfo(stream, find_event->widgets)
+	    if (!(_XEditResGetWidgetInfoResolve(stream, find_event->widgets)
 		  && _XEditResGetSigned16(stream, &find_event->x)
 		  && _XEditResGetSigned16(stream, &find_event->y)))
 		goto done;
@@ -371,7 +477,7 @@
 		XtCalloc(sizeof(WidgetInfo), get_event->num_entries);
 
 	    for (i = 0; i < get_event->num_entries; i++)
-		if (!_XEditResGetWidgetInfo(stream, get_event->widgets + i))
+		if (!_XEditResGetWidgetInfoResolve(stream, get_event->widgets + i))
 		    goto done;
 	}
 	break;
@@ -383,7 +489,7 @@
 	    _XEditResGet16(stream, &gv_event->num_entries);
 	    gv_event->widgets = (WidgetInfo *)
 		XtCalloc(sizeof(WidgetInfo), gv_event->num_entries);
-	    _XEditResGetWidgetInfo(stream, gv_event->widgets);
+	    _XEditResGetWidgetInfoResolve(stream, gv_event->widgets);
 	}
         break;
     default:
@@ -952,7 +1058,7 @@
     {
 	if ((str = VerifyWidget(w, &sv_event->widgets[i])) != NULL)
 	{
-	    _XEditResPutWidgetInfo(stream, &sv_event->widgets[i]);
+	    _XEditResPutWidgetInfoUnresolve(stream, &sv_event->widgets[i]);
 	    _XEditResPutString8(stream, str);
 	    count++;
 	}
@@ -1019,7 +1125,7 @@
      * Insert this info into the protocol stream, and update the count
      */
     (*(info->count))++;
-    _XEditResPutWidgetInfo(info->stream, info->entry);
+    _XEditResPutWidgetInfoUnresolve(info->stream, info->entry);
     _XEditResPutString8(info->stream, buf);
 }
 
@@ -1215,7 +1321,7 @@
 	/*
 	 * Send out the widget id
 	 */
-	_XEditResPutWidgetInfo(stream, &geom_event->widgets[i]);
+	_XEditResPutWidgetInfoUnresolve(stream, &geom_event->widgets[i]);
 
 	if ((str = VerifyWidget(w, &geom_event->widgets[i])) != NULL)
 	{
@@ -1470,7 +1576,7 @@
 	/*
 	 * Send out the widget id
 	 */
-	_XEditResPutWidgetInfo(stream, &res_event->widgets[i]);
+	_XEditResPutWidgetInfoUnresolve(stream, &res_event->widgets[i]);
 	if ((str = VerifyWidget(w, &res_event->widgets[i])) != NULL)
 	{
 	    _XEditResPutBool(stream, True);	/* an error occured */
@@ -1625,7 +1731,7 @@
 
     _XEditResPut16(stream, num_widgets);	/* insert number of widgets */
     for (i = 0; i < num_widgets; i++)		/* insert Widgets themselves */
-	_XEditResPut32(stream, widget_list[i]);
+	_XEditResPutWidgetUnresolve(stream, (Widget)widget_list[i]);
 
     XtFree((char *)widget_list);
 }
@@ -1743,6 +1849,80 @@
 	_XEditResPut32(stream, info->ids[i]);
 }
 
+/*
+ * Function:
+ *	_XEditResPutWidgetInfoUnresolve
+ *
+ * Parameters:
+ *	stream - stream to insert widget info into
+ *	info   - info to insert
+ *
+ * Description:
+ *	Inserts IDs for each widget in info into the protocol stream.
+ *      (Probably only useful to toolkit implementors, rather
+ *      than resource editor programs.)
+ */
+void
+_XEditResPutWidgetInfoUnresolve(ProtocolStream *stream, WidgetInfo *info)
+{
+    unsigned int i;
+
+    _XEditResPut16(stream, info->num_widgets);
+    for (i = 0; i < info->num_widgets; i++)
+	_XEditResPutWidgetUnresolve(stream, (Widget)info->ids[i]);
+}
+
+/*
+ * Function:
+ *	_XEditResPutWidgetUnresolve
+ *
+ * Parameters:
+ *	stream - stream to insert widget info into
+ *	widget - widget to insert
+ *
+ * Description:
+ *	Inserts the ID of widget in info into the protocol stream.
+ *      (Probably only useful to toolkit implementors, rather
+ *      than resource editor programs.)
+ */
+/* Note that Motif's EditRes handler needs this.*/
+void _XEditResPutWidgetUnresolve(ProtocolStream *stream, Widget widget) {
+    WidgetID id;
+    ShellNode *node;
+    id = 0;
+    if (!EnsureWidgetIDTable()) {
+	/* Something's seriously wrong. Give the client a WidgetID
+	   value that will never resolve to a widget later. */
+	_XEditResPut32(stream, WidgetIDNull);
+    }
+    /* If we're called as part of a request that included any
+       WidgetIDs in the invalid range, we can see the orphan.  In this
+       case, we just hand the editor an indvalid WidgetID. (Whenever
+       this happens, the current request has just rebuilt & renumbered
+       the WidgetIDTable, so the editor will need to refresh its
+       widget tree anyway.) */
+    if (widget == widget_id_table->orphan_widget) {
+	_XEditResPut32(stream,  WidgetIDFirstInvalid);
+	return;
+    }
+    /* If the widget is a shell and this is the first time this shell
+       has been sent out to the client, add the destroy callback that
+       unregisters it from WidgetIDTable. (See RebuildWidgetIDTable for
+       details.) Note that the callback is static; adding it here is
+       one aspect of keeping the Widget<->WidgetID mapping
+       encapsulated within the I/O layer in this file. */
+    if (XtIsShell(widget) && !WidgetIsHashed(widget, widget_id_table)) {
+	node = (ShellNode *)XtMalloc(sizeof(ShellNode));
+	node->next = widget_id_table->shells;
+	node->shell = widget;
+	widget_id_table->shells = node;
+	XtAddCallback(widget, XtNdestroyCallback, DestroyWidgetIDsForShell, node);
+    }
+
+    id = InternWidget(widget, widget_id_table);
+    _XEditResPut32(stream, id);
+}
+
 /************************************************************
  * Code for retrieving values from the protocol stream
  ************************************************************/
@@ -1949,7 +2129,7 @@
     if (!_XEditResGet16(stream, &info->num_widgets))
 	return (False);
 
-    info->ids = (unsigned long *)XtMalloc(sizeof(long) * info->num_widgets);
+    info->ids = (unsigned long *)XtCalloc(info->num_widgets, sizeof(unsigned long));
 
     for (i = 0; i < info->num_widgets; i++)
     {
@@ -1963,9 +2143,100 @@
 	info->ids[i] |= globals.base_address;
 #endif
     }
+
     return (True);
 }
 
+/*
+ * Function:
+ *	_XEditResGetWidgetInfoResolve
+ *
+ * Parameters:
+ *	stream - protocol stream
+ *	info   - widget info struct to store into
+ *
+ * Description:
+ *	  Retrieves the list of widget IDs that follow and stores
+ *	  the resolved widgets in the widget info structure provided.
+ *	  (Probably only useful to toolkit implementors, rather
+ *	  than resource editor programs.)
+ *
+ * Returns:
+ *	True if retrieval was successful
+ */
+Bool
+_XEditResGetWidgetInfoResolve(ProtocolStream *stream, WidgetInfo *info)
+{
+    unsigned int i;
+
+    if (!_XEditResGet16(stream, &info->num_widgets))
+	return (False);
+
+    info->ids = (unsigned long *)XtCalloc(info->num_widgets, sizeof(unsigned long));
+
+    for (i = 0; i < info->num_widgets; i++)
+    {
+	if (!_XEditResGetWidgetResolve(stream, (Widget *)info->ids + i))
+	{
+	    XtFree((char *)info->ids);
+	    info->ids = NULL;
+	    return (False);
+	}
+    }
+    return (True);
+}
+
+/*
+ * Function:
+ *	_XEditResGetWidgetInfoResolve
+ *
+ * Parameters:
+ *	stream  - protocol stream
+ *	*widget - widget pointer info to store into
+ *
+ * Description:
+ *	  Retrieves one widget ID that follows and stores
+ *	  the resolved widget in the widget pointer provided.
+ *	  (Probably only useful to toolkit implementors, rather
+ *	  than resource editor programs.)
+ *
+ * Returns:
+ *	True if retrieval was successful
+ */
+Bool
+_XEditResGetWidgetResolve(ProtocolStream *stream, Widget *widget) {
+    unsigned long id;
+    if (!EnsureWidgetIDTable())
+	return (False);
+    if (!_XEditResGet32(stream, &id))
+	return (False);
+    /* We only hand out WidgetIDNull in case of unrecoverable errors,
+     * so if we get it back from the resource editor, that's an error,
+     * too. */
+    if (id == WidgetIDNull)
+	return (False);
+    /* Invalid WidgetIDs are only sent to a client in case the
+       WidgetID space was exhausted during some previous request. When
+       an invalid ID comes back in, do two things: rebuild the
+       WidgetIDTable, which renumbers all widgets; and store a
+       placeholder value, orphan_widget, in *widget. orphan_widget
+       will prevent VerifyWidget from succeeding, and so the current
+       request will fail. But because widgets get renumbered, the
+       resource editor can try to refresh the widget tree and proceed
+       after that. */
+    if (id < WidgetIDFirstValid) {
+	RebuildWidgetIDTable(widget_id_table);
+	*widget = widget_id_table->orphan_widget;
+    } else {
+	*widget = FindWidgetByID(id, widget_id_table);
+	//fprintf(stderr, "<< widget: 0x%lx\n", *widget);
+	if (widget == NULL)
+	    return (False);
+    }
+    return (True);
+}
+
+
 /************************************************************
  * Code for Loading the EditresBlock resource
  ************************************************************/
@@ -2210,4 +2481,537 @@
 
     *(char **)(warg->value) = string;
     XtFree((char *)res_list);
+}
+
+/* A progression of primes that are each approximately twice as large
+   as the previous, for expanding the various arrays. The first two
+   elements are deliberately very small, to make it easier to exercise
+   rehashing. */
+static int max_size_factor = 28;
+#if defined(DEBUG)
+static int initial_size_factor = 0;
+#else
+static int initial_size_factor = 2;
+#endif
+
+static int primes[] = {
+    11,
+    23,
+    53,
+    97,
+    193,
+    389,
+    769,
+    1543,
+    3079,
+    6151,
+    12289,
+    24593,
+    49157,
+    98317,
+    196613,
+    393241,
+    786433,
+    1572869,
+    3145739,
+    6291469,
+    12582917,
+    25165843,
+    50331653,
+    100663319,
+    201326611,
+    402653189,
+    805306457,
+    1610612741
+};
+
+static Boolean
+InitializeWidgetIDTable(WidgetIDTable *table, int size_factor)
+{
+    if (size_factor > max_size_factor)
+	return FALSE;
+    table->size_factor = size_factor;
+    table->size = primes[table->size_factor];
+    table->widget_hash =
+	(WidgetIDCell *)XtCalloc(table->size, sizeof(WidgetIDCell));
+    if (table->widget_hash == NULL)
+	return FALSE;
+    table->id_hash =
+	(WidgetIDCell *)XtCalloc(table->size, sizeof(WidgetIDCell));
+    if (table->id_hash == NULL)
+	return FALSE;
+    table->next_id = WidgetIDFirstValid;
+    table->next_invalid = WidgetIDFirstInvalid;
+    table->overflow_rehash = .5;
+    table->used = 0;
+    table->shells = NULL;
+    table->orphan_widget = NULL;
+    return TRUE;
+}
+
+static void
+DeinitializeWidgetIDTableHashes(WidgetIDTable *table)
+{
+    if (table->widget_hash != NULL)
+	XtFree((char *)table->widget_hash);
+    if (table->id_hash != NULL)
+	XtFree((char *)table->id_hash);
+}
+
+static void
+DestroyWidgetIDTable(WidgetIDTable *table, Boolean extras_too)
+{
+    ShellNode *node, *tmp;
+    DeinitializeWidgetIDTableHashes(table);
+    /* It turns out the only place this is needed, it's important to
+     * not destroy the ShellNode list or orphan_widget. So this flag
+     * is just for completeness. */
+    if (extras_too) {
+	if (table->orphan_widget != NULL)
+	    XtFree((char *)table->orphan_widget);
+	node = table->shells;
+	while (node != NULL) {
+	    tmp = node->next;
+	    XtFree((char *)node);
+	    node = tmp;
+	}
+    }
+    XtFree((char *)table);
+}
+
+static WidgetIDTable *
+MakeWidgetIDTable(int size_factor)
+{
+    WidgetIDTable *table = (WidgetIDTable*)XtCalloc(1, sizeof(WidgetIDTable));
+    if (table == NULL)
+	return NULL;
+    if (!InitializeWidgetIDTable(table, size_factor)) {
+	XtFree((char *)table);
+	return NULL;
+    }
+    return table;
+}
+
+static Boolean
+EnsureWidgetIDTable()
+{
+    if (widget_id_table == NULL)
+	/* Use size_factor = 0 to start with smaller buckets. */
+	widget_id_table = MakeWidgetIDTable(initial_size_factor);
+    return (widget_id_table != NULL);
+}
+
+/* Return the index of widget in table's widget_hash if it's present,
+   or else the index of the first free slot in widget_hash if it's
+   absent. */
+static unsigned int
+WidgetHashPos(Widget widget, WidgetIDTable *table)
+{
+    unsigned int pos, deleted_pos;
+    Boolean found_deleted;
+    Widget w;
+
+    /* TODO, maybe: actually hash the widget address. */
+    pos = (unsigned long) widget % table->size;
+    found_deleted = FALSE;
+    while (((w = table->widget_hash[pos].widget) != NULL) && (w != widget)) {
+	if ((table->widget_hash[pos].id == WidgetIDNull)
+	    && (found_deleted == FALSE)) {
+	    found_deleted = TRUE;
+	    deleted_pos = pos;
+	}
+	pos = (pos+1) % table->size;
+    }
+    if ((w != widget) && (found_deleted == TRUE))
+	pos = deleted_pos;
+    //fprintf(stderr, "/// widget 0x%lx is at widget_hash[%d]\n", widget, pos);
+    return pos;
+}
+
+/* Return the index of id in table's id_hash if it's present,
+   or else the index of the first free slot in widget_hash if it's
+   absent. */
+static unsigned int
+WidgetIDHashPos(WidgetID id, WidgetIDTable *table)
+{
+    unsigned int pos, deleted_pos;
+    Boolean found_deleted;
+    WidgetID id2;
+
+    /* Knuth's hash */
+    pos = ((id*2654435761) % 0xFFFFFFFF) % table->size;
+    //pos = id % table->size;
+    found_deleted = FALSE;
+    while (((id2 = table->id_hash[pos].id) != WidgetIDNull) && (id2 != id)) {
+	if ((table->id_hash[pos].widget == NULL)
+	    && (found_deleted == FALSE)) {
+	    found_deleted = TRUE;
+	    deleted_pos = pos;
+	}
+	pos = (pos+1) % table->size;
+    }
+    if ((id2 != id) && (found_deleted == TRUE))
+	pos = deleted_pos;
+    //fprintf(stderr, "/// id %d is at id_hash[%d]\n", id, pos);
+    return pos;
+}
+
+
+static Boolean
+WidgetIsHashed(Widget w, WidgetIDTable *table)
+{
+    unsigned int pos;
+
+    pos = WidgetHashPos(w, table);
+    if (table->widget_hash[pos].id == WidgetIDNull)
+	return FALSE;
+    return TRUE;
+}
+
+static Widget
+FindWidgetByID(WidgetID id, WidgetIDTable *table)
+{
+    unsigned int pos;
+
+    if (id < WidgetIDFirstValid) /* This should never happen, is a bug. */
+	return NULL;
+
+    pos = WidgetIDHashPos(id, table);
+    if (table->id_hash[pos].widget == NULL)
+	return NULL;
+    return table->id_hash[pos].widget;
+}
+
+static void
+UnlinkShell(Widget shell, WidgetIDTable *table)
+{
+    ShellNode *node, *prev;
+
+    node = table->shells;
+    prev = NULL;
+    while ((node != NULL) && (node->shell != shell)) {
+	prev = node;
+	node = node->next;
+    }
+    if (node != NULL) {
+	if (prev == NULL)
+	    table->shells = node->next;
+	else
+	    prev->next = node->next;
+	XtFree((char *)node);
+    }
+}
+
+static void
+UninternWidget(Widget widget, WidgetIDTable *table)
+{
+    unsigned int wpos, ipos;
+    WidgetID id;
+
+    if (table->used == 0)
+	return;
+    wpos = WidgetHashPos(widget, table);
+    if (table->widget_hash[wpos].id != WidgetIDNull) { /* already deleted */
+	id = table->widget_hash[wpos].id;
+	ipos = WidgetIDHashPos(id, table);
+	/* Mark nodes as having been deleted by zeroing the values,
+	   Rehashing will skip deleted nodes. */
+	table->widget_hash[wpos].id = WidgetIDNull;
+	table->id_hash[ipos].widget = NULL;
+	if (XtIsShell(widget))
+	    UnlinkShell(widget, table);
+	--table->used;
+	_ValidateTable(table, "after unintern");
+    }
+}
+
+
+/* This verifies all the invariants that are supposed to hold within
+   the WidgetIDTable, but not any correspondence between the
+   application's widget trees and the WidgetIDTable (because the
+   widget tree may have changed by the time the table is
+   validated). There's some unnecessary redundancy between the loop
+   over widget_hash and the one over id_hash, but this is just for
+   debugging, and it's easier to observe the symmetry between the two
+   loops than to figure out what asymmetries wouldn't subvert the
+   validation. */
+
+static void
+_ValidateTable(WidgetIDTable *table, char *msg)
+{
+#if defined(DEBUG)
+#define assertoid(expr) assert(expr); if (!(expr)) goto fail;
+    WidgetID id;
+    Widget w;
+    int i, max_id;
+    int pos;
+    ShellNode *shell_node;
+
+
+    fprintf(stderr, "//validating (size: %d, used: %d)%s%s\n",
+	    table->size, table->used, (msg==NULL)?"":" ", (msg==NULL)?"":msg);
+
+    /* Ensure that every shell is present in the widget_hash. */
+    shell_node = widget_id_table->shells;
+    max_id = 0;
+    while (shell_node != NULL) {
+	w = shell_node->shell;
+	pos = WidgetHashPos(w, table);
+	assertoid(table->widget_hash[pos].id >= WidgetIDFirstValid);
+	shell_node = shell_node->next;
+    }
+    /* Traverse widget_hash. */
+    for (i=0; i<table->size; i++) {
+	w = table->widget_hash[i].widget;
+	id = table->widget_hash[i].id;
+	if (w == NULL) /* empty */
+	    continue;
+	if (id == WidgetIDNull) /* marked as deleted */
+	    continue;
+
+	assert(id >= WidgetIDFirstValid);
+	if (id > max_id)
+	    max_id = id;
+	/* Ensure that hashing w finds this index. */
+	pos = WidgetHashPos(w, table);
+	assertoid(pos == i);
+	/* Ensure that hashing id finds this widget. */
+	pos = WidgetIDHashPos(id, table);
+	assertoid(table->id_hash[pos].widget == w);
+	assertoid(table->id_hash[pos].id == id);
+    }
+    assertoid(max_id < table->next_id);
+    /* Traverse id_hash */
+    for (i=0; i<table->size; i++) {
+	id = table->id_hash[i].id;
+	w = table->id_hash[i].widget;
+	if (id == WidgetIDNull)  /* empty */
+	    continue;
+	if (w == NULL) /* marked as deleted */
+	    continue;
+
+	assert(id >= WidgetIDFirstValid);
+
+	/* Ensure that hashing id finds this index. */
+	pos = WidgetIDHashPos(id, table);
+	assertoid(pos == i);
+	/* Ensure that hashing w finds this widget. */
+	pos = WidgetHashPos(w, table);
+	assertoid(table->widget_hash[pos].widget == w);
+	assertoid(table->widget_hash[pos].id == id);
+    }
+
+    fprintf(stderr, "// validate ok\n");
+    return;
+  fail:
+    fprintf(stderr, "// validate failed\n");
+#undef assertoid
+#endif /* defined(DEBUG) */
+}
+
+static void
+CopyWidgetIDTableInto(WidgetIDTable *from, WidgetIDTable *to)
+{
+    DeinitializeWidgetIDTableHashes(to);
+    to->size_factor      = from->size_factor;
+    to->size             = from->size;
+    to->widget_hash      = from->widget_hash;
+    to->id_hash          = from->id_hash;
+    to->next_id          = from->next_id;
+    to->overflow_rehash  = from->overflow_rehash;
+    to->used             = from->used;
+    to->shells           = from->shells;
+    to->orphan_widget    = from->orphan_widget;
+}
+
+static Boolean
+InternWidgetTree(Widget widget, WidgetIDTable *table)
+{
+    int i, num_children;
+    Widget *children;
+    WidgetID id;
+
+    if ((id = InternWidget(widget, table)) < WidgetIDFirstValid)
+	return FALSE;
+
+    num_children = FindChildren(widget, &children, True, True, True);
+    for (i = 0; i < num_children; i++)
+	if (!InternWidgetTree(children[i], table))
+	    return FALSE;
+    XtFree((char *)children);
+    return TRUE;
+}
+
+/* Rebuilding the WidgetIDTable renumbers all widgets. (And also
+   rehashes, but that's an internal detail.) */
+static Boolean
+RebuildWidgetIDTable(WidgetIDTable *table)
+{
+    WidgetIDTable *tmp_table;
+    ShellNode *node;
+    Widget shell;
+
+    _ValidateTable(table, "before rebuild");
+
+    if ((tmp_table = MakeWidgetIDTable(table->size_factor)) == NULL)
+	return FALSE;
+
+    node = table->shells;
+    while (node != NULL) {
+	shell = node->shell;
+	if (!InternWidgetTree(shell, tmp_table)) {
+	    DestroyWidgetIDTable(tmp_table, FALSE);
+	    return FALSE;
+	}
+	node = node->next;
+    }
+    CopyWidgetIDTableInto(tmp_table, table);
+    XtFree((char *)tmp_table);
+
+    _ValidateTable(table, "after rebuild");
+    return TRUE;
+}
+
+/* Rehashing rearranges WidgetNodes in new (possibly, but not
+   necessarily larger) arrays. */
+static Boolean
+RehashWidgetIDTable(WidgetIDTable *table, int size_factor)
+{
+    WidgetIDTable *tmp_table;
+    Widget w;
+    WidgetID id;
+    int i, pos;
+
+    _ValidateTable(table, "before rehash");
+    if ((tmp_table = MakeWidgetIDTable(size_factor)) == NULL)
+	return FALSE;
+
+    tmp_table->next_id = table->next_id;
+    tmp_table->shells = table->shells;
+    tmp_table->orphan_widget = table->orphan_widget;
+
+    for (i = 0; i < table->size; i++) {
+ 	w = table->id_hash[i].widget;
+ 	id = table->id_hash[i].id;
+
+ 	if (w == NULL) /* empty node */
+ 	    continue;
+ 	if (id == WidgetIDNull)   /* deleted Widget */
+ 	    continue;
+
+ 	pos = WidgetHashPos(w, tmp_table);
+ 	tmp_table->widget_hash[pos].widget = w;
+ 	tmp_table->widget_hash[pos].id = id;
+
+ 	pos = WidgetIDHashPos(id, tmp_table);
+ 	tmp_table->id_hash[pos].widget = w;
+ 	tmp_table->id_hash[pos].id = id;
+ 	++tmp_table->used;
+    }
+    CopyWidgetIDTableInto(tmp_table, table);
+    XtFree((char *)tmp_table);
+
+    _ValidateTable(table, "after rehash");
+    return TRUE;
+}
+
+static Boolean
+MaybeRehashWidgetIDTable(WidgetIDTable *table)
+{
+    float used_fraction;
+
+    used_fraction = (float)table->used / (float)table->size;
+    if (used_fraction > table->overflow_rehash)
+	if (!RehashWidgetIDTable(table, table->size_factor+1))
+	    return FALSE;
+
+    return TRUE;
+}
+
+/* In principle it's possible to run out of WidgetIDs if a program
+ * creates and destroys many widgets over its lifetime, and gets
+ * queried for its widget tree many times. */
+static WidgetID
+GenerateNextWidgetID(WidgetIDTable *table)
+{
+    if (table->next_id == WidgetIDExhausted) {
+	/* Every WidgetID we've issued below WidgetIDExhausted is okay,
+	   but from now on we issue the invalid values until the
+	   client sends an invalid back to us. (See GetWidgetResolve
+	   for that.) Note an invalid value never gets stored in
+	   WidgetIDTable. */
+	//fprintf(stderr, "// exhausted the WidgetID space\n");
+	/* Of course the invalid WidgetID space could get exhausted,
+           too. When that happens, just keep handing out the first
+           invalid number. This invalidates the uniqueneness of
+           WidgetIDs in the Resource Editor, but the editor will get
+           valid WidgetIDs again once it refreshes the widget tree. */
+	if (table->next_invalid == WidgetIDFirstValid)
+	    return WidgetIDFirstInvalid;
+	return table->next_invalid++;
+    }
+    return table->next_id++;
+}
+
+static WidgetID
+InternWidget(Widget widget, WidgetIDTable *table)
+{
+    unsigned int pos;
+    WidgetID id;
+
+    if (MaybeRehashWidgetIDTable(table) == FALSE)
+	/* If rehashing failed for any reason, we're done. */
+	return WidgetIDNull;
+    pos = WidgetHashPos(widget, table);
+    id = table->widget_hash[pos].id;
+    if (id == WidgetIDNull) {
+	id = GenerateNextWidgetID(table);
+	if (id < WidgetIDFirstValid)
+	    return id;
+
+	//fprintf(stderr, "// interning widget 0x%lx id %d widget_hash[%d]", widget, id, pos);
+
+	table->widget_hash[pos].widget = widget;
+	table->widget_hash[pos].id = id;
+
+	pos = WidgetIDHashPos(id, table);
+	//fprintf(stderr, " id_hash[%d]\n", pos);
+	table->id_hash[pos].widget = widget;
+	table->id_hash[pos].id = id;
+	++table->used;
+    }
+    return id;
+}
+
+/* Clear out all descendants of widget. (Note that this could leave
+ * some WidgetIDCells interned, e.g., if some widgets have been
+ * destroyed since the last SendWidgetTree. That's unfortunate, but
+ * probably harmless. The main reason to do this cleanup is just to
+ * delay expanding the hash arrays.) */
+static void DestroyWidgetIDsForWidget(Widget widget)
+{
+    int i, num_children;
+    Widget *children;
+
+    num_children = FindChildren(widget, &children, True, True, True);
+
+    for (i = 0; i < num_children; i++) {
+	DestroyWidgetIDsForWidget(children[i]);
+	UninternWidget(children[i], widget_id_table);
+    }
+    XtFree((char *)children);
+    UninternWidget(widget, widget_id_table);
+}
+
+static void
+DestroyWidgetIDsForShell(Widget shell, XtPointer client_data, XtPointer call_data)
+{
+
+    /* This probably can't happen, but just let's be sure. */
+    if (widget_id_table == NULL) return;
+    _ValidateTable(widget_id_table, "before destroy callback");
+
+    DestroyWidgetIDsForWidget(shell);
+
+    _ValidateTable(widget_id_table, "after destroy callback");
 }
