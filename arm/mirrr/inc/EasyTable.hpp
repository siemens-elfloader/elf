// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EasyTable.pas' rev: 6.00

#ifndef EasyTableHPP
#define EasyTableHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ETblEngine.hpp>	// Pascal unit
#include <ETblSQLProcessor.hpp>	// Pascal unit
#include <Registry.hpp>	// Pascal unit
#include <ETblFolderDialog.hpp>	// Pascal unit
#include <ETblCipher.hpp>	// Pascal unit
#include <ETblStrFunc.hpp>	// Pascal unit
#include <ETblConst.hpp>	// Pascal unit
#include <ETblExcept.hpp>	// Pascal unit
#include <ETblCommon.hpp>	// Pascal unit
#include <ETblFileManage.hpp>	// Pascal unit
#include <Variants.hpp>	// Pascal unit
#include <FMTBcd.hpp>	// Pascal unit
#include <ETblBuildIndex.hpp>	// Pascal unit
#include <ETblGauge.hpp>	// Pascal unit
#include <FileCtrl.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <DB.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Math.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Easytable
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TCompressionLevel { clNone, clFastest, clDefault, clMax };
#pragma option pop

#pragma pack(push, 1)
struct TBlobCompressionLevel
{
	TCompressionLevel Level;
	System::SmallString<20>  name;
} ;
#pragma pack(pop)

#pragma option push -b-
enum TaaProgressProcess { aappImport, aappExport, aappRestructure, aappRepair, aappChangeCompression, aappCompactDB, aappRepairDB, aappChangeEncryption, aappChangeEncryptionDB, aappAddingRecords };
#pragma option pop

#pragma pack(push, 1)
struct FieldHeaderType
{
	System::SmallString<20>  fieldName;
	Db::TFieldType fieldType;
	int fieldSize;
	bool required;
} ;
#pragma pack(pop)

typedef FieldHeaderType *pFieldHeaderType;

#pragma pack(push, 1)
struct TableHeaderType
{
	int sequenceValue;
	System::SmallString<20>  sequenceName;
	int fieldCount;
	int recordCount;
	double version;
	Byte ShowAutoInc;
	TCompressionLevel blobCompressed;
	bool cipherUsed;
	int state;
} ;
#pragma pack(pop)

typedef TableHeaderType *pTableHeaderType;

#pragma pack(push, 4)
struct RecordInfoType
{
	int id;
} ;
#pragma pack(pop)

typedef RecordInfoType *pRecordInfoType;

#pragma pack(push, 4)
struct BookmarkInfoType
{
	int BookmarkData;
	Db::TBookmarkFlag BookmarkFlag;
} ;
#pragma pack(pop)

typedef BookmarkInfoType *pBookmarkInfoType;

typedef DynamicArray<int >  EasyTable__1;

#pragma pack(push, 1)
struct IndexHeaderType
{
	System::SmallString<20>  indexName;
	int indexCount;
	DynamicArray<int >  indexFields;
	char *indexOrders;
	char *indexCaseIns;
	bool ignoreCase;
	bool descending;
	Db::TIndexOptions indexOptions;
} ;
#pragma pack(pop)

typedef IndexHeaderType *pIndexHeaderType;

#pragma pack(push, 1)
struct IndexFileHeaderType
{
	int state;
	int indexCount;
	double version;
} ;
#pragma pack(pop)

typedef IndexFileHeaderType *pIndexFileHeaderType;

