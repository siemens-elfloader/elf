
#ifndef _TELNET_HPP_
#define _TELNET_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

typedef TFIREWALLTYPES TipwTelnetFirewallTypes;




typedef void __fastcall (__closure* TipwTelnetCommandEvent)(System::TObject* Sender,
                                    int CommandCode);
typedef void __fastcall (__closure* TipwTelnetConnectedEvent)(System::TObject* Sender,
                                    int StatusCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwTelnetDataInEvent)(System::TObject* Sender,
                                    char * Text, USHORT lenText);
typedef void __fastcall (__closure* TipwTelnetDisconnectedEvent)(System::TObject* Sender,
                                    int StatusCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwTelnetDoEvent)(System::TObject* Sender,
                                    int OptionCode);
typedef void __fastcall (__closure* TipwTelnetDontEvent)(System::TObject* Sender,
                                    int OptionCode);
typedef void __fastcall (__closure* TipwTelnetErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwTelnetReadyToSendEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwTelnetSubOptionEvent)(System::TObject* Sender,
                                    char * SubOption, USHORT lenSubOption);
typedef void __fastcall (__closure* TipwTelnetWillEvent)(System::TObject* Sender,
                                    int OptionCode);
typedef void __fastcall (__closure* TipwTelnetWontEvent)(System::TObject* Sender,
                                    int OptionCode);


class PACKAGE TipwTelnet : public IPWCore
{
private:
  LONG reserved;
  TipwTelnetCommandEvent FOnCommand;
  TipwTelnetConnectedEvent FOnConnected;
  TipwTelnetDataInEvent FOnDataIn;
  TipwTelnetDisconnectedEvent FOnDisconnected;
  TipwTelnetDoEvent FOnDo;
  TipwTelnetDontEvent FOnDont;
  TipwTelnetErrorEvent FOnError;
  TipwTelnetReadyToSendEvent FOnReadyToSend;
  TipwTelnetSubOptionEvent FOnSubOption;
  TipwTelnetWillEvent FOnWill;
  TipwTelnetWontEvent FOnWont;


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


  //A single character Telnet command code to be sent to the server.  //

  void __fastcall FSetCommand(int iCommand);

  //Triggers a connection or disconnection.  Action property.  //
  bool __fastcall FConnected();
  void __fastcall FSetConnected(bool bConnected);

  //A string of data to be sent to the remote host.  //

  void __fastcall FSetDataToSend(AnsiString lpDataToSend);
  void __fastcall SetDataToSend(char *lpDataToSend, USHORT lenDataToSend);


  //A single character Telnet option code to be sent to the server with the Telnet DONT command.  //

  void __fastcall FSetDontOption(int iDontOption);

  //A single character Telnet option code to be sent to the server with the Telnet DO command.  //

  void __fastcall FSetDoOption(int iDoOption);

  //A Telnet suboption to send to the server with the suboption command.  //

  void __fastcall FSetDoSubOption(AnsiString lpDoSubOption);
  void __fastcall SetDoSubOption(char *lpDoSubOption, USHORT lenDoSubOption);


  //Used to send other data to firewall.  //
  AnsiString __fastcall FFirewallData();
  void __fastcall FSetFirewallData(AnsiString lpFirewallData);
  void __fastcall SetFirewallData(char *lpFirewallData, USHORT lenFirewallData);


  //The Telnet port in the remote host (default is 23).  //
  USHORT __fastcall FRemotePort();
  void __fastcall FSetRemotePort(USHORT usRemotePort);

  //The handle of the main socket used by the component.  //
  long __fastcall FSocketHandle();


  //A string of data to be sent urgently (out-of-band) to the remote host.  //

  void __fastcall FSetUrgentData(AnsiString lpUrgentData);
  void __fastcall SetUrgentData(char *lpUrgentData, USHORT lenUrgentData);


  //A single character Telnet option code to be sent to the server with the Telnet WILL command.  //

  void __fastcall FSetWillOption(int iWillOption);

  //Size in bytes of the largest UDP datagram that can be sent or received (Windows only).  //
  USHORT __fastcall FWinsockMaxDatagramSize();


  //Maximum number of sockets available to a single process (Windows only).  //
  USHORT __fastcall FWinsockMaxSockets();


  //The path to the Winsock DLL used (Windows only).  //
  AnsiString __fastcall FWinsockPath();
  void __fastcall FSetWinsockPath(AnsiString lpszWinsockPath);

  //A single character Telnet option code to be sent to the server with the Telnet WONT command.  //

  void __fastcall FSetWontOption(int iWontOption);



  //Design-Time Properties


















  AnsiString __fastcall FFirewallHost();
  void __fastcall FSetFirewallHost(AnsiString lpszFirewallHost);

  AnsiString __fastcall FFirewallPassword();
  void __fastcall FSetFirewallPassword(AnsiString lpszFirewallPassword);

  USHORT __fastcall FFirewallPort();
  void __fastcall FSetFirewallPort(USHORT usFirewallPort);

  TipwTelnetFirewallTypes __fastcall FFirewallType();
  void __fastcall FSetFirewallType(TipwTelnetFirewallTypes iFirewallType);

  AnsiString __fastcall FFirewallUser();
  void __fastcall FSetFirewallUser(AnsiString lpszFirewallUser);

  bool __fastcall FKeepAlive();
  void __fastcall FSetKeepAlive(bool bKeepAlive);

