
#ifndef _MIME_HPP_
#define _MIME_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {

enum TipwMIMEActions {
  mimeIdle,
  mimeDecodeFromFile,
  mimeDecodeFromString,
  mimeEncodeToFile,
  mimeEncodeToString,
  mimeResetData
};
enum TipwMIMEPartEncodings {
  pe7Bit,
  peQuotedPrintable,
  peBase64,
  pe8Bit,
  peBinary
};



typedef void __fastcall (__closure* TipwMIMEProgressEvent)(System::TObject* Sender,
                                    int PercentDone);


class PACKAGE TipwMIME : public IPWCore
{
private:
  LONG reserved;
  TipwMIMEProgressEvent FOnProgress;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //Content Disposition for each part 0 to PartCount -1.  //
  AnsiString __fastcall FPartContentDisposition(USHORT PartIdx);
  void __fastcall FSetPartContentDisposition(USHORT PartIdx, AnsiString lpszPartContentDisposition);

  //Array holding the content disposition's attributes, if any, for each part, numbered 0 to PartCount -1.  //
  AnsiString __fastcall FPartContentDispositionAttr(USHORT PartIdx);
  void __fastcall FSetPartContentDispositionAttr(USHORT PartIdx, AnsiString lpszPartContentDispositionAttr);

  //Content id for each part 0 to PartCount -1.  //
  AnsiString __fastcall FPartContentId(USHORT PartIdx);
  void __fastcall FSetPartContentId(USHORT PartIdx, AnsiString lpszPartContentId);

  //Content type for each part 0 to PartCount -1.  //
  AnsiString __fastcall FPartContentType(USHORT PartIdx);
  void __fastcall FSetPartContentType(USHORT PartIdx, AnsiString lpszPartContentType);

  //Array holding the content type attributes, if any, for each part, numbered 0 to PartCount -1.  //
  AnsiString __fastcall FPartContentTypeAttr(USHORT PartIdx);
  void __fastcall FSetPartContentTypeAttr(USHORT PartIdx, AnsiString lpszPartContentTypeAttr);

  //The number of MIME parts in the encoded message.  //
  USHORT __fastcall FPartCount();
  void __fastcall FSetPartCount(USHORT usPartCount);

  //Array holding the filenames with the decoded data numbered 0 to PartCount -1.  //
  AnsiString __fastcall FPartDecodedFile(USHORT PartIdx);
  void __fastcall FSetPartDecodedFile(USHORT PartIdx, AnsiString lpszPartDecodedFile);

  //Array property. It holds the actual content of each part, numbered 0 to PartCount -1.  //
  AnsiString __fastcall FPartDecodedString(USHORT PartIdx);
  void __fastcall FSetPartDecodedString(USHORT PartIdx, AnsiString lpPartDecodedString);
  void __fastcall SetPartDecodedString(USHORT PartIdx, char *lpPartDecodedString, USHORT lenPartDecodedString);


  //The actual content encoding type for each part 0 to PartCount -1.  //
  TipwMIMEPartEncodings __fastcall FPartEncoding(USHORT PartIdx);
  void __fastcall FSetPartEncoding(USHORT PartIdx, TipwMIMEPartEncodings iPartEncoding);

  //The filename attribute specified in the headers of the part.  //
  AnsiString __fastcall FPartFilename(USHORT PartIdx);
  void __fastcall FSetPartFilename(USHORT PartIdx, AnsiString lpszPartFilename);

  //Headers for each MIME part, numbered 0 to PartCount -1.  //
  AnsiString __fastcall FPartHeaders(USHORT PartIdx);
  void __fastcall FSetPartHeaders(USHORT PartIdx, AnsiString lpszPartHeaders);

  //The name given to a part, such as the filename.  //
  AnsiString __fastcall FPartName(USHORT PartIdx);
  void __fastcall FSetPartName(USHORT PartIdx, AnsiString lpszPartName);

  //The size of each PartDecodedFile or PartDecodedString .  //
  long __fastcall FPartSize(USHORT PartIdx);




  //Design-Time Properties
  TipwMIMEActions __fastcall FAction();
  void __fastcall FSetAction(TipwMIMEActions iAction);

