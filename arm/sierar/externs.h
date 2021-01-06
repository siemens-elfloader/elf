extern void Obs_Sound_SetLogSourceEx(HObj hobj, int src);
extern int Obs_Snd_SetPurpose (HObj hObj,int purpose);
extern int Obs_Sound_SetHandsFree (HObj hObj,char hf);
extern int Obs_Sound_Set3dAudio (HObj hObj, char aud);
extern int Obs_Sound_SetEqualizer(HObj hObj, int bass, int mid, int treble, int balance);
extern int Obs_Sound_SetPWM(HObj hObj, int fIsPWM);
extern int Obs_SetOutput_Uid(HObj hObj, int OutUID,int g);
extern int Obs_Sound_SetPlayModePartial(HObj hObj, int mode);
extern int Obs_Sound_SetMute(HObj hObj,HObj sObj, int mute);
extern int Obs_Sound_SetFading(HObj hObj, int fade, int fade_way, int ms, int delta);
extern int Obs_Sound_SetShockProtection(HObj hObj, int mode);
typedef struct{
  int bass;
  int treble;
  int vis;
} VIS_FMT;

extern int Obs_Sound_SetVisualisationsParams(HObj hobj, int eMode, int eLink, int DataId, VIS_FMT* cbFormat);

//Recording
extern int Obs_Sound_SetFIsRecording(HObj hobj, int fIsRecording);
extern int Obs_Sound_SetAMRDTX(HObj hobj, int dtx);
extern int Obs_Sound_SetNofChannels(HObj hobj, int num_channels,int g,int y);
extern int Obs_Sound_SetMaxFileSize(HObj hobj, int max_file_size);
extern int Obs_Sound_SetBitrate(HObj hobj, int bitRate);
extern int Obs_Sound_SetAMRMode(HObj hobj, int data_rate);
extern int Obs_Sound_SetAMRFormat(HObj hobj, int format);
extern int Obs_Sound_SetAMRFrmPrBuf(HObj hobj, int nof_frames);
extern int Obs_Sound_SetRecordingMode(HObj hobj, int RecordingMode);
extern int Obs_SetOutput_File (HObj hObj/*, int unk_zero*/, WSHDR *path);
extern int Obs_Sound_SetSampleRate(HObj hobj, int SampleRate);
extern int Obs_SetOutput_Push(HObj hobj, int hz);
extern int Obs_SetTime(HObj hobj, int msec);
extern int Obs_Vibr(HObj hobj,int Vibr);
extern int Obs_Get(HObj hobj,int rate);
extern char *Aa();
#pragma swi_number=0x80F5
__swi __arm unsigned int Ram_LCD_Overlay_Layer(void);

#pragma swi_number=0x7A
__swi __arm void UpdateDisplayByLayerPtr(unsigned int);

#pragma swi_number=0x80F6
__swi __arm unsigned int* Ram_Layer_Base_Ptr(void);

#pragma swi_number=0x79
__swi __arm void DrawObject2Layer(unsigned int lcd_ptr, DRWOBJ* drwobj);
extern int Cam(int format,int resolution,int cropping,int disp,int flash,int call);

