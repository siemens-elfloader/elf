
char msg[24];


#pragma swi_number=22
__swi __arm int sprintf(char *buf, const char *str, ...);


__arm char *empty_func()
{
  sprintf(msg, "Fuck: %d!", 3);
  return msg;
}
