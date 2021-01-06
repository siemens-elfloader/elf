
// AI.c
#include "..\swilib.h"
#include "chess.h"
    

void GlobalAIinit(){ //Вызывать в начале!
  //memset(GlobalAIst,0,sizeof(GlobalAIst));
  GlobalAI.level=1;
  GlobalAI.vibration=true;
  GlobalAI.flip=false;
  GlobalAI.hint_blink_counter=-1;
  GlobalAI.preserve_blink=false;
  GlobalAI.series = 40;
  GlobalAI.reallyFirst=false;
}

    int GetRnd(int min, int max)// [min, max]
    {
        int z = max - min;

        if(z == 0) return max;

        //int r = m_rnd_nextInt() % (z + 1);
        int r=randint(z);
        return (min + abs(r));
    }
       
       
    void init()
	{
        historyViewer_Clear();
        
        //hist = new HIST[50 /*200*/]; /*История...*/
        hdp=1;

        //L = new MOVE[120];

        //pin = new byte[120];
        //tar = new byte[120];

        //see_wl = new int[16];
        //see_bl = new int[16];

        //wl = new int[34];
        //bl = new int[34];


        //P = new short[120];

        //Wknow = new Know();
        //Bknow = new Know();

        //psnl = new int[MAXPLY];
        
        //PV = new MOVE[MAXPLY];
        //for (int i=0; i < MAXPLY; i++)
        //    PV[i]=new MOVE();

        check=false;

//        for (int i=0; i < hist.length; i++) {
//            hist[i] = new HIST();
//            hist[i].m = new MOVE();
//        }

//        killers = new MOVE[MAXPLY][];
//        for (int i=0; i < MAXPLY; i++) {
//            killers[i] = new MOVE[2];
//            killers[i][0]=new MOVE();
//            killers[i][1]=new MOVE();
//        }
//        mvs = new MOVE[MAXPLY][];
//        mvls = new int[MAXPLY][];
//        for (int i=0; i < MAXPLY; i++)
//        {
//            int nnnn = 120;
//            if (i >= MAXPLY/2)
//             nnnn=25;
//               
//            mvs[i] = new MOVE[nnnn];
//            
//            for (int j=0; j < nnnn; j++)
//             mvs[i][j] = new MOVE();
//            mvls[i] = new int[nnnn];
//        }

		nt=0;

        num_mades=0;

        Color=WHITE;
            
        GlobalAI.BackTiming=false;
        GlobalAI.WhiteTime=0;
        GlobalAI.BlackTime=0;
        
        nummove=0;
        
        OpeningBook_Disable();
    }

    /*Посторение по имеющейся доске (B[]) всяких служебных структур*/
     void build ()
    {
           hist[0].mtrl=0;
           hist[0].xmtrl=0;

	for (int i=0; i < 120; i++)
	{
			/*Выделяем память под элементы списка фигур*/
//            L[i] = new MOVE();

			/*Заодно - считаем материал, записываем куда надо в "историю"*/
            if ((B[i] & 0x3)==WHITE)
                hist[0].mtrl += Values[B[i]>>4];
            if ((B[i] & 0x3)==BLACK)
                hist[0].xmtrl += Values[B[i]>>4];
        }

        /*Ищем королей, прописываем их в начала списков фигур:*/
        for (byte i=20; i < 100; i++)
        {
            if (B[i]==WK)
            {
                L[WHITE].dest = i;
                L[i].from = WHITE;
                L[i].dest = 0;
            }
            if (B[i]==BK)
            {
                L[BLACK].dest = i;
                L[i].from = BLACK;
                L[i].dest = 0;
            }
        }

        /*Достраиваем сами списки*/
        for (byte i=20; i < 100; i++) {
            if (i==L[WHITE].dest || i==L[BLACK].dest) continue;
            if ((B[i] & 0x3) == WHITE) {
                L[i].from = (L[1].dest);
                L[i].dest = L[L[1].dest].dest;
                L[L[i].dest].from = L[L[i].from].dest = i;
            }
            if ((B[i] & 0x3) == BLACK) {
                L[i].from = (L[2].dest);
                L[i].dest = L[L[2].dest].dest;
                L[L[i].dest].from = L[L[i].from].dest = i;
            }
        }
    }


	/*Функция, выполняющая служебные действия для "обеспечения боевой готовности".
		Должна вызываться в начале, и после каждого реально совершённого хода.*/
     void BeReady()
    {
        Ply = 0;
        nodes = 0;
        check = checktest(Color);

		/*Перед генерацией ходов всегда надо обнулять pMCount*/
        pMCount=0;
		/*Генерируем возможные ходы*/
        Gen(mvs[0]);
		/*В этот момент pMCount уже не ноль! Так как мы генерировали ходы...*/
        root_moves_num = pMCount;
        
        //GlobalAI.TimerStart = System.currentTimeMillis();       
        
        //System.arraycopy(B, 0, GlobalAI.B_draw, 0, 100);
        memcpy(GlobalAI.B_draw,B,100);
               
        GlobalAI.C_draw = Color;
        for (int i=0; i < root_moves_num; i++)
            GlobalAI.M_draw[i] = (mvs[0][i].from<<16) | mvs[0][i].dest;
        GlobalAI.Check_draw = check;        

        GlobalAI.redraw[GlobalAI.hint_to]=true;
        GlobalAI.redraw[GlobalAI.hint_from]=true;        
        GlobalAI.hint_to=0;
        GlobalAI.hint_from=0;  
    }


	 int square, destination;

    /*Засунуть возможный ход в массив ходов (для генерации ходов)*/
	/*"Откуда" и "Куда" берутся из "глобальных" переменных square и destination, тип хода идёт как параметр*/
     void            Gen_Push(short type, struct MOVE *pBuf, boolean full)
    {
        pBuf[pMCount].from = (byte)square;
        pBuf[pMCount].dest = (byte)destination;
        pBuf[pMCount].type = (byte)type;

		/*Если ход не обычный, или ходим "пришпиленной" фигурой - то проверяем на шах*/
        if(type != MOVE_TYPE_NORMAL || pin[square] != 0 )
        {
            MakeMove(pBuf+pMCount);
            if(!checktest(BLACK + WHITE - Color))
                pMCount++;
            TakeBack();
        }
        else
            pMCount++;
    }

    /*Оценочная функция, собственно*/
	 int Eval(int mode)
	{
        int mat = hist[hdp-1].mtrl - hist[hdp-1].xmtrl;

		/*Если сказано пересчитывать позиционную оценку - то пересчитываем, иначе не пересчитываем*/
        switch (mode)
        {
            case 1:
                nodes++;
                psnl[Ply] =  -score_position()*2/3;
                //System.out.println("Full-Evaluated at #" + Integer.toString(Ply));
                break;
            case 0:
                break;
        }


        int score = psnl[Ply] - mat;

		/*При приближении "правила 3 ходов" приближать оценку к ничьей.
				Кстати, далеко не факт что тут я правильно поступаю...*/
//        return score*(3-hist[hdp-1].repetition)/3;
        return score;
    }


    /*Совершить ход*/
     void           MakeMove(struct MOVE *m)
     {
        //assrt();
            

        hist[hdp].m.dest = m->dest;
        hist[hdp].m.from = m->from;
        hist[hdp].m.type = m->type;
        int cap = B[m->dest]&0xFC;
        hist[hdp].cap = (byte)cap;

        hist[hdp].xmtrl = hist[hdp-1].mtrl;
        hist[hdp].mtrl = hist[hdp-1].xmtrl - Values[B[m->dest]>>4];

		/*Вдруг мы не будем пересчитывать позиц. оценку? Тогда сразу взять её за предыдущую.
			Естественно - с обратным знаком*/
		psnl[Ply+1] = -psnl[Ply];

		/*Возможно, запретить какие-то рокировки*/
        hist[hdp].castling = (byte)(hist[hdp-1].castling | cb[m->from] | cb[m->dest]);

		/*Подсчитать, какое это по счёту повторение*/
        if (hdp<5)
            hist[hdp].repetition=0;
        else
        {
            if (hist[hdp-1].m.from==hist[hdp-3].m.dest && hist[hdp-1].m.dest==hist[hdp-3].m.from &&
                hist[hdp-2].m.from==hist[hdp-4].m.dest && hist[hdp-2].m.dest==hist[hdp-4].m.from)
              hist[hdp].repetition = (byte)min (hist[hdp-4].repetition+1, 3);
            else
              hist[hdp].repetition = 0;
        }


        /*Убрать из списка фигуру, которую съели*/
        if (cap != 0) {
            L[L[m->dest].dest].from = L[m->dest].from;
            L[L[m->dest].from].dest = L[m->dest].dest;
        }

        /*Собственно передвинуть фигуру*/
        B[m->dest] = B[m->from];
        B[m->from] = 0;

		/*Соответственно изменить список*/
        L[m->dest].dest = L[m->from].dest;
        L[m->dest].from = L[m->from].from;
        L[L[m->dest].from].dest = L[L[m->dest].dest].from = (byte)m->dest;

        if (m->type == MOVE_TYPE_ENPASANT)
        {
            hist[hdp].enpas = (byte)((m->from+m->dest)/2);
        }

        if (m->type == MOVE_TYPE_ENPASTAKE)
        {
            int target;
            if (Color==WHITE)
             target=m->dest-10;
            else
             target=m->dest+10;
            B[target]=0;

            hist[hdp].mtrl-=P_VALUE;
            L[L[target].from].dest = L[target].dest;
            L[L[target].dest].from = L[target].from;
        }



        if (m->type >= MOVE_TYPE_PROMOTION_TO_QUEEN) {       /* Promotion */
            switch (m->type) {
                case MOVE_TYPE_PROMOTION_TO_QUEEN:
                    B[m->dest] = QUEEN | (B[m->dest]&3);
                    hist[hdp].xmtrl += Q_VALUE - P_VALUE;
                    break;

                case MOVE_TYPE_PROMOTION_TO_ROOK:
                    B[m->dest] = ROOK | (B[m->dest]&3);
                    hist[hdp].xmtrl += R_VALUE - P_VALUE;
                    break;

                case MOVE_TYPE_PROMOTION_TO_BISHOP:
                    B[m->dest] = BISHOP | (B[m->dest]&3);
                    hist[hdp].xmtrl += B_VALUE - P_VALUE;
                    break;

                case MOVE_TYPE_PROMOTION_TO_KNIGHT:
                    B[m->dest] = KNIGHT | (B[m->dest]&3);
                    hist[hdp].xmtrl += N_VALUE - P_VALUE;
                    break;

                default: break;
            }
        }

        if (m->type == MOVE_TYPE_CASTLE) {
            // System.out.print ("Done castling");
            switch (m->dest) {
                case 23:
                    B[24] = WR;
                    B[21] = 0;

                    L[24].from = L[21].from;
                    L[24].dest = L[21].dest;
                    L[L[21].dest].from = 24;
                    L[L[21].from].dest = 24;

                    hist[hdp].castling |= ( WSHORT | WLONG );

                    break;
                case 27:
                    B[26] = WR;
                    B[28]=0;

                    L[26].dest = L[28].dest;
                    L[26].from = L[28].from;
                    L[L[28].dest].from = 26;
                    L[L[28].from].dest = 26;

                    hist[hdp].castling |= ( WSHORT | WLONG );

                    break;
                case 93:
                    B[94] = BR;
                    B[91] = 0;

                    L[94].dest = L[91].dest;
                    L[94].from = L[91].from;
                    L[L[91].dest].from = 94;
                    L[L[91].from].dest = 94;

                    hist[hdp].castling |= ( BSHORT | BLONG );

                    break;
                case 97:
                    B[96] = BR;
                    B[98] = 0;

                    L[96].dest = L[98].dest;
                    L[96].from = L[98].from;

                    L[L[98].dest].from = 96;
                    L[L[98].from].dest = 96;

                    hist[hdp].castling |= ( BSHORT | BLONG );

                    break;
            }
        }


        Ply++;
        hdp++;
        Color = BLACK+WHITE-Color;

        // check if hdp is too big
        if(hdp > histlength - 3)
        {
			int len = histlength;
			for(int i=10; i<len; i++)
			{
				hist[i-10].m.from = hist[i].m.from;
				hist[i-10].m.dest = hist[i].m.dest;
				hist[i-10].m.type = hist[i].m.type;

				hist[i-10].cap = hist[i].cap;
				hist[i-10].castling = hist[i].castling;
				hist[i-10].repetition = hist[i].repetition;
				hist[i-10].xmtrl = hist[i].xmtrl;
				hist[i-10].mtrl = hist[i].mtrl;
				hist[i-10].enpas = hist[i].enpas;
			}
			hdp-=10;
        }
       
        /*Если ход "особенный" - пересчитать позиц. оценку*/
        if ((m->type >= MOVE_TYPE_PROMOTION_TO_QUEEN) && (m->type <=MOVE_TYPE_PROMOTION_TO_KNIGHT))
        {
            Eval(1);
        }
        //assrt();
    }

     void            TakeBack() /*Отменить то, что сделала MakeMove(). Обратные действия в обратном порядке.*/
     {
        //assrt();
        Color = (WHITE + BLACK) - Color;
        hdp--;
        Ply--;
        struct MOVE *m = &hist[hdp].m;
        B[m->from] = B[m->dest]&0xFC;
        B[m->from] |= Color;
        B[m->dest] = hist[hdp].cap;

        L[m->from].dest = L[m->dest].dest;
        L[m->from].from = L[m->dest].from;
        L[L[m->from].dest].from = (byte)m->from;
        L[L[m->from].from].dest = (byte)m->from;

        if (hist[hdp].cap != 0) {
            B[m->dest] |= (WHITE + BLACK) - Color;//?????
            if( Color == BLACK ) {
                L[m->dest].dest = L[(L[1].dest)].dest;
                L[m->dest].from = (L[1].dest);
                L[L[(L[1].dest)].dest].from = (byte)m->dest;
                L[(L[1].dest)].dest = (byte)m->dest;
            }
            else {
                L[m->dest].dest = L[(L[2].dest)].dest;
                L[m->dest].from = (L[2].dest);
                L[L[(L[2].dest)].dest].from = (byte)m->dest;
                L[(L[2].dest)].dest = (byte)m->dest;
            }
        }
        else
            B[m->dest] = 0;


         if (hist[hdp].m.type == MOVE_TYPE_ENPASTAKE)
        {
            int target;
            if (Color==BLACK) /*!!!!!!!!!!!!!!!!!!!!!!1*/
            {
             target=m->dest+10;
             B[target]=WP;
                L[target].dest = L[(L[1].dest)].dest;
                L[target].from = (L[1].dest);
                L[L[(L[1].dest)].dest].from = (byte)target;
                L[(L[1].dest)].dest = (byte)target;
            }
            else
            {
             target=m->dest-10;
             B[target]=BP;
                L[target].dest = L[(L[2].dest)].dest;
                L[target].from = (L[2].dest);
                L[L[(L[2].dest)].dest].from = (byte)target;
                L[(L[2].dest)].dest = (byte)target;
            }

        }



        if (hist[hdp].m.type == MOVE_TYPE_PROMOTION_TO_QUEEN) {
            B[hist[hdp].m.from] = PAWN | (B[hist[hdp].m.from] & 0x3);
            hist[hdp].mtrl -= (Q_VALUE - P_VALUE);
        }
        if (hist[hdp].m.type == MOVE_TYPE_PROMOTION_TO_KNIGHT) {
            B[hist[hdp].m.from] = PAWN | (B[hist[hdp].m.from] & 0x3);
            hist[hdp].mtrl -= (N_VALUE - P_VALUE);
        }
        if (hist[hdp].m.type == MOVE_TYPE_PROMOTION_TO_BISHOP) {
            B[hist[hdp].m.from] = PAWN | (B[hist[hdp].m.from] & 0x3);
            hist[hdp].mtrl -= (B_VALUE - P_VALUE);
        }
        if (hist[hdp].m.type == MOVE_TYPE_PROMOTION_TO_ROOK) {
            B[hist[hdp].m.from] = PAWN | (B[hist[hdp].m.from] & 0x3);
            hist[hdp].mtrl -= (R_VALUE - P_VALUE);
        }

        if (hist[hdp].m.type==MOVE_TYPE_CASTLE) {
            //System.out.print ("UnDone castling");
            switch (hist[hdp].m.dest) {
                case 23:
                    B[24] = 0;
                    B[21] = WR;

                    L[21].dest = L[24].dest;
                    L[21].from = L[24].from;
                    L[L[24].dest].from = 21;
                    L[L[24].from].dest = 21;

                    break;
                case 27:
                    B[26] = 0;
                    B[28] = WR;

                    L[28].dest = L[26].dest;
                    L[28].from = L[26].from;
                    L[L[26].dest].from = 28;
                    L[L[26].from].dest = 28;

                    break;
                case 97:
                    B[96] = 0;
                    B[98] = BR;

                    L[98].dest = L[96].dest;
                    L[98].from = L[96].from;
                    L[L[96].dest].from = 98;
                    L[L[96].from].dest = 98;

                    break;
                case 93:
                    B[94] = 0;
                    B[91] = BR;

                    L[91].dest = L[94].dest;
                    L[91].from = L[94].from;
                    L[L[94].dest].from = 91;
                    L[L[94].from].dest = 91;

                    break;
            }
        }
        //assrt();
    }

