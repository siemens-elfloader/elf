#include "../../inc/swilib.h"
#include "conf_loader.h"
#include "DTop.h"
//#include "inf.c"
#include "indicators.c"
#include "Compressing_IMGHDR.c"

CSM_DESC *oldcsmd, *icsmd;
/*CSM_RAM  *olddata,  oldicsm;*/
//void (*old_icsm_onClose)(CSM_RAM*);
//void (*old_icsm_onCreate)(CSM_RAM*);
int (*old_icsm_onMessage)(CSM_RAM*, GBS_MSG *msg);

//===============================================================================================



/* char *find_eol(char *s)
{
  int c;
  s--;
  do
  {
    s++;
    c=*s;
  }
  while((c)&&(c!=10)&&(c!=13));
  return s;
} */

void loadplg()
{
  DT_ICON *TI=Dt.first;
  //char tmp[4]={'P','L','U','G'};
  for(int i=0; i<Dt.icon_cnt; i++)
  {
	PLG_P *TP=malloc(sizeof(PLG_P));
	if(((DT_ICON*)TI->next)->d==0xFF)
	{
	  //TP->sig=tmp;
	  //tmp[3]=i;
	  //TP->ic=TI;
	  wsprintf(ews,perc_t,((DT_ICON*)TI->next)->fl);
	  ExecuteFile(ews,NULL,TI);
	}
	if(i<Dt.icon_cnt-1) TI=TI->next;
  }
}

