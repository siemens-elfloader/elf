#ifndef _FILES_MENU_H_
#define _FILES_MENU_H_

class FilesList
{
public:
  FilesList();
  ~FilesList();
  
  enum FILE_TYPES
  {
    IS_BACK,
    IS_FOLDER,
    IS_FILE
  };
  
  struct FLIST
  {
    FLIST * next;
    FILE_TYPES type;
    char * fullname;  
    char * name;  
  };
  FLIST * fltop;
  
  void Free_FLIST();
  FLIST * AddFileToList(const char * full_name, const char *name, FILE_TYPES type);
  int FindFiles(char * str);
  FLIST * FindFileByNS(int * i, FILE_TYPES type);
  FLIST * FindFileByN(int n);
};

class FilesMenu
{
public:
  enum FIND_TYPES
  {
    FIND_FOLDERS,
    FIND_ALL,
  };
  
  FilesMenu();
  ~FilesMenu();
  
  void Show(void * inp_data, FIND_TYPES type);
  int onKey(void *data, GUI_MSG *msg);
  void gHook(void *data, int cmd);
  void ItemHandler(void *data, int curitem, void *unk);
  
  FilesList * list;
  static FilesMenu * Top;
  FIND_TYPES find_type;
private:
  void * input_data;
  
  int CreateRootMenu();
  
};

#endif
