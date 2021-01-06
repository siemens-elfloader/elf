#ifndef _ADDONS_H
#define _ADDONS_H

int _read32(int fh, void *buf, int len, unsigned int *err);
int _write32(int fh, void *buf, int len, unsigned int *err);
int savefile(char *fname, char *buf, int size);
char *loadfile(char *filename); // Загрузить файл, распаковать, длина в loadfilesize
int getint(void *ptr); // Получить int
short getshort(void *ptr); // Получить short
void putint(void *ptr, int data); // Записать int
void putshort(void *ptr, short data); // Записать short
void bitblt(void *screen, void *bmp, int x, int y, int sizex, int sizey, int x0, int y0,  int colormask, int flags);
char *loadgraph(char *filename); // Загрузить графику (распаковываем и перекодируем)

#endif

