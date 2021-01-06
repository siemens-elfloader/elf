
void UpdateDAEMONname(char *txt);

#ifdef ELKA
 int tab_h=112, tab1_h=14;
#else
 int tab_h=56, tab1_h=7;
#endif
 
extern const char pic_folder[128];
const char perc_s[]="%s%s";
int M_ICONS[7];
char pic_new[128];
char pic_in[128];
char pic_out[128];
char pic_draft[128];
char pic_stat[128];
char pic_config[128];
char pic_menu[128];

static void _GUIRedraw(MAIN_GUI *data) //Redraw
{
  if(data->gui.state==2)
  {
    DrawRectangle(0,YDISP, scr_w,scr_h, 0,black,black);
    //DrawRectangle(scr_w/2-100,YDISP+20, scr_w/2+100,YDISP+220, 0,white,NULL);
    int t_x=scr_w/2-tab_h;
    int t_y=YDISP+tab1_h;
    for(int i=0; i<0x10; i++)
      for(int j=0; j<0x10; j++)
      {
        switch(SMSD[i*0x10+j].type)
        {
        case TYPE_IN:
          DrawRectangle(t_x+j*tab1_h,t_y+i*tab1_h, t_x+j*tab1_h+tab1_h, t_y+i*tab1_h+tab1_h, 0,yellow,blue);
          break;
        case TYPE_OUT:
          DrawRectangle(t_x+j*tab1_h,t_y+i*tab1_h, t_x+j*tab1_h+tab1_h, t_y+i*tab1_h+tab1_h, 0,yellow,green);
          break;
        case TYPE_DRAFT:
          DrawRectangle(t_x+j*tab1_h,t_y+i*tab1_h,  t_x+j*tab1_h+tab1_h, t_y+i*tab1_h+tab1_h, 0,yellow,white);
          break;
        default:
          DrawRectangle(t_x+j*tab1_h,t_y+i*tab1_h, t_x+j*tab1_h+tab1_h, t_y+i*tab1_h+tab1_h, 0,yellow,NULL);
          break;
        }
        if(i*0x10+j+1>=scnt.all) j=i=0x10;
      }
    //DrawRectangle(5,YDISP+5+tab1_h+(tab_h*2), 5+sf_h-2, YDISP+5+tab1_h+(tab_h*2)+sf_h-1, 0,white,blue);
    //DrawRectangle(5,YDISP+5+tab1_h+(tab_h*2)+sf_h+1, 5+sf_h-2, YDISP+5+tab1_h+(tab_h*2)+2*sf_h-1, 0,white,green);
    //DrawRectangle(5,YDISP+5+tab1_h+(tab_h*2)+2*sf_h+1, 5+sf_h-2, YDISP+5+tab1_h+(tab_h*2)+3*sf_h-1, 0,white,white);
    //DrawRectangle(scr_w/2-tab_h+j*tab1_h,YDISP+tab1_h+i*tab1_h, scr_w/2-tab_h+j*tab1_h+20, YDISP+tab1_h+i*tab1_h+tab1_h, 0,white,NULL);
    //wsprintf(ws, perc_t, "Входящие\nИсходящие\nЧерновик");
    //DrawString(ws, 5+sf_h,YDISP+5+tab1_h+(tab_h*2)+1, scr_w,scr_h, FONT_SMALL, 1, white, NULL);
  }
}

static void _GUICreate(MAIN_GUI *data,void *(*malloc_adr)(int)) //Create
{
  //scr_h=ScreenH()-1; // высота экрана
  //scr_w=ScreenW()-1; // нирина экрана
  data->gui.state=1;
}

static void _GUIClose(MAIN_GUI *data,void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

static void _GUIFocus(MAIN_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
  DisableIDLETMR(); // чтоб эльф не закрывался через 2 минуты
  data->gui.state=2;
}

static void _GUIUnfocus(MAIN_GUI *data,void (*mfree_adr)(void *))
{
  if (data->gui.state!=2)
    return;
  data->gui.state=1;
}

static int _GUIOnKey(MAIN_GUI *data,GUI_MSG *msg)
{
  int m=msg->gbsmsg->msg;
  switch(m)
  {
  case KEY_DOWN: // момент нажатия клавиши
  case LONG_PRESS: // длинное нажатие
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT:
    case RED_BUTTON:
      return 1;
    }
    DirectRedrawGUI();
  }
  return 0;
}

static int met0(void){return(0);}
static const void * const gui_methods[11]=
{
  (void *)_GUIRedraw,
  (void *)_GUICreate,
  (void *)_GUIClose,
  (void *)_GUIFocus,
  (void *)_GUIUnfocus,
  (void *)_GUIOnKey,
  0,
  (void *)kill_data, //method7, //Destroy
  (void *)met0,
  (void *)met0,
  0
};

const RECT Canvas={0,0,0,0};

void stat()
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  //MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  //main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  //csm->csm.state=0;
  //csm->csm.unk1=0;
  /*maingui_id=csm->gui_id=*/CreateGUI(main_gui);
}

// extern static volatile CLIST *cltop; //Начало
// extern static void ConstructList(void)
// #include "adreslist.h"
extern void ConstructList(void);
extern void FreeCLIST(void);
extern int Cont_list(void *ed_gui, int n);
extern int FindNameByNum(SMS_DATA *dat, WSHDR *num);

SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)""},
  {0x0001,0x0000,(int)LG_QUIT},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
	menu_sk,0
};

void ed1_locret(void){}

