
#ifndef _LDAP_HPP_
#define _LDAP_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

enum TipwLDAPActions {
  ldapIdle,
  ldapBind,
  ldapUnbind,
  ldapSearch,
  ldapModify,
  ldapModifyRDN,
  ldapAdd,
  ldapDelete,
  ldapCompare,
  ldapAbandon
};
enum TipwLDAPAttrModOps {
  amoAdd,
  amoDelete,
  amoReplace
};
typedef TFIREWALLTYPES TipwLDAPFirewallTypes;

enum TipwLDAPSearchDerefAliases {
  sdaNever,
  sdaInSearching,
  sdaFindingBaseObject,
  sdaAlways
};
enum TipwLDAPSearchScopes {
  ssBaseObject,
  ssSingleLevel,
  ssWholeSubtree
};



typedef void __fastcall (__closure* TipwLDAPErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwLDAPResultEvent)(System::TObject* Sender,
                                    int MessageId,
                                    AnsiString& DN,
                                    int ResultCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwLDAPSearchCompleteEvent)(System::TObject* Sender,
                                    int MessageId,
                                    AnsiString& DN,
                                    int ResultCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwLDAPSearchResultEvent)(System::TObject* Sender,
                                    int MessageId,
                                    AnsiString& DN);


class PACKAGE TipwLDAP : public IPWCore
{
private:
  LONG reserved;
  TipwLDAPErrorEvent FOnError;
  TipwLDAPResultEvent FOnResult;
  TipwLDAPSearchCompleteEvent FOnSearchComplete;
  TipwLDAPSearchResultEvent FOnSearchResult;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //The message id to abandon (for LDAP abandon requests).  //
  int __fastcall FAbandonMessageId();
  void __fastcall FSetAbandonMessageId(int iAbandonMessageId);

  //Enables or disables data reception from the server.  //
  bool __fastcall FAcceptData();
  void __fastcall FSetAcceptData(bool bAcceptData);

  //Number of attributes values for the current entry.  //
  int __fastcall FAttrCount();
  void __fastcall FSetAttrCount(int iAttrCount);

  //Array of operations to apply on attributes during an LDAP modify operation.  //
  TipwLDAPAttrModOps __fastcall FAttrModOp(USHORT AttrIndex);
  void __fastcall FSetAttrModOp(USHORT AttrIndex, TipwLDAPAttrModOps iAttrModOp);

  //Array of attribute types for the current entry.  //
  AnsiString __fastcall FAttrType(USHORT AttrIndex);
  void __fastcall FSetAttrType(USHORT AttrIndex, AnsiString lpszAttrType);

  //Array of attribute values for the current entry.  //
  AnsiString __fastcall FAttrValue(USHORT AttrIndex);
  void __fastcall FSetAttrValue(USHORT AttrIndex, AnsiString lpAttrValue);
  void __fastcall SetAttrValue(USHORT AttrIndex, char *lpAttrValue, USHORT lenAttrValue);


  //Shows whether the component is connected.  //
  bool __fastcall FConnected();


  //Controls whether the old RDN should be deleted.  //
  bool __fastcall FDeleteOldRDN();
  void __fastcall FSetDeleteOldRDN(bool bDeleteOldRDN);

  //Used to send other data to firewall.  //
  AnsiString __fastcall FFirewallData();
  void __fastcall FSetFirewallData(AnsiString lpFirewallData);
  void __fastcall SetFirewallData(char *lpFirewallData, USHORT lenFirewallData);


  //The version of LDAP used.  //
  int __fastcall FLDAPVersion();
  void __fastcall FSetLDAPVersion(int iLDAPVersion);

  //The message id for the next LDAP request.  //
  int __fastcall FMessageId();
  void __fastcall FSetMessageId(int iMessageId);

  //The new RDN for the entry.  //
  AnsiString __fastcall FNewRDN();
  void __fastcall FSetNewRDN(AnsiString lpszNewRDN);

  //The password used to authenticate to the LDAP server.  //
  AnsiString __fastcall FPassword();
  void __fastcall FSetPassword(AnsiString lpszPassword);

  //The server port for LDAP (default 389).  //
  USHORT __fastcall FServerPort();
  void __fastcall FSetServerPort(USHORT usServerPort);

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




  TipwLDAPActions __fastcall FAction();
  void __fastcall FSetAction(TipwLDAPActions iAction);













  AnsiString __fastcall FDN();
  void __fastcall FSetDN(AnsiString lpszDN);



  AnsiString __fastcall FFirewallHost();
  void __fastcall FSetFirewallHost(AnsiString lpszFirewallHost);

  AnsiString __fastcall FFirewallPassword();
  void __fastcall FSetFirewallPassword(AnsiString lpszFirewallPassword);

  USHORT __fastcall FFirewallPort();
  void __fastcall FSetFirewallPort(USHORT usFirewallPort);

  TipwLDAPFirewallTypes __fastcall FFirewallType();
  void __fastcall FSetFirewallType(TipwLDAPFirewallTypes iFirewallType);

