#include "include.h"

#include "SiemensPDU.h"
#include "MyIpcMessage.h"
#include "File.h"
#include "AdrList.h"
#include "SmsData.h"

#define MAX_SMS 100
/*
typedef struct _EMS_ADM
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
*/
//sd list---------


SDLIST *SmsData::AllocSDL(void)
{
  SDLIST *sd=new SDLIST;
  zeromem(sd, sizeof(SDLIST));
  return sd;
}

void SmsData::DeleteSDL(SDLIST *sdl)
{
  SDLIST *sdn;
  SDLIST *sdp;
  if(sdl)
  {
    LockSched();
    sdn=(SDLIST *)sdl->next;
    sdp=(SDLIST *)sdl->prev;
    if(sdp)
      sdp->next=sdn;
    else
      sdltop=sdn;
    if(sdn)
      sdn->prev=sdp;
    UnlockSched();
    if((sdl->msg_prop&ISFILE) && sdl->fname)
      delete sdl->fname;
    if(sdl->text) FreeWS(sdl->text);
    delete sdl;
  }
}

void SmsData::FreeAllSDL(void)
{
  SDLIST *sdl;
  SDLIST *sdx;
  LockSched();
  sdl=sdltop;
  sdltop=0;
  UnlockSched();
  while(sdl)
  {
    sdx=(SDLIST *)sdl->next;
    if((sdl->msg_prop&ISFILE) && sdl->fname)
      delete sdl->fname;
    if(sdl->text) FreeWS(sdl->text);
    delete sdl;
    sdl=sdx;
  }
}

void SmsData::AddByTimeSDL(SDLIST *sdl)
{
  SDLIST *sdx;
  SDLIST *sdp;
  if(!sdl)
    return;
  if(!(sdx=sdltop))
  {
    sdltop=sdl;
    return;
  }
  while(sdx)
  {
    if(strcmp(sdl->time, sdx->time)>=0)
    {
      sdp=(SDLIST *)sdx->prev;
      if(sdp) sdp->next=sdl;
      else sdltop=sdl;
      sdl->prev=sdp;
      sdl->next=sdx;
      sdx->prev=sdl;
      return;
    }
    if(!sdx->next)
    {
      sdx->next=sdl;
      sdl->prev=sdx;
      return;
    }
    sdx=(SDLIST *)sdx->next;
  }
}

void SmsData::FreeOneSDL(SDLIST *sdl)
{
  if(IsExistSDL(sdl)) return; //if is in list
  if(sdl->text)
    FreeWS(sdl->text);
  if((sdl->msg_prop&ISFILE) && sdl->fname)
    delete (sdl->fname);
  delete(sdl);
}

SDLIST *SmsData::CopyOneSDL(SDLIST *sdl)
{
  SDLIST *sdx;
  if(!sdl) return 0;
  sdx=new SDLIST;
  memcpy(sdx, sdl, sizeof(SDLIST));
  if((sdl->msg_prop&ISFILE) && sdl->fname)
  {
    sdx->fname=new char[128];
    strcpy(sdx->fname, sdl->fname);
  }
  if(sdl->text)
  {
    sdx->text=AllocWS(sdl->text->wsbody[0]);
    wstrcpy(sdx->text, sdl->text);
  }
  return sdx;
}

SDLIST *SmsData::FindSDL(int dat_index)
{
  SDLIST *sdl=sdltop;
  while(sdl)
  {
    if(sdl->dat_index==dat_index)
      return sdl;
    sdl=(SDLIST *)sdl->next;
  }
  return 0;
}

SDLIST *SmsData::FindOpmsgSDL(int opmsg_id)
{
  RAM_EMS_ADMIN *ram_eam=RAM_EMS_Admin();
  SDLIST *sdl=sdltop;
  while(sdl)
  {
    if(sdl->opmsg_id==opmsg_id)
      return sdl;
    if(!(sdl->msg_prop&ISFILE) && sdl->dat_index)
    {
      if(opmsg_id==ram_eam->data[sdl->dat_index].opmsg_id)
      {
	sdl->opmsg_id=opmsg_id;
	return sdl;
      }
    }
    sdl=(SDLIST *)sdl->next;
  }
  return 0;
}

SDLIST *SmsData::FindSDL(WSHDR *text, char *time, char *num)
{
  SDLIST *sdl=sdltop;
  if(!sdl || !text /*|| !time */|| !num) return 0;
  while(sdl)
  {
    if(!wstrncmp_nocase(sdl->text, text, text->wsbody[0])
       && !strncmp(sdl->number, num, strlen(num)))
    {
      if(!time || !strlen(time))
        return sdl;
      if(!strncmp(sdl->time, time, strlen(time)))
        return sdl;
    }
    sdl=(SDLIST *)sdl->next;
  }
  return 0;
}

SDLIST *SmsData::FindSDL(char *filename)
{
  SDLIST *sdl=sdltop;
  if(!sdl || !filename) return 0;
  while(sdl)
  {
    if((sdl->msg_prop&ISFILE) && sdl->fname && !strcmp(filename, sdl->fname))
      return sdl;
    sdl=(SDLIST *)sdl->next;
  }
  return 0;
}

int SmsData::GetSMSCount(int type)
{
  int i=0;
  SDLIST *sdl=sdltop;
  if(type>0&&type<5)
  {
    while(sdl)
    {
      if(sdl->type==type)
        i++;
      sdl=(SDLIST *)sdl->next;
    }
  }
  else if(type==TYPE_IN_ALL)
  {
    while(sdl)
    {
      if((sdl->type==TYPE_IN_R)||(sdl->type==TYPE_IN_N)||(sdl->type==TYPE_IN_ALL))
        i++;
      sdl=(SDLIST *)sdl->next;
    }
  }
  else if(type==TYPE_FILTER)
  {
    return (FilterGetCount());
  }
  else
  {
    while(sdl)
    {
      i++;
      sdl=(SDLIST *)sdl->next;
    }
  }
  return i;
}

