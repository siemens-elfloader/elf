#ifndef _RECT_PATCHER_H_
  #define _RECT_PATCHER_H_

unsigned short scr_w, scr_h, sf_h, mswsbody[256];
WSHDR *ws, *ews, *msws, mshws;

char perc_t[]="%t",
	perc_tp[]="%t:",
	ppp[]="...",
	ppp2[]="\n<...>",
	pcd[]="(%d)",
	nth[]="",
//  d_png[]="0:\\system\\sms\\d.png",
//  i_png[]="0:\\system\\sms\\i.png",
//  m_png[]="0:\\system\\sms\\m.png",
//  n_png[]="0:\\system\\sms\\n.png",
//  o_png[]="0:\\system\\sms\\o.png",
	// §è§Ó§Ö§ä§Ñ §Õ§Ý§ñ §å§Õ§à§Ò§ã§ä§Ó§Ñ:
	yellow[]={0xff,0xff,0,100},
	white[]={0xff,0xff,0xff,100},
	black[]={0,0,0,100},
	red[]={0xff,0,0,100},
	green[]={0,0xff,0,100},
	blue[]={0,0,0xff,100};


#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

#pragma inline
void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+YDISP-1;
}

#pragma inline
void patch_input(const INPUTDIA_DESC* inp)
{
  ((INPUTDIA_DESC*)inp)->rc.x=0;
  ((INPUTDIA_DESC*)inp)->rc.y=HeaderH()+1+YDISP;
  ((INPUTDIA_DESC*)inp)->rc.x2=ScreenW()-1;
  ((INPUTDIA_DESC*)inp)->rc.y2=ScreenH()-SoftkeyH()-1;
}

#endif
