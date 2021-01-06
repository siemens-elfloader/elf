#ifndef _SMILES_H_
#define _SMILES_H_

#include "../inc/pnglist.h"

#pragma pack(1)
typedef struct
{
  void *next;
  unsigned int key; //Для быстрой проверки
  unsigned int mask;
  char text[1];
}STXT_SMILES;
#pragma pack()

typedef struct
{
  void *next;
  unsigned int uni_smile;
  STXT_SMILES *lines; //Список строк
  STXT_SMILES *botlines;
}S_SMILES;

void FreeSmiles(void);
void InitSmiles(void);
void ProcessNextSmile(void);

S_SMILES *FindSmileById(int n);
S_SMILES *FindSmileByUni(int wchar);

extern S_SMILES *s_top;
extern DYNPNGICONLIST *SmilesImgList;

extern int smiles_max;
extern int smiles_loaded;

#endif





