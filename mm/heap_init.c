#include <config.h>
#include <stdint.h>
#include <stddef.h>
#include <slos/debug.h>
#include <slos/mm/mm.h>

/* Initialize a heap for block allocation. */
int heap_init(struct heap_s *heap, void *base, uint32_t len)
{
  heap->base   = base;
  heap->total  = len;
  heap->avail  = len;
  heap->ffree   = (struct freeblock_s*)base;
  heap->ffree->next = NULL;
  heap->ffree->size = len;
  heap->lfree = heap->ffree;
  heap->hcount = 0;
  heap->hmax   = 0;

  info("heap_init at %X, %d bytes\n", base, len);
  return 0;
}

