--- src/third_party/mozjs-60/gen-config.sh.orig	2023-05-10 02:21:42 UTC
+++ src/third_party/mozjs-60/gen-config.sh
@@ -28,6 +28,9 @@ case "$_Path" in
 }
 
 case "$_Path" in
+    "platform/aarch64/freebsd")
+        _CONFIG_OPTS="--host=aarch64-freebsd"
+	;;
     "platform/aarch64/linux")
         _CONFIG_OPTS="--host=aarch64-linux"
 	;;
@@ -82,9 +85,9 @@ rm config.cache || true
 cd mozilla-release/js/src
 rm config.cache || true
 
-PYTHON=python ./configure --without-intl-api --enable-posix-nspr-emulation --disable-trace-logging --disable-js-shell --disable-tests "$_CONFIG_OPTS"
+PYTHON=python2.7 ./configure --without-intl-api --enable-posix-nspr-emulation --disable-trace-logging --disable-js-shell --disable-tests "$_CONFIG_OPTS"
 
-make recurse_export
+gmake recurse_export
 
 cd ../../..
 
