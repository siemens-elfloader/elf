
#ifndef _TRACEROUTE_HPP_
#define _TRACEROUTE_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {




typedef void __fastcall (__closure* TipwTraceRouteErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwTraceRouteHopEvent)(System::TObject* Sender,
                                    int HopNumber,
                                    AnsiString& HostAddress,
                                    long Duration);
typedef void __fastcall (__closure* TipwTraceRouteHopResolvedEvent)(System::TObject* Sender,
                                    int HopNumber,
                                    int StatusCode,
                                    AnsiString& HopHostName);


class PACKAGE TipwTraceRoute : public IPWCore
{
private:
  LONG reserved;
  TipwTraceRouteErrorEvent FOnError;
  TipwTraceRouteHopEvent FOnHop;
  TipwTraceRouteHopResolvedEvent FOnHopResolved;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //The IP address of the host for a particular hop in the trace.  //
  AnsiString __fastcall FHopHostAddress(USHORT HopIndex);


  //The name of the host for a particular hop in the trace.  //
  AnsiString __fastcall FHopHostName(USHORT HopIndex);


  //The amount of time taken by a particular hop in the trace.  //
  long __fastcall FHopTime(USHORT HopIndex);


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
  int __fastcall FHopCount();






  int __fastcall FHopLimit();
  void __fastcall FSetHopLimit(int iHopLimit);



  int __fastcall FHopTimeout();
  void __fastcall FSetHopTimeout(int iHopTimeout);

  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);

  USHORT __fastcall FQOSFlags();
  void __fastcall FSetQOSFlags(USHORT usQOSFlags);

  AnsiString __fastcall FRemoteHost();
  void __fastcall FSetRemoteHost(AnsiString lpszRemoteHost);

  bool __fastcall FResolveNames();
  void __fastcall FSetResolveNames(bool bResolveNames);



  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);

  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwTraceRoute(TComponent* Owner);
  virtual __fastcall TipwTraceRoute(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_48);
  virtual __fastcall ~TipwTraceRoute();


  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired for each hop in the trace to the RemoteHost .  //
  virtual void FireHop(int HopNumber, char* HostAddress, long Duration);
  //Fired when the name of a hop address is found.  //
  virtual void FireHopResolved(int HopNumber, int StatusCode, char* HopHostName);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };



  __property AnsiString HopHostAddress[USHORT HopIndex] = {
               read=FHopHostAddress
               };

  __property AnsiString HopHostName[USHORT HopIndex] = {
               read=FHopHostName
               };



  __property long HopTime[USHORT HopIndex] = {
               read=FHopTime
               };











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
    void __fastcall TraceTo(AnsiString Host);




__published:

  //PROPERTIES
    __property int HopCount = {
                    read=FHopCount,
                    write=SetDummyint,
                    stored=false

                   };


    __property int HopLimit = {
                    read=FHopLimit,
                    write=FSetHopLimit,
                    default=64
                   };

    __property int HopTimeout = {
                    read=FHopTimeout,
                    write=FSetHopTimeout,
                    default=10
                   };
    __property AnsiString LocalHost = {
                    read=FLocalHost,
                    write=FSetLocalHost,
                    stored=false

                   };
    __property USHORT QOSFlags = {
                    read=FQOSFlags,
                    write=FSetQOSFlags,
                    default=0
                   };
    __property AnsiString RemoteHost = {
                    read=FRemoteHost,
                    write=FSetRemoteHost,
                    stored=false

                   };
    __property bool ResolveNames = {
                    read=FResolveNames,
                    write=FSetResolveNames,
                    default=false
                   };

    __property int Timeout = {
                    read=FTimeout,
                    write=FSetTimeout,
                    default=60
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
    __property TipwTraceRouteErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired for each hop in the trace to the RemoteHost .
    __property TipwTraceRouteHopEvent OnHop = {read=FOnHop, write=FOnHop};
    //Fired when the name of a hop address is found.
    __property TipwTraceRouteHopResolvedEvent OnHopResolved = {read=FOnHopResolved, write=FOnHopResolved};


}; //end class TipwTraceRoute

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _TRACEROUTE_HPP_

