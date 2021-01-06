
#ifndef _HTTP_HPP_
#define _HTTP_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

enum TipwHTTPActions {
  httpIdle,
  httpGet,
  httpPost,
  httpHead,
  httpResetHeaders,
  httpPut
};
typedef TFIREWALLTYPES TipwHTTPFirewallTypes;

enum TipwHTTPFollowRedirects {
  frNever,
  frAlways,
  frSameScheme
};



typedef void __fastcall (__closure* TipwHTTPConnectedEvent)(System::TObject* Sender,
                                    int StatusCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwHTTPDisconnectedEvent)(System::TObject* Sender,
                                    int StatusCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwHTTPEndTransferEvent)(System::TObject* Sender,
                                    int Direction);
typedef void __fastcall (__closure* TipwHTTPErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwHTTPHeaderEvent)(System::TObject* Sender,
                                    AnsiString& Field,
                                    AnsiString& Value);
typedef void __fastcall (__closure* TipwHTTPSetCookieEvent)(System::TObject* Sender,
                                    AnsiString& Name,
                                    AnsiString& Value,
                                    AnsiString& Expires,
                                    AnsiString& Domain,
                                    AnsiString& Path,
                                    bool Secure);
typedef void __fastcall (__closure* TipwHTTPStartTransferEvent)(System::TObject* Sender,
                                    int Direction);
typedef void __fastcall (__closure* TipwHTTPTransferEvent)(System::TObject* Sender,
                                    int Direction,
                                    long BytesTransferred,
                                    char * Text, USHORT lenText);


class PACKAGE TipwHTTP : public IPWCore
{
private:
  LONG reserved;
  TipwHTTPConnectedEvent FOnConnected;
  TipwHTTPDisconnectedEvent FOnDisconnected;
  TipwHTTPEndTransferEvent FOnEndTransfer;
  TipwHTTPErrorEvent FOnError;
  TipwHTTPHeaderEvent FOnHeader;
  TipwHTTPSetCookieEvent FOnSetCookie;
  TipwHTTPStartTransferEvent FOnStartTransfer;
  TipwHTTPTransferEvent FOnTransfer;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //A file to append to PostData if the POST or PUT methods are used.  //
  AnsiString __fastcall FAttachedFile();
  void __fastcall FSetAttachedFile(AnsiString lpszAttachedFile);

  //The Authorization string to be sent to the server.  //
  AnsiString __fastcall FAuthorization();
  void __fastcall FSetAuthorization(AnsiString lpszAuthorization);

  //Shows whether the component is connected.  //
  bool __fastcall FConnected();


  //Content type for posted data.  //
  AnsiString __fastcall FContentType();
  void __fastcall FSetContentType(AnsiString lpszContentType);

  //Number of cookies in the current request.  //
  int __fastcall FCookieCount();
  void __fastcall FSetCookieCount(int iCookieCount);

  //Array of cookie names.  //
  AnsiString __fastcall FCookieName(USHORT CookieIndex);
  void __fastcall FSetCookieName(USHORT CookieIndex, AnsiString lpszCookieName);

  //Array of cookie values.  //
  AnsiString __fastcall FCookieValue(USHORT CookieIndex);
  void __fastcall FSetCookieValue(USHORT CookieIndex, AnsiString lpszCookieValue);

  //Used to send other data to firewall.  //
  AnsiString __fastcall FFirewallData();
  void __fastcall FSetFirewallData(AnsiString lpFirewallData);
  void __fastcall SetFirewallData(char *lpFirewallData, USHORT lenFirewallData);


  //The email address of the HTTP agent (optional).  //
  AnsiString __fastcall FFrom();
  void __fastcall FSetFrom(AnsiString lpszFrom);

  //The HTTP method used for the request.  //
  AnsiString __fastcall FHTTPMethod();
  void __fastcall FSetHTTPMethod(AnsiString lpszHTTPMethod);

  //The version of HTTP used by the component.  //
  AnsiString __fastcall FHTTPVersion();
  void __fastcall FSetHTTPVersion(AnsiString lpszHTTPVersion);

