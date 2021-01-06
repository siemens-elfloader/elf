#include "include.h"
#include "SiemensPDU.h"
#include "MyIpcMessage.h"
#include "File.h"
#include "SmsData.h"
#include "Vibra.h"

//const char CFG_VIBRA_RHYTHM[]="90;10;0;";

Vibra::Vibra()
{
  zeromem(&this->thythm, sizeof(int)*VBA_MAX);
  this->vba_cnt=0;
  this->vba_pp=0;
  this->InitThythm();
}

Vibra::~Vibra()
{
  this->VibraStop();
}
/*
inline int mystr2int(const char *p)
{
  int r=0;
  int c;
  while((c=*p++))
  {
    if(c>'9' || c<'0')
      break;
    r=r*10+c-'0';
  }
  return r;
}
*/
void Vibra::InitThythm()
{
  int n=1;
  int c=0;
  const char *p=CFG_VIBRA_RHYTHM;
  while((c=*p))
  {
    if(n>=VBA_MAX)
      break;
    if(c==';')
    {
      n++;
      p++;
    }
    else
    {
      //this->thythm[n]=mystr2int(p);
      this->thythm[n]=str2int(p);
      n++;
      while((c=*p))
      {
	p++;
	if(c==';')
	  break;
      }
    }
  }
  this->vba_cnt=n;
}

void Vibra::ReInitThythm()
{
  zeromem(&this->thythm, sizeof(int)*VBA_MAX);
  this->vba_cnt=0;
  this->vba_pp=0;
  GBS_DelTimer(&this->vba_tmr);
  SetVibration(0);
  this->InitThythm();
}

void Vibra::VibraStart()
{
  if(CFG_NOTIFY_TIME && CFG_ENA_VIBRA && !IsCalling())
  {
    this->vba_pp=1;
    this->VibraNext();
  }
}

void Vibra::VibraNext()
{
  if (CFG_NOTIFY_TIME && CFG_ENA_VIBRA && this->vba_pp && SMSDATA->n_new && !IsCalling())
  {
    SetVibration(this->thythm[this->vba_pp]);
    if(this->vba_pp<this->vba_cnt) this->vba_pp++;
    else this->vba_pp=1;
    GBS_StartTimerProc(&this->vba_tmr, 216/6, this->VibraNextTmrProc);
  }
  else
  {
    this->vba_pp=0;
    GBS_DelTimer(&this->vba_tmr);
    SetVibration(0);
  }
}

void Vibra::VibraStop()
{
  this->vba_pp=0;
  GBS_DelTimer(&this->vba_tmr);
  SetVibration(0);
}

void Vibra::VibraNextTmrProc()
{
  SendMyIpc(SMSYS_IPC_VIBRA_NEXT);
}