// void optmenu_ghook(void *data, int cmd)
// {
// 	if (cmd==TI_CMD_FOCUS)
// 	{
// 		DisableIDLETMR();
// 	}
// 	if (cmd==TI_CMD_DESTROY)
// 	{
// 		if(nemuRestart)
// 		{
// 			Cont_list(edsms_gui, tnomm);
// 		}
// 		else nemuRestart=1;
// 	}
// }
// 
// static void optmenuitemhandler(void *data, int curitem, void *unk)
// {
// 	WSHDR *ws0;
// 	void *item=AllocMenuItem(data);
// 	extern const char percent_t[];
// 	ws0=AllocMenuWS(data,30);
// 	CLIST *cl0=(CLIST *)MenuGetUserPointer(data);
// 	int j=0;
// 	for(int i=0; i<NUMBERS_MAX; i++)
// 		if(j<curitem)
// 	{
// 		if(cl0->num[i]) j++;
// 	}
// 	else if(cl0->num[i])
// 	{
// 		wstrcat(ws0, cl0->num[i]);
// 		i=NUMBERS_MAX;
// 	}
// 	
// 	SetMenuItemText(data, item, ws0, curitem);
// }
// 
// static int optmenu_keyhook(void *data, GUI_MSG *msg)
// {
// 	if ((msg->keys==0x18)||(msg->keys==0x3D))
// 	{
// 		int curitem=GetCurMenuItem(data);
// 		CLIST *cl0=(CLIST *)MenuGetUserPointer(data);
// 		int j=0;
// 		for(int i=0; i<NUMBERS_MAX; i++)
// 			if(j<curitem)
// 		{
// 			if(cl0->num[i]) j++;
// 		}
// 		else if(cl0->num[i])
// 		{
// 			nemuRestart=0;
// 			return add_to_num(cl0->num[i]);
// 		}
// 	}
// 	return(0);
// }
// 
// 
// static const MENU_DESC optmenu=
// {
// 	8,
//  optmenu_keyhook,
//  optmenu_ghook,
//  NULL,
//  optenusoftkeys,
//  &menu_skt,
//  0x10,//MENU_FLAG,
//  optmenuitemhandler,
//  NULL,//menuitems,
//  NULL,//menuprocs,
//  0
// };
// 
// void options_menu(CLIST *cl0, int n, int cnt)
// {
// // 	ws_2str(cl0->name, nmtxt, cl0->name->wsbody[0]);
// 	patch_header(&optmenuhdr);
// 	CreateMenu(0,0,&optmenu,&optmenuhdr,j,cnt,cl0,0);
// }

typedef struct
{
	char num[32];
	WSHDR *ws;
	void *up;
}OUT_SMS;

// SOFTKEY_DESC outsms_sk[]=
// {
// 	{0x0018,0x0000,(int)"Открыть"},
// 	{0x0001,0x0000,(int)"Отмена"},
// 	{0x003D,0x0000,(int)LGP_DOIT_PIC}
// };
// 
// SOFTKEYSTAB outsms_skt=
// {
// 	outsms_sk,0
// };

int edit_sms(char *n, WSHDR *m, char *num);
static const SOFTKEY_DESC sk_cancel={0x0FFF,0x0000,(int)LG_CANSEL};
static const SOFTKEY_DESC sk_send0={0x0FFF,0x0000,(int)LG_SEND};
static const SOFTKEY_DESC sk_send={0x0FF0,0x0000,(int)LG_SEND};

int outsms_onkey(GUI *data, GUI_MSG *msg)
{
  if(msg->keys==0xFFF) return 1;
  if(msg->keys==0xFF0)
  {
    OUT_SMS *t=EDIT_GetUserPointer(data);
    SendSMS(t->ws,t->num,MMI_CEPID,MSG_SMS_RX-1,6);
    //FreeWS(t->ws);
    t->ws=NULL;
    return 1;
  }
  //-1 - do redraw
  return(0); //Do standart keys
  //1: close
}

void outsms_ghook(GUI *data, int cmd)
{
  OUT_SMS *t;
  switch(cmd)
  {
  case TI_CMD_FOCUS:
    DisableIDLETMR();
    break;
  case TI_CMD_REDRAW:
    SetSoftKey(data,&sk_cancel,SET_SOFT_KEY_N);
    SetSoftKey(data,&sk_send,SET_SOFT_KEY_N==0?1:0);
    break;
  case TI_CMD_DESTROY:
    t=EDIT_GetUserPointer(data);
    if(t->ws)
      edit_sms(t->up, t->ws, t->num);
    break;
  }
}

HEADER_DESC outsms_hdr={0,0,0,0,NULL,NULL,LGP_NULL};

INPUTDIA_DESC outsms_desc=
{
	1,
 outsms_onkey,
 outsms_ghook,
 (void *)ed1_locret,
  0,
  &menu_skt,
  {0,0,0,0},
  FONT_SMALL,
  100,
  101,
  0,

//  0x00000001 - Выровнять по правому краю
//  0x00000002 - Выровнять по центру
//  0x00000004 - Инверсия знакомест
//  0x00000008 - UnderLine
//  0x00000020 - Не переносить слова
//  0x00000200 - bold
  2,

//  0x00000002 - ReadOnly
//  0x00000004 - Не двигается курсор
  0x40000000 // Поменять местами софт-кнопки
};

int outsms_ed(OUT_SMS *t)
{
	void *ma=malloc_adr();
	void *eq;
	EDITCONTROL ec;
	EDITC_OPTIONS ec_options;

	PrepareEditControl(&ec);
	eq=AllocEQueue(ma,mfree_adr());
	
// 	if(IN_SMSD.type!=TYPE_IN) return 0;
	
	outsms_hdr.lgp_id=(int)LG_SENDQ;
	
// 	Time
// 	wsprintf(ews,perc_t,IN_SMSD.Time);
// 	ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,ews->wsbody[0]);
// 	PrepareEditCOptions(&ec_options);
// 		SetPenColorToEditCOptions(&ec_options,2);
// 	SetAlignToEditCOptions(&ec_options,TEXT_ALIGNMIDDLE);
// 	SetFontToEditCOptions(&ec_options,2);
// 	CopyOptionsToEditControl(&ec,&ec_options);
// 	AddEditControlToEditQend(eq,&ec,ma);
	
	SMS_LEN *l=smslen(t->ws);
	
	wsprintf(ews,"%d SMS\n(%d %t)\n",l->cnt,l->len,LG_LETTERS);
	ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,ews->wsbody[0]);
	PrepareEditCOptions(&ec_options);
