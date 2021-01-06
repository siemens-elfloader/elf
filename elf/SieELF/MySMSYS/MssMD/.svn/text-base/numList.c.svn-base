#include "..\..\inc\swilib.h"
#include "sms_dat.h"
#include "edGui.h"
#include "numList.h"

void AddToNumList(void *euo)
{
	USER_OP *uo=(USER_OP *)euo;
	NUM_LIST *nl=malloc(sizeof(NUM_LIST));
	zeromem(nl, sizeof(NUM_LIST));
	nl->name=AllocWS(150);
	if(!uo->nltop)
		uo->nltop=nl;
	else
	{
		NUM_LIST *nlx=uo->nltop;
		while(nlx->next)
			nlx=nlx->next;
		nlx->next=nl;
		nl->prev=nlx;
	}
}

void FreeNumList(void *euo)
{
	NUM_LIST *nlx;
	USER_OP *uo=(USER_OP *)euo;
	NUM_LIST *nl=uo->nltop;
	uo->nltop=0;
	while(nl)
	{
		nlx=nl->next;
		if(nl->name)
			FreeWS(nl->name);
		mfree(nl);
		nl=nlx;
	}
}

void DelNumList(void *euo, NUM_LIST *nl)
{
	NUM_LIST *nln;
	NUM_LIST *nlp;
	USER_OP *uo=(USER_OP *)euo;
	if(!nl)
		return;
	nln=nl->next;
	nlp=nl->prev;
	if(nl==uo->nltop)
	{
		if(!nln) //必须保留一个
		{
			nl->num[0]=0;
			CutWSTR(nl->name, 0);
		}
		else
		{
			uo->nltop=nln;
			nln->prev=0;
			if(nl->name)
				FreeWS(nl->name);
			mfree(nl);
		}
	}
	else
	{
		if(nln)
			nln->prev=nlp;
		if(nlp)
			nlp->next=nln;
		if(nl->name)
			FreeWS(nl->name);
		mfree(nl);
	}
}


NUM_LIST *GetNumListCur(void *euo, int n)
{
	USER_OP *uo=(USER_OP *)euo;
	NUM_LIST *nl=uo->nltop;
	int i=1;
	while(nl)
	{
		if(i==n)
			return nl;
		nl=nl->next;
		i++;
	}
	return 0;
}

int InsertToNumList(void *euo, NUM_LIST *nl, int n)
{
	NUM_LIST *nlx;
	NUM_LIST *nln;
	if((!nl)||(!n))
		return 0;
	if(!(nlx=GetNumListCur(euo, n)))
		return 0;
	nln=nlx->next;
	nlx->next=nl;
	nl->prev=nlx;
	nl->next=nln;
	if(nln)
		nln->prev=nl;
	return 1;
}
int isNum(WSHDR *num)
{
	int i=0;
	for(;i<num->wsbody[0];i++)
	{
		int c=num->wsbody[1+i];
		if((c>'9'||c<'0')&&(c!='+'))
			return 0;
	}
	return 1;
}

int IsHaveNumInList(void *euo)
{
	USER_OP *uo=(USER_OP *)euo;
	NUM_LIST *nl=uo->nltop;
	while(nl)
	{
		if(strlen(nl->num))
			return 1;
		nl=nl->next;
	}
	return 0;
}

