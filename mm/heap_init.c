#include <config.h>
#include <stdint.h>
#include <slos/mm/mm.h>

/* Initialize a heap for block allocation. */
int heap_init(struct heap_s *heap, void *base, uint32_t len)
{
  heap->base   = base;
  heap->len    = len;
  heap->avail  = len;
  heap->hcount = 0;
  heap->hmax   = 0;

  return 0;
}

