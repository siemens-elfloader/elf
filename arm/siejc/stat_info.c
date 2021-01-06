#include "..\inc\swilib.h"
#include "string_util.h"
#include "stat_info.h"
#include "lang.h"
#include "main.h"

#include "rect_patcher.h"
#define MAX_SYMB 1024

WSHDR* ws_stat_info = NULL;
extern JABBER_STATE Jabber_state; 
char percent_i[]="%i";
extern unsigned int out_virt_bytes_count;
extern unsigned int out_bytes_count;
extern unsigned int in_virt_bytes_count;
extern unsigned int in_bytes_count;
extern int sendq_l;
char SW_Support_Compression=0;

int stat_info_onkey(GUI *gui, GUI_MSG *msg)
{
  if (msg->keys==0x18)
  {
    return(-1); //do redraw
  }
  return(0); //Do standart keys
}

void stat_info_ghook(GUI *gui, int cmd)
{
  if (cmd==TI_CMD_CREATE)
  {
    //Called after onCreate
  }
  if (cmd==TI_CMD_REDRAW && !EDIT_IsMarkModeActive(gui))
  {
  wsprintf(ws_stat_info,percent_i, Jabber_state);
    EDIT_SetTextToEditControl(gui, 3, ws_stat_info);

  if(!SW_Support_Compression)
  {
  wsprintf(ws_stat_info,percent_i, in_bytes_count);
    EDIT_SetTextToEditControl(gui, 5, ws_stat_info);
  wsprintf(ws_stat_info,percent_i, out_virt_bytes_count);
    EDIT_SetTextToEditControl(gui, 7, ws_stat_info);
  wsprintf(ws_stat_info,percent_i, sendq_l);
    EDIT_SetTextToEditControl(gui, 9, ws_stat_info); //9 //15
  } else
  {
  wsprintf(ws_stat_info,percent_i, in_bytes_count);
    EDIT_SetTextToEditControl(gui, 5, ws_stat_info);
  wsprintf(ws_stat_info,percent_i, out_bytes_count);
    EDIT_SetTextToEditControl(gui, 7, ws_stat_info);
  wsprintf(ws_stat_info,percent_i, (in_bytes_count*100/in_virt_bytes_count));
//      wsprintf(ws_stat_info,percent_i, (in_bytes_count));
    EDIT_SetTextToEditControl(gui, 9, ws_stat_info);
  wsprintf(ws_stat_info,percent_i, (out_bytes_count*100/out_virt_bytes_count));
//      wsprintf(ws_stat_info,percent_i, (out_bytes_count));

    EDIT_SetTextToEditControl(gui, 12, ws_stat_info);
  wsprintf(ws_stat_info,percent_i, sendq_l);
    EDIT_SetTextToEditControl(gui, 15, ws_stat_info); //9 //15    
  }
  
  }
  if(cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();   // Отключаем таймер выхода по таймауту
  }
  if(cmd==TI_CMD_DESTROY)     // onDestroy
  {
    FreeWS(ws_stat_info);
    ws_stat_info = NULL;
  }
}
extern void inp_locret(void);

SOFTKEY_DESC stat_info_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB stat_info_skt=
{
  stat_info_sk,0
};

INPUTDIA_DESC stat_info_desc=
{
  1,
  stat_info_onkey,
  stat_info_ghook,
  (void *)inp_locret,
  0,
  &stat_info_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0x40000000// Поменять софт-кнопки
};

HEADER_DESC stat_info_hdr={0,0,0,0,NULL,NULL,LGP_NULL};

