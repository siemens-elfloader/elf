#include "c:\arm\inc\swilib.h"
#include "externs.h"
#include "conf_loader.h"

/////////////////////////////////////////
//               E - XO 2.4
//             (c) Vedan

const int minus11=-11;

extern void kill_data(void *p, void (*func_p)(void *));

extern void DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush);

unsigned int MAINCSM_ID = 0;

unsigned int MAINGUI_ID = 0;

unsigned short maincsm_name_body[140];

extern volatile int total_img;

extern const char PIC_DIR[128];

extern IMGHDR *fon,
              *menu_cursor,
              *game_cursor,
              *logo,
              *draw_x,
              *draw_o,
              *table;





#ifdef NEWSGOLD
#define FONT 11
#define FONT_ATR 32
#else
#define FONT 7
#define FONT_ATR 32
#endif

const char perc_t[]="%t";
const char perc_tt[]="%t%t";
const char perc_td[]="%t%d";
const char perc_tdt[]="%t%d%t";
const char perc_tdtd[]="%t%d%t%d";
const char perc_tdtdt[]="%t%d%t%d%t";
char FON_COLOR[4]={0xa9,0xa5,0xa5,100},
     FON_M_CURSOR[4]={0xdc,0xd9,0xd9,100},
     FON_FRINF[4]={0xff,0,0,40};
GBSTMR timer;
GBSTMR load_img;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;
//1 - черный
//0 - белый
int cur_x=20, cur_y=320/4-2, game_cur_x=45,game_cur_y=150;
int count=0;  
int ena_msg=1, ena_msg_fal=1;
int DrawXoid=0,DrawOoid=0, IsConnectProcess=0;
int eDrawInfo=0;
//int one_gamer=1,two_gamer=0, on_line_game=0;
int MODE_GAME=1; //1 - Одиночная, 2 - Два игрока, 3 -Он-лайн игра
int ena_two_g=1, nich=0;
int x_n_poz=3 , y_n_poz=5;
int IsLoadGraph=1;
int img_count;

int TableXod[7] [8]=
{
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},   
   {0,0,0,0,0,0,0,0}
};

/*int TableXod_10x10[12] [14]=
{
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};*/

int theme_tick=0, theme_time=0, game_time_m_sec=0;





void DrawXorO(int flag,int x_p, int y_p)
{
  //int x=5; y=70;
  switch(flag)
  {
    case 1:// X
    {
     //DrwImg(draw_x, x+ 20*x_p, y+20*y_p, NULL,NULL);
      DrwImg(draw_x, x_p, y_p, NULL,NULL);
    }
    break;
   case 2: // O
   {
      DrwImg(draw_o, x_p,y_p, NULL,NULL);
   }
    break;
  }

}

int DrRF_R_D(int x,int y)
{
  for(int i=0;i<=3;i++)
  {
    DrawRoundedFrame(x-20*i, y+20*i, x-20*i+20, y+20*i + 20,0,0,0,GetPaletteAdrByColorIndex(1),FON_FRINF);

  }
     return 0;
}


int DrRF_R_U(int x,int y)
{
  for(int i=0;i<=3;i++)
  {
    DrawRoundedFrame(x+20*i, y+20*i, x+20*i+20, y+20*i + 20,0,0,0,GetPaletteAdrByColorIndex(1),FON_FRINF);

  }
     return 0;
}

int DrRF_DOWN(int x, int y)
{
  for(int i=0;i<=3;i++)
  {
    DrawRoundedFrame(x, y+20*i,x+20, y+20*i+20,0,0,0,GetPaletteAdrByColorIndex(1),FON_FRINF);

  }
     return 0;
}

int DrRF_LEFT(int x, int y)
{
  for(int i=0;i<=3;i++)
  {
    DrawRoundedFrame(x+20*i, y ,x+20*i+20, y+20,0,0,0,GetPaletteAdrByColorIndex(1),FON_FRINF);

  }
     return 0;
}


