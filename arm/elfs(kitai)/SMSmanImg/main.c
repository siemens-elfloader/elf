#include "../inc/swilib.h"
#include "../inc/xtask_ipc.h"
#include "conf_loader.h"
#include "rect_patcher.h"
#include "sms_data.h"
#include "pdusms_sie.c"
#include "sms.c"
#include "lang.h"
#include "print.h"

SMS_DATA IN_SMSD, ch_SMSD;
int font=1;
void *canvasdata;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM; // §ã§ä§â§å§Ü§ä§å§â§Ñ csm
// PDU tPDU;

// extern const RECT cfgArea;
char SMS_SND[128];
int isvib[8], issnd[8], v_p[8], v_c[8], svol[8];

// void std_snd()
// {
// 	int f, pdsz;
// 	unsigned int er;
// 	char *pddat;
// 	if ((f=fopen("1:\\system\\hmi\\profile.pd",A_ReadOnly+A_BIN,0,&er))!=-1)
// 	{
// 		pdsz=lseek(f, 0, S_END, &er, &er);
// 		lseek(f, 0, 0, &er, &er);
// 		pddat=malloc(pdsz);
// 		fread(f,pddat,pdsz,&er);
// 		fclose(f,&er);
// 		
// 		for(int i=0; i<pdsz; i++)
// 			if(!strncmp(pddat+i,":T:Messages_",12))
// 			{
// 				if(pddat[i+12]=='1')
// 				{
// 					zeromem(SMS_SND, 128);
// 					memcpy(SMS_SND, pddat+i+14, (pddat[i-3]-'0')*100+(pddat[i-2]-'0')*10+(pddat[i-1]-'0')-20);
// 				}
// 				if(pddat[i+12]=='3')
// 				{
// 					zeromem(SMS_SND, 128);
// 					strncpy(SMS_SND, pddat+i+14, (pddat[i-3]-'0')*100+(pddat[i-2]-'0')*10+(pddat[i-1]-'0')-20);
// 					i=pdsz;
// 				}
// 			}
// 		mfree(pddat);
// 	}
// }

void reinit()
{
	InitConfig();
	
	isvib[0]=VIBR_1;
	isvib[1]=VIBR_2;
	isvib[2]=VIBR_3;
	isvib[3]=VIBR_4;
	isvib[4]=VIBR_5;
	isvib[5]=VIBR_6;
	isvib[6]=VIBR_7;
	isvib[7]=VIBR_8;
	
	issnd[0]=SOUND_1;
	issnd[1]=SOUND_2;
	issnd[2]=SOUND_3;
	issnd[3]=SOUND_4;
	issnd[4]=SOUND_5;
	issnd[5]=SOUND_6;
	issnd[6]=SOUND_7;
	issnd[7]=SOUND_8;
	
	v_p[0]=V_P_1;
	v_p[1]=V_P_2;
	v_p[2]=V_P_3;
	v_p[3]=V_P_4;
	v_p[4]=V_P_5;
	v_p[5]=V_P_6;
	v_p[6]=V_P_7;
	v_p[7]=V_P_8;
	
	v_c[0]=V_C_1;
	v_c[1]=V_C_2;
	v_c[2]=V_C_3;
	v_c[3]=V_C_4;
	v_c[4]=V_C_5;
	v_c[5]=V_C_6;
	v_c[6]=V_C_7;
	v_c[7]=V_C_8;
	
	svol[0]=S_VOL_1;
	svol[1]=S_VOL_2;
	svol[2]=S_VOL_3;
	svol[3]=S_VOL_4;
	svol[4]=S_VOL_5;
	svol[5]=S_VOL_6;
	svol[6]=S_VOL_7;
	svol[7]=S_VOL_8;
	
	/*if(!OWN_SND) std_snd();
	else */strcpy(SMS_SND, InSMSSound);
}


/*=====================================================*/

typedef struct
{
  GUI gui;
}MAIN_GUI;

#include "gui.c"

/* ************************************************** */

