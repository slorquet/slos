#ifndef __ARMV7M__H__
#define __ARMV7M__H__

#define getreg16(addr)     (*((volatile uint16_t*) (addr) ) )
#define getreg32(addr)     (*((volatile uint32_t*) (addr) ) )
#define putreg32(addr,val) (*((volatile uint32_t*) (addr) ) = (val))

static inline uint32_t armv7m_getipsr(void)
{
  register int ipsr asm("r0");
  asm("MRS r0, IPSR" : "=l" (ipsr));
  return ipsr & 0xFF;
}

/* System control space */
#define ARMV7M_SCS 0xE000E000

#define ARMV7M_SCB             (ARMV7M_SCS + 0x00000D00)
#define ARMV7M_REGBASE_FPU     (ARMV7M_SCS + 0x00000F00)

/* System control and ID registers */
#define ARMV7M_ICTR            (ARMV7M_SCS + 0x00000004) /* Interrupt Controller Type register */
#define ARMV7M_ACTLR           (ARMV7M_SCS + 0x00000008) /* Auxiliary control register */
#define ARMV7M_STIR            (ARMV7M_SCS + 0x000000F0) /* Software Triggered Interrupt register */

/* SCB registers */

#define ARMV7M_SCB_CPUID       (ARMV7M_SCB + 0x00000000)
#define ARMV7M_SCB_ICSR        (ARMV7M_SCB + 0x00000004)
#define ARMV7M_SCB_VTOR        (ARMV7M_SCB + 0x00000008)
#define ARMV7M_SCB_AIRCR       (ARMV7M_SCB + 0x0000000C)
#define ARMV7M_SCB_SCR         (ARMV7M_SCB + 0x00000010)
#define ARMV7M_SCB_CCR         (ARMV7M_SCB + 0x00000014)
#define ARMV7M_SCB_SHPR1       (ARMV7M_SCB + 0x00000018)
#define ARMV7M_SCB_SHPR2       (ARMV7M_SCB + 0x0000001C)
#define ARMV7M_SCB_SHPR3       (ARMV7M_SCB + 0x00000020)
#define ARMV7M_SCB_SHCSR       (ARMV7M_SCB + 0x00000024)
#define ARMV7M_SCB_CFSR        (ARMV7M_SCB + 0x00000028)
#define ARMV7M_SCB_HFSR        (ARMV7M_SCB + 0x0000002C)
#define ARMV7M_SCB_DFSR        (ARMV7M_SCB + 0x00000030)
#define ARMV7M_SCB_MMFAR       (ARMV7M_SCB + 0x00000034)
#define ARMV7M_SCB_BFAR        (ARMV7M_SCB + 0x00000038)
#define ARMV7M_SCB_AFSR        (ARMV7M_SCB + 0x0000003C)
#define ARMV7M_SCB_CPACR       (ARMV7M_SCB + 0x00000088)

#define ARMV7M_REGBASE_MPU     (ARMV7M_SCB + 0x00000090)

/* FPU extension */
#define ARMV7M_FPU_FPCCR       (ARMV7M_REGBASE_FPU + 0x00000034)
#define ARMV7M_FPU_FPCAR       (ARMV7M_REGBASE_FPU + 0x00000038)
#define ARMV7M_FPU_FPDSCR      (ARMV7M_REGBASE_FPU + 0x0000003C)
#define ARMV7M_FPU_MVFR0       (ARMV7M_REGBASE_FPU + 0x00000040)
#define ARMV7M_FPU_MVFR1       (ARMV7M_REGBASE_FPU + 0x00000044)

/* Exceptions indices */

#define ARMV7M_IRQ_NMI        2
#define ARMV7M_IRQ_HARDFAULT  3
#define ARMV7M_IRQ_MEMMANAGE  4
#define ARMV7M_IRQ_BUSFAULT   5
#define ARMV7M_IRQ_USAGEFAULT 6
#define ARMV7M_IRQ_SVCALL     11
#define ARMV7M_IRQ_DEBUG      12
#define ARMV7M_IRQ_PENDSV     14
#define ARMV7M_IRQ_SYSTICK    15
 
#endif
