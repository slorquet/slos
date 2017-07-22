#ifndef __SLOS__HEAP__H__
#define __SLOS__HEAP__H__

#include <config.h>
#include <stdint.h>

struct heap_s
{
  void               *base;   /* Address of first byte in heap */
  uint32_t            total;  /* Total number of bytes in heap */
  uint32_t            avail;  /* Available bytes */
  struct freeblock_s *ffree;  /* Address of the first free zone */
  struct freeblock_s *lfree;  /* Last free block, its size is reduced when handles are allocated */
  uint32_t            hcount; /* Number of allocated handles */
  uint32_t            hcmax;  /* Largest count of allocated handles */
};

typedef uint32_t handle_t;

/* Initialize heap structures */
int heap_init(struct heap_s *heap, void *base, uint32_t len);

/* Move unlocked blocks around to reduce fragmentation */
void heap_compact(struct heap_s *heap);

uint32_t heap_avail(struct heap_s *heap);

/* Allocae a memory block */
handle_t heap_alloc(struct heap_s *heap, uint32_t size);

/* Return the size of a block */
uint32_t heap_size(struct heap_s *heap, handle_t handle);

/* Return the memory address of a block. block should be locked */
void *heap_deref(struct heap_s *heap, handle_t handle);

/* lock a block of memory, preventing it from being moved */
void heap_lock(struct heap_s *heap, handle_t handle);

/* Unlock a locked memory block */
void heap_unlock(struct heap_s *heap, handle_t handle);

/* Release a block of memory */
int heap_free(struct heap_s *heap, handle_t handle);

/* Find the handle of a block by its pointer */
handle_t heap_find(struct heap_s *heap, void *ptr);

void heap_dump(struct heap_s *heap);

#endif /* __SLOS__MM__MM__H__ */

