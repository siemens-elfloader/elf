WSHDR *e_ws;
char *filename;



//================================================================================================================
char *temp_chars; //Собственно файл
char **temp_lines; //Массив указателей на строки

char days[7];
char *day[7]={"Пн","Вт","Ср","Чт","Пт","Сб","Вс"};
TTime alarm_time;
int snooze_time;
int alarm_active;
int auto_snooze;
int   alarm_hour=0;
int   alarm_min=0;

void FreePD(void)
{
  if (temp_lines) mfree(temp_lines);
  if (temp_chars) mfree(temp_chars);
  temp_lines=NULL;
  temp_chars=NULL;
}

int LoadPD()
{
  FSTATS stat;
  char fn[256];
  int f;
  unsigned int ul;
  int i;
  int fsize;
  char *p;
  char *pp;
  int c;
  FreePD();
  strcpy(fn,"1:\\system\\alarmclock.pd");
//  strcpy(fn,"0:\\alarmclock.pd");
  if (GetFileStats(fn,&stat,&ul)==-1) return 0;
  if ((fsize=stat.size)<=0) return 0;
  if((f=fopen(fn,A_ReadOnly+A_BIN,P_READ,&ul))==-1) return 0;
  p=temp_chars=malloc(fsize+1);
  p[fread(f,p,fsize,&ul)]=0;
  fclose(f,&ul);
  i=0;
  pp=p;
  for(;;)
  {
    c=*p;
    if (c<32)
    {
      if (pp&&(pp!=p))
      {
	temp_lines=realloc(temp_lines,(i+1)*sizeof(char *));
	temp_lines[i++]=pp;
      }
      pp=NULL;
      if (!c) break;
      *p=0;
    }
    else
    {
      if (pp==NULL) pp=p;
    }
    p++;
  }
  return i;
}

void ParseSnoozeTime(char *s)
{
//  do_logwrite(s);
  int time=strtoul(s,0,10);
  snooze_time=time/60;
}
void GetTime(TTime *t,int time)
{
  time=time/60;
  int hour=time/60;
  int min=time%60;
  t->hour=hour;
  t->min=min;
  alarm_hour=hour;
  alarm_min=min;
}

void ParseAlarmTime(char *s)
{
//    do_logwrite(s);
  int time=strtoul(s,0,10);//28500
  GetTime(&alarm_time,time);
}

void ParseDayInUse(char *s)
{
  //do_logwrite(s);
  //char *p=strrchr(s,'=')+1;
  char *p=malloc(1);
  for(int i=0;i<7;i++)
  {
    *p=*(s+i);
    days[i]=strtoul(p,0,10);
  }
  mfree(p);
}

void ParseAlarmActive(char *s)
{
//  do_logwrite(s);
  alarm_active=strtoul(s,0,10);
}

void ParseAutoSnooze(char *s)
{
//  do_logwrite(s);
  auto_snooze=strtoul(s,0,10);
}
void Parser()
{
  int i=LoadPD();
  if(!i) { ShowMSG(1,(int)"Don't load file!"); return; }
  int j=0;
  char *s;
  while(j<i)
  {
    s=strrchr(temp_lines[j],'=')+1;
//    ShowMSG(1,(int)s);
    if(strstr(temp_lines[j],"snooze_time"))  ParseSnoozeTime(s);
    if(strstr(temp_lines[j],"days_in_use"))  ParseDayInUse(s);
    if(strstr(temp_lines[j],"alarm_time"))   ParseAlarmTime(s);
    if(strstr(temp_lines[j],"alarm_active")) ParseAlarmActive(s);
    if(strstr(temp_lines[j],"auto_snooze"))  ParseAutoSnooze(s);
    j++;
  }
}

//================================================================================================================





