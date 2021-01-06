#include "../inc/swilib.h"
#include "view.h"
#include "display_utils.h"
#include "siemens_unicode.h"
#include "string_works.h"
#include "rect_patcher.h"
#include "main.h"
#include "file_works.h"
#include "lang.h"

extern int maincsm_id;

int GetFontHeight(int font, int atribute)
{
  int height=GetFontYSIZE(font);
  if (atribute&TEXT_INVERT)   height+=1;
  if (atribute&TEXT_UNDERLINE)   height+=1;
  if (atribute&TEXT_OUTLINE)  height+=2;
  return height;
}

unsigned int SearchNextDisplayLine(VIEWDATA *vd, LINECACHE *p, unsigned int *max_h)
{
  int left=ScreenW();
  int c,h,cw,f=0;
  unsigned int pos=p->pos;
  p->centerAtAll=0;
  vd->lastLineHeight=0;
  while(pos<vd->rawtext_size)
  {
    c=vd->rawtext[pos++];
    if ((c&0xFF00)==0xE100)
    {
      h=GetImgHeight(GetPicNByUnicodeSymbol(c));
    }
    else
    {
      h=GetFontHeight(p->bold?FONT_SMALL_BOLD:FONT_SMALL,p->underline?TEXT_UNDERLINE:0+p->ref?TEXT_INVERT:0);
    }
    switch(c)
    {
    case 0x0A:
      f=1;
      h=0;
      break;
    case UTF16_ENA_CENTER:
      p->center=1;
      continue;
    case UTF16_DIS_CENTER:
      p->center=0;
      continue;
    case UTF16_ALIGN_RIGHT:
      p->right=1;
      continue;
    case UTF16_ALIGN_LEFT:
      p->right=0;
      continue;
    case UTF16_DIS_INVERT:
      p->ref=0;
      continue;
    case UTF16_ENA_INVERT:
      p->ref=1;
      continue;
    case UTF16_DIS_UNDERLINE:
      p->underline=0;
      continue;
    case UTF16_ENA_UNDERLINE:
      p->underline=1;
      continue;
    case UTF16_FONT_SMALL:
      p->bold=0;
      continue;
    case UTF16_FONT_SMALL_BOLD:
      p->bold=1;
      continue;
    case UTF16_INK_RGBA:
      if (pos>(vd->rawtext_size-2)) goto LERR;
      p->ink1=vd->rawtext[pos++];
      p->ink2=vd->rawtext[pos++];
      continue;
    case UTF16_PAPER_RGBA:
      if (pos>(vd->rawtext_size-2)) goto LERR;
      p->paper1=vd->rawtext[pos++];
      p->paper2=vd->rawtext[pos++];
      continue;
    case UTF16_INK_INDEX:
    case UTF16_PAPER_INDEX:
      pos++;
      if (pos>=vd->rawtext_size) goto LERR;
      continue;
    }
    // ���������� ��������� �����
    cw=GetSymbolWidth(c,p->bold?FONT_SMALL_BOLD:FONT_SMALL);
    left-=cw;
    if (left<0)
    {
      int b=1;
      int cw=0;
      if (p->ref)
      {
        while (1)
        {
          if (vd->rawtext[pos-b]==UTF16_ENA_INVERT) break;
          if (vd->rawtext[pos-b]==UTF16_NEWLINE)
          {
            b++;
            break;
          }
          if (cw>=ScreenW()/2)
          {
            b=1;
            break;
          }
          cw+=GetSymbolWidth(vd->rawtext[pos-b],p->bold?FONT_SMALL_BOLD:FONT_SMALL);
          b++;
        }
      }
      else
      {
        ;
      }
      return pos-b;
    }
    
    if (cw>=ScreenW()/2||h>GetFontHeight(FONT_SMALL,0)*2) // �������� ��������
    {
      if (left+cw<ScreenW()) // image is last character
      {
        //if (c!=vd->WCHAR_LIST_FORM) // preserve dropdown list centring
        p->centerAtAll=1;
        if (vd->rawtext[pos-1]==UTF16_ENA_INVERT)
        {
          return pos-2;
        }
        else
        {
          return pos-1;
        }
      }
    }
    if (max_h)
    {
      if (h>*max_h)
      {
        *max_h=vd->lastLineHeight=h;
      }
    }
    if (cw>=ScreenW()/2||h>GetFontHeight(FONT_SMALL,0)*2) // �������� ��������
    {
      if (left+cw==ScreenW()) // image is first character
      {
        if (pos>(vd->rawtext_size-1)) goto LERR;
        //if (c!=vd->WCHAR_LIST_FORM) // preserve dropdown list centring
        p->centerAtAll=1;
        if (vd->rawtext[pos+1]==UTF16_DIS_INVERT)
        {
          p->ref=0;
          return pos+1;
        }
        else
        {
          return pos;
        }
      }
    }
    if (f)
    {
      return pos;
    }
  }
LERR:
  return(vd->rawtext_size);
}

