// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ETblSQLCommand.pas' rev: 6.00

#ifndef ETblSQLCommandHPP
#define ETblSQLCommandHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ETblExpr.hpp>	// Pascal unit
#include <ETblRelationalAlgebra.hpp>	// Pascal unit
#include <ETblCommon.hpp>	// Pascal unit
#include <ETblLexer.hpp>	// Pascal unit
#include <ETblExcept.hpp>	// Pascal unit
#include <ETblConst.hpp>	// Pascal unit
#include <DB.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Etblsqlcommand
{
//-- type declarations -------------------------------------------------------
#pragma pack(push, 4)
struct TETblSortSpecification
{
	AnsiString TableName;
	AnsiString ColumnName;
	bool Descending;
} ;
#pragma pack(pop)

#pragma option push -b-
enum TETblTableType { ettTable, ettJoinedTable, ettSubQuery };
#pragma option pop

class DELPHICLASS TETblTableReference;
class PASCALIMPLEMENTATION TETblTableReference : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	TETblTableType TableType;
	AnsiString DatabaseName;
	AnsiString TableName;
	AnsiString Pseudonym;
	AnsiString Password;
	bool NaturalJoin;
	Etblcommon::TETblJoinType JoinType;
	TETblTableReference* LeftTable;
	TETblTableReference* RightTable;
	Classes::TStringList* UsingFields;
	Etblexpr::TETblExpression* SearchCondition;
	__fastcall TETblTableReference(void);
	__fastcall virtual ~TETblTableReference(void);
	void __fastcall MakeJoin(TETblTableReference* RightNode, Etblcommon::TETblJoinType JType, bool IsNatural, Classes::TStringList* Fields, Etblexpr::TETblExpression* OnCondition);
};


class DELPHICLASS TEasySQLCommand;
class PASCALIMPLEMENTATION TEasySQLCommand : public Etblexpr::TEasyParser 
{
	typedef Etblexpr::TEasyParser inherited;
	
protected:
	void __fastcall ParseColumnList(Classes::TStringList* &Fields);
	void __fastcall ParseFieldList(Etblrelationalalgebra::TETblFields* &Fields);
	
public:
	__fastcall TEasySQLCommand(Etbllexer::TEasyLexer* Lexer);
	virtual void __fastcall ExecSQL(Db::TDataSet* query, bool IsRoot = false);
	virtual Db::TDataSet* __fastcall GetResultDataset(void);
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TEasySQLCommand(void) { }
	#pragma option pop
	
};


class DELPHICLASS TEasySQLCursorCommand;
class PASCALIMPLEMENTATION TEasySQLCursorCommand : public TEasySQLCommand 
{
	typedef TEasySQLCommand inherited;
	
protected:
	Etblrelationalalgebra::TEasyAO* RootAO;
	Db::TDataSet* ResultDataset;
	
public:
	__fastcall TEasySQLCursorCommand(Etbllexer::TEasyLexer* Lexer);
	__fastcall virtual ~TEasySQLCursorCommand(void);
	virtual void __fastcall ExecSQL(Db::TDataSet* query, bool IsRoot = false);
	virtual Etblrelationalalgebra::TEasyAO* __fastcall BuildAOTree(Db::TDataSet* query);
	virtual Db::TDataSet* __fastcall GetResultDataset(void);
	Etblrelationalalgebra::TEasyAO* __fastcall GetResultAO(void);
};


typedef DynamicArray<Etblrelationalalgebra::TETblSelectListItem >  ETblSQLCommand__5;

typedef DynamicArray<TETblTableReference* >  ETblSQLCommand__6;

typedef DynamicArray<TETblSortSpecification >  ETblSQLCommand__7;