int SmsData::GetSMSCount(int isfile, int type)
{
  int i=0;
  SDLIST *sdl=sdltop;
  if(type>0&&type<5)
  {
    while(sdl)
    {
      if((sdl->type==type) && (sdl->msg_prop&ISFILE)==isfile)
	i++;
      sdl=(SDLIST *)sdl->next;
    }
  }
  else if(type==TYPE_IN_ALL)
  {
    int t;
    while(sdl)
    {
      t=sdl->type;
      if(((t==TYPE_IN_R)||(t==TYPE_IN_N)||(t==TYPE_IN_ALL)) && (sdl->msg_prop&ISFILE)==isfile)
	i++;
      sdl=(SDLIST *)sdl->next;
    }
  }
  else
  {
    while(sdl)
    {
      if((sdl->msg_prop&ISFILE)==isfile)
	i++;
      sdl=(SDLIST *)sdl->next;
    }
  }
  return i;
}

SDLIST *SmsData::FindSDL(int type, int n)
{
  int i=0;
  SDLIST *sdl=sdltop;
  if(type>0&&type<5)
  {
    while(sdl)
    {
      if((i==n)&&(sdl->type==type))
        return sdl;
      if(sdl->type==type)
        i++;
      sdl=(SDLIST *)sdl->next;
    }
  }
  else if(type==TYPE_IN_ALL)
  {
    while(sdl)
    {
      if((sdl->type==TYPE_IN_R)||(sdl->type==TYPE_IN_N)||(sdl->type==TYPE_IN_ALL))
      {
        if(i==n) return sdl;
        i++;
      }
      sdl=(SDLIST *)sdl->next;
    }
  }
  else if(type==TYPE_FILTER)
  {
    return (FilterFindSDL(n));
  }
  else
  {
    while(sdl)
    {
      if(i==n)
        return sdl;
      sdl=(SDLIST *)sdl->next;
      i++;
    }
  }
  return 0;
}

//-----------DatReader------------------

int SmsData::ReadDat(void)
{
  int fin, res=1;
  if(sms_buf) delete sms_buf;
//  if(eam_buf) delete eam_buf;
  if((fin=FOpen(sms_dat, A_BIN+A_ReadOnly, P_READ))!=-1)
  {
    sms_size=LSeek(fin, 0, S_END)-2;
    sms_buf=new char[sms_size];
    LSeek(fin, 2, S_SET);
    if(FRead(fin, sms_buf, sms_size)!=sms_size) res=0;
    FClose(fin);
  }
  else res=0;
/*  if((fin=FOpen(ems_admin_dat, A_BIN+A_ReadOnly, P_READ))!=-1)
  {
    eam_size=LSeek(fin, 0, S_END);
    if(eam_size>0x9A4)
    {
      eam_size-=0x9A4;
      eam_buf=new char[eam_size];
      LSeek(fin, 0x9A4, S_SET);
      if(FRead(fin, eam_buf, eam_size)!=eam_size) res=0;
    }
    else res=0;
    FClose(fin);
  }
  else res=0;*/
  return res;
}

int SmsData::DeMsgDataList(SMS_DATA_LIST *lst)
{
  SMS_POS_INDEX_DATA sid;
  SDLIST *sdx;
//  EMS_ADM *pea;
  EAM_DATA *ead;
  INDEX_ID_DATA *idd;
  unsigned short *pid;
  char *pd;
  int cnt, index, i, msg_prop=0;
  char *sms_buf_end;
//  char *eam_buf_end;
  if(!sms_buf ||/* !eam_buf || */!sms_size/* || !eam_size*/) return 0;
  sms_buf_end=sms_buf+sms_size-sizeof(PDU);
//  eam_buf_end=eam_buf+eam_size-sizeof(EMS_ADM);
  if(!(idd=lst->index_id_data))
    return 0;
  if(!(pid=idd->data_id))
    return 0;
  if(!(cnt=idd->cnt_all))
    return 0;
  if(cnt!=idd->cnt_received)
    msg_prop=msg_prop|ISDES;
  index=idd->index;
  if(!index || index>MAX_SMS)
    return 0;
  ead=&RAM_EMS_Admin()->data[index];
//  pea=(EMS_ADM *)(eam_buf+(index-1)*sizeof(EMS_ADM));
//  if(pea>(EMS_ADM *)eam_buf_end)
//    return 0;
  sdx=AllocSDL();
  sdx->msg_prop=msg_prop;
  for(i=0;i<cnt;i++)
  {
    if(pid[i]==0xFFF4) continue;
    if(!GetSmsPosIndex(&sid, pid[i])) continue;
    if((pd=sms_buf+sid.pos_index*sizeof(PDU))>sms_buf_end) continue;
    if(!sdx->text) PduDecodeAll(sdx, pd);
    else PduDecodeTxt(sdx, pd);
  }
  if(sdx->text)
  {
    if(i>1) sdx->msg_prop=sdx->msg_prop|ISEMS;
    //sdx->opmsg_id=pea->opmsg_id;
    sdx->opmsg_id=ead->opmsg_id;
    sdx->dat_index=index;
    sdx->cnt_r=idd->cnt_received;
    LockSched();
    AddByTimeSDL(sdx);
    UnlockSched();
    return 1;
  }
  else
  {
    FreeOneSDL(sdx);
    return 0;
  }
}

int SmsData::ReadAllDatMsg(void)
{
  SMS_DATA_ROOT *sdroot=SmsDataRoot();
  SMS_DATA_LLIST inll=sdroot->in_msg;
  SMS_DATA_LLIST outll=sdroot->out_msg;
  SMS_DATA_LIST *lst;
  int res=0;
  if(!ReadDat()) return 0;
  lst=inll.first;
  while(lst)
  {
    if(DeMsgDataList(lst))
    {
      res++;
      if(!(res%4)) SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
    }
    lst=(SMS_DATA_LIST *)lst->next;
  }
  lst=outll.first;
  while(lst)
  {
    if(DeMsgDataList(lst))
    {
      res++;
      if(!(res%4)) SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
    }
    lst=(SMS_DATA_LIST *)lst->next;
  }
  if((res%4)) SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
  return res;
}


SMS_DATA_LIST *SmsData::FindMsgDataL(int dat_index)
{
  SMS_DATA_LIST *lst;
  SMS_DATA_ROOT *sdroot=SmsDataRoot();
  SMS_DATA_LLIST inll=sdroot->in_msg;
  SMS_DATA_LLIST outll=sdroot->out_msg;
  INDEX_ID_DATA *idd;
  if(!dat_index) return 0;
  lst=inll.first;
  while(lst)
  {
    if((idd=lst->index_id_data))
    {
      if(idd->index==dat_index)
      {
	return lst;
      }
    }
    lst=(SMS_DATA_LIST *)lst->next;
  }
  if(!lst) lst=outll.first;
  while(lst)
  {
    if((idd=lst->index_id_data))
    {
      if(idd->index==dat_index)
      {
	return lst;
      }
    }
    lst=(SMS_DATA_LIST *)lst->next;
  }
  return 0;
}