#define LINESCACHECHUNK 256

static void AddLineToCache(VIEWDATA *vd, LINECACHE *p)
{
  if ((vd->lines_cache_size%LINESCACHECHUNK)==0)
  {
    //����� �� ����� �����, ������������ ��� �����
    vd->lines_cache=realloc(vd->lines_cache,(vd->lines_cache_size+LINESCACHECHUNK)*sizeof(LINECACHE));
  }
  memcpy(vd->lines_cache+(vd->lines_cache_size++),p,sizeof(LINECACHE));
}

int LineDown(VIEWDATA *vd)
{
  if (vd->view_line+1<vd->lines_cache_size)
  {
    vd->view_line++;
  }
  else
  {
    LINECACHE lc;
    unsigned int h;
    unsigned int pos;
    if (vd->view_line>=vd->lines_cache_size)
    {
      lc.ink1=0x0000;
      lc.ink2=0x0064;
      lc.paper1=0xFFFF;
      lc.paper2=0xFF64;
      lc.pixheight=0;
      lc.bold=0;
      lc.underline=0;
      lc.ref=0;
      lc.pos=0;
      lc.center=0;
      lc.right=0;
      AddLineToCache(vd,&lc);
    }
    else
    {
      memcpy(&lc,vd->lines_cache+vd->view_line,sizeof(lc));
    }
    h=0;
    pos=SearchNextDisplayLine(vd,&lc,&h);
    (vd->lines_cache+vd->view_line)->pixheight=h;
    if (pos>=vd->rawtext_size) return 0;
    lc.pos=pos;
    vd->view_line++;
    if (vd->view_line>=vd->lines_cache_size)
    {
      AddLineToCache(vd,&lc);
    }
  }
  return 1;
}

int LineUp(VIEWDATA *vd)
{
  int vl=vd->view_line;
  if (vl)
  {
    vl--;
    vd->view_line=vl;
    return 1;
  }
  else
    return 0;
}

void scrollDown(VIEWDATA *vd, int amount)
{
  if (!RenderPage(vd,0)) return;
  
  vd->pixdisp+=amount;
  unsigned int cl_h;
L1:
  cl_h=vd->lines_cache[vd->view_line].pixheight;
  if (vd->pixdisp>cl_h)
  {
    vd->pixdisp-=cl_h;
    unsigned int pd=vd->pixdisp;
    LineDown(vd);
    vd->pixdisp=0;
    if (!RenderPage(vd,0))
    {
      while(LineDown(vd)) ;
      vd->pixdisp=0;
      scrollUp(vd,ScreenH()-1-vd->lastLineHeight);
      return;
    }
    vd->pixdisp=pd;
    goto L1;
  }
  else
  {
    if (!RenderPage(vd,0))
    {
      while(LineDown(vd)) ;
      vd->pixdisp=0;
      scrollUp(vd,ScreenH()-1-vd->lastLineHeight);
    }
  }
}

void scrollUp(VIEWDATA *vd, int amount)
{
  while (vd->pixdisp-amount<0)
  {
    if (!LineUp(vd))
    {
      vd->pixdisp=0;
      return;
    }
    amount-=vd->lines_cache[vd->view_line].pixheight;
  }
  vd->pixdisp-=amount;
}

#define MAX_COLORS_IN_LINE 32
typedef struct {
  char color[4];
  int start_x;
  int end_x;
} COLOR_RC;

void renderForm(VIEWDATA *vd, REFCACHE *rf, int x, int y)
{
  if (rf->tag=='x'||rf->tag=='p')
  {
    // calc pos
    int d=(GetImgHeight(GetPicNByUnicodeSymbol(vd->WCHAR_TEXT_FORM))-GetFontHeight(FONT_SMALL,0))/2;
    // count lenght
    int w=GetImgWidth(GetPicNByUnicodeSymbol(vd->WCHAR_TEXT_FORM))-(d*2);
    WSHDR *ws2=AllocWS(((WSHDR *)rf->data)->wsbody[0]);
    for (;ws2->wsbody[0]<((WSHDR *)rf->data)->wsbody[0];)
    {
      w-=GetSymbolWidth(((WSHDR *)rf->data)->wsbody[ws2->wsbody[0]+1],FONT_SMALL);
      if (w<=0)
        break;
      ws2->wsbody[0]++;
      if (rf->tag=='p')
        ws2->wsbody[ws2->wsbody[0]]='*';
      else
        ws2->wsbody[ws2->wsbody[0]]=((WSHDR *)rf->data)->wsbody[ws2->wsbody[0]];
    }
    DrawString(ws2,x+d,y+d,ScreenW(),ScreenH(),
      FONT_SMALL,TEXT_NOFORMAT,
      GetPaletteAdrByColorIndex(1),
      GetPaletteAdrByColorIndex(23));
    FreeWS(ws2);
  }
  if (rf->tag=='s'&&rf->value!=_NOREF)
  {
    // calc pos
    int d=(GetImgHeight(GetPicNByUnicodeSymbol(vd->WCHAR_LIST_FORM))-GetFontHeight(FONT_SMALL,0))/2;
    // count lenght
    int w=GetImgWidth(GetPicNByUnicodeSymbol(vd->WCHAR_LIST_FORM))-(d*2)-GetImgHeight(GetPicNByUnicodeSymbol(vd->WCHAR_LIST_FORM));
    int count=_rshort2(vd->oms+rf->value);
    char *c=extract_omstr(vd,rf->value);
    WSHDR *ws2=AllocWS(count);
    oms2ws(ws2,c,count);
    count=ws2->wsbody[0];
    ws2->wsbody[0]=0;
    for (;ws2->wsbody[0]<count;)
    {
      w-=GetSymbolWidth(ws2->wsbody[ws2->wsbody[0]+1],FONT_SMALL);
      if (w<=0)
        break;
      ws2->wsbody[0]++;
    }
    DrawString(ws2,x+d,y+d,ScreenW(),ScreenH(),
      FONT_SMALL,TEXT_NOFORMAT,
      GetPaletteAdrByColorIndex(1),
      GetPaletteAdrByColorIndex(23));
    FreeWS(ws2);
    mfree(c);
  }
}

