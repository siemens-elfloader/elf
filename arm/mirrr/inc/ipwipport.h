
#ifndef _IPPORT_HPP_
#define _IPPORT_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

typedef TFIREWALLTYPES TipwIPPortFirewallTypes;




typedef void __fastcall (__closure* TipwIPPortConnectedEvent)(System::TObject* Sender,
                                    int StatusCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwIPPortDataInEvent)(System::TObject* Sender,
                                    char * Text, USHORT lenText,
                                    bool EOL);
typedef void __fastcall (__closure* TipwIPPortDisconnectedEvent)(System::TObject* Sender,
                                    int StatusCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwIPPortErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwIPPortReadyToSendEvent)(System::TObject* Sender);


class PACKAGE TipwIPPort : public IPWCore
{
private:
  LONG reserved;
  TipwIPPortConnectedEvent FOnConnected;
  TipwIPPortDataInEvent FOnDataIn;
  TipwIPPortDisconnectedEvent FOnDisconnected;
  TipwIPPortErrorEvent FOnError;
  TipwIPPortReadyToSendEvent FOnReadyToSend;


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

  //The number of bytes actually sent after an assignment to DataToSend .  //
  long __fastcall FBytesSent();


  //Triggers a connection or disconnection.  Action property.  //
  bool __fastcall FConnected();
  void __fastcall FSetConnected(bool bConnected);

  //A string of data to be sent to the remote host.  //

  void __fastcall FSetDataToSend(AnsiString lpDataToSend);
  void __fastcall SetDataToSend(char *lpDataToSend, USHORT lenDataToSend);


  //Used to send other data to firewall.  //
  AnsiString __fastcall FFirewallData();
  void __fastcall FSetFirewallData(AnsiString lpFirewallData);
  void __fastcall SetFirewallData(char *lpFirewallData, USHORT lenFirewallData);


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








  AnsiString __fastcall FEOL();
  void __fastcall FSetEOL(AnsiString lpEOL);
  void __fastcall SetEOL(char *lpEOL, USHORT lenEOL);




  AnsiString __fastcall FFirewallHost();
  void __fastcall FSetFirewallHost(AnsiString lpszFirewallHost);

  AnsiString __fastcall FFirewallPassword();
  void __fastcall FSetFirewallPassword(AnsiString lpszFirewallPassword);

  USHORT __fastcall FFirewallPort();
  void __fastcall FSetFirewallPort(USHORT usFirewallPort);

  TipwIPPortFirewallTypes __fastcall FFirewallType();
  void __fastcall FSetFirewallType(TipwIPPortFirewallTypes iFirewallType);

  AnsiString __fastcall FFirewallUser();
  void __fastcall FSetFirewallUser(AnsiString lpszFirewallUser);

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

  AnsiString __fastcall FRemoteHost();
  void __fastcall FSetRemoteHost(AnsiString lpszRemoteHost);

  USHORT __fastcall FRemotePort();
  void __fastcall FSetRemotePort(USHORT usRemotePort);



  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);

  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwIPPort(TComponent* Owner);
  virtual __fastcall TipwIPPort(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_11);
  virtual __fastcall ~TipwIPPort();


  //Fired immediately after a connection completes (or fails).  //
  virtual void FireConnected(int StatusCode, char* Description);
  //Fired when data (complete lines) comes in.  //
  virtual void FireDataIn(char* Text, USHORT lenText, bool EOL);
  //Fired when a connection is closed.  //
  virtual void FireDisconnected(int StatusCode, char* Description);
  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired when IPPort is ready to send data.  //
  virtual void FireReadyToSend();



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };

  __property bool AcceptData = {
               read=FAcceptData,
               write=FSetAcceptData               };

  __property long BytesSent = {
               read=FBytesSent
               };

  __property bool Connected = {
               read=FConnected,
               write=FSetConnected               };

  __property AnsiString DataToSend = {

               write=FSetDataToSend               };



  __property AnsiString FirewallData = {
               read=FFirewallData,
               write=FSetFirewallData               };





























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
    void __fastcall Connect(AnsiString Host, int Port);
    void __fastcall Disconnect();
    void __fastcall DoEvents();
    void __fastcall Send(AnsiString Text);




__published:

  //PROPERTIES




    __property AnsiString EOL = {
                    read=FEOL,
                    write=FSetEOL,
                    
                   };

    __property AnsiString FirewallHost = {
                    read=FFirewallHost,
                    write=FSetFirewallHost,
                    
                   };
    __property AnsiString FirewallPassword = {
                    read=FFirewallPassword,
                    write=FSetFirewallPassword,
                    
                   };
    __property USHORT FirewallPort = {
                    read=FFirewallPort,
                    write=FSetFirewallPort,
                    default=0
                   };
    __property TipwIPPortFirewallTypes FirewallType = {
                    read=FFirewallType,
                    write=FSetFirewallType,
                    default=fwNone
                   };
    __property AnsiString FirewallUser = {
                    read=FFirewallUser,
                    write=FSetFirewallUser,
                    
                   };
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
    __property AnsiString RemoteHost = {
                    read=FRemoteHost,
                    write=FSetRemoteHost,
                    
                   };
    __property USHORT RemotePort = {
                    read=FRemotePort,
                    write=FSetRemotePort,
                    default=0
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
    //Fired immediately after a connection completes (or fails).
    __property TipwIPPortConnectedEvent OnConnected = {read=FOnConnected, write=FOnConnected};
    //Fired when data (complete lines) comes in.
    __property TipwIPPortDataInEvent OnDataIn = {read=FOnDataIn, write=FOnDataIn};
    //Fired when a connection is closed.
    __property TipwIPPortDisconnectedEvent OnDisconnected = {read=FOnDisconnected, write=FOnDisconnected};
    //Information about errors during data delivery.
    __property TipwIPPortErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired when IPPort is ready to send data.
    __property TipwIPPortReadyToSendEvent OnReadyToSend = {read=FOnReadyToSend, write=FOnReadyToSend};


}; //end class TipwIPPort

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _IPPORT_HPP_