#define TMR_SECOND 216
GBSTMR tmr_vibra, tmr_insms;
int vibra_cnt;
short PLAY_ID=0;

void start_vibra(void)
{
	void stop_vibra(void);
	if((vibra_cnt>0)&&(!IsCalling()))
	{
		SetVibration(v_p[GetProfile()]);
		GBS_StartTimerProc(&tmr_vibra,TMR_SECOND/4,stop_vibra);
	}
}

void stop_vibra(void)
{
	SetVibration(0);
	if((--vibra_cnt)>=0)
		GBS_StartTimerProc(&tmr_vibra,TMR_SECOND/6,start_vibra);
}

void Play(const char *fname)
{
	if (!IsCalling())
	{
// 		FSTATS fstats;
		unsigned int err;
		if (isdir(fname,&err)!=-1)
		{
			PLAYFILE_OPT _sfo1;
			WSHDR* sndPath=AllocWS(128);
			WSHDR* sndFName=AllocWS(128);
			char s[128];
			const char *p=strrchr(fname,'\\')+1;
			str_2ws(sndFName,p,128);
			strncpy(s,fname,p-fname);
			s[p-fname]='\0';
			str_2ws(sndPath,s,128);

			zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
			_sfo1.repeat_num=1;
			_sfo1.time_between_play=0;
			_sfo1.play_first=0;
			_sfo1.volume=svol[GetProfile()];//sndVolume;
#ifdef NEWSGOLD
			_sfo1.unk6=1;
			_sfo1.unk7=1;
			_sfo1.unk9=2;
			PLAY_ID=PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
			_sfo1.unk4=0x80000000;
			_sfo1.unk5=1;
			PLAY_ID=PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
			_sfo1.unk5=1;
			PLAY_ID=PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif
			FreeWS(sndPath);
			FreeWS(sndFName);
		}
	}
}


void stop_insms();

int my_keyhook(int submsg, int msg)
{
	if (msg==KEY_DOWN)
	{
		if(IsTimerProc(&tmr_insms))
			GBS_DelTimer(&tmr_insms);
		stop_insms();
	}
	return 0;
}

void stop_insms()
{
	if (PLAY_ID)
		PlayMelody_StopPlayback(PLAY_ID);
	vibra_cnt=0;
	PLAY_ID=0;
	RemoveKeybMsgHook((void *)my_keyhook);
}



/****************************************************/


// SOFTKEY_DESC insms_sk[]=
// {
// 	{0x0018,0x0000,(int)"§°§ä§Ü§â§í§ä§î"},
// 	{0x0001,0x0000,(int)"§°§ä§Þ§Ö§ß§Ñ"},
// 	{0x003D,0x0000,(int)LGP_DOIT_PIC}
// };
// 
// SOFTKEYSTAB insms_skt=
// {
// 	insms_sk,0
// };

int insms_onkey(GUI *data, GUI_MSG *msg)
{
// 	EDITCONTROL ec;
// 	SMS_DATA *n;
// 	if (msg->gbsmsg->msg==KEY_DOWN)
// 	{
// 		if (msg->gbsmsg->submess==GREEN_BUTTON)
// 		{
// 			n=EDIT_GetUserPointer(data);
// 			if(n->type==TYPE_IN)
// 			{
// 				edit_sms(n);
// 			}
// 		}
// 	}
// /*      EDIT_RemoveEditControl(data,1,&ec);
// 			PrepareEditControl(&ec);
// 			wsprintf(ews,percent_t,"§¥§à§Ò§Ñ§Ó§Ý§Ö§ß§ß§à§Ö §á§à§Ý§Ö");
// 			ConstructEditControl(&ec,3,0x40,ews,256);
// 			EDIT_InsertEditControl(data,10,&ec);
// 			EDIT_SetFocus(data,10);
	// 			EDIT_SetCursorPos(data,3);*/
// /*      ExtractEditControl(data,EDIT_GetFocus(data),&ec);
// 			wstrcpy(ews,ec.pWS);
// 			wsAppendChar(ews,0xE12B);
	// 			EDIT_SetTextToFocused(data,ews);      */
// 			ExtractEditControl(data,3,&ec);
// 			WSHDR *sw=AllocWS(ec.pWS->wsbody[0]);
// 			wstrcpy(sw,ec.pWS);
// //      SendSMS(ews,"+380636038122",0x4209,MSG_SMS_RX-1,2); //§³ §â§Ö§Õ§Ñ§Ü§ä§Ú§â§à§Ó§Ñ§ß§Ú§Ö§Þ
// //      SendSMS(ews,"+380636038122",0x4209,MSG_SMS_RX-1,6); //§³§â§Ñ§Ù§å §Ó §Ò§à§Û §ã §à§Ü§à§ê§Ü§à§Þ
// //      SendSMS(sw,"+380636038122",0x4209,MSG_SMS_RX-1,6);
// 			return(-1);
// 		}
// 	}
  //-1 - do redraw
	return(0); //Do standart keys
  //1: close
}

