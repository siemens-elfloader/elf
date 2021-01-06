#include "C:\ARM\inc\swilib.h"
#include "language.h"
#include "externs.h"


typedef struct
{
  GUI gui;
  int flag, font;
  WSHDR *msg;
  char *foncolor, *fringcolour;

}SWMSG_GUI;

unsigned int SWMSCSM_ID = 0;
short shcr_w, shcr_h;
int OkBTN=0, CloseBTN=0;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}SWMSG_CSM;

//int x8 ,y8;

extern void kill_data(void *p, void (*func_p)(void *));

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}




int SWMSG_UP=0;

int move_on=0;

#define FLAG_MSG_SIMPLE 0 // 
#define FLAG_MSG_BOX 1 // 
#define FLAG_MSG_BOX_DC 2 // 

#ifdef ELKA
#define X1_BG_FON 10 
#define X2_BG_FON 10+112
#define Y1_BG_FON 20
#define Y2_BG_FON 20+136
#define R1_BG_FON 6
#define X1_TEXT X1_BG_FON+5
#define X2_TEXT X2_BG_FON-5
#define Y1_TEXT Y1_BG_FON+5
#define Y2_TEXT Y2_BG_FON-5
#define DX1 X1_BG_FON+5
#define DX2 X2_BG_FON-45

#else
#define X1_BG_FON 10 
#define X2_BG_FON 10+112
#define Y1_BG_FON 20
#define Y2_BG_FON 20+136
#define R1_BG_FON 6
#define X1_TEXT X1_BG_FON+5
#define X2_TEXT X2_BG_FON-5
#define Y1_TEXT Y1_BG_FON+5
#define Y2_TEXT Y2_BG_FON-5
#define DX1 X1_BG_FON+5
#define DX2 X2_BG_FON-45
#endif

#ifdef NEWSGOLD
#define MSG_FONT 11
#else
#define MSG_FONT 7
#endif

int IsSimpleMsg = 0, 
    IsMsxBox    = 0,
    IsMsxBoxDC  = 0,
    IsMsxBoxNG  = 0,
    M_B_B_MODE  = 0;

int x_simple_but = X1_BG_FON + 5,
    y_simple_but = Y2_BG_FON - 5,
    x_msgbox_but = X1_BG_FON + 5,
    y_msgbox_but = Y2_BG_FON - 25;

int DrawRoundedSquare(int x,int font, int flag, const char* foncolor, const char* fringcolour)
{
   WSHDR *ws_sq = AllocWS(32);
   DrawRoundedFrame( x, y_msgbox_but , x+40 ,y_msgbox_but+20, 3, 3,0,grey20,GetPaletteAdrByColorIndex(23));
   switch(flag)
   {
         case 1: wsprintf(ws_sq, perc_t, LG_SHOWMSG_YES ); break;
         case 2: wsprintf(ws_sq, perc_t, LG_SHOWMSG_NO  ); break;
         case 3: wsprintf(ws_sq, perc_t, LG_SHOWMSG_Ok  ); break;
   }
   DrawString(ws_sq, x+2 , y_msgbox_but+2, scr_w ,scr_h, font,0, foncolor, fringcolour);
   FreeWS(ws_sq);
   return 0;
}

int DrawFonMsg(int font)
{
  DrawRoundedFrame(x_msgbox_but, y_msgbox_but , x_msgbox_but+40 ,y_msgbox_but+20, 3, 3, 0,grey0,grey0);
  DrawRoundedSquare( DX1,  font, 1, GetPaletteAdrByColorIndex(0), GetPaletteAdrByColorIndex(23));
  DrawRoundedSquare( DX2,  font, 2, GetPaletteAdrByColorIndex(0), GetPaletteAdrByColorIndex(23));
  return 0;
}
void ShWMSG(int flag, WSHDR *wmsg, int font, const char* foncolor, const char* fringcolour)
{
 DrawRoundedFrame( X1_BG_FON, 
                   Y1_BG_FON, 
                   X2_BG_FON,
                   Y2_BG_FON,
                   R1_BG_FON,
                   R1_BG_FON,
                   0,
                   grey0,
		   black30 );  
   
 switch(flag)
 {
    case 0:
         IsSimpleMsg=1;
         IsMsxBoxDC =0; 
         IsMsxBox =0; 
         IsMsxBoxNG=0;
         
         DrawRoundedSquare(x_simple_but,  font, 3, GetPaletteAdrByColorIndex(0), GetPaletteAdrByColorIndex(23));
    break;
         
    case 1:
         IsMsxBox=1;
         IsMsxBoxDC =0; 
         IsSimpleMsg = 0;
         IsMsxBoxNG=0;
         DrawFonMsg( font);

    break;
    case 2:
         IsMsxBoxDC=1;
         IsMsxBox =0; 
         IsSimpleMsg = 0;
         IsMsxBoxNG=0;
         DrawFonMsg( font);
    break;
    case 3:
         IsMsxBoxNG=1;
         IsMsxBox = IsSimpleMsg = IsMsxBoxDC=0;
         
         DrawFonMsg( font);
    break;
}

  DrawString( wmsg, 
              X1_TEXT,
              Y1_TEXT,
              X2_TEXT,
              Y2_TEXT,
              font,
              2,
              foncolor, 
              fringcolour
             );
 
  
}


