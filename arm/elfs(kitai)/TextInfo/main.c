#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "TextInfo.h"
#include "local_ipc.h"

#define TMR_SECOND 216

#define word unsigned short
#define uint unsigned int

const char ipc_my_name[]=IPC_TEXTINFO_NAME;
extern void kill_data(void *p, void (*func_p)(void *));

CSM_DESC icsmd;

WSHDR *ws;

typedef struct{
  int enabled;
  RECT rc;
  WSHDR *ws;
  char pen[4];
  char penframe[4];
  unsigned short font;
  unsigned short type;
} TInfo;

typedef struct{
  WSHDR *year;
  WSHDR *monthday;
} TNongLi;

TInfo InfoData[13];
TNongLi NongLi;
 


GBSTMR mytmr;
const IPC_REQ my_ipc={
  ipc_my_name,
  ipc_my_name,
  NULL
};

#pragma segment="ELFBEGIN"
void ElfKiller(void)
{
  kill_data(__segment_begin("ELFBEGIN"),(void (*)(void *))mfree_adr());
}
// ----------------------------------------------------------------------------
 void BSTRAdd(word *pDst, const word * pSrc, int Count)
{
	uint nSize = *pDst, i=1;
	while(*pSrc != '\0' && i<=Count)
		*(pDst+ nSize + i++) = *pSrc++;
	*pDst = nSize+i-1;
}