// 	SetPenColorToEditCOptions(&ec_options,4);
// 	SetAlignToEditCOptions(&ec_options,TEXT_ALIGNMIDDLE);
	SetFontToEditCOptions(&ec_options,4);
	CopyOptionsToEditControl(&ec,&ec_options);
	AddEditControlToEditQend(eq,&ec,ma);
	
	mfree(l);
	
// 	Number
	wsprintf(ews,perc_t,t->num);
	SMS_DATA *tsms=malloc(sizeof(SMS_DATA));
	if(FindNameByNum(tsms, ews))
	{
		wsAppendChar(ews,'\n');
		wstrcat(ews, tsms->name);
	}
	mfree(tsms);
	ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,ews->wsbody[0]);
	PrepareEditCOptions(&ec_options);
	SetFontToEditCOptions(&ec_options,3);
// 	SetAlignToEditCOptions(&ec_options,TEXT_ALIGNMIDDLE);
	CopyOptionsToEditControl(&ec,&ec_options);
	AddEditControlToEditQend(eq,&ec,ma);
	
        strcpy(pic_new,pic_folder);
        strcat(pic_new,"new.png");
        M_ICONS[0]=(int)pic_new;
        outsms_hdr.icon=M_ICONS+0;
        
	patch_header(&outsms_hdr);
	patch_input(&outsms_desc);
	return CreateInputTextDialog(&outsms_desc,&outsms_hdr,eq,1,t);
}

void tr_options(USR_MENU_ITEM *item)
{
  if (item->type==0)
  {
    switch(item->cur_item)
    {
    case 0:
      wsprintf(item->ws,perc_t,LG_TRANSLIT);
      break;
    }
  }
  if (item->type==1)
  {
    switch(item->cur_item)
    {
    case 0:
      add_translit(item->user_pointer);
      //Cont_list(item->user_pointer, 0);
      //open_select_file_gui(item->user_pointer, 0);
      break;
    }
  }   
}

void nom_options(USR_MENU_ITEM *item)
{
  if (item->type==0)
  {
    switch(item->cur_item)
    {
    case 0:
      wsprintf(item->ws,perc_t,LG_ADRBOOK);
      break;
    }
  }
  if (item->type==1)
  {
    switch(item->cur_item)
    {
    case 0:
      Cont_list(item->user_pointer, 0);
      //open_select_file_gui(item->user_pointer, 0);
      break;
    }
  }   
}


// void log_outsms(WR_SMS_DATA *logdata)
// {
// 	unsigned int ul;
// 	int f=fopen("4:\\sms\\out.smsd", A_ReadWrite+A_Create+A_Append+A_BIN, P_READ+P_WRITE, &ul);
// 	if (f!=-1)
// 	{
// 		logdata->sz=sizeof(WR_SMS_DATA)-2+2*logdata->TXT->wsbody[0];
// 		fwrite(f,logdata,sizeof(WR_SMS_DATA)-4,&ul);
// 		fwrite(f,logdata->TXT->wsbody,2+2*logdata->TXT->wsbody[0],&ul);
// 		fclose(f,&ul);
// 		ShowMSG(1,(int)"Saved");
// 	}
// // 	mfree(txt);
// }
// 
// TDate date;
// TTime time;

int ed_sms_onkey(GUI *data, GUI_MSG *msg)
{
  EDITCONTROL ec;
  char txtpos;
  if(EDIT_GetUserPointer(data)) txtpos=6;
  else txtpos=4;
  //char tmp[32];
  //WSHDR *tws;
  //WR_SMS_DATA tempsms;
  //const char *snum=EDIT_GetUserPointer(data);
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    if ((msg->gbsmsg->submess==GREEN_BUTTON)||(msg->keys==0xFFF))
    {
      ExtractEditControl(data,2,&ec);
      if(!wstrlen(ec.pWS))
      {
        EDIT_SetFocus(data, 2);
        MsgBoxError(1, (int)LG_ENT_NUM);
        return -1;
      }
      OUT_SMS *tmp=malloc(sizeof(OUT_SMS));
      zeromem(tmp,sizeof(OUT_SMS));
      ws_2str(ec.pWS, tmp->num, wstrlen(ec.pWS));
      /*if(EDIT_GetUserPointer(data)) ExtractEditControl(data,6,&ec);
      else */ExtractEditControl(data,txtpos,&ec);
      if(!wstrlen(ec.pWS))
      {
        /*if(EDIT_GetUserPointer(data)) EDIT_SetFocus(data, 6);
        else */EDIT_SetFocus(data, txtpos);
        mfree(tmp);
        MsgBoxError(1, (int)LG_ENT_TEXT);
        return -1;
      }
      tmp->ws=AllocWS(ec.pWS->wsbody[0]);
      wstrcpy(tmp->ws,ec.pWS);
      tmp->up=EDIT_GetUserPointer(data);
      outsms_ed(tmp);
      //memcpy(tempsms.Number, tmp, 32);
      //GetDateTime(&date, &time);
      //sprintf(tempsms.Time, "%02d.%02d.&02d %02d:%02d:&02d",
      //date.day,date.month,date.year%100, time.hour,time.min,time.sec );
      //tempsms.TXT=tws;
      //SUBPROC((void*)log_outsms, &tempsms);
      //SendSMS(tws,tmp,MMI_CEPID,MSG_SMS_RX-1,6);
      return(1);
    }
    if (msg->gbsmsg->submess==ENTER_BUTTON)
    {
      if(EDIT_GetFocus(data)==2)
      {
        EDIT_OpenOptionMenuWithUserItems(data,nom_options,data,1);
        return (-1);
      }
      //ConstructList();
      if(EDIT_GetFocus(data)==txtpos)
      {
        EDIT_OpenOptionMenuWithUserItems(data,tr_options,data,1);
        return (-1);
      }
    }
  }
  //-1 - do redraw
  return(0); //Do standart keys
  //1: close
}