void FringFig(int flag)
{
 if(  TableXod[1][1]==flag && TableXod[1][2]==flag && TableXod[1][3]==flag && TableXod[1][4]==flag ) DrRF_DOWN(5,70); else
 if(  TableXod[1][2]==flag && TableXod[1][3]==flag && TableXod[1][4]==flag && TableXod[1][5]==flag ) DrRF_DOWN(5,90); else
   
 if(  TableXod[2][1]==flag && TableXod[2][2]==flag && TableXod[2][3]==flag && TableXod[2][4]==flag ) DrRF_DOWN(25,70); else
 if(  TableXod[2][2]==flag && TableXod[2][3]==flag && TableXod[2][4]==flag && TableXod[2][5]==flag ) DrRF_DOWN(25,90); else  
   
 if(  TableXod[3][1]==flag && TableXod[3][2]==flag && TableXod[3][3]==flag && TableXod[3][4]==flag ) DrRF_DOWN(45,70); else   
 if(  TableXod[3][2]==flag && TableXod[3][3]==flag && TableXod[3][4]==flag && TableXod[3][5]==flag ) DrRF_DOWN(45,90); else   
   
 if(  TableXod[4][1]==flag && TableXod[4][2]==flag && TableXod[4][3]==flag && TableXod[4][4]==flag ) DrRF_DOWN(65,70); else   
 if(  TableXod[4][2]==flag && TableXod[4][3]==flag && TableXod[4][4]==flag && TableXod[4][5]==flag ) DrRF_DOWN(65,90); else   
   
 if(  TableXod[5][1]==flag && TableXod[5][2]==flag && TableXod[5][3]==flag && TableXod[5][4]==flag ) DrRF_DOWN(85,70); else   
 if(  TableXod[5][2]==flag && TableXod[5][3]==flag && TableXod[5][4]==flag && TableXod[5][5]==flag ) DrRF_DOWN(85,90); else 
   
 if(  TableXod[6][1]==flag && TableXod[6][2]==flag && TableXod[6][3]==flag && TableXod[6][4]==flag ) DrRF_DOWN(105,70); else   
 if(  TableXod[6][2]==flag && TableXod[6][3]==flag && TableXod[6][4]==flag && TableXod[6][5]==flag ) DrRF_DOWN(105,90); else   
 //------------------------------------------------------------------------------   
 if(  TableXod[1][1]==flag && TableXod[2][1]==flag && TableXod[3][1]==flag && TableXod[4][1]==flag ) DrRF_LEFT(5,70); else
 if(  TableXod[2][1]==flag && TableXod[3][1]==flag && TableXod[4][1]==flag && TableXod[5][1]==flag ) DrRF_LEFT(25,70); else
 if(  TableXod[3][1]==flag && TableXod[4][1]==flag && TableXod[5][1]==flag && TableXod[6][1]==flag ) DrRF_LEFT(45,70); else
   
 if(  TableXod[1][2]==flag && TableXod[2][2]==flag && TableXod[3][2]==flag && TableXod[4][2]==flag ) DrRF_LEFT(5,90); else  
 if(  TableXod[2][2]==flag && TableXod[3][2]==flag && TableXod[4][2]==flag && TableXod[5][2]==flag ) DrRF_LEFT(25,90); else   
 if(  TableXod[3][2]==flag && TableXod[4][2]==flag && TableXod[5][2]==flag && TableXod[6][2]==flag ) DrRF_LEFT(45,90); else   
   
 if(  TableXod[1][3]==flag && TableXod[2][3]==flag && TableXod[3][3]==flag && TableXod[4][3]==flag ) DrRF_LEFT(5,110); else  
 if(  TableXod[2][3]==flag && TableXod[3][3]==flag && TableXod[4][3]==flag && TableXod[5][3]==flag ) DrRF_LEFT(25,110); else  
 if(  TableXod[3][3]==flag && TableXod[4][3]==flag && TableXod[5][3]==flag && TableXod[6][3]==flag ) DrRF_LEFT(45,110); else      
     
 if(  TableXod[1][4]==flag && TableXod[2][4]==flag && TableXod[3][4]==flag && TableXod[4][4]==flag ) DrRF_LEFT(5,130); else  
 if(  TableXod[2][4]==flag && TableXod[3][4]==flag && TableXod[4][4]==flag && TableXod[5][4]==flag ) DrRF_LEFT(25,130); else  
 if(  TableXod[3][4]==flag && TableXod[4][4]==flag && TableXod[5][4]==flag && TableXod[6][4]==flag ) DrRF_LEFT(45,130); else  
      
 if(  TableXod[1][5]==flag && TableXod[2][5]==flag && TableXod[3][5]==flag && TableXod[4][5]==flag ) DrRF_LEFT(5,150); else  
 if(  TableXod[2][5]==flag && TableXod[3][5]==flag && TableXod[4][5]==flag && TableXod[5][5]==flag ) DrRF_LEFT(25,150); else  
 if(  TableXod[3][5]==flag && TableXod[4][5]==flag && TableXod[5][5]==flag && TableXod[6][5]==flag ) DrRF_LEFT(45,150); else
 //------------------------------------------------------------------------------     
 if(  TableXod[1][2]==flag && TableXod[2][3]==flag && TableXod[3][4]==flag && TableXod[4][5]==flag ) DrRF_R_U(5,90); else
 if(  TableXod[1][1]==flag && TableXod[2][2]==flag && TableXod[3][3]==flag && TableXod[4][4]==flag ) DrRF_R_U(5,70); else
 if(  TableXod[2][2]==flag && TableXod[3][3]==flag && TableXod[4][4]==flag && TableXod[5][5]==flag ) DrRF_R_U(5,90); else
 if(  TableXod[2][1]==flag && TableXod[3][2]==flag && TableXod[4][3]==flag && TableXod[5][4]==flag ) DrRF_R_U(25,70); else
 if(  TableXod[3][2]==flag && TableXod[4][3]==flag && TableXod[5][4]==flag && TableXod[6][5]==flag ) DrRF_R_U(45,90); else
 if(  TableXod[3][1]==flag && TableXod[4][2]==flag && TableXod[5][3]==flag && TableXod[6][4]==flag ) DrRF_R_U(45,70); else
   
 if(  TableXod[6][2]==flag && TableXod[5][3]==flag && TableXod[4][4]==flag && TableXod[3][5]==flag ) DrRF_R_D(105,90); else   
 if(  TableXod[6][1]==flag && TableXod[5][2]==flag && TableXod[4][3]==flag && TableXod[3][4]==flag ) DrRF_R_D(105,70); else    
 if(  TableXod[5][2]==flag && TableXod[4][3]==flag && TableXod[3][4]==flag && TableXod[2][5]==flag ) DrRF_R_D(85,90); else    
 if(  TableXod[5][1]==flag && TableXod[4][2]==flag && TableXod[3][3]==flag && TableXod[2][4]==flag ) DrRF_R_D(85,70); else    
 if(  TableXod[4][2]==flag && TableXod[3][3]==flag && TableXod[2][4]==flag && TableXod[1][5]==flag ) DrRF_R_D(65,90); else       
 if(  TableXod[4][1]==flag && TableXod[3][2]==flag && TableXod[2][3]==flag && TableXod[1][4]==flag ) DrRF_R_D(65,70);      
   
}

    
      


