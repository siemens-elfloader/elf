#include "C:\ARM\inc\swilib.h"
#include "externs.h"
#include "language.h"

typedef struct
{
  GUI gui;
}GAMEMENU_GUI;

unsigned int GAMEMENU_ID = 0;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
  char doscreen;
}GAMEMENU_CSM;

extern void kill_data(void *p, void (*func_p)(void *));

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

void ShowRecMSG(char *msg)
{
   DrawRectangle(0, 0, ScreenW() ,ScreenH(),0,
		   black40,
		   black40);
  
   WSHDR *ws_shw_rec_msg = AllocWS(128);
   wsprintf(ws_shw_rec_msg,perc_t, msg );
   DrawString(ws_shw_rec_msg,0, 20 ,scr_w, scr_h, FONT, 2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
   wsprintf(ws_shw_rec_msg,perc_t, "Закрыть" );
   DrawString(ws_shw_rec_msg,0, 165 ,scr_w, scr_h, FONT, 4,GetPaletteAdrByColorIndex(22),GetPaletteAdrByColorIndex(23));
   FreeWS(ws_shw_rec_msg);  
}

void TimeGame()
{
  if (++theme_tick>1)
  {
    theme_tick=0;
    theme_time++;
    game_time_m_sec++;
    if(game_time_m_sec==60)game_time_m_sec=0;
    DirectRedrawGUI();
  }
  GBS_StartTimerProc(&timer, 216, TimeGame);
}


void DrawWhoIsXod()
{
   WSHDR *ws_who = AllocWS(128);
   switch(MODE_GAME)
   {
   case 1:  
    if(!end_game)
          {
              wsprintf(ws_who,perc_t,"Ваш ход");
           }
     else
     if(!end_game) 
             wsprintf(ws_who,perc_t,"Ход соперника");
   break;
   case 2:
   if(ena_two_g==1)
   {
         if(!end_game)
         {
            switch(MODE_FIGURE)
            {
                  case 1: wsprintf(ws_who,perc_t,"Ход первого игрока (Х)"); break;
                  case 2: wsprintf(ws_who,perc_t,"Ход первого игрока (O)"); break;
            }
         }
   }
   else
   if(ena_two_g==2)
   {
         if(!end_game)
         {     
            switch(MODE_FIGURE)
            {
                  case 1: wsprintf(ws_who,perc_t,"Ход второго игрока (O)"); break;
                  case 2: wsprintf(ws_who,perc_t,"Ход второго игрока (X)"); break;
            }
         }
   }  
   break;

//case 1: 
     case 3:
     if(Online2xod==1)
     {
          if(!end_game)
          {
              wsprintf(ws_who,perc_t,"Ваш ход");
           }
     }
     else
     if(!end_game) 
             wsprintf(ws_who,perc_t,"Ход соперника");
      
break;
   }
   
   DrawString(ws_who,2, 45 ,ScreenW(),ScreenH(),FONT,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));  
   
   FreeWS(ws_who);
}


