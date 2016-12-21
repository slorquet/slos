/* http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/errno.h.html */

#ifndef __ERRNO__H__
#define __ERRNO__H__

#define E2BIG              1
#define E2BIG_STR          "Argument list too long."
#define EACCES             2
#define EACCES_STR         "Permission denied."
#define EADDRINUSE         3
#define EADDRINUSE_STR     "Address in use."
#define EADDRNOTAVAIL      4
#define EADDRNOTAVAIL_STR  "Address not available."
#define EAFNOSUPPORT       5
#define EAFNOSUPPORT_STR   "Address family not supported."
#define EAGAIN             6
#define EAGAIN_STR         "Resource unavailable, try again"
#define EALREADY           7
#define EALREADY_STR       "Connection already in progress.
#define EBADF              8
#define EBADF_STR          "Bad file descriptor."
#define EBADMSG            9
#define EBADMSG_STR        "Bad message."
#define EBUSY              10
#define EBUSY_STR          "Device or resource busy."
#define ECANCELED          11
#define ECANCELED_STR      "Operation canceled."
#define ECHILD             12
#define ECHILD_STR         "No child processes."
#define ECONNABORTED       13
#define ECONNABORTED_STR   "Connection aborted."
#define ECONNREFUSED       14
#define ECONNREFUSED_STR   "Connection refused."
#define ECONNRESET         15
#define ECONNRESET_STR     "Connection reset."
#define EDEADLK            16
#define EDEADLK_STR        "Resource deadlock would occur."
#define EDESTADDRREQ       17
#define EDESTADDRREQ_STR   "Destination address required.
#define EDOM               18
#define EDOM_STR           "Mathematics argument out of domain of function."
#define EDQUOT             19
#define EDQUOT             "Reserved."
#define EEXIST             20
#define EEXIST_STR         "File exists."
#define EFAULT    21
"Bad address."
#define EFBIG    22
"File too large."
#define EHOSTUNREACH    23
"Host is unreachable."
#define EIDRM    24
"Identifier removed."
#define EILSEQ    25
"Illegal byte sequence."
#define EINPROGRESS    26
"Operation in progress."
#define EINTR    27
"Interrupted function."
#define EINVAL    28
"Invalid argument."
#define EIO    29
"I/O error."
#define EISCONN    30
"Socket is connected."
#define EISDIR    31
"Is a directory."
#define ELOOP    32
"Too many levels of symbolic links."
#define EMFILE    33
"File descriptor value too large."
#define EMLINK    34
"Too many links."
#define EMSGSIZE    35
"Message too large."
#define EMULTIHOP    36
"Reserved."
#define ENAMETOOLONG    37
"Filename too long."
#define ENETDOWN    38
"Network is down."
#define ENETRESET    39
"Connection aborted by network."
#define ENETUNREACH    40
"Network unreachable."
#define ENFILE    41
"Too many files open in system."
#define ENOBUFS    42
"No buffer space available."
#define ENODATA    43
"No message is available on the STREAM head read queue."
#define ENODEV    44
"No such device."
#define ENOENT    45
"No such file or directory."
#define ENOEXEC    46
"Executable file format error."
#define ENOLCK    47
"No locks available."
#define ENOLINK    48
"Reserved."
#define ENOMEM    49
"Not enough space."
#define ENOMSG    50
"No message of the desired type."
#define ENOPROTOOPT    51
"Protocol not available."
#define ENOSPC    52
"No space left on device."
#define ENOSR    53
"#define OB XSR     #define Option Start     No STREAM resources. #define Option End    "
#define ENOSTR    54
"#define OB XSR     #define Option Start     Not a STREAM. #define Option End    "
#define ENOSYS    55
"Functionality not supported."
#define ENOTCONN    56
"The socket is not connected."
#define ENOTDIR    57
"Not a directory or a symbolic link to a directory."
#define ENOTEMPTY    58
"Directory not empty."
#define ENOTRECOVERABLE   59
"State not recoverable."
#define ENOTSOCK    60
"Not a socket."
#define ENOTSUP    61
"Not supported (may be the same value as #define EOPNOTSUPP    )."
#define ENOTTY    62
"Inappropriate I/O control operation."
#define ENXIO    63
"No such device or address."
#define EOPNOTSUPP    64
"Operation not supported on socket (may be the same value as #define ENOTSUP    )."
#define EOVERFLOW    65
"Value too large to be stored in data type."
#define EOWNERDEAD    66
"Previous owner died."
#define EPERM    67
"Operation not permitted."
#define EPIPE    68
"Broken pipe."
#define EPROTO    69
"Protocol error."
#define EPROTONOSUPPORT    70
"Protocol not supported."
#define EPROTOTYPE    71
"Protocol wrong type for socket."
#define ERANGE    72
"Result too large."
#define EROFS    73
"Read-only file system."
#define ESPIPE    74
"Invalid seek."
#define ESRCH    75
"No such process."
#define ESTALE    76
"Reserved."
#define ETIME    77
"#define OB XSR     #define Option Start     Stream ioctl() timeout. #define Option End  "  
#define ETIMEDOUT  78  
"Connection timed out."
#define ETXTBSY    79
"Text file busy."
#define EWOULDBLOCK  EAGAIN  
"Operation would block (may be the same value as #define EAGAIN    )."
#define EXDEV    80
"Cross-device link. "

#endif /* __ERRNO__H__ */
