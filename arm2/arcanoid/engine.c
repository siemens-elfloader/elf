#include "..\inc\swilib.h"
#include "engine.h"
#include "config.h"
#include "SpriteLoader.h"
#include "menu.h"


//#define NO_LOG


extern char *pwd;  //путь к папке с эльфом типа 4:\\windows\\ 
signed char state; //статус игры(смотри дефайны)
short score = 0;
char UsedLevel[MAX_HEIGHT][MAX_WIDTH]; //сюда копим загруженный левел
IMGHDR *level_bg; //фон для текущего уровня
short clean_bricks = 0; //кооличество бриков,которые разбили на текущий момент
short bricks_of_clean = 0; //кооличество бриков,которое надо разбить для завершения левела
char total_levels = 0; //сколько левелов нашли
char ball_max_speed = 6;
char ball_min_speed = 2;
char total_lives = 3;
char levelcounter = 1;

char press_msg[128];
char press_type;



int PLAY_ID=0xFFFF;
char SoundRepeat = 1;
/*
by ilya90. замена функции на открывающую из папки с елфом.
вынужден заменить функцию библиотеки fopen на аналогичную,
открывающую файлы из папки с елфом. Функцию в библе 
переименовать в fopenA.
*/
int fopen(const char * filename, unsigned int fileflags, unsigned int filemode, unsigned int *errornumber)
{
char *realpath=malloc(512);
sprintf(realpath,"%s%s",pwd,filename);
int f=fopenA(realpath,fileflags,filemode,errornumber);
mfree(realpath);
return(f);
}

FSTATS fstats;
unsigned int err;

char DEBUG;
TDate date; TTime time;
#ifndef NO_LOG
void log (char *string)
{
  if(!DEBUG) return;
  int logfile=fopen("ArcanoidStudio_1.4.log",A_ReadWrite+A_TXT+A_Append+A_Create,P_READ+P_WRITE,0);
  char *data=malloc(4096);
  GetDateTime(&date,&time); 
  sprintf(data,">%d:%02d:%02d/%02d-%02d-%04d< >kernel<   %s\n",time.hour,time.min,time.sec,date.day, date.month,date.year,string);
  lseek(logfile, 0x0, S_END, 0, 0);
  fwrite(logfile,data,strlen(data),0);
  mfree(data);
  fclose(logfile,0);
}
#else 
void log (char *string){}
#endif

void DrwImg(IMGHDR *img, int x, int y)
{
  //LCD_DrawImage(img,x,y);
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  DrawObject(&drwobj);
}

char perc_t[]="%t";
char perc_s[]="%s";
char perc_d[]="%d"; //для избежания галимого глюка :)

typedef struct
{
  IMGHDR *img;
  short x;
  short y;
  char stats;
}image;
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
image brick[10];


image ball[3][3]; //3 типа мяча,у каждого типа по 3 размерности(большой,средний малый)
short ball_x,ball_y,ball_spx,ball_spy;
char ball_s; //размерность
char ball_type; //тип(обычный,"невидимка","все пробивающий")


TSPRITE user[4][3];
char user_l=0,user_r=0,user_sp=5;
short user_x,user_y;
short user_c; //время,которое платформа находится в движении
char user_s;
char user_type;
short user_N;





TSPRITE brick_sparks;
TSPRITE mine_sparks;
TSPRITE rocket_sparks;


//uid от 0 до 15 зарезервирован на бонусы!!
#define UID_WEAPON_PISTOL 25
#define UID_WEAPON_ROCKET 26
#define UID_OTHER 666


TSPRITE weapon_shot[2]; //rocket and pistol
signed char bonus_shot_type = -1; //-1 - не стреляем

image boss;

char offset1; //основной оффсет прорисовки


#define NUM_OF_BONUSES 16
typedef struct
{
  TSPRITE spr;
  char num; //номер бонуса,задается при создании бонуса
}BONUS;
BONUS bonus[NUM_OF_BONUSES];
char bonus_active[NUM_OF_BONUSES];
short bonus_counter[NUM_OF_BONUSES];
short bonus_time[NUM_OF_BONUSES];

///////////////////
char mem_ball_spx; 
char mem_ball_spy;
char bon_slime_use; //прилеплен ли шар к юзеру?
////////////////////

void SetCell(char x,char y,char value,unsigned int *err);
char GetCell(char x,char y);
void InitBoom(char x,char y);
void DestroyBrick(char x,char y);
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
#define abs(x) (((x)>0)?(x):-(x))
char BossBallHit()
{
  if(ball_x>=boss.x-6 && ball_x+ball[ball_type][ball_s].img->w<=boss.x+boss.img->w && ball_y<=boss.y+boss.img->h) return 1;
  else return 0;
}



char SBhit(image brick,char num) //проверка на столкновение пульки(или ракеты) с бриком.Стену(num==7) пулька не разрушит,а ракета вполне
{
  //проверка только на нижнюю сторону брика 
  RECT br;
  br.x = brick.x;
  br.y = brick.y;
  br.x2 = br.x+brick.img->w;
  br.y2 = br.y+brick.img->h;
  short x,y;
  
  for(short i=0;i<MAX_SPRITES;i++)
  {
    if(!sprites[i].active) continue;
    if(sprites[i].uid==UID_WEAPON_PISTOL || sprites[i].uid==UID_WEAPON_ROCKET) //вычисляем наши пульки и рокеты среди реестра спрайтов
    {
      GetSpriteCoordinaties(sprites[i].N,&x,&y);
      short x2 = x+GetSpriteWidth(sprites[i].N);
      if(((x2>=br.x && x2<=br.x2) || (x>=br.x && x<=br.x2)) && y>=br.y && y<=br.y2) //берем по крайним иксам
      {
        StopSprite(sprites[i].N);
        if(sprites[i].uid==UID_WEAPON_PISTOL) return 1;
        else return 2;
      }
    }
  }
  return 0;
}






short sx=0,sy=0;






//палево это снизу,добавим дефайнов,оптимизнем код,и будет рулез
/*char BBhit(image brick) //пофиксить!!
{
  //int sx,sy;
  //sx=0;
  //sy=0;
  
  RECT bl,br;
  bl.x=ball_x;
  bl.y=ball_y;
  bl.x2=ball_x+ball[ball_s].img->w;
  bl.y2=ball_y+ball[ball_s].img->h;
  br.x=brick.x;
  br.y=brick.y;
  br.x2=brick.x+brick.img->w;
  br.y2=brick.y+brick.img->h;
  
  if(bl.x2>br.x && bl.x<br.x2)
  {
    if(bl.y2>br.y && bl.y<br.y) return 1; //верхняя часть
    if(bl.y<br.y2 && bl.y2>br.y2) return 2; //нижняя часть
  }
  if(bl.y2>br.y && bl.y<br.y2)
  {
    if(bl.x2>br.x && bl.x<br.x) {return 3;} //левая часть
    if(bl.x<br.x2 && bl.x2>br.x2) {return 4;} //правая часть
  }
  
  
  
  if(bl.x>br.x && bl.x<br.x2) //внутри брика по иксам
  {
    if(bl.y>br.y && bl.y<br.y2) return
  }
  
  
  
  
  
  
  
  return 0;
}*/


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
#define BB_DOWN_RIGHT 0
#define BB_DOWN_LEFT 1
#define BB_UP_RIGHT 2
#define BB_UP_LEFT 3

#define BB_RET_RIGHT 0
#define BB_RET_LEFT 1
#define BB_RET_DOWN 2
#define BB_RET_UP 3
#define BB_RET_NEGATIVE 4

