#include <config.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <slos/debug.h>
#include <slos/mm/mm.h>

/* Initialize a heap for block allocation. */
int heap_free(struct heap_s *heap, handle_t handle)
{
  uint32_t i;
  struct heapentry_s *entries = (struct heapentry_s*) ((uint8_t*)heap->base + heap->total - sizeof(struct heapentry_s));
  struct heapentry_s *entry;

  info("free handle %u\n", handle);
  entry = entries - handle;

  info("block address %p size %u\n", entry->addr, entry->size);

  return 0;
}

