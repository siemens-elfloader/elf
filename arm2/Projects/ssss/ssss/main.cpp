#include <stdio.h>
#include <math.h>
#include <windows.h>

int main()
{
	//формула
		double Z=0,a=0,b=0,c=0,B=0,C=0,A=0;
		double y[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	for(int k=0;k<10;k+=3)
		a+=y[k];
	for(int k=0;k<10;k+=6)
		b+=y[k];

	for(int k=0;k<30;k++)
		c+=y[k];

 Z=sin(a)+B*cos(b)+C/c;
printf("Z=%e\n\n",Z);
 //функция
	b=1;
	B=9;
	C=1;
for(int k=0; k<20;k++)
{
	y[k]=b*log(10*(A*k+C))/sqrt(k+A+B);
	printf("y[%d]=%e\n",k,y[k]);
}

system("pause");
	return 0;
}