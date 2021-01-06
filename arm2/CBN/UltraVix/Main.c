
// ���� UltraVix

//#define HIGHCOLOR // 16-������ �����
//#define GRAPH  // �������
#include "..\swilib.h" // ������� ����. - ����� �� �� ��.��������
#include "..\random.h" // "���������" �����

char *Title="UltraVix 0.1 (c)bn";
extern int width, height;
typedef unsigned char byte;
extern short *screen;//[132*176]; // ����� 132*176
extern int screensize;
extern void DrawScreen(); // ������� ����������� ������
void enter(); // ����� enter
int newgame(); // ������ ����� ����

const char *errors[]={
  0,
"������������ ������\0",
"�������� .bmp ��� font ����!\0",
"������ �������� ������� ������\0",
"������ �������� ����� ������ ������\0",
"������������ ������\0"
};

const char sini[]="save.ini", slev[]="level00.bmp";
char filename[128], *file; // ������ ��� �����
char *msg=0;

byte level=0, exit=0; // ������� ������� � �����
char *back=0, *dev=0; // �������� � �������� � ��������
char *ini=0, *font=0;

int x=0, y=0; // ������
int heat=0; // "�������" :)
int seldev=0; // ��������� ������

#define maxheat 1000
#define step 10
#define devsize 24

char ispred[256];

enum {enum_, efrom, eto, ex1, ey1, ex2, ey2, eplus, maxpr};
struct prevst{
  int a[maxpr];
  char *name;
} *prev=0, *p, *pp, *prevend; 

#define maxdel 4
/*
level0.ini  (������� �������� �� �������)
0  ��  ��   -��������  

�����_��������  ��  ��  x1  y1  x2  y2  +-  ���_�������

+-N�_���  �����N���  ���_�������
�����, ������
�����
�����, �����
����, ����, ����, ����
����, ������
*/

#define timedelay 262*200
GBSTMR timer;
void timer_proc(){ // ������� ����������� �� �������
  for(pp=prev; pp<prevend; pp++){
    if(pp->a[enum_]==0 && heat>=pp->a[efrom] && heat<p->a[eto]){
      if((heat-=p->a[ex1])<0) heat=0;
      else if(heat>=maxheat){
          ++level;
          if(newgame()) exit=1;
      }
      REDRAW();
    }
  }
  GBS_StartTimerProc(&timer,timedelay,timer_proc); // �������� ������ � �������� N ��� � �������
}  

void onredraw(){ // ����������� ������ screen[132*176]
  int i=heat*height/maxheat, j;
  short *scr=screen+(screensize>>1)-4;
  byte *bb, b;
  int dx, dy;
  movsd(screen,back,screensize>>2);
  while(--i>=0){
    scr[0]=scr[1]=scr[2]=scr[3]=0xf800;
    scr-=width;
  }
  if(msg){
    --msg;
    dx=dy=0;
    while(*++msg){
      if(dx>=width-8){
        dx=0; dy+=10;
      }
      scr=screen+dy*width+dx;
      bb=(byte*)font+*(byte*)msg * 8;
      for(j=0;j<8;j++){
        b=*bb++;
        for(i=0;i<8;i++){
          *scr++=(b&0x80)?0:0xffff;
          //if(b&0x80) *scr=0xffff;
          //scr++;
          b<<=1;
        }
        scr+=width-8;
      }
      dx+=8;
    }
    msg=0;
  }
  bitblt(screen,dev, x-devsize/2,y-devsize/2, devsize,devsize,  (seldev&3)*devsize, (seldev>>2)*devsize, 0x1f,0);
}

int onkey(unsigned char keycode, int pressed){ //  ���������� ������. ������� 0 ��� 1 ��� ������
  switch(pressed){      
  case KEY_UP: return 0; // ������� ��������
  case LONG_PRESS: // ������� ������������ ����� (������)
  case KEY_DOWN: // ������� ������
      if(exit) return 1;
      switch(keycode){ // ��� �������
      case RED_BUTTON: return 1; // �����
      case LEFT_SOFT: case '*': //+-�������
        while(!ispred[seldev=(seldev-1)&0xff]);
        break;
      case RIGHT_SOFT: case '#':
        while(!ispred[seldev=(seldev+1)&0xff]);
        break;
      case GREEN_BUTTON: //test 
        heat+=50; break;
      case LEFT_BUTTON: case '4':
        if((x-=step)<0) x=0; break;
      case RIGHT_BUTTON: case '6': 
        if((x+=step)>=width) x=width-1; break;
      case UP_BUTTON: case '2': 
        if((y-=step)<0) y=0; break;
      case DOWN_BUTTON: case '8': 
        if((y+=step)>=height) y=height-1; break;
      case ENTER_BUTTON: case '5': enter(); break;
      default: return 0;
  }
  onredraw(); DrawScreen(); // ������������ �����
  }
  return 0;
}

