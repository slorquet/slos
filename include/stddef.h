/* http://pubs.opengroup.org/onlinepubs/009695399/basedefs/stddef.h.html */

#ifndef __STDDEF__
#define __STDDEF__

typedef long int          ptrdiff_t;
typedef short int         wchar_t;
typedef unsigned long int size_t;

#define NULL ((void*)0)

#if defined (__GNUC__)
#define offsetof(record,member) __builtin_offsetof(record,member)
#else
/* https://en.wikipedia.org/wiki/Offsetof */
#define offsetof(record,member) ((size_t)&(((record *)0)->member))
#endif

#endif /* __STDDEF__ */
