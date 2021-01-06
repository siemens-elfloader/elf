#include "../inc/swilib.h"
#include "ussd_process.h"
#include "../inc/xtask_ipc.h"
#include "main.h"

//IPC
const char ipc_my_name[32]="CallCenter";
const char ipc_xtask_name[]=IPC_XTASK_NAME;
IPC_REQ gipc;

int CASH_SIZE=0;

extern long  strtol (const char *nptr,char **endptr,int base);
char cashfname[128];

extern const char CASHREQNUM[];
extern const char cashTEMP_PATH[];
extern const char cashLOG_FILE[];
extern const char cashLOG_Format[];
extern const int ENA_AUTOCASHTRACE;

int MaxCASH[MAX_CASH_SIZE];
int CurrentCASH[MAX_CASH_SIZE];

static GBSTMR ussd_tmr;

static volatile int ussdreq_sended;
static volatile int locked;

static char old_text[250];

static void WriteLog(int dummy, char *text)
{
  unsigned int ul;
  extern const int ENA_CASHTRACELOG;
  char std[300];
  TTime t;
  TDate d;
  if (!text) return;
  if (ENA_CASHTRACELOG && strcmp(old_text,text))
  {
    strcpy(old_text, text);
    int f=fopen(cashLOG_FILE,A_ReadWrite+A_Create+A_Append+A_BIN,P_READ+P_WRITE,&ul);
    if (f!=-1)
    {
      GetDateTime(&d, &t);
      ul = sprintf(std, cashLOG_Format,
              d.day,d.month,d.year, t.hour,t.min,
              text, CurrentCASH[0], CurrentCASH[1], CurrentCASH[2], CurrentCASH[3]);
      *(std+ul)=13; ul++; *(std+ul)=10; ul++; *(std+ul)=0;
      fwrite(f,std,ul,&ul);
      fclose(f,&ul);
    }
  }
  mfree(text);
}

void SaveCash(void)
{
  int f;
  unsigned int ul;
  unsigned char attrib;
  if (*cashfname)
  {
    if ((f=fopen(cashfname,A_ReadWrite+A_Create+A_BIN+A_Truncate,P_WRITE,&ul))!=-1)
    {
      fwrite(f,CurrentCASH,sizeof(CurrentCASH),&ul);      //by BoBa 4.07.07
      fwrite(f,MaxCASH,sizeof(MaxCASH),&ul);
      fclose(f,&ul);
      GetFileAttrib(cashfname,&attrib,&ul);
      if (!(attrib&FA_HIDDEN))
      {
        attrib|=FA_HIDDEN;
        SetFileAttrib(cashfname,attrib,&ul);
      }
    }
  }
}

/*
static void CheckPay(void)
{
  int i=0;
  int f=0;
  do
  {
    if (CurrentCASH[i]>MaxCASH[i])
    {
      MaxCASH[i]=CurrentCASH[i];
      f=1;
    }
    i++;
  }
  while(i<CASH_SIZE);
  if (f) SaveCash();
}
*/

extern const char CashPat0[];
extern const char CashPat1[];
extern const char CashPat2[];
extern const char CashPat3[];

static const char * const patterns[MAX_CASH_SIZE]=
{
  CashPat0,
  CashPat1,
  CashPat2,
  CashPat3
};

static int FindCash(const char *s)
{
  int n=0; //Номер
  const char *pat;
  int i;
  int f=0;
  char *ep;
  const char *p;
  const char *pval;
  int c;
  int cc;
  while(n<CASH_SIZE)
  {
    //if (!patterns[n]) break; //Больше паттернов нет
  L_RESTARTPAT:
    p=s; //Текущая позиция в строке
    s++;
    pval=NULL; //Число пока не нашли
    pat=patterns[n]; //Начинаем с начала паттерна
    while((c=*pat++,cc=*p)) //Пока не дошли до конца строки, в которой ищем
    {
      if (c=='#') //А не число ли сейчас требуется
      {
        //Проверяем на число
        if (((cc<'0')||(cc>'9'))&&(cc!='-')) goto L_RESTARTPAT; //Первая цифра не число - рестарт поиска
        pval=p; //Возможно число будет здесь
        do
        {
          cc=*++p; //Следующий символ
        }
        while(((cc>='0')&&(cc<='9'))||(cc=='-')||(cc=='.')||(cc==',')); //Пока это еще число
      }
      else
      {
        //Обычное сравнение
        if (!c) break; //Дошли до конца паттерна, значит все совпало, выходим
        //Сравниваем символы
        if (cc!=c) goto L_RESTARTPAT; //Нет совпадения, рестартуем
        p++;
      }
    }
    if (c) break; //Не дошли до конца паттерна
    if (!pval) break; //Не нашли число
    s=p; //Поиск будем продолжать отсюда
    i=strtol(pval,&ep,10)*100;
    pval=ep;
    if ((*pval=='.')||(*pval==','))
    {
      pval++;

      int j=strtol(pval, &ep, 10);//надо домножить число после запятой...
      int k=ep-pval;//... на 10^(2-k)
      if (k==1)
        j*=10;
      else
        while (k>2) {//делим j на 10^(k-2)
          j/=10; k--;
        }//ибо, бывают ещё балансы в у.е. с 3-4 знаками после запятой. Сам видел у МТСа. Lost, 15.01.2008
      if (i >= 0)
        i+=j;
      else
        i-=j;

      pval=ep;
    }
    if (i>(CurrentCASH[n]+(MaxCASH[n]/100))) //Если новый больше чем текущий +1 процент от максимального
    {
      MaxCASH[n]=i;
      f=1;
    }
    CurrentCASH[n]=i;
    n++;
  }
  //while(n<CASH_SIZE);  Может быть ни одного пока идет поиск сети
  if (f) SaveCash();
  return (n);
}