// ���������� 0, ���� ����� ����� ��������
int RenderPage(VIEWDATA *vd, int do_draw)
{
  int scr_w=ScreenW()-1;
  int scr_h=ScreenH()-1;
  int sc;
  int dc;
  WSHDR *ws=vd->ws;
  LINECACHE *lc;
  unsigned int vl;
  int ypos=-vd->pixdisp;
  unsigned int store_line=vl=vd->view_line;
  unsigned int len;
  unsigned int y2;
  
  char def_ink[4];
  COLOR_RC rc[MAX_COLORS_IN_LINE];
  int cur_rc;
  int ws_width;
  
  int c;
  int ena_ref=0;
  
  int result=1;

  unsigned int flag=0;
  
  vd->pos_first_ref=0xFFFFFFFF;
  vd->pos_last_ref=0xFFFFFFFF;
  vd->pos_prev_ref=0xFFFFFFFF;
  vd->pos_next_ref=0xFFFFFFFF;
  
  int dfh=GetFontHeight(FONT_SMALL,0)*2; //double font height
  
  int rnd_x;
  REFCACHE *rnd_rf;
  
//  RECT refrc[32];
//  int refrc_count=0;
//  int refrc_dispd=0;
  
  int lcheck=0;  // last line checker
  
  while(ypos<=scr_h)
  {
    if (!lcheck) lcheck=!LineDown(vd);
    else lcheck++;
    if (lcheck<=1&&vd->lines_cache_size>1)
    {
      if (lcheck) vl--;
      lc=vd->lines_cache+vl;
      dc=0;
      ws_width=0;
      cur_rc=1;
      rnd_rf=NULL;
      
      rc[0].start_x=0;
      rc[0].end_x=scr_w;
      rc[0].color[0]=lc->paper1>>8;
      rc[0].color[1]=lc->paper1;
      rc[0].color[2]=lc->paper2>>8;
      rc[0].color[3]=lc->paper2;
      
      if (lcheck)
      {
        sc=(lc[1]).pos;
        len=vd->rawtext_size-sc;
      }
      else
      {
        sc=lc->pos;
        len=(lc[1]).pos-sc;
      }
      
      if (ena_ref)
      {
        ws->wsbody[++dc]=UTF16_ENA_INVERT; // ���� ��� ������� �� ���������� ������
//        refrc[refrc_count].x=0;
//        refrc[refrc_count].y=ypos;
//        refrc[refrc_count].y2=lc->pixheight+ypos;
//        refrc_count++;
      }
      
      while(len>0&&(dc<32000))
      {
        c=vd->rawtext[sc];
        
        if (c==UTF16_ENA_INVERT)
        {
          if ((lc->pixheight<dfh)?(ypos<0):(ypos+lc->pixheight-dfh<0))
            goto L1;
          if ((lc->pixheight<dfh)?(ypos+lc->pixheight>=scr_h):(ypos+dfh>=scr_h))
            goto L1;
          if (vd->pos_cur_ref==sc)
          {
            flag=1;
            ena_ref=1;
//            refrc[0].x=ws_width;
//            refrc[0].y=ypos;
//            refrc[0].y2=lc->pixheight+ypos;
//            refrc_count++;
          }
          else
          {
            if (vd->pos_first_ref==0xFFFFFFFF) vd->pos_first_ref=sc;
            if (flag==0) vd->pos_prev_ref=sc;
            if (flag==1)
            {
              vd->pos_next_ref=sc;
              flag=2;
            }
            vd->pos_last_ref=sc;
            if (ena_ref) ena_ref++;
            goto L1;
          }
//          goto L1;
        }
        else
        if (c==UTF16_DIS_INVERT)
        {
          if (ena_ref!=1)
          {
            if (ena_ref) ena_ref--;
            goto L1;
          }
//          refrc[refrc_count-1].x2=ws_width-refrc[refrc_count-1].x;
          ena_ref=0;
//          goto L1;
        }
        else
        if (c==UTF16_PAPER_RGBA)
        {
          if (cur_rc<MAX_COLORS_IN_LINE)
          {
            COLOR_RC *prev=rc+cur_rc-1;
            rc[cur_rc].color[0]=vd->rawtext[sc+1]>>8;
            rc[cur_rc].color[1]=vd->rawtext[sc+1];
            rc[cur_rc].color[2]=vd->rawtext[sc+2]>>8;
            rc[cur_rc].color[3]=vd->rawtext[sc+2];
            if (memcmp((void *)rc[cur_rc].color,(void *)prev->color,4))  // ������ ���� ���� �� ����� ����������� (������� �������� �� ��������� ;))
            {
              prev->end_x=ws_width-1;
              rc[cur_rc].start_x=ws_width;
              rc[cur_rc].end_x=scr_w;
              cur_rc++;
            }
          }
        } else
        if (c==UTF16_ALIGN_LEFT||c==UTF16_ALIGN_RIGHT||c==UTF16_ENA_CENTER|| \
            c==UTF16_DIS_CENTER||c==UTF16_NEWLINE)
        {
          goto L1;
        } else
        if ((c&0xFF00)==0xE100)
        {
          if (c==vd->WCHAR_TEXT_FORM||c==vd->WCHAR_LIST_FORM)
          {
            rnd_rf=FindReferenceByBegin(vd,sc-1);
            rnd_x=ws_width;
          }
        }
        
        ws->wsbody[++dc]=c;
        ws_width+=GetSymbolWidth(c,lc->bold?FONT_SMALL_BOLD:FONT_SMALL);
        if ((c==UTF16_PAPER_RGBA)||(c==UTF16_INK_RGBA))
        {
          len--;
          ws->wsbody[++dc]=vd->rawtext[++sc];
          len--;
          ws->wsbody[++dc]=vd->rawtext[++sc];
        }
        L1:
        sc++;
        len--;
      }
      //ws->wsbody[++dc]='/';
      ws->wsbody[0]=dc;
      y2=lc->pixheight+ypos;
      
      if (do_draw)
      {
        int x=0;
        if (lc[1].right) x=scr_w-ws_width;
        if (lc[1].center||lc[1].centerAtAll) x=(scr_w-ws_width)/2;
//        if (ena_ref) refrc[refrc_count-1].x2=ws_width;
//        if (refrc_count>refrc_dispd)
//        {
//          refrc[refrc_dispd].x+=x;
//          refrc_dispd++;
//        }
        def_ink[0]=lc->ink1>>8;
        def_ink[1]=lc->ink1;
        def_ink[2]=lc->ink2>>8;
        def_ink[3]=lc->ink2;
        for (int i=0; i!=cur_rc; i++)
        {
          DrawRectangle(rc[i].start_x,ypos,rc[i].end_x,y2,
		                    RECT_FILL_WITH_PEN,rc[i].color,rc[i].color);
        }
        if (lcheck) y2=ypos+vd->lastLineHeight;
        
	      DrawString(ws,x,ypos,scr_w,y2,
		               lc->bold?FONT_SMALL_BOLD:FONT_SMALL,
                   TEXT_NOFORMAT+(lc->underline?TEXT_UNDERLINE:0),
		               def_ink,GetPaletteAdrByColorIndex(23));
        
        if (rnd_rf) renderForm(vd,rnd_rf,rnd_x+x,ypos);
      }
      if (y2>=scr_h||lcheck)
      {
        int b=(vd->lines_cache[store_line].pos*1000)/vd->rawtext_size*scr_h/1000-2;
        int e=(lc->pos*1000)/vd->rawtext_size*scr_h/1000+2;
        for (int i=b;i<=e;i++)
        {
          SetPixel(scr_w,i,GetPaletteAdrByColorIndex(2));
          SetPixel(scr_w-1,i,GetPaletteAdrByColorIndex(2));
#ifdef ELKA
          SetPixel(scr_w-2,i,GetPaletteAdrByColorIndex(2));
#endif
        }
//        if (refrc_count)
//        {
//          for (int i=0;i<refrc_count;i++)
//          {
//            DrawRectangle(refrc->x,refrc->y,refrc->x+refrc->x2,refrc->y2,0,
//              GetPaletteAdrByColorIndex(2),
//              GetPaletteAdrByColorIndex(23));
//          }
//        }
//        if (ballet_fexists("$ballet\\debug.txt"))
//        {
//          WSHDR *ws;
//          ws=AllocWS(128);
////          for (int i=store_line;i<=vl;i++)
////          {
////            wsprintf(ws,"%u: %u %c%c h:%u",i,vd->lines_cache[i].pos,vd->lines_cache[i].center?'+':'-',vd->lines_cache[i].right?'>':'<',vd->lines_cache[i].pixheight);
////            DrawString(ws,3,(1+i-store_line)*14,scr_w,scr_h,FONT_SMALL,TEXT_NOFORMAT,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
////          }
//          {
//            wsprintf(ws,"%i",ws_width);
//            DrawString(ws,3,14,scr_w,scr_h,FONT_SMALL,TEXT_NOFORMAT,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(21));
//            wsprintf(ws,"%u %u",vd->pos_first_ref,vd->pos_last_ref);
//            DrawString(ws,3,14,scr_w,scr_h,FONT_SMALL,TEXT_NOFORMAT,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(21));
//            wsprintf(ws,"%u %u",vd->pos_prev_ref,vd->pos_next_ref);
//            DrawString(ws,3,26,scr_w,scr_h,FONT_SMALL,TEXT_NOFORMAT,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(21));
//            wsprintf(ws,"%u %c",vd->pos_cur_ref,FindReference(vd,vd->pos_cur_ref)?FindReference(vd,vd->pos_cur_ref)->tag:'0');
//            DrawString(ws,3,38,scr_w,scr_h,FONT_SMALL,TEXT_NOFORMAT,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(21));
//            wsprintf(ws,"%i",vd->pixdisp);
//            DrawString(ws,3,50,scr_w,scr_h,FONT_SMALL,TEXT_NOFORMAT,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(21));
////            ws->wsbody[0]=10;
////            memcpy(&(ws->wsbody[1]),(vd->rawtext+store_pos),10);
////            DrawString(ws,3,50,scr_w,scr_h,FONT_SMALL,TEXT_NOFORMAT,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(21));
//          }
//          FreeWS(ws);
//        }
      }
      ypos=y2;
      vl++;
    }
    else
    {
      result=0;
      break;
    }
  }
  if (lcheck) result=0;
  if (flag==0) vd->pos_cur_ref=0xFFFFFFFF;
  vd->view_line=store_line;
  return(result);
}

