#include "../inc/swilib.h"
#include "language.h"
#include "main.h"
#include "mediafiles.h"
#include "conf_loader.h"

extern const char playerfolder[128];
extern const char *chotyry="4:";

typedef struct
{
  char shliah[210];
  char artist[30];
  char album[30];
  char track[30];
}mediafile;
mediafile media[];
char curent_state[30];
const RECT Canvas2={0,0,131,175};
int GUI_GUI;
int curentposition=0;
char tosearch[256];
char search_state[256];
void OnRedraw3(MAIN_GUI *data) // OnRedraw
{
  WSHDR* a=AllocWS(128);
  DrawImg(0,0,(int)GetFon());
  wsprintf(a,pt,curent_state);
  DrawString(a,1,3,130,15,FONT_SMALL_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23));
  
  utf8_2ws(a,tosearch,320);
  DrawString(a,2,20,130,100,FONT_SMALL,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23));
  
  wsprintf(a,pt,search_state);
  DrawString(a,1,100,130,130,FONT_SMALL,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23));
  
  FreeWS(a);
}
int MenuKeys2(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  if ((msg->gbsmsg->msg==KEY_DOWN))
  {
    switch(msg->gbsmsg->submess)
    {
    case RED_BUTTON:return(1);
    }
  }
  return(0);
}
const void * const gui_methods3[11]={
  (void *)OnRedraw3,	//Redraw
  (void *)onCreate2,	//Create
  (void *)onClose2,	//Close
  (void *)onFocus2,	//Focus
  (void *)onUnfocus2,	//Unfocus
  (void *)MenuKeys2,	//OnKey
  0,
  #ifdef NEWSGOLD
  (void *)onDestroy,	//Destroy
  #else
  (void *)kill_data,	//Destroy
  #endif
  (void *)method,
  (void *)method,
  0
};

void find_tegs()
{
  int f;
  char file[128];
  unsigned int err;
  FSTATS stat; 
  f=fopen(media[curentposition].shliah, A_ReadOnly+A_BIN, P_READ, &err); 
  GetFileStats(media[curentposition].shliah, &stat, &err); 
  lseek(f,(stat.size-128), 0, &err, &err); 
  fread(f, file, 128, &err);
  fclose(f, &err);
  sprintf(media[curentposition].album,"");
  sprintf(media[curentposition].track,"");
  sprintf(media[curentposition].artist,"");
  if ((file[0]=='T')&&(file[1]=='A')&&(file[2]=='G'))
  {
  int i;
  for (i=3;(file[i]!=0)&&(i<33);i++)
    {
      sprintf(media[curentposition].track,"%s%c",media[curentposition].track,file[i]);
    }
  for (i=33;(file[i]!=0)&&(i<63);i++)
    {
      sprintf(media[curentposition].artist,"%s%c",media[curentposition].artist,file[i]);
    }
  for (i=63;(file[i]!=0)&&(i<93);i++)
    {
      sprintf(media[curentposition].album,"%s%c",media[curentposition].album,file[i]);
    }
  }
  if (strlen(media[curentposition].album)==0){sprintf(media[curentposition].album,"Unknown album");}
  if (strlen(media[curentposition].track)==0){sprintf(media[curentposition].track,"Unknown track");}
  if (strlen(media[curentposition].artist)==0){sprintf(media[curentposition].artist,"Unknown artist");}
}

char extension[3];