#pragma pack(push, 1)
struct BLOBIndexFileHeaderType
{
	int blockSize;
	int numDeletedParts;
	int fieldCount;
	int recordCount;
	double version;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct BLOBFieldType
{
	Classes::TMemoryStream* stream;
	Db::TBlobStreamMode mode;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct SearchInfoType
{
	int foundRecordPosition;
	int tablePosition;
	int fieldNum;
	AnsiString operation;
	char *valueBuffer;
	IndexHeaderType *pIndexHeader;
	int indexNum;
	bool ignoreCase;
	int offset;
	bool goForward;
	bool reset;
	int foundListPosition;
} ;
#pragma pack(pop)

#pragma option push -b-
enum TaaGMRMode { aagmrReturnArray, aagmrReturnCountOnly, aagmrReturnOneRecordOnly };
#pragma option pop

#pragma option push -b-
enum TKeyIndex { kiLookup, kiRangeStart, kiRangeEnd };
#pragma option pop

struct TKeyBuffer;
typedef TKeyBuffer *PKeyBuffer;

#pragma pack(push, 1)
struct TKeyBuffer
{
	bool Exclusive;
	int FieldCount;
} ;
#pragma pack(pop)

typedef Byte *pByte;

typedef int *pInteger;

typedef short *pSmallint;

typedef __int64 *pLargeInt;

typedef Word *pWord;

typedef bool *pBoolean;

typedef double *pFloat;

typedef double *pCurrency;

typedef System::TDateTime *pDateTime;

typedef Etblconst::TETFieldType *pTETFieldType;

typedef DynamicArray<int >  aInteger;

class DELPHICLASS TaaList;
class PASCALIMPLEMENTATION TaaList : public Classes::TList 
{
	typedef Classes::TList inherited;
	
public:
	virtual void __fastcall Clear(void);
public:
	#pragma option push -w-inl
	/* TList.Destroy */ inline __fastcall virtual ~TaaList(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TaaList(void) : Classes::TList() { }
	#pragma option pop
	
};


#pragma option push -b-
enum TAddRecordsMode { arAppend, arUpdate, arAppendUpdate, arReplace };
#pragma option pop

class DELPHICLASS TEasyDataset;
typedef void __fastcall (__closure *TaaProgressEvent)(TEasyDataset* Sender, double PercentDone, TaaProgressProcess ProgressProcess);

typedef void __fastcall (__closure *TBuildIndexesProgressEvent)(TEasyDataset* Sender, double PercentDone, bool bStart, bool bFinish);

typedef void __fastcall (__closure *TProgressEvent)(Classes::TComponent* Sender, double PercentDone, TaaProgressProcess ProgressProcess, bool &Cancel);

class DELPHICLASS TEasyBlobStream;
class PASCALIMPLEMENTATION TEasyBlobStream : public Classes::TStream 
{
	typedef Classes::TStream inherited;
	
protected:
	Db::TBlobField* FField;
	Db::TBlobStreamMode FMode;
	Classes::TMemoryStream* FStream;
	bool FModified;
	bool FOpened;
	
public:
	__fastcall TEasyBlobStream(Db::TBlobField* Field, Db::TBlobStreamMode Mode);
	__fastcall virtual ~TEasyBlobStream(void);
	virtual int __fastcall Read(void *Buffer, int Count);
	virtual int __fastcall Write(const void *Buffer, int Count);
	virtual int __fastcall Seek(int Offset, Word Origin)/* overload */;
	void __fastcall Truncate(void);
	
/* Hoisted overloads: */
	
public:
	inline __int64 __fastcall  Seek(const __int64 Offset, Classes::TSeekOrigin Origin){ return TStream::Seek(Offset, Origin); }
	
};


typedef DynamicArray<bool >  EasyTable__5;

typedef DynamicArray<Etblengine::TaaIntArray* >  EasyTable__6;

class DELPHICLASS TEasyDataManager;
class DELPHICLASS TEasyDatabaseManager;
class DELPHICLASS TEasyDatabase;
class PASCALIMPLEMENTATION TEasyDatabaseManager : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	Classes::TList* DatabaseList;
	Classes::TList* DataSetList;
	bool FReadOnly;
	bool FInMemory;
	AnsiString __fastcall FPassword();
	
protected:
	Etblfilemanage::TAbstractPlainFileSystem* __fastcall GetPFSHandle(Etblfilemanage::TaaFileStoreMode FileStoreMode);
	
public:
	bool bDatabaseFile;
	bool __fastcall GetExists(void);
	void __fastcall SetInMemory(bool Value);
	void __fastcall CheckToDestroy(void);
	AnsiString FDatabaseName;
	Etblfilemanage::TaaFileStoreMode DefaultFileStoreMode;
	__fastcall TEasyDatabaseManager(TEasyDatabase* EDB)/* overload */;
	__fastcall TEasyDatabaseManager(TEasyDataset* EDS)/* overload */;
	__fastcall TEasyDatabaseManager(AnsiString DBName)/* overload */;
	__fastcall virtual ~TEasyDatabaseManager(void);
	void __fastcall OpenESFSFile(void);
	void __fastcall CloseESFSFile(void);
	bool __fastcall HasDatabaseName(AnsiString DBName);
	void __fastcall ConnectDatabase(TEasyDatabase* DBHandle);
	void __fastcall DisconnectDatabase(TEasyDatabase* DBHandle);
	void __fastcall ConnectDataset(TEasyDataset* DSHandle);
	void __fastcall DisconnectDataset(TEasyDataset* DSHandle);
	void __fastcall GetNonTempTablesList(Classes::TStrings* List);
	Etblfilemanage::TAbstractFile* __fastcall OpenFile(AnsiString FileName, Etblfilemanage::TaaFileStoreMode FileStoreMode, bool bCreateFile, bool bExclusive, bool bReadOnly);
	void __fastcall CloseFile(Etblfilemanage::TAbstractFile* FileHandle);
	bool __fastcall aaFileExists(AnsiString FileName, Etblfilemanage::TaaFileStoreMode FileStoreMode);
	bool __fastcall aaDeleteFile(AnsiString FileName, Etblfilemanage::TaaFileStoreMode FileStoreMode);
	bool __fastcall aaRenameFile(AnsiString OldFileName, AnsiString NewFileName, Etblfilemanage::TaaFileStoreMode FileStoreMode);
	bool __fastcall aaCopyFile(AnsiString OldFileName, AnsiString NewFileName, Etblfilemanage::TaaFileStoreMode FileStoreMode, AnsiString NewDatabaseName = "");
	void __fastcall SaveFile(AnsiString FileName);
	void __fastcall CreateDatabase(void);
	void __fastcall DeleteDatabase(void);
	bool __fastcall RenameDatabase(const AnsiString NewDatabaseName);
	bool __fastcall CopyDatabase(const AnsiString NewDatabaseName);
	
__published:
	__property bool Exists = {read=GetExists, nodefault};
	__property bool InMemory = {read=FInMemory, write=SetInMemory, nodefault};
};


class PASCALIMPLEMENTATION TEasyDataManager : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	Classes::TList* DatasetList;
	
public:
	#pragma pack(push, 1)
	TableHeaderType tableHeader;
	#pragma pack(pop)
	
	#pragma pack(push, 1)
	IndexFileHeaderType indexFileHeader;
	#pragma pack(pop)
	
	int FTemporaryIndexCount;
	int tableHeaderSize;
	bool isTableOpened;
	bool isBLOBUsed;
	TaaList* fieldHeaderList;
	TaaList* indexHeaderList;
	#pragma pack(push, 1)
	BLOBIndexFileHeaderType blobFileHeader;
	#pragma pack(pop)
	
	TCompressionLevel FBlobCompression;
	int FBLOBBlockSize;
	bool FEncrypted;
	bool FReadOnly;
	bool FFilesReadOnly;
	Etblfilemanage::TaaFileStoreMode FFileStoreMode;
	System::ShortString FPassword;
	int LastIOOpTime;
	int ThresholdDelay;
	int ThresholdDelayNo;
	int ThresholdDelayMaxCount;
	int ThresholdRecordCount;
	bool FFlushesEnabled;
	DynamicArray<bool >  indexUpdated;
	int indexChangesCount;
	Etblengine::TaaRecordsArray* allRecBuffer;
	DynamicArray<Etblengine::TaaIntArray* >  indexes;
	Etblfilemanage::TAbstractFile* tableFile;
	Etblfilemanage::TAbstractFile* indexFile;
	Etblfilemanage::TAbstractFile* BLOBDataFile;
	Etblfilemanage::TAbstractFile* BLOBIndexFile;
	Etblengine::TaaBLOBHeadersArray* blobHeaders;
	Etblengine::TaaBLOBPartsArray* blobDelParts;
	Etblengine::TaaIntArray* blobMap;
	Etblengine::TaaBufferLogArray* bufferLog;
	Word recordSize;
	Word bufferSize;
	DynamicArray<int >  fieldOffsets;
	int calculatedOffset;
	int recInfoBufferSize;
	int infoBufferSize;
	int fieldFlagsSize;
	int recNullOffset;
	int recCrcOffset;
	bool FastOpen;
	bool OpenTableSucceed;
	bool IsBlobConvertNeeded;
	int DesignOpenTableState;
	AnsiString FTableName;
	TEasyDatabaseManager* DBMHandle;
	int PageRecordCount;
	__fastcall TEasyDataManager(AnsiString TableName, TEasyDatabaseManager* newDBMHandle);
	__fastcall virtual ~TEasyDataManager(void);
	int __fastcall GetDatasetCount(void);
	Etblfilemanage::TaaFileStoreMode __fastcall DetectFileStoreMode(void);
	void __fastcall SetFileStoreMode(Etblfilemanage::TaaFileStoreMode newFileStoreMode);
	bool __fastcall IsDesignMode(void);
	bool __fastcall OpenFiles(bool bCreate = false);
	void __fastcall CloseFiles(void);
	void __fastcall OpenFilesForDesigning(void);
	void __fastcall CloseFilesForDesigning(void);
	
private:
	void __fastcall InitTable(void);
	int __fastcall OpenTable(bool bNotDesignMode = false);
	void __fastcall CloseTable(bool bNotDesignMode = false);
	
public:
	void __fastcall FlushIndexesToDisk(void);
	int __fastcall ConnectDataset(TEasyDataset* DSHandle);
	void __fastcall DisconnectDataset(TEasyDataset* DSHandle);
	void __fastcall CloseAllDatasets(void);
	void __fastcall CreateTable(Db::TFieldDefs* FieldDefs, Db::TIndexDefs* IndexDefs, bool AutoIndexes, int PageRecordCount1);
	void __fastcall DeleteTable(void);
	void __fastcall EmptyTable(void);
	void __fastcall RenameTable(const AnsiString NewTableName);
	void __fastcall SaveTable(void);
	void __fastcall CopyTable(const AnsiString NewTableName, const AnsiString NewDatabaseName = "");
	void __fastcall AddIndex(const AnsiString Name, const AnsiString Fields, Db::TIndexOptions Options, const AnsiString DescFields = "", const AnsiString CaseInsFields = "", bool inMemory = false);
	AnsiString __fastcall CreateTemporaryIndex(AnsiString Fields, AnsiString DescFields, AnsiString CaseInsFields);
	void __fastcall InternalAddIndex( System::ShortString &name, Classes::TStringList* fieldNames, Classes::TStringList* sortOrders, Classes::TStringList* caseIns, Db::TIndexOptions indexOptions, bool ignoreCase, bool descending);
	int __fastcall DeleteIndex(const AnsiString Name, bool inMemory = false);
	void __fastcall DeleteAllIndexes(void);
	void __fastcall BuildIndex(int n);
	void __fastcall BuildAllIndexes(void);
	void __fastcall UpdateAllIndexes(void);
	
protected:
	int __fastcall CheckIndex(int n);
	void __fastcall CheckAllIndexes(void);
	void __fastcall CreateAutoIndexes(bool AutoIndexes);
	
public:
	bool __fastcall IsUpdateIndexesNowRecommended(void);
	void __fastcall CheckBuffersOverflow(void);
	void __fastcall FlushBuffers(void);
	void __fastcall DisableFlushes(void);
	void __fastcall EnableFlushes(bool DoCheck = true);
	void __fastcall CountBufferCrc(char * inBuffer, int inSize, char * outBuffer);
	bool __fastcall CheckBufferCrc(char * inBuffer, int inSize, char * crcBuffer);
	void __fastcall ChangeBufferEncryption(char * buffer, Byte mode);
	bool __fastcall TryToOpenEncryptedTable(void);
	bool __fastcall IsTableEncrypted(void);
	void __fastcall SaveTableHeaders(void);
	void __fastcall InternalLoadTableHeader(TableHeaderType &hdr);
	void __fastcall LoadTableHeaders(void);
	void __fastcall LoadIndexesFromDisk(void);
	void __fastcall LoadBLOBHeadersFromDisk(void);
	void __fastcall SaveBLOBHeadersToDisk(bool bCreate = false);
	void __fastcall SaveIndexesToDisk(void);
	void __fastcall SaveFieldHeadersToDisk(void);
	void __fastcall ConvertToCurrentFormat(void);
	int __fastcall InternalGetFieldNo(AnsiString FieldName, bool ExceptionAllowed = true);
	int __fastcall InternalGetIndexNo(AnsiString IndexName);
	void __fastcall SetAutoIncValue(int value);
	int __fastcall aaAddRecord(char * recordBuffer, int currentIndex);
	int __fastcall aaUpdateRecord(char * recordBuffer, int currentIndex, int recPos);
	int __fastcall aaDeleteRecord(int currentIndex, int recPos);
	void __fastcall aaAddBLOBRecord(void);
	void __fastcall aaDeleteBLOBRecord(int physRecNo);
	void __fastcall aaDeleteBLOBValue(int fieldNo, int physRecNo, bool inMemory = false);
	void __fastcall aaReadBLOBValue(Classes::TStream* bStream, int fieldNo, int physRecPos);
	void __fastcall aaWriteBLOBValue(Classes::TStream* bStream, int fieldNo, int physRecPos);
	int __fastcall aaFindIndexValue(int indexNum, int position, int recordCount = 0xffffffff);
	int __fastcall FindIndexValueForDelete(const int * indexBuffer, const int indexBuffer_Size, int position, int recordCount = 0xffffffff, bool doCheck = false);
};


class DELPHICLASS TEasyMasterDataLink;
class PASCALIMPLEMENTATION TEasyMasterDataLink : public Db::TDataLink 
{
	typedef Db::TDataLink inherited;
	
private:
	TEasyDataset* FDataSet;
	AnsiString FFieldNames;
	Classes::TList* FFields;
	Classes::TNotifyEvent FOnMasterChange;
	Classes::TNotifyEvent FOnMasterDisable;
	void __fastcall SetFieldNames(const AnsiString Value);
	
protected:
	virtual void __fastcall ActiveChanged(void);
	virtual void __fastcall CheckBrowseMode(void);
	virtual void __fastcall LayoutChanged(void);
	virtual void __fastcall RecordChanged(Db::TField* Field);
	
public:
	__fastcall TEasyMasterDataLink(TEasyDataset* DataSet);
	__fastcall virtual ~TEasyMasterDataLink(void);
	__property AnsiString FieldNames = {read=FFieldNames, write=SetFieldNames};
	__property Classes::TList* Fields = {read=FFields};
	__property Classes::TNotifyEvent OnMasterChange = {read=FOnMasterChange, write=FOnMasterChange};
	__property Classes::TNotifyEvent OnMasterDisable = {read=FOnMasterDisable, write=FOnMasterDisable};
};


typedef DynamicArray<BLOBFieldType >  EasyTable__9;

class PASCALIMPLEMENTATION TEasyDataset : public Db::TDataSet 
{
	typedef Db::TDataSet inherited;
	
private:
	bool FProjection;
	Etblengine::TaaIntArray* FProjectionMap;
	TEasyDatabase* DBHandle;
	TEasyDatabaseManager* DBMHandle;
	int TableState;
	DynamicArray<BLOBFieldType >  blobFields;
	bool AutoIncChangeEnabled;
	bool FSettingProjection;
	Classes::TStringList* FProjectionFieldList;
	Classes::TStringList* FProjectionAliasList;
	bool FDirectAccessForGetFieldValue;
	int FFreezeVisibleRecordsCount;
	void __fastcall SetTableName(AnsiString value);
	AnsiString __fastcall GetTableName();
	void __fastcall ClearBLOBStreams(void);
	Etblfilemanage::TaaFileStoreMode __fastcall GetFileStoreMode(void);
	void __fastcall CheckTableState(void);
	
protected:
	AnsiString FTableName;
	AnsiString __fastcall StripFileName(AnsiString FileName);
	void __fastcall InternalCreateTable(void);
	void __fastcall InternalDeleteTable(void);
	void __fastcall InternalEmptyTable(void);
	void __fastcall InternalRenameTable(const AnsiString NewTableName);
	void __fastcall InternalSaveTable(void);
	void __fastcall InternalCopyTable(const AnsiString NewTableName, const AnsiString NewDatabaseName = "");
	bool __fastcall InternalAddRecords(Db::TDataSet* Dataset, TAddRecordsMode Mode, AnsiString &Log);
	bool __fastcall InternalImportTable(Db::TDataSource* dataSource, Db::TIndexDefs* indexDefinitions, AnsiString &log);
	bool __fastcall InternalExportTable(Db::TDataSource* dataSource, Db::TIndexDefs* indexDefinitions, Sysutils::TProcedure createTablePtr, AnsiString &log, bool ToParadox = false);
	void __fastcall InternalRestructureTable(bool NewEncrypted, AnsiString NewPassword, int NewBLOBBlockSize, TCompressionLevel NewBLOBCompression)/* overload */;
	void __fastcall InternalRestructureTable(void)/* overload */;
	bool __fastcall InternalRepairTable(AnsiString &log);
	
public:
	void __fastcall FreezeVisibleRecords(void);
	void __fastcall UnfreezeVisibleRecords(void);
	bool __fastcall VisibleRecordsFreezed(void);
	void __fastcall InternalAddIndex(const AnsiString Name, const AnsiString Fields, Db::TIndexOptions Options, const AnsiString DescFields = "", const AnsiString CaseInsFields = "");
	AnsiString __fastcall CreateTemporaryIndex(AnsiString Fields, AnsiString DescFields, AnsiString CaseInsFields);
	
protected:
	void __fastcall InternalDeleteIndex(const AnsiString Name);
	void __fastcall InternalDeleteAllIndexes(void);
	
public:
	TEasyDataManager* DMHandle;
	bool debugFlag;
	int PageRecordCount;
	void __fastcall CreateTemporaryTable(int RecordCount1 = 0x3e8);
	void __fastcall GetDatabaseNameList(Classes::TStrings* List);
	__fastcall virtual TEasyDataset(Classes::TComponent* AOwner);
	__fastcall virtual ~TEasyDataset(void);
	void __fastcall GetIndexNames(Classes::TStrings* List);
	void __fastcall OpenTable(void);
	void __fastcall CloseTable(void);
	bool __fastcall IsTableEncrypted(void);
	
protected:
	void __fastcall InternalFlushBuffers(void);
	void __fastcall aaReadBLOBValue(int FieldNo);
	void __fastcall aaWriteBLOBValue(int FieldNo);
	void __fastcall aaDeleteBLOBRecord(void);
	void __fastcall aaSaveBLOBData(void);
	
public:
	Classes::TMemoryStream* __fastcall InternalCreateBlobStream(Db::TField* Field, Db::TBlobStreamMode Mode);
	virtual Classes::TStream* __fastcall CreateBlobStream(Db::TField* Field, Db::TBlobStreamMode Mode);
	virtual void __fastcall CloseBlob(Db::TField* Field);
	
protected:
	void __fastcall SetTablePosition(int value);
	int __fastcall GetCurrentID(void);
	char * __fastcall GetCurrentRecordBuffer(void);
	virtual char * __fastcall AllocRecordBuffer(void);
	virtual void __fastcall FreeRecordBuffer(char * &Buffer);
	virtual Word __fastcall GetRecordSize(void);
	virtual int __fastcall GetRecordCount(void);
	virtual void __fastcall InternalInitFieldDefs(void);
	virtual void __fastcall InternalOpen(void);
	virtual void __fastcall InternalClose(void);
	virtual bool __fastcall IsCursorOpen(void);
	virtual void __fastcall InternalInitRecord(char * Buffer);
	virtual void __fastcall InternalHandleException(void);
	virtual void __fastcall SetRecNo(int Value);
	virtual int __fastcall GetRecNo(void);
	void __fastcall SetTablePositionByPhysRecNo(int physRecNo);
	int __fastcall GetTablePositionByPhysRecNo(int physRecNo);
	virtual Db::TGetResult __fastcall GetRecord(char * Buffer, Db::TGetMode GetMode, bool DoCheck);
	virtual void __fastcall DataConvert(Db::TField* Field, void * Source, void * Dest, bool ToNative);
	
private:
	TKeyBuffer *FKeyBuffers[3];
	TKeyBuffer *FKeyBuffer;
	bool IsRanged;
	void __fastcall AllocKeyBuffers(void);
	void __fastcall FreeKeyBuffers(void);
	PKeyBuffer __fastcall InitKeyBuffer(PKeyBuffer Buffer);
	void __fastcall SetKeyFields(TKeyIndex KeyIndex, const System::TVarRec * Values, const int Values_Size);
	int __fastcall GetKeyFieldCount(void);
	void __fastcall SetKeyFieldCount(int Value);
	void __fastcall CheckSetKeyMode(void);
	void __fastcall SetKeyBuffer(TKeyIndex KeyIndex, bool Clear);
	bool __fastcall SetCursorRange(void);
	bool __fastcall ResetCursorRange(void);
	bool __fastcall GetKeyExclusive(void);
	void __fastcall SetKeyExclusive(bool Value);
	
public:
	bool __fastcall FindKey(const System::TVarRec * KeyValues, const int KeyValues_Size);
	void __fastcall FindNearest(const System::TVarRec * KeyValues, const int KeyValues_Size);
	void __fastcall EditKey(void);
	bool __fastcall GotoKey(void);
	void __fastcall GotoNearest(void);
	void __fastcall SetKey(void);
	void __fastcall ApplyRange(void);
	void __fastcall CancelRange(void);
	void __fastcall EditRangeEnd(void);
	void __fastcall EditRangeStart(void);
	void __fastcall SetRange(const System::TVarRec * StartValues, const int StartValues_Size, const System::TVarRec * EndValues, const int EndValues_Size);
	void __fastcall SetRangeEnd(void);
	void __fastcall SetRangeStart(void);
	__property int KeyFieldCount = {read=GetKeyFieldCount, write=SetKeyFieldCount, nodefault};
	__property bool KeyExclusive = {read=GetKeyExclusive, write=SetKeyExclusive, nodefault};
	void __fastcall SetProjection(Classes::TStringList* FieldList, Classes::TStringList* AliasList, bool OnlyStoreLists = false);
	void __fastcall SetDistinct(AnsiString DistinctFields);
	HIDESBASE void __fastcall GetFieldValue(Etblcommon::TETblDataValue &value, int FieldNo, bool bCopy = false);
	HIDESBASE void __fastcall SetFieldValue(Etblcommon::TETblDataValue &value, int FieldNo);
	virtual bool __fastcall GetFieldData(Db::TField* Field, void * Buffer)/* overload */;
	virtual bool __fastcall Locate(const AnsiString KeyFields, const Variant &KeyValues, Db::TLocateOptions Options);
	virtual Variant __fastcall Lookup(const AnsiString KeyFields, const Variant &KeyValues, const AnsiString ResultFields);
	
protected:
	virtual void __fastcall SetFieldData(Db::TField* Field, void * Buffer)/* overload */;
	virtual void __fastcall InternalFirst(void);
	virtual void __fastcall InternalLast(void);
	virtual void __fastcall InternalSetToRecord(char * Buffer);
	virtual Db::TBookmarkFlag __fastcall GetBookmarkFlag(char * Buffer);
	virtual void __fastcall GetBookmarkData(char * Buffer, void * Data);
	virtual void __fastcall InternalGotoBookmark(void * Bookmark);
	virtual void __fastcall SetBookmarkFlag(char * Buffer, Db::TBookmarkFlag Value);
	virtual void __fastcall SetBookmarkData(char * Buffer, void * Data);
	
public:
	virtual int __fastcall CompareBookmarks(void * Bookmark1, void * Bookmark2);
	virtual bool __fastcall BookmarkValid(void * Bookmark);
	void __fastcall DirectInsert(void);
	void __fastcall DirectPost(void);
	void __fastcall SetSQLFilter(System::TObject* FilterExpr);
	
protected:
	virtual void __fastcall InternalAddRecord(void * Buffer, bool Append);
	virtual void __fastcall InternalInsert(void);
	virtual void __fastcall InternalCancel(void);
	virtual void __fastcall InternalPost(void);
	virtual void __fastcall InternalDelete(void);
	virtual bool __fastcall GetCanModify(void);
	bool __fastcall GetExists(void);
	virtual void __fastcall UpdateIndexDefs(void);
	void __fastcall SetActiveBuffer(void);
	virtual bool __fastcall FindRecord(bool Restart, bool GoForward);
	virtual void __fastcall ClearCalcFields(char * Buffer);
	bool __fastcall FilterRecord(char * Buffer);
	virtual void __fastcall InternalRefresh(void);
	
public:
	AnsiString FDistinctFields;
	Etblengine::TaaIntArray* visibleRecords;
	int visibleRecordCount;
	
private:
	int FDistinctIndexNo;
	char *FTemporaryRecordBuffer;
	bool FDirectInsert;
	bool FDirectFilter;
	System::TObject* FSQLFilterExpr;
	AnsiString FDatabaseName;
	AnsiString FDatabaseFileName;
	int tablePosition;
	bool isTableOpened;
	bool isIndexUsed;
	int currentIndex;
	DynamicArray<int >  foundRecords;
	int foundRecordCount;
	int foundRecordNo;
	bool foundRecordsNeedUpdate;
	AnsiString FFilter;
	Db::TFilterOptions FFilterOptions;
	bool FEncrypted;
	AnsiString FPassword;
	Db::TIndexDefs* FIndexDefs;
	Db::TIndexDefs* FRestructureIndexDefs;
	Db::TFieldDefs* FRestructureFieldDefs;
	bool FStoreDefs;
	AnsiString FIndexName;
	AnsiString FIndexFieldNames;
	bool createIndexDefs;
	Etblengine::TSearchParser* FilterParser;
	Etblengine::TSearchParser* MasterDetailParser;
	Etblengine::TSearchParser* FindParser;
	TaaList* foundVisibleRecordsList;
	char *FFilterBuffer;
	bool FExclusive;
	TEasyMasterDataLink* FMasterLink;
	bool insertMode;
	bool visRecUpdated;
	TaaProgressEvent FOnProgress;
	Extended FProgress;
	Extended FProgressMax;
	TaaProgressProcess FProgressProcess;
	TBuildIndexesProgressEvent FBuildIndexesProgress;
	bool FInMemory;
	bool FAutoIndexes;
	bool FTemporary;
	int FBLOBBlockSize;
	TCompressionLevel FBLOBCompression;
	bool FReadOnly;
	bool FSetActiveBufferFlag;
	bool FFastOpen;
	int FoldFastOpen;
	int FoldFastOpen2;
	AnsiString __fastcall GetDBName();
	void __fastcall OpenIndex( System::ShortString &name, int number = 0xffffffff);
	void __fastcall CloseIndex(void);
	
public:
	void __fastcall BuildIndex(int n);
	void __fastcall BuildAllIndexes(void);
	void __fastcall UpdateAllIndexes(void);
	int __fastcall CheckIndex(int n);
	void __fastcall CheckAllIndexes(void);
	
private:
	int __fastcall CompareRecordBuffersWithIndex(char * RecordBuffer1, char * RecordBuffer2, int IndexNo, int IndexFieldCount);
	int __fastcall CompareInIndex(char * RecordBuffer, int IndexNo, int PosInIndex, int IndexFieldCount);
	int __fastcall FindInIndex(char * RecordBuffer, int IndexNo, int IndexFieldCount, bool bForwardDirection, bool bExact);
	int __fastcall FindInVisibleRecords(char * RecordBuffer, int IndexFieldCount, bool bForwardDirection, bool bExact);
	bool __fastcall IsFiltered(void);
	bool __fastcall IsRecordVisible(char * recordBuffer, bool bRunOnFilterRecord = true);
	bool __fastcall IsViewConstrained(void);
	void __fastcall aaAddRecord(char * recordBuffer);
	void __fastcall aaUpdateRecord(char * recordBuffer);
	void __fastcall aaDeleteRecord(void);
	int __fastcall GetVisRecValue(int recordNum);
	void __fastcall CreateIndexDefinitions(void);
	int __fastcall GetIndexNoByFields(const AnsiString Fields, AnsiString DescFields = "*", bool CaseSensitive = true);
	void __fastcall SetIndexDefs(Db::TIndexDefs* Value);
	int __fastcall GetIndexFieldCount(void);
	AnsiString __fastcall GetIndexName();
	void __fastcall SetIndexName(const AnsiString Name);
	AnsiString __fastcall GetIndexFieldNames();
	void __fastcall SetIndexFieldNames(const AnsiString Value);
	Db::TField* __fastcall GetIndexField(int Index);
	void __fastcall SetIndexField(int Index, Db::TField* Value);
	void __fastcall SetDatabaseName(AnsiString name);
	void __fastcall SetDatabaseFileName(AnsiString FileName);
	AnsiString __fastcall GetCurrentVersionText();
	void __fastcall SetCurrentVersionText(AnsiString s);
	bool __fastcall GetEncrypted(void);
	
public:
	int __fastcall GetTablePositionByID(int id);
	void __fastcall GetMatchedRecords(const Etblengine::TSearchOperation &searchOperation, Db::TFilterOptions curFilterOptions, Etblengine::TBitsArray* &recordBits);
	void __fastcall GetMatchedRecordsArray(const Etblengine::TSearchOperation &searchCondition, Db::TFilterOptions curFilterOptions, TaaGMRMode mode, aInteger &FoundRecords, int &FoundRecordCount);
	bool __fastcall IsRecordMatches(const Etblengine::TSearchOperation &searchOperation, Db::TFilterOptions curFilterOptions, char * recordBuf);
	int __fastcall InternalLocate(const Etblengine::TSearchOperation * searchConditions, const int searchConditions_Size, int ConditionCount, Db::TFilterOptions curFilterOptions);
	int __fastcall PrepareAndLocate(const AnsiString KeyFields, const Variant &KeyValues, Etblengine::TSearchOperator so, Db::TFilterOptions fo);
	void __fastcall PrepareValueBuffer(int FieldNo, Etblengine::TSearchOperator &SearchOp, AnsiString value, char * &valueBuffer);
	bool __fastcall IsFieldTypeSupported(Db::TFieldType fType);
	void __fastcall GetSupportedFieldTypes(TaaList* typeList);
	AnsiString __fastcall GetTableFileExtension();
	
private:
	bool __fastcall IsStrMatchPattern(char * StrPtr, char * PatternPtr, bool bIgnoreCase);
	bool __fastcall IsWideStrMatchPattern(wchar_t * StrPtr, wchar_t * PatternPtr, bool bIgnoreCase);
	
public:
	void __fastcall CreateVisibleRecordsList(void);
	void __fastcall AssignVisibleRecordsList(Etblengine::TaaIntArray* visRecords);
	
protected:
	virtual void __fastcall SetFiltered(bool f);
	
private:
	char * __fastcall GetActiveRecordBuffer(void);
	void __fastcall SetExclusive(bool Value);
	AnsiString __fastcall GetMasterFields();
	void __fastcall SetMasterFields(const AnsiString Value);
	void __fastcall CheckMasterRange(void);
	void __fastcall MasterChanged(System::TObject* Sender);
	void __fastcall MasterDisabled(System::TObject* Sender);
	void __fastcall ChangeMasterCondition(Classes::TList* MasterFields);
	bool __fastcall FieldDefsStored(void);
	bool __fastcall IndexDefsStored(void);
	
protected:
	virtual Db::TDataSource* __fastcall GetDataSource(void);
	
private:
	void __fastcall SetDataSource(Db::TDataSource* Value);
	void __fastcall SetInMemory(bool Value);
	void __fastcall SetTemporary(bool Value);
	int __fastcall GetLastAutoIncValue(void);
	TCompressionLevel __fastcall GetBLOBCompression(void);
	void __fastcall SetBLOBCompression(TCompressionLevel value);
	int __fastcall GetBLOBBlockSize(void);
	void __fastcall SetBLOBBlockSize(int Value);
	void __fastcall SetReadOnly(bool Value);
	
protected:
	void __fastcall DoOnProgress(double Progress);
	void __fastcall DoOnBuildIndexesProgress(double Progress, bool bStart, bool bFinish);
	__property TEasyMasterDataLink* MasterLink = {read=FMasterLink};
	
public:
	void __fastcall SetAutoIncValue(int value);
	__property int IndexFieldCount = {read=GetIndexFieldCount, nodefault};
	__property Db::TField* IndexFields[int Index] = {read=GetIndexField, write=SetIndexField};
	__property int RecNo = {read=GetRecNo, write=SetRecNo, nodefault};
	__property int LastAutoIncValue = {read=GetLastAutoIncValue, nodefault};
	__property Db::TIndexDefs* RestructureIndexDefs = {read=FRestructureIndexDefs};
	__property Db::TFieldDefs* RestructureFieldDefs = {read=FRestructureFieldDefs};
	__property bool Temporary = {read=FTemporary, write=SetTemporary, nodefault};
	__property bool FastOpen = {read=FFastOpen, write=FFastOpen, default=1};
	__property Db::TIndexDefs* IndexDefs = {read=FIndexDefs, write=SetIndexDefs, stored=IndexDefsStored};
	__property FieldDefs  = {stored=FieldDefsStored};
	__property AnsiString CurrentVersion = {read=GetCurrentVersionText, write=SetCurrentVersionText};
	__property AnsiString IndexName = {read=GetIndexName, write=SetIndexName};
	__property AnsiString IndexFieldNames = {read=GetIndexFieldNames, write=SetIndexFieldNames};
	__property AnsiString TableName = {read=GetTableName, write=SetTableName};
	__property AnsiString DatabaseName = {read=FDatabaseName, write=SetDatabaseName};
	__property AnsiString DatabaseFileName = {read=FDatabaseFileName, write=SetDatabaseFileName};
	__property TCompressionLevel BLOBCompression = {read=GetBLOBCompression, write=SetBLOBCompression, default=0};
	__property int BLOBBlockSize = {read=GetBLOBBlockSize, write=SetBLOBBlockSize, default=512};
	__property bool Encrypted = {read=GetEncrypted, write=FEncrypted, default=0};
	__property AnsiString Password = {read=FPassword, write=FPassword};
	__property AnsiString Filter = {read=FFilter, write=FFilter};
	__property Db::TFilterOptions FilterOptions = {read=FFilterOptions, write=FFilterOptions, nodefault};
	__property bool Exists = {read=GetExists, nodefault};
	__property bool ReadOnly = {read=FReadOnly, write=SetReadOnly, default=0};
	__property bool StoreDefs = {read=FStoreDefs, write=FStoreDefs, default=0};
	__property bool Exclusive = {read=FExclusive, write=SetExclusive, default=0};
	__property AnsiString MasterFields = {read=GetMasterFields, write=SetMasterFields};
	__property Db::TDataSource* MasterSource = {read=GetDataSource, write=SetDataSource};
	__property TaaProgressEvent OnProgress = {read=FOnProgress, write=FOnProgress};
	__property TBuildIndexesProgressEvent OnBuildIndexesProgress = {read=FBuildIndexesProgress, write=FBuildIndexesProgress};
	__property bool InMemory = {read=FInMemory, write=SetInMemory, nodefault};
	__property bool AutoIndexes = {read=FAutoIndexes, write=FAutoIndexes, nodefault};
	__property AutoCalcFields  = {default=1};
	__property Active  = {default=0};
	__property Filtered  = {default=0};
	__property CanModify ;
	__property BeforeOpen ;
	__property AfterOpen ;
	__property BeforeClose ;
	__property AfterClose ;
	__property BeforeInsert ;
	__property AfterInsert ;
	__property BeforeEdit ;
	__property AfterEdit ;
	__property BeforePost ;
	__property AfterPost ;
	__property BeforeCancel ;
	__property AfterCancel ;
	__property BeforeDelete ;
	__property AfterDelete ;
	__property BeforeScroll ;
	__property AfterScroll ;
	__property OnCalcFields ;
	__property OnDeleteError ;
	__property OnEditError ;
	__property OnFilterRecord ;
	__property OnNewRecord ;
	__property OnPostError ;
	
/* Hoisted overloads: */
	
public:
	inline bool __fastcall  GetFieldData(int FieldNo, void * Buffer){ return TDataSet::GetFieldData(FieldNo, Buffer); }
	inline bool __fastcall  GetFieldData(Db::TField* Field, void * Buffer, bool NativeFormat){ return TDataSet::GetFieldData(Field, Buffer, NativeFormat); }
	
protected:
	inline void __fastcall  SetFieldData(Db::TField* Field, void * Buffer, bool NativeFormat){ TDataSet::SetFieldData(Field, Buffer, NativeFormat); }
	
};


class DELPHICLASS TEasyTable;
class PASCALIMPLEMENTATION TEasyTable : public TEasyDataset 
{
	typedef TEasyDataset inherited;
	
public:
	void __fastcall CreateTable(void)/* overload */;
	void __fastcall CreateTable(AnsiString NewTableName)/* overload */;
	void __fastcall DeleteTable(void);
	void __fastcall EmptyTable(void);
	void __fastcall RenameTable(const AnsiString NewTableName);
	void __fastcall CopyTable(const AnsiString NewTableName, const AnsiString NewDatabaseName = "");
	void __fastcall SaveTable(void);
	bool __fastcall AddRecords(Db::TDataSet* Dataset, TAddRecordsMode Mode, AnsiString &Log);
	bool __fastcall ImportTable(Db::TDataSource* dataSource, Db::TIndexDefs* indexDefinitions, AnsiString &log);
	bool __fastcall ExportTable(Db::TDataSource* dataSource, Db::TIndexDefs* indexDefinitions, Sysutils::TProcedure createTablePtr, AnsiString &log, bool ToParadox = false);
	void __fastcall RestructureTable(bool NewEncrypted, AnsiString NewPassword, int NewBLOBBlockSize, TCompressionLevel NewBLOBCompression)/* overload */;
	void __fastcall RestructureTable(void)/* overload */;
	bool __fastcall RepairTable(AnsiString &log);
	void __fastcall AddIndex(const AnsiString Name, const AnsiString Fields, Db::TIndexOptions Options, const AnsiString DescFields = "", const AnsiString CaseInsFields = "");
	void __fastcall DeleteIndex(const AnsiString Name);
	void __fastcall DeleteAllIndexes(void);
	void __fastcall FlushBuffers(void);
	HIDESBASE void __fastcall GetSupportedFieldTypes(TaaList* typeList);
	HIDESBASE bool __fastcall IsFieldTypeSupported(Db::TFieldType fType);
	HIDESBASE AnsiString __fastcall GetTableFileExtension();
	HIDESBASE AnsiString __fastcall GetMasterFields();
	HIDESBASE void __fastcall SetMasterFields(const AnsiString Value);
	HIDESBASE void __fastcall CheckMasterRange(void);
	HIDESBASE void __fastcall MasterChanged(System::TObject* Sender);
	HIDESBASE void __fastcall MasterDisabled(System::TObject* Sender);
	HIDESBASE void __fastcall ChangeMasterCondition(Classes::TList* MasterFields);
	HIDESBASE bool __fastcall FieldDefsStored(void);
	HIDESBASE bool __fastcall IndexDefsStored(void);
	void __fastcall GetTableNameList(Classes::TStrings* List);
	
protected:
	virtual Db::TDataSource* __fastcall GetDataSource(void);
	virtual void __fastcall DoOnNewRecord(void);
	HIDESBASE void __fastcall DoOnProgress(double Progress);
	__property TEasyMasterDataLink* MasterLink = {read=FMasterLink};
	
public:
	__property KeyFieldCount ;
	__property KeyExclusive ;
	__property RestructureIndexDefs ;
	__property RestructureFieldDefs ;
	__property LastAutoIncValue ;
	
__published:
	__property Filter ;
	__property FilterOptions ;
	__property Filtered  = {default=0};
	__property Exists ;
	__property CurrentVersion ;
	__property TableName ;
	__property DatabaseName ;
	__property DatabaseFileName ;
	__property IndexDefs ;
	__property FieldDefs ;
	__property IndexName ;
	__property IndexFieldNames ;
	__property BLOBCompression  = {default=0};
	__property BLOBBlockSize  = {default=512};
	__property Encrypted  = {default=0};
	__property Password ;
	__property ReadOnly  = {default=0};
	__property StoreDefs  = {default=0};
	__property Exclusive  = {default=0};
	__property MasterFields ;
	__property MasterSource ;
	__property InMemory ;
	__property OnProgress ;
	__property AutoIndexes ;
	__property OnBuildIndexesProgress ;
	__property AutoCalcFields  = {default=1};
	__property Active  = {default=0};
	__property CanModify ;
	__property BeforeOpen ;
	__property AfterOpen ;
	__property BeforeClose ;
	__property AfterClose ;
	__property BeforeInsert ;
	__property AfterInsert ;
	__property BeforeEdit ;
	__property AfterEdit ;
	__property BeforePost ;
	__property AfterPost ;
	__property BeforeCancel ;
	__property AfterCancel ;
	__property BeforeDelete ;
	__property AfterDelete ;
	__property BeforeScroll ;
	__property AfterScroll ;
	__property OnCalcFields ;
	__property OnDeleteError ;
	__property OnEditError ;
	__property OnFilterRecord ;
	__property OnNewRecord ;
	__property OnPostError ;
public:
	#pragma option push -w-inl
	/* TEasyDataset.Create */ inline __fastcall virtual TEasyTable(Classes::TComponent* AOwner) : TEasyDataset(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TEasyDataset.Destroy */ inline __fastcall virtual ~TEasyTable(void) { }
	#pragma option pop
	
};


class DELPHICLASS TEasyQueryDataLink;
class DELPHICLASS TEasyQuery;
class PASCALIMPLEMENTATION TEasyQuery : public TEasyDataset 
{
	typedef TEasyDataset inherited;
	
private:
	Etblsqlprocessor::TSQLScriptProcessor* FSQLProcessor;
	Classes::TStrings* FSQL2;
	char *FSQLBinary;
	AnsiString FText;
	Db::TDataLink* FDataLink;
	Db::TParams* FParams;
	bool FParamCheck;
	int FRowsAffected;
	TEasyTable* ResultTable;
	bool FRequestLive;
	void __fastcall SetQuery(Classes::TStrings* Value);
	void __fastcall SetParamsList(Db::TParams* Value);
	void __fastcall SetParamsFromCursor(void);
	void __fastcall QueryChanged(System::TObject* Sender);
	void __fastcall ReadParamData(Classes::TReader* Reader);
	void __fastcall WriteParamData(Classes::TWriter* Writer);
	void __fastcall ReadBinaryData(Classes::TStream* Stream);
	void __fastcall WriteBinaryData(Classes::TStream* Stream);
	void __fastcall RefreshParams(void);
	
protected:
	Classes::TStrings* FSQL3;
	Classes::TStrings* FSQL;
	Classes::TStrings* FSQL5;
	Classes::TStrings* FSQL4;
	HIDESBASE void __fastcall SetDataSource(Db::TDataSource* Value);
	virtual Db::TDataSource* __fastcall GetDataSource(void);
	Word __fastcall GetParamsCount(void);
	virtual void __fastcall DefineProperties(Classes::TFiler* Filer);
	virtual void __fastcall InternalOpen(void);
	virtual void __fastcall InternalClose(void);
	
public:
	__fastcall virtual TEasyQuery(Classes::TComponent* AOwner);
	__fastcall virtual ~TEasyQuery(void);
	void __fastcall ExecSQL(void);
	virtual void __fastcall GetDetailLinkFields(Classes::TList* MasterFields, Classes::TList* DetailFields);
	Db::TParam* __fastcall ParamByName(const AnsiString Value);
	void __fastcall InternalOpenAsTable(void);
	void __fastcall InternalCloseAsTable(void);
	__property Word ParamCount = {read=GetParamsCount, nodefault};
	__property int RowsAffected = {read=FRowsAffected, nodefault};
	__property char * SQLBinary = {read=FSQLBinary, write=FSQLBinary};
	__property AnsiString Text = {read=FText};
	
__published:
	__property bool ParamCheck = {read=FParamCheck, write=FParamCheck, default=1};
	__property bool RequestLive = {read=FRequestLive, write=FRequestLive, nodefault};
	__property Classes::TStrings* SQL = {read=FSQL, write=SetQuery};
	__property Db::TParams* Params = {read=FParams, write=SetParamsList, stored=false};
	__property CurrentVersion ;
	__property DatabaseName ;
	__property DatabaseFileName ;
	__property InMemory ;
	__property Db::TDataSource* DataSource = {read=GetDataSource, write=SetDataSource};
	__property Filter ;
	__property FilterOptions ;
	__property Filtered  = {default=0};
	__property AutoCalcFields  = {default=1};
	__property Active  = {default=0};
	__property CanModify ;
	__property BeforeOpen ;
	__property AfterOpen ;
	__property BeforeClose ;
	__property AfterClose ;
	__property BeforeInsert ;
	__property AfterInsert ;
	__property BeforeEdit ;
	__property AfterEdit ;
	__property BeforePost ;
	__property AfterPost ;
	__property BeforeCancel ;
	__property AfterCancel ;
	__property BeforeDelete ;
	__property AfterDelete ;
	__property BeforeScroll ;
	__property AfterScroll ;
	__property OnCalcFields ;
	__property OnDeleteError ;
	__property OnEditError ;
	__property OnFilterRecord ;
	__property OnNewRecord ;
	__property OnPostError ;
};


class PASCALIMPLEMENTATION TEasyQueryDataLink : public Db::TDetailDataLink 
{
	typedef Db::TDetailDataLink inherited;
	
private:
	TEasyQuery* FQuery;
	
protected:
	virtual void __fastcall ActiveChanged(void);
	virtual void __fastcall RecordChanged(Db::TField* Field);
	virtual Db::TDataSet* __fastcall GetDetailDataSet(void);
	virtual void __fastcall CheckBrowseMode(void);
	
public:
	__fastcall TEasyQueryDataLink(TEasyQuery* AQuery);
public:
	#pragma option push -w-inl
	/* TDataLink.Destroy */ inline __fastcall virtual ~TEasyQueryDataLink(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TEasyDatabase : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	AnsiString FDirectory;
	bool FConnected;
	AnsiString FDatabaseName;
	AnsiString FDatabaseFileName;
	bool FInMemory;
	bool FReadOnly;
	TProgressEvent FOnProgress;
	bool FCancel;
	AnsiString FPassword;
	void __fastcall SetConnected(bool value);
	void __fastcall SetDatabaseName(AnsiString name);
	void __fastcall SetDatabaseFileName(AnsiString FileName);
	void __fastcall SetDirectory(AnsiString dir);
	void __fastcall SetInMemory(bool Value);
	bool __fastcall GetEncrypted(void);
	bool __fastcall GetExists(void);
	void __fastcall DoOnProgress(double Progress, TaaProgressProcess FProgressProcess);
	
public:
	TEasyDatabaseManager* DBMHandle;
	__fastcall virtual TEasyDatabase(Classes::TComponent* AOwner);
	__fastcall virtual ~TEasyDatabase(void);
	void __fastcall CreateDatabase(void)/* overload */;
	void __fastcall CreateDatabase(AnsiString NewDatabaseFileName)/* overload */;
	void __fastcall DeleteDatabase(void);
	void __fastcall CompactProgress(System::TObject* Sender, double PercentDone, bool &Cancel);
	bool __fastcall CompactDatabase(AnsiString &log);
	void __fastcall RepairProgress(System::TObject* Sender, double PercentDone, bool &Cancel);
	void __fastcall ChangeEncryptionProgress(System::TObject* Sender, double PercentDone, bool &Cancel);
	bool __fastcall RepairDatabase(AnsiString &log, bool DeleteCorruptedFiles = false);
	bool __fastcall RenameDatabase(const AnsiString NewDatabaseName);
	bool __fastcall CopyDatabase(const AnsiString NewDatabaseName);
	bool __fastcall ChangeEncryption(AnsiString newPassword = "");
	void __fastcall Open(void);
	void __fastcall Close(void);
	void __fastcall GetTablesList(Classes::TStrings* List);
	bool __fastcall TableExists(AnsiString TableName);
	void __fastcall DeleteTable(AnsiString TableName);
	__property bool Exists = {read=GetExists, nodefault};
	
__published:
	__property bool Connected = {read=FConnected, write=SetConnected, default=0};
	__property AnsiString DatabaseFileName = {read=FDatabaseFileName, write=SetDatabaseFileName};
	__property AnsiString DatabaseName = {read=FDatabaseName, write=SetDatabaseName};
	__property AnsiString Directory = {read=FDirectory, write=SetDirectory};
	__property bool Encrypted = {read=GetEncrypted, nodefault};
	__property bool InMemory = {read=FInMemory, write=SetInMemory, nodefault};
	__property AnsiString Password = {read=FPassword, write=FPassword};
	__property bool ReadOnly = {read=FReadOnly, write=FReadOnly, nodefault};
	__property TProgressEvent OnProgress = {read=FOnProgress, write=FOnProgress};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint MAX_SUPPORTED_BLOB_COMPRESSION_LEVELS = 0x4;
extern PACKAGE TBlobCompressionLevel SUPPORTED_BLOB_COMPRESSION_LEVELS[4];
extern PACKAGE Classes::TFileStream* logFile;
static const Shortint MAX_NAME_LENGTH = 0x14;
static const Byte AutoIncOn = 0xf0;
static const Byte AutoIncOff = 0xfc;
static const Word DEFAULT_BLOB_BLOCK_SIZE = 0x200;
#define DEFAULT_BLOB_COMPRESSION (TCompressionLevel)(0)
#define tableFileExtension ".dat"
#define indexFileExtension ".idx"
#define blobIndexFileExtension ".bif"
#define blobDataFileExtension ".bdf"
#define DatabaseFileExtension ".edb"
#define DEFAULT_PRIMARY_KEY_NAME "id"
static const Shortint MAX_INDEX_CHANGES = 0xf;
static const Shortint TETERR_NO_ERROR = 0x0;
static const Shortint TETERR_NO_TABLE = 0xffffffff;
static const Shortint TETERR_NO_PASSWORD = 0xfffffffe;
static const Shortint TETERR_INVALID_PASSWORD = 0xfffffffd;
static const Shortint TETERR_OPEN_FILES = 0xfffffffc;
#define crlf "\r\n"
extern PACKAGE unsigned startTime;
extern PACKAGE unsigned stopTime;
extern PACKAGE bool timeStarted;
extern PACKAGE bool timeRestarted;
extern PACKAGE bool bDesignMode;
extern PACKAGE Classes::TList* DatabaseManagerList;
extern PACKAGE Classes::TList* DatabaseList;
extern PACKAGE Classes::TList* DataManagerList;
extern PACKAGE double InternalCurrentVersion;
extern PACKAGE double lastFormatVersion;
extern PACKAGE AnsiString internalCurrentVersionText;
extern PACKAGE Etblfilemanage::TPFSManager* PFSManager;
extern PACKAGE TEasyDatabaseManager* __fastcall aaGetDatabaseManager(AnsiString DBName, TEasyDataset* EDS = (TEasyDataset*)(0x0));
extern PACKAGE TEasyDatabase* __fastcall aaFindDatabase(AnsiString DBName);
extern PACKAGE int __fastcall aaFindIndexByFields(TEasyDataset* Table, AnsiString IndexFieldNames, AnsiString DescFields, AnsiString CaseInsensitiveFields);
extern PACKAGE int __fastcall GetStringParams(AnsiString params, Classes::TStringList* paramList);
extern PACKAGE bool __fastcall isStreamGraphic(Classes::TStream* stream);
extern PACKAGE bool __fastcall FindFieldInSourceTable(Db::TFieldDefs* fieldDefinitions, AnsiString name);
extern PACKAGE Db::TDateTimeRec __fastcall DateTimeToNative(Db::TFieldType DataType, System::TDateTime Data);
extern PACKAGE bool __fastcall IsBLOBFieldType(Db::TFieldType FieldType);
extern PACKAGE bool __fastcall IsFieldTypeCanCompriseIndex(Db::TFieldType FieldType);

}	/* namespace Easytable */
using namespace Easytable;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// EasyTable
