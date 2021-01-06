
#ifndef _IPDAEMON_HPP_
#define _IPDAEMON_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {




typedef void __fastcall (__closure* TipwIPDaemonConnectedEvent)(System::TObject* Sender,
                                    USHORT ConnectionId,
                                    int StatusCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwIPDaemonConnectionRequestEvent)(System::TObject* Sender,
                                    bool& Accept);
typedef void __fastcall (__closure* TipwIPDaemonDataInEvent)(System::TObject* Sender,
                                    USHORT ConnectionId,
                                    char * Text, USHORT lenText,
                                    bool EOL);
typedef void __fastcall (__closure* TipwIPDaemonDisconnectedEvent)(System::TObject* Sender,
                                    USHORT ConnectionId,
                                    int StatusCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwIPDaemonErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwIPDaemonReadyToSendEvent)(System::TObject* Sender,
                                    USHORT ConnectionId);


class PACKAGE TipwIPDaemon : public IPWCore
{
private:
  LONG reserved;
  TipwIPDaemonConnectedEvent FOnConnected;
  TipwIPDaemonConnectionRequestEvent FOnConnectionRequest;
  TipwIPDaemonDataInEvent FOnDataIn;
  TipwIPDaemonDisconnectedEvent FOnDisconnected;
  TipwIPDaemonErrorEvent FOnError;
  TipwIPDaemonReadyToSendEvent FOnReadyToSend;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //Enables or disables data reception (the DataIn event).  //
  bool __fastcall FAcceptData(USHORT ConnectionId);
  void __fastcall FSetAcceptData(USHORT ConnectionId, bool bAcceptData);

  //The number of bytes actually sent after an assignment to DataToSend .  //
  long __fastcall FBytesSent(USHORT ConnectionId);


  //The handle of the socket used by a particular connection.  //
  long __fastcall FClientSocketHandle(USHORT ConnectionId);


  //Used to disconnect individual connections and/or show their status.  //
  bool __fastcall FConnected(USHORT ConnId);
  void __fastcall FSetConnected(USHORT ConnId, bool bConnected);

  //The maximum number of pending connections maintained by the TCP/IP subsystem.  //
  USHORT __fastcall FConnectionBacklog();
  void __fastcall FSetConnectionBacklog(USHORT usConnectionBacklog);

  //The number of currently connected clients.  //
  int __fastcall FConnectionCount();


  //A string of data to be sent to the remote host.  Write-only property.  //

  void __fastcall FSetDataToSend(USHORT ConnectionId, AnsiString lpDataToSend);
  void __fastcall SetDataToSend(USHORT ConnectionId, char *lpDataToSend, USHORT lenDataToSend);


  //Used to break the incoming data stream into chunks separated by EOL .  //
  AnsiString __fastcall FEOL(USHORT ConnectionId);
  void __fastcall FSetEOL(USHORT ConnectionId, AnsiString lpEOL);
  void __fastcall SetEOL(USHORT ConnectionId, char *lpEOL, USHORT lenEOL);


  //If True, the component accepts incoming connections on LocalPort.  //
  bool __fastcall FListening();
  void __fastcall FSetListening(bool bListening);

  //The IP address of the interface for ConnectionId in Internet dotted format.  //
  AnsiString __fastcall FLocalAddress(USHORT ConnectionId);


  //The IP address of the RemoteHost in Internet dotted format.  //
  AnsiString __fastcall FRemoteHost(USHORT ConnectionId);


  //The IP port of the RemoteHost for a connection.  //
  USHORT __fastcall FRemotePort(USHORT ConnectionId);


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

  bool __fastcall FKeepAlive();
  void __fastcall FSetKeepAlive(bool bKeepAlive);

