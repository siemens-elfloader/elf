
#ifndef _XMLP_HPP_
#define _XMLP_HPP_
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IP*Works! V5 C++Builder Edition
// Copyright (c) 2003 /n software inc. - All rights reserved.
// www.nsoftware.com
//----------------------------------------------------------------------------

#pragma hdrstop
#include "ipwCore.h"

namespace Ipworks {




typedef void __fastcall (__closure* TipwXMLpCharactersEvent)(System::TObject* Sender,
                                    char * Text, USHORT lenText);
typedef void __fastcall (__closure* TipwXMLpCommentEvent)(System::TObject* Sender,
                                    AnsiString& Text);
typedef void __fastcall (__closure* TipwXMLpEndElementEvent)(System::TObject* Sender,
                                    AnsiString& Namespace,
                                    AnsiString& Element,
                                    AnsiString& QName,
                                    bool IsEmpty);
typedef void __fastcall (__closure* TipwXMLpEndPrefixMappingEvent)(System::TObject* Sender,
                                    AnsiString& Prefix);
typedef void __fastcall (__closure* TipwXMLpErrorEvent)(System::TObject* Sender,
                                    int ErrorCode,
                                    AnsiString& Description);
typedef void __fastcall (__closure* TipwXMLpEvalEntityEvent)(System::TObject* Sender,
                                    AnsiString& Entity,
                                    AnsiString& Value);
typedef void __fastcall (__closure* TipwXMLpIgnorableWhitespaceEvent)(System::TObject* Sender,
                                    AnsiString& Text);
typedef void __fastcall (__closure* TipwXMLpMetaEvent)(System::TObject* Sender,
                                    AnsiString& Text);
typedef void __fastcall (__closure* TipwXMLpPIEvent)(System::TObject* Sender,
                                    AnsiString& Text);
typedef void __fastcall (__closure* TipwXMLpSpecialSectionEvent)(System::TObject* Sender,
                                    AnsiString& SectionId,
                                    AnsiString& Text);
typedef void __fastcall (__closure* TipwXMLpStartElementEvent)(System::TObject* Sender,
                                    AnsiString& Namespace,
                                    AnsiString& Element,
                                    AnsiString& QName,
                                    bool IsEmpty);
typedef void __fastcall (__closure* TipwXMLpStartPrefixMappingEvent)(System::TObject* Sender,
                                    AnsiString& Prefix,
                                    AnsiString& URI);


class PACKAGE TipwXMLp : public IPWCore
{
private:
  LONG reserved;
  TipwXMLpCharactersEvent FOnCharacters;
  TipwXMLpCommentEvent FOnComment;
  TipwXMLpEndElementEvent FOnEndElement;
  TipwXMLpEndPrefixMappingEvent FOnEndPrefixMapping;
  TipwXMLpErrorEvent FOnError;
  TipwXMLpEvalEntityEvent FOnEvalEntity;
  TipwXMLpIgnorableWhitespaceEvent FOnIgnorableWhitespace;
  TipwXMLpMetaEvent FOnMeta;
  TipwXMLpPIEvent FOnPI;
  TipwXMLpSpecialSectionEvent FOnSpecialSection;
  TipwXMLpStartElementEvent FOnStartElement;
  TipwXMLpStartPrefixMappingEvent FOnStartPrefixMapping;


protected:
  void __fastcall virtual AboutDlg();
  void __fastcall TreatErr(int err);

public:

  //Accessing Run-Time Properties

  long __fastcall FCharsetMode();
  void __fastcall FSetCharsetMode(long lVal);

  //Size of attribute values array for the current element.  //
  int __fastcall FAttrCount();


  //Array of attribute names for the current element.  //
  AnsiString __fastcall FAttrName(USHORT AttrIndex);


  //Array of attribute namespaces for the current element.  //
  AnsiString __fastcall FAttrNamespace(USHORT AttrIndex);


  //Array of attribute prefixes for the current element.  //
  AnsiString __fastcall FAttrPrefix(USHORT AttrIndex);


  //Array of attribute values for the current element.  //
  AnsiString __fastcall FAttrValue(USHORT AttrIndex);


