
#ifndef _SNMP_HPP_
#define _SNMP_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

enum TipwSNMPActions {
  snmpReset,
  snmpSendGetRequest,
  snmpSendGetNextRequest,
  snmpSendSetRequest,
  snmpSendGetResponse,
  snmpSendTrap,
  snmpSendGetBulkRequest,
  snmpSendInformRequest
};
enum TipwSNMPObjTypes {
  otInteger=2,
  otOctetString=4,
  otNull=5,
  otObjectId=6,
  otIPAddress=64,
  otCounter32=65,
  otGauge32=66,
  otTimeTicks=67,
  otOpaque=68,
  otNSAP=69,
  otCounter64=70,
  otUnsignedInteger32=71
};
enum TipwSNMPSNMPVersions {
  snmpverDefault,
  snmpverV1,
  snmpverV2c
};
enum TipwSNMPTrapGenericTypes {
  tgtColdStart,
  tgtWarmStart,
  tgtLinkDown,
  tgtLinkUp,
  tgtAuthenticationFailure,
  tgtEGPNeighborLoss,
  tgtEnterpriseSpecific
};



typedef void __fastcall (__closure* TipwSNMPErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwSNMPGetBulkRequestEvent)(System::TObject* Sender,
                                    long RequestId,
                                    AnsiString& Community,
                                    int NonRepeaters,
                                    int MaxRepetitions,
                                    AnsiString& SourceAddress,
                                    USHORT SourcePort);
typedef void __fastcall (__closure* TipwSNMPGetNextRequestEvent)(System::TObject* Sender,
                                    long RequestId,
                                    AnsiString& Community,
                                    AnsiString& SourceAddress,
                                    USHORT SourcePort);
typedef void __fastcall (__closure* TipwSNMPGetRequestEvent)(System::TObject* Sender,
                                    long RequestId,
                                    AnsiString& Community,
                                    AnsiString& SourceAddress,
                                    USHORT SourcePort);
typedef void __fastcall (__closure* TipwSNMPGetResponseEvent)(System::TObject* Sender,
                                    long RequestId,
                                    AnsiString& Community,
                                    USHORT ErrorStatus,
                                    USHORT ErrorIndex,
                                    AnsiString& SourceAddress,
                                    USHORT SourcePort);
typedef void __fastcall (__closure* TipwSNMPInformRequestEvent)(System::TObject* Sender,
                                    long RequestId,
                                    AnsiString& Community,
                                    USHORT ErrorStatus,
                                    USHORT ErrorIndex,
                                    AnsiString& SourceAddress,
                                    USHORT SourcePort);
typedef void __fastcall (__closure* TipwSNMPPDUTraceEvent)(System::TObject* Sender,
                                    char * PDU, USHORT lenPDU,
                                    AnsiString& SourceAddress);
typedef void __fastcall (__closure* TipwSNMPReadyToSendEvent)(System::TObject* Sender);
typedef void __fastcall (__closure* TipwSNMPSetRequestEvent)(System::TObject* Sender,
                                    long RequestId,
                                    AnsiString& Community,
                                    AnsiString& SourceAddress,
                                    USHORT SourcePort);
typedef void __fastcall (__closure* TipwSNMPTrapEvent)(System::TObject* Sender,
                                    AnsiString& Community,
                                    AnsiString& Enterprise,
                                    AnsiString& AgentAddress,
                                    int GenericType,
                                    int SpecificType,
                                    long TimeStamp,
                                    AnsiString& SourceAddress,
                                    int SourcePort);


class PACKAGE TipwSNMP : public IPWCore
{
private:
  LONG reserved;
  TipwSNMPErrorEvent FOnError;
  TipwSNMPGetBulkRequestEvent FOnGetBulkRequest;
  TipwSNMPGetNextRequestEvent FOnGetNextRequest;
  TipwSNMPGetRequestEvent FOnGetRequest;
  TipwSNMPGetResponseEvent FOnGetResponse;
  TipwSNMPInformRequestEvent FOnInformRequest;
  TipwSNMPPDUTraceEvent FOnPDUTrace;
  TipwSNMPReadyToSendEvent FOnReadyToSend;
  TipwSNMPSetRequestEvent FOnSetRequest;
  TipwSNMPTrapEvent FOnTrap;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //Enables or disables data reception.  //
  bool __fastcall FAcceptData();
  void __fastcall FSetAcceptData(bool bAcceptData);

