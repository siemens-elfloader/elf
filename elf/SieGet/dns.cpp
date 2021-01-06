#include "include.h"
#include "dns.h"
#include "log.h"

DNR *DNR::DNRTop = NULL;

//Проверить процесс (работа с DNR только в хелпере)
inline int CheckCepId()
{
  if (GBS_GetCurCepid()==MMI_CEPID) return 1;
  return 0;
}

DNR::DNR()
{
  LockSched();
  DNRPrev = DNRTop;
  if (DNRTop)
    DNRTop->DNRNext = this;
  DNRNext = NULL;
  DNRTop = this;
  UnlockSched();

  DNR_ID = 0;
  host = NULL;
  DNR_TRIES = 0;
}

DNR::~DNR()
{
  LockSched();
  if (DNRTop==this)
  {
    DNRTop = DNRPrev;
    if (DNRTop)
      DNRTop->DNRNext = NULL;
  }
  else
  {
    if (DNRNext)
      DNRNext->DNRPrev = DNRPrev;
    if (DNRPrev)
      DNRPrev->DNRNext = DNRNext;
  }

  if (host)
    delete host;

  UnlockSched();
}

void DNR::Start(const char *_host, int _tries)
{
  if (host)
    delete host;
  host = new char[strlen(_host)+1];
  strcpy(host, _host);
  DNR_TRIES = _tries;
  DNR_ID = 0;
  SendReq();
}

void _send_req(DNR *obj)
{
  obj->SendReq();
}

void DNR::SendReq()
{
  char tmp[256];

  if (CheckCepId())
  {
    SUBPROC((void *)_send_req, this);
    return;
  }
  int ***res = NULL;
  int err;
  err = async_gethostbyname(host, &res, &DNR_ID);

  sprintf(tmp, "Sent DNR %d: result 0x%X", DNR_ID, err);
  DEBUG(tmp);

  if (err)
  {
    if ((err==0xC9)||(err==0xD6))
    {
      if (DNR_ID)
      {
        return; // Ждем готовности DNR
      }
    }
    else
    {
      onResolve(DNR_RESULT_ERROR, err); // Получили ошибку
      DNR_ID = 0;
      return;
    }
  }
  if (res)
  {
    if (res[3])
    {
      onResolve(DNR_RESULT_OK, res[3][0][0]); // Получили адрес
      DNR_ID = 0;
    }
  }
  else
  {
    DNR_TRIES--;
    if (!DNR_TRIES)
    {
      onResolve(DNR_RESULT_OUT_OF_TRIES, 0); // Истекло количество попыток
      DNR_ID = 0;
    }
  }
}
