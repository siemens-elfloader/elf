#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "string_works.h"
#include "WeatherD.h"

//=============================================================================

WSHDR *ews;
int sock;
int connect_state;
char buf[65546];
int pbuf;
void *canvasdata;

void create_connect(void);
void do_start_connection(void)
{
  SUBPROC((void *)create_connect);
}

void StartGPRS(void)
{
  GPRS_OnOff(1,1);
  GBS_StartTimerProc(&reconnect_tmr,216*30,do_start_connection);
}

void create_connect(void)
{
  SOCK_ADDR sa;
  //Устанавливаем соединение
  connect_state=0;
  pbuf=0;

  GBS_DelTimer(&reconnect_tmr);
  
  if (!IsGPRSEnabled())
  {
    StartGPRS();
    if (!old_gprs_state[1])
    {
      old_gprs_state[0] = 0;
      old_gprs_state[1] = 1;
    }
    return;
  }
  else
  {
    if (!old_gprs_state[1])
    {
      old_gprs_state[0] = 1;
      old_gprs_state[1] = 1;
    }    
  }
  
  sock=socket(1,1,0);
  if (sock!=-1)
  {
    sa.family=1;
    sa.port=htons(80);
    sa.ip=htonl(IP_ADDR(212,48,138,20));
    if (connect(sock,&sa,sizeof(sa))!=-1)
    {
      connect_state=1;
      REDRAW();
    }
    else
    {
      closesocket(sock);
      sock=-1;
      GBS_StartTimerProc(&reconnect_tmr,216*10,do_start_connection);
    }
  }
  else
  {
    //Не осилили создания сокета, закрываем GPRS-сессию
    GPRS_OnOff(0,1);
    // и через 30 секунд запускаем жопорез
    GBS_StartTimerProc(&reconnect_tmr, 216*30, StartGPRS);    
  }
}

char req_buf[256];
int page_num=1;
void send_req(void)
{
      sprintf(req_buf,"GET /wap2/towns/%i.wap2"
         " HTTP/1.0\r\nHost: wap.gismeteo.ru\r\n\r\n",TID);  
 
  send(sock,req_buf,strlen(req_buf),0);
  connect_state=2;
}

void end_socket(void)
{
  if (sock>=0)
  {
    shutdown(sock,2);
    closesocket(sock);
    // выключаем жопорез, если он изначально был выключен
    if (!old_gprs_state[0]) GPRS_OnOff(0,1);
  }
}

