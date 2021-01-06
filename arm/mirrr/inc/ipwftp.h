
#ifndef _FTP_HPP_
#define _FTP_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

enum TipwFTPActions {
  ftpIdle,
  ftpAbort,
  ftpLogon,
  ftpLogoff,
  ftpDownload,
  ftpUpload,
  ftpDeleteFile,
  ftpRenameFile,
  ftpListDirectory,
  ftpListDirectoryLong,
  ftpMakeDirectory,
  ftpRemoveDirectory,
  ftpAppend,
  ftpStoreUnique
};
typedef TFIREWALLTYPES TipwFTPFirewallTypes;

enum TipwFTPTransferModes {
  tmDefault,
  tmASCII,
  tmBinary
};



typedef void __fastcall (__closure* TipwFTPDirListEvent)(System::TObject* Sender,
                                    AnsiString& DirEntry,
                                    AnsiString& FileName,
                                    bool IsDir,
                                    long FileSize,
                                    AnsiString& FileTime);
typedef void __fastcall (__closure* TipwFTPEndTransferEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwFTPErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwFTPPITrailEvent)(System::TObject* Sender,
                                    int Direction,
                                    AnsiString& Message);
typedef void __fastcall (__closure* TipwFTPStartTransferEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwFTPTransferEvent)(System::TObject* Sender,
                                    long BytesTransferred,
                                    char * Text, USHORT lenText);


class PACKAGE TipwFTP : public IPWCore
{
private:
  LONG reserved;
  TipwFTPDirListEvent FOnDirList;
  TipwFTPEndTransferEvent FOnEndTransfer;
  TipwFTPErrorEvent FOnError;
  TipwFTPPITrailEvent FOnPITrail;
  TipwFTPStartTransferEvent FOnStartTransfer;
  TipwFTPTransferEvent FOnTransfer;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //Can be used to send additional commands directly to the FTP server.  //

  void __fastcall FSetCommand(AnsiString lpszCommand);

  //Shows whether the component is connected.  //
  bool __fastcall FConnected();


  //Used to send other data to firewall.  //
  AnsiString __fastcall FFirewallData();
  void __fastcall FSetFirewallData(AnsiString lpFirewallData);
  void __fastcall SetFirewallData(char *lpFirewallData, USHORT lenFirewallData);


  //The port for the FTP service (default is 21).  //
  USHORT __fastcall FRemotePort();
  void __fastcall FSetRemotePort(USHORT usRemotePort);

  //The handle of the main socket used by the component.  //
  long __fastcall FSocketHandle();


  //The byte index in RemoteFile and LocalFile where to start the transmission.  //
  AnsiString __fastcall FStartByte();
  void __fastcall FSetStartByte(AnsiString lpszStartByte);

  //Size in bytes of the largest UDP datagram that can be sent or received (Windows only).  //
  USHORT __fastcall FWinsockMaxDatagramSize();


  //Maximum number of sockets available to a single process (Windows only).  //
  USHORT __fastcall FWinsockMaxSockets();


  //The path to the Winsock DLL used (Windows only).  //
  AnsiString __fastcall FWinsockPath();
  void __fastcall FSetWinsockPath(AnsiString lpszWinsockPath);



  //Design-Time Properties
  TipwFTPActions __fastcall FAction();
  void __fastcall FSetAction(TipwFTPActions iAction);

  AnsiString __fastcall FAltFile();
  void __fastcall FSetAltFile(AnsiString lpszAltFile);







  AnsiString __fastcall FFirewallHost();
  void __fastcall FSetFirewallHost(AnsiString lpszFirewallHost);

  AnsiString __fastcall FFirewallPassword();
  void __fastcall FSetFirewallPassword(AnsiString lpszFirewallPassword);

  USHORT __fastcall FFirewallPort();
  void __fastcall FSetFirewallPort(USHORT usFirewallPort);

  TipwFTPFirewallTypes __fastcall FFirewallType();
  void __fastcall FSetFirewallType(TipwFTPFirewallTypes iFirewallType);

  AnsiString __fastcall FFirewallUser();
  void __fastcall FSetFirewallUser(AnsiString lpszFirewallUser);

  AnsiString __fastcall FLastReply();


