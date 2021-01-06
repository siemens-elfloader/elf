//(�)Dimadze
//sudoku.h - ���������� ������� �-��, ��������, ��������, ���������� ��� ���� SuDoKu 2.0

typedef struct {    // ����� SuDoKu � ������������� ����
  char name[32];    // ��� ����� 
  char level;       // ������� ���������, 'L' - �����, 'M' - �������, 'H' - ������, '?' - �� ������� (��� '?' ����� ���� ����� ������)
  char x, y;        // ��������� �������, �.�. ��� ���������� 
  char gcell[9][9]; // ����� ������� ����� (���������� � �������� �������, �.�. � ����)
  char rcell[9][9]; // ����� ���������� ����� (�� ��� ����������� �������)
  char preview;     // ���-�� "��������������"
  char warn;        // 0x00 - ��� ��������������, 0x01 - ������� ��������� ����������, 0x02 - ��� ����� ����������, 0x03 - ������� ��������� ����������, ��� ����� ����������
  char error;       // 0x00 - ��� ������, 0x01 - ������ �������� �����, 0x02 - ������ ID �����, 0x03 - ����������� ������ �����, 0x04 - ������ ��������� �����/����������� ����� 
  int  sec;         // ����� ���� ��� ������ ����� � ��������
}SUDOKUMAP;

// SUDOKUMAP->gcell[][]:
// 0x01-0x09 - ������� ������, ������������� ������ ������� (Default)
// 0x11-0x19 - �������� ������, �������� �����, ��� ������������� ������� ������� (Default)
// 0x21-0x29 - �������� ������, �������� ������, ��� �������� ������, ��� ������������� ����� ������� (Default)
// 0x31-0x39 - �������� ������, �������� �����, ������ ��� �������, ��� ��������� ���������� (�� �� ������ ������������), ��� ������������� ������� ������� (Default) (���������� prold'�� �� team-sc.ru)
// ��������� ����� � ������� - �������� ������, ��� �� ����������� � ��������� SUDOKUMAP ��������� ������ 0x04

typedef struct {          // C�������� ��������
  char recs;              // ���-�� ����������
  char timedate[3][16+1]; // ����� � ���� 3 �������� (14:16 17.01.2010)
  char level[3];          // ������ ��������� 3 ��������
  int  sec[3];            // ������� ����������� ��������� 5 ��� �� ������� ����������
  int  points[3];         // ������� ���� 3 ��������� ���
  char error;             // 0x00 - ��� ������, 0x01 - ������ �������� �����, 0x02 - �������� ������ �����, 0x03 - ������ ID ����� 
}SUDOKUREC;

typedef struct {        // C�������� ������ �������
  char png_file;        // ����������� png - �����. �������� �� ���-��
  char hlp_file;        // ����������� hlp - ����
  char sedit_file;      // ����������� ���� �������� 
  char ext_file;        // ������ ������� ����� ���� SuDoKu, 0x64 - ���� � �� ����������!
}ERRORSTRUCT;