  //Enables or disables sending and receiving of SNMP packets.  //
  bool __fastcall FActive();
  void __fastcall FSetActive(bool bActive);

  //Index of the first variable (object) that caused an error.  //
  int __fastcall FErrorIndex();
  void __fastcall FSetErrorIndex(int iErrorIndex);

  //Status code for outgoing 'GET RESPONSE' packets.  //
  int __fastcall FErrorStatus();
  void __fastcall FSetErrorStatus(int iErrorStatus);

  //Used by 'BULK REQUEST' packets.  //
  int __fastcall FMaxRepetitions();
  void __fastcall FSetMaxRepetitions(int iMaxRepetitions);

  //Used by 'BULK REQUEST' packets.  //
  int __fastcall FNonRepeaters();
  void __fastcall FSetNonRepeaters(int iNonRepeaters);

  //Number of objects in the current request.  //
  int __fastcall FObjCount();
  void __fastcall FSetObjCount(int iObjCount);

  //Array of OIDs encoded as strings.  //
  AnsiString __fastcall FObjId(USHORT ObjIndex);
  void __fastcall FSetObjId(USHORT ObjIndex, AnsiString lpszObjId);

  //Array of object types.  //
  TipwSNMPObjTypes __fastcall FObjType(USHORT ObjIndex);
  void __fastcall FSetObjType(USHORT ObjIndex, TipwSNMPObjTypes iObjType);

  //Array of object values.  //
  AnsiString __fastcall FObjValue(USHORT ObjIndex);
  void __fastcall FSetObjValue(USHORT ObjIndex, AnsiString lpObjValue);
  void __fastcall SetObjValue(USHORT ObjIndex, char *lpObjValue, USHORT lenObjValue);


  //The request-id to mark outgoing packets with.  //
  long __fastcall FRequestId();
  void __fastcall FSetRequestId(long lRequestId);

  //If set to True, allows more than one instance of the component to be Active on the same LocalPort .  //
  bool __fastcall FShareLocalPort();
  void __fastcall FSetShareLocalPort(bool bShareLocalPort);

  //The handle of the main socket used by the component.  //
  long __fastcall FSocketHandle();


  //The address of the object generating the trap.  //
  AnsiString __fastcall FTrapAgentAddress();
  void __fastcall FSetTrapAgentAddress(AnsiString lpszTrapAgentAddress);

  //The type of the object generating the trap.  //
  AnsiString __fastcall FTrapEnterprise();
  void __fastcall FSetTrapEnterprise(AnsiString lpszTrapEnterprise);

  //The generic type of the trap being sent.  //
  TipwSNMPTrapGenericTypes __fastcall FTrapGenericType();
  void __fastcall FSetTrapGenericType(TipwSNMPTrapGenericTypes iTrapGenericType);

  //The specific type of the trap being sent.  //
  int __fastcall FTrapSpecificType();
  void __fastcall FSetTrapSpecificType(int iTrapSpecificType);

  //Time passed since the agent was initialized (in hundredths of a second).  //
  long __fastcall FTrapTimeStamp();
  void __fastcall FSetTrapTimeStamp(long lTrapTimeStamp);

  //Size in bytes of the largest UDP datagram that can be sent or received (Windows only).  //
  USHORT __fastcall FWinsockMaxDatagramSize();


  //Maximum number of sockets available to a single process (Windows only).  //
  USHORT __fastcall FWinsockMaxSockets();


  //The path to the Winsock DLL used (Windows only).  //
  AnsiString __fastcall FWinsockPath();
  void __fastcall FSetWinsockPath(AnsiString lpszWinsockPath);



