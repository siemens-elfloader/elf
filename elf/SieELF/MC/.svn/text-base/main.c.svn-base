#include "inc\mc.h"
#include "inc\mui.h"
#include "inc\lng.h"
#include "inc\ColorMap.h"
#include "inc\config.h"
#include "inc\exts.h"
#include "inc\gui.h"
#include "inc\zslib.h"

const int minus11=-11; // стремная константа
unsigned short maincsm_name_body[140];
volatile int GUIStarted = 0; //Elf вызван
volatile int Terminate = 0; // флаг необходимости завершения работы
volatile int Busy = 0;

unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

int MsgBoxResult = -1;

unsigned int err;

#ifdef LOG
int flog=-1;
#endif

WSHDR *guibuf;
WSHDR *wsbuf;
char* pathbuf;
char* pathbuf2;
char* pathbuf_fn;
char* msgbuf;
char* szLastNewFile;
char* szLastNewDir;
char* zippathbuf;
FN_LIST tmp_files;

typedef struct
{
	CSM_RAM csm;
	int gui_id;
} MAIN_CSM;

typedef struct
{
	GUI gui;
	//  WSHDR *ws1;
	//  WSHDR *ws2;
	//  int i1;
} MAIN_GUI;


void FreeData()
{
	LockSched();
	GBS_DelTimer(&sctm);
	GBS_DelTimer(&cmtm);
	GBS_DelTimer(&offtm);
	
	if (CONFIG_LOAD_CS) SaveCS(NULL);
#ifdef DUMP_MUI
	void SaveMUI2(char* filename);
	SaveMUI2(NULL);
#else
	if (CONFIG_LOAD_MUI) SaveMUI(NULL);
#endif
	SaveCfg();
	fn_free(&buffer);
	FreeMUI();
	FreeExt();
	if (zippathbuf) mfree(zippathbuf);
	if (szLastNewDir) mfree(szLastNewDir);
	if (szLastNewFile) mfree(szLastNewFile);
	if (msgbuf) mfree(msgbuf);
	if (pathbuf_fn) mfree(pathbuf_fn);
	if (pathbuf2) mfree(pathbuf2);
	if (pathbuf) mfree(pathbuf);
	if (wsbuf) FreeWS(wsbuf);
	if (guibuf) FreeWS(guibuf);
	guibuf = wsbuf = 0;
	zippathbuf = pathbuf = pathbuf2 = pathbuf_fn = msgbuf = 0;
	for(int ii=0; ii<MAX_TABS+1; ii++)
	{
		DelFiles(ii);
		FreeTab(ii);
	}
	UnlockSched();
#ifdef LOG
	_WriteLog("FreeData");
	fclose(flog,&err);
#endif
}

