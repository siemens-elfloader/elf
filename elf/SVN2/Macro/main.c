#include "..\inc\swilib.h"
#include "conf_loader.h"

//#define USE_MUTEX_BYTE


#define MMI_CEPID 0x4209
#define TMR_SECOND 216

#define t(a) ((a)*TMR_SECOND/1000)

#define SYM_NOP 0x01
#define SYM_LOOP_4 0x02
#define SYM_LOOP_8 0x03
#define SYM_LOOP_16 0x04
#define SYM_LOOP_INF 0x05


extern int use_mutex_byte;

//SYM_LOOP_4 backlow backhigh|(ctr<<4)
//   }         x      1

//SYM_LOOP_8 backlow backhigh ctr
//   }         x      1        2

//SYM_LOOP_16 backlow backhigh ctrhigh ctrlow
//   }         x      1        2       3

//SYM_LOOP_INF backlow backhigh 
//   }         x          @     

#define MAC_EXECUTING 0x3A
#define MAC_SUICIDE   0x3E

/*#define MAC_EXECUTING1 0xDA
#define MAC_SUICIDE1   0xCE
#define MAC_EXECUTING2 0xDB
#define MAC_SUICIDE2   0xCF
#define MAC_SUICIDE_ANY  0xC2*/

///char die_code=MAC_SUICIDE1;

char * MutexByte(){return (RamMenuAnywhere()+10);};
 
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

#define MAX_PAR 4

static unsigned int pars[MAX_PAR]={0,0,0,0};
static char free_pars[MAX_PAR]={0,0,0,0};

void free_params_data()
{
  for(int i=0;i<MAX_PAR;i++)
    if(free_pars[i])
      {
        free_pars[i]=0;
        mfree((void*)free_pars[i]);        
      };
};

void (*ShowNativeMenu)();
GBSTMR step_timer;
GBSTMR watch_timer;
GBSTMR paint_timer;
WSHDR * ws1;
volatile int brk;
int wc;
char ebu[128];
char bpath[256];

typedef enum
{
  ST_NORM,
  ST_ERROR,
  ST_END,
  ST_END2,
  ST_LONG_1,
  ST_LONG_2,
  ST_WAIT,
} TState;

unsigned char * mac=0;
unsigned char * po;
TState s;
short lpc;


static const unsigned short qq[16];
static WSHDR q={(unsigned short*)&qq,0,0,0,16};

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
  free_params_data();
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