  AnsiString __fastcall FBoundary();
  void __fastcall FSetBoundary(AnsiString lpszBoundary);

  AnsiString __fastcall FContentType();
  void __fastcall FSetContentType(AnsiString lpszContentType);

  AnsiString __fastcall FContentTypeAttr();
  void __fastcall FSetContentTypeAttr(AnsiString lpszContentTypeAttr);

  AnsiString __fastcall FMessage();
  void __fastcall FSetMessage(AnsiString lpMessage);
  void __fastcall SetMessage(char *lpMessage, USHORT lenMessage);


  AnsiString __fastcall FMessageHeaders();
  void __fastcall FSetMessageHeaders(AnsiString lpszMessageHeaders);




























  void __fastcall ReadHnd(TStream* Reader);
  void __fastcall WriteHnd(TStream* Writer);

  virtual void __fastcall DefineProperties(TFiler* Filer);

  virtual __fastcall TipwMIME(TComponent* Owner);
  virtual __fastcall TipwMIME(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_28);
  virtual __fastcall ~TipwMIME();


  //Shows the progress of decoding/encoding the input data.  //
  virtual void FireProgress(int PercentDone);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };













  __property AnsiString PartContentDisposition[USHORT PartIdx] = {
               read=FPartContentDisposition,
               write=FSetPartContentDisposition               };

  __property AnsiString PartContentDispositionAttr[USHORT PartIdx] = {
               read=FPartContentDispositionAttr,
               write=FSetPartContentDispositionAttr               };

  __property AnsiString PartContentId[USHORT PartIdx] = {
               read=FPartContentId,
               write=FSetPartContentId               };

  __property AnsiString PartContentType[USHORT PartIdx] = {
               read=FPartContentType,
               write=FSetPartContentType               };

  __property AnsiString PartContentTypeAttr[USHORT PartIdx] = {
               read=FPartContentTypeAttr,
               write=FSetPartContentTypeAttr               };

  __property USHORT PartCount = {
               read=FPartCount,
               write=FSetPartCount               };

  __property AnsiString PartDecodedFile[USHORT PartIdx] = {
               read=FPartDecodedFile,
               write=FSetPartDecodedFile               };

  __property AnsiString PartDecodedString[USHORT PartIdx] = {
               read=FPartDecodedString,
               write=FSetPartDecodedString               };

  __property TipwMIMEPartEncodings PartEncoding[USHORT PartIdx] = {
               read=FPartEncoding,
               write=FSetPartEncoding               };

  __property AnsiString PartFilename[USHORT PartIdx] = {
               read=FPartFilename,
               write=FSetPartFilename               };

  __property AnsiString PartHeaders[USHORT PartIdx] = {
               read=FPartHeaders,
               write=FSetPartHeaders               };

  __property AnsiString PartName[USHORT PartIdx] = {
               read=FPartName,
               write=FSetPartName               };

  __property long PartSize[USHORT PartIdx] = {
               read=FPartSize
               };



  //METHODS
    void __fastcall DecodeFromFile();
    void __fastcall DecodeFromString();
    void __fastcall EncodeToFile();
    void __fastcall EncodeToString();
    void __fastcall ResetData();




__published:

  //PROPERTIES
    __property TipwMIMEActions Action = {
                    read=FAction,
                    write=FSetAction,
                    stored=false

                   };
    __property AnsiString Boundary = {
                    read=FBoundary,
                    write=FSetBoundary,
                    
                   };
    __property AnsiString ContentType = {
                    read=FContentType,
                    write=FSetContentType,
                    
                   };
    __property AnsiString ContentTypeAttr = {
                    read=FContentTypeAttr,
                    write=FSetContentTypeAttr,
                    
                   };
    __property AnsiString Message = {
                    read=FMessage,
                    write=FSetMessage,
                    
                   };
    __property AnsiString MessageHeaders = {
                    read=FMessageHeaders,
                    write=FSetMessageHeaders,
                    
                   };















  //EVENTS
    //Shows the progress of decoding/encoding the input data.
    __property TipwMIMEProgressEvent OnProgress = {read=FOnProgress, write=FOnProgress};


}; //end class TipwMIME

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _MIME_HPP_

