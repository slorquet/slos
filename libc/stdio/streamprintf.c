#include <slos/stdio.h>

/*----------------------------------------------------------------------------*/
/* This is the common routine for all printf-like functions */
int streamprintf(const struct printf_stream_s *stream, const char *fmt, va_list ap)
{
  stream->puts(fmt,stream->context);
  return 0;
}
