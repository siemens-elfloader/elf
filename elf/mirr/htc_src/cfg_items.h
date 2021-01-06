#define CFG_UINT 1
#define CFG_STR_UTF8 2
#define CFG_INT 3
#define CFG_STR_WIN1251 4
#define CFG_CBOX 5
#define CFG_STR_PASS 6
#define CFG_COORDINATES 7
#define CFG_COLOR 8
//Level
//min<>0 - start tag (name used)
//min=0 - end tag
#define CFG_LEVEL 9

#define CFG_UTF8_STRING 10
#define CFG_CHECKBOX 11
#define CFG_TIME 12   
//TTime
#define CFG_DATE 13  
//TDate
#define CFG_RECT 14  
//RECT

typedef struct
{
  int type;
  char name[32];
  unsigned int min;
  unsigned int max;
}CFG_HDR;

typedef struct
{
  char cbox_text[32];
}CFG_CBOX_ITEM;





