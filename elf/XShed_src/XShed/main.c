#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"


//// extern //////
extern const char fontcolor[4], outline[4];
extern const char Pon11[128], Pon12[128], Pon13[128], Pon14[128], Pon21[128], Pon22[128], Pon23[128], Pon24[128];
extern const char Pon15[128], Pon16[128], Pon17[128], Pon25[128], Pon26[128], Pon27[128];
extern const char Vt11[128], Vt12[128], Vt13[128], Vt14[128], Vt21[128], Vt22[128], Vt23[128], Vt24[128];
extern const char Vt15[128], Vt16[128], Vt17[128], Vt25[128], Vt26[128], Vt27[128];
extern const char Sr11[128], Sr12[128], Sr13[128], Sr14[128], Sr21[128], Sr22[128], Sr23[128], Sr24[128];
extern const char Sr15[128], Sr16[128], Sr17[128], Sr25[128], Sr26[128], Sr27[128];
extern const char Ch11[128], Ch12[128], Ch13[128], Ch14[128], Ch21[128], Ch22[128], Ch23[128], Ch24[128];
extern const char Ch15[128], Ch16[128], Ch17[128], Ch25[128], Ch26[128], Ch27[128];
extern const char Pt11[128], Pt12[128], Pt13[128], Pt14[128], Pt21[128], Pt22[128], Pt23[128], Pt24[128];
extern const char Pt15[128], Pt16[128], Pt17[128], Pt25[128], Pt26[128], Pt27[128];
extern const char Su11[128], Su12[128], Su13[128], Su14[128], Su21[128], Su22[128], Su23[128], Su24[128];
extern const char Su15[128], Su16[128], Su17[128], Su25[128], Su26[128], Su27[128];
extern const int font;
extern const char backcolor[4], description[128], linecolor[4];
extern void InitConfig();
extern const int Button;
extern const int x, y, CurWeek;

int week=0; // неделя
int tempday; // текуций день для гуя

CSM_DESC icsmd;

int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);

unsigned short maincsm_name_body[140];
const int minus11 = -11;

typedef struct
{
  char *name;
  int day;
  int week;
}TPara;

TPara para[84];

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

