#include "image.h"
#include "instr.c"
#include "read_write.c"

void cangefon()
{
	int i;
	for (i=0;i<p->sz;i++)
	{
		memcpy(p->sl[0].map+i*4, &COL[2].c32, 4);
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
			COL[i].c32=RGBA_BGRA(COL[i].c);
			COL[i].c16=RGB_24_16(COL[i].c);
			COL[i].c8=RGB_24_8(COL[i].c);
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
	unsigned int /* i,j, k=2*SQ_SZ,f, dc, */ tmpbsz;
	tmpbsz=vpic.h*vpic.w*4;
	char *tmpbuf=malloc(tmpbsz);
	memcpy(tmpbuf, prf, tmpbsz);
	// for (i=0;i<p->h;i++)
		// {
			// k++;
			// if(k>=2*SQ_SZ) k=0;
			// if(k<SQ_SZ) f=2*SQ_SZ;
			// else f=SQ_SZ-1;
			// for (j=0;j<p->w;j++)
			// {
				// f++;
				// if(f>=2*SQ_SZ) f=0;
				// if(f<SQ_SZ)
				// {
					// dc=RGBA_BGRA((char*)B_COL_1);
					// memcpy(tmpbuf+(i*p->w+j)*4, &dc, 3);
					// tmpbuf[(i*p->w+j)*4+3]=0xff;
				// }
				// else
				// {
					// dc=RGBA_BGRA((char*)B_COL_2);
					// memcpy(tmpbuf+(i*p->w+j)*4, &dc, 4);
					// tmpbuf[(i*p->w+j)*4+3]=0xff;
				// }
			// }
		// }
		img_32_a(tmpbuf, p, p->z);
		switch(Pt.m)
		{
			case 0:
				img_32_8(vpic.bitmap, tmpbuf, tmpbsz/4, NULL);
			 break;
			case 1:
				img_32_16(vpic.bitmap, tmpbuf, tmpbsz/4, NULL, 0);
			 break;
			case 2:
				memcpy(vpic.bitmap, tmpbuf, tmpbsz);//img_32_a(vpic.bitmap, &p[0]);
			 break;
		}
	mfree(tmpbuf);
}

void do_prf()
{
	unsigned int i,j, k=2*SQ_SZ, f, dc;
	if(prf) mfree(prf);
	prf=malloc(vpic.w*vpic.h*4);
	for (i=0;i<vpic.h;i++)
	{
		k++;
		if(k>=2*SQ_SZ) k=0;
		if(k<SQ_SZ) f=2*SQ_SZ;
		else f=SQ_SZ-1;
		for (j=0;j<vpic.w;j++)
		{
			f++;
			if(f>=2*SQ_SZ) f=0;
			if(f<SQ_SZ)
			{
				dc=RGBA_BGRA((char*)B_COL_1);
				memcpy(prf+(i*vpic.w+j)*4, &dc, 3);
				prf[(i*vpic.w+j)*4+3]=0xFF;
			}
			else
			{
				dc=RGBA_BGRA((char*)B_COL_2);
				memcpy(prf+(i*vpic.w+j)*4, &dc, 3);
				prf[(i*vpic.w+j)*4+3]=0xFF;
			}
		}
	}
}

#ifdef ELKA
 #define max_sz 0xffff
#else
 #define max_sz 0xff
#endif

void dozoom(signed char z)
{
  if((p->w>max_sz/2)||(p->h>max_sz/2)) MsgBoxError(1, (int)"Невозможно!!!");
  else
  {
	if(z<=0)
	{
		vpic.h=p->h;
		vpic.w=p->w;
		if(vpic.w>=PCPS.x2-PCPS.x-2)
		{
			BigPx=1;
			p->x+=p->cur.x;
		}
		else
		{
			p->x=(PCPS.x2+PCPS.x)/2-p->w/2; BigPx=0;
		}
		if(vpic.h>=PCPS.y2-PCPS.y-2)
		{
			BigPy=1;
			p->y+=p->cur.y;
		}
		else
		{
			p->y=(PCPS.y2+PCPS.y)/2-p->h/2; BigPy=0;
		}
		p->z=0;
		mfree(prf);
		prf=malloc(vpic.h*vpic.w*4);
		do_prf();
		mfree(vpic.bitmap);
		vpic.bitmap=malloc(vpic.h*vpic.w*map_mod[Pt.m+3]);
		do_vpic();
	}
	else
	{
		vpic.h=p->h*(z+1);
		vpic.w=p->w*(z+1);
		if(vpic.w>=PCPS.x2-PCPS.x-2)
		{
			BigPx=1;
			if(z>p->z) p->x-=p->cur.x;
			else p->x+=p->cur.x;
		}
		else
		{
			p->x=(PCPS.x2+PCPS.x)/2-p->w*(z+1)/2; BigPx=0;
		}
		if(vpic.h>=PCPS.y2-PCPS.y-2)
		{
			BigPy=1;
			if(z>p->z) p->y-=p->cur.y;
			else p->y+=p->cur.y;
		}
		else
		{
			p->y=(PCPS.y2+PCPS.y)/2-p->h*(z+1)/2; BigPy=0;
		}
		p->z=z;
		//mfree(prf);
		//prf=malloc(vpic.h*vpic.w*4);
		do_prf();
		mfree(vpic.bitmap);
		vpic.bitmap=malloc(vpic.h*vpic.w*map_mod[Pt.m+3]);
		do_vpic();
	}
  }
}

void del_sl(unsigned int nom)
{
	int i;
	mfree(p->sl[nom].map);
	if(nom<p->cs-1)
	{
		for(i=nom; i<p->cs; i++) p->sl[i]=p->sl[i+1];
		//mfree(p->sl[p->cs-1].map);
	}
	if(p->ns>=nom) p->ns--;
	p->cs--;
}

void new_sl(unsigned int nom, char *slname)
{
	//if(p->cs==8) MsgBoxError(1, (int)"Много\nвредно\n:)");
	//else
	{
		int i;
		if(nom<p->cs)
		for(i=p->cs; i>nom; i--) p->sl[i]=p->sl[i-1];
		p->sl[nom].v=1;
		p->sl[nom].w=p->w;
		p->sl[nom].h=p->h;
		memcpy( p->sl[nom].nm,  slname, 16);
		p->cs++;
		p->ns=nom;
		p->sl[nom].map=malloc(p->sz*4);
		zeromem(p->sl[nom].map, p->sz*4);
	}
}

void cr2()
{
	if(vpic.bitmap) mfree(vpic.bitmap);
	vpic.w=p->w*(p->z+1);
	vpic.h=p->h*(p->z+1);
	if(vpic.w>=PCPS.x2-PCPS.x-2) BigPx=1;
	if(vpic.h>=PCPS.y2-PCPS.y-2) BigPy=1;
	vpic.bpnum=map_mod[Pt.m];
	vpic.bitmap=malloc(vpic.h*vpic.w*map_mod[Pt.m+3]);
	do_prf();
	do_vpic();
}

void crpic()
{
	unsigned int i;
	docols(0);
	if(!open)
	{
		//if(!start)
		//{
			//for(i=0; i<p->cs; i++) mfree(p->sl[i].map);
			//if(prf) mfree(prf);
		//}
		p->sz=p->w*p->h;
		p->ns=1;
		p->sl[0].w=p->sl[1].w=p->w;
		p->sl[0].h=p->sl[1].h=p->h;
		p->sl[0].v=p->sl[1].v=1;
		p->sl[0].x=p->sl[0].y=p->sl[1].x=p->sl[1].y=0;
		sprintf( p->sl[0].nm, perc_s, "FON" );
		sprintf( p->sl[1].nm, "SLOY 1" );
		p->sl[0].map=malloc(p->sz*4);
		p->sl[1].map=malloc(p->sz*4);
		zeromem(p->sl[1].map, p->sz*4);
		for(i=0; i<p->sz; i++)
		{
			memcpy(p->sl[0].map+i*4, &COL[2].c32, 4);
		}
		p->cs=2;
	}
	start=0;
	p->x=(PCPS.x2+PCPS.x)/2-p->w/2;
	p->y=(PCPS.y2+PCPS.y)/2-p->h/2;
	p->cur.x=p->w/2;
	p->cur.y=p->h/2;
	p->z=0;
	cr2();
	if(open) Preview();
	open=0;
}








// *********************** Предпросмотр картинки ******************** //


void pvw_Redraw(PREVIEW_GUI *data)
{
	if (data->gui.state==2)
	{
		DrawRectangle(0,YDP, SCR.sw,SCR.sh, 0,black,black);
		//DrwImg((IMGHDR *)&prf, data->x, data->y, white, black);
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
				//if(p->z) dozoom();
				return 1;
			case DOWN_BUTTON:
			case '8':
				data->y-=st;
			 break;
			case UP_BUTTON:
			case '2':
				data->y+=st;
			 break;
			case RIGHT_BUTTON:
			case '6':
				data->x-=st;
			 break;
			case LEFT_BUTTON:
			case '4':
				data->x+=st;
			 break;
			case '0':
				//dozoom();
				//data->x=SCR.sw/2-vpic.w/2;
				//data->y=SCR.sh/2-vpic.h/2;
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
  pvw_gui->x=SCR.sw/2-p->w/2;
  pvw_gui->y=SCR.sh/2-p->h/2;
  return(CreateGUI(pvw_gui));
}
