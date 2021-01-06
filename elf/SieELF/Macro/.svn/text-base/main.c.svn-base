#include "..\inc\swilib.h"
#include "conf_loader.h"

#define MMI_CEPID 0x4209
#define TMR_SECOND 216

#define t(a) ((a)*TMR_SECOND/1000)

extern int delay_keybreak;
extern int watch_delay;
extern int pre_delay;
extern int paint_delay;
extern int delay_longpause;
extern int delay_smallpause;
extern int delay_wait_1;
extern int delay_wait_2;
extern int delay_wait_3;
extern int show;

extern char ShowNativeMenu_[9];
extern int wait_threshold;

void (*ShowNativeMenu)();
GBSTMR step_timer;
GBSTMR watch_timer;
GBSTMR paint_timer;
WSHDR * ws1;
volatile int brk;
int wc;
char ebu[128];

typedef enum
{
  ST_NORM,
  ST_ERROR,
  ST_END,
  ST_LONG_1,
  ST_LONG_2,
  ST_WAIT,
} TState;

char * mac=0;
char * po;
TState s;
short lpc;


static const unsigned short qq[8];
static WSHDR q={(unsigned short*)&qq,0,0,0,8};

static const unsigned short qqw[16];
static WSHDR qw={(unsigned short*)&qqw,0,0,0,16};

//------------------------------------------------
inline void KeyDown(int key)
{
GBS_SendMessage(MMI_CEPID,KEY_DOWN,key);
};
inline void KeyUp(int key)
{
GBS_SendMessage(MMI_CEPID,KEY_UP,key);
};
inline void LongPress(int key)
{
GBS_SendMessage(MMI_CEPID,LONG_PRESS,key);
};
//------------------------------------------------
unsigned int RandSeed;
unsigned int GetRand(unsigned char MaxRND)
{
RandSeed = (33 * (RandSeed) + 0x38) & 0xFFFFFF;
return ((RandSeed * ( (int)MaxRND + 1 ) >> 0x18))%MaxRND;
}

extern void kill_data(void *p, void (*func_p)(void *));
void ELF_KILLER(void)
{  
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}
void Suicide()
{
   if(mac)mfree(mac);
   FreeWS(ws1);
   SUBPROC((void *)ELF_KILLER);
};

int _hc(char c)
{
  if(c>='0'&&c<='9')
   return c-'0';
  else if(c>='A'&&c<='F')
   return c-'A'+0xA;
  if(c>='a'&&c<='f')
   return c-'a'+0xA;
  return 0;
};

unsigned int Hex2Int(char *s)
{
if(s==0) return 0;
unsigned int a=0;
int i=0;
while(s[i]!=0)
  {
  a=(a<<4)+_hc(s[i++]);
  };
return a;
};


unsigned int Str2Int(char *s)
{
if(s==0) return 0;
unsigned int a=0;
int i=0;
while((s[i]>='0')&&(s[i]<='9'))
  {
  a=(a*10)+(s[i++]-'0');
  };
return a;
};

char * ReadFile(const char * path)
{
char *mem;
unsigned int i, err;
int handle;
int len,sz;
// Работа с файлами стандартна:
handle=fopen(path,A_ReadOnly+A_BIN,P_READ,&err);
if(handle==-1) return 0;

len=lseek(handle,8*1024*1024,0,&err,&i);// ->size of file if fails
lseek(handle,0,0,&err,&i);
mem=(char*)malloc(len+1);
if(mem!=0){
  sz=fread(handle,mem,len,&err);
  mem[len]=0;//for treating bu as string
  if(sz!=len){
    mfree(mem);
    return 0;
    };
  fclose(handle,&err);
  //if(size!=0) *size=sz;
  return mem;
  }
else{
 fclose(handle,&err);
 return 0;
};
};

char * clonestr(const char *a)
{
 char *b=(char*)malloc(strlen(a)+1);
 strcpy(b,a);
 return b;
};
//------------------------------------------------

