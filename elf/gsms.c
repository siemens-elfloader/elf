#include "..\inc\swilib.h"

char txt[]="upor";
char buf[16384];
int pbuf=0;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

int connect_state=0;

int sock=-1;

extern void kill_data(void *p, void (*func_p)(void *));

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void create_connect(void)
{
  SOCK_ADDR sa;
  //Устанавливаем соединение
  connect_state=0;
  sock=socket(1,1,0);
  if (sock!=-1)
  {
    sa.family=1;
    sa.port=htons(80);
    sa.ip=htonl(IP_ADDR(62,149,13,117));
    if (connect(sock,&sa,sizeof(sa))!=-1)
    {
      connect_state=1;
      REDRAW();
    }
    else
      closesocket(sock);
  }
}

int DNR_ID;
int DNR_TRIES;
const char host[]="cbsie.dyndns.info"; //BCB53AD4

void ViewDNRresult(int ***p)
{
  char ss[100];
  if (p)
  {
    if (p[3])
    {
      DNR_TRIES=0;
      sprintf(ss,"%08X",p[3][0][0]);
      LockSched();
      ShowMSG(1,(int)ss);
      UnlockSched();
    }	
  }
  else
  {
    DNR_TRIES--;
    LockSched();
    ShowMSG(1,(int)"Host not found!");
    UnlockSched();
  }
}

void ask_dns(void)
{
  int id;
  int ***p_res;
  char ss[100];
  int err=async_gethostbyname(host,&p_res,&id); //03461351 3<70<19<81
  if (err==0)
  {
  }
  else
  {
    if ((err==0xC9)||(err==0xD6))
    {
      if (id)
      {
	DNR_ID=id;
	sprintf(ss,"Wait for DNR ID:%d...",id);
	LockSched();
	ShowMSG(1,(int)ss);
	UnlockSched();
	return;
      }
    }
    else
    {
      sprintf(ss,"DNR ERROR %d!",err);
      LockSched();
      ShowMSG(1,(int)ss);
      UnlockSched();
      return;
    }
  }
  ViewDNRresult(p_res);
}

void send_req(void)
{
  sprintf(buf,
          "POST /scripts/wap-status.php HTTP/1.1\r\n"
            "Host: sms.n-host.info\r\n"
              "Content-Type: application/x-www-form-urlencoded\r\n"
                "Content-Length: %d\r\n"
                  "\r\n"
                    "sms=%s&nomer=0661653392",
                    strlen(txt)+21,txt
                      );
  send(sock,buf,strlen(buf),0);
  zeromem(buf,sizeof(buf));
  pbuf=0;
  connect_state=2;
}

void end_socket(void)
{
  if (sock>=0)
  {
    shutdown(sock,2);
    closesocket(sock);
  }
}

void get_answer(void)
{
  int i=pbuf;
  if (i==16383)
    end_socket();
  else
  {
    i=recv(sock,buf+i,16383-i,0);
    if (i)
    {
      pbuf+=i;
    }
    else
    {
      end_socket();
    }
  }
}

void method0(MAIN_GUI *data)
{
  DrawRoundedFrame(0,0,131,175,0,0,0,
		   GetPaletteAdrByColorIndex(0),
		   GetPaletteAdrByColorIndex(20));
  wsprintf(data->ws1,"State: %02d",connect_state);
  DrawString(data->ws1,3,3,128,172,SMALL_FONT,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
}

void method1(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(256);
  data->ws2=AllocWS(256);
  data->gui.state=1;
}

void method2(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  FreeWS(data->ws1);
  FreeWS(data->ws2);
  data->gui.state=0;
}

void method3(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
}

void method4(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int method5(MAIN_GUI *data, GUI_MSG *msg)
{
  DirectRedrawGUI();
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT:
      return(1); //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
    }
  }
  //  method0(data);
  return(0);
}
void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  mfree_adr(data);
}

int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)method0,	//Redraw
  (void *)method1,	//Create
  (void *)method2,	//Close
  (void *)method3,	//Focus
  (void *)method4,	//Unfocus
  (void *)method5,	//OnKey
  0,
  (void *)method7,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,131,175};

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  DNR_TRIES=3;
  SUBPROC((void *)ask_dns);
  //  SUBPROC((void *)create_connect);
}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)end_socket);
  SUBPROC((void *)ElfKiller);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  char ss[100];
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  if (msg->msg==MSG_HELPER_TRANSLATOR)
  {
    if ((int)msg->data0==ENIP_DNR_HOST_BY_NAME)
    {
      if ((int)msg->data1==DNR_ID)
      {
	if (DNR_TRIES) SUBPROC((void *)ask_dns);
      }
      return(1);
    }
    if ((int)msg->data1==sock)
    {
      //Если наш сокет
      switch((int)msg->data0)
      {
      case ENIP_BUFFER_FREE:
	ShowMSG(1,(int)"ENIP_BUFFER_FREE");
	break;
      case ENIP_BUFFER_FREE1:
	ShowMSG(1,(int)"ENIP_BUFFER_FREE");
	break;
      case ENIP_SOCK_CONNECTED:
        if (connect_state==1)
        {
          //Если посылали запрос
          SUBPROC((void *)send_req);
          REDRAW();
        }
        else
        {
          ShowMSG(1,(int)"Illegal message ENIP_SOCK_CONNECTED!");
        }
        break;
      case ENIP_SOCK_DATA_READ:
        if (connect_state==2)
        {
          //Если посылали send
          SUBPROC((void *)get_answer);
          REDRAW();
        }
        else
        {
          ShowMSG(1,(int)"Illegal message ENIP_DATA_READ");
        }
        break;
      case ENIP_SOCK_REMOTE_CLOSED:
        //Закрыт со стороны сервера
        if (connect_state) SUBPROC((void *)end_socket);
        break;
      case ENIP_SOCK_CLOSED:
        //Закрыт вызовом closesocket
        sprintf(ss,"Recived %d bytes",pbuf);
        ShowMSG(1,(int)ss);
        connect_state=0;
        sock=-1;
        break;
      }
    }
  }
  return(1);
}

const int minus11=-11;

const CSM_DESC maincsm=
{
  maincsm_onmessage,
  maincsm_oncreate,
  0,
  0,
  0,
  0,
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
};

int main()
{
  char dummy[sizeof(MAIN_CSM)];
  LockSched();
  CreateCSM(&maincsm,dummy,0);
  UnlockSched();
  return 0;
}
