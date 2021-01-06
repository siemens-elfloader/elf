#include "menu.h"
#include "engine.h"
#include "config.h"
//отстой,а не меню.Нет времени переделывать..


extern signed char state;
extern char cont;
extern char offset1;
extern short score;
extern char levelcounter;


int sellcpx; //позиции курсора в меню выбора уровня
int sellcpy;


#define MENU_PX_STARTPOS 45
#define MENU_PY_STARTPOS 100
#define MENU_P_WIDTH 150
#define MENU_PY_OUTL 4

int menu_px=MENU_PX_STARTPOS,menu_py=MENU_PY_STARTPOS;
WSHDR *mmws;
char *mmenu_items[]= {"","","","","",""};

RECT sell={30,50,190,200};
int sellcx=30-2; //-погрешность из-за кривого шрифта
int sellcy=50+2; //+погрешность из-за кривого шрифта
int sellwsW;



char sets_cur = 0;



#define FONT_SDVIG_X 5
#define FONT_SDVIG_Y 4
//int mcur_ypos=1;
int cur_pos;
//int cur_down;
//int cur_up;


//////////////////////////////////////////////
int list_counter;
int list_ypos;
int list_drawcount;
char list_lineheight;
char list_drawoffset;
#define Getcurpos() (list_counter+list_ypos)
//////////////////////////////////////////////

#define UTF16_FONT_SMALL (0xE012)
#define UTF16_FONT_SMALL_BOLD (0xE013)

void Krakozyabra_2ws(WSHDR *name,char *krakozyabra)
{
  str_2ws(name,krakozyabra,strlen(krakozyabra));
        int wi=1;
        int c;
        while(wi<=name->wsbody[0])	
        {
          c=name->wsbody[wi];
          if (c==0xA8) c=0x401;
          if (c==0xAA) c=0x404;
          if (c==0xAF) c=0x407;
          if (c==0xB8) c=0x451;
          if (c==0xBA) c=0x454;
          if (c==0xBF) c=0x457;
          if ((c>=0xC0)&&(c<0x100)) c+=0x350;
          name->wsbody[wi++]=c;
        }
}




