#include "../inc/swilib.h"
#include "view.h"
#include "parse_oms.h"
#include "main.h"
#include "rect_patcher.h"
#include "local_ipc.h"
#include "display_utils.h"
#include "string_works.h"
#include "destructors.h"
#include "siemens_unicode.h"
#include "inet.h"
#include "urlstack.h"
#include "conf_loader.h"
#include "mainmenu.h"
#include "default_page.h"
#include "history.h"
#include "images.h"

#define DEFAULT_OMS "BalletMini.oms"

static void UpdateCSMname(void);
static int ParseInputFilename(const char *fn);

volatile int TERMINATED=0;
volatile int STOPPED=0;

int ENABLE_REDRAW=0;

extern void kill_data(void *p, void (*func_p)(void *));

const int minus11=-11;

const char ipc_my_name[32]=IPC_BALLETMINI_NAME;
IPC_REQ gipc;

int view_url_mode; //MODE_FILE, MODE_URL
char *view_url;
char *goto_url;
char *from_url;
char *goto_params;

int quit_reqired;

static const char percent_t[]="%t";

WSHDR *ws_console;

int maincsm_id;

char URLCACHE_PATH[256];
char OMSCACHE_PATH[256];
char AUTHDATA_FILE[256];
char BOOKMARKS_PATH[256];
char SEARCH_PATH[256];
char IMG_PATH[256];

char BALLET_PATH[256];

static void StartGetFile(int dummy, char *fncache)
{
  IPC_REQ *sipc;
  if (view_url_mode==MODE_FILE)
  {
    unsigned int err;
    char buf[1024];
    int i;
    int f=fopen(view_url,A_ReadOnly+A_BIN,P_READ,&err);
    if (f!=-1)
    {
      int fc=-1;
      if (fncache)
      {
        fc=fopen(fncache,A_ReadWrite+A_Create+A_Truncate+A_BIN,P_READ+P_WRITE,&err);
      }
      else
      {
        UpPageStack(); 
      }
      while((i=fread(f,buf,sizeof(buf),&err))>0)
      {
        if (fc!=-1)
        {
          fwrite(fc,buf,i,&err);
        }
        LockSched();
        if ((!TERMINATED)&&(!STOPPED))
        {
          sipc=malloc(sizeof(IPC_REQ));
          sipc->name_to=ipc_my_name;
          sipc->name_from=ipc_my_name;
          sipc->data=malloc(i+4);
          *((int *)(sipc->data))=i;
          memcpy(((char *)(sipc->data))+4,buf,i);
          GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_DATA_ARRIVED,sipc);
        }
        UnlockSched();
        if (TERMINATED||STOPPED) break;
      }
      if (fc!=-1) fclose(fc,&err);
      fclose(f,&err);
    }
    else
    {
      LockSched();
      ShowMSG(1,(int)"Can't open file!");
      UnlockSched();
    }
    mfree(fncache);
    STOPPED=1;
    SmartREDRAW();
  }
  if (view_url_mode==MODE_URL)
  {
    StartINET(view_url,fncache);
  }
}