void insms_ghook(GUI *data, int cmd)
{
	if (cmd==TI_CMD_FOCUS)
	{
		DisableIDLETMR();
	}
//  static SOFTKEY_DESC sk={0x0018,0x0000,(int)"Menu"};
// 	EDITCONTROL ec;
// 	int i;
// 	if (cmd==2)
// 	{
//     //Create
// 		edit_data=data;
// 		GBS_StartTimerProc(&mytmr,216/4,TestTimerProc);
// 	}
// 	if (cmd==3)
// 	{
// 		edit_data=NULL;
// 		GBS_DelTimer(&mytmr);
// 	}
// 	if (cmd==7)
// 	{
    //OnRun
//    SetSoftKey(data,&sk,1);
// 		ExtractEditControl(data,3,&ec);
// 		wstrcpy(ews,ec.pWS);
// 	}
// 	if (cmd==0x0D)
// 	{
    //onCombo
// 		if ((i=EDIT_GetItemNumInFocusedComboBox(data)))
// 		{
// 			wsprintf(ews,"%t%d","§±§å§ß§Ü§ä: ",i);
// 		}
// 		else
// 		{
// 			ExtractEditControl(data,EDIT_GetFocus(data)-1,&ec);
// 			wstrcpy(ews,ec.pWS);
// 		}
// 		EDIT_SetTextToFocused(data,ews);
// 	}
}

HEADER_DESC insms_hdr={0,0,0,0,NULL,NULL,LGP_NULL};

INPUTDIA_DESC insms_desc=
{
	1,
 insms_onkey,
 insms_ghook,
 (void *)ed1_locret,
  0,
  &menu_skt,
  {0,0,0,0},
  FONT_SMALL,
  100,
  101,
  0,

//  0x00000001 - §£§í§â§à§Ó§ß§ñ§ä§î §á§à §á§â§Ñ§Ó§à§Þ§å §Ü§â§Ñ§ð
//  0x00000002 - §£§í§â§à§Ó§ß§ñ§ä§î §á§à §è§Ö§ß§ä§â§å
//  0x00000004 - §ª§ß§Ó§Ö§â§ã§Ú§ñ §Ù§ß§Ñ§Ü§à§Þ§Ö§ã§ä
//  0x00000008 - UnderLine
//  0x00000020 - §¯§Ö §á§Ö§â§Ö§ß§à§ã§Ú§ä§î §ã§Ý§à§Ó§Ñ
//  0x00000200 - bold
  0,

//  0x00000002 - ReadOnly
//  0x00000004 - §¯§Ö §Õ§Ó§Ú§Ô§Ñ§Ö§ä§ã§ñ §Ü§å§â§ã§à§â
  0x40000000 // §±§à§Þ§Ö§ß§ñ§ä§î §Þ§Ö§ã§ä§Ñ§Þ§Ú §ã§à§æ§ä-§Ü§ß§à§á§Ü§Ú
};

