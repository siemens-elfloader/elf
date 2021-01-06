#include <stdio.h>
#include <math.h>
#include <conio.h>
const double PI=3.1415926;
void main()
{
double x[100],y[100],dx=PI/8;
FILE *out;
x[0]=0;

out=fopen("D:\\data.dat","w");
if(out==0)
{
printf("ERROR! data.dat");
goto end;
}
/*
for(int i=0; x[i]<=5*PI; i++)
{
y[i]=cos(x[i])-sqrt(x[i]);
x[i+1]=x[i]+dx;
printf("x[%i]=%e \t y[%i]=%e \n",i,x[i],i,y[i]);
fprintf(out,"x[%i]=%e\t y[%i]=%e \n",i,x[i],i,y[i]);
}*/
int i=0;
while(x[i]<=5*PI)
{
y[i]=cos(x[i])-sqrt(x[i]);
x[i+1]=x[i]+dx;
printf("x[%i]=%e \t y[%i]=%e \n",i,x[i],i,y[i]);
fprintf(out,"x[%i]=%e\t y[%i]=%e \n",i,x[i],i,y[i]);
i++;
}

fclose(out);
end:
_getch();
}