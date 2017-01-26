#include <stdlib.h>

void ltoa(char *buf, int nbuf, unsigned long value, int radix)
{
  int pos=0;
  int len,i;

  if (radix < 2 || radix > 36)
    {
      buf[pos] = 0;
      return;
    }

  while(value > 0)
    {
      int digit = value % radix;
      value = value / radix;

      if(digit<10)
        {
          digit += '0';
        }
      else
        {
          digit += 'a' - 10;
        }

      buf[pos++] = digit;
      if(pos==nbuf)
        {
          break;
        }
    }

  buf[pos] = 0;


  /* Now swap */
  len = pos >> 1;

  for(i=0;i<len;i++)
    {
      char tmp;
      tmp          = buf[pos-1-i];
      buf[pos-1-i] = buf[i];
      buf[i]       = tmp;
    }
}

