#include "inc\mc.h"
#include "inc\mui.h"

IFN_RET_PROC txt_inp_proc;
int testfn;
WSHDR *wssrcname;

int txt_inp_onkey(GUI *gui, GUI_MSG *msg)
{
	if (!wsbuf)
	{
		GeneralFuncF1(1);
		return(0);	
	}

	EDITCONTROL ec;
	if (msg->keys==26)
	{
		ExtractEditControl(gui,2,&ec);	
		wstrcpy(wsbuf,ec.pWS);
		if (!testfn || TestFileName(wsbuf))
		{  
			txt_inp_proc(wsbuf);
			GeneralFuncF1(1);
		} 
		else
		{
			MsgBoxError(1, (int) muitxt(ind_err_badname));
			CorFileName(wsbuf);
			msg->keys = 0;
			EDIT_SetTextToFocused(gui,wsbuf);
		} 
	}
	return(0); //Do standart keys
}

HEADER_DESC txt_inp_hdr={0,0,0,0,/*icon*/NULL,0,LGP_NULL};
INPUTDIA_DESC txt_inp_desc=
{
	1,
	txt_inp_onkey,
	empty_ghook,
	(void *)empty_locret,
	0,
	&empty_menu_skt,
	{0,0,0,0},
	FONT_SMALL,
	100,
	101,
	0,
	0,
	0x40000000
};

void TextInput(char *caption, char *prmpt, int TestFileName, WSHDR *wsname, IFN_RET_PROC retproc)
{
	txt_inp_hdr.lgp_id = (int)caption;
	txt_inp_proc = retproc;
	testfn = TestFileName;

	WSHDR *buff=AllocWS(32);

	void *ma=malloc_adr();
	void *eq=AllocEQueue(ma,mfree_adr());
	EDITCONTROL ec;
	PrepareEditControl(&ec);

	wsprintf(buff, _tc, prmpt);
	ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,buff,32);
	prep_hd(&ec);
	AddEditControlToEditQend(eq,&ec,ma);

	ConstructEditControl(&ec,ECT_CURSOR_STAY,ECF_SET_CURSOR_END,wsname,MAX_PATH);
	//  prep_inf(&ec);
	AddEditControlToEditQend(eq,&ec,ma);

	CreateInputTextDialog(&txt_inp_desc,&txt_inp_hdr,eq,1,0);

	FreeWS(buff);
}
