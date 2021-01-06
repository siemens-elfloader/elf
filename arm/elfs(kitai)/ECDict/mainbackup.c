#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "define.h"
#include "dict.h"
#include <stdbool.h>

//================= extern vars and funcs from dict.c ========================/

#define TEXT_NOAUTOLINEBREAK 128
#define MAX_UNICODE_STR 512

extern char *indexbuf;
extern const int idxbuf_size;

extern char **index;
extern const int wordcount;

extern int dict;

extern bool m_f_err;                //memory or file error;
extern char* err_msg;               //error msg string;
unsigned short mferr_unicode[] =    //"ÄÚ´æ²»×ã»ò¶ÁÎÄ¼þ´í£¬ÇëÍË³ö£¡"
        {0x5185, 0x5B58, 0x4E0D, 0x8DB3, 0x6216, 0x8BFB, 0x6587,
        0x4EF6, 0x9519, 0xFF0C, 0x8BF7, 0x9000, 0x51FA, 0xFF01, 0};

char cr[] = "[ECDICT v0.6]\nAn English-Chinese DICTionary for Siemens ELF.\n\nProgrammed by CHC, May 2007.\n\nBest Wishes...";
        

//============================================================================/


//============================================================================/

int start_index = 9;
int highlight_item = 0;
int open_entry_index = 9;

char pre_inputword[128];
bool wanna_quit = false;
int ed1_id;

#define TMR_SECOND 216
GBSTMR  timer;
bool fw_showing = false;
unsigned long global_time = 0;
unsigned long last_key_time = 0;
int ed1_last_key_down = 0;

#ifdef DICT_DEBUG
WSHDR* debug_kd_word;
WSHDR* debug_ku_word;
WSHDR* debug_lp_word;
#endif

//============================================================================/

const int minus11 = -11;

bool list_redraw_hooked = false;
void (*old_ed1_redraw)(void *data);
//void (*old_ed1_close)(void *data);