REFCACHE *FindReferenceByBegin(VIEWDATA *vd, unsigned int pos)
{
  int i=vd->ref_cache_size;
  REFCACHE *rf;
  if (!i) return NULL;
  rf=vd->ref_cache;
  do
  {
    if (rf->begin==pos) return rf;
    rf++;
  }
  while(--i);
  return NULL;
}

REFCACHE *FindReferenceFirst(VIEWDATA *vd, unsigned int pos)
{
  while (pos<vd->rawtext_size&&vd->rawtext[pos]!=UTF16_ENA_INVERT)
    pos++;
  return FindReferenceByBegin(vd,pos);
}

REFCACHE *FindReference(VIEWDATA *vd, unsigned int pos)
{
  REFCACHE *rf=FindReferenceByBegin(vd,pos);
  if (rf!=NULL) return rf;
  else
  {
    int i=vd->ref_cache_size;
    if (!i) return NULL;
    rf=vd->ref_cache;
    do
    {
      if ((rf->begin<=pos)&&(pos<rf->end)) return rf;
      rf++;
    }
    while(--i);
  }
  return NULL;
}

int FindReferenceById(VIEWDATA *vd, unsigned int id, int i) // ������� index'� ���� ref'�� � �������� id
{
  unsigned int sz=*(vd->oms+id);
  sz<<=8;
  sz|=*(vd->oms+id+1);
  while(i<vd->ref_cache_size)
  {
    if (!omstrcmp(vd,(vd->ref_cache+i)->id,id)) return i;
    i++;
  }
  return -1;
}

