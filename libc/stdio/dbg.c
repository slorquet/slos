#include <stdarg.h>
#include <config.h>
#include <slos/debug.h>
#include <slos/stdio.h>

void dbg(const char *func, int line, int prio, const char *msg, ...)
{
  va_list ap;
  va_start(ap,msg);

  kprintf("%s:%d: ", func, line);
  vkprintf(msg, ap);

  va_end(ap);
}