int insms_ed()
{
	void *ma=malloc_adr();
	void *eq;
	EDITCONTROL ec;
	EDITC_OPTIONS ec_options;

	PrepareEditControl(&ec);
	eq=AllocEQueue(ma,mfree_adr());
	
	if(IN_SMSD.type!=TYPE_IN) return 0;
	
	insms_hdr.lgp_id=(int)LG_MESS;
	
// 	Time
	wsprintf(ews,perc_t,IN_SMSD.Time);
	ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,ews->wsbody[0]);
	PrepareEditCOptions(&ec_options);
// 		SetPenColorToEditCOptions(&ec_options,2);
	SetAlignToEditCOptions(&ec_options,TEXT_ALIGNMIDDLE);
	SetFontToEditCOptions(&ec_options,2);
	CopyOptionsToEditControl(&ec,&ec_options);
	AddEditControlToEditQend(eq,&ec,ma);
	
	wsprintf(ews,"\n%t\n%t",LG_NEW_IN,LG_FROM);
	ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,ews->wsbody[0]);
	PrepareEditCOptions(&ec_options);
// 	SetPenColorToEditCOptions(&ec_options,4);
	SetAlignToEditCOptions(&ec_options,TEXT_ALIGNMIDDLE);
	SetFontToEditCOptions(&ec_options,4);
	CopyOptionsToEditControl(&ec,&ec_options);
	AddEditControlToEditQend(eq,&ec,ma);
	
// 	Number
	wsprintf(ews,perc_t,IN_SMSD.Number);
	if(IN_SMSD.name)
	{
		wsAppendChar(ews,'\n');
		wstrcat(ews, IN_SMSD.name);
	}
	else
	{
		if(FindNameByNum(&IN_SMSD, ews))
		{
			wsAppendChar(ews,'\n');
			wstrcat(ews, IN_SMSD.name);
// 			wsprintf(ws,perc_t,IN_SMSD.Number);
// 			wstrcat(ews, ws);
		}
// 		else
// 			wsprintf(ews,perc_t,IN_SMSD.Number);
	}
	ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,ews->wsbody[0]);
	PrepareEditCOptions(&ec_options);
	SetFontToEditCOptions(&ec_options,3);
	SetAlignToEditCOptions(&ec_options,TEXT_ALIGNMIDDLE);
	CopyOptionsToEditControl(&ec,&ec_options);
	AddEditControlToEditQend(eq,&ec,ma);
	
	patch_header(&insms_hdr);
	patch_input(&insms_desc);

	return CreateInputTextDialog(&insms_desc,&insms_hdr,eq,1,0);
}

static void incomcsm_oncreate(CSM_RAM *data)
{
// 	ews=AllocWS(1024);
	
// 	if(read_smsdat())
// 	{
// 		SUBPROC((void*)ConstructList);
	INCOMGUI_ID=insms_ed();//create_ed();
// 	}
// 	else
// 	{
// 		CloseCSM(MAINCSM_ID);
// 		ShowMSG(1,(int)"§à§ê§Ú§Ò§Ü§Ñ §à§ä§Ü§â§í§ä§Ú§ñ");
// 	}
	
// 	gipc.name_to=ipc_my_name;
// 	gipc.name_from=ipc_my_name;
// 	gipc.data=(void *)-1;
// 	GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_CHECK_DOUBLERUN,&gipc);
}

static void incomcsm_onclose(CSM_RAM *csm)
{
	INCOMCSM_ID=0;
// 	FreeWS(ews);
	if(IN_SMSD.SMS_TEXT) FreeWS(IN_SMSD.SMS_TEXT);
	IN_SMSD.SMS_TEXT=NULL;
// 	if(IN_SMSD.name) FreeWS(IN_SMSD.name);
// 	IN_SMSD.name=NULL;
//   SUBPROC((void *)Killer);
}

static int incomcsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
	MAIN_CSM *csm=(MAIN_CSM*)data;
	
	if (msg->msg==MSG_GUI_DESTROYED)
	{
		if ((int)msg->data0==INCOMGUI_ID)
		{
			csm->csm.state=-3;
		}
	}
	return(1);
}

static unsigned short incomcsm_name_body[140];

