#ifndef _LANGPACK_H_
#define _LANGPACK_H_

enum LGP_ID
{
  LGP_Options=0,
  LGP_Select,
  LGP_Back,
  LGP_Close,
  LGP_Cancel,
  LGP_Error,
  LGP_Unknown,
  LGP_Bookmarks,
  LGP_SelectFolder,
  LGP_NewDownload,
  LGP_StartDownload,
  LGP_PauseDownload,
  LGP_DeleteDownload,
  LGP_DeleteSuccesfulDownload,
  LGP_Settings,
  LGP_About,
  LGP_ViewLog,
  LGP_EditBookmark,
  LGP_AddBookmark,
  LGP_RenameFolder,
  LGP_AddFolder,
  LGP_DeleteBookmark,
  LGP_DeleteFolder,
  LGP_DownloadState,
  LGP_FileSize,
  LGP_LoadedSize,
  LGP_OpenFile,
  LGP_Sended,
  LGP_Received,
  LGP_TotalSended,
  LGP_TotalReceived,
  LGP_Waiting,
  LGP_Connecting,
  LGP_GettingInfo,
  LGP_Downloading,
  LGP_Completed,
  LGP_Stopped,
  LGP_Info,
  LGP_Traffic,
  LGP_Name,
  LGP_DownloadFolder,
  LGP_FileName,
  LGP_CantReadBookmark,
  LGP_FolderNotEmpty,
  LGP_EnterName,
  LGP_EnterUrl,
  LGP_EnterDownloadsFolder,
  LGP_FolderExists,
  LGP_FileExists,
  LGP_SocketConnected,
  LGP_SocketRemoteClosed,
  LGP_SocketClosed,
  LGP_SocketCreateError,
  LGP_SocketConnectError,
  LGP_SocketSendError,
  LGP_SocketCloseError,
  LGP_InvalidSocket,
  LGP_EnableGPRSFirst,
  LGP_DownloadStarted,
  LGP_DownloadStopped,
  LGP_DownloadCompleted,
  LGP_ResolvingHost,
  LGP_WaitDNR,
  LGP_DNRError,
  LGP_DNROutOfTries,
  LGP_ConnectToIPPort,
  LGP_HTTPParserReturned,
  LGP_GotResponseCode,
  LGP_GotResponseReason,
  LGP_RangesNotSupportFileDelete,
  
  LGP_DATA_NUM
};

class LangPack
{
public:
  LangPack(); // Вызывается при создании диалога
  ~LangPack(); // Вызывается при уничтожении диалога
  
  void Setup();
  void Free();
  static LangPack * Active;
  
  char * data[LGP_DATA_NUM];
private:
  int loaded;
};

/* Копирайт ;) */
#define LG_COPYRIGHT  "SieGet Downloader\n(c)Borman,\nThe_ZeN\r\nCompiled:\n"__DATE__"\n"__TIME__

#endif
