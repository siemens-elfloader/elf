
#ifndef _NETCODE_HPP_
#define _NETCODE_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

enum TipwNetCodeActions {
  netcodeIdle,
  netcodeDecodeToFile,
  netcodeEncodeToFile,
  netcodeDecodeToString,
  netcodeEncodeToString
};
enum TipwNetCodeFormats {
  fmtUUEncode,
  fmtBASE64,
  fmtQP,
  fmtURL,
  fmtJIS
};



typedef void __fastcall (__closure* TipwNetCodeProgressEvent)(System::TObject* Sender,
                                    int PercentDone);


class PACKAGE TipwNetCode : public IPWCore
{
private:
  LONG reserved;
  TipwNetCodeProgressEvent FOnProgress;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);



  //Design-Time Properties
  TipwNetCodeActions __fastcall FAction();
  void __fastcall FSetAction(TipwNetCodeActions iAction);

  AnsiString __fastcall FDecodedData();
  void __fastcall FSetDecodedData(AnsiString lpDecodedData);
  void __fastcall SetDecodedData(char *lpDecodedData, USHORT lenDecodedData);


  AnsiString __fastcall FEncodedData();
  void __fastcall FSetEncodedData(AnsiString lpEncodedData);
  void __fastcall SetEncodedData(char *lpEncodedData, USHORT lenEncodedData);


  int __fastcall FFileCnt();


  AnsiString __fastcall FFileName();
  void __fastcall FSetFileName(AnsiString lpszFileName);

  TipwNetCodeFormats __fastcall FFormat();
  void __fastcall FSetFormat(TipwNetCodeFormats iFormat);

  bool __fastcall FIntelliCode();
  void __fastcall FSetIntelliCode(bool bIntelliCode);

  long __fastcall FMaxFileSize();
  void __fastcall FSetMaxFileSize(long lMaxFileSize);

  AnsiString __fastcall FMode();
  void __fastcall FSetMode(AnsiString lpszMode);

  bool __fastcall FOverwrite();
  void __fastcall FSetOverwrite(bool bOverwrite);

  USHORT __fastcall FProgressStep();
  void __fastcall FSetProgressStep(USHORT usProgressStep);


  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwNetCode(TComponent* Owner);
  virtual __fastcall TipwNetCode(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_14);
  virtual __fastcall ~TipwNetCode();


  //Occurs when PercentDone of the input is read.  //
  virtual void FireProgress(int PercentDone);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };

























  //METHODS
    void __fastcall DecodeToFile();
    void __fastcall DecodeToString();
    void __fastcall EncodeToFile();
    void __fastcall EncodeToString();




__published:

  //PROPERTIES
    __property TipwNetCodeActions Action = {
                    read=FAction,
                    write=FSetAction,
                    stored=false

                   };
    __property AnsiString DecodedData = {
                    read=FDecodedData,
                    write=FSetDecodedData,
                    
                   };
    __property AnsiString EncodedData = {
                    read=FEncodedData,
                    write=FSetEncodedData,
                    
                   };
    __property int FileCnt = {
                    read=FFileCnt,
                    write=SetDummyint,
                    stored=false

                   };
    __property AnsiString FileName = {
                    read=FFileName,
                    write=FSetFileName,
                    
                   };
    __property TipwNetCodeFormats Format = {
                    read=FFormat,
                    write=FSetFormat,
                    default=fmtUUEncode
                   };
    __property bool IntelliCode = {
                    read=FIntelliCode,
                    write=FSetIntelliCode,
                    default=true
                   };
    __property long MaxFileSize = {
                    read=FMaxFileSize,
                    write=FSetMaxFileSize,
                    default=0
                   };
    __property AnsiString Mode = {
                    read=FMode,
                    write=FSetMode,
                    
                   };
    __property bool Overwrite = {
                    read=FOverwrite,
                    write=FSetOverwrite,
                    default=false
                   };
    __property USHORT ProgressStep = {
                    read=FProgressStep,
                    write=FSetProgressStep,
                    default=1
                   };


  //EVENTS
    //Occurs when PercentDone of the input is read.
    __property TipwNetCodeProgressEvent OnProgress = {read=FOnProgress, write=FOnProgress};


}; //end class TipwNetCode

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _NETCODE_HPP_

