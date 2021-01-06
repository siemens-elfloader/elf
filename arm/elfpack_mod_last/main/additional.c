#include "..\..\inc\swilib.h"

#ifdef NEWSGOLD
extern void(*OldShowMsg)(int, int);
#else
extern void(*OldTxtOpen)(WSHDR*, WSHDR*);
#endif

int get_file_size(const char * fname)
{
  FSTATS fs;
  unsigned int err;
  if (GetFileStats(fname,&fs,&err)==-1) return (-1);
  else return (fs.size);
}

__arm void REDRAW_impl(void)
{
  LockSched();
#ifdef NEWSGOLD
  PendedRedrawGUI();
#else
  PendedRedrawGUI();
  GBS_SendMessage(MMI_CEPID,0x90);
#endif
  UnlockSched();
}


__thumb void SEQKILLER_impl(void *data, void(*next_in_seq)(void *), void *data_to_kill)
{
  next_in_seq(data);
  mfree(data_to_kill);
}

unsigned int char8to16(int c)
{
  if (c==0xA8) c=0x401;
  if (c==0xAA) c=0x404;
  if (c==0xAF) c=0x407;
  if (c==0xB8) c=0x451;
  if (c==0xBA) c=0x454;
  if (c==0xBF) c=0x457;
  if (c==0xB2) c=0x406;
  if (c==0xB3) c=0x456;
  if ((c>=0xC0)&&(c<0x100)) c+=0x350;
  return(c);
}

void ascii2ws(char *s, WSHDR *ws)
{
  int c;
  while((c=*s++))
  {
    wsAppendChar(ws,char8to16(c));
  }
}
#ifdef NEWSGOLD
__arm void ESI(WSHDR *ws, int dummy, char *s)
#else
__arm void ESI(char *s, WSHDR *ws)
#endif
{
  if (((unsigned int)s>>28)==0xA) //Только строки из области RAM/FLASH
  {
    CutWSTR(ws,0); 
    ascii2ws(s,ws);
  }
  else
  {
    wsprintf(ws,"|%d|",s);
  }
}

__arm void DoUnknownFileType(WSHDR *filename)
{
  WSHDR *wsmime=AllocWS(15);
  wsprintf(wsmime,"txt");
  ExecuteFile(filename,wsmime,0);
  FreeWS(wsmime);
}

#ifdef NEWSGOLD 
__no_init int *EXT2_AREA;
#ifdef ELKA
__no_init int EXT2_CNT @ "REGEXPL_CNT";
#endif

#else
__no_init TREGEXPLEXT *EXT2_AREA;
__no_init int EXT2_CNT @ "REGEXPL_CNT";
#endif

#ifdef NEWSGOLD 
#ifdef ELKA
#else
__arm int *GET_EXT2_TABLE(void)
{
  int *p=EXT2_AREA;
  if (p)
  {
    return(p+1);
  }
  p=malloc(4);
  *p=0;
  return ((EXT2_AREA=p)+1);
}
#endif
#endif  

#ifdef NEWSGOLD 
#ifdef ELKA
__arm int *EXT2_REALLOC(void)
{
  int size;
  size=sizeof(REGEXPLEXT);
  int *p;
  int *p2;
  int n;
  LockSched();
  n=EXT2_CNT;
  p=EXT2_AREA;
  p2=malloc((n+1)*size);
  if (p) 
  {    
    memcpy(p2,p,n*size);
    mfree(p);
  }
  EXT2_CNT=n+1;
  EXT2_AREA=p2;
  p2+=(n*(size/sizeof(int)));
  UnlockSched();
  return (p2);
}
#else
__arm int *EXT2_REALLOC(void)
{
  int size;
  size=sizeof(REGEXPLEXT);
  int *p;
  int *p2;
  int n;
  LockSched();
  n=*(p=EXT2_AREA);
  p2=malloc((n+1)*size+4);
  memcpy(p2,p,n*size+4);
  *p2=n+1;
  mfree(p);
  EXT2_AREA=p2;
  p2+=(n*(size/sizeof(int)))+1;
  UnlockSched();
  return (p2);
}
#endif
#else
__arm TREGEXPLEXT *EXT2_REALLOC(void)
{
  TREGEXPLEXT *p,*p2;
  int n;
  LockSched();
  n=EXT2_CNT;
  p=EXT2_AREA;
  p2=malloc((n+1)*sizeof(TREGEXPLEXT));
  zeromem(p2,(n+1)*sizeof(TREGEXPLEXT));
  if (p) 
  {    
    memcpy(p2,p,n*sizeof(TREGEXPLEXT));
    mfree(p);
  }
  EXT2_CNT=n+1;
  EXT2_AREA=p2;
  UnlockSched();
  return (p2+n);
}


