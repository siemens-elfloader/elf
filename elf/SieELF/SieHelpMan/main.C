#include "..\inc\swilib.h"
#include "conf_loader.h"

#define MENU_CN

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
}MAIN_GUI;

//config
extern const char main_bg_color[4];
extern const unsigned int main_font;
extern const char main_text_color[4];
extern const unsigned int sk_font;
extern const char sk_color[4];
extern const unsigned int sys_re_t;
extern const char test_string[256];
extern const char t_a_b_color[4];
extern const int default_vibra_sta;
extern const int default_light_sta;
extern const int default_sound_sta;
extern const unsigned int max_image_num;
extern const unsigned int max_lpg_num;
extern const unsigned int max_sound_num;

extern void kill_data(void *p, void (*func_p)(void *));

int num=0;
int flag=0;
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
int status_flag=0;
int direct=0;//0为减小，1为增加 
WSHDR *ws_info;
WSHDR *ws_search; // 待查找字符串 
GBSTMR mytmr;
#define TMR_SECOND 216
#ifdef MENU_CN
#define IPC_MY_IPC "西机助手"
#else
#define IPC_MY_IPC "SieHelpMan"
#endif
#define IPC_UPDATE_STAT 1
const char ipc_my_name[]=IPC_MY_IPC;
//unsigned int REFRESH=5;
int vibra_flag;
int light_flag; //0,all , 1,display , 2,kbd , 3,do nothing
int sound_flag;
int screenw;
int screenh;
int imagew; // 待查找图片宽度
int imageh; // 待查找图片高度 
const char _percent_t[]="%t";
/*
#ifdef ELKA
int y_b=24;
#else
int y_b=0;
#endif
*/

const IPC_REQ my_ipc={
  ipc_my_name,
  ipc_my_name,
  NULL
};

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
	rc->x=x;
	rc->y=y;
	rc->x2=x2;
	rc->y2=y2;
}

#pragma inline
void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=screenw-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+YDISP-1;
}

#pragma inline
void patch_input(const INPUTDIA_DESC* inp)
{
  ((INPUTDIA_DESC*)inp)->rc.x=0;
  ((INPUTDIA_DESC*)inp)->rc.y=HeaderH()+1+YDISP;
  ((INPUTDIA_DESC*)inp)->rc.x2=ScreenW()-1;
  ((INPUTDIA_DESC*)inp)->rc.y2=ScreenH()-SoftkeyH()-1;
}

#pragma inline
int get_string_width(WSHDR *ws, int font)
{
  int width=0;
  unsigned short *body=ws->wsbody;
  int len=body[0];
  while(len)
  {
    width+=GetSymbolWidth(body[len],font);
    len--;
  }
  return (width);
}

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

int pow(int x,int y)
{
  int z=1;
  while(y)
  {
    z=z*x;
    y--;
  }
  return z;
}

SOFTKEY_DESC ed_menu_sk[]=
{
  {0x0018,0x0000,(int)""},
  {0x0001,0x0000,(int)""},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB ed_menu_skt=
{
  ed_menu_sk,0
};

unsigned int SEARCH_CSM_ID = 0;
int icon[]={0x58,0};
char gszHeader[21]="Find LGP";
HEADER_DESC ed1_hdr={0,0,0,0,icon,(int)gszHeader,LGP_NULL};
int ed1_onkey(GUI *data, GUI_MSG *msg)
{
	EDITCONTROL ec;
	ExtractEditControl(data, 2, &ec);
	wstrcpy(ws_info, ec.pWS);
	if( flag )
	{
		wsAppendChar(ws_info, ' ');
		ExtractEditControl(data, 4, &ec);
	  wstrcat(ws_info, ec.pWS);
	}
	return 0;
};
void ed1_ghook(GUI *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
};

void ed1_locret(void){};
INPUTDIA_DESC ed1_desc=
{
  1,
  ed1_onkey,
  ed1_ghook,
  (void *)ed1_locret,
  0,
  &ed_menu_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,

  0,

  0x40000000
};

int create_ed(HEADER_DESC *pHeader)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  if ( flag )
  {
#ifdef MENU_CN
    strcpy(gszHeader, "查找图片");   
    wsprintf(ws_info,_percent_t,"图片宽度");
#else
    strcpy(gszHeader, "Find Pic");   
    wsprintf(ws_info,"Pic Width");
#endif
  }
  else
  {
#ifdef MENU_CN
    strcpy(gszHeader, "查找语言包");    
    wsprintf(ws_info,_percent_t, "输入字串：");
#else
    strcpy(gszHeader, "Find LGP");   
    wsprintf(ws_info,"Input String:");
#endif
  }
  	
  ConstructEditControl(&ec,ECT_HEADER,0x40,ws_info,ws_info->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);
 
  if ( flag )
  {
  	wsprintf(ws_info, "%d", imagew);
  	ConstructEditControl(&ec,ECT_NUMBER_TYPING,0x40,ws_info,3);
  	AddEditControlToEditQend(eq,&ec,ma);
#ifdef MENU_CN
  	 wsprintf(ws_info,_percent_t, "图片高度");
#else
         wsprintf(ws_info,"Pic Height");
#endif
  	ConstructEditControl(&ec,ECT_HEADER,0x40,ws_info,10);
  	AddEditControlToEditQend(eq,&ec,ma);
  	wsprintf(ws_info, "%d", imageh);
  	ConstructEditControl(&ec,ECT_NUMBER_TYPING,0x40,ws_info,3);
  	AddEditControlToEditQend(eq,&ec,ma);
  }
  else
  {
  	ConstructEditControl(&ec,ECT_CURSOR_STAY,0x40,ws_search,20);
  	AddEditControlToEditQend(eq,&ec,ma);
  }
  patch_header(&ed1_hdr);
  patch_input(&ed1_desc); 
  return CreateInputTextDialog(&ed1_desc,pHeader,eq,1,0);
}