const SOFTKEY_DESC menu_sk[]=
{
    {0x0018,0x0000,(int)"Config"},
    {0x0001,0x0000,(int)"Close"},
    {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
	menu_sk,3
};

typedef struct
{
	CSM_RAM csm;
	int gui_id;
}MAIN_CSM;


extern const unsigned int cfg_showfreeram;

//extern const unsigned int cfg_inputword_x;
//extern const unsigned int cfg_inputword_y;
//extern const unsigned int cfg_inputword_x2;
//extern const unsigned int cfg_inputword_y2;
extern const RECT win_pos;

extern const unsigned int cfg_list_x_start;
extern const unsigned int cfg_list_y_start;

extern const unsigned int cfg_item_n;
extern const unsigned int cfg_spacing;
extern const unsigned int cfg_padding;

extern const char cfg_separator_color[4];
extern const unsigned int cfg_dim_fontsize;
extern const char cfg_dim_color[4];
//extern const int cfg_dim_bgcolor = 23;

extern const unsigned int cfg_highlight_fontsize;
extern const char cfg_highlight_color[4];

extern const char cfg_highlight_bgcolor[4];
extern const char cfg_bordercolor[4];

extern const char cfg_scrollbar_color[4];
extern const char cfg_scrollbar_blkcolor[4];

//====== instant view ==========//
extern const unsigned int cfg_floatwin;
extern const unsigned int cfg_fw_delay;
extern const unsigned int cfg_fw_phonetic;
extern const unsigned int cfg_fw_height;
extern const unsigned int cfg_fw_width;
extern const unsigned int cfg_fw_fontsize;
extern const char cfg_fw_fontcolor[4];
extern const char cfg_fw_bgcolor[4];
extern const char cfg_fw_bordercolor[4];
//=========== modifiable ============/

// modifiables
unsigned int floatwin;
unsigned int fw_phonetic;

//unsigned int MAINCSM_ID=0;
int screenh;
int screenw;


void Error(const char *msg)
{
	m_f_err = true;
	LockSched();
	ShowMSG(1, (int)msg);
	UnlockSched();
}

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

void ed2_load_entry_text(GUI* gui, int text_id)     //ed2
{
  EDITCONTROL ec;
	ExtractEditControl(gui, text_id, &ec);
	//WSHDR *ws = AllocWS(256);
	if( m_f_err )                                                     
  {                                                                   
      //copy_unicode_2ws(ec.pWS, mferr_unicode);                      
      wsprintf(ec.pWS, "%t\0", "");                                       
  }                                                                   
  else if( ed1_last_key_down==LEFT_SOFT && pre_inputword[0]==0 )      
  {                                                                   
      str_2ws(ec.pWS, cr, sizeof(cr));                                    
  }                                                                   
  else                                                                
  {                                                                   
      construct_entry_text(ec.pWS, index[open_entry_index], 1, 1, 1);     
  }  
  //DrawString(ws,5,screenh/6,screenw,screenh,FONT_SMALL,32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));                                                        
  //FreeWS(ws);
  StoreEditControl(gui, text_id, &ec);
}

void my_ed1_redraw(GUI* gui)
{
	int highlight_font_height = GetFontYSIZE(cfg_highlight_fontsize);
	int dim_font_height = GetFontYSIZE(cfg_dim_fontsize);
    int font_height_diff = 0;   //highlight_font_height - dim_font_height;
    
    int screen_width = ScreenW();
    int screen_height = ScreenH();
    RECT highlight;
    int i;
    WSHDR *ws;
    
    //REDRAW
    old_ed1_redraw(gui);
    
    if( m_f_err )
    {        
        ws = AllocWS(sizeof(mferr_unicode));
		copy_unicode_2ws(ws, mferr_unicode);
        
        DrawString(ws,
                   cfg_list_x_start + 2,
                   cfg_list_y_start,
                   screen_width - 6,
                   cfg_list_y_start + 120,
                   cfg_highlight_fontsize,
                   TEXT_ALIGNLEFT,
                   cfg_dim_color,
                   GetPaletteAdrByColorIndex(23)
                       );
        FreeWS(ws);
        return;
    }
    
    ws = AllocWS(MAX_UNICODE_STR);
    
    DrawLine(cfg_list_x_start + 1,
             cfg_list_y_start - 2,
             screen_width - cfg_list_x_start - 1,
             cfg_list_y_start - 2,
             0,
             cfg_separator_color);
    
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
            
            highlight.x  = cfg_list_x_start;
            highlight.y  = cfg_list_y_start + i*(dim_font_height + cfg_spacing + 2*cfg_padding);
            //highlight.y  = cfg_list_y_start + i*(dim_font_height + 5);
            highlight.x2 = screen_width-4;
            highlight.y2 = highlight.y + dim_font_height + 2*cfg_padding + font_height_diff;
            //highlight.y2 = highlight.y + dim_font_height + 4 + font_height_diff;
            
            DrawRoundedFrame(highlight.x,
                             highlight.y,
                             highlight.x2,
                             highlight.y2,
                             2,
                             2,
                             2,     //border-type 0=outline 1=dotted 2=inline
                             cfg_bordercolor,
                             cfg_highlight_bgcolor
                                 );
            DrawString(ws,
                       highlight.x + 2,
                       highlight.y + cfg_padding + 1,
                       //highlight.y + 3,
                       highlight.x2 - 2,
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
                       cfg_list_x_start + 2,
                       cfg_list_y_start + i*(dim_font_height + cfg_spacing + 2*cfg_padding) + cfg_padding + font_height_diff + 1,
                       //cfg_list_y_start + i*(dim_font_height + 5) + 2 + font_height_diff + 1,
                       screen_width - 6,
                       cfg_list_y_start + (i+1)*(dim_font_height + cfg_spacing + 2*cfg_padding) - cfg_padding + font_height_diff - 1,
                       //cfg_list_y_start + (i+1)*(dim_font_height + 5) - 2 + font_height_diff - 1,
                       cfg_dim_fontsize,// - 1, //Make it thin!!!!
                       TEXT_ALIGNLEFT + TEXT_NOAUTOLINEBREAK,
                       cfg_dim_color,
                       GetPaletteAdrByColorIndex(23)
                           );
        }
        
    }
    
    //draw scrollbar
    int barlen = cfg_item_n * (dim_font_height + 2*cfg_padding + cfg_spacing) + font_height_diff;
    //int barlen = cfg_item_n * (dim_font_height + 5) + font_height_diff;
    int blkpos = barlen * (start_index+highlight_item) / wordcount;
    
    DrawLine(screen_width - 2,
             cfg_list_y_start,
             screen_width - 2,
             cfg_list_y_start + barlen,
             0,
             cfg_scrollbar_color);
    
    DrawRoundedFrame(screen_width - 3,
                     cfg_list_y_start + blkpos - 1,
                     screen_width - 1,
                     cfg_list_y_start + blkpos + 1,
                     0,
                     0,
                     0,     //border-type 0=outline 1=dotted 2=inline
                     cfg_scrollbar_blkcolor,
                     cfg_scrollbar_blkcolor);
    
    //draw instant view
    if( floatwin && (global_time-last_key_time)>=cfg_fw_delay )
    {
        fw_showing = true;
        
        int fw_x, fw_y;
        
        fw_x = highlight.x2 - 2 - cfg_fw_width;
        
        if( (highlight.y2 + cfg_fw_height > screen_height - 18)     //ÏÂ·½·Å²»ÏÂ£¬18=Èí¼ü¸ß¶È
           && (highlight.y  >= cfg_list_y_start + cfg_fw_height))   //ÇÒÉÏ·½ÄÜ·ÅÏÂ
        {
            fw_y = highlight.y - cfg_fw_height;             //·Åµ½ÉÏ·½
        }
        else
        {
            fw_y = highlight.y2;                            //·Åµ½ÏÂ·½
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
        DrawString(ws,
                   fw_x + 2,
                   fw_y + 2,
                   fw_x + cfg_fw_width - 2,
                   fw_y + cfg_fw_height - 2,
                   cfg_fw_fontsize,
                   TEXT_ALIGNLEFT + TEXT_NOAUTOLINEBREAK,
                   cfg_fw_fontcolor,
                   GetPaletteAdrByColorIndex(23)
                       );
                   
    }
    else
    {
        fw_showing = false;
    }
    
    
    //draw debug info
    if( cfg_showfreeram )
    {
        int fr = GetFreeRamAvail();
        wsprintf(ws, "FreeRam: %dKB", fr/1024);
        DrawString(ws,
               2,
               screen_height-SoftkeyH()-GetFontYSIZE(FONT_SMALL),
               screen_width - 6,
               screen_height-SoftkeyH(),
               FONT_SMALL,// - 1, 
               TEXT_ALIGNRIGHT + TEXT_OUTLINE,
               GetPaletteAdrByColorIndex(0),
               GetPaletteAdrByColorIndex(1)
                   );
    }
    
#ifdef DICT_DEBUG        
    DrawString(debug_kd_word, 0,0,131,15,7,
               TEXT_ALIGNRIGHT,
               GetPaletteAdrByColorIndex(0),
               GetPaletteAdrByColorIndex(23)
                   );
    DrawString(debug_lp_word, 0,15,131,30,7,
               TEXT_ALIGNRIGHT,
               GetPaletteAdrByColorIndex(2),
               GetPaletteAdrByColorIndex(23)
                   );
    DrawString(debug_ku_word, 0,30,131,45,7,
               TEXT_ALIGNRIGHT,
               GetPaletteAdrByColorIndex(4),
               GetPaletteAdrByColorIndex(23)
                   );
    
    wsprintf(ws, "%d|%d|%d|%d|%d\n%d|%d|%d|%d|%d", gui->unk2, gui->unk3, gui->unk4, gui->unk5, gui->unk6,
             gui->unk7, gui->unk8, gui->unk9, gui->unk10, gui->flag30);
    
/*    INPUTDIA_DESC* id = (INPUTDIA_DESC*) gui->definition;
    wsprintf(ws, "%d|%d|%d|%d|%d\n%d|%d|%d", id->one, id->zero1, id->font, id->_100, id->_101,
             id->zero2, id->zero3, id->_0x40000000);
*/    

    
    //TDate d;
    //TTime t;
    //GetDateTime(&d, &t);
    //wsprintf(ws, "%ld|%ld|%d|%d|\n%d|%d|%d|%ld", global_time, d.year, d.month, d.day, t.hour, t.min, t.param, t.param2);
    
    wsprintf(ws, "%ld|%ld", global_time, last_key_time);
    
    DrawString(ws, 0,0,131,100,7,
               TEXT_ALIGNRIGHT,
               GetPaletteAdrByColorIndex(0),
               GetPaletteAdrByColorIndex(23)
               );
#endif      
  
    FreeWS(ws);
}


