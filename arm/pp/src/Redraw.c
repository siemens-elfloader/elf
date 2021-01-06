/*
* Ping-Pong 2009 - 2010
* Redraw
* (c) Danil_e71
*/

#include "Redraw.h"
#include "pp.h"

void DRE(int x, int color)//фреймы при загрузке
{
  DrawRectangle(x , nimg*220, x + nimg*10,max_width, 0, GetPaletteAdrByColorIndex(22), GetPaletteAdrByColorIndex(color));
}
 
void outtextxy(char* str)//Для вывода текста
{ 
  WSHDR *ws = AllocWS(strlen(str)+1);
  wsprintf(ws,perc_t,str);
  DrawString(ws,0,130*nimg,239*nimg,310*nimg,FONT,2,GetPaletteAdrByColorIndex(6),NULL);
  FreeWS(ws);
}

void png(int w)
{
  clear++;
  switch(w)
  {
  case 4:pics[0]=CreateIMGHDRFromPngFile(images[4], 2);break;//user1
  case 3:pics[1]=CreateIMGHDRFromPngFile(images[3], 2);break;//user2
  case 5:pics[2]=CreateIMGHDRFromPngFile(images[5], 2);break;//ball
  case 1:pics[3]=CreateIMGHDRFromPngFile(images[1], 2);break;//cur
  case 0:pics[4]=CreateIMGHDRFromPngFile(images[0], 2);break;//logo
  case 2:pics[5]=CreateIMGHDRFromPngFile(images[2], 2);break;//fon
  }
}

void T_Load_IMG()
{
  loading(img_count);
  img_count++;
  if(img_count<8){GBS_StartTimerProc(&tmr, timer_speed, T_Load_IMG);}
  if(img_count==8){GBS_DelTimer(&tmr);}
}

void DrwImg(IMGHDR *img, int x, int y)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  DrawObject(&drwobj);
}

void Game()
{
Time.mymsec++;
if(Time.mymsec>=(TMR_SECOND/timer_speed-15)){Time.mymsec=0;Time.sec++;}
if(Time.sec==60){Time.min++;Time.sec=0;}
if(Time.min==60){Time.hour++;Time.min=0;}
if(Time.hour>=1){sprintf(Time.str,"%d ч %d м %d с",Time.hour,Time.min,Time.sec);}
else
if(Time.min>=1){sprintf(Time.str,"%d м %d с",Time.min,Time.sec);}
else{sprintf(Time.str,"%d с",Time.sec);}
DrwImg(pics[5],0,0);
move_ball();
DrawLine(1,((max_height-cpu.height-user.height-cpu.y)/2)+cpu.y,max_width-1,((max_height-cpu.height-user.height-cpu.y)/2)+cpu.y,0,linecol2);
DrwImg(pics[0],user.x,user.y);
DrwImg(pics[2],ball.x,ball.y);
DrwImg(pics[1],cpu.x,cpu.y);
if (running==1){move_block();
GBS_StartTimerProc(&tmr,timer_speed,Game);}
}

void mfreeImages()//Убираем все картинки
{
  for(int i=0;i<5;i++)mfree(images[i]);
}
void mfreelang()//Удаляем язык
{
  for(int i=0;i<58;i++)mfree(lang[i]);
}
void malloclang()//Выделяем память под язык
{
  for(int i=0;i<=58;i++)lang[i]=malloc(60);
}
void deleteIMGHDR(IMGHDR *img)//Чистилище)))
{
 if(img!=NULL&&img && img->bitmap) {mfree(img->bitmap);mfree(img);}
}
void delimghdr()
{
  for(int i=0;i<clear;i++)deleteIMGHDR(pics[i]);
}
void GetSize()//Получаем размеры юзера+бола+цпу
 {
  user.width=pics[0]->w;
  user.height=pics[0]->h;
  cpu.width=pics[1]->w;
  cpu.height=pics[0]->h;
  ball.width=pics[2]->w;
  ball.height=pics[2]->h;
}
void Init()
{
  cur_y=112;
  status=load;
  malloclang();
  images[0]=malloc(sizeof(folder)+strlen("img\\logo.png")+1);
  images[1]=malloc(sizeof(folder)+strlen("img\\cursor.png")+1);
  images[2]=malloc(sizeof(folder)+strlen("img\\fon.png")+1);
  images[3]=malloc(sizeof(folder)+strlen("img\\user2.png")+1);
  images[4]=malloc(sizeof(folder)+strlen("img\\user1.png")+1);
  images[5]=malloc(sizeof(folder)+strlen("img\\ball.png")+1);
  sprintf(images[0],per_s,folder,"img\\logo.png");//logo
  sprintf(images[1],per_s,folder,"img\\cursor.png");//cur
  sprintf(images[2],per_s,folder,"img\\fon.png");//fon
  sprintf(images[3],per_s,folder,"img\\user2.png");//user2
  sprintf(images[4],per_s,folder,"img\\user1.png");//user1
  sprintf(images[5],per_s,folder,"img\\ball.png");//ball
  loadNastr();
}

