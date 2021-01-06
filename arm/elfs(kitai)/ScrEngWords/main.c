#include "../inc/swilib.h"
#include "lang.h"
#include "conf_loader.h"

#define buf_size 256
#define words_size 256
#define meaning_size 256
int fp;
int file_size=0;
char *buf;
char words[words_size];
char meaning[meaning_size];
WSHDR *ws_word;
WSHDR *ws_meaning;
int is_show_needed=0; //用于标识是否需要更新显示的数据(到了待机界面时更新一次)
int word_scroll_pos=1;
int meaning_scroll_pos=1;
int is_load_data_secs=0; //标识是否顺利打开数据库文件
const char frm_color[4]={0, 0, 0, 0};

////////////////////
//config
extern const unsigned int pos_x;
extern const unsigned int pos_y;
extern const unsigned int width;
extern const unsigned int font;
extern const unsigned int txt_attr;
extern const int enalock;
extern const char word_color[4];
extern const char word_frm_color[4];
extern const char rnd_frm_color[4];
extern const char datafile_path[128];

typedef struct
{
	CSM_RAM csm;
}MAIN_CSM;

extern kill_data(void *p, void (*func_p)(void *));


#pragma inline=forced
int toupper(int c)
{
	if ((c>='a')&&(c<='z'))
		c+='A'-'a';
	return(c);
}

#pragma inline
int strcmp_nocase(const char *s1, const char *s2)
{
	int i;
	int c;
	while(!(i=(c=toupper(*s1++))-toupper(*s2++)))
	{
		if(!c)
			break;
	}
	return i;
}



/**************简单随机算法*******************
使用FreeBSD5.3R+GCC3.4.2的产生随机数源码
再用系统实时时间的计算，使之变得更加复杂
**********************************************/
#define RAND_MAX        0x7fffffff

unsigned long rand_base=0;

void update_rand_base(void)//这个函数用系统时间来修改随机算法的基数
{
	TTime time;
	TDate date;
	GetDateTime(&date, &time);
	rand_base+=(time.sec)*(time.min)*(time.hour);
}

int do_rand(unsigned long *ctx)
{
	unsigned long hi, lo, x;
	if (*ctx==0)
		*ctx=123459876;
	hi=*ctx/127773;
	lo =*ctx%127773;
	x=16807*lo-2836*hi;
	if(x<0)
		x+=0x7fffffff;
	return ((*ctx=x)%((unsigned long)RAND_MAX+1));
}

int get_rand_fpos(void)
{
	int fs=file_size/32;
	int x=do_rand(&rand_base);
	int n=x%32;
	x%=fs;
	update_rand_base();
	return (fs*n+x);
}

int load_data(void)
{
	unsigned int err;
	if((fp=fopen(datafile_path, A_ReadOnly+A_BIN, P_READ, &err))<0)
	{
		is_load_data_secs=0;
		return 0;
	}
	is_load_data_secs=1;
	file_size=lseek(fp, 0, S_END, &err, &err);
	return 1;
}

void unload_data(void)
{
	unsigned int err;
	fclose(fp, &err);
}


int reload_data(void)
{
	unload_data();
	return (load_data());
}

void read_data(void)
{
	unsigned int err;
	if(is_load_data_secs)
	{
		lseek(fp, get_rand_fpos(), S_SET, &err, &err);
		int size=fread(fp, buf, buf_size, &err);
		if(size>=0)
			buf[size]='\0';
		lseek(fp, 0, S_SET, &err, &err);
		char *p=buf;
		while(*p)
		{
			if(*p++=='\n')
				break;
		}
		int i=0, c;
		while(c=*p++)
		{
			if(c==' ')
				break;
			words[i]=c;
			i++;
		}
		words[i]='\0';
		i=0;
		while(c=*p++)
		{
			if(c=='\n')
				break;
			meaning[i]=c;
			i++;
		}
		meaning[i]='\0';
	}
	else
	{
		strcpy(words, szOpenFileErr);
		strcpy(meaning, szOpenFileErr);
	}
	gb2ws(ws_word, words, words_size);
	gb2ws(ws_meaning, meaning, meaning_size);
}

void reconfig(void)
{
	InitConfig();
	reload_data();
}

