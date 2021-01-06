#include "..\inc\swilib.h"
#include "..\inc\xtask_ipc.h"
#include "swaper.h"
#include "gui.h"
#include "main.h"
#include "conf_loader.h"
#include "reboot_loader.h"
int a=0;

#ifdef ELKA
#else
#ifdef NEWSGOLD
int font=11;
#else
int font=7;
#endif
#endif

int book_show;
int time_not=1;
GBSTMR start_tmr;
extern const char ctasks[4];
extern const char cdaemons[4];
extern const char cinfo[4];
extern const int cleseri;
extern const int use_idle;
extern const int use_green;
int lock_other;
extern const char path_file[128];
IMGHDR *reboot1, *shutdown1, *task_img, *ram_img, *clock_img, *batt_img, *background_img, *tasks_img, *bookmarks_img, *cursor_img, *selection_img;
char soft_list_path[128];
char bokmark_list_path[128];
char icon_list_path[128];
extern const int horizontality;
#ifdef ELKA
char icon_list_ms[128];
char icon_list_xtask[128];
extern const char ctasksi[4];
#else
IMGHDR *shutdown_logo, *shutdown2;
#endif

static DrwImage(int x, int y, IMGHDR *img, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

extern const int use_trans;

void init_paths()
{
 
  char z[128];
  sprintf(z, "%sturnoff\\shutdown1.png", path_file);
  shutdown1=CreateIMGHDRFromPngFile(z, 2); 
#ifdef ELKA
#else
  sprintf(z, "%sturnoff\\shutdown_logo.png", path_file);
  shutdown_logo=CreateIMGHDRFromPngFile(z, 2); 
  sprintf(z, "%sturnoff\\shutdown2.png", path_file);
  shutdown2=CreateIMGHDRFromPngFile(z, 2); 
#endif
  sprintf(z, "%sturnoff\\reboot1.png", path_file);
  reboot1=CreateIMGHDRFromPngFile(z, 2); 
  sprintf(z, "%sother\\taski.png", path_file);
  task_img=CreateIMGHDRFromPngFile(z, 2); 
  sprintf(z, "%sother\\rami.png", path_file);
  ram_img=CreateIMGHDRFromPngFile(z, 2); 
  sprintf(z, "%sother\\clocki.png", path_file);
  clock_img=CreateIMGHDRFromPngFile(z, 2); 
  sprintf(z, "%sother\\batti.png", path_file);
  batt_img=CreateIMGHDRFromPngFile(z, 2); 
  sprintf(z, "%sbackground.png", path_file);
  if(use_trans)
  background_img=CreateIMGHDRFromPngFile(z, 0); 
  else
    background_img=CreateIMGHDRFromPngFile(z, 2); 
  sprintf(z, "%stasks.png", path_file);
  tasks_img=CreateIMGHDRFromPngFile(z, 2); 
  sprintf(z, "%sbookmarks.png", path_file);
  bookmarks_img=CreateIMGHDRFromPngFile(z, 2);
  sprintf(z, "%scursor.png", path_file);
  if(use_trans)
  cursor_img=CreateIMGHDRFromPngFile(z, 0);
  else
    cursor_img=CreateIMGHDRFromPngFile(z, 2);
  sprintf(z, "%sselection.png", path_file);
  selection_img=CreateIMGHDRFromPngFile(z, 2);
#ifdef ELKA
  sprintf(icon_list_ms, "%sicons_m\\", path_file);
  sprintf(icon_list_xtask, "%sicons_x\\", path_file);
#endif
  sprintf(icon_list_path, "%sicon_list.txt", path_file);
  sprintf(bokmark_list_path, "%sbookmark_list.txt", path_file);
  sprintf(soft_list_path, "%ssoft_list.txt", path_file);
}

//=================================bookmarks
char BM1NAME[32];
char BM1FILE[128];
char BM2NAME[32];
char BM2FILE[128];
char BM3NAME[32];
char BM3FILE[128];
char BM4NAME[32];
char BM4FILE[128];
char BM5NAME[32];
char BM5FILE[128];
char BM6NAME[32];
char BM6FILE[128];
char BM7NAME[32];
char BM7FILE[128];
char BM8NAME[32];
char BM8FILE[128];
char BM9NAME[32];
char BM9FILE[128];
char BM0NAME[32];
char BM0FILE[128];
#ifdef ELKA
char BM11NAME[32];
char BM11FILE[128];
char BM12NAME[32];
char BM12FILE[128];
char BM13NAME[32];
char BM13FILE[128];
char BM14NAME[32];
char BM14FILE[128];
char BM15NAME[32];
char BM15FILE[128];
char BM16NAME[32];
char BM16FILE[128];
char BM17NAME[32];
char BM17FILE[128];
char BM18NAME[32];
char BM18FILE[128];
char BM19NAME[32];
char BM19FILE[128];
char BM20NAME[32];
char BM20FILE[128];
char BM21NAME[32];
char BM21FILE[128];
char BM22NAME[32];
char BM22FILE[128];
char BM23NAME[32];
char BM23FILE[128];
char BM24NAME[32];
char BM24FILE[128];
char BM25NAME[32];
char BM25FILE[128];
char BM26NAME[32];
char BM26FILE[128];
char BM27NAME[32];
char BM27FILE[128];
char BM28NAME[32];
char BM28FILE[128];
char BM29NAME[32];
char BM29FILE[128];
char BM30NAME[32];
char BM30FILE[128];
#endif

void Start_bookmark(int casa)
{
  switch(casa)
  {
  case 1:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM1FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 2:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM2FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 3:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM3FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 4:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM4FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 5:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM5FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 6:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM6FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 7:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM7FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 8:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM8FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 9:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM9FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 10:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM0FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
#ifdef ELKA
  case 11:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM11FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 12:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM12FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 13:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM13FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 14:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM14FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 15:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM15FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 16:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM16FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 17:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM17FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 18:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM18FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 19:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM19FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 20:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM20FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
    case 21:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM21FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 22:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM22FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 23:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM23FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 24:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM24FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 25:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM25FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 26:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM26FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 27:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM27FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 28:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM28FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 29:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM29FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
  case 30:
    {
    WSHDR *elfname=AllocWS(256);
    wsprintf(elfname, BM30FILE);
    ExecuteFile(elfname,NULL,NULL);
    FreeWS(elfname);
    }
    break;
#endif
  }
}
//=================================bookmarks


IMGHDR screen2={0,0,8,""};

IMGHDR screen3={0,0,8,""};
int tasks;
char icon_text[32768];
int task_list=1;

void DoScreen2()
{
    int ScrH=ScreenH();
    int ScrW=ScreenW();
    char *ms=RamScreenBuffer();
    screen2.w=ScrW;
    screen2.h=ScrH;
    screen2.bitmap=malloc(ScrW*ScrH*2);
    memcpy(screen2.bitmap, ms, ScrW*ScrH*2);
}

void DoScreen3()
{
    int ScrH=40;
    int ScrW=40;
    char *ms=RamScreenBuffer();
    screen3.w=ScrW;
    screen3.h=ScrH;
    screen3.bitmap=malloc(ScrW*ScrH*2);
    memcpy(screen3.bitmap, ms, ScrW*ScrH*2);
}

const int minus11=-11; // стремная константа =)
unsigned short maincsm_name_body[140];
extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

unsigned int MAINCSM_ID = 0;

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

extern NAMELIST * volatile nltop;
int pos=1;
int total_pos=1;
int total_d;
int move_skip;
void redrit(void);
int sm;
int forward;
int halt;
int shutd;
int logout;

#include "strings2.h"

WSHDR *data4;
WSHDR *data5;
int draw_rec;
int this_rec;

//=====================reboot========================
void SaveRebootList(WSHDR *ramed)
{
  char buffer[128];
  convWS_to_ANSI(ramed, buffer);
  volatile int hFile;
  unsigned int io_error = 0;
  sprintf(buffer,"%s|", buffer);
  hFile = fopen("0:\\system\\data.bin",A_ReadWrite + A_Create + A_Append + A_BIN,P_READ+P_WRITE, &io_error);
  if(hFile!=-1)
  {
    fwrite(hFile, buffer, strlen(buffer), &io_error);
    fclose(hFile, &io_error);
  }
}
//=====================reboot========================

extern const char rebc[4];

void DrawProgress(WSHDR *dat, int casi)
{
#ifdef ELKA
  if (casi)
  {
    this_rec++;
    wsprintf(data4,"%t", "Закрытие...");
    DrawScrollString(data4,37,154,160,154+GetFontYSIZE(9),1,9,TEXT_ALIGNLEFT,ctasks,GetPaletteAdrByColorIndex(23));
    wsprintf(data4,"[OK]");
    DrawString(data4,204-Get_WS_width(data4,9),174,207,174+GetFontYSIZE(9)+1,9,0,ctasks,GetPaletteAdrByColorIndex(23));
    DrawScrollString(dat,37,174,160,174+GetFontYSIZE(9),1,9,0,ctasks,GetPaletteAdrByColorIndex(23)); 
  }
  else
  {
    if(shutd) wsprintf(data4,"%t","Выключение......");
    else wsprintf(data4,"%t","Перезагрузка......");
    DrawString(data4,37,174,200,174+GetFontYSIZE(9)+1,9,0,ctasks,GetPaletteAdrByColorIndex(23));
  }
  DrawRectangle(35,202,(202 * this_rec)/draw_rec,223,0,GetPaletteAdrByColorIndex(23),rebc);
#else
  if (casi)
  {
    this_rec++;
    wsprintf(data4, "Закрытие...");
    DrawScrollString(data4,17,97,100,97+GetFontYSIZE(font),1,font,TEXT_ALIGNLEFT,ctasks,GetPaletteAdrByColorIndex(23));
    wsprintf(data4,"[OK]");
    DrawString(data4,115-Get_WS_width(data4,font),109,115+3,109+GetFontYSIZE(font)+1,font,0,ctasks,GetPaletteAdrByColorIndex(23));
    DrawScrollString(dat,17,109,87,109+GetFontYSIZE(font),1,font,TEXT_ALIGNLEFT,ctasks,GetPaletteAdrByColorIndex(23)); 
  }
  else
  {
    if(shutd) wsprintf(data4,"Выключение......");
    else wsprintf(data4,"Restarting......");
    DrawString(data4,17,109,115,109+GetFontYSIZE(font)+1,font,0,ctasks,GetPaletteAdrByColorIndex(23));
  }
  DrawRectangle(18,125,(115 * this_rec)/draw_rec,135,0,GetPaletteAdrByColorIndex(23),rebc);
#endif
}
const char perc[]="%d";
int zin;
int init_rec=1;

void task_list3()
{
  DrwImage(0, 0,&screen2, NULL, NULL);
#ifdef ELKA
  DrwImage(30, 50,background_img,0,0);  //12,37
  DrwImage(155,65,tasks_img,0,0);
  DrwImage(180,65,bookmarks_img,0,0);
#else
  DrwImage(12, 26,background_img,0,0);  //12,37
  DrwImage(83,40,tasks_img,0,0);
  DrwImage(101,40,bookmarks_img,0,0);
#endif
  total_d=GetNumberOfDialogs()-2;
  if(init_rec) {draw_rec=total_d; init_rec=0;}
  NAMELIST *nl=nltop;
  if(total_d>0)
  {
    if(a!=1){
    NAMELIST *p=nl;
    nl=p->next;
    zin=((CSM_RAM *)(nl->p))->id;
    if (zin==CSM_root()->idle_id) 
    {
      NAMELIST *p=nl;
      nl=p->next; 
      zin=((CSM_RAM *)(nl->p))->id;
    }
    if(shutd==0) SaveRebootList(nl->name);
    DrawProgress(nl->name, 1);
    CloseCSM(zin);
    }
    GBS_StartTimerProc(&start_tmr, 100, task_list3);
  }
  else
  {
    DrawProgress(NULL, 0);
    if (shutd==1) SwitchPhoneOff();
    else RebootPhone();
  }
}
void close()
{
   DrwImage(0, 0,&screen2, NULL, NULL);
   DrwImage(30, 50,background_img,0,0);
   DrwImage(35,74+(pos*20),cursor_img,0,0);
   GBS_StartTimerProc(&start_tmr, 100, close);
}

int main_poX;
int main_poY;
int naticq_icon;

void check_name(char *a)
{
  if(strstr(a, "Config:")>0) strcpy(a, "CfgEditor");
  if(strstr(a, "NATICQ")>0) {if(naticq_icon) strcpy(a, "NATICQ2"); else strcpy(a, "NATICQ");}
  if(strstr(a, "SieJC")>0) strcpy(a, "SieJC");
  if(strstr(a, "MC")>0) strcpy(a, "MC:");
  if(strstr(a, "mc")>0) strcpy(a, "MC:");
  if(strstr(a, "BM:")>0) strcpy(a, "BM:");
}

int use_unknown;

void SearchIcon(WSHDR *ramed, int w, int show, int main_icon, int mainx, int mainy)
{
  char buffer[256];
  convWS_to_ANSI(ramed, buffer);
  check_name(buffer);
  if(main_icon) if(strstr(buffer, "IDLE")>0) strcpy(buffer, "navaico");
  char p2[]="||";
  char *s,*s1,*s2;
  int len;
Sundo:
  if((s1=strstr(icon_text,buffer))>0)
  {
    s1+=strlen(buffer);
    if((s2=strstr(s1,p2))>0)
    {
      len=s2-s1-1;
      s=malloc(len+1);
      strncpy(s,s1+1,len);
      s[len]='\0';
      if(main_icon)
      {
#ifdef ELKA
        
        char *buffer_icon=malloc(256);
        sprintf(buffer_icon, "%s%s.png", icon_list_ms, s);
        void *canvasdata = BuildCanvas();
        DrawCanvas(canvasdata,mainx,mainy,mainx+GetImgWidth((int)buffer_icon),mainy+20,1);
        DrawImg(mainx,mainy,(int)buffer_icon);
        if(horizontality) main_poX=main_poX+GetImgWidth((int)buffer_icon);
        else main_poY=main_poY+GetImgWidth((int)buffer_icon);
        mfree(buffer_icon);
#else
        void *canvasdata = BuildCanvas();
        DrawCanvas(canvasdata,mainx,mainy,mainx+26,mainy+13,1);
        DrawImg(mainx,mainy,(int)s);
        if(horizontality) main_poX=main_poX+13;
        else main_poY=main_poY+13;
#endif
      }
      else
      {
#ifdef ELKA
      char *buffer_icon=malloc(256);
      sprintf(buffer_icon, "%s%s.png", icon_list_xtask, s);
      if(show) DrawImg(37,w+2,(int)buffer_icon);
      DrawImg(181,w+2,(int)buffer_icon);
      mfree(buffer_icon);
#else
      if(show) DrawImg(17,w+1,(int)s);
      DrawImg(102,w+1,(int)s);
#endif  
      }
      mfree(s);
    }
  }
  else
  {
    if((strstr(buffer, "navaico")==0)&&(!main_icon))
    {
      if((!main_icon)&&(use_unknown)) {strcpy(buffer, "UNKNOWN"); goto Sundo;}
    }
  }
}

extern const unsigned int IDLETASKS;
extern const unsigned int IDLET_X;
extern const unsigned int IDLET_Y;

void DrawMainTasks()
{
  total_d=GetNumberOfDialogs()-1;
  NAMELIST *nl=nltop;
  main_poX=IDLET_X;
  main_poY=IDLET_Y;
  while(nl)
  {
    NAMELIST *p=nl;
    if(nl->is_daemon) { } else SearchIcon(nl->name, main_poX, 0, 1, main_poX, main_poY);
    nl=p->next;
  }
}

int refresh;
extern const char Side1[4];
extern const char Side2[4];

void DrawSideProgresbar(int count, int position) //30,50 //172,42 // 172,148  ==  //12,26 //103,33 //103,94
{
  if(count>1)
  {
#ifdef ELKA
    DrawRectangle(202,92,204,198,0,Side1,Side1);
    int height1=106/count;
    DrawRectangle(202,92+(height1*(position-1)),204,92+(height1*(position)),0,Side2,Side2);
#else
    DrawRectangle(115,59,116,120,0,Side1,Side1);
    int height1=60/count;
    DrawRectangle(115,59+(height1*(position-1)),116,59+(height1*(position)),0,Side2,Side2);
#endif
  }
}

int test2;

void DrawCPU() //182, 3 //186, 182
{
#ifdef ELKA
  test2 = GetFreeRamAvail();
  test2=test2/1024;
  DrawRectangle(212, 232-((179*test2)/8000), 216, 232, 0, cinfo, cinfo);
#endif
}

void OnRedraw(MAIN_GUI *data)
{ 
  refresh=216;
  if(task_list==1)
  {
  total_d=GetNumberOfDialogs()-1;
//#ifdef NEWSGOLD
  DrwImage(0, 0,&screen2, NULL, NULL);
//#endif
#ifdef ELKA
  DrwImage(30, 50,background_img,0,0);  //12,37
  if(tasks!=0) DrwImage(35,74+(pos*20),cursor_img,0,0);
  DrwImage(153,63,selection_img,0,0);
  DrwImage(155,65,tasks_img,0,0);
  DrwImage(180,65,bookmarks_img,0,0);
#else
  DrwImage(12, 26,background_img,0,0);  //12,37
  if(tasks!=0) DrwImage(16,48+(pos*12),cursor_img,0,0);
  DrwImage(82,39,selection_img,0,0);
  DrwImage(83,40,tasks_img,0,0);
  DrwImage(101,40,bookmarks_img,0,0);
#endif
  int show=1;
  NAMELIST *nl=nltop;
#ifdef ELKA
  int i=94;
#else
  int i=60;
#endif
  WSHDR *ws=AllocWS(64);
  int skip=move_skip+1;
  if(total_d==0)
  {
#ifdef ELKA
    wsprintf(ws, "No Tasks");
    DrawString(ws,120-(Get_WS_width(ws,9)/2),134,120+(Get_WS_width(ws,9)/2)+3,134+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23)); 
#else
    wsprintf(ws, "No Tasks");
    DrawString(ws,66-(Get_WS_width(ws,font)/2),84,66+(Get_WS_width(ws,font)/2)+3,84+GetFontYSIZE(font)+2,font,0,ctasks,GetPaletteAdrByColorIndex(23));        
#endif
  }
  else
  while((nl)&&(show<=5))
  {
    NAMELIST *p=nl;
    if(!skip) 
    {
#ifdef ELKA
      if(Get_WS_width(nl->name,9)<140)
        {
          if(pos!=show)
          {
          if(nl->is_daemon) DrawString(nl->name,37,i+1,178,i+GetFontYSIZE(8),8,0,cdaemons,GetPaletteAdrByColorIndex(23));
          else
        DrawString(nl->name,37,i+1,178,i+GetFontYSIZE(8),8,0,ctasks,GetPaletteAdrByColorIndex(23));
          }
          else
            {
          if(nl->is_daemon) DrawString(nl->name,37,i+1,178,i+GetFontYSIZE(9),9,0,cdaemons,GetPaletteAdrByColorIndex(23));
          else
        DrawString(nl->name,37,i+1,178,i+GetFontYSIZE(9),9,0,ctasksi,GetPaletteAdrByColorIndex(23));
          }
        }
        else
        {
          if(pos!=show)
          {
            if(nl->is_daemon) DrawScrollString(nl->name,37,i+1,178,i+GetFontYSIZE(8),1,8,TEXT_ALIGNLEFT,cdaemons,GetPaletteAdrByColorIndex(23)); else
          DrawScrollString(nl->name,37,i+1,178,i+GetFontYSIZE(8),1,8,TEXT_ALIGNLEFT,ctasks,GetPaletteAdrByColorIndex(23));
          }
          else
          {
            if(nl->is_daemon) DrawScrollString(nl->name,37,i+1,178,i+GetFontYSIZE(9),sm+1,9,TEXT_ALIGNLEFT,cdaemons,GetPaletteAdrByColorIndex(23)); else
            DrawScrollString(nl->name,37,i+1,178,i+GetFontYSIZE(9),sm+1,9,TEXT_ALIGNLEFT,ctasksi,GetPaletteAdrByColorIndex(23));
            refresh=10;
            if(forward==1) sm=sm+2;
            if(forward==0) sm=sm-2;
            if(forward==2)
            {
              if(halt) halt--;
              else forward=3;
            }
            if ((sm>Get_WS_width(nl->name,9)-140)&&(forward==1)) {forward=2; halt=5;}
            if (forward==3) {
              if (sm==0) {forward=4; halt=5;}
              else sm=sm-2;
            }
            if(forward==4)
            {
              if(halt) halt--;
              else forward=1;
            }
          }
        }
        SearchIcon(nl->name, i, 0, NULL, NULL, NULL);
      show++;
      i=i+20;
#else
        if(Get_WS_width(nl->name,font)<85)
        {
          if(nl->is_daemon) DrawString(nl->name,17,i+1,115,i+GetFontYSIZE(font),font,0,cdaemons,GetPaletteAdrByColorIndex(23));
          else
        DrawString(nl->name,17,i+1,115,i+GetFontYSIZE(font),font,0,ctasks,GetPaletteAdrByColorIndex(23));
        }
        else
        {
          if(pos!=show)
          {
            if(nl->is_daemon) DrawScrollString(nl->name,17,i+1,100,i+GetFontYSIZE(font),1,font,TEXT_ALIGNLEFT,cdaemons,GetPaletteAdrByColorIndex(23)); else
          DrawScrollString(nl->name,17,i+1,100,i+GetFontYSIZE(font),1,font,TEXT_ALIGNLEFT,ctasks,GetPaletteAdrByColorIndex(23));
          }
          else
          {
            if(nl->is_daemon) DrawScrollString(nl->name,17,i+1,100,i+GetFontYSIZE(font),sm+1,font,TEXT_ALIGNLEFT,cdaemons,GetPaletteAdrByColorIndex(23)); else
            DrawScrollString(nl->name,17,i+1,100,i+GetFontYSIZE(font),sm+1,font,TEXT_ALIGNLEFT,ctasks,GetPaletteAdrByColorIndex(23));
            refresh=10;
            if(forward==1) sm=sm+2;
            if(forward==0) sm=sm-2;
            if(forward==2)
            {
              if(halt) halt--;
              else forward=3;
            }
            if ((sm>Get_WS_width(nl->name,font)-85)&&(forward==1)) {forward=2; halt=5;}
            if (forward==3) {
              if (sm==0) {forward=4; halt=5;}
              else sm=sm-2;
            }
            if(forward==4)
            {
              if(halt) halt--;
              else forward=1;
            }
          }
        }
        SearchIcon(nl->name, i, 0, NULL, NULL, NULL);
      show++;
      i=i+12;
#endif
    }

    else skip--;
    nl=p->next;
  }
  DrawSideProgresbar(total_d, total_pos);
  DrawCPU();
  if(time_not)
  {
#ifdef ELKA
  wsprintf(ws, "%d", tasks);
  DrwImage(37, 203,task_img,0,0);
  DrawString(ws,56,202,56+Get_WS_width(ws,9)+3,202+GetFontYSIZE(9)+1,9,0,cinfo,GetPaletteAdrByColorIndex(23));
  int ram = GetFreeRamAvail();
  ram=ram/1024;
  wsprintf(ws,"%dKb", ram);
  DrawString(ws,204-Get_WS_width(ws,9),202,207,202+GetFontYSIZE(9)+1,9,0,cinfo,GetPaletteAdrByColorIndex(23));
  DrwImage(185-Get_WS_width(ws,9), 203, ram_img,0,0);
#else
  wsprintf(ws, "%d", tasks);
  DrwImage(16, 124, task_img,0,0);
  DrawString(ws,29,124,29+Get_WS_width(ws,font)+3,124+GetFontYSIZE(font)+1,font,0,cinfo,GetPaletteAdrByColorIndex(23));
  int ram = GetFreeRamAvail();
  ram=ram/1024;
  wsprintf(ws,"%dKb", ram);
  DrawString(ws,115-Get_WS_width(ws,font),124,115+3,124+GetFontYSIZE(font)+1,font,0,cinfo,GetPaletteAdrByColorIndex(23));
  DrwImage(115-Get_WS_width(ws,font)-13, 124,ram_img,0,0);
#endif
  }
  else
    {
      int battery = *RamCap();
      wsprintf(ws,"%d%", battery);
#ifdef ELKA
      DrwImage(37, 203,batt_img,0,0);
      DrawString(ws,56,202,56+Get_WS_width(ws,9)+3,202+GetFontYSIZE(9)+1,9,0,cinfo,GetPaletteAdrByColorIndex(23));
#else
      DrwImage(16, 124,batt_img,0,0);
      DrawString(ws,29,124,29+Get_WS_width(ws,font)+3,124+GetFontYSIZE(font)+1,font,0,cinfo,GetPaletteAdrByColorIndex(23));
#endif
      TTime time;
      TDate date;
      GetDateTime(&date, &time);
      wsprintf(ws, "%02d:%02d:%02d", time.hour, time.min, time.sec);
#ifdef ELKA
      DrawString(ws,204-Get_WS_width(ws,9),202,207,202+GetFontYSIZE(9)+1,9,0,cinfo,GetPaletteAdrByColorIndex(23));
      DrwImage(185-Get_WS_width(ws,9), 203, clock_img,0,0);
#else
      DrawString(ws,115-Get_WS_width(ws,font),124,115+3,124+GetFontYSIZE(font)+1,font,0,cinfo,GetPaletteAdrByColorIndex(23));
      DrwImage(102-Get_WS_width(ws,font), 124,clock_img,0,0);
#endif
    }
  FreeWS(ws);
  }
  else
    if(task_list==0)
  {//===============================do the links
    DrwImage(0, 0,&screen2, NULL, NULL);
#ifdef ELKA
    DrwImage(30, 50,background_img,0,0);  //12,37
    DrwImage(35,74+(pos*20),cursor_img,0,0);
    DrwImage(178,63,selection_img,0,0);
    DrwImage(155,65,tasks_img,0,0);
    DrwImage(180,65,bookmarks_img,0,0);
#else
    DrwImage(12, 26,background_img,0,0);  //12,37
    DrwImage(16,48+(pos*12),cursor_img,0,0);
    DrwImage(100,39,selection_img,0,0);
    DrwImage(83,40,tasks_img,0,0);
    DrwImage(101,40,bookmarks_img,0,0);
#endif
    int show=0;
#ifdef ELKA
    int i=94;
#else
    int i=60;
#endif
    int len;
    int skip=move_skip;
    WSHDR *ws=AllocWS(32);
#ifdef ELKA
    if((!skip)&&(book_show>=1)&&(show<5))
    {
        wsprintf(ws, BM1NAME);
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=2)&&(show<5))
    {
        wsprintf(ws, BM2NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=3)&&(show<5))
    {
        wsprintf(ws, BM3NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=4)&&(show<5))
    {
        wsprintf(ws, BM4NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=5)&&(show<5))
    {
        wsprintf(ws, BM5NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=6)&&(show<5))
    {
        wsprintf(ws, BM6NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=7)&&(show<5))
    {
        wsprintf(ws, BM7NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=8)&&(show<5))
    {
        wsprintf(ws, BM8NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=9)&&(show<5))
    {
        wsprintf(ws, BM9NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=10)&&(show<5))
    {
        wsprintf(ws, BM0NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=11)&&(show<5))
    {
        wsprintf(ws, BM11NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=12)&&(show<5))
    {
        wsprintf(ws, BM12NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=13)&&(show<5))
    {
        wsprintf(ws, BM13NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=14)&&(show<5))
    {
        wsprintf(ws, BM14NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=15)&&(show<5))
    {
        wsprintf(ws, BM15NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=16)&&(show<5))
    {
        wsprintf(ws, BM16NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=17)&&(show<5))
    {
        wsprintf(ws, BM17NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=18)&&(show<5))
    {
        wsprintf(ws, BM18NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=19)&&(show<5))
    {
        wsprintf(ws, BM19NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=20)&&(show<5))
    {
        wsprintf(ws, BM20NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=21)&&(show<5))
    {
        wsprintf(ws, BM21NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=22)&&(show<5))
    {
        wsprintf(ws, BM22NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=23)&&(show<5))
    {
        wsprintf(ws, BM23NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=24)&&(show<5))
    {
        wsprintf(ws, BM24NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=25)&&(show<5))
    {
        wsprintf(ws, BM25NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=26)&&(show<5))
    {
        wsprintf(ws, BM26NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=27)&&(show<5))
    {
        wsprintf(ws, BM27NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=28)&&(show<5))
    {
        wsprintf(ws, BM28NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=29)&&(show<5))
    {
        wsprintf(ws, BM29NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
    if((!skip)&&(book_show>=30)&&(show<5))
    {
        wsprintf(ws, BM30NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,9)/2;
        DrawString(ws,120-len,i+1,120+len+3,i+GetFontYSIZE(9)+2,9,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+20;
    }
    else
      skip--;
#else
    if((!skip)&&(book_show>=1)&&(show<5))
    {
        wsprintf(ws, BM1NAME);
      //  DrawString(ws,17,i+1,115,i+GetFontYSIZE(11)+2,11,0,ctasks,GetPaletteAdrByColorIndex(23));
        len=Get_WS_width(ws,font)/2;
        DrawString(ws,66-len,i+1,66+len,i+GetFontYSIZE(font)+2,font,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+12;
    }
    else
      skip--;
    if((!skip)&&(book_show>=2)&&(show<5))
    {
        wsprintf(ws, BM2NAME);
        len=Get_WS_width(ws,font)/2;
        DrawString(ws,66-len,i+1,66+len,i+GetFontYSIZE(font)+2,font,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+12;
    }
    else
      skip--;
    if((!skip)&&(book_show>=3)&&(show<5))
    {
        wsprintf(ws, BM3NAME);
        len=Get_WS_width(ws,font)/2;
        DrawString(ws,66-len,i+1,66+len,i+GetFontYSIZE(font)+2,font,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+12;
    }
    else
      skip--;
    if((!skip)&&(book_show>=4)&&(show<5))
    {
        wsprintf(ws, BM4NAME);
        len=Get_WS_width(ws,font)/2;
        DrawString(ws,66-len,i+1,66+len,i+GetFontYSIZE(font)+2,font,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i ,1, NULL, NULL, NULL);
        show++;
        i=i+12;
    }
    else
      skip--;
    if((!skip)&&(book_show>=5)&&(show<5))
    {
        wsprintf(ws, BM5NAME);
        len=Get_WS_width(ws,font)/2;
        DrawString(ws,66-len,i+1,66+len,i+GetFontYSIZE(font)+2,font,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+12;
    }
    else
      skip--;
    if((!skip)&&(book_show>=6)&&(show<5))
    {
        wsprintf(ws, BM6NAME);
        len=Get_WS_width(ws,font)/2;
        DrawString(ws,66-len,i+1,66+len,i+GetFontYSIZE(font)+2,font,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+12;
    }
    else
      skip--;
    if((!skip)&&(book_show>=7)&&(show<5))
    {
        wsprintf(ws, BM7NAME);
        len=Get_WS_width(ws,font)/2;
        DrawString(ws,66-len,i+1,66+len,i+GetFontYSIZE(font)+2,font,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+12;
    }
    else
      skip--;
    if((!skip)&&(book_show>=8)&&(show<5))
    {
        wsprintf(ws, BM8NAME);
        len=Get_WS_width(ws,font)/2;
        DrawString(ws,66-len,i+1,66+len,i+GetFontYSIZE(font)+2,font,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+12;
    }
    else
      skip--;
    if((!skip)&&(book_show>=9)&&(show<5))
    {
        wsprintf(ws, BM9NAME);
        len=Get_WS_width(ws,font)/2;
        DrawString(ws,66-len,i+1,66+len,i+GetFontYSIZE(font)+2,font,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+12;
    }
    else
      skip--;
    if((!skip)&&(book_show>=10)&&(show<5))
    {
        wsprintf(ws, BM0NAME);
        len=Get_WS_width(ws,font)/2;
        DrawString(ws,66-len,i+1,66+len,i+GetFontYSIZE(font)+2,font,0,ctasks,GetPaletteAdrByColorIndex(23));
        SearchIcon(ws, i, 1, NULL, NULL, NULL);
        show++;
        i=i+12;
    }
    else
      skip--;
#endif
    DrawSideProgresbar(book_show, total_pos);
    DrawCPU();
    if(time_not)
  {
#ifdef ELKA
//    if(!style) wsprintf(ws, "Tasks:%d", tasks);
  wsprintf(ws, "%d", tasks);
  DrwImage(37, 203, task_img,0,0);
  DrawString(ws,56,202,56+Get_WS_width(ws,9)+3,202+GetFontYSIZE(9)+1,9,0,cinfo,GetPaletteAdrByColorIndex(23));
  int ram = GetFreeRamAvail();
  ram=ram/1024;
  wsprintf(ws,"%dKb", ram);
  DrawString(ws,204-Get_WS_width(ws,9),202,207,202+GetFontYSIZE(9)+1,9,0,cinfo,GetPaletteAdrByColorIndex(23));
  DrwImage(185-Get_WS_width(ws,9), 203, ram_img,0,0);
#else
  wsprintf(ws, "%d", tasks);
  DrwImage(16, 124, task_img,0,0);
  DrawString(ws,29,124,29+Get_WS_width(ws,font)+3,124+GetFontYSIZE(font)+1,font,0,cinfo,GetPaletteAdrByColorIndex(23));
  int ram = GetFreeRamAvail();
  ram=ram/1024;
  wsprintf(ws,"%dKb", ram);
  DrawString(ws,115-Get_WS_width(ws,font),124,115+3,124+GetFontYSIZE(font)+1,font,0,cinfo,GetPaletteAdrByColorIndex(23));
  DrwImage(115-Get_WS_width(ws,font)-13, 124,ram_img,0,0);
#endif
  }
  else
    {
      int battery = *RamCap();
      wsprintf(ws,"%d%", battery);
#ifdef ELKA
      DrwImage(37, 203,batt_img,0,0);
      DrawString(ws,56,202,56+Get_WS_width(ws,9)+3,202+GetFontYSIZE(9)+1,9,0,cinfo,GetPaletteAdrByColorIndex(23));
#else
      DrwImage(16, 124,batt_img,0,0);
      DrawString(ws,29,124,29+Get_WS_width(ws,font)+3,124+GetFontYSIZE(font)+1,font,0,cinfo,GetPaletteAdrByColorIndex(23));
#endif
      TTime time;
      TDate date;
      GetDateTime(&date, &time);
      wsprintf(ws, "%02d:%02d:%02d", time.hour, time.min, time.sec);
#ifdef ELKA
      DrawString(ws,204-Get_WS_width(ws,9),202,207,202+GetFontYSIZE(9)+1,9,0,cinfo,GetPaletteAdrByColorIndex(23));
      DrwImage(185-Get_WS_width(ws,9), 203,clock_img,0,0);
#else
      DrawString(ws,115-Get_WS_width(ws,font),124,115+3,124+GetFontYSIZE(font)+1,font,0,cinfo,GetPaletteAdrByColorIndex(23));
      DrwImage(102-Get_WS_width(ws,font), 124,clock_img,0,0);
#endif
//      GBS_StartTimerProc(&start_tmr, 30, redrit); 
    }
  FreeWS(ws);
  }//===============================end do links
  else
    if(task_list==2)
    {
      DrwImage(0, 0,&screen2, NULL, NULL);
#ifdef ELKA
      DrwImage(30, 50,background_img,0,0);  //12,37
      DrwImage(155,65,tasks_img,0,0);
      DrwImage(180,65,bookmarks_img,0,0);
      if(shutd) DrwImage(37,124,shutdown1,0,0);
      else
      DrwImage(37,124,reboot1,0,0);
#else
      DrwImage(12, 26,background_img,0,0);  //12,37
      DrwImage(83,40,tasks_img,0,0);
      DrwImage(101,40,bookmarks_img,0,0);
//      DrwImage(23, 60,shutdown2,0,0);
//      DrwImage(68, 60,shutdown2,0,0);
      WSHDR *ews=AllocWS(64);
      if(shutd) wsprintf(ews, "Shutdown");
      else wsprintf(ews, "Restart");
      DrawString(ews,45,70,47+Get_WS_width(ews,font),70+GetFontYSIZE(font)+1,font,0,ctasks,GetPaletteAdrByColorIndex(23));
      if(shutd) DrwImage(16,91,shutdown1,0,0);
      else
      DrwImage(16,91,reboot1,0,0);
      FreeWS(ews);
#endif
      WSHDR *ws=AllocWS(32);
//      ClockDraw();
      DrawCPU();
      if(time_not)
  {
#ifdef ELKA
//    if(!style) wsprintf(ws, "Tasks:%d", tasks);
  wsprintf(ws, "%d", tasks+1);
  DrwImage(37, 203, task_img,0,0);
  DrawString(ws,56,202,56+Get_WS_width(ws,9)+3,202+GetFontYSIZE(9)+1,9,0,cinfo,GetPaletteAdrByColorIndex(23));
  int ram = GetFreeRamAvail();
  ram=ram/1024;
  wsprintf(ws,"%dKb", ram);
  DrawString(ws,204-Get_WS_width(ws,9),202,207,202+GetFontYSIZE(9)+1,9,0,cinfo,GetPaletteAdrByColorIndex(23));
  DrwImage(185-Get_WS_width(ws,9), 203,ram_img,0,0);
#else
  wsprintf(ws, "%d", tasks+1);
  DrwImage(16, 124,task_img,0,0);
  DrawString(ws,29,124,29+Get_WS_width(ws,font)+3,124+GetFontYSIZE(font)+1,font,0,cinfo,GetPaletteAdrByColorIndex(23));
  int ram = GetFreeRamAvail();
  ram=ram/1024;
  wsprintf(ws,"%dKb", ram);
  DrawString(ws,115-Get_WS_width(ws,font),124,115+3,124+GetFontYSIZE(font)+1,font,0,cinfo,GetPaletteAdrByColorIndex(23));
  DrwImage(115-Get_WS_width(ws,font)-13, 124,ram_img,0,0);
#endif
  }
  else
    {
      int battery = *RamCap();
      wsprintf(ws,"%d%", battery);
#ifdef ELKA
      DrwImage(37, 203,batt_img,0,0);
      DrawString(ws,56,202,56+Get_WS_width(ws,9)+3,202+GetFontYSIZE(9)+1,9,0,cinfo,GetPaletteAdrByColorIndex(23));
#else
      DrwImage(16, 124,batt_img,0,0);
      DrawString(ws,29,124,29+Get_WS_width(ws,font)+3,124+GetFontYSIZE(font)+1,font,0,cinfo,GetPaletteAdrByColorIndex(23));
#endif
      TTime time;
      TDate date;
      GetDateTime(&date, &time);
      wsprintf(ws, "%02d:%02d:%02d", time.hour, time.min, time.sec);
#ifdef ELKA
      DrawString(ws,204-Get_WS_width(ws,9),202,207,202+GetFontYSIZE(9)+1,9,0,cinfo,GetPaletteAdrByColorIndex(23));
      DrwImage(185-Get_WS_width(ws,9), 203, clock_img,0,0);
#else
      DrawString(ws,115-Get_WS_width(ws,font),124,115+3,124+GetFontYSIZE(font)+1,font,0,cinfo,GetPaletteAdrByColorIndex(23));
      DrwImage(102-Get_WS_width(ws,font), 124,clock_img,0,0);
#endif
//      GBS_StartTimerProc(&start_tmr, 30, redrit); 
    }
      FreeWS(ws);
    }
  if(task_list!=3) GBS_StartTimerProc(&start_tmr, refresh, redrit); 
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
//#ifdef NEWSGOLD
  mfree(screen2.bitmap);
//#endif
  #ifdef ELKA
  char* ramIconBar = RamIconBar();
  *ramIconBar = 1;
  #endif
  ClearNL();
  MAINCSM_ID = 0;
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
  data->gui.state=2;
 //  DisableIDLETMR();
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
  
  if (data->gui.state!=2) return;
  data->gui.state=1;
  CloseCSM(MAINCSM_ID);
}

int closing;
int show_daemons;


void redrit()
{
  DirectRedrawGUI();
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  if ((msg->gbsmsg->msg==KEY_DOWN)||((msg->gbsmsg->msg==LONG_PRESS)&&((msg->gbsmsg->submess==UP_BUTTON)||(msg->gbsmsg->submess==DOWN_BUTTON))))
  {
    if(task_list==1)
    {
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_BUTTON:
      pos=1;
      total_pos=1;
      move_skip=0;
      task_list=0;
      DirectRedrawGUI();
      break;
    case DOWN_BUTTON:
      if(total_d!=0)
      {
      total_pos++;
      if(total_pos<=total_d)
      {
      if((total_pos<=3)||(total_pos>total_d-2)) pos++;
      if((total_pos>3)&&(total_pos<=total_d-2)) move_skip++;
      }
      else
        //================addon prokrutka
      {
        pos=1;
        total_pos=1;
        move_skip=0;
      }
//        total_pos--;
      sm=0;
      forward=1;
      DirectRedrawGUI();
      }
      break;
    case UP_BUTTON:
      if(total_d!=0)
      {
      total_pos--;
      if(total_pos)
      {
      if((total_pos<3)||(total_pos>=total_d-2)) pos--;
      if((total_pos>=3)&&(total_pos<total_d-2)) move_skip--;
      }
      else
        //===========addon prokrutka
      {
        total_pos=total_pos+2;
        while(total_pos<=total_d)
      {
      if((total_pos<=3)||(total_pos>total_d-2)) pos++;
      if((total_pos>3)&&(total_pos<=total_d-2)) move_skip++;
      total_pos++;
      }
      total_pos--;
      }
  //      total_pos++;
      sm=0;
      forward=1;
      DirectRedrawGUI();
      }
      break;
    case '*':
      show_daemons=!show_daemons;
      pos=1;
      total_pos=1;
      move_skip=0;
      sm=0;
      forward=1;
      DirectRedrawGUI();
      break;
    case 0x30:
      time_not=!time_not;
      DirectRedrawGUI();
      break;
            case 0x31:
        if(book_show>=1) 
        {
          Start_bookmark(1);
          return(1);
        }
        break;
              case 0x32:
        if(book_show>=2) 
        {
          Start_bookmark(2);
          return(1);
        }
        break;
              case 0x33:
        if(book_show>=3) 
        {
          Start_bookmark(3);
          return(1);
        }
        break;
              case 0x34:
        if(book_show>=4) 
        {
          Start_bookmark(4);
          return(1);
        }
        break;
              case 0x35:
        if(book_show>=5) 
        {
          Start_bookmark(5);
          return(1);
        }
        break;
              case 0x36:
        if(book_show>=6) 
        {
          Start_bookmark(6);
          return(1);
        }
        break;
              case 0x37:
        if(book_show>=7) 
        {
          Start_bookmark(7);
          return(1);
        }
        break;
              case 0x38:
        if(book_show>=8) 
        {
          Start_bookmark(8);
          return(1);
        }
        break;
              case 0x39:
        if(book_show>=9) 
        {
          Start_bookmark(9);
          return(1);
        }
        break;
        case LEFT_BUTTON:
      if(!cleseri) break;
    case '#':
      if(total_d!=0)
      {
       closing=1;
      }
    case ENTER_BUTTON:
      if(total_d!=0)
      {
      minine:
        {
      NAMELIST *nl=nltop;
      int skip_run=total_pos;
      while(nl)
      {
         NAMELIST *p=nl;
         if(skip_run)
         {
           skip_run--;
           nl=p->next;
         }
         else
           goto don;
      }
      don:
      if ((!nl->is_daemon)||((closing)&&(nl->is_daemon)))
      {
        if(closing)
        {
          int i;
          closing=0;
          i=((CSM_RAM *)(nl->p))->id;
          if (i!=CSM_root()->idle_id) 
          {
            CloseCSM(i);
            int rem_pso=total_pos-1;
            pos=1;
            total_pos=1;
            move_skip=0;
            while(rem_pso!=0)
            {
            total_pos++;
            if(total_pos<=total_d-1)
            {
              if((total_pos<=3)||(total_pos>total_d-3)) pos++;
              if((total_pos>3)&&(total_pos<=total_d-3)) move_skip++;
            }
            else
            {
            total_pos--;
            }
            rem_pso--;
            }
            sm=0;
            forward=1;
            GBS_StartTimerProc(&start_tmr, 30, redrit); 
          }
        }
        else
        {
	CSMtoTop(((CSM_RAM *)(nl->p))->id,-1);
        return(1);
        }
      }
      else
        closing=0;
      }
      }
      break;
    case LEFT_SOFT:
      CSMtoTop(CSM_root()->idle_id,-1);
      return(1);
    case RIGHT_SOFT:
      if(total_d!=0)
      {
      total_pos=1;
      goto minine;
      }
      else
      {
        CSMtoTop(CSM_root()->idle_id,-1);
      return(1);
      }
     // break;
      case GREEN_BUTTON:
       if(use_green)
       {
          task_list=2;
          shutd=1;
          DirectRedrawGUI();
       }
        break;
 //     return(1);
    }
    }
    else//=======================================do the links
      if(task_list==0)
    {
      switch(msg->gbsmsg->submess)
      {
      case LEFT_BUTTON:
        pos=1;
        total_pos=1;
        move_skip=0;
        task_list=1;
        sm=0;
        forward=1;
        DirectRedrawGUI();
        break;
      case DOWN_BUTTON:
      total_pos++;
      if(total_pos<=book_show)
      {
      if((total_pos<=3)||(total_pos>book_show-2)) pos++;
      if((total_pos>3)&&(total_pos<=book_show-2)) move_skip++;
      }
      else
        total_pos--;
      DirectRedrawGUI();
      break;
    case UP_BUTTON:
      total_pos--;
      if(total_pos)
      {
      if((total_pos<3)||(total_pos>=book_show-2)) pos--;
      if((total_pos>=3)&&(total_pos<book_show-2)) move_skip--;
      }
      else
        total_pos++;
      DirectRedrawGUI();
      break;
    case 0x30:
      time_not=!time_not;
      DirectRedrawGUI();
      break;
    case LEFT_SOFT:
      CSMtoTop(CSM_root()->idle_id,-1);
      return(1);
    case RIGHT_SOFT:
      total_pos=1;
      goto minine;
      case ENTER_BUTTON:
        Start_bookmark(total_pos);
        return(1);
        case GREEN_BUTTON:
          if(use_green)
       {
          task_list=2;
          shutd=1;
          DirectRedrawGUI();
       }
        break;
      }
    }//==========================================end links
    else
      if(task_list==2)
      {
        switch(msg->gbsmsg->submess)
      {
      case GREEN_BUTTON:
        if(!lock_other)  //===========testing switch
        {
        pos=1;
        total_pos=1;
        move_skip=0;
        task_list=1;
        sm=0;
        forward=1;
        task_list=1;
        DirectRedrawGUI();
        }
        else
          goto enga;
        break;
      case RIGHT_SOFT:
        if(lock_other)
        return(1);
        break;
      case 0x30:
      time_not=!time_not;
      DirectRedrawGUI();
      break;
      case RIGHT_BUTTON:
      case LEFT_BUTTON:
        shutd=!shutd;
        DirectRedrawGUI();
        break;
      case ENTER_BUTTON:
        {
        enga:
        task_list=3;
        data4=AllocWS(128);
        data5=AllocWS(128);
        show_daemons=1;
        task_list3();
        }
        break;
      }
      }
  }
  return(0);
}

extern void kill_data(void *p, void (*func_p)(void *));
void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
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
  (void *)kill_data,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,132,176};

#pragma inline
void patch_rect(const RECT*rcc,int x,int y, int x2, int y2)
{
  RECT *rc=(RECT *)rcc;
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

void maincsm_oncreate(CSM_RAM *data)
{
//#ifdef NEWSGOLD
  DoScreen2();
//#endif
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}


void maincsm_onclose(CSM_RAM *csm)
{
  //SUBPROC((void *)ElfKiller);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
   if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  } 
  if (msg->msg==MSG_INCOMMING_CALL)
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
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
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

void UpdateCSMname(void)
{
  WSHDR *ws=AllocWS(256);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"xtask 3 mod");
  FreeWS(ws);
}
/*
CSM_RAM *GetUnderIdleCSM(void)
{
  CSM_RAM *u;
  CSM_DESC *UnderIdleDesc;
  UnderIdleDesc=(CSM_DESC *)strtoul((char *)"A042B384",0,0x10);
  LockSched();
  u=CSM_root()->csm_q->csm.first;
  while(u && u->constr!=UnderIdleDesc) u=u->next;
  UnlockSched();
  return u;
}*/

extern const char UNDER_IDLE_CONSTR[];
extern const char *successed_config_filename;

CSM_RAM *GetUnderIdleCSM(void)
{
  CSM_RAM *u;
  CSM_DESC *UnderIdleDesc;
  if (strlen((char *)UNDER_IDLE_CONSTR)==8)
  {
    UnderIdleDesc=(CSM_DESC *)strtoul((char *)UNDER_IDLE_CONSTR,0,0x10);
  }
  else
  {
    UnderIdleDesc=((CSM_RAM *)(FindCSMbyID(CSM_root()->idle_id))->prev)->constr;
    sprintf((char *)UNDER_IDLE_CONSTR,"%08X",UnderIdleDesc);
    SaveConfigData(successed_config_filename);
  }
  LockSched();
  u=CSM_root()->csm_q->csm.first;
  while(u && u->constr!=UnderIdleDesc) u=u->next;
  UnlockSched();
  return u;
}

//------------add on---------------------------//
#ifdef NEWSGOLD
 #define USE_ONE_KEY
#endif

#define TMR_SECOND(A) (1300L*A/6)

volatile int SHOW_LOCK;

CSM_DESC icsmd;
int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);


CSM_RAM *under_idle;

extern const int ACTIVE_KEY;
extern const int ACTIVE_KEY_STYLE;
extern const int RED_BUT_MODE;
extern const int ENA_LONG_PRESS;
extern const int ENA_LOCK;

extern const char *successed_config_filename;


int mode;

int mode_red;

int mode_enter;


void ShowMenu(int casi)
{
  if(!IsGuiOnTop(MAINCSM_ID))
  {
    if(casi)
    {
      total_d=GetNumberOfDialogs()-1;
#ifdef EVILFOX
        pos=1;
        total_pos=1;
        move_skip=0;
#else
        if(total_d>=1)
        {
        pos=2;
        total_pos=2;
        move_skip=0;
        }
        else
          {
        pos=1;
        total_pos=1;
        move_skip=0;
        }
#endif
    task_list=1;
//    time_not=1;
    sm=0;
    forward=1;
    logout=0;
    lock_other=0;
    }
    else
    {
      total_d=GetNumberOfDialogs()-1;
      task_list=2;
      shutd=1;
      lock_other=1;
    }
    #ifdef ELKA
  char* ramIconBar = RamIconBar();
  *ramIconBar = 0;
  #endif
    char dummy[sizeof(MAIN_CSM)];
    MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,2);
  }
}

extern const char exept_list[128];

void DoClosery()
{
  total_d=GetNumberOfDialogs()-1;
  NAMELIST *nl=nltop;
  while(nl)
  {
     NAMELIST *p=nl;
     char *ramedy=malloc(128);
     convWS_to_ANSI(nl->name, ramedy);
     check_name(ramedy);
     if((strstr(exept_list, ramedy)==0)&&(!nl->is_daemon))
     {
       int i;
       i=((CSM_RAM *)(nl->p))->id;
       if (i!=CSM_root()->idle_id) 
       {
         CloseCSM(i);
       }
     }
     mfree(ramedy);
     nl=p->next;
  }
  CSMtoTop(CSM_root()->idle_id,-1);
}

int info;

int ShowNaticq()
{
  total_d=GetNumberOfDialogs()-1;
  NAMELIST *nl=nltop;
  while(nl)
  {
     NAMELIST *p=nl;
     char *ramedy=malloc(128);
     convWS_to_ANSI(nl->name, ramedy);
     check_name(ramedy);
     if((strstr("NATICQ2", ramedy)!=0)&&(!nl->is_daemon))
     {
         CSMtoTop(((CSM_RAM *)(nl->p))->id,-1);
         mfree(ramedy);
         return 1;
     }
     mfree(ramedy);
     nl=p->next;
  }
 return 0;
}

void SwitchNext()
{
  total_d=GetNumberOfDialogs()-1;
  NAMELIST *nl=nltop;
  if(nl) {NAMELIST *p=nl; nl=p->next;};
  if(nl) {
    NAMELIST *p=nl;
    int i;
    i=((CSM_RAM *)(nl->p))->id;
    if (i!=CSM_root()->idle_id)
    {   
    CSMtoTop(((CSM_RAM *)(nl->p))->id,-1);
    }
    else
    {
      nl=p->next;
      if(nl)
      {
//        NAMELIST *p=nl;
        CSMtoTop(((CSM_RAM *)(nl->p))->id,-1);
      }
    }
  }
}

extern const int use_natioq;
extern const int LONG_RED_BUT_MODE;


int my_keyhook(int submsg, int msg)
{
#ifdef NEWSGOLD
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if ((submsg==RED_BUTTON)&&(IsIdleUiOnTop()&&(use_idle)&&(IsUnlocked())))
  {
    ShowMenu(0);
//    mode=0;
    return KEYHOOK_BREAK;
  }
  if ((submsg==RED_BUTTON)&&IsIdleUiOnTop()!=1)
  {
    close();
    return KEYHOOK_BREAK;
  }
  if ((submsg==14)&&(IsIdleUiOnTop()&&(use_natioq)&&(use_idle)&&(IsUnlocked())))
  {
    ShowNaticq();
//    mode=0;
   return KEYHOOK_BREAK;
  }
  if ((submsg==RED_BUTTON)&&(RED_BUT_MODE))
  {
    if ((CSM_root()->csm_q->csm.last==icsm)||(IsCalling())) //(IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))
    {
      if (msg==KEY_UP)
      {
	if (mode_red!=2)
	{
	  mode_red=0;
	  return KEYHOOK_BREAK;
	}
      }
      mode_red=2;
    }
    else
    {
      if (msg==KEY_DOWN)
      {
	if (mode_red==1)
	{
	  mode_red=0;
	  return KEYHOOK_NEXT; //Long press, continue with REDB PRESS
	}
      }
      if (msg==KEY_UP)
      {
	if (mode_red)
	{
	  mode_red=0; //Release after longpress
          if(LONG_RED_BUT_MODE==0) {}
          if(LONG_RED_BUT_MODE==1) {if((task_list!=3)&&(task_list!=2)&&(!MAINCSM_ID)) CSMtoTop(CSM_root()->idle_id,-1);}
	  return KEYHOOK_NEXT;
	}
	else
	  //Release after short press
	{
          if (RED_BUT_MODE==1)
          {
#ifdef EVILFOX
            if((task_list!=3)&&(task_list!=2)) GBS_SendMessage(MMI_CEPID,KEY_DOWN,RIGHT_SOFT);
#else
            if((task_list!=3)) GBS_SendMessage(MMI_CEPID,KEY_DOWN,RIGHT_SOFT);
#endif
          }
          else
            if(RED_BUT_MODE==2)
            {
	      if (!MAINCSM_ID)
	      {
	        CSMtoTop(CSM_root()->idle_id,-1);
              }
            }
          else
            if(RED_BUT_MODE==3)
            {
              if (!MAINCSM_ID) DoClosery();
            }
          else
            if(RED_BUT_MODE==4)
            {
              if (!MAINCSM_ID) SwitchNext();
            }
	}
      }
      if (msg==LONG_PRESS)
      {
	mode_red=1;
//        mode_done=1;
        //if((task_list!=3)&&(task_list!=2)) GBS_SendMessage(MMI_CEPID,KEY_DOWN,RED_BUTTON);
//        if((task_list!=3)&&(task_list!=2)) SwitchNext();
      }
      return KEYHOOK_BREAK;
    }
  }
//lul:
#endif
//#ifndef NEWSGOLD
  if (ACTIVE_KEY_STYLE==3)
  {
    if (submsg!=ENTER_BUTTON) return KEYHOOK_NEXT;
/*    if (my_csm_id)
    {
      if (((CSM_RAM *)(CSM_root()->csm_q->csm.last))->id!=my_csm_id)
      {
        CloseCSM(my_csm_id);
      }
      return KEYHOOK_NEXT;
    }*/
    switch(msg)
    {
    case KEY_DOWN:
      if (mode_enter==2)
      { 
	GBS_SendMessage(MMI_CEPID,KEY_UP,ENTER_BUTTON);
	return KEYHOOK_NEXT;
      }
      mode_enter=0;
      return KEYHOOK_BREAK;
    case KEY_UP:
      if (mode_enter==0)
      {
        mode_enter=2;
        if((task_list!=3)&&(task_list!=2)) GBS_SendMessage(MMI_CEPID,KEY_DOWN,ENTER_BUTTON);
        return KEYHOOK_BREAK;
      }
      if (mode_enter==2)
      {
        mode_enter=0;
        return KEYHOOK_NEXT;
      }
      mode_enter=0;
      return KEYHOOK_BREAK;      
    case LONG_PRESS:
      mode_enter=1;
      if ((IsUnlocked()||ENA_LOCK)&&(!MAINCSM_ID)&&(!IsCalling()))
      {
        ShowMenu(1);
            
      }
      mode=0;
      return KEYHOOK_BREAK;
    }
  }
  // * + # implementation
  if ((ACTIVE_KEY_STYLE==2) && !(MAINCSM_ID))
  {
    if (msg==KEY_UP)
    {
      mode=0;
      return KEYHOOK_NEXT;
    }
    if (msg==KEY_DOWN)
    {
      switch (submsg)
      {
      case '*':
        mode=1;
        return (0);
      case '#':
        if (mode==1)
        {
          if ((IsUnlocked()||ENA_LOCK)&&(!IsCalling()))
            ShowMenu(1);
          else mode=0;
        }
        else return KEYHOOK_NEXT;
      }
    }
  }
//#endif
  if (ACTIVE_KEY_STYLE<2)
  {
    if (submsg!=ACTIVE_KEY) return KEYHOOK_NEXT;
    if (MAINCSM_ID)
    {
/*      if (((CSM_RAM *)(CSM_root()->csm_q->csm.last))->id!=my_csm_id)
      {
	CloseCSM(my_csm_id);
      }*/
      if (msg==KEY_UP)
      {
//        total_pos=2;
//        if(total_pos>total_d) total_pos--;
        if((task_list!=3)&&(task_list!=2)) {
#ifdef ELKA
#else
        if(total_d>=2) total_pos=2;
#endif
        GBS_SendMessage(MMI_CEPID,KEY_DOWN,ENTER_BUTTON);
      }
      }
      return KEYHOOK_BREAK;
    }
    switch(msg)
    {
    case KEY_DOWN:
      mode=0;
      if (ACTIVE_KEY_STYLE==0)
	return KEYHOOK_BREAK;
      else 
	return KEYHOOK_NEXT;
    case KEY_UP:
      if (mode==1)
      {
	//Release after longpress
	mode=0;
	if ((ACTIVE_KEY_STYLE==1) || (ENA_LONG_PRESS==3))
	{
	  //Launch on LongPress or Extra on LP - Launch
	  if ((IsUnlocked()||ENA_LOCK)&&(!IsCalling()))
	  {
	    ShowMenu(1);
	  }
	  return KEYHOOK_BREAK;
	}
        if (ENA_LONG_PRESS==1) return KEYHOOK_BREAK;
	if (ENA_LONG_PRESS==2)
	{
          if ((task_list!=2)&&(task_list!=3)) CSMtoTop(CSM_root()->idle_id,-1);
	  return KEYHOOK_BREAK;
	}
        if (ENA_LONG_PRESS==4)
        {
          if ((task_list!=2)&&(task_list!=3)){
          CSMtoTop(CSM_root()->idle_id,-1);
          KbdLock();}
          return KEYHOOK_BREAK;
        }
	break;
      }
      if (ACTIVE_KEY_STYLE==0)
      {
	if ((IsUnlocked()||ENA_LOCK)&&(!IsCalling()))
	{
	  ShowMenu(1);
	}
	return KEYHOOK_BREAK;
      }
      break;
    case LONG_PRESS:
      mode=1;
#ifndef NEWSGOLD
      if (ACTIVE_KEY_STYLE==1)
      {
	if (ENA_LONG_PRESS)
	  return KEYHOOK_NEXT;
	else 
	  return KEYHOOK_BREAK;
      }
#else
      return KEYHOOK_BREAK;
#endif
    }
  }
  return KEYHOOK_NEXT;
}

volatile int callhide_mode=0;

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int reiconize;

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

const char my_ipc_name[]=IPC_XTASK_NAME;

int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{
  int csm_result;
  int icgui_id;
  //  int ocgui_id;
  int idlegui_id;
  
#ifndef NEWSGOLD 
#define EXT_BUTTON 0x63  
  if ((ACTIVE_KEY_STYLE!=2)&&(ACTIVE_KEY_STYLE!=3)) //?? "* + #" ? ?? "Enter Button"
  {//???? ????? ???? ??????? ??????? ??? ???? ???????
    if (ACTIVE_KEY==EXT_BUTTON) //?????? ?????? ????????
    {
      if (msg->msg==439) //?????? ???????
      {
        switch (msg->submess) 
        {
	case 1:
	  if((task_list!=3)&&(task_list!=2)) GBS_SendMessage(MMI_CEPID,LONG_PRESS,EXT_BUTTON);
          break;
	case 2:
	  if((task_list!=3)&&(task_list!=2)) GBS_SendMessage(MMI_CEPID,KEY_UP,EXT_BUTTON);
          break; // ???????? default!!!
        }
      }
      else //??????? ?? ?????????
	goto L1;
    }
    else //?????? ?????? ?? ???????? ?????? ??????? ?????? ????????
      goto L1;
  }
  else
L1:
  csm_result=old_icsm_onMessage(data,msg);
#else    
  csm_result = old_icsm_onMessage(data, msg); //???????? ?????? ?????????? ???????    
#endif
  
  icgui_id=((int *)data)[DISPLACE_OF_INCOMMINGGUI/4];
  idlegui_id=((int *)data)[DISPLACE_OF_IDLEGUI_ID/4];
  //  ocgui_id=((int *)data)[DISPLACE_OF_OUTGOINGGUI/4];
  if (!icgui_id) callhide_mode=0;
  //  if (!ocgui_id) callhide_mode=0;
  
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"XTask config updated!");
      InitConfig();
      init_paths();
    }
  }
#ifdef NEWSGOLD
  if(IsIdleUiOnTop()&&(IDLETASKS))
  {
    if(reiconize)
    {
      DrawMainTasks();
      reiconize--;
    }
  }
  else
    reiconize=5;
#else
//  #define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
//  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  if (IsGuiOnTop(idlegui_id)&&(IDLETASKS))
    {
        if(reiconize)
        {
          DrawMainTasks();
          reiconize--;
        }
    }
  else
    reiconize--;
#endif
  //IPC
  if (msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp(ipc->name_to,my_ipc_name)==0)
      {
	switch (msg->submess)
	{
	case IPC_XTASK_SHOW_CSM:
	  if (MAINCSM_ID) break;
	  if ((!IsCalling())&&(!SHOW_LOCK))
	  {
	    if ((CSM_root()->csm_q->csm.last!=data)||IsGuiOnTop(idlegui_id))
	    {
	      CSMtoTop((int)(ipc->data),-1);
	    }
	  }
	  break;
	case IPC_XTASK_IDLE:
	  if (MAINCSM_ID) break;
	  if ((!IsCalling())/*&&(!SHOW_LOCK)*/)
	    CSMtoTop(CSM_root()->idle_id,-1);
	  break;
	case IPC_XTASK_LOCK_SHOW:
	  SHOW_LOCK++;
	  break;
	case IPC_XTASK_UNLOCK_SHOW:
	  if (SHOW_LOCK) SHOW_LOCK--;
	  break;
        case IPC_XTASK_OFFE:
          ShowMenu(0);
          break;
        case IPC_XTASK_OPEN:
          ShowMenu(1);
          break;
        case IPC_ICON:
          {
          char test[64];
          int len=strlen(ipc->data);
          sprintf(test,"%s",ipc->data);
          test[len]='\0';
          if(test[0]==0x31) naticq_icon=1;
          else naticq_icon=0;
          if(IsIdleUiOnTop()) DrawMainTasks();
          else
          if(IsGuiOnTop(MAINCSM_ID)) DirectRedrawGUI();
          }
          break;
	}
      }
    }
  }
  if (msg->msg==MSG_INCOMMING_CALL)
  {
    callhide_mode=1;
  }
  //  #ifdef NEWSGOLD
  //  if ((msg->msg==MSG_STATE_OF_CALL)&&(msg->submess==0)&&((int)msg->data0==3)) callhide_mode=1;
  //  #else
  //if ((msg->msg==MSG_STATE_OF_CALL)&&(msg->submess==0)&&((int)msg->data0==0)) callhide_mode=1;
  //    ?????!!!! ??????!!!
  //  #endif   
  if (callhide_mode)
  {
    if ((IsGuiOnTop(icgui_id))/*||(IsGuiOnTop(ocgui_id))*/)
    {
      CSMtoTop(CSM_root()->idle_id,((CSM_RAM *)(CSM_root()->csm_q->csm.last))->id);
      callhide_mode=0;
    }
  }
  return csm_result;  
}

void MyIDLECSM_onClose(CSM_RAM *data)
{
  extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  extern void *ELF_BEGIN;
  GBS_DelTimer(&start_tmr);
  RemoveKeybMsgHook((void *)my_keyhook);
  seqkill(data,old_icsm_onClose,&ELF_BEGIN,SEQKILLER_ADR());
}

void load_icon_list()
{
    int fi;
    int fsizei;
    FSTATS stati;
    unsigned int uli;
    GetFileStats(icon_list_path,&stati,&uli);
    if(stati.size>0)
    {
      fi=fopen(icon_list_path,A_ReadOnly+A_BIN,P_READ,&uli);
      fsizei=stati.size;
      char *pi=malloc(fsizei);
      pi[fread(fi,pi,fsizei,&uli)];
      fclose(fi,&uli);
      strcpy(icon_text, pi);
      icon_text[fsizei]='\0';
      mfree(pi);
    }
    if(strstr(icon_text, "UNKNOWN")>0) use_unknown=1; else use_unknown=0;
}
int serti;

void get_bookmark(char *name, char *path, int w, char *search)
{
  int q=0;
  while(search[w]!='|')
  {
    name[q]=search[w];
    q++;
    w++;
  }
  name[q]='\0';
  w++;
  q=0;
  while(search[w]!='|')
  {
    path[q]=search[w];
    q++;
    w++;
  }
  path[q]='\0';
  serti=w+3;
  book_show++;
}

void load_bookmark_list()
{
    int f;
    int fsize;
    FSTATS stat;
    unsigned int ul;
    GetFileStats(bokmark_list_path,&stat,&ul);
    if(stat.size>0)
    {
      f=fopen(bokmark_list_path,A_ReadOnly+A_BIN,P_READ,&ul);
      fsize=stat.size;
      char *p=malloc(fsize);
      p[fread(f,p,fsize,&ul)];
      fclose(f,&ul);
      serti=0;
      if(serti<fsize-2) get_bookmark(BM1NAME, BM1FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM2NAME, BM2FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM3NAME, BM3FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM4NAME, BM4FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM5NAME, BM5FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM6NAME, BM6FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM7NAME, BM7FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM8NAME, BM8FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM9NAME, BM9FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM0NAME, BM0FILE, serti, p);
#ifdef ELKA
      if(serti<fsize-2) get_bookmark(BM11NAME, BM11FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM12NAME, BM12FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM13NAME, BM13FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM14NAME, BM14FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM15NAME, BM15FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM16NAME, BM16FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM17NAME, BM17FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM18NAME, BM18FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM19NAME, BM19FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM20NAME, BM20FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM21NAME, BM21FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM22NAME, BM22FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM23NAME, BM23FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM24NAME, BM24FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM25NAME, BM25FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM26NAME, BM26FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM27NAME, BM27FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM28NAME, BM28FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM29NAME, BM29FILE, serti, p);
      if(serti<fsize-2) get_bookmark(BM30NAME, BM30FILE, serti, p);
#endif
      mfree(p);
    }
}

void DoSplices(void)
{
  init_paths();
  extern const int SHOW_DAEMONS;
  extern int show_daemons;
  show_daemons=SHOW_DAEMONS;
  LockSched();
  if (!AddKeybMsgHook_end((void *)my_keyhook))
  {
    ShowMSG(1,(int)"Cant Start Elf!");
    SUBPROC((void *)ElfKiller);
  }
  else
  {
    {
      CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
      memcpy(&icsmd,icsm->constr,sizeof(icsmd));
      old_icsm_onClose=icsmd.onClose;
      old_icsm_onMessage=icsmd.onMessage;
      icsmd.onClose=MyIDLECSM_onClose;
      icsmd.onMessage=MyIDLECSM_onMessage;
      icsm->constr=&icsmd;
    }
    load_icon_list();
    load_bookmark_list();
    under_idle=GetUnderIdleCSM(); //???? idle_dialog
    int f;
  int sz=0;
  unsigned int ul;
  extern const char csmlist_fname[128];
  extern char csm_text[32768];
  if ((f=fopen(csmlist_fname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
  {
    sz=fread(f,csm_text,32767,&ul);
    fclose(f,&ul);
  }
  if (sz>=0) csm_text[sz]=0;
  
  }
  GBS_StartTimerProc(&start_tmr, 216*5, load_reboot_list);
  UnlockSched();
}
  
void main(void)
{
#ifdef ELKA
  if(ScreenW()<200)
  {
    ShowMSG(1,(int)"wrong display");
  }
#else
  if(ScreenW()>140)
  {
    ShowMSG(1,(int)"wrong display");
  }
#endif
  else
  {
  mode=0;
  if (InitConfig()!=2) GBS_StartTimerProc(&start_tmr,TMR_SECOND(10),DoSplices);
  else DoSplices();
  }
}
