
#ifndef _RCP_HPP_
#define _RCP_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

enum TipwRCPActions {
  rcpIdle,
  rcpGetFile,
  rcpPutFile
};
typedef TFIREWALLTYPES TipwRCPFirewallTypes;

enum TipwRCPProtocols {
  protRexec,
  protRshell
};



typedef void __fastcall (__closure* TipwRCPConnectedEvent)(System::TObject* Sender,
                                    int StatusCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwRCPDisconnectedEvent)(System::TObject* Sender,
                                    int StatusCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwRCPErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwRCPProgressEvent)(System::TObject* Sender,
                                    int PercentDone);


class PACKAGE TipwRCP : public IPWCore
{
private:
  LONG reserved;
  TipwRCPConnectedEvent FOnConnected;
  TipwRCPDisconnectedEvent FOnDisconnected;
  TipwRCPErrorEvent FOnError;
  TipwRCPProgressEvent FOnProgress;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //Used to send other data to firewall.  //
  AnsiString __fastcall FFirewallData();
  void __fastcall FSetFirewallData(AnsiString lpFirewallData);
  void __fastcall SetFirewallData(char *lpFirewallData, USHORT lenFirewallData);


  //The TCP port in the local host where the component binds.  //
  USHORT __fastcall FLocalPort();
  void __fastcall FSetLocalPort(USHORT usLocalPort);

  //The port for the service (REXEC or RSHELL).  //
  USHORT __fastcall FRemotePort();
  void __fastcall FSetRemotePort(USHORT usRemotePort);

  //The handle of the main socket used by the component.  //
  long __fastcall FSocketHandle();


  //The local port where the remote systems sends the stderr stream.  //
  USHORT __fastcall FStderrPort();
  void __fastcall FSetStderrPort(USHORT usStderrPort);

  //Size in bytes of the largest UDP datagram that can be sent or received (Windows only).  //
  USHORT __fastcall FWinsockMaxDatagramSize();


  //Maximum number of sockets available to a single process (Windows only).  //
  USHORT __fastcall FWinsockMaxSockets();


  //The path to the Winsock DLL used (Windows only).  //
  AnsiString __fastcall FWinsockPath();
  void __fastcall FSetWinsockPath(AnsiString lpszWinsockPath);



  //Design-Time Properties
  TipwRCPActions __fastcall FAction();
  void __fastcall FSetAction(TipwRCPActions iAction);

  bool __fastcall FEnableStderr();
  void __fastcall FSetEnableStderr(bool bEnableStderr);

  AnsiString __fastcall FFileMode();
  void __fastcall FSetFileMode(AnsiString lpszFileMode);



  AnsiString __fastcall FFirewallHost();
  void __fastcall FSetFirewallHost(AnsiString lpszFirewallHost);

  AnsiString __fastcall FFirewallPassword();
  void __fastcall FSetFirewallPassword(AnsiString lpszFirewallPassword);

  USHORT __fastcall FFirewallPort();
  void __fastcall FSetFirewallPort(USHORT usFirewallPort);

  TipwRCPFirewallTypes __fastcall FFirewallType();
  void __fastcall FSetFirewallType(TipwRCPFirewallTypes iFirewallType);

  AnsiString __fastcall FFirewallUser();
  void __fastcall FSetFirewallUser(AnsiString lpszFirewallUser);

  AnsiString __fastcall FLocalFile();
  void __fastcall FSetLocalFile(AnsiString lpszLocalFile);

  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);



  AnsiString __fastcall FPassword();
  void __fastcall FSetPassword(AnsiString lpszPassword);

  TipwRCPProtocols __fastcall FProtocol();
  void __fastcall FSetProtocol(TipwRCPProtocols iProtocol);

  AnsiString __fastcall FRemoteFile();
  void __fastcall FSetRemoteFile(AnsiString lpszRemoteFile);

  AnsiString __fastcall FRemoteHost();
  void __fastcall FSetRemoteHost(AnsiString lpszRemoteHost);







  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);

  AnsiString __fastcall FUser();
  void __fastcall FSetUser(AnsiString lpszUser);

  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwRCP(TComponent* Owner);
  virtual __fastcall TipwRCP(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_45);
  virtual __fastcall ~TipwRCP();


  //Fired immediately after a connection completes (or fails).  //
  virtual void FireConnected(int StatusCode, char* Description);
  //Fired when a connection is closed.  //
  virtual void FireDisconnected(int StatusCode, char* Description);
  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired whenever data is being transferred between the localhost and RemoteHost .  //
  virtual void FireProgress(int PercentDone);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };







  __property AnsiString FirewallData = {
               read=FFirewallData,
               write=FSetFirewallData               };















  __property USHORT LocalPort = {
               read=FLocalPort,
               write=FSetLocalPort               };









  __property USHORT RemotePort = {
               read=FRemotePort,
               write=FSetRemotePort               };

  __property long SocketHandle = {
               read=FSocketHandle
               };

  __property USHORT StderrPort = {
               read=FStderrPort,
               write=FSetStderrPort               };









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
    void __fastcall GetFile();
    void __fastcall Interrupt();
    void __fastcall PutFile();




__published:

  //PROPERTIES
    __property TipwRCPActions Action = {
                    read=FAction,
                    write=FSetAction,
                    stored=false

                   };
    __property bool EnableStderr = {
                    read=FEnableStderr,
                    write=FSetEnableStderr,
                    default=true
                   };
    __property AnsiString FileMode = {
                    read=FFileMode,
                    write=FSetFileMode,
                    
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
    __property TipwRCPFirewallTypes FirewallType = {
                    read=FFirewallType,
                    write=FSetFirewallType,
                    default=fwNone
                   };
    __property AnsiString FirewallUser = {
                    read=FFirewallUser,
                    write=FSetFirewallUser,
                    
                   };
    __property AnsiString LocalFile = {
                    read=FLocalFile,
                    write=FSetLocalFile,
                    
                   };
    __property AnsiString LocalHost = {
                    read=FLocalHost,
                    write=FSetLocalHost,
                    stored=false

                   };

    __property AnsiString Password = {
                    read=FPassword,
                    write=FSetPassword,
                    
                   };
    __property TipwRCPProtocols Protocol = {
                    read=FProtocol,
                    write=FSetProtocol,
                    default=protRexec
                   };
    __property AnsiString RemoteFile = {
                    read=FRemoteFile,
                    write=FSetRemoteFile,
                    
                   };
    __property AnsiString RemoteHost = {
                    read=FRemoteHost,
                    write=FSetRemoteHost,
                    
                   };



    __property int Timeout = {
                    read=FTimeout,
                    write=FSetTimeout,
                    default=0
                   };
    __property AnsiString User = {
                    read=FUser,
                    write=FSetUser,
                    
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
    __property TipwRCPConnectedEvent OnConnected = {read=FOnConnected, write=FOnConnected};
    //Fired when a connection is closed.
    __property TipwRCPDisconnectedEvent OnDisconnected = {read=FOnDisconnected, write=FOnDisconnected};
    //Information about errors during data delivery.
    __property TipwRCPErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired whenever data is being transferred between the localhost and RemoteHost .
    __property TipwRCPProgressEvent OnProgress = {read=FOnProgress, write=FOnProgress};


}; //end class TipwRCP

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _RCP_HPP_

