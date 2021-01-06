
#ifndef _IMAP_HPP_
#define _IMAP_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

enum TipwIMAPActions {
  imapIdle,
  imapNoop,
  imapConnect,
  imapDisconnect,
  imapSelectMailbox,
  imapExamineMailbox,
  imapCreateMailbox,
  imapDeleteMailbox,
  imapRenameMailbox,
  imapSearchMailbox,
  imapAppendToMailbox,
  imapCopyToMailbox,
  imapCheckMailbox,
  imapExpungeMailbox,
  imapCloseMailbox,
  imapListMailboxes,
  imapListSubscribedMailboxes,
  imapSubscribeMailbox,
  imapUnsubscribeMailbox,
  imapGetMessageInfo,
  imapGetMessageHeaders,
  imapGetMessageText,
  imapGetMessagePart,
  imapResetMessageFlags,
  imapSetMessageFlags,
  imapUnsetMessageFlags
};
typedef TFIREWALLTYPES TipwIMAPFirewallTypes;




typedef void __fastcall (__closure* TipwIMAPEndTransferEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwIMAPErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwIMAPMailboxListEvent)(System::TObject* Sender,
                                    AnsiString& Mailbox,
                                    AnsiString& Separator,
                                    AnsiString& Flags);
typedef void __fastcall (__closure* TipwIMAPMessageInfoEvent)(System::TObject* Sender,
                                    AnsiString& MessageId,
                                    AnsiString& Subject,
                                    AnsiString& MessageDate,
                                    AnsiString& From,
                                    AnsiString& Flags,
                                    long Size);
typedef void __fastcall (__closure* TipwIMAPMessagePartEvent)(System::TObject* Sender,
                                    AnsiString& PartId,
                                    long Size,
                                    AnsiString& ContentType,
                                    AnsiString& Filename,
                                    AnsiString& ContentEncoding,
                                    AnsiString& Parameters,
                                    AnsiString& MultipartMode);
typedef void __fastcall (__closure* TipwIMAPPITrailEvent)(System::TObject* Sender,
                                    int Direction,
                                    AnsiString& Message);
typedef void __fastcall (__closure* TipwIMAPStartTransferEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwIMAPTransferEvent)(System::TObject* Sender,
                                    long BytesTransferred,
                                    AnsiString& Text);


class PACKAGE TipwIMAP : public IPWCore
{
private:
  LONG reserved;
  TipwIMAPEndTransferEvent FOnEndTransfer;
  TipwIMAPErrorEvent FOnError;
  TipwIMAPMailboxListEvent FOnMailboxList;
  TipwIMAPMessageInfoEvent FOnMessageInfo;
  TipwIMAPMessagePartEvent FOnMessagePart;
  TipwIMAPPITrailEvent FOnPITrail;
  TipwIMAPStartTransferEvent FOnStartTransfer;
  TipwIMAPTransferEvent FOnTransfer;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //Can be used to send additional commands directly to the IMAP server.  //

  void __fastcall FSetCommand(AnsiString lpszCommand);

  //Shows whether the component is connected.  //
  bool __fastcall FConnected();


  //The byte index where to end the transfer.  //
  long __fastcall FEndByte();
  void __fastcall FSetEndByte(long lEndByte);

  //Used to send other data to firewall.  //
  AnsiString __fastcall FFirewallData();
  void __fastcall FSetFirewallData(AnsiString lpFirewallData);
  void __fastcall SetFirewallData(char *lpFirewallData, USHORT lenFirewallData);


  //Defined flags in the selected mailbox.  //
  AnsiString __fastcall FMailboxFlags();


  //The port of the IMAP server (default is 143).  //
  USHORT __fastcall FMailPort();
  void __fastcall FSetMailPort(USHORT lMailPort);

  //Array property with the list of BCc recipients of the message.  //
  AnsiString __fastcall FMessageBCc(USHORT AddressIndex);


  //Array property with the list of Cc recipients of the message.  //
  AnsiString __fastcall FMessageCc(USHORT AddressIndex);


  //The ContentEncoding of the selected message.  //
  AnsiString __fastcall FMessageContentEncoding();


