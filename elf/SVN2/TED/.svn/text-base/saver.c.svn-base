#include "..\inc\swilib.h"

extern unsigned int STKSZ;
extern unsigned int STKSZ50;

extern int u_disk; //Дисковый указатель верхнего стека (в блоках по STKSZ50)
extern int d_disk; //Дисковый указатель нижнего стека (в блоках по STKSZ50)
extern unsigned int usp; //Указатель на верхний стек
extern unsigned int dsp; //Указатель на нижний стек
extern unsigned int dbat[]; //Таблица распределения блоков нижнего стека во временном файле
extern unsigned int ubat[]; //Таблица распределения блоков верхнего стека во временном файлe
extern char stkfile[];
extern char filename[];

extern char *dstk;
extern char *ustk;

extern volatile int disk_access;

extern unsigned int bl_ds(unsigned int pos);

extern int terminated; //Признак закрытия диалога
extern volatile unsigned int draw_mode;

extern void DiskErrorMsg(int mode);

#define flush_obuf(FILEH,P) {if (P>=STKSZ50) {if (fwrite(FILEH,obuf,P,&ul)!=P) DiskErrorMsg(4); P=0;}}

void savetext(void)
{
  char *ibuf=NULL;
  char *obuf=NULL;

  int sf;
  int f;
  unsigned int p;
  unsigned int ul;
  int i;
  char c;
  unsigned int seekpos;

  if (!(ibuf=malloc(STKSZ50)))
  {
    LockSched();
    ShowMSG(1,(int)"Can't alloc IBUF!");
    UnlockSched();
    goto LERR1;
  }
  if (!(obuf=malloc(STKSZ50)))
  {
    LockSched();
    ShowMSG(1,(int)"Can't alloc OBUF!");
    UnlockSched();
    goto LERR1;
  }
  f=fopen(filename,A_ReadWrite+A_BIN+A_Create+A_Truncate,P_READ+P_WRITE,&ul); //Создаем выходной файл
  if (f==-1)
  {
    DiskErrorMsg(4);
    goto LERR1;
  }
  sf=fopen(stkfile,A_ReadOnly+A_BIN,P_READ,&ul); //Файл верхнего стека
  if (f==-1)
  {
    DiskErrorMsg(3);
    goto LERR2;
  }

  i=0;
  while(i<=u_disk)
  {
    //Пишем верхний стек непосредственно
    p=ubat[i++];
    seekpos=STKSZ50*p;
    if (lseek(sf,seekpos,0,&ul,&ul)!=seekpos) DiskErrorMsg(2);
    if (fread(sf,ibuf,STKSZ50,&ul)!=STKSZ50) DiskErrorMsg(0);
    p=0;
    while(p!=STKSZ50)
    {
      if (!ibuf[p]) ibuf[p]=0x0D;
      p++;
    }
    if (fwrite(f,ibuf,STKSZ50,&ul)!=STKSZ50) DiskErrorMsg(4);
  }
  //Пишем верхний стек из ОЗУ
  p=0;
  i=0;
  while(p!=usp)
  {
    c=ustk[p];
    if (!c) c=0x0D;
    obuf[i]=c;
    i++;
    flush_obuf(f,i);
    p++;
  }
  p=dsp;
  while(p!=STKSZ)
  {
    //Пишем нижний стек из ОЗУ
    c=dstk[p];
    if (!c) c=0x0D;
    obuf[i]=c;
    i++;
    flush_obuf(f,i);
    p++;
  }
  if (fwrite(f,obuf,i,&ul)!=i) DiskErrorMsg(4); //Недобиток
  i=d_disk;
  while(i>=0)
  {
    //Пишем нижний стек
    p=dbat[i--];
    seekpos=STKSZ50*p;
    if (lseek(sf,seekpos,0,&ul,&ul)!=seekpos) DiskErrorMsg(2);
    if (fread(sf,ibuf,STKSZ50,&ul)!=STKSZ50) DiskErrorMsg(0);
    p=0;
    while(p!=STKSZ50)
    {
      if (!ibuf[p]) ibuf[p]=0x0D;
      p++;
    }
    if (fwrite(f,ibuf,STKSZ50,&ul)!=STKSZ50) DiskErrorMsg(4);
  }
  fclose(sf,&ul); //Более ничего интересного в верхнем стеке
LERR2:
  fclose(f,&ul);
LERR1:
  mfree(ibuf);
  mfree(obuf);
  disk_access=0;
  draw_mode=1; //Перерисовываем
  REDRAW();
}

