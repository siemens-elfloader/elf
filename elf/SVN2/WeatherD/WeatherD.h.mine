extern const unsigned int TID;

extern const char ICON_PATH[];
extern const char DATA_PATH[];

extern const unsigned int FONT_SIZE;
extern const char FONT_COLOR[];

extern const unsigned int DATA_X;
extern const unsigned int DATA_Y;

extern const unsigned int PICT_X;
extern const unsigned int PICT_Y;

extern const int SHOW_TEMP;
extern const int SHOW_PRESSURE;
extern const int SHOW_WIND;
extern const int SHOW_REWLET;
extern const int SHOW_PIC;


typedef struct
{
  char Pic[64],
       Temp[64],
       Pressure[64],
       Wind[64],
       Rewlet[64];
}WEATHER;

/*
typedef struct
{
  char yearNormBudd; //1 - norm, 2 - buddhist
  char dateFormat;
  char timeFormat; //0-24h, 1-12h
  char timeZone; //internal representation
  char isAutoTime1; 
  char isAutoTime2;
}TDateTimeSettings;

#pragma swi_number=0x822F
__swi __arm TDateTimeSettings *RamDateTimeSettings(); //cepid=msg=0

#pragma swi_number=0x230
__swi __arm int GetTimeZoneShift(TDate* dd, TTime* tt, int timeZone);
*/

GBSTMR update_tmr;
GBSTMR reconnect_tmr;

unsigned int old_gprs_state[2]={0,0};
WEATHER weath;
