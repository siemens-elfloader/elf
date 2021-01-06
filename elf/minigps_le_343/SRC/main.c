#include "swilib.h"
#include "conf_loader.h"
#include "utils.h"

#define idlegui_id (((int *)data)[DISPLACE_OF_IDLEGUI_ID / 4])
CSM_DESC icsmd;
int (*old_icsm_onMessage)(CSM_RAM*, GBS_MSG*);

extern const int cfgx;
extern const int cfgy;
extern const int cfgcolor;
extern const int cfgcvcolor;
extern const int cfgfont;
extern const int cfgtext_attribute;
extern const int cfgupdate_time;
extern const int cfgupdate_conf;
extern const int cfgupdate_screen;
extern const char gps_dir[128];
extern const int wrlog;
extern const int wrloclog;

char filename[512];     // глобальная переменная для имени файла
char corr_name[512];    // отображаемое на гл. экране
char pcorr_name[512];
int len_;               // длина отображаемого на гл. экране
int plen_;
int oldlac;             //старые показатели lac и ci
int oldci;              //
int oldlac1;            //старые показатели lac и ci
int oldcid;             //
int lac = 0;
int ci = 0;
int count;
int oldwidth = 0;
char keycode[] = "460";
char str_zero[] = "\0";
char str_s[] = "%s";
char str_ss[] = "%s%s";
char tmpcode[64];
volatile int maindb = -1;
int records_count = 0;
int lastdatafromdb = 0;
int poldlac = 0;
int poldci = 0;
int ccnt = 0;

char *pen;
char *brush;
WSHDR *cached_ws_screen;


GBSTMR tmr_update;      // Update GPS Timer
GBSTMR tmr_redraw;      // Update SCREEN Timer

short unicode[256] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
                      18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
                      33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,
                      50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,
                      68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,
                      86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,
                      103,104,105,106,107,108,109,110,111,112,113,114,115,116,
                      117,118,119,120,121,122,123,124,125,126,127,1026,1027,8218,
                      1107,8222,8230,8224,8225,8364,8240,1033,8249,1034,1036,1035,
                      1039,1106,8216,8217,8220,8221,8226,8211,8212,152,8482,1113,8250,
                      1114,1116,1115,1119,160,1038,1118,1032,164,1168,166,167,1025,169,
                      1028,171,172,173,174,1031,176,177,1030,1110,1169,181,182,183,1105,
                      8470,1108,187,1112,1029,1109,1111,1040,1041,1042,1043,1044,1045,1046,
                      1047,1048,1049,1050,1051,1052,1053,1054,1055,1056,1057,1058,1059,1060,
                      1061,1062,1063,1064,1065,1066,1067,1068,1069,1070,1071,1072,1073,1074,
                      1075,1076,1077,1078,1079,1080,1081,1082,1083,1084,1085,1086,1087,1088,
                      1089,1090,1091,1092,1093,1094,1095,1096,1097,1098,1099,1100,1101,1102,1103};

void readcilac(int record, unsigned short * pci, unsigned short * plac, int * datapos)
{
  dlseek(maindb, 4 + record * 8, 0);
  read(maindb, plac, 2);
  read(maindb, pci, 2);
  read(maindb, datapos, 4);
}

unsigned char * getcilacdata(unsigned short pci, unsigned short plac)
{
  int b1 = 0;
  int b2 = records_count - 1;
  int b3 = b2 / 2;
  unsigned short ci1 = 0;
  unsigned short lac1 = 0;
  int datapos1 = 0;

  while (b2 - b1 > 5) //Binary search
  {
    readcilac(b3, &ci1, &lac1, &datapos1);
    if ((lac1 > plac) || (lac1 == plac && ci1 > pci))
    {
      b2 = b3;
    }
    else if ((lac1 < plac) || (lac1 == plac && ci1 < pci))
    {
      b1 = b3;
    }
    else //=
    {
      goto lblRead;
    }
    b3 = b1 + ((b2 - b1) / 2);
  }
  
  for (int i = b1; i <= b2; i++)
  {
    readcilac(i, &ci1, &lac1, &datapos1);
    if (ci1 == pci && lac1 == plac)
    {
      goto lblRead;
    }
  }
  readcilac(794, &ci1, &lac1, &datapos1);
/*  showerror("notfound b1", b1);
  showerror("notfound b2", b2);*/
  return 0;
lblRead:;
  short size = 0;
  unsigned char *data = 0;
  dlseek(maindb, datapos1, 0);
  read(maindb, &size, 2);
  data = (unsigned char *)malloc(size + 1);
  read(maindb, data, size);
  data[size] = 0;
  return data;
}

