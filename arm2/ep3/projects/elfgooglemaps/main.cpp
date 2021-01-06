/*
* ГуглоКарты
* Danil_e71 2011-2012
* Работают через промежуточный php-скрипт
* Выводит карту по частям
* Многоязычность
*/

#include "include.h"
#include "string_works.h"

#include "cache/cache.h"
#include "draw/image.h"
#include "draw/draw.h"
#include "internet/internet.h"
#include "internet/utils.h"
#include "language/language.h"
#include "map/map.h"

const int minus11=-11;
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
int my_csm_id=0;
typedef struct
{
    CSM_RAM csm;
    int gui_id;
} MAIN_CSM;

typedef struct
{
    GUI gui;
    WSHDR *ws1;
    WSHDR *ws2;
    WSHDR *ws5;
    int i1;
} MAIN_GUI;

static void OnRedraw(MAIN_GUI *data)
{

    for(int j=0; j<MAP_Y; j++)
        for(int i=0; i<MAP_X; i++)
            DrwImg(map[i][j],i*cub,j*cub);

    switch(mode)
    {
    case 1:
        wsprintf(data->ws1, "%s %s:%d kb %s:%d", lgpData[LGP_LoadingMap].c_str(),
                 lgpData[LGP_Traffic].c_str(), all_traf/1024, lgpData[LGP_State].c_str(), connect_state);
        break;
    case 0:
        wsprintf(data->ws1, "%s %s:%d kb %s:%d", lgpData[LGP_PressAnyKey].c_str(),
                 lgpData[LGP_Traffic].c_str(), all_traf/1024,lgpData[LGP_State].c_str(), connect_state);
        break;
    case 2:
        wsprintf(data->ws1, "%s",lgpData[LGP_LoadingCache].c_str());
        break;
    }

    DrawString(data->ws1,0,0,ScreenW()-1,Get_WS_width(data->ws1,FONT),FONT,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));

    DrawRectangle(cur_x,cur_y,cur_x+cub,cur_y+cub,0,GetPaletteAdrByColorIndex(2),0);
}

static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
    memset(map, 0, sizeof(map));

#ifdef ELKA
    DisableIconBar(1);
#endif
    data->ws1=AllocWS(256);
    data->gui.state=1;
}

static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
    for(int j=0; j<MAP_Y; j++)
        for(int i=0; i<MAP_X; i++)
            FreeImg(map[i][j]);

    data->gui.state=0;
    FreeWS(data->ws1);
}

static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
#ifdef ELKA
    DisableIconBar(1);
#endif
    data->gui.state=2;
    DisableIDLETMR();
}

static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
#ifdef ELKA
    DisableIconBar(1);
#endif
    if (data->gui.state!=2) return;
    data->gui.state=1;
}

static void ShiftMap(int t)
{
    if(mode)return;

    Type=t;
    switch(Type)
    {
    case RIGHT:
        for(int j=0; j<MAP_Y; j++) //MAP_Y-1 рядов
            for(int i=0; i<MAP_X-1; i++) //последний ряд не трогаем MAP_X-2 рядов
                IMGHDR_cpy(map[i][j],map[i+1][j]);
        mapi=MAP_X-1;
        mapj=0;
        longitude=XToL(LToX(longitude) + (cub<<(21-zoom)));
        break;

    case LEFT:
        for(int j=0; j<MAP_Y; j++)
            for(int i=MAP_X-1; i>0; i--)
                IMGHDR_cpy(map[i][j],map[i-1][j]);
        mapi=0;
        mapj=0;
        longitude=XToL(LToX(longitude) + ((-cub)<<(21-zoom)));
        break;


    case UP:
        for(int j=MAP_Y-1; j>0; j--)
            for(int i=0; i<MAP_X; i++)
                IMGHDR_cpy(map[i][j],map[i][j-1]);
        mapi=0;
        mapj=0;
        latitude=YToL(LToY(latitude) + (-cub<<(21-zoom)));
        break;


    case DOWN:
        for(int j=0; j<MAP_Y-1; j++)
            for(int i=0; i<MAP_X; i++)
                IMGHDR_cpy(map[i][j],map[i][j+1]);
        mapi=0;
        mapj=MAP_Y-1;
        latitude=YToL(LToY(latitude) + (cub<<(21-zoom)));
        break;
    }
    sprintf(filename,"%s%s",elf_path,resource[LOAD_TILE]);
    FreeImg(map[mapi][mapj]);
    map[mapi][mapj]=CreateIMGHDRFromPng(filename);
    c();
}

