
#ifndef _DIRECTSETTLE_HPP_
#define _DIRECTSETTLE_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! CC V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipcCore.h"

namespace Ipwcc {

enum TipcDirectSettleDetailTransactionTypes {
  dsCardNotPresent,
  dsCardPresent,
  dsOffLineCredit,
  dsForce
};
typedef TFIREWALLTYPES TipcDirectSettleFirewallTypes;

typedef TPROCESSOR TipcDirectSettleProcessors;




typedef void __fastcall (__closure* TipcDirectSettleConnectedEvent)(System::TObject* Sender,
                                    int StatusCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipcDirectSettleDataPacketInEvent)(System::TObject* Sender,
                                    char * DataPacket, USHORT lenDataPacket);
typedef void __fastcall (__closure* TipcDirectSettleDataPacketOutEvent)(System::TObject* Sender,
                                    char * DataPacket, USHORT lenDataPacket);
typedef void __fastcall (__closure* TipcDirectSettleDisconnectedEvent)(System::TObject* Sender,
                                    int StatusCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipcDirectSettleErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipcDirectSettleSSLServerAuthenticationEvent)(System::TObject* Sender,
                                    char * CertEncoded, USHORT lenCertEncoded,
                                    AnsiString& CertSubject,
                                    AnsiString& CertIssuer,
                                    AnsiString& Status,
                                    bool& Accept);
typedef void __fastcall (__closure* TipcDirectSettleSSLStatusEvent)(System::TObject* Sender,
                                    AnsiString& Message);


class PACKAGE TipcDirectSettle : public IPCCore
{
private:
  LONG reserved;
  TipcDirectSettleConnectedEvent FOnConnected;
  TipcDirectSettleDataPacketInEvent FOnDataPacketIn;
  TipcDirectSettleDataPacketOutEvent FOnDataPacketOut;
  TipcDirectSettleDisconnectedEvent FOnDisconnected;
  TipcDirectSettleErrorEvent FOnError;
  TipcDirectSettleSSLServerAuthenticationEvent FOnSSLServerAuthentication;
  TipcDirectSettleSSLStatusEvent FOnSSLStatus;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //Total of purchases plus reversals.  //
  AnsiString __fastcall FBatchHashingTotal();


  //This property indicates the source of the customer data in the original authorization request.  //
  AnsiString __fastcall FDetailAccountDataSource(USHORT RecordId);
  void __fastcall FSetDetailAccountDataSource(USHORT RecordId, AnsiString lpszDetailAccountDataSource);

  //Quick way to set all the Detail Record properties for each transaction.  //
  AnsiString __fastcall FDetailAggregate(USHORT RecordId);
  void __fastcall FSetDetailAggregate(USHORT RecordId, AnsiString lpszDetailAggregate);

  //Original amount authorized before any reversals.  //
  AnsiString __fastcall FDetailAuthorizedAmount(USHORT RecordId);
  void __fastcall FSetDetailAuthorizedAmount(USHORT RecordId, AnsiString lpszDetailAuthorizedAmount);

  //Specifies the method used to verify the identity of the cardholder in the original authorization request.  //
  AnsiString __fastcall FDetailCardholderId(USHORT RecordId);
  void __fastcall FSetDetailCardholderId(USHORT RecordId, AnsiString lpszDetailCardholderId);

  //Customer's credit card number from the original authorization request.  //
  AnsiString __fastcall FDetailCardNumber(USHORT RecordId);
  void __fastcall FSetDetailCardNumber(USHORT RecordId, AnsiString lpszDetailCardNumber);

  //Total number of detail records in this settlement.  //
  int __fastcall FDetailCount();
  void __fastcall FSetDetailCount(int iDetailCount);

  //Optional purchase order number assigned by the merchant.  //
  AnsiString __fastcall FDetailPurchaseIdentifier(USHORT RecordId);
  void __fastcall FSetDetailPurchaseIdentifier(USHORT RecordId, AnsiString lpszDetailPurchaseIdentifier);

  //Authorization Characteristics Indicator from the original authorization request.  //
  AnsiString __fastcall FDetailRequestedACI(USHORT RecordId);
  void __fastcall FSetDetailRequestedACI(USHORT RecordId, AnsiString lpszDetailRequestedACI);

