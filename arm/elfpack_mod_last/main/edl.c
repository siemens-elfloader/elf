
#include "..\..\inc\swilib.h"
#include "edl.h"

//Main pointer on EDL Base
int *pEDL_TOP = 0;


// EDL System Init
// 0 - EDL ������� ��� �������� (EDL System is launched)
// 1 - EDL ������� ������� (EDL System is created)
__arm int EDL_system_init()
{
 if (pEDL_TOP) return 0;
 pEDL_TOP = malloc(4*EDL_MAXSIZE);
 if (pEDL_TOP)
  {
   for (int i = 0; i < EDL_MAXSIZE; i++)
    {
     pEDL_TOP[i] = EDL_VOID;
    }
  } else return 0; 
 return 1;
}

// EDL System Kill
// 0 - EDL ������� �� �������� ��� �� �������� (EDL System don't load or don't work)
// 1 - EDL ������� ����� (EDL System is killed)
__arm int EDL_system_kill()
{
 if (pEDL_TOP)
  {
    for (int i = 0; i<EDL_MAXSIZE; i++)
     {
      if (pEDL_TOP[i] != 0 || pEDL_TOP[i] != EDL_VOID)
       {
         EDL_HEADER *edl = (EDL_HEADER *)pEDL_TOP[i];
         edl->killproc();
         pEDL_TOP[i] = EDL_VOID;
       }
     }
    
    zeromem((void *)pEDL_TOP, EDL_MAXSIZE*4);
    mfree(pEDL_TOP);
    pEDL_TOP = 0;
    return 1;
  }
 return 0;
}

// EDL System ReInit
__arm int EDL_system_reinit()
{
 if (EDL_system_kill())
  {
   return EDL_system_init();
  } 
  else
   return EDL_system_init();
}

//-1 - �� �������! (No find)
//-2 - EDL ������� �� �������� ��� �� �������� (EDL System don't load or don't work)
//+i - �������� ������� ��������� ���������� (Place find lib)
__arm int isEDL_exist_ep(char *name, short version)
{
  if (!pEDL_TOP) return -2;
  for (int i = 0; i<EDL_MAXSIZE; i++)
   {
    if (pEDL_TOP[i] != EDL_VOID)
     {
      EDL_HEADER *edl_struct = (EDL_HEADER *)pEDL_TOP[i];
      
      if (!strcmp(name, edl_struct->name))
       {
        if (version == edl_struct->version) return i;
       }
      }
    }
   return -1;
}

//0 - ���������� �� �������������� (Current Library don't support)
//1 - ���������� �������������� (Current Library support)
__arm int isEDL_support_ep(char platform, char *phone, short sw)
{
 if (!platform) return 1;
 else
  {
   char p = 0; 
   if (isSGoldX75() == 0) p =  platform&EDL_PLATFORM_SGX65;
   if (isSGoldX75() == 1) p = (platform&EDL_PLATFORM_SGX75)>>1;
   if (isSGoldX75() == 2) p = (platform&EDL_PLATFORM_NSG)>>2;
   if (isSGoldX75() == 3) p = (platform&EDL_PLATFORM_ELKA)>>3;
   
   if (p == 1)
    {
     if (!strcmp(phone, EDL_PHONE_NONE) || !strcmp(phone, Get_Phone_Info(PI_MODEL)))
      {
       char sw_str[8];
       sprintf(sw_str, "%d", sw);
       if (!sw || !strcmp(sw_str, Get_Phone_Info(PI_SW_NUMBER))) return 1;
      }
    }
  }
 return 0;
}

// -100  - ��� ����� (File is not find)
// -101  - ���� �� �����������/�� �������� (File don't open / don't read)
// -102  - ������������ ������ (Is not memory)
// -103  - C�������� EDL_HEADER �� ���������� (EDL_HEADER struct is not detect)
// -104  - EDL ������� �� �������� ��� �� �������� (EDL system don't work or don't load)
// -105  - ������ ���������� ��� ���������� (Library is exist)
// -106  - � ���������� ��� �� ����� �-�� (In library zero count functions)
// -107  - ���������� �� �������������� (Library is not support)

