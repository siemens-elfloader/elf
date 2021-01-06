

char dttm[6], checknew=0, *rsms, newsms=0;

unsigned int DAEMON_ID=0, MAINCSM_ID=0, MAINGUI_ID=0, INCOMCSM_ID=0, INCOMGUI_ID=0;

extern void kill_data(void *p, void (*func_p)(void *));
const int minus11=-11;

const char ipc_my_name[]=IPC_SMSMAN_NAME;
const char ipc_xtask_name[]=IPC_XTASK_NAME;
IPC_REQ gipc;

extern int char16to8(int c);

static const unsigned short sms7[128]=
{
 0x0040,0x00a3,0x0024,0x00a5,0x00e8,0x00e9,0x00f9,0x00ec,
 0x00f2,0x00c7,0x000a,0x00d8,0x00f8,0x000d,0x00c5,0x00e5,
 0x0394,0x005f,0x03a6,0x0393,0x039b,0x03a9,0x03a0,0x03a8,
 0x03a3,0x0398,0x039e,0x001b,0x00c6,0x00e6,0x00df,0x00c9,
 0x0020,0x0021,0x0022,0x0023,0x00a4,0x0025,0x0026,0x0027,
 0x0028,0x0029,0x002a,0x002b,0x002c,0x002d,0x002e,0x002f,
 0x0030,0x0031,0x0032,0x0033,0x0034,0x0035,0x0036,0x0037,
 0x0038,0x0039,0x003a,0x003b,0x003c,0x003d,0x003e,0x003f,
 0x00a1,0x0041,0x0042,0x0043,0x0044,0x0045,0x0046,0x0047,
 0x0048,0x0049,0x004a,0x004b,0x004c,0x004d,0x004e,0x004f,
 0x0050,0x0051,0x0052,0x0053,0x0054,0x0055,0x0056,0x0057,
 0x0058,0x0059,0x005a,0x00c4,0x00d6,0x00d1,0x00dc,0x00a7,
 0x00bf,0x0061,0x0062,0x0063,0x0064,0x0065,0x0066,0x0067,
 0x0068,0x0069,0x006a,0x006b,0x006c,0x006d,0x006e,0x006f,
 0x0070,0x0071,0x0072,0x0073,0x0074,0x0075,0x0076,0x0077,
 0x0078,0x0079,0x007a,0x00e4,0x00f6,0x00f1,0x00fc,0x00e0
};


int is7bit(WSHDR *sws)
{
// 	if(!wstrlen(sws)) return 1;
	char t;
	for(int i=0; i<wstrlen(sws); i++)
	{
		t=0;
		for(int j=0; j<128; j++) if(sws->wsbody[i+1]==sms7[j]) t++;
		if(!t) return 0;
	}
	return 1;
}


// §¡, §Ñ - A, a
// §¢, §Ò - B, b
// §£, §Ó - V, v
// §¤, §Ô - G, g
// §¥, §Õ - D, d
// §¦, §Ö - E, e
// §§, §× - Yo, yo
// §¨, §Ø - J(ZH), j(zh)
// §©, §Ù - Z, z
// §ª, §Ú - I, i
// §«, §Û - Y, y
// §¬, §Ü - K, k
// §­, §Ý - L, l
// §®, §Þ - M, m
// §¯, §ß - N, n
// §°, §à - O, o
// §±, §á - P, p
// §², §â - R, r
// §³, §ã - S, s
// §´, §ä - T, t
// §µ, §å - U, u
// §¶, §æ - F, f
// §·, §ç - H, h
// §¸, §è - C, c
// §¹, §é - Ch, ch
// §º, §ê - Sh(W), sh(w)
// §», §ë - Sch, sch
// §¾, §î - '
// §½, §í - X, x
// §¼, §ì - "
// §¿, §ï - '/, /
// §À, §ð - Yu, yu
// §Á, §ñ - Ya, ya
typedef struct{
	char *r, *e;
}trstruct;

