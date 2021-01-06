// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ESFSEngine.pas' rev: 6.00

#ifndef ESFSEngineHPP
#define ESFSEngineHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ESFSFileCtrl.hpp>	// Pascal unit
#include <ETblCipher.hpp>	// Pascal unit
#include <ETblDECUtil.hpp>	// Pascal unit
#include <ESFSPassword.hpp>	// Pascal unit
#include <ETblStrFunc.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Esfsengine
{
//-- type declarations -------------------------------------------------------
typedef Byte *pByte;

#pragma pack(push, 1)
struct TSingleFileHeader
{
	char Signature[8];
	unsigned CRC;
	float Version;
	int PageSize;
	int ExtentPageCount;
	int HDRPageCount;
	int GAMPageCount;
	int PFSPageCount;
	int DIRPageCount;
	int DIRFirstPageNo;
	int DIRElementsCount;
	int TOTALPageCount;
	Esfspassword::TPasswordHeader PasswordHeader;
	Byte EncMethod;
	Byte CompressionLevel;
	Byte Reserved[30];
} ;
#pragma pack(pop)

#pragma pack(push, 1)
struct TPageHeader
{
	int NextPageNo;
	unsigned CRC;
	Byte PageType;
	Byte EncType;
	Byte CrcType;
	Byte reserved1;
	Byte reserved2[20];
} ;
#pragma pack(pop)

#pragma pack(push, 1)
struct TFFPage
{
	TPageHeader PageHeader;
	void *pData;
} ;
#pragma pack(pop)

#pragma pack(push, 1)
struct TDirectoryElement
{
	int FirstMapPageNo;
	__int64 FileSize;
	_FILETIME CreationTime;
	_FILETIME LastModifiedTime;
	_FILETIME LastAccessTime;
	unsigned Attributes;
	int ParentID;
	unsigned FileCRC;
	Esfspassword::TPasswordHeader PasswordHeader;
	Byte IsFolder;
	Byte IsDeleted;
	Byte EncMethod;
	Byte Reserved1;
	char FileName[260];
	int Reserved2[7];
} ;
#pragma pack(pop)

typedef TDirectoryElement *pDirectoryElement;

#pragma pack(push, 1)
struct TEmptyPageElement
{
	int pageNo;
	int pageCount;
} ;
#pragma pack(pop)

#pragma pack(push, 1)
struct TUserFileHandle
{
	int FileID;
	__int64 Position;
	unsigned Mode;
	AnsiString Key;
} ;
#pragma pack(pop)

typedef TUserFileHandle *pUserFileHandle;

#pragma pack(push, 1)
struct TESFSFileStreamHeader
{
	char signature[4];
	int BlockSize;
	int Crc32;
	int NumBlocks;
	float version;
	Byte compressionLevel;
	Byte CrcMode;
	Byte EncMethod;
	int CustomHeaderSize;
	char reserved[1];
	char controlBlock[100];
} ;
#pragma pack(pop)

#pragma pack(push, 1)
struct TESFSHeader
{
	unsigned packedSize;
	unsigned trueSize;
	unsigned Crc32;
	unsigned nextHeaderNo;
} ;
#pragma pack(pop)

typedef DynamicArray<TESFSHeader >  ESFSEngine__2;

typedef DynamicArray<__int64 >  ESFSEngine__3;

class DELPHICLASS TESFSHeadersArray;
class PASCALIMPLEMENTATION TESFSHeadersArray : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	int AllocBy;
	int DeAllocBy;
	int MaxAllocBy;
	int AllocItemCount;
	
public:
	DynamicArray<TESFSHeader >  Items;
	DynamicArray<__int64 >  Positions;
	int ItemCount;
	__fastcall TESFSHeadersArray(void);
	__fastcall virtual ~TESFSHeadersArray(void);
	void __fastcall SetSize(int newSize);
	void __fastcall AppendItem(const TESFSHeader &value, __int64 pos);
	int __fastcall FindPosition(__int64 pos);
};


typedef void __fastcall (__closure *TESFSProgressEvent)(System::TObject* Sender, double PercentDone, bool &Cancel);

typedef void __fastcall (__closure *TESFSNoCancelProgressEvent)(System::TObject* Sender, double PercentDone);

