
// MP3 Player
//без define
#include "..\mylib.h"

char Title[]="Player 0.1 (c)bn";
typedef unsigned char byte;
extern char screen[132*176]; // Экран 132*176
extern const int screensize;
extern void DrawScreen(); // Функция перерисовки экрана

WSHDR *ws1=0, *ws2=0; //free
DIR_ENTRY de;
SFO sfo={1,0,0,3};
byte exit=0;

void onredraw(void){ // Перерисовка экрана screen[132*176]
}

void next(){ //играть след.песню
   str_2ws(ws2,de.file_name,strlen(de.file_name)+1);
   PlayFile(0xC,ws1,ws2,MMI_CEPID,0x167,&sfo);  //GBS_GetCurCepid()
   if(!FindNextFile(&de,&err)) exit=1;
}

int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){      
  case KEY_UP: return 0; // Клавиша отпущена
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
    if(exit) return 1; //exit
    switch(keycode){
     case RED_BUTTON: return 1; // Выход
     default: next(); break;
    }
  }
  return 0;
}

void onclose(){ // Закрытие окна
//  running=0; // Сигнал на остановку фонового процесса
//  GBS_DelTimer(&timer); //(у меня pickoff)???
  //  GBS_StopTimer(&timer); // Останавливаем таймер (у меня pickoff)
//  savegame();  // Сохраняем результаты
  FindClose(&de,&err); 
}

void onexit(){ // Выход
  if(ws1) mfree(ws1);
  if(ws2) mfree(ws2);
}


void oncreate(){ // Создание окна
  next();
//  SUBPROC((void *)execute); // Запускаем фоновый процесс (не нужен счас)
//  running=1; mode=0;
  //REDRAW();//??
//  GBS_StartTimerProc(&timer,(10-buf[speed])*50,timer_proc); // Стартуем таймер с частотой N раз в секунду
}



int onstart(char *exename, char *fname){
  char *file;
  if(!fname) return 1;
  ws1=AllocWS(256);
  ws2=AllocWS(128);
  file=fname+strlen(fname);
  while(*--file!='\\');
  *file=0;
  str_2ws(ws1,fname,strlen(fname)+1);  
  memcpy(file,"\\*.*",5);  
  if(!FindFirstFile(&de,fname,&err)){  FindClose(&de,&err);  return 1;}
  return 0;
}  

