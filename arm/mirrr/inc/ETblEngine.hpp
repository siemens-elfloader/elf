// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ETblEngine.pas' rev: 6.00

#ifndef ETblEngineHPP
#define ETblEngineHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <DB.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <ETblFileManage.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Etblengine
{
//-- type declarations -------------------------------------------------------
typedef DynamicArray<Byte >  ETblEngine__2;

class DELPHICLASS TBitsArray;
class PASCALIMPLEMENTATION TBitsArray : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	DynamicArray<Byte >  bits;
	int bitCount;
	__fastcall TBitsArray(int length);
	__fastcall virtual ~TBitsArray(void);
	void __fastcall SetSize(int length);
	int __fastcall FindFirst(bool bitValue);
	int __fastcall FindNext(void);
	void __fastcall SetBit(int bitNo, bool bitValue);
	bool __fastcall GetBit(int bitNo);
	void __fastcall SetBits(bool bitValue);
	void __fastcall NotBits(void);
	void __fastcall AndBits(TBitsArray* bits1);
	void __fastcall OrBits(TBitsArray* bits1);
	void __fastcall AndBit(int bitNo, bool bitValue);
	void __fastcall OrBit(int bitNo, bool bitValue);
	
private:
	int FBitNo;
	Byte FBitValue;
};


#pragma option push -b-
enum TSearchOperator { soEQ, soNEQ, soLTE, soGTE, soLT, soGT, soLike, soNotLike, soIsNull, soIsNotNull };
#pragma option pop

#pragma option push -b-
enum TBoolOperator { boNone, boNot, boAnd, boOr, boOpenParenthesis, boCloseParenthesis };
#pragma option pop

#pragma pack(push, 4)
struct TSearchOperation
{
	TBoolOperator BoolOp;
	int FieldNo;
	AnsiString FieldName;
	TSearchOperator SearchOp;
	bool bPartialCompare;
	char *ValueBuffer;
} ;
#pragma pack(pop)

typedef DynamicArray<TSearchOperation >  TSearchOperations;

typedef DynamicArray<TBitsArray* >  ETblEngine__4;

class DELPHICLASS TSearchParser;
class PASCALIMPLEMENTATION TSearchParser : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	Db::TDataSet* ds;
	AnsiString ParsedStr;
	DynamicArray<TBitsArray* >  bitsArr;
	int bitsArrCount;
	int bitsArrNo;
	int AllocBy;
	char *recordBuffer;
	bool __fastcall IsStartStr(AnsiString s1, int &n, AnsiString s2);
	void __fastcall PreParseBooleanExpression(int &n);
	void __fastcall PreParseBooleanSum(int &n);
	void __fastcall PreParseBooleanMultiplication(int &n);
	void __fastcall PreParseBooleanMultiplier(int &n);
	void __fastcall PreParseFieldExpression(int &n);
	void __fastcall PreParseFieldName(int &n);
	void __fastcall PreParseFieldOperation(int &n);
	void __fastcall PreParseFieldOperator(int &n);
	void __fastcall PreParseFieldValue(int &n);
	void __fastcall PreParseNumber(int &n);
	void __fastcall PreParseText(int &n);
	void __fastcall PreParseBoolean(int &n);
	void __fastcall ParseBooleanExpression(int &n);
	void __fastcall ParseBooleanSum(int &n);
	void __fastcall ParseBooleanMultiplication(int &n);
	void __fastcall ParseBooleanMultiplier(int &n);
	void __fastcall ParseFieldExpression(int &n);
	bool __fastcall CheckBooleanExpression(int &n);
	bool __fastcall CheckBooleanSum(int &n);
	bool __fastcall CheckBooleanMultiplication(int &n);
	bool __fastcall CheckBooleanMultiplier(int &n);
	bool __fastcall CheckFieldExpression(int &n);
	void __fastcall IncBitsArrNo(void);
	DynamicArray<TSearchOperation >  opArr;
	int opCount;
	int opNo;
	Db::TFilterOptions FilterOptions;
	__fastcall TSearchParser(Db::TDataSet* ds1);
	__fastcall virtual ~TSearchParser(void);
	void __fastcall PreParse(AnsiString Filter);
	void __fastcall Parse(void);
	bool __fastcall IsRecordMatches(char * recordBuf);
};


#pragma pack(push, 1)
struct TaaBLOBHeader
{
	int numParts;
	int position;
	int size;
	int trueSize;
	System::SmallString<15>  crc32;
} ;
#pragma pack(pop)

#pragma pack(push, 1)
struct TaaBLOBPart
{
	int blockNumber;
	int blockCount;
} ;
#pragma pack(pop)

