#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "weather.h"
#include "string_works.h"
#include "img_works.h"
#include "towns_list.h"
#include "rect_patcher.h"
#include "main.h"

const int minus11=-11;
unsigned short maincsm_name_body[140];
int MAINCSM_ID;
WSHDR *ews;

int sock;
int connect_state;
char buf[16384];
char logbuf[1024];
int pbuf;

char Town_ID[5];


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

WEATHER weath[20];
char Town_Name[64];

void create_connect(void)
{
  SOCK_ADDR sa;
  //Устанавливаем соединение
  connect_state=0;
  pbuf=0;

  sock=socket(1,1,0);
  if (sock!=-1)
  {
    sa.family=1;
    sa.port=htons(80);
    sa.ip=htonl(IP_ADDR(212,48,138,20));
    //sa.ip=htonl(IP_ADDR(212,48,138,19));
    if (connect(sock,&sa,sizeof(sa))!=-1)
    {
      connect_state=1;
      REDRAW();
    }
    else
      closesocket(sock);
  }
}

void do_start_connection(void)
{
  SUBPROC((void *)create_connect);
}

char req_buf[256];
int page_num=1;
void send_req(void)
{
  if (page_num==1)
    {
      sprintf(req_buf,"GET /wap2/towns/%s.wap2"
         " HTTP/1.0\r\nHost: wap.gismeteo.ru\r\n\r\n",Town_ID);              
    }            
    else
    {
      sprintf(req_buf,"GET /wap2/towns/%s_%i.wap2"
         " HTTP/1.0\r\nHost: wap.gismeteo.ru\r\n\r\n",Town_ID, page_num);
    }  
  send(sock,req_buf,strlen(req_buf),0);
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
    if (i>=0)
    {
      pbuf+=i;
    }
    else
    {
      end_socket();
    }
  }
}
/*
void log_data(char *data, int pn)
{
  int hFile;
  unsigned int io_error = 0;
  char fullname[256];
  
  sprintf(fullname, "%s%i.data", "0:\\ZBin\\Weather\\", pn);
  hFile = fopen(fullname,A_ReadWrite +A_Create+ A_BIN,P_READ+P_WRITE, &io_error);
  if(!io_error)
  {
    fwrite(hFile, data, strlen(data)-1, &io_error);
    fclose(hFile, &io_error);
  }  
}
*/
int itemnum=0;
void Parsing()
{  
    char *fcstr;
    int i;  

    //Town
    fcstr=strstr(buf,"<title>Gismeteo: ")+strlen("<title>Gismeteo: ");
    for (i=0;fcstr[i]!='<'&&(i<strlen (fcstr)) ;i++);
      strncpy(Town_Name, fcstr, i+1);
    Town_Name[i]=0;
    utf82win(Town_Name,(const char *)Town_Name);

    for (int j=0;j<5;j++)
    {
      //Date
      fcstr=strstr(fcstr,"</table>");
      fcstr=strstr(fcstr,"<tr><td")+strlen ("<tr><td");
      fcstr=strstr(fcstr,">")+1;
      for (i=0;fcstr[i]!='<'&&(i<strlen (fcstr));i++);
        strncpy(weath[itemnum].DateTime, fcstr, i+1);
      weath[itemnum].DateTime[i]=0;

      //Картинка
      fcstr=strstr(fcstr,"/images/")+strlen ("/images/");
      for (i=0;fcstr[i]!='.'&&(i<strlen (fcstr));i++);
        strncpy(weath[itemnum].Pic, fcstr, i+1);
      weath[itemnum].Pic[i]=0; 
      strcat(weath[itemnum].Pic, ".png");
    
      //осадки
      fcstr=strstr(fcstr,"alt=")+strlen ("alt=")+1;
      for (i=0;fcstr[i]!='"'&&(i<strlen (fcstr));i++);
        strncpy(weath[itemnum].Cloudiness, fcstr, i+1);
      weath[itemnum].Cloudiness[i]=0;
    
      //Температура
      fcstr=strstr(fcstr,"<b>")+strlen ("<b>")+1;
      for (i=0;fcstr[i]!='<'&&(i<strlen (fcstr));i++);
        strncpy(weath[itemnum].Temp, fcstr, i+1);
      weath[itemnum].Temp[i]=0;      

      //Давление
      fcstr=strstr(fcstr,"<tr><td")+strlen ("<tr><td");
      fcstr=strstr(fcstr,">")+1;
      for (i=0;fcstr[i]!='<'&&(i<strlen (fcstr));i++);
        strncpy(weath[itemnum].Pressure, fcstr, i+1);
      weath[itemnum].Pressure[i]=0;    
    
      //Ветер
      fcstr=strstr(fcstr,"<tr><td")+strlen ("<tr><td");
      fcstr=strstr(fcstr,">")+1;
      for (i=0;fcstr[i]!='<'&&(i<strlen (fcstr));i++);
        strncpy(weath[itemnum].Wind, fcstr, i+1);
      weath[itemnum].Wind[i]=0;    
    
      //Влажность
      fcstr=strstr(fcstr,"<tr><td")+strlen ("<tr><td");
      fcstr=strstr(fcstr,">")+1;
      for (i=0;fcstr[i]!='<'&&(i<strlen (fcstr));i++);
        strncpy(weath[itemnum].Rewlet, fcstr, i+1);
      weath[itemnum].Rewlet[i]=0;
      
      itemnum++;
    }

  //SUBPROC((void *)log_data, buf, page_num);
  page_num++;  

  if (page_num<=4) do_start_connection();
    else
      {
        itemnum=0;
        void ShowWeather(void);
        ShowWeather();        
      };
}


