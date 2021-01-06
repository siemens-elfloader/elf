#include "..\..\inc\swilib.h"
#include "sms_dat.h"
#include "adrList.h"
#include "language.h"
#include "config_data.h"

#include "MySMSYS_ipc.h"

#include "main.h"
#include "string_works.h"
#include "NewDatReader.h"


#include "Filter.h"
SMS_DATA *sdltop=0;

void delSDList(SMS_DATA *sdl)
{
	SMS_DATA *sdn;
	SMS_DATA *sdp;
	if(sdl)
	{
		LockSched();
		sdn=sdl->next;
		sdp=sdl->prev;
		if(sdl==sdltop)
			sdltop=sdn;
		if(sdn)
			sdn->prev=sdp;
		if(sdp)
			sdp->next=sdn;
		UnlockSched();
		if((sdl->isfile==1)&&(sdl->fname!=0))
			mfree(sdl->fname);
		if(sdl->SMS_TEXT)
			FreeWS(sdl->SMS_TEXT);
		mfree(sdl);
	}
}

void freeSDList(void)
{
	SMS_DATA *sdl;
	LockSched();
	sdl=sdltop;
	sdltop=0;
	UnlockSched();
	while(sdl)
	{
		SMS_DATA *sdlx;
		sdlx=sdl;
		sdl=sdl->next;
		if((sdlx->isfile==1)&&(sdlx->fname!=0))
			mfree(sdlx->fname);
		if(sdlx->SMS_TEXT)
			FreeWS(sdlx->SMS_TEXT);
		mfree(sdlx);
	}
}

int getCountByType(int type) //0, all
{
  int i=0;
  SMS_DATA *sdl=sdltop;
  if(type>0&&type<5)
  {
    while(sdl)
    {
      if(sdl->type==type)
	i++;
      sdl=sdl->next;
    }
  }
  else if(type==TYPE_IN_ALL)
  {
    while(sdl)
    {
      if((sdl->type==TYPE_IN_R)||(sdl->type==TYPE_IN_N)||(sdl->type==TYPE_IN_ALL))
	i++;
      sdl=sdl->next;
    }
  }
  else if(type==TYPE_FILTER)
  {
    return (FilterGetCountSDL());
  }
  else
  {
    while(sdl)
    {
      i++;
      sdl=sdl->next;
    }
  }
  return i;
}


int GetCountByIsFileType(int isfile, int type) //0, all
{
  int i=0;
  SMS_DATA *sdl=sdltop;
  if(type>0&&type<5)
  {
    while(sdl)
    {
      if((sdl->type==type) && sdl->isfile==isfile)
	i++;
      sdl=sdl->next;
    }
  }
  else if(type==TYPE_IN_ALL)
  {
    int t;
    while(sdl)
    {
      t=sdl->type;
      if(((t==TYPE_IN_R)||(t==TYPE_IN_N)||(t==TYPE_IN_ALL)) && sdl->isfile==isfile)
	i++;
      sdl=sdl->next;
    }
  }
  else
  {
    while(sdl)
    {
      if(sdl->isfile==isfile)
	i++;
      sdl=sdl->next;
    }
  }
  return i;
}

SMS_DATA *getSMSDataByType(int n, int type)//0, all
{
	int i=0;
	SMS_DATA *sdl=sdltop;
	if(type>0&&type<5)
	{
		while(sdl)
		{
			if((i==n)&&(sdl->type==type))
				return sdl;
			if(sdl->type==type)
				i++;
			sdl=sdl->next;
		}
	}
	else if(type==TYPE_IN_ALL)
	{
		while(sdl)
		{
			if((i==n)&&((sdl->type==TYPE_IN_R)||(sdl->type==TYPE_IN_N)||(sdl->type==TYPE_IN_ALL)))
				return sdl;
			if((sdl->type==TYPE_IN_R)||(sdl->type==TYPE_IN_N)||(sdl->type==TYPE_IN_ALL))
				i++;
			sdl=sdl->next;
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
			sdl=sdl->next;
			i++;
		}
	}
	return 0;
}

int getSDPos(SMS_DATA *sd)
{
	SMS_DATA *sdl=sdltop;
	int i=0;
	if(!sdl)
		return -1;
	while(sdl->next) //goto last
		sdl=sdl->next;
	while(sdl)
	{
		if(sdl==sd)
			return i;
		sdl=sdl->prev;
		i++;
	}
	return -1;
}

void Hex2Num(char *hex, char *num, int len)
{
	int c;
	int i=0,j;
	char *p=hex;
	len--;
	if(*p==0x91)
	{
		num[i++]='+';
	}
	p++;
	for(j=0;j<len;j++)
	{
		c=p[j]%0x10;
		if(c>=0&&c<=9)
			num[i++]=c+'0';
		else
			break;
		c=p[j]/0x10;
		if(c>=0&&c<=9)
			num[i++]=c+'0';
		else
			break;
	}
	num[i]=0;
}

void Add2WS(char *data, char *wsbody, int len)
{
	int i;
	for(i=0;i<len;i+=2)
	{
		wsbody[i+2]=data[i+1];
		wsbody[i+3]=data[i];
	}
	unsigned short *p=(unsigned short *)wsbody;
	*p=len/2;
}

int memcmp_wo1(void *d1, void *d2, int n)
{
	int i=0, j=0;
	int c;
	char *s1=(char *)d1;
	char *s2=(char *)d2;
	for(;i<n;i++)
	{
		c=s1[i]-s2[i];
		if((c)&&(j))
			return c;
		if(c)
			j++;
	}
	return 0;
}
char *FindNextPartOfEMS(char *data, int cnt_a, int cnt_n, int sig, char *buf_start, char *buf_end, int cmp_size, int type)
{
	char *d2=buf_start;
	int size=cmp_size;
	if((type==TYPE_IN_N)||(type==TYPE_IN_R))
		size-=3;
	while(d2<buf_end)
	{
		if(!memcmp_wo1(d2, data, size))
		{
			char *p=d2;
			int skip;
			p+=cmp_size+2;
			//skip=*p;
			skip=p[1];
			if(skip==8)
				skip=6;
			else
				skip=5;
			if((p[skip-2]==sig)&&(p[skip-1]==cnt_a)&&(p[skip]==cnt_n+1))
				return d2;
		}
		d2+=sizeof(PDU);
	}
	return 0;
}

int IsPartOfEMS(char *data) //return 1: first, 0xFF: sms, 0xFE: last part of ems
{
	int c, isems, isplus, isin, skip=0;
	char *p=data;
	if(*p++!=0x11)
		return 0;
	
	if(*p++!=0x11)
		return 0;

	if((c=*p++)==0)
		return 0;
		
	if((c==0x01)||(c==0x03)) isin=1;
	else isin=0;
		
	c=*p++; //sms center
	p+=c;
	c=*p++;
	if((c>>4)%2) isplus=1;
	else isplus=0;
	if((c>>6)%2) isems=1;
	else return 0xFF;
	if(!isin)
		p++;	
	c=*p++;
	if(c%2)
		c=c/2+1;
	else
		c=c/2;
	p+=c+2; //num
	p++; //ttype
	if(isin)
		p+=7; //time ????????????????
	if((isplus)&&(!isin)) p++; //
	p++; //len
	//...text,
	if(isems)
	{
		//skip=*p;
			skip=p[1];
			if(skip==8)
				skip=6;
			else
				skip=5;
		//if(p[skip]!=1) //非EMS 的开头部分
		//	return 1;
		if(p[skip]==p[skip-1])
			return 0xFE;
		return (p[skip]);
	}
	return 0;
}

