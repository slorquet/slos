#ifndef __ARMV8M__H__
#define __ARMV8M__H__

#include <stdint.h>

#define getreg16(addr)     (*((volatile uint16_t*) (addr) ) )
#define getreg32(addr)     (*((volatile uint32_t*) (addr) ) )
#define putreg32(addr,val) (*((volatile uint32_t*) (addr) ) = (val))

static inline void updatereg32(uint32_t addr, uint32_t setbits, uint32_t clrbits)
{
  uint32_t reg = getreg32(addr);
  reg &= ~clrbits; //Clear bits before setting them, can be used as masking
  reg |= setbits;
  putreg32(addr, reg);
}

static inline uint32_t armv8m_getipsr(void)
{
  register int ipsr asm("r0");
  asm("MRS r0, IPSR" : "=l" (ipsr));
  return ipsr & 0xFF;
}

/* System control space */
#define ARMV8M_SCS             0xE000E000

#define ARMV8M_SCB             (ARMV8M_SCS + 0x00000D00)
#define ARMV8M_REGBASE_FPU     (ARMV8M_SCS + 0x00000F00)

/* System control and ID registers */
#define ARMV8M_ICTR            (ARMV8M_SCS + 0x00000004) /* Interrupt Controller Type register */
#define ARMV8M_ACTLR           (ARMV8M_SCS + 0x00000008) /* Auxiliary control register */
#define ARMV8M_STIR            (ARMV8M_SCS + 0x000000F0) /* Software Triggered Interrupt register */

/* SCB registers */

#define ARMV8M_SCB_CPUID       (ARMV8M_SCB + 0x00000000)
#define ARMV8M_SCB_ICSR        (ARMV8M_SCB + 0x00000004)
#define ARMV8M_SCB_VTOR        (ARMV8M_SCB + 0x00000008)
#define ARMV8M_SCB_AIRCR       (ARMV8M_SCB + 0x0000000C)
#define ARMV8M_SCB_SCR         (ARMV8M_SCB + 0x00000010)
#define ARMV8M_SCB_CCR         (ARMV8M_SCB + 0x00000014)
#define ARMV8M_SCB_SHPR1       (ARMV8M_SCB + 0x00000018)
#define ARMV8M_SCB_SHPR2       (ARMV8M_SCB + 0x0000001C)
#define ARMV8M_SCB_SHPR3       (ARMV8M_SCB + 0x00000020)
#define ARMV8M_SCB_SHCSR       (ARMV8M_SCB + 0x00000024)
#define ARMV8M_SCB_CFSR        (ARMV8M_SCB + 0x00000028)
#define ARMV8M_SCB_HFSR        (ARMV8M_SCB + 0x0000002C)
#define ARMV8M_SCB_DFSR        (ARMV8M_SCB + 0x00000030)
#define ARMV8M_SCB_MMFAR       (ARMV8M_SCB + 0x00000034)
#define ARMV8M_SCB_BFAR        (ARMV8M_SCB + 0x00000038)
#define ARMV8M_SCB_AFSR        (ARMV8M_SCB + 0x0000003C)
#define ARMV8M_SCB_CPACR       (ARMV8M_SCB + 0x00000088)

#define ARMV8M_REGBASE_MPU     (ARMV8M_SCB + 0x00000090)

#ifdef ARCH_ARMV8M_SECURE
/* Define the Non-secure SCB registers, only if compiling with security enabled */

#define ARMV8M_SCS_NS          0xE002E000
#define ARMV8M_SCB_NS          (ARMV8M_SCS_NS + 0x00000D00)

/* Non-secure System control and ID registers */
#define ARMV8M_ICTR_NS         (ARMV8M_SCS_NS + 0x00000004) /* Interrupt Controller Type register */
#define ARMV8M_ACTLR_NS        (ARMV8M_SCS_NS + 0x00000008) /* Auxiliary control register */
#define ARMV8M_STIR_NS         (ARMV8M_SCS_NS + 0x000000F0) /* Software Triggered Interrupt register */

/* Non-secure SCB registers */

#define ARMV8M_SCB_CPUID_NS    (ARMV8M_SCB_NS + 0x00000000)
#define ARMV8M_SCB_ICSR_NS     (ARMV8M_SCB_NS + 0x00000004)
#define ARMV8M_SCB_VTOR_NS     (ARMV8M_SCB_NS + 0x00000008)
#define ARMV8M_SCB_AIRCR_NS    (ARMV8M_SCB_NS + 0x0000000C)
#define ARMV8M_SCB_SCR_NS      (ARMV8M_SCB_NS + 0x00000010)
#define ARMV8M_SCB_CCR_NS      (ARMV8M_SCB_NS + 0x00000014)
#define ARMV8M_SCB_SHPR1_NS    (ARMV8M_SCB_NS + 0x00000018)
#define ARMV8M_SCB_SHPR2_NS    (ARMV8M_SCB_NS + 0x0000001C)
#define ARMV8M_SCB_SHPR3_NS    (ARMV8M_SCB_NS + 0x00000020)
#define ARMV8M_SCB_SHCSR_NS    (ARMV8M_SCB_NS + 0x00000024)
#define ARMV8M_SCB_CFSR_NS     (ARMV8M_SCB_NS + 0x00000028)
#define ARMV8M_SCB_HFSR_NS     (ARMV8M_SCB_NS + 0x0000002C)
#define ARMV8M_SCB_DFSR_NS     (ARMV8M_SCB_NS + 0x00000030)
#define ARMV8M_SCB_MMFAR_NS    (ARMV8M_SCB_NS + 0x00000034)
#define ARMV8M_SCB_BFAR_NS     (ARMV8M_SCB_NS + 0x00000038)
#define ARMV8M_SCB_AFSR_NS     (ARMV8M_SCB_NS + 0x0000003C)
#define ARMV8M_SCB_CPACR_NS    (ARMV8M_SCB_NS + 0x00000088)

#define ARMV8M_REGBASE_MPU_NS  (ARMV8M_SCB_NS + 0x00000090)

#endif /* ARCH_ARMV8M_SECURE */

/* FPU extension */
#define ARMV8M_FPU_FPCCR       (ARMV8M_REGBASE_FPU + 0x00000034)
#define ARMV8M_FPU_FPCAR       (ARMV8M_REGBASE_FPU + 0x00000038)
#define ARMV8M_FPU_FPDSCR      (ARMV8M_REGBASE_FPU + 0x0000003C)
#define ARMV8M_FPU_MVFR0       (ARMV8M_REGBASE_FPU + 0x00000040)
#define ARMV8M_FPU_MVFR1       (ARMV8M_REGBASE_FPU + 0x00000044)

/* Exceptions indices */

#define ARMV8M_IRQ_NMI          2
#define ARMV8M_IRQ_HARDFAULT    3
#define ARMV8M_IRQ_MEMMANAGE    4
#define ARMV8M_IRQ_BUSFAULT     5
#define ARMV8M_IRQ_USAGEFAULT   6
#define ARMV8M_IRQ_SECUREFAULT  7
#define ARMV8M_IRQ_SVCALL      11
#define ARMV8M_IRQ_DEBUG       12
#define ARMV8M_IRQ_PENDSV      14
#define ARMV8M_IRQ_SYSTICK     15
 
#endif
