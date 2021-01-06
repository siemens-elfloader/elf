#include "../inc/swilib.h"
#include "conf_loader.h"
#include "scrfrm.h"

extern kill_data(void *p, void (*func_p)(void *));

//config
//extern const int ENA_LOCK;

typedef struct
{
	CSM_RAM csm;
}MAIN_CSM;
/*
void draw(RECT pos, int xrnd, int yrnd, int rnd_flag, const char *color, const char *string, int str_x, int str_y, int font, const char *str_col, const char *strfr_col)
{
	char *bg_col=GetPaletteAdrByColorIndex(23);
	int scrh=ScreenH()-1;
	int scrw=ScreenW()-1;
	WSHDR *ws=AllocWS(128);
	wsprintf(ws, "%t", string);
	DrawRoundedFrame(pos.x, pos.y, pos.x2, pos.y2, xrnd, yrnd, rnd_flag, color, bg_col);
	DrawString(ws, str_x, str_y, scrw, scrw, font, 32, str_col, strfr_col);
	FreeWS(ws);
}*/

WSHDR *ws;
int scrh;
int scrw;

const char _percent_t[]="%t";
void DrawFrame(void)
{
	//const char *bg_col=GetPaletteAdrByColorIndex(23);
	//int scrh=ScreenH()-1;
	//int scrw=ScreenW()-1;
//	WSHDR *ws=AllocWS(128);
	//DrawRoundedFrame(int x1,int y1,int x2,int y2,int x_round,int y_round,int flags,const char *pen,const char *brush);
	if(enable1)
	{
//		draw(pos1, xrnd1, yrnd1, style1, color1, string1, str_x1, str_y1, font1, str_col1, strfr_col1);
		DrawRoundedFrame(pos1.x, pos1.y, pos1.x2, pos1.y2, xrnd1, yrnd1, style1, color1, bg_col1);
//		WSHDR *ws=AllocWS[128];
		wsprintf(ws, _percent_t, string1);
		//utf8_2ws(ws, string1, strlen(string1));
		DrawString(ws, str_x1, str_y1, scrw, scrw, font1, 32, str_col1, strfr_col1);
//		FreeWS(ws);
	}
	if(enable2)
	{
		DrawRoundedFrame(pos2.x, pos2.y, pos2.x2, pos2.y2, xrnd2, yrnd2, style2, color2, bg_col2);
		wsprintf(ws, _percent_t, string2);
		DrawString(ws, str_x2, str_y2, scrw, scrw, font2, 32, str_col2, strfr_col2);
	}
	if(enable3)
	{
		DrawRoundedFrame(pos3.x, pos3.y, pos3.x2, pos3.y2, xrnd3, yrnd3, style3, color3, bg_col3);
		wsprintf(ws, _percent_t, string3);
		DrawString(ws, str_x3, str_y3, scrw, scrw, font3, 32, str_col3, strfr_col3);
	}
	if(enable4)
	{
		DrawRoundedFrame(pos4.x, pos4.y, pos4.x2, pos4.y2, xrnd4, yrnd4, style4, color4, bg_col4);
		wsprintf(ws, _percent_t, string4);
		DrawString(ws, str_x4, str_y4, scrw, scrw, font4, 32, str_col4, strfr_col4);
	}
	if(enable5)
	{
		DrawRoundedFrame(pos5.x, pos5.y, pos5.x2, pos5.y2, xrnd5, yrnd5, style5, color5, bg_col5);
		wsprintf(ws, _percent_t, string5);
		DrawString(ws, str_x5, str_y5, scrw, scrw, font5, 32, str_col5, strfr_col5);
	}
	if(enable6)
	{
		DrawRoundedFrame(pos6.x, pos6.y, pos6.x2, pos6.y2, xrnd6, yrnd6, style6, color6, bg_col6);
		wsprintf(ws, _percent_t, string6);
		DrawString(ws, str_x6, str_y6, scrw, scrw, font6, 32, str_col6, strfr_col6);
	}
//	FreeWS(ws);
}

#pragma inline=forced
int toupper(int c)
{
	if((c>='a')&&(c<='z'))
		c+='A'-'a';
	return c;
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
int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
#define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
	CSM_RAM *icsm;
	if(msg->msg==MSG_RECONFIGURE_REQ)
	{
		extern const char *successed_config_filename;
		if(strcmp_nocase(successed_config_filename, (char *)msg->data0)==0)
		{
			ShowMSG(1, (int)"ScreenFrame ÅäÖÃ¸üÐÂ!");
			InitConfig();
		}
	}
	icsm=FindCSMbyID(CSM_root()->idle_id);
	if(icsm)
	{
		if(IsGuiOnTop(idlegui_id(icsm)))
		{
			GUI *igui=GetTopGUI();
			if(igui)
			{
				if(ENA_LOCK||IsUnlocked())
				{
					DrawFrame();
				}
			}
		}
	}
	return 1;
}

static void maincsm_oncreate(CSM_RAM *data)
{
	ws=AllocWS(128);
	scrh=ScreenH()-1;
	scrw=ScreenW()-1;
}

static void Killer(void)
{
	extern void *ELF_BEGIN;
	FreeWS(ws);
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
	wsprintf((WSHDR *)(&MAINCSM.maincsm_name), "ScreenFrame");
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