void GetEMSText(char *data, WSHDR *text, int cnt_a, int cnt_n, int type, char *buf_start, char *buf_end)
{
	int c;
	int ttype;
	int isems;
	int isplus;
	int skip=0, cmp_size=0;
	char *p, *p2=0, *ems_next=0;
	WSHDR wsloc, *wn;
	unsigned short wsb[150];
	wn=CreateLocalWS(&wsloc,wsb,150);

	p=data;
	if(*p++!=0x11)
		return;
	
	if(*p++!=0x11)
		return;
	if(*p++==0)
		return;
	c=*p++; //sms center
	p+=c;
	c=*p++;
	if((c>>4)%2) isplus=1;
	else isplus=0;
	if((c>>6)%2) isems=1;
	else isems=0;
	if((type==TYPE_OUT)||(type==TYPE_DRAFT)) //out
		p++;
	c=*p++;
	if(c%2)
		c=c/2+2;
	else
		c=c/2+1;
	p+=c+1; //num
	ttype=*p++;
	if((type==TYPE_IN_R)||(type==TYPE_IN_N))
		p+=7; //time

	if(isplus&&((type==TYPE_OUT)||(type==TYPE_DRAFT))) p++; //

	c=*p++;
	//...text,
	if(isems)
	{
		int sk=p[1];
		cmp_size=p-data-2;
		skip=*p;
		p2=p;
		if(ttype==8)
		{
			p+=skip+1;
			c-=skip+1;
		}
		if(sk==8)
			skip=6;
		else
			skip=5;
	}
	if(ttype==0x8)
	{
		Add2WS(p, (char *)wn->wsbody, c);
		wstrcat(text, wn);
	}
	else if(ttype==0x0) //7bit
	{
		GSMTXT_Decode(wn,(void*)p,c*7/8+1, ttype, (void*(*)(int))malloc_adr(),(void(*)(void))mfree_adr());
		if(wslen(wn)>c)
		{
			CutWSTR(wn, c);
		}
		wstrcat(text, wn);
	}
	else
	{
		wsprintf(wn, STR_UNK_TXTT, ttype);
		wstrcat(text, wn);
	}
	if(isems&&(p2)&&(skip)&&(p2[skip]<p2[skip-1]))
	{
		if(cmp_size) ems_next=FindNextPartOfEMS(data, p2[skip-1], p2[skip], p2[skip-2], buf_start, buf_end, cmp_size, type);
		if(ems_next) GetEMSText(ems_next, text, p2[skip-1], p2[skip], type, buf_start, buf_end);
	}
}
/*
const IPC_REQ my_ipc_upd=
{
  my_ipc_name,
  my_ipc_name,
  NULL
};
*/
int ReadAllSmsN(void)
{
  if(!sdltop) return(readAllSMS());
  return 0;
}

int readAllSMS(void)
{
  int n;
  if(is_readall) return 0;
  is_readall=1;
  freeSDList();
  n=NewMsgReader();
  n+=readFile(TYPE_IN_ALL);
  n+=readFile(TYPE_OUT);
  n+=readFile(TYPE_DRAFT);
  new_sms_n=getCountByType(TYPE_IN_N);
  is_readall=0;
  SendSimpleIpcMsg(SMSYS_IPC_SMS_DATA_UPDATE);
  //GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SMS_DATA_UPDATE,&my_ipc_upd);
  return n;
}

//------------------------------------------------------

//write


int newToRead(SMS_DATA *sd)
{
  if(!sd) return 0;
  if(!sd->isfile)
  {
    if(!sd->id) return 0;
    if(SetSmsStatus(sd->id, 1)!=0x3E8) return 0;
  }
  else
  {
    if(NewToRead_File(sd))
    {
#ifdef ELKA
      extern int sli_sta;
      extern void STOP_SLI(void);
      if(!new_sms_n && sli_sta) STOP_SLI();
      return 1;
#endif
    }
    else return 0;
  }
  sd->type=TYPE_IN_R;
  if(new_sms_n>0) new_sms_n--;
#ifdef ELKA
  extern int sli_sta;
  extern void STOP_SLI(void);
  if(!new_sms_n && sli_sta) STOP_SLI();
#endif
  return 1;
}

#define MAX_FILE 10000
//-------------------------------------

#define HEADER	"MySMSYS"
int GetMssPath(char *path, char *folder, TTime *time, TDate *date)
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

int saveFile(WSHDR *ws, char *number, SMS_DATA *sd, int type, int need_reload) //need_reload,0 not, 1 all, 2 this
{
  char path[128];
  TTime time;
  TDate date;
  unsigned int err;
  int f, len, x;
  const char *folder;
  char dir[128];
  SMS_DATA *sdx=0;
  if(type==TYPE_FILTER)
  {
    if(sd) type=sd->type;
    else type=0;
  }
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
  MSS_FILE_P2 *msf=malloc(sizeof(MSS_FILE_P2));
  zeromem(msf, sizeof(MSS_FILE_P2));
  GetDateTime(&date, &time);
  if(!isdir(CFG_MAIN_FOLDER, &err))
    mkdir(CFG_MAIN_FOLDER, &err);
  strcpy(dir, CFG_MAIN_FOLDER);
  if((len=strlen(dir))<=0) return 0;
  x=dir[len-1];
  if((x!='\\')&&(x!='/'))
  {
    dir[len]='\\';
    dir[len+1]=0;
  }
  strcat(dir, folder);
  if(!isdir(dir, &err))
    mkdir(dir, &err);
  if(type==TYPE_DRAFT && sd && sd->type==TYPE_DRAFT && sd->isfile && sd->fname)
    strcpy(path, sd->fname); 
  else if(!GetMssPath(path, dir, &time, &date))
    return 0;
  if((f=fopen(path, A_BIN+A_WriteOnly+A_Create+A_Truncate, P_WRITE, &err))<0)
  {
    mfree(msf);
    return 0;
  }
  strcpy(msf->header, ELFNAME);
  strncpy(msf->number, number, 32);
  msf->type=type;
  msf->version=MSS_VERSION;
  //如果是来短信,直接使用短信中的时间保存
  if(((type==TYPE_IN_N)||(type==TYPE_IN_R)||(type==TYPE_IN_ALL))
     &&(sd!=0)
       &&(strlen(sd->Time)))
  {
    strcpy(msf->time, sd->Time);
  }
  else
    sprintf(msf->time, "%02d-%02d-%02d %02d:%02d:%02d", 
	    date.year%2000, // ? //2008 ->08
	    date.month, date.day,
	    time.hour, time.min,
	    time.sec);
  if(fwrite(f, msf, sizeof(MSS_FILE_P2), &err)!=sizeof(MSS_FILE_P2))
  {
    mfree(msf);
    fclose(f, &err);
    return 0;
  }
  fwrite(f, ws->wsbody, (ws->wsbody[0]+1)*2, &err);
  fclose(f, &err);
  mfree(msf);
  if(need_reload==1) readAllSMS();
  else if(need_reload==2)
  {
    //int ReadMSS(char *fname, SMS_DATA *sd)
    sdx=AllocSD();
    if(ReadMSS(path, sdx))
    {
      LockSched();
      AddToSdlByTime(sdx);
      UnlockSched();
      return ((int)sdx);
    }
    else FreeSdOne(sdx);
  }
  return 1;
}

