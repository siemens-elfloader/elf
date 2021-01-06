/*
    SieNatJabber Project
    Функции работы с vCard

    Работа с присланной нодой vCard, сохранение фотки
*/

#ifndef _VCARD_H_
  #define _VCARD_H_

#include "xml_parser.h"

// Создание чистой vCard
VCARD Create_vCard();

// Освобождение памяти из-под vCard
void Free_vCard(VCARD vcard);

// Получить поле из vCard
char *Get_VCard_Value(VCARD src, char *par_name);

// Обработчик ноды vCard
void Process_vCard(char *from, XMLNode *vCard);

// Показать фотку из вкарда
void vCard_Photo_Display(char *path);

// Показать vCard для контакта по JID. Если контакт не имеет vCard, возвращает 0, иначе 1.
int Show_vCard(char *jid);

#endif