trstruct tr_r[]=
{
 {"§¡","A"}, {"§Ñ","a"},
 {"§¢","B"}, {"§Ò","b"},
 {"§£","V"}, {"§Ó","v"},
 {"§¤","G"}, {"§Ô","g"},
 {"§¥","D"}, {"§Õ","d"},
 {"§¦","E"}, {"§Ö","e"},
 {"§§","Yo"}, {"§×","yo"},
 {"§¨","J"}, {"§Ø","j"},
 {"§©","Z"}, {"§Ù","z"},
 {"§ª","I"}, {"§Ú","i"},
 {"§«","Y"}, {"§Û","y"},
 {"§¬","K"}, {"§Ü","k"},
 {"§­","L"}, {"§Ý","l"},
 {"§®","M"}, {"§Þ","m"},
 {"§¯","N"}, {"§ß","n"},
 {"§°","O"}, {"§à","o"},
 {"§±","P"}, {"§á","p"},
 {"§²","R"}, {"§â","r"},
 {"§³","S"}, {"§ã","s"},
 {"§´","T"}, {"§ä","t"},
 {"§µ","U"}, {"§å","u"},
 {"§¶","F"}, {"§æ","f"},
 {"§·","H"}, {"§ç","h"},
 {"§¸","C"}, {"§è","c"},
 {"§¹","Ch"}, {"§é","ch"},
 {"§º","Sh"}, {"§ê","sh"},
 {"§»","Sch"}, {"§ë","sch"},
 {"§¼","\""}, {"§ì","\""},
 {"§½","Y"}, {"§í","Y"},
 {"§¾","'"}, {"§î","'"},
 {"§¿","E"}, {"§ï","e"},
 {"§À","Yu"}, {"§ð","yu"},
 {"§Á","Ya"}, {"§ñ","ya"}
};

// const char *tr_e[]=
// {
//  "A","a",
//  "B","b",
//  "V","v",
//  "G","g",
//  "D","d",
//  "E","e",
//  "Yo","yo",
//  "J","j",
//  "Z","z",
//  "I","i",
//  "Y","y",
//  "K","k",
//  "L","l",
//  "M","m",
//  "N","n",
//  "O","o",
//  "P","p",
//  "R","r",
//  "S","s",
//  "T","t",
//  "U","u",
//  "F","f",
//  "H","h",
//  "C","c",
//  "Ch","ch",
//  "Sh","sh",
//  "Sch","sch",
//  "\"","\"",
//  "Y","Y",
//  "'","'",
//  "E","e",
//  "Yu","yu",
//  "Ya","ya"
// };

WSHDR *translit(WSHDR *ws0)
{
	if(!wstrlen(ws0)) return ws0;
// 	if(is7bit(ws0)) return ws0;
// 	WSHDR *tws=AllocWS(wstrlen(ws0)*2);
	char *txt=malloc(wstrlen(ws0)*2);
	zeromem(txt, wstrlen(ws0)*2);
	for(int i=0; i<wstrlen(ws0); i++)
	{
		char c=char16to8(ws0->wsbody[i+1])&0xff;
// 		char t=1;
		for(int j=0; j<66; j++)
		{
			if(c==*tr_r[j].r)
			{
				c=0;
				strcat(txt, tr_r[j].e);
				j=66;
			}
		}
		if(c) txt[strlen(txt)]=c;
	}
// 	ShowMSG(1,(int)txt);
	WSHDR *tws=AllocWS(strlen(txt));
	wsprintf(tws,txt);
	mfree(txt);
	return tws;
}

int add_translit(void *edsms_gui)
{
	EDITCONTROL ec;
	EDIT_ExtractFocusedControl(edsms_gui,&ec);
	WSHDR *ws0=translit(ec.pWS);//=AllocWS(ec.maxlen*2);
// 	wstrcat(ws0,wstxt);
	if(ws0!=ec.pWS)
	{
		EDIT_SetTextToFocused(edsms_gui,ws0);
		FreeWS(ws0);
	}
	return 1;
}

SMS_LEN *smslen(WSHDR *t)
{
// 	int cnt, len;
	SMS_LEN *tt=malloc(sizeof(SMS_LEN));
	if(is7bit(t))
	{
		tt->is7=1;
		tt->len=wstrlen(t);
		if(!tt->len) tt->cnt=0;
		else if(tt->len<=160) tt->cnt=1;
		else tt->cnt=(tt->len-1)/152+1;
	}
	else
	{
		tt->is7=0;
		tt->len=wstrlen(t);
		if(!tt->len) tt->cnt=0;
		else if(tt->len<=70) tt->cnt=1;
		else tt->cnt=(tt->len-1)/66+1;
	}
	return tt;
}

