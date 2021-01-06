#include "..\..\inc\swilib.h"
#include "..\conf_loader.h"
#include "..\mailclient.h"

#define TMR_SECOND 216

const char mailer_db_name[]=MDB_NAME;

const char ipc_viewer_name[]=IPC_VIEWER_NAME;
const char ipc_my_name[]=IPC_DAEMON_NAME;

volatile int viewer_present=-1; //Активен ли вьювер

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

#pragma inline
int is_digit(int c)
{
  if (c>=0&&c<=9) return (1);
  return (0);
}

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}



char *recived_line;

volatile int sendq_l=0;
volatile void *sendq_p=NULL;

volatile int maincsm_id;

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}


const char percent_t[]="%t";
const char empty_str[]="";
const char eol[]="\r\n";



POP_STAT pop_stat;
//Флаг для больших сообщений
int mes_rec=0;


GBSTMR reconnect_tmr;
volatile int is_gprs_online=1;
volatile ML_DAEMON *mails;

ML_DAEMON *cur_ml;


int sock=-1;

#pragma segment="ELFBEGIN"
void ElfKiller(void)
{
  kill_data(__segment_begin("ELFBEGIN"),(void (*)(void *))mfree_adr());
}

void FreeMailDB()
{
  ML_DAEMON *ml_cur=(ML_DAEMON *)mails;
  ML_DAEMON *ml_prev;
  while (ml_cur)
  {
    if (ml_cur->uidl) mfree(ml_cur->uidl);
    ml_prev=ml_cur;
    ml_cur=ml_cur->next;
    mfree(ml_prev);
  }
  mails=0;
}

void InitMailDB()
{
  char fname[256];
  int f;
  MAIL_DB mail_db;
  char *uidl;
  ML_DAEMON *ml_cur=(ML_DAEMON *)&mails;
  unsigned int err;
  strcpy(fname,EML_PATH);
  strcat(fname,mailer_db_name);
  FreeMailDB();
  if ((f=fopen(fname,A_BIN+A_ReadOnly,P_READ,&err))!=-1)
  {
    while (fread(f,&mail_db,sizeof(MAIL_DB),&err)==sizeof(MAIL_DB))
    {
      if(mail_db.magic!=MDB_MAGIC) break;
      ml_cur=ml_cur->next=malloc(sizeof(ML_DAEMON));
      ml_cur->next=0;
      ml_cur->state=mail_db.state;
      ml_cur->is_read=mail_db.is_read;
      ml_cur->mail_size=mail_db.mail_size;
      if (mail_db.uidl_len)
      {
        uidl=malloc(mail_db.uidl_len+1);
        uidl[mail_db.uidl_len]=0;
        fread(f,uidl,mail_db.uidl_len,&err);
        ml_cur->uidl=uidl;
      }
      else ml_cur->uidl=0;
      ml_cur->num_in_list=-1;
    }
    fclose(f,&err);
  }
}

