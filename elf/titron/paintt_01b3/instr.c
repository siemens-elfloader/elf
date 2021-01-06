#include <math.h>

GBSTMR instmr;
extern void do_vpic(), dozoom();
extern int menu(MENU_PARAM m);
int keymod1(GUI_MSG *msg);
int key_point(GUI_MSG *msg);
int key_kist(GUI_MSG *msg);
void do_point(),
	do_kist(),
	
	do_line(),
	dr_line(),
	
	do_rect(),
	dr_rect(),
	
	dr_ellipse(),
	do_ellipse(),
	
	dr_ellipse(),
	do_elli();

typedef struct{
	char n,
		nm[16],
		mod,
		p;
	int (*key)(GUI_MSG *msg);
	void (*dr)(),
		(*doit)();
}INST_PARAM;

void dr_0(){};

INST_PARAM inst[]=
{
	{1,"карандаш",			0,	0,	key_point,	dr_0,			do_point	},
	{2,"кисть",				0,	0,	key_kist,	dr_0,			do_kist		},
	{3,"линия",				0,	0,	keymod1,	dr_line,		do_line	},
	{4,"прямоугольник",		0,	0,	keymod1,	dr_rect,		do_rect		},
	//{5,"эллипс",			0,	0,	keymod1,	dr_ellipse,		do_ellipse	},
	{5,"эллипс",			0,	0,	keymod1,	dr_ellipse,		do_elli	},
	{0,"",0,0,0,0,0}
};

void stp(char *outmap, RECT ps, char clr_n, char *inmap)
{
	if(inmap)
	{
		memcpy(outmap+ps.y2*p1.w*4+ps.x2*4,   inmap+ps.y*p1.w*4+ps.x*4,   4);
	}
	else
	{
		memcpy(outmap+ps.y2*p1.w*4+ps.x2*4,   &COL[clr_n].c32, 4);
	}
}

void do_point()
{
	RECT ps;
	ps.x2=cur.x;
	ps.y2=cur.y;
	stp(sl[p1.ac_sl].p.bitmap, ps, 0, NULL);
	do_vpic();
}

void do_kist()
{
	if(inst[p1.inst].p) inst[p1.inst].p=0;
	else inst[p1.inst].p=1;
}

void do_line()
{
	inst[p1.inst].p=0;
	int i,j;
	char a=0,s=0;
	//unsigned short q;
	RECT ps;
		patch_rect(&dr, cur.x, cur.y, cur.x2, cur.y2);
	if(cur.x<cur.x2)
	{
		patch_rect(&dr, cur.x2, dr.y, cur.x, dr.y2);
		//q=cur.x;
		//cur.x=cur.x2;
		//cur.x2=q;
		a=1;
	}
	if(cur.y<cur.y2)
	{
		patch_rect(&dr, dr.x, cur.y2, dr.x2, cur.y);
		//q=cur_y;
		//cur_y=cur_y1;
		//cur_y1=q;
		s=1;
	}
	dr.x++;
	dr.y++;
	if(dr.x-dr.x2<dr.y-dr.y2)
	{
			dr.y2--;
		if((a-s)==0)
		{
			for(i=1;i<dr.y-dr.y2;i++)
			{
				j=((dr.x-dr.x2)*i)/(dr.y-dr.y2);
				ps.x2=dr.x2+j;
				ps.y2=dr.y2+i;
				stp(sl[p1.ac_sl].p.bitmap, ps, 0, NULL);
				// memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4, &COL[0][2], 1);
				// memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+1, &COL[0][1], 1);
				// memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+2, &COL[0][0], 1);
				// memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+3, &COL[0][3], 1);
			}
		}
		else
		{
			for(i=1;i<dr.y-dr.y2;i++)
			{
				j=((dr.x-dr.x2)*(dr.y-dr.y2-i))/(dr.y-dr.y2);
				ps.x2=dr.x2+j;
				ps.y2=dr.y2+i;
				stp(sl[p1.ac_sl].p.bitmap, ps, 0, NULL);
				//stp(cur_y1+i, cur_x1+j, 0, 0, 0, 0, 0);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4, &COL[0][2], 1);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+1, &COL[0][1], 1);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+2, &COL[0][0], 1);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+3, &COL[0][3], 1);
			}
		}
			//cur.y2++;
	}
	else
	{
		dr.x2--;
		if((a-s)==0)
		{
			for(j=1;j<dr.x-dr.x2;j++)
			{
				i=((dr.y-dr.y2)*j)/(dr.x-dr.x2);
				ps.x2=dr.x2+j;
				ps.y2=dr.y2+i;
				stp(sl[p1.ac_sl].p.bitmap, ps, 0, NULL);
				//stp(cur_y1+i, cur_x1+j, 0, 0, 0, 0, 0);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4, &COL[0][2], 1);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+1, &COL[0][1], 1);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+2, &COL[0][0], 1);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+3, &COL[0][3], 1);
			}
		}
		else
		{
			for(j=1;j<dr.x-dr.x2;j++)
			{
				i=((dr.y-dr.y2)*(dr.x-dr.x2-j))/(dr.x-dr.x2);
				ps.x2=dr.x2+j;
				ps.y2=dr.y2+i;
				stp(sl[p1.ac_sl].p.bitmap, ps, 0, NULL);
				//stp(cur_y1+i, cur_x1+j, 0, 0, 0, 0, 0);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4, &COL[0][2], 1);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+1, &COL[0][1], 1);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+2, &COL[0][0], 1);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+3, &COL[0][3], 1);
			}
		}
		//cur.x2++;
	}
	//cur.x--;
	//cur.y--;
	do_vpic();
}



