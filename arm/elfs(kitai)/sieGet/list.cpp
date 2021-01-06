#include "include.h"
#include "gui.h"
#include "inet.h"
#include "list.h"
#include "log.h"
#include "url_input.h"
#include "dialog.h"
#include "rect_patcher.h"
#include "log_widget.h"
#include "info.h"
#include "langpack.h"
#include "iconpack.h"

List * List::Active = NULL;

SOFTKEY_DESC list_sk[]=
{
  {0x0018,0x0000,NULL},
  {0x0001,0x0000,NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB list_skt=
{
  list_sk,0
};

void list_ghook(void * data, int cmd)
{
  List * list = List::Active;
  list->gHook(data, cmd);
}

void list_itemhndl(void * data, int curitem, void * unk)
{
  List * list = List::Active;
  list->ItemHandler(data, curitem, unk);
}

int list_keyhook(void * data, GUI_MSG *msg)
{
  List * list = List::Active;
  return list->onKey(data, msg);
}

HEADER_DESC list_hdr={0,0,0,0, NULL, NULL, LGP_NULL};

const int list_softkeys[]={0,1,2};

static const ML_MENU_DESC list_desc=
{
  8, list_keyhook, list_ghook, NULL,
  list_softkeys,
  &list_skt,
  0x200+0x11,
  list_itemhndl,
  NULL,   // Items
  NULL,   // Procs
  NULL,   // n
  1       // Добавочных строк  
};

int List::onKey(void * data, GUI_MSG * msg)
{
  Download * dl;
  if(DownloadHandler::Top)
  {
    if(msg->keys==0x3D)
    {
      if(dl = DownloadHandler::Top->GetDownloadbyN(GetCurMenuItem(data)))
      {
        LogWidget * log = new LogWidget(dl->log);
        log->Create();
      }
    }
    if (msg->keys==0x18)
    {
      dl = DownloadHandler::Top->GetDownloadbyN(GetCurMenuItem(data));
      ListOptions * opt = new ListOptions;
      opt->Show(dl);
    }
    if (msg->gbsmsg->msg == KEY_DOWN)
    {
      switch(msg->gbsmsg->submess)
      {
      case GREEN_BUTTON:
        {
          URLInput * ui = new URLInput();
          ui->Show("http://");
        }
        break;
      case '#':
        if(dl = DownloadHandler::Top->GetDownloadbyN(GetCurMenuItem(data)))
        {
          unsigned int io_error;
          unlink(dl->log->filename, &io_error);
          DownloadHandler::Top->DeleteDownload(dl);
          RefreshGUI();
        }
        break;
      case '5':
        if(dl = DownloadHandler::Top->GetDownloadbyN(GetCurMenuItem(data)))
        {
          if (dl->download_state == DOWNLOAD_COMPLETE)
          {
            int len = strlen(dl->full_file_name);
            WSHDR * ws = AllocWS(len + 1);
            str_2ws(ws, dl->full_file_name, len);
            ExecuteFile(ws, 0, 0);
            FreeWS(ws);
          }
        }
        break;
      }
    }
  }
  return GUI_RESULT_OK;
}

void List::gHook(void *data, int cmd)
{
  if (cmd == TI_CMD_FOCUS)
  {
    DisableIDLETMR();
    int n = DownloadHandler::Top->GetNumOfDownloads();
    Menu_SetItemCountDyn(data, n);
  }
}

void List::wsprintf_bytes(WSHDR * ws, int bytes)
{
  if(bytes < 1024)
    wsprintf(ws, "%u b", bytes);
  if(bytes > 1024 && bytes < (1024 * 1024))
    wsprintf(ws, "%u Kb", bytes/1024);
  if(bytes > (1024 * 1024))
    wsprintf(ws, "%u Mb", bytes/1024/1024);
}

void List::wsprintf_bytes(WSHDR * ws, int bytes1, int bytes2)
{
  if(bytes2 < 1024)
    wsprintf(ws, "/%u b, %d%", bytes2, bytes1 * 100 / bytes2);
  if(bytes2 > 1024 && bytes2 < (1024 * 1024))
    wsprintf(ws, "/%u Kb, %d%", bytes2/1024, bytes1 * 100 / bytes2);
  if(bytes2 > (1024 * 1024))
    wsprintf(ws, "/%u Mb, %d%", bytes2/(1024 * 1024), bytes1 * 100 / bytes2);
}

void List::ItemHandler(void * data, int curitem, void * unk)
{
  WSHDR * ws1, * ws2, * ws3;
  void * item = AllocMLMenuItem(data);
  Download * dl = DownloadHandler::Top->GetDownloadbyN(curitem);
  if(dl && dl->file_name)
  {
    ws1 = AllocMenuWS(data, strlen(dl->file_name) + 1);
    str_2ws(ws1, dl->file_name, strlen(dl->file_name));
  }
  else
  {
    ws1 = AllocMenuWS(data, 32);
    ascii2ws(ws1, "No name");
  }
  ws2 = AllocMenuWS(data, 32);
  switch(dl->download_state)
  {
  case DOWNLOAD_ERROR:
    ascii2ws(ws2, LangPack::Active->data[LGP_Error]);
    SetMenuItemIconArray(data, item, &IconPack::Active->data[IMG_Error]);
    break;
  case DOWNLOAD_CONNECT:
    ascii2ws(ws2, LangPack::Active->data[LGP_Connecting]);
    SetMenuItemIconArray(data, item, &IconPack::Active->data[IMG_Start]);
    break;
  case DOWNLOAD_GET_INFO:
    ascii2ws(ws2, LangPack::Active->data[LGP_GettingInfo]);
    SetMenuItemIconArray(data, item, &IconPack::Active->data[IMG_GetInfo]);
    break;
  case DOWNLOAD_DATA:
    if(dl->file_size)
    {
      ws3 = AllocWS(16);
      wsprintf_bytes(ws2, dl->file_loaded_size);
      wsprintf_bytes(ws3, dl->file_loaded_size, dl->file_size);
      wstrcat(ws2, ws3);
      FreeWS(ws3);
    }
    else
      wsprintf_bytes(ws2, dl->file_loaded_size);
    SetMenuItemIconArray(data, item, &IconPack::Active->data[IMG_Downloading]);
    break;
  case DOWNLOAD_COMPLETE:
    ascii2ws(ws2, LangPack::Active->data[LGP_Completed]);
    SetMenuItemIconArray(data, item, &IconPack::Active->data[IMG_Complete]);
    break;
  case DOWNLOAD_STOPPED:
    ascii2ws(ws2, LangPack::Active->data[LGP_Stopped]);
    SetMenuItemIconArray(data, item, &IconPack::Active->data[IMG_Pause]);
    break;
  default:
    ascii2ws(ws2, LangPack::Active->data[LGP_Waiting]);
    SetMenuItemIconArray(data, item, &IconPack::Active->data[IMG_Idle]);
    break;
  }
  if (dl->AcceptRangesState != ACCEPT_RANGES_UNKNOWN) // Вставляем смайл - индикатор поддержки докачки
    wsInsertChar(ws2, dl->AcceptRangesState == ACCEPT_RANGES_OK?LGP_SMILE_OK:LGP_SMILE_NO, 1);
  SetMLMenuItemText(data, item, ws1, ws2, curitem);
}

void List::Show()
{
  patch_header(&list_hdr, &IconPack::Active->data[IMG_Logo], (int)"SieGet");
  
  list_sk[0].lgp_id = (int)LangPack::Active->data[LGP_Options];
  list_sk[1].lgp_id = (int)LangPack::Active->data[LGP_Close];
  
  gui_id = CreateMultiLinesMenu(NULL, NULL, &list_desc, &list_hdr, NULL, DownloadHandler::Top->GetNumOfDownloads());
}

List::List()
{
  Active = this;
  gui_id = NULL;
}

List::~List()
{
}

/*******************************************************************************
  Опции
*******************************************************************************/

void list_options_new_download(GUI * data)
{
  ListOptions * list_opt = (ListOptions *)MenuGetUserPointer(data);
  URLInput * ui = new URLInput();
  ui->Show("http://");
  GeneralFunc_flag1(list_opt->gui_id, 1);
}

void list_options_start_selected(GUI * data)
{
  ListOptions * list_opt = (ListOptions *)MenuGetUserPointer(data);
  SUBPROC((void *)_start_download, list_opt->dl);
  GeneralFunc_flag1(list_opt->gui_id, 1);
}

void list_options_stop_selected(GUI * data)
{
  ListOptions * list_opt = (ListOptions *)MenuGetUserPointer(data);
  list_opt->dl->StopDownload();
  GeneralFunc_flag1(list_opt->gui_id, 1);
}

void list_options_info_selected(GUI * data)
{
  ListOptions * list_opt = (ListOptions *)MenuGetUserPointer(data);
  Info * inf = new Info;
  inf->Show(list_opt->dl, Info::DownloadInfo);
  GeneralFunc_flag1(list_opt->gui_id, 1);
}

void list_options_traffic_selected(GUI * data)
{
  ListOptions * list_opt = (ListOptions *)MenuGetUserPointer(data);
  Info * inf = new Info;
  inf->Show(list_opt->dl, Info::TrafficInfo);
  GeneralFunc_flag1(list_opt->gui_id, 1);
}

void list_options_delete_selected(GUI * data)
{
  unsigned int io_error;
  
  ListOptions * list_opt = (ListOptions *)MenuGetUserPointer(data);

  unlink(list_opt->dl->log->filename, &io_error);
  DownloadHandler::Top->DeleteDownload(list_opt->dl);
  GeneralFunc_flag1(list_opt->gui_id, 1);
}

void list_options_delete_successfull(GUI * data)
{
  unsigned int io_error;
  
  ListOptions * list_opt = (ListOptions *)MenuGetUserPointer(data);
  while(Download * complete_download = DownloadHandler::Top->GetDownloadByState(DOWNLOAD_COMPLETE))
  {
    unlink(complete_download->log->filename, &io_error);
    DownloadHandler::Top->DeleteDownload(complete_download);
  }
  GeneralFunc_flag1(list_opt->gui_id, 1);
}

void list_options_edit_config(GUI * data)
{
  extern const char * successed_config_filename;
  int len = strlen(successed_config_filename);
  
  ListOptions * list_opt = (ListOptions *)MenuGetUserPointer(data);
  
  WSHDR * ws = AllocWS(len);
  str_2ws(ws, successed_config_filename, len);
  ExecuteFile(ws, 0, 0);
  FreeWS(ws);
  
  GeneralFunc_flag1(list_opt->gui_id, 1);
}

void list_options_show_about(GUI * data)
{
  ListOptions * list_opt = (ListOptions *)MenuGetUserPointer(data);
  ShowMSG(2, (int)LG_COPYRIGHT);
  GeneralFunc_flag1(list_opt->gui_id, 1);
}

extern const char *successed_config_filename;
  
  
SOFTKEY_DESC list_options_sk[]=
{
  {0x0018,0x0000,NULL},
  {0x0001,0x0000,NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB list_options_skt=
{
  list_options_sk,0
};

#define LIST_OPTIONS_ITEMS_N 9
HEADER_DESC list_options_hdr={0,0,0,0,NULL,NULL,LGP_NULL};

MENUITEM_DESC list_options_items[LIST_OPTIONS_ITEMS_N]=
{
  {NULL, NULL, LGP_NULL, NULL, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL, NULL, LGP_NULL, NULL, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL, NULL, LGP_NULL, NULL, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL, NULL, LGP_NULL, NULL, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL, NULL, LGP_NULL, NULL, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL, NULL, LGP_NULL, NULL, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL, NULL, LGP_NULL, NULL, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL, NULL, LGP_NULL, NULL, NULL, MENU_FLAG3, MENU_FLAG2},
};

const MENUPROCS_DESC list_options_procs[LIST_OPTIONS_ITEMS_N]=
{
  list_options_new_download,
  list_options_start_selected,
  list_options_stop_selected,
  list_options_info_selected,
  list_options_traffic_selected,
  list_options_delete_selected,
  list_options_delete_successfull,
  list_options_edit_config,
  list_options_show_about
};

void list_options_ghook(void * data, int cmd)
{
  ListOptions * list_opt = (ListOptions *)MenuGetUserPointer(data);
  list_opt->gHook(data, cmd);
}

const int list_options_softkeys[]={0,1,2};

MENU_DESC list_options_desc=
{
  8, NULL, list_options_ghook,NULL,
  list_options_softkeys,
  &list_options_skt,
  0x11,
  NULL,
  list_options_items,   //Items
  list_options_procs,   //Procs
  LIST_OPTIONS_ITEMS_N //n
};

void ListOptions::gHook(void * data, int cmd)
{
  if (cmd == TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
  if (cmd == TI_CMD_DESTROY)
  {
    delete this;
  }
}

void ListOptions::Show(Download * _dl)
{
  int to_remove[LIST_OPTIONS_ITEMS_N+1];
  int n = NULL;
  
  this->dl = _dl;
  
  patch_header_small(&list_options_hdr);
  
  if(!dl) // Закачек нет
  {
    to_remove[++n] = 1; // Не показываем пункт "Старт"
    to_remove[++n] = 2; // Не показываем пункт "Стоп"
    to_remove[++n] = 3; // Не показываем пункт "Свойства"
    to_remove[++n] = 5; // Не показываем пункт "Удалить"
    to_remove[++n] = 6; // Не показываем пункт "Удалить успешные"
  }
  else // Что-то все таки есть
  {
    if (ACTIVE_DOWNLOAD_STATE(dl->download_state))
      to_remove[++n] = 1;
    else
      to_remove[++n] = 2;
    if(!DownloadHandler::Top->GetNumOfDownloadsByState(DOWNLOAD_COMPLETE))
      to_remove[++n] = 6; // Не показываем пункт "Удалить успешные"
  }
  
  to_remove[0] = n;
  if (n == LIST_OPTIONS_ITEMS_N) return;
  
  list_options_items[0].icon = &IconPack::Active->data[IMG_New];
  list_options_items[1].icon = &IconPack::Active->data[IMG_Start];
  list_options_items[2].icon = &IconPack::Active->data[IMG_Pause];
  list_options_items[3].icon = &IconPack::Active->data[IMG_GetInfo];
  list_options_items[4].icon = &IconPack::Active->data[IMG_Traffic];
  list_options_items[5].icon = &IconPack::Active->data[IMG_Delete];
  list_options_items[6].icon = &IconPack::Active->data[IMG_DeleteSuccesful];
  list_options_items[7].icon = &IconPack::Active->data[IMG_Settings];
  list_options_items[8].icon = &IconPack::Active->data[IMG_About];
  
  list_options_items[0].lgp_id_small = (int)LangPack::Active->data[LGP_NewDownload];
  list_options_items[1].lgp_id_small = (int)LangPack::Active->data[LGP_StartDownload];
  list_options_items[2].lgp_id_small = (int)LangPack::Active->data[LGP_PauseDownload];
  list_options_items[3].lgp_id_small = (int)LangPack::Active->data[LGP_Info];
  list_options_items[4].lgp_id_small = (int)LangPack::Active->data[LGP_Traffic];
  list_options_items[5].lgp_id_small = (int)LangPack::Active->data[LGP_DeleteDownload];
  list_options_items[6].lgp_id_small = (int)LangPack::Active->data[LGP_DeleteSuccesfulDownload];
  list_options_items[7].lgp_id_small = (int)LangPack::Active->data[LGP_Settings];
  list_options_items[8].lgp_id_small = (int)LangPack::Active->data[LGP_About];
  
  list_options_sk[0].lgp_id = (int)LangPack::Active->data[LGP_Select];
  list_options_sk[1].lgp_id = (int)LangPack::Active->data[LGP_Back];
  
  list_options_hdr.lgp_id = (int)LangPack::Active->data[LGP_Options];
  
  gui_id = CreateMenu(1, 0, &list_options_desc, &list_options_hdr, 0, LIST_OPTIONS_ITEMS_N, this, to_remove);
}

ListOptions::ListOptions()
{
  dl = NULL;
}

ListOptions::~ListOptions()
{
}
