#ifndef _ADDONS_H
#define _ADDONS_H

int _read32(int fh, void *buf, int len, unsigned int *err);
int _write32(int fh, void *buf, int len, unsigned int *err);
int savefile(char *fname, char *buf, int size);
char *loadfile(char *filename); // ��������� ����, �����������, ����� � loadfilesize
int getint(void *ptr); // �������� int
short getshort(void *ptr); // �������� short
void putint(void *ptr, int data); // �������� int
void putshort(void *ptr, short data); // �������� short
void bitblt(void *screen, void *bmp, int x, int y, int sizex, int sizey, int x0, int y0,  int colormask, int flags);
char *loadgraph(char *filename); // ��������� ������� (������������� � ������������)

#endif

