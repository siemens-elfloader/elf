
// ���� Balloons 0.3  (c)cbn  http://cbn.narod.ru
// �������� ���� ������

#define NEWSGOLD
//NEWSGOLD ������ ���� ������ ������!
//�.�. Siemens.c �������������� ��� ������.

#include "..\swilib.h" // ������� ����. - ����� �� �� ��.��������
#include "..\random.h" // "���������" �����

char *Title="Balloons 0.3 (c)bn";

typedef unsigned char byte;
extern int width, height;
const int block=10;
extern char *screen;//[132*176]; // ����� 132*176
extern int screensize;
extern void DrawScreen(); // ������� ����������� ������
//unsigned int err;
int f;
#define RGB8(R,G,B) (B+(G<<2)+(R<<5))

const char *errors[]={0};

char filename[128]; // ������ ��� sav �����
int maxy=17, maxxy=17*13;
#define maxx 13
#define maxyy 247
#define rec 248
#define maxrec 252
#define datasize 256
byte data[datasize];  // ����� � ����������� � ������� �������
#define dat(x,y) data[(y)*maxx+(x)]

const byte curcolor=0xff;//RGB8(0,0,3);
const byte colors[]={ // ����� �����
  0, RGB8(7,0,0),RGB8(0,7,0),RGB8(0,0,3),RGB8(7,0,3),
};

int curx=maxx/2, cury=17/2;
byte col; //tmp color
int del; //tmp ����� ����.�����

//void *memset(void *mem, int val, int size){
//  char *s=(char*)mem;
//  while(--size>=0) *s++=(char)val;
//  return mem;
//}

void newgame(){ //����� ����
  int i;
  byte *ptr=data;
  memset(screen,0,screensize);
  memset(data,0,maxrec);
  //���������� ����. ������
  for(i=0;i<maxxy;i++)
    *ptr++=(rand()&3)+1;
}

int endgame(){ //�������� ����������� �� ����?
  int curx,cury;
  for(cury=0;cury<maxy;cury++)
    for(curx=0;curx<maxx;curx++)
    if(col=dat(curx,cury)){
      if(curx>0 && dat(curx-1,cury)==col) return 0;
      if(curx<maxx-1 && dat(curx+1,cury)==col) return 0;
      if(cury>0 && dat(curx,cury-1)==col) return 0;
      if(cury<maxy-1 && dat(curx,cury+1)==col) return 0;
    }
  //���� ������.
  char msg[32];
  sprintf(msg,"�����: %d\n������: %d",*(int*)(data+rec), *(int*)(data+maxrec));
  if(*(int*)(data+rec)>*(int*)(data+maxrec)) *(int*)(data+maxrec)=*(int*)(data+rec);
  ShowMSG(1,(int)msg);
  newgame();
  return 1;
}


void down(){ //������ ���� (����.������ �����)
  int i=maxxy,j,k;
  while(--i>=maxx){
    if(!data[i]){ //������ ������ - ������ ������
      j=i;
      k=0;
      while(j>=maxx){
        if(data[j]=data[j-maxx]) k=1;
        j-=maxx;
      }
      data[j]=0;
      if(k) ++i;
    }
  }
}

void is(int curx,int cury){ //����������� �������� ������������ ����� � ������ col
  ++del;
  dat(curx,cury)=0;
  if(curx>0 && dat(curx-1,cury)==col) is(curx-1,cury);
  if(curx<maxx-1 && dat(curx+1,cury)==col) is(curx+1,cury);
  if(cury>0 && dat(curx,cury-1)==col) is(curx,cury-1);
  if(cury<maxy-1 && dat(curx,cury+1)==col) is(curx,cury+1);
}

void enter(){ //������ ��. enter
//  int pos=cury*maxx+curx;
  if(col=dat(curx,cury)){
    del=0;
    is(curx,cury); //���������� ��������� ��.
    if(del>1){
      *(int*)(data+rec)+=del*(del-1);
      down();
    }else dat(curx,cury)=col;
  }
}

void onredraw(){ // ����������� ������ screen[132*176]
  //���������� "������"
  int i,j,k;
  char *sc, *scr=screen+width+1;
  byte *dat=data, color;
  for(j=0;j<maxy;j++){
    sc=scr;
    for(i=0;i<maxx;i++){
      color=colors[*dat++];
      for(k=0;k<block;k++,scr+=width)
        memset(scr,color,block);
      scr-=width*block-block;
    }
    scr=sc+width*block;
  }
  //���������� ������
  scr=screen+width+1+cury*block*width+curx*block;
  memset(scr,curcolor,block);
  for(i=0;i<block;i++,scr+=width)
    scr[0]=scr[block-1]=curcolor;
  memset(scr-width,curcolor,block);
}


int onkey(unsigned char keycode, int pressed){ //  ���������� ������. ������� 0 ��� 1 ��� ������
  switch(pressed){      
  case KEY_UP: return 0; // ������� ��������
  case LONG_PRESS: // ������� ������������ ����� (������)
  case KEY_DOWN: // ������� ������
    switch(keycode){ // ��� �������
    case RED_BUTTON: return 1; // �����
    case GREEN_BUTTON: 
      maxy=(maxy==17)?13:17;
      maxxy=maxx*maxy;
      if(cury>=maxy) cury=maxy-1;
    case LEFT_SOFT: case RIGHT_SOFT:
      newgame(); break;
    //�������. �������
    case LEFT_BUTTON: case '4': 
      if(--curx<0) curx=maxx-1; break;
    case RIGHT_BUTTON: case '6': 
      if(++curx>=maxx) curx=0; break;
    case UP_BUTTON: case '2':
      if(--cury<0) cury=maxy-1; break;
    case DOWN_BUTTON: case '8': 
      if(++cury>=maxy) cury=0; break;
    case ENTER_BUTTON: case '5': 
      enter(); if(endgame()) return 0;
      break;
    default: return 0;
    }
  }
  onredraw(); DrawScreen(); // ������������ �����
  return 0;
}

void savegame(){ // �������� ����
  if((f=fopen(filename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
    data[maxyy]=(byte)maxy;
    fwrite(f,data,datasize,&err); 
    fclose(f,&err);
}}

void loadgame(){ // ��������� ����
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    if(fread(f,data,datasize,&err)==datasize){
      maxy=data[maxyy];
      maxxy=maxx*maxy;
      endgame();
    }else newgame();
    fclose(f,&err);
  }else newgame();
}

void onclose(){ // �������� ����
  savegame();  // ��������� ����������
}

void onexit(){ // �����
}

void oncreate(){ // �������� ����
}

int onstart(char *exename, char *fname){ // ����� ����������. ���������� 0 ��� 1 ��� ������.
  strcpy(filename,exename);
  memcpy(filename+strlen(filename)-3,"sav",4);
  Randomize();
  loadgame();
  return 0;
}