char oxff4[4]={0xff,0xff,0xff,0xff};

int read_smsdat()
{
	int f;
	unsigned int er;
	char *smsdat;
	if ((f=fopen(SMS_DAT_PATH,A_ReadOnly+A_BIN,0,&er))!=-1)
	{
		int fsz=lseek(f,0,S_END,&er,&er)-2;
		scnt.all=fsz/sizeof(PDU);
		SMSD=malloc(sizeof(SMS_DATA)*scnt.all);
		lseek(f, 2, 0, &er, &er);
		smsdat=malloc(sizeof(PDU)*scnt.all);
		fread(f,smsdat,sizeof(PDU)*scnt.all,&er);
		fclose(f,&er);
		for(int i=0; i<scnt.all; i++) GetSMSData(&SMSD[i], (PDU*)smsdat+i);
		mfree(smsdat);
	}
	else
	{
		return 0;
	}
	
	scnt.in=scnt.out=scnt.d=scnt.inf=scnt.outf=scnt.df=0;
	
	for(int i=0; i<scnt.all; i++)
	{
// 		if(SMSD[i].n==1)
		switch(SMSD[i].type)
		{
			case TYPE_OUT:
				if(SMSD[i].n==1) scnt.out++;
				scnt.outf++;//=SMSD[i].cnt;
				break;
			case TYPE_IN:
				if(SMSD[i].n==1) scnt.in++;
				scnt.inf++;//=SMSD[i].cnt;
				break;
			case TYPE_DRAFT:
				if(SMSD[i].n==1) scnt.d++;
				scnt.df++;//=SMSD[i].cnt;
				break;
		}
	}
	
	if(scnt.in) _in=malloc(scnt.in*5);
	if(scnt.out) _out=malloc(scnt.out*5);
	if(scnt.d) _draft=malloc(scnt.d*5);
	
	char tin=0, tout=0, td=0;
	
	for(int i=0; i<scnt.all; i++)
	{
		if(SMSD[i].n==1)
			switch(SMSD[i].type)
		{
			case TYPE_OUT:
				_out[tout*5]=i;
				if(SMSD[i].cnt>1)
				{
					memcpy(_out+tout*5+1, oxff4, 4);
					for(int ii=0; ii<scnt.all; ii++)
						if((SMSD[ii].sig==SMSD[i].sig)&&(i!=ii))
							_out[tout*5+SMSD[ii].n-1]=ii;
				}
				tout++;
				break;
			case TYPE_IN:
				_in[tin*5]=i;
				if(SMSD[i].cnt>1)
				{
					memcpy(_in+tin*5+1, oxff4, 4);
					for(int ii=0; ii<scnt.all; ii++)
						if((SMSD[ii].sig==SMSD[i].sig)&&(i!=ii))
							_in[tin*5+SMSD[ii].n-1]=ii;
				}
				tin++;
				break;
			case TYPE_DRAFT:
				_draft[td*5]=i;
				if(SMSD[i].cnt>1)
				{
					memcpy(_draft+td*5+1, oxff4, 4);
					for(int ii=0; ii<scnt.all; ii++)
						if((SMSD[ii].sig==SMSD[i].sig)&&(i!=ii))
							_draft[td*5+SMSD[ii].n-1]=ii;
				}
				td++;
				break;
		}
	}
	
	char tmp[5], k=0;
	
	for(int i = 0; i <= scnt.in-1; i++)
	{
		for(int j = 0; j <= scnt.in-2-i; j++)
		{
			k=0;
			check:
			if( SMSD[_in[j*5]].tm[k]<SMSD[_in[j*5+5]].tm[k] )
			{
				memcpy(tmp, _in+j*5, 5);
				memcpy(_in+j*5, _in+j*5+5, 5);
				memcpy(_in+j*5+5, tmp, 5);
			}
			else if((SMSD[_in[j*5]].tm[k]==SMSD[_in[j*5+5]].tm[k])&&(k<6))
			{
				k++; goto check;
			}
// 			if(k==6) ShowMSG(1,(int)"§à§ê§Ú§Ò§Ü§Ñ §ã§à§â§ä§Ú§â§à§Ó§Ü§Ú");
		}
	}
	return 1;
}

