#ifndef _VIBRATION_H_
#define _VIBRATION_H_

#define VBA_MAX 64

class Vibra
{
public:
  Vibra();
  ~Vibra();
  void ReInitThythm();
  void VibraStart();
  void VibraNext();
  void VibraStop();
private:
  GBSTMR vba_tmr;
  int vba_pp; //0,stop
  int vba_cnt;
  int thythm[VBA_MAX];
  static void VibraNextTmrProc();
  void InitThythm();
};
#endif


