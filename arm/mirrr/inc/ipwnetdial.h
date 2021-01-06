
#ifndef _NETDIAL_HPP_
#define _NETDIAL_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

enum TipwNetDialActions {
  netdialIdle,
  netdialConnect,
  netdialDisconnect,
  netdialListPhonebook,
  netdialListConnections,
  netdialListDevices,
  netdialCreateEntry,
  netdialDeleteEntry
};



typedef void __fastcall (__closure* TipwNetDialConnectedEntryEvent)(System::TObject* Sender,
                                    long Handle,
                                    AnsiString& Entry,
                                    AnsiString& DeviceName,
                                    AnsiString& DeviceType,
                                    AnsiString& StatusDescription);
typedef void __fastcall (__closure* TipwNetDialDeviceEvent)(System::TObject* Sender,
                                    AnsiString& DeviceName,
                                    AnsiString& DeviceType);
typedef void __fastcall (__closure* TipwNetDialErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwNetDialPhonebookEntryEvent)(System::TObject* Sender,
                                    AnsiString& Entry);
typedef void __fastcall (__closure* TipwNetDialStatusEvent)(System::TObject* Sender,
                                    long Operation,
                                    long StatusCode,
                                    AnsiString& OperationDescription,
                                    AnsiString& StatusDescription);


class PACKAGE TipwNetDial : public IPWCore
{
private:
  LONG reserved;
  TipwNetDialConnectedEntryEvent FOnConnectedEntry;
  TipwNetDialDeviceEvent FOnDevice;
  TipwNetDialErrorEvent FOnError;
  TipwNetDialPhonebookEntryEvent FOnPhonebookEntry;
  TipwNetDialStatusEvent FOnStatus;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //The handle of the connection. 0 if invalid or not connected.  //
  long __fastcall FHandle();
  void __fastcall FSetHandle(long lHandle);



  //Design-Time Properties
  TipwNetDialActions __fastcall FAction();
  void __fastcall FSetAction(TipwNetDialActions iAction);

  AnsiString __fastcall FCallbackNumber();
  void __fastcall FSetCallbackNumber(AnsiString lpszCallbackNumber);

  AnsiString __fastcall FDomain();
  void __fastcall FSetDomain(AnsiString lpszDomain);

  AnsiString __fastcall FEntryDeviceName();
  void __fastcall FSetEntryDeviceName(AnsiString lpszEntryDeviceName);

  AnsiString __fastcall FEntryDeviceType();
  void __fastcall FSetEntryDeviceType(AnsiString lpszEntryDeviceType);

  AnsiString __fastcall FEntryDNSServer();
  void __fastcall FSetEntryDNSServer(AnsiString lpszEntryDNSServer);

  AnsiString __fastcall FEntryIPAddress();
  void __fastcall FSetEntryIPAddress(AnsiString lpszEntryIPAddress);

  AnsiString __fastcall FEntryPhoneNumber();
  void __fastcall FSetEntryPhoneNumber(AnsiString lpszEntryPhoneNumber);

  AnsiString __fastcall FEntryWINSServer();
  void __fastcall FSetEntryWINSServer(AnsiString lpszEntryWINSServer);



  AnsiString __fastcall FPassword();
  void __fastcall FSetPassword(AnsiString lpszPassword);

  AnsiString __fastcall FPhonebook();
  void __fastcall FSetPhonebook(AnsiString lpszPhonebook);

  AnsiString __fastcall FPhonebookEntry();
  void __fastcall FSetPhonebookEntry(AnsiString lpszPhonebookEntry);

  AnsiString __fastcall FPhoneNumber();
  void __fastcall FSetPhoneNumber(AnsiString lpszPhoneNumber);

  int __fastcall FTimeout();
  void __fastcall FSetTimeout(int iTimeout);

  AnsiString __fastcall FUser();
  void __fastcall FSetUser(AnsiString lpszUser);


  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwNetDial(TComponent* Owner);
  virtual __fastcall TipwNetDial(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_27);
  virtual __fastcall ~TipwNetDial();


