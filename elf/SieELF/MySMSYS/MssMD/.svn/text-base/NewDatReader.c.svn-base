#include "..\..\inc\swilib.h"
#include "config_data.h"
#include "sms_dat.h"
#include "language.h"
#include "main.h"
#include "MySMSYS_ipc.h"
#define MAX_SMS 100
typedef struct
{
  char unk0;
  char unk1;
  unsigned short index_id; //0xFFFF, no
  char num[12]; //hex, num[0],len
  short txt_len;
  short w_char[7]; //
  char unk2;
  char unk3;
  short unk_0x160F;
  char unk4[8];
  int opmsg_id;
  unsigned short data_id;//SMS: (data_id-0x2A)*sizeof(PDU)= the position of this sms in sms.dat, EMS: 0xFFF4 ?
  short unk5; //0xA800 ?
}EMS_ADM;

void Add2WS_NEW(char *data, unsigned short *wsbody, int len)
{
  int i;
  char *p=(char *)wsbody;
  for(i=0;i<len;i+=2)
  {
    p[i+2]=data[i+1];
    p[i+3]=data[i];
  }
  wsbody[0]=len/2;
}

void Hex2Num_NEW(char *hex, char *num, int len)
{
  char *p=hex;
  char *pp=num;
  int m=0;
  int c=0;
  int c1;
  if((c1=*p++)==0x91) {*pp='+'; pp++;}
  else if(c1==0xD0) //7bit ?
  {
    len=((len&1)?1:0) + (len>>1);
    while(len)
    {
      c=0x80;
      do
      {
	if(!m) {c1=*p++; m=8;}
	c>>=1;
	if(c1&1) c|=0x80;
	c1>>=1; m--;
      }while(!(c&1));
      c>>=1;
      if(!c) c='@';
      if(c==2) c='$';
      *pp=c;
      pp++;
      len--;
    }
    *pp=0;
    return;
  }
  while(m<len)
  {
    if(m&1) c1=c>>4;
    else c1=(c=(*p++))&0x0F;
    *pp=c1+0x30; pp++;
    m++;
  }
  *pp=0;
}

void Bit7Decode(WSHDR *ws, char *pdata, int skip, int len) //big respect to Rst7(LogSms),
{
  char *p=pdata;
  int c, c2, i=0;
  while(len)
  {
    c=0x80;
    do
    {
      if(!i) {c2=*p++; i=8;}
      c>>=1;
      if(c2&1) c|=0x80;
      c2>>=1; i--;
    }while(!(c&1));
    c>>=1;
    if(!c) c='@';
    if(c==2) c='$';
    if(skip) skip--;
    else wsAppendChar(ws, c);
    len--;
  }
}

int PduDecodeTxt(SMS_DATA *sd, char *data) //0: fail, 1: successful, //2: unktype
{
  int c;
  int ttype;
  int isplus, wlen, isems, skip=0;
  char *p;
  WSHDR *ws, wsn, *wst;
  unsigned short wsb[300];
  ws=CreateLocalWS(&wsn, wsb, 300);
  p=data;
  if(*p++!=0x11)
    return 0;
  if(*p++!=0x11)
    return 0;
  c=*p++;
  if(!c)
    return 0;
  c=*p++; //sms center
  p+=c;
  c=*p++;
  if((c>>4)%2) isplus=1;
  else isplus=0;
  if((c>>6)%2) isems=1;
  else isems=0;
  if((sd->type==TYPE_OUT)||(sd->type==TYPE_DRAFT)) //out
  {
    p++;
  }
  c=*p++;
  c=((c&1)?1:0) + (c>>1) +1;
/*  if(c)
  {
    if(c%2)
      c=c/2+2;
    else
      c=c/2+1;
  }
  else
  {
    c=1;
    //sd->Number[0]=0;
  }*/
  p+=c+1; //num
  ttype=*p++;
  if((sd->type==TYPE_IN_R)||(sd->type==TYPE_IN_N))
  {
    p+=7; //time
  }
  if(isplus&&((sd->type==TYPE_OUT)||(sd->type==TYPE_DRAFT))) p++; //
  c=*p++;
  //...text,
  if(isems)
  {
    skip=(*p)+1;
    if(ttype!=8) skip=((skip*8)+6)/7;
    else
    {
      p+=skip;
      c-=skip;
    }
  }
  if(ttype==0x8)
  {
    Add2WS_NEW(p, ws->wsbody, c);
  }
  else if(ttype==0x0) //7bit
  {
    //GSMTXT_Decode(ws,(void*)p,c*7/8+1, ttype, (void*(*)(int))malloc_adr(),(void(*)(void))mfree_adr());
    Bit7Decode(ws, p, skip, c);
    if(wstrlen(ws)>c)
    {
      CutWSTR(ws, c);
    }
  }
  else 
  {
    sd->msg_type=sd->msg_type|ISUNKE;
    wsprintf(ws, STR_UNK_TXTT, ttype);
  }
  wst=sd->SMS_TEXT;
  wlen=wstrlen(ws);
  if(wlen)
  {
    if(wst)
    {
      wlen+=wstrlen(wst);
      sd->SMS_TEXT=AllocWS(wlen);
      wstrcpy(sd->SMS_TEXT, wst);
      wstrcat(sd->SMS_TEXT, ws);
      FreeWS(wst);
    }
    else
    {
      sd->SMS_TEXT=AllocWS(wlen);
      wstrcpy(sd->SMS_TEXT, ws);
    }
  }
  return 1;
}

