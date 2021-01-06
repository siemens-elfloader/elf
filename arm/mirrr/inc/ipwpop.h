
#ifndef _POP_HPP_
#define _POP_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

enum TipwPOPActions {
  popIdle,
  popConnect,
  popDisconnect,
  popRetrieve,
  popDelete,
  popReset
};
typedef TFIREWALLTYPES TipwPOPFirewallTypes;




typedef void __fastcall (__closure* TipwPOPEndTransferEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwPOPErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwPOPHeaderEvent)(System::TObject* Sender,
                                    AnsiString& Field,
                                    AnsiString& Value);
typedef void __fastcall (__closure* TipwPOPPITrailEvent)(System::TObject* Sender,
                                    int Direction,
                                    AnsiString& Message);
typedef void __fastcall (__closure* TipwPOPStartTransferEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwPOPTransferEvent)(System::TObject* Sender,
                                    long BytesTransferred,
                                    char * Text, USHORT lenText,
                                    bool EOL);


class PACKAGE TipwPOP : public IPWCore
{
private:
  LONG reserved;
  TipwPOPEndTransferEvent FOnEndTransfer;
  TipwPOPErrorEvent FOnError;
  TipwPOPHeaderEvent FOnHeader;
  TipwPOPPITrailEvent FOnPITrail;
  TipwPOPStartTransferEvent FOnStartTransfer;
  TipwPOPTransferEvent FOnTransfer;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //Can be used to send additional commands directly to the POP server.  //

  void __fastcall FSetCommand(AnsiString lpszCommand);

  //Shows whether the component is connected.  //
  bool __fastcall FConnected();


  //Used to send other data to firewall.  //
  AnsiString __fastcall FFirewallData();
  void __fastcall FSetFirewallData(AnsiString lpFirewallData);
  void __fastcall SetFirewallData(char *lpFirewallData, USHORT lenFirewallData);


  //The server port for POP (default 110).  //
  USHORT __fastcall FMailPort();
  void __fastcall FSetMailPort(USHORT usMailPort);

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
  TipwPOPActions __fastcall FAction();
  void __fastcall FSetAction(TipwPOPActions iAction);







  AnsiString __fastcall FFirewallHost();
  void __fastcall FSetFirewallHost(AnsiString lpszFirewallHost);

  AnsiString __fastcall FFirewallPassword();
  void __fastcall FSetFirewallPassword(AnsiString lpszFirewallPassword);

  USHORT __fastcall FFirewallPort();
  void __fastcall FSetFirewallPort(USHORT usFirewallPort);

  TipwPOPFirewallTypes __fastcall FFirewallType();
  void __fastcall FSetFirewallType(TipwPOPFirewallTypes iFirewallType);

  AnsiString __fastcall FFirewallUser();
  void __fastcall FSetFirewallUser(AnsiString lpszFirewallUser);

  AnsiString __fastcall FLastReply();


  AnsiString __fastcall FLocalFile();
  void __fastcall FSetLocalFile(AnsiString lpszLocalFile);

  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);



  AnsiString __fastcall FMailServer();
  void __fastcall FSetMailServer(AnsiString lpszMailServer);

  USHORT __fastcall FMaxLineLength();
  void __fastcall FSetMaxLineLength(USHORT usMaxLineLength);

  USHORT __fastcall FMaxLines();
  void __fastcall FSetMaxLines(USHORT usMaxLines);

  USHORT __fastcall FMessageCount();


  AnsiString __fastcall FMessageHeaders();


  USHORT __fastcall FMessageNumber();
  void __fastcall FSetMessageNumber(USHORT usMessageNumber);

  long __fastcall FMessageSize();


  AnsiString __fastcall FMessageText();


  AnsiString __fastcall FMessageUID();


  AnsiString __fastcall FPassword();
  void __fastcall FSetPassword(AnsiString lpszPassword);



  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);

  long __fastcall FTotalSize();


  AnsiString __fastcall FUser();
  void __fastcall FSetUser(AnsiString lpszUser);

  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwPOP(TComponent* Owner);
  virtual __fastcall TipwPOP(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_24);
  virtual __fastcall ~TipwPOP();


  //Fired when the message completes transferring.  //
  virtual void FireEndTransfer();
  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired for every message header being retrieved.  //
  virtual void FireHeader(char* Field, char* Value);
  //Traces the commands sent to the mail server, and the respective replies.  //
  virtual void FirePITrail(int Direction, char* Message);
  //Fired when the message starts transferring.  //
  virtual void FireStartTransfer();
  //Fired while the message gets transferred from MailServer .  //
  virtual void FireTransfer(long BytesTransferred, char* Text, USHORT lenText, bool EOL);



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

  __property AnsiString FirewallData = {
               read=FFirewallData,
               write=FSetFirewallData               };

















  __property USHORT MailPort = {
               read=FMailPort,
               write=FSetMailPort               };





















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
    void __fastcall Connect();
    void __fastcall Delete();
    void __fastcall Disconnect();
    void __fastcall DoEvents();
    void __fastcall Interrupt();
    void __fastcall Reset();
    void __fastcall Retrieve();




__published:

  //PROPERTIES
    __property TipwPOPActions Action = {
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
    __property TipwPOPFirewallTypes FirewallType = {
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

    __property AnsiString MailServer = {
                    read=FMailServer,
                    write=FSetMailServer,
                    
                   };
    __property USHORT MaxLineLength = {
                    read=FMaxLineLength,
                    write=FSetMaxLineLength,
                    default=2048
                   };
    __property USHORT MaxLines = {
                    read=FMaxLines,
                    write=FSetMaxLines,
                    default=0
                   };
    __property USHORT MessageCount = {
                    read=FMessageCount,
                    write=SetDummyUSHORT,
                    stored=false

                   };
    __property AnsiString MessageHeaders = {
                    read=FMessageHeaders,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property USHORT MessageNumber = {
                    read=FMessageNumber,
                    write=FSetMessageNumber,
                    default=0
                   };
    __property long MessageSize = {
                    read=FMessageSize,
                    write=SetDummylong,
                    stored=false

                   };
    __property AnsiString MessageText = {
                    read=FMessageText,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString MessageUID = {
                    read=FMessageUID,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString Password = {
                    read=FPassword,
                    write=FSetPassword,
                    
                   };

    __property int Timeout = {
                    read=FTimeout,
                    write=FSetTimeout,
                    default=0
                   };
    __property long TotalSize = {
                    read=FTotalSize,
                    write=SetDummylong,
                    stored=false

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
    //Fired when the message completes transferring.
    __property TipwPOPEndTransferEvent OnEndTransfer = {read=FOnEndTransfer, write=FOnEndTransfer};
    //Information about errors during data delivery.
    __property TipwPOPErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired for every message header being retrieved.
    __property TipwPOPHeaderEvent OnHeader = {read=FOnHeader, write=FOnHeader};
    //Traces the commands sent to the mail server, and the respective replies.
    __property TipwPOPPITrailEvent OnPITrail = {read=FOnPITrail, write=FOnPITrail};
    //Fired when the message starts transferring.
    __property TipwPOPStartTransferEvent OnStartTransfer = {read=FOnStartTransfer, write=FOnStartTransfer};
    //Fired while the message gets transferred from MailServer .
    __property TipwPOPTransferEvent OnTransfer = {read=FOnTransfer, write=FOnTransfer};


}; //end class TipwPOP

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _POP_HPP_