  //Authorization Characteristics Indicator from the original authorization response.  //
  AnsiString __fastcall FDetailResponseACI(USHORT RecordId);
  void __fastcall FSetDetailResponseACI(USHORT RecordId, AnsiString lpszDetailResponseACI);

  //Response Approval Code from the original authorization response.  //
  AnsiString __fastcall FDetailResponseApprovalCode(USHORT RecordId);
  void __fastcall FSetDetailResponseApprovalCode(USHORT RecordId, AnsiString lpszDetailResponseApprovalCode);

  //Auth Source Code from the original authorization response.  //
  AnsiString __fastcall FDetailResponseAuthSource(USHORT RecordId);
  void __fastcall FSetDetailResponseAuthSource(USHORT RecordId, AnsiString lpszDetailResponseAuthSource);

  //Address Verification Code from the original authorization response.  //
  AnsiString __fastcall FDetailResponseAVS(USHORT RecordId);
  void __fastcall FSetDetailResponseAVS(USHORT RecordId, AnsiString lpszDetailResponseAVS);

  //Response code from the original authorization response.  //
  AnsiString __fastcall FDetailResponseCode(USHORT RecordId);
  void __fastcall FSetDetailResponseCode(USHORT RecordId, AnsiString lpszDetailResponseCode);

  //The amount that the customer will be charged.  //
  AnsiString __fastcall FDetailSettlementAmount(USHORT RecordId);
  void __fastcall FSetDetailSettlementAmount(USHORT RecordId, AnsiString lpszDetailSettlementAmount);

  //Local Transaction Date from the original authorization response.  //
  AnsiString __fastcall FDetailTransactionDate(USHORT RecordId);
  void __fastcall FSetDetailTransactionDate(USHORT RecordId, AnsiString lpszDetailTransactionDate);

  //Transaction Identifier from the original authorization response.  //
  AnsiString __fastcall FDetailTransactionId(USHORT RecordId);
  void __fastcall FSetDetailTransactionId(USHORT RecordId, AnsiString lpszDetailTransactionId);

  //Transaction Number from the original authorization request.  //
  AnsiString __fastcall FDetailTransactionNumber(USHORT RecordId);
  void __fastcall FSetDetailTransactionNumber(USHORT RecordId, AnsiString lpszDetailTransactionNumber);

  //Local transaction time from the original authorization response.  //
  AnsiString __fastcall FDetailTransactionTime(USHORT RecordId);
  void __fastcall FSetDetailTransactionTime(USHORT RecordId, AnsiString lpszDetailTransactionTime);

  //Indicates transaction type for this detail record  //
  TipcDirectSettleDetailTransactionTypes __fastcall FDetailTransactionType(USHORT RecordId);
  void __fastcall FSetDetailTransactionType(USHORT RecordId, TipcDirectSettleDetailTransactionTypes iDetailTransactionType);

  //Validation Code from the original authorization response.  //
  AnsiString __fastcall FDetailValidationCode(USHORT RecordId);
  void __fastcall FSetDetailValidationCode(USHORT RecordId, AnsiString lpszDetailValidationCode);

  //Used to send other data to firewall.  //
  AnsiString __fastcall FFirewallData();
  void __fastcall FSetFirewallData(AnsiString lpFirewallData);
  void __fastcall SetFirewallData(char *lpFirewallData, USHORT lenFirewallData);


  //Indicates the status of the batch transmission.  //
  AnsiString __fastcall FResponseCode();


  //Total of purchases minus reversals. Compare to BatchNetDeposit .  //
  AnsiString __fastcall FResponseNetDeposit();


  //Batch number that belongs to this response.  //
  AnsiString __fastcall FResponseNumber();


  //Number of records received by the server in this batch.  //
  long __fastcall FResponseRecordCount();


  //Contents of this field are dependent upon the ResponseCode .  //
  AnsiString __fastcall FResponseText();


  //Date that the batch was settled.  //
  AnsiString __fastcall FResponseTransmissionDate();


  //An opaque handle to the internal representation of the certificate.  //
  long __fastcall FSSLCertHandle();
  void __fastcall FSetSSLCertHandle(long lSSLCertHandle);

  //The minimum cipher strength used for bulk encryption.  //
  int __fastcall FSSLCipherStrength();
  void __fastcall FSetSSLCipherStrength(int iSSLCipherStrength);

