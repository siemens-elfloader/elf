#include "swilib.h"
extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

char days[7];
char *day[7]={"Ïí","Âò","Ñð","×ò","Ïò","Ñá","Âñ"};
TTime alarm_time;
int snooze_time;
int alarm_active;
int auto_snooze;
int   alarm_hour=0;
int   alarm_min=0;

void ParseSnoozeTime(char *s)
{
//  do_logwrite(s);
  int time=strtoul(s,0,10);
  snooze_time=time/60;
}



void GetTime(TTime *t,int time)
{
  time=time/60;
  int hour=time/60;
  int min=time%60;
  t->hour=hour;
  t->min=min;
  alarm_hour=hour;
  alarm_min=min;
}

void ParseAlarmTime(char *s)
{
//    do_logwrite(s);
  int time;
  sscanf(s,"%i",&time);//28500
  GetTime(&alarm_time,time);
}

void ParseDayInUse(char *s)
{
  //do_logwrite(s);
  char *p=strrchr(s,'=')+1;
  //char *p=(char *)malloc(1);
  for(int i=0;i<7;i++)
  {
    *p=*(s+i);
    days[i]=strtoul(p,0,10);
  }
  mfree(p);
}

void ParseAlarmActive(char *s)
{
//  do_logwrite(s);
  alarm_active=strtoul(s,0,10);
}

void ParseAutoSnooze(char *s)
{
//  do_logwrite(s);
  auto_snooze=strtoul(s,0,10);
}
