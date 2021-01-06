#include <conio.h>
#include <stdio.h>
#include <math.h>
const double PI=3.1415926;


void main()
{
 double **matr;
 double max=0,min=0;
 int N,M;

 FILE *f=fopen("D:\\data.dat","w");
 if(f==0)
 {
	 printf("Error! data.dat");
	 goto end;
 }
 printf("Enter N=");
 scanf("%d",&N);
 printf("Enter M=");
 scanf("%d",&M);

 matr=new double*[N];

 
 if(matr==0)
 {
	 printf("Error! memory not allocated!");
	 goto end;
 }

 for(int i=0;i<N;i++)
 {
 matr[i]=new double[M];
  if(matr[i]==0)
 {
	 printf("Error! memory not allocated to matr[%d]!",i);
	 goto end;
 }
 }

for(int i=0;i<N;i++)
{
  for(int j=0;j<N;j++)
  {
	  matr[i][j]=2*sin(3.*i)+cos((double)j);
	  if(max<matr[i][j])max=matr[i][j];
      if(min>matr[i][j])min=matr[i][j];
	  fprintf(f,"matr[%d][%d]=%e\n",i,i,matr[i][j]);
	  printf("matr[%d][%d]=%e\n",i,i,matr[i][j]);

  }
  
}
for(int i=0;i<N;i++)
delete matr[i];

delete []matr;

	  fprintf(f,"max=%e min=%e\n",max,min);
      printf("max=%e min=%e\n",max,min);

 end:
    fclose(f);
	_getch();
}