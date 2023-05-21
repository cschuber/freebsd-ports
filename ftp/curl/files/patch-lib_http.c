--- lib/http.c.orig	2023-05-15 03:55:59.000000000 -0700
+++ lib/http.c	2023-05-21 07:14:13.538801000 -0700
@@ -4537,13 +4537,13 @@
   return copy;
 }
 
-CURLcode Curl_http_req_make(struct http_req **preq,
+CURLcode Curl_http_req_make(struct Curl_http_req **preq,
                             const char *method, size_t m_len,
                             const char *scheme, size_t s_len,
                             const char *authority, size_t a_len,
                             const char *path, size_t p_len)
 {
-  struct http_req *req;
+  struct Curl_http_req *req;
   CURLcode result = CURLE_OUT_OF_MEMORY;
 
   DEBUGASSERT(method);
@@ -4580,7 +4580,7 @@
   return result;
 }
 
-static CURLcode req_assign_url_authority(struct http_req *req, CURLU *url)
+static CURLcode req_assign_url_authority(struct Curl_http_req *req, CURLU *url)
 {
   char *user, *pass, *host, *port;
   struct dynbuf buf;
@@ -4646,7 +4646,7 @@
   return result;
 }
 
-static CURLcode req_assign_url_path(struct http_req *req, CURLU *url)
+static CURLcode req_assign_url_path(struct Curl_http_req *req, CURLU *url)
 {
   char *path, *query;
   struct dynbuf buf;
@@ -4694,11 +4694,11 @@
   return result;
 }
 
-CURLcode Curl_http_req_make2(struct http_req **preq,
+CURLcode Curl_http_req_make2(struct Curl_http_req **preq,
                              const char *method, size_t m_len,
                              CURLU *url, const char *scheme_default)
 {
-  struct http_req *req;
+  struct Curl_http_req *req;
   CURLcode result = CURLE_OUT_OF_MEMORY;
   CURLUcode uc;
 
@@ -4738,7 +4738,7 @@
   return result;
 }
 
-void Curl_http_req_free(struct http_req *req)
+void Curl_http_req_free(struct Curl_http_req *req)
 {
   if(req) {
     free(req->scheme);
@@ -4778,7 +4778,7 @@
 }
 
 CURLcode Curl_http_req_to_h2(struct dynhds *h2_headers,
-                             struct http_req *req, struct Curl_easy *data)
+                             struct Curl_http_req *req, struct Curl_easy *data)
 {
   const char *scheme = NULL, *authority = NULL;
   struct dynhds_entry *e;
