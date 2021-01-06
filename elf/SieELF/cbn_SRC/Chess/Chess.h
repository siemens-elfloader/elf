
#include "..\random.h"
#include "gai.h"    

// type = (new UniversalMenu().GetPromotionType()); НУЖНО!!!!!!
//FAKES here !!!
//    int m_rnd;
//    int m_rnd_nextInt(){ //random FAKE!!!
//      return Random();
//    }
    inline int abs(int a){ return(a<0)?-a:a;}
    inline int min(int a, int b){ return(a<b)?-a:b;}
    inline int max(int a, int b){ return(a>b)?-a:b;}
    void historyViewer_Clear(){}
//    boolean GlobalAI_CanMove(int from, int to){ return false;} 
  
    int wl[34],bl[34]; 
    
    /* power table */
    short P[120];
    int *pf, *xpf, wpf[10], bpf[10]; /* # of w&b pawns on a file */
    int *b;


//const from GLOBALAI!
    const char* difficultyNames[] = {"Very Easy", "Easy", "Normal 1", "Normal 2", "Hard", "Very Hard"};
    const int TAKEN=7;
    const short TEMPO = 4;


struct GlobalAIst GlobalAI; 
    
struct MOVE tm, nm, tmpmove, tmpMove, move;

#define histlength 50

struct HIST          /*Запись в массиве истории*/
{
    struct MOVE      m;   /*Совершённый ход*/
    byte             cap; /*Какую при этом фигуру взяли*/
    byte castling;   /*Состояние возможностей рокировок на момент после совершённого хода*/
    byte repetition; /*Сколько ходов подряд уже идёт повторение*/
    
    int xmtrl, mtrl;/*Ценность материала у текущей стороны, у противоположной стороны*/
    byte enpas;      /*Через эту клетку прыгала пешка (для EnPasant)*/
}   hist[histlength]; //200     /*История игры*/;

struct Know
{
    short hung, khung, kshield;
    byte p, n, b, r, q;
    byte kp, r7r;
    boolean prune;             /* is it ok to prune search in this pos ? */
    byte kstorm, qstorm;    /* diffside castling: king attack q/k side */
    byte devel;           /* development needed?, 0 ... no */
    short castling;
    byte bishopcolor,     /* square color of friendly bishops, or-red */
    xbishopcolor;     /* square color of enemy bishops */
    byte worsebm;           /* mobility of the worse bishop */
    byte lpf, rpf;        /* leftmost/rightmost pawn file */
}  Wknow, Bknow, know, xknow;

//class G_AI
//{
    int OK_count=0;

     const short RANDOMIZER_WINDOW=3;

     int easy;   /*Пока не используется*/
     int total_ply;  /*На сколько всего полуходов перебирать*/
     int quescence_ply;  /*Сколько из них "полных"*/

#define MMAXPLY 14
int MAXPLY=12;
     
#define  PAWN    0x10
#define  KNIGHT  0x20
#define  BISHOP  0x30
#define  ROOK    0x40
#define  QUEEN   0x50
#define  KING    0x60

#define  EMPTY   0
#define  WHITE   1
#define  BLACK   2

	/*Константы для рокировки*/
#define WSHORT 1
     /*Если выставлен флаг WSHORT - значит короткая рокировка белых запрещена*/
#define WLONG  2
        /*Аналогично...*/
#define BSHORT 4
#define BLONG  8

#define	WP  (1|0x10) 
     //WHITE|PAWN;
#define	WN  (1|0x20)
     //WHITE|KNIGHT;
#define	WB  (1|0x30)
     //WHITE|BISHOP;
#define	WR  (1|0x40)
     //WHITE|ROOK;
#define WQ  (1|0x50)
     //WHITE|QUEEN;
#define WK  (1|0x60)
     //WHITE|KING;

#define	BP  (2|0x10)
     //BLACK|PAWN;
#define BN  (2|0x20)
     //BLACK|KNIGHT;
#define BB  (2|0x30)
     //BLACK|BISHOP;
#define BR  (2|0x40)
     //BLACK|ROOK;
#define BQ  (2|0x50)
     //BLACK|QUEEN;
#define BK  (2|0x60)
     //BLACK|KING;

	/*Это для оценочной функции только, какие-то флаги...*/
     const short WPM = 0x0001;
     const short WNM = 0x0002;
     const short WBM = 0x0004;
     const short WRM = 0x0008;
     const short WQM = 0x0010;
     const short WWW = 0x0020;

     const short BPM = 0x0100;
     const short BNM = 0x0200;
     const short BBM = 0x0400;
     const short BRM = 0x0800;
     const short BQM = 0x1000;
     const short BBB = 0x2000;


#define FILE_A 1
     const short FILE_B =2;
     const short FILE_C =3;
     const short FILE_D =4;
     const short FILE_E =5;
     const short FILE_F =6;
     const short FILE_G =7;
#define FILE_H 8

     const byte
    A1=21, B1=22, C1=23, D1=24, E1=25, F1=26, G1=27, H1=28,
    A2=31, B2=32, C2=33, D2=34, E2=35, F2=36, G2=37, H2=38,
    A3=41, B3=42, C3=43, D3=44, E3=45, F3=46, G3=47, H3=48,
    A4=51, B4=52, C4=53, D4=54, E4=55, F4=56, G4=57, H4=58,
    A5=61, B5=62, C5=63, D5=64, E5=65, F5=66, G5=67, H5=68,
        A6=71, B6=72, C6=73, D6=74, E6=75, F6=76, G6=77, H6=78,
    A7=81, B7=82, C7=83, D7=84, E7=85, F7=86, G7=87, H7=88,
    A8=91, B8=92, C8=93, D8=94, E8=95, F8=96, G8=97, H8=98, H9=99;

    /*Как ходит конь*/
     short N_moves[] = { -21, -19, -12, -8, 21, 19, 12, 8 };
	/*Направляющие ходьбы для ладьи, слона, ферзя, короля*/
     short RB_dirs[] = { 1, -1, 10, -10, 11, -11, 9, -9 };
     short *K_moves = RB_dirs;

     const short	MATE            =30000;
     const short	CHECKMATE            =30000;

	/*Ценность фигур*/
