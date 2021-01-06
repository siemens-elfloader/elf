#include "..\inc\swilib.h"
#include "rect_patcher.h"
//nclude "../inc/cfg_items.h"
#include "conf_loader.h"


//-----------------------------------------------------//
//Эт стремные переменные,но они нужны в любом проекте :)
const int minus11=-11;
unsigned short maincsm_name_body[140];

unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
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

//Объявляем переменные из конфига
extern void InitConfig();

//----------------------------------//

//GBSTMR timer;


#ifndef ELKA
#define W 133
#define H 177
#define FONT_SM 7
#define FONT_MD 5
#define FONT_LG 4
#else
#define W 240
#define H 320
#define FONT_SM 8
#define FONT_MD 7
#define FONT_LG 5
#endif


extern const char CFG_menu_frbgcolor[]; //цвет огранки фона меню
extern const char CFG_menu_bgcolor[]; //цвет фона меню
extern const char CFG_menu_fontcolor[]; //цвет шрифта меню
extern const char CFG_menu_curcolor[]; //цвет курсора в меню
extern const unsigned int CFG_menu_font; //шрифт меню
extern const unsigned int CFG_menu_rounded; //коэффициент скругливания краев фона
extern const unsigned int CFG_menu_currounded; //коэффициент скругливания краев фона
extern const unsigned int CFG_menu_curspeed; //скорость движения курсора


extern const char CFG_edit_bgcolor[];
extern const char CFG_edit_cur_bgcolor[];
extern const char CFG_edit_cur_frcolor[];
extern const unsigned int CFG_edit_curround;

extern const char CFG_edit_panel_bgcolor[];
extern const char CFG_edit_panel_frcolor[];
extern const unsigned int CFG_edit_panel_xc;
extern const unsigned int CFG_edit_panel_offset;
extern const unsigned int CFG_edit_panel_drawcount;

extern const unsigned int CFG_edit_scaleW;
extern const unsigned int CFG_edit_scaleH;

extern const char CFG_edit_comment_color[];
extern const unsigned int CFG_edit_comment_font;

extern const unsigned int CFG_edit_font;

const char perc_s[]="%s";
const char perc_d[]="%d";
const char perc_t[]="%t";




int ShowAbout=0;
int menu_active=0;
char ShowEdit=0;


char *menu_items[]= 
{
  "создать новый",
  "параметры уровня",
  "сохранить",
  ">dump map",
  "настройки",
  "о программе",
  "выход"
};
#define NUM_MENU_ITEMS 7

#define FONT_SDVIG_X 5
#define FONT_SDVIG_Y 4
char cur_pos = 0;

void DrawMenu()
{
  WSHDR *ws=AllocWS(128);
  short line_h = GetFontYSIZE(CFG_menu_font)-FONT_SDVIG_Y;
  short menu_ypos=ScreenH()-line_h*NUM_MENU_ITEMS; //игрек позиция для меню
  short sdvig_y=menu_ypos;
  
  wsprintf(ws,perc_t,menu_items[1]);
  short max_width = Get_WS_width(ws,CFG_menu_font);
  
  //фон
  DrawRoundedFrame(0,menu_ypos-FONT_SDVIG_Y,max_width+(FONT_SDVIG_X*2),ScreenH(),CFG_menu_rounded,CFG_menu_rounded,0,CFG_menu_frbgcolor,CFG_menu_bgcolor);
  //курсор
  DrawRoundedFrame(FONT_SDVIG_X-2,menu_ypos+(line_h*cur_pos)-2,max_width+FONT_SDVIG_X+2,menu_ypos+(line_h*cur_pos)+line_h,CFG_menu_currounded,CFG_menu_currounded,0,NULL,CFG_menu_curcolor);
  
  for(int i=0;i<NUM_MENU_ITEMS;i++)
  {
   wsprintf(ws,perc_t,menu_items[i]);
   DrawString(ws,FONT_SDVIG_X,sdvig_y-FONT_SDVIG_Y,Get_WS_width(ws,CFG_menu_font)+FONT_SDVIG_X,ScreenH(),CFG_menu_font,TEXT_ALIGNLEFT,CFG_menu_fontcolor,NULL);
   sdvig_y+=GetFontYSIZE(CFG_menu_font)-FONT_SDVIG_Y; 
  }
  
  FreeWS(ws);
  //if(menu_active) GBS_StartTimerProc(&timer,9,DrawMenu);
  //else GBS_DelTimer(&timer);
}

void About()
{
  char bgcol[4]={70,70,70,90};
  char frbgcol[4]={0,0,100,100};
  char fontcol[4]={0,170,10,100};
  int height=ScreenH()/2;
  WSHDR *ws=AllocWS(512);
  
  DrawRoundedFrame(0,height-(height/2),ScreenW(),height+(height/2),0,0,1,frbgcol,bgcol);
  wsprintf(ws,perc_t,"мапосоздавалко версии 0.3\n для Арканойда версии 1.3\n(c)Half65");
  DrawString(ws,3,(height-(height/2)-3),ScreenW(),(height+(height/2)+3),CFG_menu_font,TEXT_ALIGNMIDDLE,fontcol,NULL);
  wsprintf(ws,perc_t,"\nвсе баги и пожелания в 404558107");
  DrawString(ws,3,height,ScreenW(),(height+(height/2)+3),CFG_menu_font,TEXT_ALIGNMIDDLE,fontcol,NULL);
  FreeWS(ws);
}



char *pwd;
WSHDR *e_ws;

typedef unsigned char trigger;


int fopen(const char * filename, unsigned int fileflags, unsigned int filemode, unsigned int *errornumber)
{
  char *realpath=malloc(512);
  sprintf(realpath,"%s%s",pwd,filename);
  int f=fopenA(realpath,fileflags,filemode,errornumber);
  mfree(realpath);
  return(f);
}


#define NO_LOG

