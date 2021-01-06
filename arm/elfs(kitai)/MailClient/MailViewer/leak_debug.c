#ifndef __LEAK_DEBUG__
#define __LEAK_DEBUG__
#include "leak_debug.h"

//------------------------------------------------------------------------------


typedef struct memory_block 
{
  void * pointer;
  int size;
  struct memory_block *next;
  char caller_name[256];
} memory_block;

//------------------------------------------------------------------------------

memory_block *head = 0;

//------------------------------------------------------------------------------

int GetTempName(void)
{
  static const int DMonth[]={0,31,59,90,120,151,181,212,243,273,304,334,365};
  unsigned long iday;
  TTime tt;
  TDate dd;
  GetDateTime(&dd,&tt);
  dd.year=dd.year%100;
  iday=365*dd.year+DMonth[dd.month-1]+(dd.day - 1);
  iday=iday+(dd.year>>2);
  if (dd.month>2||(dd.year&3)>0)
    iday++;
  iday=(tt.sec+60*(tt.min+60*(tt.hour+24* iday)));
  return iday;
} 

//------------------------------------------------------------------------------

void SaveError(char * msg)
{
  char fn[256];
  int f;
  unsigned err;
  
  if(!DEBUG) return;

  snprintf(fn, 255, "0:\\errors%u.txt", GetTempName());

  if ((f=fopen(fn,A_WriteOnly+A_BIN+A_Create+A_Append,P_WRITE,&err))!=-1)
  {
    fwrite(f,msg,strlen(msg),&err);
    fclose(f,&err);
  }   
 
}

//------------------------------------------------------------------------------

void *debug_malloc(int size, char * caller_name)
{
  char msg[512];

  if(size <= 0)
  {
    snprintf(msg, 255, "Attemp allocate zero bytes in \"%s\"!\n", caller_name);
    SaveError(msg);
    return 0;
  }

  void *new_block = malloc(size);
  
  if(new_block==NULL)
  { 
    snprintf(msg, 255, "not allocated ptr in \"%s\" size=%08X!\n", caller_name, size);
    SaveError(msg);
  }
    
  memory_block *ptr = head, *last;
  while(ptr)
  { 
    last = ptr;
    ptr = ptr->next;
  }
  ptr = malloc(sizeof(memory_block));
  if(head) last->next = ptr;
  ptr->next = 0;
  ptr->pointer = new_block;
  ptr->size = size;
  strcpy(ptr->caller_name, caller_name);

  if(!head) head = ptr;
  
//  snprintf(msg, 255, "Allocated %08X!\n", new_block);
 // SaveError(msg);

  return new_block;
}

//------------------------------------------------------------------------------

void debug_mfree(void *block, char * caller_name)
{
  char msg[256];
  memory_block *ptr = head, *last = ptr;
  while(ptr)
  {
    if(ptr->pointer == block)
    {
      if(last == ptr)
        head = head->next;
      else
        last->next = ptr->next;

//  snprintf(msg, 255, "Fried %08X!\n", block);
//  SaveError(msg);
      
      mfree(block);
      mfree(ptr);
      return;
    }
    last = ptr;
    ptr = ptr->next;
  }
  snprintf(msg, 255, "Free not allocated ptr in \"%s\"!\n", caller_name);
 
  SaveError(msg);
  
  LockSched();
  ShowMSG(1,(int)msg);
  UnlockSched();
  
}

//------------------------------------------------------------------------------

void * debug_realloc(void *block, int size, char * caller_name)
{
  char msg[256];
  memory_block *ptr = head, *new_block;

  if(size <= 0)
  {
    snprintf(msg, 255, "Attemp reallocate zero bytes in \"%s\"!\n", caller_name);
    SaveError(msg);
    return 0;
  }

  while(ptr)
  {
//    snprintf(msg, 255, "Old %08X!\n", ptr->pointer);
//    SaveError(msg);
    if(ptr->pointer == block)
    {
      new_block = realloc(block, size);
      ptr->pointer = new_block;
      ptr->size = size;
      strcpy(ptr->caller_name, caller_name);
      return new_block;
    }
    ptr = ptr->next;
  }
  snprintf(msg, 255, "Realloc not allocated ptr in \"%s\" size=%u adr=%08X!\n", caller_name, size, block);

  SaveError(msg);
  
  LockSched();
  ShowMSG(1,(int)msg);
  UnlockSched();
  return 0;
}

//------------------------------------------------------------------------------

void Clean()
{
  char fn[256], leak[256], msg[256];
  unsigned err, i = 0;
  int f;
  memory_block *ptr = head, *last;
  while(ptr)
  {
    snprintf(fn, 255, "0:\\leaks%u.txt", GetTempName());
    snprintf(leak, 255, "Allocated in function \"%s\", size %u bytes, adr = %08X\n",
             ptr->caller_name, ptr->size, ptr->pointer);
    mfree(ptr->pointer);

    if ((f=fopen(fn,A_WriteOnly+A_BIN+A_Create+A_Append,P_WRITE,&err))!=-1)
    {
      fwrite(f,leak,strlen(leak),&err);
      fclose(f,&err);
    }          
    last = ptr;
    ptr = ptr->next;
    mfree(last);
    i++;
  }  
  if(i)
  {
    snprintf(msg, 255, "Total leaks %u", i);
  
    LockSched();
    ShowMSG(1,(int)msg);
    UnlockSched();
  }
}

//------------------------------------------------------------------------------

#endif