#define  P_VALUE  100
#define  N_VALUE  350
#define  B_VALUE  350
#define  R_VALUE  550
#define  Q_VALUE  1050
#define  K_VALUE  30000
     //MATE;
     int Values[] = { 0, 100,350,350,550,1050,0};
     //P_VALUE, N_VALUE, B_VALUE, R_VALUE, Q_VALUE, 0 };


	/*Здесь хранится доска.  Формат 10x12.*/
	 int B[] = {
        3,  3,  3,  3,  3,  3,  3,  3,  3,  3,
        3,  3,  3,  3,  3,  3,  3,  3,  3,  3,
       3, WR, WN, WB, WQ, WK, WB, WN, WR,  3, //!!!!!!!!!!!!!1
       3, WP, WP, WP, WP, WP, WP, WP, WP,  3,
        3,  0,  0,  0,  0,  0,  0,  0,  0,  3,
        3,  0,  0,  0,  0,  0,  0,  0,  0,  3,
        3,  0,  0,  0,  0,  0,  0,  0,  0,  3,
        3,  0,  0,  0,  0,  0,  0,  0,  0,  3,
        3, BP, BP, BP, BP, BP, BP, BP, BP,  3,
        3, BR, BN, BB, BQ, BK, BB, BN, BR,  3,
        3,  3,  3,  3,  3,  3,  3,  3,  3,  3,
        3,  3,  3,  3,  3,  3,  3,  3,  3,  3,
         
    };
	/*"Референсная" копия стартовой доски, чтобы её выставлять когда надо заново игру начать*/

    const int ref_B[] = {
        3,  3,  3,  3,  3,  3,  3,  3,  3,  3,
        3,  3,  3,  3,  3,  3,  3,  3,  3,  3,
        3, WR, WN, WB, WQ, WK, WB, WN, WR,  3,
        3, WP, WP, WP, WP, WP, WP, WP, WP,  3,
        3,  0,  0,  0,  0,  0,  0,  0,  0,  3,
        3,  0,  0,  0,  0,  0,  0,  0,  0,  3,
        3,  0,  0,  0,  0,  0,  0,  0,  0,  3,
        3,  0,  0,  0,  0,  0,  0,  0,  0,  3,
        3, BP, BP, BP, BP, BP, BP, BP, BP,  3,
        3, BR, BN, BB, BQ, BK, BB, BN, BR,  3,
        3,  3,  3,  3,  3,  3,  3,  3,  3,  3,
        3,  3,  3,  3,  3,  3,  3,  3,  3,  3,
    };

	/*Ходы с/на какие поля запрещают какие рокировки*/
     const byte cb[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, WLONG, 0, 0, 0, (WSHORT|WLONG), 0, 0, WSHORT, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, BLONG, 0, 0, 0, (BSHORT|BLONG), 0, 0, BSHORT, 0
    };


    /*Текущая сторона*/
     int             Color=1;//WHITE;           /* side to move, value = BLACK or WHITE */

    /*Возможные типы ходов*/
