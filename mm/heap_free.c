#include <config.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <slos/debug.h>
#include <slos/heap.h>
#include "heap_internal.h"

/* Initialize a heap for block allocation. */
int heap_free(struct heap_s *heap, handle_t handle)
{
  struct heapentry_s *entries = (struct heapentry_s*) ((uint8_t*)heap->base + heap->total - sizeof(struct heapentry_s));
  struct heapentry_s *entry;
  struct freeblock_s *fb,*cur,*prev;

  info("free handle %u\n", handle);
  entry = entries - handle;
  
  info("entries at %p, entry at %p\n", entries, entry);

  if (entry->addr==0)
    {
      err("Trying to free a handle that is not allocated\n");
      return EINVAL;
    }

  info("block address %p size %u\n", entry->addr, entry->size);

  /* Create a free block entry over the block that is freed */
  fb = (struct freeblock_s*)entry->addr;
  fb->size = entry->size;

  /* Link the block in the free list, keeping the free list sorted by address */
  for(cur = heap->ffree, prev = NULL; cur != NULL; prev=cur, cur = cur->next)
    {
      info("have a freeblock at %p, size %d, next %p\n", cur, cur->size, cur->next);
      if(cur>fb)
        {
          /* Stop, we have to insert before this block */
          info("this block is after the block to be freed\n");

          fb->next = cur;
          break;
        }
    }
 
  /* Insert the new free block in the list */

  if(prev)
    prev->next = fb; /* We are in the middle of the list: update next of previous block */
  else
    heap->ffree = fb; /* We are at the start of the list: update list head */

  if(prev) info("stat: prev: %p size %u end %p\n", prev, prev->size, ((uint8_t*)prev)+prev->size);
  info("stat: this: %p size %u end %p\n", fb  ,   fb->size,   ((uint8_t*)fb)+fb->size);
  info("stat: cur : %p size %u end %p\n", cur ,  cur->size,  ((uint8_t*)cur)+cur->size);

  /* if end of this is beginning of cur, grow this to include cur */
  if(((uint8_t*)fb)+fb->size == (uint8_t*)cur)
    {
      fb->next = cur->next;
      fb->size = fb->size + cur->size;
      info("cur integrated in this\n");
      /* Maintain pointer to last free block */
      if (!fb->next)
        {
          heap->lfree = fb;
        }
      /* Now cur has disappeared, included in fb */
    }

  /* if end of prev is beginning of this, grow prev to include this */
  if (prev)
    {
      if (((uint8_t*)prev)+prev->size == (uint8_t*)fb)
        {
          prev->next = fb->next;
          prev->size = prev->size + fb->size;
          info("this integrated in prev\n");
          /* Maintain pointer to last free block */
          if (!prev->next)
            {
              heap->lfree = prev;
            }
          /* Now fb has disappeared, included in prev */
        }
    }


  /* Erase previously allocated entry */

  entry->addr   = 0;
  entry->size   = 0;
  entry->locked = 0;
  heap->hcount -=1;

  /* If this is the last entry, reduce the index of last used entry */

  while(heap->hcmax > 0 && entries[ -(heap->hcmax - 1)].addr == 0)
  {
    info("release last entry #%d\n", heap->hcmax - 1);
    heap->hcmax       -= 1;
    heap->avail       += sizeof(struct heapentry_s);
    heap->lfree->size += sizeof(struct heapentry_s);
  }

  info("done\n");

  return 0;
}

