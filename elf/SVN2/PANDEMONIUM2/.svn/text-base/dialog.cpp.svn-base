/*******************************************************************************
                                  PandemonuimDialog
*******************************************************************************/

#include "include.h"
#include "dialog.h"
#include "conf_loader.h"

extern char *successed_config_filename;

void PandemonuimDialog::onCreate()
{
  SetName("PANDEMONIUM");
  list->Show();
}


int PandemonuimDialog::onMessage(GBS_MSG * msg)
{
  if (msg->msg==MSG_GUI_DESTROYED && (int)msg->data0==list->gui_id)
  {
    data->state=-3;
    list->gui_id = NULL;
    Close();
  }
  

  
  
  
 if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    if (stricmp(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"Pandemonuim config updated!");
      InitConfig();
    }    
  }    
  return CSM_MSG_RESULT_CONTINUE;
}

void PandemonuimDialog::onClose()
{
  
}

PandemonuimDialog::PandemonuimDialog()
{
  list = new List;
  iconpack = new IconPack();
}

PandemonuimDialog::~PandemonuimDialog()
{
  delete list;
  delete iconpack;
}

