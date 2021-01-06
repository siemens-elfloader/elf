char target[80],name[50],level1[80],level2[80],level3[80],compl1[80],compl2[80],compl3[80];
int yes1,yes2,yes3;
static void tmethod0(MAIN_GUI *data)
{ 
  WSHDR *ws = AllocWS(256);
  if(yes1==1){sprintf(compl1,"Завершено");}
  if(yes1==0){sprintf(compl1,"Не выполнено!");}
  if(yes2==1){sprintf(compl2,"Завершено");}
  if(yes2==0){sprintf(compl2,"Не выполнено!");}
  if(yes3==1){sprintf(compl3,"Завершено");}
  if(yes3==0){sprintf(compl3,"Не выполнено!");}
  DrawRoundedFrame(0,0,ScreenW()-1,ScreenH()-1,0,0,0,GOLD,DARKBROWN);
  
  wsprintf(ws,"%t %t\0","Уровень:",name);
  DrawString(ws,5,10,ScreenW()-5,28,FONT_SMALL_BOLD,0,GOLD,GetPaletteAdrByColorIndex(23)); 
  
  DrawRoundedFrame(3,31,ScreenW()-3,ScreenH()-3,0,0,0,DARKGOLD,NULLL);
  DrawRoundedFrame(2,30,ScreenW()-3,ScreenH()-3,0,0,0,GOLD,NULLL);
  
  wsprintf(ws,"%t",target);
  DrawString(ws,5,35,ScreenW()-5,80,FONT_SMALL,0,GOLD,GetPaletteAdrByColorIndex(23)); 
  
  
  
  wsprintf(ws,"%t%t\n  %t","Цели: \n",level1,compl1);
  DrawString(ws,5,90,ScreenW()-5,180,FONT_SMALL,0,GOLD,GetPaletteAdrByColorIndex(23)); 
  
  wsprintf(ws,"%t\n  %t",level2,compl2);
  DrawString(ws,5,200,ScreenW()-5,245,FONT_SMALL,0,GOLD,GetPaletteAdrByColorIndex(23)); 
  
  wsprintf(ws,"%t\n  %t",level3,compl3);
  DrawString(ws,5,255,ScreenW()-5,300,FONT_SMALL,0,GOLD,GetPaletteAdrByColorIndex(23)); 
  
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



int TextBox(char nameb[255],char targetb[255],char mission1[255],int miss1,char mission2[255],int miss2,char mission3[255],int miss3)
{
  strncpy(target,targetb, 255);
  strncpy(name,nameb, 255);
  strncpy(level1,mission1, 255);
  strncpy(level2,mission2, 255);
  strncpy(level3,mission3, 255);
  yes1=miss1;
  yes2=miss2;
  yes3=miss3;
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvt);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_tmethods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();

  return(CreateGUI(main_gui));
  
}
