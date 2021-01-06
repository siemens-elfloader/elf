const char perc_t[]="%t";
const char perc_d[]="%d";
const char perc_tt[]="%t%t";
const char perc_td[]="%t%d";
const char perc_tdt[]="%t%d%t";
const char perc_tdtd[]="%t%d%t%d";
const char perc_tdtdt[]="%t%d%t%d%t";
const char mda_perc_tdtdtd[]="%t%d%t%d%t%d";
const char perc_t0dd[]="%t%0d%d%";

char FON_COLOR[4]={0xa9,0xa5,0xa5,100},
     FON_M_CURSOR[4]={0xdc,0xd9,0xd9,100},
     FON_FRINF[4]={0xff,0,0,40};

char black0[]={0,0,0,60},
     black10[]={0,0,0,10},
     black30[]={0,0,0,30},
     black40[]={0,0,0,40},
     grey0[]={0xff,0xff,0xff,50},
      grey20[]={0xff,0xff,0xff,20},
		red[]={0xff,0,0,100},
		white[]={0xff,0xff,0xff,100},
		white0[]={0xff,0xff,0xff,50};

GBSTMR timer,
       load_img;
#ifdef ELKA
int y_s_n_g=320/4;
int Y_POZ_GMC=320/2, POZ_GMC=1;
#else
int y_s_n_g=176/4;
int Y_POZ_GMC=176/2, POZ_GMC=1;
#endif
int scr_w,
    scr_h,
    IsMenu=1,           // Меню ( 1- Активировано, 0 - Закрыто)
    NewGame=0,          // Новая игра ( 1- Начата, 0 - Не начата)
    end_game=0,         // Конец игры ( 1- Конец, 0 - Не конец )
    MODE_GAME=1,        // 1 - Одиночная, 2 - Два игрока, 3 - Он-лайн игра
    MODE_GAME_M_CURSOR=1,  // 1 - Отключиться
    MODE_FIGURE=1,         // 1 - Крестиком , 2 - Ноликом
    theme_tick=0,       // Тики таймера для времени
    theme_time=0,       // Секунды
    game_time_m_sec=0,  // Минуты
    ena_two_g=1,
    nich=0,
    x_n_poz=3 , 
    y_n_poz=5,
    IsLoadGraph=1,
    img_count,
    IsOnLineGame,
    draw_logo=1,
    ena_one_g=1,
    IsConnectProcess=0,
    Online2xod=1 , 
    Online1xod=0,
    DrawGameMenu=0,
    X_LOGO,
    Y_LOGO,
    X_MENU_CURSOR,
    count_gamer_num_1=0,
    count_gamer_num_2=0,
    summ_count1=1,
    summ_count2=1,
    isDrawFring=0,
    OnlainGameXod=0,
    Quit_Game_Giu=0,
    ShowREC_MSG=0,
    SetFigure=0,
    m_x=15,
    POZ_MENU_CUR=1;     // Позиция курсора в меню ( 1 -  Начать игру , 2 Режим игры, 3 - Настройки , 4 - Информация о эльфе, 5 - Выход )

