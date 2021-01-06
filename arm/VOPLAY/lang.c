#include "lang.h" 
#include "C:\arm\inc\swilib.h"

//#include "C:\pp\png.h" 
typedef unsigned short byte;
extern const char folder[128];
char lang_file[];//"0:\\lang.txt";
char * lgpData[LGP_DATA_NUM];
int lgpLoaded;
void T_Load_IMG();
extern byte status;
extern int langg;
extern int lan;

void lgpInitLangPack(void)
{
  
  int hFile;
  unsigned int io_error = NULL;
  sprintf(lang_file,"%s%s",folder,"lang.lng");//Какой файл

  for (int i = 0; i < LGP_DATA_NUM; i ++)
    lgpData[i] = NULL;
  lgpLoaded = 0;
  
  char * buf;
  FSTATS fstat;
  
  if (GetFileStats(lang_file, &fstat,0) != -1)
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
      
        lgpLoaded = 1;
        
        
        if (strlen(lgpData[LGP_LangCode]) > 2)
        {
       
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
     
        return;
      }
      fclose(hFile, &io_error);
      
    }
  }
  if (GetFileStats(lang_file, &fstat,0) == -1&&lan==0)
  {
    langg=2;
    }
  if (GetFileStats(lang_file, &fstat,0) == -1&&lan==1){
 
lgpData[LG_OV_ALIGN]=                  "Атрибут";
lgpData[LG_BG_COL]=                  "Цвет фона";
lgpData[LG_COL]=                          "Цвет";
lgpData[LG_OV_FONT]=                  "Шрифт";
lgpData[LG_OVERLAY]=                  "Оверлей-теги";
lgpData[LG_VISUAL]=                  "Главный экран и тд";
lgpData[LG_VIS_FOL]=                "Настройки путей и тд";
lgpData[LG_FOLDERS]=                  "Папки";
lgpData[LG_STARTED]=                  "Уже запущен!";
lgpData[LG_ERFIND]=                  "Тэги не найдены!";
lgpData[LG_EROPEN]=                  "Ошибка открытия!";
lgpData[LG_BACK]=                  "Назад";
lgpData[LG_EDIT]=                  "Edit";
lgpData[LG_EDITTAG]=               "EditTag";
lgpData[LG_TAG_TITLE]=             "Title";
lgpData[LG_TAG_ARTIST]=            "Artist";
lgpData[LG_TAG_ALBUM]=             "Album";
lgpData[LG_TAG_YEAR]=             "Year";
lgpData[LG_TAG_COMMENT]=           "Comment";
lgpData[LG_TAG_TRACK]=             "Track";
lgpData[LG_TAG_GENRE]=             "Genre";
lgpData[LG_ID3_EDITOR]= "Редактор тегов";
lgpData[LG_ALLWAYS]= "Always";
lgpData[LG_IFUNLOCK]= "If Unlock";
lgpData[LG_NEVER]= "Never";
lgpData[LG_MEDIALIBRARY]= "Medialibrary";
lgpData[LG_CREATE_MEDIALIBRARY]= "Create";
lgpData[LG_ICON_ON_IDLE]= "IDLE";
lgpData[LG_ENABLE_ICON_ON_IDLE]= "Enable";
lgpData[LG_IDLE_ICON_POSITION]= "Position";
lgpData[LG_MENU]= "Menu";
lgpData[LG_PF]= "PlayerFolder";
lgpData[LG_PLAYLIST]= "Playlist";
lgpData[LG_SELECT_PLAYLIST]= "Select playlist";
lgpData[LG_SELECT]= "Select";
lgpData[LG_CLOSE]= "Back";
lgpData[LG_ERROR]= "Error";
lgpData[LG_CONFIG_UPDATED]= "Config updated!";
lgpData[LG_NO_PLAYLIST]= "No playlist!";
lgpData[LG_FFP]= "Folder for creating playlist";
lgpData[LG_DRAW_TRACK_TIME]= "Draw time";
lgpData[LG_DRAW_TRACK_TIME_TIMER]= "Draw time timer";
lgpData[LG_F1]= "Format 1";
lgpData[LG_F2]= "Format 2";
lgpData[LG_F3]= "Format 3";
lgpData[LG_F4]= "Format 4";
lgpData[LG_FORMATS]= "Formats";
lgpData[LG_TIME]= "Time options";
lgpData[LG_STOPRESUME]= "Pause";
lgpData[LG_STOP]= "Stop";
lgpData[LG_VOLUMEUP]= "Volume up";
lgpData[LG_VOLUMEDOWN]= "Volume down";
lgpData[LG_RANDOM]= "At random";
lgpData[LG_PREVIOUSSKIN]= "Previous skin";
lgpData[LG_NEXTSKIN]= "Next skin";
lgpData[LG_PREVIOUSTRACK]= "Previous track";
lgpData[LG_NEXTTRACK]= "Next track";
lgpData[LG_CONFIG]= "Config(0)";
lgpData[LG_PLAYLISTMENU]= "Playlist menu";
lgpData[LG_MUTE]= "Muting";
lgpData[LG_BLOCKKEYBOARD]= "Block keyboard and do IDLE";
lgpData[LG_EXIT]= "Exit";
lgpData[LG_NOTHING]= "Nothing";
lgpData[LG_ABOUT]= "About...";
lgpData[LG_KEYBLOCK]= "Block keyboard";
lgpData[LG_CONFIG4]= "Config(4)";
lgpData[LG_MEDIABASE]= "База данных медиафайлов";
lgpData[LG_DOIDLE]= "Do IDLE";
lgpData[LG_PLAY_ONCE_MORE_OR_PREVIOUS]= "Play once/Next track";
lgpData[LGP_LangCode]=              "en";

    
  }
    

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
