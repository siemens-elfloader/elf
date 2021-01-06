#ifndef _BUFF_H_
#define _BUFF_H_

#define LOAD_SIZE 8192
extern int buffed;
extern int buffSize;
extern int readStartAdr;
extern int readOffset;
extern int readOffset1;
extern int readSize;
extern int visualOffset;
extern int visualSize;
extern int visualRows;
extern int maxVisualSize;

extern char* readBuffer;

int initBuffer(void);
int getStartOffset(void);
int setPrevBlock(void);
int setNextBlock(void);
int loadBlock(void);
int saveBlock(void);
WSHDR* getOffsetWS(int start, int offset, int wslen);
#endif
