#include "../include.h"
#include "cache.h"
#include "../draw/image.h"
#include "../internet/utils.h"

void load_cache()
{
for(int j=0;j<MAP_Y;j++)
for(int i=0;i<MAP_X;i++)
  {
  sprintf(filename,"%scache%f_%f\\map_%d_%d_%d_%d.png",elf_path,longitude,latitude,i,j,zoom,map_type);
  if(is_file_exists(filename))sprintf(filename,"%s%s",elf_path,resource[NO_TILE]);
  map[i][j]=CreateIMGHDRFromPng(filename);
  }
}

void search_cache()
{
  mode=2;//загрузка кеша
  DIR_ENTRY de;
  char folder[128];
  strcpy(folder,elf_path);
  strcat(folder,"*.*");

    if (FindFirstFile(&de,folder,0))
  {
    do
    {
      if(strstr(de.file_name,"cache"))
      {
        strcpy(folder,de.file_name);
        sscanf(folder,"cache%lf_%lf",&longitude,&latitude);
        zoom=Zoom;

       goto a;
      }
    }
    while(FindNextFile(&de,0));
  }
a:
       FindClose(&de,0);
       SUBPROC((void*)load_cache);
       mode=0;//загрузили кеш
}
