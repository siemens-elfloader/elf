#include "include.h"
#include "langpack.h"
#include "file_works.h"

/* 
  LangPack
  ������� ����� �� ����� BalletMini � ���� ����������� ��� ���������� 
  �������������� ��������� ����� ;)
*/

LangPack * LangPack::Active = NULL;

LangPack::LangPack()
{
  for (int i = 0; i < LGP_DATA_NUM; i ++)
    data[i] = NULL;
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
  char * buf; // ����� ��� ����
  char line[128]; // ������� ������
  int line_size = 0; // ����� ������� ������
  int cur_id=0; // ������� LGP_ID
  int buf_pos = 0; // ������� � ������
  FSTATS fstat;
  char * lang_file = getSymbolicPath("$sieget\\lang.txt");
  if (GetFileStats(lang_file, &fstat, &io_error)!=-1) // �������� ������ �����
  {
    if((hFile=fopen(lang_file, A_ReadOnly + A_BIN, P_READ, &io_error))!=-1) // ��������� ���� ��� ������
    {
      if (buf = new char[fstat.size+1]) // �������� ������ ��� �����
      {
        buf[fread(hFile, buf, fstat.size, &io_error)]=0; // ������ ���� � �����

        while(buf[buf_pos] && buf_pos < fstat.size && cur_id < LGP_DATA_NUM) // ���� �� ����� ����� � �� ��������� ��� ���� �������
        {
          if (buf[buf_pos]=='\n' || buf[buf_pos]=='\r') // ���� ����� ������
          {
            if (line_size) // ���� ����� ������ > 0
            {
              data[cur_id] = new char[line_size + 1]; // �������� ������ � ������� ��� ������
              memcpy(data[cur_id], line, line_size); // �������� ������ � ������
              data[cur_id][line_size] = NULL; // ����� ������
              cur_id ++;
              line_size = NULL;
            }
          }
          else
            line[line_size++]=buf[buf_pos]; // ��������� � ������ ������� �� ������, ���� �� ����� �����
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
        delete buf; // ������� �����. �� ��� ��� �� �����������
        loaded = 1;
        fclose(hFile, &io_error);
        for (int i = 0; i < LGP_DATA_NUM; i ++)
        {
          if (!data[i])
          {
            data[i] = new char[64];
            strcpy(data[i], "Error! Update lang.txt!");
          }
        }
        return;
      }
      fclose(hFile, &io_error);
    }
  }
  delete lang_file;
  // ���� �� �����-�� �������� ���� ������ ���������, �� ������������� ���������� �������
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
  data[LGP_DownloadStarted] = "Download started";
  data[LGP_DownloadStopped] = "Download stopped";
  data[LGP_DownloadCompleted] = "Download completed";
  data[LGP_ResolvingHost] = "Resolving host...";
  data[LGP_WaitDNR] = "DNR not ready! Wait 5 seconds...";
  data[LGP_DNRError] = "DNR Error: %d";
  data[LGP_DNROutOfTries] = "DNR out of tries!";
  data[LGP_ConnectToIPPort] = "Connecting to IP %d.%d.%d.%d, port %d";
  data[LGP_HTTPParserReturned] = "HTTP Parser returned %d b (data size %d b)";
  data[LGP_GotResponseCode] = "Got response code: %d";
  data[LGP_GotResponseReason] = "Got response reason: \"%s\"";
  data[LGP_RangesNotSupportFileDelete] = "Ranges not supported, file will be deleted!";
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