int _hc2(char c)
{
  if(c>='0'&&c<='9')
   return c-'0';
  else if(c>='A'&&c<='F')
   return c-'A'+0xA;
  if(c>='a'&&c<='f')
   return c-'a'+0xA;
  return 0x200;
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

unsigned int Hex2Int_p(char *s,char ** next_not_digit)
{
if(s==0)
  {
  if(next_not_digit) *next_not_digit=0;
  return 0;
  };
unsigned int a=0;
unsigned int q=0;
while(*s!=0 && ((q=_hc2(*s++))<0x100) )
  {
  a=a*16+q;
  };
if(next_not_digit) *next_not_digit=s;
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

unsigned int Str2Int_p(char *s,char **nepo)
{
  if(s==0) {
    if(nepo) *nepo=0;
    return 0;
  }
unsigned int a=0;
while((*s>='0')&&(*s<='9'))
  {
  a=(a*10)+((*s++)-'0');
  };
if(nepo) *nepo=s;
return a;
};


unsigned char * ReadFile(const char * path)
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
  return (unsigned char*)mem;
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
//    if(*MutexByte()!=MAC_EXECUTING)
if(use_mutex_byte){  
    if(po == mac) *MutexByte()=MAC_EXECUTING;  
}
    
//    if(*MutexByte()==MAC_SUICIDE)
//       ShowMSG(2,(int)"Ooops!");
      
    delay=delay_keybreak;  
    while(*po==10||*po==13||*po==';'||*po==SYM_NOP) po++;
    switch(*po)
      {        
//SYM_LOOP_4 backlow backhigh|(ctr<<4)
//   }         x      1
        
      case SYM_LOOP_4:
        {
        unsigned char * zz=po;  
        unsigned int back=(po[1])|((po[2]&0xF)<<8);
        unsigned int ctr=(po[2])>>4;
        
        if(ctr>0)
            {
            ctr--;  
            po-=(1+back);
            }
        else
            po+=2;
        zz[1]=back & 0xFF;
        zz[2]=((back>>8)&0xF)|(ctr<<4);
        break;
        };  
        
     
       
//SYM_LOOP_8 backlow backhigh ctr
//   }         x      1        2        
      case SYM_LOOP_8:
        {
        unsigned char * zz=po;  
        unsigned int back=(po[1])|(po[2]<<8);
        unsigned int ctr=po[3];
        if(ctr>0)
            {
            ctr--;  
            po-=(1+back);
            }
        else
            po+=3;
        zz[1]=back & 0xFF;
        zz[2]=(back>>8);
        zz[3]=ctr;
        break;
        };  

//SYM_LOOP_16 backlow backhigh ctrlow ctrhigh
//   }         x      1        2       3        
        
      case SYM_LOOP_16:
        {
        unsigned char * zz=po;  
        unsigned int back=(po[1])|(po[2]<<8);
        unsigned int ctr=(po[3])|(po[4]<<8);
        if(ctr>0)
            {
            ctr--;  
            po-=(1+back);
            }
        else
            po+=4;
        zz[1]=back & 0xFF;
        zz[2]=(back>>8);
        zz[3]=ctr && 0xFF;
        zz[4]=(ctr>>8);
        break;
        };       
        
//SYM_LOOP_inf backlow backhigh 
//   }         x      @        
        
      case SYM_LOOP_INF:
        {
        unsigned int back=(po[1])|(po[2]<<8);
        po-=(1+back);
        break;
        };                  
        

      case '{':
        {
        *po=SYM_NOP;  
        unsigned char * la=po+1;
        int sco=1;
        while(*la)
          {
            if(*la=='{')  sco++;
            else if(*la=='}')  sco--;
            if(sco<0)
              {
              s=ST_ERROR;
              sprintf(ebu,"unexpected }");  
              goto fuck1;
              }
            else if(sco==0) break;
            la++;
          };
        if(*la==0)
              {
              s=ST_ERROR;
              sprintf(ebu,"not founded }");  
              goto fuck1;
              };
        //ppoints to }
        unsigned char * zu=la+1;
        unsigned int back=la-po-1;
        if(*zu!='x')        
          {
              s=ST_ERROR;
              sprintf(ebu,"expected 'x'");  
              goto fuck1;            
          };
        zu++;
        if(*zu=='@')
          {
          *la=SYM_LOOP_INF;  
          la[1]=back & 0xFF;
          la[2]=((back>>8) & 0xFF);          
          break;  
          };
        unsigned int ctr=Str2Int(zu)-1;
        if(ctr<10)
          {
          *la=SYM_LOOP_4;
          la[1]=back&0xFF;
          la[2]=((back>>8) & 0x0F) | (ctr<<4);
          }
        else if(ctr<100)
          {
          *la=SYM_LOOP_8;  
          la[1]=back & 0xFF;
          la[2]=((back>>8) & 0xFF);          
          la[3]=ctr;
          }
        else
          {
          *la=SYM_LOOP_16;  
          la[1]=back & 0xFF;
          la[2]=((back>>8) & 0xFF);          
          la[3]=ctr & 0xFF;
          la[4]=((ctr>>8) & 0xFF);          
          while(*zu && *zu>='0' && *zu<='9') *zu++=SYM_NOP;
          };
        
  fuck1:
        break;  
        };

        
      case '&':
        {
        po++;
        if(!strncmp(po,"call",4))
          {
          po+=4;  
          if(*po++!='{'){s=ST_ERROR;sprintf(ebu,"no { after &call");break;}; 
          unsigned char * nu=po;
          while(*po&&*po!='}') po++;
          *po=0;
          MakeVoiceCall(nu,0x10,0x20C0);
          delay=delay_longpause*2;  
          }
        else if(*po=='@')
          {
            typedef void (*TVoidFunc)(unsigned int p0,unsigned int p1,unsigned int p2,unsigned int p3);
            
            //address
            po++;
            unsigned int addr=Hex2Int_p(po,&po);
            if(*po!='{')
              {
              ((TVoidFunc)addr)(0,0,0,0);
//static char bu[130];
//sprintf(bu,"ad=`%x`",addr);
//ShowMSG(2,(int)bu);         
              delay=delay_longpause*2;
              //po++;
              break;
              };
            po++;
            char * poe=po;
            while(*poe && *poe!='}') poe++;
            if(*poe==0)
                    {
                    s=ST_ERROR;
                    sprintf(ebu,"no closing `}` in func call");  
                    break;
                    };          
            free_params_data();
            int npars=0;                        
            do
              {
                if(*po=='\"')
                  {
                    //string
                    free_pars[npars]=1;
                    po++;
                    char* fu=po;
                    while(*fu && *fu!='\"') fu++;
                    *fu=0;
                    pars[npars]=(unsigned int)clonestr(po);
                    *fu='\"';                    
                    po=fu+1;
                  }
                else if(*po=='$')
                  {
                    //hex
                    free_pars[npars]=0;
                    char * popo=po+1;
                    pars[npars]=Hex2Int_p(popo,&po);
                    if(po==popo)
                      {
                      s=ST_ERROR;
                      sprintf(ebu,"wrong $hex param");
                      break;
                      };
                    npars++;
                  }
                else
                  {
                    //int
                    free_pars[npars]=0;
                    char * popo=po+1;
                    pars[npars]=Str2Int_p(popo,&po);
                    if(po==popo)
                      {
                      s=ST_ERROR;
                      sprintf(ebu,"wrong int param");
                      break;
                      };
                    npars++;                    
                  };
                if(*po==',') po++;
                else if(*po=='}') break;
                else
                      {
                      s=ST_ERROR;
                      sprintf(ebu,"wrong param list");
                      break;
                      };                  
              }
            while(1);
            po=poe+1;
            if(s!=ST_ERROR)
              ((TVoidFunc)addr)(pars[0],pars[1],pars[2],pars[3]);
          }
        else
          {
          s=ST_ERROR;
          sprintf(ebu,"Unk cmd in `&`");
          };     
        break;  
        };
        
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
        //ShowMSG(2,(int)bu);
        if(bu[0]==0) strcpy(bu,bpath);
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
        delay=Str2Int(++po);
        while(*po&&*po>='0'&&*po<='9') po++;
        if(*po=='s')
          {
          po++;  
          delay*=1000;
          }
        else
        if(*po=='m')
          {
          po++;  
          delay*=60000;
          };          
        if(*po!=')')
           {
             s=ST_ERROR;
             sprintf(ebu,") expected but %s founded",xs(po));
           };
        delay=t(delay);
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
 //   brk=1;
    if(IsTimerProc(&watch_timer)) GBS_StopTimer(&watch_timer);
    if(show) if(IsTimerProc(&paint_timer)) GBS_StopTimer(&paint_timer);
   UnlockSched();
  case ST_END2:   
if(use_mutex_byte){
    if(brk!=2) *MutexByte()=0;    
}
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
LockSched();
extern int bak;
extern int breakeycode;  
int rac;
if((rac=*RamPressedKey())!=0)
  {
  if(bak || (rac==breakeycode)) brk=1;
  };
if(use_mutex_byte){
if(*MutexByte() == MAC_SUICIDE) 
    {
    brk=2;
    *MutexByte()=0;    
    };
}
UnlockSched();

if(!brk)
  GBS_StartTimerProc(&watch_timer,watch_delay,&Watch);
//else 
//  ShowMSG(1,(int)"brk=1 by watch");
//wsprintf(&q,"%d",*MutexByte());
//  {
//    s=ST_END2;
//  };  
};

void Paint()
{
if(brk) return;
static unsigned int Red=0x640000FF;  
static unsigned int Black=0x64000000;  
DrawString(s==ST_WAIT?&qw:&q,0,YDISP,256,256,FONT_SMALL_BOLD,0,(char*)&Black,(char*)&Red);
if(!brk)GBS_StartTimerProc(&paint_timer,paint_delay,&Paint);
};

int main(char * self,char * path)
{ 
if(use_mutex_byte){
  if(*MutexByte() == MAC_EXECUTING) 
    {
    *MutexByte() = MAC_SUICIDE;
    pre_delay+=watch_delay*16;
    }
  else 
    {
    *MutexByte() = MAC_EXECUTING;
    };
}
  
  strcpy(bpath,path);
  
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

/*  
  AddKeybMsgHook((void *)KeybMsgHook);
  
  RemoveKeybMsgHook((void*)KeybMsgHook);

#define KEYBHOOK_PASS   0
#define KEYBHOOK_BLOCK  2
  
int KeybMsgHook(int key, int m)
{  
if(!IsUnlocked()||menu->Exists()) return 0;

if((m==KEY_DOWN)&&(key==key_open))
    {
    return 2;
    };
return 0;
};*/