  bool __fastcall FLinger();
  void __fastcall FSetLinger(bool bLinger);

  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);

  USHORT __fastcall FLocalPort();
  void __fastcall FSetLocalPort(USHORT usLocalPort);

  AnsiString __fastcall FRemoteHost();
  void __fastcall FSetRemoteHost(AnsiString lpszRemoteHost);





  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);

  bool __fastcall FTransparent();
  void __fastcall FSetTransparent(bool bTransparent);





  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();





  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwTelnet(TComponent* Owner);
  virtual __fastcall TipwTelnet(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_19);
  virtual __fastcall ~TipwTelnet();


  //Fired when a Telnet command comes from the Telnet server.  //
  virtual void FireCommand(int CommandCode);
  //Fired immediately after a connection completes (or fails).  //
  virtual void FireConnected(int StatusCode, char* Description);
  //Fired when data is received from the remote host.  //
  virtual void FireDataIn(char* Text, USHORT lenText);
  //Fired when a connection is closed.  //
  virtual void FireDisconnected(int StatusCode, char* Description);
  //Fired when a Telnet DO OPTION command comes from the Telnet server.  //
  virtual void FireDo(int OptionCode);
  //Fired when a Telnet DONT OPTION command comes from the Telnet server.  //
  virtual void FireDont(int OptionCode);
  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired when the component is ready to send data.  //
  virtual void FireReadyToSend();
  //Fired when a Telnet suboption command comes from the Telnet server.  //
  virtual void FireSubOption(char* SubOption, USHORT lenSubOption);
  //Fired when a Telnet WILL OPTION command comes from the Telnet server.  //
  virtual void FireWill(int OptionCode);
  //Fired when a Telnet WONT OPTION command comes from the Telnet server.  //
  virtual void FireWont(int OptionCode);



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

  __property int Command = {

               write=FSetCommand               };

  __property bool Connected = {
               read=FConnected,
               write=FSetConnected               };

  __property AnsiString DataToSend = {

               write=FSetDataToSend               };

  __property int DontOption = {

               write=FSetDontOption               };

  __property int DoOption = {

               write=FSetDoOption               };

  __property AnsiString DoSubOption = {

               write=FSetDoSubOption               };

  __property AnsiString FirewallData = {
               read=FFirewallData,
               write=FSetFirewallData               };





















  __property USHORT RemotePort = {
               read=FRemotePort,
               write=FSetRemotePort               };

  __property long SocketHandle = {
               read=FSocketHandle
               };





  __property AnsiString UrgentData = {

               write=FSetUrgentData               };

  __property int WillOption = {

               write=FSetWillOption               };





  __property USHORT WinsockMaxDatagramSize = {
               read=FWinsockMaxDatagramSize
               };

  __property USHORT WinsockMaxSockets = {
               read=FWinsockMaxSockets
               };

  __property AnsiString WinsockPath = {
               read=FWinsockPath,
               write=FSetWinsockPath               };



  __property int WontOption = {

               write=FSetWontOption               };



  //METHODS
    void __fastcall Connect(AnsiString Host);
    void __fastcall Disconnect();
    void __fastcall DoEvents();
    void __fastcall Send(AnsiString Text);




__published:

  //PROPERTIES









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
    __property TipwTelnetFirewallTypes FirewallType = {
                    read=FFirewallType,
                    write=FSetFirewallType,
                    default=fwNone
                   };
    __property AnsiString FirewallUser = {
                    read=FFirewallUser,
                    write=FSetFirewallUser,
                    
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
    __property AnsiString RemoteHost = {
                    read=FRemoteHost,
                    write=FSetRemoteHost,
                    
                   };


    __property int Timeout = {
                    read=FTimeout,
                    write=FSetTimeout,
                    default=0
                   };
    __property bool Transparent = {
                    read=FTransparent,
                    write=FSetTransparent,
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
    //Fired when a Telnet command comes from the Telnet server.
    __property TipwTelnetCommandEvent OnCommand = {read=FOnCommand, write=FOnCommand};
    //Fired immediately after a connection completes (or fails).
    __property TipwTelnetConnectedEvent OnConnected = {read=FOnConnected, write=FOnConnected};
    //Fired when data is received from the remote host.
    __property TipwTelnetDataInEvent OnDataIn = {read=FOnDataIn, write=FOnDataIn};
    //Fired when a connection is closed.
    __property TipwTelnetDisconnectedEvent OnDisconnected = {read=FOnDisconnected, write=FOnDisconnected};
    //Fired when a Telnet DO OPTION command comes from the Telnet server.
    __property TipwTelnetDoEvent OnDo = {read=FOnDo, write=FOnDo};
    //Fired when a Telnet DONT OPTION command comes from the Telnet server.
    __property TipwTelnetDontEvent OnDont = {read=FOnDont, write=FOnDont};
    //Information about errors during data delivery.
    __property TipwTelnetErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired when the component is ready to send data.
    __property TipwTelnetReadyToSendEvent OnReadyToSend = {read=FOnReadyToSend, write=FOnReadyToSend};
    //Fired when a Telnet suboption command comes from the Telnet server.
    __property TipwTelnetSubOptionEvent OnSubOption = {read=FOnSubOption, write=FOnSubOption};
    //Fired when a Telnet WILL OPTION command comes from the Telnet server.
    __property TipwTelnetWillEvent OnWill = {read=FOnWill, write=FOnWill};
    //Fired when a Telnet WONT OPTION command comes from the Telnet server.
    __property TipwTelnetWontEvent OnWont = {read=FOnWont, write=FOnWont};


}; //end class TipwTelnet

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _TELNET_HPP_

