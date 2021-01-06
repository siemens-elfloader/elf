#include "swilib.h"
#include "obs.h"

#define MakeFunc(prot,name,adr) prot* const name =  (prot*)adr
HObj gObj=NULL;
typedef void* PlaySeekP4 (int,...);
typedef int PlaySeekP (int, int);
typedef int PlaySeekP3 (void*, int*);
typedef void* PlaySeekP2 (int);
//PlaySeekP * const PlayMelody_Seek =(PlaySeekP*)0xA059B768;
//PlaySeekP2 * const _GetSoundObjById2 =(PlaySeekP2*)0xA0635360;
//MakeFunc(PlaySeekP4,_GetSoundObjById,0xA0635360);
//PlaySeekP3 * const _GetSoundObjDuration =(PlaySeekP3*)0xA0CC40B8;
//PlaySeekP3 * const _GetSoundObjPosition =(PlaySeekP3*)0xA0CC4378;
//MakeFunc(PlaySeekP4,Obs_TranslateMessage,0xA0CDDE60);
//MakeFunc(PlaySeekP4,Obs_TranslateMessageGBS,0xA0CDE10C);
//MakeFunc(PlaySeekP4,Obs_SetPosition,0xA0CC42B4);
//MakeFunc(PlaySeekP4,Obs_Pause,0xA0CC7F84);
//MakeFunc(PlaySeekP4,Obs_Resume,0xA0CC8140);
//MakeFunc(PlaySeekP4,Obs_SetRenderOffset,0xA0D249EC);

//MakeFunc(PlaySeekP4,Obs_GetCapability,0xA0CC7C14);
//MakeFunc(PlaySeekP4,Obs_Prepare,0xA0CC7C84);

///MakeFunc(PlaySeekP4,Obs_Mam_SetPurpose,0xA0CC8444);

//MakeFunc(PlaySeekP4,Obs_Sound_SetPurpose,0xA0CD0820);
// MakeFunc(PlaySeekP4,Obs_Sound_SetHandsFree,0xA0CD075C);
//     MakeFunc(PlaySeekP4,Obs_Sound_SetVolumeEx,0xA0CCFEC0 );
  //   MakeFunc(PlaySeekP4,Obs_SetScalingAlt,0xA0CD7C14 );     
          
extern void kill_data(void *p, void (*func_p)(void *));
#define MSG_Report  0xB034
const int minus11=-11;
  WSHDR *mws,*mws2;
__root int xxx=123;
volatile static int yyy;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

#define RGB8(R,G,B) (B+(G<<2)+(R<<5))


int curmode=-1; //1 -pics



void Log(int dummy, char *txt)
{
  unsigned int ul;
  int f=fopen("4:\\log",A_ReadWrite+A_Create+A_Append+A_BIN,P_READ+P_WRITE,&ul);
  if (f!=-1)
  {
    fwrite(f,txt,strlen(txt),&ul);
    fclose(f,&ul);
  }
  mfree(txt);
}
  int fh;

  RECT rc;
  DRWOBJ drwobj;
;
  
  
  
DrwImg221(IMGHDR *img, short x, short y){

  rc.x=0;
  rc.y=0;
  rc.x2=239;
  rc.y2=239;

  
//StoreXYWHtoRECT(&rc,x,y,(short)img->w,(unsigned short)img->h);
//  StoreXYWHtoRECT(&rc,x,y,(short)img->h,(unsigned short)img->w);  
      char *s=(char*)malloc(100);


   //    StoreXYWHtoRECT(&rc,x,y,(short)img->w,(unsigned short)img->h);  
   sprintf(s,"DrwImg2 %d %d %d %d %d %d \r\n",rc.x,rc.y,rc.x2,rc.y2,(short)img->w,(unsigned short)img->h);
     
    SUBPROC((void *)Log,0,s);      

  SetPropTo_Obj5(&drwobj,&rc,0,img);
  DrawObject(&drwobj);
}

