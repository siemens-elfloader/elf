/*
    SieNatJabber Project

    Отображение меню закладок
*/

#ifndef _BOOKMARKS_H_
  #define _BOOKMARKS_H_

#include "xml_parser.h"
// Получить список закладок
void Get_Bookmarks_List();

// Уничтожить список закладок
void KillBMList();

// Jabber Handler
void Process_Bookmarks_Storage(XMLNode* nodeEx);

// Отобразить меню закладок
void Disp_BM_Menu();


#endif
