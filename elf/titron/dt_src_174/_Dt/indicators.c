
TDate date;
TTime time;

/* static struct{
  char cpu_load;
  char cpu_clock;
  int freeram;
  unsigned short ak;
  char mess;
  char call;
  char sms;
  RAMNET *rn;
} f; */

/* CSM_DESC oldcsmd, icsmd;
CSM_RAM *olddata, oldicsm;
void (*old_icsm_onClose)(CSM_RAM*);
void (*old_icsm_onCreate)(CSM_RAM*);
int (*old_icsm_onMessage)(CSM_RAM*, GBS_MSG *msg); */

void dr_null(){}

static DT_ICON dt_first={
	NULL,NULL,
	{1,1,0,0},
	1,
	NULL,
	NULL,
	NULL,
	NULL,
	1,1,
	dr_null,
	int_0,
	void_0
};

static DT_ICON dt_null={
	NULL,NULL,
	{0,0,0,0},
	1,
	NULL,
	NULL,
	NULL,
	NULL,
	1,1,
	dr_null,
	int_0,
	void_0
};

void inf_icon()
{
	char tmp[32];
	int len;
	//if((cur.x>=Dt.icon[n]->p.x)&&(cur.x<=Dt.icon[n]->p.x2)&&(cur.y>=Dt.icon[n]->p.y)&&(cur.y<=Dt.icon[n]->p.y2))
	//{
		len=strlen(Dt.act->fl);
		int i=0;
		while(Dt.act->fl[len-i]!='\\'){i++;}
		zeromem(tmp, 32);
		memcpy(tmp, Dt.act->fl+len-i+1, i-1);
		sprintf(Dt.act->inf, "%s\n%s", Dt.act->nm, tmp );
	//}
}

void dr_icon()
{
		//DrawRectangle(p->x,p->y,p->x2,p->y2,0,white,white0);
	DrawImg(TAI->p.x, TAI->p.y, (int)TAI->img);
}

int Enter_icon()
{
	wsprintf(ews,perc_t,Dt.act->fl);
	ExecuteFile(ews,NULL,NULL);
	return 0;
}

static DT_ICON _icon={
	NULL,NULL,
	{0,0,0,0},
	1,
	NULL,
	NULL,
	NULL,
	NULL,
	1,1,
	dr_icon,
	Enter_icon,
	inf_icon
};

void inf_entry()
{
	//char tmp[32];
	//int len;
	//if((cur.x>=Dt.icon[n]->p.x)&&(cur.x<=Dt.icon[n]->p.x2)&&(cur.y>=Dt.icon[n]->p.y)&&(cur.y<=Dt.icon[n]->p.y2))
	//{
		//len=strlen(Dt.act->fl);
		//int i=0;
		//while(Dt.act->fl[len-i]!='\\'){i++;}
		//zeromem(tmp, 32);
		//memcpy(tmp, Dt.act->fl+len-i+1, i-1);
		sprintf(Dt.act->inf, "%s\n%s", Dt.act->nm, Dt.act->fl );
	//}
}

int Enter_entry()
{
	char c=0;
	int point=0;
	if(strlen(Dt.act->fl)!=8)
	{
	 ShowMSG(0, (int)"entrypoint is not correct");
	 return 0;
	}
	for(int i=0; i<8; i++)
	{
		c=Dt.act->fl[i];
		if((c>='0')&&(c<='9'))
		{
		 point=point*0x10;
		 point+=c-'0';
		}
		else if((c>='a')&&(c<='f'))
		{
		 point=point*0x10;
		 point+=c-'a'+10;
		}
		else if((c>='A')&&(c<='F'))
		{
		 point=point*0x10;
		 point+=c-'A'+10;
		}
		else
		{
		 ShowMSG(0, (int)"entrypoint is not correct");
		 return 0;
		}
	}
	((func)point)();
	return 0;
}

static DT_ICON entry_icon={
	NULL,NULL,
	{0,0,0,0},
	1,
	NULL,
	NULL,
	NULL,
	NULL,
	1,1,
	dr_icon,
	Enter_entry,
	inf_entry
};