void DoMsgReport(SMS_DATA *sd, char *data, WSHDR *ws)
{
  char time[32];
  int status, i;
  char *pp=time, *p=data;
  for(i=0;i<6;i++) //time
  {
    *pp++=p[i]%0x10+'0';
    *pp++=p[i]/0x10+'0';
    if(i<2)
      *pp++='-';
    if(i==2)
      *pp++=' ';
    if(i>2&&i<5)
      *pp++=':';
  }
  *pp=0;
  p+=7; //time 
  status=*p;
  if(status==0)
    wsprintf(ws, "%t\r%t: 20%s", lgp.LGP_MSG_REPORT, lgp.LGP_MSG_REVEICED, time);
  else
    wsprintf(ws, "%t\r%t: 20%s\r%s (%d)!", lgp.LGP_MSG_REPORT, lgp.LGP_TIME, time, lgp.LGP_UNK_RP_STATUS, status);
}


int PduDecodeAll(SMS_DATA *sd, char *data) //0: fail, 1: successful, //2: unktype
{
  int c;
  int ttype, wlen;
  int isplus, isems, skip=0, isreport=0;
  char *p;
  WSHDR *ws, wsn;
  unsigned short wsb[300];
  ws=CreateLocalWS(&wsn, wsb, 300);
  p=data;
  if(*p++!=0x11)
    return 0;
  if(*p++!=0x11)
    return 0;
  c=*p++;
  if(!c)
    return 0;
  switch(c)
  {
  case 0x01:
    sd->type=TYPE_IN_R;
    break;
  case 0x03:
    sd->type=TYPE_IN_N;
    break;
  case 0x05:
    sd->type=TYPE_OUT;
    break;
  case 0x07:
    sd->type=TYPE_DRAFT;
    break;
  default:
    sd->type=TYPE_UNK;
    sd->msg_type=sd->msg_type|ISUNKT;
    wsprintf(ws, STR_UNK_TYPE, c);
    goto TEND;
    //return 2; //back 
  }
  c=*p++; //sms center
  p+=c;
  c=*p++;
  if(c==0x6)
  {
    isreport=1;
    p++;
  }
  if((c>>4)%2) isplus=1;
  else isplus=0;
  if((c>>6)%2) isems=1;
  else isems=0;
  if((sd->type==TYPE_OUT)||(sd->type==TYPE_DRAFT)) //out
  {
    p++;
  }
  c=*p++;
  if(c)
  {
    Hex2Num_NEW(p, sd->Number, c);
    c=((c&1)?1:0) + (c>>1) +1;
  }
  else
  {
    c=1;
    sd->Number[0]=0;
  }
  if(isreport)
    p+=c;
  else
  {
    p+=c+1; //num
    ttype=*p++;
  }
  if((sd->type==TYPE_IN_R)||(sd->type==TYPE_IN_N))
  {
    char *pp=sd->Time;
    int i;
    for(i=0;i<6;i++) //time
    {
      *pp++=p[i]%0x10+'0';
      *pp++=p[i]/0x10+'0';
      if(i<2)
	*pp++='-';
      if(i==2)
	*pp++=' ';
      if(i>2&&i<5)
	*pp++=':';
    }
    *pp=0;
    p+=7; //time
  }
  if(isreport)
  {
    sd->msg_type=sd->msg_type|ISREPORT;
    DoMsgReport(sd, p, ws);
    goto TEND;
  }
  if(isplus&&((sd->type==TYPE_OUT)||(sd->type==TYPE_DRAFT))) p++; //
  c=*p++;
  //...text,
  if(isems)
  {
    skip=(*p)+1;
    if(ttype!=8) skip=((skip*8)+6)/7;
    else
    {
      p+=skip;
      c-=skip;
    }
  }
  if(ttype==0x8)
  {
    Add2WS_NEW(p, ws->wsbody, c);
  }
  else if(ttype==0x0) //7bit
  {
    //GSMTXT_Decode(ws,(void*)p, c, ttype, (void*(*)(int))malloc_adr(),(void(*)(void))mfree_adr());
    Bit7Decode(ws, p, skip, c);
    sd->msg_type=sd->msg_type|IS7BIT;
    if(wstrlen(ws)>c)
    {
      CutWSTR(ws, c);
    }
  }
  else 
  {
    sd->msg_type=sd->msg_type|ISUNKE;
    wsprintf(ws, STR_UNK_TXTT, ttype);
  }
TEND:
  wlen=wstrlen(ws);
  if(!wlen)
    wlen=1;
  sd->SMS_TEXT=AllocWS(wlen);
  wstrcpy(sd->SMS_TEXT, ws);
  return 1;
}

