#include "..\inc\swilib.h"
#include "main.h"
#include "clist_util.h"
#include "jabber_util.h"
#include "string_util.h"
#include "xml_parser.h"
#include "item_info.h"
#include "lang.h"
#include "rect_patcher.h"

#define MAX_SYMB 1024
WSHDR* ws_info = NULL;

extern const char KNOW_FEATURES_PATH[];
int info_onkey(GUI *gui, GUI_MSG *msg)
{
  if (msg->keys==0x18)
  {
    return(-1); //do redraw
  }
  return(0); //Do standart keys

}

void info_ghook(GUI *gui, int cmd)
{
  if (cmd==TI_CMD_CREATE)
  {
    //Called after onCreate
  }

  if (cmd==TI_CMD_REDRAW)
  {

  }

  if(cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();   // Отключаем таймер выхода по таймауту
  }

  if(cmd==TI_CMD_DESTROY)     // onDestroy
  {
    FreeWS(ws_info);
    ws_info = NULL;
  }
}

extern void inp_locret(void);
extern const char percent_s[];
extern const char* PRESENCES[PRES_COUNT];
extern const char* JABBER_AFFS[];
extern const char* JABBER_ROLS[];

SOFTKEY_DESC info_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB info_skt=
{
  info_sk,0
};

INPUTDIA_DESC info_desc=
{
  1,
  info_onkey,
  info_ghook,
  (void *)inp_locret,
  0,
  &info_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0x40000000// Поменять софт-кнопки
};

HEADER_DESC info_hdr={0,0,0,0,NULL,(int)LG_ITEMIHDR,LGP_NULL};


// Показ информации о контакте
void Disp_Info(TRESOURCE* ResEx)
{

  // Сначала получим инфу о том, на какой контакт это всё приходится
  CLIST* ClEx = CList_FindContactByJID(ResEx->full_name);

  // Теперь выполним приготовление самого диалога ввода
  ws_info = AllocWS(MAX_SYMB);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());

  // Маленькая хитрость - пустой элемент, принимающий фокус ввода, в начале списка
  wsprintf(ws_info,"");
  ConstructEditControl(&ec,ECT_READ_ONLY,ECF_NORMAL_STR,ws_info,256);
  AddEditControlToEditQend(eq,&ec,ma);

  // Создаём поля
  /*
  T_NORMAL,       // Обычный (просто ресурс)
  T_VIRTUAL,      // Создаётся при создании контакта, для удаления
  T_CONF_ROOT,    // Корень конференции (место доставки публичных сообщений)
  T_CONF_NODE,    // Участник конференции (отображаем только "ресурс" жида)
  T_TRANSPORT,    // Транспортный агент
  T_GROUP         // Элемент "группа"
  */
  if(ResEx->entry_type==T_NORMAL)   ascii2ws(ws_info, LG_ELROSTER);
  if(ResEx->entry_type==T_VIRTUAL)  ascii2ws(ws_info, LG_OFFLORCONTTR);
  if(ResEx->entry_type==T_CONF_ROOT)ascii2ws(ws_info, LG_MUC);
  if(ResEx->entry_type==T_CONF_NODE)ascii2ws(ws_info, LG_MUCPART);
  if(ResEx->entry_type==T_TRANSPORT)ascii2ws(ws_info, LG_JTRANSP);
  if(ResEx->entry_type==T_GROUP)    ascii2ws(ws_info, LG_GROUPROSTER);

  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,256);
  AddEditControlToEditQend(eq,&ec,ma);

  //  if(ResEx->entry_type==T_NORMAL || ResEx->entry_type==T_VIRTUAL || ResEx->entry_type==T_CONF_ROOT || ResEx->entry_type==T_TRANSPORT)
  if(ResEx->entry_type!=T_GROUP&& ResEx->entry_type!=T_CONF_NODE)
  {
    // JID
    ascii2ws(ws_info, "JID:");
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,256);
    AddEditControlToEditQend(eq,&ec,ma);

    utf8_2ws(ws_info, ClEx->JID, 128);
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,256);
    AddEditControlToEditQend(eq,&ec,ma);
  }

  if(ResEx->entry_type==T_CONF_ROOT)
  {
    // тема конфы
    MUC_ITEM* TmpMUC= CList_FindMUCByJID(ClEx->JID);
    if(TmpMUC)
    {
      if(TmpMUC->muctema)
      {
        ascii2ws(ws_info, LG_MUCSABJECT);
        ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,256);
        AddEditControlToEditQend(eq,&ec,ma);
        utf8_2ws(ws_info, TmpMUC->muctema, strlen(TmpMUC->muctema)*2);
        ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,wstrlen(ws_info));
        AddEditControlToEditQend(eq,&ec,ma);
      }
    }
  }
  if(ResEx->entry_type==T_CONF_NODE)
  {
    // nick
    ascii2ws(ws_info, LG_NICK);
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,256);
    AddEditControlToEditQend(eq,&ec,ma);

    utf8_2ws(ws_info, ResEx->name, 128);
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,256);
    AddEditControlToEditQend(eq,&ec,ma);
  }

  if((ResEx->entry_type==T_NORMAL || ResEx->entry_type==T_VIRTUAL)&&(ResEx->name))
  {
    // Ресурс
    ascii2ws(ws_info, LG_RESOURCE);
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,256);
    AddEditControlToEditQend(eq,&ec,ma);

    utf8_2ws(ws_info, ResEx->name, 128);
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,256);
    AddEditControlToEditQend(eq,&ec,ma);

