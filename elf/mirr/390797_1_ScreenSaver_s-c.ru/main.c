/****************************************************************************************************************************
iphone_saver.elf (main.c)
(с)Mirrr (http://init.org.ua, mirrr@ukr.net)
(с)2008 

Разрешается модифицировать и использовать по вашему усмотрению любой документ из архива,
при условиях:
 - не удаляйте копирайты и адрес сайта, а также данное уведомление из исходных кодов программы.
 - при модификации программы не удаляйте логотип сайта http://init.org.ua, отображаемый один раз при первом запуске эльфа.

Эта программа является свободно распространяемой; Вы можете распространять ее повторно и (или) изменять, 
соблюдая условия Открытого лицензионного соглашения GNU (GNU GPL), опубликованного Фондом свободно распространяемого 
программного обеспечения; либо редакции 2 Соглашения, либо (на ваше усмотрение) любой редакции, выпущенной позже.
Эта программа распространяется в надежде на то, что она окажется полезной, но БЕЗ КАКИХ-ЛИБО ГАРАНТИЙ, 
включая подразумеваемую гарантию КАЧЕСТВА либо ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. 

Подробности содержатся в Открытом лицензионном соглашении GNU.

Вместе с этой программой должен распространяться экземпляр Открытого лицензионного соглашения GNU, если он 
отсутствует, сообщите об этом в Фонд свободно распространяемого программного обеспечения 
(Free Software Foundation, Inc.), 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA 
***************************************************************************************************************************/

#include "swilib.h"
#include "SWILIB.C"
#include "Colors.h"
#include "Variable.h"
#include "Events.h"
#include "Funct.h"

//файлы картинок ================================================================================================
#include "_file2_png.c"  //о.. это светлячек красный, не отключайте их ибо не дам больше исходников)
#include "fon1_png.c"    //подложка под часы и снизу 
#include "exclam_png.c"  // знак разряженой батареи (восклицательный знак в треугольнике)
#include "left1_png.c"   //левая часть батареи  [зеленая]
#include "left2_png.c"   //левая часть батареи  [красная]      
#include "right1_png.c"  //правая часть батареи  [зеленая]  
#include "right2_png.c"  //правая часть батареи  [пустая]  
#include "center1_png.c" //средняя часть батареи [зеленая] (ширина 8пикс)   
#include "center3_png.c" //средняя часть батареи [пустая] (ширина 8пикс)   
#include "line_png.c"    //зеленая полоска справа
#include "line2_png.c"   //зеленая полоска слева   (их я отключил)
#include "ree2_png.c"     //Часы!!! Ну нарисуйте получше)) Они еще в мейне режутся на кучу циферок)
#include "slide_png.c"    //подложка со стрелкой (всплывающая подсказка)
#include "iconbar2_png.c" //иконбар
//=====================================================================================================


#include "string_works.h"
char enter[] = "\x0D\x0A";
char battery = 100; int ZONEmin = 0; int ZONEnet = 0;
//IPC constants for XTask interface


void Hide()
{
  gipc.name_to=ipc_xtask_name;
  gipc.name_from=ipc_my_name;
  gipc.data=0;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_IDLE,&gipc);
}


int off=0;


//-------------------- Проверка, запущена ли другая копия заставки ---------------------------------------
void CheckDoubleRun(void)
{
  int csm_id;
  if ((csm_id=(int)(gipc.data))!=-1)
  {
    gipc.name_to=ipc_xtask_name;
    gipc.name_from=ipc_my_name;
    gipc.data=(void *)csm_id;

    LockSched();
    CloseCSM(MAINCSM_ID);
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_SHOW_CSM,&gipc);
    UnlockSched();
}}

//===================================  Функции ТАЙМЕРОВ ===============================================================================

void TimeZone() //Вызывается каждые три секунды, проверяет изменилось-ли состояние минут, если да то перерисовка
{if (state >3){  //Сама заставка находится выше 3 состояния, ниже идет лого http://init.org.ua
    TDate date;  
    TTime time; 
    GetDateTime(&date,&time); 
    if (ZONEmin != time.min) {state = 4; DirectRedrawGUI_ID (MAINGUI_ID); ZONEmin = time.min;}
   
  if (bond) {GBS_DelTimer(&time_timer); GBS_StartTimerProc(&time_timer, TMR_SECOND*3, TimeZone);} //запуск таймера снова на 3 сек
} }


