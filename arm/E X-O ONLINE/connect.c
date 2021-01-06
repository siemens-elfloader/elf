#include "C:\ARM\inc\swilib.h"
#include "externs.h"
#include "language.h"


typedef struct
{
  GUI gui;
}ULIST_GUI;

unsigned int ULIST_ID = 0;



typedef struct
{
  CSM_RAM csm;
  int gui_id;
}ULIST_CSM;


extern void kill_data(void *p, void (*func_p)(void *));

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}





//Redraw
static void OnRedraw(ULIST_GUI *data)
{
  if (data->gui.state==2)
  {
   }
}




 //Create
static void OnCreate(ULIST_GUI *data,void *(*malloc_adr)(int))
{
  	#ifdef ELKA
	DisableIconBar(1);
	#endif
	data->gui.state=1;
}

//Close
static void OnClose(ULIST_GUI *data,void (*mfree_adr)(void *))
{
	data->gui.state=0;
}

//Focus
static void OnFocus(ULIST_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
	#ifdef ELKA
	DisableIconBar(1);
	#endif
	DisableIDLETMR();
	data->gui.state=2;
}

//Unfocus
static void OnUnfocus(ULIST_GUI *data,void (*mfree_adr)(void *))
{
	#ifdef ELKA
	DisableIconBar(0);
	#endif
        if (data->gui.state!=2) return;
        data->gui.state=1;
}



 //OnKey
static int OnKey(ULIST_GUI *data, GUI_MSG *msg)
{
 int sh=msg->gbsmsg->msg;
  switch(sh)
  {
   
   case KEY_DOWN:
	
	switch(msg->gbsmsg->submess)
	{
        
	 case RIGHT_SOFT:
		return 1;
       
        case '3':
        break;
	 case UP_BUTTON:          
	 case '2':
              
		
	   break;
	 case DOWN_BUTTON:
	 case '8':
              
	   break;
	 case RIGHT_BUTTON:
	 case '6':
               
		
	   break;
	 case LEFT_BUTTON:
	 case '4':
              
		
	   break;
         case '5':  
         case ENTER_BUTTON:
       
         break; 
    
	}
	DirectRedrawGUI();
	break;
        
   case KEY_UP:
	//movcr.st=1;
	switch(msg->gbsmsg->submess)
	{
         case '5': 
         case ENTER_BUTTON:
        
         break;  
         
	 case UP_BUTTON:
	 case DOWN_BUTTON:
	 case '2':
	 case '8':
		
	   break;
	 case RIGHT_BUTTON:
	 case LEFT_BUTTON:
         case '4':
	 case '6':
		
	   break;
          
	}
	DirectRedrawGUI();
	break;
  }
	DirectRedrawGUI();
  return 0;
}


 // фигня какая-то
static int met0(void){return(0);}
static const void * const ULIST_GUI_methods[11]={
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





void CONNECT_GUI()
{
  static const RECT Canvas={0,0,0,0};
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  StoreXYXYtoRECT((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  ULIST_GUI *main_gui=malloc(sizeof(ULIST_GUI));
  zeromem(main_gui,sizeof(ULIST_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.methods=(void *)ULIST_GUI_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  CreateGUI(main_gui);
      
}
