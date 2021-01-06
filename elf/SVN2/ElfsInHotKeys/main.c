#include "../inc/swilib.h"
#include "conf_loader.h"

extern unsigned long  strtoul (const char *nptr,char **endptr,int base);
extern const int i_action;
extern const char action_parameter[256];

void OpenConfig(char *filename)
{
  WSHDR *ws;
  ws = AllocWS(256);
  WSHDR *xws;
  xws=AllocWS(256);
  int id;
  str_2ws(xws,"bcfg",255);
  str_2ws(ws, filename, 255);
  id=GetExtUid_ws(xws);
  TREGEXPLEXT *pr=get_regextpnt_by_uid(id);
  typedef unsigned int (*func)(WSHDR *p1, WSHDR *p2, int p3);
  func myproc = (func)(pr->proc);
  myproc(ws, xws, 0);
  FreeWS(ws);
  FreeWS(xws);
}

int main()
{
  // ���������� ������� �������
  char *current_key="";
  current_key = RamPressedKey();
  if(strlen(current_key)==0)
  {
    ShowMSG(1, (int)"Press on key not enough long!!!");
    return 0;
  }
  // ��������� ������� �������� X:\ZBin\etc\hotkeys
  int found = 0;
  unsigned int err;
  if(isdir("4:\\Zbin\\etc", &err))
  {
    found = 1;
    // ���� ����� Zbin\etc �� ����� 4 ��������� ������� ��� hotkeys
    if(!isdir("4:\\Zbin\\etc\\hotkeys", &err))
    {
      // ���� �� ������� - �������
      mkdir("4:\\Zbin\\etc\\hotkeys", &err);
    }
  }
  else
  {
    // ����� ���� Zbin\etc �� ����� 0
    if(isdir("0:\\Zbin\\etc", &err))
    {
      found = 1;
      // ���� ����� - ���� hotkeys
      if(!isdir("0:\\Zbin\\etc\\hotkeys", &err))
      {
        mkdir("0:\\Zbin\\etc\\hotkeys", &err);        
      }
    }
  }
  if (!found) // ���� ���� �� ����� - ������� �����
  {
    ShowMSG(1, (int)"Path '?:\\Zbin\\etc' not found!");
    return 0;
  }
  // ������ ������
  char *config_name = malloc(256);
  sprintf(config_name, "4:\\ZBin\\etc\\hotkeys\\ElfsInHotkeys_%s.bcfg",current_key);
  if (LoadConfigData(config_name)<0) // ���� ������ �� ����� 4
  {
    config_name[0] = '0';
    if (LoadConfigData(config_name)<0) // ���� ������ �� ����� 0
    {
      ShowMSG(1, (int)"Unsupported button :("); // ���������
      return 0;
    }
  }
  // ������� � ���������� �� ������
  char *parameter;
  parameter = (char*)action_parameter;
  switch(i_action)
  {
  case 0:
    {
      // ������ �� �����������... ��������� ������ �� ��������������
      OpenConfig(config_name);
    }
    break;
  case 1:
    {
      // ������ �����
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname,parameter);
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
    }
    break;
  case 2:
    {
      // �������
      unsigned int* addr = (unsigned int*)GetFunctionPointer(parameter);
      if (addr)
      {
        typedef void (*voidfunc)(); 
#ifdef NEWSGOLD          
        voidfunc pp=(voidfunc)*(addr+4);
#else 
        voidfunc pp=(voidfunc)addr; 
#endif 
        SUBPROC((void*)pp);
      }
    }
    break;
  case 3:
    {
      // ������
      typedef void (*voidfunc)(); 
      unsigned int addr=strtoul(parameter, 0, 16 );
      voidfunc pp=(voidfunc)addr;
      SUBPROC((void*)pp);
    }
    break;
  }
  return 0;
}
