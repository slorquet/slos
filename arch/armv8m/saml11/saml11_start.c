#include <config.h>

#include "saml11_uart.h"
#include "saml11_flash.h"

void chip_start(void)
{
  saml11_clock_setup();

  saml11_uart_earlysetup();

#ifdef CONFIG_SAML11_FLASH
  saml11_flash_init();
#endif

}

