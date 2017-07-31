#include <stddef.h>
#include <string.h>

/* Required when linking with clang */
void __attribute__((weak)) __aeabi_memclr(void *dest, size_t n)
{
  memset(dest, 0, n);
}