  //Used to enable/disable the supported security protocols.  //
  long __fastcall FSSLEnabledProtocols();
  void __fastcall FSetSSLEnabledProtocols(long lSSLEnabledProtocols);

  //The security provider to use.  //
  AnsiString __fastcall FSSLProvider();
  void __fastcall FSetSSLProvider(AnsiString lpszSSLProvider);

  //Flags to control certificate verification.  //
  long __fastcall FSSLSecurityFlags();
  void __fastcall FSetSSLSecurityFlags(long lSSLSecurityFlags);



  //Design-Time Properties
  AnsiString __fastcall FAgentBankNumber();
  void __fastcall FSetAgentBankNumber(AnsiString lpszAgentBankNumber);

  AnsiString __fastcall FAgentChainNumber();
  void __fastcall FSetAgentChainNumber(AnsiString lpszAgentChainNumber);



  AnsiString __fastcall FBatchNetDeposit();


  AnsiString __fastcall FBatchNumber();
  void __fastcall FSetBatchNumber(AnsiString lpszBatchNumber);

  int __fastcall FBatchRecordCount();










































  AnsiString __fastcall FErrorData();


  int __fastcall FErrorDataFieldNumber();


  AnsiString __fastcall FErrorRecordType();


  int __fastcall FErrorSequenceNumber();


  AnsiString __fastcall FErrorType();




  AnsiString __fastcall FFirewallHost();
  void __fastcall FSetFirewallHost(AnsiString lpszFirewallHost);

  AnsiString __fastcall FFirewallPassword();
  void __fastcall FSetFirewallPassword(AnsiString lpszFirewallPassword);

  USHORT __fastcall FFirewallPort();
  void __fastcall FSetFirewallPort(USHORT usFirewallPort);

  TipcDirectSettleFirewallTypes __fastcall FFirewallType();
  void __fastcall FSetFirewallType(TipcDirectSettleFirewallTypes iFirewallType);

  AnsiString __fastcall FFirewallUser();
  void __fastcall FSetFirewallUser(AnsiString lpszFirewallUser);

  AnsiString __fastcall FMerchantBankId();
  void __fastcall FSetMerchantBankId(AnsiString lpszMerchantBankId);

  AnsiString __fastcall FMerchantCategoryCode();
  void __fastcall FSetMerchantCategoryCode(AnsiString lpszMerchantCategoryCode);

  AnsiString __fastcall FMerchantCountryCode();
  void __fastcall FSetMerchantCountryCode(AnsiString lpszMerchantCountryCode);

  AnsiString __fastcall FMerchantCurrencyCode();
  void __fastcall FSetMerchantCurrencyCode(AnsiString lpszMerchantCurrencyCode);

  AnsiString __fastcall FMerchantIndustryCode();
  void __fastcall FSetMerchantIndustryCode(AnsiString lpszMerchantIndustryCode);

  AnsiString __fastcall FMerchantLanguage();
  void __fastcall FSetMerchantLanguage(AnsiString lpszMerchantLanguage);

  AnsiString __fastcall FMerchantLocationNumber();
  void __fastcall FSetMerchantLocationNumber(AnsiString lpszMerchantLocationNumber);

  AnsiString __fastcall FMerchantName();
  void __fastcall FSetMerchantName(AnsiString lpszMerchantName);

  AnsiString __fastcall FMerchantNumber();
  void __fastcall FSetMerchantNumber(AnsiString lpszMerchantNumber);

  AnsiString __fastcall FMerchantServiceNumber();
  void __fastcall FSetMerchantServiceNumber(AnsiString lpszMerchantServiceNumber);

  AnsiString __fastcall FMerchantState();
  void __fastcall FSetMerchantState(AnsiString lpszMerchantState);

  AnsiString __fastcall FMerchantStoreNumber();
  void __fastcall FSetMerchantStoreNumber(AnsiString lpszMerchantStoreNumber);

  AnsiString __fastcall FMerchantTerminalNumber();
  void __fastcall FSetMerchantTerminalNumber(AnsiString lpszMerchantTerminalNumber);

  AnsiString __fastcall FMerchantTimeZone();
  void __fastcall FSetMerchantTimeZone(AnsiString lpszMerchantTimeZone);