void ed_sms_ghook(GUI *data, int cmd)
{
//  static SOFTKEY_DESC sk={0x0018,0x0000,(int)"Menu"};
// 	static const SOFTKEY_DESC sk_cancel={0x0FF0,0x0000,(int)LG_CLOSE};
	EDITCONTROL ec;
// 	EDITC_OPTIONS ec_options;
// 	int cnt, len;
	switch(cmd)
	{
		case TI_CMD_CREATE:
			if(EDIT_GetUserPointer(data)) EDIT_SetFocus(data, 6);
			else EDIT_SetFocus(data, 4);
			break;
		case TI_CMD_FOCUS:
			DisableIDLETMR();
			break;
		case TI_CMD_REDRAW:
			SetSoftKey(data,&sk_send0,SET_SOFT_KEY_N);
			if(EDIT_GetUserPointer(data))
			{
				if((EDIT_GetFocus(data)==6))
				{
					ExtractEditControl(data,6,&ec);
					SMS_LEN *l=smslen(ec.pWS);
					wsprintf(ws, "%t(%d/%d):", LG_ANSWER, l->len, l->cnt);
					mfree(l);
					EDIT_SetTextToEditControl(data,5,ws);
				}
			}
			else if(EDIT_GetFocus(data)==4)
			{
				ExtractEditControl(data,4,&ec);
				SMS_LEN *l=smslen(ec.pWS);
				wsprintf(ws, "%t(%d/%d):", LG_MESS, l->len, l->cnt);
				mfree(l);
				EDIT_SetTextToEditControl(data,3,ws);
			}
			break;
	}
}

HEADER_DESC ed_sms_hdr={0,0,0,0,NULL,NULL,LGP_NULL};

INPUTDIA_DESC ed_sms_desc=
{
	1,
 ed_sms_onkey,
 ed_sms_ghook,
 (void *)ed1_locret,
  0,
  &menu_skt,
  {0,0,0,0},
  FONT_SMALL,
  100,
  101,
  0,

//  0x00000001 - Выровнять по правому краю
//  0x00000002 - Выровнять по центру
//  0x00000004 - Инверсия знакомест
//  0x00000008 - UnderLine
//  0x00000020 - Не переносить слова
//  0x00000200 - bold
  0,

//  0x00000002 - ReadOnly
//  0x00000004 - Не двигается курсор
  0x40000000 // Поменять местами софт-кнопки
};

int edit_sms(char *n, WSHDR *m, char *num)
{
	void *ma=malloc_adr();
	void *eq;
	EDITCONTROL ec;
	EDITC_OPTIONS ec_options;

	PrepareEditControl(&ec);
	eq=AllocEQueue(ma,mfree_adr());
	
	if(n) ed_sms_hdr.lgp_id=(int)LG_ANSWER;
	else ed_sms_hdr.lgp_id=(int)LG_NEW_SMS;
	
	wsprintf(ews,perc_t,LG_TO);
	ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,ews->wsbody[0]);
	PrepareEditCOptions(&ec_options);
	SetPenColorToEditCOptions(&ec_options,2);
	SetFontToEditCOptions(&ec_options,2);
	CopyOptionsToEditControl(&ec,&ec_options);
	AddEditControlToEditQend(eq,&ec,ma);
	
// 	Number
	if(n) wsprintf(ews,perc_t,SMSD[*n].Number);
	else if(num) wsprintf(ews,perc_t,num);
	else wsprintf(ews,perc_t,"");
	ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_DEFAULT_DIGIT+ECF_APPEND_EOL,ews,32);
	PrepareEditCOptions(&ec_options);
	SetFontToEditCOptions(&ec_options,1);
	CopyOptionsToEditControl(&ec,&ec_options);
	AddEditControlToEditQend(eq,&ec,ma);
	
	
	
	if(n)
	{
		wsprintf(ews,perc_tp,LG_MESS);
		ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,ews->wsbody[0]);
		PrepareEditCOptions(&ec_options);
		SetPenColorToEditCOptions(&ec_options,2);
		SetFontToEditCOptions(&ec_options,2);
		CopyOptionsToEditControl(&ec,&ec_options);
		AddEditControlToEditQend(eq,&ec,ma);
	
	// 	text
