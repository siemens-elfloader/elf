#include "image.h"
#include "instr.c"
#include "read_write.c"

void cangefon()
{
	int i;
	for (i=0;i<p1.sz;i++)
	{
		memcpy(sl[0].p.bitmap+i*4, &COL[2].c32, 4);
	}
	do_vpic();
}

void docols(char cf)
{
	unsigned int i;
	for(i=0;i<3;i++)
	{
		if(COL[i].c[3]<25) {COL[i].c8=0xC0; COL[i].c16=0xE000; COL[i].c32=0;}
		else
		{
			/* COL[i].c8=(COL[i].c[0] & 0xE0);
			COL[i].c8|=((COL[i].c[1]>>3)&0x1C);
			COL[i].c8|=((COL[i].c[2]>>6)&0x3);
			COL[i].c16=((COL[i].c[0]<<8)&0xF800);
			COL[i].c16|=((COL[i].c[1]<<3)&0x7E0);
			COL[i].c16|=((COL[i].c[2]>>3)&0x1F); */
			COL[i].c32=(COL[i].c[3]<<24)+(COL[i].c[0]<<16)+(COL[i].c[1]<<8)+(COL[i].c[2]);
			COL[i].c16=rgb_24_16(COL[i].c32);
			COL[i].c8=rgb_24_8(COL[i].c32);
		}
	}
	memcpy(dop_col0[0], COL[0].c, 4);
	if(cf) cangefon();
}

void cangecol()
{
	char dop_cl[4];
	memcpy(dop_cl, &COL[0].c, 4);
	memcpy(&COL[0].c, &COL[1].c, 4);
	memcpy(&COL[1].c, dop_cl, 4);
	docols(0);
}

void do_vpic()
{
	unsigned int i,k,j;
	char c1;
	unsigned short c2;
		switch(p1.mod)
		{
			case 0:
				for(i=0; i<vpic.h*vpic.w; i++)
					vpic.bitmap[i]=prz.c8;
			 break;
			case 1:
				for(i=0; i<vpic.h*vpic.w; i++)
					memcpy(vpic.bitmap+i*2, &prz.c16, 2);
			 break;
			case 2:
				zeromem(vpic.bitmap, vpic.h*vpic.w*4 );
			 break;
		}
	for(k=0; k<p1.sl_cnt; k++)
	 if(sl[k].v)
		switch(p1.mod)
		{
			case 0:
				if(!p1.zoom)
				{
				  for(i=0; i<p1.sz; i++)
					if(sl[k].p.bitmap[i*4+3]>25)
					{
						c1=sl[k].p.bitmap[i*4+2] & 0xE0;
						c1|=(sl[k].p.bitmap[i*4+1]>>3)&0x1C;
						c1|=(sl[k].p.bitmap[i*4+0]>>6)&0x3;
						memcpy(vpic.bitmap+i, &c1, 1);
					}
				}
				else
				  for(i=0; i<p1.h; i++)
				   for(j=0; j<p1.w; j++)
					if(sl[k].p.bitmap[(i*p1.w+j)*4+3]>25)
					{
						c1=sl[k].p.bitmap[(i*p1.w+j)*4+2] & 0xE0;
						c1|=(sl[k].p.bitmap[(i*p1.w+j)*4+1]>>3)&0x1C;
						c1|=(sl[k].p.bitmap[(i*p1.w+j)*4+0]>>6)&0x3;
						memcpy(vpic.bitmap+(i*vpic.w+j)*2, &c1, 1);
						memcpy(vpic.bitmap+(i*vpic.w+j)*2+1, &c1, 1);
						memcpy(vpic.bitmap+(i*vpic.w+j)*2+vpic.w, &c1, 1);
						memcpy(vpic.bitmap+(i*vpic.w+j)*2+vpic.w+1, &c1, 1);
					}
			 break;
			case 1:
				if(!p1.zoom)
				{
				  for(i=0; i<p1.sz; i++)
					if(sl[k].p.bitmap[i*4+3]>25)
					{
						c2=((sl[k].p.bitmap[i*4+2]<<8)&0xF800);
						c2|=((sl[k].p.bitmap[i*4+1]<<3)&0x7E0);
						c2|=((sl[k].p.bitmap[i*4+0]>>3)&0x1F);
						memcpy(vpic.bitmap+i*2, &c2, 2);
					}
				}
				else
				  for(i=0; i<p1.h; i++)
				   for(j=0; j<p1.w; j++)
					if(sl[k].p.bitmap[(i*p1.w+j)*4+3]>25)
					{
						c2=((sl[k].p.bitmap[(i*p1.w+j)*4+2]<<8)&0xF800);
						c2|=((sl[k].p.bitmap[(i*p1.w+j)*4+1]<<3)&0x7E0);
						c2|=((sl[k].p.bitmap[(i*p1.w+j)*4+0]>>3)&0x1F);
						memcpy(vpic.bitmap+(i*vpic.w+j)*4, &c2, 2);
						memcpy(vpic.bitmap+(i*vpic.w+j)*4+2, &c2, 2);
						memcpy(vpic.bitmap+(i*vpic.w+j)*4+vpic.w*2, &c2, 2);
						memcpy(vpic.bitmap+(i*vpic.w+j)*4+vpic.w*2+2, &c2, 2);
					}
			 break;
			case 2:
				if(!p1.zoom)
				{
				  for(i=0; i<p1.sz; i++)
					if(sl[k].p.bitmap[i*4+3]>25)
					{
						memcpy(vpic.bitmap+i*4, sl[k].p.bitmap+i*4, 4);
					}
				}
				else
				  for(i=0; i<p1.h; i++)
				   for(j=0; j<p1.w; j++)
					if(sl[k].p.bitmap[(i*p1.w+j)*4+3]>25)
					{
						memcpy(vpic.bitmap+(i*vpic.w+j)*8, sl[k].p.bitmap+(i*p1.w+j)*4, 4);
						memcpy(vpic.bitmap+(i*vpic.w+j)*8+4, sl[k].p.bitmap+(i*p1.w+j)*4, 4);
						memcpy(vpic.bitmap+(i*vpic.w+j)*8+vpic.w*4, sl[k].p.bitmap+(i*p1.w+j)*4, 4);
						memcpy(vpic.bitmap+(i*vpic.w+j)*8+vpic.w*4+4, sl[k].p.bitmap+(i*p1.w+j)*4, 4);
					}
			 break;
		}
}

