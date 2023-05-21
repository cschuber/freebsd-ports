--- lib/http1.h.orig	2023-05-15 03:55:59.000000000 -0700
+++ lib/http1.h	2023-05-21 07:14:31.953303000 -0700
@@ -34,7 +34,7 @@
 #define H1_PARSE_OPT_STRICT     (1 << 0)
 
 struct h1_req_parser {
-  struct http_req *req;
+  struct Curl_http_req *req;
   struct bufq scratch;
   size_t scratch_skip;
   const char *line;
@@ -51,7 +51,7 @@
                                const char *scheme_default, int options,
                                CURLcode *err);
 
-CURLcode Curl_h1_req_dprint(const struct http_req *req,
+CURLcode Curl_h1_req_dprint(const struct Curl_http_req *req,
                             struct dynbuf *dbuf);
 
 