// 		wsprintf(ews,perc_t,n->SMS_TEXT);
		WSHDR *tws;
		unsigned short sz=0;
		if(SMSD[*n].cnt>1)
		{
			for(int i=0; i<SMSD[*n].cnt; i++)
				sz+=SMSD[*n].SMS_TEXT->wsbody[0];
			tws=AllocWS(sz);
			zeromem(tws->wsbody, sz*2);
// 		memcpy(tws->wsbody, SMSD[*n].SMS_TEXT->wsbody,SMSD[*n].SMS_TEXT->wsbody[0]);
			for(int i=0; i<SMSD[*n].cnt; i++)
				if(n[i]==0xff)
			{
				wsprintf(ws,ppp2);
				wstrcat(tws, ws);
				i=SMSD[*n].cnt;
			}
			else wstrcat(tws, SMSD[n[i]].SMS_TEXT);
		}
		else tws=SMSD[*n].SMS_TEXT;
		
		ConstructEditControl(&ec,4, ECF_APPEND_EOL, tws,tws->wsbody[0]);
		PrepareEditCOptions(&ec_options);
		SetFontToEditCOptions(&ec_options,1);
		CopyOptionsToEditControl(&ec,&ec_options);
		AddEditControlToEditQend(eq,&ec,ma);
	}

	if(n) wsprintf(ews,perc_tp,LG_ANSWER);
	else wsprintf(ews,perc_tp,LG_MESS);
	ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,ews->wsbody[0]+7);
	PrepareEditCOptions(&ec_options);
	SetPenColorToEditCOptions(&ec_options,2);
	SetFontToEditCOptions(&ec_options,2);
	CopyOptionsToEditControl(&ec,&ec_options);
	AddEditControlToEditQend(eq,&ec,ma);

// 	text
	wsprintf(ews,perc_t,"");
	if(m) ConstructEditControl(&ec,4, ECF_APPEND_EOL, m,1024);
	else ConstructEditControl(&ec,4, ECF_APPEND_EOL, ews,1024);
	PrepareEditCOptions(&ec_options);
	SetFontToEditCOptions(&ec_options,1);
	CopyOptionsToEditControl(&ec,&ec_options);
	AddEditControlToEditQend(eq,&ec,ma);
	
// 	else wsprintf(ews,perc_t,"");
        
        strcpy(pic_new,pic_folder);
        strcat(pic_new,"new.png");
        M_ICONS[0]=(int)pic_new;
        ed_sms_hdr.icon=M_ICONS+0;
	
	patch_header(&ed_sms_hdr);
	patch_input(&ed_sms_desc);

	return CreateInputTextDialog(&ed_sms_desc,&ed_sms_hdr,eq,1,n);
}


// void delsms(char n)
// {
// 	int f;
// 	unsigned int er;
// 	char *smsdat;
// 	int psz=sizeof(PDU);
// 	if ((f=fopen("0:\\system\\sms\\sms.dat", A_ReadWrite+A_Truncate,P_READ+P_WRITE,&er))!=-1)
// 	{
// // 		lseek(f, 2, 0, &er, &er);
// 		smsdat=malloc(psz*100+2);
// 		fread(f,smsdat,psz*100+2,&er);
// 		for(int i=0; i<psz; i++)
// 			smsdat[n*psz+2+i]=0xff;
// 		fwrite(f,smsdat,psz*100+2,&er);
// 		fclose(f,&er);
// // 		for(int i=0; i<100; i++) GetSMSData(&SMSD[i], (PDU*)smsdat+i);
// 		mfree(smsdat);
// 	}
// 	else
// 		ShowMSG(1, (int)"ЖОПА!");
// }


// SOFTKEY_DESC menu_sk[]=
// {
// 	{0x0018,0x0000,(int)"Опции"},
// 	{0x0001,0x0000,(int)"Выход"},
// 	{0x003D,0x0000,(int)LGP_DOIT_PIC}
// };
// 
// SOFTKEYSTAB menu_skt=
// {
// 	menu_sk,0
// };
// 
// void ed1_locret(void){}

int ed1_onkey(GUI *data, GUI_MSG *msg)
{
// 	EDITCONTROL ec;
	char *n;
	if (msg->gbsmsg->msg==KEY_DOWN)
	{
		int m=msg->gbsmsg->submess;
		if ((m==GREEN_BUTTON)||(msg->keys==0xFFF))
		{
			n=EDIT_GetUserPointer(data);
			if(SMSD[*n].type==TYPE_IN)
			{
				edit_sms(n, 0, 0);
			}
		}
// 		if(m=='#')
// 		{
// 			n=EDIT_GetUserPointer(data);
// 			delsms(*n);
// 		}
	}
  //-1 - do redraw
	return(0); //Do standart keys
  //1: close
}

void ed1_ghook(GUI *data, int cmd)
{
	static const SOFTKEY_DESC sk={0x0FFF,0x0000,(int)LG_ANSWER};
	static const SOFTKEY_DESC sk0={0x0FFF,0x0000,(int)""};
	if (cmd==TI_CMD_FOCUS)
	{
		DisableIDLETMR();
	}
	if (cmd==TI_CMD_REDRAW)
	{
		char *n=EDIT_GetUserPointer(data);
		if(SMSD[*n].type==TYPE_IN) SetSoftKey(data,&sk,SET_SOFT_KEY_N);
		else SetSoftKey(data,&sk0,SET_SOFT_KEY_N);
	}
//  static SOFTKEY_DESC sk={0x0018,0x0000,(int)"Menu"};
// 	EDITCONTROL ec;
// 	int i;
// 	if (cmd==2)
// 	{
//     //Create
// 		edit_data=data;
// 		GBS_StartTimerProc(&mytmr,216/4,TestTimerProc);
// 	}
// 	if (cmd==3)
// 	{
// 		edit_data=NULL;
// 		GBS_DelTimer(&mytmr);
// 	}
// 	if (cmd==7)
// 	{
    //OnRun
//    SetSoftKey(data,&sk,1);
// 		ExtractEditControl(data,3,&ec);
// 		wstrcpy(ews,ec.pWS);
// 	}
// 	if (cmd==0x0D)
// 	{
    //onCombo
// 		if ((i=EDIT_GetItemNumInFocusedComboBox(data)))
// 		{
// 			wsprintf(ews,"%t%d","Пункт: ",i);
// 		}
// 		else
// 		{
// 			ExtractEditControl(data,EDIT_GetFocus(data)-1,&ec);
// 			wstrcpy(ews,ec.pWS);
// 		}
// 		EDIT_SetTextToFocused(data,ews);
// 	}
}

