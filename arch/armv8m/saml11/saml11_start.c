#include <config.h>

#include "saml11_clock.h"
#include "saml11_uart.h"

void chip_start(void)
{
  saml11_clock_setup();

  saml11_uart_earlysetup();
}

