#include "..\inc\swilib.h"


extern char filename[128];
extern WSHDR *e_ws;
extern void patch_header(const HEADER_DESC* head);
extern void patch_input(const INPUTDIA_DESC* inp);
extern SOFTKEYSTAB menu_skt;
extern HEADER_DESC inp_hdr;
extern void UpdateCSMname(void);
//extern volatile int edit_gui_id;

WSHDR *tmo;
char header_str[128];
HEADER_DESC sf_inp_hdr={0,0,0,0,0,(int)"另存为:",LGP_NULL};

/*
SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"选择"},
  {0x0001,0x0000,(int)"返回"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};*/

void savetmo(void)
{
	UpdateCSMname();
	//char *sh_fname=strrchr(filename,'\\');
	//inp_hdr.lgp_id=(int)sh_fname;
	ws2gb(e_ws, header_str, 128);
	char *sh_fname=strrchr(header_str,'\\');
	inp_hdr.lgp_id=(int)sh_fname;
	extern int SaveText(WSHDR *tmostr);
	SaveText(tmo);
}

void sf_inp_ghook(GUI *data, int cmd)
{
	static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)"保存"};
	EDITCONTROL ec;
	if (cmd==7)
	{
		SetSoftKey(data,&sk,SET_SOFT_KEY_N);
		ExtractEditControl(data,1,&ec);
		wstrcpy(e_ws,ec.pWS);
	}
}


int sf_inp_onkey(GUI *data, GUI_MSG *msg)
{
	if (msg->keys==0xFFF)
	{
		ws_2str(e_ws,filename,128);
		SUBPROC((void *)savetmo);
		return(1); //Close
	}
	return(0);
}

void sf_inp_locret(void){}

INPUTDIA_DESC sf_inp_desc=
{
	1,
	sf_inp_onkey,
	sf_inp_ghook,
	(void *)sf_inp_locret,
	0,
	&menu_skt,
	{0,0,0,0},
	4,
	100,
	101,
	0,
	0,
	0x40000000
};

void CreateSaveAsDialog(WSHDR *tmostr)
{
	void *ma=malloc_adr();
	void *eq;
	tmo=tmostr;
	str_2ws(e_ws, filename, 128);
	//WSHDR *e_ws=AllocWS(128);
	EDITCONTROL ec;
	PrepareEditControl(&ec);
	eq=AllocEQueue(ma,mfree_adr());
	ConstructEditControl(&ec,ECT_CURSOR_STAY,ECF_APPEND_EOL,e_ws,128);
	AddEditControlToEditQend(eq,&ec,ma);
	patch_header(&sf_inp_hdr);
	patch_input(&sf_inp_desc);
	CreateInputTextDialog(&sf_inp_desc,&sf_inp_hdr,eq,1,0);
}

