// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EtblPasswordDialog.pas' rev: 6.00

#ifndef EtblPasswordDialogHPP
#define EtblPasswordDialogHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Etblpassworddialog
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TPassDialog;
class PASCALIMPLEMENTATION TPassDialog : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TLabel* Label1;
	Stdctrls::TEdit* Pass;
	Stdctrls::TButton* cbOk;
	Stdctrls::TButton* cbCancel;
	Stdctrls::TLabel* lbName;
	void __fastcall cbOkClick(System::TObject* Sender);
	
public:
	System::TObject* FDataManager;
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TPassDialog(Classes::TComponent* AOwner) : Forms::TForm(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TPassDialog(Classes::TComponent* AOwner, int Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TPassDialog(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TPassDialog(HWND ParentWindow) : Forms::TForm(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TPassDialog* PassDialog;
extern PACKAGE bool __fastcall PasswordDialog(System::TObject* DataManager, AnsiString TableName = "");

}	/* namespace Etblpassworddialog */
using namespace Etblpassworddialog;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// EtblPasswordDialog
