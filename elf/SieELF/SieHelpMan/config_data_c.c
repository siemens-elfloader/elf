#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

__root const CFG_HDR cfghdr0={CFG_COLOR,"������ɫ",0,0};
__root const char main_bg_color[4]={0,0,0,100};

__root const CFG_HDR cfghdr1={CFG_UINT,"�ı�����",0,65535};
__root const unsigned int main_font=FONT_SMALL;

__root const CFG_HDR cfghdr2={CFG_COLOR,"�ı���ɫ",0,0};
__root const char main_text_color[4]={255,255,255,100};

__root const CFG_HDR cfghdr3={CFG_UINT,"�������",0,65535};
__root const unsigned int sk_font=FONT_MEDIUM;

__root const CFG_HDR cfghdr4={CFG_COLOR,"�����ɫ",0,0};
__root const char sk_color[4]={255,255,255,100};

__root const CFG_HDR cfghdr5={CFG_UINT,"ˢ��ʱ��",0,600};
__root const unsigned int sys_re_t=5;

__root const CFG_HDR cfghdr6={CFG_STR_GB,"�����ִ�",0,255};
__root const char test_string[256]="�������� Test String 123";

__root const CFG_HDR cfghdr7={CFG_COLOR,"������ɫ",0,0};
__root const char t_a_b_color[4]={255,0,0,100};

__root const CFG_HDR cfghdr8={CFG_CBOX, "Ĭ����", 0, 2};
__root const int default_vibra_sta = 0;
__root const CFG_CBOX_ITEM cfgcbox0[2] = {"��", "��"};

__root const CFG_HDR cfghdr9 = {CFG_CBOX, "Ĭ������", 0, 4};
__root const int default_light_sta = 3;
__root const CFG_CBOX_ITEM cfgcbox1[4] = {"ȫ��","��Ļ","����","�Ӳ�"};

__root const CFG_HDR cfghdr10={CFG_CBOX, "Ĭ������", 0, 2};
__root const int default_sound_sta = 0;
__root const CFG_CBOX_ITEM cfgcbox2[2] = {"��", "��"};

__root const CFG_HDR cfghdr11={CFG_UINT,"���ͼƬ��",0,999999};
__root const unsigned int max_image_num=1700;

__root const CFG_HDR cfghdr12={CFG_UINT,"������԰���",0,999999};
__root const unsigned int max_lpg_num=8000;

__root const CFG_HDR cfghdr13={CFG_UINT,"���������",0,999999};
__root const unsigned int max_sound_num=150;