static void _lock(void)
{
  if (locked) return;
  gipc.name_to=ipc_xtask_name;
  gipc.name_from=ipc_my_name;
  gipc.data=0;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_LOCK_SHOW,&gipc);
  locked=1;
}

static void _unlock(void)
{
  if (!locked) return;
  gipc.name_to=ipc_xtask_name;
  gipc.name_from=ipc_my_name;
  gipc.data=0;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_UNLOCK_SHOW,&gipc);
  locked=0;
}

static void ussd_timeout(void)
{
  _unlock();
  ussdreq_sended=0;
  StartHoursTimer();
}


int ProcessUSSD(CSM_RAM* data, GBS_USSD_MSG *msg)
{
  WSHDR *ws;
  int len;
  char *s;
  int i=0;

#define ussdreqgui_id (((int *)data)[DISPLACE_OF_USSDREQGUI_ID/4])

//  if (!ENA_CASHTRACE) return 0;
  if (msg->msg==MSG_USSD_RX)
  {
    if (!ussdreq_sended) return 0;
    EndUSSDtimer();
  }
  if (msg->msg==MSG_AUTOUSSD_RX)
  {
    if (!ENA_AUTOCASHTRACE) return 0;
  }
  ws=AllocWS(256);
  len=msg->pkt_length;
  if (len>240) len=240;
  GSMTXT_Decode(ws,msg->pkt,len,msg->encoding_type,(void*(*)(int))malloc_adr(),(void(*)(void))mfree_adr());
  if ((len=ws->wsbody[0]))
  {
    zeromem(s=malloc(len+3),len+3);
    len=0;
    while(len<ws->wsbody[0])
    {
      int c=ws->wsbody[len+1];
      c=char16to8(c);
      if (c<32) c='?';
      s[len++]=c;
    }
    i=FindCash(s);
 //   s[len++]=13;
 //   s[len++]=10;
    SUBPROC((void *)WriteLog,0,s);
  }
  FreeWS(ws);
  if (ussdreqgui_id)
  {
    GeneralFunc_flag1(ussdreqgui_id,0);
    ussdreqgui_id=0;
  }
  StartHoursTimer();
  if (msg->msg==MSG_AUTOUSSD_RX)
  {
    if (!i) return (0);
    SendAutoUSSDack();
  }
  FreeGSMTXTpkt(msg->pkt);
  return 1;
}

static void ussd_send(void)
{
  if (IsGuiOnTop(((int *)FindCSMbyID(CSM_root()->idle_id))[DISPLACE_OF_IDLEGUI_ID/4]))
  {
    ussdreq_sended=1;
    MakeVoiceCall(CASHREQNUM,0x10,0x2FFF);
    GBS_StartTimerProc(&ussd_tmr,216*60,ussd_timeout);
  }
  else
  {
    SendCashReq();
  }
}

void SendCashReq(void)
{
  if (ussdreq_sended) return; //Ужо летим ;)
  GBS_StartTimerProc(&ussd_tmr,216*3,ussd_send);
  _lock();
}

void EndUSSDtimer(void)
{
  GBS_DelTimer(&ussd_tmr);
  ussdreq_sended=0;
  _unlock();
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

void LoadCash(void)
{
  unsigned int ul;
  int s=0;
  char imsi_str[IMSI_DATA_BYTE_LEN*2+1];

  CASH_SIZE=0;

  extern char cur_imsi[];
  imsi2str(cur_imsi,imsi_str);
  sprintf(cashfname,"%sCallCenter_cash_%s.tmp",cashTEMP_PATH,imsi_str);
  zeromem(CurrentCASH,sizeof(CurrentCASH));
  zeromem(MaxCASH,sizeof(MaxCASH));
  int f=fopen(cashfname,A_ReadOnly+A_BIN,P_READ,&ul);
  if (f!=-1)
  {
    s=fread(f,CurrentCASH,sizeof(CurrentCASH),&ul);     //by BoBa 4.07.07
    s=fread(f,MaxCASH,sizeof(MaxCASH),&ul);
    fclose(f,&ul);
  }
  if (s!=sizeof(MaxCASH))
  {
    memcpy(MaxCASH,CurrentCASH,sizeof(MaxCASH));
    SaveCash();
  }
  while ((CASH_SIZE<MAX_CASH_SIZE)&&(*patterns[CASH_SIZE]))
  {
    CASH_SIZE++;
  }
}