int SmsData::ReadMessageOne(int dat_index)
{
  int res;
  SMS_DATA_LIST *lst;
  SDLIST *sdl;
  if(!dat_index) return 0;
  if(!(lst=FindMsgDataL(dat_index))) return 0;
  if(!ReadDat()) return 0;
  if((sdl=FindSDL(dat_index))) DeleteSDL(sdl);
  if((res=DeMsgDataList(lst)))
    this->n_new=GetSMSCount(TYPE_IN_N);
  return res;
}

void SmsData::FreeDatBuf(void)
{
  if(sms_buf) delete sms_buf;
//  if(eam_buf) delete eam_buf;
  sms_buf=NULL;
//  eam_buf=NULL;
  sms_size=0;
//  eam_size=0;
}
//-----------FileReader----------
#define ELFNAME "MySMSYS"
int SmsData::ReadMss(char *fname, SDLIST *sdl)
{
  int fin;
  int size, len=0;
  MSS_FILE_P1 msf1;
  MSS_FILE_P2 msf2;
  int version;
  if((fin=FOpen(fname, A_BIN+A_ReadOnly, P_READ))<0)
    return 0;
  size=LSeek(fin, 0, S_END);
  if(size<sizeof(MSS_FILE_P1))
    goto ERR_BACK;
  LSeek(fin, 8, S_SET);
  if(FRead(fin, &version, sizeof(int))!=sizeof(int))
  {
  ERR_BACK:
    FClose(fin);
    return 0;
  }
  LSeek(fin, 0, S_SET);
  if(version==1)
  {
    if(FRead(fin, &msf1, sizeof(MSS_FILE_P1))!=sizeof(MSS_FILE_P1))
      goto ERR_BACK;
    if(strncmp(msf1.header, ELFNAME, 7))
      goto ERR_BACK;
    strcpy(sdl->time, msf1.time);
    strcpy(sdl->number, msf1.number);
  }
  else if(version==2)
  {
    if(FRead(fin, &msf2, sizeof(MSS_FILE_P2))!=sizeof(MSS_FILE_P2))
      goto ERR_BACK;
    if(strncmp(msf2.header, ELFNAME, 7))
      goto ERR_BACK;
    strcpy(sdl->time, msf2.time);
    strcpy(sdl->number, msf2.number);
    sdl->type=msf2.type;
  }
  else goto ERR_BACK;
  if(FRead(fin, &len, 2)!=2) goto ERR_BACK;
  sdl->text=AllocWS(len);
  if(FRead(fin, sdl->text->wsbody+1, len*2)!=len*2)
    goto ERR_BACK;
  FClose(fin);
  sdl->text->wsbody[0]=len;
  sdl->msg_prop|=ISFILE;
  sdl->fname=new char[128];
  strcpy(sdl->fname, fname);
  return 1;
}


