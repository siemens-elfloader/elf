#ifndef _FM_H_
  #define _FM_H_

#include "../inc/stdbool.h"
#define TCFMlines 256

// Проверяем расширения   AAA
bool IsExt(short type, char* name);

// Грузим файлы из папки. Респект
void LoadingDaemonList(const char* path, unsigned int re, unsigned int toPL);

//void NULLmass(int* mass, unsigned int end);

void ShowFM();

#endif
