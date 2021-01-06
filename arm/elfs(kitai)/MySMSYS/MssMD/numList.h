
typedef struct
{
	void *prev;
	void *next;
	char num[50];
	WSHDR *name;
}NUM_LIST;


void AddToNumList(void *euo);

void FreeNumList(void *euo);

void DelNumList(void *euo, NUM_LIST *nl);
NUM_LIST *GetNumListCur(void *euo, int n);
int isNum(WSHDR *num);
int InsertToNumList(void *euo, NUM_LIST *nl, int n);
int IsHaveNumInList(void *euo);

