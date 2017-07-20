#include <config.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <slos/debug.h>
#include <slos/mm/mm.h>

/* Initialize a heap for block allocation. */
handle_t heap_alloc(struct heap_s *heap, uint32_t size)
{
  uint32_t i;
  struct heapentry_s *entry = (struct heapentry_s*) ((uint8_t*)heap->base + heap->total - sizeof(struct heapentry_s));
  struct freeblock_s *cur;
  void *addr;
  struct freeblock_s *pnx;
  uint32_t psz;

  /* Round up the size to the upper 4 bytes */

  size = (size+0x03) & ~0x03;

  info("round to %d bytes\n", size);

  /* Make sure the heap can store the requested size */

  if ( heap->avail < size )
    {
      return -ENOMEM;
    }

  /* Find a free zone big enough for allocation */
  for(cur = heap->ffree; cur != NULL; cur = cur->next)
    {
      if(cur->size > size)
        {
          break;
        }
    }
  if(!cur)
    {
      return -ENOMEM; /* TODO: compress heap then retry */
    }

  /* Reserve mem */
  addr = cur;

  /* Remember freeblock contents */
  pnx = cur->next;
  psz = cur->size;

  /* current block is now smaller and starts farther */

  cur = (struct freeblock_s*)((uint8_t*)cur + size);
  cur->next = pnx;
  cur->size = psz - size;

  /* Link block */
  if(heap->ffree == cur)
    {
      heap->ffree = cur;
    }

  /* Try to reuse an old entry */

  for (i=0; i<heap->hmax; i++)
    {
      if (!entry[-i].addr)
        {
          goto found;
        }
    }

  /* No reusable entry was found, allocate a new one, if possible */

  if ( heap->avail < (size + sizeof(struct heapentry_s) ) )
    {
      return -ENOMEM;
    }

  i = heap->hmax + 1;
  heap->hmax = i;

found:

  /* Okay */

  entry[i].size   = size;
  entry[i].addr   = addr;
  entry[i].locked = 0;

  return i;
}