void GetDayOf(TDate pSt,TNongLi *NongLiData)
{ 
/*天干名称*/
//const char *cTianGan[] = {"甲","乙","丙","丁","戊","己","庚","辛","壬","癸"};
const word cTianGan[] = {0x7532,0x4E59,0x4E19,0x4E01,0x620A,0x5DF1,0x5E9A,0x8F9B,0x58EC,0x7678,0};  
/*地支名称*/
//const char *cDiZhi[] = {"子","丑","寅","卯","辰","巳","午",
//       "未","申","酉","戌","亥"};
const word cDiZhi[] = {0x5B50,0x4E11,0x5BC5,0x536F,0x8FB0,0x5DF3,0x5348,0x672A,0x7533,0x9149,0x620C,0x4EA5,0};
/*属相名称*/
//const char *cShuXiang[] = {"鼠","牛","虎","兔","龙","蛇",
//       "马","羊","猴","鸡","狗","猪"};
const word cShuXiang[] = {0x9F20,0x725B,0x864E,0x5154,0x9F99,0x86C7,0x9A6C,0x7F8A,0x7334,0x9E21,0x72D7,0x732A,0};
/*农历日期名*/
/*const char *cDayName[] = {"*","初一","初二","初三","初四","初五",
       "初六","初七","初八","初九","初十",
       "十一","十二","十三","十四","十五",
       "十六","十七","十八","十九","二十",
       "廿一","廿二","廿三","廿四","廿五",       
       "廿六","廿七","廿八","廿九","三十"};*/
const word cDayName[][2] = {{0x002A},
{0x521D,0x4E00},{0x521D,0x4E8C},{0x521D,0x4E09},
{0x521D,0x56DB},{0x521D,0x4E94},{0x521D,0x516D},{0x521D,0x4E03},
{0x521D,0x516B},{0x521D,0x4E5D},{0x521D,0x5341},{0x5341,0x4E00},
{0x5341,0x4E8C},{0x5341,0x4E09},{0x5341,0x56DB},{0x5341,0x4E94},
{0x5341,0x516D},{0x5341,0x4E03},{0x5341,0x516B},{0x5341,0x4E5D},
{0x4E8C,0x5341},{0x5EFF,0x4E00},{0x5EFF,0x4E8C},{0x5EFF,0x4E09},
{0x5EFF,0x56DB},{0x5EFF,0x4E94},{0x5EFF,0x516D},{0x5EFF,0x4E03},
{0x5EFF,0x516B},{0x5EFF,0x4E5D},{0x4E09,0x5341},{0,0}};
/*农历月份名*/
/*const char *cMonName[] = {"*","正","二","三","四","五","六",
       "七","八","九","十","十一","腊"};*/
const word cMonName[] = {0x002A,0x6B63,0x4E8C,0x4E09,0x56DB,0x4E94,0x516D,0x4E03,0x516B,0x4E5D,0x5341,0x4E00,0x814A,0};
/*其它名称:年,月,闰*/
const word cOtherName[] = {0x5E74,0x6708,0x95F0,0};
/*公历每月前面的天数*/
const int wMonthAdd[12] = {0,31,59,90,120,151,181,212,243,273,304,334};
/*农历数据*/
const int wNongliData[100] = {2635,333387,1701,1748,267701,694,2391,133423,1175,396438
       ,3402,3749,331177,1453,694,201326,2350,465197,3221,3402
       ,400202,2901,1386,267611,605,2349,137515,2709,464533,1738
       ,2901,330421,1242,2651,199255,1323,529706,3733,1706,398762
       ,2741,1206,267438,2647,1318,204070,3477,461653,1386,2413
       ,330077,1197,2637,268877,3365,531109,2900,2922,398042,2395
       ,1179,267415,2635,661067,1701,1748,398772,2742,2391,330031
       ,1175,1611,200010,3749,527717,1452,2742,332397,2350,3222
       ,268949,3402,3493,133973,1386,464219,605,2349,334123,2709
       ,2890,267946,2773,592565,1210,2651,395863,1323,2707,265877};
static int wCurYear,wCurMonth,wCurDay;
static int nTheDate,nIsEnd,m,k,n,i,nBit;
//word szNongli[30], szNongliDay[10],szShuXiang[10];
word UniToday[5];
/*---取当前公历年、月、日---*/
wCurYear = pSt.year;
wCurMonth = pSt.month;
wCurDay = pSt.day;
/*---计算到初始时间1921年2月8日的天数：1921-2-8(正月初一)---*/
nTheDate = (wCurYear - 1921) * 365 + (wCurYear - 1921) / 4 + wCurDay + wMonthAdd[wCurMonth - 1] - 38;
if((!(wCurYear % 4)) && (wCurMonth > 2))
  nTheDate = nTheDate + 1;

/*--计算农历天干、地支、月、日---*/
nIsEnd = 0;
m = 0;
while(nIsEnd != 1)
{
  if(wNongliData[m] < 4095)
   k = 11;
  else
   k = 12;
  n = k;
  while(n>=0)
  {
   //获取wNongliData(m)的第n个二进制位的值
   nBit = wNongliData[m];
   for(i=1;i<n+1;i++)
    nBit = nBit/2;

   nBit = nBit % 2;

   if (nTheDate <= (29 + nBit))
   {
    nIsEnd = 1;
    break;
   }

   nTheDate = nTheDate - 29 - nBit;
   n = n - 1;
  }
  if(nIsEnd)
   break;
  m = m + 1;
}
wCurYear = 1921 + m;
wCurMonth = k - n + 1;
wCurDay = nTheDate;
if (k == 12)
{
  if (wCurMonth == wNongliData[m] / 65536 + 1)
   wCurMonth = 1 - wCurMonth;
  else if (wCurMonth > wNongliData[m] / 65536 + 1)
   wCurMonth = wCurMonth - 1;
}

/*--生成农历天干、地支、属相 ==> wNongli--*/
CutWSTR(NongLiData->year,0);
UniToday[0] = cTianGan[((wCurYear - 4) % 60) % 10];   //天干
UniToday[1] = cDiZhi[((wCurYear - 4) % 60) % 12];     //地支
UniToday[2] = cShuXiang[((wCurYear - 4) % 60) % 12];  //属相
UniToday[3] = cOtherName[0];                          //年
BSTRAdd(NongLiData->year->wsbody,UniToday,4);

//sprintf(szShuXiang,"%s",cShuXiang[((wCurYear - 4) % 60) % 12]);
//sprintf(szNongli,"%s(%s%s)年",szShuXiang,cTianGan[((wCurYear - 4) % 60) % 10],cDiZhi[((wCurYear - 4) % 60) % 12]);

/*--生成农历月 --*/
CutWSTR(NongLiData->monthday,0);
if (wCurMonth < 1)                            //闰月
{
  UniToday[0] = cOtherName[2];                //闰
  if(-1 * wCurMonth == 11)                    //如果为11月，则将显示两个汉字"十一"
  {
    UniToday[1] = cMonName[10];              
    UniToday[2] = cMonName[11];
    BSTRAdd(NongLiData->monthday->wsbody,UniToday,3);
  }
  else
  {
    UniToday[1] = cMonName[-1 * wCurMonth];
    BSTRAdd(NongLiData->monthday->wsbody,UniToday,2);
  }
}
else
{
   if(wCurMonth == 11)
  {
    UniToday[0] = cMonName[10];
    UniToday[1] = cMonName[11];
    BSTRAdd(NongLiData->monthday->wsbody,UniToday,2);
  }
  else
  {
    UniToday[0] = cMonName[wCurMonth];
    BSTRAdd(NongLiData->monthday->wsbody,UniToday,1);
  }
}
  UniToday[0] = cOtherName[1];                //月
  BSTRAdd(NongLiData->monthday->wsbody,UniToday,1);
/*--生成农历日 --*/  
  UniToday[0] = cDayName[wCurDay][0];  
  UniToday[1] = cDayName[wCurDay][1]; 
  BSTRAdd(NongLiData->monthday->wsbody,UniToday,2);  
/*if (wCurMonth < 1)
  sprintf(szNongliDay,"闰%s",cMonName[-1 * wCurMonth]);
else
  strcpy(szNongliDay,cMonName[wCurMonth]);

strcat(szNongliDay,"月");
strcat(szNongliDay,cDayName[wCurDay]);
strcat(szNongli,szNongliDay);
memcpy(chNL,szNongli,strlen(szNongli));*/
}  



