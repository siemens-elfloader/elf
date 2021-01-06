
#ifndef _WEBUPLOAD_HPP_
#define _WEBUPLOAD_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

enum TipwWebUploadActions {
  webuploadIdle,
  webuploadUpload,
  webuploadReset
};
typedef TFIREWALLTYPES TipwWebUploadFirewallTypes;




typedef void __fastcall (__closure* TipwWebUploadConnectedEvent)(System::TObject* Sender,
                                    int StatusCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwWebUploadDisconnectedEvent)(System::TObject* Sender,
                                    int StatusCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwWebUploadEndTransferEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwWebUploadErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwWebUploadHeaderEvent)(System::TObject* Sender,
                                    AnsiString& Field,
                                    AnsiString& Value);
typedef void __fastcall (__closure* TipwWebUploadSetCookieEvent)(System::TObject* Sender,
                                    AnsiString& Name,
                                    AnsiString& Value,
                                    AnsiString& Expires,
                                    AnsiString& Domain,
                                    AnsiString& Path,
                                    bool Secure);
typedef void __fastcall (__closure* TipwWebUploadStartTransferEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwWebUploadTransferEvent)(System::TObject* Sender,
                                    long BytesTransferred,
                                    char * Text, USHORT lenText);
typedef void __fastcall (__closure* TipwWebUploadUploadProgressEvent)(System::TObject* Sender,
                                    int PercentDone);


class PACKAGE TipwWebUpload : public IPWCore
{
private:
  LONG reserved;
  TipwWebUploadConnectedEvent FOnConnected;
  TipwWebUploadDisconnectedEvent FOnDisconnected;
  TipwWebUploadEndTransferEvent FOnEndTransfer;
  TipwWebUploadErrorEvent FOnError;
  TipwWebUploadHeaderEvent FOnHeader;
  TipwWebUploadSetCookieEvent FOnSetCookie;
  TipwWebUploadStartTransferEvent FOnStartTransfer;
  TipwWebUploadTransferEvent FOnTransfer;
  TipwWebUploadUploadProgressEvent FOnUploadProgress;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //The Authorization string to be sent to the server.  //
  AnsiString __fastcall FAuthorization();
  void __fastcall FSetAuthorization(AnsiString lpszAuthorization);

  //Shows whether the component is connected.  //
  bool __fastcall FConnected();


  //Number of cookies in the current request.  //
  int __fastcall FCookieCount();
  void __fastcall FSetCookieCount(int iCookieCount);

  //Array of cookie names.  //
  AnsiString __fastcall FCookieName(USHORT CookieIndex);
  void __fastcall FSetCookieName(USHORT CookieIndex, AnsiString lpszCookieName);

  //Array of cookie values.  //
  AnsiString __fastcall FCookieValue(USHORT CookieIndex);
  void __fastcall FSetCookieValue(USHORT CookieIndex, AnsiString lpszCookieValue);

  //The paths of the uploaded files.  //
  AnsiString __fastcall FFileNames(USHORT FileIndex);
  void __fastcall FSetFileNames(USHORT FileIndex, AnsiString lpszFileNames);

  //Names of form variables corresponding to the posted files.  //
  AnsiString __fastcall FFileVarNames(USHORT FileIndex);
  void __fastcall FSetFileVarNames(USHORT FileIndex, AnsiString lpszFileVarNames);

  //Used to send other data to firewall.  //
  AnsiString __fastcall FFirewallData();
  void __fastcall FSetFirewallData(AnsiString lpFirewallData);
  void __fastcall SetFirewallData(char *lpFirewallData, USHORT lenFirewallData);


  //Number of form variables for the current request.  //
  int __fastcall FFormVarCount();
  void __fastcall FSetFormVarCount(int iFormVarCount);

  //Array of form variable names for the current request.  //
  AnsiString __fastcall FFormVarNames(USHORT VarIndex);
  void __fastcall FSetFormVarNames(USHORT VarIndex, AnsiString lpszFormVarNames);

  //Array of form variable values for the current request.  //
  AnsiString __fastcall FFormVarValues(USHORT VarIndex);
  void __fastcall FSetFormVarValues(USHORT VarIndex, AnsiString lpszFormVarValues);

  //The email address of the HTTP agent (optional).  //
  AnsiString __fastcall FFrom();
  void __fastcall FSetFrom(AnsiString lpszFrom);

  //Other headers as determined by the user (optional).  //
  AnsiString __fastcall FOtherHeaders();
  void __fastcall FSetOtherHeaders(AnsiString lpszOtherHeaders);

  //Similar to the Authorization property, but for proxy authorization.  //
  AnsiString __fastcall FProxyAuthorization();
  void __fastcall FSetProxyAuthorization(AnsiString lpszProxyAuthorization);

