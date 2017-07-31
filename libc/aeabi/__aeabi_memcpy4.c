#include <stddef.h>
#include <string.h>

/* Required when linking with clang */
void __attribute__((weak)) __aeabi_memcpy4(void *dest, const void *src, size_t n)
{
  memcpy(dest, src, n);
}