int SmsData::ReadFolder(int type)
{
  const char *folder;
  char dir[128];
  char fullpath[128];
  int n=0,len;//, x;
  DIR_ENTRY de;
  SDLIST *sdx;
  switch(type)
  {
  case TYPE_DRAFT:
    folder=FLDR_DRAFT;
    break;
  case TYPE_SENT:
    folder=FLDR_SENT;
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
  strcpy(dir, main_folder);
  //if((len=strlen(dir))<=0) return 0;
  //x=dir[len-1];
  //if((x!='\\')&&(x!='/'))
  //{
  //  dir[len]='\\';
  //  dir[len+1]=0;
  //}
  strcat(dir, folder);
  if(!IsDir(dir))
    return 0;
  strcat(dir, "*.mss");
  if(FindFirstFile(&de, dir))
  {
    do
    {
      strcpy(fullpath, de.folder_name);
      if((len=strlen(fullpath))<=0) continue;
      if(fullpath[len-1]!='\\'&&fullpath[len-1]!='/')
      {
	fullpath[len++]='\\';
	fullpath[len]='\0';
      }
      strcat(fullpath, de.file_name);
      sdx=AllocSDL();
      if(ReadMss(fullpath, sdx))
      {
	n++;
	LockSched();
	AddByTimeSDL(sdx);
	UnlockSched();
	if(!(n%4)) SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
      }
      else FreeOneSDL(sdx);
    }
    while(FindNextFile(&de));
  }
  FindClose(&de);
  if((n%4)) SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
  return n;
}
//-----------SmsDataMan--------------

int SmsData::SaveMss(WSHDR *ws, const char *number, SDLIST *sdl, int type, int need_reload)
{
  char path[128];
  TTime time;
  TDate date;
  int f;//, len, x;
  const char *folder;
  char dir[128];
  SDLIST *sdx=0;
  MSS_FILE_P2 msf;
  if(!ws || !number)
    return 0;
  switch(type)
  {
  case TYPE_DRAFT:
    folder=FLDR_DRAFT;
    break;
  case TYPE_SENT:
    folder=FLDR_SENT;
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
  zeromem(&msf, sizeof(MSS_FILE_P2));
  GetDateTime(&date, &time);
  strcpy(dir, main_folder);
  //if((len=strlen(dir))<=0) return 0;
  //x=dir[len-1];
  //if((x!='\\')&&(x!='/'))
  //{
  //  dir[len]='\\';
  //  dir[len+1]=0;
  //}
  if(!IsDir(dir))
    MkDir(dir);
  strcat(dir, folder);
  if(!IsDir(dir))
    MkDir(dir);
  if(type==TYPE_DRAFT && sdl && sdl->type==TYPE_DRAFT && (sdl->msg_prop&ISFILE) && sdl->fname)
    strcpy(path, sdl->fname);
  else if(!GetMssPath(path, dir, &time, &date))
    return 0;
  if((f=FOpen(path, A_BIN+A_WriteOnly+A_Create+A_Truncate, P_WRITE))<0)
  {
    return 0;
  }
  strcpy(msf.header, ELFNAME);
  strncpy(msf.number, number, 32);
  msf.type=type;
  msf.version=MSS_VERSION;
  //如果是来短信,直接使用短信中的时间保存
  if(((type==TYPE_IN_N)||(type==TYPE_IN_R)||(type==TYPE_IN_ALL))
     &&(sdl!=0)
       &&(strlen(sdl->time)))
  {
    strcpy(msf.time, sdl->time);
  }
  else
    sprintf(msf.time, "%02d-%02d-%02d %02d:%02d:%02d",
	    date.year%2000, // ? //2008 ->08
	    date.month, date.day,
	    time.hour, time.min,
	    time.sec);
  if(FWrite(f, &msf, sizeof(MSS_FILE_P2))!=sizeof(MSS_FILE_P2))
  {
    FClose(f);
    return 0;
  }
  FWrite(f, ws->wsbody, (ws->wsbody[0]+1)*2);
  FClose(f);
  if(need_reload==1)
  {
    SUBPROC((void*)ReadAllMessageCHK, this);
  }
  else if(need_reload==2)
  {
    sdx=AllocSDL();
    if(ReadMss(path, sdx))
    {
      LockSched();
      AddByTimeSDL(sdx);
      UnlockSched();
      return ((int)sdx);
    }
    else FreeOneSDL(sdx);
  }
  return 1;
}

int SmsData::GetMssPath(char *path, char *folder, TTime *time, TDate *date)
{
  char temp[128];
  int i=0;
  sprintf(path, "%04d%02d%02d%02d%02d%02d",
	  date->year,
	  date->month,
	  date->day,
	  time->hour,
	  time->min,
	  time->sec);
  strcpy(temp, folder);
  strcat(temp, path);
  strcat(temp, ".mss");
  if(!IsFileExist(temp))
  {
    strcpy(path, temp);
    return 1;
  }
  while(i<MAX_FILE)
  {
    sprintf(temp, "%s%s_%04d%s", folder, path, i, ".mss");
    if(!IsFileExist(temp))
    {
      strcpy(path, temp);
      return 1;
    }
    i++;
  }
  return 0;
}

int SmsData::DeleteMessage(SDLIST *sdl)
{
  short cnt;
  if(!sdl) return 0;
  if((sdl->msg_prop&ISFILE) && sdl->fname)
  {
    FDelete(sdl->fname);
  }
  else if(sdl->dat_index)
  {
    if(DeleteSMS(sdl->dat_index, &cnt)!=0x3E8) return 0;
  }
  else return 0;
  if(IsExistSDL(sdl)) DeleteSDL(sdl); //可能已经在onmessage中被删除
  //if(need_reload==1) return (ReadAllMessage());
  return 1;
}

int SmsData::ReadAllMessage(void)
{
  int n=0;
  is_reading=1;
  n=ReadAllDatMsg();
  n+=ReadFolder(TYPE_IN_ALL);
  n+=ReadFolder(TYPE_SENT);
  n+=ReadFolder(TYPE_DRAFT);
  SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
  is_reading=0;
  this->n_new=GetSMSCount(TYPE_IN_N);
  return n;
}

int SmsData::ReadAllMessageCHK(SmsData *data)
{
  if(!data->sdltop) return data->ReadAllMessage();
  return 0;
}


int SmsData::ReadAllMessageFRC(SmsData *data)
{
  return data->ReadAllMessage();
}

SmsData::SmsData()
{
  sms_buf=NULL;
//  eam_buf=NULL;
  sms_size=0;
//  eam_size=0;
  sdltop=NULL;
  is_reading=0;
  this->n_new=0;
  SUBPROC((void *)this->ReadAllMessageCHK, this);
}

SmsData::~SmsData()
{
  if(sms_buf) delete sms_buf;
//  if(eam_buf) delete eam_buf;
  sms_size=0;
//  eam_size=0;
  FreeAllSDL();
}


SmsData *SMSDATA=NULL;


int SmsData::IsNewSMS(int dat_index)
{
  SMS_DATA_ROOT *sdroot=SmsDataRoot();
  SMS_DATA_LLIST inll=sdroot->in_msg;
  SMS_DATA_LIST *lst;
  INDEX_ID_DATA *idd;
  if(!dat_index)
    return 0;
  lst=inll.last;
  while(lst)
  {
    if((idd=lst->index_id_data))
    {
      if(idd->index == dat_index)
      {
	if(idd->cnt_all != idd->cnt_received)
	  return 0;
	if(idd->type==1)
	  return 1;
	return 0;
      }
    }
    lst=(SMS_DATA_LIST *)lst->prev;
  }
  return 0;
}

int SmsData::CheckSMS(int dat_index)
{
  SDLIST *sdl;
  SMS_DATA_ROOT *sdroot=SmsDataRoot();
  SMS_DATA_LLIST inll=sdroot->in_msg;
  SMS_DATA_LLIST outll=sdroot->out_msg;
  SMS_DATA_LIST *lst;
  INDEX_ID_DATA *idd;
  if(!dat_index)
    return 0;
  lst=inll.first;
  while(lst)
  {
    if((idd=lst->index_id_data))
    {
      if(idd->index==dat_index)
      {
	if((sdl=FindSDL(dat_index)))
	{
	  if(sdl->cnt_r < idd->cnt_received)
	  {
	    //DeleteSDL(sdl);
	    return CHK_RES_RELOAD;
	  }
	  if(idd->type==1)
	  {
	    if(sdl->type!=TYPE_IN_N)
	    {
	      sdl->type=TYPE_IN_N;
	      return CHK_RES_REFRESH;
	    }
	  }
	  else
	  {
	    if(sdl->type==TYPE_IN_N)
	    {
	      sdl->type=TYPE_IN_R;
	      return CHK_RES_REFRESH;
	    }
	  }
	}
	else return CHK_RES_RELOAD;
	return CHK_RES_DONOTHING;
      }
    }
    lst=(SMS_DATA_LIST *)lst->next;
  }
  lst=outll.first;
  while(lst)
  {
    if((idd=lst->index_id_data))
    {
      if(idd->index==dat_index)
      {
	if(!(sdl=FindSDL(dat_index))) return CHK_RES_RELOAD;
	else if(sdl->cnt_r < idd->cnt_received)
	{
	  //DeleteSDL(sdl);
	  return CHK_RES_RELOAD;
	}
	return CHK_RES_DONOTHING;
      }
    }
    lst=(SMS_DATA_LIST *)lst->next;
  }
  //is not exist, del form list
  if((sdl=FindSDL(dat_index)))
  {
    DeleteSDL(sdl);
    return CHK_RES_REFRESH;
  }
  return CHK_RES_DONOTHING;
}

int SmsData::CheckDat(void)
{
  SDLIST *sdl;
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
      if((sdl=FindSDL(idd->index)))
      {
	if(sdl->cnt_r < idd->cnt_received)
	{
	  DeleteSDL(sdl);
	  if(ReadMessageOne(idd->index))
	  {
	    res++;
	    if(!(res%4)) SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
	  }
	  continue;
	}
	if(idd->type==1)
	{
	  if(sdl->type!=TYPE_IN_N)
	  {
	    sdl->type=TYPE_IN_N;
	    res++;
	    if(!(res%4)) SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
	    continue;
	  }
	}
	else
	{
	  if(sdl->type==TYPE_IN_N)
	  {
	    sdl->type=TYPE_IN_R;
	    res++;
	    if(!(res%4)) SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
	    continue;
	  }
	}
      }
      else
      {
	if(ReadMessageOne(idd->index))
	{
	  res++;
	  if(!(res%4)) SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
	}
      }
    }
    lst=(SMS_DATA_LIST *)lst->next;
  }
  lst=outll.first;
  while(lst)
  {
    if((idd=lst->index_id_data))
    {
      if(!(sdl=FindSDL(idd->index)) || sdl->cnt_r < idd->cnt_received)
      {
	if(ReadMessageOne(idd->index))
	{
	  res++;
	  if(res && !(res%4)) SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
	}
      }
    }
    lst=(SMS_DATA_LIST *)lst->next;
  }
  if((res%4)) SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
  return res;
}