  //The ContentType of the message.  //
  AnsiString __fastcall FMessageContentType();


  //The time the message was created.  //
  AnsiString __fastcall FMessageDate();


  //The time the message was delivered to the mail server.  //
  AnsiString __fastcall FMessageDeliveryTime();


  //Flags of the current message.  //
  AnsiString __fastcall FMessageFlags();
  void __fastcall FSetMessageFlags(AnsiString lpszMessageFlags);

  //The address of the author of the message.  //
  AnsiString __fastcall FMessageFrom();


  //RFC822-encoded headers of the message.  //
  AnsiString __fastcall FMessageHeaders();
  void __fastcall FSetMessageHeaders(AnsiString lpszMessageHeaders);

  //The message id of the current message.  //
  AnsiString __fastcall FMessageId();


  //The unique message ID of the message this one is in reply to.  //
  AnsiString __fastcall FMessageInReplyTo();


  //The globally unique id of the message.  //
  AnsiString __fastcall FMessageNetId();


  //Email address(s) where replies to the message should be sent.  //
  AnsiString __fastcall FMessageReplyTo();


  //The address of the sender of the message.  //
  AnsiString __fastcall FMessageSender();


  //The size of the selected message.  //
  long __fastcall FMessageSize();


  //The subject of the message.  //
  AnsiString __fastcall FMessageSubject();


  //The body of the retrieved message  //
  AnsiString __fastcall FMessageText();
  void __fastcall FSetMessageText(AnsiString lpszMessageText);

  //Array property with the list of direct recipients of the message.  //
  AnsiString __fastcall FMessageTo(USHORT AddressIndex);


  //The new name of the mailbox during an imapRenameMailbox operation.  //
  AnsiString __fastcall FNewMailbox();
  void __fastcall FSetNewMailbox(AnsiString lpszNewMailbox);

  //The PartId of the part to retrieve.  //
  AnsiString __fastcall FPartId();
  void __fastcall FSetPartId(AnsiString lpszPartId);

  //When set to True, the message Seen flag is not changed during reading.  //
  bool __fastcall FPeekMode();
  void __fastcall FSetPeekMode(bool bPeekMode);

  //The handle of the main socket used by the component.  //
  long __fastcall FSocketHandle();


  //The byte index where to start the transfer from.  //
  long __fastcall FStartByte();
  void __fastcall FSetStartByte(long lStartByte);

  //If true, permanent message id-s are used instead of the default temporary id-s.  //
  bool __fastcall FUIDMode();
  void __fastcall FSetUIDMode(bool bUIDMode);

  //Size in bytes of the largest UDP datagram that can be sent or received (Windows only).  //
  USHORT __fastcall FWinsockMaxDatagramSize();


  //Maximum number of sockets available to a single process (Windows only).  //
  USHORT __fastcall FWinsockMaxSockets();


  //The path to the Winsock DLL used (Windows only).  //
  AnsiString __fastcall FWinsockPath();
  void __fastcall FSetWinsockPath(AnsiString lpszWinsockPath);



  //Design-Time Properties
  TipwIMAPActions __fastcall FAction();
  void __fastcall FSetAction(TipwIMAPActions iAction);









  AnsiString __fastcall FFirewallHost();
  void __fastcall FSetFirewallHost(AnsiString lpszFirewallHost);

  AnsiString __fastcall FFirewallPassword();
  void __fastcall FSetFirewallPassword(AnsiString lpszFirewallPassword);

  USHORT __fastcall FFirewallPort();
  void __fastcall FSetFirewallPort(USHORT usFirewallPort);

  TipwIMAPFirewallTypes __fastcall FFirewallType();
  void __fastcall FSetFirewallType(TipwIMAPFirewallTypes iFirewallType);

  AnsiString __fastcall FFirewallUser();
  void __fastcall FSetFirewallUser(AnsiString lpszFirewallUser);

  AnsiString __fastcall FLastReply();