char * xs(char * c)
{
  static char bu[16];
  if(c==0) return "<EOF>";
  if(*c<32) sprintf(bu,"0x%x",*c);
  else sprintf(bu,"'%c'/0x%x",*c,*c);
  return bu;
  };

inline short keytab(char c)
{
  if(c>='0'&&c<='9') return c;
  if(c=='*'||c=='#') return c;

  if(c=='@') return GREEN_BUTTON;
  if(c=='!') return RED_BUTTON;

  if(c=='+') return ENTER_BUTTON;
  if(c=='L') return LEFT_SOFT;
  if(c=='R') return RIGHT_SOFT;

#ifdef ELKA
if(c=='J') return POC_BUTTON;
#else
if(c=='J') return INTERNET_BUTTON;
#endif
  if(c=='%') return '0'+GetRand(10);
  if(c=='$') return '2'+GetRand(8);

  if(c=='<'||c=='l') return LEFT_BUTTON;
  if(c=='>'||c=='r') return RIGHT_BUTTON;
  if(c=='^'||c=='u') return UP_BUTTON;
  if(c=='V'||c=='d') return DOWN_BUTTON;

  if(c=='[') return VOL_UP_BUTTON;
  if(c==']') return VOL_DOWN_BUTTON;

  return -1;
};





void Step()
{
  //interrupted
  if(brk) s=ST_END;
  
  int delay;
  switch(s)
  {
  //------------------------------------  
  case ST_NORM:
    {
    delay=delay_keybreak;  
    while(*po==10||*po==13||*po==';') po++;
    switch(*po)
      {
      case '`':
        {
        char * p1=po+1;
        char * p2=po+1;
        while(*p2&&*p2!='`')p2++;
        if(*p2==0)          {
          s=ST_ERROR;
          strcpy(ebu,"Unexpected <EOF>");     
          }
        else{       
        po=p2;  
        char bu[256];
        memcpy(bu,p1,p2-p1);
        bu[p2-p1]=0;
        ShowMSG(2,(int)bu);
        wsprintf(ws1,"%t",bu);
        ExecuteFile(ws1,0,0);  
                
        s=ST_WAIT;
        StartCpuUsageCount();
        delay=delay_wait_1+delay_longpause;
        if(show){wsprintf(&qw,"wait `...`");   wc=0;};
        };
        };
        break;
        
      case 'N':
        if(ShowNativeMenu==0)
          {
          s=ST_ERROR;
          strcpy(ebu,"No ShowNativeMenu() address defined ");     
          }
       else
          { 
          ShowNativeMenu();
          delay=delay_smallpause;
          };
        break;
        
      case '(':
        {
        delay=t(Str2Int(po+1));  
        do{po++;}while(*po&&*po>='0'&&*po<='9');
        if(*po!=')')
           {
             s=ST_ERROR;
             sprintf(ebu,") expected but %s founded",xs(po));
           };
        };
        break;
        
      case ' ':case '.':
        delay=delay_smallpause;
        break;
        
      case 'P':
        delay=delay_longpause;
        break;
        
      case '/':
        break;        
        
       
      case '|':
        {         
        po++;  
        short ch=keytab(*po);              
        if(ch==-1){s=ST_ERROR;sprintf(ebu,"Unk character %s",xs(po));break;};
        KeyUp(ch);
        };        
        break;
        
      case '_':
        {         
        po++;  
        short ch=keytab(*po);              
        if(ch==-1){s=ST_ERROR;sprintf(ebu,"Unk character %s",xs(po));break;};
        KeyDown(ch);
        };      
        break;
        
      case '~':
        {         
        po++;  
        lpc=keytab(*po);              
        if(lpc==-1){s=ST_ERROR;sprintf(ebu,"Unk character %s",xs(po));break;};
        KeyDown(lpc);        
        s=ST_LONG_1;
        };   
        break;
        
      case 'W':
        {
        s=ST_WAIT;
        StartCpuUsageCount();
        delay=delay_wait_1+delay_keybreak;
        if(show){wsprintf(&qw,"wait W");
        wc=0;};
        };
        break;
        
      case 0:
        delay=1;
        s=ST_END;
        break;
        
      default:
        {         
        short ch=keytab(*po);      
        if(ch==-1){s=ST_ERROR;sprintf(ebu,"Unk character %s",xs(po));break;};
        KeyDown(ch);
        KeyUp(ch);
        };        
      };    
    po++;
    };break;
  //------------------------------------      
  case ST_LONG_1:
    {
    LongPress(lpc);
    s=ST_LONG_2;    
    delay=delay_keybreak;
    };
    break;
  //------------------------------------      
  case ST_WAIT:
    {
    if(GetCPULoad()<=wait_threshold)
      {
      s=ST_NORM;
      delay=delay_wait_3;
      }
    else
      {
      delay=delay_wait_2;
      if(show)wsprintf(&qw,"wait %d",wc++);
      };
    };
    break;    
  //------------------------------------      
  case ST_LONG_2:
    {
    KeyUp(lpc);        
    s=ST_NORM;    
    delay=delay_keybreak;
    };
    break;    
  //------------------------------------      
  //------------------------------------          
  case ST_ERROR:
    ShowMSG(2,(int)ebu); 
  case ST_END:
   LockSched();
    brk=1;
    if(IsTimerProc(&watch_timer)) GBS_StopTimer(&watch_timer);
    if(show) if(IsTimerProc(&paint_timer)) GBS_StopTimer(&paint_timer);
   UnlockSched();
    Suicide();
    return;
  //------------------------------------          
  default:
     strcpy(ebu,"wrong state!");
     s=ST_ERROR;
  };
GBS_StartTimerProc(&step_timer,delay,&Step);
};