int DoMsgList(SMS_DATA_LIST *lst, char *sms_buf, char *ems_admin_buf, int sms_size, int ems_admin_size)
{
  extern void AddToSdlByTime(SMS_DATA *sd);
  extern void FreeSdOne(SMS_DATA *sd);
  SMS_POS_INDEX_DATA sid;
  SMS_DATA *sdx;
  char *sms_buf_end=sms_buf+sms_size-sizeof(PDU);
  char *ems_admin_buf_end=ems_admin_buf+ems_admin_size-sizeof(EMS_ADM);
  EMS_ADM *pea;
  INDEX_ID_DATA *idd;
  unsigned short *pid;
  char *pd;
  int cnt, index, i, msg_type=0;
  if(!(idd=lst->index_id_data))
    return 0;
  if(!(pid=idd->data_id))
    return 0;
  if(!(cnt=idd->cnt_all))
    return 0;
  if(cnt!=idd->cnt_received)
    msg_type=msg_type|ISDES;
    //return 0;
  index=idd->index;
  if(!index || index>MAX_SMS)
    return 0;
  pea=(EMS_ADM *)(ems_admin_buf+(index-1)*sizeof(EMS_ADM));
  if(pea>(EMS_ADM *)ems_admin_buf_end)
    return 0;
  sdx=AllocSD();
  sdx->msg_type=msg_type;
  for(i=0;i<cnt;i++)
  {
    if(pid[i]==0xFFF4) continue;
    if(!GetSmsPosIndex(&sid, pid[i])) continue;
    if((pd=sms_buf+sid.pos_index*sizeof(PDU))>sms_buf_end) continue;
    if(!sdx->SMS_TEXT) PduDecodeAll(sdx, pd);
    else PduDecodeTxt(sdx, pd);
  }
  if(sdx->SMS_TEXT)
  {
    if(i>1) sdx->msg_type=sdx->msg_type|ISEMS;
    sdx->opmsg_id=pea->opmsg_id;
    sdx->id=index;
    sdx->cnt_r=idd->cnt_received;
    LockSched();
    AddToSdlByTime(sdx);
    UnlockSched();
  }
  else
  {
    FreeSdOne(sdx);
    return 0;
  }
  return 1;
}
int DoAllDatMsg(char *sms_buf, char *ems_admin_buf, int sms_size, int ems_admin_size)
{
  SMS_DATA_ROOT *sdroot=SmsDataRoot();
  SMS_DATA_LLIST inll=sdroot->in_msg;
  SMS_DATA_LLIST outll=sdroot->out_msg;
  SMS_DATA_LIST *lst;
  int res=0;
  lst=inll.first;
  while(lst)
  {
    if(DoMsgList(lst, sms_buf, ems_admin_buf, sms_size, ems_admin_size))
    {
      res++;
      if(!(res%4)) SendSimpleIpcMsg(SMSYS_IPC_SMS_DATA_UPDATE);//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SMS_DATA_UPDATE,&my_ipc_upd);
    }
    lst=lst->next;
  }
  lst=outll.first;
  while(lst)
  {
    if(DoMsgList(lst, sms_buf, ems_admin_buf, sms_size, ems_admin_size))
    {
      res++;
      if(!(res%4)) SendSimpleIpcMsg(SMSYS_IPC_SMS_DATA_UPDATE);//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SMS_DATA_UPDATE,&my_ipc_upd);
    }
    lst=lst->next;
  }
  if((res%4)) SendSimpleIpcMsg(SMSYS_IPC_SMS_DATA_UPDATE);//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SMS_DATA_UPDATE,&my_ipc_upd);
  return res;
}

