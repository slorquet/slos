#include <stddef.h>
#include <stdint.h>
#include <string.h>

void memset(void *dest, int c, size_t n)
{
  size_t i;
  for(i=0;i<n;i++)
    {
      ((uint8_t*)dest)[i] = (uint8_t)c;
    }
}