void DrawWait()
{
  WSHDR *ws = AllocWS(1024);
    wsprintf(ws,"%s",logbuf);
    DrawString(ws,2,YDISP+5,ScreenW()-1,ScreenH()-1,FONT_SMALL,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  FreeWS(ws);
}

void OnRedraw(MAIN_GUI *data)
{  
  DrawRectangle(0,YDISP,ScreenW()-1,ScreenH()-1,0,
		   GetPaletteAdrByColorIndex(0),
		   GetPaletteAdrByColorIndex(1));  
  DrawWait();
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
  DisableIDLETMR();
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  DirectRedrawGUI();
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT: 
#ifndef NEWSGOLD
    case RED_BUTTON:       
#endif
      return(1);
    }
  }
  return(0);
}

extern void kill_data(void *p, void (*func_p)(void *));
void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data, mfree_adr);
}

int method8(void){return(0);}
int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)OnRedraw,	
  (void *)onCreate,	
  (void *)onClose,	
  (void *)onFocus,	
  (void *)onUnfocus,
  (void *)OnKey,	
  0,
  (void *)method7,	
  (void *)method8,
  (void *)method9,
  0
};
/*
void fdt2dt(unsigned int uitime, TTime *time, TDate *date)
{
  date->year=(uitime>>25) + 80;
  if(date->year>100)date->year-=100;
  date->month=(uitime>>21) & 0x0f;
  date->day=(uitime>>16) & 0x1f;
  
  time->hour=(uitime>>11) & 0x1f;
  time->min=(uitime>>5)  & 0x3f;
}
*/

const RECT Canvas={0,0,0,0};
void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  //main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);    

  
  /*
  DIR_ENTRY de;
  unsigned int err;
  char fullname[256];
  TDate curdate, fdate;
  TTime curtime, ftime;
  
  GetDateTime(&curdate, &curtime);
  
  sprintf(fullname, "%s1.data", ICON_PATH, page_num);
  
  FindFirstFile(&de,fullname,&err);
  fdt2dt(de.create_date_time, &ftime, &fdate);
  */
  
  
  ews=AllocWS(1024);
  do_start_connection();
}

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  FreeWS(ews);
  SUBPROC((void *)ElfKiller);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  
  if (msg->msg==MSG_HELPER_TRANSLATOR)
  {
    if ((int)msg->data1==sock)
    {
      //Если наш сокет
      switch((int)msg->data0)
      {
      case ENIP_SOCK_CONNECTED:
        if (connect_state==1)
        {
          //Если посылали запрос
          if (!strstr(logbuf,"Connected\n")) strcat(logbuf,"Connected\n");
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
        sprintf(logbuf, "%sReceived page %i\n", logbuf, page_num);
        SUBPROC((void *)Parsing);
        connect_state=0;
        sock=-1;
        break;
      }
    }
  }
  return(1);
}

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
    maincsm_onmessage,
    maincsm_oncreate,
