#include "../inc/swilib.h"
#include "lang.h"
#include "conf_loader.h"



typedef struct
{
	CSM_RAM csm;
}MAIN_CSM;

extern kill_data(void *p, void (*func_p)(void *));
extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

extern const unsigned int pos_x;
extern const unsigned int pos_y;
extern const unsigned int length;
extern const unsigned int font;
extern const char color[4];
extern const char frmcolor[4];
extern const unsigned int txt_attr;
extern const int ENA_LOCK;
extern const char frmmain_color[4];
extern const char frmbg_color[4];
extern const unsigned int xrnd;
extern const unsigned int yrnd;
extern const int style;
extern const unsigned int speed;
//extern const unsigned int wait_time;
extern const char CSMADR[];
extern const int show_gp;
extern const int show_ext;

WSHDR *ews;
//WSHDR *ews_2;
//WSHDR *temp;
//int drawname_needed=0;
int scroll_pos=1;
//GBSTMR mytmr;
//int is_tmr=0;
//int is_drawname=0;
char utf8_name[128];
char name_temp[128];
char name_temp_cmp[128];
int is_music_file=0;
int is_player_active=0;

const char percent_t[]="%t";

unsigned int playercsmid=0;
void *playercsmadr=NULL;


#define time_second 216
GBSTMR tmup;
int time=0;
//int is_playing=0;
#pragma swi_number=0x01F8
__swi __arm int GetPlayStatus(void);

WSHDR *ws_lrc;
//WSHDR *temp_lrc;
char *lrc_buf;
char lrc_path[128];
int is_no_lrc;
//GBSTMR lrctmr;
//int is_dlrc_tmr=0;
int scroll_pos_lrc=1;
extern const int ena_lrc;
extern const char lrc_dir_path[128];
extern const unsigned int lrc_font;
extern const char lrc_color[4];
extern const char lrc_frmcolor[4];
extern const unsigned int lrc_speed;
extern const unsigned int lrc_txt_attr;

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strncmp_nocase(const char *s1,const char *s2,unsigned int n)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))&&(--n)) if (!c) break;
  return(i);
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
//ad
//amr,imy,m4a,mfi,mid,mp3,srt,wav,

//vd
//mp4,3gp

//gf
//bmp,bmx,gif,jpeg,jpg,png,svg,wbmp

void getname(void)
{
	char *p=strrchr(name_temp, '.');
	if(p)
	{
		if(!strncmp_nocase(p, ".mp3", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".mp3");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".aac", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".aac");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".m4a", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".m4a");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".wav", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".wav");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".amr", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".amr");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".mid", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".mid");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".3gp", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".3gp");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".mp4", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".mp4");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".imy", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".imy");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".srt", 4))
		{
			is_music_file=1;
			//strcpy(&utf8_name[i], ".srt");
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".bmp", 4))
		{
			if(show_gp)
				is_music_file=1;
			else
				is_music_file=0;
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".jpg", 4))
		{
			if(show_gp)
				is_music_file=1;
			else
				is_music_file=0;
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".gif", 4))
		{
			if(show_gp)
				is_music_file=1;
			else
				is_music_file=0;
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".png", 4))
		{
			if(show_gp)
				is_music_file=1;
			else
				is_music_file=0;
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".jpeg", 5))
		{
			if(show_gp)
				is_music_file=1;
			else
				is_music_file=0;
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".bmx", 4))
		{
			if(show_gp)
				is_music_file=1;
			else
				is_music_file=0;
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".svg", 4))
		{
			if(show_gp)
				is_music_file=1;
			else
				is_music_file=0;
			goto if_show_ext;
		}
		if(!strncmp_nocase(p, ".wbmp", 4))
		{
			if(show_gp)
				is_music_file=1;
			else
				is_music_file=0;
			goto if_show_ext;
		}
	}
	else
		utf8_name[0]=0;
	
	is_music_file=0;
//gf
//bmp,bmx,gif,jpeg,jpg,png,svg,wbmp
if_show_ext:
	if(!show_ext)
		goto not_show_ext;
	strcpy(utf8_name, name_temp);
	goto end;
	
not_show_ext:
	strncpy(utf8_name, name_temp, p-name_temp);
	utf8_name[p-name_temp]=0;
	
end:
	str_2ws(ews, utf8_name, 128);
}

void RereadSettings(void)
{
	InitConfig();
	if(strlen((char *)CSMADR)==8)
		playercsmadr=(void *)strtoul(CSMADR,NULL,16);
}

int getMaxChars(unsigned short *wsbody, int len, int font) // 获取可显示的最大字符数 Unicode
{
	int ii,width=0;
	for(ii=0;ii<len;ii++)
	{
		width+=GetSymbolWidth(wsbody[ii], font);
		if (width>=length-4) break;
	}
	return ii;
}

void drawname_proc(void)
{
	int ws_width=Get_WS_width(ews, font);
	if((ws_width>=length-4)&&speed)
	{
		DrawScrollString(ews,pos_x+2,pos_y+2,pos_x+length-2,pos_y+GetFontYSIZE(font)+2,scroll_pos,font,txt_attr,color,frmcolor);
		if((ws_width-scroll_pos)<=(length-4))
			scroll_pos=1;
		else
			scroll_pos+=speed;
	}
	else
	{
		DrawString(ews,pos_x+2,pos_y+2,pos_x+length-2,pos_y+GetFontYSIZE(font)+2,font,txt_attr,color,frmcolor);
	}
}

