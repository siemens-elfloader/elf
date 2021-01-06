#ifndef ALARM_H
#define ALARM_H

#include "..\lgp.h"

const char percent_t[]="%t";
const char percent_s[]="%s";
const char percent_d[]="%d";
const char txt_null[]="";
const char percent_txt[]="%t: ";

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#define PROFILE_PD_DISC "1"
#else
#define DEFAULT_DISK "0"
#define PROFILE_PD_DISC "0"
#endif

#ifdef NEWSGOLD
#define CBOX_CHECKED 0xE116
#define CBOX_UNCHECKED 0xE117
#else
#define CBOX_CHECKED 0xE10B
#define CBOX_UNCHECKED 0xE10C
#endif

#define alarm_dir DEFAULT_DISK":\\Zbin\\alarm2\\"

#define MYMAGIC 0xA1B2C3D4

char icon1[] = alarm_dir"icons\\logo.png";		//значек будильника вверху
char icon2[] = alarm_dir"icons\\alarm_on.png";		//в списке вкл
char icon3[] = alarm_dir"icons\\alarm_off.png";		//выкл
char icon4[] = alarm_dir"icons\\addalarm.png";		//иконка перед добавлением нового будильника
//char icon5[] = alarm_dir"icons\\settings.png";	//иконка настройки вверху
const char icon_ms[] = alarm_dir"icons\\icon.png";		//иконка будильника на главном экране
const char ring_logo[] = alarm_dir"icons\\ring_logo.png";	//картинка будильника в ring.elf

const char default_cfgfile[]=alarm_dir"config.dat";
const char default_cfgmelody[]="0:\\Sounds\\AlarmMelody.wav";
const char ring_elf[]=alarm_dir"ring.elf";
const char profile_pd_file[]=PROFILE_PD_DISC":\\system\\hmi\\profile.pd";
const char ms_pic[]=alarm_dir"icons\\ms.dat";

#if (NEWSGOLD || X75)
const char profile_pd_magic[]="Alarm_Clock_3=";
#else
const char profile_pd_magic[]="Alarm_3=";
#endif

const char daemon_name[]="alarm daemon";
const char ring_name[]="alarm ring";
const char alarm_name[]="alarm";

typedef struct
{
  int magic;
  char name[64];
  char use;
  char melody[128];
  char vibra_power;
  char volume;
  bool set_profile;
  char restart_time;
  char count;
}ring_settings;

typedef struct
{
  void *next;
  bool status;
  char hour;
  char min;
  ring_settings ring;
}MYLIST;


unsigned short maincsm_name_body[140];
extern void kill_data(void *p, void (*func_p)(void *));

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

const int minus11=-11;

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

#endif
