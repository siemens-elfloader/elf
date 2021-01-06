// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ESingleFileSystem.pas' rev: 6.00

#ifndef ESingleFileSystemHPP
#define ESingleFileSystemHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ESFSPassword.hpp>	// Pascal unit
#include <ESFSEngine.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Esinglefilesystem
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TESFSCompressionLevel { esfsNone, zlibFastest, zlibNormal, ppmNormal, ppmMax, zlibMax, ppmFastest, bzipFastest, bzipNormal, bzipMax };
#pragma option pop

#pragma option push -b-
enum TESFSOverwriteMode { omAlways, omNever, omPrompt };
#pragma option pop

class DELPHICLASS TESingleFileSystem;
class PASCALIMPLEMENTATION TESingleFileSystem : public System::TObject 
{
	typedef System::TObject inherited;
	
protected:
	Esfsengine::TPageFileManager* PFMHandle;
	Esfsengine::TDIRManager* DMHandle;
	Esfsengine::TFreeSpaceManager* FSMHandle;
	Esfsengine::TUserFilePageMapManager* UFMHandle;
	Esfsengine::TSortedPtrArray* FFileHandles;
	bool FReadOnly;
	bool FExclusive;
	bool FCancel;
	AnsiString FPassword;
	AnsiString FFileName;
	Word FOpenMode;
	bool __fastcall GetPasswordHeader(AnsiString FileName, Esfspassword::TPasswordHeader &passHeader);
	void __fastcall SetPasswordHeader(AnsiString FileName, const Esfspassword::TPasswordHeader &passHeader);
	bool __fastcall GetEncrypted(void);
	AnsiString __fastcall PGetControlQuestion();
	
private:
	Extended FProgress;
	Extended FProgressMax;
	Esfsengine::TESFSProgressEvent FOnProgress;
	Esfsengine::TESFSFileProgressEvent FOnFileProgress;
	Esfsengine::TESFSOverwritePromptEvent FOnOverwritePrompt;
	Esfsengine::TESFSDiskFullEvent FOnDiskFull;
	Esfsengine::TESFSOnPasswordEvent FOnPassword;
	bool FInMemory;
	void __fastcall CloseAllFiles(void);
	void __fastcall InternalCreate(void);
	void __fastcall DoOnProgress(double Progress);
	void __fastcall DoOnDiskFull(System::TObject* Sender);
	void __fastcall DoOnPassword(AnsiString FileName, AnsiString &NewPassword, bool &SkipFile);
	void __fastcall SetInMemory(bool value);
	
public:
	int FLastError;
	__fastcall TESingleFileSystem(AnsiString FileName, Word Mode, AnsiString Password, AnsiString Question, AnsiString Answer, TESFSCompressionLevel DefaultCompressionLevel)/* overload */;
	__fastcall TESingleFileSystem(AnsiString FileName, Word Mode, bool InMemoryMode, AnsiString Password, AnsiString Question, AnsiString Answer, TESFSCompressionLevel DefaultCompressionLevel, int PageSize, int ExtentPageCount)/* overload */;
	__fastcall virtual ~TESingleFileSystem(void);
	bool __fastcall InternalRepair(AnsiString &log, bool DeleteCorruptedFiles = false, bool ChangeEncryption = false, AnsiString newPassword = "", AnsiString newQuestion = "", AnsiString newAnswer = "");
	bool __fastcall Repair(AnsiString &log, bool DeleteCorruptedFiles = false);
	bool __fastcall RestorePasswordByControlAnswer(AnsiString FileName, AnsiString Answer, AnsiString &Password);
	bool __fastcall IsPasswordValid(AnsiString FileName, AnsiString Password);
	AnsiString __fastcall GetControlQuestion(AnsiString FileName);
	bool __fastcall IsFileEncrypted(AnsiString FileName);
	int __fastcall FileCreate(const AnsiString FileName, AnsiString Password = "", AnsiString Question = "", AnsiString Answer = "");
	int __fastcall FileOpen(const AnsiString FileName, unsigned Mode, AnsiString Password = "", AnsiString Question = "", AnsiString Answer = "");
	void __fastcall FileClose(int Handle);
	int __fastcall FileRead(int Handle, void *Buffer, int Count);
	int __fastcall FileWrite(int Handle, const void *Buffer, int Count);
	__int64 __fastcall FileSeek(int Handle, const __int64 Offset, int Origin);
	void __fastcall FlushFileBuffers(int Handle);
	__int64 __fastcall FileSetSize(int Handle, __int64 Size);
	bool __fastcall DeleteFile(const AnsiString FileName);
	bool __fastcall RenameFile(const AnsiString OldName, const AnsiString NewName);
	bool __fastcall FileExists(const AnsiString FileName);
	int __fastcall FileGetAttr(const AnsiString FileName);
	int __fastcall FileSetAttr(const AnsiString FileName, int Attr);
	int __fastcall FileAge(const AnsiString FileName);
	int __fastcall FileGetDate(int Handle);
	int __fastcall FileSetDate(int Handle, int Age);
	int __fastcall FindFirst(const AnsiString Path, int Attr, Sysutils::TSearchRec &F);
	int __fastcall FindNext(Sysutils::TSearchRec &F);
	void __fastcall FindClose(Sysutils::TSearchRec &F);
	bool __fastcall ChangeEncryption(AnsiString newPassword = "", AnsiString newQuestion = "", AnsiString newAnswer = "");
	__int64 __fastcall DiskSize(void);
	void __fastcall SaveToStream(Classes::TStream* Stream);
	void __fastcall SaveToFile(const AnsiString FileName);
	
protected:
	bool __fastcall ForceDirectories(AnsiString Dir);
	bool __fastcall DirectoryExists(AnsiString Name);
	
__published:
	__property Esfsengine::TESFSFileProgressEvent OnFileProgress = {read=FOnFileProgress, write=FOnFileProgress};
	__property Esfsengine::TESFSProgressEvent OnProgress = {read=FOnProgress, write=FOnProgress};
	__property Esfsengine::TESFSOverwritePromptEvent OnOverwritePrompt = {read=FOnOverwritePrompt, write=FOnOverwritePrompt};
	__property Esfsengine::TESFSDiskFullEvent OnDiskFull = {read=FOnDiskFull, write=FOnDiskFull};
	__property Esfsengine::TESFSOnPasswordEvent OnPassword = {read=FOnPassword, write=FOnPassword};
	__property bool Encrypted = {read=GetEncrypted, nodefault};
	__property AnsiString Password = {read=FPassword};
	__property AnsiString ControlQuestion = {read=PGetControlQuestion};
	__property bool InMemory = {read=FInMemory, write=SetInMemory, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE bool __fastcall RenameESFS(const AnsiString OldName, const AnsiString NewName);
extern PACKAGE bool __fastcall CopyESFS(const AnsiString OldName, const AnsiString NewName);
extern PACKAGE bool __fastcall DeleteESFS(const AnsiString FileName);
extern PACKAGE bool __fastcall IsESFSFile(const AnsiString FileName);
extern PACKAGE void __fastcall MakeSFX(AnsiString ESFSFileName, AnsiString SFXStubFileName, AnsiString SFXFileName);
extern PACKAGE bool __fastcall RestorePasswordByControlAnswer(AnsiString FileName, AnsiString Answer, AnsiString &Password);
extern PACKAGE bool __fastcall IsPasswordValid(AnsiString FileName, AnsiString Password);
extern PACKAGE AnsiString __fastcall GetControlQuestion(AnsiString FileName);
extern PACKAGE bool __fastcall IsSingleFileEncrypted(AnsiString FileName);
extern PACKAGE AnsiString __fastcall GetTemporaryDirectory();

}	/* namespace Esinglefilesystem */
using namespace Esinglefilesystem;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ESingleFileSystem
