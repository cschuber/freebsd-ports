--- lib/http.h.orig	2023-05-15 03:55:59.000000000 -0700
+++ lib/http.h	2023-05-21 07:14:12.521821000 -0700
@@ -260,7 +260,7 @@
 /**
  * All about a core HTTP request, excluding body and trailers
  */
-struct http_req {
+struct Curl_http_req {
   char method[12];
   char *scheme;
   char *authority;
@@ -272,17 +272,17 @@
 /**
  * Create a HTTP request struct.
  */
-CURLcode Curl_http_req_make(struct http_req **preq,
+CURLcode Curl_http_req_make(struct Curl_http_req **preq,
                             const char *method, size_t m_len,
                             const char *scheme, size_t s_len,
                             const char *authority, size_t a_len,
                             const char *path, size_t p_len);
 
-CURLcode Curl_http_req_make2(struct http_req **preq,
+CURLcode Curl_http_req_make2(struct Curl_http_req **preq,
                              const char *method, size_t m_len,
                              CURLU *url, const char *scheme_default);
 
-void Curl_http_req_free(struct http_req *req);
+void Curl_http_req_free(struct Curl_http_req *req);
 
 #define HTTP_PSEUDO_METHOD ":method"
 #define HTTP_PSEUDO_SCHEME ":scheme"
@@ -306,7 +306,7 @@
  * @param data       the handle to lookup defaults like ' :scheme' from
  */
 CURLcode Curl_http_req_to_h2(struct dynhds *h2_headers,
-                             struct http_req *req, struct Curl_easy *data);
+                             struct Curl_http_req *req, struct Curl_easy *data);
 
 /**
  * All about a core HTTP response, excluding body and trailers
