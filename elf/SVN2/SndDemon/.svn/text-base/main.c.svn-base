
#include "..\inc\swilib.h"

#include "..\inc\playsound.h"
#include "swilib2.h"
#include "conf_loader.h"
#ifdef ELKA
#include "snd_buffers.h"
#endif
#ifdef NEWSGOLD
#include "player_tags.h"
#include "some_utils.h"
#endif
#include "speech_txt.h"
#include "..\inc\mplayer.h"
word next=0;
char gbs[128]; //check may be short 

CSM_DESC icsmd;
//CSM_RAM oldicsm,*poldicsm;
void **picsm,*picsm2;
//-------------------------------------------------------------------
#ifdef NEWSGOLD
  #define _GetAkkuCapacity GetAkkuCapacity
  #define sMSG 0xDF01
  extern const unsigned int key_prev;  
  extern const unsigned int key_next;    
#else
  #define _GetAkkuCapacity  *RamCap
  #define sMSG
#endif

#ifndef NEWSGOLD
#ifndef NOHEADSET
  #define NOHEADSET
#endif
#endif

#define PLAYERTRACK
#ifdef NOHEADSET
  #undef   PLAYERTRACK
#endif




//-------------------------------------------------------------------
#ifdef NEWSGOLD
#ifndef ELKA
  byte gfp2=0;
  extern const unsigned int killPlr;  //mp3 call for S75
#endif
#endif
//-- vars ------------------------------------------------------------


//void (*old_icsm_onClose)(CSM_RAM*);
int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
GBSTMR mytmr;
#ifdef PLAYERTRACK  
  GBSTMR mytmr2;
#endif
const unsigned int refresh=130;
byte  llevel=0;
//byte  kbs=0;

  extern const unsigned int spc_min;
  byte rds=0;
#ifndef NOHEADSET
  int st=0;
#endif

  extern const unsigned int spc_level;
  extern const unsigned int spc_net;  
//-------------------------------------------------------------------
inline void ReadConfig(){
  InitConfig();
#ifdef PLAYERTRACK  
  scr_w=cTgr.x2-cTgr.x;
  initTags();
#endif  
   if (spc_net)  
    rds=*RamNetOnline();
  
  if (spc_level)     llevel=(_GetAkkuCapacity()-1)/5;  

}
//-------------------------------------------------------------------

//-- config ------------------------------------------

#ifndef NOHEADSET
  extern const unsigned int batt_level;
  extern const unsigned int exitOnHeadDisc;
  extern const unsigned int keyb_state;
#endif


extern const unsigned int spc_keyvol;
extern const unsigned int spc_kukvol;
extern const unsigned int spc_kukloc;
extern const unsigned int spc_kukkey;
//--------------------------------------------

#define _TDEBUG  
#ifdef TDEBUG  
  GBSTMR mytmr7;
#endif





//-------------------------------------------------------------------
 void ProcessTime(byte cl){
  GetDateTime (&dt,&tm);
  if (cl) if (tm.min!=0){
    return;
  };
  char tmp[128];
  char tmp2[30];  //check    
  tmp[0]=0;
  char ms[25]="v0aaavvvvvvvvvvvvvvvv0aa"; //hours
  sprintf (tmp2,"%st%d.wav;th%c.wav",cl?"thx.wav;":"",tm.hour,ms[tm.hour]);
  char ms2[11+11]="0ayyy00000000000000000";  //minutes                 
  if (tm.min<=20){         
    if (spc_min&&tm.min==0){
      sprintf (tmp,"%s;tx.wav;#",tmp2);      
    } else
    if (tm.min!=1&&tm.min!=2)
      sprintf (tmp,"%s;t%d.wav;tm%c.wav;#",tmp2,tm.min,ms2[tm.min]);
     else
       sprintf (tmp,"%s;t%de.wav;tm%c.wav;#",tmp2,tm.min,ms2[tm.min]);
  }else
   if (tm.min%10!=1&&tm.min%10!=2&&tm.min%10!=0)
     sprintf (tmp,"%s;t%d0.wav;t%d.wav;tm%c.wav;#",tmp2,tm.min/10,tm.min%10,ms2[tm.min%10]);
    else
     sprintf (tmp,"%s;t%d0.wav;t%de.wav;tm%c.wav;#",tmp2,tm.min/10,tm.min%10,ms2[tm.min%10]);
   if (cl)      SpeechPhrasesChk(tmp)    ;     
    else      SpeechPhrasesChkNat(tmp)    ;     
}
//-------------------------------------------------------------------
byte zds=0;
/*
char t_dash[]="#";
 char num[22]="\0";
void ProcessAON(){
  int cnt=strlen(num);
// ShowMSG(1,(int)num);
  char tmp[128],*tmp2;
  tmp2=tmp;
  //оптимизировать
  sprintf (tmp2,"kp.wav;"); //децл чит что все номера с +
  for (int i=1;(i<cnt)&&(i<18);i++){ //i,17 additional check gbs 125 bytes only 
        sprintf (tmp2,"k%c.wav;",num[i]);
        tmp2+=7;
  }
//  tmp2[0]='#';
//  tmp2[1]=0;

  sprintf (tmp2,t_dash);  //оптимизировать
  SpeechPhrasesChk(tmp);
}
/*
void TimerProcAON(void)
{ 
  ProcessAON();
}*/