void DrawMenu()
{
  char menu_pointer_pen[4]={50,50,50,100}; //для курсора
  char menu_pointer_brush[4]={90,90,90,90}; //для курсора
  char menu_text_brush[4]={25,120,5,100}; //цвет текста в меню
  char selcolor[4]={5,5,5,100}; //цвет текста выделенного пункта в меню и выборе левела
  
  //фон
  char bg_color[4]={0,0,0,100};
  DrawRoundedFrame(0,0,sw,sh,2,2,0,NULL,bg_color);
  
  switch(state)
  {
    case STATE_MENU: //in main menu
      {
        int sdvig_y = MENU_PY_STARTPOS;
        short line_h = GetFontYSIZE(FONT_MD)-FONT_SDVIG_Y;
        if(cont) mmenu_items[0]="продолжить";
        else mmenu_items[0]="новая игра";
        char *cl;
        //курсор
        DrawRoundedFrame(2,MENU_PY_STARTPOS+(line_h*cur_pos),sw-2,MENU_PY_STARTPOS+(line_h*cur_pos)+line_h,3,3,0,menu_pointer_pen,menu_pointer_brush);
            
        for(int i=0;i<6;i++) //в цикеле рисуем имена итемов меню
        {
          if(i==cur_pos) cl = selcolor;
          else cl = menu_text_brush;
          wsprintf(mmws,perc_t,mmenu_items[i]);
          DrawString(mmws,0,sdvig_y-FONT_SDVIG_Y,sw,sh,FONT_MD,TEXT_ALIGNMIDDLE,cl,NULL);
          sdvig_y+=GetFontYSIZE(FONT_MD)-FONT_SDVIG_Y; 
        }
        break;
      }
     case STATE_ABOUT: //about
      {
        int text_y=75;
        int text_x=10;
        wsprintf(mmws,"%s","ArcanoidStudio\nfor SieELFPlatform\n version 1.3 Freeware\n(c)half65\nICQ - 404558107");
        DrawString(mmws,text_x,text_y,W,H,FONT_LG,TEXT_ALIGNMIDDLE,menu_text_brush,NULL);
        wsprintf(mmws,"%s","back");
        DrawString(mmws,ScreenW()-Get_WS_width(mmws,FONT_MD)-6,ScreenH()-GetFontYSIZE(FONT_MD)-6,ScreenW(),ScreenH(),FONT_MD,TEXT_ALIGNMIDDLE,menu_text_brush,NULL);
        break;
      }
    case STATE_SETTINGS: //settings
      {
        int offset3 = offset1+1;
        short sdvig = GetFontYSIZE(FONT_SM)+6;
        char *cl = menu_text_brush;
        
        DrawRoundedFrame(1,offset3+(sets_cur*sdvig)-1,ScreenW()-1,offset3+(sets_cur*sdvig)+GetFontYSIZE(FONT_SM)+3,0,0,0,menu_pointer_brush,menu_pointer_pen); //курсор
        
        if(savedata.difficulty==DIFF_EASY) {wsprintf(mmws,perc_t,"сложность: легко");}
        if(savedata.difficulty==DIFF_NORMAL) {wsprintf(mmws,perc_t,"сложность: норма");}
        if(savedata.difficulty==DIFF_HARD) {wsprintf(mmws,perc_t,"сложность: оченнно сложно");}
        DrawString(mmws,1,offset3+(sdvig*0),W-1,offset3+(sdvig*0)+GetFontYSIZE(FONT_SM)+3,FONT_SM,TEXT_ALIGNMIDDLE,cl,NULL);
        
        if(savedata.recs_autosave==1) {wsprintf(mmws,perc_t,"автосохранение рекордов: вкл");}
        if(savedata.recs_autosave==0) {wsprintf(mmws,perc_t,"автосохранение рекордов: выкл");}
        DrawString(mmws,1,offset3+(sdvig*1),W-1,offset3+(sdvig*1)+GetFontYSIZE(FONT_SM)+3,FONT_SM,TEXT_ALIGNMIDDLE,cl,NULL);
        
        if(savedata.SoundsEnable==1) {wsprintf(mmws,perc_t,"музыка:включено");}
        if(savedata.SoundsEnable==0) {wsprintf(mmws,perc_t,"музыка:выключено");}
        DrawString(mmws,1,offset3+(sdvig*2),W-1,offset3+(sdvig*2)+GetFontYSIZE(FONT_SM)+3,FONT_SM,TEXT_ALIGNMIDDLE,cl,NULL);
        
        if(savedata.VibraEnable==1) {wsprintf(mmws,perc_t,"вибра:включено");}
        if(savedata.VibraEnable==0) {wsprintf(mmws,perc_t,"вибра:выключено");}
        DrawString(mmws,1,offset3+(sdvig*3),W-1,offset3+(sdvig*3)+GetFontYSIZE(FONT_SM)+3,FONT_SM,TEXT_ALIGNMIDDLE,cl,NULL);
        
        wsprintf(mmws,"%t: %d","громкость музыки",savedata.SndVolume);
        DrawString(mmws,1,offset3+(sdvig*4),W-1,offset3+(sdvig*4)+GetFontYSIZE(FONT_SM)+3,FONT_SM,TEXT_ALIGNMIDDLE,cl,NULL);
        
        wsprintf(mmws,"%t: %d","сила вибрации",savedata.VibraVolume);
        DrawString(mmws,1,offset3+(sdvig*5),W-1,offset3+(sdvig*5)+GetFontYSIZE(FONT_SM)+3,FONT_SM,TEXT_ALIGNMIDDLE,cl,NULL);
        
        wsprintf(mmws,"%t: %d","задержка вибрации",savedata.VibraCount);
        DrawString(mmws,1,offset3+(sdvig*6),W-1,offset3+(sdvig*6)+GetFontYSIZE(FONT_SM)+3,FONT_SM,TEXT_ALIGNMIDDLE,cl,NULL);
        
        if(savedata.SndEnable==1) {wsprintf(mmws,perc_t,"звуки:включено");}
        if(savedata.SndEnable==0) {wsprintf(mmws,perc_t,"звуки:выключено");}
        DrawString(mmws,1,offset3+(sdvig*7),W-1,offset3+(sdvig*7)+GetFontYSIZE(FONT_SM)+3,FONT_SM,TEXT_ALIGNMIDDLE,cl,NULL);
        
#ifdef STD_SND
        wsprintf(mmws,"%t: %d","номер звука ball+user",savedata.StdSnd_user);
        DrawString(mmws,1,offset3+(sdvig*8),W-1,offset3+(sdvig*8)+GetFontYSIZE(FONT_SM)+3,FONT_SM,TEXT_ALIGNMIDDLE,cl,NULL);
        
        wsprintf(mmws,"%t: %d","номер звука ball+brick",savedata.StdSnd_brick);
        DrawString(mmws,1,offset3+(sdvig*9),W-1,offset3+(sdvig*9)+GetFontYSIZE(FONT_SM)+3,FONT_SM,TEXT_ALIGNMIDDLE,cl,NULL);
#endif
        
        wsprintf(mmws,"%t: %d","задержка перерисовки",savedata.tmr_speed);
        DrawString(mmws,1,offset3+(sdvig*10),W-1,offset3+(sdvig*10)+GetFontYSIZE(FONT_SM)+3,FONT_SM,TEXT_ALIGNMIDDLE,cl,NULL);
        
        //wsprintf(mmws,"%s","back");
        //DrawString(mmws,ScreenW()-Get_WS_width(mmws,FONT_MD)-6,ScreenH()-GetFontYSIZE(FONT_MD)-6,ScreenW(),ScreenH(),FONT_MD,TEXT_ALIGNMIDDLE,cl,NULL);
        break;
      }
    case STATE_SLEVEL: //select level
      {
        char *cl2;
        char un_color[4]={15,80,5,60};
        //DrawRoundedFrame(0,0,ScreenW()-1,ScreenH()-1,0,0,0,menu_pointer_pen,menu_pointer_brush);
        list_drawoffset = offset1+1; //чуть ниже иконбара
        list_lineheight = GetFontYSIZE(FONT_LG)+2;
        char max_strings=(sh-1-list_drawoffset)/list_lineheight;
        if(total_levels>max_strings) list_drawcount=max_strings-1; //максимум 10 строк рисуем
        else list_drawcount=total_levels; //если строк меньше чем 10,то рисуем все
        
        for(int i=0;i<list_drawcount;i++)
        {
          wsprintf(mmws,"%t %d","уровень",i+list_counter+1); 
          
          if(i+list_counter<savedata.opened_levels) cl2 = menu_text_brush;
          else cl2 = un_color;
          
          if(list_ypos==i) //под курсором
          {
            //cl2 = selcolor;
            DrawRoundedFrame(1,list_drawoffset+(list_lineheight*list_ypos)+3,sw-2,list_drawoffset+(list_lineheight*list_ypos)+list_lineheight+2,3,3,0,menu_pointer_pen,menu_pointer_brush);
          }
          //else cl2 = menu_text_brush;
          
          DrawString(mmws,2,list_drawoffset+(list_lineheight*i)+2,sw-2,list_drawoffset+(list_lineheight*i)+list_lineheight+2,FONT_LG,TEXT_ALIGNMIDDLE,cl2,NULL);
        }
         break;
      }
      case STATE_RECORDS: //records
      {
        int lh = GetFontYSIZE(FONT_MD);
        //int offset = 40;
        for(int i=0;i<MAX_RECORDS;i++)
        {
          wsprintf(mmws,perc_t,savedata.recs[i].name);
          DrawString(mmws,1,offset1+3+(lh*i)+2,sw-1,offset1+3+(lh*i)+lh+2,FONT_MD,TEXT_ALIGNMIDDLE,menu_text_brush,NULL);
        }
        //wsprintf(mmws,"%s","back");
        //DrawString(mmws,sw-Get_WS_width(mmws,FONT_MD)-6,sh-GetFontYSIZE(FONT_MD)-6,sw,sh,FONT_MD,TEXT_ALIGNMIDDLE,menu_text_brush,NULL);
        break;
      }
  }
}