typedef void __fastcall (__closure *TESFSFileProgressEvent)(System::TObject* Sender, double PercentDone, AnsiString FileName);

typedef void __fastcall (__closure *TESFSOverwritePromptEvent)(System::TObject* Sender, AnsiString ExistsingFileName, AnsiString NewFileName, bool &bOverwrite);

typedef void __fastcall (__closure *TESFSDiskFullEvent)(System::TObject* Sender);

typedef void __fastcall (__closure *TESFSOnPasswordEvent)(System::TObject* Sender, AnsiString FileName, AnsiString &NewPassword, bool &SkipFile);

typedef DynamicArray<int >  ESFSEngine__5;

class DELPHICLASS TIntegerArray;
class PASCALIMPLEMENTATION TIntegerArray : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	DynamicArray<int >  Items;
	int ItemCount;
	int CurrentItem;
	int AllocBy;
	int deAllocBy;
	int MaxAllocBy;
	int AllocItemCount;
	__fastcall TIntegerArray(int size, int defaultAllocBy, int defaultMaxAllocBy);
	__fastcall virtual ~TIntegerArray(void);
	void __fastcall SetSize(int newSize);
	void __fastcall Append(int value);
	void __fastcall Insert(int ItemNo, int value);
	void __fastcall Delete(int ItemNo);
	void __fastcall MoveTo(int itemNo, int newItemNo);
	void __fastcall CopyTo(int * ar, const int ar_Size, int itemNo, int iCount);
};


typedef DynamicArray<int >  ESFSEngine__7;

typedef DynamicArray<void * >  ESFSEngine__8;

class DELPHICLASS TSortedPtrArray;
class PASCALIMPLEMENTATION TSortedPtrArray : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	int uniqueKeyValue;
	int AllocBy;
	int deAllocBy;
	int MaxAllocBy;
	int AllocItemCount;
	int __fastcall FindPositionForInsert(int key);
	int __fastcall FindPosition(int key);
	void __fastcall InsertByPosition(int ItemNo, int key, void * value);
	void __fastcall DeleteByPosition(int ItemNo);
	
public:
	DynamicArray<int >  KeyItems;
	DynamicArray<void * >  ValueItems;
	int ItemCount;
	__fastcall TSortedPtrArray(int size, int defaultAllocBy, int defaultMaxAllocBy);
	__fastcall virtual ~TSortedPtrArray(void);
	void __fastcall SetSize(int newSize);
	void * __fastcall Find(int key);
	void __fastcall Insert(int key, void * value);
	void __fastcall Delete(int key);
	int __fastcall GetNextKeyValue(void);
};


typedef DynamicArray<TIntegerArray* >  ESFSEngine__01;

typedef DynamicArray<TDirectoryElement >  ESFSEngine__11;

class DELPHICLASS TDIRArray;
class PASCALIMPLEMENTATION TDIRArray : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	int AllocBy;
	int MaxAllocBy;
	int AllocItemCount;
	
public:
	DynamicArray<TIntegerArray* >  FoundItems;
	DynamicArray<TDirectoryElement >  Items;
	TIntegerArray* NameIndex;
	TIntegerArray* ParentIndex;
	int FoundItemCount;
	int ItemCount;
	int IndexElementsCount;
	void __fastcall BuildIndexes(void);
	__fastcall TDIRArray(int size, int defaultAllocBy, int defaultMaxAllocBy);
	__fastcall virtual ~TDIRArray(void);
	void __fastcall SetSize(int newSize);
	int __fastcall FindPositionForInsert(const TDirectoryElement &value, bool bByName = true, bool bFirst = false, bool bInsert = true);
	int __fastcall FindFileByName(char * FileName, int startDir = 0xffffffff);
	AnsiString __fastcall GetFullFilePath(int ItemNo);
	void __fastcall PrepareSearchRecord(int ItemNo, Sysutils::TSearchRec &F);
	int __fastcall FindFirst(const AnsiString Path, int Attr, Sysutils::TSearchRec &F, int currentDir = 0xffffffff);
	int __fastcall FindNext(Sysutils::TSearchRec &F);
	void __fastcall FindClose(Sysutils::TSearchRec &F);
	void __fastcall AppendItem(const TDirectoryElement &value);
	void __fastcall UpdateItem(const TDirectoryElement &value, int position);
	TDirectoryElement __fastcall ReadItem(int position);
};


