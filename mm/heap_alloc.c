#include <config.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <slos/debug.h>
#include <slos/heap.h>
#include "heap_internal.h"

/* Initialize a heap for block allocation. */
handle_t heap_alloc(struct heap_s *heap, uint32_t size)
{
  uint32_t i;
  struct heapentry_s *entries = (struct heapentry_s*) ((uint8_t*)heap->base + heap->total - sizeof(struct heapentry_s));
  struct freeblock_s *cur, *prev;
  void *addr;
  struct freeblock_s *pnx;
  uint32_t psz;

  /* Ensure minimum size */

  if (size < 8)
    {
      size = 8;
    }

  /* Round up the size to the upper 4 bytes */

  size = (size+0x03) & ~0x03;

  info("round size to %u bytes\n", size);

  /* Make sure the heap can store the requested size */

  if ( heap->avail < size )
    {
      return -ENOMEM;
    }

  /* Find a free zone big enough for allocation */
  for(cur = heap->ffree, prev=NULL; cur != NULL; prev = cur, cur = cur->next)
    {
      info("free block at %p size %u next %p\n", cur, cur->size, cur->next);
      if(cur->size >= size)
        {
          info("is usable");
          break;
        }
    }
  if(!cur)
    {
      err("no freeblock\n");
      return -ENOMEM; /* TODO: compress heap then retry */
    }


  /* Reserve mem at the beginning of the selected free block */
  addr = cur;
  info("will allocate block at %p\n", cur);

  /* Remember freeblock contents */
  pnx = cur->next;
  psz = cur->size;

  info("free block size afer alloc: %d bytes\n", psz - size);
  /* current block still exists, is now smaller and starts farther */
  if (psz - size > sizeof(struct freeblock_s))
    {
      /* There is still room for allocations in this freeblock */
      cur = (struct freeblock_s*)((uint8_t*)cur + size); /* Now the free block starts farther */
      cur->next = pnx; /* it is still in the same place in the linked list of free blocks */
      cur->size = psz - size; /* and its size is now smaller */
      info("enough room to keep a free block, now at %p, size %d\n", cur, cur->size);
    }
  else
    {
      /* No more room in this freeblock -> it disappears */
      cur = cur->next; /* the cur block is replaced by the next in chain */
      info("not enough room to keep a free block, replacing by next: %p\n", cur->next);
    }

  /* cur may have changed, maintain prev block pointer */
  if (prev)
    {
      prev->next = cur;
      info("prev block next ptr updated\n");
    }
  else
    {
      heap->ffree = cur;
    }

  /* cur may have changed, maintain last block pointer */
  if (!cur->next)
    {
      heap->lfree = cur;
    }

  /* Try to reuse an old handle entry */

  for (i=0; i<heap->hcmax; i++)
    {
      if (!entries[-i].addr)
        {
          goto found;
        }
    }

  /* No reusable entry was found, allocate a new one, if possible */

  if ( heap->avail < (size + sizeof(struct heapentry_s) ) )
    {
      return -ENOMEM;
    }

  i           = heap->hcmax;
  heap->hcmax = i + 1;

  /* Doing this, we consume some bytes in the last freeblock */
  heap->avail       -= sizeof(struct heapentry_s);
  heap->lfree->size -= sizeof(struct heapentry_s);
found:

  /* Okay */
  info("entries at %p, entry at %p\n", entries, &entries[-i]);
  entries[-i].size   = size;
  entries[-i].addr   = addr;
  entries[-i].locked = 0;
  heap->hcount +=1;

  return i;
}

