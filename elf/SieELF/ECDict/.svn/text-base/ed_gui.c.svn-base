#include "..\inc\swilib.h"
#include "dict.h"
#include "gui.h"
#include "define.h"
#include "rect_patcher.h"
#include <stdbool.h>

#define TEXT_NOAUTOLINEBREAK 128
#define MAX_UNICODE_STR 512

extern const int wordcount;
extern int screenh;
extern int screenw;
extern char **index;
extern bool m_f_err;
extern bool wanna_quit;
extern unsigned int floatwin;
extern bool fw_showing;
extern unsigned long global_time;
extern unsigned long last_key_time;


//config

extern const unsigned int cfg_showfreeram;
extern const unsigned int cfg_fr_font;
extern const char cfg_fr_color[4];
//input gui
extern const RECT win_pos;
extern const unsigned int cfg_item_n;
extern const char cfg_input_gui_color[4];

extern const char cfg_separator_color[4];
extern const unsigned int cfg_dim_fontsize;
extern const char cfg_dim_color[4];

extern const unsigned int cfg_highlight_fontsize;
extern const char cfg_highlight_color[4];

extern const char cfg_highlight_bgcolor[4];
extern const char cfg_bordercolor[4];

//extern const char cfg_scrollbar_color[4];
//extern const char cfg_scrollbar_blkcolor[4];

//====== instant view ==========//
extern const unsigned int cfg_fw_delay;
extern const unsigned int cfg_fw_height;
extern const unsigned int cfg_fw_width;
extern const unsigned int cfg_fw_fontsize;
extern const char cfg_fw_fontcolor[4];
extern const char cfg_fw_bgcolor[4];
extern const char cfg_fw_bordercolor[4];

int ed_id;
int start_index = 9;
int highlight_item = 0;
char pre_inputword[128];
//int ed_last_key_down = 0;
unsigned int fw_phonetic=1;
bool list_redraw_hooked = false;
void (*old_ed_redraw)(void *data);
int is_ed_started=0;

unsigned short mferr_unicode[] =    //"内存不足或读文件错，请退出！"
        {0x5185, 0x5B58, 0x4E0D, 0x8DB3, 0x6216, 0x8BFB, 0x6587,
        0x4EF6, 0x9519, 0xFF0C, 0x8BF7, 0x9000, 0x51FA, 0xFF01, 0};


void QuitProc(int really_quit)  //回调函数不是立即调用的
{
  if( !really_quit )
  {
    wanna_quit = true;
  }
}

void quit(void)
{
  wanna_quit = false; 
  MsgBoxYesNo(1, (int)"Quit ECDict?", QuitProc); 
}

void show_freeram(void)
{
  WSHDR *ws=AllocWS(32);
  int fr = GetFreeRamAvail();
  wsprintf(ws, "FreeRam: %dKB", fr/1024);
  DrawString(ws,2,screenh-SoftkeyH()-GetFontYSIZE(FONT_SMALL),screenw - 6,screenh-SoftkeyH(),cfg_fr_font,TEXT_ALIGNRIGHT + TEXT_OUTLINE,cfg_fr_color,GetPaletteAdrByColorIndex(1));
  FreeWS(ws);
}