void TimeSleep()  // Время сна)) Гасим подсветку через 5 секунд         
{

  SetIllumination(1,1,0,200);
  Illumination = 0;
  SetIllumination(0,1,0,200);  
}

void TimeTouch()  // Сбрасывается состояние двойного нажатия для разблокировки (секунда)         
{
Touch = 0; 
}

void Mod0() 
{
  state = 1;
  DirectRedrawGUI_ID (MAINGUI_ID);
}

void Mod1() 
{
  if (tike <= 22 && cop == 1)
  {
    state = 1;
    DirectRedrawGUI_ID (MAINGUI_ID);
    tike++;
  }
  else
    if (cop == 0)
    {
      state = 4;
      DirectRedrawGUI_ID (MAINGUI_ID);
      tike=0;
    }/*
  else
    {
      state = 2;
      DirectRedrawGUI_ID (MAINGUI_ID);
      tike=0;
    }*/  
} 
/*
void Mod2() // по таймеру перерисовываемдвижение светлячков на лого
{
  if (tike <= 97 && cop == 1)
  {
    state = 2;
    DirectRedrawGUI_ID (MAINGUI_ID);
    tike++;
  } 
  else if (cop == 0)
  {
    state = 4;
    DirectRedrawGUI_ID (MAINGUI_ID);
    tike=0;
  }
  else
  {
    state = 3;
    DirectRedrawGUI_ID (MAINGUI_ID);
    tike=0;
  }

} 
*/
void Mod3() // 
{
  if (tike <= 80  && cop == 1)
  {
    state = 3;
    DirectRedrawGUI_ID (MAINGUI_ID);
    tike++;
  }
  else
  {
    state = 4;
    KbdLock();
    DirectRedrawGUI_ID (MAINGUI_ID);
    tike=0;
  }
}

void Mod4() // по таймеру перерисовка заставки
{
  if (zzy>64 ) state = 4; else Vniz=1;
  DirectRedrawGUI_ID (MAINGUI_ID);  
 
  if (zzy<65) 
  {
    state = 5;
    zzy += 5;
    DirectRedrawGUI_ID (MAINGUI_ID);
  }
   else
   {
     state = 4;
     DirectRedrawGUI_ID (MAINGUI_ID);
   }
}


void OnRedraw(MAIN_GUI *data)
{
  //DisableIconBar(1);

  if (state == 1)
  {
    DrawRoundedFrame( 0,0,239,319, 0, 0, 0, GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1) );
    if (bond) 
    {
      GBS_DelTimer(&idle_timer);
      GBS_StartTimerProc(&idle_timer, TMR_SECOND/60, Mod2);
    }
  }  

/*
if (state == 2) {      // логотип  init.org.ua  
  if (uin == 1)   {SetIllumination(1,1,cur_keys,200);
  SetIllumination(0,1,cur_display,200);uin =0;
   Illumination = 1;
  }
  
  DrawRectangle(0,0,239,319,2,cfg333_ID,cfg333_ID );
  if ((xx2-FImage2->w)>100 && xx2<200) { DrwPngImg(FImage2, 120-(FImage2->w)/2,xx1-FImage2->w); DrwPngImg(FImage2, 120-(FImage2->w)/2,320 - (xx3-FImage2->w));}
  
  DrwPngImg(FImage2, xx2-FImage2->w,170 - xx5 -(FImage2->w)/2);
  DrwPngImg(FImage2, 240 - (xx4-FImage2->w),170-(FImage2->w)/2);  
  WSHDR * ws = AllocWS( 124 );
  wsprintf(ws,"http://init.org.ua"); 
  DrawString( ws,1,158,239,319, 5, 2, co127, GetPaletteAdrByColorIndex(23)); 
  FreeWS(ws);
  if (xx2>40 && co127[0]<250) {co127[0]+=2;co127[2]+=2;}// cfg333_ID[0] +=2;
 xx1 +=5;
 xx2 += 4;
 xx3 +=5;
 xx4 += 4;
 if (bond) {GBS_DelTimer(&idle_timer); GBS_StartTimerProc(&idle_timer, TMR_SECOND/75, Mod2);}
 }  



if (state == 3) {    //плавный переход от логотипа к  заставке     
  if (co127[0]>5) {co127[0]-=2;co127[2]-=2;}
  WSHDR * ws = AllocWS( 124 );
  wsprintf(ws,"http://init.org.ua"); 
  DrawString( ws,1,158,239,319, 5, 2, co127, GetPaletteAdrByColorIndex(23)); 
  FreeWS(ws);
  if (bond) {GBS_DelTimer(&idle_timer);GBS_StartTimerProc(&idle_timer, TMR_SECOND/75, Mod3);}
 }  
*/


