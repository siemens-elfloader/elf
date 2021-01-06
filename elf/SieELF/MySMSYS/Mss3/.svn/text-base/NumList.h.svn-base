#ifndef _NUMLIST_H_
#define _NUMLIST_H_

typedef struct _NLST
{
  _NLST *next;
  _NLST *prev;
  char number[50];
  WSHDR *name;
  unsigned short name_body[51];
  WSHDR _name;
}NLST;

class NumList
{
public:
	int IsNumExist(const char *number);
	void ClearNL(NLST *nl);
	NLST * InsertNL_behind(NLST *nl, const char *number);
	NLST * AllocNL(const char *number);
	NLST * InsertNL_front(NLST *nl, const char *number);
	void UpdateNL(NLST *nl, const char *number);
	void UpdateNL(const char *number, int pos);
	int AddNumsToList(const char *nums);
	void DeleteNL(int pos);
	void DeleteNL(NLST *nl);
	void AddToList(const char *number, int pos);
	void AddToList(const char *number);
	void AddToList(NLST *nl);
	void AddToList_first(NLST *nl);
	NLST * FindNL(int pos);
	void AddToList(NLST *nl, int pos);
	void AddToList_end(NLST *nl);
	void FreeList(void);
	NLST * AllocNL();
	NumList();
	~NumList();
	NLST *nltop;
};
#endif
