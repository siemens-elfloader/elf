// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ETblRelationalAlgebra.pas' rev: 6.00

#ifndef ETblRelationalAlgebraHPP
#define ETblRelationalAlgebraHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ETblEngine.hpp>	// Pascal unit
#include <ETblCommon.hpp>	// Pascal unit
#include <ETblExcept.hpp>	// Pascal unit
#include <ETblConst.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <DB.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Etblrelationalalgebra
{
//-- type declarations -------------------------------------------------------
#pragma pack(push, 4)
struct TETblFieldLink
{
	AnsiString FieldName;
	Db::TFieldType FieldType;
	int FieldSize;
	AnsiString DisplayName;
	void *AO;
	Db::TDataSet* Dataset;
	int FieldNo;
	bool IsHidden;
	bool IsExpression;
	bool IsAggregate;
	System::TObject* Expr;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TETblSelectListItem
{
	AnsiString TableName;
	bool AllFields;
	AnsiString FieldName;
	bool IsExpression;
	System::TObject* ValueExpr;
	AnsiString Pseudonym;
} ;
#pragma pack(pop)

typedef DynamicArray<TETblSelectListItem >  ETblRelationalAlgebra__2;

class DELPHICLASS TETblFields;
class PASCALIMPLEMENTATION TETblFields : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	DynamicArray<TETblSelectListItem >  Items;
	int ItemCount;
	__fastcall TETblFields(void);
	void __fastcall Append(TETblSelectListItem &Item);
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TETblFields(void) { }
	#pragma option pop
	
};


typedef DynamicArray<TETblFieldLink >  ETblRelationalAlgebra__4;

class DELPHICLASS TEasyAO;
class PASCALIMPLEMENTATION TEasyAO : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	bool FIsRootAO;
	bool FIsAOTable;
	bool FIsAOGroupBy;
	System::TObject* FFilterExpr;
	
protected:
	AnsiString FTableName;
	AnsiString FTableAlias;
	bool FIsMaterialized;
	bool FMaterializationComplete;
	Db::TDataSet* FResultDataset;
	Etblengine::TaaIntArray* FResultFieldsOrder;
	int FFieldCount;
	bool FLeftAONull;
	bool FRightAONull;
	AnsiString FIndexFieldNames;
	AnsiString FDescFields;
	AnsiString FCaseInsensitiveFields;
	AnsiString FDistinctFields;
	bool FExpressionsExists;
	DynamicArray<TETblFieldLink >  FFieldLinks;
	void __fastcall InternalCreate(TEasyAO* LeftAO = (TEasyAO*)(0x0), TEasyAO* RightAO = (TEasyAO*)(0x0), AnsiString TableName = "", AnsiString TableAlias = "");
	virtual void __fastcall InternalFirst(void);
	virtual void __fastcall InternalNext(void);
	virtual bool __fastcall InternalGetEof(void);
	virtual int __fastcall InternalGetRecordCount(void);
	virtual void __fastcall First(void);
	virtual void __fastcall Next(void);
	virtual bool __fastcall GetEof(void);
	virtual int __fastcall GetRecordCount(void);
	virtual void __fastcall SetFieldNames(void);
	virtual void __fastcall DoMaterialize(void);
	
public:
	TEasyAO* FLeftAO;
	TEasyAO* FRightAO;
	__fastcall virtual ~TEasyAO(void);
	virtual void __fastcall Execute(bool IsRootAO = false);
	void __fastcall FilterRecord(Db::TDataSet* DataSet, bool &Accept);
	virtual void __fastcall SetFilter(System::TObject* FilterExpr);
	virtual void __fastcall SetResultFields(TETblSelectListItem * FieldRefs, const int FieldRefs_Size, bool bDistinct);
	virtual int __fastcall FieldExists(AnsiString FieldName, AnsiString TableName, bool Unhide, Etblengine::TaaIntArray* FieldNumbers = (Etblengine::TaaIntArray*)(0x0));
	virtual AnsiString __fastcall GetFieldName(int FieldNo, bool bOriginal = true);
	virtual void __fastcall GetFieldValue(Etblcommon::TETblDataValue &value, int FieldNo, bool bCopy = false, bool AccessToHidden = false);
	int __fastcall GetFieldSize(AnsiString FieldName)/* overload */;
	int __fastcall GetFieldSize(int FieldNo)/* overload */;
	Db::TFieldType __fastcall GetFieldType(int FieldNo);
	virtual void __fastcall InternalSetIndex(void);
	virtual void __fastcall SetIndex(AnsiString IndexFieldNames, AnsiString DescFields, AnsiString CaseInsensitiveFields);
	__property bool IsMaterialized = {read=FIsMaterialized, nodefault};
	__property int FieldCount = {read=FFieldCount, nodefault};
	__property int RecordCount = {read=GetRecordCount, nodefault};
	__property Db::TDataSet* ResultDataset = {read=FResultDataset};
	__property bool Eof = {read=GetEof, nodefault};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TEasyAO(void) : System::TObject() { }
	#pragma option pop
	
};