  //Referer URL/document (optional).  //
  AnsiString __fastcall FReferer();
  void __fastcall FSetReferer(AnsiString lpszReferer);

  //The handle of the main socket used by the component.  //
  long __fastcall FSocketHandle();


  //The first line of the last server response.  //
  AnsiString __fastcall FStatusLine();


  //The contents of the last transfer.  //
  AnsiString __fastcall FTransferredData();


  //The full set of headers as received from the server.  //
  AnsiString __fastcall FTransferredHeaders();


  //Size in bytes of the largest UDP datagram that can be sent or received (Windows only).  //
  USHORT __fastcall FWinsockMaxDatagramSize();


  //Maximum number of sockets available to a single process (Windows only).  //
  USHORT __fastcall FWinsockMaxSockets();


  //The path to the Winsock DLL used (Windows only).  //
  AnsiString __fastcall FWinsockPath();
  void __fastcall FSetWinsockPath(AnsiString lpszWinsockPath);



  //Design-Time Properties
  TipwWebUploadActions __fastcall FAction();
  void __fastcall FSetAction(TipwWebUploadActions iAction);











  int __fastcall FFileCount();
  void __fastcall FSetFileCount(int iFileCount);







  AnsiString __fastcall FFirewallHost();
  void __fastcall FSetFirewallHost(AnsiString lpszFirewallHost);

  AnsiString __fastcall FFirewallPassword();
  void __fastcall FSetFirewallPassword(AnsiString lpszFirewallPassword);

  USHORT __fastcall FFirewallPort();
  void __fastcall FSetFirewallPort(USHORT usFirewallPort);

  TipwWebUploadFirewallTypes __fastcall FFirewallType();
  void __fastcall FSetFirewallType(TipwWebUploadFirewallTypes iFirewallType);

