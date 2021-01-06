#ifndef _STATUSCHANGE_H_
  #define _STATUSCHANGE_H_

// Показать меню смены статуса
void DispStatusChangeMenu();

// Показать меню смены XStatus'а
void DispXStatusChangeMenu(void);


void LoadXStatusText(void);
void SaveXStatusText(void);
void FreeXStatusText(void);
char *GetXStatusStr(int n, int *len);

#endif