int SmsData::CheckFolder(int type)
{
  char filepath[128];
  const char *folder;
  char dir[128];
  int x, len, res=0;
  DIR_ENTRY de;
  SDLIST *sdx;
  switch(type)
  {
  case TYPE_DRAFT:
    folder=FLDR_DRAFT;
    break;
  case TYPE_SENT:
    folder=FLDR_SENT;
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
  //if(!IsDir(CFG_MAIN_FOLDER)) return 0;
  strcpy(dir, main_folder);
  //if((len=strlen(dir))<=0) return 0;
  //x=dir[len-1];
  //if((x!='\\')&&(x!='/'))
  //{
  //  dir[len]='\\';
  //  dir[len+1]=0;
  //}
  if(!IsDir(dir)) return 0;
  strcat(dir, folder);
  if(!IsDir(dir)) return 0;
  strcat(dir, "*.mss");
  if(FindFirstFile(&de, dir))
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
      if(!(sdx=FindSDL(filepath)))
      {
	sdx=AllocSDL();
	if(ReadMss(filepath, sdx))
	{
	  res++;
	  LockSched();
	  AddByTimeSDL(sdx);
	  UnlockSched();
	  if(!(res%4)) SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
	}
	else FreeOneSDL(sdx);
      }
    }while(FindNextFile(&de));
  }
  FindClose(&de);
  if((res%4)) SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
  return res;
}

int SmsData::IsDatExist(int dat_index)
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
      if(idd->index==dat_index)
	return 1;
    }
    lst=(SMS_DATA_LIST *)lst->next;
  }
  lst=outll.first;
  while(lst)
  {
    if((idd=lst->index_id_data))
    {
      if(idd->index==dat_index)
	return 1;
    }
    lst=(SMS_DATA_LIST *)lst->next;
  }
  return 0;
}

int SmsData::CheckSDList(void)
{
  SDLIST *sdl=sdltop;
  SDLIST *sdx;
  int n=0;
  while(sdl)
  {
    if((sdl->msg_prop&ISFILE))
    {
      if(sdl->fname)
      {
	if(!IsFileExist(sdl->fname))
	{
	  sdx=sdl;
	  sdl=(SDLIST *)sdl->next;
	  DeleteSDL(sdx);
	  n++;
	  if(!(n%4)) SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
	  continue;
	}
      }
    }
    else if(sdl->dat_index)
    {
      if(!IsDatExist(sdl->dat_index))
      {
	sdx=sdl;
	sdl=(SDLIST *)sdl->next;
	DeleteSDL(sdx);
	n++;
	if(!(n%4)) SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
	continue;
      }
    }
    sdl=(SDLIST *)sdl->next;
  }
  if((n%4)) SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
  return n;
}

int SmsData::CheckAll(void)
{
  int res=0;
  res=CheckSDList();
  res+=CheckDat();
  res+=CheckFolder(TYPE_IN_ALL);
  res+=CheckFolder(TYPE_SENT);
  res+=CheckFolder(TYPE_DRAFT);
  SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
  this->n_new=GetSMSCount(TYPE_IN_N);
  return res;
}

int SmsData::CheckAllCHK(SmsData *data)
{
  if(!data->is_reading)
  {
    return data->CheckAll();
  }
  return 0;
}

//不支持1版本Mss文件
int SmsData::NewToReadSMS(SDLIST *sdl)
{
  if(sdl->type!=TYPE_IN_N) return 0;
  if ((sdl->msg_prop&ISFILE))
  {
    if (sdl->fname)
    {
      int fin;
      int version;
      int type;
      char filepath[128];
      strcpy(filepath, sdl->fname);
      if ((fin=FOpen(filepath, A_BIN+A_ReadWrite, P_READ+P_WRITE))!=-1)
      {
	LSeek(fin, 8, S_SET);
	if(FRead(fin, &version, sizeof(int))==sizeof(int))
	{
	  if(version==2)
	  {
	    type=TYPE_IN_R;
	    LSeek(fin, 0xC, S_SET);
	    FWrite(fin, &type, sizeof(int));
	  }
	}
	FClose(fin);
	sdl->type=TYPE_IN_R;
	if(this->n_new) this->n_new--;
	return 1;
      }
      return 0;
    }
    return 0;
  }
  else if (sdl->dat_index)
  {
    if (SetSmsStatus(sdl->dat_index, 1)==0x3E8)
    {
      sdl->type=TYPE_IN_R;
      if(this->n_new) this->n_new--;
      return 1;
    }
    return 0;
  }
  return 0;
}


int SmsData::IsExistSDL(SDLIST *sdl)
{
  SDLIST *sdx=this->sdltop;
  while(sdx)
  {
    if(sdx==sdl) return 1;
    sdx=(SDLIST *)sdx->next;
  }
  return 0;
}


