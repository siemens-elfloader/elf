#include "..\inc\swilib.h"
#include "engine.h"
#include "config.h"
#include "SpriteLoader.h"



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
image ball[3];  short ball_x,ball_y,ball_s=0,ball_spx,ball_spy;
image user[9]; short user_x,user_y,user_s=2,user_l=0,user_r=0,user_sp=5;
int user_c; //время,которое платформа находится в движении



TSPRITE brick_sparks;
TSPRITE mine_sparks;




TSPRITE weapon_shot[2]; //rocket and pistol
short shot_n[2][32]; //номера "пулек" для каждого оружия
short shot_counter = 0; //это тупо счетчик
signed char bonus_shot_type = -1; //-1 - не стреляем



image boss;

char offset1; //основной оффсет прорисовки


#define NUM_OF_BONUSES 16
#define MAX_BONUS_DRAWS 9
image bonus[NUM_OF_BONUSES];
char bonus_speed=4;
short bonus_drawnum[NUM_OF_BONUSES]; //для каждого бонуса количество прорисовок
short bonusx[NUM_OF_BONUSES][MAX_BONUS_DRAWS];
short bonusy[NUM_OF_BONUSES][MAX_BONUS_DRAWS];
char bonus_allowdraw[NUM_OF_BONUSES][MAX_BONUS_DRAWS];

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
  if(ball_x>=boss.x-6 && ball_x+ball[ball_s].img->w<=boss.x+boss.img->w && ball_y<=boss.y+boss.img->h) return 1;
  else return 0;
}




