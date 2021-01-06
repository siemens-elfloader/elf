// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ETblStrFunc.pas' rev: 6.00

#ifndef ETblStrFuncHPP
#define ETblStrFuncHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Etblstrfunc
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
static const char WildCardMultipleChar = '\x25';
static const char WildCardSingleChar = '\x5f';
extern PACKAGE char ToUpperChars[256];
extern PACKAGE char ToLowerChars[256];
extern PACKAGE char ToOemChars[256];
extern PACKAGE char ToAnsiChars[256];
extern PACKAGE char TurkishToAnsiChars[256];
extern PACKAGE char TurkishToUpperChars[256];
extern PACKAGE char TurkishToLowerChars[256];
extern PACKAGE bool __fastcall IsStrMatchPattern(char * StrPtr, char * PatternPtr, bool bIgnoreCase);
extern PACKAGE bool __fastcall IsWideStrMatchPattern(wchar_t * StrPtr, wchar_t * PatternPtr, bool bIgnoreCase);
extern PACKAGE int __fastcall Q_PCompStr(char * P1, char * P2);
extern PACKAGE int __fastcall Q_CompStrL(const AnsiString S1, const AnsiString S2, unsigned MaxL);
extern PACKAGE int __fastcall Q_PCompText(char * P1, char * P2);
extern PACKAGE int __fastcall Q_CompTextL(const AnsiString S1, const AnsiString S2, unsigned MaxL);
extern PACKAGE char * __fastcall Q_PStrToAnsi(char * P);
extern PACKAGE char * __fastcall Q_PStrToOem(char * P);
extern PACKAGE int __fastcall Q_AnsiPCompStr(char * P1, char * P2);
extern PACKAGE int __fastcall Q_AnsiCompStrL(char * P1, char * P2, unsigned MaxL);
extern PACKAGE int __fastcall Q_AnsiPCompText(char * P1, char * P2);
extern PACKAGE int __fastcall Q_AnsiCompTextL(char * P1, char * P2, unsigned MaxL);

}	/* namespace Etblstrfunc */
using namespace Etblstrfunc;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ETblStrFunc
