#include "fm.c"

char *tempnm;
int _setname(void);
extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

// отрисовка
void instm_dr(RECT cv, int lev), // инструменты
	
	slm_dr(RECT cv, int lev), // слои 
	sslm_dr(RECT cv, int lev), // выбор слоя 
	ssslm_dr(RECT cv, int lev), // меню слоя 
	newslm_dr(RECT cv, int lev), // новы слой 
	delslm_dr(RECT cv, int lev), // удаление слоя 
	
	cm_dr(RECT cv, int lev), // цвета 
	colorm_dr(RECT cv, int lev), // выбор цвета 
	
	pm_dr(RECT cv, int lev), // картинка 
	oppicm_dr(RECT cv, int lev), // уже открытые
	picopm_dr(RECT cv, int lev), // уже открытые
	newpicm_dr(RECT cv, int lev), // новая
	savepm_dr(RECT cv, int lev), // сохранение 
	postsavem_dr(RECT cv, int lev); // сохранение 

// клавиатура
int	instm_key(GUI_MSG *msg, MENU_GUI *data), // инструменты
	
	slm_key(GUI_MSG *msg, MENU_GUI *data), // слои 
	sslm_key(GUI_MSG *msg, MENU_GUI *data), // выбор слоя 
	ssslm_key(GUI_MSG *msg, MENU_GUI *data), // меню слоя 
	newslm_key(GUI_MSG *msg, MENU_GUI *data), // новы слой 
	delslm_key(GUI_MSG *msg, MENU_GUI *data), // удаление слоя 
	
	cm_key(GUI_MSG *msg, MENU_GUI *data), // цвета 
	colorm_key(GUI_MSG *msg, MENU_GUI *data), // выбор цвета 
	
	pm_key(GUI_MSG *msg, MENU_GUI *data), // картинка 
	oppicm_key(GUI_MSG *msg, MENU_GUI *data), // уже открытые
	picopm_key(GUI_MSG *msg, MENU_GUI *data), // уже открытые
	newpicm_key(GUI_MSG *msg, MENU_GUI *data), // новая
	savepm_key(GUI_MSG *msg, MENU_GUI *data), // сохранение 
	postsavem_key(GUI_MSG *msg, MENU_GUI *data), // сохранение 
	
	create_ed(void);

RECT mcv[5]={{2,YDISP+2,0,0},{12,YDISP+12,0,0},{22,YDISP+22,0,0},{32,YDISP+32,0,0},{42,YDISP+42,0,0}};

MENU_PARAM ml[8],
	tmpm={0,0,"","",0,0}; // временная структура для создания нового подменю
static const MENU_PARAM
	// инструменты
		instm={5,0,"выбор","назад",{0,0,0,0},instm_key,instm_dr}, // инструменты
	// слои
		slm=	{3,0,"выбор",	"назад",	{0,0,0,0},	slm_key,	slm_dr}, // слои 
		sslm=	{5,0,"выбор"	,"назад",	{0,0,0,0},	sslm_key,	sslm_dr}, // выбор слоя 
		ssslm=	{3,0,"выбор",	"назад",	{0,0,0,0},	ssslm_key,	ssslm_dr}, // меню слоя 
		newslm=	{2,0,"выбор",	"назад",	{0,0,0,0},	newslm_key,	newslm_dr}, // новы слой 
		delslm=	{1,0,"ДА",		"НЕТ",		{0,0,0,0},	delslm_key,	delslm_dr}, // удаление слоя 
	// цвет
		cm=		{3,0,"выбор","назад",	{0,0,0,0},	cm_key,		cm_dr}, // цвета 
		colorm=	{5,0,"сохр.","отмена",	{0,0,0,0},	colorm_key,	colorm_dr}, // выбор цвета 
	// картинка
		pm=			{5,0,"выбор",	"назад",{0,0,0,0},	pm_key,			pm_dr}, // картинка 
		oppicm=		{1,0,"выбор",	"назад",{0,0,0,0},	oppicm_key,		oppicm_dr}, // уже открытые
		picopm=		{3,0,"выбор",	"назад",{0,0,0,0},	picopm_key,		picopm_dr}, // опции картинки
		newpicm=	{5,0,"создать",	"назад",{0,0,0,0},	newpicm_key,	newpicm_dr}, // новая
		savepm=		{4,0,"выбор",	"назад",{0,0,0,0},	savepm_key,		savepm_dr}, // сохранение 
		postsavem=	{1,0,"",		"Ok",	{0,0,0,0},	postsavem_key,	postsavem_dr}; // ожидание при сохранении 
		


////////////////////////////////////////////////////////////
// ************************** МЕНЮ **********************//
////////////////////////////////////////////////////////////

#define MENU_BACK 1
#define MENU_NOTH 2
#define MENU_CLOSE 3
#define MENU_EXIT 0xff


static const char *bitnm[]={"8бит","16бит","32бита"},
		*colnm[]={"ЦВЕТ 1","ЦВЕТ 2","ЦВЕТ ФОНА"},
		*visibility[]={"невидимый","видимый"};
		//mm_list[]="  ГЛ.МЕНЮ\nслои\nинструменты\nцвета\nкартинка\nоб эльфе\nнастройка\nвыход",
		//cm_list[]="  ЦВЕТА\nцвет 1\nцвет 2\nфон";
char *sl_list,
	sl0_list[6][19],
	*instm_list;


// отрисовка меню
void standart_dr(WSHDR *list, RECT cv, int lev)
{
	DrawRectangle(cv.x-1,cv.y-f_h-1,cv.x2-10,cv.y+1,0,white,black);
	DrawRectangle(cv.x-1,cv.y-1,cv.x2+1,cv.y2+1,0,white,black);
	DrawRectangle(cv.x,cv.y+ml[lev].pos*f_h,cv.x2,cv.y+(ml[lev].pos+1)*f_h,0,white,red);
	DrawString(list,cv.x+1,cv.y-f_h+1,cv.x2-1,SCR.sh,FONT_SMALL,1,white,NULL);
}

void standart_dr_sl(WSHDR *list, RECT cv, int lev)
{
	DrawRectangle(cv.x+10,cv.y-f_h-1,cv.x2+1,cv.y+1,0,white,black);
	DrawRectangle(cv.x-1,cv.y-1,cv.x2+1,cv.y2+1,0,white,black);
	DrawRectangle(cv.x,cv.y+ml[lev].pos*f_h,cv.x2,cv.y+(ml[lev].pos+1)*f_h,0,white,red);
	DrawString(list,cv.x+1,cv.y-f_h+1,cv.x2-1,SCR.sh,FONT_SMALL,4,white,NULL);
}

// создание нового меню
void newm(MENU_GUI *data, MENU_PARAM newm)
{
	//data->lev++;
	ml[data->lev]=newm;
	data->sh_all=1;
	
	patch_rect(&ml[data->lev].cv, mcv[data->lev].x, mcv[data->lev].y,
				mcv[data->lev].x+SCR.sw-30, mcv[data->lev].y+(ml[data->lev].cnt)*f_h );
	
	//ml[data->lev].cv.x2=mcv[data->lev].x+SCR.sw-30;
	//mcv[data->lev].cv.y2=mcv[data->lev].y+(ml[data->lev].cnt)*f_h;
}

