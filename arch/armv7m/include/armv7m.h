#ifndef __ARMV7M__H__
#define __ARMV7M__H__

#define getreg16(addr)     (*((volatile uint16_t*) (addr) ) )
#define getreg32(addr)     (*((volatile uint32_t*) (addr) ) )
#define putreg32(addr,val) (*((volatile uint32_t*) (addr) ) = (val))

#define ARMV7M_SCS 0xE000E000

#endif