  AnsiString __fastcall FFirewallUser();
  void __fastcall FSetFirewallUser(AnsiString lpszFirewallUser);









  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);

  long __fastcall FMaxTransferredData();
  void __fastcall FSetMaxTransferredData(long lMaxTransferredData);



  AnsiString __fastcall FPassword();
  void __fastcall FSetPassword(AnsiString lpszPassword);



  AnsiString __fastcall FProxyPassword();
  void __fastcall FSetProxyPassword(AnsiString lpszProxyPassword);

  USHORT __fastcall FProxyPort();
  void __fastcall FSetProxyPort(USHORT usProxyPort);

  AnsiString __fastcall FProxyServer();
  void __fastcall FSetProxyServer(AnsiString lpszProxyServer);

  AnsiString __fastcall FProxyUser();
  void __fastcall FSetProxyUser(AnsiString lpszProxyUser);







  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);





  AnsiString __fastcall FURL();
  void __fastcall FSetURL(AnsiString lpszURL);

  AnsiString __fastcall FUser();
  void __fastcall FSetUser(AnsiString lpszUser);

  AnsiString __fastcall FUserAgent();
  void __fastcall FSetUserAgent(AnsiString lpszUserAgent);

  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwWebUpload(TComponent* Owner);
  virtual __fastcall TipwWebUpload(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_51);
  virtual __fastcall ~TipwWebUpload();


  //Fired immediately after a connection completes (or fails).  //
  virtual void FireConnected(int StatusCode, char* Description);
  //Fired when a connection is closed.  //
  virtual void FireDisconnected(int StatusCode, char* Description);
  //Fired when a document finishes transferring.  //
  virtual void FireEndTransfer();
  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired every time a header line comes in.  //
  virtual void FireHeader(char* Field, char* Value);
  //Fired for every cookie set by the server.  //
  virtual void FireSetCookie(char* Name, char* Value, char* Expires, char* Domain, char* Path, bool Secure);
  //Fired when a document starts transferring (after the headers).  //
  virtual void FireStartTransfer();
  //Fired while a document transfers (delivers document).  //
  virtual void FireTransfer(long BytesTransferred, char* Text, USHORT lenText);
  //Fired while the control is uploading files to the URL .  //
  virtual void FireUploadProgress(int PercentDone);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };



  __property AnsiString Authorization = {
               read=FAuthorization,
               write=FSetAuthorization               };

  __property bool Connected = {
               read=FConnected
               };

  __property int CookieCount = {
               read=FCookieCount,
               write=FSetCookieCount               };

  __property AnsiString CookieName[USHORT CookieIndex] = {
               read=FCookieName,
               write=FSetCookieName               };

  __property AnsiString CookieValue[USHORT CookieIndex] = {
               read=FCookieValue,
               write=FSetCookieValue               };



  __property AnsiString FileNames[USHORT FileIndex] = {
               read=FFileNames,
               write=FSetFileNames               };

  __property AnsiString FileVarNames[USHORT FileIndex] = {
               read=FFileVarNames,
               write=FSetFileVarNames               };

  __property AnsiString FirewallData = {
               read=FFirewallData,
               write=FSetFirewallData               };











  __property int FormVarCount = {
               read=FFormVarCount,
               write=FSetFormVarCount               };

  __property AnsiString FormVarNames[USHORT VarIndex] = {
               read=FFormVarNames,
               write=FSetFormVarNames               };

  __property AnsiString FormVarValues[USHORT VarIndex] = {
               read=FFormVarValues,
               write=FSetFormVarValues               };

  __property AnsiString From = {
               read=FFrom,
               write=FSetFrom               };





  __property AnsiString OtherHeaders = {
               read=FOtherHeaders,
               write=FSetOtherHeaders               };



  __property AnsiString ProxyAuthorization = {
               read=FProxyAuthorization,
               write=FSetProxyAuthorization               };









  __property AnsiString Referer = {
               read=FReferer,
               write=FSetReferer               };

  __property long SocketHandle = {
               read=FSocketHandle
               };

  __property AnsiString StatusLine = {
               read=FStatusLine
               };



  __property AnsiString TransferredData = {
               read=FTransferredData
               };

  __property AnsiString TransferredHeaders = {
               read=FTransferredHeaders
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
    void __fastcall AddCookie(AnsiString CookieName, AnsiString CookieValue);
    void __fastcall AddFileVar(AnsiString FileVar, AnsiString FileName);
    void __fastcall AddFormVar(AnsiString VarName, AnsiString VarValue);
    void __fastcall DoEvents();
    void __fastcall Interrupt();
    void __fastcall Reset();
    void __fastcall Upload();
    void __fastcall UploadTo(AnsiString URL);




__published:

  //PROPERTIES
    __property TipwWebUploadActions Action = {
                    read=FAction,
                    write=FSetAction,
                    stored=false

                   };





    __property int FileCount = {
                    read=FFileCount,
                    write=FSetFileCount,
                    default=0
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
    __property TipwWebUploadFirewallTypes FirewallType = {
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
    __property long MaxTransferredData = {
                    read=FMaxTransferredData,
                    write=FSetMaxTransferredData,
                    default=4096
                   };

    __property AnsiString Password = {
                    read=FPassword,
                    write=FSetPassword,
                    
                   };

    __property AnsiString ProxyPassword = {
                    read=FProxyPassword,
                    write=FSetProxyPassword,
                    
                   };
    __property USHORT ProxyPort = {
                    read=FProxyPort,
                    write=FSetProxyPort,
                    default=80
                   };
    __property AnsiString ProxyServer = {
                    read=FProxyServer,
                    write=FSetProxyServer,
                    
                   };
    __property AnsiString ProxyUser = {
                    read=FProxyUser,
                    write=FSetProxyUser,
                    
                   };



    __property int Timeout = {
                    read=FTimeout,
                    write=FSetTimeout,
                    default=0
                   };


    __property AnsiString URL = {
                    read=FURL,
                    write=FSetURL,
                    
                   };
    __property AnsiString User = {
                    read=FUser,
                    write=FSetUser,
                    
                   };
    __property AnsiString UserAgent = {
                    read=FUserAgent,
                    write=FSetUserAgent,
                    
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
    __property TipwWebUploadConnectedEvent OnConnected = {read=FOnConnected, write=FOnConnected};
    //Fired when a connection is closed.
    __property TipwWebUploadDisconnectedEvent OnDisconnected = {read=FOnDisconnected, write=FOnDisconnected};
    //Fired when a document finishes transferring.
    __property TipwWebUploadEndTransferEvent OnEndTransfer = {read=FOnEndTransfer, write=FOnEndTransfer};
    //Information about errors during data delivery.
    __property TipwWebUploadErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired every time a header line comes in.
    __property TipwWebUploadHeaderEvent OnHeader = {read=FOnHeader, write=FOnHeader};
    //Fired for every cookie set by the server.
    __property TipwWebUploadSetCookieEvent OnSetCookie = {read=FOnSetCookie, write=FOnSetCookie};
    //Fired when a document starts transferring (after the headers).
    __property TipwWebUploadStartTransferEvent OnStartTransfer = {read=FOnStartTransfer, write=FOnStartTransfer};
    //Fired while a document transfers (delivers document).
    __property TipwWebUploadTransferEvent OnTransfer = {read=FOnTransfer, write=FOnTransfer};
    //Fired while the control is uploading files to the URL .
    __property TipwWebUploadUploadProgressEvent OnUploadProgress = {read=FOnUploadProgress, write=FOnUploadProgress};


}; //end class TipwWebUpload

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _WEBUPLOAD_HPP_