// TEMPLATES MENU
GUI *paste_gui;

int templ_menu_onkey(void *gui, GUI_MSG *msg)
{
  if (msg->keys==0x3D || msg->keys==0x18)
  {
    // select
    int item=GetCurMenuItem(gui);
    EDITCONTROL ec;
    ExtractEditControl(paste_gui,1,&ec);
    char fname[256];
    int file;
    unsigned int ul;
    getSymbolicPath(fname,"$ballet\\templates.txt");
    if ((file=fopen(fname,A_ReadWrite,P_READ+P_WRITE,&ul))!=-1)
    {
      int num=0;
      unsigned int buf_size = lseek(file, 0, S_END, &ul, &ul);
      lseek(file, 0, S_SET, &ul, &ul);
      char *buffer = malloc(buf_size);
      fread(file, buffer, buf_size, &ul);
      fclose(file, &ul);
      int start=0,len=0;
      for (int i=0;i<=buf_size;i++)
        if (buffer[i]==0x0A||buffer[i]==0x0D||i==buf_size)
        {
          if (num==item) len=i-start;
          num++;
          if (num==item) start=i+1;
        }
      char *c=malloc(len+1);
      memcpy(c,buffer+start,len);
      c[len]=NULL;
      ascii2ws(ec.pWS,c);
      StoreEditControl(paste_gui,1,&ec);
      mfree(buffer);
      mfree(c);
    }
    return 0xFF;
  }
  return (0);
}

