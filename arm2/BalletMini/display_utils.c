#include "../inc/swilib.h"
#include "view.h"
#include "display_utils.h"
#include "siemens_unicode.h"
#include "string_works.h"
#include "rect_patcher.h" 
#include "main.h"
#include "file_works.h"
#include "urlstack.h"
#include "lang.h"

extern int maincsm_id;

extern const int scr_shift;
extern const int word_wrap;

extern const int cfgPwdNormalText;
extern const int cfgShowCharCounter;
extern const char cfgCursorColor[4];
extern const char cfgCursorColorPictures[4];
extern const int cfgInvertCursor;

extern WSHDR *search_string;
extern int search_isCaseSens;

int GetFontHeight(int font, int atribute)
{
  int height=GetFontYSIZE(font);
  if (atribute&TEXT_INVERT)   height+=1;
  if (atribute&TEXT_UNDERLINE)   height+=1;
  if (atribute&TEXT_OUTLINE)  height+=2;
  return height;
}

int GetSymbolBitmapWidth(VIEWDATA *vd, int wchar,int font)
{
  if ((wchar&0xFF00)==0xE100)
  {
    OMS_DYNPNGLIST *dpl = vd->dynpng_list;
    do
    {
      if (dpl->w_char == wchar)
      {
        return (dpl->dp.img)->w;
      }
    }
    while(dpl=dpl->dp.next);
  }
  return GetSymbolWidth(wchar,font);
}

int GetBitmapHeight(VIEWDATA *vd, int wchar)
{
  OMS_DYNPNGLIST *dpl = vd->dynpng_list;
  do
  {
    if (dpl->w_char == wchar)
    {
      return (dpl->dp.img)->h;
    }
  }
  while(dpl=dpl->dp.next);
  return GetImgHeight(GetPicNByUnicodeSymbol(wchar));;
}

unsigned int SearchNextDisplayLine(VIEWDATA *vd, LINECACHE *p/*, unsigned int *max_h*/)
{
  int scrW = ScreenW()-MARGIN;
  int left=scrW;
  int c,h,cw,f=0;
  p->centerAtAll=0;
  p->pixheight=0;
  p->pos=vd->lines_cache_pos;
  while(p->pos<vd->rawtext_size)
  {
    c=vd->rawtext[p->pos++];
    if ((c&0xFF00)==0xE100)
    {
      
      h=GetBitmapHeight(vd,c);
    }
    else
    {
      h=GetFontHeight(p->bold?FONT_SMALL_BOLD:FONT_SMALL,p->underline?TEXT_UNDERLINE:0+p->ref?TEXT_INVERT:0);
    }
    switch(c)
    {
    case UTF16_NEWLINE:
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
      {
        p->bold=0;
      }
      continue;
    case UTF16_FONT_SMALL_BOLD:
      {
        p->bold=1;
      }
      continue;
    case UTF16_INK_RGBA:
      if (p->pos>(vd->rawtext_size-2)) return 0;
      p->ink1=vd->rawtext[p->pos++];
      p->ink2=vd->rawtext[p->pos++];
      continue;
    case UTF16_PAPER_RGBA:
      if (p->pos>(vd->rawtext_size-2)) return 0;
      p->paper1=vd->rawtext[p->pos++];
      p->paper2=vd->rawtext[p->pos++];
      continue;
    case UTF16_INK_INDEX:
    case UTF16_PAPER_INDEX:
      if (p->pos>=(vd->rawtext_size-1)) return 0;
      p->pos++;
      continue;
    }
    // компоновка элементов здесь
    cw=GetSymbolBitmapWidth(vd,c,p->bold?FONT_SMALL_BOLD:FONT_SMALL);
    left-=cw;
    if (left<0)
    {
      int b=1;
      int cw=0;
      if (p->ref)
      {
        while (1)
        {
          cw+=GetSymbolBitmapWidth(vd,vd->rawtext[p->pos-b],p->bold?FONT_SMALL_BOLD:FONT_SMALL);
          if (cw>=(scrW*3/4))
          {
            b=1;
            break;
          }
          if (word_wrap && (vd->rawtext[p->pos-b]==UTF16_SPACE)) { /*b--;*/ break;}
          if (vd->rawtext[p->pos-b]==UTF16_ENA_INVERT) break;
          if (vd->rawtext[p->pos-b]==UTF16_NEWLINE)
          {
            b++;
            break;
          }
          b++;
        }
      }
      else
      {
        if (word_wrap)
        {
          while (1)
          {
            cw+=GetSymbolBitmapWidth(vd,vd->rawtext[p->pos-b],p->bold?FONT_SMALL_BOLD:FONT_SMALL);
            if (cw>=(scrW*3/4))
            {
              b=1;
              break;
            }
            if ((vd->rawtext[p->pos-b]&0xFF00)==0xE100) {b--; break;}
            if (vd->rawtext[p->pos-b]==UTF16_SPACE) { b--; break;}
            if (vd->rawtext[p->pos-b]==UTF16_DIS_INVERT) break;
            if (vd->rawtext[p->pos-b]==UTF16_NEWLINE)
            {
              b++;
              break;
            }
            b++;
          }
        }
      }
      p->pos-=b;
      return 1; // here can be a bug with line height
    }
    
    /*if (cw>=(scrW/2)||h>(GetFontHeight(FONT_SMALL,0)*2)) // Картинки отдельно
    {
      if ((left+cw)<scrW) // image is last character
      {
        if (vd->rawtext[p->pos-1]==UTF16_ENA_INVERT)
        {
          p->pos-=2;
          return 1;
        }
        else
        {
          p->pos-=1;
          return 1;
        }
      }
    }*/
    if (h>p->pixheight) p->pixheight=h;
      
    if ((cw>=scrW/2)&&h>(GetFontHeight(FONT_SMALL,0)*3)) // Картинки отдельно
    {
      if ((left+cw)==scrW) // image is first character
      {
        if (p->pos>(vd->rawtext_size-1)) return 0;
        p->centerAtAll=1;
        if (vd->rawtext[p->pos+1]==UTF16_DIS_INVERT)
        {
          p->ref=0;
          p->pos+=1;
          return 1;
        }
        else
        {
          return 1;
        }
      }
    }
    if (f) return 1;
  }
  return 0;
}