//==============================================================================
int IsMenu=1, NewGame=0;


void DrawMainMenu(void)
{

//DrawRoundedFrame( cur_x, cur_y, cur_x+90,cur_y+15,0,0,0,GetPaletteAdrByColorIndex(1),FON_M_CURSOR);
DrwImg(menu_cursor, cur_x, cur_y, NULL,NULL);
WSHDR *ws_menu = AllocWS(128);

if(MODE_GAME==3) wsprintf(ws_menu,perc_t,"Соединиться");
            else wsprintf(ws_menu,perc_t,"Новая игра");

DrawString(ws_menu,0,320/4 ,240,240,FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

switch(MODE_GAME)
{
case 1: wsprintf(ws_menu,perc_t,"< Одиночная >");    break;
case 2: wsprintf(ws_menu,perc_t,"< Два игрока >");   break;
case 3: wsprintf(ws_menu,perc_t,"< Он-лайн игра >"); break;
}
DrawString(ws_menu,0,320/4+20 ,240,240,FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

wsprintf(ws_menu,perc_t,"О игре");
DrawString(ws_menu,0,320/4+40 ,240,240,FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

wsprintf(ws_menu,perc_t,"Выход");
DrawString(ws_menu,0,320/4+60 ,240,240,FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
FreeWS(ws_menu);
}



void TimeGame()
{
  if (++theme_tick>2)
  {
    theme_tick=0;
    theme_time++;
    game_time_m_sec++;
    if(game_time_m_sec==60)game_time_m_sec=0;
    DirectRedrawGUI();
  }
  GBS_StartTimerProc(&timer, 216/2, TimeGame);
}
extern void Load_IMG(int flag);

void T_Load_IMG()
{
  img_count++;
  Load_IMG(img_count);
  DirectRedrawGUI();
  if(img_count>8)
  {
    GBS_DelTimer(&load_img);
    IsLoadGraph=0;
  }
  
  GBS_StartTimerProc(&load_img, 216/6, T_Load_IMG);
}


void DrawCount()
{
WSHDR *ws_info = AllocWS(128);

if(MODE_GAME==2)
{
  wsprintf(ws_info,perc_td,"Ходов: ",DrawXoid+DrawOoid);
}
else
{
wsprintf(ws_info,perc_td,"Ходов: ",DrawXoid+count);
}
DrawString(ws_info,2, 5 ,240,240,FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
FreeWS(ws_info);
}


int DrawTime()
{
WSHDR *ws_time = AllocWS(64);

if(theme_time>60)
{
  wsprintf(ws_time,perc_tdtdt,"Время игры: ",theme_time/60," м ",game_time_m_sec," с");
}
else
{
 wsprintf(ws_time,perc_tdt,"Время игры: ",theme_time," с");
}
//DrawString(ws_time,2,15 ,240,240,FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
DrawString(ws_time,2, 15 ,240,240,FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
FreeWS(ws_time);
return 0;
}



int end_game=0;
void EndGame()
{
  WSHDR *ws_end = AllocWS(128);
  if(MODE_GAME==2)
  {
    if( DrawXoid+count==30 || DrawXoid+DrawOoid==30 )
    {
      GBS_StopTimer(&timer);
      end_game=1;
      wsprintf(ws_end,perc_t,"Игра закончена! Ничья!");
    }
  }
  DrawString(ws_end,2,45 ,240,240,FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  
FreeWS(ws_end);

}

int DrawLevel()
{
  DrwImg(table, 5,70, NULL,NULL);
  //DrawSetka();
  //DrawSetka10x10();
  //DrawGameCur();
  DrawCount();
  DrawTime();
  EndGame();
  
  return 0;
}




//1 - крестик
//2 - нолик

void DrawWhoIsXod()
{
   WSHDR *ws_who = AllocWS(128);
   if(ena_two_g==1)
   {
     if(!end_game)
     {
     wsprintf(ws_who,perc_t,"Ход первого игрока ( Х )");
     }
   }
   else
   if(ena_two_g==2)
   {
     if(!end_game)
     {     
     wsprintf(ws_who,perc_t,"Ход второго игрока ( О )");
     }
   }  
   DrawString(ws_who,2, 45 ,240,320,FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
   FreeWS(ws_who);
}

void DrawAbout()
{
   WSHDR *ws_about = AllocWS(128);
   DrwImg(fon, 0,0, NULL,NULL);
   
   //DrawRoundedFrame(0,0,131,175,0,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(0));
   
   wsprintf(ws_about,perc_t,"ELF X-O\nv 1.4\n(C) Vedan, 2008\nSITE: www.MobiGraph.ru\n\nРасширенные крестики-нолики.");
   DrawString(ws_about,0, 20 ,240,320,FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
   
   wsprintf(ws_about,perc_t,"OK");
   DrawString(ws_about,2, 165 ,240,320,FONT,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
   
   wsprintf(ws_about,perc_t,"Закрыть");
   DrawString(ws_about,0, 165 ,240,320,FONT,4,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
   
   FreeWS(ws_about);
   
}


void WRITE_xod(int flag, int x, int y) { if((x_n_poz==x)&&(y_n_poz==y)) TableXod[x][y]= flag; }


void Write_XOD(int flag)
{
  WRITE_xod(flag,1,1);WRITE_xod(flag,2,1);WRITE_xod(flag,3,1);WRITE_xod(flag,4,1);WRITE_xod(flag,5,1);WRITE_xod(flag,6,1);
  WRITE_xod(flag,1,2);WRITE_xod(flag,2,2);WRITE_xod(flag,3,2);WRITE_xod(flag,4,2);WRITE_xod(flag,5,2);WRITE_xod(flag,6,2);
  WRITE_xod(flag,1,3);WRITE_xod(flag,2,3);WRITE_xod(flag,3,3);WRITE_xod(flag,4,3);WRITE_xod(flag,5,3);WRITE_xod(flag,6,3);
  WRITE_xod(flag,1,4);WRITE_xod(flag,2,4);WRITE_xod(flag,3,4);WRITE_xod(flag,4,4);WRITE_xod(flag,5,4);WRITE_xod(flag,6,4);
  WRITE_xod(flag,1,5);WRITE_xod(flag,2,5);WRITE_xod(flag,3,5);WRITE_xod(flag,4,5);WRITE_xod(flag,5,5);WRITE_xod(flag,6,5);
  WRITE_xod(flag,1,6);WRITE_xod(flag,2,6);WRITE_xod(flag,3,6);WRITE_xod(flag,4,6);WRITE_xod(flag,5,6);WRITE_xod(flag,6,6);
  WRITE_xod(flag,1,7);WRITE_xod(flag,2,7);WRITE_xod(flag,3,7);WRITE_xod(flag,4,7);WRITE_xod(flag,5,7);WRITE_xod(flag,6,7);
}


void OXod(int flag)
{
  if(TableXod[1][1]==flag)DrawXorO(flag,5,70);// 1 1
  if(TableXod[1][2]==flag)DrawXorO(flag,5,90);// 1 2
  if(TableXod[1][3]==flag)DrawXorO(flag,5,110);// 1 3
  if(TableXod[1][4]==flag)DrawXorO(flag,5,130);// 1 4
  if(TableXod[1][5]==flag)DrawXorO(flag,5,150);// 1 4
  
  if(TableXod[2][1]==flag)DrawXorO(flag,25,70);// 2 1
  if(TableXod[2][2]==flag)DrawXorO(flag,25,90);// 2 2
  if(TableXod[2][3]==flag)DrawXorO(flag,25,110);// 2 3
  if(TableXod[2][4]==flag)DrawXorO(flag,25,130);// 2 4
  if(TableXod[2][5]==flag)DrawXorO(flag,25,150);// 2 4
  
  if(TableXod[3][1]==flag)DrawXorO(flag,45,70);// 3 1
  if(TableXod[3][2]==flag)DrawXorO(flag,45,90);// 3 2
  if(TableXod[3][3]==flag)DrawXorO(flag,45,110);// 3 3
  if(TableXod[3][4]==flag)DrawXorO(flag,45,130);// 3 4
  if(TableXod[3][5]==flag)DrawXorO(flag,45,150);// 3 4
  
  if(TableXod[4][1]==flag)DrawXorO(flag,65,70);// 4 1
  if(TableXod[4][2]==flag)DrawXorO(flag,65,90);// 4 2
  if(TableXod[4][3]==flag)DrawXorO(flag,65,110);// 4 3
  if(TableXod[4][4]==flag)DrawXorO(flag,65,130);// 4 4
  if(TableXod[4][5]==flag)DrawXorO(flag,65,150);// 4 4
  
  if(TableXod[5][1]==flag)DrawXorO(flag,85,70);// 5 1
  if(TableXod[5][2]==flag)DrawXorO(flag,85,90);// 5 2
  if(TableXod[5][3]==flag)DrawXorO(flag,85,110);// 5 3
  if(TableXod[5][4]==flag)DrawXorO(flag,85,130);// 5 4
  if(TableXod[5][5]==flag)DrawXorO(flag,85,150);// 5 4  
  
  if(TableXod[6][1]==flag)DrawXorO(flag,105,70);// 5 1
  if(TableXod[6][2]==flag)DrawXorO(flag,105,90);// 5 2
  if(TableXod[6][3]==flag)DrawXorO(flag,105,110);// 5 3
  if(TableXod[6][4]==flag)DrawXorO(flag,105,130);// 5 4
  if(TableXod[6][5]==flag)DrawXorO(flag,105,150);// 5 4   
}

  
void KompXod()
{

  TDate date;
  TTime time;
  GetDateTime(&date,&time);
  int x,y,counter=0;
  int num=(time.hour+time.min+time.sec)%9;
  x=num/3; y=num-3*x;
  while(TableXod[x+1][y+1]!=0 && counter<15)
  {
    counter++;
    if(num>=15) num=-1;
    num=(num+5)%9;
    x=num/5; y=num-5*x;
  }
  if (counter==15) return;
  TableXod[x+1][y+1]=2;
  count++;
  
 
  
}

void A_I()
{
  //if(DrawXoid==1)
  //{
   for(int i=1;i<=6;i++)
   {
   for(int j=1;j<=6;j++)
   {
   if (TableXod[i][j]==1)
   {
     if(i<5)
     {
       TableXod[i+1][j]=0;
     } 
     else
     if(j<5)
     {
       TableXod[i][j+1]=0;
     }
     
   }
   }
  }
 // }
}

void NullGame()
{
  for(int i=1;i<=6;i++)
  {
   for(int j=1;j<=6;j++)
   {
   TableXod[i][j]=0;
   }
  }
}



  

void Read_XOD(int flag)
{
  WSHDR *ws_res = AllocWS(128);
  
  if(
       (TableXod[1][1]==flag && TableXod[1][2]==flag && TableXod[1][3]==flag && TableXod[1][4]==flag )
    || (TableXod[1][2]==flag && TableXod[1][3]==flag && TableXod[1][4]==flag && TableXod[1][5]==flag )
    || (TableXod[2][1]==flag && TableXod[2][2]==flag && TableXod[2][3]==flag && TableXod[2][4]==flag)
    || (TableXod[2][2]==flag && TableXod[2][3]==flag && TableXod[2][4]==flag && TableXod[2][5]==flag)
    || (TableXod[3][1]==flag && TableXod[3][2]==flag && TableXod[3][3]==flag && TableXod[3][4]==flag)
    || (TableXod[3][2]==flag && TableXod[3][3]==flag && TableXod[3][4]==flag && TableXod[3][5]==flag)
    || (TableXod[4][1]==flag && TableXod[4][2]==flag && TableXod[4][3]==flag && TableXod[4][4]==flag )
    || (TableXod[4][2]==flag && TableXod[4][3]==flag && TableXod[4][4]==flag && TableXod[4][5]==flag )
    || (TableXod[5][1]==flag && TableXod[5][2]==flag && TableXod[5][3]==flag && TableXod[5][4]==flag )
    || (TableXod[5][2]==flag && TableXod[5][3]==flag && TableXod[5][4]==flag && TableXod[5][5]==flag )
    || (TableXod[6][1]==flag && TableXod[6][2]==flag && TableXod[6][3]==flag && TableXod[6][4]==flag )
    || (TableXod[6][2]==flag && TableXod[6][3]==flag && TableXod[6][4]==flag && TableXod[6][5]==flag )
    
      
//------------------------------------------------------------------------------      
    || (TableXod[1][1]==flag && TableXod[2][1]==flag && TableXod[3][1]==flag && TableXod[4][1]==flag )
    || (TableXod[2][1]==flag && TableXod[3][1]==flag && TableXod[4][1]==flag && TableXod[5][1]==flag )
    || (TableXod[3][1]==flag && TableXod[4][1]==flag && TableXod[5][1]==flag && TableXod[6][1]==flag )  

    || (TableXod[1][2]==flag && TableXod[2][2]==flag && TableXod[3][2]==flag && TableXod[4][2]==flag )
    || (TableXod[2][2]==flag && TableXod[3][2]==flag && TableXod[4][2]==flag && TableXod[5][2]==flag )
    || (TableXod[3][2]==flag && TableXod[4][2]==flag && TableXod[5][2]==flag && TableXod[6][2]==flag )
                  
    || (TableXod[1][3]==flag && TableXod[2][3]==flag && TableXod[3][3]==flag && TableXod[4][3]==flag )
    || (TableXod[2][3]==flag && TableXod[3][3]==flag && TableXod[4][3]==flag && TableXod[5][3]==flag )
    || (TableXod[3][3]==flag && TableXod[4][3]==flag && TableXod[5][3]==flag && TableXod[6][3]==flag )    
     
    || (TableXod[1][4]==flag && TableXod[2][4]==flag && TableXod[3][4]==flag && TableXod[4][4]==flag )
    || (TableXod[2][4]==flag && TableXod[3][4]==flag && TableXod[4][4]==flag && TableXod[5][4]==flag )
    || (TableXod[3][4]==flag && TableXod[4][4]==flag && TableXod[5][4]==flag && TableXod[6][4]==flag ) 
      
    || (TableXod[1][5]==flag && TableXod[2][5]==flag && TableXod[3][5]==flag && TableXod[4][5]==flag )
    || (TableXod[2][5]==flag && TableXod[3][5]==flag && TableXod[4][5]==flag && TableXod[5][5]==flag )
    || (TableXod[3][5]==flag && TableXod[4][5]==flag && TableXod[5][5]==flag && TableXod[6][5]==flag )  
      
//------------------------------------------------------------------------------      
    
    || (TableXod[1][2]==flag && TableXod[2][3]==flag && TableXod[3][4]==flag && TableXod[4][5]==flag )
    || (TableXod[1][1]==flag && TableXod[2][2]==flag && TableXod[3][3]==flag && TableXod[4][4]==flag )
    || (TableXod[2][2]==flag && TableXod[3][3]==flag && TableXod[4][4]==flag && TableXod[5][5]==flag ) 
    || (TableXod[2][1]==flag && TableXod[3][2]==flag && TableXod[4][3]==flag && TableXod[5][4]==flag )  
    || (TableXod[3][2]==flag && TableXod[4][3]==flag && TableXod[5][4]==flag && TableXod[6][5]==flag ) 
    || (TableXod[3][1]==flag && TableXod[4][2]==flag && TableXod[5][3]==flag && TableXod[6][4]==flag )       
    || (TableXod[6][2]==flag && TableXod[5][3]==flag && TableXod[4][4]==flag && TableXod[3][5]==flag )        
    || (TableXod[6][1]==flag && TableXod[5][2]==flag && TableXod[4][3]==flag && TableXod[3][4]==flag )  
    || (TableXod[5][2]==flag && TableXod[4][3]==flag && TableXod[3][4]==flag && TableXod[2][5]==flag )  
    || (TableXod[5][1]==flag && TableXod[4][2]==flag && TableXod[3][3]==flag && TableXod[2][4]==flag )  
    || (TableXod[4][2]==flag && TableXod[3][3]==flag && TableXod[2][4]==flag && TableXod[1][5]==flag )   
    || (TableXod[4][1]==flag && TableXod[3][2]==flag && TableXod[2][3]==flag && TableXod[1][4]==flag )        
     )
  {
    GBS_StopTimer(&timer);

    switch(flag)
    {
     case 1:
 
     
     if(MODE_GAME==2)
     {
     ena_two_g=0, end_game=1;
     wsprintf(ws_res,perc_t,"Первый игрок выиграл!");
     }
     else
     {
      ena_two_g=0, end_game=flag;
     wsprintf(ws_res,perc_t,"Вы выиграли!");
     }
   break;
    case 2:
    
     if(MODE_GAME==2)
     {
     ena_two_g=0, end_game=1;
     wsprintf(ws_res,perc_t,"Второй игрок выиграл!");
     
     }
     else
     {
       ena_two_g=0, end_game=1;
     wsprintf(ws_res,perc_t,"Вы проиграли!");
     }
  
    }   
  
  }
  
  DrawString(ws_res,0,35,240,240,FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  FreeWS(ws_res);
}



  
int color_frame[8]={23,23,23,23,23,23,23,23};

int draw_logo=1;
extern int _done[8];
extern int error_count;
int DRE(int x, int color)
{
  DrawRectangle(x , 160, x + 5,170, 0, GetPaletteAdrByColorIndex(22), GetPaletteAdrByColorIndex(color));
  return 0;
}
int exit_ungraf=0;

static void OnRedraw(MAIN_GUI *data)//------------------------------------------
{
int scr_w=ScreenW();
int scr_h=ScreenH();  

//int prog_x=0;
if(IsLoadGraph==1)
{
  WSHDR *ws_load = AllocWS(128);
  int dlina=7*img_count;
  //if(dlina>92)dlina=96-36;
  //if(img_count==7)dlina=96-36;
  //dlina=(dlina>115) ? 112: +14;
  
  DrawRectangle(0,YDISP,scr_w-1,scr_h-1,0,
		   GetPaletteAdrByColorIndex(1),
		   GetPaletteAdrByColorIndex(1));
  
   DrawRectangle(33,scr_h/3+20,101,scr_h/3+30,0,
		   GetPaletteAdrByColorIndex(0),
		   GetPaletteAdrByColorIndex(23));
   
   DrawRectangle(35,scr_h/3+22,36+dlina,scr_h/3+28,0,
		   GetPaletteAdrByColorIndex(0),
		   GetPaletteAdrByColorIndex(22));
  
   DRE(33,color_frame[1]);
   DRE(43,color_frame[2]);
   DRE(53,color_frame[3]);
   DRE(63,color_frame[4]);
   DRE(73,color_frame[5]);
   DRE(83,color_frame[6]);
   DRE(93,color_frame[7]);
   
   wsprintf(ws_load,perc_t,"E X-O");
   DrawString(ws_load,0, scr_h/5 ,240,320,2,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
   
   if(img_count!=7){
   wsprintf(ws_load,perc_t,"Загрузка...");
   DrawString(ws_load,0, scr_h/3 ,240,320,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
   }
  
   
   switch(img_count)
   {
    case 1:
          if(_done[1]==1)
      {
    
     wsprintf(ws_load,perc_t,"5% / 100%\no.png : загружен");  
     color_frame[1]=4;
      }
      else
        {
       color_frame[1]=2;
       wsprintf(ws_load,perc_t,"5% / 100%\no.png : не найден!");  
      }
   
    break;
    case 2:
     
      if(_done[2]==1)
      {
      color_frame[2]=4;  
      wsprintf(ws_load,perc_t,"10% / 100%\nx.png : загружен"); 
      }
      else
      {
      color_frame[2]=2;
      wsprintf(ws_load,perc_t,"10% / 100%\nx.png : не найден!"); 
      }
  
    break;
    case 3:
            if(_done[3]==1)
      {
      color_frame[3]=4;  
    wsprintf(ws_load,perc_t,"20% / 100%\ngame_cursor.png : загружен");
      }
      else
      {
     color_frame[3]=2;  
    wsprintf(ws_load,perc_t,"20% / 100%\ngame_cursor.png : не найден!");
      }
    
    break;
    case 4:
               if(_done[4]==1)
      {
      color_frame[4]=4;  
      wsprintf(ws_load,perc_t,"30% / 100%\nmenu_cursor.png : загружен");  
      }
      else
      {
        color_frame[4]=2;  
      wsprintf(ws_load,perc_t,"30% / 100%\nmenu_cursor.png : не найден!");
      }
   
    break;
    case 5:
      if(_done[5]==1)
      {
      color_frame[5]=4;  
      wsprintf(ws_load,perc_t,"45% / 100%\nlogo.png : загружен");    
      }
      else
      {
      color_frame[5]=2;  
      wsprintf(ws_load,perc_t,"45% / 100%\nlogo.png : не найден!");    
      }
    break;
    case 6:
     if(_done[6]==1)
      {
      color_frame[6]=4;  
      wsprintf(ws_load,perc_t,"70% / 100%\ntable.png : загружен");  
      }
     else
     {
       color_frame[6]=2;  
      wsprintf(ws_load,perc_t,"70% / 100%\ntable.png : не найден!");
     }
   
    break;
    case 7:
      if(_done[7]==1)
      {
      color_frame[7]=4;  
     wsprintf(ws_load,perc_t,"100% / 100%\nfon.png : загружен"); 
      }
      else
      {
      color_frame[7]=2;  
       wsprintf(ws_load,perc_t,"100% / 100%\nfon.png : не найден"); 
      }
    break;
    default:
      if(error_count==7)
      {
        wsprintf(ws_load,perc_t,"Ошибка!Отсутствует графика!"); 
        exit_ungraf=1;
        IsLoadGraph=1;
      }
      else
      {
      wsprintf(ws_load,perc_t,"Игра загружена");
      }
}
   DrawString(ws_load,0, 90 ,240,320,FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
   FreeWS(ws_load);

}
else
{
  DrawRectangle(0,YDISP,scr_w-1,scr_h-1,0,
		   GetPaletteAdrByColorIndex(1),
		   GetPaletteAdrByColorIndex(1));
  
  
  DrwImg(fon, 0,0, NULL,NULL);
if(draw_logo==1)DrwImg(logo, 26,48, NULL,NULL);
 if(IsMenu)
 {
  
   DrawMainMenu();
   if(eDrawInfo==1)DrawAbout();
 }
 
 if(NewGame)
 {
  
   DrawLevel();
   if(MODE_GAME==2)DrawWhoIsXod();
   Read_XOD(1);
   Read_XOD(2);
   OXod(1);
   OXod(2);
   FringFig(1);
   FringFig(2);
   DrwImg(game_cursor, game_cur_x,game_cur_y, NULL,NULL);
 }
  
  
}
if(exit_ungraf==1)
{
   WSHDR *ws_err = AllocWS(128);
   
  DrawRectangle(0,YDISP,scr_w-1,scr_h-1,0,
		   GetPaletteAdrByColorIndex(2),
		   GetPaletteAdrByColorIndex(2));
  wsprintf(ws_err,perc_tt,"Ошибка!\nОтсутствует графика!\nПроверьте расположение графики\n\nТребуемый путь\n\n",PIC_DIR); 
  DrawString(ws_err,0, 30 ,240,320,FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  
   wsprintf(ws_err,perc_t,"ВЫХОД");
   DrawString(ws_err,0, 160 ,240,320,FONT,4,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  
  
   FreeWS(ws_err);
}

if(IsConnectProcess)
{
  
}

}


//=========ОnClose
void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if(fon)
  { 
   mfree(fon->bitmap);
   mfree(fon);
  }
  if(table)
  { 
   mfree(table->bitmap);
   mfree(table);
  }
   if(game_cursor)
  { 
   mfree(game_cursor->bitmap);
   mfree(game_cursor);
  }
   if(menu_cursor)
  { 
   mfree(menu_cursor->bitmap);
   mfree(menu_cursor);
  }
   if(draw_x)
  { 
   mfree(draw_x->bitmap);
   mfree(draw_x);
  }
     if(draw_o)
  { 
   mfree(draw_o->bitmap);
   mfree(draw_o);
  }
       if(logo)
  { 
   mfree(logo->bitmap);
   mfree(logo);
  }
  
  
  FreeWS(data->ws1);
  FreeWS(data->ws2);
  data->gui.state=0;
}



void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
 
  data->ws1=AllocWS(256);
  data->ws2=AllocWS(256);
  data->gui.state=1;
}



void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{ 
  DisableIDLETMR();
  data->gui.state=2;
 
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
  
}


int ena_one_g=1;
void AntiXod()
{
  if((TableXod[x_n_poz][y_n_poz]==1)||(TableXod[x_n_poz][y_n_poz]==2))
  {
     WSHDR *ws_anti = AllocWS(128);
     wsprintf(ws_anti,perc_t,"Не верно!");
     DrawString(ws_anti,0,25,240,240,FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
     FreeWS(ws_anti);
           
  }
  else
  {
    if(MODE_GAME==2)
    {
      if(ena_two_g==1)
      {
        Write_XOD(1);
        DrawXoid++;
        ena_two_g=2;

      }
      else
      if(ena_two_g==2)
      {
        Write_XOD(2);
        DrawOoid++;
        ena_two_g=1;

      }
    }
    else
  {
        Write_XOD(1);
        DrawXoid++;
        KompXod();
        //A_I();
  }
  
  }
  
}
  




void InitParametres()
{
  TimeGame();
  
  IsMenu=0, 
  NewGame=1,

  DrawXoid=0,
  DrawOoid=0,
  count=0,
  
  end_game=0,
  nich=0,
  
  x_n_poz=3 , 
  y_n_poz=5,

  ena_two_g=1,
  ena_msg_fal=1,
  ena_msg=1,
 
  game_cur_x=45,
  game_cur_y=150,
    
  theme_tick=0, 
  theme_time=0, 
  game_time_m_sec=0;
}


void NullTableXod()
{
  for(int i=1;i<=7;i++)
  for(int j=1;j<=8;j++)
  TableXod[i][j]=0;
}
int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
 DirectRedrawGUI();

//REDRAW();

if (msg->gbsmsg->msg==KEY_DOWN)
{
 switch(msg->gbsmsg->submess)
 {
 case LEFT_SOFT:
  if(eDrawInfo==1)eDrawInfo=0;
  draw_logo=1;
  if(NewGame==1)
   {
     
     draw_logo=0;
   }
  break;
 case RIGHT_SOFT: 
   if(exit_ungraf==1)
   {
     CloseCSM(MAINCSM_ID);
   }
   else
   {
   if(eDrawInfo==1)
   {
     eDrawInfo=0;
     draw_logo=1;
   }
   
  
   if(NewGame==1)
   {
     draw_logo=1;
     NullGame();
     NewGame=0;
     IsMenu=1;
   }
   }
   
 break;
 
 case LEFT_BUTTON:
 case '4':

      if(IsMenu==1)
      {
        if(cur_y==320/4-2+20)
        {
         //if(one_gamer==1)one_gamer=0;else one_gamer+=1;
        // if(two_gamer==0)two_gamer=1;else two_gamer-=1;
         if(MODE_GAME==1)MODE_GAME=3;else MODE_GAME--;
         //one_gamer += (one_gamer==1) ? 0: 1;
         //two_gamer -= (two_gamer==0) ? 1: 1;
        }
      }
      else
      if(NewGame==1)
      {
           if(x_n_poz==1)x_n_poz=6;else x_n_poz--;
           if(game_cur_x==5)game_cur_x=105; else game_cur_x-=20;
           //x_n_poz -= (x_n_poz==1) ? 6 :1;
           //game_cur_x -= (game_cur_x==5) ? 105: 20;
      }
 break;
 
 case RIGHT_BUTTON:
 case '6':
      if(IsMenu==1)
      {
        if(cur_y==320/4-2+20)
        {
         //if(one_gamer==1)one_gamer=0;else one_gamer+=1;
         //if(two_gamer==0)two_gamer=1;else two_gamer-=1;
         if(MODE_GAME==3)MODE_GAME=1;else MODE_GAME++;
         //one_gamer += (one_gamer==1) ? 0: 1;
         //two_gamer -= (two_gamer==0) ? 1: 1;
        }
      }
      else
      if(NewGame==1)
      {
        
          
           if(x_n_poz==6)x_n_poz=1;else x_n_poz++;
           
           if(game_cur_x==105)game_cur_x=5; else game_cur_x+=20;
        
            //x_n_poz += (x_n_poz==6) ? 1 :1;
            //game_cur_x += (game_cur_x==150) ? 5: 20;
      }
 break;
    
 case DOWN_BUTTON:
 case '8':
      if(IsMenu==1)
      {
           //if(cur_y==320/4-2)cur_y+=20;
           if(cur_y==320/4-2+60)cur_y=320/4-2;else cur_y+=20;
           //cur_y += (cur_y==320/4-2+60) ? 320/4-2 :20;
      }
      else
      if(NewGame==1)
      {
           if(y_n_poz==5)y_n_poz=1;else y_n_poz++;
           if(game_cur_y==150)game_cur_y=70; else game_cur_y+=20;
           //y_n_poz += (y_n_poz==5) ? 1 :1;
           //game_cur_y += (game_cur_y==150) ? 70: 20;
      }
 break;
    
 case UP_BUTTON:
 case '2':
      if(IsMenu==1)
      {
           if(cur_y==320/4-2)cur_y=320/4-2+60;else cur_y-=20;
           //cur_y -= (cur_y==320/4-2) ? 320/4-2+60 :20;
           //if(cur_y==320/4-2+40)cur_y-=20;
      }
      else
      if(NewGame==1)
      {
           if(y_n_poz==1)y_n_poz=5;else y_n_poz--;
           if(game_cur_y==70)game_cur_y=150; else game_cur_y-=20;
           
          // y_n_poz -= (y_n_poz==1) ? 5 :1;
           //game_cur_y -= (game_cur_y==70) ? 150: 20;
      }
 break; 
    
    case ENTER_BUTTON: 
    case '5':
      if(IsMenu==1)
      {
       if(cur_y==320/4-2)
       {
        if(MODE_GAME==3)
        {
          //CONNECT_GUI();
          IsConnectProcess=1;
        }
        else
        {
         draw_logo=0;
         InitParametres();
        }
      }
      else
      if(cur_y==320/4-2+60)CloseCSM(MAINCSM_ID);else
      if(cur_y==320/4-2+40)eDrawInfo=1; 
      }
      else
      if(NewGame==1)
      {
        if(end_game==0)AntiXod();
        
      }
    break;
    case RED_BUTTON:
    if(exit_ungraf==1)CloseCSM(MAINCSM_ID);
   
   break;
    }           

    
}
return(0);
}





void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  mfree_adr(data);
}

void ElfKiller(void)
{
  
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

int method8(void){return(0);}
int method9(void){return(0);}
const void * const gui_methods[11]={
  (void *)OnRedraw,	
  (void *)onCreate,	
  (void *)onClose,	
  (void *)onFocus,	
  (void *)onUnfocus,
  (void *)OnKey,	
  0,
  #ifdef NEWSGOLD
  (void *)onDestroy,
  #else
  (void *)kill_data,	
  #endif
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,129,129};
void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  MAINGUI_ID=csm->gui_id;
}

int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}



void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)ElfKiller);
  GBS_DelTimer(&timer);
  GBS_DelTimer(&load_img);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  

  return(1);
}
  


const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {//meerc.ifmo ip
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"E X-O (C) Vedan");
}

int main(void)
{
  InitConfig();
  T_Load_IMG();
  UpdateCSMname();
  CSM_RAM main_csm;
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  return 0;
}

