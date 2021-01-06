#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"
#include "IdleLinks.h"

extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

CSM_DESC icsmd;

int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);

typedef struct
{
  int x, y, Type;
  char *Pic, *FileName;
}TLabelData;

TLabelData LabelData[15];

int CalcPic(char* picture)
{
  int pic = strtoul(picture, 0, 10);
  if ( (pic <= 4) && (strlen(picture) > 1) )
  {
     pic = (int)picture;
  }
  return pic;
}

unsigned short maincsm_name_body[140];
const int minus11=-11;

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

int pos;

void OnRedraw(MAIN_GUI *data) // OnRedraw
{
  void *canvasdata = BuildCanvas();
  int i=0;
  int pic;
  do
    {
     pic = CalcPic(LabelData[i].Pic);           
      if (!vybor)
        {                
          DrawCanvas(canvasdata,LabelData[i].x-1, LabelData[i].y-1,
                                LabelData[i].x+GetImgWidth(pic)+1,
                                LabelData[i].y+GetImgHeight(pic)+1, 1);
        
          if (i==pos-1)
            {
              DrawRoundedFrame(LabelData[pos-1].x-1, LabelData[pos-1].y-1,
                               LabelData[pos-1].x+GetImgWidth(pic)+1,
                               LabelData[pos-1].y+GetImgHeight(pic)+1,0,0,0,frcol,cl);                      
            }
        }
          else
            DrawCanvas(canvasdata,LabelData[i].x-1, LabelData[i].y-1,
                                  LabelData[i].x+GetImgWidth(pic)+1,
                                  LabelData[i].y+GetImgHeight(pic)+1, 1);  
      
      DrawImg(LabelData[i].x,LabelData[i].y,pic);    
      i++;
    }
  while (i<=count);

  if (vybor==1)
    {
      pic = CalcPic(LabelData[pos-1].Pic); 
      DrawImg(LabelData[pos-1].x+GetImgWidth(pic)-GetImgWidth((int)chpic),
              LabelData[pos-1].y+GetImgHeight(pic)-GetImgHeight((int)chpic),(int)chpic);            
    }
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  // Тут можно создать переменные
  data->gui.state=1;
  pos=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
  // Тут можно освободить выделяемую память
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  DirectRedrawGUI();  
  
  if (msg->gbsmsg->msg==KEY_DOWN)
  {          
    switch(msg->gbsmsg->submess)
    {
#ifdef NEWSGOLD
    case RIGHT_SOFT:      
#else
    case RED_BUTTON:
#endif
      return(1);
    case RIGHT_BUTTON:
      {
        pos+=1;
        if (pos==(count+2)) pos=1;
      }
        break;
     case LEFT_BUTTON:
       {
          pos-=1;
          if (pos==0) pos=count+1;
       }
        break;        
    case ENTER_BUTTON:
      {
        switch (LabelData[pos-1].Type)
        {
        case 0:
          {
            WSHDR *elfname=AllocWS(256);
            wsprintf(elfname,LabelData[pos-1].FileName);
            ExecuteFile(elfname,NULL,NULL);
            FreeWS(elfname);
          }
          break;
        case 1:
          {
            unsigned int* addr = (unsigned int*)GetFunctionPointer(LabelData[pos-1].FileName);
            if (addr)
            {
              typedef void (*voidfunc)(); 
      #ifdef NEWSGOLD          
              voidfunc pp=(voidfunc)*(addr+4);
      #else 
              voidfunc pp=(voidfunc)addr; 
      #endif 
              SUBPROC((void*)pp);
            }
          }
          break;
        case 2:
          {
              typedef void (*voidfunc)(); 
              unsigned int addr=strtoul( LabelData[pos-1].FileName, 0, 16 );
              voidfunc pp=(voidfunc)addr;
              SUBPROC((void*)pp);
          }
          break;          
        }   
        return(1);
      }
    }
  }
  return(0);
}

int method8(void){return(0);}

int method9(void){return(0);}

extern void kill_data(void *p,void (*func_p)(void *));
void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

// Массив с методами, чтобы дать ОС информацию, какие когда вызывать
const void * const gui_methods[11]={
  (void *)OnRedraw,	//Redraw
  (void *)onCreate,	//Create
  (void *)onClose,	//Close
  (void *)onFocus,	//Focus
  (void *)onUnfocus,	//Unfocus
  (void *)OnKey,	//OnKey
  0,
  (void *)kill_data,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

// Канвас для основного GUI
const RECT Canvas={0,0,0,0};

// Вызывается при создании главного CSM. В данном примере
// создаётся GUI, его ID записывается в MAINGUI_ID
// на всякий случай - вдруг понадобится ;)

#pragma inline
void patch_rect(const RECT*rcc,int x,int y, int x2, int y2)
{
  RECT *rc=(RECT *)rcc;
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  //main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  InitConfig();
}

// Вызывается при закрытии главного CSM. Тут и вызывается киллер
void maincsm_onclose(CSM_RAM *csm)
{
  //SUBPROC((void *)ElfKiller);
}

// Обработчик событий главного CSM
int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
   if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  } 
  return(1); 
}

// Инициализация структуры MAINCSM
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

// Функция, которая устанавливает название этого CSM для X-Task.
void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"IdleLinks");
}