char CheckSUDOKUMAP(SUDOKUMAP *sdm) //�������� ������������ ����������� ����� SuDoKu, 0x04 - ������, 0 - �� �����!))
{ 
 int t=0;
 for (char i=1;i<10;i++) for (int k=0;k<9;k++) //�������� �� ����� (�����������); ���������, ��� �� ���������� ����.
  {
   int a=0;
   for (int j=0;j<9;j++) if (sdm->rcell[k][j]==i) a++;
   if  (a>1) {t=1; goto ERROR;} // ������! ������� ���������� 0x04
  }
 
 for (char i=1;i<10;i++) for (int k=0;k<9;k++) //�������� �� �������� (���������); ���������, ��� �� ���������� ����.
  {
   int a=0;
   for (int j=0;j<9;j++) if (sdm->rcell[j][k]==i) a++;
   if  (a>1) {t=1; goto ERROR;} // ������! ������� ���������� 0x04
  }

 // #1#2#3
 // #4#5#6 - �������� �� ��������� ��������
 // #7#8#9

//--------
 for (char i=1;i<10;i++) //�������� � #1 ��������� ��������; ���������, ��� �� ���������� ����.
  {
    int a=0;
    for (int k=0;k<3;k++) for (int j=0;j<3;j++) if (sdm->rcell[k][j]==i) a++;
    if  (a>1) {t=1; goto ERROR;} // ������! ������� ���������� 0x04
  }
 
 for (char i=1;i<10;i++) //�������� � #2 ��������� ��������; ���������, ��� �� ���������� ����.
  {
    int a=0;
    for (int k=0;k<3;k++) for (int j=3;j<6;j++) if (sdm->rcell[k][j]==i) a++;
    if  (a>1) {t=1; goto ERROR;} // ������! ������� ���������� 0x04
  }
 
 for (char i=1;i<10;i++) //�������� � #3 ��������� ��������; ���������, ��� �� ���������� ����.
  {
    int a=0;
    for (int k=0;k<3;k++) for (int j=6;j<9;j++) if (sdm->rcell[k][j]==i) a++;
    if  (a>1) {t=1; goto ERROR;} // ������! ������� ���������� 0x04
  }
//--------
 for (char i=1;i<10;i++) //�������� � #4 ��������� ��������; ���������, ��� �� ���������� ����.
  {
    int a=0;
    for (int k=3;k<6;k++) for (int j=0;j<3;j++) if (sdm->rcell[k][j]==i) a++;
    if  (a>1) {t=1; goto ERROR;} // ������! ������� ���������� 0x04
  }
 
 for (char i=1;i<10;i++) //�������� � #5 ��������� ��������; ���������, ��� �� ���������� ����.
  {
    int a=0;
    for (int k=3;k<6;k++) for (int j=3;j<6;j++) if (sdm->rcell[k][j]==i) a++;
    if  (a>1) {t=1; goto ERROR;} // ������! ������� ���������� 0x04
  }
 
 for (char i=1;i<10;i++) //�������� � #6 ��������� ��������; ���������, ��� �� ���������� ����.
  {
    int a=0;
    for (int k=3;k<6;k++) for (int j=6;j<9;j++) if (sdm->rcell[k][j]==i) a++;
    if  (a>1) {t=1; goto ERROR;} // ������! ������� ���������� 0x04
  }
//--------
 for (char i=1;i<10;i++) //�������� � #7 ��������� ��������; ���������, ��� �� ���������� ����.
  {
    int a=0;
    for (int k=6;k<9;k++) for (int j=0;j<3;j++) if (sdm->rcell[k][j]==i) a++;
    if  (a>1) {t=1; goto ERROR;} // ������! ������� ���������� 0x04
  }
 
 for (char i=1;i<10;i++) //�������� � #8 ��������� ��������; ���������, ��� �� ���������� ����.
  {
    int a=0;
    for (int k=6;k<9;k++) for (int j=3;j<6;j++) if (sdm->rcell[k][j]==i) a++;
    if  (a>1) {t=1; goto ERROR;} // ������! ������� ���������� 0x04
  }
 
 for (char i=1;i<10;i++) //�������� � #9 ��������� ��������; ���������, ��� �� ���������� ����.
  {
    int a=0;
    for (int k=6;k<9;k++) for (int j=6;j<9;j++) if (sdm->rcell[k][j]==i) a++;
    if  (a>1) {t=1; goto ERROR;} // ������! ������� ���������� 0x04
  }
//-------- 
 
ERROR: //���� ����� ������, �� ���������� ���� ��������� ���� ...
  
 if (t==1) return 0x04; else return 0;
}


SUDOKUMAP *ClearSUDOKUMAP(SUDOKUMAP *sdm)
{
 sdm->name[0] = 0;
 sdm->level = '?';
 sdm->x = 4; sdm->y = 4;
 for (int i=0;i<9;i++) for (int j=0;j<9;j++) sdm->gcell[i][j] = 0;
 for (int i=0;i<9;i++) for (int j=0;j<9;j++) sdm->rcell[i][j] = 0; 
 sdm->preview = 0;
 sdm->warn    = 0;
 sdm->error   = 0;
 sdm->sec     = 0;
 return sdm;
}

void MemFreeOfSUDOKUMAP(SUDOKUMAP *sdm) // ������� ������ �� SUDOKUMAP
{
 mfree(sdm);
}

void MemFreeOfERRORSTRUCT(ERRORSTRUCT *errs) // ������� ������ �� ERRORSTRUCT
{
 mfree(errs);
};