static const struct
{
	CSM_DESC maincsm;
	WSHDR maincsm_name;
}INCOMCSM =
{
	{
		incomcsm_onmessage,
  incomcsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  incomcsm_onclose,
  sizeof(MAIN_CSM),
		 1,
   &minus11
	},
 {
	 incomcsm_name_body,
  NAMECSM_MAGIC1,
  NAMECSM_MAGIC2,
  0x0,
  139
 }
};

// void Log(int dummy, char *txt)
// {
// 	unsigned int ul;
// 	int f=fopen("4:\\log",A_ReadWrite+A_Create+A_Append+A_BIN,P_READ+P_WRITE,&ul);
// 	if (f!=-1)
// 	{
// 		fwrite(f,txt,strlen(txt),&ul);
// 		fclose(f,&ul);
// 	}
// 	mfree(txt);
// }

void Incom_SMS()//GBS_MSG *msg)
{
	GetSMSData(&IN_SMSD, IncommingPDU());
	if((!IN_SMSD.SMS_TEXT)||(IN_SMSD.n!=1)) return;
	if(IN_SMSD.type!=TYPE_IN) return;
	char tmp=0;
	for(int i=0; i<6; i++)
		if(ch_SMSD.tm[i]!=IN_SMSD.tm[i]) tmp++;
	if(!tmp) return;
	ch_SMSD=IN_SMSD;
	
// 	TTime time;
// 	TDate date;
// 	GetDateTime(&date, &time);
// 	char *s=malloc(100);
// 	sprintf(s,"%02d:%02d:%02d %08X %08X %08X %08X\r\n", time.hour,time.min,time.sec, msg->msg,msg->submess,msg->data0,msg->data1);
// 	SUBPROC((void *)Log,0,s);
	
	newsms++;
	char txt[64];
	sprintf(txt,"SMSD: %d new", newsms);
	UpdateDAEMONname(txt);
	
	if(IsCalling()) return;
	
	if(isvib[GetProfile()])
	{
		vibra_cnt=v_c[GetProfile()];
		start_vibra();
	}
	
	if(issnd[GetProfile()]) Play(SMS_SND);
	
	if(issnd[GetProfile()] || isvib[GetProfile()])
	{
		AddKeybMsgHook((void *)my_keyhook);
		GBS_StartTimerProc(&tmr_insms,TMR_SECOND*30,stop_insms);
	}
	
	if(INCOMCSM_ID)
	{
		gipc.name_to=ipc_xtask_name;
		gipc.name_from=ipc_my_name;
		gipc.data=(void *)INCOMCSM_ID;
		GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_SHOW_CSM,&gipc);
	}
	else
	{
		char dummy[sizeof(MAIN_CSM)];
		UpdateCSMname("NEW SMS", (WSHDR *)&INCOMCSM.maincsm_name);
		
		CSM_RAM *save_cmpc;
		LockSched();
		save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
		CSM_root()->csm_q->current_msg_processing_csm=NULL;
		INCOMCSM_ID = CreateCSM(&INCOMCSM.maincsm, dummy, 0);
		CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
		UnlockSched();
	}
}

static void daemoncsm_oncreate(CSM_RAM *data)
{
	scr_h=ScreenH()-1; // §Ó§í§ã§à§ä§Ñ §ï§Ü§â§Ñ§ß§Ñ
	scr_w=ScreenW()-1; // §ß§Ú§â§Ú§ß§Ñ §ï§Ü§â§Ñ§ß§Ñ
	msws=CreateLocalWS(&mshws,mswsbody,256);
	sf_h=GetFontYSIZE(FONT_SMALL);
// 	msws=AllocWS(256);
	ws=AllocWS(256);
	ews=AllocWS(256);
	
	GetSMSData(&ch_SMSD, IncommingPDU());
	
	gipc.name_to=ipc_my_name;
	gipc.name_from=ipc_my_name;
	gipc.data=(void *)-1;
	GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_CHECK_DOUBLERUN,&gipc);
}