void soft_key(char bFind)
{
  WSHDR *wsl = AllocWS(16);
  WSHDR *wsr = AllocWS(16);
#ifdef MENU_CN
   wsprintf(wsl,_percent_t, "菜单");
  if( bFind )
  	wsprintf(wsr,_percent_t, "查找");
  else
  	wsprintf(wsr,_percent_t, "退出");
#else
  wsprintf(wsl, "Menu");
  if( bFind )
  	  wsprintf(wsr, "Find");
  else
  	  wsprintf(wsr, "Exit");
#endif
  //DrawRectangle(0,screenh-GetFontYSIZE(FONT_MEDIUM)-2,screenw,screenh,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
  DrawString(wsl,2,screenh-GetFontYSIZE(sk_font)-2,screenw,screenh,sk_font,32,sk_color,GetPaletteAdrByColorIndex(23)); 
  DrawString(wsr,screenw-get_string_width(wsr,sk_font)-4,screenh-GetFontYSIZE(sk_font)-2,screenw,screenh,sk_font,32,sk_color,GetPaletteAdrByColorIndex(23)); 
  FreeWS(wsl);
  FreeWS(wsr);
}

int number_judge(int min,int max,int num)  //判断num是否超值 
{
  if(num<min){
   return (max);
  }
  /*
  if(num==max+1){
   return(min);
  }
  */
  else if(num>max){
     return(min);
  }
 else return(num);
}

void lgp(void)
{
  WSHDR *ws = AllocWS(256);
  soft_key(1);
  num=number_judge(0,max_lpg_num,num);
  for(int i=0;i<3;i++)
  {
      wsprintf(ws, "LGP_ID: %4d %4X H\n%t",num+i,num+i,num+i);
      DrawString(ws,5,YDISP+i*(screenh-YDISP)/3,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23));
  }
  FreeWS(ws);
}


