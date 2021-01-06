#include <stdlib.h>
#include <stdio.h>
char add[128];

char *ret()
{
	return add;
}

int main()
{
	//add=new char(128);
	sprintf(add,"sss");
	printf("a0%x\n",ret());
	system("pause");
	return 0;
}