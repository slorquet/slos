#ifndef __ARMV8M__SYSTICK__H__
#define __ARMV8M__SYSTICK__H__

#include "armv8m.h"
#include "armv8m_nvic.h"

/* SysTick */
#define ARMV8M_SYSTICK_CSR     (ARMV8M_SCS + 0x00000010) /* Control and Status Register */
#define ARMV8M_SYSTICK_RVR     (ARMV8M_SCS + 0x00000014) /* Reload Value Register */
#define ARMV8M_SYSTICK_CVR     (ARMV8M_SCS + 0x00000018) /* Current Value Register */
#define ARMV8M_SYSTICK_CALIB   (ARMV8M_SCS + 0x0000001C) /* Calibration Value Register */

/* SysTick_CSR */
#define SYSTICK_CSR_ENABLE    (1<< 0) /* Counter Enable */
#define SYSTICK_CSR_TICKINT   (1<< 1) /* Underflow Interrupt Enable */
#define SYSTICK_CSR_CLKSOURCE (1<< 2) /* Clock Source */
#define SYSTICK_CSR_COUNTFLAG (1<<16) /* Underflow Happened */

void armv8m_systick_init(void);
void armv8m_systick_callback(armv8m_irqhandler_f handler, void *arg);

#endif /* __ARMV8M__SYSTICK__H__ */

