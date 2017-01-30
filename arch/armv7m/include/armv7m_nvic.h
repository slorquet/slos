#ifndef __ARMV7M__NVIC__H__
#define __ARMV7M__NVIC__H__

#include <stdint.h>
#include <stdbool.h>

#define ARMV7M_NVIC_REGBASE_ISER (ARMV7M_SCS + 0x100) /* Interrupt Set-Enable registers (15) */
#define ARMV7M_NVIC_REGBASE_ICER (ARMV7M_SCS + 0x180) /* Interrupt Clear-Enable registers (15) */
#define ARMV7M_NVIC_REGBASE_ISPR (ARMV7M_SCS + 0x200) /* Interrupt Set-Pending registers (15) */
#define ARMV7M_NVIC_REGBASE_ICPR (ARMV7M_SCS + 0x280) /* Interrupt Clear-Pending registers (15) */
#define ARMV7M_NVIC_REGBASE_IABR (ARMV7M_SCS + 0x300) /* Interrupt Active registers (15) */
#define ARMV7M_NVIC_REGBASE_IPR  (ARMV7M_SCS + 0x400) /* Interrupt Priority registers (123) */

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

void armv7m_irq_enable(void);

void armv7m_irq_disable(void);

/* Exception handler has 3 parameters:
 * - the number of the exception being processed
 * - a pointer to a void *sp pointer, that can be :
 *    - casted to struct armv7m_excontext_t to get values of saved registers
 *    - changed to support context switching
 * - an argument word that was saved during irq attach
 */
typedef void (*armv7m_irqhandler_f)(uint32_t irqno, void **context, void *arg);

void armv7m_irq_init(void);
void armv7m_irq_attach(uint32_t irqno, armv7m_irqhandler_f handler, void *arg);
void armv7m_irq_activate(uint32_t irqno, bool state);

#endif
