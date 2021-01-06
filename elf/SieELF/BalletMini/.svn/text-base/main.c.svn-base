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
#include "history.h"
#include "file_works.h"
#include "lang.h"
#include "../inc/sieget_ipc.h"
#include "url_utils.h"

extern const char DEFAULT_PARAM[128];
extern const int length;

static void UpdateCSMname(void);
static int ParseInputFilename(const char *fn);

volatile int TERMINATED=0;
volatile int STOPPED=0;

int ENABLE_REDRAW=0;

extern void kill_data(void *p, void (*func_p)(void *));

const int minus11=-11;

const char ipc_my_name[32]=IPC_BALLETMINI_NAME;
const char sieget_ipc_name[32] = SIEGET_IPC_NAME;

IPC_REQ sieget_ipc;

int view_url_mode;
char *view_url;
char *goto_url;
char *from_url;
char *goto_params;

WSHDR *ws_console;

int maincsm_id;

char BALLET_PATH[256];
char BALLET_EXE[256];

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
      ShowMSG(1,(int)lgpData[LGP_CantOpenFile]);
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
  if (view_url_mode==MODE_BOOKMARKS)
  {
    MAIN_CSM *main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id);
    if (main_csm)
    {
      STOPPED=1;
      main_csm->sel_bmk=CreateBookmarksMenu();
    }
  }
  if (view_url_mode==MODE_NONE)
  {
//    MAIN_CSM *main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id);
//    if (main_csm)
//    {
//      VIEW_GUI *p=FindGUIbyId(main_csm->view_id,NULL);
//      VIEWDATA *vd=p->vd;
//      *((unsigned short *)(&(vd->current_tag_d)))=(unsigned short)0x813A;
//      *((unsigned int *)(&(vd->current_tag_s)))=(unsigned int)0x0D15F000;
//      AddNewStyle(vd);
//      AddTextItem(vd, "Begin OMS Hacking . . .\nNOW\n!!!\n\n",33);
//      AddBeginRef(vd);
//      RawInsertChar(vd,AddPictureItemFile(vd, "0:\\ZBin\\NatICQ\\smiles\\1405.png"));
//      AddEndRef(vd);
//      RawInsertChar(vd,AddPictureItemFile(vd, "0:\\ZBin\\NatICQ\\smiles\\1406.png"));
//      AddBeginRef(vd);
//      AddEndRef(vd);
//      RawInsertChar(vd,AddPictureItemFile(vd, "0:\\ZBin\\NatICQ\\smiles\\1407.png"));
//      AddBeginRef(vd);
//      AddEndRef(vd);
//      RawInsertChar(vd,AddPictureItemFile(vd, "0:\\ZBin\\NatICQ\\smiles\\1408.png"));
//      AddBeginRef(vd);
//      AddEndRef(vd);
//      RawInsertChar(vd,AddPictureItemFile(vd, "0:\\ZBin\\NatICQ\\smiles\\1409.png"));
//      RawInsertChar(vd,AddPictureItemFile(vd, "0:\\ZBin\\NatICQ\\smiles\\1410.png"));
//      RawInsertChar(vd,AddPictureItemFile(vd, "0:\\ZBin\\NatICQ\\smiles\\1411.png"));
//      AddBrItem(vd);
//      AddPageEndItem(vd);
//      SmartREDRAW();
//    }
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
      if (vd->rawtext[prf->begin+1]==vd->WCHAR_RADIO_ON||vd->rawtext[prf->begin+1]==vd->WCHAR_BUTTON_ON)
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
        //b=ToWeb(b,1);
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
        char se[1024];
        int utf8conv_res_len;
        ws_2utf8(prf->data,se,&utf8conv_res_len,length);
        char *b=c=(char *)malloc(length);
        for (int i=0; i<strlen(se); i++) *c++=se[i];
        *c=0;
        //b=ToWeb(b,1);
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
        if (vd->rawtext[prf->begin+1]==vd->WCHAR_RADIO_ON||vd->rawtext[prf->begin+1]==vd->WCHAR_BUTTON_ON)
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
        //b=ToWeb(b,1);
        memcpy(s+pos, b, strlen(b));
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
        char se[1024];
        int utf8conv_res_len;
        ws_2utf8(prf->data,se,&utf8conv_res_len,length);
        char *b=c=(char *)malloc(length);
        for (int i=0; i<strlen(se); i++) *c++=se[i];
        *c=0;
        //b=ToWeb(b,1);
        memcpy(s+pos, b, strlen(b));
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

//          break;
//        case 2:

          wstrcpy(data->ws1, ws_console);
          //wsprintf(data->ws1,percent_t,);
          break;
//        case 3:

//          break;
        }
      }
      ascii2ws(data->ws2, lgpData[LGP_Stop]);
      
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
  vd->ws=AllocWS(256);
  vd->pos_cur_ref=0xFFFFFFFF; 
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

