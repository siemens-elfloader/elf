#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char str[32]="0:\\111dsd.elf";
char *GetFileName(char *fname){return strrchr(fname,'\\')+1;}
char *msg;

char *f()
{
	    char fname[32];
	//strcpy(fname,GetFileName(str));
		sprintf(fname,"sd%s",(char*)GetFileName(str));
	return fname;
}


void main()
{



  printf("%s", f());
	system("pause");
}