--- lib/cf-h2-proxy.c.orig	2023-05-15 03:55:59.000000000 -0700
+++ lib/cf-h2-proxy.c	2023-05-21 07:14:11.186055000 -0700
@@ -777,7 +777,7 @@
                           struct Curl_cfilter *cf,
                           struct Curl_easy *data,
                           nghttp2_session *h2,
-                          struct http_req *req,
+                          struct Curl_http_req *req,
                           const nghttp2_priority_spec *pri_spec,
                           void *stream_user_data,
                           nghttp2_data_source_read_callback read_callback,
@@ -846,7 +846,7 @@
 {
   struct cf_h2_proxy_ctx *ctx = cf->ctx;
   CURLcode result;
-  struct http_req *req = NULL;
+  struct Curl_http_req *req = NULL;
 
   infof(data, "Establish HTTP/2 proxy tunnel to %s", ts->authority);
 