char *collectItemsParams(VIEWDATA *vd, REFCACHE *rf)
{
  unsigned int pos=0;
  for (int i=0;i<vd->ref_cache_size;i++)
  {
    REFCACHE *prf=vd->ref_cache+i;
    switch (prf->tag)
    {
    case 's':
      {
        if (prf->multiselect)
        {
          int p=_rshort2(vd->oms+prf->id);
          int start=prf->id+2+p+3+1;
          for (int i=0;i<prf->size;i++)
          {
            if (((char*)prf->data)[i])
            {
              // write
              p=_rshort2(vd->oms+start);
              start=start+2+p;
              pos+=_rshort2(vd->oms+prf->id)+_rshort2(vd->oms+start)+2;
              p=_rshort2(vd->oms+start);
              start=start+2+p+2;
            }
            else
            {
              // skip
              p=_rshort2(vd->oms+start);
              start=start+2+p;
              p=_rshort2(vd->oms+start);
              start=start+2+p+2;
            }
          }
        }
        else
        {
          pos+=_rshort2(vd->oms+prf->id)+1+_rshort2(vd->oms+prf->id2)+1;
        }
      }
      break;
    case 'c':
    case 'r':
      if (vd->rawtext[prf->begin+1]==vd->img_rbtn_on||vd->rawtext[prf->begin+1]==vd->img_cbtn_on)
        pos+=_rshort2(vd->oms+prf->id)+1+_rshort2(vd->oms+prf->value)+1;
      break;
    case 'i':
    case 'u':
      {
        if (prf!=rf) break;
        pos+=_rshort2(vd->oms+prf->id)+2;
        char *c=extract_omstr(vd,prf->value);
        WSHDR *ws=AllocWS(256);
        oms2ws(ws,c,strlen(c));
        mfree(c);
        char *b=c=(char *)malloc(ws->wsbody[0]+3);
        for (int i=0; i<ws->wsbody[0]; i++) *c++=char16to8(ws->wsbody[i+1]);
        *c=0;
        b=ToWeb(b,1);
        pos+=strlen(b);
        mfree(b);
        FreeWS(ws);
      }
      break;
    case 'p':
    case 'x':
      {
        pos+=_rshort2(vd->oms+prf->id)+2;
        char *c;
        char *b=c=(char *)malloc(((WSHDR *)prf->data)->wsbody[0]+3);
        for (int i=0; i<((WSHDR *)prf->data)->wsbody[0]; i++) *c++=char16to8(((WSHDR *)prf->data)->wsbody[i+1]);
        *c=0;
        b=ToWeb(b,1);
        pos+=strlen(b);
        mfree(b);
      }
      break;
    }
  }
//  DEBUGS("pos:%i\r\n",pos);
  char *s=malloc(pos+1);
  pos=0;
  for (int i=0;i<vd->ref_cache_size;i++)
  {
    REFCACHE *prf=vd->ref_cache+i;
    switch (prf->tag)
    {
    case 's':
      {
        if (prf->multiselect)
        {
          int p=_rshort2(vd->oms+prf->id);
          int start=prf->id+2+p+3+1;
          for (int i=0;i<prf->size;i++)
          {
            if (((char*)prf->data)[i])
            {
              // write
              p=_rshort2(vd->oms+start);
              start=start+2+p;
              s[pos]='&';
              pos++;
              char *c=extract_omstr(vd,prf->id);
              memcpy(s+pos,c,strlen(c));
              pos+=strlen(c);
              mfree(c);
              s[pos]='=';
              pos++;
              c=extract_omstr(vd,start);
              memcpy(s+pos,c,strlen(c));
              pos+=strlen(c);
              mfree(c);
              p=_rshort2(vd->oms+start);
              start=start+2+p+2;
            }
            else
            {
              // skip
              p=_rshort2(vd->oms+start);
              start=start+2+p;
              p=_rshort2(vd->oms+start);
              start=start+2+p+2;
            }
          }
        }
        else
        {
          s[pos]='&';
          pos++;
          char *c=extract_omstr(vd,prf->id);
          memcpy(s+pos,c,strlen(c));
          pos+=strlen(c);
          mfree(c);
          s[pos]='=';
          pos++;
          c=extract_omstr(vd,prf->id2);
          memcpy(s+pos,c,strlen(c));
          pos+=strlen(c);
          mfree(c);
        }
      }
      break;
    case 'c':
    case 'r':
      {
        if (vd->rawtext[prf->begin+1]==vd->img_rbtn_on||vd->rawtext[prf->begin+1]==vd->img_cbtn_on)
        {
          s[pos]='&';
          pos++;
          char *c=extract_omstr(vd,prf->id);
          memcpy(s+pos,c,strlen(c));
          pos+=strlen(c);
          mfree(c);
          s[pos]='=';
          pos++;
          c=extract_omstr(vd,prf->value);
          memcpy(s+pos,c,strlen(c));
          pos+=strlen(c);
          mfree(c);
        }
      }
      break;
    case 'i':
    case 'u':
      {
        if (prf!=rf) break;
        s[pos]='&';
        pos++;
        char *c=extract_omstr(vd,prf->id);
        memcpy(s+pos,c,strlen(c));
        pos+=strlen(c);
        mfree(c);
        s[pos]='=';
        pos++;
        c=extract_omstr(vd,prf->value);
        WSHDR *ws=AllocWS(256);
        oms2ws(ws,c,strlen(c));
        mfree(c);
        char *b=c=(char *)malloc(ws->wsbody[0]+3);
        for (int i=0; i<ws->wsbody[0]; i++) *c++=char16to8(ws->wsbody[i+1]);
        *c=0;
        b=ToWeb(b,1);
        memcpy(s+pos,b,strlen(b));
        pos+=strlen(b);
        mfree(b);
        FreeWS(ws);
      }
      break;
    case 'p':
    case 'x':
      {
        s[pos]='&';
        pos++;
        char *c=extract_omstr(vd,prf->id);
        memcpy(s+pos,c,strlen(c));
        pos+=strlen(c);
        mfree(c);
        s[pos]='=';
        pos++;
        char *b=c=(char *)malloc(((WSHDR *)prf->data)->wsbody[0]+3);
        for (int i=0; i<((WSHDR *)prf->data)->wsbody[0]; i++) *c++=char16to8(((WSHDR *)prf->data)->wsbody[i+1]);
        *c=0;
        b=ToWeb(b,1);
        memcpy(s+pos,b,strlen(b));
        pos+=strlen(b);
        mfree(b);
      }
      break;
    }
  }
//  DEBUGS("pos:%i\r\n",pos);
  s[pos]=0;
//  unsigned int ul;
//  int f;
//  if ((f=fopen("0:\\zbin\\balletmini\\dump.txt",A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
//  {
//    fwrite(f,s,pos,&ul);
//    fclose(f,&ul);
//  }
  return s;
}