#ifdef NEWSGOLD
0,
0,
0,
0,
#endif
maincsm_onclose,
sizeof(MAIN_CSM),
1,
&minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Weather");
}

extern const unsigned int TID;
int main()
{
  InitConfig();
  if (TID)
  {  
    char dummy[sizeof(MAIN_CSM)];
    UpdateCSMname();
    LockSched();
    MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
    UnlockSched();
    sprintf(Town_ID, "%i", TID);
  }
  else
  {
    LockSched();
    ShowMSG(1,(int)"Please setup Town ID!");
    UnlockSched();
  }    
  return 0;
}

//---------------------------- Edit Control -----------------------------------
int wd_id;

static const SOFTKEY_DESC menu_sk[] =
{
  {0x0018, 0x0000, (int)"Города"},
  {0x0001, 0x0000, (int)"Выход"},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};

void edchat_ghook(GUI *data, int cmd)
{
  DYNPNGILIST_MY *t=EDIT_GetUserPointer(data);
  PNGTOP_DESC *pltop=PNG_TOP();
  if (cmd==3)
  {
    while (t)
    {
      DYNPNGILIST_MY *d;
      d=t;
      t=t->dpl.next;
      mfree(d->dpl.img->bitmap);
      mfree(d->dpl.img);
      mfree(d->fname);
      mfree(d);
    }    
  }
  if (cmd==9)
  {
    pltop->dyn_pltop=NULL;
  }
  if (cmd==0x0A)
  {
    pltop->dyn_pltop=(DYNPNGICONLIST *)t;
    DisableIDLETMR();
  }
  if (cmd==7)
  {
    SetSoftKey(data,&menu_sk[0],0);
    SetSoftKey(data,&menu_sk[1],1);
  }  
}

int edchat_onkey(GUI *data, GUI_MSG *msg)
{
  void ShowWeather(void);
  switch (msg->gbsmsg->submess)
  {
  case LEFT_SOFT:
    DispTownsMenu();
    break;
  case RIGHT_SOFT:
#ifndef NEWSGOLD
  case RED_BUTTON:
#endif
      CloseCSM(MAINCSM_ID);
      break;
      
  case RIGHT_BUTTON:
        itemnum++;
        if (itemnum==20) itemnum=19;
        GeneralFunc_flag1(wd_id,1);
        ShowWeather();        
      break;
  case LEFT_BUTTON:
        itemnum--;
        if (itemnum==-1) itemnum=0;
        GeneralFunc_flag1(wd_id,1);
        ShowWeather();       
      break;
  }

  return(0); //Do standart keys
}

char hdesc[48];
void patch_hdesc()
{
  sprintf(hdesc, "%i/20, %s", itemnum+1, Town_Name);
  //strcat(hdesc, Town_Name);
}

void edchat_locret(void){};

HEADER_DESC edchat_hdr={0,0,0,0,NULL,(int)hdesc,LGP_NULL};

const SOFTKEYSTAB menu_skt =
{
  menu_sk, 0
};