void templ_menu_ghook(void *gui, int cmd)
{
  if (cmd==3) // free
  {
    ;
  }
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}
void templ_menu_iconhndl(void *gui, int cur_item, void *user_pointer)
{
  WSHDR *ws;
  void *item=AllocMenuItem(gui);
  char fname[256];
  int file;
  unsigned int ul;
  getSymbolicPath(fname,"$ballet\\templates.txt");
  if ((file=fopen(fname,A_ReadWrite,P_READ+P_WRITE,&ul))!=-1)
  {
    int num=0;
    unsigned int buf_size = lseek(file, 0, S_END, &ul, &ul);
    lseek(file, 0, S_SET, &ul, &ul);
    char *buffer = malloc(buf_size);
    fread(file, buffer, buf_size, &ul);
    fclose(file, &ul);
    int start=0,len=0;
    for (int i=0;i<=buf_size;i++)
      if (buffer[i]==0x0A||buffer[i]==0x0D||i==buf_size)
      {
        if (num==cur_item) len=i-start;
        num++;
        if (num==cur_item) start=i+1;
      }
    ws=AllocMenuWS(gui,len);
    str_2ws(ws,buffer+start,len);
    mfree(buffer);
  }
  else
  {
    ws=AllocMenuWS(gui,10);
    wsprintf(ws, "������");
  }
  SetMenuItemText(gui, item, ws, cur_item);
}