void ed1_locret(void){}
void ed2_locret(void){}

int create_ed1(void);
int create_ed2(void);

/*
void my_ed1_close(GUI* gui)
{
ShowDialog_Error(1, (int)"my exit");
gui->state = 1;
}
*/


void QuitProc(int really_quit)  //»Øµ÷º¯Êý²»ÊÇÁ¢¼´µ÷ÓÃµÄ
{
    if( !really_quit )
    {
        wanna_quit = true;
    }
    //else
    //{
        //create_ed1();     //dup!
    //}
}

int ed1_onkey(GUI *data, GUI_MSG *msg)
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
    
    if( keymsg==KEY_DOWN )  //...for showing cr...
    {
        ed1_last_key_down = keycode;
    }
    if( keymsg==LONG_PRESS )
    {
        ed1_last_key_down = 0;
    }
    
	if ( keymsg==KEY_UP || keymsg==LONG_PRESS)
	{
	  int upthres, downthres;                                                                    
    upthres = 1;                                                                                   
    downthres = cfg_item_n - 2;                                                                    
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
        ret = RET_CLOSE;    
        break;    
      case GREEN_BUTTON:
        fw_phonetic = 1 - fw_phonetic;
        ret = RET_REDRAW; 
        break;      
      case LEFT_SOFT://¿ÉÄÜÏÔÊ¾°æÈ¨ÐÅÏ¢
        if( keymsg == KEY_UP && get_inputword(data, 1)[0]==0 )
          ret = RET_CLOSE;            
        break;
    //else if( keycode == RIGHT_SOFT )                                                             
    //{                                                                                            
        //do_lookup(data);      //      ÔÚÕâÀïdo_lookup¾Í´íÁË¡£ÏµÍ³»¹Î´´¦ÀíonkeyÊÂ¼þ               
    //}                                                                                                                                                                                                  
    //* switch float window                                         
#ifdef NEWSGOLD                                                                                                      
      case '*':
        if(keymsg==LONG_PRESS)  
        {
          wanna_quit = false; 
          MsgBoxYesNo(1, (int)"Quit ECDict?", QuitProc); 
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
        wanna_quit = false;                                                                        
        MsgBoxYesNo(1, (int)"Quit ECDict?", QuitProc);                                             
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
                                                                                                   
                                                                                               
    
    //for debug
#ifdef DICT_DEBUG
    char* temp;
    if ( keymsg==KEY_DOWN )
    {
        temp = get_inputword(data, 1);
        str_2ws(debug_kd_word, temp, strlen(temp));
    }
    if( keymsgg==LONG_PRESS )
    {
        temp = get_inputword(data, 1);
        str_2ws(debug_lp_word, temp, strlen(temp));
    }
    if( keymsg==KEY_UP )
    {
        temp = get_inputword(data, 1);
        str_2ws(debug_ku_word, temp, strlen(temp));
    }
#endif
    
    
    //REDRAW();
    //return -1;        //return -1 to redraw
    //return 1: close
	return ret;
}

void ed1_ghook(GUI *gui, int cmd)
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
				old_ed1_redraw=(void (*)(void *))(methods[0]);
				methods[0]=(void *)my_ed1_redraw;
                
                //old_ed1_close =(void (*)(void *))(methods[2]);
                //methods[2]=(void *)my_ed1_close;
                
				m[1]=methods;
                list_redraw_hooked = true;
			}
		}
        //gui->methods[0] = (void*)my_ed1_redraw;     //no simple here..
    }
    else if( cmd == 7 ) //?? OnRun ??
    {
        do_lookup(gui);
    }
        
}

