#include <stdint.h>

static uint32_t g_clock;

void stm32l4_clock_setup(void)
{
    g_clock = 4000000;
}

uint32_t stm32l4_clock_get(void)
{
    return g_clock;
}
