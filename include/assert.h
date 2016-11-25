#ifndef __ASSERT__H__
#define __ASSERT__H__

#ifndef NDEBUG
#define assert(cond) if(!(cond)) { fprintf(stderr, "%s:%d: Assertion "#cond" failed\n", __FILE__, __LINE__);
#define static_assert(cond) extern char assert__failure[0!=(cond)?1:-1];extern char assert__failure[sizeof(assert__failure)] 
#else
#define assert(cond)
#define static_assert(cond)
#endif

#endif /* __ASSERT__H__ */