void MyIDLECSM_onClose(CSM_RAM *data)
{
  extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  extern void *ELF_BEGIN;
  seqkill(data,old_icsm_onClose,&ELF_BEGIN,SEQKILLER_ADR());
}

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

int MyIDLECSM_onMessage(CSM_RAM* data, GBS_MSG* msg)
{
  int csm_result;
  csm_result=old_icsm_onMessage(data,msg);
  
  if(msg->msg == MSG_RECONFIGURE_REQ) // Перечитывание конфига по сообщению
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      void RereadSettings(void);
      RereadSettings();
      ShowMSG(1,(int)"IdleLinks config updated!");
    }
  }

  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if ((IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))&&(active)&&(!IsScreenSaver()))
  {
  int i=0;
  int pic;
  do
  {
    pic = CalcPic(LabelData[i].Pic); 
    DrawImg(LabelData[i].x,LabelData[i].y,pic);    
    i++;
  }
  while (i<=count);  
  }
  
  return(csm_result);
}  

int my_keyhook(int key, int m)
{
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if ((IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))&&IsUnlocked()&&(m==KEY_DOWN)&&(active)&&(!IsScreenSaver()))
     if (key==CALL_BTN) 
       {
         LockSched();
         char dummy[sizeof(MAIN_CSM)];
         UpdateCSMname();
         CreateCSM(&MAINCSM.maincsm,dummy,2);
         UnlockSched();
       }
  
  return 0;
}

void RereadSettings(void)
{
  InitConfig();
  
  LabelData[0].Type=type1;
  LabelData[1].Type=type2;
  LabelData[2].Type=type3;
  LabelData[3].Type=type4;
  LabelData[4].Type=type5;
  LabelData[5].Type=type6;
  LabelData[6].Type=type7;
  LabelData[7].Type=type8;
  LabelData[8].Type=type9;
  LabelData[9].Type=type10;
  LabelData[10].Type=type11;
  LabelData[11].Type=type12;
  LabelData[12].Type=type13;
  LabelData[13].Type=type14;
  LabelData[14].Type=type15;
  
  LabelData[0].x=x1;   LabelData[0].y=y1;    LabelData[0].Pic=(char*)pic1;   LabelData[0].FileName=(char*)file1;
  LabelData[1].x=x2;   LabelData[1].y=y2;    LabelData[1].Pic=(char*)pic2;   LabelData[1].FileName=(char*)file2;
  LabelData[2].x=x3;   LabelData[2].y=y3;    LabelData[2].Pic=(char*)pic3;   LabelData[2].FileName=(char*)file3;
  LabelData[3].x=x4;   LabelData[3].y=y4;    LabelData[3].Pic=(char*)pic4;   LabelData[3].FileName=(char*)file4;
  LabelData[4].x=x5;   LabelData[4].y=y5;    LabelData[4].Pic=(char*)pic5;   LabelData[4].FileName=(char*)file5;
  LabelData[5].x=x6;   LabelData[5].y=y6;    LabelData[5].Pic=(char*)pic6;   LabelData[5].FileName=(char*)file6;
  LabelData[6].x=x7;   LabelData[6].y=y7;    LabelData[6].Pic=(char*)pic7;   LabelData[6].FileName=(char*)file7;
  LabelData[7].x=x8;   LabelData[7].y=y8;    LabelData[7].Pic=(char*)pic8;   LabelData[7].FileName=(char*)file8;
  LabelData[8].x=x9;   LabelData[8].y=y9;    LabelData[8].Pic=(char*)pic9;   LabelData[8].FileName=(char*)file9;
  LabelData[9].x=x10;  LabelData[9].y=y10;   LabelData[9].Pic=(char*)pic10;  LabelData[9].FileName=(char*)file10;
  LabelData[10].x=x11; LabelData[10].y=y11;  LabelData[10].Pic=(char*)pic11; LabelData[10].FileName=(char*)file11;
  LabelData[11].x=x12; LabelData[11].y=y12;  LabelData[11].Pic=(char*)pic12; LabelData[11].FileName=(char*)file12;
  LabelData[12].x=x13; LabelData[12].y=y13;  LabelData[12].Pic=(char*)pic13; LabelData[12].FileName=(char*)file13;
  LabelData[13].x=x14; LabelData[13].y=y14;  LabelData[13].Pic=(char*)pic14; LabelData[13].FileName=(char*)file14;
  LabelData[14].x=x15; LabelData[14].y=y15;  LabelData[14].Pic=(char*)pic15; LabelData[14].FileName=(char*)file15;  
}

// Основная процедура. Она первой получает управление при старте эльфа.
int main(void)
{
  LockSched();
  RereadSettings();
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  memcpy(&icsmd,icsm->constr,sizeof(icsmd));
  old_icsm_onMessage=icsmd.onMessage;
  icsmd.onMessage=MyIDLECSM_onMessage;
  old_icsm_onClose=icsmd.onClose;
  icsmd.onClose=MyIDLECSM_onClose;  
  icsm->constr=&icsmd;  
  
  #ifdef NEWSGOLD
      AddKeybMsgHook((void *)my_keyhook);
  #else
      if (!AddKeybMsgHook_end((void *)my_keyhook)) ShowMSG(1, (int) "IdleLinks. Невозможно зарегистрировать обработчик!"); 
  #endif
  UnlockSched();
  
  return 0;
}
