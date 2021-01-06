
#ifndef _SOAP_HPP_
#define _SOAP_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

enum TipwSOAPActions {
  soapIdle,
  soapSendRequest,
  soapReset,
  soapBuildPacket,
  soapSendPacket,
  soapEvalPacket
};
typedef TFIREWALLTYPES TipwSOAPFirewallTypes;

enum TipwSOAPValueFormats {
  vfText,
  vfXML,
  vfFullXML
};



typedef void __fastcall (__closure* TipwSOAPConnectedEvent)(System::TObject* Sender,
                                    int StatusCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwSOAPDisconnectedEvent)(System::TObject* Sender,
                                    int StatusCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwSOAPEndTransferEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwSOAPErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwSOAPHeaderEvent)(System::TObject* Sender,
                                    AnsiString& Field,
                                    AnsiString& Value);
typedef void __fastcall (__closure* TipwSOAPSetCookieEvent)(System::TObject* Sender,
                                    AnsiString& Name,
                                    AnsiString& Value,
                                    AnsiString& Expires,
                                    AnsiString& Domain,
                                    AnsiString& Path,
                                    bool Secure);
typedef void __fastcall (__closure* TipwSOAPStartTransferEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwSOAPTransferEvent)(System::TObject* Sender,
                                    long BytesTransferred);


class PACKAGE TipwSOAP : public IPWCore
{
private:
  LONG reserved;
  TipwSOAPConnectedEvent FOnConnected;
  TipwSOAPDisconnectedEvent FOnDisconnected;
  TipwSOAPEndTransferEvent FOnEndTransfer;
  TipwSOAPErrorEvent FOnError;
  TipwSOAPHeaderEvent FOnHeader;
  TipwSOAPSetCookieEvent FOnSetCookie;
  TipwSOAPStartTransferEvent FOnStartTransfer;
  TipwSOAPTransferEvent FOnTransfer;


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


  //Content type for SOAP request data.  //
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


  //Flags controlling the behaviour of the parser.  //
  long __fastcall FFlags();
  void __fastcall FSetFlags(long lFlags);

  //Other headers as determined by the user (optional).  //
  AnsiString __fastcall FOtherHeaders();
  void __fastcall FSetOtherHeaders(AnsiString lpszOtherHeaders);

  //The number of default Namespaces defined.  //
  int __fastcall FNamespaceCount();
  void __fastcall FSetNamespaceCount(int iNamespaceCount);

  //The default Namespaces defined by the component.  //
  AnsiString __fastcall FNamespaces(USHORT NamespaceIndex);
  void __fastcall FSetNamespaces(USHORT NamespaceIndex, AnsiString lpszNamespaces);

  //Extra attributes of the Method parameters.  //
  AnsiString __fastcall FParamAttr(USHORT ParamIndex);
  void __fastcall FSetParamAttr(USHORT ParamIndex, AnsiString lpszParamAttr);

  //The number of parameters sent to the remote host.  //
  int __fastcall FParamCount();
  void __fastcall FSetParamCount(int iParamCount);

  //The names of the Method parameters.  //
  AnsiString __fastcall FParamName(USHORT ParamIndex);
  void __fastcall FSetParamName(USHORT ParamIndex, AnsiString lpszParamName);

  //The values of the Method parameters.  //
  AnsiString __fastcall FParamValue(USHORT ParamIndex);
  void __fastcall FSetParamValue(USHORT ParamIndex, AnsiString lpszParamValue);

  //The prefixes corresponding to the default Namespaces defined by the component.  //
  AnsiString __fastcall FPrefixes(USHORT NamespaceIndex);
  void __fastcall FSetPrefixes(USHORT NamespaceIndex, AnsiString lpszPrefixes);

  //Similar to the Authorization property, but for proxy authorization.  //
  AnsiString __fastcall FProxyAuthorization();
  void __fastcall FSetProxyAuthorization(AnsiString lpszProxyAuthorization);

  //Contents of the optional SOAP header sent to the server.  //
  AnsiString __fastcall FSOAPHeader();
  void __fastcall FSetSOAPHeader(AnsiString lpszSOAPHeader);

  //Full contents of the SOAP packet.  //
  AnsiString __fastcall FSOAPPacket();
  void __fastcall FSetSOAPPacket(AnsiString lpszSOAPPacket);

  //The handle of the main socket used by the component.  //
  long __fastcall FSocketHandle();


  //The first line of the last server response.  //
  AnsiString __fastcall FStatusLine();


  //Size in bytes of the largest UDP datagram that can be sent or received (Windows only).  //
  USHORT __fastcall FWinsockMaxDatagramSize();


  //Maximum number of sockets available to a single process (Windows only).  //
  USHORT __fastcall FWinsockMaxSockets();