void do_prf()
{
	unsigned int i,j, k=2*SQ_SZ,f;
	char cl;
	//if(prf.bitmap) mfree(prf.bitmap);
	//prf.bitmap=malloc(p1.sz+3*p1.sz*p1.zoom);
	for (i=0;i<prf.h;i++)
	{
		k++;
		if(k>=2*SQ_SZ) k=0;
		if(k<SQ_SZ) f=2*SQ_SZ;
		else f=SQ_SZ-1;
		for (j=0;j<prf.w;j++)
		{
			f++;
			if(f>=2*SQ_SZ) f=0;
			if(f<SQ_SZ)
			{
				cl=(B_COL_1[0] & 0xE0);
				cl|=((B_COL_1[1]>>3)&0x1C);
				cl|=((B_COL_1[2]>>6)&0x3);
			}
			else
			{
				cl=(B_COL_2[0] & 0xE0);
				cl|=((B_COL_2[1]>>3)&0x1C);
				cl|=((B_COL_2[2]>>6)&0x3);
			}
			memcpy(prf.bitmap+i*prf.w+j, &cl, 1);
		}
	}
}

#ifdef ELKA
 #define max_sz 0xffff
#else
 #define max_sz 0xff
#endif

void dozoom()
{
  if((p1.w>max_sz/2)||(p1.h>max_sz/2)) MsgBoxError(1, (int)"Невозможно!!!");
  else
  {
	if(p1.zoom)
	{
		p1.zoom=0;
		prf.h=vpic.h=p1.h;
		prf.w=vpic.w=p1.w;
		if(vpic.w>=PCPS.x2-PCPS.x-2)
		{
			BigPx=1;
			p1.x+=cur.x;
		}
		else
		{
			p1.x=(PCPS.x2+PCPS.x)/2-p1.w/2; BigPx=0;
		}
		if(vpic.h>=PCPS.y2-PCPS.y-2)
		{
			BigPy=1;
			p1.y+=cur.y;
		}
		else
		{
			p1.y=(PCPS.y2+PCPS.y)/2-p1.h/2; BigPy=0;
		}
		mfree(prf.bitmap);
		prf.bitmap=malloc(p1.sz);
		do_prf();
		mfree(vpic.bitmap);
		vpic.bitmap=malloc(vpic.h*vpic.w*map_mod[p1.mod+3]);
		do_vpic();
	}
	else
	{
		p1.zoom=1;
		prf.h=vpic.h=p1.h*2;
		prf.w=vpic.w=p1.w*2;
		if(vpic.w>=PCPS.x2-PCPS.x-2)
		{
			BigPx=1;
			p1.x-=cur.x;
		}
		else
		{
			p1.x=(PCPS.x2+PCPS.x)/2-p1.w; BigPx=0;
		}
		if(vpic.h>=PCPS.y2-PCPS.y-2)
		{
			BigPy=1;
			p1.y-=cur.y;
		}
		else
		{
			p1.y=(PCPS.y2+PCPS.y)/2-p1.h; BigPy=0;
		}
		mfree(prf.bitmap);
		prf.bitmap=malloc(p1.sz*4);
		do_prf();
		mfree(vpic.bitmap);
		vpic.bitmap=malloc(vpic.h*vpic.w*map_mod[p1.mod+3]);
		do_vpic();
	}
  }
}