void initic()
{
  DT_ICON *TI;
  char *s, nm[32], nsz;
  int f, t, m, i=0;
  unsigned int ul, cfg_sz;
  if ((f=fopen(ICON_DT,A_ReadOnly,P_READ,&ul))!=-1)
  {
	cfg_sz=lseek(f,0,S_END,&ul,&ul);
	lseek(f,0,S_SET,&ul,&ul);
	s=malloc(cfg_sz+1);
	fread(f,s,cfg_sz,&ul);
	while(i<cfg_sz)
	{
		zeromem(nm, 32);
		while((s[i]!='[')&&(i<cfg_sz)){i++;}
		if(i>=cfg_sz) break;
		i++;
		nsz=0;
		while(s[i+nsz]!=']'){nsz++;}
		memcpy(nm, s+i, nsz);
		i+=nsz;
		while((s[i]!='+')&&(i<cfg_sz)){i++;}
		if(i>=cfg_sz) break;
		if(!strncmp(s+i,"+ACT",4))
		{
			i+=4;
			if(!strncmp(s+i,"(std)=",6))
			{
				i+=6;
				if(!strncmp(s+i,"net",3))
				{
					// Dt.icon[Dt.icon_cnt]=malloc(sizeof(DT_ICON));
					// memcpy(Dt.icon[Dt.icon_cnt], &net_icon, sizeof(DT_ICON));
					TI=&net_icon;
				}
				else if(!strncmp(s+i,"bat",3))
				{
					// Dt.icon[Dt.icon_cnt]=malloc(sizeof(DT_ICON));
					// memcpy(Dt.icon[Dt.icon_cnt], &akk_icon, sizeof(DT_ICON));
					TI=&akk_icon;
				}
				else if(!strncmp(s+i,"clock",5))
				{
					// Dt.icon[Dt.icon_cnt]=malloc(sizeof(DT_ICON));
					// memcpy(Dt.icon[Dt.icon_cnt], &clock_icon, sizeof(DT_ICON));
					TI=&clock_icon;
				}
				else continue;
				TI->inf=malloc(256);
				zeromem(TI->inf, 256);
				TI->nm=malloc(32);
				memcpy(TI->nm, nm, 32);
			}
			else if(!strncmp(s+i,"(file)=",7))
			{
				i+=7;
				TI=malloc(sizeof(DT_ICON));
				memcpy(TI, &_icon, sizeof(DT_ICON));
				TI->inf=malloc(256);
				zeromem(TI->inf, 256);
				nsz=0;
				while(s[i+nsz]!=';'){nsz++;}
				TI->fl=malloc(nsz+1);
				zeromem(TI->fl, nsz+1);
				memcpy(TI->fl, s+i, nsz);
				i+=nsz;
				TI->nm=malloc(32);
				memcpy(TI->nm, nm, 32);
			}
			else if(!strncmp(s+i,"(plugin)=",9))
			{
				i+=9;
				TI=malloc(sizeof(DT_ICON));
				memcpy(TI, &dt_null, sizeof(DT_ICON));
				TI->d=0xFF;
				nsz=0;
				while(s[i+nsz]!=';'){nsz++;}
				TI->fl=malloc(nsz+1);
				zeromem(TI->fl, nsz+1);
				memcpy(TI->fl, s+i, nsz);
				i+=nsz;
				TI->nm=malloc(32);
				memcpy(TI->nm, nm, 32);
			}
			else continue;
		}
		else continue;
		
		while((s[i]!='+')&&(i<cfg_sz)){i++;}
		if(i>=cfg_sz) break;
		if(!strncmp(s+i,"+ICON=",6))
		{
			i+=6;
			nsz=0;
			while(s[i+nsz]!=';'){nsz++;}
			TI->img=malloc(nsz+1);
			zeromem(TI->img, nsz+1);
			memcpy(TI->img, s+i, nsz);
			i+=nsz;
		}
		else goto dopos;
		
		while((s[i]!='+')&&(i<cfg_sz)){i++;}
		if(i>=cfg_sz) break;
	  dopos:
		if(!strncmp(s+i,"+POS=",5))
		{
			i+=5;
			//nsz=0;
			m=0;
			if(s[i]=='-'){m=1;i++;}
			t=0;
			while(s[i]!=','){t=t*10+s[i]-'0'; i++;}
			 if(m) TI->p.x=scr_w-t;
			 else TI->p.x=t;
			i++;
			
			m=0;
			if(s[i]=='-'){m=1;i++;}
			t=0;
			while(s[i]!=';'){t=t*10+s[i]-'0'; i++;}
			 if(m) TI->p.y=scr_h-t;
			 else TI->p.y=t;
			TI->p.x2=TI->p.x+GetImgWidth((int)TI->img);
			TI->p.y2=TI->p.y+GetImgHeight((int)TI->img);
		}
		
		while((s[i]!='+')&&(i<cfg_sz)){i++;}
		if(i>=cfg_sz) break;
		if(!strncmp(s+i,"+SIZE=",6))
		{
			i+=6;
			//nsz=0;
			t=0;
			while(s[i]!=','){t=t*10+s[i]-'0'; i++;}
			 TI->p.x2=TI->p.x+t;
			i++;
			
			t=0;
			while(s[i]!=';'){t=t*10+s[i]-'0'; i++;}
			 TI->p.y2=TI->p.y+t;
		}
		
		DT_ICON *TTI=Dt.first;
		Dt.first=TI;
		Dt.first->next=TTI;
		((DT_ICON*)Dt.first->next)->prev=Dt.first;
	
		// TI->next=Dt.icon;
		Dt.icon_cnt++;
		// Dt.icon=TI;
		i++;
		REDRAW();
	
	}
	fclose(f,&ul);
	Dt.first->prev=NULL;
	Dt.last->next=NULL;
	SUBPROC((void*)loadplg);
  }
  mfree(s);
}

// typedef struct
// {
  // CSM_RAM csm;
  // int gui_id;
// }MAIN_CSM;

int MAINGUI_ID=0;

void dofn()
{
	mfn=CreateIMGHDRFromPngFile(BG_IMG, 2);
	PressImg(mfn,1);
	cursor=CreateIMGHDRFromPngFile(CUR_IMG, 0);
	PressImg(cursor,1);
}

//===============================================================================================

