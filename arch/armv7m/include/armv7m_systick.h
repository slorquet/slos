#ifndef __ARMV7M__SYSTICK__H__
#define __ARMV7M__SYSTICK__H__

#include "armv7m.h"

/* SysTick */
#define ARMV7M_SYSTICK_CSR     (ARMV7M_SCS + 0x00000010) /* Control and Status Register */
#define ARMV7M_SYSTICK_RVR     (ARMV7M_SCS + 0x00000014) /* Reload Value Register */
#define ARMV7M_SYSTICK_CVR     (ARMV7M_SCS + 0x00000018) /* Current Value Register */
#define ARMV7M_SYSTICK_CALIB   (ARMV7M_SCS + 0x0000001C) /* Calibration Value Register */

/* SysTick_CSR */
#define SYSTICK_CSR_ENABLE    (1<< 0) /* Counter Enable */
#define SYSTICK_CSR_TICKINT   (1<< 1) /* Underflow Interrupt Enable */
#define SYSTICK_CSR_CLKSOURCE (1<< 2) /* Clock Source */
#define SYSTICK_CSR_COUNTFLAG (1<<16) /* Underflow Happened */

void armv7m_systick_init(void);

#endif /* __ARMV7M__SYSTICK__H__ */

