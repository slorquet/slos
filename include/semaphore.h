#ifndef __SEMAPHORE__H__
#define __SEMAPHORE__H__

/* http://pubs.opengroup.org/onlinepubs/009695399/basedefs/semaphore.h.html */

struct sem_s
{
  int count;
};

typedef struct sem_s sem_t;

int sem_init(sem_t * sem, int pshared, unsigned value);
int sem_post(sem_t * sem);
int sem_wait(sem_t * sem);
int sem_trywait(sem_t * sem);

#endif /* __SEMAPHORE__H__ */

