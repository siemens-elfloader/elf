// Функци?управлен? медиаплеером
// (c) Kibab
// Верс? 0.4
// (r) All S-C Community

/* Ло?изменени?
0.4 - inline, добавлен комплект функци?//BoBa
0.3 - добавлен?функци?выключен? плеера, выключен? звук?0.2 - добавлен?функция изменения громкост?0.1 - перв? публичная верс?
*/

#ifndef _MPLAYER_H_
  #define _MPLAYER_H_

// Команд?плеера
#define PLAYER_PREV	0x01
#define PLAYER_NEXT	0x02
#define PLAYER_RESTART	0x03
//0x04 ?хз... часики рисует... БД??
//0x05 хрен?какая-то ?кнопками...
//0x06 ро?ет
//0x07 рестар?
//0x08 рестар?
//0x09 рестар?
#define PLAYER_MUTE	0x0A
//0x0b kill?
#define PLAYER_KILL	0x0C
//0x0d
#define PLAYER_PLAY	0x0E
#define PLAYER_STOP	0x0F
#define PLAYER_PAUSE	0x10
#define PLAYER_TOGGLE	0x11
#define PLAYER_FWD	0x12
#define PLAYER_RWN	0x13
#define PLAYER_NRM	0x14
#define PLAYER_VOL_UP	0x15
#define PLAYER_VOL_DN	0x16
//0x17 mute?
#define PLAYER_REPEAT1	0x18
//0x19 error?
//0x20
//0x21 ро?ет

inline void Send_MPlayer_Command(unsigned short cmd, short substract){		// Отправит?команд?плееру
	GBS_SendMessage(0x4209, 0x8053, 0, *((unsigned int*)RamMPlayer_CtrlCode())-substract,cmd);
}

inline void MPlayer_VolChange(short dir){					// Громкост?ввер?вниз (dir=1 / dir=-1)
	int cmd;
	if(dir==1){
    		cmd = PLAYER_VOL_UP;
  	}else{
    		cmd = PLAYER_VOL_DN;
  	}
	Send_MPlayer_Command(cmd,2);
	Send_MPlayer_Command(cmd,0);
}

inline void MPlayer_Stop()	{Send_MPlayer_Command(PLAYER_STOP,0);}	// Остановить игру
inline void MPlayer_Start()	{Send_MPlayer_Command(PLAYER_PLAY,0);}	// Запуск проигрыван?
inline void MPlayer_Next()	{Send_MPlayer_Command(PLAYER_NEXT,0);}	// Переключиться на следующу?песн?
inline void MPlayer_Prev()	{Send_MPlayer_Command(PLAYER_PREV,0);}	// Переключиться на предыдущую песн?
inline void MPlayer_Toggle()	{Send_MPlayer_Command(PLAYER_TOGGLE,0);}// Пауз?воспроизведени?
inline void MPlayer_Shutdown()	{Send_MPlayer_Command(PLAYER_KILL,0);}	// Завершит?работу плеера
inline void MPlayer_Mute()	{Send_MPlayer_Command(PLAYER_MUTE,0);}	// Выключит?звук. Пр?повторно?вызове звук включает?
inline void MPlayer_Pause()	{Send_MPlayer_Command(PLAYER_PAUSE,0);}	// Пауз?

#endif
