#include <math.h>

GBSTMR instmr;
extern void do_vpic(), dozoom(signed char z);
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

void stp(char *tobuf, RECT ps, char clr_n, char *frombuf) // запись пикселя в картинку
{
	unsigned int i=ps.y2, j=ps.x2, k, zi, zj, xy;
	int pos=i*p->w+j;
	char qq, tmpbuf[4];
	if(frombuf) // из другого битмапа
	{
		//tubuf[i*4]  = tubuf[ i*4 ]+((frombuf[ i*4 ]-tubuf[ i*4 ])*frombuf[i*4+3])/0xff;
		//tubuf[i*4+1]= tubuf[i*4+1]+((frombuf[i*4+1]-tubuf[i*4+1])*frombuf[i*4+3])/0xff;
		//tubuf[i*4+2]= tubuf[i*4+2]+((frombuf[i*4+2]-tubuf[i*4+2])*frombuf[i*4+3])/0xff;
		//tubuf[i*4+3]= tubuf[i*4+3]+((0xff-tubuf[i*4+3])*frombuf[i*4+3])/0xff;
		
				qq=frombuf[ pos*4 ]-((frombuf[ pos*4 ]-tobuf[ pos*4 ])*tobuf[pos*4+3])/0xff;
				tobuf[ pos*4 ]=qq+((frombuf[ pos*4 ]-qq)*frombuf[pos*4+3])/0xff;
					
				qq=frombuf[pos*4+1]-((frombuf[pos*4+1]-tobuf[pos*4+1])*tobuf[pos*4+3])/0xff;
				tobuf[pos*4+1]=qq+((frombuf[pos*4+1]-qq)*frombuf[pos*4+3])/0xff;
					
				qq=frombuf[pos*4+2]-((frombuf[pos*4+2]-tobuf[pos*4+2])*tobuf[pos*4+3])/0xff;
				tobuf[pos*4+2]=qq+((frombuf[pos*4+2]-qq)*frombuf[pos*4+3])/0xff;
				
		tobuf[pos*4+3]= tobuf[pos*4+3]+((0xff-tobuf[pos*4+3])*frombuf[pos*4+3])/0xff;
	}
	else // цвет
	{
		//tubuf[i*4]  = tubuf[ i*4 ]+((COL[clr_n].c[2]-tubuf[ i*4 ])*COL[clr_n].c[3])/0xff;
		//tubuf[i*4+1]= tubuf[i*4+1]+((COL[clr_n].c[1]-tubuf[i*4+1])*COL[clr_n].c[3])/0xff;
		//tubuf[i*4+2]= tubuf[i*4+2]+((COL[clr_n].c[0]-tubuf[i*4+2])*COL[clr_n].c[3])/0xff;
		//tubuf[i*4+3]= tubuf[i*4+3]+((0xff-tubuf[i*4+3])*COL[clr_n].c[3])/0xff;
		//memcpy(outmap+ps.y2*p->w*4+ps.x2*4,   &COL[clr_n].c32, 4);
		
				qq=COL[clr_n].c[2]-((COL[clr_n].c[2]-tobuf[ pos*4 ])*tobuf[pos*4+3])/0xff;
				tobuf[ pos*4 ]=qq+((COL[clr_n].c[2]-qq)*COL[clr_n].c[3])/0xff;
					
				qq=COL[clr_n].c[1]-((COL[clr_n].c[1]-tobuf[pos*4+1])*tobuf[pos*4+3])/0xff;
				tobuf[pos*4+1]=qq+((COL[clr_n].c[1]-qq)*COL[clr_n].c[3])/0xff;
					
				qq=COL[clr_n].c[0]-((COL[clr_n].c[0]-tobuf[pos*4+2])*tobuf[pos*4+3])/0xff;
				tobuf[pos*4+2]=qq+((COL[clr_n].c[0]-qq)*COL[clr_n].c[3])/0xff;
				
		tobuf[pos*4+3]= tobuf[pos*4+3]+((0xff-tobuf[pos*4+3])*COL[clr_n].c[3])/0xff;
	}

	if(!p->z)
	{
		memcpy(tmpbuf, prf+pos*4, 4);
	}
	else
	{
		xy=(((i*(p->z+1))*p->w*(p->z+1))+(j*(p->z+1)));
		memcpy(tmpbuf, prf+xy*4, 4);
	}
	  for(k=0; k<p->cs; k++)
	   if(p->sl[k].v)
		{
			qq=p->sl[k].map[ pos*4 ]-((p->sl[k].map[ pos*4 ]-tmpbuf[0])*tmpbuf[3])/0xff;
			tmpbuf[0]=qq+((p->sl[k].map[ pos*4 ]-qq)*p->sl[k].map[pos*4+3])/0xff;
			qq=p->sl[k].map[pos*4+1]-((p->sl[k].map[pos*4+1]-tmpbuf[1])*tmpbuf[3])/0xff;
			tmpbuf[1]=qq+((p->sl[k].map[pos*4+1]-qq)*p->sl[k].map[pos*4+3])/0xff;
			qq=p->sl[k].map[pos*4+2]-((p->sl[k].map[pos*4+2]-tmpbuf[2])*tmpbuf[3])/0xff;
			tmpbuf[2]=qq+((p->sl[k].map[pos*4+2]-qq)*p->sl[k].map[pos*4+3])/0xff;
			tmpbuf[3]= tmpbuf[3]+((0xff-tmpbuf[3])*p->sl[k].map[pos*4+3])/0xff;
		}
	if(!p->z)
	{
		switch(Pt.m)
		{
			case 0:
				img_32_8(vpic.bitmap+pos, tmpbuf, 1, NULL);
			 break;
			case 1:
				img_32_16(vpic.bitmap+pos*2, tmpbuf, 1, NULL, 0);
			 break;
			case 2:
				memcpy(vpic.bitmap+pos*4, tmpbuf, 4);//img_32_a(vpic.bitmap, &p[0]);
			 break;
		}
	}
	else
	{
	  for(zj=0; zj<p->z+1; zj++)
		for(zi=0; zi<p->z+1; zi++)
		{
			xy=(((i*(p->z+1)+zi)*p->w*(p->z+1))+(j*(p->z+1)+zj));
			switch(Pt.m)
			{
				case 0:
					img_32_8(vpic.bitmap+xy, tmpbuf, 1, NULL);
				 break;
				case 1:
					img_32_16(vpic.bitmap+xy*2, tmpbuf, 1, NULL, 0);
				 break;
				case 2:
					memcpy(vpic.bitmap+xy*4, tmpbuf, 4);//img_32_a(vpic.bitmap, &p[0]);
				 break;
			}
			// qq=p->sl[k].map[ (j*p->w+i)*4 ]-((p->sl[k].map[ (j*p->w+i)*4 ]-tmpbuf[ xy ])*tmpbuf[xy+3])/0xff;
			// tmpbuf[ xy ]=qq+((p->sl[k].map[ (j*p->w+i)*4 ]-qq)*p->sl[k].map[(j*p->w+i)*4+3])/0xff;
			// qq=p->sl[k].map[(j*p->w+i)*4+1]-((p->sl[k].map[(j*p->w+i)*4+1]-tmpbuf[xy+1])*tmpbuf[xy+3])/0xff;
			// tmpbuf[xy+1]=qq+((p->sl[k].map[(j*p->w+i)*4+1]-qq)*p->sl[k].map[(j*p->w+i)*4+3])/0xff;
			// qq=p->sl[k].map[(j*p->w+i)*4+2]-((p->sl[k].map[(j*p->w+i)*4+2]-tmpbuf[xy+2])*tmpbuf[xy+3])/0xff;
			// tmpbuf[xy+2]=qq+((p->sl[k].map[(j*p->w+i)*4+2]-qq)*p->sl[k].map[(j*p->w+i)*4+3])/0xff;
			// tmpbuf[xy+3]= tmpbuf[xy+3]+((0xff-tmpbuf[xy+3])*p->sl[k].map[(j*p->w+i)*4+3])/0xff;
		}
	}
}

