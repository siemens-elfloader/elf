

void Hide();







const int minus11=-11;
int cop = 0;
int zzy = 65;
int Vniz = 0;  //режим опускания панели
int sep = 1; // вырубление через унфокус
unsigned short maincsm_name_body[140];

unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
void TimeZone();

static const char *percent_t="%t";
char *nill="";
char *pps="%s%s";




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











void OnRedraw(MAIN_GUI *data);

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  //Hide();
  if (sep == 0) KbdUnlock();
  GBS_DelTimer(&idle_timer); 
  GBS_DelTimer(&time_timer);  
  GBS_DelTimer(&sleep_timer);
  GBS_DelTimer(&touch_timer);  
  DisableIconBar(0);
  data->gui.state=0;
  
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  DisableIconBar(1);
  if (bond) {GBS_StartTimerProc(&time_timer, TMR_SECOND/3, TimeZone);}
 if (state>3) KbdLock();
 //zzy = 65;
 //zz = 0;
  REDRAW();
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
DisableIconBar(0);
GBS_DelTimer(&idle_timer); 
GBS_DelTimer(&time_timer); 
GBS_DelTimer(&sleep_timer);
GBS_DelTimer(&touch_timer);
  if (data->gui.state!=2) return;
  data->gui.state=1;
  //if (cur_keys>0) {} SetIllumination (1,1,cur_keys,200);} else { SetIllumination(1,1,50,200);}
 // if (cur_display>0) {  SetIllumination (0,1,cur_display,200);} else { SetIllumination(0,1,50,200);}
  CloseCSM(MAINCSM_ID);
  
}

/*
Продолжение заставки [b]iPhone_Saver[/b].
Добавил разблокировку "левый-правый софт". Работает когда видна подсказка. Также можно открыть текстовым редактором iPhone_Saver2.ini из etc и отредактировать надпись "Разблокировать #". Убрал левые таймеры, меньше грузит проц. 
зы Ближайшее время больше ничего модифицировать не буду, разве что исправление ошибок. (Недовыложилось)
*/




int OnKey(MAIN_GUI *data, GUI_MSG *msg);

extern void kill_data(void *p, void (*func_p)(void *));

void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data,mfree_adr);
}

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
#ifdef NEWSGOLD
(void *)onDestroy,
#else
(void *)kill_data,	
#endif
(void *)method8,
(void *)method9,
0
};






void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  gipc.name_to=ipc_my_name;
  gipc.name_from=ipc_my_name;
  gipc.data=(void *)-1;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_CHECK_DOUBLERUN,&gipc);
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  MAINGUI_ID=csm->gui_id;
  if (fore>0) {cur_display = fore; cur_keys=fore;} else {
  cur_display=*(GetIlluminationDataTable()+3);
  cur_keys=*(GetIlluminationDataTable()+152+3);}

}

void ElfKiller(void)
{
  extern void kill_data(void *p, void (*func_p)(void *));
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  
  
  
  //if (cur_keys>0) {SetIllumination(1,1,cur_keys,200);} else {SetIllumination(1,1,50,200);}
 // if (cur_display>0) {SetIllumination(0,1,cur_display,200);} else {SetIllumination(0,1,50,200);}
 // if (cur_display>0) {*RamBr() = cur_display;} else {*RamBr() = 50;}  
bond=0; // умер таймер
  //mfree(outim->bitmap);
  //mfree(outim);
 
   if (FImage1->bitmap) mfree(FImage1->bitmap); 
   if (FImage2->bitmap) mfree(FImage2->bitmap);
   if  (strlen (FImage3->bitmap)>0) mfree(FImage3->bitmap); 
   if  (strlen (FImage3b->bitmap)>0) mfree(FImage3b->bitmap);  
   if  (strlen (FImage4->bitmap)>0) mfree(FImage4->bitmap); 
   if  (strlen (FImage5->bitmap)>0) mfree(FImage5->bitmap); 
   if  (strlen (FImage5b->bitmap)>0) mfree(FImage5b->bitmap);   
   if  (strlen (FImage6->bitmap)>0) mfree(FImage6->bitmap); 
   if  (strlen (FImage6b->bitmap)>0) mfree(FImage6b->bitmap);      
   if  (strlen (FImage7->bitmap)>0) mfree(FImage7->bitmap);   
   if  (strlen (FImage7b->bitmap)>0) mfree(FImage7b->bitmap);   
   //if  (strlen (FImage8->bitmap)>0) mfree(FImage8->bitmap);  очищается сразу после порезки на куски (шрифт)   
   if  (strlen (FImage9->bitmap)>0) mfree(FImage9->bitmap);    
   if  (strlen (FImage10->bitmap)>0) mfree(FImage10->bitmap);     
 
   mfree(Dig0->bitmap);
   mfree(Dig1->bitmap);
    mfree(Dig2->bitmap);
     mfree(Dig3->bitmap);
      mfree(Dig4->bitmap);
       mfree(Dig5->bitmap);
        mfree(Dig6->bitmap);
         mfree(Dig7->bitmap);
          mfree(Dig8->bitmap);
           mfree(Dig9->bitmap);
            mfree(Dig10->bitmap);
   mfree(Dig0);
   mfree(Dig1);
    mfree(Dig2);
     mfree(Dig3);
      mfree(Dig4);
       mfree(Dig5);
        mfree(Dig6);
         mfree(Dig7);
          mfree(Dig8);
           mfree(Dig9);
            mfree(Dig10);            
            if (block) mfree(block);     
   
   
   
   if (FImage1) mfree(FImage1); 
   if (FImage2) mfree(FImage2);
   if (FImage3) mfree(FImage3); 
   if (FImage3b) mfree(FImage3b); 
   if (FImage4) mfree(FImage4); 
   if (FImage5) mfree(FImage5); 
   if (FImage5b) mfree(FImage5b);    
   if (FImage6) mfree(FImage6); 
   if (FImage6b) mfree(FImage6b);    
   if (FImage7) mfree(FImage7); 
   if (FImage7b) mfree(FImage7b); 
//   if (FImage8) mfree(FImage8);   очищается сразу после порезки на куски (шрифт)   
   if (FImage9) mfree(FImage9);  
   if (FImage10) mfree(FImage10);  

  // UnFonts ();
  GBS_DelTimer(&idle_timer);
  SUBPROC((void *)ElfKiller);
}
int strcmp_nocase(const char *s, const char *d);
int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
    if (msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
      {
        switch (msg->submess)
        {
         case IPC_CHECK_DOUBLERUN:
	    //Если приняли свое собственное сообщение, значит запускаем чекер
	    if (ipc->name_from==ipc_my_name) SUBPROC((void *)CheckDoubleRun);
            else ipc->data=(void *)MAINCSM_ID;
	    break; 
       case IPC_SHOW_MSG:          break;           
        }
      }
    }
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
  WSHDR *ws=AllocWS(256);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"ScreenSaver");
  FreeWS(ws);
}