void patch_dialog(INPUTDIA_DESC* dialog, int x,int y,int x2, int y2)
{
    dialog->rc.x = x;
    dialog->rc.y = y;
    dialog->rc.x2 = x2;
    dialog->rc.y2 = y2;
}

//unsigned short thdr1[] = {0xF182, 0x496C, 0x8BCD, 0x5178, 0}; //"Ó¢ºº´Êµä"
HEADER_DESC ed1_hdr={0, 0, 131, 19, NULL, (int)"En-Cn Dictionary", LGP_NULL};

INPUTDIA_DESC ed1_desc=
{
	1,
	ed1_onkey,
	ed1_ghook,
	(void *)ed1_locret,
	0,
	&menu_skt,
	//{4, 12, 131, 172},
	{2,YDISP+2,scrw,scrh},
	FONT_SMALL,
	100,
	101,
	0,
    
	//  0x00000001 - Âûðîâíÿòü ïî ïðàâîì?êð?	//  0x00000002 - Âûðîâíÿòü ïî öåíòðó
	//  0x00000004 - Èíâåðñ? çíàêîìåñ?//  0x00000008 - UnderLine
	//  0x00000020 - Íå ïåðåíîñèòü ñëîâ?//  0x00000200 - bold
	0,
    
	//  0x00000002 - ReadOnly
	//  0x00000004 - Íå äâèãàåòñÿ êóðñîð
	//  0x40000000 - Ïîìå?òü ìåñòàì?ñîôò-êíîï?	0
	0x40000000
};