#define MOVE_TYPE_NONE                  0
#define MOVE_TYPE_NORMAL                1
#define MOVE_TYPE_CASTLE                2
#define MOVE_TYPE_ENPASANT              3  /*Прыжок пешки "через один"*/
#define MOVE_TYPE_ENPASTAKE             10/*Собственно, взятие "на проходе"*/
#define MOVE_TYPE_PROMOTION_TO_QUEEN    4
#define MOVE_TYPE_PROMOTION_TO_ROOK     5
#define MOVE_TYPE_PROMOTION_TO_BISHOP   6
#define MOVE_TYPE_PROMOTION_TO_KNIGHT   7

    /*Массив, хранящий списки, где стоят фигуры.*/
     struct MOVE L[120];
	/*Устроен нетривиально.

	По размеру L[] совпадает с B[], оба по 120 элементов.

	L[1] всегда ранит в своём .dest координату, где стоит на доске белый король.
	Пусть по началу он (король) стоит на "25".   L[1].dest==25.
	Тогда L[25].dest - это координата следующей (любой) белой фиругы.
	L[ L[25].dest ].dest - координата далее следующей белой фигуры, и т.п.

	Аналогично, L[2].dest - позиция чёрного короля.*/


	/*Массивы "пришпиленных" фигур и, кажется, "атакуемых" фигур*/
     byte pin[120];
     byte tar[120];

    /*Кеш, где хранятся ходы, вызывавшие бета-отсечение. По два хода на каждый уровень глубины (ply)*/
	 struct MOVE killers[MMAXPLY][2];

    /*Здесь хранятся сгенерированные ходы, по 120 штук на каждый ply*/
	 struct MOVE mvs[MMAXPLY][120];
	/*А здесь хранятся текущие значения этих ходов (наскольок они хороши)*/
     int mvls[MMAXPLY][120];

    /*Какие-то списки для функции see()*/
     int see_wl[16];
     int see_bl[16];
     int backup;


     int             hdp;      /*Индекс текущего хода в истории игры.
				Совершаемый ход пишется в hist[hdp],  совершённый доступен через hist[hdp-1].*/

     int            nodes;       /*Счётчик обсчитанных узлов (нужно только для отладки и статистики)*/
     int num_mades=0;  /*Отладочный счётчик совершённых ходов. Можно все упоминания о нём удалить*/

	 int Ply=0;                  /*На какой глубине мы в данный момент находимся*/

     int pMCount; /*Количество сгенерированных ходов на данном уровне.*/

    /*Стоит ли сейчас шах*/
	 boolean check;

	/*Количество "корневых" ходов. "Корневые" - то есть, ходы, из которых реально придётся выбирать.
		То есть вот есть позиция, движок начал думать. У него есть корневые ходы, он среди них и выбирает.*/
     int root_moves_num;

	/*Тут  мы сохраняем позиционную оценку.
	Если на глубоких уровнях мы решим позиционную оценку не пересчитывать - то просто берём оценку предыдущих уровней*/
     int psnl[MMAXPLY];

     //MOVE PV[];

	/*Затычка для того, чтобы её в Search() передать, она туда вернёт лучший найденный ход.
		Он нас не интересует, поэтому - просто "затычка"*/
	 struct MOVE fucked_move;//=new MOVE();
         
         struct MOVE best_move;//=new MOVE();

	/*Строка, куда можно что-то записать, а потом, при желании, вывести на экран. Можно смело удалять*/
	char *nt=0;
         
        int nummove=0;
        long seed=0;

	/*Инициализация/сброс. В начале, а так же когда хотим начать игру заново - надо эту ф-ию вызывать*/
    /*ПОЗИЦИОННАЯ ОЦЕНКА.................................*/

    /**
     ***   If the material value is between ENDMATERIAL and MIDMATERIAL,
     ***   Phalanx utes both eevndgame and middlegame evaluation.
     ***   The evaluation is proportionally computed from these two values.
     **/
     const short ENDMATERIAL = 3000; /* minimum is 0 */
     const short MIDMATERIAL = 6000; /* maximum is 8600 */

     int Totmat;

     const int DrawScore = -20;
    /* isolated pawn penalty by rank */
     const short isofile[] =
    { 0, -4, -6, -8, -10, -10, -8, -6, -4, 0 };
    /***  A   B   C    D    E   F   G   H  ***/

    /*** Square color ***/
     const byte sqcolor[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 2, 1, 2, 1, 2, 1, 2, 1, 0,
        0, 1, 2, 1, 2, 1, 2, 1, 2, 0,
        0, 2, 1, 2, 1, 2, 1, 2, 1, 0,
        0, 1, 2, 1, 2, 1, 2, 1, 2, 0,
        0, 2, 1, 2, 1, 2, 1, 2, 1, 0,
        0, 1, 2, 1, 2, 1, 2, 1, 2, 0,
        0, 2, 1, 2, 1, 2, 1, 2, 1, 0,
        0, 1, 2, 1, 2, 1, 2, 1, 2, 0
    };

     const byte central[]= {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, -1, 0, 0, 0, 0, 0, 0, -1, 0,
        0, 0, 0, 1, 2, 2, 1, 0, 0, 0,
        0, 0, 1, 2, 3, 3, 2, 1, 0, 0,
        0, 1, 3, 4, 5, 5, 4, 3, 1, 0,
        0, 2, 4, 5, 7, 7, 5, 4, 2, 0,
        0, 2, 4, 5, 7, 7, 5, 4, 2, 0,
        0, 1, 3, 4, 5, 5, 4, 3, 1, 0,
        0, 0, 1, 2, 3, 3, 2, 1, 0, 0,
        0, 0, 0, 1, 2, 2, 1, 0, 0, 0,
        0, -1, 0, 0, 0, 0, 0, 0, -1, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    /*** Pawn in middlegame ***/
     const byte pmpb[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  2,  3,  4,  6,  6,  4,  3,  2,  0,
        0,  0,  1,  5,  8,  8,  5,  1,  0,  0,
        0,  0,  1,  6, 16, 12,  6,  1,  0,  0,
        0,  1,  5,  7, 16, 12,  7,  5,  1,  0,
        0,  5,  8, 10, 16, 12, 10,  8,  5,  0,
        0,  5,  5,  5,  6,  6,  5,  5,  5,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };

    /*** queenside pawn attack ***/
     const byte qstormtable[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,-12,-12,-12,  0,  0, 10, 10, 10,  0,
        0, -9,-10, -9,  0,  6,  8,  8,  8,  0,
        0, -6, -6, -6,  6, 10,  4,  4,  4,  0,
        0, -3, -3, -3, 10,  4,  0,  0,  0,  0,
        0,  0,  0,  5,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };

    /*** kingside pawn attack ***/
     const byte kstormtable[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0, 10, 10, 10,  0,  0,-12,-12,-12,  0,
        0,  8,  8,  8,  6,  0, -9,-10, -9,  0,
        0,  4,  4,  4, 10,  6, -6, -6, -6,  0,
        0,  0,  0,  0,  4, 10, -3, -3, -3,  0,
        0,  0,  0,  0,  0,  0,  5,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };

    /*** knight in middlegame ***/
     const byte nmpb[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,-16,-10, -8, -8, -8, -8,-10,-16,  0,
        0,-10, -3,  1,  3,  3,  1, -3,-10,  0,
        0, -8,  1,  5,  5,  5,  5,  1, -8,  0,
        0, -8,  2,  5,  8,  8,  5,  2, -8,  0,
        0, -8,  4,  6, 10, 10,  6,  4, -8,  0,
        0, -8,  4,  7,  8,  8,  7,  4, -8,  0,
        0,-10,  0,  3,  4,  4,  3,  0,-10,  0,
        0,-16,-10, -8, -8, -8, -8,-10,-16,  0
    };

    /*** bishop in middlegame ***/
     const byte bmpb[] = {
        0,  0,   0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,   0,  0,  0,  0,  0,  0,  0,  0,
        0,  10,  8,  6,  4,  4,  6,  8, 10,  0,
        0,   8, 12,  8,  9,  9,  8, 12,  8,  0,
        0,  10, 10, 11, 11, 11, 11, 10, 10,  0,
        0,  11, 12, 13, 14, 14, 13, 12, 11,  0,
        0,  12, 13, 15, 17, 17, 15, 14, 12,  0,
        0,  13, 14, 16, 16, 16, 16, 14, 13,  0,
        0,  11, 14, 12, 12, 12, 12, 14, 11,  0,
        0,  13, 10, 10, 10, 10, 10, 10, 13,  0
    };

    /*** bishop in endgame ***/
     const byte bepb[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0, 24, 21, 18, 15, 15, 18, 21, 24,  0,
        0, 21, 24, 21, 18, 18, 21, 24, 21,  0,
        0, 18, 21, 24, 24, 24, 24, 21, 18,  0,
        0, 15, 18, 24, 30, 30, 24, 18, 15,  0,
        0, 15, 18, 24, 30, 30, 24, 18, 15,  0,
        0, 18, 21, 24, 24, 24, 24, 21, 18,  0,
        0, 21, 24, 21, 18, 18, 21, 24, 21,  0,
        0, 24, 21, 18, 15, 15, 18, 21, 24,  0
    };

    /*** rook in middlegame ***/
     const byte rmpb[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  1,  2,  3,  3,  2,  1,  0,  0,
        0,  0,  1,  2,  3,  3,  2,  1,  0,  0,
        0,  0,  1,  2,  3,  3,  2,  1,  0,  0,
        0,  0,  1,  2,  3,  3,  2,  1,  0,  0,
        0,  0,  1,  2,  3,  3,  2,  1,  0,  0,
        0,  7,  8,  9, 10, 10,  9,  8,  7,  0,
        0, 10, 11, 12, 13, 13, 12, 11, 10,  0,
        0, 10, 11, 12, 13, 13, 12, 11, 10,  0
    };

    /*** queen in middlegame ***/
     const byte qmpb[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  1,  2,  3,  3,  2,  1,  0,  0,
        0,  4,  5,  6,  7,  7,  6,  5,  4,  0,
        0,  5,  6,  7,  8,  8,  7,  6,  5,  0,
        0,  6,  7,  8,  9,  9,  8,  7,  6,  0,
        0,  8,  9, 10, 11, 11, 10,  9,  8,  0,
        0, 10, 11, 12, 13, 13, 12, 11, 10,  0,
        0,  8, 10, 11, 12, 12, 11, 10,  8,  0,
        0,  5,  6,  7,  8,  8,  7,  6,  5,  0
    };

    /*** king in middlegame ***/
     const byte kmpb[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0, -3, -6, -6, -3,  0,  0,  0,
        0, -2, -4, -8,-12,-12, -8, -4, -2,  0,
        0, -6,-12,-20,-25,-25,-20,-12, -6,  0,
        0,-15,-20,-30,-40,-40,-30,-20,-15,  0,
        0,-30,-40,-50,-60,-60,-50,-40,-30,  0,
        0,-35,-45,-55,-65,-65,-55,-45,-35,  0,
        0,-30,-40,-50,-60,-60,-50,-40,-30,  0,
        0,-20,-30,-40,-50,-50,-40,-30,-20,  0
    };

    /*** king in endgame ***/
     const byte kepb[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0, -5,  5, 10, 15, 15, 10,  5, -5,  0,
        0,  6, 11, 16, 21, 21, 16, 11,  6,  0,
        0, 12, 17, 22, 27, 27, 22, 17, 12,  0,
        0, 18, 24, 30, 34, 34, 28, 24, 18,  0,
        0, 20, 27, 33, 48, 48, 33, 27, 20,  0,
        0, 16, 25, 34, 40, 40, 34, 25, 16,  0,
        0,  9, 20, 28, 35, 35, 28, 20,  9,  0,
        0,  3, 10, 17, 24, 24, 17, 10,  3,  0,
    };

    /*** knight in endgame ***/
     const byte c_bonus[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,-16,-10, -6, -2, -2, -6,-10,-16,  0,
        0, -9, -3,  1,  4,  4,  1, -3, -9,  0,
        0, -4,  1,  5,  8,  8,  5,  1, -4,  0,
        0,  0,  4,  8, 12, 12,  8,  4,  0,  0,
        0,  1,  5,  9, 13, 13,  9,  5,  1,  0,
        0, -2,  2,  6,  9,  9,  6,  2, -2,  0,
        0, -6, -1,  2,  5,  5,  2, -1, -6,  0,
        0, -9, -6, -3,  0,  0, -3, -6, -9,  0
    };

     const byte outpost[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 1, 2, 2, 1, 0, 0, 0,
        0, 0, 1, 2, 3, 3, 2, 1, 0, 0,
        0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

     int *l, wl[/*34*/], bl[/*34*/];   /* w&b piece Lst. Indexes to B[] (mB[]) */
     int n, wn, bn;

    /* mirrored board */
     int mB[] =
    { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
      3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
      3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
      3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
      3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
      3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
      3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
      3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };

       int mBinit[] =
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
        3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
        3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
        3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
        3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
        3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
        3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
        3, 0, 0, 0, 0, 0, 0, 0, 0, 3 };

         byte m[] =
        { 0,   0,   0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,
          0, 0x0, 0x0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,
          0, 0x1, 0x1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,
          0, 0x1, 0x1, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,
          0, 0x7, 0x7, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,
          0, 0xF, 0xF, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0,
          0, 0xF, 0xF, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0 };

           byte Th[] = {
              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
              0, 91, 92, 93, 94, 95, 96, 97, 98,  0,
              0, 81, 82, 83, 84, 85, 86, 87, 88,  0,
              0, 71, 72, 73, 74, 75, 76, 77, 78,  0,
              0, 61, 62, 63, 64, 65, 66, 67, 68,  0,
              0, 51, 52, 53, 54, 55, 56, 57, 58,  0,
              0, 41, 42, 43, 44, 45, 46, 47, 48,  0,
              0, 31, 32, 33, 34, 35, 36, 37, 38,  0,
              0, 21, 22, 23, 24, 25, 26, 27, 28,  0
          };
           byte Tv[] = {
              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
              0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
              0, 28, 27, 26, 25, 24, 23, 22, 21,  0,
              0, 38, 37, 36, 35, 34, 33, 32, 31,  0,
              0, 48, 47, 46, 45, 44, 43, 42, 41,  0,
              0, 58, 57, 56, 55, 54, 53, 52, 51,  0,
              0, 68, 67, 66, 65, 64, 63, 62, 61,  0,
              0, 78, 77, 76, 75, 74, 73, 72, 71,  0,
              0, 88, 87, 86, 85, 84, 83, 82, 81,  0,
              0, 98, 97, 96, 95, 94, 93, 92, 91,  0
          };
          
          byte gon_na_G6[] = 
          {
              0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
              0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
              
              0,  1,  2,  3,  4,  4,  4,  5,  5,    0,              
              0,  2,  4,  6,  7,  9,  9,  9,  9,    0,
              0,  3,  6,  8, 10, 10, 11, 13, 11,    0,              
              0,  4,  6,  8, 10, 12, 14, 18, 16,    0,
              0,  3,  5,  8, 12, 14, 25, 30, 30,    0,
              0,  3,  5,  7,  9,  5, 10, 45, 45,    0,              
              0,  2,  3,  5,  6,  8,  9, 10,  2,    0,              
              0,  1,  2,  3,  4,  5,  6,  2,  1,    0,
          };
              

                   /* table for king bishop knight endings */
                    const short nb[] = {
                       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                       0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                       0,100, 90, 80, 70, 60, 50, 40, 30,  0,
                       0, 90, 80, 70, 57, 45, 32, 20, 40,  0,
                       0, 80, 70, 50, 37, 23, 10, 32, 50,  0,
                       0, 70, 57, 37, 10,  0, 23, 45, 60,  0,
                       0, 60, 45, 23,  0, 10, 37, 57, 70,  0,
                       0, 50, 32, 10, 23, 37, 50, 70, 80,  0,
                       0, 40, 20, 32, 45, 57, 70, 80, 90,  0,
                       0, 30, 40, 50, 60, 70, 80, 90,100,  0
                   };

           const byte rfip[] =
          { 0, -2, -3, -4, -5, -5, -4, -3, -2, 0 };


           const byte B_mobi[] =
          { -36, -28, -20, -14, -6, -2, 1, 2, 3, 4, 5, 6, 7, 8, 8, 8, 8, 8, 8, 8 };
           const byte R_mobi[] =
          { -9, -5, -2, 0, 2, 4, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
          const byte P_advance[] =
          {  0,  0,  0, 10, 15, 25, 40, 60, 95,  0,  0,  0 };
           const byte frb[] =
          { 0, 0, -5, -5, -2, 0, 2, 4, 8, 10, 10, 10 };
           const byte bon_1[] =
          { 5, 3, 1, -2, -2, -2, -2, -2 };
           const byte bon_2[] =
          { 8,  8,  8,  7,  5,  3,  1,  0,
            -1, -2, -3, -4, -5, -6, -7, -8 };
             const byte bon_4[] =
            { 8, /* 1-st entry is never used */
              8, 8, 5, 2, -1, -4, -7 };
               const byte bon_5[] =
              { 10, 10, 10,  9,  7,  5,  3,  0,
                -2, -4, -8, -8, -8, -8, -8, -8 };
                const byte Oppb[] =  /* outside passed pawn bonus */
                /*       +10  +8  +6  +4             */
                {  0,  0, 40, 50, 58, 64, 68, 68,
                   68, 68, 68, 68, 68, 68, 68, 68, 68 };
                    const byte passed[] =
                   { 0, 100, 75, 50, 30, 10, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

                    const byte kbonus[] = {
                       0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
                       0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
                       0,  0,  1,  2,  3,  3,  2,  1,  0, 0,
                       0, 10, 11, 12, 13, 13, 12, 11, 10, 0,
                       0, 20, 21, 22, 23, 23, 22, 21, 20, 0,
                       0, 30, 31, 32, 33, 33, 32, 31, 30, 0,
                       0, 40, 41, 42, 43, 43, 42, 41, 40, 0,
                       0, 50, 51, 52, 53, 53, 52, 51, 50, 0,
                       0, 50, 51, 52, 53, 53, 52, 51, 50, 0,
                       0, 42, 45, 47, 48, 48, 47, 45, 42, 0
                   };


struct OpeningBookst { //КОД ВЫРЕЗАН - ВСТАВИТЬ!!!
    boolean enabled;
//    static java.io.InputStream is;
    int level;
    int count;
}OpeningBook;
    
     void OpeningBook_Disable() {
//        try {
//            if (is!=null)
//                is.close();
//            enabled=false;
//        }
//        catch (IOException ioe){}
    }
    
    void OpeningBook_Enable() {
        OpeningBook_Disable();
//        is = (new MOVE()).getClass().getResourceAsStream("realchess.book");
     //   if (is!=null)
      //      enabled=true;
        OpeningBook.level=0;
        OpeningBook.count=0;
    }
    
    void OpeningBook_AdvanceMove(struct MOVE *m) { // КОД НУЖЕН!!!!!!!
//        short req=0;
//        int fr = m.from%10-1 + (m.from/10-2)*8;
//        int tr = m.dest%10-1 + (m.dest/10-2)*8;
//        req |= (level<<12);
//        req |= (fr<<6);
//        req |= tr;
//        
//        //try {
//            while (true) {
//                int b1=is.read();
//                int b2=is.read();
//                count += 2;
//                
//                if (b1==-1 || b2==-1 || ((b1>>4) < level)) {
//                    //System.out.println ("Move advancing fell out on count: " + count);
//                    Disable();
//                    break;
//                }
//                
//                short tst = 0;
//                tst |= (b1<<8)|b2;
//                
//                if (tst==req) {
//                    level++;
//                    //System.out.println ("After advancing move now on: " + count);
//                    
//                    if (level==16) 
//                        Disable();
//                    return;
//                }
//            }
//        }
//        catch (IOException e) 
//        {
//            Disable();
//        }
    }
    
    struct MOVE *OpeningBook_GetMove() {
//        int[] fs = new int[16];
//        int[] ts = new int[16];
//        int nfound=0;
//
//        try {
//            
//            int c = count;
//            while (true) {
//                int b1=is.read();
//                int b2=is.read();
//                c+=2;
//                
//                if (b1==-1 || b2==-1 || ((b1>>4) < level)) 
//                {
//                    //System.out.println ("Finishing seeking variants, on count: " + c + " Found variants: " + nfound);
//                    is.close();
//                    is = (new MOVE()).getClass().getResourceAsStream("realchess.book");
//                    is.skip (count);
//                    //System.out.println ("Skipped new stream by count: " + count);                    
//                    break;
//                }
//                
//                if (b1>>4==level)
//                {
//                    fs[nfound] = ((b1&0x0F)<<2) | (b2>>6);
//                    ts[nfound] = b2&0x3F;
//                    nfound++;
//                }
//            }
//        }
//        catch(IOException e)
//        {
//            Disable();
//            return null;
//        }
//        
//        if (nfound > 0)
//        {
//            int r_n = G_AI.GetRnd(0,nfound-1);
//            MOVE ret = new MOVE();
//            ret.from = (byte)((fs[r_n]%8+1)+(fs[r_n]/8+2)*10);
//            ret.dest = (byte)((ts[r_n]%8+1)+(ts[r_n]/8+2)*10);
//            ret.type = (byte)GlobalAI.GetMoveType (ret.from, ret.dest);
//            return ret;
//        }
//        else
//        {
//            Disable();
//            return null;
//        }
//   
      return null; //add!!!
    }
   /* 
    static byte[] forced_pos = 
    {
        3,   3,   3,   3,   3,   3,   3,   3,   3,   3,
        3,   3,   3,   3,   3,   3,   3,   3,   3,   3,
        3,  WR,  WN,   0,   0,   0,  WR,  WK,   0,   3,
        3,  WP,  WP,   0,   0,   0,  WP,  WP,  WP,   3,
        3,   0,   0,  WP,   0,   0,  WN,   0,   0,   3,
        3,   0,   0,   0,   0,   0,   0,   0,   0,   3,
        3,  BN,   0,   0,  WQ,  BP,   0,   0,   0,   3,
        3,   0,   0,   0,   0,   0,   0,   0,   0,   3,
        3,  BP,  BP,   0,   0,  BQ,   0,   0,  BP,   3,
        3,  BR,   0,  BB,   0,  BK,   0,  BR,   0,   3,
        3,   3,   3,   3,   3,   3,   3,   3,   3,   3,
        3,   3,   3,   3,   3,   3,   3,   3,   3,   3,
    };
    
    static void LoadForced ()
    {
        init();
        for (int i=0;i<120;i++)
        {
            B[i]=forced_pos[i];
        }
        build();
        Color=BLACK;
        SetLevel (0, 1);
        hist[hdp-1].castling = BSHORT | WSHORT | WLONG;
        GlobalAI.flip=true;
        BeReady();
    }*/
    

// функции
boolean checktest(int side);
void MakeMove(struct MOVE *m);
void Gen(struct MOVE *moves);
void TakeBack();
int score_position();
void generate_legal_captures(struct  MOVE *moves, int minval);
int attacktest( int square, int ocolor );
int find_queen (int c);
byte taxi_dist( int a, int b );
byte max_dist( int a, int b );
byte min_dist( int a, int b );
byte diag_dist( int a, int b );
void find_pins( boolean check );
int pawns();
int e_mp();
int e_nb( int color );
int e_rpr();
int e_q ();
void DoMove(int from, int to);
void DoMove3 (int from, int to, int type);
    void init();
           void build ();
                  void BeReady();
////////////////////////////////////////chess40.c














//class GlobalAI extends G_AI
//была куча переменных - перенес
    
     void SetLevel(int d, int s) {

        GlobalAI.level=d;
        GlobalAI.side=s;
        switch (d) {
            case 0:
                total_ply = 2;
                quescence_ply=1;
                MAXPLY=10;
                break;
            case 1:
                total_ply=4;
                quescence_ply=1;
                MAXPLY=10;
                break;
            case 2:
                total_ply=4;
                quescence_ply=2;
                MAXPLY=10;
                break;
            case 3:
                total_ply=6;
                quescence_ply=2;
                MAXPLY=10;
                break;
            case 4:
                total_ply=6;
                quescence_ply=3;
                MAXPLY=12;
                break;
            case 5:
                total_ply=8;
                quescence_ply=4;
                MAXPLY=14;
                break;
        }
        
        switch (s) {
            case 0:
                GlobalAI.PlayerLocal[1]=true;
                GlobalAI.PlayerLocal[2]=false;
                GlobalAI.num_humans=1;
                break;
            case 1:
                GlobalAI.PlayerLocal[1]=false;
                GlobalAI.PlayerLocal[2]=true;
                GlobalAI.num_humans=1;
                break;
            case 2:
                GlobalAI.PlayerLocal[1]=true;
                GlobalAI.PlayerLocal[2]=true;
                GlobalAI.num_humans=2;
                break;
        }
        
//        if (s<2) {
//            historyViewer.Append("[AI: " + difficultyNames[d] + "]", 0x007800);
//            historyViewer.Append("[You play: " + ((s==0)?"White]":"Black]"),0x007800);
//        }
//        else 
//            historyViewer.Append("[No AI]",0x007800);
    }
    

    boolean GlobalAI_CanMove(int from, int to/*, boolean any*/) 
    {
        for (int i=0; i < root_moves_num; i++) {
            if ((GlobalAI.M_draw[i]>>16) == from && (/*any || */(GlobalAI.M_draw[i]&0xFFFF)==to))
                return true;
        }
        return false;
    }
    
    
    int GetMoveType (int from, int to)
    {
        int type=MOVE_TYPE_NORMAL;
        
        if ((B[from] & 0xFC) == KING && from%10==5 && (to%10==3 || to%10==7))
//        if ((B[from] & 0xFC) == KING && from%10==4 && (to%10==2 || to%10==6))
            type=MOVE_TYPE_CASTLE;
        if ((B[from] & 0xFC) == PAWN && (to/10==2 || to/10==9)) {
            if (GlobalAI.PlayerLocal[Color]) {
                //type = (new UniversalMenu().GetPromotionType());
            }
            else 
            {
                type = MOVE_TYPE_PROMOTION_TO_QUEEN;
            }
        }
        
        if (((B[from] & 0xFC) == PAWN) && (abs(to-from)==20)) {
            type=MOVE_TYPE_ENPASANT;
        }
        if (((B[from] & 0xFC) == PAWN) && to==hist[hdp-1].enpas && hist[hdp-1].m.type==MOVE_TYPE_ENPASANT) {
            type=MOVE_TYPE_ENPASTAKE;
        }
        return type;
    }

    void DoMove(int from, int to) 
    {
        
        if (from==0 && to==0) return;        
        DoMove3(from, to, GetMoveType(from,to));
    }
        
    void DoMove3 (int from, int to, int type)
    {
        GlobalAI.last_taken = B[to];
        //InvalidateTime();
        //MOVE m = new MOVE();
        move.from=(byte)from; move.dest=(byte)to; move.type=(byte)type;
        MakeMove(&move);
        BeReady();
        
        GlobalAI.redraw[from]=true;
        GlobalAI.redraw[to]=true;
        GlobalAI.redraw[GlobalAI.last_move]=true;
        GlobalAI.redraw[GlobalAI.last_from]=true;
        GlobalAI.redraw[TAKEN]=true;
        if (type != MOVE_TYPE_NORMAL)
          GlobalAI.needClear=true;
        GlobalAI.last_move=to;
        GlobalAI.last_from=from;
        GlobalAI.last_move_remover_counter=0;
//        str_last_move=Notation(from,to, last_taken, type);
        
        if (Color==BLACK) nummove++;
        
//        historyViewer.AppendEncoded(m, (B[to]&0x3)==WHITE, (last_taken!=0), check, root_moves_num==0,  type >= MOVE_TYPE_PROMOTION_TO_QUEEN && type <= MOVE_TYPE_PROMOTION_TO_KNIGHT, type == MOVE_TYPE_CASTLE, nummove);
        GlobalAI.reallyFirst=false;
    
 //       if (OpeningBook.enabled)
 //           OpeningBook.AdvanceMove(m);
    }
    
 void InvalidateTime()
    {
//        long curTimer = System.currentTimeMillis();
//
//        if (Color==WHITE) 
//        {
//            if (BackTiming)
//            {
//                WhiteTime += GlobalAI.Increment;
//                WhiteTime -= (curTimer-TimerStart)/100;
//            }
//            else
//                WhiteTime += (curTimer-TimerStart)/100;                
//        }
//        else 
//        {
//            if (BackTiming)
//            {
//                BlackTime += GlobalAI.Increment;
//                BlackTime -= (curTimer-TimerStart)/100;
//            }
//            else
//                BlackTime += (curTimer-TimerStart)/100;
//     
//        }
    }    
    
    void UndoMove()
    {
        if (hdp<3)
            return;
        
        InvalidateTime();
        
        if (GlobalAI.PlayerLocal[BLACK+WHITE-Color])
        {
            TakeBack();
//            historyViewer.Append ("[Half-Move undone]",0x007800);
        }
        else
        {
            TakeBack();
            TakeBack();
//            historyViewer.Append ("[Move undone]",0x007800);
        }
        GlobalAI.str_last_move="";
        GlobalAI.last_move=0;
        GlobalAI.last_from=0;
        GlobalAI.last_taken=0;
        BeReady();
        GlobalAI.needClear=true;
    }
    
    void KillPiece (int wh)
    {
        if (B[wh]==0) return;
        if ((B[wh]&0xFC) == KING) return;
        
        if ((B[wh]&0x3)==WHITE)
         hist[hdp-1].mtrl -= Values[B[wh]>>4];
        else
         hist[hdp-1].xmtrl -= Values[B[wh]>>4];
            
        
        B[wh]=0;
        GlobalAI.B_draw[wh]=0;        
        L[L[wh].from].dest=L[wh].dest;
        L[L[wh].dest].from=L[wh].from;
        
        hist[hdp-1].castling |= cb[wh]; 

        GlobalAI.redraw[wh]=true;
    }
    void RestorePiece (int wh)
    {
        if (B[wh]!=0) return;
        if (ref_B[wh]==0) return;
        
        B[wh]=ref_B[wh];
        GlobalAI.B_draw[wh]=ref_B[wh];
        int c = B[wh]&0x3;
        
                L[wh].dest = L[(L[c].dest)].dest;
                L[wh].from = (L[c].dest);
                L[L[(L[c].dest)].dest].from = (byte)wh;
                L[(L[c].dest)].dest = (byte)wh;
                
        /*Attention!  ONLY for handicap it is!*/
        hist[hdp-1].castling &= (~cb[wh]);
        
        if ((B[wh]&0x3)==WHITE)
         hist[hdp-1].mtrl += Values[B[wh]>>4];
        else
         hist[hdp-1].xmtrl += Values[B[wh]>>4];
        
        GlobalAI.redraw[wh]=true;
        
    }
   
    void LoadIdentity (boolean reseed)
    {
        for (int i=0; i < 120; i++) B[i]=ref_B[i];
        Color=WHITE;
        init();
 //       historyViewer.Append ("[Game Started]", 0x007800);
        build();
        BeReady();
        GlobalAI.reallyFirst=true;
//        if (reseed) seed = System.currentTimeMillis() % 256;
//        m_rnd =  new java.util.Random(seed);
//        historyViewer.Append ("[Seed:" + seed + "]", 0x007800);        
        
//        OpeningBook.Enable();        
    }

/*
       void Load(int slot)
    {
        RecordStore rs;
        try
        {
            if (IsSaved(slot, false)==0) return;
            //LoadIdentity();
            rs = RecordStore.openRecordStore("Saved"+Integer.toString(slot), false);
            byte bt[] = rs.getRecord(1);
            
            rs.closeRecordStore();
            
            init();
            
            for (int i=0; i < 120; i++)
            {
                B[i]=bt[i];
            }
            build();
            
            Color=bt[120];
            
            seed=bt[124];
            m_rnd = new java.util.Random(seed);

	    SetLevel(bt[123], bt[121]);
            
            hist[hdp-1].castling=bt[126];
            hist[hdp-1].repetition=bt[127];
            nummove = bt[128];
            
            GlobalAI.flip = (bt[129]==1);

            DataInputStream dis = new DataInputStream (new ByteArrayInputStream (bt, 131, 14));
            
            GlobalAI.WhiteTime = dis.readInt();
            GlobalAI.BlackTime = dis.readInt();
            GlobalAI.Increment = dis.readInt();
            GlobalAI.BackTiming = dis.readBoolean();
            GlobalAI.rated = dis.readBoolean();
            
            BeReady();
            
            //LoadForced();
            
           // LoadHistory(slot);
            historyViewer.Append ("[Game Loaded]", 0x007800);
            historyViewer.Append ("[Seed:" + seed + "]", 0x007800);                 
            if (GlobalAI.rated)
                historyViewer.Append("[Rated game]", 0x000000FF);
            else
                historyViewer.Append("[Unrated game]", 0x000000FF);
            
            PlayChess40 pc=new PlayChess40(PlayChess40.PLAYCHESS_TYPE_NORMAL, null);
            if (Color==WHITE)
                pc.pointer=35;
            else
                pc.pointer=85;
            GlobalAI.last_move=bt[122];
            GlobalAI.last_from=bt[125];
            GlobalAI.last_taken = bt[130];
            GlobalAI.last_move_remover_counter=0;
            GlobalAI.str_last_move="";
            GlobalAI.display.setCurrent(pc);
            dis.close();
        }
        catch(RecordStoreException e){}
        catch(IOException ioe){};

    }

    void Save(int slot)
    {
        KillSave(slot);
        
        try
          {
            RecordStore rs = RecordStore.openRecordStore("Saved"+Integer.toString(slot), true);
            
            byte bt[]=new byte[180];
            for (int i=0; i < 120; i++)
            {
                bt[i]=(byte)B[i];
            }
            bt[120]=(byte)Color;
            bt[121]=(byte)GlobalAI.side;
            bt[122]=(byte)last_move;
            bt[123]=(byte)GlobalAI.level;
            bt[124]=(byte)seed;
            bt[125]=(byte)last_from;
            bt[126]=(byte)hist[hdp-1].castling;
            bt[127]=(byte)hist[hdp-1].repetition;
            bt[128]=(byte)nummove;
            bt[129]=(byte)(GlobalAI.flip?1:0);
            bt[130]=(byte)last_taken;
            
            InvalidateTime();
            
            ByteArrayOutputStream baos = new ByteArrayOutputStream(50);
            DataOutputStream dos = new DataOutputStream (baos);
            
            dos.writeInt(GlobalAI.WhiteTime);
            dos.writeInt(GlobalAI.BlackTime);
            dos.writeInt(GlobalAI.Increment);
            dos.writeBoolean(GlobalAI.BackTiming);
            dos.writeBoolean(GlobalAI.rated);
            System.arraycopy(baos.toByteArray(), 0, bt, 131, 14);
            
            rs.addRecord(bt,0,146);
            rs.closeRecordStore();
            dos.close();
            //SaveHistory(slot);
        }
        catch (RecordStoreException rse)
        {
        }
        catch (IOException e)
        {
        };
        
    }
    
    void SaveSettings ()
    {
       try
          {
            try{
                RecordStore.deleteRecordStore("Settings");
            } 
            catch(RecordStoreException e)
            {
                System.out.println (e.getClass().getName());
                System.out.println (e.getMessage());
                int i=1+2;
            }
            RecordStore rs = RecordStore.openRecordStore("Settings", true);
            
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            DataOutputStream dos = new DataOutputStream(baos);
            
            dos.writeByte((byte)GlobalAI.level);
            dos.writeBoolean(GlobalAI.vibration);
            dos.writeByte((byte)GlobalAI.defside);
            dos.writeUTF(OnlineScores.Nickname);
            dos.writeUTF(OnlineScores.Password);
            dos.write(OnlineScores.levelstats);
            
            byte[] bt = baos.toByteArray();
            rs.addRecord(bt, 0, bt.length);
            baos.close();
            rs.closeRecordStore();
        }
        catch (RecordStoreException e)
        {
        }        
        catch (IOException ioe)
        {};
    }
    void LoadSettings ()
    {
        RecordStore rs=null;
        try
        {
            rs = RecordStore.openRecordStore("Settings", false);
            byte bt[] = rs.getRecord(1);
            DataInputStream dis = new DataInputStream(new ByteArrayInputStream(bt));
            GlobalAI.level = dis.readByte();
                if (GlobalAI.level < 0) GlobalAI.level=0;
                if (GlobalAI.level >= difficultyNames.length)  GlobalAI.level=difficultyNames.length-1;
            GlobalAI.vibration = dis.readBoolean();
            GlobalAI.defside = dis.readByte();
                if (GlobalAI.defside < 0 || GlobalAI.defside > 1) GlobalAI.defside = 0;
            
            OnlineScores.Nickname = dis.readUTF();
            OnlineScores.Password = dis.readUTF();
            dis.read(OnlineScores.levelstats, 0, GlobalAI.difficultyNames.length);
            rs.closeRecordStore();  
            dis.close();            
        }
        catch (Exception e)
        {
           try
           {
               if (rs!=null)rs.closeRecordStore();
           }
           catch(Exception ee)
           {}
        }
    }
    
        
    int IsSaved(int slot, boolean getside) 
    {
        try {
            RecordStore rs = RecordStore.openRecordStore("Saved"+Integer.toString(slot), false);
            if (getside)
            {
                byte[]  btarr = rs.getRecord(1);
                rs.closeRecordStore();
                
                int ret = btarr[121]+1;
                if (ret>=1 && ret <=3)
                    return ret;
                else
                    return 0;
            }
            else
            {
                rs.closeRecordStore();
                if (debugSave) stringSave.append("Closed. True.\n");            
                return 1;
            }
        }   
        catch (Exception e) 
        {
            if (debugSave) stringSave.append("Exception " + e.getClass() + " " + e.getMessage() + "False.\n");            
            return 0;
        }
    }
    
    void KillSave (int slot)
    {
            try{
            RecordStore.deleteRecordStore("Saved"+Integer.toString(slot));
            }catch(RecordStoreException e){};
    }
    String Notation (int src, int dst, int capture, int type)
        {
            String ret = new String();
            if (type <= MOVE_TYPE_PROMOTION_TO_QUEEN || type >= MOVE_TYPE_PROMOTION_TO_KNIGHT)
            switch (B[dst]&0xFC)
            {
                case PAWN:
                    ret="";
                    break;
                case KNIGHT:
                    ret="N";
                    break;
                case BISHOP:
                    ret="B";
                    break;
                case ROOK:
                    ret="R";
                    break;
                case QUEEN:
                    ret="Q";
                    break;
                case KING:
                    ret="K";
                    break;
            }
            ret += (char)('a' + src%10-1);
            ret += Integer.toString(src/10-1);
            ret += ((capture!=0)?'x':'-');
            ret += (char)('a' + dst%10-1);
            ret += Integer.toString(dst/10-1);
            
            if (type >= MOVE_TYPE_PROMOTION_TO_QUEEN && type <= MOVE_TYPE_PROMOTION_TO_KNIGHT)
            switch (B[dst]&0xFC)
            {
                case KNIGHT:
                    ret+="N";
                    break;
                case BISHOP:
                    ret+="B";
                    break;
                case ROOK:
                    ret+="R";
                    break;
                case QUEEN:
                    ret+="Q";
                    break;
                case KING:
                    ret="K";
                    break;
            }            
            
            if (type==MOVE_TYPE_CASTLE) 
            {
                if (dst>src) 
                    ret= "0-0";
                else
                    ret="0-0-0";
            }            
            
            if (GlobalAI.root_moves_num==0 && GlobalAI.check)
             ret += "X";
            else if (GlobalAI.check)
             ret += '+';
            
        
            return ret;
    }
*/