inline void savegame(){ // �������� ����
  int f;
  strcpy(file,sini);
  if((f=fopen(filename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
    fwrite(f,&level,1,&err); 
    fclose(f,&err);
}}


void onclose(){ // �������� ����
  GBS_DelTimer(&timer); 
  savegame();  // ��������� ����������
}

void onexit(){ // �����
  if(back) mfree(back);
  if(dev) mfree(dev);
  if(prev) mfree(prev);
  if(ini) mfree(ini);
  if(font) mfree(font);
}

void oncreate(){ // �������� ����
  GBS_StartTimerProc(&timer,timedelay,timer_proc); // �������� ������ � �������� N ��� � �������
}

int onstart(char *exename, char *fname){ // ����� ����������. ���������� 0 ��� 1 ��� ������.
  int f;
  strcpy(filename,exename);
  strcpy(strrchr(filename,'.'),".bmp");
  if(!(back=malloc(screensize))) return 1;
  if(!(dev=loadgraph(filename))) return 2;
  //loadini
  strcpy((file=strrchr(filename,'\\')+1),sini);
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    fread(f,&level,1,&err);
    fclose(f,&err);
  }
  strcpy(file,"font.bmp");
  if(!(font=loadfile(filename))) return 2;//2?
  if(f=newgame()){
    level=0; if(f=newgame()) return f;
  }
  return 0;
}

int newgame(){ // ������ ����� ����
  char *pic, *s;
  int i,j,jj,sign, maxprev=0;
  heat=exit=0;
  x=y=100;
  msg=0;
  memset(ispred,0,256);
  memset(back,0,screensize);
  strcpy(file,slev);
  file[5]=level/10+'0';
  file[6]=level%10+'0';
  if(!(pic=loadgraph(filename))) return 3;
  bitblt(back,pic,0,0,0,0,0,0,0,0);
  mfree(pic);
  // ��������� ����. ���� �� �����. �����
  strcpy(file+7,".png");
  if(ini) mfree(ini);
  if(!(s=ini=loadfile(filename))) return 4;
  ini[loadfilesize-2]=0;
  do{
    while(*++s && *s!=0xd);
    ++maxprev;
  }while(*s);
  if(prev) mfree(prev);
  if(!(prevend=prev=(struct prevst*)malloc((maxprev+3)*sizeof(struct prevst)))) return 5;
  s=ini-1;
  do{
    switch(*++s){
    case ' ': case 9: case 0xd: case 0xa: case 0: break;
    case ';': case '/': while(*++s && *s!=0xd); break;
    default:
      jj=maxpr;
      for(i=0;i<jj;i++){
        while(*s==' ') ++s;
        if(*s=='-'){ ++s; sign=1;} else sign=0;
        j=0;
        while(*s>='0' && *s<='9'){ j=j*10+*s-'0'; ++s;}
        prevend->a[i]=(sign)?(-j):j;
        if(i==0){ ispred[j]=1;
          if(!j) jj=maxdel;
        }
      }
      if(*s==0xd) --s;
      prevend->name=s+1;
      ++prevend;
      while(*++s && *s!=0xd);
      if(*s==0xd) *s++=0;
    }
  }while(*s);
  return 0;
}

     
void enter(){ // ����� enter
  if(!seldev) return;
  for(p=prev; p<prevend; p++){
    if(p->a[enum_]==seldev && heat>=p->a[efrom] && heat< p->a[eto]){
      if(x>=p->a[ex1] && x<p->a[ex2] && y>=p->a[ey1] && y<p->a[ey2]){
        //ok, action!
        msg=p->name;
        if((heat+=p->a[eplus])>=maxheat){
          ++level;
          if(newgame()) exit=1;
        }else
          if(heat < -maxheat){
            --level;
            if(newgame()) exit=1;
          }  
        if(heat<0) heat=0;
      }
    }
  }
}