int NewMsgReader(void)
{
//  char sms_dat[128];
//  char ems_admin_dat[128];
  int fin;
  unsigned int err;
  char *sms_buf;
  char *ems_admin_buf;
  int res=0, sms_size, ems_admin_size/*, x, xl*/;
/*  strcpy(sms_dat, CFG_SYSTEM_FOLDER);
  if((xl=strlen(sms_dat))>0)
    x=sms_dat[xl-1];
  if((x!='\\')&&(x!='/'))
  {
    sms_dat[xl]='\\';
    sms_dat[xl+1]=0;
  }
  strcat(sms_dat, "SMS\\SMS.dat");
  strcpy(ems_admin_dat, CFG_SYSTEM_FOLDER);
  if((xl=strlen(ems_admin_dat))>0)
    x=ems_admin_dat[xl-1];
  if((x!='\\')&&(x!='/'))
  {
    ems_admin_dat[xl]='\\';
    ems_admin_dat[xl+1]=0;
  }
  strcat(ems_admin_dat, "SMS\\EMS_Admin.dat");*/
  if((fin=fopen(sms_dat, A_BIN+A_ReadOnly, P_READ, &err))<0)
    return 0;
  sms_size=lseek(fin, 0, S_END, &err, &err)-2;
  sms_buf=malloc(sms_size);
  lseek(fin, 2, S_SET, &err, &err);
  if(fread(fin, sms_buf, sms_size, &err)!=sms_size)
  {
    fclose(fin, &err);
    res=0;
    goto EXIT0;
  }
  fclose(fin, &err);
  if((fin=fopen(ems_admin_dat, A_BIN+A_ReadOnly, P_READ, &err))<0)
  {
    res=0;
    goto EXIT0;
  }
  ems_admin_size=lseek(fin, 0, S_END, &err, &err)-0x9A4;
  ems_admin_buf=malloc(ems_admin_size);
  lseek(fin, 0x9A4, S_SET, &err, &err);
  if(fread(fin, ems_admin_buf, ems_admin_size, &err)!=ems_admin_size)
  {
    fclose(fin, &err);
    res=0;
    goto EXIT1;
  }
  fclose(fin, &err);
  res=DoAllDatMsg(sms_buf, ems_admin_buf, sms_size, ems_admin_size);
EXIT1:
  mfree(ems_admin_buf);
EXIT0:
  mfree(sms_buf);
  return res;
}

int IsHaveNewSMS(void)
{
  SMS_DATA_ROOT *sdroot=SmsDataRoot();
  SMS_DATA_LLIST inll;
  SMS_DATA_LIST *lst;
  INDEX_ID_DATA *idd;
  if(!sdroot->cnt_in_new_sms_dat)
    return 0;
  inll=sdroot->in_msg;
  if(!(lst=inll.last))
    return 0;
  if(!(idd=lst->index_id_data))
    return 0;
  if(idd->cnt_all != idd->cnt_received)
    return 0;
  if(idd->type==1)
    return 1;
  return 1;
}

SMS_DATA *GetTheLastNew(int reload) //1, reload, 0, no
{
  SMS_DATA *sdl;
  if(reload)
  {
    freeSDList();
    NewMsgReader();
  }
  sdl=sdltop;
  while(sdl)
  {
    if(sdl->type==TYPE_IN_N)
      return sdl;
    sdl=sdl->next;
  }
  return 0;
}

SMS_DATA *FindSmsByIndex(int index)
{
  SMS_DATA *sdl=sdltop;
  while(sdl)
  {
    if(sdl->id==index)
      return sdl;
    sdl=sdl->next;
  }
  return 0;
}

int CheckThisSMS(int index) //return, 0:do nothing, 1:need to reload all, 2:need to refresh gui
{
  SMS_DATA *sd;
  SMS_DATA_ROOT *sdroot=SmsDataRoot();
  SMS_DATA_LLIST inll=sdroot->in_msg;
  SMS_DATA_LLIST outll=sdroot->out_msg;
  SMS_DATA_LIST *lst;
  INDEX_ID_DATA *idd;
  //int exist=0;
  if(!index)
    return 0;
  lst=inll.first;
  while(lst)
  {
    if((idd=lst->index_id_data))
    {
      if(idd->index==index)
      {
	//exist=1;
	//if(idd->cnt_all != idd->cnt_received) //not full received or not full deleted
	//  return 0;
	  //goto FindAndDel;
	if((sd=FindSmsByIndex(index)))
	{
	  if(sd->cnt_r < idd->cnt_received) return 1;
	  if(idd->type==1)
	  {
	    if(sd->type!=TYPE_IN_N)
	    {
	      sd->type=TYPE_IN_N;
	      return 2;
	    }
	  }
	  else
	  {
	    if(sd->type==TYPE_IN_N)
	    {
	      sd->type=TYPE_IN_R;
	      return 2;
	    }
	  }
	}
	else return 1;
	return 0;
      }
    }
    lst=lst->next;
  }
  lst=outll.first;
  while(lst)
  {
    if((idd=lst->index_id_data))
    {
      if(idd->index==index)
      {
	//exist=1;
	//if(idd->cnt_all != idd->cnt_received) //not full received or not full deleted
	//  return 0;
	  //goto FindAndDel;
	if(!(sd=FindSmsByIndex(index))) return 1;
	else if(sd->cnt_r < idd->cnt_received) return 1;
	return 0;
      }
    }
    lst=lst->next;
  }
  //is not exist, del form list
//FindAndDel:
  if((sd=FindSmsByIndex(index)))
  {
    delSDList(sd);
    return 2;
  }
  return 0;
}