void drawmod(int mod)
{
   int pyf = GetMissedCallsCount();
   WSHDR * ws = AllocWS( 256 );
   char *zs = malloc (6);
   char *ds = malloc (20);
   TDate date;
   TTime time;
   int xu = 30;
   int yu = 76;
   int xuu = 240-29-82+1;
   char *pyfstr = malloc(40);
   int yid = main_mod*70;

   switch(mod)
     {
      //------------------------------------------
        case 0:
          GetDateTime(&date,&time);
          sprintf(zs, "%02i:%02i",time.hour,time.min);
          sprintf(ds, "%02i.%02i.%02i",date.day,date.month,date.year);
          ds[6]=ds[8];ds[7]=ds[9];ds[8]=0;
          if (main_mod==0){//рисуем подложки для часов
              DrwPngImg(FImage4, 29, 63);
              DrwPngImg(FImage4, 240-29-82, 63);
          }
          //========== рисуем дату и провайдера ==============
          ascii2ws(ws, ds); DrawString( ws, 11,  33,  229, 320, 8, 1, co21, GetPaletteAdrByColorIndex( 23 ) );
          GetProvider(ws, 0);
          DrawString( ws, 11,  33,  229, 320, 8, 4, co21, GetPaletteAdrByColorIndex( 23 ) );
    
          if (IsUnlocked())
          {
            if (zxmainzerro) DrwPngImg(SetIco[10], 29, 155+28*zxmain-yid); // - рисуем курсор для "Вызовы","Календарь"
    
            DrwPngImg(FImage9, 32, 189-yid);
            DrawLine(28,182-yid,212,182-yid,1,co22x);
            DrawLine(28,210-yid,212,210-yid,1,co22x);
            DrawLine(28,238-yid,212,238-yid,1,co22x);
    
          if (!pyf) {
            ascii2ws(ws, "Вызовы");
            DrawString( ws, 58,  183-yid,  230, 320-yid, 6, 1, co21, GetPaletteAdrByColorIndex( 23 ) );
            }
          else {
            sprintf (pyfstr, "Вызовы (%i)", pyf);
            ascii2ws(ws, pyfstr);
            DrawString( ws, 58,  183-yid,  230, 320-yid, 6, 1, co21, GetPaletteAdrByColorIndex( 23 ) );
            }
          
          if (GetAlarmclockState(1)) 
          {
            sprintf (pyfstr, "%02i:%02i", alarm_hour, alarm_min);
            ascii2ws(ws, pyfstr);
            DrwPngImg(FImage9a, 33, 166-yid);
            DrawString( ws, 50,  163-yid,  230, 320-yid, 8, 1, co22v, GetPaletteAdrByColorIndex( 23 ) );
          }
          else
          {
            ascii2ws(ws, "Сигнал выключен");
            DrwPngImg(FImage9b, 33, 166-yid);
            DrawString( ws, 50,  163-yid,  230, 320-yid, 8, 1, co22x, GetPaletteAdrByColorIndex( 23 ) );
          }
    
    
          ascii2ws(ws, "Календарь");  DrawString( ws, 58,  211-yid,  230, 320-yid, 6, 1, co21, GetPaletteAdrByColorIndex( 23 ) );
        }
        else 
        {
          DrawLine(28,183-yid,211,183-yid,1,co22x);
          DrawLine(28,237-yid,211,237-yid,1,co22x);
          DrawLine(28,183-yid,28,237-yid,1,co22x);
          DrawLine(211,183-yid,211,237-yid,1,co22x);
            
          ascii2ws(ws, "Для разблокировки");  DrawString( ws, 38,  185-yid,  230, 320-yid, 6, 1, co21, GetPaletteAdrByColorIndex( 23 ) );
          ascii2ws(ws, "нажмите #");  DrawString( ws, 38,  208-yid,  230, 320-yid, 6, 1, co21, GetPaletteAdrByColorIndex( 23 ) );
        }
            
        if (main_mod==0)//бааальшие часы
        {         
           if (zs[0] == '0') DrwPngImg(Clock[0], xu, yu);
           if (zs[0] == '1') DrwPngImg(Clock[1], xu, yu);
           if (zs[0] == '2') DrwPngImg(Clock[2], xu, yu);
           if (zs[0] == '3') DrwPngImg(Clock[3], xu, yu);
           if (zs[0] == '4') DrwPngImg(Clock[4], xu, yu);
           if (zs[0] == '5') DrwPngImg(Clock[5], xu, yu);
           if (zs[0] == '6') DrwPngImg(Clock[6], xu, yu);
           if (zs[0] == '7') DrwPngImg(Clock[7], xu, yu);
           if (zs[0] == '8') DrwPngImg(Clock[8], xu, yu);
           if (zs[0] == '9') DrwPngImg(Clock[9], xu, yu);
           if (zs[1] == '0') DrwPngImg(Clock[0], xu+40, yu);
           if (zs[1] == '1') DrwPngImg(Clock[1], xu+40, yu);
           if (zs[1] == '2') DrwPngImg(Clock[2], xu+40, yu);
           if (zs[1] == '3') DrwPngImg(Clock[3], xu+40, yu);
           if (zs[1] == '4') DrwPngImg(Clock[4], xu+40, yu);
           if (zs[1] == '5') DrwPngImg(Clock[5], xu+40, yu);
           if (zs[1] == '6') DrwPngImg(Clock[6], xu+40, yu);
           if (zs[1] == '7') DrwPngImg(Clock[7], xu+40, yu);
           if (zs[1] == '8') DrwPngImg(Clock[8], xu+40, yu);
           if (zs[1] == '9') DrwPngImg(Clock[9], xu+40, yu);
            
           if (zs[3] == '0') DrwPngImg(Clock[0], xuu, yu);
           if (zs[3] == '1') DrwPngImg(Clock[1], xuu, yu);
           if (zs[3] == '2') DrwPngImg(Clock[2], xuu, yu);
           if (zs[3] == '3') DrwPngImg(Clock[3], xuu, yu);
           if (zs[3] == '4') DrwPngImg(Clock[4], xuu, yu);
           if (zs[3] == '5') DrwPngImg(Clock[5], xuu, yu);
           if (zs[3] == '6') DrwPngImg(Clock[6], xuu, yu);
           if (zs[3] == '7') DrwPngImg(Clock[7], xuu, yu);
           if (zs[3] == '8') DrwPngImg(Clock[8], xuu, yu);
           if (zs[3] == '9') DrwPngImg(Clock[9], xuu, yu);
           if (zs[4] == '0') DrwPngImg(Clock[0], xuu+40, yu);
           if (zs[4] == '1') DrwPngImg(Clock[1], xuu+40, yu);
           if (zs[4] == '2') DrwPngImg(Clock[2], xuu+40, yu);
           if (zs[4] == '3') DrwPngImg(Clock[3], xuu+40, yu);
           if (zs[4] == '4') DrwPngImg(Clock[4], xuu+40, yu);
           if (zs[4] == '5') DrwPngImg(Clock[5], xuu+40, yu);
           if (zs[4] == '6') DrwPngImg(Clock[6], xuu+40, yu);
           if (zs[4] == '7') DrwPngImg(Clock[7], xuu+40, yu);
           if (zs[4] == '8') DrwPngImg(Clock[8], xuu+40, yu);
           if (zs[4] == '9') DrwPngImg(Clock[9], xuu+40, yu);
        }
        else 
        {
            ascii2ws(ws, zs); DrawString( ws, 11,  65,  229, 320, 1, 3, co21, GetPaletteAdrByColorIndex( 23 ) );
            sprintf (pyfstr, "Заряд батареи: %i%c", battery, '%'); ascii2ws(ws, pyfstr); DrawString( ws, 58,  175,  230, 195, 8, 1, co21, GetPaletteAdrByColorIndex( 23 ) );
            DrawRectangle( 31, 181, 47,187, 0, co21, GetPaletteAdrByColorIndex( 23 ));
            DrawRectangle( 33, 183, 32+((13*battery)/100),185, 0, co21, co21);
            
            sprintf (pyfstr, "ОЗУ: %iKb", GetFreeRamAvail()/1024); ascii2ws(ws, pyfstr); DrawString( ws, 58,  190,  230, 210, 8, 1, co21, GetPaletteAdrByColorIndex( 23 ) );
            DrawRectangle( 31, 196, 47,202, 0, co21, GetPaletteAdrByColorIndex( 23 ));
            DrawRectangle( 33, 198, 32+(((13*GetFreeRamAvail())/1024)/int_settings[25]),200, 0, co21, co21);
        }
        
        DrawRectangle( 0, 296, 240,320, 1, co27, co27);
        ascii2ws(ws, "Входящие"); DrawString( ws, 10,  300,  230, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
        ascii2ws(ws, "Программы");  DrawString( ws, 10,  300,  230, 320, 9, 4, co126, GetPaletteAdrByColorIndex( 23 ) );
        break;
        
        //------------------------------------------
        
        case 1:
            ascii2ws(ws, "Контакты"); DrawString( ws, 11,  27,  229, 320, 5, 3, co21, GetPaletteAdrByColorIndex( 23 ) );
            if (Adr_Cur<6) DrwPngImg(SetIco[5], 0, 22+37*(Adr_Cur+1));
            CMC = Play5(adressmv);
    
             /* DrawString( e_ws, 10,  200,  230, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );*/
            DrawRectangle( 0, 296, 240,320, 1, co27, co27);
            ascii2ws(ws, "Больше"); DrawString( ws, 10,  300,  230, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
            ascii2ws(ws, "Меню");  DrawString( ws, 10,  300,  230, 320, 9, 4, co126, GetPaletteAdrByColorIndex( 23 ) );
        break;
        
    //------------------------------------------
        
       case 2:
          ascii2ws(ws, "Сообщения"); DrawString( ws, 11,  27,  229, 320, 5, 3, co21, GetPaletteAdrByColorIndex( 23 ) );
          DrwPngImg(SetIco[36], 203, 59);
    
          ascii2ws(ws, "Нет новых сообщений");  DrawString( ws, 10,  145,  230, 320, 6, 3, co21, GetPaletteAdrByColorIndex( 23 ) );
          
          DrawRectangle( 0, 296, 240,320, 1, co27, co27);
          ascii2ws(ws, "Все"); DrawString( ws, 10,  300,  230, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
          ascii2ws(ws, "Меню");  DrawString( ws, 10,  300,  230, 320, 9, 4, co126, GetPaletteAdrByColorIndex( 23 ) );
        break;
        
      //------------------------------------------
        
      case 3:
         ascii2ws(ws, "Эл. почта"); DrawString( ws, 11,  27,  229, 320, 5, 3, co21, GetPaletteAdrByColorIndex( 23 ) );
         DrwPngImg(SetIco[11], 203, 59);
    
         DrawRectangle( 112-SetIco[35]->w/2, 70, 240-(126-SetIco[35]->w/2)-15,180+SetIco[35]->h/2, 0, co22, co126);
         //DrawLine(112-SetIco[35]->w/2,100,240-(126-SetIco[35]->w/2)-13,100,1,co22);
         DrawRectangle( 111-SetIco[35]->w/2, 66, 240-(126-SetIco[35]->w/2)-18,180+SetIco[35]->h/2, 0, co22, co126);
         DrawLine(111-SetIco[35]->w/2,100,240-(126-SetIco[35]->w/2)-18,100,1,co22);
    
         ascii2ws(ws, "Новых писем нет"); DrawString( ws, 113-(SetIco[35]->w/2)+3,  67,  240-(126-SetIco[35]->w/2)-3, 80, 9, 1, co24, GetPaletteAdrByColorIndex( 23 ) );
         ascii2ws(ws, "MD TouchFLO"); DrawString( ws, 114-(SetIco[35]->w/2)+3,  81,  240-(126-SetIco[35]->w/2)-65, 100, 10, 1, co22, GetPaletteAdrByColorIndex( 23 ) );
         ascii2ws(ws, "12.55"); DrawString( ws, 240-(126-SetIco[35]->w/2)-60,  81,  240-(126-SetIco[35]->w/2)-16, 100, 10, 2, co22, GetPaletteAdrByColorIndex( 23 ) );
         ascii2ws(ws, "Не обнаружено новых писем в почтовом ящике, возможно не подключен плагин управления электронной почтой..");
         DrawString( ws, 114-(SetIco[35]->w/2)+3,  101,  240-(126-SetIco[35]->w/2)-16, 180+SetIco[35]->h/2, 10, 1, co22, GetPaletteAdrByColorIndex( 23 ) );
    
         DrwPngImg(SetIco[35], 105-SetIco[35]->w/2, 190-SetIco[35]->h/2);
    
         DrawRectangle( 0, 296, 240,320, 1, co27, co27);
         ascii2ws(ws, "Получить"); DrawString( ws, 10,  300,  230, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
         ascii2ws(ws, "Меню");  DrawString( ws, 10,  300,  230, 320, 9, 4, co126, GetPaletteAdrByColorIndex( 23 ) );
      break;
      
      //------------------------------------------
      
      case 4:
         zxinet = zxn*37-4;
         if (zxn == 0 && Setzxn==1)  DrwPngImg(SetIco[8], 38, 171);
         DrwPngImg(FImage11, 120-FImage11->w/2, zxinet + 57);
         ascii2ws(ws, "Запустить браузер"); DrawString( ws, 0,  zxinet +170,  240, zxinet +200, 6, 3, co21, GetPaletteAdrByColorIndex( 23 ) );
         DrawLine(38,zxinet + 195,202,zxinet + 195,1,co22x);
    
         if (zxn && Setzxn) DrwPngImg(SetIco[5], 0, 171);
    
         zxinet = zxn*37;
         DrawLine(0,zxinet +208,239,zxinet +208,1,co22x);
         ascii2ws(ws, "Смотреть видео"); DrawString( ws, 42,  zxinet +212,  229, zxinet +320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
         ascii2ws(ws, "Видео оффлайн на телефоне"); DrawString( ws, 42,  zxinet +226,  229, zxinet +320, 8, 1, co22z, GetPaletteAdrByColorIndex( 23 ) );
         DrwPngImg(SetIco[6], 10, zxinet +215);
    
         zxinet = (zxn+1)*37;
         DrawLine(0,zxinet +208,239,zxinet +208,1,co22x);
         ascii2ws(ws, "Google"); DrawString( ws, 10,  zxinet +212,  229, zxinet +320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
         ascii2ws(ws, "www.google.com"); DrawString( ws, 23,  zxinet +226,  229, zxinet +320, 8, 1, co22z, GetPaletteAdrByColorIndex( 23 ) );
         DrwPngImg(SetIco[9], 10, zxinet +229);
    
         zxinet = (zxn+2)*37;
         DrawLine(0,zxinet +208,239,zxinet +208,1,co22x);
         ascii2ws(ws, "Siemens-Club Team"); DrawString( ws, 10,  zxinet +212,  229, zxinet +320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
         ascii2ws(ws, "team-sc.ru"); DrawString( ws, 23,  zxinet +226,  229, zxinet +320, 8, 1, co22z, GetPaletteAdrByColorIndex( 23 ) );
         DrwPngImg(SetIco[9], 10, zxinet +229);
    
    
         zxinet = (zxn+3)*37-1;
         DrawLine(0,zxinet +208,239,zxinet +208,1,co22x);
         ascii2ws(ws, "Wikipedia"); DrawString( ws, 10,  zxinet +212,  229, zxinet +320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
         ascii2ws(ws, "ru.wikipedia.org"); DrawString( ws, 23,  zxinet +226,  229, zxinet +320, 8, 1, co22z, GetPaletteAdrByColorIndex( 23 ) );
         DrwPngImg(SetIco[9], 10, zxinet +229);
    
         zxinet = (zxn+4)*37-1;
         DrawLine(0,zxinet +208,239,zxinet +208,1,co22x);
         ascii2ws(ws, "Yandex"); DrawString( ws, 10,  zxinet +212,  229, zxinet +320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
         ascii2ws(ws, "www.yandex.ru"); DrawString( ws, 23,  zxinet +226,  229, zxinet +320, 8, 1, co22z, GetPaletteAdrByColorIndex( 23 ) );
         DrwPngImg(SetIco[9], 10, zxinet +229);
    
         DrwPngImg(FImage6, 0, 25);
         ascii2ws(ws, "Интернет"); DrawString( ws, 11,  27,  229, 320, 5, 3, co21, GetPaletteAdrByColorIndex( 23 ) );
    
         DrawRectangle( 0, 296, 240,320, 1, co27, co27);
         ascii2ws(ws, "Обозреватель"); DrawString( ws, 10,  300,  230, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
         ascii2ws(ws, "Меню");  DrawString( ws, 10,  300,  230, 320, 9, 4, co126, GetPaletteAdrByColorIndex( 23 ) );
       break;
      
      //------------------------------------------
      
      case 5:
         ascii2ws(ws, "Фото и видео"); DrawString( ws, 11,  27,  229, 320, 5, 3, co21, GetPaletteAdrByColorIndex( 23 ) );
         Play6(1,0);
        //ascii2ws(ws, "Извините, вкладка в процессе доработки и временно закрыта");  DrawString( ws, 10,  145,  230, 320, 8, 3, co21, GetPaletteAdrByColorIndex( 23 ) );
    
         DrawRectangle( 0, 296, 240,320, 1, co27, co27);
         ascii2ws(ws, "Видео"); DrawString( ws, 10,  300,  230, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
         ascii2ws(ws, "Меню");  DrawString( ws, 10,  300,  230, 320, 9, 4, co126, GetPaletteAdrByColorIndex( 23 ) );
      break;
      
      //------------------------------------------
      
      case 6:
         ascii2ws(ws, "Музыка"); DrawString( ws, 11,  27,  229, 320, 5, 3, co21, GetPaletteAdrByColorIndex( 23 ) );
         Play6(1,1);
         //ascii2ws(ws, "Извините, вкладка в процессе доработки и временно закрыта");  DrawString( ws, 10,  145,  230, 320, 8, 3, co21, GetPaletteAdrByColorIndex( 23 ) );
    
         DrawRectangle( 0, 296, 240,320, 1, co27, co27);
         ascii2ws(ws, "Радио"); DrawString( ws, 10,  300,  230, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
         ascii2ws(ws, "Меню");  DrawString( ws, 10,  300,  230, 320, 9, 4, co126, GetPaletteAdrByColorIndex( 23 ) );
      break;
      
      //------------------------------------------
    
      case 7:
        ascii2ws(ws, "Погода"); DrawString( ws, 11,  27,  229, 320, 5, 3, co21, GetPaletteAdrByColorIndex( 23 ) );
        ascii2ws(ws, "Извините, вкладка в процессе доработки и временно закрыта");  DrawString( ws, 10,  145,  230, 320, 8, 3, co21, GetPaletteAdrByColorIndex( 23 ) );
    
        DrawRectangle( 0, 296, 240,320, 1, co27, co27);
        ascii2ws(ws, "5 дней"); DrawString( ws, 10,  300,  230, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
        ascii2ws(ws, "Меню");  DrawString( ws, 10,  300,  230, 320, 9, 4, co126, GetPaletteAdrByColorIndex( 23 ) );
      break;
      
    //------------------------------------------
    
      case 8:
         ascii2ws(ws, "Настройка"); DrawString( ws, 11,  27,  229, 320, 5, 3, co21, GetPaletteAdrByColorIndex( 23 ) );
         if (SetCursor) DrwPngImg(SetIco[5], 0, 22+37*SetCursor);
    
         ascii2ws(ws, "Система"); DrawString( ws, 42,  62,  229, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
         ascii2ws(ws, "Настройки оболочки и системы"); DrawString( ws, 42,  76,  229, 320, 8, 1, co22z, GetPaletteAdrByColorIndex( 23 ) );
         DrwPngImg(SetIco[0], 8, 65);
         DrawLine(0,95,239,95,1,co22x);
    
         ascii2ws(ws, "Звуки"); DrawString( ws, 42,  99,  229, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
         ascii2ws(ws, "Звонки и сигналы"); DrawString( ws, 42,  113,  229, 320, 8, 1, co22z, GetPaletteAdrByColorIndex( 23 ) );
         DrwPngImg(SetIco[1], 8, 102);
         DrawLine(0,132,239,132,1,co22x);
    
         ascii2ws(ws, "Графика"); DrawString( ws, 42,  136,  229, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
         ascii2ws(ws, "Графика, шрифты и цвета"); DrawString( ws, 42,  150,  229, 320, 8, 1, co22z, GetPaletteAdrByColorIndex( 23 ) );
         DrwPngImg(SetIco[2], 8, 139);
         DrawLine(0,169,239,169,1,co22x);
    
         ascii2ws(ws, "Приложения"); DrawString( ws, 42,  173,  229, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
         ascii2ws(ws, "Настройка программ"); DrawString( ws, 42,  187,  229, 320, 8, 1, co22z, GetPaletteAdrByColorIndex( 23 ) );
         DrwPngImg(SetIco[3], 8, 176);
         DrawLine(0,206,239,206,1,co22x);
    
         ascii2ws(ws, "Дополн. настройки"); DrawString( ws, 42,  210,  229, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
         ascii2ws(ws, "Настройки не вошедшие в др."); DrawString( ws, 42,  224,  229, 320, 8, 1, co22z, GetPaletteAdrByColorIndex( 23 ) );
         DrwPngImg(SetIco[4], 8, 213);
    
    
         DrawRectangle( 0, 296, 240,320, 1, co27, co27);
         ascii2ws(ws, "Все"); DrawString( ws, 10,  300,  230, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
         ascii2ws(ws, "Меню");  DrawString( ws, 10,  300,  230, 320, 9, 4, co126, GetPaletteAdrByColorIndex( 23 ) );
      break;
      
    //------------------------------------------
    
      case 9:
        ascii2ws(ws, "Программы"); DrawString( ws, 11,  27,  229, 320, 5, 3, co21, GetPaletteAdrByColorIndex( 23 ) );
        ascii2ws(ws, "Извините, вкладка в процессе доработки и временно закрыта");  DrawString( ws, 10,  145,  230, 320, 8, 3, co21, GetPaletteAdrByColorIndex( 23 ) );
    
        DrawRectangle( 0, 296, 240,320, 1, co27, co27);
        ascii2ws(ws, "Выбрать"); DrawString( ws, 10,  300,  230, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
        ascii2ws(ws, "Меню");  DrawString( ws, 10,  300,  230, 320, 9, 4, co126, GetPaletteAdrByColorIndex( 23 ) );
      break;
      
    //------------------------------------------
      
      case 10:
        ascii2ws(ws, "djuice"); DrawString( ws, 11,  27,  229, 320, 5, 3, co21, GetPaletteAdrByColorIndex( 23 ) );
        ascii2ws(ws, "Извините, вкладка в процессе доработки и временно закрыта");  DrawString( ws, 10,  145,  230, 320, 8, 3, co21, GetPaletteAdrByColorIndex( 23 ) );
    
        DrawRectangle( 0, 296, 240,320, 1, co27, co27);
        ascii2ws(ws, "Телефон"); DrawString( ws, 10,  300,  230, 320, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
        ascii2ws(ws, "Меню");  DrawString( ws, 10,  300,  230, 320, 9, 4, co126, GetPaletteAdrByColorIndex( 23 ) );
      break;
      
    //------------------------------------------
   }//switch(mod)

   if(mod!=1) {adressmv = 0; CMC = 6; Adr_Cur = 0;}
   if(mod!=0) {zxmainzerro = 0;}
   mfree (zs);
   mfree(pyfstr);
   mfree (ds);
   FreeWS(ws);
}