TDate date; TTime time;
#ifndef NO_LOG
void Tlog (char *string)
{
  int logfile=fopen("ArcanoidMapMaker_0.4.log",A_ReadWrite+A_TXT+A_Append+A_Create,P_READ+P_WRITE,0);
  char *data=malloc(4096);
  GetDateTime(&date,&time); 
  sprintf(data,">%d:%02d:%02d/%02d-%02d-%04d< >kernel<   %s\n",time.hour,time.min,time.sec,date.day, date.month,date.year,string);
  lseek(logfile, 0x0, S_END, 0, 0);
  fwrite(logfile,data,strlen(data),0);
  mfree(data);
  fclose(logfile,0);
}
#else 
void Tlog (char *string){}
#endif
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  //SetColor(&drwobj, (char*)pen, (char*)brush);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

IMGHDR *bricks[10];
IMGHDR *big_bricks[30]; //включает все брики кроме бонусных,вместо них рисуются сами бонусы
//1,2,3 = normal bricks;
//4 = double collised brick;
//5 = thirst collised brick;
//6 = undestroyed brick;
//7 = bonus brick;




//8 = teleport brick; не юзается пока
//9 = mine brick; не юзается пока



//20 = bonus bigest user
//21 = bonus smallest user
//22 = bonus заморозка биты на 3 сек
//23 = bonus ускорение шара на 1
//24 = bonus замедление шара на 1
//25 = bonus +1 жизнь



//26 = bonus супер шар,летит почти через все :)
//27 = bonus шар летит почти через все,но ничего не бьет
//28 = bonus стреляем пульками
//29 = bonus стреляем ракетницей
//30 = bonus прилипалка на 30 сек
//31 = bonus страховка на 30 сек
//32 = bonus увеличение шара
//33 = bonus уменьшение шара
//34 = bonus неизвестный
//35 = bonus +100 очков пока не юзается


#define MAX_LEVELS 60
#define MAX_WIDTH 15
#define MAX_HEIGHT 32

char used_level[MAX_HEIGHT][MAX_WIDTH];

typedef struct
{
  char sign[4];
  char version[4]; //new
  char bg_num; //номер фона для текущего уровня
  char snd_num; //номер песни
  char type; //0=normal;1=boss.
  char boss_diff; //new
  char boss_lives;
}MAP;
MAP map;

char lgn[128];

char num_to_save;


void ZeroLevel()
{
  map.sign[0] = 'A';
  map.sign[1] = 'D';
  map.sign[2] = 'M';
  map.sign[3] = 0x00;
  
  map.version[0] = '0';
  map.version[1] = '0';
  map.version[2] = '4';
  map.version[3] = 0x00;
  
  map.bg_num = 0;
  map.snd_num = 0;
  map.type = 0;
  map.boss_diff = 0;
  map.boss_lives = 0;
  num_to_save = 1;
  
  for(int y=0;y<MAX_HEIGHT;y++)
  {
    for(int x=0;x<MAX_WIDTH;x++)
    {
      used_level[y][x]=0;
    }
  }
}




const char *comments[]= 
{
  "нормальный кирпичик",
  "2 попадания",
  "3 попадания",
  "неразбиваемый кирпичик",
  "кирпичик-телепорт",
  "кирпичик-мина",
  "увеличалка платформы",
  "уменьшалка платформы",
  "заморозка юзера",
  "ускорение мяча",
  "замедление мяча",
  "+1 жизнь!",
  "супер мячик",
  "мяч-привидение",
  "стреляем пульками",
  "стреляем рокетом",
  "прилипалка",
  "страховка",
  "увеличение шара",
  "уменьшение шара",
  "неизвестный бонус",
  "+100 очков",
  "<пусто типа>"
};
WSHDR *comment_buffer;
char cmt[128];



static void OnRedraw(MAIN_GUI *data) {}


int cur_ypos = 6;
int cur_xpos;

int p_pos;
int p_counter;


int offset1;




void DrawEditor()
{
  int bx=0;
  int by=0;
  for(int y=0;y<MAX_HEIGHT;y++)
  {
    for(int x=0;x<MAX_WIDTH;x++)
    {
      char num = used_level[y][x];
      if(num>0)
      {
        if(num<9)
        {
          by=bricks[num-1]->h*y;
          bx=bricks[num-1]->w*x;
          DrwImg(bricks[num-1],bx,by,NULL,NULL);
        }
        else if(num>=20)
        {
          by=bricks[8]->h*y;
          bx=bricks[8]->w*x;
          DrwImg(bricks[8],bx,by,NULL,NULL);
        }
      }
    }
  }
  
  //типа курсор рисуем
  by=bricks[0]->h*cur_ypos;
  bx=bricks[0]->w*cur_xpos;
  DrawRoundedFrame(bx,by,bx+bricks[0]->w-1,by+bricks[0]->h-1,CFG_edit_curround,CFG_edit_curround,0,CFG_edit_cur_frcolor,CFG_edit_cur_bgcolor);
  
  DrawRoundedFrame(0,(bricks[0]->h*MAX_HEIGHT)+1,ScreenW()-1,ScreenH()-1,0,0,0,CFG_edit_panel_frcolor,CFG_edit_panel_bgcolor); //панель внизу
  
  //пишем коммент к элементу под курсором
  WSHDR *ws = AllocWS(128);
  wsprintf(ws,"map[%d]\n%t[%d]",num_to_save,cmt,used_level[cur_ypos][cur_xpos]);
  DrawString(ws,0,(bricks[0]->h*MAX_HEIGHT)+1+3,ScreenW(),(bricks[0]->h*MAX_HEIGHT)+3+(GetFontYSIZE(CFG_edit_comment_font)*2),CFG_edit_comment_font,TEXT_ALIGNMIDDLE,CFG_edit_comment_color,NULL);
  FreeWS(ws);
  
  int offset = (bricks[0]->h*MAX_HEIGHT)+1+3+(GetFontYSIZE(CFG_edit_comment_font)*2);
  //расчитываем...
  by=offset+((ScreenH()-offset)/2) - (big_bricks[0]->h/2);
  
  
  for(int i=0;i<CFG_edit_panel_drawcount;i++)
  {
    bx=CFG_edit_panel_xc+((big_bricks[0]->w+CFG_edit_panel_offset)*i);
    DrwImg(big_bricks[i+p_counter],bx,by,NULL,NULL);
  }
  //еще один курсор,который на нижней панельке ходит :)
  DrawRoundedFrame(CFG_edit_panel_xc+((big_bricks[0]->w+CFG_edit_panel_offset)*p_pos),by,CFG_edit_panel_xc+((big_bricks[0]->w+CFG_edit_panel_offset)*p_pos+big_bricks[0]->w-1),by+big_bricks[0]->h-1,0,0,0,CFG_edit_cur_frcolor,CFG_edit_cur_bgcolor);
  
  
  /*WSHDR *ws = AllocWS(64);
  const char fontcol[4]={0,175,0,100};
  wsprintf(ws,"pos=%d\ncounter=%d",p_pos,p_counter);
  DrawString(ws,10,ScreenH()/2,ScreenW(),ScreenH()/2+50,CFG_menu_font,TEXT_ALIGNMIDDLE,fontcol,NULL);
  FreeWS(ws);*/
}






