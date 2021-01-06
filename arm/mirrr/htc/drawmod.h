  WSHDR *e_ws;
char *filename;
//================================================================================================================
extern "C" {
extern char days[7];
extern char *day[7];
extern TTime alarm_time;
extern int snooze_time;
extern int alarm_active;
extern int auto_snooze;
extern int   alarm_hour;
extern int   alarm_min;
extern void ParseSnoozeTime(char *s);
extern void GetTime(TTime *t,int time);
extern void ParseAlarmTime(char *s);
extern void ParseDayInUse(char *s);
extern void ParseAlarmActive(char *s);
extern void ParseAutoSnooze(char *s);
}
//================================================================================================================
char *temp_chars; //���������� ����
char **temp_lines; //������ ���������� �� ������


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
  p=temp_chars=(char *)malloc(fsize+1);
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
	temp_lines=(char **)realloc(temp_lines,(i+1)*sizeof(char *));
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

extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

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
    //if(strstr(temp_lines[j],"snooze_time"))  ParseSnoozeTime(s);
    //if(strstr(temp_lines[j],"days_in_use"))  ParseDayInUse(s);
    if(strstr(temp_lines[j],"alarm_time"))   ParseAlarmTime(s);
    //if(strstr(temp_lines[j],"alarm_active")) ParseAlarmActive(s);
    //if(strstr(temp_lines[j],"auto_snooze"))  ParseAutoSnooze(s);
    j++;
  }
}