void ProcessAccum(void){
  char tmp[64];
  byte lvl= _GetAkkuCapacity();
  byte lvl10=(lvl-1)/5;
  byte LS=*RamLS();
  if ((zds)==0&&LS)  {    
    SpeechPhrasesChk("found.wav;#");    
    llevel=lvl10;
  }else
  if ((zds)!=3&&(LS==3))      SpeechPhrasesChk("full.wav;#");
   else
  if ((zds)!=0&&(LS==0))      SpeechPhrasesChk("found0.wav;#");
  zds=LS;

  if (LS!=3&&((lvl10/2)!=(llevel/2))){
    tmp[0]=0;
    if (LS)
      sprintf (tmp,"up.wav;%d0.wav;percent.wav;#",lvl10/2);
    else
     if (lvl<spc_level) sprintf (tmp,"down.wav;%d0.wav;percent.wav;#",(lvl10/2)+1);
    if (tmp[0]!=0)      SpeechPhrasesChk(tmp);     
  };
  if (lvl<6&&llevel==1&&LS!=3) SpeechPhrasesChk("down.wav;5.wav;percent.wav;#"); 
  llevel=lvl10;
};

//-------------------------------------------------------------------

void ProcessNet(){
  byte rdsc=*RamNetOnline();
  if (rds!=rdsc){
    if (rds) SpeechPhrasesChk("sp.wav;#"); 
     else SpeechPhrasesChk("sn.wav;#"); 
    rds=rdsc;
  }
}
//-------------------------------------------------------------------
int cntr=1;
void TimerProc(void)
{ 
  cntr=cntr+1;
#define CNT_S 99
  if (cntr>CNT_S){
    cntr=1;
  }
  
  if (!IsCalling()){
    if (spc_kukvol&&(cntr==1)){
      ProcessTime(1);  
    }

    if  (spc_net)  ProcessNet();
    if  (spc_level)ProcessAccum();
    
  #ifndef NOHEADSET
    if (st>3)st--;
    if (st==3){
      st=2;
      MEDIA_PLAYER();
    }
  #ifdef ELKA
    if (cntr==1)  if (allowbuf==2){
      if (GetPlayStatus())
       SetupBuffers((buff_size+(buff_nof*256)));
      else
        SetupBuffers(oldAudValue);        
    }
  #endif
    
  #endif  
    
  }

#ifdef PLAYERTRACK  
  if (  pcsmadr)GetTags();
#endif  
  GBS_StartTimerProc(&mytmr, refresh, TimerProc);
}


word  klong=0;

int TopG (int disp){
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  if (!icsm) return 0;
  if (!IsGuiOnTop(((int *)icsm)[disp/4])) return 0;
  return 1;
}


