#ifndef _BOOKMARKS_H_
#define _BOOKMARKS_H_

class BookmarksList
{
public:
  BookmarksList();
  ~BookmarksList();
  
  enum ItemType
  {
    IS_BACK,
    IS_FOLDER,
    IS_FILE
  };
  struct ItemsList
  {
    ItemsList * next;
    ItemType type;
    char * fullname;  
    char * name;  
  };
  
  static BookmarksList * Top;
  
  ItemsList * top_list;
  ItemsList * FindItemByN(int n);
  int FindFilesInFolder(char * folder);
  char * current_folder;
private:
  void FreeList(); // Очистить список
  ItemsList * AddItemToList(const char * full_name, const char * name, ItemType type); // Добавить обьект в список
  ItemsList * FindItemByNS(int *i, ItemType type);
};

class BookmarksInput
{
public:
  BookmarksInput();
  ~BookmarksInput();
  
  enum EDIT_MODE
  {
    EditBookmark,
    CreateBookmark,
    RenameFolder,
    CreateFolder
  };
  int onKey(GUI *gui, GUI_MSG *msg);
  void gHook(GUI *gui, int cmd);
  void Show(EDIT_MODE _mode, BookmarksList::ItemsList * _il);
  char * extract_name(GUI * gui);
  char * extract_link(GUI * gui);
  BookmarksList::ItemsList * il;
private:
  EDIT_MODE mode;
  
  int gui_id;
  
  int name_pos;
  int url_pos;
  char * name;
  char * url;
};

class BookmarksOptions
{
public:
  BookmarksOptions();
  ~BookmarksOptions();
  
  void gHook(void * data, int cmd);
  void Show(BookmarksList::ItemsList * _il);
  
  int gui_id; // ID меню опций
  BookmarksList::ItemsList * il;
};

class BookmarksMenu
{
public:
  BookmarksMenu();
  ~BookmarksMenu();

  int onKey(void * data, GUI_MSG * msg);
  void gHook(void * data, int cmd);
  void ItemHandler(void * data, int curitem, void * unk);
  void Show(void * inp_data);
  
  BookmarksList * list;

  void * input_data;
};

#endif
