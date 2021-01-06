// Borland C++ Builder
// Copyright (c) 2002 Borland Software Corporation
// All rights reserved

#ifndef XMLNodeImp_h
#define XMLNodeImp_h


// Template class to delegate all IXMLNode methods to TXMLNode for
// XML Data Binding classes.

template <typename T, typename IMPL>
class IXMLNodeImpl : public T
{
public:
  virtual HRESULT __stdcall QueryInterface(const GUID& IID, void **Obj)  {
    return static_cast<T*>(this)->IMPL::QueryInterface(IID, (void**)Obj);
  }
  virtual ULONG __stdcall AddRef() {
    return static_cast<T*>(this)->IMPL::_AddRef();
  }
  virtual ULONG __stdcall Release()  {
    return static_cast<T*>(this)->IMPL::_Release();
  }
  virtual OleVariant __fastcall GetAttribute(const WideString AttrName){
    return static_cast<T*>(this)->IMPL::GetAttribute(AttrName);
  }
  virtual _di_IXMLNodeList __fastcall GetAttributeNodes(){
    return static_cast<T*>(this)->IMPL::GetAttributeNodes();
  }
  virtual _di_IXMLNodeList __fastcall GetChildNodes(){
    return static_cast<T*>(this)->IMPL::GetChildNodes();
  }
  virtual OleVariant __fastcall GetChildValue(const OleVariant &IndexOrName){
    return static_cast<T*>(this)->IMPL::GetChildValue(IndexOrName);
  }
  virtual _di_IXMLNodeCollection __fastcall GetCollection(){
    return static_cast<T*>(this)->IMPL::GetCollection();
  }
  virtual Xmldom::_di_IDOMNode __fastcall GetDOMNode(){
    return static_cast<T*>(this)->IMPL::GetDOMNode();
  }
  virtual bool __fastcall GetHasChildNodes(){
    return static_cast<T*>(this)->IMPL::GetHasChildNodes();
  }
  virtual bool __fastcall GetIsTextElement(){
    return static_cast<T*>(this)->IMPL::GetIsTextElement();
  }
  virtual WideString __fastcall GetLocalName(){
    return static_cast<T*>(this)->IMPL::GetLocalName();
  }
  virtual WideString __fastcall GetNamespaceURI(){
    return static_cast<T*>(this)->IMPL::GetNamespaceURI();
  }
  virtual WideString __fastcall GetNodeName(){
    return static_cast<T*>(this)->IMPL::GetNodeName();
  }
  virtual TNodeType __fastcall GetNodeType(){
    return static_cast<T*>(this)->IMPL::GetNodeType();
  }
  virtual OleVariant __fastcall GetNodeValue(){
    return static_cast<T*>(this)->IMPL::GetNodeValue();
  }
  virtual _di_IXMLDocument __fastcall GetOwnerDocument(){
    return static_cast<T*>(this)->IMPL::GetOwnerDocument();
  }
  virtual _di_IXMLNode __fastcall GetParentNode(){
    return static_cast<T*>(this)->IMPL::GetParentNode();
  }
  virtual WideString __fastcall GetPrefix(){
    return static_cast<T*>(this)->IMPL::GetPrefix();
  }
  virtual bool __fastcall GetReadOnly(){
    return static_cast<T*>(this)->IMPL::GetReadOnly();
  }
  virtual WideString __fastcall GetText(){
    return static_cast<T*>(this)->IMPL::GetText();
  }
  virtual WideString __fastcall GetXML(){
    return static_cast<T*>(this)->IMPL::GetXML();
  }
  virtual void __fastcall SetAttribute(const WideString AttrName, const OleVariant &Value){
    static_cast<T*>(this)->IMPL::SetAttribute(AttrName, Value);
  }
  virtual void __fastcall SetChildValue(const OleVariant &IndexOrName, const OleVariant &Value){
    static_cast<T*>(this)->IMPL::SetChildValue(IndexOrName, Value);
  }
  virtual void __fastcall SetNodeValue(const OleVariant &Value){
    static_cast<T*>(this)->IMPL::SetNodeValue(Value);
  }
  virtual void __fastcall SetReadOnly(const bool Value){
    static_cast<T*>(this)->IMPL::SetReadOnly(Value);
  }
  virtual void __fastcall SetText(const WideString Value){
    static_cast<T*>(this)->IMPL::SetText(Value);
  }
  virtual _di_IXMLNode __fastcall AddChild(const WideString TagName, int Index = 0xffffffff){
    return static_cast<T*>(this)->IMPL::AddChild(TagName, Index);
  }
  virtual _di_IXMLNode __fastcall AddChild(const WideString TagName, const WideString NamespaceURI, bool GenPrefix = false, int Index = 0xffffffff){
    return static_cast<T*>(this)->IMPL::AddChild(TagName, NamespaceURI, GenPrefix, Index);
  }
  virtual _di_IXMLNode __fastcall CloneNode(bool Deep){
    return static_cast<T*>(this)->IMPL::CloneNode(Deep);
  }
  virtual void __fastcall DeclareNamespace(const WideString Prefix, const WideString URI){
    static_cast<T*>(this)->IMPL::DeclareNamespace(Prefix, URI);
  }
  virtual WideString __fastcall FindNamespaceURI(const WideString TagOrPrefix){
    return static_cast<T*>(this)->IMPL::FindNamespaceURI(TagOrPrefix);
  }
  virtual _di_IXMLNode __fastcall FindNamespaceDecl(const WideString NamespaceURI){
    return static_cast<T*>(this)->IMPL::FindNamespaceDecl(NamespaceURI);
  }
  virtual OleVariant __fastcall GetAttributeNS(const WideString AttrName, const WideString NamespaceURI){
    return static_cast<T*>(this)->IMPL::GetAttributeNS(AttrName, NamespaceURI);
  }
  virtual bool __fastcall HasAttribute(const WideString Name){
    return static_cast<T*>(this)->IMPL::HasAttribute(Name);
  }
  virtual bool __fastcall HasAttribute(const WideString Name, const WideString NamespaceURI){
    return static_cast<T*>(this)->IMPL::HasAttribute(Name, NamespaceURI);
  }
  virtual _di_IXMLNode __fastcall NextSibling(){
    return static_cast<T*>(this)->IMPL::NextSibling();
  }
  virtual void __fastcall Normalize(){
    return static_cast<T*>(this)->IMPL::Normalize();
  }
  virtual _di_IXMLNode __fastcall PreviousSibling(){
    return static_cast<T*>(this)->IMPL::PreviousSibling();
  }
  virtual void __fastcall Resync(){
    static_cast<T*>(this)->IMPL::Resync();
  }
  virtual void __fastcall SetAttributeNS(const WideString AttrName, const WideString NamespaceURI, const OleVariant &Value){
    static_cast<T*>(this)->IMPL::SetAttributeNS(AttrName, NamespaceURI, Value);
  }
  virtual void __fastcall TransformNode(const _di_IXMLNode stylesheet, WideString &output){
    static_cast<T*>(this)->IMPL::TransformNode(stylesheet, output);
  }
  virtual void __fastcall TransformNode(const _di_IXMLNode stylesheet, const _di_IXMLDocument output){
    static_cast<T*>(this)->IMPL::TransformNode(stylesheet, output);
  }
};

