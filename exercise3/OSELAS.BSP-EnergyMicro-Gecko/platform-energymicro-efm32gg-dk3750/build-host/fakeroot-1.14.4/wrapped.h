/* Automatically generated file. Do not edit. Edit wrapawk/wrapfunc.inp. */
#ifndef WRAPPED_H
#define WRAPPED_H


extern int (*NEXT_LSTAT_NOARG)LSTAT_ARG(int ver, const char *file_name, struct stat *buf);
extern int (*NEXT_STAT_NOARG)STAT_ARG(int ver, const char *file_name, struct stat *buf);
extern int (*NEXT_FSTAT_NOARG)FSTAT_ARG(int ver, int fd, struct stat *buf);
#ifdef HAVE_FSTATAT
extern int (*NEXT_FSTATAT_NOARG)FSTATAT_ARG(int ver, int dir_fd, const char *path, struct stat *buf, int flags);
#endif /* HAVE_FSTATAT */

#ifdef STAT64_SUPPORT
extern int (*NEXT_LSTAT64_NOARG)LSTAT64_ARG(int ver, const char *file_name, struct stat64 *buf);
extern int (*NEXT_STAT64_NOARG)STAT64_ARG(int ver, const char *file_name, struct stat64 *buf);
extern int (*NEXT_FSTAT64_NOARG)FSTAT64_ARG(int ver, int fd, struct stat64 *buf);
#ifdef HAVE_FSTATAT
extern int (*NEXT_FSTATAT64_NOARG)FSTATAT64_ARG(int ver, int dir_fd, const char *path, struct stat64 *buf, int flags);
#endif /* HAVE_FSTATAT */
#endif /* STAT64_SUPPORT */

#ifdef __APPLE__
#ifdef __LP64__
extern int (*next_getattrlist)(const char *path, void *attrList, void *attrBuf, size_t attrBufSize, unsigned int options);
extern int (*next_fgetattrlist)(int fd, void *attrList, void *attrBuf, size_t attrBufSize, unsigned int options);
#else
extern int (*next_getattrlist)(const char *path, void *attrList, void *attrBuf, size_t attrBufSize, unsigned long options);
extern int (*next_fgetattrlist)(int fd, void *attrList, void *attrBuf, size_t attrBufSize, unsigned long options);
extern int (*next_getattrlist$UNIX2003)(const char *path, void *attrList, void *attrBuf, size_t attrBufSize, unsigned long options);
#endif
extern int (*next_lstat$INODE64)(const char *file_name, struct stat *buf);
extern int (*next_stat$INODE64)(const char *file_name, struct stat *buf);
extern int (*next_fstat$INODE64)(int fd, struct stat *buf);
#endif /* ifdef __APPLE__ */

extern int (*NEXT_MKNOD_NOARG)MKNOD_ARG(int ver, const char *pathname, mode_t mode, dev_t XMKNOD_FRTH_ARG dev);

#ifdef HAVE_FSTATAT
#ifdef HAVE_MKNODAT
extern int (*NEXT_MKNODAT_NOARG)MKNODAT_ARG(int ver, int dir_fd, const char *pathname, mode_t mode, dev_t dev);
#endif /* HAVE_MKNODAT */
#endif /* HAVE_FSTATAT */


extern int (*next_chown)(const char *path, uid_t owner, gid_t group);
extern int (*next_lchown)(const char *path, uid_t owner, gid_t group);
extern int (*next_fchown)(int fd, uid_t owner, gid_t group);
extern int (*next_chmod)(const char *path, mode_t mode);
extern int (*next_fchmod)(int fd, mode_t mode);
#if defined __APPLE__ && !defined __LP64__
extern int (*next_lchown$UNIX2003)(const char *path, uid_t owner, gid_t group);
extern int (*next_chmod$UNIX2003)(const char *path, mode_t mode);
extern int (*next_fchmod$UNIX2003)(int fd, mode_t mode);
#endif /* if defined __APPLE__ && !defined __LP64__ */
extern int (*next_mkdir)(const char *path, mode_t mode);
extern int (*next_unlink)(const char *pathname);
extern int (*next_rmdir)(const char *pathname);
extern int (*next_remove)(const char *pathname);
extern int (*next_rename)(const char *oldpath, const char *newpath);

#ifdef FAKEROOT_FAKENET
extern pid_t (*next_fork)(void);
extern pid_t (*next_vfork)(void);
extern int (*next_close)(int fd);
extern int (*next_dup2)(int oldfd, int newfd);
#endif /* FAKEROOT_FAKENET */


