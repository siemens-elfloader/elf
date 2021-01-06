
#ifndef _REXEC_HPP_
#define _REXEC_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

typedef TFIREWALLTYPES TipwRexecFirewallTypes;




typedef void __fastcall (__closure* TipwRexecConnectedEvent)(System::TObject* Sender,
                                    int StatusCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwRexecDisconnectedEvent)(System::TObject* Sender,
                                    int StatusCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwRexecErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwRexecStderrEvent)(System::TObject* Sender,
                                    char * Text, USHORT lenText,
                                    bool EOL);
typedef void __fastcall (__closure* TipwRexecStdoutEvent)(System::TObject* Sender,
                                    char * Text, USHORT lenText,
                                    bool EOL);


class PACKAGE TipwRexec : public IPWCore
{
private:
  LONG reserved;
  TipwRexecConnectedEvent FOnConnected;
  TipwRexecDisconnectedEvent FOnDisconnected;
  TipwRexecErrorEvent FOnError;
  TipwRexecStderrEvent FOnStderr;
  TipwRexecStdoutEvent FOnStdout;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //The number of bytes actually sent after an assignment to Stdin.  //
  long __fastcall FBytesSent();


  //Shows whether the component is connected.  //
  bool __fastcall FConnected();


  //Used to break the stdout data stream into chunks separated by its value.  //
  AnsiString __fastcall FEOL();
  void __fastcall FSetEOL(AnsiString lpEOL);
  void __fastcall SetEOL(char *lpEOL, USHORT lenEOL);


  //Used to break the stderr data stream into chunks separated by its value.  //
  AnsiString __fastcall FErrEOL();
  void __fastcall FSetErrEOL(AnsiString lpErrEOL);
  void __fastcall SetErrEOL(char *lpErrEOL, USHORT lenErrEOL);


  //Used to send other data to firewall.  //
  AnsiString __fastcall FFirewallData();
  void __fastcall FSetFirewallData(AnsiString lpFirewallData);
  void __fastcall SetFirewallData(char *lpFirewallData, USHORT lenFirewallData);


  //The TCP port in the local host where the component binds.  //
  USHORT __fastcall FLocalPort();
  void __fastcall FSetLocalPort(USHORT usLocalPort);

  //The remote exec service port (default is 512).  //
  USHORT __fastcall FRemotePort();
  void __fastcall FSetRemotePort(USHORT usRemotePort);

  //The handle of the main socket used by the component.  //
  long __fastcall FSocketHandle();


  //The local port where the remote systems sends the stderr stream.  //
  USHORT __fastcall FStderrPort();
  void __fastcall FSetStderrPort(USHORT usStderrPort);

  //A string of data to be sent to the remote host while connected.  //

  void __fastcall FSetStdin(AnsiString lpStdin);
  void __fastcall SetStdin(char *lpStdin, USHORT lenStdin);


  //Size in bytes of the largest UDP datagram that can be sent or received (Windows only).  //
  USHORT __fastcall FWinsockMaxDatagramSize();


  //Maximum number of sockets available to a single process (Windows only).  //
  USHORT __fastcall FWinsockMaxSockets();


  //The path to the Winsock DLL used (Windows only).  //
  AnsiString __fastcall FWinsockPath();
  void __fastcall FSetWinsockPath(AnsiString lpszWinsockPath);



  //Design-Time Properties


  AnsiString __fastcall FCommand();
  void __fastcall FSetCommand(AnsiString lpszCommand);



  bool __fastcall FEnableStderr();
  void __fastcall FSetEnableStderr(bool bEnableStderr);





  AnsiString __fastcall FErrorMessage();




  AnsiString __fastcall FFirewallHost();
  void __fastcall FSetFirewallHost(AnsiString lpszFirewallHost);

  AnsiString __fastcall FFirewallPassword();
  void __fastcall FSetFirewallPassword(AnsiString lpszFirewallPassword);

  USHORT __fastcall FFirewallPort();
  void __fastcall FSetFirewallPort(USHORT usFirewallPort);