  AnsiString __fastcall FLocalFile();
  void __fastcall FSetLocalFile(AnsiString lpszLocalFile);

  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);

  AnsiString __fastcall FMailbox();
  void __fastcall FSetMailbox(AnsiString lpszMailbox);





  AnsiString __fastcall FMailServer();
  void __fastcall FSetMailServer(AnsiString lpszMailServer);









  int __fastcall FMessageCount();






















  AnsiString __fastcall FMessageSet();
  void __fastcall FSetMessageSet(AnsiString lpszMessageSet);













  AnsiString __fastcall FPassword();
  void __fastcall FSetPassword(AnsiString lpszPassword);



  int __fastcall FRecentMessageCount();


  AnsiString __fastcall FSearchCriteria();
  void __fastcall FSetSearchCriteria(AnsiString lpszSearchCriteria);





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

  virtual __fastcall TipwIMAP(TComponent* Owner);
  virtual __fastcall TipwIMAP(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_31);
  virtual __fastcall ~TipwIMAP();


  //Fired when the message or the part data finishes transferring.  //
  virtual void FireEndTransfer();
  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired for each mailbox received through the various imapListMailbox actions.  //
  virtual void FireMailboxList(char* Mailbox, char* Separator, char* Flags);
  //Fired with information for the message(s) retrieved by the server.  //
  virtual void FireMessageInfo(char* MessageId, char* Subject, char* MessageDate, char* From, char* Flags, long Size);
  //Fired for each message part when an imapGetMessageInfo action is performed.  //
  virtual void FireMessagePart(char* PartId, long Size, char* ContentType, char* Filename, char* ContentEncoding, char* Parameters, char* MultipartMode);
  //Traces the commands sent to the mail server, and the respective replies.  //
  virtual void FirePITrail(int Direction, char* Message);
  //Fired when the message or the part data starts transferring.  //
  virtual void FireStartTransfer();
  //Fired while the message gets transferred from the MailServer .  //
  virtual void FireTransfer(long BytesTransferred, char* Text);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };



  __property AnsiString Command = {

               write=FSetCommand               };

  __property bool Connected = {
               read=FConnected
               };

  __property long EndByte = {
               read=FEndByte,
               write=FSetEndByte               };

  __property AnsiString FirewallData = {
               read=FFirewallData,
               write=FSetFirewallData               };



















  __property AnsiString MailboxFlags = {
               read=FMailboxFlags
               };

  __property USHORT MailPort = {
               read=FMailPort,
               write=FSetMailPort               };



  __property AnsiString MessageBCc[USHORT AddressIndex] = {
               read=FMessageBCc
               };

  __property AnsiString MessageCc[USHORT AddressIndex] = {
               read=FMessageCc
               };

  __property AnsiString MessageContentEncoding = {
               read=FMessageContentEncoding
               };

  __property AnsiString MessageContentType = {
               read=FMessageContentType
               };



  __property AnsiString MessageDate = {
               read=FMessageDate
               };

  __property AnsiString MessageDeliveryTime = {
               read=FMessageDeliveryTime
               };

  __property AnsiString MessageFlags = {
               read=FMessageFlags,
               write=FSetMessageFlags               };

  __property AnsiString MessageFrom = {
               read=FMessageFrom
               };

  __property AnsiString MessageHeaders = {
               read=FMessageHeaders,
               write=FSetMessageHeaders               };

  __property AnsiString MessageId = {
               read=FMessageId
               };

  __property AnsiString MessageInReplyTo = {
               read=FMessageInReplyTo
               };

  __property AnsiString MessageNetId = {
               read=FMessageNetId
               };

  __property AnsiString MessageReplyTo = {
               read=FMessageReplyTo
               };

  __property AnsiString MessageSender = {
               read=FMessageSender
               };



  __property long MessageSize = {
               read=FMessageSize
               };

  __property AnsiString MessageSubject = {
               read=FMessageSubject
               };

  __property AnsiString MessageText = {
               read=FMessageText,
               write=FSetMessageText               };

  __property AnsiString MessageTo[USHORT AddressIndex] = {
               read=FMessageTo
               };

  __property AnsiString NewMailbox = {
               read=FNewMailbox,
               write=FSetNewMailbox               };

  __property AnsiString PartId = {
               read=FPartId,
               write=FSetPartId               };



  __property bool PeekMode = {
               read=FPeekMode,
               write=FSetPeekMode               };





  __property long SocketHandle = {
               read=FSocketHandle
               };

  __property long StartByte = {
               read=FStartByte,
               write=FSetStartByte               };



  __property bool UIDMode = {
               read=FUIDMode,
               write=FSetUIDMode               };







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
    void __fastcall AddMessageFlags(AnsiString Flags);
    void __fastcall AppendToMailbox();
    void __fastcall CheckMailbox();
    void __fastcall CloseMailbox();
    void __fastcall Connect();
    void __fastcall CopyToMailbox();
    void __fastcall CreateMailbox();
    void __fastcall DeleteMailbox();
    void __fastcall Disconnect();
    void __fastcall DoEvents();
    void __fastcall ExamineMailbox();
    void __fastcall ExpungeMailbox();
    void __fastcall FetchMessageHeaders();
    void __fastcall FetchMessageInfo();
    void __fastcall FetchMessagePart();
    void __fastcall FetchMessageText();
    void __fastcall Interrupt();
    void __fastcall ListMailboxes();
    void __fastcall ListSubscribedMailboxes();
    void __fastcall Noop();
    void __fastcall RenameMailbox();
    void __fastcall ResetMessageFlags();
    void __fastcall SearchMailbox();
    void __fastcall SelectMailbox();
    void __fastcall SubscribeMailbox();
    void __fastcall UnsetMessageFlags();
    void __fastcall UnsubscribeMailbox();




