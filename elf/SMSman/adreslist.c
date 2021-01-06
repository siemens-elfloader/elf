#include "swilib.h"
#include "adreslist.h"
#include "sms_data.h"
// #include "lang.h"

volatile CLIST *cltop; //Начало
char pics_menu[128];
int A_ICONS[1];
int *cllist;
int cl_n=0;
/*
int char16to8(int c)
{
  if (c<0x400) return (c);
  c-=0x400;
  if (c<16)
  {
    if (c==1) c=0;  //big_yo
    else if (c==4) c=2;  //big_ye
    else if (c==6) c=10; //big_i
    else return (c);
  }
  else if (c>79)
  {
    if (c==0x51) c=16; //small_yo
    else if (c==0x54) c=18; //small_ye
    else if (c==0x56) c=11; //small_i
    else if (c==0x57) c=23; //small_yi
    else return (c);
  }
  else c+=8;
  c+=168;
  return (c);
}*/
extern unsigned int char16to8(unsigned int c);

//сравнение длинных строк
int wstrcmp_nocase(WSHDR *ws1, WSHDR *ws2)
{
  int l1=wslen(ws1);
  int l2=wslen(ws2);
  int pos=1;
  int cs;//, ds;
  while((pos<=l1)&&(pos<=l2))
  {
    cs=ws1->wsbody[pos]-ws2->wsbody[pos];
    //cs=char16to8(ws1->wsbody[pos]);
    //if (cs&0x40) cs&=0xDF;
    //ds=char16to8(ws2->wsbody[pos]);
    //if (ds&0x40) ds&=0xDF;
    //cs-=ds;
    if (cs) return cs;
    pos++;
  }
  return(l1-l2);
}

//сравнение номеров
int num_nocase(WSHDR *ws1, WSHDR *ws2)
{
  int l1=wslen(ws1);
  int l2=wslen(ws2);
  int pos1,pos2;
  switch(l1-l2)
  {
  case 0:
    pos1=1;
    pos2=1;
    break;
  case 1:
    if(ws1->wsbody[1]!='+') return 1;
    pos1=3;
    pos2=2;
    break;
  case -1:
    if(ws2->wsbody[1]!='+') return 1;
    pos1=2;
    pos2=3;
    break;
  default: return 1;
  }
  int cs;//, ds;
  while((pos1<=l1)&&(pos2<=l2))
  {
    cs=ws1->wsbody[pos1]-ws2->wsbody[pos2];
    //cs=char16to8(ws1->wsbody[pos]);
    //if (cs&0x40) cs&=0xDF;
    //ds=char16to8(ws2->wsbody[pos]);
    //if (ds&0x40) ds&=0xDF;
    //cs-=ds;
    if (cs) return cs;
    pos1++;
    pos2++;
  }
  return(0);
}


int FindNameByNum(SMS_DATA *dat, WSHDR *num)
{
  CLIST *cl0=(CLIST*)cltop;
  while(cl0)
  {
    for(int i=0; i<NUMBERS_MAX; i++)
      if(cl0->num[i])
        if(!num_nocase(cl0->num[i], num))
        {
          //dat->name=AllocWS(1);
          //mfree(dat->name->wsbody);
          dat->name=cl0->name;
          //wstrcat(name, cl0->name);
          return 1;
        }
    cl0=(CLIST*)(cl0->next);
  }
  return 0;
}

//Уничтожить список
void FreeCLIST(void)
{
  LockSched();
  CLIST *cl0=(CLIST*)cltop;
  mfree(cllist);
  cltop=0;
  UnlockSched();
  while(cl0)
  {
    CLIST *p;
    FreeWS(cl0->name);
    FreeWS(cl0->nm[0]);
    FreeWS(cl0->nm[1]);
    FreeWS(cl0->nm[2]);
    for(int i=0;i<NUMBERS_MAX;i++) FreeWS(cl0->num[i]);
    //FreeWS(cl->icons);
    p=cl0;
    cl0=(CLIST*)(cl0->next);
    mfree(p);
  }
}

