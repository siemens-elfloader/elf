#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"
#include "IdleLinks.h"

#define DAEMON

#ifdef DAEMON
typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;
#endif

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
int MAINCSM_ID=0;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM_GUI;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

int pos;

void DoLabel()
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
        CloseCSM(MAINCSM_ID); //There GeneralFunc challenge for Tech. GUI -> close GUI
        MAINCSM_ID=0;
}

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
  WSHDR *wsBuf=AllocWS(30);
  char *p=strrchr(LabelData[pos-1].FileName, '\\');
  if( p )
    utf8_2ws(wsBuf,p+1,30);
  else
    utf8_2ws(wsBuf,LabelData[pos-1].FileName,30);
  DrawRoundedFrame(0,0,ScreenW()-1,14,0,0,0,frcol,cl);
  DrawString(wsBuf,
             0,
             2,
             ScreenW()-1,
             13,
             FONT_SMALL_BOLD,
             TEXT_ALIGNMIDDLE,
             frcol,cl);
  FreeWS(wsBuf);
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  // Ту?можн?создат?переменные
  data->gui.state=1;
  pos=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
  // Ту?можн?освободить выде?емую па?ть
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

void Bubble2Sort(int* pData, int count, int* cur, char dir) 
{
#if 0
  int i,iTemp; 
  int left = 1; 
  int right =count -1; 
  int t,t2=pData[*cur]; 
  do 
  {
    //ХэПтµДІї·Ц 
    for(i=right;i>=left;i--) 
    {
      if(dir==0 && LabelData[pData[i]-1].y < LabelData[pData[i-1]-1].y ||
         dir==1 && LabelData[pData[i]-1].x < LabelData[pData[i-1]-1].x) 
      {
        iTemp = pData[i]; 
        pData[i] = pData[i-1]; 
        pData[i-1] = iTemp; 
        t = i; 
      } 
    } 
    left = t+1; 
    //·ґПтµДІї·Ц 
    for(i=left;i<right+1;i++) 
    {
      if(dir==0 && LabelData[pData[i]-1].y < LabelData[pData[i-1]-1].y ||
         dir==1 && LabelData[pData[i]-1].x < LabelData[pData[i-1]-1].x) 
      {
        iTemp = pData[i]; 
        pData[i] = pData[i-1]; 
        pData[i-1] = iTemp; 
        t = i; 
      }
    }
    right = t-1; 
  }while(left<=right); 
  for(t=0; t<count; t++)
  {
    if(pData[t] == t2)
    {
      *cur = t;
      break;
    }
  }
#else
  int i,j,iTemp; 
  int t=pData[*cur]; 
  char exchange=1; //Ѕ»»»±кЦѕ
  for(i=1; exchange && i<count; i++) //Чо¶аЧцn-1МЛЕЕРт
  {
	  exchange=0; //±ѕМЛЕЕРтїЄКјЗ°Ј¬Ѕ»»»±кЦѕУ¦ОЄјЩ
	  for(j=count-1; j>=i; j--)
	  {
		  if(dir==0 && LabelData[pData[j]-1].y < LabelData[pData[j-1]-1].y ||
			  dir==1 && LabelData[pData[j]-1].x < LabelData[pData[j-1]-1].x)
		  {
			  iTemp = pData[j];
			  pData[j] = pData[j-1];
			  pData[j-1] = iTemp;
			  exchange = 1;
		  }
	  }
  }
  for(i=0; i<count; i++)
  {
	  if(pData[i] == t)
	  {
		  *cur = i;
		  break;
	  }
  }
#endif
}

