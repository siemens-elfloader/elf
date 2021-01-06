#ifndef _IDLELINKS_H_
  #define _IDLELINKS_H_

typedef struct
{
  int x; 
  int y;
  int Enabled;
  int Type;
  char *Pic;
  int PicNumder;
  char *LinkName;
  char *FileName;
  void *next; // tridog, 15.08.2009 ƒелаем неограниченное число €рдычков
}TLabelData;

#endif
