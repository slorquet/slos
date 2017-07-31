#include <stddef.h>
#include <stdint.h>
#include <string.h>

void memcpy(void *dest, const void *src, size_t n)
{
  size_t i;
  for(i=0;i<n;i++)
    {
      ((uint8_t*)dest)[i] = ((uint8_t*)src)[i];
    }
}