if (state == 4 || zzy==0)
{  

//DrawCanvas(data, 0, 0, 239, 319, 1);
   int y=1;
    DrawRoundedFrame( 0,0,239,319, 0, 0, 0, GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(1));
   
    int yyu= 110; int xxu= 20;
    battery = *RamCap();
    if (battery>4) DrwPngImg(FImage3, xxu,yyu);   
    else DrwPngImg(FImage3b, xxu,yyu); 
  
    for (int b = xxu+15; b<=xxu+175; b+=8) {
      
      if (battery < y*5) DrwPngImg(FImage6b, b,yyu);
      else DrwPngImg(FImage6, b,yyu); 
    y++;
  }
  
  if (battery>99) DrwPngImg(FImage5, xxu+175,yyu);   
  else DrwPngImg(FImage5b, xxu+175,yyu);   
  
  if (battery<5) DrwPngImg(FImage1, xxu+20,yyu+25); 
  
  
    TDate date;
    TTime time; 
    GetDateTime(&date,&time); 
    char *zs = malloc (150);
sprintf(zs, "%02i:%02i",time.hour,time.min);
int yu= 30; int xu= 30; int xuu= xu+102;
  DrwPngImg(FImage4, 0,24);
  DrwPngImg(FImage10, 4,3);
//========================================================  

 RAMNET *net_data;
char cl4[]={0xD1,0xDE,0xE7,0x64};
char cl2[]={0x91,0x9E,0xE7,0x64};
      net_data=RamNet();

if (((110-net_data->power)/2)> 0) DrawRoundedFrame(20,15,22,17,0,0,0,   ( ((net_data->ch_number)<255)?cl2:cl4 ),( ((net_data->ch_number)<255)?cl2:cl4) );
else DrawRoundedFrame(20,16,22,17,0,0,0,    colba24, colba24 );
if (((110-net_data->power)/2)> 5) DrawRoundedFrame(24,13,26,17,0,0,0,   ( ((net_data->ch_number)<255)?cl2:cl4 ),( ((net_data->ch_number)<255)?cl2:cl4) );
else DrawRoundedFrame(24,16,26,17,0,0,0,    colba24, colba24 );
if (((110-net_data->power)/2)> 10) DrawRoundedFrame(28,11,30,17,0,0,0,   ( ((net_data->ch_number)<255)?cl2:cl4 ),( ((net_data->ch_number)<255)?cl2:cl4) );
else DrawRoundedFrame(28,16,30,17,0,0,0,    colba24, colba24 );
if (((110-net_data->power)/2)> 15) DrawRoundedFrame(32,9,34,17,0,0,0,   ( ((net_data->ch_number)<255)?cl2:cl4 ),( ((net_data->ch_number)<255)?cl2:cl4) );
else DrawRoundedFrame(32,16,34,17,0,0,0,    colba24, colba24 );
if (((110-net_data->power)/2)> 20)DrawRoundedFrame(36,7,38,17,0,0,0,   ( ((net_data->ch_number)<255)?cl2:cl4 ),( ((net_data->ch_number)<255)?cl2:cl4) );
else DrawRoundedFrame(36,16,38,17,0,0,0,    colba24, colba24 );
if (((110-net_data->power)/2)> 25) DrawRoundedFrame(40,5,42,17,0,0,0,   ( ((net_data->ch_number)<255)?cl2:cl4 ),( ((net_data->ch_number)<255)?cl2:cl4) );
else DrawRoundedFrame(40,16,42,17,0,0,0,    colba24, colba24 );

  
  
  
  
  
//========================================================  
DrawRoundedFrame( 0,0,239,23, 0, 0, 0, co1ba2, co1ba2); 
DrawRoundedFrame( 213,7,229,14, 0, 0, 0,  GetPaletteAdrByColorIndex(23), GetPaletteAdrByColorIndex(1)); 
DrawRoundedFrame( 214,8,214+((14*battery)/100),13, 0, 0, 0,  GetPaletteAdrByColorIndex(4), GetPaletteAdrByColorIndex(4)); 
DrawRoundedFrame( 12,13,13,14, 0, 0, 0,  colba24, colba24);
DrawRoundedFrame( 12,14,13,16, 0, 0, 0,  colba23, colba23);
DrawRoundedFrame( 11,14,14,15, 0, 0, 0,  colba23, colba23);
DrawRoundedFrame( 116,10,125,16, 0, 0, 0,  colba23, colba23); 
if (zs[0] == '0') DrwPngImg(Dig0, xu, yu); 
if (zs[0] == '1') DrwPngImg(Dig1, xu+8, yu); 
if (zs[0] == '2') DrwPngImg(Dig2, xu, yu); 
if (zs[0] == '3') DrwPngImg(Dig3, xu, yu); 
if (zs[0] == '4') DrwPngImg(Dig4, xu, yu); 
if (zs[0] == '5') DrwPngImg(Dig5, xu, yu); 
if (zs[0] == '6') DrwPngImg(Dig6, xu, yu); 
if (zs[0] == '7') DrwPngImg(Dig7, xu+1, yu); 
if (zs[0] == '8') DrwPngImg(Dig8, xu+1, yu); 
if (zs[0] == '9') DrwPngImg(Dig9, xu, yu); 
if (zs[1] == '0') DrwPngImg(Dig0, xu+40, yu); 
if (zs[1] == '1') DrwPngImg(Dig1, xu+40+8, yu); 
if (zs[1] == '2') DrwPngImg(Dig2, xu+40, yu); 
if (zs[1] == '3') DrwPngImg(Dig3, xu+40, yu); 
if (zs[1] == '4') DrwPngImg(Dig4, xu+40, yu); 
if (zs[1] == '5') DrwPngImg(Dig5, xu+40, yu); 
if (zs[1] == '6') DrwPngImg(Dig6, xu+40, yu); 
if (zs[1] == '7') DrwPngImg(Dig7, xu+40+1, yu); 
if (zs[1] == '8') DrwPngImg(Dig8, xu+40+1, yu); 
if (zs[1] == '9') DrwPngImg(Dig9, xu+40, yu); 
DrwPngImg(Dig10, xu+84, yu); 
if (zs[3] == '0') DrwPngImg(Dig0, xuu, yu); 
if (zs[3] == '1') DrwPngImg(Dig1, xuu+8, yu); 
if (zs[3] == '2') DrwPngImg(Dig2, xuu, yu); 
if (zs[3] == '3') DrwPngImg(Dig3, xuu, yu); 
if (zs[3] == '4') DrwPngImg(Dig4, xuu, yu); 
if (zs[3] == '5') DrwPngImg(Dig5, xuu, yu); 
if (zs[3] == '6') DrwPngImg(Dig6, xuu, yu); 
if (zs[3] == '7') DrwPngImg(Dig7, xuu+1, yu); 
if (zs[3] == '8') DrwPngImg(Dig8, xuu+1, yu); 
if (zs[3] == '9') DrwPngImg(Dig9, xuu, yu); 
if (zs[4] == '0') DrwPngImg(Dig0, xuu+40, yu); 
if (zs[4] == '1') DrwPngImg(Dig1, xuu+40+8, yu); 
if (zs[4] == '2') DrwPngImg(Dig2, xuu+40, yu); 
if (zs[4] == '3') DrwPngImg(Dig3, xuu+40, yu); 
if (zs[4] == '4') DrwPngImg(Dig4, xuu+40, yu); 
if (zs[4] == '5') DrwPngImg(Dig5, xuu+40, yu); 
if (zs[4] == '6') DrwPngImg(Dig6, xuu+40, yu); 
if (zs[4] == '7') DrwPngImg(Dig7, xuu+40+1, yu); 
if (zs[4] == '8') DrwPngImg(Dig8, xuu+40+1, yu); 
if (zs[4] == '9') DrwPngImg(Dig9, xuu+40, yu);
WSHDR * ws = AllocWS( 124 );
  DrawRoundedFrame( 0,259,239,319, 0, 0, 0,  GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(1));
  DrwPngImg(FImage4, 0,zzy+260); 
  DrawRoundedFrame( 0,zzy+260,239,zzy+319, 0, 0, 0, co1ba, co1ba);
  DrwPngImg(FImage9, 10,zzy+270);  

  ascii2ws(ws, block);
  DrawString( ws,35,zzy+292,239,zzy+300, 8, 2, GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(23)); 
  DrawString( ws,30,zzy+284,239,zzy+300, 8, 2, colba23, GetPaletteAdrByColorIndex(23)); 
  FreeWS(ws);
 } 
    
