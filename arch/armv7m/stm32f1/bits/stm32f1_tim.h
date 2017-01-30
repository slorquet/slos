#ifndef __ARCH__ARMV7M__STM32F1__BITS__STM32F1__TIM__H__
#define __ARCH__ARMV7M__STM32F1__BITS__STM32F1__TIM__H__

/* Register offsets */

/* TIM                            1 2 3 4 5 6 7 8 9 1011121314 */
#define STM32F1_TIM_CR1   0x00 /* x x x x x x x x x x x x x x  */
#define STM32F1_TIM_CR2   0x04 /* x x x x x x x x              */
#define STM32F1_TIM_SMCR  0x08 /* x x x x x     x x x x x x x  */
#define STM32F1_TIM_DIER  0x0C /* x x x x x x x x x x x x x x  */
#define STM32F1_TIM_SR    0x10 /* x x x x x x x x x x x x x x  */
#define STM32F1_TIM_EGR   0x14 /* x x x x x x x x x x x x x x  */
#define STM32F1_TIM_CCMR1 0x18 /* x x x x x     x x x x x x x  */
#define STM32F1_TIM_CCMR2 0x1C /* x x x x x     x              */
#define STM32F1_TIM_CCER  0x20 /* x x x x x     x x x x x x x  */
#define STM32F1_TIM_CNT   0x24 /* x x x x x x x x x x x x x x  */
#define STM32F1_TIM_PSC   0x28 /* x x x x x x x x x x x x x x  */
#define STM32F1_TIM_ARR   0x2C /* x x x x x x x x x x x x x x  */
#define STM32F1_TIM_RCR   0x30 /* x             x              */
#define STM32F1_TIM_CCR1  0x34 /* x x x x x     x x x x x x x  */
#define STM32F1_TIM_CCR2  0x38 /* x x x x x     x x     x      */
#define STM32F1_TIM_CCR3  0x3C /* x x x x x     x              */
#define STM32F1_TIM_CCR4  0x40 /* x x x x x     x              */
#define STM32F1_TIM_BDTR  0x44 /* x             x              */
#define STM32F1_TIM_DCR   0x48 /* x x x x x     x              */
#define STM32F1_TIM_DMAR  0x4C /* x x x x x     x              */

/* CR1 */

#define TIM_CR1_CEN       (1<<0)  /* Counter Enable */
#define TIM_CR1_UDIS      (1<<1)  /* Update Disable */
#define TIM_CR1_URS       (1<<2)  /* Update Request Source */
#define TIM_CR1_OPM       (1<<3)  /* One Pulse Mode */
#define TIM_CR1_DIR       (1<<4)  /* Direction */
#define TIM_CR1_CMS_SHIFT 5       /* Center Aligned Mode Selection */
#define TIM_CR1_CMS_MASK  (3<<TIM_CR1_CMS_SHIFT)
#define TIM_CR1_ARPE      7       /* Auto-Reload preload enable */
#define TIM_CR1_CKD_SHIFT 8       /* Clock Division (See ref manual) */
#define TIM_CR1_CKD_MASK  (3<<TIM_CR1_CKD_SHIFT)
#define TIM_CR1_CKD_NONE  (0<<TIM_CR1_CKD_SHIFT)
#define TIM_CR1_CKD_BY2   (1<<TIM_CR1_CKD_SHIFT)
#define TIM_CR1_CKD_BY4   (2<<TIM_CR1_CKD_SHIFT)

/* CR2 */

#define TIM_CR2_CCPC      (1<<0)  /* Capture/Compare Preloaded Control */
#define TIM_CR2_CCUS      (1<<2)  /* Capture/Compare Control Update Selection */
#define TIM_CR2_CCDS      (1<<3)  /* Capture/Compare DMA Selection */
#define TIM_CR2_MMS_SHIFT 4       /* Master Mode Selection */
#define TIM_CR2_MMS_RESET  (0<<TIM_CR2_MMS_SHIFT)
#define TIM_CR2_MMS_ENABLE (1<<TIM_CR2_MMS_SHIFT)
#define TIM_CR2_MMS_UPDATE (2<<TIM_CR2_MMS_SHIFT)
#define TIM_CR2_MMS_COMP_P (3<<TIM_CR2_MMS_SHIFT)
#define TIM_CR2_MMS_COMP_1 (4<<TIM_CR2_MMS_SHIFT)
#define TIM_CR2_MMS_COMP_2 (5<<TIM_CR2_MMS_SHIFT)
#define TIM_CR2_MMS_COMP_3 (6<<TIM_CR2_MMS_SHIFT)
#define TIM_CR2_MMS_COMP_4 (7<<TIM_CR2_MMS_SHIFT)
#define TIM_CR2_TI1S      (1<<7)  /* TI1 Selection (1 means XOR of CH1/2/3) */
#define TIM_CR2_OIS1      (1<<8)  /* Output Idle State, OC1 */
#define TIM_CR2_OIS1N     (1<<9)  /* Output Idle State, OC1N */
#define TIM_CR2_OIS2      (1<<10) /* Output Idle State, OC2 */
#define TIM_CR2_OIS2N     (1<<11) /* Output Idle State, OC2N */
#define TIM_CR2_OIS3      (1<<12) /* Output Idle State, OC3 */
#define TIM_CR2_OIS3N     (1<<13) /* Output Idle State, OC3N */
#define TIM_CR2_OIS4      (1<<14) /* Output Idle State, OC4 */