#endif



#ifdef NEWSGOLD
__thumb MyShowMSG(int p1, int p2)
{
#ifdef ELKA
  if (p2!=0x1DD1)
#else
    if (p2!=(0x1DCC+5))
#endif    
    {
      OldShowMsg(p1,p2);
      return;
    }
  asm("MOVS R0,R6\n");
  DoUnknownFileType((WSHDR *)p1);
}
#else

__arm void PropertyPatch(WSHDR *unk_foldername, WSHDR *unk_filename)
{
  WSHDR *ws;
  ws=AllocWS(255);
  wstrcpy(ws,unk_foldername);
  wsAppendChar(ws,'\\');
  wstrcat (ws,unk_filename);
  DoUnknownFileType(ws);
  FreeWS(ws);
}

#endif


//Патчи
#pragma diag_suppress=Pe177

#ifdef NEWSGOLD
__root static const int NEW_SHOWMSG @ "PATCH_SHOWMSG_BLF" = (int)MyShowMSG;
#endif


__root static const int SWILIB_FUNC172 @ "SWILIB_FUNC172" = (int)REDRAW_impl;
__root static const int SWILIB_FUNC19C @ "SWILIB_FUNC19C" = (int)SEQKILLER_impl;
#pragma diag_default=Pe177


#ifndef NEWSGOLD

// В этот файл включены некоторые функции которых нет в прошивке для SGOLD

// ========================================== Reg Files =============================================
__arm void RegFile(WSHDR*ext,int unical_id,int menu_flag,unsigned int* icon1,int obex_path_id,int enabled_options,void *proc1,void *proc2,unsigned int *icon2)
{
  TREGEXPLEXT *reg;
  unsigned int *icon2new;
  reg=EXT2_REALLOC();
  LockSched();
  reg->zero=0;
  reg->icon1=icon1;
  reg->unical_id=unical_id;
  reg->obex_path_id=obex_path_id;
  reg->menu_flag=menu_flag;
  reg->enabled_options=enabled_options;
  reg->ext=ext;
  reg->proc=proc1;
  reg->altproc=proc2;
   
  icon2new=malloc(sizeof(int)*2);
  icon2new[0]=*icon1>>28==0xA?*icon2:*icon1+1;
  icon2new[1]=0;
  reg->icon2=icon2new;
  UnlockSched();
}

__arm int GetBigIcon(const unsigned int icon, int uid)
{
  asm("mov r1, r8");
  TREGEXPLEXT *reg;
  if ((icon>>28)!=0xA) return (icon+1);
  reg=get_regextpnt_by_uid(uid);
  if (!reg) return (0);
  return (*(reg->icon2));
}

__arm void UnregExplExt_impl(REGEXPLEXT const * reg_orig)
{
  char ext[16];
  TREGEXPLEXT *reg=(TREGEXPLEXT*)EXT2_AREA;
  for (int i=0;i!=EXT2_CNT;i++)
  {
    if (reg_orig->unical_id==reg[i].unical_id)
    {
      ws_2str(reg[i].ext,ext,15);
      if (!strcmp(ext,reg_orig->ext))
      {
        FreeWS(reg[i].ext);
        mfree((void*)reg[i].icon2);
        EXT2_CNT--;
        memcpy(&reg[i],&reg[i+1],sizeof(TREGEXPLEXT)*(EXT2_CNT-i));
        return;
      }
    }
  }
}

// ========================================= Keyb Hooks ===========================================
typedef struct
{
  void *next;
  void *prev;
  int (*proc)(int submsg,int msg);
  char is_first;
}PLIST;



__no_init LLQ _plistq;

#pragma optimize=no_inline
static void LLaddToEnd(LLQ *ll, void *data)
{
  LLIST *d=data;
  d->next=NULL;
  d->prev=ll->last;
  if (ll->last)
  {
    ((LLIST *)ll->last)->next=d;
  }
  else
  {
    ll->first=d;
  }
  ll->last=d;
}

#pragma optimize=no_inline
static void LLaddToBegin(LLQ *ll, void *data)
{
  LLIST *d=data;
  d->next=ll->first;
  d->prev=0;
  if (!ll->last)
  {
    ll->last=d;
  }
  else
  {
    ((LLIST *)ll->first)->prev=d;
  }
  ll->first=d;
}

