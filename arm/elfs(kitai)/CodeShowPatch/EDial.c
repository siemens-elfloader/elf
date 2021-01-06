#include "addr.h"
#include "type_.h"
typedef struct
{
  unsigned short invert;  // |1
  unsigned short bitmask;
  char font;              // |2
  char align;             // |4
  char pen[4];            // |8
  char brush[4];          // |0x10
}EDITC_OPTIONS;

#pragma pack(2)
typedef struct
{
  char type;
  char unk2[3];
  int flag;
  char zero_cbox;  // if text input field: lang 0 - default, 2 - english
  char unk5;
  EDITC_OPTIONS ed_options;
  short maxlen;
  short num_of_items_cbox;
  short start_item_cbox;
  short unk9;
  short unk10;
  short unk11;
  int unk12;
  WSTRING *pWS;
}EDITCONTROL;
#pragma pack()

extern WSTRING*  WS_InitByZero(WSTRING*, word* buf, int count);
extern void AppendInfoW(WSTRING *pWS, WSTRING * pNo);
extern void AddNewLine(WSTRING *ws);
extern int IsNum(unsigned short *pstr, int enable_dot);
__thumb void AddDialEQ(void *eq, EDITCONTROL *ec, EDITC_OPTIONS *ecop, void *malloc_adr)
{
  unsigned short ws_b[32];
  WSTRING *ws, _ws;
  ws=WS_InitByZero(&_ws, ws_b, 31);
  //0xA0A256E5   ; 165: void ConstructEditControl(EDITCONTROL *EditControl,int type,int flag,WSHDR *ws,int maxlen)
  ((void (*)(EDITCONTROL *, int, int, WSTRING *, int))ConstructEditControl_adr)(ec, 1, 0x40, ws, 31);
  
  //0xA0A25363   ; 1CA: void SetFontToEditCOptions(EDITC_OPTIONS *ec_options, int font)
  ((void (*)(EDITC_OPTIONS *, int))SetFontToEditCOptions_adr)(ecop, 1);
  
  //0738: 0xA0A25411   ; 1CE: void CopyOptionsToEditControl(EDITCONTROL *ec,EDITC_OPTIONS *ec_options)
  ((void (*)(EDITCONTROL *, EDITC_OPTIONS*))CopyOptionsToEditControl_adr)(ec, ecop);
  
  //0xA0A26133   ; 166: int AddEditControlToEditQend(void *EditQ,EDITCONTROL *EditControl,void *malloc_a)
  ((void (*)(void *, EDITCONTROL *, void *))AddEditControlToEditQend_adr)(eq, ec, malloc_adr);
}


__thumb void DialGHookRedraw(void *gui)
{
  EDITCONTROL ec;
  unsigned short ws_b[32];
  WSTRING *ws, _ws;
  unsigned short *pstr;
  ws=WS_InitByZero(&_ws, ws_b, 31);
  
  //0xA0A2BFB9   ; 169: int ExtractEditControl(void *guidata,int n,EDITCONTROL *)
  ((int (*)(void *, int, EDITCONTROL*))ExtractEditControl_adr)(gui, 1, &ec);
  pstr=ec.pWS->pstr;
  if(pstr[0]>=3 && IsNum(pstr, 0))
  {
    //((void (*)(WSTRING *,int))ADDR_wsAppendChar)(ws, 0xD);
    ((void (*)(WSTRING *,int))ADDR_wsAppendChar)(ws, 0xE01D);//©©сротй╬
    if(pstr[1]=='0')
      AppendInfoW(ws, ec.pWS);
    else if(pstr[1]=='+')
    {
      if(pstr[2]=='8' && pstr[3]=='6')
      {
	if(pstr[0]==3)
	{
	}
	else if(pstr[4]=='0')
	{
	  if(pstr[0]>=6)
	    AppendInfoW(ws, ec.pWS);
	}
	else if(pstr[4]=='1')
	{
	  if(pstr[0]>=10)
	    AppendInfoW(ws, ec.pWS);
	}
	else
	  AppendInfoW(ws, ec.pWS);
      }
      else
      {
	AppendInfoW(ws, ec.pWS);
      }
    }
    else if(pstr[1]=='1')
    {
      if(pstr[0]>=7)
	AppendInfoW(ws, ec.pWS);
    }
    else
      AppendInfoW(ws, ec.pWS);
  }
  //0778: 0xA0A2BFAD   ; 1DE: int EDIT_SetTextToEditControl(void *gui,int n,WSHDR *ws)
  ((int (*)(void *, int, WSTRING*))EDIT_SetTextToEditControl_adr)(gui, 2, ws);
}

