#include "../inc/swilib.h"
#include "BalletView.h"
#include "clist_util.h"
#include "cont_menu.h"
#include "rect_patcher.h"
#include "message_list.h"

extern const char PATH_TO_AVATARS[128];

//-------------Цвета. Много цветов :)
extern const unsigned int DEF_SKR;
extern RGBA MESSAGEWIN_BGCOLOR ; // Общий фон
extern RGBA MESSAGEWIN_TITLE_BGCOLOR ; // Фон заголовка
extern RGBA MESSAGEWIN_TITLE_FONT ; // Цвет шрифта заголовка
extern RGBA MESSAGEWIN_MY_BGCOLOR ; // Цвет фона исходящих сообщений
extern RGBA MESSAGEWIN_CH_BGCOLOR ; // Цвет фона приватных сообщений
extern RGBA MESSAGEWIN_CURSOR_BGCOLOR; // Цвет фона курсора
extern RGBA MESSAGEWIN_GCHAT_BGCOLOR_1 ; // Чередование: Цвет фона сообщений конференции 1
extern RGBA MESSAGEWIN_GCHAT_BGCOLOR_2 ; // Чередование: Цвет фона сообщений конференции 2
extern RGBA MESSAGEWIN_SYS_BGCOLOR ; // Цвет фона сообщений уведомлений
extern RGBA MESSAGEWIN_STATUS_BGCOLOR; // Цвет фона сообщений смены статуса
extern RGBA MESSAGEWIN_CHAT_FONT; // Цвет шрифта сообщений
extern RGBA CURSOR_BORDER;

#define color(x) (char *)(&(x))

// fdecl
void scrollDown(VIEWDATA *vd, int amount);
void scrollUp(VIEWDATA *vd, int amount);
int RenderPage(VIEWDATA *vd, int do_draw);
void FreeViewData(VIEWDATA *vd);
void AddStringItem(VIEWDATA *vd, char *text);
void AddTextItem(VIEWDATA *vd, WSHDR *ws);
void VIEWDATA_ParseMessages(VIEWDATA *vd);
void AddBeginRef(VIEWDATA *vd);
void AddEndRef(VIEWDATA *vd);
void Init_Message(TRESOURCE* ContEx, char *init_text);
void RawInsertChar(VIEWDATA *vd, int wchar);
//void AddPictureItem(VIEWDATA *vd, void *picture);

// smiles
extern const char SMILE_FILE[];
extern const char SMILE_PATH[];

// string_works.c
int debugA=A_Truncate;
unsigned int debug_ul;
int debug_file;

void debugv(char *file,int line,void *p, int sz)
{
  if ((debug_file=fopen("0:\\zbin\\siejc\\debug.txt",A_ReadWrite+A_Create+debugA,P_READ+P_WRITE,&debug_ul))!=-1)
  {
    fwrite(debug_file,p,sz,&debug_ul);
    fclose(debug_file,&debug_ul);
  }
  debugA=A_Append;
}

void debugf(char *file,int line)
{
  if ((debug_file=fopen("0:\\zbin\\siejc\\debug.txt",A_ReadWrite+A_Create+debugA,P_READ+P_WRITE,&debug_ul))!=-1)
  {
    char c[256];
    sprintf(c,"%s : %i\n",file,line);
    fwrite(debug_file,c,strlen(c),&debug_ul);
    fclose(debug_file,&debug_ul);
  }
  debugA=A_Append;
}