SOFTKEY_DESC menu_sk[]=
{
    {0x0018,0x0000,(int)""},
    {0x0001,0x0000,(int)""},
    {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
	menu_sk,0
};

char* get_inputword(GUI* gui, int editc_id)     //ed1
{
  static char word[64];
  EDITCONTROL ec; 
  ExtractEditControl(gui, editc_id, &ec);
  ws_2str(ec.pWS, word, sizeof(word));
  return word;
}

//hard to write a function to set inputword, maybe because of T9 buffer.
void do_lookup(GUI *data)                       //ed1
{
  int pos;
  char *word = get_inputword(data, 1);
  
  //if input word doesn't changed, then no need to lookup!
  if( strcmp(word, pre_inputword)!=0 && (pos = lookup(word)) >= 0 )
  {
    strcpy(pre_inputword, word);
    start_index = pos;
    highlight_item = 0;
  }
}

void my_ed_redraw(GUI* gui)
{
  int highlight_font_height = GetFontYSIZE(cfg_highlight_fontsize);
  int dim_font_height = GetFontYSIZE(cfg_dim_fontsize);
  int font_height_diff = 0;   //highlight_font_height - dim_font_height;
  RECT highlight;
  int i;
  int y_end;
  WSHDR *ws;  
  //REDRAW  
  old_ed_redraw(gui);  
  DrawRectangle(0,win_pos.y2,screenw,screenh,0,cfg_input_gui_color,cfg_input_gui_color);
  if( m_f_err )
  {        
    ws = AllocWS(sizeof(mferr_unicode));
    copy_unicode_2ws(ws, mferr_unicode);
    DrawString(ws,win_pos.x + 2,win_pos.y2,screenw - 6,win_pos.y2 + 120,cfg_highlight_fontsize,TEXT_ALIGNLEFT,cfg_dim_color,GetPaletteAdrByColorIndex(23));
    FreeWS(ws);
    return;
  }
  //show free ram
  if(cfg_showfreeram)
  {
    show_freeram();
    y_end=screenh-SoftkeyH()-GetFontYSIZE(FONT_SMALL)-1;
  }
  else
  {
    y_end=screenh-SoftkeyH()-1; 
  }
  ws = AllocWS(MAX_UNICODE_STR);  
  DrawLine(win_pos.x+1,win_pos.y2,screenw-win_pos.x+1,win_pos.y2,0,cfg_separator_color);  
  //draw items
  for( i=0; i<cfg_item_n; i++ )
  {
    if( (start_index+i)>=wordcount )
    {
      break;
    }    
    str_2ws(ws, index[start_index+i], strlen(index[start_index+i]));
    if( i == highlight_item )       //draw highlight item and frame
    {
      font_height_diff = highlight_font_height - dim_font_height;
      
      highlight.x  = win_pos.x;
      highlight.y  = win_pos.y2 + i*(dim_font_height + 5);
      highlight.x2 = screenw-4;
      highlight.y2 = highlight.y + dim_font_height + 4 + font_height_diff;
      
      DrawRoundedFrame(highlight.x,
                       highlight.y,
                       highlight.x2,
                       highlight.y2,
                       2,
                       2,
                       2,/*border-type 0=outline 1=dotted 2=inline*/
                       cfg_bordercolor,
                       cfg_highlight_bgcolor
                       );
      DrawString(ws,
                 highlight.x + 2,
                 highlight.y + 3,
                 //highlight.x2 - 2,
                 512,//加大宽度范围，防止自动换行
                 highlight.y2 - 1,
                 cfg_highlight_fontsize,
                 TEXT_ALIGNLEFT + TEXT_NOAUTOLINEBREAK,
                 cfg_highlight_color,
                 GetPaletteAdrByColorIndex(23)
                 ); 
    }
    else                        //draw dim(normal) item, no frame
    {
      DrawString(ws,
                 win_pos.x + 2,
                 win_pos.y2 + i*(dim_font_height + 5) + 2 + font_height_diff + 1,
                 //screenw - 6,
                 512,//加大宽度范围，防止自动换行
                 //win_pos.y2 + (i+1)*(dim_font_height + 5) - 2 + font_height_diff - 1,
                 y_end,
                 cfg_dim_fontsize,// - 1, //Make it thin!!!!
                 TEXT_ALIGNLEFT + TEXT_NOAUTOLINEBREAK,
                 cfg_dim_color,
                 GetPaletteAdrByColorIndex(23)
                 );
    }    
  }    
  //draw scrollbar
  //去掉了意义并不大的进度滑块
  //int barlen = cfg_item_n * (dim_font_height + 5) + font_height_diff;
  //int blkpos = barlen * (start_index+highlight_item) / wordcount;  
  //DrawLine(screenw - 2,win_pos.y2,screenw - 2,win_pos.y2 + barlen,0,cfg_scrollbar_color);  
  //DrawRoundedFrame(screenw - 3,
  //               win_pos.y2 + blkpos - 1,
  //               screenw - 1,
  //               win_pos.y2 + blkpos + 1,
  //               0,
  //               0,
  //               0,     //border-type 0=outline 1=dotted 2=inline
  //               cfg_scrollbar_blkcolor,
  //               cfg_scrollbar_blkcolor);  
  //draw instant view
  if( floatwin && (global_time-last_key_time)>=cfg_fw_delay )
  {
    fw_showing = true;      
    int fw_x, fw_y;      
    fw_x =highlight.x2-2-cfg_fw_width;      
    if((highlight.y2+cfg_fw_height>y_end)     //下方放不下
       &&(highlight.y>=win_pos.y2+cfg_fw_height))   //且上方能放下
    {
      fw_y = highlight.y-cfg_fw_height-1;             //放到上方
    }
    else
    {
      fw_y = highlight.y2+1;                            //放到下方
    }      
    DrawRoundedFrame(fw_x,
                     fw_y,
                     fw_x + cfg_fw_width,
                     fw_y + cfg_fw_height,
                     4,
                     4,
                     2,     //border-type 0=outline 1=dotted 2=inline
                     cfg_fw_bordercolor,
                     cfg_fw_bgcolor
                         );      
    construct_entry_text(ws, index[start_index + highlight_item], 0, fw_phonetic, 1);
    DrawString(ws,fw_x + 2,fw_y + 2,fw_x + cfg_fw_width - 2,fw_y + cfg_fw_height - 2,cfg_fw_fontsize,TEXT_ALIGNLEFT + TEXT_NOAUTOLINEBREAK,cfg_fw_fontcolor,GetPaletteAdrByColorIndex(23));
  }
  else
  {
    fw_showing = false;
  }
  FreeWS(ws);
}

void ed_locret(void){}

int ed_onkey(GUI *data, GUI_MSG *msg)
{
#define RET_REDRAW  -1
#define RET_DEFAULT 0
#define RET_CLOSE   1
    
  int ret = RET_DEFAULT;
  int keycode = msg->gbsmsg->submess;
  int keymsg = msg->gbsmsg->msg;
  
  if( keycode == 99 )     //virtual redraw demand keycode
  {
    return RET_REDRAW;
  }
  if( m_f_err )
  {
    wanna_quit = true;
    return RET_CLOSE;
  }  
  //if( keymsg==KEY_DOWN )  //...for showing cr...
  //{
  //    ed_last_key_down = keycode;
  //}
  //if( keymsg==LONG_PRESS )
  //{
  //    ed_last_key_down = 0;
  //}
	if ( keymsg==KEY_DOWN || keymsg==LONG_PRESS)
	{
	  int upthres, downthres;                                                                    
    upthres = 2;                                                                                   
    downthres = cfg_item_n - 3;                                                                    
    switch(keycode)                                                                                
    {                                                                                              
      case DOWN_BUTTON:                                                                                         
        if( (highlight_item==downthres || highlight_item==cfg_item_n)                              
           && (start_index < wordcount-highlight_item-1) )                                         
        {                                                                                          
            //move whole                                                                           
            start_index ++;                                                                        
        }                                                                                          
        else if( highlight_item < cfg_item_n-1                                                     
                && (start_index < wordcount-highlight_item-1) )                                    
        {                                                                                          
            //move highlight                                                                       
            highlight_item ++;                                                                     
        }                                                                                          
        ret = RET_REDRAW;
        break;                                                                                           
      case UP_BUTTON:                                                                                                                                                            
        if( (highlight_item==upthres || highlight_item==0) && (start_index>0) )                    
        {                                                                                          
            //move whole                                                                           
            start_index --;                                                                        
        }                                                                                          
        else if( highlight_item>0 )                                                                
        {                                                                                          
            //move highlight                                                                       
            highlight_item --;                                                                     
        }                                                                                          
        ret = RET_REDRAW;
        break;
      case ENTER_BUTTON:
        //if(get_inputword(data, 1)[0]==0)
        //  create_gui();//由于中键在文本编辑中的作用，对于中键的响应还是去掉
        //ret = RET_CLOSE;    
        break;    
      case GREEN_BUTTON:
        fw_phonetic = 1 - fw_phonetic;
        ret = RET_REDRAW; 
        break;      
      case LEFT_SOFT:
        //if( keymsg == KEY_DOWN && get_inputword(data, 1)[0]==0 )
        //  ret = RET_CLOSE;   
        create_gui();
        break;                                      
#ifdef NEWSGOLD                                                                                                      
      case '*':
        if(keymsg==LONG_PRESS)  
        {
          quit();
          ret = RET_REDRAW;  
        }   
        else
        {
          floatwin = 1 - floatwin;                                                                   
          ret = RET_REDRAW;
        }
        break;                                                                                        
#else                                                                                                         
      case '*':                                                                        
        floatwin = 1 - floatwin;                                                                   
        ret = RET_REDRAW;   
        break;                                                          
      case RED_BUTTON:
        quit();                                             
        ret = RET_REDRAW;
        break;                                                                                          
#endif        
      case '#':
        break;
      default:
        last_key_time = global_time; 
        break;
    }   
  }   
	return ret;
}

void ed_ghook(GUI *gui, int cmd)
{
  if( !list_redraw_hooked ) 
  {
	  static void *methods[16];
	  void **m=GetDataOfItemByID(gui,4);
      
	  if (m)
	  {
	  	if (m[1])
	  	{
	  		memcpy(methods,m[1],sizeof(methods));
	  		old_ed_redraw=(void (*)(void *))(methods[0]);
	  		methods[0]=(void *)my_ed_redraw;
                
	  		m[1]=methods;
                list_redraw_hooked = true;
	  	}
	  }
  }
  else if( cmd == 7 ) //?? OnRun ??
  {
      do_lookup(gui);
  }     
}

INPUTDIA_DESC ed_desc=
{
	1,
	ed_onkey,
	ed_ghook,
	(void *)ed_locret,
	0,
	&menu_skt,
	{2,YDISP+2,scrw,scrh},
	FONT_SMALL,
	100,
	101,
	0,
    
	0,
    
	0x40000000
};

int create_ed(void)
{
  is_ed_started=1;
	void *ma=malloc_adr();
	void *eq;
	WSHDR *pws;
	EDITCONTROL ec;
    
	PrepareEditControl(&ec);
	eq=AllocEQueue(ma,mfree_adr());
	pws=AllocWS(MAX_UNICODE_STR);

	wsprintf(pws, "%t", pre_inputword);
	ConstructEditControl(&ec, ECT_NORMAL_TEXT, ECF_APPEND_EOL, pws, 16);    //最长输入16个字母？
	AddEditControlToEditQend(eq, &ec, ma);
	FreeWS(pws);
    
  patch_dialog(&ed_desc, win_pos.x, win_pos.y, win_pos.x2, win_pos.y2);  
  list_redraw_hooked = false;
	ed_id =  CreateInputTextDialog(&ed_desc, NULL/*&ed1_hdr*/, eq, 1, 0);
    
  return ed_id;
}

