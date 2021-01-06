
#ifndef _MX_HPP_
#define _MX_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {




typedef void __fastcall (__closure* TipwMXErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwMXResponseEvent)(System::TObject* Sender,
                                    int RequestId,
                                    AnsiString& Domain,
                                    AnsiString& MailServer,
                                    int Precedence,
                                    long TimeToLive,
                                    int StatusCode,
                                    AnsiString& Description);


class PACKAGE TipwMX : public IPWCore
{
private:
  LONG reserved;
  TipwMXErrorEvent FOnError;
  TipwMXResponseEvent FOnResponse;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //The port where the DNS server is listening.  //
  USHORT __fastcall FDNSPort();
  void __fastcall FSetDNSPort(USHORT usDNSPort);

  //Identifies each request.  //
  USHORT __fastcall FRequestId();
  void __fastcall FSetRequestId(USHORT usRequestId);

  //The handle of the main socket used by the component.  //
  long __fastcall FSocketHandle();


  //Size in bytes of the largest UDP datagram that can be sent or received (Windows only).  //
  USHORT __fastcall FWinsockMaxDatagramSize();


  //Maximum number of sockets available to a single process (Windows only).  //
  USHORT __fastcall FWinsockMaxSockets();


  //The path to the Winsock DLL used (Windows only).  //
  AnsiString __fastcall FWinsockPath();
  void __fastcall FSetWinsockPath(AnsiString lpszWinsockPath);



  //Design-Time Properties


  AnsiString __fastcall FDNSServer();
  void __fastcall FSetDNSServer(AnsiString lpszDNSServer);

  AnsiString __fastcall FEmailAddress();
  void __fastcall FSetEmailAddress(AnsiString lpszEmailAddress);

  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);

  AnsiString __fastcall FMailServer();






  AnsiString __fastcall FStatus();


  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);

  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwMX(TComponent* Owner);
  virtual __fastcall TipwMX(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_29);
  virtual __fastcall ~TipwMX();


  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired for each MailServer accepting email for the domain.  //
  virtual void FireResponse(int RequestId, char* Domain, char* MailServer, int Precedence, long TimeToLive, int StatusCode, char* Description);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };

  __property USHORT DNSPort = {
               read=FDNSPort,
               write=FSetDNSPort               };









  __property USHORT RequestId = {
               read=FRequestId,
               write=FSetRequestId               };

  __property long SocketHandle = {
               read=FSocketHandle
               };









  __property USHORT WinsockMaxDatagramSize = {
               read=FWinsockMaxDatagramSize
               };

  __property USHORT WinsockMaxSockets = {
               read=FWinsockMaxSockets
               };

  __property AnsiString WinsockPath = {
               read=FWinsockPath,
               write=FSetWinsockPath               };





  //METHODS
    void __fastcall DoEvents();
    void __fastcall Resolve(AnsiString EmailAddress);




__published:

  //PROPERTIES

    __property AnsiString DNSServer = {
                    read=FDNSServer,
                    write=FSetDNSServer,
                    
                   };
    __property AnsiString EmailAddress = {
                    read=FEmailAddress,
                    write=FSetEmailAddress,
                    stored=false

                   };
    __property AnsiString LocalHost = {
                    read=FLocalHost,
                    write=FSetLocalHost,
                    stored=false

                   };
    __property AnsiString MailServer = {
                    read=FMailServer,
                    write=SetDummyAnsiString,
                    stored=false

                   };


    __property AnsiString Status = {
                    read=FStatus,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property int Timeout = {
                    read=FTimeout,
                    write=FSetTimeout,
                    default=0
                   };
    __property AnsiString WinsockInfo = {
                    read=FWinsockInfo,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property bool WinsockLoaded = {
                    read=FWinsockLoaded,
                    write=FSetWinsockLoaded,
                    default=true
                   };



    __property AnsiString WinsockStatus = {
                    read=FWinsockStatus,
                    write=SetDummyAnsiString,
                    stored=false

                   };


  //EVENTS
    //Information about errors during data delivery.
    __property TipwMXErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired for each MailServer accepting email for the domain.
    __property TipwMXResponseEvent OnResponse = {read=FOnResponse, write=FOnResponse};


}; //end class TipwMX

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _MX_HPP_

