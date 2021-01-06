/********************************************************************
   (C) Copyright free source ,by Bennie.Joe@Gmail.com  

	filename: 	CodeShow.c
	created:	2005-10-1
	author:		Bennie
	
	describe:	replaces provider name with custom format
	history:    2005-06-22 V2
*********************************************************************/
#include "addr.h"
#include "type_.h"

#define VERSION "2.0b"

//#define BASEADDRESS			0xA1580000
#define CODESHOWDATAADDRESS	BASEADDRESS
#ifdef OLD_VER // 老版数据库格式
#define IPCODETABLECOUNT (BASEADDRESS+0x1E000)
#define COUNTRYCODETABLE (BASEADDRESS+0x1E100)
#define REPEATSELECTTABLE (BASEADDRESS+0x1F200)
#define LOCALNOINFOTABLE (BASEADDRESS+0x1F300)
#else
#define IPCODETABLECOUNT (BASEADDRESS+0x0080)
#define COUNTRYCODETABLE (BASEADDRESS+0x0180)
#define REPEATSELECTTABLE (BASEADDRESS+0x1280)
#define LOCALNOINFOTABLE (BASEADDRESS+0x1380)
#endif
#define CODESHOWFLAG		0xFB
#define CODESHOWVERSION		2
#define MAXCITYNO		0x1FF


#define LOBYTE(w) ((byte)(w))
#define HIBYTE(w) ((byte)(((word)(w) >> 8) & 0xFF))


extern int strlen(const char*);
extern int memcmp(const void*, const void*, int size);
extern uint atou(const char*);
extern WSTRING*  WS_InitByZero(WSTRING*, word* buf, int count);
extern void GetCalleeNumber(int index, WSTRING *ws);
extern void UpdateWndItem(void* Countext, WSTRING* ws, int index); 
int GetProvAndCity(word *pBSTR, char *pNoStr);
void BSTRAdd(word *pDst, const word * pSrc, int Count );
word FindLocale(LOCALE *pLocale, int LocaleCount, int LocaleNo, int *nRepeatNum);
void AppendInfoW(WSTRING *pWS, WSTRING * pNo);
word GetCode(byte *pBuf, dword Index);
#ifndef OLD_VER
word GetCodeRange(CRANGE *pBuf, uint dwNum, uint dwNo);
#endif

const word szUnknownUser[] 	= { 0x672A, 0x77E5, 0x53F7,0x7801, 0};
const word szErrorData[] 	= { 0x6570, 0x636E, 0x5E93, 0x9519, 0x8BEF, 0};
const word szLocalCode[] 	= { 0x672C, 0x5730, 0x53F7,0x7801, 0};
const word szSplit[] 		= { 0x2027, 0 };
const word szAddInfo[] 		= { 0x20, 0 };
const word szShortNo[]          = { 0x96C6, 0x56E2, 0x77ED, 0x53F7, 0};//集团短号Unicode

/****************/
/* main program */
/****************/
void memcpy(char *szDest, char *szSrc, int len)
#ifdef SK6Cv50
 @ "CODE_X"
#endif
{
  int i;
  for(i=0; i<len; i++)
    szDest[i] = szSrc[i];
  szDest[len] = 0;
}

//参考along代码 国际代码
char FindCRName(word *pBSTR, char *szNo)
#ifdef SK6Cv50
 @ "CODE_X"
#endif
{
	if(memcmp(szNo, "86", 2) == 0)//中国内地
		return 0;
	else
	{
          char szTemp[5]="\0";
	  word wCRNo;
	  word wTable=*(word *)COUNTRYCODETABLE;
	  word wCount=*(word *)(COUNTRYCODETABLE+2);
	  const word *pTable=(word *)(COUNTRYCODETABLE+4);
	  CRNO *pCRNO=(CRNO *)(COUNTRYCODETABLE+(wTable+2<<1));
	  int j = 0, k, nRepeatNum = 0;
	  int i = 0, nStart = 0, nEnd = wCount;
	  int len=strlen(szNo);
	  if(len > 4)len = 4;
	  for(k=len; k>0; k--)
	    {
		memcpy(szTemp, szNo, k);
		nStart = 0, nEnd = wCount;
		wCRNo = atou(szTemp);
		while(nStart <= nEnd)
		  {
		      i = (nEnd+nStart)/2;
		      if(wCRNo == pCRNO[i].CRNo)
			{
			  do{		  
                              if(wCRNo != pCRNO[i].CRNo)break;
			      i--;
			    }while(i > 0);
		          i++;
		          j = i;
			  do{
			      if(wCRNo != pCRNO[j].CRNo)break;
			      j++;
			      nRepeatNum++;
			    }while(j <= nEnd);
			  break;
			}
		  if(wCRNo < pCRNO[i].CRNo)nStart = i+1;
                  else nEnd = i-1;
                }
            if(nRepeatNum > 0)break;
           }
        if(nRepeatNum == 0)
          {
      	    BSTRAdd(pBSTR, szUnknownUser, 4);
          }
       else
         {
      	    for(j=0; j<nRepeatNum; j++)
      	      {
      		for(k=0; k<12; k++)
      		{
      		    wCRNo = GetCode(pCRNO[i+j].Names, k);//????
      		    if(wCRNo == MAXCITYNO)break;
      		    else BSTRAdd(pBSTR, pTable+wCRNo, 1);
      		}
      		if(j+1 != nRepeatNum)
      		{
      		    BSTRAdd(pBSTR, szAddInfo, 1);
      		}
      	    }
         }
      }
      return 1;
}

