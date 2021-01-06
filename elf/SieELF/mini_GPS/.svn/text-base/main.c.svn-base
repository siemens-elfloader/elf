#include "..\inc\swilib.h"
#include "conf_loader.h"

#define idlegui_id (((int *)data)[DISPLACE_OF_IDLEGUI_ID/4])
CSM_DESC icsmd;
int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);

extern const int cfgx;
extern const int cfgy;
extern const int cfgx2;
extern const int cfgy2;
extern const int cfgcolor;
extern const int cfgcvcolor;
extern const int cfgfont;
extern const int cfgtext_attribute;
extern const int cfgupdate_time;
extern const char gps_dir[128];
extern const int wrlog;
extern const int wrnew;
extern const int skwd;
extern const int clrlog;
char filename[128];     // global? variable? for names? file?
char corr_name[128];   // Display on Ch. screen
int len_;   // length? otobrazhaemog? at Ch. screen 
int oldlac; //lac old figures? ci 
int oldci;  //
int oldlac1; //lac old figures? ci 
int oldcid;  //
int count;
GBSTMR update_tmr;  // For the timer? 
GBSTMR tm2;  //For the timer?


RAMNET GetNetParams()
{
  RAMNET Result;
  zeromem(&Result, sizeof(RAMNET));
  Result = *RamNet();
  return Result;
}

void GetFileName()
{
  RAMNET Res;
  Res = GetNetParams(); 
  sprintf(filename,"%s\\%u\\%u-%u.tmo",gps_dir,Res.lac,Res.ci,Res.lac);  
}

void writetolog(){
  unsigned int errcode;
  volatile int hFile = -1;
  RAMNET Res;
  Res = GetNetParams(); 
  char *logfile = malloc(128);;
  sprintf(logfile,"%s\\logfile.txt",gps_dir);
  hFile = fopen(logfile,A_WriteOnly+A_Append+A_Create,P_WRITE,&errcode);
WSHDR *ws5 = AllocWS(256);
TDate date; TTime time;
GetDateTime(&date,&time);
char data[128];
if (!(Res.ci==0 || Res.lac==0))
{
  sprintf(data,"[%02d-%02d-%04d - %d:%02d:%02d] Network change: [Cell ID:%u, LAC:%u]\r\n",date.day, date.month,date.year,time.hour,time.min,Res.ci,Res.lac);
}
else {
  sprintf(data,"[%02d-%02d-%04d - %d:%02d:%02d] Net Search \r\n",date.day, date.month,date.year,time.hour,time.min);
     }
  str_2ws(ws5,data,1000);
    unsigned int len = wstrlen(ws5);//length learn? zapisannog? 
    fwrite(hFile,data,len,&errcode);
FreeWS(ws5);
fclose(hFile,&errcode);
}


int MyIDLECSM_onMessage(CSM_RAM* data, GBS_MSG* msg)
{
  int csm_result;
	
	 csm_result=old_icsm_onMessage(data, msg);
	
  if (IsGuiOnTop(idlegui_id))
  {
    GUI *igui=GetTopGUI();
    if (igui)
    {
      void* idata = GetDataOfItemByID(igui, 2);
      if (idata)
      {
        void load_name();
        load_name();
	void *canvasdata=((void **)idata)[DISPLACE_OF_IDLECANVAS/4];
        WSHDR *ws = AllocWS(256);
        str_2ws(ws,corr_name,len_);
        DrawCanvas(canvasdata,cfgx,cfgy,cfgx+(wstrlen(ws))*6,cfgy+12,1);
        DrawString(ws,cfgx,cfgy,cfgx2,cfgy2,cfgfont,cfgtext_attribute*2,GetPaletteAdrByColorIndex(cfgcolor),GetPaletteAdrByColorIndex(cfgcvcolor));
        FreeWS(ws);
      }
    }
  }
  return(csm_result);
}

