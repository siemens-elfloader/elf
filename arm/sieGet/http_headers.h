#ifndef _HTTP_HEADERS_H_
#define _HTTP_HEADERS_H_

#include "log.h"

/*******************************************************************************
  HTTP Response Headers
*******************************************************************************/
                          
enum HTTP_RESP_HEADERS
{
  RESP_Accept_Ranges,
  RESP_Age,
  RESP_Cache_Control,
  RESP_Connection,
  RESP_Content_Disposition,
  RESP_Content_Encoding,
  RESP_Content_Language,
  RESP_Content_Length,
  RESP_Content_Location,
  RESP_Content_MD5,
  RESP_Content_Range,
  RESP_Content_Type,
  RESP_Date,
  RESP_ETag,
  RESP_Expires,
  RESP_Last_Modified,
  RESP_Location,
  RESP_Pragma,
  RESP_Proxy_Authenticate,
  RESP_Retry_After,
  RESP_Server,
  RESP_Set_Cookie,
  RESP_Trailer,
  RESP_Transfer_Encoding,
  RESP_Upgrade,
  RESP_Vary,
  RESP_Via,
  RESP_WWW_Authenticate,
  RESP_Warning,
  
  N_HTTP_RESP_HEADERS
};

// Статус-код ответа
enum HTTP_RESP_CODES
{
  // Успешно
  RESP_CODE_OK =	            200,
  RESP_CODE_CREATED =   	    201,
  RESP_CODE_ACCEPTED =              202,
  RESP_CODE_NO_CONTENT =            204,
  RESP_CODE_PARTIAL_CONTENTS =      206,
  // Переадресация
  RESP_CODE_MULTIPLE_CHOICES =      300,
  RESP_CODE_MOVED_PERMANENTLY =     301,
  RESP_CODE_MOVED_TEMPORARILY =     302,
  RESP_CODE_SEE_OTHER =             303, // HTTP/1.1
  RESP_CODE_NOT_MODIFIED =          304,
  RESP_CODE_TEMPORARY_REDIRECT =    307, // HTTP/1.1
  // Ошибка клиента
  RESP_CODE_BAD_REQUEST =           400,
  RESP_CODE_UNAUTHORIZED =          401,
  RESP_CODE_FORBIDDEN =             403,
  RESP_CODE_NOT_FOUND =             404,
  RESP_CODE_RANGE_NOT_SATISFIABLE = 416,
  // Ошибка сервера
  RESP_CODE_INTERNAL =		    500,
  RESP_CODE_NOT_IMPLEMENTED =  	    501,
  RESP_CODE_BAD_GATEWAY =           502,
  RESP_CODE_UNAVAILABLE =           503,
};

#define RESP_CODE_20X(x)          (((x) >= 200) && ((x) < 300))
#define RESP_CODE_CLIENT_ERROR(x) (((x) >= 400) && ((x) < 500))
#define RESP_CODE_SERVER_ERROR(x) (((x) >= 500) && ((x) < 600))
#define RESP_CODE_PARTIAL(x)      ((x) == RESP_CODE_PARTIAL_CONTENTS)
#define RESP_CODE_REDIRECTED(x)   ((x) == RESP_CODE_MOVED_PERMANENTLY || \
                                   (x) == RESP_CODE_MOVED_TEMPORARILY || \
                                   (x) == RESP_CODE_SEE_OTHER	      || \
                                   (x) == RESP_CODE_TEMPORARY_REDIRECT)

/* How many bytes it will take to store LEN bytes in base64.  */
#define BASE64_LENGTH(len) (4 * (((len) + 2) / 3))

class HTTP_Response_Headers
{
public:
  // Добавить заголовок, передаваемый как одна строка ответа
  int Add(char *str);

  // Получить значение заголовка по его имени. Возвращает NULL если такой заголовок не найден
  char * GetValue(char * name);
  
  HTTP_Response_Headers(Log * _log);
  ~HTTP_Response_Headers();
private:
  int GetHeaderId(char * header_name);
  int SplitHeader(char * header, char * name, char * value);
  char * headers[N_HTTP_RESP_HEADERS];
  Log * log;
};

/* // Страшный геморрой!
typedef struct
{
  char * Cache_Control;
  char * Connection;
  char * Date;
  char * Pragma;
  char * Trailer;
  char * Transfer_Encoding;
  char * Upgrade;
  char * Via;
  char * Warning;
} HTTP_GENERAL_HEADERS;

typedef struct
{
  char * Accept_Ranges;
  char * Age;
  char * ETag;
  char * Location;
  char * Proxy_Authenticate;
  char * Retry_After;
  char * Server;
  char * Vary;
  char * WWW_Authenticate;
} HTTP_RESPONSE_HEADERS;

typedef struct
{
  char * Content_Encoding;
  char * Content_Language;
  char * Content_Length;
  char * Content_Location;
  char * Content_MD5;
  char * Content_Range;
  char * Content_Type;
  char * Expires;
  char * Last_Modified;
} HTTP_ENTITY_HEADERS;
*/

#endif
