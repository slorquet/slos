#include <stdint.h>
#include <stddef.h>
#include <config.h>

#include "armv7m.h"
#include "bits/stm32l4_periphs.h"
#include "bits/stm32l4_gpio.h"
#include "bits/stm32l4_rcc.h"
#include "stm32l4_gpio.h"

/*==============================================================================
 * Definitions
 *==============================================================================
 */

/*==============================================================================
 * Types
 *==============================================================================
 */

struct stm32l4_gpio_s {
    uint32_t base;
    uint32_t ckenreg;
    uint32_t ckenbit;
};

/*==============================================================================
 * Function Prototypes
 *==============================================================================
 */

/*==============================================================================
 * Variables and constants
 *==============================================================================
 */

#ifdef CONFIG_STM32L4_GPIOA
static const struct stm32l4_gpio_s g_stm32l4_gpioa =
{
  .base    = STM32L4_REGBASE_GPIOA,
  .ckenreg = STM32L4_RCC_AHB2ENR,
  .ckenbit = RCC_AHB2ENR_GPIOAEN
};
#endif

#ifdef CONFIG_STM32L4_GPIOB
static const struct stm32l4_gpio_s g_stm32l4_gpiob =
{
  .base    = STM32L4_REGBASE_GPIOB,
  .ckenreg = STM32L4_RCC_AHB2ENR,
  .ckenbit = RCC_AHB2ENR_GPIOBEN
};
#endif

#ifdef CONFIG_STM32L4_GPIOC
static const struct stm32l4_gpio_s g_stm32l4_gpioc =
{
  .base    = STM32L4_REGBASE_GPIOC,
  .ckenreg = STM32L4_RCC_AHB2ENR,
  .ckenbit = RCC_AHB2ENR_GPIOCEN
};
#endif

#ifdef CONFIG_STM32L4_GPIOD
static const struct stm32l4_gpio_s g_stm32l4_gpiod =
{
  .base    = STM32L4_REGBASE_GPIOD,
  .ckenreg = STM32L4_RCC_AHB2ENR,
  .ckenbit = RCC_AHB2ENR_GPIODEN
};
#endif

#ifdef CONFIG_STM32L4_GPIOE
static const struct stm32l4_gpio_s g_stm32l4_gpioe =
{
  .base    = STM32L4_REGBASE_GPIOE,
  .ckenreg = STM32L4_RCC_AHB2ENR,
  .ckenbit = RCC_AHB2ENR_GPIOEEN
};
#endif

#ifdef CONFIG_STM32L4_GPIOF
static const struct stm32l4_gpio_s g_stm32l4_gpiof =
{
  .base    = STM32L4_REGBASE_GPIOF,
  .ckenreg = STM32L4_RCC_AHB2ENR,
  .ckenbit = RCC_AHB2ENR_GPIOFEN
};
#endif

#ifdef CONFIG_STM32L4_GPIOG
static const struct stm32l4_gpio_s g_stm32l4_gpiog =
{
  .base    = STM32L4_REGBASE_GPIOG,
  .ckenreg = STM32L4_RCC_AHB2ENR,
  .ckenbit = RCC_AHB2ENR_GPIOGEN
};
#endif

#ifdef CONFIG_STM32L4_GPIOH
static const struct stm32l4_gpio_s g_stm32l4_gpioh =
{
  .base    = STM32L4_REGBASE_GPIOH,
  .ckenreg = STM32L4_RCC_AHB2ENR,
  .ckenbit = RCC_AHB2ENR_GPIOHEN
};
#endif

static const struct stm32l4_gpio_s *g_stm32l4_gpios[] = {
#ifdef CONFIG_STM32L4_GPIOA
  &g_stm32l4_gpioa,
#else
  NULL,
#endif
#ifdef CONFIG_STM32L4_GPIOB
  &g_stm32l4_gpiob,
#else
  NULL,
#endif
#ifdef CONFIG_STM32L4_GPIOC
  &g_stm32l4_gpioc,
#else
  NULL,
#endif
#ifdef CONFIG_STM32L4_GPIOD
  &g_stm32l4_gpiod,
#else
  NULL,
#endif
#ifdef CONFIG_STM32L4_GPIOE
  &g_stm32l4_gpioe,
#else
  NULL,
#endif
#ifdef CONFIG_STM32L4_GPIOF
  &g_stm32l4_gpiof,
#else
  NULL,
#endif
#ifdef CONFIG_STM32L4_GPIOG
  &g_stm32l4_gpiog,
#else
  NULL,
#endif
#ifdef CONFIG_STM32L4_GPIOH
  &g_stm32l4_gpioh,
#else
  NULL,
#endif
};

