#ifndef _SmartAlerts_H_
  #define _SmartAlerts_H_

#include "..\lgp.h"

#ifdef NEWSGOLD
  #ifdef S68
    #define alarm_dir "0:\\Zbin\\SmartAlerts\\"
    #define DEFAULT_DISK "0"
  #else
    #define alarm_dir "4:\\Zbin\\SmartAlerts\\"
    #define DEFAULT_DISK "4"
  #endif
#else
  #define alarm_dir "0:\\Zbin\\SmartAlerts\\"
  #define DEFAULT_DISK "0"
#endif

#define num_alarms 5
#define fon 1
#define st_off 2
#define st_on 3
#define wd_off 4
#define wd_on 5
#define logo 6
#define menus 9
#define sevens 8
#define dats 24

#ifdef NEWSGOLD
#pragma swi_number=0x9E
__swi __arm GetMissedEventCount(unsigned int Event);
#endif

char cfgfile[]=alarm_dir"SmartAlerts.cfg";
char fonpng[]=alarm_dir"fon.png";
char ring[]=alarm_dir"alarm_ring.elf";
char icon[]=alarm_dir"icon.png";
const char param_new_cfg[]="new_cfg";
char bcfgfile[]=DEFAULT_DISK":\\Zbin\\etc\\alarm_melody.bcfg";
char bcfgfile1[]=DEFAULT_DISK":\\Zbin\\etc\\SmartAlerts.bcfg";
char sa[]=DEFAULT_DISK":\\Zbin\\Daemons\\SmartAlertsC.elf";

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

void runFile(char *file) 
{
      WSHDR *ws;
      ws=AllocWS(64);
      str_2ws(ws,file,strlen(file)+1);
      ExecuteFile(ws, 0, 0);
      FreeWS(ws);
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
  if (GetFileStats(ring,&fstats,&err)==-1)
  {
    ShowMSG(1,(int)msg_no_alarm_ring_elf);
    err2+=1;
  }
  else
    {
      if (GetFileStats(bcfgfile,&fstats,&err)==-1)
      {
        WSHDR *_elf=AllocWS(100);
        str_2ws(_elf,ring,strlen(ring)+1);
        ExecuteFile(_elf,0,(void *)param_new_cfg);
        FreeWS(_elf);
        runFile(bcfgfile);
      }
    }
  if (GetFileStats(fonpng,&fstats,&err)==-1 || GetFileStats(icon,&fstats,&err)==-1)
  {
    char *msg=malloc(strlen(msg_no_images));
    sprintf(msg,msg_no_images);
    ShowMSG(1,(int)msg);
    mfree(msg);
    err2+=1;
  }
  return err2;
}


#endif
