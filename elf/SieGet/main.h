/*
  Проект SieGet Downloader
                          */

#ifndef _MAIN_H_
#define _MAIN_H_

#include "include.h"
#include "daemon.h"

#define color(x) (char *)(&(x))
#define allpoints(a) a.x, a.y, a.x2, a.y2

typedef struct
{
  char r;
  char g;
  char b;
  char a;
} RGBA;



#endif