void OnRedraw(MAIN_GUI *data) // OnRedraw
{
	if (!GUIStarted)
	{
		guibuf=AllocWS(MAX_PATH*2);
		wsbuf=AllocWS(MAX_PATH*2);
		pathbuf=malloc(MAX_PATH);
		pathbuf2=malloc(MAX_PATH);
		pathbuf_fn=malloc(MAX_PATH);
		msgbuf=malloc(256);
		szLastNewFile=malloc(MAX_PATH);
		szLastNewDir=malloc(MAX_PATH);
		zippathbuf=malloc(MAX_PATH);
		*szLastNewFile = '\0';
		*szLastNewDir = '\0';
		LoadKeys();
#ifdef LOG
		_WriteLog("LoadExts");
#endif
		LoadExts();
#ifdef LOG
		_WriteLog("LoadCfg");
#endif
		LoadCfg();

		for(int ii=0; ii < MAX_TABS+1; ii++)
			InitTab(ii);

		if (CONFIG_SAVE_PATH)
		{
#ifdef LOG
			_WriteLog("Init Last Dirs");
#endif
			for(int ii=0;ii<MAX_TABS;ii++)
			{
				int srt=MCConfig.tabs[ii].sort;
				int srtH=(srt & STD_MASK);
				int srtL=(srt & STV_MASK);
				srt=(srtL<=ST_LAST?srtL:0) | srtH;
				tabs[ii]->sort=srt;
				if (MCConfig.tabs[ii].LastPath[0] /*&& isdir(MCConfig.tabs[ii].LastPath, &err)*/)
				{
					cd(ii, MCConfig.tabs[ii].LastPath);
					SetTabIndex(ii, MCConfig.tabs[ii].LastInd, 0);
				}
			}
			curtab = MCConfig.curtab;
		}
#ifdef LOG
		_WriteLog("InitCS");
#endif
		InitScr();
		InitCS();
		InitAllMD();
		if (CONFIG_LOAD_MUI)
			LoadMUI(NULL);
		else
			InitMUI();
#ifdef LOG
		_WriteLog("Work...");
#endif
		if (CONFIG_SCROLL_TEXT_SPEED)
			GBS_StartTimerProc(&sctm,CONFIG_SCROLL_TEXT_SPEED,DrwName);

		GUIStarted = 1;

		if (in_open_path[0])
		{
			if (isdir(in_open_path, &err))
			{
				cd(curtab = 0, in_open_path);
			}
			else if (CONFIG_ZIP_ENABLE && IsItZipFile(in_open_path))
			{
				// переходим в папку с зипом
				cd(curtab = 0, GetFileDir(in_open_path, pathbuf));
				// ищем наш зип файл
				int idx = GetCurTabFileIndex(GetFileName(in_open_path));
				SetCurTabIndex(idx, 0);
				// открываем
				strcpy(zippathbuf, in_open_path);
				SUBPROC((void*)S_ZipOpen);
			}
		}
	}

	if (IsGuiOnTop(MAINGUI_ID))
	{
		if (progr_start) ShowProgr();
		else ShowFiles();
	}
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
#ifdef LOG
	_WriteLog("gui.onCreate");
#endif
	//  data->ws1=AllocWS(256);
	//  data->ws2=AllocWS(256);
	data->gui.state = 1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
#ifdef LOG
	_WriteLog("gui.onClose");
#endif
	//  FreeWS(data->ws1);
	//  FreeWS(data->ws2);
	data->gui.state = 0;
	Terminate = progr_stop = 1;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
	if (ext_pnglist != NULL)
	{
		PNGTOP_DESC* pltop = PNG_TOP();
		pltop->dyn_pltop = &ext_pnglist->dpl;
	}
	
	data->gui.state = 2;
	if (Terminate && !Busy)
		GeneralFuncF1(1); // рубим верхний гуй. И приложение закрывается.
	else
		DirectRedrawGUI();
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
	PNGTOP_DESC* pltop = PNG_TOP();
	pltop->dyn_pltop = NULL;

	if (data->gui.state != 2) return;
	data->gui.state = 1;
}

void CB_Stop(int id)
{
	if (id==IDYES) progr_stop = 1;
}

int lastKey = -1;
int lastIsLongPress = 0;
int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
	if (GUIStarted) // Обрабатываем только после полной инициализации
	{
		// Для сброса счетчика таймера автовыхода отслеживаем только клавиши
		ResetAutoExit();

		short key = msg->gbsmsg->submess;
		int isLongPress = 0;
		int ignore = 1;

		if (progr_start)
		{
			if (msg->gbsmsg->submess==RIGHT_SOFT || msg->gbsmsg->submess==LEFT_SOFT)
				MsgBoxYesNo(1, (int) muitxt(ind_pmt_stop), CB_Stop);
		}
		else if (!Busy)
		{
			if (GetKeyprocLongByKey(key) == NULL)
			{
				// Не нужна обработка двойного нажатия
				// Обрабатываем только KEY_DOWN и LONG_PRESS
				ignore = (msg->gbsmsg->msg != KEY_DOWN && msg->gbsmsg->msg != LONG_PRESS);
			}
			else
			{
				isLongPress = (msg->gbsmsg->msg == LONG_PRESS);
				
				// Игнорим KEY_UP если уже обработали долгое нажатие этой же кнопки
				// Обрабатываем только KEY_UP и LONG_PRESS
				ignore = (lastKey == key && lastIsLongPress && msg->gbsmsg->msg == KEY_UP)
					|| (msg->gbsmsg->msg != KEY_UP && msg->gbsmsg->msg != LONG_PRESS);
			}
		}

		if (!ignore)
		{
			DoKey(isLongPress, key);
			DirectRedrawGUI();
		}

		lastKey = key;
		lastIsLongPress = isLongPress;
	}

	return(0);
}

extern void kill_data(void *p, void (*func_p)(void *));

void Killer(void)
{
	FreeData();
	extern void *ELF_BEGIN;
	kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
	(void *)OnRedraw,	//Redraw
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

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
	rc->x=x;
	rc->y=y;
	rc->x2=x2;
	rc->y2=y2;
}
const RECT Canvas={0,0,0,0};