class DELPHICLASS TPageFileManager;
class PASCALIMPLEMENTATION TPageFileManager : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	Esfsfilectrl::TESFSHugeFile* ESFSFile;
	
private:
	__int64 __fastcall PageNoToOffset(int PageNo);
	bool __fastcall EncodeBuffer(char * buffer, int Size, Byte EncType, AnsiString Password);
	
public:
	bool __fastcall DecodeBuffer(char * buffer, int Size, Byte EncType, AnsiString Password);
	bool __fastcall InternalLoadHeader(__int64 FileOffset);
	int __fastcall GetPageDataSize(void);
	void __fastcall SetInMemory(bool Value);
	AnsiString FFileName;
	bool FInMemory;
	#pragma pack(push, 1)
	TSingleFileHeader FHeader;
	#pragma pack(pop)
	
	bool FReadOnly;
	bool FExclusive;
	AnsiString FKey;
	int FLastError;
	AnsiString FPassword;
	__fastcall TPageFileManager(const AnsiString FileName, Word Mode, AnsiString Password, AnsiString Question, AnsiString Answer, bool IsInMemory, int PageSize, int ExtentPageCount);
	__fastcall virtual ~TPageFileManager(void);
	void __fastcall LoadSFHeader(void);
	void __fastcall SaveSFHeader(void);
	void __fastcall AllocPageBuffer(TFFPage &FFPage);
	void __fastcall FreePageBuffer(const TFFPage &FFPage);
	bool __fastcall ReadPage(TFFPage &buffer, int PageNo, int Size = 0xffffffff, AnsiString Password = "", bool bIgnoreEncrypted = false);
	bool __fastcall WritePage(TFFPage &buffer, int PageNo, int Size = 0xffffffff, AnsiString Password = "");
	bool __fastcall AppendPages(int qty);
	void __fastcall DeletePagesFromEOF(int qty);
	bool __fastcall RenameFile(AnsiString NewName);
	bool __fastcall DeleteFile(void);
	void __fastcall FlushFileBuffers(void);
	void __fastcall LoadFromStream(Classes::TStream* Stream);
	__int64 __fastcall DiskFree(void);
	
__published:
	__property int PageDataSize = {read=GetPageDataSize, nodefault};
	__property bool InMemory = {read=FInMemory, write=SetInMemory, nodefault};
};


class DELPHICLASS TFreeSpaceManager;
class PASCALIMPLEMENTATION TFreeSpaceManager : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	TPageFileManager* PFMHandle;
	
private:
	char *PFS;
	char *GAM;
	char *SGAM;
	TIntegerArray* PFSPageMap;
	TIntegerArray* GAMPageMap;
	int FPageSize;
	int FGAMPageSize;
	int FGAMExtentsPerPage;
	int FPFSExtentsPerPage;
	int FPFSPageSize;
	int FExtentPageCount;
	int FFreeExtentCount;
	int FMixedExtentCount;
	int FExtentCount;
	int FPageCount;
	void __fastcall LoadPFS(void);
	void __fastcall LoadGAM(void);
	void __fastcall SavePFS(TIntegerArray* pages);
	void __fastcall SaveGAM(TIntegerArray* pages);
	int __fastcall GetGAMPageNo(int extentNo);
	int __fastcall GetPFSPageNo(int extentNo);
	
public:
	__fastcall TFreeSpaceManager(TPageFileManager* PageFileManager);
	__fastcall virtual ~TFreeSpaceManager(void);
	bool __fastcall GetPages(int PageCount, int StartPageNo, bool bUniform, TIntegerArray* &pages);
	void __fastcall FreePages(TIntegerArray* &pages);
	__int64 __fastcall GetFreePageCount(void);
};


class DELPHICLASS TDIRManager;
class PASCALIMPLEMENTATION TDIRManager : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	TFreeSpaceManager* FSMHandle;
	TIntegerArray* DIRPageMap;
	int FDIRElementsPerPage;
	int FDIRPageSize;
	
