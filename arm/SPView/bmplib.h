#include "../inc/swilib.h"

#  define BF_TYPE 0x4D42
#  define BI_RGB       0             /* No compression - straight BGR data */
#  define BI_RLE8      1             /* 8-bit run-length compression */
#  define BI_RLE4      2             /* 4-bit run-length compression */
#  define BI_BITFIELDS 3             /* RGB bitmap with RGB masks */
#  define BI_JPEG      4
#  define BI_PNG       5
#  define BI_ALPHABITFIELDS 6

#pragma pack(push, 1) //устанавливаем другое выравнивание полей

typedef struct                       /**** BMP file header structure ****/
{
  unsigned short bfType;           /* Magic number for file */
  unsigned int   bfSize;           /* Size of file */
  unsigned short bfReserved1;      /* Reserved */
  unsigned short bfReserved2;      /* ... */
  unsigned int   bfOffBits;        /* Offset to bitmap data */
} BITMAPFILEHEADER;

#pragma pack(pop)  //возвращаем выравнивание

typedef struct                       /**** BMP file info structure ****/
{
  unsigned int   biSize;           /* Size of info header */
  int            biWidth;          /* Width of image */
  int            biHeight;         /* Height of image */
  unsigned short biPlanes;         /* Number of color planes */
  unsigned short biBitCount;       /* Number of bits per pixel */
  unsigned int   biCompression;    /* Type of compression to use */
  unsigned int   biSizeImage;      /* Size of image data */
  int            biXPelsPerMeter;  /* X pixels per meter */
  int            biYPelsPerMeter;  /* Y pixels per meter */
  unsigned int   biClrUsed;        /* Number of colors used */
  unsigned int   biClrImportant;   /* Number of important colors */
} BITMAPINFOHEADER;

int SaveBMP(const char *fname, const char *rastrum, const int width, const int height,  char *palette,
                      const unsigned int palette_size, const unsigned int bit_count, const unsigned int compression);
char *SieRastrDecoder(const char *rastrum, const int permission);
