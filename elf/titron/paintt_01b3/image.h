//#define RGB8(R,G,B) (B+(G<<2)+(R<<5))
//#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))

inline char rgb_24_8(int color){return ((color>>6)&3)|((color>>11)&0x1C)|((color>>16)&0xE0); }
inline short rgb_24_16(int color){return ((color>>3)&0x1f)|((color>>5)&0x7e0)|((color>>8)&0xf800); }
inline char rgb_16_8(short color){return ((color>>3)&3)|((color>>6)&0x1C)|((color>>8)&0xE0); }

#ifdef ELKA
	#define PTIV 2
#else
	#define PTIV 1
#endif

unsigned const short BMP_id=0x4d42, PTI_id='P'+'T'*0x100, PTI_ver=PTIV*0x100+'I';

char edcl[4]={0,0,0,255}, ednm;

static const char *BMP_format[]={"8бит (палитра)","16бит","24бита","32бита"},
				*PTI_format[]={"Да","Нет"};

typedef struct  {
	//unsigned short BMP_id; 				//00	2	'BM'
	unsigned long size,				//02	4	Размер файла в байтах;
				zero_res,			//06	4	0000 0000
				offbits,			//10	4	Смещение начала изображения в файле;
				biSize,				//14	4	Размер этого заголовка, 40;
				Width,				//18	4	Ширина изображения в пикселях;
				Height;				//22	4	Высота изображения в пикселях;
	unsigned short biPlanes,		//26	2	Число плоскостей изображения, 1;
				biBitCount;			//28	2	Бит на пиксел: 1,4,8,16,24,32;
	unsigned long biCompression,	//30	4	Тип сжатия; 0 = BI_RGB
				biSizeImage,		//34	4	Размер сжатого изображения в байтах или 0;
				biXPelsPerMeter,	//38	4	Горизонтальное разрешение, в пикселях / на метр; 0xB40
				biYPelsPerMeter,	//42	4	Вертикальное разрешение, в пикселях / на метр; 0xB40
				biClrUsed,			//46	4	Количество используемых цветов;
				biClrImportant;		//50	4	Число "важных" цветов;
} BMP_HDR;

BMP_HDR Def_BMP={0,
				0,
				54,
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
				0};




/* 

if (type==PNG_1)
  {
    int rowc_w=(width+7)>>3;
    int size=height*rowc_w;
    unsigned char *iimg=(unsigned char *)(pp.img=malloc(size));
    zeromem(iimg,size);
    for (unsigned int y = 0; y<height; y++)
    {
      png_read_row(png_ptr, (png_bytep)pp.row, NULL);
      for (unsigned int x = 0; x<width; x++)
      {
        if (!pp.row[x*4+0] && !pp.row[x*4+1] && !pp.row[x*4+2])
          iimg[x>>3]|=(0x80>>(x&7));
      }
      iimg+=rowc_w;
    }
    pp.img_h->bpnum=1;
  }
  else
  {
    switch (type)
    {
    case PNG_8:
      {
        unsigned char *iimg=(unsigned char *)(pp.img=malloc(width*height));
        for (unsigned int y = 0; y<height; y++)
        {
          png_read_row(png_ptr, (png_bytep)pp.row, NULL);
          for (unsigned int x = 0; x<width; x++)
          {
            if (pp.row[x*4+3]<ALPHA_THRESHOLD)
              *iimg++=0xC0;
            else
            {
              unsigned char c=(pp.row[x*4+0] & 0xE0);
              c|=((pp.row[x*4+1]>>3)&0x1C);
              c|=((pp.row[x*4+2]>>6)&0x3);
              *iimg++=c;
            }
          }
        }
        pp.img_h->bpnum=5;
        break;
      }
    case PNG_16:
      {
        unsigned short *iimg=(unsigned short *)(pp.img=malloc(width*height*2));
        for (unsigned int y = 0; y<height; y++)
        {
          png_read_row(png_ptr, (png_bytep)pp.row, NULL);
          for (unsigned int x = 0; x<width; x++)
          {
            if (pp.row[x*4+3]<ALPHA_THRESHOLD)
              *iimg++=0xE000;
            else
            {
              unsigned int c=((pp.row[x*4+0]<<8)&0xF800);
              c|=((pp.row[x*4+1]<<3)&0x7E0);
              c|=((pp.row[x*4+2]>>3)&0x1F);
              *iimg++=c;
            }
          }
        }
        pp.img_h->bpnum=8;
        break;
      }
#if NEWSGOLD || X75
    case PNG_24:
      {
        unsigned char *iimg=(unsigned char *)(pp.img=malloc((width*height)<<2));
        for (unsigned int y = 0; y<height; y++)
        {
          png_read_row(png_ptr, (png_bytep)pp.row, NULL);
          for (unsigned int x = 0; x<width; x++)
          {
	    unsigned int c;
            *iimg++=pp.row[x*4+2];
            *iimg++=pp.row[x*4+1];
            *iimg++=pp.row[x*4+0];
	    c=pp.row[x*4+3];
//	    if (c>=128) c++;
//	    c*=100;
//	    c>>=8;
            *iimg++=c;//(pp.row[x*4+3]*100)/0xFF;
          }
        }
        pp.img_h->bpnum=0xA;
        break;
      }
#endif
    } */

