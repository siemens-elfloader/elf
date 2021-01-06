#include "../inc/swilib.h"
#include "language.h"
#include "main.h"
#include "mainmenu.h"
#include "conf_loader.h"

extern const char playerfolder[128];

int curent=0,select_art=0,select_alb=0,select_tra=0,max_art,max_alb,max_tra;
int ToView=1;
char masyv[30000];
typedef struct
{
  char c[30];
  int i;
}p;
p artists[50],albums[50],tracks[200];
const RECT Canvas3={0,0,131,175};
int GUI2;
void OnRedraw4(MAIN_GUI *data) // OnRedraw
{
  WSHDR* a=AllocWS(128);
  WSHDR* b=AllocWS(128);
  DrawImg(0,0,(int)GetFon());
  switch(ToView)
  {
  case 1:
  {
    int bottom,top;
    if (max_art>9)
    {
    if((select_art-4)>=0){top=select_art-4;}else{top=0;}
    if (top+10<max_art){bottom=max_art;}
    bottom=top+9;
    if(bottom>max_art)
    {
      while (bottom!=max_art) {bottom--;top--;}
    }
    }
    else
    {
      top=0;
      bottom=max_art;
    }
    int bkcolor=23;
    if (max_art!=0)
    {
    for (int i=top;i<bottom;i++)
    {
        int colour=GetKatalogfontcolour();
        if (i==select_art)
      {
        bkcolor=GetKatalogbackgroundcolour();
      }
      else
      {
        bkcolor=23;
      }
        utf8_2ws(a,artists[i].c,320);
        wsprintf(a,pt,artists[i].c);
        if (Get_WS_width(a,7)<Get_WS_width(b,7))
        {
          DrawString(b,2,(i-top)*15+22,1000,(i-top+1)*15+18,7,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(bkcolor));
        }
        else
        {
          DrawString(a,2,(i-top)*15+22,1000,(i-top+1)*15+18,7,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(bkcolor));
        }
    }
    }
    wsprintf(a,"%i%c%i",select_art+1,'/',max_art);
    DrawString(a,1,3,128,176,7,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23)); 
    wsprintf(a,pt,LG_ARTISTS);
    DrawString(a,1,3,90,15,FONT_SMALL_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23));
    //wsprintf(wss.ws1,pt,LG_REMOVE);
    //DrawString(wss.ws1,1,163,130,176,7,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
    //wsprintf(wss.ws1,pt,LG_ADD);
    //DrawString(wss.ws1,1,163,130,176,7,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
    DrawLine(0,17,132,17,0,GetPaletteAdrByColorIndex(GetKatalogfontcolour()));
    DrawLine(92,17,92,0,0,GetPaletteAdrByColorIndex(GetKatalogfontcolour()));
  }break;
  case 2:
    {
    int bottom,top;
    if (max_alb>9)
    {
    if((select_alb-4)>=0){top=select_alb-4;}else{top=0;}
    if (top+10<max_alb){bottom=max_alb;}
    bottom=top+9;
    if(bottom>max_alb)
    {
      while (bottom!=max_alb) {bottom--;top--;}
    }
    }
    else
    {
      top=0;
      bottom=max_alb;
    }
    int bkcolor=23;
    if (max_alb!=0)
    {
    for (int i=top;i<bottom;i++)
    {
        int colour=GetKatalogfontcolour();
        utf8_2ws(a,albums[i].c,320);
        wsprintf(b,pt,albums[i].c);
        if (i==select_alb)
      {
        bkcolor=GetKatalogbackgroundcolour();
      }
      else
      {
        bkcolor=23;
      }
        if (Get_WS_width(a,7)<Get_WS_width(b,7))
        {
          DrawString(b,2,(i-top)*15+22,1000,(i-top+1)*15+18,7,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(bkcolor));
        }
        else
        {
          DrawString(a,2,(i-top)*15+22,1000,(i-top+1)*15+18,7,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(bkcolor));
        }
    }
    }
    wsprintf(a,"%i%c%i",select_alb+1,'/',max_alb);
    DrawString(a,1,3,128,176,7,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23)); 
    wsprintf(a,pt,artists[select_art].c);
    DrawString(a,1,3,90,15,FONT_SMALL_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23));
    //wsprintf(wss.ws1,pt,LG_REMOVE);
    //DrawString(wss.ws1,1,163,130,176,7,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
    //wsprintf(wss.ws1,pt,LG_ADD);
    //DrawString(wss.ws1,1,163,130,176,7,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
    DrawLine(0,17,132,17,0,GetPaletteAdrByColorIndex(GetKatalogfontcolour()));
    DrawLine(92,17,92,0,0,GetPaletteAdrByColorIndex(GetKatalogfontcolour()));
  }break;
  case 3:
    {
    int bottom,top;
    if (max_tra>9)
    {
    if((select_tra-4)>=0){top=select_tra-4;}else{top=0;}
    if (top+10<max_tra){bottom=max_tra;}
    bottom=top+9;
    if(bottom>max_tra)
    {
      while (bottom!=max_tra) {bottom--;top--;}
    }
    }
    else
    {
      top=0;
      bottom=max_tra;
    }
    int bkcolor=23;
    if (max_tra!=0)
    {
    for (int i=top;i<bottom;i++)
    {
        int colour=GetKatalogfontcolour();
        utf8_2ws(a,tracks[i].c,320);
        wsprintf(b,pt,tracks[i].c);
        if (i==select_tra)
      {
        bkcolor=GetKatalogbackgroundcolour();
      }
      else
      {
        bkcolor=23;
      }
        if (Get_WS_width(a,7)<Get_WS_width(b,7))
        {
          DrawString(b,2,(i-top)*15+22,1000,(i-top+1)*15+18,7,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(bkcolor));
        }
        else
        {
          DrawString(a,2,(i-top)*15+22,1000,(i-top+1)*15+18,7,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(bkcolor));
        }
    }
    }
    wsprintf(a,"%i%c%i",select_tra+1,'/',max_tra);
    DrawString(a,1,3,128,176,7,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23)); 
    wsprintf(a,pt,albums[select_alb].c);
    DrawString(a,1,3,90,15,FONT_SMALL_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23));
    //wsprintf(wss.ws1,pt,LG_REMOVE);
    //DrawString(wss.ws1,1,163,130,176,7,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
    //wsprintf(wss.ws1,pt,LG_ADD);
    //DrawString(wss.ws1,1,163,130,176,7,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
    DrawLine(0,17,132,17,0,GetPaletteAdrByColorIndex(GetKatalogfontcolour()));
    DrawLine(92,17,92,0,0,GetPaletteAdrByColorIndex(GetKatalogfontcolour()));
  }break;
  }
  FreeWS(a);
  FreeWS(b);
}
int MenuKeys3(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RED_BUTTON:case RIGHT_SOFT:
      {
        ToView--;
        if (!ToView) return(1);
        REDRAW();
      }break;
    case UP_BUTTON:case'2':
      {
        switch(ToView)
        {
        case 1:
          {
            select_art--;
            if (select_art==-1)
            {
              select_art=max_art-1;
            }
          }break;
        case 2:
          {
            select_alb--;
            if (select_alb==-1)
            {
              select_alb=max_alb-1;
            }
          }break;
        case 3:
          {
            select_tra--;
            if (select_tra==-1)
            {
              select_tra=max_tra-1;
            }
          }break;
        }
        REDRAW();
      }break;
    case DOWN_BUTTON:case'8':
      {
        switch(ToView)
        {
        case 1:
          {
            select_art++;
            if (select_art==max_art)
            {
              select_art=0;
            }
          }break;
        case 2:
          {
            select_alb++;
            if (select_alb==max_alb)
            {
              select_alb=0;
            }
          }break;
        case 3:
          {
            select_tra++;
            if (select_tra==max_tra)
            {
              select_tra=0;
            }
          }break;
        }
        REDRAW();
      }break;
    case ENTER_BUTTON:case'5':
      if (ToView==1)
      {
        curent=0;
        char album[30];
        for (int i=artists[select_art].i+2;i<artists[select_art+1].i;i++)
        {
          sprintf(album,pp);
          while ((masyv[i]!=0x0D)&&(i<artists[select_art+1].i))
          {
            sprintf(album,"%s%c",album,masyv[i]);
            i++;
          }
        
          if (strcmp(albums[curent-1].c,album))
          {
            sprintf(albums[curent].c,album);
            albums[curent].i=i;
            curent++;
          }
          for (int j=0;j<3;j++)
          {
            i++;
            while ((masyv[i]!=0x0D)&&(i<artists[select_art+1].i))
            {
              i++;
            }
          }
          i++;
        }
        max_alb=curent;
        albums[max_alb].i=artists[select_art+1].i;
        select_alb=0;
        ToView++;
        REDRAW();
      }
      else
        if (ToView==2)
      {
        curent=0;
        char track[30];
        for (int i=albums[select_alb].i+2;i<albums[select_alb+1].i;i++)
        {
          sprintf(track,pp);
          while ((masyv[i]!=0x0D)&&(i<albums[select_alb+1].i))
          {
            sprintf(track,"%s%c",track,masyv[i]);
            i++;
          }
        
          //if (strcmp(tracks[curent-1].c,track))
          {
            sprintf(tracks[curent].c,track);
            tracks[curent].i=i;
            curent++;
          }
          
          for (int j=0;j<3;j++)
          {
            i++;
            while ((masyv[i]!=0x0D)&&(i<albums[select_alb+1].i))
            {
              i++;
            }
          }
          i++;
        }
        max_tra=curent;
        tracks[max_tra].i=albums[select_alb+1].i;
        select_tra=0;
        ToView++;
        REDRAW();
      }
      else
        if (ToView==3)
        {
          char shliah[256];
          int i=tracks[select_tra].i+2;
          int f;
          unsigned int err;
          char way[256];
          sprintf(way,"%smedia.ipl",playerfolder);
          if ((f=fopen(way, A_WriteOnly+A_Create, P_WRITE, & err ))!=-1)
          {          
            sprintf(shliah,"%c%c%c\r\n",max_tra,1,select_tra);
            fwrite(f,shliah,5,&err);
            for (i=0;i<max_tra;i++)
            {
              int j=tracks[i].i+2;
              sprintf(shliah,pp);
              while ((masyv[j]!=0x0D)&&(j<tracks[i+1].i))
              {
                sprintf(shliah,"%s%c",shliah,masyv[j]);
                j++;
              }
              char s[256]="";
              char *y=strrchr(shliah,'\\')+1;
              strncpy(s,shliah,y-shliah);
              s[y-shliah]='\0';
              sprintf(y,"%s\r\n",y);
              fwrite(f,s,strlen(s),&err);
              fwrite(f,"*",1,&err);
              fwrite(f,y,strlen(y),&err);
            }
            sprintf(shliah,"%sivoplay.elf",playerfolder);
            main(shliah,way);
            /*CLOSECURENTCSM();
            WSHDR* w=AllocWS(128);
            wsprintf(w,"%sivoplay.elf",playerfolder);
            ExecuteFile(w,0,way);
            FreeWS(w);*/
          }
          else
          {
            Message(LG_CANT_CREATE_FILE);
          }
          fclose(f,&err);
          
          CloseMAINMENU();
          GeneralFunc_flag1 (GUI2,1);
          
        }
      break;
    }
  }
  return(0);
}
const void * const gui_methods4[11]={
  (void *)OnRedraw4,	//Redraw
  (void *)onCreate2,	//Create
  (void *)onClose2,	//Close
  (void *)onFocus2,	//Focus
  (void *)onUnfocus2,	//Unfocus
  (void *)MenuKeys3,	//OnKey
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

int ViewFiles()
{
  ToView=1;
  int f;
  char artist[30];
  unsigned int err;
  char name[320];
  sprintf(name,"%smediafiiles.txt",playerfolder);
  f=fopen(name, A_ReadOnly, P_READ, & err );
  if (f!=-1)
  {
  DIR_ENTRY de;
  FindFirstFile(&de,name,&err);
  fread(f,masyv,de.file_size,&err);
  sprintf(artist,pp);
  for (int i=0;i<de.file_size;i++)
  {
    sprintf(artist,"");
    while ((masyv[i]!=0x0D)&&(i<de.file_size))
    {
      sprintf(artist,"%s%c",artist,masyv[i]);
      i++;
    }
    if (strcmp(artists[curent-1].c,artist))
    {
      sprintf(artists[curent].c,artist);
      artists[curent].i=i;
      curent++;
    }
    for (int j=0;j<3;j++)
    {
      i++;
      while ((masyv[i]!=0x0D)&&(i<de.file_size))
      {
        i++;
      }
    }
    i++;
  }
  max_art=curent;
  artists[max_art].i=de.file_size;
  FindClose(&de,&err);
  }
  fclose(f,&err);
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas3);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods4;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  GUI2=CreateGUI(main_gui);
  return(0);
}
