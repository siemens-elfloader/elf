/*******************************************************************************
 Диалог ввода URL
*******************************************************************************/
#include "include.h"
#include "inet.h"
#include "url_input.h"
#include "gui.h"
#include "log.h"
#include "daemon.h"
#include "rect_patcher.h"
#include "files_menu.h"
#include "bookmarks.h"
#include "langpack.h"
#include "url_utils.h"
#include "dialog.h"

void input_options_select_bookmark(USR_MENU_ITEM *item)
{
  BookmarksMenu * bm;
  if (item->type==0)
  {
    switch(item->cur_item)
    {
    case 0: ascii2ws(item->ws, LangPack::Active->data[LGP_Bookmarks]); break;
    }
  }
  if (item->type==1)
  {
    switch(item->cur_item)
    {
    case 0:
      bm = new BookmarksMenu;
      bm->Show(item->user_pointer);
      break;
    }
  }
}

void input_options_select_folder(USR_MENU_ITEM *item)
{
  FilesMenu * fm;
  if (item->type==0)
  {
    switch(item->cur_item)
    {
    case 0: ascii2ws(item->ws, LangPack::Active->data[LGP_SelectFolder]); break;
    }
  }
  if (item->type==1)
  {
    switch(item->cur_item)
    {
    case 0:
      fm = new FilesMenu;
      fm->Show(item->user_pointer, FilesMenu::FIND_FOLDERS);
      break;
    }
  }
}

int urlinput_onkey(GUI *gui, GUI_MSG *msg)
{
  URLInput * ui = (URLInput *)EDIT_GetUserPointer(gui);
  return ui->onKey(gui, msg);
}

void urlinput_ghook(GUI *gui, int cmd)
{
  URLInput * ui = (URLInput *)EDIT_GetUserPointer(gui);
  ui->gHook(gui, cmd);
}

void urlinput_locret(void) {};

