void writemap(char *fname);
int strcmp_nocase(const char *s1,const char *s2);
void writeinit(int digit, int init);
void changeSize(int xx, int yy);
char zag[255];
char all[255];
char cel1[255];
char cel2[255];
char cel3[255];
int kadrnum=1 ;   // текущий кадр анимации ландшафта
int mapx = 0, mapy = 0; // –азмеры карты по x и y
int sm=0; // смещение в байтах от начала дл€ обхода даных карты до начала номера первой картинки
int sizeSP=20; //размер €чейки
int sizeX=11;  // сколько €чеек выводить на экран по ’
int sizeY=14;  // сколько €чеек выводить на экран по Y
int scrX=0; //координаты экрана относительно начала карты
int scrY=0;
int cursorX=0; //координаты курсора в карте
int cursorY=0;
int heroyX=0;
int heroyY=0;
int Xscr=10;  // текущие координаты в экране 
              // точнее координаты с которых выводитс€ карта 
int npic (int x,int y); // функци€ возвращает номер картинки
GBSTMR timerredraw;
GBSTMR tmr;
GBSTMR tmr2;
int countM2=3; // текущий пункт меню
int countM4=1;
const int counCOLM=5; // максимум пунктов меню
const int counCOLM2=3; // максимум пунктов меню
int sizeF=17;  // размер точнее высота шрифта
int gold=1500;  //золото
int wood=1500;  //дерево
int Yscr=2;
int i;
int y;
int x;
int p;
int DelayVAR;
int tpic=1;  // текуща€ картинка
int maxpic=105;// максимальный номер картинки дл€ фона
int minpic=1;
int scrCURx;
int typeGUI;
int scrCURy;
int typeGUI=0;// номер текущего экрана:0-карта 1-меню 2-выбор картинки...
int hercur=0;
int scr_w, scr_h;//Ўирина и высота экрана


int ab=0;
int ba=0;
int ia;
void xy2xy(int *x,int *y,int *x2,int *y2,int *x3,int *y3)//‘ункци€ движени€ из точки x,y в x2,y2(скорость зависит от speed и перерисовки)
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
void xy2xya(int *x,int *y,int *x2,int *y2)//‘ункци€ движени€ из точки x,y в x2,y2(скорость зависит от speed и перерисовки)
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
