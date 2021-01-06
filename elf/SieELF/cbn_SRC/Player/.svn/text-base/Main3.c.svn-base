
// MP3 Player
#define HIGHCOLOR // 16-битный режим
#define GRAPH  // Графика
#include "..\mylib.h"
#include "..\random.h"

char Title[]="Player 0.2 (c)bn";
typedef unsigned char byte;
extern short screen[132*176]; // Экран 132*176
extern const int screensize;
extern void DrawScreen(); // Функция перерисовки экрана

#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))

SFO sfo={1,0,0,2};
byte exit=0;

#define maxlistsize 32768
char path[256], *fon=0, *list=0, *listend; //free
char **sound=0; //free
WSHDR *ws1=0, *ws2=0; //free
int maxsound=0, cursound=0;
char filename[128];

void onredraw(void){ // Перерисовка экрана screen[132*176]
}


void playsound(char *fname){
  char *file=fname+strlen(fname);
  while(*--file!='\\');
  *file++=0;
  str_2ws(ws1,fname,strlen(fname)+1);  
  str_2ws(ws2,file,strlen(file)+1);
  onredraw(); DrawScreen();
  if(!exit)
    DrawString(ws2,5,5,131,75,3,0, GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  PlayFile(0xC,ws1,ws2,MMI_CEPID,0x167,&sfo);  //GBS_GetCurCepid()
  *--file='\\';
  REDRAW();
}


void play(){ //играть след.песню
  playsound(sound[cursound]);
  if(++cursound>=maxsound) cursound=0;
//   str_2ws(ws2,de.file_name,strlen(de.file_name)+1);
//   PlayFile(0xC,ws1,ws2,MMI_CEPID,0x167,&sfo);  //GBS_GetCurCepid()
//   if(!FindNextFile(&de,&err)) exit=1;
}

int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){      
  case KEY_UP: return 0; // Клавиша отпущена
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
    if(exit) return 1; //exit
    switch(keycode){
     case RED_BUTTON: return 1; // Выход
     case UP_BUTTON: 
       if(++sfo.volume>4) sfo.volume=4; break;
    case DOWN_BUTTON: 
      if(--sfo.volume<0) sfo.volume=0; break;
   case LEFT_BUTTON:
     --cursound;
   case GREEN_BUTTON:
      if(--cursound<0) cursound=maxsound-2;
    case RIGHT_BUTTON:
     default: play(); break;
    }
  }
  return 0;
}


void onclose(){ // Закрытие окна
//  running=0; // Сигнал на остановку фонового процесса
//  GBS_DelTimer(&timer); //(у меня pickoff)???
  //  GBS_StopTimer(&timer); // Останавливаем таймер (у меня pickoff)
  savefile(path,list,listend-list);  // Сохраняем результаты

  //ЗАТКНУТЬ!
  sfo.unk1=1; sfo.volume=0; exit=1;
  playsound(filename);
}

void onexit(){ // Выход
  if(ws1) mfree(ws1);
  if(ws2) mfree(ws2);
  if(fon) mfree(fon);
  if(sound) mfree(sound);
  if(list) mfree(list);
}


void oncreate(){ // Создание окна
  play();
//  SUBPROC((void *)execute); // Запускаем фоновый процесс (не нужен счас)
//  running=1; mode=0;
  //REDRAW();//??
//  GBS_StartTimerProc(&timer,(10-buf[speed])*50,timer_proc); // Стартуем таймер с частотой N раз в секунду
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
      strcpy(file,de.file_name);
      if(isdir(path,&err)) ;
      else add();
    }while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
}

void makelist(){    //составить список с вложенными папками
  static DIR_ENTRY de;
  char *file=path+strlen(path);
  while(*--file!='\\');
  memcpy(++file,"*.*",4);
  if (FindFirstFile(&de,path,&err)){
    do{
      strcpy(file,de.file_name);
      if(isdir(path,&err))///attr???
        find();
      else add();
    }while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
}

int onstart(char *exename, char *fname){
  if(!fname) return 1;
  strcpy(filename,exename);
  memcpy(filename+strlen(filename)-3,"mid",4);
  strcpy(path,fname);
  memcpy(exename+strlen(exename)-3,"bmp",4);
  fon=loadgraph(exename);
  if(!(list=loadfile(path)) || loadfilesize<8){ //пустой список
    if(list) mfree(list);
    if(!(listend=list=(char*)malloc(maxlistsize))) return 1;
    makelist();
    if(listend==list) return 1;
    strcpy(path,fname);
  }else listend=list+loadfilesize;
  genlist();
  memsetw(screen,RGB16(16,32,16),132*176);
  if(fon) bitblt(screen,fon,0,0,0,0, 0,0,0,0);
  ws1=AllocWS(256);
  ws2=AllocWS(128);
  Randomize();
//  REDRAW();//?
  return 0;
}
