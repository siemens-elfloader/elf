#include "..\inc\swilib.h"
#include "urlwork.h"

void urlescape(char *out, const char *source)
{
  const char * h = "0123456789abcdef";
  int c;
  while((c =*source++)!=0)
  {
    if ('a' <= c && c <= 'z'
	|| 'A' <= c && c <= 'Z'
	  || '0' <= c && c <= '9'
	    /*|| c == '-' */|| c == '_' || c == '.'
	      )
      *out++= c;
    else 
//      if( c == ' ' )
//	*out++= '+';
//      else 
      {
	*out++= '%';
	*out++= h[c >> 4];
	*out++= h[c & 0x0f];
      }
  }
  *out=0;
}

void urlcat(char *out, const char *source)
{
  urlescape(out+strlen(out),source);
}