if (state == 5) {        
  WSHDR * ws = AllocWS( 124 );
  DrawRoundedFrame( 0,259,239,319, 0, 0, 0,  GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(1));
  DrwPngImg(FImage4, 0,zzy+260); 
  DrawRoundedFrame( 0,zzy+260,239,zzy+319, 0, 0, 0, co1ba, co1ba);
  DrwPngImg(FImage9, 10,zzy+270);  

  ascii2ws(ws, block);
  DrawString( ws,35,zzy+292,239,zzy+300, 8, 2, GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(23)); 
  DrawString( ws,30,zzy+284,239,zzy+300, 8, 2, colba23, GetPaletteAdrByColorIndex(23)); 
  FreeWS(ws);
 if (bond) {
   if (Vniz==1) {GBS_DelTimer(&idle_timer); GBS_StartTimerProc(&idle_timer, 2, Mod4);}
   else {GBS_DelTimer(&idle_timer); GBS_StartTimerProc(&idle_timer, TMR_SECOND*4, Mod4);}}
 } 

  UnlockSched();
}
//==================================== НАЖАТИЕ КНОПОК ============================================================================

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  
  if ((msg->gbsmsg->msg==LONG_PRESS))// Если клавиша зажата
  {
      if (bond && state>3) {GBS_DelTimer(&sleep_timer); GBS_StartTimerProc(&sleep_timer, TMR_SECOND*5, TimeSleep);}
       SetIllumination(1,1,cur_keys,200);
  SetIllumination(0,1,cur_display,200);
   Illumination = 1;
     switch(msg->gbsmsg->submess)
      {        
      case '#':// Джой вниз
    sep = 0; return(2);
       
      default:
         if (Vniz==0 && zzy==0) {} else {Vniz=0; zzy=0; state = 5;}DirectRedrawGUI_ID (MAINGUI_ID);  return(0);
      

      }  
  }
  if ((msg->gbsmsg->msg==KEY_DOWN))// Если клавиша нажата
  {



    if (Illumination == 1){if (bond && state>3) {GBS_DelTimer(&sleep_timer); GBS_StartTimerProc(&sleep_timer, TMR_SECOND*5, TimeSleep);}
       SetIllumination(1,1,cur_keys,200);
  SetIllumination(0,1,cur_display,200);}
      switch(msg->gbsmsg->submess)
      {       
      case LEFT_SOFT: if (zzy<10){Touch = 1; if (bond && state>3) {GBS_DelTimer(&sleep_timer); GBS_StartTimerProc(&touch_timer, TMR_SECOND, TimeTouch);}};return(0); 
      case RIGHT_SOFT:  DirectRedrawGUI_ID (MAINGUI_ID); if (zzy<10){if (Touch) {sep = 0; return(2);}};return(0);  
      case '#': state = 4; return(0);
        case 13: state = 4; return(0);
        case 14: state = 4; return(0);
        case 21: state = 4; return(1);
        case 20: state = 4; return(1);        
        case 24:// Джой вниз
        return(2);  
      default:
        Touch = 0;   if (Vniz==0 && zzy==0) {Vniz=1;DirectRedrawGUI_ID (MAINGUI_ID);} else {if (Illumination == 1){Vniz=0; zzy=0; state = 5;DirectRedrawGUI_ID (MAINGUI_ID);}}  return(0);
      

      }  
  }
  return(0);
  }

