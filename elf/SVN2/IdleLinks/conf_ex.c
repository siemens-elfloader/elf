#include "..\inc\swilib.h"
#include "IdleLinks.h"
#include "conf_loader.h"
#include "idle.h"
#include "editor.h"
#ifdef LOG
  #include "utils.h"
#endif

#ifdef LOG
char module[] = "conf_ex";
#endif

char *BcfgsPath = "X:\\Zbin\\etc\\IdleLinks"; // Путь к bcfg файлам
char *percent_ss = "%s\\%s";
char *percent_ss_bcfg = "%s\\%s.bcfg";

TLabelData *TLabels  = NULL; // Ярлычки :)
int Labels = 0; // Количество ярлычков

int *S_ICONS;

void FreeBcfgs()
{
  //
  // Освобождает память, занятую под список
  //
  LockSched();
  TLabelData* all = TLabels;
  TLabels = NULL;
  while (all)
  {
    TLabelData *tmp;
    if (all->Pic) mfree(all->Pic);
    if (all->FileName) mfree(all->FileName);
    if (all->LinkName) mfree(all->LinkName);
    tmp = all;
    all = (TLabelData*)(all->next);
    mfree(tmp);
    tmp = NULL;
  }
  UnlockSched(); 
  Labels = 0;
  if(S_ICONS)
  {
    mfree(S_ICONS);
  }
}

char *header = "X:\\Zbin\\img\\IL.png";
extern const char *successed_config_filename;
  
void LoadBcfgs()
{
  //
  // Загружает данные из конфигов в список
  //
 
  S_ICONS = malloc(sizeof(int));
  header[0]= successed_config_filename[0];
  S_ICONS[0] = (int)header;
  Labels = 0;
  char *filename;
  BcfgsPath[0] = successed_config_filename[0];
  unsigned int err;
#ifdef LOG
  log(module, "bcfgs path is", BcfgsPath);
#endif
  if (isdir(BcfgsPath, &err) == 1)  // Если папка существует
  {
    // Готовим маску для поиска наших bcfg
    char *filter;
    filter = malloc(strlen(BcfgsPath) + 8);
    sprintf(filter, "%s\\*.*", BcfgsPath);
    DIR_ENTRY dE;
    // Ищем
#ifdef LOG
  log(module, "search bcfgs in", filter);
#endif
    if (FindFirstFile(&dE,filter,&err))
    {
      do
      {
        // Читаем конфиг
        filename = malloc(strlen(dE.folder_name) + strlen(dE.file_name) + 2);
        sprintf(filename, "%s\\%s", dE.folder_name, dE.file_name);
        InitLink(filename);
        mfree(filename);
        // Создаем новый элемент списка
        TLabelData *NewLabel = malloc(sizeof(TLabelData));
        // Сбрасываем значения из конфига в структуру
        extern const unsigned int link_x;
        NewLabel->x = link_x;
        extern const unsigned int link_y;        
        NewLabel->y = link_y;
        extern const int b_enabled;
        NewLabel->Enabled = b_enabled;
        extern const int link_type;
        NewLabel->Type = link_type;
        extern const char link_pic[128];
        NewLabel->Pic = malloc(strlen((const char*)link_pic) + 1);
        sprintf(NewLabel->Pic, (const char*)link_pic);
        S_ICONS = realloc(S_ICONS, (Labels + 2)*sizeof(int));
        int i;
        i = CalcPic((char*)NewLabel->Pic);
        S_ICONS[Labels+1]=i;
        NewLabel->PicNumder = Labels+1;
        extern const char link_file[128];
        NewLabel->FileName = malloc(strlen((const char*)link_file) + 1);
        sprintf(NewLabel->FileName, (const char*)link_file);
        NewLabel->LinkName = malloc(strlen((const char*)dE.file_name) + 1);
        sprintf(NewLabel->LinkName, (const char*)dE.file_name);
#ifdef LOG
        log(module, "   ---   ---   ", "");
        log(module, "add bcfg to list", NewLabel->LinkName);
        log(module, "new bcfg filename: ", NewLabel->FileName);  
        log(module, "new bcfg picname:", NewLabel->Pic); 
        char* temp1 = malloc(5);
        sprintf(temp1, "%d", NewLabel->PicNumder);
        log(module, "new bcfg picnumber", temp1); 
        mfree(temp1);
        log(module, "   ---   ---   ", "");
#endif
        NewLabel->next = NULL;
        // Добавляем новый элемент к списку        
        TLabelData *TLabelRoot = TLabels;
        if(TLabelRoot)
          while(TLabelRoot->next) TLabelRoot = TLabelRoot->next;
        if(TLabelRoot)
        {
          TLabelRoot->next = NewLabel;
        }
        else
        {
          TLabels = NewLabel;
        }
        Labels++;
#ifdef LOG
        char* temp = malloc(5);
        sprintf(temp, "%d", Labels);
        log(module, "bcfg count is", temp);
        mfree(temp);
#endif
      }while(FindNextFile(&dE,&err));
      FindClose(&dE,&err);
      mfree(filter);
    }
  }
}


