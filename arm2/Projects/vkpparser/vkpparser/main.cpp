#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double X1=0,Y1=0,X2=0,Y2=0;
void main()
{
	double ab=0;
	printf("vvedite x1:=");
	scanf("%le",&X1);
	printf("vvedite x2:=");
	scanf("%le",&X2);
	printf("vvedite y1:=");
	scanf("%le",&Y1);
	printf("vvedite y2:=");
	scanf("%le",&Y2);
	ab=sqrt(pow((X2-X1),2)+pow((Y2-Y1),2));
	printf("ab=%e",ab);
}