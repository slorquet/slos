#include <stdlib.h>

void ultoa(char *buf, int nbuf, unsigned long value, int radix)
{
  int pos=0;
  int len,i;

  if(nbuf<=1) return; //need toom to store final zero at least

  nbuf--; //Compute how many chars can be stored excluding final zero

  if (radix < 2 || radix > 36)
    {
      buf[0] = 0;
      return;
    }

  // Radix okay

  if (value==0)
    {
      if(nbuf<1) return; //need room to store one char
      buf[pos++] = '0'; //Special case: Next code will return an empty string for value=0
      buf[pos++] = 0;
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