void OpenBcfg(char *filename)
{
  //
  // Открывает любой файл в BcfgEditor'e
  //
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

void OpenBcfgFromMenu(char *linkname)
{
  char *temp;
  temp = malloc(strlen(BcfgsPath) + strlen(linkname) + 6);
  sprintf(temp, percent_ss, BcfgsPath, linkname);
  OpenBcfg(temp);
  mfree(temp);
}

void CreateNewBcfg(char *linkname)
{
  //
  // Создает bcfg для нового ярлычка
  //
  InitConfig();
  char *fname;
  fname = malloc(strlen(BcfgsPath) + strlen(linkname) + 7);
  sprintf(fname, percent_ss_bcfg, BcfgsPath, linkname);
  extern const char *successed_config_filename; 
  fname[0] = successed_config_filename[0];
  InitLink(fname);
  OpenBcfg(fname);
  mfree(fname);
  FreeBcfgs();
  LoadBcfgs(); 
  EDITOR_MenuRecount();
}

void RenameBcfg(char *first, char *last)
{
  char *ffirst;
  ffirst = malloc(strlen(BcfgsPath) + strlen(first) + 7);
  sprintf(ffirst, percent_ss_bcfg, BcfgsPath, first);
  char *flast;
  flast = malloc(strlen(BcfgsPath) + strlen(last) + 7);
  sprintf(flast, percent_ss_bcfg, BcfgsPath, last);  
  unsigned int *err=0;
  fmove(ffirst, flast, err);
  mfree(ffirst);
  mfree(flast);
  FreeBcfgs();
  LoadBcfgs(); 
  EDITOR_MenuRecount();
}

char *deleted_path;

void remove(int res)
{
  if(!res)
  {
    unsigned int *err = 0;
    unlink(deleted_path, err);
    mfree(deleted_path);
    FreeBcfgs();
    LoadBcfgs(); 
    EDITOR_MenuRecount();     
    GBS_SendMessage(MMI_CEPID, MSG_RECONFIGURE_REQ,0,deleted_path);
  }
}

void DeleteBcfg(char* linkpath)
{
  deleted_path = malloc(strlen(BcfgsPath) + strlen(linkpath));
  sprintf(deleted_path, percent_ss, BcfgsPath, linkpath);
  MsgBoxYesNo(1, (int)"Do you want to delete?", remove);
}


int CreatePathToBcfgs()
{
  //
  // Создает папку IdleLinks внутри папки ?:\Zbin\etc
  //
  int found = 0;
  unsigned int err;
  if(isdir("4:\\Zbin\\etc", &err))
  {
    found = 1;
    // Если нашли Zbin\etc на диске 4 проверяем наличие там IdleLinks
    if(!isdir("4:\\Zbin\\etc\\IdleLinks", &err))
    {
      // Если не создаем - создаем
      mkdir("4:\\Zbin\\etc\\IdleLinks", &err);
      found = 1;
    }
  }
  else
  {
    // Иначе ищем Zbin\etc на диске 0
    if(isdir("0:\\Zbin\\etc", &err))
    {
      found = 1;
      // Если нашли - ищем IdleLinks
      if(!isdir("0:\\Zbin\\etc\\IdleLinks", &err))
      {
        // Если не нашли - создаем
        mkdir("0:\\Zbin\\etc\\IdleLinks", &err);        
        found =1;
      }
    }
  }
  return found;
}

