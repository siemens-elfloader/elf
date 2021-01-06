/*
sielf (s)tripper

(c)Captain_SISka 2007
(r)Rst7
*/

//#include <condefs.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

#include "strip.h"

int opt_info=0;

int help()
{
printf("SiElf Tripper\n  Using: tripper [-i] source.elf [dest.elf]\n  this program clean siemens ELF executables like strip util\n  Options:\n   -i show elf information\n\n");
return 0;
};

int pack(char * src,char * dst)
{
int err;
if((err=ReadElf(src))!=0)
  {
  printf("READ ERROR %d!\n\n",err);
  return -1;
  };
if((err=WriteElf(dst))!=0)
  {
  printf("WRITE ERROR %d!\n\n",err);
  return -1;
  };
extern int newsz,oldsz;
printf("Size reduction %3.2f%%",100.0*(-newsz+oldsz)/oldsz);
return 0;
};

void GetStr(char *str)
{
	int i=strlen(str);
    while(str[i--]!='\\');
	str[i+1]='\\';
	str[i+2]='\0';
}

int main(int argc, char* argv[])
{
	if(argc<2)  {help();goto end;}

int ap=1;

if(argv[1][0]=='-')
 {
 //options
 if(strstr(argv[1],"i")) opt_info=1; 
 ap++;
 }

if(argc<=ap)  {help();goto end;}

if(argc>ap+1){
	 pack(argv[ap],argv[ap+1]);goto end;}
else
	{
   char bu[256],bu2[256];
   strcpy(bu,argv[ap]);
   bu[strlen(bu)-4]=0;
   sprintf(bu2,"%s_new.elf",bu);
    pack(argv[ap],bu2);
	printf("\n");
	
	GetStr(bu2);
printf(bu2);   
}
end:;
_getch();
//goto st;
}