  //Number of elements in the current element stack.  //
  int __fastcall FElementCount();


  //The elements in the current element stack.  //
  AnsiString __fastcall FElements(USHORT ElementIndex);


  //Extra characters for the parser to consider as name characters.  //
  AnsiString __fastcall FExtraNameChars();
  void __fastcall FSetExtraNameChars(AnsiString lpszExtraNameChars);

  //Extra characters for the parser to consider as white space.  //
  AnsiString __fastcall FExtraSpaceChars();
  void __fastcall FSetExtraSpaceChars(AnsiString lpszExtraSpaceChars);

  //Flags controlling the behaviour of the parser.  //
  long __fastcall FFlags();
  void __fastcall FSetFlags(long lFlags);

  //When set, the parser flushes all text, and checks its end state.  //

  void __fastcall FSetFlushText(bool bFlushText);

  //Provides input to the parser.  Write-only property.  //

  void __fastcall FSetInputText(AnsiString lpszInputText);

  //The number of namespaces in the current namespace stack.  //
  int __fastcall FNamespaceCount();


  //The namespaces in the current namespace stack.  //
  AnsiString __fastcall FNamespaces(USHORT NamespaceIndex);


  //Current offset of the document being parsed.  //
  long __fastcall FOffset();


  //The namespace prefixes in the current namespace stack.  //
  AnsiString __fastcall FPrefixes(USHORT NamespaceIndex);


  //When set, the parser initializes itself to its default state.  //

  void __fastcall FSetResetText(bool bResetText);



  //Design-Time Properties










  bool __fastcall FBuildDOM();
  void __fastcall FSetBuildDOM(bool bBuildDOM);











  bool __fastcall FFlushOnEOL();
  void __fastcall FSetFlushOnEOL(bool bFlushOnEOL);















  bool __fastcall FValidate();
  void __fastcall FSetValidate(bool bValidate);

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

  virtual __fastcall TipwXMLp(TComponent* Owner);
  virtual __fastcall TipwXMLp(TComponent* Owner, bool Registered, LPSTR lpKey=IPWORKS_OEMKEY_54);
  virtual __fastcall ~TipwXMLp();


  //Fired for plain text segments of the input stream.  //
  virtual void FireCharacters(char* Text, USHORT lenText);
  //Fired when a comment section is encountered.  //
  virtual void FireComment(char* Text);
  //Fired when an end-element tag is encountered.  //
  virtual void FireEndElement(char* Namespace, char* Element, char* QName, bool IsEmpty);
  //Fired when leaving the scope of a namespace declaration.  //
  virtual void FireEndPrefixMapping(char* Prefix);
  //Information about errors during data delivery.  //
  virtual void FireError(int ErrorCode, char* Description);
  //Fired every time an entity needs to be evaluated.  //
  virtual void FireEvalEntity(char* Entity, char*& Value);
  //Fired when a section of ignorable whitespace is encountered.  //
  virtual void FireIgnorableWhitespace(char* Text);
  //Fired when a meta section is encountered.  //
  virtual void FireMeta(char* Text);
  //Fired when a processing instruction section is encountered.  //
  virtual void FirePI(char* Text);
  //Fired when a special section is encountered.  //
  virtual void FireSpecialSection(char* SectionId, char* Text);
  //Fired when a begin-element tag is encountered in the document.  //
  virtual void FireStartElement(char* Namespace, char* Element, char* QName, bool IsEmpty);
  //Fired when entering the scope of a namespace declaration.  //
  virtual void FireStartPrefixMapping(char* Prefix, char* URI);



  //RUNTIME PROPERTIES

  __property long CharsetMode = {
                read=FCharsetMode,
                write=FSetCharsetMode
               };

  __property int AttrCount = {
               read=FAttrCount
               };

  __property AnsiString AttrName[USHORT AttrIndex] = {
               read=FAttrName
               };

  __property AnsiString AttrNamespace[USHORT AttrIndex] = {
               read=FAttrNamespace
               };

  __property AnsiString AttrPrefix[USHORT AttrIndex] = {
               read=FAttrPrefix
               };

