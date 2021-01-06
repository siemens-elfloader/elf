#include "..\..\inc\swilib.h"
#include "..\tbase_work\tbase.h"
#include "prepatch.h"



int pmode    = 0;
int bcounts  = 0;
int bcurrent = 0;
PATCH_ITEM *pbuffer = 0;


void SetPrePatchMode(int m)
{
  if (m == 2)
   {
    pmode    = 0;
    bcounts  = 0;
    bcurrent = 0;
    if (pbuffer && pbuffer != (PATCH_ITEM *)-1)
     {
      mfree(pbuffer);
      zeromem(pbuffer, sizeof(PATCH_ITEM)*bcounts);
      pbuffer = 0;
     }
    pbuffer  = 0;
   } else pmode = m;
}

int PrePatch(void *addr, char old_data, char new_data)
{
 if (!pmode)
  {
    bcounts++;
    return 0;
  } else
     {
      if (bcounts)
       {
        if (!pbuffer)
         {
           pbuffer = malloc(sizeof(PATCH_ITEM)*bcounts);
           bcurrent = 0;
           if (!pbuffer) 
            {
              pbuffer = (PATCH_ITEM *)-1;
              return -1;
            } else zeromem(pbuffer, sizeof(PATCH_ITEM)*bcounts);
         }
           
        if (pbuffer != (PATCH_ITEM *) -1)
         {
          pbuffer[bcurrent].address  = addr;
          pbuffer[bcurrent].old_data = old_data;
          pbuffer[bcurrent].new_data = new_data;
          bcurrent++;
          return 1;
         }
       }
     }
 return -1;
}

int PatchFunction(int type)
{
 if (pmode && bcounts)
  {
   if (pbuffer != (PATCH_ITEM *) -1  && pbuffer)
    {
     for (int i = 0; i < bcounts; i++)
      { 
       switch (type)
        {
         case 0: ApplyPatch(pbuffer[i].address, pbuffer[i].new_data); break;
         case 1: UndoPatch(pbuffer[i].address, pbuffer[i].old_data);  break;
         case 2: ApplyPatch(pbuffer[i].address, pbuffer[i].old_data); break;
        }
      }
     return 1;
    }
   return -1;
  }
 return 0;
}

