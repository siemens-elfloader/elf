
#include "OsVar.h"
#include ".\..\inc\swilib.h"


//warning  две функции из "малой либы",  вроде есть во всех текущих либах и содержат адреса такие же как и в swilib.h их аналоги с номерами >100
#pragma swi_number=0xBB
__swi __arm void *LIB_Memset(void *s, int c, int n);

#pragma swi_number=0x59
__swi __arm void *LIB_Memcpy(void *dest,const void *source,int cnt);


__arm void GBS_SendMessageThumb(int cepid_to, int msg,int submess=0, void *data1=0, void *data2=0){
  GBS_SendMessage(cepid_to,msg,submess,data1,data2);
}
/*

__arm int pdcache_getvalThumb(unsigned char* ret, int maxlen_of_return_str, char cachetype, char *pd_entry_identifier_class, char  *pd_entry_identifier_sub){
  return  pdcache_getval(ret, maxlen_of_return_str,cachetype,  pd_entry_identifier_class, pd_entry_identifier_sub);
}
__arm int pdcache_setvalThumb(unsigned char *new_value, char cachetype,  char *pd_entry_identifier_class, char *pd_entry_identifier_sub){
return  pdcache_setval(new_value,  cachetype,  pd_entry_identifier_class,pd_entry_identifier_sub);
}
*/
///////////////////////


#include "incl.h"
#include ADRCH

#include "OsFunc.h"
#pragma once




#include "multisim_ipc.h"
#include "kvSIM_var.h"
#include "a3a8.h"
#include "msim_msg.h"

__no_init KV_SIM_CTRL_BLOCK *SIM_Data @ UNUSED_RAM_BASE_ADR ;



#define A38_Data_buffer			(SIM_Data->A38_Data_buffer)
#define Response_State			(SIM_Data->Response_State)
#define SIM_State		        (SIM_Data->SIM_State)
#define SIM_number		        (SIM_Data->SIM_number)
#define Block5401		        (SIM_Data->Block5401)
#define ReciveBuffer          (SIM_Data->ReciveBuffer)
#define ReciveBufferLen       (SIM_Data->ReciveBufferLen)
#define NeedAnswer            (SIM_Data->NeedAnswer)
#define Block5403             (SIM_Data->Block5403)
#define RAM_IMSI_Ptr          (SIM_Data->RAM_IMSI_Ptr)
#define RAM_KC_Ptr            (SIM_Data->RAM_KC_Ptr)
#define RAM_SPN_Ptr           (SIM_Data->RAM_SPN_Ptr)
#define RAM_F14_Ptr           (SIM_Data->RAM_F14_Ptr)
#define RAM_LOCI_Ptr          (SIM_Data->RAM_LOCI_Ptr)
#define RAM_FPLMN_Ptr          (SIM_Data->RAM_FPLMN_Ptr)

#define RAM_BCCH_Ptr          (SIM_Data->RAM_BCCH_Ptr)

#define REAL_SIM_IMSI			(SIM_Data->REAL_SIM_IMSI)
#define REAL_SIM_LOCI			(SIM_Data->REAL_SIM_LOCI)
#define REAL_SIM_BCCH         (SIM_Data->REAL_SIM_BCCH)
#define REAL_SIM_KC           (SIM_Data->REAL_SIM_KC)
#define REAL_SIM_SPN			(SIM_Data->REAL_SIM_SPN)
#define REAL_SIM_F14			(SIM_Data->REAL_SIM_F14)

///cheat structures


#define SIM_Cnt (SIM_Data->simCnt)
     
#define RAM_TIMER1                      (SIM_Data->RamTimer1)
#define RAM_TIMER2                      (SIM_Data->RamTimer2)

extern "C" void SIM_Cmd_Hook(int what, int cla, int ins, int p1, int p2, int rw, int SendLen, unsigned char *SendBuf, int RecvLen, unsigned char *RecvBuf);
extern "C" void SIM_Rsp_Hook(void);
extern "C" void MultisimINIT(void);
#ifndef NEWSGOLD
extern "C" void SaveHTTPProfile(int profile);
extern "C" void SaveSMSProfile(char profile);
#endif
extern "C" void InitMenu (); 


void ChangeSIM(int SimNum);

