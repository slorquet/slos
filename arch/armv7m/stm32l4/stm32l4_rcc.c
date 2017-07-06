#include <stdint.h>
#include <stdbool.h>
#include "stm32l4_rcc.h"
#include "bits/stm32l4_rcc.h"

static uint32_t g_clock;

void stm32l4_clock_setup(void)
{
    g_clock = 4000000;
}

uint32_t stm32l4_clock_get(void)
{
    return g_clock;
}

void stm32l4_clock_setup(void);

/* System clock tree management */

struct stm32l4_clocks_s * stm32l4_clock_getinfo(void)
{
}

bool stm32l4_ahbprescaler(uint32_t prescaler)
{
  return false;
}

bool stm32l4_apb1prescaler(uint32_t prescaler)
{
  return false;
}

bool stm32l4_apb2prescaler(uint32_t prescaler)
{
  return false;
}

void stm32l4_clock_enablebkp(void)
{
}

/* Individual clocks enable */

bool stm32l4_clock_lse_enable(bool state)
{
  return false;
}

bool stm32l4_clock_lse_ready(void)
{
  return false;
}

bool stm32l4_clock_hse_enable(bool state)
{
  return false;
}

bool stm32l4_clock_hse_ready(void)
{
  return false;
}

bool stm32l4_clock_hsi_ready(void)
{
  return false;
}

bool stm32l4_clock_lsi_ready(void)
{
  return false;
}


/* Clock selection for configurable peripherals */

bool stm32l4_clock_rtc(int rtcclocksource)
{
  return false;
}

bool stm32l4_clock_48M(int femclocksource)
{
  return false;
}

bool stm32l4_clock_adc(int adcclocksource)
{
  return false;
}

/* Clock change hooks management */

bool stm32l4_clock_registerhook(stm32l4_clockhook_f hook)
{
  return false;
}


