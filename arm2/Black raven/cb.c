char cbtext[80], cbbutt[8];
int pic;
int x=15,y=50,x2=225,y2=150;
static void mmmethod0(MAIN_GUI *data)
{ 
  WSHDR *ws = AllocWS(256);
  const char percentt[3]="%t\0";
  DrawRoundedFrame(15,50,225,150,3,3,0,DARKGOLD,DARKBROWN);
  DrawRoundedFrame(20,55,220,145,0,0,0,DARKGOLD,DARKBROWN);
  DrawRoundedFrame(55,120,ScreenW()-45,140,0,0,0,DARKGOLD,DARKBROWN);
  
  //DrawImg(12,22,pic);
  
  wsprintf(ws,percentt,cbtext);
  DrawString(ws,47,70,ScreenW()-47,119,FONT_SMALL,2,GOLD,GetPaletteAdrByColorIndex(23)); 
  
  wsprintf(ws,percentt,cbbutt);
  DrawString(ws,47,120,ScreenW()-47,139,FONT_MEDIUM_BOLD,2,GOLD,GetPaletteAdrByColorIndex(23)); 
  
  FreeWS(ws);
}

static void mmmethod1(MAIN_GUI *data,void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

static void mmmethod2(MAIN_GUI *data,void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

static void mmmethod3(MAIN_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
  DisableIDLETMR();
  data->gui.state=2;
}

static void mmmethod4(MAIN_GUI *data,void (*mfree_adr)(void *))
{
  if (data->gui.state!=2)
    return;
  data->gui.state=1;
}

static int mmmethod5(MAIN_GUI *data,GUI_MSG *msg)
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case ENTER_BUTTON: case '5': return(1);
    }
    
  }
  return(0);
}

static int mmmethod8(void){return(0);}

static int mmmethod9(void){return(0);}

extern void kill_data(void *p, void (*func_p)(void *));
static const void * const gui_mmmethods[11]={
  (void *)mmmethod0,  //Redraw
  (void *)mmmethod1,  //Create
  (void *)mmmethod2,  //Close
  (void *)mmmethod3,  //Focus
  (void *)mmmethod4,  //Unfocus
  (void *)mmmethod5,  //OnKey
  0,
  (void *)kill_data, //method7, //Destroy
  (void *)mmmethod8,
  (void *)mmmethod9,
  0
};

const RECT Canvvvv={0,0,129,129};



int ConfirmBox(char text[80], char button[8], int picz)
{
  strncpy(cbtext,text, 80);
  strncpy(cbbutt,button,8);
  pic=(picz==0)?0xDEAD:picz;
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvvvv);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_mmmethods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();

  return(CreateGUI(main_gui));
  
}
