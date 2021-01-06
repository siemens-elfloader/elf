#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <string.h>
#include <conio.h>
#include <iostream>
#include <winsock2.h>
#include "packets.h"
#include "login.h"

FLAP flap,flap3;
FLAP_PACKET packet;
void Login()
{
recv(sock,(char*)&flap,sizeof(FLAP),0);
printf("Sign: 0x%x Len:%d Channel:%d Seq:%d\n",flap.Sign,flap.Len,flap.ChID,flap.SEQ);
char *data=new char((int)flap.Len+1);
recv(sock,(char*)&data,flap.Len,0);
if((int)data==0x1000000)
{
recv(sock,(char*)&flap3,sizeof(FLAP),0);
printf("Sign: 0x%x Len:%d Channel:%d Seq:%d\n",flap3.Sign,flap3.Len,flap3.ChID,flap3.SEQ);
}

}