// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ETblEdit.pas' rev: 6.00

#ifndef ETblEditHPP
#define ETblEditHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Variants.hpp>	// Pascal unit
#include <FMTBcd.hpp>	// Pascal unit
#include <DesignEditors.hpp>	// Pascal unit
#include <DesignIntf.hpp>	// Pascal unit
#include <ETblFolderDialog.hpp>	// Pascal unit
#include <ETblFldLinks.hpp>	// Pascal unit
#include <EasyTable.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <DB.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Etbledit
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TDirectoryProperty;
class PASCALIMPLEMENTATION TDirectoryProperty : public Designeditors::TStringProperty 
{
	typedef Designeditors::TStringProperty inherited;
	
public:
	virtual void __fastcall Edit(void);
	virtual Designintf::TPropertyAttributes __fastcall GetAttributes(void);
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TDirectoryProperty(const Designintf::_di_IDesigner ADesigner, int APropCount) : Designeditors::TStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TDirectoryProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TEasyTableFieldLinkProperty;
class PASCALIMPLEMENTATION TEasyTableFieldLinkProperty : public Etblfldlinks::TFieldLinkProperty 
{
	typedef Etblfldlinks::TFieldLinkProperty inherited;
	
private:
	Easytable::TEasyTable* FTable;
	
protected:
	virtual void __fastcall GetFieldNamesForIndex(Classes::TStrings* List);
	virtual bool __fastcall GetIndexBased(void);
	virtual Db::TIndexDefs* __fastcall GetIndexDefs(void);
	virtual AnsiString __fastcall GetIndexFieldNames();
	virtual AnsiString __fastcall GetIndexName();
	virtual AnsiString __fastcall GetMasterFields();
	virtual void __fastcall SetIndexFieldNames(const AnsiString Value);
	virtual void __fastcall SetIndexName(const AnsiString Value);
	virtual void __fastcall SetMasterFields(const AnsiString Value);
	
public:
	__property bool IndexBased = {read=GetIndexBased, nodefault};
	__property Db::TIndexDefs* IndexDefs = {read=GetIndexDefs};
	__property AnsiString IndexFieldNames = {read=GetIndexFieldNames, write=SetIndexFieldNames};
	__property AnsiString IndexName = {read=GetIndexName, write=SetIndexName};
	__property AnsiString MasterFields = {read=GetMasterFields, write=SetMasterFields};
	virtual void __fastcall Edit(void);
public:
	#pragma option push -w-inl
	/* TFieldLinkProperty.CreateWith */ inline __fastcall virtual TEasyTableFieldLinkProperty(Db::TDataSet* ADataSet) : Etblfldlinks::TFieldLinkProperty(ADataSet) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TEasyTableFieldLinkProperty(const Designintf::_di_IDesigner ADesigner, int APropCount) : Etblfldlinks::TFieldLinkProperty(ADesigner, APropCount) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TEasyTableFieldLinkProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TDBStringProperty;
class PASCALIMPLEMENTATION TDBStringProperty : public Designeditors::TStringProperty 
{
	typedef Designeditors::TStringProperty inherited;
	
public:
	virtual Designintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall GetValueList(Classes::TStrings* List);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TDBStringProperty(const Designintf::_di_IDesigner ADesigner, int APropCount) : Designeditors::TStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TDBStringProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TIndexFieldNamesProperty;
class PASCALIMPLEMENTATION TIndexFieldNamesProperty : public TDBStringProperty 
{
	typedef TDBStringProperty inherited;
	
public:
	virtual void __fastcall GetValueList(Classes::TStrings* List);
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TIndexFieldNamesProperty(const Designintf::_di_IDesigner ADesigner, int APropCount) : TDBStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TIndexFieldNamesProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TIndexNameProperty;
class PASCALIMPLEMENTATION TIndexNameProperty : public TDBStringProperty 
{
	typedef TDBStringProperty inherited;
	
public:
	virtual void __fastcall GetValueList(Classes::TStrings* List);
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TIndexNameProperty(const Designintf::_di_IDesigner ADesigner, int APropCount) : TDBStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TIndexNameProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TTableNameProperty;
class PASCALIMPLEMENTATION TTableNameProperty : public TDBStringProperty 
{
	typedef TDBStringProperty inherited;
	
public:
	virtual void __fastcall GetValueList(Classes::TStrings* List);
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TTableNameProperty(const Designintf::_di_IDesigner ADesigner, int APropCount) : TDBStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TTableNameProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TDatabaseNameProperty;
class PASCALIMPLEMENTATION TDatabaseNameProperty : public TDBStringProperty 
{
	typedef TDBStringProperty inherited;
	
public:
	virtual void __fastcall GetValueList(Classes::TStrings* List);
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TDatabaseNameProperty(const Designintf::_di_IDesigner ADesigner, int APropCount) : TDBStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TDatabaseNameProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TDatabaseFileNameProperty;
class PASCALIMPLEMENTATION TDatabaseFileNameProperty : public Designeditors::TStringProperty 
{
	typedef Designeditors::TStringProperty inherited;
	
public:
	virtual void __fastcall Edit(void);
	virtual Designintf::TPropertyAttributes __fastcall GetAttributes(void);
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TDatabaseFileNameProperty(const Designintf::_di_IDesigner ADesigner, int APropCount) : Designeditors::TStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TDatabaseFileNameProperty(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE Classes::TPersistent* __fastcall GetPropertyValue(Classes::TPersistent* Instance, const AnsiString PropName);

}	/* namespace Etbledit */
using namespace Etbledit;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ETblEdit
