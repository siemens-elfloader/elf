
// Fopen
// Выбор эльфа для неизвестного расширения 

#include "..\swilib.h"

char Title[]="ExtN 0.1 (c)bn";
//extern short screen[132*176]; // Экран 132*176*2
extern void DrawScreen(); // Функция перерисовки экрана
//void onredraw(void);

const char cext[]="4:\\ZBin\\etc\\extension.cfg";
const char p_t[]="%t:%t";

#define maxscpos 10 //строк на экране
#define maxext 128
char *ext[maxext], *elf[maxext];
int maxi=0; //всего элементов
int start=0, end=0, pos=0; //меню
char *buf=0;
WSHDR *ws=0;
char *filename;

inline void execelf(char *exename, char *fname){ //fname-параметр (имя файла), передаваемый в эльф 
  WSHDR *ws=AllocWS(256); 
  str_2ws(ws,exename,strlen(exename)+1); 
  ExecuteFile(ws,0,fname); 
  FreeWS(ws);
}

void onredraw(void){ // Перерисовка экрана screen[132*176]
}

void DrawScreen(){
  int i,y;
  DrawRoundedFrame(0,0,131,175,0,0,0, GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(20));
  if(start>maxi) start=0;
  if((end=start+maxscpos)>maxi) end=maxi;
  for(i=start;i<end;i++){
    wsprintf(ws,p_t,ext[i],elf[i]+7);
    y=5+16*(i-start);
    DrawString(ws,5,y,130,y+14, 3,0, GetPaletteAdrByColorIndex((i==pos)?2:4),GetPaletteAdrByColorIndex(23));
  }
}

// keycode - код клавиши, pressed - нажата/отпущена/удерживается
int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){      
  case KEY_UP: break; // Клавиша отпущена
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
    switch(keycode){ // Код клавиши
    case RED_BUTTON: return 1; // Выход
    case ENTER_BUTTON: 
      execelf(elf[pos],filename);
      break;
    case LEFT_BUTTON: 
      if(pos!=start) pos=start;
      else{
        if((pos-=maxscpos)<0) pos=0;
        start=pos;
      }
      break;
    case UP_BUTTON: 
      if(--pos<0){ 
        start=(maxi/maxscpos)*maxscpos;
        pos=maxi-1;
      }else if(pos<start) start-=maxscpos;
      break;
    case RIGHT_BUTTON:
       if(pos!=end-1) pos=end-1;
       else{
         if((pos+=maxscpos)>=maxi)
           pos=(maxi/maxscpos)*maxscpos;
         start=pos;
       }
       break;
    case DOWN_BUTTON:
      if(++pos>=maxi) start=pos=0;
      else if(pos>=end) start=pos;
      break;
    default: return 0;
    }
    onredraw(); DrawScreen(); // Перерисовать экран
  }
  return 0;
}

void onclose(){ // Закрытие окна
  if(ws) FreeWS(ws);
  if(buf) mfree(buf);
}

void onexit(){ // Выход
}

void oncreate(){ // Создание окна
  ws=AllocWS(256);
}

int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода.
  char *s, *ss;
//  if(fname[1]!=':') return 1;
  filename=fname;
  if(!(buf=loadfile((char*)cext))){
    *(char*)cext='0';  if(!(buf=loadfile((char*)cext)))  return 1;
  }
  ss=(s=buf)+loadfilesize;
  --s;
  while(++s<ss && maxi<maxext){
    if(*s=='['){ ext[maxi]=s+1;
      while(++s<ss && *s!=']');
      *s=0;
      while(++s<ss-4 && getint(s)!='=NUR');
      elf[maxi++]=s+4;
      while(++s<ss && *s!=0xd);
      *s=0;
    }
  }
  return 0;
}