/*
 ****************************************************************************
 * Search function - a typical alphabeta, main search function              *
 ****************************************************************************
 */

     int Search(int alpha, int beta, int depth, int qply, struct MOVE *pBestMove, int check_extend, int whoami)// throws InterruptedException
     {
        int             i,
        value;
        //int havemove;
        struct MOVE         *moveBuf, tmpMove;
        moveBuf= mvs[Ply];
        int bestval = -30000;
        //int bm;
        //int st_nodes=nodes;

        boolean full_gen;
        
        if (GlobalAI.AbortFlag!=0)
        {
            //System.out.println("Thread abort requested.");
            //throw new InterruptedException("Thread Abort requested");
        }

        check = checktest (Color);
        
        if (check && (check_extend<2))
        {
            depth++;
            qply++;
            check_extend++;
        } 

        pMCount=0;
        if (Ply < qply || (check && (check_extend < 2)))
        {
            Gen(moveBuf); // generate all moves for current position 
            full_gen = true;
        }
        else
        {
            generate_legal_captures( moveBuf, 0); //generate only capture moves
            full_gen=false;
            
             //if (pMCount==0 && Ply == qply)            {
             //   Gen(moveBuf);
             //   full_gen=true;
             //   depth=0;
            //}
            
            if (!full_gen && pMCount > 4 && Ply == qply)
            {
                depth--;
            }    //ВЫЗЫВАЛО СЛИТИЕ ФИГУР!
            
            if (!full_gen)
            {
                int a;
                if (Ply==qply && Ply != 1)
                {
                    a = -Eval(1);
                }
                else
                {
                    a = -Eval(0);
                }
                if (alpha < a)
                {
                    alpha = a;
                    if (alpha > beta+RANDOMIZER_WINDOW) return alpha;
                }
                bestval=a;
            }
        }

        int *mVals = mvls[Ply];
        for (i=0; i < pMCount; i++) {
            if (depth > 1)
            {
                MakeMove(moveBuf+i);
                mVals[i] = Eval((Ply < qply)?1:0);
                TakeBack();
            }
            else {
                mVals[i]=0;
                //              mVals[i]=Values[ B[ moveBuf[i].from ]>>4 ];
                //            if (B[moveBuf[i].dest] != 0) //capture
                //           mVals[i]+= 100 + Values[B[ moveBuf[i].dest ]>>4];
            }
            if (moveBuf[i].dest==killers[Ply][0].dest && moveBuf[i].from==killers[Ply][0].from)
                mVals[i] += 200;
            if (moveBuf[i].dest==killers[Ply][1].dest && moveBuf[i].from==killers[Ply][1].from)
                mVals[i] += 200;
        }
        //blunder (moveBuf, mVals);

        boolean sorted = false; int tmpInt; 
        while (!sorted){ //Сортируем пузырьком. А не лучше ли qsort'ом ?!
            sorted = true;
            for (i=1; i < pMCount; i++)
////ERROR HERE!!!
              if (mVals[i] > mVals[i-1]) {
                //memcpy(&tmpMove,moveBuf+i,sizeof(struct MOVE));
                //memcpy(moveBuf+i,moveBuf+i-1,sizeof(struct MOVE));
                //memcpy(moveBuf+i-1,&tmpMove,sizeof(struct MOVE));
                *(int*)&tmpMove=*(int*)(moveBuf+i);
                *(int*)(moveBuf+i)=*(int*)(moveBuf+i-1);
                *(int*)(moveBuf+i-1)=*(int*)&tmpMove;
                
                    //tmpMove = moveBuf[i]; moveBuf[i] = moveBuf[i-1]; moveBuf[i-1] = tmpMove;
                    tmpInt  = mVals[i];   mVals[i]   = mVals[i-1];   mVals[i-1]   = tmpInt;
                    sorted = false;
                }
            if (sorted) break;
            for (i = pMCount-1; i >= 1; i--)
                if (mVals[i] > mVals[i-1]) {
                //memcpy(&tmpMove,moveBuf+i,sizeof(struct MOVE));
                //memcpy(moveBuf+i,moveBuf+i-1,sizeof(struct MOVE));
                //memcpy(moveBuf+i-1,&tmpMove,sizeof(struct MOVE));
                  *(int*)&tmpMove=*(int*)(moveBuf+i);
                  *(int*)(moveBuf+i)=*(int*)(moveBuf+i-1);
                  *(int*)(moveBuf+i-1)=*(int*)&tmpMove;
                  
//                  tmpMove = moveBuf[i]; moveBuf[i] = moveBuf[i-1]; moveBuf[i-1] = tmpMove;
                    tmpInt  = mVals[i];   mVals[i]   = mVals[i-1];   mVals[i-1]   = tmpInt;
                    sorted = false;
                }

        }

        // loop through the moves 
        for (i = 0; i < pMCount; ++i)
        {
            //if (easy!=0 && mVals[i]==-1534) continue;
            MakeMove(moveBuf+i);
            //if (checktest(BLACK+WHITE-Color))
            //{
            //    TakeBack();
            //    continue;
            //}

	        if (hist[hdp-1].repetition < 3)
                {
        if ((depth > 1 || moveBuf[i].type==MOVE_TYPE_PROMOTION_TO_QUEEN) && Ply < MAXPLY-1){ // If depth is still, continue to search deeper 
	                int old_moves = pMCount;
                        if (Ply==2 && i==14)
                        {
                            Ply=Ply;
                        }
                        //try
                        {
                            value = -Search(-beta, -alpha, depth - 1, qply, &fucked_move, check_extend, i);
                        }
                        //catch (InterruptedException ie)
//                        {
//                            TakeBack();
//                            throw ie;
//                        }
	                pMCount=old_moves;
	            }
	            else
	            {
	                value = Eval(full_gen?1:0);
                        if  (!full_gen && Ply % 2 == 1)
                        {
                            if (attacktest (moveBuf[i].dest, Color)!=0)
                            {
                                value -= Values[B[moveBuf[i].dest]>>4]*2/3;
                            }
                        }                        
	            }
	        }
	        else
	        {
	            value = 0;
	        }

            TakeBack();

            if (value > bestval) 
            {
                bestval = value;
                //bm=i;
            }

            if (value > alpha) {
                if (value >= beta+RANDOMIZER_WINDOW+1) { //ОБЯЗАТЕЛЬНО +1, Так как тут >= !!!!!!
                    if (moveBuf[i].dest != killers[Ply][0].dest || moveBuf[i].from != killers[Ply][0].from) {
                        killers[Ply][1].dest=killers[Ply][0].dest;
                        killers[Ply][1].from=killers[Ply][0].from;
                        killers[Ply][0].dest = moveBuf[i].dest;
                        killers[Ply][0].from = moveBuf[i].from;
                    }
                    return value;
                }
                alpha = value;
                pBestMove->type = moveBuf[i].type;
                pBestMove->dest = moveBuf[i].dest;
                pBestMove->from = moveBuf[i].from;
            }
        }
        if (pMCount==0 && full_gen) // If no legal moves, that is checkmate or stalemate 
        {
            pBestMove->type = MOVE_TYPE_NONE;
            if (checktest(Color))
                return -MATE + 50*Ply; // add Ply to find the longest path to lose or shortest path to win 
            else
                return 0;
        }

        return bestval;
    }

    
    
    
	/*Поиск среди корневых ходов. Отличается тем, что ходы не сортитует (их в computer_think сортируют).*/

    struct MOVE *SearchRoot(int depth, int q, struct MOVE *root_moves, int *root_vals, int root_moves_num)// throws InterruptedException
    {
        int bm=0, i; /*Храним номер лучшего хода. Реально не особо нужно, но так просто...*/
        //MOVE tm = new MOVE(); /*Очередная "затычка", чтобы Search() в неё что-то вернул*/
        root_vals[0] = -MATE;

        for (i = 0; i < root_moves_num; ++i)
        {
            MakeMove(root_moves+i);

            /*if (checktest(BLACK+WHITE-Color)) {
                TakeBack();
                continue;
            }*/

	        if (hist[hdp-1].repetition < 3)
	        {
	            if (depth > 1)
	            {
	                Eval(1);/*Принудительно вычислить позиционную оценку*/
                        if (i==8)
                            i=i;
					/*Ну и вперёд, просчитывать...*/
	                //try
                        {
                            root_vals[i] = -Search(-MATE, -root_vals[bm], depth - 1, q, &tm, 0,i);
                        }
//                        catch (InterruptedException ie)
//                        {
//                            TakeBack();
//                            if (GlobalAI.AbortFlag == 2)
//                                best_move = root_moves[bm];  /*Лучший из уже обсчитанных*/
//                            throw ie;
//                        }

					// Чтобы пешки охотнее двигались
					if (hist[hdp].xmtrl == 0)
					{
                                            root_vals[i] += 25;
                                            if ((B[root_moves[i].dest]&0xFC)==PAWN || (root_moves[i].type>=MOVE_TYPE_PROMOTION_TO_QUEEN && root_moves[i].type <= MOVE_TYPE_PROMOTION_TO_KNIGHT) )
                                            {
                                                root_vals[i] += 25;
                                            }
                                            else
                                            {
                                                int qu = find_queen(3-Color);
                                                int ek = L[Color].dest;
                                                int mk = L[3-Color].dest;
                                                if (qu != 0)
                                                {
                                                    if ( taxi_dist(ek, H8) <= 2)
                                                    {
                                                        if (qu==E6 || qu==E7) 
                                                        {
                                                            root_vals[i] += 40;
                                                            root_vals[i] += (gon_na_G6[mk]-gon_na_G6[root_moves[i].from]);
                                                        }

                                                           root_vals[i] += (gon_na_G6[mk]-gon_na_G6[root_moves[i].from]);
                                                        
                                                                                                                
                                                        if (gon_na_G6[mk]==30)
                                                        {
                                                            if (qu==E7 && qu==root_moves[i].dest) root_vals[i]+=60;
                                                        }
                                                    }
                                                    else
                                                      root_vals[i] -= (max_dist (mk, qu-9) + max_dist(mk,qu-10))*2;

                                                    if (qu%10>=ek%10) 
                                                        root_vals[i]-=60;
                                                    if (qu/10>=ek/10) 
                                                        root_vals[i]-=60;
                                                    if (qu==root_moves[i].dest)
                                                    {
                                                        if ((root_moves[i].from%10 < ek%10) && (root_moves[i].from/10 < ek/10))
                                                        {
                                                            if (qu%10 < root_moves[i].from % 10) 
                                                                root_vals[i]-=40;
                                                            if (qu/10 < root_moves[i].from / 10) 
                                                                root_vals[i]-=40;
                                                        }
                                                        root_vals[i] += 20;
                                                    }
                                                }
                                            }
					}
	            }
	            else
				{
	                root_vals[i] = Eval(1);
	            }
	        }
	        else
	        {
	            root_vals[i] = 0;
	        }

            TakeBack();

            if (root_vals[i] > root_vals[bm])
            {
                bm = i;
            }
            
            GlobalAI.Stage_progress = i+1;
        }

        if (root_moves_num != 0)
            return root_moves+bm;
        else
        {
			/*Если ходов возможных нет - то это или пат или мат. Вернуть MOVE_TYPE_NONE*/
            //MOVE nm = new MOVE();
            nm.type = MOVE_TYPE_NONE;
            return &nm;
        }
    }

    int WhiteMovesFrom[] = {34, 35, 35,  22, 27};
    int WhiteMovesTo[] =  {54, 55, 55,  43, 46};
    
    
     struct MOVE *ComputerThink()// throws InterruptedException
    {
        int q,d;
        GlobalAI.Stage_draw=0;   
        
        struct MOVE *m=null;
//        if (OpeningBook.enabled)
//          m = OpeningBook_GetMove();
//        
//        if (m!=null){
//            if (GlobalAI_CanMove (m->from, m->dest)){
//                return m;
//            }
//            else
//            {
                m = &tmpmove;//new MOVE();//???????
//            }
//        }
        int             score;
        // reset some values before searching 
        Ply = 0;
        nodes = 0;

        struct MOVE *moveBuf = mvs[Ply]; //Установить буфер для корневых ходов в mvs[0]

        int *mVals = mvls[Ply]; 	//Установить буфер под значения ходов в mvls[0]

        //РАНЬШЕ (до 24 августа), здесь была проверка на шах и генерение корневых ходов.
         //Но это дублирует BeReady() => нафиг.

        for (q=1, d=1; q <= quescence_ply; q++)
        { //Пробегаем глубиной "полного" перебора от маленькой до выбранной
		  //Для каждой высчитываем соответствующую общую глубину перебора

		  //Это нужно чтобы сначала на небольших глубинах "быстро" посчитать и осуществить качественную сортировку ходов
            
            if (q != quescence_ply && q >2) 
                continue;   //Хватит сортировать, считать пора!
            
            
            if (q==1) 
            {
                d=2;
            }
            if (q==2) 
            {
                d=4;
            }
            if (q==quescence_ply) 
            {
                d = total_ply;
            }
            GlobalAI.Stage_progress = 0;
            
            best_move = moveBuf[0];
            
            GlobalAI.Stage_draw++;
            
//            try
//            {
		   //Посчитали, заполнился массив mVals
                m = SearchRoot(d, q,  moveBuf, mVals, root_moves_num);
//            }
//            catch(InterruptedException ie)
//            {
//                if (GlobalAI.AbortFlag==2) 
//                {
//                    GlobalAI.AbortFlag=0;
//                    return best_move;
//                }
//                else
//                    throw ie;
//            }

		   //Теперь сортируем, пузырёчком. Может, встроенными средствами и лучше будет...
            struct MOVE tmpMove2;
            boolean sorted = false; int tmpInt;
  
            while (!sorted) {
                sorted = true;
                for (int i=1; i < root_moves_num; i++)
                    if (mVals[i] > mVals[i-1]) {
                      //memcpy(&tmpMove2,moveBuf+i,sizeof(struct MOVE));
                      //memcpy(moveBuf+i,moveBuf+i-1,sizeof(struct MOVE));
                      //memcpy(moveBuf+i-1,&tmpMove2,sizeof(struct MOVE));
                 *(int*)&tmpMove2=*(int*)(moveBuf+i);
                *(int*)(moveBuf+i)=*(int*)(moveBuf+i-1);
                *(int*)(moveBuf+i-1)=*(int*)&tmpMove2;

 //                       tmpMove2 = moveBuf[i]; moveBuf[i] = moveBuf[i-1]; moveBuf[i-1] = tmpMove2;
                        tmpInt  = mVals[i];   mVals[i]   = mVals[i-1];   mVals[i-1]   = tmpInt;
                        sorted = false;
                    }
                if (sorted) break;
                for (int i = root_moves_num-1; i >= 1; i--)
                   if (mVals[i] > mVals[i-1]) {
                      //memcpy(&tmpMove2,moveBuf+i,sizeof(struct MOVE));
                      //memcpy(moveBuf+i,moveBuf+i-1,sizeof(struct MOVE));
                      //memcpy(moveBuf+i-1,&tmpMove2,sizeof(struct MOVE));
                *(int*)&tmpMove2=*(int*)(moveBuf+i);
                *(int*)(moveBuf+i)=*(int*)(moveBuf+i-1);
                *(int*)(moveBuf+i-1)=*(int*)&tmpMove2;

//                        tmpMove2 = moveBuf[i]; moveBuf[i] = moveBuf[i-1]; moveBuf[i-1] = tmpMove2;
                        tmpInt  = mVals[i];   mVals[i]   = mVals[i-1];   mVals[i-1]   = tmpInt;
                        sorted = false;
                    }
            }
        }

        if (root_moves_num != 0)
        {
            int i=0;
            while ((i<4) && (i < root_moves_num))
            {
                i++;
                if (mVals[0]-mVals[i] > RANDOMIZER_WINDOW) break;
            }

			int returned;

			if(i == 0)
				returned = 0;
			else
				returned = GetRnd(0, i-1);
            return moveBuf+returned;
        }
        else
        {
            return m;
        }


        //return m; //Возвращённый последний раз "лучший" ход.
	//С таким же успехом можно было бы вернуть mvs[0],
	//так как после сортировки лучший ход на нулевое место как раз и встанет
  
    }




   /*Генерация всех ходов в переданный буфер*/
     void Gen(struct MOVE *moves)
	{
        int i = 0;

		/*Пометить все "пришпиленные" фиругы, чтобы лишний раз не проверять шахи*/
        find_pins( check );

        for(square=L[Color].dest; square!=0; square=L[square].dest ) {
            int pbs=B[square]&0xFC;
            switch ( pbs ) {
                case PAWN: {
                    if(Color==WHITE) {
                        destination = square+10;
                        if( B[destination] == 0 ) {
                            if( destination < 91 ) /* not a promotion */ {
                                Gen_Push(MOVE_TYPE_NORMAL,moves,true);
                            }
                            else /* pawn promotion */ {
                                Gen_Push(MOVE_TYPE_PROMOTION_TO_QUEEN,moves,true);
                                //Gen_Push (MOVE_TYPE_PROMOTION_TO_KNIGHT,moves);
                            }
                            if( square < 41 ) {
                                destination += 10;
                                if( B[destination] == 0 )
                                    Gen_Push(MOVE_TYPE_ENPASANT,moves,true);
                            }
                        }
                        if (hist[hdp-1].m.type==MOVE_TYPE_ENPASANT) {
                             for( destination = square+9;
                                  destination <= square+11;
                                  destination += 2)
                                 if (destination==hist[hdp-1].enpas)
                                     Gen_Push(MOVE_TYPE_ENPASTAKE,moves,true);
                            }
                        for( destination = square+9;
                        destination != square+13;
                        destination += 2 )
                            if( (B[destination] & 0x3) == BLACK )
                                if( destination < 91 ) {
                                    Gen_Push(MOVE_TYPE_NORMAL,moves,true);
                                }
                                else {
                                    Gen_Push(MOVE_TYPE_PROMOTION_TO_QUEEN,moves,true);
                                    //Gen_Push (MOVE_TYPE_PROMOTION_TO_KNIGHT,moves);
                                }
                    }
                    else {
                        destination = square-10;
                        if( B[destination] == 0 ) {
                            if( destination > 28 ) /* not a promotion */ {
                                Gen_Push(MOVE_TYPE_NORMAL,moves,true);
                            }
                            else /* pawn promotion */ {
                                Gen_Push(MOVE_TYPE_PROMOTION_TO_QUEEN,moves,true);
                                //Gen_Push (MOVE_TYPE_PROMOTION_TO_KNIGHT,moves);
                            }
                            if( square > 78 ) {
                                destination -= 10;
                                if( B[destination] == 0 )
                                    Gen_Push(MOVE_TYPE_ENPASANT,moves,true);
                            }
                        }
                        if (hist[hdp-1].m.type==MOVE_TYPE_ENPASANT) {
                             for( destination = square-11;
                                  destination <= square-9;
                                  destination += 2)
                                 if (destination==hist[hdp-1].enpas)
                                     Gen_Push(MOVE_TYPE_ENPASTAKE,moves,true);
                            }
                        for( destination = square-9;
                        destination != square-13;
                        destination -= 2 )
                            if( (B[destination] & 0x3) == WHITE )
                                if( destination > 28 ) {
                                    Gen_Push(MOVE_TYPE_NORMAL,moves,true);
                                }
                                else {
                                    Gen_Push(MOVE_TYPE_PROMOTION_TO_QUEEN,moves,true);
                                    //Gen_Push (MOVE_TYPE_PROMOTION_TO_KNIGHT,moves);
                                }
                    }
                    break;
                }

                case KNIGHT: case KING: {
                    int j;
                    short *mov = (pbs==KING ? K_moves : N_moves);
                    for( j=0; j!=8; j++ ) {
                        destination = square+mov[j];
                        if( (B[destination] & Color) == 0 )
                            Gen_Push(MOVE_TYPE_NORMAL, moves,true);
                    }
                    break;
                }

                default: /* BISHOP, ROOK, QUEEN */ {
                    int d;
                    int d1 = (pbs==BISHOP ? 4 : 0);
                    int d2 = (pbs==ROOK   ? 4 : 8);
                    for( d=d1; d!=d2; d++ ) {
                        int step=RB_dirs[d];
                        destination=square;
                        for(;;)
                        {	destination += step;
                                if( ( (B[destination]&3) & Color ) == 0 )
                                    Gen_Push(MOVE_TYPE_NORMAL, moves,true);
                                if( B[destination] != 0 ) break;
                        }
                    }
                }
            }
        }

        if( ! check )
            if( Color == WHITE ) {
                /****** Short ******/
                if( ( hist[hdp-1].castling & WSHORT ) == 0 )
                    if( B[F1]==0 && B[G1]==0 )
                        if( attacktest(F1,BLACK)==0 && attacktest(G1,BLACK)==0 ) {
                            square = E1;
                            destination = G1;
                            Gen_Push(MOVE_TYPE_CASTLE, moves,true);
                        }
                /****** Long ******/
                if( ( hist[hdp-1].castling & WLONG ) == 0 )
                    if( B[B1]==0 && B[C1]==0 && B[D1]==0 )
                        if( attacktest(C1,BLACK)==0 && attacktest(D1,BLACK)==0 ) {
                            square = E1;
                            destination = C1;
                            Gen_Push(MOVE_TYPE_CASTLE, moves,true);
                        }
            }
            else /* Black */ {
                /****** Short ******/
                if( ( hist[hdp-1].castling & BSHORT ) == 0 )
                    if( B[F8]==0 && B[G8]==0 )
                        if( attacktest(F8,WHITE)==0 && attacktest(G8,WHITE) ==0) {
                            square = E8;
                            destination = G8;
                            Gen_Push(MOVE_TYPE_CASTLE, moves,true);
                        }
                /****** Long ******/
                if( ( hist[hdp-1].castling & BLONG ) == 0 )
                    if( B[B8]==0 && B[C8]==0 && B[D8]==0 )
                        if( attacktest(C8,WHITE)==0 && attacktest(D8,WHITE)==0 ) {
                            square = E8;
                            destination = C8;
                            Gen_Push(MOVE_TYPE_CASTLE, moves,true);
                        }
            }

    }

	/*Генерирует только взятия*/
     void generate_legal_captures(struct  MOVE *moves, int minval)
    {

        int i = 0;

        find_pins( check );

        for( square=L[Color].dest; square!=0; square=L[square].dest ) {
            int pbs=(B[square]&0xFC);
            switch ( pbs ) {
                case PAWN:
                    if(Color==WHITE)
                    {	destination = square+10;
                        if( B[destination] == 0 && destination>=A8 )
                        { Gen_Push(MOVE_TYPE_PROMOTION_TO_QUEEN, moves,false); }
                        else if (B[destination]==0 && destination >=A7)
                        { Gen_Push(MOVE_TYPE_NORMAL, moves,false); }
                            
                        for( destination = square+9;
                        destination != square+13;
                        destination += 2 )
                            if( (B[destination]&0x3) == BLACK )
                                if( destination < A8 )
                                    Gen_Push(MOVE_TYPE_NORMAL, moves,false);
                                else
                                    Gen_Push(MOVE_TYPE_PROMOTION_TO_QUEEN, moves,false);
                    }
                    else /* This is a black pawn */
                    {	destination = square-10;
                        if( B[destination] == 0 && destination<=H1 )
                        { Gen_Push(MOVE_TYPE_PROMOTION_TO_QUEEN, moves,false); }
                        else if (B[destination] == 0 && destination <=H2)
                        { Gen_Push(MOVE_TYPE_NORMAL, moves,false); }
                            
                        for( destination = square-9;
                        destination != square-13;
                        destination -= 2 )
                            if( (B[destination]&0x3) == WHITE )
                                if( destination > H1 )
                                    Gen_Push(MOVE_TYPE_NORMAL, moves,false);
                                else
                                    Gen_Push(MOVE_TYPE_PROMOTION_TO_QUEEN, moves,false);
                    }
                    break;
                case KNIGHT: case KING: {
                    int j;
                    short *mov = ((pbs==KING) ? K_moves : N_moves);
                    for( j=0; j!=8; j++ ) {
                        destination = square+mov[j];
                        if( (B[destination]&0x3) == BLACK+WHITE-Color )
                            Gen_Push(MOVE_TYPE_NORMAL, moves,false);
                    }
                }
                break;
                default: /* BISHOP, ROOK, QUEEN */ {
                    int d;
                    int d1 = pbs==BISHOP ? 4 : 0;
                    int d2 = pbs==ROOK   ? 4 : 8;
                    for( d=d1; d!=d2; d++ ) {
                        int step=RB_dirs[d];
                        destination=square;
                        for(;;)
                        {	destination += step;
                                if( (B[destination]&0x3) == BLACK+WHITE-Color )
                                   Gen_Push(MOVE_TYPE_NORMAL, moves,false);
                                   if( B[destination]!=0 ) break;
                        }
                    }
                }
            }
        }
    }


	/*Как-то просчитывает результат после осущесвления "размена в точке" до конца.*/
     int see(int *b, int from, int square ) {

        int wn, bn;
        int color = (b[from] & 0x3);
        int i,p;
        int minwn, minbn;


        //#define ret(X) return ( color==WHITE ? (X) : -(X) )

        wn=bn=1;
        if( color == WHITE ) {
            see_wl[0] = Values[ b[from] >> 4 ];
            see_bl[0] = Values[ b[square] >> 4 ];
        }
        else {
            see_wl[0] = Values[ b[square] >> 4 ];
            see_bl[0] = Values[ b[from] >> 4 ];
        }

        backup = b[from]; b[from] = 0;

        if( b[square-9]==WP )  { see_wl[wn] = P_VALUE; wn++; }
        if( b[square-11]==WP ) { see_wl[wn] = P_VALUE; wn++; }
        if( b[square+9]==BP )  { see_bl[bn] = P_VALUE; bn++; }
        if( b[square+11]==BP ) { see_bl[bn] = P_VALUE; bn++; }

        for( i=0; i!=8; i++ ) if( ( p = b[square+N_moves[i]] ) != 0 )
            switch( p ) {
                case WN: see_wl[wn] = N_VALUE; wn++; break;
                case BN: see_bl[bn] = N_VALUE; bn++; break;
            }

            see_wl[ minwn=wn ] = CHECKMATE;
            see_bl[ minbn=bn ] = CHECKMATE;

            for( i=0; i!=8; i++ ) {
                int step = RB_dirs[i];
                int minw = minwn;
                int minb = minbn;
                int dest = square;
                for(;;) {
                    dest += step;
                    while( b[dest] == 0 ) dest += step;
                    p = b[dest];
                    if( p==3 || (p&0xFC)==KNIGHT ) break;
                    if( i < 4 ) { if( (p&0xFC) == BISHOP ) break; }
                    else        { if( (p&0xFC) == ROOK ) break; }
                    if( p==WK ) {
                        if( dest-step==square )
                        { see_wl[wn] = CHECKMATE; wn++;
                          see_wl[wn] = CHECKMATE; }
                        break;
                    }
                    else if( p==BK ) {
                        if( dest-step==square )
                        { see_bl[bn] = CHECKMATE; bn++;
                          see_bl[bn] = CHECKMATE; }
                        break;
                    }
                    else if( p==WP ) {
                        if( dest-square == 9 || dest-square == 11 )
                            continue; else break;
                    }
                    else if( p==BP ) {
                        if( dest-square == -9 || dest-square == -11 )
                            continue; else break;
                    }
                    else {
                        int j;
                        int val = Values[p>>4];
                        if( (p & 0x3) == WHITE ) {
                            while( see_wl[minw] <= val ) minw++;
                            for( j=wn+1; j!=minw; j-- )
                                see_wl[j] = see_wl[j-1];
                            see_wl[minw] = val;
                            wn++; see_wl[wn]=CHECKMATE;
                            minw++;
                        }
                        else {
                            while( see_bl[minb] <= val ) minb++;
                            for( j=bn+1; j!=minb; j-- )
                                see_bl[j] = see_bl[j-1];
                            see_bl[minb] = val;
                            bn++; see_bl[bn]=CHECKMATE;
                            minb++;
                        }
                    }
                }
            }

            b[from] = backup;

            {
                int wi=0; int bi=0; int result=0;
                int alpha=-CHECKMATE, beta=CHECKMATE;

                if( color == BLACK )
                { result -= see_wl[wi]; wi++; alpha = result; }

                for(;;) {
                    if( wi == wn ) return((Color==WHITE)?alpha:-alpha);
                    else {
                        result += see_bl[bi]; bi++;
                        if( result < beta )
                        { if( result < alpha ) return((Color==WHITE)?alpha:-alpha); beta = result; }
                    }

                    if( bi == bn ) return((Color==WHITE)?beta:-beta);
                    else {
                        result -= see_wl[wi]; wi++;
                        if( result > alpha )
                        { if( result > beta ) return((Color==WHITE)?beta:-beta); alpha = result; }
                    }
                }
            }

    }

     void find_pins( boolean check ) {
        int d, square;

        if(check)
        { for (int i=20; i < 100; i++) pin[i]=1; return; }

        for (int i=20; i < 100; i++) pin[i]=0;

        square = L[Color].dest;

        pin[square] = 1;

        for(d=0;d!=8;d++) {
            int step = RB_dirs[d];
            int destination = square;
            int mark = 0;
            for(;;) {
                destination += step;
                if( B[destination] != 0 ) {
                    if( (B[destination] & 0x3) == Color ) {
                        if(mark != 0) break;
                        mark = destination;
                    }
                    else {
                        if(mark != 0) {
                            switch( B[destination] & 0xFC ) {
                                case QUEEN:

                                    pin[mark]=(byte)abs(step);
                                    break;
                                case ROOK:
                                    if(d<4) pin[mark]=(byte)abs(step);
                                    break;
                                case BISHOP:
                                    if(d>3) pin[mark]=(byte)abs(step);
                                    break;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }

     void find_targets() {
        int d,square;

        for (int i=20; i < 100; i++) tar[i]=0;

        square = L[BLACK+WHITE-Color].dest;

        for(d=0;d!=8;d++) {
            int step = RB_dirs[d];
            int destination = square;
            for(;;) {
                destination += step;
                if( B[destination] != 0 ) break;
                if( d<4 ) tar[destination]=ROOK;
                else tar[destination]=BISHOP;
            }

            if( B[(destination=square+N_moves[d])] == 0 ) tar[destination]=KNIGHT;
        }
    }

     int attacktest( int square, int ocolor ) {

        /* pawn */
        if(ocolor!=1)
        { if( B[square+11]==BP || B[square+9]==BP ) return 2; }
        else
        { if( B[square-11]==WP || B[square-9]==WP ) return 2; }

        /* knight */
        {
            int i, enemy = KNIGHT+ocolor;
            for( i=0; i!=8; i++ )
                if( B[square+N_moves[i]] == enemy ) return 2;
        }

        /* rook or queen */
        {
            int d, enemy1 = ROOK+ocolor, enemy2 = QUEEN+ocolor;
            for( d=0; d!=4; d++ ) {
                int i=square; int step=RB_dirs[d];
                do i += step; while( B[i] == 0 );
                if( B[i]==enemy1 || B[i]==enemy2 ) return 2;
            }
        }

        /* bishop or  queen */
        {
            int d, enemy1 = BISHOP+ocolor, enemy2 = QUEEN+ocolor;
            for( d=4; d!=8; d++ ) {
                int i=square; int step=RB_dirs[d];
                do i += step; while( B[i] == 0 );
                if( B[i]==enemy1 || B[i]==enemy2 ) return 2;
            }
        }

        /* king */
        if( max_dist(square, L[ocolor].dest) == 1 ) return 1;

        return 0;
    }

     boolean checktest(int side) {
        return (attacktest( (side==WHITE)?(L[1].dest):(L[2].dest), BLACK+WHITE-side) != 0);
    }






                    int score_position() {

                       // System.out.println ();
                       //System.out.println ("Entered scoring");
                       //System.out.println ();


                       /**
                        ***  We always compute both 'endgame' value and 'middlegame' position
                        ***  value.  After they are computed, they are balanced by total material.
                        ***  This prevents evaluation to do big jumps when searching a position
                        ***  on the edge of middlegame and endgame.
                        ***
                        ***  Evaluation is done in two passes:
                        ***  1) Extract knowledge (see typedef tknow), prepare mirrored board.
                        ***  2) Use knowledge.  Thanks to mirroring board in first pass, we dont
                        ***     have to write evaluation of specific things twice (for white and
                        ***     black separately).  This might also make better use of internal
                        ***     cache on small machines.
                        **/

                       int i;

                       int midresult, endresult, result;

                       int whp, bhp; /* sum of hung pieces. >=2 means troubles -> big penalty. */

                       int kp, xkp; /* this side and other side king position */

                       int npin;

                       npin=0;
                       Totmat=0;
                       Totmat = hist[hdp-1].mtrl;
                       Totmat += hist[hdp-1].xmtrl;

                       /***************************************************************/

                       if( Totmat <= (R_VALUE+R_VALUE+P_VALUE) ) 
                       {
                           /* if there are no pieces, return special pawn endgame evaluation */
                           /* [moved, computed later] */

        /* Now, check some special endgame positions that are known to be
         * hopeless draw (this might also cause pruning of the search). */
                           switch(Totmat) 
                           {
                               case (B_VALUE+P_VALUE): /* minor piece and pawn */
                               {	int r = e_mp();
                                        if( r!=0 ) return ( (Ply%2!=0) ? -DrawScore : DrawScore )+r;
                               }
                               break;
                               case (N_VALUE+N_VALUE): /* minor against minor or two knights */
                                   if( hist[hdp-1].mtrl == N_VALUE ) /* minor:minor */
                                       if( hist[hdp-1].cap == 0 ) return ( (Ply%2!=0) ? -DrawScore : DrawScore );
                                       { int nn=0;
                                         for( i=L[(L[1].dest)].dest; i!=0; i=L[i].dest )
                                             if( B[i] == WN ) nn++;
                                         if( nn == 1 ) return e_nb(WHITE);
                                         if( nn == 2 ) return
                                         Color==WHITE ?
                                         ( (Ply%2!=0) ? -DrawScore : DrawScore )-(N_VALUE+N_VALUE)
                                         : ( (Ply%2!=0) ? -DrawScore : DrawScore )+(N_VALUE+N_VALUE);
                                         if( nn == 0 ) {
                                             for( i=L[(L[2].dest)].dest; i!=0; i=L[i].dest )
                                                 if( B[i] == BN ) nn++;
                                             if( nn == 1 ) return e_nb(BLACK);
                                             if( nn == 2 ) return
                                             Color==WHITE ?
                                             ( (Ply%2!=0) ? -DrawScore : DrawScore )+(N_VALUE+N_VALUE)
                                             : ( (Ply%2!=0) ? -DrawScore : DrawScore )-(N_VALUE+N_VALUE);
                                         }
                                       }
                                       break;
                               case (R_VALUE+R_VALUE+P_VALUE):  /* RPr */
                                   if( abs(hist[hdp-1].mtrl-hist[hdp-1].xmtrl) == P_VALUE ) {
                                       int np=0;
                                       for( i=L[(L[1].dest)].dest; i!=0; i=L[i].dest ) np++;
                                       for( i=L[(L[2].dest)].dest; i!=0; i=L[i].dest ) np++;
                                       if( np == 3 ) return e_rpr();
                                   }
                                   break;
                           }
                       }
                       
                       if (hist[hdp-1].mtrl==0 || hist[hdp-1].xmtrl==0)
                       {
                           if (find_queen(WHITE)!=0 || find_queen(BLACK)!=0) return e_q();
                       }
                       
                       
                       result = midresult = endresult = whp = bhp = npin = 0;

                       for (i=20; i < 100; i++) mB[i] = mBinit[i];
                       wn = bn = 1; /* King ... at least */
                       for(i=0;i!=10;i++) wpf[i]=bpf[i]=0;

                       /*OPTIMAL WAY ??*/
                       Wknow.b=Wknow.bishopcolor=Wknow.devel=Wknow.kp=Wknow.kstorm=Wknow.lpf=Wknow.n=Wknow.p=Wknow.q=Wknow.qstorm=Wknow.qstorm=Wknow.r=Wknow.r7r=Wknow.rpf=Wknow.worsebm=Wknow.xbishopcolor=0; Wknow.hung=Wknow.khung=Wknow.kshield=0;
                       Wknow.prune=false;
                       Wknow.castling=0;
                       Bknow.b=Bknow.bishopcolor=Bknow.devel=Bknow.kp=Bknow.kstorm=Bknow.lpf=Bknow.n=Bknow.p=Bknow.q=Bknow.qstorm=Bknow.qstorm=Bknow.r=Bknow.r7r=Bknow.rpf=Bknow.worsebm=Bknow.xbishopcolor=0; Bknow.hung=Bknow.khung=Bknow.kshield=0;
                       Bknow.prune=false;
                       Bknow.castling=0;

                       for (i=0; i < 120; i++)
                           P[i]=0;

                       Wknow.kp = (L[1].dest); Wknow.worsebm = 100;
                       Wknow.lpf = 9;
                       Bknow.kp = (L[2].dest); Bknow.worsebm = 100;
                       Bknow.lpf = 9;

                       //System.out.println ("Got before White mobi-cycle");
                       /************************************************/

                       i=(L[1].dest); mB[ Th[i] ] = BK; wl[0] = i;
                       for( i=L[i].dest; i!=0; i=L[i].dest ) {
                           int j; int mobi;
                           switch( B[i] ) {
                               case WP:
                                   //System.out.println ("Got before WHITE PAWN");
                                   mB[ Th[i] ] = BP; wl[wn] = i; wn++;
                                   wpf[i%10]++;
                                   if(i%10<Wknow.lpf) Wknow.lpf=(byte)(i%10);
                                   if(i%10>Wknow.rpf) Wknow.rpf=(byte)(i%10);
                                   Wknow.p++;
                                   for( j=i+9; j<=i+11; j+=2 ) { P[j] |= WPM; P[j] += WWW; }
                                   if( i>=A6 && B[i+10]==0 ) /* Passed pawn */
                                   { Bknow.hung+=4;
                                     if(B[i+20]==0||B[i+20]==3) Bknow.hung+=16;
                                   }
                                   break;
                               case WN:
                                   //System.out.println ("Got before WHITE KNIGHT");
                                   mB[ Th[i] ] = BN; wl[wn] = i; wn++;
                                   Wknow.n++;
                                   for( j=0; j!=8; j++ )
                                   { int d = i+N_moves[j]; P[d] |= WNM; P[d] += WWW; }
                                   break;
                               case WB:
                                   //System.out.println ("Got before WHITE BISHOP");
                                   mB[ Th[i] ] = BB; wl[wn] = i; wn++;
                                   Wknow.b++;
                                   Wknow.bishopcolor  |= sqcolor[i];
                                   Bknow.xbishopcolor |= 3-sqcolor[i];
                                   mobi = 4;
                                   for( j=4; j!=8; j++ )
                                   { int step = RB_dirs[j]; int d = i;
                                     do {
                                         d+=step;
                                         mobi++;
                                         P[d] |= WBM;
                                         P[d] += WWW;
                                     }
                                     while( B[d] == 0 );
                                     if( (B[d] & WHITE) != 0 ) /* edge or friendly piece */ {
                                         mobi--;
                                         if( B[d]==3 || ( B[d]==WP && B[d+10]!=0 ) ) mobi--;
                                     }
                                     else
                                         if( B[d]==BN || B[d]==BR || B[d]==BQ )
                                         { pin[npin]=(byte)d;
                                           do d+=step; while( B[d]==0 );
                                           if( B[d]==BQ || B[d]==BK ) npin++;
                                         }
                                   }
                                   result += B_mobi[mobi];
                                   if( mobi < Wknow.worsebm ) Wknow.worsebm = (byte)mobi;
                                   break;
                               case WR:
                                   mB[ Th[i] ] = BR; wl[wn] = i; wn++;
                                   //System.out.println ("Got before WHITE ROOK");
                                   if( i>=A7 && i<=H7 ) Wknow.r7r+=2;
                                   Wknow.r++;
                                   mobi = 0;
                                   for( j=0; j!=4; j++ )
                                   { int step = RB_dirs[j]; int d = i;
                                     do { d += step; mobi++; P[d] |= WRM; P[d] += WWW;}
                                     while( B[d] == 0 );
                                     if( (B[d] & WHITE) != 0 ) mobi--;
                                     else
                                         if( B[d]==BN || B[d]==BB || B[d]==BQ )
                                         { pin[npin]=(byte)d;
                                           do d+=step; while( B[d]==0 );
                                           if( B[d]==BQ || B[d]==BK ) npin++;
                                         }
                                   }
                                   result += R_mobi[mobi];
                                   break;
                               case WQ:
                                   //System.out.println ("Got before WHITE QUEEN");
                                   mB[ Th[i] ] = BQ; wl[wn] = i; wn++;
                                   if( i>=A1 && i<=H3 ) Wknow.r7r++;
                                   Wknow.q++;
                                   for( j=0; j!=8; j++ )
                                   { int step = RB_dirs[j]; int d = i;
                                     do { d += step; P[d] |= WQM; P[d] += WWW; }
                                     while( B[d] == 0 );

                                     if( B[d]==BN || ( B[d]==BB && d<4 ) || ( B[d]==BR && d>=4 ) )
                                     { pin[npin]=(byte)d;
                                       do d+=step; while( B[d]==0 );
                                       if( B[d]==BK ) npin++;
                                     }
                                   }
                                   break;
                           }
                       }
                       //System.out.println("Got before Black mobi-list. Result is " + Integer.toString(result));

                       i=(L[2].dest); mB[ Th[i] ] = WK; bl[0] = Th[i];
                       for( i=L[i].dest; i!=0; i=L[i].dest ) {
                           int j;
                           int mobi;
                           switch( B[i] ) {
                               case BP:
                                   //System.out.println("Got before Black PAWN");
                                   mB[ Th[i] ] = WP; bl[bn] = Th[i]; bn++;
                                   bpf[i%10]++;
                                   if(i%10<Bknow.lpf) Bknow.lpf=(byte)(i%10);
                                   if(i%10>Bknow.rpf) Bknow.rpf=(byte)(i%10);
                                   Bknow.p++;
                                   for( j=i-11; j<=i-9; j+=2 ) { P[j] |= BPM; P[j] += BBB; }
                                   if( i<=H3 && B[i-10]==0 )
                                   { Wknow.hung+=4;
                                     if(B[i-20]==0||B[i-20]==3) Wknow.hung+=16;
                                   }
                                   break;
                               case BN:
                                   //System.out.println("Got before Black KNIGHT");
                                   mB[ Th[i] ] = WN; bl[bn] = Th[i]; bn++;
                                   Bknow.n++;
                                   for( j=0; j!=8; j++ )
                                   { int d = i+N_moves[j]; P[d] |= BNM; P[d] += BBB; }
                                   break;
                               case BB:
                                   //System.out.println("Got before Black BISHOP");
                                   mB[ Th[i] ] = WB; bl[bn] = Th[i]; bn++;
                                   Bknow.b++;
                                   Bknow.bishopcolor  |= 3-sqcolor[i];
                                   Wknow.xbishopcolor |= sqcolor[i];
                                   mobi = 4;
                                   for( j=4; j!=8; j++ )
                                   { int step = RB_dirs[j]; int d = i;
                                     do { d += step; mobi++; P[d] |= BBM; P[d] += BBB; }
                                     while( B[d] == 0 );
                                     if( (B[d] & BLACK) != 0 ) {
                                         mobi--;
                                         if( B[d]==3 || ( B[d]==BP && B[d-10]!=0 ) ) mobi--;
                                     }
                                     else
                                         if( B[d]==WN || B[d]==WR || B[d]==WQ )
                                         { pin[npin]=(byte)d;
                                           do d+=step; while( B[d]==0 );
                                           if( B[d]==WQ || B[d]==WK ) npin++;
                                         }
                                   }
                                   result -= B_mobi[mobi];
                                   if( mobi < Bknow.worsebm ) Bknow.worsebm = (byte)mobi;
                                   break;
                               case BR:
                                   //System.out.println("Got before Black ROOK");
                                   mB[ Th[i] ] = WR; bl[bn] = Th[i]; bn++;
                                   if( i>=A2 && i<=H2 ) Bknow.r7r+=2;
                                   Bknow.r++;
                                   mobi = 0;
                                   for( j=0; j!=4; j++ )
                                   { int step = RB_dirs[j]; int d = i;
                                     do { d += step; mobi++; P[d] |= BRM; P[d] += BBB; }
                                     while( B[d] == 0 );
                                     if( (B[d] & BLACK) != 0 ) mobi--;
                                     else
                                         if( B[d]==WN || B[d]==WB || B[d]==WQ )
                                         { pin[npin]=(byte)d;
                                           do d+=step; while( B[d]==0 );
                                           if( B[d]==WQ || B[d]==WK ) npin++;
                                         }
                                   }
                                   result -= R_mobi[mobi];
                                   break;
                               case BQ:
                                   //System.out.println("Got before Black QUEEN");
                                   mB[ Th[i] ] = WQ; bl[bn] = Th[i]; bn++;
                                   if( i>=A1 && i<=H3 ) Bknow.r7r++;
                                   Bknow.q++;
                                   for( j=0; j!=8; j++ )
                                   { int step = RB_dirs[j]; int d = i;
                                     do { d += step; P[d] += BBB; P[d] |= BQM; }
                                     while( B[d] == 0 );
                                     if( B[d]==WN || ( B[d]==WB && d<4 ) || ( B[d]==WR && d>=4 ) )
                                     { pin[npin]=(byte)d;
                                       do d+=step; while( B[d]==0 );
                                       if( B[d]==WK ) npin++;
                                     }
                                   }
                                   break;
                           }
                       }

                       //System.out.println("Got before pini-cycle. Tatally npin: " + Integer.toString(npin) + "  Result is: "  + Integer.toString(result));



                       if( Totmat == P_VALUE*(Wknow.p+Bknow.p) )
                       { /* only pawns */ return pawns(); }

                       /**
                        ***   Scan pinned pieces
                        **/
                       { int pini;
                         for( i=0; i!=npin; i++ )
                             switch( B[ pini = pin[i] ] ) {
                                 case WQ: result -= 50; Wknow.hung += 20;
                                 break;
                                 case BQ: result += 50; Bknow.hung += 20;
                                 break;
                                 case WN: case WB: case WR:
                                     if( (P[pini] & WPM) == 0 ) /* not pawn-protectd */
                                     { Wknow.hung += 6; result += -15*(P[pini]>>13); }
                                     else result += -6*(P[pini]>>13);
                                     if( (P[pini] & BPM) != 0) { Wknow.hung += 5; result -= 15; }
                                     break;
                                 case BN: case BB: case BR:
                                     if( (P[pini] & BPM) == 0 )
                                     { Bknow.hung += 6; result +=  15*((0x00F0&P[pini])>>5); }
                                     else result +=  6*((0x00F0&P[pini])>>5);
                                     if( (P[pini] & WPM) != 0 ) { Bknow.hung += 5; result += 15; }
                                     break;
                             }
                       }

                       /**
                        ***   Look for hung pieces & weak pawns
                        **/
                       //System.out.println ("Got before hung pieces. Result is " + Integer.toString(result));
                       {
                           for( i=L[(L[1].dest)].dest; i!=0; i=L[i].dest )
                               if( (P[i]&0xFF00) != 0) /* Black attacks the square 'i' */ {
                                   if( (P[i]&0x00FF)==0 /* undefended */
                                   || ( ((m[B[i]] & (P[i]>>8)) !=0) ) /* attacked by less valuable */ )
                                       switch(B[i])
                                       { case WP: Wknow.hung += 8; break;
                                           case WN:
                                           case WB: whp++; Wknow.hung+=12; break;
                                           case WR: whp++; Wknow.hung+=14; break;
                                           case WQ: whp++; Wknow.hung+=16;
                                       }
                                   else if( (P[i]&WPM) == 0 ) /* not pawn-protected */
                                       if(B[i]==WP) result += (P[i]>>13)*5;
                                       else Wknow.hung += 6;
                               }

                           for( i=L[(L[2].dest)].dest; i!=0; i=L[i].dest )
                               if((P[i]&0x00FF) != 0) /* white attacks this square */ {
                                   if( (P[i]&0xFF00)==0 || ( (m[B[i]] & P[i]) != 0) )
                                       switch(B[i])
                                       { case BP: Bknow.hung += 8; break;
                                           case BN:
                                           case BB: bhp++; Bknow.hung+=12; break;
                                           case BR: bhp++; Bknow.hung+=14; break;
                                           case BQ: bhp++; Bknow.hung+=16;
                                       }
                                   else if( (P[i]&BPM) == 0 ) /* not pawn-protected */
                                       if(B[i]==BP) result -= ((P[i]>>5)&0x7)*5;
                                       else Bknow.hung += 6;
                               }

                           if( whp>1 ) Wknow.hung += 8*whp;
                           if( bhp>1 ) Bknow.hung += 8*bhp;
                       }

                       //System.out.println("Got before King safety. Result is "  + Integer.toString(result));
                       /*** King safety ***/
                       for(i=0;i!=8;i++) {
                           int direction = K_moves[i];
                           int d=Wknow.kp+direction;
                           if(B[d]!=3) {
                               int ataks = (P[d]>>13) & 0x7;
                               if(ataks != 0) {
                                   int defs = (P[d]>>5) & 0x7;
                                   Wknow.khung += ataks;
                                   if( defs == 0 ) {
                                       Wknow.khung ++;
                                       if( ataks>1 && (P[d]&BQM)!=0 )
                                           Wknow.khung += 2;
                                   }
                               }

                               /*** Add number of safe checks available ***/
                               if( B[d]==0 ) {
                                   d += direction;
                                   while( (B[d]&BLACK) == 0 ) {
                                       if( ( P[d] & 0xE0 ) == 0 ) {
                                           if( i<4 )
                                           { if( (P[d] & (BQM|BRM))!=0 )
                                             { Wknow.khung +=2; break; } }
                                           else
                                           { if( (P[d] & (BQM|BBM)) != 0 )
                                             { Wknow.khung +=2; break; } }
                                       }
                                       if( B[d] != 0 ) break;
                                       d += direction;
                                   }
                               }
                               d = Wknow.kp+N_moves[i];
                               if( (P[d]&BNM)!=0 && ((B[d]&BLACK) == 0) && (( P[d] & 0xE0 ) == 0) )
                                   Wknow.khung += 2;
                           }

                           d=Bknow.kp+direction;
                           if(B[d]!=3) {
                               int ataks = (P[d]>>5) & 0x7;
                               if(ataks!=0) {
                                   int defs = (P[d]>>5) & 0x7;
                                   Bknow.khung += ataks;
                                   if( defs == 0 ) {
                                       Bknow.khung ++;
                                       if( ataks>1 && (P[d]&WQM)!=0 )
                                           Bknow.khung += 2;
                                   }
                               }

                               /*** Add number of safe checks available ***/
                               if( B[d]==0 ) {
                                   d += direction;
                                   while( (B[d]&WHITE) == 0 ) {
                                       if( ( P[d] & 0xE000 ) == 0 ) {
                                           if( i<4 )
                                           { if( (P[d] & (WQM|WRM))!=0 )
                                             { Bknow.khung +=2; break; } }
                                           else
                                           { if( (P[d] & (WQM|WBM))!=0 )
                                             { Bknow.khung +=2; break; } }
                                       }
                                       if( B[d]!=0 ) break;
                                       d += direction;
                                   }
                               }
                               d = Bknow.kp+N_moves[i];
                               if( (P[d]&WNM)!=0 && (B[d]&WHITE) == 0 && ( P[d] & 0xE000 ) == 0 )
                               { Bknow.khung += 2; }
                           }
                       }

                       if( Totmat >= ENDMATERIAL+Q_VALUE )
                           if( Wknow.kp%10 < FILE_E && Bknow.kp%10 > FILE_E )
                           { Wknow.kstorm = 1; Bknow.qstorm = 1; }
                           else
                               if( Wknow.kp%10 > FILE_E && Bknow.kp%10 < FILE_E )
                               { Wknow.qstorm = 1; Bknow.kstorm = 1; }

                       if( Wknow.hung!=0 || Bknow.hung!=0 ) {
                           int hresult = Bknow.hung - Wknow.hung;
                           midresult += hresult;
                           endresult += hresult;
                       }

                       Wknow.castling = (short)( hist[hdp-1].castling & 3 );
                       Bknow.castling = (short)( hist[hdp-1].castling >> 2 );

                       if( ((P[G1]|P[F1]) & 0xFF00)!=0 ) Wknow.castling |= WSHORT;
                       if( ((P[C1]|P[D1]) & 0xFF00)!=0 ) Wknow.castling |= WLONG;

                       if( ((P[G8]|P[F8]) & 0x00FF)!=0 ) Bknow.castling |= WSHORT; /* WSHORT is correct! */
                       if( ((P[C8]|P[D8]) & 0x00FF)!=0 ) Bknow.castling |= WLONG;  /* We're mirroring */
                       //System.out.println ("P[C8] is  " + Integer.toString(P[C8]&0xFF));

                       //System.out.println ("Got before pass-2.  KHUNGS are" + Integer.toString (Wknow.khung) + "/" + Integer.toString (Bknow.khung));

                       /**
                        ***   PASS 2
                        **/
                       n = wn; l = wl; b = B;
                       pf = wpf; xpf = bpf;
                       know = Wknow; xknow = Bknow;
                       kp = Wknow.kp; xkp = Bknow.kp;
                       for(;;) {
                           int j;
                           int mr = 0, er = 0;

                           /* bishop pair */
                           if( know.bishopcolor == 3 ) {
                               int bb = 18 + 2*know.worsebm;
                               mr += bb;
                               er += bb*2;
                           }
                           //System.out.println ("mr after bishoping is " + Integer.toString(mr));

                           /* rooks on 7th row */
                           /* r7r: 2 pts for rook, 1 pt for queen on 6-8th row */
                           if( know.r7r > 1 ) {
                               if( xkp >= A8 )
                               { er += 12 * know.r7r; mr += 5 * know.r7r; }
                               mr += 10 * know.r7r; er += 4 * know.r7r;
                               if( know.r7r > 2 ) mr += know.r7r * know.r7r + 4;
                           }
                           //System.out.println ("mr after r7r is " + Integer.toString(mr));

                           if( Totmat >= ENDMATERIAL ) {
                               int d = 0;

                               /*** play Pc2-c4 (black Pc7-c5) in closed games ***/
                               if( b[D5]==BP ) {
                                   if( b[C4]==WP )
                                   {	mr+=10;
                                        if( b[E6]==BP && B[D4]==WP ) mr+=10;
                                        /*** defender in stonewall must keep pressure
                                         *** to opponent's d-pawn ****/
                                        if( b[F5]==BP ) mr+=15;
                                   }
                                   if( b[C2]==WP ) {
                                       if( b[C3]!=0 ) mr -= 7;
                                       else           mr -= 3;
                                       if( b[E2]==WP || b[E3]==WP ) mr -= 5;
                                       if( b[E6]==BP || b[C6]==BP ) mr -= 4;
                                   }
                               }

                               //System.out.println ("mr after c2c4 is " + Integer.toString(mr));


                               /*** development ***/
                               if( b[A1] == WR && pf[FILE_A] != 0 ) d+=2;
                               if( b[B1] == WN ) d+=5;
                               if( b[C1] == WB ) { d+=3; if( b[B2]!=0 && b[D2]!=0 ) d+=4; }
                               if( b[D1] == WQ ) d++;
                               if( b[F1] == WB ) { d+=3; if( b[E2]!=0 && b[G2]!=0 ) d+=4; }
                               if( b[G1] == WN ) d+=5;
                               if( b[H1] == WR && pf[FILE_H] != 0 ) d+=2;

                               know.devel = (byte)d; /* maximum is 29, <10 is okay */
                               //System.out.println ("Devel is " + Integer.toString(d));

                               /*** central pawns ***/
                               if( b[D4]==WP && b[E4]==WP ) {
                                   if( b[E5]!=BP && b[D5]!=BP ) d = 12; else d = 6;
                                   if( b[C4]==WP || b[F4]==WP ) d += 4;

                                   mr += d;

                               }

                               {
                                   //System.out.println ("mr before castling is " + Integer.toString(mr));
                                   //System.out.println("Got before castling");
                                   /*** castling ***/
                                   int cneed;
                                   d = 0;
                                   if( kp%10 < FILE_D || kp%10 > FILE_E ) cneed=0;
                                   else {
                                       cneed = 4;
                                       if(  pf[FILE_E] ==0 ) cneed += 3;
                                       if(  xpf[FILE_E] ==0) cneed += 5;
                                   }
                                   //System.out.println ("cneed is " + Integer.toString(cneed));
                                   //System.out.println ("castling is " + Integer.toString(know.castling));

                                   switch( know.castling ) {
                                       case 0:               /* both castlings possible */
                                           if( b[F1]!=0 ) d -= 2*cneed;
                                           if( b[G1]!=0 ) d -= 2*cneed;
                                           if( b[B1]!=0 ) d -= cneed;
                                           if( b[C1]!=0 ) d -= cneed;
                                           if( b[D1]!=0 ) d -= cneed;
                                           break;
                                       case WSHORT:          /* only long castling possible */
                                           d-=20;
                                           if( b[B1]!=0 ) d -= cneed;
                                           if( b[C1]!=0 ) d -= cneed;
                                           if( b[D1]!=0 ) d -= cneed;
                                           break;
                                       case WLONG:           /* only short castling possible */
                                           d-=8;
                                           if( b[F1]!=0 ) d -= 2*cneed;
                                           if( b[G1]!=0 ) d -= 2*cneed;
                                           break;
                                       case (WSHORT|WLONG):  /* castling impossible */
                                           if( kp%10 > FILE_E ) {
                                               if( b[G2]!=WP && b[G3]!=WP ) d -= 10;
                                               if( b[H2]!=WP && b[H3]!=WP ) d -= 8;
                                           }
                                           else if( kp%10 < FILE_D ) {
                                               d -= 15;
                                               if( b[B2]!=WP && b[B3]!=WP ) d -= 10;
                                               if( b[A2]!=WP && b[A3]!=WP ) d -= 8;
                                           }
                                           else
                                           { d -= 5*cneed; }
                                           break;
                                   }

                                   //System.out.println ("d before totmat-5000 is " + Integer.toString(d));

                                   if( Totmat < 5000 ) d /= 2;

                                   mr += d;

                               }
                               //System.out.println("Got after castling.   M/E-Results are " + Integer.toString(mr) + "/" + Integer.toString (er));

                           }

                           /*** pawn structure ***/
                           for( i=1; i!=9; i++ ) if( pf[i] != 0 ) {
                               if( pf[i] > 1 ) /* doubled */ { mr-=5; er-=10; }

                               if( pf[i-1]==0 && pf[i+1]==0 ) /* isolated */ {
                        /* knights are strong against an isolated pawn
                         * since they can block it. */
                                   int pen = isofile[i]
                                   + (2+isofile[i]) * xknow.n
                                   + 4*know.b;

                        /* rooks are strong against an isolated pawn on
                         * open file */
                                   if( xpf[i]==0 && xknow.r!=0 ) {
                                       for( j=i+20; j<H9; j+=10 ) if( b[j]==BR )
                                           pen += rfip[i];
                                       pen += (rfip[i]-2)*xknow.r;
                                   }

                                   if( pf[i] > 1 ) pen = pen*pf[i] + 2*isofile[i];

                                   mr += pen; er += pen;
                               }
                           }

                           //System.out.println ("Got before SCAN PIECES.  M/E-Results are " + Integer.toString(mr) + "/" + Integer.toString (er));
                           for( i=0; i!=n; i++ ) /* scan pieces */ {
                               int sq;
                               sq = l[i];
                               switch( b[ sq ] ) {
                                   case WP:
                                       /* is it passed? */

                                       passed: {
                                           for( j=sq+10; j<A8; j+=10 )
                                               if( b[j-1]==BP || b[j]==BP || b[j+1]==BP )
                                                  // break passed;
                                           goto not_passed;
                                           /* yes, the pawn is passed */

                                           int row = sq/10;
                                           int abonus = P_advance[row];
                                           int ppeval = abonus;

                                           if( b[sq+10]==0 ) {
                                               if( row==8 )
                                               { if(see(b,sq,sq+10)>=0) ppeval+=80; }
                                               else
                                                   if( row==7 && b[sq+20]==0 )
                                                       if( see(b,sq,sq+10)>=0 && see(b,sq,sq+20)>=0 )
                                                           ppeval+=50;
                                           }
                                           else /* blocked */
                                               if( (b[sq+10]&0x3) == BLACK ) ppeval-=abonus/2;

                                           /* blocked - reserve blocking square */
                                           if( (b[sq+20]&0x3) == BLACK ) ppeval-=abonus/4;

                                           /* covered or a member of a phalanx */
                                           if( b[sq-9]==WP || b[sq-11]==WP
                                           || b[sq-1]==WP || b[sq+1]==WP )
                                           { ppeval += 2*abonus; }

                                           /* rook behind - support or brake */
                                           for( j=sq-10;
                                           b[j]==0 || b[j]==WR || b[j]==BR
                                           || b[j]==BQ || b[j]==WQ;
                                           j-=10 )
                                               if( b[j] == WR )
                                               { ppeval += abonus/2 + 4; }
                                               else if( b[j] == BR )
                                               { ppeval -= abonus/2 + 9; }

                                           if( Totmat < ENDMATERIAL ) {
                                               /* distance from enemy king */
                                               int difdis
                                               = 2*max_dist(xkp, sq+10) - ( 9 - row );

                                               if( difdis >= 0 ) ppeval += 8+4*difdis;

                                               /* king supports the pawn */
                                               if( max_dist(kp, sq+10) < 2 ) ppeval += abonus;
                                           }

                                           er += ppeval;
                                           mr += ppeval/2;

                                       }

                                       not_passed:;

                                       /* backward */
                                       if(     sq <= H3
                                       && ( b[sq+19]==BP || b[sq+21]==BP )
                                       && b[sq+10] != BP
                                       && b[sq-1]  != WP
                                       && b[sq+1]  != WP
                                       && b[sq-9]  != WP
                                       && b[sq-11] != WP    ) {
                                           int pen = 0;

                                           if( xpf[sq%10]==0 && xknow.r!=0 ) {
                                               for( j=sq%10+20; j<H9; j+=10 ) if( b[j]==BR )
                                                   pen += -2 + isofile[sq%10]/2;
                                               pen += isofile[sq%10]*xknow.r;
                                           }

                                           mr += isofile[ sq%10 ] + pen/2;
                                           er += -15 + pen;
                                       }

                                       /* cannot move */
                                       {
                                           int cannotmove = 0;

                                           if( b[ sq + 10 ] != 0 ) {
                                               mr -= (12-sq/10); er -= (12-sq/10);
                                               if( sq == E2 || sq == D2 )
                                               { mr -= 10; er -= 8; }

                                               if( b[ sq + 10 ]!=0 ) {	/* blocked pawn is an attack brake */
                                                   if( know.kstorm!=0 && sq%10 > FILE_E )
                                                       mr -= 12;
                                                   else
                                                       if( know.qstorm!=0 && sq%10 < FILE_D )
                                                           mr -= 12;

                                                   if( b[sq+10]==BP
                                                   && pf[sq%10-1]==0
                                                   && pf[sq%10+1]==0 )
                                        /* this pawn was already penalized
                                         * as isolated. But this is a pawn
                                         * ram - blocked by enemy pawn
                                         * face to face. It is not so
                                         * critical; take back a small part
                                         * of the penalty. *********/
                                                   { mr+=5; er+=8; }
                                               }

                                               cannotmove = 1;
                                           }
                                           else {
                                               int ata=0;
                                               if( b[ sq - 1 ] == WP ) ata++;
                                               if( b[ sq + 1 ] == WP ) ata++;
                                               if( b[ sq + 9 ] == BP ) ata--;
                                               if( b[ sq +11 ] == BP ) ata--;

                                               if( ata < 1 ) {
                                                   mr += -4+ata; er += -8+2*ata;
                                                   cannotmove = 1;
                                               }
                                           }

                                           if( cannotmove!=0 ) {
                                               int p = 1 + ((b[sq+10]==BP)?1:0);

                                               if( Totmat < 1500 ) er -= 6*p;

                                /* penalize friendly bishop that stands
                                 * on a square of this color */
                                               if( (sqcolor[sq] & know.bishopcolor)!=0 ) {
                                                   if(    sq==E4 || sq==D4
                                                   || sq==E3 || sq==D3   )
                                                   { er-=7*p; mr-=5*p; }
                                                   else
                                                   { er-=5*p; mr-=4*p; }
                                               }
                                           }
                                       }

                                       /* pawn phalanx or chain, both midgame & endgame */
                                       if( b[sq-1]==WP || b[sq-9]==WP || b[sq-11]==WP ) {
                                           if( sq >= A4 )
                                           { mr += 6; er += 4; }
                                           else
                                           { mr += 2; er += 2; }
                                       }

                                       if( Totmat >= ENDMATERIAL ) {
                                           /*** outpost "spacemaker" pawn in midgame */
                                           if( outpost[sq]!=0 ) {
                                               int o = outpost[sq] + ((sq==D4)?1:0);
                                               if( b[sq-1]==WP ) mr += 2*o;
                                               if( b[sq+1]==WP ) mr += 2*o;
                                               if( b[sq-9]==WP || b[sq-11]==WP ) mr += 3*o;
                                               if( b[sq+9]==BP || b[sq+11]==BP ) mr -= 3*o;
                                               if(b==B) mr += (P[sq]&0x00FF)/0x0020 *  5*o;
                                               else     mr += (P[sq]>>8)    /0x0020 *  5*o;
                                           }

                                           /*** storm */
                                           if( know.qstorm!=0 ) mr += qstormtable[sq];
                                           else if( know.kstorm!=0 ) mr += kstormtable[sq];

                                           /*** `table' bonus */
                                           mr += pmpb[sq];

                                           /*** don't play a4/b4/g4/h4 in opening */
                                           if( sq >= A4 )
                                               if( know.castling == (WSHORT|WLONG) )
                                                   if( kp%10 > FILE_E )
                                                   { if( sq%10 > FILE_F ) mr -= 10; }
                                                   else
                                                   { if( kp%10 < FILE_D && sq%10 < FILE_C )
                                                         mr -= 8; }
                                               else
                                                   if( sq%10 < 3 ) mr -= know.devel;
                                                   else if( sq%10 > 6 ) mr -= 4+know.devel;
                                       }

                                       break;
                                   case WK:
                                       er += kepb[sq];

                                       if( Totmat >= ENDMATERIAL ) {
                                           mr += kmpb[sq];
                                           /* SHELTER */

                                           switch( b[sq-1] )
                                           { case WP: mr += 3; know.kshield++; break;
                                               case WB: mr += 2; know.kshield++;
                                               if( b[sq+9]==WP ) mr += 2; }

                                           switch( b[sq+1] )
                                           { case WP: mr += 3; know.kshield++; break;
                                               case WB: mr += 2; know.kshield++;
                                               if( b[sq+11]==WP ) mr += 2; }

                                           switch( b[sq+10] )
                                           { case WP: mr += 6; know.kshield+=2;
                                             if( b[sq+9]==WP || b[sq+11]==WP )
                                             { mr += 3; know.kshield+=2; }
                                             break;
                                               case WB: mr += 2; know.kshield++;
                                               if( b[sq+9]==WP || b[sq+11]==WP ) {
                                                   know.kshield++;
                                                   if( b[sq+20]==WP )
                                                   { mr += 2; know.kshield++; }
                                               }
                                           }

                                           if( b[sq+20]==WP )
                                           { know.kshield++;
                                             if( b[sq+19]==WP || b[sq+21]==WP )
                                                 know.kshield++;
                                           }

                                           if( b[sq+9]==WP ) { know.kshield++; mr += 4; }

                                           if( b[sq+11]==WP ) { know.kshield++; mr += 4; }

                                           if( xknow.q!=0 || xknow.r >= 2 )
                                           {	int file = sq%10;
                                                if( pf[file] == 0 ) mr -= 6;
                                                if( pf[file-1] == 0 ) mr -= 3;
                                                if( pf[file+1] == 0 ) mr -= 3;

                                                if( file > FILE_C && file < FILE_F ) { /* open center makes us cry */
                                                    if( xpf[file] == 0 )
                                                        if(pf[file]==0) mr -= 8;
                                                        else            mr -= 5;
                                                }
                                           }
                                       }

                                       break;
                                   case WR: {
                                       int r;
                                       int mrr = 0; int err = 0;

                                       for( j = sq+10; b[j]==0 || b[j]>=ROOK; j += 10 ) {};

                                       r=j/10;		/* 2...10 */

                                       if( b[j]==WP && b[j+1]!=0 ) r--;

                                       mrr = err = frb[r];

                                       if( xpf[sq%10] != 0 ) mrr -= 5;

                                       if( pf[sq%10] != 0 ) {
                                           mrr -= 5;
                                           if( b[j]==WP ) {
                        /* avoid pseudocastling, that's moving king
                         * e1-f1-g1, satisfying king safety but blocking
                         * the rook undeveloped */
                                               if( sq==H1 || sq==H2 || sq==G1 )
                                                   if( kp==F1 || kp==G1 )
                                                   { mrr -= 33; err -= 33; }
                                           }
                                       }

                                       {
                                           int b = bon_1[ min_dist(xkp,sq) ];
                                           if(b>0) {
                                               b += r;
                                               if( know.qstorm!=0 || know.kstorm!=0 ) mrr += b;
                                               if( b > 5 )
                                                   if( b > 8 ) xknow.khung += 2;
                                                   else         xknow.khung ++;
                                           }
                                       }

                                       mrr += rmpb[sq];

                                       mr += mrr; er += err;
                                   }
                                   break;
                                   case WB:
                                       if(    b[sq+10]==BP
                                       || (    outpost[sq] != 0
                                       && ( b[sq-9]==WP || b[sq-11]==WP )
                                       )
                                       ) {
                                           int bonus;
                                           //outposting:
                                           {
                                                for( j=sq+9; j<A8; j+=10 )
                                                    if( b[j]==BP || b[j+2]==BP ) 
                                                        goto notout; //break outposting;

                                                   bonus = 0;
                                                   if( b[sq+10]==BP ) bonus += 12*xpf[sq%10];
                                                   if( b[sq+20]==BP ) bonus += 8;
                                                   if( outpost[sq]!=0 ) bonus += 10 + 4*outpost[sq];
                                                   if( b[sq-9]==WP ) bonus += 10;
                                                   if( b[sq-11]==WP ) bonus += 10;

                                                   mr += bonus; er += bonus/2;
                                            }
                                       notout:;//add
                                       }

                                       /*** trapped bishop - it's not worth the pawn ***/
                                       if( sq==A7 ) {
                                           if( b[B6] == BP && see(b,A7,B6) < -200 )
                                           { mr -= 140; er -= 140; }
                                       }
                                       else
                                           if( sq==H7 ) {
                                               if( b[G6] == BP && see(b,H7,G6) < -200 )
                                               { mr -= 140; er -= 140; }
                                           }

                                       if( know.qstorm!=0 || know.kstorm!=0 ) {
                                           mr += bon_2[ diag_dist(xkp, sq) ];
                                       }

                                       mr += bmpb[sq]; er += bepb[sq];
                                       break;
                                   case WN:
                                       if(    b[sq+10]==BP
                                       || (    outpost[sq]!=0
                                       && ( b[sq-9]==WP || b[sq-11]==WP )
                                       )
                                       ) {
                                           int bonus;

                                           outposting:
                                           {
                                               for( j=sq+9; j<A8; j+=10 )
                                                if( b[j]!=BP && b[j+2]!=BP ) 
                                                    goto notoutpost; //break outposting;
                                               
                                               bonus = 0;
                                               if( b[sq+10]==BP ) bonus += 15*xpf[sq%10];
                                               if( outpost[sq]!=0 ) bonus += 8 + 5*outpost[sq];
                                               if( b[sq-9]==WP ) bonus += 10;
                                               if( b[sq-11]==WP ) bonus += 10;

                                               /*** Look at opponent's minor pieces:
                                               *** is it possible to attack the knight
                                               *** with a minor piece? ******************/
                                               if( sq>=A4 && sq%10>=FILE_B && sq%10<=FILE_G
                                                && xknow.n == 0
                                                && ( know.xbishopcolor & sqcolor[sq] ) == 0
                                                && ( b[sq-9]==WP || b[sq-11]==WP )
                                                 )
                                                 { mr+=8+2*outpost[sq]; er+=15+4*outpost[sq]; }

                                                 mr += bonus; er += bonus/2;
                                             }
                                       notoutpost:;//add
                                       }

                                       /*** trapped knight ***/
                                       if( sq==A8 ) {
                                           if( b[A7] == BP && see(b,A8,C7) < -200 )
                                           { mr -= 140; er -= 140; }
                                       }
                                       else if( sq==H8 ) {
                                           if( b[H7] == BP && see(b,H8,F7) < -200 )
                                           { mr -= 140; er -= 140; }
                                       }
                                       else if( sq==A7 ) {
                                           if( b[B7]==BP )
                                               if( b[A6]==BP || b[C6]==BP )
                                               { mr -= 45; er -= 45; }
                                       }
                                       else if( sq==H7 ) {
                                           if( b[G7]==BP )
                                               if( b[H6]==BP || b[F6]==BP )
                                               { mr -= 45; er -= 45; }
                                       }

                                       mr += nmpb[sq];

                                       if( know.qstorm!=0 || know.kstorm!=0 ) {
                                           mr += bon_4[ max_dist(xkp,sq) ];
                                       }

                                       if( Totmat < ENDMATERIAL ) {
                        /* look at the leftmost and righmost pawn file -
                         * large distance between these files is bad
                         * for knight in endgame */
                                           int d =
                                           max(Wknow.rpf,Bknow.rpf)-min(Wknow.lpf,Bknow.lpf);
                                           if(d>3)  /* look at nonpawn material */
                                           { if( Totmat-P_VALUE*(Wknow.p+Bknow.p)
                                             <= N_VALUE+B_VALUE ) er-=5*d;
                                             else                     er-=3*d;
                                           }
                                       }

                                       er += c_bonus[sq];
                                       break;
                                   case WQ:
                                       /* penalize early queen activity, */
                                       /* 10 to 31 pts., depending on development */
                                       if( know.devel >= 8 )
                                           if( sq >= A3 ) mr -= (2+know.devel);

                                       /* let's play aggressively - */
                                       /* penalize for distance from enemy king */
                                       /* active queen is very strong; especially in endgame */
                                       {
                                           int qb;

                                           if( ( B==b ? (P[sq]>>8) : (P[Th[sq]]&0x00FF) )==0 )
                                               qb = bon_5[/* xkdist[sq].taxi*/taxi_dist(xkp, sq)];

                                           else	qb = -8;

                                           if( know.qstorm!=0 || know.kstorm!=0 ) mr += 2*qb;
                                           else mr += qb;
                                           er += 3*qb;
                                       }

                                           mr += qmpb[sq];

                                           break;
                               }
                           }

                           //System.out.println("Got to the end.  M/E-Result is" + Integer.toString (mr) + "/" + Integer.toString (er));

                           if( l == wl ) {
                               midresult += mr; endresult += er;
                               l = bl; n = bn; b = mB;
                               pf = bpf; xpf = wpf;
                               know = Bknow; xknow = Wknow;
                               kp = Th[Bknow.kp]; xkp = Th[Wknow.kp];
                               //System.out.println ("Finished with white");
                           }
                           else {
                               midresult -= mr; endresult -= er;
                               //System.out.println ("Finished with black");
                               break;
                           }
                       }


                       /*********** Development */

                       if( Totmat >= ENDMATERIAL ) {

                           if( Color == WHITE ) { if( Wknow.devel>1 && Wknow.hung<10 ) Wknow.devel-=2; }
                           else                 { if( Bknow.devel>1 && Bknow.hung<10 ) Bknow.devel-=2; }

                           {
                               int d = Bknow.devel-Wknow.devel;
                               d = 4*d + d*max(Wknow.devel,Bknow.devel)/8;

                               midresult += d;

                           }

                       }
                       else  /* outside passed pawn */ {
                           int whas=0, bhas=0;

                           /* white/black left/right -most pawn file (0-10) */
                           int wrm = Wknow.rpf;
                           int wlm = Wknow.lpf;
                           int brm = Bknow.rpf;
                           int blm = Bknow.lpf;

                           /*** look at leftmost pawn ***/
                           if( wlm+1<blm && wrm>wlm+3 ) whas=blm-wlm;
                           else
                               if( blm+1<wlm && brm>blm+3 ) bhas=wlm-blm;

                           /*** look at rightmost pawn ***/
                           if( wrm-1>brm && wrm>wlm+3 ) whas+=wrm-brm;
                           else
                               if( brm-1>wrm && brm>blm+3 ) bhas+=brm-wrm;

                           endresult +=
                           (Oppb[whas]-Oppb[bhas]) * Q_VALUE
                           / (Q_VALUE+Totmat-P_VALUE*(Wknow.p+Bknow.p));
                       }

                       midresult += (Bknow.khung-Wknow.khung) * 2;

                       /*********** King danger */
                       Wknow.khung -= Wknow.kshield/3;
                       Bknow.khung -= Bknow.kshield/3;
                       if( Wknow.khung > 1 ) {
                           midresult -= Wknow.khung * Wknow.khung;
                       }

                       if( Bknow.khung > 1 ) {
                           midresult += Bknow.khung * Bknow.khung;
                       }

                       Wknow.prune = ( Wknow.hung < 10 && Wknow.khung < 2 );
                       Bknow.prune = ( Bknow.hung < 10 && Bknow.khung < 2 );

                       /**
                        ***   Trade down bonus
                        **/
                       //System.out.println ("Got before trade-down. M/E-Result is" + Integer.toString (midresult) + "/" + Integer.toString (endresult));
                       {
                           int tbonus = ( hist[hdp-1].mtrl - hist[hdp-1].xmtrl );
                           if( tbonus != 0 ) {
                               int r;

                               if( Color == BLACK ) tbonus = -tbonus;

                               if( tbonus > 0 ) /* white stronger */ {
                                   if( Wknow.p!=0 || tbonus>=(N_VALUE+P_VALUE) )
                                       r = (   tbonus * Wknow.p
                                       - tbonus * (2*Bknow.q+Bknow.b+Bknow.r+Bknow.n)
                                       ) / 30;
                                   else /* white has no pawns! */
                                       r = - tbonus / 2;
                               }
                               else             /* black stronger */ {
                                   if( Bknow.p!=0 || tbonus <=(N_VALUE+P_VALUE) )
                                       r = (   tbonus * Bknow.p
                                       - tbonus * (2*Wknow.q+Wknow.b+Wknow.r+Wknow.n)
                                       ) / 30;
                                   else
                                       r = - tbonus / 2;
                               }

                               endresult += r;
                               midresult += r/2;

                           }

                       }

                       if( Totmat < ENDMATERIAL ) result += endresult;
                       else if( Totmat > MIDMATERIAL ) result += midresult;
                       else result += (Totmat-ENDMATERIAL) * midresult / (MIDMATERIAL-ENDMATERIAL)
                       + (MIDMATERIAL-Totmat) * endresult / (MIDMATERIAL-ENDMATERIAL);

                       /*** different colored bishops in endgame lead to draw ***/
                       if( Totmat <  ENDMATERIAL )
                           if(   Wknow.bishopcolor!=0
                           && Wknow.xbishopcolor!=0
                           && Wknow.bishopcolor+Wknow.xbishopcolor == 3
                           && Wknow.n==0 && Wknow.r==0 && Wknow.q==0
                           && Bknow.n==0 && Bknow.r==0 && Bknow.q==0 ) {
                               int difference = ( hist[hdp-1].mtrl - hist[hdp-1].xmtrl ) / 4;
                               result/=2;
                               if( difference > 0 )
                               { if(Color==WHITE) result -= 50+difference;
                                 else result += 50+difference; }
                               else
                                   if( difference < 0 )
                                   { if(Color==WHITE) result += 50-difference;
                                     else result -= 50-difference; }
                           }



                       if( Color == WHITE ) return result+TEMPO;
                       else return -result-TEMPO;

                   }

                    byte taxi_dist( int a, int b )
                   { return (byte)(abs( a%10 - b%10 ) + abs( a/10 - b/10 )); }

                    byte diag_dist( int a, int b ) {
                       int fdi = abs( a%10 - b%10 );
                       int rdi = abs( a/10 - b/10 );
                       return (byte)(abs(rdi-fdi) + max(rdi,fdi));
                   }

                    byte max_dist( int a, int b ) {
                       int fdi = abs( a%10 - b%10 );
                       int rdi = abs( a/10 - b/10 );
                       return (byte)max(rdi,fdi);
                   }

                    byte min_dist( int a, int b ) {
                       int fdi = abs( a%10 - b%10 );
                       int rdi = abs( a/10 - b/10 );
                       return (byte)min(rdi,fdi);
                   }

               /*E N D I N G S*/

                    int onepawn( int wk, int wp, int bk, int wtm ) 
                    {
                        //System.out.println ("Really evaluating onepawn");

                       int wpfile = wp%10;
                       int target = wpfile + 90;
                       int steps = target/10 - wp/10 + (( wk>wp && (wk-wp)%10==0 )?1:0) - (( wp <= H2 )?1:0);
                       boolean rookpawn;

                       /**
                        ***  If black king is out of the square, it's won.
                        **/
                       if( (int)(max_dist(target, bk)) > steps-wtm+1 ) return R_VALUE-steps;

                       /**
                        ***  Now, a draw rule: if black king is much closer to the pawn than
                        ***  the white king, it must be a draw.  We already know it is in the
                        ***  square.  Sometimes pawn can stop enemy's diagonal run, so let's
                        ***  add a step.  With rook pawn it's even easier for the defending side
                        ***  - let's add a step too.
                        **/
                       if(    max_dist(wp, bk) + wtm + 1 + (( (bk-wp)%9==0 || (bk-wp)%11==0 )?1:0)
                       <=   max_dist(wp,wk)
                       + (( rookpawn = ( wpfile==FILE_A || wpfile==FILE_H ) )==true?1:0)        )
                           return (1-P_VALUE);

                       /**
                        ***  Rook-pawn.
                        **/
                       if(rookpawn) {
                           if( max_dist(target, bk)+wtm-1 > max_dist(target, wk) && abs(wpfile-wk%10)==1 )
                               return R_VALUE-P_VALUE-2*steps;
                           return (1-P_VALUE);
                       }

                       /**
                        ***  Look at the critical squares, according to the endgames textbook
                        ***  by IGM Ludek Pachman.
                        **/
                       if( wk-wp==19 || wk-wp==20 || wk-wp==21 ) return R_VALUE-4*steps;
                       if( wk-wp==9 || wk-wp==10 || wk-wp==11 ) if( wp>A5 || ( wtm != ((bk-wk==20)?1:0) ) )
                           return R_VALUE-8*steps;

                       /**
                        ***  Some simple drawish knowledge - white cannot access critical square.
                        **/
                       if( wp<A7 && bk-wp==10 ) return (1-P_VALUE);
                       if( wp<A6 ) {
                           if( bk-wp==20 ) return (1-P_VALUE);
                           if( ( bk-wp==19 || bk-wp==21 ) && bk-wk==20 ) return (1-P_VALUE);
                       }

                       /**
                        ***  We still dont know :-(
                        ***  Lets try to return something reasonable.
                        **/
                       {
                           int d;
                           int d1 = ( wp + ( wp<A5 ? 19 : 9 ) );
                           int d2 = ( wp + ( wp<A5 ? 21 : 11 ) );
                           if( max_dist(wk, d1) < max_dist(wk, d2) )
                               d = wtm + max_dist(bk, d1) - max_dist(wk, d1);
                           else
                               if( max_dist(wk, d1) > max_dist(wk, d2) )
                                   d = wtm + max_dist(bk, d2) - max_dist(wk, d2);
                               else
                                   if( max_dist(bk, d1) < max_dist(bk, d2) )
                                       d = wtm + max_dist(bk, d2) - max_dist(wk, d2);
                                   else	d = wtm + max_dist(bk, d1)- max_dist(wk, d1);

                           if(d>0) return R_VALUE-P_VALUE-4*(steps-d);
                           else
                               if(d<0) return (1-P_VALUE)+20+2*d;

                           return 32* (taxi_dist(wp+10,bk) - taxi_dist(wp+20, wk));
                       }

                   }

                    int pawns() {
                       int result;
                       int color;
                       int wbest=32, bbest=32;


                       if( Totmat == P_VALUE )  /* KPK routine */ {
                           int wk, wp, bk, wtm;

                           if( Color==WHITE ) wtm=1; else wtm=0;

                           if( L[(L[WHITE].dest)].dest != 0 )
                           {	wk = (L[WHITE].dest); wp = L[(L[WHITE].dest)].dest; bk = (L[BLACK].dest);
                                result = onepawn(wk,wp,bk,wtm);
                           }
                           else
                           {	wk = Th[(L[BLACK].dest)]; wp = Th[L[(L[BLACK].dest)].dest]; bk = Th[(L[WHITE].dest)];
                                wtm = 1-wtm;
                                result = -onepawn(wk,wp,bk,wtm);
                           }

                           if(Color==WHITE) return result; else return -result;
                       }

                       result = kbonus[(L[WHITE].dest)]-kbonus[Th[(L[BLACK].dest)]];

                       for( color=1; color!=3; color++ ) {
                           int step = ( color==WHITE ? 10 : -10 );
                           int best = 32;
                           int pawn = PAWN+color;
                           int xpawn = PAWN+3-color;
                           int kp = L[color].dest;
                           int xkp = L[3-color].dest;
                           int  *pf = ( color==WHITE ? wpf : bpf );
                           int s;  /* square */
                           int i;

                           for( i=1; i!=9; i++ ) pf[i]=0;

                           for( s = L[kp].dest; s != 0; s = L[s].dest ) {
                               int b, togo;
                               int blocks = 0;
                               boolean cannotmove;
                               boolean protectd;
                               int stepstosquare;

                               pf[s%10]++;

                               /* doubled pawn */
                               if( pf[s%10] > 1 ) result -= ( color==WHITE ? (8) : -(8) );

                               if( B[s+step] !=0 ) cannotmove = true;
                               else {
                                   int f=0;
                                   if( B[s+step+step+1] == xpawn ) f++;
                                   if( B[s+step+step-1] == xpawn ) f++;
                                   if(f!=0) {
                                       if( B[s+1] == pawn ) f--;
                                       if( B[s-1] == pawn ) f--;
                                       cannotmove = (f>0);
                                   } else cannotmove=false;
                               }

                               if(cannotmove) result -= ( color==WHITE ? (6) : -(6) );
                               protectd = ( B[s-step-1]==pawn || B[s-step+1]==pawn );

                               passed: {
                                   /* lets make kings active */
                                   if( ! protectd ) {
                                       int di = max_dist(xkp,s);
                                       if(cannotmove) b = ( color==WHITE ? (32-4*di) : -(32-4*di) );
                                       else b = ( color==WHITE ? (16-2*di) : -(16-2*di) );
                                       if(di==1)
                                       { if(cannotmove) b+=30; else b+=20; }

                                       result -= b;
                                   }

                                   if( B[s+step] == xpawn ) goto notpassed; //break passed;
                                   for( i=s+step+step; B[i]!=3; i+=step ) {
                                       if( B[i] !=0 ) blocks++;
                                       if( B[i]==xpawn || B[i-1]==xpawn || B[i+1]==xpawn )
                                           goto notpassed;//break passed;
                                   }

                                   /*** BEGIN: passed pawn evaluation ***/

                                   i -= step;                  /* the queening square */
                                   togo = blocks+abs(s-i)/10;  /* steps to queen */
                                   b = ( color==WHITE ? (passed[togo]) : -(passed[togo]) );
                                   result += b;

                                   /* protectd passer -> more bonus */
                                   if( protectd ) result += b+b;

                                   /* out of enemy's king square */
                                   stepstosquare=(int)(max_dist(xkp,i))-togo+((Color==color)?1:0);

                                   if( stepstosquare>1 ) {
                                       result += b+b;
                                       if( togo < best ) best = togo;
                                   }

                                   /* distance from enemy king */
                                   b = max_dist(xkp,s+step) * (12-togo);
                                   result += ( color==WHITE ? (b) : -(b) );

                                   /*** END: passed pawn evaluation ***/

                               }
                           notpassed: //added!!!
                               /*** some points for advancement ***/
                               result += (s/10-4-color)*2;
                           }
                           if( color == WHITE ) wbest=best; else bbest=best;
                       }

                       if( wbest!=32 )
                           if( bbest!=32 )
                           { if(      wbest-bbest > 2 ) result += -300 + (bbest-wbest)*60;
                             else if( bbest-wbest > 2 ) result +=  300 + (bbest-wbest)*60;
                             else                       result += (bbest-wbest)*40;
                           }
                           else
                               result += (30-wbest)*20;
                       else
                           if( bbest!=32 )
                               result -= (30-bbest)*20;

                       /* a simple detection of outside passed pawn */
                       if( hist[hdp-1].mtrl !=0 && hist[hdp-1].xmtrl!=0 )    /* both sides must have pawns */ {
                           int whas=0, bhas=0;

                           /* white/black left/right -most pawn file (0-10) */
                           int wrm = Wknow.rpf;
                           int wlm = Wknow.lpf;
                           int brm = Bknow.rpf;
                           int blm = Bknow.lpf;

                           /*** look at leftmost pawn ***/
                           if( wlm+1<blm && wrm>wlm+3 ) whas=blm-wlm;
                           else
                               if( blm+1<wlm && brm>blm+3 ) bhas=wlm-blm;

                           /*** look at rightmost pawn ***/
                           if( wrm-1>brm && wrm>wlm+3 ) whas+=wrm-brm;
                           else
                               if( brm-1>wrm && brm>blm+3 ) bhas+=brm-wrm;

                           result += Oppb[whas]-Oppb[bhas];
                       }

                       if( Color == BLACK ) result = -result;

                       /* consistency with trade down bonus: 5 points per pawn */
                       if( hist[hdp-1].mtrl > hist[hdp-1].xmtrl ) result += hist[hdp-1].mtrl/20;
                       else
                           if( hist[hdp-1].mtrl < hist[hdp-1].xmtrl ) result -= hist[hdp-1].xmtrl/20;

                       return result;

                   }

                   int e_mp()  /*** minor piece and pawn ***/ {

                       if( hist[hdp-1].mtrl!=0 && hist[hdp-1].xmtrl !=0 ) {	/*** minor piece against pawn ***/
                           int p;
                           if( hist[hdp-1].mtrl == P_VALUE ) {
                               if( Color == WHITE ) p = L[(L[WHITE].dest)].dest/10;
                               else p = 11 - L[(L[BLACK].dest)].dest/10;
                           }
                           else {
                               if( Color == WHITE ) p = - ( 11 - L[(L[BLACK].dest)].dest/10 );
                               else p = - L[(L[WHITE].dest)].dest/10;
                           }
                           return hist[hdp-1].xmtrl - hist[hdp-1].mtrl + 3*p;
                       }
                       else {	/*** check for bad bishop ***/
                           int ss;  /* stronger side */
                           int wb, wp, wk, bk;

                           if( L[(L[WHITE].dest)].dest !=0) {
                               wk=(L[WHITE].dest);
                               if( B[L[wk].dest]==WP ) { wp=L[wk].dest; wb=L[wp].dest; }
                               else                    { wb=L[wk].dest; wp=L[wb].dest; }
                               if( B[wb] == WN )
                                   if(   ( B[A7]==WP && ( B[A8]==BK || B[B7]==BK ) )
                                   ||( B[H7]==WP && ( B[H8]==BK || B[G7]==BK ) )
                                   )    return   hist[hdp-1].xmtrl - hist[hdp-1].mtrl;
                                   else return   0;
                               bk=(L[BLACK].dest); ss=WHITE;
                           }
                           else {
                               wk=(L[BLACK].dest);
                               if( B[L[wk].dest]==BP ) { wp=L[wk].dest; wb=L[wp].dest; }
                               else                    { wb=L[wk].dest; wp=L[wb].dest; }
                               bk=(L[WHITE].dest); ss=BLACK;
                               if( B[wb] == BN )
                                   if(   ( B[A2]==BP && ( B[A1]==WK || B[B2]==WK ) )
                                   ||( B[H2]==BP && ( B[H1]==WK || B[G2]==WK ) )
                                   )    return   hist[hdp-1].xmtrl - hist[hdp-1].mtrl;
                                   else return   0;
                               wk=Th[wk]; wp=Th[wp]; wb=Th[wb]; bk=Th[bk];
                           }

                           switch( wp%10 )
                           { case FILE_A: break;
                               case FILE_H: wp=Tv[wp]; wk=Tv[wk]; wb=Tv[wb]; bk=Tv[bk]; break;
                               default: return 0; /* this is not a rook pawn */
                           }

                           if( sqcolor[wb] == 1 ) return 0;  /* the bishop is ok */

                           /* Draw!! */
                           if( bk > wp )
                               if( bk%10<FILE_C && bk>=A7 ) {
                                   return   hist[hdp-1].xmtrl - hist[hdp-1].mtrl;
                               }
                       }

                       return 0;

                   }



                    int e_nb( int color )  /*** mating with knight and bishop ***/ {
                       int kdist = 8 * max_dist((L[WHITE].dest),(L[BLACK].dest));
                       int kp=A1;
                       int i, npd=0;

                       if( color == WHITE ) {
                           for( i=L[(L[WHITE].dest)].dest; i!=0; i=L[i].dest )
                               if( B[i] == WN ) npd=2*taxi_dist(i,(L[BLACK].dest));
                               else if( B[i] == WB )
                                   if( sqcolor[i] == 1 ) kp = Th[(L[BLACK].dest)]; else kp = (L[BLACK].dest);
                       }
                       else {
                           for( i=L[(L[BLACK].dest)].dest; i!=0; i=L[i].dest )
                               if( B[i] == BN ) npd=2*taxi_dist(i,(L[WHITE].dest));
                               else if( B[i] == BB )
                                   if( sqcolor[i] == 1 ) kp = Th[(L[WHITE].dest)]; else kp = (L[WHITE].dest);
                       }

                       if( color == Color ) return -kdist-npd+nb[kp];
                       else return  kdist+npd-nb[kp];
                   }



                    int e_rpr() 
                   {
                       int wk, wr, wp, bk, br;
                       int result = 0;
                       int sstm;    /* it's stronger's side move */

                       if( hist[hdp-1].mtrl > hist[hdp-1].xmtrl )
                       { sstm=1; wk=L[Color].dest; bk=L[3-Color].dest; br=L[bk].dest; }
                       else
                       { sstm=0; wk=L[3-Color].dest; bk=L[Color].dest; br=L[bk].dest; }

                       if( ((B[L[wk].dest])&0xFC) == ROOK )
                       { wr=L[wk].dest; wp=L[wr].dest; }
                       else
                       { wp=L[wk].dest; wr=L[wp].dest; }

                       if( B[bk] == WK )
                       { wk=Th[wk]; wr=Th[wr]; wp=Th[wp]; bk=Th[bk]; br=Th[br]; }

                       if( wp%10 > FILE_D )
                       { wk=Tv[wk]; wr=Tv[wr]; wp=Tv[wp]; bk=Tv[bk]; br=Tv[br]; }

                       result = wp/10-5;
                       if( wp%10 == FILE_A ) result -= 15;

                       result -= 2*max_dist(br,wp) + 3*abs(br%10-wp%10);

                       if( bk > wp )
                           switch( wp%10-bk%10 )
                           { case -2: break;
                               case -1: result -= 20; break;
                               case  0: result -= 50; break;
                               case  1: result -= 40; break;
                               case  2: if( br%10-wp%10 > 3 ) result -= 35;
                               else result -= abs(br%10-wp%10)*3;
                               break;
                               default: result += 10*abs(wp%10-bk%10);
                           }
                       else result += 5*(wp/10-bk/10);

                       if( wk < wp ) result -= 5*(wp/10-wk/10);

                       if( br<wp && (br-wp)%10 == 0 ) { result -= 20; }

                       if(sstm!=0) return result; else return -result;
                   }
                   
                   
                   
                   int e_q ()
                   {
                       int wk, bk, q;
                       int result=0;
                       boolean sstm;
                       
                       if (hist[hdp-1].mtrl > hist[hdp-1].xmtrl) 
                       {
                        sstm=true;
                        wk = L[Color].dest;
                        bk = L[3-Color].dest;
                        q = find_queen(Color);
                       }
                       else
                       {
                        sstm=false;
                        wk = L[3-Color].dest;
                        bk = L[Color].dest;
                        q = find_queen(3-Color);;
                       }
                       /*Считаем, как будто белый король ставит с ладьёй мат чёрному королю. 
                        result максимизируем для мата.*/
                       /*
                       resulting:
                       {
                           result=0;
                           if (max_dist(bk, H8) > 1)
                           {
                        */
                               result = -max_dist (bk, H8)*10 + 10;
                               //result -= 2*max_dist (q,wk);
                        /*
                               result -= 3*max_dist(wk,bk);
                               break resulting;
                           }
                         */  
                       //}                           
                       
                       if (sstm) 
                           return result;
                       else 
                           return -result;
                       
                   }
                   
                   int find_queen (int c)
                   {
                       int result=0;
                       for (int i = L[c].dest; i != 0; i = L[i].dest)
                       {
                           if ((B[i] & 0xFC) == QUEEN)
                           {
                                result=i;
                                break;
                           }
                       }
                       return result;
                   }

//}