void CheckComments()
{
  switch(used_level[cur_ypos][cur_xpos])
  {
    /*case 0:{wsprintf(comment_buffer,perc_t,comments[21]);break;}
    case 1:{wsprintf(comment_buffer,perc_t,comments[0]);break;}
    case 2:{wsprintf(comment_buffer,perc_t,comments[0]);break;}
    case 3:{wsprintf(comment_buffer,perc_t,comments[0]);break;}
    case 4:{wsprintf(comment_buffer,perc_t,comments[21]);break;}
    case 5:{wsprintf(comment_buffer,perc_t,comments[1]);break;}
    case 6:{wsprintf(comment_buffer,perc_t,comments[2]);break;}
    case 7:{wsprintf(comment_buffer,perc_t,comments[3]);break;}
    case 8:{wsprintf(comment_buffer,perc_t,comments[4]);break;}
    case 9:{wsprintf(comment_buffer,perc_t,comments[5]);break;}
    case 20:{wsprintf(comment_buffer,perc_t,comments[6]);break;}
    case 21:{wsprintf(comment_buffer,perc_t,comments[7]);break;}
    case 22:{wsprintf(comment_buffer,perc_t,comments[8]);break;}
    case 23:{wsprintf(comment_buffer,perc_t,comments[9]);break;}
    case 24:{wsprintf(comment_buffer,perc_t,comments[10]);break;}
    case 25:{wsprintf(comment_buffer,perc_t,comments[11]);break;}
    case 26:{wsprintf(comment_buffer,perc_t,comments[12]);break;}
    case 27:{wsprintf(comment_buffer,perc_t,comments[13]);break;}
    case 28:{wsprintf(comment_buffer,perc_t,comments[14]);break;}
    case 29:{wsprintf(comment_buffer,perc_t,comments[15]);break;}
    case 30:{wsprintf(comment_buffer,perc_t,comments[16]);break;}
    case 31:{wsprintf(comment_buffer,perc_t,comments[17]);break;}
    case 32:{wsprintf(comment_buffer,perc_t,comments[18]);break;}
    case 33:{wsprintf(comment_buffer,perc_t,comments[19]);break;}
    case 34:{wsprintf(comment_buffer,perc_t,comments[20]);break;}
    case 35:{wsprintf(comment_buffer,perc_t,comments[21]);break;}*/
    case 0:{strcpy(cmt,"<типа пусто>");break;}
    case 1:case 2:case 3:{strcpy(cmt,"обычный кирпичик");break;}
    case 4:{strcpy(cmt,"2 попадания");break;}
    case 5:{strcpy(cmt,"3 попадания");break;}
    case 6:{strcpy(cmt,"стенка");break;}
    case 7:{strcpy(cmt,"мина");break;}
    case 8:{strcpy(cmt,"телепорт");break;}
    case 20:{strcpy(cmt,"увеличение платформы");break;}
    case 21:{strcpy(cmt,"уменьшение платформы");break;}
    case 22:{strcpy(cmt,"заморозка юзера");break;}
    case 23:{strcpy(cmt,"ускорение мяча");break;}
    case 24:{strcpy(cmt,"замедление мяча");break;}
    case 25:{strcpy(cmt,"+1 жизнь!");break;}
    case 26:{strcpy(cmt,"крутой мячик");break;}
    case 27:{strcpy(cmt,"мяч-привидение");break;}
    case 28:{strcpy(cmt,"стреляем пульками");break;}
    case 29:{strcpy(cmt,"стреляем рокетом");break;}
    case 30:{strcpy(cmt,"прилипалка");break;}
    case 31:{strcpy(cmt,"страховка");break;}
    case 32:{strcpy(cmt,"увеличение шара");break;}
    case 33:{strcpy(cmt,"уменьшение шара");break;}
    case 34:{strcpy(cmt,"случайный бонус");break;}
    case 35:{strcpy(cmt,"+100 очков");break;}
    default:{strcpy(cmt,"unknown error 1");break;}
  }
}




char edit_cur=0;

