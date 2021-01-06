// TViewGUI.h: interface for the TViewGUI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TVIEWGUI_H__4A0BE83B_D723_4CCE_A62E_A5BF38252EAE__INCLUDED_)
#define AFX_TVIEWGUI_H__4A0BE83B_D723_4CCE_A62E_A5BF38252EAE__INCLUDED_

#include "..\..\INC\swilib.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class TViewGUI  
{
public:
	int gui_id;
	int CreateTViewGUI(WSHDR *text, WSHDR *hdr_t);
	static void locret(void);
	static void GHook(void *data, int cmd);
	static int OnKey(void *data, GUI_MSG *msg);
	static TVIEW_DESC tview;
	TViewGUI();
	~TViewGUI();
};

#endif // !defined(AFX_TVIEWGUI_H__4A0BE83B_D723_4CCE_A62E_A5BF38252EAE__INCLUDED_)
