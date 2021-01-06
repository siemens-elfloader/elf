
#ifndef _SMTP_HPP_
#define _SMTP_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

enum TipwSMTPActions {
  smtpIdle,
  smtpConnect,
  smtpDisconnect,
  smtpSend,
  smtpResetHeaders,
  smtpExpand,
  smtpVerify,
  smtpSendToTerminalAndEmail,
  smtpSendToTerminalOrEmail,
  smtpSendToTerminalOnly
};
typedef TFIREWALLTYPES TipwSMTPFirewallTypes;




typedef void __fastcall (__closure* TipwSMTPEndTransferEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwSMTPErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwSMTPExpandEvent)(System::TObject* Sender,
                                    AnsiString& Address);
typedef void __fastcall (__closure* TipwSMTPPITrailEvent)(System::TObject* Sender,
                                    int Direction,
                                    AnsiString& Message);
typedef void __fastcall (__closure* TipwSMTPStartTransferEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwSMTPTransferEvent)(System::TObject* Sender,
                                    long BytesTransferred);


class PACKAGE TipwSMTP : public IPWCore
{
private:
  LONG reserved;
  TipwSMTPEndTransferEvent FOnEndTransfer;
  TipwSMTPErrorEvent FOnError;
  TipwSMTPExpandEvent FOnExpand;
  TipwSMTPPITrailEvent FOnPITrail;
  TipwSMTPStartTransferEvent FOnStartTransfer;
  TipwSMTPTransferEvent FOnTransfer;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //A switch allowing the component to use ESMTP features (SMTP extensions).  //
  bool __fastcall FAllowExtensions();
  void __fastcall FSetAllowExtensions(bool bAllowExtensions);

  //A file to append to MessageText when sending mail.  //
  AnsiString __fastcall FAttachedFile();
  void __fastcall FSetAttachedFile(AnsiString lpszAttachedFile);

  //Can be used to send additional commands directly to the SMTP server.  //

  void __fastcall FSetCommand(AnsiString lpszCommand);

  //Shows whether the component is connected.  //
  bool __fastcall FConnected();


  //Used to send other data to firewall.  //
  AnsiString __fastcall FFirewallData();
  void __fastcall FSetFirewallData(AnsiString lpFirewallData);
  void __fastcall SetFirewallData(char *lpFirewallData, USHORT lenFirewallData);


  //The argument for HELO (herald) command to the server (defaults to local host name).  //
  AnsiString __fastcall FHello();
  void __fastcall FSetHello(AnsiString lpszHello);

  //The server port for SMTP (default 25).  //
  USHORT __fastcall FMailPort();
  void __fastcall FSetMailPort(USHORT usMailPort);

  //Maximum length for headers to avoid line folding (default 80).  //
  int __fastcall FMaxHeaderLength();
  void __fastcall FSetMaxHeaderLength(int iMaxHeaderLength);

  //An RFC 822 compliant string consisting of extra headers.  //
  AnsiString __fastcall FOtherHeaders();
  void __fastcall FSetOtherHeaders(AnsiString lpszOtherHeaders);

  //A login password to login with in the MailServer .  //
  AnsiString __fastcall FPassword();
  void __fastcall FSetPassword(AnsiString lpszPassword);

  //The handle of the main socket used by the component.  //
  long __fastcall FSocketHandle();


  //A user id to login as in the MailServer .  //
  AnsiString __fastcall FUser();
  void __fastcall FSetUser(AnsiString lpszUser);

  //Size in bytes of the largest UDP datagram that can be sent or received (Windows only).  //
  USHORT __fastcall FWinsockMaxDatagramSize();


  //Maximum number of sockets available to a single process (Windows only).  //
  USHORT __fastcall FWinsockMaxSockets();


  //The path to the Winsock DLL used (Windows only).  //
  AnsiString __fastcall FWinsockPath();
  void __fastcall FSetWinsockPath(AnsiString lpszWinsockPath);



  //Design-Time Properties
  TipwSMTPActions __fastcall FAction();
  void __fastcall FSetAction(TipwSMTPActions iAction);





  AnsiString __fastcall FBCc();
  void __fastcall FSetBCc(AnsiString lpszBCc);

  AnsiString __fastcall FCc();
  void __fastcall FSetCc(AnsiString lpszCc);





  AnsiString __fastcall FDate();
  void __fastcall FSetDate(AnsiString lpszDate);



  AnsiString __fastcall FFirewallHost();
  void __fastcall FSetFirewallHost(AnsiString lpszFirewallHost);

  AnsiString __fastcall FFirewallPassword();
  void __fastcall FSetFirewallPassword(AnsiString lpszFirewallPassword);

  USHORT __fastcall FFirewallPort();
  void __fastcall FSetFirewallPort(USHORT usFirewallPort);

  TipwSMTPFirewallTypes __fastcall FFirewallType();
  void __fastcall FSetFirewallType(TipwSMTPFirewallTypes iFirewallType);

  AnsiString __fastcall FFirewallUser();
  void __fastcall FSetFirewallUser(AnsiString lpszFirewallUser);

  AnsiString __fastcall FFrom();
  void __fastcall FSetFrom(AnsiString lpszFrom);