int Enter_shortcut()
{
#ifdef NEWSGOLD
	( (func)(GetShortcutRecordByName(Dt.act->fl)->entry) )();
#else
	( (func)GetFunctionPointer(Dt.act->fl) )();
#endif
	return 0;
}

static DT_ICON shortcut_icon={
	NULL,NULL,
	{0,0,0,0},
	1,
	NULL,
	NULL,
	NULL,
	NULL,
	1,1,
	dr_icon,
	Enter_shortcut,
	inf_entry
};

void inf_mc()
{
	char tmp[32];
	int len=strlen(Dt.act->fl);
		if(Dt.act->fl[len-1]=='\\')
		{
		 len-=1;
		 Dt.act->fl[len-1]=0;
		}
		int i=1;
		while(Dt.act->fl[len-i]!='\\'){i++;}
		zeromem(tmp, 32);
		memcpy(tmp, Dt.act->fl+len-i+1, i-1);
		sprintf(Dt.act->inf, "%s\n%s", Dt.act->nm, tmp );
	//}
}

int Enter_mc()
{
	int len=strlen(Dt.act->fl);
	if(Dt.act->fl[len-1]=='\\') Dt.act->fl[len]=0;
	wsprintf(ews,perc_t,MC_PATH);
	ExecuteFile(ews,NULL,Dt.act->fl);
	return 0;
}

static DT_ICON mc_icon={
	NULL,NULL,
	{0,0,0,0},
	1,
	NULL,
	NULL,
	NULL,
	NULL,
	1,1,
	dr_icon,
	Enter_mc,
	inf_mc
};



//===============================================================================================

	extern DT_ICON clock_icon;
void inf_clock_icon()
{
	sprintf(clock_icon.inf, "%s\n%02d/%02d/%d", clock_icon.nm, date.day,date.month, date.year );
}

void dr_clock_icon()
{
	
	GetDateTime(&date, &time);
	
	wsprintf(ws, "%02d:%02d", time.hour,time.min);
		//DrawString(ws,p->x,p->y+6,p->x2,p->y2,FONT_SMALL,2,red,NULL);
	/* else */ DrawString(ws,clock_icon.p.x,clock_icon.p.y+6,clock_icon.p.x2,clock_icon.p.y2,FONT_SMALL,2,white,NULL);
}

int Enter_clock_icon()
{
	//gui();
	//ShowWMSG(0, "проверка вывода сообщения", FONT_SMALL, GetPaletteAdrByColorIndex(3), GetPaletteAdrByColorIndex(7), 1);
	return 0;
}

static DT_ICON clock_icon={
	NULL,NULL,
	{10,20,100,40},
	0,
	NULL,
	NULL,
	NULL,
	NULL,
	1,1,
	dr_clock_icon,
	Enter_clock_icon,
	inf_clock_icon
};


//===============================================================================================

	extern DT_ICON akk_icon;
void inf_akk_icon()
{
	unsigned short ak=*RamCap();
  #ifdef NEWSGOLD
	if(GetAccessoryType()==13) sprintf(akk_icon.inf, "%s\nCharging", akk_icon.nm );
	else
  #endif
	if(ak<25) sprintf(akk_icon.inf, "%s\nLow", akk_icon.nm );
	else if(ak<95) sprintf(akk_icon.inf, "%s\nNormal", akk_icon.nm );
	else sprintf(akk_icon.inf, "%s\nFull", akk_icon.nm );
}

void dr_akk_icon()
{

	unsigned short ak=*RamCap();
	
	DrawRectangle(akk_icon.p.x, akk_icon.p.y, akk_icon.p.x2,akk_icon.p.y+5,0,white,NULL);
	DrawRectangle(akk_icon.p.x2-(ak*(akk_icon.p.x2-akk_icon.p.x)/100),akk_icon.p.y,
		akk_icon.p.x2,akk_icon.p.y+5,0,white,white0);
	
	wsprintf(ws, "%d%%", ak );
	/* else */ DrawString(ws,akk_icon.p.x,akk_icon.p.y+6,akk_icon.p.x2,akk_icon.p.y2,FONT_SMALL,2,white,NULL);

		// DrawRoundedFrame(scr_w*2/3,2,scr_w-2,12,0,0,0,white,NULL);
		// DrawRoundedFrame(scr_w-2-(f.ak*(scr_w/3)/100),2,scr_w-2,12,0,0,0,white,white0);
}