void EndGame()
{
  WSHDR *ws_end = AllocWS(128);
  //if(MODE_GAME==2 || MODE_GAME==3)
  //{
    if( DrawXoid+count==30 || DrawXoid+DrawOoid==30 || DrawXoid+OnlainGameXod==30)
    {
      nich=end_game=1;
      GBS_StopTimer(&timer);  //Остановить таймер времени игры
      //count_gamer_num_1=count_gamer_num_2=0;
      wsprintf(ws_end,perc_t,"Игра закончена! Ничья!");
    }
 // }
  DrawString(ws_end,2,45 ,ScreenW(),ScreenW(),FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  
FreeWS(ws_end);

}

extern int speed_count;
extern char speed[64];
void DrawCount()
{
WSHDR *ws_info = AllocWS(128);

switch(MODE_GAME)
{
case 1: wsprintf(ws_info,mda_perc_tdtdtd,"Ходов: ",DrawXoid+count, " Счет: ",count_gamer_num_1,":", count_gamer_num_2); break ;
case 2: wsprintf(ws_info,mda_perc_tdtdtd,"Ходов: ",DrawXoid+DrawOoid, "; Счет: ",count_gamer_num_1,":", count_gamer_num_2); break;
case 3:case 4: wsprintf(ws_info,mda_perc_tdtdtd,"Ходов: ",DrawXoid+OnlainGameXod, " Счет: ",count_gamer_num_1,":", count_gamer_num_2);
}
DrawString(ws_info,2, 5 ,ScreenW(),ScreenW(),FONT,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

wsprintf(ws_info,"%t%d%t%d%t%t","Время: ",theme_time/60, ":", game_time_m_sec,"соединение: ",speed);
DrawString(ws_info,2, 15 ,ScreenW(),ScreenW(),FONT,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));


FreeWS(ws_info);
}

int DrawLevel()
{
#ifdef ELKA
  DrwImg(images[5], 10,125);
#else
  DrwImg(images[5], 5,70);
#endif
  DrawCount();
  EndGame();
    return 0;
}



static void DrawFonCyr()
{
    int y=35 + 15*POZ_GMC;
    DrawRectangle(0, 0, ScreenW() ,ScreenH(),0,
		   black40,
		   black40);
    
    DrawRectangle(21, 48, 111 ,128,0,
		   grey0,
		   black0);
       
    DrawRoundedFrame( 23, y , 109 ,y+15,0,0,0,grey0,grey0);
}

//Redraw
static void OnRedraw(GAMEMENU_GUI *data)
{
  
  //main_gui->doscreen=1;
  
  if (data->gui.state==2)
  {
    
    DrwImg(images[6], 0,0);
    
    if(NewGame)
    {

   #ifdef ELKA
   int X_G_C=36*x_n_poz -24;
   int Y_G_C=91+ 36*y_n_poz;
#else
      int X_G_C=20*x_n_poz -15;
   int Y_G_C=50+ 20*y_n_poz;
#endif
   DrawLevel();
   DrawWhoIsXod();
   OXod(1);
   OXod(2);
   if(isDrawFring)
   {
    DoFring();
   }
   DrwImg(images[2], X_G_C, Y_G_C);
     }
    
    if(DrawGameMenu)
    {
    
       WSHDR *ws_g_menu = AllocWS(128);
       DrawFonCyr();
       
       if(nich==1 || end_game==1)
       wsprintf(ws_g_menu,perc_t,"Сыграть ещё"); 
       else wsprintf(ws_g_menu,perc_t,"Продолжить"); 
       
       DrawString(ws_g_menu,0, 50 ,ScreenW(),ScreenH(),FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

       wsprintf(ws_g_menu,perc_t,"Переиграть"); 
       DrawString(ws_g_menu,0, 65 ,ScreenW(),ScreenH(),FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
       
       if(IsOnLineGame) wsprintf(ws_g_menu,perc_t,"Отключиться"); else
       wsprintf(ws_g_menu,perc_t,"Закончить игру");
       DrawString(ws_g_menu,0, 80 ,ScreenW(),ScreenH(),FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
       
       if(IsOnLineGame) {wsprintf(ws_g_menu,perc_t,"Сообщение"); 
       DrawString(ws_g_menu,0, 95 ,ScreenW(),ScreenH(),FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));}
       
       FreeWS(ws_g_menu);

   }

 }
}




 //Create
static void OnCreate(GAMEMENU_GUI *data,void *(*malloc_adr)(int))
{
       	#ifdef ELKA
	DisableIconBar(1);
	#endif
       data->gui.state=1;
}

//Close
void OnClose(GAMEMENU_GUI *data,void (*mfree_adr)(void *))
{
	data->gui.state=0;
}

//Focus
static void OnFocus(GAMEMENU_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
	#ifdef ELKA
	DisableIconBar(1);
	#endif
	DisableIDLETMR();
	data->gui.state=2;
}

//Unfocus
static void OnUnfocus(GAMEMENU_GUI *data,void (*mfree_adr)(void *))
{
	#ifdef ELKA
	DisableIconBar(0);
	#endif
        if (data->gui.state!=2) return;
        data->gui.state=1;
}


void AntiXod()
{
  if((TableXod[x_n_poz][y_n_poz]==1)||(TableXod[x_n_poz][y_n_poz]==2))
  {
     WSHDR *ws_anti = AllocWS(128);
     wsprintf(ws_anti,perc_t,"Не верно!");
     DrawString(ws_anti,0,20,scr_w, scr_h, FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
     FreeWS(ws_anti);
           
  }
  else
  {
    switch(MODE_GAME)
    {
       case 1:  
                DrawXoid++;
                DoXod();
                
                if(end_game==0 || nich==0)KompXod();
        break;
        case 2:
        if(ena_two_g==1)
        {
                  DoXod();
                  DrawXoid++;
                  DoFring();
                  ena_two_g=2;
        }
        else
        if(ena_two_g==2)
        {
                  DoInvertXod();
                  DrawOoid++;
                  DoFring();
                  ena_two_g=1;
        } break;
        
    case 3:case 4:
        if(Online2xod==1)
        {
                 Online1xod=1;
                 DrawXoid++;
                 WRITE_STEP(1);
                 SendXod(x_n_poz, y_n_poz);
                 Online2xod=0;
                 DoFring();
       } break;
  }
 }
}



 //OnKey
static int OnKey(GAMEMENU_GUI *data, GUI_MSG *msg)
{
if(Quit_Game_Giu)return 1;  
int sh=msg->gbsmsg->msg;
switch(sh)
 {
  case KEY_DOWN:
   switch(msg->gbsmsg->submess)
     {
      case RIGHT_SOFT:  if(DrawGameMenu) DrawGameMenu=0; else DrawGameMenu=1;  break;
      case LEFT_SOFT:   if(DrawGameMenu) DrawGameMenu=0; else DrawGameMenu=1;  break;
      case UP_BUTTON: case '2': 
      if(NewGame)
      {
               if(DrawGameMenu)
               { 
                 if(POZ_GMC==1){if(IsOnLineGame)POZ_GMC=4;else POZ_GMC=3;}else POZ_GMC--;
               }
               else
               {
                        if(y_n_poz==1)y_n_poz=5;else y_n_poz--;
               }
      }
      break;
      case DOWN_BUTTON: case '8': 
      if(NewGame==1)
      {
               if(DrawGameMenu)
               { int max=4;
                 if(IsOnLineGame)max=4;else max=3;
                 if(POZ_GMC==max)POZ_GMC=1;else POZ_GMC++;
               }
               else
               {
                        if(y_n_poz==5)y_n_poz=1;else y_n_poz++;
               }
      }
      break;
      case RIGHT_BUTTON:
      case '6':
      if(NewGame)
      {
               if(!DrawGameMenu)
               { 
                       if(x_n_poz    == 6)   x_n_poz=1;    else x_n_poz++;
               }
      }
      break;
      case LEFT_BUTTON:
      case '4':
      if(NewGame==1)
      {
              if(!DrawGameMenu)
              { 
                      if(x_n_poz    == 1) x_n_poz=6;      else x_n_poz--;
              }
      } 
      break;
      case ENTER_BUTTON: case '5':
       if(NewGame==1)
       {
           
          if(DrawGameMenu)
          {
               
          switch(POZ_GMC)
          {
          case 1: ResumeGame(); break;
          case 2: QuestResGame(); break;
          case 3: CloseGame();   break;
          case 4: if(IsOnLineGame)
          {
            DrawGameMenu=0; 
            WriteMsg();
          }
          break;
            
          }
        }
        else
        if(!end_game)AntiXod();
       }
       break;
      case '3':
	if(NewGame)
        {
              if(!DrawGameMenu)
              { 
                      
                      if(y_n_poz == 1) y_n_poz=5; else y_n_poz--;
                      if(x_n_poz == 6) x_n_poz=1; else x_n_poz++;
              }
        }
        break;
     case '9':
       if(NewGame)
        {
              if(!DrawGameMenu)
              { 
                      
                      if(y_n_poz==5)y_n_poz=1;else y_n_poz++;
                      if(x_n_poz == 6) x_n_poz=1; else x_n_poz++;
              }
        }
       break;
     case '1':
       if(NewGame)
        {
              if(!DrawGameMenu)
              { 
                      
                      if(y_n_poz==1)y_n_poz=5;else y_n_poz--;
                      if(x_n_poz    == 1) x_n_poz=6;      else x_n_poz--;
              }
        }
       break;
     case '7':
        if(NewGame)
        {
              if(!DrawGameMenu)
              { 
                      
                      if(y_n_poz==5)y_n_poz=1;else y_n_poz++;
                     if(x_n_poz    == 1) x_n_poz=6;      else x_n_poz--;
              }
        }
       
	
	break;
  }
  DirectRedrawGUI();
  
 }
return 0;
}

// фигня какая-то
static const void * const GAMEMENU_GUI_methods[11]={
  (void *)OnRedraw,
  (void *)OnCreate,
  (void *)OnClose,
  (void *)OnFocus,
  (void *)OnUnfocus,
  (void *)OnKey,
  0,
  (void *)kill_data, //Destroy
  (void *)0,
  (void *)0,
  0
};

void GAME_MENU_GUI()
{
  static const RECT Canvas={0,0,0,0};
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  StoreXYXYtoRECT((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  GAMEMENU_GUI *main_gui=malloc(sizeof(GAMEMENU_GUI));
  zeromem(main_gui,sizeof(GAMEMENU_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.methods=(void *)GAMEMENU_GUI_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  CreateGUI(main_gui);
      
}