char SBhit(image brick,char num) //проверка на столкновение пульки(или ракеты) с мячом.Стену(num==7) пулька не разрушит,а ракета вполне
{
  //проверка только на нижнюю сторону брика
  short x,y,x2;
  
  RECT br;
  br.x = brick.x;
  br.y = brick.y;
  br.x2 = br.x+brick.img->w;
  br.y2 = br.y+brick.img->h;
  for(char i=0;i<32;i++) //каждую пульку внимательно проверим..
  {
    GetSpriteCoordinaties(shot_n[bonus_shot_type][i],&x,&y); //взяли координаты пульки
    x2 = x+GetSpriteWidth(shot_n[bonus_shot_type][i]);
    if(((x2>=br.x && x2<=br.x2) || (x>=br.x && x<=br.x2)) && y>=br.y && y<=br.y2) //берем по крайним иксам
    {
      //SetSpriteCoordinaties(shot_n[i],x,0);
      StopSprite(shot_n[bonus_shot_type][i]);
      return 1;
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
  bl.x2 = bl.x+ball[ball_s].img->w;
  bl.y2 = bl.y+ball[ball_s].img->h;
  
  
  
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
  //столкновение с левым краем
  if(ball_x+(ball[ball_s].img->w/2) > user_x  &&  ball_x+(ball[ball_s].img->w/2) < user_x+(user[user_s].img->w/4) && ball_y+ball[ball_s].img->h > user_y) return 1;
  //столкновение с центром платформы
  if(ball_x+(ball[ball_s].img->w/2) > user_x+(user[user_s].img->w/4)  &&  ball_x+(ball[ball_s].img->w/2) < user_x+((user[user_s].img->w/4)*3) && ball_y+ball[ball_s].img->h > user_y) return 2;
  //столкновение с правым краем
  if(ball_x+(ball[ball_s].img->w/2) > user_x+((user[user_s].img->w/4)*3)  &&  ball_x+(ball[ball_s].img->w/2) < user_x+user[user_s].img->w && ball_y+ball[ball_s].img->h > user_y) return 3;
  return 0; //если не столкнулись,то выходим с нулем
}
char UBNhit(image bonus,int bx,int by) //столкновение юзера с бонусами
{
  if(bx+bonus.img->w>user_x && bx<user_x+user[user_s].img->w && by+bonus.img->h>user_y && by<user_y+user[user_s].img->h) return 1;
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
  total_lives = 3;
  //score = 0;
  cont = 0;
  ball_x=sw/2;
  ball_y=sh/2;
  user_x=(sw/2)-(user[user_s].img->w/2);
  user_y=sh-user[user_s].img->h-1;
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
  
  user_x = (sw/2)-(user[user_s].img->w/2);
  user_y = sh-user[user_s].img->h;
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














void SetCell(char x,char y,char value)
{
  if(x<MAX_WIDTH && y<MAX_HEIGHT) UsedLevel[y][x] = value;
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
          //если столкнулись с бриком
          if(CheckAndChangeBallState(brick[b_num],x,y,0)==1 || SBhit(brick[b_num],num))
          {
            if(num==1 || num==2 || num==3) {SetCell(x,y,0);clean_bricks++;InitSprite(&brick_sparks,brick[b_num].x,brick[b_num].y,1);} //на месте исчезновения брика рисуем искры типа
            if(num==4) {SetCell(x,y,3);clean_bricks++;InitSprite(&brick_sparks,brick[b_num].x,brick[b_num].y,1);}
            if(num==5) {SetCell(x,y,4);clean_bricks++;InitSprite(&brick_sparks,brick[b_num].x,brick[b_num].y,1);}
            if(num==7)
            {
              SetCell(x,y,0);
              SetCell(x+1,y,0);
              SetCell(x-1,y,0);
              SetCell(x,y-1,0);
              SetCell(x,y+1,0);
              SetCell(x-1,y-1,0);
              SetCell(x+1,y+1,0);
              SetCell(x+1,y-1,0);
              SetCell(x-1,y+1,0);
              InitSprite(&mine_sparks,brick[b_num].x,brick[b_num].y,1);
            }
            
            
            score+=20;
          }
      }
      else if(num>=20 && num<=35) //бонусы
      {
        brick[8].y=br_draw_offset+brick[8].img->h*y;                          //установка позиции прорисовки бонусного брика
        brick[8].x=brick[8].img->w*x;                          //установка позиции прорисовки бонусного брика
        DrwImg(brick[8].img,brick[8].x,brick[8].y);   //сама прорисовка, как говорится по месту
        //чекаем шарик на скорость и направление +изменяем их на соответствующие
        if(CheckAndChangeBallState(brick[8],x,y,0)==1 || SBhit(brick[8],num)) //если возвращает 1,знач шарик столкнулся с бриком(здесь - бонусным)
        {  
          char bonusnumber=GetCell(x,y)-20;
          //if(bonusnumber<0 || bonusnumber>5) log("err");
          //несколько малопонятные замуты с индексами ;)
          SetCell(x,y,0); //делаем брик,в который врезались невидимым
          clean_bricks++; //увеличиваем счетчик побитых бриков
          score+=25;
          bonusx[bonusnumber][bonus_drawnum[bonusnumber]]=brick[8].x; //установка позиции для bonus[] подиндекса bonus_drawnum[]
          if(bonusx[bonusnumber][bonus_drawnum[bonusnumber]]>W-bonus[bonusnumber].img->w) bonusx[bonusnumber][bonus_drawnum[bonusnumber]]=W-bonus[bonusnumber].img->w; //чтобы x бонуса не выходил за экран
          if(bonusx[bonusnumber][bonus_drawnum[bonusnumber]]<0) bonusx[bonusnumber][bonus_drawnum[bonusnumber]]=0+bonus[bonusnumber].img->w; //чтобы x бонуса не выходил за экран
         
          bonusy[bonusnumber][bonus_drawnum[bonusnumber]]=brick[8].y; //установка позиции для bonus[] подиндекса bonus_drawnum[]
          bonus_allowdraw[bonusnumber][bonus_drawnum[bonusnumber]]=1; //разрешаем бонусу рисоваться,надо для снятия прорисовки лишних бонусов
          if(bonus_drawnum[bonusnumber]<MAX_BONUS_DRAWS) bonus_drawnum[bonusnumber]+=1;
          else bonus_drawnum[bonusnumber]=0;
        }
      }
    }
  }
}



