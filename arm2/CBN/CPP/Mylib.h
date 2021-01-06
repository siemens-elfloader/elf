
// ��� VC mylib.h 0.1
// �������� ������ �� vc

//#define NEWSGOLD // ��� S75
#define HIGHCOLOR // 16-������ �����
//#define GRAPH  // �������
//#define UNPACK // ���������� �������
//#define NO7Z   // ����� 7z
//#define NOZIP  // ����� zip
//#define NORAR  // ����� rar
//#define NOLOAD // in loadgraph data loaded allready

#include "swilib.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
//#include <mem.h>


extern unsigned int err;
extern int loadfilesize;

#define fread32 ffread
#define fwrite32 ffwrite

#define ffread32 ffread
#define ffwrite32 ffwrite


#ifdef GRAPH
extern int loadgraphsize;
char *loadgraph(char *filename); // ��������� ������� (������������� � ������������) #define HIGHCOLOR ������
#endif

int savefile(char *fname, char *buf, int size);  
char *loadfile(char *filename); // ��������� ����, �����������, ����� � loadfilesize

//void *memset(void *mem, int val, int size); 
void *memsetw(void *mem, int val, int size); 
//int fgets(char *buf,int size,int fh);
//int sscanf(char *buf, char *s, ...);
//void fputc(char c, int fh);
//void fprintf(int fh, char *s, ...);
//char toupper(char c);
//char fgetc(int fh);
//int min(int a, int b);
//int max(int a, int b);
//int abs(int a);
//void printf(char *s,...);
//char *strdup(char *s);
//void *memcpyrev(void *to, void *from, int size);
//int memcmp(char *s1, char *s2, int size);
//char *toup(char *str);			// � �������� ��������
//char *todown(char *str);		// � ������� ��������
int  isalth (unsigned char sym);	// ���������� ������ ?
int  isval (char sym);		// ������ �������� ������ ?
int strchrpos(const char *s, int c);	// ������� ������� � ������ (1-N, 0=���)
int emptystr(char *str);		// ������ �� ������
char  *alltrim (char *str);		// ������� ������� �� ����� ������
int   strcmpsize (const char *s1,const char *s2,int size); // �������� ������ ����� size
int getint(void *ptr); // �������� int
short getshort(void *ptr); // �������� short
void putint(void *ptr, int data); // �������� int
void putshort(void *ptr, short data); // �������� short
void bitblt(void *screen, void *bmp, int x, int y, int sizex, int sizey, int x0, int y0,  int colormask, int flags);
//    void memmove(signed char *to, signed char *from, int size);//�����-� �������-�� ������
char *loadgraph(char *filename); // ��������� ������� (������������� � ������������)
//char *strcpy(char *to, char *from);
//char *strcat(char *to, char *from);

///////////////////
/*
#define public
#define private
#define static
#define protected
#define boolean char
#define byte signed char
#define false 0
#define true 1
#define null 0
#define final const
*/

//extern "C"{

FILE *ffopen(const char * cFileName, unsigned int iFileFlags, unsigned int iFileMode, unsigned int *ErrorNumber);
int ffread(FILE *FileHandler, void *cBuffer, int iByteCount, unsigned int *ErrorNumber);
unsigned int ffwrite(FILE *FileHandler, void const * cBuffer, int iByteCount, unsigned int *ErrorNumber);
void ffclose(FILE *FileHandler, unsigned int *ErrorNumber);
unsigned int llseek(FILE *FileHandler, unsigned int offset, unsigned int origin, unsigned int *ErrorNumber, unsigned int *ErrorNumber2);
void mfree(void *mem);

//}
/*

FILE *ffopen(const char * cFileName, unsigned int iFileFlags, unsigned int iFileMode, unsigned int *ErrorNumber){
  return fopen(cFileName,(iFileFlags&1)?"wb":"rb");
}

int ffread(FILE *FileHandler, void *cBuffer, int iByteCount, unsigned int *ErrorNumber){
  return fread(cBuffer, 1, iByteCount, FileHandler);
}

unsigned int ffwrite(FILE *FileHandler, void const * cBuffer, int iByteCount, unsigned int *ErrorNumber){
  return fwrite(cBuffer, 1, iByteCount, FileHandler);
}

void ffclose(FILE *FileHandler, unsigned int *ErrorNumber){
  fclose(FileHandler);
}

unsigned int llseek(FILE *FileHandler, unsigned int offset, unsigned int origin, unsigned int *ErrorNumber, unsigned int *ErrorNumber2){
  //if(origin==2) return ftell(FileHandler);
  fseek(FileHandler,offset,origin);
  return ftell(FileHandler);
}

void mfree(void *mem){
  free(mem);
}
*/
//void *malloc(unsigned int size){
//}
      
//#define min(a,b) ((a)<(b))?(a):(b)
//#define max(a,b) ((a)<(b))?(b):(a)

//int min(int a, int b);
//int max(int a, int b);
//void *memset(void *mem, int val, int size);

#define SUBPROC
#define REDRAW onredraw

