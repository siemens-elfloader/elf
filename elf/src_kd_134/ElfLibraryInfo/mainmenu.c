#include "C:/arm/inc/swilib.h"
#include "elfsubmainmenu.h"
#include "groopmainmenu.h"
#include "mainmenu.h"
#include "main.h"

#pragma inline
void patch_header(HEADER_DESC* head)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}
#pragma inline
void patch_input(INPUTDIA_DESC* inp)
{
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}

#ifdef ELKA
int main_icon[]={0x4DD,0}; //�������� ��������
int menu_icon[]={0x027,0}; //����� ��������
int set_icon[]={0x120,0}; //��������� ��������
int inet_icon[]={0x145,0}; //�������� ��������
int about_icon[]={0x156,0}; //�� ����� ��������
int exit_icon[]={0x195,0}; //����� ��������
#else
#ifdef NEWSGOLD
int main_icon[]={0x2B8,0}; //�������� ��������
int menu_icon[]={0x041,0}; //����� ��������
int set_icon[]={0x148,0}; //��������� ��������
int inet_icon[]={0x16C,0}; //�������� ��������
int about_icon[]={0x17D,0}; //�� ����� ��������
int exit_icon[]={0x1C3,0}; //����� ��������
#else
int main_icon[]={0xFA0,0}; //�������� ��������
int menu_icon[]={0xFA0,0}; //����� ��������
int set_icon[]={0xFA0,0}; //��������� ��������
int inet_icon[]={0xFA0,0}; //�������� ��������
int about_icon[]={0xFA0,0}; //�� ����� ��������
int exit_icon[]={0xFA0,0}; //����� ��������
#endif
#endif

HEADER_DESC menuhdr={0,0,131,21,main_icon,(int)"ElfLibraryInfo:",0x7FFFFFFF};
int menusoftkeys[]={0,1,2};
int Terminate = 0;
#define N_ITEMS 5
int MainMenu_ID;

//�����-------------------------------------------------------------------------

void  GetSubMenu(GUI *data)
{
  GetGroopMenu();
};

//����������--------------------------------------------------------------------

void InetBase(GUI *data)
{
//do_start_connection();
  GetInetInfo();
}

//���������---------------------------------------------------------------------

void OpenSettings(GUI *data)
{
  extern const char *successed_config_filename;
  WSHDR *ws;
  ws=AllocWS(150);
  str_2ws(ws,successed_config_filename,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
}

//�� �����----------------------------------------------------------------------

void AboutDlg(GUI *data)
{
  ELIAbout();
};

//�����-------------------------------------------------------------------------

void Exit(GUI *data)  // �������� �������� (����� �� ����)
{
  Terminate =1 ;
  GeneralFuncF1(1);
}

void mmenu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

MENUITEM_DESC menuitems[N_ITEMS]=
{
{menu_icon,(int)"�����",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{inet_icon,(int)"��������",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{set_icon,(int)"���������",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{about_icon,(int)"�� �����...",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{exit_icon,(int)"�����",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};

MENUPROCS_DESC menuprocs[N_ITEMS]={GetSubMenu,InetBase,OpenSettings,AboutDlg,Exit};

static const SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"�����"},
  {0x0001,0x0000,(int)"�����"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
  (SOFTKEY_DESC *)menu_sk,0
};

MENU_DESC tmenu=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_skt,
  1,
  NULL,
  menuitems,
  menuprocs,
  N_ITEMS
};

int StartMenu(void)
{
  CreateMenu(0,0,&tmenu,&menuhdr,0,N_ITEMS,0,0);
  return(0);
}