class DELPHICLASS TEasyAOTable;
class PASCALIMPLEMENTATION TEasyAOTable : public TEasyAO 
{
	typedef TEasyAO inherited;
	
public:
	__fastcall TEasyAOTable(AnsiString TableName, AnsiString TableAlias, AnsiString DatabaseName, AnsiString DatabaseFileName, bool bInMemory, AnsiString Password);
	virtual void __fastcall SetResultFields(TETblSelectListItem * FieldRefs, const int FieldRefs_Size, bool bDistinct);
	__property IsMaterialized ;
	__property FieldCount ;
	__property RecordCount ;
	__property ResultDataset ;
	__property Eof ;
public:
	#pragma option push -w-inl
	/* TEasyAO.Destroy */ inline __fastcall virtual ~TEasyAOTable(void) { }
	#pragma option pop
	
};


class DELPHICLASS TEasyAOJoin;
class PASCALIMPLEMENTATION TEasyAOJoin : public TEasyAO 
{
	typedef TEasyAO inherited;
	
private:
	bool FDekart;
	bool FUnionJoin;
	bool FOuterJoin;
	bool FInnerJoin;
	Etblcommon::TETblJoinType FJoinType;
	Etblengine::TaaIntArray* FFields1;
	Etblengine::TaaIntArray* FFields2;
	Etblcommon::TETblCompareResult FCompareResult;
	int FRightRecNo;
	bool FEqualStarted;
	bool FFirstTimeCalled;
	bool FEof;
	
protected:
	void __fastcall CompareRecords(void);
	virtual void __fastcall InternalFirst(void);
	virtual void __fastcall InternalNext(void);
	virtual bool __fastcall InternalGetEof(void);
	virtual int __fastcall InternalGetRecordCount(void);
	
public:
	__fastcall TEasyAOJoin(TEasyAO* LeftChild, TEasyAO* RightChild, Etblcommon::TETblJoinType JoinType, bool IsNatural, TETblFields* FieldList1, TETblFields* FieldList2);
	__fastcall virtual ~TEasyAOJoin(void);
	__property IsMaterialized ;
	__property FieldCount ;
	__property RecordCount ;
	__property ResultDataset ;
	__property Eof ;
	__property bool OuterJoin = {read=FOuterJoin, nodefault};
};


class DELPHICLASS TEasyAOUnion;
class PASCALIMPLEMENTATION TEasyAOUnion : public TEasyAO 
{
	typedef TEasyAO inherited;
	
private:
	bool FEof;
	Etblcommon::TETblUnionType FUnionType;
	Etblengine::TaaIntArray* FFields1;
	Etblengine::TaaIntArray* FFields2;
	Etblcommon::TETblCompareResult FCompareResult;
	bool FFirstTimeCalled;
	bool FShowLeft;
	
protected:
	void __fastcall CompareRecords(void);
	void __fastcall ShowLeftAO(void);
	void __fastcall ShowRightAO(void);
	virtual void __fastcall InternalFirst(void);
	virtual void __fastcall InternalNext(void);
	virtual bool __fastcall InternalGetEof(void);
	virtual int __fastcall InternalGetRecordCount(void);
	
public:
	__fastcall TEasyAOUnion(TEasyAO* LeftChild, TEasyAO* RightChild, Etblcommon::TETblUnionType UnionType, bool IsCorresponding, bool bDistinct, TETblFields* FieldList);
	__fastcall virtual ~TEasyAOUnion(void);
	__property IsMaterialized ;
	__property FieldCount ;
	__property RecordCount ;
	__property ResultDataset ;
	__property Eof ;
};


class DELPHICLASS TEasyAOTableExpr;
class PASCALIMPLEMENTATION TEasyAOTableExpr : public TEasyAO 
{
	typedef TEasyAO inherited;
	
protected:
	virtual void __fastcall InternalFirst(void);
	virtual void __fastcall InternalNext(void);
	virtual bool __fastcall InternalGetEof(void);
	virtual int __fastcall InternalGetRecordCount(void);
	
public:
	__fastcall TEasyAOTableExpr(TEasyAO* Child);
	__property IsMaterialized ;
	__property FieldCount ;
	__property RecordCount ;
	__property ResultDataset ;
	__property Eof ;
public:
	#pragma option push -w-inl
	/* TEasyAO.Destroy */ inline __fastcall virtual ~TEasyAOTableExpr(void) { }
	#pragma option pop
	
};


class DELPHICLASS TEasyAOGroupBy;
class PASCALIMPLEMENTATION TEasyAOGroupBy : public TEasyAO 
{
	typedef TEasyAO inherited;
	
protected:
	Db::TDataSet* FTempDataset;
	bool FFirstTimeCalled;
	bool FAllFields;
	Etblengine::TaaIntArray* FFields;
	Etblcommon::TETblCompareResult FCompareResult;
	bool FGroupFinished;
	bool FEOF;
	void __fastcall CompareRecords(void);
	virtual void __fastcall InternalFirst(void);
	virtual void __fastcall InternalNext(void);
	virtual bool __fastcall InternalGetEof(void);
	virtual int __fastcall InternalGetRecordCount(void);
	
public:
	virtual void __fastcall SetResultFields(TETblSelectListItem * FieldRefs, const int FieldRefs_Size, bool bDistinct);
	__fastcall TEasyAOGroupBy(TEasyAO* Child, TETblFields* FieldList);
	__fastcall virtual ~TEasyAOGroupBy(void);
	__property IsMaterialized ;
	__property FieldCount ;
	__property RecordCount ;
	__property ResultDataset ;
	__property Eof ;
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Etblrelationalalgebra */
using namespace Etblrelationalalgebra;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ETblRelationalAlgebra