void keycode(int code)
{
  WSHDR *ws = AllocWS(64);
  WSHDR *wsk = AllocWS(64);
  WSHDR *wsc = AllocWS(16); 
  WSHDR *wst=AllocWS(16);
  WSHDR *wsh=AllocWS(16);
  switch(code)
  {
   case '0' : wsprintf(wsc,"   0");  break;
   case '1' : wsprintf(wsc,"   1");  break;
   case '2' : wsprintf(wsc,"   2");  break;
   case '3' : wsprintf(wsc,"   3");  break;
   case '4' : wsprintf(wsc,"   4");  break;
   case '5' : wsprintf(wsc,"   5");  break;
   case '6' : wsprintf(wsc,"   6");  break;
   case '7' : wsprintf(wsc,"   7");  break;
   case '8' : wsprintf(wsc,"   8");  break;
   case '9' : wsprintf(wsc,"   9");  break;
   case '*' : wsprintf(wsc,"   *");  break;
   case '#' : wsprintf(wsc,"   #");  break;
#ifdef MENU_CN
   #ifdef NEWSGOLD
   case 0x01 : wsprintf(wsc,_percent_t,"左软键");  break;
   case 0x04 : wsprintf(wsc,_percent_t,"右软键");  break;
   case 0x0B : wsprintf(wsc,_percent_t,"绿键");  break;
   case 0x0C : wsprintf(wsc,_percent_t,"红键");  break;
   case 0x0D : wsprintf(wsc,_percent_t,"音量+");  break;
   case 0x0E : wsprintf(wsc,_percent_t,"音量-");  break;
   case 0x3B : wsprintf(wsc,_percent_t,"摇杆上");  break;
   case 0x3C : wsprintf(wsc,_percent_t,"摇杆下");  break;
   case 0x3D : wsprintf(wsc,_percent_t,"摇杆左");  break;
   case 0x3E : wsprintf(wsc,_percent_t,"摇杆右");  break;
   case 0x1A : wsprintf(wsc,_percent_t,"摇杆中");  break;
#ifdef ELKA
   case 0x15 : wsprintf(wsc,_percent_t,"直接拨打键");  break;
#else   
   case 0x15 : wsprintf(wsc,_percent_t,"播放器键");  break;
#endif
   case 0x11 : wsprintf(wsc,_percent_t,"上网键");  break;
   case 0x14 : wsprintf(wsc,_percent_t,"照相键");  break;
#else
   case 0x01 : wsprintf(wsc,_percent_t,"左软键");  break;
   case 0x04 : wsprintf(wsc,_percent_t,"右软键");  break;
   case 0x0B : wsprintf(wsc,_percent_t,"绿键");  break;
   case 0x0C : wsprintf(wsc,_percent_t,"红键");  break;
#ifdef X75
   case 0x14 : wsprintf(wsc,_percent_t,"音量+");  break;
   case 0x15 : wsprintf(wsc,_percent_t,"音量-");  break;
#else
   case 0x0D : wsprintf(wsc,_percent_t,"音量+");  break;
   case 0x0E : wsprintf(wsc,_percent_t,"音量-");  break;
#endif
   case 0x3B : wsprintf(wsc,_percent_t,"摇杆上");  break;
   case 0x3C : wsprintf(wsc,_percent_t,"摇杆下");  break;
   case 0x3D : wsprintf(wsc,_percent_t,"摇杆左");  break;
   case 0x3E : wsprintf(wsc,_percent_t,"摇杆右");  break;
   case 0x1A : wsprintf(wsc,_percent_t,"摇杆中");  break;
   case 0x11 : wsprintf(wsc,_percent_t,"上网键");  break;
#endif
#else
#ifdef NEWSGOLD
   case 0x01 : wsprintf(wsc,"LEFT_SOFT");  break;
   case 0x04 : wsprintf(wsc,"RIGHT_SOFT");  break;
   case 0x0B : wsprintf(wsc,"GREEN_BUTTON");  break;
   case 0x0C : wsprintf(wsc,"RED_BUTTON");  break;
   case 0x0D : wsprintf(wsc,"VOL_UP_BUTTON");  break;
   case 0x0E : wsprintf(wsc,"VOL_DOWN_BUTTON");  break;
   case 0x3B : wsprintf(wsc,"UP_BUTTON");  break;
   case 0x3C : wsprintf(wsc,"DOWN_BUTTON");  break;
   case 0x3D : wsprintf(wsc,"LEFT_BUTTON");  break;
   case 0x3E : wsprintf(wsc,"RIGHT_BUTTON");  break;
   case 0x1A : wsprintf(wsc,"ENTER_BUTTON");  break;
#ifdef ELKA
   case 0x15 : wsprintf(wsc,"POC_BUTTON");  break;
#else   
   case 0x15 : wsprintf(wsc,"PLAY_BUTTON");  break;
#endif
   case 0x11 : wsprintf(wsc,"INTERNET_BUTTON");  break;
   case 0x14 : wsprintf(wsc,"CAMERA_BUTTON");  break;
#else
   case 0x01 : wsprintf(wsc,"LEFT_SOFT");  break;
   case 0x04 : wsprintf(wsc,"RIGHT_SOFT");  break;
   case 0x0B : wsprintf(wsc,"GREEN_BUTTON");  break;
   case 0x0C : wsprintf(wsc,"RED_BUTTON");  break;
#ifdef X75
   case 0x14 : wsprintf(wsc,"VOL_UP_BUTTON");  break;
   case 0x15 : wsprintf(wsc,"VOL_DOWN_BUTTON");  break;
#else
   case 0x0D : wsprintf(wsc,"VOL_UP_BUTTON");  break;
   case 0x0E : wsprintf(wsc,"VOL_DOWN_BUTTON");  break;
#endif
   case 0x3B : wsprintf(wsc,"UP_BUTTON");  break;
   case 0x3C : wsprintf(wsc,"DOWN_BUTTON");  break;
   case 0x3D : wsprintf(wsc,"LEFT_BUTTON");  break;
   case 0x3E : wsprintf(wsc,"RIGHT_BUTTON");  break;
   case 0x1A : wsprintf(wsc,"ENTER_BUTTON");  break;
   case 0x11 : wsprintf(wsc,"INTERNET_BUTTON");  break;
#endif
#endif
  }
#ifdef MENU_CN
  wsprintf(wsh, _percent_t,"*键值测试*");
  wsprintf(ws, _percent_t,"长按左软键返回菜单\n");
  wsprintf(wst,_percent_t,"按键: "); 
  wsprintf(wsk,"%t%.2d  %.2X H","键值: ",code,code);
#else
  wsprintf(wsh, "*KeyCode*");
  wsprintf(ws, "Please long press\nLEFT_SOFT\nback to Menu.\n");
  wsprintf(wst,"Key: "); 
  wsprintf(wsk, "Keycode: %.2d  %.2X H",code,code);
#endif
 
  int h_len=get_string_width(wst,main_font);
  
  DrawRectangle(0,0,screenw,screenh,0,GetPaletteAdrByColorIndex(1),main_bg_color);
  DrawString(wsh,5,0,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23)); 
  DrawString(ws,5,screenh/7,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23)); 
  DrawString(wst,5,screenh/3,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23));
  DrawString(wsc,5+h_len,screenh/3,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23));
  DrawString(wsk,5,screenh/2,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23));
  
  FreeWS(wsh);
  FreeWS(ws);
  FreeWS(wsk);
  FreeWS(wsc);
  FreeWS(wst);
}

