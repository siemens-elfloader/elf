#include "..\inc\swilib.h"
#include "..\SerialLib\serial.h"
#include "serial_dbg.h"

char _is_com_init=0;

void tx_str(char *str)
{
  int i = GetAccessoryType();
//  char q[20];
//  sprintf(q,"Acc=%d", i);
//  ShowMSG(1,(int)q);
  if(i!=15)return;
  if(!_is_com_init)
  {
    SetSpeed(1);
    _is_com_init = 1;
  }
  int len = strlen(str);
  for (int i=0; i<len; i++)
    Tx_byte(str[i]);
}

