// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ETblSQLProcessor.pas' rev: 6.00

#ifndef ETblSQLProcessorHPP
#define ETblSQLProcessorHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ETblRelationalAlgebra.hpp>	// Pascal unit
#include <ETblSQLCommand.hpp>	// Pascal unit
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

namespace Etblsqlprocessor
{
//-- type declarations -------------------------------------------------------
typedef DynamicArray<Etblsqlcommand::TEasySQLCommand* >  ETblSQLProcessor__2;

class DELPHICLASS TSQLScriptProcessor;
class PASCALIMPLEMENTATION TSQLScriptProcessor : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	Etbllexer::TEasyLexer* FLex;
	Db::TParams* FParams;
	DynamicArray<Etblsqlcommand::TEasySQLCommand* >  Queries;
	int QueryCount;
	void __fastcall Parse(void);
	void __fastcall AddSelectQuery(void);
	void __fastcall AddInsertQuery(void);
	void __fastcall AddUpdateQuery(void);
	void __fastcall AddDeleteQuery(void);
	void __fastcall AddCreateTableQuery(void);
	void __fastcall AddDropTableQuery(void);
	void __fastcall AddAlterTableQuery(void);
	void __fastcall AddCreateIndex(void);
	void __fastcall AddDropIndexQuery(void);
	
public:
	__fastcall TSQLScriptProcessor(AnsiString SQLScript, Db::TParams* Params);
	__fastcall virtual ~TSQLScriptProcessor(void);
	void __fastcall ExecSQL(Db::TDataSet* query);
	Db::TDataSet* __fastcall GetResultDataset(void);
	Etblrelationalalgebra::TEasyAO* __fastcall GetResultAO(void);
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Etblsqlprocessor */
using namespace Etblsqlprocessor;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ETblSQLProcessor
