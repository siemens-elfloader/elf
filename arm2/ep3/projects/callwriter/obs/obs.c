#include <swilib.h>
#include "obs.h"







amr::amr(char *fname,int mode,int bitrate)
{
  WSHDR *ws=AllocWS(256);
  wsprintf(ws,"amr");
#ifndef NEWSGOLD
  object=Obs_CreateObject(0x30,GetExtUid_ws(ws),2,0,1,0,0);
  str_2ws(ws,fname,255);
  Obs_SetOutput_File(object,RecordName);
#else
  object=Obs_CreateObject(0x34,GetExtUid_ws(ws),2,0x70A3,0,0,0);
  str_2ws(ws,fname,255);
  Obs_SetOutput_File(object,ws);
#endif

  Obs_Sound_SetMaxFileSize(object,GetFreeRamAvail()-500);

  Obs_Sound_SetAMRMode(object,amrmode);break;

  #ifdef NEWSGOLD
  Obs_Sound_SetBitrate(object,bitrate);break;

  Obs_Sound_SetAMRFrmPrBuf(object,0xA0);

  Obs_Sound_SetFIsRecording(object,1);

  Obs_Sound_SetNofChannels(object,1);

  Obs_Sound_SetAMRFormat(object,NULL);

  Obs_Sound_SetAMRDTX(object,NULL);

  Obs_Mam_SetPurpose(object,0xB);

#ifndef ELKA
  Obs_Sound_SetPurpose(object,0xB);
#endif

#endif
  Obs_Sound_SetRecordingMode(object,NULL);
  FreeWS(ws);

  action=AMR_CREATED;
}
~amr()
{
  Obs_Stop(object);
  action=AMR_STOP;
  Obs_DestroyObject(object);
  action=AMR_NOT_CREATED;
}

void amr::start()
{
  Obs_Start(object);
  action=AMR_WRITE;
}

