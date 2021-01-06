
#ifndef _PING_HPP_
#define _PING_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {




typedef void __fastcall (__closure* TipwPingErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);


class PACKAGE TipwPing : public IPWCore
{
private:
  LONG reserved;
  TipwPingErrorEvent FOnError;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //The handle of the main socket used by the component.  //
  long __fastcall FSocketHandle();


  //The time to live (TTL) value for the ICMP packets sent by the component.  //
  USHORT __fastcall FTimeToLive();
  void __fastcall FSetTimeToLive(USHORT usTimeToLive);

  //The type of the ICMP message sent as a ping request.  //
  int __fastcall FTypeOfService();
  void __fastcall FSetTypeOfService(int iTypeOfService);

  //Size in bytes of the largest UDP datagram that can be sent or received (Windows only).  //
  USHORT __fastcall FWinsockMaxDatagramSize();


  //Maximum number of sockets available to a single process (Windows only).  //
  USHORT __fastcall FWinsockMaxSockets();


  //The path to the Winsock DLL used (Windows only).  //
  AnsiString __fastcall FWinsockPath();
  void __fastcall FSetWinsockPath(AnsiString lpszWinsockPath);



  //Design-Time Properties
  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);

  USHORT __fastcall FPacketSize();
  void __fastcall FSetPacketSize(USHORT usPacketSize);

  USHORT __fastcall FQOSFlags();
  void __fastcall FSetQOSFlags(USHORT usQOSFlags);

  AnsiString __fastcall FRemoteHost();
  void __fastcall FSetRemoteHost(AnsiString lpszRemoteHost);

  AnsiString __fastcall FResponseSource();


  long __fastcall FResponseTime();




  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);





  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwPing(TComponent* Owner);
  virtual __fastcall TipwPing(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_44);
  virtual __fastcall ~TipwPing();


  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };













  __property long SocketHandle = {
               read=FSocketHandle
               };



  __property USHORT TimeToLive = {
               read=FTimeToLive,
               write=FSetTimeToLive               };

  __property int TypeOfService = {
               read=FTypeOfService,
               write=FSetTypeOfService               };





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
    void __fastcall PingHost(AnsiString Host);




__published:

  //PROPERTIES
    __property AnsiString LocalHost = {
                    read=FLocalHost,
                    write=FSetLocalHost,
                    stored=false

                   };
    __property USHORT PacketSize = {
                    read=FPacketSize,
                    write=FSetPacketSize,
                    default=64
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
    __property AnsiString ResponseSource = {
                    read=FResponseSource,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property long ResponseTime = {
                    read=FResponseTime,
                    write=SetDummylong,
                    stored=false

                   };

    __property int Timeout = {
                    read=FTimeout,
                    write=FSetTimeout,
                    default=10
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
    __property TipwPingErrorEvent OnError = {read=FOnError, write=FOnError};


}; //end class TipwPing

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _PING_HPP_

