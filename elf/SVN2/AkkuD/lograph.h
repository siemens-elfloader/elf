#ifndef lograph__
#define lograph__


#include "utime.h"

#define LOGRAPHMAXPOINTS  128

typedef struct
{
  UTIME time;
  char cap;
}
TSample;

class TLograph
{
private:
  TSample pts[LOGRAPHMAXPOINTS];
  int npts;
  void AddPoint(UTIME time,char cap);
  TSample * GetPoint(int idx){if(idx>=npts) return 0; return pts+idx;};
  void LoadLogFile();
  void WriteLog(char *text);
  char ebu[128];
public:
  char * LastNAmsg;
  TLograph();
  ~TLograph();
  void PushCurrentPoint();
  float EstimateElapsedTime();//in hours
};
#endif
