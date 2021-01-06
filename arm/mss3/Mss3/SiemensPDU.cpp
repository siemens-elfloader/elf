#include "include.h"
#include "SiemensPDU.h"

void SiememPDU::Add2WS(char *data, WSHDR *ws, int len)
{
/*  int i;
  int mlen;
  char *p;
  if(!data || !ws) return 0;
  mlen=(ws->maxlen < len)?ws->maxlen : len;
  p=(char *)(ws->wsbody+1);
  for(i=0;i<mlen;i+=2)
  {
    p[i]=data[i+1];
    p[i+1]=data[i];
  }
  ws->wsbody[0]=mlen/2;
  return (mlen/2);*/
  unsigned short c;
  int i=0;
  CutWSTR(ws, 0);
  if(len<2) return;
  if((len&1)) len--;
  while(i<len)
  {
    c=data[i++];
    c<<=8;
    c|=data[i++];
    wsAppendChar(ws, c);
  }
}

void SiememPDU::Hex2Num(char *hex, char *num, int len)
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

void SiememPDU::Bit7Decode(WSHDR *ws, char *pdata, int skip, int len) //big respect to Rst7(LogSms),
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

int SiememPDU::PduDecodeTxt(SDLIST *sd, char *data) //0: fail, 1: successful, //2: unktype
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
  if((sd->type==TYPE_SENT)||(sd->type==TYPE_DRAFT)) //out
  {
    p++;
  }
  c=*p++;
  c=((c&1)?1:0) + (c>>1) +1;

  p+=c+1; //num
  ttype=*p++;
  if((sd->type==TYPE_IN_R)||(sd->type==TYPE_IN_N))
  {
    p+=7; //time
  }
  if(isplus&&((sd->type==TYPE_SENT)||(sd->type==TYPE_DRAFT))) p++; //
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
    Add2WS(p, ws, c);
  }
  else if(ttype==0x0) //7bit
  {
    Bit7Decode(ws, p, skip, c);
    if(wstrlen(ws)>c)
    {
      CutWSTR(ws, c);
    }
  }
  else 
  {
    //sd->msg_prop=sd->msg_prop|ISUNKE;
	GSMTXT_Decode(ws, p, c, ttype, (void *(*)(int))malloc_adr(), (void (*)())mfree_adr());
	if (ws->wsbody[0] == 0)
	{
		wsprintf(ws, STR_UNK_TXTT, ttype);
		sd->msg_prop |= ISUNKE;
	}
	else
	{
		CutWSTR(ws, c);
	}
  }
  wst=sd->text;
  wlen=wstrlen(ws);
  if(wlen)
  {
    if(wst)
    {
      wlen+=wstrlen(wst);
      sd->text=AllocWS(wlen);
      wstrcpy(sd->text, wst);
      wstrcat(sd->text, ws);
      FreeWS(wst);
    }
    else
    {
      sd->text=AllocWS(wlen);
      wstrcpy(sd->text, ws);
    }
  }
  return 1;
}


int SiememPDU::PduDecodeAll(SDLIST *sd, char *data) //0: fail, 1: successful, //2: unktype
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
    sd->type=TYPE_SENT;
    break;
  case 0x07:
    sd->type=TYPE_DRAFT;
    break;
  default:
    sd->type=TYPE_UNK;
    sd->msg_prop=sd->msg_prop|ISUNKT;
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
  if((sd->type==TYPE_SENT)||(sd->type==TYPE_DRAFT)) //out
  {
    p++;
  }
  c=*p++;
  if(c)
  {
    Hex2Num(p, sd->number, c);
    c=((c&1)?1:0) + (c>>1) +1;
  }
  else
  {
    c=1;
    sd->number[0]=0;
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
    char *pp=sd->time;
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
    sd->msg_prop=sd->msg_prop|ISREPORT;
    DoSmsReport(sd, p, ws);
    goto TEND;
  }
  if(isplus&&((sd->type==TYPE_SENT)||(sd->type==TYPE_DRAFT))) p++; //
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
    Add2WS(p, ws, c);
  }
  else if(ttype==0x0) //7bit
  {
    Bit7Decode(ws, p, skip, c);
    sd->msg_prop=sd->msg_prop|IS7BIT;
    if(wstrlen(ws)>c)
    {
      CutWSTR(ws, c);
    }
  }
  else 
  {
    //sd->msg_prop=sd->msg_prop|ISUNKE;
	GSMTXT_Decode(ws, p, c, ttype, (void *(*)(int))malloc_adr(), (void (*)())mfree_adr());
	if (ws->wsbody[0] == 0)
	{
		wsprintf(ws, STR_UNK_TXTT, ttype);
		sd->msg_prop |= ISUNKE;
	}
	else
	{
		CutWSTR(ws, c);
	}
  }
TEND:
  wlen=wstrlen(ws);
  if(!wlen)
    wlen=1;
  sd->text=AllocWS(wlen);
  wstrcpy(sd->text, ws);
  return 1;
}

void SiememPDU::DoSmsReport(SDLIST *sd, char *data, WSHDR *ws)
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
    wsprintf(ws, "%t\r%t: 20%s", LGP->lgp.LGP_MSG_REPORT, LGP->lgp.LGP_MSG_REVEICED, time);
  else
    wsprintf(ws, "%t\r%t: 20%s\r%s (%d)!", LGP->lgp.LGP_MSG_REPORT, LGP->lgp.LGP_TIME, time, LGP->lgp.LGP_UNK_RP_STATUS, status);
}