void do_point()
{
	RECT ps;
	ps.x2=p->cur.x;
	ps.y2=p->cur.y;
	stp(p->sl[p->ns].map, ps, 0, NULL);
	//do_vpic();
}

void do_kist()
{
	if(inst[Pt.i].p) inst[Pt.i].p=0;
	else inst[Pt.i].p=1;
}

void do_line()
{
	inst[Pt.i].p=0;
	int i,j;
	char a=0,s=0;
	//unsigned short q;
	RECT ps;
		patch_rect(&dr, p->cur.x, p->cur.y, p->cur.x2, p->cur.y2);
	if(p->cur.x<p->cur.x2)
	{
		patch_rect(&dr, p->cur.x2, dr.y, p->cur.x, dr.y2);
		//q=p->cur.x;
		//p->cur.x=p->cur.x2;
		//p->cur.x2=q;
		a=1;
	}
	if(p->cur.y<p->cur.y2)
	{
		patch_rect(&dr, dr.x, p->cur.y2, dr.x2, p->cur.y);
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
				stp(p->sl[p->ns].map, ps, 0, NULL);
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
				stp(p->sl[p->ns].map, ps, 0, NULL);
				//stp(cur_y1+i, cur_x1+j, 0, 0, 0, 0, 0);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4, &COL[0][2], 1);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+1, &COL[0][1], 1);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+2, &COL[0][0], 1);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+3, &COL[0][3], 1);
			}
		}
			//p->cur.y2++;
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
				stp(p->sl[p->ns].map, ps, 0, NULL);
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
				stp(p->sl[p->ns].map, ps, 0, NULL);
				//stp(cur_y1+i, cur_x1+j, 0, 0, 0, 0, 0);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4, &COL[0][2], 1);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+1, &COL[0][1], 1);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+2, &COL[0][0], 1);
				//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+3, &COL[0][3], 1);
			}
		}
		//p->cur.x2++;
	}
	//p->cur.x--;
	//p->cur.y--;
	//do_vpic();
}



