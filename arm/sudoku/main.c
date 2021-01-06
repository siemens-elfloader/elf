//(C)opy(R)ights - ��������� ��� ������� ����������� �������� (���) ;)
#define ELF_NAME     "SuDoKu"
#define ELF_VERSION  "2.0"
#define ELF_AUTHOR   "Dimadze"
#define ELF_RESPECT  "SIEMENS"

#ifdef SGOLD
#define ELF_PLATFORM "SGold"
#endif

#ifdef NEWSGOLD
#ifndef ELKA
#define ELF_PLATFORM "NewSGold"
#endif
#endif
    
#ifdef ELKA
#define ELF_PLATFORM "NewSGold (E/EL71)"
#endif

//General game #defines  - �������� ������� ������� (���-�� ���������)

#define SCRH 160 //ScreenH() //������ �������� ����
#define SCRW 128 //ScreenW() //������ �������� ����

#define SCRHM 130 //���������� ������ ������
#define SCRWM 128 //���������� ������ ������

#define TIMER_SECOND 262
#define MAXXC        9
#define MAXYC        9
#define MAXPREVIEW   200   //200 �������������
#define MAXSECOND    18000 //5 ����� �� ����
 

//General game/system #includes - �������� �������/��������� ���������

#include "..\inc\swilib.h"
#include "..\inc\rect_patcher.h"
#include "conf_loader.h"

#include "engine\fileop\resources.h" //�������: �����, ������ � ����

//Global consts and vars - ���������� ��������� � ����������
GBSTMR timer;
int GBSTIMER_KOEFFICENT = 1;
int RENDERWINDOW = 0;
int MESSAGEWINDOW =0;
char TYPEREDRAW = 0;
char TEMPREDRAW = 0;

int pravda = 0;

char sudoku[256], bgg[256], bgm[256]; //���� png - ��������: sudoku.png, bgg.png, bgm.png
char dig[28][256];                    //���� png - ��������: 0.png, 1-9.png, 1s-9s.png, 1a-9a.png

char ssffile[5][256];          //���� 5 ssf - ������                      (/cfg/sudoku_%02d.ssf)
char hlpfile[256];             //���� hlp - �����                         (/cfg/sudoku.hlp)
char seditor[256];             //���� ���� - ��������� ������ ���� SuDoKu (/smfeditor.elf)
char cfgfile[256];             //���� BCFG - �����

char elffolder[256];           //���� ����� ����������� �����
char imgfolder[256];           //���� ����� /SCRWxSCRH/ - �������
char cfgfolder[256];           //���� ����� /cfg/ - ��������� ���������, �����
char smffolder[256];           //���� ����� /smf/ - ����� ���� SuDoKu

IMGHDR  logo_img = {90, 90, 0x88, logo_bitmap};                                     //������� (���� � ����)
IMGHDR *sudoku_img     = 0;                                                         //��������� � ���� (�� C72, SL65 �� �� �����)
IMGHDR *bgg_img        = 0;                                                         //��� �������� ����
IMGHDR *bgm_img        = 0;                                                         //��� ����
IMGHDR *dig_img[28]    = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //�������� �����


//BCFG - ����������
int bcfg_mmenu_font         = 7;              // ����� ��������� ����
char bcfg_mmenu_col[4]      = {0,0,255,100};  // ���� ��������� ����
char bcfg_mmenu_bgcol_u[4]  = {0,0,0,100};    // ���� ��������� �������� ����
char bcfg_mmenu_bgcol_m[4]  = {255,0,0,100};  // ���� ��������� ����������� �������� ����

int bcfg_sh_headfont         = 7;
char bcfg_sh_headcolt[4]     = {0,0,0,100};
char bcfg_sh_headcolg[4]     = {0,0,0,100};

int bcfg_sh_softfont         = 7;
char bcfg_sh_softcolt[4]     = {255,0,0,100};
char bcfg_sh_softcolg[4]     = {0,0,0,100};


//Additional game/system #includes - ������������� �������/��������� ���������

#include "engine\system\lang.h"      //���� ���������� - ���������� ����������� #define'�� (�� �������� Ivoplay)
#include "engine\system\sieelf.h"    //��������� ������ ��� IAR
#include "engine\system\addfunc.h"   //���������� �������������� �-��
#include "engine\system\sudoku.h"    //���������� ������� �-��, ��������, ��������, ���������� ��� ���� SuDoKu, �� ���� ��� ���� ;)

#include "engine\fileop\ext_work.h"  //���������� �-�� ��� ������ � ������� ���� SuDoKu 
#include "engine\fileop\ssf_work.h"  //���������� �-�� ��� ������ � ssf - �������  [!]
#include "engine\fileop\elffolder.h" //���������� �-�� ��� ������ � ������� �� ������� ����� elf - ����������


