
#ifndef _IPINFO_HPP_
#define _IPINFO_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {




typedef void __fastcall (__closure* TipwIPInfoErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwIPInfoRequestCompleteEvent)(System::TObject* Sender,
                                    long RequestId,
                                    int StatusCode,
                                    AnsiString& Description);


class PACKAGE TipwIPInfo : public IPWCore
{
private:
  LONG reserved;
  TipwIPInfoErrorEvent FOnError;
  TipwIPInfoRequestCompleteEvent FOnRequestComplete;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //Size in bytes of the largest UDP datagram that can be sent or received (Windows only).  //
  USHORT __fastcall FWinsockMaxDatagramSize();


  //Maximum number of sockets available to a single process (Windows only).  //
  USHORT __fastcall FWinsockMaxSockets();


  //The path to the Winsock DLL used (Windows only).  //
  AnsiString __fastcall FWinsockPath();
  void __fastcall FSetWinsockPath(AnsiString lpszWinsockPath);



  //Design-Time Properties
  AnsiString __fastcall FHostAddress();
  void __fastcall FSetHostAddress(AnsiString lpszHostAddress);

  AnsiString __fastcall FHostAliases();


  AnsiString __fastcall FHostName();
  void __fastcall FSetHostName(AnsiString lpszHostName);

  AnsiString __fastcall FLocalHost();


  AnsiString __fastcall FOtherAddresses();


  USHORT __fastcall FPendingRequests();
  void __fastcall FSetPendingRequests(USHORT usPendingRequests);

  long __fastcall FRequestId();


  AnsiString __fastcall FServiceAliases();


  AnsiString __fastcall FServiceName();
  void __fastcall FSetServiceName(AnsiString lpszServiceName);

  USHORT __fastcall FServicePort();
  void __fastcall FSetServicePort(USHORT usServicePort);

  AnsiString __fastcall FServiceProtocol();
  void __fastcall FSetServiceProtocol(AnsiString lpszServiceProtocol);

  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwIPInfo(TComponent* Owner);
  virtual __fastcall TipwIPInfo(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_15);
  virtual __fastcall ~TipwIPInfo();


  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired after an asynchronous request completes.  //
  virtual void FireRequestComplete(long RequestId, int StatusCode, char* Description);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
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
    AnsiString __fastcall ResolveAddress(AnsiString HostAddress);
    AnsiString __fastcall ResolveName(AnsiString HostName);




__published:

  //PROPERTIES
    __property AnsiString HostAddress = {
                    read=FHostAddress,
                    write=FSetHostAddress,
                    stored=false

                   };
    __property AnsiString HostAliases = {
                    read=FHostAliases,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString HostName = {
                    read=FHostName,
                    write=FSetHostName,
                    stored=false

                   };
    __property AnsiString LocalHost = {
                    read=FLocalHost,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString OtherAddresses = {
                    read=FOtherAddresses,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property USHORT PendingRequests = {
                    read=FPendingRequests,
                    write=FSetPendingRequests,
                    default=0
                   };
    __property long RequestId = {
                    read=FRequestId,
                    write=SetDummylong,
                    stored=false

                   };
    __property AnsiString ServiceAliases = {
                    read=FServiceAliases,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString ServiceName = {
                    read=FServiceName,
                    write=FSetServiceName,
                    
                   };
    __property USHORT ServicePort = {
                    read=FServicePort,
                    write=FSetServicePort,
                    default=0
                   };
    __property AnsiString ServiceProtocol = {
                    read=FServiceProtocol,
                    write=FSetServiceProtocol,
                    
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
    __property TipwIPInfoErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired after an asynchronous request completes.
    __property TipwIPInfoRequestCompleteEvent OnRequestComplete = {read=FOnRequestComplete, write=FOnRequestComplete};


}; //end class TipwIPInfo

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _IPINFO_HPP_