int list_counter;
int list_ypos;
int list_drawcount;
char list_lineheight;
char list_drawoffset;
#define Getcurpos() (list_counter+list_ypos)


void ListDown() //вниз по списку
{
   if(Getcurpos()>=total_levels-1) {list_counter=0;list_ypos=0;} //возвращаемся на начало списка
   else
   {
     if(list_drawoffset+(list_lineheight*list_ypos)<ScreenH()/2) {list_ypos++;} //если курсор еще не дошел до середины экрана
     else if(list_counter<total_levels-list_drawcount) {list_counter++;} //если дошел,то курсор далее двигаться не должен,а список должен двигаться вверх
     else if(list_drawoffset+(list_lineheight*list_ypos)+list_lineheight<list_drawoffset+(list_lineheight*list_drawcount)) {list_ypos++;} //зато он должен двигаться до конца списка,пока не дойдет до последнего элемента
   }
}
void ListUp() //вверх по списку
{
   if((list_lineheight*list_ypos)>(ScreenH()/3)) list_ypos--; //если курсор еще не дошел до середины экрана
   else if(list_counter>0) {list_counter--;}
   else if(list_drawoffset+(list_lineheight*list_ypos)+list_lineheight>list_drawoffset+list_lineheight) {list_ypos--;}
   else if(Getcurpos()<=0) {list_counter=total_levels-list_drawcount;list_ypos=list_drawcount-1;} //если дошли до верха,спускаемся на самый конец списка
}















