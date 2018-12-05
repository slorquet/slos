#include "config.h"

extern int main(void);

void os_start(void)
{
  int ret;
  ret = main();
  while(1);
}

