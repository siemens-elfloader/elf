#include "utime.h"
//#include <time.h>

#define ISRAMFUNCDEFINED(a) ((unsigned int)(a)!=0xFFFFFFFF)

#define SECSPERMIN  60
#define MINSPERHOUR     60
#define HOURSPERDAY     24
#define DAYSPERWEEK     7
#define DAYSPERNYEAR    365
#define DAYSPERLYEAR    366
#define SECSPERHOUR     (SECSPERMIN * MINSPERHOUR)
#define SECSPERDAY      ((long) SECSPERHOUR * HOURSPERDAY)
#define MONSPERYEAR 12
#define YEAR_BASE 2000

static  int    mon_lengths[2][MONSPERYEAR] = {
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

#define isleap(y)  (((y) % 4 == 0 && (y) % 100 != 0) || (y) % 400 == 0)
#define YEAR_DAYS(y) (isleap(y)?DAYSPERLYEAR:DAYSPERNYEAR)


UTIME DateTime2Utime(TDate* date,TTime* time)
{    
  UTIME a=0;
  for(int y=YEAR_BASE;y<date->year;y++) a+=YEAR_DAYS(y);
  int * md=mon_lengths[isleap(date->year)?1:0];
  for(int m=0;m<date->month;m++) a+=md[m];
  a+=(date->day-1);
  TDateTimeSettings * ts=RamDateTimeSettings();
  int zone_ofs_minutes=ISRAMFUNCDEFINED(ts)?GetTimeZoneShift(date,time,ts->timeZone):0; 
  return time->sec+SECSPERMIN*((time->min-zone_ofs_minutes)+MINSPERHOUR*(time->hour+HOURSPERDAY*a)); 
};

UTIME DateTime2Utime(int year,int month,int day,int hour,int min)
{
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