//=====================================================
// Конструктор списка
//=====================================================
void ConstructList(void)
{
	int fin;
	unsigned int ul;
	char recname[128];

	AB_UNPRES ur;
	void *buffer;

#pragma pack(1)
	struct {
#ifdef NEWSGOLD
		long dummy1;
		short dummy2;
		char bitmap[MAX_RECORDS/8];
#else
		long dummy1;
		char bitmap[MAX_RECORDS/8];
#endif
	} ABmain;
#pragma pack()

	unsigned int rec=0;
	int fsz;
	CLIST contact;

	WSHDR *sws=AllocWS(50);

	cl_n=0;
	FreeCLIST(); //Уничтожаем пред. список
// 	LockSched();
// 	if (e_ws) wstrcpy(sws,(WSHDR *)e_ws);
// 	if (hook_state==4) hook_state=5;
// 	UnlockSched();
	zeromem(&contact,sizeof(contact));
	if ((buffer=malloc(65536)))
	{
		zeromem(&ABmain,sizeof(ABmain));
		if ((fin=fopen(s_ab_main, A_ReadOnly+A_BIN, P_READ, &ul))!=-1)
		{
#ifdef ELKA
			if (fread(fin,&ABmain,sizeof(ABmain),&ul)>=194)
#else
			if (fread(fin,&ABmain,sizeof(ABmain),&ul)==sizeof(ABmain))
#endif
			{
				fclose(fin,&ul);
				do
				{
#ifdef NEWSGOLD
					if (ABmain.bitmap[rec>>3]&(0x80>>(rec&7)))
#else
					if (ABmain.bitmap[rec>>3]&(1<<(rec&7)))
#endif
					{
#ifdef NEWSGOLD
	    //Запись есть в битмапе
						unsigned int rl1;
						unsigned int rl2;
						unsigned int rl3;
						rl1=rec/LEVEL1_RN;
						rl2=(rec%LEVEL1_RN)/LEVEL2_RN;
						rl3=rec%LEVEL2_RN;
						snprintf(recname, 128, s_ab_entry, rl1, rl2, rl3);
#else
						unsigned int rl1=rec/LEVEL1_RN;
						unsigned int r12=rec%LEVEL1_RN;
						snprintf(recname, 128, s_ab_entry, rl1, r12);
#endif
						if ((fin=fopen(recname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
						{
							zeromem(&ur,sizeof(AB_UNPRES));
							fsz=lseek(fin,0,S_END,&ul,&ul);
							lseek(fin,0,S_SET,&ul,&ul);
							fread(fin,buffer,fsz,&ul);
							fclose(fin,&ul);
#ifdef NEWSGOLD
							UnpackABentry(&ur,((char *)buffer+8),fsz,0x28);
#else
							UnpackABentry(&ur,((char *)buffer+4),fsz-4,0x28);
#endif
							int i=0;
							zeromem(&contact,sizeof(contact));
// 							contact.icons=AllocWS(NUMBERS_MAX);
							while(i<ur.number_of_records)
							{
								AB_UNPRES_ITEM *r=ur.record_list+i;
								if (r->no_data!=1)
								{
									switch(GetTypeOfAB_UNPRES_ITEM(r->item_type))
									{
										case 0x05:
#ifdef NEWSGOLD
//                    if (r->item_type==0x81)
											if (
												r->item_type==LAST_NAME||
												r->item_type==FIRST_NAME||
// 												r->item_type==COMPANY_NAME||
// 												r->item_type==POST_NAME||
												r->item_type==DISPLAY_NAME
											   )
#else
											if (
												r->item_type==LAST_NAME||
												r->item_type==FIRST_NAME||
												r->item_type==COMPANY_NAME
											   )
#endif
											{
//                      #ifdef NEWSGOLD
//		      if (r->data)
//		      {
//			wstrcpy(contact.name=AllocWS(150),(WSHDR *)(r->data));
//			*((int *)(&contact.next))|=CompareStrT9(contact.name,sws,0);
//		      }
//                      #else
												if (r->data)
												{
													if (!contact.name)
													{
														cl_n++;
														wstrcpy(contact.nm[0]=AllocWS(150),(WSHDR *)(r->data));
														wstrcpy(contact.name=AllocWS(150),(WSHDR *)(r->data));
// 						*((int *) (&contact.next))|= CompareStrT9(contact.name,sws,0);
														contact.next = (void*)1;
													}
													else if (!contact.nm[1])
													{
// 														cl_n++;
														wstrcpy(contact.nm[1]=AllocWS(150),(WSHDR *)(r->data));
														wsAppendChar(contact.name,',');
														wsAppendChar(contact.name,' ');
														wstrcat(contact.name, (WSHDR*)(r->data));
// 						*((int *) (&contact.next))|= CompareStrT9(contact.name,sws,0);
														contact.next = (void*)1;
													}
													else// if (!contact.name[1])
													{
// 														cl_n++;
														wstrcpy(contact.nm[2]=AllocWS(150),(WSHDR *)(r->data));
														wsAppendChar(contact.name,',');
														wsAppendChar(contact.name,' ');
														wstrcat(contact.name, (WSHDR*)(r->data));
// 						*((int *) (&contact.next))|= CompareStrT9(contact.name,sws,0);
														contact.next = (void*)1;
													}
// 													else
// 													{
// 														wsAppendChar(contact.name,',');
// 														wsAppendChar(contact.name,' ');
// 														wstrcat(contact.name, (WSHDR*)(r->data));
// // 						*((int *) (&contact.next))|= CompareStrT9(contact.name,sws,0);
// 														contact.next = (void*)1;
// 													}
												}
//                      #endif
											}
											break;
										case 0x01:
										{
											PKT_NUM *p=(PKT_NUM*)r->data;
											unsigned int n=r->item_type;
											int j;
											unsigned int c;
											WSHDR *ws0;
#ifdef NEWSGOLD
											if (n!=106) n-=0x62;
											else n=4;
											if (n<5)
#else
											switch(r->item_type)
											{
												case PHONE_NUMBER:
													n=0;    break;
												case PHONE_OFFICE:
													n=1;    break;
												case PHONE_MOBILE:
													n=2;    break;
												case PHONE_FAX:
													n=3;    break;
												case PHONE_FAX2:
													n=4;    break;
												default:
													continue;
											}
#endif
											{
												if (p)
												{
													unsigned int c1;
													int m;
													ws0=contact.num[n]=AllocWS(50);
			  //Добавляем иконки телефонов
// 										wsAppendChar(contact.icons, utf_symbs[n]);
													j=0;
													m=0;
													if (p->format==0x91)
														wsAppendChar(ws0,'+');
													while(j<p->data_size)
													{
														if (m&1) {c1=c>>4; j++;}
														else c1=(c=p->data[j])&0x0F;
														if (c1==0x0F) break;

														if (c1==0xA) c1='*';
														else if (c1==0xB) c1='#';
														else if (c1==0xC) c1='+';
														else if (c1==0xD) c1='?';
														else c1+='0';
														wsAppendChar(ws0,c1);
														m++;
													}
// 									*((int *) (&contact.next))|= CompareStrT9(ws,sws,0);
													contact.next = (void*)1;
												}
											}
											break;
										}
									}
								}
								i++;
							}
							if (!contact.next)
							{
								FreeWS(contact.name);
								FreeWS(contact.nm[0]);
								FreeWS(contact.nm[1]);
								FreeWS(contact.nm[2]);
								for(int i=0;i<NUMBERS_MAX;i++) FreeWS(contact.num[i]);
// 								FreeWS(contact.icons);
							}
							FreeUnpackABentry(&ur,mfree_adr());
// 							if (hook_state!=5) goto L_STOP;
							LockSched();
							if (/*(hook_state==5)&&*/(contact.next))
							{
		//Добавляем в список
								int n=0;
								CLIST *p=malloc(sizeof(contact));
								CLIST *t;
								CLIST *b=(CLIST *)(&cltop);
								contact.next=0;
								memcpy(p,&contact,sizeof(contact));
								for(;;)
								{
									if (t=b->next)
									{
		    //Есть следующие
										if (wstrcmp_nocase(contact.name,t->name)<0)
										{
		      //Следующий больше вставляемого, втыкаем сдесь
											p->next=t;
											b->next=p;
// 											if (is_pos_changed && n<=curpos) curpos++;  // Отсаемся на выбранной позиции
											break;
										}
										b=t; //Следующий
										n++; //Номер добавляемого, для расчета, нужен ли REDRAW
									}
									else
									{
		    //Больше нет никого
										b->next=p;
										break;
									}
								}
							}
							UnlockSched();
						}
					}
					rec++;
				}
				while(rec<MAX_RECORDS);
			}
			else
			{
				fclose(fin,&ul);
			}
		}
//   L_STOP:
		  mfree(buffer);
	}
	if (contact.next)
	{
		FreeWS(contact.name);
		FreeWS(contact.nm[0]);
		FreeWS(contact.nm[1]);
		FreeWS(contact.nm[2]);
		for(int i=0;i<NUMBERS_MAX;i++) FreeWS(contact.num[i]);
// 		FreeWS(contact.icons);
	}
	FreeWS(sws);
	
// 	cl_n=0;
	cllist=malloc(cl_n*4);
	int t=0;
	CLIST *cl0=(CLIST*)cltop;
	while(cl0)
	{
		cllist[t]=(int)cl0;
		t++;
// 		cl_n++;
		cl0=(CLIST*)(cl0->next);
	}
}

void *edsms_gui=NULL;
char cltxt[32], nmtxt[64], nemuRestart=1;
int tnomm=0;
HEADER_DESC clhdr={0,0,131,21,NULL,(int)cltxt,LGP_NULL};
HEADER_DESC nmenuhdr={0,0,0,0,NULL,(int)LG_SEL_NUM,LGP_NULL};
extern char perc_t[];
extern void patch_header(const HEADER_DESC* head);
extern int menusoftkeys[];
extern SOFTKEY_DESC menu_sk[];
extern SOFTKEYSTAB menu_skt;

int add_to_num(WSHDR *wstxt)
{
  EDITCONTROL ec;
  EDIT_ExtractFocusedControl(edsms_gui,&ec);
  //WSHDR *ws0=AllocWS(ec.maxlen);
  //wstrcat(ws0,wstxt);
  EDIT_SetTextToFocused(edsms_gui,wstxt);
  //FreeWS(ws0);
  return 1;
}

int Cont_list(void *ed_gui, int n);

void nmenu_ghook(void *data, int cmd)
{
  if (cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
  if (cmd==TI_CMD_DESTROY)
  {
    if(nemuRestart)
    {
      Cont_list(edsms_gui, tnomm);
    }
    else nemuRestart=1;
  }
}

static void nmenuitemhandler(void *data, int curitem, void *unk)
{
  WSHDR *ws0;
  void *item=AllocMenuItem(data);
  extern const char percent_t[];
  ws0=AllocMenuWS(data,30);
  CLIST *cl0=(CLIST *)MenuGetUserPointer(data);
  int j=0;
  for(int i=0; i<NUMBERS_MAX; i++)
    if(j<curitem)
    {
      if(cl0->num[i]) j++;
    }
    else if(cl0->num[i])
    {
      wstrcat(ws0, cl0->num[i]);
      i=NUMBERS_MAX;
    }
  SetMenuItemText(data, item, ws0, curitem);
}

static int nmenu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    int curitem=GetCurMenuItem(data);
    CLIST *cl0=(CLIST *)MenuGetUserPointer(data);
    int j=0;
    for(int i=0; i<NUMBERS_MAX; i++)
      if(j<curitem)
      {
        if(cl0->num[i]) j++;
      }
      else if(cl0->num[i])
      {
        nemuRestart=0;
        return add_to_num(cl0->num[i]);
      }
  }
  return(0);
}


static const MENU_DESC nmenu=
{
  8,nmenu_keyhook,nmenu_ghook,NULL,
 menusoftkeys,
 &menu_skt,
 0x10,//MENU_FLAG,
 nmenuitemhandler,
 NULL,//menuitems,
 NULL,//menuprocs,
 0
};

void ShowExtMum(CLIST *cl0, int n, int cnt)
{
  //ws_2str(cl0->name, nmtxt, cl0->name->wsbody[0]);
  patch_header(&nmenuhdr);
  int j=0;
  if(cl0->num[2])
  {
    for(int i=0; i<2; i++)
      if(cl0->num[i]) j++;
  }
  else
  {
    for(int i=0; i<n; i++)
      if(cl0->num[i]) j++;
  }
  CreateMenu(0,0,&nmenu,&nmenuhdr,j,cnt,cl0,0);
}

struct
{
  char n, t[32];
  int cnt, *list;
}fnd;

// struct{
// 	
// }

void ReCount(void *data)
{
	int p[3];
	char txt[3];
// 	CLIST *cl0=(CLIST*)cltop;
// 	while(cl0)
// 	{
// 		p=0;
// 		zeromem(txt,32);
// 		for(int i=0; i<32; i++)
// 		{
// 			txt[i]=(char16to8(cl0->name->wsbody[i+1]))&0xff;
// 			if(i>=cl0->name->wsbody[0]) i=32;
// 		}
// 		//ws_2str(cl0->name, txt, wstrlen(cl0->name));
// 		for(int i=0; i<fnd.n; i++)
// 			if(fnd.t[i]!=table_T9Key[txt[i]]) p++;
// 		if(!p) t++;
// 		cl0=(CLIST*)(cl0->next);
// 	}
	fnd.cnt=0;
	CLIST **list=(CLIST**)cllist;
	for(int j=0; j<cl_n; j++)
	{
		p[0]=0;
		p[1]=0;
		p[2]=0;
// 		zeromem(txt1,32);
// 		zeromem(txt2,32);
// 		zeromem(txt3,32);
// 		for(int i=0; i<32; i++)
// 		{
// 			txt[i]=char16to8(list[j]->name->wsbody[i+1])&0xff;
// 			if(i>=list[j]->name->wsbody[0]) i=32;
// 		}
		//ws_2str(cl0->name, txt, wstrlen(cl0->name));
		for(int i=0; i<fnd.n; i++)
		{
			for(int k=0; k<3; k++)
			{
				if(list[j]->nm[k])
				{
					if(i<list[j]->nm[k]->wsbody[0])
						txt[k]=char16to8(list[j]->nm[k]->wsbody[i+1])&0xff;
				}
				else txt[k]=0;
				
				if(fnd.t[i]!=table_T9Key[txt[k]]) p[k]++;
			}
		}
		if((!p[0])||(!p[1])||(!p[2]))
		{
			fnd.list[fnd.cnt++]=(int)list[j];
		}
	}
	sprintf(cltxt, "%s(%d)", fnd.t, fnd.cnt);
	SetCursorToMenuItem(data,0);
	Menu_SetItemCountDyn(data,fnd.cnt);
}

int cl_onkey(void *data, GUI_MSG *msg)
{
	tnomm=GetCurMenuItem(data);
	int t=0, tt=0;
	if (msg->keys==0x3D)
	{
		CLIST *cl0=(CLIST *)cltop;
// 		for(int k=0; k<tnomm; k++) cl0=cl0->next;
		if(fnd.n)
			cl0=(CLIST*)fnd.list[tnomm];
		else
			cl0=(CLIST*)cllist[tnomm];
		for(int j=0; j<NUMBERS_MAX; j++)
			if(cl0->num[j])
			{
				t++;
				tt=j;
			}
		if(!t)
		{
			MsgBoxError(1, (int)LG_NONUM);
			return -1;
		}
		else if(t==1) return add_to_num(cl0->num[tt]);
		else if(t>1)
		{
// 			tnomm=i;
			ShowExtMum(cl0,tt,t);
			return 1;
		}
		return(-1);
	}
	if (msg->gbsmsg->msg==KEY_DOWN)
	{
		int c=msg->gbsmsg->submess;
		if (((c>='0')&&(c<='9'))||(c=='#')||(c=='*'))
		{
			fnd.t[fnd.n++]=c;
// 			fnd.n++;
			ReCount(data);
// 			Menu_SetItemCountDyn(data,c-'0');
			return(-1);
		}
		if((c==RIGHT_SOFT)||(c==RED_BUTTON))
		{
			if(fnd.n)
			{
				if(!(--fnd.n))
				{
					sprintf(cltxt, LG_ADRBOOKD, cl_n);
					SetCursorToMenuItem(data,0);
					Menu_SetItemCountDyn(data,cl_n);
				}
				else
				{
					fnd.t[fnd.n]=0;
					ReCount(data);
				}
				return -1;
			}
		}
	}
	return(0);
}

void cl_ghook(void *data, int cmd)
{
  if (cmd==TI_CMD_CREATE)
  {
    fnd.list=malloc(cl_n*4);
  }
  if (cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
  if (cmd==TI_CMD_DESTROY)
  {
    mfree(fnd.list);
    zeromem(&fnd,sizeof(fnd));
    //FreeCLIST();
  }
}


void cl_iconhndl(void *data, int curitem, void *unk)
{
  void *item=AllocMLMenuItem(data);
  CLIST *cl0;//=(CLIST *)cltop;
  int t=0, tt;//, p;
  //char txt[32];
  //int i=0;
  //while(i<curitem)
  //{
  //if(fnd.n)
  //{
  //fnd1:
  //p=0;
  //zeromem(txt,32);
  //for(int j=0; j<32; j++)
  //{
  //txt[j]=(char16to8(cl0->name->wsbody[j+1]))&0xff;
  //if(j>=cl0->name->wsbody[0]) j=32;
  //}
  //ws_2str(cl0->name, txt, wstrlen(cl0->name));
  //for(int j=0; j<fnd.n; j++)
  //if(fnd.t[j]!=table_T9Key[txt[j]]) p++;
  //if(p)
  //{
  //cl0=(CLIST*)(cl0->next);
  //goto fnd1;
  //}
  //if(i<curitem-1) cl0=cl0->next;
  //}
  //else cl0=cl0->next;
  //i++;
  //}
  if(fnd.n)
    cl0=(CLIST*)fnd.list[curitem];
  else
    cl0=(CLIST*)cllist[curitem];
  WSHDR *ws1=AllocMenuWS(data,cl0->name->wsbody[0]);
  WSHDR *ws2=AllocMenuWS(data,30);
  wstrcat(ws1, cl0->name);
  for(int j=0; j<NUMBERS_MAX; j++)
    if(cl0->num[j])
    {
      t++;
      tt=j;
    }
  if(!t)
    wsprintf(ws2, perc_t, LG_NONUM);
  else if(t==1)
    wstrcat(ws2, cl0->num[tt]);
  else if(t>1)
  {
    if(cl0->num[2]) wstrcat(ws2, cl0->num[2]);
    else wstrcat(ws2, cl0->num[tt]);
  }
  SetMLMenuItemText(data, item, ws1, ws2, curitem);
}

static const ML_MENU_DESC cl=
{
  8,
 cl_onkey,
 cl_ghook,
 NULL,
 menusoftkeys,
 &menu_skt,
 0x11,
 cl_iconhndl,
 NULL,   //Items
 NULL,   //Procs
 0,   //n
 1
};

int Cont_list(void *ed_gui, int n)
{
  //ConstructList();
  zeromem(&fnd,sizeof(fnd));
  if(cl_n)
  {
    edsms_gui=ed_gui;
    sprintf(cltxt,LG_ADRBOOKD,cl_n);
    strcpy(pics_menu,pic_folder);
    strcat(pics_menu,"adr.png");
    A_ICONS[0]=(int)pics_menu;
    clhdr.icon=A_ICONS;
    patch_header(&clhdr);
    return(CreateMultiLinesMenu(0,0,&cl,&clhdr,n,cl_n));
  }
  MsgBoxError(1,(int)LG_EMPTY);
  return 0;
}