HEADER_DESC ed1_hdr={0,0,0,0,NULL,NULL,LGP_NULL};

INPUTDIA_DESC ed1_desc=
{
	1,
 ed1_onkey,
 ed1_ghook,
 (void *)ed1_locret,
  0,
  &menu_skt,
  {0,0,0,0},
  FONT_SMALL,
  100,
  101,
  0,

//  0x00000001 - Выровнять по правому краю
//  0x00000002 - Выровнять по центру
//  0x00000004 - Инверсия знакомест
//  0x00000008 - UnderLine
//  0x00000020 - Не переносить слова
//  0x00000200 - bold
  0,

//  0x00000002 - ReadOnly
//  0x00000004 - Не двигается курсор
  0x40000000 // Поменять местами софт-кнопки
};

int read_sms(char *n, char full)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  EDITC_OPTIONS ec_options;
  
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
	
  if(SMSD[*n].type==TYPE_OUT)
  {
    ed1_hdr.lgp_id=(int)LG_OUTCOM;
    wsprintf(ews,perc_t,LG_TO);
  }
  else if(SMSD[*n].type==TYPE_IN)
  {
    ed1_hdr.lgp_id=(int)LG_INCOM;
    //Time
    wsprintf(ews,perc_t,SMSD[*n].Time);
    ConstructEditControl(&ec,ECT_READ_ONLY,ECF_APPEND_EOL,ews,ews->wsbody[0]);
    PrepareEditCOptions(&ec_options);
    //SetPenColorToEditCOptions(&ec_options,2);
    SetFontToEditCOptions(&ec_options,1);
    //SetAlignToEditCOptions(&ec_options,TEXT_UNDERLINE);
    CopyOptionsToEditControl(&ec,&ec_options);
    AddEditControlToEditQend(eq,&ec,ma);
		
    wsprintf(ews,perc_t,LG_FROM);
  }
  else
  {
    wsprintf(ews,perc_t,LG_DRAFT);
    wsprintf(ews,perc_t,LG_TO);
  }
  //from/to
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,ews->wsbody[0]);
  PrepareEditCOptions(&ec_options);
  SetPenColorToEditCOptions(&ec_options,2);
  SetFontToEditCOptions(&ec_options,2);
  CopyOptionsToEditControl(&ec,&ec_options);
  AddEditControlToEditQend(eq,&ec,ma);
	
  //Number
  wsprintf(ews,perc_t,SMSD[*n].Number);
  if(SMSD[*n].name)
  {
    wsAppendChar(ews,'\n');
    //wstrcat(ews, "\n");
    wstrcat(ews, SMSD[*n].name);
  }
  ConstructEditControl(&ec,ECT_READ_ONLY,ECF_APPEND_EOL,ews,ews->wsbody[0]);
  PrepareEditCOptions(&ec_options);
  SetFontToEditCOptions(&ec_options,1);
  CopyOptionsToEditControl(&ec,&ec_options);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,perc_tp,LG_MESS);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,ews->wsbody[0]);
  PrepareEditCOptions(&ec_options);
  SetPenColorToEditCOptions(&ec_options,2);
  SetFontToEditCOptions(&ec_options,2);
  CopyOptionsToEditControl(&ec,&ec_options);
  AddEditControlToEditQend(eq,&ec,ma);

  //text
  WSHDR *tws;
  unsigned short sz=0;
  if(SMSD[*n].cnt>1)
  {
    for(int i=0; i<SMSD[*n].cnt; i++)
      sz+=SMSD[*n].SMS_TEXT->wsbody[0];
    tws=AllocWS(sz);
    zeromem(tws->wsbody, sz*2);
    //memcpy(tws->wsbody, SMSD[*n].SMS_TEXT->wsbody,SMSD[*n].SMS_TEXT->wsbody[0]);
    for(int i=0; i<SMSD[*n].cnt; i++)
      if(n[i]==0xff)
      {
        wsprintf(ws,ppp2);
        wstrcat(tws, ws);
        i=SMSD[*n].cnt;
      }
      else wstrcat(tws, SMSD[n[i]].SMS_TEXT);
  }
  else tws=SMSD[*n].SMS_TEXT;
	
  ConstructEditControl(&ec,4, ECF_APPEND_EOL, tws,tws->wsbody[0]);
  PrepareEditCOptions(&ec_options);
  SetFontToEditCOptions(&ec_options,1);
  CopyOptionsToEditControl(&ec,&ec_options);
  AddEditControlToEditQend(eq,&ec,ma);
  
  strcpy(pic_new,pic_folder);
  strcat(pic_new,"new.png");
  M_ICONS[0]=(int)pic_new;
  ed1_hdr.icon=M_ICONS+0;
	
  patch_header(&ed1_hdr);
  patch_input(&ed1_desc);

  return CreateInputTextDialog(&ed1_desc,&ed1_hdr,eq,1,n);
}

char menuhdrtxt[32];
HEADER_DESC menuhdr={0,0,131,21,NULL,NULL,LGP_NULL};
int menusoftkeys[]={0,1,2};

const int S_ICONS[6]={0,0,0,0,0,0};

int menu_in_onkey(void *data, GUI_MSG *msg);
void menu_in_ghook(void *data, int cmd);
void menu_in_iconhndl(void *data, int curitem, void *unk);

static const ML_MENU_DESC menu_in=
{
 8,
 menu_in_onkey,
 menu_in_ghook,
 NULL,
 menusoftkeys,
 &menu_skt,
 0x10,
 menu_in_iconhndl,
 NULL,   //Items
 NULL,   //Procs
 0,   //n
 1
};

int menu_in_cnt=0;