typedef DynamicArray<TaaBLOBPart >  TaaBlobParts;

#pragma option push -b-
enum TaaRecordOperation { roMove, roBLOBWrite };
#pragma option pop

typedef DynamicArray<int >  ETblEngine__6;

class DELPHICLASS TaaIntArray;
class PASCALIMPLEMENTATION TaaIntArray : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	DynamicArray<int >  Items;
	int ItemCount;
	int AllocBy;
	int deAllocBy;
	int MaxAllocBy;
	int AllocItemCount;
	__fastcall TaaIntArray(int size, int DefaultAllocBy, int MaximumAllocBy);
	__fastcall virtual ~TaaIntArray(void);
	void __fastcall SetSize(int newSize);
	void __fastcall Assign(TaaIntArray* v);
	void __fastcall Append(int value);
	void __fastcall Insert(int ItemNo, int value);
	void __fastcall Delete(int ItemNo);
	void __fastcall MoveTo(int itemNo, int newItemNo);
	void __fastcall CopyTo(int * ar, const int ar_Size, int itemNo, int iCount);
	bool __fastcall IsValueExists(int value);
};


typedef DynamicArray<int >  ETblEngine__8;

typedef DynamicArray<int >  ETblEngine__9;

class DELPHICLASS TaaSortedIntArray;
class PASCALIMPLEMENTATION TaaSortedIntArray : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	DynamicArray<int >  KeyItems;
	DynamicArray<int >  ValueItems;
	int ItemCount;
	int AllocBy;
	int deAllocBy;
	int MaxAllocBy;
	int AllocItemCount;
	int __fastcall FindPositionForInsert(int key);
	int __fastcall FindPosition(int key);
	void __fastcall InsertByPosition(int ItemNo, int key, int value);
	void __fastcall DeleteByPosition(int ItemNo);
	
public:
	__fastcall TaaSortedIntArray(int size);
	__fastcall virtual ~TaaSortedIntArray(void);
	void __fastcall SetSize(int newSize);
	int __fastcall Find(int key);
	void __fastcall Insert(int key, int value);
	void __fastcall Delete(int key);
};


typedef DynamicArray<TaaBLOBPart >  ETblEngine__11;

class DELPHICLASS TaaBLOBPartsArray;
class PASCALIMPLEMENTATION TaaBLOBPartsArray : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	DynamicArray<TaaBLOBPart >  Items;
	int ItemCount;
	int AllocBy;
	int deAllocBy;
	int MaxAllocBy;
	int AllocItemCount;
	__fastcall TaaBLOBPartsArray(int size);
	__fastcall virtual ~TaaBLOBPartsArray(void);
	void __fastcall SetSize(int newSize);
	void __fastcall Insert(int ItemNo, const TaaBLOBPart &value);
	void __fastcall Append(const TaaBLOBPart &value);
	void __fastcall Delete(int ItemNo);
	void __fastcall AppendFrom(const TaaBLOBPart * src, const int src_Size, int qty);
};


typedef DynamicArray<TaaBLOBHeader >  ETblEngine__31;

typedef DynamicArray<TaaBLOBPart >  ETblEngine__41;

typedef DynamicArray<DynamicArray<TaaBLOBPart > >  ETblEngine__51;

class DELPHICLASS TaaBLOBHeadersArray;
class PASCALIMPLEMENTATION TaaBLOBHeadersArray : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	DynamicArray<TaaBLOBHeader >  Headers;
	DynamicArray<DynamicArray<TaaBLOBPart > >  Parts;
	int ItemCount;
	int AllocBy;
	int deAllocBy;
	int MaxAllocBy;
	int AllocItemCount;
	int LastBlockNumber;
	__fastcall TaaBLOBHeadersArray(int size);
	__fastcall virtual ~TaaBLOBHeadersArray(void);
	void __fastcall SetSize(int newSize);
	void __fastcall Delete(int itemNo, int qty = 0x1);
	void __fastcall ClearParts(int itemNo);
};


class DELPHICLASS TRecordsPage;
class PASCALIMPLEMENTATION TRecordsPage : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	int FMaxRecordCount;
	char *pData;
	void *DMHandle;
	void __fastcall SetMaxRecordCount(int value);
	void __fastcall SetAccessVariables(void);
	