void get_answer(void)
{
  int i=pbuf;
  if (i==65535)
    end_socket();
  else
  {
    i=recv(sock,buf+i,65535-i,0);
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

//==============================================================================


void log_data(char *data)
{
  int hFile;
  unsigned int io_error = 0;
  char fullname[256];
  
  TTime time;
  TDate date;
  GetDateTime(&date, &time);
  
  
  sprintf(fullname, "%s%i%i%i%i%i", DATA_PATH, date.year, date.month, date.day, time.hour, time.min);
  hFile = fopen(fullname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE, &io_error);
  if(!io_error)
  {
    fwrite(hFile, data, strlen(data)-1, &io_error);
    fclose(hFile, &io_error);
    //ShowMSG(1, (int)"Writed!");
  }  
}

void Parsing()
{  
    char *fcstr;
    int i;  
      
    fcstr=strstr(buf,"</table>");
      
    //Картинка
    fcstr=strstr(fcstr,"/images/")+strlen ("/images/");
    for (i=0;fcstr[i]!='.'&&(i<strlen (fcstr));i++);
      strncpy(weath.Pic, fcstr, i+1);
    weath.Pic[i]=0; 
    strcat(weath.Pic, ".png");
    
    //Температура
    fcstr=strstr(fcstr,"<b>")+strlen ("<b>");
    for (i=0;fcstr[i]!='<'&&(i<strlen (fcstr));i++);
      strncpy(weath.Temp, fcstr, i+1);
      weath.Temp[i]=0;
    strcat(weath.Temp, "\xB0\x43\n");     
      
    //Давление
    fcstr=strstr(fcstr,"<tr><td")+strlen ("<tr><td");
    fcstr=strstr(fcstr,">")+18;
    for (i=0;fcstr[i]!='<'&&(i<strlen (fcstr));i++);
      strncpy(weath.Pressure, fcstr, i+1);
    weath.Pressure[i]='\n';    
    
    //Ветер
    fcstr=strstr(fcstr,"<tr><td")+strlen ("<tr><td");
    fcstr=strstr(fcstr,">")+12;
    for (i=0;fcstr[i]!='<'&&(i<strlen (fcstr));i++);
      strncpy(weath.Wind, fcstr, i+1);
    weath.Wind[i]='\n';    
    
    //Влажность
    fcstr=strstr(fcstr,"<tr><td")+strlen ("<tr><td");
    fcstr=strstr(fcstr,">")+20;
    for (i=0;fcstr[i]!='<'&&(i<strlen (fcstr));i++);
      strncpy(weath.Rewlet, fcstr, i+1);
    weath.Rewlet[i]='\n';    
  
    //SUBPROC((void *)log_data, buf);
}

//==============================================================================

const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

extern void kill_data(void *p, void (*func_p)(void *));

void CountTime(void)
{
  TDate date;
  TTime time;
  unsigned int min_before_update;

  GetDateTime(&date, &time);

  if ((time.hour*60+time.min)-GetTimeZoneShift(&date, &time, RamDateTimeSettings()->timeZone)+180 >= 1230/*20.30 мск*/)
    {
      min_before_update = 1590-((time.hour*60+time.min)-GetTimeZoneShift(&date, &time, RamDateTimeSettings()->timeZone)+180)+10/*10 минут запаса*/;
      goto L_END;
    }
 
  if ((time.hour*60+time.min)-GetTimeZoneShift(&date, &time, RamDateTimeSettings()->timeZone)+180 < 150/*2.30 мск*/)
    {
      min_before_update = 150-((time.hour*60+time.min)-GetTimeZoneShift(&date, &time, RamDateTimeSettings()->timeZone)+180)+10/*10 минут запаса*/;
      goto L_END;
    }  
  
  if ((time.hour*60+time.min)-GetTimeZoneShift(&date, &time, RamDateTimeSettings()->timeZone)+180 >= 870/*14.30 мск*/)
    {
      min_before_update = 1230-((time.hour*60+time.min)-GetTimeZoneShift(&date, &time, RamDateTimeSettings()->timeZone)+180)+10/*10 минут запаса*/;
      goto L_END;
    }
 
  if ((time.hour*60+time.min)-GetTimeZoneShift(&date, &time, RamDateTimeSettings()->timeZone)+180 >= 510/*8.30 мск*/)
    {
      min_before_update = 870-((time.hour*60+time.min)-GetTimeZoneShift(&date, &time, RamDateTimeSettings()->timeZone)+180)+10/*10 минут запаса*/;
      goto L_END;
    }  
  
  if ((time.hour*60+time.min)-GetTimeZoneShift(&date, &time, RamDateTimeSettings()->timeZone)+180 >= 150/*2.30 мск*/)
    {
      min_before_update = 510-((time.hour*60+time.min)-GetTimeZoneShift(&date, &time, RamDateTimeSettings()->timeZone)+180)+10/*10 минут запаса*/;
      goto L_END;
    }

L_END:
  GBS_DelTimer(&update_tmr);
  GBS_StartTimerProc(&update_tmr, (216*60)*min_before_update, do_start_connection); 
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"WeatherD config updated!");
      InitConfig();
    }
  }

  if (weath.Temp[0]=='+' || weath.Temp[0]=='-')
  {
    int scr_w=ScreenW();
    int scr_h=ScreenH();
    char sss[1024];

    #define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
    CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);    
    if (IsGuiOnTop(idlegui_id)&&!IsScreenSaver()/*&&IsUnlocked()*/) //Если IdleGui на самом верху
    {
      GUI *igui=GetTopGUI();
      if (igui) //И он существует
      {
	//void *canvasdata=BuildCanvas();
        canvasdata = BuildCanvas();
        
        sprintf(sss, "%s%s%s%s", 
                SHOW_TEMP     ? weath.Temp       : "", 
                SHOW_PRESSURE ? weath.Pressure   : "", 
                SHOW_WIND     ? weath.Wind       : "", 
                SHOW_REWLET   ? weath.Rewlet     : "");
        
        utf82win(sss,(const char *)sss);
        ascii2ws(ews, sss);
        DrawCanvas(canvasdata, DATA_X, DATA_Y, DATA_X+Get_WS_width(ews, FONT_SIZE)+1, DATA_Y+GetFontYSIZE(FONT_SIZE), 1); 
        DrawString(ews, DATA_X, DATA_Y ,scr_w-4, scr_h-4-GetFontYSIZE(FONT_SIZE),
	         FONT_SIZE,0,FONT_COLOR,GetPaletteAdrByColorIndex(23));
        
        if (SHOW_PIC)
        {
          DrawCanvas(canvasdata, PICT_X, PICT_Y, PICT_X + GetImgWidth((int)MakeGlobalString(ICON_PATH, '\\', weath.Pic)), PICT_Y + GetImgHeight((int)MakeGlobalString(ICON_PATH, '\\', weath.Pic)), 1);
          DrawImg(PICT_X, PICT_Y, (int)MakeGlobalString(ICON_PATH, '\\', weath.Pic));
        }
      }
    }    
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
          SUBPROC((void *)send_req);
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
        SUBPROC((void *)Parsing);
        CountTime();
        old_gprs_state[1] = 0;
        connect_state=0;
        sock=-1;
        break;
      }
    }
  }
  
  return (1);
}

static void maincsm_oncreate(CSM_RAM *data)
{
  ews=AllocWS(1024);
  do_start_connection();
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  FreeWS(ews);
  GBS_DelTimer(&update_tmr);
  GBS_DelTimer(&reconnect_tmr);
  SUBPROC((void *)Killer);
}

static unsigned short maincsm_name_body[140];

static const struct
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

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"WeatherD");
}

int main()
{
  InitConfig();
  
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();  
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();

  return 0;
}
