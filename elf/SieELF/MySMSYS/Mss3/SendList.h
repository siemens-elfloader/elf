#ifndef _SENDLIST_H_
#define _SENDLIST_H_
typedef struct _SNDLST
{
  _SNDLST *next;
  _SNDLST *prev;
  int csm_id;
  //int send_fail;
  char number[50];
  WSHDR *text;
}SNDLST;

class SendList
{
public:
	static void Send(SendList *sndlst);
	static void SendOnTop(SendList *sndlst);
	void CatList(SNDLST *sl);
	int IsSendCSM(int csm_id);
	int SendEnd(int csm_id);
	int SendStart(void);
	int IsSending(void);
	SNDLST * FindSL(int csm_id);
	void DeleteSL(SNDLST *sl);
	void AddToList(const char *number, WSHDR *text);
	void AddToList(SNDLST *sl);
	SendList();
	~SendList();
	void FreeList();
	SNDLST * AllocSL();
	SNDLST * sltop;
};
#endif
