#ifndef _CREATEMENU_H_
#define _CREATEMENU_H_



  int CreateMenu(const ML_MENU_DESC *menu, const HEADER_DESC *hdr, int start_item, int n_items, void *user_pointer);
  int CreateMenu(const MENU_DESC *menu, const HEADER_DESC *hdr, int start_item, int n_items, void *user_pointer);
  int CreateMenu(const ML_MENU_DESC *menu, const HEADER_DESC *hdr, WSHDR *hdr_t, int start_item, int n_items, void *user_pointer);
  int CreateMenu(const MENU_DESC *menu, const HEADER_DESC *hdr, WSHDR *hdr_t, int start_item, int n_items, void *user_pointer);
  int CreateMenu30or2(const ML_MENU_DESC *menu, const HEADER_DESC *hdr, int start_item, int n_items, void *user_pointer);
  int CreateMenu30or2(const MENU_DESC *menu, const HEADER_DESC *hdr, int start_item, int n_items, void *user_pointer);
  int CreateMenu30or2(const ML_MENU_DESC *menu, const HEADER_DESC *hdr, WSHDR *hdr_t, int start_item, int n_items, void *user_pointer);
  int CreateMenu30or2(const MENU_DESC *menu, const HEADER_DESC *hdr, WSHDR *hdr_t, int start_item, int n_items, void *user_pointer);

#endif