//===============================================================================================

static void method0(VIEW_GUI *data)
{
  int scr_w=ScreenW()-1;
  int scr_h=ScreenH()-1;
  
  VIEWDATA *vd=data->vd;
  
  if (data->gui.state==2)
  {
    DrawRectangle(0,0,scr_w,scr_h,0,
      GetPaletteAdrByColorIndex(0),
      GetPaletteAdrByColorIndex(0));
    RenderPage(vd,1);
//    DrawString(ws_console,0,0,scr_w,20,
//		  FONT_SMALL,TEXT_NOFORMAT,
//		  GetPaletteAdrByColorIndex(1),
//      GetPaletteAdrByColorIndex(0));
    extern int connect_state;
    if (!STOPPED)
    {
      int w1, h1;
      if (connect_state)
      {
        switch(connect_state)
        {
        case 1: case 2: case 3:
//          wsprintf(data->ws1,percent_t,"����������...");
//          break;
//        case 2:
//          wsprintf(data->ws1,percent_t,"���������...");
          wstrcpy(data->ws1, ws_console);
          //wsprintf(data->ws1,percent_t,);
          break;
//        case 3:
//          wsprintf(data->ws1,percent_t,"��������...");
//          break;
        }
      }
      wsprintf(data->ws2,percent_t,"����");
      
      h1=scr_h-GetFontYSIZE(FONT_SMALL)-2;
      w1=scr_w-Get_WS_width(data->ws2,FONT_SMALL)-2;
      DrawRectangle(0,h1,w1,scr_h,0,
        GetPaletteAdrByColorIndex(1),
        GetPaletteAdrByColorIndex(0));
      DrawRectangle(w1+1,h1,scr_w,scr_h,0,
        GetPaletteAdrByColorIndex(1),
        GetPaletteAdrByColorIndex(0));
      if ((view_url_mode==MODE_FILE && vd->loaded_sz<vd->page_sz) ||
      (view_url_mode==MODE_URL && connect_state==3 && vd->loaded_sz<vd->page_sz))
      {
        DrawRectangle(1,h1+1,vd->loaded_sz*(w1-1)/vd->page_sz,scr_h-1,0,
          GetPaletteAdrByColorIndex(2),
          GetPaletteAdrByColorIndex(2));
        wsprintf(data->ws1,"%uB/%uB",vd->loaded_sz,vd->page_sz);
      }
      DrawString(data->ws1,0,h1+2,w1,scr_h,FONT_SMALL,TEXT_ALIGNMIDDLE,
        GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));   
      DrawString(data->ws2,w1+1,h1+2,scr_w,scr_h,FONT_SMALL,TEXT_ALIGNMIDDLE,
        GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));      
      
//      DrawString(ws_console,0,0,scr_w,20,
//		    FONT_SMALL,TEXT_NOFORMAT,
//		    GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(0));
    }
  }
}

static void method1(VIEW_GUI *data,void *(*malloc_adr)(int))
{
  VIEWDATA *vd=malloc(sizeof(VIEWDATA));
  zeromem(vd,sizeof(VIEWDATA));
  vd->ws=AllocWS(32767);
  vd->pos_cur_ref=0xFFFFFFFF; //��� ������ �� ������� ������
  *((unsigned short *)(&vd->current_tag_d))=0xFFFF;
  data->vd=vd;
  data->ws1=AllocWS(128);
  data->ws2=AllocWS(128);
  data->gui.state=1;
  STOPPED=0;
  if ((vd->cached=data->cached))
  {
    SUBPROC((void *)StartGetFile,0,NULL);
  }
  else
  {
    SUBPROC((void *)StartGetFile,1,PushPageToStack());
  }
}

void FreeViewUrl(void)
{
  freegstr(&view_url);
}

static void method2(VIEW_GUI *data,void (*mfree_adr)(void *))
{
  STOPPED=1;
  SUBPROC((void*)StopINET);
  FreeViewData(data->vd);
  data->vd=NULL;
  FreeWS(data->ws1);
  FreeWS(data->ws2);
  data->gui.state=0;
  FreeViewUrl();
}

static void method3(VIEW_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
#ifdef ELKA
  DisableIconBar(1);
#endif
  PNGTOP_DESC *pltop=PNG_TOP();
  pltop->dyn_pltop=&data->vd->dynpng_list->dp;
  ENABLE_REDRAW=1;
  DisableIDLETMR();
  data->gui.state=2;
}

