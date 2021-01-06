//Draw Handler System

#include "..\..\inc\swilib.h"

#include "dhs.h"

DHS_TOP *dhs = 0;
int priodraw = 0;

__arm void DHS_init()
{
 LockSched();
 dhs = malloc(sizeof(DHS_TOP));
 if (dhs)
  {
   dhs->first   = DHS_FIRST_ITEM;
   dhs->count   = DHS_ZERO;
   dhs->unlock  = DHS_UNLOCKDVALUE;
   dhs->last    = DHS_LAST_ITEM;
   priodraw     = DHS_ZERO;
  }
  UnlockSched();
}

__arm void DHS_kill()
{
 if (dhs)
  {
   if (dhs->first != DHS_FIRST_ITEM)
    {
     LockSched();
     DHS_ITEM *dhsi = dhs->first;
     do
     {
       DHS_ITEM *dhsi_s = dhsi;
       dhsi = dhsi->next;
       zeromem((void *)dhsi_s, sizeof(DHS_ITEM));
       if (dhsi_s) mfree(dhsi_s);
     }
     while (dhsi->next != DHS_LAST_ITEM);
     zeromem((void *)dhs, sizeof(DHS_TOP));
     mfree(dhs);
     dhs = DHS_ZERO;
     priodraw = DHS_ZERO;
     UnlockSched();
    }
    else priodraw = DHS_ZERO;
  }
}

__thumb void DHS_drawItems(LCDLAYER *layer)
{
  if (dhs)
    {
     if (dhs->unlock == DHS_UNLOCKDVALUE) 
      {
       if (dhs->first != DHS_FIRST_ITEM)
        {
         DHS_ITEM *dhsi = dhs->first;
         do
         {
          if (dhsi != DHS_LAST_ITEM)
           {
            dhsi->dh_proc(layer);
            dhsi = (DHS_ITEM *)dhsi->next;
           }
          }
         while (dhsi != DHS_LAST_ITEM);
       }
    }
    if (priodraw)
     {
       ((void (*)(LCDLAYER *))(priodraw))(layer);
     }
  }
}

__arm int DHS_addProc_ep(void (*dh_proc)(LCDLAYER *))
{
  if (dhs)
   {
     DHS_ITEM *dhsi = dhs->first;
     if (dhs->first == DHS_FIRST_ITEM)
      {
        LockSched();
        DHS_ITEM *dhsi_r = malloc(sizeof(DHS_ITEM));
        if (!dhsi_r) return DHS_NULL;
        dhsi_r->next = DHS_LAST_ITEM;
        dhsi_r->prev = DHS_FIRST_ITEM;
        dhsi_r->dh_proc = dh_proc;
        dhs->first = dhsi_r;
        dhs->last = dhsi_r;
        dhs->count++;
        UnlockSched();
        return 1;
      }
       else
        {
          while (dhsi->next != DHS_LAST_ITEM) dhsi = dhsi->next;
          if (dhsi->next == DHS_LAST_ITEM)
           {
            LockSched(); 
            DHS_ITEM *dhsi_r = malloc(sizeof(DHS_ITEM));
            if (!dhsi_r) return DHS_NULL;
            dhsi_r->next = DHS_LAST_ITEM;
            dhsi_r->prev = dhsi;
            dhsi_r->dh_proc = dh_proc;
            dhsi->next = dhsi_r;
            dhs->last = dhsi_r;
            dhs->count++;
            UnlockSched();
            return 1;
           }
        }
    }
  return DHS_ZERO;
}

