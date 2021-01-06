#define IPC_MAPLYER "MusicAPlayer"
#define IPC_CONTROL_NAME "Control"
#define IPC_CHECK_DOUBLERUN 1
#define IPC_PREV 4
#define IPC_ENTER_BUTTON    5 //Play, Pause...
#define IPC_NEXT 6


#define IPC_VOL_INC 10
#define IPC_VOL_DEC 11
#define IPC_SET_STOP 12
#define IPC_GET_INFO 13

#define IPC_OUT_SEND_INFO 14
#define IPC_OUT_PLAYER_START 7
#define IPC_OUT_PLAYER_CLOSE 8
#define IPC_CLOSE_PLAYER 9 

typedef struct{
char trackName[128];
int trackPosTime;
int trackTime;
int playActive;
int pause;
int volume;
int mute;
}MUSIC_INFO; 
