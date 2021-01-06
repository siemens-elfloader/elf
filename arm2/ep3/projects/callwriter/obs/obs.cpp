#include <swilib.h>
#include "obs.h"



amr::amr(char *fname,int mode,int bitrate)
{
  WSHDR *ws=AllocWS(256);
  wsprintf(ws,"amr");
#ifndef NEWSGOLD
  object=Obs_CreateObject(0x30,GetExtUid_ws(ws),2,0,1,0,0);
  Obs_SetOutput_File(object,fname);
#else
  object=Obs_CreateObject(0x34,GetExtUid_ws(ws),2,0x70A3,0,0,0);
  str_2ws(ws,fname,255);
  Obs_SetOutput_File(object,ws);
#endif

  Obs_Sound_SetMaxFileSize(object,2000*1024);

  Obs_Sound_SetAMRMode(object,mode);

  #ifdef NEWSGOLD
  Obs_Sound_SetBitrate(object,bitrate);

  Obs_Sound_SetAMRFrmPrBuf(object,0xA0);

  Obs_Sound_SetFIsRecording(object,1);

  Obs_Sound_SetNofChannels(object,1);

  Obs_Sound_SetAMRFormat(object,0);

  Obs_Sound_SetAMRDTX(object,0);

  Obs_Mam_SetPurpose(object,0xB);

#ifndef ELKA
  Obs_Sound_SetPurpose(object,0xB);
#endif

#endif
  Obs_Sound_SetRecordingMode(object,0);
  FreeWS(ws);

  action=AMR_CREATED;

  Obs_Start(object);
  FILE *f=fopen("0:\\log.txt","rw");
  fwrite(fname,strlen(fname),1,f);
  fclose(f);
  action=AMR_WRITE;
}

amr::~amr()
{
    ShowMSG(1,(int)"stop");
  Obs_Stop(object);
  action=AMR_STOP;
  Obs_DestroyObject(object);
}