SOFTKEY_DESC urlinput_sk[]=
{
  {0x0018,0x0000,NULL},
  {0x0001,0x0000,(int)"OK"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB urlinput_skt=
{
  urlinput_sk,0
};

HEADER_DESC urlinput_hdr={0,0,0,0, NULL, NULL, LGP_NULL};

INPUTDIA_DESC urlinput_desc=
{
  1,
  urlinput_onkey,
  urlinput_ghook,
  (void *)urlinput_locret,
  0,
  &urlinput_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0x40000000// Поменять софт-кнопки
};

int  URLInput::onKey(GUI *gui, GUI_MSG *msg)
{
  if (msg->keys==0xFF0)
  {
    return GUI_RESULT_CLOSE;
  }
  if(msg->keys==0xFFF)
  {
    EDITCONTROL ec;
    ExtractEditControl(gui, url_pos, &ec);
    if(!ec.pWS->wsbody[0])
    {
      MsgBoxError(1, (int)LangPack::Active->data[LGP_EnterUrl]);
      return GUI_RESULT_OK;
    }
    int new_len;
    char * u_str = new char[ec.maxlen];
    ws_2utf8(ec.pWS, u_str, &new_len, ec.maxlen);
    if (strlen(u_str)<=7) // http://
    {
      MsgBoxError(1, (int)LangPack::Active->data[LGP_EnterUrl]);
      delete u_str;
      return GUI_RESULT_OK;
    }
    ExtractEditControl(gui, path_pos, &ec);
    if(!ec.pWS->wsbody[0])
    {
      MsgBoxError(1, (int)LangPack::Active->data[LGP_EnterDownloadsFolder]);
      delete u_str;
      return GUI_RESULT_OK;
    }
    char * url = new char[new_len + 1];
    strcpy(url, u_str);
    delete u_str;
    
    char * path = new char[ec.maxlen];
    ws_2str(ec.pWS, path, ec.maxlen);
    
    char * fname = NULL;
    ExtractEditControl(gui, fname_pos, &ec);
    if(ec.pWS->wsbody[0])
    {
      fname = new char[ec.maxlen];
      ws_2str(ec.pWS, fname, ec.maxlen);
    }
    char * referer = NULL;
    ExtractEditControl(gui, referer_pos, &ec);
    if(ec.pWS->wsbody[0])
    {
      referer = new char[ec.maxlen];
      ws_2str(ec.pWS, referer, ec.maxlen);
    }
    char * cookies = NULL;
    ExtractEditControl(gui, cookies_pos, &ec);
    if(ec.pWS->wsbody[0])
    {
      cookies = new char[ec.maxlen];
      ws_2str(ec.pWS, cookies, ec.maxlen);
    }
    Download * new_dl = new Download;
    new_dl->url = url;
    if (fname)
    {
      new_dl->is_const_file_name = 1;
      new_dl->file_name = fname;
    }
    new_dl->referer = referer;
    new_dl->cookies = cookies;
    new_dl->file_path = path;
    new_dl->StartDownload();
    if(CFG_CLOSE_GUI) SieGetDialog::Active->Close();
    else return GUI_RESULT_CLOSE;
  }
  if(msg->gbsmsg->msg==KEY_DOWN && msg->gbsmsg->submess==ENTER_BUTTON)
  {
    int focus = EDIT_GetFocus(gui);
    if (focus == url_pos)
    {
      EDIT_OpenOptionMenuWithUserItems(gui, input_options_select_bookmark, gui, 1);
      return GUI_RESULT_REDRAW;
    }
    if (focus == path_pos)
    {
      EDIT_OpenOptionMenuWithUserItems(gui, input_options_select_folder, gui, 1);
      return GUI_RESULT_REDRAW;
    }
  }
  return GUI_RESULT_OK;
}

void URLInput::gHook(GUI *gui, int cmd)
{
  EDITCONTROL ec;
  static const SOFTKEY_DESC sk_ok={0x0FFF,0x0000,(int)"OK"};
  static const SOFTKEY_DESC sk_cancel={0x0FF0,0x0000,(int)LangPack::Active->data[LGP_Cancel]};
  if (cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
  if (cmd==TI_CMD_DESTROY)
  {
    delete this;
  }
  if (cmd==TI_CMD_REDRAW)
  {
    SetSoftKey(gui, &sk_ok, SET_SOFT_KEY_N); // Устанавливаем на правый софткей текст "OK"
    ExtractEditControl(gui, EDIT_GetFocus(gui), &ec); // Извлекаем выделенный EDITCONTROL
    if (!ec.pWS->wsbody[0] || EDIT_GetCursorPos(gui) == 1) // Если строка пуста или курсор в начале строки
      SetSoftKey(gui, &sk_cancel, SET_SOFT_KEY_N==0?1:0); // Ставим на левй софткей текст "Cancel"
  }
}

void URLInput::Show(char * url_str, char * ref_str)
{
  WSHDR * ws = AllocWS(512);
  EDITCONTROL ec;
  void * ma = malloc_adr();
  void * eq;

  eq = AllocEQueue(ma, mfree_adr());

  ascii2ws(ws, "URL:");
  PrepareEditControl(&ec);
  ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, ws->wsbody[0]);
  AddEditControlToEditQend(eq, &ec, ma);
  
  URL_unescape(url_str);
  utf8_2ws(ws, url_str, 511);
  PrepareEditControl(&ec);
  ConstructEditControl(&ec, ECT_NORMAL_TEXT, ECF_APPEND_EOL, ws, 511);
  url_pos = AddEditControlToEditQend(eq, &ec, ma);
  
  ascii2ws(ws, LangPack::Active->data[LGP_DownloadFolder]);
  PrepareEditControl(&ec);
  ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, ws->wsbody[0]);
  AddEditControlToEditQend(eq, &ec, ma);
  
  str_2ws(ws, CFG_DOWNLOADS_FOLDER, 511);
  PrepareEditControl(&ec);
  ConstructEditControl(&ec, ECT_NORMAL_TEXT, ECF_APPEND_EOL, ws, 511);
  path_pos = AddEditControlToEditQend(eq, &ec, ma);

  ascii2ws(ws, LangPack::Active->data[LGP_FileName]);
  PrepareEditControl(&ec);
  ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, ws->wsbody[0]);
  AddEditControlToEditQend(eq, &ec, ma);
  
  ascii2ws(ws, "");
  PrepareEditControl(&ec);
  ConstructEditControl(&ec, ECT_NORMAL_TEXT, ECF_APPEND_EOL, ws, 256);
  fname_pos = AddEditControlToEditQend(eq, &ec, ma);
  
  ascii2ws(ws, "Referer:");
  PrepareEditControl(&ec);
  ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, ws->wsbody[0]);
  AddEditControlToEditQend(eq, &ec, ma);
  
  ascii2ws(ws, ref_str ? ref_str : "");
  PrepareEditControl(&ec);
  ConstructEditControl(&ec, ECT_NORMAL_TEXT, ECF_APPEND_EOL, ws, 256);
  referer_pos = AddEditControlToEditQend(eq, &ec, ma);
  
  ascii2ws(ws, "Cookies:");
  PrepareEditControl(&ec);
  ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, ws->wsbody[0]);
  AddEditControlToEditQend(eq, &ec, ma);
  
  ascii2ws(ws, "");
  PrepareEditControl(&ec);
  ConstructEditControl(&ec, ECT_NORMAL_TEXT, ECF_APPEND_EOL, ws, 1024);
  cookies_pos = AddEditControlToEditQend(eq, &ec, ma);

  FreeWS(ws);
  
  patch_header(&urlinput_hdr, &IconPack::Active->data[IMG_New], (int)LangPack::Active->data[LGP_NewDownload]);
  patch_input(&urlinput_desc);
  urlinput_sk[0].lgp_id = (int)LangPack::Active->data[LGP_Cancel];
  CreateInputTextDialog(&urlinput_desc,&urlinput_hdr,eq,1,this);
}
