HObj object=0;
#define AMR_NOT_CREATED 0
#define AMR_CREATED 1
#define AMR_WRITE 2
#define AMR_STOP 3
#define AMR_PAUSE 4
int action=AMR_NOT_CREATED;
int MSG_Report=0;
extern const int amrmode;
extern const int bitrate;
extern const int size;
extern const char folder[128];
int mode=0;
int bit=0;
char RecordName[256];
FSTATS fs;
#define AMR_OK 1
#define AMR_ERR -1
int LastErr=0;
int Obs_CreateAmrFile(char *fname);
int Obs_StopAmrWrite();
int Obs_DeleteObj();
int Obs_PauseAmrWrite();
int Obs_ResumeAmrWrite();
unsigned int Obs_GetRealSize();
int GetLastError();
int Obs_StartAmrWrite();
double Obs_Percente();