int IsThisSmsNewIn(int index)
{
  SMS_DATA_ROOT *sdroot=SmsDataRoot();
  SMS_DATA_LLIST inll=sdroot->in_msg;
  SMS_DATA_LIST *lst;
  INDEX_ID_DATA *idd;
  //int exist=0;
  if(!index)
    return 0;
  lst=inll.last;
  while(lst)
  {
    if((idd=lst->index_id_data))
    {
      if(idd->index == index)
      {
	if(idd->cnt_all != idd->cnt_received)
	  return 0;
	if(idd->type==1)
	  return 1;
      }
    }
    lst=lst->prev;
  }
  return 0;
}

/*
int GetSmsDat(char **sms_buf, char **ems_admin_buf, int *sms_size, int *ems_admin_size)
{
  char sms_dat[128];
  char ems_admin_dat[128];
  int fin;
  unsigned int err;
  char *sms_buf_2;
  char *ems_admin_buf_2;
  int sms_size_2, ems_admin_size_2, x, xl;
  strcpy(sms_dat, CFG_SYSTEM_FOLDER);
  if((xl=strlen(sms_dat))>0)
    x=sms_dat[xl-1];
  if((x!='\\')&&(x!='/'))
  {
    sms_dat[xl]='\\';
    sms_dat[xl+1]=0;
  }
  strcat(sms_dat, "SMS\\SMS.dat");
  strcpy(ems_admin_dat, CFG_SYSTEM_FOLDER);
  if((xl=strlen(ems_admin_dat))>0)
    x=ems_admin_dat[xl-1];
  if((x!='\\')&&(x!='/'))
  {
    ems_admin_dat[xl]='\\';
    ems_admin_dat[xl+1]=0;
  }
  strcat(ems_admin_dat, "SMS\\EMS_Admin.dat");
  if((fin=fopen(sms_dat, A_BIN+A_ReadOnly, P_READ, &err))<0)
    return 0;
  sms_size_2=lseek(fin, 0, S_END, &err, &err)-2;
  sms_buf_2=malloc(sms_size_2);
  lseek(fin, 2, S_SET, &err, &err);
  if(fread(fin, sms_buf_2, sms_size_2, &err)!=sms_size_2)
  {
    fclose(fin, &err);
    return 0;
  }
  fclose(fin, &err);
  *sms_buf=sms_buf_2;
  *sms_size=sms_size_2;
  if((fin=fopen(ems_admin_dat, A_BIN+A_ReadOnly, P_READ, &err))<0)
  {
    return 0;
  }
  ems_admin_size_2=lseek(fin, 0, S_END, &err, &err)-0x9A4;
  ems_admin_buf_2=malloc(ems_admin_size_2);
  lseek(fin, 0x9A4, S_SET, &err, &err);
  if(fread(fin, ems_admin_buf_2, ems_admin_size_2, &err)!=ems_admin_size_2)
  {
    fclose(fin, &err);
    return 0;
  }
  fclose(fin, &err);
  *ems_admin_buf=ems_admin_buf_2;
  *ems_admin_size=ems_admin_size_2;
  return 1;
}
*/
//int DoMsgList(SMS_DATA_LIST *lst, char *sms_buf, char *ems_admin_buf, int sms_size, int ems_admin_size)

