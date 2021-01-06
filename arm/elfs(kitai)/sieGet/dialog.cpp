/*******************************************************************************
                                  SieGetDialog
*******************************************************************************/

#include "include.h"
#include "dialog.h"
#include "daemon.h"
#include "../inc/xtask_ipc.h"

char xtask_ipc_name[]= IPC_XTASK_NAME;

extern char sieget_ipc_name[];

SieGetDialog * SieGetDialog::Active = NULL;

void SieGetDialog::onCreate()
{
  Active = this;
  SetName(DIALOG_CSM_NAME);
  list->Show();
}

void SieGetDialog::Show(char * _url)
{
  if (!csm_id) Create();
  else // Иначе посылаем сообщение в XTask для получения диалогом фокуса
  {
    Xipc.name_to = xtask_ipc_name;
    Xipc.name_from = sieget_ipc_name;
    Xipc.data = (void *)csm_id;
    GBS_SendMessage(MMI_CEPID, MSG_IPC, IPC_XTASK_SHOW_CSM, &Xipc);
  }
  if (_url)
  {
    _safe_delete(url);
    url = new char[strlen(_url) + 1];
    strcpy(url, _url);
  }
}

int SieGetDialog::onMessage(GBS_MSG * msg)
{
  if (msg->msg==MSG_GUI_DESTROYED && (int)msg->data0==list->gui_id)
  {
    data->state=-3;
    list->gui_id = NULL;
    Close();
  }
  if (msg->msg==MSG_IPC )
  {
    IPC_REQ *ipc;
    if (ipc = (IPC_REQ *)msg->data0)
      // Обработка IPC сообщений
      if(stricmp(ipc->name_to, sieget_ipc_name)==0)
        ProcessIPC(ipc->name_from, msg->submess, ipc->data);
  }
  if (url)
  {
    URLInput * ui = new URLInput;
    ui->Show(url);
    delete url;
    url = NULL;
  }
  return CSM_MSG_RESULT_CONTINUE;
}

void SieGetDialog::ProcessIPC(const char * from, int submsg, void * data)
{
  switch(submsg)
  {
  case IPC_REFRESH_LIST:
    if (IsGuiOnTop(list->gui_id)) RefreshGUI(); // Это нужно запускать из диалога. Иначе - пикофф :(
    break;
  }
}

void SieGetDialog::RefreshList()
{
  if (!list->gui_id) return;
  if (!IsGuiOnTop(list->gui_id)) return;
  IPC_REQ ipc;
  ipc.name_to = sieget_ipc_name;
  ipc.name_from = sieget_ipc_name;
  ipc.data = NULL;
  GBS_SendMessage(MMI_CEPID, MSG_IPC, IPC_REFRESH_LIST, &ipc);
}

void SieGetDialog::onClose()
{
  Active = NULL;
}

SieGetDialog::SieGetDialog()
{
  url = NULL;
  list = new List;
}

SieGetDialog::~SieGetDialog()
{
  _safe_delete(url);
  delete list;
}

