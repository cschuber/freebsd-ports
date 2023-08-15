--- src/share/poudriere/common.sh.orig	2021-08-18 11:10:31.000000000 -0700
+++ src/share/poudriere/common.sh	2023-08-15 13:37:51.001089000 -0700
@@ -1482,11 +1482,11 @@
 
 	if [ $dozfs -eq 1 ]; then
 		# remove old snapshot if exists
-		zfs destroy -r ${fs}@${name} 2>/dev/null || :
+		lockf -s -w -k -t 600 /tmp/kq-poudriere zfs destroy -r ${fs}@${name} 2>/dev/null || :
 		rollback_file "${mnt}" "${name}" snapfile
 		unlink "${snapfile}" || :
 		#create new snapshot
-		zfs snapshot ${fs}@${name}
+		lockf -s -w -k -t 600 /tmp/kq-poudriere zfs snapshot ${fs}@${name}
 		# Mark that we are in this snapshot, which rollbackfs
 		# will check for not existing when rolling back later.
 		: > "${snapfile}"
