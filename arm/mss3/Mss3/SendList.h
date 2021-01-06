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
	SendList();
	~SendList();
	static void Send(SendList *sndlst);
	void CatList(SNDLST *sl);
	int SendEnd(int csm_id);
	void AddToList(const char *number, WSHDR *text);
	
	SNDLST * sltop;

private:
	static void SendOnTop(SendList *sndlst);
	int IsSendCSM(int csm_id);
	int SendStart(void);
	int IsSending(void);
	SNDLST * FindSL(int csm_id);
	void DeleteSL(SNDLST *sl);
	void AddToList(SNDLST *sl);
	void FreeList();
	SNDLST * AllocSL();
	static void CsmToTop(int csm_id);
	
	static IPC_REQ ipc_xtask;
};
#endif
