#ifndef __STDINT__H__
#define __STDINT__H__

#include <assert.h>

typedef signed char int8_t;
typedef unsigned char uint8_t;

typedef signed short int16_t;
typedef unsigned short uint16_t;

typedef signed int int32_t;
typedef unsigned int uint32_t;

typedef signed long long int int64_t;
typedef unsigned long long int uint64_t;

static_assert(sizeof( uint8_t)==1);
static_assert(sizeof(uint16_t)==2);
static_assert(sizeof(uint32_t)==4);
static_assert(sizeof(uint64_t)==8);

#endif /* __STDINT__H__ */
