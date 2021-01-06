#include "..\inc\swilib.h"
//#include "..\inc\mplayer.h"

const int minus11=-11; // стремная константа
unsigned short maincsm_name_body[140];
int filePassed=0; // передано ли имя файла
int ViewerCalled = 0; //редактор вызван
volatile int Terminate = 0; // флаг необходимости завершения работы

unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

WSHDR *ws_eddata;     // хранилище списка файлов
char *filename;     // глобальная переменная для имени файла
unsigned short findex=0;
unsigned int errcode=0;
short f_LoadFromPIT = 0;

char Is_GPN=0;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;


DrwImg(IMGHDR *img, int x, int y, int *pen, int *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}


typedef struct
{
  char signature[16];
  unsigned short picnum;
  unsigned short unk1;
  char w;
  char h;
  char Compr_Bits;
}PICHDR;

// Глобальные переменные, используемые для отображения именно текущей пикчи
PICHDR Cur_Pichdr;
void *Pic_Buffer;
int CurPic_Ofs=0;

void Disp_Picture(short LoadFromPIT);

int GetNextOffsetInGPN(int CurOfs, char Direction)
/*
  CurOfs - смещение ТЕКУЩЕГО GPF в GPN!
  На CurOfs накладывается условие - кратность 16
  Direction = 1, если поиск вперёд; 0, если назад
*/
{
  int bkp_Ofs=CurOfs;
  
  if(!Is_GPN)
  {
    return CurOfs;
  }
  
  char buf[17];
  buf[16]=0x0;
  char Sig[]="GraphicPatchFile";
  if(CurOfs % 16 !=0)
  {
    ShowMSG(1,(int)"ОШИБКА! Offset не кратно 16");
    return -1;    
  }
  // Сбиваем оффсет, чтобы первым же шагом не найти наш же текущий файл
  if(Direction==1)
  {
    CurOfs=CurOfs+16;
  }
  else
  {
    CurOfs=CurOfs-16;
    if(CurOfs<0)
    {
      return bkp_Ofs;
    }
  }
  unsigned int hF=fopen(filename, A_ReadOnly+A_BIN, P_READ + P_WRITE, &errcode);
  lseek(hF, CurOfs, S_SET, &errcode, &errcode);
  unsigned int NewOfs = CurOfs;
  unsigned int Counter=0;
  int temp;
  while(!errcode)
  {
    fread(hF, &buf, 16, &errcode);
    if(strcmp(buf,Sig)==0)
    {
      //ShowMSG(1,(int)"Найдено новое Offset");
      NewOfs = lseek(hF, 0, S_CUR, &errcode, &errcode)-16;
      break;
    }
    if(Direction==0)
    {
      temp=lseek(hF, 0, S_CUR, &errcode, &errcode);
      temp=temp-0x20;
      if(temp<0)
      {
        fclose(hF, &errcode);
        return bkp_Ofs+16;
      }
      lseek(hF, temp, S_SET, &errcode, &errcode);
    }
    Counter++;
    if(Counter>256)
    {
      //ShowMSG(1,(int)"Offset НЕ НАЙДЕНО");
      fclose(hF, &errcode);
      return bkp_Ofs;
    }
  }
  //sprintf(Sig, "Off=%d",NewOfs);
  //ShowMSG(2, (int)Sig);
  fclose(hF, &errcode);
  return NewOfs;
}

int Read_Picture(int PicOffset)
{
  if(!filePassed)
  {
    WSHDR *ws=AllocWS(17);
    wsprintf(ws,"Не передано имя!");
    DrawString(ws,12,60,131,75,5,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));  
    FreeWS(ws);
    return -1;
  }
  unsigned int hF=fopen(filename, A_ReadOnly+A_BIN, P_READ + P_WRITE, &errcode);
  if(errcode)
  {
    ShowMSG(1,(int)"ОШИБКА! Файл не открыт");
    return -1;
  }
  lseek(hF,PicOffset,S_SET, &errcode, &errcode);
  fread(hF, &Cur_Pichdr, sizeof(PICHDR),&errcode);
  if(!errcode)
  {   
      void UpdateCSMname();
      UpdateCSMname();
      //int f_size = lseek(hF, 0, S_END, &errcode, &errcode);
      int f_size = GetNextOffsetInGPN(PicOffset,1) - PicOffset;      
      if(f_size==0) // Достижимо, если мы на последней картинке
      {
        f_size = lseek(hF, 0, S_END, &errcode, &errcode) - PicOffset;
      }
      if(Pic_Buffer!=NULL)
      {
        mfree(Pic_Buffer);
      }
      Pic_Buffer = malloc((f_size-0x20+3)&(~3));
      if(Pic_Buffer==NULL)
      {
        ShowMSG(2,(int)"ОШИБКА! Память не выделена");
        fclose(hF, &errcode);
        return -1;
      }
      lseek(hF, PicOffset+0x20, S_SET, &errcode, &errcode);
      fread(hF,Pic_Buffer,((f_size-0x20+3)&(~3)),&errcode);
      fclose(hF,&errcode);
  }
  else
  {
    ShowMSG(1,(int)"ОШИБКА! Сбой при чтении");
    return -1;
  }