void del_sl(unsigned int nom)
{
	int i;
	mfree(sl[nom].p.bitmap);
	if(nom<p1.sl_cnt-1)
	{
		for(i=nom; i<p1.sl_cnt; i++) sl[i]=sl[i+1];
		//mfree(sl[p1.sl_cnt-1].p.bitmap);
	}
	if(p1.ac_sl>=nom) p1.ac_sl--;
	p1.sl_cnt--;
}

void new_sl(unsigned int nom, char *slname)
{
	if(p1.sl_cnt==8) MsgBoxError(1, (int)"Много\nвредно\n:)");
	else
	{
		int i;
		if(nom<p1.sl_cnt)
		for(i=p1.sl_cnt; i>nom; i--) sl[i]=sl[i-1];
		sl[nom].p.bpnum=10;
		sl[nom].v=1;
		sl[nom].p.w=p1.w;
		sl[nom].p.h=p1.h;
		memcpy( sl[nom].nm,  slname, 16);
		p1.sl_cnt++;
		p1.ac_sl=nom;
		sl[nom].p.bitmap=malloc(p1.sz*4);
		zeromem(sl[nom].p.bitmap, p1.sz*4);
	}
}

void crpic()
{
	unsigned int i;
	if(!open)
	{
		p1.sz=p1.w*p1.h;
		p1.ac_sl=1;
		sl[0].p.w=sl[1].p.w=p1.w;
		sl[0].p.h=sl[1].p.h=p1.h;
		sl[0].p.bpnum=10;
		sl[1].p.bpnum=10;
		sl[0].v=1;
		sl[1].v=1;
		sl[0].x=sl[0].y=-3;
		sprintf( sl[0].nm, "FON" );
		sprintf( sl[1].nm, "SLOY 1" );
		if(start)
		{
			sl[0].p.bitmap=malloc(p1.sz*4);
			sl[1].p.bitmap=malloc(p1.sz*4);
			zeromem(sl[1].p.bitmap, p1.sz*4);
			for(i=0; i<p1.sz; i++)
			{
				memcpy(sl[0].p.bitmap+i*4, &COL[2].c32, 4);
			}
		}
		else
		{
			for(i=0; i<p1.sl_cnt; i++) mfree(sl[i].p.bitmap);
			sl[0].p.bitmap=malloc(p1.sz*4);
			sl[1].p.bitmap=malloc(p1.sz*4);
			zeromem(sl[1].p.bitmap, p1.sz*4);
			for(i=0; i<p1.sz; i++)
			{
				memcpy(sl[0].p.bitmap+i*4, &COL[2].c32, 4);
			}
			mfree(vpic.bitmap);
			mfree(prf.bitmap);
		}
		p1.sl_cnt=2;
	}
	open=0;
	prf.w=vpic.w=p1.w;
	prf.h=vpic.h=p1.h;
	if(vpic.w>=PCPS.x2-PCPS.x-2) BigPx=1;
	if(vpic.h>=PCPS.y2-PCPS.y-2) BigPy=1;
	vpic.bpnum=map_mod[p1.mod];
	vpic.bitmap=malloc(vpic.h*vpic.w*map_mod[p1.mod+3]);
	prf.bitmap=malloc(p1.sz);
	p1.x=(PCPS.x2+PCPS.x)/2-p1.w/2;
	p1.y=(PCPS.y2+PCPS.y)/2-p1.h/2;
	cur.x=p1.w/2;
	cur.y=p1.h/2;
	do_prf();
	do_vpic();
	docols(0);
}








