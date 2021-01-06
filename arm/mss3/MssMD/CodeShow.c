/********************************************************************
   (C) Copyright free source ,by Bennie.Joe@Gmail.com  

	filename: 	CodeShow.c
	created:	2005-10-1
	author:		Bennie
	
	describe:	replaces provider name with custom format
	history:    2005-06-22 V2
*********************************************************************/
#include "..\..\inc\swilib.h"
#include "string_works.h"
#include "CodeShow.h"

#define VERSION "2.0b"

#define BASEADDRESS			0xA1580000
//#define BASEADDRESS			mBASEADDRESS
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

//#define IPCODETABLECOUNT	(BASEADDRESS+0x1E000)
//#define REPEATSELECTTABLE	(BASEADDRESS+0x1F000)
//#define LOCALNOINFOTABLE	(BASEADDRESS+0x1F100)
//#define COUNTRYCODETABLE	(BASEADDRESS+0x1E100)
#define CODESHOWFLAG		0xFB
#define CODESHOWVERSION		2
#define MAXCITYNO			0x1FF

#define LOBYTE(w) ((byte)(w))
#define HIBYTE(w) ((byte)(((word)(w) >> 8) & 0xFF))

typedef unsigned char	byte;
typedef unsigned short	word;
typedef unsigned int	dword;
typedef unsigned int	uint;
typedef unsigned long	uint32;
/*
typedef struct {
    byte Flag;
    byte ID;
    byte Version;
    byte Year;
    byte Month;
    byte Day;
    byte ProvinceNameLen;
    byte CityNameLen;
    dword CodeTableOffset;
    dword CodeCount;
    dword LocaleTableOffset;
    dword LocaleCount;
    dword ProvinceTableOffset;
    dword ProvinceCount;
    dword CityTableOffset;
    dword CityCount;
}CODESHOWHEAD;*/
#ifdef OLD_VER // 老版数据库格式
typedef struct {
    byte Flag;
    byte ID;
    byte Version;
    byte Year;
    byte Month;
    byte Day;
    byte ProvinceNameLen;
    byte CityNameLen;
    dword CodeTableOffset;
    dword CodeCount;
    dword LocaleTableOffset;
    dword LocaleCount;
    dword ProvinceTableOffset;
    dword ProvinceCount;
    dword CityTableOffset;
    dword CityCount;
}CODESHOWHEAD;
#else
typedef struct CODESHOWHEAD{
    byte Flag;
    byte ID;
    byte Version;
    byte Year;
    byte Month;
    byte Day;
    byte ProvinceNameLen;
    byte CityNameLen;
    dword CodeTableOffset;
    dword CodeCount;
    dword LocaleTableOffset;
    dword LocaleCount;
    dword ProvinceTableOffset;
    dword ProvinceCount;
    dword CityTableOffset;
    dword CityCount;
	byte Author[8];
	dword RangeOffset[10][2];
}CODESHOWHEAD;

typedef struct CRANGE{ // 新的数据库格式定义
	uint32 dwNum :17;
	uint32 dwRange :6;
	uint32 wCityNo :9;
}CRANGE;
#endif

#pragma pack(2)
typedef struct {
    word ProvinceName[3];
    word StartOffset;
    word EndOffset;
}PROVINCE;

typedef struct {
    word CityName[6];
    word LocaleNo     :10;
    word ProvinceNo   :6;
}CITY;
#pragma pack()

typedef struct {
    word LocaleNo;
    word CityNo;
}LOCALE;

typedef struct {
    word CRNo;
    byte Names[14];
}CRNO;

const word szUnknownUser[] 	= { 0x672A, 0x77E5, 0x53F7,0x7801, 0};
const word szErrorData[] 	= { 0x6570, 0x636E, 0x5E93, 0x9519, 0x8BEF, 0};
const word szLocalCode[] 	= { 0x672C, 0x5730, 0x53F7,0x7801, 0};
const word szChineseTaiBei[] = { 0x4E2D, 0x56FD, 0x53F0,0x6E7E, 0};
const word szSplit[] 		= { 0x2027, 0 };
const word szAddInfo[] 		= { 0x20, 0 };

word GetCodeRange(CRANGE *pBuf, uint32 dwNum, uint32 dwNo);
char FindCRName(word *pBSTR, char *szNo);
word GetLocalNoInfo(char *szLocalNo, char *szLocalName);
word FindLocale(LOCALE *pLocale, int LocaleCount, int LocaleNo, int *nRepeatNum);
word GetCode(byte *pBuf, dword Index);
void BSTRAdd(word *pDst, const word * pSrc, int Count );