class DELPHICLASS TEasySQLSelect;
class PASCALIMPLEMENTATION TEasySQLSelect : public TEasySQLCursorCommand 
{
	typedef TEasySQLCursorCommand inherited;
	
protected:
	bool Distinct;
	bool AllFields;
	DynamicArray<Etblrelationalalgebra::TETblSelectListItem >  SelectList;
	int SelectListCount;
	AnsiString IntoDatabase;
	AnsiString IntoTable;
	DynamicArray<TETblTableReference* >  FromTables;
	int FromTablesCount;
	Etblexpr::TETblExpression* SearchCondition;
	Etblrelationalalgebra::TETblFields* GroupByFields;
	Etblexpr::TETblExpression* HavingCondition;
	DynamicArray<TETblSortSpecification >  OrderBySpecs;
	int OrderBySpecsCount;
	bool __fastcall ParseSelectToken(void);
	bool __fastcall ParseSetQuantifier(void);
	bool __fastcall ParseSelectSubList(void);
	bool __fastcall ParseSelectList(void);
	bool __fastcall ParseInto(void);
	bool __fastcall ParseJoinCondition(Etblexpr::TETblExpression* &SearchCondition);
	bool __fastcall ParseNamedColumnsJoin(Classes::TStringList* &Fields);
	bool __fastcall ParseJoin(TETblTableReference* &tblRef);
	bool __fastcall ParseTableReference(TETblTableReference* tblRef = (TETblTableReference*)(0x0));
	bool __fastcall ParseFromClause(void);
	bool __fastcall ParseWhereClause(void);
	bool __fastcall ParseGroupByClause(void);
	bool __fastcall ParseHavingClause(void);
	bool __fastcall ParseSortSpecification(void);
	bool __fastcall ParseOrderByClause(void);
	AnsiString __fastcall GetDefaultDatabaseName();
	Etblrelationalalgebra::TEasyAO* __fastcall CreateTableAO(TETblTableReference* &TableRef);
	Etblrelationalalgebra::TEasyAO* __fastcall CreateJoinedTableAO(TETblTableReference* &TableRef);
	Etblrelationalalgebra::TEasyAO* __fastcall CreateAO(TETblTableReference* &TableRef);
	Etblrelationalalgebra::TEasyAO* __fastcall BuildOneTableTree(void);
	Etblrelationalalgebra::TEasyAO* __fastcall BuildMultiTablesTree(void);
	void __fastcall ApplyOrderBy(Etblrelationalalgebra::TEasyAO* AO);
	
public:
	__fastcall TEasySQLSelect(Etbllexer::TEasyLexer* Lexer);
	__fastcall virtual ~TEasySQLSelect(void);
	virtual void __fastcall Parse(void);
	virtual void __fastcall ExecSQL(Db::TDataSet* query, bool IsRoot = false);
	virtual Etblrelationalalgebra::TEasyAO* __fastcall BuildAOTree(Db::TDataSet* query);
};


#pragma option push -b-
enum TETblQueryExprType { qetSelect, qetUnion, qetExcept, qetIntersect };
#pragma option pop

class DELPHICLASS TETblQueryExprNode;
class PASCALIMPLEMENTATION TETblQueryExprNode : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	TETblQueryExprType NodeType;
	TETblQueryExprNode* Left;
	TETblQueryExprNode* Right;
	bool All;
	bool Corresponding;
	Classes::TStringList* CorrespondingFields;
	TEasySQLSelect* SelectCommand;
	__fastcall TETblQueryExprNode(void)/* overload */;
	__fastcall TETblQueryExprNode(TETblQueryExprNode* Src)/* overload */;
	__fastcall virtual ~TETblQueryExprNode(void);
	void __fastcall AddNode(TETblQueryExprType NewType, TETblQueryExprNode* RightNode, bool bAll, bool bCorresponding, Classes::TStringList* ColumnList = (Classes::TStringList*)(0x0));
};


class DELPHICLASS TEasySQLUnion;
class PASCALIMPLEMENTATION TEasySQLUnion : public TEasySQLCursorCommand 
{
	typedef TEasySQLCursorCommand inherited;
	
protected:
	TETblQueryExprNode* FRootNode;
	bool __fastcall ParseAll(void);
	bool __fastcall ParseCorrespondingSpec(Classes::TStringList* &ColumnsList);
	TETblQueryExprNode* __fastcall ParseQuerySpecification(void);
	TETblQueryExprNode* __fastcall ParseSimpleTable(void);
	TETblQueryExprNode* __fastcall ParseNonJoinQueryPrimary(void);
	TETblQueryExprNode* __fastcall ParseNonJoinQueryTerm(void);
	TETblQueryExprNode* __fastcall ParseNonJoinQueryExpression(void);
	TETblQueryExprNode* __fastcall ParseQueryExpression(void);
	Etblrelationalalgebra::TEasyAO* __fastcall BuildAO(TETblQueryExprNode* Node);
	
public:
	__fastcall TEasySQLUnion(Etbllexer::TEasyLexer* Lexer);
	__fastcall virtual ~TEasySQLUnion(void);
	virtual void __fastcall Parse(void);
	virtual Etblrelationalalgebra::TEasyAO* __fastcall BuildAOTree(Db::TDataSet* query);
};


