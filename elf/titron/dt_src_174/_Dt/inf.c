
RECT pop={2,50,100,200};
unsigned short px=0,py=0;

void popupp()
{
	char ch=2;
	px+=20;
	py+=20;
	if(px>pop.x2-pop.x){ch--; px=pop.x2-pop.x;}
	if(py>pop.y2-pop.y){ch--; py=pop.y2-pop.y;}
	DrwImg(mfn, 0,0, NULL,NULL);
	bar();
	DrawRectangle(pop.x,pop.y,pop.x+px,pop.y+py,0,red,white0);
	DrwImg(cursor, cur.x,cur.y, NULL,NULL);
	if(ch) GBS_StartTimerProc(&inftmr, 5, popupp);
	else DirectRedrawGUI();
}

void chota()
{
	DrawRectangle(cur.x,cur.y,cur.x+70,cur.y+90,0,red,white0);
	//DrwImg(cursor, cur.x+50,cur.y+50, NULL,NULL);
}

 //Redraw
static void gOnRedraw(MAIN_GUI *data)
{
  if ((data->gui.state==2)&&(py>=pop.y2-pop.y))
  {
	//DrawRectangle(0,0,scr_w,scr_h,0,black,black);
	DrwImg(mfn, 0,0, NULL,NULL);
	bar();
	DrawRectangle(pop.x,pop.y,pop.x+px,pop.y+py,0,red,white0);
	
	RAMNET *rn=RamNet();
    RAMNET *rn1=RamNet()+1;
    RAMNET *rn2=RamNet()+2;
    RAMNET *rn3=RamNet()+3;
    RAMNET *rn4=RamNet()+4;
    RAMNET *rn5=RamNet()+5;
    RAMNET *rn6=RamNet()+6;
		// if((cur.x<100)&&(cur.y<50)) DrawString(ws,2,13,scr_w/3,scr_h,FONT_SMALL,1,red,NULL);
		// else DrawString(ws,2,13,scr_w/3,scr_h,FONT_SMALL,1,white,NULL);
		//if(f.rn->power!=0) DrawRoundedFrame(2,2,2+(scr_w/3-(f.rn->power-60)*(scr_w/3)/60),12,0,0,0,white,white0);
		if(rn->power!=0) DrawRoundedFrame(3,43,3+(scr_w/3-(rn->power-60)*(scr_w/3)/60),50,0,0,0,red,black );
		if(rn1->power!=0) DrawRoundedFrame(3,53,3+(scr_w/3-(rn1->power-60)*(scr_w/3)/60),60,0,0,0,red,black );
		if(rn2->power!=0) DrawRoundedFrame(3,63,3+(scr_w/3-(rn2->power-60)*(scr_w/3)/60),70,0,0,0,red,black );
		if(rn3->power!=0) DrawRoundedFrame(3,73,3+(scr_w/3-(rn3->power-60)*(scr_w/3)/60),80,0,0,0,red,black);
		if(rn4->power!=0) DrawRoundedFrame(3,83,3+(scr_w/3-(rn4->power-60)*(scr_w/3)/60),90,0,0,0,red,black );
		if(rn5->power!=0) DrawRoundedFrame(3,93,3+(scr_w/3-(rn5->power-60)*(scr_w/3)/60),100,0,0,0,red,black );
		if(rn6->power!=0) DrawRoundedFrame(3,103,3+(scr_w/3-(rn6->power-60)*(scr_w/3)/60),110,0,0,0,red,black );
	
	
	
	DrwImg(cursor, cur.x,cur.y, NULL,NULL);
	// if(IsTimerProc(&chcurtmr)) GBS_DelTimer(&chcurtmr);
	// GBS_StartTimerProc(&chcurtmr, 108, chota);
	//fillTriangle(cur.x, cur.y, cur.x+10, cur.y+5, cur.x+5, cur.y+10, 0, white, white0);
  }
}

 //Create
static void gOnCreate(MAIN_GUI *data,void *(*malloc_adr)(int))
{
	px=0;py=0;
	data->gui.state=1;
	popupp();
	//REDRAW();
}

 //Close
static void gOnClose(MAIN_GUI *data,void (*mfree_adr)(void *))
{
	data->gui.state=0;
}

 //Focus
static void gOnFocus(MAIN_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
	#ifdef ELKA
		DisableIconBar(1);
	#endif
	DisableIDLETMR();
	data->gui.state=2;
}

 //Unfocus
static void gOnUnfocus(MAIN_GUI *data,void (*mfree_adr)(void *))
{
	#ifdef ELKA
		DisableIconBar(0);
	#endif
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

 //OnKey
static int gOnKey(MAIN_GUI *data,GUI_MSG *msg)
{
  int m=msg->gbsmsg->msg;
  switch(m)
  {
   //case LONG_PRESS: st=10;
   case KEY_DOWN:
	//movcr.st=1;
	switch(msg->gbsmsg->submess)
	{
	 case RIGHT_SOFT:
		return 1;
	 case RED_BUTTON:
		ShowWMSG(0, "проверка вывода сообщения", FONT_SMALL, GetPaletteAdrByColorIndex(3), GetPaletteAdrByColorIndex(7), 1);
	   break;
	}
	//DirectRedrawGUI();
	break;
  }
  curkey(msg);
	//DirectRedrawGUI();
  return 0;
}

static const void * const ggui_methods[11]={
  (void *)gOnRedraw,
  (void *)gOnCreate,
  (void *)gOnClose,
  (void *)gOnFocus,
  (void *)gOnUnfocus,
  (void *)gOnKey,
  0,
  (void *)kill_data, //method7, //Destroy
  (void *)int_0,
  (void *)int_0,
  0
};

static void gui()
{
  static const RECT Canvas={0,0,0,0};
  StoreXYXYtoRECT((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
//  view_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)ggui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  CreateGUI(main_gui);
}