int ReadThisSms(int index, int saf) //saf,0:do nothing,1:save as file
{
  SMS_DATA_ROOT *sdroot=SmsDataRoot();
  SMS_DATA_LLIST inll=sdroot->in_msg;
  SMS_DATA_LLIST outll=sdroot->out_msg;
  SMS_DATA_LIST *lst;
  INDEX_ID_DATA *idd;
  SMS_DATA *sdx;
  //char *sms_buf=0;
  //char *ems_admin_buf=0;
  int /*sms_size=0, ems_admin_size=0, res=0,*/ msg_type=0, cnt;
  unsigned short *pid;
  if(!index) return 0;
  if((sdx=FindSmsByIndex(index))) delSDList(sdx);
  lst=inll.first;
  while(lst)
  {
    if((idd=lst->index_id_data))
    {
      if(idd->index==index)
      {
	/*if(GetSmsDat(&sms_buf, &ems_admin_buf, &sms_size, &ems_admin_size))
	{
	  if(DoMsgList(lst, sms_buf, ems_admin_buf, sms_size, ems_admin_size))
	    res=1;
	}
	if(sms_buf) mfree(sms_buf);
	if(ems_admin_buf) mfree(ems_admin_buf);
	return res;*/
	break;
      }
    }
    lst=lst->next;
  }
  if(!lst) lst=outll.first;
  while(lst)
  {
    if((idd=lst->index_id_data))
    {
      if(idd->index==index)
      {
	/*if(GetSmsDat(&sms_buf, &ems_admin_buf, &sms_size, &ems_admin_size))
	{
	  if(DoMsgList(lst, sms_buf, ems_admin_buf, sms_size, ems_admin_size))
	    res=1;
	}
	if(sms_buf) mfree(sms_buf);
	if(ems_admin_buf) mfree(ems_admin_buf);
	return res;*/
	break;
      }
    }
    lst=lst->next;
  }
  if(!lst) return 0;
  if(!(idd=lst->index_id_data)) return 0;
  if(!(pid=idd->data_id)) return 0;
  if(!(cnt=idd->cnt_all)) return 0;
  if(cnt!=idd->cnt_received) msg_type=msg_type|ISDES;
  
  //-----------------------open read dat-------------------
  
//  char sms_dat[128];
//  char ems_admin_dat[128];
  int fsd, fea;
  unsigned int err;
  int sms_size, ems_admin_size,/* x,*/ xl, i;
  char pdu[sizeof(PDU)];
  EMS_ADM pea;
  SMS_POS_INDEX_DATA sid;
/*  strcpy(sms_dat, CFG_SYSTEM_FOLDER);
  if((xl=strlen(sms_dat))>0)
    x=sms_dat[xl-1];
  if((x!='\\')&&(x!='/'))
  {
    sms_dat[xl]='\\';
    sms_dat[xl+1]=0;
  }
  strcat(sms_dat, "SMS\\SMS.dat");
  strcpy(ems_admin_dat, CFG_SYSTEM_FOLDER);
  if((xl=strlen(ems_admin_dat))>0)
    x=ems_admin_dat[xl-1];
  if((x!='\\')&&(x!='/'))
  {
    ems_admin_dat[xl]='\\';
    ems_admin_dat[xl+1]=0;
  }
  strcat(ems_admin_dat, "SMS\\EMS_Admin.dat");*/
  if((fsd=fopen(sms_dat, A_BIN+A_ReadOnly, P_READ, &err))<0)
    return 0;
  sms_size=lseek(fsd, 0, S_END, &err, &err)/*-2*/;
  if((fea=fopen(ems_admin_dat, A_BIN+A_ReadOnly, P_READ, &err))<0)
  {
    fclose(fsd, &err);
    return 0;
  }
  ems_admin_size=lseek(fea, 0, S_END, &err, &err)/*-0x9A4*/;
  if((xl=(index-1)*sizeof(EMS_ADM)+0x9A4)>(ems_admin_size-sizeof(EMS_ADM)))
  {
    fclose(fsd, &err);
    fclose(fea, &err);
    return 0;
  }
  lseek(fea, xl, S_SET, &err, &err);
  if(fread(fea, &pea, sizeof(EMS_ADM), &err)!=sizeof(EMS_ADM))
  {
    fclose(fsd, &err);
    fclose(fea, &err);
    return 0;
  }
  fclose(fea, &err);
  
  sdx=AllocSD();
  sdx->msg_type=msg_type;
  for(i=0;i<cnt;i++)
  {
    if(pid[i]==0xFFF4) continue;
    if(!GetSmsPosIndex(&sid, pid[i])) continue;
    if((xl=sid.pos_index*sizeof(PDU)+2)>(sms_size-sizeof(PDU))) continue;
    lseek(fsd, xl, S_SET, &err, &err);
    if(fread(fsd, &pdu, sizeof(pdu), &err)!=sizeof(PDU)) continue;
    if(!sdx->SMS_TEXT) PduDecodeAll(sdx, (char *)(&pdu));
    else PduDecodeTxt(sdx, (char *)(&pdu));
  }
  fclose(fsd, &err);
  if(sdx->SMS_TEXT)
  {
    if(i>1) sdx->msg_type=sdx->msg_type|ISEMS;
    sdx->opmsg_id=pea.opmsg_id;
    sdx->id=index;
    sdx->cnt_r=idd->cnt_received;
    if(CFG_ENA_AUTO_SAF_RT && !(sdx->msg_type&ISDES) && saf==1 && saveFile(sdx->SMS_TEXT, sdx->Number, sdx, sdx->type, 2))
    {
      deleteDat(sdx, 0);
      FreeSdOne(sdx);
      return 1;
    }
    LockSched();
    AddToSdlByTime(sdx);
    UnlockSched();
  }
  else 
  {
    FreeSdOne(sdx);
    return 0;
  }
  return 1;
}


SMS_DATA *FindSdByFileName(char *filename)
{
  SMS_DATA *sdl=sdltop;
  while(sdl)
  {
    if(sdl->isfile && sdl->fname && !strcmp(filename, sdl->fname))
      return sdl;
    sdl=sdl->next;
  }
  return 0;
}

