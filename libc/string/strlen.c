/* http://pubs.opengroup.org/onlinepubs/9699919799/functions/strlen.html */

#include <stddef.h>

size_t strlen(const char *str)
{
  size_t len=0;
  while(*str)
    {
      len++;
      str++;
    }
  return len;
}

