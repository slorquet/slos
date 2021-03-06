#ifndef _ARCH_ARMV7M_STM32L4_STM32L4_GPIO_H_
#define _ARCH_ARMV7M_STM32L4_STM32L4_GPIO_H_

#include <stdint.h>

/* format for flags
  offset size name
   0     4    LINE   (0-15)
   4     4    PORT   (0-10)
   8     4    ALT    (0-15)
  12     2    MODE   (0- 3)
  14     2    PULL   (0- 2)
  16     2    SPEED  (0- 3)
  18     1    TYPE   (0- 1)
*/

#define GPIO_PORT_COUNT 11

enum {
  GPIO_FLAGS_LINE_SHIFT  = 0,
  GPIO_FLAGS_PORT_SHIFT  = 4,
  GPIO_FLAGS_ALT_SHIFT   = 8,
  GPIO_FLAGS_MODE_SHIFT  = 12,
  GPIO_FLAGS_PULL_SHIFT  = 14,
  GPIO_FLAGS_SPEED_SHIFT = 16,
  GPIO_FLAGS_TYPE_SHIFT  = 18,
};

enum {
  GPIO_FLAGS_PORT_MASK  = 0xF << GPIO_FLAGS_PORT_SHIFT,
  GPIO_FLAGS_ALT_MASK   = 0xF << GPIO_FLAGS_ALT_SHIFT,
  GPIO_FLAGS_MODE_MASK  = 0x3 << GPIO_FLAGS_MODE_SHIFT,
  GPIO_FLAGS_PULL_MASK  = 0x3 << GPIO_FLAGS_PULL_SHIFT,
  GPIO_FLAGS_SPEED_MASK = 0x3 << GPIO_FLAGS_SPEED_SHIFT,
  GPIO_FLAGS_TYPE_MASK  = 0x1 << GPIO_FLAGS_TYPE_SHIFT,
  GPIO_FLAGS_LINE_MASK  = 0xF << GPIO_FLAGS_LINE_SHIFT,
};

enum {
  GPIO_PIN_0 =  0 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_1 =  1 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_2 =  2 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_3 =  3 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_4 =  4 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_5 =  5 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_6 =  6 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_7 =  7 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_8 =  8 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_9 =  9 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_10= 10 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_11= 11 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_12= 12 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_13= 13 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_14= 14 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_15= 15 << GPIO_FLAGS_LINE_SHIFT,
};

enum {
  GPIO_PORT_A =  0 << GPIO_FLAGS_PORT_SHIFT,
  GPIO_PORT_B =  1 << GPIO_FLAGS_PORT_SHIFT,
  GPIO_PORT_C =  2 << GPIO_FLAGS_PORT_SHIFT,
  GPIO_PORT_D =  3 << GPIO_FLAGS_PORT_SHIFT,
  GPIO_PORT_E =  4 << GPIO_FLAGS_PORT_SHIFT,
  GPIO_PORT_F =  5 << GPIO_FLAGS_PORT_SHIFT,
  GPIO_PORT_G =  6 << GPIO_FLAGS_PORT_SHIFT,
  GPIO_PORT_H =  7 << GPIO_FLAGS_PORT_SHIFT,
  GPIO_PORT_I =  8 << GPIO_FLAGS_PORT_SHIFT,
  GPIO_PORT_J =  9 << GPIO_FLAGS_PORT_SHIFT,
  GPIO_PORT_K = 10 << GPIO_FLAGS_PORT_SHIFT,
};

enum {
    GPIO_ALT_0 =  0<<GPIO_FLAGS_ALT_SHIFT,
    GPIO_ALT_1 =  1<<GPIO_FLAGS_ALT_SHIFT,
    GPIO_ALT_2 =  2<<GPIO_FLAGS_ALT_SHIFT,
    GPIO_ALT_3 =  3<<GPIO_FLAGS_ALT_SHIFT,
    GPIO_ALT_4 =  4<<GPIO_FLAGS_ALT_SHIFT,
    GPIO_ALT_5 =  5<<GPIO_FLAGS_ALT_SHIFT,
    GPIO_ALT_6 =  6<<GPIO_FLAGS_ALT_SHIFT,
    GPIO_ALT_7 =  7<<GPIO_FLAGS_ALT_SHIFT,
    GPIO_ALT_8 =  8<<GPIO_FLAGS_ALT_SHIFT,
    GPIO_ALT_9 =  9<<GPIO_FLAGS_ALT_SHIFT,
    GPIO_ALT_10= 10<<GPIO_FLAGS_ALT_SHIFT,
    GPIO_ALT_11= 11<<GPIO_FLAGS_ALT_SHIFT,
    GPIO_ALT_12= 12<<GPIO_FLAGS_ALT_SHIFT,
    GPIO_ALT_13= 13<<GPIO_FLAGS_ALT_SHIFT,
    GPIO_ALT_14= 14<<GPIO_FLAGS_ALT_SHIFT,
    GPIO_ALT_15= 15<<GPIO_FLAGS_ALT_SHIFT,
};

enum {
    GPIO_MODE_IN     = 0<<GPIO_FLAGS_MODE_SHIFT,
    GPIO_MODE_OUT    = 1<<GPIO_FLAGS_MODE_SHIFT,
    GPIO_MODE_ALT    = 2<<GPIO_FLAGS_MODE_SHIFT,
    GPIO_MODE_ANALOG = 3<<GPIO_FLAGS_MODE_SHIFT,
};

enum {
    GPIO_PULL_NONE   = 0<<GPIO_FLAGS_PULL_SHIFT,
    GPIO_PULL_UP     = 1<<GPIO_FLAGS_PULL_SHIFT,
    GPIO_PULL_DOWN   = 2<<GPIO_FLAGS_PULL_SHIFT,
};

enum {
    GPIO_SPEED_LOW   = 0<<GPIO_FLAGS_SPEED_SHIFT,
    GPIO_SPEED_MED   = 1<<GPIO_FLAGS_SPEED_SHIFT,
    GPIO_SPEED_FAST  = 2<<GPIO_FLAGS_SPEED_SHIFT,
    GPIO_SPEED_HIGH  = 3<<GPIO_FLAGS_SPEED_SHIFT,
};

enum {
    GPIO_TYPE_PP     = 0<<GPIO_FLAGS_TYPE_SHIFT,
    GPIO_TYPE_OD     = 1<<GPIO_FLAGS_TYPE_SHIFT,
};

void stm32l4_gpio_init(uint32_t gpiodesc);
void stm32l4_gpio_write(uint32_t gpio, int state);
int stm32l4_gpio_read(uint32_t gpiodesc);

#endif //GPIO
