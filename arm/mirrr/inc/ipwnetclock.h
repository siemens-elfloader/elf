
#ifndef _NETCLOCK_HPP_
#define _NETCLOCK_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

enum TipwNetClockActions {
  netclockIdle,
  netclockGetTime,
  netclockGetAndSetTime
};



typedef void __fastcall (__closure* TipwNetClockErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);


class PACKAGE TipwNetClock : public IPWCore
{
private:
  LONG reserved;
  TipwNetClockErrorEvent FOnError;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //The handle of the main socket used by the component.  //
  long __fastcall FSocketHandle();


  //The UDP port where the remote Time server is listening.  //
  USHORT __fastcall FTimePort();
  void __fastcall FSetTimePort(USHORT usTimePort);

  //Size in bytes of the largest UDP datagram that can be sent or received (Windows only).  //
  USHORT __fastcall FWinsockMaxDatagramSize();


  //Maximum number of sockets available to a single process (Windows only).  //
  USHORT __fastcall FWinsockMaxSockets();


  //The path to the Winsock DLL used (Windows only).  //
  AnsiString __fastcall FWinsockPath();
  void __fastcall FSetWinsockPath(AnsiString lpszWinsockPath);



  //Design-Time Properties
  TipwNetClockActions __fastcall FAction();
  void __fastcall FSetAction(TipwNetClockActions iAction);

  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);

  AnsiString __fastcall FLocalTime();


  AnsiString __fastcall FServerTime();




  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);



  AnsiString __fastcall FTimeServer();
  void __fastcall FSetTimeServer(AnsiString lpszTimeServer);

  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwNetClock(TComponent* Owner);
  virtual __fastcall TipwNetClock(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_43);
  virtual __fastcall ~TipwNetClock();


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



  __property USHORT TimePort = {
               read=FTimePort,
               write=FSetTimePort               };







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
    void __fastcall GetAndSetTime();
    void __fastcall GetTime();




__published:

  //PROPERTIES
    __property TipwNetClockActions Action = {
                    read=FAction,
                    write=FSetAction,
                    stored=false

                   };
    __property AnsiString LocalHost = {
                    read=FLocalHost,
                    write=FSetLocalHost,
                    stored=false

                   };
    __property AnsiString LocalTime = {
                    read=FLocalTime,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString ServerTime = {
                    read=FServerTime,
                    write=SetDummyAnsiString,
                    stored=false

                   };

    __property int Timeout = {
                    read=FTimeout,
                    write=FSetTimeout,
                    default=10
                   };

    __property AnsiString TimeServer = {
                    read=FTimeServer,
                    write=FSetTimeServer,
                    
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
    __property TipwNetClockErrorEvent OnError = {read=FOnError, write=FOnError};


}; //end class TipwNetClock

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _NETCLOCK_HPP_