// *********************** Предпросмотр картинки ******************** //


void pvw_Redraw(PREVIEW_GUI *data)
{
	if (data->gui.state==2)
	{
		DrawRectangle(0,YDP, SCR.sw,SCR.sh, 0,black,black);
		DrwImg((IMGHDR *)&prf, data->x, data->y, white, black);
		DrwImg((IMGHDR *)&vpic, data->x, data->y, white, black);
	}
}

void pvw_Create(PREVIEW_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

void pvw_Close(PREVIEW_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

void pvw_Focus(PREVIEW_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
	DisableIDLETMR();
	#ifdef ELKA
	if(UseFullScr) DisableIconBar(1);
	#endif
  data->gui.state=2;
}

void pvw_Unfocus(PREVIEW_GUI *data, void (*mfree_adr)(void *))
{
	#ifdef ELKA
	if(UseFullScr) DisableIconBar(0);
	#endif
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int pvw_OnKey(PREVIEW_GUI *data, GUI_MSG *msg)
{
	char st=5;
	switch(msg->gbsmsg->msg)
	{
	  case LONG_PRESS: st=20;
	  case KEY_DOWN:
		switch(msg->gbsmsg->submess)
		{
			case RED_BUTTON:
			case RIGHT_SOFT:
				if(p1.zoom) dozoom();
				return 1;
			case DOWN_BUTTON:
			case '8':
				data->y+=st;
			 break;
			case UP_BUTTON:
			case '2':
				data->y-=st;
			 break;
			case RIGHT_BUTTON:
			case '6':
				data->x+=st;
			 break;
			case LEFT_BUTTON:
			case '4':
				data->x-=st;
			 break;
			case '0':
				dozoom();
				data->x=SCR.sw/2-vpic.w/2;
				data->y=SCR.sh/2-vpic.h/2;
			 break;
		}
		DirectRedrawGUI();
	}
	return(0);
}

void pvw_Destroy(PREVIEW_GUI *data, void (*mfree_adr)(void *))
{
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(data,mfree_adr);
}

const void * const pvw_methods[11]={
  (void *)pvw_Redraw,
  (void *)pvw_Create,
  (void *)pvw_Close,
  (void *)pvw_Focus,
  (void *)pvw_Unfocus,
  (void *)pvw_OnKey,
  0,
  (void *)pvw_Destroy,
  (void *)met0,
  (void *)met0,
  0
};

int Preview()
{
  PREVIEW_GUI *pvw_gui=malloc(sizeof(PREVIEW_GUI));
  zeromem(pvw_gui,sizeof(PREVIEW_GUI));
  patch_rect((RECT*)&Canvas_2,0,YDP,ScreenW()-1,ScreenH()-1);
  pvw_gui->gui.canvas=(void *)(&Canvas_2);
  pvw_gui->gui.flag30=2;
  pvw_gui->gui.methods=(void *)pvw_methods;
  pvw_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  pvw_gui->x=SCR.sw/2-p1.w/2;
  pvw_gui->y=SCR.sh/2-p1.h/2;
  return(CreateGUI(pvw_gui));
}