SDLIST *SmsData::FindNextSDL(SDLIST *sdl, int type)
{
  if(!sdl) return 0;
  if((type==TYPE_SENT)||(type==TYPE_DRAFT))
  {
    sdl=(SDLIST *)sdl->next;
    while(sdl)
    {
      if(sdl->type==type)
	return sdl;
      sdl=(SDLIST *)sdl->next;
    }
  }
  else if((type==TYPE_IN_ALL)||(type==TYPE_IN_N)||(type==TYPE_IN_R))
  {
    sdl=(SDLIST *)sdl->next;
    while(sdl)
    {
      if((sdl->type==TYPE_IN_R)||(sdl->type==TYPE_IN_N)||(sdl->type==TYPE_IN_ALL))
	return sdl;
      sdl=(SDLIST *)sdl->next;
    }
  }
  else if(type==TYPE_FILTER)
  {
    return FilterFindNext(sdl);
  }
  else
  {
    sdl=(SDLIST *)sdl->next;
    return sdl;
  }
  return 0;
}

SDLIST *SmsData::FindPrevSDL(SDLIST *sdl, int type)
{
  if(!sdl) return 0;
  if((type==TYPE_SENT)||(type==TYPE_DRAFT))
  {
    sdl=(SDLIST *)sdl->prev;
    while(sdl)
    {
      if(sdl->type==type)
	return sdl;
      sdl=(SDLIST *)sdl->prev;
    }
  }
  else if((type==TYPE_IN_ALL)||(type==TYPE_IN_N)||(type==TYPE_IN_R))
  {
    sdl=(SDLIST *)sdl->prev;
    while(sdl)
    {
      if((sdl->type==TYPE_IN_R)||(sdl->type==TYPE_IN_N)||(sdl->type==TYPE_IN_ALL))
	return sdl;
      sdl=(SDLIST *)sdl->prev;
    }
  }
  else if(type==TYPE_FILTER)
  {
    return (FilterFindPrev(sdl));
  }
  else
  {
    sdl=(SDLIST *)sdl->prev;
    return sdl;
  }
  return 0;
}


SDLIST *SmsData::FilterFindSDL(int n)
{
  switch(CFG_FILTEROP)
  {
  case FILTER_ALL:
    return (FindSDL(0, n));
  case FILTER_NEW:
    return (FindSDL(TYPE_IN_N, n));
  case FILTER_DAT:
    return (FilterFindSDL(0, n));
  case FILTER_FILE:
    return (FilterFindSDL(ISFILE, n));
  case FILTER_NUM:
    return (FilterFindSDL(CFG_STRORNUM, n));
  case FILTER_STR:
    {
      WSHDR *ws, wsn;
      unsigned short wsb[64];
      ws=CreateLocalWS(&wsn, wsb, 64);
      utf8_2ws(ws, CFG_STRORNUM, 64);
      return (FilterFindSDL(ws, n));
    }
  default:
    return 0;
  }
}

SDLIST *SmsData::FilterFindSDL(int isfile, int n)
{
  int i=0;
  SDLIST *sdl=sdltop;
  while(sdl)
  {
    if((sdl->msg_prop&ISFILE)==isfile)
    {
      if(i==n) return sdl;
      i++;
    }
    sdl=(SDLIST *)sdl->next;
  }
  return 0;
}

SDLIST *SmsData::FilterFindSDL(const char *number, int n)
{
  int i=0;
  SDLIST *sdl=sdltop;
  while(sdl)
  {
    if(NumberMatch(sdl->number, number))
    {
      if(i==n)
	return sdl;
      i++;
    }
    sdl=(SDLIST *)sdl->next;
  }
  return 0;
}

SDLIST *SmsData::FilterFindSDL(WSHDR *str, int n)
{
  int i=0;
  SDLIST *sdl=sdltop;
  while(sdl)
  {
    if(wstrstr(sdl->text, str))
    {
      if(i==n)
	return sdl;
      i++;
    }
    sdl=(SDLIST *)sdl->next;
  }
  return 0;
}


int SmsData::FilterGetCount(void)
{
  //GetCPUClock();
  switch(CFG_FILTEROP)
  {
  case FILTER_ALL:
    return (GetSMSCount(0));
  case FILTER_NEW:
    return (GetSMSCount(TYPE_IN_N));
  case FILTER_DAT:
    return (GetSMSCount(0, 0));
  case FILTER_FILE:
    return (GetSMSCount(ISFILE, 0));
  case FILTER_NUM:
    return (FilterGetCount(CFG_STRORNUM));
  case FILTER_STR:
    {
      WSHDR *ws, wsn;
      unsigned short wsb[64];
      ws=CreateLocalWS(&wsn, wsb, 64);
      utf8_2ws(ws, CFG_STRORNUM, 64);
      return (FilterGetCount(ws));
    }
  default:
    return 0;
  }
}


int SmsData::FilterGetCount(const char *number)
{
  int i=0;
  SDLIST *sdl=sdltop;
  while(sdl)
  {
    if(NumberMatch(sdl->number, number))
    {
      i++;
    }
    sdl=(SDLIST *)sdl->next;
  }
  return i;
}

int SmsData::FilterGetCount(WSHDR *str)
{
  int i=0;
  SDLIST *sdl=sdltop;
  while(sdl)
  {
    if(wstrstr(sdl->text, str))
    {
      i++;
    }
    sdl=(SDLIST *)sdl->next;
  }
  return i;
}


SDLIST *SmsData::FilterFindNext(SDLIST *sdl)
{
  if(!sdl) return 0;
  switch(CFG_FILTEROP)
  {
  case FILTER_ALL:
    return (FindNextSDL(sdl, 0));
  case FILTER_NEW:
    return (FindNextSDL(sdl, TYPE_IN_N));
  case FILTER_DAT:
    sdl=(SDLIST *)sdl->next;
    while(sdl)
    {
      if(!(sdl->msg_prop&ISFILE)) return sdl;
      sdl=(SDLIST *)sdl->next;
    }
    return 0;
  case FILTER_FILE:
    sdl=(SDLIST *)sdl->next;
    while(sdl)
    {
      if((sdl->msg_prop&ISFILE)) return sdl;
      sdl=(SDLIST *)sdl->next;
    }
    return 0;
  case FILTER_NUM:
    return (FilterFindNext(sdl, CFG_STRORNUM));
  case FILTER_STR:
    {
      WSHDR *ws, wsn;
      unsigned short wsb[64];
      ws=CreateLocalWS(&wsn, wsb, 64);
      utf8_2ws(ws, CFG_STRORNUM, 64);
      return (FilterFindNext(sdl, CFG_STRORNUM));
    }
  default:
    return 0;
  }
}
SDLIST *SmsData::FilterFindNext(SDLIST *sdl, const char *number)
{
  if(!sdl) return 0;
  sdl=(SDLIST *)sdl->next;
  while(sdl)
  {
    if(NumberMatch(sdl->number, number))
      return sdl;
    sdl=(SDLIST *)sdl->next;
  }
  return 0;
}
SDLIST *SmsData::FilterFindNext(SDLIST *sdl, WSHDR *str)
{
  if(!sdl) return 0;
  sdl=(SDLIST *)sdl->next;
  while(sdl)
  {
    if(wstrstr(sdl->text, str))
      return sdl;
    sdl=(SDLIST *)sdl->next;
  }
  return 0;
}

