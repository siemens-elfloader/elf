#include "..\..\inc\swilib.h"

typedef struct
{
  void *next;
  int is_folder;
  char *fullname;  
  char *name;  
}FLIST;

typedef struct
{
  void *gui;
  int type;
}FVIEW;


void SavePath(void *ed_gui, FLIST *fl);
void patch_header(const HEADER_DESC* head);
void open_select_file_gui(void *ed_gui, int type);

