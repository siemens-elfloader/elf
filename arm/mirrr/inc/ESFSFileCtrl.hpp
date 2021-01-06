// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ESFSFileCtrl.pas' rev: 6.00

#ifndef ESFSFileCtrlHPP
#define ESFSFileCtrlHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Esfsfilectrl
{
//-- type declarations -------------------------------------------------------
struct TESFSHugeFilePartitionHeader
{
	char Signature[8];
	__int64 PartitionSize;
	char NextFileName[261];
} ;

class DELPHICLASS TESFSAbstractFile;
class PASCALIMPLEMENTATION TESFSAbstractFile : public System::TObject 
{
	typedef System::TObject inherited;
	
protected:
	AnsiString FFileName;
	bool FExclusive;
	bool FReadOnly;
	virtual void __fastcall SetExclusive(bool value);
	virtual void __fastcall SetPosition(int Pos);
	virtual int __fastcall GetPosition(void);
	virtual void __fastcall SetReadOnly(bool value);
	virtual void __fastcall SetSize(int value) = 0 ;
	virtual int __fastcall GetSize(void);
	
public:
	__fastcall virtual TESFSAbstractFile(AnsiString FileName, bool bReadOnly, bool bExclusive);
	int __fastcall CopyFrom(TESFSAbstractFile* Source, int Count);
	virtual void __fastcall Close(void) = 0 ;
	virtual void __fastcall FlushBuffers(void) = 0 ;
	virtual bool __fastcall Open(bool bCreate) = 0 ;
	virtual int __fastcall Read(void *Buffer, int Count) = 0 ;
	void __fastcall ReadBuffer(void *Buffer, int Count);
	virtual int __fastcall Seek(int Offset, Word Origin) = 0 ;
	virtual int __fastcall Write(const void *Buffer, int Count) = 0 ;
	void __fastcall WriteBuffer(const void *Buffer, int Count);
	
__published:
	__property bool Exclusive = {read=FExclusive, write=SetExclusive, default=0};
	__property AnsiString FileName = {read=FFileName, write=FFileName};
	__property int Position = {read=GetPosition, write=SetPosition, default=0};
	__property bool ReadOnly = {read=FReadOnly, write=SetReadOnly, default=0};
	__property int Size = {read=GetSize, write=SetSize, default=0};
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TESFSAbstractFile(void) { }
	#pragma option pop
	
};


class DELPHICLASS TESFSDiskFile;
class PASCALIMPLEMENTATION TESFSDiskFile : public TESFSAbstractFile 
{
	typedef TESFSAbstractFile inherited;
	
private:
	int FHandle;
	AnsiString FDirectory;
	void __fastcall Reopen(void);
	
protected:
	bool __fastcall InternalOpen(const AnsiString FileName, bool bCreate);
	virtual void __fastcall SetExclusive(bool value);
	virtual void __fastcall SetReadOnly(bool value);
	virtual void __fastcall SetSize(int value);
	
public:
	__fastcall virtual TESFSDiskFile(AnsiString FileName, bool bReadOnly, bool bExclusive);
	virtual void __fastcall Close(void);
	__fastcall virtual ~TESFSDiskFile(void);
	virtual void __fastcall FlushBuffers(void);
	virtual bool __fastcall Open(bool bCreate);
	virtual int __fastcall Read(void *Buffer, int Count);
	virtual int __fastcall Seek(int Offset, Word Origin);
	virtual int __fastcall Write(const void *Buffer, int Count);
	
__published:
	__property bool Exclusive = {read=FExclusive, write=SetExclusive, default=0};
	__property AnsiString FileName = {read=FFileName, write=FFileName};
	__property bool ReadOnly = {read=FReadOnly, write=SetReadOnly, default=0};
	__property int Position = {read=GetPosition, write=SetPosition, default=0};
	__property int Size = {read=GetSize, write=SetSize, default=0};
};


class DELPHICLASS TESFSMemoryFile;
class PASCALIMPLEMENTATION TESFSMemoryFile : public TESFSAbstractFile 
{
	typedef TESFSAbstractFile inherited;
	
private:
	Classes::TMemoryStream* FStream;
	
protected:
	virtual void __fastcall SetSize(int value);
	
public:
	__fastcall virtual TESFSMemoryFile(AnsiString FileName, bool bReadOnly, bool bExclusive);
	virtual void __fastcall Close(void);
	__fastcall virtual ~TESFSMemoryFile(void);
	virtual void __fastcall FlushBuffers(void);
	virtual bool __fastcall Open(bool bCreate);
	virtual int __fastcall Read(void *Buffer, int Count);
	virtual int __fastcall Seek(int Offset, Word Origin);
	virtual int __fastcall Write(const void *Buffer, int Count);
	
__published:
	__property bool Exclusive = {read=FExclusive, write=SetExclusive, default=0};
	__property AnsiString FileName = {read=FFileName, write=FFileName};
	__property bool ReadOnly = {read=FReadOnly, write=SetReadOnly, default=0};
	__property int Position = {read=GetPosition, write=SetPosition, default=0};
	__property int Size = {read=GetSize, write=SetSize, default=0};
};


typedef DynamicArray<TESFSAbstractFile* >  ESFSFileCtrl__5;

class DELPHICLASS TESFSHugeFile;
class PASCALIMPLEMENTATION TESFSHugeFile : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	AnsiString FFileName;
	bool FExclusive;
	bool FReadOnly;
	bool FInMemory;
	__int64 FPosition;
	__int64 FSize;
	__int64 FPartitionSize;
	__int64 FPartitionDataSize;
	DynamicArray<TESFSAbstractFile* >  PartFiles;
	bool IsFileOpen;
	__int64 FStubSize;
	void __fastcall GetFileNoAndOffset(__int64 Pos, int &FileNo, __int64 &Offset);
	void __fastcall InitPartHeader(TESFSHugeFilePartitionHeader &HFPartHeader);
	bool __fastcall AppendPartFile(void);
	void __fastcall DeleteLastPartFile(void);
	bool __fastcall OpenFilesChain(const AnsiString FileName);
	bool __fastcall InternalOpen(const AnsiString FileName, bool bCreate, bool bIgnoreErrors = false);
	void __fastcall SetExclusive(bool value);
	void __fastcall SetInMemory(bool value);
	void __fastcall SetPosition(__int64 Pos);
	__int64 __fastcall GetPosition(void);
	void __fastcall SetReadOnly(bool value);
	void __fastcall SetSize(__int64 value);
	__int64 __fastcall GetSize(void);
	void __fastcall CalculateStubSize(TESFSAbstractFile* FFile);
	
public:
	__fastcall TESFSHugeFile(AnsiString FileName, bool bReadOnly, bool bExclusive, bool bInMemory, __int64 PartitionSize);
	__fastcall virtual ~TESFSHugeFile(void);
	__int64 __fastcall CopyFrom(TESFSHugeFile* Source, __int64 Count);
	void __fastcall SaveToStream(Classes::TStream* Stream);
	void __fastcall LoadFromStream(Classes::TStream* Stream);
	void __fastcall Close(void);
	void __fastcall FlushBuffers(void);
	bool __fastcall Open(bool bCreate, bool bIgnoreErrors = false);
	int __fastcall Read(void *Buffer, int Count);
	void __fastcall ReadBuffer(void *Buffer, int Count);
	__int64 __fastcall Seek(__int64 Offset, Word Origin);
	int __fastcall Write(const void *Buffer, int Count);
	void __fastcall WriteBuffer(const void *Buffer, int Count);
	bool __fastcall CopyFile(const AnsiString NewName);
	bool __fastcall RenameFile(const AnsiString NewName);
	bool __fastcall DeleteFile(void);
	
__published:
	__property bool Exclusive = {read=FExclusive, write=SetExclusive, default=0};
	__property AnsiString FileName = {read=FFileName, write=FFileName};
	__property __int64 Position = {read=GetPosition, write=SetPosition, default=0};
	__property bool ReadOnly = {read=FReadOnly, write=SetReadOnly, default=0};
	__property __int64 Size = {read=GetSize, write=SetSize, default=0};
	__property bool InMemory = {read=FInMemory, write=SetInMemory, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE char HFSignature[8];
static const Shortint HFSignatureSize = 0x8;
static const int FBlockSize = 0x80000;
static const int HFPHeaderSize = 0x118;

}	/* namespace Esfsfilectrl */
using namespace Esfsfilectrl;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ESFSFileCtrl