void dr_inf()
{
  //DT_ICON *TI;
	char l=1, j=0, tmp[64];
	unsigned int len=0, k;
	RECT p;
	Dt.act->onInf();
	for(k=1; k<strlen(Dt.act->inf); k++)
	{
		j++;
		if(Dt.act->inf[k]=='\n')
		{
			l++;
			zeromem(tmp, 64);
			memcpy(tmp, Dt.act->inf+k-j, j);
			wsprintf(ews, perc_t, tmp);
			j=0;
			if(Get_WS_width(ews, FONT_SMALL)>len) len=Get_WS_width(ews, FONT_SMALL);
		}
	}
	zeromem(tmp, 64);
	memcpy(tmp, Dt.act->inf+k-j, j);
	wsprintf(ews, perc_t, tmp);
	j=0;
	if(Get_WS_width(ews, FONT_SMALL)>len) len=Get_WS_width(ews, FONT_SMALL);
	wsprintf(ews, perc_t, Dt.act->inf );
	/* if(l==1) */ //len=Get_WS_width(ews, FONT_SMALL);
	if(cur.x+len+3>=scr_w)
	{
		p.x=scr_w-len-3;
		p.x2=scr_w;
	}
	else
	{
		p.x=cur.x;
		p.x2=cur.x+len+3;
	}
	if(cur.y+cursor->h+l*f_h+1>=scr_h)
	{
		p.y=cur.y-l*f_h-1;
		p.y2=cur.y-1;
	}
	else
	{
		p.y=cur.y+cursor->h+1;
		p.y2=cur.y+cursor->h+l*f_h+1;
	}
	DrawRectangle(p.x,p.y,p.x2,p.y2, 0,white,white0);
	DrawString(ews,p.x+2,p.y+1,p.x2,p.y2,FONT_SMALL,1,black,NULL);
}

	// __root const CFG_HDR cfghdr0_0={CFG_CBOX,"Selecting mode",0,2};
	// __root const int MN_SEL_MOD=0;
	// __root const CFG_CBOX_ITEM cfgcbox1[]={"Cursor","Selecting"};

extern const char MN_COL1[],MN_COL0[],S_MN_COL1[],S_MN_COL0[],MN_FONT_COL[];

void m_redr()
{
	DrwImg(mfn, 0,0, NULL,NULL); // fon
	DT_MENU_P *tmnp=mm.first;


   TAI=Dt.first;
	switch(State)
	{
	 case DT_MAIN:
		Dt.foc=0;
		do
		{
		 if(infoc(&TAI->p, cur.x,cur.y)) // selected found
		 {
			Dt.act=TAI;
			Dt.foc=1;
			DrawRectangle(Dt.act->p.x-1,Dt.act->p.y-1,Dt.act->p.x2,Dt.act->p.y2,1,white,NULL); // round selected
		 }
		 TAI->onDraw();
		}while(TAI=TAI->next);
		if((Dt.inf)&&(Dt.foc)) dr_inf(); // draw popup info
	  break;
	 case DT_MENU:
		if(Dt.foc) DrawRectangle(Dt.act->p.x-1,Dt.act->p.y-1,Dt.act->p.x2,Dt.act->p.y2,1,white,NULL); // round selected
		do
		{
		 TAI->onDraw();
		}while(TAI=TAI->next);
		// if(State==DT_MENU) // draw menu
		// {
			DrawRectangle(mm.p.x,mm.p.y,mm.p.x2,mm.p.y2,0,MN_COL0,MN_COL1);
			if((MN_SEL_MOD)||(mm.foc)) DrawRectangle(mm.act->p.x-1,mm.act->p.y-1,mm.act->p.x2+1,mm.act->p.y2+1,0,S_MN_COL0,S_MN_COL1);
			mm.foc=0;
			do
			{
			 if(!MN_SEL_MOD)
			  if(infoc(&tmnp->p, cur.x,cur.y))
			  {
			   mm.foc=1;
			   mm.act=tmnp;
			  }
			  wsprintf(ews, perc_t, tmnp->nm );
			  DrawString(ews,tmnp->p.x,tmnp->p.y,tmnp->p.x2,tmnp->p.y2,FONT_SMALL,1,MN_FONT_COL,NULL);
			}while(tmnp=(DT_MENU_P*)tmnp->next);
		// }
	  break;
	}
  
  //fillTriangle(cur.x, cur.y, cur.x+10, cur.y+5, cur.x+5, cur.y+10, 0, white, white0);
  if((State!=DT_MENU)||(!MN_SEL_MOD)) DrwImg(cursor, cur.x,cur.y, white,white0);
}

 //Redraw