public:
	TPageFileManager* PFMHandle;
	TDIRArray* FDIR;
	TIntegerArray* FOpenedFiles;
	int FLastError;
	void __fastcall Load(void);
	bool __fastcall AddItem(const TDirectoryElement &item);
	void __fastcall ReadItem(int ItemNo, TDirectoryElement &item);
	void __fastcall WriteItem(int ItemNo, const TDirectoryElement &item);
	int __fastcall FindByName(AnsiString FileName);
	AnsiString __fastcall GetFullFilePath(int ItemNo);
	int __fastcall FileCreate(const AnsiString FileName, AnsiString Password = "", AnsiString Question = "", AnsiString Answer = "");
	int __fastcall FileOpen(const AnsiString FileName, AnsiString Password, AnsiString &Key);
	void __fastcall FileClose(int ItemNo);
	bool __fastcall RenameFile(const AnsiString OldName, const AnsiString NewName);
	int __fastcall GetOpenFiles(int ItemNo);
	bool __fastcall RestorePasswordByControlAnswer(AnsiString FileName, AnsiString Answer, AnsiString &Password);
	bool __fastcall IsPasswordValid(AnsiString FileName, AnsiString Password);
	AnsiString __fastcall GetControlQuestion(AnsiString FileName);
	bool __fastcall GetPasswordHeader(AnsiString FileName, Esfspassword::TPasswordHeader &passHeader);
	void __fastcall SetPasswordHeader(AnsiString FileName, const Esfspassword::TPasswordHeader &passHeader);
	bool __fastcall IsFileEncrypted(AnsiString FileName);
	AnsiString CurrentPath;
	int CurrentDir;
	__fastcall TDIRManager(TPageFileManager* PageFileManager, TFreeSpaceManager* FreeSpaceManager);
	__fastcall virtual ~TDIRManager(void);
	int __fastcall FindFirst(const AnsiString Path, int Attr, Sysutils::TSearchRec &F);
	int __fastcall FindNext(Sysutils::TSearchRec &F);
	void __fastcall FindClose(Sysutils::TSearchRec &F);
	AnsiString __fastcall GetCurrentDir();
	bool __fastcall SetCurrentDir(const AnsiString Dir);
	bool __fastcall RemoveDir(const AnsiString Dir);
	bool __fastcall CreateDir(const AnsiString Dir);
	bool __fastcall ForceDirectories(AnsiString Dir);
	bool __fastcall DirectoryExists(AnsiString Name);
};


class DELPHICLASS TUserFilePageMapManager;
class PASCALIMPLEMENTATION TUserFilePageMapManager : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	TPageFileManager* PFMHandle;
	int FLastError;
	
private:
	TFreeSpaceManager* FSMHandle;
	TSortedPtrArray* UFPMMaps;
	TSortedPtrArray* UFMaps;
	int PagesPerMapPage;
	TIntegerArray* TempPages;
	int __fastcall GetCoverPageCount(__int64 Size);
	void __fastcall GetMaps(TDirectoryElement &FileRec, TIntegerArray* &UFPMMap, TIntegerArray* &UFMap);
	bool __fastcall AppendPages(TDirectoryElement &FileRec, int PageCount, bool bWriteAppendedPages);
	void __fastcall DeletePagesFromEOF(TDirectoryElement &FileRec, int PageCount);
	void __fastcall SaveMapPages(int ItemNo, int ItemCount, TIntegerArray* UFPMMap, TIntegerArray* UFMap);
	
public:
	__fastcall TUserFilePageMapManager(TPageFileManager* PFMHandle1, TFreeSpaceManager* FSMHandle1);
	__fastcall virtual ~TUserFilePageMapManager(void);
	bool __fastcall GetPages(TDirectoryElement &FileRec, __int64 Offset, __int64 Size, bool IsAllocateAllowed, TIntegerArray* &pages);
	bool __fastcall SetSize(TDirectoryElement &FileRec, __int64 NewSize, bool bWriteAppendedPages = true);
};


