#include "C:\arm\inc\swilib.h"
#include "obs.h"





int Obs_CreateAmrFile(char *fname)
{
  int uid=0;
  
  strcpy(RecordName,folder);
  WSHDR *ws=AllocWS(256);
  wsprintf(ws,"amr");
  uid=GetExtUid_ws(ws);
  strcat(RecordName,fname);
  if(object!=NULL)object=0;
  object=Obs_CreateObject(0x34,uid,2,MSG_Report,1,0,0);
  str_2ws(ws,RecordName,255);
  Obs_SetOutput_File(object,ws);
  Obs_Sound_SetMaxFileSize(object,size*1024);
   switch(amrmode)
  {
  case 0:Obs_Sound_SetAMRMode(object,LOW_MODE);mode=LOW_MODE;break;
  case 1:Obs_Sound_SetAMRMode(object,NORMAL_MODE);mode=NORMAL_MODE;break;
  case 2:Obs_Sound_SetAMRMode(object,HIGHT_MODE);mode=HIGHT_MODE;break;
  }
  
  switch(bitrate)
  {
  case 0:Obs_Sound_SetBitrate(object,LOW_BITRATE);bit=LOW_BITRATE;break;
  case 1:Obs_Sound_SetBitrate(object,NORMAL_BITRATE);bit=NORMAL_BITRATE;break;
  case 2:Obs_Sound_SetBitrate(object,HIGHT_BITRATE);bit=HIGHT_BITRATE;break;
  }
  
  Obs_Sound_SetRecordingMode(object,NULL);
  
  Obs_Sound_SetFIsRecording(object,1);
  
  Obs_Sound_SetNofChannels(object,1);
  
  Obs_Sound_SetAMRFormat(object,NULL);
  
  Obs_Sound_SetAMRDTX(object,NULL);
  
  Obs_Sound_SetAMRFrmPrBuf(object,0xA0);
  
  Obs_SetOutput_Uid(object,uid);
  
  Obs_Mam_SetPurpose(object,0xB);

  FreeWS(ws);
  action=AMR_CREATED;
  return AMR_OK;
}

int Obs_StopAmrWrite()
{
  Obs_Stop(object);
  action=AMR_STOP;
  Obs_DeleteObj();
  return AMR_OK;
}

int Obs_StartAmrWrite()
{
  Obs_Start(object);
  action=AMR_WRITE;
  return AMR_OK;
}

int Obs_DeleteObj()
{
  Obs_DestroyObject(object);
  action=AMR_NOT_CREATED;
  return AMR_OK;
}

int Obs_PauseAmrWrite()
{
  Obs_Pause(object);
  action=AMR_PAUSE;
  return AMR_OK;
}

int Obs_ResumeAmrWrite()
{
  Obs_Resume(object);
  action=AMR_WRITE;
  return AMR_OK;
}

unsigned int Obs_GetRealSize()
{
  GetFileStats(RecordName,&fs,0);
  return fs.size;
}

int GetLastError()
{
  return LastErr;
}

double Obs_Percente()
{
  return (double)Obs_GetRealSize()/((double)size*(double)1024);
}
