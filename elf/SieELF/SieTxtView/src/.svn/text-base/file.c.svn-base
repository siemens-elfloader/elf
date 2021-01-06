#include "..\..\inc\swilib.h"
#include "..\inc\main.h"
#include "..\inc\menu.h"
#include "..\inc\file.h"
#include "..\inc\buff.h"
#include "..\inc\code.h"
#include "..\inc\history.h"

int fileSize = 0;
unsigned int err;
int fd;

typedef struct {
	void *next;
	int is_folder;
	char *fullname;
	char *name;
	int is_cur;
} FLIST;

typedef struct {
	void *gui;
	int type;
} FVIEW;

volatile FLIST *fltop;
enum TYPES {IS_BACK, IS_FOLDER, IS_FILE};
const char back[] = "..";
//char header[128];
WSHDR *hdr_t=0;
int openFile(char* filename) {
	if (fd > 0)
		fclose(fd, &err);
	buffed = 0;
	if ((fd = fopen(filename, A_ReadOnly + A_BIN, P_READ, &err)) != - 1) {
		char* head = (char*)malloc(3);
		fread(fd, head, 3, &err);
		codetype = getCodeType(head);
		//#ifndef NEWSGOLD
                fileSize = lseek(fd, 0, S_END, &err, &err);
                lseek(fd, 0, S_SET, &err, &err);
                //#else
		//fileSize = GetFileSize(filename);
                //#endif
		mfree(head);
		return 1;
	}
	return 0;
}

void Free_FLIST(void) {
	LockSched();
	FLIST *fl = (FLIST *)fltop;
	fltop = 0;
	UnlockSched();
	while (fl) {
		FLIST *fl_prev = fl;
		fl = fl->next;
		mfree(fl_prev);
	}
}

//File Name
char* GetFileExt(char* fname) {
	char *s1, *s2;
	s1 = strrchr(fname, '.');
	if (s1) {
		int i = 0;
		s2 = ++s1;
		while (*s2++)
			i++;
		if (i > MAX_EXT)
			s1 = 0;
	}
	return s1;
}

char* GetFileName(char* fname) {

	int len = strlen(fname);
	int ii;
	for (ii = len - 1; ii >= 0; ii--) {
		if (fname[ii] == '\\' || fname[ii] == '/')
			break;
	}
	if (ii>=0)
		return fname+ii+1;
	return fname;
}

char* GetFileDir(char* fname, char* buf) {
	int ii;
	int len = strlen(fname);

	for (ii = len-2; ii > 0; ii--)
		if (fname[ii] == '\\' || fname[ii] == '/')
			break;
	len = ii;

	if (buf) {
		for (ii = 0; ii < len; ii++)
			buf[ii] = fname[ii];
		buf[len] = 0;
	}
	return buf;
}

int strcmp_nocase(const char *s, const char *d) {
	int cs;
	int ds;
	do {
		cs = *s++;
		if (cs & 0x40)
			cs &= 0xDF;
		ds = *d++;
		if (ds & 0x40)
			ds &= 0xDF;
		cs -= ds;
		if (cs)
			break;
	} while (ds);
	return (cs);
}

FLIST *AddToFList(const char* full_name, const char *name, int is_folder, int is_cur) {

	int l_fname;
	FLIST *fl;
	FLIST *fn = malloc(sizeof(FLIST) + (l_fname = strlen(full_name))
			+ strlen(name) + 2);
	fn->fullname = (char *)fn + sizeof(FLIST);
	fn->name = (char *)fn + sizeof(FLIST) + l_fname + 1;
	strcpy(fn->fullname, full_name);
	strcpy(fn->name, name);
	fn->is_folder = is_folder;
	fn->is_cur = is_cur;
	fn->next = 0;
	fl = (FLIST *)fltop;
	if (fl) {

		FLIST *pr;
		pr = (FLIST *) &fltop;
		while (strcmp_nocase(fl->name, fn->name) < 0) {
			pr = fl;
			fl = fl->next;
			if (!fl)
				break;
		}
		fn->next = fl;
		pr->next = fn;
	} else {
		fltop=fn;
	}
	return (fn);
}