#define LINESCACHECHUNK 256

static void newCacheLine(VIEWDATA *vd, LINECACHE *p)
{
  if ((vd->lines_cache_size%LINESCACHECHUNK)==0)
  {
    //Дошли до конца куска, реаллоцируем еще кусок
    vd->lines_cache=realloc(vd->lines_cache,(vd->lines_cache_size+LINESCACHECHUNK)*sizeof(LINECACHE));
  }
  memcpy(vd->lines_cache+(vd->lines_cache_size++),p,sizeof(LINECACHE));
  vd->lines_cache_pos=p->pos;
}

int LineDown(VIEWDATA *vd)
{
  LINECACHE lc;
  if (vd->view_line+1<vd->lines_cache_size)
  {
    vd->view_line++;
  }
  else
  {
    LINECACHE *plc;
    if (!vd->lines_cache_size)
    {
      lc.ink1=0x0000;
      lc.ink2=0x0064;
      lc.paper1=0xFFFF;
      lc.paper2=0xFF64;
      lc.pixheight=0;
      lc.ycoord = 0;
      lc.bold=0;
      lc.underline=0;
      lc.ref=0;
      lc.pos=0;
      lc.center=0;
      lc.right=0;
      lc.centerAtAll=0;
      newCacheLine(vd,&lc);
    }
    plc=vd->lines_cache+vd->lines_cache_size-1;
    if (!SearchNextDisplayLine(vd,plc)) return 0; // can't caching futher
    memcpy(&lc,plc,sizeof(LINECACHE));
    lc.ycoord += plc->pixheight;
    newCacheLine(vd,&lc);
    vd->view_line++;
  }
  return 1;
}
// 0 page start
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
  if (!RenderPage(vd,0)||vd->lines_cache_size==0) return;
  
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
      vd->pixdisp=(vd->lines_cache+vd->lines_cache_size-1)->pixheight;
      scrollUp(vd,ScreenH()-1-scr_shift);
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
      vd->pixdisp=(vd->lines_cache+vd->lines_cache_size-1)->pixheight;
      scrollUp(vd,ScreenH()-1-scr_shift);
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