//Redraw
static void OnRedraw(SWMSG_GUI *data)
{
  if (data->gui.state==2)
  {
              
	ShWMSG(data->flag, data->msg, data->font, data->foncolor, data->fringcolour);

   }
}




 //Create
static void OnCreate(SWMSG_GUI *data,void *(*malloc_adr)(int))
{
	data->gui.state=1;
}

//Close
static void OnClose(SWMSG_GUI *data,void (*mfree_adr)(void *))
{

	FreeWS(data->msg);
	data->gui.state=0;
}

//Focus
static void OnFocus(SWMSG_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
	#ifdef ELKA
	DisableIconBar(1);
	#endif
	DisableIDLETMR();
	data->gui.state=2;
}

//Unfocus
static void OnUnfocus(SWMSG_GUI *data,void (*mfree_adr)(void *))
{
	#ifdef ELKA
	DisableIconBar(0);
	#endif
        if (data->gui.state!=2) return;
        data->gui.state=1;
}



void NULL_PARAM()
{
    IsSimpleMsg = 0, 
    IsMsxBox    = 0,
    IsMsxBoxDC  = 0,
    M_B_B_MODE  = 0;
}
 //OnKey
static int OnKey(SWMSG_GUI *data, GUI_MSG *msg)
{
 int sh=msg->gbsmsg->msg;
  switch(sh)
  {
   
   case KEY_DOWN:
	
	switch(msg->gbsmsg->submess)
	{
       
	 case RIGHT_BUTTON:
	 case '6':
          if(IsMsxBox || IsMsxBoxDC || IsMsxBoxNG)
          {
            if(M_B_B_MODE==0)M_B_B_MODE=1;else M_B_B_MODE=0;
            if(x_msgbox_but==DX1)x_msgbox_but=DX2;else x_msgbox_but=DX1;
          }

	   break;
	 case LEFT_BUTTON:
	 case '4':
          if(IsMsxBox || IsMsxBoxDC || IsMsxBoxNG)
          {
            if(M_B_B_MODE==0)M_B_B_MODE=1;else M_B_B_MODE=0;
            if(x_msgbox_but==DX1)x_msgbox_but=DX2;else x_msgbox_but=DX1;
          }
	
	   break;
           
         case '5':  
         case ENTER_BUTTON:
           if(IsSimpleMsg==1) return 1;
           else
         if(IsMsxBox)
         {
           if(M_B_B_MODE==0)AnswerResGame(1);
           if(M_B_B_MODE==1)AnswerResGame(0);
         }
         else
         if(IsMsxBoxDC)
         {
           if(M_B_B_MODE==0)AnswerExitGame(1);
           if(M_B_B_MODE==1)AnswerExitGame(0); 
         }
         else
         if(IsMsxBoxNG)
         {
           if(M_B_B_MODE==0)AnswerNewGame(1);
           if(M_B_B_MODE==1)AnswerNewGame(0); 
         }
         //NULL_PARAM();
         return 1;
         
         
	
	}
	DirectRedrawGUI();
	break;
   }
	DirectRedrawGUI();
  return 0;
}


 // фигня какая-то
static int met0(void){return(0);}
static const void * const SWMSG_gui_methods[11]={
  (void *)OnRedraw,
  (void *)OnCreate,
  (void *)OnClose,
  (void *)OnFocus,
  (void *)OnUnfocus,
  (void *)OnKey,
  0,
  (void *)kill_data, //method7, //Destroy
  (void *)met0,
  (void *)met0,
  0
};





void ShowWMSG(int flag, const char* msg, int font, const char* foncolor, const char* fringcolour, int ena)
{
 if(ena)
 {
  static const RECT Canvas={0,0,0,0};
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  StoreXYXYtoRECT((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  SWMSG_GUI *main_gui=malloc(sizeof(SWMSG_GUI));
  zeromem(main_gui,sizeof(SWMSG_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
//view_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)SWMSG_gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  
  main_gui->flag=flag;
  main_gui->font=font;
  main_gui->msg=AllocWS(256);
  wsprintf(main_gui->msg, perc_t, msg);
  main_gui->foncolor=(char*)foncolor;
  main_gui->fringcolour=(char*)fringcolour;
  CreateGUI(main_gui);
     
 }
}