static void method4(VIEW_GUI *data,void (*mfree_adr)(void *))
{
#ifdef ELKA
  DisableIconBar(0);
#endif
  PNGTOP_DESC *pltop=PNG_TOP();
  pltop->dyn_pltop=NULL;
  ENABLE_REDRAW=0;
  if (data->gui.state!=2)
    return;
  data->gui.state=1;
}

static void RunOtherCopyByURL(const char *url)
{
  char fname[256];
  TDate d;
  TTime t;
  int f;
  unsigned int err;
  WSHDR *ws;
  GetDateTime(&d,&t);
  sprintf(fname,"%s%d%d%d%d%d%d.url",URLCACHE_PATH,d.year,d.month,d.day,t.hour,t.min,t.sec);
  f=fopen(fname,A_Create+A_Truncate+A_BIN+A_ReadWrite,P_READ+P_WRITE,&err);
  if (f!=-1)
  {
    fwrite(f,url,strlen(url),&err);
    fclose(f,&err);
    ws=AllocWS(256);
    str_2ws(ws,fname,255);
    ExecuteFile(ws,NULL,NULL);
    FreeWS(ws);
    unlink(fname,&err);
  }
}

static int method5(VIEW_GUI *data,GUI_MSG *msg)
{
  if (quit_reqired)
  {
    quit_reqired=0;
    return 0xFF;
  }
  VIEWDATA *vd=data->vd;
  REFCACHE *rf;
  int m=msg->gbsmsg->msg;
  if ((m==KEY_DOWN)||(m==LONG_PRESS))
  {
    switch(msg->gbsmsg->submess)
    {
    case ENTER_BUTTON:
      rf=FindReference(vd,vd->pos_cur_ref);
      if (rf)
      {
        switch(rf->tag)
        {
        case 'Z':
          if (rf->id!=_NOREF)
          {
            char *c=extract_omstr(vd,rf->id);
            unsigned int l=_rshort2(vd->oms+rf->id);
            goto_url=malloc(l-strlen(c)+1);
            strcpy(goto_url,c+strlen(c)+1);
            mfree(c);
            return 0xFF;
          }
          break;
        case 'L':
          if (rf->id!=_NOREF)
          {
            // 1/http:        �� ������ ����� ������
            // 0/http:        �� ���������
            goto_url=extract_omstr(vd,rf->id);
            // 0/javascript:  upload data
            if (!strncmp("0/javascript",goto_url,12))
            {
              from_url=malloc(strlen(vd->pageurl)+1);
              strcpy(from_url,vd->pageurl);
              goto_params=collectItemsParams(vd,rf);
            }
            return 0xFF;
          }
          break;
        case 'r':
          {
            REFCACHE *rfp;
            int i;
            if (vd->rawtext[rf->begin+1]!=vd->img_rbtn_off) break;
            vd->rawtext[rf->begin+1]=vd->img_rbtn_on;
            i=0;
            while((i=FindReferenceById(vd,rf->id,i))>=0)
            {
              rfp=vd->ref_cache+i;
              if (rfp!=rf)
                if (vd->rawtext[rfp->begin+1]==vd->img_rbtn_on)
                  vd->rawtext[rfp->begin+1]=vd->img_rbtn_off;
              i++;
            }
          }
          if (!rf->no_upload)
          {
            goto_url=malloc(strlen(vd->pageurl)+1);
            strcpy(goto_url,vd->pageurl);
            from_url=malloc(strlen(vd->pageurl)+1);
            strcpy(from_url,vd->pageurl);
            goto_params=collectItemsParams(vd,rf);
            return 0xFF;
          }
          break;
        case 'c':
          if (vd->rawtext[rf->begin+1]==vd->img_cbtn_on)
            vd->rawtext[rf->begin+1]=vd->img_cbtn_off;
          else
            vd->rawtext[rf->begin+1]=vd->img_cbtn_on;
          if (!rf->no_upload)
          {
            goto_url=malloc(strlen(vd->pageurl)+1);
            strcpy(goto_url,vd->pageurl);
            from_url=malloc(strlen(vd->pageurl)+1);
            strcpy(from_url,vd->pageurl);
            goto_params=collectItemsParams(vd,rf);
            return 0xFF;
          }
          break;
        case 'x':
        case 'p':
          CreateInputBox(vd,rf);
          break;
        case 'i':
        case 'u':
          goto_url=malloc(strlen(vd->pageurl)+1);
          strcpy(goto_url,vd->pageurl);
          from_url=malloc(strlen(vd->pageurl)+1);
          strcpy(from_url,vd->pageurl);
          goto_params=collectItemsParams(vd,rf);
          return 0xFF;
        case 's':
          ChangeMenuSelection(vd, rf);
          break;
        default:
          {
            char c[128];
            sprintf(c,"Reftype: \'%c\' under construction!",rf->tag);
            ShowMSG(1,(int)c);
          }
        break;
        }
      }
      else
      {
	      ShowMSG(1,(int)"RF empty!");
      }
      break;
    case UP_BUTTON:
      if (vd->pos_cur_ref!=vd->pos_first_ref&&vd->pos_first_ref==vd->pos_last_ref)
        vd->pos_cur_ref=0xFFFFFFFF;
      if (vd->pos_cur_ref==0xFFFFFFFF&&vd->pos_last_ref!=0xFFFFFFFF)
        vd->pos_cur_ref=vd->pos_last_ref;
      else
        if (vd->pos_prev_ref!=0xFFFFFFFF)
          vd->pos_cur_ref=vd->pos_prev_ref;
        else
          scrollUp(vd,20);
      break;
    case DOWN_BUTTON:
      if (vd->pos_cur_ref!=vd->pos_first_ref&&vd->pos_first_ref==vd->pos_last_ref)
        vd->pos_cur_ref=0xFFFFFFFF;
      if (vd->pos_cur_ref==0xFFFFFFFF&&vd->pos_first_ref!=0xFFFFFFFF)
        vd->pos_cur_ref=vd->pos_first_ref;
      else
        if (vd->pos_next_ref!=0xFFFFFFFF)
          vd->pos_cur_ref=vd->pos_next_ref;
        else
          scrollDown(vd,20);
      break;
    case RIGHT_BUTTON:
    case VOL_DOWN_BUTTON:
      scrollDown(vd,ScreenH()-20);
      if (vd->pos_cur_ref<vd->pos_first_ref)
        vd->pos_cur_ref=0xFFFFFFFF;
      break;
    case LEFT_BUTTON:
    case VOL_UP_BUTTON:
      scrollUp(vd,ScreenH()-20);
      if (vd->pos_cur_ref>vd->pos_last_ref)
        vd->pos_cur_ref=0xFFFFFFFF;
      break;
    case LEFT_SOFT:
      STOPPED=1;
      CreateMainMenu(vd);
      break;
    case RIGHT_SOFT:
      if (STOPPED)
      {
        mfree(PopPageFromStack());
        return 0xFE;
      }
      else
      {
        if (view_url_mode==MODE_URL)
        {
          SUBPROC((void*)StopINET);
        }
        else
        {
          STOPPED=1;
        }
        break;
      }
    case GREEN_BUTTON:
      rf=FindReference(vd,vd->pos_cur_ref);
      if (rf)
      {
        if (rf->tag=='L')
        {
          //ShowMSG(0x10,(int)(rf->id));
          if (rf->id!=_NOREF)
          {
            char *s=extract_omstr(vd,rf->id);
            RunOtherCopyByURL(s+2);
            mfree(s);
          }
        }
      }
      break;
    case 0x31: // '1'
      {
        //Dump OMS
        unsigned int ul;
        int f;
        if ((f=fopen("0:\\zbin\\balletmini\\dumpoms.txt",A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
        {
          fwrite(f,vd->oms,vd->oms_size,&ul);
          fclose(f,&ul);
        }
      }
      break;
    case 0x34: // '4'
      {
        //Dump RAWTEXT
        unsigned int ul;
        int f;
        if ((f=fopen("0:\\zbin\\balletmini\\dumpraw.txt",A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
        {
          fwrite(f,vd->rawtext,vd->rawtext_size*2,&ul);
          fclose(f,&ul);
        }
      }
      break;
    case 0x37: // '7'
      {
        //Dump REFCACHE
        unsigned int ul;
        int f;
        if ((f=fopen("0:\\zbin\\balletmini\\dumpref.txt",A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
        {
          char c[256];
          sprintf(c,"\nref_cache_size : %i\n",vd->ref_cache_size);
          fwrite(f,c,strlen(c),&ul);
          sprintf(c,  "oms_size       : %i\n",vd->oms_size);
          fwrite(f,c,strlen(c),&ul);
          sprintf(c,  "page_sz        : %i\n",vd->page_sz);
          fwrite(f,c,strlen(c),&ul);
          sprintf(c,  "loaded_sz      : %i\n\n",vd->loaded_sz);
          fwrite(f,c,strlen(c),&ul);
          for (int i=0;i<vd->ref_cache_size;i++)
          {
            REFCACHE *rf=vd->ref_cache+i;
            sprintf(c,"\nREF : %i\n",i);
            fwrite(f,c,strlen(c),&ul);
            sprintf(c,"  tag:       %c\n",rf->tag);
            fwrite(f,c,strlen(c),&ul);
            sprintf(c,"  id:        %u",rf->id);
            fwrite(f,c,strlen(c),&ul);
            if (rf->id!=_NOREF)
            {
              char *s=extract_omstr(vd,rf->id);
              for (int to=_rshort2(vd->oms+rf->id)-1;to;to--) if (s[to]==NULL) s[to]=' ';
              sprintf(c,"   %s",s);
              fwrite(f,c,strlen(c),&ul);
              mfree(s);
            }
            fwrite(f,"\n",1,&ul);
            sprintf(c,"  id2:       %u",rf->id2);
            fwrite(f,c,strlen(c),&ul);
            if (rf->id2!=_NOREF)
            {
              char *s=extract_omstr(vd,rf->id2);
              for (int to=_rshort2(vd->oms+rf->id)-1;to;to--) if (s[to]==NULL) s[to]=' ';
              sprintf(c,"   %s",s);
              fwrite(f,c,strlen(c),&ul);
              mfree(s);
            }
            fwrite(f,"\n",1,&ul);
            sprintf(c,"  value:     %u",rf->value);
            fwrite(f,c,strlen(c),&ul);
            if (rf->value!=_NOREF)
            {
              char *s=extract_omstr(vd,rf->value);
              for (int to=_rshort2(vd->oms+rf->id)-1;to;to--) if (s[to]==NULL) s[to]=' ';
              sprintf(c,"   %s",s);
              fwrite(f,c,strlen(c),&ul);
              mfree(s);
            }
            fwrite(f,"\n",1,&ul);
            sprintf(c,"  begin:     %u\n",rf->begin);
            fwrite(f,c,strlen(c),&ul);
            sprintf(c,"  end:       %u\n",rf->end);
            fwrite(f,c,strlen(c),&ul);
            sprintf(c,"  upload:    %s\n",rf->no_upload?"false":"true");
            fwrite(f,c,strlen(c),&ul);
            if (rf->tag=='s')
            {
              sprintf(c,"  multiple:  %s\n",rf->multiselect?"true":"false");
              fwrite(f,c,strlen(c),&ul);
              sprintf(c,"  size:    %i ",rf->size);
              fwrite(f,c,strlen(c),&ul);
              fwrite(f,rf->data,rf->size,&ul);
              fwrite(f,"\n",1,&ul);
            }
          }
          fclose(f,&ul);
        }
      }
      break;
    }
  }
  DirectRedrawGUI();
  return(0);
}

static int method8(void){return(0);}

static int method9(void){return(0);}

static const void * const gui_methods[11]={
  (void *)method0,  //Redraw
  (void *)method1,  //Create
  (void *)method2,  //Close
  (void *)method3,  //Focus
  (void *)method4,  //Unfocus
  (void *)method5,  //OnKey
  0,
  (void *)kill_data, //method7, //Destroy
  (void *)method8,
  (void *)method9,
  0
};

static int CreateViewGUI(int cached)
{
  static const RECT Canvas={0,0,0,0};
  VIEW_GUI *view_gui=malloc(sizeof(VIEW_GUI));
  zeromem(view_gui,sizeof(VIEW_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  view_gui->gui.canvas=(void *)(&Canvas);
//  view_gui->gui.flag30=2;
  view_gui->gui.methods=(void *)gui_methods;
  view_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  view_gui->cached=cached;
  return CreateGUI(view_gui);
}

static void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  ws_console=AllocWS(1024);
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->view_id=CreateViewGUI(0);
}

static void KillAll(void)
{
  FreePageStack();
  FreeWS(ws_console);
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  KillAll();
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  TERMINATED=1;
  mfree(goto_url);
  SUBPROC((void *)Killer);
}

void GotoLink(void)
{
  LockSched();
  if (!TERMINATED)
  {
    IPC_REQ *sipc;
    sipc=malloc(sizeof(IPC_REQ));
    sipc->name_to=ipc_my_name;
    sipc->name_from=ipc_my_name;
    sipc->data=NULL;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_GOTO_URL,sipc);
  }
  UnlockSched();
}

void GotoFile(void)
{
  LockSched();
  if (!TERMINATED)
  {
    IPC_REQ *sipc;
    sipc=malloc(sizeof(IPC_REQ));
    sipc->name_to=ipc_my_name;
    sipc->name_from=ipc_my_name;
    sipc->data=NULL;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_GOTO_FILE,sipc);
  }
  UnlockSched();
}

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  int csm_result=1;
  //IPC
  if (msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
      {
        switch (msg->submess)
        {
        case IPC_DATA_ARRIVED:
          //���� ������� ���� ����������� ���������, ������ ��������� �����
          if (ipc->name_from==ipc_my_name)
          {
            VIEW_GUI *p=FindGUIbyId(csm->view_id,NULL);
            VIEWDATA *vd;
            int len=*((int*)(ipc->data));
            char *buf=((char*)(ipc->data))+4;
            if (p)
            {
              vd=p->vd;
              if (vd)
              {
                OMS_DataArrived(vd,buf,len);
                if (IsGuiOnTop(csm->view_id)) DirectRedrawGUI();
              }
            }
            mfree(ipc->data);
            mfree(ipc);
            csm_result=0;  //���������� ��������� 
          }
          break;
        case IPC_GOTO_URL:
          if (ipc->name_from==ipc_my_name)
          {
            mfree(ipc);
            FreeViewUrl();
            view_url=goto_url;
            view_url_mode=MODE_URL;
            goto_url=NULL;
            UpdateCSMname();
            csm->view_id=CreateViewGUI(0);
            csm_result=0;  //���������� ��������� 
          }
          break;
        case IPC_GOTO_FILE:
          if (ipc->name_from==ipc_my_name)
          {
            mfree(ipc);
            if (ParseInputFilename(goto_url))
            {
              UpdateCSMname();
              csm->view_id=CreateViewGUI(1);
            }
            mfree(goto_url);
            goto_url=NULL;
            csm_result=0;   //���������� ��������� 
          }
          break;
        }
      }
    }
  }
  if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"BalletMini config updated!");
      InitConfig();
    }    
  }
  ParseSocketMsg(msg);
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->view_id)
    {
      switch((int)msg->data1)
      {
      case 0xFE:
        //������� ���� �� ����� �����
        if ((goto_url=PopPageFromStack()))
        {
          SUBPROC((void*)GotoFile);
          break;
        }
        goto L_CLOSE;
      case 0xFF:
        if (goto_url)
        {
          //���� ���� �����
          SUBPROC((void*)GotoLink);
          break;
        }
        else
          goto L_CLOSE;
      default:
      L_CLOSE:
        csm->csm.state=-3;
        break;
      }
    }
    if ((int)msg->data0==csm->goto_url)
    {
      if ((int)msg->data1==0xFF)
      {
        GeneralFunc_flag1(csm->view_id,0xFF);        
      }
      csm->goto_url=0;
    }
    if ((int)msg->data0==csm->sel_bmk)
    {
      if ((int)msg->data1==0xFF)
      {
        GeneralFunc_flag1(csm->view_id,0xFF);        
      }
      csm->sel_bmk=0;
    }
    if ((int)msg->data0==csm->main_menu_id)
    {
      csm->main_menu_id=0;
    }
  }
  return(csm_result);
}

static unsigned short maincsm_name_body[140];

static const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

static void UpdateCSMname(void)
{
  WSHDR *ws=AllocWS(256);
  switch(view_url_mode)
  {
  case MODE_FILE:
    str_2ws(ws,view_url,255);
    break;
  case MODE_URL:
    ascii2ws(ws,view_url+2);
    break;
  }
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"BM: %w",ws);
  FreeWS(ws);
}