void pic()
{ 
  int i,max_pic_num;
  WSHDR *ws = AllocWS(50);
  WSHDR *wsr = AllocWS(50);

  for(i=0;!GetImgWidth(max_image_num-i);i++); //寻找末尾图片
  max_pic_num=max_image_num-i;//max=max_image_num
  num=number_judge(0,max_pic_num,num);
  if(num!=max_pic_num && GetImgWidth(num)==255 && GetImgHeight(num)==255) //跳过所有255 x 255的空白图片  
  {
    if(direct==0)//往回找
    {
    for(i=0;GetImgWidth(num-i)==255;i++);
    num-=i;
    }
    else//往前找
    {
    for(i=0;GetImgWidth(num+i)==255&&(num+i)!=max_pic_num;i++);
    num+=i;
    }
  } 
  int w=GetImgWidth(num);
  int h=GetImgHeight(num);
#ifdef MENU_CN
 wsprintf(ws,"%t%4d %3X H\n%t%3dx%d","图片ID: ",num,num,"大小: ",w,h); 
 wsprintf(wsr,_percent_t,"没有该图片!");
#else
 wsprintf(ws, "Pic_ID:%4d %3X H\nSize: %3dx%d",num,num,w,h); 
 wsprintf(wsr, "No Such Picture!");
#endif

  if(w)
  {
    DrawRoundedFrame(screenw/2-w/2-1,screenh/2-h/2-1,screenw/2+w/2+1,screenh/2+h/2+1,0,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
    DrawImg(screenw/2-w/2,screenh/2-h/2,num);
    //DrawRoundedFrame(screenw/2-w/2-1,(screenh+GetFontYSIZE(main_font)+2)/2-h/2-1,screenw/2+w/2+1,(screenh+GetFontYSIZE(main_font)+2)/2+h/2+1,0,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
    //DrawImg(screenw/2-w/2,(screenh+GetFontYSIZE(main_font)+2)/2-h/2,num);
  }
  if(!w || (w==255 && h==255))
  {
   DrawString(wsr,0,(screenh+2*GetFontYSIZE(main_font)+2)/2-GetFontYSIZE(main_font)/2,screenw,screenh,main_font,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  }
  soft_key(1);//图片不会挡住菜单
  DrawString(ws,5,0,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23));//图片不会挡住文字
  FreeWS(ws);
  FreeWS(wsr);
}

void font()
{
  int font_max;
  //char test_str[]="Test String 123";
  #ifdef NEWSGOLD
  #ifdef ELKA
  font_max=11;
  #else
  font_max=16;
  #endif
  #else
  font_max=10;
  #endif
  WSHDR *ws = AllocWS(64);
  WSHDR *wsl = AllocWS(32);
  WSHDR *wsh=AllocWS(16);
  soft_key(0);
  num=number_judge(0,font_max,num);
 #ifdef MENU_CN
  wsprintf(wsh,_percent_t,"*字体查看*");
  wsprintf(wsl,"%t%2d","字体大小: ",num);
#else
  wsprintf(wsh,"*Font*");
  wsprintf(wsl,"Font Size: %2d",num);
#endif
  
  DrawString(wsh,5,0,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23)); 
  DrawString(wsl,5,screenh/4,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23)); 
#ifdef MENU_CN
  wsprintf(ws,_percent_t,test_string);
#else
  utf8_2ws(ws,test_string,strlen(test_string));
#endif
  DrawString(ws,5,screenh/3+GetFontYSIZE(main_font)+3,screenw,screenh,num,32,main_text_color,GetPaletteAdrByColorIndex(23)); 
 
  FreeWS(wsl);
  FreeWS(ws);
  FreeWS(wsh);
}

void status(void)
{
  WSHDR *wsh = AllocWS(16);
  RAMNET *net=RamNet();
  int temp=GetAkku(1,3)-0xAAA+15;
  int volt=GetAkku(0,9);
  unsigned int err;
  int t_4=GetTotalFlexSpace(4,&err)/1024;
  int f_4=GetFreeFlexSpace(4,&err)/1024;
  #ifdef NEWSGOLD
  #ifdef ELKA
  char model[]="ELKA";
  #else
  char model[]="NewSGold";
  #endif
  #else
  char model[]="SGOLD";
  #endif
  DrawRectangle(0,0,screenw,screenh,0,GetPaletteAdrByColorIndex(1),main_bg_color);
  soft_key(0);
  GUI *igui=GetTopGUI();
#ifdef MENU_CN
  wsprintf(wsh,_percent_t,"*系统信息*");
  //gbprintf(ws_info,"机型: %s\n信号: %c%ddB\n温度: %d.%d℃\n基站: %d-%d:%d\nC1: %d C2: %d\n电压:%d.%02dV 电量: %02d%%\nCL: %d%% CC: %dMHz\n剩余内存: %uKb",model,(net->ch_number>=255)?'=':'-',net->power,temp/10,temp%10,net->ci,net->lac,net->ch_number,net->c1,net->c2,volt/1000,(volt%1000)/10,*RamCap(),GetCPULoad(),GetCPUClock(),GetFreeRamAvail()/1024);
  wsprintf(ws_info,"%t%s\n%t%c%ddB\n%t%d.%d%t\n%t%d-%d:%d\nC1: %d C2: %d\n%t%d.%02dV %t%02d%%\nCL: %d%% CC: %dMHz\n%t%uKb","机型: ",model,"信号: ",(net->ch_number>=255)?'=':'-',net->power,"温度: ",temp/10,temp%10,"℃","基站: ",net->ci,net->lac,net->ch_number,net->c1,net->c2,"电压:",volt/1000,(volt%1000)/10,"电量: ",*RamCap(),GetCPULoad(),GetCPUClock(),"剩余内存: ",GetFreeRamAvail()/1024);
#else
  wsprintf(wsh,"*SystemInfo*");
  wsprintf(ws_info,"Phone: %s\nNet: %c%ddB\nT: %d.%d℃nBts: %d-%d:%d\nC1: %d C2: %d\nV:%d.%02dV Cap: %02d%%\nCL: %d%% CC: %dMHz\nFreeRam: %uKb",model,(net->ch_number>=255)?'=':'-',net->power,temp/10,temp%10,net->ci,net->lac,net->ch_number,net->c1,net->c2,volt/1000,(volt%1000)/10,*RamCap(),GetCPULoad(),GetCPUClock(),GetFreeRamAvail()/1024);
#endif
  DrawString(wsh,5,0,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23)); 
  DrawString(ws_info,5,GetFontYSIZE(main_font),screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23)); 
  wsprintf(ws_info,"0: %dKb / %dKb\n1: %dKb / %dKb\n2: %dKb / %dKb\n4: %dKB / %dKB",GetFreeFlexSpace(0,&err)/1024,GetTotalFlexSpace(0,&err)/1024,GetFreeFlexSpace(1,&err)/1024,GetTotalFlexSpace(1,&err)/1024,GetFreeFlexSpace(2,&err)/1024,GetTotalFlexSpace(2,&err)/1024,f_4,t_4);
  DrawString(ws_info,5,GetFontYSIZE(main_font)*9,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23)); 
  FreeWS(wsh);
}


