//
//  ALL THE RENDERER NEED
//  add content by add items util, then render by this util
//  this -> addItems
//  this !-> refCache, just hold pos of the ref
//
#ifndef _BALLETVIEW_H_
#define _BALLETVIEW_H_
#include "color.h"
#include "main.h"
#include "../inc/pnglist.h"

typedef struct
{
  DYNPNGICONLIST dp;
  int w_char;
  int index;
}OMS_DYNPNGLIST;

// линия кончается с данными параметрами, т.е. это параметры следующей строки
// выравнивание, же, - для данной линии
typedef struct
{
  unsigned int pos; // позиция последнего символа в строке
  unsigned short ink1;
  unsigned short ink2;
  unsigned short paper1;
  unsigned short paper2;
  unsigned short pixheight;
  unsigned short bold:1, underline:1, ref:1,center:1,right:1,centerAtAll:1;
}LINECACHE;

typedef struct
{
  int           tag;
  unsigned int  begin;
  unsigned int  end;
  LOG_MESSAGE  *id;
}REFCACHE;
/*
// smiles
typedef struct
{
  void *next;
  unsigned int key; //Для быстрой проверки
  unsigned int mask;
  char text[1];
}STXT_SMILES;

typedef struct
{
  void *next;
  unsigned int uni_smile;
  STXT_SMILES *lines; //Список строк
  STXT_SMILES *botlines;
}S_SMILES;
*/
typedef struct
{
  unsigned short *rawtext;
  unsigned int rawtext_size;
  
  LINECACHE *lines_cache;
  unsigned int lines_cache_size;
  
  unsigned int view_line;
  int pixdisp;
  
  WSHDR            *ws;
  
  unsigned int      pos_cur_ref;
  
  unsigned int      pos_first_ref;
  unsigned int      pos_last_ref;
  unsigned int      pos_prev_ref;
  unsigned int      pos_next_ref;
  
  REFCACHE         *ref_cache;
  int               ref_cache_size;
  REFCACHE          work_ref;
  
  OMS_DYNPNGLIST   *dynpng_list;
  
  int               OLD_MessList_Count;
  TRESOURCE        *Resource_Ex;
  
  unsigned short lastLineHeight;

}VIEWDATA;

// siemens_unicode.h
#define UTF16_DIS_UNDERLINE (0xE002)
#define UTF16_ENA_UNDERLINE (0xE001)
#define UTF16_DIS_INVERT (0xE004)
#define UTF16_ENA_INVERT (0xE005)
#define UTF16_INK_RGBA (0xE006)
#define UTF16_PAPER_RGBA (0xE007)
#define UTF16_INK_INDEX (0xE008)
#define UTF16_PAPER_INDEX (0xE009)
#define UTF16_FONT_SMALL (0xE012)
#define UTF16_FONT_SMALL_BOLD (0xE013)
#define UTF16_ALIGN_LEFT (0xE01C)
#define UTF16_ALIGN_RIGHT (0xE01D)
#define UTF16_ENA_CENTER (0xE01E)
#define UTF16_DIS_CENTER (0xE01F)
#define UTF16_NEWLINE 0x000A
#define UTF16_SPACE 0x0020

// main.h
typedef struct
{
  GUI gui;
  VIEWDATA vd;
}VIEW_GUI;


// string_works.h
void debugf(char *file,int line);
#define DEBUGF(void) debugf(__FILE__,__LINE__)
void debugv(char *file,int line,void *p, int sz);
#define DEBUGV(a,b) debugv(__FILE__,__LINE__,a,b)
#define DEBUGC(a) debugv(__FILE__,__LINE__,a,strlen(a))
#define DEBUGS(a,b) {static char c[512];sprintf(c,a,b);DEBUGV(c,strlen(c));}



void VIEWDATA_Display(TRESOURCE* ContEx);
void Init_Message(TRESOURCE* ContEx, char *init_text);

#endif
