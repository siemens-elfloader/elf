
// Среда выполнения Basica

#include "E:\ARM\swilib.h"

extern short screen[132*176]; // Экран 132*176*2
extern void DrawScreen(); // Функция перерисовки экрана
void onredraw();

char *Title="vNES 0.1 (c)bn";

const char *errors[]={
  0,
  "Запустите .nes файл",
  "error"
};

//#define RGB8(R,G,B) (B+(G<<2)+(R<<5))
#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))

typedef unsigned char byte;

volatile int running=0; // Процесс проверяет флаг и выходит если =0

void execute(){ // Выполняем basic код
  running=1;
  while(running){ // Пока нет команды на останов
    ;
  }
}

void onredraw(){ // Перерисовка экрана screen[132*176]
//  int i,j;
//  for(i=0,j=color++;i<132*176;i++){
//    screen[i]=j++;
//  }
}

// keycode - код клавиши, pressed - нажата/отпущена/удерживается
int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){      
  case KEY_UP: break; // Клавиша отпущена
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
    switch(keycode){ // Код клавиши
    case RED_BUTTON: return 1; // Выход
    case LEFT_SOFT: case RIGHT_BUTTON: case UP_BUTTON: case ENTER_BUTTON: // Делаем что-либо
    case '0': case '9': case '#': case '*':  break; 
    default: return 0;
    }
    onredraw(); DrawScreen(); // Перерисовать экран
  }
  return 0;
}




void onclose(){ // Закрытие окна
  running=0; // Сигнал на остановку фонового процесса
//  GBS_StopTimer(&timer); // Останавливаем таймер  pickoff!!
//  savelog();  // Сохраняем лог
}

void onexit(){ // Выход
//  if(buf) mfree(buf); // Освобождаем память
}

void oncreate(){ // Создание окна
  SUBPROC((void *)execute); // Запускаем фоновый процесс 
//  GBS_StartTimerProc(&timer,262/2,timer_proc); // Стартуем таймер с частотой 2 раз в секунду
}

int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода.
  return 0;
}