void do_rect()
{
		inst[p1.inst].p=0;
		int i,j;
		//char a=0,s=0;
		//unsigned short q;
		RECT ps;
		patch_rect(&dr, cur.x, cur.y, cur.x2, cur.y2);
	if(cur.x<cur.x2)
	{
		patch_rect(&dr, cur.x2, dr.y, cur.x, dr.y2);
		//q=cur.x;
		//cur.x=cur.x2;
		//cur.x2=q;
		//a=1;
	}
	if(cur.y<cur.y2)
	{
		patch_rect(&dr, dr.x, cur.y2, dr.x2, cur.y);
		//q=cur_y;
		//cur_y=cur_y1;
		//cur_y1=q;
		//s=1;
	}
	for(i=0;i<dr.y-dr.y2+1;i++)
	{
		for(j=0;j<dr.x-dr.x2+1;j++)
		{
			if((i==0)||(i==dr.y-dr.y2))
			{
				ps.x2=dr.x2+j;
				ps.y2=dr.y2+i;
				stp(sl[p1.ac_sl].p.bitmap, ps, 0, NULL);
				//stp(cur_y1+i, cur_x1+j, 0, 0, 0, 0, 0);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4, &COL[0][2], 1);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+1, &COL[0][1], 1);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+2, &COL[0][0], 1);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+3, &COL[0][3], 1);
			}
			else
			{
				if((j==0)||(j==dr.x-dr.x2))
				{
					ps.x2=dr.x2+j;
					ps.y2=dr.y2+i;
					stp(sl[p1.ac_sl].p.bitmap, ps, 0, NULL);
					//stp(cur_y1+i, cur_x1+j, 0, 0, 0, 0, 0);
					//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4, &COL[0][2], 1);
					//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+1, &COL[0][1], 1);
					//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+2, &COL[0][0], 1);
					//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+3, &COL[0][3], 1);
				}
				else
				{
					ps.x2=dr.x2+j;
					ps.y2=dr.y2+i;
					stp(sl[p1.ac_sl].p.bitmap, ps, 1, NULL);
					//stp(cur_y1+i, cur_x1+j, 0, 1, 0, 0, 0);
					//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4, &COL[1][2], 1);
					//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+1, &COL[1][1], 1);
					//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+2, &COL[1][0], 1);
					//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+3, &COL[1][3], 1);
				}
			}
		}
	}
	do_vpic();
}

