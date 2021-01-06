// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ETblFolderDialog.pas' rev: 6.00

#ifndef ETblFolderDialogHPP
#define ETblFolderDialogHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Registry.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <FileCtrl.hpp>	// Pascal unit
#include <ShlObj.hpp>	// Pascal unit
#include <ActiveX.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Etblfolderdialog
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TBrowseInfoFlags { OnlyComputers, OnlyPrinters, OnlyDomains, OnlyAncestors, OnlyFileSystem, ShowPath };
#pragma option pop

typedef Set<TBrowseInfoFlags, OnlyComputers, ShowPath>  TBrowseInfoFlagSet;

#pragma option push -b-
enum TSHFolders { foDesktop, foDesktopExpanded, foPrograms, foControlPanel, foPrinters, foPersonal, foFavorites, foStartup, foRecent, foSendto, foRecycleBin, foStartMenu, foDesktopFolder, foMyComputer, foNetwork, foNetworkNeighborhood, foFonts, foTemplates };
#pragma option pop

class DELPHICLASS TPBFolderDialog;
typedef void __fastcall (__closure *TBrowserInitializedEvent)(TPBFolderDialog* Sender, HWND DialogHandle);

typedef void __fastcall (__closure *TSelectionChangedEvent)(TPBFolderDialog* Sender, HWND DialogHandle, const Shlobj::PItemIDList ItemIDList, const AnsiString Folder);

class PASCALIMPLEMENTATION TPBFolderDialog : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	HWND FDialogHandle;
	HWND FNewFolderHandle;
	AnsiString FLabelCaption;
	HWND FParentHandle;
	AnsiString FDisplayName;
	int FImageIndex;
	AnsiString FFolder;
	AnsiString FSelectedFolder;
	TBrowseInfoFlagSet FFlags;
	TSHFolders FRootFolder;
	bool FNewFolderVisible;
	bool FNewFolderEnabled;
	AnsiString FNewFolderCaption;
	int FNewFolderWidth;
	bool FRestart;
	bool FValidPath;
	AnsiString FVersion;
	AnsiString FLocale;
	Classes::TStringList* FNewFolderCaptions;
	Classes::TStringList* FLabelCaptions;
	TBrowserInitializedEvent FOnInitialized;
	TSelectionChangedEvent FOnSelectionChanged;
	AnsiString __fastcall LocaleText(Classes::TStringList* List);
	AnsiString __fastcall MakeDisplayPath(AnsiString Path, int MaxL);
	void __fastcall Dummy(AnsiString Value);
	void __fastcall SetNewFolderCaption(AnsiString Value);
	void __fastcall SetNewFolderEnabled(bool Value);
	void __fastcall SetNewFolderVisible(bool Value);
	void __fastcall SetNewFolderWidth(int Value);
	void __fastcall SetNewFolderCaptions(Classes::TStringList* Value);
	void __fastcall SetSelectedFolder(AnsiString Value);
	void __fastcall SetFlags(TBrowseInfoFlagSet Value);
	void __fastcall SetLabelCaptions(Classes::TStringList* Value);
	void __fastcall LabelCaptionsChange(System::TObject* Sender);
	void __fastcall NewFolderCaptionsChange(System::TObject* Sender);
	
public:
	__fastcall virtual TPBFolderDialog(Classes::TComponent* AOwner);
	virtual void __fastcall Loaded(void);
	__fastcall virtual ~TPBFolderDialog(void);
	bool __fastcall Execute(void);
	void __fastcall SetSelectionPIDL(const HWND Hwnd, const Shlobj::PItemIDList ItemIDList);
	void __fastcall SetSelectionPath(const HWND Hwnd, const AnsiString Path);
	void __fastcall EnableOK(const HWND Hwnd, const bool Value);
	void __fastcall GetIDListFromPath(AnsiString Path, Shlobj::PItemIDList &ItemIDList);
	__property AnsiString DisplayName = {read=FDisplayName};
	__property int ImageIndex = {read=FImageIndex, nodefault};
	__property HWND ParentHandle = {read=FParentHandle, write=FParentHandle, nodefault};
	__property HWND DialogHandle = {read=FDialogHandle, write=FDialogHandle, nodefault};
	__property HWND NewFolderHandle = {read=FNewFolderHandle, write=FNewFolderHandle, nodefault};
	__property AnsiString SelectedFolder = {read=FSelectedFolder, write=SetSelectedFolder};
	
__published:
	__property AnsiString Folder = {read=FFolder, write=FFolder};
	__property TBrowseInfoFlagSet Flags = {read=FFlags, write=SetFlags, nodefault};
	__property TSHFolders RootFolder = {read=FRootFolder, write=FRootFolder, default=1};
	__property bool NewFolderVisible = {read=FNewFolderVisible, write=SetNewFolderVisible, nodefault};
	__property bool NewFolderEnabled = {read=FNewFolderEnabled, write=SetNewFolderEnabled, nodefault};
	__property int NewFolderWidth = {read=FNewFolderWidth, write=SetNewFolderWidth, default=75};
	__property TBrowserInitializedEvent OnInitialized = {read=FOnInitialized, write=FOnInitialized};
	__property TSelectionChangedEvent OnSelectionChanged = {read=FOnSelectionChanged, write=FOnSelectionChanged};
	__property Classes::TStringList* LabelCaptions = {read=FLabelCaptions, write=SetLabelCaptions};
	__property Classes::TStringList* NewFolderCaptions = {read=FNewFolderCaptions, write=SetNewFolderCaptions};
	__property AnsiString Version = {read=FVersion, write=Dummy, stored=false};
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Etblfolderdialog */
using namespace Etblfolderdialog;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ETblFolderDialog
