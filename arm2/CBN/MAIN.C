
// ����� ���������� Basica

#include "E:\ARM\swilib.h"

extern short screen[132*176]; // ����� 132*176*2
extern void DrawScreen(); // ������� ����������� ������
void onredraw();

char *Title="vNES 0.1 (c)bn";

const char *errors[]={
  0,
  "��������� .nes ����",
  "error"
};

//#define RGB8(R,G,B) (B+(G<<2)+(R<<5))
#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))

typedef unsigned char byte;

volatile int running=0; // ������� ��������� ���� � ������� ���� =0

void execute(){ // ��������� basic ���
  running=1;
  while(running){ // ���� ��� ������� �� �������
    ;
  }
}

void onredraw(){ // ����������� ������ screen[132*176]
//  int i,j;
//  for(i=0,j=color++;i<132*176;i++){
//    screen[i]=j++;
//  }
}

// keycode - ��� �������, pressed - ������/��������/������������
int onkey(unsigned char keycode, int pressed){ //  ���������� ������. ������� 0 ��� 1 ��� ������
  switch(pressed){      
  case KEY_UP: break; // ������� ��������
  case LONG_PRESS: // ������� ������������ ����� (������)
  case KEY_DOWN: // ������� ������
    switch(keycode){ // ��� �������
    case RED_BUTTON: return 1; // �����
    case LEFT_SOFT: case RIGHT_BUTTON: case UP_BUTTON: case ENTER_BUTTON: // ������ ���-����
    case '0': case '9': case '#': case '*':  break; 
    default: return 0;
    }
    onredraw(); DrawScreen(); // ������������ �����
  }
  return 0;
}




void onclose(){ // �������� ����
  running=0; // ������ �� ��������� �������� ��������
//  GBS_StopTimer(&timer); // ������������� ������  pickoff!!
//  savelog();  // ��������� ���
}

void onexit(){ // �����
//  if(buf) mfree(buf); // ����������� ������
}

void oncreate(){ // �������� ����
  SUBPROC((void *)execute); // ��������� ������� ������� 
//  GBS_StartTimerProc(&timer,262/2,timer_proc); // �������� ������ � �������� 2 ��� � �������
}

int onstart(char *exename, char *fname){ // ����� ����������. ���������� 0 ��� 1 ��� ������.
  return 0;
}
