#include <config.h>
#include <stdint.h>

#include "armv7m.h"

#include "bits/stm32f1_periphs.h"
#include "bits/stm32f1_gpio.h"
#include "stm32f1_gpio.h"

static const uint32_t g_stm32f1_gpioaddr[] =
{
#ifdef CONFIG_STM32F1_GPIOA
  STM32F1_REGBASE_GPIOA,
#else
  0,
#endif
#ifdef CONFIG_STM32F1_GPIOB
  STM32F1_REGBASE_GPIOB,
#else
  0,
#endif
#ifdef CONFIG_STM32F1_GPIOC
  STM32F1_REGBASE_GPIOC,
#else
  0,
#endif
#ifdef CONFIG_STM32F1_GPIOD
  STM32F1_REGBASE_GPIOD,
#else
  0,
#endif
#ifdef CONFIG_STM32F1_GPIOE
  STM32F1_REGBASE_GPIOE,
#else
  0,
#endif
#ifdef CONFIG_STM32F1_GPIOF
  STM32F1_REGBASE_GPIOF,
#else
  0,
#endif
#ifdef CONFIG_STM32F1_GPIOG
  STM32F1_REGBASE_GPIOG,
#else
  0,
#endif
};

#define STM32F1_PORTCOUNT (sizeof(g_stm32f1_gpioaddr)/sizeof(g_stm32f1_gpioaddr[0]))

/*----------------------------------------------------------------------------*/
static inline void stm32f1_gpio_putreg(const uint32_t base, uint32_t regoff, uint32_t value)
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
void stm32f1_gpio_init(uint32_t gpiodesc)
{
  uint32_t base,reg,val;
  uint32_t line = (gpiodesc & GPIO_FLAGS_LINE_MASK) >> GPIO_FLAGS_LINE_SHIFT;
  uint32_t port = (gpiodesc & GPIO_FLAGS_PORT_MASK) >> GPIO_FLAGS_PORT_SHIFT;
  if (port >= STM32F1_PORTCOUNT)
    {
      return;
    }
  base = g_stm32f1_gpioaddr[port];
  if (base==0)
    {
      return;
    }

  /* First of all, single bit changes */

  if ((gpiodesc & GPIO_FLAGS_MODE_MASK) == GPIO_MODE_IN)
    {
      /* set pull level */

      if ((gpiodesc & GPIO_FLAGS_PULL_MASK) == GPIO_PULL_UP)
        {
          stm32f1_gpio_updatereg(base, STM32F1_GPIO_ODR, 1<<line, 0);
        }
      else if ((gpiodesc & GPIO_FLAGS_PULL_MASK) == GPIO_PULL_DOWN)
        {
          stm32f1_gpio_updatereg(base, STM32F1_GPIO_ODR, 0, 1<<line);
        }

    }
  else if ((gpiodesc & GPIO_FLAGS_MODE_MASK) == GPIO_MODE_OUT)
    {
      /* set output level */

      if ((gpiodesc & GPIO_FLAGS_STATE_MASK) == GPIO_STATE_SET)
        {
          stm32f1_gpio_updatereg(base, STM32F1_GPIO_ODR, 1<<line, 0);
        }
      else if ((gpiodesc & GPIO_FLAGS_STATE_MASK) == GPIO_STATE_CLEAR)
        {
          stm32f1_gpio_updatereg(base, STM32F1_GPIO_ODR, 0, 1<<line);
        }
    }

  /* next, deal with correct CNF reg */

  /* select config register */

  if (line<8)
    {
      reg = STM32F1_GPIO_CRL;
    }
  else
    {
      reg = STM32F1_GPIO_CRH;
      line -= 8;
    }

  line <<= 2; /* transform to bit shift */

  /* erase bits that will be set later */

  val  = stm32f1_gpio_getreg(base, reg);
  val &= ~((GPIO_CNF_MASK | GPIO_MODE_MASK) << line);

  if ((gpiodesc & GPIO_FLAGS_MODE_MASK) == GPIO_MODE_IN)
    {
      /* Set mode */

      val |= GPIO_MODE_INPUT << line;

      /* set pull mode */
      if((gpiodesc & GPIO_FLAGS_PULL_MASK) == 0)
        {
          val |= GPIO_CNF_INFLOAT << line;
        }
      else
        {
          val |= GPIO_CNF_INPULL << line;
        }

    }

  else if ((gpiodesc & GPIO_FLAGS_MODE_MASK) == GPIO_MODE_OUT)
    {
      if ((gpiodesc & GPIO_FLAGS_SPEED_MASK) == GPIO_SPEED_LOW)
        {
          val |= GPIO_MODE_OUT2MHZ << line;
        }
      else if ((gpiodesc & GPIO_FLAGS_SPEED_MASK) == GPIO_SPEED_MED)
        {
          val |= GPIO_MODE_OUT10MHZ << line;
        }
      else if ((gpiodesc & GPIO_FLAGS_SPEED_MASK) == GPIO_SPEED_HIGH)
        {
          val |= GPIO_MODE_OUT50MHZ << line;
        }

     /* set output type */

      if ((gpiodesc & GPIO_FLAGS_TYPE_MASK) == GPIO_TYPE_OD)
        {
          val |= GPIO_CNF_OD << line;
        }

    }

  else if ((gpiodesc & GPIO_FLAGS_MODE_MASK) == GPIO_MODE_ALT)
    {
      val |= GPIO_CNF_ALT << line;

     /* set output type */

      if ((gpiodesc & GPIO_FLAGS_TYPE_MASK) == GPIO_TYPE_OD)
        {
          val |= GPIO_CNF_OD << line;
        }

    }

  else if ((gpiodesc & GPIO_FLAGS_MODE_MASK) == GPIO_MODE_ANALOG)
    {
      val |= GPIO_CNF_ANALOG << line;
    }

  stm32f1_gpio_putreg(base, reg, val);
}

/*----------------------------------------------------------------------------*/
void stm32f1_gpio_write(uint32_t gpio, int state)
{
  uint32_t base,reg,val;
  uint32_t line = (gpio & GPIO_FLAGS_LINE_MASK) >> GPIO_FLAGS_LINE_SHIFT;
  uint32_t port = (gpio & GPIO_FLAGS_PORT_MASK) >> GPIO_FLAGS_PORT_SHIFT;
  if (port >= STM32F1_PORTCOUNT)
    {
      return;
    }
  base = g_stm32f1_gpioaddr[port];
  if (base==0)
    {
      return;
    }
  if (state)
    {
      stm32f1_gpio_putreg(base, STM32F1_GPIO_BSRR, 1 << line);
    }
  else
    {
      stm32f1_gpio_putreg(base, STM32F1_GPIO_BRR, 1 << line);
    }

}

