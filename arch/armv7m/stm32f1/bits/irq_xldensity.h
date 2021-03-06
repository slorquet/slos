#ifndef __ARCH__ARMV7M__STM32F1__BITS__IRQ__XLDENSITY__H__
#define __ARCH__ARMV7M__STM32F1__BITS__IRQ__XLDENSITY__H__

#include <assert.h>

enum IRQS
{
  STM32F1_IRQ_WWDG = 16,
  STM32F1_IRQ_PVD,
  STM32F1_IRQ_TAMPER,
  STM32F1_IRQ_RTC,
  STM32F1_IRQ_FLASH,
  STM32F1_IRQ_RCC,
  STM32F1_IRQ_EXTI0,
  STM32F1_IRQ_EXTI1,
  STM32F1_IRQ_EXTI2,
  STM32F1_IRQ_EXTI3,
  STM32F1_IRQ_EXTI4,
  STM32F1_IRQ_DMA1_CH1,
  STM32F1_IRQ_DMA1_CH2,
  STM32F1_IRQ_DMA1_CH3,
  STM32F1_IRQ_DMA1_CH4,
  STM32F1_IRQ_DMA1_CH5,
  STM32F1_IRQ_DMA1_CH6,
  STM32F1_IRQ_DMA1_CH7,
  STM32F1_IRQ_ADC1_2,
  STM32F1_IRQ_USB_HP_CAN1_TX,
  STM32F1_IRQ_USB_LP_CAN1_RX0,
  STM32F1_IRQ_CAN1_RX1,
  STM32F1_IRQ_CAN1_SCE,
  STM32F1_IRQ_EXTI9_5,
  STM32F1_IRQ_TIM1_BRK_TIM9,
  STM32F1_IRQ_TIM1_UP_TIM10,
  STM32F1_IRQ_TIM1_TRG_COM_TIM11,
  STM32F1_IRQ_TIM1_CC,
  STM32F1_IRQ_TIM2,
  STM32F1_IRQ_TIM3,
  STM32F1_IRQ_TIM4,
  STM32F1_IRQ_I2C1_EV,
  STM32F1_IRQ_I2C1_ER,
  STM32F1_IRQ_I2C2_EV,
  STM32F1_IRQ_I2C2_ER,
  STM32F1_IRQ_SPI1,
  STM32F1_IRQ_SPI2,
  STM32F1_IRQ_USART1,
  STM32F1_IRQ_USART2,
  STM32F1_IRQ_USART3,
  STM32F1_IRQ_EXTI15_10,
  STM32F1_IRQ_RTC_ALARM,
  STM32F1_IRQ_OTG_FS_WKUP,
  STM32F1_IRQ_TIM8_BRK_TIM12,
  STM32F1_IRQ_TIM8_UP_TIM13,
  STM32F1_IRQ_TIM8_TRG_COM_TIM14,
  STM32F1_IRQ_TIM8_CC,
  STM32F1_IRQ_ADC3,
  STM32F1_IRQ_FSMC,
  STM32F1_IRQ_SDIO,
  STM32F1_IRQ_TIM5,
  STM32F1_IRQ_SPI3
  STM32F1_IRQ_UART4,
  STM32F1_IRQ_UART5,
  STM32F1_IRQ_TIM6,
  STM32F1_IRQ_TIM7,
  STM32F1_IRQ_DMA2_CH1,
  STM32F1_IRQ_DMA2_CH2,
  STM32F1_IRQ_DMA2_CH3,
  STM32F1_IRQ_DMA2_CH4_5,
  STM32F1_IRQ_LAST,

  ARCH_CHIP_NIRQS = STM32F1_IRQ_LAST - 16
};

static_assert(ARCH_CHIP_NIRQS==60);

#endif
