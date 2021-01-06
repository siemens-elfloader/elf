#include <swilib.h>
#include "config.h"
#include "engine.h"



SAVE_DATA savedata;


void SetDefaultSettings()
{
  savedata.difficulty = DIFF_NORMAL;
  savedata.opened_levels = 1;
  savedata.recs_autosave = 1;
  savedata.SoundsEnable = 0;
  savedata.SndEnable = 0;
  savedata.StdSnd_user = 52;
  savedata.StdSnd_brick = 53;
  savedata.VibraEnable = 0;
  savedata.SndVolume = 2;
  savedata.VibraVolume = 20;
  savedata.VibraCount = 15;
  savedata.tmr_speed = 9;
  zeromem(savedata.recs,sizeof(RECORDS)*MAX_RECORDS);
}

static int f;
void saveSettings()
{
  if((f=fopen("savedata.bin",A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,0))!=-1)
  {
   fwrite(f,&savedata,sizeof(savedata),0);
   fclose(f,0);
  }
  else 
  {
    ShowMSG(1,(int)"не могу сохранить настройки!");
  }
}

void loadSettings()
{
  if((f=fopen("savedata.bin",A_ReadOnly+A_BIN,P_READ,0))!=-1)
  {
    fread(f,&savedata,sizeof(savedata),0);
    fclose(f,0);
  }
  else
  {
    ShowMSG(1,(int)"не могу загрузить настройки!");
    SetDefaultSettings();
    saveSettings();
  }
}