int FindFiles(char *str, int type) {// type == 0 SelectFolder, type == 1 SelectFile

	DIR_ENTRY de;
	unsigned int err;
	char *rev, *s, *d;
	int i, c, n = 0;
	char path[256];
	char name[128];

	strcpy(path, str);
	Free_FLIST();
	s = path;
	d = name;
	rev = 0;
	while ((c = *s++)) {
		*d++ = c;
		if (c == '\\' && *s != '\0')
			rev = d;
	}
	if (rev == 0)
		AddToFList("ROOT", back, IS_BACK, 0);
	else {
		*rev=0;
		AddToFList(name, back, IS_BACK, 0);
	}
	n++;

	i = strlen(path);
	path[i++] = '*';
	path[i] = '\0';
	if (FindFirstFile(&de, path, &err)) {
		do {
			i = strlen(de.folder_name);
			strcpy(path, de.folder_name);
			path[i++] = '\\';
			strcpy(path + i, de.file_name);
			if (de.file_attr & FA_DIRECTORY) {
				i = strlen(path);
				path[i++] = '\\';
				path[i] = 0;
				name[0] = '\\';
				strcpy(name + 1, de.file_name);
				AddToFList(path, name, IS_FOLDER, (!strncmp(path, procfile, strlen(path)))?1:0);
				n++;
			} else {
				if (type != 0) {
					AddToFList(path, de.file_name, IS_FILE, (!strcmp(path, procfile))?1:0);
					n++;
				}
			}
		} while (FindNextFile(&de, &err));
	}
	FindClose(&de, &err);
	return n;
}

FLIST *FindFLISTtByNS(int *i, int si) {
	FLIST *fl;
	fl = (FLIST *)fltop;
	while (fl) {
		if (fl->is_folder == si) {
			if (!(*i))
				return (fl);
			(*i)--;
		}
		fl = fl->next;
	}
	return fl;
}

FLIST *FindFLISTtByN(int n) {

	FLIST *fl;
	fl = FindFLISTtByNS(&n, IS_BACK);
	if ((!n) && (fl))
		return (fl);
	fl = FindFLISTtByNS(&n, IS_FOLDER);
	if ((!n) && (fl))
		return (fl);
	fl = FindFLISTtByNS(&n, IS_FILE);
	if ((!n) && (fl))
		return (fl);
	return fl;
}

int FindFLISTCur(void)
{
  int i=0;
  FLIST *fl=(FLIST *)fltop;
  while(fl)
  {
    if(fl->is_folder==IS_BACK)
    {
      if(fl->is_cur) return i;
      i++;
    }
    fl=fl->next;
  }
  fl=(FLIST *)fltop;
  while(fl)
  {
    if(fl->is_folder==IS_FOLDER)
    {
      if(fl->is_cur) return i;
      i++;
    }
    fl=fl->next;
  }
  fl=(FLIST *)fltop;
  while(fl)
  {
    if(fl->is_folder==IS_FILE)
    {
      if(fl->is_cur) return i;
      i++;
    }
    fl=fl->next;
  }
  return 0;
}

void SavePath(FLIST *fl) {
	if (openFile(fl->fullname)) {
		strcpy(procfile, fl->fullname);
		updateCSMname();
		initBuffer();
		getStartOffset();
		setReadPostion();
		AddPathToHList(procfile);
	}
	else {
		ShowMSG(1, (int)"打开文件失败!");
	}
	/*
	 EDITCONTROL ec;
	 EDIT_ExtractFocusedControl(ed_gui,&ec);
	 WSHDR *ws=AllocWS(ec.maxlen);
	 str_2ws(ws,fl->fullname,ec.maxlen);
	 EDIT_SetTextToFocused(ed_gui,ws);
	 FreeWS(ws);*/
}