int create_ed1(void)
{
	void *ma=malloc_adr();
	void *eq;
	WSHDR *pws;
	EDITCONTROL ec;
    
	PrepareEditControl(&ec);
	eq=AllocEQueue(ma,mfree_adr());
	pws=AllocWS(MAX_UNICODE_STR);

	wsprintf(pws, "%t", pre_inputword);
	ConstructEditControl(&ec, ECT_NORMAL_TEXT, ECF_APPEND_EOL, pws, 16);    //×î³¤ÊäÈë16¸ö×ÖÄ¸£¿
	AddEditControlToEditQend(eq, &ec, ma);
	FreeWS(pws);
    
    patch_dialog(&ed1_desc, win_pos.x, win_pos.y, win_pos.x2, win_pos.y2); 
    
    list_redraw_hooked = false;
	ed1_id =  CreateInputTextDialog(&ed1_desc, NULL/*&ed1_hdr*/, eq, 1, 0);
    
    return ed1_id;
}

int ed2_onkey(GUI *data, GUI_MSG *msg)
{
#define RET_REDRAW  -1
#define RET_DEFAULT 0
#define RET_CLOSE   1
    
    int ret = RET_DEFAULT;
    int keycode = msg->gbsmsg->submess;
	if ( msg->gbsmsg->msg==KEY_DOWN || msg->gbsmsg->msg==LONG_PRESS)
	{
        switch( keycode )
        {
        case RIGHT_BUTTON:
        case DOWN_BUTTON:
            if( open_entry_index < wordcount-1 )
            {   
                open_entry_index ++;
                ed2_load_entry_text(data, 1);
                ret = RET_REDRAW;
            }
            break;
            
        case LEFT_BUTTON:
        case UP_BUTTON:
            if( open_entry_index > 0 )
            {   
                open_entry_index --;
                ed2_load_entry_text(data, 1);
                ret = RET_REDRAW;
            }
            break;
            
        case LEFT_SOFT:
        case RIGHT_SOFT:
        case RED_BUTTON:
            ret = RET_REDRAW;       //disable right_soft && red_button exit.
        case ENTER_BUTTON:
            create_ed1();
            break;
            
        default:
            break;
        }
	}
    
	return ret; 
}

void ed2_ghook(GUI *gui, int cmd)
{
    static bool new_created;
    
    if (cmd == 0x02)        //onCreate
    {
        new_created = true;
    }
    else if( cmd == 0x0A )  //onFocus
    {        
        if( new_created )
        {
            new_created = false;
            create_ed1();
        }
        else
        {
            open_entry_index = start_index+highlight_item;
            ed2_load_entry_text(gui, 1);
        }
    }
}

HEADER_DESC ed2_hdr={0, 0, 0, 0, NULL, (int)"", LGP_NULL};

