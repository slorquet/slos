#ifndef _ARCH_ARMV7M_STM32L4_BITS_STM32L4_DAC_H_
#define _ARCH_ARMV7M_STM32L4_BITS_STM32L4_DAC_H_

//reg offsets
#define STM32L4_DAC_CR               0x00
#define STM32L4_DAC_SWTRGR           0x04
#define STM32L4_DAC_DHR12R1          0x08
#define STM32L4_DAC_DHR12L1          0x0C
#define STM32L4_DAC_DHR8R1           0x10
#define STM32L4_DAC_DHR12R2          0x14
#define STM32L4_DAC_DHR12L2          0x18
#define STM32L4_DAC_DHR8R2           0x1C
#define STM32L4_DAC_DHR12RD          0x20
#define STM32L4_DAC_DHR12LD          0x24
#define STM32L4_DAC_DHR8RD           0x28
#define STM32L4_DAC_DOR1             0x2C
#define STM32L4_DAC_DOR2             0x30
#define STM32L4_DAC_SR               0x34
#define STM32L4_DAC_CCR              0x38
#define STM32L4_DAC_MCR              0x3C
#define STM32L4_DAC_SHSR1            0x40
#define STM32L4_DAC_SHSR2            0x44
#define STM32L4_DAC_SHHR             0x48
#define STM32L4_DAC_SHRR             0x4C

//bits values
#define DAC_CR_EN1                   (1<<0)
#define DAC_CR_TEN1                  (1<<2)
#define DAC_CR_TSEL1_SHIFT           3
#define DAC_CR_TSEL1_MASK            (0x07 << DAC_CR_TSEL1_MASK)
#define DAC_CR_TSEL1_TIMER6          (0x00 << DAC_CR_TSEL1_MASK)
#define DAC_CR_TSEL1_TIMER7          (0x02 << DAC_CR_TSEL1_MASK)
#define DAC_CR_TSEL1_TIMER2          (0x04 << DAC_CR_TSEL1_MASK)
#define DAC_CR_TSEL1_EXTI9           (0x06 << DAC_CR_TSEL1_MASK)
#define DAC_CR_TSEL1_SOFT            (0x07 << DAC_CR_TSEL1_MASK)
#define DAC_CR_WAVE1_SHIFT           6
#define DAC_CR_WAVE1_MASK            (0x03 << DAC_CR_WAVE1_MASK)
#define DAC_CR_WAVE1_NONE            (0x00 << DAC_CR_WAVE1_MASK)
#define DAC_CR_WAVE1_NOISE           (0x01 << DAC_CR_WAVE1_MASK)
#define DAC_CR_WAVE1_TRIANGLE        (0x02 << DAC_CR_WAVE1_MASK)

#define DAC_CR_MAMP1_SHIFT           8
#define DAC_CR_MAMP1_MASK            (0x0F << DAC_CR_MAMP1_MASK)
#define DAC_CR_DMAEN1                (1<<12)
#define DAC_CR_DMAUDRIE1             (1<<13)
#define DAC_CR_CEN1                  (1<<14)
#define DAC_CR_EN2                   (1<<16)
#define DAC_CR_TEN2                  (1<<18)
#define DAC_CR_TSEL2_SHIFT           19
#define DAC_CR_TSEL2_MASK            (0x07 << DAC_CR_TSEL2_MASK)
#define DAC_CR_TSEL2_TIMER6          (0x00 << DAC_CR_TSEL2_MASK)
#define DAC_CR_TSEL2_TIMER7          (0x02 << DAC_CR_TSEL2_MASK)
#define DAC_CR_TSEL2_TIMER2          (0x04 << DAC_CR_TSEL2_MASK)
#define DAC_CR_TSEL2_EXTI9           (0x06 << DAC_CR_TSEL2_MASK)
#define DAC_CR_TSEL2_SOFT            (0x07 << DAC_CR_TSEL2_MASK)
#define DAC_CR_WAVE2_SHIFT           22
#define DAC_CR_WAVE2_MASK            (0x03 << DAC_CR_WAVE2_MASK)
#define DAC_CR_WAVE2_NONE            (0x00 << DAC_CR_WAVE2_MASK)
#define DAC_CR_WAVE2_NOISE           (0x01 << DAC_CR_WAVE2_MASK)
#define DAC_CR_WAVE2_TRIANGLE        (0x02 << DAC_CR_WAVE2_MASK)
#define DAC_CR_MAMP2_SHIFT           24
#define DAC_CR_MAMP2_MASK            (0x0F << DAC_CR_MAMP2_MASK)
#define DAC_CR_DMAEN2                (1<<28)
#define DAC_CR_DMAUDRIE2             (1<<29)
#define DAC_CR_CEN2                  (1<<30)

#define DAC_SWTRGR_SWTRIG1           (1<<0)
#define DAC_SWTRGR_SWTRIG2           (1<<1)

#define DAC_DHR12R_SHIFT             0
#define DAC_DHR12R_MASK              (0xFFF << DAC_DHR12R_SHIFT)

#define DAC_DHR12L_SHIFT             4
#define DAC_DHR12L_MASK              (0xFFF << DAC_DHR12L_SHIFT)

#define DAC_DHR8R_SHIFT              0
#define DAC_DHR8R_MASK               (0xFF << DAC_DHR8R_SHIFT)

#define DAC_DHR12RD_SHIFT            16
#define DAC_DHR12RD_MASK             (0xFFF << DAC_DHR12R_SHIFT)

#define DAC_DHR12LD_SHIFT            20
#define DAC_DHR12LD_MASK             (0xFFF << DAC_DHR12L_SHIFT)

#define DAC_DHR8RD_SHIFT             16
#define DAC_DHR8RD_MASK              (0xFF << DAC_DHR8R_SHIFT)

#define DAC_SR_DMAUDR1               (1<<13)
#define DAC_SR_CAL_FLAG1             (1<<14)
#define DAC_SR_BWST1                 (1<<15)
#define DAC_SR_DMAUDR2               (1<<29)
#define DAC_SR_CAL_FLAG2             (1<<30)
#define DAC_SR_BWST2                 (1<<31)

#define DAC_CCR_OTRIM1_SHIFT         0
#define DAC_CCR_OTRIM1_MASK          (31<<DAC_CCR_OTRIM1_SHIFT)
#define DAC_CCR_OTRIM2_SHIFT         16
#define DAC_CCR_OTRIM2_MASK          (31<<DAC_CCR_OTRIM2_SHIFT)

#define DAC_MCR_MODE1_EXTERNAL       (0<< 0)
#define DAC_MCR_MODE1_ONCHIP         (1<< 0)
#define DAC_MCR_MODE1_BUFEN          (0<< 1)
#define DAC_MCR_MODE1_NOBUF          (1<< 1)
#define DAC_MCR_MODE1_NORMAL         (0<< 2)
#define DAC_MCR_MODE1_SAMPHOLD       (1<< 2)
#define DAC_MCR_MODE2_EXTERNAL       (0<<16)
#define DAC_MCR_MODE2_ONCHIP         (1<<16)
#define DAC_MCR_MODE2_BUFEN          (0<<17)
#define DAC_MCR_MODE2_NOBUF          (1<<17)
#define DAC_MCR_MODE2_NORMAL         (0<<18)
#define DAC_MCR_MODE2_SAMPHOLD       (1<<18)

#endif /* _ARCH_ARMV7M_STM32L4_BITS_STM32L4_SPI_H_ */
