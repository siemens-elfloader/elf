// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ETblCommon.pas' rev: 6.00

#ifndef ETblCommonHPP
#define ETblCommonHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ETblConst.hpp>	// Pascal unit
#include <Math.hpp>	// Pascal unit
#include <ETblStrFunc.hpp>	// Pascal unit
#include <ETblExcept.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <DB.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Etblcommon
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TETblCompareResult { ecrEqual, ecrGreater, ecrLower, ecrLeftNull, ecrRightNull, ecrBothNull };
#pragma option pop

#pragma option push -b-
enum TETblJoinType { ejtCross, ejtInner, ejtUnion, ejtLeftOuter, ejtRightOuter, ejtFullOuter };
#pragma option pop

#pragma option push -b-
enum TETblUnionType { eutUnion, eutIntersect, eutExcept };
#pragma option pop

typedef Byte *pByte;

typedef int *pInteger;

typedef short *pSmallint;

typedef __int64 *pLargeInt;

typedef Word *pWord;

typedef bool *pBoolean;

typedef double *pFloat;

typedef double *pCurrency;

typedef System::TDateTime *pDateTime;

#pragma option push -b-
enum TETblDataOperator { doUNDEFINED, doEQ, doNE, doGT, doLT, doGE, doLE, doNOT, doAND, doOR, doIN, doNOTIN, doBETWEEN, doNOTBETWEEN, doLIKE, doNOTLIKE, doISNULL, doISNOTNULL, doADD, doSUB, doMUL, doDIV, doPOSITION, doCONCAT, doUPPER, doLOWER, doTRIM, doLTRIM, doRTRIM, doLENGTH, doPOS, doSUBSTRING, doSUM, doAVG, doMIN, doMAX, doCOUNT, doCOUNTALL, doCAST };
#pragma option pop

#pragma pack(push, 4)
struct TETblDataValue
{
	Db::TFieldType DataType;
	int DataSize;
	bool IsNull;
	char *pData;
	bool IsDataLinked;
} ;
#pragma pack(pop)

typedef TETblDataValue *PETblDataValue;

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall InitDataValue(TETblDataValue &value);
extern PACKAGE void __fastcall FinalizeDataValue(TETblDataValue &value);
extern PACKAGE void __fastcall CopyDataValue(const TETblDataValue &SrcValue, TETblDataValue &DestValue);
extern PACKAGE void __fastcall SetDataValueAsInteger(TETblDataValue &DataValue, int IntValue);
extern PACKAGE int __fastcall GetDataValueAsInteger(TETblDataValue &DataValue);
extern PACKAGE void __fastcall SetDataValueAsFloat(TETblDataValue &DataValue, double FloatValue);
extern PACKAGE void __fastcall SetDataValueAsSmallInt(TETblDataValue &DataValue, short Value);
extern PACKAGE void __fastcall SetDataValueAsWord(TETblDataValue &DataValue, Word Value);
extern PACKAGE void __fastcall SetDataValueAsLargeInt(TETblDataValue &DataValue, __int64 Value)/* overload */;
extern PACKAGE void __fastcall SetDataValueAsBoolean(TETblDataValue &DataValue, bool Value)/* overload */;
extern PACKAGE bool __fastcall GetDataValueAsBoolean(const TETblDataValue &DataValue);
extern PACKAGE void __fastcall SetDataValueAsCurrency(TETblDataValue &DataValue, double Value);
extern PACKAGE void __fastcall SetDataValueAsDate(TETblDataValue &DataValue, System::TDateTime Value);
extern PACKAGE void __fastcall SetDataValueAsTime(TETblDataValue &DataValue, System::TDateTime Value);
extern PACKAGE void __fastcall SetDataValueAsDateTime(TETblDataValue &DataValue, System::TDateTime Value);
extern PACKAGE void __fastcall SetDataValueAsString(TETblDataValue &DataValue, AnsiString StrValue);
extern PACKAGE AnsiString __fastcall GetDataValueAsString(TETblDataValue &DataValue);
extern PACKAGE void __fastcall SetDataValueAsWideString(TETblDataValue &DataValue, const WideString Value);
extern PACKAGE WideString __fastcall GetDataValueAsWideString(TETblDataValue &DataValue);
extern PACKAGE AnsiString __fastcall GetTemporaryName(AnsiString BaseName = "");
extern PACKAGE TETblCompareResult __fastcall CompareDataValues(TETblDataValue &value1, TETblDataValue &value2, TETblJoinType JoinType = (TETblJoinType)(0x1), bool bIgnoreCase = false, bool bPartialCompare = false);
extern PACKAGE Db::TFieldType __fastcall getCommonDataType(Db::TFieldType a, Db::TFieldType b);
extern PACKAGE void __fastcall Cast(TETblDataValue &Value, Db::TFieldType FieldType);
extern PACKAGE void __fastcall AddDataValues(TETblDataValue &value1, const TETblDataValue &value2, bool IgnoreNULL = false);
extern PACKAGE void __fastcall NegativeDataValues(TETblDataValue &value);
extern PACKAGE void __fastcall MulDataValues(TETblDataValue &value1, const TETblDataValue &value2);
extern PACKAGE void __fastcall DivDataValues(TETblDataValue &value1, const TETblDataValue &value2);
extern PACKAGE AnsiString __fastcall GetDataTypeName(Db::TFieldType dt);
extern PACKAGE AnsiString __fastcall GetOperatorName(TETblDataOperator op);
extern PACKAGE bool __fastcall IsNumericDataType(Db::TFieldType dt);
extern PACKAGE Db::TFieldType __fastcall GetFieldType(const AnsiString TypeName);

}	/* namespace Etblcommon */
using namespace Etblcommon;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ETblCommon
