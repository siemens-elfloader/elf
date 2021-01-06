/*******************************************************************************
 Диалог ввода URL
*******************************************************************************/
#include "include.h"
#include "inet.h"
#include "info.h"
#include "gui.h"
#include "rect_patcher.h"
#include "langpack.h"
#include "iconpack.h"
#include "url_input.h"

int info_onkey(GUI *gui, GUI_MSG *msg)
{
  Info * i = (Info *)EDIT_GetUserPointer(gui);
  return i->onKey(gui, msg);
}

void info_ghook(GUI *gui, int cmd)
{
  Info * i = (Info *)EDIT_GetUserPointer(gui);
  i->gHook(gui, cmd);
}

void info_locret(void) {};

SOFTKEY_DESC info_sk[]=
{
  {0x0018,0x0000,(int)NULL},
  {0x0001,0x0000,(int)"OK"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB info_skt=
{
  info_sk,0
};

HEADER_DESC info_hdr={0,0,0,0, NULL, NULL,LGP_NULL};

INPUTDIA_DESC info_desc=
{
  1, info_onkey, info_ghook,
  (void *)info_locret,
  0,
  &info_skt,
  {0,0,0,0},
  4, 100, 101, 0,
  0,
  0x40000000// Поменять софт-кнопки
};

int Info::onKey(GUI *gui, GUI_MSG *msg)
{
  if (mode == DownloadInfo)
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
      
      ExtractEditControl(gui, path_pos, &ec);
      if(!ec.pWS->wsbody[0])
      {
        MsgBoxError(1, (int)LangPack::Active->data[LGP_EnterDownloadsFolder]);
        delete u_str;
        return GUI_RESULT_OK;
      }
      if ACTIVE_DOWNLOAD_STATE(download->download_state)
        download->download_state = DOWNLOAD_STOPPED;
      char * url = new char[new_len + 1];
      strcpy(url, u_str);
      delete u_str;
      
      char * path = new char[ec.maxlen];
      ws_2str(ec.pWS, path, ec.maxlen);
      if(strcmp(download->file_path, path))
      {
        _safe_delete(download->HTTPRequest);
        
        delete download->file_path;
        download->file_path = path;
        download->file_size = NULL;
        download->file_loaded_size = NULL;
      }
      else delete path;
      if(strcmp(download->url, url))
      {
        _safe_delete(download->HTTPRequest)

        delete download->url;
        download->url = url;
        download->file_size = NULL;
        download->file_loaded_size = NULL;
      }
      else delete url;
      return GUI_RESULT_CLOSE;
    }
    int focus = EDIT_GetFocus(gui);
    if(msg->gbsmsg->msg==KEY_DOWN && msg->gbsmsg->submess==ENTER_BUTTON && (focus == url_pos || focus == path_pos || focus == open_file_pos))
    {
      if(focus == url_pos)
      {
        EDIT_OpenOptionMenuWithUserItems(gui, input_options_select_bookmark, gui, 1);
        return GUI_RESULT_REDRAW;
      }
      if(focus == path_pos)
      {
        EDIT_OpenOptionMenuWithUserItems(gui, input_options_select_folder, gui, 1);
        return GUI_RESULT_REDRAW;
      }
      if(focus == open_file_pos && open_file_pos != -1)
      {
        int len = strlen(download->full_file_name);
        WSHDR * ws = AllocWS(len + 1);
        str_2ws(ws, download->full_file_name, len);
        ExecuteFile(ws, 0, 0);
        FreeWS(ws);
        return GUI_RESULT_REDRAW;
      }
    }
  }
  return GUI_RESULT_OK;
}

void Info::gHook(GUI *gui, int cmd)
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
  if (cmd==TI_CMD_REDRAW && download)
  {
    if (mode == DownloadInfo)
    {
      SetSoftKey(gui, &sk_ok, SET_SOFT_KEY_N); // Устанавливаем на правый софткей текст "OK"
      int focused = EDIT_GetFocus(gui);
      if(focused == url_pos || focused == path_pos)
      {
        ExtractEditControl(gui, focused, &ec); // Извлекаем выделенный EDITCONTROL
        if (!ec.pWS->wsbody[0] || EDIT_GetCursorPos(gui) == 1) // Если строка пуста или курсор в начале строки
          SetSoftKey(gui, &sk_cancel, SET_SOFT_KEY_N==0?1:0); // Ставим на левй софткей текст "Cancel"
      }
      else
        SetSoftKey(gui, &sk_cancel, SET_SOFT_KEY_N==0?1:0);
    }
  }
}

