#ifndef ALARM_H
#define ALARM_H

#include "..\lgp.h"

//#define NO_PNG
//#define SIX_ALARMS

#ifdef NEWSGOLD
  #define DEFAULT_DISK "4"
  #define alarm_dir "4:\\Zbin\\alarm\\"
  #define PROFILE_PD_DISC "1"
char alarm_str[]="Alarm_Clock_3=";
#else
  #define DEFAULT_DISK "0"
  #define alarm_dir "0:\\Zbin\\alarm\\"
  #define PROFILE_PD_DISC "0"
  #ifdef X75
char alarm_str[]="Alarm_Clock_3=";
  #else
char alarm_str[]="Alarm_3=";
  #endif
#endif

#ifdef SIX_ALARMS
  #ifndef NEWSGOLD
    #define num_alarms 6
  #else
    #define num_alarms 5
  #endif
#else
  #define num_alarms 5
#endif

#define fon 1
#define st_off 2
#define st_on 3
#define wd_off 4
#define wd_on 5
#define logo 6

char profile_pd_file[]=PROFILE_PD_DISC":\\system\\hmi\\profile.pd";
char cfgfile[]=alarm_dir"alarm.cfg";
char bcfgfile[]=DEFAULT_DISK":\\Zbin\\etc\\alarm_melody.bcfg";
char alarm_ring_elf[]=alarm_dir"alarm_ring.elf";
const char param_new_cfg[]="new_cfg";
const char percent_t[]="%t";

#ifdef NO_PNG
  char fonimg[]=alarm_dir"fon.gpf";
  char icon[]=alarm_dir"icon.gpf";
  char img_ext[]="gpf";
#else
  char fonimg[]=alarm_dir"fon.png";
  char icon[]=alarm_dir"icon.png";
  char img_ext[]="png";
#endif

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

void open_bcfg()
{
  WSHDR *_elf=AllocWS(256);
  wsprintf(_elf,percent_t,bcfgfile);
  ExecuteFile(_elf,0,0);
  FreeWS(_elf);
}

int check_install()
{
  int err2=0;
  unsigned int err;
  if(!isdir(alarm_dir,&err))
  {
    char *msg=malloc(strlen(msg_dir)+strlen(alarm_dir));
    sprintf(msg,msg_dir,alarm_dir);
    ShowMSG(1,(int)msg);
    mfree(msg);
    mkdir(alarm_dir,&err);
  }
  FSTATS fstats;
  if (GetFileStats(alarm_ring_elf,&fstats,&err)==-1)
  {
    ShowMSG(1,(int)msg_no_alarm_ring_elf);
    err2+=1;
  }
  else
    {
      if (GetFileStats(bcfgfile,&fstats,&err)==-1)
      {
        WSHDR *_elf=AllocWS(256);
        wsprintf(_elf,percent_t,alarm_ring_elf);
        ExecuteFile(_elf,0,(void *)param_new_cfg);
        FreeWS(_elf);
        open_bcfg();
      }
    }
  if (GetFileStats(fonimg,&fstats,&err)==-1 || GetFileStats(icon,&fstats,&err)==-1)
  {
    char *msg=malloc(strlen(msg_no_images)+strlen(img_ext)*2);
    sprintf(msg,msg_no_images,img_ext,img_ext);
    ShowMSG(1,(int)msg);
    mfree(msg);
    err2+=1;
  }
  return err2;
}

#endif
