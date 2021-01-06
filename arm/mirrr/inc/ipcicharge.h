
#ifndef _ICHARGE_HPP_
#define _ICHARGE_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! CC V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipcCore.h"

namespace Ipwcc {

typedef TCARDTYPE TipcIChargeCardTypes;

typedef TFIREWALLTYPES TipcIChargeFirewallTypes;

enum TipcIChargeGateways {
  gwNoGateway,
  gwAuthorizeNet,
  gwDPI,
  gwEprocessing,
  gwGoRealTime,
  gwIBill,
  gwIntellipay,
  gwIOnGate,
  gwITransact,
  gwNetBilling,
  gwPayFlowPro,
  gwPayready,
  gwViaKlix,
  gwUSAePay,
  gwPlugNPay,
  gwPlanetPayment,
  gwMPCS,
  gwRTWare,
  gwECX,
  gwBankOfAmerica
};
typedef TPROXYSSL TipcIChargeProxySSLs;

enum TipcIChargeTransactionTypes {
  ttSale,
  ttAuthOnly,
  ttCapture,
  ttCredit,
  ttVoid,
  ttForce,
  ttAVSOnly
};



typedef void __fastcall (__closure* TipcIChargeErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipcIChargeSSLServerAuthenticationEvent)(System::TObject* Sender,
                                    char * CertEncoded, USHORT lenCertEncoded,
                                    AnsiString& CertSubject,
                                    AnsiString& CertIssuer,
                                    AnsiString& Status,
                                    bool& Accept);
typedef void __fastcall (__closure* TipcIChargeSSLStatusEvent)(System::TObject* Sender,
                                    AnsiString& Message);


class PACKAGE TipcICharge : public IPCCore
{
private:
  LONG reserved;
  TipcIChargeErrorEvent FOnError;
  TipcIChargeSSLServerAuthenticationEvent FOnSSLServerAuthentication;
  TipcIChargeSSLStatusEvent FOnSSLStatus;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //Type of credit card being used in this transaction.  //
  TipcIChargeCardTypes __fastcall FCardType();
  void __fastcall FSetCardType(TipcIChargeCardTypes iCardType);

  //Used to send other data to firewall.  //
  AnsiString __fastcall FFirewallData();
  void __fastcall FSetFirewallData(AnsiString lpFirewallData);
  void __fastcall SetFirewallData(char *lpFirewallData, USHORT lenFirewallData);


  //Similar to the Authorization property, but for proxy authorization.  //
  AnsiString __fastcall FProxyAuthorization();
  void __fastcall FSetProxyAuthorization(AnsiString lpszProxyAuthorization);

  //Array of special gateway field names to submit in this transaction.  //
  AnsiString __fastcall FSpecialFieldNames(USHORT FieldIndex);
  void __fastcall FSetSpecialFieldNames(USHORT FieldIndex, AnsiString lpszSpecialFieldNames);

  //Array of special gateway field values to submit in this transaction.  //
  AnsiString __fastcall FSpecialFieldValues(USHORT FieldIndex);
  void __fastcall FSetSpecialFieldValues(USHORT FieldIndex, AnsiString lpszSpecialFieldValues);

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
  AnsiString __fastcall FCardCVV2Data();
  void __fastcall FSetCardCVV2Data(AnsiString lpszCardCVV2Data);

  AnsiString __fastcall FCardExpMonth();
  void __fastcall FSetCardExpMonth(AnsiString lpszCardExpMonth);

  AnsiString __fastcall FCardExpYear();
  void __fastcall FSetCardExpYear(AnsiString lpszCardExpYear);

  AnsiString __fastcall FCardNumber();
  void __fastcall FSetCardNumber(AnsiString lpszCardNumber);



  AnsiString __fastcall FCustomerAddress();
  void __fastcall FSetCustomerAddress(AnsiString lpszCustomerAddress);

