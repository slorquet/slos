#ifndef __SLOS__DEBUG__H__
#define __SLOS__DEBUG__H__

#include "config.h"

#if defined( CONFIG_DEBUG )

void dbg(const char *func, int line, int prio, const char *msg, ...);

#define err(msg,...)  dbg(__FUNCTION__, __LINE__, 1, msg, ##__VA_ARGS__)
#define warn(msg,...) dbg(__FUNCTION__, __LINE__, 2, msg, ##__VA_ARGS__)
#define info(msg,...) dbg(__FUNCTION__, __LINE__, 3, msg, ##__VA_ARGS__)

#else

#define err(msg,...)
#define warn(msg,...)
#define info(msg,...)

#endif

#endif /* __SLOS__DEBUG__H__ */

