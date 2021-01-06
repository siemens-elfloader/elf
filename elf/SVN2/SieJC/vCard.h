/*
    SieNatJabber Project
    ������� ������ � vCard

    ������ � ���������� ����� vCard, ���������� �����
*/

#ifndef _VCARD_H_
  #define _VCARD_H_

#include "xml_parser.h"

// �������� ������ vCard
VCARD Create_vCard();

// ������������ ������ ��-��� vCard
void Free_vCard(VCARD vcard);

// �������� ���� �� vCard
char *Get_VCard_Value(VCARD src, char *par_name);

// ���������� ���� vCard
void Process_vCard(char *from, XMLNode *vCard);

// �������� ����� �� ������
void vCard_Photo_Display(char *path);

// �������� vCard ��� �������� �� JID. ���� ������� �� ����� vCard, ���������� 0, ����� 1.
int Show_vCard(char *jid);

#endif