  __property AnsiString AttrValue[USHORT AttrIndex] = {
               read=FAttrValue
               };



  __property int ElementCount = {
               read=FElementCount
               };

  __property AnsiString Elements[USHORT ElementIndex] = {
               read=FElements
               };

  __property AnsiString ExtraNameChars = {
               read=FExtraNameChars,
               write=FSetExtraNameChars               };

  __property AnsiString ExtraSpaceChars = {
               read=FExtraSpaceChars,
               write=FSetExtraSpaceChars               };

  __property long Flags = {
               read=FFlags,
               write=FSetFlags               };



  __property bool FlushText = {

               write=FSetFlushText               };

  __property AnsiString InputText = {

               write=FSetInputText               };

  __property int NamespaceCount = {
               read=FNamespaceCount
               };

  __property AnsiString Namespaces[USHORT NamespaceIndex] = {
               read=FNamespaces
               };

  __property long Offset = {
               read=FOffset
               };

  __property AnsiString Prefixes[USHORT NamespaceIndex] = {
               read=FPrefixes
               };

  __property bool ResetText = {

               write=FSetResetText               };



















  //METHODS
    AnsiString __fastcall Attr(AnsiString AttrName);
    void __fastcall Flush();
    void __fastcall Input(AnsiString Text);
    void __fastcall ParseFile(AnsiString FileName);
    void __fastcall Reset();




__published:

  //PROPERTIES





    __property bool BuildDOM = {
                    read=FBuildDOM,
                    write=FSetBuildDOM,
                    default=true
                   };





    __property bool FlushOnEOL = {
                    read=FFlushOnEOL,
                    write=FSetFlushOnEOL,
                    default=true
                   };







    __property bool Validate = {
                    read=FValidate,
                    write=FSetValidate,
                    default=true
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
    //Fired for plain text segments of the input stream.
    __property TipwXMLpCharactersEvent OnCharacters = {read=FOnCharacters, write=FOnCharacters};
    //Fired when a comment section is encountered.
    __property TipwXMLpCommentEvent OnComment = {read=FOnComment, write=FOnComment};
    //Fired when an end-element tag is encountered.
    __property TipwXMLpEndElementEvent OnEndElement = {read=FOnEndElement, write=FOnEndElement};
    //Fired when leaving the scope of a namespace declaration.
    __property TipwXMLpEndPrefixMappingEvent OnEndPrefixMapping = {read=FOnEndPrefixMapping, write=FOnEndPrefixMapping};
    //Information about errors during data delivery.
    __property TipwXMLpErrorEvent OnError = {read=FOnError, write=FOnError};
    //Fired every time an entity needs to be evaluated.
    __property TipwXMLpEvalEntityEvent OnEvalEntity = {read=FOnEvalEntity, write=FOnEvalEntity};
    //Fired when a section of ignorable whitespace is encountered.
    __property TipwXMLpIgnorableWhitespaceEvent OnIgnorableWhitespace = {read=FOnIgnorableWhitespace, write=FOnIgnorableWhitespace};
    //Fired when a meta section is encountered.
    __property TipwXMLpMetaEvent OnMeta = {read=FOnMeta, write=FOnMeta};
    //Fired when a processing instruction section is encountered.
    __property TipwXMLpPIEvent OnPI = {read=FOnPI, write=FOnPI};
    //Fired when a special section is encountered.
    __property TipwXMLpSpecialSectionEvent OnSpecialSection = {read=FOnSpecialSection, write=FOnSpecialSection};
    //Fired when a begin-element tag is encountered in the document.
    __property TipwXMLpStartElementEvent OnStartElement = {read=FOnStartElement, write=FOnStartElement};
    //Fired when entering the scope of a namespace declaration.
    __property TipwXMLpStartPrefixMappingEvent OnStartPrefixMapping = {read=FOnStartPrefixMapping, write=FOnStartPrefixMapping};


}; //end class TipwXMLp

}//end namespace Ipworks

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ipworks;
#endif

//-- end unit ----------------------------------------------------------------
#endif  // _XMLP_HPP_