////   if (ResEx->priority != 0)
////    {
    // Приоритет
    ascii2ws(ws_info, LG_PRIORITY);
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,256);
    AddEditControlToEditQend(eq,&ec,ma);

    wsprintf(ws_info, "%i", ResEx->priority);
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,256);
    AddEditControlToEditQend(eq,&ec,ma);
////    }
  }

  //  if(ResEx->entry_type==T_NORMAL || ResEx->entry_type==T_CONF_NODE || ResEx->entry_type==T_TRANSPORT ||ResEx->entry_type==T_VIRTUAL)
  if(ResEx->entry_type!=T_GROUP && ResEx->entry_type!=T_CONF_ROOT)
  {

    if(ResEx->muc_privs.real_jid)
    {
      ascii2ws(ws_info, LG_REALJID);
      ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,256);
      AddEditControlToEditQend(eq,&ec,ma);

      utf8_2ws(ws_info, ResEx->muc_privs.real_jid, 128);
      ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,600);
      AddEditControlToEditQend(eq,&ec,ma);
    }

    // Статус и сообщение статуса
    ascii2ws(ws_info, LG_STATUS2);
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,256);
    AddEditControlToEditQend(eq,&ec,ma);
    if(ResEx->status_msg)
    {
      if(strlen(ResEx->status_msg)<512)
      {
        WSHDR *s=AllocWS(512);
        utf8_2ws(s, ResEx->status_msg, 512);
        wsprintf(ws_info,"%s: %w",PRESENCES[ResEx->status], s);
        FreeWS(s);
      }
    }
    else wsprintf(ws_info,percent_s,PRESENCES[ResEx->status]);
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,600);
    AddEditControlToEditQend(eq,&ec,ma);
  }


  if(ResEx->entry_type==T_CONF_NODE)
  {
    // Afflliation, role
    ascii2ws(ws_info, LG_PRIVILEGES);
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,256);
    AddEditControlToEditQend(eq,&ec,ma);

    wsprintf(ws_info, percent_s, JABBER_AFFS[ResEx->muc_privs.aff]);
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,256);
    AddEditControlToEditQend(eq,&ec,ma);

    ascii2ws(ws_info, LG_ROLE);
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,256);
    AddEditControlToEditQend(eq,&ec,ma);

    wsprintf(ws_info, percent_s, JABBER_ROLS[ResEx->muc_privs.role]);
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,256);
    AddEditControlToEditQend(eq,&ec,ma);
  }
  
  if ((ResEx->entry_type!=T_GROUP)&&(ResEx->entry_type!=T_CONF_NODE)&&(ResEx->entry_type!=T_CONF_ROOT))
  {    // подписка
    ascii2ws(ws_info, LG_ISUBSCRIBE);
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,256);
    AddEditControlToEditQend(eq,&ec,ma);
    switch (ClEx->subscription)
    {
    case SUB_NONE:
      {
        wsprintf(ws_info, percent_s, "NONE");
        break;
      }
    case SUB_TO:
      {
        wsprintf(ws_info, percent_s, "TO");
        break;
      }
    case SUB_FROM:
      {
        wsprintf(ws_info, percent_s, "FROM");
        break;
      }
    case SUB_BOTH:
      {
        wsprintf(ws_info, percent_s, "BOTH");
        break;
      }
    default:
      {
        wsprintf(ws_info, percent_s, "X.3.");
        break;
      }
    }

    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,256);
    AddEditControlToEditQend(eq,&ec,ma);
  }
  
  patch_header(&info_hdr);
  patch_input(&info_desc);
  CreateInputTextDialog(&info_desc,&info_hdr,eq,1,0);
}