inline void Clear_FPNMN(){
  LIB_Memset(RAM_FPLMN_Ptr, 0xFF, FPLMN_DATA_BYTE_LEN);
}

 void CopySPN(unsigned char *dest, unsigned char *src)
{
  int k = 2, lng = 0;
  *dest++=*src++;
  *dest++ = 0x95;
  for(; *src && k < 15; k++)
  {
    unsigned char c = *src++;
    if(c >= 0xC0)
    {
      if(!lng)
      {
        *dest++ = 0x9B;
        k++;
        lng = 1;
      }
      *dest++ = c - 0xB0;
    }
    else
    {
      if(lng)
      {
        *dest++ = 0x91;
        k++;
        lng = 0;
      }
      *dest++ = c;
    }
  }
  for(int i = k; i < 16; i++)
    *dest++ = 0;
}

void SIM_Cmd_Hook(int what, int cla, int ins,
                int p1, int p2, int rw, 
                                int SendLen, unsigned char *SendBuf,
                int RecvLen, unsigned char *RecvBuf)
{
  int flag = 0;
  MultisimINIT();
  if(rw)
  {
    ReciveBuffer = RecvBuf;
    ReciveBufferLen = RecvLen;
  }
  NeedAnswer = 0;
  
  switch (ins)
  {
    case CONST_Run_GSM_A38:
      SIM_State = CONST_Run_GSM_A38;
      LIB_Memcpy(A38_Data_buffer, SendBuf, KI_BYTE_LEN); // copy the 'Rand' for GSM algorithm
      break;
    case CONST_Select_File:
      if (CONST_Select_Elementary_File == SendBuf[0])
        SIM_State = SendBuf[1]; // current file for emulator is last selected file
      break;
    case CONST_Get_Response:
      if(SIM_State == CONST_Run_GSM_A38)
        NeedAnswer = 1;  // if GSM algorithm already running answer to response ack
      break;             // another acks not captured
    case CONST_Read_Binary:
      NeedAnswer = 1;    // if MS want read file we need answer to ack
      break;
    case CONST_Update_Binary:
      switch (SIM_State) // updating emulated files with new data
      {
        case CONST_Select_LOCI_File:
          //store file LOCI into EEPROM block 5402
          LIB_Memcpy(Block5403.LOCI+p2, SendBuf, SendLen);
          EEFullWriteBlock(5403, Block5403.LOCI, 0x00, LOCI_DATA_BYTE_LEN,0,0);
          LIB_Memcpy(SIM_Data->SendBuf2, REAL_SIM_LOCI, LOCI_DATA_BYTE_LEN);
          flag=1;  // when virtual data is stored, SIM need write data physical SIM from
//          SendBuf=SIM_Data->SendBuf2;
          break;   // other buffer
        case CONST_Select_BCCH_File:
          //store file BCCH into EEPROM block 5402
          LIB_Memcpy(Block5403.BCCH+p2, SendBuf, SendLen);
          EEFullWriteBlock(5403, Block5403.BCCH, 0x10, BCCH_DATA_BYTE_LEN,0,0);
          LIB_Memcpy(SIM_Data->SendBuf2, REAL_SIM_BCCH, BCCH_DATA_BYTE_LEN);
          flag=1;  // when virtual data is stored, SIM need write data physical SIM from
//          SendBuf=SIM_Data->SendBuf2;          
          break;   // other buffer
        case CONST_Select_KC_File:
          //store file Kc into EEPROM block 5402
          LIB_Memcpy(Block5403.KC+p2, SendBuf, SendLen);
          EEFullWriteBlock(5403, Block5403.KC, 0x20, KC_DATA_BYTE_LEN,0,0);
          LIB_Memcpy(SIM_Data->SendBuf2, REAL_SIM_KC, KC_DATA_BYTE_LEN);
          flag=1;  // when virtual data is stored, SIM need write data physical SIM from
//          SendBuf=SIM_Data->SendBuf2;          
          break;   // other buffer
        default:
          break;
      }
      break;
    default:
      break;      
  }                                      

  if(flag)  // send command to real SIM ;)
    SIM_Access(what, cla, ins, p1, p2, rw, SendLen, SIM_Data->SendBuf2, RecvLen, RecvBuf);
  else
    SIM_Access(what, cla, ins, p1, p2, rw, SendLen, SendBuf, RecvLen, RecvBuf);
}