void GetNextPos(int key)
{
  int i=0,xCount=0,yCount=0;
  int x=LabelData[pos-1].x;
  int y=LabelData[pos-1].y;
  int p1[15],p2[15],px,py,step;
  for(i=0; i<=count; i++)
  {
    if(LabelData[i].x+3 >= x && LabelData[i].x <= x+3)
    {
      if(pos == i+1)
        py = yCount;
      p1[yCount++] = i+1;
    }
    if(LabelData[i].y+3 >= y && LabelData[i].y <= y+3)
    {
      if(pos == i+1)
        px = xCount;
      p2[xCount++] = i+1;
    }
  }
  step=(key == UP_BUTTON || key == LEFT_BUTTON)?-1:1;
  if(key == UP_BUTTON || key == DOWN_BUTTON)
  {
    if(yCount > 1)
    {
      Bubble2Sort(p1, yCount, &py, 0);
      py += step;
      if(py < 0)
        py = yCount-1;
      else if (py == yCount)
        py = 0;
      pos = p1[py];
    }
  }
  else if(key == LEFT_BUTTON || key == RIGHT_BUTTON)
  {
    if(xCount > 1)
    {
      Bubble2Sort(p2, xCount, &px, 1);
      px += step;
      if(px < 0)
        px = xCount-1;
      else if(px == xCount)
        px = 0;
      pos = p2[px];
    }
  }
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  DirectRedrawGUI();  
  
  if (msg->gbsmsg->msg==KEY_DOWN)
  { 
    if (msg->gbsmsg->submess == RED_BUTTON)
    {
      CloseCSM(MAINCSM_ID); //There GeneralFunc challenge for Tech. GUI -> close GUI
      MAINCSM_ID=0;      
      return (1);
    }
    switch (msg->gbsmsg->submess)
    {
#if 1
    case UP_BUTTON:
    case DOWN_BUTTON:
    case LEFT_BUTTON:
    case RIGHT_BUTTON:
      GetNextPos( msg->gbsmsg->submess );
      break;
#else
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
#endif        
    case ENTER_BUTTON:
      {
        DoLabel();   
        return(1);
      }
    case '*': case '0': case '#':
    case 49: case 50: case 51:  case 52:  case 53:  case 54:  case 55:  case 56: case 57: //1-9
      {
        if(msg->gbsmsg->submess == '*')
          msg->gbsmsg->submess = 58;
        else if(msg->gbsmsg->submess == '0')
          msg->gbsmsg->submess = 59;
        else if(msg->gbsmsg->submess == '#')
          msg->gbsmsg->submess = 60;
        
        if (msg->gbsmsg->submess-49>count) return(0);
        
        pos = msg->gbsmsg->submess-48;
        DoLabel();
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

// Массив ?методами, чтоб?дать ОС информацию, каки?когд?вызывать
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

// Канвас для основног?GUI
const RECT Canvas={0,0,0,0};

// Вызывает? пр?создании главного CSM. ?данном пример?// создаётся GUI, ег?ID записывает? ?MAINGUI_ID
// на всяки?случай - вдру?понадобится ;)

#pragma inline
void patch_rect(const RECT*rcc,int x,int y, int x2, int y2)
{
  RECT *rc=(RECT *)rcc;
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

void maincsm_oncreate_GUI(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM_GUI*csm=(MAIN_CSM_GUI*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  //main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

#ifndef DAEMON
static void ELF_KILLER(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}
#endif
void maincsm_onclose_GUI(CSM_RAM *csm)
{
#ifndef DAEMON
  SUBPROC((void *)ELF_KILLER);
#endif
}

// Обработчик событи?главного CSM
int maincsm_onmessage_GUI(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM_GUI *csm=(MAIN_CSM_GUI*)data;
   if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  } 
  return(1); 
}

// Инициализация структур?MAINCSM
const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name_GUI;
}MAINCSM =
{
  {
    maincsm_onmessage_GUI,
    maincsm_oncreate_GUI,
#ifdef NEWSGOLD
0,
0,
0,
0,
#endif
maincsm_onclose_GUI,
sizeof(MAIN_CSM_GUI),
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

#ifdef DAEMON
void Check()
{
  LockSched();
  char dummy[sizeof(MAIN_CSM_GUI)];
  //UpdateCSMname_GUI();
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,2);
  UnlockSched();
}

int maincsm_onmessage(CSM_RAM* data, GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (StrCmpNoCase(successed_config_filename,(char *)msg->data0)==0)
    {
      void RereadSettings(void);
      RereadSettings();
//      ShowMSG(1,(int)"IdleLinks config updated!");
    }
  }
  return (1);
}  

int my_keyhook(int key, int m)
{
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if ((IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))&&IsUnlocked()&&(m==KEY_DOWN)&&(active)&&(!IsScreenSaver()))
     if (key==CALL_BTN) 
       {
         Check();
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

static void maincsm_oncreate(CSM_RAM *data)
{
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  if (MAINCSM_ID) CloseCSM(MAINCSM_ID);
  RemoveKeybMsgHook((void *)my_keyhook);  
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
}

static unsigned short maincsm_name_body[140];

static const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM_d =
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

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM_d.maincsm_name),"IdleLinks_d");
}
#endif

void UpdateCSMname_GUI(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name_GUI),"IdleLinks");
}

// Основн? процедур? Он?первой получает управление пр?старте эльф?
int main(void)
{
  LockSched();
  RereadSettings();
#ifdef DAEMON
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  
  #ifdef NEWSGOLD
    save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
    CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
    CreateCSM(&MAINCSM_d.maincsm,dummy,0);
    CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
    AddKeybMsgHook((void *)my_keyhook);
  #else
    AddKeybMsgHook((void *)my_keyhook);
/*      if (!AddKeybMsgHook((void *)my_keyhook)) 
      {
        ShowMSG(1, (int) "TurnOff_d. Unable to register a handler!"); 
        SUBPROC((void *)Killer);
      }
      else*/
      {
        save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
        CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
        CreateCSM(&MAINCSM_d.maincsm,dummy,0);
        CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
      }
  #endif
#else  
  char dummy[sizeof(MAIN_CSM_GUI)];
  UpdateCSMname_GUI();
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
#endif  

  UnlockSched();
  
  return 0;
}
