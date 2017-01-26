#ifndef __ARCH__ARMV6M__STM32F1__STM32F1__GPIO__H__
#define __ARCH__ARMV6M__STM32F1__STM32F1__GPIO__H__

#include <stdint.h>

/* format for flags
  offset size name
   0     4    LINE   (0-15)
   4     4    PORT   (0- 7)
   8     4    Reserved
  12     2    MODE   (0- 3) i-o-alt-ana
  14     2    PULL   (0- 2) (out) none-up-down
  16     2    SPEED  (0- 3) (out) low-mid-hi
  18     1    TYPE   (0- 1) (out) od-pp
  19     1    STATE  (0- 1) initial state
*/

enum {
  GPIO_FLAGS_LINE_SHIFT  = 0,
  GPIO_FLAGS_PORT_SHIFT  = 4,
  GPIO_FLAGS_MODE_SHIFT  = 12,
  GPIO_FLAGS_PULL_SHIFT  = 14,
  GPIO_FLAGS_SPEED_SHIFT = 16,
  GPIO_FLAGS_TYPE_SHIFT  = 18,
  GPIO_FLAGS_STATE_SHIFT = 19,
};

enum {
  GPIO_FLAGS_PORT_MASK  = 0xF << GPIO_FLAGS_PORT_SHIFT,
  GPIO_PORT_A           =   0 << GPIO_FLAGS_PORT_SHIFT,
  GPIO_PORT_B           =   1 << GPIO_FLAGS_PORT_SHIFT,
  GPIO_PORT_C           =   2 << GPIO_FLAGS_PORT_SHIFT,
  GPIO_PORT_D           =   3 << GPIO_FLAGS_PORT_SHIFT,
  GPIO_PORT_E           =   4 << GPIO_FLAGS_PORT_SHIFT,
  GPIO_PORT_F           =   5 << GPIO_FLAGS_PORT_SHIFT,
  GPIO_PORT_G           =   6 << GPIO_FLAGS_PORT_SHIFT,
};

enum {
  GPIO_FLAGS_LINE_MASK  = 0xF << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_0            =   0 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_1            =   1 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_2            =   2 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_3            =   3 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_4            =   4 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_5            =   5 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_6            =   6 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_7            =   7 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_8            =   8 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_9            =   9 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_10           =  10 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_11           =  11 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_12           =  12 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_13           =  13 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_14           =  14 << GPIO_FLAGS_LINE_SHIFT,
  GPIO_PIN_15           =  15 << GPIO_FLAGS_LINE_SHIFT,
};

enum {
  GPIO_FLAGS_MODE_MASK  = 0x3 << GPIO_FLAGS_MODE_SHIFT,
  GPIO_MODE_IN          =   0 << GPIO_FLAGS_MODE_SHIFT, /* Also for alt inputs */
  GPIO_MODE_OUT         =   1 << GPIO_FLAGS_MODE_SHIFT,
  GPIO_MODE_ALT         =   2 << GPIO_FLAGS_MODE_SHIFT, /* Alt outputs */
  GPIO_MODE_ANALOG      =   3 << GPIO_FLAGS_MODE_SHIFT,
};

enum {
  GPIO_FLAGS_PULL_MASK  = 0x3 << GPIO_FLAGS_PULL_SHIFT,
  GPIO_PULL_NONE        =   0 << GPIO_FLAGS_PULL_SHIFT,
  GPIO_PULL_UP          =   1 << GPIO_FLAGS_PULL_SHIFT,
  GPIO_PULL_DOWN        =   2 << GPIO_FLAGS_PULL_SHIFT,
};

enum {
  GPIO_FLAGS_SPEED_MASK = 0x3 << GPIO_FLAGS_SPEED_SHIFT,
  GPIO_SPEED_LOW        =   0 << GPIO_FLAGS_SPEED_SHIFT,
  GPIO_SPEED_MED        =   1 << GPIO_FLAGS_SPEED_SHIFT,
  GPIO_SPEED_HIGH       =   2 << GPIO_FLAGS_SPEED_SHIFT,
};

enum {
  GPIO_FLAGS_TYPE_MASK  = 0x1 << GPIO_FLAGS_TYPE_SHIFT,
  GPIO_TYPE_PP          =   0 << GPIO_FLAGS_TYPE_SHIFT,
  GPIO_TYPE_OD          =   1 << GPIO_FLAGS_TYPE_SHIFT,
};

enum {
  GPIO_FLAGS_STATE_MASK = 0x1 << GPIO_FLAGS_STATE_SHIFT,
  GPIO_STATE_CLEAR      =   0 << GPIO_FLAGS_STATE_SHIFT,
  GPIO_STATE_SET        =   1 << GPIO_FLAGS_STATE_SHIFT,
};

void stm32f1_gpio_init(uint32_t descriptor);
void stm32f1_gpio_write(uint32_t gpio, int state);

#endif /* __ARCH__ARMV6M__STM32F1__STM32F1__GPIO__H__ */