  //A date determining the maximum age of the desired document.  //
  AnsiString __fastcall FIfModifiedSince();
  void __fastcall FSetIfModifiedSince(AnsiString lpszIfModifiedSince);

  //Other headers as determined by the user (optional).  //
  AnsiString __fastcall FOtherHeaders();
  void __fastcall FSetOtherHeaders(AnsiString lpszOtherHeaders);

  //The data to post with the URL if the POST method is used.  //
  AnsiString __fastcall FPostData();
  void __fastcall FSetPostData(AnsiString lpPostData);
  void __fastcall SetPostData(char *lpPostData, USHORT lenPostData);


  //A browser/server specific header line (optional).  //
  AnsiString __fastcall FPragma();
  void __fastcall FSetPragma(AnsiString lpszPragma);

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


  //The path for the URL.  //
  AnsiString __fastcall FURLPath();
  void __fastcall FSetURLPath(AnsiString lpszURLPath);

  //The port for the URL.  //
  USHORT __fastcall FURLPort();
  void __fastcall FSetURLPort(USHORT usURLPort);

  //The scheme for the URL.  //
  AnsiString __fastcall FURLScheme();
  void __fastcall FSetURLScheme(AnsiString lpszURLScheme);

  //The server for the URL.  //
  AnsiString __fastcall FURLServer();
  void __fastcall FSetURLServer(AnsiString lpszURLServer);

  //Size in bytes of the largest UDP datagram that can be sent or received (Windows only).  //
  USHORT __fastcall FWinsockMaxDatagramSize();


  //Maximum number of sockets available to a single process (Windows only).  //
  USHORT __fastcall FWinsockMaxSockets();


  //The path to the Winsock DLL used (Windows only).  //
  AnsiString __fastcall FWinsockPath();
  void __fastcall FSetWinsockPath(AnsiString lpszWinsockPath);



  //Design-Time Properties
  AnsiString __fastcall FAccept();
  void __fastcall FSetAccept(AnsiString lpszAccept);

  TipwHTTPActions __fastcall FAction();
  void __fastcall FSetAction(TipwHTTPActions iAction);

















  AnsiString __fastcall FFirewallHost();
  void __fastcall FSetFirewallHost(AnsiString lpszFirewallHost);

  AnsiString __fastcall FFirewallPassword();
  void __fastcall FSetFirewallPassword(AnsiString lpszFirewallPassword);

  USHORT __fastcall FFirewallPort();
  void __fastcall FSetFirewallPort(USHORT usFirewallPort);

  TipwHTTPFirewallTypes __fastcall FFirewallType();
  void __fastcall FSetFirewallType(TipwHTTPFirewallTypes iFirewallType);

  AnsiString __fastcall FFirewallUser();
  void __fastcall FSetFirewallUser(AnsiString lpszFirewallUser);

  TipwHTTPFollowRedirects __fastcall FFollowRedirects();
  void __fastcall FSetFollowRedirects(TipwHTTPFollowRedirects iFollowRedirects);









  AnsiString __fastcall FLocalFile();
  void __fastcall FSetLocalFile(AnsiString lpszLocalFile);

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

  virtual __fastcall TipwHTTP(TComponent* Owner);
  virtual __fastcall TipwHTTP(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_18);
  virtual __fastcall ~TipwHTTP();


