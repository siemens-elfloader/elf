#include "include.h"

//SDLIST *sdltop=0;

char sms_dat[128];
char main_folder[128];
//char ems_admin_dat[128];

const int softkeys[]={0,1,2};
const int minus11=-11;

SOFTKEY_DESC sel_menu_sk[]=
{
  {0x0018,0x0000,(int)LGP_NULL},
  {0x0001,0x0000,(int)LGP_NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB sel_menu_skt=
{
  sel_menu_sk,0
};