void write_mail_DB()
{
  int f;
  unsigned int err;
  char fname[128];
  ML_DAEMON *ml_list=(ML_DAEMON *)&mails;
  MAIL_DB mail_db;
  strcpy(fname,EML_PATH);
  strcat(fname,mailer_db_name);
  if ((f=fopen(fname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1)
  {
    while((ml_list=ml_list->next))
    {
      mail_db.magic=MDB_MAGIC;
      mail_db.uidl_len=ml_list->uidl?strlen(ml_list->uidl):0;
      mail_db.state=ml_list->state;
      mail_db.is_read=ml_list->is_read;
      mail_db.mail_size=ml_list->mail_size;
      mail_db.hdr[0] = 0;
      fwrite(f,&mail_db,sizeof(MAIL_DB),&err);
      if (mail_db.uidl_len) fwrite(f,ml_list->uidl,mail_db.uidl_len,&err);
    }
    fclose(f,&err);
  }
}

void add_uidl_if_exist(char *recv_line)
{
  int num_in_list=strtoul(recv_line,0,10);
  recv_line=strchr(recv_line,' ')+1;
  *strrchr(recv_line,'\r')=0;
  ML_DAEMON *ml_list=(ML_DAEMON *)&mails;
  ML_DAEMON *ml_cur;
  while(ml_list->next)
  {
    ml_list=ml_list->next;
    if (ml_list->uidl)
    {
      if (!strcmp(recv_line,ml_list->uidl))
      {
        ml_list->num_in_list=num_in_list;
        return;
      }
    }
  }
  ml_cur=ml_list->next=malloc(sizeof(ML_DAEMON));
  ml_cur->num_in_list=num_in_list;
  ml_cur->next=0;
  ml_cur->uidl=malloc(strlen(recv_line)+1);
  strcpy(ml_cur->uidl,recv_line);
  if (DEFAULT_ACTION==1 && LOAD_IF_LESS)
  {
    ml_cur->state=M_IS_BIG_LETTER;
  }
  else ml_cur->state=DEFAULT_ACTION;
  ml_cur->is_read=0;
  ml_cur->mail_size=0;
}
  
void set_mes_size(char *recv_line)
{
  int num_in_list;
  int mes_size;
  num_in_list=strtoul(recv_line,0,10);
  mes_size=strtoul(strchr(recv_line,' ')+1,0,10);

  ML_DAEMON *ml_list=(ML_DAEMON *)mails;
  while(ml_list)
  {
    if (ml_list->num_in_list==num_in_list)
    {
      ml_list->mail_size=mes_size;
      if (ml_list->state==M_IS_BIG_LETTER)
      {
        ml_list->state=mes_size>LOAD_IF_LESS?M_LOAD_HEADER:M_LOAD_FULL;
      }
      return;
    }
    ml_list=ml_list->next;
  }
}

void remove_cur_from_list()
{
  char fname[128];
  unsigned int err;
  ML_DAEMON *ml_list=(ML_DAEMON *)&mails;
  ML_DAEMON *ml_prev=ml_list;
  while ((ml_list=ml_list->next))
  {
    if (!strcmp(ml_list->uidl,cur_ml->uidl))
    {
      sprintf(fname,"%s%s.eml",EML_PATH,cur_ml->uidl);
      unlink(fname,&err);
      ml_prev->next=cur_ml->next;
      mfree(cur_ml->uidl);
      mfree(cur_ml);
      cur_ml=ml_prev;
      return;
    }
    ml_prev=ml_list;
  }
}
  
void do_losted_mes()
{
  if (IF_DEL_AUX==0 || cur_ml->state==M_DELETE) remove_cur_from_list();
}  

void end_socket();

void ClearSendQ(void)
{
  mfree((void *)sendq_p);
  sendq_p=NULL;
  sendq_l=0;
}

void send_str(char* str)
{
  int j;
  int i;
  if (str)
  {
    j=strlen(str);
    // Проверяем не надо ли добавить в очередь
    if (sendq_p)
    {
      // Если есть то добавляем в нее
      sendq_p=realloc((void *)sendq_p, sendq_l+j);
      memcpy((char *)sendq_p+sendq_l,str,j);
      sendq_l+=j;
      return;     
    }
    sendq_p=malloc(j);
    memcpy((char *)sendq_p,str,j);
    sendq_l=j;
  }
  // отправляем уже существующие в очереди
  while((i=sendq_l)!=0)
  {
    i=i>0x400?0x400:i;
    j=send(sock,(void *)sendq_p,i,0);
    pop_stat.total_send+=j;
    snprintf(pop_stat.log,255,"send res %d",j);
    REDRAW();
    if (j<0)
    {
      j=*socklasterr();
      if ((j==0xC9) || (j==0xD6))
      {
        // Передали что хотели
        strcpy(pop_stat.log,"Send delayed...");
        return;
      }
      else
      {
        // Ошибка 
        LockSched();
        ShowMSG(1,(int)"send error!");
        UnlockSched();
        end_socket();
        return;
      }
    }
    memcpy((void *)sendq_p,(char *)sendq_p+j,sendq_l-=j);
    if (j<i)
    {
      // передали меньше чем заказывали
      return;
    }
  }
  mfree((void *)sendq_p);
  sendq_p=NULL;
}

void send_login()
{
  char login[128];
  sprintf(login,"USER %s\r\n",MAIL_LOGIN);
  send_str(login);
}

void send_pass()
{
  char pass[128];
  sprintf(pass,"PASS %s\r\n",MAIL_PASS);
  send_str(pass);
}

void send_get_stat()
{send_str("STAT\r\n");}

void send_get_uidl_list()
{send_str("UIDL\r\n");}

void get_list()
{send_str("LIST\r\n");}

void send_get_mes(int i)
{
  char buf[64];
  sprintf(buf,"RETR %u\r\n",i);
  send_str(buf);
}

void send_get_headers(int i)
{
  char buf[64];
  sprintf(buf,"TOP %u 0\r\n",i);
  send_str(buf);
}

void send_del_mes(int i)
{
  char buf[64];
  sprintf(buf,"DELE %u\r\n",i);
  send_str(buf);
}

void send_quit()
{send_str("QUIT\r\n");}


int resp_ok(char *buf)
{
  if (strncmp(buf,"+OK",3)) return -1;
  return (0);
}


int fhandler=-1;

void end_connect(char *err)
{
  strcpy(pop_stat.log,err);
  REDRAW();
  send_quit();
  end_socket();
  if (recived_line)
  {
    mfree(recived_line);
    recived_line=0;
  }
  if (fhandler!=-1)
  {
    //Закроем поток если некорректно вышли
    unsigned int err;
    fclose(fhandler,&err);
  }
  if (viewer_present!=-1)
  {
    IPC_REQ *ipc=malloc(sizeof(IPC_REQ));
    ipc->name_to=ipc_viewer_name;
    ipc->name_from=ipc_my_name;
    ipc->data=0;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_LOADING_FINISHED,ipc);
  }
}
  

void process_line(char *rec_line)
{
  unsigned int err;
  switch(pop_stat.pop_state)
  {
  case POP_GREETING:
    if (resp_ok(rec_line))
    {
      end_connect(rec_line);
      return;
    }
    send_login();
    pop_stat.pop_state=POP_VER_LOGIN;
    REDRAW();
    return;
    
  case POP_VER_LOGIN:
    if (resp_ok(rec_line))
    {
      end_connect(rec_line);
      return;
    }
    send_pass();
    pop_stat.pop_state=POP_VER_PASS;
    REDRAW();
    return;
    
  case POP_VER_PASS:
    if (resp_ok(rec_line))
    {
      end_connect(rec_line);
      return;
    }
    send_get_stat();
    pop_stat.pop_state=POP_GET_STAT;
    REDRAW();
    return;
    
  case POP_GET_STAT:
    if (resp_ok(rec_line))
    {
      end_connect(rec_line);
      return;
    }
    pop_stat.in_pop3=strtoul(strchr(rec_line,' ')+1,0,10);
    if (!pop_stat.in_pop3)
    {
      pop_stat.pop_state=0;
      end_connect("Mailbox is empty");
      return;
    }
    send_get_uidl_list();
    pop_stat.pop_state=POP_GET_UIDL_LIST;
    REDRAW();
    return;
    
  case POP_GET_UIDL_LIST:
    if (!mes_rec)
    {
      if (resp_ok(rec_line))
      {
        end_connect(rec_line);
        return;
      }
      mes_rec=1;
      return;
    }
    else
    {
      if (strcmp(rec_line,".\r\n"))
      {
        add_uidl_if_exist(rec_line);
        return;
      }
      else
      {
        mes_rec=0;
        get_list();
        pop_stat.pop_state=POP_GET_LIST;
        REDRAW();
        return;
      }
    }
    
  case POP_GET_LIST:
    if (!mes_rec)
    {
      if (resp_ok(rec_line))
      {
        end_connect(rec_line);
        return;
      }
      mes_rec=1;
      break;
    }
    else
    {
      if (strcmp(rec_line,".\r\n"))
      {
        set_mes_size(rec_line);
        return;
      }
      else
      {
        mes_rec=0;
        cur_ml=(ML_DAEMON*)&mails;
        write_mail_DB();
        pop_stat.pop_state=POP_PROCESS_LIST;
        REDRAW();
      }
    }
    
  case POP_PROCESS_LIST:
  case POP_RECEIVE_HEADERS:
  case POP_RECEIVE_MESSAGE:
  case POP_DELETE_MESSAGE:
    if (pop_stat.pop_state==POP_RECEIVE_HEADERS||pop_stat.pop_state==POP_RECEIVE_MESSAGE)
    {
      if (!mes_rec)
      {
        char fname[128];
        if (resp_ok(rec_line))
        {
          end_connect(rec_line);
          return;
        }
        sprintf(fname,"%s%s.eml",EML_PATH,cur_ml->uidl);
        if ((fhandler=fopen(fname,A_WriteOnly+A_Create+A_Truncate+A_BIN,P_WRITE,&err))==-1)
        {
          end_connect(pop_stat.pop_state==POP_RECEIVE_HEADERS?"Can't write headers!":"Can't write message!");
          return;
        }
        mes_rec=1;
        return;
      }
      else
      {
        if (strcmp(rec_line,".\r\n"))
        {
          fwrite(fhandler,rec_line,strlen(rec_line),&err);
          return;
        }
        else
        {
          cur_ml->state=(pop_stat.pop_state==POP_RECEIVE_HEADERS)?M_HEADERS_LOADED:M_FULL_LOADED;
          fclose(fhandler,&err);
          fhandler=-1;
          mes_rec=0;
          write_mail_DB();
          pop_stat.pop3_recv++;
          if (pop_stat.pop_state==POP_RECEIVE_MESSAGE)
          {
            if (DEL_AFTER_LOAD)
            {
              send_del_mes(cur_ml->num_in_list);
              pop_stat.pop_state=POP_DELETE_MESSAGE;
              REDRAW();
              return;
            }
          }    
          pop_stat.pop_state=POP_PROCESS_LIST;
          REDRAW();
        }
      }
    }
    else if (pop_stat.pop_state==POP_DELETE_MESSAGE)
    {
      if (resp_ok(rec_line))
      {
        end_connect("Can't delete!");
        return;
      }
      pop_stat.pop3_del++;
      pop_stat.pop_state=POP_PROCESS_LIST;
      REDRAW();
    }
    
    while ((cur_ml=cur_ml->next))
    {
      if (cur_ml->num_in_list==-1)
      {
        do_losted_mes();
        continue;
      }
      switch(cur_ml->state)
      {
      case M_LOAD_HEADER:
        send_get_headers(cur_ml->num_in_list);
        pop_stat.pop_state=POP_RECEIVE_HEADERS;
        REDRAW();
        return;
      case M_LOAD_FULL:
        send_get_mes(cur_ml->num_in_list);
        pop_stat.pop_state=POP_RECEIVE_MESSAGE;
        REDRAW();
        return;
      case M_HEADERS_LOADED:
      case M_FULL_LOADED:
        continue;
        
      case M_DELETE:
        send_del_mes(cur_ml->num_in_list);
        remove_cur_from_list();
        pop_stat.pop_state=POP_DELETE_MESSAGE;
        REDRAW();
        return;
      }
    }
    pop_stat.pop_state=0;
    write_mail_DB();
    end_connect("Done!");
    return;
  }
}

#define BUF_SIZE 1024
void get_answer(void)
{
  char msg_buf[BUF_SIZE];
  char *s=msg_buf;
  char *d; //Куда
  int c;
  int i;
  i=recv(sock,msg_buf,BUF_SIZE-1,0);
  if (i>0)
  {
    pop_stat.total_recv+=i;
    REDRAW();
    d=recived_line;
    if (d)
    {
      //Уже была строка
      d=recived_line=realloc(recived_line,strlen(d)+i+1); //Возможно, мы добавим весь буфер и \0
      d+=strlen(d);
    }
    else
    {
      //Заново
     L_NEWLINE:
       d=recived_line=malloc(i+1); //Возможно, это будет целый буфер и \0
    }
    while(i)
    {
      i--;
      c=*d++=*s++; //Копируем символ
      if (c=='\n')
      {
        //Конец строки
        *d=0;
        process_line(recived_line);
        mfree(recived_line);
        goto L_NEWLINE;
      }
    }
    *d=0; //Временно закончили строку
  }
}

// ==============================================================================================
int DNR_ID=0;
int DNR_TRIES=3;


void create_connect(void)
{
  char ip_adr[64];
  char *end_ip;
  unsigned int ip;
  int err;
  int ***p_res=NULL;
  
  void do_reconnect(void);
  SOCK_ADDR sa;
  //Устанавливаем соединение
  pop_stat.connect_state=0;
  GBS_DelTimer(&reconnect_tmr);
  ClearSendQ();
  if (!IsGPRSEnabled())
  {
    is_gprs_online=0;
    snprintf(pop_stat.log,255,"Wait for GPRS up!");
    return;
  }
  DNR_ID=0;
  strcpy(ip_adr,POP3_ADRESS);
  end_ip=strrchr(ip_adr,':');
  if (end_ip) *end_ip=0;
  ip=str2ip(ip_adr);
  if (ip!=0xFFFFFFFF)  
  {
    snprintf(pop_stat.log,255,"Connect via IP...");
    REDRAW();
    sa.ip=ip;
    goto L_CONNECT;
  }  
  snprintf(pop_stat.log,255,"Send DNR...");
  REDRAW();
  *socklasterr()=0;
  err=async_gethostbyname(POP3_ADRESS,&p_res,&DNR_ID); //03461351 3<70<19<81
  if (err)
  {
    if ((err==0xC9)||(err==0xD6))
    {
      if (DNR_ID)
      {
	return; //Ждем готовности DNR
      }
    }
    else
    {
      snprintf(pop_stat.log,255,"DNR ERROR %d!",err);
      REDRAW();
      GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*120,do_reconnect);
      return;
    }
  }
  if (p_res)
  {
    if (p_res[3])
    {
      snprintf(pop_stat.log,255,"DNR Ok, connecting...");
      REDRAW();
      DNR_TRIES=0;
      sa.ip=p_res[3][0][0];

    L_CONNECT:
      zeromem(&pop_stat,sizeof(POP_STAT));
      sock=socket(1,1,0);

      if (sock!=-1)
      {
	sa.family=1;
	sa.port=htons(POP3_PORT);
	if (connect(sock,&sa,sizeof(sa))!=-1)
	{
	  pop_stat.connect_state=1;
	  REDRAW();
	}
	else
	{
	  closesocket(sock);
	  sock=-1;
	  LockSched();
	  ShowMSG(1,(int)"Can't connect!");
	  UnlockSched();
	  GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*120,do_reconnect);
	}
      }
      else
      {
	LockSched();
	ShowMSG(1,(int)"Can't create socket, GPRS restarted!");
	UnlockSched();
	//Не осилили создания сокета, закрываем GPRS-сессию
	GPRS_OnOff(0,1);
      }
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

void do_reconnect(void)
{
  if (is_gprs_online)
  {
    DNR_TRIES=3;
    SUBPROC((void*)create_connect);
  }
}

void end_socket(void)
{
  if (sock>=0)
  {
    shutdown(sock,2);
    closesocket(sock);
  }
}

#ifdef NEWSGOLD
#define sms_submess 0x26
#else
#define sms_submess 0x1E
#endif


int numbercmp(const char *num, const char *numlist)
{
  const char *num2=num;
  int i;
  int c,d;
  for (;;) 
  {
    c=*num++;
    d=*numlist++;
    if(d==',') d=0;
    i=c-d;
    if (!i) 
    {
      if (!c) break;
      else continue;
    }
    numlist=strchr(numlist,',');
    if (!numlist) break;
    numlist++;
    num=num2;
  }
  return(i);
}

IPC_REQ gipc;

void CheckDoubleRun(void)
{
  if ((int)(gipc.data)>1)
  {
    LockSched();
    CloseCSM(maincsm_id);
    ShowMSG(1,(int)"MailDaemon already started!");
    UnlockSched();
  }
  else
  {
    gipc.name_to=ipc_viewer_name;
    gipc.name_from=ipc_my_name;
    gipc.data=&pop_stat;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_DAEMON_LOGON,&gipc);
  }
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"MailDaemon config updated!");
      InitConfig();
    }
  }
  if (msg->msg==MSG_IPC)  // Пришло сообщение, возможно от вьювера
  { 
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
      {
        switch (msg->submess)
        {
        case IPC_VIEWER_LOGON:
          if (viewer_present)
          {
            viewer_present=0;
            ipc->name_to=ipc->name_from;
            ipc->name_from=ipc_my_name;
            ipc->data=&pop_stat;
            GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_DAEMON_LOGON,ipc);
          }
          break;
          
        case IPC_VIEWER_LOGFF:
          if (!viewer_present)
          {
            viewer_present=-1;   // Вьювер вышел
          }
          break;
          
        case IPC_CHECK_MAILBOX:
          ipc->name_to=ipc->name_from;
          ipc->name_from=ipc_my_name;
          if ((pop_stat.connect_state==0)&&(sock==-1))
          {
            GBS_DelTimer(&reconnect_tmr);
            DNR_TRIES=3;
            SUBPROC((void *)create_connect);
            ipc->data=(void *)1;
          }
          else
            ipc->data=(void *)0;
          GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_CHECK_MAILBOX,ipc);
          break;
          
        case IPC_STOP_CHECKING:
          mfree(ipc);
          SUBPROC((void *)end_connect,"Manually stopped");
          break;
          
        case IPC_CHECK_DOUBLERUN:
          ipc->data=(void *)((int)(ipc->data)+1);
          //Если приняли свое собственное сообщение, значит запускаем чекер
          if (ipc->name_from==ipc_my_name) SUBPROC((void *)CheckDoubleRun);
          break;
        }
      }
    }
  }
  if (msg->msg==MSG_SMS_RX)
  {
    if (msg->submess==sms_submess)
    {
      char number[64];
      int GetSMSNumber(const PDU *sms, char *number);
      if (GetSMSNumber(IncommingPDU(),number))
      {
        if (!numbercmp(number,SMSFORWARD))
        {
          if ((pop_stat.connect_state==0)&&(sock==-1))
          {
            GBS_DelTimer(&reconnect_tmr);
            DNR_TRIES=3;
            SUBPROC((void *)create_connect);
          }
        }
      }
    }
  }
  if (msg->msg==MSG_HELPER_TRANSLATOR)
  {
    switch((int)msg->data0)
    {
    case LMAN_DISCONNECT_IND:
      is_gprs_online=0;
      break;
    case LMAN_CONNECT_CNF:
      is_gprs_online=1;
      GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*120,do_reconnect);
      break;
    case ENIP_DNR_HOST_BY_NAME:
      if ((int)msg->data1==DNR_ID)
      {
	if (DNR_TRIES) SUBPROC((void *)create_connect);
      }
      break;
    }
    if ((int)msg->data1==sock)
    {
      //Если наш сокет
      switch((int)msg->data0)
      {
      case ENIP_SOCK_CONNECTED:
	if (pop_stat.connect_state==1)
	{
	  //Соединение установленно, посылаем пакет login
          InitMailDB();
	  strcpy(pop_stat.log,"Try to login...");
          pop_stat.connect_state=2;
	  REDRAW();
	}
	else
	{
	  ShowMSG(1,(int)"Illegal message ENIP_SOCK_CONNECTED!");
	}
	break;
      case ENIP_SOCK_DATA_READ:
	if (pop_stat.connect_state>=2)
	{
	  //Если посылали send
	  SUBPROC((void *)get_answer);
	  //    REDRAW();
	}
	else
	{
	  ShowMSG(1,(int)"Illegal message ENIP_DATA_READ");
	}
	break;
        
      case ENIP_BUFFER_FREE:
        if (!sendq_p)
        {
          ShowMSG(1,(int)"Illegal ENIP_BUFFER_FREE!");
          SUBPROC((void *)end_socket);
        }
        else
        {
          //Досылаем очередь
          snprintf(pop_stat.log,255,"ENIP_BUFFER_FREE");
          REDRAW();
          SUBPROC((void *)send_str,0);
        }
        break;
        
      case ENIP_BUFFER_FREE1:
        if (!sendq_p)
        {
          ShowMSG(1,(int)"Illegal ENIP_BUFFER_FREE1!");
          SUBPROC((void *)end_socket);
        }
        else
        {
          // Досылаем очередь
          snprintf(pop_stat.log,255,"ENIP_BUFFER_FREE1");
          REDRAW();
          SUBPROC((void *)send_str,0);
        }
        break;
          
        
      case ENIP_SOCK_REMOTE_CLOSED:
	//Закрыт со стороны сервера
	if (pop_stat.connect_state) SUBPROC((void *)end_socket);
	break;
        
      case ENIP_SOCK_CLOSED:
	pop_stat.connect_state=0;
	sock=-1;
        if (sendq_p)
        {
          snprintf(pop_stat.log,255,"Disconnected, %d bytes not sended!", sendq_l);
        }
	REDRAW();
        SUBPROC((void *)ClearSendQ);
	break;
      }
    }
  }
  return(1);
}
// ==============================================================================================