return 1;
}


void KillFileList();

void FreeResource()
{
  if(filename!=NULL)
  {
    mfree(filename);
  }
  FreeWS(ws_eddata);
  if(Pic_Buffer!=NULL)
  {
    mfree(Pic_Buffer);
  }
  KillFileList();
}

void OnRedraw(MAIN_GUI *data) // OnRedraw
{
  DrawRoundedFrame(0,0,131,175,0,0,0,
			GetPaletteAdrByColorIndex(0),
			GetPaletteAdrByColorIndex(20));
  if(!ViewerCalled)
  {
    ViewerCalled = 1;
    if(Read_Picture(0x0))
    {
      Disp_Picture(0);
    }
  }
  else
  {
    Disp_Picture(f_LoadFromPIT);
  }

}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  data->ws1=AllocWS(256);
  data->ws2=AllocWS(256);
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
  FreeResource();
  FreeWS(data->ws1);
  FreeWS(data->ws2);
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
  data->gui.state=2;
  if(Terminate)
  {
    GeneralFuncF1(1); // рубим верхний гуй. И приложение закрывается.
  }
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

typedef struct
{
  int fnumber;
  char *fname;
  void *next;
  void *prev;
}PFileList;

PFileList *FileListRoot;
unsigned short FileCount;
PFileList *CurrentFile;


// Получает в глобальные переменные указатель на струкуру с текущим файлом
void SetCurrentFile()
{
  if(Terminate){return;}
  PFileList *CurEx = FileListRoot;
  if(CurEx==NULL)
  {return;}
  CurrentFile = FileListRoot;
  do
  {
    if(strcmp(CurEx->fname, filename)==0)
      {
        CurrentFile = CurEx;
      }
    CurEx = CurEx->next;
  }while(CurEx->fnumber!=1);  
}

char * GetFileDir(char *fname)
{
  char *xz = fname;
//  sprintf(xz,"0:\\Misc\\patches\\gpf\\ELF.gpf");
  
//  char *q = malloc(128);
  // Сначала ищем первый справа слеш
  int len = strlen(xz);

  int i;
  char sym;
  for(i=0;i<len;i++)
  {
    sym = xz[len-i-1];
    if(sym=='\\')
    {
      break;
    }
  }
//  q[len+1]=0x00;
// sprintf(q,"%d",len-i);
  len = len-i;
  char *res = malloc(len+1);
  for(i=0;i<len;i++)
  {
    res[i]=xz[i];
  }
  res[len]=0x00;
//  ShowMSG(1,(int)res);
  return res;
}

void AddFile(int fnum, char *fname)
{
  PFileList *CurEx = malloc(sizeof(PFileList));
  CurEx->fname = fname;
//  ShowMSG(1,(int)fname);
  CurEx->fnumber = fnum;
  CurEx->next=0;
  CurEx->prev = 0;
  LockSched();
  if(!FileListRoot)
  {
    FileListRoot = CurEx;
    CurEx->prev=FileListRoot;
    CurEx->next=FileListRoot;
  }
  else
  {
    PFileList *temp = FileListRoot->next; // Второй элемент
    FileListRoot->next = CurEx;           // Вставили вместо второго
    
    CurEx->prev = FileListRoot;           // Для добавленного FileListRoot - предыдущий
    CurEx->next = temp;                   // А бывший второй - следующий
    temp->prev = CurEx;                   // Коррекция ссылки на предыдущий у бывшего второго
  }
  UnlockSched();
}

// Заполняет список файлов текущей директории
void FillFileList()
{
  DIR_ENTRY de;
  unsigned int err;
  int i=1;
  char name[256];
  char *newname;
  char *path = GetFileDir(filename); // Получим путь
  strcpy(name,path);
  strcat(name,"*.gp?");
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      strcpy(name,path);
      strcat(name,de.file_name);
      newname = malloc(128);
      strcpy(newname,name);
      AddFile(i, newname);
      i++;
    }
    while(FindNextFile(&de,&err));

  }
  CurrentFile = FileListRoot;
  FileCount = i -1;
//  newname=malloc(10);
//  sprintf(newname, "Cnt=%d",FileCount);
//  ShowMSG(1,(int)newname);
//  mfree(newname);
  FindClose(&de,&err);
}