static char *Known_Features = NULL;

extern const char DEFAULT_DISC[128];
extern const char KNOW_FEATURES_PATH[];

char *Lookup_Known_Vars(char *var_name)
{
  if(!Known_Features)
  {
    // Грузим фичи из файла
    unsigned int io_error = 0;
    char path[255];
    strcpy(path,KNOW_FEATURES_PATH);
    volatile int hF=fopen(path ,A_ReadWrite + A_BIN,P_READ + P_WRITE, &io_error);
    if(io_error) return var_name; //ненашли файл, ну и фиг с ним
    Known_Features=malloc(4096);
    zeromem(Known_Features,4096);
    fread(hF, Known_Features, 4095, &io_error);
    fclose(hF, &io_error);
  }
  char *vn = Get_Param_Value(Known_Features, var_name, 1);
  if(vn!=NULL)
  {return vn;
  }else return var_name;
}

void Disp_From_Disco(char *jid, XMLNode *info)
{

  // Сначала получим инфу о том, на какой контакт это всё приходится
  CLIST* ClEx = CList_FindContactByJID(jid);

  // Теперь выполним приготовление самого диалога ввода
  ws_info = AllocWS(MAX_SYMB);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());

  ascii2ws(ws_info, "Identity:");
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,256);
  AddEditControlToEditQend(eq,&ec,ma);

  XMLNode *nodeExI = info->subnode;
  while(nodeExI)
  {
    if(!strcmp(nodeExI->name,"identity"))
    {
      char *category = XML_Get_Attr_Value("category", nodeExI->attr);
      if(category)
      {
        utf8_2ws(ws_info, category, 128);
        ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,256);
        AddEditControlToEditQend(eq,&ec,ma);
      }
      char *type = XML_Get_Attr_Value("type", nodeExI->attr);
      if(type)
      {
        utf8_2ws(ws_info, type, 128);
        ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,256);
        AddEditControlToEditQend(eq,&ec,ma);
      }
      char *name = XML_Get_Attr_Value("name", nodeExI->attr);
      if(name)
      {
        utf8_2ws(ws_info, name, 128);
        ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,256);
        AddEditControlToEditQend(eq,&ec,ma);
      }
    }
    nodeExI = nodeExI->next;
  }        

  // JID
  ascii2ws(ws_info, "JID:");
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,256);
  AddEditControlToEditQend(eq,&ec,ma);

  utf8_2ws(ws_info, jid, 128);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,256);
  AddEditControlToEditQend(eq,&ec,ma);


  ascii2ws(ws_info, LG_POSIBLCLIENT);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_info,256);
  AddEditControlToEditQend(eq,&ec,ma);

  XMLNode *nodeEx = info->subnode;
  while(nodeEx)
  {
    if(!strcmp(nodeEx->name,"feature"))
    {
      char *var = XML_Get_Attr_Value("var", nodeEx->attr);
      if(var)
      {
        var = Lookup_Known_Vars(var);
        utf8_2ws(ws_info, var, 128);
        ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_info,256);
        AddEditControlToEditQend(eq,&ec,ma);
      }
    }
    nodeEx = nodeEx->next;
  }
  if(Known_Features)
  {
    mfree(Known_Features);
    Known_Features = NULL;
  }
  patch_header(&info_hdr);
  patch_input(&info_desc);
  CreateInputTextDialog(&info_desc,&info_hdr,eq,1,0);
}

//EOL,EOF
