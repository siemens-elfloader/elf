#include "bitconv.h"


//#define RGB8(R,G,B) (B+(G<<2)+(R<<5))
//#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))


#define PTIV 3

unsigned const short BMP_id=0x4d42, PTI_id='P'+'T'*0x100, PTI_ver=PTIV*0x100+'I';

char edcl[4]={0,0,0,255}, ednm;

static const char *BMP_format[]={"8��� (�������)","16���","24����","32����"},
				*GPF_format[]={"GPF","GPF_2"},
				*PTI_format[]={"��","���"},
				*save_ext[]={".pti",".bmp",".gpf",".dat"};



typedef struct  {
	WORD w, h;
	BYTE type;
} DAT_HDR;



static const char *GPF_id="GraphicPatchFile";
typedef struct  {
	WORD num, c1_0;
	BYTE w, h;
	WORD type;
	double c2_0;
} GPF_HDR;

static const char *GPF2_id="GraphPatchFile_2";
typedef struct  {
	WORD num, c1_0, w, h;
	DWORD type;
	LONG c2_0;
} GPF2_HDR;

GPF_HDR Def_GPF={ 0, 0, 0, 0, 0, 0 };
GPF2_HDR Def_GPF2={ 0, 0, 0, 0, 0, 0 };

typedef struct  {
	//unsigned short BMP_id; 				//00	2	'BM'
	DWORD size,				//02	4	������ ����� � ������;
		zero_res,			//06	4	0000 0000
		offbits;			//10	4	�������� ������ ����������� � �����;
				// biSize,				//14	4	������ ����� ���������, 40;
				// Width,				//18	4	������ ����������� � ��������;
				// Height;				//22	4	������ ����������� � ��������;
	// unsigned short biPlanes,		//26	2	����� ���������� �����������, 1;
				// biBitCount;			//28	2	��� �� ������: 1,4,8,16,24,32;
	// unsigned long biCompression,	//30	4	��� ������; 0 = BI_RGB
				// biSizeImage,		//34	4	������ ������� ����������� � ������ ��� 0;
				// biXPelsPerMeter,	//38	4	�������������� ����������, � �������� / �� ����; 0xB40
				// biYPelsPerMeter,	//42	4	������������ ����������, � �������� / �� ����; 0xB40
				// biClrUsed,			//46	4	���������� ������������ ������;
				// biClrImportant;		//50	4	����� "������" ������;
} BMP_HEAD;

typedef struct { 
    DWORD   biSize;
    LONG    biWidth;
    LONG    biHeight;
    WORD    biPlanes;
    WORD    biBitCount;
    DWORD   biCompression;
    DWORD   biSizeImage;
    LONG    biXPelsPerMeter;
    LONG    biYPelsPerMeter;
    DWORD   biClrUsed;
    DWORD   biClrImportant;
} BITMAPINFOHEADER;

typedef struct  {
	BMP_HEAD bmp;
	BITMAPINFOHEADER img;
}BMP_HDR;

static const BMP_HDR Def_BMP=
{
	{
		0,
		0,
		54	
	},
	{
		40,
		0,
		0,
		1,
		16,
		0,
		0,
		0xB40,
		0xB40,
		0,
		0
	}
};






