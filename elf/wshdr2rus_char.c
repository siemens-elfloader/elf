///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////WS_2_RUSCHAR-перевод типа WSHDR в голый char с сохранением русских букв (кирилицы)//////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

#define wslen(ws) ws->wsbody[0]
#define EZXML_BUFSIZE 1024

char *utf16_to_utf8(char **s, size_t *len)
{
    char *u;
    size_t l = 0, sl, max = *len;
    long c, c2;
    int b, be = 0;
    if (be == -1) return NULL; 
    u = malloc(max); zeromem(u, max);
        for (sl = 2; sl <= *len ; sl += 2) {
      c = (be) ? ((long)(*s)[sl] << 8) | (*s)[sl + 1] : 
	((long)(*s)[sl + 1] << 8) | (*s)[sl];  
      if (c >= 0xD800 && c <= 0xDFFF && (sl += 2) < *len - 1) { 
	c2 = (be) ? ((long)(*s)[sl] << 8) | (*s)[sl + 1] : 
	  ((long)(*s)[sl + 1] << 8) | (*s)[sl];  
            c = (((c & 0x3FF) << 10) | (c2 & 0x3FF)) + 0x10000;
        }
        while (l + 6 > max) u = realloc(u, max += EZXML_BUFSIZE);
        if (c < 0x80) u[l++] = c; 
        else { 
	  for (b = 0, c2 = c; c2; c2 /= 2) b++; 
	  b = (b - 2) / 5; 
	  u[l++] = (0xFF << (7 - b)) | (c >> (6 * b)); 
	  while (b) u[l++] = 0x80 | ((c >> (6 * --b)) & 0x3F); 
        }
    }
    *len = l;
    u = realloc(u, l+1);
    return u;
}

void utf82win(char*d,const char *s)
{
  for (; *s; s+=2)
  {
    unsigned char ub = *s, lb = *(s+1);
    if (ub == 208)
      if (lb != 0x81)
        {*d = lb + 48; d++;}
      else
        {*d = 'и'; d++;}

    if (ub == 209)
      if (lb != 0x91)
        {*d = lb + 112; d++;}
      else
        {*d = '¬'; d++;}

    if ((ub != 208) && (ub != 209) && (lb != 91) && (lb != 81))
    {
      *d = ub;
      d++;
      s--;
    }
  }
  *d = 0;
}
char *ws2utf8(WSHDR *ws)
{
   size_t len = wslen(ws)*2;
   char* body =  utf16_to_utf8((char**)ws,&len);
   body[len]='\0';
   return body;
}





////////////ПРИМЕР :-) /////////////////
char xmsg[1024];
utf82win(xmsg,(const char *)ws2utf8(ec.pWS));
ShowMSG(1,(int)xmsg);