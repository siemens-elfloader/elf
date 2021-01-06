#include "..\inc\swilib.h"
#include "about.h"

extern int screenh;
extern int screenw;

extern const unsigned int cfg_gui_font;
extern const char cfg_gui_color[4];

char cr[] = "ECDICT\nEnglish-Chinese DICTionary for Siemens ELF.\n\nby CHC,bingk, 2007.\n";

void about(void)
{
  WSHDR *ws = AllocWS(256);
  str_2ws(ws, cr, sizeof(cr));
  DrawString(ws,5,YDISP,screenw,screenh-SoftkeyH(),cfg_gui_font,32,cfg_gui_color,GetPaletteAdrByColorIndex(23));
  FreeWS(ws);
}

