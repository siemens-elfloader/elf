/*
* Ping-Pong 2009 - 2010
* main
* (c) Danil_e71
*/

//��������� + ����
#include "C:\arm\inc\swilib.h"
#ifdef ELKA//����
#define max_width 240
#define max_height 320
#define FONT 9//9 �����
#define timer_speed 5//�������� �����������
#define nimg 1//��� ���������� ��������� ��� ��� ���������
#else
#ifdef SG//�����
#define max_width 132
#define max_height 176
#define FONT 2//2 �����
#define timer_speed 7
#define nimg 0.5
#else//���
#define max_width 132
#define max_height 176
#define FONT 5//5 �����
#define timer_speed 12
#define nimg 0.5
#endif
#endif
#define NUM_RECORD 5//�� ����� ����� ������ �������
#define TMR_SECOND 216//������� ����
#define LGP_MENU_LANG1                 "�������� ����"//����� ������ ���� �����
#define LGP_MENU_LANG2                 "Select language"
#define LGP_LANG_RU                    "�������"
#define LGP_LANG_EN                    "English"
#define LEFT_SIDE  1//USER.DX
#define RIGHT_SIDE 2//USER.DX
#define STOP_SIDE  0//USER.DX



IMGHDR *pics[6];//����� ��������

int clear=0;//��� ���������� ������

const int rndtable[64]={//������� �������
 0,  1,  6, -3,  7, -2,  5, -1,  3,  4,  2, -7, -5,  0,  4,  1,
 3, -4,  4,  6, -1,  2,  7, -3, -7, -5, -3,  0,  3,  0,  2,  4,
-7,  1,  5,  3,  0,  2, -5, -2,  5,  7, -1,  2, -5,  3,  1,  4,
-3, -7,  2,  6,  0, -2,  1,  3,  5, -4, -1,  2,  0, -3,  4, -6
};
int rndindex=0;//������ �������
volatile int running=0; // ���� ����������
typedef struct//���������� ������ , ���� � ���
{
  int x,
      y,
      height,
      width,
      speed,
      lifetime,
      round,
      dx,
      dy;
}Mytype;
Mytype user;
Mytype cpu;
Mytype ball;

struct{int mymsec,hour,min,sec;char *str;}Time;//�����

enum {load,menu,settings,settings_igra,music,game,rec}status; //��������� ��� ����

int 
cur_x=nimg*30,//x ��������
cur_y=nimg*52,//y ��������
main_y=nimg*60,//^
difficult=0,//������ ���������
lives=7,//�����(� ����� ��� data.sys????)
mode=0,//���� ��� �����
speed_game=0,//�������� ����
gdy,//�� ����� ��� �������))))))���. ������� ������ ����� ����
def_vol=0,//���������
on_off_sound=0,//���� ������ ��� ����
PLAY_ID=0xFFF,//������)))��� Half65
saveload=1,//���������� ��� ��������
img_count,//��� ��������
game_new_cont=1,//����� ��� ����������
langenru=0,//����� ����??
vibra,//��� ��������� �����
exiting=0,//��� ������
error_count=0,//���������� ������(����������� ��������)
AI_line=0,//�����, ����� ������� �������� ������ cpu
isload=0,//���� 1 - ���� ��������
color_frame[8]={23,23,23,23,23,23,23,23};//8 �������(��� ��������)
extern const char folder[128];//���� � �����
extern const char name[15];//��� ������
const char bgcol_lang_cur[4]={1,1,1,100};//���������� ������� � ������ �����
const char linecol2[4] = {100,0,0,100};//���� ������� �����
const char bgcol[4]={50,50,50,255};//��������� ��� ��������
const char perc_t[]="%t";
const char per_s[]="%s%s";

char *folders;//��� �����
char *lang[60];//��� �������
char *images[6];//5 ��������(��� �����)
GBSTMR tmr,vibr;//������ �����������+�������, �����
extern void UpdateCSMname();
extern void RedrawScreen();
extern void lgpInitLangPack();//���������� ����
extern void T_Load_IMG();//�������� �������
extern void load_lang();//�������� ������� �2

int idle=1;

const int minus11=-11;
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;
typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  WSHDR *ws5;
  int i1;
}MAIN_GUI;
