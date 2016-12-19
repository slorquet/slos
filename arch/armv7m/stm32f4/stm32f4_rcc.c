#include <stdint.h>

static uint32_t g_stm32f4_clock;

/*============================================================================*/
void stm32f4_clock_default(void)
{
    g_stm32f4_clock = 16000000;
}

/*============================================================================*/
uint32_t stm32f4_clock_get(void)
{
    return g_stm32f4_clock;
}