/*
void DrawBricks()
{
  for(int lp=0;lp<MAX_WIDTH*MAX_HEIGHT;lp++)
  {
    
    
    
    if(UsedLevel[ly][lx]==1)
    {
         brick[0].y=br_draw_offset+brick[0].img->h*ly;
         brick[0].x=0+brick[0].img->w*lx;
         DrwImg(brick[0].img,brick[0].x,brick[0].y);
         //чекаем шарик на скорость и направление +изменяем их на соответствующие
         if(CheckAndChangeBallState(brick[0],0) || bon_ball==1) {UsedLevel[ly][lx] = 0;clean_bricks+=1;score+=20;} //делаем брик,в который врезались невидимым 
     }
    
     if(UsedLevel[ly][lx]==2)
       {
         brick[1].y=br_draw_offset+brick[1].img->h*ly;
         brick[1].x=0+brick[1].img->w*lx;
         DrwImg(brick[1].img,brick[1].x,brick[1].y);
         //чекаем шарик на скорость и направление +изменяем их на соответствующие
         if(CheckAndChangeBallState(brick[1],1) || bon_ball==1) {UsedLevel[ly][lx] = 0;clean_bricks+=1;score+=20;} //делаем брик,в который врезались невидимым 
       }
    
     if(UsedLevel[ly][lx]==3)
       {
         brick[2].y=br_draw_offset+brick[2].img->h*ly;
         brick[2].x=0+brick[2].img->w*lx;
         DrwImg(brick[2].img,brick[2].x,brick[2].y);
         //чекаем шарик на скорость и направление +изменяем их на соответствующие
         if(CheckAndChangeBallState(brick[2],2) || bon_ball==1) {UsedLevel[ly][lx] = 0;clean_bricks+=1;score+=20;} //делаем брик,в который врезались невидимым 
       }
    
      if(UsedLevel[ly][lx]==4)
       {
         brick[3].y=br_draw_offset+brick[3].img->h*ly;
         brick[3].x=0+brick[3].img->w*lx;
         DrwImg(brick[3].img,brick[3].x,brick[3].y);
         //чекаем шарик на скорость и направление +изменяем их на соответствующие
         if(CheckAndChangeBallState(brick[3],3) || bon_ball==1) {UsedLevel[ly][lx] = 3;clean_bricks+=1;score+=20;} //
       }
        
       if(UsedLevel[ly][lx]==5)
       {
         brick[4].y=br_draw_offset+brick[4].img->h*ly;
         brick[4].x=0+brick[4].img->w*lx;
         DrwImg(brick[4].img,brick[4].x,brick[4].y);
         //чекаем шарик на скорость и направление +изменяем их на соответствующие
         if(CheckAndChangeBallState(brick[4],4) || bon_ball==1) {UsedLevel[ly][lx] = 4;clean_bricks+=1;score+=20;} //
       }
       if(UsedLevel[ly][lx]==6)
       {
         brick[5].y=br_draw_offset+brick[5].img->h*ly;
         brick[5].x=0+brick[5].img->w*lx;
         DrwImg(brick[5].img,brick[5].x,brick[5].y);
         //чекаем шарик на скорость и направление +изменяем их на соответствующие
         CheckAndChangeBallState(brick[5],5);
       }
      //семерки как таковой вообще нету,она типа должна была быть бонусом,потом я изменил алгоритм,и она ни туды ни сюды..
       if(UsedLevel[ly][lx]==8)
       {
         brick[7].y=br_draw_offset+brick[7].img->h*ly;
         brick[7].x=0+brick[7].img->w*lx;
         DrwImg(brick[7].img,brick[7].x,brick[7].y);
         //чекаем шарик на скорость и направление +изменяем их на соответствующие
         if(CheckAndChangeBallState(brick[7],7))  {UsedLevel[ly][lx] = 0;clean_bricks+=1;score+=20;}
       }
       if(UsedLevel[ly][lx]==9)
       {
         brick[8].y=br_draw_offset+brick[8].img->h*ly;
         brick[8].x=0+brick[8].img->w*lx;
         DrwImg(brick[8].img,brick[8].x,brick[8].y);
         //чекаем шарик на скорость и направление +изменяем их на соответствующие
         if(CheckAndChangeBallState(brick[8],8))  {UsedLevel[ly][lx] = 0;clean_bricks+=1;score+=20;}
       }
    
      CheckBonusesBricks(); //бонусные брики выносим в отдельную функцию
     
     
    lx++;
    if(lx==MAX_WIDTH) {lx=0;ly+=1;}
  }
  lx=0;ly=0;
}
*/






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
     if(ball_x>=W-ball[ball_s].img->w) {ball_spx=-ball_spx;ball_spy=ball_spy;} //двигаемся влево+вверх
     
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
   
   

  
  if(ball_spy>0 && ball_spx>0) //вправо+вниз
  {
    
    if(ball_x>=W-ball[ball_s].img->w) {ball_spx=-ball_spx;ball_spy=ball_spy;} //двигаемся влево+вниз
    
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
  
  if(ball_spx==0) ball_spx=1;
  if(ball_spy==0) ball_spy=1;
  
  ball_x+=ball_spx;
  ball_y+=ball_spy;
  
  if(ball_y>=H) LoseLife(); //если  проворонили шарик,то теряем жизнь
  
  switch(ball_s)
  {
   case 0: DrwImg(ball[0].img,ball_x,ball_y); break;
   case 1: DrwImg(ball[1].img,ball_x,ball_y); break;
   case 2: DrwImg(ball[2].img,ball_x,ball_y); break;
  }
  
}


