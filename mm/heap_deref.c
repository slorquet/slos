#include <config.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <slos/debug.h>
#include <slos/heap.h>
#include "heap_internal.h"

/* Return the address of an allocated block */
void *heap_deref(struct heap_s *heap, handle_t handle)
{
  struct heapentry_s *entries = (struct heapentry_s*) ((uint8_t*)heap->base + heap->total - sizeof(struct heapentry_s));

  if(handle > heap->hcmax)
    {
      err("invalid handle\n");
      return NULL;
    }

  return entries[-handle].addr;
}

