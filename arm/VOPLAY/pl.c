#include "../inc/swilib.h"
#include "lang.h"
#include "main.h"
#include "mainmenu.h"
#include "conf_loader.h"
#include "mediafiles_base.h"
#include "libr.h"

extern long timelength[256];
extern const char playerfolder[128];

const RECT Canvas_pl={0,0,239,319};
int GUI_pl;

extern IMGHDR *fonn;
void OnRedraw_pl(MAIN_GUI *data) // OnRedraw
{
  WSHDR* a=AllocWS(128);
  WSHDR* b=AllocWS(128);
#ifndef VOVKA
    DrwImg(fonn,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));  
#else
    DrawRectangle(0,0,240,320,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
#endif  
  //DrawImg(0,0,(int)GetFon());
  switch(ToView)
  {
  case 1:
  {
    int font=GetKatalogFont();
    int otstup=GetKatalogXotstup();
    numit=(ScreenH()-23-(GetFontYSIZE(font)+4))/GetFontYSIZE(font)-1;
    polit=numit/2;
    int bottom,top;
    if (max_art>numit)
    {
    if((select_art-polit)>=0){top=select_art-polit;}else{top=0;}
    if (top+numit+1<max_art){bottom=max_art;}
    bottom=top+numit+1;
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
        wsprintf(b,pt,artists[i].c);
        if(i==top) {yyy1=24;yyy2=24+GetFontYSIZE(font);}else {yyy1=24+(i-top)*(GetFontYSIZE(font)); yyy2=24+(i-top+1)*(GetFontYSIZE(font));}
#ifdef ELKA
        if (Get_WS_width(a,font)<Get_WS_width(b,font))
        {
          DrawString(b,otstup,yyy1,1000,yyy2,font,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(bkcolor));
        }
       else
        {
          DrawString(a,otstup,yyy1,1000,yyy2,font,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(bkcolor));
        }
#else
        if (Get_WS_width(a,font)<Get_WS_width(b,font))
        {
          DrawString(b,otstup,yyy1,1000,yyy2,FONT_SMALL,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(bkcolor));
        }
        else
        {
          DrawString(a,2,yyy1,1000,yyy2,FONT_SMALL,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(bkcolor));
        }
#endif        
    }
    }
    wsprintf(a,"%i%c%i",select_art+1,'/',max_art);
    DrawString(a,1,5,ScreenW()-10,ScreenH(),FONT_SMALL,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23)); 
    wsprintf(a,pt,LG_ARTISTS);
    DrawString(a,1,5,162,27,FONT_SMALL_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23));
    //wsprintf(wss.ws1,pt,LG_REMOVE);
    //DrawString(wss.ws1,1,163,130,176,FONT_SMALL,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
    //wsprintf(wss.ws1,pt,LG_ADD);
    //DrawString(wss.ws1,1,163,130,176,FONT_SMALL,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
    //DrawLine(0,23,240,23,0,GetPaletteAdrByColorIndex(GetKatalogfontcolour()));
    //DrawLine(180,23,180,0,0,GetPaletteAdrByColorIndex(GetKatalogfontcolour()));  
  }break;
  case 2:
    {
    int font=GetKatalogFont();
    int otstup=GetKatalogXotstup();
    numit=(ScreenH()-23-(GetFontYSIZE(font)+4))/GetFontYSIZE(font)-1;
    polit=numit/2;
    int bottom,top;
    if (max_alb>numit)
    {
    if((select_alb-polit)>=0){top=select_alb-polit;}else{top=0;}
    if (top+numit+1<max_alb){bottom=max_alb;}
    bottom=top+numit+1;
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
        if(i==top) {yyy1=24;yyy2=24+GetFontYSIZE(font);}else {yyy1=24+(i-top)*(GetFontYSIZE(font)); yyy2=24+(i-top+1)*(GetFontYSIZE(font));}
        if (Get_WS_width(a,font)<Get_WS_width(b,font))
        {
          DrawString(b,otstup,yyy1,1000,yyy2,font,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(bkcolor));
        }
        else
        {
          DrawString(a,otstup,yyy1,1000,yyy2,font,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(bkcolor));
        }
    }
    }
    wsprintf(a,"%i%c%i",select_alb+1,'/',max_alb);
    DrawString(a,1,5,ScreenW()-10,ScreenH(),FONT_SMALL,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23)); 
    wsprintf(a,pt,artists[select_art].c);
    DrawString(a,1,5,162,27,FONT_SMALL_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23));
  }break;
  case 3:
    {
    int font=GetKatalogFont();
    int otstup=GetKatalogXotstup();
    numit=(ScreenH()-23-(GetFontYSIZE(font)+4))/GetFontYSIZE(font)-1;
    polit=numit/2;  
    int bottom,top;
    if (max_tra>numit)
    {
    if((select_tra-polit)>=0){top=select_tra-polit;}else{top=0;}
    if (top+numit+1<max_tra){bottom=max_tra;}
    bottom=top+numit+1;
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
      if(i==top) {yyy1=24;yyy2=24+GetFontYSIZE(font);}else {yyy1=24+(i-top)*(GetFontYSIZE(font)); yyy2=24+(i-top+1)*(GetFontYSIZE(font));}
        if (Get_WS_width(a,font)<Get_WS_width(b,font))
        {
          DrawString(b,otstup,yyy1,1000,yyy2,font,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(bkcolor));
        }
        else
        {
          DrawString(a,otstup,yyy1,1000,yyy2,font,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(bkcolor));
        }
    }
    }
    wsprintf(a,"%i%c%i",select_tra+1,'/',max_tra);
    DrawString(a,1,5,ScreenW()-10,ScreenH(),FONT_SMALL,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23)); 
    wsprintf(a,pt,albums[select_alb].c);
    DrawString(a,1,5,162,27,FONT_SMALL_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23));
  }break;
  }
  if(view_flag==0){
  wsprintf(a,"%t","Пересоздать");  
  DrawString(a,5+xlsh,ScreenH()-GetFontYSIZE(FONT_SMALL_BOLD)-2+ylsh,234,320,FONT_SMALL_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23));
  wsprintf(a,"%t","Назад");
  DrawString(a,1,ScreenH()-GetFontYSIZE(FONT_SMALL_BOLD)-2+yrsh,234-xrsh,320,FONT_SMALL_BOLD,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23));
  //DrawLine(0,320-GetFontYSIZE(FONT_SMALL_BOLD)-4,240,320-GetFontYSIZE(FONT_SMALL_BOLD)-4,0,GetPaletteAdrByColorIndex(0));
  }
  else
  { DrawRectangle(0,0,ScreenW(),ScreenH(),0,color3,color3);
    DrawRectangle(18,18,ScreenW()-24,ScreenH()-20,0,GetPaletteAdrByColorIndex(1),color4);
    wsprintf(a,"%t","Пересоздать базу?");  
    DrawString(a,21,94,ScreenW()-24,ScreenH()-25,FONT_MEDIUM,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(1),color4);
    wsprintf(a,"%t","Да");  
  DrawString(a,5+xlsh,ScreenH()-GetFontYSIZE(FONT_SMALL_BOLD)-2+ylsh,234,320,FONT_SMALL_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23));
  wsprintf(a,"%t","Нет");
  DrawString(a,1,ScreenH()-GetFontYSIZE(FONT_SMALL_BOLD)-2+yrsh,234-xrsh,320,FONT_SMALL_BOLD,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(GetKatalogfontcolour()),GetPaletteAdrByColorIndex(23));
  //DrawLine(0,320-GetFontYSIZE(FONT_SMALL_BOLD)-4,240,320-GetFontYSIZE(FONT_SMALL_BOLD)-4,0,GetPaletteAdrByColorIndex(0));
  }
  FreeWS(a);
  FreeWS(b);
}

