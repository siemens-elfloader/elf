
#ifndef _SNPP_HPP_
#define _SNPP_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

enum TipwSNPPActions {
  snppIdle,
  snppConnect,
  snppDisconnect,
  snppSend,
  snppReset
};
typedef TFIREWALLTYPES TipwSNPPFirewallTypes;




typedef void __fastcall (__closure* TipwSNPPErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwSNPPPITrailEvent)(System::TObject* Sender,
                                    int Direction,
                                    AnsiString& Message);


class PACKAGE TipwSNPP : public IPWCore
{
private:
  LONG reserved;
  TipwSNPPErrorEvent FOnError;
  TipwSNPPPITrailEvent FOnPITrail;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //Can be used to send additional commands directly to the SNPP server.  //

  void __fastcall FSetCommand(AnsiString lpszCommand);

  //Shows whether the component is connected.  //
  bool __fastcall FConnected();


  //Used to send other data to firewall.  //
  AnsiString __fastcall FFirewallData();
  void __fastcall FSetFirewallData(AnsiString lpFirewallData);
  void __fastcall SetFirewallData(char *lpFirewallData, USHORT lenFirewallData);


  //The server port for SNPP (default 444).  //
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
  TipwSNPPActions __fastcall FAction();
  void __fastcall FSetAction(TipwSNPPActions iAction);

  AnsiString __fastcall FCallerId();
  void __fastcall FSetCallerId(AnsiString lpszCallerId);







  AnsiString __fastcall FFirewallHost();
  void __fastcall FSetFirewallHost(AnsiString lpszFirewallHost);

  AnsiString __fastcall FFirewallPassword();
  void __fastcall FSetFirewallPassword(AnsiString lpszFirewallPassword);

  USHORT __fastcall FFirewallPort();
  void __fastcall FSetFirewallPort(USHORT usFirewallPort);

  TipwSNPPFirewallTypes __fastcall FFirewallType();
  void __fastcall FSetFirewallType(TipwSNPPFirewallTypes iFirewallType);

  AnsiString __fastcall FFirewallUser();
  void __fastcall FSetFirewallUser(AnsiString lpszFirewallUser);

  AnsiString __fastcall FLastReply();


  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);

  AnsiString __fastcall FMessage();
  void __fastcall FSetMessage(AnsiString lpszMessage);

  AnsiString __fastcall FPagerId();
  void __fastcall FSetPagerId(AnsiString lpszPagerId);

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

  virtual __fastcall TipwSNPP(TComponent* Owner);
  virtual __fastcall TipwSNPP(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_32);
  virtual __fastcall ~TipwSNPP();


  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Traces the commands sent to the server, and the respective replies.  //
  virtual void FirePITrail(int Direction, char* Message);



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
    void __fastcall Connect();
    void __fastcall Disconnect();
    void __fastcall DoEvents();
    void __fastcall Reset();
    void __fastcall Send();




__published:

  //PROPERTIES
    __property TipwSNPPActions Action = {
                    read=FAction,
                    write=FSetAction,
                    stored=false

                   };
    __property AnsiString CallerId = {
                    read=FCallerId,
                    write=FSetCallerId,
                    
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
    __property TipwSNPPFirewallTypes FirewallType = {
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
    __property AnsiString LocalHost = {
                    read=FLocalHost,
                    write=FSetLocalHost,
                    stored=false

                   };
    __property AnsiString Message = {
                    read=FMessage,
                    write=FSetMessage,
                    
                   };
    __property AnsiString PagerId = {
                    read=FPagerId,
                    write=FSetPagerId,
                    
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
    __property TipwSNPPErrorEvent OnError = {read=FOnError, write=FOnError};
    //Traces the commands sent to the server, and the respective replies.
    __property TipwSNPPPITrailEvent OnPITrail = {read=FOnPITrail, write=FOnPITrail};


}; //end class TipwSNPP

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _SNPP_HPP_

