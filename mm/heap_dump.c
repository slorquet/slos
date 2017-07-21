#include <config.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <slos/debug.h>
#include <slos/mm/mm.h>

/* Initialize a heap for block allocation. */
void heap_dump(struct heap_s *heap)
{
  uint32_t i;
  struct heapentry_s *entries = (struct heapentry_s*) ((uint8_t*)heap->base + heap->total - sizeof(struct heapentry_s));
  struct freeblock_s *cur;

  info("------------------------------\n");
  info("--- HEAP DUMP -----\n");
  info("base %p total %u\n", heap->base, heap->total);
  info("hcount %u hmax %u\n", heap->hcount, heap->hmax);
  for(i=0;i<heap->hmax;i++)
    {
      if (!entries[-i].addr)
        {
          info("#%u available\n", i);
        }
      else
        {
          info("#%u addr %p size %d %s (end %p)\n", i, entries[-i].addr, entries[-i].size, entries[-i].locked?"LOCKED":"unlocked", entries[-i].addr + entries[-i].size);
        }
    }
  info("free list, first %p last %p\n", heap->ffree, heap->lfree);
  for(cur=heap->ffree; cur != NULL; cur = cur->next)
    {
      info("@%p size %u next %p (end %p)\n", cur, cur->size, cur->next, ((uint8_t*)cur)+cur->size);
    }
  info("------------------------------\n");

}

