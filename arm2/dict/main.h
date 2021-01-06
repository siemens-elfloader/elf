typedef struct{
int x, y, dx, dy, width, height, g,x0,y0;
} my;
my user, cpu, ball, cpuvr, uservr;
typedef struct{
int x, y;
} my2;
my2 udar;
int timer_speed=5;
volatile int running=0;
GBSTMR tmr;
char map[32];
char user_flag[32];
char cpu_flag[32];
char user_i[32];
char cpu_i[32];
char ball_i[32];
int xy=6;
int lico=1;
int sila;
void init();
int udarh=10;

void xy2xy(int *x,int *y,int *dx, int *dy,int *x2,int *y2,int speed)//Функция движения из точки x,y в x2,y2(скорость зависит от speed и перерисовки)
{
 if(*y2==*y)
{
  *dy=0;
}
if(*x2==*x)
{
  *dx=0;
}
if(*x>*x2)
{
  *dx=-speed;
} 
if(*x<*x2)
{
  *dx=speed;
} 
if(*y>*y2)
{
  *dy=-speed;
} 
if(*y<*y2)
{
  *dy=speed;
} 

*x+=*dx; 
*y+=*dy; 
}

void xrx(my *who,my *balll)
{
   if (balll->x+balll->width>=who->x&&balll->x<=who->x+who->width&&balll->y+balll->height>=who->y&&balll->y<=who->y+who->height)
   {
    balll->x=who->x;
    balll->y=who->y;
   }
}
