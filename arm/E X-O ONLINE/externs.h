#define FONT_ATR 32


extern void NullTableXod(),
            AntiXod(),
            KompXod(),
            NGame(),
            DrwImg(IMGHDR *img, int x, int y),
            DrawXorO(int flag,int x_p, int y_p),
            FringFig(int flag),
            WRITE_xod(int flag, int x, int y),
            Write_XOD(int flag),
            OXod(int flag),
            NullGame(),
            create_connect(void),
            ClearSendQ(void),
            end_socket(void),
            FreeCLIST(void),
            TimeGame(),
            GAME_MENU_GUI(),
                       DrRF_R_U(int flag,int x,int y),
           DrRF_R_D(int flag,int x,int y),
           DrRF_DOWN(int flag,int x, int y),
                      DrRF_LEFT(int flag,int x, int y),
            Seng_Msg(),
            SMART_REDRAW(void),
            ShowRecMSG(char *recmsg),
            DoFring(),
            QuestResGame(),
            AnswerResGame(int decision),
            AnswerExitGame(int decision),
            AnswerNewGame(int decision),
            ShowWMSG(int flag, const char* msg, int font, const char* foncolor, const char* fringcolour, int ena),
            InitParametres(),
            DoXod(),
            DoInvertXod(),
            RestoreGame(),
            CloseGame(),
            ResumeGame();
extern  void WRITE_STEP(int flag);
extern const char PICTURES_PATH[128],
                  perc_t[],
                  perc_d[],
                  perc_tt[],
                  perc_td[],
                  perc_tdt[],
                  perc_tdtd[],
                  perc_t0dd[],
                  perc_tdtdt[],
                 // perc_tdtdtd[],
                  mda_perc_tdtdtd[],
                  PASS[];

extern int scr_w,
           scr_h,
           TableXod [7][8],
           IsMenu,   
           NewGame,          
           end_game,         
           MODE_GAME,   
           MODE_FIGURE,
           theme_tick,     
           theme_time,       
           game_time_m_sec,
           ena_two_g,
           nich,
           x_n_poz , 
           y_n_poz,
           IsLoadGraph,
           img_count,
           draw_logo,
           ena_one_g,
           IsConnectProcess,
           Online2xod,
           Online1xod,
           connect_state,
           sock,
           eDrawInfo,
           POZ_MENU_CUR,
           exit_ungraf,
           //game_cur_x,
           //game_cur_y,
           //cur_y,
           DrawGameMenu,
           DrawXoid,
           DrawOoid,
           X_LOGO,
           Y_LOGO,
           X_MENU_CURSOR,
           count_gamer_num_1,
           count_gamer_num_2,
           summ_count1,
           summ_count2,
           isDrawFring,
           i_count,
           OnlainGameXod,
           Quit_Game_Giu,
           SetFigure,
           y_s_n_g,
           m_x,
           DNR_TRIES;
           
extern volatile int disautorecconect,
                    SENDMSGCOUNT;

extern int count, 
           x_n_poz, 
           y_n_poz,
           Y_POZ_GMC,
           POZ_GMC,
           IsOnLineGame,

           WriteMsg(),
           A_I(int flag, int anti_flag),
           A_I2(int flag, int anti_flag),
           RandXod(int anti_flag),
           SendQuest(char *quest, int flag),

           SendXod(int x, int y);

extern char FON_COLOR[4],
            black0[4],
            black10[4],
            black30[4],
            black40[4],
            grey0[4],
            grey20[4],
            FON_M_CURSOR[4],
            FON_FRINF[4];

extern IMGHDR *images[7];

extern GBSTMR timer,
              TMR_drive_set,
              load_img,
              tmr_active,
              
              reconnect_tmr;

extern const unsigned int UIN,
                          UIN_2;

extern const int ena_vibr,
                 FONT;

extern unsigned int MAINCSM_ID,
                    MAINGUI_ID;
#define IPC_EXO_NAME "E X-O"
#define IPC_TENSECONDS 4
