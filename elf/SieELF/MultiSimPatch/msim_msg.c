#include "..\inc\swilib.h"
#include "msim_msg.h"
#include "multisim_ipc.h"
#include "OsFunc.h"
#include "siemens.h"
#include "kvSIM_var.h"

extern KV_SIM_CTRL_BLOCK *SIM_Data;

#define MEM_onmsg		(SIM_Data->onmsg)
#define MEM_icsmd		(SIM_Data->icsmd)
#define SIM_number		        (SIM_Data->SIM_number)
#define SIM_Cnt (SIM_Data->simCnt)
#define Block5400		        (SIM_Data->Block5400)
#define Block5402		        (SIM_Data->Block5402)
#define MEM_gipc		(SIM_Data->gipc)
#define RAM_TIMER2                      (SIM_Data->RamTimer2)


__arm extern void GBS_SendMessageThumb(int cepid_to, int msg,int submess=0, void *data1=0, void *data2=0);
//warning
#pragma swi_number=0xBB
__swi __arm void *LIB_Memset(void *s, int c, int n);

#pragma swi_number=0x59
__swi __arm void *LIB_Memcpy(void *dest,const void *source,int cnt);

//-------------------------------------------
 int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{  
  int csm_result;
  csm_result = MEM_onmsg(data, msg); 
 // MSIM_IPC_MSG_EEPROM *eepmsg;  
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
/*    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"XTask config updated!");
      InitConfig();
    }
    */
  }
  //IPC 
  if (msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp(ipc->name_to,IPC_MSIM_NAME)==0)
      {
	switch (msg->submess)
	{
	case IPC_MSIM_SWITCH:
            ChangeSIM((int)(ipc->data));
   
	  break;
	case IPC_MSIM_EEPROM_AUTOSEARCH:
           RegNetwork(4,0,0x207);
	  break;
        /*
	case IPC_MSIM_EEPROM_BACKDOOR:
          eepmsg = (MSIM_IPC_MSG_EEPROM*) ipc->data;
          if (eepmsg->type&PRC_MSIM_WRITEBLOCK)
            EEFullWriteBlock(eepmsg->block,eepmsg->buf,eepmsg->offset,eepmsg->size,0,0);
          else
            EEFullReadBlock(eepmsg->block,eepmsg->buf,eepmsg->offset,eepmsg->size,0,0);
          SendReply(IPC_MSIM_PROCESSED+eepmsg->type,0);
          break;
	case IPC_MSIM_GET_RAM5400:
          MSIM_ELF_RESP *rbl;

          rbl=(MSIM_ELF_RESP *)ipc->data;
          LIB_Memset(rbl,0,sizeof(MSIM_ELF_RESP));
//          rbl->CurSim=SIM_number;
          rbl->CurSim=Block5402[0x2F];
          if (SIM_Cnt==-1){
            int i;
            for (i=0;i<20&&(Block5400[0x30*(i)+0x20+2]!=0);i++);
            SIM_Cnt=i;
          }
          for (int i=0;i<SIM_Cnt;i++){
            LIB_Memcpy(rbl->SimNames[i], &Block5400[0x30*(i)+0x20+1], 15);
            LIB_Memcpy(rbl->SimFlags[i], &Block5400[0x30*(i)+0x0A], 4);          
          }
            
          rbl->SimCnt=SIM_Cnt;
          SendReply(IPC_MSIM_PROCESSED,ipc->data);
          break;
          */
	}
      }
    }
  }
    return csm_result;  
};


 __arm void initMsg(void){
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  if (!icsm){ //если null то телефон не догрузился запускаем заново таймер
    GBS_StartTimerProc(&RAM_TIMER2, 216*1, &initMsg);    
    return;
  }
  LIB_Memcpy(&MEM_icsmd,icsm->constr,sizeof(CSM_DESC));
  MEM_onmsg=MEM_icsmd.onMessage;
  MEM_icsmd.onMessage=MyIDLECSM_onMessage;
  icsm->constr=&MEM_icsmd;
}

void SendReply(int submess, void *data){
  MEM_gipc.name_to="\0";//ipc_xtask_name;
  MEM_gipc.name_from=IPC_MSIM_NAME;
  MEM_gipc.data=0;
  GBS_SendMessageThumb(MMI_CEPID,MSG_IPC,submess,&MEM_gipc);
}