SDLIST *SmsData::FilterFindPrev(SDLIST *sdl)
{
  if(!sdl) return 0;
  switch(CFG_FILTEROP)
  {
  case FILTER_ALL:
    return (FindPrevSDL(sdl, 0));
  case FILTER_NEW:
    return (FindPrevSDL(sdl, TYPE_IN_N));
  case FILTER_DAT:
    sdl=(SDLIST *)sdl->prev;
    while(sdl)
    {
      if(!(sdl->msg_prop&ISFILE)) return sdl;
      sdl=(SDLIST *)sdl->prev;
    }
    return 0;
  case FILTER_FILE:
    sdl=(SDLIST *)sdl->prev;
    while(sdl)
    {
      if((sdl->msg_prop&ISFILE)) return sdl;
      sdl=(SDLIST *)sdl->prev;
    }
    return 0;
  case FILTER_NUM:
    return (FilterFindPrev(sdl, CFG_STRORNUM));
  case FILTER_STR:
    {
      WSHDR *ws, wsn;
      unsigned short wsb[64];
      ws=CreateLocalWS(&wsn, wsb, 64);
      utf8_2ws(ws, CFG_STRORNUM, 64);
      return (FilterFindPrev(sdl, CFG_STRORNUM));
    }
  default:
    return 0;
  }
}
SDLIST *SmsData::FilterFindPrev(SDLIST *sdl, const char *number)
{
  if(!sdl) return 0;
  sdl=(SDLIST *)sdl->prev;
  while(sdl)
  {
    if(NumberMatch(sdl->number, number))
      return sdl;
    sdl=(SDLIST *)sdl->prev;
  }
  return 0;
}
SDLIST *SmsData::FilterFindPrev(SDLIST *sdl, WSHDR *str)
{
  if(!sdl) return 0;
  sdl=(SDLIST *)sdl->prev;
  while(sdl)
  {
    if(wstrstr(sdl->text, str))
      return sdl;
    sdl=(SDLIST *)sdl->prev;
  }
  return 0;
}


int SmsData::MoveToArchive(SDLIST *sdl) //只支持mss
{
  char fullpath[128];
  char folder[128];
//  unsigned int err;
//  MSS_FILE_P2 msf;
  //int /*fin,*/ len, c;
  TTime time;
  TDate date;
  if(!sdl || !(sdl->msg_prop&ISFILE))
    return 0;
  GetDateTime(&date, &time);
  strcpy(folder, main_folder);
  //len=strlen(folder);
  //c=folder[len-1];
  //if(c!='\\' && c!='/')
  //{
  //  folder[len]='\\';
  //  folder[len+1]=0;
  //}
  if(!IsDir(folder))
    MkDir(folder);
  strcat(folder, FLDR_ARCHIVE);
  if(!strncmp(sdl->fname, folder, strlen(folder))) //判断是否已经在档案柜文件夹中
    return 0;
  if(!IsDir(folder))
    MkDir(folder);
  if(strlen(sdl->time)>4)
  {
    strcpy(fullpath, "20");
    strncat(fullpath, sdl->time, 5);
    fullpath[7]='\\';
    fullpath[8]='\0';
    //sprintf(fullpath, "20%05s\\", sdl->time);
    StrClearChr(fullpath, '-');
  }
  else sprintf(fullpath, "%04d%02d\\", date.year, date.month); //借用~_~ , 按月份存储
  strcat(folder, fullpath);
  if(!IsDir(folder))
    MkDir(folder);
  switch(sdl->type)
  {
  case TYPE_DRAFT:
    strcat(folder, FLDR_DRAFT);
    break;
  case TYPE_SENT:
    strcat(folder, FLDR_SENT);
    break;
  case TYPE_IN_N:
  case TYPE_IN_R:
  case TYPE_IN_ALL:
    strcat(folder, FLDR_IN);
    break;
  default:
    strcat(folder, FLDR_UNK);
    break;
  }
  if(!IsDir(folder))
    MkDir(folder);
  if(!GetFilePathSDL(sdl, folder, fullpath, FTYPE_MSS))
    return 0;
  if (sdl->fname)
  {
    if(FMove(sdl->fname, fullpath))
    {
      DeleteSDL(sdl);
      return 1;
    }
  }
  return 0;
}

int SmsData::GetFilePathSDL(SDLIST *sdl, char *folder, char *filepath, int ftype)
{
  int hasname;
  WSHDR *wname, nm;
  unsigned short nmb[64];
  char sname[65];
  char temp[128];
  TTime time;
  TDate date;
  int i=0;
  GetDateTime(&date, &time);
  wname=CreateLocalWS(&nm, nmb, 64);
  if(strlen(sdl->number))
  {
    if(!ADRLST->FindName(wname, sdl->number))
    {
      hasname=0;
    }
    else
    {
      hasname=1;
      ws_2str(wname, sname, 64);
    }
  }
  else
  {
    hasname=1;
    strcpy(sname, "Unk");
  }
  if(strlen(sdl->time))
  {
    snprintf(filepath, 128, "%s_%s", (hasname)?sname:sdl->number, sdl->time/*, (ftype==FTYPE_MSS)?"mss":"txt"*/);
  }
  else
    snprintf(filepath, 128, "%s_%02d-%02d-%02d %02d%02d%02d", (hasname)?sname:sdl->number,
	    date.year%2000,
	    date.month,
	    date.day,
	    time.hour,
	    time.min,
	    time.sec
	      );
  StrClearChr(filepath, ':');
  StrClearChr(filepath, '*');
  StrClearChr(filepath, '?');
  StrClearChr(filepath, '<');
  StrClearChr(filepath, '>');
  StrClearChr(filepath, '|');
  StrClearChr(filepath, '\\');
  StrClearChr(filepath, '/');
  strcpy(temp, folder);
  strcat(temp, filepath);
  strcat(temp, (ftype==FTYPE_MSS)?".mss":".txt");
  if(!IsFileExist(temp))
  {
    strcpy(filepath, temp);
    return 1;
  }
  while(i<MAX_FILE)
  {
    sprintf(temp, "%s%s_%04d%s", folder, filepath, i, (ftype==FTYPE_MSS)?".mss":".txt");
    if(!IsFileExist(temp))
    {
      strcpy(filepath, temp);
      return 1;
    }
    i++;
  }
  return 0;
}