  AnsiString __fastcall FFirewallUser();
  void __fastcall FSetFirewallUser(AnsiString lpszFirewallUser);



  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);







  int __fastcall FResultCode();


  AnsiString __fastcall FResultDescription();


  AnsiString __fastcall FResultDN();


  TipwLDAPSearchDerefAliases __fastcall FSearchDerefAliases();
  void __fastcall FSetSearchDerefAliases(TipwLDAPSearchDerefAliases iSearchDerefAliases);

  AnsiString __fastcall FSearchFilter();
  void __fastcall FSetSearchFilter(AnsiString lpszSearchFilter);

  bool __fastcall FSearchReturnValues();
  void __fastcall FSetSearchReturnValues(bool bSearchReturnValues);

  TipwLDAPSearchScopes __fastcall FSearchScope();
  void __fastcall FSetSearchScope(TipwLDAPSearchScopes iSearchScope);

  int __fastcall FSearchSizeLimit();
  void __fastcall FSetSearchSizeLimit(int iSearchSizeLimit);

  int __fastcall FSearchTimeLimit();
  void __fastcall FSetSearchTimeLimit(int iSearchTimeLimit);

  AnsiString __fastcall FServerName();
  void __fastcall FSetServerName(AnsiString lpszServerName);





  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);

  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwLDAP(TComponent* Owner);
  virtual __fastcall TipwLDAP(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_33);
  virtual __fastcall ~TipwLDAP();


  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired for every server response, except search responses.  //
  virtual void FireResult(int MessageId, char* DN, int ResultCode, char* Description);
  //Fired upon completion of a search operation.  //
  virtual void FireSearchComplete(int MessageId, char* DN, int ResultCode, char* Description);
  //Fired for every entry returned from a search operation.  //
  virtual void FireSearchResult(int MessageId, char* DN);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };

  __property int AbandonMessageId = {
               read=FAbandonMessageId,
               write=FSetAbandonMessageId               };

  __property bool AcceptData = {
               read=FAcceptData,
               write=FSetAcceptData               };



  __property int AttrCount = {
               read=FAttrCount,
               write=FSetAttrCount               };

  __property TipwLDAPAttrModOps AttrModOp[USHORT AttrIndex] = {
               read=FAttrModOp,
               write=FSetAttrModOp               };

  __property AnsiString AttrType[USHORT AttrIndex] = {
               read=FAttrType,
               write=FSetAttrType               };

  __property AnsiString AttrValue[USHORT AttrIndex] = {
               read=FAttrValue,
               write=FSetAttrValue               };

  __property bool Connected = {
               read=FConnected
               };

  __property bool DeleteOldRDN = {
               read=FDeleteOldRDN,
               write=FSetDeleteOldRDN               };



  __property AnsiString FirewallData = {
               read=FFirewallData,
               write=FSetFirewallData               };











  __property int LDAPVersion = {
               read=FLDAPVersion,
               write=FSetLDAPVersion               };



  __property int MessageId = {
               read=FMessageId,
               write=FSetMessageId               };

  __property AnsiString NewRDN = {
               read=FNewRDN,
               write=FSetNewRDN               };

  __property AnsiString Password = {
               read=FPassword,
               write=FSetPassword               };





















  __property USHORT ServerPort = {
               read=FServerPort,
               write=FSetServerPort               };

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
    void __fastcall Abandon();
    void __fastcall Add();
    void __fastcall Bind();
    void __fastcall Compare();
    void __fastcall Delete();
    void __fastcall DoEvents();
    void __fastcall Modify();
    void __fastcall ModifyRDN();
    void __fastcall Search();
    void __fastcall Unbind();




__published:

  //PROPERTIES


    __property TipwLDAPActions Action = {
                    read=FAction,
                    write=FSetAction,
                    stored=false

                   };






    __property AnsiString DN = {
                    read=FDN,
                    write=FSetDN,
                    
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
    __property TipwLDAPFirewallTypes FirewallType = {
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



    __property int ResultCode = {
                    read=FResultCode,
                    write=SetDummyint,
                    stored=false

                   };
    __property AnsiString ResultDescription = {
                    read=FResultDescription,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString ResultDN = {
                    read=FResultDN,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property TipwLDAPSearchDerefAliases SearchDerefAliases = {
                    read=FSearchDerefAliases,
                    write=FSetSearchDerefAliases,
                    default=sdaNever
                   };
    __property AnsiString SearchFilter = {
                    read=FSearchFilter,
                    write=FSetSearchFilter,
                    
                   };
    __property bool SearchReturnValues = {
                    read=FSearchReturnValues,
                    write=FSetSearchReturnValues,
                    default=true
                   };
    __property TipwLDAPSearchScopes SearchScope = {
                    read=FSearchScope,
                    write=FSetSearchScope,
                    default=ssBaseObject
                   };
    __property int SearchSizeLimit = {
                    read=FSearchSizeLimit,
                    write=FSetSearchSizeLimit,
                    default=0
                   };
    __property int SearchTimeLimit = {
                    read=FSearchTimeLimit,
                    write=FSetSearchTimeLimit,
                    default=0
                   };
    __property AnsiString ServerName = {
                    read=FServerName,
                    write=FSetServerName,
                    
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
    //Information about errors during data delivery.
    __property TipwLDAPErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired for every server response, except search responses.
    __property TipwLDAPResultEvent OnResult = {read=FOnResult, write=FOnResult};
    //Fired upon completion of a search operation.
    __property TipwLDAPSearchCompleteEvent OnSearchComplete = {read=FOnSearchComplete, write=FOnSearchComplete};
    //Fired for every entry returned from a search operation.
    __property TipwLDAPSearchResultEvent OnSearchResult = {read=FOnSearchResult, write=FOnSearchResult};


}; //end class TipwLDAP

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _LDAP_HPP_

