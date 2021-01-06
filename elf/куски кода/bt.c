unsigned int TotalTime = 0,
             TotalTimeTick = 0;
unsigned int RercentOfFile, TimeOfEnd, MinusTime;



#define YES_SCROLL 1
#define NO_SCROLL  0

void Draw_String(const char *text, int x, int y, int type)
{
  if(TYPE_FONT)
  {
    if(type)
    {
      PrintText(x, y, (char*)text, 0, 1, SPACE, 0, 1, 0, ScrW );
    }
    else
    {
      PrintField(x, y, (char*)text, 0, 1, SPACE);
    }
  }
  else
  {
    WSHDR *ws_text = AllocWS(256);
    wsprintf(ws_text, perc_t, text);
    
    if(type)
    {
      int string_w = Get_WS_width(ws_text, SFONT_NUM);
      if (string_w < ScrW)
      {
        DrawString(ws_text, x, y, ScrW, ScrH, SFONT_NUM, 32, FONT_COLOUR, FONT_FRING_COLOUR);
      }
      else
      {
        static byte dir = 0;
        int dif = string_w - ScrW;
        static short sm=0;
        int step = 4+(3*string_w)/ScrW; 
        sm += step*(dir?-1:1);
        DrawScrollString(ws_text, x, y, ScrW, ScrH,sm+1, SFONT_NUM, 32, FONT_COLOUR, FONT_FRING_COLOUR);
        if ((sm-step)<0) dir = 0;
		else
		  if ((sm)>dif)dir = 1;
      }
    }
    else
    {
      DrawString(ws_text, x, y, ScrW, ScrH, SFONT_NUM, 32, FONT_COLOUR, FONT_FRING_COLOUR);
    }
    FreeWS(ws_text);
  }
}


 RamFileSize = *RamSizeOfRecievedSendFile();
    unsigned int RamFilePart = *RamSizeOfPart();
    RercentOfFile = ( RamFilePart * 100 ) / RamFileSize;


// Проценты---------------------------------------------------------------------
    
    if(ENA_PERCENTS_TEXT)
    {
      Draw_Img(ENA_PERCENTS_IMG, position[PERCENT_IX] , position[PERCENT_IY], COMPLETE_IMG);
      
      int PERCENTS;
      char TEXT_PERCENT[256]="";
      if(MODE) PERCENTS = 100; else PERCENTS = RercentOfFile;
      sprintf(TEXT_PERCENT, "%d %s", PERCENTS,"%");
      
      Draw_String(TEXT_PERCENT, position[PERCENT_TX], position[PERCENT_TY], NO_SCROLL);
    }
              
// Скорость-------------------------------------------------------------------
                
    if(ENA_SPEED_TEXT)
    {
      Draw_Img(ENA_SPEED_IMG, position[SPEED_IX] , position[SPEED_IY], SPEED_IMG);
      
      char TEXT_SPEED[256]="";
      if(SPEED_TYPE) sprintf(TEXT_SPEED, "%d%s",((RamFilePart)/1024)/TotalTime," kb/s");
      else sprintf(TEXT_SPEED, "%d%s",RamFilePart/TotalTime," b/s");
      
      Draw_String(TEXT_SPEED, position[SPEED_TX], position[SPEED_TY], NO_SCROLL);
    }


void StartTimeTimer()
{
  if (++TotalTimeTick>4)
  {
    TotalTimeTick = 0;
    TotalTime++;
  }
  GBS_StartTimerProc(&OnTimeTimer,216/4,StartTimeTimer);
}