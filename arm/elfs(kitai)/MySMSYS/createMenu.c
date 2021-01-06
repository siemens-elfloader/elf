#include "..\inc\swilib.h"


unsigned int CreateMLMenu(const ML_MENU_DESC *menu, const HEADER_DESC *hdr, int start_item, int n_items, void *user_pointer)
{
	void *ma=malloc_adr();
	void *gui=GetMultiLinesMenuGUI(ma, mfree_adr());
	SetMenuToGUI(gui, menu);
	SetMenuItemCount(gui, n_items);
	MenuSetUserPointer(gui, user_pointer);
	SetCursorToMenuItem(gui, start_item);
	SetHeaderToMenu(gui, hdr, ma);
	return (CreateGUI(gui));
}

unsigned int CreateSLMenu(const MENU_DESC *menu, const HEADER_DESC *hdr, int start_item, int n_items, void *user_pointer)
{
	
	void *ma=malloc_adr();
	void *gui=GetMenuGUI(ma, mfree_adr());
	SetMenuToGUI(gui, menu);
	SetMenuItemCount(gui, n_items);
	MenuSetUserPointer(gui, user_pointer);
	SetCursorToMenuItem(gui, start_item);
	SetHeaderToMenu(gui, hdr, ma);
	return (CreateGUI(gui));
}

unsigned int CreateSLMenu_30or2(const MENU_DESC *menu, const HEADER_DESC *hdr, int start_item, int n_items, void *user_pointer)
{
	
	void *ma=malloc_adr();
	void *gui=GetMenuGUI(ma, mfree_adr());
	SetMenuToGUI(gui, menu);
	SetMenuItemCount(gui, n_items);
	MenuSetUserPointer(gui, user_pointer);
	SetCursorToMenuItem(gui, start_item);
	SetHeaderToMenu(gui, hdr, ma);
	return (CreateGUI_30or2(gui));
}

