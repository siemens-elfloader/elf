// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ESFSPassword.pas' rev: 6.00

#ifndef ESFSPasswordHPP
#define ESFSPasswordHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ETblCipher.hpp>	// Pascal unit
#include <ETblDECUtil.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Esfspassword
{
//-- type declarations -------------------------------------------------------
#pragma pack(push, 1)
struct TPasswordHeader
{
	char Key[32];
	char Pass[32];
	unsigned KeyCRC;
	unsigned PassCRC;
	char Question[100];
} ;
#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
static const Shortint MAX_PASSWORD_LENGTH = 0x20;
static const Shortint MAX_QUESTION_LENGTH = 0x64;
static const Shortint crcFast = 0x0;
static const Shortint crcFull = 0x1;
#define QUESTION_MASK "aFD:S.<@#Q$^562dg"
extern PACKAGE unsigned __fastcall CountCRC(char * buffer, int size, Byte mode);
extern PACKAGE bool __fastcall CheckCRC(char * buffer, int size, Byte mode, unsigned CRC);
extern PACKAGE void __fastcall CreatePasswordHeader(TPasswordHeader &PasswordHeader, AnsiString Password, AnsiString Question = "", AnsiString Answer = "");
extern PACKAGE bool __fastcall CheckPassword(const TPasswordHeader &PasswordHeader, AnsiString Password, AnsiString &Key);
extern PACKAGE bool __fastcall CheckAnswer(const TPasswordHeader &PasswordHeader, AnsiString Answer, AnsiString &Password);
extern PACKAGE AnsiString __fastcall DecryptQuestion(const TPasswordHeader &PasswordHeader);

}	/* namespace Esfspassword */
using namespace Esfspassword;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ESFSPassword
