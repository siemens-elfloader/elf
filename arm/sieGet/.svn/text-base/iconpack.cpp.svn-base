#include "include.h"
#include "iconpack.h"
#include "file_works.h"

IconPack * IconPack::Active = NULL;

static const char * const img_names[TOTAL_ICONS_NUM]=
{
  "about.png",
  "bookmark.png",
  "complete.png",
  "delete.png",
  "delete_succesful.png",
  "downloading.png",
  "error.png",
  "folder.png",
  "get_info.png",
  "idle.png",
  "log.png",
  "logo.png",
  "new.png",
  "pause.png",
  "settings.png",
  "start.png",
  "traffic.png"
};

IconPack::IconPack()
{
  for(int i=0; i < TOTAL_ICONS_NUM; i++)
    data[i] = NULL;
  Setup();
}

IconPack::~IconPack()
{
  Free();
}

void IconPack::Setup()
{
  Free();
  
  char * icons_path = getSymbolicPath("$img\\");
  
  Active = this;
  for(int i=0; i<TOTAL_ICONS_NUM; i++)
  {
    char * img = new char[strlen(icons_path) + strlen(img_names[i])+1];
    strcpy(img, icons_path);
    strcat(img, img_names[i]);
    data[i] = (int)img;
  }
  delete icons_path;
}

void IconPack::Free()
{
  for(int i=0; i < TOTAL_ICONS_NUM; i++)
  {
    if(data[i])
      delete (void *)data[i];
    data[i] = NULL;
  }
}
