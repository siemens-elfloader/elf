#include "../inc/swilib.h"
#include "string_util.h"

/////////////////////////////////////////// Разный стафф для замены спецсимволов

/* Вернуть значение параметра по имени параметра из строки вида:
 nonce="2444323444",qop="auth",charset=utf-8,algorithm=md5-sess

IN: str - строка
    req - имя требуемого параметра
    cut_quotes - обрезать ли кавычки, если параметр в кавычках
OUT: Искомое значение; нужно освободить память!
*/
char * Get_Param_Value(char * str, char * req, int cut_quotes)
{
//  char str[]="nonce=\"2444323444\",qop=\"auth\",charset=utf-8,algorithm=md5-sess";
//  char req[]="qop";
  char * n_displace = strstr(str, req);     // начало строки с именем параметра
  char * eq = n_displace + strlen(req);
  if (!(eq[0] == '=')) return NULL;
  eq += 1;
  char * zpt = strchr(n_displace, ',');
  if (!zpt) zpt= str + strlen(str);
  int len;
  char * val;
  if(cut_quotes)
  {
    len = zpt - eq - 2;
    val = new char[len + 1];
    for(int i = 0; i < len; i++)
      val[i] = *(eq + i + 1);
  }
  else
  {
    len = zpt - eq;
    val = new char[len + 1];
    for(int i = 0; i < len; i++)
      val[i] = *(eq + i);
  }
  val[len] = NULL;
  return val;
}


/*
  Преобразование буфера данных из кодировки UTF-8 в ANSI
IN:
  - tmp_out: куда положить результат. Буфер уже должен существовать
             и в нем должно быть достаточно места
  - UTF8_str: откуда брать данные для преобразования
  - size: сколько длина буфера для преобразования (UTF8_str)
  - fact - куда положить итоговый размер данных в буфере

OUT:  результирующий буфер.
*/
void* convUTF8_to_ANSI(char* tmp_out, char *UTF8_str, unsigned int size, int* fact)
{
  // Рассматривая строку UTF8 как обычную, определяем её длину
  if(!UTF8_str)return NULL;
  int st_len = size;

  // Выделяем память - на всякий случай столько же. Это предельный случай,
  // когда весь поступивший буфер - на русском языке. Реально будет, скорее всего,
  // занято меньше, посему в конце сделаем realloc
  int lastchar = 0;
  int dummy;
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
  tmp_out = (char *)realloc(tmp_out,lastchar);
  *fact = lastchar;
  return tmp_out;
}

// Преобразование в нижний регистр
char * str2lower(char *st)
{
  unsigned int len = strlen(st);
  for(int i=0;i<len;i++)
  {
    char sym = *(st+i);
    if(sym<0x80)
    {
      if(st[i]>='A' && st[i]<='Z') st[i] += ('a' - 'A');
      continue;
    }
    if(sym<0xe0)
    {
      i++;
      if(st[i] >= 0x90 && st[i]<=0xAF) st[i]+= (0xB0 - 0x90);
    }
  }
  return st;
}

////////////////////////////////////////////////////////////////////////////////
#pragma inline
int tolower(int C)
{
//  if ((C>='A' && C<='Z')) C-='A'-'a';
    if(C<0x80)
    {
      if(C>='A' && C<='Z') C += ('a' - 'A');
      return C;
    }
      if(C >= 0x90 && C<=0xAF) C+= (0xB0 - 0x90);
  return(C);
}

// Аналог strcmp, но без чувствительности к регистру
int stricmp(const char *s, const char *d)
{
  int cs;
  int ds;
  do
  {
    cs=tolower(*s++);
    ds=tolower(*d++);
    cs-=ds;
    if (cs) break;
  }
  while(ds);
  return(cs);
}

int strnicmp(const char *s1, const char *s2, size_t len)
{
  /* Yes, Virginia, it had better be unsigned */
  unsigned int c1 = 0;
  unsigned int c2 = 0;

  if (len)
  {
    do
    {
      c1 = *s1; c2 = *s2;
      s1++; s2++;
      if (!c1) break;
      if (!c2) break;
      if (c1 == c2) continue;
      c1 = tolower(c1);
      c2 = tolower(c2);
      if (c1 != c2) break;
    } while (--len);
  }
  return c1 - c2;
}