void TimerProc(void)
{
  if (!IsGuiOnTop(MAINGUI_ID)) status_flag=0;
  if(status_flag) status();
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&my_ipc);
}

void rgb24()
{
  WSHDR *wsh = AllocWS(16);
  WSHDR *ws = AllocWS(32);
  soft_key(0);
  num=number_judge(0,23,num);
#ifdef MENU_CN
  wsprintf(wsh,_percent_t,"*RGB颜色*");
  wsprintf(ws,"%t%2d","RGB24颜色编号: ",num);
#else
  wsprintf(wsh,"*RGB24*");
   wsprintf(ws,"RGB24 COLOR ID: %2d",num);
#endif
  DrawString(wsh,5,0,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23)); 
  DrawString(ws,5,screenh/9,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23)); 
  DrawRoundedFrame(5,screenh/4,screenw-5,screenh-GetFontYSIZE(FONT_MEDIUM)-screenh/12,0,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(num));
  FreeWS(ws);
  FreeWS(wsh);
}

void sound()
{
  WSHDR *ws = AllocWS(32);
  WSHDR *wsh = AllocWS(16);
  WSHDR *status = AllocWS(16);
  soft_key(0);
  num=number_judge(0, max_sound_num, num);
#ifdef MENU_CN
   wsprintf(wsh,_percent_t,"*内置铃声*");
   wsprintf(ws,"%t%3d","铃声编号: ",num);
   if(sound_flag)wsprintf(status, _percent_t,"状态: 开启");
   else wsprintf(status,_percent_t, "状态: 关闭");
#else
 wsprintf(wsh, "*Sound*");
   wsprintf(ws, "Sound Num: %3d",num);
   if(sound_flag)wsprintf(status, "Status: On");
else wsprintf(status, "Status: Off");
#endif
  DrawString(wsh,5,0,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23)); 
  DrawString(status,5,screenh/2,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23)); 
  DrawString(ws,5,screenh/4,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23)); 
  if(sound_flag)PlaySound(0,0,0,num,0);
  FreeWS(ws);
  FreeWS(wsh);
  FreeWS(status);
}

void text_attribute(void)
{
  WSHDR *wsh = AllocWS(128);
  WSHDR *ws = AllocWS(32);
  int i;
  WSHDR *wst=AllocWS(8);
  wsprintf(wst,"256: ");
  int h_len=get_string_width(wst,main_font);
  FreeWS(wst);
  DrawRectangle(0,0,screenw,screenh,0,GetPaletteAdrByColorIndex(1),main_bg_color);
  soft_key(0);
#ifdef MENU_CN
  wsprintf(wsh,_percent_t,"*文本属性* \n\n    1:\n    2:\n    4:\n    8:\n  16:\n  32:\n  64:\n128:\n256:");
  wsprintf(ws,_percent_t,"中文Ab12");
#else
  wsprintf(wsh, "*Text attribute* \n\n    1:\n    2:\n    4:\n    8:\n  16:\n  32:\n  64:\n128:\n256:");
  wsprintf(ws,"Test string");
#endif 
  DrawString(wsh,5,0,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23));

  for(i=0;i<9;i++)
  {
    DrawString(ws,h_len+7,GetFontYSIZE(main_font)*(i+1)+15,screenw,screenh,main_font,pow(2,i),main_text_color,t_a_b_color);
  }
  FreeWS(ws);
  FreeWS(wsh);
}