extern int Message_gui_ID;

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
    if (cw>=ScreenW()/2||h>GetFontHeight(FONT_SMALL,0)*2)
    {
      if (left+cw<ScreenW())
      {
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
    if (cw>=ScreenW()/2||h>GetFontHeight(FONT_SMALL,0)*2)
    {
      if (left+cw==ScreenW())
      {
        if (pos>(vd->rawtext_size-1)) goto LERR;
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
    //Дошли до конца куска, реаллоцируем еще кусок
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

// возвращает 0, если виден конец страницы
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
  
  unsigned int flag=0;
  
  vd->pos_first_ref=0xFFFFFFFF;
  vd->pos_last_ref=0xFFFFFFFF;
  vd->pos_prev_ref=0xFFFFFFFF;
  vd->pos_next_ref=0xFFFFFFFF;
  
  int dfh=GetFontHeight(FONT_SMALL,0)*2; //double font height
  
  RECT rcs[32]; // cursor
  RECT rcs_work;
  int  rcs_num=0;
  
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
      zeromem(&rcs_work,sizeof(RECT));
      
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
      
      while(len>0&&(dc<32000))
      {
        c=vd->rawtext[sc];
        
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
              prev->end_x=ws_width-1;
              rc[cur_rc].start_x=ws_width;
              rc[cur_rc].end_x=scr_w;
              cur_rc++;
            }
          }
        }
        if (c==UTF16_ALIGN_LEFT||c==UTF16_ALIGN_RIGHT||c==UTF16_ENA_CENTER|| \
            c==UTF16_DIS_CENTER||c==UTF16_NEWLINE)
        {
          goto L1;
        }
        
        if ((c==UTF16_PAPER_RGBA)||(c==UTF16_INK_RGBA))
        {
          len--;
          sc++; sc++; //игнорируем код смены цвета. Влияет на выравнивание.
          //ws->wsbody[++dc]=vd->rawtext[++sc];
          len--;
          //ws->wsbody[++dc]=vd->rawtext[++sc];
          goto L1;
        }
        ws->wsbody[++dc]=c;
        ws_width+=GetSymbolWidth(c,lc->bold?FONT_SMALL_BOLD:FONT_SMALL);
        
        L1:
        sc++;
        len--;
      }
      ws->wsbody[0]=dc;
      if (lcheck)
        y2=ypos+vd->lastLineHeight;
      else
        y2=lc->pixheight+ypos;
      
      if (do_draw&&y2!=ypos)
      {
        int x=0;
        if (lc[1].right) x=scr_w-ws_width;
        if (lc[1].center||lc[1].centerAtAll) x=(scr_w-ws_width)/2;
        
        def_ink[0]=lc->ink1>>8;
        def_ink[1]=lc->ink1;
        def_ink[2]=lc->ink2>>8;
        def_ink[3]=lc->ink2;
        
        for (int i=0; i!=cur_rc; i++)
        {
          DrawRectangle(rc[i].start_x,ypos,rc[i].end_x,y2,
		                    RECT_FILL_WITH_PEN,rc[i].color,rc[i].color);
        }
        
        if (ena_ref) rcs_work.x2=ws_width;
        if ((rcs_work.x!=0||rcs_work.x2!=0)&&rcs_work.x!=rcs_work.x2)
        {
          rcs_work.y=ypos;
          rcs_work.y2=y2;
          rcs_work.x=0;//+=x;
          rcs_work.x2=scr_w;//+=x;
          
          rcs_work.x-=2;
          rcs_work.x2++;
          rcs_work.y--;
          
          if (rcs_work.x<0) rcs_work.x=0;
          if (rcs_work.x2>scr_w) rcs_work.x2=scr_w;
          
          memcpy(&rcs[rcs_num],&rcs_work,sizeof(RECT));
          rcs_num++;
        }
	      DrawString(ws,x,ypos,scr_w,y2,
		               lc->bold?FONT_SMALL_BOLD:FONT_SMALL,
                   TEXT_NOFORMAT+(lc->underline?TEXT_UNDERLINE:0),
		               def_ink,GetPaletteAdrByColorIndex(23));
        
        if (lcheck) vd->Resource_Ex->has_unread_msg =0; // Непрочитанных сообщений больше нет
      }
      if (y2>=scr_h||lcheck)
      {
        if (rcs_num)
        {
          char *c1=color(MESSAGEWIN_CURSOR_BGCOLOR);
          for (int i=0;i<rcs_num;i++)
          {
             DrawLine(rcs[i].x2  ,rcs[i].y  ,rcs[i].x2  ,rcs[i].y2  ,0,c1);
             DrawLine(rcs[i].x2-1,rcs[i].y  ,rcs[i].x2-1,rcs[i].y2  ,0,c1);
             if (i+1<rcs_num&&rcs[i].x<rcs[i+1].x2)
             {
               DrawLine(rcs[i].x2,rcs[i].y2,rcs[i+1].x2,rcs[i].y2,0,c1);
               if (rcs[i].x2>rcs[i+1].x2)
                 DrawLine(rcs[i].x2-1,rcs[i].y2+1,rcs[i+1].x2+1,rcs[i].y2+1,0,c1);
               else
                 DrawLine(rcs[i].x2+1,rcs[i].y2+1,rcs[i+1].x2-1,rcs[i].y2+1,0,c1);
             }
             else
             {
               DrawLine(rcs[i].x2  ,rcs[i].y2  ,rcs[i].x  ,rcs[i].y2  ,0,c1);
               DrawLine(rcs[i].x2-1,rcs[i].y2+1,rcs[i].x+1,rcs[i].y2+1,0,c1);
             }
             
             DrawLine(rcs[i].x  ,rcs[i].y2  ,rcs[i].x  ,rcs[i].y  ,0,c1);
             DrawLine(rcs[i].x+1,rcs[i].y2  ,rcs[i].x+1,rcs[i].y  ,0,c1);
             if (i>0&&rcs[i].x2>rcs[i-1].x)
             {
               DrawLine(rcs[i].x,rcs[i].y,rcs[i-1].x,rcs[i].y,0,c1);
               if (rcs[i].x<rcs[i-1].x)
                 DrawLine(rcs[i].x+1,rcs[i].y-1,rcs[i-1].x-1,rcs[i].y-1,0,c1);
               else
                 DrawLine(rcs[i].x-1,rcs[i].y-1,rcs[i-1].x+1,rcs[i].y-1,0,c1);
             }
             else
             {
               DrawLine(rcs[i].x  ,rcs[i].y  ,rcs[i].x2 , rcs[i].y  ,0,c1);
               DrawLine(rcs[i].x+1,rcs[i].y-1,rcs[i].x2-1,rcs[i].y-1,0,c1);
             }
          }
        }
        int b=(vd->lines_cache[store_line].pos*1000)/vd->rawtext_size*scr_h/1000-2;
        int e=(lc->pos*1000)/vd->rawtext_size*scr_h/1000+2;
        if (!lcheck||b>0)
        {
          if (lcheck) e=scr_h;
#ifdef ELKA
          DrawRectangle(scr_w-2,b,scr_w,e,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(2));
#else
          DrawRectangle(scr_w-1,b,scr_w,e,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(2));
#endif
        }
      }
      ypos=y2;
      vl++;
    }
    else
      break;
  }
  if (flag==0) vd->pos_cur_ref=0xFFFFFFFF;
  vd->view_line=store_line;
  
  if (lcheck==0)
    return 1;
  else
    return 0;
}