int bon_user_stop=0; //для работы bonus[2]
int bon_user_stop_counter; //счетчик для работы того-же бонуса
void DrawUser()
{
  if(!bon_user_stop)
  {
   if(user_r) {user_x+=user_sp;user_c++;}
   else if(!user_l) user_c=0;
   if(user_l) {user_x-=user_sp;user_c++;}
   else if(!user_r) user_c=0;
  }
  else {bon_user_stop_counter++;if(bon_user_stop_counter>70) {bon_user_stop_counter=0;bon_user_stop=0;}}
  
  if(user_x<0) user_x=0;
  if(user_x>sw-user[user_s].img->w) user_x=sw-user[user_s].img->w;
  
  switch(user_s)
  {
  case 0: {DrwImg(user[0].img,user_x,user_y); }break; //small0
  case 1: {DrwImg(user[1].img,user_x,user_y); }break; //small1
  case 2: {DrwImg(user[2].img,user_x,user_y); }break; //normal0
  case 3: {DrwImg(user[3].img,user_x,user_y); }break; //normal1
  case 4: {DrwImg(user[4].img,user_x,user_y); }break; //big0
  case 5: {DrwImg(user[5].img,user_x,user_y); }break; //big1
  }
}







void CheckBonuses(int bnum)
{
  switch(bnum)
  {
    case 0: //увеличение паддлы)
     {
       switch(user_s)
       {
       case 0: {user_s=2;} break;
       case 1: {user_s=3;} break;
       case 2: {user_s=4;} break;
       case 3: {user_s=5;} break;
       }
     } break;
     
    case 1: //уменьшение паддлы
     {
       switch(user_s)
       {
       case 2: {user_s=0;} break;
       case 3: {user_s=1;} break;
       case 4: {user_s=2;} break;
       case 5: {user_s=3;} break;
       }
     } break;
    
    case 2: //заморозка биты на 3 сек
      {
        bon_user_stop=1;
      } break;
      
    case 3: //ускорение шара на 1
      {
        if(ball_spx<0) ball_spx-=1;
        if(ball_spy<0) ball_spy-=1;
        if(ball_spx>0) ball_spx+=1;
        if(ball_spy>0) ball_spy+=1;
      } break;
      
    case 4: //замедление шара на 1
      {
        if(ball_spx<0) ball_spx+=1;
        if(ball_spy<0) ball_spy+=1;
        if(ball_spx>0) ball_spx-=1;
        if(ball_spy>0) ball_spy-=1;
      } break;
      
    case 5: //жизнь
      {
        total_lives++;
      } break;
      
    case 6: //super ball
      {
        bon_ball = 1;
      } break;
  }
  
}