// Уничтожение списка файлов НАХ - пока не пашет!!!
void KillFileList()
{
//  ShowMSG(1,(int)"Очистка произведена!");

  if(FileListRoot==NULL)
  {
    return;
  }
 LockSched();
 
while(FileListRoot!=NULL)
{
 if(FileListRoot==FileListRoot->next)
 {
//   ShowMSG(1,(int)"FileListRoot destroy");
   mfree(FileListRoot->fname);
   mfree(FileListRoot);
   FileCount--;
   CurrentFile = NULL;
   FileListRoot=NULL;
UnlockSched();   
   return;
 }
 PFileList *CurEx = FileListRoot->next; // Второй элемент
 ((PFileList*)(CurEx->next))->prev = FileListRoot; //Предыдущий у третьего - на первый
 FileListRoot->next = ((PFileList*)(CurEx->next)); // Следующий у первого - на третий
 mfree(CurEx->fname);
 mfree(CurEx);
 FileCount--;
} 

UnlockSched();
/*
  LockSched();
  PFileList *CurEx = FileListRoot->next;
  while(CurEx)
  {
    PFileList *p = CurEx;
    mfree(CurEx->fname);
    CurEx = CurEx->next;
    if(p==CurEx)
    {
      break;
    }
    mfree(p);
  }
  mfree(CurEx);
  UnlockSched();
*/
}


void ShowFiles()
{
  if(FileListRoot==NULL)
  {
    ShowMSG(1,(int)"Список пуст");
    return;
  }
  WSHDR *ws = AllocWS(256);
  PFileList *CurEx = FileListRoot;
  char *info = malloc(100);
  int i=1;
  do
  {
    sprintf(info,"%X - %X", CurEx->prev, CurEx->next);
    str_2ws(ws, /*CurEx->fname*/info, 128);
      DrawString(ws,1,1+i*15,131,(i+1)*15,5,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23)); 
      if(strcmp(CurEx->fname, filename)==0)
      {
        //ShowMSG(1,(int)"Us");
      }
    CurEx = CurEx->next;
    i++;
  }while(CurEx->fnumber!=1);
  mfree(info);
  FreeWS(ws);
}


// +1 = следующий файл
// -1 = предыдущий файл
void GetFNameByDir(char *buffer, short dir)
{
  if(FileListRoot==NULL){FillFileList();}
  SetCurrentFile();
  if(CurrentFile==NULL)
  {
    return;
  }
  if(dir==1){CurrentFile = CurrentFile->next;}
  else{CurrentFile = CurrentFile->prev;}
  strcpy(buffer, CurrentFile->fname);
  return;
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
DirectRedrawGUI();
  //  wsprintf(data->ws2,"MSG:%08X %08X",msg->gbsmsg->msg,msg->gbsmsg->submess);
//  DrawString(data->ws2,5,45,131,55,11,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

  if (msg->gbsmsg->msg==KEY_UP)
  {
    switch(msg->gbsmsg->submess)
    {
case '0': {ShowFiles();break;} 
}
}

  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT:
      {
        Terminate=1;
        return(1); //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
      }
/*    
    case '2': {MPlayer_VolChange(1); break;}
    case '8': {MPlayer_VolChange(-1); break;}
    case '7': {MPlayer_Shutdown(); break;}
    case '9': {MPlayer_Mute(); break;}
*/    
    case '1': {KillFileList();char *q=malloc(10);sprintf(q,"q=%d",FileCount);ShowMSG(1,(int)q);mfree(q);break;}
   
     
    case DOWN_BUTTON:
    case '8':
      {
        //ShowFiles();
        GetFNameByDir(filename,+1);
        //ShowMSG(1,(int)filename);
        if(Read_Picture(0))
        {
          Disp_Picture(f_LoadFromPIT);
        }
        break;
      }

    case UP_BUTTON:
    case '2':
      {
        GetFNameByDir(filename,-1);
        if(Read_Picture(0))
        {
          Disp_Picture(f_LoadFromPIT);
        }
        break;
      }
      
    case '5':
      {
        if(!f_LoadFromPIT)
        {
          f_LoadFromPIT = 1;
        }
        else
        {
          f_LoadFromPIT = 0;
        }
        Disp_Picture(f_LoadFromPIT);
        break;
      }
    
    case LEFT_SOFT:
      {
	void DispMenu(void);
	DispMenu();
        break;
      }
    
    case RIGHT_BUTTON:
    case '6':
      {
        CurPic_Ofs=GetNextOffsetInGPN(CurPic_Ofs,1);
        if(Read_Picture(CurPic_Ofs))
        {
          Disp_Picture(f_LoadFromPIT);
        }
        break;
      }  

    case LEFT_BUTTON:
    case '4':
      {
        CurPic_Ofs=GetNextOffsetInGPN(CurPic_Ofs,0);
        if(Read_Picture(CurPic_Ofs))
        {
          Disp_Picture(f_LoadFromPIT);
        }        
        break;
      }
    }
  }
  //  method0(data);
  return(0);
}

