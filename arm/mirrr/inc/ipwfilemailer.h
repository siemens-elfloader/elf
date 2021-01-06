
#ifndef _FILEMAILER_HPP_
#define _FILEMAILER_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

enum TipwFileMailerActions {
  filemailerIdle,
  filemailerSend
};
typedef TFIREWALLTYPES TipwFileMailerFirewallTypes;




typedef void __fastcall (__closure* TipwFileMailerEndTransferEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwFileMailerErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwFileMailerPITrailEvent)(System::TObject* Sender,
                                    int Direction,
                                    AnsiString& Message);
typedef void __fastcall (__closure* TipwFileMailerStartTransferEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwFileMailerTransferEvent)(System::TObject* Sender,
                                    long BytesTransferred);


class PACKAGE TipwFileMailer : public IPWCore
{
private:
  LONG reserved;
  TipwFileMailerEndTransferEvent FOnEndTransfer;
  TipwFileMailerErrorEvent FOnError;
  TipwFileMailerPITrailEvent FOnPITrail;
  TipwFileMailerStartTransferEvent FOnStartTransfer;
  TipwFileMailerTransferEvent FOnTransfer;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //The paths of files to attach to the message.  //
  AnsiString __fastcall FAttachments(USHORT AttachmentIndex);
  void __fastcall FSetAttachments(USHORT AttachmentIndex, AnsiString lpszAttachments);

  //Used to send other data to firewall.  //
  AnsiString __fastcall FFirewallData();
  void __fastcall FSetFirewallData(AnsiString lpFirewallData);
  void __fastcall SetFirewallData(char *lpFirewallData, USHORT lenFirewallData);


  //The server port for SMTP (default 25).  //
  USHORT __fastcall FMailPort();
  void __fastcall FSetMailPort(USHORT usMailPort);

  //Maximum length for headers to avoid line folding (default 80).  //
  int __fastcall FMaxHeaderLength();
  void __fastcall FSetMaxHeaderLength(int iMaxHeaderLength);

  //An RFC 822 compliant string consisting of extra headers.  //
  AnsiString __fastcall FOtherHeaders();
  void __fastcall FSetOtherHeaders(AnsiString lpszOtherHeaders);

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
  TipwFileMailerActions __fastcall FAction();
  void __fastcall FSetAction(TipwFileMailerActions iAction);

  int __fastcall FAttachmentCount();
  void __fastcall FSetAttachmentCount(int iAttachmentCount);



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

  TipwFileMailerFirewallTypes __fastcall FFirewallType();
  void __fastcall FSetFirewallType(TipwFileMailerFirewallTypes iFirewallType);

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

  virtual __fastcall TipwFileMailer(TComponent* Owner);
  virtual __fastcall TipwFileMailer(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_41);
  virtual __fastcall ~TipwFileMailer();


  //Fired when the message text completes transferring.  //
  virtual void FireEndTransfer();
  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
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





  __property AnsiString Attachments[USHORT AttachmentIndex] = {
               read=FAttachments,
               write=FSetAttachments               };







  __property AnsiString FirewallData = {
               read=FFirewallData,
               write=FSetFirewallData               };

















  __property USHORT MailPort = {
               read=FMailPort,
               write=FSetMailPort               };



  __property int MaxHeaderLength = {
               read=FMaxHeaderLength,
               write=FSetMaxHeaderLength               };





  __property AnsiString OtherHeaders = {
               read=FOtherHeaders,
               write=FSetOtherHeaders               };





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
    void __fastcall AddAttachment(AnsiString FileName);
    void __fastcall DoEvents();
    void __fastcall Interrupt();
    void __fastcall Send();




__published:

  //PROPERTIES
    __property TipwFileMailerActions Action = {
                    read=FAction,
                    write=FSetAction,
                    stored=false

                   };
    __property int AttachmentCount = {
                    read=FAttachmentCount,
                    write=FSetAttachmentCount,
                    default=0
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
    __property TipwFileMailerFirewallTypes FirewallType = {
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
    __property TipwFileMailerEndTransferEvent OnEndTransfer = {read=FOnEndTransfer, write=FOnEndTransfer};
    //Information about errors during data delivery.
    __property TipwFileMailerErrorEvent OnError = {read=FOnError, write=FOnError};
    //Traces the commands sent to the mail server, and the respective replies.
    __property TipwFileMailerPITrailEvent OnPITrail = {read=FOnPITrail, write=FOnPITrail};
    //Fired when the message text starts transferring.
    __property TipwFileMailerStartTransferEvent OnStartTransfer = {read=FOnStartTransfer, write=FOnStartTransfer};
    //Fired while the message text gets transferred to MailServer .
    __property TipwFileMailerTransferEvent OnTransfer = {read=FOnTransfer, write=FOnTransfer};


}; //end class TipwFileMailer

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _FILEMAILER_HPP_