// -1 .. -13 - ������ ������� 'ELF' (Errors of ELF format)

// +i    - ���������� ���������! i - �������� ���-�� �-�� (Library is loaded, i is count functions of library)
__arm int EDL_load_ep(char *fname)
{
  char fn[256];
  strcpy(fn, fname);
  if (fname[1] != ':')
   {
     sprintf(fn, "X:\\Zbin\\libs\\%s.edl", fname);
     fn[0] = '0' + DEFAULT_DISK_N;
   }
  
  int edl_size = get_file_size(fn);
  if (edl_size == -1) return -100;
  int edl = fopen(fn, A_ReadOnly+A_BIN, P_READ, 0);
  if (edl < 0) return -101;
  
  
  char *data = malloc(edl_size);
  if (!data) return -102;
     
  fread(edl, data, edl_size, 0);
  fclose(edl, 0);
     
  int edlpos = 0;
  int edl_id[3]={EDL_ID1,EDL_ID2,EDL_ID3};
  for (int i=0; i<edl_size; i++)
   {
    if (memcmp((char *)data + i, (char *)edl_id, 12) == 0)
     {
      edlpos = i;
      goto END_SCAN_EDLFILE;
     }
    }
  
  return -103;
  
  END_SCAN_EDLFILE:
  
  asm("NOP");
   
  EDL_HEADER *edls = malloc(sizeof(EDL_HEADER));
  memcpy(edls, data + edlpos, sizeof(EDL_HEADER));
   
  zeromem((void *)data, edl_size);
  mfree(data);

   int ex = isEDL_exist_ep(edls->name, edls->version);
   if (ex == -1)
    {
     if (isEDL_support_ep(edls->platform, edls->phone, edls->sw))
      {
       short count = edls->count;
       mfree(edls);
       if (!count) return -106;
       short res = elfload(fn, "", 0, 0);
       if (!res) return count;
            else return res;
      } else 
         {
          mfree(edls);
          return -107;
         }
    } else 
         {
          mfree(edls);
          if (ex == -2) return -104; 
                   else return -105;
         }
}


//  0 - ���������� �� ���������� (Library is not exist)
// -1 - EDL ������� �� �������� ��� �� �������� (EDL system don't work or don't load)
//  1 - ���������� ��������� (Library unload from RAM)
__arm int EDL_unload_ep(char *name, short version)
{
  int plc = isEDL_exist_ep(name, version);
  if (plc == -1) return 0;
  if (plc == -2) return -1;
  if (plc >= 0)
   {
     EDL_HEADER *edl = (EDL_HEADER *)pEDL_TOP[plc];
     edl->killproc();
     pEDL_TOP[plc] = EDL_VOID;
     return 1;
   }
  else return 0;
}



//  0 - ���������� ��� ���������� (Library is exist)
// -1 - EDL ������� �� �������� ��� �� �������� (EDL system don't work or don't load)
//  1 - ��������� (Library added in base)
__arm int EDL_addlib_ep(EDL_STRUCT *edl_struct)
{
  int plc = isEDL_exist_ep(edl_struct->edl_head.name, edl_struct->edl_head.version);
  if (plc >= 0) return 0;
  else
     {
      if (plc == -1)
       {
        for (int i = 0; i<EDL_MAXSIZE; i++)
         {
           if (pEDL_TOP[i] == EDL_VOID)
            {
             pEDL_TOP[i] = (int)edl_struct;
             return 1;
            }
         }
       } else return -1;
     }
  return -1;
}


