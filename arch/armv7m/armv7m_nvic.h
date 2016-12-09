#ifndef __ARMV7M__NVIC__H__
#define __ARMV7M__NVIC__H__

#include <stdint.h>

/* These are the registers saved during exception entry */
struct armv7m_excontext_t
{
  uint32_t R0;    /* At Mem[SP+0x0 ] */
  uint32_t R1;    /* At Mem[SP+0x4 ] */
  uint32_t R2;    /* At Mem[SP+0x8 ] */
  uint32_t R3;    /* At Mem[SP+0xC ] */
  uint32_t R12;   /* At Mem[SP+0x10] */
  uint32_t LR;    /* At Mem[SP+0x14] */
  uint32_t PC;    /* At Mem[SP+0x18] Really the return address */
  uint32_t xPSR;  /* At Mem[SP+0x1C] */
  /* If FPU is enabled, FP regs stored here */
  /* Padding word if xPSR<9> is one */
  /* Old SP points here */
};

#endif /* __ARMV7M__NVIC__H__ */
