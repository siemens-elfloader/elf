#ifndef _SND_BUFS_H_
  #define _SND_BUFS_H_

  extern const unsigned int allowbuf;
  extern const unsigned int audcfg;
  extern const unsigned int buff_nof;
  extern const unsigned int buff_size;
  extern   word  oldAudValue;
  void SetupBuffers(word val);
  int autosearch(void);
#endif