  AnsiString __fastcall FCustomerCity();
  void __fastcall FSetCustomerCity(AnsiString lpszCustomerCity);

  AnsiString __fastcall FCustomerCountry();
  void __fastcall FSetCustomerCountry(AnsiString lpszCustomerCountry);

  AnsiString __fastcall FCustomerEmail();
  void __fastcall FSetCustomerEmail(AnsiString lpszCustomerEmail);

  AnsiString __fastcall FCustomerFax();
  void __fastcall FSetCustomerFax(AnsiString lpszCustomerFax);

  AnsiString __fastcall FCustomerFirstName();
  void __fastcall FSetCustomerFirstName(AnsiString lpszCustomerFirstName);

  AnsiString __fastcall FCustomerId();
  void __fastcall FSetCustomerId(AnsiString lpszCustomerId);

  AnsiString __fastcall FCustomerLastName();
  void __fastcall FSetCustomerLastName(AnsiString lpszCustomerLastName);

  AnsiString __fastcall FCustomerPhone();
  void __fastcall FSetCustomerPhone(AnsiString lpszCustomerPhone);

  AnsiString __fastcall FCustomerState();
  void __fastcall FSetCustomerState(AnsiString lpszCustomerState);

  AnsiString __fastcall FCustomerZip();
  void __fastcall FSetCustomerZip(AnsiString lpszCustomerZip);



  AnsiString __fastcall FFirewallHost();
  void __fastcall FSetFirewallHost(AnsiString lpszFirewallHost);

  AnsiString __fastcall FFirewallPassword();
  void __fastcall FSetFirewallPassword(AnsiString lpszFirewallPassword);

  USHORT __fastcall FFirewallPort();
  void __fastcall FSetFirewallPort(USHORT usFirewallPort);

  TipcIChargeFirewallTypes __fastcall FFirewallType();
  void __fastcall FSetFirewallType(TipcIChargeFirewallTypes iFirewallType);

  AnsiString __fastcall FFirewallUser();
  void __fastcall FSetFirewallUser(AnsiString lpszFirewallUser);

  TipcIChargeGateways __fastcall FGateway();
  void __fastcall FSetGateway(TipcIChargeGateways iGateway);

  AnsiString __fastcall FGatewayURL();
  void __fastcall FSetGatewayURL(AnsiString lpszGatewayURL);

  AnsiString __fastcall FInvoiceNumber();
  void __fastcall FSetInvoiceNumber(AnsiString lpszInvoiceNumber);

  AnsiString __fastcall FMerchantLogin();
  void __fastcall FSetMerchantLogin(AnsiString lpszMerchantLogin);

  AnsiString __fastcall FMerchantPassword();
  void __fastcall FSetMerchantPassword(AnsiString lpszMerchantPassword);



  AnsiString __fastcall FProxyPassword();
  void __fastcall FSetProxyPassword(AnsiString lpszProxyPassword);

  USHORT __fastcall FProxyPort();
  void __fastcall FSetProxyPort(USHORT usProxyPort);

  AnsiString __fastcall FProxyServer();
  void __fastcall FSetProxyServer(AnsiString lpszProxyServer);

  TipcIChargeProxySSLs __fastcall FProxySSL();
  void __fastcall FSetProxySSL(TipcIChargeProxySSLs iProxySSL);

  AnsiString __fastcall FProxyUser();
  void __fastcall FSetProxyUser(AnsiString lpszProxyUser);

  AnsiString __fastcall FResponseApprovalCode();


  AnsiString __fastcall FResponseAVS();


  AnsiString __fastcall FResponseCode();


  AnsiString __fastcall FResponseCVV2();


  AnsiString __fastcall FResponseData();


  AnsiString __fastcall FResponseInvoiceNumber();


  AnsiString __fastcall FResponseText();


  AnsiString __fastcall FResponseTransactionId();


  int __fastcall FSpecialFieldCount();
  void __fastcall FSetSpecialFieldCount(int iSpecialFieldCount);