void SIM_Rsp_Hook(void)
{
  unsigned char CUR_KI[KI_BYTE_LEN];

  MultisimINIT();
  if(!NeedAnswer) return;    // if not need response leave function
  
 
  switch (SIM_State)         // switch with last selected file
  {
    case CONST_Run_GSM_A38:  // if MS want response for GSM algorithm
      if(SIM_number)         // for virtual SIM cards
        {
          LIB_Memcpy(CUR_KI, Block5401[SIM_number].KI, KI_BYTE_LEN);
          A3A8(A38_Data_buffer, CUR_KI, ReciveBuffer); // run aghorithm and store result
        }
      break;
    case CONST_Select_IMSI_File:
      RAM_IMSI_Ptr = ReciveBuffer; // capture IMSI address in RAM
      LIB_Memcpy(REAL_SIM_IMSI, ReciveBuffer, IMSI_DATA_BYTE_LEN);
      if(SIM_number)               // replace SIM response with virtual data from EEPROM
        LIB_Memcpy(ReciveBuffer, Block5401[SIM_number].IMSI, IMSI_DATA_BYTE_LEN);
      break;
    case CONST_Select_LOCI_File:   
      RAM_LOCI_Ptr = ReciveBuffer; // capture LOCI address in RAM
      LIB_Memcpy(REAL_SIM_LOCI, ReciveBuffer, LOCI_DATA_BYTE_LEN);
  //    if(SIM_number)               // replace SIM response with virtual data from EEPROM
        LIB_Memcpy(ReciveBuffer, Block5403.LOCI, LOCI_DATA_BYTE_LEN);
      break;
    case CONST_Select_SPN_File:   
      RAM_SPN_Ptr = ReciveBuffer;  // capture SPN address in RAM
      LIB_Memcpy(REAL_SIM_SPN, ReciveBuffer, SPN_DATA_BYTE_LEN);
      if(SIM_number)               // replace SIM response with virtual data from EEPROM
        CopySPN(ReciveBuffer, Block5401[SIM_number].SPN);

      break;
    case CONST_Select_File_14:    
      RAM_F14_Ptr = ReciveBuffer;  // capture F14 address in RAM
      LIB_Memcpy(REAL_SIM_F14, ReciveBuffer, SPN_DATA_BYTE_LEN);
      if(SIM_number)               // replace SIM response with virtual data from EEPROM
        CopySPN(ReciveBuffer, Block5401[SIM_number].SPN);
      break;
    case CONST_Select_BCCH_File: 
      RAM_BCCH_Ptr = ReciveBuffer; // capture BCCH address in RAM
      LIB_Memcpy(REAL_SIM_BCCH, ReciveBuffer, BCCH_DATA_BYTE_LEN);
  //    if(SIM_number)               // replace SIM response with virtual data from EEPROM
        LIB_Memcpy(ReciveBuffer, Block5403.BCCH, BCCH_DATA_BYTE_LEN);
      break;
    case CONST_Select_KC_File:   
      RAM_KC_Ptr = ReciveBuffer;   // capture KC address in RAM
      LIB_Memcpy(REAL_SIM_KC, ReciveBuffer, KC_DATA_BYTE_LEN);
  //    if(SIM_number)               // replace SIM response with virtual data from EEPROM
        LIB_Memcpy(ReciveBuffer, Block5403.KC, KC_DATA_BYTE_LEN);
      break;
    case CONST_Select_FPLMN_File:   
      RAM_FPLMN_Ptr = ReciveBuffer;   // capture FPLMN address in RAM
      break;
    default:
      break;  //other files not emulated
  }
  // answer already complete :)
  NeedAnswer = 0;
}


#ifdef NEWSGOLD  
__arm int  IdleGui(void){

  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  if (!icsm) return 0;
  if (!IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])) return 0;  
  if (!(GetTopGUI())) return 0; 
  return 1;
}
#endif


void ReturnToPhysicalSIM(void)
{
#ifndef NEWSGOLD  
  if (RAM_STBY)
#else
  if (IdleGui())    
#endif    
    ChangeSIM(Block5403.num2sw);
  else
    GBS_StartTimerProc(&RAM_TIMER1, 13000, &ReturnToPhysicalSIM);
}

