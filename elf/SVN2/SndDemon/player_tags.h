#ifndef _MP3_TAGS_H_
  #define _MP3_TAGS_H_
  extern  void *pcsmadr;
  extern   WSHDR *wstag;
  extern const RECT cTgr;  
  extern int scr_w;
  extern const char clr[];
  extern int TopG (int);

  void initTags(void);
  void GetTags();
  int  ShowTag(void);
#endif
