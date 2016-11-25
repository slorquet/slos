#include <stdint.h>

static uint32_t g_clock;

void stm32l4_clock_default(void)
{
    g_clock = 16000000;
}

uint32_t stm32l4_clock_get(void)
{
    return g_clock;
}