void do_ellipse()
{
		inst[p1.inst].p=0;
		int i,j;
		//char a=0,s=0;
		unsigned short w;
		RECT ps;
		patch_rect(&dr, cur.x, cur.y, cur.x2, cur.y2);
	if(cur.x<cur.x2)
	{
		patch_rect(&dr, cur.x2, dr.y, cur.x, dr.y2);
		//q=cur.x;
		//cur.x=cur.x2;
		//cur.x2=q;
		//a=1;
	}
	if(cur.y<cur.y2)
	{
		patch_rect(&dr, dr.x, cur.y2, dr.x2, cur.y);
		//q=cur_y;
		//cur_y=cur_y1;
		//cur_y1=q;
		//s=1;
	}
		for(i=0;i<dr.y-dr.y2+1;i++)
		{
			for(j=0;j<dr.x-dr.x2+1;j++)
			{
				//w=sqrt((i-(cur.x-cur.x2)/2)*(i-(cur.x-cur.x2)/2)+(j-(cur.x-cur.x2)/2)*(j-(cur.x-cur.x2)/2));
				w=((j-(dr.x-dr.x2)/2)*(j-(dr.x-dr.x2)/2)*100)/(((dr.x-dr.x2)/2)*((dr.x-dr.x2)/2))+((i-(dr.y-dr.y2)/2)*(i-(dr.y-dr.y2)/2)*100)/(((dr.y-dr.y2)/2)*((dr.y-dr.y2)/2));
				if(w<=100)
				{
					ps.x2=dr.x2+j;
					ps.y2=dr.y2+i;
					stp(sl[p1.ac_sl].p.bitmap, ps, 0, NULL);
				}
			}
		}
		for(i=0;i<dr.y-dr.y2+1;i++)
		{
			for(j=0;j<dr.x-dr.x2+1;j++)
			{
				w=((j-(dr.x-dr.x2-2)/2)*(j-(dr.x-dr.x2-2)/2)*100)/(((dr.x-dr.x2-2)/2)*((dr.x-dr.x2-2)/2))+((i-(dr.y-dr.y2-2)/2)*(i-(dr.y-dr.y2-2)/2)*100)/(((dr.y-dr.y2-2)/2)*((dr.y-dr.y2-2)/2));
				if(w<100)
				{
					ps.x2=dr.x2+j+1;
					ps.y2=dr.y2+i+1;
					stp(sl[p1.ac_sl].p.bitmap, ps, 1, NULL);
				}
			}
		}
	do_vpic();
}

void do_do_elli()
{
		inst[p1.inst].p=0;
		int i,j;
		//char a=0,s=0;
		unsigned short ww, *w;//=malloc(SCR.sw*SCR.sh*2);
		RECT ps;
		//patch_rect(&dr, cur.x, cur.y, cur.x2, cur.y2);
	//if(cur.x<cur.x2)
	//{
		//patch_rect(&dr, cur.x2, dr.y, cur.x, dr.y2);
		//q=cur.x;
		//cur.x=cur.x2;
		//cur.x2=q;
		//a=1;
	//}
	//if(cur.y<cur.y2)
	//{
		//patch_rect(&dr, dr.x, cur.y2, dr.x2, cur.y);
		//q=cur_y;
		//cur_y=cur_y1;
		//cur_y1=q;
		//s=1;
	//}
				w=(unsigned short *)RamScreenBuffer();
		for(i=0;i<dr.y-dr.y2+1;i++)
		{
			for(j=0;j<dr.x-dr.x2+1;j++)
			{
				ww=w[i*(SCR.sw+1)+j];
				if(ww==0xffff)
				{
					ps.x2=dr.x2+j;
					ps.y2=dr.y2+i;
					stp(sl[p1.ac_sl].p.bitmap, ps, 0, NULL);
				}
				else if(ww!=0x0000)
				{
					ps.x2=dr.x2+j;
					ps.y2=dr.y2+i;
					stp(sl[p1.ac_sl].p.bitmap, ps, 1, NULL);
				}
			}
		}
		//mfree(w);
		/* for(i=0;i<dr.y-dr.y2+1;i++)
		{
			for(j=0;j<dr.x-dr.x2+1;j++)
			{
				w=((j-(dr.x-dr.x2-2)/2)*(j-(dr.x-dr.x2-2)/2)*100)/(((dr.x-dr.x2-2)/2)*((dr.x-dr.x2-2)/2))+((i-(dr.y-dr.y2-2)/2)*(i-(dr.y-dr.y2-2)/2)*100)/(((dr.y-dr.y2-2)/2)*((dr.y-dr.y2-2)/2));
				if(w<100)
				{
					ps.x2=dr.x2+j+1;
					ps.y2=dr.y2+i+1;
					stp(sl[p1.ac_sl].p.bitmap, ps, 1, NULL);
				}
			}
		} */
	do_vpic();
		gst=2;
	DirectRedrawGUI();
}

void do_elli()
{
		gst=0;
		inst[p1.inst].p=2;
		GBS_StartTimerProc(&instmr, 1, do_do_elli);
}




extern void cangecol();



// **************************** прорисовка ************************


