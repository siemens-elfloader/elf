#include "..\inc\swilib.h"
#include "base64.h"


static size_t _sf_b64_len = 0;
static unsigned char _sf_uc_ib[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/==";


/*
 * Encode the given data using Base64 encoding.
 */
char *
base64_encode(const void *data, int *size)
{
  char *output;
  char *ou;
  const char *p=(const char *)data;
  int original_size = size?*size:strlen((const char *)data);
  const void *dte= (const char *)data + original_size;
  int malloc_len;
  int nc = 0;
  
  if(data == NULL)
    return NULL;
  
  malloc_len = + (4 * (original_size + 2) / 3) + 1;
  ou=output=malloc(malloc_len);
  
  if(output == NULL)
    return NULL;
  
  while((char *)dte - (char *)p >= 3) 
  {
    *ou = _sf_uc_ib[ *p >> 2 ];
    ou[1] = _sf_uc_ib[ ((*p & 0x03) << 4) | (p[1] >> 4) ];
    ou[2] = _sf_uc_ib[ ((p[1] & 0x0F) << 2) | (p[2] >> 6) ];
    ou[3] = _sf_uc_ib[ p[2] & 0x3F ];
    
    p+=3;
    ou+=4;
    
    nc+=4;
    
  }
  
  if((char *)dte - (char *)p == 2) 
  {
    *ou++ = _sf_uc_ib[ *p >> 2 ];
    *ou++ = _sf_uc_ib[ ((*p & 0x03) << 4) | (p[1] >> 4) ];
    *ou++ = _sf_uc_ib[ ((p[1] & 0x0F) << 2) ];
    *ou++ = '=';
  }
  
  else if((char *)dte - (char *)p == 1)
  {
    *ou++ = _sf_uc_ib[ *p >> 2 ];
    *ou++ = _sf_uc_ib[ ((*p & 0x03) << 4) ];
    *ou++ = '=';
    *ou++ = '=';
  }
  
  *ou = '\0';

  _sf_b64_len = (ou - output);
  if(size) *size = _sf_b64_len; 
  return (output);
}