void vibra(void)
{
  WSHDR *ws = AllocWS(64);
  WSHDR *wsh = AllocWS(16);
  WSHDR *status = AllocWS(16);
  soft_key(0);
  num=number_judge(0,100,num);
    #ifdef MENU_CN
   wsprintf(wsh,_percent_t, "*振动测试*");
   wsprintf(ws, "%t%3d%%","振动强度: ",num);
   if(sound_flag)wsprintf(status,_percent_t, "状态: 开启");
   else wsprintf(status, _percent_t,"状态: 关闭");
#else
  wsprintf(wsh, "*VibraTest*");
  wsprintf(ws, "Vibra Power:%3d%%",num);
  if(vibra_flag)wsprintf(status, "Status: On");
  else wsprintf(status, "Status: Off");
#endif
	DrawString(wsh,5,0,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23)); 
  if (vibra_flag)SetVibration(num);
  else SetVibration(0);   
  DrawString(status,5,screenh/2,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23)); 
  DrawString(ws,5,screenh/4,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23)); 
  FreeWS(ws);
  FreeWS(wsh);
  FreeWS(status);
}
  
void light(void)
{
  WSHDR *ws = AllocWS(64);
  WSHDR *wsh = AllocWS(16);
  WSHDR *status = AllocWS(20);  
  soft_key(0);
  num=number_judge(0,100,num);
#ifdef MENU_CN
  char *zh_str[]={"全开","显示屏","键盘灯","全关"};
  wsprintf(wsh,_percent_t,"*亮度测试*");//标题
  wsprintf(ws,"%t%3d%%","亮度: ",num);
  wsprintf(status,"%t%t","状态: ",zh_str[light_flag]);
#else
  char *en_str[]={"All","Display","Keyboard","Do Nothing"};
  wsprintf(wsh, "*LightTest*");
  wsprintf(ws, "Light:%3d%%", num);
  wsprintf(status,"Status: %s",en_str[light_flag]);
#endif
  DrawString(wsh,5,0,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23));
  switch(light_flag)
  {
      case 0:
        SetIllumination(0, 1, num, 0);
        SetIllumination(1, 1, num, 0);
        break;
      case 1:
        SetIllumination(0, 1, num, 0);
        break;
      case 2:
        SetIllumination(1, 1, num, 0);
        break;
      case 3:
        break;
  }
  DrawString(status,5,screenh/5,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23));
  DrawString(ws,5,screenh/9,screenw,screenh,main_font,32,main_text_color,GetPaletteAdrByColorIndex(23));
  DrawRoundedFrame(5,screenh/3,screenw-5,screenh-GetFontYSIZE(FONT_MEDIUM)-screenh/12,0,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(0));
  FreeWS(ws);
  FreeWS(wsh);
  FreeWS(status);
}


void onRedraw(MAIN_GUI *data)
{
#ifdef ELKA
  DisableIconBar(1);
#endif
  DrawRectangle(0,0,screenw,screenh,0,GetPaletteAdrByColorIndex(1),main_bg_color);
  if (flag!=4)
  {
    status_flag=0;
  }
  switch(flag)
  {
    case 0: lgp(); break;
    case 1: pic(); break;
    case 2: keycode(ENTER_BUTTON); break;
    case 3: font(); break;
    case 4: status(); status_flag=1; break;
    case 5: rgb24(); break;
    case 6: sound(); break;
    case 7: text_attribute(); break;
    case 8: vibra();break;
    case 9: light();break;
    default : flag=0; break;
  }
}


void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  DisableIDLETMR();
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

void create_num(int numx)
{
  num=num*10+numx;
  REDRAW();
}

void back_to_menu(void)
{
  status_flag=0;
  GeneralFuncF1(1); 
}

