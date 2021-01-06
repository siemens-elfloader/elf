/*
sielf (s)tripper

(c)Разработчики эльфпака(Rst7/CBSIE, BoBa и другие), Captain_SISka
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

int main(int argc, char* argv[])
{
if(argc<2) return help();

int ap=1;
if(argv[1][0]=='-')
 {
 //options
 if(strstr(argv[1],"i")) opt_info=1; 
 ap++;
 };
if(argc<=ap) return help();
if(argc>ap+1)
	return pack(argv[ap],argv[ap+1]);
else
	{
   char bu[256],bu2[256];
   strcpy(bu,argv[ap]);
   bu[strlen(bu)-4]=0;
   sprintf(bu2,"%s_new.elf",bu);
   return pack(argv[ap],bu2);
   };
};