void EditLevel()
{
  short height = (bricks[0]->h*MAX_HEIGHT)+3; //конец рисования по высоте
#define EDIT_START_XPOS 0
#define EDIT_START_YPOS 20
  char bg_col[4]={0,0,0,100};
  char font_col[4]={0,180,0,100};
  char cur_frcol[4]={0,180,180,100};
  char cur_bgcol[4]={90,90,80,100};
  WSHDR *ws = AllocWS(64);
  short fontH = GetFontYSIZE(CFG_edit_font)+3;
  short sdvig = fontH+13;
  
  
  DrawRoundedFrame(0,0,ScreenW()-1,height,0,0,0,NULL,bg_col); //фон
  
  DrawRoundedFrame(0,EDIT_START_YPOS+(edit_cur*sdvig)-1,ScreenW()-1,EDIT_START_YPOS+(edit_cur*sdvig)+fontH+1,0,0,0,cur_frcol,cur_bgcol); //курсор
  
  wsprintf(ws,"%t:%d","номер уровня",num_to_save);
  DrawString(ws,EDIT_START_XPOS,EDIT_START_YPOS+(sdvig*0),ScreenW(),EDIT_START_YPOS+(sdvig*0)+fontH,CFG_edit_font,TEXT_ALIGNMIDDLE,font_col,NULL);
  
  wsprintf(ws,"%t:%d","номер фона",map.bg_num);
  DrawString(ws,EDIT_START_XPOS,EDIT_START_YPOS+(sdvig*1),ScreenW(),EDIT_START_YPOS+(sdvig*1)+fontH,CFG_edit_font,TEXT_ALIGNMIDDLE,font_col,NULL);
  
  if(map.type==0) wsprintf(ws,perc_t,"тип уровня: обычный");
  if(map.type==1) wsprintf(ws,perc_t,"тип уровня: уровень-босс");
  DrawString(ws,EDIT_START_XPOS,EDIT_START_YPOS+(sdvig*2),ScreenW(),EDIT_START_YPOS+(sdvig*2)+fontH,CFG_edit_font,TEXT_ALIGNMIDDLE,font_col,NULL);
  
  if(map.boss_diff==0) wsprintf(ws,perc_t,"сложность босса: очень легко");
  if(map.boss_diff==1) wsprintf(ws,perc_t,"сложность босса: легко");
  if(map.boss_diff==2) wsprintf(ws,perc_t,"сложность босса: нормально");
  if(map.boss_diff==3) wsprintf(ws,perc_t,"сложность босса: сложно");
  if(map.boss_diff==4) wsprintf(ws,perc_t,"сложность босса: очень сложно");
  DrawString(ws,EDIT_START_XPOS,EDIT_START_YPOS+(sdvig*3),ScreenW(),EDIT_START_YPOS+(sdvig*3)+fontH,CFG_edit_font,TEXT_ALIGNMIDDLE,font_col,NULL);
  
  wsprintf(ws,"%t:%d","номер мелодии",map.snd_num);
  DrawString(ws,EDIT_START_XPOS,EDIT_START_YPOS+(sdvig*4),ScreenW(),EDIT_START_YPOS+(sdvig*4)+fontH,CFG_edit_font,TEXT_ALIGNMIDDLE,font_col,NULL);
  
  
  //wsprintf(ws,perc_t,"назад");
  //DrawString(ws,0,height-fontH,ScreenW()/2,height,CFG_edit_font,TEXT_ALIGNLEFT,font_col,NULL);
  wsprintf(ws,perc_t,"назад");
  DrawString(ws,ScreenW()-Get_WS_width(ws,CFG_edit_font)-3,height-fontH,ScreenW(),height,CFG_edit_font,TEXT_ALIGNRIGHT,font_col,NULL);
  
  
  FreeWS(ws);
}




void RedrawScreen()
{
  DrawRoundedFrame(0,0,ScreenW()-1,ScreenH()-1,0,0,0,NULL,CFG_edit_bgcolor);
  
  CheckComments();
  DrawEditor();
  
  if(ShowAbout)   About();
  if(ShowEdit)    EditLevel();
  if(menu_active) DrawMenu();
}




void SaveMap()
{
  Tlog("start saveMap...");
  
  int f;
  char *temp = malloc(512);
  sprintf(temp,"maps\\level%d.adm",num_to_save);
  sprintf(lgn,"SaveMap-%s",temp);Tlog(lgn);
  if((f=fopen(temp,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,0))==-1) {ShowMSG(1,(int)"error while writing!");return;}
  
  mfree(temp);
  
  map.sign[0] = 'A';
  map.sign[1] = 'D';
  map.sign[2] = 'M';
  map.sign[3] = 0x00;
  fwrite(f,&map.sign,4,0);
  
  map.version[0] = '0';
  map.version[1] = '0';
  map.version[2] = '4';
  map.version[3] = 0x00;
  fwrite(f,&map.version,4,0);
  
  fwrite(f,&map.bg_num,1,0);
  fwrite(f,&map.snd_num,1,0);
  fwrite(f,&map.type,1,0);
  fwrite(f,&map.boss_diff,1,0);
  
  for(int y=0;y<MAX_HEIGHT;y++)
  {
    for(int x=0;x<MAX_WIDTH;x++)
    {
      fwrite(f,&used_level[y][x],1,0);
    }
  }
  
  fclose(f,0);
  ShowMSG(1,(int)"мапа сохранена");
}



void DumpMap()
{
  char *temp = malloc(256);
  sprintf(temp,"%smaps\\level%d.log",pwd,num_to_save);
  int file = fopenA(temp,A_WriteOnly+A_BIN+A_Create,P_WRITE,0);
  
  for(int y=0;y<MAX_HEIGHT;y++)
  {
    sprintf(temp,perc_s,"{");
    fwrite(file,temp,1,0);
    for(int x=0;x<MAX_WIDTH;x++)
    {
      sprintf(temp,"%d,",used_level[y][x]);
      fwrite(file,temp,strlen(temp),0);
    }
    sprintf(temp,perc_s,"}");
    fwrite(file,temp,1,0);
    temp[0]=0x0D;
    fwrite(file,&temp[0],1,0);
  }
  
  fclose(file,0);
  mfree(temp);
}




static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))//Тут делаем что либо при создании гуи
{
#ifdef ELKA//Если елка,то отключаем иконбар
  DisableIconBar(1);
#endif
  data->ws1=AllocWS(256);//Выделяем память под строку
  data->gui.state=1;
}








