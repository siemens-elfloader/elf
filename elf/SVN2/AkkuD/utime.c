#include "utime.h"
#include <time.h>

#define ISRAMFUNCDEFINED(a) ((unsigned int)(a)!=0xFFFFFFFF)


/*
#define wslen(ws) ws->wsbody[0]


#ifndef DSTMINUTES
#define DSTMINUTES 60
#endif

#define FALSE 0
#define TRUE 1



#define SECSPERMIN      60
#define MINSPERHOUR     60
#define HOURSPERDAY     24
#define DAYSPERWEEK     7
#define DAYSPERNYEAR    365
#define DAYSPERLYEAR    366
#define SECSPERHOUR     (SECSPERMIN * MINSPERHOUR)
#define SECSPERDAY      ((long) SECSPERHOUR * HOURSPERDAY)
#define MONSPERYEAR     12
#define YEAR_BASE    1995
#define isleap(y) ((((y) % 4) == 0 && ((y) % 100) != 0) || ((y) % 400) == 0)
#define YEAR_DAYS(y) year_lengths[isleap(y)?1:0]
static int	mon_lengths[2][MONSPERYEAR] = {
	{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

static int	year_lengths[2] = {
	DAYSPERNYEAR, DAYSPERLYEAR
};

typedef struct
{
  char yearNormBudd; //1 - norm, 2 - buddhist
  char dateFormat;
  char timeFormat; //0-24h, 1-12h
  char timeZone; //internal representation
  char isAutoTime1; 
  char isAutoTime2;
}TDateTimeSettings;

*/



UTIME DateTime2Utime(TDate* date,TTime* time)
{
  struct tm q;
  memset(&q,0,sizeof(q));
  q.tm_sec=time->sec;
  q.tm_min=time->min;
  q.tm_hour=time->hour;
  q.tm_mday=date->day;
  q.tm_mon=date->month-1;
  q.tm_year=date->year-1900;
  
  UTIME a=mktime(&q);

//  s=  ctime((const long*)&a);
//  ShowMSG(1,(int)s);

  TDateTimeSettings *ts=RamDateTimeSettings();
  int zone_ofs_minutes=ISRAMFUNCDEFINED(ts)?GetTimeZoneShift(date,time,ts->timeZone):0;
 
  a-=zone_ofs_minutes*60;
  return a; 
};

UTIME DateTime2UtimeM(int year,int month,int day,int hour,int min)
{
  /*UTIME a=0;
  for(int y=YEAR_BASE;y<year;y++) a+=YEAR_DAYS(y);
  int * md=mon_lengths[isleap(year)?1:0];
  month--;
  for(int m=0;m<month;m++) a+=md[m];
  a+=(day-1);
  TDateTimeSettings * ds=RamDateTimeSettings();
  return SECSPERMIN*(min+MINSPERHOUR*(hour+HOURSPERDAY*a));*/
  TDate xdate;
  TTime xtime;
  xdate.year=year;
  xdate.month=month;
  xdate.day=day;
  xtime.hour=hour;
  xtime.min=min;
  xtime.sec=0;
  return DateTime2Utime(&xdate,&xtime);
};


UTIME Now()
{
  TDate d;
  TTime t;
  GetDateTime(&d,&t);
  return DateTime2Utime(&d,&t);
};



float Utime2Hours(UTIME u)
{
  return u*(1.0/3600.0);
};


UTIME Hours2Utime(float h)
{
  return (int)(h*3600.0);
};





