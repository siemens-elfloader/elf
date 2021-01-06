// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'ETblGauge.pas' rev: 6.00

#ifndef ETblGaugeHPP
#define ETblGaugeHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
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

namespace Etblgauge
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TTETGauge;
class PASCALIMPLEMENTATION TTETGauge : public Controls::TGraphicControl 
{
	typedef Controls::TGraphicControl inherited;
	
private:
	Graphics::TBitmap* Fbmp;
	Graphics::TColor Fbgcolor;
	Graphics::TColor Fscolor;
	Graphics::TColor Fecolor;
	int Fprogress;
	int Fmax;
	int Fmin;
	bool Fautocap;
	AnsiString Text;
	
protected:
	void __fastcall Setcolor1(Graphics::TColor Value);
	void __fastcall Setcolor2(Graphics::TColor Value);
	void __fastcall Setbgcolor(Graphics::TColor Value);
	void __fastcall Setmin(int Value);
	void __fastcall Setmax(int Value);
	void __fastcall Setprogress(int Value);
	HIDESBASE void __fastcall Settext(AnsiString Value);
	void __fastcall Setautocap(bool Value);
	void __fastcall Gradfill(Graphics::TColor Clr1, Graphics::TColor Clr2, Graphics::TBitmap* Thebitmap);
	virtual void __fastcall Paint(void);
	
public:
	__fastcall virtual TTETGauge(Classes::TComponent* Aowner);
	__fastcall virtual ~TTETGauge(void);
	void __fastcall inc(void);
	void __fastcall dec(void);
	
__published:
	__property Graphics::TColor Backcolor = {read=Fbgcolor, write=Setbgcolor, nodefault};
	__property Graphics::TColor Color1 = {read=Fscolor, write=Setcolor1, nodefault};
	__property Graphics::TColor Color2 = {read=Fecolor, write=Setcolor2, nodefault};
	__property int Min = {read=Fmin, write=Setmin, nodefault};
	__property int Max = {read=Fmax, write=Setmax, nodefault};
	__property int Progress = {read=Fprogress, write=Setprogress, nodefault};
	__property AnsiString Caption = {read=Text, write=Settext};
	__property bool Autocaption = {read=Fautocap, write=Setautocap, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint Arc1 = 0xa;

}	/* namespace Etblgauge */
using namespace Etblgauge;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// ETblGauge
