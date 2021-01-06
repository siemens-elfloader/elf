
#ifndef _ICMPPORT_HPP_
#define _ICMPPORT_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {




typedef void __fastcall (__closure* TipwICMPPortDataInEvent)(System::TObject* Sender,
                                    BYTE MessageType,
                                    BYTE MessageSubType,
                                    char * MessageData, USHORT lenMessageData,
                                    bool Checksum,
                                    AnsiString& SourceAddress);
typedef void __fastcall (__closure* TipwICMPPortErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwICMPPortReadyToSendEvent)(System::TObject* Sender);


class PACKAGE TipwICMPPort : public IPWCore
{
private:
  LONG reserved;
  TipwICMPPortDataInEvent FOnDataIn;
  TipwICMPPortErrorEvent FOnError;
  TipwICMPPortReadyToSendEvent FOnReadyToSend;


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

  //The handle of the main socket used by the component.  //
  long __fastcall FSocketHandle();


  //The time to live (TTL) value for the ICMP packets sent by the component.  //
  USHORT __fastcall FTimeToLive();
  void __fastcall FSetTimeToLive(USHORT usTimeToLive);

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

  USHORT __fastcall FMaxMessageSize();
  void __fastcall FSetMaxMessageSize(USHORT lMaxMessageSize);

  BYTE __fastcall FMessageSubType();
  void __fastcall FSetMessageSubType(BYTE iMessageSubType);

  BYTE __fastcall FMessageType();
  void __fastcall FSetMessageType(BYTE iMessageType);

  long __fastcall FOutBufferSize();
  void __fastcall FSetOutBufferSize(long lOutBufferSize);

  USHORT __fastcall FQOSFlags();
  void __fastcall FSetQOSFlags(USHORT usQOSFlags);

  AnsiString __fastcall FRemoteHost();
  void __fastcall FSetRemoteHost(AnsiString lpszRemoteHost);





  bool __fastcall FUseConnection();
  void __fastcall FSetUseConnection(bool bUseConnection);

  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwICMPPort(TComponent* Owner);
  virtual __fastcall TipwICMPPort(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_16);
  virtual __fastcall ~TipwICMPPort();


  //Fired when new ICMP messages come in.  //
  virtual void FireDataIn(BYTE MessageType, BYTE MessageSubType, char* MessageData, USHORT lenMessageData, bool Checksum, char* SourceAddress);
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

















  __property long SocketHandle = {
               read=FSocketHandle
               };

  __property USHORT TimeToLive = {
               read=FTimeToLive,
               write=FSetTimeToLive               };







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
    __property USHORT MaxMessageSize = {
                    read=FMaxMessageSize,
                    write=FSetMaxMessageSize,
                    default=2048
                   };
    __property BYTE MessageSubType = {
                    read=FMessageSubType,
                    write=FSetMessageSubType,
                    default=0
                   };
    __property BYTE MessageType = {
                    read=FMessageType,
                    write=FSetMessageType,
                    default=0
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
    //Fired when new ICMP messages come in.
    __property TipwICMPPortDataInEvent OnDataIn = {read=FOnDataIn, write=FOnDataIn};
    //Information about errors during data delivery.
    __property TipwICMPPortErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired when the component is ready to send data.
    __property TipwICMPPortReadyToSendEvent OnReadyToSend = {read=FOnReadyToSend, write=FOnReadyToSend};


}; //end class TipwICMPPort

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _ICMPPORT_HPP_

