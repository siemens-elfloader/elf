typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned int   dword;
typedef unsigned int   uint;
//#define OLD_VER //采用旧版本数据格式

typedef struct WString{
	word* pstr;
	int unknown[3];
	int buflen;
}WSTRING; 

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
uint dwNum :17;
uint dwRange :6;
uint wCityNo :9;
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