void UpdateLocaleToItem(int Index, int NoIndex, void* Context)
#ifdef SK6Cv50
 @ "CODE_X"
#endif
{
	WSTRING ws1, ws2, *pws1, *pws2;
	word buf1[0x3E], buf2[0x3E];
	pws1 = WS_InitByZero(&ws1, buf1, 0x3D);
	pws2 = WS_InitByZero(&ws2, buf2, 0x3D);
	GetCalleeNumber(NoIndex, pws1);
	AppendInfoW(pws2, pws1);
	UpdateWndItem(Context, pws2, Index); 
}

//WString号码版本
void AppendInfoW(WSTRING *pWS, WSTRING * pNo)
#ifdef SK6Cv50
 @ "CODE_X"
#endif
{
	char szPNo[0x30];
	int i=0;
	for(; i<*pNo->pstr && i<0x2B; ++i)
	{
		szPNo[i] = pNo->pstr[i+1];
	}
	szPNo[i] = '\0';
	GetProvAndCity(pWS->pstr, szPNo);			
}

word GetLocalNoInfo(char *szLocalNo, char *szLocalName)
#ifdef SK6Cv50
 @ "CODE_X"
#endif
{
	int i = 0;
	word len = 0;
	word no1, no2;
	int nLocalNo=atou(szLocalNo);
	int nLocalNum=*(int*)LOCALNOINFOTABLE;
	const char * pLocalInfo = (const char *)(LOCALNOINFOTABLE+20);
	for(; i< nLocalNum; ++i, pLocalInfo += 14)
	{
	    no1 = *(word *)(pLocalInfo);
	    no2 = *(word *)(pLocalInfo+2);
		if(no1 <= nLocalNo && nLocalNo <= no2)
		{
		    len = 5;
		    memcpy(szLocalName, (char *)(pLocalInfo+4), 10);
			break;
		}
	}
	return len;
}