static void maincsm_oncreate(CSM_RAM *data)
{
  gipc.name_to=ipc_my_name;
  gipc.name_from=ipc_my_name;
  gipc.data=0;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_CHECK_DOUBLERUN,&gipc);
}


static void maincsm_onclose(CSM_RAM *csm)
{
  gipc.name_to=ipc_viewer_name;
  gipc.name_from=ipc_my_name;
  gipc.data=(void *)0;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_DAEMON_LOGOFF,&gipc);
  
  GBS_DelTimer(&reconnect_tmr);
  if (recived_line)
  {
    mfree(recived_line); 
    recived_line=NULL;
  }
  FreeMailDB();
  SUBPROC((void *)end_socket);
  SUBPROC((void *)ClearSendQ);
  SUBPROC((void *)ElfKiller);
}

static unsigned short maincsm_name_body[140];
const int minus11=-11;

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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"MailDaemon");
}

int main(char *exename, char *fname)
{
  CSM_RAM *save_cmpc;
  MAIN_CSM main_csm;
  InitConfig();
  UpdateCSMname();
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  maincsm_id=CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  return (0);
}


int GetSMSNumber(const PDU *sms, char *number)
{
  const char *p=sms->data;
  unsigned int i;
  unsigned int m;
  unsigned int c;
  unsigned int c1;
  if ((*p++)!=0x11) return (0);
  if ((*p++)!=0x11) return (0);
  if (!(*p++)) return (0);
  c=*p++; //Пропускаем SCA
  p+=c;
  if ((*p++)&3) return (0); //Неподходящий тип сообщения ;)
  i=*p++; //Длина номера в нибблах
  if (*p++==0x91) *number++='+';
  m=0;
  c=0;
  while(m<i && m<32)
  {
    if (m&1) c1=c>>4; else c1=(c=(*p++))&0x0F;
    *number++=c1+'0';
    m++;
  }
  *number=0;
  return (1);
}