  AnsiString __fastcall FSSLAcceptServerCert();
  void __fastcall FSetSSLAcceptServerCert(AnsiString lpSSLAcceptServerCert);
  void __fastcall SetSSLAcceptServerCert(char *lpSSLAcceptServerCert, USHORT lenSSLAcceptServerCert);




  AnsiString __fastcall FSSLCertStore();
  void __fastcall FSetSSLCertStore(AnsiString lpszSSLCertStore);

  AnsiString __fastcall FSSLCertSubject();
  void __fastcall FSetSSLCertSubject(AnsiString lpszSSLCertSubject);









  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);

  AnsiString __fastcall FTransactionAmount();
  void __fastcall FSetTransactionAmount(AnsiString lpszTransactionAmount);

  bool __fastcall FTransactionApproved();


  AnsiString __fastcall FTransactionDesc();
  void __fastcall FSetTransactionDesc(AnsiString lpszTransactionDesc);

  TipcIChargeTransactionTypes __fastcall FTransactionType();
  void __fastcall FSetTransactionType(TipcIChargeTransactionTypes iTransactionType);


  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipcICharge(TComponent* Owner);
  virtual __fastcall TipcICharge(TComponent* Owner, bool Registered, LPSTR lpKey=IPWCC_OEMKEY_24);
  virtual __fastcall ~TipcICharge();


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









  __property TipcIChargeCardTypes CardType = {
               read=FCardType,
               write=FSetCardType               };























  __property AnsiString FirewallData = {
               read=FFirewallData,
               write=FSetFirewallData               };





















  __property AnsiString ProxyAuthorization = {
               read=FProxyAuthorization,
               write=FSetProxyAuthorization               };





























  __property AnsiString SpecialFieldNames[USHORT FieldIndex] = {
               read=FSpecialFieldNames,
               write=FSetSpecialFieldNames               };

  __property AnsiString SpecialFieldValues[USHORT FieldIndex] = {
               read=FSpecialFieldValues,
               write=FSetSpecialFieldValues               };



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
    void __fastcall AddSpecialField(AnsiString Name, AnsiString Val);
    void __fastcall Authorize();
    AnsiString __fastcall Config(AnsiString ConfigString);
    void __fastcall Interrupt();
    void __fastcall PreAuthorize();
    void __fastcall ResetData();
    void __fastcall ResetSpecialFields();




__published:

  //PROPERTIES
    __property AnsiString CardCVV2Data = {
                    read=FCardCVV2Data,
                    write=FSetCardCVV2Data,
                    
                   };
    __property AnsiString CardExpMonth = {
                    read=FCardExpMonth,
                    write=FSetCardExpMonth,
                    
                   };
    __property AnsiString CardExpYear = {
                    read=FCardExpYear,
                    write=FSetCardExpYear,
                    
                   };
    __property AnsiString CardNumber = {
                    read=FCardNumber,
                    write=FSetCardNumber,
                    
                   };