__arm int DHS_removeProc_ep(void (*dh_proc)(LCDLAYER *))
{
 if (dhs)
  {
   if (dhs->first != DHS_FIRST_ITEM)
    {
     DHS_ITEM *dhsi = dhs->first;
     do
      {
       if (dhsi->dh_proc == dh_proc)
        {
         //Удаление единственного процесса 
         if (dhsi->prev == DHS_FIRST_ITEM && dhsi->next == DHS_LAST_ITEM)
          {
           LockSched();
           dhs->first = DHS_FIRST_ITEM;
           dhs->last  = DHS_LAST_ITEM;
           zeromem((void *)dhsi, sizeof(DHS_ITEM));
           if (dhsi) mfree(dhsi);
           dhs->count--;
           UnlockSched();
           return 1;
          }
         
         //Удаление первого процесса из списка 
         if (dhsi->prev == DHS_FIRST_ITEM && dhsi->next != DHS_LAST_ITEM)
          {
           LockSched();
           DHS_ITEM *dhsn = (DHS_ITEM *)dhsi->next;
           dhs->first = dhsn;
           dhsn->prev = DHS_FIRST_ITEM;
           zeromem((void *)dhsi, sizeof(DHS_ITEM));
           if (dhsi) mfree(dhsi);
           dhs->count--;
           UnlockSched();
           return 1;
          }
         
         //Удаление последнего процесса из списка 
         if (dhsi->prev != DHS_FIRST_ITEM && dhsi->next == DHS_LAST_ITEM)
          {
           LockSched();
           DHS_ITEM *dhsp = (DHS_ITEM *)dhsi->prev;
           dhs->last  = dhsp;
           dhsp->next = DHS_LAST_ITEM;
           zeromem((void *)dhsi, sizeof(DHS_ITEM));
           if (dhsi) mfree(dhsi);
           dhs->count--;
           UnlockSched();
           return 1;
          }  else
              {
               //Удаление процесса из списка 
               LockSched();
               DHS_ITEM *dhsp = (DHS_ITEM *)dhsi->prev;
               DHS_ITEM *dhsn = (DHS_ITEM *)dhsi->next;
               dhsp->next = dhsn;
               dhsn->prev = dhsp;
               zeromem((void *)dhsi, sizeof(DHS_ITEM));
               if (dhsi) mfree(dhsi);
               dhs->count--;
               UnlockSched();
               return 1;
             }
       }
      dhsi = (DHS_ITEM *)dhsi->next;
     } while (dhsi != DHS_LAST_ITEM);
    return DHS_NULL;
   }
  }
 return DHS_ZERO;
}


__thumb void DHS_lockDraw_ep(int lock)
{
 if (dhs)
  {
   if (!lock)
     dhs->unlock  = DHS_UNLOCKDVALUE;
    else
     dhs->unlock  = DHS_ZERO;
  }
}

__thumb DHS_TOP *DHS_getBaseAddr_ep()
{
 return dhs;
}

__thumb int DHS_getStatusItem_ep(void (*dh_proc)(LCDLAYER *))
{
 if (dhs)
  {
   if (priodraw == (int)dh_proc)  return 2;
   if (dhs->first != DHS_FIRST_ITEM) 
    {
     if (dhs->first == dhs->last)  return -2;
     if (dh_proc == dhs->last->dh_proc)  return  1;
     if (dh_proc == dhs->first->dh_proc) return DHS_NULL;
     return DHS_ZERO;
    }
    return  -3;
  }
 return  -4;
}


__arm int DHS_workProcPrio_ep(void (*dh_proc)(LCDLAYER *), int work)
{
 if (dhs)
  {
    if (work == DHS_PRIOPROC_GETSTAT)
     {
      if (priodraw) return 1;
               else return DHS_ZERO;
     }
    
    if (work)
    {
     if (!priodraw)
      {
        LockSched();
        priodraw = (int)dh_proc;
        UnlockSched();
        return 1;
      } else return DHS_ZERO;
    } else 
      {
       if (priodraw)
        {
          LockSched();
          priodraw = DHS_ZERO;
          UnlockSched();
          return 1;
        } else return DHS_ZERO;
      }
  }
 return DHS_NULL;
}


#pragma diag_suppress=Pe177
__root static const int SWILIB_FUNC319 @ "SWILIB_FUNC319_31E" = (int)DHS_addProc_ep;
__root static const int SWILIB_FUNC31A @ "SWILIB_FUNC319_31E" = (int)DHS_removeProc_ep;

__root static const int SWILIB_FUNC31B @ "SWILIB_FUNC319_31E" = (int)DHS_lockDraw_ep;
__root static const int SWILIB_FUNC31C @ "SWILIB_FUNC319_31E" = (int)DHS_getBaseAddr_ep;


__root static const int SWILIB_FUNC31D @ "SWILIB_FUNC319_31E" = (int)DHS_getStatusItem_ep;
__root static const int SWILIB_FUNC31E @ "SWILIB_FUNC319_31E" = (int)DHS_workProcPrio_ep;
#pragma diag_default=Pe177