  AnsiString __fastcall FLastReply();


  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);



  AnsiString __fastcall FMailServer();
  void __fastcall FSetMailServer(AnsiString lpszMailServer);



  AnsiString __fastcall FMessageDate();
  void __fastcall FSetMessageDate(AnsiString lpszMessageDate);

  AnsiString __fastcall FMessageText();
  void __fastcall FSetMessageText(AnsiString lpszMessageText);





  AnsiString __fastcall FReplyTo();
  void __fastcall FSetReplyTo(AnsiString lpszReplyTo);

  AnsiString __fastcall FSendTo();
  void __fastcall FSetSendTo(AnsiString lpszSendTo);



  AnsiString __fastcall FSubject();
  void __fastcall FSetSubject(AnsiString lpszSubject);

  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);



  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwSMTP(TComponent* Owner);
  virtual __fastcall TipwSMTP(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_23);
  virtual __fastcall ~TipwSMTP();


  //Fired when the message text completes transferring.  //
  virtual void FireEndTransfer();
  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired for every email address returned by the server when Action is set to Expand .  //
  virtual void FireExpand(char* Address);
  //Traces the commands sent to the mail server, and the respective replies.  //
  virtual void FirePITrail(int Direction, char* Message);
  //Fired when the message text starts transferring.  //
  virtual void FireStartTransfer();
  //Fired while the message text gets transferred to MailServer .  //
  virtual void FireTransfer(long BytesTransferred);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };



  __property bool AllowExtensions = {
               read=FAllowExtensions,
               write=FSetAllowExtensions               };

  __property AnsiString AttachedFile = {
               read=FAttachedFile,
               write=FSetAttachedFile               };





  __property AnsiString Command = {

               write=FSetCommand               };

  __property bool Connected = {
               read=FConnected
               };



  __property AnsiString FirewallData = {
               read=FFirewallData,
               write=FSetFirewallData               };













  __property AnsiString Hello = {
               read=FHello,
               write=FSetHello               };





  __property USHORT MailPort = {
               read=FMailPort,
               write=FSetMailPort               };



  __property int MaxHeaderLength = {
               read=FMaxHeaderLength,
               write=FSetMaxHeaderLength               };





  __property AnsiString OtherHeaders = {
               read=FOtherHeaders,
               write=FSetOtherHeaders               };

  __property AnsiString Password = {
               read=FPassword,
               write=FSetPassword               };





  __property long SocketHandle = {
               read=FSocketHandle
               };





  __property AnsiString User = {
               read=FUser,
               write=FSetUser               };





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
    void __fastcall Connect();
    void __fastcall Disconnect();
    void __fastcall DoEvents();
    void __fastcall Expand(AnsiString EmailAddress);
    void __fastcall Interrupt();
    void __fastcall ResetHeaders();
    void __fastcall Send();
    void __fastcall SendToTerminalAndEmail();
    void __fastcall SendToTerminalOnly();
    void __fastcall SendToTerminalOrEmail();
    void __fastcall Verify(AnsiString EmailAddress);




__published:

  //PROPERTIES
    __property TipwSMTPActions Action = {
                    read=FAction,
                    write=FSetAction,
                    stored=false

                   };


    __property AnsiString BCc = {
                    read=FBCc,
                    write=FSetBCc,
                    
                   };
    __property AnsiString Cc = {
                    read=FCc,
                    write=FSetCc,
                    
                   };


    __property AnsiString Date = {
                    read=FDate,
                    write=FSetDate,
                    
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
    __property TipwSMTPFirewallTypes FirewallType = {
                    read=FFirewallType,
                    write=FSetFirewallType,
                    default=fwNone
                   };
    __property AnsiString FirewallUser = {
                    read=FFirewallUser,
                    write=FSetFirewallUser,
                    
                   };
    __property AnsiString From = {
                    read=FFrom,
                    write=FSetFrom,
                    
                   };

    __property AnsiString LastReply = {
                    read=FLastReply,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString LocalHost = {
                    read=FLocalHost,
                    write=FSetLocalHost,
                    stored=false

                   };

    __property AnsiString MailServer = {
                    read=FMailServer,
                    write=FSetMailServer,
                    
                   };

    __property AnsiString MessageDate = {
                    read=FMessageDate,
                    write=FSetMessageDate,
                    
                   };
    __property AnsiString MessageText = {
                    read=FMessageText,
                    write=FSetMessageText,
                    
                   };


    __property AnsiString ReplyTo = {
                    read=FReplyTo,
                    write=FSetReplyTo,
                    
                   };
    __property AnsiString SendTo = {
                    read=FSendTo,
                    write=FSetSendTo,
                    
                   };

    __property AnsiString Subject = {
                    read=FSubject,
                    write=FSetSubject,
                    
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
    //Fired when the message text completes transferring.
    __property TipwSMTPEndTransferEvent OnEndTransfer = {read=FOnEndTransfer, write=FOnEndTransfer};
    //Information about errors during data delivery.
    __property TipwSMTPErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired for every email address returned by the server when Action is set to Expand .
    __property TipwSMTPExpandEvent OnExpand = {read=FOnExpand, write=FOnExpand};
    //Traces the commands sent to the mail server, and the respective replies.
    __property TipwSMTPPITrailEvent OnPITrail = {read=FOnPITrail, write=FOnPITrail};
    //Fired when the message text starts transferring.
    __property TipwSMTPStartTransferEvent OnStartTransfer = {read=FOnStartTransfer, write=FOnStartTransfer};
    //Fired while the message text gets transferred to MailServer .
    __property TipwSMTPTransferEvent OnTransfer = {read=FOnTransfer, write=FOnTransfer};


}; //end class TipwSMTP

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _SMTP_HPP_

