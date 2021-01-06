HObj object=0;
#define AMR_NOT_CREATED 0
#define AMR_CREATED 1
#define AMR_WRITE 2
#define AMR_STOP 3
int action=AMR_NOT_CREATED;

extern const int amrmode;
extern const int bitrate;
extern const char folder[128];
char RecordName[256];
int Obs_CreateAmrFile(char *fname);
int Obs_StopAmrWrite();
int Obs_DeleteObj();
int Obs_StartAmrWrite();
