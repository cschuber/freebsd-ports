--- vorbis_header_utils.c.orig	2003-10-23 19:46:32 UTC
+++ vorbis_header_utils.c
@@ -153,15 +153,15 @@ vorbis_comment *vorbis_comment_dup(vorbis_comment *vc)
     die("malloc");
   
   memcpy(new_vc, vc, sizeof(vorbis_comment));
-  new_vc->user_comments = (char **)malloc((vc->comments + 1) * sizeof(char *));
-  new_vc->comment_lengths = (int *)malloc((vc->comments + 1) * sizeof(int));
+  new_vc->user_comments = (char **)malloc((vc->comments + 1) * sizeof(*new_vc->user_comments));
+  new_vc->comment_lengths = (int *)malloc((vc->comments + 1) * sizeof(*new_vc->comment_lengths));
   if ((new_vc->user_comments == NULL) || (new_vc->comment_lengths == NULL))
     die("malloc");
   for (i = 0; i < vc->comments; i++)
     new_vc->user_comments[i] = strdup(vc->user_comments[i]);
   new_vc->user_comments[vc->comments] = 0;
   memcpy(new_vc->comment_lengths, vc->comment_lengths,
-         (vc->comments + 1) * sizeof(char *));
+         (vc->comments + 1) * sizeof(*new_vc->comment_lengths));
   new_vc->vendor = strdup(vc->vendor);
   
   return new_vc;
