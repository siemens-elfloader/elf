unsigned int CreateSLMenu(const MENU_DESC *menu, const HEADER_DESC *hdr, int start_item, int n_items, void *user_pointer);
unsigned int CreateMLMenu(const ML_MENU_DESC *menu, const HEADER_DESC *hdr, int start_item, int n_items, void *user_pointer);
unsigned int CreateSLMenu_30or2(const MENU_DESC *menu, const HEADER_DESC *hdr, int start_item, int n_items, void *user_pointer);
unsigned int CreateMLMenuWSHDR(const ML_MENU_DESC *menu, const HEADER_DESC *hdr, WSHDR *hdr_t, int start_item, int n_items, void *user_pointer);
unsigned int CreateSLMenuWSHDR(const MENU_DESC *menu, const HEADER_DESC *hdr, WSHDR *hdr_t, int start_item, int n_items, void *user_pointer);

