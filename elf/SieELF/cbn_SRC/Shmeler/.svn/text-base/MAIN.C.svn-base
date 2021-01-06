
// Shmeler

#include "..\swilib.h"

char Title[]="Shmeler 0.2 (c)bn";
//extern short screen[132*176]; // Экран 132*176*2
extern void DrawScreen(); // Функция перерисовки экрана
//void onredraw(void);

extern IMGHDR *img;//=0xA0DA0024
IMGHDR *img2;
WSHDR *ws;

extern int imgnum;
int input=0;

char filename[128], *file;

#define headsize 32
char head[headsize]="GraphicPatchFile";

void onredraw(void){ // Перерисовка экрана screen[132*176]
}

void savegpf(){
  int f;
  unsigned int err, size;
  if((img=GetPITaddr(imgnum)) && (img2=GetPITaddr(imgnum+1)) && (size=img2->bitmap-img->bitmap)<64000){
    sprintf(file,"%d.gpf",imgnum);
    if((f=fopen(filename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
      *(long*)(head+16)=imgnum;
      *(long*)(head+20)=*(long*)img;
      fwrite(f,head,headsize,&err);
      fwrite(f,img->bitmap,size,&err);
      if(size&=0xf){ //выровнять кратно 16!
        fwrite(f,head+16,16-(size&0xf),&err);
      }
      fclose(f,&err);
      ShowMSG(1,(int)"Сохранен");
    }
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
    case LEFT_BUTTON: case UP_BUTTON: case LEFT_SOFT: input=0;
      if(--imgnum<0) imgnum=0; break;
    case RIGHT_BUTTON: case DOWN_BUTTON: case RIGHT_SOFT:
      ++imgnum;  input=0;  break;
    case ENTER_BUTTON: savegpf();  input=0; break;
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
      if(!input) imgnum=0;
      imgnum=imgnum*10+keycode-'0';
      input=1;
      break;
    default: input=0; return 0;
    }
    onredraw(); DrawScreen(); // Перерисовать экран
  }
  return 0;
}

void onclose(){ // Закрытие окна
  FreeWS(ws);
}

void onexit(){ // Выход
}

void oncreate(){ // Создание окна
  ws=AllocWS(64);
}

int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода.
  strcpy(filename,exename);
  file=filename+strlen(filename);
  while(*--file!='\\');
  ++file;
//  char s[64];
//  sprintf(s,"%X",(int)GetPITaddr(0x600));
//  ShowMSG(1,(int)s);
  return 0;
}