void do_rect()
{
		inst[Pt.i].p=0;
		int i,j;
		//char a=0,s=0;
		//unsigned short q;
		RECT ps;
		patch_rect(&dr, p->cur.x, p->cur.y, p->cur.x2, p->cur.y2);
	if(p->cur.x<p->cur.x2)
	{
		patch_rect(&dr, p->cur.x2, dr.y, p->cur.x, dr.y2);
		//q=p->cur.x;
		//p->cur.x=p->cur.x2;
		//p->cur.x2=q;
		//a=1;
	}
	if(p->cur.y<p->cur.y2)
	{
		patch_rect(&dr, dr.x, p->cur.y2, dr.x2, p->cur.y);
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
				stp(p->sl[p->ns].map, ps, 0, NULL);
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
					stp(p->sl[p->ns].map, ps, 0, NULL);
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
					stp(p->sl[p->ns].map, ps, 1, NULL);
					//stp(cur_y1+i, cur_x1+j, 0, 1, 0, 0, 0);
					//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4, &COL[1][2], 1);
					//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+1, &COL[1][1], 1);
					//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+2, &COL[1][0], 1);
					//memcpy(premap+(cur_y1+i)*pic_w*4+(cur_x1+j)*4+3, &COL[1][3], 1);
				}
			}
		}
	}
	//do_vpic();
}

/* void do_ellipse()
{
		inst[Pt.i].p=0;
		int i,j;
		//char a=0,s=0;
		unsigned short w;
		RECT ps;
		patch_rect(&dr, p->cur.x, p->cur.y, p->cur.x2, p->cur.y2);
	if(p->cur.x<p->cur.x2)
	{
		patch_rect(&dr, p->cur.x2, dr.y, p->cur.x, dr.y2);
		//q=p->cur.x;
		//p->cur.x=p->cur.x2;
		//p->cur.x2=q;
		//a=1;
	}
	if(p->cur.y<p->cur.y2)
	{
		patch_rect(&dr, dr.x, p->cur.y2, dr.x2, p->cur.y);
		//q=cur_y;
		//cur_y=cur_y1;
		//cur_y1=q;
		//s=1;
	}
		for(i=0;i<dr.y-dr.y2+1;i++)
		{
			for(j=0;j<dr.x-dr.x2+1;j++)
			{
				//w=sqrt((i-(p->cur.x-p->cur.x2)/2)*(i-(p->cur.x-p->cur.x2)/2)+(j-(p->cur.x-p->cur.x2)/2)*(j-(p->cur.x-p->cur.x2)/2));
				w=((j-(dr.x-dr.x2)/2)*(j-(dr.x-dr.x2)/2)*100)/(((dr.x-dr.x2)/2)*((dr.x-dr.x2)/2))+((i-(dr.y-dr.y2)/2)*(i-(dr.y-dr.y2)/2)*100)/(((dr.y-dr.y2)/2)*((dr.y-dr.y2)/2));
				if(w<=100)
				{
					ps.x2=dr.x2+j;
					ps.y2=dr.y2+i;
					stp(p->sl[p->ns].map, ps, 0, NULL);
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
					stp(p->sl[p->ns].map, ps, 1, NULL);
				}
			}
		}
	//do_vpic();
} */