//  0 - ���������� �� ���������� (Library is not exist)
// -1 - EDL ������� �� �������� ��� �� �������� (EDL system don't work or don't load)
//  1 - ���������� ������ �� ������� (�� ��� ����� � RAM) / Library is removed, but she in RAM
__arm int EDL_remove_ep(EDL_STRUCT *edl_struct)
{
  int plc = isEDL_exist_ep(edl_struct->edl_head.name, edl_struct->edl_head.version);
  if (plc == -1) return 0;
  if (plc == -2) return -1;
  if (plc >=  0)
    {
      pEDL_TOP[plc] = EDL_VOID;
      return 1;
    }
  return 0;
}


//  0 - ���������� �� ���������� (Library is not exist)
// -1 - EDL ������� �� �������� ��� �� �������� (EDL system don't work or don't load)
//  1 - ������ �-�� ��������� (Addresses functions filled) 
__arm int EDL_use_ep(char *name, short version, void *func_struct)
{
 int pls = isEDL_exist_ep(name, version);
 if (pls == -1) return 0;
 if (pls == -2) return -1;
 else
  {
   EDL_STRUCT *edl = (EDL_STRUCT *)pEDL_TOP[pls];
   memcpy(func_struct, &edl->edl_pnt.func_first, edl->edl_head.count*4);
   return 1;
  }
}

// ���������� ��������� �� ���� ���������� (Return pointer on Library)
__arm void *getEDL_baseAddr_ep()
{
 return pEDL_TOP;
}

// ���������� ������� ���-�� ����������� ��������� (Return �urrent count libs)
__arm int getEDL_curLibs_ep()
{
 int cur = 0; 
 for (int i = 0; i<EDL_MAXSIZE; i++)
  {
   if (pEDL_TOP[i] != EDL_VOID) cur++;
  }
 return cur;
}

// ���������� ������������ ���-�� ����������� ��������� (Return max count libs)
__arm int getEDL_maxLibs_ep()
{
 return EDL_MAXSIZE;
}


// isSGoldX75()
#ifdef NEWSGOLD
#ifdef ELKA
#pragma diag_suppress=Pe177
__root static const int SWILIB_FUNC300 @ "SWILIB_FUNC300_30A" = 0x00000003;
#pragma diag_default=Pe177
#else
#pragma diag_suppress=Pe177
__root static const int SWILIB_FUNC300 @ "SWILIB_FUNC300_30A" = 0x00000002;
#pragma diag_default=Pe177
#endif
#else
#ifdef X75
#pragma diag_suppress=Pe177
__root static const int SWILIB_FUNC300 @ "SWILIB_FUNC300_30A" = 0x00000001;
#pragma diag_default=Pe177
#else
#pragma diag_suppress=Pe177
__root static const int SWILIB_FUNC300 @ "SWILIB_FUNC300_30A" = 0x00000000;
#pragma diag_default=Pe177
#endif
#endif



#pragma diag_suppress=Pe177
__root static const int SWILIB_FUNC301 @ "SWILIB_FUNC300_30A" = (int)EDL_load_ep;
__root static const int SWILIB_FUNC302 @ "SWILIB_FUNC300_30A" = (int)EDL_unload_ep;

__root static const int SWILIB_FUNC303 @ "SWILIB_FUNC300_30A" = (int)EDL_addlib_ep;
__root static const int SWILIB_FUNC304 @ "SWILIB_FUNC300_30A" = (int)EDL_remove_ep;
__root static const int SWILIB_FUNC305 @ "SWILIB_FUNC300_30A" = (int)EDL_use_ep;

__root static const int SWILIB_FUNC306 @ "SWILIB_FUNC300_30A" = (int)isEDL_exist_ep;
__root static const int SWILIB_FUNC307 @ "SWILIB_FUNC300_30A" = (int)isEDL_support_ep;
__root static const int SWILIB_FUNC308 @ "SWILIB_FUNC300_30A" = (int)getEDL_baseAddr_ep;
__root static const int SWILIB_FUNC309 @ "SWILIB_FUNC300_30A" = (int)getEDL_curLibs_ep;
__root static const int SWILIB_FUNC30A @ "SWILIB_FUNC300_30A" = (int)getEDL_maxLibs_ep;
#pragma diag_default=Pe177

