/*
    SieNatJabber Project

    ����������� ���� ��������
*/

#ifndef _BOOKMARKS_H_
  #define _BOOKMARKS_H_

#include "xml_parser.h"
// �������� ������ ��������
void Get_Bookmarks_List();

// ���������� ������ ��������
void KillBMList();

// Jabber Handler
void Process_Bookmarks_Storage(XMLNode* nodeEx);

// ���������� ���� ��������
void Disp_BM_Menu();


#endif