int Enter_akk_icon()
{
	//gui();
	return 0;
}

static DT_ICON akk_icon={
	NULL,NULL,
	{10,20,100,40},
	0,
	NULL,
	NULL,
	NULL,
	NULL,
	1,1,
	dr_akk_icon,
	Enter_akk_icon,
	inf_akk_icon
};





//===============================================================================================

// void get_akk_info()
// {
	// f.cpu_load=GetCPULoad();
	// f.cpu_clock=GetCPUClock();
	// f.freeram=GetFreeRamAvail();
	// f.ak=*RamCap();
	// GetDateTime(&date, &time);
	// f.rn=RamNet();
	// // f.mess=*RamMissedMessage();
	// // f.call=*RamMissedCalls();
	// #ifndef NEWSGOLD
	// f.sms=*RamMissedSMS();
	// #endif
// }


	extern DT_ICON net_icon;
void inf_net_icon()
{
	RAMNET *rn=RamNet();
	if (rn->ch_number>=255) sprintf(net_icon.inf, "%s\nGSM1800", net_icon.nm );
	else sprintf(net_icon.inf, "%s\nGSM900", net_icon.nm );
}


void dr_net_icon()
{

	RAMNET *rn=RamNet();
	
	DrawRectangle(net_icon.p.x,net_icon.p.y,
		net_icon.p.x2,net_icon.p.y+5,0,white,NULL);
	if(rn->power!=0) DrawRectangle(net_icon.p.x,net_icon.p.y,
		net_icon.p.x+((net_icon.p.x2-net_icon.p.x)-(rn->power-60)*(scr_w/3)/60),
		net_icon.p.y+5,0,white,white0);
	
	//if(rn->power!=0)  DrawRoundedFrame(2,46-((rn->power)/4),7,46,2,2,0,white,green);
	//wsprintf(ws, "-%ddB\n%d\n%d\n%d\n%d\n%d\n%d\n%d", f.rn->power, f.rn->ch_number, f.rn->ci, f.rn->lac, f.rn->c1, f.rn->c2, f.rn->unk, f.rn->unk2 );
	
	wsprintf(ws, "-%ddB", rn->power );
	/* else */ DrawString(ws,net_icon.p.x,net_icon.p.y+6,net_icon.p.x2,net_icon.p.y2,FONT_SMALL,2,white,NULL);

	//wsprintf(ws, "-%ddB", f.rn->power);
	/* if(rn1->power!=0) DrawRoundedFrame(1,23,2+((110-rn1->power)/2),23,0,0,0,cl2,cl2 );
	if(rn2->power!=0) DrawRoundedFrame(1,25,2+((110-rn2->power)/2),25,0,0,0,cl2,cl2 );
	if(rn3->power!=0) DrawRoundedFrame(1,27,2+((110-rn3->power)/2),27,0,0,0,cl2,cl2);
	if(rn4->power!=0) DrawRoundedFrame(1,29,2+((110-rn4->power)/2),29,0,0,0,cl2,cl2 );
	if(rn5->power!=0) DrawRoundedFrame(1,31,2+((110-rn5->power)/2),31,0,0,0,cl2,cl2 );
	if(rn6->power!=0) DrawRoundedFrame(1,33,2+((110-rn6->power)/2),33,0,0,0,cl2,cl2 ); */
}

int Enter_net_icon()
{
	//gui();
	return 0;
}

static DT_ICON net_icon={
	NULL,NULL,
	{10,20,100,40},
	0,
	NULL,
	NULL,
	NULL,
	NULL,
	1,1,
	dr_net_icon,
	Enter_net_icon,
	inf_net_icon
};