int SmsData::MoveAllToArchive(void)
{
  int res=0;
  SDLIST *sdx;
  SDLIST *sdl=this->sdltop;
  while(sdl)
  {
    sdx=(SDLIST *)sdl->next;
    if(MoveToArchive(sdl))
    {
      res++;
      if(res%4) SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
    }
    sdl=sdx;
  }
  return res;
}

void SmsData::MoveAllToArchiveBG(SmsData *data)
{
  char msgt[64];
  int res=data->MoveAllToArchive();
  sprintf(msgt, LGP->lgp.LGP_MOVE_MSSARCHIVER_N,res);
  ShowMSG(1, (int)msgt);
}




SDLIST * SmsData::FindLastNew(void)
{
  SDLIST *sdl=this->sdltop;
  while(sdl)
  {
    if(sdl->type==TYPE_IN_N)
      return sdl;
    sdl=sdl->next;
  }
  return 0;
}
/*
int SmsData::ExportText(SDLIST *sdl)
{
	if(!sdl)
		return 0;
	char *buf;
	char folder[128];
	char filepath[128];
	char sname[64];
	int len;
	int c;
	int fin;
	strcpy(folder, CFG_MAIN_FOLDER);
	if(!(len=strlen(folder)))
		return 0;
	c=folder[len-1];
	if(c!='\\' && c!='/')
	{
		folder[len]='\\';
		folder[le]='\0';
	}
	if(!IsDir(folder))
		MkDir(folder);
	strcat(folder, "Text\\");
	if(!IsDir(folder))
		MkDir(folder);
	if(GetFilePathSDL(sdl, folder, filepath, FTYPE_TXT))
		return 0;
	if((fin=FOpen(filepath, A_BIN+A_WriteOnly+A_Create+A_Truncate, P_WRITE))==-1)
		return 0;
	len=sdl->text->wsbody[0]*3+4;
	buf=new char[len];
	buf[0]=0xEF;
	buf[1]=0xBB;
	buf[2]=0xBF;
	if(FWrite(fin, buf, 3)!=3)
	{
		delete buf;
		return 0;
	}
	ws_2utf8(sdl->text, buf, len);
}*/

const char *utf8_hdr="\xEF\xBB\xBF";
int SmsData::ExportAllToText()
{
  int fin;
  int res=0;
  //int c;
  int len;
  int utf8_res_len;
  char *buf;
  char folder[128];
  char filename[128];
  char temp[256];
  char sname[64];
  TTime time;
  TDate date;
  SDLIST *sdl;
  strcpy(folder, main_folder);
  //if(!(len=strlen(folder)))
  //  return 0;
  //c=folder[len-1];
  //if(c!='\\' && c!='/')
  //{
  //  folder[len++]='\\';
  //  folder[len]='\0';
  //}
  if(!IsDir(folder))
    MkDir(folder);
  strcat(folder, "Text\\");
  if(!IsDir(folder))
    MkDir(folder);
  GetDateTime(&date, &time);
  sprintf(filename, "%s%04d%02d%02d_%02d%02d.txt",
    folder,
    date.year,
    date.month,
    date.day,
    time.hour,
    time.min);
  if(IsFileExist(filename))
    return 0;
  if((fin=FOpen(filename, A_BIN+A_WriteOnly+A_Create+A_Truncate, P_WRITE))==-1)
    return 0;
  if(FWrite(fin, utf8_hdr, 3)!=3)
  {
    FClose(fin);
    return 0;
  }
  sdl=this->sdltop;
  buf=new char[MAX_TEXT*3];
  while(sdl)
  {
    CLIST *cl;
    if((cl=ADRLST->FindCList(sdl->number))
      && cl->name
      )
    {
      ws_2utf8(cl->name, sname, &utf8_res_len, 64);
    }
    else
    {
      strcpy(sname, sdl->number);
    }
    sprintf(temp, "%s: %s\r\n%s: %s\r\n%s: %s\r\n%s:\r\n",
      (sdl->type==TYPE_SENT||sdl->type==TYPE_DRAFT)?STR_TO_UTF8:STR_FROM_UTF8,
      sname,
      STR_NUMBER_UTF8,
      sdl->number,
      STR_TIME_UTF8,
      (strlen(sdl->time))?sdl->time:STR_UNK_UTF8,
      STR_TEXT_UTF8
      );
    len=strlen(temp);
    if(FWrite(fin, temp, len)!=len)
      break;
    ws_2utf8(sdl->text, buf, &utf8_res_len, MAX_TEXT*3);
    strcat(buf, "\r\n\r\n");
    len=strlen(buf);
    if(FWrite(fin, buf, len)!=len)
      break;
    res++;
    sdl=sdl->next;
  }
  delete buf;
  FClose(fin);
  return res;
}

void SmsData::ExportAllToTextBG(SmsData *smsdata)
{
  char msgt[64];
  int res=smsdata->ExportAllToText();
  sprintf(msgt, LGP->lgp.LGP_EXPORT_N, res);
  ShowMSG(1, (int)msgt);
}

int SmsData::DeleteAllMss()
{
  int res=0;
  SDLIST *s0;
  SDLIST *sdl=this->sdltop;
  while(sdl)
  {
    s0=sdl->next;
    if(
      (sdl->msg_prop&ISFILE)
      && sdl->fname
      && FDelete(sdl->fname)
      )
    {
      DeleteSDL(sdl);
      res++;
      if(res%4) SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
    }
    sdl=s0;
  }
  return res;
}

void SmsData::DeleteAllMssBG(SmsData *smsdata)
{
  char msgt[64];
  int res=smsdata->DeleteAllMss();
  sprintf(msgt, LGP->lgp.LGP_DEL_N, res);
  ShowMSG(1, (int)msgt);
}