void Info::wsprintf_bytes(WSHDR * ws, int bytes)
{
  if(bytes < 1024)
    wsprintf(ws, "%u b", bytes);
  if(bytes > 1024 && bytes < (1024 * 1024))
    wsprintf(ws, "%u Kb (%u b)", bytes/1024, bytes);
  if(bytes > (1024 * 1024))
    wsprintf(ws, "%u Mb (%u Kb)", bytes/(1024 * 1024), bytes/1024);
}

void Info::wsprintf_bytes(WSHDR * ws, int bytes1, int bytes2)
{
  if(bytes1 < 1024) // Bytes
    wsprintf(ws, "%u b (%d%)", bytes1, bytes1 * 100 / bytes2);
  if(bytes1 > 1024 && bytes1 < (1024 * 1024)) // Kilobytes
    wsprintf(ws, "%u Kb (%u b, %d%)", bytes1/1024, bytes1, bytes1 * 100 / bytes2);
  if(bytes1 > (1024 * 1024)) // Megabytes
    wsprintf(ws, "%u Mb (%u Kb, %d%)", bytes1/(1024 * 1024), bytes1/1024, bytes1 * 100 / bytes2);
}

void Info::Show(Download * _download, Info::InfoMode _mode)
{
  open_file_pos = -1;
  mode = _mode;
  download = _download;
  WSHDR *ws = AllocWS(512);
  EDITCONTROL ec;
  void * ma=malloc_adr();
  void * eq;

  eq=AllocEQueue(ma,mfree_adr());

  switch (mode)
  {
  case DownloadInfo:
    ascii2ws(ws, LangPack::Active->data[LGP_DownloadState]);
    PrepareEditControl(&ec);
    ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, wstrlen(ws));
    AddEditControlToEditQend(eq,&ec,ma);
      
    switch(download->download_state)
    {
    case DOWNLOAD_ERROR: ascii2ws(ws, LangPack::Active->data[LGP_Error]); break;
    case DOWNLOAD_CONNECT: ascii2ws(ws, LangPack::Active->data[LGP_Connecting]); break;
    case DOWNLOAD_GET_INFO: ascii2ws(ws, LangPack::Active->data[LGP_GettingInfo]); break;
    case DOWNLOAD_DATA: ascii2ws(ws, LangPack::Active->data[LGP_Downloading]); break;
    case DOWNLOAD_COMPLETE: ascii2ws(ws, LangPack::Active->data[LGP_Completed]); break;
    case DOWNLOAD_STOPPED: ascii2ws(ws, LangPack::Active->data[LGP_Stopped]); break;
    default: ascii2ws(ws, LangPack::Active->data[LGP_Waiting]); break;
    }
    PrepareEditControl(&ec);
    ConstructEditControl(&ec, ECT_READ_ONLY, ECF_APPEND_EOL, ws, wstrlen(ws));
    AddEditControlToEditQend(eq,&ec,ma);
      
    ascii2ws(ws, "URL:");
    PrepareEditControl(&ec);
    ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, wstrlen(ws));
    AddEditControlToEditQend(eq,&ec,ma);
      
    utf8_2ws(ws, download->url, 511);
    PrepareEditControl(&ec);
    ConstructEditControl(&ec, 4, ECF_APPEND_EOL, ws, 511);
    url_pos = AddEditControlToEditQend(eq,&ec,ma);
      
    ascii2ws(ws, LangPack::Active->data[LGP_DownloadFolder]);
    PrepareEditControl(&ec);
    ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, wstrlen(ws));
    AddEditControlToEditQend(eq,&ec,ma);
      
    str_2ws(ws, download->file_path, 511);
    PrepareEditControl(&ec);
    ConstructEditControl(&ec, 4, ECF_APPEND_EOL, ws, 511);
    path_pos = AddEditControlToEditQend(eq,&ec,ma);
      
    ascii2ws(ws, LangPack::Active->data[LGP_FileSize]);
    PrepareEditControl(&ec);
    ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, wstrlen(ws));
    AddEditControlToEditQend(eq,&ec,ma);
      
    if(download->file_size) wsprintf_bytes(ws, download->file_size);
    else ascii2ws(ws, LangPack::Active->data[LGP_Unknown]);
    PrepareEditControl(&ec);
    ConstructEditControl(&ec, ECT_READ_ONLY, ECF_APPEND_EOL, ws, wstrlen(ws));
    AddEditControlToEditQend(eq,&ec,ma);
      
    ascii2ws(ws, LangPack::Active->data[LGP_LoadedSize]);
    PrepareEditControl(&ec);
    ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, wstrlen(ws));
    AddEditControlToEditQend(eq,&ec,ma);
      
    if(download->file_size) wsprintf_bytes(ws, download->file_loaded_size, download->file_size);
    else wsprintf_bytes(ws, download->file_loaded_size);
    PrepareEditControl(&ec);
    ConstructEditControl(&ec, ECT_READ_ONLY, ECF_APPEND_EOL, ws, wstrlen(ws));
    AddEditControlToEditQend(eq,&ec,ma);
    
    if (download->download_state == DOWNLOAD_COMPLETE)
    {
      ascii2ws(ws, LangPack::Active->data[LGP_OpenFile]);
      PrepareEditControl(&ec);
      ConstructEditControl(&ec, ECT_LINK, ECF_APPEND_EOL, ws, wstrlen(ws));
      open_file_pos = AddEditControlToEditQend(eq,&ec,ma);
    }
    break;
  case TrafficInfo:
    if (download)
    {
      ascii2ws(ws, LangPack::Active->data[LGP_Sended]);
      PrepareEditControl(&ec);
      ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, wstrlen(ws));
      AddEditControlToEditQend(eq,&ec,ma);
      
      wsprintf_bytes(ws, download->Tx);
      PrepareEditControl(&ec);
      ConstructEditControl(&ec, ECT_READ_ONLY, ECF_APPEND_EOL, ws, wstrlen(ws));
      AddEditControlToEditQend(eq,&ec,ma);
        
      ascii2ws(ws, LangPack::Active->data[LGP_Received]);
      PrepareEditControl(&ec);
      ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, wstrlen(ws));
      AddEditControlToEditQend(eq,&ec,ma);
        
      wsprintf_bytes(ws, download->Rx);
      PrepareEditControl(&ec);
      ConstructEditControl(&ec, ECT_READ_ONLY, ECF_APPEND_EOL, ws, wstrlen(ws));
      AddEditControlToEditQend(eq,&ec,ma);
    }
    ascii2ws(ws, LangPack::Active->data[LGP_TotalSended]);
    PrepareEditControl(&ec);
    ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, wstrlen(ws));
    AddEditControlToEditQend(eq,&ec,ma);
    
    wsprintf_bytes(ws, Download::GlobalTx);
    PrepareEditControl(&ec);
    ConstructEditControl(&ec, ECT_READ_ONLY, ECF_APPEND_EOL, ws, wstrlen(ws));
    AddEditControlToEditQend(eq,&ec,ma);
    
    ascii2ws(ws, LangPack::Active->data[LGP_TotalReceived]);
    PrepareEditControl(&ec);
    ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, wstrlen(ws));
    AddEditControlToEditQend(eq,&ec,ma);
    
    wsprintf_bytes(ws, Download::GlobalRx);
    PrepareEditControl(&ec);
    ConstructEditControl(&ec, ECT_READ_ONLY, ECF_APPEND_EOL, ws, wstrlen(ws));
    AddEditControlToEditQend(eq,&ec,ma);
    break;
  }
  FreeWS(ws);
  if (mode == DownloadInfo)
    patch_header(&info_hdr, &IconPack::Active->data[IMG_GetInfo], (int)LangPack::Active->data[LGP_Info]);
  if (mode == TrafficInfo)
    patch_header(&info_hdr, &IconPack::Active->data[IMG_Traffic], (int)LangPack::Active->data[LGP_Traffic]);
  patch_input(&info_desc);
  info_sk[0].lgp_id=(int)LangPack::Active->data[LGP_Cancel];
  gui_id=CreateInputTextDialog(&info_desc, &info_hdr, eq, 1, this); 
}