//=======================================================================================


  int X_isfile (char *names){
int f;
unsigned int err;
 f = fopen(names, A_ReadOnly, P_READ, &err ); 
   fclose(f,&err); 
 if ( f==-1 ) return 0; 
 else return 1;

}



char *loadfile(char *filename);
//=======================================================================================
int main (char *exename, int *ght)
{
  
  if (ght) fore = *ght;
block = malloc (128);
  
  unsigned int err = 0;
if (!X_isfile ("0:\\Zbin\\etc\\iPhone_Saver2.ini") && !X_isfile ("4:\\Zbin\\etc\\iPhone_Saver2.ini")){cop=1;state = 1;}

if (X_isfile ("0:\\Zbin\\etc\\iPhone_Saver.ini")){unlink("0:\\Zbin\\etc\\iPhone_Saver.ini",0);}  
if (X_isfile ("4:\\Zbin\\etc\\iPhone_Saver.ini")){unlink("4:\\Zbin\\etc\\iPhone_Saver.ini",0);}

if (X_isfile ("0:\\Zbin\\etc\\iPhone_Saver2.ini")){block = loadfile("0:\\Zbin\\etc\\iPhone_Saver2.ini");}  
else if (X_isfile ("4:\\Zbin\\etc\\iPhone_Saver2.ini")){block = loadfile("4:\\Zbin\\etc\\iPhone_Saver2.ini");}
else strcpy ( block, "Разблокировать #");

if (isdir("0:\\Zbin\\etc", &err)) {if (!X_isfile ("0:\\Zbin\\etc\\iPhone_Saver2.ini")){savefile("0:\\Zbin\\etc\\iPhone_Saver2.ini", "Разблокировать #", 17);}}  
if (isdir("4:\\Zbin\\etc", &err)) {if (!X_isfile ("4:\\Zbin\\etc\\iPhone_Saver2.ini")){savefile("4:\\Zbin\\etc\\iPhone_Saver2.ini", "Разблокировать #", 17);}}  
  
  LockSched(); 
  char dummy[sizeof(MAIN_CSM)];
  
   MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);

  UpdateCSMname();
  