int CheckFile(int type)
{
  char filepath[128];
  const char *folder;
  char dir[128];
  int x, len, res=0;
  unsigned int err;
  DIR_ENTRY de;
  SMS_DATA *sdx;
  switch(type)
  {
  case TYPE_DRAFT:
    folder=FLDR_DRAFT;
    break;
  case TYPE_OUT:
    folder=FLDR_OUT;
    break;
  case TYPE_IN_N:
  case TYPE_IN_R:
  case TYPE_IN_ALL:
    folder=FLDR_IN;
    break;
  default:
    folder=FLDR_UNK;
    break;
  }
  if(!isdir(CFG_MAIN_FOLDER, &err)) return 0;
  strcpy(dir, CFG_MAIN_FOLDER);
  if((len=strlen(dir))<=0) return 0;
  x=dir[len-1];
  if((x!='\\')&&(x!='/'))
  {
    dir[len]='\\';
    dir[len+1]=0;
  }
  strcat(dir, folder);
  if(!isdir(dir, &err)) return 0;
  strcat(dir, "*.mss");
  if(FindFirstFile(&de, dir, &err))
  {
    do
    {
      strcpy(filepath, de.folder_name);
      if((len=strlen(filepath))<=0) continue;
      x=filepath[len-1];
      if((x!='\\')&&(x!='/'))
      {
	filepath[len]='\\';
	filepath[len+1]=0;
      }
      strcat(filepath, de.file_name);
      if(!(sdx=FindSdByFileName(filepath)))
      {
	sdx=AllocSD();
	if(ReadMSS(filepath, sdx))
	{
	  res++;
	  LockSched();
	  AddToSdlByTime(sdx);
	  UnlockSched();
	  if(!(res%4)) SendSimpleIpcMsg(SMSYS_IPC_SMS_DATA_UPDATE);//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SMS_DATA_UPDATE,&my_ipc_upd);
	}
	else FreeSdOne(sdx);
      }
    }while(FindNextFile(&de, &err));
  }
  FindClose(&de, &err);
  if((res%4)) SendSimpleIpcMsg(SMSYS_IPC_SMS_DATA_UPDATE);//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SMS_DATA_UPDATE,&my_ipc_upd);
  return res;
}

int CheckDat(void)
{
  SMS_DATA *sd;
  SMS_DATA_ROOT *sdroot=SmsDataRoot();
  SMS_DATA_LLIST inll=sdroot->in_msg;
  SMS_DATA_LLIST outll=sdroot->out_msg;
  SMS_DATA_LIST *lst;
  INDEX_ID_DATA *idd;
  int res=0;
  lst=inll.first;
  while(lst)
  {
    if((idd=lst->index_id_data))
    {
      if((sd=FindSmsByIndex(idd->index)))
      {
	if(sd->cnt_r < idd->cnt_received)
	{
	  if(ReadThisSms(idd->index, 0))
	    res++;
	  if(res && !(res%4)) SendSimpleIpcMsg(SMSYS_IPC_SMS_DATA_UPDATE);//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SMS_DATA_UPDATE,&my_ipc_upd);
	  continue;
	}
	if(idd->type==1)
	{
	  if(sd->type!=TYPE_IN_N)
	  {
	    sd->type=TYPE_IN_N;
	    res++;
	    if(!(res%4)) SendSimpleIpcMsg(SMSYS_IPC_SMS_DATA_UPDATE);//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SMS_DATA_UPDATE,&my_ipc_upd);
	    continue;
	  }
	}
	else
	{
	  if(sd->type==TYPE_IN_N)
	  {
	    sd->type=TYPE_IN_R;
	    res++;
	    if(!(res%4)) SendSimpleIpcMsg(SMSYS_IPC_SMS_DATA_UPDATE);//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SMS_DATA_UPDATE,&my_ipc_upd);
	    continue;
	  }
	}
      }
      else
      {
	if(ReadThisSms(idd->index, 0))
	  res++;
      }
    }
    lst=lst->next;
  }
  lst=outll.first;
  while(lst)
  {
    if((idd=lst->index_id_data))
    {
      if(!(sd=FindSmsByIndex(idd->index)) || sd->cnt_r < idd->cnt_received)
      {
	if(ReadThisSms(idd->index, 0))
	  res++;
	if(res && !(res%4)) SendSimpleIpcMsg(SMSYS_IPC_SMS_DATA_UPDATE);//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SMS_DATA_UPDATE,&my_ipc_upd);
      }
    }
    lst=lst->next;
  }
  if((res%4)) SendSimpleIpcMsg(SMSYS_IPC_SMS_DATA_UPDATE);//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SMS_DATA_UPDATE,&my_ipc_upd);
  return res;
}

int IsDatExsit(int index)
{
  SMS_DATA_ROOT *sdroot=SmsDataRoot();
  SMS_DATA_LLIST inll=sdroot->in_msg;
  SMS_DATA_LLIST outll=sdroot->out_msg;
  SMS_DATA_LIST *lst;
  INDEX_ID_DATA *idd;
  lst=inll.first;
  while(lst)
  {
    if((idd=lst->index_id_data))
    {
      if(idd->index==index)
	return 1;
    }
    lst=lst->next;
  }
  lst=outll.first;
  while(lst)
  {
    if((idd=lst->index_id_data))
    {
      if(idd->index==index)
	return 1;
    }
    lst=lst->next;
  }
  return 0;
}