int filelist_menu_onkey(void *data, GUI_MSG *msg) {

	FLIST *fl;
	int i, n;
	i = GetCurMenuItem(data);
	fl = FindFLISTtByN(i);

	if (msg->keys == 0x3D || msg->keys == 0x18) {

		if (fl) {
			if (fl->is_folder == IS_FOLDER || fl->is_folder == IS_BACK) {
				//int len;
				if (strcmp(fl->fullname, "ROOT")) {
					//strncpy(header, fl->fullname, sizeof (header) - 1);
					//len = strlen(fl->fullname);
					//header[len> sizeof(header) - 1 ? sizeof (header) - 1 : len] = 0;
					str_2ws((hdr_t=AllocWS(128)), fl->fullname, 127);
					n = FindFiles(fl->fullname, 1);
				} else {
					int CreateRootMenu();
					n = CreateRootMenu();
				}
				Menu_SetItemCountDyn(data, n);
				SetCursorToMenuItem(data, FindFLISTCur());
				RefreshGUI();
			} else {
				SavePath(fl);
				return 1;
			}
		}
		//    GeneralFunc_F1(1);
		return -1;
	}
	return 0;
}

void filelist_menu_ghook(void *data, int cmd) {
	if (cmd == 3) {
		Free_FLIST();
		if(hdr_t)
		{
			FreeWS(hdr_t);
			hdr_t=0;
		}
	}
	if (cmd == 0x0A) {
		if(hdr_t)
		{
			SetHeaderText(GetHeaderPointer(data), hdr_t, malloc_adr(), mfree_adr());
			hdr_t=0;
		}
		//SetCursorToMenuItem(data, FindFLISTCur());
		DisableIDLETMR();
	}
}

void filelist_menu_iconhndl(void *data, int curitem, void *user_pointer) {

	FLIST *fl;
	WSHDR *ws;
	void *item = AllocMenuItem(data);
	int len;
	fl = FindFLISTtByN(curitem);
	if (fl) {
		len = strlen(fl->name);
		ws = AllocMenuWS(data, len + 4);
		if (fl->is_folder == IS_BACK || fl->is_folder == IS_FOLDER) {
			//if(!strncmp(fl->fullname, procfile, strlen(fl->fullname)))
			//  SetCursorToMenuItem(data, curitem);
			str_2ws(ws, fl->name, len);
			wsInsertChar(ws, 0x0002, 1);
			wsInsertChar(ws, 0xE008, 1);
		} else {
			//if(!strcmp(fl->fullname, procfile))
			//  SetCursorToMenuItem(data, curitem);
			str_2ws(ws, fl->name, len);
		}
	} else {
		ws = AllocMenuWS(data, 10);
		wsprintf(ws, "?");
	}
	SetMenuItemText(data, item, ws, curitem);
}

HEADER_DESC filelist_HDR = { 0, 0, 0, 0, NULL, LGP_NULL, LGP_NULL };

MENU_DESC filelist_STRUCT = {

8, filelist_menu_onkey, filelist_menu_ghook, NULL, menusoftkeys, &menu_skt,
		0x10, filelist_menu_iconhndl, NULL, //Items
		NULL, //Procs
		0 //n
		};

int CreateRootMenu(void) {
	char path[32];
	unsigned int err;
	int n = 0;
	Free_FLIST();
	for (int i = 0; i != 5; i++) {
		path[0] = i+'0';
		path[1] = ':';
		path[2] = '\\';
		path[3] = 0;
		if (isdir(path, &err)) {
			AddToFList(path, path, IS_FOLDER, (!strncmp(path, procfile, strlen(path)))?1:0);
			n++;
		}
	}
	//strcpy(header, "Root");
	str_2ws((hdr_t=AllocWS(128)), "Root", 127);
	return (n);
}

void open_select_file_gui(int type) {
	char *s, *rev=0;
	int n, c/*, len*/;
	char folder[128];
	strcpy(folder, procfile);
	s = folder;
	while ((c = *s++)) {
		if (c == '\\' && *s != '\0')
			rev = s;
	}
	if (!rev)
		n = CreateRootMenu();
	else {
		*rev = 0;
		//strncpy(header, procfile, sizeof (header) - 1);
		//len = strlen(procfile);
		//header[len> sizeof (header) - 1 ? sizeof (header) - 1 : len] = 0;
		str_2ws((hdr_t=AllocWS(128)), folder, 127);
		n = FindFiles(folder, type);
	}
	patch_header(&filelist_HDR);
	CreateMenu(0, 0, &filelist_STRUCT, &filelist_HDR, FindFLISTCur(), n, 0, 0);
}
