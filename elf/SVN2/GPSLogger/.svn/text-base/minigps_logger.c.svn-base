#include "../inc/swilib.h"
#include "minigps_logger.h"
// $Revision$
// $Revision

// Путь к БД
extern const          char MGPS_DB[128];
extern const          char LOGFILE[128];
extern const unsigned int CACHE_SIZE;
extern const          int LOG_UNKNOWN_CELLS;
extern const          int DISP_UNKNOWN_CELLS;
const char Unk_t[]="<no name>";

#define CACHE_SIZE_MAX 10

// Строковый вариант конверсии UTF-8 -> ANSI (Win-2151)
// Взято из SieJC
char* convUTF8_to_ANSI_STR(char *UTF8_str)
{
  // Рассматривая строку UTF8 как обычную, определяем её длину
  if(!UTF8_str)return NULL;
  int st_len = strlen(UTF8_str);

  // Выделяем память - на всякий случай дохера
  int lastchar = 0;
  int dummy;
  char* tmp_out = malloc(st_len+1);
  zeromem(tmp_out,st_len+1);
  char chr, chr2, chr3;
  for(int i=0;i<st_len;i++)
  {
  chr = (*(UTF8_str+i));

	if (chr<0x80)
        {
          *(tmp_out+lastchar)=chr;
          lastchar++;
          goto L_END_CYCLE;
        }
	if (chr<0xc0)
        {
          ShowMSG(1,(int)"Bad UTF-8 Encoding encountered (chr<0xC0)");
          mfree(tmp_out);
          return NULL;
        }
	
        chr2 = *(UTF8_str+i+1);

        if (chr2<0x80)
        {
          ShowMSG(1,(int)"Bad UTF-8 Encoding encountered (chr2<0x80)");
          mfree(tmp_out);
          return NULL;
        }
	
	if (chr<0xe0) {
	    // cx, dx
	    char test1 = (chr & 0x1f)<<6;
            char test2 = chr2 & 0x3f;
            *(tmp_out+lastchar)= test1 | test2 + 127 + 0x31;
            i++;
            lastchar++;
            goto L_END_CYCLE;
	}
	if (chr<0xf0) {
	    // cx, dx
	    chr3= *(UTF8_str+i+2);

	    if (chr3<0x80)
            {
              ShowMSG(1,(int)"Bad UTF-8 Encoding encountered");
              mfree(tmp_out);
              return NULL;
            }
	    else
            {
              *(tmp_out+lastchar) =  ((chr & 0x0f)<<12) | ((chr2 &0x3f) <<6) | (chr3 &0x3f);
              i=i+2;
            }
	}

  L_END_CYCLE:
    dummy++;
  }
  st_len = strlen(tmp_out);
  tmp_out = realloc(tmp_out,st_len+1);
  return tmp_out;
}

// Пишет в лог-файл соту с параметрами, переданными в процедуру.
// Запись ведётся в конец файла, формат CSV. 
// Кодировка файла - Windows-1251
void WriteLog(unsigned short ci, unsigned short lac, char *name)
{
  TTime now_time;
  TDate now_date;
  unsigned int errcode;
  char datestr[200];
  
  GetDateTime(&now_date,&now_time);  
  sprintf(datestr, "%02d.%02d; %02d:%02d; %05d; %05d; %s;\r\n",now_date.day,now_date.month,now_time.hour,now_time.min, lac, ci, name);
  char *ansi_text = convUTF8_to_ANSI_STR(datestr);
  volatile int hFile = -1;
  volatile int flags =A_WriteOnly+A_BIN;
  
  hFile = fopen(LOGFILE,flags,P_WRITE,&errcode);
  if(hFile==-1)
  {
    flags +=A_Create;
    hFile = fopen(LOGFILE,flags,P_WRITE,&errcode);
    if(hFile==-1)return;
    char zag[]="Date; Time; LAC; CID; Name;\r\n";
    fwrite(hFile, &zag, strlen(zag), &errcode);
  }
  else lseek(hFile, 0, S_END, &errcode, &errcode);
  fwrite(hFile, ansi_text, strlen(ansi_text), &errcode);
  fclose(hFile, &errcode);
  mfree(ansi_text);
}


//// Организация кеша данных о сети ////////////////////////////////////////////

// Структура записи кеша
typedef struct
{
  unsigned short ci;
  unsigned short lac;
  char *name;
}RAMNET_CACHE_ENTRY;

// Сам кеш и указатель на последний элемент
RAMNET_CACHE_ENTRY Ramnet_Cache[CACHE_SIZE_MAX];
char Cache_p = 0;

