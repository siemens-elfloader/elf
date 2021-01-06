
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
	newpicm_dr(RECT cv, int lev), // новая
	savepm_dr(RECT cv, int lev), // сохранение 
	postsavem_dr(RECT cv, int lev); // сохранение 

// клавиатура
int	instm_key(GUI_MSG *msg, int lev), // инструменты
	
	slm_key(GUI_MSG *msg, int lev), // слои 
	sslm_key(GUI_MSG *msg, int lev), // выбор слоя 
	ssslm_key(GUI_MSG *msg, int lev), // меню слоя 
	newslm_key(GUI_MSG *msg, int lev), // новы слой 
	delslm_key(GUI_MSG *msg, int lev), // удаление слоя 
	
	cm_key(GUI_MSG *msg, int lev), // цвета 
	colorm_key(GUI_MSG *msg, int lev), // выбор цвета 
	
	pm_key(GUI_MSG *msg, int lev), // картинка 
	newpicm_key(GUI_MSG *msg, int lev), // новая
	savepm_key(GUI_MSG *msg, int lev), // сохранение 
	postsavem_key(GUI_MSG *msg, int lev), // сохранение 
	
	create_ed(void);

RECT mcv[5]={{2,YDISP+2,0,0},{12,YDISP+12,0,0},{22,YDISP+22,0,0},{32,YDISP+32,0,0},{42,YDISP+42,0,0}};

MENU_PARAM ml[8],
		instm={5,0,"выбор","назад",instm_key,instm_dr}, // инструменты
		
		slm={4,0,"выбор","назад",slm_key,slm_dr}, // слои 
		sslm={1,0,"актив.","назад",sslm_key,sslm_dr}, // выбор слоя 
		ssslm={3,0,"выбор","назад",ssslm_key,ssslm_dr}, // меню слоя 
		newslm={1,0,"выбор","назад",newslm_key,newslm_dr}, // новы слой 
		delslm={1,0,"ДА","НЕТ",delslm_key,delslm_dr}, // удаление слоя 
		
		cm={3,0,"выбор","назад",cm_key,cm_dr}, // цвета 
		colorm={5,0,"сохр.","отмена",colorm_key,colorm_dr}, // выбор цвета 
		
		pm={4,0,"выбор","назад",pm_key,pm_dr}, // картинка 
		newpicm={4,0,"создать","назад",newpicm_key,newpicm_dr}, // новая
		savepm={2,0,"выбор","назад",savepm_key,savepm_dr}, // сохранение 
		postsavem={1,0,"","Ok",postsavem_key,postsavem_dr}, // ожидание при сохранении 
		
		tmpm={0,0,"","",0,0}; // временная структура для создания нового подменю


////////////////////////////////////////////////////////////
// ************************** МЕНЮ **********************//
////////////////////////////////////////////////////////////

#define MENU_BACK 1
#define MENU_NOTH 2
#define MENU_CLOSE 3
#define MENU_EXIT 0xff


static const char *bitnm[]={"8бит","16бит","32бита"},
		*colnm[]={"ЦВЕТ 1","ЦВЕТ 2","ЦВЕТ ФОНА"},
		*visibility[]={"невидимый","видимый"},
		mm_list[]="  ГЛ.МЕНЮ\n1 слои\n2 инструменты\n3 цвета\n4 картинка\n5 об эльфе\n6 настройка\n7 выход",
		cm_list[]="  ЦВЕТА\nцвет 1\nцвет 2\nфон";
char *sl_list,
	sl0_list[6][16],
	*instm_list;


// отрисовка меню
void standart_dr(WSHDR *list, RECT cv, int lev)
{
	DrawRectangle(cv.x-1,cv.y-f_h-1,cv.x2-10,cv.y+1,0,white,black);
	DrawRectangle(cv.x-1,cv.y-1,cv.x2+1,cv.y2+1,0,white,black);
	DrawRectangle(cv.x,cv.y+ml[lev].pos*f_h,cv.x2,cv.y+(ml[lev].pos+1)*f_h,0,white,red);
	DrawString(list,cv.x+1,cv.y-f_h+1,cv.x2-1,SCR.sh,FONT_SMALL,1,white,NULL);
}


/////////////////////////////// ГЛ. МЕНЮ ////////////////


void mm_dr(RECT cv, int lev)
{
	DrawRectangle(0,YDP,SCR.sw,SCR.sh,0,white,black);
	DrPic();
	DrawRectangle(0,YDP, SCR.sw,SCR.sh, 0,blpr,blpr);
	wsprintf(ws,perc_t,mm_list);
	standart_dr(ws, cv, lev);
}