static void daemoncsm_onclose(CSM_RAM *csm)
{
	if(INCOMCSM_ID) CloseCSM(INCOMCSM_ID);
	if(MAINCSM_ID) CloseCSM(MAINCSM_ID);
	FreeWS(ws);
	FreeWS(ews);
	FreeCLIST();
	SUBPROC((void *)Killer);
}

void CheckDoubleRun(void)
{
	int csm_id;//, f, c;
// 	unsigned int er;
// 	char *smsdat, *p;
	if ((csm_id=(int)(gipc.data))!=-1)
	{
		gipc.name_to=ipc_my_name;
		gipc.name_from=ipc_my_name;
		gipc.data=(void*)csm_id;
		LockSched();
		GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_OPEN_GUI,&gipc);
		CloseCSM(DAEMON_ID);
		UnlockSched();
	}
	else
	{
		reinit();
		SUBPROC((void*)ConstructList);
	}
		
// 		checknew=isNewSMS(0);
// 		char *t=(char*)IncommingPDU();
// 		char c=*(t+=t[3]+5);
// 		if(c%2) c=c/2+2;
// 		else c=c/2+1;
// 		t+=c+3;
// 		for (int i=0; i<6; i++)
// 		{
// 			dttm[i]=t[i]%0x10*10+t[i]/0x10;
// 		}
// 		memcpy(dttm, t, 7);
// 		tPDU=malloc(sizeof(PDU));
// 		memcpy(tPDU, IncommingPDU, sizeof(PDU));
// 	}
}

// void InSMS(int decision)
// {
// 	if(!decision)
// 		if(MAINCSM_ID)
// 		{
// 			gipc.name_to=ipc_xtask_name;
// 			gipc.name_from=ipc_my_name;
// 			gipc.data=(void *)MAINCSM_ID;
// 			GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_SHOW_CSM,&gipc);
// 		}
// 		else main2();
// }

