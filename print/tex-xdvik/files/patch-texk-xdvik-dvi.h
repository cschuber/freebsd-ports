--- texk/xdvik/dvi.h.orig	2019-07-27 23:56:42 UTC
+++ texk/xdvik/dvi.h
@@ -5,9 +5,13 @@
 #define	SETCHAR0	0
 #define	SET1		128
 #define	SET2		129
+#define	SET3		130
+#define	SET4		131
 #define	SETRULE		132
 #define	PUT1		133
 #define	PUT2		134
+#define	PUT3		135
+#define	PUT4		136
 #define	PUTRULE		137
 #define	NOP		138
 #define	BOP		139
@@ -60,5 +64,9 @@
 #define	POSTPOST	249
 #define	SREFL		250
 #define	EREFL		251
+
+#ifdef PTEX
+#define TDIR            255
+#endif  /* PTEX */
 
 #define	TRAILER		223	/* Trailing bytes at end of file */
