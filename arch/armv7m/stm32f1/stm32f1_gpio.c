#include <config.h>

#include "armv7m.h"

#include <bits/stm32f1_periphs.h>
#include <bits/stm32f1_gpio.h>

static const uint32_t g_stm32f1_gpioaddr[] =
{
#ifdef STM32F1_GPIOA
  STM32F1_REGBASE_GPIOA,
#else
  0,
#endif
#ifdef STM32F1_GPIOB
  STM32F1_REGBASE_GPIOB,
#else
  0,
#endif
#ifdef STM32F1_GPIOC
  STM32F1_REGBASE_GPIOC,
#else
  0,
#endif
#ifdef STM32F1_GPIOD
  STM32F1_REGBASE_GPIOD,
#else
  0,
#endif
#ifdef STM32F1_GPIOE
  STM32F1_REGBASE_GPIOE,
#else
  0,
#endif
#ifdef STM32F1_GPIOF
  STM32F1_REGBASE_GPIOF,
#else
  0,
#endif
#ifdef STM32F1_GPIOG
  STM32F1_REGBASE_GPIOG,
#else
  0,
#endif
}

/*----------------------------------------------------------------------------*/
static inline void stm32l4_gpio_putreg(const uint32_t base, uint32_t regoff, uint32_t value)
{
  putreg32(base + regoff, value);
}

/*----------------------------------------------------------------------------*/
static inline uint32_t stm32f1_gpio_getreg(const uint32_t base, uint32_t regoff)
{
  return getreg32(base + regoff);
}

/*----------------------------------------------------------------------------*/
static inline void stm32f1_gpio_updatereg(const uint32_t base, uint32_t regoff, uint32_t set, uint32_t clr)
{
  uint32_t val;
  val = getreg32(base + regoff);
  val &= ~clr;
  val |=  set;
  putreg32(base + regoff, val);
}

/*----------------------------------------------------------------------------*/
void stm32f1_gpio_init(uint32_t gpio)
{
  uint32_t reg,val;
  uint32_t line = (gpiodesc & GPIO_FLAGS_LINE_MASK) >> GPIO_FLAGS_LINE_SHIFT;
  uint32_t port = (gpiodesc & GPIO_FLAGS_PORT_MASK) >> GPIO_FLAGS_PORT_SHIFT;
}

/*----------------------------------------------------------------------------*/
void stm32f1_gpio_write(uint32_t gpio, bool state)
{
  uint32_t reg,val;
  uint32_t line = (gpiodesc & GPIO_FLAGS_LINE_MASK) >> GPIO_FLAGS_LINE_SHIFT;
  uint32_t port = (gpiodesc & GPIO_FLAGS_PORT_MASK) >> GPIO_FLAGS_PORT_SHIFT;
}