void Create()
{
  char folder[256];
  sprintf(folder,tosearch);
  sprintf(curent_state,LG_SEARCHING_FILES);
  REDRAW();
  DIR_ENTRY de;
  unsigned int err;
  char path[128];
  sprintf(path,"%s\\*",folder);
  if (FindFirstFile(&de,path,&err))
  {
    do
    {
      sprintf(extension,"%c%c%c",de.file_name[strlen(de.file_name)-3],de.file_name[strlen(de.file_name)-2],de.file_name[strlen(de.file_name)-1]);
      char temp[128];
      sprintf(temp,"%s\\%s",folder,de.file_name);
      if (!IsFile(de.file_name))
      {
        sprintf(tosearch,temp);
        Create();
      }
      else
      if (!strcmp_nocase(extension,"mp3"))
      {
        sprintf(media[curentposition].shliah,temp);
        find_tegs();
        sprintf(curent_state,LG_READING_TAGS);
        sprintf(search_state,LG_TEXT_1,curentposition);
        REDRAW();
        curentposition++;
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  if (!strcmp_nocase(folder,chotyry))
  {
    sprintf(curent_state,LG_VPORIADKOVUJU);
    sprintf(tosearch,pp);
    REDRAW();
    //Впорядковуємо...
    {
      char name[320];
      for (int i=0;i<curentposition+1;i++)
      {
        for (int j=i+1;j<curentposition;j++)
        {
          if (strcmp(media[i].artist,media[j].artist)>0)
          {
            sprintf(name,media[i].artist);
            sprintf(media[i].artist,media[j].artist);
            sprintf(media[j].artist,name);
            
            sprintf(name,media[i].track);
            sprintf(media[i].track,media[j].track);
            sprintf(media[j].track,name);
            
            sprintf(name,media[i].album);
            sprintf(media[i].album,media[j].album);
            sprintf(media[j].album,name);
            
            sprintf(name,media[i].shliah);
            sprintf(media[i].shliah,media[j].shliah);
            sprintf(media[j].shliah,name);
          }
        }
      }
      
      for (int i=0;i<curentposition+1;i++)
      {
        for (int j=i+1;j<curentposition;j++)
        {
          if ((strcmp(media[i].artist,media[j].artist)==0)&&(strcmp(media[i].album,media[j].album)>0))
          {
            sprintf(name,media[i].artist);
            sprintf(media[i].artist,media[j].artist);
            sprintf(media[j].artist,name);
            
            sprintf(name,media[i].track);
            sprintf(media[i].track,media[j].track);
            sprintf(media[j].track,name);
            
            sprintf(name,media[i].album);
            sprintf(media[i].album,media[j].album);
            sprintf(media[j].album,name);
            
            sprintf(name,media[i].shliah);
            sprintf(media[i].shliah,media[j].shliah);
            sprintf(media[j].shliah,name);
          }
        }
      }
      int f;
      unsigned int err;
      sprintf(curent_state,LG_SAVING);
      sprintf(name,"%smediafiiles.txt",playerfolder);
      f=fopen(name, A_WriteOnly+A_Create, P_WRITE, & err );
      WSHDR* a=AllocWS(256);
      for (int i=0;i<curentposition;i++)
      {
        sprintf(search_state,LG_TEXT_2,curentposition,i);
        REDRAW();
        sprintf(name,"%s\r\n%s\r\n%s\r\n%s\r\n",media[i].artist,media[i].album,media[i].track,media[i].shliah);
        //utf8_2ws(a,name,256);
        //ws_2str(a,name,256);
        fwrite(f,name,strlen(name),&err);
      }
      FreeWS(a);
      fclose(f,&err);
    }
    GeneralFunc_flag1(GUI_GUI,1);
    ViewFiles();
  }
}

int CreateBaseOfMediafiles()
{
  DIR_ENTRY de;
  unsigned int err;
  char name[320];
  sprintf(name,"%smediafiiles.txt",playerfolder);
  if(!FindFirstFile(&de,name,&err))
    {
      MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
      zeromem(main_gui,sizeof(MAIN_GUI));
      main_gui->gui.canvas=(void *)(&Canvas2);
      main_gui->gui.flag30=2;
      main_gui->gui.methods=(void *)gui_methods3;
      main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
      GUI_GUI=CreateGUI(main_gui);
      sprintf(tosearch,chotyry);
      sprintf(curent_state,LG_SEARCHING);
      SUBPROC((void *)Create);
    }
  else
  {
    ViewFiles();
  }
  FindClose(&de,&err);
  return(0);
}