inline unsigned long atou(char *str)
{
  return (str2int(str));
}

int GetProvAndCity(word *pBSTR, char *pNo)
{
  char NoStr[0x30];
  char *pNoStr=NoStr;
	int bLocal=0;
    char szLocalNo[5];
	word CityNo = MAXCITYNO;
	char szLocalInfo[11];
	const PROVINCE * pProvince;
	const CITY* pCity;
	LOCALE *pLocale;
	const CODESHOWHEAD * pHead;
	int CodeLen;
	//if(!mBASEADDRESS)
	//{
	//	BSTRAdd(pBSTR, szErrorData, 4);
	//	return 0;
	//}
	int nLocalNum=*(int*)LOCALNOINFOTABLE;
	const PROVINCE LocalProvince=*(PROVINCE*)(LOCALNOINFOTABLE+4);
	const CITY LocalCity=*(CITY*)(LOCALNOINFOTABLE+10);
	int nRepeatNum=1;
	strcpy(NoStr, pNo);

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
	  if(FindCRName(pBSTR, pNoStr+1))return 0;
	  else pNoStr += 3;
        }
	//如果长度大于12，则包括IP前缀，下面滤去已知IP前缀
	CodeLen = strlen(pNoStr);
	if(CodeLen > 7)
	{
		int i = 0;
		const char * pIPCode = (const char *)(IPCODETABLECOUNT+4);
		for(; i< *(const int *)IPCODETABLECOUNT; ++i, pIPCode += 10)
		{
			if(!memcmp(pNoStr, (void*)(pIPCode+1), *pIPCode)){
				pNoStr += *pIPCode;	
				if(!memcmp(pNoStr, "013", 3) || !memcmp(pNoStr, "015", 3))
					++pNoStr;
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
	//如果是13x，则判定为移动电话
	else if(*pNoStr == '1' && *(pNoStr+1) >= '2')//(*(pNoStr+1) == '3' || *(pNoStr+1) == '5'))
	{
		char chTemp=(*(pNoStr+1)-'0');
		bLocal = 2;
		pNoStr += 2;
		*(pNoStr+5) = '\0';
		//得到手机号码的前五位，在手机号码表中查找对应的城市号
#ifdef OLD_VER
		if(chTemp == '3')//13X
		  CityNo = GetCode((byte *)(CODESHOWDATAADDRESS+pHead->CodeTableOffset), atou(pNoStr));
		else
		  CityNo = GetCode((byte *)(CODESHOWDATAADDRESS+0x20000), atou(pNoStr));
#else
		if(strlen(pNoStr) != 5)
			CityNo = MAXCITYNO;
		else
		{
			if(pHead->RangeOffset[chTemp][0] == 0xFFFFFFFF)
				CityNo = MAXCITYNO;
			else
				CityNo = GetCodeRange((CRANGE *)(CODESHOWDATAADDRESS+0x4000+(pHead->RangeOffset[chTemp][0]<<2)), pHead->RangeOffset[chTemp][1], str2int(pNoStr));
		}
#endif
	}
	//如果不是长话和移动电话，判断为本地区号。或者不能在IP表中找到对应项。
	else
	{
		BSTRAdd(pBSTR, szLocalCode, 4);	
		if(nLocalNum > 0 && nLocalNum < 200)
		{
		  memcpy(szLocalNo, pNoStr, 4);
		  if(GetLocalNoInfo(szLocalNo, szLocalInfo))
		  {
		    BSTRAdd(pBSTR, szAddInfo, 1);
			BSTRAdd(pBSTR, (word *)szLocalInfo, 5);
		  }
		}
		return 0;
	}

	//如果城市号不在范围内	
	if(CityNo >= pHead->CityCount){
		BSTRAdd(pBSTR, szUnknownUser, 4);	
		return 0;
	}
	else
	{
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
			   bLocal = (memcmp(LocalCity.CityName, pCity[CityNo].CityName, 10) == 0);
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

void BSTRAdd(word *pDst, const word *pSrc, int Count)
{
	uint nSize = *pDst, i=1;
	while(*pSrc != '\0' && i<=Count)
		*(pDst+ nSize + i++) = *pSrc++;
	*pDst = nSize+i-1;
}

word GetCode(byte *pBuf, dword Index)
{
    word CodeL, CodeH;
    pBuf = pBuf + (Index + (Index>>3));					//每条记录9个bit,即Index*9/8
    Index &= 0x7;										//得到在字节内的偏移量
    CodeL = ((word)pBuf[0])>>Index ;					//低字节右移偏移量
    CodeH = ((pBuf[1]<<(15-Index)) & 0xFFFF)>>7;	    //高字节去掉高处无效位,并左移到合适的位置
    return (CodeH + CodeL);								//拼接高低字节,共9位
}


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

void AppendInfoW(WSHDR *pWS, WSHDR *pNo)
{
	char szPNo[0x30];
	int i=0;
	for(; i<*pNo->wsbody && i<0x2B; ++i)
	{
		szPNo[i] = pNo->wsbody[i+1];
	}
	szPNo[i] = '\0';
	GetProvAndCity(pWS->wsbody, szPNo);	
}

word GetLocalNoInfo(char *szLocalNo, char *szLocalName)
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

char FindCRName(word *pBSTR, char *szNo)
{
	if(memcmp(szNo, "86", 2) == 0)//中国内地
		return 0;
	if(memcmp(szNo, "886", 3) == 0)
	{
		BSTRAdd(pBSTR, szChineseTaiBei, 4);
		BSTRAdd(pBSTR, szSplit, 1);
		if(memcmp(szNo+3, "0836", 4) == 0)
			BSTRAdd(pBSTR, (const word *)"\x6C\x9A\x56\x79", 2);
		else if(memcmp(szNo+3, "0827", 4) == 0)
			BSTRAdd(pBSTR, (const word *)"\x1C\x4E\x99\x6C\x20\x00\x57\x53\x99\x6C", 5);				
		else if(memcmp(szNo+3, "0826", 4) == 0)
			BSTRAdd(pBSTR, (const word *)"\x4C\x4E\x18\x4E", 2);
		else if(memcmp(szNo+3, "0823", 4) == 0)
			BSTRAdd(pBSTR, (const word *)"\xD1\x91\xE8\x95", 2);
		else if(memcmp(szNo+3, "089", 3) == 0)
			BSTRAdd(pBSTR, (const word *)"\xF0\x53\x1C\x4E", 2);
		else if(memcmp(szNo+3, "049", 3) == 0)
			BSTRAdd(pBSTR, (const word *)"\x57\x53\x95\x62", 5);
		else if(memcmp(szNo+3, "037", 3) == 0)
			BSTRAdd(pBSTR, (const word *)"\xD7\x82\x17\x68", 2);
		else if(memcmp(szNo+3, "02", 2) == 0)
			BSTRAdd(pBSTR, (const word *)"\xF0\x53\x17\x53\x20\x00\xFA\x57\x86\x96", 5);
		else if(memcmp(szNo+3, "03", 2) == 0)
			BSTRAdd(pBSTR, (const word *)"\x43\x68\xED\x56\xB0\x65\xF9\x7A\xB1\x82\xB2\x83\x9C\x5B\x70\x51", 8);
		else if(memcmp(szNo+3, "04", 2) == 0)
			BSTRAdd(pBSTR, (const word *)"\x70\x5F\x16\x53\x20\x00\xF0\x53\x2D\x4E", 5);
		else if(memcmp(szNo+3, "05", 2) == 0)
			BSTRAdd(pBSTR, (const word *)"\x09\x56\x49\x4E\x20\x00\x91\x4E\x97\x67", 5);
		else if(memcmp(szNo+3, "06", 2) == 0)
			BSTRAdd(pBSTR, (const word *)"\xF0\x53\x57\x53\x20\x00\x8E\x6F\x56\x6E", 5);
		else if(memcmp(szNo+3, "07", 2) == 0)
			BSTRAdd(pBSTR, (const word *)"\xD8\x9A\xC4\x96", 2);
		else if(memcmp(szNo+3, "08", 2) == 0)
			BSTRAdd(pBSTR, (const word *)"\x4F\x5C\x1C\x4E", 2);
		else
			BSTRAdd(pBSTR, szUnknownUser, 2);
	}
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
      		    wCRNo = GetCode(pCRNO[i+j].Names, k);
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

word GetCodeRange(CRANGE *pBuf, uint32 dwNum, uint32 dwNo)
{
	CRANGE test;
	int left = 0, right = 0, index = 0;
	right = dwNum-1;
	while(left <= right)
	{
		 index = (left+right)/2;
		 test = pBuf[index];
		 if(test.dwNum <= dwNo && dwNo <= test.dwNum+test.dwRange) 
		 {
			 return test.wCityNo;
		 }
		 else if(dwNo > test.dwNum+test.dwRange)  left = index+1;
		 else  right = index-1;
	}
	return MAXCITYNO;
}

