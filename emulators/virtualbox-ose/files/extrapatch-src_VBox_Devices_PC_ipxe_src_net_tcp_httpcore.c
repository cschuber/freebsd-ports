--- src/VBox/Devices/PC/ipxe/src/net/tcp/httpcore.c.orig	2023-04-13 11:24:16.000000000 +0200
+++ src/VBox/Devices/PC/ipxe/src/net/tcp/httpcore.c	2023-04-28 20:13:10.781920000 +0200
@@ -646,9 +646,9 @@
 	int request_len = unparse_uri ( NULL, 0, http->uri,
 					URI_PATH_BIT | URI_QUERY_BIT );
 	struct {
-		uint8_t user_pw[ user_pw_len + 1 /* NUL */ ];
-		char user_pw_base64[ user_pw_base64_len + 1 /* NUL */ ];
-		char request[ request_len + 1 /* NUL */ ];
+		uint8_t user_pw[ 32 ];
+		char user_pw_base64[ 64 ];
+		char request[ 1024 ];
 		char range[48]; /* Enough for two 64-bit integers in decimal */
 	} *dynamic;
 	int partial;