static void RunOtherCopyByURL(const char *url, int isNativeBrowser)
{
  int f;
  unsigned int err;
  WSHDR *ws;
  char * filename = getSymbolicPath("$urlcache\\$date$time.url");
  f=fopen(filename,A_Create+A_Truncate+A_BIN+A_ReadWrite,P_READ+P_WRITE,&err);
  if (f!=-1)
  {
    fwrite(f,url,strlen(url),&err);
    fclose(f,&err);
    ws=AllocWS(256);
    if (isNativeBrowser)
    {
      gb2ws(ws,filename,255);
      ExecuteFile(ws,NULL,NULL);
    }
    else
    {
      gb2ws(ws,BALLET_EXE,255);
      ExecuteFile(ws,NULL,filename);
    } 
    FreeWS(ws);
    unlink(filename,&err);
  }
  mfree(filename);
}

static int method5(VIEW_GUI *data,GUI_MSG *msg)
{
  VIEWDATA *vd=data->vd;
  REFCACHE *rf;
  int m=msg->gbsmsg->msg;
  if ((m==KEY_DOWN)||(m==LONG_PRESS))
  {
    switch(msg->gbsmsg->submess)
    {
    case ENTER_BUTTON:
      if (vd->pos_cur_ref==0xFFFFFFFF) break;
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
            _safe_free(goto_url);
            goto_url=malloc(l-strlen(c)+1);
            strcpy(goto_url,c+strlen(c)+1);
            mfree(c);
            return 0xFF;
          }
          break;
        case 'L':
          if (rf->id!=_NOREF)
          {

            _safe_free(goto_url);
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
        case '@':
          if (rf->id!=_NOREF)
          {
            char *s=extract_omstr(vd,rf->id);
            RunOtherCopyByURL(s,1);
            mfree(s);
          }
          break;
        case 'r':
          {
            REFCACHE *rfp;
            int i;
            if (vd->rawtext[rf->begin+1]!=vd->WCHAR_RADIO_OFF) break;
            vd->rawtext[rf->begin+1]=vd->WCHAR_RADIO_ON;
            i=0;
            while((i=FindReferenceById(vd,rf->id,i))>=0)
            {
              rfp=vd->ref_cache+i;
              if (rfp!=rf)
                if (vd->rawtext[rfp->begin+1]==vd->WCHAR_RADIO_ON)
                  vd->rawtext[rfp->begin+1]=vd->WCHAR_RADIO_OFF;
              i++;
            }
          }
          if (!rf->no_upload)
          {
            _safe_free(goto_url);
            goto_url=malloc(strlen(vd->pageurl)+1);
            strcpy(goto_url,vd->pageurl);
            from_url=malloc(strlen(vd->pageurl)+1);
            strcpy(from_url,vd->pageurl);
            goto_params=collectItemsParams(vd,rf);
            return 0xFF;
          }
          break;
        case 'c':
          if (vd->rawtext[rf->begin+1]==vd->WCHAR_BUTTON_ON)
            vd->rawtext[rf->begin+1]=vd->WCHAR_BUTTON_OFF;
          else
            vd->rawtext[rf->begin+1]=vd->WCHAR_BUTTON_ON;
          if (!rf->no_upload)
          {
            _safe_free(goto_url);
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
          {
            MAIN_CSM *main_csm;
            int bookmark_menu_id;
            if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
            {
              bookmark_menu_id=CreateInputBox(vd,rf);
              main_csm->sel_bmk=bookmark_menu_id;
            }
          }
          break;
        case 'i':
        case 'u':
          _safe_free(goto_url);
          goto_url=malloc(strlen(vd->pageurl)+1);
          strcpy(goto_url,vd->pageurl);
          from_url=malloc(strlen(vd->pageurl)+1);
          strcpy(from_url,vd->pageurl);
          goto_params=collectItemsParams(vd,rf);
          return 0xFF;
        case 's':
          
          {
            MAIN_CSM *main_csm;
            int bookmark_menu_id;
            if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
            {
              bookmark_menu_id=ChangeMenuSelection(vd, rf);
              main_csm->sel_bmk=bookmark_menu_id;
            }
          }
          break;
        default:
          {
            char c[128];
            sprintf(c,lgpData[LGP_RefUnderConstruction],rf->tag);
            ShowMSG(1,(int)c);
          }
        break;
        }
      }
      else
      {
	      ShowMSG(1,(int)lgpData[LGP_RefEmpty]);
      }
      break;
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
      case 0x31: // '1'
        if (rf = FindReference(vd,vd->pos_cur_ref))
        {
          if (rf->id != _NOREF)
          {
            if (rf->tag == 'L' || rf->tag == 'Z' || rf->tag == '@')
            {
              char * s = extract_omstr(vd, rf->id);
              if (rf->tag == 'L') s += 2;
              if (rf->tag == 'Z') s += strlen(s) + 1;
              
              if (sieget_ipc.data) mfree(sieget_ipc.data);
              sieget_ipc.name_to = sieget_ipc_name; 
              sieget_ipc.name_from = ipc_my_name;
              sieget_ipc.data = malloc(strlen(s) + 1);
              strcpy((char *)sieget_ipc.data, s);
              GBS_SendMessage(MMI_CEPID, MSG_IPC, SIEGET_GOTO_URL, &sieget_ipc);

              s=0; // is it necessary
              mfree(s);
            }
          }
        }
      break;
    case 0x32:
    case GREEN_BUTTON:
      rf=FindReference(vd,vd->pos_cur_ref);
      if (rf)
      {
        if (rf->id!=_NOREF)
        {
          if (rf->tag=='L'||rf->tag=='Z')
          {
            char *s=extract_omstr(vd,rf->id);
            if (rf->tag=='L')
              s+=2;
            if (rf->tag=='Z')
              s+=strlen(s)+1;
            if (msg->gbsmsg->submess==0x32)
            {
              RunOtherCopyByURL(s,1);
            }
            else
            {
              RunOtherCopyByURL(s,0);
            }
            s=0; // is it necessary
            mfree(s);
          }
        }
      }
      break;
    case 0x33: // '3'
      vd->pixdisp=0;
      vd->view_line=0;
      vd->pos_cur_ref=0xFFFFFFFF;
      break;
    /*case 0x34: // '4'
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
              for (int to=strlen(s);to;to--) if (s[to-1]==NULL) s[to-1]=' ';
              sprintf(c,"   %s",s);
              fwrite(f,c,strlen(c),&ul);
              mfree(s);
            }
            fwrite(f,"\n",1,&ul);
            sprintf(c,"  id2:       %u",rf->id2);
            fwrite(f,c,strlen(c),&ul);
            if (rf->id2!=_NOREF&&rf->tag!='@')
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
    case 0x38: // '8'
      {
        //Dump LINECACHE
        unsigned int ul;
        int f;
        if ((f=fopen("0:\\zbin\\balletmini\\dumplc.txt",A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
        {
          char c[256];
          sprintf(c,"\nlines_cache_size : %i\n",vd->lines_cache_size);
          fwrite(f,c,strlen(c),&ul);
          for (int i=0;i<vd->lines_cache_size;i++)
          {
            LINECACHE *lc=vd->lines_cache+i;
            sprintf(c,"%i\n  pos : %u\n  pix : %u\n",i,lc->pos,lc->pixheight);
            fwrite(f,c,strlen(c),&ul);
          }
         fclose(f,&ul);
        }
      }
      break;*/
    case 0x39: // '9'
      while(LineDown(vd)) ;
      vd->pixdisp=0;
      scrollUp(vd,ScreenH()-1);
      vd->pos_cur_ref=0xFFFFFFFF;
      break;
    case 0x30: // '0'
      {
        // get text from page
        int scr_h=ScreenH()-1;
        WSHDR *ws=AllocWS(512);
        LINECACHE *lc;
        unsigned int vl;
        int ypos=-vd->pixdisp;
        unsigned int store_line=vl=vd->view_line;
        unsigned int len;
        int sc;
        int c;

        while(ypos<=scr_h)
        {
          if (LineDown(vd))
          {
            lc=vd->lines_cache+vl;
            if ((vl+1)<vd->lines_cache_size)
            {
              len=(lc[1]).pos-(lc[0]).pos;
            }
            else
              len=vd->rawtext_size-lc->pos;
            sc=lc->pos;
            while(len>0)
            {
              c=vd->rawtext[sc];
              if ((c&0xFF00)!=0xE100)
              {
                switch (c)
                {
                case UTF16_FONT_SMALL:
                case UTF16_FONT_SMALL_BOLD:
                case UTF16_DIS_UNDERLINE:
                case UTF16_ENA_UNDERLINE:
                case UTF16_ENA_INVERT:
                case UTF16_DIS_INVERT:
                case UTF16_ALIGN_LEFT:
                case UTF16_ALIGN_RIGHT:
                case UTF16_ENA_CENTER:
                case UTF16_DIS_CENTER:
                  break;
                case UTF16_INK_RGBA:
                case UTF16_PAPER_RGBA:
                  len--;
                  sc++;
                  len--;
                  sc++;
                  break;
                default :
                  wsAppendChar(ws,c);
                }
              }
              sc++;
              len--;
            }
            ypos+=lc->pixheight;
            vl++;
          }
          else
            break;
        }
        vd->view_line=store_line;
        createTextView(ws);
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
  goto_url = NULL;
  MAIN_CSM *csm=(MAIN_CSM*)data;
  ws_console=AllocWS(1024);
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->view_id=CreateViewGUI(0);
  sieget_ipc.data = NULL;
}

static void KillAll(void)
{
  FreePageStack();
  FreeWS(ws_console);
  lgpFreeLangPack();
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
  if (goto_url) mfree(goto_url);
  if (sieget_ipc.data) mfree(sieget_ipc.data);
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
            csm_result=0; 
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
            csm_result=0; 
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
            _safe_free(goto_url);
            csm_result=0;  
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
      //ShowMSG(1,(int)"BalletMini config updated!");
      ShowMSG(1,(int)lgpData[LGP_CfgUpdated]);
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
        if ((goto_url=PopPageFromStack()))
        {
          SUBPROC((void*)GotoFile);
          break;
        }
        goto L_CLOSE;
      case 0xFF:
        if (goto_url)
        {
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
    gb2ws(ws,view_url,255);
    break;
  case MODE_URL:
    ascii2ws(ws,view_url+2);
    break;
  default:
    gb2ws(ws,"",1);
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
  FreeViewUrl();
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
  if (!strcmp_nocase(fn,"bookmarks"))
  {
    view_url_mode=MODE_BOOKMARKS;
    return 1;
  }
  else
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
      else if (!strcmp_nocase(s,"url"))
      {
        if (!ReadUrlFile((char *)fn)) return (0);
      }
      else return 0;
      return 1;
    }
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
  char * authdata_file = getSymbolicPath("$ballet\\AuthCode");
  if (GetFileStats(authdata_file,&stat,&err)==-1) return 0;
  if ((fsize=stat.size)<=0) return 0;
  if ((f=fopen(authdata_file,A_ReadOnly+A_BIN,P_READ,&err))==-1) return 0;
  mfree(authdata_file);
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
  //if (GetFileStats(pathbuf,&stat,&ul)!=-1) return;
  if (stat.size==0)
  {
    unlink(pathbuf,&ul);
    f = fopen(pathbuf,A_WriteOnly+A_Create+A_BIN,P_READ+P_WRITE,&ul);
    if (f!=-1)
    {
      fwrite(f,from,size,&ul);
      fclose(f,&ul);
    }
  }
  mfree(pathbuf);

}

int main(const char *exename, const char *filename)
{
  char dummy[sizeof(MAIN_CSM)];
  char *path=strrchr(exename,'\\');
  int l;
  if (!path) return 0; 
  path++;
  l=path-exename;
  InitConfig();
  
  memcpy(BALLET_PATH,exename,l);
  strcpy(BALLET_EXE, exename);
 
  
  //CheckHistory("http://perk11.info/elf");

//  GenerateFile(IMG_PATH, RADIO_BTTN_CLKD, radio_bttn_clkd_png, radio_bttn_clkd_png_size);
//  GenerateFile(IMG_PATH, RADIO_BTTN,      radio_bttn_png,      radio_bttn_png_size);
//  GenerateFile(IMG_PATH, BUTTON_CLKD,     button_clkd_png,     button_clkd_png_size);
//  GenerateFile(IMG_PATH, BUTTON,          button_png,          button_png_size);
//  GenerateFile(IMG_PATH, TEXT_FORM,       text_form_png,       text_form_png_size);
//  GenerateFile(IMG_PATH, LIST,            list_png,            list_png_size);
  
  lgpInitLangPack();

  if (!LoadAuthCode())
  {
    LockSched();
    ShowMSG(1,(int)lgpData[LGP_CantLoadAuthCode]);
    UnlockSched();
    SUBPROC((void *)Killer);
    return 0;
  }

  if (ParseInputFilename(filename)) // open oms or url
  {
    UpdateCSMname();
    LockSched();
    maincsm_id=CreateCSM(&MAINCSM.maincsm,dummy,0);
    UnlockSched();
  }
  else
  {
    if (ParseInputFilename(DEFAULT_PARAM))
    {
      UpdateCSMname();
      LockSched();
      maincsm_id=CreateCSM(&MAINCSM.maincsm,dummy,0);
      UnlockSched();
    }
    else
    {
      // create smiles view
      UpdateCSMname();
      LockSched();
      maincsm_id=CreateCSM(&MAINCSM.maincsm,dummy,0);
      UnlockSched();
      view_url_mode=MODE_NONE;
    }
  }
  return 0;
}
