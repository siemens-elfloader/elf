#pragma pack(1)
typedef struct  
{
        WORD  bftype;//2
        DWORD bfsize;//4
        WORD  rez1; //2
        WORD  rez2;//2
        DWORD bfoffbits;//4
} BMP_HEAD;


typedef struct
{
        DWORD  bisize;//4
        LONG   biwidth;//4
        LONG   biheight;//4
        WORD   biplanes;//2
        WORD   bibitcount;//2
        DWORD  bicompression;//4
        DWORD  bisizeimage;//4
        LONG   bix;//4
        LONG   biy;//4
        DWORD  biclrused;//4
        DWORD  biclrimp;//4
}BITMAP_HEAD;

typedef struct
{
  int last_err;
  char *fname;
  char *Bitmap;
  IMGHDR *img;
  BMP_HEAD HEAD;
  BITMAP_HEAD MAP_HEAD;
  char *pallete;
}BMP_HDR;
#pragma pack()

#define SIZE_BMP_HEAD 14
#define SIZE_BITMAP_HEAD 40

//bicompression;
#define BI_RGB  0
#define BI_RLE8 1
#define BI_RLE4 2
#define BI_BITFIELDS 3
#define BI_JPEG 4
#define BI_PNG 5
#define BI_ALPHABITFIELDS 6

//bibitcount
//1, 2, 4, 8, 16, 24, 32, 48
#define BITS_1 1
#define BITS_2 2//not offical supported
#define BITS_4 4
#define BITS_8 8
#define BITS_16 16
#define BITS_24 24
#define BITS_32 32
#define BITS_48 48

BMP_HDR readBmp(char *fname);
int SaveBmp(IMGHDR *img,char *fname);
//errors
#define UNK_FRMT_ERR -1;
#define NO_ERR 1
#define NOT_CREATE_ERR -1
#define NOT_SUPP_ERR -3
//png bpnum
#define PNG_24  0x0A //type=3
#define PNG_16  0x08 //type=2
#define PNG_8   0x05//type=1
