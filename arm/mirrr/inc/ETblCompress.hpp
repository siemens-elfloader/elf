// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ETblCompress.pas' rev: 6.00

#ifndef ETblCompressHPP
#define ETblCompressHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ETblZLIB.hpp>	// Pascal unit
#include <EasyTable.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Etblcompress
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern PACKAGE bool __fastcall aaCompressBuffer(char * inBuf, int inSize, /* out */ char * &outBuf, /* out */ int &outSize, Easytable::TCompressionLevel compressionLevel = (Easytable::TCompressionLevel)(0x1));
extern PACKAGE bool __fastcall aaDecompressBuffer(char * inBuf, int inSize, /* out */ char * &outBuf, /* out */ int &outSize, Easytable::TCompressionLevel compressionLevel = (Easytable::TCompressionLevel)(0x1));
extern PACKAGE unsigned __fastcall PPMCompressBuffer(char * inBuf, unsigned inSize, char * outBuf, int Max_Order = 0x6, int SASize = 0xa);
extern PACKAGE unsigned __fastcall PPMDecompressBuffer(char * inBuf, unsigned inSize, char * outBuf);

}	/* namespace Etblcompress */
using namespace Etblcompress;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ETblCompress