/*  осталось от ~jhellico, наверно надо это все таки стереть и разобраться с GRPSD
void AttachGPRS(void)
{
  SwitchGPRS(0, 0); // attach
}  

void CheckOnline(void)
{
  if (RAM_NET_ONLINE)
  {
    SwitchGPRS(0, 1); // detach
    StartTimerProc(&RAM_TIMER2, 2*216, &AttachGPRS);
  }
  else
    StartTimerProc(&RAM_TIMER2, 216, &CheckOnline);
}
*/

#ifdef NEWSGOLD
#define SMS_CENTER_FILE "1:\\system\\opwv_msg\\sms.pd"    
#define SMS_CENTER_PARAM "sms.center..0.number"

/*
sample of SMS_CENTER_FILE

000032:T:sms.charset-optimize=1 
000026:T:sms.reply-path=0 
000031:T:sms.connection-type=3 
000043:T:sms.center..0.number=+79037011111 

*/


inline __arm char*  GetSetValFromCache(char *filename,char *name,char *newval){
  int f,f2;
  int frw;
  frw=newval!=NULL;
  char valbuf[64];
  unsigned int ul;
  char *buf,*buf2,*bufrw,*bufrws;
//  int val=-1;
  valbuf[0]=0;
  unsigned int len;
  if ((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)  {
    len=lseek(f,0,S_END,&ul,&ul);;
    if (!(buf2=(char*)malloc(len))) {
      fclose(f,&ul);
      return NULL;
    }
    if (frw&&!(bufrw=(char*)malloc(len+256))) { //warnig fixed size
        frw=0;
    }
    if (frw)bufrws=bufrw;
    lseek(f,0,S_SET,&ul,&ul);;
    if (fread(f,buf2,len,&ul)==len)    {
      buf=buf2;
      int next=0;
      char *str=(char *)malloc(256);
      do {
        sscanf(buf,"%6d:T:%[^=]=%63s",&next,str,valbuf);//==3;
        if (frw){
          if (!strcmp(str,name)) 
          bufrw+=sprintf(bufrw,"%06d:T:%s=%s",strlen(str)+strlen(newval)+11,str,newval);
         else
          bufrw+=sprintf(bufrw,"%06d:T:%s=%s",next,str,valbuf);      
         bufrw++;
         bufrw[0]=13;
         bufrw[1]=10;
         bufrw+=2;
         
        }else
        if (!strcmp(str,name))          break;else valbuf[0]=0;
        buf+=next+2;
      }while ((buf-buf2)<len);
      mfree (str);
      mfree (buf2);
      fclose(f,&ul);
    }
    else
      fclose(f,&ul);
  }
  if (frw){
    if ((f2=fopen(filename ,0x8301,0x100,&ul))!=-1) {fwrite(f2,bufrws,bufrw-bufrws,&ul);      
        fclose(f2,&ul);
    }
        mfree(bufrws);
    return newval;
  }
  if (valbuf[0]!=0)
  return valbuf;
  else return NULL;
};



//struct that  descibes profiles inet profile NSG
struct profnames{
  char num;  //1b  (0-9)
  char name[0x19];//0x01 maxlen 24, last byte 0 
  char unk2[2];//0x1a  (0)
  int active;//0x1c  (1 if active)
  int unk          ;//0x20 (0)
  int unkFFFE;//0x24 (FFFE0000)
};//0x28

// warning !!! новый код сам не тестил
inline void SetProfileCtx(int n){
    unsigned char *prf=NULL;
  prf=(unsigned char*)malloc(0x190);//0x28*0a
  if (prf){
    LIB_Memset(prf,0,0x190)  ;
    if (    GetAllCtxInfo(prf)){
      Set_Profile(prf+sizeof(profnames)*n);
    }
    mfree(prf);    
  }
};
#endif
 void ChangeSMSC(void){


#ifdef NEWSGOLD  
   //TODO fix  
//pdcache_setvalThumb(&Block5402[0x30], 0x2,NULL, "T:sms.center..0.number");        
   if (Block5403.SMSC[0]!=0)
      GetSetValFromCache(SMS_CENTER_FILE,SMS_CENTER_PARAM,(char*)Block5403.SMSC);
  /*
// фиксить всю эту гадость наверно хватит памяти с размером 0x20, а может просто надо было ложить в стек со смещением 4
  /unsigned char *mts=NULL;//[]="\1\0\0\0\0\0\0\0\0\0\0\\0\\0\0\00\00\0\0\0\0\0\0\0\0\0\0\0\0\0";
  mts =(unsigned char*)malloc(0x190);
  if (mts){
    LIB_Memset(mts,0,0x190)  ;
    mts[0]=Block5402[0x40 + 0x0F];
    Set_Profile(mts);
    mfree(mts)    ;
  }*/
// warning !!! попробовал переделать профили на NSG, сам не тестил 
  SetProfileCtx(Block5403.inet_profile);
#else   
    Set_HTTP_Profile(Block5403.inet_profile);
    Set_SMS_Profile(Block5403.sms_profile);
#endif  
};

#ifdef NEWSGOLD


 void UpdateSMSC(void){
  LIB_Memcpy(Block5403.SMSC,  GetSetValFromCache(SMS_CENTER_FILE,SMS_CENTER_PARAM,NULL),16);
   //TODO fix
//  pdcache_getvalThumb(&Block5402[0x30], 0x2,16, NULL, "T:sms.center..0.number");
  char *prf=NULL;
  prf=(char*)malloc(0x190);
  if (prf){
    LIB_Memset(prf,0,0x190)  ;
    if (    GetAllCtxInfo(prf)){
      for (char i=0;i<10;i++){
        if         (((profnames*)(prf+0x28*i))->active){
          Block5403.inet_profile=i;
          //  break;
        };
      }
    }
    mfree(prf);
  }
}
#endif

// пытался вставить костыли для случаев не рещистрации в сети, но как то с ними не очень
/*
#pragma swi_number=0x80D6
__swi __arm char *RamNetOnline();

#pragma swi_number=0x018C
__swi __arm void GBS_DelTimer_(GBSTMR *);

__arm void GBS_DelTimer(GBSTMR *a){
  GBS_DelTimer_(a);
};

__arm void TryRigesterInfinity(){
  if ((*RamNetOnline())){
//    ShowMSG(1,(int)"good net");
    return; 
  }
  else{
//      ShowMSG(1,(int)"bad net");
    LIB_Memcpy(RAM_LOCI_Ptr, &Block5402[0x00], LOCI_DATA_BYTE_LEN);  
    Set_LAI();
    RegNetwork(1, (unsigned char *)(RAM_LOCI_Ptr)+4, 0x207);
      GBS_StartTimerProc(&RAM_TIMER2, 216*4, &TryRigesterInfinity);
  }
}

*/

 void ChangeSIM(int SimNum){
  if(SimNum && !Block5401[SimNum].IMSI[0]) // if sim data not present (IMSI is null)
    return;
#ifdef NEWSGOLD
  UpdateSMSC(); //сохраняем СМСЦ
#endif   
  
  Clear_FPNMN();  // all networks is permited for reistration

  //Store current SIM data on their place in 5402 block (dynamic data)
  EEFullWriteBlock(5402, &Block5403, SIM_number * 0x50 + 0x00, 0x50,0,0);
  //Read new SIM dynamic data
  EEFullReadBlock(5402, &Block5403, SimNum * 0x50 + 0x00, 0x50,0,0);
  //Store new SIM dynamic data in working block (5403) 
  EEFullWriteBlock(5403, &Block5403, 0x00, 0x50,0,0);
  if(SimNum)
  {
    LIB_Memcpy(RAM_IMSI_Ptr, Block5401[SimNum].IMSI, IMSI_DATA_BYTE_LEN);
  }
  else
  {
    LIB_Memcpy(RAM_IMSI_Ptr, REAL_SIM_IMSI, IMSI_DATA_BYTE_LEN);
	
//warning !!! возможно тут и чуть далее чето лишне закоментил	
    //LIB_Memcpy(RAM_LOCI_Ptr, REAL_SIM_LOCI, LOCI_DATA_BYTE_LEN);
    //LIB_Memcpy(RAM_BCCH_Ptr, REAL_SIM_BCCH, BCCH_DATA_BYTE_LEN);
    //LIB_Memcpy(RAM_KC_Ptr,   REAL_SIM_KC,   KC_DATA_BYTE_LEN);
/*
    LIB_Memcpy(RAM_LOCI_Ptr, &Block5402[0x00], LOCI_DATA_BYTE_LEN);
    LIB_Memcpy(RAM_BCCH_Ptr, &Block5402[0x10], BCCH_DATA_BYTE_LEN);
    LIB_Memcpy(RAM_KC_Ptr, &Block5402[0x20], KC_DATA_BYTE_LEN);
*/
//    if (RAM_SPN_Ptr!=(void*)-1)    LIB_Memcpy(RAM_SPN_Ptr,  REAL_SIM_SPN,  SPN_DATA_BYTE_LEN);
//    if (RAM_F14_Ptr!=(void*)-1)    LIB_Memcpy(RAM_F14_Ptr,  REAL_SIM_F14,  SPN_DATA_BYTE_LEN);   
  }
   if (RAM_SPN_Ptr!=(void*)-1)  CopySPN(RAM_SPN_Ptr, Block5401[SimNum].SPN); // fixed old bug, thanx to  ManOfWar 
	else    if (RAM_F14_Ptr!=(void*)-1)  CopySPN(RAM_F14_Ptr, Block5401[SimNum].SPN);	
	
    LIB_Memcpy(RAM_LOCI_Ptr, Block5403.LOCI, LOCI_DATA_BYTE_LEN);
    LIB_Memcpy(RAM_BCCH_Ptr, Block5403.BCCH, BCCH_DATA_BYTE_LEN);
    LIB_Memcpy(RAM_KC_Ptr, Block5403.KC, KC_DATA_BYTE_LEN);

  SIM_number = SimNum;

//  LIB_Memset(&RAM_KCGPRS, 0xFF, 9);
//  LIB_Memset(&RAM_LOCIGPRS, 0xFF, 14);

  //save number
//  SetEEFULLBlock(5400, &SIM_number, 0x00, 1);
  //Block5402[0x51] = SIM_number;  
  Set_LAI();

  ChangeSMSC();
  SendReply(IPC_MSIM_SWITCHED,0);

  RegNetwork(1, (unsigned char *)(RAM_LOCI_Ptr)+4, 0x207);
  
  //send msg to elfs

//  GBS_DelTimer(&RAM_TIMER2);
//  GBS_StartTimerProc(&RAM_TIMER2, 216*10, &TryRigesterInfinity); //tipa 10secund hvatit na poteru seti

  if (Block5403.time2sw>0)
    GBS_StartTimerProc(&RAM_TIMER1, 13000*Block5403.time2sw, &ReturnToPhysicalSIM);
}





void MultisimINIT(void){
  if(((int)SIM_Data & 0xA8000000) != 0xA8000000)
  {
    SIM_Data = (KV_SIM_CTRL_BLOCK *) malloc(sizeof(KV_SIM_CTRL_BLOCK));
    LIB_Memset(SIM_Data, 0xFF, sizeof(KV_SIM_CTRL_BLOCK));

    EEFullReadBlock(5401, &Block5401, 0, BL_SZ_5401,0,0);
    EEFullReadBlock(5403, &Block5403, 0, BL_SZ_5403,0,0);

//    SIM_number = Block5400[0x00];
    SIM_number = Block5403.simnum;
   // SIM_number = 0;    
    SIM_State = CONST_Response_FALSE;
    GBS_StartTimerProc(&RAM_TIMER2, 216*1, &initMsg);    
  }
 
}

#ifndef NEWSGOLD

void SaveHTTPProfile(int profile){
    Block5403.inet_profile = profile;
    //maybe comment next line
    EEFullWriteBlock(5403, &Block5403.inet_profile, 0x40 + 0x0F, 1,0,0);
}

void SaveSMSProfile(char profile){
  char *curprof = (char *)Current_SMS_Profile_ADR;
  if (profile>5) return;
  *curprof = profile;
  Save_SMS_Profile(5138);
    Block5403.sms_profile = profile;
    //maybe comment next line
    EEFullWriteBlock(5403, &Block5403.sms_profile, 0x40 + 0x0E, 1,0,0);
}
#endif

extern "C" void ShowMenu (); 

inline __arm void smn(void){
  WSHDR *ws;
  ws=AllocWS(150);
#ifdef NEWSGOLD  

  #ifndef DISK0   
    str_2ws(ws,"4:\\zbin\\utilities\\multisim.elf\0",128);
  #else 
    str_2ws(ws,"0:\\zbin\\utilities\\multisim.elf\0",128);
  #endif  
#else   
  str_2ws(ws,"0:\\zbin\\utilities\\multisim.elf\0",128);
#endif
  ExecuteFile(ws,0,0);
  FreeWS(ws);
}

void ShowMenu (){
  smn(); //jump to arm  
}

