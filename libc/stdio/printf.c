#include <stdarg.h>
#include <slos/stdio.h>

/*----------------------------------------------------------------------------*/
int printf(const char *fmt, ...)
{
  int ret;
  va_list ap;
  va_start(ap,fmt);
  ret = vkprintf(fmt, ap);
  va_end(ap);
  return ret;
}
