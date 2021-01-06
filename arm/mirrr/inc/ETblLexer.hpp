// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ETblLexer.pas' rev: 6.00

#ifndef ETblLexerHPP
#define ETblLexerHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ETblExcept.hpp>	// Pascal unit
#include <ETblConst.hpp>	// Pascal unit
#include <DB.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Etbllexer
{
//-- type declarations -------------------------------------------------------
typedef AnsiString ETblLexer__1[12];

#pragma option push -b-
enum TTokenType { tktNone, tktString, tktQuotedString, tktBracketedString, tktInt, tktFloat, tktReservedWord, tktParam, tktLeftParenthesis, tktRightParenthesis, tktComma, tktDot };
#pragma option pop

typedef Set<TTokenType, tktNone, tktDot>  TTokenTypes;

#pragma pack(push, 4)
struct TToken
{
	TTokenType TokenType;
	Etblconst::TReservedWord ReservedWord;
	AnsiString Text;
	int LineNum;
	int ColumnNum;
} ;
#pragma pack(pop)

typedef TToken *PToken;

typedef DynamicArray<TToken >  ETblLexer__2;

#pragma pack(push, 4)
struct TSQLCommand
{
	DynamicArray<TToken >  Tokens;
	int NumTokens;
	int CurrentTokenNo;
} ;
#pragma pack(pop)

typedef DynamicArray<TSQLCommand >  ETblLexer__4;

class DELPHICLASS TEasyLexer;
class PASCALIMPLEMENTATION TEasyLexer : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	AnsiString FSQL;
	Db::TParams* FParams;
	void __fastcall Parse(void);
	
public:
	int NumCommands;
	DynamicArray<TSQLCommand >  Commands;
	int CurrentCommandNo;
	__fastcall TEasyLexer(AnsiString SQLScript, Db::TParams* Params);
	__fastcall virtual ~TEasyLexer(void);
	AnsiString __fastcall Test(bool bGenerate = true, bool bShowDetails = true);
	bool __fastcall GetNextCommand(void);
	bool __fastcall GetNextToken(TToken &Token);
	bool __fastcall GetCurrentToken(TToken &Token);
	bool __fastcall LookNextToken(TToken &Token);
	int __fastcall GetCurrentTokenNo(void);
	bool __fastcall SetCurrentTokenNo(int TokenNo, TToken &Token);
	bool __fastcall GetNextSpecifiedToken(TToken &Token, TTokenTypes TokenTypes);
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE AnsiString Lf;
extern PACKAGE AnsiString Cr;
extern PACKAGE AnsiString Crlf;
extern PACKAGE AnsiString Tab;
static const char Comment = '\x2d';
static const char Comment1 = '\x23';
static const char Dot = '\x2e';
static const char Comma = '\x2c';
static const char SemiColon = '\x3b';
static const char Asterisk = '\x2a';
static const char SingleQuote = '\x27';
static const char DoubleQuote = '\x22';
static const char Space = '\x20';
static const char LeftParenthesis = '\x28';
static const char RightParenthesis = '\x29';
static const char Percent = '\x25';
extern PACKAGE AnsiString ETblTokenType[12];
extern PACKAGE bool __fastcall IsReservedWord(const TToken &Token, Etblconst::TReservedWord ReservedWord = (Etblconst::TReservedWord)(0xec));

}	/* namespace Etbllexer */
using namespace Etbllexer;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ETblLexer
