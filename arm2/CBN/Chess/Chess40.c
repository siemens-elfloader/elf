
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
//                PlayerLocal[1]=true;
//                PlayerLocal[2]=false;
                GlobalAI.num_humans=1;
                break;
            case 1:
//                PlayerLocal[1]=false;
//                PlayerLocal[2]=true;
                GlobalAI.num_humans=1;
                break;
            case 2:
//                PlayerLocal[1]=true;
//                PlayerLocal[2]=true;
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
    

    boolean CanMove(int from, int to/*, boolean any*/) 
    {
        for (int i=0; i < root_moves_num; i++) {
            if ((M_draw[i]>>16) == from && (/*any || */(M_draw[i]&0xFFFF)==to))
                return true;
        }
        return false;
    }
    
    
    int GetMoveType (int from, int to)
    {
        int type=MOVE_TYPE_NORMAL;
        
        if ((B[from] & 0xFC) == KING && from%10==5 && (to%10==3 || to%10==7))
            type=MOVE_TYPE_CASTLE;
        if ((B[from] & 0xFC) == PAWN && (to/10==2 || to/10==9)) {
            if (PlayerLocal[Color]) {
                type = (new UniversalMenu().GetPromotionType());
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
        last_taken = B[to];
        InvalidateTime();
        MOVE m = new MOVE();
        m.from=(byte)from; m.dest=(byte)to; m.type=(byte)type;
        MakeMove (m);
        BeReady();
        
        redraw[from]=true;
        redraw[to]=true;
        redraw[last_move]=true;
        redraw[last_from]=true;
        redraw[TAKEN]=true;
        if (type != MOVE_TYPE_NORMAL)
          needClear=true;
        last_move=to;
        last_from=from;
        last_move_remover_counter=0;
        str_last_move=Notation(from,to, last_taken, type);
        
        if (Color==BLACK) nummove++;
        
        historyViewer.AppendEncoded(m, (B[to]&0x3)==WHITE, (last_taken!=0), check, root_moves_num==0,  type >= MOVE_TYPE_PROMOTION_TO_QUEEN && type <= MOVE_TYPE_PROMOTION_TO_KNIGHT, type == MOVE_TYPE_CASTLE, nummove);
        reallyFirst=false;
    
 //       if (OpeningBook.enabled)
 //           OpeningBook.AdvanceMove(m);
    }
    
 void InvalidateTime()
    {
        long curTimer = System.currentTimeMillis();

        if (Color==WHITE) 
        {
            if (BackTiming)
            {
                WhiteTime += GlobalAI.Increment;
                WhiteTime -= (curTimer-TimerStart)/100;
            }
            else
                WhiteTime += (curTimer-TimerStart)/100;                
        }
        else 
        {
            if (BackTiming)
            {
                BlackTime += GlobalAI.Increment;
                BlackTime -= (curTimer-TimerStart)/100;
            }
            else
                BlackTime += (curTimer-TimerStart)/100;
     
        }
    }    
    
    void UndoMove()
    {
        if (hdp<3)
            return;
        
        InvalidateTime();
        
        if (GlobalAI.PlayerLocal[GlobalAI.BLACK+GlobalAI.WHITE-GlobalAI.Color])
        {
            GlobalAI.TakeBack();
            historyViewer.Append ("[Half-Move undone]",0x007800);
        }
        else
        {
            GlobalAI.TakeBack();
            GlobalAI.TakeBack();
            historyViewer.Append ("[Move undone]",0x007800);
        }
        GlobalAI.str_last_move="";
        GlobalAI.last_move=0;
        GlobalAI.last_from=0;
        GlobalAI.last_taken=0;
        GlobalAI.BeReady();
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
        B_draw[wh]=0;        
        L[L[wh].from].dest=L[wh].dest;
        L[L[wh].dest].from=L[wh].from;
        
        hist[hdp-1].castling |= cb[wh]; 

        redraw[wh]=true;
    }
    void RestorePiece (int wh)
    {
        if (B[wh]!=0) return;
        if (ref_B[wh]==0) return;
        
        B[wh]=ref_B[wh];
        B_draw[wh]=ref_B[wh];
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
        
        redraw[wh]=true;
        
    }
   
    void LoadIdentity (boolean reseed)
    {
        for (int i=0; i < 120; i++) B[i]=ref_B[i];
        Color=WHITE;
        init();
        historyViewer.Append ("[Game Started]", 0x007800);
        build();
        BeReady();
        reallyFirst=true;
        if (reseed) seed = System.currentTimeMillis() % 256;
        m_rnd =  new java.util.Random(seed);
        historyViewer.Append ("[Seed:" + seed + "]", 0x007800);        
        
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