//SMS_DATA *AllocSD(void);
//void AddToSdlByTime(SMS_DATA *sd);

int readFile(int type)
{
  unsigned int err;
//  int fp;
  const char *folder;
  char dir[128];
  char fullpath[128];
  int n=0/*, wlen*/;
  DIR_ENTRY de;
  int len, x;
  SMS_DATA *sdx;
  //WSHDR *ws, wsn;
  //unsigned short wsb[MAX_TEXT];
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
  strcpy(dir, CFG_MAIN_FOLDER);
  if((len=strlen(dir))<=0) return 0;
  x=dir[len-1];
  if((x!='\\')&&(x!='/'))
  {
    dir[len]='\\';
    dir[len+1]=0;
  }
  strcat(dir, folder);
  if(!isdir(dir, &err))
    return 0;
  strcat(dir, "*.mss");
  //ws=CreateLocalWS(&wsn, wsb, MAX_TEXT);
  if(FindFirstFile(&de, dir, &err))
  {
    do
    {
//      char *buf=malloc((de.file_size+3)&(~3));
      strcpy(fullpath, de.folder_name);
      if((len=strlen(fullpath))<=0) continue;
      if(fullpath[len-1]!='\\'&&fullpath[len-1]!='/')
      {
	fullpath[len++]='\\';
	fullpath[len]='\0';
      }
      strcat(fullpath, de.file_name);
      sdx=AllocSD();
      if(ReadMSS(fullpath, sdx))
      {
	n++;
	LockSched();
	AddToSdlByTime(sdx);
	UnlockSched();
	if(!(n%4)) SendSimpleIpcMsg(SMSYS_IPC_SMS_DATA_UPDATE);//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SMS_DATA_UPDATE,&my_ipc_upd);
      }
      else FreeSdOne(sdx);
    }
    while(FindNextFile(&de, &err));
  }
  FindClose(&de, &err);
  if((n%4)) SendSimpleIpcMsg(SMSYS_IPC_SMS_DATA_UPDATE);//GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SMS_DATA_UPDATE,&my_ipc_upd);
  return n;
}

int deleteFile(SMS_DATA *sd, int need_reload)
{
	if((sd!=0)&&(sd->isfile==1)&&(sd->fname!=0))
	{
		unsigned int err;
		unlink(sd->fname, &err);
		if(need_reload)
			return(readAllSMS());
		if(sd->type==TYPE_IN_N && new_sms_n) new_sms_n--;
		return 1;
	}
	return 0;
}

int deleteDat(SMS_DATA *sd, int need_reload)
{
	short cnt;
	if((sd==0)||(sd->isfile)||(sd->id==0))
		return 0;
	//extern int DeltetSmsNew(int index, short *del_cnt);
	//if(DeltetSmsNew(sd->id, &cnt)!=0x3E8)
	if(DeleteSMS(sd->id, &cnt)!=0x3E8)
		return 0;
	if(need_reload)
		return (readAllSMS());
	return 1;
}

/*-----------------------------------------------------------*/
// new reader
#define MAX_DAT 100
typedef struct
{
	void *next;
	void *prev;
	int type;
	int cnt;
	int isused;
	char number[32];
	char time[32];
	WSHDR *text;
}EMS_DATA;

typedef struct
{
	short index;
	short unk0;
	int opmsg_id;
	short is_xms;
	short unk1;
	short unk2;
	short unk3;
}EMS_INDEX;

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

void AddToEDL(EMS_DATA **edltop)
{
	EMS_DATA *edl=malloc(sizeof(EMS_DATA));
	zeromem(edl, sizeof(EMS_DATA));
	edl->text=AllocWS(MAX_TEXT);
	if(!(*edltop))
		(*edltop)=edl;
	else
	{
		EMS_DATA *edx=(*edltop);
		edl->next=edx;
		(*edltop)=edl;
		edx->prev=edl;
	}
}

