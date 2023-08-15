--- src/share/poudriere/include/fs.sh.orig	2021-08-18 11:10:31.000000000 -0700
+++ src/share/poudriere/include/fs.sh	2023-08-15 13:37:16.620363000 -0700
@@ -119,7 +119,7 @@
 		if ! [ -f "${sfile}" ] && ! : > "${sfile}"; then
 			# Cannot create our race check file, so just try
 			# and assume it is OK.
-			zfs rollback -r "${fs}@${name}" || \
+			lockf -s -w -k -t 600 /tmp/kq-poudriere zfs rollback -r "${fs}@${name}" || \
 			    err 1 "Unable to rollback ${fs}"
 			: > "${sfile}" || :
 			return
@@ -127,7 +127,7 @@
 		tries=0
 		while :; do
 			# Success
-			if zfs rollback -r "${fs}@${name}" && \
+			if lockf -s -w -k -t 600 /tmp/kq-poudriere zfs rollback -r "${fs}@${name}" && \
 			    ! [ -f "${sfile}" ]; then
 				break
 			fi
@@ -357,7 +357,7 @@
 	else
 		[ "${fs}" != "none" ] && fs=$(zfs_getfs ${mnt})
 		if [ -n "${fs}" -a "${fs}" != "none" ]; then
-			zfs destroy -rf ${fs}
+			lockf -s -w -k -t 600 /tmp/kq-poudriere zfs destroy -rf ${fs}
 			rmdir ${mnt} || :
 			# Must invalidate the zfs_getfs cache.
 			cache_invalidate _zfs_getfs "${mnt}"
