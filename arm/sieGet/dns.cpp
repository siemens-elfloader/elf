#include "include.h"
#include "dns.h"
#include "log.h"
#include "langpack.h"

//Проверить процесс (работа с DNR только в хелпере)
inline int CheckCepId()
{
  if (GBS_GetCurCepid()==MMI_CEPID) return 1;
  return 0;
}

DNR::DNR()
{
  dnr_tmr.dnr=this;
  DNR_ID = 0;
  host = NULL;
  log = NULL;
  DNR_TRIES = 0;
}

DNR::~DNR()
{
  _safe_delete(host);
#ifdef DNR_SEND_TIMER
  GBS_DelTimer((GBSTMR*)&dnr_tmr);
#endif
}

void DNR::Start(const char *_host, int _tries)
{
  _safe_delete(host);
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

#ifdef DNR_SEND_TIMER
void dnr_resend(DNR_TMR* tmr)
{
  SUBPROC((void *)_send_req, tmr->dnr);
}
#endif

void DNR::SendReq()
{
  if (CheckCepId())
  {
    SUBPROC((void *)_send_req, this);
    return;
  }
  int ***res = NULL;
  int err;

  err = async_gethostbyname(host, &res, &DNR_ID);
  
  if (err)
  {
    if (err == 0xC9 || err == 0xD6)
    {
      if (DNR_ID)
      {
        #ifdef DNR_SEND_TIMER
        DNR_TRIES --;
        if (!DNR_TRIES)
        {
          onResolve(DNR_RESULT_OUT_OF_TRIES, 0); // Истекло количество попыток
          DNR_ID = 0;
          return;
        }
        if (log)
          log->Print(LangPack::Active->data[LGP_WaitDNR], CLR_Green);
        GBS_StartTimerProc(&dnr_tmr, _tmr_second(5), (void(*)())&dnr_resend); // Пробуем резолвиться по таймеру
        #endif
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
      #ifdef DNR_SEND_TIMER
      if(IsTimerProc((GBSTMR*)&dnr_tmr)) GBS_StopTimer((GBSTMR*)&dnr_tmr);
      #endif
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

/*******************************************************************************
 DNRHandler
*******************************************************************************/

DNR *DNRHandler::GetDNR(int DNR_ID)
{
  DNRQ *tmp = queue;
  while (tmp)
  {
    if (tmp->dnr->DNR_ID==DNR_ID)
      return tmp->dnr; // Нашли!
    tmp = tmp->next;
  }
  return NULL; // Не нашли...
}

void DNRHandler::RegisterDNR(DNR *dnr)
{
  DNRQ *tmp = new DNRQ;
  tmp->dnr = dnr;
  tmp->next = queue;
  queue = tmp;
}

void DNRHandler::DeleteDNR(DNR *dnr)
{
  if (!queue)
    return;
  DNRQ *tmp;
  if (queue->dnr==dnr)
  {
    tmp = queue;
    queue = queue->next;
    delete tmp;
  }
  else
  {
    DNRQ * prev = queue;
    tmp = queue->next;
    while (tmp)
    {
      if (tmp->dnr == dnr)
      {
        prev->next = tmp->next;
        delete tmp;
        break;
      }
      prev = tmp;
      tmp = tmp->next;
    }
  }
}

DNRHandler::DNRHandler()
{
  queue = NULL;
}

DNRHandler::~DNRHandler()
{
  DNRQ *tmp;
  while (tmp = queue)
  {
    queue = queue->next;
    delete tmp;
  }
}