class DELPHICLASS TEasySQLInsert;
class PASCALIMPLEMENTATION TEasySQLInsert : public TEasySQLCommand 
{
	typedef TEasySQLCommand inherited;
	
protected:
	AnsiString TableName;
	AnsiString Password;
	Classes::TStringList* FieldNames;
	Classes::TStringList* FieldValues;
	TEasySQLSelect* InternalSelecter;
	void __fastcall ParseList(Classes::TStringList* list);
	void __fastcall SetFieldValue(Db::TField* field, AnsiString value);
	
public:
	__fastcall TEasySQLInsert(Etbllexer::TEasyLexer* Lexer);
	__fastcall virtual ~TEasySQLInsert(void);
	virtual void __fastcall Parse(void);
	virtual void __fastcall ExecSQL(Db::TDataSet* query, bool IsRoot = false);
};


class DELPHICLASS TEasySQLUpdate;
class PASCALIMPLEMENTATION TEasySQLUpdate : public TEasySQLCommand 
{
	typedef TEasySQLCommand inherited;
	
protected:
	AnsiString TableName;
	AnsiString Password;
	Classes::TStringList* FieldNames;
	Classes::TStringList* FieldValues;
	TEasySQLSelect* InternalSelecter;
	void __fastcall SetFieldValue(Db::TField* field, AnsiString value);
	
public:
	__fastcall TEasySQLUpdate(Etbllexer::TEasyLexer* Lexer);
	__fastcall virtual ~TEasySQLUpdate(void);
	virtual void __fastcall Parse(void);
	virtual void __fastcall ExecSQL(Db::TDataSet* query, bool IsRoot = true);
};


class DELPHICLASS TEasySQLDelete;
class PASCALIMPLEMENTATION TEasySQLDelete : public TEasySQLCommand 
{
	typedef TEasySQLCommand inherited;
	
protected:
	TEasySQLSelect* InternalSelecter;
	AnsiString TableName;
	bool FullDelete;
	
public:
	__fastcall TEasySQLDelete(Etbllexer::TEasyLexer* Lexer);
	__fastcall virtual ~TEasySQLDelete(void);
	virtual void __fastcall Parse(void);
	virtual void __fastcall ExecSQL(Db::TDataSet* query, bool IsRoot = false);
};


#pragma option push -b-
enum TRequaredType { rtRequared, rtNotRequared, rtUndefined };
#pragma option pop

#pragma pack(push, 4)
struct TEasyFieldDef
{
	AnsiString FieldName;
	Db::TFieldType FieldType;
	int Length;
	TRequaredType Required;
} ;
#pragma pack(pop)

typedef DynamicArray<TEasyFieldDef >  ETblSQLCommand__41;

class DELPHICLASS TEasyDDLTableManipulation;
class PASCALIMPLEMENTATION TEasyDDLTableManipulation : public TEasySQLCommand 
{
	typedef TEasySQLCommand inherited;
	
protected:
	AnsiString Password;
	int BlobBlockSize;
	int BlobCompressionLevel;
	int LastAutoIncValue;
	AnsiString TableName;
	DynamicArray<TEasyFieldDef >  TETFieldDefs;
	Classes::TStringList* PrimaryKey;
	void __fastcall ParseTableElementList(void);
	void __fastcall ParseTableNameToken(void);
	void __fastcall FillColumnType(TEasyFieldDef &FieldDef);
	void __fastcall FillColumnRequared(TEasyFieldDef &FieldDef);
	void __fastcall ParsePassword(void);
	void __fastcall ParseBlobCompressionLevel(void);
	void __fastcall ParseBlobBlockSize(void);
	void __fastcall ParseLastAutoIncValue(void);
	bool __fastcall ParsePrimaryKey(void);
	Db::TDataSet* __fastcall CreateInternalEasyTable(Db::TDataSet* query);
	void __fastcall UpdateAutoInc(Db::TDataSet* tet);
	void __fastcall AddPrimaryKey(Db::TDataSet* tet);
	void __fastcall DeletePrimaryKey(Db::TDataSet* tet);
	
public:
	__fastcall TEasyDDLTableManipulation(Etbllexer::TEasyLexer* Lexer);
	__fastcall virtual ~TEasyDDLTableManipulation(void);
	virtual void __fastcall Parse(void);
	virtual void __fastcall ExecSQL(Db::TDataSet* query, bool IsRoot = true) = 0 ;
};


