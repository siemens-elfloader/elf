
// Player
// Взято с http://cbn.narod.ru  (c)bn
#define HIGHCOLOR // 16-битный режим
//#define GRAPH  // Графика
#include "..\swilib.h"
#include "..\random.h"

char *Title="Player 0.4 (c)bn";
typedef unsigned char byte;
extern short *screen; // Экран 132*176
extern void DrawScreen(); // Функция перерисовки экрана

extern unsigned char SGOLD2, C65, S75, EL71;
extern int width, height, screensize;

#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))
#define delay 262/10

const char *errors[]={
  0,
  "Щелкните на файллист!\0",
  "Мало памяти!\0",
  "Нет файлов!\0"
};

SFO sfo={1,0,0,2};
byte exit=0;

struct param{ //параметры
  byte volume, repeat, random, stop; //повтор/СЧ/
  byte rez1, rez2, rez3, rez4;
}p={2,0,0};

byte modify=0; //измен. файллиста
#define maxlistsize 32768
char path[256], *fon=0, *list=0, *listend; //free
char **sound=0; //free
WSHDR *ws1=0, *ws2=0; //free
int maxsound=0, cursound=0, oldsound=0;
char filename[128], *file;
int f;

GBSTMR timer;

void onredraw(){ // Перерисовка экрана screen[132*176]
}

int rndsnd(){
  unsigned int i, cnt=0;  
  if(maxsound<2) return 0;
  do{
//    i=Random();
//    if(maxsound>256) i=(i<<8)|Random();
    i=randint(maxsound);
  }while(i==cursound && ++cnt<8);//(i%=maxsound)
  oldsound=cursound;
  return cursound=i;
}

void playsound(char *fname){ // Проиграть файл fname
//  char *file=fname+strlen(fname);
//  while(*--file!='\\');
  char *file=strrchr(fname,'\\');
  *file++=0;
  str_2ws(ws1,fname,strlen(fname)+1);  
  str_2ws(ws2,file,strlen(file)+1);
  onredraw(); DrawScreen();
  if(!exit)
    DrawString(ws2,5,5,131,75,3,0, GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
//if(S75)// ПРОВЕРКА типа мобилы (разные функции проигрывания на 75 и 65 моделях)  
  PlayFile(0xC,ws1,ws2,MMI_CEPID,0x167,&sfo);  //GBS_GetCurCepid()
  *--file='\\';
  REDRAW();
}

void timer_proc(){ // Функция выполняется по таймеру N раз в секунду
  if(!IsPlayerOn()){
     if(p.random) rndsnd();
     else if(++cursound>=maxsound) cursound=0;
     playsound(sound[cursound]); 
  }
  GBS_StartTimerProc(&timer,delay,timer_proc); // Стартуем таймер с частотой N раз в секунду
}

int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){      
  case KEY_UP: return 0; // Клавиша отпущена
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
//    if(exit) return 1; //exit
    switch(keycode){
     case RED_BUTTON: return 1; // Выход
    case '1': sfo.unk1=(p.repeat=!p.repeat)?-1:1; break;
    case '2': p.random=!p.random; break;
    case '4': p.stop=!p.stop; break;
    case '3': //del in list
      if(cursound<maxsound && maxsound>1){
        --maxsound; modify=1;
        for(int i=cursound;i<maxsound;i++){
          sound[i]=sound[i+1];
        }if(cursound>=maxsound) cursound=maxsound-1;
      }goto lplay;
     case UP_BUTTON: if(++sfo.volume>4) sfo.volume=4; break;
    case DOWN_BUTTON: if(--sfo.volume<0) sfo.volume=0; break;
     case LEFT_BUTTON:
       if(p.random){ if(cursound!=oldsound) cursound=oldsound; else rndsnd();
       }else if(--cursound<0) cursound=maxsound-1;
    case ENTER_BUTTON:
    case GREEN_BUTTON:
       playsound(sound[cursound]); 
       break;
    case RIGHT_BUTTON: //след.муз.
     default:
       if(p.random) rndsnd();
       else if(++cursound>=maxsound) cursound=0;
 lplay:
       playsound(sound[cursound]); break;
    }
  }
  return 0;
}


