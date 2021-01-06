#ifndef _MAINMENU_H_
  #define _MAINMENU_H_

void inp_locret(void);

void patch_header(HEADER_DESC* head);

void patch_input(INPUTDIA_DESC* inp);

// Показать главное меню
void MM_Show();

#ifndef NO_PNG /////////////////////////////////////

#define TOTAL_ITEMS 7

static const char * const items[TOTAL_ITEMS] = {
/*  1*/ "setnexttrack",
/*  2*/ "showid3",
/*  3*/ "fm",
/*  4*/ "setsmenu",
/*  5*/ "settings",
/*  6*/ "about",
/*  7*/ "exit",
};
#endif

#endif /////////////////////////////////////////////