// Аналог strstr, но без чувствительности к регистру
/*
 * Find the first occurrence of find in s.
 */
char *stristr(const char *s, const char *find)
{
    char c, sc;
    size_t len;

    if ((c = tolower((unsigned char)(*find++))) != 0) {
        len = strlen(find);
        do {
            do {
                if ((sc = tolower((unsigned char)(*s++))) == 0)
                    return (NULL);
            } while (sc != c);
        } while (strnicmp(s, find, len) != 0);
        s--;
    }
    return ((char *)s);
}
////////////////////////////////////////////////////////////////////////////////

/*
// Аналог strstr, но без чувствительности к регистру
char *stristr(char *haystack, char *needle)
{
  if(!haystack || !needle)return NULL;
  char *i_haystack = malloc(strlen(haystack)+1);
  char *i_needle = malloc(strlen(needle)+1);
  strcpy(i_haystack, haystack);
  strcpy(i_needle, needle);
  str2lower(i_haystack);
  str2lower(i_needle);
  // Сравниваем уже строки в нижнем регистре и считаем смещение
  char *q = strstr(i_haystack, i_needle);
  mfree(i_haystack);
  mfree(i_needle);
  if(!q)  // Значит, нет подстроки
  {
    return NULL;
  }
  int delta = q - i_haystack;
  return haystack + delta;  // Есть подстрока, очевидно, по тому же смещению
}

// Аналог strcmp, но без чувствительности к регистру
int stricmp(char *str1, char *str2)
{
  if(!str1 || !str2)return NULL;
  char *i_str1 = malloc(strlen(str1)+1);
  char *i_str2 = malloc(strlen(str2)+1);
  strcpy(i_str1, str1);
  strcpy(i_str2, str2);
  str2lower(i_str1);
  str2lower(i_str2);
  // Сравниваем уже строки в нижнем регистре
  int res= strcmp(i_str1, i_str2);
  mfree(i_str1);
  mfree(i_str2);
  return res;
}
*/
char* str2lower_ANSI(char *st)
{
  unsigned int len = strlen(st);
  for(int i=0;i<len;i++)
  {
    char sym = *(st+i);
    char *cc = st+i;
    *cc= sym>='A' && sym<='Z' ? sym + ('a' - 'A') : sym >= 'А' && sym <= 'Я'? sym + ('а' - 'А') : sym;
  }
  return st;
}


// Строковый вариант
char* convUTF8_to_ANSI_STR(char *UTF8_str)
{
  // Рассматривая строку UTF8 как обычную, определяем её длину
  if(!UTF8_str)return NULL;
  int st_len = strlen(UTF8_str);

  // Выделяем память - на всякий случай дохера
  int lastchar = 0;
  int dummy;
  char* tmp_out = (char *)malloc(st_len+1);
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
  tmp_out = (char *)realloc(tmp_out,st_len+1);
  return tmp_out;
}



// Готовимся к отказу от ANSI вообще. Пока не используется, скоро, наверное, будет...

/* UTF-8 to UTF-16 conversion.  Surrogates are handeled properly, e.g.
 * a single 4-byte UTF-8 character is encoded into a surrogate pair.
 * On the other hand, if the UTF-8 string contains surrogate values, this
 * is considered an error and returned as such.
 *
 * The destination array must be able to hold as many Unicode-16 characters
 * as there are ASCII characters in the UTF-8 string.  This in case all UTF-8
 * characters are ASCII characters.  No more will be needed.
 *
 * Copyright (c) 2000 Morten Rolland, Screen Media
 */