void time_update_proc(void)
{
	if(is_player_active&&ena_lrc)
	{
		int status=GetPlayStatus();
		if(status==2)
			time++;
		else
			if(status==0)
				time=0;
	}
	GBS_StartTimerProc(&tmup,time_second,time_update_proc);
}



void draw_lrc_proc(void)
{
	int fh=GetFontYSIZE(font);
	int lrcfh=GetFontYSIZE(lrc_font);
	int ws_width=Get_WS_width(ws_lrc, lrc_font);
	if((ws_width>=length-4)&&lrc_speed)
	{
		DrawScrollString(ws_lrc,pos_x+2,pos_y+fh+4,pos_x+length-2,pos_y+fh+lrcfh+4,scroll_pos_lrc,lrc_font,lrc_txt_attr,lrc_color,lrc_frmcolor);
		if((ws_width-scroll_pos_lrc)<=(length-4))
			scroll_pos_lrc=1;
		else
			scroll_pos_lrc+=lrc_speed;
	}
	else
		DrawString(ws_lrc,pos_x+2,pos_y+fh+4,pos_x+length-2,pos_y+fh+lrcfh+4,lrc_font,lrc_txt_attr,lrc_color,lrc_frmcolor);
}

void drawlrc(void)
{
	if(is_no_lrc)
		goto end;
	char *p;
	char *pp;
	int c;
	char ch_time[16];
	sprintf(ch_time,"%02d:%02d",time/60,time%60);
	///////////////////
	
	p=strstr(lrc_buf,ch_time);
	if(p)
	{
		while(c=*p)
		{
			if(c=='\n')
				break;
			p++;
		}
		pp=p;
		while(c=*pp)
		{
			if(c==']')
			{
				pp++;
				break;
			}
			pp--;
		}
		int len=p-pp;
		if(len>=127) len=127;
		gb2ws(ws_lrc,pp,len);
		scroll_pos_lrc=1;
	}
end:
	draw_lrc_proc();
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
	if(msg->msg==MSG_RECONFIGURE_REQ)
	{
		extern const char *successed_config_filename;
		if(strcmp_nocase(successed_config_filename, (char *)msg->data0)==0)
		{
			ShowMSG(1, (int)LGP_UPDATE_CONFIG);
			RereadSettings();
			getname();
		}
	}
	
	if (playercsmid)
	{
		CSM_RAM *csmp=FindCSMbyID(playercsmid);
		if(csmp)
		{
			WSHDR *fn=((WSHDR **)csmp)[0x2C/4];
			if (!fn) goto L_ACTIVE;
			if (!fn->wsbody) goto L_ACTIVE;
			if (fn->wsbody[0])
			{
				ws_2str(fn, name_temp, 128);
				if((strcmp(name_temp, name_temp_cmp))&&ena_lrc)
				{
					strcpy(name_temp_cmp, name_temp);
					strcpy(lrc_path,lrc_dir_path);
					strcat(lrc_path,name_temp);
					char *p=strchr(lrc_path,'.');
					strcpy(p,".lrc");
					int size;
					int f;
					unsigned int err;
					if((f=fopen(lrc_path, A_ReadOnly, P_READ, &err))!=-1)
					{
						size=fread(f,lrc_buf,8*1024,&err);
						fclose(f, &err);
						is_no_lrc=0;
						if(size>=0)
							lrc_buf[size]=0;
					}
					else
					{
						wsprintf(ws_lrc, percent_t, "无歌词!");
						is_no_lrc=1;
					}
					scroll_pos=1;
					scroll_pos_lrc=1;
					time=0;
				}
				getname();
			}
			else
			{
			L_ACTIVE:
				wsprintf(ews, percent_t, "出错!");
			}
			is_player_active=1;
		}
		else
		{
			playercsmid=0;
			is_player_active=0;
		}
	}
	else
	{
		CSM_RAM *p=CSM_root()->csm_q->csm.first;
		while(p)
		{
			if (p->constr==playercsmadr) break;
			p=p->next;
		}
		if(p)
		{
			playercsmid=p->id;
		}
		else
			is_player_active=0;
	}	
	
	if(is_player_active&&(ENA_LOCK||IsUnlocked()))
	{
#define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
		CSM_RAM *icsm;
		icsm=FindCSMbyID(CSM_root()->idle_id);
		if(icsm&&is_music_file)
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
					if (idata)
					{
						void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
#endif
						int n;
						if(ena_lrc)
							n=GetFontYSIZE(lrc_font)+2;
						else
							n=0;
						DrawCanvas(canvasdata,pos_x,pos_y,pos_x+length,pos_y+GetFontYSIZE(font)+n+4,1);
						DrawRoundedFrame(pos_x,pos_y,pos_x+length,pos_y+GetFontYSIZE(font)+n+4, xrnd, yrnd, style, frmmain_color, frmbg_color);
						drawname_proc();
						if(ena_lrc)
							drawlrc();
					}
				}
			}
		}
	}
	return 1;
}

static void maincsm_oncreate(CSM_RAM *data)
{
	ews=AllocWS(128);
	ws_lrc=AllocWS(128);
	lrc_buf=malloc(8*1024);
	time_update_proc();
}

extern int my_keyhook(int submsg, int msg);
static void Killer(void)
{
	extern void *ELF_BEGIN;
	FreeWS(ews);
	FreeWS(ws_lrc);
	mfree(lrc_buf);
	GBS_DelTimer(&tmup);
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
	RereadSettings();
	UpdateCSMName();
	LockSched();
	save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
	CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
	CreateCSM(&MAINCSM.maincsm, dummy,0);
	CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
	UnlockSched();
	return 0;
}

