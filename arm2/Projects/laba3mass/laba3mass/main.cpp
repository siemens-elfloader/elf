#include <conio.h>
#include <stdio.h>
#include <math.h>

double matr[3][3]={{0.5,3.2,7.1},
                   {0,-2.1,3.5},
                   {0.8,2.5,-1.5}
};

int main()
{
   for(int i=0;i<3;i++)
   {
	   matr[i][i]=fabs(matr[i][i]);
   }
   for(int i=0;i<3;i++)
	   for(int j=0;j<3;j++)
	   printf("matr[%d][%d]=%e\n",i,j,matr[i][j]);
	  
	_getch();
	return 0;
}