void RedrawScreen()//Собственно функция перерисовки процесса игры
{
WSHDR *ws_menu = AllocWS(32);
if(status!=game)DrwImg(pics[4],0,0);
else Game();
switch(status)
{
case menu:
 {
DrwImg(pics[3],cur_x,cur_y);

switch(game_new_cont)
{
case 1:wsprintf(ws_menu,perc_t,lang[1]);break;
case 2:wsprintf(ws_menu,perc_t,lang[2]);break;
case 3:wsprintf(ws_menu,perc_t,lang[3]);break;
}
DrawString(ws_menu,0,main_y,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
switch(saveload)
{
case 2:wsprintf(ws_menu,perc_t,lang[5]);break;
default:wsprintf(ws_menu,perc_t,lang[4]);break; 
}
DrawString(ws_menu,0,main_y+nimg*40,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
switch(mode)
{
case 1: wsprintf(ws_menu,perc_t,lang[6]); break; 
case 0: wsprintf(ws_menu,perc_t,lang[8]); break;
}
DrawString(ws_menu,0,main_y+nimg*80,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));

wsprintf(ws_menu,perc_t,lang[9]);
DrawString(ws_menu,0,main_y+nimg*120,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));

wsprintf(ws_menu,perc_t,lang[10]);
DrawString(ws_menu,0,main_y+nimg*160,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));

wsprintf(ws_menu,perc_t,lang[11]);
DrawString(ws_menu,0,main_y+nimg*200,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
}
break;
case settings:
{
DrwImg(pics[3],cur_x,cur_y);
wsprintf(ws_menu,perc_t,lang[12]);
DrawString(ws_menu,0,main_y,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
wsprintf(ws_menu,perc_t,lang[26]);
DrawString(ws_menu,0,main_y+nimg*40,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
}
break;
case settings_igra:
{
DrwImg(pics[3],cur_x,cur_y);
wsprintf(ws_menu,perc_t,lang[15]);
DrawString(ws_menu,0,main_y,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(3),GetPaletteAdrByColorIndex(23));
switch(difficult)
{
case 0:wsprintf(ws_menu,perc_t,lang[16]);break;
case 1:wsprintf(ws_menu,perc_t,lang[17]);break;
case 2:wsprintf(ws_menu,perc_t,lang[18]);break;
}
DrawString(ws_menu,0,main_y+nimg*40,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));

wsprintf(ws_menu,perc_t,lang[19]);
DrawString(ws_menu,0,main_y+nimg*80,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(3),GetPaletteAdrByColorIndex(23));
switch(speed_game)
{
case 0:wsprintf(ws_menu,perc_t,lang[20]);break;
case 1:wsprintf(ws_menu,perc_t,lang[21]);break;
case 2:wsprintf(ws_menu,perc_t,lang[22]);break;
case 3:wsprintf(ws_menu,perc_t,lang[23]);break;
}
DrawString(ws_menu,0,main_y+nimg*120,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
wsprintf(ws_menu,perc_t,lang[24]);
DrawString(ws_menu,0,main_y+nimg*160 ,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(3),GetPaletteAdrByColorIndex(23));
switch(mode)
{
case 0:wsprintf(ws_menu,perc_t,lang[25]);break;
case 1:wsprintf(ws_menu,"<  %d  >",lives);break;
}
DrawString(ws_menu,0,main_y+nimg*200,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
}
break;
case music:
{
DrwImg(pics[3],cur_x,cur_y);
wsprintf(ws_menu,perc_t,lang[28]);
DrawString(ws_menu,0,main_y,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(3),GetPaletteAdrByColorIndex(23));
switch(on_off_sound)
{
case 0:wsprintf(ws_menu,perc_t,lang[29]);break;
case 1:wsprintf(ws_menu,perc_t,lang[31]);break;
case 2:wsprintf(ws_menu,perc_t,lang[32]);break;
}
DrawString(ws_menu,0,main_y+nimg*40,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
wsprintf(ws_menu,perc_t,lang[33]);
DrawString(ws_menu,0,main_y+nimg*80,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(3),GetPaletteAdrByColorIndex(23));
wsprintf(ws_menu,"<  %d  >",def_vol);
DrawString(ws_menu,0,main_y+nimg*120,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
wsprintf(ws_menu,perc_t,lang[34]);
DrawString(ws_menu,0,main_y+nimg*160,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(3),GetPaletteAdrByColorIndex(23));
switch(vibra)
{
case 1:wsprintf(ws_menu,perc_t,lang[30]);break;
default:wsprintf(ws_menu,perc_t,lang[29]);break;
}
DrawString(ws_menu,0,main_y+nimg*200,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
}
break;
case rec:
{
wsprintf(ws_menu,perc_t,lang[35]);
DrawString(ws_menu,0,nimg*17,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
for(int i=0;i<NUM_RECORD;i++)
{
wsprintf(ws_menu,"%d.  %s  %d",i+1,record.name[i],record.points[i]);
DrawString(ws_menu,nimg*35,nimg*37+i*(30),nimg*35+Get_WS_width(ws_menu,FONT),nimg*37+i*(30)+GetFontYSIZE(FONT),FONT,2,GetPaletteAdrByColorIndex(3),GetPaletteAdrByColorIndex(23));
}
}
break;
}
FreeWS(ws_menu);
}

void load_lang()
{
WSHDR *ws_menu = AllocWS(64);
DrawRoundedFrame(0,0,max_width,max_height,0,0,0,NULL,bgcol);
DrawRoundedFrame(cur_x,cur_y,nimg*210,cur_y+nimg*30,0,0,0,NULL,bgcol_lang_cur);
switch(langenru)
{
case 0:wsprintf(ws_menu,perc_t,LGP_MENU_LANG1);break;
case 1:wsprintf(ws_menu,perc_t,LGP_MENU_LANG2);break;
}
DrawString(ws_menu,0,max_height/4 ,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23)); 
wsprintf(ws_menu,perc_t,LGP_LANG_RU);
DrawString(ws_menu,0,max_height/4+nimg*40,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23)); 
wsprintf(ws_menu,perc_t,LGP_LANG_EN);
DrawString(ws_menu,0,max_height/4+nimg*80,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
FreeWS(ws_menu);
}

void loading(int flag)
{
FSTATS fs;
WSHDR *ws_load = AllocWS(64);
WSHDR *ws_load2 = AllocWS(64);
int dlina=nimg*29*flag;
DrawRoundedFrame(0,0,max_width,max_height,0,0,0,NULL,bgcol);
DrawRectangle(3,max_height/3+nimg*80,max_width-3,max_height/3+nimg*92,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
DrawRectangle(5,max_height/3+nimg*82,nimg*32+dlina,max_height/3+nimg*90,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(22));
wsprintf(ws_load2,perc_t,lang[0]);
DrawString(ws_load2,0, max_height/5 ,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
for(int i=1;i<=6;i++)DRE(nimg*3+i*(30),color_frame[i]);
switch(flag)
 {
   case 6:
     {
     if(error_count>0)
      {
      DrawRoundedFrame(0,0,max_width,max_height,0,0,0,NULL,bgcol);
      WSHDR *ws_err = AllocWS(128);
      wsprintf(ws_err,perc_t,lang[44]); 
      DrawString(ws_err,0, nimg*120 ,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
      FreeWS(ws_err);
      }
     else
     {
      WSHDR *ws_err = AllocWS(128);
      wsprintf(ws_err,perc_t,lang[45]); 
      DrawString(ws_err,0, nimg*120 ,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
      FreeWS(ws_err);
     }
     GetSize();
   }
   break;
   case 7:
     {
     if(error_count>0)
      {
      DrawRoundedFrame(0,0,max_width,max_height,0,0,0,NULL,bgcol);
      WSHDR *ws_err = AllocWS(128);
      wsprintf(ws_err,"%t%s%s",lang[46],folder,"img\\"); 
      DrawString(ws_err,0, nimg*30 ,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
      FreeWS(ws_err);
      }
     else
     {
       cur_y=52;
      status=menu;
      RedrawScreen();
     }
    
   }
    break;
  default:
    {
  if(GetFileStats(images[flag],&fs,0)!=-1)
{
  wsprintf(ws_load,"%s: %t",images[flag],lang[42]); 
  png(flag);
  color_frame[flag+1]=4;
}
else
{
  error_count++;
  color_frame[flag+1]=2;
  wsprintf(ws_load,"%s: %t",images[flag],lang[43]);
}
DrawString(ws_load,0, max_height/3 ,max_width,max_height,FONT,2,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
    }
   }


FreeWS(ws_load);
FreeWS(ws_load2);
}