int ReadUrlFile(char *url_file)
{
  int f;
  unsigned int err;
  int fsize;
  char *buf, *s;
  FSTATS stat;
  if (GetFileStats(url_file,&stat,&err)==-1) return 0;
  if ((fsize=stat.size)<=0) return 0;
  if ((f=fopen(url_file,A_ReadOnly+A_BIN,P_READ,&err))==-1) return 0;
  buf=malloc(fsize+3);
  buf[0]='0';
  buf[1]='/';
  buf[fread(f,buf+2,fsize,&err)+2]=0;
  fclose(f,&err);
  s=buf;
  while(*s>32) s++;
  *s++=0;
  view_url=realloc(buf,s-buf);
  view_url_mode=MODE_URL;
  return (1);
}

static int ParseInputFilename(const char *fn)
{
  char *s=strrchr(fn,'.');
  FreeViewUrl();
  if (s)
  {
    s++;
    if (!strcmp_nocase(s,"oms"))
    {
      view_url=globalstr(fn);
      view_url_mode=MODE_FILE;
    }
    else
      if (!strcmp_nocase(s,"url"))
      {
        if (!ReadUrlFile((char *)fn)) return (0);
      }
      else return 0;
    return 1;
  }
  return 0;
}

char AUTH_PREFIX[64];
char AUTH_CODE[128];