  //Design-Time Properties


  TipwSNMPActions __fastcall FAction();
  void __fastcall FSetAction(TipwSNMPActions iAction);



  AnsiString __fastcall FCommunity();
  void __fastcall FSetCommunity(AnsiString lpszCommunity);





  long __fastcall FInBufferSize();
  void __fastcall FSetInBufferSize(long lInBufferSize);

  AnsiString __fastcall FLocalHost();
  void __fastcall FSetLocalHost(AnsiString lpszLocalHost);

  USHORT __fastcall FLocalPort();
  void __fastcall FSetLocalPort(USHORT usLocalPort);













  long __fastcall FOutBufferSize();
  void __fastcall FSetOutBufferSize(long lOutBufferSize);

  AnsiString __fastcall FRemoteHost();
  void __fastcall FSetRemoteHost(AnsiString lpszRemoteHost);

  USHORT __fastcall FRemotePort();
  void __fastcall FSetRemotePort(USHORT usRemotePort);





  TipwSNMPSNMPVersions __fastcall FSNMPVersion();
  void __fastcall FSetSNMPVersion(TipwSNMPSNMPVersions iSNMPVersion);













  AnsiString __fastcall FWinsockInfo();


  bool __fastcall FWinsockLoaded();
  void __fastcall FSetWinsockLoaded(bool bWinsockLoaded);







  AnsiString __fastcall FWinsockStatus();



  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwSNMP(TComponent* Owner);
  virtual __fastcall TipwSNMP(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_30);
  virtual __fastcall ~TipwSNMP();


  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired when a GetBulkRequest packet is received.  //
  virtual void FireGetBulkRequest(long RequestId, char* Community, int NonRepeaters, int MaxRepetitions, char* SourceAddress, USHORT SourcePort);
  //Fired when a GetNextRequest packet is received.  //
  virtual void FireGetNextRequest(long RequestId, char* Community, char* SourceAddress, USHORT SourcePort);
  //Fired when a GetRequest packet is received.  //
  virtual void FireGetRequest(long RequestId, char* Community, char* SourceAddress, USHORT SourcePort);
  //Fired when a GetResponse packet is received.  //
  virtual void FireGetResponse(long RequestId, char* Community, USHORT ErrorStatus, USHORT ErrorIndex, char* SourceAddress, USHORT SourcePort);
  //Fired when a SetRequest packet is received.  //
  virtual void FireInformRequest(long RequestId, char* Community, USHORT ErrorStatus, USHORT ErrorIndex, char* SourceAddress, USHORT SourcePort);
  //Fired for every packet sent or received.  //
  virtual void FirePDUTrace(char* PDU, USHORT lenPDU, char* SourceAddress);
  //Fired when the component is ready to send data.  //
  virtual void FireReadyToSend();
  //Fired when a SetRequest packet is received.  //
  virtual void FireSetRequest(long RequestId, char* Community, char* SourceAddress, USHORT SourcePort);
  //Fired when a SNMP trap packet is received.  //
  virtual void FireTrap(char* Community, char* Enterprise, char* AgentAddress, int GenericType, int SpecificType, long TimeStamp, char* SourceAddress, int SourcePort);



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



  __property int ErrorIndex = {
               read=FErrorIndex,
               write=FSetErrorIndex               };

  __property int ErrorStatus = {
               read=FErrorStatus,
               write=FSetErrorStatus               };







  __property int MaxRepetitions = {
               read=FMaxRepetitions,
               write=FSetMaxRepetitions               };

  __property int NonRepeaters = {
               read=FNonRepeaters,
               write=FSetNonRepeaters               };

  __property int ObjCount = {
               read=FObjCount,
               write=FSetObjCount               };

  __property AnsiString ObjId[USHORT ObjIndex] = {
               read=FObjId,
               write=FSetObjId               };

  __property TipwSNMPObjTypes ObjType[USHORT ObjIndex] = {
               read=FObjType,
               write=FSetObjType               };

