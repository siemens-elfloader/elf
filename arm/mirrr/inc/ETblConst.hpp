// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ETblConst.pas' rev: 6.00

#ifndef ETblConstHPP
#define ETblConstHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <DB.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Etblconst
{
//-- type declarations -------------------------------------------------------
#pragma pack(push, 1)
struct TETFieldType
{
	Db::TFieldType fieldType;
	System::SmallString<20>  sqlName;
	System::SmallString<20>  name;
} ;
#pragma pack(pop)

typedef AnsiString ETblConst__1[143];

#pragma option push -b-
enum TReservedWord { rwABSOLUTE, rwACTION, rwADD, rwALL, rwALLOCATE, rwALTER, rwAND, rwANY, rwARE, rwAS, rwASC, rwASSERTION, rwAT, rwAUTHORIZATION, rwAVG, rwBEGIN, rwBETWEEN, rwBIT, rwBIT_LENGTH, rwBOTH, rwBY, rwCASCADE, rwCASCADED, rwCASE, rwCAST, rwCATALOG, rwCHAR, rwCHARACTER, rwCHAR_LENGTH, rwCHARACTER_LENGTH, rwCHECK, rwCLOSE, rwCOALESCE, rwCOLLATE, rwCOLLATION, rwCOLUMN, rwCOMMIT, rwCONNECT, rwCONNECTION, rwCONSTRAINT, rwCONSTRAINTS, rwCONTINUE, rwCONVERT, rwCORRESPONDING, rwCOUNT, rwCREATE, rwCROSS, rwCURRENT, rwCURRENT_DATE, rwCURRENT_TIME, rwCURRENT_TIMESTAMP, rwCURRENT_USER, rwCURSOR, rwDATE, rwDAY, rwDEALLOCATE, rwDEC, rwDECIMAL, rwDECLARE, rwDEFAULT, rwDEFERRABLE, rwDEFERRED, rwDELETE, rwDESC, rwDESCRIBE, rwDESCRIPTOR, rwDIAGNOSTICS, rwDISCONNECT, rwDISTINCT, rwDOMAIN, rwDOUBLE, rwDROP, rwELSE, rwEND, rwEND_EXEC, rwESCAPE, rwEXCEPT, rwEXCEPTION, rwEXEC, rwEXECUTE, rwEXISTS, rwEXTERNAL, rwEXTRACT, rwFALSE, rwFETCH, rwFIRST, rwFLOAT, rwFOR, rwFOREIGN, rwFOUND, rwFROM, rwFULL, rwGET, rwGLOBAL, rwGO
	, rwGOTO, rwGRANT, rwGROUP, rwHAVING, rwHOUR, rwIDENTITY, rwIMMEDIATE, rwIN, rwINDICATOR, rwINITIALLY, rwINNER, rwINPUT, rwINSENSITIVE, rwINSERT, rwINT, rwINTEGER, rwINTERSECT, rwINTERVAL, rwINTO, rwIS, rwISOLATION, rwJOIN, rwKEY, rwLANGUAGE, rwLAST, rwLEADING, rwLEFT, rwLEVEL, rwLIKE, rwLOCAL, rwLOWER, rwMATCH, rwMAX, rwMIN, rwMINUS, rwMINUTE, rwMODULE, rwMONTH, rwNAMES, rwNATIONAL, rwNATURAL, rwNCHAR, rwNEXT, rwNO, rwNOT, rwNULL, rwNULLIF, rwNUMERIC, rwOCTET_LENGTH, rwOF, rwON, rwONLY, rwOPEN, rwOPTION, rwOR, rwORDER, rwOUTER, rwOUTPUT, rwOVERLAPS, rwPAD, rwPARTIAL, rwPOSITION, rwPRECISION, rwPREPARE, rwPRESERVE, rwPRIMARY, rwPRIOR, rwPRIVILEGES, rwPROCEDURE, rwPUBLIC, rwREAD, rwREAL, rwREFERENCES, rwRELATIVE, rwRESTRICT, rwREVOKE, rwRIGHT, rwROLLBACK, rwROWS, rwSCHEMA, rwSCROLL, rwSECOND, rwSECTION, rwSELECT, rwSESSION, rwSESSION_USER, rwSET, rwSIZE, rwSMALLINT, rwSOME, rwSPACE, rwSQL, rwSQLCODE, rwSQLERROR, rwSQLSTATE, rwSUBSTRING, rwSUM, rwSYSTEM_USER, rwTABLE, rwTEMPORARY, rwTHEN, rwTIME, rwTIMESTAMP
	, rwTIMEZONE_HOUR, rwTIMEZONE_MINUTE, rwTO, rwTRAILING, rwTRANSACTION, rwTRANSLATE, rwTRANSLATION, rwTRIM, rwTRUE, rwUNION, rwUNIQUE, rwUNKNOWN, rwUPDATE, rwUPPER, rwUSAGE, rwUSER, rwUSING, rwVALUE, rwVALUES, rwVARCHAR, rwVARYING, rwVIEW, rwWHEN, rwWHENEVER, rwWHERE, rwWITH, rwWORK, rwWRITE, rwYEAR, rwZONE, rwPASSWORD, rwBLOB_COMPRESSION_LEVEL, rwBLOB_BLOCK_SIZE, rwLAST_AUTOINC_VALUE, rwMODIFY, rwNEW, rwINDEX, rwNOCASE, rwNone };
#pragma option pop

typedef AnsiString ETblConst__2[236];

//-- var, const, procedure ---------------------------------------------------
static const Shortint MAX_SUPPORTED_FIELD_TYPES = 0x13;
extern PACKAGE TETFieldType SUPPORTED_FIELD_TYPES[19];
static const Shortint ErUnknownError = 0x0;
static const Shortint ErMissingRightParenthesis = 0x1;
static const Shortint ErUnexpectedRightParenthesis = 0x2;
static const Shortint ErUnterminatedString = 0x3;
static const Shortint ErCannotOpenTable = 0x4;
static const Shortint ErCannotSetFilter = 0x5;
static const Shortint ErDifferentLength = 0x6;
static const Shortint ErTableIsNotOpened = 0x7;
static const Shortint ErRecordBufferIsNil = 0x8;
static const Shortint ErInvalidFieldNo = 0x9;
static const Shortint ErInvalidField = 0xa;
static const Shortint ErFieldHeaderIsNil = 0xb;
static const Shortint ErFieldNotFound = 0xc;
static const Shortint ErInvalidTableName = 0xd;
static const Shortint ErInvalidFieldLink = 0xe;
static const Shortint ErCannotReadHiddenField = 0xf;
static const Shortint ErCannotSetIndexDatasetNil = 0x10;
static const Shortint ErInvalidJoinField = 0x11;
static const Shortint ErArrayIsEmpty = 0x12;
static const Shortint ErFieldIsHidden = 0x13;
static const Shortint ErInvalidTypeCast = 0x14;
static const Shortint ErInvalidTypeCastName = 0x15;
static const Shortint ErBothJoinAOEqual = 0x16;
static const Shortint ErInvalidType = 0x17;
static const Shortint ErInvalidTypeName = 0x18;
static const Shortint ErEqualRecordsInJoins = 0x19;
static const Shortint ErDistinctIndexNotCreated = 0x1a;
static const Shortint ErInvalidUnionType = 0x1b;
static const Shortint ErInvalidFieldName = 0x1c;
static const Shortint ErInvalidNumericSymbol = 0x1d;
static const Shortint ErInvalidFilterExpressionType = 0x1e;
static const Shortint ErFieldDoesNotIncludedInGroupByList = 0x1f;
static const Shortint ErNonAggregateFunctionInGroupBySelectList = 0x20;
static const Shortint ErBlankSQLCommand = 0x47;
static const Shortint ErSQLCommandExpected = 0x48;
static const Shortint ErUnexpectedEndOfCommand = 0x49;
static const Shortint ErFieldNameExpected = 0x4a;
static const Shortint ErFieldPseudonymExpected = 0x4b;
static const Shortint ErTableNameExpected = 0x4c;
static const Shortint ErFromExpected = 0x4d;
static const Shortint ErFieldListExpected = 0x4e;
static const Shortint ErUnexpectedToken = 0x4f;
static const Shortint ErOtherTokenExpected = 0x50;
static const Shortint ErBooleanExpressionExpected = 0x51;
static const Shortint ErSortSpecificationExpected = 0x52;
static const Shortint ErColumnFromOrderByNotFound = 0x53;
static const Shortint ErCannotFindField = 0x54;
static const Shortint ErUnsupportedOperator = 0x55;
static const Shortint ErAmbiguousFieldReference = 0x56;
static const Shortint ErCircularDataLink = 0x57;
static const Shortint ErNodeIsNotField = 0x58;
static const Shortint ErCannotSetIndexWithField = 0x59;
static const Shortint ErNoCursorInQuery = 0x5a;
static const Shortint ErNotApplicableCondition = 0x5b;
static const Shortint ErExprValue = 0x5c;
static const Shortint ErNonInsertCommand = 0x65;
static const Shortint ErTableOrIndexKeywordExpected = 0x66;
static const Shortint ErLeftParenthesisExpected = 0x67;
static const Shortint ErFieldTypeExpected = 0x68;
static const Shortint ErUnknownFileldType = 0x69;
static const Shortint ErDecimalConstantExpected = 0x6a;
static const Shortint ErRightParenthesisExpected = 0x6b;
static const Shortint ErNullKeywordExpected = 0x6c;
static const Shortint ErErrorCreatingTable = 0x6d;
static const Shortint ErQuotedPasswordDataExpected = 0x6e;
static const Shortint ErRightParenthesisOrCommaExpected = 0x6f;
static const Shortint ErBlobCompressionLevelValueExpected = 0x70;
static const Shortint ErUnknownCompressLevel = 0x71;
static const Shortint ErDroppingTable = 0x72;
static const Shortint ErAddOrDropOrModifyKeywordExpected = 0x73;
static const Shortint ErNewDataTypeOrNotNullExpected = 0x74;
static const Shortint ErPasswordKeywordExpected = 0x75;
static const Shortint ErDroppingColumns = 0x76;
static const Shortint ErIndexKeywordExpected = 0x77;
static const Shortint ErIndexNameExpected = 0x78;
static const Shortint ErOnKeywordExpected = 0x79;
static const Shortint ErIntoKeywordExpected = 0x7a;
static const Shortint ErInsertFromTheTableToItSelf = 0x7b;
static const Shortint ErSetKeywordExpected = 0x7c;
static const Shortint ErEqualExpected = 0x7d;
static const Shortint ErNotnumericArgument = 0x7e;
static const Shortint ErCantConvertTypeFromTo = 0x7f;
static const Byte ErStringArgumentExpected = 0x80;
static const Byte ErNotStringArgument = 0x81;
static const Byte ErArgumentExpected = 0x82;
static const Byte ErNotIntegerDataType = 0x83;
static const Byte ErNotBooleanDataType = 0x84;
static const Byte ErNotAapplicableCastType = 0x85;
static const Byte ErTableAlreadyExists = 0x86;
static const Byte ETblMaxError = 0x8e;
extern PACKAGE AnsiString ETblErrorMessages[143];
static const Byte ETblMaxNativeError = 0xfb;
extern PACKAGE int ETblNativeToErrorCode[252][2];
static const Byte ETblMaxSQLReservedWords = 0xeb;
extern PACKAGE AnsiString ETblSQLReservedWords[236];

}	/* namespace Etblconst */
using namespace Etblconst;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ETblConst
