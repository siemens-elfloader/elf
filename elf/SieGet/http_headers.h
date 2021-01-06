#ifndef _HTTP_HEADERS_H_
#define _HTTP_HEADERS_H_

#define N_RESP_HEADERS 27

#define H_Accept_Ranges 0
#define H_Age 1
#define H_Cache_Control 2
#define H_Connection 3
#define H_Content_Encoding 4
#define H_Content_Language 5
#define H_Content_Length 6
#define H_Content_Location 7
#define H_Content_MD5 8
#define H_Content_Range 9
#define H_Content_Type 10
#define H_Date 11
#define H_ETag 12
#define H_Expires 13
#define H_Last_Modified 14
#define H_Location 15
#define H_Pragma 16
#define H_Proxy_Authenticate 17
#define H_Retry_After 18
#define H_Server 19
#define H_Trailer 20
#define H_Transfer_Encoding 21
#define H_Upgrade 22
#define H_Vary 23
#define H_Via 24
#define H_WWW_Authenticate 25
#define H_Warning 26

class HTTP_Response_Headers
{
public:
  // Добавить заголовок, передаваемый как одна строка ответа
  int Add(char *str);

  // Получить значение заголовка по его имени. Возвращает NULL если такой заголовок не найден
  char *GetValue(char *name);

  HTTP_Response_Headers();
  ~HTTP_Response_Headers();
private:
  int GetHeaderId(char *header_name);
  int SplitHeader(char *header, char *name, char *value);
  char *headers[N_RESP_HEADERS];
};

/* // Страшный геморрой!
typedef struct
{
  char *Cache_Control;
  char *Connection;
  char *Date;
  char *Pragma;
  char *Trailer;
  char *Transfer_Encoding;
  char *Upgrade;
  char *Via;
  char *Warning;
} HTTP_GENERAL_HEADERS;

typedef struct
{
  char *Accept_Ranges;
  char *Age;
  char *ETag;
  char *Location;
  char *Proxy_Authenticate;
  char *Retry_After;
  char *Server;
  char *Vary;
  char *WWW_Authenticate;
} HTTP_RESPONSE_HEADERS;

typedef struct
{
  char *Content_Encoding;
  char *Content_Language;
  char *Content_Length;
  char *Content_Location;
  char *Content_MD5;
  char *Content_Range;
  char *Content_Type;
  char *Expires;
  char *Last_Modified;
} HTTP_ENTITY_HEADERS;

typedef struct
{
  char *Accept;
  char *Accept_Charset;
  char *Accept_Encoding;
  char *Accept_Language;
  char *Authorization;
  char *Expect;
  char *From;
  char *Host;
  char *If_Match;
  char *If_Modified_Since;
  char *If_None_Match;
  char *If_Range;
  char *If_Unmodified_Since;
  char *Max_Forwards;
  char *Proxy_Authorization;
  char *Range;
  char *Referer;
  char *TE;
  char *User_Agent;
} HTTP_REQUEST_HEADERS;
*/

#endif