int CheckBack(void)
{
  SMS_DATA *sdl=sdltop;
  SMS_DATA *sdx;
  int n=0;
  while(sdl)
  {
    if(sdl->isfile)
    {
      if(sdl->fname)
      {
	if(!IsFileExist(sdl->fname))
	{
	  sdx=sdl;
	  sdl=sdl->next;
	  delSDList(sdx);
	  n++;
	  if(!(n%4)) SendSimpleIpcMsg(SMSYS_IPC_SMS_DATA_UPDATE);//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SMS_DATA_UPDATE,&my_ipc_upd);
	  continue;
	}
      }
    }
    else if(sdl->id)
    {
      if(!IsDatExsit(sdl->id))
      {
	sdx=sdl;
	sdl=sdl->next;
	delSDList(sdx);
	n++;
	if(!(n%4)) SendSimpleIpcMsg(SMSYS_IPC_SMS_DATA_UPDATE);//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SMS_DATA_UPDATE,&my_ipc_upd);
	continue;
      }
    }
    sdl=sdl->next;
  }
  if((n%4)) SendSimpleIpcMsg(SMSYS_IPC_SMS_DATA_UPDATE);//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SMS_DATA_UPDATE,&my_ipc_upd);
  return n;
}

//extern const IPC_REQ my_ipc_upd; //sms_dat.c
int CheckAll(void)
{
  int res=0;
  if(is_readall) return 0;
  CheckBack();
  res=CheckDat();
  res+=CheckFile(TYPE_IN_ALL);
  res+=CheckFile(TYPE_OUT);
  res+=CheckFile(TYPE_DRAFT);
  new_sms_n=getCountByType(TYPE_IN_N);
  SendSimpleIpcMsg(SMSYS_IPC_SMS_DATA_UPDATE);//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SMS_DATA_UPDATE,&my_ipc_upd);
  return res;
}


int NewToRead_File(SMS_DATA *sd)
{
  int fin, size, version, lsize;
  char *buf;
  unsigned int err;
  MSS_FILE_P1 mfp1;
  MSS_FILE_P2 mfp2;
  char filepath[128];
  if(!sd || !sd->isfile || !sd->fname)
    return 0;
//  sd->type=TYPE_IN_R;
//  if(new_sms_n>0) new_sms_n--;
  
  //先修改文件
  strcpy(filepath, sd->fname);
  if((fin=fopen(filepath, A_BIN+A_ReadOnly, P_READ, &err))<0)
    return 0;
  size=lseek(fin, 0, S_END, &err, &err);
  if(size<sizeof(MSS_FILE_P1))
  {
  FERR:
    fclose(fin, &err);
    return 0;
  }
  lseek(fin, 8, S_SET, &err, &err); //version;
  if(fread(fin, &version, sizeof(int), &err)!=sizeof(int))
  {
    goto FERR;
  }
  lseek(fin, 0, S_SET, &err, &err);
  if(version==1)
  {
    if(fread(fin, &mfp1, sizeof(MSS_FILE_P1), &err)!=sizeof(MSS_FILE_P1))
      goto FERR;
    lsize=size-sizeof(MSS_FILE_P1);
    mfp2.version=MSS_VERSION;
    mfp2.type=TYPE_IN_R;
    strcpy(mfp2.header, mfp1.header);
    strcpy(mfp2.time, mfp1.time);
    strcpy(mfp2.number, mfp1.number);
  }
  else if(version==2)
  {
    if(fread(fin, &mfp2, sizeof(MSS_FILE_P2), &err)!=sizeof(MSS_FILE_P2))
      goto FERR;
    lsize=size-sizeof(MSS_FILE_P2);
    mfp2.type=TYPE_IN_R;
  }
  else
  {
    goto FERR;
  }
  buf=malloc(lsize);
  if(fread(fin, buf, lsize, &err)!=lsize)
  {
  FERR1:
    mfree(buf);
    goto FERR;
  }
  fclose(fin, &err);
  if((fin=fopen(filepath, A_BIN+A_WriteOnly+A_Create+A_Truncate, P_WRITE, &err))<0)
  {
    mfree(buf);
    return 0;
  }
  if(fwrite(fin, &mfp2, sizeof(MSS_FILE_P2), &err)!=sizeof(MSS_FILE_P2))
    goto FERR1;
  if(fwrite(fin, buf, lsize, &err)!=lsize)
    goto FERR1;
  mfree(buf);
  fclose(fin, &err);
  sd->type=TYPE_IN_R;
  if(new_sms_n>0) new_sms_n--;
  return 1;
}