static const INPUTDIA_DESC edchat_desc =
{
  1,
  edchat_onkey,
  edchat_ghook,
  (void *)edchat_locret,
  0,
  &menu_skt,
  {0,NULL,NULL,NULL},
  FONT_SMALL,
  100,
  101,
  0,
  //  0x00000001 - Выровнять по правому краю
  //  0x00000002 - Выровнять по центру
  //  0x00000004 - Инверсия знакомест
  //  0x00000008 - UnderLine
  //  0x00000020 - Не переносить слова
  //  0x00000200 - bold
  0,
  //  0x00000002 - ReadOnly
  //  0x00000004 - Не двигается курсор
  //  0x40000000 - Поменять местами софт-кнопки
  0x00000002
};



#define wslen(ws) ws->wsbody[0]
void ShowWeather(void)
{
  EDITCONTROL ec;
  EDITC_OPTIONS ec_options;
  void *ma=malloc_adr();
  void *eq;
  
  DYNPNGILIST_MY *top=0;
  int pic_n;
  
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());

  if (Town_Name!=0)
  {
    patch_hdesc();
    
    char str[1024];
    CutWSTR(ews,0);
    utf82win(str,(const char *)weath[itemnum].DateTime);
    ascii2ws(ews, str);
    
    extern const unsigned int FONT_SIZE_DATE;
    extern const unsigned int FONT_DATE_COLOR;
    
    PrepareEditCOptions(&ec_options);
    SetPenColorToEditCOptions(&ec_options,FONT_DATE_COLOR);
    SetFontToEditCOptions(&ec_options,FONT_SIZE_DATE);
    ConstructEditControl(&ec,ECT_READ_ONLY,0x40,ews,wslen(ews));
    CopyOptionsToEditControl(&ec,&ec_options);  
    AddEditControlToEditQend(eq,&ec,ma);
    
    extern const unsigned int FONT_SIZE_DATA;
    extern const unsigned int FONT_DATA_COLOR;  
    PrepareEditCOptions(&ec_options);
    SetPenColorToEditCOptions(&ec_options,FONT_DATA_COLOR);
    SetFontToEditCOptions(&ec_options,FONT_SIZE_DATA);
        
    CutWSTR(ews,0);
    extern const char ICON_PATH[];
    pic_n= AddPicIfNotExist(&top,MakeGlobalString(ICON_PATH, '\\', weath[itemnum].Pic));
    if (pic_n!=-1)
    {
      wsAppendChar(ews,pic_n);
      wsAppendChar(ews,' ');
      ConstructEditControl(&ec,ECT_READ_ONLY,0x00,ews,wslen(ews));
      CopyOptionsToEditControl(&ec,&ec_options);
      AddEditControlToEditQend(eq,&ec,ma);      
    }    

    sprintf(str, "%s\xB0\x43\n%s\n%s\n%s\n%s", weath[itemnum].Temp,
                                               weath[itemnum].Cloudiness,
                                               weath[itemnum].Pressure,
                                               weath[itemnum].Wind,
                                               weath[itemnum].Rewlet);
    utf82win(str,(const char *)str);
    ascii2ws(ews, str);

    ConstructEditControl(&ec,/*ECT_READ_ONLY*/ECT_NORMAL_TEXT,0x40,ews,wslen(ews));
    CopyOptionsToEditControl(&ec,&ec_options);
    AddEditControlToEditQend(eq,&ec,ma);     
  }
  else
  {
    wsprintf(ews, "Информация о погоде в городе с ID %i отсутствует!", TID);
    
    PrepareEditCOptions(&ec_options);
    SetPenColorToEditCOptions(&ec_options,2);//красный
    SetFontToEditCOptions(&ec_options,4);
    ConstructEditControl(&ec,ECT_READ_ONLY,0x00,ews,wslen(ews));
    CopyOptionsToEditControl(&ec,&ec_options);  
    AddEditControlToEditQend(eq,&ec,ma);    
  }
    
  //*((int **)(&edchat_hdr.icon))=(int *)MakeGlobalString(ICON_PATH, '\\', "logo.png");
  patch_header(&edchat_hdr);
  patch_input(&edchat_desc);    
  wd_id=CreateInputTextDialog(&edchat_desc,&edchat_hdr,eq,1,top);
}
