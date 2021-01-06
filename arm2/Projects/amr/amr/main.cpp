#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <io.h>
#include <windows.h>


#define amr_header 6
#define infile "C:\\4.amr"

const int FrameLenTable[8] = { 13, 14, 16, 18, 20, 21, 27, 32 };
typedef struct FRAME
{
int len,count,mode;
}FRAME;
int GetFileSize(char *fname)
{
struct stat st_one;
stat(fname,&st_one);
return st_one.st_size;
}
FRAME GetFrameStats(char *fname)
{
FRAME frame;
char header[amr_header+1];
FILE *f=fopen(fname,"r");
fread(header,amr_header+1,1,f);//+1 - first frame header
frame.mode = (header[6] & 0x38) >> 3;//3 bit is mode
frame.len=FrameLenTable[frame.mode];
frame.count=(GetFileSize(fname)-6)/frame.len;
fclose(f);
return frame;
}


int r=0;

int main()
{
	char head[6];
    char frame_header[1];
	FRAME frame=GetFrameStats(infile);
	printf("File: %s mode:%d len:%d count:%d\n",infile,frame.mode,frame.len,frame.count);
    FILE *in=fopen(infile,"r");
	FILE *out=fopen("c:\\frame.dat","w");
	r=fread(head,6,1,in);//6 bytes
	char frame_data[20];
//for(int i=0;i<frame.count;i++)
	{
      fread(frame_data,20,1,in);//frame data	
      fwrite(frame_data,20,1,out);
	}
	fclose(in);
fclose(out);
	_getch();
	return 0;
}

unsigned char data[20] = {//вытянул фрейм
	0x24/*первый байт-заголовок*/, 0x63, 0x3C, 0x67, 0xE0, 0x00, 0x1F, 0xF5, 0x01, 0xF0, 0xFC, 0x3F, 0x77, 0x18, 0x61, 0x86, 
	0x00, 0x00, 0x00, 0x00
};