#ifndef _BOOKMARK_H_
#define _BOOKMARK_H_

typedef struct BMKLIST {
  struct BMKLIST *next;
  int address;
  int offset;
  WSHDR *preview;
} BMKLIST;

void Free_BLIST(void);
int readAddrInt(void);
int writeAddrInt(BMKLIST* bmklist);
int create_menu_bookmark(void);
int getBMKMount(BMKLIST* bmklist);
void writeSysBMKInt(void);
void initBMKList(int start, int row);
int gotoBMKNode(BMKLIST* bl);

extern BMKLIST *blhead;
extern BMKLIST *bltop;

#endif
