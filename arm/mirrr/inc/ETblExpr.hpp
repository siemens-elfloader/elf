// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ETblExpr.pas' rev: 6.00

#ifndef ETblExprHPP
#define ETblExprHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ETblStrFunc.hpp>	// Pascal unit
#include <ETblRelationalAlgebra.hpp>	// Pascal unit
#include <ETblExcept.hpp>	// Pascal unit
#include <ETblConst.hpp>	// Pascal unit
#include <ETblLexer.hpp>	// Pascal unit
#include <ETblCommon.hpp>	// Pascal unit
#include <DB.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Etblexpr
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TETblExprNodeKind { enkField, enkConst, enkOperator, enkSet, enkNull };
#pragma option pop

#pragma option push -b-
enum TSign { sgnUndefined, sgnPlus, sgnMinus };
#pragma option pop

class DELPHICLASS TETblExprNode;
class PASCALIMPLEMENTATION TETblExprNode : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	Classes::TList* Children;
	Etblcommon::TETblDataOperator Operator;
	Etblcommon::TETblDataValue Data;
	char TestIndentString;
	__fastcall TETblExprNode(void)/* overload */;
	__fastcall TETblExprNode(Etblcommon::TETblDataOperator Op)/* overload */;
	__fastcall TETblExprNode(Etblcommon::TETblDataOperator Op, TETblExprNode* Node)/* overload */;
	__fastcall TETblExprNode(Etblcommon::TETblDataOperator Op, TETblExprNode* Node1, TETblExprNode* Node2)/* overload */;
	__fastcall TETblExprNode(Etblcommon::TETblDataOperator Op, TETblExprNode* Node1, TETblExprNode* Node2, TETblExprNode* Node3)/* overload */;
	__fastcall virtual ~TETblExprNode(void);
	virtual bool __fastcall CanBeAssigned(Etblrelationalalgebra::TEasyAO* AO);
	virtual AnsiString __fastcall GetFilter(Etblrelationalalgebra::TEasyAO* AO);
	virtual bool __fastcall IsJoinCondition(Etblrelationalalgebra::TEasyAO* AO1, Etblrelationalalgebra::TEasyAO* AO2);
	virtual void __fastcall ReplacePseudonyms(const Etblrelationalalgebra::TETblSelectListItem * SelectList, const int SelectList_Size);
	virtual void __fastcall AssignAO(Etblrelationalalgebra::TEasyAO* AO);
	virtual Etblcommon::TETblDataValue __fastcall GetDataValue(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0)) = 0 ;
	virtual void __fastcall Init(void);
	virtual void __fastcall Accumulate(void);
	virtual int __fastcall GetDataSize(void);
	virtual Db::TFieldType __fastcall GetDataType(void);
	virtual bool __fastcall isAggregated(void);
	virtual bool __fastcall isConstant(void);
	virtual AnsiString __fastcall TestTree(int Indent);
};


