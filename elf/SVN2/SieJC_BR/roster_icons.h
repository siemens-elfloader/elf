/*
    SieNatJabber Project
    ������� ��������� ������ �������
*/


// ������ �������� � ������� �� �������� �����������
void Roster_DrawIcon(unsigned short x, unsigned short y, unsigned int img_num);
// ������ "�������" � ����������� �������
int Roster_getIconWidth(char *path_to_pic);
int Roster_getIconHeight(char *path_to_pic);

// �������� ����� ��������
#ifdef USE_PNG_EXT
void Roster_getIcon(char* path_to_pic, CLIST* ClEx, TRESOURCE* resEx);
#else
int Roster_getIcon(CLIST* ClEx, TRESOURCE* resEx);
#endif
 //�������� �������� �� png
  void Roster_fillIcons();

//������ ����� �������� �� �������
#ifdef USE_PNG_EXT
char* Roster_getIconByStatus(char* path_to_pic, char status);
#else
  int Roster_getIconByStatus(char status);
#endif
