//----------------------------------------------------------------------------
// IP*Works! V5 C++ Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com

//----------------------------------------------------------------------------
#ifndef _ipwCore_HPP_
#define _ipwCore_HPP_
//----------------------------------------------------------------------------

#pragma hdrstop

#include "ipworks.key"

#pragma warn -pia
#pragma warn -sig

#if (__BORLANDC__ < 0x530)
#define PACKAGE
#endif

#ifdef BCBBPL
#define IDEBPL
#endif

namespace Ipworks {


enum TFIREWALLTYPES {
  fwNone,
  fwTunnel,
  fwSOCKS4,
  fwSOCKS5
};





















































#ifdef IDEBPL
class PACKAGE TAbout : public TObject
{
  __fastcall TAbout(void);
};
#endif //IDEBPL

class PACKAGE EIPWCore : public Exception
{
  public:
    int Code;
    __fastcall EIPWCore(int err, char* desc);
};


class PACKAGE IPWCore : public TComponent
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
		__fastcall virtual IPWCore(TComponent* Owner);

#ifdef IDEBPL
  __published:
    __property TAbout *About = {read=ReadAbout, write=WriteAbout, stored=false, nodefault};
#endif
};

}//namespace


#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

#endif // _ipwCore;_HPP_