void FreeImages()
{
  for(int i=0;i<8;i++)
  {
    if(bricks[i] && bricks[i]->bitmap)
    {
      mfree(bricks[i]->bitmap);
      mfree(bricks[i]);
    }
  }
  Tlog("bricks free");
  for(int i1=0;i1<23;i1++)
  {
    if(big_bricks[i1] && big_bricks[i1]->bitmap)
    {
      //sprintf(lgn,"free[%d]...",i1);Tlog(lgn);
      mfree(big_bricks[i1]->bitmap);
      mfree(big_bricks[i1]);
    }
  }
  
}

static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))//Сдесь делаем что нить при закрытии гуи:)
{
  FreeWS(e_ws);
  FreeImages();
  
  data->gui.state=0;
  FreeWS(data->ws1);//например, освобождаем память
}

static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Если гуи на верху то опять же делаем что нужно
{
  //GBS_StartTimerProc(&timer,20,RedrawScreen);
  data->gui.state=2;
  DisableIDLETMR();//отключаем таймер,иначе через 2 минуты эльф закроется
}

static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))//а если гуи не вверху,то можно закрыть эльф например:)
{
  //GBS_DelTimer(&timer);
  if (data->gui.state!=2) return;
  data->gui.state=1;
}





int openconf()
{
  WSHDR *fws=AllocWS(256);
  extern const char *successed_config_filename;
  wsprintf(fws,perc_t,successed_config_filename);
  ExecuteFile(fws,NULL,NULL);
  FreeWS(fws);
  return 0;
}


//extern void CreateTextEditDialog(int type,char *src,int maxlen);

void RenameLevel()
{
  //CreateTextEditDialog(1,map.name,64); //просто создаем диалог
}

void NewLevel() //сперва создаем диалог,а потом прочие параметры
{
  ZeroLevel();
  //CreateTextEditDialog(0,"New Level",64);
}




int MenuKeyhook(GUI_MSG *msg)
{
  if(msg->gbsmsg->msg==KEY_DOWN)
  {
     if(msg->gbsmsg->submess==LEFT_SOFT) {menu_active=0;Tlog("menu disable");RedrawScreen();return 0;}
    
      if((msg->gbsmsg->submess==DOWN_BUTTON || msg->gbsmsg->submess=='8') && cur_pos<NUM_MENU_ITEMS-1) {cur_pos+=1;RedrawScreen();return 0;}
      if((msg->gbsmsg->submess==UP_BUTTON || msg->gbsmsg->submess=='2') && cur_pos>0) {cur_pos-=1;RedrawScreen();return 0;}
      
      if((msg->gbsmsg->submess==ENTER_BUTTON || msg->gbsmsg->submess=='5' || msg->gbsmsg->submess==RIGHT_BUTTON) && cur_pos==0) {menu_active=0;NewLevel();RedrawScreen();return 0;}
      if((msg->gbsmsg->submess==ENTER_BUTTON || msg->gbsmsg->submess=='5' || msg->gbsmsg->submess==RIGHT_BUTTON) && cur_pos==1) {menu_active=0;ShowEdit=1;RedrawScreen();return 0;}
      if((msg->gbsmsg->submess==ENTER_BUTTON || msg->gbsmsg->submess=='5' || msg->gbsmsg->submess==RIGHT_BUTTON) && cur_pos==2) {menu_active=0;SaveMap();RedrawScreen();return 0;}
      if((msg->gbsmsg->submess==ENTER_BUTTON || msg->gbsmsg->submess=='5' || msg->gbsmsg->submess==RIGHT_BUTTON) && cur_pos==3) {menu_active=0;DumpMap();return 0;}
      if((msg->gbsmsg->submess==ENTER_BUTTON || msg->gbsmsg->submess=='5' || msg->gbsmsg->submess==RIGHT_BUTTON) && cur_pos==4) {menu_active=0;openconf();return 0;}
      if((msg->gbsmsg->submess==ENTER_BUTTON || msg->gbsmsg->submess=='5' || msg->gbsmsg->submess==RIGHT_BUTTON) && cur_pos==5) {menu_active=0;ShowAbout=1;RedrawScreen();return 0;}
      if((msg->gbsmsg->submess==ENTER_BUTTON || msg->gbsmsg->submess=='5' || msg->gbsmsg->submess==RIGHT_BUTTON) && cur_pos==6) {return 1;} //exit
  }
  return(0);
}



int EditKeyhook(GUI_MSG *msg)
{
  if(msg->gbsmsg->msg==KEY_DOWN)
  {
     if(msg->gbsmsg->submess==RIGHT_SOFT) {ShowEdit=0;RedrawScreen();return 0;}
     if((msg->gbsmsg->submess==DOWN_BUTTON || msg->gbsmsg->submess=='8') && edit_cur<4) {edit_cur++;RedrawScreen();return 0;}
     if((msg->gbsmsg->submess==UP_BUTTON   || msg->gbsmsg->submess=='2') && edit_cur>0) {edit_cur--;RedrawScreen();return 0;}  
     
     if(msg->gbsmsg->submess==RIGHT_BUTTON && edit_cur==0 && num_to_save<250) {num_to_save++;RedrawScreen();return 0;}
     if(msg->gbsmsg->submess==LEFT_BUTTON && edit_cur==0 && num_to_save>1) {num_to_save--;RedrawScreen();return 0;}
     if(msg->gbsmsg->submess==RIGHT_BUTTON && edit_cur==1 && map.bg_num<250) {map.bg_num++;RedrawScreen();return 0;}
     if(msg->gbsmsg->submess==LEFT_BUTTON && edit_cur==1 && map.bg_num>0) {map.bg_num--;RedrawScreen();return 0;}
     if(msg->gbsmsg->submess==RIGHT_BUTTON && edit_cur==2) {map.type=1;RedrawScreen();return 0;}
     if(msg->gbsmsg->submess==LEFT_BUTTON && edit_cur==2) {map.type=0;RedrawScreen();return 0;}
     if(msg->gbsmsg->submess==RIGHT_BUTTON && edit_cur==3 && map.boss_diff<4) {map.boss_diff++;RedrawScreen();return 0;}
     if(msg->gbsmsg->submess==LEFT_BUTTON && edit_cur==3 && map.boss_diff>0) {map.boss_diff--;RedrawScreen();return 0;}
     if(msg->gbsmsg->submess==RIGHT_BUTTON && edit_cur==4 && map.snd_num<250) {map.snd_num++;RedrawScreen();return 0;}
     if(msg->gbsmsg->submess==LEFT_BUTTON && edit_cur==4 && map.snd_num>0) {map.snd_num--;RedrawScreen();return 0;}
     
     
  }
  return 0;
}




