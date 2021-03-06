typedef struct{
  char mpg_ver[12];
  char layer[12];
  char bitrate[12];
  char chanl[16];
  char freq[16];
}FILEPRP;

#ifdef NEWSGOLD
#ifdef ELKA
#define FONT_SMALL_BOLD 9
#else
#define FONT_SMALL_BOLD 5
#endif
#endif

//#pragma swi_number=0x26E
//__swi __arm int Obs_Sound_SetVbr(HObj hObj, int Vbr);
//arm
//pattern_NSG=??,??,??,E9,??,??,??,E1,??,??,??,E3,??,??,??,E5,??,??,??,E1,??,??,??,E1,??,??,??,EB,??,??,??,E3,??,??,??,03,??,??,??,0A,??,??,??,E1,??,??,??,E1,??,??,??,E1,??,??,??,E5,??,??,??,EB,??,??,??,E8,??,??,??,E9,??,??,??,E1,??,??,??,E3,??,??,??,EB,??,??,??,E1,??,??,??,03,??,??,??,0A,??,??,??,E1,??,??,??,EB,??,??,??,E3,??,??,??,13,??,??,??,13,??,??,??,13,??,??,??,0A
//pattern_ELKA=??,??,??,E9,??,??,??,E1,??,??,??,E5,??,??,??,E2,??,??,??,E1,??,??,??,E1,??,??,??,E1,??,??,??,E5,??,??,??,E8,??,??,??,E5,??,??,??,E3,??,??,??,E5,??,??,??,E5,??,??,??,E3,??,??,??,FB,??,??,??,E3,??,??,??,E1,??,??,??,EB,??,??,??,E3

#pragma swi_number=0x26E
__swi __arm int Obs_Sound_SetEqulizer(HObj hObj, char bass, char mid, char treble, char balance); 

#pragma swi_number=0x270
__swi __arm int Obs_Sound_SetHandsFree(HObj hObj, int aud);

#pragma swi_number=0x81FA
__swi __arm char *RamVolumeStep();

#pragma swi_number=0x27 
__swi __arm void AddIconToIconBar(int pic, short *num);

#pragma swi_number=0x2DB
__swi __arm void MediaSendCSM_Open(WSHDR *file, WSHDR *path);

//A0CC5A8C Obs_GetMixing, hobj1=%p, hObj2=%p. returnValue=%d

//A0CC5B8C Obs_GetBufferSize, hobj=%p, rate=%d, returnValue=%d
/*int obParam (HObj hobj,int pl, int error){
ShowMSG(1,(int)"Param";
if(rew_flag==1) {Obs_Resume(hobj); rew_flag=0;}
return 0;
};
*/