void method0(MAIN_GUI *data)
{
   DisableIconBar(1); 
  DisableIDLETMR();
void *p=NULL;
//p=GetDataOfItemByID((GUI*)data,4);
p=GetDataOfItemByID(&data->gui,4);
  int i;
  int c;
  DrawRoundedFrame(0,0,239,319,0,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(20));
  c=data->i1;
  i=0;
//  DrwImg((IMGHDR *)&img1,2,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
///  wsprintf(data->ws1,"Redraw number %d",++data->i1);
  wsprintf(data->ws1," %0x",p);  
//  DrawString(data->ws1,5,30,230,100,11,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
}

void method1(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(256);
  data->ws2=AllocWS(256);
  data->gui.state=1;
}
KillObj(){
 if (!gObj) return;
  Obs_DestroyObject(gObj);
  gObj=NULL;
}
void method2(MAIN_GUI *data, void (*mfree_adr)(void *))
{
 KillObj(); 
  FreeWS(data->ws1);
  FreeWS(data->ws2);
  data->gui.state=0;
}

void method3(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  DisableIconBar(1);
  data->gui.state=2;
}

void method4(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}


int col=0;
IMGHDR  *myimg=NULL;
int dir=90;
int obFrameUpd(HObj hobj){

    wsprintf(mws,"Redraw number %d",col++);
//  DrawRoundedFrame(5,230,121,270,0,0,0,			GetPaletteAdrByColorIndex(0),			GetPaletteAdrByColorIndex(20));    
  DrawRoundedFrame(0,0,239,319,0,0,0,			GetPaletteAdrByColorIndex(1),			GetPaletteAdrByColorIndex(20));  
  DrawString(mws,5,230,121,270,11,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

    char *s=(char*)malloc(100);
    sprintf(s,"Frame upd\r\n");
      IMGHDR *tmpimg=NULL;
    SUBPROC((void *)Log,0,s);      
int err=Obs_Output_GetPictstruct(hobj,&tmpimg);
if (!err){ 

//      char *s=(char*)malloc(100);
      unsigned char m=tmpimg->bpnum;
//    sprintf(s,"bpnum %dx%d-%d\r\n",tmpimg->w,tmpimg->h,m);
  //  SUBPROC((void *)Log,0,s);      

int     msz=CalcBitmapSize (tmpimg->w,tmpimg->h,tmpimg->bpnum);
/*
if (myimg==NULL){
  myimg=malloc(sizeof(IMGHDR));
  myimg->bitmap=malloc(msz);  
}else{
  realloc( myimg->bitmap,msz);
}

  myimg->w=tmpimg->w;
  myimg->h=tmpimg->h;
  myimg->bpnum=tmpimg->bpnum;
  */

 // memcpy(myimg->bitmap,tmpimg->bitmap,msz);
//  zeromem(tmpimg->bitmap,msz/2);
//DrwImg2(myimg,00,00); 
/*
        short d=tmpimg->w;
      tmpimg->w=tmpimg->h;
      tmpimg->h=d;
      */
  
//  Obs_SetRenderOffset(gObj,rc.x,rc.y);
//    Obs_SetRenderOffset(gObj,rc.x,0);
//  StoreXYWHtoRECT(&rc,x,y,(short)img->h,(unsigned short)img->w);  
      char *s=(char*)malloc(100);


//       StoreXYWHtoRECT(&rc,x,y,(short)img->w,(unsigned short)img->h);  
   sprintf(s,"framessss %d %d %d %d %d %d \r\n",rc.x,rc.y,rc.x2,rc.y2,(short)tmpimg->w,(unsigned short)tmpimg->h);
     
    SUBPROC((void *)Log,0,s);        
    if (dir==0){
  rc.x=(240-tmpimg->w)>>1;
  rc.y=(320-tmpimg->h)>>1;
  rc.x2=rc.x+tmpimg->w;
  rc.y2=rc.y+tmpimg->h;
      
    Obs_SetRenderOffset(hobj,rc.x,rc.y);
    }else
      if (dir==90){
  rc.x=(240-tmpimg->w)>>1;
  rc.y=(320-tmpimg->h)>>1;
  rc.x2=rc.x+tmpimg->w;
  rc.y2=rc.y+tmpimg->h;
    Obs_SetRenderOffset(hobj,rc.x,rc.y);
  }
    
   SetPropTo_Obj5(&drwobj,&rc,0,tmpimg);
  DrawObject(&drwobj);
  
//       Obs_SetRenderOffset(gObj,(short)0,(short)60);    
//DrwImg2(tmpimg,70,70);  
    
    
//DrwImg2(myimg,70,70);  
//mfree(myimg->bitmap);
//mfree(myimg);

  //DrwImg2(tmpimg,120,120);        
}
  return 0;
}

int obError(HObj hobj,int error){
    char *s=(char*)malloc(100);
    sprintf(s,"obs-Error: %d %0x\r\n",error,error);
      SUBPROC((void *)Log,0,s);
      Obs_DestroyObject(hobj);
  return 0;
}

int obPrep(HObj hobj,int error){
      char *s=(char*)malloc(100);
    sprintf(s,"obs-prepa: %d %0x\r\n",error,error);
      SUBPROC((void *)Log,0,s);
//  Obs_SetOutputImageSize(gObj,239,160);//width
            
int   err=Obs_Start(hobj);
      char *s2=(char*)malloc(100);
    sprintf(s2,"start %x\r\n",err);
    SUBPROC((void *)Log,0,s2);
    /*
int   err=Obs_GetInfo(hobj,0);    
      

      char *s2=(char*)malloc(100);
    sprintf(s2,"info %x\r\n",err);
    SUBPROC((void *)Log,0,s2);         
    */
  return 0;
    
}
int obInfo(HObj hobj,int error){
      char *s=(char*)malloc(100);
    sprintf(s,"obs-info: %d %0x\r\n",error,error);
      SUBPROC((void *)Log,0,s);  
  
}
       

int obResumeCon(HObj hobj,int error){
      char *s=(char*)malloc(100);
    sprintf(s,"obs-resumecon: %d %0x\r\n",error,error);
      SUBPROC((void *)Log,0,s);  
  return 0;
};
int obParam (HObj hobj,int pl, int error){
      char *s=(char*)malloc(100);
    sprintf(s,"obs-0x36: %0x %0x\r\n",pl,error);
      SUBPROC((void *)Log,0,s);    
      if (pl==2)obFrameUpd(hobj);
      if (pl==1)Obs_Resume(hobj);
  return 0;
}
int pint=0;
int obPause (HObj hobj,int pl, int error){
      char *s=(char*)malloc(100);
    sprintf(s,"pause: %0x %0x\r\n",pl,error);
      SUBPROC((void *)Log,0,s);    
      if (pint==1){
        int r;
          GetPlayObjPosition((void*)gObj,&r);
          Obs_SetPosition(gObj,r);
          pint--;
      }
  return 0;
}

OBSevent ObsEventsHandlers[]={
  OBS_EV_FrameUpdate,(void*)obFrameUpd,
  OBS_EV_Error,(void*)obError,
  //OBS_EV_GetInfoCon,(void*)obInfo,
  OBS_EV_PauseCon,(void*)obPause,
  OBS_EV_ParamChanged, (void*)obParam,
//  OBS_EV_ResumeCon,(void*)obResumeCon,
  OBS_EV_PrepareCon,(void*)obPrep,
  OBS_EV_EndList,NULL
};




//MakeFunc(PlaySeekP4,GBS_MsgConv,0xA0091DC9);
//MakeFunc(PlaySeekP4,GBS_ConvKill,0xA009432F);
void SetupImage(){
/*  Obs_SetRotation
  Obs_SetOutputImageSize
  Obs_SetScaling5
  Obs_SetScalingAlt3
  */
}

void SetupVideo(){
/*  Obs_SetRotation
  Obs_SetOutputImageSize
  Obs_SetScaling5
  37
  Obs_Mam_SetPurpose
  16
  Obs_Sound_SetPurpose
  Obs_Sound_SetHandsFree
  Obs_Sound_SetVolumeEx
  Obs_SetScalingAlt3
  */
}

void SetupSound(){
/*
Obs_SetLoopCount
  Obs_Sound_SetVolumeEx
  16
  Obs_Mam_SetPurpose
  Obs_Sound_SetPurpose
  Obs_Sound_SetPWM
  Obs_Sound_SetTimeBeetweenPlay
  Obs_Sound_SetEventType
  
  Obs_Sound_SetHandsFree
  Obs_Sound_SetEqulizer
  Obs_Sound_Set3dAudio

  Obs_SetScalingAlt3
  */
}



int ShowAnimSt(WSHDR *path){
  int err=0;
  KillObj();
  HObj *pic=&gObj;
 WSHDR *ext;

  int uid;
  short pos;
  int len;
  if (!path)goto exit0;
  len=wstrlen(path); 
  pos= wstrrchr(path,len,'.'); 
  if (!pos)goto exit0;

  ext=AllocWS(len-pos);
  wstrcpybypos(ext,path,pos+1,len-pos);
  uid=GetExtUid_ws(ext); 
  FreeWS(ext);
  
  *pic=Obs_CreateObject(uid,0x2d,2,MSG_Report,1,0,&err);
  if (err)  return 2;
  err=Obs_SetInput_File(*pic,0,path);
  if (err)  goto exit1;  
  /*
  Obs_SetClientData
  Obs_SetOutputImageSize
  Obs_Graphics_SetClipping
  Obs_SetScaling5(0x15);
   Obs_SetScalingAlt3 (0x05)
  */
  /*
  if (width!=0){ 
    unsigned short w=width;  
    unsigned short h=height;      
    /*
    err=Obs_GetInfo(mypicObj,0);    
      if (err)  goto exit1;  
    err=Obs_GetInputImageSize(mypicObj,&w,&h);    
      if (err)  goto exit1;  
      */
  /*
    err=Obs_SetOutputImageSize(mypicObj,w,h);
      if (err)  goto exit1;      
    if (rot){  
      err= Obs_SetRotation(mypicObj,rot);
        if (err)  goto exit1;      
    }
    err=Obs_SetScaling(mypicObj,5);
      if (err)  goto exit1;          
  }
  */
  /*
  Obs_Prepare 
    Obs_GetInfo
  Obs_GetCapability
  */
    err=(int)Obs_Prepare(*pic);
    char *s=(char*)malloc(100);
    sprintf(s,"prep %x\r\n",err);
    SUBPROC((void *)Log,0,s);     
    
//  err=Obs_Start(*pic);
  //  if (err)  goto exit1; 
    goto exit0;
    /*
  err=Obs_Output_GetPictstruct(mypicObj,&tmpimg);
    if (err)  goto exit1;             
  msz=CalcBitmapSize (tmpimg->w,tmpimg->h,tmpimg->bpnum);
  myimg=malloc(sizeof(IMGHDR));
  myimg->w=tmpimg->w;
  myimg->h=tmpimg->h;
  myimg->bpnum=tmpimg->bpnum;
  myimg->bitmap=malloc(msz);
  memcpy(myimg->bitmap,tmpimg->bitmap,msz);
    */
exit1:
  Obs_DestroyObject(*pic);
  *pic=NULL;
exit0:  
  return err;
};
int ShowSndSt(WSHDR *path){
  int err=0;
  KillObj();
  HObj *pic=&gObj;
 WSHDR *ext;

  int uid;
  short pos;
  int len;
  if (!path)goto exit0;
  len=wstrlen(path); 
  pos= wstrrchr(path,len,'.'); 
  if (!pos)goto exit0;

  ext=AllocWS(len-pos);
  wstrcpybypos(ext,path,pos+1,len-pos);
  uid=GetExtUid_ws(ext); 
  FreeWS(ext);
  
  *pic=Obs_CreateObject(uid,0x34,2,MSG_Report,1,0,&err);
  if (err)  return 2;
  err=Obs_SetInput_File(*pic,0,path);
  if (err)  goto exit1;  
  /*
  Obs_SetClientData
  Obs_SetOutputImageSize
  Obs_Graphics_SetClipping
  Obs_SetScaling5(0x15);
   Obs_SetScalingAlt3 (0x05)
  */
  /*
  if (width!=0){ 
    unsigned short w=width;  
    unsigned short h=height;      
    /*
    err=Obs_GetInfo(mypicObj,0);    
      if (err)  goto exit1;  
    err=Obs_GetInputImageSize(mypicObj,&w,&h);    
      if (err)  goto exit1;  
      */
  /*
    err=Obs_SetOutputImageSize(mypicObj,w,h);
      if (err)  goto exit1;      
    if (rot){  
      err= Obs_SetRotation(mypicObj,rot);
        if (err)  goto exit1;      
    }
    err=Obs_SetScaling(mypicObj,5);
      if (err)  goto exit1;          
  }
  */
  /*
  Obs_Prepare 
    Obs_GetInfo
  Obs_GetCapability
  */
  
 err= (int)Obs_Mam_SetPurpose(*pic,0x16);
    char *s=(char*)malloc(100);
    sprintf(s,"mampurpose %x\r\n",err);
    SUBPROC((void *)Log,0,s);     
    
// err= (int)Obs_Sound_SetPurpose(*pic,0x16);
 s=(char*)malloc(100);
    sprintf(s,"purpose %x\r\n",err);
    SUBPROC((void *)Log,0,s);     

//err=   (int) Obs_Sound_SetHandsFree(*pic,0x0);
    s=(char*)malloc(100);
    sprintf(s,"hf %x\r\n",err);
    SUBPROC((void *)Log,0,s);     
err= (int) Obs_Sound_SetVolumeEx(*pic,0x4,1);
    s=(char*)malloc(100);
    sprintf(s,"vol %x\r\n",err);
    SUBPROC((void *)Log,0,s);     

    
    
  err=(int)Obs_Prepare(*pic);
 s=(char*)malloc(100);
    sprintf(s,"prep %x\r\n",err);
    SUBPROC((void *)Log,0,s);     
  

  //  if (err)  goto exit1; 
    goto exit0;
    /*
  err=Obs_Output_GetPictstruct(mypicObj,&tmpimg);
    if (err)  goto exit1;             
  msz=CalcBitmapSize (tmpimg->w,tmpimg->h,tmpimg->bpnum);
  myimg=malloc(sizeof(IMGHDR));
  myimg->w=tmpimg->w;
  myimg->h=tmpimg->h;
  myimg->bpnum=tmpimg->bpnum;
  myimg->bitmap=malloc(msz);
  memcpy(myimg->bitmap,tmpimg->bitmap,msz);
    */
exit1:
  Obs_DestroyObject(*pic);
  *pic=NULL;
exit0:  
  return err;
};

int ShowVidSt(WSHDR *path){
  int err=0;
  KillObj();
  HObj *pic=&gObj;
 WSHDR *ext;

  int uid;
  short pos;
  int len;
  if (!path)goto exit0;
  len=wstrlen(path); 
  pos= wstrrchr(path,len,'.'); 
  if (!pos)goto exit0;

  ext=AllocWS(len-pos);
  wstrcpybypos(ext,path,pos+1,len-pos);
  uid=GetExtUid_ws(ext); 
  FreeWS(ext);
  
  *pic=Obs_CreateObject(uid,0x2d,2,MSG_Report,1,0,&err);
  if (err)  return 2;
  err=Obs_SetInput_File(*pic,0,path);
  if (err)  goto exit1;  
  /*
  Obs_SetClientData
  Obs_SetOutputImageSize
  Obs_Graphics_SetClipping
  Obs_SetScaling5(0x15);
   Obs_SetScalingAlt3 (0x05)
  */
  /*
  if (width!=0){ 
    unsigned short w=width;  
    unsigned short h=height;      
    /*
    err=Obs_GetInfo(mypicObj,0);    
      if (err)  goto exit1;  
    err=Obs_GetInputImageSize(mypicObj,&w,&h);    
      if (err)  goto exit1;  
      */
  /*
    err=Obs_SetOutputImageSize(mypicObj,w,h);
      if (err)  goto exit1;      
    if (rot){  
      err= Obs_SetRotation(mypicObj,rot);
        if (err)  goto exit1;      
    }
    err=Obs_SetScaling(mypicObj,5);
      if (err)  goto exit1;          
  }
  */
  /*
  Obs_Prepare 
    Obs_GetInfo
  Obs_GetCapability
  */
  

char *s;    
// err= (int)Obs_Sound_SetPurpose(*pic,0x16);
 s=(char*)malloc(100);
    sprintf(s,"purpose %x\r\n",err);
    SUBPROC((void *)Log,0,s);     


//err=   (int) Obs_SetOutputImageSize(*pic,320,240);
    s=(char*)malloc(100);
    sprintf(s,"Obs_SetOutputImageSize %x\r\n",err);
    SUBPROC((void *)Log,0,s);     

//err=   (int) Obs_SetOutputImageSize(*pic,320,240);
//  err=   Obs_SetOutputImageSize(gObj,240+16,180-8);//width    
//  err=   Obs_SetOutputImageSize(gObj,160,120);//width
//  err=   Obs_SetOutputImageSize(gObj,320,240);//width  
            Obs_SetRotation(gObj,dir);
  err=   Obs_SetOutputImageSize(gObj,160,120);//width    

//  err=   Obs_SetOutputImageSize(gObj,180,240);//width 
//  err=Obs_SetScaling(*pic,5);
 err= (int)Obs_Mam_SetPurpose(*pic,0x16);
    s=(char*)malloc(100);
    sprintf(s,"mampurpose %x\r\n",err);
    SUBPROC((void *)Log,0,s);     
//  Obs_SetScalingAlt(*pic,3);      
//  err=   Obs_SetOutputImageSize(gObj,320,262);//width  
      s=(char*)malloc(100);
    sprintf(s,"is %x\r\n",err);
    SUBPROC((void *)Log,0,s);     
//  err=   Obs_SetOutputImageSize(gObj,320,240);//width  
//    err=Obs_SetRotation(*pic,90);
    err= (int) Obs_Sound_SetVolumeEx(*pic,0x0,1);
    s=(char*)malloc(100);
    sprintf(s,"vol %x\r\n",err);
    SUBPROC((void *)Log,0,s);     

;    
    
  err=(int)Obs_Prepare(*pic);
 s=(char*)malloc(100);
    sprintf(s,"prep %x\r\n",err);
    SUBPROC((void *)Log,0,s);     
  

  //  if (err)  goto exit1; 
    goto exit0;
    /*
  err=Obs_Output_GetPictstruct(mypicObj,&tmpimg);
    if (err)  goto exit1;             
  msz=CalcBitmapSize (tmpimg->w,tmpimg->h,tmpimg->bpnum);
  myimg=malloc(sizeof(IMGHDR));
  myimg->w=tmpimg->w;
  myimg->h=tmpimg->h;
  myimg->bpnum=tmpimg->bpnum;
  myimg->bitmap=malloc(msz);
  memcpy(myimg->bitmap,tmpimg->bitmap,msz);
    */
exit1:
  Obs_DestroyObject(*pic);
  *pic=NULL;
exit0:  
  return err;
};

int method5(MAIN_GUI *data, GUI_MSG *msg)
{
  DirectRedrawGUI();
  wsprintf(data->ws2,"MSG:%08X %08X",msg->gbsmsg->msg,msg->gbsmsg->submess);
  DrawString(data->ws2,5,95,239,227,11,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

  if (msg->gbsmsg->msg==MSG_PLAYFILE_REPORT)
  {
  }  
void *p;
int err;
int r=0;
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT:
      return(1); //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI

        
    case '1':

//             wsprintf(mws,"%s","0:\\Pictures\\Wallpaper\\Bird.gif");
//      wsprintf(mws,"%s","2:\\default\\WaitAnimation.gif");
      wsprintf(mws,"%s","4:\\a.jpg");
       ShowAnimSt(mws);
      break;
      
    case '2':
      wsprintf(mws,"%s","4:\\1.mp3");
       ShowSndSt(mws);
      break;
      
    case '3':
      wsprintf(mws,"%s","4:\\videos\\Haddaway - What Is Love_15fps.mp4");      
//      wsprintf(mws,"%s","4:\\videos\\Haddaway - What Is Love_low.mp4");
       ShowVidSt(mws);
      break;      
      
    case '4':
       KillObj();
      break;

      
    case '6':
      pint=1;
      Obs_Pause(gObj);
//         Obs_SetRenderOffset(gObj,0,0);
      Obs_SetRotation(gObj,90);
//  err=   Obs_SetOutputImageSize(gObj,240,320);//width 
  err=   Obs_SetOutputImageSize(gObj,320,240);//width   
//      Obs_SetRenderOffset(gObj,0,0);
     char  *s=(char*)malloc(100);
    sprintf(s,"is3 %x\r\n",err);
    SUBPROC((void *)Log,0,s);  
          GetPlayObjPosition((void*)gObj,&r);
      Obs_SetPosition(gObj,r+1);
      break;
      
    case '#':
       Obs_SetRenderOffset(gObj,(short)0,(short)10);
      break;
    case '*':
       Obs_SetRenderOffset(gObj,(short)0,(short)1);
      break;
      
    case '9':
      pint=1;
      Obs_Pause(gObj);
//      Obs_SetRenderOffset(gObj,0,0);
//      Obs_SetRotation(gObj,90);
  err=   Obs_SetOutputImageSize(gObj,160,120);//width 
//      Obs_SetRenderOffset(gObj,0,0);
      s=(char*)malloc(100);
    sprintf(s,"is3 %x\r\n",err);
    SUBPROC((void *)Log,0,s);  
          GetPlayObjPosition((void*)gObj,&r);
      Obs_SetPosition(gObj,r+1);
      break;

    case '5':
     Obs_Pause(gObj);
      break;      
    case '8':
     Obs_Resume(gObj);
      break;      
      break;
    case '7':
      {
      Obs_GetPosition(gObj,&r);
      Obs_SetPosition(gObj,r+1);
//         obFrameUpd(gObj);
      }      
      break;
    case '0':
      Obs_SetPosition(gObj,1000*60);

      break;
    }
  }
//  method0(data);
  return(0);
}