void InitInfoData(void);
void TimerProc(void)
{
  InitInfoData();
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&my_ipc);
}

#pragma inline
int get_string_width(WSHDR *ws, int font)
{
  int width=0;
  unsigned short *body=ws->wsbody;
  int len=body[0];
  while(len)
  {
    width+=GetSymbolWidth(body[len],font);
    len--;
  }
  return (width);
}

void FillInfoData(TInfo *Info,int x_start,int y_start, int font,const char *color,const char *colorframe)
{  
  Info->rc.x=x_start;
  Info->rc.y=y_start;
  Info->rc.x2=x_start+get_string_width(Info->ws,font);
  Info->rc.y2=y_start+GetFontYSIZE(font);
  Info->font=font;
  memcpy(Info->pen,color,4);
  memcpy(Info->penframe,colorframe,4);
}
  
int wsprintf_bytes(WSHDR *ws, unsigned int bytes)
{
	//char *str;
	if (bytes<=1024)
		return (wsprintf(ws,BYTES_FMT,bytes,BYTES_SG));
	 //str=BYTES_SG;
	else 
	{
		bytes>>=10;
		return (wsprintf(ws,BYTES_FMT,bytes,KBYTES_SG));
		//str=KBYTES_SG;
	}  
}


void InitInfoData(void)
{
  RAMNET *net_data;
  int c;
  char cWeek[16];
  char cData[16];
  const char cWeekName[4][7][16]={
    {"MONDAY","TUESDAY","WEDNESDAY","THUSDAY","FRIDAY","SATURDAY","SUNDAY"},
    {"MON","TUES","WED","THU","FRI","SAT","SUN"},
    {"Monday","Tuesday","Wednesday","Thusday","Friday","Saturday","Sunday"},
    {"Mon","Tues","Wed","Thu","Fri","Sat","Sun"}};
  const word XINGQI[] = {0x661F, 0x671F, 0}; //星期
  const word UniNum[] = {0x4E00,0x4E8C,0x4E09,0x56DB,0x4E94,0x516D,0x65E5,0};//一二三四五六日
  const word UniData[] = {0x5E74,0x6708,0x65E5,0};//年月日
  const word UniTime[] = {0x70B9,0x5206,0x79D2,0x4E0A,0x4E0B,0x5348,0};//点分秒上下午
  word UniToday[3];
  char cDataFmt[8][16] = {
    "%02d/%02d/%02d",
    "%02d-%02d-%02d",
    "%02d.%02d.%02d",
    "%02d %02d %02d",
    "%02d/%02d",
    "%02d-%02d",
    "%02d.%02d",
    "%02d %02d",};
  TTime tt;
  TDate d;

  char chText[255];
 
  if(NET_ENA)
  {
    InfoData[0].enabled=1;
    net_data=RamNet();
    c=(net_data->ch_number>=255)?'=':'-';
    wsprintf(InfoData[0].ws,NET_FMT,c,net_data->power);
    FillInfoData(&InfoData[0],NET_X,NET_Y,NET_FONT,NET_COLORS,NET_FRAME_COLORS);
  }
  else
  {
    InfoData[0].enabled=0;
  }
  
  if (TEMP_ENA)
  {
    InfoData[1].enabled=1;
    c=GetAkku(1,3)-0xAAA+15;
    wsprintf(InfoData[1].ws,TEMP_FMT,c/10,c%10);
    FillInfoData(&InfoData[1],TEMP_X,TEMP_Y,TEMP_FONT,TEMP_COLORS,TEMP_FRAME_COLORS);
  }
  else
  {
    InfoData[1].enabled=0;
  }
  
  if (VOLT_ENA)
  {
    InfoData[2].enabled=1;
    c=GetAkku(0,9);
    wsprintf(InfoData[2].ws,VOLT_FMT,c/1000,(c%1000)/10);
    FillInfoData(&InfoData[2],VOLT_X,VOLT_Y,VOLT_FONT,VOLT_COLORS,VOLT_FRAME_COLORS);
  }
  else
  {
    InfoData[2].enabled=0;
  }
  
  if (CAP_ENA)
  {
    InfoData[3].enabled=1;
    c=*RamCap();
    wsprintf(InfoData[3].ws,CAP_FMT,c);
    FillInfoData(&InfoData[3],ACCU_X,ACCU_Y,ACCU_FONT,ACCU_COLORS,ACCU_FRAME_COLORS);
  }
  else
  {
    InfoData[3].enabled=0;
  }
  
  if (CPU_ENA)
  {
    InfoData[4].enabled=1;
    c=GetCPULoad();
    if(c==100)
    	c=99;
    wsprintf(InfoData[4].ws,CPU_FMT,c);
    FillInfoData(&InfoData[4],CPU_X,CPU_Y,CPU_FONT,CPU_COLORS,CPU_FRAME_COLORS);
  }
  else
  {
    InfoData[4].enabled=0;
  }

  if (GPRS_ENA)
  {
    InfoData[5].enabled=1;
    //RefreshGPRSTraffic();
    c=*GetGPRSTrafficPointer();
    wsprintf_bytes(InfoData[5].ws,c);
    FillInfoData(&InfoData[5],GPRS_X,GPRS_Y,GPRS_FONT,GPRS_COLORS,GPRS_FRAME_COLORS);
  }
  else
  {
    InfoData[5].enabled=0;
  }
  
  if (RAM_ENA)
  {
    InfoData[6].enabled=1;
    c=GetFreeRamAvail();
    wsprintf_bytes(InfoData[6].ws,c);
    FillInfoData(&InfoData[6],RAM_X,RAM_Y,RAM_FONT,RAM_COLORS,RAM_FRAME_COLORS);  
  }
  else
  {
    InfoData[6].enabled=0;
  }
  
  if(WEEK_ENA)
  {
    InfoData[7].enabled=1;
    GetDateTime(&d,&tt);
    c = GetWeek(&d);
    if(WEEK_FMT <4)
    {
      for(int iloop = 0;iloop < 16;iloop++)
      {
        cWeek[iloop] = cWeekName[WEEK_FMT][c][iloop];        
      }
      wsprintf(InfoData[7].ws,cWeek,c);
    }
    else
    {
      CutWSTR(InfoData[7].ws,0);
      UniToday[0] = UniNum[c];
      if(WEEK_FMT==4)
         BSTRAdd(InfoData[7].ws->wsbody, XINGQI, 2);
      BSTRAdd(InfoData[7].ws->wsbody,UniToday, 1);      
    }
    FillInfoData(&InfoData[7],WEEK_X,WEEK_Y,WEEK_FONT,WEEK_COLORS,WEEK_FRAME_COLORS);
  }
  else
  {
    InfoData[7].enabled=0;
  }
  
  if(DATA_ENA)
  {
    InfoData[8].enabled=1;
    GetDateTime(&d,&tt);  
    for(int iloop = 0;iloop < 16;iloop++)
    {
      cData[iloop] = cDataFmt[DATA_FMT][iloop];        
    }
    if(DATA_FMT < 4)
      wsprintf(InfoData[8].ws,cData,d.year,d.month,d.day);
    else if(DATA_FMT <8)
      wsprintf(InfoData[8].ws,cData,d.month,d.day);
    else
    {
      CutWSTR(InfoData[8].ws,0);
      if(DATA_FMT == 8)
      {
        wsprintf(InfoData[8].ws,"%04d",d.year);
        UniToday[0] = UniData[0];
        BSTRAdd(InfoData[8].ws->wsbody,UniToday, 1);
      }
      
      UniToday[0] = d.month/10 + 0x30;
      UniToday[1] = d.month%10 + 0x30;
      BSTRAdd(InfoData[8].ws->wsbody,UniToday, 2);
      UniToday[0] = UniData[1];
      BSTRAdd(InfoData[8].ws->wsbody,UniToday, 1);
      
      UniToday[0] = d.day/10 + 0x30;
      UniToday[1] = d.day%10 + 0x30;
      BSTRAdd(InfoData[8].ws->wsbody,UniToday, 2);
      UniToday[0] = UniData[2];
      BSTRAdd(InfoData[8].ws->wsbody,UniToday, 1);      
    }
    FillInfoData(&InfoData[8],DATA_X,DATA_Y,DATA_FONT,DATA_COLORS,DATA_FRAME_COLORS);
  }
  else
  {
    InfoData[8].enabled=0;
  }
  
  if(TIME_ENA)
  {
    InfoData[9].enabled=1;
    GetDateTime(&d,&tt);
    switch(TIME_FMT)
    {
    case 0:
      wsprintf(InfoData[9].ws,"%02d:%02d",tt.hour,tt.min);
      break;
      
    case 1:
      if(tt.hour <= 12)
      {
        wsprintf(InfoData[9].ws,"AM %02d:%02d",tt.hour,tt.min);
      }
      else
      {
        tt.hour = tt.hour - 12;
        wsprintf(InfoData[9].ws,"PM %02d:%02d",tt.hour,tt.min);
      }
      break;
      
    case 2:
      if(tt.hour > 12)
        tt.hour = tt.hour - 12;
      wsprintf(InfoData[9].ws,"%02d:%02d",tt.hour,tt.min);
      break;
      
    case 3:
      wsprintf(InfoData[9].ws,"%02d:%02d:%02d",tt.hour,tt.min,tt.sec);
      break;
      
    case 4:
      if(tt.hour <= 12)
      {
        wsprintf(InfoData[9].ws,"AM %02d:%02d:%02d",tt.hour,tt.min,tt.sec);
      }
      else
      {
        tt.hour = tt.hour - 12;
        wsprintf(InfoData[9].ws,"PM %02d:%02d:%02d",tt.hour,tt.min,tt.sec);
      }
      break;
    case 5:
      wsprintf(InfoData[9].ws,"%02d",tt.hour);
      UniToday[0] = UniTime[0];
      BSTRAdd(InfoData[9].ws->wsbody,UniToday, 1);
      
      UniToday[0] = tt.min/10 + 0x30;
      UniToday[1] = tt.min%10 + 0x30;
      BSTRAdd(InfoData[9].ws->wsbody,UniToday, 2);
      UniToday[0] = UniTime[1];
      BSTRAdd(InfoData[9].ws->wsbody,UniToday, 1);
      break;
    case 6:
      wsprintf(InfoData[9].ws,"%02d",tt.hour);
      UniToday[0] = UniTime[0];
      BSTRAdd(InfoData[9].ws->wsbody,UniToday, 1);
      
      UniToday[0] = tt.min/10 + 0x30;
      UniToday[1] = tt.min%10 + 0x30;
      BSTRAdd(InfoData[9].ws->wsbody,UniToday, 2);
      UniToday[0] = UniTime[1];
      BSTRAdd(InfoData[9].ws->wsbody,UniToday, 1);
      
      UniToday[0] = tt.sec/10 + 0x30;
      UniToday[1] = tt.sec%10 + 0x30;
      BSTRAdd(InfoData[9].ws->wsbody,UniToday, 2);
      UniToday[0] = UniTime[2];
      BSTRAdd(InfoData[9].ws->wsbody,UniToday, 1);
      break;
    default:
      break;
      
    }   
    FillInfoData(&InfoData[9],TIME_X,TIME_Y,TIME_FONT,TIME_COLORS,TIME_FRAME_COLORS);
  }
  else
  {
    InfoData[9].enabled=0;
  }
  
  if (TEXT_ENA)
  {
    InfoData[10].enabled=1;
    for(c=0;c<strlen(TEXT_FMT);c++)
    {
      chText[c]=TEXT_FMT[c];
    }
    utf8_2ws(InfoData[10].ws,chText,strlen(TEXT_FMT));
    /*memcpy(chText,TEXT_FMT,strlen(TEXT_FMT));
    wsprintf(InfoData[10].ws,TEXT_FMT);*/
    FillInfoData(&InfoData[10],TEXT_X,TEXT_Y,TEXT_FONT,TEXT_COLORS,TEXT_FRAME_COLORS);
  }
  else
  {
    InfoData[10].enabled=0;
  }  
  
  
  if (NongLiNian_ENA)
  {
    InfoData[11].enabled=1;
    CutWSTR(InfoData[11].ws,0);
    GetDateTime(&d,&tt); 
    GetDayOf(d,&NongLi);
    memcpy(InfoData[11].ws->wsbody,NongLi.year->wsbody,16);
    FillInfoData(&InfoData[11],NongLiNian_X,NongLiNian_Y,NongLiNian_FONT,NongLiNian_COLORS,NongLiNian_FRAME_COLORS);
  }
  else
  {
    InfoData[11].enabled=0;
  }    

  if (NongLiData_ENA)
  {
    InfoData[12].enabled=1;
    CutWSTR(InfoData[12].ws,0);
    GetDateTime(&d,&tt); 
    GetDayOf(d,&NongLi);
    memcpy(InfoData[12].ws->wsbody,NongLi.monthday->wsbody,16);
    FillInfoData(&InfoData[12],NongLiData_X,NongLiData_Y,NongLiData_FONT,NongLiData_COLORS,NongLiData_FRAME_COLORS);
  }
  else
  {
    InfoData[12].enabled=0;
  } 

  
}

