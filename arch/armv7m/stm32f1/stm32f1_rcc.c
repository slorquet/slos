#include <stdint.h>

#include "armv7m.h"

#include "bits/stm32f1_periphs.h"
#include "bits/stm32f1_rcc.h"

static uint32_t g_stm32f1_clock; /* current system clock frequency */

/*----------------------------------------------------------------------------*/
void stm32f1_clock_setup(void)
{
  /*RM0008 rev16 7.2.6 page 96: Default to HSI (8 MHz) */
  g_stm32f1_clock = 8000000;
}

/*----------------------------------------------------------------------------*/
uint32_t stm32f1_clock_get(void)
{
  return g_stm32f1_clock;
}

/*----------------------------------------------------------------------------*/
void stm32f1_rcc_enableperipherals(void)
{
  uint32_t reg;
  
  /* Enable APB1 peripherals */

  reg = getreg32(STM32F1_REGBASE_RCC + STM32F1_RCC_APB1ENR);

#ifdef CONFIG_STM32F1_TIM2
  reg |= RCC_APB1ENR_TIM2EN;
#endif

#ifdef CONFIG_STM32F1_TIM3
  reg |= RCC_APB1ENR_TIM3EN;
#endif

#ifdef CONFIG_STM32F1_TIM4
  reg |= RCC_APB1ENR_TIM4EN;
#endif

#ifdef CONFIG_STM32F1_TIM5
  reg |= RCC_APB1ENR_TIM5EN;
#endif

#ifdef CONFIG_STM32F1_TIM6
  reg |= RCC_APB1ENR_TIM6EN;
#endif

#ifdef CONFIG_STM32F1_TIM7
  reg |= RCC_APB1ENR_TIM7EN;
#endif

#ifdef CONFIG_STM32F1_TIM12
  reg |= RCC_APB1ENR_TIM12EN;
#endif

#ifdef CONFIG_STM32F1_TIM13
  reg |= RCC_APB1ENR_TIM13EN;
#endif

#ifdef CONFIG_STM32F1_TIM14
  reg |= RCC_APB1ENR_TIM14EN;
#endif

#ifdef CONFIG_STM32F1_RTC
  reg |= RCC_APB1ENR_RTCEN;
#endif

#ifdef CONFIG_STM32F1_WWDG
  reg |= RCC_APB1ENR_WWDGEN;
#endif

#ifdef CONFIG_STM32F1_IWDG
  reg |= RCC_APB1ENR_IWDGEN;
#endif

#ifdef CONFIG_STM32F1_SPI2
  reg |= RCC_APB1ENR_SPI2EN;
#endif

#ifdef CONFIG_STM32F1_SPI3
  reg |= RCC_APB1ENR_SPI3EN;
#endif

#ifdef CONFIG_STM32F1_USART2
  reg |= RCC_APB1ENR_USART2EN;
#endif

#ifdef CONFIG_STM32F1_USART3
  reg |= RCC_APB1ENR_USART3EN;
#endif

#ifdef CONFIG_STM32F1_UART4
  reg |= RCC_APB1ENR_UART4EN;
#endif

#ifdef CONFIG_STM32F1_UART5
  reg |= RCC_APB1ENR_UART5EN;
#endif

#ifdef CONFIG_STM32F1_I2C1
  reg |= RCC_APB1ENR_I2C1EN;
#endif

#ifdef CONFIG_STM32F1_I2C2
  reg |= RCC_APB1ENR_I2C2EN;
#endif

#ifdef CONFIG_STM32F1_USBFS
  reg |= RCC_APB1ENR_USBEN;
#endif

#ifdef CONFIG_STM32F1_CAN1
  reg |= RCC_APB1ENR_CAN1EN;
#endif

#ifdef CONFIG_STM32F1_CAN2
  reg |= RCC_APB1ENR_CAN2EN;
#endif

#ifdef CONFIG_STM32F1_BKP
  reg |= RCC_APB1ENR_BKPEN;
#endif

#ifdef CONFIG_STM32F1_PWR
  reg |= RCC_APB1ENR_PWREN;
#endif

#ifdef CONFIG_STM32F1_DAC
  reg |= RCC_APB1ENR_DACEN;
#endif

  putreg32(STM32F1_REGBASE_RCC + STM32F1_RCC_APB1ENR, reg);
  
  /* Enable APB2 peripherals */

  reg = getreg32(STM32F1_REGBASE_RCC + STM32F1_RCC_APB2ENR);

#ifdef CONFIG_STM32F1_AFIO
  reg |= RCC_APB2ENR_AFIOEN;
#endif

#ifdef CONFIG_STM32F1_EXTI
  reg |= RCC_APB2ENR_EXTIEN;
#endif

#ifdef CONFIG_STM32F1_GPIOA
  reg |= RCC_APB2ENR_IOPAEN;
#endif

#ifdef CONFIG_STM32F1_GPIOB
  reg |= RCC_APB2ENR_IOPBEN;
#endif

#ifdef CONFIG_STM32F1_GPIOC
  reg |= RCC_APB2ENR_IOPCEN;
#endif

#ifdef CONFIG_STM32F1_GPIOD
  reg |= RCC_APB2ENR_IOPDEN;
#endif

#ifdef CONFIG_STM32F1_GPIOE
  reg |= RCC_APB2ENR_IOPEEN;
#endif

#ifdef CONFIG_STM32F1_GPIOF
  reg |= RCC_APB2ENR_IOPFEN;
#endif

#ifdef CONFIG_STM32F1_GPIOG
  reg |= RCC_APB2ENR_IOPGEN;
#endif

#ifdef CONFIG_STM32F1_ADC1
  reg |= RCC_APB2ENR_ADC1EN;
#endif

#ifdef CONFIG_STM32F1_ADC2
  reg |= RCC_APB2ENR_ADC2EN;
#endif

#ifdef CONFIG_STM32F1_TIM1
  reg |= RCC_APB2ENR_TIM1EN;
#endif

#ifdef CONFIG_STM32F1_SPI1
  reg |= RCC_APB2ENR_SPI1EN;
#endif

#ifdef CONFIG_STM32F1_TIM8
  reg |= RCC_APB2ENR_TIM8EN;
#endif

#ifdef CONFIG_STM32F1_USART1
  reg |= RCC_APB2ENR_USART1EN;
#endif

#ifdef CONFIG_STM32F1_ADC3
  reg |= RCC_APB2ENR_ADC3EN;
#endif

#ifdef CONFIG_STM32F1_TIM9
  reg |= RCC_APB2ENR_TIM9EN;
#endif

#ifdef CONFIG_STM32F1_TIM10
  reg |= RCC_APB2ENR_TIM10EN;
#endif

#ifdef CONFIG_STM32F1_TIM11
  reg |= RCC_APB2ENR_TIM11EN;
#endif

  putreg32(STM32F1_REGBASE_RCC + STM32F1_RCC_APB2ENR, reg);
  
  /* Enable AHB peripherals */

  reg = getreg32(STM32F1_REGBASE_RCC + STM32F1_RCC_AHBENR);

#ifdef CONFIG_STM32F1_SDIO
  reg |= RCC_AHBENR_SDIOEN;
#endif

#ifdef CONFIG_STM32F1_DMA1
  reg |= RCC_AHBENR_DMA1EN;
#endif

#ifdef CONFIG_STM32F1_DMA2
  reg |= RCC_AHBENR_DMA2EN;
#endif

#ifdef CONFIG_STM32F1_FLASH
  reg |= RCC_AHBENR_FLASHEN;
#endif

#ifdef CONFIG_STM32F1_CRC
  reg |= RCC_AHBENR_CRCEN;
#endif

#ifdef CONFIG_STM32F1_ETH
  reg |= RCC_AHBENR_ETHMACEN | RCC_AHBENR_ETHMACRXEN | RCC_AHBENR_ETHMACTXEN;
#endif

#ifdef CONFIG_STM32F1_OTGFS
  reg |= RCC_AHBENR_OTGFSEN;
#endif

#ifdef CONFIG_STM32F1_FSMC
  reg |= RCC_AHBENR_FSMCEN;
#endif

  putreg32(STM32F1_REGBASE_RCC + STM32F1_RCC_AHBENR, reg);
  
}