void PanelCursorLeft()
{
  if(CFG_edit_panel_xc+(big_bricks[0]->w*p_pos) > 0+big_bricks[0]->w-1 && p_pos+p_counter>0) p_pos--;
  //else if(p_pos+p_counter>1) p_counter++;
}
void PanelCursorRight()
{
  if(CFG_edit_panel_xc+(big_bricks[0]->w*p_pos) < ScreenW()-((big_bricks[0]->w-1)*2) && p_pos+p_counter<24) p_pos++;
  //else if(p_pos+p_counter<8) p_counter++;
}



#define PS (p_pos+p_counter)


void FillLevelByPos()
{
  char dest;
  if(PS<8) dest=PS+1;
  else dest=PS+12;
  /*else switch(PS)
  {
    case 9: {dest = 20;break;} //bigest user
    case 10: {dest = 21;break;} //smallest user
    case 11: {dest = 22;break;} //freeze
    case 11: {dest = 23;break;} //speedy
    case 12: {dest = 24;break;} //slowly
    case 13: {dest = 25;break;} //live++
    case 14: {dest = 26;break;} //super ball
    case 15: {dest = 27;break;} //nightmare-ball
    case 16: {dest = 28;break;} //shells1
    case 17: {dest = 29;break;} //rockets
    case 18: {dest = 30;break;} //prilipalka
    case 19: {dest = 31;break;} //защита
    case 20: {dest = 32;break;} //увеличение мяча
    case 21: {dest = 33;break;} //уменьшение мяча
    case 22: {dest = 34;break;} //неизвестный бонус
    case 23: {dest = 35;break;} //+100 points
  }*/
  used_level[cur_ypos][cur_xpos] = dest;
}


char sp_type; //0-right;1-left;2-up;3-down
int sp_count;
int sp_utime;
int sp_time;
GBSTMR sptimer;


void MoveCursor()
{
  if(sp_type==0 && cur_xpos<14) cur_xpos++;
  if(sp_type==1 && cur_xpos>0) cur_xpos--;
  if(sp_type==2 ) 
  {
   if(cur_ypos>3) cur_ypos--;
  }
  if(sp_type==3 && cur_ypos<31) cur_ypos++;
  
  sp_utime++;
  if(sp_utime<sp_time) GBS_StartTimerProc(&sptimer,sp_count,MoveCursor);
  else {sp_utime=0;GBS_StopTimer(&sptimer);GBS_DelTimer(&sptimer);RedrawScreen();return;}
}


void StartSpeedCursor(char type,int count,int time)
{
  sp_type = type;
  sp_count = count;
  sp_time = time;
  MoveCursor();
}

extern const unsigned int CFG_cur_count;
extern const unsigned int CFG_cur_time;

void NavCursor(GUI_MSG *msg)
{
  if(msg->gbsmsg->msg==KEY_DOWN)
  {
    if((msg->gbsmsg->submess==RIGHT_BUTTON || msg->gbsmsg->submess=='6') && cur_xpos<14) {cur_xpos++;RedrawScreen();return;}
    if((msg->gbsmsg->submess==LEFT_BUTTON || msg->gbsmsg->submess=='4') && cur_xpos>0) {cur_xpos--;RedrawScreen();return;}
    if((msg->gbsmsg->submess==DOWN_BUTTON || msg->gbsmsg->submess=='8') && cur_ypos<31) {cur_ypos++;RedrawScreen();return;}
    if((msg->gbsmsg->submess==UP_BUTTON || msg->gbsmsg->submess=='2')) 
    {
      if(cur_ypos>3) cur_ypos--;
      RedrawScreen();return;
    }
  }
  if(msg->gbsmsg->msg==LONG_PRESS)
  {
    if(msg->gbsmsg->submess==RIGHT_BUTTON || msg->gbsmsg->submess=='6') {StartSpeedCursor(0,CFG_cur_count,CFG_cur_time);RedrawScreen();return;}
    if(msg->gbsmsg->submess==LEFT_BUTTON || msg->gbsmsg->submess=='4') {StartSpeedCursor(1,CFG_cur_count,CFG_cur_time);RedrawScreen();return;}
    if(msg->gbsmsg->submess==DOWN_BUTTON || msg->gbsmsg->submess=='8') {StartSpeedCursor(3,CFG_cur_count,CFG_cur_time);RedrawScreen();return;}
    if(msg->gbsmsg->submess==UP_BUTTON || msg->gbsmsg->submess=='2') {StartSpeedCursor(2,CFG_cur_count,CFG_cur_time);RedrawScreen();return;}
  }
  
}


static int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  
  if(menu_active) return(MenuKeyhook(msg));
  if(ShowEdit) return(EditKeyhook(msg));
  
  NavCursor(msg);
  
  if(msg->gbsmsg->msg==KEY_DOWN)
  {
    if((msg->gbsmsg->submess==ENTER_BUTTON || msg->gbsmsg->submess=='5' || msg->gbsmsg->submess==RIGHT_BUTTON) && ShowAbout) {ShowAbout=0;RedrawScreen();return 0;}
    if(msg->gbsmsg->submess==LEFT_SOFT && menu_active==0) {menu_active=1;Tlog("menu enable");RedrawScreen();return 0;}
    
    if(msg->gbsmsg->submess=='3') {PanelCursorRight();RedrawScreen();return 0;}
    if(msg->gbsmsg->submess=='1') {PanelCursorLeft();RedrawScreen();return 0;}
    
    if(msg->gbsmsg->submess=='7' && p_counter>0) {p_counter--;RedrawScreen();return 0;}
    if(msg->gbsmsg->submess=='9' && p_counter<24-CFG_edit_panel_drawcount) {p_counter++;RedrawScreen();return 0;}
    
    if(msg->gbsmsg->submess==ENTER_BUTTON || msg->gbsmsg->submess=='5') {FillLevelByPos();RedrawScreen();return 0;}
    if(msg->gbsmsg->submess==GREEN_BUTTON) {used_level[cur_ypos][cur_xpos] = 0;RedrawScreen();return 0;}
    //if(msg->gbsmsg->submess==RIGHT_SOFT) return 1;
  }
  
  return 0;
}