/* Slave Mode Control */

#define TIM_SMCR_SMS_SHIFT   0 /* Slave Mode Selection */
#define TIM_SMCR_SMS_MASK    (7<<TIM_SMCR_SMS_SHIFT)
#define TIM_SMCR_TS_SHIFT    4 /* Trigger Selection */
#define TIM_SMCR_TS_MASK     (7<<TIM_SMCR_TS_SHIFT)
#define TIM_SMCR_MSM         7 /* Master/Slave mode */
#define TIM_SMCR_ETF_SHIFT   8 /* External Trigger Filter */
#define TIM_SMCR_ETF_MASK   (15<<TIM_SMCR_ETF_SHIFT)
#define TIM_SMCR_ETPS_SHIFT 12 /* External Trigger Prescaler */
#define TIM_SMCR_ETPS_MASK  (3<<TIM_SMCR_ETPS_SHIFT)
#define TIM_SMCR_ECE        14 /* External Clock Enable */
#define TIM_SMCR_ETP        15 /* External Trigger Polarity */

/* DMA/Interrupt enable */

#define TIM_DIER_UIE   (1<< 0) /* Update interrupt enable */
#define TIM_DIER_CC1IE (1<< 1) /* Capture/Compare 1 interrupt enable */
#define TIM_DIER_CC2IE (1<< 2) /* Capture/Compare 2 interrupt enable */
#define TIM_DIER_CC3IE (1<< 3) /* Capture/Compare 3 interrupt enable */
#define TIM_DIER_CC4IE (1<< 4) /* Capture/Compare 4 interrupt enable */
#define TIM_DIER_COMIE (1<< 5) /* COM interrupt enable */
#define TIM_DIER_TIE   (1<< 6) /* Trigger interrupt enable */
#define TIM_DIER_BIE   (1<< 7) /* Break interrupt enable */
#define TIM_DIER_UDE   (1<< 8) /* Update DMA request enable */
#define TIM_DIER_CC1DE (1<< 9) /* Capture/Compare 1 DMA request enable */
#define TIM_DIER_CC2DE (1<<10) /* Capture/Compare 2 DMA request enable */
#define TIM_DIER_CC3DE (1<<11) /* Capture/Compare 3 DMA request enable */
#define TIM_DIER_CC4DE (1<<12) /* Capture/Compare 4 DMA request enable */
#define TIM_DIER_COMDE (1<<13) /* COM DMA request enable */
#define TIM_DIER_TDE   (1<<14) /* Trigger DMA request enable */

/* Status Register */

#define TIM_SR_UIF   (1<< 0) /* Update interrupt flag */
#define TIM_SR_CC1IF (1<< 1) /* Capture/Compare 1 interrupt flag */
#define TIM_SR_CC2IF (1<< 2) /* Capture/Compare 2 interrupt flag */
#define TIM_SR_CC3IF (1<< 3) /* Capture/Compare 3 interrupt flag */
#define TIM_SR_CC4IF (1<< 4) /* Capture/Compare 4 interrupt flag */
#define TIM_SR_COMIF (1<< 5) /* COM interrupt flag */
#define TIM_SR_TIF   (1<< 6) /* Trigger interrupt flag */
#define TIM_SR_BIF   (1<< 7) /* Break interrupt flag */
#define TIM_SR_CC1OF (1<< 9) /* Capture/Compare 1 overcapture flag */
#define TIM_SR_CC2OF (1<<10) /* Capture/Compare 2 overcapture flag */
#define TIM_SR_CC3OF (1<<11) /* Capture/Compare 3 overcapture flag */
#define TIM_SR_CC4OF (1<<12) /* Capture/Compare 4 overcapture flag */

/* Event Generation */

#define TIM_EGR_UG   (1<<0) /* Update generation */
#define TIM_EGR_CC1G (1<<1) /* Capture/Compare 1 generation */
#define TIM_EGR_CC2G (1<<2) /* Capture/Compare 2 generation */
#define TIM_EGR_CC3G (1<<3) /* Capture/Compare 3 generation */
#define TIM_EGR_CC4G (1<<4) /* Capture/Compare 4 generation */
#define TIM_EGR_COMG (1<<5) /* COM generation */
#define TIM_EGR_TG   (1<<6) /* Trigger generation */
#define TIM_EGR_BG   (1<<7) /* Break generation */