void Savenew()
{
  unsigned int errcode;
  volatile int hFile = -1;
  RAMNET Res;
  Res = GetNetParams(); 
  GetFileName();
hFile = fopen(filename,A_WriteOnly+A_Create,P_WRITE,&errcode);
if(hFile==-1)
{
      char dir[128];
      sprintf(dir,"%s\\%u",gps_dir,Res.lac);
      mkdir(dir, &errcode);
      Savenew();
}
else{
WSHDR *ws0 = AllocWS(256);
if (skwd) {
wsprintf(ws0,"0 %u-%u",Res.ci,Res.lac);
          }
else {
wsprintf(ws0,"%u-%u",Res.ci,Res.lac);
      }

    unsigned int len = wstrlen(ws0);
    fwrite(hFile,ws0->wsbody,len*2+2,&errcode);
    unsigned int crc = (int)ws0->wsbody[0];
    void *temp;
    char *arr;
    temp = ws0->wsbody;
    arr = temp;
    for(int i=2;i<(len+1)*2;i++)
    {
      crc = crc ^ arr[i];
    }
    fwrite(hFile,&crc,2,&errcode);
FreeWS(ws0);
}
//if(errcode){ ShowMSG(1,(int)"error !");}
fclose(hFile,&errcode);
}

void load_name()
{
  unsigned int errcode;
  volatile int hFile = -1;
  GetFileName();
  hFile = fopen(filename,A_ReadWrite,P_READ+P_WRITE,&errcode);
  if(hFile==-1)//if the file? no?
  {
    //ShowMSG(1,(int)"naiden? new network!");
    if(wrnew)
    {//write new id
        Savenew();//create file 
        load_name();//run? anew
    }
    else
    {//to display current id,we must build a string to display
      RAMNET Res;
      Res = GetNetParams();
      sprintf(corr_name,"%u-%u",Res.ci,Res.lac);
      len_=strlen(corr_name);
    }
  }
  else 
  {
    if (skwd) 
    {
      int str_len = 0;
      fread(hFile,&str_len,2,&errcode);
      WSHDR *ws1=AllocWS(str_len);
      lseek(hFile,4,0,&errcode,&errcode);
      fread(hFile,ws1->wsbody,(str_len+1)*2,&errcode);
      CutWSTR(ws1,str_len-2);
      len_=(str_len-2)*4;
      ws_2str(ws1,corr_name,len_);
      FreeWS(ws1);
    }
    else 
    {
      int str_len = 0;
      fread(hFile,&str_len,2,&errcode);//
      WSHDR *ws1=AllocWS(str_len);
      errcode=0;
      lseek(hFile,0,0,&errcode,&errcode); // positioning at the beginning of the file? 
      fread(hFile,ws1->wsbody,(str_len+1)*2,&errcode);
      len_=(str_len)*4;
      ws_2str(ws1,corr_name,len_);
      FreeWS(ws1);
    }
  }
  //if(errcode){ ShowMSG(1,(int)"error !");}
  fclose(hFile, &errcode);
}

void check()
{
  RAMNET Res0;
  Res0 = GetNetParams(); 
  if (Res0.ci!=oldci || Res0.lac!=oldlac)
  { 
  oldlac=Res0.lac; oldci=Res0.ci;
  writetolog();
  }
  GBS_StartTimerProc(&update_tmr,262*cfgupdate_time,check);
}

int main()
{
  unsigned int err;
  InitConfig();
  
  if(clrlog)
  {
    char *logfile0 = malloc(128);;
    sprintf(logfile0,"%s\\logfile.txt",gps_dir);
    unlink(logfile0,&err);
  }
  
  if(!isdir(gps_dir,&err)){//if no folder?   
    mkdir(gps_dir,&err);//create it 
  }
//  if(err){ ShowDialog_Error(1,(int)"happened? error !");}
  
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);//Mouth at home? Screen savers?
  memcpy(&icsmd,icsm->constr,sizeof(icsmd));//
  old_icsm_onMessage=icsmd.onMessage;//
  icsmd.onMessage=MyIDLECSM_onMessage;// 
  icsm->constr=&icsmd;//
  
  if (wrlog) GBS_StartTimerProc(&update_tmr,262*cfgupdate_time,check);//write? Law?  //  GBS_StartTimerProc(&update_tmr,262*60,InitConfig);
  return 0;
}
