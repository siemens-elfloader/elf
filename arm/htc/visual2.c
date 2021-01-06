#include "swilib.h"
char Text_in_Editor[4000];
char *Text_out_Editor="Бабушка кормила Андрюшку яблоками и грушами. От яблок у Андрюшки был понос, а oт груш его пучило.   ";
typedef void (*IFN_RET_PROC) (WSHDR *wsname);
    WSHDR *wsbuf;
    
//#include "inc\mc.h"
//extern void patch_input( INPUTDIA_DESC* inp);
extern void patch_header(HEADER_DESC* head);
extern open_select_file_gui(void *ed_gui, int type);
IFN_RET_PROC txt_inp_proc;
void empty_ghook(GUI *gui, int cmd){};
void empty_locret(void) {}
SOFTKEY_DESC empty_menu_sk[]= { { 0, 0, 0 } };

SOFTKEYSTAB empty_menu_skt =
{
	empty_menu_sk, 0
};

int testfn;
WSHDR *wssrcname;
 WSHDR *ws;
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
		if (!testfn)
		{
			txt_inp_proc(wsbuf);
			GeneralFuncF1(1);
		}
		else
		{
                  MsgBoxError(1, (int) "O-o! :)");
			CorFileName(wsbuf);
			msg->keys = 0;
			EDIT_SetTextToFocused(gui,wsbuf);
		}
	}
	return(0); //Do standart keys
}

HEADER_DESC txt_inp_hdr={0,0,0,0,NULL,(int)"Редактор",LGP_NULL};
INPUTDIA_DESC txt_inp_desc=
{
   1,
   txt_inp_onkey,
   empty_ghook,
   (void *)empty_locret,
   0,
	&empty_menu_skt,
  {2,44,239,239},//{0,0,0,0},
  FONT_SMALL,
  100,
  101,
  0,
  0x00000000,
  0x40000000
};



void TextInput(char *caption, char *prmpt, int TestFileName, WSHDR *wsname, IFN_RET_PROC retproc)
{
	txt_inp_hdr.lgp_id = (int)caption;
	txt_inp_proc = retproc;
	testfn = TestFileName;

	WSHDR *buff=AllocWS(320);

	void *ma=malloc_adr();
	void *eq=AllocEQueue(ma,mfree_adr());

	EDITCONTROL ec;//------------------------------------------------------------------------
	EDITCONTROL et;//------------------------------------------------------------------------
	PrepareEditControl(&ec);
	PrepareEditControl(&et);
	 ascii2ws(buff,  prmpt);//_tc,
//-----------------------------------------------------------------------------------------------
        // open_select_file_gui(ec, 0);

//-----------------------------------------------------------------------------------------------
	ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,buff,320);
        prep_hd(&ec);
	AddEditControlToEditQend(eq,&ec,ma);
//-----------------------------------------------------------------------------------------------
	ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_SET_CURSOR_END,wsname,2048);
	prep_inf(&ec);
	AddEditControlToEditQend(eq,&ec,ma);
//-----------------------------------------------------------------------------------------------
	ConstructEditControl(&et,ECT_HEADER,ECF_APPEND_EOL,buff,320);
	prep_hd(&et);
	AddEditControlToEditQend(eq,&et,ma);
//-----------------------------------------------------------------------------------------------
        patch_input(&txt_inp_desc);
        patch_header(&txt_inp_hdr);
	CreateInputTextDialog(&txt_inp_desc,&txt_inp_hdr,eq,1,0);
        ws = ec.pWS;

	FreeWS(buff);
}

