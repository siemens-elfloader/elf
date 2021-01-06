#ifndef _LANGUAGE_H_
#define _LANGUAGE_H_
#include "..\multisim_ipc.h"

#define LG_COPYRIGHT     "MultisimElf v0.9b\n(C) by Shadows\nSinclair\n(R)Rst7\nKreN\n"
//��������� ������ ���� ������ ����� ����� ����
//#define LANG_RU
//#define LANG_UA
#define LANG_EN

#ifdef LANG_RU

//===============================

#define LG_MENU    "����"
#define LG_OPTIONS "�����"
#define LG_CLOSE   "�������"
#define LG_CLEAR   "<C"
#define LG_DOIT    "���������"
#define LG_PASTESM "��������"
//-------------
#define LG_SELECT  "�����"
#define	LG_TEXT    "�����"
#define LG_BACK    "�����"
//--------------
#define LG_ADD      "��������"
//--------------

//===============================


//================================
#define LG_MNUEDCFG   "���������"
#define LG_MNUPHYSIM  "���������� ���"
#define LG_MNUVIRTSIM "����������� ���"
#define LG_MNUABOUT   "�� �����"
#define LG_MNUCFG   "������� ������"
#define LG_MNUASNET   "��������� ����"
#define LG_MNUSAVEB   "��������� 5401 � ����"
#define LG_MNULOADB   "�������� 5401 �� �����"
#define LG_MNUOPENB   "������� ���� 5401 � TED"
#define LG_MNUSAVEB1   "��������� 5402 � ����"
#define LG_MNULOADB1   "�������� 5402 �� �����"
#define LG_MNUOPENB1   "������� ���� 5402 � TED"
#define LG_MNUFIX   "��������� ����� (physical SIM must select)"
//--------------
#define LG_CFG_PATH5400S   "���� ���  ����� 5401"
#define LG_CFG_PATH5401S   "���� ���  ����� 5402"
#define LG_CFG_SEC_FCLICK   "��������� ������������ 1-click"
#define LG_CFG_NSIMENABLE   "��������� ������� ������������"
#define LG_CFG_NMAINSIM   "����� �������� ���"
#define LG_CFG_NADITSIM   "����� ��������������� ���"
//--------------
#define LG_MSGERRBLOCK     "���� 5401/5402 �� ������ ���� ����� �������� ������!"
//=================================



//=================================


#endif

#ifdef LANG_UA


#endif

#ifdef LANG_EN

#define LG_MENU    "Menu"
#define LG_OPTIONS "Options"
#define LG_CLOSE   "Close"
#define LG_CLEAR   "<C"
#define LG_DOIT    "Doit"
#define LG_PASTESM "Paste"
//-------------
#define LG_SELECT  "Select"
#define	LG_TEXT    "Text"
#define LG_BACK    "Back"
//--------------
#define LG_ADD      "Add"
//--------------

//===============================


//================================
#define LG_MNUEDCFG   "Preferences"
#define LG_MNUPHYSIM  "Physic SIM"
#define LG_MNUVIRTSIM "Virtual SIM"
#define LG_MNUCFG   "Open Config"
#define LG_MNUASNET   "Auto Network"
#define LG_MNUSAVEB   "Save 5401 to file"
#define LG_MNULOADB   "Update 5401 from file"
#define LG_MNUOPENB   "Open File 5401 by TED"
#define LG_MNUSAVEB1   "Save 5402 to file"
#define LG_MNULOADB1   "Update 5402 from file"
#define LG_MNUOPENB1   "Open File 5402 by TED"
#define LG_MNUFIX   "Physic Block(physical SIM must select)"
//--------------
#define LG_CFG_PATH5400S   "Path 5401"
#define LG_CFG_PATH5401S   "Path 5402"
#define LG_CFG_SEC_FCLICK   "Setting switch 1-click"
#define LG_CFG_NSIMENABLE   "Enable rapid switch"
#define LG_CFG_NMAINSIM   "Number Main Sim"
#define LG_CFG_NADITSIM   "Number ADIT Sim"
//--------------
#define LG_MSGERRBLOCK     "Block 5401/5402 not found or in wrong format!"
//=================================

//================================
#define LG_MNUABOUT   "About"

//-------------

//================================
#endif

#endif

