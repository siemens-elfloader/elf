#include "..\inc\swilib.h"
#include "lang.h"
#include "file_works.h"

char * lgpData[LGP_DATA_NUM];
int lgpLoaded;

void lgpInitLangPack(void)
{
  int hFile;
  unsigned int io_error = NULL;
  char * lang_file = getSymbolicPath("$ballet\\lang.txt");
  
  for (int i = 0; i < LGP_DATA_NUM; i ++)
    lgpData[i] = NULL;
  lgpLoaded = 0;
  
  char * buf;
  FSTATS fstat;
  
  if (GetFileStats(lang_file, &fstat, &io_error) != -1)
  {
    if((hFile = fopen(lang_file, A_ReadOnly + A_BIN, P_READ, &io_error))!=-1)
    {
      if (buf =(char *)malloc(fstat.size + 1))
      {
        buf[fread(hFile, buf, fstat.size, &io_error)] = NULL;
        fclose(hFile, &io_error);
        
        char line[128];
        int lineSize = NULL;
        int lp_id = NULL;
        int buf_pos = NULL;
        while(buf[buf_pos] && buf_pos < fstat.size && lp_id < LGP_DATA_NUM)
        {
          if (buf[buf_pos]=='\n' || buf[buf_pos]=='\r')
          {
            if (lineSize > 0)
            {
              lgpData[lp_id] = (char *)malloc(lineSize+1);
              memcpy(lgpData[lp_id], line, lineSize);
              lgpData[lp_id][lineSize] = NULL;
              lp_id ++;
              lineSize = NULL;
            }
          }
          else
            line[lineSize ++] = buf[buf_pos];
          buf_pos ++;
        }
        if (lineSize > 0 && lp_id < LGP_DATA_NUM) // eof
        {
          lgpData[lp_id] = (char *)malloc(lineSize+1);
          memcpy(lgpData[lp_id], line, lineSize);
          lgpData[lp_id][lineSize] = NULL;
          lp_id ++;
          lineSize = NULL;
        }
        mfree(buf);
        lgpLoaded = 1;
        
        // old langpack
        if (strlen(lgpData[LGP_LangCode]) > 2)
        {
          mfree(lgpData[LGP_LangCode]);
          lgpData[LGP_LangCode] = (char *)malloc(3);
          strcpy(lgpData[LGP_LangCode],"ru");
        }
        for (int i = 0; i < LGP_DATA_NUM; i ++)
        {
          if (!lgpData[i])
          {
            lgpData[i] = (char *)malloc(32);
            strcpy(lgpData[i], "Error! Update lang.txt!");
          }
        }
        mfree(lang_file);
        return;
      }
      fclose(hFile, &io_error);
    }
  }
  mfree(lang_file);
  lgpData[LGP_CantOpenFile]=          "Can't open file!";
  lgpData[LGP_CantLoadAuthCode]=      "Can't load AuthCode!";
  lgpData[LGP_HistoryFileFailed]=     "Can't open history.txt!";
  lgpData[LGP_CfgUpdated]=            "Config updated!";
  lgpData[LGP_RefUnderConstruction]=  "Ref \'%c\' under construction!";
  lgpData[LGP_RefEmpty]=              "RF empty!";
  lgpData[LGP_Error]=                 "Error!";
  lgpData[LGP_Stop]=                  "Stop";
  lgpData[LGP_WaitDNR]=               "Wait DNR...";
  lgpData[LGP_IpConnect]=             "Ip connect...";
  lgpData[LGP_GetHostByName]=         "Get host by name";
  lgpData[LGP_FaultDNR]=              "DNR fault!";
  lgpData[LGP_OkDNR]=                 "DNR ok!";
  lgpData[LGP_OpenSocket]=            "Open socket...";
  lgpData[LGP_ConnectFault]=          "Connect fault...";
  lgpData[LGP_AnswerDNR]=             "DNR answer...";
  lgpData[LGP_Connected]=             "Connected...";
  lgpData[LGP_DataReceived]=          "Data received...";
  lgpData[LGP_RemoteClosed]=          "Remote closed!";
  lgpData[LGP_LocalClosed]=           "Local closed!";
  lgpData[LGP_InetBusy]=              "INET process busy!";
  lgpData[LGP_EnableGPRS]=            "Enable GPRS first!";
  lgpData[LGP_UnderConstruction]=     "Under Construction!";
  lgpData[LGP_Select]=                "Select";
  lgpData[LGP_Close]=                 "Close";
  lgpData[LGP_Ok]=                    "Ok";
  lgpData[LGP_Cancel]=                "Cancel";
  lgpData[LGP_Templates]=             "Templates";
  lgpData[LGP_NameHeader]=            "Name:";
  lgpData[LGP_LinkHeader]=            "Link:";
  lgpData[LGP_TextHeader]=            "Text:";
  lgpData[LGP_SearchEngine]=          "Search engine:";
  lgpData[LGP_SelectHeader]=          "Select:";
  lgpData[LGP_EnterHeader]=           "Enter:";
  lgpData[LGP_Add]=                   "Add";
  lgpData[LGP_BookmarkHeader]=        "Bookmark...";
  lgpData[LGP_Save]=                  "Save";
  lgpData[LGP_NewBookmark]=           "New bookmark";
  lgpData[LGP_NewFolder]=             "New folder";
  lgpData[LGP_Absent]=                "Absent";
  lgpData[LGP_OptionsHeader]=         "Options:";
  lgpData[LGP_Edit]=                  "Edit";
  lgpData[LGP_Delete]=                "Delete";
  lgpData[LGP_Back]=                  "Back";
  lgpData[LGP_Options]=               "Options";
  lgpData[LGP_SelectBookmarkHeader]=  "Select bookmark:";
  lgpData[LGP_SearchHeader]=          "Search:";
  lgpData[LGP_Go]=                    "Go";
  lgpData[LGP_HistoryHeader]=         "History:";
  lgpData[LGP_AddressHeader]=         "Address";
  lgpData[LGP_Menu]=                  "Menu";
  lgpData[LGP_GoTo]=                  "Go to";
  lgpData[LGP_Bookmarks]=             "Bookmarks";
  lgpData[LGP_History]=               "History";
  lgpData[LGP_Settings]=              "Settings";
  lgpData[LGP_Exit]=                  "Exit";
  lgpData[LGP_Search]=                "Search";
  lgpData[LGP_EnterName]=             "Enter name!";
  lgpData[LGP_EnterURL]=              "Enter URL!";
  lgpData[LGP_FolderExists]=          "Folder is allready exists!";
  lgpData[LGP_FileExists]=            "File is allready exists!";
  lgpData[LGP_FolderNotEmpty]=        "Folder is not empty!";
  
  lgpData[LGP_LangCode]=              "en";
}

void lgpFreeLangPack(void)
{
  if (!lgpLoaded) return;
  for (int i = 0; i < LGP_DATA_NUM; i ++)
  {
    if (lgpData[i])
      mfree(lgpData[i]);
  }
}
