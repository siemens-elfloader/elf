#include "C:\arm\inc\swilib.h"
#include "obs.h"

int Obs_CreateAmrFile(char *fname)
{
  int uid=0;
  if(folder[strlen(folder)-1]=='\\')strcpy(RecordName,folder);
  else snprintf(RecordName,255,"\\%s",folder);
  WSHDR *ws=AllocWS(256);
  wsprintf(ws,"amr");
  uid=GetExtUid_ws(ws);
  strcat(RecordName,fname);
  str_2ws(ws,RecordName,255);
  if(object!=NULL)object=NULL;
#ifndef NEWSGOLD
  object=Obs_CreateObject(0x30,uid,2,0,1,0,0);
  Obs_SetOutput_File(object,RecordName);  
#else
  object=Obs_CreateObject(0x34,uid,2,0x70A3,0,0,0);
  Obs_SetOutput_File(object,ws);  
#endif

  Obs_Sound_SetMaxFileSize(object,GetFreeRamAvail()-500);
  
   switch(amrmode)
  {
  case 1:Obs_Sound_SetAMRMode(object,NORMAL_MODE);break;
  case 2:Obs_Sound_SetAMRMode(object,HIGHT_MODE);break;
  default:Obs_Sound_SetAMRMode(object,LOW_MODE);break;
  }
  #ifdef NEWSGOLD
  switch(bitrate)
  {
  case 1:Obs_Sound_SetBitrate(object,NORMAL_BITRATE);break;
  case 2:Obs_Sound_SetBitrate(object,HIGHT_BITRATE);break;
  default:Obs_Sound_SetBitrate(object,LOW_BITRATE);break;
  }
    
  Obs_Sound_SetAMRFrmPrBuf(object,0xA0);
  
  Obs_Sound_SetFIsRecording(object,1);
  
  Obs_Sound_SetNofChannels(object,1);
  
  Obs_Sound_SetAMRFormat(object,NULL);
  
  Obs_Sound_SetAMRDTX(object,NULL);
  
  
 
#ifndef ELKA
  Obs_Sound_SetPurpose(object,0xB);
#else
  Obs_Mam_SetPurpose(object,0xB);
#endif
#endif
  Obs_Sound_SetRecordingMode(object,NULL);
  FreeWS(ws);
  action=AMR_CREATED;  
  return action;
}


int Obs_StopAmrWrite()
{
  Obs_Stop(object);
  action=AMR_STOP;
  Obs_DeleteObj();
  return action;
}



int Obs_StartAmrWrite()
{
  Obs_Start(object);
  action=AMR_WRITE;
  return action;
}

int Obs_DeleteObj()
{
  Obs_DestroyObject(object);
  action=AMR_NOT_CREATED;
  return action;
}