REFCACHE *findReferencePos(VIEWDATA *vd, unsigned int pos)
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

void VIEWDATA_onRedraw(VIEW_GUI *data)
{
  int scr_w=ScreenW()-1;
  int scr_h=ScreenH()-1;
  
  VIEWDATA *vd=&data->vd;
  
  if (data->gui.state==2)
  {
    if(vd->Resource_Ex->total_msg_count!=vd->OLD_MessList_Count)
      VIEWDATA_ParseMessages(vd);
      
    DrawRectangle(0,0,scr_w,scr_h,0,
      color(MESSAGEWIN_BGCOLOR),
      color(MESSAGEWIN_BGCOLOR));
    RenderPage(vd,1);
  }
}

void VIEWDATA_onCreate(VIEW_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
  data->vd.ws=AllocWS(32767);
  data->vd.pos_cur_ref=0xFFFFFFFF; //Еще вообще не найдена ссылка
}

void VIEWDATA_onClose(VIEW_GUI *data, void (*mfree_adr)(void *))
{
  FreeViewData(&data->vd);
  data->gui.state=0;
}

void VIEWDATA_onFocus(VIEW_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  PNGTOP_DESC *pltop=PNG_TOP();
  pltop->dyn_pltop=&data->vd.dynpng_list->dp;
  DisableIDLETMR();   // Отключаем таймер выхода по таймауту
  data->gui.state=2;
}

