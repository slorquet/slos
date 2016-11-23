#ifndef ARMV7M__H
#define ARMV7M__H

#define getreg16(addr)     (*((volatile uint16_t*) (addr) ) )
#define getreg32(addr)     (*((volatile uint32_t*) (addr) ) )
#define putreg32(addr,val) (*((volatile uint32_t*) (addr) ) = (val))

#endif
