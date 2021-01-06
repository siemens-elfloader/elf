
//gai.h
typedef signed char byte;
typedef char boolean;
#define true 1
#define false 0
#define null 0

struct MOVE
{
    byte from, dest;
    byte type, tmp;
};

    struct GlobalAIst{// extends G_AI //from Chess40.java
    /*BIVSHIY GlobalAI*/
//    Display display; //ну эта точно нужна    
//    Chess ch; //Чтобы из разных мест можно было вызвать функциию выхода
    int gr_set; //Выбранный набор графики для фигур
    int num_humans;
    boolean rated;
    int level;
    int side;
    boolean vibration;
    boolean flip;
    int defside;
    /*GlobalAI*/
    boolean debugSave;
    char *stringSave;
//    Thread WorkerThread;
    int AbortFlag;  /*0 - Clear.  1 - Abort Request.   2 - Immediate Move Request. */
    boolean BackTiming;
    int WhiteTime, BlackTime, Increment;
    long TimerStart;    
   
    boolean PlayerLocal[3];
    
    char *note;
    int notecolor;
    char *timenote;
    char *blacktimenote;
    char *whitetimenote;
    
    char *str_last_move;
    
    int last_move;
    int last_from;
    int last_taken;
    int last_move_remover_counter;
    
    int hint_from, hint_to, hint_blink_counter;
    boolean preserve_blink;
//    javax.microedition.lcdui.Image bigimg;
//    javax.microedition.lcdui.Image backimglr;
//    javax.microedition.lcdui.Image backimgup;
//    javax.microedition.lcdui.Image backimgdown;
//    javax.microedition.lcdui.Image fontimg;
//    
//    javax.microedition.lcdui.Image backimg;
//    java.util.Hashtable poshash;
    int series;
    boolean redraw[120];//=new boolean[120];/*Какие клетки надо перерисовывать*/
    boolean needClear;/*Если true, то надо обязательно перерисовать всю доску*/
    boolean reallyFirst;
    int B_draw[100];
    int C_draw;
    int M_draw[120];
    boolean Check_draw;
    int Stage_draw;
    int Stage_progress;    
};

extern struct GlobalAIst GlobalAI; 
extern int Color;


extern void init();
extern void build();
extern void BeReady();
extern void GlobalAIinit();
extern int B[];
extern const int ref_B[];
extern void Randomize();
extern struct MOVE *ComputerThink();
extern void DoMove(int from, int to);
extern void SetLevel(int d, int s);
extern boolean GlobalAI_CanMove(int from, int to/*, boolean any*/);
extern void DoMove(int from, int to);