void begin_search(int key)
{
          if (flag==0 || flag==1)
          {
          	int i,j,step;
          	char bFound=0;
         		step = key==VOL_UP_BUTTON ? -1 : 1;
          	if( flag )
          	{
          		int w,h;
          		for(i=num+step; i>=0 && i<max_image_num; i+=step)
          		{
          			w=GetImgWidth(i);
          			h=GetImgHeight(i);
          			if((imagew == 0 || imagew == w) && (imageh == 0 || imageh == h))
          			{
          				bFound = 1;
          				num = i;
          				break;
          			}		  				
          		}
          	}
          	else
          	{
          		WSHDR *ws = AllocWS(256);
          		for(i=num+step; i>=0 && i<max_lpg_num; i+=step)
          		{
          			wsprintf(ws, "%t", i);
          			for(j=1; j<=ws_search->wsbody[0]; j++)
          			{
          				if(j > ws->wsbody[0] || ws_search->wsbody[j] != ws->wsbody[j])
          					break;
          			}
          			if( j > ws_search->wsbody[0] )
          			{
          				bFound = 1;
          				num = i;
          				break;
          			} 
          		}
          		FreeWS( ws );
          	}
          	if( !bFound )
          	{
/*          		if (key==VOL_DOWN_BUTTON)
          			num = 0;
          		else
          			num = flag ? max_image_num : max_lpg_num;*/
#ifdef MENU_CN
          		ShowMSG(1, (int)"未找到?");
#else
                        ShowMSG(1, (int)"Not Found?");
#endif
          	}
          }
          REDRAW();
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  if (flag==2)
  {
    keycode(msg->gbsmsg->submess);
    if (msg->gbsmsg->submess==LEFT_SOFT)
    {
      if (msg->gbsmsg->msg==LONG_PRESS)
        back_to_menu();
    }
  }
  else
  {
    
    if (msg->gbsmsg->msg==KEY_UP)                        
    {                                                    
      switch(msg->gbsmsg->submess)                       
      {                                                  
        case '0':
          if(flag!=7||flag!=4) create_num(0); break;                  
        case '1':
          if(flag!=7||flag!=4) create_num(1); break;                  
        case '2': 
          if(flag!=7||flag!=4) create_num(2); break;                  
        case '3': 
          if(flag!=7||flag!=4) create_num(3); break;                  
        case '4': 
          if(flag!=7||flag!=4) create_num(4); break;                  
        case '5': 
          if(flag!=7||flag!=4) create_num(5); break;                  
        case '6': 
          if(flag!=7||flag!=4) create_num(6); break;                  
        case '7': 
          if(flag!=7||flag!=4) create_num(7); break;                  
        case '8': 
          if(flag!=7||flag!=4) create_num(8); break;                  
        case '9': 
          if(flag!=7||flag!=4) create_num(9); break;  
        case '*': 
          if(flag!=7||flag!=4) num=0; REDRAW(); break;  
        case '#': 
          if(flag!=7||flag!=4) num=num/10; REDRAW(); break;   
        case UP_BUTTON: 
          if(flag!=7||flag!=4) num=num+1;direct=1; REDRAW(); break;      
        case DOWN_BUTTON: 
          if(flag!=7||flag!=4) num=num-1;direct=0;REDRAW(); break;  
        case RIGHT_BUTTON: 
          if(flag!=7||flag!=4) 
        if(flag!=0)num=num+1;else num=num+3;direct=1; REDRAW(); break;   
        case LEFT_BUTTON: 
          if(flag!=7||flag!=4) 
		if(flag!=0)num=num-1;else num=num-3;direct=0; REDRAW(); break; 
			  case VOL_UP_BUTTON:
			  case VOL_DOWN_BUTTON:
			  	begin_search( msg->gbsmsg->submess );
			  	break;
        case ENTER_BUTTON:
          if(flag==8)
          {
            vibra_flag=!vibra_flag;
          }
          if(flag==9)
          {
            if(light_flag==3)
              light_flag=0;
            else
              light_flag++;
          }
		  if(flag==6){//铃声
		  sound_flag=!sound_flag;
		  }
          REDRAW();
          break; 
        case RIGHT_SOFT: 
          {
            if (vibra_flag) SetVibration(0);
            if (flag==0 || flag==1)
            	SEARCH_CSM_ID=create_ed(&ed1_hdr);
            else
            	CloseCSM(MAINCSM_ID); 
            break;  
          }
        case LEFT_SOFT: 
          {
            if (vibra_flag) SetVibration(0);
            back_to_menu(); 
            break; 
          } 
      }  
    }  
    if (msg->gbsmsg->msg==LONG_PRESS)  
    {                                                    
      switch(msg->gbsmsg->submess)  
      {                                                  
        case UP_BUTTON: num=num+1;direct=1; REDRAW(); break;      
        case DOWN_BUTTON: num=num-1;direct=0; REDRAW(); break;    
        case RIGHT_BUTTON: if(flag!=0)num=num+1;else num=num+3;direct=1; REDRAW(); break;   
        case LEFT_BUTTON: if(flag!=0)num=num-1;else num=num-3;direct=0; REDRAW(); break;    
      }  
    }
  }
  return(0);
}

int method8(void){return(0);}
int method9(void){return(0);}

const void * const gui_methods[11]={
	(void *)onRedraw,	//Redraw
	(void *)onCreate,	//Create
	(void *)onClose,	//Close
	(void *)onFocus,	//Focus
	(void *)onUnfocus,	//Unfocus
	(void *)OnKey,		//OnKey
	0,
	(void *)kill_data,	//Destroy
	(void *)method8,
	(void *)method9,
	0
};

const RECT Canvas={0,0,0,0};

void startgui(void)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
	zeromem(main_gui,sizeof(MAIN_GUI));	
	patch_rect((RECT*)&Canvas,0,0,screenw-1,screenh-1);
	main_gui->gui.canvas=(void *)(&Canvas);
	main_gui->gui.flag30=2;
	main_gui->gui.methods=(void *)gui_methods;
	main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();	
	MAINGUI_ID=CreateGUI(main_gui);
}



int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
#ifdef MENU_CN
	  ShowMSG(1,(int)"西机助手设置已经更新!");
#else
      ShowMSG(1,(int)"SieHelpMan config updated!");
#endif
      InitConfig();
    }
  }
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==SEARCH_CSM_ID))
  {
  	if ((int)msg->data1==1 && wstrlen(ws_info) > 0) // 确认保存查找条件 
  	{
  		if ( flag )
  		{
  			char szTemp[9];
  			ws_2str(ws_info, szTemp, 7);
  			sscanf(szTemp, "%d %d", &imagew, &imageh);
  		}
  		else
  		{
  			wstrcpy(ws_search, ws_info);
  		}
  		begin_search( VOL_DOWN_BUTTON );
  	}
  }
  
  if (msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
      {
        switch (msg->submess)
        {
        case IPC_UPDATE_STAT:
#ifdef NEWSGOLD
          if (!getCpuUsedTime_if_ena())
          {
            StartCpuUsageCount();
          }
#endif
          GBS_StartTimerProc(&mytmr, sys_re_t*TMR_SECOND/10, TimerProc);
        }
      }
    }
    
  }
  return(1);
}