void dr_line()
{
	if(inst[p1.inst].p!=2)
	{
		patch_rect(&dr, cur.x, cur.y, cur.x2, cur.y2);
	}
	DrawLine(p1.x+(p1.zoom+1)*cur.x,YDP+p1.y+(p1.zoom+1)*cur.y,p1.x+(p1.zoom+1)*cur.x2,YDP+p1.y+(p1.zoom+1)*cur.y2,0,COL[0].c);
	if(inst[p1.inst].p==2)
	{
		if(dr.x<cur.x2) patch_rect(&dr, cur.x2, dr.y, cur.x, dr.y2);
		if(dr.y<cur.y2) patch_rect(&dr, dr.x, cur.y2, dr.x2, cur.y);
		DrawRectangle(0,0,dr.x-dr.x2,dr.y-dr.y2,0,black,black);
		DrawLine(0,0,dr.x-dr.x2,dr.y-dr.y2,0,white);
	}
}

void dr_rect()
{DrawRectangle(p1.x+(p1.zoom+1)*cur.x,YDP+p1.y+(p1.zoom+1)*cur.y,p1.x+(p1.zoom+1)*cur.x2,YDP+p1.y+(p1.zoom+1)*cur.y2,1,COL[0].c,COL[1].c);}

void dr_ellipse()
{
	if(inst[p1.inst].p!=2)
	{
		patch_rect(&dr, cur.x, cur.y, cur.x2, cur.y2);
		if(cur.x<cur.x2) patch_rect(&dr, cur.x2, dr.y, cur.x, dr.y2);
		if(cur.y<cur.y2) patch_rect(&dr, dr.x, cur.y2, dr.x2, cur.y);
	}
	drawArc(p1.x+(p1.zoom+1)*dr.x2,YDP+p1.y+(p1.zoom+1)*dr.y2,p1.x+(p1.zoom+1)*dr.x,YDP+p1.y+(p1.zoom+1)*dr.y,0,360,0,COL[0].c,COL[1].c);
	if(inst[p1.inst].p==2)
	{
		DrawRectangle(0,0,dr.x-dr.x2,dr.y-dr.y2,0,black,black);
		drawArc(0,0,dr.x-dr.x2,dr.y-dr.y2,0,360,0,white,blue);
	}
}





// **************************  клавиши **************************


#ifdef ELKA
 #define OTSTUP 25
#else
 #define OTSTUP 11
#endif


int move_cur(GUI_MSG *msg, unsigned short st_m, unsigned short st_b)
{
	unsigned short st=st_m;
	switch(msg->gbsmsg->msg)
	{
	 case LONG_PRESS: st=st_b;
	 case KEY_DOWN:
		switch(msg->gbsmsg->submess)
		{
	     case RED_BUTTON:
			if(inst[p1.inst].p) inst[p1.inst].p=0;
			else MsgBoxYesNo(1,(int)"Выход?",ExitProc);
		  break;
		 case UP_BUTTON:
		 case '2':
			cur.y-=st;
			if(cur.y>=p1.h)
			{
				if(BigPy)p1.y=PCPS.y2-p1.h*(p1.zoom+1)-OTSTUP;
				cur.y=p1.h-1;
			}
		  break;
		 case DOWN_BUTTON:
		 case '8':
			cur.y+=st;
			if(cur.y>=p1.h)
			{
				if(BigPy)p1.y=PCPS.y+OTSTUP;
				cur.y=0;
			}
	      break;
		 case LEFT_BUTTON:
		 case '4':
			cur.x-=st;
			if(cur.x>=p1.w)
			{
				if(BigPx)p1.x=PCPS.x2-p1.w*(p1.zoom+1)-OTSTUP;
				cur.x=p1.w-1;
			}
		  break;
		 case RIGHT_BUTTON:
		 case '6':
			cur.x+=st;
			if(cur.x>=p1.w)
			{
				if(BigPx)p1.x=PCPS.x+OTSTUP;
				cur.x=0;
			}
		  break;
		 case '1':
			cur.y-=st;
			if(cur.y>=p1.h)
			{
				if(BigPy)p1.y=PCPS.y2-p1.h*(p1.zoom+1)-OTSTUP;
				cur.y=p1.h-1;
			}
			cur.x-=st;
			if(cur.x>=p1.w)
			{
				if(BigPx)p1.x=PCPS.x2-p1.w*(p1.zoom+1)-OTSTUP;
				cur.x=p1.w-1;
			}
		  break;
		 case '3':
			cur.y-=st;
			if(cur.y>=p1.h)
			{
				if(BigPy)p1.y=PCPS.y2-p1.h*(p1.zoom+1)-OTSTUP;
				cur.y=p1.h-1;
			}
			cur.x+=st;
			if(cur.x>=p1.w)
			{
				if(BigPx)p1.x=PCPS.x+OTSTUP;
				cur.x=0;
			}
		  break;
		 case '7':
			cur.y+=st;
			if(cur.y>=p1.h)
			{
				if(BigPy)p1.y=PCPS.y+OTSTUP;
				cur.y=0;
			}
			cur.x-=st;
			if(cur.x>=p1.w)
			{
				if(BigPx)p1.x=PCPS.x2-p1.w*(p1.zoom+1)-OTSTUP;
				cur.x=p1.w-1;
			}
		  break;
		 case '9':
			cur.y+=st;
			if(cur.y>=p1.h)
			{
				if(BigPy)p1.y=PCPS.y+OTSTUP;
				cur.y=0;
			}
			cur.x+=st;
			if(cur.x>=p1.w)
			{
				if(BigPx)p1.x=PCPS.x+OTSTUP;
				cur.x=0;
			}
		  break;
	case '#':
		cangecol();
		//inst_mod=0;
		//create_instm();
	  break;
		}
	}
	if(p1.x+cur.x*(p1.zoom+1)>PCPS.x2-OTSTUP) p1.x-=st*(p1.zoom+1);
	if(p1.x+cur.x*(p1.zoom+1)<PCPS.x+OTSTUP) p1.x+=st*(p1.zoom+1);
	if(p1.y+cur.y*(p1.zoom+1)>PCPS.y2-OTSTUP) p1.y-=st*(p1.zoom+1);
	if(p1.y+cur.y*(p1.zoom+1)<PCPS.y+OTSTUP) p1.y+=st*(p1.zoom+1);
  return(0);
}