class DELPHICLASS TEasyDDLCreateTable;
class PASCALIMPLEMENTATION TEasyDDLCreateTable : public TEasyDDLTableManipulation 
{
	typedef TEasyDDLTableManipulation inherited;
	
protected:
	void __fastcall CreateTable(Db::TDataSet* query);
	
public:
	virtual void __fastcall Parse(void);
	virtual void __fastcall ExecSQL(Db::TDataSet* query, bool IsRoot = true);
public:
	#pragma option push -w-inl
	/* TEasyDDLTableManipulation.Create */ inline __fastcall TEasyDDLCreateTable(Etbllexer::TEasyLexer* Lexer) : TEasyDDLTableManipulation(Lexer) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TEasyDDLTableManipulation.Destroy */ inline __fastcall virtual ~TEasyDDLCreateTable(void) { }
	#pragma option pop
	
};


class DELPHICLASS TEasyDDLDropTable;
class PASCALIMPLEMENTATION TEasyDDLDropTable : public TEasyDDLTableManipulation 
{
	typedef TEasyDDLTableManipulation inherited;
	
protected:
	HIDESBASE void __fastcall ParseTableNameToken(void);
	void __fastcall DropTable(Db::TDataSet* query);
	
public:
	virtual void __fastcall Parse(void);
	virtual void __fastcall ExecSQL(Db::TDataSet* query, bool IsRoot = true);
public:
	#pragma option push -w-inl
	/* TEasyDDLTableManipulation.Create */ inline __fastcall TEasyDDLDropTable(Etbllexer::TEasyLexer* Lexer) : TEasyDDLTableManipulation(Lexer) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TEasyDDLTableManipulation.Destroy */ inline __fastcall virtual ~TEasyDDLDropTable(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TAlterType { atAdd, atDrop, atModify };
#pragma option pop

class DELPHICLASS TEasyDDLAlterTable;
class PASCALIMPLEMENTATION TEasyDDLAlterTable : public TEasyDDLTableManipulation 
{
	typedef TEasyDDLTableManipulation inherited;
	
protected:
	TAlterType AlterType;
	AnsiString NewPassword;
	bool NewEncrypted;
	void __fastcall ParseAlterTypeToken(void);
	void __fastcall ParseNewPasswordToken(void);
	void __fastcall DropColumn(Db::TDataSet* tet);
	void __fastcall AddColumn(Db::TDataSet* tet);
	void __fastcall Modify(Db::TDataSet* tet);
	
public:
	__fastcall TEasyDDLAlterTable(Etbllexer::TEasyLexer* Lexer);
	virtual void __fastcall Parse(void);
	virtual void __fastcall ExecSQL(Db::TDataSet* query, bool IsRoot = true);
public:
	#pragma option push -w-inl
	/* TEasyDDLTableManipulation.Destroy */ inline __fastcall virtual ~TEasyDDLAlterTable(void) { }
	#pragma option pop
	
};


#pragma pack(push, 4)
struct TEasyIndexField
{
	AnsiString FieldName;
	bool desc;
	bool nocase;
} ;
#pragma pack(pop)

typedef DynamicArray<TEasyIndexField >  ETblSQLCommand__91;

class DELPHICLASS TEasyDDLCreateIndex;
class PASCALIMPLEMENTATION TEasyDDLCreateIndex : public TEasySQLCommand 
{
	typedef TEasySQLCommand inherited;
	
protected:
	bool Unique;
	AnsiString IndexName;
	AnsiString TableName;
	AnsiString Password;
	DynamicArray<TEasyIndexField >  TETIndexFields;
	
public:
	__fastcall TEasyDDLCreateIndex(Etbllexer::TEasyLexer* Lexer);
	virtual void __fastcall Parse(void);
	virtual void __fastcall ExecSQL(Db::TDataSet* query, bool IsRoot = true);
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TEasyDDLCreateIndex(void) { }
	#pragma option pop
	
};


class DELPHICLASS TEasyDDLDropIndex;
class PASCALIMPLEMENTATION TEasyDDLDropIndex : public TEasySQLCommand 
{
	typedef TEasySQLCommand inherited;
	
protected:
	AnsiString TableName;
	AnsiString IndexName;
	AnsiString Password;
	
public:
	__fastcall TEasyDDLDropIndex(Etbllexer::TEasyLexer* Lexer);
	virtual void __fastcall Parse(void);
	virtual void __fastcall ExecSQL(Db::TDataSet* query, bool IsRoot = true);
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TEasyDDLDropIndex(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Etblsqlcommand */
using namespace Etblsqlcommand;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ETblSQLCommand
