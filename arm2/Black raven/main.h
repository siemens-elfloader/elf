void writemap(char *fname);
int strcmp_nocase(const char *s1,const char *s2);
void writeinit(int digit, int init);
void changeSize(int xx, int yy);
char zag[255];
char all[255];
char cel1[255];
char cel2[255];
char cel3[255];
int kadrnum=1 ;   // ������� ���� �������� ���������
int mapx = 0, mapy = 0; // ������� ����� �� x � y
int sm=0; // �������� � ������ �� ������ ��� ������ ����� ����� �� ������ ������ ������ ��������
int sizeSP=20; //������ ������
int sizeX=11;  // ������� ����� �������� �� ����� �� �
int sizeY=14;  // ������� ����� �������� �� ����� �� Y
int scrX=0; //���������� ������ ������������ ������ �����
int scrY=0;
int cursorX=0; //���������� ������� � �����
int cursorY=0;
int heroyX=0;
int heroyY=0;
int Xscr=10;  // ������� ���������� � ������ 
              // ������ ���������� � ������� ��������� ����� 
int npic (int x,int y); // ������� ���������� ����� ��������
GBSTMR timerredraw;
GBSTMR tmr;
GBSTMR tmr2;
int countM2=3; // ������� ����� ����
int countM4=1;
const int counCOLM=5; // �������� ������� ����
const int counCOLM2=3; // �������� ������� ����
int sizeF=17;  // ������ ������ ������ ������
int gold=1500;  //������
int wood=1500;  //������
int Yscr=2;
int i;
int y;
int x;
int p;
int DelayVAR;
int tpic=1;  // ������� ��������
int maxpic=105;// ������������ ����� �������� ��� ����
int minpic=1;
int scrCURx;
int typeGUI;
int scrCURy;
int typeGUI=0;// ����� �������� ������:0-����� 1-���� 2-����� ��������...
int hercur=0;
int scr_w, scr_h;//������ � ������ ������


int ab=0;
int ba=0;
int ia;
void xy2xy(int *x,int *y,int *x2,int *y2,int *x3,int *y3)//������� �������� �� ����� x,y � x2,y2(�������� ������� �� speed � �����������)
{
  
if(*x!=*x2&&*y!=*y2&&ab==0){
if(*x>*x2)
{*x-=1;} 
if(*x<*x2)
{*x+=1;} 
if(*y>*y2)
{*y-=1;} 
if(*y<*y2)
{*y+=1;}
}
else{
  ia=0;
  ab=1;
  if(*x>*x3)
{*x-=1;} 
if(*x<*x3)
{*x+=1;} 
if(*y>*y3)
{*y-=1;} 
if(*y<*y3)
{*y+=1;}

if(*x==*x3&&*y==*y3)
{
  ab=0;
}
}


}
void xy2xya(int *x,int *y,int *x2,int *y2)//������� �������� �� ����� x,y � x2,y2(�������� ������� �� speed � �����������)
{
  
if(*x!=*x2&&*y!=*y2){
if(*x>*x2)
{*x-=1;} 
if(*x<*x2)
{*x+=1;} 
if(*y>*y2)
{*y-=1;} 
if(*y<*y2)
{*y+=1;}}
else{


}


}
int x22=12,y22=12;
int bearX=19;
int bearY=19;
int x33=19;
int y33=19;

typedef struct{
  int life,power,dexterity,rank;
}mystr;
mystr celdric,bear;
int gameover;


void ai()
{
  if(bearX!=heroyX&&bearY!=heroyY)
  {
    ia++;
    if(ia==30){
      xy2xy(&bearX,&bearY,&x22,&y22,&x33,&y33);}
  }
   if(bearX==heroyX&&bearY==heroyY)
   {
     celdric.life-=20;
     xy2xya(&bearX,&bearY,&heroyX,&heroyY);
   }
}