INPUTDIA_DESC ed2_desc=
{
	1,
	ed2_onkey,
	ed2_ghook,
	(void *)ed2_locret,
	0,
	&menu_skt,
	//{2,2,131,172},
	{2,YDISP+scrw/6,scrw,scrh},
	FONT_SMALL,
	100,
	101,
	0,
    
	//  0x00000001 - Âûðîâíÿòü ïî ïðàâîì?êð?	//  0x00000002 - Âûðîâíÿòü ïî öåíòðó
	//  0x00000004 - Èíâåðñ? çíàêîìåñ?//  0x00000008 - UnderLine
	//  0x00000020 - Íå ïåðåíîñèòü ñëîâ?//  0x00000200 - bold
	0,
    
	//  0x00000002 - ReadOnly
	//  0x00000004 - Íå äâèãàåòñÿ êóðñîð
	//  0x40000000 - Ïîìå?òü ìåñòàì?ñîôò-êíîï?	0
	0x40000000
};

int create_ed2(void)
{
	void *ma=malloc_adr();
	void *eq;
	WSHDR *pws;
	EDITCONTROL ec;
    
	PrepareEditControl(&ec);
	eq=AllocEQueue(ma,mfree_adr());
	pws=AllocWS(MAX_UNICODE_STR);
    
    str_2ws(pws, cr, sizeof(cr));
    
	ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, pws, MAX_UNICODE_STR);
	AddEditControlToEditQend(eq, &ec, ma);
    
	FreeWS(pws);
    
	return CreateInputTextDialog(&ed2_desc, &ed2_hdr, eq, 1, 0);
}

void Killer(void)
{
	extern void *ELF_BEGIN;
	extern void kill_data(void *p, void (*func_p)(void *));
	CloseDict();
	UnloadDictIndex();
  GBS_DelTimer(&timer);
	kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_oncreate(CSM_RAM *data)
{
  screenh=ScreenH();
  screenw=ScreenW();
	MAIN_CSM *csm=(MAIN_CSM*)data;
    
	csm->gui_id=create_ed2();
    
    floatwin = cfg_floatwin;
    fw_phonetic = cfg_fw_phonetic;
    LoadDictIndex();
    OpenDict();
    
#ifdef DICT_DEBUG
    debug_kd_word = AllocWS(64);
    debug_lp_word = AllocWS(64);
    debug_ku_word = AllocWS(64);
#endif
}

void maincsm_onclose(CSM_RAM *csm)
{
#ifdef DICT_DEBUG
    FreeWS(debug_kd_word);
    FreeWS(debug_lp_word);
    FreeWS(debug_ku_word);
#endif
    
	SUBPROC((void *)Killer);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
	MAIN_CSM *csm=(MAIN_CSM*)data;
	if (msg->msg==MSG_GUI_DESTROYED)
	{
		if ((int)msg->data0==csm->gui_id)
		{
			csm->csm.state=-3;
		}
	}
    if( wanna_quit )
    {
        csm->csm.state=-3;
    }
	return(1);
}

unsigned short maincsm_name_body[140];

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
	unsigned short csmname1[] = {0x82F1, 0x6C49, 0x8BCD, 0x5178, 0}; //"Ó¢ºº´Êµä"
	copy_unicode_2ws((WSHDR *)(&MAINCSM.maincsm_name), csmname1);
}

void TimeCounterProc(void)
{
    global_time ++;
    
    if( !fw_showing && (global_time-last_key_time)>=cfg_fw_delay )
    {
        GBS_SendMessage(MMI_CEPID, KEY_DOWN, 99);           //ÔÝÊ±ÏÈÓÃ¼üÂë99×öË¢ÐÂ¡£¡£
    }
    GBS_StartTimerProc(&timer, TMR_SECOND/10, TimeCounterProc);
}

int main()
{
	char dummy[sizeof(MAIN_CSM)];
  InitConfig();
  UpdateCSMname();
  
	LockSched();
	CreateCSM(&MAINCSM.maincsm, dummy, 0);
	UnlockSched(); 
	
	GBS_StartTimerProc(&timer, TMR_SECOND, TimeCounterProc);
	return 0;
}
