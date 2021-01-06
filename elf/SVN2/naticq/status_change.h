#ifndef _STATUSCHANGE_H_
  #define _STATUSCHANGE_H_

// �������� ���� ����� �������
void DispStatusChangeMenu();

// �������� ���� ����� XStatus'�
void DispXStatusChangeMenu(void);


void LoadXStatusText(void);
void SaveXStatusText(void);
void FreeXStatusText(void);
char *GetXStatusStr(int n, int *len);

//  <tridog/>
//  2.01.11. ����������.
void AutoStatusOnIdle(void);
void InitAutoStatusEngine(void);
void DisposeAutoStatusEngine(void);
void AutoStatusOnAccessory(void);
//  </tridog>

#endif