static void EditConfig(void) // открытие конфига из эльфа done
{
  extern const char *successed_config_filename;
  WSHDR *ws;
  ws=AllocWS(150);
  str_2ws(ws,successed_config_filename,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
  GeneralFuncF1(1);
}

void FillData(void)
{
 InitConfig();
 para[0].name=(char *)Pon11;  para[0].day=1;  para[0].week=1;
 para[1].name=(char *)Pon12;  para[1].day=1;  para[1].week=1;
 para[2].name=(char *)Pon13;  para[2].day=1;  para[2].week=1;
 para[3].name=(char *)Pon14;  para[3].day=1;  para[3].week=1;
 para[4].name=(char *)Pon15;  para[4].day=1;  para[4].week=1;
 para[5].name=(char *)Pon16;  para[5].day=1;  para[5].week=1;
 para[6].name=(char *)Pon17;  para[6].day=1;  para[6].week=1;
 para[7].name=(char *)Pon21;  para[7].day=1;  para[7].week=2;
 para[8].name=(char *)Pon22;  para[8].day=1;  para[8].week=2;
 para[9].name=(char *)Pon23;  para[9].day=1;  para[9].week=2;
 para[10].name=(char *)Pon24;  para[10].day=1;  para[10].week=2;
 para[11].name=(char *)Pon25;  para[11].day=1;  para[11].week=2;
 para[12].name=(char *)Pon26;  para[12].day=1;  para[12].week=2;
 para[13].name=(char *)Pon27;  para[13].day=1;  para[13].week=2;
 para[14].name=(char *)Vt11;  para[14].day=2;  para[14].week=1;
 para[15].name=(char *)Vt12;  para[15].day=2;  para[15].week=1;
 para[16].name=(char *)Vt13;  para[16].day=2;  para[16].week=1;
 para[17].name=(char *)Vt14;  para[17].day=2;  para[17].week=1;
 para[18].name=(char *)Vt15;  para[18].day=2;  para[18].week=1;
 para[19].name=(char *)Vt16;  para[19].day=2;  para[19].week=1;
 para[20].name=(char *)Vt17;  para[20].day=2;  para[20].week=1;
 para[21].name=(char *)Vt21;  para[21].day=2;  para[21].week=2;
 para[22].name=(char *)Vt22;  para[22].day=2;  para[22].week=2;
 para[23].name=(char *)Vt23;  para[23].day=2;  para[23].week=2;
 para[24].name=(char *)Vt24;  para[24].day=2;  para[24].week=2;
 para[25].name=(char *)Vt25;  para[25].day=2;  para[25].week=2;
 para[26].name=(char *)Vt26;  para[26].day=2;  para[26].week=2;
 para[27].name=(char *)Vt27;  para[27].day=2;  para[27].week=2;
 para[28].name=(char *)Sr11;  para[28].day=3;  para[28].week=1;
 para[29].name=(char *)Sr12;  para[29].day=3;  para[29].week=1;
 para[30].name=(char *)Sr13;  para[30].day=3;  para[30].week=1;
 para[31].name=(char *)Sr14;  para[31].day=3;  para[31].week=1;
 para[32].name=(char *)Sr15;  para[32].day=3;  para[32].week=1;
 para[33].name=(char *)Sr16;  para[33].day=3;  para[33].week=1;
 para[34].name=(char *)Sr17;  para[34].day=3;  para[34].week=1;
 para[35].name=(char *)Sr21;  para[35].day=3;  para[35].week=2;
 para[36].name=(char *)Sr22;  para[36].day=3;  para[36].week=2;
 para[37].name=(char *)Sr23;  para[37].day=3;  para[37].week=2;
 para[38].name=(char *)Sr24;  para[38].day=3;  para[38].week=2;
 para[39].name=(char *)Sr25;  para[39].day=3;  para[39].week=2;
 para[40].name=(char *)Sr26;  para[40].day=3;  para[40].week=2;
 para[41].name=(char *)Sr27;  para[41].day=3;  para[41].week=2;
 para[42].name=(char *)Ch11;  para[42].day=4;  para[42].week=1;
 para[43].name=(char *)Ch12;  para[43].day=4;  para[43].week=1;
 para[44].name=(char *)Ch13;  para[44].day=4;  para[44].week=1;
 para[45].name=(char *)Ch14;  para[45].day=4;  para[45].week=1;
 para[46].name=(char *)Ch15;  para[46].day=4;  para[46].week=1;
 para[47].name=(char *)Ch16;  para[47].day=4;  para[47].week=1;
 para[48].name=(char *)Ch17;  para[48].day=4;  para[48].week=1;
 para[49].name=(char *)Ch21;  para[49].day=4;  para[49].week=2;
 para[50].name=(char *)Ch22;  para[50].day=4;  para[50].week=2;
 para[51].name=(char *)Ch23;  para[51].day=4;  para[51].week=2;
 para[52].name=(char *)Ch24;  para[52].day=4;  para[52].week=2;
 para[53].name=(char *)Ch25;  para[53].day=4;  para[53].week=2;
 para[54].name=(char *)Ch26;  para[54].day=4;  para[54].week=2;
 para[55].name=(char *)Ch27;  para[55].day=4;  para[55].week=2;
 para[56].name=(char *)Pt11;  para[56].day=5;  para[56].week=1;
 para[57].name=(char *)Pt12;  para[57].day=5;  para[57].week=1;
 para[58].name=(char *)Pt13;  para[58].day=5;  para[58].week=1;
 para[59].name=(char *)Pt14;  para[59].day=5;  para[59].week=1;
 para[60].name=(char *)Pt15;  para[60].day=5;  para[60].week=1;
 para[61].name=(char *)Pt16;  para[61].day=5;  para[61].week=1;
 para[62].name=(char *)Pt17;  para[62].day=5;  para[62].week=1;
 para[63].name=(char *)Pt21;  para[63].day=5;  para[63].week=2;
 para[64].name=(char *)Pt22;  para[64].day=5;  para[64].week=2;
 para[65].name=(char *)Pt23;  para[65].day=5;  para[65].week=2;
 para[66].name=(char *)Pt24;  para[66].day=5;  para[66].week=2;
 para[67].name=(char *)Pt25;  para[67].day=5;  para[67].week=2;
 para[68].name=(char *)Pt26;  para[68].day=5;  para[68].week=2;
 para[69].name=(char *)Pt27;  para[69].day=5;  para[69].week=2;
 para[70].name=(char *)Su11;  para[70].day=6;  para[70].week=1;
 para[71].name=(char *)Su12;  para[71].day=6;  para[71].week=1;
 para[72].name=(char *)Su13;  para[72].day=6;  para[72].week=1;
 para[73].name=(char *)Su14;  para[73].day=6;  para[73].week=1;
 para[74].name=(char *)Su15;  para[74].day=6;  para[74].week=1;
 para[75].name=(char *)Su16;  para[75].day=6;  para[75].week=1;
 para[76].name=(char *)Su17;  para[76].day=6;  para[76].week=1;
 para[77].name=(char *)Su21;  para[77].day=6;  para[77].week=2;
 para[78].name=(char *)Su22;  para[78].day=6;  para[78].week=2;
 para[79].name=(char *)Su23;  para[79].day=6;  para[79].week=2;
 para[80].name=(char *)Su24;  para[80].day=6;  para[80].week=2;
 para[81].name=(char *)Su25;  para[81].day=6;  para[81].week=2;
 para[82].name=(char *)Su26;  para[82].day=6;  para[82].week=2;
 para[83].name=(char *)Su27;  para[83].day=6;  para[83].week=2;

  week = CurWeek + 1;
}

void onRedraw(MAIN_GUI *data)
{
  
  TDate date;
  TTime time;
  GetDateTime(&date,&time); 

  void *canvasdata=BuildCanvas();
  
  DrawCanvas(canvasdata,0,0,131,176,1);
  DrawRoundedFrame(0,0,131,176,0,0,0,backcolor,backcolor);
  
  WSHDR *ws=AllocWS(127);
  int dy=0;
  int i=0;
  int height;
  
  char *cday[7]={"Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота" ,"Выходной!!!"};
  
  height = GetFontYSIZE(font) + 1;
  wsprintf(ws, description);
  DrawString(ws,5,2,5 + Get_WS_width(ws, font) + 1, 5 + height, font, 32, fontcolor, outline);
  wsprintf(ws,cday[tempday-1]);
  DrawString(ws,5,20,5 + Get_WS_width(ws,font) + 1, 20 + height, font ,32 , fontcolor, outline);

    do
    {
      if ((para[i].week == week) && (para[i].day == tempday) && (tempday != 7) && (para[i].name != " "))
      {
        wsprintf(ws,para[i].name," ");
        DrawRoundedFrame(5,40 + dy, 126, 40 + dy +height, 0, 0, 0, linecolor,GetPaletteAdrByColorIndex(23));
        DrawString(ws,5,40 + dy,5 + Get_WS_width(ws, font) + 1, 40 + dy + height, font, 32 ,fontcolor, outline);
        dy += height;
      }
      i++;
    }while (i<84);///// us
    
    /*if ((para[i].week == 1) && (para[i].day == 1))
    {
      wsprintf(ws,para[i].name);
      DrawString(ws,5,dy,5+Get_WS_width(ws, 7),dy + GetFontYSIZE(7),7,33,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(0));
      dy+=GetFontYSIZE(7)+1;
    }
    i++;
  }
  while (i<4); */
  //DrawString(ws,5,10,5+Get_WS_width(ws,7),10+GetFontYSIZE(7),7,1,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));
  FreeWS(ws);
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int onKey(MAIN_GUI *data, GUI_MSG *msg)
{
  REDRAW();
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
#ifdef NEWSGOLD
    case RIGHT_SOFT:
      return(1);
#else
    case RED_BUTTON:
      return(1);
#endif
    case GREEN_BUTTON:
      ShowMSG(1,(int)"XShed\n©Nicckk"); // не трогать )))
      break;
    case LEFT_BUTTON:
      if (tempday == 1 ) tempday = 6;
        else tempday -=1;
      break;
    case RIGHT_BUTTON:
      if (tempday == 6) tempday = 1;
        else tempday +=1;
      break;
    case '*':
      EditConfig();
      break;
    };
  }
  return(0);
}