static void cur(int i)
{

    switch(i)
    {
    case UP:
        if(cur_y>=cub)cur_y-=cub;
        else ShiftMap(i);
        break;


    case DOWN:
        if(cur_y<ScreenH()-cub)cur_y+=cub;
        else ShiftMap(i);
        break;

    case LEFT:
        if(cur_x>=cub)cur_x-=cub;
        else ShiftMap(i);
        break;


    case RIGHT:
        if(cur_x<ScreenW()-cub)cur_x+=cub;
        else ShiftMap(i);
        break;

    }
    DirectRedrawGUI();
}
/*
int openconf()//Для чтения настроек с конфига
{
extern const char *successed_config_filename;
WSHDR *fws=AllocWS(strlen(successed_config_filename)+1);
wsprintf(fws,"%t",successed_config_filename);
ExecuteFile(fws,NULL,NULL);
FreeWS(fws);
return 0;
}*/
static int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{

    switch(msg->gbsmsg->msg)
    {
    case KEY_UP:
        break;

    case KEY_DOWN:

        switch(msg->gbsmsg->submess)
        {
        case RIGHT_SOFT:
            return 1;
//         case LEFT_SOFT: openconf();break;
        case '5':
            if(mode==0)
            {
                if(zoom<19)zoom++;
                Type=RIGHT;
                mapi=0;
                mapj=0;
                c();
            }
            break;
        case '0':
            if(mode==0)
            {
                if(zoom> 0)zoom--;
                Type=RIGHT;
                mapi=0;
                mapj=0;
                c();
            }
            break;
        case GREEN_BUTTON:
            if(mode==0)
            {
                Type=RIGHT;
                mapi=0;
                mapj=0;
                latitude=0;
                longitude=0;
                my_latitude=0;
                my_longitude=0;
                c();
            }
            break;
        case '2':
        case UP_BUTTON:
            cur(UP);
            break;
        case '4':
        case LEFT_BUTTON:
            cur(LEFT);
            break;
        case '6':
        case RIGHT_BUTTON:
            cur(RIGHT);
            break;
        case '8':
        case DOWN_BUTTON:
            cur(DOWN);
            break;
        }
    }
    return(0);
}


extern "C" void kill_data(void *p, void (*func_p)(void *));

void method8() {
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
    (void *)method8,
    0
};








int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
    if(msg->msg == MSG_RECONFIGURE_REQ)
    {
        //extern const char *successed_config_filename;
        //  if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0){
        // InitConfig();
        // zoom=Zoom;
        //}
    }
    MAIN_CSM *csm=(MAIN_CSM*)data;
    if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
    {
        csm->csm.state=-3;
    }

    if (msg->msg==MSG_HELPER_TRANSLATOR)
    {

        if ((int)msg->data1==sock)
        {
            //Если наш сокет
            switch((int)msg->data0)
            {
            case ENIP_SOCK_CONNECTED:
                if (connect_state==1)
                {
                    //Если посылали запрос
                    c();

                }
                break;
            case ENIP_SOCK_DATA_READ:
                if (connect_state==2)

                    SUBPROC((void *)get_answer);
                //  get_answer();
                break;
            case ENIP_SOCK_REMOTE_CLOSED:
                //Закрыт со стороны сервера
                if (connect_state)
                    SUBPROC((void *)end_socket);
                //    end_socket();
                break;
            case ENIP_SOCK_CLOSED:
                //Закрыт вызовом closesocket
                break;
            }
        }
    }
    return (1);
}

const RECT Canvas= {0,0,0,0};
static void maincsm_oncreate(CSM_RAM *data)
{
    MAIN_CSM *csm=(MAIN_CSM*)data;
    MAIN_GUI *main_gui = new MAIN_GUI;
    zeromem(main_gui,sizeof(MAIN_GUI));
    main_gui->gui.canvas=(RECT *)(&Canvas);
    main_gui->gui.methods=(void *)gui_methods;
    main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
    csm->csm.state=0;
    csm->csm.unk1=0;
    my_csm_id=csm->gui_id=CreateGUI(main_gui);
    Type=RIGHT;
}


static void maincsm_onclose(CSM_RAM *csm)
{
//    GBS_DelTimer(&tmr);
    kill_elf();
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

static void UpdateCSMname(void)
{
    wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"ElfGoogleMaps");
}




int main()
{
// InitConfig();
    MAIN_CSM main_csm;
    LockSched();
    UpdateCSMname();
    CreateCSM(&MAINCSM.maincsm,&main_csm,0);
    UnlockSched();
    DrawInstall();
    return 0;
}


extern "C" void *__aeabi_memcpy(void *dst, void *src, size_t size) {
    return memcpy(dst, src, size);
}


