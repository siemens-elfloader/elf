// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ETblFileManage.pas' rev: 6.00

#ifndef ETblFileManageHPP
#define ETblFileManageHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ESingleFileSystem.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Etblfilemanage
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TaaFileStoreMode { fsmDefault, fsmDisk, fsmESFS, fsmInMemory, fsmTemporary };
#pragma option pop

class DELPHICLASS TAbstractFile;
class DELPHICLASS TAbstractPlainFileSystem;
class PASCALIMPLEMENTATION TAbstractPlainFileSystem : public System::TObject 
{
	typedef System::TObject inherited;
	
protected:
	Classes::TList* OpenFileList;
	
public:
	AnsiString DatabaseName;
	TaaFileStoreMode FileStoreMode;
	__fastcall TAbstractPlainFileSystem(AnsiString NewDatabaseName, TaaFileStoreMode NewFileStoreMode);
	__fastcall virtual ~TAbstractPlainFileSystem(void);
	virtual TAbstractFile* __fastcall OpenFile(AnsiString FileName, bool bCreate, bool bExclusive, bool bReadOnly) = 0 ;
	virtual void __fastcall CloseFile(TAbstractFile* FileHandle) = 0 ;
	virtual bool __fastcall DeleteFile(const AnsiString FileName) = 0 ;
	virtual bool __fastcall RenameFile(const AnsiString OldName, const AnsiString NewName) = 0 ;
	virtual bool __fastcall FileExists(const AnsiString FileName) = 0 ;
	virtual void __fastcall GetFilesListByExt(AnsiString Ext, Classes::TStrings* List) = 0 ;
	TAbstractFile* __fastcall GetOpenFile(AnsiString FileName);
};


class PASCALIMPLEMENTATION TAbstractFile : public System::TObject 
{
	typedef System::TObject inherited;
	
protected:
	AnsiString FFileName;
	bool FExclusive;
	bool FReadOnly;
	bool FTemporary;
	virtual void __fastcall SetExclusive(bool value);
	virtual void __fastcall SetPosition(int Pos);
	virtual int __fastcall GetPosition(void);
	virtual void __fastcall SetReadOnly(bool value);
	virtual void __fastcall SetSize(int value) = 0 ;
	virtual int __fastcall GetSize(void);
	virtual void __fastcall SetTemporary(bool value);
	
public:
	TAbstractPlainFileSystem* FPFSHandle;
	__fastcall TAbstractFile(TAbstractPlainFileSystem* PFSHandle, AnsiString FileName, bool bReadOnly, bool bExclusive);
	__fastcall virtual ~TAbstractFile(void);
	int __fastcall CopyFrom(TAbstractFile* Source, int Count);
	virtual void __fastcall Close(void) = 0 ;
	virtual void __fastcall FlushBuffers(void) = 0 ;
	virtual void __fastcall Open(bool bCreate) = 0 ;
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
	__property bool Temporary = {read=FTemporary, write=SetTemporary, default=0};
};