extern uid_t (*next_getuid)(void);
extern gid_t (*next_getgid)(void);
extern uid_t (*next_geteuid)(void);
extern gid_t (*next_getegid)(void);
extern int (*next_setuid)(uid_t id);
extern int (*next_setgid)(gid_t id);
extern int (*next_seteuid)(uid_t id);
extern int (*next_setegid)(gid_t id);
extern int (*next_setreuid)(SETREUID_ARG ruid, SETREUID_ARG euid);
extern int (*next_setregid)(SETREGID_ARG rgid, SETREGID_ARG egid);
#if defined __APPLE__ && !defined __LP64__
extern int (*next_setreuid$UNIX2003)(SETREUID_ARG ruid, SETREUID_ARG euid);
extern int (*next_setregid$UNIX2003)(SETREGID_ARG rgid, SETREGID_ARG egid);
#endif /* if defined __APPLE__ && !defined __LP64__ */
#ifdef HAVE_GETRESUID
extern int (*next_getresuid)(uid_t *ruid, uid_t *euid, uid_t *suid);
#endif /* HAVE_GETRESUID */
#ifdef HAVE_GETRESGID
extern int (*next_getresgid)(gid_t *rgid, gid_t *egid, gid_t *sgid);
#endif /* HAVE_GETRESGID */
#ifdef HAVE_SETRESUID
extern int (*next_setresuid)(uid_t ruid, uid_t euid, uid_t suid);
#endif /* HAVE_SETRESUID */
#ifdef HAVE_SETRESGID
extern int (*next_setresgid)(gid_t rgid, gid_t egid, gid_t sgid);
#endif /* HAVE_SETRESGID */
#ifdef HAVE_SETFSUID
extern uid_t (*next_setfsuid)(uid_t fsuid);
#endif /* HAVE_SETFSUID */
#ifdef HAVE_SETFSGID
extern gid_t (*next_setfsgid)(gid_t fsgid);
#endif /* HAVE_SETFSGID */
extern int (*next_initgroups)(const char *user, INITGROUPS_SECOND_ARG group);
extern int (*next_setgroups)(SETGROUPS_SIZE_TYPE size, const gid_t *list);

#ifdef HAVE_FSTATAT
#ifdef HAVE_FCHMODAT
extern int (*next_fchmodat)(int dir_fd, const char *path, mode_t mode, int flags);
#endif /* HAVE_FCHMODAT */
#ifdef HAVE_FCHOWNAT
extern int (*next_fchownat)(int dir_fd, const char *path, uid_t owner, gid_t group, int flags);
#endif /* HAVE_FCHOWNAT */
#ifdef HAVE_MKDIRAT
extern int (*next_mkdirat)(int dir_fd, const char *pathname, mode_t mode);
#endif /* HAVE_MKDIRAT */
#ifdef HAVE_OPENAT
extern int (*next_openat)(int dir_fd, const char *pathname, int flags);
#endif /* HAVE_OPENAT */
#ifdef HAVE_RENAMEAT
extern int (*next_renameat)(int olddir_fd, const char *oldpath, int newdir_fd, const char *newpath);
#endif /* HAVE_RENAMEAT */
#ifdef HAVE_UNLINKAT
extern int (*next_unlinkat)(int dir_fd, const char *pathname, int flags);
#endif /* HAVE_UNLINKAT */
#endif /* HAVE_FSTATAT */

#ifdef HAVE_SYS_ACL_H
extern int (*next_acl_set_fd)(int fd, acl_t acl);
extern int (*next_acl_set_file)(const char *path_p, acl_type_t type, acl_t acl);
#endif /* HAVE_SYS_ACL_H */

#ifdef HAVE_FTS_READ
extern FTSENT * (*next_fts_read)(FTS *ftsp);
#ifdef __APPLE__
extern FTSENT * (*next_fts_read$INODE64)(FTS *ftsp);
#endif /* ifdef __APPLE__ */
#endif /* HAVE_FTS_READ */
#ifdef HAVE_FTS_CHILDREN
extern FTSENT * (*next_fts_children)(FTS *ftsp, int options);
#ifdef __APPLE__
extern FTSENT * (*next_fts_children$INODE64)(FTS *ftsp, int options);
#endif /* ifdef __APPLE__ */
#endif /* HAVE_FTS_CHILDREN */
#endif