// Macro to delegate all IXMLNode methods to TXMLNode for
// XML Data Binding classes.

#define __IXMLNODE_IMPL__ \
  virtual HRESULT __stdcall QueryInterface(const GUID& IID, void **Obj)  { \
    return TXMLNode::QueryInterface(IID, (void**)Obj); \
  } \
  virtual ULONG __stdcall AddRef() { \
    return TXMLNode::_AddRef(); \
  } \
  virtual ULONG __stdcall Release()  { \
    return TXMLNode::_Release(); \
  } \
  virtual OleVariant __fastcall GetAttribute(const WideString AttrName){ \
    return TXMLNode::GetAttribute(AttrName); \
  } \
  virtual _di_IXMLNodeList __fastcall GetAttributeNodes(){ \
    return TXMLNode::GetAttributeNodes(); \
  } \
  virtual _di_IXMLNodeList __fastcall GetChildNodes(){ \
    return TXMLNode::GetChildNodes(); \
  } \
  virtual OleVariant __fastcall GetChildValue(const OleVariant &IndexOrName){ \
    return TXMLNode::GetChildValue(IndexOrName); \
  } \
  virtual _di_IXMLNodeCollection __fastcall GetCollection(){ \
    return TXMLNode::GetCollection(); \
  } \
  virtual Xmldom::_di_IDOMNode __fastcall GetDOMNode(){ \
    return TXMLNode::GetDOMNode(); \
  } \
  virtual bool __fastcall GetHasChildNodes(){ \
    return TXMLNode::GetHasChildNodes(); \
  } \
  virtual bool __fastcall GetIsTextElement(){ \
    return TXMLNode::GetIsTextElement(); \
  } \
  virtual WideString __fastcall GetLocalName(){ \
    return TXMLNode::GetLocalName(); \
  } \
  virtual WideString __fastcall GetNamespaceURI(){ \
    return TXMLNode::GetNamespaceURI(); \
  } \
  virtual WideString __fastcall GetNodeName(){ \
    return TXMLNode::GetNodeName(); \
  } \
  virtual TNodeType __fastcall GetNodeType(){ \
    return TXMLNode::GetNodeType(); \
  } \
  virtual OleVariant __fastcall GetNodeValue(){ \
    return TXMLNode::GetNodeValue(); \
  } \
  virtual _di_IXMLDocument __fastcall GetOwnerDocument(){ \
    return TXMLNode::GetOwnerDocument(); \
  } \
  virtual _di_IXMLNode __fastcall GetParentNode(){ \
    return TXMLNode::GetParentNode(); \
  } \
  virtual WideString __fastcall GetPrefix(){ \
    return TXMLNode::GetPrefix(); \
  } \
  virtual bool __fastcall GetReadOnly(){ \
    return TXMLNode::GetReadOnly(); \
  } \
  virtual WideString __fastcall GetText(){ \
    return TXMLNode::GetText(); \
  } \
  virtual WideString __fastcall GetXML(){ \
    return TXMLNode::GetXML(); \
  } \
  virtual void __fastcall SetAttribute(const WideString AttrName, const OleVariant &Value){ \
    TXMLNode::SetAttribute(AttrName, Value); \
  } \
  virtual void __fastcall SetChildValue(const OleVariant &IndexOrName, const OleVariant &Value){ \
    TXMLNode::SetChildValue(IndexOrName, Value); \
  } \
  virtual void __fastcall SetNodeValue(const OleVariant &Value){ \
    TXMLNode::SetNodeValue(Value); \
  } \
  virtual void __fastcall SetReadOnly(const bool Value){ \
    TXMLNode::SetReadOnly(Value); \
  } \
  virtual void __fastcall SetText(const WideString Value){ \
    TXMLNode::SetText(Value); \
  } \
  virtual _di_IXMLNode __fastcall AddChild(const WideString TagName, int Index = 0xffffffff){ \
    return TXMLNode::AddChild(TagName, Index); \
  } \
  virtual _di_IXMLNode __fastcall AddChild(const WideString TagName, const WideString NamespaceURI, bool GenPrefix = false, int Index = 0xffffffff){ \
    return TXMLNode::AddChild(TagName, NamespaceURI, GenPrefix, Index); \
  } \
  virtual _di_IXMLNode __fastcall CloneNode(bool Deep){ \
    return TXMLNode::CloneNode(Deep); \
  } \
  virtual void __fastcall DeclareNamespace(const WideString Prefix, const WideString URI){ \
    TXMLNode::DeclareNamespace(Prefix, URI); \
  } \
  virtual WideString __fastcall FindNamespaceURI(const WideString TagOrPrefix){ \
    return TXMLNode::FindNamespaceURI(TagOrPrefix); \
  } \
  virtual _di_IXMLNode __fastcall FindNamespaceDecl(const WideString NamespaceURI){ \
    return TXMLNode::FindNamespaceDecl(NamespaceURI); \
  } \
  virtual OleVariant __fastcall GetAttributeNS(const WideString AttrName, const WideString NamespaceURI){ \
    return TXMLNode::GetAttributeNS(AttrName, NamespaceURI); \
  } \
  virtual bool __fastcall HasAttribute(const WideString Name){ \
    return TXMLNode::HasAttribute(Name); \
  } \
  virtual bool __fastcall HasAttribute(const WideString Name, const WideString NamespaceURI){ \
    return TXMLNode::HasAttribute(Name, NamespaceURI); \
  } \
  virtual _di_IXMLNode __fastcall NextSibling(){ \
    return TXMLNode::NextSibling(); \
  } \
  virtual void __fastcall Normalize(){ \
    return TXMLNode::Normalize(); \
  } \
  virtual _di_IXMLNode __fastcall PreviousSibling(){ \
    return TXMLNode::PreviousSibling(); \
  } \
  virtual void __fastcall Resync(){ \
    TXMLNode::Resync(); \
  } \
  virtual void __fastcall SetAttributeNS(const WideString AttrName, const WideString NamespaceURI, const OleVariant &Value){ \
    TXMLNode::SetAttributeNS(AttrName, NamespaceURI, Value); \
  } \
  virtual void __fastcall TransformNode(const _di_IXMLNode stylesheet, WideString &output){ \
    TXMLNode::TransformNode(stylesheet, output); \
  } \
  virtual void __fastcall TransformNode(const _di_IXMLNode stylesheet, const _di_IXMLDocument output){ \
    TXMLNode::TransformNode(stylesheet, output); \
  }

// Macro to delegate all IXMLNodeCollection methods to TXMLNodeCollection for
// XML Data Binding classes.

#define __IXMLNODECOLLECTION_IMPL__ \
    __IXMLNODE_IMPL__ \
	virtual int __fastcall GetCount(){ \
      return TXMLNodeCollection::GetCount(); \
    } \
	virtual _di_IXMLNode __fastcall GetNode(int Index){ \
      return TXMLNodeCollection::GetNode(Index); \
    } \
	virtual void __fastcall Clear(){ \
      TXMLNodeCollection::Clear(); \
    } \
	virtual void __fastcall Delete(int Index){ \
      TXMLNodeCollection::Delete(Index); \
    } \
	virtual int __fastcall Remove(const _di_IXMLNode Node){ \
      return TXMLNodeCollection::Remove(Node); \
    } \

#endif