    __property AnsiString CustomerAddress = {
                    read=FCustomerAddress,
                    write=FSetCustomerAddress,
                    
                   };
    __property AnsiString CustomerCity = {
                    read=FCustomerCity,
                    write=FSetCustomerCity,
                    
                   };
    __property AnsiString CustomerCountry = {
                    read=FCustomerCountry,
                    write=FSetCustomerCountry,
                    
                   };
    __property AnsiString CustomerEmail = {
                    read=FCustomerEmail,
                    write=FSetCustomerEmail,
                    
                   };
    __property AnsiString CustomerFax = {
                    read=FCustomerFax,
                    write=FSetCustomerFax,
                    
                   };
    __property AnsiString CustomerFirstName = {
                    read=FCustomerFirstName,
                    write=FSetCustomerFirstName,
                    
                   };
    __property AnsiString CustomerId = {
                    read=FCustomerId,
                    write=FSetCustomerId,
                    
                   };
    __property AnsiString CustomerLastName = {
                    read=FCustomerLastName,
                    write=FSetCustomerLastName,
                    
                   };
    __property AnsiString CustomerPhone = {
                    read=FCustomerPhone,
                    write=FSetCustomerPhone,
                    
                   };
    __property AnsiString CustomerState = {
                    read=FCustomerState,
                    write=FSetCustomerState,
                    
                   };
    __property AnsiString CustomerZip = {
                    read=FCustomerZip,
                    write=FSetCustomerZip,
                    
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
    __property TipcIChargeFirewallTypes FirewallType = {
                    read=FFirewallType,
                    write=FSetFirewallType,
                    default=fwNone
                   };
    __property AnsiString FirewallUser = {
                    read=FFirewallUser,
                    write=FSetFirewallUser,
                    
                   };
    __property TipcIChargeGateways Gateway = {
                    read=FGateway,
                    write=FSetGateway,
                    default=gwNoGateway
                   };
    __property AnsiString GatewayURL = {
                    read=FGatewayURL,
                    write=FSetGatewayURL,
                    
                   };
    __property AnsiString InvoiceNumber = {
                    read=FInvoiceNumber,
                    write=FSetInvoiceNumber,
                    
                   };
    __property AnsiString MerchantLogin = {
                    read=FMerchantLogin,
                    write=FSetMerchantLogin,
                    
                   };
    __property AnsiString MerchantPassword = {
                    read=FMerchantPassword,
                    write=FSetMerchantPassword,
                    
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
    __property TipcIChargeProxySSLs ProxySSL = {
                    read=FProxySSL,
                    write=FSetProxySSL,
                    default=psAutomatic
                   };
    __property AnsiString ProxyUser = {
                    read=FProxyUser,
                    write=FSetProxyUser,
                    
                   };
    __property AnsiString ResponseApprovalCode = {
                    read=FResponseApprovalCode,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString ResponseAVS = {
                    read=FResponseAVS,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString ResponseCode = {
                    read=FResponseCode,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString ResponseCVV2 = {
                    read=FResponseCVV2,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString ResponseData = {
                    read=FResponseData,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString ResponseInvoiceNumber = {
                    read=FResponseInvoiceNumber,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString ResponseText = {
                    read=FResponseText,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property AnsiString ResponseTransactionId = {
                    read=FResponseTransactionId,
                    write=SetDummyAnsiString,
                    stored=false

                   };
    __property int SpecialFieldCount = {
                    read=FSpecialFieldCount,
                    write=FSetSpecialFieldCount,
                    default=0
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




    __property int Timeout = {
                    read=FTimeout,
                    write=FSetTimeout,
                    default=30
                   };
    __property AnsiString TransactionAmount = {
                    read=FTransactionAmount,
                    write=FSetTransactionAmount,
                    
                   };
    __property bool TransactionApproved = {
                    read=FTransactionApproved,
                    write=SetDummybool,
                    stored=false

                   };
    __property AnsiString TransactionDesc = {
                    read=FTransactionDesc,
                    write=FSetTransactionDesc,
                    
                   };
    __property TipcIChargeTransactionTypes TransactionType = {
                    read=FTransactionType,
                    write=FSetTransactionType,
                    default=ttSale
                   };


  //EVENTS
    //Information about errors during data delivery.
    __property TipcIChargeErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired after the server presents its certificate to the client.
    __property TipcIChargeSSLServerAuthenticationEvent OnSSLServerAuthentication = {read=FOnSSLServerAuthentication, write=FOnSSLServerAuthentication};
    //Shows the progress of the secure connection.
    __property TipcIChargeSSLStatusEvent OnSSLStatus = {read=FOnSSLStatus, write=FOnSSLStatus};


}; //end class TipcICharge

}//end namespace Ipwcc

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipwcc;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _ICHARGE_HPP_

