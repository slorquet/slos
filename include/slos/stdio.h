#ifndef __SLOS__STDIO__H__
#define __SLOS__STDIO__H__

/* SLOS Specific bits used to implement stdio */

#include <stdarg.h>

struct printf_stream_s
{
  void (*putchar)(const char  ch, void *context);
  int  (*puts)   (const char *ch, void *context); /* return number of chars written */
  void *context;
};

extern const struct printf_stream_s konsole;

/* kernel debug */
int vkprintf(const char *fmt, va_list ap);
int kprintf(const char *fmt, ...);

/* common printf code */
int streamprintf(const struct printf_stream_s *stream, const char *fmt, va_list ap);

#endif /* __SLOS__STDIO__H__ */
