#include "include.h"
#include "AdrList.h"
#include "NumList.h"


NumList::NumList()
{
  this->nltop=NULL;
}

NumList::~NumList()
{
  FreeList();
}

NLST * NumList::AllocNL()
{
  NLST *nl=new NLST;
  zeromem(nl, sizeof(NLST));
  nl->name=CreateLocalWS(&nl->_name, nl->name_body, 50);
  return nl;
}

void NumList::FreeList()
{
  NLST *nl;
  NLST *nl0;
  LockSched();
  nl=this->nltop;
  this->nltop=NULL;
  UnlockSched();
  while(nl)
  {
    nl0=nl->next;
    delete nl;
    nl=nl0;
  }
}

void NumList::AddToList_end(NLST *nl) //end
{
  if (!nl) return;
  LockSched();
  if(!this->nltop)
  {
    this->nltop=nl;
  }
  else if(!this->nltop->next && !strlen(this->nltop->number))
  {
    strcpy(this->nltop->number, nl->number);
    wstrcpy(this->nltop->name, nl->name);
  }
  else
  {
    NLST *n0=this->nltop;
    while(n0->next) n0=n0->next;
    n0->next=nl;
    nl->prev=n0;
  }
  UnlockSched();
}

void NumList::AddToList(NLST *nl, int pos)
{
  NLST *n0;
  if(!pos)
  {
    AddToList_first(nl);
  }
  else
  {
    if(!(n0=FindNL(pos)))
    {
      AddToList_end(nl);
    }
    //else if (!strlen(n0->number))
    //{
    //  strcpy(this->nltop->number, nl->number);
    //  wstrcpy(this->nltop->name, nl->name);
    //}
    else //front
    {
      NLST *np=n0->prev;
      np->next=nl; //..null
      nl->prev=np;
      nl->next=n0;
      n0->prev=nl;
    }
  }
}

NLST * NumList::FindNL(int pos)
{
  int i=0;
  NLST *nl=this->nltop;
  while(nl)
  {
    if(pos==i)
      return nl;
    nl=nl->next;
    i++;
  }
  return 0;
}

void NumList::AddToList_first(NLST *nl)
{
  if(!nl) return;
  LockSched();
  if(this->nltop)
  {
    this->nltop=nl;
  }
  else if (!strlen(this->nltop->number))
  {
    strcpy(this->nltop->number, nl->number);
    wstrcpy(this->nltop->name, nl->name);
  }
  else
  {
    NLST *n0;
    n0=this->nltop;
    this->nltop=nl;
    nl->next=n0;
    n0->prev=nl;
  }
  UnlockSched();
}

void NumList::AddToList(NLST *nl)
{
  AddToList_end(nl);
}

void NumList::AddToList(const char *number)
{
  NLST *nl;
  if (
    (!number
    || !strlen(number))
  //  && (!this->nltop)
    )
  {
    if (!this->nltop)
      AddToList(AllocNL());
    return;
  }
  if((nl=this->nltop) && !strlen(nl->number))
  {
    //if(!strlen(nl->number))
    {
      strcpy(nl->number, number);
      if(!ADRLST->FindName(nl->name, number))
	num_2ws(nl->name, number, 50);
      return;
    }
  }
  nl=AllocNL();
  strcpy(nl->number, number);
  if(!ADRLST->FindName(nl->name, number))
    num_2ws(nl->name, number, 50);
  AddToList(nl);
}

void NumList::AddToList(const char *number, int pos)
{
  NLST *nl;
  if (
    (!number
    || !strlen(number))
    )
  {
    if (!this->nltop)
      AddToList(AllocNL());
    return;
  }
  nl=AllocNL();
  strcpy(nl->number, number);
  if(!ADRLST->FindName(nl->name, number))
    num_2ws(nl->name, number, 50);
  AddToList(nl, pos);
}

void NumList::DeleteNL(NLST *nl)
{
  if(!nl) return;
  LockSched();
  if(nl==this->nltop)
  {
    if(!nl->next)
    {
      nl->number[0]='\0';
      CutWSTR(nl->name, 0);
    }
    else
    {
      this->nltop=nl->next;
      nl->next->prev=NULL;
      delete nl;
    }
  }
  else
  {
    nl->prev->next=nl->next;
    if(nl->next)
      nl->next->prev=nl->prev;
    delete nl;
  }
  UnlockSched();
}

void NumList::DeleteNL(int pos)
{
  DeleteNL(FindNL(pos));
}

int NumList::AddNumsToList(const char *nums) //多个号码,以分号或逗号隔开
{
  char temp[128];
  const char *p;
  char *p2=temp;
  int c;
  int res=0;
  if(!nums) return 0;
  p=nums;
  while((c=*p++))
  {
    if(c>='0' && c<='9')
    {
      *p2++=c;
    }
    else if(c==';' || c==',')
    {
      if(p2!=temp)
      {
	*p2='\0';
	AddToList(temp);
	p2=temp;
	res++;
      }
    }
  }
  if(p2!=temp)
  {
    *p2='\0';
    AddToList(temp);
    res++;
  }
  if (!this->nltop)
    AddToList(AllocNL());
  return res;
}

//DEL void NumList::UpdateName(NLST *nl)
//DEL {
//DEL 
//DEL }

void NumList::UpdateNL(const char *number, int pos)
{
  NLST *nl;
  if(!number
    || !(nl=FindNL(pos))
    )
    return;
  strcpy(nl->number, number);
  if(!ADRLST->FindName(nl->name, number))
    num_2ws(nl->name, number, 50);
}

//DEL void NumList::UpdateNL(NLST *nl)
//DEL {
//DEL 
//DEL }

void NumList::UpdateNL(NLST *nl, const char *number)
{
  if( !nl
    || !number
    )
    return;
  strcpy(nl->number, number);
  if(!ADRLST->FindName(nl->name, number))
    num_2ws(nl->name, number, 50);
}

NLST * NumList::InsertNL_front(NLST *nl, const char *number)
{
  NLST *n0;
  if(
    !nl ||
    !number
    )
    return 0;
  n0=AllocNL(number);
  LockSched();
  if(nl==this->nltop)
  {
    this->nltop=n0;
    n0->next=nl;
    nl->prev=n0;
  }
  else
  {
    n0->next=nl;
    n0->prev=nl->prev;
    nl->prev->next=n0;
    nl->prev=n0;
  }
  UnlockSched();
  return n0;
}

NLST * NumList::AllocNL(const char *number)
{
  NLST *nl=new NLST;
  zeromem(nl, sizeof(NLST));
  nl->name=CreateLocalWS(&nl->_name, nl->name_body, 50);
  if(number)
  {
    strcpy(nl->number, number);
    if(!ADRLST->FindName(nl->name, number))
      num_2ws(nl->name, number, 50);
  }
  return nl;
}

NLST * NumList::InsertNL_behind(NLST *nl, const char *number)
{
  NLST *n0;
  if(
    !nl ||
    !number
    )
    return 0;
  n0=AllocNL(number);
  LockSched();
  n0->prev=nl;
  n0->next=nl->next;
  if(nl->next) nl->next->prev=n0;
  nl->next=n0;
  UnlockSched();
  return n0;
}

void NumList::ClearNL(NLST *nl)
{
  if(!nl) return;
  nl->number[0]='\0';
  CutWSTR(nl->name,0);
}

int NumList::IsNumExist(const char *number)
{
  NLST *nl=this->nltop;
  while(nl)
  {
    if(NumberMatch(number, nl->number)==MATCH_NML)
      return 1;
    nl=nl->next;
  }
  return 0;
}
