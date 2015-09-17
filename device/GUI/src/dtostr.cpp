#include "dtostr.h"

using namespace STR;

static char *STR::Reverse (char *str)
{
  char *j;
  int32_t c;
 
  j = str + strlen(str) - 1;
  while(str < j) {
    c = *str;
    *str++ = *j;
    *j-- = c;
  }	
	return j;	
}

char *STR::itoa (int32_t val, char *str, uint32_t base)
{
  int32_t i, sign;
 
  if ((sign = val) < 0)              /* record sign */
      val = -val;                    /* make n positive */
  i = 0;
  do {                               /* generate digits in reverse order */
      str[i++] = val % base + '0';   /* get next digit */
  } while ((val /= base) > 0);       /* delete it */
  if (sign < 0)
      str[i++] = '-';
  str[i] = '\0';
  
  return Reverse(str);	
}