  //Fired immediately after a connection completes (or fails).  //
  virtual void FireConnected(int StatusCode, char* Description);
  //Fired when a connection is closed.  //
  virtual void FireDisconnected(int StatusCode, char* Description);
  //Fired when a document finishes transferring.  //
  virtual void FireEndTransfer(int Direction);
  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired every time a header line comes in.  //
  virtual void FireHeader(char* Field, char* Value);
  //Fired for every cookie set by the server.  //
  virtual void FireSetCookie(char* Name, char* Value, char* Expires, char* Domain, char* Path, bool Secure);
  //Fired when a document starts transferring (after the headers).  //
  virtual void FireStartTransfer(int Direction);
  //Fired while a document transfers (delivers document).  //
  virtual void FireTransfer(int Direction, long BytesTransferred, char* Text, USHORT lenText);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };





  __property AnsiString AttachedFile = {
               read=FAttachedFile,
               write=FSetAttachedFile               };

  __property AnsiString Authorization = {
               read=FAuthorization,
               write=FSetAuthorization               };

  __property bool Connected = {
               read=FConnected
               };

  __property AnsiString ContentType = {
               read=FContentType,
               write=FSetContentType               };

  __property int CookieCount = {
               read=FCookieCount,
               write=FSetCookieCount               };

  __property AnsiString CookieName[USHORT CookieIndex] = {
               read=FCookieName,
               write=FSetCookieName               };

  __property AnsiString CookieValue[USHORT CookieIndex] = {
               read=FCookieValue,
               write=FSetCookieValue               };

  __property AnsiString FirewallData = {
               read=FFirewallData,
               write=FSetFirewallData               };













  __property AnsiString From = {
               read=FFrom,
               write=FSetFrom               };

  __property AnsiString HTTPMethod = {
               read=FHTTPMethod,
               write=FSetHTTPMethod               };

  __property AnsiString HTTPVersion = {
               read=FHTTPVersion,
               write=FSetHTTPVersion               };

  __property AnsiString IfModifiedSince = {
               read=FIfModifiedSince,
               write=FSetIfModifiedSince               };







  __property AnsiString OtherHeaders = {
               read=FOtherHeaders,
               write=FSetOtherHeaders               };



  __property AnsiString PostData = {
               read=FPostData,
               write=FSetPostData               };

  __property AnsiString Pragma = {
               read=FPragma,
               write=FSetPragma               };

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



  __property AnsiString URLPath = {
               read=FURLPath,
               write=FSetURLPath               };

  __property USHORT URLPort = {
               read=FURLPort,
               write=FSetURLPort               };

  __property AnsiString URLScheme = {
               read=FURLScheme,
               write=FSetURLScheme               };

  __property AnsiString URLServer = {
               read=FURLServer,
               write=FSetURLServer               };









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
    void __fastcall DoEvents();
    void __fastcall Get(AnsiString URL);
    void __fastcall Head(AnsiString URL);
    void __fastcall Interrupt();
    void __fastcall Post(AnsiString URL);
    void __fastcall Put(AnsiString URL);
    void __fastcall ResetHeaders();




__published:

  //PROPERTIES
    __property AnsiString Accept = {
                    read=FAccept,
                    write=FSetAccept,
                    
                   };
    __property TipwHTTPActions Action = {
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
    __property TipwHTTPFirewallTypes FirewallType = {
                    read=FFirewallType,
                    write=FSetFirewallType,
                    default=fwNone
                   };
    __property AnsiString FirewallUser = {
                    read=FFirewallUser,
                    write=FSetFirewallUser,
                    
                   };
    __property TipwHTTPFollowRedirects FollowRedirects = {
                    read=FFollowRedirects,
                    write=FSetFollowRedirects,
                    default=frNever
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
    __property TipwHTTPConnectedEvent OnConnected = {read=FOnConnected, write=FOnConnected};
    //Fired when a connection is closed.
    __property TipwHTTPDisconnectedEvent OnDisconnected = {read=FOnDisconnected, write=FOnDisconnected};
    //Fired when a document finishes transferring.
    __property TipwHTTPEndTransferEvent OnEndTransfer = {read=FOnEndTransfer, write=FOnEndTransfer};
    //Information about errors during data delivery.
    __property TipwHTTPErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired every time a header line comes in.
    __property TipwHTTPHeaderEvent OnHeader = {read=FOnHeader, write=FOnHeader};
    //Fired for every cookie set by the server.
    __property TipwHTTPSetCookieEvent OnSetCookie = {read=FOnSetCookie, write=FOnSetCookie};
    //Fired when a document starts transferring (after the headers).
    __property TipwHTTPStartTransferEvent OnStartTransfer = {read=FOnStartTransfer, write=FOnStartTransfer};
    //Fired while a document transfers (delivers document).
    __property TipwHTTPTransferEvent OnTransfer = {read=FOnTransfer, write=FOnTransfer};


}; //end class TipwHTTP

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _HTTP_HPP_

