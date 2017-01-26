#include <stdbool.h>
#include <slos/stdio.h>

/*----------------------------------------------------------------------------*/
/* This is the common routine for all printf-like functions */
int streamprintf(const struct printf_stream_s *stream, const char *fmt, va_list ap)
{
  int written    = 0;  /* Nbr of chars written to stream */
  int base       = 10; /* Numeric base */
  bool ucase     = false; /* Uppercase output */
  bool leading   = false; /* Print leading zeros */
  int  width     = 0;     /* field width */
  bool longarg   = false; /* arg is long int */
  bool notsigned = false; /* interpret arg as unsigned */
  unsigned long arg;     /* integer to be printed */
  char nbuf[10];

  while(*fmt)
    {
      char ch = *fmt++;

      /* Easy output for normal chars */

      if(ch!='%')
        {
          stream->putchar(ch,stream->context);
          written++;
          continue;
        }

      /* Get format : 0?[0-9]*l?[dxXpu] */

      ch = *fmt++;

      /* If zero, set leading zero flag */

      if(ch=='0')
        {
          leading=true;
          ch = *fmt++;
        }

      /* get field width */

      while(ch>='0' && ch <='9')
        {
          width *= 10;
          width += ch - '0';
        }

      /* test for long format arg */

      if(ch=='l')
        {
          longarg=true;
          ch = *fmt++;
        }

      switch (ch)
        {
          case 's':
            {
              char *str = va_arg(ap, char*);
              if (!str)
                {
                  str = "(null)";
                }
              written += stream->puts(str, stream->context);
              continue;
            }
          case '%': stream->putchar('%', stream->context); written++; continue;
          default: continue;

          case 'X': ucase = true;
          case 'p':
          case 'x': base=16;
          case 'u': notsigned = true;
          case 'd':
            if(longarg)
              {
                arg = (unsigned long)va_arg(ap,long);
              }
            else
              {
                arg = (unsigned long)va_arg(ap,int);
              }
          /* output the sign */
          if(!notsigned)
            {
              if( (signed long)arg < 0)
                {
                  stream->putchar('-',stream->context);
                  written++;
                  arg = -arg;
                }
            }

          /* print value */
          ltoa(nbuf, 10, arg, base);
          if(ucase)
            {
              int i;
              for (i=0; i < sizeof(nbuf)-1; i++)
                {
                  if (nbuf[i]>='a' && nbuf[i]<='z') nbuf[i] -= ('a'-'A');
                }
            }
          written += stream->puts(nbuf, stream->context);
        }
    }

  return written;
}
