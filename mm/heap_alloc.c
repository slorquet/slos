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

  info("round size to %u bytes\n", size);

  /* Make sure the heap can store the requested size */

  if ( heap->avail < size )
    {
      return -ENOMEM;
    }

  /* Find a free zone big enough for allocation */
  for(cur = heap->ffree; cur != NULL; cur = cur->next)
    {
      info("free block at %p size %u next %p\n", cur, cur->size, cur->next);
      if(cur->size > size)
        {
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
  /* current block is now smaller and starts farther */
  if (psz-size > sizeof(struct freeblock_s))
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

  /* If the cur block is the first one of the chain, update the first block*/
  if(heap->ffree == addr)
    {
      info("cur block is first one, updating head, new first block at %p\n", cur);
      heap->ffree = cur;
    }

  /* If the cur block is the last block, update the pointer to the last block */
  if(cur == NULL)
  /* Try to reuse an old handle entry */

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

  /* Doing this, we consume some bytes in the last freeblock */
  heap->avail -= sizeof(struct heapentry_s);

found:

  /* Okay */

  entry[i].size   = size;
  entry[i].addr   = addr;
  entry[i].locked = 0;

  return i;
}

