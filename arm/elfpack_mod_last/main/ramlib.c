#include "..\..\inc\swilib.h"

extern int get_file_size(const char * fname);
extern unsigned int DEFAULT_DISK_N;
extern void logger(char *log_string, void *address);
extern int RunSWIFromCashe_ep();

__no_init void *(*pLIB_TOP)[];
extern void *Library[];

#define LIB_EMPTY  ((void *)-1L)
#define LIB_SIZE4  16384
#define LIB_SIZE   4096


short  pLIB_TOP_cashe  = 0;
char  *pLIB_TOP_exist  = 0;
int   *pLIB_TOP_backup = 0;

__arm void LoadLibrary()
{
  void *(*lt)[]=pLIB_TOP;
  unsigned int ul;
  int sz;
  int f;
  char fn[128];
  strcpy(fn+1,":\\Zbin\\libs\\swi.blib");
  fn[0]=DEFAULT_DISK_N+'0';
  if (lt)
  {
    pLIB_TOP=NULL;
    mfree(lt);
    lt=NULL;
    if (pLIB_TOP_exist)
     {
      mfree(pLIB_TOP_exist);
      pLIB_TOP_exist = NULL;
     }
    if (pLIB_TOP_backup)
     {
      mfree(pLIB_TOP_backup);
      pLIB_TOP_backup = NULL;
     }
  }
  
  if (!pLIB_TOP_exist)
   {
    pLIB_TOP_exist = malloc(LIB_SIZE);
    for (int i = 0; i < LIB_SIZE; i++) pLIB_TOP_exist[i] = 0xFF;
   }
    
  
  if ((sz=get_file_size(fn))==-1) return;
  if (sz!=LIB_SIZE4)
  {
    MsgBoxError(1,(int)"EP 3.0:\nIllegal blib size!");
    return;
  }
  f=fopen(fn,A_ReadOnly+A_BIN, P_READ, &ul);
  if (f==-1) return;
  lt=malloc(LIB_SIZE4);
  if (fread(f,lt,sz,&ul)!=sz)
  {
    fclose(f,&ul);
    MsgBoxError(1,(int)"EP 3.0:\nCan't read blib!");
  LERR:
    mfree(lt);
    return;
  }
  fclose(f,&ul);
  f=0;
  do
  {
    if (((*lt)[f]!=LIB_EMPTY)&&(Library[f]!=LIB_EMPTY))
    {
      if ((*lt)[f]!=Library[f])
      {
	char s[50];
	sprintf(s,"EP 3.0:\nFunc 0x%03X conflict!",f);
	MsgBoxError(1,(int)s);
	goto LERR;
      }
    }
    if ((*lt)[f]==LIB_EMPTY)
    {
      (*lt)[f]=Library[f];
    }
    f++;
  }
  while(f<LIB_SIZE);
  pLIB_TOP=lt;
  if (pLIB_TOP)
   {
    pLIB_TOP_backup = malloc(LIB_SIZE4);
    memcpy(pLIB_TOP_backup, pLIB_TOP, LIB_SIZE4);
   }
}

__arm void FUNC_ABORT(int f, void *address)
{
 
 if (pLIB_TOP_exist)
  {
   char msg[64];
   sprintf(msg, "FUNC #0x%03X no find in lib!", f);
   if (pLIB_TOP_exist[f] == 0xFF)
    {
     logger(msg, address);
     pLIB_TOP_exist[f] = 0x00;
     MsgBoxError(1,(int)msg);
    }
     else
      {
       logger(msg, address);
      }
   }
}

__arm int SetSWIHookInRAMState_ep()
{
 if (!pLIB_TOP)
  {
   void *pLIB_TOP_copy = malloc(LIB_SIZE4);
   pLIB_TOP_backup = malloc(LIB_SIZE4);
   if (!pLIB_TOP_copy || !pLIB_TOP_backup) return 0;
   memcpy(pLIB_TOP_copy, Library, LIB_SIZE4);
   memcpy(pLIB_TOP_backup, pLIB_TOP_copy, LIB_SIZE4);
   
   pLIB_TOP = pLIB_TOP_copy;
   return 1;
  }
 return 0;
}

int SetSWINumInCashe_ep(short swinum)
{
 if (pLIB_TOP) pLIB_TOP_cashe = swinum;
   else return 0;
 return 1;
}


__arm int SetSWIFunc_ep(void *addrfunc, short swinum)
{
  if (pLIB_TOP)
  {
   LockSched();
   int *pLIB = (int *)pLIB_TOP;
   pLIB[swinum] = (int)addrfunc;
   UnlockSched();
   return 1;
  } else return 0;
}

__arm int RepairSWIFunc_ep(short swinum)
{
  if (pLIB_TOP)
  {
   LockSched();
   int *pLIB = (int *)pLIB_TOP;
   pLIB[swinum] = (int)pLIB_TOP_backup[swinum];
   UnlockSched();
   return 1;
  } else return 0;
}

__arm int RepairSWILib_ep()
{
  if (pLIB_TOP)
  {
   LockSched();
   memcpy(pLIB_TOP, pLIB_TOP_backup, LIB_SIZE4);
   UnlockSched();
   return 1;
  } else return 0;
}


#pragma diag_suppress=Pe177
__root static const int SWILIB_FUNC30B @ "SWILIB_FUNC30B_310" = (int)SetSWIHookInRAMState_ep;
__root static const int SWILIB_FUNC30C @ "SWILIB_FUNC30B_310" = (int)SetSWINumInCashe_ep;
__root static const int SWILIB_FUNC30D @ "SWILIB_FUNC30B_310" = (int)RunSWIFromCashe_ep;
__root static const int SWILIB_FUNC30E @ "SWILIB_FUNC30B_310" = (int)SetSWIFunc_ep;
__root static const int SWILIB_FUNC30F @ "SWILIB_FUNC30B_310" = (int)RepairSWIFunc_ep;
__root static const int SWILIB_FUNC310 @ "SWILIB_FUNC30B_310" = (int)RepairSWILib_ep;
#pragma diag_default=Pe177
