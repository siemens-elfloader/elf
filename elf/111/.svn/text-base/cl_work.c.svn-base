#include "../inc/swilib.h"
#include "NatICQ.h"
#include "strings.h"
#include "main.h"
#include "cl_work.h"


extern volatile unsigned int GROUP_CACHE; //Текущая группа для добавления
extern volatile CLIST *cltop;
extern int Is_Show_Groups;
extern char ContactT9Key[32];
extern int Is_Show_Offline;
extern int IsActiveUp;

extern const unsigned int UIN;
extern const char TEMPLATES_PATH[];

void FreeXText(CLIST *t)
{
  if (t->xtext) {mfree(t->xtext);t->xtext=NULL;}
}

//Уничтожить список
void FreeCLIST(void)
{
  CLIST *cl=(CLIST*)cltop;
  cltop=0;
  while(cl)
  {
    CLIST *p;
    if (cl->log) FreeLOGQ(&cl->log);
    if (cl->answer) mfree(cl->answer);
    if (cl->xtext) mfree(cl->xtext);
    p=cl;
    cl=(CLIST*)(cl->next);
    mfree(p);
  }
}

//Прописать всех в offline
void FillAllOffline(void)
{
  CLIST *cl=(CLIST*)cltop;
  while(cl)
  {
    if (!cl->isgroup)
    {
      LOGQ *lp=cl->log;
      while(lp)
      {
	lp->ID|=0x18000;
	lp=lp->next;
      }
    }
    if ((cl->state!=0xFFFF)&&
	(!cl->isgroup))     //by BoBa 2.05.2007
    {
      CLIST *p=cl;
      p->state=0xFFFF;
      FreeXText(p);
      cl=cl->next;
      ChangeContactPos(p);
      continue;
    }
    cl=(CLIST*)(cl->next);
  }
}


CLIST *FindContactByUin(unsigned int uin)
{
  CLIST *t;
  t=(CLIST *)cltop;
  while(t)
  {
    if ((t->uin==uin)&&(!t->isgroup)) break;
    t=t->next;
  }
  return(t);
}

CLIST *FindGroupByID(unsigned int grp)
{
  CLIST *t;
  t=(CLIST *)cltop;
  while(t)
  {
    if ((t->group==grp)&&(t->isgroup)) break;
    t=t->next;
  }
  return(t);
}

//Ключи для поиска по T9
static const char table_T9Key[256]=
"11111111111111111111111111111111"
"10001**0***0000*012345678900***0"
"0222333444555666777788899991*110"
"122233344455566677778889999111*1"
"11111111111111111111111111111111"
"11111111311111111111111131111111"
"22223333444455566677778888899999"
"22223333444455566677778888899999";


CLIST *FindContactByNS(int *i, int si, int act_flag, CLIST *search_contact)
{
  CLIST *t;
  t=(CLIST *)cltop;
  char *s;
  char *d;
  int c;
  int grp_id=0;
  int grp_dis=0;
  while(t)
  {
    if (t->isgroup)
    {
      grp_id=t->group;
      grp_dis=t->state;
    }
    if (act_flag<2)
    {
      if ((act_flag)&&(!t->isactive)) goto L_NOT9;
      if ((!act_flag)&&(t->isactive)) goto L_NOT9;
    }
    if ((si==IS_ANY)||(GetIconIndex(t)==si))
    {
      s=ContactT9Key;
      if ((!Is_Show_Groups)&&(t->isgroup)) goto L_NOT9;
      
      if ((!t->isgroup)&&(t->group==grp_id)&&(grp_dis)&&(!(*s))) goto L_NOT9;
      
      if (!Is_Show_Offline) // by Seklth 13.06.2007
        if ((!t->isgroup)&&(!t->isactive)&&(t->state==0xFFFF)&&(t->uin!=UIN)&&(!(*s))) 
          if (!t->isunread) goto L_NOT9;
      
      d=t->name;
      while(c=*s++)
      {
	if (c!=table_T9Key[*d++]) goto L_NOT9;
      }
      if (search_contact==t) return t; //Нашли контакт по адресу
      if (!(*i)) return(t);
      (*i)--;
    }
  L_NOT9:
    t=t->next;
  }
  return(t);
}


int CountContacts(void)
{
  int l=-1;
  FindContactByNS(&l,IS_ANY,2,NULL);
  l=-1-l;
  return l;
}

CLIST *FindContactByN(int i)
{
  CLIST *t;
  int f=IsActiveUp;
  if (f)
  {
    t=FindContactByNS(&i,IS_ANY,1,NULL); if ((!i)&&(t)) return (t);
    f=0;
  }
  else f=2;
  t=FindContactByNS(&i,IS_ANY,f,NULL);
  return t;
}

int FindContactByContact(CLIST *p)
{
  int l=-1;
  //  CLIST *t;
  int f=IsActiveUp;
  if (f)
  {
    if (FindContactByNS(&l,IS_ANY,1,p)) return -1-l;
    f=0;
  }
  else f=2;
  FindContactByNS(&l,IS_ANY,f,p);
  return -1-l;
}

void SwapContacts(CLIST *first, CLIST *second)
{
  CLIST *tp;
  if ((tp=second->next)) tp->prev=first;
  if ((tp=first->prev)) tp->next=second;
  first->next=second->next;
  second->next=first;
  second->prev=first->prev;
  first->prev=second;
}