  AnsiString __fastcall FMerchantZip();
  void __fastcall FSetMerchantZip(AnsiString lpszMerchantZip);

  TipcDirectSettleProcessors __fastcall FProcessor();
  void __fastcall FSetProcessor(TipcDirectSettleProcessors iProcessor);













  AnsiString __fastcall FSSLAcceptServerCert();
  void __fastcall FSetSSLAcceptServerCert(AnsiString lpSSLAcceptServerCert);
  void __fastcall SetSSLAcceptServerCert(char *lpSSLAcceptServerCert, USHORT lenSSLAcceptServerCert);




  AnsiString __fastcall FSSLCertStore();
  void __fastcall FSetSSLCertStore(AnsiString lpszSSLCertStore);

  AnsiString __fastcall FSSLCertSubject();
  void __fastcall FSetSSLCertSubject(AnsiString lpszSSLCertSubject);









  AnsiString __fastcall FTerminalId();
  void __fastcall FSetTerminalId(AnsiString lpszTerminalId);

  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);


  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipcDirectSettle(TComponent* Owner);
  virtual __fastcall TipcDirectSettle(TComponent* Owner, bool Registered, LPSTR lpKey=IPWCC_OEMKEY_29);
  virtual __fastcall ~TipcDirectSettle();


  //Fired immediately after a connection completes (or fails).  //
  virtual void FireConnected(int StatusCode, char* Description);
  //Fired when receiving a data packet from the transaction server.  //
  virtual void FireDataPacketIn(char* DataPacket, USHORT lenDataPacket);
  //Fired when sending a data packet to the transaction server.  //
  virtual void FireDataPacketOut(char* DataPacket, USHORT lenDataPacket);
  //Fired when a connection is closed.  //
  virtual void FireDisconnected(int StatusCode, char* Description);
  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired after the server presents its certificate to the client.  //
  virtual void FireSSLServerAuthentication(char* CertEncoded, USHORT lenCertEncoded, char* CertSubject, char* CertIssuer, char* Status, bool& Accept);
  //Shows the progress of the secure connection.  //
  virtual void FireSSLStatus(char* Message);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };





  __property AnsiString BatchHashingTotal = {
               read=FBatchHashingTotal
               };







  __property AnsiString DetailAccountDataSource[USHORT RecordId] = {
               read=FDetailAccountDataSource,
               write=FSetDetailAccountDataSource               };

  __property AnsiString DetailAggregate[USHORT RecordId] = {
               read=FDetailAggregate,
               write=FSetDetailAggregate               };

  __property AnsiString DetailAuthorizedAmount[USHORT RecordId] = {
               read=FDetailAuthorizedAmount,
               write=FSetDetailAuthorizedAmount               };

  __property AnsiString DetailCardholderId[USHORT RecordId] = {
               read=FDetailCardholderId,
               write=FSetDetailCardholderId               };

  __property AnsiString DetailCardNumber[USHORT RecordId] = {
               read=FDetailCardNumber,
               write=FSetDetailCardNumber               };

  __property int DetailCount = {
               read=FDetailCount,
               write=FSetDetailCount               };

  __property AnsiString DetailPurchaseIdentifier[USHORT RecordId] = {
               read=FDetailPurchaseIdentifier,
               write=FSetDetailPurchaseIdentifier               };

  __property AnsiString DetailRequestedACI[USHORT RecordId] = {
               read=FDetailRequestedACI,
               write=FSetDetailRequestedACI               };

  __property AnsiString DetailResponseACI[USHORT RecordId] = {
               read=FDetailResponseACI,
               write=FSetDetailResponseACI               };

  __property AnsiString DetailResponseApprovalCode[USHORT RecordId] = {
               read=FDetailResponseApprovalCode,
               write=FSetDetailResponseApprovalCode               };

  __property AnsiString DetailResponseAuthSource[USHORT RecordId] = {
               read=FDetailResponseAuthSource,
               write=FSetDetailResponseAuthSource               };

  __property AnsiString DetailResponseAVS[USHORT RecordId] = {
               read=FDetailResponseAVS,
               write=FSetDetailResponseAVS               };

  __property AnsiString DetailResponseCode[USHORT RecordId] = {
               read=FDetailResponseCode,
               write=FSetDetailResponseCode               };

  __property AnsiString DetailSettlementAmount[USHORT RecordId] = {
               read=FDetailSettlementAmount,
               write=FSetDetailSettlementAmount               };

  __property AnsiString DetailTransactionDate[USHORT RecordId] = {
               read=FDetailTransactionDate,
               write=FSetDetailTransactionDate               };

  __property AnsiString DetailTransactionId[USHORT RecordId] = {
               read=FDetailTransactionId,
               write=FSetDetailTransactionId               };

  __property AnsiString DetailTransactionNumber[USHORT RecordId] = {
               read=FDetailTransactionNumber,
               write=FSetDetailTransactionNumber               };

  __property AnsiString DetailTransactionTime[USHORT RecordId] = {
               read=FDetailTransactionTime,
               write=FSetDetailTransactionTime               };

  __property TipcDirectSettleDetailTransactionTypes DetailTransactionType[USHORT RecordId] = {
               read=FDetailTransactionType,
               write=FSetDetailTransactionType               };

  __property AnsiString DetailValidationCode[USHORT RecordId] = {
               read=FDetailValidationCode,
               write=FSetDetailValidationCode               };











  __property AnsiString FirewallData = {
               read=FFirewallData,
               write=FSetFirewallData               };











































  __property AnsiString ResponseCode = {
               read=FResponseCode
               };

  __property AnsiString ResponseNetDeposit = {
               read=FResponseNetDeposit
               };

  __property AnsiString ResponseNumber = {
               read=FResponseNumber
               };

  __property long ResponseRecordCount = {
               read=FResponseRecordCount
               };

  __property AnsiString ResponseText = {
               read=FResponseText
               };

  __property AnsiString ResponseTransmissionDate = {
               read=FResponseTransmissionDate
               };



  __property long SSLCertHandle = {
               read=FSSLCertHandle,
               write=FSetSSLCertHandle               };





  __property int SSLCipherStrength = {
               read=FSSLCipherStrength,
               write=FSetSSLCipherStrength               };

  __property long SSLEnabledProtocols = {
               read=FSSLEnabledProtocols,
               write=FSetSSLEnabledProtocols               };

  __property AnsiString SSLProvider = {
               read=FSSLProvider,
               write=FSetSSLProvider               };

  __property long SSLSecurityFlags = {
               read=FSSLSecurityFlags,
               write=FSetSSLSecurityFlags               };







  //METHODS
    AnsiString __fastcall Config(AnsiString ConfigString);
    void __fastcall Interrupt();
    void __fastcall ResetData();
    void __fastcall SendSettlement();