void Watch()
{
if(*RamPressedKey()) brk=1;
else if(!brk)GBS_StartTimerProc(&watch_timer,watch_delay,&Watch);
};

void Paint()
{
static unsigned int Red=0x640000FF;  
static unsigned int Black=0x64000000;  
DrawString(s==ST_WAIT?&qw:&q,0,YDISP,256,256,FONT_SMALL_BOLD,0,(char*)&Black,(char*)&Red);
if(!brk)GBS_StartTimerProc(&paint_timer,paint_delay,&Paint);
};

int main(char * self,char * path)
{
  static const char pt[]="%t";
  wsprintf(&q,pt,"mac");
  wsprintf(&qw,pt,"wait");
  
  //randomize()
  TDate date; TTime time;
  GetDateTime(&date,&time);
  RandSeed=time.millisec+time.sec*time.min+date.day*date.month+date.year+GetCPULoad();

  InitConfig();
  
  //recalc delays
delay_keybreak=t(delay_keybreak);
watch_delay=t(watch_delay);
pre_delay=t(pre_delay);
paint_delay=t(paint_delay);
delay_longpause=t(delay_longpause);
delay_smallpause=t(delay_smallpause);
delay_wait_1=t(delay_wait_1);
delay_wait_2=t(delay_wait_2);
delay_wait_3=t(delay_wait_3);

  
  ShowNativeMenu=(void (*)())Hex2Int(ShowNativeMenu_);
  
  if((path==0)||( (((unsigned int)path)>>28)!=0xA ))
    {
      ShowMSG(2,(int)"No macro!");
      Suicide();
      return 0;
    }
  else
    {
      if(path[1]==':'&&path[2]=='\\'&&path[0]>='0'&&path[0]<='4')
        {
          mac=ReadFile(path);
          if(mac==0)
            {
            ShowMSG(2,(int)"Cant open macro file!");
            Suicide();
            return 0;
            }
        }
      else
        mac=clonestr(path); 
    };
  
  s=ST_NORM;
  po=mac;   
  brk=0;
  ws1=AllocWS(256);
  
  GBS_StartTimerProc(&watch_timer,pre_delay,&Watch);
  GBS_StartTimerProc(&step_timer,pre_delay,&Step);
  if(show)GBS_StartTimerProc(&paint_timer,pre_delay,&Paint);
  return 0;
};
