#ifndef _FILE_H_
#define _FILE_H_

#define MAX_EXT 8

extern int fileSize;
extern unsigned int err;
extern int fd;
extern char procfile[];

int openFile(char* filename);
void open_select_file_gui(int type);
char* GetFileName(char* fname);

#endif
