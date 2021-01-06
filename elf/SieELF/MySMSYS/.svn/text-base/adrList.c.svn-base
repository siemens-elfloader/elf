#include "..\inc\swilib.h"
#include "sms_dat.h"
#include "adrList.h"
#include "rect_patcher.h"
#include "language.h"
#include "edGui.h"
#include "createMenu.h"
#include "numList.h"
#include "config_data.h"
#include "string_works.h"

#pragma swi_number=0x44
__swi __arm void TempLightOn(int x, int y);

volatile CLIST *cltop=0;
int cl_n;

void FreeCLIST(void)
{
	LockSched();
	CLIST *cl0=(CLIST*)cltop;
	cltop=0;
	UnlockSched();
	while(cl0)
	{
		CLIST *p;
		if(cl0->name) FreeWS(cl0->name);
		for(int i=0;i<NUMBERS_MAX;i++) 
		{
			if(cl0->num[i])
				mfree(cl0->num[i]);
		}
		if(cl0->sms_melody_filepath) mfree(cl0->sms_melody_filepath);
		p=cl0;
		cl0=(CLIST*)(cl0->next);
		mfree(p);
	}
}

void ConstructListN(void)
{
  if(!cltop) ConstructList();
}

void ConstructList(void)
{
  int fin;
  unsigned int ul;
  char recname[128];
  char s_ab_main[128];
  char s_ab_entry[128];
  
  AB_UNPRES ur;
  void *buffer;
#pragma pack(1)
  struct {
#ifdef NEWSGOLD
    long dummy1;
    short dummy2;
    char bitmap[MAX_RECORDS/8];
#else
    long dummy1;
    char bitmap[MAX_RECORDS/8];
#endif
  } ABmain;
#pragma pack()

  unsigned int rec=0;
  int fsz;
  int x, xl;
  CLIST contact;
  
  FreeCLIST();
  cl_n=0;
  strcpy(s_ab_main, CFG_SYSTEM_FOLDER);
  if((xl=strlen(s_ab_main))>0)
    x=s_ab_main[xl-1];
  if((x!='\\')&&(x!='/'))
    strcat(s_ab_main, "\\");
  strcat(s_ab_main, "apo\\addr\\main");
  strcpy(s_ab_entry, CFG_SYSTEM_FOLDER);
  if((xl=strlen(s_ab_entry))>0)
    x=s_ab_entry[xl-1];
  if((x!='\\')&&(x!='/'))
    strcat(s_ab_entry, "\\");
#ifdef NEWSGOLD
  strcat(s_ab_entry, "apo\\addr\\data\\%02d\\%02d\\%02d");
#else
  strcat(s_ab_entry, "apo\\addr\\%02x\\%02x");
#endif
  zeromem(&contact,sizeof(contact));
  if ((buffer=malloc(65536)))
  {
    zeromem(&ABmain,sizeof(ABmain));
    if ((fin=fopen(s_ab_main, A_ReadOnly+A_BIN, P_READ, &ul))!=-1)
    {
#ifdef ELKA
      if (fread(fin,&ABmain,sizeof(ABmain),&ul)>=194)
#else
	if (fread(fin,&ABmain,sizeof(ABmain),&ul)==sizeof(ABmain))
#endif
	{
	  fclose(fin,&ul);
	  do
	  {
#ifdef NEWSGOLD
	    if (ABmain.bitmap[rec>>3]&(0x80>>(rec&7)))
#else
	      if (ABmain.bitmap[rec>>3]&(1<<(rec&7)))
#endif
	      {
#ifdef NEWSGOLD
		unsigned int rl1;
		unsigned int rl2;
		unsigned int rl3;
		rl1=rec/LEVEL1_RN;
		rl2=(rec%LEVEL1_RN)/LEVEL2_RN;
		rl3=rec%LEVEL2_RN;
		snprintf(recname, 128, s_ab_entry, rl1, rl2, rl3);
#else
		unsigned int rl1=rec/LEVEL1_RN;
		unsigned int r12=rec%LEVEL1_RN;
		snprintf(recname, 128, s_ab_entry, rl1, r12);
#endif
		if ((fin=fopen(recname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
		{
		  zeromem(&ur,sizeof(AB_UNPRES));
		  fsz=lseek(fin,0,S_END,&ul,&ul);
		  lseek(fin,0,S_SET,&ul,&ul);
		  fread(fin,buffer,fsz,&ul);
		  fclose(fin,&ul);
#ifdef NEWSGOLD
		  UnpackABentry(&ur,((char *)buffer+8),fsz,0x28);
#else
		  UnpackABentry(&ur,((char *)buffer+4),fsz-4,0x28);
#endif
		  int i=0;
		  zeromem(&contact,sizeof(contact));
		  while(i<ur.number_of_records)
		  {
		    AB_UNPRES_ITEM *r=ur.record_list+i;
		    if (r->no_data!=1)
		    {
		      switch(GetTypeOfAB_UNPRES_ITEM(r->item_type))
		      {
		      case 0x05:
#ifdef NEWSGOLD
			if (
			    r->item_type==LAST_NAME||
			      r->item_type==FIRST_NAME||
				r->item_type==DISPLAY_NAME
				  )
#else
			  if (
			      r->item_type==LAST_NAME||
				r->item_type==FIRST_NAME||
				  r->item_type==COMPANY_NAME
				    )
#endif
			  {
			    if (r->data)
			    {
			      if (!contact.name)
			      {
				cl_n++;
				wstrcpy(contact.name=AllocWS(150),(WSHDR *)(r->data));
			      }
			      else
			      {
				wsAppendChar(contact.name,',');
				wsAppendChar(contact.name,' ');
				wstrcat(contact.name, (WSHDR*)(r->data));
			      }
			      contact.next = (void*)1;
			    }
			  }
			else if(r->item_type==SMS_MELODY)
			{
			  if(r->data)
			  {
			    if(!contact.sms_melody_filepath)
			      contact.sms_melody_filepath=malloc(128);
			    ws_2str(r->data, contact.sms_melody_filepath, 127);
			  }
			}
			break;
		      case 0x01:
			{
			  PKT_NUM *p=(PKT_NUM*)r->data;
			  unsigned int n=r->item_type;
			  int j;
			  unsigned int c;
			  char *nump;
			  //WSHDR *ws0;
#ifdef NEWSGOLD
			  if (n!=106) n-=0x62;
			  else n=4;
			  if (n<5)
#else
			    switch(r->item_type)
			    {
			    case PHONE_NUMBER:
			      n=0;    break;
			    case PHONE_OFFICE:
			      n=1;    break;
			    case PHONE_MOBILE:
			      n=2;    break;
			    case PHONE_FAX:
			      n=3;    break;
			    case PHONE_FAX2:
			      n=4;    break;
			    default:
			      continue;
			    }
#endif
			  {
			    if (p)
			    {
			      unsigned int c1;
			      int m;
			      nump=contact.num[n]=malloc(50);
			      j=0;
			      m=0;
			      if (p->format==0x91)
				*nump++='+';
			      while(j<p->data_size)
			      {
				if (m&1) {c1=c>>4; j++;}
				else c1=(c=p->data[j])&0x0F;
				if (c1==0x0F) break;

				if (c1==0xA) c1='*';
				else if (c1==0xB) c1='#';
				else if (c1==0xC) c1='+';
				else if (c1==0xD) c1='?';
				else c1+='0';
				*nump++=c1;
				//wsAppendChar(ws0,c1);
				m++;
			      }
			      *nump=0;
			      contact.next = (void*)1;
			    }
			  }
			  break;
			}
		      }
		    }
		    i++;
		  }
		  if (!contact.next)
		  {
		    if(contact.name) FreeWS(contact.name);
		    for(int i=0;i<NUMBERS_MAX;i++)
		    {
		      if(contact.num[i])
			mfree(contact.num[i]);
		    }
		  }
		  FreeUnpackABentry(&ur,mfree_adr());
		  /**/ //排序加入链表
		  LockSched();
		  if (contact.next)
		  {
		    //int n=0;
		    CLIST *p=malloc(sizeof(contact));
		    //CLIST *t;
		    //CLIST *b=(CLIST *)(&cltop);
		    contact.next=0;
		    memcpy(p,&contact,sizeof(contact));
		    p->next=(CLIST *)cltop;
		    cltop=p;
		  }
		  UnlockSched();
		}
	      }
	    rec++;
	  }
	  while(rec<MAX_RECORDS);
	}
	else
	{
	  fclose(fin,&ul);
	}
    }
    mfree(buffer);
  }
  if (contact.next)
  {
    if(contact.name) FreeWS(contact.name);
    for(int i=0;i<NUMBERS_MAX;i++) 
    {
      if(contact.num[i])
	mfree(contact.num[i]);
    }
  }
}


CLIST *GetClistItem(int n)
{
	int i=0;
	CLIST *cl0=(CLIST *)cltop;
	while(cl0)
	{
		if(i==n)
			return cl0;
		cl0=cl0->next;
		i++;
	}
	return 0;
}

int SearchInCList(WSHDR *searchstr)
{
	int i=0;
	CLIST *cl=(CLIST *)cltop;
	while(cl)
	{
		if(cl->name)
			if(!wstrncmp_nocase(cl->name, searchstr, wslen(searchstr)))
				return i;
		cl=cl->next;
		i++;
	}
	return -1;
}
#define MAX(A, B) ((A>B)?A:B)
#define MIN(A, B) ((A<B)?A:B)
int findNameByNum(WSHDR *name_to, char *num)
{
	CLIST *cl=(CLIST *)cltop;
	int i, la, lb, ld;
	char *p1;
	char *pp;
	if((!num)||(!name_to)||(strlen(num)<=3))
		return 0;
	while(cl)
	{
		i=0;
		for(;i<NUMBERS_MAX;i++)
		{
			if(cl->num[i])
			{
				//号码查找比较,根据短的比较长的后面部分
				p1=cl->num[i];
				if(*p1=='+')
					p1++;
				pp=num;
				if(*pp=='+')
					pp++;
				la=strlen(pp);
				lb=strlen(p1);
				if(MAX(la, lb)-MIN(la, lb) > 3)
					continue;
				if(la>lb)
				{
					ld=lb;
					pp+=la-lb;
				}
				else
				{
					ld=la;
					p1+=lb-la;
				}
				if(!strncmp(pp, p1, ld))
				{
					if(cl->name)
					{
						wstrcpy(name_to, cl->name);
						return 1;
					}
				}
			}
		}
		cl=cl->next;
	}
	return 0;
}


CLIST *FindClByNum(const char *num)
{
  CLIST *cl=(CLIST *)cltop;
  int i, la, lb, ld;
  const char *p1;
  const char *pp;
  if((!num)||(strlen(num)<=3))
    return 0;
  while(cl)
  {
    i=0;
    for(;i<NUMBERS_MAX;i++)
    {
      if(cl->num[i])
      {
	//号码查找比较,根据短的比较长的后面部分
	p1=cl->num[i];
	if(*p1=='+')
	  p1++;
	pp=num;
	if(*pp=='+')
	  pp++;
	la=strlen(pp);
	lb=strlen(p1);
	if(MAX(la, lb)-MIN(la, lb) > 3)
	  continue;
	if(la>lb)
	{
	  ld=lb;
	  pp+=la-lb;
	}
	else
	{
	  ld=la;
	  p1+=lb-la;
	}
	if(!strncmp(pp, p1, ld))
	{
	  return cl;
	}
      }
    }
    cl=cl->next;
  }
  return 0;
}

int getNumCount(CLIST *cl)
{
	int i=0;
	int j=0;
	for(;j<NUMBERS_MAX;j++)
	{
		if(cl->num[j])
			i++;
	}
	return i;
}

char *getNumFromCL(CLIST *cl, int n)
{
	int i=0, j=0;
	for(;j<NUMBERS_MAX;j++)
	{
		if(cl->num[j]!=0)
		{
			if(i==n)
				return cl->num[j];
			else
				i++;
		}
	}
	return 0;
}

char *getPrefNumFromCL(CLIST *cl)
{
	int i=NUMBERS_MAX-1;
	for(;i>=0;i--)
	{
		if(cl->num[i]!=0)
			return cl->num[i];
	}
	return 0;
}
