--- src/VBox/Devices/PC/ipxe/src/core/settings.c.orig	2023-04-13 11:24:00.000000000 +0200
+++ src/VBox/Devices/PC/ipxe/src/core/settings.c	2023-04-28 11:09:40.133502000 +0200
@@ -286,7 +286,7 @@
 						     const char *name ) {
 	struct {
 		struct autovivified_settings autovivified;
-		char name[ strlen ( name ) + 1 /* NUL */ ];
+		char name[ 32 ];
 	} *new_child;
 	struct settings *settings;
 