  //The path to the Winsock DLL used (Windows only).  //
  AnsiString __fastcall FWinsockPath();
  void __fastcall FSetWinsockPath(AnsiString lpszWinsockPath);

  //Size of attribute values array for the current element.  //
  int __fastcall FXAttrCount();


  //Array of attribute names for the current element.  //
  AnsiString __fastcall FXAttrName(USHORT AttrIndex);


  //Array of attribute namespaces for the current element.  //
  AnsiString __fastcall FXAttrNamespace(USHORT AttrIndex);


  //Array of attribute prefixes for the current element.  //
  AnsiString __fastcall FXAttrPrefix(USHORT AttrIndex);


  //Array of attribute values for the current element.  //
  AnsiString __fastcall FXAttrValue(USHORT AttrIndex);




  //Design-Time Properties
  TipwSOAPActions __fastcall FAction();
  void __fastcall FSetAction(TipwSOAPActions iAction);

  AnsiString __fastcall FActionURI();
  void __fastcall FSetActionURI(AnsiString lpszActionURI);













  AnsiString __fastcall FFaultActor();


  AnsiString __fastcall FFaultCode();


  AnsiString __fastcall FFaultString();




  AnsiString __fastcall FFirewallHost();
  void __fastcall FSetFirewallHost(AnsiString lpszFirewallHost);

  AnsiString __fastcall FFirewallPassword();
  void __fastcall FSetFirewallPassword(AnsiString lpszFirewallPassword);

  USHORT __fastcall FFirewallPort();
  void __fastcall FSetFirewallPort(USHORT usFirewallPort);

  TipwSOAPFirewallTypes __fastcall FFirewallType();
  void __fastcall FSetFirewallType(TipwSOAPFirewallTypes iFirewallType);