int LoadAuthCode(void)
{
  int f;
  unsigned int err;
  int fsize;
  char *buf;
  char *s;
  int c;
  FSTATS stat;
  if (GetFileStats(AUTHDATA_FILE,&stat,&err)==-1) return 0;
  if ((fsize=stat.size)<=0) return 0;
  if ((f=fopen(AUTHDATA_FILE,A_ReadOnly+A_BIN,P_READ,&err))==-1) return 0;
  buf=malloc(fsize+1);
  buf[fread(f,buf,fsize,&err)]=0;
  fclose(f,&err);
  s=buf;
  f=0;
  err=0;
  while((c=*s++)>=32)
  {
    if (c=='.') break;
    if (f<63) AUTH_PREFIX[f++]=c;
  }
  if (c)
  {
    while((c=*s)<32)
    {
      if (!c) goto LEND;
      s++;
    }
    f=0;
    while((c=*s++)>32)
    {
      if (c=='.') break;
      if (f<127) AUTH_CODE[f++]=c;
    }
    err=1;
  }
LEND:
  mfree(buf);
  return err;
}

void GenerateFile(char *path, char *name, unsigned char *from, unsigned size)
{
  unsigned ul;
  int f;
  FSTATS stat;
  char *pathbuf;

  pathbuf = (char *)malloc(strlen(path) + strlen(name) + 1);
  strcpy(pathbuf, path); strcat(pathbuf, name);
  
  stat.size = 0;
  GetFileStats(pathbuf,&stat,&ul); 
  ///if (GetFileStats(pathbuf,&stat,&ul)!=-1) return;
  if (stat.size>0) return;

  unlink(pathbuf,&ul);
  f = fopen(pathbuf,A_WriteOnly+A_Create+A_BIN,P_READ+P_WRITE,&ul);
  if (f!=-1)
  {
    fwrite(f,from,size,&ul);
    fclose(f,&ul);
  }
  mfree(pathbuf);

}