void do_do_elli()
{
		inst[Pt.i].p=0;
		int i,j;
		//char a=0,s=0;
		unsigned short ww, *w;//=malloc(SCR.sw*SCR.sh*2);
		RECT ps;
		//patch_rect(&dr, p->cur.x, p->cur.y, p->cur.x2, p->cur.y2);
	//if(p->cur.x<p->cur.x2)
	//{
		//patch_rect(&dr, p->cur.x2, dr.y, p->cur.x, dr.y2);
		//q=p->cur.x;
		//p->cur.x=p->cur.x2;
		//p->cur.x2=q;
		//a=1;
	//}
	//if(p->cur.y<p->cur.y2)
	//{
		//patch_rect(&dr, dr.x, p->cur.y2, dr.x2, p->cur.y);
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
					stp(p->sl[p->ns].map, ps, 0, NULL);
				}
				else if(ww!=0x0000)
				{
					ps.x2=dr.x2+j;
					ps.y2=dr.y2+i;
					stp(p->sl[p->ns].map, ps, 1, NULL);
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
					stp(p->sl[p->ns].map, ps, 1, NULL);
				}
			}
		} */
	//do_vpic();
		gst=2;
	DirectRedrawGUI();
}

void do_elli()
{
		gst=0;
		inst[Pt.i].p=2;
		GBS_StartTimerProc(&instmr, 1, do_do_elli);
}




extern void cangecol();



// **************************** прорисовка ************************


void dr_line()
{
	if(inst[Pt.i].p!=2)
	{
		patch_rect(&dr, p->cur.x, p->cur.y, p->cur.x2, p->cur.y2);
	}
	DrawLine(p->x+(p->z+1)*p->cur.x,YDP+p->y+(p->z+1)*p->cur.y,p->x+(p->z+1)*p->cur.x2,YDP+p->y+(p->z+1)*p->cur.y2,0,COL[0].c);
	if(inst[Pt.i].p==2)
	{
		if(dr.x<p->cur.x2) patch_rect(&dr, p->cur.x2, dr.y, p->cur.x, dr.y2);
		if(dr.y<p->cur.y2) patch_rect(&dr, dr.x, p->cur.y2, dr.x2, p->cur.y);
		DrawRectangle(0,0,dr.x-dr.x2,dr.y-dr.y2,0,black,black);
		DrawLine(0,0,dr.x-dr.x2,dr.y-dr.y2,0,white);
	}
}

void dr_rect()
{DrawRectangle(p->x+(p->z+1)*p->cur.x,YDP+p->y+(p->z+1)*p->cur.y,p->x+(p->z+1)*p->cur.x2,YDP+p->y+(p->z+1)*p->cur.y2,1,COL[0].c,COL[1].c);}

