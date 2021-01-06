#pragma swi_number=126
__swi __arm int rand(void);

#pragma swi_number=0x8248
__swi __arm char *RamFormatTrack();

#pragma swi_number=0x8249
__swi __arm char *RamFreq();

#pragma swi_number=0x824A
__swi __arm char *RamChannel();

#pragma swi_number=0x45 
#ifdef NEWSGOLD 
__swi __arm int GetWavLen(char *filename); 
#else 
__swi __arm int GetWavLen(TWavLen *wl);
#endif