public:
	int RecordSize;
	int FirstRecordNo;
	int RecordCount;
	int PageNo;
	int UseCount;
	int LastUseTime;
	int LockCount;
	__fastcall TRecordsPage(int NewMaxRecordCount, void * NewDMHandle);
	__fastcall virtual ~TRecordsPage(void);
	bool __fastcall RecordExists(int RecordNo);
	char * __fastcall GetRecordPtr(int RecordNo);
	char * __fastcall AppendRecord(char * pRecordBuffer);
	void __fastcall CopyRecords(int StartRecNo, char * pDestBuffer, int Count = 0x1);
	void __fastcall DeleteLastRecord(void);
	void __fastcall Read(int NewPageNo);
	void __fastcall ReadRecords(int StartRecNo, int RecCount);
	void __fastcall DeleteRecords(int StartRecNo);
	void __fastcall Init(int NewPageNo);
	
__published:
	__property int MaxRecordCount = {read=FMaxRecordCount, write=SetMaxRecordCount, default=0};
};


typedef DynamicArray<TRecordsPage* >  ETblEngine__81;

class DELPHICLASS TaaRecordsArray;
class PASCALIMPLEMENTATION TaaRecordsArray : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	void *DMHandle;
	DynamicArray<TRecordsPage* >  RecordPage;
	TaaSortedIntArray* RecordPageNoArr;
	int PageCount;
	int PageRecordCount;
	int EndPageIndex;
	bool bLargePagesMode;
	bool bAllPagesAllocated;
	void __fastcall CheckResetPages(void);
	void __fastcall ResetPages(void);
	int __fastcall GetPageIndex(int PageNo);
	int __fastcall GetPageToUse(int NewPageNo);
	void __fastcall CheckEndPageLoaded(void);
	int __fastcall GetPageNoByRecNo(int RecordNo);
	
public:
	bool FastOpen;
	__fastcall TaaRecordsArray(void * pDataManager, bool FastOpenValue);
	__fastcall virtual ~TaaRecordsArray(void);
	char * __fastcall Append(char * pRecordData = (void *)(0x0));
	void __fastcall Delete(int recordNo);
	char * __fastcall GetRecordDataPtr(int RecordNo);
	void __fastcall LockRecordPage(int recordNo);
	void __fastcall UnlockRecordPage(int recordNo);
};


#pragma pack(push, 4)
struct TaaBufferLogRecord
{
	unsigned curTime;
	int physRecNo;
	TaaRecordOperation operation;
	int dataIndex;
	TaaBLOBPartsArray* blobParts;
} ;
#pragma pack(pop)

typedef DynamicArray<void * >  ETblEngine__02;

typedef DynamicArray<int >  ETblEngine__12;

class DELPHICLASS TaaBuffersArray;
class PASCALIMPLEMENTATION TaaBuffersArray : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	DynamicArray<void * >  Items;
	DynamicArray<int >  Sizes;
	int overallSize;
	int ItemCount;
	int AllocBy;
	int deAllocBy;
	int MaxAllocBy;
	int AllocItemCount;
	__fastcall TaaBuffersArray(int size);
	__fastcall virtual ~TaaBuffersArray(void);
	void __fastcall SetSize(int newSize);
	void __fastcall Append(void * buffer, int size, bool copyFlag = false);
};


typedef DynamicArray<TaaBufferLogRecord >  ETblEngine__32;

class DELPHICLASS TaaBufferLogArray;
class PASCALIMPLEMENTATION TaaBufferLogArray : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	DynamicArray<TaaBufferLogRecord >  Items;
	TaaBuffersArray* blobData;
	int MaxItems;
	int MaxMemAlloc;
	unsigned MaxTime;
	Etblfilemanage::TAbstractFile* dataFile;
	Etblfilemanage::TAbstractFile* blobFile;
	int blobBlockSize;
	int dataOffset;
	int ItemCount;
	int AllocBy;
	int deAllocBy;
	int MaxAllocBy;
	int AllocItemCount;
	__fastcall TaaBufferLogArray(Etblfilemanage::TAbstractFile* dFile, Etblfilemanage::TAbstractFile* bFile, int blockSize, int offset, int size);
	__fastcall virtual ~TaaBufferLogArray(void);
	void __fastcall SetSize(int newSize);
	void __fastcall Append(TaaRecordOperation oper, char * recPtr, int recSize = 0xffffffff, int recPos = 0xffffffff, bool moveFlag = true, void * blobParts = (void *)(0x0), int numBlobParts = 0x0);
	void __fastcall FlushBuffers(void);
	bool __fastcall CheckOverflow(void);
	bool __fastcall IsRecordInBuffer(int recordNo, char * &pRecBuf);
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE System::ShortString SearchOperators[10];
static const Shortint DefaultRecordPages = 0x32;
static const Word DefaultRecordsPerPage = 0x3e8;

}	/* namespace Etblengine */
using namespace Etblengine;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ETblEngine