extern void kill_data(void *p, void (*func_p)(void *));//Эта функция убивает эльф и освобождает память

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
  (void *)kill_data,
  (void *)method8,
  (void *)method9,
  0
};


int gui_id;
MAIN_GUI *main_gui;

static void maincsm_oncreate(CSM_RAM *data)//Вызывается при открытии эльфа,делаем что нужно
{
  /*//тут хитрые махинации для получения ид гуя чтобы мона было с ним манипулировать
  static const RECT Canvas={0,0,0,0};
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);*/
  
  static const RECT Canvas={0,0,0,0};
  StoreXYXYtoRECT((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  //patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  gui_id=csm->gui_id=CreateGUI(main_gui);
}

void ElfKiller(void)//освобождаем все занятое место эльфом в оперативе
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}


static void maincsm_onclose(CSM_RAM *csm)//функция закрытия эльфа,тут освобождаем памчть если нужно и т.п.
{
  SUBPROC((void *)ElfKiller);
}


#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)//тут вообщем протекают все сообщения поступаемые из эльфа так сказать:)
{
  //сообщение о реконфигурации например,ипц и т.д. и т.п.
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  if (msg->msg==MSG_RECONFIGURE_REQ)//Елси была реконфигурация,то обновляем настройки эльфа
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"конфиг обновлен!");
      InitConfig();
    }
  }

  return(1);
}


static const struct//это структура цсм,разбираться не надо:)
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
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

void UpdateCSMname(void)//ну собственно имя эльфа передаваемое хтаску
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"ArcanoidMapMaker v0.4 (c)half65");
}







#define NUM_BRICKS 9





int tolower(int toLower)
{
    if ((toLower >= 'A') && (toLower <= 'Z')) return (toLower + 0x20);
    return toLower;
}
IMGHDR* CreateImgHdrByAnyFile (char * name,short width, short height, int rot,int scale,int origin_size)
{
  WSHDR *path=AllocWS(256);
  str_2ws(path,name,256);
  unsigned int err=0;
  int msz,uid;
  IMGHDR *tmpimg,*myimg=NULL;  
  WSHDR *ext;
  HObj  mypicObj;
  short pos;
  int len;
  if (!path)goto exit0;
  len=wstrlen(path); 
  pos= wstrrchr(path,len,'.'); 
  if (!pos)goto exit0;

  ext=AllocWS(len-pos);
  wstrcpybypos(ext,path,pos+1,len-pos);
  char e_ext[8];
  ws_2str(ext,e_ext,wstrlen(ext));
  for(int tl=0;tl<strlen(e_ext);tl++)
  {
    e_ext[tl] = tolower(e_ext[tl]);
  }
  str_2ws(ext,e_ext,strlen(e_ext));
  
  uid=GetExtUid_ws(ext);      
  FreeWS(ext);
  
  mypicObj=Obs_CreateObject(uid,0x2d,0x02,0x80A8,1,1,&err);    
    if (err)  return 0;
  err=Obs_SetInput_File(mypicObj,0,path);
  FreeWS(path);
    if (err)  goto exit1;
    
  if (width!=0){ 
    short w=width;  
    short h=height;      
    if(origin_size)
    {
      err=Obs_GetInfo(mypicObj,0);    
      if (err)  goto exit1;  
      err=Obs_GetInputImageSize(mypicObj,&w,&h);    
      if (err)  goto exit1;  
      //x_size=w;
      //y_size=h;
    }
    err=Obs_SetOutputImageSize(mypicObj,w,h);
      if (err)  goto exit1;      
    if (rot){  
      err= Obs_SetRotation(mypicObj,rot);
        if (err)  goto exit1;      
    }
    err=Obs_SetScaling(mypicObj,scale);
      if (err)  goto exit1;          
  }
  err=Obs_Start(mypicObj);
    if (err)  goto exit1;            
  err=Obs_Output_GetPictstruct(mypicObj,&tmpimg);
    if (err)  goto exit1;             
  msz=CalcBitmapSize (tmpimg->w,tmpimg->h,tmpimg->bpnum);
  myimg=malloc(sizeof(IMGHDR));
  myimg->w=tmpimg->w;
  myimg->h=tmpimg->h;
  myimg->bpnum=tmpimg->bpnum;
  myimg->bitmap=malloc(msz);
  memcpy(myimg->bitmap,tmpimg->bitmap,msz);
exit1:
  Obs_DestroyObject(mypicObj);
exit0:  
  return myimg;
}