extern int savePTI();

void stkey(GUI_MSG *msg)
{
  int m=msg->gbsmsg->msg;
  if (m==KEY_DOWN)
  {
	switch(msg->gbsmsg->submess)
	{
    case LEFT_SOFT:
		//inst_mod=0;
		menu(mm);
      break;
    case GREEN_BUTTON:
			//savePTI();////
      break;
    case RIGHT_SOFT:
      break;
	case '0':
		dozoom();
	  break;
	case '*':
		//inst_mod=0;
		//create_colm();
	  break;
      //return(1); //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
    }
	//DirectRedrawGUI();
  }
}


int key_point(GUI_MSG *msg)
{
	if ((msg->gbsmsg->msg==KEY_DOWN)&&((msg->gbsmsg->submess==ENTER_BUTTON)||(msg->gbsmsg->submess=='5')))
		inst[p1.inst].doit();
	stkey(msg);
	int k=move_cur(msg, 1, 5);
	DirectRedrawGUI();
	return(k);
}

int key_kist(GUI_MSG *msg)
{
	int k;
	if ((msg->gbsmsg->msg==KEY_DOWN)&&((msg->gbsmsg->submess==ENTER_BUTTON)||(msg->gbsmsg->submess=='5')))
	{
		inst[p1.inst].doit();
	}
	if(inst[p1.inst].p>0)
	{
		k=move_cur(msg, 1, 1);
		do_point();
		DirectRedrawGUI();
		return(k);
	}
	else stkey(msg);
	k=move_cur(msg, 1, 5);
	DirectRedrawGUI();
	return(k);
}

int keymod1(GUI_MSG *msg)
{
	if(!inst[p1.inst].p)stkey(msg);
	int k=move_cur(msg, 1, 5);
	switch(msg->gbsmsg->msg)
	{
		case KEY_DOWN:
			if((msg->gbsmsg->submess==ENTER_BUTTON)||(msg->gbsmsg->submess=='5'))
			{
				if(inst[p1.inst].p==1)	inst[p1.inst].doit();
				else
				//{
					inst[p1.inst].p=1;
					cur.x2=cur.x;
					cur.y2=cur.y;
					/*dr.x=cur.x;
					dr.x2=cur.x;
					dr.y=cur.y;
					dr.y2=cur.y;
				} */
			}
	/* 	case LONG_PRESS:
			if(inst[p1.inst].p)
			{
				if(cur.x>cur.x2) {dr.x2=cur.x; dr.x=cur.x2;}
				else {dr.x=cur.x; dr.x2=cur.x2;}
				if(cur.y>cur.y2) {dr.y2=cur.y; dr.y=cur.y2;}
				else {dr.y=cur.y; dr.y2=cur.y2;}
			} */
		 break;
	}
	DirectRedrawGUI();
	return(k);
}