FImage1=read_pngimg(exclam_png);  
FImage2=read_pngimg(_file2_png);
FImage3=read_pngimg(left1_png);
FImage3b=read_pngimg(left2_png);
FImage4=read_pngimg(fon1_png);
FImage5=read_pngimg(right1_png);
FImage5b=read_pngimg(right2_png);
FImage6=read_pngimg(center1_png);
FImage6b=read_pngimg(center3_png);
FImage7=read_pngimg(line_png);
FImage7b=read_pngimg(line2_png);
FImage8=read_pngimg(ree2_png);
FImage9=read_pngimg(slide_png);
FImage10=read_pngimg(iconbar2_png);




Dig0 = CreateImgr(40, 55); drawimg2img( FImage8,Dig0, 0, 0, 0, 0,39, 55);
Dig1 = CreateImgr(40, 55); drawimg2img( FImage8,Dig1, 0, 0, 40, 0,23, 55); 
Dig2 = CreateImgr(40, 55); drawimg2img(FImage8,Dig2,  0, 0, 66, 0,37, 55); 
Dig3 = CreateImgr(40, 55); drawimg2img( FImage8, Dig3,0, 0, 102, 0,39, 55); 
Dig4 = CreateImgr(40, 55); drawimg2img( FImage8, Dig4,0, 0, 141, 0,39, 55);
Dig5 = CreateImgr(40, 55); drawimg2img( FImage8, Dig5,0, 0, 180, 0,39, 55);
Dig6 = CreateImgr(40, 55); drawimg2img(FImage8, Dig6, 0, 0, 219, 0,39, 55);
Dig7 = CreateImgr(40, 55); drawimg2img(FImage8,Dig7,  0, 0, 258, 0,38, 55);
Dig8 = CreateImgr(40, 55); drawimg2img(FImage8,Dig8,  0, 0, 297, 0,38, 55); 
Dig9 = CreateImgr(40, 55); drawimg2img(FImage8,Dig9,  0, 0, 335, 0,39, 55);
Dig10 = CreateImgr(40, 55); drawimg2img(FImage8,Dig10,  0, 0, 379, 0,13, 55);
   if  (strlen (FImage8->bitmap)>0) mfree(FImage8->bitmap);  
      if (FImage8) mfree(FImage8);
  UnlockSched();
  if (bond) {GBS_DelTimer(&time_timer); GBS_StartTimerProc(&time_timer, TMR_SECOND/3, TimeZone);}
  return 0;
}