int utf8_to_utf16(char *utf8, int cc, char *unicode16)
{
	int count = 0;
	unsigned char c0, c1;
	unsigned long scalar;

	while(--cc >= 0) {
		c0 = *utf8++;
		/*DPRINTF("Trying: %02x\n",c0);*/

		if ( c0 < 0x80 ) {
			/* Plain ASCII character, simple translation :-) */
			*unicode16++ = c0;
			count++;
			continue;
		}

		if ( (c0 & 0xc0) == 0x80 )
			/* Illegal; starts with 10xxxxxx */
			return -1;

		/* c0 must be 11xxxxxx if we get here => at least 2 bytes */
		scalar = c0;
		if(--cc < 0)
			return -1;
		c1 = *utf8++;
		/*DPRINTF("c1=%02x\n",c1);*/
		if ( (c1 & 0xc0) != 0x80 )
			/* Bad byte */
			return -1;
		scalar <<= 6;
		scalar |= (c1 & 0x3f);

		if ( !(c0 & 0x20) ) {
			/* Two bytes UTF-8 */
			if ( scalar < 0x80 )
				return -1;	/* Overlong encoding */
			*unicode16++ = scalar & 0x7ff;
			count++;
			continue;
		}

		/* c0 must be 111xxxxx if we get here => at least 3 bytes */
		if(--cc < 0)
			return -1;
		c1 = *utf8++;
		/*DPRINTF("c1=%02x\n",c1);*/
		if ( (c1 & 0xc0) != 0x80 )
			/* Bad byte */
			return -1;
		scalar <<= 6;
		scalar |= (c1 & 0x3f);

		if ( !(c0 & 0x10) ) {
			/*DPRINTF("####\n");*/
			/* Three bytes UTF-8 */
			if ( scalar < 0x800 )
				return -1;	/* Overlong encoding */
			if ( scalar >= 0xd800 && scalar < 0xe000 )
				return -1;	/* UTF-16 high/low halfs */
			*unicode16++ = scalar & 0xffff;
			count++;
			continue;
		}

		/* c0 must be 1111xxxx if we get here => at least 4 bytes */
		c1 = *utf8++;
		if(--cc < 0)
			return -1;
		/*DPRINTF("c1=%02x\n",c1);*/
		if ( (c1 & 0xc0) != 0x80 )
			/* Bad byte */
			return -1;
		scalar <<= 6;
		scalar |= (c1 & 0x3f);

		if ( !(c0 & 0x08) ) {
			/* Four bytes UTF-8, needs encoding as surrogates */
			if ( scalar < 0x10000 )
				return -1;	/* Overlong encoding */
			scalar -= 0x10000;
			*unicode16++ = ((scalar >> 10) & 0x3ff) + 0xd800;
			*unicode16++ = (scalar & 0x3ff) + 0xdc00;
			count += 2;
			continue;
		}

		return -1;	/* No support for more than four byte UTF-8 */
	}
	return count;
}




/*
Следующая функция взята из файла:
http://www.cs.umd.edu/projects/hpsl/chaos/ResearchAreas/ic/dist/InterComm-1.5.tar.gz/InterComm/src/ezxml/ezxml.c

В функции отключена проверка на UNICODE LE / BE, ибо в Сименсе используется только LE
*/
#define EZXML_BUFSIZE 1024
/* converts a UTF-16 string to UTF-8, returns a new string the must be freed or NULL if no conversion was needed*/
//char *ezxml_to_utf8(char **s, size_t *len) - оригинальный заголовок
char *utf16_to_utf8(char **s, size_t *len)
{
    char *u;
    size_t l = 0, sl, max = *len;
    long c, c2;
    int b, be = 0;//be = (**s == '\xFE') ? 1 : (**s == '\xFF') ? 0 : -1; - отключение проверки!!!

    if (be == -1) return NULL; /* not UTF-16*/

    u = (char *)malloc(max); zeromem(u, max);
    //    for (sl = 2; sl < *len - 1; sl += 2) {      // Второй фикс: у нас строка на 2 байта больше
        for (sl = 2; sl <= *len ; sl += 2) {
      c = (be) ? ((long)(*s)[sl] << 8) | (*s)[sl + 1] : /* big-endian*/
	((long)(*s)[sl + 1] << 8) | (*s)[sl];  /* little-endian*/
      if (c >= 0xD800 && c <= 0xDFFF && (sl += 2) < *len - 1) { /* high-half*/
	c2 = (be) ? ((long)(*s)[sl] << 8) | (*s)[sl + 1] : /* big-endian*/
	  ((long)(*s)[sl + 1] << 8) | (*s)[sl];  /* little-endian*/
            c = (((c & 0x3FF) << 10) | (c2 & 0x3FF)) + 0x10000;
        }

        while (l + 6 > max) u = (char *)realloc(u, max += EZXML_BUFSIZE);
        if (c < 0x80) u[l++] = c; /* US-ASCII subset*/
        else { /* multi-byte UTF-8 sequence*/
	  for (b = 0, c2 = c; c2; c2 /= 2) b++; /* bits in c*/
	  b = (b - 2) / 5; /* bytes in payload;*/
	  u[l++] = (0xFF << (7 - b)) | (c >> (6 * b)); /*head*/
	  while (b) u[l++] = 0x80 | ((c >> (6 * --b)) & 0x3F); /* payload*/
        }
    }

    //return *s = realloc(u, *len = l);
    *len = l;
    u = (char *)realloc(u, l+1);    // Не убиваем исходную WSHDR!
    return u;
}