const int menusoftkeys[]={0,1,2};
SOFTKEY_DESC menu_sk[]=
{
#ifdef MENU_CN
  {0x0018,0x0000,(int)"选择"},
  {0x0001,0x0000,(int)"退出"},
#else
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Exit"},
#endif
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

#define ITEMS_N 12


#ifdef MENU_CN

MENUITEM_DESC menu_items[ITEMS_N]=
{
  {NULL,(int)"系统信息",     LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"内置图片",        LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"LGP查看",         LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"内置铃声",          LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"字体查看",           LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"文本属性",       LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"RGB颜色",          LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"振动强度",     LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"亮度测试",          LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"键值测试",        LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"设置选项",        LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"关于",          LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};
#else

MENUITEM_DESC menu_items[ITEMS_N]=
{
  {NULL,(int)"SystemInfo",     LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"Picture",        LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"LGP_ID",         LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"Sound",          LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"Font",           LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"TextAttr",       LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"RGB24",          LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"VibraPower",     LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"Light",          LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"KeyCode",        LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"Options",        LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"About",          LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};
#endif

void lgp_gui(GUI *data)
{
  flag=0;
  startgui();
}

void pic_gui(GUI *data)
{
  flag=1;
  startgui();
}

void keycode_gui(GUI *data)
{
  flag=2;
  startgui();
}

void font_gui(GUI *data)
{
  flag=3;
  startgui();
}

void status_gui(GUI *data)
{
  flag=4;
  startgui();
}

void rgb24_gui(GUI *data)
{
  flag=5;
  startgui();
}

void sound_gui(GUI *data)
{
  flag=6;
  startgui();
}

void text_attr_gui(GUI *data)
{
  flag=7;
  startgui();
}

void vibra_gui(GUI *data)
{
  flag=8;
  startgui();
}

void light_gui(GUI *data)
{
  flag=9;
  startgui();
}

void options(GUI *data)
{
  extern const char *successed_config_filename;
  WSHDR *ws;
  ws=AllocWS(128);
  str_2ws(ws,successed_config_filename,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
}

void about(GUI *data)
{
#ifdef MENU_CN
  ShowMSG(1, (int)"西机助手V0.61GB  (c) 2008\nbinghelingxi\nOmo DaiXM\nalong1976");
#else
  ShowMSG(1, (int)"SieHelpManV0.61  (c) 2008\nbinghelingxi\nOmo DaiXM\nalong1976");
#endif
}

const MENUPROCS_DESC menu_hndls[ITEMS_N]=
{
  status_gui,
  pic_gui,
  lgp_gui,
  sound_gui,
  font_gui,
  text_attr_gui,
  rgb24_gui,
  vibra_gui,
  light_gui,
  keycode_gui,
  options,
  about,
};

int menu_onkey(void *data, GUI_MSG *msg)
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
      case RIGHT_SOFT : CloseCSM(MAINCSM_ID); break;
      //case LEFT_SOFT : GBS_SendMessage(MMI_CEPID,KEY_UP,ENTER_BUTTON); break;
    }
  }
  return (0);
}

void mm_menu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}
#ifdef MENU_CN
HEADER_DESC mm_menuhdr={0,0,0,0,NULL,(int)"西机助手V0.61GB",LGP_NULL};
#else
HEADER_DESC mm_menuhdr={0,0,0,0,NULL,(int)"SieHelpManV0.61",LGP_NULL};
#endif

const MENU_DESC mm_menu=
{
  8,menu_onkey,NULL,NULL,
  menusoftkeys,
  &menu_skt,
  0,
  NULL,
  menu_items,   //Items
  menu_hndls,   //Procs
  ITEMS_N   //n
};

void maincsm_oncreate(CSM_RAM *data)
{
	imagew=imageh=0;
  screenw=ScreenW();
  screenh=ScreenH();
  vibra_flag=default_vibra_sta;
  light_flag=default_light_sta;
  sound_flag=default_sound_sta;
  ws_info = AllocWS(256);
  ws_search = AllocWS(20);
  CutWSTR(ws_search, 0);
  MAIN_CSM *csm=(MAIN_CSM *)data;
  csm->csm.state=0;
  csm->csm.unk1=0;
  patch_header(&mm_menuhdr);
  csm->gui_id=CreateMenu(0,0,&mm_menu,&mm_menuhdr,0,ITEMS_N,0,0);
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&my_ipc);
}


void Killer(void)
{
  extern void *ELF_BEGIN;
  GBS_DelTimer(&mytmr);
  FreeWS(ws_info);
  FreeWS(ws_search);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
}

const int minus11=-11;
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
#ifdef MENU_CN
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),_percent_t,ipc_my_name);
#else
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name), ipc_my_name);
#endif
}

int main()
{
  char dummy[sizeof(MAIN_CSM)];
  InitConfig();
  UpdateCSMname();
  LockSched();
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  return 0;
}

