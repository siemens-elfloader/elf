#include <swilib.h>
#include <unistd.h>
#include <conf_loader.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>


/*
    Для отключение прямого вызова сви-функци добавьте дефайн __NO_DIRECT_SWI (Нужен пропатченный гцц)
    Может быть полезным если нужно уменьшить размер эльфа.
*/

GBSTMR tmr;


unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
const int minus11=-11;
int my_csm_id=0;

typedef struct
{
    CSM_RAM csm;
    int gui_id;
} MAIN_CSM;

typedef struct
{
    GUI gui;
    WSHDR *ws;
} MAIN_GUI;


/*------------------------------------------------------------------------*/
/*--------------------- Создание цсм процесса и гуя ----------------------*/
/*------------------------------------------------------------------------*/
char clrWhite[]= {0xFF,0xFF,0xFF,0x64};
char clrBlack[]= {0x00,0x00,0x00,0x64};
int scr_w,scr_h;

void DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);

  DrawObject(&drwobj);
}







IMGHDR scrfn={0,0,8,0};
void doscreen()
{
	char *ms= (char*)( (*(int*)0xA8EA9128));
	scrfn.w=145;
	scrfn.h=172;
	scrfn.bitmap=new unsigned char[scrfn.w*scrfn.h*2];
	memcpy(scrfn.bitmap, ms, scrfn.w*scrfn.h*2);
}
/*sleep function by Danil_e71*/

unsigned int sleep(unsigned int sec)
{
    TTime start,now;
    GetDateTime(0,&start);
    while(1)
    {
        GetDateTime(0,&now);
        unsigned int total_seconds=(now.hour-start.hour)*60*60;
        total_seconds+=(now.min-start.min)*60;
        total_seconds+=(now.sec-start.sec);
        if(total_seconds>=sec)return total_seconds;
    }
}

static void OnRedraw(MAIN_GUI *data)
{
 //   DrawRoundedFrame(0,0,scr_w,scr_h,0,0,0,clrBlack,clrWhite);

    wsprintf(data->ws, "sss");
//
   // DrawString(data->ws, 0,0,scr_w-1,scr_h-1,FONT_SMALL,2+32,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
}







static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
    data->ws = AllocWS(128);
    data->gui.state=1;
   // Draw(&tmr);
}

static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
    data->gui.state=0;
    FreeWS( data->ws );
}

static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
    data->gui.state=2;
    DisableIDLETMR();
#ifdef ELKA
    DisableIconBar(1);
#endif
}

static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
    if (data->gui.state!=2) return;
    data->gui.state=1;
}

static int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
    if ((msg->gbsmsg->msg==KEY_DOWN || msg->gbsmsg->msg==LONG_PRESS))
    {
        switch(msg->gbsmsg->submess)
        {
        case RIGHT_SOFT:
            return (1);

        case '5':DrwImg(&scrfn, 0,0, NULL,NULL);break;
        case '4':doscreen();DrawRoundedFrame(0,0,scr_w,scr_h,0,0,0,clrBlack,clrWhite);break;

        }
    }
    //REDRAW();

    return(0);
}

extern "C" void kill_data(void *p, void (*func_p)(void *));

int method8(void)
{
    return(0);
}
int method9(void)
{
    return(0);
}

const void * const gui_methods[11]=
{
    (void *)OnRedraw,
    (void *)onCreate,
    (void *)onClose,
    (void *)onFocus,
    (void *)onUnfocus,
    (void *)OnKey,
    0,
    (void *)kill_data,
    (void *)method8,
    (void *)method9,
    0
};


const RECT Canvas= {0,0,0,0};
static void maincsm_oncreate(CSM_RAM *data)
{
    scr_w=ScreenW()-1;
    scr_h=ScreenH()-1;
    MAIN_CSM *csm=(MAIN_CSM*)data;
    MAIN_GUI *main_gui = new MAIN_GUI;
    zeromem(main_gui,sizeof(MAIN_GUI));
    main_gui->gui.canvas=(RECT *)(&Canvas);
    main_gui->gui.methods=(void *)gui_methods;
    main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
    csm->csm.state=0;
    csm->csm.unk1=0;
    my_csm_id=csm->gui_id=CreateGUI(main_gui);
}

void ElfKiller(void)
{
    kill_elf();
}

static void maincsm_onclose(CSM_RAM *csm)
{
//delete socket;
   // GBS_StopTimer(&tmr);
  delete [] scrfn.bitmap;
    SUBPROC((void *)ElfKiller);
}

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
    MAIN_CSM *csm=(MAIN_CSM*)data;
    if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
    {
        csm->csm.state=-3;
    }

    return(1);
}


static const struct
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
        139,
        0
    }
};


void UpdateCSMname(void)
{
    wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"TestSocket");
}


int main(const char *exename, const char *fname)
{

    MAIN_CSM main_csm;
    LockSched();
    UpdateCSMname();
    CreateCSM(&MAINCSM.maincsm,&main_csm,0);
    UnlockSched();
    return 0;
}