/*
  Обеспечивает преобразование кривого UTF-8 Сименса в UTF-8 для Jabber
*/
char* Correct_UTF8_String(char* utf8_str)
{
  int l = strlen(utf8_str)*2;
  // ^ так нельзя делать цикл, строка на самом длиннее, чем strlen
  int j=0;
  int i=0;
  char character = *utf8_str;
  while(character!='\0')
  {
    if(character!=0x1F)
    {
      utf8_str[j]=character;
      j++;
    }
    i++;
    character = *(utf8_str+i);
  }
  utf8_str[j]='\0';
  utf8_str = (char *)realloc(utf8_str, j+1);
  return utf8_str;
}


char* ANSI2UTF8(char* ansi_str, unsigned int maxlen)
{
  WSHDR* ws_str = AllocWS(maxlen);
  ascii2ws(ws_str, ansi_str);
  char* utf8_str = (char *)malloc(maxlen*2+1);
  ws_2str(ws_str, utf8_str, maxlen*2);
  FreeWS(ws_str);
  //utf8_str = Correct_UTF8_String(utf8_str);
  return utf8_str;
}

// From NatICQ

typedef struct
{
  unsigned short u;
  char dos;
  char win;
  char koi8;
} TUNICODE2CHAR;

const TUNICODE2CHAR unicode2char[]=
{
  // CAPITAL Cyrillic letters (base)
  0x410,0x80,0xC0,0xE1, // А
  0x411,0x81,0xC1,0xE2, // Б
  0x412,0x82,0xC2,0xF7, // В
  0x413,0x83,0xC3,0xE7, // Г
  0x414,0x84,0xC4,0xE4, // Д
  0x415,0x85,0xC5,0xE5, // Е
  0x416,0x86,0xC6,0xF6, // Ж
  0x417,0x87,0xC7,0xFA, // З
  0x418,0x88,0xC8,0xE9, // И
  0x419,0x89,0xC9,0xEA, // Й
  0x41A,0x8A,0xCA,0xEB, // К
  0x41B,0x8B,0xCB,0xEC, // Л
  0x41C,0x8C,0xCC,0xED, // М
  0x41D,0x8D,0xCD,0xEE, // Н
  0x41E,0x8E,0xCE,0xEF, // О
  0x41F,0x8F,0xCF,0xF0, // П
  0x420,0x90,0xD0,0xF2, // Р
  0x421,0x91,0xD1,0xF3, // С
  0x422,0x92,0xD2,0xF4, // Т
  0x423,0x93,0xD3,0xF5, // У
  0x424,0x94,0xD4,0xE6, // Ф
  0x425,0x95,0xD5,0xE8, // Х
  0x426,0x96,0xD6,0xE3, // Ц
  0x427,0x97,0xD7,0xFE, // Ч
  0x428,0x98,0xD8,0xFB, // Ш
  0x429,0x99,0xD9,0xFD, // Щ
  0x42A,0x9A,0xDA,0xFF, // Ъ
  0x42B,0x9B,0xDB,0xF9, // Ы
  0x42C,0x9C,0xDC,0xF8, // Ь
  0x42D,0x9D,0xDD,0xFC, // Э
  0x42E,0x9E,0xDE,0xE0, // Ю
  0x42F,0x9F,0xDF,0xF1, // Я
  // CAPITAL Cyrillic letters (additional)
  0x402,'_',0x80,'_', // _ .*.*
  0x403,'_',0x81,'_', // _ .*.*
  0x409,'_',0x8A,'_', // _ .*.*
  0x40A,'_',0x8C,'_', // _ .*.*
  0x40C,'_',0x8D,'_', // _ .*.*
  0x40B,'_',0x8E,'_', // _ .*.*
  0x40F,'_',0x8F,'_', // _ .*.*
  0x40E,0xF6,0xA1,'_', // Ў ...*
  0x408,0x4A,0xA3,0x4A, // _ .*.*
  0x409,0x83,0xA5,0xBD, // _ .*..
  0x401,0xF0,0xA8,0xB3, // Ё
  0x404,0xF2,0xAA,0xB4, // Є
  0x407,0xF4,0xAF,0xB7, // Ї
  0x406,0x49,0xB2,0xB6, // _ .*..
  0x405,0x53,0xBD,0x53, // _ .*.*
  // SMALL Cyrillic letters (base)
  0x430,0xA0,0xE0,0xC1, // а
  0x431,0xA1,0xE1,0xC2, // б
  0x432,0xA2,0xE2,0xD7, // в
  0x433,0xA3,0xE3,0xC7, // г
  0x434,0xA4,0xE4,0xC4, // д
  0x435,0xA5,0xE5,0xC5, // е
  0x436,0xA6,0xE6,0xD6, // ж
  0x437,0xA7,0xE7,0xDA, // з
  0x438,0xA8,0xE8,0xC9, // и
  0x439,0xA9,0xE9,0xCA, // й
  0x43A,0xAA,0xEA,0xCB, // к
  0x43B,0xAB,0xEB,0xCC, // л
  0x43C,0xAC,0xEC,0xCD, // м
  0x43D,0xAD,0xED,0xCE, // н
  0x43E,0xAE,0xEE,0xCF, // о
  0x43F,0xAF,0xEF,0xD0, // п
  0x440,0xE0,0xF0,0xD2, // р
  0x441,0xE1,0xF1,0xD3, // с
  0x442,0xE2,0xF2,0xD4, // т
  0x443,0xE3,0xF3,0xD5, // у
  0x444,0xE4,0xF4,0xC6, // ф
  0x445,0xE5,0xF5,0xC8, // х
  0x446,0xE6,0xF6,0xC3, // ц
  0x447,0xE7,0xF7,0xDE, // ч
  0x448,0xE8,0xF8,0xDB, // ш
  0x449,0xE9,0xF9,0xDD, // щ
  0x44A,0xEA,0xFA,0xDF, // ъ
  0x44B,0xEB,0xFB,0xD9, // ы
  0x44C,0xEC,0xFC,0xD8, // ь
  0x44D,0xED,0xFD,0xDC, // э
  0x44E,0xEE,0xFE,0xC0, // ю
  0x44F,0xEF,0xFF,0xD1, // я
  // SMALL Cyrillic letters (additional)
  0x452,'_',0x90,'_', // _ .*.*
  0x453,'_',0x83,'_', // _ .*.*
  0x459,'_',0x9A,'_', // _ .*.*
  0x45A,'_',0x9C,'_', // _ .*.*
  0x45C,'_',0x9D,'_', // _ .*.*
  0x45B,'_',0x9E,'_', // _ .*.*
  0x45F,'_',0x9F,'_', // _ .*.*
  0x45E,0xF7,0xA2,'_', // ў ...*
  0x458,0x6A,0xBC,0x6A, // _ .*.*
  0x491,0xA3,0xB4,0xAD, // _ .*..
  0x451,0xF1,0xB8,0xA3, // ё
  0x454,0xF3,0xBA,0xA4, // є
  0x457,0xF5,0xBF,0xA7, // ї
  0x456,0x69,0xB3,0xA6, // _ .*..
  0x455,0x73,0xBE,0x73, // _ .*.*
  0x0A0,'_',0xA0,0x20, // space .*..
  0x0A4,'_',0xA4,0xFD, // ¤   .*..
  0x0A6,'_',0xA6,'_', // ¦   .*.*
  0x0B0,0xF8,0xB0,0x9C, // °
  0x0B7,0xFA,0xB7,0x9E, // ·
  // 0x2022,,0x95,0x95, //    .*..
  // 0x2116,0xFC,0xB9,0x23, // №   ...*
  // 0x2219,,0xF9,0x9E, //    .*..
  // 0x221A,0xFB,,0x96, // v   ..*.
  // 0x25A0,0xFE,,0x94, // ¦
  0x0000,0,0,0
};