//-------------------------------------------------------------
int my_keyhook(int submsg, int msg)
{
  int vl=TopG(DISPLACE_OF_IDLEGUI_ID);
 
  if (msg==KEY_UP){
    if (!IsCalling()){  

#ifdef NEWSGOLD      
       if (submsg!=RED_BUTTON&&submsg!=key_prev&&submsg!=key_next&&submsg!=PTT_BUTTON&&submsg!=35&&((!IsUnlocked()&&spc_kukloc)||(submsg==spc_kukkey&&vl))){        
#else
       if (submsg!=RED_BUTTON&&submsg!=35&&((!IsUnlocked()&&spc_kukloc)||(submsg==spc_kukkey&&vl))){        
#endif          
         if (klong){
           ProcessTime(0);
           klong=0;      
           return 2;    
         }else;
       } else
       {
#ifndef  NOHEADSET
       
       if (spc_keyvol&&IsUnlocked()&&TopG(DISPLACE_OF_EDGUI_ID)&&!st){
 #else
       if (spc_keyvol&&IsUnlocked()&&TopG(DISPLACE_OF_EDGUI_ID)){         
#endif         
            
         char tmp[]="k-.wav;#";
         if (submsg==35){
           if (klong)  tmp[1]='q';
            else  tmp[1]='s';
         }else
         if (submsg=='0'){
           if (klong)   tmp[1]='p';
            else     tmp[1]='0';
         }else
         if (submsg==42)tmp[1]='z';       
          else
         if (submsg>'0'&&submsg<='9'){
           tmp[1]=(char)submsg;
         }else;
         if (tmp[1]!='-'){
                          
            SpeechPhrasesChk(tmp);    

         }
       }
       }
       
     } 
    
     klong=0;         
   } else
     if (msg==LONG_PRESS){
       klong++;   
#ifndef NOHEADSET     
       if ((GetPlayStatus()==2)&&(klong&0x1)){
         if (submsg==key_prev||submsg==key_next){  
           
//            (void *)(MPlayer_VolChange(submsg==VOL_DOWN_BUTTON));
           if (submsg==key_prev)  MPlayer_Prev(); else  MPlayer_Next();
           GetTags();    

//           if (submsg==key_prev)   SUBPROC((void*)vol2);else            SUBPROC((void*)vol1);                         
           return 2;
           
         }
       }
#endif       
     }if (msg==KEY_DOWN) {
       klong=0;
       /*
#ifndef NOHEADSET            
       if (submsg==VOL_UP_BUTTON||submsg==VOL_DOWN_BUTTON) {
         if (_GetPlayStatus())
          return 2;
       }
      
#endif   
       */
     }  
  return 0;
}



#pragma inline=forced
inline int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
int inline strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}
/*
///////////////////////////////////////////////
int ingui=0;
  char s[]="s";
        char ss[]="s2";
       char sss[]="s3";

char *getNumber(){


 memset (num,0,sizeof(num));
   CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
 
      
  void *data=FindGUIbyId(((int *)icsm)[DISPLACE_OF_INCOMMINGGUI/4],NULL);
  if (data){

    int ***d1=        GetDataOfItemByID(data,9);
    int d3=d1[0x1c/4][0x08/4][0];
    WSHDR *snd=AllocWS(70);
    if (d3) {
      memcpy(snd->wsbody,(unsigned short*)d3,((unsigned short*)d3)[0]*2+2);         //maybe check len of mem

    }
    if (snd){
     
      if (snd->wsbody) {
        if (snd->wsbody[0]) {
             ws_2str(snd,num,20);
            
             FreeWS(snd);
                  
             return num;
           
        }
      }
    }
    FreeWS(snd);
  }
  return NULL;
}
*/





//-------------------------------------------
int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{


  #ifdef NEWSGOLD
#ifndef ELKA  // cheats for mp3 melody on calls at S75

  if (msg->msg==   MSG_INCOMMING_CALL){
    gfp2=(GetPlayStatus()==2);
    if (gfp2&&killPlr){
      MPlayer_Stop();
      MPlayer_Shutdown();
//      MEDIA_PLAYLAST();      
//      MPlayer_Toggle();

    }

  }else
  if (msg->msg==   MSG_END_CALL){
    if (gfp2&&killPlr){
      MEDIA_PLAYLAST();
//      MPlayer_Toggle();      
      gfp2=0;
    }


  }else;

#endif
  //new code (R) BoBa

#ifdef ELKA
  

  if (msg->msg==0x15680){
#else
  if (msg->msg==0x15682){
#endif    

    if ((   ((char *)(((int *)msg->data1)[6]))[0x11]  )==0){

      byte loc;
      loc=keyb_state==2?1:IsUnlocked()==keyb_state;
      
      if (loc&&(!batt_level||(_GetAkkuCapacity()>batt_level))){
     //insert 
      
    #ifdef ELKA        
          if (allowbuf)SetupBuffers((buff_size+(buff_nof*256)));
    #endif        

          if (!GetPlayStatus()){
            st=7;
          }else
            st=2;            
          
            MEDIA_PLAYLAST();          
       }
        
      ;//     PlayVibra(50,30,1);
  
    }
    if ((   ((char *)(((int *)msg->data1)[6]))[0x11]  )==1){
      //eject
    #ifdef ELKA        
          if (oldAudValue)SetupBuffers(oldAudValue);
    #endif        
          if (exitOnHeadDisc) MPlayer_Shutdown();
            else  MPlayer_Pause();

    }
  }
  
  
  
  
  
#endif    
    
return(old_icsm_onMessage(data,msg));  
  }
 ;
int MainCSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{

//  int csm_result;

#define edgui_id (((int *)data)[DISPLACE_OF_EDGUI_ID/4])


  /*
    if (!ingui) {
    if (TopG(DISPLACE_OF_INCOMMINGGUI)){
       char *num ;
      if (num=getNumber() ){
                   
    //    ProcessAON();
        ingui=1;
      }
    }
  }else{
    
    ingui=TopG(DISPLACE_OF_INCOMMINGGUI); //not good csm states
  }
  
*/
  
#ifdef PLAYERTRACK
 
  if (msg->msg== sMSG){
    ShowTag();
    GBS_StartTimer(&mytmr2,refresh, sMSG,0,MMI_CEPID);
    //csm_result = 1;
    return (1);
  }else{
//     csm_result=old_icsm_onMessage(data,msg); 
#else     
    //  csm_result=old_icsm_onMessage(data,msg);      
#endif     

  if(msg->msg == MSG_RECONFIGURE_REQ)   {
    
   extern const int REFMSG;
    extern const char *successed_config_filename;
   if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)    {
      if(REFMSG)ShowMSG(1,(int)"SndDemon config updated!");
      ReadConfig();
   }  
  }else
  if (msg->msg==MSG_PLAYFILE_REPORT)  {
    if ((msg->submess>>16)==next){    
      word kd=(msg->submess);
      if (kd==M_SAE_PLAYBACK_DONE||kd==M_SAE_PLAYBACK_ERROR)        SpeechPhrases(gbs);else;        
    };/*else{ //try capture song id
      int nextp=(msg->submess>>16);
      if (nextp){
        char p[128];
        sprintf(p,"%d    ",nextp);
        ShowMSG(1,(int)p);
      }
     
    }*/
    
    
  };/*else
*/
 ;

#ifdef PLAYERTRACK 
  }
#endif  
//  return(csm_result);
    return(1);
}

/*
void MyIDLECSM_onClose(CSM_RAM *data)
{
 

  extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  extern void *ELF_BEGIN;
  GBS_DelTimer(&mytmr);
#ifdef PLAYERTRACK  
  GBS_DelTimer(&mytmr2);    
        FreeWS(wstag);
#endif  
  RemoveKeybMsgHook((void *)my_keyhook);
  FreeWS(sndPath);
  FreeWS(sndFName);

  seqkill(data,old_icsm_onClose,&ELF_BEGIN,SEQKILLER_ADR());  
}*/

extern void kill_data(void *p, void (*func_p)(void *));

const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

#define SND_VER "SndDemon v1.50"

static void maincsm_oncreate(CSM_RAM *data)
{
    extern const int ALLOW_HELLO_MSG;
  if (ALLOW_HELLO_MSG) ShowMSG(1,(int)(SND_VER " loaded."));  
  sndPath=AllocWS(256);
  sndFName=AllocWS(256);

  AddKeybMsgHook((void *)my_keyhook);   
  
  GBS_StartTimerProc(&mytmr,216*3,TimerProc);  //262 delay for starting from demon
#ifdef PLAYERTRACK  

  GBS_SendMessage(MMI_CEPID, sMSG);
#endif  

}

static void Killer(void)
{
  extern void *ELF_BEGIN;

  /*LockSched();
  memcpy(poldicsm,&oldicsm,sizeof(oldicsm));  
  UnlockSched();
   */
  picsm[0]=picsm2;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
  
//    extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
//  extern void *ELF_BEGIN;

//  seqkill(data,old_icsm_onClose,&ELF_BEGIN,SEQKILLER_ADR());  


}

static void maincsm_onclose(CSM_RAM *csm)
{
    RemoveKeybMsgHook((void *)my_keyhook);  
  GBS_DelTimer(&mytmr);
#ifdef PLAYERTRACK  
  GBS_DelTimer(&mytmr2);    
        FreeWS(wstag);
#endif  
  FreeWS(sndPath);
  FreeWS(sndFName);

  SUBPROC((void *)Killer);
}

static unsigned short maincsm_name_body[140];

static const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
 MainCSM_onMessage,
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

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),SND_VER);
}


int main(char *exename, char *fname)
{
      CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  
  ReadConfig();
   UpdateCSMname();  
  LockSched();  

#ifdef ELKA // try find audiobuffer size hook
  
  if (allowbuf&&!audcfg){
    if (autosearch())
      ShowMSG(1,(int)"Entry point for Buffer change found.");
    else{
      ShowMSG(1,(int)"Entry point not found :(");    
      UnlockSched();        
      return -1;
    }
  }
#endif 



   save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;


  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
//  poldicsm=icsm;
//  memcpy(&oldicsm,icsm,sizeof(oldicsm));  
   picsm =&icsm->constr;
   picsm2 =icsm->constr;
  memcpy(&icsmd,icsm->constr,sizeof(icsmd));
  old_icsm_onMessage=icsmd.onMessage;
//  old_icsm_onClose=icsmd.onClose;
  icsmd.onMessage=MyIDLECSM_onMessage;  
//  icsmd.onClose=MyIDLECSM_onClose;  
  icsm->constr=&icsmd;

  UnlockSched();    
  
  return 0;
}