// Инициализировать кеш
void InitRamNetCache()
{
  zeromem(Ramnet_Cache, sizeof(RAMNET_CACHE_ENTRY)*CACHE_SIZE);
}

// Убить кеш
void KillRamNetCache()
{
  for(int i=0;i<CACHE_SIZE;i++)
  {
    if(Ramnet_Cache[i].name)mfree(Ramnet_Cache[i].name);
  }
}

// Положить запись в кеш
void Put_In_Cache(unsigned short ci, unsigned short lac, char *name)
{
  Ramnet_Cache[Cache_p].ci = ci;
  Ramnet_Cache[Cache_p].lac = lac;
  if(Ramnet_Cache[Cache_p].name)mfree(Ramnet_Cache[Cache_p].name);
  Ramnet_Cache[Cache_p].name = malloc(strlen(name)+1);
  strcpy(Ramnet_Cache[Cache_p].name, name);
/*
  char q[40];
  sprintf(q,"->cache, N=%d",Cache_p);
  ShowMSG(1,(int)q);
*/  
  WriteLog(ci, lac, name);
    
  Cache_p++;
  if(Cache_p>=CACHE_SIZE)Cache_p=0;
}

// Искать запись в кеше
char *Get_From_Cache(unsigned short ci, unsigned short lac)
{
  for(int i=0;i<CACHE_SIZE;i++)
  {
    if(Ramnet_Cache[i].ci==ci && Ramnet_Cache[i].lac==lac) return Ramnet_Cache[i].name;
  } 
  return NULL;
}

// Удалить одну запись из кеша
void Del_From_Cache(unsigned short ci, unsigned short lac)
{
  for(int i=0;i<CACHE_SIZE;i++)
  {
    if(Ramnet_Cache[i].ci==ci && Ramnet_Cache[i].lac==lac)
    {
      if(Ramnet_Cache[i].name)mfree(Ramnet_Cache[i].name);
      Ramnet_Cache[i].ci = Ramnet_Cache[i].lac =0;
      Ramnet_Cache[i].name= NULL;     
      return;
    }
  } 
}
////////////////////////////////////////////////////////////////////////////////

// Получить текущее местоположение из miniGPS-базы
// Строка выделяется функцией, необходимо освобождение после юзания
// в action возвращается действие для выполнения
// Строка возвращается в кодировке UTF-8
char *Get_Current_Location(char *action)
{
  RAMNET Res;
  char filename[128];
  unsigned int errcode;
  int hFile;
  *action = 0;  // инициализация нулём - никакого действия по дефолту
  Res = *RamNet();
  
  // Пробуем зохавать соту из кеша, чтобы не обращаться к диску
  char *_res, *res;
  _res = Get_From_Cache(Res.ci,Res.lac);
  if(_res)
  {
    res = malloc(strlen(_res)+1);
    strcpy(res, _res);
    return res;
  }

  // Не найдено в кеше, открываем файл и получаем имя и действие  
  snprintf(filename,127,"%s\\%u\\%u-%u.tmo",&MGPS_DB,Res.lac,Res.ci,Res.lac);  
  
  // Открываем файло
  hFile = fopen(filename,A_ReadOnly+A_BIN,P_READ,&errcode);
  if(hFile==-1)
  {
    if(LOG_UNKNOWN_CELLS)WriteLog(Res.ci,Res.lac,(char*)&Unk_t); 
    if(DISP_UNKNOWN_CELLS)
    {
      res = malloc(20);
      sprintf(res, "%d-%d", Res.ci,Res.lac);
      Put_In_Cache(Res.ci,Res.lac, res);// Пишем псевдоимя в лог
      return res;
    }
    return NULL;
  }
  // Файло открыто, читаем файло
  char *buf;
  char *str;
  int result_len;
  
  buf = malloc(256);
  fread(hFile, buf, 256, &errcode);
  fclose(hFile, &errcode);
  
  short str_len = (short)*buf - 2;
  WSHDR *ws = AllocWS(str_len);

  *action = *(buf+2);

  memcpy(ws->wsbody+1, buf+2+2+2, (str_len)*2); // [0] = длина, + 2 символа в UTF-16 нам не нужны
  ws->wsbody[0] = str_len;
  str = malloc(str_len*2+1);
  ws_2utf8(ws, str, &result_len, (str_len)*2+1);
  FreeWS(ws);
  str = realloc(str, result_len+1);
  Put_In_Cache(Res.ci,Res.lac, str);
  return str;
}

//EOL,EOF