int method8(void)
{
  return(0);
}

int method9(void)
{
  return(0);
}

extern void kill_data(void *p,void(*func_p)(void *));
void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

const void * const gui_methods[11]=
{
  (void *)onRedraw,
  (void *)onCreate,
  (void *)onClose,
  (void *)onFocus,
  (void *)onUnfocus,
  (void *)onKey,
  0,
  (void *)kill_data,
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,0,0};

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui = malloc(sizeof(MAIN_GUI));
  MAIN_CSM *csm = (MAIN_CSM*)data;
  zeromem(main_gui, sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id = CreateGUI(main_gui);
}

void maincsm_onclose(CSM_RAM *csm)
{
  //SUBPROC((void *)ElfKiller);
}
///// добавить сообщение для вызова GUI из другого эльфа!!!!!!
int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm = (MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED) && ((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  return(1);
}

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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"XShed");
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

int MyIDLECSM_onMessage(CSM_RAM*data, GBS_MSG *msg)
{
  int csm_result;
  csm_result=old_icsm_onMessage(data,msg);
  
  if (msg->msg == MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      FillData();
      ShowMSG(1,(int)"XShed\n config updated!");
    }
  }
  
  void *icsm = FindCSMbyID(CSM_root()->idle_id);
  if ((IsGuiOnTop(((int*)icsm)[DISPLACE_OF_IDLEGUI_ID/4])) && (!IsScreenSaver()))
  {
    void *canvasdata = BuildCanvas();
    
    TDate date;
    TTime time;
    int day, i=0, dy=0, height;
    
    height = GetFontYSIZE(font) + 1;
    GetDateTime(&date, &time);
    day = GetWeek(&date) + 1;
    
    WSHDR *ws=AllocWS(128);
    // добавить подсветку текущей пары!!!!!
   // do
    //{
      if ((para[i].day == day) && (para[i].week == week) && (day != 7)) 
      {
        //DrawRoundedFrame(x,y,x+10,y+10,1,1,0,GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(0));
        if(time.hour>=8 && time.hour <=9 && time.min <= 30) i=0;
        else if(time.hour>=9 &&  time.min>=45 && time.hour <=11 && time.min <= 15) i=1;
        else if(time.hour>=11 && time.min>=15 && time.hour <=13 && time.min <=  0) i=2;
        else if(time.hour>=13 && time.min>=15 && time.hour <=14 && time.min <= 45) i=3;
        else if(time.hour>=15 && time.min>= 0  && time.hour <=16 && time.min <= 30) i=4;
        else if(time.hour>=16 && time.min>=45 && time.hour <=18 && time.min <= 15) i=5;
        else if(time.hour>=18 && time.min>=30 && time.hour <=20 && time.min <=  0) i=6;
        
        wsprintf(ws,"%t\n%t",para[i].name,para[i+1].name);
        DrawCanvas(canvasdata,x, y /*+ dy*/, x + Get_WS_width(ws, font), y + dy + height, 1);
        DrawString(ws, x, y/* + dy*/, x + Get_WS_width(ws, font), y + dy + height, font, 32, fontcolor, outline);
//        dy += height;
      }
    //  i++;
   // }while (i<84);
    
    FreeWS(ws);
  }
  return(csm_result);
}

int my_keyhook(int key, int m)
{
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if ((IsGuiOnTop(((int*)icsm)[DISPLACE_OF_IDLEGUI_ID/4])) && IsUnlocked() && (m==KEY_DOWN) && (!IsScreenSaver()))
  {
    if (key == Button)
    {
      TDate date;
      TTime time;
      
      GetDateTime(&date, &time);
      
      tempday = GetWeek(&date) + 1;
      /*
      LockSched();
      char dummy[sizeof(MAIN_CSM)];
      UpdateCSMname();
      CreateCSM(&MAINCSM.maincsm, dummy, 2);
      UnlockSched();*/
    }
  }
  return(0);
}
/*static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"XShed");
}*/

int main(void)
{
  LockSched();
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  memcpy(&icsmd, icsm->constr, sizeof(icsmd));
  old_icsm_onMessage=icsmd.onMessage;
  icsmd.onMessage=MyIDLECSM_onMessage;
  old_icsm_onClose=icsmd.onClose;
  icsmd.onClose=MyIDLECSM_onClose;
  icsm->constr=&icsmd;
  
  AddKeybMsgHook((void *)my_keyhook);
///  UnlockSched();
  
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();  
  //LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  FillData();
  
  return(0);
}