__published:

  //PROPERTIES
    __property AnsiString AgentBankNumber = {
                    read=FAgentBankNumber,
                    write=FSetAgentBankNumber,
                    
                   };
    __property AnsiString AgentChainNumber = {
                    read=FAgentChainNumber,
                    write=FSetAgentChainNumber,
                    
                   };

    __property AnsiString BatchNetDeposit = {
                    read=FBatchNetDeposit,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString BatchNumber = {
                    read=FBatchNumber,
                    write=FSetBatchNumber,
                    
                   };
    __property int BatchRecordCount = {
                    read=FBatchRecordCount,
                    write=SetDummyint,
                    stored=false

                   };




















    __property AnsiString ErrorData = {
                    read=FErrorData,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property int ErrorDataFieldNumber = {
                    read=FErrorDataFieldNumber,
                    write=SetDummyint,
                    stored=false

                   };
    __property AnsiString ErrorRecordType = {
                    read=FErrorRecordType,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property int ErrorSequenceNumber = {
                    read=FErrorSequenceNumber,
                    write=SetDummyint,
                    stored=false

                   };
    __property AnsiString ErrorType = {
                    read=FErrorType,
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
    __property TipcDirectSettleFirewallTypes FirewallType = {
                    read=FFirewallType,
                    write=FSetFirewallType,
                    default=fwNone
                   };
    __property AnsiString FirewallUser = {
                    read=FFirewallUser,
                    write=FSetFirewallUser,
                    
                   };
    __property AnsiString MerchantBankId = {
                    read=FMerchantBankId,
                    write=FSetMerchantBankId,
                    
                   };
    __property AnsiString MerchantCategoryCode = {
                    read=FMerchantCategoryCode,
                    write=FSetMerchantCategoryCode,
                    
                   };
    __property AnsiString MerchantCountryCode = {
                    read=FMerchantCountryCode,
                    write=FSetMerchantCountryCode,
                    
                   };
    __property AnsiString MerchantCurrencyCode = {
                    read=FMerchantCurrencyCode,
                    write=FSetMerchantCurrencyCode,
                    
                   };
    __property AnsiString MerchantIndustryCode = {
                    read=FMerchantIndustryCode,
                    write=FSetMerchantIndustryCode,
                    
                   };
    __property AnsiString MerchantLanguage = {
                    read=FMerchantLanguage,
                    write=FSetMerchantLanguage,
                    
                   };
    __property AnsiString MerchantLocationNumber = {
                    read=FMerchantLocationNumber,
                    write=FSetMerchantLocationNumber,
                    
                   };
    __property AnsiString MerchantName = {
                    read=FMerchantName,
                    write=FSetMerchantName,
                    
                   };
    __property AnsiString MerchantNumber = {
                    read=FMerchantNumber,
                    write=FSetMerchantNumber,
                    
                   };
    __property AnsiString MerchantServiceNumber = {
                    read=FMerchantServiceNumber,
                    write=FSetMerchantServiceNumber,
                    
                   };
    __property AnsiString MerchantState = {
                    read=FMerchantState,
                    write=FSetMerchantState,
                    
                   };
    __property AnsiString MerchantStoreNumber = {
                    read=FMerchantStoreNumber,
                    write=FSetMerchantStoreNumber,
                    
                   };
    __property AnsiString MerchantTerminalNumber = {
                    read=FMerchantTerminalNumber,
                    write=FSetMerchantTerminalNumber,
                    
                   };
    __property AnsiString MerchantTimeZone = {
                    read=FMerchantTimeZone,
                    write=FSetMerchantTimeZone,
                    
                   };
    __property AnsiString MerchantZip = {
                    read=FMerchantZip,
                    write=FSetMerchantZip,
                    
                   };
    __property TipcDirectSettleProcessors Processor = {
                    read=FProcessor,
                    write=FSetProcessor,
                    default=psVITAL
                   };






    __property AnsiString SSLAcceptServerCert = {
                    read=FSSLAcceptServerCert,
                    write=FSetSSLAcceptServerCert,
                    stored=false

                   };

    __property AnsiString SSLCertStore = {
                    read=FSSLCertStore,
                    write=FSetSSLCertStore,
                    
                   };
    __property AnsiString SSLCertSubject = {
                    read=FSSLCertSubject,
                    write=FSetSSLCertSubject,
                    
                   };




    __property AnsiString TerminalId = {
                    read=FTerminalId,
                    write=FSetTerminalId,
                    
                   };
    __property int Timeout = {
                    read=FTimeout,
                    write=FSetTimeout,
                    default=30
                   };


  //EVENTS
    //Fired immediately after a connection completes (or fails).
    __property TipcDirectSettleConnectedEvent OnConnected = {read=FOnConnected, write=FOnConnected};
    //Fired when receiving a data packet from the transaction server.
    __property TipcDirectSettleDataPacketInEvent OnDataPacketIn = {read=FOnDataPacketIn, write=FOnDataPacketIn};
    //Fired when sending a data packet to the transaction server.
    __property TipcDirectSettleDataPacketOutEvent OnDataPacketOut = {read=FOnDataPacketOut, write=FOnDataPacketOut};
    //Fired when a connection is closed.
    __property TipcDirectSettleDisconnectedEvent OnDisconnected = {read=FOnDisconnected, write=FOnDisconnected};
    //Information about errors during data delivery.
    __property TipcDirectSettleErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired after the server presents its certificate to the client.
    __property TipcDirectSettleSSLServerAuthenticationEvent OnSSLServerAuthentication = {read=FOnSSLServerAuthentication, write=FOnSSLServerAuthentication};
    //Shows the progress of the secure connection.
    __property TipcDirectSettleSSLStatusEvent OnSSLStatus = {read=FOnSSLStatus, write=FOnSSLStatus};


}; //end class TipcDirectSettle

}//end namespace Ipwcc

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipwcc;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _DIRECTSETTLE_HPP_

