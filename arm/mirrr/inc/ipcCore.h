//----------------------------------------------------------------------------
// IP*Works! CC V5 C++ Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com

//----------------------------------------------------------------------------
#ifndef _ipcCore_HPP_
#define _ipcCore_HPP_
//----------------------------------------------------------------------------

#pragma hdrstop

#include "ipworkscc.key"

#pragma warn -pia
#pragma warn -sig

#if (__BORLANDC__ < 0x530)
#define PACKAGE
#endif

#ifdef BCBBPL
#define IDEBPL
#endif

namespace Ipwcc {

enum TFIREWALLTYPES {
  fwNone,
  fwTunnel,
  fwSOCKS4,
  fwSOCKS5
};

enum TPROCESSOR {
  psVITAL
};





enum TCARDTYPE {
  ccUnknown,
  ccVisa,
  ccMasterCard,
  ccAMEX,
  ccDiscover,
  ccDiners,
  ccJCB,
  ccBankCard
};



enum TPROXYSSL {
  psAutomatic,
  psAlways,
  psNever,
  psTunnel
};




#ifdef IDEBPL
class PACKAGE TAbout : public TObject
{
  __fastcall TAbout(void);
};
#endif //IDEBPL

class PACKAGE EIPCCore : public Exception
{
  public:
    int Code;
    __fastcall EIPCCore(int err, char* desc);
};


class PACKAGE IPCCore : public TComponent
{

  private:
    void* reserved;

  protected:
    void __fastcall SetDummyAnsiString(AnsiString val){}
    void __fastcall SetDummyint(int val){}
    void __fastcall SetDummylong(long val){}
    void __fastcall SetDummybool(bool val){}
    void __fastcall SetDummyUSHORT(USHORT val){}


#ifdef IDEBPL
    void __fastcall WriteAbout(TAbout* val);
    TAbout* __fastcall ReadAbout(void);
#endif

	public:
	
    void __fastcall virtual AboutDlg();
		__fastcall virtual IPCCore(TComponent* Owner);

#ifdef IDEBPL
  __published:
    __property TAbout *About = {read=ReadAbout, write=WriteAbout, stored=false, nodefault};
#endif
};

}//namespace


#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipwcc;
#endif

#endif // _ipcCore;_HPP_