const char wintranslation[128]=
{
  0x5F,0x5F,0x27,0x5F,0x22,0x3A,0xC5,0xD8,0x5F,0x25,0x5F,0x3C,0x5F,0x5F,0x5F,0x5F,
  0x5F,0x27,0x27,0x22,0x22,0x07,0x2D,0x2D,0x5F,0x54,0x5F,0x3E,0x5F,0x5F,0x5F,0x5F,
  0xFF,0xF6,0xF7,0x5F,0xFD,0x83,0xB3,0x15,0xF0,0x63,0xF2,0x3C,0xBF,0x2D,0x52,0xF4,
  0xF8,0x2B,'I' ,'i' ,0xA3,0xE7,0x14,0xFA,0xF1,0xFC,0xF3,0x3E,0x5F,0x5F,0x5F,0xF5,
  0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
  0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
  0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
  0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF
};
const unsigned short dos2unicode[128]=
{
  0x0410,0x0411,0x0412,0x0413,0x0414,0x0415,0x0416,0x0417,
  0x0418,0x0419,0x041A,0x041B,0x041C,0x041D,0x041E,0x041F,
  0x0420,0x0421,0x0422,0x0423,0x0424,0x0425,0x0426,0x0427,
  0x0428,0x0429,0x042A,0x042B,0x042C,0x042D,0x042E,0x042F,
  0x0430,0x0431,0x0432,0x0433,0x0434,0x0435,0x0436,0x0437,
  0x0438,0x0439,0x043A,0x043B,0x043C,0x043D,0x043E,0x043F,
  0x002D,0x002D,0x002D,0x00A6,0x002B,0x00A6,0x00A6,0x00AC,
  0x00AC,0x00A6,0x00A6,0x00AC,0x002D,0x002D,0x002D,0x00AC,
  0x004C,0x002B,0x0054,0x002B,0x002D,0x002B,0x00A6,0x00A6,
  0x004C,0x0433,0x00A6,0x0054,0x00A6,0x003D,0x002B,0x00A6,
  0x00A6,0x0054,0x0054,0x004C,0x004C,0x002D,0x0433,0x002B,
  0x002B,0x002D,0x002D,0x002D,0x002D,0x00A6,0x00A6,0x002D,
  0x0440,0x0441,0x0442,0x0443,0x0444,0x0445,0x0446,0x0447,
  0x0448,0x0449,0x044A,0x044B,0x044C,0x044D,0x044E,0x044F,
  0x0401,0x0451,0x0404,0x0454,0x0407,0x0457,0x040E,0x045E,
  0x00B0,0x2022,0x00B7,0x0076,0x2116,0x00A4,0x00A6,0x00A0
};