/* Capture/Compare mode (3 is like 1, 4 is like 2) */

#define TIM_CCMR_CC1S_SHIFT   0
#define TIM_CCMR_CC1S_MASK    (3<<TIM_CCMR_CC1S_SHIFT)
#define TIM_CCMR_OC1FE        (1<<2)
#define TIM_CCMR_OC1PE        (1<<3)
#define TIM_CCMR_IC1PSC_SHIFT 2
#define TIM_CCMR_IC1PSC_MASK  (3<<TIM1_CCMR_IC1PSC_SHIFT)
#define TIM_CCMR_OC1M_SHIFT   4
#define TIM_CCMR_OC1M_MASK    (7<<TIM_CCMR_OC1M_SHIFT)
#define TIM_CCMR_OC1CE        (1<<7)
#define TIM_CCMR_IC1F_SHIFT   4
#define TIM_CCMR_IC1F_MASK    (15<<TIM_CCMR_IC1F_SHIFT)
#define TIM_CCMR_CC2S_SHIFT   8
#define TIM_CCMR_CC2S_MASK    (3<<TIM_CCMR_CC2S_SHIFT)
#define TIM_CCMR_OC2FE        (1<<10)
#define TIM_CCMR_OC2PE        (1<<11)
#define TIM_CCMR_IC2PSC_SHIFT 10
#define TIM_CCMR_IC2PSC_MASK  (3<<TIM1_CCMR_IC2PSC_SHIFT)
#define TIM_CCMR_OC2M_SHIFT   12
#define TIM_CCMR_OC2M_MASK    (7<<TIM_CCMR_OC2M_SHIFT)
#define TIM_CCMR_OC2CE        (1<<15)
#define TIM_CCMR_IC2F_SHIFT   12
#define TIM_CCMR_IC2F_MASK    (15<<TIM_CCMR_IC2F_SHIFT)

/* Capture/Compare enable */

#define TIM_CCER_CC1E  (1<< 0) /* Capture/Compare 1 Output Enable */
#define TIM_CCER_CC1P  (1<< 1) /* Capture/Compare 1 Output Polarity */
#define TIM_CCER_CC1NE (1<< 2) /* Capture/Compare 1 Complementary Output Enable */
#define TIM_CCER_CC1NP (1<< 3) /* Capture/Compare 1 Complementary Output Polarity */
#define TIM_CCER_CC2E  (1<< 4) /* Capture/Compare 2 Output Enable */
#define TIM_CCER_CC2P  (1<< 5) /* Capture/Compare 2 Output Polarity */
#define TIM_CCER_CC2NE (1<< 6) /* Capture/Compare 2 Complementary Output Enable */
#define TIM_CCER_CC2NP (1<< 7) /* Capture/Compare 2 Complementary Output Polarity */
#define TIM_CCER_CC3E  (1<< 8) /* Capture/Compare 3 Output Enable */
#define TIM_CCER_CC3P  (1<< 9) /* Capture/Compare 3 Output Polarity */
#define TIM_CCER_CC3NE (1<<10) /* Capture/Compare 3 Complementary Output Enable */
#define TIM_CCER_CC3NP (1<<11) /* Capture/Compare 3 Complementary Output Polarity */
#define TIM_CCER_CC4E  (1<<12) /* Capture/Compare 4 Output Enable */
#define TIM_CCER_CC4P  (1<<13) /* Capture/Compare 4 Output Polarity */

/* Break and Dead-time */

#define TIM_BDTR_DTG_SHIFT  0 /* Dead-time generator Setup */
#define TIM_BDTR_DTG_MASK   (255<<TIM_BDTR_DTG_SHIFT)
#define TIM_BDTR_LOCK_SHIFT 8 /* Lock Configuration  */
#define TIM_BDTR_LOCK_MASK  (3<<TIM_BDTR_LOCK_SHIFT)
#define TIM_BDTR_OSSI       (1<<10) /* Off-state selection for Idle Mode */
#define TIM_BDTR_OSSR       (1<<11) /* Off-state selection for Run Mode */
#define TIM_BDTR_BKE        (1<<12) /* Break Enable */
#define TIM_BDTR_BKP        (1<<13) /* Break Polarity */
#define TIM_BDTR_AOE        (1<<14) /* Automatic Output Enable */
#define TIM_BDTR_MOE        (1<<15) /* Main Output Enable */

/* DMA control */

#define TIM_DCR_DBA_SHIFT 0 /* DMA base address */
#define TIM_DCR_DBA_MASK  (0x1F<<TIM_DCR_DBA_SHIFT)
#define TIM_DCR_DBL_SHIFT 8 /* DMA burst length */
#define TIM_DCR_DBL_MASK  (0x1F<<TIM_DCR_DBL_SHIFT)

#endif /* __ARCH__ARMV7M__STM32F1__BITS__STM32F1__TIM__H__ */

