#include "play.h"

void Create()
{
  //melody_addr=&melody_data;
  sound=Obs_CreateObject(0x36,0,0,0x70A3,1,0,0);
  Obs_SetInput_Memory(sound,0,(void*)0xA022213A,0x3c);
  Obs_Mam_SetPurpose(object,0x25);
  Obs_Sound_SetVolumeEx(sound,4,1);
}
void Start()
{
  Obs_Start(sound);
}
void Stop()
{

  Obs_Stop(sound);
  Obs_DestroyObject(sound);
    sound=0;
}
