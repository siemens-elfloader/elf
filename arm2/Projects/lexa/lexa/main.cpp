#include "stdlib.h"
#include "stdio.h"
#include <string.h>
char string1[64]="tessassst";
char string2[64]="ta";

int delete_chars(char *src,char *dest)
{
//if(!src||!dest)return 0;
for(int i=0;i<strlen(src);i++)
{
	for(int j=0;j<strlen(dest);j++)
	{
		if(src[i]==dest[j])src[i]=(char)" ";
		
	}
}
return 1;
}

int main()
{
printf("str1:%s\nstr2:%s\n",string1,string2);
delete_chars(string1,string2);
printf("after\nstr1:%s\nstr2:%s\n",string1,string2);
system("pause");
	return 0;
}