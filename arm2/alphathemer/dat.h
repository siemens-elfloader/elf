#define _WAIT		0
#define F_CACHE_DIR	2
#define F_PROF_PD	3
#define OTH_ERR		4

#define _OK			1

#define NOT_24	-2
#define W_FAIL	-1
#define W_FIN	0
#define W_INIT	2
#define W_WRT	3

const int tcd_[2]={0x68545c3a, 0x43656d65};


const char	/* CACHE_DIR_1[]="1:\\ThemeCache\\",
		CACHE_DIR_2[]="2:\\ThemeCache\\", */
		PROF_PD[]="1:\\system\\hmi\\profile.pd";
char c_dir[64],
	w_err=0,
	w_warn=0,
	compr=0,
	pos,
	sbpos=0,
	c_w,
	sb=0;


int state=0,
	rPD();

static IPC_REQ gipc;
static const char ipc_my_name[32]="AlfaThemer_3",
	#ifdef ELKA
		ccnt=19;
	#else
		ccnt=17;
	#endif

typedef struct
{
	char *nm, *pdnm, *fl, a;
	int nom;
}THEMECONF;

#define HEADLINE_STANDART        0x0
#define HEADLINE_FULLSCREEN      0x1
#define BODY_STANDART            0x2
#define BODY_TAB                 0x3
#define BOTTOM_STANDART          0x4
#define BOTTOM_FULLSCREEN        0x5
#define POPUP_OPTIONS            0x6
#define POPUP_FEEDBACK           0x7
#define SELECTION_1_LINE         0x8
#define SELECTION_2_LINE         0x9
#define SELECTION_3_LINE         0xA
#define SELECTION_ICON_ONLY      0xB
#define POPUP_SEARCH_LINE        0xC
#define POPUP_QUICK_ACCESS_FIELD 0xD
#define PROGRESS_STATUSBAR       0xE
#define TAB_SELECTED             0xF
#define TAB_UNSELECTED           0x10
#define STATUSBAR_STANDART       0x11
#define STATUSBAR_FULLSCREEN     0x12


THEMECONF c[]=
{
		{
			"background_picture_body_default",
			"Body_Standard_Bg_Image",
			"",
			0,
			BODY_STANDART
		},
		{
			"background_picture_body_tab",
			"Body_Tab_Bg_Image",
			"",
			0,
			BODY_TAB
		},
		{
			"background_picture_bottom_default",
			"Bottom_Standard_Bg_Image",
			"",
			0,
			BOTTOM_STANDART
		},
		{
			"background_picture_bottom_fullscreen",
			"Bottom_Fullscreen_Bg_Image",
			"",
			0,
			BOTTOM_FULLSCREEN
		},
		{
			"background_picture_feedback_popup",
			"Popup_Feedback_Bg_Image",
			"",
			1,
			POPUP_FEEDBACK
		},
		{
			"background_picture_headline_default",
			"Headline_Standard_Bg_Image",
			"",
			0,
			HEADLINE_STANDART
		},
		{
			"background_picture_headline_fullscreen",
			"Headline_Fullscreen_Bg_Image",
			"",
			0,
			HEADLINE_FULLSCREEN
		},
		{
			"background_picture_options_popup",
			"Popup_Options_Bg_Image",
			"",
			1,
			POPUP_OPTIONS
		},
		{
			"background_picture_quickaccessfield_popup",
			"Popup_Quick_Access_Field_Bg_Image",
			"",
			1,
			POPUP_QUICK_ACCESS_FIELD
		},
		{
			"background_picture_searchfield_popup",
			"Popup_Search_Line_Bg_Image",
			"",
			1,
			POPUP_SEARCH_LINE
		},
		{
			"background_picture_selection_list",
			"Selection_1_Line_Bg_Image",
			"",
			1,
			SELECTION_1_LINE
		},
		{
			"background_picture_selection_2lines",
			"Selection_2_Line_Bg_Image",
			"",
			1,
			SELECTION_2_LINE
		},
		{
			"background_picture_selection_3lines",
			"Selection_3_Line_Bg_Image",
			"",
			1,
			SELECTION_3_LINE
		},
		{
			"background_picture_selection_icon",
			"Selection_Icon_Only_Bg_Image",
			"",
			1,
			SELECTION_ICON_ONLY
		},
		{
			"progressbar",
			"Progress_Statusbar_Image",
			"",
			1,
			PROGRESS_STATUSBAR
		},
	#ifdef ELKA
		{
			"statusbar_fullscreen",
			"Statusbar_Fullscreen",
			"",
			0,
			STATUSBAR_FULLSCREEN
		},
		{
			"statusbar_standard",
			"Statusbar_Standard",
			"",
			0,
			STATUSBAR_STANDART
		},
	#endif
		{
			"tabulator_background_selected",
			"Tab_Selected_Bg_Image",
			"",
			1,
			TAB_SELECTED
		},
		{
			"tabulator_background_unselected",
			"Tab_Unselected_Bg_Image",
			"",
			1,
			TAB_UNSELECTED
		}
};



