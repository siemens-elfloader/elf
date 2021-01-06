
#ifndef _WHOIS_HPP_
#define _WHOIS_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

typedef TFIREWALLTYPES TipwWhoisFirewallTypes;




typedef void __fastcall (__closure* TipwWhoisErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);


class PACKAGE TipwWhois : public IPWCore
{
private:
  LONG reserved;
  TipwWhoisErrorEvent FOnError;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //Used to send other data to firewall.  //
  AnsiString __fastcall FFirewallData();
  void __fastcall FSetFirewallData(AnsiString lpFirewallData);
  void __fastcall SetFirewallData(char *lpFirewallData, USHORT lenFirewallData);


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
  AnsiString __fastcall FDefaultServer();
  void __fastcall FSetDefaultServer(AnsiString lpszDefaultServer);

  AnsiString __fastcall FDomain();
  void __fastcall FSetDomain(AnsiString lpszDomain);

  AnsiString __fastcall FDomainInfo();




  AnsiString __fastcall FFirewallHost();
  void __fastcall FSetFirewallHost(AnsiString lpszFirewallHost);

  AnsiString __fastcall FFirewallPassword();
  void __fastcall FSetFirewallPassword(AnsiString lpszFirewallPassword);

  USHORT __fastcall FFirewallPort();
  void __fastcall FSetFirewallPort(USHORT usFirewallPort);

  TipwWhoisFirewallTypes __fastcall FFirewallType();
  void __fastcall FSetFirewallType(TipwWhoisFirewallTypes iFirewallType);

  AnsiString __fastcall FFirewallUser();
  void __fastcall FSetFirewallUser(AnsiString lpszFirewallUser);

  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);

  AnsiString __fastcall FServer();
  void __fastcall FSetServer(AnsiString lpszServer);



  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);

  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwWhois(TComponent* Owner);
  virtual __fastcall TipwWhois(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_53);
  virtual __fastcall ~TipwWhois();


  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };







  __property AnsiString FirewallData = {
               read=FFirewallData,
               write=FSetFirewallData               };















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
    void __fastcall DoEvents();
    void __fastcall Query(AnsiString Domain);




__published:

  //PROPERTIES
    __property AnsiString DefaultServer = {
                    read=FDefaultServer,
                    write=FSetDefaultServer,
                    
                   };
    __property AnsiString Domain = {
                    read=FDomain,
                    write=FSetDomain,
                    stored=false

                   };
    __property AnsiString DomainInfo = {
                    read=FDomainInfo,
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
    __property TipwWhoisFirewallTypes FirewallType = {
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
    __property AnsiString Server = {
                    read=FServer,
                    write=FSetServer,
                    
                   };

    __property int Timeout = {
                    read=FTimeout,
                    write=FSetTimeout,
                    default=30
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
    __property TipwWhoisErrorEvent OnError = {read=FOnError, write=FOnError};


}; //end class TipwWhois

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _WHOIS_HPP_