class DELPHICLASS TDiskFile;
class PASCALIMPLEMENTATION TDiskFile : public TAbstractFile 
{
	typedef TAbstractFile inherited;
	
private:
	int FHandle;
	AnsiString FDirectory;
	void __fastcall Reopen(void);
	
protected:
	void __fastcall InternalOpen(const AnsiString FileName, bool bCreate);
	virtual void __fastcall SetExclusive(bool value);
	virtual void __fastcall SetReadOnly(bool value);
	virtual void __fastcall SetSize(int value);
	
public:
	__fastcall TDiskFile(TAbstractPlainFileSystem* PFSHandle, AnsiString FileName, bool bReadOnly, bool bExclusive);
	virtual void __fastcall Close(void);
	__fastcall virtual ~TDiskFile(void);
	virtual void __fastcall FlushBuffers(void);
	virtual void __fastcall Open(bool bCreate);
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


class DELPHICLASS TMemoryFile;
class PASCALIMPLEMENTATION TMemoryFile : public TAbstractFile 
{
	typedef TAbstractFile inherited;
	
private:
	Classes::TMemoryStream* FStream;
	
protected:
	virtual void __fastcall SetSize(int value);
	
public:
	__fastcall TMemoryFile(TAbstractPlainFileSystem* PFSHandle, AnsiString FileName, bool bReadOnly, bool bExclusive);
	virtual void __fastcall Close(void);
	__fastcall virtual ~TMemoryFile(void);
	virtual void __fastcall FlushBuffers(void);
	virtual void __fastcall Open(bool bCreate);
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


class DELPHICLASS TESFSFile;
class PASCALIMPLEMENTATION TESFSFile : public TAbstractFile 
{
	typedef TAbstractFile inherited;
	
private:
	Esinglefilesystem::TESingleFileSystem* ESFSHandle;
	int FHandle;
	AnsiString FDirectory;
	void __fastcall Reopen(void);
	
protected:
	void __fastcall InternalOpen(const AnsiString FileName, bool bCreate);
	virtual void __fastcall SetExclusive(bool value);
	virtual void __fastcall SetReadOnly(bool value);
	virtual void __fastcall SetSize(int value);
	
public:
	__fastcall TESFSFile(Esinglefilesystem::TESingleFileSystem* ESFSHandle1, TAbstractPlainFileSystem* PFSHandle, AnsiString FileName, bool bReadOnly, bool bExclusive)/* overload */;
	virtual void __fastcall Close(void);
	__fastcall virtual ~TESFSFile(void);
	virtual void __fastcall FlushBuffers(void);
	virtual void __fastcall Open(bool bCreate);
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


class DELPHICLASS TDiskPlainFileSystem;
class PASCALIMPLEMENTATION TDiskPlainFileSystem : public TAbstractPlainFileSystem 
{
	typedef TAbstractPlainFileSystem inherited;
	
protected:
	AnsiString FDirectory;
	AnsiString __fastcall GetFullFileName(AnsiString FileName);
	
public:
	__fastcall TDiskPlainFileSystem(AnsiString NewDatabaseName, TaaFileStoreMode NewFileStoreMode);
	virtual TAbstractFile* __fastcall OpenFile(AnsiString FileName, bool bCreate, bool bExclusive, bool bReadOnly);
	virtual void __fastcall CloseFile(TAbstractFile* FileHandle);
	virtual bool __fastcall DeleteFile(const AnsiString FileName);
	virtual bool __fastcall RenameFile(const AnsiString OldName, const AnsiString NewName);
	virtual bool __fastcall FileExists(const AnsiString FileName);
	virtual void __fastcall GetFilesListByExt(AnsiString Ext, Classes::TStrings* List);
	
__published:
	__property AnsiString Directory = {read=FDirectory, write=FDirectory};
public:
	#pragma option push -w-inl
	/* TAbstractPlainFileSystem.Destroy */ inline __fastcall virtual ~TDiskPlainFileSystem(void) { }
	#pragma option pop
	
};


class DELPHICLASS TTemporaryPlainFileSystem;
class PASCALIMPLEMENTATION TTemporaryPlainFileSystem : public TDiskPlainFileSystem 
{
	typedef TDiskPlainFileSystem inherited;
	
public:
	virtual TAbstractFile* __fastcall OpenFile(AnsiString FileName, bool bCreate, bool bExclusive, bool bReadOnly);
	virtual void __fastcall CloseFile(TAbstractFile* FileHandle);
	virtual bool __fastcall DeleteFile(const AnsiString FileName);
	virtual bool __fastcall RenameFile(const AnsiString OldName, const AnsiString NewName);
	
__published:
	__property Directory ;
public:
	#pragma option push -w-inl
	/* TDiskPlainFileSystem.Create */ inline __fastcall TTemporaryPlainFileSystem(AnsiString NewDatabaseName, TaaFileStoreMode NewFileStoreMode) : TDiskPlainFileSystem(NewDatabaseName, NewFileStoreMode) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TAbstractPlainFileSystem.Destroy */ inline __fastcall virtual ~TTemporaryPlainFileSystem(void) { }
	#pragma option pop
	
};


class DELPHICLASS TMemoryPlainFileSystem;
class PASCALIMPLEMENTATION TMemoryPlainFileSystem : public TAbstractPlainFileSystem 
{
	typedef TAbstractPlainFileSystem inherited;
	
public:
	virtual TAbstractFile* __fastcall OpenFile(AnsiString FileName, bool bCreate, bool bExclusive, bool bReadOnly);
	virtual void __fastcall CloseFile(TAbstractFile* FileHandle);
	virtual bool __fastcall DeleteFile(const AnsiString FileName);
	virtual bool __fastcall RenameFile(const AnsiString OldName, const AnsiString NewName);
	virtual bool __fastcall FileExists(const AnsiString FileName);
	virtual void __fastcall GetFilesListByExt(AnsiString Ext, Classes::TStrings* List);
public:
	#pragma option push -w-inl
	/* TAbstractPlainFileSystem.Create */ inline __fastcall TMemoryPlainFileSystem(AnsiString NewDatabaseName, TaaFileStoreMode NewFileStoreMode) : TAbstractPlainFileSystem(NewDatabaseName, NewFileStoreMode) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TAbstractPlainFileSystem.Destroy */ inline __fastcall virtual ~TMemoryPlainFileSystem(void) { }
	#pragma option pop
	
};


class DELPHICLASS TESFSPlainFileSystem;
class PASCALIMPLEMENTATION TESFSPlainFileSystem : public TAbstractPlainFileSystem 
{
	typedef TAbstractPlainFileSystem inherited;
	
protected:
	bool FReadOnly;
	bool FInMemory;
	void __fastcall SetInMemory(bool Value);
	
public:
	Esinglefilesystem::TESingleFileSystem* ESFSHandle;
	__fastcall TESFSPlainFileSystem(AnsiString NewDatabaseName, AnsiString Password, TaaFileStoreMode NewFileStoreMode, bool ReadOnly, bool InMemory, bool bCreate);
	__fastcall virtual ~TESFSPlainFileSystem(void);
	virtual TAbstractFile* __fastcall OpenFile(AnsiString FileName, bool bCreate, bool bExclusive, bool bReadOnly);
	virtual void __fastcall CloseFile(TAbstractFile* FileHandle);
	virtual bool __fastcall DeleteFile(const AnsiString FileName);
	virtual bool __fastcall RenameFile(const AnsiString OldName, const AnsiString NewName);
	virtual bool __fastcall FileExists(const AnsiString FileName);
	virtual void __fastcall GetFilesListByExt(AnsiString Ext, Classes::TStrings* List);
	
__published:
	__property bool ReadOnly = {read=FReadOnly, write=FReadOnly, nodefault};
	__property bool InMemory = {read=FInMemory, write=SetInMemory, nodefault};
};


class DELPHICLASS TPFSManager;
class PASCALIMPLEMENTATION TPFSManager : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	Classes::TList* PFSList;
	
public:
	__fastcall TPFSManager(void);
	__fastcall virtual ~TPFSManager(void);
	TAbstractPlainFileSystem* __fastcall FindPFS(AnsiString DatabaseName, TaaFileStoreMode FileStoreMode, bool ESFSInMemory);
	TAbstractPlainFileSystem* __fastcall GetPFSHandle(AnsiString DatabaseName, AnsiString Password, TaaFileStoreMode FileStoreMode, bool &ESFSReadOnly, bool ESFSInMemory);
	void __fastcall ClosePhysESFS(AnsiString DatabaseName, bool InMemory);
	bool __fastcall CreatePhysESFS(AnsiString DatabaseName, AnsiString Password, bool InMemory);
	bool __fastcall DeletePhysESFS(AnsiString DatabaseName, bool InMemory);
	bool __fastcall RenamePhysESFS(AnsiString DatabaseName, bool InMemory, const AnsiString NewDatabaseName);
	bool __fastcall CopyPhysESFS(AnsiString DatabaseName, bool InMemory, const AnsiString NewDatabaseName);
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Etblfilemanage */
using namespace Etblfilemanage;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ETblFileManage
