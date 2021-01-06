#include "..\inc\swilib.h"
#include <stdbool.h>

int icon[]={0x58,0};
const int minus11=-11;
char oldstr[20];

char *dict=0;
int loaded_dict=0;
int dict_size=0;

const char _percent_t[]="%t";

SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Лев"},
  {0x0001,0x0000,(int)"Прав"},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

WSHDR *ews;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

void ed1_locret(void){}

int ed1_onkey(GUI *data, GUI_MSG *msg)
{
  //-1 - do redraw
  return(0); //Do standart keys
  //1: close
}

void LoadDict(int num);

void ed1_ghook(GUI *data, int cmd)
{
  EDITCONTROL ec, ec2;
  if (cmd==7)
  {
    ExtractEditControl(data,2,&ec);
    ExtractEditControl(data,4,&ec2);
    
    char word[40];
    ws_2str(ec.pWS, word, 40);
    
    if (strlen(word)!=0)
    {
      int d;
      if (word[0]<'g')
        d=1;
      else if (word[0]<'p')
        d=2;
      else
        d=3;
      
      LoadDict(d);
    
      char *pos=dict;
      bool found=false;
      while (pos<dict+dict_size)
      {
        if (!strcmp(word, pos))
        {
          pos+=strlen(pos)+1;
          found=true;
          break;
        }
        pos+=strlen(pos)+1;
      }
      if (found)
      {
        wsprintf(ec2.pWS, _percent_t, pos); 
        StoreEditControl(data ,4, &ec2);
      }
      else
      {
        wsprintf(ec2.pWS, _percent_t, "Нет вариантов"); 
        StoreEditControl(data ,4, &ec2);
      }
    }    
    else
    {
      wsprintf(ec2.pWS, _percent_t, "Введите слово для перевода"); 
      StoreEditControl(data ,4, &ec2);
    }
  }
}

HEADER_DESC ed1_hdr={0,0,131,21,NULL,(int)"En-Ru cловарь",0x7FFFFFFF};

INPUTDIA_DESC ed1_desc=
{
  1,
  ed1_onkey,
  ed1_ghook,
  (void *)ed1_locret,
  0,
  &menu_skt,
  {0,22,131,153},
  4,
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
  0
};

int create_ed(void)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;

  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());

  wsprintf(ews,"%t","Слово для перевода:");
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,"%t","");
  ConstructEditControl(&ec,3,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,"%t","Перевод:");
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,"%t","Введите слово для перевода");
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  return CreateInputTextDialog(&ed1_desc,&ed1_hdr,eq,1,0);
}

void ErrorMsg(const char *msg)
{
  LockSched();
  ShowMSG(1,(int)msg);
  UnlockSched();
}

void Killer(void)
{
  extern void *ELF_BEGIN;
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void LoadDict(int num)
{
  if (loaded_dict!=num)
  {
    int f;
    unsigned int ul;  

    if (dict != 0)
      mfree(dict);
    loaded_dict=0;

    char fname[40];
    sprintf(fname, "0:\\ZBin\\dictionary\\dict\\%d.dic", num);
  
    if ((f=fopen(fname, A_ReadOnly+A_BIN, 0, &ul))==-1)
    {
       sprintf(fname, "4:\\ZBin\\dictionary\\dict\\%d.dic", num);
       if ((f=fopen(fname, A_ReadOnly+A_BIN, 0, &ul))==-1)
       {
         ErrorMsg("Can't open .dict file!");
         return;
       }
    }
    dict_size=lseek(f,0,S_END,&ul,&ul);
    lseek(f,0,S_SET,&ul,&ul);
    if (dict_size<=0)
    {
      ErrorMsg("Zero lenght of .dict file!");
      fclose(f,&ul);
    } 
    else if ((dict=malloc(dict_size))==0)
    {
      ErrorMsg("Can't malloc!");
    }
    else if (fread(f, dict, dict_size, &ul)!=dict_size)
    {
      ErrorMsg("Can't read .dict file!");
      fclose(f, &ul);
      mfree(dict);
      dict=0;
    }
    else
      loaded_dict=num;
  fclose(f, &ul);
  }
}

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  ews=AllocWS(256);
  csm->gui_id=create_ed();
  LoadDict(3);
}

void maincsm_onclose(CSM_RAM *csm)
{
  FreeWS(ews);
  if (dict != 0)
    mfree(dict);
  SUBPROC((void *)Killer);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->gui_id)
    {
      /*if (ed1_desc._0x40000000)
      {
	ed1_desc._0x40000000<<=1;
	csm->gui_id=create_ed();
      }
      else*/
      {
	csm->csm.state=-3;
      }
    }
  }
  return(1);
}

unsigned short maincsm_name_body[140];

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"En-Ru Dictionary");
}

int main()
{
  char dummy[sizeof(MAIN_CSM)];
  LockSched();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  return 0;
}
