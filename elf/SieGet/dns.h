#ifndef _DNS_H_
#define _DNS_H_

#include "include.h"

#define DNR_RESULT_OK 0
#define DNR_RESULT_ERROR 1
#define DNR_RESULT_OUT_OF_TRIES 2

class DNR
{
public:
  DNR();
  ~DNR();
  void Start(const char *host, int tries);
  void SendReq();

  virtual void onResolve(int result, int value) = 0; //Â HELPER

  static DNR *DNRTop;
  DNR *DNRNext;
  DNR *DNRPrev;
  int DNR_ID;
private:
  int DNR_TRIES;
  char *host;
};

#endif
