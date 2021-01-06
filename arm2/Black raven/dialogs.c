WSHDR *ws_info;
#include "main.h"
//#include "debug.c"
const char percent_t[]="%t";
const char percent_d[]="%d";
const char percent_s[]="%s";
const char percent_ss[]="%s%s";
const char percent_td[]="%t%d";
const char percent_x[]="%x";
const char percent_dd[]="%05d";

int type1 = 0;

int EditcontrolOnKey(GUI *data, GUI_MSG *msg)
{
  DisableIconBar(1); //долбаный иконбар)
  WSHDR *ws;
  ws = AllocWS(32);
  EDITCONTROL ec;
  char tmpstr[32];
  if (msg->keys==0xFFF || msg->keys == 0x18)
  {
    switch (type1)
    {
      case 2:
        {
          ExtractEditControl(data,1,&ec);
          wstrcpy(ws,ec.pWS);
          ws_2str(ws, tmpstr, 32);
          int unit = 0;
          sscanf(tmpstr, percent_d, &unit);
          writeinit(unit, 1);
          break;
        }
      case 3:
        {
          ExtractEditControl(data,1,&ec);
          wstrcpy(ws,ec.pWS);
          ws_2str(ws, tmpstr, 32);
          int unit = 0;
          sscanf(tmpstr, percent_d, &unit);
          writeinit(unit, 2);
          break;
        }
        case 4:
        {
          char xmap[32];
          char ymap[32];
          int x1 = 0, y1 = 0;
          ExtractEditControl(data,2,&ec);
          wstrcpy(ws,ec.pWS);
          ws_2str(ws, xmap, 32);
          sscanf(xmap, percent_d, &x1);
          CutWSTR(ws, 0);
          ExtractEditControl(data,4,&ec);
          wstrcpy(ws,ec.pWS);
          ws_2str(ws, ymap, 32);
          sscanf(ymap, percent_d, &y1);
          if(x1 > 200) x1 = 200;
          if(y1 > 200) y1 = 200;
          changeSize(x1, y1);
          break;
        }        
      case 1:
      default:
        {
          ExtractEditControl(data,1,&ec);
       
          wstrcpy(ws,ec.pWS);
          ws_2str(ws, tmpstr, 32);
          writemap(tmpstr);
          break;
        }
    }
    if(ws) FreeWS(ws);
    return 1;
  }
  
  return(0); // Возвращаем стандартные кнопки

}

void EditcontrolGHook(GUI *data, int cmd)
{
  //EDITCONTROL ec;
  static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)"OK"};
  if(cmd==0xA)
  {
    DisableIDLETMR();   // Отключаем таймер выхода по таймауту
  }
  if(cmd==0x03)     // При закрытии меню
  {
    FreeWS(ws_info);
    ws_info = NULL;
  }
  if (cmd==7)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
  }
}

void edchat_locret(void){}

SOFTKEY_DESC fmenu_sk[]=
{
  {0x0018,0x0000,(int)"Выбор"},
  {0x0001,0x0000,(int)"Закрыть"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB fmenu_skt=
{
  fmenu_sk,0
};

INPUTDIA_DESC EditcontrolStruct=
{
  1,
  EditcontrolOnKey,
  EditcontrolGHook,
  (void *)edchat_locret,
  0,
  &fmenu_skt,
  {2,22,239,300},
  4, 100, 101, 0, 0,
  0x40000000// Поменять софт-кнопки
};

HEADER_DESC FilenameHeader={0,0,0,0,NULL,(int)"Имя файла",LGP_NULL};
HEADER_DESC GoldHeader={0,0,0,0,NULL,(int)"Золото",LGP_NULL};
HEADER_DESC WoodHeader={0,0,0,0,NULL,(int)"Лес",LGP_NULL};
HEADER_DESC SizeHeader={0,0,0,0,NULL,(int)"Размер карты",LGP_NULL};

void DoEditcontrol(int type, char *deftext, char *def2)
{
  type1 = type;
  char *text = malloc(256);
  ws_info = AllocWS(256);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  switch (type)
  {
    case 2:
      {
        // Золото
        wsprintf(ws_info, percent_s,deftext);
        ConstructEditControl(&ec,2,0x40,ws_info,6); // 1
        AddEditControlToEditQend(eq,&ec,ma);
        patch_header(&GoldHeader);
        patch_input(&EditcontrolStruct);
        CreateInputTextDialog(&EditcontrolStruct,&GoldHeader,eq,1,0);
        break;
      }
    case 3:
      {
        // Лес
        wsprintf(ws_info, percent_s,deftext);
        ConstructEditControl(&ec,2,0x40,ws_info,6); // 1
        AddEditControlToEditQend(eq,&ec,ma);
        patch_header(&WoodHeader);
        patch_input(&EditcontrolStruct);
        CreateInputTextDialog(&EditcontrolStruct,&WoodHeader,eq,1,0);
        break;
      }
    case 4:
      {
        // Размер карты
        wsprintf(ws_info, percent_t,"Ширина: ");
        ConstructEditControl(&ec,1,0x00,ws_info,256); // 1 
        AddEditControlToEditQend(eq,&ec,ma); 

        CutWSTR(ws_info,0);
        wsprintf(ws_info, percent_s,deftext);
        ConstructEditControl(&ec,2,0x40,ws_info,3); // 2
        AddEditControlToEditQend(eq,&ec,ma);
        
        wsprintf(ws_info, percent_t,"Высота: ");
        ConstructEditControl(&ec,1,0x00,ws_info,256); // 3 
        AddEditControlToEditQend(eq,&ec,ma); 

        CutWSTR(ws_info,0);
        wsprintf(ws_info, percent_s,def2);
        ConstructEditControl(&ec,2,0x40,ws_info,3); // 4
        AddEditControlToEditQend(eq,&ec,ma);
        
        patch_header(&SizeHeader);
        patch_input(&EditcontrolStruct);
        CreateInputTextDialog(&EditcontrolStruct,&SizeHeader,eq,1,0);
        break;
      }
    case 1:
    default:
      {
        // Имя файла
        wsprintf(ws_info, percent_s,deftext);
        ConstructEditControl(&ec,3,0x40,ws_info,256); // 1
        AddEditControlToEditQend(eq,&ec,ma);
        patch_header(&FilenameHeader);
        patch_input(&EditcontrolStruct);
        CreateInputTextDialog(&EditcontrolStruct,&FilenameHeader,eq,1,0);
        break;
      }
  }
}