//得到号码所对应的省市字串  
int GetProvAndCity(word *pBSTR, char *pNoStr)
{
	int bLocal=0;
    char szLocalNo[5];
	word CityNo = MAXCITYNO;
	char szLocalInfo[11];
	const PROVINCE * pProvince;
	const CITY* pCity;
	LOCALE *pLocale;
	const CODESHOWHEAD * pHead;
	int CodeLen;
	int nLocalNum=*(int*)LOCALNOINFOTABLE;
	const PROVINCE LocalProvince=*(PROVINCE*)(LOCALNOINFOTABLE+4);
	const CITY LocalCity=*(CITY*)(LOCALNOINFOTABLE+10);
	int nRepeatNum=1;

	pHead = (const CODESHOWHEAD *)CODESHOWDATAADDRESS;
	//校验数据库的有效性
	if(pHead->Flag != CODESHOWFLAG || pHead->Version != CODESHOWVERSION) {
		BSTRAdd(pBSTR, szErrorData, 4);	
		return 0;	
	}
	//得到省表和市表
	pProvince = (PROVINCE*)(CODESHOWDATAADDRESS+pHead->ProvinceTableOffset);
	pCity = (CITY*)(CODESHOWDATAADDRESS+pHead->CityTableOffset);
	//去掉国际码+86
	if(*pNoStr == '+')
        {
	  if(FindCRName(pBSTR, pNoStr+1))return 1;
	  else pNoStr += 3;
        }
	//如果长度大于12，则包括IP前缀，下面滤去已知IP前缀
	CodeLen = strlen(pNoStr);
	if(CodeLen > 12)
	{
		int i = 0;
		const char * pIPCode = (const char *)(IPCODETABLECOUNT+4);
		for(; i< *(const int *)IPCODETABLECOUNT; ++i, pIPCode += 10)//原来为8
		{
			if(!memcmp(pNoStr, pIPCode+1, *pIPCode)){
			  pNoStr += *pIPCode;	//过滤已知IP
#ifdef OLD_VER //过滤手机号码前的0
			  if(!memcmp(pNoStr, "013", 3) || !memcmp(pNoStr, "015", 3) || !memcmp(pNoStr, "018", 3))//删除手机号前的0
				++pNoStr;
#else
                          if(!memcmp(pNoStr,"01",2) && pHead->RangeOffset[*(pNoStr+2)-'0'][0] != 0xFFFFFFFF)//是手机号码
                            ++pNoStr;
#endif
				break;
			}
		}
	}

	//得到长途电话区号表
	pLocale = (LOCALE*)(CODESHOWDATAADDRESS+pHead->LocaleTableOffset);
	//如果以0开头，则判断为是固定长途电话
	if(*pNoStr == '0')
	{
		++pNoStr;
		//判断是否是三位区号010和02x
		if(*pNoStr == '1' || *pNoStr == '2')
		{
			memcpy(szLocalNo, pNoStr+2, 4);
			*(pNoStr+2) = '\0';
		}
		else
		{
			memcpy(szLocalNo, pNoStr+3, 4);
			*(pNoStr+3) = '\0';	
		}
		//得到区号，在区号表中查找对应的城市号
		CityNo = FindLocale(pLocale, pHead->LocaleCount, atou(pNoStr), &nRepeatNum); 
	}
#ifdef OLD_VER
	//如果是13x，15x，18x，则判定为移动电话
	else if(*pNoStr == '1' && (*(pNoStr+1) == '3' || *(pNoStr+1) == '5' || *(pNoStr+1) == '8'))
	{
		bLocal = 2;
                char chTemp=*(pNoStr+1);
		pNoStr += 2;
		*(pNoStr+5) = '\0';
		//得到手机号码的前五位，在手机号码表中查找对应的城市号
		if(chTemp == '3')//13X
		  CityNo = GetCode((byte *)(CODESHOWDATAADDRESS+pHead->CodeTableOffset), atou(pNoStr));
		else if(chTemp == '5')//15X
		  CityNo = GetCode((byte *)(CODESHOWDATAADDRESS+0x20000), atou(pNoStr));
                else if(chTemp == '8')//18x
                CityNo = GetCode((byte *)(CODESHOWDATAADDRESS+0x3B774), atou(pNoStr));
#else
	//手机号码
	else if(*pNoStr == '1' && pHead->RangeOffset[*(pNoStr+1)-'0'][0] != 0xFFFFFFFF)
	{
		bLocal = 2;
                char chTemp=(*(pNoStr+1)-'0');
                pNoStr += 2;
		*(pNoStr+5) = '\0';
CityNo = GetCodeRange((CRANGE *)(CODESHOWDATAADDRESS+0x4000+(pHead->RangeOffset[chTemp][0]<<2)), pHead->RangeOffset[chTemp][1], atou(pNoStr));          
#endif
	}
	//如果不是长话和移动电话，判断为本地区号。或者不能在IP表中找到对应项。
	else
	{
		//集团短号规则：61-69开头，3-6位短号              
                if(*pNoStr=='6'&&CodeLen>=4&&CodeLen<=7)//包括最后的'\0'
		{
		  BSTRAdd(pBSTR, szShortNo, 4);
		}
		else //本地号码
                {
			BSTRAdd(pBSTR, szLocalCode, 4);	
			if(nLocalNum > 0 && nLocalNum < 200)//?????
			{
		  	   memcpy(szLocalNo, pNoStr, 4);
		  	   if(GetLocalNoInfo(szLocalNo, szLocalInfo))
		  	   {
		    		BSTRAdd(pBSTR, szAddInfo, 1);
				BSTRAdd(pBSTR, (word *)szLocalInfo, 5);
		 	   }
			}
		}
		return 0;
	}

	//如果城市号不在范围内	
	if(CityNo >= pHead->CityCount){
		BSTRAdd(pBSTR, szUnknownUser, 4);	
		return 0;
	}
	else{
		if(nRepeatNum == 1)
		{
		  BSTRAdd(pBSTR, pProvince[pCity[CityNo].ProvinceNo].ProvinceName, 3);
		  BSTRAdd(pBSTR, szSplit, 1);
		  BSTRAdd(pBSTR, pCity[CityNo].CityName, 5);
		  if(bLocal == 0)
		    bLocal = (memcmp(LocalCity.CityName, pCity[CityNo].CityName, 10) == 0);
		}
		else
		{
		  int i;
		  BSTRAdd(pBSTR, pProvince[pCity[pLocale[CityNo].CityNo].ProvinceNo].ProvinceName, 3);
		  BSTRAdd(pBSTR, szSplit, 1);
		  for(i=0; i<nRepeatNum; i++)
		  {
		     if(nRepeatNum < 3)
			   BSTRAdd(pBSTR, szAddInfo, 1);
		     BSTRAdd(pBSTR, pCity[pLocale[i+CityNo].CityNo].CityName, 5);
			 if(bLocal == 0)
			   bLocal = (memcmp(LocalCity.CityName, pCity[CityNo].CityName, 10) == 0);//如果城市名相同，bLocal=1，显示区级地名
		   }
		}
		if(bLocal == 1 && nLocalNum > 0 && nLocalNum < 200 && (memcmp(LocalProvince.ProvinceName, pProvince[pCity[CityNo].ProvinceNo].ProvinceName, 6) == 0))
		{
		  if(GetLocalNoInfo(szLocalNo, szLocalInfo))
		  {
	        BSTRAdd(pBSTR, szAddInfo, 1);
		    BSTRAdd(pBSTR, (word *)szLocalInfo, 5);
		  }
		}
		return 1;
	}
}
//从手机号码表中查找对应的城市号
word GetCode(byte *pBuf, dword Index)
{
    word CodeL, CodeH;
    pBuf = pBuf + (Index + (Index>>3));					//每条记录9个bit,即Index*9/8
    Index &= 0x7;										//得到在字节内的偏移量
    CodeL = ((word)pBuf[0])>>Index ;					//低字节右移偏移量
    CodeH = ((pBuf[1]<<(15-Index)) & 0xFFFF)>>7;	    //高字节去掉高处无效位,并左移到合适的位置
    return (CodeH + CodeL);								//拼接高低字节,共9位
}
#ifndef OLD_VER
//二分法查找城市代码
word GetCodeRange(CRANGE *pBuf, uint dwNum, uint dwNo)
{
CRANGE test;
int left = 0, right = dwNum-1, index = 0;
while(left <= right)
{
  index = (left+right)/2;
  test = pBuf[index];
  if(test.dwNum <= dwNo && dwNo <= test.dwNum+test.dwRange) 
  {
   return test.wCityNo;
  }
  else if(dwNo < test.dwNum) right = index-1;
  else left = index+1;
}
  return MAXCITYNO;
}
#endif
//从长话区号表中查找对应的城市号
word FindLocale(LOCALE *pLocale, int LocaleCount, int LocaleNo, int *nRepeatNum)
{
	//长话区号表是顺序存储的,下面是个简单的二分法查找.
	int j = 0;
    int i = 0, nStart = 0, nEnd = LocaleCount;

	//处理几个特殊的地区，这些地区有相同的区号，在二分法时结果不确定
	*nRepeatNum = 0;
/*	
	while(i < *(int*)REPEATSELECTTABLE)
	{
		if(	LocaleNo == *(word*)(REPEATSELECTTABLE+4+i*4))
		{
			return *(word*)(REPEATSELECTTABLE+6+i*4);
		}
		++i;
	}*/
	//二分法查找对应的城市号，区号表是升序存储的
	while(nStart <= nEnd)
    {
        i = (nEnd+nStart)/2;

        if(LocaleNo == pLocale[i].LocaleNo)
		{
			do
			{
			  if(LocaleNo != pLocale[i].LocaleNo)
			    break;
			  i--;
			}
			while(i > 0);
			i++;
			j = i;
			do
			{
			  if(LocaleNo != pLocale[j].LocaleNo)
			    break;
			  j++;
			  (*nRepeatNum)++;
			}
			while(j <= nEnd);
            break;
		}
        if(LocaleNo < pLocale[i].LocaleNo)
            nEnd   = i-1;
        else
            nStart = i+1;
    }
	if(*nRepeatNum > 1)
	  return	i;
	else
      return	(nStart > nEnd)? MAXCITYNO:pLocale[i].CityNo;
}

//附加UNICODE字串到另一个字串上,结束标志是L'\0'或Count个字符
void BSTRAdd(word *pDst, const word * pSrc, int Count)
{
	uint nSize = *pDst, i=1;
	while(*pSrc != '\0' && i<=Count)
		*(pDst+ nSize + i++) = *pSrc++;
	*pDst = nSize+i-1;
}