  bool __fastcall FLinger();
  void __fastcall FSetLinger(bool bLinger);





  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);

  USHORT __fastcall FLocalPort();
  void __fastcall FSetLocalPort(USHORT usLocalPort);

  long __fastcall FMaxLineLength();
  void __fastcall FSetMaxLineLength(long lMaxLineLength);

  long __fastcall FOutBufferSize();
  void __fastcall FSetOutBufferSize(long lOutBufferSize);







  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwIPDaemon(TComponent* Owner);
  virtual __fastcall TipwIPDaemon(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_12);
  virtual __fastcall ~TipwIPDaemon();


  //Fired immediately after a connection completes (or fails).  //
  virtual void FireConnected(USHORT ConnectionId, int StatusCode, char* Description);
  //Fired when a request for connection comes from a remote host.  //
  virtual void FireConnectionRequest(bool& Accept);
  //Fired when data (complete lines) comes in.  //
  virtual void FireDataIn(USHORT ConnectionId, char* Text, USHORT lenText, bool EOL);
  //Fired when a connection is closed.  //
  virtual void FireDisconnected(USHORT ConnectionId, int StatusCode, char* Description);
  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired when the component is ready to send data.  //
  virtual void FireReadyToSend(USHORT ConnectionId);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };

  __property bool AcceptData[USHORT ConnectionId] = {
               read=FAcceptData,
               write=FSetAcceptData               };

  __property long BytesSent[USHORT ConnectionId] = {
               read=FBytesSent
               };

  __property long ClientSocketHandle[USHORT ConnectionId] = {
               read=FClientSocketHandle
               };

  __property bool Connected[USHORT ConnId] = {
               read=FConnected,
               write=FSetConnected               };

  __property USHORT ConnectionBacklog = {
               read=FConnectionBacklog,
               write=FSetConnectionBacklog               };

  __property int ConnectionCount = {
               read=FConnectionCount
               };

  __property AnsiString DataToSend[USHORT ConnectionId] = {

               write=FSetDataToSend               };

  __property AnsiString EOL[USHORT ConnectionId] = {
               read=FEOL,
               write=FSetEOL               };







  __property bool Listening = {
               read=FListening,
               write=FSetListening               };

  __property AnsiString LocalAddress[USHORT ConnectionId] = {
               read=FLocalAddress
               };









  __property AnsiString RemoteHost[USHORT ConnectionId] = {
               read=FRemoteHost
               };

  __property USHORT RemotePort[USHORT ConnectionId] = {
               read=FRemotePort
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
    void __fastcall Disconnect(long ConnectionId);
    void __fastcall DoEvents();
    void __fastcall Send(long ConnectionId, AnsiString Text);




__published:

  //PROPERTIES








    __property long InBufferSize = {
                    read=FInBufferSize,
                    write=FSetInBufferSize,
                    default=2048
                   };
    __property bool KeepAlive = {
                    read=FKeepAlive,
                    write=FSetKeepAlive,
                    default=false
                   };
    __property bool Linger = {
                    read=FLinger,
                    write=FSetLinger,
                    default=true
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
    __property long MaxLineLength = {
                    read=FMaxLineLength,
                    write=FSetMaxLineLength,
                    default=2048
                   };
    __property long OutBufferSize = {
                    read=FOutBufferSize,
                    write=FSetOutBufferSize,
                    default=2048
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
    //Fired immediately after a connection completes (or fails).
    __property TipwIPDaemonConnectedEvent OnConnected = {read=FOnConnected, write=FOnConnected};
    //Fired when a request for connection comes from a remote host.
    __property TipwIPDaemonConnectionRequestEvent OnConnectionRequest = {read=FOnConnectionRequest, write=FOnConnectionRequest};
    //Fired when data (complete lines) comes in.
    __property TipwIPDaemonDataInEvent OnDataIn = {read=FOnDataIn, write=FOnDataIn};
    //Fired when a connection is closed.
    __property TipwIPDaemonDisconnectedEvent OnDisconnected = {read=FOnDisconnected, write=FOnDisconnected};
    //Information about errors during data delivery.
    __property TipwIPDaemonErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired when the component is ready to send data.
    __property TipwIPDaemonReadyToSendEvent OnReadyToSend = {read=FOnReadyToSend, write=FOnReadyToSend};


}; //end class TipwIPDaemon

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _IPDAEMON_HPP_

