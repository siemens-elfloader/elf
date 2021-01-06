#include "..\..\inc\swilib.h"

extern void* OldTable;
extern void* OldFRTable;
extern char shortcuts_filename[];
extern char shortcut_names_filename[];
extern char fast_run_filename[];
extern char shortcuts_last_name[];
extern char msg_error[];
extern void run_elf();

/*typedef struct
{
  char name[16];//имя шортката
  void* pointer;//адрес функции
  int unk_zero;
  int unk_1;
  int lgp_full_name;//полное имя
  int unk_2;
  int unk_3;
  int lgp_short_name;//сокращенное имя
  int unk_4;
  int lgp_comment_msg;//текст справки по этому шорткату, в патче - путь к эльфу
}shortcut;*/

void run_elf2(char* ShortCut)
{
  void** table_point=(void**)FreeRAM()+0x1C;
  if ((*table_point)==0){
    ShowMSG(1,(int)msg_error);
  }
  else{
    int i = 0;
    shortcut* table = *table_point;
    while((i<200) && (strcmp(table[i].name,shortcuts_last_name)!=0) && (table[i].name[0]!=0)){
      if (strcmp(table[i].name,ShortCut)==0)
      {
        int len = strlen((char*)(table[i].lgp_comment_msg));
        if (len>5){
          WSHDR *ws = AllocWS(len+1);
          str_2ws(ws,(char*)(table[i].lgp_comment_msg),len);
          ExecuteFile(ws,0,0);
          FreeWS(ws);
        }
        return;
      }
      i++;
    }
  }
}

void* getaddr(int a)
{
  void** table_point=(void**)FreeRAM()+0x1C + a;
  if ((*table_point)!=0){
    return *table_point;
  }
  else{
    int isok=0;
    volatile int hFile;
    unsigned int io_error = 0;
    int len=0;
    FSTATS fstat;
    if (GetFileStats((a==0)?shortcuts_filename:fast_run_filename,&fstat,&io_error)!=-1)
    {
      if ((hFile=fopen((a==0)?shortcuts_filename:fast_run_filename,A_ReadOnly+A_BIN,P_READ,&io_error))!=-1)
      {
        len=fstat.size;
        if ((len>0) && (len <15000)){
          *table_point=malloc(len+1);
          fread(hFile,*table_point,len,&io_error);
          isok=1;
          
          if (a==0){
            char* names;
            if (GetFileStats(shortcut_names_filename,&fstat,&io_error)!=-1)
            {
              fclose(hFile,&io_error);
              if ((hFile=fopen(shortcut_names_filename,A_ReadOnly+A_BIN,P_READ,&io_error))!=-1)
              {
                len=fstat.size;
                if (len>0){
                  names=malloc(len+1);
                  fread(hFile,names,len,&io_error);
                  
                  *(table_point+2) = (void*)&run_elf;
                  int magic = 0x7FFE;
                  int i = 0;
                  int count = 0;
                  shortcut* table = *table_point;
                  while((i<250) && (strcmp(table[i].name,shortcuts_last_name)!=0))
                  {
                    if ((table[i].lgp_full_name == magic) || (table[i].lgp_short_name == magic))
                    {
                      table[i].lgp_full_name = (int)(names+count*160);
                      table[i].lgp_short_name = (int)(names+count*160+16);
                      table[i].lgp_comment_msg = (int)(names+count*160+32);
                      table[i].pointer = (void*)&run_elf;
                      count ++;
                    }
                    i++;
                  }
                }
              }
            }
          }
        }
        fclose(hFile,&io_error);
      }
    }
    if (isok)
      return *table_point;
    else
      return (a==1)?OldTable:OldFRTable;
  }
}

void* return_addr()
{
  return getaddr(0);
}

void* load_fast_run_addr()
{
  return getaddr(1);
}