void DrawBonuses()
{
  for(int num=0;num<NUM_OF_BONUSES;num++)
  {
    for(int i=0;i<bonus_drawnum[num];i++)
    {
      if(bonus_allowdraw[num][i]) DrwImg(bonus[num].img,bonusx[num][i],bonusy[num][i]);
      bonusy[num][i]+=2;
      if(bonusy[num][i]>H) bonus_allowdraw[num][i]=0;
      if(UBNhit(bonus[num],bonusx[num][i],bonusy[num][i]))
      {
        bonusx[num][i]=500;
        bonusy[num][i]=500;
        CheckBonuses(num);
      }
    }
  }
}





IMGHDR *press0;

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





void DrawWeapons()
{
  short shx,shy;
  for(int i=0;i<128;i++)
  {
    GetSpriteCoordinaties(shot_n[bonus_shot_type][i],&shx,&shy);
    if(shy>offset1) SetSpriteCoordinaties(shot_n[bonus_shot_type][i],shx,shy-4);
    else {StopSprite(shot_n[bonus_shot_type][i]);}
  }
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



int Ti = 0;



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
    DrwImg(ball[ball_s].img,ball_x,ball_y);
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



void moveuser(GUI_MSG *msg)
{
  if(msg->gbsmsg->msg==KEY_DOWN)
  {
    if(msg->gbsmsg->submess=='6' || msg->gbsmsg->submess==RIGHT_BUTTON) user_r=1;
    if(msg->gbsmsg->submess=='4' || msg->gbsmsg->submess==LEFT_BUTTON) user_l=1;
  }
    if(msg->gbsmsg->msg==KEY_UP)
  {
    if(msg->gbsmsg->submess=='6' || msg->gbsmsg->submess==RIGHT_BUTTON) user_r=0;
    if(msg->gbsmsg->submess=='4' || msg->gbsmsg->submess==LEFT_BUTTON) user_l=0;
  }
  //DirectRedrawGUI();
}




void Test()
{
  Ti++;
  Test();
  
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
      switch(bonus_shot_type)
      {
        case 0: n=3;break;
        case 1: n=6;break;
      }
      if(counter>n)
      {
        shot_n[bonus_shot_type][shot_counter] = InitSprite(&weapon_shot[bonus_shot_type],(user_x+user[user_s].img->w/2)-(weapon_shot[bonus_shot_type].img[0]->w/2),user_y-2,10000); //10000 думаю хватит :D
        if(shot_counter<32) shot_counter++;
        else shot_counter = 0; 
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
          N = InitSprite(&mine_sparks,x,150,1);
          x+=35;
        }
        GetSpriteCoordinaties(N,&sx,&sy);
        sprintf(lgn,"TEST=> N:%d,sx: %d,sy:%d",N,sx,sy);log(lgn);
        
        return 0;
      }
    }
    
    
    
    
    
    if(msg->gbsmsg->submess=='1') {brick_sparks.time-=1;mine_sparks.time-=1;return 0;}
    if(msg->gbsmsg->submess=='3') {brick_sparks.time+=1;mine_sparks.time+=1;return 0;}
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
  
  
  sprintf(img_path,"%s%s",pwd,"pics\\ball1.png"); //normal ball
  ball[0].img=CreateIMGHDRFromPngFile(img_path,2);
  sprintf(img_path,"%s%s",pwd,"pics\\ball2.png"); //medium ball
  ball[1].img=CreateIMGHDRFromPngFile(img_path,2);
  sprintf(img_path,"%s%s",pwd,"pics\\ball3.png"); //very large ball
  ball[2].img=CreateIMGHDRFromPngFile(img_path,2);
  log("ball ok");
  
  
  sprintf(img_path,"%s%s",pwd,"pics\\user_small0.png");
  user[0].img=CreateIMGHDRFromPngFile(img_path,2);
  sprintf(img_path,"%s%s",pwd,"pics\\user_small1.png");
  user[1].img=CreateIMGHDRFromPngFile(img_path,2);
  sprintf(img_path,"%s%s",pwd,"pics\\user_normal0.png");
  user[2].img=CreateIMGHDRFromPngFile(img_path,2);
  sprintf(img_path,"%s%s",pwd,"pics\\user_normal1.png");
  user[3].img=CreateIMGHDRFromPngFile(img_path,2);
  sprintf(img_path,"%s%s",pwd,"pics\\user_big0.png");
  user[4].img=CreateIMGHDRFromPngFile(img_path,2);
  sprintf(img_path,"%s%s",pwd,"pics\\user_big1.png");
  user[5].img=CreateIMGHDRFromPngFile(img_path,2);
  log("user ok");
  
   
  bonus[0].img=(IMGHDR*)ImageLoadFromFile("pics\\bon_0.png",1);
  bonus[1].img=(IMGHDR*)ImageLoadFromFile("pics\\bon_1.png",1);
  bonus[2].img=(IMGHDR*)ImageLoadFromFile("pics\\bon_2.png",1);
  bonus[3].img=(IMGHDR*)ImageLoadFromFile("pics\\bon_3.png",1);
  bonus[4].img=(IMGHDR*)ImageLoadFromFile("pics\\bon_4.png",1);
  bonus[5].img=(IMGHDR*)ImageLoadFromFile("pics\\bon_5.png",1);
  bonus[6].img=(IMGHDR*)ImageLoadFromFile("pics\\bon_6.png",1);
  bonus[7].img=(IMGHDR*)ImageLoadFromFile("pics\\bon_7.png",1);
  bonus[8].img=(IMGHDR*)ImageLoadFromFile("pics\\bon_8.png",1);
  bonus[9].img=(IMGHDR*)ImageLoadFromFile("pics\\bon_9.png",1);
  bonus[10].img=(IMGHDR*)ImageLoadFromFile("pics\\bon_10.png",1);
  bonus[11].img=(IMGHDR*)ImageLoadFromFile("pics\\bon_11.png",1);
  bonus[12].img=(IMGHDR*)ImageLoadFromFile("pics\\bon_12.png",1);
  bonus[13].img=(IMGHDR*)ImageLoadFromFile("pics\\bon_13.png",1);
  bonus[14].img=(IMGHDR*)ImageLoadFromFile("pics\\bon_14.png",1);
  bonus[15].img=(IMGHDR*)ImageLoadFromFile("pics\\bon_15.png",1);
  log("bonuses ok");
  
  //mfree(img_path);
  
  
  log("images loaded");
  SetDefaultGameParameters();
  log("parameters ok");
  loadSettings(); //грузим сохраненные настройки
  log("settings ok");
  SetDifficulty();
  
  mmws=AllocWS(128);
  mmenu_items[0]="новая игра";
  mmenu_items[1]="выбрать уровень";
  mmenu_items[2]="настройки";
  mmenu_items[3]="рекорды";
  mmenu_items[4]="об игре";
  mmenu_items[5]="выход";
  
  
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
  
  PlayMelody_StopPlayback(PLAY_ID);
  FreeWS(mmws);
  ifree(level_bg);
  
  imfree(boss);
  
  //ifree(load_screen);
  ifree(press0);
  //imfree(defense);
  //imfree(rocket);
  //imfree(shell);
  
  imfree(ball[0]);
  imfree(ball[1]);
  imfree(ball[2]);
  
  for(int i=0;i<8;i++)
  {
    imfree(brick[i]);
  }
  
  for(int i=0;i<5;i++)
  {
    imfree(user[i]);
  }
  
  for(int i=0;i<NUM_OF_BONUSES;i++)
  {
    imfree(bonus[i]);
  }
  
  DeinitSpriteBuffer();
  FreeSprite(&brick_sparks);
  FreeSprite(&mine_sparks);
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