void maincsm_oncreate(CSM_RAM *data)
{
#ifdef LOG
	_WriteLog("maincsm_oncreate");
#endif
	MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
	MAIN_CSM *csm=(MAIN_CSM*)data;
	zeromem(main_gui,sizeof(MAIN_GUI));
	patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
	main_gui->gui.canvas=(void *)(&Canvas);
	main_gui->gui.flag30=2;
	main_gui->gui.methods=(void *)gui_methods;
	main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
	csm->csm.state=0;
	csm->csm.unk1=0;
	csm->gui_id=CreateGUI(main_gui);
	MAINGUI_ID=csm->gui_id;
}


void maincsm_onclose(CSM_RAM *csm)
{
#ifdef LOG
	_WriteLog("maincsm_onclose");
#endif
	SUBPROC((void *)Killer);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
#ifdef LOG
	_WriteLogHex("msg:", msg->msg);
#endif
	MAIN_CSM *csm=(MAIN_CSM*)data;
	if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
	{
		csm->csm.state=-3;
	}
	else
	{
		if (msg->msg == MSG_IDLETMR_EXPIRED)
		{
			return(0);
		}
		else
		{
			if (msg->msg==MSG_RECONFIGURE_REQ)
			{
				//	ShowMSG(1,(int)muitxt(ind_reconfig));
				InitConfig();
				UpdateAll();

				if(!IsTimerProc(&offtm))
					AutoExitProc();		
				ResetAutoExit();
			}
		}
	}
	return(1);
}

const struct
{
	CSM_DESC maincsm;
	WSHDR maincsm_name;
} MAINCSM =
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
	if (wsbuf)
	{
		str_2ws(wsbuf,_CurPath,MAX_PATH);
		wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"mc - %w", wsbuf);
	}
}

int main(char *exename, char *fname)
{
	guibuf=wsbuf=0;
	pathbuf=pathbuf2=pathbuf_fn=msgbuf=0;

	GetFileDir(exename, mcpath);
#ifdef LOG
	char buf[MAX_PATH];
	pathbuf = &buf[0];
	flog = fopen(MCFilePath("mc.log"),A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&err);
	pathbuf = 0;
	_WriteLog("Start");
#endif

#ifdef LOG
	_WriteLog("InitConfig");
#endif
	InitConfig();
	AutoExitProc();
	if (fname) strcpy(in_open_path, fname);

	char dummy[sizeof(MAIN_CSM)];
	MAINCSM_ID = CreateCSM(&MAINCSM.maincsm, dummy, 0);
	UpdateCSMname();
	return 0;
}




















#ifdef LOG
void _WriteLog(char *buf)
{
	if (flog!=-1)
	{
		char msg[512];

		TTime t;
		TDate d;
		GetDateTime(&d,&t);
		sprintf(msg, "%02d:%02d:%02d %s\n", t.hour,t.min,t.sec,buf);
		//  sprintf(msg, "%s\n", buf);
		fwrite(flog,msg,strlen(msg),&err);
	}
}
void _WriteLogWS(WSHDR *buf)
{
	if (flog!=-1)
	{
		char msg[256];
		char msg2[256];
		ws_2str(buf, msg2, 256);

		TTime t;
		TDate d;
		GetDateTime(&d,&t);
		sprintf(msg, "%02d:%02d:%02d %s\n", t.hour,t.min,t.sec,msg2);
		//  sprintf(msg, "%s\n", buf);
		fwrite(flog,msg,strlen(msg),&err);
	}
}

void _WriteLog2(char *buf1, char *buf2)
{
	if (flog!=-1)
	{
		char msg[512];

		TTime t;
		TDate d;
		GetDateTime(&d,&t);
		sprintf(msg, "%02d:%02d:%02d %s %s\n", t.hour,t.min,t.sec,buf1,buf2);
		//  sprintf(msg, "%s\n", buf);
		fwrite(flog,msg,strlen(msg),&err);
	}
}
void _WriteLogInt(char *buf, int ii)
{
	if (flog!=-1)
	{
		char msg[512];
		TTime t;
		TDate d;
		GetDateTime(&d,&t);
		sprintf(msg, "%02d:%02d:%02d %s %d\n", t.hour,t.min,t.sec,buf,ii);
		fwrite(flog,msg,strlen(msg),&err);
	}
}
void _WriteLogHex(char *buf, int ii)
{
	if (flog!=-1)
	{
		char msg[512];
		TTime t;
		TDate d;
		GetDateTime(&d,&t);
		sprintf(msg, "%02d:%02d:%02d %s %.8x\n", t.hour,t.min,t.sec,buf,ii);
		fwrite(flog,msg,strlen(msg),&err);
	}
}
#endif