unsigned int char8to16(int c)
{
  if (c>=128)
  {
    //Win->Dos
    c=wintranslation[c-128];
    if (c<128) return(c);
    return(dos2unicode[c-128]);
  }
  return(c);
}

unsigned int char16to8(unsigned int c)
{
  const TUNICODE2CHAR *p=unicode2char;
  unsigned int i;
  if (c<128) return(c);
  while((i=p->u))
  {
    if (c==i)
    {
      return(p->win);
    }
    p++;
  }
  c&=0xFF;
  if (c<32) return(' ');
  return(c);
}

void ascii2ws(WSHDR * ws, const char * s)
{
  char c;
  CutWSTR(ws,0);
  while((c=*s++))
  {
    wsAppendChar(ws,char8to16(c));
  }
}

void utf82win(char*d,const char *s)
{
  for (; *s; s+=2)
  {
    unsigned char ub = *s, lb = *(s+1);
    if (ub == 208)
      if (lb != 0x81)
        {*d = lb + 48; d++;}
      else
        {*d = 'Ё'; d++;}

    if (ub == 209)
      if (lb != 0x91)
        {*d = lb + 112; d++;}
      else
        {*d = 'ё'; d++;}

    if ((ub != 208) && (ub != 209) && (lb != 91) && (lb != 81))
    {
      *d = ub;
      d++;
      s--;
    }
  }
  *d = 0;
}