void ChangeContactPos(CLIST *p)
{
  CLIST *t;
  if ((t=p->prev))
  {
    //Проверяем, не надо ли всплывать
    while(CompareContacts(t,p)>0)
    {
      //Всплываем вверх списка
      SwapContacts(t,p);
      if (!(t=p->prev)) return; //Всплыли
    }
  }
  if ((t=p->next))
  {
    //Проверяем, не надо ли углубляться
    while(CompareContacts(p,t)>0)
    {
      SwapContacts(p,t);
      if (!(t=p->next)) return; //Углубились нах ;)
    }
  }
}

int CompareContacts(CLIST *t, CLIST *p)
{
  int c;
  if (Is_Show_Groups)
  {
    if ((c=p->group-t->group))
    {
      return(c);
    }
  }
  
  extern const int SORT_CLIST;
  int ip=GetIconIndex(p);
  int it=GetIconIndex(t);
  switch (SORT_CLIST)
  {
  case 0: // by name
    if ((ip>IS_OFFLINE)&&(ip<IS_MSG)&&
	(it>IS_OFFLINE)&&(it<IS_MSG)) break;
  case 1: // by status
    if ((c=ip-it))
    {
      return(c);
    }
    break;
  }
  
  return(strcmp_nocase(t->name,p->name));
}

void DeleteContact(CLIST *p)
{  
  if(p->prev)
    {
    //not first
    ((CLIST *)p->prev)->next=p->next;
    if(p->next) ((CLIST *)p->next)->prev=p->prev;    
    }
  else
    {
    //first  
    cltop=p->next;  
    cltop->prev=0;
    };
if (p->log) FreeLOGQ(&p->log);
if (p->answer) mfree(p->answer);
if (p->xtext) mfree(p->xtext);
mfree(p);  
};

CLIST *AddContactOrGroup(CLIST **top, CLIST *p)
{
  CLIST *t;
  CLIST *pr;
  t=*top;
  if (t)
  {
    //Не первый
    while(CompareContacts(t,p)<0)
    {
      if (!(pr=t->next))
      {
	//добавляем в конец
	t->next=p;
	p->prev=t;
	return(p);
      }
      t=pr;
    }
    if ((pr=t->prev))
      pr->next=p;
    else
      *top=p;
    p->prev=pr;
    p->next=t;
    t->prev=p;
  }
  else
  {
    //Первый
    *top=p;
  }
  return(p);
}

void ResortCL(void)
{
  CLIST *first=NULL;
  CLIST *cl=(CLIST *)cltop;
  while(cl)
  {
    CLIST *pr=cl;
    cl=cl->next;
    pr->next=0;
    pr->prev=0;
    if (pr->isgroup)
    {
      pr->state=Is_Show_Groups?0xFFFF:0;
    }
    AddContactOrGroup(&first,pr);    
  }
  cltop=first;
}

CLIST *AddContact(unsigned int uin, char *name, unsigned int group, int local)
{
  CLIST *p=malloc(sizeof(CLIST));
  zeromem(p,sizeof(CLIST));
  p->uin=uin;
  p->group=group;
  strncpy(p->name,name,sizeof(p->name)-1);
  p->state=0xFFFF;
  p->local=local;
  return AddContactOrGroup((CLIST **)&cltop,p);
}

CLIST *AddGroup(unsigned int grp, char *name)
{
  CLIST *p=malloc(sizeof(CLIST));
  zeromem(p,sizeof(CLIST));
  //  p->uin=0;
  p->group=grp;
  p->isgroup=1;
  strncpy(p->name,name,sizeof(p->name)-1);
  if (!Is_Show_Groups) p->state=0;//Открыть группу
  else
    p->state=0xFFFF;
  return AddContactOrGroup((CLIST **)&cltop,p);
}

//by BoBa 19.11.2007
void LoadLocalCL(void){
 FSTATS stat;
 char fn[256];
 int f;
 unsigned int ul;
 int fsize;
 char *p,*s;
 char cn[64];
 unsigned int uin;
 const char _slash[]="\\";
 strcpy(fn,TEMPLATES_PATH);
 if (fn[strlen(fn)-1]!='\\') strcat(fn, _slash);
 strcat(fn,"local.cl");
 if (GetFileStats(fn,&stat,&ul)==-1) return;
 if ((fsize=stat.size)<=0) return;
 if ((f=fopen(fn,A_ReadOnly+A_BIN,P_READ,&ul))==-1) return;
 s=p=malloc(fsize+1);
 s[fread(f,p,fsize,&ul)]=0;
 fclose(f,&ul);
 while(*p!=0){
  char cc;
  while((cc=*p)!=';'){    //нах имя группы
   if (cc==0) goto L_EOF;
   p++;
  }
  p++;
  uin=0;
  while((cc=*p)!=';'){   //uin
   if (cc==0) goto L_EOF;
   uin*=10;
   uin+=((*p++)-'0');
  }
  p++;
  char *c=cn;
  while((cc=*p)!=';'){   //nick
   if (cc==0) goto L_EOF;
   *c++=*p++;
  }
  *c=0;
  while(*p!=13 && *p!=10 && *p!=0) p++; //нах конец строки
  if (*p!=0) p++;
  if ((*p==13)||(*p==10)) p++;
  if (!FindContactByUin(uin)) AddContact(uin, cn, 0, 1);
 }
L_EOF:
 mfree(s);
}
