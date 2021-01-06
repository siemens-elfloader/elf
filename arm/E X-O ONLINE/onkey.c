#include "c:\arm\inc\swilib.h"
#include "language.h"
#include "writemsg.h"
#include "externs.h"
#include "onkey.h"


void ENTER_GREEN_BUTTON()
{
  if(IsConnectProcess)
   {
      disautorecconect=0;
      if ((connect_state==0)&&(sock==-1))
      {
          GBS_DelTimer(&reconnect_tmr);
	  DNR_TRIES=3;
          SUBPROC((void *)create_connect);
      }
   }

}

extern GBSTMR tmr_vibra;
void CLOSE_CONNECT_PROCESS()
{
     MODE_GAME=1;
     IsConnectProcess=0; 
     IsOnLineGame=0;
    /* GBS_DelTimer(&tmr_active);
     GBS_DelTimer(&reconnect_tmr);
     GBS_DelTimer(&timer);
     GBS_DelTimer(&load_img);
     GBS_DelTimer(&tmr_vibra);*/
     FreeCLIST();
     SUBPROC((void *)end_socket);
     SUBPROC((void *)ClearSendQ);
}

void EndSetFigure()
{
  SetFigure=0;
  POZ_MENU_CUR++;
  y_s_n_g+=20;
}

void ENTER_LEFT_SOFT()
{
  if(IsConnectProcess)
  { 
     CLOSE_CONNECT_PROCESS();
  }
  else
  { 
     IsMenu=1;
     if(eDrawInfo)eDrawInfo=0;
     if(NewGame) draw_logo=0; else draw_logo=1;
  }
}

void ENTER_0()
{
  if(IsConnectProcess)
   {
      SUBPROC((void*)end_socket);
      GBS_DelTimer(&reconnect_tmr);
      DNR_TRIES=3;
      SUBPROC((void *)create_connect);
    }
}



void ENTER_RIGHT_SOFT()
{
   if(!IsConnectProcess) //Если не процесс соединения
   { 
      if(exit_ungraf==1)
      {
          CloseCSM(MAINCSM_ID);
      }
      else
      
      if(eDrawInfo==1)    // Если показана информация
      {
         IsMenu=1;
         eDrawInfo=0;     // Убрать показ
         draw_logo=1;     // Показать логотип
     }
     
   }
}


void ENTER_LEFT_BUTTON_OR_4()
{
  if(!IsConnectProcess) // Если не процесс соединения
   { 
      if(IsMenu)
      {
        if(POZ_MENU_CUR==2) // Если курсор на выборе режима игры
        {
          if(MODE_GAME==1)MODE_GAME=4;else MODE_GAME--;
        }
         if(SetFigure)
        {
          if(MODE_FIGURE==1)MODE_FIGURE=2;else MODE_FIGURE--;
          if(m_x==66)m_x=15;else m_x+=51;
        }
      }
  
   }
}


void ENTER_RIGHT_BUTTON_OR_6()
{
    if(!IsConnectProcess)
   { 
      if(IsMenu)
      {
        if(POZ_MENU_CUR==2) 
        {
         if(MODE_GAME==4)MODE_GAME=1;else MODE_GAME++;
        }
        if(SetFigure)
        {
          if(MODE_FIGURE==2)MODE_FIGURE=1;else MODE_FIGURE++;
          if(m_x==15)m_x=66;else m_x-=51;
        }
      }
     
   }
}


void ENTER_DOWN_BUTTON_OR_8()
{
    if(!IsConnectProcess)
    { 
      if(!SetFigure)
      {
        if(!eDrawInfo)
        {
          if(POZ_MENU_CUR==5)POZ_MENU_CUR=1;else POZ_MENU_CUR++;
        }
      }
      if(SetFigure)
      {
            EndSetFigure();
      }
      
     
   }
}

void ENTER_UP_BUTTON_OR_2()
{
    if(!IsConnectProcess)
   { 
     
      if(!SetFigure)
      {
         if(!eDrawInfo)
        {
           if(POZ_MENU_CUR==1)POZ_MENU_CUR=5;else POZ_MENU_CUR--;
        }
      }
      if(SetFigure)
      {
            EndSetFigure();
      }
      
     
   }
}