__published:

  //PROPERTIES
    __property TipwIMAPActions Action = {
                    read=FAction,
                    write=FSetAction,
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
    __property TipwIMAPFirewallTypes FirewallType = {
                    read=FFirewallType,
                    write=FSetFirewallType,
                    default=fwNone
                   };
    __property AnsiString FirewallUser = {
                    read=FFirewallUser,
                    write=FSetFirewallUser,
                    
                   };
    __property AnsiString LastReply = {
                    read=FLastReply,
                    write=SetDummyAnsiString,
                    stored=false

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
    __property AnsiString Mailbox = {
                    read=FMailbox,
                    write=FSetMailbox,
                    
                   };


    __property AnsiString MailServer = {
                    read=FMailServer,
                    write=FSetMailServer,
                    
                   };




    __property int MessageCount = {
                    read=FMessageCount,
                    write=SetDummyint,
                    stored=false

                   };










    __property AnsiString MessageSet = {
                    read=FMessageSet,
                    write=FSetMessageSet,
                    
                   };






    __property AnsiString Password = {
                    read=FPassword,
                    write=FSetPassword,
                    
                   };

    __property int RecentMessageCount = {
                    read=FRecentMessageCount,
                    write=SetDummyint,
                    stored=false

                   };
    __property AnsiString SearchCriteria = {
                    read=FSearchCriteria,
                    write=FSetSearchCriteria,
                    
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
    //Fired when the message or the part data finishes transferring.
    __property TipwIMAPEndTransferEvent OnEndTransfer = {read=FOnEndTransfer, write=FOnEndTransfer};
    //Information about errors during data delivery.
    __property TipwIMAPErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired for each mailbox received through the various imapListMailbox actions.
    __property TipwIMAPMailboxListEvent OnMailboxList = {read=FOnMailboxList, write=FOnMailboxList};
    //Fired with information for the message(s) retrieved by the server.
    __property TipwIMAPMessageInfoEvent OnMessageInfo = {read=FOnMessageInfo, write=FOnMessageInfo};
    //Fired for each message part when an imapGetMessageInfo action is performed.
    __property TipwIMAPMessagePartEvent OnMessagePart = {read=FOnMessagePart, write=FOnMessagePart};
    //Traces the commands sent to the mail server, and the respective replies.
    __property TipwIMAPPITrailEvent OnPITrail = {read=FOnPITrail, write=FOnPITrail};
    //Fired when the message or the part data starts transferring.
    __property TipwIMAPStartTransferEvent OnStartTransfer = {read=FOnStartTransfer, write=FOnStartTransfer};
    //Fired while the message gets transferred from the MailServer .
    __property TipwIMAPTransferEvent OnTransfer = {read=FOnTransfer, write=FOnTransfer};


}; //end class TipwIMAP

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _IMAP_HPP_