int getnamefromdb(unsigned short pci, unsigned short plac)
{
  if (maindb == -1)
  {
    return 0;
  }
  
  if (poldlac == plac && poldci == pci && poldlac != 0)
  {
    //sprintf(corr_name, str_s, pcorr_name);
    strcpy(corr_name, pcorr_name);
    len_ = plen_;
    return 1;
  }
  
  unsigned char *data = getcilacdata(pci, plac);
  if (data == 0)
  {
    return 0;
  }
  
  zeromem(corr_name, 512);
  WSHDR *ws1 = AllocWS(strlen((char *)data) + 2);
  for (int i = 0; i < strlen((char *)data); i++)
  {
    ws1->wsbody[i + 1] = unicode[data[i]];
  }
  ws1->wsbody[0] = strlen((char *)data);
  CutWSTR(ws1, strlen((char *)data));
  len_ = strlen((char *)data) * 2 + 2;
  ws_2str(ws1, corr_name, len_);
  
  FreeWS(ws1);
  free(data);
  
  //sprintf(pcorr_name, str_s, corr_name);
  strcpy(pcorr_name, corr_name);
  poldlac = plac;
  poldci = pci;
  plen_ = len_;
  return 1;
}

void GetNetParams()
{
  RAMNET Result;
  RAMNET *tmpResult;
  zeromem(&Result, sizeof(RAMNET));
  tmpResult = RamNet();
  Result = *tmpResult;
  
  lac = Result.lac;
  ci = Result.ci;
}

void GetFileName(int get_net_params)
{
  if (get_net_params)
  {
    GetNetParams();
  }
  sprintf(filename, "%s\\%u\\%u-%u.tmo", gps_dir, lac, ci, lac);  
}

void writetolog()
{
  unsigned int errcode;
  volatile int hFile = -1;
  GetNetParams(); 
  
  char *logfile = malloc(128);
  sprintf(logfile, "%s\\logfile.txt", gps_dir);
  hFile = fopen(logfile, A_WriteOnly + A_Append + A_Create, P_WRITE, &errcode);
  WSHDR *ws5 = AllocWS(256);
  
  TDate date;
  TTime time;
  GetDateTime(&date, &time);
  
  if (wrloclog)
  {
    void load_name();
    load_name();
  }
  
  char data[128];
  if (!(ci==0 || lac==0))
  {
    sprintf(data, "[%02d%02d%04d-%d:%02d] Changed: [Cell ID:%u, LAC:%u] %s\r\n", 
            date.day, date.month, date.year, time.hour, time.min, ci, lac, (wrloclog ? corr_name : ""));
  }
  else
  {
    sprintf(data, "[%02d%02d%04d-%d:%02d] Search\r\n", 
            date.day, date.month, date.year, time.hour, time.min);
  }
  str_2ws(ws5, data, 1000);
  unsigned int len = wstrlen(ws5);//узнаем длину записанного
  fwrite(hFile, data, len, &errcode);
  FreeWS(ws5);
  fclose(hFile,&errcode);
  //Free
  mfree(logfile);
}

void LoadConfig()
{
  InitConfig();
  
  pen   = GetPaletteAdrByColorIndex(cfgcolor);
  brush = GetPaletteAdrByColorIndex(cfgcvcolor);
}

int MyIDLECSM_onMessage(CSM_RAM* data, GBS_MSG* msg)
{
  int csm_result;
  
  if(msg->msg == MSG_RECONFIGURE_REQ)
  {
    LoadConfig();
  }
  
  csm_result = old_icsm_onMessage(data, msg);
  
  void refresh_screen(int reload_data);
  refresh_screen(1);

  return(csm_result);
}

