
typedef struct
{
	void *next;
	void *prev;
	char *name;
	int name_len;
	char *func;
	int func_len;
	int type;
	int IsEdited;
}MENU_LIST;


typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
}MAIN_GUI;


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