void OpenSetting()
{
  extern const char *successed_config_filename;
  WSHDR *ws;
  ws=AllocWS(128);
  str_2ws(ws,successed_config_filename,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
}

void NGame()
{
  isDrawFring=0;
  OnlainGameXod=0;
  isDrawFring=0;
  end_game=0, nich=0;
  summ_count1=summ_count2=1;
  ena_two_g=1;
  NullGame();             // Обнулить значение игры
  theme_tick=theme_time=game_time_m_sec=DrawXoid=count=DrawOoid=OnlainGameXod=0; //Обнулить значения
  x_n_poz=3 , y_n_poz=5;  // Вернуть в начальное положение курсор игры
  DrawGameMenu=0;         // Закрыть меню игры
  if(end_game==0 || nich==0)GBS_StartTimerProc(&timer, 216/2, TimeGame); // Запускаем время игры
}
void ResumeMSgame()
{
  if( nich==1 || end_game==1 )
  {
        DrawGameMenu=0;   
        NGame();
  }
  else DrawGameMenu=0;  
 
  
}
void AnswerIsOnline()
{
  if( nich==1 || end_game==1 )
    {
     SendQuest("NG",2);
    }
    else DrawGameMenu=0;  
}
void ResumeGame()
{
  if(IsOnLineGame)//Если сейчас онлайн-игра
  {
     AnswerIsOnline();
  }
  else
  {
    ResumeMSgame();
  }
  
}

void CloseGame()
{
     if(IsOnLineGame) 
     {
           SendQuest("e_y_g",NULL);
           DrawGameMenu=0;
           end_game=1;
           CLOSE_CONNECT_PROCESS();
     }
     else
     {
  //DrawGameMenu=0;     
  isDrawFring=0; 
  Quit_Game_Giu=1;
  OnlainGameXod=0;  
  isDrawFring=0;
  summ_count1=summ_count2=1;
  end_game=0, nich=0;
  count_gamer_num_1=0,
  count_gamer_num_2=0;
  draw_logo=1;       // Показать логотип
  NullGame();        // Обнулить значение игры
  NewGame=0;         // Выйти из игры
  IsMenu=1;          // Показать меню
  DirectRedrawGUI();
  GBS_SendMessage(MMI_CEPID,KEY_DOWN,RIGHT_BUTTON);

  
  }

}

extern void RestoreGame();

void AnswerNewGame(int decision)
{
   if(decision)
   {
     SendQuest("Y_ng",NULL);
     NGame();
   }
   if(!decision)
   {
      SendQuest("N_ng",NULL);
   }
}


void AnswerExitGame(int decision)
{
   if(decision)
   {
    //DrawGameMenu=0;   
    CLOSE_CONNECT_PROCESS();
    Quit_Game_Giu=1;
    CloseGame();
   }
   if(!decision)
   {
      //SendQuest("N_rg",NULL);
   }
}
void AnswerResGame(int decision)
{
     if(decision)
     {
            SendQuest("Y_rg",NULL);
            RestoreGame();
     }
     if(!decision)
     {
            SendQuest("N_rg",NULL);
     }
}
void QuestResGame()
{
     if(IsOnLineGame)//Если сейчас онлайн-игра
     {
       
           SendQuest("RG",1);
           //DrawGameMenu=0;  
     }
     else
     {
     //DrawGameMenu=0;  
     RestoreGame();
     }
}

void RestoreGame()
{
  DrawGameMenu=0;   
  isDrawFring=0;
  ena_two_g=1;
  OnlainGameXod=0;
  isDrawFring=0;
  end_game=0, nich=0;
  summ_count1=summ_count2=1;
  count_gamer_num_1=0,
  count_gamer_num_2=0;
  NullGame();             // Обнулить значение игры
  theme_tick=theme_time=game_time_m_sec=DrawXoid=count=DrawOoid=0; //Обнулить значения
  x_n_poz=3 , y_n_poz=5;  // Вернуть в начальное положение курсор игры
  if(end_game==0 || nich==0)GBS_StartTimerProc(&timer, 216/2, TimeGame); // Запускаем время игры
}
#define  server 1
#define client 2
extern int mode;


void ENTER_ENTER_BUTTON_OR_5()
{
    if(!IsConnectProcess)
    { 
      if(IsMenu)
      {
          if(SetFigure)
                        {
                          EndSetFigure();
                          
                          GAME_MENU_GUI();
                          InitParametres();  
                        }
          else
          {
         if(!eDrawInfo)
        {
            
        switch(POZ_MENU_CUR)
        {
        case 1:  if(MODE_GAME>2) 
                 { 
                   if(IsOnLineGame==1) {IsOnLineGame=0;CLOSE_CONNECT_PROCESS();}
                        else 
                        {
                          if (!UIN)
                          {
                               extern const char *successed_config_filename;
                               WSHDR *ws;
                               ShowMSG(1,(int)LG_MSGNOUINPASS);
                               ws=AllocWS(150);
                               str_2ws(ws,successed_config_filename,128);
                               ExecuteFile(ws,0,0);
                               FreeWS(ws);
                          }
                          else
                          {
                            if(MODE_GAME==3)mode=server;
                            if(MODE_GAME==4)mode=client;
                               IsConnectProcess=1;
                               ENTER_GREEN_BUTTON();
                               SMART_REDRAW();
                          }
                        }
                        
                 } else
                      { 
                        if(!SetFigure)
                        {
                          SetFigure=1;
                          POZ_MENU_CUR--;
                          y_s_n_g-=20;
                          
                        }
                    
                      }
                   break;
        case 3:  OpenSetting(); break;
        case 4:  eDrawInfo=1;   break;
        case 5:  CloseCSM(MAINCSM_ID); break;
        }
      }
          }
      }
   }
}


 
   
