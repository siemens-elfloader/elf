char target[80],name[50],level[80];

static void tmethod0(MAIN_GUI *data)
{ 
  WSHDR *ws = AllocWS(256);
  //const char percentt[3]="%t\0";
  DrawRoundedFrame(0,0,ScreenW()-1,ScreenH()-1,0,0,0,GOLD,DARKBROWN);
  
#ifdef ELKA
  wsprintf(ws,"Lvl:%t\0",name);
  DrawString(ws,5,10,ScreenW()-5,28,FONT_SMALL_BOLD,0,GOLD,GetPaletteAdrByColorIndex(23)); 
  
  DrawRoundedFrame(3,31,ScreenW()-3,ScreenH()-3,0,0,0,DARKGOLD,NULLL);
  DrawRoundedFrame(2,30,ScreenW()-3,ScreenH()-3,0,0,0,GOLD,NULLL);
  
  wsprintf(ws,"%t\n%t%t",target,"Цели:",level);
  DrawString(ws,5,90,ScreenW()-5,220,FONT_SMALL,0,GOLD,GetPaletteAdrByColorIndex(23)); 
#else
  wsprintf(ws,"Lvl:%t\0",name);
  DrawString(ws,5,5,ScreenW()-5,20,FONT_SMALL_BOLD,0,GOLD,GetPaletteAdrByColorIndex(23)); 
  
  DrawRoundedFrame(3,21,ScreenW()-3,ScreenH()-3,0,0,0,DARKGOLD,NULLL);
  DrawRoundedFrame(2,20,ScreenW()-3,ScreenH()-3,0,0,0,GOLD,NULLL);
  
  wsprintf(ws,"%t\n%t%t",target,"Цели:",level);
  DrawString(ws,5,25,ScreenW()-5,128,FONT_SMALL,0,GOLD,GetPaletteAdrByColorIndex(23)); 
#endif
  
  FreeWS(ws);
}

static void tmethod1(MAIN_GUI *data,void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

static void tmethod2(MAIN_GUI *data,void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

static void tmethod3(MAIN_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
  DisableIDLETMR();
  data->gui.state=2;
}

static void tmethod4(MAIN_GUI *data,void (*mfree_adr)(void *))
{
  if (data->gui.state!=2)
    return;
  data->gui.state=1;
}

static int tmethod5(MAIN_GUI *data,GUI_MSG *msg)
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case ENTER_BUTTON: case '5': case RED_BUTTON: case RIGHT_SOFT: return(1);
    }
    
  }
  return(0);
}

static int tmethod8(void){return(0);}

static int tmethod9(void){return(0);}

extern void kill_data(void *p, void (*func_p)(void *));
static const void * const gui_tmethods[11]={
  (void *)tmethod0,  //Redraw
  (void *)tmethod1,  //Create
  (void *)tmethod2,  //Close
  (void *)tmethod3,  //Focus
  (void *)tmethod4,  //Unfocus
  (void *)tmethod5,  //OnKey
  0,
  (void *)kill_data, //method7, //Destroy
  (void *)tmethod8,
  (void *)tmethod9,
  0
};

const RECT Canvt={0,0,0,0};


int TextBox(char nameb[80],char targetb[80],char levelb[80])
{
  strncpy(target,targetb, 80);
  strncpy(name,nameb, 50);
  strncpy(level,levelb, 80);
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvt);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_tmethods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();

  return(CreateGUI(main_gui));
  
}