  AnsiString __fastcall FFirewallUser();
  void __fastcall FSetFirewallUser(AnsiString lpszFirewallUser);





  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);

  AnsiString __fastcall FMethod();
  void __fastcall FSetMethod(AnsiString lpszMethod);

  AnsiString __fastcall FMethodURI();
  void __fastcall FSetMethodURI(AnsiString lpszMethodURI);













  AnsiString __fastcall FPassword();
  void __fastcall FSetPassword(AnsiString lpszPassword);





  USHORT __fastcall FProxyPort();
  void __fastcall FSetProxyPort(USHORT usProxyPort);

  AnsiString __fastcall FProxyServer();
  void __fastcall FSetProxyServer(AnsiString lpszProxyServer);

  AnsiString __fastcall FReturnValue();


  AnsiString __fastcall FSOAPEncoding();
  void __fastcall FSetSOAPEncoding(AnsiString lpszSOAPEncoding);









  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);

  AnsiString __fastcall FURL();
  void __fastcall FSetURL(AnsiString lpszURL);

  AnsiString __fastcall FUser();
  void __fastcall FSetUser(AnsiString lpszUser);

  AnsiString __fastcall FUserAgent();
  void __fastcall FSetUserAgent(AnsiString lpszUserAgent);

  TipwSOAPValueFormats __fastcall FValueFormat();
  void __fastcall FSetValueFormat(TipwSOAPValueFormats iValueFormat);

  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();












  int __fastcall FXChildren();


  AnsiString __fastcall FXElement();


  AnsiString __fastcall FXNamespace();


  AnsiString __fastcall FXParent();


  AnsiString __fastcall FXPath();
  void __fastcall FSetXPath(AnsiString lpszXPath);

  AnsiString __fastcall FXPrefix();


  AnsiString __fastcall FXText();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwSOAP(TComponent* Owner);
  virtual __fastcall TipwSOAP(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_55);
  virtual __fastcall ~TipwSOAP();


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
  //Fired while the response transfers.  //
  virtual void FireTransfer(long BytesTransferred);



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











  __property long Flags = {
               read=FFlags,
               write=FSetFlags               };

  __property AnsiString OtherHeaders = {
               read=FOtherHeaders,
               write=FSetOtherHeaders               };







  __property int NamespaceCount = {
               read=FNamespaceCount,
               write=FSetNamespaceCount               };

  __property AnsiString Namespaces[USHORT NamespaceIndex] = {
               read=FNamespaces,
               write=FSetNamespaces               };

  __property AnsiString ParamAttr[USHORT ParamIndex] = {
               read=FParamAttr,
               write=FSetParamAttr               };

  __property int ParamCount = {
               read=FParamCount,
               write=FSetParamCount               };

  __property AnsiString ParamName[USHORT ParamIndex] = {
               read=FParamName,
               write=FSetParamName               };

  __property AnsiString ParamValue[USHORT ParamIndex] = {
               read=FParamValue,
               write=FSetParamValue               };



  __property AnsiString Prefixes[USHORT NamespaceIndex] = {
               read=FPrefixes,
               write=FSetPrefixes               };

  __property AnsiString ProxyAuthorization = {
               read=FProxyAuthorization,
               write=FSetProxyAuthorization               };









  __property AnsiString SOAPHeader = {
               read=FSOAPHeader,
               write=FSetSOAPHeader               };

  __property AnsiString SOAPPacket = {
               read=FSOAPPacket,
               write=FSetSOAPPacket               };

  __property long SocketHandle = {
               read=FSocketHandle
               };

  __property AnsiString StatusLine = {
               read=FStatusLine
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



  __property int XAttrCount = {
               read=FXAttrCount
               };

  __property AnsiString XAttrName[USHORT AttrIndex] = {
               read=FXAttrName
               };

  __property AnsiString XAttrNamespace[USHORT AttrIndex] = {
               read=FXAttrNamespace
               };

  __property AnsiString XAttrPrefix[USHORT AttrIndex] = {
               read=FXAttrPrefix
               };

  __property AnsiString XAttrValue[USHORT AttrIndex] = {
               read=FXAttrValue
               };

















  //METHODS
    void __fastcall AddCookie(AnsiString CookieName, AnsiString CookieValue);
    void __fastcall AddParam(AnsiString ParamName, AnsiString ParamValue);
    void __fastcall BuildPacket();
    void __fastcall DoEvents();
    void __fastcall EvalPacket();
    void __fastcall Interrupt();
    void __fastcall Reset();
    void __fastcall SendPacket();
    void __fastcall SendRequest();




__published:

  //PROPERTIES
    __property TipwSOAPActions Action = {
                    read=FAction,
                    write=FSetAction,
                    stored=false

                   };
    __property AnsiString ActionURI = {
                    read=FActionURI,
                    write=FSetActionURI,
                    
                   };






    __property AnsiString FaultActor = {
                    read=FFaultActor,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString FaultCode = {
                    read=FFaultCode,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString FaultString = {
                    read=FFaultString,
                    write=SetDummyAnsiString,
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
    __property TipwSOAPFirewallTypes FirewallType = {
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
    __property AnsiString Method = {
                    read=FMethod,
                    write=FSetMethod,
                    
                   };
    __property AnsiString MethodURI = {
                    read=FMethodURI,
                    write=FSetMethodURI,
                    
                   };






    __property AnsiString Password = {
                    read=FPassword,
                    write=FSetPassword,
                    
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
    __property AnsiString ReturnValue = {
                    read=FReturnValue,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString SOAPEncoding = {
                    read=FSOAPEncoding,
                    write=FSetSOAPEncoding,
                    
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
    __property TipwSOAPValueFormats ValueFormat = {
                    read=FValueFormat,
                    write=FSetValueFormat,
                    stored=false

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





    __property int XChildren = {
                    read=FXChildren,
                    write=SetDummyint,
                    stored=false

                   };
    __property AnsiString XElement = {
                    read=FXElement,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString XNamespace = {
                    read=FXNamespace,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString XParent = {
                    read=FXParent,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString XPath = {
                    read=FXPath,
                    write=FSetXPath,
                    
                   };
    __property AnsiString XPrefix = {
                    read=FXPrefix,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString XText = {
                    read=FXText,
                    write=SetDummyAnsiString,
                    stored=false

                   };


  //EVENTS
    //Fired immediately after a connection completes (or fails).
    __property TipwSOAPConnectedEvent OnConnected = {read=FOnConnected, write=FOnConnected};
    //Fired when a connection is closed.
    __property TipwSOAPDisconnectedEvent OnDisconnected = {read=FOnDisconnected, write=FOnDisconnected};
    //Fired when a document finishes transferring.
    __property TipwSOAPEndTransferEvent OnEndTransfer = {read=FOnEndTransfer, write=FOnEndTransfer};
    //Information about errors during data delivery.
    __property TipwSOAPErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired every time a header line comes in.
    __property TipwSOAPHeaderEvent OnHeader = {read=FOnHeader, write=FOnHeader};
    //Fired for every cookie set by the server.
    __property TipwSOAPSetCookieEvent OnSetCookie = {read=FOnSetCookie, write=FOnSetCookie};
    //Fired when a document starts transferring (after the headers).
    __property TipwSOAPStartTransferEvent OnStartTransfer = {read=FOnStartTransfer, write=FOnStartTransfer};
    //Fired while the response transfers.
    __property TipwSOAPTransferEvent OnTransfer = {read=FOnTransfer, write=FOnTransfer};


}; //end class TipwSOAP

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _SOAP_HPP_