  AnsiString __fastcall FLocalFile();
  void __fastcall FSetLocalFile(AnsiString lpszLocalFile);

  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);

  bool __fastcall FPassive();
  void __fastcall FSetPassive(bool bPassive);

  AnsiString __fastcall FPassword();
  void __fastcall FSetPassword(AnsiString lpszPassword);

  AnsiString __fastcall FRemoteFile();
  void __fastcall FSetRemoteFile(AnsiString lpszRemoteFile);

  AnsiString __fastcall FRemoteHost();
  void __fastcall FSetRemoteHost(AnsiString lpszRemoteHost);

  AnsiString __fastcall FRemotePath();
  void __fastcall FSetRemotePath(AnsiString lpszRemotePath);







  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);

  TipwFTPTransferModes __fastcall FTransferMode();
  void __fastcall FSetTransferMode(TipwFTPTransferModes iTransferMode);

  AnsiString __fastcall FUser();
  void __fastcall FSetUser(AnsiString lpszUser);

  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwFTP(TComponent* Owner);
  virtual __fastcall TipwFTP(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_17);
  virtual __fastcall ~TipwFTP();


  //Fired when a directory entry is received.  //
  virtual void FireDirList(char* DirEntry, char* FileName, bool IsDir, long FileSize, char* FileTime);
  //Fired when a file completes downloading/uploading.  //
  virtual void FireEndTransfer();
  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Traces the commands sent to the server, and the respective replies.  //
  virtual void FirePITrail(int Direction, char* Message);
  //Fired when a file starts downloading/uploading.  //
  virtual void FireStartTransfer();
  //Fired during file download/upload.  //
  virtual void FireTransfer(long BytesTransferred, char* Text, USHORT lenText);



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



























  __property USHORT RemotePort = {
               read=FRemotePort,
               write=FSetRemotePort               };

  __property long SocketHandle = {
               read=FSocketHandle
               };

  __property AnsiString StartByte = {
               read=FStartByte,
               write=FSetStartByte               };











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
    void __fastcall Abort();
    void __fastcall Append();
    void __fastcall DeleteFile();
    void __fastcall DoEvents();
    void __fastcall Download();
    void __fastcall Interrupt();
    void __fastcall ListDirectory();
    void __fastcall ListDirectoryLong();
    void __fastcall Logoff();
    void __fastcall Logon();
    void __fastcall MakeDirectory();
    void __fastcall RemoveDirectory();
    void __fastcall RenameFile();
    void __fastcall StoreUnique();
    void __fastcall Upload();




__published:

  //PROPERTIES
    __property TipwFTPActions Action = {
                    read=FAction,
                    write=FSetAction,
                    stored=false

                   };
    __property AnsiString AltFile = {
                    read=FAltFile,
                    write=FSetAltFile,
                    
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
    __property TipwFTPFirewallTypes FirewallType = {
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
    __property bool Passive = {
                    read=FPassive,
                    write=FSetPassive,
                    default=false
                   };
    __property AnsiString Password = {
                    read=FPassword,
                    write=FSetPassword,
                    
                   };
    __property AnsiString RemoteFile = {
                    read=FRemoteFile,
                    write=FSetRemoteFile,
                    
                   };
    __property AnsiString RemoteHost = {
                    read=FRemoteHost,
                    write=FSetRemoteHost,
                    
                   };
    __property AnsiString RemotePath = {
                    read=FRemotePath,
                    write=FSetRemotePath,
                    
                   };



    __property int Timeout = {
                    read=FTimeout,
                    write=FSetTimeout,
                    default=0
                   };
    __property TipwFTPTransferModes TransferMode = {
                    read=FTransferMode,
                    write=FSetTransferMode,
                    default=tmDefault
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
    //Fired when a directory entry is received.
    __property TipwFTPDirListEvent OnDirList = {read=FOnDirList, write=FOnDirList};
    //Fired when a file completes downloading/uploading.
    __property TipwFTPEndTransferEvent OnEndTransfer = {read=FOnEndTransfer, write=FOnEndTransfer};
    //Information about errors during data delivery.
    __property TipwFTPErrorEvent OnError = {read=FOnError, write=FOnError};
    //Traces the commands sent to the server, and the respective replies.
    __property TipwFTPPITrailEvent OnPITrail = {read=FOnPITrail, write=FOnPITrail};
    //Fired when a file starts downloading/uploading.
    __property TipwFTPStartTransferEvent OnStartTransfer = {read=FOnStartTransfer, write=FOnStartTransfer};
    //Fired during file download/upload.
    __property TipwFTPTransferEvent OnTransfer = {read=FOnTransfer, write=FOnTransfer};


}; //end class TipwFTP

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _FTP_HPP_

