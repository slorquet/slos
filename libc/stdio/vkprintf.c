#include <stdarg.h>
#include <slos/stdio.h>

/*----------------------------------------------------------------------------*/
int vkprintf(const char *fmt, va_list ap)
{
  return streamprintf(&konsole, fmt, ap);
}
