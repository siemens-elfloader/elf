#include "..\inc\swilib.h"
#include "swilib2.h"
#include "snd_buffers.h"
#include "conf_loader.h"
  extern const unsigned int allowbuf;
  extern const unsigned int audcfg;
  extern const unsigned int buff_nof;
  extern const unsigned int buff_size;
  extern   word  oldAudValue;
  void SetupBuffers(word val);
  int autosearch(void);
  extern const char playerfolder[128];
   word  oldAudValue=0;
  void SetupBuffers(word val){
    word * buf=(word*)audcfg;
    if  (*buf==val)return;
    oldAudValue=*buf;
    buf[0]=val;
  }
  //---------------------------------------------------
   int autosearch(void){
    byte * bufst=(byte*)0xA0CB0000;
    byte * bufend=(byte*)0xA0CF0000;  
    byte fl=0;
    for (;!fl&&(bufst<bufend);bufst+=4) 
      if(memcmp(bufst,(void*)"Audio Buf",8)==0)fl=1;
    if (fl){
      unsigned int *mem=(unsigned int*)((int)&audcfg);
      *mem=*((dword*)(bufst-24+12));
      SaveConfig();
    }else{
      unsigned int *mem=(unsigned int*)((int)&allowbuf);
      *mem=0;

      SaveConfig();
    }
    return fl;
  }
  //-------------------------------------------------------------------