//-- var, const, procedure ---------------------------------------------------
#define crlf "\r\n"
#define ESingleFileSystemSignature "AASFSSGN"
#define ESFSStreamSignature "AACS"
static const Shortint SignatureSize = 0x8;
#define ESFSCurrentVersion  (2.000000E+00)
#define FormatVersion  (1.000000E+00)
static const Shortint DEFAULT_PAGE_SIZE = 0x4;
static const Shortint DEFAULT_EXTENT_PAGE_COUNT = 0x10;
static const Shortint UNIFORM_MIN_PAGE_COUNT = 0x10;
static const Shortint DIRPage = 0x1;
static const Shortint GAMPage = 0x2;
static const Shortint SGAMPage = 0x3;
static const Shortint PFSPage = 0x4;
static const Shortint UFPMPage = 0x5;
static const Shortint UFPage = 0x6;
static const Shortint rootID = 0xffffffff;
static const Shortint erOk = 0x0;
static const Shortint erInvalidPath = 0xfffffffe;
static const Shortint erInvalidCurrentDir = 0xfffffffd;
static const Shortint erInvalidSearchRec = 0xfffffffc;
static const Shortint erFileNotFound = 0xfffffffb;
static const Shortint erInvalidHandle = 0xfffffffa;
static const Shortint erReadPageHeaderError = 0xfffffff9;
static const Shortint erWritePageHeaderError = 0xfffffff8;
static const Shortint erReadPageError = 0xfffffff7;
static const Shortint erWritePageError = 0xfffffff6;
static const Shortint erCRCError = 0xfffffff5;
static const Shortint erDecodeError = 0xfffffff4;
static const Shortint erEncodeError = 0xfffffff3;
static const Shortint erNoMemory = 0xfffffff2;
static const Shortint erRenameFileError = 0xfffffff1;
static const Shortint erFileNotDeleted = 0xfffffff0;
static const Shortint erDiskFull = 0xffffffef;
static const Shortint None = 0xffffffff;
static const Shortint encNone = 0x0;
static const Shortint encRijndael = 0x1;
#define SPasswordTitle "Password for \"%s\""
#define SPasswordPrompt "Enter password: "
extern PACKAGE bool debugFlag;
static const char WildCardMultipleChar = '\x2a';
static const char WildCardSingleChar = '\x3f';
#define WildCardAnyFile "*.*"
static const int DefaultMaxBlockSize = 0x100000;
static const int BlockSizeForFastest = 0x80000;
static const int BlockSizeForNormal = 0x100000;
static const int BlockSizeForMax = 0x180000;
static const Shortint PPM_FASTEST_MO = 0x3;
static const Shortint PPM_FASTEST_SA = 0xa;
static const Shortint PPM_NORMAL_MO = 0x5;
static const Shortint PPM_NORMAL_SA = 0x19;
static const Shortint PPM_MAX_MO = 0xd;
static const Shortint PPM_MAX_SA = 0x32;
static const Shortint CRC32_checksum = 0x1;
static const Shortint DefaultCompressionLevel = 0x1;
static const Shortint Default_Crc_Method = 0x1;
#define ESFSCompressCurrentVersion  (2.000000E+00)
static const int ESFSCompressedHeaderSize = 0x10;
static const int ESFSFileStreamHeaderSize = 0x80;
static const int SingleFileHeaderSize = 0x100;
static const int PageHeaderSize = 0x20;
static const int DirElementSize = 0x200;
static const int UserFileHandleSize = 0x14;
extern PACKAGE bool __fastcall IsStrMatchPattern(char * StrPtr, char * PatternPtr, bool bIgnoreCase = true);
extern PACKAGE bool __fastcall ExtractPathAndPattern(char * InPath, char * &OutPath, char * &Pattern);
extern PACKAGE void __fastcall SetCurrentTime(_FILETIME &fTime);
extern PACKAGE void __fastcall SetFileName(AnsiString FileName, TDirectoryElement &el);
extern PACKAGE void __fastcall InitDirectoryElement(TDirectoryElement &el);
extern PACKAGE void __fastcall SetBit(char * BitMap, int BitNo, bool bSet);
extern PACKAGE bool __fastcall GetBit(char * BitMap, int BitNo);

}	/* namespace Esfsengine */
using namespace Esfsengine;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ESFSEngine
