#ifndef _CL_WORK_H_
  #define _CL_WORK_H_


void FreeXText(CLIST *t);
void FreeCLIST(void);
void FillAllOffline(void);

CLIST *FindContactByUin(unsigned int uin);
CLIST *FindGroupByID(unsigned int grp);

CLIST *FindContactByNS(int *i, int si, int act_flag, CLIST *search_contact);
int CountContacts(void);
CLIST *FindContactByN(int i);
int FindContactByContact(CLIST *p);
void SwapContacts(CLIST *first, CLIST *second);
void ChangeContactPos(CLIST *p);
int CompareContacts(CLIST *t, CLIST *p);

void ResortCL(void);
CLIST *AddContactOrGroup(CLIST **top, CLIST *p);
CLIST *AddContact(unsigned int uin, char *name, unsigned int group, int local);
CLIST *AddGroup(unsigned int grp, char *name);
void DeleteContact(CLIST *p);

void LoadLocalCL(void);

#endif