int check_keycode()
{
  if (strlen(tmpcode) > 0)
  {
    if (strlen(tmpcode) <= strlen(keycode))
    {
      for (int i =0; i < strlen(tmpcode); i++)
      {
        if (tmpcode[i] != keycode[i])
        {
          sprintf(tmpcode, str_s, str_zero);
          return 0;
        }
      }
      if (strlen(tmpcode) == strlen(keycode))
      {
        return 1;
      }
    }
    else
    {
      sprintf(tmpcode, str_s, str_zero);
    }
  }
  return 0;
}

int my_keyhook(int submsg, int msg)
{
  void *data;
  data = FindCSMbyID(CSM_root()->idle_id);
  if (IsGuiOnTop(idlegui_id))
  {    
    GUI *igui = GetTopGUI();
    if (igui)
    {
      void* idata = GetDataOfItemByID(igui, 2);
      if (idata)
      {
        if ((msg==KEY_DOWN)||(msg==KEY_UP)||(msg==LONG_PRESS))
        {
          if ((msg==KEY_DOWN)||(msg==LONG_PRESS))
          {
            switch(submsg)
            {
            case '0':
              sprintf(tmpcode, str_ss, tmpcode, "0");
              break;
            case '4':
              sprintf(tmpcode, str_ss, tmpcode, "4");
              break;
            case '6':
              sprintf(tmpcode, str_ss, tmpcode, "6");
              break;
            default:
              tmpcode[0] = 0;
              return 0;
            }
            if (check_keycode())
            {
              GetFileName(0);
              if (lastdatafromdb)
              {
                void Savenew(int usecorr);
                Savenew(1);
              }
              WSHDR *outfilews;
              outfilews=AllocWS(strlen(filename) * 2 + 4);
              str_2ws(outfilews,filename,strlen(filename));
              ExecuteFile(outfilews,0,0);
              FreeWS(outfilews);
              sprintf(tmpcode, str_s, str_zero);
              return 2;
            }
          }
        }
      }
    }
  }
  return 0;
}


