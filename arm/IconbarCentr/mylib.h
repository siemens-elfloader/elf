#pragma swi_number=0x81FA
__swi __arm char *RamVolumeStep();

#pragma swi_number=0x81FB
__swi __arm char *RamMediaIsPlaying();

#pragma swi_number=0x81FA
__swi __arm char *RamLighterPower();

#pragma swi_number=0x8257
__swi __arm char *RamIsSendReceiveBT();

#pragma swi_number=0x8281
__swi __arm char *RamIsRunJava();

#pragma swi_number=0x8282
__swi __arm char *RamIsRunCamera();

#pragma swi_number=0x284
__swi __arm int IsGPRS();

#ifdef ELKA
#pragma swi_number=0x285
__swi __arm int IsEDGE();
#else
#pragma swi_number=0x8285
__swi __arm char *RamIsEDGE();
#endif

#pragma swi_number=0x286
__swi __arm int GetSMSState();

#pragma swi_number=0x287
__swi __arm int BT_GetLocVisibility();

#pragma swi_number=0x288
__swi __arm int GetCurrAudioPath();

#pragma swi_number=0x289
__swi __arm int isDecryption();

#pragma swi_number=0x828A
__swi __arm char *RamIsFileCache();

#pragma swi_number=0x828F
__swi __arm char *RamIsNumberTyping();

#pragma swi_number=0x8290
__swi __arm char *RamCallState();

