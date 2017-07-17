#ifndef __SLOS__MM__MM__H__
#define __SLOS__MM__MM__H__

#include <config.h>
#include <stdint.h>

struct heap_s
{
  void *   base; /* Address of first byte in heap */
  uint32_t len;  /* Total number of bytes in heap */
  uint32_t avail; /* Number of free bytes in the heap */
  uint32_t hcount; /* Number of allocated handles */
  uint32_t hmax; /* Largest allocated handle */
};

struct heapentry_s
{
  uint64_t handle: 16; /* Handle index, max 65536 handles, zero if free. */
  uint64_t size  : 20; /* Block size in units of 4 bytes, max 1M units. */
  uint64_t offset: 18; /* Offset between beginning of pool and block data. */
  uint64_t locked:  1; /* TRUE if block cannot be moved. */
  uint64_t big   :  1; /* TRUE if block granularity is 16 bytes, else 4 bytes. */
};

typedef uint32_t handle_t;

/* Initialize heap structures */
int heap_init(struct heap_s *heap, void *base, uint32_t len);

/* Move unlocked blocks around to reduce fragmentation */
void heap_compact(struct heap_s *heap);

uint32_t heap_avail(struct heap_s *heap);

/* Allocae a memory block */
handle_t heap_alloc(struct heap_s *heap, uint32_t size);

/* Find the handle of a block by its pointer */
handle_t heap_find(void *ptr);

/* Return the size of a block */
uint32_t heap_size(handle_t handle);

/* lock a block of memory, preventing it from being moved */
void heap_lock(handle_t handle);

/* Return the memory address of a block. block should be locked */
void *heap_deref(handle_t handle);

/* Unlock a locked memory block */
void heap_unlock(handle_t handle);

/* Release a block of memory */
void heap_free(handle_t handle);


#endif /* __SLOS__MM__MM__H__ */

