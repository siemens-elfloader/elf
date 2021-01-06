#define byte unsigned char
#define FILE int
#define BUFFER_SIZE 1024
#define afwrite(F, D, L, ERR) fwrite(F, D, L, ERR)
#define afread(F, D, L, ERR) fread(F, D, L, ERR)
#define free(x) mfree(x)
#pragma pack()

#define O_RDONLY       0x0000
#define _O_RDONLY      0x0000
#define O_WRONLY       0x0001
#define _O_WRONLY      0x0001
#define O_RDWR         0x0002
#define _O_RDWR        0x0002
#define O_RDWRMASK     0x0003 /* Mask used to get O_RDONLY etc. */
#define _O_RDWRMASK    0x0003
#define O_APPEND       0x0008
#define _O_APPEND      0x0008
#define O_TRUNC        0x0200
#define _O_TRUNC       0x0200
#define O_CREAT        0x0100
#define _O_CREAT       0x0100
#define O_BINARY       0x8000
#define _O_BINARY      0x8000
#define O_TEXT         0x4000
#define _O_TEXT        0x4000

#define SEEK_SET        0
#define SEEK_CUR        1
#define SEEK_END        2

typedef struct{
  //short bfType;
  long bfSize;
  short bfReserved1;
  short bfReserved2;
  long bfOffBits;
} BITMAPFILEHEADER;

typedef struct{
    long biSize;
    long biWidth;
    long biHeight;
    short biPlanes;
    short biBitCount;
    long biCompression;
    long biSizeImage;
    long biXPelsPerMeter;
    long biYPelsPerMeter;
    long biClrUsed;
    long biClrImportant;
} BITMAPINFOHEADER;

typedef struct{
  int b_pos;
  byte data[BUFFER_SIZE];
} FILEBUFFER;

extern void readpos(int hFile, int pos, void *data, int length);
extern void writepos(int hFile, int pos, void *data, int length);
extern int rgbwidth(int Width, int bits);
extern void showerror(char *message, int errorcode);
extern void getrgb(int color, int *r, int *g, int *b);
extern void readposbuffered(int hFile, int pos, void *data, int length, FILEBUFFER *buffer);
int get_file_size(char* fname);
int fread32(int fh, void *buf, int len, unsigned int *err);
int read32pos(int hFile, int pos, void *data, int length);
unsigned int write32pos(int hFile, int pos, void *data, int length);
unsigned int fwrite32(int fh, void *buf, int len, unsigned int *err);
void str_append(char *string, char *app);
int open(char *filename, int mode, int perm);
int close(int hFile);
int read(int hFile, void *data, int length);
int write(int hFile, void *data, int length);
int __write(int hFile, void *data, int length);
int fprintf(int hFile, const char *fmt, ...);
int dlseek(int hFile, int offset, int mode);
int strpos(char *source, char *search);
WSHDR * char2WSHDR(const char *data);
void str2WSHDR(WSHDR *ws0, const char *data);
int checkfile(char *filename);