int mm_key(GUI_MSG *msg, int lev)
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
				switch(ml[lev].pos)
				{
					case 0:
						tmpm=slm;
					 break;
					case 1:
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
						instm.cnt=i;
						tmpm=instm;
					 break;
					case 2:
						tmpm=cm;
					 break;
					case 3:
						tmpm=pm;
					 break;
					case 4:
						inf=malloc(128);
						sprintf(inf, "Paintt\nv%s\nhttp://paintt.h2m.ru\nby titron",ver);
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

int instm_key(GUI_MSG *msg, int lev)
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
				p1.inst=ml[lev].pos;
				return MENU_CLOSE;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


/////////////////////////// Слои ///////////////////////


void slm_dr(RECT cv, int lev)
{
	wsprintf(ws,perc_t,"  СЛОИ\nвыбoр\nновый\nобъединить все\nобъед. видимые");
	standart_dr(ws, cv, lev);
}

int slm_key(GUI_MSG *msg, int lev)
{
	int i;
	if (msg->gbsmsg->msg==KEY_DOWN)
	{
		switch(msg->gbsmsg->submess)
		{
			case LEFT_BUTTON:
			case RIGHT_SOFT:
			case RED_BUTTON:
				do_vpic();
				return MENU_BACK;
			case LEFT_SOFT:
			case RIGHT_BUTTON:
			case ENTER_BUTTON:
			case '5':
				switch(ml[lev].pos)
				{
					case 0:
						sslm.cnt=p1.sl_cnt;
						sslm.pos=sslm.cnt-p1.ac_sl-1;
						sl_list=malloc(18*(sslm.cnt+1));
						sprintf( sl_list, perc_sn, "ВЫБОР СЛОЯ");
						for(i=p1.sl_cnt-1; i>=0; i--) sprintf( sl_list+strlen(sl_list), perc_sn, sl[i].nm);
						tmpm=sslm;
					 break;
					case 1:
						newslm.cnt=p1.sl_cnt+1;
						newslm.pos=newslm.cnt-p1.ac_sl-2;
						sprintf( sl0_list[0], "SLOY %d", p1.sl_cnt );
						for(i=p1.sl_cnt-1; i>=0; i--) strcpy( sl0_list[p1.sl_cnt-i], sl[i].nm);
						tmpm=newslm;
					 break;
					default: ShowMSG(1, (int)"В разработке :)"); break;
				}
			 break;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


/////////////////////////// Выбор слоя //////////////////


void sslm_dr(RECT cv, int lev)
{
	wsprintf(ws,perc_t, sl_list);
	standart_dr(ws, cv, lev);
}

int sslm_key(GUI_MSG *msg, int lev)
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
				p1.ac_sl=ml[lev].cnt-ml[lev].pos-1;
				return MENU_CLOSE;
			case RIGHT_BUTTON:
			case ENTER_BUTTON:
			case '5':
				tmpm=ssslm;
				//if(sl[ml[lev].cnt-ml[lev].pos-1].v) sl[ml[lev].cnt-ml[lev].pos-1].v=0;
				//else sl[ml[lev].cnt-ml[lev].pos-1].v=1;
			 break;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


/////////////////////////// Меню слоя //////////////////////


void ssslm_dr(RECT cv, int lev)
{
	wsprintf(ws, "  %t\n%t\n%t", sl[ml[lev-1].cnt-ml[lev-1].pos-1].nm, visibility[sl[ml[lev-1].cnt-ml[lev-1].pos-1].v], "активным\nудалить");
	standart_dr(ws, cv, lev);
}

int ssslm_key(GUI_MSG *msg, int lev)
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
				switch(ml[lev].pos)
				{
					case 0:
						if(sl[ml[lev-1].cnt-ml[lev-1].pos-1].v) sl[ml[lev-1].cnt-ml[lev-1].pos-1].v=0;
						else sl[ml[lev-1].cnt-ml[lev-1].pos-1].v=1;
					 break;
					case 1:
						p1.ac_sl=ml[lev-1].cnt-ml[lev-1].pos-1;
					 return MENU_CLOSE;
					case 2:
						tmpm=delslm;
						return 0;
					default: ShowMSG(1, (int)"В разработке :)");
				}
			 break;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


/////////////////////////// Новый слой //////////////////////


void newslm_dr(RECT cv, int lev)
{
	int i;
	char *_list=malloc(18*(ml[lev].cnt+1));
	sprintf( _list, perc_sn, "НОВЫЙ СЛОЙ");
	for(i=0; i<ml[lev].cnt; i++)
	{
		if(i==ml[lev].pos) sprintf( _list+strlen(_list), perc_sn, sl0_list[0]);
		else
			if(i>ml[lev].pos) sprintf( _list+strlen(_list), perc_sn, sl0_list[i]);
			else sprintf( _list+strlen(_list), perc_sn, sl0_list[i+1]);
	}
	wsprintf(ws,perc_t,_list);
	standart_dr(ws, cv, lev);
}

int newslm_key(GUI_MSG *msg, int lev)
{
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
				new_sl(ml[lev].cnt-ml[lev].pos-1, sl0_list[0]);
			 return 1;
			case DOWN_BUTTON:
			case '8':
				ml[lev].pos++;
				if(ml[lev].pos>=ml[lev].cnt-1) ml[lev].pos=0;
			 return MENU_NOTH;
			case UP_BUTTON:
			case '2':
				ml[lev].pos--;
				if(ml[lev].pos>=ml[lev].cnt-1) ml[lev].pos=ml[lev].cnt-2;
			 return MENU_NOTH;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


/////////////////////////// Удаление слоя //////////////////////////


void delslm_dr(RECT cv, int lev)
{
	DrawRectangle(0,0,SCR.sw,SCR.sh,0,red,black);
	wsprintf(ws, "%t\n%t", "Удалить слой?", sl[ml[lev-2].cnt-ml[lev-2].pos-1].nm);
	DrawString(ws,0,50,SCR.sw,SCR.sh,FONT_LARGE,2,white,NULL);
}

int delslm_key(GUI_MSG *msg, int lev)
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
				del_sl(ml[lev-2].cnt-ml[lev-2].pos-1);
				return MENU_CLOSE;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


//////////////////////////////////// Цвета ////////////////////////////


void cm_dr(RECT cv, int lev)
{
	wsprintf(ws,perc_t,cm_list);
	standart_dr(ws, cv, lev);
}

int cm_key(GUI_MSG *msg, int lev)
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
				memcpy(tmp_col.c, COL[ml[lev].pos].c, 4);
				tmp_col.c32=ml[lev].pos;
				tmpm=colorm;
			 break;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


//////////////////////////////////// Выбор цвета ////////////////////////////

void convcol()
{
	int c32;
	if(tmp_col.c[3]<25)
	{
		tmp_col.c16=prz.c16;
		tmp_col.c8=prz.c8;
	}
	else
	{
		c32=(tmp_col.c[3]<<24)+(tmp_col.c[2]<<16)+(tmp_col.c[1]<<8)+(tmp_col.c[0]);
		tmp_col.c16=rgb_24_16(c32);
		tmp_col.c8=rgb_24_8(c32);
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
	DrawString(ws,cv.x+1,cv.y-f_h+1,cv.x2-1,SCR.sh,FONT_SMALL,1,white,NULL);
	wsprintf(ws," R:%02X\n G:%02X\n B:%02X\n A:%02X\n8b:%02X\n16b:%04X",tmp_col.c[0],tmp_col.c[1],tmp_col.c[2],tmp_col.c[3],tmp_col.c8,tmp_col.c16);
	DrawString(ws,cv.x+6,cv.y+2*f_h+3,cv.x2-1,SCR.sh,FONT_SMALL,1,white,NULL);
}

int colorm_key(GUI_MSG *msg, int lev)
{
	int st=1;
	if(ml[lev].pos)
		switch(msg->gbsmsg->msg)
		{
		 case LONG_PRESS: st=0x10;
		 case KEY_DOWN:
			switch(msg->gbsmsg->submess)
			{
				case LEFT_BUTTON:
					tmp_col.c[ml[lev].pos-1]-=st;
				 break;
				case RIGHT_BUTTON:
					tmp_col.c[ml[lev].pos-1]+=st;
				 break;
				case ENTER_BUTTON:
				case LEFT_SOFT:
				case '5':
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
				case ENTER_BUTTON:
				case '5':
					memcpy(tmp_col.c, prz.c, 4);
				 return MENU_NOTH;
				case LEFT_SOFT:
					COL[tmp_col.c32]=tmp_col;
				case LEFT_BUTTON:
				 return MENU_BACK;
			}
		}
	return 0;
}


//////////////////////////////////// Меню картинки ////////////////////////////


void pm_dr(RECT cv, int lev)
{
	wsprintf(ws,perc_t,"  КАРТИНКА\nпредпросмотр\nновая\nоткрыть\nсохранить");
	standart_dr(ws, cv, lev);
}

int pm_key(GUI_MSG *msg, int lev)
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
				switch(ml[lev].pos)
				{
					case 0:
						Preview();
					 break;
					case 1:
						tmp_p=p1;;
						tmpm=newpicm;
					 break;
					 
					case 3:
						tmpm=savepm;
					 break;
					default: ShowMSG(1, (int)"В разработке :)"); break;
				}
			 break;
		}
		//DirectRedrawGUI();
	}
	return 0;
}


//////////////////////////////////// Новая картинка /////////////////


void newp(int decision)
{
	if(!decision)
	{
		p1=tmp_p;
		crpic();
	}
}

void newpicm_dr(RECT cv, int lev)
{
	if(start) DrawRectangle(0,YDP,SCR.sw,SCR.sh,0,black,black);
	wsprintf(ws,"%t%d\n%t%d\n%t\n%t","  КАРТИНКА\nвысота:",tmp_p.h,"ширина:",tmp_p.w, bitnm[tmp_p.mod], "фон");
	standart_dr(ws, cv, lev);
}

int newpicm_key(GUI_MSG *msg, int lev)
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
						p1=tmp_p;
						start=0;
						docols(0);
						crpic();
						return MENU_CLOSE;
					}
					else MsgBoxYesNo(1,(int)"Удалить\nредактируемую?",newp);
				 return 3;
				case RED_BUTTON:
				case RIGHT_SOFT:
					if(start) return MENU_EXIT;
					else return MENU_BACK;
				case RIGHT_BUTTON:
				case '6':
					switch(ml[lev].pos)
					{
						case 0:
							tmp_p.h+=stp;
							#ifndef ELKA
							if(tmp_p.h>0xff) tmp_p.h=0;
							#endif
						 break;
						case 1:
							tmp_p.w+=stp;
							#ifndef ELKA
							if(tmp_p.w>0xff) tmp_p.w=0;
							#endif
						 break;
						case 2:
							if(tmp_p.mod==2) tmp_p.mod=0;
							else tmp_p.mod++;
						 break;
					}
				case ENTER_BUTTON:
					switch(ml[lev].pos)
					{
						case 3:
							memcpy(tmp_col.c, COL[2].c, 4);
							tmp_col.c32=2;
							tmpm=colorm;
						 break;
					}
				 break;
				case LEFT_BUTTON:
				case '4':
					switch(ml[lev].pos)
					{
						case 0:
							tmp_p.h-=stp;
							#ifndef ELKA
							if(tmp_p.h>0xff) tmp_p.h=0xff;
							#endif
						 break;
						case 1:
							tmp_p.w-=stp;
							#ifndef ELKA
							if(tmp_p.w>0xff) tmp_p.w=0xff;
							#endif
						 break;
						case 2:
							if(tmp_p.mod==0) tmp_p.mod=2;
							else tmp_p.mod--;
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


void savepm_dr(RECT cv, int lev)
{
	wsprintf(ws,perc_t,"  Сохранение\n*.pti\n*.bmp");
	standart_dr(ws, cv, lev);
}

int savepm_key(GUI_MSG *msg, int lev)
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
				switch(ml[lev].pos)
				{
					case 0: SAVEp.doit=savePTI; break;
					case 1: SAVEp.doit=saveBMP; break;
				}
				SAVEp.bit=0;
				SAVEp.type=ml[lev].pos;
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
	DrawRectangle(10,SCR.sh-3*f_h,SCR.sw-10,SCR.sh-2*f_h,0,white,black);
	DrawRectangle(11,SCR.sh-3*f_h+1,11+(SCR.sw-22)*SAVEp.cur_part/SAVEp.parts,SCR.sh-2*f_h-1,0,blue,blue);
	DrawString(ws,0,50,SCR.sw,SCR.sh,FONT_LARGE,2,white,NULL);
}

int postsavem_key(GUI_MSG *msg, int lev)
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
				case LEFT_SOFT:
				case ENTER_BUTTON:
				case '5':
					zeromem(&SAVEp, sizeof(SAVEp));
					return MENU_BACK;
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
	if(tmpm.cnt)
	{
		data->lev++;
		ml[data->lev]=tmpm;
		mcv[data->lev].x2=mcv[data->lev].x+SCR.sw-30;
		mcv[data->lev].y2=mcv[data->lev].y+(ml[data->lev].cnt)*f_h;
		tmpm.cnt=0;
	}
	int i;
	for(i=0; i<=data->lev; i++)
	{
		if(i) DrawRectangle(mcv[i-1].x-1,mcv[i-1].y-f_h-1,mcv[i-1].x2+1,mcv[i-1].y2+1,0,blpr,blpr);
		ml[i].dr(mcv[i] ,i);
	}
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
	switch(ml[data->lev].key(msg, data->lev))
	{
		case MENU_CLOSE: return 1;
		case MENU_BACK:
			if(data->lev==0) return 1;
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
				if(data->lev==0) return 1;
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
  mcv[0].x2=mcv[0].x+SCR.sw-30;
  mcv[0].y2=mcv[0].y+(m.cnt)*f_h;
  return(CreateGUI(m_gui));
}





///////////////////////////////////////////////////////////////
// *********************** Ввод имени ************************//
///////////////////////////////////////////////////////////////




void menu_ghook(void *data, int cmd)
{
}

int menusoftkeys[]={0,1,2};

int S_ICONS[];

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

SOFTKEY_DESC save_sk[]=
{
  {0x0018,0x0000,(int)"сохр."},
  {0x0001,0x0000,(int)"назад"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB save_skt=
{
  save_sk,0
};




/////////////////////////////////////////////////////////



void kbps(int i)
{
	if(!i) 
	{
		if(SAVEp.doit(1)==RES_OK)
		{
				tmpm=postsavem;
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

int ed1_onkey(GUI *data, GUI_MSG *msg)
{
  EDITCONTROL ec;
	if (msg->keys==0xFFF)  // OK
	{
		//int i=EDIT_GetFocus(data);
		ExtractEditControl(data,2,&ec);
		wstrcpy(ews,ec.pWS);
		ws_2str(ews,SAVEp.nm,32);
		waitsave=1;
		//if(SAVEp.type)
		//{
			//i=EDIT_GetItemNumInFocusedComboBox(data);
			//SAVEp.bit=i-1;
		//}
		//saveBMP();
		/* if(SAVEp.doit(0)!=RES_OK) {MsgBoxError(1,(int)"Файл не создаётся!!!"); return 0;}
	ShowMSG(1,(int)"Файл сохранён");
		if(rwr==DO_REWR) {MsgBoxYesNo(1, (int)"Файл уже есть!!! Заменить?", kbps); return 1;}
		zeromem(&SAVEp, sizeof(SAVEp));
		else {MsgBoxError(1, (int)"Непонятная ошибка"); return 1;} */
		
		switch(SAVEp.doit(0))
		{
			case RES_OK:
				//ShowMSG(1,(int)"Файл сохранён");
				//zeromem(&SAVEp, sizeof(SAVEp));
				tmpm=postsavem;
			  return 1;
			case DO_REWR:
				MsgBoxYesNo(1, (int)"Файл уже есть!\nЗаменить?", kbps);
			  return 1;
			case FAIL_OPEN:
				MsgBoxError(1,(int)"Файл не создаётся!!!");
				zeromem(&SAVEp, sizeof(SAVEp));
			  return 1;
			default:
				MsgBoxError(1, (int)"Непонятная ошибка");
				zeromem(&SAVEp, sizeof(SAVEp));
			  return 1;
		}
		
		//return 1;
	}
  //int utf8conv_res_len;
  //int i=EDIT_GetFocus(data);
  //char *fnm;
  // if ((msg->keys==0x18)||(msg->keys==0x3D))
  // {
	// saveBMP();
  // }
  //if (msg->gbsmsg->msg==KEY_DOWN)
  //{
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
  //}
  //-1 - do redraw
  return(0); //Do standart keys
  //1: close
}

void *edit_data;

void ed1_ghook(GUI *data, int cmd)
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
		switch(SAVEp.type)
		{
		 case 0:
			wsprintf(ews,perc_t,PTI_format[i-1]);
		  break;
		 case 1:
			wsprintf(ews,perc_t,BMP_format[i-1]);
		  break;
		}
		SAVEp.bit=i-1;
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
  
	wsprintf(ews,perc_t,"Имя файла:");
	ConstructEditControl(&ec,1,0x40,ews,32);
	AddEditControlToEditQend(eq,&ec,ma);

	wsprintf(ews,perc_t,SAVEp.nm);
	ConstructEditControl(&ec,3,0x40,ews,32);
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


