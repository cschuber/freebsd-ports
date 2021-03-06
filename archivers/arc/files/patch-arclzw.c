--- arclzw.c.orig	2013-06-27 02:00:19 UTC
+++ arclzw.c
@@ -55,9 +55,11 @@ extern u_char	*pinbuf;
 #define NOT_FND  0xFFFF
 
 extern u_char	*pinbuf;
-u_char		*inbeg, *inend;
-u_char          *outbuf;
-u_char          *outbeg, *outend; 
+u_char		*inbeg;
+u_char		*inend;
+extern u_char	*outbuf;
+u_char		*outbeg;
+extern u_char	*outend; 
 
 static int      sp;		/* current stack pointer */
 static int	inflag;
@@ -558,7 +560,7 @@ decomp(squash, f, t)		/* decompress a file */
 		 */
 		if (code >= free_ent) {
 			if (code > free_ent) {
-				if (warn) {
+				if (arcwarn) {
 					printf("Corrupted compressed file.\n");
 					printf("Invalid code %d when max is %d.\n",
 					       code, free_ent);