int menu_in_onkey(void *data, GUI_MSG *msg)
{
  int i=GetCurMenuItem(data);
  if (msg->keys==0x3D)
  {
    if(menu_in_cnt) read_sms(rsms+i*5, 1);
    return(-1);
  }
  return(0);
}

void menu_in_ghook(void *data, int cmd)
{
  if (cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
}

void menu_in_iconhndl(void *data, int curitem, void *unk)
{
  void *item=AllocMLMenuItem(data);
  WSHDR *ws1=AllocMenuWS(data,30);
  WSHDR *ws2=AllocMenuWS(data,30);
  if(SMSD[rsms[curitem*5]].cnt>1) wsprintf(ws1,pcd,SMSD[rsms[curitem*5]].cnt);
  else wsprintf(ws1,nth);
  wstrncat(ws1, SMSD[rsms[curitem*5]].SMS_TEXT, 20);
  wsprintf(ws2,ppp);
  wstrncat(ws1, ws2, 3);
  wsprintf(ws2,nth);
  if(SMSD[rsms[curitem*5]].name)
  {
    wstrcat(ws2, SMSD[rsms[curitem*5]].name);
  }
  else
  {
    wsprintf(ws,perc_t,SMSD[rsms[curitem*5]].Number);
    if(FindNameByNum(&SMSD[rsms[curitem*5]], ws))
    {
      wstrcat(ws2, SMSD[rsms[curitem*5]].name);
    }
    else
      wsprintf(ws2,perc_t,SMSD[rsms[curitem*5]].Number);
  }
  SetMLMenuItemText(data, item, ws1, ws2, curitem);
}

int create_menu2(int n)
{
  char cnt;
  switch(n)
  {
  case 1:
    sprintf(menuhdrtxt, "%s %d", LG_INBOX, scnt.in);
    cnt=scnt.in;
    rsms=_in;
    strcpy(pic_in,pic_folder);
    strcat(pic_in,"in.png");
    M_ICONS[1]=(int)pic_in;
    menuhdr.icon=M_ICONS+1;
    break;
  case 2:
    sprintf(menuhdrtxt, "%s %d", LG_OUTBOX, scnt.out);
    cnt=scnt.out;
    rsms=_out;
    strcpy(pic_out,pic_folder);
    strcat(pic_out,"out.png");
    M_ICONS[2]=(int)pic_out;
    menuhdr.icon=M_ICONS+2;
    break;
  case 3:
    sprintf(menuhdrtxt, "%s %d", LG_DRAFT, scnt.d);
    cnt=scnt.d;
    rsms=_draft;
    strcpy(pic_draft,pic_folder);
    strcat(pic_draft,"draft.png");
    M_ICONS[3]=(int)pic_draft;
    menuhdr.icon=M_ICONS+3;
    break;
  }
  menuhdr.lgp_id=(int)menuhdrtxt;
  patch_header(&menuhdr);
  menu_in_cnt=cnt;
  return(CreateMultiLinesMenu(0,0,&menu_in,&menuhdr,0,cnt));
}

HEADER_DESC mmhdr={0,0,131,21,NULL,(int)"短信管理器",LGP_NULL};
// int menusoftkeys[]={0,1,2};

extern const char *successed_config_filename;

int mm_onkey(void *data, GUI_MSG *msg)
{
  char txt[64];
  int i=GetCurMenuItem(data);
  if (msg->keys==0x3D)
  {
    switch(i)
    {
    case 0:
      edit_sms(NULL, 0, 0);
      break;
    case 1:
      sprintf(txt,"SMSD");
      UpdateDAEMONname(txt);
      newsms=0;
    case 2:
    case 3:
      create_menu2(i);
      break;
    case 4:
      stat();
      break;
    case 5:
      wsprintf(ws,perc_t,successed_config_filename);
      ExecuteFile(ws,NULL,NULL);
      break;
    }
    return(-1);
  }
// 	if (msg->gbsmsg->msg==KEY_DOWN)
// 	{
// 		int c=msg->gbsmsg->submess;
// 		if ((c=='0'))
// 		{
// 			extern void Incom_SMS();
// 			Incom_SMS();
// 		}
// 		
// 		if ((c=='#'))
// 		{
// 			extern char SMS_SND[];
// 			ShowMSG(1, (int)SMS_SND);
// 		}
// 	}
  return(0);
}

void mm_ghook(void *data, int cmd)
{
  if (cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
}

void mm_iconhndl(void *data, int curitem, void *unk)
{
  void *item=AllocMLMenuItem(data);
  WSHDR *ws1=AllocMenuWS(data,30);
  WSHDR *ws2=AllocMenuWS(data,30);
  switch(curitem)
  {
  case 0:
    //Создать смс
    wsprintf(ws1,perc_t,LG_CREATE);
    wsprintf(ws2,perc_t,LG_NEW_SMS);
    SetMenuItemIconArray(data,item,M_ICONS+0);
    break;
  case 1:
    //Входящие
    wsprintf(ws1,"%t %d",LG_INBOX,scnt.in);
    wsprintf(ws2,"%d / %d",scnt.in,scnt.inf);
    SetMenuItemIconArray(data,item,M_ICONS+1);
    break;
  case 2:
    //Исходящие
    wsprintf(ws1,"%t %d",LG_OUTBOX,scnt.out);
    wsprintf(ws2,"%d / %d",scnt.out,scnt.outf);
    SetMenuItemIconArray(data,item,M_ICONS+2);
    break;
  case 3:
    //Черновик
    wsprintf(ws1,"%t %d",LG_DRAFT,scnt.d);
    wsprintf(ws2,"%d / %d",scnt.d,scnt.df);
    SetMenuItemIconArray(data,item,M_ICONS+3);
    break;
  case 4:
    //Статистика
    wsprintf(ws1,perc_t,LG_STATISTIC);
    wsprintf(ws2,perc_t,"SMS.dat");
    SetMenuItemIconArray(data,item,M_ICONS+4);
    break;
  case 5:
    //Настройки
    wsprintf(ws1,perc_t,LG_SETTINGS);
    wsprintf(ws2,perc_t,"SMSman.bcfg");
    SetMenuItemIconArray(data,item,M_ICONS+5);
    break;
  }
  //wsAppendChar(ws2,0xE116);
  //wsAppendChar(ws2,0xE117);
  SetMLMenuItemText(data, item, ws1, ws2, curitem);
}

static const ML_MENU_DESC mm=
{
 8,
 mm_onkey,
 mm_ghook,
 NULL,
 menusoftkeys,
 &menu_skt,
 0x11,
 mm_iconhndl,
 NULL,
 NULL,
 0,
 1
};

int create_mm(void)
{
  //int cnt=0;
  //for(int i=0; i<100; i++)
  //if(SMSD[i].type) cnt++;
  //sprintf(mmtxt, "SMSMan: %d", cnt);
  //menuhdr.lgp_id=(int)menuhdrtxt;
  //Создать смс
  strcpy(pic_new,pic_folder);
  strcat(pic_new,"new.png");
  M_ICONS[0]=(int)pic_new;
  //Входящие
  strcpy(pic_in,pic_folder);
  strcat(pic_in,"in.png");
  M_ICONS[1]=(int)pic_in;
  //Исходящие
  strcpy(pic_out,pic_folder);
  strcat(pic_out,"out.png");
  M_ICONS[2]=(int)pic_out;
  //Черновик
  strcpy(pic_draft,pic_folder);
  strcat(pic_draft,"draft.png");
  M_ICONS[3]=(int)pic_draft;
  //Статистика
  strcpy(pic_stat,pic_folder);
  strcat(pic_stat,"stat.png");
  M_ICONS[4]=(int)pic_stat;
  //Настройки
  strcpy(pic_config,pic_folder);
  strcat(pic_config,"config.png");
  M_ICONS[5]=(int)pic_config;
  //Меню
  strcpy(pic_menu,pic_folder);
  strcat(pic_menu,"top.png");
  M_ICONS[6]=(int)pic_menu;
  mmhdr.icon=M_ICONS+6;
  patch_header(&mmhdr);
  return(CreateMultiLinesMenu(0,0,&mm,&mmhdr,0,6));
}

static void UpdateCSMname(char *txt, WSHDR *tows)
{
  wsprintf(tows,perc_t,txt);
}

static void Killer(void)
{
  FontPathFree();
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

int strcmp_nocase(const char *s, const char *d)
{
  int cs;
  int ds;
  do
  {
    cs=*s++;
    if (cs&0x40) cs&=0xDF;
    ds=*d++;
    if (ds&0x40) ds&=0xDF;
    cs-=ds;
    if (cs) break;
  }
  while(ds);
  return(cs);
}

static void maincsm_oncreate(CSM_RAM *data)
{
  //ews=AllocWS(1024);
  if(read_smsdat())
  {
    //SUBPROC((void*)ConstructList);
    MAINGUI_ID=create_mm();//create_ed();
  }
  else
  {
    //CloseCSM(MAINCSM_ID);
    ShowMSG(1,(int)LG_OPEN_ERR);
  }
  //gipc.name_to=ipc_my_name;
  //gipc.name_from=ipc_my_name;
  //gipc.data=(void *)-1;
  //GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_CHECK_DOUBLERUN,&gipc);
}

static void maincsm_onclose(CSM_RAM *csm)
{
  MAINCSM_ID=0;
  //FreeCLIST();
  //FreeWS(ews);
  for(int i=0; i<scnt.all; i++)
  {
    if(SMSD[i].SMS_TEXT) FreeWS(SMSD[i].SMS_TEXT);
    SMSD[i].SMS_TEXT=NULL;
    //if(SMSD[i].name) FreeWS(SMSD[i].name);
    //SMSD[i].name=NULL;
  }
  if(SMSD)
  {
    mfree(SMSD);
    SMSD=NULL;
  }
  //SUBPROC((void *)Killer);
}

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==MAINGUI_ID)
    {
      csm->csm.state=-3;
    }
}
  
  
// 	if (msg->msg==MSG_IPC)
// 	{
// 		IPC_REQ *ipc;
// 		if ((ipc=(IPC_REQ*)msg->data0))
// 		{
// 			if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
// 			{
// 				switch (msg->submess)
// 				{
// 				 case IPC_CHECK_DOUBLERUN:
// 	    //Если приняли свое собственное сообщение, значит запускаем чекер
// 					 if (ipc->name_from==ipc_my_name) /*SUBPROC((void *)*/CheckDoubleRun();
// 					 else ipc->data=(void *)maincsm_id;
// 					break;
// 				 case IPC_OPEN_GUI:
// 					 read_smsdad();
// 					 MAINGUI_ID=create_mm();//create_ed();
	// 					 
// 				}
// 			}
// 		}
// 	}
	return(1);
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

void main2()
{
  if(MAINCSM_ID)
  {
    gipc.name_to=ipc_xtask_name;
    gipc.name_from=ipc_my_name;
    gipc.data=(void *)MAINCSM_ID;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_SHOW_CSM,&gipc);
  }
  else
  {
    char dummy[sizeof(MAIN_CSM)];
    UpdateCSMname("短信管理器", (WSHDR *)&MAINCSM.maincsm_name);
    CSM_RAM *save_cmpc;
    LockSched();
    save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
    CSM_root()->csm_q->current_msg_processing_csm=NULL;
    MAINCSM_ID = CreateCSM(&MAINCSM.maincsm, dummy, 0);
    CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
    UnlockSched();
  }
}

