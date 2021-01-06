#ifndef _DECODE_XML_H_
  #define _DECODE_XML_H_


typedef struct XMLAttr_type XMLAttr;

typedef struct XMLAttr_type {
  XMLAttr *next;
  char *name;
  char *param;
} _XMLAttr;

typedef struct XMLNode_type XMLNode;

typedef struct XMLNode_type {
  XMLNode *next;
  XMLNode *subnode;
  char *name;
  XMLAttr *attr;
  char *value;
} _XMLNode;


// Декодировать поток
XMLNode *XMLDecode(char *buf, int size);

// Уничтожить дерево
void DestroyTree(XMLNode *tmpp);

enum XML_MAINSTATE{
  MS_BEGIN=1,                 //< Начало парсинга
  MS_BEGINTAG,                //< Начался тег
  MS_MIDDLETAG,               //< Середина тега, но еще до имени
  MS_TAGNAME,                 //< Парсим имя тега
  MS_ENDTAGNAME,              //< Закончили парсить имя тега
  MS_ATTRIBNAME,              //< Парсим имя аттрибута
  MS_ENDATTRIBNAME,           //< Прочитали имя аттрибута
  MS_ENDEQUALLY,              //< Прошли знак = между именем аттритута и значением
  MS_ATTRIBVALUE,             //< Парсим значение аттрибута (после ")
  MS_ENDTAG,                  //< Конец тега (для самозакрывающегося после /)
  MS_TEXT,                    //< Текст
  MS_CHECK_DECL,
  MS_CDATA_SECTION,
  MS_COMMENT
};

enum XML_TAGSTATE{
  TS_INDEFINITE=1,            //< Неопределенный, т.к. тег только начали парсить (если начали)
  TS_NORMAL,                  //< Обычный (не)закрывающийся. Точно не декларация
  TS_CLOSE,                   //< Закрывающийся
  TS_EMPTY,                   //< Сам и закрывается
  TS_DECLARATION              //< Декларация, что это XML. Парсер аттрибуты игнорирует
};

#endif