  TipwRexecFirewallTypes __fastcall FFirewallType();
  void __fastcall FSetFirewallType(TipwRexecFirewallTypes iFirewallType);

  AnsiString __fastcall FFirewallUser();
  void __fastcall FSetFirewallUser(AnsiString lpszFirewallUser);

  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);



  long __fastcall FMaxLineLength();
  void __fastcall FSetMaxLineLength(long lMaxLineLength);

  AnsiString __fastcall FRemoteHost();
  void __fastcall FSetRemoteHost(AnsiString lpszRemoteHost);

  AnsiString __fastcall FRemotePassword();
  void __fastcall FSetRemotePassword(AnsiString lpszRemotePassword);



  AnsiString __fastcall FRemoteUser();
  void __fastcall FSetRemoteUser(AnsiString lpszRemoteUser);







  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);

  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwRexec(TComponent* Owner);
  virtual __fastcall TipwRexec(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_22);
  virtual __fastcall ~TipwRexec();


  //Fired immediately after a connection completes (or fails).  //
  virtual void FireConnected(int StatusCode, char* Description);
  //Fired when a connection is closed.  //
  virtual void FireDisconnected(int StatusCode, char* Description);
  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired when data (complete lines) come in through stderr.  //
  virtual void FireStderr(char* Text, USHORT lenText, bool EOL);
  //Fired when data (complete lines) come in through stdout.  //
  virtual void FireStdout(char* Text, USHORT lenText, bool EOL);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };

  __property long BytesSent = {
               read=FBytesSent
               };



  __property bool Connected = {
               read=FConnected
               };



  __property AnsiString EOL = {
               read=FEOL,
               write=FSetEOL               };

  __property AnsiString ErrEOL = {
               read=FErrEOL,
               write=FSetErrEOL               };



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

  __property AnsiString Stdin = {

               write=FSetStdin               };







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
    void __fastcall Disconnect();
    void __fastcall DoEvents();
    void __fastcall Execute(AnsiString Command);
    void __fastcall Send(AnsiString Text);




__published:

  //PROPERTIES

    __property AnsiString Command = {
                    read=FCommand,
                    write=FSetCommand,
                    stored=false

                   };

    __property bool EnableStderr = {
                    read=FEnableStderr,
                    write=FSetEnableStderr,
                    default=true
                   };


    __property AnsiString ErrorMessage = {
                    read=FErrorMessage,
                    write=SetDummyAnsiString,
                    stored=false

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
    __property TipwRexecFirewallTypes FirewallType = {
                    read=FFirewallType,
                    write=FSetFirewallType,
                    default=fwNone
                   };
    __property AnsiString FirewallUser = {
                    read=FFirewallUser,
                    write=FSetFirewallUser,
                    
                   };
    __property AnsiString LocalHost = {
                    read=FLocalHost,
                    write=FSetLocalHost,
                    stored=false

                   };

    __property long MaxLineLength = {
                    read=FMaxLineLength,
                    write=FSetMaxLineLength,
                    default=2048
                   };
    __property AnsiString RemoteHost = {
                    read=FRemoteHost,
                    write=FSetRemoteHost,
                    
                   };
    __property AnsiString RemotePassword = {
                    read=FRemotePassword,
                    write=FSetRemotePassword,
                    
                   };

    __property AnsiString RemoteUser = {
                    read=FRemoteUser,
                    write=FSetRemoteUser,
                    
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
    __property TipwRexecConnectedEvent OnConnected = {read=FOnConnected, write=FOnConnected};
    //Fired when a connection is closed.
    __property TipwRexecDisconnectedEvent OnDisconnected = {read=FOnDisconnected, write=FOnDisconnected};
    //Information about errors during data delivery.
    __property TipwRexecErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired when data (complete lines) come in through stderr.
    __property TipwRexecStderrEvent OnStderr = {read=FOnStderr, write=FOnStderr};
    //Fired when data (complete lines) come in through stdout.
    __property TipwRexecStdoutEvent OnStdout = {read=FOnStdout, write=FOnStdout};


}; //end class TipwRexec

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _REXEC_HPP_

