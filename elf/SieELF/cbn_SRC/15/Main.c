
// 15

//#define HIGHCOLOR // 16-������ �����
//#define GRAPH  // �������
#include "..\swilib.h" // ������� ����. - ����� �� �� ��.��������
#include "..\random.h" // "���������" �����

char *Title="15 v0.1 (c)bn";
extern int width, height;
typedef unsigned char byte;
extern short *screen;//[132*176]; // ����� 132*176
extern int screensize;
extern void DrawScreen(); // ������� ����������� ������
//void enter(); // ����� enter
int newgame(); // ������ ����� ����

const char *errors[]={
  0,
"������ �������� ��������\0",
"������� �������� ������ ���� 132�176\0"
};

char *bmp=0; // �������� � �������� � ��������
int end=0, show=0;
byte tab[4][4]; //�������
int x,y; //������ (���������)

int isend(){
  int i;
  byte *b=(byte*)tab;
  for(i=0;i<16;i++,b++)
    if(*b && *b!=i+1) return 0;
  return end=1;
}

void onredraw(){ // ����������� ������ screen[132*176]
  int x,y;
  byte b;
  short *scr;
  if(show || isend()){
    movsd(screen,bmp+4,screensize>>2);
  }else{
    memsetd(screen,0,screensize>>2);
    for(y=0;y<4;y++){
      for(x=0;x<4;x++){
        if(b=tab[y][x]){
        --b;
        bitblt(screen,bmp, x*33, y*44, 33,44,  (b&3)*33, (b>>2)*44, 0,0);
        }
      }
    }
    for(y=0,scr=screen;y<176;y++,scr+=132)
      scr[33]=scr[66]=scr[99]=0;
    for(x=0,scr=screen;x<132;x++,scr++)
      scr[44*132]=scr[88*132]=scr[(44+88)*132]=0;
    
  }
}


void getxy(){
  for(y=0;y<4;y++){
    for(x=0;x<4;x++){
      if(!tab[y][x]) return;
    }
  }
}


 
int onkey(unsigned char keycode, int pressed){ //  ���������� ������. ������� 0 ��� 1 ��� ������
  switch(pressed){      
  case KEY_UP: return 0; // ������� ��������
  case LONG_PRESS: // ������� ������������ ����� (������)
  case KEY_DOWN: // ������� ������
      if(end) newgame(); 
      else if(show) show=0;
      else{
        getxy();
      switch(keycode){ // ��� �������
      case RED_BUTTON: return 1; // �����
      case GREEN_BUTTON: show=!show; break;
      case LEFT_BUTTON: case '4':
        if(x<3){ tab[y][x]=tab[y][x+1]; tab[y][x+1]=0;} break;        
      case RIGHT_BUTTON: case '6': 
        if(x>0){ tab[y][x]=tab[y][x-1]; tab[y][x-1]=0;} break;
      case UP_BUTTON: case '2': 
        if(y<3){ tab[y][x]=tab[y+1][x]; tab[y+1][x]=0;} break;
      case DOWN_BUTTON: case '8': 
        if(y>0){ tab[y][x]=tab[y-1][x]; tab[y-1][x]=0;} break;
      default: return 0;
      }
  }
  onredraw(); DrawScreen(); // ������������ �����
  }
  return 0;
}



void onclose(){ // �������� ����
//  GBS_DelTimer(&timer); 
//  savegame();  // ��������� ����������
}

void onexit(){ // �����
  if(bmp) mfree(bmp);
}

void oncreate(){ // �������� ����
//  GBS_StartTimerProc(&timer,timedelay,timer_proc); // �������� ������ � �������� N ��� � �������
}

int onstart(char *exename, char *fname){ // ����� ����������. ���������� 0 ��� 1 ��� ������.
  if(!fname || fname[1]!=':'){
    strcpy(strrchr(fname=exename,'.'),".b15");
  }
  if(!(bmp=loadgraph(fname))) return 1;
  if(*(long*)bmp!=0xB00084) return 2; //176 x 132
  Randomize();
  return newgame();
}

int newgame(){ // ������ ����� ����
  int i,j;
  byte tmp[16], *b=(byte*)tab;
  //��������� ����. ������
  for(i=0;i<16;i++)
    tmp[i]=i+1;
  for(i=0;i<16;i++){
    *b++=tmp[j=randint(16-i)];
    tmp[j]=tmp[15-i];
  }
  //������  //*((byte*)tab+randint(16))=0;
  tab[randint(4)][randint(4)]=0;
  return end=0;
}

  