void VIEWDATA_onUnfocus(VIEW_GUI *data, void (*mfree_adr)(void *))
{
  PNGTOP_DESC *pltop=PNG_TOP();
  pltop->dyn_pltop=NULL;
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int VIEWDATA_onKey(VIEW_GUI *data, GUI_MSG *msg)
{
  VIEWDATA *vd=&data->vd;
  int m=msg->gbsmsg->msg;
  if ((m==KEY_DOWN)||(m==LONG_PRESS))
  {
    switch(msg->gbsmsg->submess)
    {
      case '5':
      case ENTER_BUTTON:
        {
          if (vd->pos_cur_ref!=0xFFFFFFFF)
          {
            REFCACHE *rf=findReferencePos(vd,vd->pos_cur_ref);
            if (rf)
            {
              char *s=rf->id->mess;
              unsigned int l = strlen(s);
              char *init_text = malloc(l+3+1);
              zeromem(init_text,l+3+1);
              init_text[0] = '>';
              init_text[1] = '>';
              strcat(init_text, s);
              init_text[2+l] = '\n';
              init_text[3+l] = '\0';
              Init_Message(vd->Resource_Ex, init_text);
              mfree(init_text);
            }
          }
        }
        break;
    case '9':
      while(LineDown(vd)) ;
      vd->pixdisp=0;
      scrollUp(vd,ScreenH()-1-vd->lastLineHeight);
      RenderPage(vd,0);
        break;
    case '1':
      while(LineUp(vd)) ;
      vd->pixdisp=0;
      RenderPage(vd,0);
        break;
    case '2':
    case UP_BUTTON:
      if (vd->pos_cur_ref==0xFFFFFFFF&&vd->pos_last_ref!=0xFFFFFFFF)
        vd->pos_cur_ref=vd->pos_last_ref;
      else
        if (vd->pos_prev_ref!=0xFFFFFFFF)
          vd->pos_cur_ref=vd->pos_prev_ref;
        else
        {
          scrollUp(vd,20);
          RenderPage(vd,0);
          if (vd->pos_prev_ref!=0xFFFFFFFF)
            vd->pos_cur_ref=vd->pos_prev_ref;
        }
      break;
    case '8':
    case DOWN_BUTTON:
      if (vd->pos_cur_ref==0xFFFFFFFF&&vd->pos_first_ref!=0xFFFFFFFF)
        vd->pos_cur_ref=vd->pos_first_ref;
      else
        if (vd->pos_next_ref!=0xFFFFFFFF)
          vd->pos_cur_ref=vd->pos_next_ref;
        else
        {
          scrollDown(vd,20);
          RenderPage(vd,0);
          if (vd->pos_next_ref!=0xFFFFFFFF)
            vd->pos_cur_ref=vd->pos_next_ref;
        }
      break;
    case RIGHT_BUTTON:
    case VOL_DOWN_BUTTON:
      scrollDown(vd,ScreenH()-20);
      vd->pos_cur_ref=0xFFFFFFFF;
      break;
    case LEFT_BUTTON:
    case VOL_UP_BUTTON:
      scrollUp(vd,ScreenH()-20);
      vd->pos_cur_ref=0xFFFFFFFF;
      break;
    case GREEN_BUTTON:
      {
        Init_Message(vd->Resource_Ex, NULL);
      }
      break;
      case '#':
        {
          if (vd->pos_cur_ref!=0xFFFFFFFF)
          {
            REFCACHE *rf=findReferencePos(vd,vd->pos_cur_ref);
            if (rf)
            {
              if(rf->id->mtype==MSG_GCHAT)
              {
              unsigned int au_nick_len = strlen(rf->id->muc_author);
              char *init_text = malloc(au_nick_len+3);
              zeromem(init_text, au_nick_len+3);
              strcpy(init_text, rf->id->muc_author);
              init_text[au_nick_len]=':';
              init_text[au_nick_len+1]=' ';
              init_text[au_nick_len+2]='\0';
              Init_Message(vd->Resource_Ex, init_text);
              mfree(init_text);
              }
            }
          }
        }
        break;
    case '0':
        // Убить список сообщений
        KillMsgList(vd->Resource_Ex->log);
        vd->Resource_Ex->log = NULL;
        vd->Resource_Ex->has_unread_msg=0;
        vd->Resource_Ex->total_msg_count=0;
        return 1;
        
    case LEFT_SOFT:
       Disp_Contact_Menu();
        break;
#ifndef NEWSGOLD
    case RED_BUTTON:
#endif
    case RIGHT_SOFT:
      return 1;
    }
  }
  DirectRedrawGUI();
  return(0);
}

extern void kill_data(void *p, void (*func_p)(void *));

int VIEWDATA_method8(void){return(0);}

int VIEWDATA_method9(void){return(0);}

const void * const VIEWDATA_methods[11]={
  (void *)VIEWDATA_onRedraw,	//Redraw
  (void *)VIEWDATA_onCreate,	//Create
  (void *)VIEWDATA_onClose,	  //Close
  (void *)VIEWDATA_onFocus,	  //Focus
  (void *)VIEWDATA_onUnfocus,	//Unfocus
  (void *)VIEWDATA_onKey,	    //OnKey
  0,
  (void *)kill_data,          //onDestroy,	//Destroy
  (void *)VIEWDATA_method8,
  (void *)VIEWDATA_method9,
  0
};

void VIEWDATA_ParseMessages(VIEWDATA *vd)
{
  if(!vd->Resource_Ex)return;
  int parsed_counter=0;
  LOG_MESSAGE* MessEx=vd->Resource_Ex->log;
  if(!MessEx)return;
  LockSched();
  // Цикл по всем сообщениям
  while(MessEx)
  {
    if(parsed_counter>=vd->OLD_MessList_Count)
    {
      WSHDR *temp_ws=AllocWS(strlen(MessEx->mess)*2);
      utf8_2ws(temp_ws,MessEx->mess,strlen(MessEx->mess)*2);
      AddStringItem(vd,"\n");
      RawInsertChar(vd,UTF16_INK_RGBA);
      RawInsertChar(vd,(MESSAGEWIN_CHAT_FONT.r<<8)+MESSAGEWIN_CHAT_FONT.g);
      RawInsertChar(vd,(MESSAGEWIN_CHAT_FONT.b<<8)+MESSAGEWIN_CHAT_FONT.a);
      switch(MessEx->mtype)
      {
      case MSG_ME:
        RawInsertChar(vd,UTF16_PAPER_RGBA);
        RawInsertChar(vd,(MESSAGEWIN_MY_BGCOLOR.r<<8)+MESSAGEWIN_MY_BGCOLOR.g);
        RawInsertChar(vd,(MESSAGEWIN_MY_BGCOLOR.b<<8)+MESSAGEWIN_MY_BGCOLOR.a);
        break;
      case MSG_CHAT:
        RawInsertChar(vd,UTF16_PAPER_RGBA);
        RawInsertChar(vd,(MESSAGEWIN_CH_BGCOLOR.r<<8)+MESSAGEWIN_CH_BGCOLOR.g);
        RawInsertChar(vd,(MESSAGEWIN_CH_BGCOLOR.b<<8)+MESSAGEWIN_CH_BGCOLOR.a);
        break;
      case MSG_SYSTEM:
        RawInsertChar(vd,UTF16_PAPER_RGBA);
        RawInsertChar(vd,(MESSAGEWIN_SYS_BGCOLOR.r<<8)+MESSAGEWIN_SYS_BGCOLOR.g);
        RawInsertChar(vd,(MESSAGEWIN_SYS_BGCOLOR.b<<8)+MESSAGEWIN_SYS_BGCOLOR.a);
        break;
      case MSG_STATUS:
        RawInsertChar(vd,UTF16_PAPER_RGBA);
        RawInsertChar(vd,(MESSAGEWIN_STATUS_BGCOLOR.r<<8)+MESSAGEWIN_STATUS_BGCOLOR.g);
        RawInsertChar(vd,(MESSAGEWIN_STATUS_BGCOLOR.b<<8)+MESSAGEWIN_STATUS_BGCOLOR.a);
        break;
      case MSG_GCHAT:
        {
          RGBA cl=parsed_counter%2==0?MESSAGEWIN_GCHAT_BGCOLOR_1:MESSAGEWIN_GCHAT_BGCOLOR_2;
          RawInsertChar(vd,UTF16_PAPER_RGBA);
          RawInsertChar(vd,(cl.r<<8)+cl.g);
          RawInsertChar(vd,(cl.b<<8)+cl.a);
        }
        break;
      }
  /*    
      if (MessEx==vd->Resource_Ex->log) // avatar
      {
        DEBUGC(vd->Resource_Ex->full_name);
        DEBUGC("\n");
        char fname[128];
        strcpy(fname,PATH_TO_AVATARS);
        int i=0;
        for(;i<strlen(vd->Resource_Ex->full_name);i++)
        {
          if (vd->Resource_Ex->full_name[i]==0x2F)
            break;
        }
        DEBUGS("i : %i\n",i);
        i+=strlen(fname);
        DEBUGS("i : %i\n",i);
        strcpy(fname+strlen(fname),vd->Resource_Ex->full_name);
//        *(fname+(strlen(fname)+i-1))=0;
        DEBUGC(fname);
        DEBUGC("\n");
        strcpy(fname+i,".jpg");
        DEBUGC(fname);
        DEBUGC("\n");

        int f;
        unsigned int err;
        int fsize;
        char *buf;
        FSTATS stat;
        if (GetFileStats(fname,&stat,&err)!=-1)
        {
          if ((fsize=stat.size)>0)
          {
            if ((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))!=-1)
            {
              buf=malloc(fsize+1);
              buf[fread(f,buf,fsize,&err)]=0;
              fclose(f,&err);
              AddPictureItem(vd,buf);
              mfree(buf);
            }
          }
        }
      }
      */
      //if (MessEx->mtype!=MSG_STATUS)
      {
        AddBeginRef(vd);
        vd->work_ref.id=MessEx;
      }
      AddTextItem(vd,temp_ws);
      //if (MessEx->mtype!=MSG_STATUS)
      AddEndRef(vd);
      FreeWS(temp_ws);
    }
    MessEx = MessEx->next;
    parsed_counter++;
  }
  UnlockSched();
  vd->OLD_MessList_Count=vd->Resource_Ex->total_msg_count;
}

// Отобразить список сообщений
void VIEWDATA_Display(TRESOURCE* ContEx)
{
  if(!ContEx)return;
  // Замутим гуй
  VIEW_GUI *mess_gui=malloc(sizeof(VIEW_GUI));
  zeromem(mess_gui, sizeof(VIEW_GUI));
  static const RECT Canvas={0,0,0,0};
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  mess_gui->gui.canvas=(void *)(&Canvas);
  mess_gui->gui.methods=(void *)VIEWDATA_methods;
  mess_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  Message_gui_ID = CreateGUI(mess_gui);
  mess_gui->vd.Resource_Ex=ContEx;
  mess_gui->vd.OLD_MessList_Count=0;
  VIEWDATA_ParseMessages(&mess_gui->vd);
}

// destructors.c
void FreeDynImgList(VIEWDATA *vd)
{
  OMS_DYNPNGLIST *dpl=vd->dynpng_list;
  vd->dynpng_list=NULL;
  while(dpl)
  {
    OMS_DYNPNGLIST *p=dpl;
    dpl=dpl->dp.next;
    if (p->dp.img)
    {
      mfree(p->dp.img->bitmap);
      mfree(p->dp.img);
    }
    mfree(p);
  }
}

void FreeViewData(VIEWDATA *vd)
{
  if (vd->ws) FreeWS(vd->ws);
  mfree(vd->ref_cache);
  vd->ref_cache=NULL;
  vd->ref_cache_size=0;
  mfree(vd->lines_cache);
  vd->lines_cache=NULL;
  mfree(vd->rawtext);
  vd->rawtext=NULL;
  vd->rawtext_size=0;
  FreeDynImgList(vd);
}


// additems.c
#define DP_IS_FRAME (-2)
#define DP_IS_NOINDEX (-1)
#define RAWTEXTCHUNK (16384)
#define REFCACHECHUNK (256)

void RawInsertChar(VIEWDATA *vd, int wchar)
{
  if ((vd->rawtext_size%RAWTEXTCHUNK)==0)
  {
    //Дошли до конца куска, реаллоцируем еще кусок
    vd->rawtext=realloc(vd->rawtext,(vd->rawtext_size+RAWTEXTCHUNK)*2);
  }
  //
  vd->rawtext[vd->rawtext_size++]=wchar;
}

void AddBeginRef(VIEWDATA *vd)
{
  vd->work_ref.begin=vd->rawtext_size;
  RawInsertChar(vd,UTF16_ENA_INVERT);
}

void AddEndRef(VIEWDATA *vd)
{
  RawInsertChar(vd,UTF16_DIS_INVERT);
  REFCACHE *p;
  if ((vd->ref_cache_size%REFCACHECHUNK)==0)
  {
    vd->ref_cache=realloc(vd->ref_cache,(vd->ref_cache_size+REFCACHECHUNK)*sizeof(REFCACHE));
  }
  p=vd->ref_cache+vd->ref_cache_size;
  memcpy(p,&(vd->work_ref),sizeof(REFCACHE));
  p->end=vd->rawtext_size;
  vd->ref_cache_size++;
  if (vd->pos_cur_ref==0xFFFFFFFF)
  {
    vd->pos_cur_ref=vd->work_ref.begin;
  }
  memset(&(vd->work_ref),0xFF,sizeof(REFCACHE));
}

void AddStringItem(VIEWDATA *vd, char *text)
{
  for (int i=0;i<strlen(text);i++)
  {
    unsigned int char8to16(int c);
    RawInsertChar(vd,char8to16(text[i]));
  }
}

void AddTextItem(VIEWDATA *vd, WSHDR *ws)
{
  for (int i=1;i<=ws->wsbody[0];i++)
  {
    RawInsertChar(vd,ws->wsbody[i]);
  }
}

//is_index >= 0 использовать последний
//is_index <0 - задать  принудительно
OMS_DYNPNGLIST *AddToDPngQueue(VIEWDATA *vd, IMGHDR *img, int is_index)
{
  int wchar, i, index;
  OMS_DYNPNGLIST *dpl;
  OMS_DYNPNGLIST *odp=malloc(sizeof(OMS_DYNPNGLIST));
  odp->dp.next=0;
  odp->dp.img=img;
  dpl=vd->dynpng_list;
  if (!dpl)
  {
    odp->dp.icon=GetPicNByUnicodeSymbol((wchar=FIRST_UCS2_BITMAP));
    odp->w_char=wchar;
    if (is_index>=0) odp->index=0;
    else odp->index=is_index;
    LockSched();
    vd->dynpng_list=odp;
    UnlockSched();
    RefreshGUI();
  }
  else
  {
    i=0;
    index=0;
    OMS_DYNPNGLIST *d;
    do
    {
      d=dpl;
      if (is_index>=0 && d->index>=0) index++;
      i++;
    }
    while((dpl=dpl->dp.next));
    wchar=FIRST_UCS2_BITMAP+i;
    odp->dp.icon=GetPicNByUnicodeSymbol(wchar);
    odp->w_char=wchar;
    if (is_index>=0)  odp->index=index;
    else odp->index=is_index;
    LockSched();
    d->dp.next=odp;
    UnlockSched();
  }
  return odp;
}
/*
void AddPictureItem(VIEWDATA *vd, void *picture)
{
  int wchar=0xE115;
  IMGHDR *img;
  OMS_DYNPNGLIST *dpl;
  if (picture)
  {
    if ((img=read_pngimg(picture)))
    {
      dpl=AddToDPngQueue(vd, img, 0);
      wchar=dpl->w_char;
    }
    else  if ((img=read_jpgimg(picture)))
    {
      dpl=AddToDPngQueue(vd, img, 0);
      wchar=dpl->w_char;
    }
  }
  RawInsertChar(vd,wchar);
}
*/
void AddPageEndItem(VIEWDATA *vd)
{
  AddStringItem(vd,"\n<Q>");
}