long GetIDLETime(TTime intime, TDate indate)
{
 TTime endt;
 TDate endd;
// TDate endd, resd;
 signed int res=0, rmin=0;
 long resul=0;
 GetDateTime(&endd, &endt);
 res = endt.sec - intime.sec;
 if (res < 0)
 {
   res = 60 + res;
   rmin = 1;
 }
 resul = res;
 res = endt.min - intime.min - rmin;
 rmin = 0;
 if (res < 0)
 {
   res = 60 + res;
   rmin = 1;
 }
 resul = resul + res*60;
 res = endt.hour - intime.hour - rmin;
 rmin = 0;
 if (res < 0)
 {
   res = 24 + res;
   rmin = 1;
 }
 resul = resul + res*3600;
 res = endd.day - indate.day - rmin;
 rmin = 0;
 if (res < 0)
 {
   res = 31 + res;
//   rmin=1;
 }
 resul = resul + res*86400;
/*
 res = end.mounth - indate.mounth - rmin;
 rmin = 0;
 if (res < 0 )
 {
   res = 12 + res;
 }
 res = resul + res*2678400; mnogovato trowki
   */
 return(resul);
}

char * utf82filename(char *str)
{
  int len = strlen(str)+16;
  WSHDR *ws = AllocWS(len);
  char * res = new char[len];
  utf8_2ws(ws, str, len);
  ws_2str(ws, res, len);
  FreeWS(ws);
  return res;
}

char * filename2utf8(char * str)
{
  int len = strlen(str) + 16;
  int new_len = 0;
  WSHDR * ws = AllocWS(len);
  char * tmp = new char[len];
  str_2ws(ws, tmp, len);
  ws_2utf8(ws, tmp, &new_len, len);
  char * res = new char[new_len + 1];
  strcpy(res, tmp);
  delete tmp;
  FreeWS(ws);
  return res;
}

// Удаление расширения из имени файла
void del_ext(char * source)
{
  while(*source)source++;
  while(*source!='.')source--;
  *source=0;
};

char * get_fname_from_path(char * path)
{
  char * fname = NULL;
  char * tmp_fname = NULL;
  if(tmp_fname = strrchr(path, '/'))
  {
    fname = new char[strlen(tmp_fname)+1];
    strcpy(fname, tmp_fname + 1);
  }
  else
  {
    fname = new char[strlen(path)+1];
    strcpy(fname, path);
  }
  return fname;
}

const char badchars[] = {'?', '*', '"', ':', '<', '>', '/', '\\', '|', '\n', '\r'};

void remove_bad_chars(char *s)
{
  int c;
  while((c=*s))
  {
    for (int i=0; i<(sizeof(badchars)/sizeof(char)); i++)
    {
      if (c==badchars[i])
      {
        *s='_';
        break;
      }    
    }
    s++;
  }
}
