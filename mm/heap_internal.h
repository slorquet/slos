#ifndef __MM__HEAP__INTERNAL__H__
#define __MM__HEAP__INTERNAL__H__
#include <stdint.h>

struct heapentry_s
{
  void    *addr;       /* Block address. */
  uint32_t size  : 31; /* Block size in units of 4 bytes, max 2GB*4 = 8GB */
  uint32_t locked:  1; /* TRUE if block cannot be moved. */
};

struct freeblock_s
{
  struct freeblock_s *next;
  uint32_t size;
};

#endif /*__MM__HEAP__INTERNAL__H__*/

