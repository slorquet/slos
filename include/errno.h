/* http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/errno.h.html */

#ifndef __ERRNO__H__
#define __ERRNO__H__

/* Generic errors */

#define E2BIG               1
#define E2BIG_STR           "Argument list too long."
#define EACCES              2
#define EACCES_STR          "Permission denied."
#define EAGAIN              3
#define EWOULDBLOCK         EAGAIN   
#define EAGAIN_STR          "Resource unavailable, try again"
#define EBUSY               4
#define EBUSY_STR           "Device or resource busy."
#define ECANCELED           5
#define ECANCELED_STR       "Operation canceled."
#define ECHILD              6
#define ECHILD_STR          "No child processes."
#define EDEADLK             7
#define EDEADLK_STR         "Resource deadlock would occur."
#define EDOM                8
#define EDOM_STR            "Mathematics argument out of domain of function."
#define EFAULT              9
#define EFAULT_STR          "Bad address."
#define EIDRM               10
#define EIDRM_STR           "Identifier removed."
#define EILSEQ              11
#define EILSEQ_STR          "Illegal byte sequence."
#define EINPROGRESS         12
#define EINPROGRESS_STR     "Operation in progress."
#define EINTR               13
#define EINTR_STR           "Interrupted function."
#define EINVAL              14
#define EINVAL_STR          "Invalid argument."
#define EIO                 15
#define EIO_STR             "I/O error."
#define ENOBUFS             16
#define ENOBUFS_STR         "No buffer space available."
#define ENODATA             17
#define ENODATA_STR         "No message is available on the STREAM head read queue."
#define ENODEV              18
#define ENODEV_STR          "No such device."
#define ENOLCK              19
#define ENOLCK_STR          "No locks available."
#define ENOLINK             20
#define ENOLINK_STR         "Reserved."
#define ENOMEM              21
#define ENOMEM_STR          "Not enough space."
#define ENOSR               22
#define ENOSR_STR           "No STREAM resources."
#define ENOSTR              23
#define ENOSTR_STR          "Not a STREAM."
#define ENOSYS              24
#define ENOSYS_STR          "Functionality not supported."
#define ENOTRECOVERABLE     25
#define ENOTRECOVERABLE_STR "State not recoverable."
#define ENOTSUP             26
#define ENOTSUP_STR         "Not supported."
#define ENOTTY              27
#define ENOTTY_STR          "Inappropriate I/O control operation."
#define ENXIO               28
#define ENXIO_STR           "No such device or address."
#define EOVERFLOW           29
#define EOVERFLOW_STR       "Value too large to be stored in data type."
#define EOWNERDEAD          30
#define EOWNERDEAD_STR      "Previous owner died."
#define EPERM               31
#define EPERM_STR           "Operation not permitted."
#define EPIPE               32
#define EPIPE_STR           "Broken pipe."
#define ERANGE              33
#define ERANGE_STR          "Result too large."
#define ESRCH               34
#define ESRCH_STR           "No such process."
#define ESTALE              35
#define ESTALE_STR          "Reserved."
#define ETIME               36
#define ETIME_STR           "Stream ioctl() timeout."  

/* VFS errors */

#define EBADF               50
#define EBADF_STR           "Bad file descriptor."
#define EDQUOT              51
#define EDQUOT              "Reserved."
#define EEXIST              52
#define EEXIST_STR          "File exists."
#define EFBIG               53
#define EFBIG_STR           "File too large."
#define EISDIR              54
#define EISDIR_STR          "Is a directory."
#define ELOOP               55
#define ELOOP_STR           "Too many levels of symbolic links."
#define EMFILE              56
#define EMFILE_STR          "File descriptor value too large."
#define EMLINK              57
#define EMLINK_STR          "Too many links."
#define ENAMETOOLONG        58
#define ENAMETOOLONG_STR    "Filename too long."
#define ENFILE              59
#define ENFILE_STR          "Too many files open in system."
#define ENOENT              60
#define ENOENT_STR          "No such file or directory."
#define ENOEXEC             61
#define ENOEXEC_STR         "Executable file format error."
#define ENOSPC              62
#define ENOSPC_STR          "No space left on device."
#define ENOTDIR             63
#define ENOTDIR_STR         "Not a directory or a symbolic link to a directory."
#define ENOTEMPTY           64
#define ENOTEMPTY_STR       "Directory not empty."
#define EROFS               65
#define EROFS_STR           "Read-only file system."
#define ESPIPE              66
#define ESPIPE_STR          "Invalid seek."
#define ETXTBSY             67
#define ETXTBSY_STR         "Text file busy."
#define EXDEV               68
#define EXDEV_STR           "Cross-device link. "

/* Network errors */

#define EADDRINUSE          100
#define EADDRINUSE_STR      "Address in use."
#define EADDRNOTAVAIL       101
#define EADDRNOTAVAIL_STR   "Address not available."
#define EAFNOSUPPORT        102
#define EAFNOSUPPORT_STR    "Address family not supported."
#define EALREADY            103
#define EALREADY_STR        "Connection already in progress.
#define EBADMSG             104
#define EBADMSG_STR         "Bad message."
#define ECONNABORTED        105
#define ECONNABORTED_STR    "Connection aborted."
#define ECONNREFUSED        106
#define ECONNREFUSED_STR    "Connection refused."
#define ECONNRESET          107
#define ECONNRESET_STR      "Connection reset."
#define EDESTADDRREQ        108
#define EDESTADDRREQ_STR    "Destination address required.
#define EHOSTUNREACH        109
#define EHOSTUNREACH_STR    "Host is unreachable."
#define EISCONN             110
#define EISCONN_STR         "Socket is connected."
#define EMSGSIZE            111
#define EMSGSIZE_STR        "Message too large."
#define EMULTIHOP           112
#define EMULTIHOP_STR       "Reserved."
#define ENETDOWN            113
#define ENETDOWN_STR        "Network is down."
#define ENETRESET           114
#define ENETRESET_STR       "Connection aborted by network."
#define ENETUNREACH         115
#define ENETUNREACH_STR     "Network unreachable."
#define ENOMSG              116
#define ENOMSG_STR          "No message of the desired type."
#define ENOPROTOOPT         117
#define ENOPROTOOPT_STR     "Protocol not available."
#define ENOTCONN            118
#define ENOTCONN_STR        "The socket is not connected."
#define ENOTSOCK            119
#define ENOTSOCK_STR        "Not a socket."
#define EOPNOTSUPP          120
#define EOPNOTSUPP_STR      "Operation not supported on socket."
#define EPROTO              121
#define EPROTO_STR          "Protocol error."
#define EPROTONOSUPPORT     122
#define EPROTONOSUPPORT_STR "Protocol not supported."
#define EPROTOTYPE          123
#define EPROTOTYPE_STR      "Protocol wrong type for socket."
#define ETIMEDOUT           124
#define ETIMEDOUT_STR       "Connection timed out."

#endif /* __ERRNO__H__ */
