/********************************************************************
   (C) Copyright free source ,by Bennie.Joe@Gmail.com  

	filename: 	RepSP.c
	created:	2005-10-1
	author:		Bennie
	
	describe:	replaces provider name with custom format
	history:    2005-06-22 V2
*********************************************************************/
#include "..\inc\swilib.h"

#define UC_XING 0x661F //xing
#define UC_QI 0x671F //qi
#define UC_CHU 0x521D //chu
#define UC_SHI 0x5341 //ʮ
#define UC_ERSHI 0x5EFF //إ
#define UC_SANSHI 0x5345 //ئ
#define UC_ZHENG 0x6B63
//��һ�����������߰˾�ʮإئ
const unsigned short UC_CHARS[12]=
{
  0x65E5,
  0x4E00,
  0x4E8C,
  0x4E09,
  0x56DB,
  0x4E94,
  0x516D,
  0x4E03,
  0x516B,
  0x4E5D,
  0x5341,
  0
  //0x5EFF,
  //0x5345
};
const char weekdays[7][10]=
{
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday",
  "Sunday"
};

const char enmonth[12][10]=
{
  "January",
  "February",
  "March",
  "April",
  "May",
  "June",
  "July",
  "August",
  "September",
  "October",
  "November",
  "December"
};
#pragma swi_number=0x8D
__swi __arm void GetProfileName(WSHDR *ws);

#pragma swi_number=0x41
__swi __arm void GetProvider(WSHDR *ws, int _0);