#pragma optimize=no_inline
static void LLremoveFromQ(LLQ *ll, void *data, int is_free)
{
  LLIST *d=data;
  if (d->prev)
  {
    ((LLIST *)d->prev)->next=d->next;
  }
  else
  {
    ll->first=d->next;
  }
  if (d->next)
  {
    ((LLIST *)d->next)->prev=d->prev;
  }
  else
  {
    ll->last=d->prev;
  }
  if (is_free)
  {
    ll->data_mfree(d);
  }
}

__arm void AddKeybMsgHook_impl(int (*proc)(int submsg,int msg))
{
  LLQ *plistq=&_plistq;
  PLIST *newp;
  if (!plistq->data_mfree)
  {
    plistq->first=0;
    plistq->last=0;
    plistq->data_mfree=(void(*)(void *))mfree_adr();
  }
  newp=malloc(sizeof(PLIST));
  if (newp)
  {
    newp->proc=proc;
    newp->is_first=0;
    LLaddToEnd(plistq,newp);
  }
}


__arm int AddKeybMsgHook_end_impl(int (*proc)(int submsg,int msg))
{
  LLQ *plistq=&_plistq;
  PLIST *newp, *pfirst;
  if (!plistq->data_mfree)
  {
    plistq->first=0;
    plistq->last=0;
    plistq->data_mfree=(void(*)(void *))mfree_adr();
  }
  if (pfirst=plistq->first)
  {
    if (pfirst->is_first==1) return 0;
  }
  newp=malloc(sizeof(PLIST));
  if (!newp) return 0;
  newp->proc=proc;
  newp->is_first=1;
  LLaddToBegin(plistq,newp);
  return 1;
}  

extern BXR1(void *, void (*)(void *));


__arm void RemoveKeybMsgHook_impl(int (*proc)(int submsg,int msg))
{
  LLQ *plistq=&_plistq;
  PLIST *plist=plistq->first;
  while(plist)
  {
    if (plist->proc==proc)
    {
      LLremoveFromQ(plistq,plist,1);
      return;      
    }  
    plist=plist->next;    
  }
}


int PatchKeybMsg(int submsg, int msg)
{
  LLQ *plistq=&_plistq;
  PLIST *plist=plistq->first;
  int proc_ret;
  int is_no_gui=0;
  while(plist)
  {
    if (plist->proc)
    {
      proc_ret=plist->proc(submsg,msg);
      switch(proc_ret)
      {
      case KEYHOOK_NEXT:
        break;
      case KEYHOOK_NEXT_NOT2GUI:
        is_no_gui=1;
        break;
      case KEYHOOK_BREAK:
        return (2);
      case KEYHOOK_ENDQ:
        return is_no_gui==1?2:0;
      default:
        break;
      }      
    }
    plist=plist->next;
  }
  return is_no_gui;
}

// ========================================= fread/fwrite ===========================================
extern int (*FReadOld)(int FileHandler, void *cBuffer, int iByteCount, unsigned int *ErrorNumber);
extern unsigned int(*FWriteOld)(int FileHandler, char * cBuffer, int iByteCount, unsigned int *ErrorNumber);

int fread32(int fh, void *buf, int len, unsigned int *err)
{
  int clen;
  int rlen;
  int total=0;
  while(len)
  {
    clen=len>=0x4000?0x4000:len;
    total+=(rlen=FReadOld(fh, buf, clen, err));
    if (rlen!=clen) break;
    buf=(char *)buf+rlen;
    len-=clen;
  }
  return(total);
}


unsigned int fwrite32(int fh, void *buf, int len, unsigned int *err)
{
  int clen;
  unsigned int wlen;
  int total=0;
  while(len)
  {
    clen=len>=0x4000?0x4000:len;
    total+=(wlen=FWriteOld(fh, buf, clen, err));
    if (wlen!=clen) break;
    buf=(char *)buf+wlen;
    len-=clen;
  }
  return(total);
}



#pragma diag_suppress=Pe177
__root static const int SWILIB_FUNC00B @ "SWILIB_FUNC00B" = (int)fread32;
__root static const int SWILIB_FUNC00C @ "SWILIB_FUNC00C" = (int)fwrite32;
__root static const int SWILIB_FUNC095 @ "SWILIB_FUNC095" = (int)UnregExplExt_impl;
__root static const int SWILIB_FUNC12B @ "SWILIB_FUNC12B_12D" = (int)AddKeybMsgHook_impl;
__root static const int SWILIB_FUNC12C @ "SWILIB_FUNC12B_12D" = (int)AddKeybMsgHook_end_impl;
__root static const int SWILIB_FUNC12D @ "SWILIB_FUNC12B_12D" = (int)RemoveKeybMsgHook_impl;
#pragma diag_default=Pe177



#endif