//================================================================================================================





 void drawmod(int mod){
	 int pyf = GetMissedCallsCount();
     WSHDR * ws = AllocWS( 256 );
      char *zs = (char *)malloc (6);
      char *ds = (char *)malloc (20);
    TDate date;
    TTime time;
int xu = 30; int yu = 76; int xuu = 240-29-82+1;
char *pyfstr = (char *)malloc(40);
int yid = int_settings[22]*70;

      switch(mod)
      {
//------------------------------------------

case 0:

    GetDateTime(&date,&time);
sprintf(zs, "%02i:%02i",time.hour,time.min);
sprintf(ds, "%02i.%02i.%02i",date.day,date.month,date.year);
ds[6]=ds[8];ds[7]=ds[9];ds[8]=0;
if (int_settings[22]==0){//������ �������� ��� �����
if(int_skin[1])DrwPngImg(FImage4, 29+int_skin[4], 63+int_skin[5]);
if(int_skin[2])DrwPngImg(FImage4, 240-29-82+int_skin[6], 63+int_skin[7]);
}
//========== ������ ���� � ���������� ==============
ascii2ws(ws, ds); DrawString( ws, 11,  33,  229, 320, 8, 1, colors[25], GetPaletteAdrByColorIndex( 23 ) );
GetProvider(ws, 0);
DrawString( ws, 11,  33,  229, 320, 8, 4, colors[25], GetPaletteAdrByColorIndex( 23 ) );


if (IsUnlocked()){
	if (zxmainzerro) DrwPngImg(SetIco[10], 29, 155+28*zxmain-yid); // - ������ ������ ��� "������","���������"
DrwPngImg(FImage9, 32, 189-yid);
DrawLine(28,182-yid,212,182-yid,1,colors[16]);
DrawLine(28,210-yid,212,210-yid,1,colors[16]);
DrawLine(28,238-yid,212,238-yid,1,colors[16]);

if (!pyf) {
	ascii2ws(ws, "������");
  } else {
	sprintf (pyfstr, "������ (%i)", pyf);
	ascii2ws(ws, pyfstr);
}
if(zxmain != 1 || zxmainzerro==0) DrawString( ws, 58,  183-yid,  230, 320-yid, 6, 1, colors[9], GetPaletteAdrByColorIndex( 23 ) );
else  DrawString( ws, 58,  183-yid,  230, 320-yid, 6, 1, colors[15], GetPaletteAdrByColorIndex( 23 ) );

if (GetAlarmclockState(1)) {
	sprintf (pyfstr, "%02i:%02i", alarm_hour, alarm_min);
	ascii2ws(ws, pyfstr);
	DrwPngImg(FImage9a, 33, 166-yid);
	DrawString( ws, 50,  163-yid,  230, 320-yid, 8, 1, colors[28], GetPaletteAdrByColorIndex( 23 ) );}
else {
	ascii2ws(ws, "������ ��������");
	DrwPngImg(FImage9b, 33, 166-yid);
	DrawString( ws, 50,  163-yid,  230, 320-yid, 8, 1, colors[27], GetPaletteAdrByColorIndex( 23 ) );}

ascii2ws(ws, "���������");
if(zxmain != 2  || zxmainzerro==0)  { DrawString( ws, 58,  211-yid,  230, 320-yid, 6, 1, colors[9], GetPaletteAdrByColorIndex( 23 ) );}
else  {DrawString( ws, 58,  211-yid,  230, 320-yid, 6, 1, colors[15], GetPaletteAdrByColorIndex( 23 ) );}
}
else {

DrawLine(28,183-yid,211,183-yid,1,colors[16]);
DrawLine(28,237-yid,211,237-yid,1,colors[16]);
DrawLine(28,183-yid,28,237-yid,1,colors[16]);
DrawLine(211,183-yid,211,237-yid,1,colors[16]);

ascii2ws(ws, "��� �������������");  DrawString( ws, 38,  185-yid,  230, 320-yid, 6, 1, colors[9], GetPaletteAdrByColorIndex( 23 ) );
ascii2ws(ws, "������� #");  DrawString( ws, 38,  208-yid,  230, 320-yid, 6, 1, colors[9], GetPaletteAdrByColorIndex( 23 ) );

	}
if (int_settings[22]==0){ //��������� ����
if (zs[0] == '0') DrwPngImg(Clock[0], xu+int_skin[8], yu+int_skin[9]);
if (zs[0] == '1') DrwPngImg(Clock[1], xu+int_skin[8], yu+int_skin[9]);
if (zs[0] == '2') DrwPngImg(Clock[2], xu+int_skin[8], yu+int_skin[9]);
if (zs[0] == '3') DrwPngImg(Clock[3], xu+int_skin[8], yu+int_skin[9]);
if (zs[0] == '4') DrwPngImg(Clock[4], xu+int_skin[8], yu+int_skin[9]);
if (zs[0] == '5') DrwPngImg(Clock[5], xu+int_skin[8], yu+int_skin[9]);
if (zs[0] == '6') DrwPngImg(Clock[6], xu+int_skin[8], yu+int_skin[9]);
if (zs[0] == '7') DrwPngImg(Clock[7], xu+int_skin[8], yu+int_skin[9]);
if (zs[0] == '8') DrwPngImg(Clock[8], xu+int_skin[8], yu+int_skin[9]);
if (zs[0] == '9') DrwPngImg(Clock[9], xu+int_skin[8], yu+int_skin[9]);

if (zs[1] == '0') DrwPngImg(Clock[0], xu+40+int_skin[10], yu+int_skin[11]);
if (zs[1] == '1') DrwPngImg(Clock[1], xu+40+int_skin[10], yu+int_skin[11]);
if (zs[1] == '2') DrwPngImg(Clock[2], xu+40+int_skin[10], yu+int_skin[11]);
if (zs[1] == '3') DrwPngImg(Clock[3], xu+40+int_skin[10], yu+int_skin[11]);
if (zs[1] == '4') DrwPngImg(Clock[4], xu+40+int_skin[10], yu+int_skin[11]);
if (zs[1] == '5') DrwPngImg(Clock[5], xu+40+int_skin[10], yu+int_skin[11]);
if (zs[1] == '6') DrwPngImg(Clock[6], xu+40+int_skin[10], yu+int_skin[11]);
if (zs[1] == '7') DrwPngImg(Clock[7], xu+40+int_skin[10], yu+int_skin[11]);
if (zs[1] == '8') DrwPngImg(Clock[8], xu+40+int_skin[10], yu+int_skin[11]);
if (zs[1] == '9') DrwPngImg(Clock[9], xu+40+int_skin[10], yu+int_skin[11]);

if (zs[3] == '0') DrwPngImg(Clock[0], xuu+int_skin[12], yu+int_skin[13]);
if (zs[3] == '1') DrwPngImg(Clock[1], xuu+int_skin[12], yu+int_skin[13]);
if (zs[3] == '2') DrwPngImg(Clock[2], xuu+int_skin[12], yu+int_skin[13]);
if (zs[3] == '3') DrwPngImg(Clock[3], xuu+int_skin[12], yu+int_skin[13]);
if (zs[3] == '4') DrwPngImg(Clock[4], xuu+int_skin[12], yu+int_skin[13]);
if (zs[3] == '5') DrwPngImg(Clock[5], xuu+int_skin[12], yu+int_skin[13]);
if (zs[3] == '6') DrwPngImg(Clock[6], xuu+int_skin[12], yu+int_skin[13]);
if (zs[3] == '7') DrwPngImg(Clock[7], xuu+int_skin[12], yu+int_skin[13]);
if (zs[3] == '8') DrwPngImg(Clock[8], xuu+int_skin[12], yu+int_skin[13]);
if (zs[3] == '9') DrwPngImg(Clock[9], xuu+int_skin[12], yu+int_skin[13]);

if (zs[4] == '0') DrwPngImg(Clock[0], xuu+40+int_skin[14], yu+int_skin[15]);
if (zs[4] == '1') DrwPngImg(Clock[1], xuu+40+int_skin[14], yu+int_skin[15]);
if (zs[4] == '2') DrwPngImg(Clock[2], xuu+40+int_skin[14], yu+int_skin[15]);
if (zs[4] == '3') DrwPngImg(Clock[3], xuu+40+int_skin[14], yu+int_skin[15]);
if (zs[4] == '4') DrwPngImg(Clock[4], xuu+40+int_skin[14], yu+int_skin[15]);
if (zs[4] == '5') DrwPngImg(Clock[5], xuu+40+int_skin[14], yu+int_skin[15]);
if (zs[4] == '6') DrwPngImg(Clock[6], xuu+40+int_skin[14], yu+int_skin[15]);
if (zs[4] == '7') DrwPngImg(Clock[7], xuu+40+int_skin[14], yu+int_skin[15]);
if (zs[4] == '8') DrwPngImg(Clock[8], xuu+40+int_skin[14], yu+int_skin[15]);
if (zs[4] == '9') DrwPngImg(Clock[9], xuu+40+int_skin[14], yu+int_skin[15]);

} else {
ascii2ws(ws, zs); DrawString( ws, 11+int_skin[17],  65+int_skin[18],  229+int_skin[17], 320, 1, int_skin[16], colors[26], GetPaletteAdrByColorIndex( 23 ) );
sprintf (pyfstr, "����� �������: %i%c", battery, '%'); ascii2ws(ws, pyfstr); DrawString( ws, 58,  175,  230, 195, 8, 1, colors[9], GetPaletteAdrByColorIndex( 23 ) );
DrawRectangle( 31, 181, 47,187, 0, colors[9], GetPaletteAdrByColorIndex( 23 ));
DrawRectangle( 33, 183, 32+((13*battery)/100),185, 0, colors[9], colors[9]);

sprintf (pyfstr, "���: %iKb", GetFreeRamAvail()/1024); ascii2ws(ws, pyfstr); DrawString( ws, 58,  190,  230, 210, 8, 1, colors[9], GetPaletteAdrByColorIndex( 23 ) );
DrawRectangle( 31, 196, 47,202, 0, colors[9], GetPaletteAdrByColorIndex( 23 ));
DrawRectangle( 33, 198, 32+(((13*GetFreeRamAvail())/1024)/int_settings[25]),200, 0, colors[9], colors[9]);
	}




    DrawRectangle( 0, 296, 240,320, 1, colors[3], colors[3]);
    ascii2ws(ws, "��������"); DrawString( ws, 10,  300,  230, 320, 9, 1, colors[4], GetPaletteAdrByColorIndex( 23 ) );
    ascii2ws(ws, "���������");  DrawString( ws, 10,  300,  230, 320, 9, 4, colors[4], GetPaletteAdrByColorIndex( 23 ) );
break;
//------------------------------------------
case 1:
     ascii2ws(ws, "��������"); DrawString( ws, 11,  27,  229, 320, 5, 3, colors[25], GetPaletteAdrByColorIndex( 23 ) );
	 if (Adr_Cur<6) DrwPngImg(SetIco[5], 0, 22+37*(Adr_Cur+1));
     CMC = Play5(adressmv, Adr_Cur);



    DrawRectangle( 0, 296, 240,320, 1, colors[3], colors[3]);
    ascii2ws(ws, "������"); DrawString( ws, 10,  300,  230, 320, 9, 1, colors[4], GetPaletteAdrByColorIndex( 23 ) );
    ascii2ws(ws, "����");  DrawString( ws, 10,  300,  230, 320, 9, 4, colors[4], GetPaletteAdrByColorIndex( 23 ) );

break;
//------------------------------------------
case 2:
     ascii2ws(ws, "���������"); DrawString( ws, 11,  27,  229, 320, 5, 3, colors[25], GetPaletteAdrByColorIndex( 23 ) );
DrwPngImg(SetIco[36], 203, 59);


/**============================================================================================
 *
 typedef struct
{
	int type;
	char SMS_CENTER[32];
	char Number[32];
	char Time[32];
	int tm[6];
	short sig;
	char cnt, n;
	WSHDR *name;
	WSHDR *SMS_TEXT;
}SMS_DATA;
*/

if((!SMSD[2].SMS_TEXT)||(SMSD[2].n!=1)) {ascii2ws(ws, "��� ����� ���������");  DrawString( ws, 10,  145,  230, 320, 6, 3, colors[9], GetPaletteAdrByColorIndex( 23 ) );}
else  DrawString( SMSD[2].SMS_TEXT, 10,  145,  230, 320, 6, 3, colors[9], GetPaletteAdrByColorIndex( 23 ) );
/**============================================================================================*/


    DrawRectangle( 0, 296, 240,320, 1, colors[3], colors[3]);
    ascii2ws(ws, "���"); DrawString( ws, 10,  300,  230, 320, 9, 1, colors[4], GetPaletteAdrByColorIndex( 23 ) );
    ascii2ws(ws, "����");  DrawString( ws, 10,  300,  230, 320, 9, 4, colors[4], GetPaletteAdrByColorIndex( 23 ) );
break;
//------------------------------------------
case 3:
     ascii2ws(ws, "��. �����"); DrawString( ws, 11,  27,  229, 320, 5, 3, colors[25], GetPaletteAdrByColorIndex( 23 ) );
DrwPngImg(SetIco[11], 203, 59);

DrawRectangle( 112-SetIco[35]->w/2, 70, 240-(126-SetIco[35]->w/2)-15,180+SetIco[35]->h/2, 0, colors[18], colors[17]);
//DrawLine(112-SetIco[35]->w/2,100,240-(126-SetIco[35]->w/2)-13,100,1,co22);
DrawRectangle( 111-SetIco[35]->w/2, 66, 240-(126-SetIco[35]->w/2)-18,180+SetIco[35]->h/2, 0, colors[18], colors[17]);
DrawLine(111-SetIco[35]->w/2,100,240-(126-SetIco[35]->w/2)-18,100,1,colors[19]);




 ascii2ws(ws, "����� ����� ���"); DrawString( ws, 113-(SetIco[35]->w/2)+3,  67,  240-(126-SetIco[35]->w/2)-3, 80, 9, 1, colors[20], GetPaletteAdrByColorIndex( 23 ) );
ascii2ws(ws, "MD TouchFLO"); DrawString( ws, 114-(SetIco[35]->w/2)+3,  81,  240-(126-SetIco[35]->w/2)-65, 100, 10, 1, colors[20], GetPaletteAdrByColorIndex( 23 ) );
ascii2ws(ws, "12.55"); DrawString( ws, 240-(126-SetIco[35]->w/2)-60,  81,  240-(126-SetIco[35]->w/2)-16, 100, 10, 2, colors[20], GetPaletteAdrByColorIndex( 23 ) );
ascii2ws(ws, "�� ���������� ����� ����� � �������� �����!");
DrawString( ws, 114-(SetIco[35]->w/2)+3,  101,  240-(126-SetIco[35]->w/2)-16, 180+SetIco[35]->h/2, 10, 1, colors[21], GetPaletteAdrByColorIndex( 23 ) );

DrwPngImg(SetIco[35], 105-SetIco[35]->w/2, 190-SetIco[35]->h/2);

    DrawRectangle( 0, 296, 240,320, 1, colors[3], colors[3]);
    ascii2ws(ws, "��������"); DrawString( ws, 10,  300,  230, 320, 9, 1, colors[4], GetPaletteAdrByColorIndex( 23 ) );
    ascii2ws(ws, "����");  DrawString( ws, 10,  300,  230, 320, 9, 4, colors[4], GetPaletteAdrByColorIndex( 23 ) );
break;
//------------------------------------------
case 4:
    zxinet = zxn*37-4;
    if (zxn == 0 && Setzxn==1)  DrwPngImg(SetIco[8], 38, 171);
    DrwPngImg(FImage11, 120-FImage11->w/2, zxinet + 57);  ascii2ws(ws, "��������� �������");
    if (!(zxn == 0 && Setzxn==1)) DrawString( ws, 0,  zxinet +170,  240, zxinet +200, 6, 3, colors[7], GetPaletteAdrByColorIndex( 23 ) );
    else   DrawString( ws, 0,  zxinet +170,  240, zxinet +200, 6, 3, colors[13], GetPaletteAdrByColorIndex( 23 ) );
    DrawLine(38,zxinet + 195,202,zxinet + 195,1,colors[16]);

    if (zxn && Setzxn) DrwPngImg(SetIco[5], 0, 171);



      zxinet = zxn*37;
     DrawLine(0,zxinet +208,239,zxinet +208,1,colors[16]);
     ascii2ws(ws, "�������� �����"); DrawString( ws, 42,  zxinet +212,  229, zxinet +320, 9, 1, colors[7], GetPaletteAdrByColorIndex( 23 ) );
     ascii2ws(ws, "����� ������� �� ��������"); DrawString( ws, 42,  zxinet +226,  229, zxinet +320, 8, 1, colors[8], GetPaletteAdrByColorIndex( 23 ) );
     DrwPngImg(SetIco[6], 10, zxinet +215);

    zxinet = (zxn+1)*37;
     DrawLine(0,zxinet +208,239,zxinet +208,1,colors[16]);
     ascii2ws(ws, "Google"); DrawString( ws, 10,  zxinet +212,  229, zxinet +320, 9, 1, colors[7], GetPaletteAdrByColorIndex( 23 ) );
     ascii2ws(ws, "www.google.com"); DrawString( ws, 23,  zxinet +226,  229, zxinet +320, 8, 1, colors[8], GetPaletteAdrByColorIndex( 23 ) );
     DrwPngImg(SetIco[9], 10, zxinet +229);

    zxinet = (zxn+2)*37;
    DrawLine(0,zxinet +208,239,zxinet +208,1,colors[16]);
    ascii2ws(ws, "Siemens-Club Team"); DrawString( ws, 10,  zxinet +212,  229, zxinet +320, 9, 1, colors[7], GetPaletteAdrByColorIndex( 23 ) );
    ascii2ws(ws, "team-sc.ru"); DrawString( ws, 23,  zxinet +226,  229, zxinet +320, 8, 1, colors[8], GetPaletteAdrByColorIndex( 23 ) );
    DrwPngImg(SetIco[9], 10, zxinet +229);


    zxinet = (zxn+3)*37-1;
    DrawLine(0,zxinet +208,239,zxinet +208,1,colors[16]);
    ascii2ws(ws, "Wikipedia"); DrawString( ws, 10,  zxinet +212,  229, zxinet +320, 9, 1, colors[7], GetPaletteAdrByColorIndex( 23 ) );
    ascii2ws(ws, "ru.wikipedia.org"); DrawString( ws, 23,  zxinet +226,  229, zxinet +320, 8, 1, colors[8], GetPaletteAdrByColorIndex( 23 ) );
    DrwPngImg(SetIco[9], 10, zxinet +229);

    zxinet = (zxn+4)*37-1;
    DrawLine(0,zxinet +208,239,zxinet +208,1,colors[16]);
    ascii2ws(ws, "Yandex"); DrawString( ws, 10,  zxinet +212,  229, zxinet +320, 9, 1, colors[7], GetPaletteAdrByColorIndex( 23 ) );
    ascii2ws(ws, "www.yandex.ru"); DrawString( ws, 23,  zxinet +226,  229, zxinet +320, 8, 1, colors[8], GetPaletteAdrByColorIndex( 23 ) );
    DrwPngImg(SetIco[9], 10, zxinet +229);

    if (FImage6->bpnum == 10){ DrwPngImg(FImage6,0,25);} else DrawRectangle( -1, 25, 241,55, 1, colors[24], colors[6]);
    ascii2ws(ws, "��������"); DrawString( ws, 11,  27,  229, 320, 5, 3, colors[25], GetPaletteAdrByColorIndex( 23 ) );





        DrawRectangle( 0, 296, 240,320, 1, colors[3], colors[3]);
    ascii2ws(ws, "������������"); DrawString( ws, 10,  300,  230, 320, 9, 1, colors[4], GetPaletteAdrByColorIndex( 23 ) );
    ascii2ws(ws, "����");  DrawString( ws, 10,  300,  230, 320, 9, 4, colors[4], GetPaletteAdrByColorIndex( 23 ) );
break;
//------------------------------------------
case 5:
     ascii2ws(ws, "���� � �����"); DrawString( ws, 11,  27,  229, 320, 5, 3, colors[25], GetPaletteAdrByColorIndex( 23 ) );


Play6(1,0,0);
//ascii2ws(ws, "��������, ������� � �������� ��������� � �������� �������");  DrawString( ws, 10,  145,  230, 320, 8, 3, colors[9], GetPaletteAdrByColorIndex( 23 ) );


         DrawRectangle( 0, 296, 240,320, 1, colors[3], colors[3]);
    ascii2ws(ws, "�����"); DrawString( ws, 10,  300,  230, 320, 9, 1, colors[4], GetPaletteAdrByColorIndex( 23 ) );
    ascii2ws(ws, "����");  DrawString( ws, 10,  300,  230, 320, 9, 4, colors[4], GetPaletteAdrByColorIndex( 23 ) );
break;
//------------------------------------------
case 6:
    ascii2ws(ws, "������"); DrawString( ws, 11,  27,  229, 320, 5, 3, colors[25], GetPaletteAdrByColorIndex( 23 ) );

Play6(1,1,0);
//ascii2ws(ws, "��������, ������� � �������� ��������� � �������� �������");  DrawString( ws, 10,  145,  230, 320, 8, 3, colors[9], GetPaletteAdrByColorIndex( 23 ) );

        DrawRectangle( 0, 296, 240,320, 1, colors[3], colors[3]);
    ascii2ws(ws, "�����"); DrawString( ws, 10,  300,  230, 320, 9, 1, colors[4], GetPaletteAdrByColorIndex( 23 ) );
    ascii2ws(ws, "����");  DrawString( ws, 10,  300,  230, 320, 9, 4, colors[4], GetPaletteAdrByColorIndex( 23 ) );
break;
//------------------------------------------
case 7:
     ascii2ws(ws, "������"); DrawString( ws, 11,  27,  229, 320, 5, 3, colors[25], GetPaletteAdrByColorIndex( 23 ) );

ascii2ws(ws, "�� ��������� Weather.elf!");  DrawString( ws, 10,  145,  230, 320, 8, 3, colors[9], GetPaletteAdrByColorIndex( 23 ) );

         DrawRectangle( 0, 296, 240,320, 1, colors[3], colors[3]);
    ascii2ws(ws, "5 ����"); DrawString( ws, 10,  300,  230, 320, 9, 1, colors[4], GetPaletteAdrByColorIndex( 23 ) );
    ascii2ws(ws, "����");  DrawString( ws, 10,  300,  230, 320, 9, 4, colors[4], GetPaletteAdrByColorIndex( 23 ) );
break;
//------------------------------------------
case 8:
    ascii2ws(ws, "���������"); DrawString( ws, 11,  27,  229, 320, 5, 3, colors[25], GetPaletteAdrByColorIndex( 23 ) );
    if (SetCursor) DrwPngImg(SetIco[5], 0, 22+37*SetCursor);
	char *coloris7;
	char *coloris8;


if(SetCursor!=1){coloris7 = colors[7]; coloris8 = colors[8];}
else  {coloris7 = colors[13]; coloris8 = colors[14];}

     ascii2ws(ws, "�������"); DrawString( ws, 42,  62,  229, 320, 9, 1, coloris7, GetPaletteAdrByColorIndex( 23 ) );
     ascii2ws(ws, "��������� �������� HTC"); DrawString( ws, 42,  76,  229, 320, 8, 1, coloris8, GetPaletteAdrByColorIndex( 23 ) );
     DrwPngImg(SetIco[0], 8, 65);
     DrawLine(0,95,239,95,1,colors[16]);

if(SetCursor!=2){coloris7 = colors[7]; coloris8 = colors[8];}
else  {coloris7 = colors[13]; coloris8 = colors[14];}

     ascii2ws(ws, "�����"); DrawString( ws, 42,  99,  229, 320, 9, 1, coloris7, GetPaletteAdrByColorIndex( 23 ) );
     ascii2ws(ws, "������ � �������"); DrawString( ws, 42,  113,  229, 320, 8, 1, coloris8, GetPaletteAdrByColorIndex( 23 ) );
     DrwPngImg(SetIco[1], 8, 102);
     DrawLine(0,132,239,132,1,colors[16]);

if(SetCursor!=3){coloris7 = colors[7]; coloris8 = colors[8];}
else  {coloris7 = colors[13]; coloris8 = colors[14];}

     ascii2ws(ws, "�������"); DrawString( ws, 42,  136,  229, 320, 9, 1, coloris7, GetPaletteAdrByColorIndex( 23 ) );
     ascii2ws(ws, "�������, ������ � �����"); DrawString( ws, 42,  150,  229, 320, 8, 1, coloris8, GetPaletteAdrByColorIndex( 23 ) );
     DrwPngImg(SetIco[2], 8, 139);
     DrawLine(0,169,239,169,1,colors[16]);

if(SetCursor!=4){coloris7 = colors[7]; coloris8 = colors[8];}
else  {coloris7 = colors[13]; coloris8 = colors[14];}

     ascii2ws(ws, "����������"); DrawString( ws, 42,  173,  229, 320, 9, 1, coloris7, GetPaletteAdrByColorIndex( 23 ) );
     ascii2ws(ws, "��������� ��������"); DrawString( ws, 42,  187,  229, 320, 8, 1, coloris8, GetPaletteAdrByColorIndex( 23 ) );
     DrwPngImg(SetIco[3], 8, 176);
     DrawLine(0,206,239,206,1,colors[16]);

if(SetCursor!=5){coloris7 = colors[7]; coloris8 = colors[8];}
else  {coloris7 = colors[13]; coloris8 = colors[14];}

     ascii2ws(ws, "������. ���������"); DrawString( ws, 42,  210,  229, 320, 9, 1, coloris7, GetPaletteAdrByColorIndex( 23 ) );
     ascii2ws(ws, "�� �������� � ������"); DrawString( ws, 42,  224,  229, 320, 8, 1, coloris8, GetPaletteAdrByColorIndex( 23 ) );
     DrwPngImg(SetIco[4], 8, 213);



         DrawRectangle( 0, 296, 240,320, 1, colors[3], colors[3]);
    ascii2ws(ws, "���"); DrawString( ws, 10,  300,  230, 320, 9, 1, colors[4], GetPaletteAdrByColorIndex( 23 ) );
    ascii2ws(ws, "����");  DrawString( ws, 10,  300,  230, 320, 9, 4, colors[4], GetPaletteAdrByColorIndex( 23 ) );

break;
//------------------------------------------
case 9:
    ascii2ws(ws, "���������"); DrawString( ws, 11,  27,  229, 320, 5, 3, colors[25], GetPaletteAdrByColorIndex( 23 ) );

ascii2ws(ws, "��� ������������� ����������");  DrawString( ws, 10,  145,  230, 320, 8, 3, colors[9], GetPaletteAdrByColorIndex( 23 ) );


        DrawRectangle( 0, 296, 240,320, 1, colors[3], colors[3]);
    ascii2ws(ws, "�������"); DrawString( ws, 10,  300,  230, 320, 9, 1, colors[4], GetPaletteAdrByColorIndex( 23 ) );
    ascii2ws(ws, "����");  DrawString( ws, 10,  300,  230, 320, 9, 4, colors[4], GetPaletteAdrByColorIndex( 23 ) );
break;
//------------------------------------------
case 10:
    ascii2ws(ws, "djuice"); DrawString( ws, 11,  27,  229, 320, 5, 3, colors[9], GetPaletteAdrByColorIndex( 23 ) );

ascii2ws(ws, "��� ������������� ����������");  DrawString( ws, 10,  145,  230, 320, 8, 3, colors[9], GetPaletteAdrByColorIndex( 23 ) );


        DrawRectangle( 0, 296, 240,320, 1, colors[3], colors[3]);
    ascii2ws(ws, "�������"); DrawString( ws, 10,  300,  230, 320, 9, 1, colors[4], GetPaletteAdrByColorIndex( 23 ) );
    ascii2ws(ws, "����");  DrawString( ws, 10,  300,  230, 320, 9, 4, colors[4], GetPaletteAdrByColorIndex( 23 ) );
break;
//------------------------------------------












      }
if(mod!=1) {adressmv = 0; CMC = 6; Adr_Cur = 0;}
if(mod!=0) {zxmainzerro = 0;}
mfree (zs);
mfree(pyfstr);
mfree (ds);
    FreeWS(ws);
}