  //Fired for every connected device if Action is set to 4 (List Connections) .  //
  virtual void FireConnectedEntry(long Handle, char* Entry, char* DeviceName, char* DeviceType, char* StatusDescription);
  //Fired for every dial device when Action is set 'List Devices'.  //
  virtual void FireDevice(char* DeviceName, char* DeviceType);
  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired for every Phonebook entry when Action is set to 3 (List Phonebook Entries) .  //
  virtual void FirePhonebookEntry(char* Entry);
  //Occurs during connect or disconnect attempts.  //
  virtual void FireStatus(long Operation, long StatusCode, char* OperationDescription, char* StatusDescription);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };



















  __property long Handle = {
               read=FHandle,
               write=FSetHandle               };















  //METHODS
    void __fastcall Connect();
    void __fastcall CreateEntry();
    void __fastcall DeleteEntry();
    void __fastcall Disconnect();
    void __fastcall DoEvents();
    void __fastcall ListConnections();
    void __fastcall ListDevices();
    void __fastcall ListPhonebook();




__published:

  //PROPERTIES
    __property TipwNetDialActions Action = {
                    read=FAction,
                    write=FSetAction,
                    stored=false

                   };
    __property AnsiString CallbackNumber = {
                    read=FCallbackNumber,
                    write=FSetCallbackNumber,
                    
                   };
    __property AnsiString Domain = {
                    read=FDomain,
                    write=FSetDomain,
                    
                   };
    __property AnsiString EntryDeviceName = {
                    read=FEntryDeviceName,
                    write=FSetEntryDeviceName,
                    
                   };
    __property AnsiString EntryDeviceType = {
                    read=FEntryDeviceType,
                    write=FSetEntryDeviceType,
                    
                   };
    __property AnsiString EntryDNSServer = {
                    read=FEntryDNSServer,
                    write=FSetEntryDNSServer,
                    
                   };
    __property AnsiString EntryIPAddress = {
                    read=FEntryIPAddress,
                    write=FSetEntryIPAddress,
                    
                   };
    __property AnsiString EntryPhoneNumber = {
                    read=FEntryPhoneNumber,
                    write=FSetEntryPhoneNumber,
                    
                   };
    __property AnsiString EntryWINSServer = {
                    read=FEntryWINSServer,
                    write=FSetEntryWINSServer,
                    
                   };

    __property AnsiString Password = {
                    read=FPassword,
                    write=FSetPassword,
                    
                   };
    __property AnsiString Phonebook = {
                    read=FPhonebook,
                    write=FSetPhonebook,
                    
                   };
    __property AnsiString PhonebookEntry = {
                    read=FPhonebookEntry,
                    write=FSetPhonebookEntry,
                    
                   };
    __property AnsiString PhoneNumber = {
                    read=FPhoneNumber,
                    write=FSetPhoneNumber,
                    
                   };
    __property int Timeout = {
                    read=FTimeout,
                    write=FSetTimeout,
                    default=0
                   };
    __property AnsiString User = {
                    read=FUser,
                    write=FSetUser,
                    
                   };


  //EVENTS
    //Fired for every connected device if Action is set to 4 (List Connections) .
    __property TipwNetDialConnectedEntryEvent OnConnectedEntry = {read=FOnConnectedEntry, write=FOnConnectedEntry};
    //Fired for every dial device when Action is set 'List Devices'.
    __property TipwNetDialDeviceEvent OnDevice = {read=FOnDevice, write=FOnDevice};
    //Information about errors during data delivery.
    __property TipwNetDialErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired for every Phonebook entry when Action is set to 3 (List Phonebook Entries) .
    __property TipwNetDialPhonebookEntryEvent OnPhonebookEntry = {read=FOnPhonebookEntry, write=FOnPhonebookEntry};
    //Occurs during connect or disconnect attempts.
    __property TipwNetDialStatusEvent OnStatus = {read=FOnStatus, write=FOnStatus};


}; //end class TipwNetDial

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _NETDIAL_HPP_