class DELPHICLASS TEasyParser;
class PASCALIMPLEMENTATION TEasyParser : public System::TObject 
{
	typedef System::TObject inherited;
	
protected:
	Etbllexer::TEasyLexer* FLex;
	Etbllexer::TToken Token;
	
public:
	bool __fastcall GetCurrentToken(void);
	bool __fastcall GetNextToken(void)/* overload */;
	bool __fastcall GetNextToken(Etbllexer::TTokenTypes PermittedTypes, int NativeErrorCode = 0xffffffff, bool RaiseExceptions = true)/* overload */;
	bool __fastcall GetNextSpecifiedToken(Etbllexer::TTokenTypes PermittedTypes, int NativeErrorCode = 0xffffffff, bool RaiseExceptions = true);
	virtual void __fastcall Parse(void) = 0 ;
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TEasyParser(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TEasyParser(void) { }
	#pragma option pop
	
};


class DELPHICLASS TETblExprNodeConst;
class PASCALIMPLEMENTATION TETblExprNodeConst : public TETblExprNode 
{
	typedef TETblExprNode inherited;
	
public:
	__fastcall TETblExprNodeConst(const Etblcommon::TETblDataValue &Value)/* overload */;
	virtual bool __fastcall CanBeAssigned(Etblrelationalalgebra::TEasyAO* AO);
	virtual AnsiString __fastcall GetFilter(Etblrelationalalgebra::TEasyAO* AO);
	virtual Etblcommon::TETblDataValue __fastcall GetDataValue(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
	virtual Db::TFieldType __fastcall GetDataType(void);
	virtual int __fastcall GetDataSize(void);
	virtual AnsiString __fastcall TestTree(int Indent);
public:
	#pragma option push -w-inl
	/* TETblExprNode.Destroy */ inline __fastcall virtual ~TETblExprNodeConst(void) { }
	#pragma option pop
	
};


class DELPHICLASS TETblExprNodeField;
class PASCALIMPLEMENTATION TETblExprNodeField : public TETblExprNode 
{
	typedef TETblExprNode inherited;
	
protected:
	Etblrelationalalgebra::TEasyAO* FAO;
	int FieldNumber;
	AnsiString FieldName;
	AnsiString TableName;
	
public:
	__fastcall TETblExprNodeField(AnsiString FieldName1, AnsiString TableName1)/* overload */;
	virtual bool __fastcall CanBeAssigned(Etblrelationalalgebra::TEasyAO* AO);
	virtual AnsiString __fastcall GetFilter(Etblrelationalalgebra::TEasyAO* AO);
	void __fastcall FillItem(Etblrelationalalgebra::TETblSelectListItem &Item);
	virtual void __fastcall ReplacePseudonyms(const Etblrelationalalgebra::TETblSelectListItem * SelectList, const int SelectList_Size);
	virtual bool __fastcall isConstant(void);
	virtual AnsiString __fastcall TestTree(int Indent);
	virtual void __fastcall AssignAO(Etblrelationalalgebra::TEasyAO* AO);
	virtual Etblcommon::TETblDataValue __fastcall GetDataValue(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
	virtual Db::TFieldType __fastcall GetDataType(void);
	virtual int __fastcall GetDataSize(void);
public:
	#pragma option push -w-inl
	/* TETblExprNode.Destroy */ inline __fastcall virtual ~TETblExprNodeField(void) { }
	#pragma option pop
	
};


class DELPHICLASS TETblExprNodeArithmetic;
class PASCALIMPLEMENTATION TETblExprNodeArithmetic : public TETblExprNode 
{
	typedef TETblExprNode inherited;
	
protected:
	void __fastcall SubData(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
	void __fastcall AddData(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
	void __fastcall MulData(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
	void __fastcall DivData(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
	
public:
	virtual AnsiString __fastcall GetFilter(Etblrelationalalgebra::TEasyAO* AO);
	virtual Etblcommon::TETblDataValue __fastcall GetDataValue(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
	virtual int __fastcall GetDataSize(void);
	virtual Db::TFieldType __fastcall GetDataType(void);
	virtual AnsiString __fastcall TestTree(int Indent);
public:
	#pragma option push -w-inl
	/* TETblExprNode.Create */ inline __fastcall TETblExprNodeArithmetic(void)/* overload */ : TETblExprNode() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TETblExprNode.Destroy */ inline __fastcall virtual ~TETblExprNodeArithmetic(void) { }
	#pragma option pop
	
};


class DELPHICLASS TETblExprNodeComparison;
class PASCALIMPLEMENTATION TETblExprNodeComparison : public TETblExprNode 
{
	typedef TETblExprNode inherited;
	
public:
	virtual bool __fastcall IsJoinCondition(Etblrelationalalgebra::TEasyAO* AO1, Etblrelationalalgebra::TEasyAO* AO2);
	virtual Etblcommon::TETblDataValue __fastcall GetDataValue(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
public:
	#pragma option push -w-inl
	/* TETblExprNode.Create */ inline __fastcall TETblExprNodeComparison(void)/* overload */ : TETblExprNode() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TETblExprNode.Destroy */ inline __fastcall virtual ~TETblExprNodeComparison(void) { }
	#pragma option pop
	
};


class DELPHICLASS TETblExprNodeBoolean;
class PASCALIMPLEMENTATION TETblExprNodeBoolean : public TETblExprNode 
{
	typedef TETblExprNode inherited;
	
private:
	void __fastcall Like(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
	void __fastcall bIn(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
	void __fastcall Between(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
	
public:
	virtual Etblcommon::TETblDataValue __fastcall GetDataValue(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
public:
	#pragma option push -w-inl
	/* TETblExprNode.Create */ inline __fastcall TETblExprNodeBoolean(void)/* overload */ : TETblExprNode() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TETblExprNode.Destroy */ inline __fastcall virtual ~TETblExprNodeBoolean(void) { }
	#pragma option pop
	
};


class DELPHICLASS TETblExprNodeCast;
class PASCALIMPLEMENTATION TETblExprNodeCast : public TETblExprNode 
{
	typedef TETblExprNode inherited;
	
private:
	Db::TFieldType CastType;
	
public:
	__fastcall TETblExprNodeCast(TETblExprNode* Node, Db::TFieldType CastType)/* overload */;
	virtual Db::TFieldType __fastcall GetDataType(void);
	virtual Etblcommon::TETblDataValue __fastcall GetDataValue(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
public:
	#pragma option push -w-inl
	/* TETblExprNode.Destroy */ inline __fastcall virtual ~TETblExprNodeCast(void) { }
	#pragma option pop
	
};


class DELPHICLASS TETblExprNodeAggregated;
class PASCALIMPLEMENTATION TETblExprNodeAggregated : public TETblExprNode 
{
	typedef TETblExprNode inherited;
	
private:
	int count;
	bool distinct;
	Etblcommon::TETblDataValue AvgSum;
	
public:
	__fastcall TETblExprNodeAggregated(Etblcommon::TETblDataOperator Op)/* overload */;
	__fastcall TETblExprNodeAggregated(Etblcommon::TETblDataOperator Op, bool distinct, TETblExprNode* Node)/* overload */;
	__fastcall virtual ~TETblExprNodeAggregated(void);
	virtual Etblcommon::TETblDataValue __fastcall GetDataValue(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
	virtual Db::TFieldType __fastcall GetDataType(void);
	virtual void __fastcall Init(void);
	virtual void __fastcall Accumulate(void);
	virtual bool __fastcall isAggregated(void);
	virtual AnsiString __fastcall TestTree(int Indent);
};


class DELPHICLASS TETblExprNodeStringFunction;
class PASCALIMPLEMENTATION TETblExprNodeStringFunction : public TETblExprNode 
{
	typedef TETblExprNode inherited;
	
protected:
	void __fastcall Concat(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
	void __fastcall Upper(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
	void __fastcall Lower(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
	void __fastcall Trim(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
	void __fastcall LTrim(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
	void __fastcall RTrim(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
	
public:
	virtual int __fastcall GetDataSize(void);
	virtual Etblcommon::TETblDataValue __fastcall GetDataValue(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
	virtual AnsiString __fastcall TestTree(int Indent);
public:
	#pragma option push -w-inl
	/* TETblExprNode.Create */ inline __fastcall TETblExprNodeStringFunction(void)/* overload */ : TETblExprNode() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TETblExprNode.Destroy */ inline __fastcall virtual ~TETblExprNodeStringFunction(void) { }
	#pragma option pop
	
};


class DELPHICLASS TETblExpression;
class PASCALIMPLEMENTATION TETblExpression : public TEasyParser 
{
	typedef TEasyParser inherited;
	
private:
	TETblExprNode* FRootNode;
	void __fastcall SaveState(int &SavedTokenNo);
	void __fastcall RestoreState(int SavedTokenNo);
	Etblcommon::TETblDataOperator __fastcall ParseCompOp(void);
	TETblExprNode* __fastcall ParseRowValueConstructorElement(void);
	TETblExprNode* __fastcall ParseRowValueConstructor(void);
	TETblExprNode* __fastcall ParseComparisonPredicate(void);
	TETblExprNode* __fastcall ParseLikePredicate(void);
	TETblExprNode* __fastcall ParseNullPredicate(void);
	TETblExprNode* __fastcall ParseBetweenPredicate(void);
	TETblExprNode* __fastcall ParseInPredicate(void);
	TETblExprNode* __fastcall ParsePredicate(void);
	TETblExprNode* __fastcall ParseBooleanPrimary(void);
	TETblExprNode* __fastcall ParseBooleanTest(void);
	TETblExprNode* __fastcall ParseBooleanFactor(void);
	TETblExprNode* __fastcall ParseBooleanTerm(void);
	TETblExprNode* __fastcall ParseSearchCondition(void);
	TETblExprNode* __fastcall ParseValueExpression(void);
	TETblExprNode* __fastcall ParseNumericValueExpression(void);
	TETblExprNode* __fastcall ParseTerm(void);
	TETblExprNode* __fastcall ParseFactor(void);
	TSign __fastcall ParseSign(void);
	TETblExprNode* __fastcall ParseNumericPrimary(void);
	TETblExprNode* __fastcall ParseValueExpressionPrimary(void);
	TETblExprNode* __fastcall ParseUnsignedValueSpecification(void);
	TETblExprNode* __fastcall ParseUnsignedLiteral(void);
	TETblExprNode* __fastcall ParseUnsignedNumericLiteral(void);
	TETblExprNode* __fastcall ParseColumnReference(void);
	TETblExprNode* __fastcall ParseSetFunctionSpecification(void);
	TETblExprNode* __fastcall ParseGeneralSetFunction(void);
	TETblExprNode* __fastcall ParseCastSpecification(void);
	TETblExprNode* __fastcall ParseCastOperand(void);
	TETblExprNode* __fastcall ParseStringValueExpression(void);
	TETblExprNode* __fastcall ParseCharacterValueExpression(void);
	TETblExprNode* __fastcall ParseConcatination(void);
	TETblExprNode* __fastcall ParseCharacterFactor(void);
	TETblExprNode* __fastcall ParseCharacterPrimary(void);
	TETblExprNode* __fastcall ParseGeneralLiteral(void);
	TETblExprNode* __fastcall ParseCharacterStringLiteral(void);
	TETblExprNode* __fastcall ParseStringValueFunction(void);
	TETblExprNode* __fastcall ParseCharacterValueFunction(void);
	
public:
	__fastcall TETblExpression(Etbllexer::TEasyLexer* Lexer)/* overload */;
	__fastcall TETblExpression(TETblExprNode* RootNode)/* overload */;
	__fastcall virtual ~TETblExpression(void);
	void __fastcall ParseSearchExpression(void);
	void __fastcall ParseValueExpr(void);
	virtual void __fastcall Parse(void);
	void __fastcall ApplyFilterParts(Etblrelationalalgebra::TEasyAO* AO);
	int __fastcall ExtractJoinConditions(Etblrelationalalgebra::TEasyAO* AO1, Etblrelationalalgebra::TEasyAO* AO2, Etblrelationalalgebra::TETblFields* FieldList1, Etblrelationalalgebra::TETblFields* FieldList2);
	AnsiString __fastcall GetFilter(Etblrelationalalgebra::TEasyAO* AO);
	void __fastcall ReplacePseudonyms(const Etblrelationalalgebra::TETblSelectListItem * SelectList, const int SelectList_Size);
	bool __fastcall IsEmpty(void);
	void __fastcall AssignAO(Etblrelationalalgebra::TEasyAO* AO);
	Etblcommon::TETblDataValue __fastcall GetDataValue(Db::TDataSet* DataSet = (Db::TDataSet*)(0x0));
	Db::TFieldType __fastcall GetDataType(Etblrelationalalgebra::TEasyAO* AO);
	int __fastcall GetDataSize(Etblrelationalalgebra::TEasyAO* AO);
	void __fastcall Init(void);
	void __fastcall Accumulate(void);
	AnsiString __fastcall TestTree();
	bool __fastcall IsAggregated(void);
	virtual bool __fastcall isConstant(void);
	bool __fastcall IsField(void);
	void __fastcall GetFieldInfo(AnsiString &TableName, AnsiString &FieldName);
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Etblexpr */
using namespace Etblexpr;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ETblExpr