void draw_main_screen(void)
{
	int fh=GetFontYSIZE(font);
	int word_width=Get_WS_width(ws_word, font);
	int meaning_width=Get_WS_width(ws_meaning, font);
	DrawScrollString(ws_word, pos_x+2, pos_y+2, pos_x+width-2, pos_y+fh+2, word_scroll_pos, font, txt_attr, word_color, word_frm_color);
	DrawScrollString(ws_meaning, pos_x+2, pos_y+fh+4, pos_x+width-2, pos_y+2*fh+4, meaning_scroll_pos, font, txt_attr, word_color, word_frm_color);
	if(word_width<=(width-4))
	{
		word_scroll_pos=1;
	}
	else
	{
		if((word_width-word_scroll_pos)<=width)
			word_scroll_pos=1;
		else
			word_scroll_pos+=10;
	}
	if(meaning_width<=(width-4))
	{
		meaning_scroll_pos=1;
	}
	else
	{
		if((meaning_width-meaning_scroll_pos)<=width)
			meaning_scroll_pos=1;
		else
			meaning_scroll_pos+=10;
	}
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
	if(msg->msg==MSG_RECONFIGURE_REQ)
	{
		extern const char *successed_config_filename;
		if(strcmp_nocase(successed_config_filename, (char *)msg->data0)==0)
		{
			ShowMSG(1, (int)LGP_UPDATE_CONFIG);
			reconfig();
		}
	}
	
#define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
	CSM_RAM *icsm;
	icsm=FindCSMbyID(CSM_root()->idle_id);
	if(icsm)
	{
		if(IsGuiOnTop(idlegui_id(icsm)))
		{
			GUI *igui=GetTopGUI();
			if(igui)
			{
#ifdef ELKA
				void *canvasdata = BuildCanvas();
				{
#else
				void *idata = GetDataOfItemByID(igui, 2);
				if(idata)
				{
					void *canvasdata=((void **)idata)[DISPLACE_OF_IDLECANVAS/4];
#endif
					if(IsUnlocked()||enalock)
					{
						if(is_show_needed==0)
							read_data();
						is_show_needed=1;
						int fh=GetFontYSIZE(font);
						DrawCanvas(canvasdata, pos_x, pos_y, pos_x+width, pos_y+2*fh+6, 1);
						DrawRoundedFrame(pos_x, pos_y, pos_x+width, pos_y+2*fh+6, 2, 2, 0, rnd_frm_color, frm_color);
						draw_main_screen();
					}
				}
#ifndef ELKA
				else
					is_show_needed=0;
#endif
			}
			else
				is_show_needed=0;
		}
		else
			is_show_needed=0;
	}
	else
		is_show_needed=0;
	return 1;
}

static void maincsm_oncreate(CSM_RAM *data)
{
	buf=malloc(buf_size);
	ws_word=AllocWS(words_size);
	ws_meaning=AllocWS(meaning_size);
	load_data();
	update_rand_base();
}

static void Killer(void)
{
	extern void *ELF_BEGIN;
	mfree(buf);
	FreeWS(ws_word);
	FreeWS(ws_meaning);
	unload_data();
	kill_data(&ELF_BEGIN, (void (*)(void *))mfree_adr());
}


static void maincsm_onclose(CSM_RAM *csm)
{
	SUBPROC((void *)Killer);
}


const int minius11=-11;
static unsigned short maincsm_name_body[140];
static const struct
{
	CSM_DESC maincsm;
	WSHDR maincsm_name;
}MAINCSM=
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
		&minius11
	},
	{
		maincsm_name_body,
		NAMECSM_MAGIC1,
		NAMECSM_MAGIC2,
		0,
		139
	}
};


static void UpdateCSMName(void)
{
	wsprintf((WSHDR *)(&MAINCSM.maincsm_name), "%t", ELF_NAME);
}	


int main(void)
{
	CSM_RAM *save_cmpc;
	char dummy[sizeof(MAIN_CSM)];
	InitConfig();
	UpdateCSMName();
	LockSched();
	save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
	CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
	CreateCSM(&MAINCSM.maincsm, dummy,0);
	CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
	UnlockSched();
	return 0;
}

