--- include/X11/Xmu/EditresP.h.orig	2019-03-16 11:42:32.000000000 -0700
+++ include/X11/Xmu/EditresP.h	2023-10-15 22:26:04.029549000 -0700
@@ -362,6 +362,21 @@
  WidgetInfo		*info
  );
 
+/* Usage hint: if you are editres, you use use _XEditResPutWidgetInfo
+ * & _XEditResPut32. If you're a program that wants to hand out IDs
+ * for your widgets, use this and _XEditResPutWidgetUnresolve. */
+void _XEditResPutWidgetInfoUnresolve
+(
+ ProtocolStream		*stream,
+ WidgetInfo		*info
+ );
+
+void _XEditResPutWidgetUnresolve
+(
+ ProtocolStream		*stream,
+ Widget			widget
+ );
+
 void _XEditResResetStream
 (
  ProtocolStream		*stream
@@ -401,6 +416,35 @@
 (
  ProtocolStream		*stream,
  WidgetInfo		*info
+ );
+
+/* Usage hint: if you are editres, you use use _XEditResGetWidgetInfo
+ * & _XEditResGet32. If you're a program that has handed out IDs for
+ * your widgets and wants to turn them back into pointers, use this
+ * and _XEditResGetWidgetResolve. */
+Bool _XEditResGetWidgetInfoResolve
+(
+ ProtocolStream		*stream,
+ WidgetInfo		*info
+ );
+
+Bool _XEditResGetWidgetResolve
+(
+ ProtocolStream		*stream,
+ Widget			*widget
+ );
+
+
+Bool _XEditResWidgetHasID
+(
+ Widget			w
+ );
+
+void _XEditResDestroyWidgetIDsForShell
+(
+ Widget			shell,
+ XtPointer		client_data,
+ XtPointer		call_data
  );
 
 _XFUNCPROTOEND
