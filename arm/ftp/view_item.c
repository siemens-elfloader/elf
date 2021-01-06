#include "../inc/swilib.h"
#include "view_item.h"
#include "rect_patcher.h"
#include "strings.h"

static const HEADER_DESC view_item_hdr={0,0,NULL,NULL,NULL,(int)"View Item",LGP_NULL};

static void view_item_locret(void){}

static const SOFTKEY_DESC view_item_sk[] =
{
  {0x0018, 0x0000, (int)""},
  {0x0001, 0x0000, (int)"Close"},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB view_item_skt =
{
  view_item_sk, 0
};

static int view_item_onkey(GUI *data, GUI_MSG *msg)
{
  return (0);
}

static void view_item_ghook(GUI *gui, int cmd)
{
  if (cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
  if (cmd==TI_CMD_SUBFOCUS_CHANGE)
  {
    if (EDIT_GetFocus(gui)>EDIT_GetUnFocus(gui)) // Если листаем сверху вниз...
      EDIT_SetCursorPos(gui, 1); // ...То ставим курсор в начало
  }
}

static const INPUTDIA_DESC view_item_desc =
{
  1,
  view_item_onkey,
  view_item_ghook,
  (void *)view_item_locret,
  0,
  &view_item_skt,
  {0,NULL,NULL,NULL},
  FONT_SMALL,
  100,
  101,
  0,
  //  0x00000001 - Выровнять по правому краю
  //  0x00000002 - Выровнять по центру
  //  0x00000004 - Инверсия знакомест
  //  0x00000008 - UnderLine
  //  0x00000020 - Не переносить слова
  //  0x00000200 - bold
  0,
  //  0x00000002 - ReadOnly
  //  0x00000004 - Не двигается курсор
  //  0x40000000 - Поменять местами софт-кнопки
  0x40000000
};

int create_view_item(RSS_ITEM *p)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  EDITC_OPTIONS ec_options;
  int t_len=0, d_len=0, a_len=0, h_len=64, max;
  WSHDR *ws;

  eq=AllocEQueue(ma,mfree_adr());
  if (p->title) t_len=strlen(p->title);
  if (p->author) a_len=strlen(p->author);
  if (p->description) d_len=strlen(p->description);
  
  if (t_len>h_len) max=t_len;
  if (a_len>max) max=a_len;
  if (d_len>max) max=d_len;

  ws=AllocWS(max);
  
  if (p->title)
  {
    PrepareEditControl(&ec);
    ascii2ws(ws,"Title:");
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws,ws->wsbody[0]);
    AddEditControlToEditQend(eq,&ec,ma);
    
    PrepareEditControl(&ec);
    ascii2ws(ws,p->title);
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws,ws->wsbody[0]);
    PrepareEditCOptions(&ec_options);
    SetFontToEditCOptions(&ec_options,1);
    CopyOptionsToEditControl(&ec,&ec_options);
    AddEditControlToEditQend(eq,&ec,ma);
  }
  
  if (p->author)
  {
    PrepareEditControl(&ec);
    ascii2ws(ws,"Author:");
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws,ws->wsbody[0]);
    AddEditControlToEditQend(eq,&ec,ma);
    
    PrepareEditControl(&ec);
    ascii2ws(ws,p->author);
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws,ws->wsbody[0]);
    PrepareEditCOptions(&ec_options);
    SetFontToEditCOptions(&ec_options,1);
    CopyOptionsToEditControl(&ec,&ec_options);
    AddEditControlToEditQend(eq,&ec,ma);
  }
  
  if (p->description)
  {
    PrepareEditControl(&ec);
    ascii2ws(ws,"Description:");
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws,ws->wsbody[0]);
    AddEditControlToEditQend(eq,&ec,ma);
    
    PrepareEditControl(&ec);
    ascii2ws(ws,p->description);
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws,ws->wsbody[0]);
    PrepareEditCOptions(&ec_options);
    SetFontToEditCOptions(&ec_options,1);
    CopyOptionsToEditControl(&ec,&ec_options);
    AddEditControlToEditQend(eq,&ec,ma);
  }

  FreeWS(ws);
  patch_header(&view_item_hdr);
  patch_input(&view_item_desc);
  return CreateInputTextDialog(&view_item_desc,&view_item_hdr,eq,1,NULL);
}