//если мяч летит вверх+влево,то чекаем на    BB_DOWN_RIGHT
//если мяч летит вниз+влево,то чекаем на     BB_UP_RIGHT
//если мяч летит вверх+вправо,то чекаем на   BB_DOWN_LEFT
//если мяч летит вниз+вправо,то чекаем на    BB_UP_LEFT
char BBhit(image brick,char type)
{
  RECT br; //это непосредственные координаты нашего брика(кирпичика то есть)
  br.x = brick.x;
  br.y = brick.y;
  br.x2 = br.x+brick.img->w;
  br.y2 = br.y+brick.img->h;
  
  RECT bl; //непосредственные координаты мяча
  bl.x = ball_x;
  bl.y = ball_y;
  bl.x2 = bl.x+ball[ball_type][ball_s].img->w;
  bl.y2 = bl.y+ball[ball_type][ball_s].img->h;
  
  
  
  if(type==BB_DOWN_RIGHT) //проверка на столкновение только с нижней и правой частью брика
  {
    if((bl.x>=br.x && bl.x<=br.x2 && bl.y>=br.y && bl.y<=br.y2) //мяч левым верхним краем внутри брика
    || (bl.x>=br.x && bl.x<=br.x2 && bl.y2>=br.y && bl.y2<=br.y2)
    || (bl.x2>=br.x && bl.x2<=br.x2 && bl.y>=br.y && bl.y<=br.y2))
    {
      //теперь проверим к чему мяч ближе - к низу или к правой стороне брика?
      //для этого сравниваем отрезки от координат мяча до координат брика по иксам и игрекам
      if(br.y2-bl.y>br.x2-bl.x) return BB_RET_RIGHT;
      else return BB_RET_DOWN;
    }
  }
  
  if(type==BB_DOWN_LEFT) //проверка на столкновение только с нижней и левой частью брика
  {
    if((bl.x2>=br.x && bl.x2<=br.x2 && bl.y>=br.y && bl.y<=br.y2) //мяч правым верхним краем внутри брика
    || (bl.x2>=br.x && bl.x2<=br.x2 && bl.y2>=br.y && bl.y2<=br.y2)
    || (bl.x>=br.x && bl.x<=br.x2 && bl.y>=br.y && bl.y<=br.y2))
    {
      //теперь проверим к чему мяч ближе - к низу или к левой стороне брика?
      //для этого сравниваем отрезки от координат мяча до координат брика по иксам и игрекам
      if(br.y2-bl.y>bl.x2-br.x) return BB_RET_LEFT;
      else return BB_RET_DOWN;
    }
  }
  
  if(type==BB_UP_RIGHT) //проверка на столкновение только с верхней и правой частью брика
  {
    if((bl.x>=br.x && bl.x<=br.x2 && bl.y2>=br.y && bl.y2<=br.y2) //мяч левым нижним краем внутри брика
    || (bl.x>=br.x && bl.x<=br.x2 && bl.y>=br.y && bl.y<=br.y2)
    || (bl.x2>=br.x && bl.x2<=br.x2 && bl.y2>=br.y && bl.y2<=br.y2))
    {
      //теперь проверим к чему мяч ближе - к низу или к правой стороне брика?
      //для этого сравниваем отрезки от координат мяча до координат брика по иксам и игрекам
      if(bl.y2-br.y>br.x2-bl.x) return BB_RET_RIGHT;
      else return BB_RET_UP;
    }
  }
  
  if(type==BB_UP_LEFT) //проверка на столкновение только с верхней и левой частью брика
  {
    if((bl.x2>=br.x && bl.x2<=br.x2 && bl.y2>=br.y && bl.y2<=br.y2) //мяч правым нижним краем внутри брика
    || (bl.x2>=br.x && bl.x2<=br.x2 && bl.y>=br.y && bl.y<=br.y2)
    || (bl.x>=br.x && bl.x<=br.x2 && bl.y2>=br.y && bl.y2<=br.y2))
    {
      //теперь проверим к чему мяч ближе - к низу или к левой стороне брика?
      //для этого сравниваем отрезки от координат мяча до координат брика по иксам и игрекам
      if(bl.y2-br.y>bl.x2-br.x) return BB_RET_LEFT;
      else return BB_RET_UP;
    }
  }
  
  return BB_RET_NEGATIVE;
}
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
char UBhit()
{
  short ux,uy,uw;
  GetSpriteCoordinaties(user_N,&ux,&uy);
  uw = GetSpriteWidth(user_N);
  
  //столкновение с левым краем
  if(ball_x+(ball[ball_type][ball_s].img->w/2) > ux  &&  ball_x+(ball[ball_type][ball_s].img->w/2) < ux+(uw/4) && ball_y+ball[ball_type][ball_s].img->h > uy) return 1;
  //столкновение с центром платформы
  if(ball_x+(ball[ball_type][ball_s].img->w/2) > ux+(uw/4)  &&  ball_x+(ball[ball_type][ball_s].img->w/2) < ux+((uw/4)*3) && ball_y+ball[ball_type][ball_s].img->h > uy) return 2;
  //столкновение с правым краем
  if(ball_x+(ball[ball_type][ball_s].img->w/2) > ux+((uw/4)*3)  &&  ball_x+(ball[ball_type][ball_s].img->w/2) < ux+uw && ball_y+ball[ball_type][ball_s].img->h > uy) return 3;
  return 0; //если не столкнулись,то выходим с нулем
}
char UBNhit(short bx,short bx2,short by2) //столкновение юзера с бонусами
{
  short ux,uy,uw,uh;
  GetSpriteCoordinaties(user_N,&ux,&uy);
  uw = GetSpriteWidth(user_N);
  uh = GetSpriteHeight(user_N);
  
  if(bx2>ux && bx<ux+uw && by2>uy && by2<uy+uh) return 1;
  return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
void SetDifficulty()
{
  if(savedata.difficulty==DIFF_EASY)
  {
    ball_max_speed = 4;
    ball_min_speed = 1;
  }
  else if(savedata.difficulty==DIFF_NORMAL)
  {
    ball_max_speed = 6;
    ball_min_speed = 2;
  }
  else if(savedata.difficulty==DIFF_HARD)
  {
    ball_max_speed = 8;
    ball_min_speed = 3;
  }
}

char cont; // 1-пишем в меню "продолжить" 0-"новая игра"

void SetDefaultGameParameters()
{
  user_type = 0; //normal user
  user_s = 1; //normal length
  ball_type = 0; //normal ball
  ball_s = 0; //small size
  
  total_lives = 3;
  //score = 0;
  cont = 0;
  ball_x=sw/2;
  ball_y=sh/2;
  user_x=(sw/2)-(user[user_type][user_s].img[0]->w/2);
  user_y=sh-user[user_type][user_s].img[0]->h-1;
  ball_spx=2;
  ball_spy=2;
  SetDifficulty();
}


extern void CreateTextEditDialog(int type,char *src,int maxlen);




void Play(const char *fname)
{
  if ((!IsCalling()) && savedata.SoundsEnable)
  {
    if(GetFileStats(fname,&fstats,&err)!=-1)
    {
      PLAYFILE_OPT _sfo1;
      WSHDR* sndPath=AllocWS(128);
      WSHDR* sndFName=AllocWS(128);
      char s[128];
      const char *p=strrchr(fname,'\\')+1;
      str_2ws(sndFName,p,128);
      strncpy(s,fname,p-fname);
      s[p-fname]='\0';
      str_2ws(sndPath,s,128);

      zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
      _sfo1.repeat_num=SoundRepeat;
      _sfo1.time_between_play=0;
      _sfo1.play_first=0;
      _sfo1.volume=savedata.SndVolume;
#ifdef NEWSGOLD
      _sfo1.unk6=1;
      _sfo1.unk7=1;
      _sfo1.unk9=2;
      PLAY_ID = PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
      _sfo1.unk4=0x80000000;
      _sfo1.unk5=1;
      PLAY_ID = PlayFile(0xC, sndPath, sndFName, 0,MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#else
      _sfo1.unk5=1;
      PLAY_ID = PlayFile(0xC, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif
      FreeWS(sndPath);
      FreeWS(sndFName);
    }
  }
}




void PlayMusic(char id)
{
  char *temp = malloc(512);
  
  if(id==MENU_MUSIC)
  {
    SoundRepeat = 20;
    sprintf(temp,"%ssounds\\menu.mid",pwd);
  }
  else if(id==GAME_MUSIC)
  {
    SoundRepeat = 20;
    sprintf(temp,"%ssounds\\%d.mid",pwd,map.snd_num);
  }
  else if(id==LOSE_MUSIC)
  {
    SoundRepeat = 1;
    sprintf(temp,"%ssounds\\lose.mid",pwd);
  }
  else if(id==WIN_MUSIC)
  {
    SoundRepeat = 1;
    sprintf(temp,"%ssounds\\win.mid",pwd);
  }
  else if(id==END_MUSIC)
  {
    SoundRepeat = 1;
    sprintf(temp,"%ssounds\\end.mid",pwd);
  }
  Play(temp);
  mfree(temp);
}




#define STD_SND

#define SND_USER 0
#define SND_BRICK 1

#ifndef STD_SND
void PlaySnd(char id)
{
  char *temp = malloc(512);
  SoundRepeat = 1;
  if(id==SND_USER)
  {
    sprintf(temp,"%ssounds\\user.amr",pwd);
  }
  else if(id==SND_BRICK)
  {
    sprintf(temp,"%ssounds\\brick.amr",pwd);
  }
  Play(temp);
  mfree(temp);
}
#else

void PlaySnd(char id)
{
  if(savedata.SndEnable)
  {
    if(id==SND_USER) PlaySound(1,0,0,savedata.StdSnd_user,0);
    if(id==SND_BRICK) PlaySound(1,0,0,savedata.StdSnd_brick,0);
  }
}
#endif

GBSTMR vtmr;
void StopVibra()
{
  SetVibration(0);
  if(IsTimerProc(&vtmr))
  {
   GBS_StopTimer(&vtmr);
   GBS_DelTimer(&vtmr);
  }
}
void StartVibra(char value,char len)
{
  if(savedata.VibraEnable)
  {
   SetVibration(value);
   GBS_StartTimerProc(&vtmr,len,StopVibra);
  }
}



GBSTMR press_tmr;
void PressTimerFunc() //для корректной работы надо время на отрисовку,а потом по таймеру пускаем эту функцию
{
  state = STATE_PRESS;
  GBS_DelTimer(&press_tmr);
  TimerRedrawScreen();
}




void DumpMap(char lev[MAX_HEIGHT][MAX_WIDTH],char num)
{
  char *temp = malloc(256);
  sprintf(temp,"%smaps\\level%d.log",pwd,num);
  int file = fopenA(temp,A_WriteOnly+A_BIN+A_Create,P_WRITE,0);
  
  
  for(int y=0;y<MAX_HEIGHT;y++)
  {
    sprintf(temp,perc_s,"{");
    fwrite(file,temp,1,0);
    for(int x=0;x<MAX_WIDTH;x++)
    {
      sprintf(temp,"%d,",lev[y][x]);
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




char TestLevel[MAX_HEIGHT] [MAX_WIDTH] =
    {
      {1,1,1,1,1,1,2,2,2,1,1,1,1,1,1},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,7,7,7,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
      {5,5,5,5,5,0,0,0,0,0,5,5,5,5,5},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {30,30,30,30,30,30,30,30,30,30,30,30,30,30,30},
      {30,30,30,30,30,30,30,30,30,30,30,30,30,30,30},
      {30,30,30,30,30,30,30,30,30,30,30,30,30,30,30},
      {25,25,25,25,25,25,25,25,25,25,25,25,25,25,25},
      {26,26,26,26,26,26,26,26,26,26,26,26,26,26,26},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };


void LoadTestLevel(char **level)
{
  char *temp = malloc(256);
  memcpy(level,&TestLevel,MAX_WIDTH*MAX_HEIGHT);
  ifree(level_bg);
  sprintf(temp,"%spics\\0.png",pwd);
  level_bg = CreateIMGHDRFromPngFile(temp,2);
  mfree(temp);
  map.snd_num = 0;
  map.type = TYPE_NORMAL;
  map.boss_diff = DIFF_NORMAL;
  map.boss_lives = 2;
}











char PrepareLevel(char levelnum)
{
  extern void LoadMapFromFile(char level[MAX_HEIGHT][MAX_WIDTH],char num,char *err);
  char level[MAX_HEIGHT][MAX_WIDTH];
  sprintf(lgn,"PrepareLevel(%d)...",levelnum);log(lgn);
  
  /*if(rand_level)
  {
    int trigger; //меняется по рандому от 0 до 2
    int value; //записываемое значение в левел
    for(int ly=0; ly<32;ly++) //тут все упрощенно)
    {
     for(int lx=0;lx<15;lx++)
     {
        trigger=rnd(0); //присваиваем триггеру 1, 0, или 2
        if(trigger==0) value=0; //делаем в левеле пустое место(типа нету тут ничо)
        if(trigger==1) value=rnd(1); //пихаем рандомный бонус
        if(trigger==2) value=rnd(2); //пихаем рандомный брик
        level[ly][lx] = value; //записываем полученное значение поячейково
     }
    }
    
    
  } //и получилось у нас хз что =))
  else*/
  char err=0;
  if(levelnum>total_levels)
  {
    sprintf(press_msg,"Все уровни завершены\nПобеда!");
    press_type = PRESS_GAMEOVER;
    cont=0;
    GBS_StartTimerProc(&press_tmr,6,PressTimerFunc);
    log("levels completed");
    return 0;
  }
  else LoadMapFromFile(level,levelnum,&err); //грузим из файла
  sprintf(lgn,"start preparing[%d]",levelnum);log(lgn);
  bricks_of_clean=0;
  clean_bricks=0;
  if(err) {sprintf(lgn,"PrepareLevel: Error while loading map");log(lgn);return 0;}
  if(savedata.opened_levels<levelnum) savedata.opened_levels = levelnum;
  //DumpMap(level,levelcounter);
  
  
  for(int ly=0; ly<MAX_HEIGHT;ly++)
  {
   for(int lx=0;lx<MAX_WIDTH;lx++)
   {
     if(level[ly][lx]==1 || level[ly][lx]==2 || level[ly][lx]==3) bricks_of_clean+=1; //normal bricks
     if(level[ly][lx]>=20 && level[ly][lx]<=35) bricks_of_clean+=1; //bonus bricks
     
     if(level[ly][lx]==4) bricks_of_clean+=2; //брик,требующий двойное попадание,следовательно увеличиваем bricks_of_clean на 2
     if(level[ly][lx]==5) bricks_of_clean+=3; //брик,требующий тройное попадание,следовательно увеличиваем bricks_of_clean на 3
     UsedLevel[ly][lx]=level[ly][lx];
   }
  }
  
  user_x = (sw/2)-(user[user_type][user_s].img[0]->w/2);
  user_y = sh-user[user_type][user_s].img[0]->h;
  ball_x=W/2;
  ball_y=H-20;
  if(ball_spy>0) ball_spy=-ball_min_speed; //шарик двигается вверх на минималке
  sprintf(lgn,"[level %d]bricks_of_clean:%d",levelnum,bricks_of_clean);log(lgn);
  
  PlayMusic(GAME_MUSIC);
  press_type = PRESS_NEWLEVEL;
  sprintf(press_msg,"уровень %d\nна очереди %d попаданий!\nготовы?",levelnum,bricks_of_clean);
  TimerRedrawScreen();
  GBS_StartTimerProc(&press_tmr,6,PressTimerFunc);
  return 1;
}



void GetCoordinatiesByLevelPos(char x,char y,short *px,short *py)
{
  *px = 0+brick[0].img->w*x;
  *py = 0+brick[0].img->h*y;
}


void GetCellState(char x,char y,unsigned int *err)
{
  if(x>=MAX_WIDTH || y>=MAX_HEIGHT) *err=1;
  else *err=0;
}






//епт падает по watch_dog_min_time(перегрузка видимо) если миной подрываются соседние мины((
void InitBoom(char x,char y) //x и y - координаты в левеле.
{
  asm("nop"); //это так,палево какое-то (:
  asm("nop");
  asm("nop");
  
  short px,py;
  //эти 2 массива для сокращения писанины,внимательно смотри первый закомментированный код ниже(длинный :))
  static signed char x_line[9] = {0,1,-1,0,0,-1,1,1,-1};
  static signed char y_line[9] = {0,0,0,-1,1,-1,1,-1,1};
  
  for(char i=0;i<9;i++)
  {
    char cx = x+x_line[i];
    char cy = y+y_line[i];
    
    GetCellState(cx,cy,&err);
    if(!err)
    {
      GetCoordinatiesByLevelPos(cx,cy,&px,&py);
      if(GetCell(cx,cy)==7) {SetCell(cx,cy,0,&err);} //если это мина,то киляем ее нахъ
      else DestroyBrick(cx,cy); //не мина,знач все сделает функция DestroyBrick.Надо это для избежания той левой фигни с перегрузкой
      InitSprite(&mine_sparks,UID_OTHER,px,py,1);
    }
  }
  /*
  GetCellState(x,y,&err);
  if(!err)
  {
    GetCoordinatiesByLevelPos(x,y,&px,&py);
    DestroyBrick(x,y);
    InitSprite(&mine_sparks,UID_OTHER,px,py,1);
  }
  
  GetCellState(x+1,y,&err);
  if(!err)
  {
    GetCoordinatiesByLevelPos(x+1,y,&px,&py);
    DestroyBrick(x+1,y);
    InitSprite(&mine_sparks,UID_OTHER,px,py,1);
  }
  
  GetCellState(x-1,y,&err);
  if(!err)
  {
    GetCoordinatiesByLevelPos(x-1,y,&px,&py);
    DestroyBrick(x-1,y);
    InitSprite(&mine_sparks,UID_OTHER,px,py,1);
  }
  
  GetCellState(x,y-1,&err);
  if(!err)
  {
    GetCoordinatiesByLevelPos(x,y-1,&px,&py);
    DestroyBrick(x,y-1);
    InitSprite(&mine_sparks,UID_OTHER,px,py,1);
  }
  
  GetCellState(x,y+1,&err);
  if(!err)
  {
    GetCoordinatiesByLevelPos(x,y+1,&px,&py);
    DestroyBrick(x,y+1);
    InitSprite(&mine_sparks,UID_OTHER,px,py,1);
  }
  
  GetCellState(x-1,y-1,&err);
  if(!err)
  {
    GetCoordinatiesByLevelPos(x-1,y-1,&px,&py);
    DestroyBrick(x-1,y-1);
    InitSprite(&mine_sparks,UID_OTHER,px,py,1);
  }
  
  GetCellState(x+1,y+1,&err);
  if(!err)
  {
    GetCoordinatiesByLevelPos(x+1,y+1,&px,&py);
    DestroyBrick(x+1,y+1);
    InitSprite(&mine_sparks,UID_OTHER,px,py,1);
  }
  
  GetCellState(x+1,y-1,&err);
  if(!err)
  {
    GetCoordinatiesByLevelPos(x+1,y-1,&px,&py);
    DestroyBrick(x+1,y-1);
    InitSprite(&mine_sparks,UID_OTHER,px,py,1);
  }
  
  GetCellState(x-1,y+1,&err);
  if(!err)
  {
    GetCoordinatiesByLevelPos(x-1,y+1,&px,&py);
    DestroyBrick(x-1,y+1);
    InitSprite(&mine_sparks,UID_OTHER,px,py,1);
  }*/
  //log("Boom OK");
}















//калечный код(
char blocks_trigger; //если около брика,с кот. столкнулся мяч,есть соседние брики,то ставим на 1,и после столкновения не учитываем одновременное столкновение
//с ними,иначе шар будет лететь куда попало





int ball_check_only_pos_x=0;
int ball_check_only_pos_y=0;
int CheckAndChangeBallState(image brick,int xnum,int ynum,int bonus) //xnym и ynum это координаты брика в массиве
{
  if(ball_check_only_pos_x>100) {ball_check_only_pos_x=0;ball_spy+=1;} //для выхода из тупикового зацикливания шарика на одной оси :)
  if(ball_check_only_pos_y>100) {ball_check_only_pos_y=0;ball_spx+=1;} //для выхода из тупикового зацикливания шарика на одной оси :)
  char mode;
  
  if(ball_spx<0 && ball_spy<0) //если двигался до столкновения влево+вверх
  {
    mode = BBhit(brick,BB_DOWN_RIGHT); //можем столкнуться только с низом и правой стороной
    
    if(mode==BB_RET_NEGATIVE) {blocks_trigger=0;} //когда шарик вышел из "опасной зоны",то есть он уже не сталкивается с бриками,тогда выключаем триггер
    else
    {
      if(UsedLevel[ynum][xnum+1]>0) mode=BB_RET_DOWN; //если справо от нашего брика есть другой брик,то можем столкнуться только с нижней стороной брика,не так ли?
      else if(UsedLevel[ynum+1][xnum]>0) mode=BB_RET_RIGHT; //только с правой стороной
    }
    
    if(mode==BB_RET_DOWN && blocks_trigger==0)
    {
      ball_spx=ball_spx;  //продолжаем двигаться влево
      ball_spy=-ball_spy;  //теперь двигаемся не вверх,а вниз
      blocks_trigger=1;
      return 1;
    }
    if(mode==BB_RET_RIGHT && blocks_trigger==0)
    {
      ball_spx=-ball_spx; //теперь двигаемся не влево,а вправо
      ball_spy=ball_spy;  //продолжаем двигаться вверх
      blocks_trigger=1;
      return 1;
    }
  }
  
  if(ball_spx>0 && ball_spy>0) //если двигался до столкновения вправо+вниз
  {
    mode = BBhit(brick,BB_UP_LEFT); //можем столкнуться только с верхом и левой стороной
    if(mode==BB_RET_NEGATIVE) {blocks_trigger=0;} //когда шарик вышел из "опасной зоны",то есть он уже не сталкивается с бриками,тогда выключаем триггер
    else
    {
      if(UsedLevel[ynum][xnum-1]>0) mode=BB_RET_UP;
      else if(UsedLevel[ynum-1][xnum]>0) mode=BB_RET_LEFT;
    }
    
    if(mode==BB_RET_UP && blocks_trigger==0)
    {
      ball_spx=ball_spx;  //продолжаем двигаться вправо
      ball_spy=-ball_spy;  //теперь двигаемся не вниз,а вверх
      blocks_trigger=1;
      return 1;
    }
    if(mode==BB_RET_LEFT && blocks_trigger==0)
    {
      ball_spx=-ball_spx; //теперь двигаемся не вправо,а влево
      ball_spy=ball_spy;  //продолжаем двигаться вниз
      blocks_trigger=1;
      return 1;
    }
  }
  
  if(ball_spx>0 && ball_spy<0) //если двигался до столкновения вправо+вверх
  {
    mode = BBhit(brick,BB_DOWN_LEFT); //можем столкнуться только с низом и левой стороной
    if(mode==BB_RET_NEGATIVE) {blocks_trigger=0;} //когда шарик вышел из "опасной зоны",то есть он уже не сталкивается с бриками,тогда выключаем триггер
    else
    {
      if(UsedLevel[ynum][xnum-1]>0) mode=BB_RET_DOWN; //если справо от нашего брика есть другой брик,то можем столкнуться только с нижней стороной брика,не так ли?
      else if(UsedLevel[ynum+1][xnum]>0) mode=BB_RET_LEFT; //только с правой стороной
    }
    
    if(mode==BB_RET_DOWN && blocks_trigger==0)
    {
      ball_spx=ball_spx;  //продолжаем двигаться вправо
      ball_spy=-ball_spy;  //теперь двигаемся не вверх,а вниз
      blocks_trigger=1;
      return 1;
    }
    if(mode==BB_RET_LEFT && blocks_trigger==0)
    {
      ball_spx=-ball_spx; //теперь двигаемся не влево,а вправо
      ball_spy=ball_spy;  //продолжаем двигаться вверх
      blocks_trigger=1;
      return 1;
    }
  }
  
  if(ball_spx<0 && ball_spy>0) //если двигался до столкновения влево+вниз
  {
    mode = BBhit(brick,BB_UP_RIGHT); //можем столкнуться только с верхом и правой стороной
    if(mode==BB_RET_NEGATIVE) {blocks_trigger=0;} //когда шарик вышел из "опасной зоны",то есть он уже не сталкивается с бриками,тогда выключаем триггер
    else
    {
      if(UsedLevel[ynum][xnum+1]>0) mode=BB_RET_UP;
      else if(UsedLevel[ynum-1][xnum]>0) mode=BB_RET_RIGHT;
    }
    
    if(mode==BB_RET_UP && blocks_trigger==0)
    {
      ball_spx=ball_spx;  //продолжаем двигаться влево
      ball_spy=-ball_spy;  //теперь двигаемся не вниз,а вверх
      blocks_trigger=1;
      return 1;
    }
    if(mode==BB_RET_RIGHT && blocks_trigger==0)
    {
      ball_spx=-ball_spx; //теперь двигаемся не влево,а вправо
      ball_spy=ball_spy;  //продолжаем двигаться вниз
      blocks_trigger=1;
      return 1;
    }
  }
  
  
  return 0;
}








void CopyRecords(char *dest)
{
  sprintf(lgn,"CopyRecords(%s)..[score=%d]",dest,score);log(lgn);
  if(score==0) return;
  char *t = malloc(128);
  sprintf(t,"%s - %d",dest,score);
  
  char i = 0;
  char e = 0;
  while(i<MAX_RECORDS)
  {
    if(!savedata.recs[i].use) 
    {
      strcpy(savedata.recs[i].name,t);
      savedata.recs[i].use = 1;
      e=1;
      break;
    }
    i++;
  }
  if(e==0) //все рекорды уже заняты,пишем в первый
  {
     strcpy(savedata.recs[0].name,t);
     savedata.recs[0].use = 1;
  }
}





void Edit_endproc(int type,char *dest)
{
  if(type==0) //имя для рекорда
  {
    CopyRecords(dest);
  }
  
}





GBSTMR ptmr;
void PlayMusicOfTime()
{
  GBS_StopTimer(&ptmr);
  GBS_DelTimer(&ptmr);
  PlayMusic(GAME_MUSIC);
}


void LoseLife()
{
  PlayMusic(LOSE_MUSIC);
  GBS_StartTimerProc(&ptmr,500,PlayMusicOfTime);
  
  if(map.type==TYPE_NORMAL)
  {
   ball_x=sw/2;
   ball_y=sh-sh/3;
  }
  else if(map.type==TYPE_BOSS)
  {
   ball_x=sw/2;
   ball_y=sh/2;
  }
  if(ball_spy>0) ball_spy=-ball_min_speed; //шарик двигается вверх на минималке
  total_lives--;
  
  if(total_lives<=0) //game over
  {
    cont=0;
    PlayMusic(END_MUSIC);
    press_type = PRESS_GAMEOVER;
    sprintf(press_msg,"игра закончена,ваши очки: %d",score);
    sprintf(lgn,"LoseLife - game over[msg: %s]",press_msg);log(lgn);
    TimerRedrawScreen();
    GBS_StartTimerProc(&press_tmr,15,PressTimerFunc);
    return;
  }
  
  
  press_type = PRESS_LOSELIFE;
  if(total_lives==1) sprintf(press_msg,perc_s,"осталась одна жизнь");
  if(total_lives==2 || total_lives==3 || total_lives==4) sprintf(press_msg,"осталось %d жизни",total_lives);
  if(total_lives>=5) sprintf(press_msg,"осталось %d жизней",total_lives);
  
  sprintf(lgn,"LoseLife[msg: %s]",press_msg);log(lgn);
  
    TimerRedrawScreen();
    GBS_StartTimerProc(&press_tmr,15,PressTimerFunc);
}


void Boss_loselife()
{
  PlayMusic(WIN_MUSIC);
  GBS_StartTimerProc(&ptmr,500,PlayMusicOfTime);
  ball_x=W/2;
  ball_y=H/3;
  if(ball_spy<0) ball_spy=-ball_min_speed; //шарик двигается вниз на минималке
  
  map.boss_lives--;
  if(map.boss_lives<=0) //game over
  {
    sprintf(press_msg,perc_s,"босс сдул");
     TimerRedrawScreen();
     GBS_StartTimerProc(&press_tmr,15,PressTimerFunc);
    return;
  }
  if(map.boss_lives==1) sprintf(press_msg,perc_t,"у босса осталась одна жизнь");
  if(map.boss_lives==2 || map.boss_lives==3 || map.boss_lives==4) sprintf(press_msg,"%t %d %t","у босса осталось",map.boss_lives,"жизни");
  if(map.boss_lives>=5) sprintf(press_msg,"%t %d %t","у босса осталось",map.boss_lives,"жизней");
  
  sprintf(lgn,"Boss_LoseLife[msg: %s]",press_msg);log(lgn);
  
    TimerRedrawScreen();
    GBS_StartTimerProc(&press_tmr,15,PressTimerFunc);
}




int bon_ball; //1 - super ball;2 - ghost ball
int br_draw_offset;




#define NUM_BRICKS 9






void DestroyBrick(char x,char y) //уничтожение брика.
{
  
  short px,py;
  GetCoordinatiesByLevelPos(x,y,&px,&py);
  char num = GetCell(x,y);
  
  sprintf(lgn,"DestroyBrick[x:%d,y:%d,px:%d,py:%d]",x,y,px,py);log(lgn);
  
  if(num==1 || num==2 || num==3) {SetCell(x,y,0,&err);score+=20;clean_bricks++;InitSprite(&brick_sparks,UID_OTHER,px,py,1);return;} //на месте исчезновения брика рисуем искры типа
  if(num==4) {SetCell(x,y,3,&err);score+=20;clean_bricks++;InitSprite(&brick_sparks,UID_OTHER,px,py,1);return;}
  if(num==5) {SetCell(x,y,4,&err);score+=20;clean_bricks++;InitSprite(&brick_sparks,UID_OTHER,px,py,1);return;}
  if(num==6) {InitSprite(&brick_sparks,UID_OTHER,px,py,1);return;} //стена
  if(num==7) {score+=25;InitBoom(x,y);return;}
  if(num>=20 && num<=35) //бонусы
  {
    char bonusnumber = num-20;
    SetCell(x,y,0,&err); //делаем брик,в который врезались невидимым
    clean_bricks++; //увеличиваем счетчик побитых бриков
    score+=25;
    InitSprite(&brick_sparks,UID_OTHER,px,py,1);
    //uid будет у нас номером бонуса :)
    InitMSprite(&bonus[bonusnumber].spr,bonusnumber,px,py,0,3,0,sh-bonus[bonusnumber].spr.img[0]->h); //старт полета бонуса вниз
  }
}








void SetCell(char x,char y,char value,unsigned int *err)
{
  *err = 0;
  if(x>=MAX_WIDTH || y>=MAX_HEIGHT) {*err = 1;return;}
  UsedLevel[y][x] = value;
}

char GetCell(char x,char y)
{
  if(x<MAX_WIDTH && y<MAX_HEIGHT) return UsedLevel[y][x];
  sprintf(lgn,"GetCell(%d,%d) - Error!",x,y);log(lgn);
  return 0;
}






void DrawBricks()
{
  for(int y=0;y<MAX_HEIGHT;y++)
  {
    for(int x=0;x<MAX_WIDTH;x++)
    {
      char num = GetCell(x,y); //ячейка
      if(num>0 && num<9) //норм. брики
      {
        char b_num = num-1;
          brick[b_num].y = br_draw_offset+brick[b_num].img->h*y;
          brick[b_num].x = 0+brick[b_num].img->w*x;
          DrwImg(brick[b_num].img,brick[b_num].x,brick[b_num].y);
          //чекаем шарик на скорость и направление +изменяем их на соответствующие
          char type = SBhit(brick[b_num],num);
          if(CheckAndChangeBallState(brick[b_num],x,y,0)==1 || type>0) //если столкнулись с бриком
          {
            DestroyBrick(x,y); //киляем брик
            //если врезались ракетой,то мутим типа большой взрыв
            if(type==2) {InitSprite(&rocket_sparks,UID_OTHER,brick[b_num].x,brick[b_num].y,1);InitBoom(x,y);}
          }
      }
      else if(num>=20 && num<=35) //бонусы
      {
        brick[8].y=br_draw_offset+brick[8].img->h*y;                          //установка позиции прорисовки бонусного брика
        brick[8].x=brick[8].img->w*x;                          //установка позиции прорисовки бонусного брика
        DrwImg(brick[8].img,brick[8].x,brick[8].y);   //сама прорисовка, как говорится по месту
        //чекаем шарик на скорость и направление +изменяем их на соответствующие
        char type = SBhit(brick[8],num);
        if(CheckAndChangeBallState(brick[8],x,y,0)==1 || type>0)
        {  
          DestroyBrick(x,y); //киляем брик
          if(type==2) {InitSprite(&rocket_sparks,UID_OTHER,brick[8].x,brick[8].y,1);InitBoom(x,y);}
        }
      }
    }
  }
}





int ball_a=0; //ускорение шарика,0 - нет ускорения,отрицательные значения = ускорение--
int user_a=0;

#define NSM -2 //минусовая скорость
#define NSP 2 //плюсовая скорость

int ball_spx_accel; //типа изменение угла полета шарика
int ball_spy_accel;

/*int UBhit()
{
  //столкновение с левым краем
  if(ball_x+(ball[ball_s].img->w/2) > user_x  &&  ball_x+(ball[ball_s].img->w/2) < user_x+(user[user_s].img->w/3) && ball_y+ball[ball_s].img->h > user_y) return 1;
  //столкновение с центром платформы
  if(ball_x+(ball[ball_s].img->w/2) > user_x+(user[user_s].img->w/3)  &&  ball_x+(ball[ball_s].img->w/2) < user_x+((user[user_s].img->w/3)*2) && ball_y+ball[ball_s].img->h > user_y) return 2;
  //столкновение с правым краем
  if(ball_x+(ball[ball_s].img->w/2) > user_x+((user[user_s].img->w/3)*2)  &&  ball_x+(ball[ball_s].img->w/2) < user_x+user[user_s].img->w && ball_y+ball[ball_s].img->h > user_y) return 3;
  return 0; //если не столкнулись,то выходим с нулем
}*/



void DrawBall()
{
  

   if(ball_spy<0 && ball_spx>0) //вправо+вверх
   {
     if(ball_x>=sw-ball[ball_type][ball_s].img->w) {ball_spx=-ball_spx;ball_spy=ball_spy;} //двигаемся влево+вверх
     
     if(map.type==TYPE_NORMAL) //обычный левел
     {
       if(ball_y<=offset1) {ball_spx=ball_spx;ball_spy=-ball_spy;} //двигаемся вправо+вниз
     }
     else //левел-босс
     {
       if(BossBallHit())
       {
         ball_spx=ball_spx;ball_spy=-ball_spy; //двигаемся вправо+вниз
         PlaySnd(SND_USER);
         StartVibra(savedata.VibraVolume,savedata.VibraCount);
       }
       else
       if(ball_y<offset1) //босс запарил =)
       {
         score+=100;
         Boss_loselife();
       }
     }
   }
   
  if(ball_spy<0 && ball_spx<0) //влево+вверх
  {
    if(ball_x<=0) {ball_spx=-ball_spx;ball_spy=ball_spy;} //двигаемся вправо+вверх
    
    if(map.type==TYPE_NORMAL) //обычный левел
    {
      if(ball_y<offset1) {ball_spx=ball_spx;ball_spy=-ball_spy;} //двигаемся влево+вниз
    }
    else
    {
       if(BossBallHit())
       {
         ball_spx=ball_spx;ball_spy=-ball_spy; //двигаемся влево+вниз
         PlaySnd(SND_USER);
         StartVibra(savedata.VibraVolume,savedata.VibraCount);
       }
       else
       if(ball_y<=offset1) //босс запарил =)
       {
         score+=100;
         Boss_loselife();
       }
      
      
    }
  }
   
   
  if(bonus_active[BON_SLIME]) //прилипалка активна
  {
    if(UBhit()>0) //столкнулся мяч с юзером
    {   
      PlaySnd(SND_USER);
      StartVibra(savedata.VibraVolume,savedata.VibraCount);
      mem_ball_spx = ball_spx;
      mem_ball_spy = ball_spy;
      ball_spx = 0;
      ball_spy = 0;
      bon_slime_use = 1; //лишнее это,но так вроде понятнее
    }
  }
  
  //так как ^скорости равны нулям,то нижнее условие(и остальные три тоже) не выполнится :)
  if(ball_spy>0 && ball_spx>0) //вправо+вниз
  {
    if(ball_x>=sw-ball[ball_type][ball_s].img->w) {ball_spx=-ball_spx;ball_spy=ball_spy;} //двигаемся влево+вниз
    
    if(UBhit()==2)
    {
         PlaySnd(SND_USER);
         StartVibra(savedata.VibraVolume,savedata.VibraCount);
      
      if(user_r)
      { 
        //if(ABS(ball_spx)<ball_max_speed && ABS(ball_spy)<ball_max_speed && ABS(ball_spx)<ball_max_speed && ABS(ball_spy)<ball_max_speed)
        //{
          if(user_c>5 && user_c<15) {ball_spx+=1;ball_spy+=1;} //прибавляем,так как цикл движения=вправо+вниз(x++ y++)
          else if(user_c>15 && user_c<25) {ball_spx+=2;ball_spy+=2;} //ускорение шарика
          else if(user_c>25 && user_c<50) {ball_spx+=3;ball_spy+=3;}
          
          //изменяем угол полета по x после столкновения
          if(user_c>0 && user_c<10) {ball_spx+=1;ball_spy+=0;}
          else if(user_c>10 && user_c<20) {ball_spx+=2;ball_spy+=0;}
          else if(user_c>20 && user_c<30) {ball_spx+=3;ball_spy+=0;}
          else if(user_c>30 && user_c<40) {ball_spx+=4;ball_spy+=0;}
          else if(user_c>40 && user_c<50) {ball_spx+=5;ball_spy+=0;}
        //}
        ball_spx=ball_spx;ball_spy=-ball_spy; //двигаемся вправо+вверх
      }
      
      if(user_l)
      {
        //if(ABS(ball_spx)>ball_min_speed && ABS(ball_spy)>ball_min_speed && ABS(ball_spx)<ball_max_speed && ABS(ball_spy)<ball_max_speed)
        //{
          if(user_c>5 && user_c<15) {ball_spx-=1;ball_spy-=1;} //прибавляем,так как цикл движения=вправо+вниз(x++ y++)
          else if(user_c>15 && user_c<25) {ball_spx-=2;ball_spy-=2;} //замедление шарика
          else if(user_c>25 && user_c<50) {ball_spx-=3;ball_spy-=3;}
          
          //изменяем угол полета по x после столкновения
          if(user_c>0 && user_c<10) {ball_spx-=1;ball_spy+=0;}
          else if(user_c>10 && user_c<20) {ball_spx-=2;ball_spy+=0;}
          else if(user_c>20 && user_c<30) {ball_spx-=3;ball_spy+=0;}
          else if(user_c>30 && user_c<40) {ball_spx-=4;ball_spy+=0;}
          else if(user_c>40 && user_c<50) {ball_spx-=5;ball_spy+=0;}
        //}
        ball_spx=-ball_spx;ball_spy=-ball_spy; //двигаемся влево+вверх
      } 
      if(!user_r && !user_l) {ball_spx=ball_spx;ball_spy=-ball_spy;} //двигаемся вправо+вверх
    }
    
     if(UBhit()==1)
     {
         PlaySnd(SND_USER);
         StartVibra(savedata.VibraVolume,savedata.VibraCount);
      if(user_r)
      {
          //изменяем угол полета по x после столкновения
          if(user_c>0 && user_c<10) {ball_spx+=0;ball_spy+=1;}
          else if(user_c>10 && user_c<20) {ball_spx+=0;ball_spy+=2;}
          else if(user_c>20 && user_c<30) {ball_spx+=0;ball_spy+=3;}
          else if(user_c>30 && user_c<40) {ball_spx+=0;ball_spy+=4;}
          else if(user_c>40 && user_c<50) {ball_spx+=0;ball_spy+=5;}
        ball_spx=ball_spx;ball_spy=-ball_spy; //двигаемся вправо+вверх
      }
      if(user_l)
      {
           //изменяем угол полета по x после столкновения
          if(user_c>0 && user_c<10) {ball_spx-=0;ball_spy-=1;}
          else if(user_c>10 && user_c<20) {ball_spx-=0;ball_spy-=2;}
          else if(user_c>20 && user_c<30) {ball_spx-=0;ball_spy-=3;}
          else if(user_c>30 && user_c<40) {ball_spx-=0;ball_spy-=4;}
          else if(user_c>40 && user_c<50) {ball_spx-=0;ball_spy-=5;}
        ball_spx=-ball_spx;ball_spy=-ball_spy; //двигаемся влево+вверх
      }
      if(!user_r && !user_l) {ball_spx=ball_spx;ball_spy=-ball_spy;} //двигаемся вправо+вверх  
     }
    
     if(UBhit()==3)
     {
         PlaySnd(SND_USER);
         StartVibra(savedata.VibraVolume,savedata.VibraCount);
       
      if(user_r)
      {
          //изменяем угол полета по x после столкновения
          if(user_c>0 && user_c<10) {ball_spx+=0;ball_spy+=1;}
          else if(user_c>10 && user_c<20) {ball_spx+=0;ball_spy+=2;}
          else if(user_c>20 && user_c<30) {ball_spx+=0;ball_spy+=3;}
          else if(user_c>30 && user_c<40) {ball_spx+=0;ball_spy+=4;}
          else if(user_c>40 && user_c<50) {ball_spx+=0;ball_spy+=5;}
        ball_spx=ball_spx;ball_spy=-ball_spy; //двигаемся влево+вверх
      }
      if(user_l)
      {
           //изменяем угол полета по x после столкновения
          if(user_c>0 && user_c<10) {ball_spx-=0;ball_spy-=1;}
          else if(user_c>10 && user_c<20) {ball_spx-=0;ball_spy-=2;}
          else if(user_c>20 && user_c<30) {ball_spx-=0;ball_spy-=3;}
          else if(user_c>30 && user_c<40) {ball_spx-=0;ball_spy-=4;}
          else if(user_c>40 && user_c<50) {ball_spx-=0;ball_spy-=5;}
        ball_spx=-ball_spx;ball_spy=-ball_spy; //двигаемся вправо+вверх
      }
      if(!user_r && !user_l) {ball_spx=ball_spx;ball_spy=-ball_spy;} //двигаемся вправо+вверх  
     }
  }
  
  
  
  
  
  if(ball_spy>0 && ball_spx<0) //влево+вниз
  {
    //if(ball_x>user_x && ball_x<user_x+user[user_s].img->w && ball_y>user_y-user[user_s].img->h) {ball_spx=ball_spx;ball_spy=-ball_spy;} //двигаемся влево+вверх
    
    //if(ball_y>=H-ball[ball_s].img->h) {ball_spx=NSM-ball_a;ball_spy=NSM-ball_a;} //двигаемся влево+вверх
    if(ball_x<=0) {ball_spx=-ball_spx;ball_spy=ball_spy;} //двигаемся вправо+вниз
    
    if(UBhit()==2)
    {
         PlaySnd(SND_USER);
         StartVibra(savedata.VibraVolume,savedata.VibraCount);
         
      if(user_r)
      {
        //if(ABS(ball_spx)>ball_min_speed && ABS(ball_spy)>ball_min_speed && ABS(ball_spx)<ball_max_speed && ABS(ball_spy)<ball_max_speed) 
        //{
          //замедляем шарик
          if(user_c>5 && user_c<15) {ball_spx+=1;ball_spy-=1;}
          else if(user_c>15 && user_c<25) {ball_spx+=2;ball_spy-=2;}
          else if(user_c>25 && user_c<50) {ball_spx+=3;ball_spy-=3;}
          
          //изменяем угол полета по x после столкновения
          if(user_c>0 && user_c<10) {ball_spx+=1;ball_spy+=0;}
          else if(user_c>10 && user_c<20) {ball_spx+=2;ball_spy+=0;}
          else if(user_c>20 && user_c<30) {ball_spx+=3;ball_spy+=0;}
          else if(user_c>30 && user_c<40) {ball_spx+=4;ball_spy+=0;}
          else if(user_c>40 && user_c<50) {ball_spx+=5;ball_spy+=0;}
          
        //}
        ball_spx=-ball_spx;ball_spy=-ball_spy; //двигаемся влево+вверх
      }
      
      if(user_l)
      {
        //if(ABS(ball_spx)<ball_max_speed && ABS(ball_spy)<ball_max_speed && ABS(ball_spx)<ball_max_speed && ABS(ball_spy)<ball_max_speed) //а тут соответственно ускоряем
        //{  
          if(user_c>5 && user_c<15) {ball_spx-=1;ball_spy+=1;}
          else if(user_c>15 && user_c<25) {ball_spx-=2;ball_spy+=2;}
          else if(user_c>25 && user_c<50) {ball_spx-=3;ball_spy+=3;}
          
           //изменяем угол полета по x после столкновения
          if(user_c>0 && user_c<10) {ball_spx-=1;ball_spy+=0;}
          else if(user_c>10 && user_c<20) {ball_spx-=2;ball_spy+=0;}
          else if(user_c>20 && user_c<30) {ball_spx-=3;ball_spy+=0;}
          else if(user_c>30 && user_c<40) {ball_spx-=4;ball_spy+=0;}
          else if(user_c>40 && user_c<50) {ball_spx-=5;ball_spy+=0;}
        //}
        ball_spx=ball_spx;ball_spy=-ball_spy; //двигаемся вправо+вверх
      } 
      if(!user_r && !user_l) {ball_spx=ball_spx;ball_spy=-ball_spy;} //двигаемся вправо+вверх
    }
    
     if(UBhit()==1)
     {
         PlaySnd(SND_USER);
         StartVibra(savedata.VibraVolume,savedata.VibraCount);
         
      if(user_r)
      {
          //изменяем угол полета по x после столкновения
          if(user_c>0 && user_c<10) {ball_spx+=0;ball_spy+=1;}
          else if(user_c>10 && user_c<20) {ball_spx+=0;ball_spy+=2;}
          else if(user_c>20 && user_c<30) {ball_spx+=0;ball_spy+=3;}
          else if(user_c>30 && user_c<40) {ball_spx+=0;ball_spy+=4;}
          else if(user_c>40 && user_c<50) {ball_spx+=0;ball_spy+=5;}
        ball_spx=-ball_spx;ball_spy=-ball_spy; //двигаемся вправо+вверх
      }
      if(user_l)
      {
           //изменяем угол полета по x после столкновения
          if(user_c>0 && user_c<10) {ball_spx-=0;ball_spy+=1;}
          else if(user_c>10 && user_c<20) {ball_spx-=0;ball_spy+=2;}
          else if(user_c>20 && user_c<30) {ball_spx-=0;ball_spy+=3;}
          else if(user_c>30 && user_c<40) {ball_spx-=0;ball_spy+=4;}
          else if(user_c>40 && user_c<50) {ball_spx-=0;ball_spy+=5;}
        ball_spx=ball_spx;ball_spy=-ball_spy; //двигаемся вправо+вверх
      }
      if(!user_r && !user_l) {ball_spx=ball_spx;ball_spy=-ball_spy;} //двигаемся вправо+вверх  
     }
    
     if(UBhit()==3)
     {
         PlaySnd(SND_USER);
         StartVibra(savedata.VibraVolume,savedata.VibraCount);
         
      if(user_r)
      {
          //изменяем угол полета по x после столкновения
          if(user_c>0 && user_c<10) {ball_spx+=0;ball_spy+=1;}
          else if(user_c>10 && user_c<20) {ball_spx+=0;ball_spy+=2;}
          else if(user_c>20 && user_c<30) {ball_spx+=0;ball_spy+=3;}
          else if(user_c>30 && user_c<40) {ball_spx+=0;ball_spy+=4;}
          else if(user_c>40 && user_c<50) {ball_spx+=0;ball_spy+=5;}
        ball_spx=-ball_spx;ball_spy=-ball_spy; //двигаемся вправо+вверх
      }
      
      if(user_l)
      {
           //изменяем угол полета по x после столкновения
          if(user_c>0 && user_c<10) {ball_spx-=0;ball_spy+=1;}
          else if(user_c>10 && user_c<20) {ball_spx-=0;ball_spy+=2;}
          else if(user_c>20 && user_c<30) {ball_spx-=0;ball_spy+=3;}
          else if(user_c>30 && user_c<40) {ball_spx-=0;ball_spy+=4;}
          else if(user_c>40 && user_c<50) {ball_spx-=0;ball_spy+=5;}
        ball_spx=ball_spx;ball_spy=-ball_spy; //двигаемся вправо+вверх
      }
      if(!user_r && !user_l) {ball_spx=ball_spx;ball_spy=-ball_spy;} //двигаемся вправо+вверх  
     }
  }
  
  
  if(abs(ball_spy)>=ball_max_speed && ball_spy>0) ball_spy=ball_max_speed;
  if(abs(ball_spy)>=ball_max_speed && ball_spy<0) ball_spy=-ball_max_speed;
  if(abs(ball_spy)<=ball_min_speed && ball_spy>0) ball_spy=ball_min_speed;
  if(abs(ball_spy)<=ball_min_speed && ball_spy<0) ball_spy=-ball_min_speed;
  
  if(abs(ball_spx)>=ball_max_speed && ball_spx>0) ball_spx=ball_max_speed;
  if(abs(ball_spx)>=ball_max_speed && ball_spx<0) ball_spx=-ball_max_speed;
  if(abs(ball_spx)<=ball_min_speed && ball_spx>0) ball_spx=ball_min_speed;
  if(abs(ball_spx)<=ball_min_speed && ball_spx<0) ball_spx=-ball_min_speed;
  
  if(!bon_slime_use)
  {
    if(ball_spx==0) ball_spx=1;
    if(ball_spy==0) ball_spy=1;
  }
  
  ball_x+=ball_spx;
  ball_y+=ball_spy;
  
  if(ball_y>=H) LoseLife(); //если  проворонили шарик,то теряем жизнь
  
   DrwImg(ball[ball_type][ball_s].img,ball_x,ball_y);
}



void DrawUser()
{
  if(!bonus_active[BON_USER_FREEZE])
  {
   if(user_r)
   {
     if(bon_slime_use) ball_x+=user_sp;
     user_x+=user_sp;
     user_c++;
   }
   else if(!user_l) user_c=0;
   if(user_l)
   {
     if(bon_slime_use) ball_x-=user_sp;
     user_x-=user_sp;
     user_c++;
   }
   else if(!user_r) user_c=0;
  }
  
  if(user_x<0) user_x=0;
  if(user_x>sw-user[user_type][user_s].img[0]->w) user_x=sw-user[user_type][user_s].img[0]->w;
  SetSpriteCoordinaties(user_N,user_x,user_y);
}







void CheckBonuses(int bnum)
{
  switch(bnum)
  {
    case BON_USER_BIG: //увеличение паддлы)
     {
       if(user_s<2) user_s++;
       StopSprite(user_N);
       user_N = InitSprite(&user[user_type][user_s],UID_OTHER,user_x,user_y,10000);
     } break;
     
    case BON_USER_SMALL: //уменьшение паддлы
     {
       if(user_s>0) user_s--;
       StopSprite(user_N);
       user_N = InitSprite(&user[user_type][user_s],UID_OTHER,user_x,user_y,10000);
     } break;
    
    case BON_USER_FREEZE: //заморозка биты на 3 сек
      {
        user_type=3;
        StopSprite(user_N);
        user_N = InitSprite(&user[user_type][user_s],UID_OTHER,user_x,user_y,10000);
        bonus_active[BON_USER_FREEZE] = 1;
        bonus_counter[BON_USER_FREEZE] = 0;
        bonus_time[BON_USER_FREEZE] = 70;
      } break;
      
    case BON_BALL_INCREASE: //ускорение шара на 1
      {
        if(ball_spx<0) ball_spx-=1;
        if(ball_spy<0) ball_spy-=1;
        if(ball_spx>0) ball_spx+=1;
        if(ball_spy>0) ball_spy+=1;
      } break;
      
    case BON_BALL_DECREASE: //замедление шара на 1
      {
        if(ball_spx<0) ball_spx+=1;
        if(ball_spy<0) ball_spy+=1;
        if(ball_spx>0) ball_spx-=1;
        if(ball_spy>0) ball_spy-=1;
      } break;
      
    case BON_LIFE: //жизнь
      {
        total_lives++;
      } break;
      
    case BON_BALL_MEGA: //super ball
      {
        bonus_active[BON_BALL_MEGA] = 1;
        bonus_active[BON_BALL_GHOST] = 0;
        bonus_counter[BON_BALL_MEGA] = 0;
        bonus_time[BON_BALL_MEGA] = 500;
        ball_type = 2;
      } break;
      
      case BON_BALL_GHOST: //ghost ball
      {
        bonus_active[BON_BALL_GHOST] = 1;
        bonus_active[BON_BALL_MEGA] = 0; //сбрасываем
        bonus_counter[BON_BALL_GHOST] = 0;
        bonus_time[BON_BALL_GHOST] = 500;
        ball_type = 1;
      } break;
      
    case 8: //стеляем пульками
      {
        user_type=1;
        StopSprite(user_N);
        user_N = InitSprite(&user[user_type][user_s],UID_OTHER,user_x,user_y,10000);
        bonus_shot_type = 0;
      } break;
      
    case 9: //стеляем рокетом
      {
        user_type=1;
        StopSprite(user_N);
        user_N = InitSprite(&user[user_type][user_s],UID_OTHER,user_x,user_y,10000);
        bonus_shot_type = 1;
      } break;
      
    case 10: //платформа-магнит
      {
        user_type = 2;
        StopSprite(user_N);
        user_N = InitSprite(&user[user_type][user_s],UID_OTHER,user_x,user_y,10000);
        bonus_active[BON_SLIME] = 1;
        bonus_counter[BON_SLIME] = 0;
        bonus_time[BON_SLIME] = 500;
      } break;
      
    case 12: //ball size ++
      {
        if(ball_s<2) ball_s++;
      } break;
      
    case 13: //ball size --
      {
        if(ball_s>0) ball_s--;
      } break;
  }
  
}

void DrawBonuses()
{
  short x,y;
  for(short i=0;i<MAX_SPRITES;i++)
  {
    if(!sprites[i].active) continue;
    if(sprites[i].uid>=0 && sprites[i].uid<=15)
    {
      GetSpriteCoordinaties(sprites[i].N,&x,&y);
      short bonusw = GetSpriteWidth(sprites[i].N);
      short bonush = GetSpriteHeight(sprites[i].N);
      if(UBNhit(x,x+bonusw,y+bonush))
      {
        StopSprite(sprites[i].N);
        CheckBonuses(sprites[i].uid);
      }
    }
  }
  
  
  for(char i=0;i<NUM_OF_BONUSES;i++) //таймеры для бонусов
  {
    if(bonus_active[i])
    {
      if(bonus_counter[i]<bonus_time[i]) bonus_counter[i]++;
      else
      {
        if(i==BON_USER_FREEZE)
        {
          user_type = 1;
          StopSprite(user_N);
          user_N = InitSprite(&user[user_type][user_s],UID_OTHER,user_x,user_y,10000);
        }
        if(i==BON_SLIME)
        {
          user_type = 1;
          StopSprite(user_N);
          user_N = InitSprite(&user[user_type][user_s],UID_OTHER,user_x,user_y,10000);
        }
        if(i==BON_BALL_MEGA || i==BON_BALL_GHOST) ball_type = 0;
        bonus_counter[i]=0;
        bonus_active[i] = 0;
      }
    }
  }
  
  /*for(char i=0;i<NUM_OF_BONUSES;i++)
  {
    if(bonus[i].active==0) continue;
    GetSpriteCoordinaties(bonus[i].N,&x,&y);
    y+=3;
    SetSpriteCoordinaties(bonus[i].N,x,y);
    if(UBNhit(x,x+bonus[i].spr.img[0]->w,y+bonus[i].spr.img[0]->h))
    {
      StopSprite(bonus[i].N);
      CheckBonuses(bonus[i].num);
      bonus[i].active = 0;
      if(bonus_counter>0) bonus_counter--;
    }
    else if(y>sh)
    {
      StopSprite(bonus[i].N);
      bonus[i].active = 0;
      if(bonus_counter>0) bonus_counter--;
    }
  }*/
}





IMGHDR *press0;





void DrawWeapons()
{
  /*short shx,shy;
  for(int i=0;i<128;i++)
  {
    GetSpriteCoordinaties(shot_n[bonus_shot_type][i],&shx,&shy);
    if(shy>offset1) SetSpriteCoordinaties(shot_n[bonus_shot_type][i],shx,shy-4);
    else {StopSprite(shot_n[bonus_shot_type][i]);}
  }*/
}



void DrawOther()
{
  DrawSprites();
  DrawWeapons();
}














void DrawBoss()
{
  boss.x=ball_x-(boss.img->w/2)+3;
  DrwImg(boss.img,boss.x,boss.y);
}




int fps;
int sfps;
int lastsec;
TDate date;
TTime time;



void DrawIconbar(WSHDR *ws)
{
  const char icbar_bgcol[4]={0,0,0,100};
  const char icbar_frcol[4]={90,90,90,90};
  DrawRoundedFrame(0,0,W-1,offset1,3,3,0,icbar_frcol,icbar_bgcol);
  if(state==STATE_GAME)
  {
    if(map.type==TYPE_NORMAL) wsprintf(ws,"%t: %d   fps: %d","жизни",total_lives,fps);
    if(map.type==TYPE_BOSS) wsprintf(ws,"%t: [%d|%d]   fps: %d","жизни",total_lives,map.boss_lives,fps);
    DrawString(ws,2,2,W/2,2+(GetFontYSIZE(FONT_SM)+2),FONT_SM,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(12),NULL);
    //wsprintf(ws,"%t:%d cleaned:%d","очки",score,clean_bricks);
    wsprintf(ws,"x:%d  y:%d",sx,sy);
    DrawString(ws,sw/2,2,sw-2,2+(GetFontYSIZE(FONT_SM)+2),FONT_SM,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(12),NULL); 
  }
  else
  {
    wsprintf(ws,"bat: %d%",*RamCap());
    DrawString(ws,2,2,sw/2,2+(GetFontYSIZE(FONT_SM)+2),FONT_SM,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(12),NULL);
    TDate date;
    TTime time;
    GetDateTime(&date,&time);
    wsprintf(ws,"%d:%d",time.hour,time.min);
    DrawString(ws,sw/2,2,sw-2,2+(GetFontYSIZE(FONT_SM)+2),FONT_SM,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(12),NULL);
  }
}








void TimerRedrawScreen()
{
  WSHDR *wws=AllocWS(128);
  sfps++;
  GetDateTime(&date,&time);
  if(lastsec!=time.sec)
  {
    lastsec = time.sec;
    fps = sfps;
    sfps = 0;
  }

  
  if(state==STATE_GAME)
  {
    if(clean_bricks>=bricks_of_clean)
    {
      PrepareLevel((levelcounter++)+1);
    }
    
    DrwImg(level_bg,0,0);
    DrawBricks();
    DrawBall();
    DrawUser();
    if(map.type==TYPE_BOSS) DrawBoss();
    DrawBonuses();
    DrawOther();
  }
    else if(state==STATE_MENU || state==STATE_ABOUT ||
      state==STATE_SETTINGS || state==STATE_RECORDS ||
      state==STATE_SLEVEL)
    {
      DrawMenu();
    }
  
  if(state==STATE_DBG_SETBALL)
  {
    DrwImg(level_bg,0,0);
    DrwImg(ball[ball_type][ball_s].img,ball_x,ball_y);
  }
  
  if(state==STATE_PRESS) //что-то произошло,и что-то выводим на экран,после нажатия на "0" игра продолжается
  {
    const char bgcol[4]={30,30,30,50};
    const char frcol[4]={190,190,190,100};
    const char strcol[4]={250,250,250,100};
    short y1 = (sh/2)-(sh/4);
    short y2 = (sh/2)+(sh/4);
    DrawRoundedFrame(0,y1,sw-1,y2,4,4,0,frcol,bgcol);
    wsprintf(wws,perc_t,press_msg);
    DrawString(wws,0,y1+4,sw-1,y2-4,FONT_MD,TEXT_ALIGNMIDDLE,strcol,NULL);
    DrwImg(press0,(sw/2)-(press0->w/2),y2-press0->h-2);
  }
  DrawIconbar(wws);
  FreeWS(wws);
  //LCD_Redraw();
  if(savedata.tmr_speed<4 || savedata.tmr_speed>15) savedata.tmr_speed=9;
  if(state==STATE_GAME) {GBS_StartTimerProc(&gametimer,savedata.tmr_speed,TimerRedrawScreen);}
}





void moveuser(GUI_MSG *msg)
{
  if(msg->gbsmsg->msg==KEY_DOWN)
  {
    if(msg->gbsmsg->submess=='6' || msg->gbsmsg->submess==RIGHT_BUTTON) user_r=1;
    if(msg->gbsmsg->submess=='4' || msg->gbsmsg->submess==LEFT_BUTTON) user_l=1;
    if(msg->gbsmsg->submess=='5' || msg->gbsmsg->submess==ENTER_BUTTON && bonus_active[BON_SLIME]) //нажали и мяч полетеел..
    {
      if(bon_slime_use)
      {
        ball_spx = -mem_ball_spx; //в обр сторону
        ball_spy = -abs(mem_ball_spy); //вверх
        bon_slime_use=0; //самоотключалка
      }
    }
  }
  
  if(msg->gbsmsg->msg==KEY_UP)
  {
    if(msg->gbsmsg->submess=='6' || msg->gbsmsg->submess==RIGHT_BUTTON) user_r=0;
    if(msg->gbsmsg->submess=='4' || msg->gbsmsg->submess==LEFT_BUTTON) user_l=0;
  }
}




void debug_keys(GUI_MSG *msg)
{
  if(msg->gbsmsg->msg==KEY_DOWN || msg->gbsmsg->msg==LONG_PRESS)
  {
    if(msg->gbsmsg->submess=='6') {ball_x+=4;TimerRedrawScreen();return;}
    if(msg->gbsmsg->submess=='4') {ball_x-=4;TimerRedrawScreen();return;}
    if(msg->gbsmsg->submess=='8') {ball_y+=4;TimerRedrawScreen();return;}
    if(msg->gbsmsg->submess=='2') {ball_y-=4;TimerRedrawScreen();return;}
    
    //if(msg->gbsmsg->submess=='0') {state=STATE_GAME;TimerRedrawScreen();return;}
  }
}

void check_shoot(GUI_MSG *msg)
{
  static int counter = 0;
  if(msg->gbsmsg->msg==KEY_DOWN || msg->gbsmsg->msg==LONG_PRESS)
  {
    if((msg->gbsmsg->submess=='5' || msg->gbsmsg->submess==ENTER_BUTTON) && bonus_shot_type>=0)
    {
      char n;
      char uid;
      switch(bonus_shot_type)
      {
        case 0: n=4;uid=UID_WEAPON_PISTOL;break;
        case 1: n=8;uid=UID_WEAPON_ROCKET;break;
      }
      if(counter>n) //струляем
      {
        InitMSprite(&weapon_shot[bonus_shot_type],uid,(user_x+user[user_type][user_s].img[0]->w/2)-(weapon_shot[bonus_shot_type].img[0]->w/2),user_y-2,0,-3,0,offset1);
        counter=0;
        return;
      }
    }
  }
  counter++;
}







int Keyhook(GUI_MSG *msg)
{
  if(state==STATE_MENU || state==STATE_ABOUT ||
     state==STATE_SETTINGS || state==STATE_RECORDS ||
     state==STATE_SLEVEL) return(MenuNavigation(msg)); //если меню активно,то юзаем только кнопы меню
  if(state==STATE_GAME)
  {
    moveuser(msg);
    check_shoot(msg);
  }
  
  if(state==STATE_DBG_SETBALL) debug_keys(msg);
  
  if(msg->gbsmsg->msg==KEY_DOWN)
  {
    if(msg->gbsmsg->submess==RIGHT_SOFT && state==STATE_GAME)  //заходим из игры в меню
    {
       PlayMusic(MENU_MUSIC);
       state=STATE_MENU;//переходим в меню
       cont=1; //ставим флаг на продолжение игры
       GBS_StartTimerProc(&gametimer,25,TimerRedrawScreen); //пускаем рисование
       return 0;
    } 
    if(msg->gbsmsg->submess=='0')
    {
      if(state==STATE_PRESS)
      {
      if(press_type==PRESS_GAMEOVER) //сдули нахъ или выиграли =)
      {
        SetDefaultGameParameters();
        state = STATE_MENU;
        CreateTextEditDialog(0,"ваше имя",32);
      }
      else if(press_type==PRESS_LOSELIFE) //лайф потеряли
      {
        state = STATE_GAME;
        TimerRedrawScreen();
      }
      else if(press_type==PRESS_NEWLEVEL) //новый левел
      {
        state = STATE_GAME;
        TimerRedrawScreen();
      }
      else //xz
      {
        state = STATE_GAME;
        TimerRedrawScreen();
      }
      return 0;
      }
      else if(state==STATE_GAME)
      {
        //DumpMap(UsedLevel,levelcounter);
       //LCD_DrawImage(user[user_s].img,100,100);
        //LCD_Redraw();
        //SUBPROC((void*)Test);
        //state = STATE_DBG_SETBALL;
       
        short N;
        int x=0;
        for(int i=0;i<6;i++)
        {
          N = InitSprite(&mine_sparks,126,x,150,1);
          x+=35;
        }
        GetSpriteCoordinaties(N,&sx,&sy);
        sprintf(lgn,"TEST=> N:%d,sx: %d,sy:%d",N,sx,sy);log(lgn);
        
        return 0;
      }
    }
    
    
    
    
    
    if(msg->gbsmsg->submess=='1') {InitMSprite(&weapon_shot[0],195,user_x+10,user_y-2,0,-3,0,offset1+30);return 0;}
    if(msg->gbsmsg->submess=='3') {InitMSprite(&weapon_shot[1],195,user_x+10,user_y-2,0,-3,0,offset1+30);return 0;}
    if(msg->gbsmsg->submess=='7') {bonus_shot_type=0;return 0;}
    if(msg->gbsmsg->submess=='9') {bonus_shot_type=1;return 0;}
    
    if(msg->gbsmsg->submess=='*')
    {
      sprintf(press_msg,"op. levels: %d",savedata.opened_levels);
      press_type = 50; //xz
      GBS_StartTimerProc(&press_tmr,6,PressTimerFunc);
    }
    if(msg->gbsmsg->submess=='#')
    {
      sprintf(press_msg,"сброшено");
      clean_bricks = bricks_of_clean;
      press_type = 50; //xz
      GBS_StartTimerProc(&press_tmr,6,PressTimerFunc);
    }
    
    //if(msg->gbsmsg->submess=='*') {sxx++;return 0;}
    //if(msg->gbsmsg->submess=='#') {sxx--;StartVibra(20,20);return 0;}
    //if(msg->gbsmsg->submess=='1') {AI_df--;return 0;}
    //if(msg->gbsmsg->submess=='3') {AI_df++;return 0;}
    
  }
  return 0;
}



IMGHDR *ImageLoadFromFile(char *name,int type) //это мне было лень переписывать загрузку бонусов.. =)
{
  char temp[512];
  sprintf(temp,"%s%s",pwd,name);
  return(CreateIMGHDRFromPngFile(temp,2));
}






void LoadOther(char *p)
{
  //defense.img = ImageLoadFromFile("pics\\items\\defense.png",1);
  //defense.x = 0; defense.y = sh-defense.img->h; defense.stats = 0;
  
  InitSpriteBuffer();
  LoadSprite("pics\\items\\brick_sparks.png",3,2,&brick_sparks);
  LoadSprite("pics\\items\\mine_sparks.png",4,2,&mine_sparks);
  LoadSprite("pics\\items\\rocket_sparks.png",7,2,&rocket_sparks);
  
  LoadSprite("pics\\items\\pistol_shot.png",3,2,&weapon_shot[0]);
  LoadSprite("pics\\items\\rocket_shot.png",3,2,&weapon_shot[1]);
  
  log("items ok");
}

void LoadBricks(char *p)
{
  for(char i=0;i<NUM_BRICKS;i++)
  {
    sprintf(p,"pics\\brick%d.png",i+1);
    brick[i].img = ImageLoadFromFile(p,1);
  }
  log("bricks ok");
}







void Init()
{
  log("called function init");
  char img_path[512];
  
  sprintf(img_path,"%s%s",pwd,"pics\\press0.png");
  press0 = CreateIMGHDRFromPngFile(img_path,2);
  log("press0 ok");
  
  offset1 = 2+GetFontYSIZE(FONT_SM);
  
  sprintf(img_path,"%s%s",pwd,"pics\\boss.png");
  boss.img=CreateIMGHDRFromPngFile(img_path,2);
  boss.y = offset1;
  boss.x = (ScreenW()/2)-(boss.img->w/2);
  log("boss ok");
  
  LoadOther(img_path);
  LoadBricks(img_path);
  
  /*sprintf(img_path,"%s%s",pwd,"pics\\brick1.png");
  brick[0].img=CreateIMGHDRFromPngFile(img_path,2); //обычный брик
  log("brick 1 ok");
    sprintf(img_path,"%s%s",pwd,"pics\\brick2.png");
  brick[1].img=CreateIMGHDRFromPngFile(img_path,2); //обычный брик
  log("brick 2 ok");
    sprintf(img_path,"%s%s",pwd,"pics\\brick3.png");
  brick[2].img=CreateIMGHDRFromPngFile(img_path,2); //обычный брик
  log("brick 3 ok");
    sprintf(img_path,"%s%s",pwd,"pics\\brick4.png");
  brick[3].img=CreateIMGHDRFromPngFile(img_path,2); //2 попадания
  log("brick 4 ok");
    sprintf(img_path,"%s%s",pwd,"pics\\brick5.png");
  brick[4].img=CreateIMGHDRFromPngFile(img_path,2); //3 попадания
  log("brick 5 ok");
  
    sprintf(img_path,"%s%s",pwd,"pics\\brick_wall.png");
  brick[5].img=CreateIMGHDRFromPngFile(img_path,2); //неразбиваемый брик
  log("brick 6 ok");
    sprintf(img_path,"%s%s",pwd,"pics\\brick_bon.png");
  brick[6].img=CreateIMGHDRFromPngFile(img_path,2); //брик,"содержащий" бонус
  log("brick 7 ok");
    sprintf(img_path,"%s%s",pwd,"pics\\brick_teleport.png");
  brick[7].img=CreateIMGHDRFromPngFile(img_path,2); //брик-телепорт
  log("brick 8 ok");
    sprintf(img_path,"%s%s",pwd,"pics\\brick_mine.png");
  brick[8].img=CreateIMGHDRFromPngFile(img_path,2); //брик-мина,взрывает вокруг себя 4 любых брика,кроме телепортов
  log("bricks ok");*/
  
  
  for(char i=0;i<3;i++)
  {
    for(char t=0;t<3;t++)
    {
      sprintf(img_path,"pics\\ball%d_%d.png",i,t);
      ball[i][t].img = ImageLoadFromFile(img_path,1);
    }
  }
  
  for(char i=0;i<4;i++)
  {
    for(char t=0;t<3;t++)
    {
      sprintf(img_path,"pics\\user%d_%d.png",i,t);
      LoadSprite(img_path,3,6,&user[i][t]); //!!
    }
  }
  
  for(char i=0;i<NUM_OF_BONUSES;i++)
  {
    sprintf(img_path,"pics\\bon_%d.png",i);
    LoadSprite(img_path,1,1,&bonus[i].spr);
    bonus_counter[i]=0;
    bonus_active[i]=0;
  }
  log("images loaded");
  
  
  
  
  
  SetDefaultGameParameters();
  user_N = InitSprite(&user[user_type][user_s],UID_OTHER,user_x,user_y,10000); //резервируем user_N ячейку буфера
  log("parameters ok");
  
  
  
  
  
  loadSettings(); //грузим сохраненные настройки
  log("settings ok");
  SetDifficulty();
  
  InitMenu();
  
  log("all initialised!");
  state=STATE_MENU;
  
  PlayMusic(MENU_MUSIC);
  
  cont=0;
  
  extern char loading;
  loading = 0;
  log("menu_music ok");
  ifree(load_screen);
  log("Init func ok");
  TimerRedrawScreen();
}





void ifree(IMGHDR *img)
{
  if(img!=NULL)
  {
    if(img && img->bitmap) {mfree(img->bitmap);mfree(img);}
  }
}
void imfree(image img)
{
  if(img.img!=NULL)
  {
    if(img.img && img.img->bitmap) {mfree(img.img->bitmap);mfree(img.img);}
  }
}

void FreeMemory()
{
  log("freememory...");
  
  DeinitMenu();
  PlayMelody_StopPlayback(PLAY_ID);
  ifree(level_bg);
  
  imfree(boss);
  
  ifree(press0);
  
  for(char i=0;i<3;i++)
  {
    imfree(ball[i][0]);
    imfree(ball[i][1]);
    imfree(ball[i][2]);
  }
  for(char i=0;i<4;i++)
  {
    FreeSprite(&user[i][0]);
    FreeSprite(&user[i][1]);
    FreeSprite(&user[i][2]);
  }
  
  for(int i=0;i<8;i++)
  {
    imfree(brick[i]);
  }
  
  
  for(int i=0;i<NUM_OF_BONUSES;i++)
  {
    FreeSprite(&bonus[i].spr);
  }
  
  DeinitSpriteBuffer();
  FreeSprite(&brick_sparks);
  FreeSprite(&mine_sparks);
  FreeSprite(&rocket_sparks);
  FreeSprite(&weapon_shot[0]);
  FreeSprite(&weapon_shot[1]);
  
  if(savedata.recs_autosave)
  {
    char *nn = malloc(64);
    TDate d;TTime t;
    GetDateTime(&d,&t);
    sprintf(nn,"%d/%0d/%d_%d:%0d",d.day,d.month,d.year,t.hour,t.min);
    CopyRecords(nn);
    mfree(nn);
  }
  saveSettings(); //сохраняем пройденное
  
  log("completed!");
}