int templ_softkeys[]={0,1,2};
SOFTKEY_DESC templ_sk[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Close"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB templ_skt=
{
  templ_sk,0
};

HEADER_DESC templ_HDR={0,0,0,0,NULL,(int)"�����",LGP_NULL};

MENU_DESC templ_STRUCT=
{
  8,templ_menu_onkey,templ_menu_ghook,NULL,
  templ_softkeys,
  &templ_skt,
  0x10,
  templ_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

void createTemplatesMenu()
{
  // get amount of lines
  char fname[256];
  int file;
  unsigned int ul;
  getSymbolicPath(fname,"$ballet\\templates.txt");
  if ((file=fopen(fname,A_ReadWrite,P_READ+P_WRITE,&ul))!=-1)
  {
    int num=1;
    unsigned int buf_size=lseek(file, 0, S_END, &ul, &ul);
    lseek(file, 0, S_SET, &ul, &ul);
    char *buffer=malloc(buf_size);
    fread(file, buffer, buf_size, &ul);
    fclose(file, &ul);
    if ((buffer[buf_size-1]==0x0A||buffer[buf_size-1]==0x0D)) buf_size--;
    for (int i=0;i<buf_size;i++)
    {
      if ((buffer[i]==0x0A||buffer[i]==0x0D))
      {
        num++;
      }
    }
    patch_header(&templ_HDR);
    mfree(buffer);
    if (num>0)
    {
      CreateMenu(0,0,&templ_STRUCT,&templ_HDR,0,num,0,0);
    }
  }
}

// EDIT BOX
REFCACHE *cur_ref;
VIEWDATA *cur_vd;

extern char *goto_url;
extern char *from_url;
extern char *goto_params;

char *collectItemsParams(VIEWDATA *vd, REFCACHE *rf);

SOFTKEY_DESC input_box_menu_sk[]=
{
  {0x0018,0x0000,(int)"Ok"},
  {0x0001,0x0000,(int)"Cancel"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB input_box_menu_skt=
{
  input_box_menu_sk,0
};

HEADER_DESC input_box_hdr={0,0,0,0,NULL,(int)"Enter:",LGP_NULL};

static void input_box_ghook(GUI *data, int cmd)
{
  SOFTKEY_DESC sk={0x0FFF,0x0000,(int)lgpData[LGP_Ok]};
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
  if (cmd==7)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
  }
}

static void input_box_locret(void){}

void input_box_onkey_options(USR_MENU_ITEM *item)
{
  if (item->type==0)
  {
    switch(item->cur_item)
    {
    case 0:
      ascii2ws(item->ws,lgpData[LGP_Templates]);
      break;
    }
  }
  if (item->type==1)
  {
    switch(item->cur_item)
    {
    case 0:
      createTemplatesMenu();
      break;
    }
  }
}

static int input_box_onkey(GUI *data, GUI_MSG *msg)
{
  EDITCONTROL ec;
  if (msg->gbsmsg->msg==KEY_DOWN&&msg->gbsmsg->submess==ENTER_BUTTON)
	{
    paste_gui=data;
    EDIT_OpenOptionMenuWithUserItems(data,input_box_onkey_options,0,1);
    return (-1);
	}
  if (msg->keys==0xFFF)
  {
    // set value
    ExtractEditControl(data,1,&ec);
    FreeWS(((WSHDR *)cur_ref->data));
    cur_ref->data=(void *)AllocWS(ec.pWS->wsbody[0]);
    wstrcpy(((WSHDR *)cur_ref->data),ec.pWS);
    if (!cur_ref->no_upload)
    {
      goto_url=malloc(strlen(cur_vd->pageurl)+1);
      strcpy(goto_url,cur_vd->pageurl);
      from_url=malloc(strlen(cur_vd->pageurl)+1);
      strcpy(from_url,cur_vd->pageurl);
      goto_params=collectItemsParams(cur_vd,cur_ref);
    }
    else
    {
      MAIN_CSM *main_csm;
      if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
      {
        main_csm->sel_bmk=0;
      }
    }
    cur_ref=NULL;
    cur_vd=NULL;
    return (0xFF);
  }
  return (0);
}

static const INPUTDIA_DESC input_box_desc =
{
  1,
  input_box_onkey,
  input_box_ghook,
  (void *)input_box_locret,
  0,
  &input_box_menu_skt,
  {0,0,0,0},
  FONT_SMALL,
  100,
  101,
  0,
  //  0x00000001 - ��������� �� ������� ����
  //  0x00000002 - ��������� �� ������
  //  0x00000004 - �������� ���������
  //  0x00000008 - UnderLine
  //  0x00000020 - �� ���������� �����
  //  0x00000200 - bold
  0,
  //  0x00000002 - ReadOnly
  //  0x00000004 - �� ��������� ������
  //  0x40000000 - �������� ������� ����-������
  0x40000000
};

int CreateInputBox(VIEWDATA *vd, REFCACHE *rf)
{
  cur_ref=rf;
  cur_vd=vd;
  
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  
  eq=AllocEQueue(ma,mfree_adr());
  WSHDR *ews=AllocWS(16384);
  
  wstrcpy(ews,((WSHDR *)rf->data));
  
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL|(rf->tag=='p'?ECF_PASSW:NULL),ews,16384);
  AddEditControlToEditQend(eq,&ec,ma);

  FreeWS(ews);
  patch_header(&input_box_hdr);
  patch_input(&input_box_desc);
  return CreateInputTextDialog(&input_box_desc,&input_box_hdr,eq,1,0);
}

// TEXT VIEW
SOFTKEY_DESC txtview_menu_sk[]=
{
  {0x0018,0x0000,(int)"Ok"},
  {0x0001,0x0000,(int)"Cancel"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB txtview_menu_skt=
{
  txtview_menu_sk,0
};

HEADER_DESC txtview_hdr={0,0,0,0,NULL,(int)"Text :",LGP_NULL};

static void txtview_ghook(GUI *data, int cmd)
{
  SOFTKEY_DESC sk={0x0FFF,0x0000,(int)lgpData[LGP_Ok]};
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
  if (cmd==7)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
  }
}

static void txtview_locret(void){}

static int txtview_onkey(GUI *data, GUI_MSG *msg)
{
  if (msg->keys==0xFFF)
  {
    return (0xFF);
  }
  return (0);
}

static const INPUTDIA_DESC txtview_desc =
{
  1,
  txtview_onkey,
  txtview_ghook,
  (void *)txtview_locret,
  0,
  &txtview_menu_skt,
  {0,0,0,0},
  FONT_SMALL,
  100,
  101,
  0,
  0,
  0x40000000
};

void createTextView(WSHDR *ws)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  eq=AllocEQueue(ma,mfree_adr());
  if (!wstrlen(ws))
  {
    FreeWS(ws);
    return;
  }
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws,512);
  AddEditControlToEditQend(eq,&ec,ma);
  FreeWS(ws);
  patch_header(&txtview_hdr);
  patch_input(&txtview_desc);
  CreateInputTextDialog(&txtview_desc,&txtview_hdr,eq,1,0);
}

// SELECTION MENU
typedef struct
{
  void *next;
  char name[256];
  unsigned short value;
  unsigned short id2;
}SEL_STRUCT;

int sel_menu_onkey(void *gui, GUI_MSG *msg)
{
  SEL_STRUCT *ustop=MenuGetUserPointer(gui);
  if (msg->keys==0x3D || msg->keys==0x18)
  {
    int i=GetCurMenuItem(gui);
    int n=0;
    for (; n!=i; n++) ustop=ustop->next;
    if (ustop)
    {
      if (cur_ref->multiselect)
      {
        if(((char*)cur_ref->data)[n])
          ((char*)cur_ref->data)[n]=0;
        else
          ((char*)cur_ref->data)[n]=1;
        SetMenuItemIcon(gui,i,((char*)cur_ref->data)[n]);
        RefreshGUI();
      }
      else
      {
        cur_ref->value=ustop->value;
        cur_ref->id2=ustop->id2;
        if (!cur_ref->no_upload)
        {
          goto_url=malloc(strlen(cur_vd->pageurl)+1);
          strcpy(goto_url,cur_vd->pageurl);
          from_url=malloc(strlen(cur_vd->pageurl)+1);
          strcpy(from_url,cur_vd->pageurl);
          goto_params=collectItemsParams(cur_vd,cur_ref);
        }
        else
        {
          MAIN_CSM *main_csm;
          if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
          {
            main_csm->sel_bmk=0;
          }
        }
        cur_ref=NULL;
        cur_vd=NULL;
        return 0xFF;
      }
    }
  }
  return (0);
}

void sel_menu_ghook(void *gui, int cmd)
{
  SEL_STRUCT *ustop=MenuGetUserPointer(gui);
  if (cmd==3)
  {
    while(ustop)
    {
      SEL_STRUCT *us=ustop;
      ustop=ustop->next;
      mfree(us);
    }    
  }
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

static int icon_array[2];

void sel_menu_iconhndl(void *gui, int cur_item, void *user_pointer)
{
  SEL_STRUCT *ustop=user_pointer;
  WSHDR *ws;
  int len;
  int n=0;
  for (; n!=cur_item; n++) ustop=ustop->next;
  void *item=AllocMenuItem(gui);
  if (ustop)
  {
    len=strlen(ustop->name);
    ws=AllocMenuWS(gui,len+4);
    oms2ws(ws,ustop->name,len);
    if (cur_ref->multiselect)
    {
      SetMenuItemIconArray(gui,item,icon_array);
      SetMenuItemIcon(gui,cur_item,((char*)cur_ref->data)[n]);
    }
  }
  else
  {
    ws=AllocMenuWS(gui,10);
    ascii2ws(ws,lgpData[LGP_Error]);//"������");
  }
  SetMenuItemText(gui, item, ws, cur_item);
}

int sel_softkeys[]={0,1,2};
SOFTKEY_DESC sel_sk[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Close"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB sel_skt=
{
  sel_sk,0
};

HEADER_DESC sel_HDR={0,0,0,0,NULL,(int)"Select:",LGP_NULL};

MENU_DESC sel_STRUCT=
{
  8,sel_menu_onkey,sel_menu_ghook,NULL,
  sel_softkeys,
  &sel_skt,
  0x10,
  sel_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

int ChangeMenuSelection(VIEWDATA *vd, REFCACHE *rf)
{
  int start=0;
  SEL_STRUCT *ustop=0, *usbot=0;
  SEL_STRUCT *us;
  unsigned short i;
  vd->oms_pos=rf->id;
  i=_rshort2(vd->oms+vd->oms_pos);
  vd->oms_pos+=2+i+1;
  int n_sel=_rshort2(vd->oms+vd->oms_pos);
  vd->oms_pos+=2;
  for(int o=0;o<n_sel;o++)
  {
    while(*(vd->oms+vd->oms_pos)!='o') vd->oms_pos++; // '$'
    vd->oms_pos++;
    if (rf->value==vd->oms_pos) start=o;
    us=malloc(sizeof(SEL_STRUCT));
    char *d=extract_omstr(vd,vd->oms_pos);
    strcpy(us->name,d);
    mfree(d);
    us->value=vd->oms_pos;
    int i=_rshort2(vd->oms+vd->oms_pos);
    vd->oms_pos+=2+i;
    us->id2=vd->oms_pos;
    i=_rshort2(vd->oms+vd->oms_pos);
    vd->oms_pos+=2+i+1;
    us->next=0;
    if (usbot)
    {
      usbot->next=us;
      usbot=us;
    }
    else
    {
      ustop=us;
      usbot=us;
    }
  }
  cur_ref=rf;
  cur_vd=vd;
  icon_array[0]=GetPicNByUnicodeSymbol(CBOX_UNCHECKED);
  icon_array[1]=GetPicNByUnicodeSymbol(CBOX_CHECKED);
  if (rf->multiselect) sel_STRUCT.flags2=0x11;
  else sel_STRUCT.flags2=0x10;
  patch_header(&sel_HDR);
  return CreateMenu(0,0,&sel_STRUCT,&sel_HDR,start,n_sel,ustop,0);
}

void initDisplayUtilsLangPack()
{
  txtview_hdr.lgp_id=(int)lgpData[LGP_TextHeader];
  sel_HDR.lgp_id=(int)lgpData[LGP_TextHeader];
  sel_HDR.lgp_id=(int)lgpData[LGP_SelectHeader];
  sel_sk[0].lgp_id=(int)lgpData[LGP_Select];
  sel_sk[1].lgp_id=(int)lgpData[LGP_Close];
  txtview_menu_sk[0].lgp_id=(int)lgpData[LGP_Ok];
  txtview_menu_sk[1].lgp_id=(int)lgpData[LGP_Cancel];
  input_box_hdr.lgp_id=(int)lgpData[LGP_EnterHeader];
  input_box_menu_sk[0].lgp_id=(int)lgpData[LGP_Ok];
  input_box_menu_sk[1].lgp_id=(int)lgpData[LGP_Cancel];
}
