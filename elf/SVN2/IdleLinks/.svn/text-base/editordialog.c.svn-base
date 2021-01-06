#include "..\inc\swilib.h"
#include "main.h"
#include "utils.h"
#include "conf_ex.h"

char *firstname;

////////////////////////////////////////////////////////////////////////////////
// Диалог создания / переименования ярлычка ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

typedef struct
{
  int ext;
  int small_png;
  int large_png;
  int elf;
  int altelf;
}ES;

HEADER_DESC dialogforneworrename_hdr={0,0,0,0,NULL,(int)"Edit",LGP_NULL};

void dialogforneworrename_locret(void){}

extern int b_rename;

int dialogforneworrename_onkey(GUI *data, GUI_MSG *msg)
{
  if (msg->keys==0x04) // Кнопочка ОК
  {
    EDITCONTROL ec;
    char * tmp_name;
    ExtractEditControl(data, 2, &ec);
    if(ec.pWS->wsbody[0])
    {
      tmp_name = (char *)malloc(ec.maxlen);
      ws_2str(ec.pWS, tmp_name, ec.maxlen);
      if(!b_rename)
      {
        // Создание ярлыка
        CreateNewBcfg(tmp_name);
        mfree(tmp_name);
        return 1;
      }
      else
      {
        // Переименование  
        RenameBcfg(firstname, tmp_name);
        mfree(tmp_name);
        return 1;
      }
    }
    else
    {
      ShowMSG(1, (int)"Name of link not be empty!");
      return 0;
    }
  }
  return 0;
}

void dialogforneworrename_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC sk={0x04,0x01,(int)"OK"};
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
  if (cmd==7)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
  }
}

extern SOFTKEYSTAB menu_linkslist_skt;
INPUTDIA_DESC dealogforneworrename_desc =
{
  1,
  dialogforneworrename_onkey,
  dialogforneworrename_ghook,
  (void *)dialogforneworrename_locret,
  0,
  &menu_linkslist_skt,
  {0,0,0,0},
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

void CreateDialogForNewOrRenameLink(void *menugui, int index, char *curname)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  int ect_type;
  
  eq=AllocEQueue(ma,mfree_adr());   
  WSHDR *ews=AllocWS(128);
  wsprintf(ews,"%t","Name of link:");  
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_HEADER,0x40,ews,ews->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);    
  
  CutWSTR(ews,strlen(curname));

  str_2ws(ews, curname, strlen(curname));
  ect_type=ECT_NORMAL_TEXT;
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ect_type,0x40,ews,128);
  AddEditControlToEditQend(eq,&ec,ma);   
  patch_header(&dialogforneworrename_hdr);
  patch_input(&dealogforneworrename_desc);
  CreateInputTextDialog(&dealogforneworrename_desc,&dialogforneworrename_hdr,eq,1,NULL);  
  
  firstname = curname;
}
