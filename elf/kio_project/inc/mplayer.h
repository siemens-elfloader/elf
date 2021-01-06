// Функции управления медиаплеером
// (c) Kibab
// Версия 0.3
// (r) All S-C Community

/* Лог изменений 
0.3 - добавлены функции выключения плеера, выключения звука
0.2 - добавлена функция изменения громкости
0.1 - первая публичная версия
*/

#ifndef _MPLAYER_H_
  #define _MPLAYER_H_

// Команды плеера
#define PLAYER_FWD    0x02
#define PLAYER_RWD    0x01
#define PLAYER_PAUSE  0x10
#define PLAYER_PLAY   0x0E
#define PLAYER_TOGGLE 0x11
#define PLAYER_STOP   0x0F
#define PLAYER_VOL_UP 0x15
#define PLAYER_VOL_DN 0x16
#define PLAYER_KILL   0x0C
#define PLAYER_MUTE   0x0A

void Send_MPlayer_Command(unsigned short cmd, short substract);  // Отправить команду плееру
void MPlayer_Stop();   // Остановить игру
void MPlayer_Start();  // Запуск проигрывания
void MPlayer_Next();   // Переключиться на следующую песню
void MPlayer_Prev();   // Переключиться на предыдущую песню
void MPlayer_Toggle(); // Пауза/воспроизведение
void MPlayer_VolChange(short dir); // Громкость вверх/вниз (dir=1 / dir=-1)
void MPlayer_Shutdown(); // Завершить работу плеера
void MPlayer_Mute(); // Выключить звук. При повторном вызове звук включается

#endif