static void OnRedraw(MAIN_GUI *data)
{
  if (data->gui.state==2)
  {
	m_redr();
  }
}

 //Create
static void OnCreate(MAIN_GUI *data,void *(*malloc_adr)(int))
{
	//mm.first=&mm1;
	ws=AllocWS(256);
	ews=AllocWS(256);
	scr_w=ScreenW()-1;
	scr_h=ScreenH()-1;
	dofn();
	f_h=GetFontYSIZE(FONT_SMALL); // высота мелкого шрифта
	
	// StoreXYWHtoRECT(&net_icon.p, 10, 50, 30, 6+f_h);
	// net_icon.inf=malloc(256);
	// Dt.icon[0]=&net_icon;
	
	// StoreXYWHtoRECT(&akk_icon.p, scr_w-80, 50, 30, 6+f_h);
	// akk_icon.inf=malloc(256);
	// Dt.icon[1]=&akk_icon;
	
	State=DT_MAIN;
	Dt.icon_cnt=0;
	Dt.inf=0;
	Dt.first=Dt.last=Dt.act=&dt_first;
	SUBPROC((void*)initic);
	data->gui.state=1;
	//REDRAW();
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void ClearIcons()
{
  DT_ICON *TTI;
  DT_ICON *TI=Dt.first;
	if(mfn)
	{
		mfree(mfn->bitmap);
		mfree(mfn);
	}
	if(cursor)
	{
		mfree(cursor->bitmap);
		mfree(cursor);
	}
	for(int i=0; i<Dt.icon_cnt; i++)
	{
		if(strlen(TI->nm)) mfree(TI->nm);
		if(strlen(TI->fl)) mfree(TI->fl);
		if(strlen(TI->img)) mfree(TI->img);
		mfree(TI->inf);
		if(i<Dt.icon_cnt-1) TTI=TI->next;
		if(TI->d) mfree(TI);
		if(i<Dt.icon_cnt-1) TI=TTI;
		//*nm, *inf, *img, *fl,
	}
}

 //Close
static void OnClose(MAIN_GUI *data,void (*mfree_adr)(void *))
{
	FreeWS(ws);
	FreeWS(ews);
	ClearIcons();
	if(idle_ch)
	{
        CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
        LockSched();
        icsm->constr=oldcsmd;
        UnlockSched();
		mfree(icsmd);
        // LockSched();
        // icsmd->onMessage=old_icsm_onMessage;
        // UnlockSched();
	}
	else data->gui.state=0;
	
  SUBPROC((void *)Killer);
}

 //Focus
static void OnFocus(MAIN_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
	#ifdef ELKA
		DisableIconBar(1);
	#endif
	DisableIDLETMR();
	data->gui.state=2;
}

 //Unfocus
static void OnUnfocus(MAIN_GUI *data,void (*mfree_adr)(void *))
{
	#ifdef ELKA
		DisableIconBar(0);
	#endif
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

void Ad_MN_Point(DT_MENU_P *point)
{
	DT_MENU_P *tmnp=mm.first;
	mm.first=point;
	mm.first->next=tmnp;
	((DT_MENU_P*)mm.first->next)->prev=mm.first;
}

void onRight()
{
	Dt.foc=0;
   DT_ICON *TI=Dt.first;
   do
   {
	if(infoc(&TI->p, cur.x,cur.y))
	{
		Dt.act=TI;
		Dt.foc=1;
	}
   }while(TI=TI->next);

	char mcnt=0;
	unsigned short len=0;
	State=DT_MENU;
	DT_MENU_P *tmnp;
	
	mm.first=mm.last=&mm_exit;
	mm.last->next=NULL;
	
	Ad_MN_Point(&mm_icon_dt);
	// mm.first=&mm_icon_dt;
	// mm.first->next=tmnp;
	// ((DT_MENU_P*)mm.first->next)->prev=mm.first;
	//mm.first->next=tmnp;
	
	Ad_MN_Point(&mm_bcfg);
	// tmnp=mm.first;
	// mm.first=&mm_bcfg;
	// mm.first->next=tmnp;
	// ((DT_MENU_P*)mm.first->next)->prev=mm.first;
	//mm.first->next=tmnp;
	
	if(Dt.foc)
	{
	 Ad_MN_Point(&mm_open);
	 // tmnp=mm.first;
	 // mm.first=&mm_open;
	 // mm.first->next=tmnp;
	 // ((DT_MENU_P*)mm.first->next)->prev=mm.first;
	 //mm.first->next=tmnp;
	}
	
	mm.first->prev=NULL;
	if(MN_SEL_MOD) mm.act=mm.first;
	
	// mm2.next=NULL;
	// mm.last=mm1.next=&mm2;
	// mm.act=mm.first=&mm1;
	
	mm.foc=0;
	tmnp=mm.first;
	do
	{
		//StoreXYWHtoRECT(&tmnp->p,cur.x+3,cur.y+(f_h+1)*mcnt+1,100,f_h+1);
		wsprintf(ews, perc_t, tmnp->nm);
		if(len<Get_WS_width(ews,FONT_SMALL)) len=Get_WS_width(ews,FONT_SMALL);
		mcnt++;
	}while(tmnp=tmnp->next);
	StoreXYWHtoRECT(&mm.p,cur.x,cur.y,len+4,(f_h+2)*mcnt+2);
	if(mm.p.x2>scr_w) StoreXYXYtoRECT(&mm.p,mm.p.x-(mm.p.x2-scr_w),mm.p.y,scr_w,mm.p.y2);
	if(mm.p.y2>scr_h) StoreXYXYtoRECT(&mm.p,mm.p.x,mm.p.y-(mm.p.y2-scr_h),mm.p.x2,scr_h);
	mcnt=0;
	tmnp=mm.first;
	do
	{
		StoreXYWHtoRECT(&tmnp->p,mm.p.x+2,mm.p.y+(f_h+2)*mcnt+2,len,f_h);
		mcnt++;
	}while(tmnp=tmnp->next);
	//StoreXYWHtoRECT(&mm1.p,cur.x+3,cur.y+3,100,f_h+1);
	//StoreXYWHtoRECT(&mm2.p,cur.x+3,cur.y+6+f_h,100,f_h+1);
  /* for(int i=Dt.icon_cnt-1; i>=0; i--)
	if((cur.x>=Dt.icon[i]->p.x)&&(cur.x<=Dt.icon[i]->p.x2)&&(cur.y>=Dt.icon[i]->p.y)&&(cur.y<=Dt.icon[i]->p.y2))
	{
		Dt.icon[i]->onEnter(i);
		i=-0;
	} */
}

void onEnter()
{
  // DT_ICON *TI=Dt.icon;
  // for(int i=0; i<Dt.icon_cnt; i++)
	// if((cur.x>=TI->p.x)&&(cur.x<=TI->p.x2)&&(cur.y>=TI->p.y)&&(cur.y<=TI->p.y2))
	// {
		// TI->onEnter();
		// i=Dt.icon_cnt;
		// if(i<Dt.icon_cnt-1) TI=TI->next;
	// }
}

void MN_OnKey(GUI_MSG *msg)
{
  int m=msg->gbsmsg->msg;
   if((m==KEY_DOWN)||(m==LONG_PRESS))
	switch(msg->gbsmsg->submess)
	{
	 case RIGHT_BUTTON:
		mm.act=mm.last;
	  break;
	 case LEFT_BUTTON:
		mm.act=mm.first;
	  break;
	 case UP_BUTTON:
		if(!(mm.act=mm.act->prev)) mm.act=mm.last;
	  break;
	 case DOWN_BUTTON:
		if(!(mm.act=mm.act->next)) mm.act=mm.first;
	  break;
	 default: return;
	}
	DirectRedrawGUI();
}

 //OnKey
static int OnKey(MAIN_GUI *data,GUI_MSG *msg)
{
  int m=msg->gbsmsg->msg;
	switch(State)
	{
	 case DT_MAIN:
	   if(m==KEY_DOWN)
		switch(msg->gbsmsg->submess)
		{
		 case RIGHT_SOFT:
			onRight();
		  return 0;
		 case ENTER_BUTTON:
		 case '5':
			if(Dt.foc) return(Dt.act->onEnter());
			else return 0;
		}
	   curkey(msg);
	  break;
	  
	 /********************************************************/
	 
	 case DT_MENU:
	   if(m==KEY_DOWN)
		switch(msg->gbsmsg->submess)
		{
		 case RIGHT_SOFT:
		 case RED_BUTTON:
			if(!MN_SEL_MOD) onRight(); // cursor
			else State=DT_MAIN;
		  break;
		 case ENTER_BUTTON:
		 case '5':
			if(!MN_SEL_MOD) // cursor
			{
			 if(!infoc(&mm.p, cur.x,cur.y)) State=DT_MAIN;
			 else if(mm.foc) return(mm.act->onEnter());
			}
			else return(mm.act->onEnter());
		  break;
		}
		if(!MN_SEL_MOD) curkey(msg); // cursor
		else MN_OnKey(msg);
		DirectRedrawGUI();
	  break;
	}
	//DirectRedrawGUI();
  return 0;
}

static const void * const gui_methods[11]={
  (void *)OnRedraw,
  (void *)OnCreate,
  (void *)OnClose,
  (void *)OnFocus,
  (void *)OnUnfocus,
  (void *)OnKey,
  0,
  (void *)kill_data, //method7, //Destroy
  (void *)int_0,
  (void *)int_0,
  0
};

static void maincsm_oncreate(CSM_RAM *data)
{
  static const RECT Canvas={0,0,0,0};
  //MAIN_CSM *csm=(MAIN_CSM*)data;
  StoreXYXYtoRECT((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
//  view_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  /* csm->csm. */data->state=0;
  /* csm->csm.. */data->unk1=0;
  /* csm->gui_id= */MAINGUI_ID=CreateGUI(main_gui);
}

static void maincsm_onclose(CSM_RAM *data)
{
	//data=olddata;
	
        // LockSched();
        // CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
        // memcpy(&icsmd,icsm->constr,sizeof(icsmd));
        //memcpy(&oldcsmd,icsm->constr,sizeof(oldcsmd));
        //old_icsm_onClose=icsmd.onClose;
        // icsmd.onMessage=oldcsmd.onMessage;
        // icsmd.onCreate=oldcsmd.onCreate;
        // icsmd.onClose=oldcsmd.onClose;
		
        // old_icsm_onClose=icsmd.onClose;
		// old_icsm_onCreate=icsmd.onCreate;
		// old_icsm_onMessage=icsmd.onMessage;
		
        // icsm->constr=&oldcsmd;
        // icsm=&oldicsm;
        // UnlockSched();
	
  //SUBPROC((void *)Killer);
}



//static IPC_REQ gipc;
const char ipc_my_name[]=IPC_DT_NAME;

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

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
	int rtn=1;
	
	if(idle_ch)
	{
	 if(firstmsg)
	 {
		#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
		CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
		// if (IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))/*&&IsUnlocked()*/ //Если IdleGui на самом верху
		// {
			// OLDIDLE=malloc(sizeof(GUI));
			// GUI* tempg=GetTopGUI();
			// memcpy(OLDIDLE, tempg, sizeof(GUI));
			// if (igui) //И он существует
			// {
			// }
		// }
		static const RECT Canvas={0,0,0,0};
		//MAIN_CSM *csm=(MAIN_CSM*)data;
		StoreXYXYtoRECT((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
		MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
		zeromem(main_gui,sizeof(MAIN_GUI));
		main_gui->gui.canvas=(void *)(&Canvas);
		//  view_gui->gui.flag30=2;
		main_gui->gui.methods=(void *)gui_methods;
		main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
		// data->state=0;
		// data->unk1=0;
		MAINGUI_ID=CreateGUI_ID(main_gui,idlegui_id);
		firstmsg=0;
	  //maincsm_oncreate(data);
	 }
	 rtn=old_icsm_onMessage(data, msg);
	}
	else if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==MAINGUI_ID))
		{
			/* csm->csm.. */data->state=-3;
		}


  if(msg->msg == MSG_RECONFIGURE_REQ) // Перечитывание конфига по сообщению
  {
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
		InitConfig();
		ShowMSG(1,(int)"DeskTop config updated!");
    }
  }
	
	
	/* MAIN_CSM *csm;
	if(firstmsg)
	{
		olddata=data;
		csm=malloc(sizeof(MAIN_CSM));
		memcpy(&csm->csm, data, sizeof(CSM_RAM));
		data=(CSM_RAM*)csm;
	}
	else */
	//{
	   //MAIN_CSM *csm=(MAIN_CSM*)data;
	//}
	
	// if (msg->msg==MSG_IPC)
	// {
		// IPC_REQ *ipc;
		// if ((ipc=(IPC_REQ*)msg->data0))
		// {
			// if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
			// {
					// DT_ICON *ti;
					// DT_ICON *tti;
					// DT_ICON *TI=Dt.icon;
				// switch (msg->submess)
				// {
				 // case IPC_NPLG:
					// ti=(DT_ICON*)ipc->data;
					// if(ti->d!=0xFF)
					// {
						// for(int i=0; i<ti->d; i++) TI=TI->next;
						// tti=malloc(sizeof(DT_ICON));
						// memcpy(tti, TI, sizeof(DT_ICON));
						// mfree(TI);
						// TI=ti;
						// Dt.icon[ti->d]->inf=malloc(256);
						// zeromem(Dt.icon[v-1]->inf, 256);
						// TI->p=tti->p;
						// TI->nm=tti->nm;
						// TI->fl=tti->fl;
						// TI->img=tti->img;
						//Dt.icon[ti->d]->inf=Dt.icon[Dt.icon_cnt]->inf;
				// TI->inf=malloc(256);
				// zeromem(TI->inf, 256);
						// mfree(tti);
						// TI->d=0;
					// }
					// else
					// {
						// TI=ipc->data;
						// TI->inf=malloc(256);
						// zeromem(TI->inf, 256);
						// TI->next=Dt.icon;
						// Dt.icon=TI;
						// Dt.icon_cnt++;
					// }
					// DirectRedrawGUI();
				  // break;
				// }
			// }
		// }
	// }
	
	
	
	
  return(rtn);
}

static unsigned short maincsm_name_body[140];

static const struct
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
  sizeof(CSM_RAM),
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"DeskTop");
}


int main(char *exename, char *fname)
{
	//SF.fl=malloc(strlen(fname));
	//sprintf(SF.fl,fname);
	InitConfig();
	
	if(CH_IDLE)
	{
		idle_ch=1;
        CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
		icsmd=malloc(sizeof(CSM_DESC));
        LockSched();
        memcpy(icsmd,icsm->constr,sizeof(icsmd));
        //memcpy(&oldcsmd,icsm->constr,sizeof(oldcsmd));
        //memcpy(&oldicsm,icsm,sizeof(CSM_RAM));
		
		old_icsm_onMessage=icsmd->onMessage;
		
        icsmd->onMessage=maincsm_onmessage;
        //icsmd.onCreate=maincsm_oncreate;
        //icsmd.onClose=maincsm_onclose;
		oldcsmd=icsm->constr;
        icsm->constr=icsmd;
        UnlockSched();
    }
	else
	{
	 UpdateCSMname();
	 LockSched();
	 char dummy[sizeof(CSM_RAM)];
	 MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
	 UnlockSched();
	}
	
	
	
  return 0;
}
