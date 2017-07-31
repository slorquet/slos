#ifndef __STRING__H__
#define __STRING__H__

#include <stddef.h>

int strlen(const char *str);

void memset(void *dest, int c, size_t n);
void memcpy(void *dest, const void *src, size_t n);

#endif

