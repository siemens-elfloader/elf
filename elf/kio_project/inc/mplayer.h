// ������� ���������� ������������
// (c) Kibab
// ������ 0.3
// (r) All S-C Community

/* ��� ��������� 
0.3 - ��������� ������� ���������� ������, ���������� �����
0.2 - ��������� ������� ��������� ���������
0.1 - ������ ��������� ������
*/

#ifndef _MPLAYER_H_
  #define _MPLAYER_H_

// ������� ������
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

void Send_MPlayer_Command(unsigned short cmd, short substract);  // ��������� ������� ������
void MPlayer_Stop();   // ���������� ����
void MPlayer_Start();  // ������ ������������
void MPlayer_Next();   // ������������� �� ��������� �����
void MPlayer_Prev();   // ������������� �� ���������� �����
void MPlayer_Toggle(); // �����/���������������
void MPlayer_VolChange(short dir); // ��������� �����/���� (dir=1 / dir=-1)
void MPlayer_Shutdown(); // ��������� ������ ������
void MPlayer_Mute(); // ��������� ����. ��� ��������� ������ ���� ����������

#endif