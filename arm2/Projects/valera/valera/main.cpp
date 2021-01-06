
/* первая
#include <stdio.h>
#include <stdlib.h>

int A[3][3]={{8,2,-2},
             {4,5,2},
             {9,7,4}};
int min=0,max=0;
int result=0;



int main()
{
	min=A[0][0];
	max=A[0][0];
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			if(min>A[i][j])min=A[i][j];
			if(max<A[i][j])max=A[i][j];
		}
		result=max-min;
		printf("min:%d max%d result:%d",min,max,result);
		system("pause");
	return 0;
}*/
/* вторая
#include <stdio.h>
#include <stdlib.h>

int A[3][3]={{8,2,-2},
             {4,5,2},
             {4,0,4}};
int number=0,sum=0,sum2=0;



int main()
{
	
	for(int i=0;i<3;i++)//строки
	{
		sum2=0;
		for(int j=0;j<3;j++)
		{
			sum2+=A[i][j];
		}
		if(sum2>sum){sum=sum2;number=i;}
	}

	printf("stroka:%d sum:%d",number,sum);
		system("pause");
	return 0;
}*/
/* третья
#include <stdio.h>
#include <stdlib.h>

#define M 9

int X[M]={8,2,-2,4,5,2,4,0,4};
int c=0;


int main()
{
	
	for(int i=0;i<M;i++)//строки
	{
		if(X[i]!=0){printf("X[%d]=%d\r\n",i,X[i]);c*=X[i];}
	}

	printf("c=%d",c);
	system("pause");
	return 0;
}*/
/* четвертая
#include <stdio.h>
#include <stdlib.h>



int X[6]={8,2,-2,4,5,2};

int Y[7]={8,2,-2,4,-5,2,-9};
int sum=0;
int main()
{
	
	for(int i=0;i<6;i++)//строки
	{
		if(X[i]>0){sum++;printf("X[%d]=%d\r\n",i,X[i]);}
	}
	
	for(int i=0;i<7;i++)//строки
	{
		if(Y[i]<0){sum++;printf("Y[%d]=%d\r\n",i,Y[i]);}
	}
	printf("sum=%d",sum);
	system("pause");
	return 0;
	}*/
/* пятая
#include <stdio.h>
#include <stdlib.h>


#define C 3
int T[8]={8,2,-2,4,5,2};


int sum=0;
int main()
{
	
	for(int i=0;i<6;i++)//строки
	{
		if(T[i]<C)sum++;
	}
	

	printf("sum=%d",sum);
	system("pause");
	return 0;
}*/
/* шестая
#include <stdio.h>
#include <stdlib.h>



int T[8]={8,2,-2,4,5,2};
int min=0,max=0,mini=0,maxi=0;

int main()
{
	
	for(int i=0;i<6;i++)//строки
	{
		if(min>T[i]){min=T[i];nimi=i}
		if(max<T[i]){max=T[i];maxi=i;}
	}
	T[mini]=max;
	T[maxi]=min;
	system("pause");
	return 0;
}
*/
/* седьмая
#include <stdio.h>
#include <stdlib.h>



int T[8]={8,2,-2,4,5,2};
int max=0,maxi=0;

int main()
{
	max=T[0];
	for(int i=0;i<6;i++)//строки
	{
		if(max<T[i]){max=T[i];maxi=i;}
	}
	T[7]=max;
	T[maxi]=T[7];
	system("pause");
	return 0;
}*/
/*восьмая
#include <stdio.h>
#include <stdlib.h>

#define N 3
#define M 4
int A[N][M]={{2,3,5,0},
             {-1,2,9,4},
			 {4,0,5,1},
};
int B[N]={0};
int max=0;
int main()
{
	for(int i=0;i<N;i++)
	{
		max=A[i][0];
     for(int j=0;j<M;j++)
	 {
		 if(max<A[i][j])max=A[i][j];
	 }
	 B[i]=max;
	}
    for(int i=0;i<N;i++)
		printf("B[%d]=%d\n",i,B[i]);
	system("pause");
	return 0;
}*/
/*девятая

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define n 120

double s=0;

int main()
{
	s=1/1*2;
    for(int i=2;i<n;i++)
	{
      s-=(double)1/(double)i*((double)i+(double)1);
	}
	printf("%f",s);
	system("pause");
	return 0;
}*/
/*десятая
#include <stdio.h>
#include <stdlib.h>
#define NUM 5
int M[NUM];


int main()
{
	int C=1;

	   for(int i=0;i<NUM;i++)
	   {
		   printf("Input num\n");
    scanf("%d",&M[i]);
	   }
	   for(int i=0;i<NUM-1;i++)
	   {
if(M[i]>M[i+1])C=0;
	   }
	   if(C)
	   printf("Vozrastaet\n");
	   else printf("ne vozrastaet\n");
	   system("pause");
	return 0;
}*/
/* 11
#include <stdio.h>
#include <stdlib.h>


int T[8]={8,2,2,4,5,2,2};

int main()
{
	int C=0,count=0;


	printf("Input num\n");
    scanf("%d",&C);
	   
	   for(int i=0;i<8;i++)
	   {
if(C==T[i])count++;
	   }

	   printf("num: %d\n",count);

	   system("pause");
	return 0;
}*/
/*12
#include <stdio.h>
#include <stdlib.h>

#define N 3
#define M 4
double A[N][M]={{2,3,5,0},
             {-1,2,9,4},
			 {4,0,5,1},
};
double min=0;
int main()
{
	for(int i=0;i<N;i++)
      for(int j=0;j<N;j++)
	  {
		  if(min>A[i][j])min=A[i][j];
	  }
	for(int i=0;i<N;i++)
      for(int j=0;j<N;j++)
	  {
		  A[N][M]/=min;
	  }
	   system("pause");
	return 0;
}*/
//остальное то же самое..ток цифры другие))