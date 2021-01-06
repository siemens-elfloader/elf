#ifndef _STRING_UTIL_H_
  #define _STRING_UTIL_H_

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
void* convUTF8_to_ANSI(char* tmp_out, char *UTF8_str, unsigned int size, int* fact);

char* convUTF8_to_ANSI_STR(char *UTF8_str);


void ascii2ws(WSHDR * ws, const char * s);

unsigned int char8to16(int c);

// Преобразование в нижний регистр
char* str2lower(char *st);

// Функция из интернета. UTF16->UTF8
char *utf16_to_utf8(char **s, size_t *len);

// Функция из интернета. UTF8->UTF16
int utf8_to_utf16(char *utf8, int cc, char *unicode16);

// UTF8 для джаббера
char* Correct_UTF8_String(char* utf8_jid);

// А это вообще чтобы всем было хорошо (с) Чеботарёв А.А.
char* ANSI2UTF8(char* ansi_str, unsigned int maxlen);

// Получить значение по параметру (см. описание в теле файла)
char * Get_Param_Value(char * str, char * req, int cut_quotes);

// Аналог strstr, но без чувствительности к регистру
//char *stristr(char *haystack, char *needle);
char *stristr(const char *s, const char *find);

// Аналог strcmp, но без чувствительности к регистру
int stricmp(const char *s, const char *d);

unsigned int char16to8(unsigned int c);
void utf82win(char*d,const char *s);

//разница времени
long GetIDLETime(TTime intime, TDate indate);

char * utf82filename(char *str);
char * filename2utf8(char *str);

void del_ext(char *source);
char * get_fname_from_path(char * path);
void remove_bad_chars(char *s);

#endif