void FreeEDL(EMS_DATA **edltop)
{
	EMS_DATA *edl=(*edltop);
	(*edltop)=0;
	while(edl)
	{
		EMS_DATA *edlx=edl->next;;
		FreeWS(edl->text);
		mfree(edl);
		edl=edlx;
	}
}
void DoSMS(SMS_DATA *sdl, char *data)
{
	int c;
	int ttype;
	int isplus;
	char *p;
	p=data;
	if(*p++!=0x11)
		return;
	
	if(*p++!=0x11)
		return;
	c=*p++;
	if(!c)
		return;

	switch(c)
	{
	case 0x01:
		sdl->type=TYPE_IN_R;
		break;
	case 0x03:
		sdl->type=TYPE_IN_N;
		break;
	case 0x05:
		sdl->type=TYPE_OUT;
		break;
	case 0x07:
		sdl->type=TYPE_DRAFT;
		break;
	default:
		sdl->type=TYPE_UNK;
		wsprintf(sdl->SMS_TEXT, STR_UNK_TYPE, c);
		return; //back 
	}
	
	c=*p++; //sms center
	p+=c;
	c=*p++;
	if((c>>4)%2) isplus=1;
		else isplus=0;
	if((sdl->type==TYPE_OUT)||(sdl->type==TYPE_DRAFT)) //out
	{
		p++;
	}
	c=*p++;
	if(c)
	{
		if(c%2)
			c=c/2+2;
		else
			c=c/2+1;
		Hex2Num(p, sdl->Number, c);
	}
	else
	{
		c=1;
		sdl->Number[0]=0;
	}
	p+=c+1; //num
	ttype=*p++;
	if((sdl->type==TYPE_IN_R)||(sdl->type==TYPE_IN_N))
	{
		char *pp=sdl->Time;
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
	if(isplus&&((sdl->type==TYPE_OUT)||(sdl->type==TYPE_DRAFT))) p++; //
	c=*p++;
	//...text,
	if(ttype==0x8)
	{
		Add2WS(p, (char *)(sdl->SMS_TEXT->wsbody), c);
	}
	else if(ttype==0x0) //7bit
	{
		GSMTXT_Decode(sdl->SMS_TEXT,(void*)p,c*7/8+1, ttype, (void*(*)(int))malloc_adr(),(void(*)(void))mfree_adr());
		if(wslen(sdl->SMS_TEXT)>c)
		{
			CutWSTR(sdl->SMS_TEXT, c);
		}
	}
	else 
	{
		wsprintf(sdl->SMS_TEXT, STR_UNK_TXTT, ttype);
	}
}

void DoSMS_E(EMS_DATA *edl, char *data)
{
	int c;
	int ttype;
	int isplus;
	char *p;
	p=data;
	if(*p++!=0x11)
		return;
	
	if(*p++!=0x11)
		return;
	c=*p++;
	if(!c)
		return;

	switch(c)
	{
	case 0x01:
		edl->type=TYPE_IN_R;
		break;
	case 0x03:
		edl->type=TYPE_IN_N;
		break;
	case 0x05:
		edl->type=TYPE_OUT;
		break;
	case 0x07:
		edl->type=TYPE_DRAFT;
		break;
	default:
		edl->type=TYPE_UNK;
		wsprintf(edl->text, STR_UNK_TYPE, c);
		return; //back 
	}
	
	c=*p++; //sms center
	p+=c;
	c=*p++;
	if((c>>4)%2) isplus=1;
		else isplus=0;
	if((edl->type==TYPE_OUT)||(edl->type==TYPE_DRAFT)) //out
	{
		p++;
	}
	c=*p++;
	if(c)
	{
		if(c%2)
			c=c/2+2;
		else
			c=c/2+1;
		Hex2Num(p, edl->number, c);
	}
	else
	{
		c=1;
		edl->number[0]=0;
	}
	p+=c+1; //num
	ttype=*p++;
	if((edl->type==TYPE_IN_R)||(edl->type==TYPE_IN_N))
	{
		char *pp=edl->time;
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
	if(isplus&&((edl->type==TYPE_OUT)||(edl->type==TYPE_DRAFT))) p++; //
	c=*p++;
	//...text,
	if(ttype==0x8)
	{
		Add2WS(p, (char *)(edl->text->wsbody), c);
	}
	else if(ttype==0x0) //7bit
	{
		GSMTXT_Decode(edl->text,(void*)p,c*7/8+1, ttype, (void*(*)(int))malloc_adr(),(void(*)(void))mfree_adr());
		if(wslen(edl->text)>c)
		{
			CutWSTR(edl->text, c);
		}
	}
	else 
	{
		wsprintf(edl->text, STR_UNK_TXTT, ttype);
	}
}

void DoEMS(EMS_DATA *edl, char *data, char *sms_dat_buf_start, char *sms_dat_buf_end)
{
	int c;
	int ttype;
	int isems;
	int isplus;
	int skip=0, cmp_size=0;
	char *p, *p2=0, *ems_next=0;
	p=data;
	if(*p++!=0x11)
		return;
	
	if(*p++!=0x11)
		return;
	c=*p++;
	if(!c)
		return;
	switch(c)
	{
	case 0x01:
		edl->type=TYPE_IN_R;
		break;
	case 0x03:
		edl->type=TYPE_IN_N;
		break;
	case 0x05:
		edl->type=TYPE_OUT;
		break;
	case 0x07:
		edl->type=TYPE_DRAFT;
		break;
	default:
		edl->type=TYPE_UNK;
		wsprintf(edl->text, STR_UNK_TYPE, c);
		return; //back 
	}
	
	c=*p++; //sms center
	p+=c;
	c=*p++;
	if((c>>4)%2) isplus=1;
	else isplus=0;
	if((c>>6)%2) isems=1;
	else return; //is not ems
	if((edl->type==TYPE_OUT)||(edl->type==TYPE_DRAFT)) //out
		p++;
	c=*p++;
	if(c)
	{
		if(c%2)
			c=c/2+2;
		else
			c=c/2+1;
		Hex2Num(p, edl->number, c);
	}
	else
	{
		c=1;
		edl->number[0]=0;
	}
	p+=c+1; //num
	ttype=*p++;
	if((edl->type!=TYPE_OUT)&&(edl->type!=TYPE_DRAFT))
	{
		char *pp=edl->time;
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
	if(isplus&&((edl->type==TYPE_OUT)||(edl->type==TYPE_DRAFT))) p++; //
	c=*p++;
	//...text,
	if(isems)
	{
		int sk;
		cmp_size=p-data-2;
		skip=*p;
		sk=p[1];
		p2=p;
		if(ttype==8)
		{
			p+=skip+1;
			c-=skip+1;
		}
		if(sk==8)
			skip=6;
		else
			skip=5;
	}
	edl->cnt=p2[skip-1];
	if(ttype==0x8)
	{
		Add2WS(p, (char *)(edl->text->wsbody), c);
	}
	else if(ttype==0x0) //7bit
	{
		GSMTXT_Decode(edl->text,(void*)p,c*7/8+1, ttype, (void*(*)(int))malloc_adr(),(void(*)(void))mfree_adr());
		if(wslen(edl->text)>c)
		{
			CutWSTR(edl->text, c);
		}
	}
	else
	{
		wsprintf(edl->text, STR_UNK_TXTT, ttype);
	}
	if(isems&&(p2)&&(skip)&&(p2[skip]<p2[skip-1]))
	{
		if(cmp_size)
		{
			ems_next=FindNextPartOfEMS(data, p2[skip-1], p2[skip], p2[skip-2], sms_dat_buf_start, sms_dat_buf_end, cmp_size, edl->type);
		}
		if(ems_next) GetEMSText(ems_next, edl->text, p2[skip-1], p2[skip], edl->type, sms_dat_buf_start, sms_dat_buf_end);
	}
	
}
void ReadAllEMS(EMS_DATA **edltop, char *sms_dat_buf, char *sms_dat_buf_end)
{
	char *p=sms_dat_buf;
	int i;
	EMS_DATA *edl;
	while(p<sms_dat_buf_end)
	{
		i=IsPartOfEMS(p);
		if(i==1)
		{
			AddToEDL(edltop);
			edl=(*edltop);
			DoEMS(edl, p, sms_dat_buf, sms_dat_buf_end);
		}
		else if(i==0xFF)
		{
			AddToEDL(edltop);
			edl=(*edltop);
			DoSMS_E(edl, p);
		}
		p+=sizeof(PDU);
	}
}

/////////////////////////////////////////////
//NEW LIST
SMS_DATA *AllocSD(void)
{
	SMS_DATA *sd=malloc(sizeof(SMS_DATA));
	zeromem(sd, sizeof(SMS_DATA));
	//sd->SMS_TEXT=AllocWS(MAX_TEXT);
	return sd;
}

void AddToSdlByTime(SMS_DATA *sd)
{
	SMS_DATA *sdp;
	SMS_DATA *sdl=sdltop;
	if(!sd)
		return;
	if(!sdl)
	{
		sdltop=sd;
		return;
	}
	while(sdl)
	{
		if(strcmp(sd->Time, sdl->Time)>=0)
		{
			sdp=sdl->prev;
			if(!sdp)
				sdltop=sd;
			else
				sdp->next=sd;
			sd->prev=sdp;
			sd->next=sdl;
			sdl->prev=sd;
			return;
		}
		sdl=sdl->next;
	}
	sdl=sdltop;
	while(sdl->next) //add to the last;
		sdl=sdl->next;
	sdl->next=sd;
	sd->prev=sdl;
}


SMS_DATA *FindSDByOpmsgId(int opmsg_id)
{
	SMS_DATA *sdl=sdltop;
	while(sdl)
	{
		if(sdl->opmsg_id==opmsg_id)
		{
			return sdl;
		}
		sdl=sdl->next;
	}
	return 0;
}
/*
int SaveAllAsFile(void)
{
	int res=0;
	SMS_DATA *sdl=sdltop;
	while(sdl)
	{
		if((!(sdl->isfile))&&((sdl->id)>0))
		{
			if(saveFile(sdl->SMS_TEXT, sdl->Number, sdl, sdl->type, 0))
			{
				res++;
				deleteDat(sdl, 0);
			}
		}
		sdl=sdl->next;
	}
	readAllSMS();
	return res;
}
*/
SMS_DATA *FindNextByType(SMS_DATA *sdl, int type)
{
  if(!sdl) return 0;
  if((type==TYPE_OUT)||(type==TYPE_DRAFT))
  {
    sdl=sdl->next;
    while(sdl)
    {
      if(sdl->type==type)
	return sdl;
      sdl=sdl->next;
    }
  }
  else if((type==TYPE_IN_ALL)||(type==TYPE_IN_N)||(type==TYPE_IN_R))
  {
    sdl=sdl->next;
    while(sdl)
    {
      if((sdl->type==TYPE_IN_R)||(sdl->type==TYPE_IN_N)||(sdl->type==TYPE_IN_ALL))
	return sdl;
      sdl=sdl->next;
    }
  }
  else if(type==TYPE_FILTER)
  {
    return FindNextFilterSDL(sdl);
  }
  else
  {
    sdl=sdl->next;
    return sdl;
  }
  return 0;
}

SMS_DATA *FindPrevByType(SMS_DATA *sdl, int type)
{
  if(!sdl) return 0;
  if((type==TYPE_OUT)||(type==TYPE_DRAFT))
  {
    sdl=sdl->prev;
    while(sdl)
    {
      if(sdl->type==type)
	return sdl;
      sdl=sdl->prev;
    }
  }
  else if((type==TYPE_IN_ALL)||(type==TYPE_IN_N)||(type==TYPE_IN_R))
  {
    sdl=sdl->prev;
    while(sdl)
    {
      if((sdl->type==TYPE_IN_R)||(sdl->type==TYPE_IN_N)||(sdl->type==TYPE_IN_ALL))
	return sdl;
      sdl=sdl->prev;
    }
  }
  else if(type==TYPE_FILTER)
  {
    return (FindPrevFilterSDL(sdl));
  }
  else
  {
    sdl=sdl->prev;
    return sdl;
  }
  return 0;
}

int ReadMSS(char *fname, SMS_DATA *sd)
{
  unsigned int err;
  int fin;
  int size, js, len=0;
  MSS_FILE_P1 msf1;
  MSS_FILE_P2 msf2;
  int version;
  //WSHDR *ws, wsn;
  //unsigned short wsb[MAX_TEXT];
  if((fin=fopen(fname, A_BIN+A_ReadOnly, P_READ, &err))<0)
    return 0;
//  GetCPUClock();
  size=lseek(fin, 0, S_END, &err, &err);
  lseek(fin, 8, S_SET, &err, &err);
  if(fread(fin, &version, sizeof(int), &err)!=sizeof(int))
    goto EX_BACK0;
  if(version==1)
  {
    js=sizeof(MSS_FILE_P1);
    if(size<js)
      goto EX_BACK0;
    lseek(fin, 0, S_SET, &err, &err);
    if(fread(fin, &msf1, js, &err)!=js)
      goto EX_BACK0;
    if(strncmp(msf1.header, ELFNAME, 7))
      goto EX_BACK0; 
    strcpy(sd->Time, msf1.time);
    strcpy(sd->Number, msf1.number);
  }
  else if(version==2)
  {
    js=sizeof(MSS_FILE_P2);
    if(size<js)
      goto EX_BACK0;
    lseek(fin, 0, S_SET, &err, &err);
    if(fread(fin, &msf2, js, &err)!=js)
      goto EX_BACK0;
    if(strncmp(msf2.header, ELFNAME, 7))
      goto EX_BACK0; 
    strcpy(sd->Time, msf2.time);
    strcpy(sd->Number, msf2.number);
    sd->type=msf2.type;
  }
  else goto EX_BACK0;
  //ws=CreateLocalWS(&wsn, wsb, MAX_TEXT);
  if(fread(fin, &len, 2, &err)!=2)
    goto EX_BACK0;
  sd->SMS_TEXT=AllocWS(len);
  if(fread(fin, sd->SMS_TEXT->wsbody+1, len*2, &err)!=len*2)
    goto EX_BACK0;
  sd->SMS_TEXT->wsbody[0]=len;
  //if(fread(fin, ws->wsbody, size-js, &err)!=(size-js))
  //  goto EX_BACK0;
  fclose(fin, &err);
//  if(!(len=wstrlen(ws)))
//    len=1;
//  sd->SMS_TEXT=AllocWS(len);
//  wstrcpy(sd->SMS_TEXT, ws);
  sd->isfile=1;
  sd->fname=malloc(128);
  strcpy(sd->fname, fname);
  return 1;
EX_BACK0:
  fclose(fin, &err);
  return 0;
}

void FreeSdOne(SMS_DATA *sd)
{
	if(sd->SMS_TEXT)
		FreeWS(sd->SMS_TEXT);
	if(sd->fname)
		mfree(sd->fname);
	mfree(sd);
}

SMS_DATA *SdCopyOne(SMS_DATA *sdx)
{
	SMS_DATA *sd;
	if(!sdx)
		return 0;
	sd=malloc(sizeof(SMS_DATA));
	memcpy(sd, sdx, sizeof(SMS_DATA));
	if(sdx->fname)
	{
		sd->fname=malloc(128);
		strcpy(sd->fname, sdx->fname);
	}
	if(sdx->SMS_TEXT)
	{
		int len=wstrlen(sdx->SMS_TEXT);
		if(!len) len=1;
		sd->SMS_TEXT=AllocWS(len);
		wstrcpy(sd->SMS_TEXT, sdx->SMS_TEXT);
	}
	else
	  sd->SMS_TEXT=AllocWS(1);
	return sd;
}


SMS_DATA *FindSdByTxtTimeNum(WSHDR *ws, char *time, char *num)
{
	SMS_DATA *sdl=sdltop;
	while(sdl)
	{
		if(!wstrncmp_nocase(sdl->SMS_TEXT, ws, ws->wsbody[0])
				&& !strncmp(sdl->Number, num, strlen(num)))
		{
			if(!time || !strlen(time))
				return sdl;
			if(!strncmp(sdl->Time, time, strlen(time)))
				return sdl;
		}
		sdl=sdl->next;
	}
	return 0;
}

int IsSdInList(SMS_DATA *sd)
{
	SMS_DATA *sdl=sdltop;
	while(sdl)
	{
		if(sdl==sd)
			return 1;
		sdl=sdl->next;
	}
	return 0;
}

//-----------------------------------------------
//file works
int IsFileExist(const char *filename)
{
  FSTATS fst;
  unsigned int err;
  if(GetFileStats(filename, &fst, &err)!=-1)
    return 1;
  else
    return 0;
}

void StrClearChr(char *str, int chr)
{
  char *p=str;
  char *t;
  while(*p)
  {
    if(*p==chr)
    {
      t=p;
      while(*t)
      {
	*t=*(t+1);
	t++;
      }
    }
    p++;
  }
}

#define FTYPE_TXT 0
#define FTYPE_MSS 1

int GetFilePathBySd(SMS_DATA *sd, char *folder, char *filepath, int ftype)
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
  if(strlen(sd->Number))
  {
    if(!findNameByNum(wname, sd->Number))
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
  if(strlen(sd->Time))
  {
    snprintf(filepath, 128, "%s_%s", (hasname)?sname:sd->Number, sd->Time/*, (ftype==FTYPE_MSS)?"mss":"txt"*/);
  }
  else
    snprintf(filepath, 128, "%s_%02d-%02d-%02d %02d%02d%02d", (hasname)?sname:sd->Number, 
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

int ExportAllToOneTxt_ASCII(char *filename)
{
  SMS_DATA *sdl=sdltop;
  int fin, s_n=0, len;
  unsigned int err;
  char text[MAX_TEXT*2];
  char buf[MAX_TEXT*2+256];
  WSHDR *wname, nm;
  unsigned short nmb[64];
  char sname[65];
  wname=CreateLocalWS(&nm, nmb, 64);
  if(IsFileExist(filename))
    return -1;
  if((fin=fopen(filename, A_WriteOnly+A_Create+A_Truncate, P_WRITE, &err))<0)
    return 0;
  while(sdl)
  {
    s_n++;
    ws_2ascii(sdl->SMS_TEXT, text, MAX_TEXT*2);
    if(!findNameByNum(wname, sdl->Number))
      strcpy(sname, lgp.LGP_UNK_NUM);
    else
      ws_2ascii(wname, sname, 64);
    sprintf(buf, "%s: %s\r\n%s: %s\r\n%s: %s\r\n%s:\r\n%s\r\n\r\n",
	    (sdl->type==TYPE_OUT||sdl->type==TYPE_DRAFT)?lgp.LGP_TO:lgp.LGP_FROM,
	    sname,
	    lgp.LGP_NUMBER,
	    sdl->Number,
	    lgp.LGP_TIME,
	    (strlen(sdl->Time))?sdl->Time:lgp.LGP_UNK,
	    lgp.LGP_TEXT,
	    text);
    len=strlen(buf);
    if(fwrite(fin, buf, len, &err)!=len)
      break;
    sdl=sdl->next;
  }
  fclose(fin, &err);
  return s_n;
}

int ExportOneToTxt_ASCII(SMS_DATA *sd)
{
  char folder[128];
  char fullpath[128];
  int fin, len, c;
  unsigned int err;
  char text[MAX_TEXT*2];
  char buf[MAX_TEXT*2+256];
  WSHDR *wname, nm;
  char sname[65];
  unsigned short nmb[64];
  wname=CreateLocalWS(&nm, nmb, 64);
  strcpy(folder, CFG_MAIN_FOLDER);
  len=strlen(folder);
  c=folder[len-1];
  if(c!='\\' && c!='/')
  {
    folder[len]='\\';
    folder[len+1]=0;
  }
  if(!isdir(folder, &err))
    mkdir(folder, &err);
  strcat(folder, "Text\\");
  if(!isdir(folder, &err))
    mkdir(folder, &err);
  if(!GetFilePathBySd(sd, folder, fullpath, FTYPE_TXT))
    return -1;
  if((fin=fopen(fullpath, A_WriteOnly+A_Create+A_Truncate, P_WRITE, &err))<0)
    return 0;
  ws_2ascii(sd->SMS_TEXT, text, MAX_TEXT*2);
  if(!findNameByNum(wname, sd->Number))
    strcpy(sname, lgp.LGP_UNK_NUM);
  else
    ws_2ascii(wname, sname, 64);
  sprintf(buf, "%s: %s\r\n%s: %s\r\n%s: %s\r\n%s:\r\n%s\r\n",
	  (sd->type==TYPE_OUT||sd->type==TYPE_DRAFT)?lgp.LGP_TO:lgp.LGP_FROM,
	  sname,
	  lgp.LGP_NUMBER,
	  sd->Number,
	  lgp.LGP_TIME,
	  (strlen(sd->Time))?sd->Time:lgp.LGP_UNK,
	  lgp.LGP_TEXT,
	  text);
  len=strlen(buf);
  if(fwrite(fin, buf, len, &err)!=len)
  {
    fclose(fin, &err);
    return 0;
  }
  fclose(fin, &err);
  return 1;
}

//utf8
int ExportAllToOneTxt_UTF8(char *filename)
{
  SMS_DATA *sdl=sdltop;
  int fin, s_n=0, len, utf8_res_len;
  unsigned int err;
  char text[MAX_TEXT*3];
  char buf[MAX_TEXT*3+256];
  WSHDR *wname, nm;
  unsigned short nmb[64];
  char sname[65];
  wname=CreateLocalWS(&nm, nmb, 64);
  if(IsFileExist(filename))
    return -1;
  if((fin=fopen(filename, A_WriteOnly+A_Create+A_Truncate, P_WRITE, &err))<0)
    return 0;
  buf[0]=0xEF;
  buf[1]=0xBB;
  buf[2]=0xBF;
  if(fwrite(fin, buf, 3, &err)!=3)
    return -2;
  while(sdl)
  {
    s_n++;
    ws_2utf8(sdl->SMS_TEXT, text, &utf8_res_len, MAX_TEXT*3);
    if(!findNameByNum(wname, sdl->Number))
      strcpy(sname, STR_UNK_NUM_UTF8);
    else
      ws_2utf8(wname, sname, &utf8_res_len, 64);
    sprintf(buf, "%s: %s\r\n%s: %s\r\n%s: %s\r\n%s:\r\n%s\r\n\r\n",
	    (sdl->type==TYPE_OUT||sdl->type==TYPE_DRAFT)?STR_TO_UTF8:STR_FROM_UTF8,
	    sname,
	    STR_NUMBER_UTF8,
	    sdl->Number,
	    STR_TIME_UTF8,
	    (strlen(sdl->Time))?sdl->Time:STR_UNK_UTF8,
	    STR_TEXT_UTF8,
	    text);
    len=strlen(buf);
    if(fwrite(fin, buf, len, &err)!=len)
      break;
    sdl=sdl->next;
  }
  fclose(fin, &err);
  return s_n;
}

int ExportOneToTxt_UTF8(SMS_DATA *sd)
{
  char folder[128];
  char fullpath[128];
  int fin, len, c, utf8_res_len;
  unsigned int err;
  char text[MAX_TEXT*3];
  char buf[MAX_TEXT*3+256];
  WSHDR *wname, nm;
  char sname[65];
  unsigned short nmb[64];
  wname=CreateLocalWS(&nm, nmb, 64);
  strcpy(folder, CFG_MAIN_FOLDER);
  len=strlen(folder);
  c=folder[len-1];
  if(c!='\\' && c!='/')
  {
    folder[len]='\\';
    folder[len+1]=0;
  }
  if(!isdir(folder, &err))
    mkdir(folder, &err);
  strcat(folder, "Text\\");
  if(!isdir(folder, &err))
    mkdir(folder, &err);
  if(!GetFilePathBySd(sd, folder, fullpath, FTYPE_TXT))
    return -1;
  if((fin=fopen(fullpath, A_WriteOnly+A_Create+A_Truncate, P_WRITE, &err))<0)
    return 0;
  buf[0]=0xEF;
  buf[1]=0xBB;
  buf[2]=0xBF;
  if(fwrite(fin, buf, 3, &err)!=3)
    return -2;
  ws_2utf8(sd->SMS_TEXT, text, &utf8_res_len, MAX_TEXT*3);
  if(!findNameByNum(wname, sd->Number))
    strcpy(sname, STR_UNK_NUM_UTF8);
  else
    ws_2utf8(wname, sname, &utf8_res_len, 64);
  sprintf(buf, "%s: %s\r\n%s: %s\r\n%s: %s\r\n%s:\r\n%s\r\n",
	  (sd->type==TYPE_OUT||sd->type==TYPE_DRAFT)?STR_TO_UTF8:STR_FROM_UTF8,
	  sname,
	  STR_NUMBER_UTF8,
	  sd->Number,
	  STR_TIME_UTF8,
	  (strlen(sd->Time))?sd->Time:STR_UNK_UTF8,
	  STR_TEXT_UTF8,
	  text);
  len=strlen(buf);
  if(fwrite(fin, buf, len, &err)!=len)
  {
    fclose(fin, &err);
    return 0;
  } 
  fclose(fin, &err);
  return 1;
}


#define CHARSET_ASCII 0
#define CHARSET_UTF8 1
int ExportAllToOneTxt(char *filename)
{
  if (CFG_EXPORT_CHARSET==CHARSET_ASCII)
    return (ExportAllToOneTxt_ASCII(filename));
  else if (CFG_EXPORT_CHARSET==CHARSET_UTF8)
    return (ExportAllToOneTxt_UTF8(filename));
  return 0;
}

int ExportOneToTxt(SMS_DATA *sd)
{
  if (CFG_EXPORT_CHARSET==CHARSET_ASCII)
    return (ExportOneToTxt_ASCII(sd));
  else if (CFG_EXPORT_CHARSET==CHARSET_UTF8)
    return (ExportOneToTxt_UTF8(sd));
  return 0;
}


//-------------------------------------
//archive

int MoveToArchive(SMS_DATA *sd)
{
  char fullpath[128];
  char folder[128];
  unsigned int err;
  MSS_FILE_P2 msf;
  int fin, len, c;
  TTime time;
  TDate date;
  GetDateTime(&date, &time);
  strcpy(folder, CFG_MAIN_FOLDER);
  len=strlen(folder);
  c=folder[len-1];
  if(c!='\\' && c!='/')
  {
    folder[len]='\\';
    folder[len+1]=0;
  }
  if(!isdir(folder, &err))
    mkdir(folder, &err);
  strcat(folder, FLDR_ARCHIVE);
  if(!isdir(folder, &err))
    mkdir(folder, &err);
  if(strlen(sd->Time)>4)
  {
    strcpy(fullpath, "20");
    strncat(fullpath, sd->Time, 5);
    fullpath[7]='\\';
    fullpath[8]='\0';
    StrClearChr(fullpath, '-');
  }
  else sprintf(fullpath, "%04d%02d\\", date.year, date.month); //借用~_~ , 按月份存储
  strcat(folder, fullpath);
  if(!isdir(folder, &err))
    mkdir(folder, &err);
  switch(sd->type)
  {
  case TYPE_DRAFT:
    strcat(folder, FLDR_DRAFT);
    break;
  case TYPE_OUT:
    strcat(folder, FLDR_OUT);
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
  if(!isdir(folder, &err))
    mkdir(folder, &err);
  if(!GetFilePathBySd(sd, folder, fullpath, FTYPE_MSS))
    return -1;
  if (sd->isfile && sd->fname)
  {
    fmove(sd->fname, fullpath, &err);
    return 1;
  }
  if((fin=fopen(fullpath, A_BIN+A_WriteOnly+A_Create+A_Truncate, P_WRITE, &err))<0)
    return 0;
  zeromem(&msf, sizeof(MSS_FILE_P2));
  strcpy(msf.header, ELFNAME);
  msf.version=MSS_VERSION;
  msf.type=sd->type;
  strcpy(msf.number, sd->Number);
  if (strlen(sd->Time))
    strcpy(msf.time, sd->Time);
  else
  {
    sprintf(msf.time, "%02d-%02d-%02d %02d:%02d:%02d", 
	    date.year%2000, // ? //2008 ->08
	    date.month, date.day,
	    time.hour, time.min,
	    time.sec);
  }
  if(fwrite(fin, &msf, sizeof(MSS_FILE_P2), &err)!=sizeof(MSS_FILE_P2))
  {
    fclose(fin, &err);
    return 0;
  }
  len=(sd->SMS_TEXT->wsbody[0]+1)*2;
  if (fwrite(fin, sd->SMS_TEXT->wsbody, len, &err)!=len)
  {
    fclose(fin, &err);
    return 0;
  }
  fclose(fin, &err);
  return 1;
}

int MoveAllMssToArchive(void)
{
  int res=0;
  SMS_DATA *sdl=sdltop;
  while(sdl)
  {
    if(sdl->isfile && sdl->fname)
    {
      if(MoveToArchive(sdl)==1)
      {
      	res++;
      }
    }
    sdl=sdl->next;
  }
  readAllSMS();
  return res;
}

int MoveAllToArchive(void)
{
  int res=0;
  SMS_DATA *sdl=sdltop;
  while(sdl)
  {
    if(MoveToArchive(sdl)==1)
    {
      res++;
    }
    if(!sdl->isfile && sdl->id>0)
    {
      deleteDat(sdl, 0);
    }
    sdl=sdl->next;
  }
  readAllSMS();
  return res;
}


void ShowFileErrCode(int code)
{
  if (code==0)
    MsgBoxError(1, (int)lgp.LGP_FILE_FAILED);
  else if (code==-1)
    MsgBoxError(1, (int)lgp.LGP_FILE_EXIST);
}

void DeleteAllMss(void)
{
	SMS_DATA *sdl=sdltop;
	while(sdl)
	{
		if(sdl->isfile && sdl->fname)
			deleteFile(sdl, 0);
		sdl=sdl->next;
	}
	readAllSMS();
}
/*
void DeleteAll(void)
{
	SMS_DATA *sdl=sdltop;
	while(sdl)
	{
		if(sdl->isfile && sdl->fname)
			deleteFile(sdl, 0);
		else if(sdl->id > 0)
			deleteDat(sdl, 0);
		sdl=sdl->next;
	}
	readAllSMS();
}
*/
int CovDatToTxt_ASCII(char *dat_path, char *txt_path)
{
  int fin, ft, size, res=0, len;
  unsigned int err;
  char *buf;
  EMS_DATA *edl=0;
  EMS_DATA *edx;
  char temp[MAX_TEXT*2+256];
  char text[MAX_TEXT*2];
  WSHDR *wname, nm;
  unsigned short nmb[64];
  char sname[65];
  wname=CreateLocalWS(&nm, nmb, 64);
  if(IsFileExist(txt_path))
    return -1;
//  GetCPUClock();
  if((fin=fopen(dat_path, A_BIN+A_ReadOnly, P_WRITE, &err))<0)
    return 0;
  size=lseek(fin, 0, S_END, &err, &err)-2;
  if(!size)
    goto EXIT2;
  lseek(fin, 2, S_SET, &err, &err);
  buf=malloc(size);
  if(fread(fin, buf, size, &err)!=size)
    goto EXIT3;
  fclose(fin, &err);
  ReadAllEMS(&edl, buf, buf+size-sizeof(PDU));
  if(edl)
  {
    edx=edl;
    if((ft=fopen(txt_path, A_WriteOnly+A_Create+A_Truncate, P_WRITE, &err))!=-1)
    {
      while(edx)
      {
	res++;
	ws_2ascii(edx->text, text, MAX_TEXT*2);
	if(!findNameByNum(wname, edx->number))
	  strcpy(sname, lgp.LGP_UNK_NUM);
	else
	  ws_2ascii(wname, sname, 64);
	sprintf(temp, "%s: %s\r\n%s: %s\r\n%s: %s\r\n%s:\r\n%s\r\n\r\n",
		(edx->type==TYPE_OUT||edx->type==TYPE_DRAFT)?lgp.LGP_TO:lgp.LGP_FROM,
		sname,
		lgp.LGP_NUMBER,
		edx->number,
		lgp.LGP_TIME,
		(strlen(edx->time))?edx->time:lgp.LGP_UNK,
		lgp.LGP_TEXT,
		text);
	len=strlen(temp);
	if(fwrite(ft, temp, len, &err)!=len)
	  break;
	edx=edx->next;
      }
      fclose(ft, &err);
    }
  }
  FreeEDL(&edl);
  mfree(buf);
  return res;
EXIT3:
  mfree(buf);
EXIT2:
  fclose(fin, &err);
  return 0;
}

int CovDatToTxt_UTF8(char *dat_path, char *txt_path)
{
  int fin, ft, size, res=0, len, utf8_cov_len;
  unsigned int err;
  char *buf;
  EMS_DATA *edl=0;
  EMS_DATA *edx;
  char temp[MAX_TEXT*3+256];
  char text[MAX_TEXT*3];
  WSHDR *wname, nm;
  unsigned short nmb[64];
  char sname[65];
  wname=CreateLocalWS(&nm, nmb, 64);
  if(IsFileExist(txt_path))
    return -1;
//  GetCPUClock();
  if((fin=fopen(dat_path, A_BIN+A_ReadOnly, P_WRITE, &err))<0)
    return 0;
  size=lseek(fin, 0, S_END, &err, &err)-2;
  if(!size)
    goto EXIT2;
  lseek(fin, 2, S_SET, &err, &err);
  buf=malloc(size);
  if(fread(fin, buf, size, &err)!=size)
    goto EXIT3;
  fclose(fin, &err);
  ReadAllEMS(&edl, buf, buf+size-sizeof(PDU));
  if(edl)
  {
    edx=edl;
    if((ft=fopen(txt_path, A_WriteOnly+A_Create+A_Truncate, P_WRITE, &err))!=-1)
    {
      temp[0]=0xEF;
      temp[1]=0xBB;
      temp[2]=0xBF;
      if(fwrite(ft, temp, 3, &err)==3)
      {
      while(edx)
      {
	res++;
	ws_2utf8(edx->text, text, &utf8_cov_len, MAX_TEXT*3);
	if(!findNameByNum(wname, edx->number))
	  strcpy(sname, STR_UNK_NUM_UTF8);
	else
	  ws_2utf8(wname, sname, &utf8_cov_len, 64);
	sprintf(temp, "%s: %s\r\n%s: %s\r\n%s: %s\r\n%s:\r\n%s\r\n\r\n",
		(edx->type==TYPE_OUT||edx->type==TYPE_DRAFT)?STR_TO_UTF8:STR_FROM_UTF8,
		sname,
		STR_NUMBER_UTF8,
		edx->number,
		STR_TIME_UTF8,
		(strlen(edx->time))?edx->time:STR_UNK_UTF8,
		STR_TEXT_UTF8,
		text);
	len=strlen(temp);
	if(fwrite(ft, temp, len, &err)!=len)
	  break;
	edx=edx->next;
      }
      }
      fclose(ft, &err);
    }
  }
  FreeEDL(&edl);
  mfree(buf);
  return res;
EXIT3:
  mfree(buf);
EXIT2:
  fclose(fin, &err);
  return 0;
}

int CovDatToTxt(char *dat_path, char *txt_path)
{
  if (CFG_EXPORT_CHARSET==CHARSET_ASCII)
    return (CovDatToTxt_ASCII(dat_path, txt_path));
  else if (CFG_EXPORT_CHARSET==CHARSET_UTF8)
    return (CovDatToTxt_UTF8(dat_path, txt_path));
  return 0;
}

SMS_DATA *FindNextMss(SMS_DATA *sd)
{
  char folder[128];
  char filename[128];
  char dir[128];
  char *p;
  unsigned int err;
  int is_find=0, len;
  SMS_DATA *sdx=0;
  DIR_ENTRY de;
  char *pp=sd->fname;
//  GetCPUClock();
  if (!sd || !sd->isfile || !pp)
    return 0;
  if(!(p=strrchr(pp, '\\')) && !(p=strrchr(pp, '/')))
    return 0;
  strncpy(folder, pp, p-pp+1);
  if(!isdir(folder, &err))
    return 0;
  strcpy(filename, p+1);
  strcpy(dir, folder);
  strcat(dir, "*.mss");
  if(FindFirstFile(&de, dir, &err))
  {
    do
    {
      if(is_find)
      {
	strcpy(filename, de.folder_name);
	len=strlen(filename);
	if(filename[len-1]!='\\'&&filename[len-1]!='/')
	{
	  filename[len++]='\\';
	  filename[len]='\0';
	}
	strcat(filename, de.file_name);
	sdx=malloc(sizeof(SMS_DATA));
	zeromem(sdx, sizeof(SMS_DATA));
	if(!ReadMSS(filename, sdx))
	{
	  FreeSdOne(sdx);
	  sdx=0;
	}
	break;
      }
      if(!strcmp(de.file_name, filename))
	is_find=1;
    }while(FindNextFile(&de, &err));
  }
  FindClose(&de, &err);
  return sdx;
}

SMS_DATA *FindPrevMss(SMS_DATA *sd)
{
  char folder[128];
  char filename[128];
  char dir[128];
  char temp[128]={0};
  char *p;
  unsigned int err;
  int len;
  SMS_DATA *sdx=0;
  DIR_ENTRY de;
  char *pp=sd->fname;
//  GetCPUClock();
  if (!sd || !sd->isfile || !pp)
    return 0;
  if(!(p=strrchr(pp, '\\')) && !(p=strrchr(pp, '/')))
    return 0;
  strncpy(folder, pp, p-pp+1);
  if(!isdir(folder, &err))
    return 0;
  strcpy(filename, p+1);
  strcpy(dir, folder);
  strcat(dir, "*.mss");
  if(FindFirstFile(&de, dir, &err))
  {
    do
    {
      if(!strcmp(de.file_name, filename))
      {
	if(!strlen(temp))
	  break;
	strcpy(filename, de.folder_name);
	len=strlen(filename);
	if(filename[len-1]!='\\'&&filename[len-1]!='/')
	{
	  filename[len++]='\\';
	  filename[len]='\0';
	}
	strcat(filename, temp);
	sdx=malloc(sizeof(SMS_DATA));
	zeromem(sdx, sizeof(SMS_DATA));
	if(!ReadMSS(filename, sdx))
	{
	  FreeSdOne(sdx);
	  sdx=0;
	}
	break;
      }
      strcpy(temp, de.file_name);
    }while(FindNextFile(&de, &err));
  }
  FindClose(&de, &err);
  return sdx;
}