void newm_sl(MENU_GUI *data, MENU_PARAM newm)
{
	//data->lev++;
	ml[data->lev]=newm;
	
	patch_rect(&ml[data->lev].cv, SCR.sw-10-10*data->lev-SCR.sw+50, PCPS.y2-10*data->lev-ml[data->lev].cnt*f_h,
				SCR.sw-10-10*data->lev, PCPS.y2-10*data->lev );
	
	//mcv[data->lev].x2=mcv[data->lev].x+SCR.sw-30;
	//mcv[data->lev].y2=mcv[data->lev].y+(ml[data->lev].cnt)*f_h;
}

void zmenu_dr(RECT cv, int lev)
{
	DrawRectangle(0,YDP,SCR.sw,SCR.sh,0,white,black);
	DrPic();
	DrawRectangle(0,YDP, SCR.sw,SCR.sh, 0,blpr,blpr);
	patch_rect(&cv, SCR.sw-10-10*lev-SCR.sw+50, PCPS.y2-10*lev-ml[lev].cnt*f_h,
				SCR.sw-10-10*lev, PCPS.y2-10*lev );
	wsprintf(ws, perc_t, "  ZOOM:\n(+) увеличить\n(-) уменьшить");
	standart_dr_sl(ws, cv, lev);
}

int zmenu_key(GUI_MSG *msg, MENU_GUI *data)
{
	if (msg->gbsmsg->msg==KEY_DOWN)
	{
		switch(msg->gbsmsg->submess)
		{
			case LEFT_BUTTON:
			case RIGHT_SOFT:
			case RED_BUTTON:
				return MENU_BACK;
			case LEFT_SOFT:
			case RIGHT_BUTTON:
			case ENTER_BUTTON:
			case '5':
				switch(ml[data->lev].pos)
				{
					case 0:
						dozoom(p->z+1);
					 break;
					case 1:
						dozoom(p->z-1);
					 break;
				}
			 return MENU_CLOSE;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


/////////////////////////////// ГЛ. МЕНЮ ////////////////


void mm_dr(RECT cv, int lev)
{
	DrawRectangle(0,YDP,SCR.sw,SCR.sh,0,white,black);
	DrPic();
	DrawRectangle(0,YDP, SCR.sw,SCR.sh, 0,blpr,blpr);
	wsprintf(ws,perc_t,"  ГЛ.МЕНЮ\nинструменты\nцвета\nслои\nкартинка\nоб эльфе\nнастройка\nвыход");
	standart_dr(ws, cv, lev);
}

int mm_key(GUI_MSG *msg, MENU_GUI *data)
{
	int i=0, len=0;
	char *inf;
	if (msg->gbsmsg->msg==KEY_DOWN)
	{
		switch(msg->gbsmsg->submess)
		{
			case LEFT_BUTTON:
				return MENU_BACK;
			case LEFT_SOFT:
			case RIGHT_BUTTON:
			case ENTER_BUTTON:
			case '5':
				switch(ml[data->lev].pos)
				{
					case 0:
						data->lev++;
						newm(data, instm);
						do
						{
							len+=strlen(inst[i].nm);
							i++;
						}while(inst[i].n);
						instm_list=malloc(14+len+2*i);
						sprintf( instm_list, "%s\n%s\n", "ИНСТРУМЕНТЫ", inst[0].nm );
						i=1;
						do
						{
							sprintf( instm_list+strlen(instm_list), "%s\n", inst[i].nm );
							i++;
						}while(inst[i].n);
						ml[data->lev].cnt=i;
					 break;
					case 1:
						data->lev++;
						newm(data, cm);
					 break;
					case 2:
						newm(data, slm);
						patch_rect(&ml[data->lev].cv, 0, 0, 0, 0);
						ml[data->lev].cnt=p->cs;
						ml[data->lev].pos=p->cs-p->ns-1;
					 break;
					case 3:
						data->lev++;
						newm(data, pm);
					 break;
					case 4:
						inf=malloc(128);
						sprintf(inf, "Paintt v%s\nby titron\n\npaintt.h2m.ru",ver);
						ShowMSG(1, (int)inf);
						mfree(inf);
					 break;
					case 5:
						wsprintf(fws,perc_t,successed_config_filename);
						ExecuteFile(fws,NULL,NULL);
					 break;
					case 6:
						return MENU_EXIT;
						//MsgBoxYesNo(1,(int)"Выход?",ExitProc);
					 //break;
					default: ShowMSG(1, (int)"В разработке :)"); break;
				}
			 break;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


//////////////////////////////////// Инструменты ///////////////////////////


void instm_dr(RECT cv, int lev)
{
	wsprintf(ws,perc_t,instm_list);
	standart_dr(ws, cv, lev);
}

int instm_key(GUI_MSG *msg, MENU_GUI *data)
{
	if (msg->gbsmsg->msg==KEY_DOWN)
	{
		switch(msg->gbsmsg->submess)
		{
			case RED_BUTTON:
			case RIGHT_SOFT:
			case LEFT_BUTTON:
				mfree(instm_list);
				return MENU_BACK;
			case LEFT_SOFT:
			case RIGHT_BUTTON:
			case ENTER_BUTTON:
			case '5':
				mfree(instm_list);
				Pt.i=ml[data->lev].pos;
				return MENU_CLOSE;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


/////////////////////////// Слои ///////////////////////

void do_1_sl()
{
	unsigned int i,k;
	if(!p->sl[1].v)zeromem(p->sl[1].map, p->sl[1].w*p->sl[1].h*4);
	for(k=2; k<p->cs; k++)
	 if(p->sl[k].v)
	   for(i=0; i<p->sl[1].w*p->sl[1].h; i++)
		if(p->sl[k].map[i*4+3]>25)
			memcpy(p->sl[1].map+i*4, p->sl[k].map+i*4, 4);
	p->cs=2;
	p->ns=1;
}

void slm_dr(RECT cv, int lev)
{
	DrawRectangle(0,YDP,SCR.sw,SCR.sh,0,white,black);
	DrPic();
	DrawRectangle(0,YDP, SCR.sw,SCR.sh, 0,blpr,blpr);
	//if(!SWOW_SL) PCPS.x2=SCR.sw-13;
	DrawSl();
	fillTriangle(SCR.sw-20, PCPS.y2-12*(p->cs-ml[lev].pos),
				SCR.sw-20, PCPS.y2-12*(p->cs-ml[lev].pos)+8,
				SCR.sw-14, PCPS.y2-12*(p->cs-ml[lev].pos)+4, 0, white, red);
	//DrawRectangle(PCPS.x2+3, PCPS.y2-12*(i+1), SCR.sw-2, PCPS.y2-12*(i+1)+8, 0,white,CoL);
	
	str_2ws(ws,p->sl[p->cs-ml[lev].pos-1].nm, 19);
	DrawString(ws,PCPS.x2-9-Get_WS_width(ws, FONT_SMALL),PCPS.y2-12*(p->cs-ml[lev].pos)+8-f_h,
				PCPS.x2-9,PCPS.y2-12*(p->cs-ml[lev].pos)+8,FONT_SMALL,1,white,black);
	//standart_dr(ws, cv, lev);
}

int slm_key(GUI_MSG *msg, MENU_GUI *data)
{
	//int i;
	if (msg->gbsmsg->msg==KEY_DOWN)
	{
		switch(msg->gbsmsg->submess)
		{
			case LEFT_BUTTON:
			case RIGHT_SOFT:
			case RED_BUTTON:
				if(!SWOW_SL) PCPS.x2=SCR.sw;
				//do_vpic();
				return MENU_BACK;
			case LEFT_SOFT:
			case RIGHT_BUTTON:
			case ENTER_BUTTON:
			case '5':
				data->lev++;
				newm_sl(data, sslm);
				/* switch(ml[data->lev].pos)
				{
					case 0:
						data->lev++;
						newm(data, sslm);
						ml[data->lev].cnt=p->cs;
						ml[data->lev].pos=ml[data->lev].cnt-p->ns-1;
						sl_list=malloc(18*(ml[data->lev].cnt+1));
						sprintf( sl_list, perc_sn, "ВЫБОР СЛОЯ");
						for(i=p->cs-1; i>=0; i--) sprintf( sl_list+strlen(sl_list), perc_sn, p->sl[i].nm);
					 break;
					case 1:
						data->lev++;
						newm(data, newslm);
						ml[data->lev].cnt=p->cs+1;
						ml[data->lev].pos=ml[data->lev].cnt-p->ns-2;
						sprintf( sl0_list[0], "SLOY %d", p->cs );
						for(i=p->cs-1; i>=0; i--) strcpy( sl0_list[p->cs-i], p->sl[i].nm);
					 break;
					case 2:
						do_1_sl();
					 return MENU_CLOSE;
					default: ShowMSG(1, (int)"В разработке :)"); break;
				} */
			 break;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


/////////////////////////// Меню слоя //////////////////


void sslm_dr(RECT cv, int lev)
{
	wsprintf(ws,"%t%t%t", "\nактивным\n", visibility[p->sl[p->cs-ml[lev-1].pos-1].v], "\nпереименовать\nновый\nудалить");
	standart_dr_sl(ws, cv, lev);
	str_2ws(ws,p->sl[p->cs-ml[lev-1].pos-1].nm,19);
	DrawString(ws,cv.x+1,cv.y-f_h,cv.x2-1,SCR.sh,FONT_SMALL,4,white,NULL);
}

int sslm_key(GUI_MSG *msg, MENU_GUI *data)
{
	int i;
	if (msg->gbsmsg->msg==KEY_DOWN)
	{
		switch(msg->gbsmsg->submess)
		{
			case LEFT_BUTTON:
			case RIGHT_SOFT:
			case RED_BUTTON:
				//mfree(sl_list);
				return MENU_BACK;
			case LEFT_SOFT:
			case RIGHT_BUTTON:
			case ENTER_BUTTON:
			case '5':
				i=p->cs-ml[data->lev-1].pos-1;
				switch(ml[data->lev].pos)
				{
					case 0:
						p->ns=i;
					 return MENU_CLOSE;
					case 1:
						if(p->sl[i].v) p->sl[i].v=0;
						else p->sl[i].v=1;
					 break;
					case 2:
						tempnm=p->sl[i].nm;
						_setname();
					 break;
					case 3:
						data->lev++;
						newm_sl(data, newslm);
					 break;
					case 4:
						data->lev++;
						newm_sl(data, delslm);
					 return 0;
				}
				//data->lev++;
				//newm_sl(data, ssslm);
				//if(p->sl[ml[lev].cnt-ml[lev].pos-1].v) p->sl[ml[lev].cnt-ml[lev].pos-1].v=0;
				//else p->sl[ml[lev].cnt-ml[lev].pos-1].v=1;
			 break;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


/////////////////////////// Меню слоя //////////////////////

/* 
void ssslm_dr(RECT cv, int lev)
{
	wsprintf(ws, "  %t\n%t\n%t", p->sl[ml[lev-1].cnt-ml[lev-1].pos-1].nm, visibility[p->sl[ml[lev-1].cnt-ml[lev-1].pos-1].v], "активным\nудалить");
	standart_dr_sl(ws, cv, lev);
}

int ssslm_key(GUI_MSG *msg, MENU_GUI *data)
{
	if (msg->gbsmsg->msg==KEY_DOWN)
	{
		switch(msg->gbsmsg->submess)
		{
			case LEFT_BUTTON:
			case RIGHT_SOFT:
			case RED_BUTTON:
				return MENU_BACK;
			case LEFT_SOFT:
			case RIGHT_BUTTON:
			case ENTER_BUTTON:
			case '5':
				switch(ml[data->lev].pos)
				{
					case 0:
						if(p->sl[ml[data->lev-1].cnt-ml[data->lev-1].pos-1].v) p->sl[ml[data->lev-1].cnt-ml[data->lev-1].pos-1].v=0;
						else p->sl[ml[data->lev-1].cnt-ml[data->lev-1].pos-1].v=1;
					 break;
					case 1:
						p->ns=ml[data->lev-1].cnt-ml[data->lev-1].pos-1;
					 return MENU_CLOSE;
					case 2:
						tmpm=delslm;
						return 0;
					default: ShowMSG(1, (int)"В разработке :)");
				}
			 break;
		}
	}
	return 0;
} */


/////////////////////////// Новый слой //////////////////////


void newslm_dr(RECT cv, int lev)
{
	wsprintf(ws, perc_t, "  Новый слой\nнад этим\nпод зтим");
	standart_dr_sl(ws, cv, lev);
}

int newslm_key(GUI_MSG *msg, MENU_GUI *data)
{
	char tempsln;
	if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))
	{
		switch(msg->gbsmsg->submess)
		{
			case LEFT_BUTTON:
			case RIGHT_SOFT:
			case RED_BUTTON:
				return MENU_BACK;
			case LEFT_SOFT:
			case RIGHT_BUTTON:
			case ENTER_BUTTON:
			case '5':
				switch(ml[data->lev].pos)
				{
					case 0:
						tempsln=p->cs-ml[data->lev-2].pos;
					 break;
					case 1:
						tempsln=p->cs-ml[data->lev-2].pos-1;
					 break;
				}
				new_sl(tempsln, "New");
				tempnm=p->sl[tempsln].nm;
				_setname();
				ml[data->lev-2].cnt++;
				return MENU_BACK;
			// case DOWN_BUTTON:
			// case '8':
				// ml[data->lev].pos++;
				// if(ml[data->lev].pos>=ml[data->lev].cnt-1) ml[data->lev].pos=0;
			 // return MENU_NOTH;
			// case UP_BUTTON:
			// case '2':
				// ml[data->lev].pos--;
				// if(ml[data->lev].pos>=ml[data->lev].cnt-1) ml[data->lev].pos=ml[data->lev].cnt-2;
			 // return MENU_NOTH;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


/////////////////////////// Удаление слоя //////////////////////////


void delslm_dr(RECT cv, int lev)
{
	DrawRectangle(0,0,SCR.sw,SCR.sh,0,red,black);
	wsprintf(ws, "%t\n%t", "Удалить слой?", p->sl[p->cs-ml[lev-2].pos-1].nm);
	DrawString(ws,0,50,SCR.sw,SCR.sh,FONT_LARGE,2,white,NULL);
}

int delslm_key(GUI_MSG *msg, MENU_GUI *data)
{
	if (msg->gbsmsg->msg==KEY_DOWN)
	{
		switch(msg->gbsmsg->submess)
		{
			case LEFT_BUTTON:
			case RIGHT_SOFT:
			case RED_BUTTON:
				return MENU_BACK;
			case LEFT_SOFT:
			case ENTER_BUTTON:
			case '5':
				del_sl(p->cs-ml[data->lev-2].pos-1);
				ml[data->lev-2].cnt--;
				return MENU_BACK;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


//////////////////////////////////// Цвета ////////////////////////////


void cm_dr(RECT cv, int lev)
{
	wsprintf(ws,perc_t,"  ЦВЕТА\nцвет 1\nцвет 2\nфон");
	standart_dr(ws, cv, lev);
}

int cm_key(GUI_MSG *msg, MENU_GUI *data)
{
	if (msg->gbsmsg->msg==KEY_DOWN)
	{
		switch(msg->gbsmsg->submess)
		{
			case LEFT_BUTTON:
			case RIGHT_SOFT:
			case RED_BUTTON:
					docols(1);
				return MENU_BACK;
			case LEFT_SOFT:
			case RIGHT_BUTTON:
			case ENTER_BUTTON:
			case '5':
				memcpy(tmp_col.c, COL[ml[data->lev].pos].c, 4);
				tmp_col.c32=ml[data->lev].pos;
				data->lev++;
				newm(data, colorm);
				DrawRectangle(ml[data->lev-1].cv.x-1,ml[data->lev-1].cv.y-f_h-1,ml[data->lev-1].cv.x2+1,ml[data->lev-1].cv.y2+1,0,blpr,blpr);
				data->sh_all=0;
			 break;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


//////////////////////////////////// Выбор цвета ////////////////////////////

void convcol()
{
	//int c32;
	if(tmp_col.c[3]==0)
	{
		tmp_col.c16=prz.c16;
		tmp_col.c8=prz.c8;
	}
	else
	{
		//c32=(tmp_col.c[3]<<24)+(tmp_col.c[2]<<16)+(tmp_col.c[1]<<8)+(tmp_col.c[0]);
		tmp_col.c16=RGB_24_16(tmp_col.c);
		tmp_col.c8=RGB_24_8(tmp_col.c);
	}
}

void colorm_dr(RECT cv, int lev)
{
	convcol();
	DrawRectangle(cv.x-1,cv.y-f_h-1,cv.x2-10,cv.y+1,0,white,black);
	DrawRectangle(cv.x-1,cv.y-1,cv.x2+1,cv.y+8*f_h+3,0,white,black);
	if(!ml[lev].pos) DrawRectangle(cv.x,cv.y+ml[lev].pos*f_h,cv.x2,cv.y+(ml[lev].pos+1)*f_h,0,white,red);
	else 
	{
		DrawRectangle(cv.x,cv.y+f_h,cv.x2,cv.y+2*f_h,0,white,red);
		DrawRectangle(cv.x+5,cv.y+(ml[lev].pos+1)*f_h+2,cv.x2-1,cv.y+(ml[lev].pos+2)*f_h+1,0,white,red);
	}
	wsprintf(ws,"  %t\n%t",colnm[tmp_col.c32],"прозрачный\nцвет",tmp_col.c[0],tmp_col.c[1],tmp_col.c[2],tmp_col.c[3]);
		DrwImg((IMGHDR *)&small_prf, cv.x2-3*sf_h-3, cv.y+8*f_h-2*sf_h, white, black);
		DrawRectangle(cv.x2-3*sf_h-3, cv.y+8*f_h-2*sf_h,cv.x2-2,cv.y+8*f_h,0,tmp_col.c,tmp_col.c);
	DrawString(ws,cv.x+1,cv.y-f_h+1,cv.x2-1,SCR.sh,FONT_SMALL,1,white,NULL);
	wsprintf(ws," R:%02X\n G:%02X\n B:%02X\n A:%02X\n8b:%02X\n16b:%04X",tmp_col.c[0],tmp_col.c[1],tmp_col.c[2],tmp_col.c[3],tmp_col.c8,tmp_col.c16);
	DrawString(ws,cv.x+6,cv.y+2*f_h+3,cv.x2-1,SCR.sh,FONT_SMALL,1,white,NULL);
}

int colorm_key(GUI_MSG *msg, MENU_GUI *data)
{
	int st=1;
	if(ml[data->lev].pos)
		switch(msg->gbsmsg->msg)
		{
		 case LONG_PRESS: st=0x10;
		 case KEY_DOWN:
			switch(msg->gbsmsg->submess)
			{
				case LEFT_BUTTON:
					tmp_col.c[ml[data->lev].pos-1]-=st;
				 break;
				case RIGHT_BUTTON:
					tmp_col.c[ml[data->lev].pos-1]+=st;
				 break;
				case ENTER_BUTTON:
				case LEFT_SOFT:
				case '5':
					data->sh_all=1;
					COL[tmp_col.c32]=tmp_col;
				 return MENU_BACK;
			}
		  break;
			//DirectRedrawGUI();
		}
	else
		switch(msg->gbsmsg->msg)
		{
		 case KEY_DOWN:
			switch(msg->gbsmsg->submess)
			{
				case RIGHT_BUTTON:
				case ENTER_BUTTON:
				case '5':
					memcpy(tmp_col.c, prz.c, 4);
				 return MENU_NOTH;
				case LEFT_SOFT:
					COL[tmp_col.c32]=tmp_col;
				case LEFT_BUTTON:
					data->sh_all=1;
				 return MENU_BACK;
			}
		}
	return 0;
}


//////////////////////////////////// Меню картинки ////////////////////////////


void pm_dr(RECT cv, int lev)
{
	wsprintf(ws,perc_t,"  КАРТИНКА\nоткрытые\nпредпросмотр\nновая\nоткрыть\nсохранить");
	standart_dr(ws, cv, lev);
}

int pm_key(GUI_MSG *msg, MENU_GUI *data)
{
	if (msg->gbsmsg->msg==KEY_DOWN)
	{
		switch(msg->gbsmsg->submess)
		{
			case LEFT_BUTTON:
			case RIGHT_SOFT:
			case RED_BUTTON:
				return MENU_BACK;
			case LEFT_SOFT:
			case RIGHT_BUTTON:
			case ENTER_BUTTON:
			case '5':
				switch(ml[data->lev].pos)
				{
					case 0:
						data->lev++;
						newm(data, oppicm);
						ml[data->lev].cnt=Pt.cp;
						patch_rect(&ml[data->lev].cv, mcv[data->lev].x, mcv[data->lev].y,
									mcv[data->lev].x+SCR.sw-30, mcv[data->lev].y+(ml[data->lev].cnt)*f_h );
					 break;
					case 1:
						Preview();
					 break;
					case 2:
						//tmp_p=*p;
						zeromem(&tmp_p, sizeof(PIC_PARAM));
						data->lev++;
						sprintf(tmp_p.nm, "%s_%d", "Image", Pt.cp+1);
						tmp_p.w=DEF_W;
						tmp_p.h=DEF_H;
						newm(data, newpicm);
					 break;
					case 3:
						fmtype=1;
						open_select_file_gui(&data->gui, 1);
					 return MENU_CLOSE;
					case 4:
						data->lev++;
						newm(data, savepm);
					 break;
					default: ShowMSG(1, (int)"В разработке :)"); break;
				}
			 break;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


//////////////////////////////////// открытые кортинки ////////////////////////////


void oppicm_dr(RECT cv, int lev)
{
	DrawRectangle(cv.x-1,cv.y-f_h-1,cv.x2-10,cv.y+1,0,white,black);
	DrawRectangle(cv.x-1,cv.y-1,cv.x2+1,cv.y2+1,0,white,black);
	DrawRectangle(cv.x,cv.y+ml[lev].pos*f_h,cv.x2,cv.y+(ml[lev].pos+1)*f_h,0,white,red);
	wsprintf(ws, perc_t, "  Открытые");
	DrawString(ws,cv.x+1,cv.y-f_h+1,cv.x2-1,SCR.sh,FONT_SMALL,1,white,NULL);
	for (int i=0; i<Pt.cp; i++)
	{
		str_2ws(ws,picp[i].nm,32);
		DrawString(ws,cv.x+1,cv.y+f_h*i+1,cv.x2-1,SCR.sh,FONT_SMALL,1,white,NULL);
	}
}

int oppicm_key(GUI_MSG *msg, MENU_GUI *data)
{
	if (msg->gbsmsg->msg==KEY_DOWN)
	{
		switch(msg->gbsmsg->submess)
		{
			case LEFT_BUTTON:
			case RIGHT_SOFT:
			case RED_BUTTON:
				//mfree(op_list);
				return MENU_BACK;
			case LEFT_SOFT:
			case RIGHT_BUTTON:
			case ENTER_BUTTON:
			case '5':
				data->lev++;
				newm(data, picopm);
				DrawRectangle(ml[data->lev-1].cv.x-1,ml[data->lev-1].cv.y-f_h-1,ml[data->lev-1].cv.x2+1,ml[data->lev-1].cv.y2+1,0,blpr,blpr);
				data->sh_all=0;
			 break;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


//////////////////////////////////// открытые кортинки ////////////////////////////


void picopm_dr(RECT cv, int lev)
{
	wsprintf(ws,perc_t,"\nвыбрать\nпереименовать\nзакрыть");
	standart_dr(ws, cv, lev);
	str_2ws(ws,picp[ml[lev-1].pos].nm,32);
	DrawString(ws,cv.x+1,cv.y-f_h,cv.x2-1,SCR.sh,FONT_SMALL,1,white,NULL);
}

int picopm_key(GUI_MSG *msg, MENU_GUI *data)
{
	if (msg->gbsmsg->msg==KEY_DOWN)
	{
		switch(msg->gbsmsg->submess)
		{
			case LEFT_BUTTON:
			case RIGHT_SOFT:
			case RED_BUTTON:
				//mfree(op_list);
				return MENU_BACK;
			case LEFT_SOFT:
			case RIGHT_BUTTON:
			case ENTER_BUTTON:
			case '5':
				switch(ml[data->lev].pos)
				{
					case 0:
						p=&picp[ml[data->lev-1].pos];
						cr2();
					 return MENU_CLOSE;
					case 1:
						tempnm=picp[ml[data->lev-1].pos].nm;
						_setname();
					 return MENU_BACK;
					default: ShowMSG(1, (int)"В разработке :)"); break;
				}
			 break;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


//////////////////////////////////// Новая картинка /////////////////


/* void newp(int decision)
{
	if(!decision)
	{
		&p=tmp_p;
		crpic();
	}
} */

void newpicm_dr(RECT cv, int lev)
{
	if(start) DrawRectangle(0,YDP,SCR.sw,SCR.sh,0,black,black);
	wsprintf(ws,"%t%d\n%t%d\n%t\n%t","  КАРТИНКА\nширина (x):",tmp_p.w,"высота (y):",tmp_p.h, bitnm[Pt.m], "фон\nимя");
	standart_dr(ws, cv, lev);
}

int newpicm_key(GUI_MSG *msg, MENU_GUI *data)
{
	int stp=1;
	switch (msg->gbsmsg->msg)
	{
		case LONG_PRESS: stp=10;
		case KEY_DOWN:
			switch(msg->gbsmsg->submess)
			{
				case LEFT_SOFT:
					if(start)
					{
						Pt.cp=1;
						Pt.np=0;
					}
					else
					{
						Pt.cp++;
						Pt.np=Pt.cp-1;
					}
					p=&picp[Pt.np];
					*p=tmp_p;
					//docols(0);
					crpic();
					return MENU_CLOSE;
					//else MsgBoxYesNo(1,(int)"Удалить\nредактируемую?",newp);
				 //return 3;
				case RED_BUTTON:
				case RIGHT_SOFT:
					if(start) return MENU_EXIT;
					else return MENU_BACK;
				case RIGHT_BUTTON:
				case '6':
					switch(ml[data->lev].pos)
					{
						case 0:
							tmp_p.w+=stp;
							#ifndef ELKA
							if(tmp_p.w>0xff) tmp_p.w=0;
							#endif
						 break;
						case 1:
							tmp_p.h+=stp;
							#ifndef ELKA
							if(tmp_p.h>0xff) tmp_p.h=0;
							#endif
						 break;
						case 2:
							if(Pt.m==2) Pt.m=0;
							else Pt.m++;
						 break;
					}
				case ENTER_BUTTON:
					switch(ml[data->lev].pos)
					{
						case 3:
							memcpy(tmp_col.c, COL[2].c, 4);
							tmp_col.c32=2;
							data->lev++;
							newm(data, colorm);
							DrawRectangle(ml[data->lev-1].cv.x-1,ml[data->lev-1].cv.y-f_h-1,ml[data->lev-1].cv.x2+1,ml[data->lev-1].cv.y2+1,0,blpr,blpr);
							data->sh_all=0;
						 break;
						case 4:
							tempnm=tmp_p.nm;
							_setname();
						 break;
					}
				 break;
				case LEFT_BUTTON:
				case '4':
					switch(ml[data->lev].pos)
					{
						case 0:
							tmp_p.w-=stp;
							#ifndef ELKA
							if(tmp_p.w>0xff) tmp_p.w=0xff;
							#endif
						 break;
						case 1:
							tmp_p.h-=stp;
							#ifndef ELKA
							if(tmp_p.h>0xff) tmp_p.h=0xff;
							#endif
						 break;
						case 2:
							if(Pt.m==0) Pt.m=2;
							else Pt.m--;
						 break;
						case 3:
							if(start) return MENU_EXIT;
							else return MENU_BACK;
					}
				 break;
			}
		//DirectRedrawGUI();
		break;
	}
	return 0;
}


//////////////////////////////////// Сохранение картинки ////////////////////////////

MENU_GUI *menudata;


void savepm_dr(RECT cv, int lev)
{
	wsprintf(ws,perc_t,"  Сохранение\n*.pti\n*.bmp\n*.gpf\n*.dat");
	standart_dr(ws, cv, lev);
}

int savepm_key(GUI_MSG *msg, MENU_GUI *data)
{
	if (msg->gbsmsg->msg==KEY_DOWN)
	{
		switch(msg->gbsmsg->submess)
		{
			case LEFT_BUTTON:
			case RIGHT_SOFT:
			case RED_BUTTON:
				return MENU_BACK;
			case LEFT_SOFT:
			case RIGHT_BUTTON:
			case ENTER_BUTTON:
			case '5':
				switch(ml[data->lev].pos)
				{
					case 0: SAVEp.doit=savePTI; break;
					case 1: SAVEp.doit=saveBMP; break;
					case 2: SAVEp.doit=saveGPF; break;
					case 3: SAVEp.doit=saveDAT; break;
				}
				SAVEp.btype=0;
				SAVEp.type=ml[data->lev].pos;
				if(SAVE_PATH[strlen(SAVE_PATH)-1]==_SLASH)
					strcpy(SAVEp.fl, SAVE_PATH);
				else sprintf(SAVEp.fl, "%s\\", SAVE_PATH);
				strcpy(SAVEp.nm, p->nm);
				menudata=data;
				create_ed();
			 break;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


//////////////////////////////////// Ожидание при сохранении картинки ////////////////////////////


void postsavem_dr(RECT cv, int lev)
{
	DrawRectangle(0,0,SCR.sw,SCR.sh,0,red,black);
	str_2ws(ws, fname, 256);
	DrawString(ws,3,YDP,SCR.sw-3,SCR.sh,FONT_SMALL,2,white,NULL);
	if(waitsave)
	{
		zeromem( ml[lev].bt2, 16 );
		wsprintf(ws, perc_t, "Сохранение\nЖдите!!!");
	}
	else
	{
		sprintf( ml[lev].bt2, "Ok" );
		wsprintf(ws, perc_t, "Сохранено\nжми кнопку");
	}
	DrawString(ws,0,YDP+3*f_h,SCR.sw,SCR.sh,FONT_MEDIUM_BOLD,2,white,NULL);
	DrawRectangle(10,SCR.sh-3*f_h,SCR.sw-10,SCR.sh-2*f_h,0,white,black);
	DrawRectangle(11,SCR.sh-3*f_h+1,11+(SCR.sw-22)*SAVEp.cur_part/SAVEp.parts,SCR.sh-2*f_h-1,0,blue,blue);
}

int postsavem_key(GUI_MSG *msg, MENU_GUI *data)
{
	if (msg->gbsmsg->msg==KEY_DOWN)
	{
		/* switch(msg->gbsmsg->submess)
		{
			case LEFT_BUTTON:
			case RIGHT_SOFT:
			case RED_BUTTON: */
		if(waitsave) return MENU_NOTH;
		else
		{
			switch(msg->gbsmsg->submess)
			{
				case RIGHT_SOFT:
				case RED_BUTTON:
				//case LEFT_SOFT:
				case ENTER_BUTTON:
				case '5':
					zeromem(&SAVEp, sizeof(SAVEp));
					return MENU_CLOSE;
			}
		}
		/* 	case LEFT_SOFT:
			case RIGHT_BUTTON:
			case ENTER_BUTTON:
			case '5':
				if(waitsave)
			 break;
		} */
		//DirectRedrawGUI();
	}
	return MENU_NOTH;
}


// *********************** ОСНОВА МЕНЮ ******************** //


void m_Redraw(MENU_GUI *data)
{
	int i;
  if(data->sh_all==1)
	for(i=0; i<data->lev; i++)
	{
		ml[i].dr(ml[i].cv ,i);
		DrawRectangle(ml[i].cv.x-1,ml[i].cv.y-f_h-1,ml[i].cv.x2+1,ml[i].cv.y2+1,0,blpr,blpr);
	}
	ml[data->lev].dr(ml[data->lev].cv ,data->lev);
	DrawRectangle(0, SCR.sh-f_h-1, SCR.sw, SCR.sh+1, 0, white, black);
	wsprintf(ws,perc_t,ml[data->lev].bt1);
	DrawString(ws,3,SCR.sh-f_h,SCR.sw/2,SCR.sh,FONT_SMALL,1,white,NULL);
	wsprintf(ws,perc_t,ml[data->lev].bt2);
	DrawString(ws,SCR.sw/2,SCR.sh-f_h,SCR.sw-3,SCR.sh,FONT_SMALL,4,white,NULL);
}

void m_Create(MENU_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

void m_Close(MENU_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

void m_Focus(MENU_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
	DisableIDLETMR();
	#ifdef ELKA
	if(UseFullScr) DisableIconBar(1);
	#endif
  data->gui.state=2;
}

void m_Unfocus(MENU_GUI *data, void (*mfree_adr)(void *))
{
	#ifdef ELKA
	if(UseFullScr) DisableIconBar(0);
	#endif
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int m_OnKey(MENU_GUI *data, GUI_MSG *msg)
{
	switch(ml[data->lev].key(msg, data))
	{
		case MENU_CLOSE: do_vpic(); return 1;
		case MENU_BACK:
			data->sh_all=1;
			if(data->lev==0){do_vpic(); return 1;}
			else{ data->lev--;
			DirectRedrawGUI();
			return 0;}
		case MENU_EXIT:
			MsgBoxYesNo(1,(int)"Выход?",ExitProc);
		case MENU_NOTH:
			DirectRedrawGUI();
			return 0;
	}
	if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))
	{
		switch(msg->gbsmsg->submess)
		{
			case RED_BUTTON:
			case RIGHT_SOFT:
				data->sh_all=1;
				if(data->lev==0){do_vpic(); return 1;}
				else data->lev--;
			 break;
			case DOWN_BUTTON:
			case '8':
				ml[data->lev].pos++;
				if(ml[data->lev].pos>=ml[data->lev].cnt) ml[data->lev].pos=0;
			 break;
			case UP_BUTTON:
			case '2':
				ml[data->lev].pos--;
				if(ml[data->lev].pos>=ml[data->lev].cnt) ml[data->lev].pos=ml[data->lev].cnt-1;
			 break;
		}
		DirectRedrawGUI();
	}
	return(0);
}

void m_Destroy(MENU_GUI *data, void (*mfree_adr)(void *))
{
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(data,mfree_adr);
}

const void * const m_methods[11]={
  (void *)m_Redraw,
  (void *)m_Create,
  (void *)m_Close,
  (void *)m_Focus,
  (void *)m_Unfocus,
  (void *)m_OnKey,
  0,
  (void *)m_Destroy,
  (void *)met0,
  (void *)met0,
  0
};

int menu(MENU_PARAM m)
{
  MENU_GUI *m_gui=malloc(sizeof(MENU_GUI));
  zeromem(m_gui,sizeof(MENU_GUI));
  patch_rect((RECT*)&Canvas_2,0,YDP,ScreenW()-1,ScreenH()-1);
  m_gui->gui.canvas=(void *)(&Canvas_2);
  m_gui->gui.flag30=2;
  m_gui->gui.methods=(void *)m_methods;
  m_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  ml[0]=m;
  m_gui->lev=0;
	m_gui->sh_all=1;

	patch_rect(&ml[0].cv, mcv[0].x, mcv[0].y,
	mcv[0].x+SCR.sw-30, mcv[0].y+(ml[0].cnt)*f_h );
  //mcv[0].x2=mcv[0].x+SCR.sw-30;
  //mcv[0].y2=mcv[0].y+(m.cnt)*f_h;
  return(CreateGUI(m_gui));
}





///////////////////////////////////////////////////////////////
// *********************** Ввод имени ************************//
///////////////////////////////////////////////////////////////


SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"выбор"},
  {0x0001,0x0000,(int)"назад"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};




/////////////////////////////////////////////////////////



void kbps(int i)
{
	if(!i) 
	{
		if(SAVEp.doit(1)==RES_OK)
		{
				menudata->lev++;
				newm(menudata, postsavem);
				menudata->sh_all=0;
				DirectRedrawGUI();
		}
		else MsgBoxError(1,(int)"Файл не создаётся!!!");
	}
	//SAVEp.doit(1);
}


/* 
typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM; */


void ed1_locret(void){}

void on_utf8ec(USR_MENU_ITEM *item)
{
  if (item->type==0)
  {
    switch(item->cur_item)
    {
    case 0:
      wsprintf(item->ws,perc_t,"Select");
      break;
    // case 1:
      // wsprintf(item->ws,_percent_t,"SelectFile");
      // break;
    }
  }
  if (item->type==1)
  {
    switch(item->cur_item)
    {
    case 0:
		fmtype=0;
		open_select_file_gui(item->user_pointer, 1);
      break;
    // case 1:
      // open_select_file_gui(item->user_pointer, 1);
      // break;
    }
  }   
}

int ed1_onkey(GUI *data, GUI_MSG *msg)
{
  EDITCONTROL ec;
  char tmpstr[5];
	if (msg->keys==0xFFF)  // OK
	{
		//int i=EDIT_GetFocus(data);
		ExtractEditControl(data,2,&ec);
		wstrcpy(ews,ec.pWS);
		ws_2str(ews,SAVEp.fl,256);
		ExtractEditControl(data,4,&ec);
		wstrcpy(ews,ec.pWS);
		ws_2str(ews,SAVEp.nm,128);
		waitsave=1;
		if(SAVEp.type==2)
		{
			ExtractEditControl(data,8,&ec);
			wstrcpy(ews,ec.pWS);
			ws_2str(ews,tmpstr,5);
			SAVEp.n=strtoul(tmpstr,0,10);
		}
		
		switch(SAVEp.doit(0))
		{
			case RES_OK:
				menudata->lev++;
				newm(menudata, postsavem);
				menudata->sh_all=0;
				//tmpm=postsavem;
			  return 1;
			case DO_REWR:
				MsgBoxYesNo(1, (int)"Файл уже есть!\nЗаменить?", kbps);
			  return 1;
			case FAIL_OPEN:
				MsgBoxError(1,(int)"Файл не создаётся!!!");
				zeromem(&SAVEp, sizeof(SAVEp));
			  return 1;
			case OVER_COLCNT:
				MsgBoxError(1,(int)"Слишком много цветов!!!");
				zeromem(&SAVEp, sizeof(SAVEp));
			  return 1;
			default:
				MsgBoxError(1, (int)"Непонятная ошибка");
				zeromem(&SAVEp, sizeof(SAVEp));
			  return 1;
		}
		
		//return 1;
	}
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
	if ((msg->gbsmsg->submess==ENTER_BUTTON)&&(EDIT_GetFocus(data)==2))
	{
		EDIT_OpenOptionMenuWithUserItems(data,on_utf8ec,data,1);//open_select_file_gui(&data, 1, SAVEp.nm);
		return (-1);
	}
   // if (msg->gbsmsg->submess==GREEN_BUTTON)
    //{
		//ExtractEditControl(data,i,&ec);
		//WSHDR *wwws=AllocWS(ec.pWS->wsbody[0]);
		//wstrcpy(wwws,ec.pWS);
		//ws_2utf8( wwws, fnm , &utf8conv_res_len, 32);
		//ws_2str(wwws, fnm, 32);
		//FreeWS(wwws);
/*      EDIT_RemoveEditControl(data,1,&ec);
      PrepareEditControl(&ec);
      wsprintf(ews,percent_t,"Добавленное поле");
      ConstructEditControl(&ec,3,0x40,ews,256);
      EDIT_InsertEditControl(data,10,&ec);
      EDIT_SetFocus(data,10);
      EDIT_SetCursorPos(data,3);*/
/*      ExtractEditControl(data,EDIT_GetFocus(data),&ec);
      wstrcpy(ews,ec.pWS);
      wsAppendChar(ews,0xE12B);
      EDIT_SetTextToFocused(data,ews);      */
      //ExtractEditControl(data,3,&ec);
      //WSHDR *sw=AllocWS(ec.pWS->wsbody[0]);
      //wstrcpy(sw,ec.pWS);
//      SendSMS(ews,"+380636038122",0x4209,MSG_SMS_RX-1,2); //С редактированием
//      SendSMS(ews,"+380636038122",0x4209,MSG_SMS_RX-1,6); //Сразу в бой с окошком
//      SendSMS(sw,"+380636038122",0x4209,MSG_SMS_RX-1,6);
		//saveBMP();
      //return(-1);
    //}
  }
  //-1 - do redraw
  return(0); //Do standart keys
  //1: close
}

//void *edit_data;

void ed1_ghook(GUI *data, int cmd)
{
	static SOFTKEY_DESC ok={0x0FFF,0x0000,(int)"OK"};
	//static SOFTKEY_DESC back={0x0FFE,0x0000,(int)"Back"};
	//static SOFTKEY_DESC close={0x0FFE,0x0000,(int)"Close"};
//  static SOFTKEY_DESC sk={0x0018,0x0000,(int)"Menu"};
  EDITCONTROL ec;
  int i, j;//, utf8conv_res_len;
  if (cmd==2)
  {
    //Create
    //edit_data=data;
	//int need_to_jump=(int)EDIT_GetUserPointer(data);
    //EDIT_SetFocus(data,need_to_jump);
    //GBS_StartTimerProc(&mytmr,216/4,TestTimerProc);
  }
  if (cmd==3)
  {
	//edit_data=NULL;
	i=EDIT_GetFocus(data);
	//IsFieldCorrect(data,i);
    //GBS_DelTimer(&mytmr);
  }
  if (cmd==7)
  {
    //OnRun
	//SetSoftKey(data,&sk,1);
	//ExtractEditControl(data,3,&ec);
	//wstrcpy(ews,ec.pWS);
	i=EDIT_GetFocus(data);
	ExtractEditControl(data,i,&ec);
	wstrcpy(ews,ec.pWS);
	
	//ws_2str(ews,savename,32);
	
	SetSoftKey(data,&ok,SET_SOFT_KEY_N);
        //SetSoftKey(data,&close,!SET_SOFT_KEY_N);
  }
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
  if (cmd==0x0C)
  {
    i=EDIT_GetUnFocus(data);
    //IsFieldCorrect(data,i);
  }
  if (cmd==0x0D)
  {
    // onCombo
	j=EDIT_GetFocus(data);
	ExtractEditControl(data,j,&ec);
	if ((i=EDIT_GetItemNumInFocusedComboBox(data)))
	{
		switch(SAVEp.type)
		{
		 case 0:
			wsprintf(ews,perc_t,PTI_format[i-1]);
			SAVEp.btype=i-1;
		  break;
		 case 1:
			wsprintf(ews,perc_t,BMP_format[i-1]);
			SAVEp.btype=i-1;
		  break;
		 case 2:
			if(j==5){ wsprintf(ews,perc_t,GPF_format[i-1]);
				SAVEp.param=i-1;}
			if(j==6){ wsprintf(ews,perc_t,bitnm[i-1]);
				SAVEp.btype=i-1;}
		  break;
		}
	}
	else
	{
		ExtractEditControl(data,EDIT_GetFocus(data),&ec);
		wstrcpy(ews,ec.pWS);
	}
	EDIT_SetTextToFocused(data,ews);
  }
}

HEADER_DESC ed1_hdr={0,0,131,21,NULL,(int)"Сохранение",LGP_NULL};

INPUTDIA_DESC ed1_desc=
{
  1,
  ed1_onkey,
  ed1_ghook,
  (void *)ed1_locret,
  0,
  &menu_skt,
  {0,22,131,153},
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

int create_ed(void)
{
	patch_header(&ed1_hdr);
	patch_input(&ed1_desc);

  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;

  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());

 /*  wsprintf(ews,"%08X ",ed1_desc._0x40000000);
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma); */
  
	wsprintf(ews,perc_t,"Папка:");
	ConstructEditControl(&ec,1,0x40,ews,32);
	AddEditControlToEditQend(eq,&ec,ma);

	wsprintf(ews,perc_t,SAVEp.fl);
	ConstructEditControl(&ec,3,0x40,ews,256);
	AddEditControlToEditQend(eq,&ec,ma);
  
	wsprintf(ews,perc_t,"Имя:");
	ConstructEditControl(&ec,1,0x40,ews,32);
	AddEditControlToEditQend(eq,&ec,ma);

	str_2ws(ews, SAVEp.nm, strlen(SAVEp.nm));
	ConstructEditControl(&ec,3,0x40,ews,128);
	AddEditControlToEditQend(eq,&ec,ma);

	switch(SAVEp.type)
	{
	 case 0:
		wsprintf(ews,perc_t,"Слои:");
		ConstructEditControl(&ec,1,0x40,ews,256);
		AddEditControlToEditQend(eq,&ec,ma);

		//wsprintf(ews,"item1");
		ConstructComboBox(&ec,7,0x40,ews,9,0,2,1);
		AddEditControlToEditQend(eq,&ec,ma);
	  break;
	 case 1:
		//wsprintf(ews,"item1");
		ConstructComboBox(&ec,7,0x40,ews,15,0,4,1);
		AddEditControlToEditQend(eq,&ec,ma);
	  break;
	 case 2:
		//wsprintf(ews,"item1");
		ConstructComboBox(&ec,7,0x40,ews,15,0,2,1);
		AddEditControlToEditQend(eq,&ec,ma);
		
		ConstructComboBox(&ec,7,0x40,ews,15,0,3,1);
		AddEditControlToEditQend(eq,&ec,ma);

		wsprintf(ews,perc_t,"Номер:");
		ConstructEditControl(&ec,1,0x40,ews,256);
		AddEditControlToEditQend(eq,&ec,ma);

		wsprintf(ews,"0");
		ConstructEditControl(&ec,6,0x40,ews,5);
		AddEditControlToEditQend(eq,&ec,ma);
	  break;
	}

/*   wsprintf(ews,percent_t,"Строка с номером телефона:");
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,"123456789*#");
  ConstructEditControl(&ec,2,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,percent_t,"Число (фикс. кол. цифр):");
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,"3");
  ConstructEditControl(&ec,5,0x40,ews,5);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,percent_t,"Число (произв. кол. цифр):");
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,"123");
  ConstructEditControl(&ec,6,0x40,ews,5);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,percent_t,"ComboBox:");
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,"item1");
  ConstructComboBox(&ec,7,0x40,ews,10,0,3,1);
  AddEditControlToEditQend(eq,&ec,ma); */

  return CreateInputTextDialog(&ed1_desc,&ed1_hdr,eq,1,0);
}





///////////////////////////////////////////////////////////////
// *********************** Ввод имени ************************//
///////////////////////////////////////////////////////////////


int slnm_onkey(GUI *data, GUI_MSG *msg)
{
  EDITCONTROL ec;
  //char tmpn[19];
  //int rl;
	if (msg->keys==0xFFF)  // OK
	{
		//int i=EDIT_GetFocus(data);
		ExtractEditControl(data,2,&ec);
		wstrcpy(ews,ec.pWS);
		ws_2str(ews,tempnm,19);
		//zeromem(p->sl[tempsln].nm, 19);
		//snprintf(p->sl[tempsln].nm, 19, perc_s, tmpn);
		
		return 1;
	}
  //-1 - do redraw
  return(0); //Do standart keys
  //1: close
}

void slnm_ghook(GUI *data, int cmd)
{
	static SOFTKEY_DESC ok={0x0FFF,0x0000,(int)"OK"};
	//static SOFTKEY_DESC back={0x0FFE,0x0000,(int)"Back"};
	//static SOFTKEY_DESC close={0x0FFE,0x0000,(int)"Close"};
//  static SOFTKEY_DESC sk={0x0018,0x0000,(int)"Menu"};
  EDITCONTROL ec;
  int i;//, utf8conv_res_len;
  if (cmd==2)
  {
    //Create
    //edit_data=data;
	//int need_to_jump=(int)EDIT_GetUserPointer(data);
    //EDIT_SetFocus(data,need_to_jump);
    //GBS_StartTimerProc(&mytmr,216/4,TestTimerProc);
  }
  if (cmd==3)
  {
	//edit_data=NULL;
	i=EDIT_GetFocus(data);
	//IsFieldCorrect(data,i);
    //GBS_DelTimer(&mytmr);
  }
  if (cmd==7)
  {
    //OnRun
	//SetSoftKey(data,&sk,1);
	//ExtractEditControl(data,3,&ec);
	//wstrcpy(ews,ec.pWS);
	i=EDIT_GetFocus(data);
	ExtractEditControl(data,i,&ec);
	wstrcpy(ews,ec.pWS);
	
	//ws_2str(ews,savename,32);
	
	SetSoftKey(data,&ok,SET_SOFT_KEY_N);
        //SetSoftKey(data,&close,!SET_SOFT_KEY_N);
  }
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
  if (cmd==0x0C)
  {
    i=EDIT_GetUnFocus(data);
    //IsFieldCorrect(data,i);
  }
  if (cmd==0x0D)
  {
    // onCombo
	i=EDIT_GetFocus(data);
	ExtractEditControl(data,i,&ec);
	if ((i=EDIT_GetItemNumInFocusedComboBox(data)))
	{
	}
	else
	{
		ExtractEditControl(data,EDIT_GetFocus(data),&ec);
		wstrcpy(ews,ec.pWS);
	}
	EDIT_SetTextToFocused(data,ews);
  }
}

HEADER_DESC slnm_hdr={0,0,131,21,NULL,(int)"Ввод имени",LGP_NULL};

INPUTDIA_DESC slnm_desc=
{
  1,
  slnm_onkey,
  slnm_ghook,
  (void *)ed1_locret,
  0,
  &menu_skt,
  {0,22,131,153},
  FONT_SMALL,
  100,
  101,
  0,
  0,
  0x40000000 // Поменять местами софт-кнопки
};

int _setname(void)
{
	patch_header(&slnm_hdr);
	patch_input(&slnm_desc);

  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;

  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  
	wsprintf(ews,perc_t,"Введите имя:",tempnm);
	ConstructEditControl(&ec,1,0x40,ews,32);
	AddEditControlToEditQend(eq,&ec,ma);

	wsprintf(ews,perc_t,tempnm);
	ConstructEditControl(&ec,3,0x40,ews,19);
	AddEditControlToEditQend(eq,&ec,ma);

  return CreateInputTextDialog(&slnm_desc,&slnm_hdr,eq,1,0);
}