int MenuNavigation(GUI_MSG *msg)
{
  if(msg->gbsmsg->msg==KEY_DOWN)
  {
    if(state==STATE_MENU)
    {
      if((msg->gbsmsg->submess==DOWN_BUTTON || msg->gbsmsg->submess=='8') && cur_pos<6-1) {cur_pos++;TimerRedrawScreen();return 0;}
      if((msg->gbsmsg->submess==UP_BUTTON || msg->gbsmsg->submess=='2') && cur_pos>0) {cur_pos--;TimerRedrawScreen();return 0;}
      
      if((msg->gbsmsg->submess==ENTER_BUTTON || msg->gbsmsg->submess=='5' || msg->gbsmsg->submess==RIGHT_BUTTON) && cur_pos==5) {return 1;} //exit
      if((msg->gbsmsg->submess==ENTER_BUTTON || msg->gbsmsg->submess=='5' || msg->gbsmsg->submess==RIGHT_BUTTON) && cur_pos==3) {state=STATE_RECORDS;TimerRedrawScreen();return 0;} //records
      if((msg->gbsmsg->submess==ENTER_BUTTON || msg->gbsmsg->submess=='5' || msg->gbsmsg->submess==RIGHT_BUTTON) && cur_pos==4) {state=STATE_ABOUT;TimerRedrawScreen();return 0;} //about
      if((msg->gbsmsg->submess==ENTER_BUTTON || msg->gbsmsg->submess=='5' || msg->gbsmsg->submess==RIGHT_BUTTON) && cur_pos==2) {state=STATE_SETTINGS;TimerRedrawScreen();return 0;} //settings
      if((msg->gbsmsg->submess==ENTER_BUTTON || msg->gbsmsg->submess=='5' || msg->gbsmsg->submess==RIGHT_BUTTON) && cur_pos==1) {state=STATE_SLEVEL;TimerRedrawScreen();return 0;} //select level
      if((msg->gbsmsg->submess==ENTER_BUTTON || msg->gbsmsg->submess=='5' || msg->gbsmsg->submess==RIGHT_BUTTON) && cur_pos==0)
      {
         
         state=STATE_GAME; //continue game
         if(cont==0) {score=0;SetDefaultGameParameters();PrepareLevel(1);} //новая игра
         else 
         {
           levelcounter=1;
           PlayMusic(GAME_MUSIC);
           GBS_StartTimerProc(&gametimer,25,TimerRedrawScreen); //тупо продолжаем
         }
         return 0;
      }
    } //in main menu
    
    if(state==STATE_ABOUT) //если в about
    {
      if(msg->gbsmsg->submess==ENTER_BUTTON)
      {
        //LCD_DrawImage(press0,100,100);
        //LCD_Redraw();
        //sprintf(lgn,"%spics\\items\\boom.png",pwd);
        //IMGHDR **tt = LoadSprites(lgn,4,1);
        //for(int i=0;i<4;i++) DrwImg(tt[i],20+(i*tt[i]->w+5),50);
        
        return 0;
      }
     if(msg->gbsmsg->submess==RIGHT_SOFT)
     {
       state=STATE_MENU; //переходим назад в меню
       TimerRedrawScreen();
       return 0;
     }
    }
    
    if(state==STATE_RECORDS) //если в records
    {
     if(msg->gbsmsg->submess==RIGHT_SOFT)
     {
       state=STATE_MENU; //переходим назад в меню
       TimerRedrawScreen();
       return 0;
     }
     if(msg->gbsmsg->submess=='#')
     {
       zeromem(savedata.recs,sizeof(RECORDS)*MAX_RECORDS);
       ShowMSG(1,(int)"рекорды сброшены");
       TimerRedrawScreen();
       return 0;
     }
    }
    
    
    if(state==STATE_SETTINGS) //если в settings
    {
     if(msg->gbsmsg->submess==RIGHT_SOFT)
     {
       state=STATE_MENU; //переходим назад в меню
       TimerRedrawScreen();
       return 0;
     }
#ifndef STD_SND
     if((msg->gbsmsg->submess==DOWN_BUTTON || msg->gbsmsg->submess=='8') && sets_cur<7) {sets_cur++;TimerRedrawScreen();return 0;}
#else
     if((msg->gbsmsg->submess==DOWN_BUTTON || msg->gbsmsg->submess=='8') && sets_cur<10) {sets_cur++;TimerRedrawScreen();return 0;}
#endif
     if((msg->gbsmsg->submess==UP_BUTTON   || msg->gbsmsg->submess=='2') && sets_cur>0) {sets_cur--;TimerRedrawScreen();return 0;}
     
     if(msg->gbsmsg->submess==RIGHT_BUTTON && sets_cur==0 && savedata.difficulty<2) {savedata.difficulty++;TimerRedrawScreen();return 0;}
     if(msg->gbsmsg->submess==LEFT_BUTTON  && sets_cur==0 && savedata.difficulty>0) {savedata.difficulty--;TimerRedrawScreen();return 0;}
     
     if(msg->gbsmsg->submess==RIGHT_BUTTON && sets_cur==1 && savedata.recs_autosave==0) {savedata.recs_autosave=1;TimerRedrawScreen();return 0;}
     if(msg->gbsmsg->submess==LEFT_BUTTON && sets_cur==1 && savedata.recs_autosave==1) {savedata.recs_autosave=0;TimerRedrawScreen();return 0;}
     
     if(msg->gbsmsg->submess==RIGHT_BUTTON && sets_cur==2 && savedata.SoundsEnable==0) {savedata.SoundsEnable=1;PlayMusic(MENU_MUSIC);TimerRedrawScreen();return 0;}
     if(msg->gbsmsg->submess==LEFT_BUTTON && sets_cur==2 && savedata.SoundsEnable==1) {savedata.SoundsEnable=0;PlayMelody_StopPlayback(PLAY_ID);TimerRedrawScreen();return 0;}
     
     if(msg->gbsmsg->submess==RIGHT_BUTTON && sets_cur==3 && savedata.VibraEnable==0) {savedata.VibraEnable=1;StartVibra(savedata.VibraVolume,100);TimerRedrawScreen();return 0;}
     if(msg->gbsmsg->submess==LEFT_BUTTON && sets_cur==3 && savedata.VibraEnable==1) {savedata.VibraEnable=0;TimerRedrawScreen();return 0;}
     
     if(msg->gbsmsg->submess==RIGHT_BUTTON && sets_cur==4 && savedata.SndVolume<15) {savedata.SndVolume++;PlayMelody_ChangeVolume(PLAY_ID,savedata.SndVolume);TimerRedrawScreen();return 0;}
     if(msg->gbsmsg->submess==LEFT_BUTTON && sets_cur==4 && savedata.SndVolume>0) {savedata.SndVolume--;PlayMelody_ChangeVolume(PLAY_ID,savedata.SndVolume);TimerRedrawScreen();return 0;}
     
     if(msg->gbsmsg->submess==RIGHT_BUTTON && sets_cur==5 && savedata.VibraVolume<100) {savedata.VibraVolume+=10;StartVibra(savedata.VibraVolume,50);TimerRedrawScreen();return 0;}
     if(msg->gbsmsg->submess==LEFT_BUTTON && sets_cur==5 && savedata.VibraVolume>10) {savedata.VibraVolume-=10;StartVibra(savedata.VibraVolume,50);TimerRedrawScreen();return 0;}
     
     if(msg->gbsmsg->submess==RIGHT_BUTTON && sets_cur==6 && savedata.VibraCount<100) {savedata.VibraCount+=5;StartVibra(savedata.VibraVolume,savedata.VibraCount);TimerRedrawScreen();return 0;}
     if(msg->gbsmsg->submess==LEFT_BUTTON && sets_cur==6 && savedata.VibraCount>10) {savedata.VibraCount-=5;StartVibra(savedata.VibraVolume,savedata.VibraCount);TimerRedrawScreen();return 0;}
     
     if(msg->gbsmsg->submess==RIGHT_BUTTON && sets_cur==7 && savedata.SndEnable==0) {savedata.SndEnable=1;PlaySound(1,0,0,5,0);TimerRedrawScreen();return 0;}
     if(msg->gbsmsg->submess==LEFT_BUTTON && sets_cur==7 && savedata.SndEnable==1) {savedata.SndEnable=0;PlaySound(1,0,0,5,0);TimerRedrawScreen();return 0;}
#ifdef STD_SND
     if(msg->gbsmsg->submess==RIGHT_BUTTON && sets_cur==8 && savedata.StdSnd_user<500) {savedata.StdSnd_user++;PlaySound(1,0,0,savedata.StdSnd_user,0);TimerRedrawScreen();return 0;}
     if(msg->gbsmsg->submess==LEFT_BUTTON && sets_cur==8 && savedata.StdSnd_user>0) {savedata.StdSnd_user--;PlaySound(1,0,0,savedata.StdSnd_user,0);TimerRedrawScreen();return 0;}
     
     if(msg->gbsmsg->submess==RIGHT_BUTTON && sets_cur==9 && savedata.StdSnd_brick<500) {savedata.StdSnd_brick++;PlaySound(1,0,0,savedata.StdSnd_brick,0);TimerRedrawScreen();return 0;}
     if(msg->gbsmsg->submess==LEFT_BUTTON && sets_cur==9 && savedata.StdSnd_brick>0) {savedata.StdSnd_brick--;PlaySound(1,0,0,savedata.StdSnd_brick,0);TimerRedrawScreen();return 0;}
#endif
     
     if(msg->gbsmsg->submess==RIGHT_BUTTON && sets_cur==10 && savedata.tmr_speed<50) {savedata.tmr_speed++;TimerRedrawScreen();return 0;}
     if(msg->gbsmsg->submess==LEFT_BUTTON && sets_cur==10 && savedata.tmr_speed>2) {savedata.tmr_speed--;TimerRedrawScreen();return 0;}
     
    }
    
    if(state==STATE_SLEVEL) //select level
    {
     if(msg->gbsmsg->submess=='2' || msg->gbsmsg->submess==UP_BUTTON)
     {
       ListUp();
       TimerRedrawScreen();return 0;
       //return 0;
     }
     if(msg->gbsmsg->submess=='8' || msg->gbsmsg->submess==DOWN_BUTTON)
     {
       ListDown();
       TimerRedrawScreen();return 0;
       //return 0;
     }
     if(msg->gbsmsg->submess==ENTER_BUTTON || msg->gbsmsg->submess=='5') 
     {
         levelcounter = Getcurpos()+1; //высчитываем по позиции курсора номер левела
         if(levelcounter<=savedata.opened_levels)
         {
           score=0;
           SetDefaultGameParameters();
           state=STATE_GAME; //старт игры
           PrepareLevel(levelcounter);
         }
         else {levelcounter=0;ShowMSG(1,(int)"уровень еще не открыт");}
         TimerRedrawScreen();return 0;
       //return 0;
     }
     
     if(msg->gbsmsg->submess==RIGHT_SOFT)  {state=STATE_MENU;TimerRedrawScreen();return 0;} //переходим назад в меню
   }
   
   
   
 }
 
 
  return 0;
}




void InitMenu()
{
  mmws=AllocWS(128);
  mmenu_items[0]="новая игра";
  mmenu_items[1]="выбрать уровень";
  mmenu_items[2]="настройки";
  mmenu_items[3]="рекорды";
  mmenu_items[4]="об игре";
  mmenu_items[5]="выход";
}

void DeinitMenu()
{
  FreeWS(mmws);
}