void renderForm(VIEWDATA *vd, REFCACHE *rf, int x, int y, int y2, int wchar, int isRef)
{
  int scr_w = ScreenW() - MARGIN/2;
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
    DrawString(ws2,x+d,y+d,scr_w,ScreenH(),
      FONT_SMALL,TEXT_NOFORMAT,
      GetPaletteAdrByColorIndex(isRef?0:1),
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
    DrawString(ws2,x+d,y+d,scr_w,ScreenH(),
      FONT_SMALL,TEXT_NOFORMAT,
      GetPaletteAdrByColorIndex(isRef?0:1),
      GetPaletteAdrByColorIndex(23));
    FreeWS(ws2);
    mfree(c);
  }
  if (rf->tag=='u')
  {
    DrawString((WSHDR *)rf->data,x+4,y+3+(y2-y-GetImgHeight(GetPicNByUnicodeSymbol(wchar))),scr_w,ScreenH(),
      FONT_SMALL,TEXT_NOFORMAT,
      GetPaletteAdrByColorIndex(isRef?0:1),
      GetPaletteAdrByColorIndex(23));
  }
}
// возвращает 1, если видна последняя строка
// возвращает 2, если виден конец страницы
int RenderPage(VIEWDATA *vd, int do_draw)
{
  int scr_w=ScreenW()-MARGIN/2;
  int scr_h=ScreenH()-1;
  int sc=0;
  int dc;
  WSHDR *ws=vd->ws;
  LINECACHE *lc;
  int ypos=scr_shift-vd->pixdisp;
  unsigned int vl;
  unsigned int store_line=vl=vd->view_line;
  unsigned int len;
  unsigned int y2;
  
  char def_ink[4];
  COLOR_RC rc[MAX_COLORS_IN_LINE];
  int cur_rc;
  int ws_width;
  
  int c;
  int ena_ref=0;
  int isBold = 0;
  int isUnderline = 0;
  int max_ref_height;
  
  unsigned int flag=0;
  
  vd->pos_first_ref=0xFFFFFFFF;
  vd->pos_last_ref=0xFFFFFFFF;
  vd->pos_prev_ref=0xFFFFFFFF;
  vd->pos_next_ref=0xFFFFFFFF;
  
  int dfh=GetFontHeight(FONT_SMALL,0)*2; //double font height
  
  typedef struct
  {
    REFCACHE *form_rf;
    int       form_x;
    int       form_char;
    int       isRef;
  }tFormData;
  
  REFCACHE *rnd_rf;
  tFormData form_data[32];
  int form_num;
  
  RECT rcs[32]; // cursor
  RECT rcs_work;
  RECT rc_search;
  int  rcs_num=0;
  
  int lcheck=0; // last line checker
  int lprev=0; // prev line
  
  int x;
  
  while(ypos<=scr_h)
  {
    if (!lcheck) 
      lcheck=!LineDown(vd);
    else 
      lcheck++;
    if (lcheck<=1&&vd->lines_cache_size>0)
    {

      lc=vd->lines_cache+vl;
      if (vl) lprev=-1;
      dc=0;
      ws_width=0;
      cur_rc=1;
      rnd_rf=NULL;
      zeromem(&rc_search,sizeof(RECT));
      zeromem(&rcs_work,sizeof(RECT));
      zeromem(&form_data, 32*sizeof(tFormData));
      form_num = 0;
      max_ref_height = 0;
      rc[0].start_x=MARGIN/2;
      rc[0].end_x=scr_w-1;
      rc[0].color[0]=lc[lprev].paper1>>8;
      rc[0].color[1]=lc[lprev].paper1;
      rc[0].color[2]=lc[lprev].paper2>>8;
      rc[0].color[3]=lc[lprev].paper2;
      
      if (vl) sc=lc[lprev].pos;
      len=lc->pos-sc;
      
      if (lc[lprev].bold)
      {
        isBold = 1;
      }
      
      if (lc[lprev].underline)
      {
        isUnderline = 1;
      }
      
      if ((cfgInvertCursor) && (ena_ref))
        ws->wsbody[++dc]=UTF16_ENA_INVERT;
          
      while(len>0&&dc<250)
      {
        c=vd->rawtext[sc];
        
        if (sc == vd->found_word_pos)
        {
          rc_search.x=ws_width+MARGIN/2;
        }
          
        if ((vd->found_word_pos != -1) && (sc == vd->found_word_pos+wstrlen(search_string)))
        {
          rc_search.x2=ws_width+MARGIN/2;
        }
        
        if (c==UTF16_ENA_INVERT)
        {
          if ((lc->pixheight<dfh)?(ypos<0):(ypos+lc->pixheight-dfh<0))
            goto L1;
          if ((lc->pixheight<dfh)?(ypos+lc->pixheight>scr_h):(ypos+dfh>scr_h))
            goto L1;
          if (vd->pos_cur_ref==sc)
          { 
            flag=1;
            ena_ref=1;
            rcs_work.x=ws_width;
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
          if (!cfgInvertCursor)
            goto L1;
        }
        if (c==UTF16_DIS_INVERT)
        {
          if (ena_ref!=1)
          {
            if (ena_ref) ena_ref--;
            goto L1;
          }
          rcs_work.x2=ws_width;
          ena_ref=0;
          if (!cfgInvertCursor)
            goto L1;
        }
        if (c==UTF16_PAPER_RGBA)
        {
          if (cur_rc<MAX_COLORS_IN_LINE)
          {
            COLOR_RC *prev=rc+cur_rc-1;
            rc[cur_rc].color[0]=vd->rawtext[sc+1]>>8;
            rc[cur_rc].color[1]=vd->rawtext[sc+1];
            rc[cur_rc].color[2]=vd->rawtext[sc+2]>>8;
            rc[cur_rc].color[3]=vd->rawtext[sc+2];
            if (memcmp((void *)rc[cur_rc].color,(void *)prev->color,4))  // Только если цвет не равен предыдущему (очередь объектов не резиновая ;))
            {
              if (ws_width)
                prev->end_x=ws_width-1+MARGIN/2;
              else
                prev->end_x = MARGIN/2;
              rc[cur_rc].start_x=ws_width+MARGIN/2;
              rc[cur_rc].end_x=scr_w-1;
              cur_rc++;
            }
          }
        }
        if (c==UTF16_ALIGN_LEFT||c==UTF16_ALIGN_RIGHT||c==UTF16_ENA_CENTER|| \
            c==UTF16_DIS_CENTER||c==UTF16_NEWLINE)
        {
          goto L1;
        }
        if ((c&0xFF00)==0xE100)
        {
          rnd_rf=FindReferenceByBegin(vd,sc-1);         
          if ((rnd_rf) && (c==vd->WCHAR_TEXT_FORM||c==vd->WCHAR_LIST_FORM||rnd_rf->tag == 'u'))
          {
            form_data[form_num].form_rf = rnd_rf;
            form_data[form_num].form_x = ws_width;
            form_data[form_num].form_char = c;
            if (cfgInvertCursor)
              form_data[form_num].isRef = ena_ref;
            form_num++;    
          }  
        }
        if (c==UTF16_ENA_UNDERLINE)
        {
          isUnderline = 1;
        }
        if (c==UTF16_DIS_UNDERLINE)
        {
          isUnderline = 0;
        }
        if (c==UTF16_FONT_SMALL_BOLD)
        {
          isBold = 1;
        }
        if (c==UTF16_FONT_SMALL)
        {
          isBold = 0;
        }
        ws->wsbody[++dc]=c;
        ws_width+=GetSymbolWidth(c,isBold?FONT_SMALL_BOLD:FONT_SMALL);
        if (ena_ref)
        {
          int th;
          if ((c&0xFF00)==0xE100)
          {
            th=GetImgHeight(GetPicNByUnicodeSymbol(c));
          }
          else
          {
            th=GetFontHeight(isBold?FONT_SMALL_BOLD:FONT_SMALL,isUnderline?TEXT_UNDERLINE:0);
          }
          if ( th > max_ref_height)
            max_ref_height = th;
        }

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
      ws->wsbody[0]=dc;
      y2=lc->pixheight+ypos;
      if (do_draw)
      {
        if (y2!=ypos)
        {
          x=MARGIN/2;
          if (lc->right) x=scr_w-ws_width;
          if (lc->center||lc->centerAtAll) x=(ScreenW()-ws_width)/2;
          
          def_ink[0]=lc[lprev].ink1>>8;
          def_ink[1]=lc[lprev].ink1;
          def_ink[2]=lc[lprev].ink2>>8;
          def_ink[3]=lc[lprev].ink2;
          
          for (int i=0; i!=cur_rc; i++)
          {
            DrawRectangle(rc[i].start_x,ypos,rc[i].end_x,y2,
                          RECT_FILL_WITH_PEN,rc[i].color,rc[i].color);
          }
          
          if (ena_ref) rcs_work.x2=ws_width;
          if ((rcs_work.x!=0||rcs_work.x2!=0)&&rcs_work.x!=rcs_work.x2)
          {
            rcs_work.y=y2-max_ref_height;
            rcs_work.y2=y2;
            rcs_work.x+=x;
            rcs_work.x2+=x;
           
            
            rcs_work.x-=2;
            rcs_work.x2++;
            rcs_work.y--;
            
            if (rcs_work.x<0) rcs_work.x=0;
            if (rcs_work.x2>scr_w) rcs_work.x2=scr_w;
            
            memcpy(&rcs[rcs_num],&rcs_work,sizeof(RECT));
            rcs_num++;
          }
          
 
          DrawString(ws,x,ypos,scr_w-1,y2,
                     lc[lprev].bold?FONT_SMALL_BOLD:FONT_SMALL,
                     TEXT_NOFORMAT+(lc[lprev].underline?TEXT_UNDERLINE:0),
                     def_ink,GetPaletteAdrByColorIndex(23));
          
          for (int i = 0; form_data[i].form_rf != 0; i++)
          {           
            renderForm(vd, form_data[i].form_rf, form_data[i].form_x+x, ypos, y2, form_data[i].form_char, form_data[i].isRef);
          }
          
          if (rc_search.x!=rc_search.x2)
          {
            char cl[4];
            setColor(255,0,0,100,cl);
            if (rc_search.x == 0)
              rc_search.x = MARGIN/2;
            if (rc_search.x2 == 0)
              rc_search.x2 = scr_w-1;
            DrawLine(rc_search.x,y2-2,rc_search.x2,y2-2, 0, cl);
            DrawLine(rc_search.x,y2-1,rc_search.x2,y2-1, 0, cl);
          }
           
        }
        
        
        if (y2>=scr_h||lcheck)
        {
          if ((!cfgInvertCursor) && (rcs_num))
          {
            char* cl;
            cl = (char*)cfgCursorColor;
            REFCACHE *rf=FindReferenceByBegin(vd,vd->pos_cur_ref);
            if (rf->tag=='Z') 
              cl = (char*)cfgCursorColorPictures;
            for (int i=0;i<rcs_num;i++)
            {
 
               DrawLine(rcs[i].x2  ,rcs[i].y  ,rcs[i].x2  ,rcs[i].y2  ,0,cl);
               DrawLine(rcs[i].x2-1,rcs[i].y  ,rcs[i].x2-1,rcs[i].y2  ,0,cl);
               if (i+1<rcs_num&&rcs[i].x<rcs[i+1].x2)
               {
                 DrawLine(rcs[i].x2,rcs[i].y2,rcs[i+1].x2,rcs[i].y2,0,cl);
                 if (rcs[i].x2>rcs[i+1].x2)
                   DrawLine(rcs[i].x2-1,rcs[i].y2+1,rcs[i+1].x2+1,rcs[i].y2+1,0,cl);
                 else
                   DrawLine(rcs[i].x2+1,rcs[i].y2+1,rcs[i+1].x2-1,rcs[i].y2+1,0,cl);
               }
               else
               {
                 DrawLine(rcs[i].x2  ,rcs[i].y2  ,rcs[i].x  ,rcs[i].y2  ,0,cl);
                 DrawLine(rcs[i].x2-1,rcs[i].y2+1,rcs[i].x+1,rcs[i].y2+1,0,cl);
               }
               DrawLine(rcs[i].x  ,rcs[i].y2  ,rcs[i].x  ,rcs[i].y  ,0,cl);
               DrawLine(rcs[i].x+1,rcs[i].y2  ,rcs[i].x+1,rcs[i].y  ,0,cl);
               if (i>0&&rcs[i].x2>rcs[i-1].x)
               {
                 DrawLine(rcs[i].x,rcs[i].y,rcs[i-1].x,rcs[i].y,0,cl);
                 if (rcs[i].x<rcs[i-1].x)
                   DrawLine(rcs[i].x+1,rcs[i].y-1,rcs[i-1].x-1,rcs[i].y-1,0,cl);
                 else
                   DrawLine(rcs[i].x-1,rcs[i].y-1,rcs[i-1].x+1,rcs[i].y-1,0,cl);
               }
               else
               {
                 DrawLine(rcs[i].x  ,rcs[i].y  ,rcs[i].x2 , rcs[i].y  ,0,cl);
                 DrawLine(rcs[i].x+1,rcs[i].y-1,rcs[i].x2-1,rcs[i].y-1,0,cl);
               }
            }
          }
          
          if (vd->lines_cache_size)
          {
            LINECACHE *lastline = vd->lines_cache + vd->lines_cache_size - 1;
            int pageheight = lastline->ycoord + lastline->pixheight;
            if (pageheight)
            {
              unsigned int ycoord = vd->lines_cache[store_line].ycoord;
              unsigned int scrh = scr_h-scr_shift+1;
              int b = (ycoord+vd->pixdisp)*scrh/pageheight+scr_shift;
              int e = scrh*scrh/pageheight;
              if (e < 4) e = 4;  
              if (e < scrh)
              {
    #ifdef ELKA
                char cl1[4];
                setColor(160,48,48,100,cl1);
                char cl2[4];
                setColor(160,16,16,100,cl2);
                char cl3[4];
                setColor(136,140,136,100,cl3);
                char cl4[4];
                setColor(200,204,200,100,cl4);
                DrawLine(ScreenW()-2,scr_shift,ScreenW()-2,ScreenH()-1, 0, cl3);
                DrawLine(ScreenW()-1,scr_shift,ScreenW()-1,ScreenH()-1, 0, cl4);
                DrawLine(ScreenW()-2,b,ScreenW()-2,b+e, 0, cl1);
                DrawLine(ScreenW()-1,b,ScreenW()-1,b+e, 0, cl2);
    #else
                DrawRectangle(ScreenW()-1,b,ScreenW(),b+e,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(2));
    #endif
              }
            }
          }
          
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
      }
      else
        vd->found_word_pos = -1;
      ypos=y2;
      vl++;
    }
    else
    {
      break;
    }
  }
  
 

  if (flag==0) vd->pos_cur_ref=0xFFFFFFFF;
  vd->view_line=store_line;
  
//  WSHDR *ws2;
//  ws2=AllocWS(128);
//  wsprintf(ws2,"lcheck:%i",lcheck);
//  DrawString(ws2,3,14,scr_w,scr_h,FONT_SMALL,TEXT_NOFORMAT,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(21));
//  FreeWS(ws2);
  
  if (lcheck==2)
    return 0;
  else
    return 1;
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

int FindReferenceById(VIEWDATA *vd, unsigned int id, int i) // Находит index'ы всех ref'ов с заданным id
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

/*******************************************************************************
  Templates menu
*******************************************************************************/
//GUI *paste_gui;

//Templates
char * templates_chars; //Собственно файл
char ** templates_lines; //Массив указателей на строки

void FreeTemplates(void)
{
  if (templates_lines) mfree(templates_lines);
  if (templates_chars) mfree(templates_chars);
  templates_lines=NULL;
  templates_chars=NULL;
}

SaveTextToTemplate(WSHDR* ws)
{
  int hFile;
  unsigned int io_error;
  char* s = malloc(wstrlen(ws)+2);
  ws2ascii(s, ws);
  strcat(s,"\n");
  char * templates_file = getSymbolicPath("$ballet\\templates.txt");
  if ((hFile = fopen(templates_file, A_ReadWrite+A_Create+A_Append,P_READ+P_WRITE, &io_error)) != -1)
  {
    fwrite(hFile,s,strlen(s),&io_error);
    fclose(hFile,&io_error);
  }
  mfree(s);
}

int LoadTemplates()
{
  FSTATS fstat;
  int hFile;
  unsigned int io_error = NULL;
  int templates_num = NULL;
  char * p;
  char * pp;
  int c;
  char * templates_file = getSymbolicPath("$ballet\\templates.txt");

  FreeTemplates();
  if (GetFileStats(templates_file, &fstat, &io_error) != -1)
  {
    if (fstat.size > 0)
    {
      if ((hFile = fopen(templates_file, A_ReadOnly + A_BIN, P_READ, &io_error)) != -1)
      {
        p = templates_chars = malloc(fstat.size + 1);
        p[fread(hFile, p, fstat.size, &io_error)] = NULL;
        fclose(hFile, &io_error);
        pp = p;
        for(;;)
        {
          c = *p;
          if (c < 32)
          {
            if (pp && (pp != p))
            {
              templates_lines = realloc(templates_lines,(templates_num + 1)*sizeof(char *));
              templates_lines[templates_num ++] = pp;
            }
            pp = NULL;
            if (!c) break;
            *p = NULL;
          }
          else
          {
            if (!pp) pp = p;
          }
          p++;
        }
      }
    }
  }
  mfree(templates_file);
  return templates_num;
}

int curpos;
int curpos_changed = 0;

int templates_menu_onkey(void *gui, GUI_MSG *msg)
{
  if (msg->keys == 0x3D || msg->keys == 0x18)
  {
    int i = GetCurMenuItem(gui);
    if (templates_lines[i])
    {
      GUI* paste_gui = (GUI*)MenuGetUserPointer(gui);
      EDITCONTROL ec;
      ExtractEditControl(paste_gui, 1, &ec);
      curpos=EDIT_GetCursorPos(paste_gui);
      char c;
      while((c=*(templates_lines[i])++))
      {
        wsInsertChar(ec.pWS,char8to16(c),curpos++);
      }
      curpos_changed = 1;
    }
    return (1);
  }
  return (0);
}

void templates_menu_ghook(void *gui, int cmd)
{
  if (cmd == TI_CMD_DESTROY) // free
  {
    FreeTemplates();
  }
  if (cmd == TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
}
void templates_menu_iconhndl(void *gui, int cur_item, void *user_pointer)
{
  int len = strlen(templates_lines[cur_item]);
  WSHDR * ws = AllocMenuWS(gui, len + 4);
  void * item = AllocMenuItem(gui);
  ascii2ws(ws, templates_lines[cur_item]);
  SetMenuItemText(gui, item, ws, cur_item);
}

int templates_menu_softkeys[]={0,1,2};
SOFTKEY_DESC templates_menu_sk[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Close"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB templates_menu_skt=
{
  templates_menu_sk,0
};

HEADER_DESC templates_menu_header={0,0,0,0,NULL,(int)"Выбор",LGP_NULL};

MENU_DESC templates_menu_struct=
{
  8, templates_menu_onkey, templates_menu_ghook, NULL,
  templates_menu_softkeys,
  &templates_menu_skt,
  0x10,
  templates_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

void createTemplatesMenu(void* data)
{
  patch_header(&templates_menu_header);
  
  templates_menu_sk[0].lgp_id=(int)lgpData[LGP_Select];
  templates_menu_sk[1].lgp_id=(int)lgpData[LGP_Back];
  templates_menu_header.lgp_id=(int)lgpData[LGP_Templates];
  
  CreateMenu(0, 0, &templates_menu_struct, &templates_menu_header, 0, LoadTemplates(), data, 0);
}

// EDIT BOX
VIEWDATA *cur_vd;
unsigned int pos_ref;

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
    if (cfgShowCharCounter)
    {
      void *ma=malloc_adr();
      void *mf=mfree_adr();
      WSHDR* htext = AllocWS(256);
      EDITCONTROL ec;
      ExtractEditControl(data,1,&ec);
      wsprintf(htext,"%t    %d", lgpData[LGP_EnterHeader], ec.pWS->wsbody[0]);
      SetHeaderText(GetHeaderPointer(data), htext, ma, mf);
    }
  }
  if(cmd==TI_CMD_FOCUS)
  {
    if (curpos_changed)
    {
      curpos_changed = 0;
      EDIT_SetCursorPos(data, curpos);
    }
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
    case 1:
      ascii2ws(item->ws,lgpData[LGP_AddToTemplate]);
      break;
    case 2:
      ascii2ws(item->ws,lgpData[LGP_Clear]);
      break;
    }
  }
  if (item->type==1)
  {
    GUI *data = item->user_pointer;
    EDITCONTROL ec;
    ExtractEditControl(data,1,&ec);
    switch(item->cur_item)
    {
    case 0:
      createTemplatesMenu(data);
      break;
    case 1:
      SaveTextToTemplate(ec.pWS);
      break;
    case 2:
      CutWSTR(ec.pWS,0);
      break;
    }
  }
}

static int input_box_onkey(GUI *data, GUI_MSG *msg)
{
  EDITCONTROL ec;
  int gb_pressed = 0;
  if ((msg->gbsmsg->msg==KEY_DOWN)&&(msg->gbsmsg->submess==ENTER_BUTTON))
  {
    //paste_gui=data;
    EDIT_OpenOptionMenuWithUserItems(data,input_box_onkey_options,data,3);
    return (-1);
  }
  if ((msg->gbsmsg->msg==KEY_DOWN)&&(msg->gbsmsg->submess==GREEN_BUTTON))
    gb_pressed = 1;
  if ((msg->keys==0xFFF) || (gb_pressed))
  {
    // set value
    ExtractEditControl(data,1,&ec);
    REFCACHE* text_ref = FindReference(cur_vd,pos_ref);
    FreeWS(((WSHDR *)text_ref->data));
    text_ref->data=(void *)AllocWS(ec.pWS->wsbody[0]);
    wstrcpy(((WSHDR *)text_ref->data),ec.pWS);
    setUserText(text_ref->id, ec.pWS);
    if ((!text_ref->no_upload) || (gb_pressed))
    {
      goto_url=malloc(strlen(cur_vd->pageurl)+1);
      strcpy(goto_url,cur_vd->pageurl);
      from_url=malloc(strlen(cur_vd->pageurl)+1);
      strcpy(from_url,cur_vd->pageurl);
      goto_params=collectItemsParams(cur_vd,text_ref);
    }
    else
    {
      MAIN_CSM *main_csm;
      if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
      {
        main_csm->sel_bmk=0;
      }
    }
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
  //  0x00000001 - Выровнять по правому краю
  //  0x00000002 - Выровнять по центру
  //  0x00000004 - Инверсия знакомест
  //  0x00000008 - UnderLine
  //  0x00000020 - Не переносить слова
  //  0x00000200 - bold
  0,
  //  0x00000002 - ReadOnly
  //  0x00000004 - Не двигается курсор
  //  0x40000000 - Поменять местами софт-кнопки
  0x40000000
};

int CreateInputBox(VIEWDATA *vd, REFCACHE* rf, unsigned int cur_pos_ref)
{
  pos_ref=cur_pos_ref;
  cur_vd=vd;
  
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  
  eq=AllocEQueue(ma,mfree_adr());
  WSHDR *ews=AllocWS(16384);
  
  wstrcpy(ews,((WSHDR *)rf->data));
  
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL|(((rf->tag=='p')&&(!cfgPwdNormalText))?ECF_PASSW:NULL),ews,16384);
  AddEditControlToEditQend(eq,&ec,ma);

  FreeWS(ews);
  patch_header(&input_box_hdr);
  patch_input(&input_box_desc);
  input_box_hdr.lgp_id=(int)lgpData[LGP_EnterHeader];
  input_box_menu_sk[0].lgp_id=(int)lgpData[LGP_Ok];
  input_box_menu_sk[1].lgp_id=(int)lgpData[LGP_Cancel];
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
  if (cmd==0x0C)
    EDIT_SetCursorPos(data, 1);
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
  EDITC_OPTIONS ec_options;
  eq=AllocEQueue(ma,mfree_adr());
  if (!wstrlen(ws))
  {
    FreeWS(ws);
    return;
  }
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ws,2048);
  PrepareEditCOptions(&ec_options);
  SetFontToEditCOptions(&ec_options,FONT_SMALL);
  CopyOptionsToEditControl(&ec,&ec_options);
  AddEditControlToEditQend(eq,&ec,ma);
  FreeWS(ws);
  patch_header(&txtview_hdr);
  patch_input(&txtview_desc);
  txtview_hdr.lgp_id=(int)lgpData[LGP_TextHeader];
  txtview_menu_sk[0].lgp_id=(int)lgpData[LGP_Ok];
  txtview_menu_sk[1].lgp_id=(int)lgpData[LGP_Cancel];
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
    REFCACHE* sel_ref = FindReference(cur_vd,pos_ref);
    for (; n!=i; n++) ustop=ustop->next;
    if (ustop)
    {
      if (sel_ref->multiselect)
      {
        if(((char*)sel_ref->data)[n])
          ((char*)sel_ref->data)[n]=0;
        else
          ((char*)sel_ref->data)[n]=1;
        SetMenuItemIcon(gui,i,((char*)sel_ref->data)[n]);
        RefreshGUI();
      }
      else
      {
        sel_ref->value=ustop->value;
        sel_ref->id2=ustop->id2;
        setUserList(sel_ref->id, sel_ref->value, sel_ref->id2);
        if (!sel_ref->no_upload)
        {
          goto_url=malloc(strlen(cur_vd->pageurl)+1);
          strcpy(goto_url,cur_vd->pageurl);
          from_url=malloc(strlen(cur_vd->pageurl)+1);
          strcpy(from_url,cur_vd->pageurl);
          goto_params=collectItemsParams(cur_vd,sel_ref);
        }
        else
        {
          MAIN_CSM *main_csm;
          if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
          {
            main_csm->sel_bmk=0;
          }
        }

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
    REFCACHE* sel_ref = FindReference(cur_vd,pos_ref);
    if (sel_ref->multiselect)
    {
      SetMenuItemIconArray(gui,item,icon_array);
      SetMenuItemIcon(gui,cur_item,((char*)sel_ref->data)[n]);
    }
  }
  else
  {
    ws=AllocMenuWS(gui,10);
    ascii2ws(ws,lgpData[LGP_Error]);//"Ошибка");
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

int ChangeMenuSelection(VIEWDATA *vd, REFCACHE *rf, unsigned int cur_pos_ref)
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
  cur_vd=vd;
  pos_ref = cur_pos_ref;
  icon_array[0]=GetPicNByUnicodeSymbol(CBOX_UNCHECKED);
  icon_array[1]=GetPicNByUnicodeSymbol(CBOX_CHECKED);
  if (rf->multiselect) sel_STRUCT.flags2=0x11;
  else sel_STRUCT.flags2=0x10;
  patch_header(&sel_HDR);
  sel_HDR.lgp_id=(int)lgpData[LGP_SelectHeader];
  sel_sk[0].lgp_id=(int)lgpData[LGP_Select];
  sel_sk[1].lgp_id=(int)lgpData[LGP_Close];
  return CreateMenu(0,0,&sel_STRUCT,&sel_HDR,start,n_sel,ustop,0);
}


SOFTKEY_DESC link_box_menu_sk[]=
{
  {0x0018,0x0000,(int)"Ok"},
  {0x0001,0x0000,(int)"Cancel"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB link_box_menu_skt=
{
  link_box_menu_sk,0
};

HEADER_DESC link_box_hdr={0,0,0,0,NULL,(int)"Link:",LGP_NULL};

static void link_box_locret(void){}

static void link_box_ghook(GUI *data, int cmd)
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

void link_options(USR_MENU_ITEM *item)
{
  const char per_t[] = "%t";
  if (item->type==0)
  {
    switch(item->cur_item)
    {
      case 0: wsprintf(item->ws,per_t,"ballet"); break;
      case 1: wsprintf(item->ws,per_t,"browser");break;
      case 2: wsprintf(item->ws,per_t,"nrss");break;
      case 3: wsprintf(item->ws,per_t,"sieget");break;
      case 4: ascii2ws(item->ws,lgpData[LGP_Clear]);break;
    }
  }
  if (item->type==1)
  {
    GUI *gui = (GUI*)(item->user_pointer);
    EDITCONTROL ec;
    ExtractEditControl(gui,1,&ec);
    if (item->cur_item == 4)
      CutWSTR(ec.pWS,0);
    else
    {
      char* s = malloc(wstrlen(ec.pWS)+1);
      ws2ascii(s, ec.pWS);
      RunOtherByURL(s,item->cur_item);
      mfree(s);
    }
  }   
}

static int link_box_onkey(GUI *data, GUI_MSG *msg)
{
  if (msg->keys==0xFFF)
  {
    return (0xFF);
  }
  if ((msg->gbsmsg->msg==KEY_DOWN) && (msg->gbsmsg->submess == ENTER_BUTTON))
  {
    EDIT_OpenOptionMenuWithUserItems(data,link_options,data,5);
    return -1;
  }
  return (0);
}

static const INPUTDIA_DESC link_box_desc =
{
  1,
  link_box_onkey,
  link_box_ghook,
  (void *)link_box_locret,
  0,
  &link_box_menu_skt,
  {0,0,0,0},
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
  //  0x40000000 - Поменять местами софт-кнопки
  0x40000000
};

int ShowLink(char *link)
{
  
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  WSHDR* wslink = AllocWS(strlen(link));
  ascii2ws(wslink, link);
  
  eq=AllocEQueue(ma,mfree_adr());
  
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,wslink,wstrlen(wslink)*2);
  AddEditControlToEditQend(eq,&ec,ma);
  FreeWS(wslink);

  patch_header(&link_box_hdr);
  patch_input(&link_box_desc);
  link_box_menu_sk[0].lgp_id=(int)lgpData[LGP_Ok];
  link_box_menu_sk[1].lgp_id=(int)lgpData[LGP_Cancel];
  return CreateInputTextDialog(&link_box_desc,&link_box_hdr,eq,1,0);
}

void FindStringOnPage(VIEWDATA* cur_vd)
{
    int ld = LineDown(cur_vd);
    int i;
    i = (cur_vd->lines_cache[cur_vd->view_line]).pos+1;
    int j = 0;
    int found = 0;
    while ((i < cur_vd->rawtext_size) && (!found))
    {
      while ((j < wstrlen(search_string)) && 
             CompareWchar(cur_vd->rawtext[i+j], search_string->wsbody[1+j], search_isCaseSens))
        j++;
      if (j == wstrlen(search_string))
      {
        found = 1;
        cur_vd->found_word_pos = i;
      }
      else
      {
        i += 1+j;
        j = 0;
      }
    }
    if (found)
    {
      if (LineDown(cur_vd))
      {
        while (((cur_vd->lines_cache[cur_vd->view_line]).pos < i) && (LineDown(cur_vd)));
      }
    }
    if (ld)
      LineUp(cur_vd);
}