static int daemoncsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ)//§±§Ö§â§Ö§é§Ú§ä§í§Ó§Ñ§ß§Ú§Ö §Ü§à§ß§æ§Ú§Ô§Ñ §á§à §ã§à§à§Ò§ë§Ö§ß§Ú§ð
  {
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      FontPathFree();
      reinit();//§°§Ò§ß§à§Ó§Ý§ñ§Ö§Þ §Ü§à§ß§æ§Ú§Ô
      FontPathInit(font,(char *)PNG_FNT_PATH,FULLFONT);
    }
  }
  if(IN_NOTIFY)//§°§á§à§Ó§Ö§ë§Ö§ß§Ú§Ö §à §ß§à§Ó§à§Û §ã§Þ§ã
  {
  #ifdef ELKA
    if(msg->msg == 0x6106)
  #else
      if((msg->msg == 0x61D6)||(msg->msg == 0x61CC))
  #endif
      {
        Incom_SMS();//msg);
      }
  }
  //§¯§Ñ§â§Ú§ã§å§Ö§Þ §Ú§Ü§à§ß§à§é§Ü§å §Þ§à§Ö§Ô§à §ã§ä§Ñ§ä§å§ã§Ñ
  extern const int show_in;
  unsigned int show;
  switch (show_in)//§±§â§Ú §Ü§Ñ§Ü§à§Þ §Þ§à§Þ§Ö§ß§ä§Ö §Ó§í§Ó§à§Õ§Ú§ä§î §Ú§ß§æ§à§â§Þ§Ñ§è§Ú§ð §ß§Ñ §¤§¿
  {
  case 0:
   show=!IsUnlocked();
  break;
  case 1:
   show=IsUnlocked();
  break;
  case 2:
  show=1;
  break;
  }
  #define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
  if(newsms||SHOW0NEW)
  {
    CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
    if (IsGuiOnTop(idlegui_id)&& show) //§¦§ã§Ý§Ú IdleGui §ß§Ñ §ã§Ñ§Þ§à§Þ §Ó§Ö§â§ç§å
    {
      GUI *igui=GetTopGUI();
      if (igui)//§ª §à§ß §ã§å§ë§Ö§ã§ä§Ó§å§Ö§ä
      {
        if(SHOW_IDLE_TEXT)//§£§í§Ó§à§Õ§Ú§Þ §ä§Ö§Ü§ã§ä
        {
        char txt[128];
        canvasdata=BuildCanvas();
        switch(TYPE_FNT)//§£§í§Ò§à§â §Ü§Ñ§Ü §â§Ú§ã§à§Ó§Ñ§ä§î §ä§Ö§Ü§ã§ä, §á§ß§Ô §Ú§Ý§Ú §ê§â§Ú§æ§ä§à§Þ §ä§Ö§Ý§Ñ
        {
        case 0:
          sprintf(txt, IDLETXT, newsms);
          wsprintf(msws, perc_t, txt);
          DrawCanvas(canvasdata,IDLE_X,IDLE_Y,IDLE_X+Get_WS_width(msws,IDLE_FNT), IDLE_Y+sf_h,1);
          DrawString(msws, IDLE_X,IDLE_Y, IDLE_X+Get_WS_width(msws,IDLE_FNT), IDLE_Y+sf_h, IDLE_FNT, 1, white, NULL);
        break;
        case 1:
          sprintf(txt,IDLETXT, newsms);
          PrintField(IDLE_X,IDLE_Y,txt,ALIGN, font,SPACE);
        break;
        }
        }
        if(SHOW_IDLE_PIC)//§²§Ú§ã§å§Ö§Þ §ã§ä§Ñ§ä§å§ã §ã§Þ§ã §Ü§Ñ§â§ä§Ú§ß§Ü§à§Û
        {
          extern const char pic_folder[128];
          const char perc_s[]="%s%s";
          char pic_idle[64];
          if(newsms)
          {
           sprintf(pic_idle,perc_s,pic_folder,"newsms.png");//§¬§Ñ§â§ä§Ú§ß§Ü§Ñ §ß§à§Ó§à§Û §ã§Þ§ã
           DrawImg(IDLEICON_X,IDLEICON_Y,(int)pic_idle);
          }
          if(SHOW0NEW)
          {
           sprintf(pic_idle,perc_s,pic_folder,"sms.png");//§¬§Ñ§â§ä§Ú§ß§Ü§Ñ §á§â§Ú 0 §ã§Þ§ã
           DrawImg(IDLEICON_X,IDLEICON_Y,(int)pic_idle);
          }
        }
      }
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
        case IPC_CHECK_DOUBLERUN:
	//§¦§ã§Ý§Ú §á§â§Ú§ß§ñ§Ý§Ú §ã§Ó§à§Ö §ã§à§Ò§ã§ä§Ó§Ö§ß§ß§à§Ö §ã§à§à§Ò§ë§Ö§ß§Ú§Ö, §Ù§ß§Ñ§é§Ú§ä §Ù§Ñ§á§å§ã§Ü§Ñ§Ö§Þ §é§Ö§Ü§Ö§â
          if (ipc->name_from==ipc_my_name) CheckDoubleRun();
          else ipc->data=(void *)DAEMON_ID;
          break;
        case IPC_OPEN_GUI:
        //Incom_SMS();
          main2();
          break;
        }
      }
    }
  }
  return(1);
}

static unsigned short daemoncsm_name_body[140];

static const struct
{
	CSM_DESC daemoncsm;
	WSHDR daemoncsm_name;
}DAEMONCSM =
{
	{
		daemoncsm_onmessage,
  daemoncsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  daemoncsm_onclose,
  sizeof(MAIN_CSM),
		 1,
   &minus11
	},
 {
	 daemoncsm_name_body,
  NAMECSM_MAGIC1,
  NAMECSM_MAGIC2,
  0x0,
  139
 }
};

void UpdateDAEMONname(char *txt)
{
  UpdateCSMname(txt, (WSHDR *)&DAEMONCSM.daemoncsm_name);  
}

int main()
{
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateDAEMONname("SMSD");
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  DAEMON_ID=CreateCSM(&DAEMONCSM.daemoncsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  FontPathInit(font,(char *)PNG_FNT_PATH,FULLFONT);
  return 0;
}