int main(const char *exename, const char *filename)
{
  char dummy[sizeof(MAIN_CSM)];
  char *pathbuf;
  unsigned int ul;
  char *path=strrchr(exename,'\\');
  int l;
  if (!path) return 0; //����� �����-��
  path++;
  l=path-exename;
  InitConfig();
  memcpy(URLCACHE_PATH,exename,l);
  strcat(URLCACHE_PATH,"UrlCache");
  memcpy(OMSCACHE_PATH,exename,l);
  strcat(OMSCACHE_PATH,"OmsCache");
  memcpy(AUTHDATA_FILE,exename,l);
  strcat(AUTHDATA_FILE,"AuthCode");
  memcpy(BOOKMARKS_PATH,exename,l);
  strcat(BOOKMARKS_PATH,"Bookmarks");
  memcpy(IMG_PATH,exename,l);
  strcat(IMG_PATH,"img");
  
  memcpy(BALLET_PATH,exename,l);

  memcpy(SEARCH_PATH,exename,l);
  strcat(SEARCH_PATH,"Search");

  //Create folders if not exists
  if (!isdir(URLCACHE_PATH,&ul))
    mkdir(URLCACHE_PATH,&ul);
  if (!isdir(OMSCACHE_PATH,&ul))
    mkdir(OMSCACHE_PATH,&ul);
  if (!isdir(BOOKMARKS_PATH,&ul))
    mkdir(BOOKMARKS_PATH,&ul);
  if (!isdir(SEARCH_PATH,&ul))
    mkdir(SEARCH_PATH,&ul);
  if (!isdir(IMG_PATH,&ul))
    mkdir(IMG_PATH,&ul);
  
  strcat(URLCACHE_PATH,"\\");
  strcat(OMSCACHE_PATH,"\\");
  strcat(BOOKMARKS_PATH,"\\");
  strcat(SEARCH_PATH,"\\");
  strcat(IMG_PATH,"\\");
  
  CheckHistory("http://perk11.info/elf");

  GenerateFile(IMG_PATH, RADIO_BTTN_CLKD, radio_bttn_clkd_png, radio_bttn_clkd_png_size);
  GenerateFile(IMG_PATH, RADIO_BTTN,      radio_bttn_png,      radio_bttn_png_size);
  GenerateFile(IMG_PATH, BUTTON_CLKD,     button_clkd_png,     button_clkd_png_size);
  GenerateFile(IMG_PATH, BUTTON,          button_png,          button_png_size);
  GenerateFile(IMG_PATH, TEXT_FORM,       text_form_png,       text_form_png_size);
  GenerateFile(IMG_PATH, LIST,            list_png,            list_png_size);

  
  if (!LoadAuthCode())
  {
    LockSched();
    ShowMSG(1,(int)"BM: Can't load AuthCode!");
    UnlockSched();
    SUBPROC((void *)Killer);
    return 0;
  }

  if (ParseInputFilename(filename))
  {
    UpdateCSMname();
    LockSched();
    maincsm_id=CreateCSM(&MAINCSM.maincsm,dummy,0);
    UnlockSched();
  }
  else
  {
    
    GenerateFile(OMSCACHE_PATH, DEFAULT_OMS, default_page,default_page_size);

    /*unlink(pathbuf,&ul);
    f=fopen(pathbuf,A_WriteOnly+A_Create+A_BIN,P_READ+P_WRITE,&ul);
    if (f!=-1)
    {
      fwrite(f,default_page,default_page_size,&ul);
      fclose(f,&ul);
    }*/
//    mfree(pathbuf);
    
    pathbuf = malloc(strlen(OMSCACHE_PATH) + strlen(DEFAULT_OMS) + 1);
    strcpy(pathbuf, OMSCACHE_PATH); strcat(pathbuf, DEFAULT_OMS);
    view_url=pathbuf;
    view_url_mode=MODE_FILE;
    UpdateCSMname();
    LockSched();
    maincsm_id=CreateCSM(&MAINCSM.maincsm,dummy,0);
    UnlockSched();
  }
  return 0;
}
