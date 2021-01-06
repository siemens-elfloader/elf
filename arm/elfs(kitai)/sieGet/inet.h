/*
  Проект SieGet Downloader
                          */

//inet.h
//Высокоуровневые функции для получения потока данных целиком по одному запросу

#ifndef _INET_H_
#define _INET_H_

#include "include.h"
#include "mem.h"
#include "socket.h"
#include "http.h"
#include "dns.h"
#include "url.h"
#include "log.h"

enum HTTP_STATE   // Статус HTTP
{
  HTTP_IDLE,      // Простой
  HTTP_RESOLVE,   // Получение IP
  HTTP_REDIRECT,  // Редирект
  HTTP_HEADER,    // Получение заголовка
  HTTP_STREAM,    // Получение данных
};

enum DOWNLOAD_STATE   // Статус закачки
{
  DOWNLOAD_WAITING,   // Ожидание
  DOWNLOAD_ERROR,     // Ошибка
  DOWNLOAD_CONNECT,   // Соединение
  DOWNLOAD_GET_INFO,  // Получение заголовка
  DOWNLOAD_DATA,      // Получение файла
  DOWNLOAD_COMPLETE,  // Успешно завершено
  DOWNLOAD_STOPPED    // Остановлено
};

enum ACCEPT_RANGES_STATE
{
  ACCEPT_RANGES_UNKNOWN,  // Неизвестно
  ACCEPT_RANGES_OK,       // Сервер поддерживает докачку
  ACCEPT_RANGES_NO        // Сервер не поддерживает докачку
};

// Макрос, показывающий активность нужной закачки
#define ACTIVE_DOWNLOAD_STATE(x) ((x) == DOWNLOAD_WAITING      \
                                  || (x) == DOWNLOAD_CONNECT   \
                                  || (x) == DOWNLOAD_GET_INFO  \
                                  || (x) == DOWNLOAD_DATA)

class HttpAbstract;

class HttpDNR: public DNR
{
public:
  virtual void onResolve(DNR_RESULT_MSG result_msg, int value);
  void Bind(HttpAbstract * sock);
  HttpDNR();
private:
  HttpAbstract * Callback;
};

class HttpAbstract: public Socket
{
public:
  virtual void onCreate(); // Создание сокета
  virtual void onDataRead(); // Получение данных
  virtual void onConnected(); // Соединение
  virtual void onClose(); // Закрытие сокета
  virtual void onRemoteClose(); // Удаленное закрытие
  virtual void onError(SOCK_ERROR err); // Обработчик ошибок

  virtual void onHTTPConnect() = 0; // Вызывается при соединении
  virtual int onHTTPHeaders() = 0; // Обработка заголовка HTTP
  virtual void onHTTPData(char * data, int size) = 0; // Обработка остальных данных (сохранение в файл)
  virtual void onHTTPRedirect() = 0; // Переадресация
  virtual void onHTTPStopped() = 0; // Остановка
  virtual void onHTTPFinish() = 0; // Окончание закачки
  
  void onResolve(DNR_RESULT_MSG result_msg, int value);
  
  void Start(int ip, short port); // Соединение по IP
  void Start(const char * host, short port); // Соединение по имени хоста
  
  void doConnect();
  
  HttpAbstract();
  ~HttpAbstract();
  
  HTTP_Request * HTTPRequest; // Запрос
  HTTP_Response * HTTPResponse; // Ответ
  HTTP_STATE http_state; // Состояние HTTP
  DOWNLOAD_STATE download_state; // Состояние закачки
  Buffer * req_buf; // Буфер запроса
  
private:
  int ip; // IP
  short port; // Порт
  Buffer * recv_buf; // Буфер ответа
  HttpDNR * Resolver; // Резолвер
};

class Download: public HttpAbstract
{
  virtual void onHTTPConnect() {}; // Тут пока нечего реализовывать
  virtual int onHTTPHeaders(); // Обработка заголовков HTTP
  virtual void onHTTPData(char * data, int size); // Обработка данных
  virtual void onHTTPRedirect(); // Переадресация
  virtual void onHTTPStopped(); // Остановка закачки
  virtual void onHTTPFinish(); // ФИниш закачки
public:
  Download();
  ~Download();

  static Download * Top; // Очередь закачек
  Download * next;
  
  void StartDownload();
  void StopDownload();
  
  ACCEPT_RANGES_STATE AcceptRangesState; // Поддержка сервером докачки
  
  char * url;             // URL
  char * file_name;       // Имя файла
  int is_const_file_name; // Флаг, указывающий, что имя файла указано юзером и его не следует менять
  char * full_file_name;  // Полное имя файла
  char * file_path;       // Папка сохранения
  int file_size;          // Полный размер файла
  int file_loaded_size;   // Размер закачанной части
private:
  int hFile; // Хендлер файла
};

void _start_download(Download * download);

class DownloadHandler
{
public:
  DownloadHandler();
  ~DownloadHandler();
  
  // Добавить закачку
  void CreateDownload(Download * download);
  //Удалить закачку
  void DeleteDownload(Download * download);
  //Получить класс закачки по ID сокета
  Download * GetDownloadbyID(int socket_id);
  //Получить класс закачки по ее позиции в списке
  Download * GetDownloadbyN(int n);
  // Получить число закачек с определенным статусом
  int GetNumOfDownloadsByState(DOWNLOAD_STATE state);
  //Получить закачку по статусу
  Download * GetDownloadByState(DOWNLOAD_STATE state);

  int IsAnyDownloadActive();
  // Получить число всех закачек в очереди
  int GetNumOfDownloads();
  
  static DownloadHandler * Top;
  
  void SaveQueue();
  void LoadQueue();

private:
  // Собственно очередь сокетов
  struct DownloadQ
  {
    Download * download;
    DownloadQ * next;
  };
  DownloadQ * queue;
};

void _load_queue(DownloadHandler * dh);
void _save_queue(DownloadHandler * dh);

#endif