void refresh_screen(int reload_data)
{
  void *data;
  data = FindCSMbyID(CSM_root()->idle_id);
  if (IsGuiOnTop(idlegui_id))
  {    
    GUI *igui = GetTopGUI();
    if (igui)
    {
#ifdef ELKA
      void *canvasdata = BuildCanvas();
      {
#else
      void* idata = GetDataOfItemByID(igui, 2);
      if (idata)
      {
#endif
        void load_name();
        if (reload_data)
        {
          load_name();
        }
#ifdef ELKA
#else        
        void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
#endif
        str_2ws(cached_ws_screen, corr_name, len_);
        
        int textwidth = Get_WS_width(cached_ws_screen, cfgfont) + 2; //(wstrlen(ws))*6;
        int textheight = GetFontYSIZE(cfgfont) + 1; //12;
        
        DrawCanvas(canvasdata, cfgx, cfgy, cfgx + (textwidth > oldwidth ? textwidth : oldwidth), cfgy + textheight, 1);          
        DrawString(cached_ws_screen, cfgx, cfgy, cfgx + textwidth, cfgy + textheight, cfgfont, cfgtext_attribute, pen, brush);
        
        oldwidth = textwidth;
      }  
    }
  }
}

void Savenew(int usecorr)
{
  unsigned int errcode;
  volatile int hFile = -1;
  GetFileName(1);
  hFile = fopen(filename, A_WriteOnly + A_Create, P_WRITE, &errcode);
  if(hFile == -1)
  {
    char dir[256];
    sprintf(dir, "%s\\%u", gps_dir, lac);
    mkdir(dir, &errcode);
    
    hFile = fopen(filename, A_WriteOnly + A_Create, P_WRITE, &errcode);
    if (hFile == -1) //Still error?
    {
      //Unreasonable continue trying to open file,
      //we can freeze system, so we are exiting now
      return;
    }
    else
    {
      goto lblFileOK;
    }
  }
  else
  {
    lblFileOK:;
    WSHDR *ws0 = AllocWS(512);
    if (usecorr)
    {
      str_2ws(ws0,corr_name,strlen(corr_name));
      ws0->wsbody[0] += 2;
      for (int i = strlen(corr_name) - 1; i >= 0 ; i--)
      {
           ws0->wsbody[i + 3] = ws0->wsbody[i + 1];
      }
      ws0->wsbody[1] = unicode['0'];
      ws0->wsbody[2] = unicode[' '];
    }
    else
    {
      wsprintf(ws0, "0 %u-%u", ci, lac);
    }

    unsigned int len = wstrlen(ws0);
    fwrite(hFile, ws0->wsbody, len * 2 + 2, &errcode);
    unsigned int crc = (int)ws0->wsbody[0];
    
    for(int i = 1; i < (len + 1); i++)
    {
      crc = crc ^ ws0->wsbody[i];
    }
    fwrite(hFile, &crc, 2, &errcode);
    FreeWS(ws0);
  }
  fclose(hFile, &errcode);
}

void load_name()
{
  unsigned int errcode;
  volatile int hFile = -1;
  GetNetParams();
  
  lastdatafromdb = 0;
  if (lac == 0 && ci == 0)
  {
    zeromem(corr_name, 512);
    sprintf(corr_name, "searching...");
  }
  GetFileName(0);
  hFile = fopen(filename, A_ReadWrite, P_READ + P_WRITE, &errcode);
  if (hFile == -1) //If there are no file
  {
    if (getnamefromdb(ci, lac)) //Try to get data from DB
    {
      lastdatafromdb = 1;
      return;
    }
    Savenew(0);    //Creating New file
    hFile = fopen(filename, A_ReadWrite, P_READ + P_WRITE, &errcode);
    if (hFile == -1) //Still no file?
    {
      //Unreasonable continue trying to open file,
      //we can freeze system, so we are exiting now
      return;
    }
    else
    {
      goto lblFileOK;
    }
  }
  else
  {
  lblFileOK:
    zeromem(corr_name, 512);
    
    int str_len = 0;
    fread(hFile, &str_len, 2, &errcode);
    WSHDR *ws1 = AllocWS(str_len);
    lseek(hFile, 4, 0, &errcode, &errcode);
    fread(hFile, ws1->wsbody, (str_len) * 2, &errcode);
    CutWSTR(ws1, str_len-2);
    len_ = (str_len) * 2;
    ws_2str(ws1, corr_name, len_);
    FreeWS(ws1);
  }
  fclose(hFile, &errcode);
}

void check()
{
  GetNetParams(); 
  if (ci != oldci || lac != oldlac)
  { 
    oldlac = lac;
    oldci = ci;
    if (wrlog)
    {
      writetolog();
    }
  }
  if (cfgupdate_time)
  {
    GBS_StartTimerProc(&tmr_update, 262 * cfgupdate_time, check);
  }
}

void update_screen()
{
  refresh_screen(1);
  if (cfgupdate_screen)
  {
    GBS_StartTimerProc(&tmr_redraw, 262 * cfgupdate_screen, update_screen);
  }
}

int main()
{
  unsigned int err;
  sprintf(tmpcode, str_s, str_zero);
  
  LoadConfig();
  cached_ws_screen = AllocWS(512);
    
  if (wrlog)
  {
    //Killing old log file
    char *logfile0 = malloc(128);
    sprintf(logfile0, "%s\\logfile.txt", gps_dir);
    unlink(logfile0, &err);
    mfree(logfile0);
  }
  
  //Creating dir if it doesn't exist
  if(!isdir(gps_dir, &err))
  {
    mkdir(gps_dir, &err);
  }
  
  char dbfn[512];
  sprintf(dbfn, "%s\\tmodb.db", gps_dir);  
  maindb = open(dbfn, A_ReadOnly + A_BIN, P_READ);
  if (maindb != -1)
  {
    read(maindb, &records_count, 4);
  }
  
  CSM_RAM *icsm = FindCSMbyID(CSM_root()->idle_id); //засовываем на главный экран 
  memcpy(&icsmd, icsm->constr, sizeof(icsmd));
  old_icsm_onMessage = icsmd.onMessage;
  icsmd.onMessage = MyIDLECSM_onMessage;
  icsm->constr = &icsmd;
  
  
  if ((wrlog) || (cfgupdate_time))
  {
    check();
  }
  if (cfgupdate_screen)
  {
    load_name();
    update_screen();
  }
  
  AddKeybMsgHook((void *)my_keyhook);
  
  return 0;
}
