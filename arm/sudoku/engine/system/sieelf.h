const int minus11=-11;
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

extern void START_CONTROL();
extern void CREATE_CONTROL();
extern void MAXIMIZE_CONTROL();
extern void MINIMIZE_CONTROL();
extern void END_CONTROL();
extern void REDRAW_CONTROL();
extern void MESSAGES_CONTROL();
extern int KEY_CONTROL();


//Keys
#define KEYMSG  msg->gbsmsg->msg
#define KEYSMSG msg->gbsmsg->submess
#define GKEYEND goto KEYEND
#define NEXT return(0)
#define END return(1)


//#define LG_RECONFIG  "��������!"
//#define LG_FOR_SG    "������ ����\n��� SGold!"
//#define LG_FOR_NSG   "������ ����\n��� NewSGold!"
//#define LG_FOR_ELKA  "������ ����\n��� E/EL71!"


static void OnRedraw(MAIN_GUI *data)//��� ������� ����� ��� ����������� ������,��� ������ ��� ��� ��� �����
{
 REDRAW_CONTROL();
}

static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
#ifdef ELKA
  DisableIconBar(1);
#endif
  
  CREATE_CONTROL();
  data->gui.state=1;
}

static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  END_CONTROL();
  data->gui.state=0;
}

static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//���� ��� �� ����� �� ����� �� ������ ��� �����
{
#ifdef ELKA
  DisableIconBar(1);
#endif
  
  data->gui.state=2;
  DisableIDLETMR();//��������� ������,����� ����� 2 ������ ���� ���������
  MAXIMIZE_CONTROL();
  
}

static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))//� ���� ��� �� ������,�� ����� ������� ���� ��������:)
{
  MINIMIZE_CONTROL();
  if (data->gui.state!=2) return;
  data->gui.state=1;
}


static int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  return(KEY_CONTROL(msg)); 
}



extern void kill_data(void *p, void (*func_p)(void *));//��� ������� ������� ���� � ����������� ������

int method8(void){return(0);}
int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)OnRedraw,
  (void *)onCreate,
  (void *)onClose,
  (void *)onFocus,
  (void *)onUnfocus,
  (void *)OnKey,
  0,
  (void *)kill_data,
  (void *)method8,
  (void *)method9,
  0
};

static void maincsm_oncreate(CSM_RAM *data)//���������� ��� �������� �����,������ ��� �����
{
  static const RECT Canvas={0,0,0,0};
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

void ElfKiller(void)//����������� ��� ������� ����� ������ � ���������
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}


static void maincsm_onclose(CSM_RAM *csm)//������� �������� �����,��� ����������� ������ ���� ����� � �.�.
{
  SUBPROC((void *)ElfKiller);
}


#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)//��� ������� ��������� ��� ��������� ����������� �� ����� ��� �������:)
{
  //��������� � �������������� ��������,��� � �.�. � �.�.
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  if (msg->msg==MSG_RECONFIGURE_REQ)//���� ���� ��������������,�� ��������� ��������� �����
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      //ShowMSG(1,(int)LG_RECONFIG);
      InitConfig();
    }
  }
  MESSAGES_CONTROL();

  return(1);
}


static const struct //��� ��������� ���,����������� �� ����:)
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




void UpdateCSMname(void)//�� ���������� ��� ����� ������������ ������
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),ELF_NAME);
}

int main(char *exename, char *fname)//exename-���� ������������ �����, fname �������� ������������ �����
{
#ifndef MULTISGOLD
  
  #ifdef SGOLD
  if (isnewSGold()!=0) ShowMSG(1,(int)LG_FOR_SG);
  if (isnewSGold()==0){
  #endif
  
  #ifdef NEWSGOLD
  #ifndef ELKA
  if (isnewSGold()!=1) ShowMSG(1,(int)LG_FOR_NSG);
  if (isnewSGold()==1){
  #endif
  #endif
    
  #ifdef ELKA
  if (isnewSGold()!=2) ShowMSG(1,(int)LG_FOR_ELKA);
  if (isnewSGold()==2){
  #endif
    
#endif
    
  START_CONTROL(exename, fname);

#ifndef MULTISGOLD 
  
  MAIN_CSM main_csm;
  LockSched();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);//������� ���
  UnlockSched();
  }
  
#endif
  
  return 0;
}