int MenuKeys_pl(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    switch(msg->gbsmsg->submess)
    {
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
    }
  }
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {  
    case RIGHT_SOFT:
      {
        xrsh=2;
        yrsh=2; 
        REDRAW();
      }break;
    case LEFT_SOFT:
      {
        xlsh=2;
        ylsh=2; 
        REDRAW();
      }break; 
    }
  }
  if (msg->gbsmsg->msg==KEY_UP)
  {
    switch(msg->gbsmsg->submess)
    {
    case RED_BUTTON:case RIGHT_SOFT:
      {
        xrsh=0;
        yrsh=0; 
        if(view_flag==0)
        {
        ToView--;
        if ((select_art==0)&&(ToView))
        {
          ToView--;
        }
        if (!ToView) {GeneralFunc_flag1 (GUI_GUI,1);return(1);}
        REDRAW();
        }
        else {reload=0;view_flag=0;REDRAW();}
      }break;
    case LEFT_SOFT:
      {
        xlsh=0;
        ylsh=0; 
        if(view_flag==1){view_flag=0;GeneralFunc_flag1 (GUI2,1); reload=1; CreateBaseOfMediafiles(); REDRAW();}
        else view_flag=1;
        REDRAW();
      }
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
      }
      break;
    case ENTER_BUTTON:case'5':
      if (ToView==1)
      {
        if (select_art==0)
        {
          curent=0;
          char track[30];
          int i=0;
          while ((masyv[i]!=0x0D)&&(i<artists[max_art].i)){i++;}
          i++;
          while ((masyv[i]!=0x0D)&&(i<artists[max_art].i)){i++;}
          for (i=i+2;i<artists[max_art].i;i++)
          {
            sprintf(track,pp);
            while ((masyv[i]!=0x0D)&&(i<artists[max_art].i))
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
              while ((masyv[i]!=0x0D)&&(i<artists[max_art].i))
              {
                i++;
              }
            }
            i++;
          }
          max_tra=curent;
          tracks[max_tra].i=artists[max_art].i;
          select_tra=0;
          ToView=3;
          REDRAW();
        }
        else
        {
          curent=1;
          char album[30];
          sprintf(albums[0].c,"<BCE>");
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
          albums[0].i=artists[select_art].i;
          select_alb=0;
          ToView++;
          REDRAW();
        }
      }
      else
        if (ToView==2)
        {
          {
          curent=0;
          char track[30];
          int h=albums[select_alb+1].i;
          if (select_alb==0)
          {
            h=albums[max_alb].i;
            albums[0].i++;
            while ((masyv[albums[0].i]!=0x0D)&&(albums[0].i<h))
            {
              albums[0].i++;
            }
          }
          for (int i=albums[select_alb].i+2;i<h;i++)
          {
            sprintf(track,pp);
            while ((masyv[i]!=0x0D)&&(i<h))
            {
              sprintf(track,"%s%c",track,masyv[i]);
              i++;
            }
              sprintf(tracks[curent].c,track);
              tracks[curent].i=i;
              curent++;
            for (int j=0;j<3;j++)
            {
              i++;
              while ((masyv[i]!=0x0D)&&(i<h))
              {
                i++;
              }
            }
            i++;
          }
          max_tra=curent;
          tracks[max_tra].i=h;
          select_tra=0;
          ToView++;
          REDRAW();
          }
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
          if ((f=fopen(way, A_ReadWrite+A_Create,P_READ+P_WRITE, & err ))!=-1)
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
                sprintf(s,"%s*%s",s,y);
                s[strlen(s)-2]='\0';
                timelength[j]=-1;
                sprintf(s,"%s%c%d%c%c",s,0x2F,timelength[j],0x0D,0x0A);
                fwrite(f,s,strlen(s),&err);
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
extern void kill_data(void *p, void (*func_p)(void *));
const void * const gui_methods_pl[11]={
  (void *)OnRedraw_pl,	//Redraw
  (void *)onCreate2,	//Create
  (void *)onClose2,	//Close
  (void *)onFocus2,	//Focus
  (void *)onUnfocus2,	//Unfocus
  (void *)MenuKeys_pl,	//OnKey
  0,
  (void *)kill_data,	//Destroy
  (void *)method,
  (void *)method,
  0
};

int ViewPL()
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas_pl);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods_pl;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  GUI_pl=CreateGUI(main_gui);
  return(0);
}