/*==============================================================================
 * Functions
 *==============================================================================
 */

/*----------------------------------------------------------------------------*/
static inline void stm32l4_gpio_putreg(const struct stm32l4_gpio_s *gpio, uint32_t regoff, uint32_t value)
{
  putreg32(gpio->base + regoff, value);
}

/*----------------------------------------------------------------------------*/
static inline uint32_t stm32l4_gpio_getreg(const struct stm32l4_gpio_s *gpio, uint32_t regoff)
{
  return getreg32(gpio->base + regoff);
}

/*----------------------------------------------------------------------------*/
static inline void stm32l4_gpio_updatereg(const struct stm32l4_gpio_s *gpio, uint32_t regoff, uint32_t set, uint32_t clr)
{
  updatereg32(gpio->base + regoff, set, clr);
}

/*----------------------------------------------------------------------------*/
void stm32l4_gpio_init(uint32_t gpiodesc)
{
  uint32_t reg,val;
  const struct stm32l4_gpio_s *gpio;
  uint32_t line = (gpiodesc & GPIO_FLAGS_LINE_MASK) >> GPIO_FLAGS_LINE_SHIFT;
  uint32_t port = (gpiodesc & GPIO_FLAGS_PORT_MASK) >> GPIO_FLAGS_PORT_SHIFT;

  if (port >= (sizeof(g_stm32l4_gpios)/sizeof(g_stm32l4_gpios[0])))
    {
      return; /* Port does not exist */
    }

  gpio = g_stm32l4_gpios[port];
  if (!gpio)
    {
      return; /* This port is not implemented. */
    }

  /* Enable clock to GPIO peripheral */

  updatereg32(STM32L4_REGBASE_RCC + gpio->ckenreg, gpio->ckenbit, 0);

  /* Configure 1-bit ports */

  val = (gpiodesc & GPIO_FLAGS_TYPE_MASK) >> GPIO_FLAGS_TYPE_SHIFT;
  stm32l4_gpio_updatereg(gpio, STM32L4_GPIO_OTYPER, val<<line, 1<<line);
  
  /* Configure 2-bit ports */

  line += line;
  
  val = (gpiodesc & GPIO_FLAGS_MODE_MASK) >> GPIO_FLAGS_MODE_SHIFT;
  stm32l4_gpio_updatereg(gpio, STM32L4_GPIO_MODER, val<<line, 3<<line);
  
  val = (gpiodesc & GPIO_FLAGS_SPEED_MASK) >> GPIO_FLAGS_SPEED_SHIFT;
  stm32l4_gpio_updatereg(gpio, STM32L4_GPIO_OSPEEDER, val<<line, 3<<line);

  val = (gpiodesc & GPIO_FLAGS_PULL_MASK) >> GPIO_FLAGS_PULL_SHIFT;
  stm32l4_gpio_updatereg(gpio, STM32L4_GPIO_PUPDR, val<<line, 3<<line);

  /* Configure 4-bit ports */

  line += line;
  
  /* Offset 20 AFRL (for lines 0- 7) */
  /* Offset 24 AFRH (for lines 8-15) */

  val = (gpiodesc & GPIO_FLAGS_ALT_MASK) >> GPIO_FLAGS_ALT_SHIFT;
  if (line < (8<<2))
    {
      stm32l4_gpio_updatereg(gpio, STM32L4_GPIO_AFRL, val<<line, 15<<line);
    }
  else
    {
      line -= 32;
      stm32l4_gpio_updatereg(gpio, STM32L4_GPIO_AFRH, val<<line, 15<<line);
    }
}

/*----------------------------------------------------------------------------*/
void stm32l4_gpio_write(uint32_t gpiodesc, int state)
{
  const struct stm32l4_gpio_s *gpio;
  uint32_t line = (gpiodesc & GPIO_FLAGS_LINE_MASK) >> GPIO_FLAGS_LINE_SHIFT;
  uint32_t port = (gpiodesc & GPIO_FLAGS_PORT_MASK) >> GPIO_FLAGS_PORT_SHIFT;

  if (port >= (sizeof(g_stm32l4_gpios)/sizeof(g_stm32l4_gpios[0])))
    {
      return; /* Port does not exist */
    }

  gpio = g_stm32l4_gpios[port];
  if (!gpio)
    {
      return; /* This port is not implemented. */
    }

  //get port base address
  if (!state)
    {
      line += 16; //access BR instead of BS
    }
  stm32l4_gpio_putreg(gpio, STM32L4_GPIO_BSRR, 1<<line);
}