void Killer(void)
{
  extern void *ELF_BEGIN;
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  mfree_adr(data);
}

int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)OnRedraw,	//Redraw
  (void *)onCreate,	//Create
  (void *)onClose,	//Close
  (void *)onFocus,	//Focus
  (void *)onUnfocus,	//Unfocus
  (void *)OnKey,	//OnKey
  0,
  (void *)onDestroy,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,131,175};

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  MAINGUI_ID=csm->gui_id;
}


void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  return(1);
}

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
  0,
  0,
  0,
  0,
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

void Disp_Picture(short LoadFromPIT)
{
      int wpos;
      int hpos;
      int width;
      int height;
      char *sh_fname;
      if(LoadFromPIT)
      {
        width = GetImgWidth(Cur_Pichdr.picnum);
        height = GetImgHeight(Cur_Pichdr.picnum);
//        width = Cur_Pichdr.w;//GetImgWidth(Cur_Pichdr.picnum);
//        height = Cur_Pichdr.h;//GetImgHeight(Cur_Pichdr.picnum);

      }
      else
      {
        width = Cur_Pichdr.w;
        height = Cur_Pichdr.h;
      }
      
      wpos = (ScreenW() - width)/2;
      hpos = (ScreenH() - height)/2;

      if(!LoadFromPIT)
      {
        IMGHDR image;
        image.w = width;
        image.h = height;
        image.bpnum = Cur_Pichdr.Compr_Bits;
        image.bitmap = Pic_Buffer;        
        DrwImg(&image, wpos,hpos,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(0));
        sh_fname = strrchr(filename,'\\');
      }
      else
      {
        DrawImg(wpos, hpos, Cur_Pichdr.picnum);
        sh_fname = malloc(10);
        sprintf(sh_fname, "PIT");
      }
      WSHDR *ws=AllocWS(25);
      wsprintf(ws,"#%d (0x%02X): %dx%d",Cur_Pichdr.picnum,Cur_Pichdr.picnum,width,height);
      DrawString(ws,1,1,131,10,11,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));   
      WSHDR *fname=AllocWS(50);
      str_2ws(fname,sh_fname,40);
      if(LoadFromPIT)
      {
        mfree(sh_fname);
      }
      DrawString(fname,1,160,131,176,5,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));  
      FreeWS(fname);
      FreeWS(ws);
}


void UpdateCSMname(void)
{
  WSHDR *ws=AllocWS(256);
  char *sh_fname = strrchr(filename,'\\');
  str_2ws(ws,sh_fname,128);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"GPView: %w",ws);
  FreeWS(ws);
}

int main(char *exename, char *fname)
{
  char dummy[sizeof(MAIN_CSM)];
  filename = malloc(128);
  if (fname)
  {
    if (strlen(fname)<128)
    {
      strcpy(filename,fname);     // сохраняем в глоб.перем.переданное имя
      filePassed = 1;
      if(strstr(filename,".gpn"))
      {
        Is_GPN=0x01;
      }
    }
  }
  ws_eddata=AllocWS(256);
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  return 0;
}

void menup2(void)  // Покинуть редактор (вызов из меню)
{
  Terminate =1 ;
  GeneralFuncF1(1);
}

void AboutDlg(void)
{
  char *str = "GP*-вьювер v0.9RC3 (0xC605)\r\n(c) 2006 Kibab\r\nInspired by RainMaker\r\n(r)Rst/CBSIE";
  ShowMSG(2,(int)str); 
}

int icon[]={0x3DB,0};
int about_icon[]={0x4DB,0};
int exit_icon[] = {0x315,0};

HEADER_DESC menuhdr={0,0,131,21,icon,(int)"Меню вьювера",0x7FFFFFFF};
int menusoftkeys[]={0,1,2};
MENUITEM_DESC menuitems[2]=
{
  {exit_icon,(int)"Выход",0x7FFFFFFF,0,NULL/*menusoftkeys*/,0,0x59D},
  {about_icon,(int)"Об эльфе...",0x7FFFFFFF,0,NULL/*menusoftkeys*/,0,0x59D},
};

void *menuprocs[2]={(void *)menup2, (void *) AboutDlg};

SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Выбор"},
  {0x0001,0x0000,(int)"Назад"},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

MENU_DESC tmenu=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_skt,
  1,
  NULL,
  menuitems,
  menuprocs,
  2
};

void DispMenu(void)
{
  CreateMenu(0,0,&tmenu,&menuhdr,0,2,0,0);
}