void dr_ellipse()
{
	if(inst[Pt.i].p!=2)
	{
		patch_rect(&dr, p->cur.x, p->cur.y, p->cur.x2, p->cur.y2);
		if(p->cur.x<p->cur.x2) patch_rect(&dr, p->cur.x2, dr.y, p->cur.x, dr.y2);
		if(p->cur.y<p->cur.y2) patch_rect(&dr, dr.x, p->cur.y2, dr.x2, p->cur.y);
	}
	drawArc(p->x+(p->z+1)*dr.x2,YDP+p->y+(p->z+1)*dr.y2,p->x+(p->z+1)*dr.x,YDP+p->y+(p->z+1)*dr.y,0,360,0,COL[0].c,COL[1].c);
	if(inst[Pt.i].p==2)
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
			if(inst[Pt.i].p) inst[Pt.i].p=0;
			else MsgBoxYesNo(1,(int)"Выход?",ExitProc);
		  break;
		 case UP_BUTTON:
		 case '2':
			p->cur.y-=st;
			if(p->cur.y<0)
			{
				if(BigPy)p->y=PCPS.y2-p->h*(p->z+1)-OTSTUP;
				p->cur.y=p->h-1;
			}
		  break;
		 case DOWN_BUTTON:
		 case '8':
			p->cur.y+=st;
			if(p->cur.y>=p->h)
			{
				if(BigPy)p->y=PCPS.y+OTSTUP;
				p->cur.y=0;
			}
	      break;
		 case LEFT_BUTTON:
		 case '4':
			p->cur.x-=st;
			if(p->cur.x<0)
			{
				if(BigPx)p->x=PCPS.x2-p->w*(p->z+1)-OTSTUP;
				p->cur.x=p->w-1;
			}
		  break;
		 case RIGHT_BUTTON:
		 case '6':
			p->cur.x+=st;
			if(p->cur.x>=p->w)
			{
				if(BigPx)p->x=PCPS.x+OTSTUP;
				p->cur.x=0;
			}
		  break;
		 case '1':
			p->cur.y-=st;
			if(p->cur.y<0)
			{
				if(BigPy)p->y=PCPS.y2-p->h*(p->z+1)-OTSTUP;
				p->cur.y=p->h-1;
			}
			p->cur.x-=st;
			if(p->cur.x<0)
			{
				if(BigPx)p->x=PCPS.x2-p->w*(p->z+1)-OTSTUP;
				p->cur.x=p->w-1;
			}
		  break;
		 case '3':
			p->cur.y-=st;
			if(p->cur.y<0)
			{
				if(BigPy)p->y=PCPS.y2-p->h*(p->z+1)-OTSTUP;
				p->cur.y=p->h-1;
			}
			p->cur.x+=st;
			if(p->cur.x>=p->w)
			{
				if(BigPx)p->x=PCPS.x+OTSTUP;
				p->cur.x=0;
			}
		  break;
		 case '7':
			p->cur.y+=st;
			if(p->cur.y>=p->h)
			{
				if(BigPy)p->y=PCPS.y+OTSTUP;
				p->cur.y=0;
			}
			p->cur.x-=st;
			if(p->cur.x<0)
			{
				if(BigPx)p->x=PCPS.x2-p->w*(p->z+1)-OTSTUP;
				p->cur.x=p->w-1;
			}
		  break;
		 case '9':
			p->cur.y+=st;
			if(p->cur.y>=p->h)
			{
				if(BigPy)p->y=PCPS.y+OTSTUP;
				p->cur.y=0;
			}
			p->cur.x+=st;
			if(p->cur.x>=p->w)
			{
				if(BigPx)p->x=PCPS.x+OTSTUP;
				p->cur.x=0;
			}
		  break;
		 case RIGHT_SOFT:
			//dozoom();
			menu(zmenu);
		  break;
		 case '#':
			cangecol();
			//inst_mod=0;
			//create_instm();
		  break;
		}
	}
	if(p->x+p->cur.x*(p->z+1)>PCPS.x2-OTSTUP) p->x-=st*(p->z+1);
	if(p->x+p->cur.x*(p->z+1)<PCPS.x+OTSTUP) p->x+=st*(p->z+1);
	if(p->y+p->cur.y*(p->z+1)>PCPS.y2-OTSTUP) p->y-=st*(p->z+1);
	if(p->y+p->cur.y*(p->z+1)<PCPS.y+OTSTUP) p->y+=st*(p->z+1);
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
		//dozoom();
	  break;
	case '*':
		Preview();
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
		inst[Pt.i].doit();
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
		inst[Pt.i].doit();
	}
	if(inst[Pt.i].p>0)
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
	if(!inst[Pt.i].p) stkey(msg);
	int k=move_cur(msg, 1, 5);
	switch(msg->gbsmsg->msg)
	{
		case KEY_DOWN:
			if((msg->gbsmsg->submess==ENTER_BUTTON)||(msg->gbsmsg->submess=='5'))
			{
				if(inst[Pt.i].p==1)	inst[Pt.i].doit();
				else
				//{
					inst[Pt.i].p=1;
					p->cur.x2=p->cur.x;
					p->cur.y2=p->cur.y;
					/*dr.x=p->cur.x;
					dr.x2=p->cur.x;
					dr.y=p->cur.y;
					dr.y2=p->cur.y;
				} */
			}
	/* 	case LONG_PRESS:
			if(inst[Pt.i].p)
			{
				if(p->cur.x>p->cur.x2) {dr.x2=p->cur.x; dr.x=p->cur.x2;}
				else {dr.x=p->cur.x; dr.x2=p->cur.x2;}
				if(p->cur.y>p->cur.y2) {dr.y2=p->cur.y; dr.y=p->cur.y2;}
				else {dr.y=p->cur.y; dr.y2=p->cur.y2;}
			} */
		 break;
	}
	DirectRedrawGUI();
	return(k);
}

