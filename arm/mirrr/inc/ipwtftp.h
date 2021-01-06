
#ifndef _TFTP_HPP_
#define _TFTP_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

enum TipwTFTPActions {
  tftpIdle,
  tftpGetFile,
  tftpPutFile
};



typedef void __fastcall (__closure* TipwTFTPEndTransferEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwTFTPErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwTFTPStartTransferEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwTFTPTransferEvent)(System::TObject* Sender,
                                    long BytesTransferred,
                                    char * Text, USHORT lenText);


class PACKAGE TipwTFTP : public IPWCore
{
private:
  LONG reserved;
  TipwTFTPEndTransferEvent FOnEndTransfer;
  TipwTFTPErrorEvent FOnError;
  TipwTFTPStartTransferEvent FOnStartTransfer;
  TipwTFTPTransferEvent FOnTransfer;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //The handle of the main socket used by the component.  //
  long __fastcall FSocketHandle();


  //The UDP port where the remote TFTP server is listening.  //
  USHORT __fastcall FTFTPPort();
  void __fastcall FSetTFTPPort(USHORT usTFTPPort);

  //Size in bytes of the largest UDP datagram that can be sent or received (Windows only).  //
  USHORT __fastcall FWinsockMaxDatagramSize();


  //Maximum number of sockets available to a single process (Windows only).  //
  USHORT __fastcall FWinsockMaxSockets();


  //The path to the Winsock DLL used (Windows only).  //
  AnsiString __fastcall FWinsockPath();
  void __fastcall FSetWinsockPath(AnsiString lpszWinsockPath);



  //Design-Time Properties
  TipwTFTPActions __fastcall FAction();
  void __fastcall FSetAction(TipwTFTPActions iAction);

  AnsiString __fastcall FLocalFile();
  void __fastcall FSetLocalFile(AnsiString lpszLocalFile);

  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);

  USHORT __fastcall FMaxRetransmits();
  void __fastcall FSetMaxRetransmits(USHORT usMaxRetransmits);

  AnsiString __fastcall FRemoteFile();
  void __fastcall FSetRemoteFile(AnsiString lpszRemoteFile);

  USHORT __fastcall FRetransmitTimeout();
  void __fastcall FSetRetransmitTimeout(USHORT usRetransmitTimeout);





  AnsiString __fastcall FTFTPServer();
  void __fastcall FSetTFTPServer(AnsiString lpszTFTPServer);

  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);

  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwTFTP(TComponent* Owner);
  virtual __fastcall TipwTFTP(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_46);
  virtual __fastcall ~TipwTFTP();


  //Fired when a file completes downloading/uploading.  //
  virtual void FireEndTransfer();
  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired when a file starts downloading/uploading.  //
  virtual void FireStartTransfer();
  //Fired during file download/upload.  //
  virtual void FireTransfer(long BytesTransferred, char* Text, USHORT lenText);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };













  __property long SocketHandle = {
               read=FSocketHandle
               };

  __property USHORT TFTPPort = {
               read=FTFTPPort,
               write=FSetTFTPPort               };









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
    __property TipwTFTPActions Action = {
                    read=FAction,
                    write=FSetAction,
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
    __property USHORT MaxRetransmits = {
                    read=FMaxRetransmits,
                    write=FSetMaxRetransmits,
                    default=3
                   };
    __property AnsiString RemoteFile = {
                    read=FRemoteFile,
                    write=FSetRemoteFile,
                    
                   };
    __property USHORT RetransmitTimeout = {
                    read=FRetransmitTimeout,
                    write=FSetRetransmitTimeout,
                    default=5
                   };


    __property AnsiString TFTPServer = {
                    read=FTFTPServer,
                    write=FSetTFTPServer,
                    
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
    //Fired when a file completes downloading/uploading.
    __property TipwTFTPEndTransferEvent OnEndTransfer = {read=FOnEndTransfer, write=FOnEndTransfer};
    //Information about errors during data delivery.
    __property TipwTFTPErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired when a file starts downloading/uploading.
    __property TipwTFTPStartTransferEvent OnStartTransfer = {read=FOnStartTransfer, write=FOnStartTransfer};
    //Fired during file download/upload.
    __property TipwTFTPTransferEvent OnTransfer = {read=FOnTransfer, write=FOnTransfer};


}; //end class TipwTFTP

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _TFTP_HPP_

