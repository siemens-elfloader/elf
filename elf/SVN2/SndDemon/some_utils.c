#ifdef NEWSGOLD
#include "../inc/swilib.h"
#include "swilib2.h"
#include "some_utils.h"
//  int  GetValFromCache(char *filename,char *name){

int  GetValFromCache(void){
    char res[3];
//   pdcache_getval(char* ret, int maxlen_of_return_str, char cachetype, char *pd_entry_identifier_class, char  *pd_entry_identifier_sub);
   pdcache_getval(res, 0x2,4, NULL, "AUDIO_SYSTEMVOLUME");
   return res[0]-'0';
};

/*
MediaProc_IsBackgroundFree

//arm
//pattern_ELKA= 08 00 90 E5 01 00 70 E2 00 00 A0 33 08 80 BD E8 -24
//thumb
//pattern_NEWSGOLD= ????01208968002900D0+1

 MEDIA_PLAYER_TOGGLE
 MEDIA_PLAYLAST-8
*/

//some cheats but doesn`t work ??
#pragma swi_number=0x81FF
__swi __arm int* MEDIA_PLAYLASTadr();

typedef void ( local)(void);
void MEDIA_PLAYER(void){
  local *m;
m=(local*)((char*)MEDIA_PLAYLASTadr()-0x8);
              if (IsUnlocked())
m();
}

#endif