SUDOKUMAP *sdm = 0;
ERRORSTRUCT *errs = 0;

#include "engine\render\logow.c"     //��������� ���� ����
#include "engine\render\mmenu.c"     //��������� �������� ����

//General programs functions - �������� ������� ����/���������


void START_CONTROL(char *exename, char *fname) // ���������� �-�� ��� ������ ����������, exename - ���� ����������� �����, fname - �������� ��� �������, ��������, ���� ������-���� �����
{
  //if (SECRETFUNCTION(exename)==1) {ShowMSG(1,(int)"AAAAA!");SUBPROC((void *)ElfKiller); }
 
  
 sdm = CreateSUDOKUMAPbyEXTFILE(fname);
 
 ElfFolderOperations(exename);
 errs = ElfFolderCheckFiles(sdm, fname);
 InitConfig(); 
}


void END_CONTROL() // ���������� �-�� ��� ���������� ����������
{
  MemFreeOfIMGHDR(bgm_canvas_mmenu);
  MemFreeOfIMGHDR(bgm_canvas_mrsoft);
  MEMORYFREE(counter); 
  GBS_DelTimer(&timer);
  
}

void MINIMIZE_CONTROL() // ���������� �-�� ��� "������������" ����������
{
  
 GBS_StopTimer(&timer);
  
}

void MAXIMIZE_CONTROL() // ���������� �-�� ��� "��������������" ����������
{ 
 FULLREDRAW();
}

void CREATE_CONTROL() // ���������� �-�� ��� �������� ���� ����������
{
 GBS_StartTimerProc(&timer,TIMER_SECOND/GBSTIMER_KOEFFICENT,REDRAW_CONTROL);
 FULLREDRAW();
}

void MESSAGES_CONTROL() // ���������� �-�� ��� ������� ���������
{

}

void REDRAW_CONTROL() // ���������� �-�� ���������� ������, REDRAW() - ��� ������ ���� �-��
{
if (MESSAGEWINDOW == 0)
{
  if (RENDERWINDOW  == 0) LOGOW_RENDER();
  if (RENDERWINDOW  == 1) MMENU_RENDER();
} 

}


int KEY_CONTROL(GUI_MSG *msg) // ���������� �-�� ��� ������� ������, KEYMSG - ��� �������, KEYSMSG - ��� �������, END - ���������� ���������, NEXT - �������� ���������� ������� �������
{ 
int MT=0;
 if (KEYMSG == KEY_DOWN || KEYMSG == LONG_PRESS)
  {
    if (MESSAGEWINDOW == 1)
     {
       if (KEYSMSG > 0 && RENDERWINDOW == -1) END;
       if (KEYSMSG > 0 && RENDERWINDOW != -1) {MESSAGEWINDOW = 0;MT=1; GKEYEND;}
     }
    else
    {
      if (RENDERWINDOW == 1)
       {
         if (KEYSMSG == '0') if (pravda == 0) pravda = 1; else pravda = 0;
         if (KEYSMSG == UP_BUTTON    || KEYSMSG == '2') {if (mmenu_cur==0) mmenu_cur=(MMENU_CT - 1); else mmenu_cur--; GKEYEND;}
         if (KEYSMSG == DOWN_BUTTON  || KEYSMSG == '8') {if (mmenu_cur==(MMENU_CT - 1)) mmenu_cur=0; else mmenu_cur++; GKEYEND;}
         if (KEYSMSG == ENTER_BUTTON || KEYSMSG == '5')
         {
           if (mmenu_cur == 0) {RENDERWINDOW = 2;    GKEYEND;}
           if (mmenu_cur == 1) {RENDERWINDOW = 3;    GKEYEND;}
           if (mmenu_cur == 2) {OpenFile(cfgfile,0); GKEYEND;}
           if (mmenu_cur == 3) {ShowMessage(LG_MMENU_ERROR, 7, MSGINFO); GKEYEND;}
           if (mmenu_cur == 4) {ShowMessage(LG_MMENU_ERROR, 7, MSGINFO); GKEYEND;}
           if (mmenu_cur == 5) {RENDERWINDOW = 5;    GKEYEND;}
           if (mmenu_cur == 6) END;  
         }
       }
         
    }
    
    
      
  }
 
 
KEYEND:

if (TEMPREDRAW != RENDERWINDOW || MT == 1) FULLREDRAW(); else SMARTREDRAW();
TEMPREDRAW = RENDERWINDOW; 
 
 NEXT; 
}
