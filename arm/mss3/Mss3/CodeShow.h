// CodeShow.h: interface for the CCodeShow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CODESHOW_H__33A5E9E0_870E_4BBE_B777_6771252D4CBC__INCLUDED_)
#define AFX_CODESHOW_H__33A5E9E0_870E_4BBE_B777_6771252D4CBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

class CodeShow  
{
public:
	static void AppendInfoW(WSHDR *pWS, WSHDR * pNo);
	static int GetProvAndCity(word *pBSTR, char *pNoStr);
	CodeShow();
	virtual ~CodeShow();
private:
	//static char * mBASEADDRESS;
	static word GetCodeRange(CRANGE *pBuf, uint32 dwNum, uint32 dwNo);
	static char FindCRName(word *pBSTR, char *szNo);
	static word GetLocalNoInfo(char *szLocalNo, char *szLocalName);
	static word FindLocale(LOCALE *pLocale, int LocaleCount, int LocaleNo, int *nRepeatNum);
	static word GetCode(byte *pBuf, dword Index);
	static void BSTRAdd(word *pDst, const word * pSrc, int Count );
};

#endif // !defined(AFX_CODESHOW_H__33A5E9E0_870E_4BBE_B777_6771252D4CBC__INCLUDED_)