void saveini(){
  if((f=fopen(filename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
    p.volume=sfo.volume;
    fwrite(f,&p,sizeof(struct param),&err); 
    fclose(f,&err);
  }
}

void loadini(){
 if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
  fread(f,&p,sizeof(struct param),&err);
  fclose(f,&err);
  sfo.unk1=(p.repeat)?-1:1;
  sfo.volume=p.volume;
}}


void savelist(){ //пересорт. список
  char *mem, *ptr;
  int i;
  if((f=fopen(path,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
    if(ptr=mem=(char*)malloc(listend-list)){
      for(i=0;i<maxsound;i++){
        strcpy(ptr,sound[i]);
        ptr+=strlen(sound[i])+1;
      }
      fwrite(f,mem,ptr-mem,&err); 
      mfree(mem);
    }
    fclose(f,&err);
  }
}

void onclose(){ // Закрытие окна
//  running=0; // Сигнал на остановку фонового процесса
  GBS_DelTimer(&timer); //(у меня pickoff)???
  if(modify) savelist();
  else savefile(path,list,listend-list);  // Сохраняем результаты
  saveini();
  //ЗАТКНУТЬ!
  memcpy(file,"mid",4);
  sfo.unk1=1; sfo.volume=0; exit=1;
  if(!p.stop)  playsound(filename);
}

void onexit(){ // Выход
  if(ws1) mfree(ws1);
  if(ws2) mfree(ws2);
  if(fon) mfree(fon);
  if(sound) mfree(sound);
  if(list) mfree(list);
}


void oncreate(){ // Создание окна
  playsound(sound[cursound=(p.random?rndsnd():0)]);
  GBS_StartTimerProc(&timer,delay,timer_proc); // Стартуем таймер с частотой N раз в секунду
}

void genlist(){
  char *s=list, **snd;
  maxsound=0;
  //посчитать строки
  do{
    ++maxsound;
  }while((s+=strlen(s)+1)<listend);
  sound=snd=(char**)malloc(maxsound<<2);
  //заполнить строки
  s=list;
  do{
    *snd++=s;
  }while((s+=strlen(s)+1)<listend);
}


void add(){ //path -> list
  strcpy(listend,path);
  listend+=strlen(path)+1;
}
 
void find(){ // Найти все пути (использ.path)
  static DIR_ENTRY de;
  char *file;
  file=path+strlen(path);
  memcpy(file++,"\\*.*",5);
  if (FindFirstFile(&de,path,&err)){
    do{
      strcpy(file,SGOLD2?de.file_name:((char*)&de+169));
//      strcpy(file,de.file_name);
      if(isdir(path,&err)) ;//nothing
      else add();
    }while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
}

void makelist(){    //составить список с вложенными папками
  static DIR_ENTRY de;
//  char *file=path+strlen(path);
//  while(*--file!='\\');
  char *file=strrchr(path,'\\');
  memcpy(++file,"*.*",4);
  if (FindFirstFile(&de,path,&err)){
    do{
      strcpy(file,SGOLD2?de.file_name:((char*)&de+169));
//      strcpy(file,de.file_name);
      if(isdir(path,&err))///attr???
        find();
      else add();
    }while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
}

int onstart(char *exename, char *fname){
  if(!fname || fname[1]!=':') return 1;
  strcpy(path,fname);
  strcpy(filename,exename);
  file=filename+strlen(filename)-3;
#ifdef GRAPH  
  memcpy(file,"bmp",4);
  fon=loadgraph(filename);
#endif  
  memcpy(file,"ini",4);
  loadini();
  if(!(list=loadfile(path)) || loadfilesize<8){ //пустой список
    if(list) mfree(list);
    if(!(listend=list=(char*)malloc(maxlistsize))) return 2;
    makelist();
    if(listend==list) return 3;
    strcpy(path,fname);
  }else listend=list+loadfilesize;
  genlist();
  memsetw(screen,RGB16(16,32,16),132*176);
#ifdef GRAPH  
  if(fon) bitblt(screen,fon,0,0,0,0, 0,0,0,0);
#endif  
  ws1=AllocWS(256);
  ws2=AllocWS(128);
  Randomize();
//  REDRAW();//?
  return 0;
}
