#include <stdint.h>

#include <bits/stm32f1_periphs.h>
#include <bits/stm32f1_rcc.h>

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
