#include "include.h"
#include "CreateMenu.h"



int CreateMenu(const ML_MENU_DESC *menu, const HEADER_DESC *hdr, int start_item, int n_items, void *user_pointer)
{
  void *ma=malloc_adr();
  void *gui=GetMultiLinesMenuGUI(ma, mfree_adr());
  SetMenuToGUI(gui, menu);
  SetMenuItemCount(gui, n_items);
  MenuSetUserPointer(gui, user_pointer);
  SetCursorToMenuItem(gui, start_item);
  patch_header(hdr);
  SetHeaderToMenu(gui, hdr, ma);
  return CreateGUI(gui);
}

int CreateMenu(const MENU_DESC *menu, const HEADER_DESC *hdr, int start_item, int n_items, void *user_pointer)
{
  void *ma=malloc_adr();
  void *gui=GetMenuGUI(ma, mfree_adr());
  SetMenuToGUI(gui, menu);
  SetMenuItemCount(gui, n_items);
  MenuSetUserPointer(gui, user_pointer);
  SetCursorToMenuItem(gui, start_item);
  patch_header(hdr);
  SetHeaderToMenu(gui, hdr, ma);
  return CreateGUI(gui);
}


int CreateMenu(const ML_MENU_DESC *menu, const HEADER_DESC *hdr, WSHDR *hdr_t, int start_item, int n_items, void *user_pointer)
{
  void *ma=malloc_adr();
  void *mf=mfree_adr();
  void *gui=GetMultiLinesMenuGUI(ma, mf);
  SetMenuToGUI(gui, menu);
  SetMenuItemCount(gui, n_items);
  MenuSetUserPointer(gui, user_pointer);
  SetCursorToMenuItem(gui, start_item);
  patch_header(hdr);
  SetHeaderToMenu(gui, hdr, ma);
  SetHeaderText(GetHeaderPointer(gui), hdr_t, ma, mf);
  return CreateGUI(gui);
}

int CreateMenu(const MENU_DESC *menu, const HEADER_DESC *hdr, WSHDR *hdr_t, int start_item, int n_items, void *user_pointer)
{
  void *ma=malloc_adr();
  void *mf=mfree_adr();
  void *gui=GetMenuGUI(ma, mf);
  SetMenuToGUI(gui, menu);
  SetMenuItemCount(gui, n_items);
  MenuSetUserPointer(gui, user_pointer);
  SetCursorToMenuItem(gui, start_item);
  patch_header(hdr);
  SetHeaderToMenu(gui, hdr, ma);
  SetHeaderText(GetHeaderPointer(gui), hdr_t, ma, mf);
  return CreateGUI(gui);
}


int CreateMenu30or2(const ML_MENU_DESC *menu, const HEADER_DESC *hdr, WSHDR *hdr_t, int start_item, int n_items, void *user_pointer)
{
  void *ma=malloc_adr();
  void *mf=mfree_adr();
  void *gui=GetMultiLinesMenuGUI(ma, mf);
  SetMenuToGUI(gui, menu);
  SetMenuItemCount(gui, n_items);
  MenuSetUserPointer(gui, user_pointer);
  SetCursorToMenuItem(gui, start_item);
  patch_option_header(hdr);
  SetHeaderToMenu(gui, hdr, ma);
  SetHeaderText(GetHeaderPointer(gui), hdr_t, ma, mf);
  return CreateGUI_30or2(gui);
}

int CreateMenu30or2(const MENU_DESC *menu, const HEADER_DESC *hdr, WSHDR *hdr_t, int start_item, int n_items, void *user_pointer)
{
  void *ma=malloc_adr();
  void *mf=mfree_adr();
  void *gui=GetMenuGUI(ma, mf);
  SetMenuToGUI(gui, menu);
  SetMenuItemCount(gui, n_items);
  MenuSetUserPointer(gui, user_pointer);
  SetCursorToMenuItem(gui, start_item);
  patch_option_header(hdr);
  SetHeaderToMenu(gui, hdr, ma);
  SetHeaderText(GetHeaderPointer(gui), hdr_t, ma, mf);
  return CreateGUI_30or2(gui);
}

int CreateMenu30or2(const ML_MENU_DESC *menu, const HEADER_DESC *hdr, int start_item, int n_items, void *user_pointer)
{
  void *ma=malloc_adr();
  void *gui=GetMultiLinesMenuGUI(ma, mfree_adr());
  SetMenuToGUI(gui, menu);
  SetMenuItemCount(gui, n_items);
  MenuSetUserPointer(gui, user_pointer);
  SetCursorToMenuItem(gui, start_item);
  patch_option_header(hdr);
  SetHeaderToMenu(gui, hdr, ma);
  return CreateGUI_30or2(gui);
}

int CreateMenu30or2(const MENU_DESC *menu, const HEADER_DESC *hdr, int start_item, int n_items, void *user_pointer)
{
  void *ma=malloc_adr();
  void *gui=GetMenuGUI(ma, mfree_adr());
  SetMenuToGUI(gui, menu);
  SetMenuItemCount(gui, n_items);
  MenuSetUserPointer(gui, user_pointer);
  SetCursorToMenuItem(gui, start_item);
  patch_option_header(hdr);
  SetHeaderToMenu(gui, hdr, ma);
  return CreateGUI_30or2(gui);
}