void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
{
    FreeWS(mws);
    FreeWS(mws2);
  kill_data(data, mfree_adr);
}

int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)method0,	//Redraw
  (void *)method1,	//Create
  (void *)method2,	//Close
  (void *)method3,	//Focus
  (void *)method4,	//Unfocus
  (void *)method5,	//OnKey
  0,
  (void *)method7,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,00,239,320};

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=(MAIN_GUI*) malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));

  main_gui->gui.canvas=(RECT *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

void ELF_KILLER(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)ELF_KILLER);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_Report)
  {
    char *s=(char*)malloc(100);
    sprintf(s,"myrep %08X %08X %08X\r\n",msg->submess,msg->data0,msg->data1);
    SUBPROC((void *)Log,0,s);
    void *msg_internal;
//    GBS_MsgConv ((int)&msg_internal,msg);
//    Obs_TranslateMessage((int)&msg_internal,ObsEventsHandlers);
//    GBS_ConvKill((int)&msg_internal);
       Obs_TranslateMessageGBS(msg,ObsEventsHandlers);
    return 0;
  }
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  return(1);
}

unsigned short maincsm_name_body[140];

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
    maincsm_onmessage,
    maincsm_oncreate,
#ifdef NEWSGOLD
0,
0,
0,
0,
#endif
maincsm_onclose,
sizeof(MAIN_CSM),
1,
&minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"TCSM");
}

