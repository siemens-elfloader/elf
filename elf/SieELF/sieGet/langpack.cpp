#include "include.h"
#include "langpack.h"
#include "file_works.h"

/* 
  LangPack
  Функции взяты из эльфа BalletMini и чуть подправлены для увеличения 
  быстродействия обработки файла ;)
*/

LangPack * LangPack::Active = NULL;

LangPack::LangPack()
{
  loaded = NULL;
  Setup();
}

LangPack::~LangPack()
{
  Free();
}

void LangPack::Setup()
{
  Free();
  Active = this;
  volatile int hFile;
  unsigned int io_error = 0;
  char * buf; // Буфер под файл
  char line[128]; // Текущая строка
  int line_size = 0; // Длина текущей строки
  int cur_id=0; // Текущий LGP_ID
  int buf_pos = 0; // Позиция в буфере
  FSTATS fstat;
  char lang_file[256];
  getSymbolicPath(lang_file, "$sieget\\lang.txt");
  if (GetFileStats(lang_file, &fstat, &io_error)!=-1) // Получаем размер файла
  {
    if((hFile=fopen(lang_file, A_ReadOnly + A_BIN, P_READ, &io_error))!=-1) // Открываем файл для чтения
    {
      if (buf = new char[fstat.size+1]) // Выделяем память под буфер
      {
        buf[fread(hFile, buf, fstat.size, &io_error)]=0; // Читаем файл в буфер

        while(buf[buf_pos] && buf_pos < fstat.size && cur_id < LGP_DATA_NUM) // Пока не конец файла и не заполнены все поля массива
        {
          if (buf[buf_pos]=='\n' || buf[buf_pos]=='\r') // Если конец строки
          {
            if (line_size) // Если длина строки > 0
            {
              data[cur_id] = new char[line_size + 1]; // Выделяем память в массиве под строку
              memcpy(data[cur_id], line, line_size); // Копируем строку в массив
              data[cur_id][line_size] = NULL; // Конец строки
              cur_id ++;
              line_size = NULL;
            }
          }
          else
            line[line_size++]=buf[buf_pos]; // Добавляем в строку символы из буфера, пока не конец сроки
          buf_pos++;
        }
        if (line_size && cur_id < LGP_DATA_NUM) // eof
        {
          data[cur_id] = new char[line_size + 1];
          memcpy(data[cur_id], line, line_size);
          data[cur_id][line_size] = NULL;
          cur_id ++;
          line_size = NULL;
        }
        delete buf; // Удаляем буфер. он нам уже не понадобится
        loaded = 1;
        fclose(hFile, &io_error);
        return;
      }
      fclose(hFile, &io_error);
    }
  }
  // Если по каким-то причинам файл нельзя прочитать, то устанавливаем английский ленгпак
  data[LGP_Options] = "Options";
  data[LGP_Select] = "Select";
  data[LGP_Back] = "Back";
  data[LGP_Close] = "Close";
  data[LGP_Cancel] = "Cancel";
  data[LGP_Error] = "Error";
  data[LGP_Unknown] = "Unknown";
  data[LGP_Bookmarks] = "Bookmarks";
  data[LGP_SelectFolder] = "Select folder";
  data[LGP_NewDownload] = "New download";
  data[LGP_StartDownload] = "Start";
  data[LGP_PauseDownload] = "Stop";
  data[LGP_DeleteDownload] = "Delete";
  data[LGP_DeleteSuccesfulDownload] = "Delete succesful";
  data[LGP_Settings] = "Settings";
  data[LGP_About] = "About";
  data[LGP_ViewLog] = "View log";
  data[LGP_EditBookmark] = "Edit bookmark";
  data[LGP_AddBookmark] = "Add bookmark";
  data[LGP_RenameFolder] = "Rename folder";
  data[LGP_AddFolder] = "Add folder";
  data[LGP_DeleteBookmark] = "Delete bookmark";
  data[LGP_DeleteFolder] = "Delete folder";
  data[LGP_DownloadState] = "Download state:";
  data[LGP_FileSize] = "File size:";
  data[LGP_LoadedSize] = "Loaded size:";
  data[LGP_OpenFile] = "Open file";
  data[LGP_Sended] = "Sended:";
  data[LGP_Received] = "Received:";
  data[LGP_TotalSended] = "Total sended:";
  data[LGP_TotalReceived] = "Total received:";
  data[LGP_Waiting] = "Waiting";
  data[LGP_Connecting] = "Connecting";
  data[LGP_GettingInfo] = "Getting info";
  data[LGP_Downloading] = "Downloading";
  data[LGP_Completed] = "Completed";
  data[LGP_Stopped] = "Stopped";
  data[LGP_Info] = "Info";
  data[LGP_Traffic] = "Traffic";
  data[LGP_Name] = "Name:";
  data[LGP_DownloadFolder] = "Download to:";
  data[LGP_FileName] = "File name:";
  data[LGP_CantReadBookmark] = "Can't read bookmark!";
  data[LGP_FolderNotEmpty] = "Folder is not empty!";
  data[LGP_EnterName] = "Enter name, please!";
  data[LGP_EnterUrl] = "Enter URL, please!";
  data[LGP_EnterDownloadsFolder] = "Enter downloads folder, please!";
  data[LGP_FolderExists] = "This folder is allready exists!";
  data[LGP_FileExists] = "This file is allready exists!";
  data[LGP_SocketConnected] = "Socket connected";
  data[LGP_SocketRemoteClosed] = "Socket remote closed";
  data[LGP_SocketClosed] = "Socket closed";
  data[LGP_SocketCreateError] = "Socket create error!";
  data[LGP_SocketConnectError] = "Socket connect error!";
  data[LGP_SocketSendError] = "Socket send error!";
  data[LGP_SocketCloseError] = "Socket close error!";
  data[LGP_InvalidSocket] = "Invalid socket!";
  data[LGP_EnableGPRSFirst] = "Enable GPRS first!";
  
  data[LGP_Reserved1] = 
  data[LGP_Reserved2] = 
  data[LGP_Reserved3] = 
  data[LGP_Reserved4] = 
  data[LGP_Reserved5] = "Please, update lang.txt";
}

void LangPack::Free()
{
  if (loaded)
  {
    for (int i = 0; i < LGP_DATA_NUM; i ++)
      _safe_delete(data[i]);
    loaded = NULL;
  }
}