void LoadImages()
{
  char *temp = malloc(512);
   // sprintf(temp,"%spics\\brick1.png",pwd);
  //bricks[0] = CreateImgHdrByAnyFile(temp,0,0,0,0,1);
  
  //int hh = ScreenH()-((bricks[0]->h*32)+4); //это высота нового брика
  int hh = CFG_edit_scaleH;
  int ww = CFG_edit_scaleW;
  
  //big_bricks[0] = CreateImgHdrByAnyFile(temp,ww,hh,0,6,0);
  
  /*
    sprintf(temp,"%spics\\brick2.png",pwd);
  bricks[1] = CreateImgHdrByAnyFile(temp,0,0,0,0,1);
  big_bricks[1] = CreateImgHdrByAnyFile(temp,ww,hh,0,6,0);
    sprintf(temp,"%spics\\brick3.png",pwd);
  bricks[2] = CreateImgHdrByAnyFile(temp,0,0,0,0,1);
  big_bricks[2] = CreateImgHdrByAnyFile(temp,ww,hh,0,6,0);
    sprintf(temp,"%spics\\brick4.png",pwd);
  bricks[3] = CreateImgHdrByAnyFile(temp,0,0,0,0,1);
  big_bricks[3] = CreateImgHdrByAnyFile(temp,ww,hh,0,6,0);
    sprintf(temp,"%spics\\brick5.png",pwd);
  bricks[4] = CreateImgHdrByAnyFile(temp,0,0,0,0,1);
  big_bricks[4] = CreateImgHdrByAnyFile(temp,ww,hh,0,6,0);
    sprintf(temp,"%spics\\brick6.png",pwd);
  bricks[5] = CreateImgHdrByAnyFile(temp,0,0,0,0,1);
  big_bricks[5] = CreateImgHdrByAnyFile(temp,ww,hh,0,6,0);
    sprintf(temp,"%spics\\brick_bon.png",pwd);
  bricks[6] = CreateImgHdrByAnyFile(temp,0,0,0,0,1);
  //big_bricks[6] = CreateImgHdrByAnyFile(temp,ww,hh,0,6,0);
    sprintf(temp,"%spics\\brick_teleport.png",pwd);
  bricks[7] = CreateImgHdrByAnyFile(temp,0,0,0,0,1);
  big_bricks[6] = CreateImgHdrByAnyFile(temp,ww,hh,0,6,0);
    sprintf(temp,"%spics\\brick_mine.png",pwd);
  bricks[8] = CreateImgHdrByAnyFile(temp,0,0,0,0,1);
  big_bricks[7] = CreateImgHdrByAnyFile(temp,ww,hh,0,6,0);
  */
  
  for(int i=0;i<NUM_BRICKS;i++) //грузим картинки бонусов
  {
    sprintf(temp,"%spics\\brick%d.png",pwd,i+1);
    bricks[i] = CreateImgHdrByAnyFile(temp,0,0,0,0,1);
    if(i<NUM_BRICKS-1) big_bricks[i] = CreateImgHdrByAnyFile(temp,ww,hh,0,6,0);
  }
  
  for(int i=0;i<16;i++) //грузим картинки бонусов
  {
    sprintf(temp,"%spics\\bon_%d.png",pwd,i);
    big_bricks[NUM_BRICKS-1+i] = CreateImgHdrByAnyFile(temp,ww,hh,0,6,0);
  }
  
  
  mfree(temp);
}

const char perc_i[] = "%i";
int str2int(char *str)
{
  sprintf(lgn,"str2int(%s)",str);Tlog(lgn);
  int scan = -1;
  sscanf(str,perc_i,&scan);
  sprintf(lgn,"scan: %d",scan);Tlog(lgn);
  return scan;
}


void LoadMapFromPath(char *path,char level[MAX_HEIGHT][MAX_WIDTH]) //грузим мапу
{
  unsigned int err;
  sprintf(lgn,"LoadMap[%s]",path); Tlog(lgn);
  
  char *tt = malloc(32);
  memcpy(tt,path+(strlen(path)-5),1);
  tt[1]=0x00;
  num_to_save = str2int(tt);
  mfree(tt);
  
  
  int file=fopenA(path,A_ReadOnly+A_BIN,P_READ,&err);
  if(file==-1) {ShowMSG(0,(int)"Cant open map file!");return;}
  fread(file,(void *)&map.sign,4,&err);
  if(strcmp(map.sign,"ADM")!=0) {ShowMSG(0,(int)"wrong map sign!");fclose(file,0);return;}
  
  fread(file,(void*)&map.version,4,0);
  if(strcmp(map.version,"004")!=0) {ShowMSG(0,(int)"wrong map version!");fclose(file,0);return;}
  
  fread(file,(void*)&map.bg_num,1,0);
  fread(file,(void*)&map.snd_num,1,0);
  fread(file,(void*)&map.type,1,0);
  fread(file,(void*)&map.boss_diff,1,0);
  
  for(int y=0;y<MAX_HEIGHT;y++)
  {
    for(int x=0;x<MAX_WIDTH;x++)
    {
      fread(file,&level[y][x],1,0);
    }
  }
  
  fclose(file,0);
  sprintf(lgn,"map succesfully readed!"); Tlog(lgn);
}





int main(char *exename, char *fname)//exename-путь запускаемого эльфа, fname параметр передаваемый эльфу
{
   char s[128];
   const char *p=strrchr(exename,'\\')+1;
   strncpy(s,exename,p-exename);
   s[p-exename]='\0';
   pwd=malloc(128);
   sprintf(pwd,s);
   Tlog("--------------------------------------------------------");
   Tlog("Log started by root, UID=0. starting elf...");
   char *tempstr = malloc(512);
   sprintf(tempstr,"Environment variable PWD = %s",pwd);
   Tlog(tempstr);
   Tlog("All seems to be OK...");
   mfree(tempstr);
   
  MAIN_CSM main_csm;
  InitConfig();//инициируем конфиг,тобишь читаем настройки из него
  LockSched();
  UpdateCSMname();//обновляем имя для хтаска
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);//создаем цсм
  UnlockSched();
  
  e_ws = AllocWS(128);
  offset1 = 2+GetFontYSIZE(FONT_SM);
  
  LoadImages(); //грузим картинки
  
  FSTATS fs;
  sprintf(lgn,"fname:%s",fname);Tlog(lgn);
  if((fname!=NULL && GetFileStats(fname,&fs,0)!=-1) && (strstr(fname,".adm") || strstr(fname,".ADM"))) //если запустили с параметром,то открываем левел
  {
    LoadMapFromPath(fname,used_level);
  }
  else ZeroLevel(); //зануляем текущий левел 
  
  RedrawScreen();
  return 0;
}