void Disp_stat_Info(void)
{
  extern const int USE_ZLIB;
  extern char Support_Compression;
  // Теперь выполним приготовление самого диалога ввода
  ws_stat_info = AllocWS(MAX_SYMB);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());

  // Маленькая хитрость - пустой элемент, принимающий фокус ввода, в начале списка
  wsprintf(ws_stat_info,"");
  ConstructEditControl(&ec,ECT_READ_ONLY,ECF_NORMAL_STR,ws_stat_info,256);
  AddEditControlToEditQend(eq,&ec,ma); //1

  ascii2ws(ws_stat_info,LG_STAT_CONDITION_);
  ConstructEditControl(&ec,ECT_HEADER,ECF_NORMAL_STR,ws_stat_info,256);
  AddEditControlToEditQend(eq,&ec,ma);//2
  wsprintf(ws_stat_info,percent_i, Jabber_state);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_stat_info,256);
  AddEditControlToEditQend(eq,&ec,ma);//3

  if(!Support_Compression || !USE_ZLIB)
  {
    SW_Support_Compression = 0;

  ascii2ws(ws_stat_info,LG_STAT_TRAFINPUT_);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_stat_info,256);
  AddEditControlToEditQend(eq,&ec,ma);//4
  wsprintf(ws_stat_info,percent_i, in_bytes_count);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_stat_info,256);
  AddEditControlToEditQend(eq,&ec,ma);//5

  ascii2ws(ws_stat_info,LG_STAT_TRAFOUTPUT_);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_stat_info,256);
  AddEditControlToEditQend(eq,&ec,ma);//6
  wsprintf(ws_stat_info,percent_i, out_virt_bytes_count);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_stat_info,256);
  AddEditControlToEditQend(eq,&ec,ma);//7
  } else
  {
    SW_Support_Compression = 1;
  ascii2ws(ws_stat_info,LG_STAT_ZIPTRAFINPUT);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_stat_info,256);
  AddEditControlToEditQend(eq,&ec,ma);//-4
  wsprintf(ws_stat_info,percent_i, in_virt_bytes_count);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_stat_info,256);
  AddEditControlToEditQend(eq,&ec,ma);//-5

  ascii2ws(ws_stat_info,LG_STAT_ZIPTRAFOUTPUT);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_stat_info,256);
  AddEditControlToEditQend(eq,&ec,ma);//=6
  wsprintf(ws_stat_info,percent_i, out_bytes_count);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_stat_info,256);
  AddEditControlToEditQend(eq,&ec,ma);//-7

  ascii2ws(ws_stat_info,LG_STAT_COMPRESIONIN);
  ConstructEditControl(&ec,ECT_HEADER,ECF_NORMAL_STR,ws_stat_info,256);
  AddEditControlToEditQend(eq,&ec,ma);//8
  wsprintf(ws_stat_info,percent_i, 100-(in_bytes_count*100/in_virt_bytes_count));
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_NORMAL_STR,ws_stat_info,256);
  AddEditControlToEditQend(eq,&ec,ma);//9
  ascii2ws(ws_stat_info," [%]");
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_stat_info,256);
  AddEditControlToEditQend(eq,&ec,ma);//10

  ascii2ws(ws_stat_info,LG_STAT_COMPRESIONOUT);
  ConstructEditControl(&ec,ECT_HEADER,ECF_NORMAL_STR,ws_stat_info,256);
  AddEditControlToEditQend(eq,&ec,ma);//11
  wsprintf(ws_stat_info,percent_i, 100-(out_bytes_count*100/out_virt_bytes_count));
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_NORMAL_STR,ws_stat_info,256);
  AddEditControlToEditQend(eq,&ec,ma);//12
  ascii2ws(ws_stat_info," [%]");
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_stat_info,256);
  AddEditControlToEditQend(eq,&ec,ma);//13

  }
  ascii2ws(ws_stat_info,LG_STAT_QLENGTH);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws_stat_info,256);
  AddEditControlToEditQend(eq,&ec,ma);//8 //14
  wsprintf(ws_stat_info,percent_i, sendq_l);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws_stat_info,256);
  AddEditControlToEditQend(eq,&ec,ma); //9 //15

  stat_info_hdr.lgp_id=(int)LG_STAT_STATISTICS;
  patch_header(&stat_info_hdr);
  patch_input(&stat_info_desc);
  CreateInputTextDialog(&stat_info_desc,&stat_info_hdr,eq,1, 0);
}
//EOL,EOF

