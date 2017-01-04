#include <stdarg.h>
#include <slos/stdio.h>

/*----------------------------------------------------------------------------*/
int kprintf(const char *fmt, ...)
{
  int ret;
  va_list ap;
  va_start(ap,fmt);
  ret = streamprintf(&konsole, fmt, ap);
  va_end(ap);
  return ret;
}
