#include <config.h>
#include <stdint.h>
#include <errno.h>
#include <slos/mm/mm.h>

/* Initialize a heap for block allocation. */
handle_t heap_alloc(struct heap_s *heap, uint32_t size)
{
  uint32_t i;
  struct heapentry_s *entry = (struct heapentry_s) heap->base;

  /* Round up the size to the upper 4 bytes */

  size = (size+0x03) & ~0x03;

  /* Make sure the heap can store the requested size */

  if ( heap->avail < size )
    {
      return -ENOMEM;
    }

  /* Try to reuse an old entry */

  for (i=0; i<heap->hmax; i++)
    {
      if (!entry[i].handle)
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

  /* Find some RAM hole to allocate */


  /* Okay */

  entry[i].handle = i;
  entry[i].len    = size >> 2; /* low order bits are always zero */
  entry[i].base   = 0; /* Low order bits are always zero */
  entry[i].locked = 0;
  entry[i].big    = 0;

  return i;
}

