#define lograh_cpp
#include "lograph.h"
#include "AKKUSRC.h"


TLograph::TLograph(){npts=0;LastNAmsg="";LoadLogFile();/*CalcMaxLineLength();*/};
TLograph::~TLograph(){};

#define MAXLINELENGTH  256
//int MAXLINELENGTH=50;
#define MAXLOGFILEBLOCK ((MAXLINELENGTH+2)*LOGRAPHMAXPOINTS)

extern int logopt_cpuclock;
extern int logopt_net;
extern int logopt_cpuclock;
extern int logopt_cpuload;
extern int logopt_iscalling;
extern int logopt_gprs;
extern int logopt_lte;

/*void TLograph::CalcMaxLineLength()
{
 int s=50;
 if(logopt_cpuclock) s+=16;
 if(logopt_net) s+=10;
 //if(logopt_) s+=;
 //if(logopt_) s+=;
 //if(logopt_) s+=;
    
 MAXLINELENGTH=s;
};*/

float TLograph::EstimateElapsedTime()
{    
#define ERR(m) {LastNAmsg=m;return -1;};
#define ERRM(m,p)  {sprintf(ebu,m,p);LastNAmsg=ebu;return -1;};
  
  if(npts<2)ERR("N/A:n<2");
  extern int LOOKBACKHOURS;
  
  UTIME now=Now();
  int dcap=0;
  UTIME dutime=0;
  
  UTIME timelimit=Hours2Utime(LOOKBACKHOURS);
  //[a,b]
  TSample * b=GetPoint(0), *a;
  int i=1;  
  do{
    if((a=GetPoint(i))==0) break;
    if(dutime>timelimit) break;
     //correct timespan
      if(b->time > a->time)        
      //not charge
      if(a->cap >= b->cap)
        {
        if(b->time - a->time > timelimit-dutime)
            {
            dcap+=(int)(1.0*(timelimit - dutime)/(b->time - a->time)*(a->cap - b->cap));
            dutime+=(timelimit - dutime);
            break;
            } 
          else
            { 
            dcap+=(a->cap - b->cap);
            dutime+=(b->time - a->time);
            }
        };
    b=a;
    i++;
    }
  while(1);
  
  if(dutime==0) ERR("N/A:dt=0");   
  if(dcap==0) ERR("N/A:d%=0");   
  //patology
  if(dutime<0) ERRM("!dt=%d<0",dutime);   
  if(dcap<0) ERRM("!dcap=%d<0",dcap);   
  
  float h=Utime2Hours( (long)((1.0*GetPoint(0)->cap)*dutime/(1.0*dcap))+GetPoint(0)->time - now);
  //patology
  if(h<0) ERRM("!%.1fh<0",h);
  return h;
};
//in hours




extern char LOGPATH[128];

void TLograph::WriteLog(char *text)
{
  unsigned int ul;
  if (!text) return;
  int f=fopen(LOGPATH,A_ReadWrite+A_Create+A_Append+A_BIN,P_READ+P_WRITE,&ul);
  if (f!=-1)
  {
    fwrite(f,text,strlen(text),&ul);
    fclose(f,&ul);
  }
}

void TLograph::AddPoint(UTIME time,char cap)
{
  if(npts<LOGRAPHMAXPOINTS) npts++;
  for(int j=npts-1;j>=1;j--)pts[j]=pts[j-1];
 
  pts->cap=cap;
  pts->time=time;
};



void TLograph::PushCurrentPoint()
{
  int cap=AkkuCapacity();
  int pow=-RamNet()->power;
  int clo=GetCPUClock();
  
  TDate date;
  TTime time;
  GetDateTime(&date,&time);
  static char bu[MAXLINELENGTH+1];
  char hu[64];
  
  UTIME utime=Now();
    
  //snprintf(bu,MAXLINELENGTH,"%02d:%02d %02d/%02d/%04d CAP=%d%s NET=%ddb CPUCLOCK=%dMHz\r\n",time.hour,time.min,date.day,date.month,date.year,cap,"%",pow,clo);
  snprintf(bu,MAXLINELENGTH,"%02d:%02d %02d/%02d/%04d CAP=%d%s",time.hour,time.min,date.day,date.month,date.year,cap,"%");
  
#define LOG_IT(name,fmtstr,fmtparam) if(logopt_##name){\
  sprintf(hu,fmtstr,fmtparam);\
    strncat(bu,hu,MAXLINELENGTH-strlen(bu)-3);\
  };

  LOG_IT(net," NET=%ddb",pow)  
  LOG_IT(cpuclock," CPUCLOCK=%dMHz",clo)
  LOG_IT(cpuload," CPULOAD=%d%%",GetCPULoad())  
  LOG_IT(iscalling," ISCALLING=%d",IsCalling())
  LOG_IT(gprs," GPRS=%s",IsGPRSEnabled()?(IsGPRSConnected()?"connected":"enabled"):"disabled")
  LOG_IT(lte," LTE=%3.4fh",EstimateElapsedTime())  
    
  strncat(bu,"\r\n",MAXLINELENGTH);
  WriteLog(bu);

  AddPoint(utime,cap);
};

char * StrBack(char * limit,char * s)
{
  while(s>=limit && (*s!=10) && (*s!=13) ) s--;
  if(s<limit) return 0;
  while(s>=limit && (*s==10 || *s==13) ) s--;
  if(s<limit) return 0;
  
  while(s>=limit && (*s!=10) && (*s!=13) ) s--;
  return s+1;
};

void TLograph::LoadLogFile()
{
//load block  
char *mem;
unsigned int i, err;
int handle;

handle=fopen(LOGPATH,A_ReadOnly+A_BIN,P_READ,&err);
if(handle==-1) return ;

int len=lseek(handle,8*1024*1024,0,&err,&i);// ->size of file if fails
mem=new char[MAXLOGFILEBLOCK+1];
if(mem==0){fclose(handle,&err);return;};

int ofs=len-MAXLOGFILEBLOCK;
if(ofs<0) ofs=0;

lseek(handle,ofs,0,&err,&i);
int q=fread(handle,mem,MAXLOGFILEBLOCK,&err);
fclose(handle,&err);
if(q<=0) return;

mem[q]=0;//for treating bu as string

char * cur=mem+q-1;
char ** lines=new char*[LOGRAPHMAXPOINTS+1];
int nlines=0;

while((cur=StrBack(mem,cur)) && nlines<LOGRAPHMAXPOINTS)
  lines[nlines++]=cur;

while(nlines>0)
  {   
  nlines--; 
  int hh,mm, d,m,y,cap;
    if(sscanf(lines[nlines],
           "%d:%d %d/%d/%d CAP=%d",
           &hh,&mm, &d,&m,&y,&cap)>=6)        
                AddPoint(DateTime2Utime(y,m,d,hh,mm),cap);
     
  };

delete lines;
delete mem;  
};

