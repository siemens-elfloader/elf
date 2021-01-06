
#ifndef _UDPPORT_HPP_
#define _UDPPORT_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {




typedef void __fastcall (__closure* TipwUDPPortDataInEvent)(System::TObject* Sender,
                                    char * Datagram, USHORT lenDatagram,
                                    AnsiString& SourceAddress,
                                    USHORT SourcePort);
typedef void __fastcall (__closure* TipwUDPPortErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwUDPPortReadyToSendEvent)(System::TObject* Sender);


class PACKAGE TipwUDPPort : public IPWCore
{
private:
  LONG reserved;
  TipwUDPPortDataInEvent FOnDataIn;
  TipwUDPPortErrorEvent FOnError;
  TipwUDPPortReadyToSendEvent FOnReadyToSend;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //Enables or disables data reception (the DataIn event).  //
  bool __fastcall FAcceptData();
  void __fastcall FSetAcceptData(bool bAcceptData);

  //Enables or disables sending and receiving of data.  Action property.  //
  bool __fastcall FActive();
  void __fastcall FSetActive(bool bActive);

  //A string of data to be sent to the remote host.  Write-only property.  //

  void __fastcall FSetDataToSend(AnsiString lpDataToSend);
  void __fastcall SetDataToSend(char *lpDataToSend, USHORT lenDataToSend);


  //If set to True, forces the socket to send data directly to interface (no routing).  //
  bool __fastcall FDontRoute();
  void __fastcall FSetDontRoute(bool bDontRoute);

  //If set to True, allows more than one instance of the component to be Active on the same LocalPort .  //
  bool __fastcall FShareLocalPort();
  void __fastcall FSetShareLocalPort(bool bShareLocalPort);

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








  long __fastcall FInBufferSize();
  void __fastcall FSetInBufferSize(long lInBufferSize);

  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);

  USHORT __fastcall FLocalPort();
  void __fastcall FSetLocalPort(USHORT usLocalPort);

  USHORT __fastcall FMaxPacketSize();
  void __fastcall FSetMaxPacketSize(USHORT lMaxPacketSize);

  long __fastcall FOutBufferSize();
  void __fastcall FSetOutBufferSize(long lOutBufferSize);

  USHORT __fastcall FQOSFlags();
  void __fastcall FSetQOSFlags(USHORT usQOSFlags);

  AnsiString __fastcall FRemoteHost();
  void __fastcall FSetRemoteHost(AnsiString lpszRemoteHost);

  USHORT __fastcall FRemotePort();
  void __fastcall FSetRemotePort(USHORT usRemotePort);





  USHORT __fastcall FTimeToLive();
  void __fastcall FSetTimeToLive(USHORT lTimeToLive);

  bool __fastcall FUseConnection();
  void __fastcall FSetUseConnection(bool bUseConnection);

  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwUDPPort(TComponent* Owner);
  virtual __fastcall TipwUDPPort(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_13);
  virtual __fastcall ~TipwUDPPort();


  //Fired when data is received.  //
  virtual void FireDataIn(char* Datagram, USHORT lenDatagram, char* SourceAddress, USHORT SourcePort);
  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired when the component is ready to send data.  //
  virtual void FireReadyToSend();



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };

  __property bool AcceptData = {
               read=FAcceptData,
               write=FSetAcceptData               };

  __property bool Active = {
               read=FActive,
               write=FSetActive               };

  __property AnsiString DataToSend = {

               write=FSetDataToSend               };

  __property bool DontRoute = {
               read=FDontRoute,
               write=FSetDontRoute               };

















  __property bool ShareLocalPort = {
               read=FShareLocalPort,
               write=FSetShareLocalPort               };

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
    void __fastcall Send(AnsiString Text);




__published:

  //PROPERTIES




    __property long InBufferSize = {
                    read=FInBufferSize,
                    write=FSetInBufferSize,
                    default=2048
                   };
    __property AnsiString LocalHost = {
                    read=FLocalHost,
                    write=FSetLocalHost,
                    stored=false

                   };
    __property USHORT LocalPort = {
                    read=FLocalPort,
                    write=FSetLocalPort,
                    default=0
                   };
    __property USHORT MaxPacketSize = {
                    read=FMaxPacketSize,
                    write=FSetMaxPacketSize,
                    default=2048
                   };
    __property long OutBufferSize = {
                    read=FOutBufferSize,
                    write=FSetOutBufferSize,
                    default=2048
                   };
    __property USHORT QOSFlags = {
                    read=FQOSFlags,
                    write=FSetQOSFlags,
                    default=0
                   };
    __property AnsiString RemoteHost = {
                    read=FRemoteHost,
                    write=FSetRemoteHost,
                    
                   };
    __property USHORT RemotePort = {
                    read=FRemotePort,
                    write=FSetRemotePort,
                    default=0
                   };


    __property USHORT TimeToLive = {
                    read=FTimeToLive,
                    write=FSetTimeToLive,
                    default=0
                   };
    __property bool UseConnection = {
                    read=FUseConnection,
                    write=FSetUseConnection,
                    default=false
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
    //Fired when data is received.
    __property TipwUDPPortDataInEvent OnDataIn = {read=FOnDataIn, write=FOnDataIn};
    //Information about errors during data delivery.
    __property TipwUDPPortErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired when the component is ready to send data.
    __property TipwUDPPortReadyToSendEvent OnReadyToSend = {read=FOnReadyToSend, write=FOnReadyToSend};


}; //end class TipwUDPPort

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _UDPPORT_HPP_