int main()
{
     mws=AllocWS(256);
      mws2=AllocWS(256);
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  return 0;
}

//---------------------------------------------------------------------------
// Test menu
//---------------------------------------------------------------------------
void menup1(GUI *data)
{
      ShowMSG(1,(int)"Тестовое сообщение 1");
}

void menup2(GUI *data)
{
      ShowMSG(1,(int)"Тестовое сообщение 2");
}

int icon[]={0x58,0};

const HEADER_DESC menuhdr={0,0,131,21,icon,(int)"Заголовок меню",LGP_NULL};
const int menusoftkeys[]={0,1,2};
const MENUITEM_DESC menuitems[2]=
{
  {NULL,(int)"Пункт 1",LGP_NULL,0,NULL/*menusoftkeys*/,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Пункт 2",LGP_NULL,0,NULL/*menusoftkeys*/,MENU_FLAG3,MENU_FLAG2},
};

const MENUPROCS_DESC menuprocs[2]={
  menup1,
  menup2
};

const SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Лев"},
  {0x0001,0x0000,(int)"Прав"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt=
{
  (SOFTKEY_DESC *)menu_sk,0
};

const MENU_DESC tmenu=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_skt,
  0,
  NULL,
  menuitems,
  menuprocs,
  2
};

void TestMenu(void)
{
  CreateMenu(0,0,&tmenu,&menuhdr,0,2,0,0);
}