// ----------------------------------------------------------------------------
#define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}


int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  CSM_RAM *icsm;
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"TextInfo config updated!");
      InitConfig();
    }
  }
  if (msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
      {
        switch (msg->submess)
        {
        case IPC_UPDATE_STAT:
#ifdef NEWSGOLD
          if (!getCpuUsedTime_if_ena())
          {
            StartCpuUsageCount();
          }
#endif
          GBS_StartTimerProc(&mytmr, REFRESH*TMR_SECOND/10, TimerProc);
        }
      }
    }
  }
  icsm=FindCSMbyID(CSM_root()->idle_id);
  if (icsm)
  {
    if (IsGuiOnTop(idlegui_id(icsm))) //篷腓 IdleGui 磬 襦祛?忮瘐?
    {
      GUI *igui=GetTopGUI();
      if (igui) //?铐 耋耱怏弪
      {
        InitInfoData();
#ifdef ELKA
        {
          void *canvasdata = BuildCanvas();
#else
        void *idata = GetDataOfItemByID(igui, 2);
        if (idata)
        {
          void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
#endif
          for (int i=0; i<(sizeof(InfoData)/sizeof(TInfo)); i++)
          {
            if (InfoData[i].enabled)
            {
          DrawCanvas(canvasdata, InfoData[i].rc.x, InfoData[i].rc.y, InfoData[i].rc.x2, InfoData[i].rc.y2, 1);
          DrawString(InfoData[i].ws, InfoData[i].rc.x, InfoData[i].rc.y, InfoData[i].rc.x2+10, InfoData[i].rc.y2, InfoData[i].font,
          32,InfoData[i].pen, InfoData[i].penframe);         
            }
          }
        }
      }
    }
  }
  return(1);
}


static void maincsm_oncreate(CSM_RAM *data)
{
  for (int i=0;i<13; i++)
  {
    InfoData[i].ws=AllocWS(50);
  } 
  NongLi.year=AllocWS(100);
  NongLi.monthday=AllocWS(100);
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&my_ipc);
}


static void maincsm_onclose(CSM_RAM *csm)
{
  GBS_DelTimer(&mytmr);
  for (int i=0;i!=13; i++)
  {
    FreeWS(InfoData[i].ws);
  }
  FreeWS(NongLi.year);
  FreeWS(NongLi.monthday);    
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
  sizeof(CSM_RAM),
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"TextInfo");
}
// ----------------------------------------------------------------------------

int main(void)
{
  CSMROOT *csmr;
  CSM_RAM *save_cmpc;
  CSM_RAM main_csm;
  InitConfig();
  UpdateCSMname();
  LockSched();
  csmr=CSM_root();
  save_cmpc=csmr->csm_q->current_msg_processing_csm;
  csmr->csm_q->current_msg_processing_csm=csmr->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  csmr->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  return (0);
}
