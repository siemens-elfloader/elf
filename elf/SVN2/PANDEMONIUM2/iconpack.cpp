#include "include.h"
#include "iconpack.h"

IconPack * IconPack::Active = NULL;

static const char * const img_names[TOTAL_ICONS_NUM]=
{
  "about.png",
  "update.png",
  "reboot.png",
  "config.png"
};

IconPack::IconPack()
{
  for(int i=0; i < TOTAL_ICONS_NUM; i++)
    data[i] = NULL;
  for(int i=0; i < 7; i++)
    mode_data[i] = NULL;
  Setup();
}

IconPack::~IconPack()
{
  Free();
}

extern char basepath[128];

void IconPack::Setup()
{
  Free();
  extern const char IMG_PATH[128]; 
  Active = this;
  for(int i=0; i<TOTAL_ICONS_NUM; i++)
  {
    char * img = new char[strlen(IMG_PATH) + strlen(img_names[i])+1];
    strcpy(img, IMG_PATH);
    strcat(img, img_names[i]);
    data[i] = (int)img;
  }  
  
  for(int i=0;i<7;i++)
    {
     char * img=new char[strlen(IMG_PATH) + 11];
     sprintf(img,"%s%c%c%s.png",IMG_PATH,i&MODE_ENABLED_NEW?'E':'D',i&MODE_ENABLED_OLD?'E':'D',i&MODE_UPDATEABLE?"G":"");
     mode_data[i] = (int)img;
    };
     
}

void IconPack::Free()
{
  for(int i=0; i < TOTAL_ICONS_NUM; i++)
  {
    if(data[i])
      delete (void *)data[i];
    data[i] = NULL;
  }
  
for(int i=0; i < 7; i++)
  {
    if(mode_data[i])
      delete (void *)data[i];
    data[i] = NULL;
  }
  
}
