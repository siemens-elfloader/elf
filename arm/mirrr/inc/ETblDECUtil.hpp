// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ETblDECUtil.pas' rev: 6.00

#ifndef ETblDECUtilHPP
#define ETblDECUtilHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Etbldecutil
{
//-- type declarations -------------------------------------------------------
typedef Byte *PByte;

typedef unsigned *PInteger;

typedef Word *PWord;

typedef unsigned TIntArray[1024];

typedef unsigned *PIntArray;

class DELPHICLASS EProtection;
class PASCALIMPLEMENTATION EProtection : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EProtection(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EProtection(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EProtection(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EProtection(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EProtection(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EProtection(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EProtection(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EProtection(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EProtection(void) { }
	#pragma option pop
	
};


class DELPHICLASS EStringFormat;
class PASCALIMPLEMENTATION EStringFormat : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EStringFormat(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EStringFormat(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EStringFormat(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EStringFormat(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EStringFormat(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EStringFormat(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EStringFormat(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EStringFormat(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EStringFormat(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TPAction { paEncode, paDecode, paScramble, paCalc, paWipe };
#pragma option pop

typedef Set<TPAction, paEncode, paWipe>  TPActions;

class DELPHICLASS TProtection;
class PASCALIMPLEMENTATION TProtection : public System::TInterfacedObject 
{
	typedef System::TInterfacedObject inherited;
	
private:
	TProtection* FProtection;
	TPActions FActions;
	TProtection* __fastcall GetProtection(void);
	void __fastcall SetProtection(TProtection* Value);
	
protected:
	virtual void __fastcall CodeInit(TPAction Action);
	virtual void __fastcall CodeDone(TPAction Action);
	virtual void __fastcall CodeBuf(void *Buffer, const int BufferSize, TPAction Action);
	
public:
	__fastcall TProtection(TProtection* AProtection);
	__fastcall virtual ~TProtection(void);
	/*         class method */ static Word __fastcall Identity(TMetaClass* vmt);
	int __fastcall Release(void);
	int __fastcall AddRef(void);
	virtual void __fastcall CodeStream(Classes::TStream* Source, Classes::TStream* Dest, int DataSize, TPAction Action);
	virtual void __fastcall CodeFile(const AnsiString Source, const AnsiString Dest, TPAction Action);
	virtual AnsiString __fastcall CodeString(const AnsiString Source, TPAction Action, int Format);
	virtual int __fastcall CodeBuffer(void *Buffer, int BufferSize, TPAction Action);
	__property TProtection* Protection = {read=GetProtection, write=SetProtection};
	__property TPActions Actions = {read=FActions, write=FActions, default=31};
};


typedef TMetaClass*TStringFormatClass;

class DELPHICLASS TStringFormat;
class PASCALIMPLEMENTATION TStringFormat : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	/* virtual class method */ virtual AnsiString __fastcall ToStr(TMetaClass* vmt, char * Value, int Len);
	/* virtual class method */ virtual AnsiString __fastcall StrTo(TMetaClass* vmt, char * Value, int Len);
	/* virtual class method */ virtual AnsiString __fastcall Name(TMetaClass* vmt);
	/* virtual class method */ virtual int __fastcall Format(TMetaClass* vmt);
	/* virtual class method */ virtual bool __fastcall IsValid(TMetaClass* vmt, char * Value, int Len, bool ToStr);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TStringFormat(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TStringFormat(void) { }
	#pragma option pop
	
};


class DELPHICLASS TStringFormat_HEX;
class PASCALIMPLEMENTATION TStringFormat_HEX : public TStringFormat 
{
	typedef TStringFormat inherited;
	
public:
	/* virtual class method */ virtual AnsiString __fastcall ToStr(TMetaClass* vmt, char * Value, int Len);
	/* virtual class method */ virtual AnsiString __fastcall StrTo(TMetaClass* vmt, char * Value, int Len);
	/* virtual class method */ virtual AnsiString __fastcall Name(TMetaClass* vmt);
	/* virtual class method */ virtual int __fastcall Format(TMetaClass* vmt);
	/* virtual class method */ virtual bool __fastcall IsValid(TMetaClass* vmt, char * Value, int Len, bool ToStr);
	/* virtual class method */ virtual char * __fastcall CharTable(TMetaClass* vmt);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TStringFormat_HEX(void) : TStringFormat() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TStringFormat_HEX(void) { }
	#pragma option pop
	
};


class DELPHICLASS TStringFormat_HEXL;
class PASCALIMPLEMENTATION TStringFormat_HEXL : public TStringFormat_HEX 
{
	typedef TStringFormat_HEX inherited;
	
public:
	/* virtual class method */ virtual AnsiString __fastcall Name(TMetaClass* vmt);
	/* virtual class method */ virtual int __fastcall Format(TMetaClass* vmt);
	/* virtual class method */ virtual char * __fastcall CharTable(TMetaClass* vmt);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TStringFormat_HEXL(void) : TStringFormat_HEX() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TStringFormat_HEXL(void) { }
	#pragma option pop
	
};


class DELPHICLASS TStringFormat_MIME64;
class PASCALIMPLEMENTATION TStringFormat_MIME64 : public TStringFormat_HEX 
{
	typedef TStringFormat_HEX inherited;
	
public:
	/* virtual class method */ virtual AnsiString __fastcall ToStr(TMetaClass* vmt, char * Value, int Len);
	/* virtual class method */ virtual AnsiString __fastcall StrTo(TMetaClass* vmt, char * Value, int Len);
	/* virtual class method */ virtual AnsiString __fastcall Name(TMetaClass* vmt);
	/* virtual class method */ virtual int __fastcall Format(TMetaClass* vmt);
	/* virtual class method */ virtual char * __fastcall CharTable(TMetaClass* vmt);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TStringFormat_MIME64(void) : TStringFormat_HEX() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TStringFormat_MIME64(void) { }
	#pragma option pop
	
};


class DELPHICLASS TStringFormat_UU;
class PASCALIMPLEMENTATION TStringFormat_UU : public TStringFormat 
{
	typedef TStringFormat inherited;
	
public:
	/* virtual class method */ virtual AnsiString __fastcall ToStr(TMetaClass* vmt, char * Value, int Len);
	/* virtual class method */ virtual AnsiString __fastcall StrTo(TMetaClass* vmt, char * Value, int Len);
	/* virtual class method */ virtual AnsiString __fastcall Name(TMetaClass* vmt);
	/* virtual class method */ virtual int __fastcall Format(TMetaClass* vmt);
	/* virtual class method */ virtual bool __fastcall IsValid(TMetaClass* vmt, char * Value, int Len, bool ToStr);
	/* virtual class method */ virtual char * __fastcall CharTable(TMetaClass* vmt);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TStringFormat_UU(void) : TStringFormat() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TStringFormat_UU(void) { }
	#pragma option pop
	
};


class DELPHICLASS TStringFormat_XX;
class PASCALIMPLEMENTATION TStringFormat_XX : public TStringFormat_UU 
{
	typedef TStringFormat_UU inherited;
	
public:
	/* virtual class method */ virtual AnsiString __fastcall Name(TMetaClass* vmt);
	/* virtual class method */ virtual int __fastcall Format(TMetaClass* vmt);
	/* virtual class method */ virtual char * __fastcall CharTable(TMetaClass* vmt);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TStringFormat_XX(void) : TStringFormat_UU() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TStringFormat_XX(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TProgressEvent)(System::TObject* Sender, int Current, int Maximal);

//-- var, const, procedure ---------------------------------------------------
static const Shortint fmtDEFAULT = 0xffffffff;
static const Shortint fmtNONE = 0x0;
static const Shortint fmtCOPY = 0x1;
static const Shortint fmtHEX = 0x10;
static const Word fmtHEXL = 0x3f8;
static const Word fmtMIME64 = 0x1064;
static const Word fmtUU = 0x5555;
static const Word fmtXX = 0x5858;
extern PACKAGE bool InitTestIsOk;
extern PACKAGE Word IdentityBase;
extern PACKAGE unsigned __fastcall (*SwapInteger)(unsigned Value);
extern PACKAGE void __fastcall (*SwapIntegerBuffer)(void * Source, void * Dest, int Count);
extern PACKAGE TProgressEvent Progress;
extern PACKAGE System::Comp __fastcall PerfCounter(void);
extern PACKAGE System::Comp __fastcall PerfFreq(void);
extern PACKAGE int __fastcall DefaultStringFormat(void);
extern PACKAGE void __fastcall SetDefaultStringFormat(int Format);
extern PACKAGE int __fastcall CPUType(void);
extern PACKAGE bool __fastcall IsObject(void * AObject, TMetaClass* AClass);
extern PACKAGE unsigned __fastcall ROL(unsigned Value, int Shift);
extern PACKAGE unsigned __fastcall ROLADD(unsigned Value, unsigned Add, int Shift);
extern PACKAGE unsigned __fastcall ROLSUB(unsigned Value, unsigned Sub, int Shift);
extern PACKAGE unsigned __fastcall ROR(unsigned Value, int Shift);
extern PACKAGE unsigned __fastcall RORADD(unsigned Value, unsigned Add, int Shift);
extern PACKAGE unsigned __fastcall RORSUB(unsigned Value, unsigned Sub, int Shift);
extern PACKAGE unsigned __fastcall SwapBits(unsigned Value);
extern PACKAGE int __fastcall LSBit(int Value);
extern PACKAGE int __fastcall MSBit(int Value);
extern PACKAGE int __fastcall OneBit(int Value);
extern PACKAGE int __fastcall MemCompare(void * P1, void * P2, int Size);
extern PACKAGE void __fastcall XORBuffers(void * I1, void * I2, int Size, void * Dest);
extern PACKAGE void __fastcall DoProgress(System::TObject* Sender, int Current, int Maximal);
extern PACKAGE TMetaClass* __fastcall StringFormat(int Format);
extern PACKAGE AnsiString __fastcall StrToFormat(char * Value, int Len, int Format);
extern PACKAGE AnsiString __fastcall FormatToStr(char * Value, int Len, int Format);
extern PACKAGE AnsiString __fastcall ConvertFormat(char * Value, int Len, int FromFormat, int ToFormat);
extern PACKAGE bool __fastcall IsValidFormat(char * Value, int Len, int Format);
extern PACKAGE bool __fastcall IsValidString(char * Value, int Len, int Format);
extern PACKAGE void __fastcall RegisterStringFormats(TMetaClass* * StringFormats, const int StringFormats_Size);
extern PACKAGE void __fastcall GetStringFormats(Classes::TStrings* Strings);
extern PACKAGE AnsiString __fastcall InsertCR(const AnsiString Value, int BlockSize);
extern PACKAGE AnsiString __fastcall DeleteCR(const AnsiString Value);
extern PACKAGE AnsiString __fastcall InsertBlocks(const AnsiString Value, const AnsiString BlockStart, const AnsiString BlockEnd, int BlockSize);
extern PACKAGE AnsiString __fastcall RemoveBlocks(const AnsiString Value, const AnsiString BlockStart, const AnsiString BlockEnd);
extern PACKAGE AnsiString __fastcall GetShortClassName(TMetaClass* Value);
extern PACKAGE int __fastcall RndXORBuffer(int Seed, void *Buffer, int Size);
extern PACKAGE int __fastcall RndTimeSeed(void);
extern PACKAGE Word __fastcall CRC16(Word CRC, void * Data, unsigned DataSize);
extern PACKAGE unsigned __fastcall CRC32(unsigned CRC, void * Data, unsigned DataSize);
extern PACKAGE char * __fastcall GetTestVector(void);

}	/* namespace Etbldecutil */
using namespace Etbldecutil;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ETblDECUtil