  __property AnsiString ObjValue[USHORT ObjIndex] = {
               read=FObjValue,
               write=FSetObjValue               };







  __property long RequestId = {
               read=FRequestId,
               write=FSetRequestId               };

  __property bool ShareLocalPort = {
               read=FShareLocalPort,
               write=FSetShareLocalPort               };



  __property long SocketHandle = {
               read=FSocketHandle
               };

  __property AnsiString TrapAgentAddress = {
               read=FTrapAgentAddress,
               write=FSetTrapAgentAddress               };

  __property AnsiString TrapEnterprise = {
               read=FTrapEnterprise,
               write=FSetTrapEnterprise               };

  __property TipwSNMPTrapGenericTypes TrapGenericType = {
               read=FTrapGenericType,
               write=FSetTrapGenericType               };

  __property int TrapSpecificType = {
               read=FTrapSpecificType,
               write=FSetTrapSpecificType               };

  __property long TrapTimeStamp = {
               read=FTrapTimeStamp,
               write=FSetTrapTimeStamp               };





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
    void __fastcall Reset();
    void __fastcall SendGetBulkRequest();
    void __fastcall SendGetNextRequest();
    void __fastcall SendGetRequest();
    void __fastcall SendGetResponse();
    void __fastcall SendInformRequest();
    void __fastcall SendSetRequest();
    void __fastcall SendTrap();




__published:

  //PROPERTIES

    __property TipwSNMPActions Action = {
                    read=FAction,
                    write=FSetAction,
                    stored=false

                   };

    __property AnsiString Community = {
                    read=FCommunity,
                    write=FSetCommunity,
                    
                   };


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
    __property USHORT LocalPort = {
                    read=FLocalPort,
                    write=FSetLocalPort,
                    default=0
                   };






    __property long OutBufferSize = {
                    read=FOutBufferSize,
                    write=FSetOutBufferSize,
                    default=2048
                   };
    __property AnsiString RemoteHost = {
                    read=FRemoteHost,
                    write=FSetRemoteHost,
                    
                   };
    __property USHORT RemotePort = {
                    read=FRemotePort,
                    write=FSetRemotePort,
                    default=0
                   };


    __property TipwSNMPSNMPVersions SNMPVersion = {
                    read=FSNMPVersion,
                    write=FSetSNMPVersion,
                    default=snmpverDefault
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
    __property TipwSNMPErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired when a GetBulkRequest packet is received.
    __property TipwSNMPGetBulkRequestEvent OnGetBulkRequest = {read=FOnGetBulkRequest, write=FOnGetBulkRequest};
    //Fired when a GetNextRequest packet is received.
    __property TipwSNMPGetNextRequestEvent OnGetNextRequest = {read=FOnGetNextRequest, write=FOnGetNextRequest};
    //Fired when a GetRequest packet is received.
    __property TipwSNMPGetRequestEvent OnGetRequest = {read=FOnGetRequest, write=FOnGetRequest};
    //Fired when a GetResponse packet is received.
    __property TipwSNMPGetResponseEvent OnGetResponse = {read=FOnGetResponse, write=FOnGetResponse};
    //Fired when a SetRequest packet is received.
    __property TipwSNMPInformRequestEvent OnInformRequest = {read=FOnInformRequest, write=FOnInformRequest};
    //Fired for every packet sent or received.
    __property TipwSNMPPDUTraceEvent OnPDUTrace = {read=FOnPDUTrace, write=FOnPDUTrace};
    //Fired when the component is ready to send data.
    __property TipwSNMPReadyToSendEvent OnReadyToSend = {read=FOnReadyToSend, write=FOnReadyToSend};
    //Fired when a SetRequest packet is received.
    __property TipwSNMPSetRequestEvent OnSetRequest = {read=FOnSetRequest, write=FOnSetRequest};
    //Fired when a SNMP trap packet is received.
    __property TipwSNMPTrapEvent OnTrap = {read=FOnTrap, write=FOnTrap};


}; //end class TipwSNMP

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _SNMP_HPP_