//#pragma swi_number=0x80DD
//__swi __arm char *RamCurrentTrack(void);
#ifdef ELKA
#define RamTrack1 0xAD2B3D60
#else
#define RamTrack3 0xA892C6B0
#define RamTrack2 0xA89A32F4
#define RamTrack1 0xA899F2BC
#endif
#define MAX_LEN 64 //UNICODE
__arm void GetRepString(WSHDR *pws, const unsigned short *pformat) 
{
  WSHDR *wst, wstn;
  unsigned short wstb[32], *s2, cs;
  const unsigned short *ss;
  TDate date, Ldate;
  TTime time;
  RAMNET *net;
  int z, week, LunarRet, c;
  char *qp;
  wst=CreateLocalWS(&wstn, wstb, 32);
  GetDateTime(&date, &time);
  LunarRet = GetLunarDate(&date, &Ldate);
  week = GetWeek(&date);
  ss=pformat;
  while((ss-pformat)<MAX_LEN && (c=*ss++))
  {
    if(c=='%')
    {
      CutWSTR(wst, 0);
      if((ss-pformat)>=MAX_LEN)
	break;
      switch((z=*ss++))
      {
      case 'y': //������λ��
	wsprintf(wst, "%02d", date.year%100);
	wstrcat(pws, wst);
	break;
      case 'Y': //������λ��
	wsprintf(wst, "%d", date.year);
	wstrcat(pws, wst);
	break;
      case 'M': //������
	wsprintf(wst, "%02d", date.month);
	wstrcat(pws, wst);
	break;
      case 'D': //������
	wsprintf(wst, "%02d", date.day);
	wstrcat(pws, wst);
	break;
      case 'N': //��������
	wsprintf(wst, "%t", GetLunarYearID(Ldate.year));
	wstrcat(pws, wst);
	break;
      case 'n': //������Ф
	wsprintf(wst, "%t", GetLunarAnimal(Ldate.year));
	wstrcat(pws, wst);
	break;
      case 'm': //������
	z=Ldate.month;
	if(LunarRet != 0 )
	{ 
	  if(z == (LunarRet+1))
	    wsAppendChar(wst, 0x95F0);
	  if(z >= (LunarRet+1))
	    --z;
	}
	if(z==1)
	  wsAppendChar(wst, UC_ZHENG);
	else if(z<11)
	  wsAppendChar(wst, UC_CHARS[z]);
	else if(z<13)
	{
	  wsAppendChar(wst, UC_SHI);
	  wsAppendChar(wst, UC_CHARS[z-10]);
	}
	wstrcat(pws, wst);
	break;
      case 'd': //������
	z=Ldate.day;
	if(z<11)
	{
	  wsAppendChar(wst, 0x521D); //��
	  wsAppendChar(wst, UC_CHARS[z]);
	}
	else if(z<21)
	{
	  wsAppendChar(wst, (z==20)?UC_ERSHI:UC_SHI);
	  wsAppendChar(wst, UC_CHARS[z-10]);
	}
	else if(z<31)
	{
	  wsAppendChar(wst, (z==30)?UC_SANSHI:UC_ERSHI);
	  wsAppendChar(wst, UC_CHARS[z-20]);
	}
	wstrcat(pws, wst);
	break;
      case 'H': //ʱ
	wsprintf(wst, "%02d", time.hour);
	wstrcat(pws, wst);
	break;
      case 'F': //��
	wsprintf(wst, "%02d", time.min);
	wstrcat(pws, wst);
	break;
      case 'X': //��������
	wsAppendChar(wst, UC_XING);
	wsAppendChar(wst, UC_QI);
      case 'x': //��д��������
	wsAppendChar(wst, UC_CHARS[(week>5)?0:(week+1)]);
	wstrcat(pws, wst);
	break;
      case 'W': //����Ӣ������
	wsprintf(wst, weekdays[week]);
	wstrcat(pws, wst);
	break;
      case 'w': //��дӢ������
	wsprintf(wst, weekdays[week]);
	CutWSTR(wst, 3);
	wsAppendChar(wst, '.');
	wstrcat(pws, wst);
	break;
      case 'U': //����Ӣ���·�
	wsprintf(wst, enmonth[date.month-1]);
	wstrcat(pws, wst);
	break;
      case 'u': //��дӢ���·�
	wsprintf(wst, enmonth[date.month-1]);
	CutWSTR(wst, 3);
	wsAppendChar(wst, '.');
	wstrcat(pws, wst);
	break;
      case 'P': //�龰ģʽ��
	GetProfileName(wst);
	wstrcat(pws, wst);
	break;
      case 'S': //��Ӫ����
	GetProvider(wst, 0);
	wstrcat(pws, wst);
	break;
      case 'R': //�źŵȼ�
	net=RamNet();
	wsprintf(wst, "%c%d", (net->ch_number>=255)?'=':'-', net->power);
	wstrcat(pws, wst);
	break;
      case 'A': //akku ��ѹv
	z=GetAkku(0,9);
	wsprintf(wst, "%d.%02d", z/1000, (z%1000)/10);
	wstrcat(pws, wst);
	break;
      case 'a': //akku ���� in %
	wsprintf(wst, "%d", *RamCap());
	wstrcat(pws, wst);
	break;
      case 'T': //�����¶� TEV
	z = 3;
	goto TempChange;
      case 't': //����¶� TBA
	z = 1;
TempChange:
	z = (GetAkku(z,3)-0xAAA);
	wsprintf(wst, "%d.%d", z/10, z%10);
	wstrcat(pws, wst);
	break;
      case 'Q': //��ʾ������ID3
	if(GetPlayStatus())
	{
	  qp=(char *)RamTrack1;
#ifndef ELKA
	  if(*qp==0xFB)
	  {
	    qp=(char *)RamTrack2;
	    if(*qp!=0xFB)
	    {
	      if(*qp<0x1F && *(qp-3)!=0xAC) qp+=0xC; //�鿴�����Ի���UNICODE֮���������仯
	    }
	    else qp=(char *)RamTrack3;
	  }
#endif
	  z=qp[0x104];
	  if(z==0x3) //utf8
	    utf8_2ws(wst, qp, 32);
	  else if(z==0x2) //unicode
	  {
	    z=0;
	    s2=(unsigned short *)qp;
	    if(s2[0]==0xFEFF) s2++;
	    while(z<32 && (cs=s2[z++]))
	      wsAppendChar(wst, cs);
	  }
	  else
	    wsprintf(wst, "%t", qp);
	  wstrcat(pws, wst);
	}
	break;
      case 'q': //������״̬
	if((z=GetPlayStatus()))
	{
	  if(z==1)
	    wsAppendChar(pws, 0xE44F); //0xE44F pause
	  else if(z==2)
	    wsAppendChar(pws, 0xE450); //0xE44F play
	}
	break;
      case '%':
	wsAppendChar(pws, '%');
	break;
      case '!':
	wsAppendChar(pws, '\r');
	break;
      case '<':
	wsAppendChar(pws, 0xE01E);
	break;
      case '>':
	wsAppendChar(pws, 0xE01D);
	break;
      case '=':
	wsAppendChar(pws, 0xE01F);
	break;
      case 0:
	goto EXIT_ENTRY;
      case 'z':
	wsAppendChar(pws, 0xE012);
	break;
      case 'Z':
	wsAppendChar(pws, 0xE014);
	break;
      case 'c':
	if((ss-pformat)>=MAX_LEN)
	  goto EXIT_ENTRY;
	z=*ss++;
	if(z>='0' && z<=('0'+24))
	{
	  wsAppendChar(pws, 0xE009);
	  wsAppendChar(pws, z-'0');
	}
	break;
      case 'C':
	if((ss-pformat)>=MAX_LEN)
	  goto EXIT_ENTRY;
	z=*ss++;
	if(z>='0' && z<=('0'+24))
	{
	  wsAppendChar(pws, 0xE008);
	  wsAppendChar(pws, z-'0');
	}
	break;
      default:
	wsAppendChar(pws, z);
	break;
      }
    }
    else
    {
      wsAppendChar(pws, c);
    }
  }
EXIT_ENTRY:
  return;
}

