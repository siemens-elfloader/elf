#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
double Lat=44.956353;
double Lon=42.028497;
#include <winsock2.h>


#define PI 3.1415926535
#define offset  268435456
double radius = offset / PI; 
double LToX(double x);
double LToY(double y);
double XToL(double x);
double YToL(double x);
int get_dec(const char *str)
{
	int dec=0;
	int r=0;
	while(str[dec]!=0x2E&&dec<strlen(str))
	{
		if(str[dec]-0x30<0||str[dec]-0x30>9)r++;
		dec++;
	}
	return dec-r;
}

double str_to_double(const char *str)
{
	volatile int flag=0;
	int dec=get_dec(str);
        double r=0.0;
	for(int i=0;i<strlen(str);i++)
	{
          if(str[i]-0x30<0||str[i]-0x30>9)continue;
		if(str[i]==0x2E)
		{
			flag=1;
			dec=get_dec(str);
			continue;
		}
		if(flag)r+=(double)(str[i]-0x30)/pow((double)10,(double)(i-dec));
		else r+=((double)str[i]-0x30)*(double)pow((double)10,(double)(--dec));
	}
	return r;
}
void LonLatAddPixel(double lat, double lon, int deltaX, int deltaY, int z,double *NLon,double *NLat)
{
        *NLon=XToL(LToX(lon) + (deltaX<<(21-z)));
		*NLat=YToL(LToY(lat) + (deltaY<<(21-z)));
}

double round(double num)
{
	double flr = (int)num;

	if(num - flr >= 0.5)
		return ceil(num);
	else
		return flr;
}
double LToX(double x)
{
	return round(offset + radius * x * PI / 180);
}
 
double LToY(double y)
{
	return round(
		offset - radius * 
		log((1 + sin(y * PI / 180))/(1 - sin(y * PI / 180))) / 2);
} 
 
double XToL(double x)
{
	return ((round(x) - offset) / radius) * 180 / PI;
}
 
double YToL(double y)
{
	return (PI / 2 - 2 * atan(exp((round(y)-offset)/radius))) * 180 / PI;
}
#define MAP_X 6
#define MAP_Y 8

int main()
{
/*double NLat=0,NLon=0;
int zoom=9;
LonLatAddPixel(Lat,Lon,0,20,zoom,&NLon,&NLat);
//lat,lon,x+,y+,zoom,ret...)
//printf("http://st-hunter.ru/siemens/maps/?lat=%f&lon=%f&zoom=%d&t=mobile&frmt=png&szx=320&szy=240&color=blue&name=i&q=image",NLat,NLon,zoom);
printf("%f",str_to_double(" 44.3232 "));*/

	
 for(int j=MAP_Y-1;j>1;j--)
    for(int i=MAP_X-1;i>0;i--)
		printf("j:%d i:%d\n",j,i);
_getch();
	return 0;
}