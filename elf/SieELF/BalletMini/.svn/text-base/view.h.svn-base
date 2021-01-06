#ifndef _VIEW_H_
#define _VIEW_H_

#include "../inc/pnglist.h"

#define _NOREF (0xFFFFFFFF)

typedef struct
{
  DYNPNGICONLIST dp;
  int w_char;
  int index;
}OMS_DYNPNGLIST;


#pragma pack(push)
#pragma pack(1)
typedef struct
{
  unsigned short magic;
  unsigned long size;
}OMS_HEADER_COMMON;

typedef struct
{
  unsigned short res1[9];
  unsigned short tag_count;
  unsigned short part_current;
  unsigned short part_count;
  unsigned short res2;
  unsigned short Stag_count;
  unsigned short res3;
  unsigned char res4;
  unsigned short cachable;
  unsigned short res5;
}OMS_HEADER_V2;

#pragma pack(pop)

typedef struct
{
  unsigned long 
  reserved:8,
  red:5, green:6, blue: 5,
  unk0:1,bold:1,underline:1,unk3:1,center:1,right:1,unk6:1,unk7:1;
}TAG_S;

typedef struct
{
  unsigned short red:5, green:6, blue: 5;
}TAG_D;

typedef struct
{
  unsigned int   pos; // last line character
  unsigned short ink1; // line ends with . . .
  unsigned short ink2;
  unsigned short paper1;
  unsigned short paper2;
  unsigned short bold:1,underline:1,ref:1,center:1,right:1,centerAtAll:1;
  unsigned short pixheight; // line height
}LINECACHE;

typedef struct
{
  unsigned int begin;
  unsigned int end;
  int tag;
  unsigned int id;
  unsigned int value;
  unsigned int id2;
  //WSHDR *ws;
  void *data;
  int size;
  char no_upload:1, multiselect:1;
}REFCACHE;


typedef struct
{
  z_stream *zs;              
  
  int cached;
  
  unsigned short *rawtext;
  unsigned int rawtext_size;
    
  LINECACHE *lines_cache;
  unsigned int lines_cache_size;
  unsigned int lines_cache_pos;

  unsigned int view_line;
  int pixdisp;
  
  WSHDR *ws;
  
  unsigned int pos_cur_ref;
  
  unsigned int pos_first_ref;
  unsigned int pos_last_ref;
  unsigned int pos_prev_ref;
  unsigned int pos_next_ref;

  //
  char *oms;
  int oms_size;
  int oms_pos;
  int oms_wanted;
  int parse_state;
  //
  //int tag_l_count;
  //
  TAG_S *S_cache;
  int S_cache_size;
  TAG_S current_tag_s;
  TAG_S prev_tag_s;
//  int prev_bold;
//  int prev_underline;
  
  TAG_D current_tag_d;
  //
  unsigned int iw;
  unsigned int ih;
  //
  unsigned int tag_o_count;
  //unsigned int ref_mode_L;
  unsigned int ref_mode_i;
  char ref_mode_P;
  //
  OMS_DYNPNGLIST *dynpng_list;
  
  //References
  REFCACHE work_ref;
  REFCACHE work_ref_Z;
  REFCACHE *ref_cache;
  int ref_cache_size;
  
  int page_sz;
  int loaded_sz;
  unsigned short wchar_hr;
  
  char *pageurl;    //utf8
  char *title;
  
  int WCHAR_BUTTON_OFF, WCHAR_BUTTON_ON, WCHAR_RADIO_OFF, WCHAR_RADIO_ON, WCHAR_TEXT_FORM, WCHAR_LIST_FORM;
  
}VIEWDATA;

//#define RADIO_BTTN_CLKD "radio_bttn_clkd.png"
//#define RADIO_BTTN      "radio_bttn.png"
//#define BUTTON_CLKD     "button_clkd.png"
//#define BUTTON          "button.png"
//#define TEXT_FORM       "text_form.png"
//#define LIST            "list.png"

#endif


