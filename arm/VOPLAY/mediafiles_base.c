#include "../inc/swilib.h"
#include "language.h"
#include "main.h"
#include "mediafiles.h"
#include "conf_loader.h"
#include "mediafiles_base.h"
#include "libr.h"

int reload=0;
extern const char playerfolder[128];
//extern const char *chotyry="4:";
char chotyry[128];
extern const char folder_scan[128];
typedef struct
{
  char shliah[160];
  char artist[30];
  char album[30];
  char track[30];
}mediafile;
mediafile media[1024];
char curent_state[30];
const RECT Canvas2={0,0,239,319};
int GUI_GUI;
int curentposition=0;
char tosearch[256];
char search_state[256];
void OnRedraw3(MAIN_GUI *data) // OnRedraw
{
  WSHDR* a=AllocWS(128);
  DrawImg(0,0,(int)GetFon());
  wsprintf(a,pt,curent_state);
  DrawString(a,5,3,ScreenW()-6,ScreenH(),FONT_SMALL_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23));
  
  utf8_2ws(a,tosearch,320);
  DrawString(a,10,40,ScreenW()-10,180,FONT_SMALL,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23));
  
  wsprintf(a,pt,search_state);
  DrawString(a,5,ScreenH()-GetFontYSIZE(FONT_SMALL_BOLD)*3-4,234,320,FONT_SMALL_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23));
  
  //wsprintf(a,"%t","Отмена");
//  DrawString(a,5,ScreenH()-GetFontYSIZE(FONT_SMALL_BOLD)-4,234,320,FONT_SMALL_BOLD,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23));
  //DrawLine(0,320-GetFontYSIZE(FONT_SMALL_BOLD)-4,240,320-GetFontYSIZE(FONT_SMALL_BOLD)-4,0,GetPaletteAdrByColorIndex(0));
  //DrawLine(0,23,240,23,0,GetPaletteAdrByColorIndex(0));
  FreeWS(a);
}

extern void kill_data(void *p, void (*func_p)(void *));
int create_stopped=0;
int MenuKeys2(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  if ((msg->gbsmsg->msg==KEY_DOWN))
  {
    switch(msg->gbsmsg->submess)
    {
   // case RIGHT_SOFT:case RED_BUTTON:{create_stopped=1;return(1);}
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
  (void *)kill_data,	//Destroy
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
  char artist[30];
  char album[30];
  char track[30];
  sprintf(album,"");
  sprintf(track,"");
  sprintf(artist,"");
  if ((file[0]=='T')&&(file[1]=='A')&&(file[2]=='G'))
  {
  int i;
  for (i=3;(file[i]!=0)&&(i<33);i++)
    {
      sprintf(track,"%s%c",track,file[i]);
    }
  for (i=33;(file[i]!=0)&&(i<63);i++)
    {
      sprintf(artist,"%s%c",artist,file[i]);
    }
  for (i=63;(file[i]!=0)&&(i<93);i++)
    {
      sprintf(album,"%s%c",album,file[i]);
    }
  }
  if (!strlen(album)) {sprintf(media[curentposition].album, "Unknown album"); }else{sprintf(media[curentposition].album,  album);}
  if (!strlen(track)) {sprintf(media[curentposition].track, "Unknown track"); }else{sprintf(media[curentposition].track,  track);}
  if (!strlen(artist)){sprintf(media[curentposition].artist,"Unknown artist");}else{sprintf(media[curentposition].artist,artist);}
}

char extension[3];

void Create()
{
  char folder[256];
  sprintf(folder,tosearch);
  sprintf(curent_state,(char *)LG_SEARCHING_FILES);
  REDRAW();
  DIR_ENTRY de;
  unsigned int err;
  char path[256];
  sprintf(path,"%s\\*",folder);
  if (FindFirstFile(&de,path,&err))
  {
    do
    {
      sprintf(extension,"%c%c%c",de.file_name[strlen(de.file_name)-3],de.file_name[strlen(de.file_name)-2],de.file_name[strlen(de.file_name)-1]);
      char temp[256];
      sprintf(temp,"%s\\%s",folder,de.file_name);
      if (!IsFile(de.file_name))
      {
        sprintf(tosearch,temp);
      //  if(create_stopped!=1)
          Create();
     /*   else   
        {
          create_stopped=0;
          goto a;
        }*/
      }
      else
      if (!strcmp_nocase(extension,"mp3"))
      {
        sprintf(media[curentposition].shliah,temp);
        find_tegs();
        sprintf(curent_state,(char *)LG_READING_TAGS);
        sprintf(search_state,(char *)LG_TEXT_1,curentposition);
        REDRAW();
        curentposition++;
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  if (!strcmp_nocase(folder,chotyry))
  {
    sprintf(curent_state,(char *)LG_VPORIADKOVUJU);
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
      sprintf(curent_state,(char *)LG_SAVING);
      sprintf(name,"%smediafiles.txt",playerfolder);
      f=fopen(name, A_ReadWrite+A_Create, P_READ+P_WRITE, & err );
      if ( f==-1 ) 
      {
        ShowMSG(1,(int)"Can't open mediafiles.txt");
        fclose( f, & err ); 
      }
      else
      {
      for (int i=0;i<curentposition;i++)
      {
        sprintf(search_state,(char *)LG_TEXT_2,curentposition,i+1);
        REDRAW();
        sprintf(name,"%s\r\n%s\r\n%s\r\n%s\r\n",media[i].artist,media[i].album,media[i].track,media[i].shliah);
        if (((media[i].shliah[strlen(media[i].shliah)-3]=='m')||(media[i].shliah[strlen(media[i].shliah)-3]=='M'))&&((media[i].shliah[strlen(media[i].shliah)-2]=='p')||(media[i].shliah[strlen(media[i].shliah)-2]=='P'))&&(media[i].shliah[strlen(media[i].shliah)-1]=='3'))
        {
         fwrite(f,name,strlen(name),&err);
        }
      }
      fclose(f,&err);
      }
    }
 // a:
    GeneralFunc_flag1(GUI_GUI,1);
    reload=0;
    ViewFiles();
  }
}

int CreateBaseOfMediafiles()
{
  DIR_ENTRY de;
  unsigned int err;
  char name[320];
  sprintf(name,"%smediafiles.txt",playerfolder);
  if(reload==1) unlink(name,&err);
  if(!FindFirstFile(&de,name,&err))
    {
      MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
      zeromem(main_gui,sizeof(MAIN_GUI));
      main_gui->gui.canvas=(void *)(&Canvas2);
      main_gui->gui.flag30=2;
      main_gui->gui.methods=(void *)gui_methods3;
      main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
      GUI_GUI=CreateGUI(main_gui);
      sprintf(chotyry,folder_scan);
      chotyry[strlen(chotyry)-1]='\0';
      sprintf(tosearch,chotyry);
      sprintf(curent_state,(char *)LG_SEARCHING);
      curentposition=0;
      SUBPROC((void *)Create);
      //reload=0;
    }
  else
  {
    ViewFiles();
  }
  FindClose(&de,&err);
  return(0);
}