// int isdtinlist(char *t)
// {
// 	char ch=0;
// 	for(int j=0; j<100; j++)
// 	{
// 		ch=0;
// 	  	for(int i=0; i<6; i++)
// 			if(SMSD[j].tm[i]==(t[i]%0x10*10+t[i]/0x10))
// 			{
// 				ch++;
// 			}
// 		if(ch==6) return 1;
// 	}
// 	return 0;
// }

// int isNewSMS(char type)
// {
// 	int c;
// 	char *p=(char*)IncommingPDU();
// 	if ( *p++ != 0x11 ) return 0;
// 	if ( *p++ != 0x11 ) return 0;
// 	c=*p++;
// 	if((c!=1)&&(c!=3)) return 0;
// 	p+=3;
// 	c=*p++;
// 	p+=c+1;
// 	c=*p++;
// 	if(c)
// 		if(c%2) c=c/2+2;
// 		else c=c/2+1;
// 	p+=c+2;
// 	if(!type)
// 	{
// 		for (int i=0; i<6; i++)
// 			dttm[i]=p[i]%0x10*10+p[i]/0x10;
// 		return 1;
// 	}
// 	else
// 	{
// 	  for(int i=0; i<6; i++)
// 		if(dttm[i]!=(p[i]%0x10*10+p[i]/0x10))
// 		{
// 			/*if(isdtinlist(p)) return 0;
// 			else*/ return 1;
// 		}
// 	}
// 	return 0;
// }


// void wrpng()
// {
// 	if ((f=fopen(d_png,A_ReadOnly+A_BIN,0,&er))!=-1) fclose(f,&er);
// 	else if ((f=fopen(d_png,A_WriteOnly+A_Create+A_BIN,P_WRITE,&er))!=-1)
// 	{
// 		fwrite(f,pic_d,sizeof(pic_d),&ul);
// 		fclose(f,&ul);
// 	}
	// 	
// 	if ((f=fopen(i_png,A_ReadOnly+A_BIN,0,&er))!=-1) fclose(f,&er);
// 	else if ((f=fopen(i_png,A_WriteOnly+A_Create+A_BIN,P_WRITE,&er))!=-1)
// 	{
// 		fwrite(f,pic_i,sizeof(pic_i),&ul);
// 		fclose(f,&ul);
// 	}
	// 	
// 	if ((f=fopen(m_png,A_ReadOnly+A_BIN,0,&er))!=-1) fclose(f,&er);
// 	else if ((f=fopen(m_png,A_WriteOnly+A_Create+A_BIN,P_WRITE,&er))!=-1)
// 	{
// 		fwrite(f,pic_m,sizeof(pic_m),&ul);
// 		fclose(f,&ul);
// 	}
	// 	
// 	if ((f=fopen(n_png,A_ReadOnly+A_BIN,0,&er))!=-1) fclose(f,&er);
// 	else if ((f=fopen(n_png,A_WriteOnly+A_Create+A_BIN,P_WRITE,&er))!=-1)
// 	{
// 		fwrite(f,pic_n,sizeof(pic_n),&ul);
// 		fclose(f,&ul);
// 	}
	// 	
// 	if ((f=fopen(o_png,A_ReadOnly+A_BIN,0,&er))!=-1) fclose(f,&er);
// 	else if ((f=fopen(o_png,A_WriteOnly+A_Create+A_BIN,P_WRITE,&er))!=-1)
// 	{
// 		fwrite(f,pic_o,sizeof(pic_o),&ul);
// 		fclose(f,&ul);
// 	}
// 	S_ICONS[0]=(int)i_png;
// 	S_ICONS[1]=(int)o_png;
// 	S_ICONS[2]=(int)d_png;
// 	S_ICONS[3]=(int)m_png;
// 	S_ICONS[4]=(int)n_png;
// }
