#include "swilib.h"
#include "ussd_process.h"
#include "xtask_ipc.h"
#define IMSI_DATA_BYTE_LEN  (9)
extern int draw_body;
//IPC

IPC_REQ gipc;

int CASH_SIZE=0;
extern int    eya;
extern long  strtol (const char *nptr,char **endptr,int base);
char cashfname[128];



static volatile int ussdreq_sended;
static volatile int locked;




int char16to8z(int c)
{
  if (c<0x400) return (c);
  c-=0x400;
  if (c<16)
  {
    if (c==1) c=0;  //big_yo
    else if (c==4) c=2;  //big_ye
    else if (c==6) c=10; //big_i
    else return (c);
  }
  else if (c>79)
  {
    if (c==0x51) c=16; //small_yo
    else if (c==0x54) c=18; //small_ye
    else if (c==0x56) c=11; //small_i
    else if (c==0x57) c=23; //small_yi
    else return (c);
  }
  else c+=8;
  c+=168;
  return (c);
}

#define IPC1_XTASK_NAME "XTask"
#define IPC1_XTASK_IDLE 1
#define IPC1_XTASK_SHOW_CSM 2
#define IPC1_XTASK_LOCK_SHOW 3
#define IPC1_XTASK_UNLOCK_SHOW 4
const char ipc1_my_name[32]="MD_TouchFlo";

void _lock(void)
{
  if (locked) return;
  gipc.name_to=IPC1_XTASK_NAME;
  gipc.name_from=ipc1_my_name;
  gipc.data=0;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_LOCK_SHOW,&gipc);
  locked=1;
}

void _unlock(void)
{
  if (!locked) return;
  gipc.name_to=IPC1_XTASK_NAME;
  gipc.name_from=ipc1_my_name;
  gipc.data=0;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_UNLOCK_SHOW,&gipc);
  locked=0;
}


extern int MENU_GUI_ID;// ИД гуя меню
extern int show_ussd; // отображать всплывающие сообщения
extern WSHDR *ussdws;
int ProcessUSSD(CSM_RAM* data, GBS_USSD_MSG *msg)
{


  int len;
  char *s;
  int i=0;
  #define ussdreqgui_id (((int *)data)[DISPLACE_OF_USSDREQGUI_ID/4])

//  if (!ENA_CASHTRACE) return 0;



  len=msg->pkt_length;

  if (len>240) len=240;
  GSMTXT_Decode(ussdws,msg->pkt,len,msg->encoding_type,(void*(*)(int))malloc_adr(),(void(*)(void))mfree_adr());
  if ((len=ussdws->wsbody[0]))
  {
    zeromem(s=malloc(len+3),len+3);
    len=0;
    while(len<ussdws->wsbody[0])
    {
      int c=ussdws->wsbody[len+1];
      c=char16to8z(c);
      if (c<32) c='?';
      s[len++]=c;
    }
    i=1;
 //   s[len++]=13;
 //   s[len++]=10;
  }

  if (ussdreqgui_id)
  {
    GeneralFunc_flag1(ussdreqgui_id,0);
    ussdreqgui_id=0;
  }
  if (msg->msg==MSG_AUTOUSSD_RX)
  {
    if (!i) return (0);
    SendAutoUSSDack();
  }
  FreeGSMTXTpkt(msg->pkt);
     show_ussd = 1;
 draw_body = 1;DirectRedrawGUI_ID(MENU_GUI_ID);
  return 1;

}



void imsi2str(char *imsi, char *str)
{
  unsigned int c, c1;
  int j, m;
  m=0;
  j=0;
  while(j<IMSI_DATA_BYTE_LEN)
  {
    if (m&1) {c1=c>>4; j++;}
    else c1=(c=imsi[j])&0x0F;
    *str++=c1+'0';
    m++;
  }
  *str=0;
}
