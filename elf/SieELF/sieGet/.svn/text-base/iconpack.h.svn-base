#ifndef _ICONPACK_H_
#define _ICONPACK_H_

#define LGP_SMILE_OK 0xE41F // :)
#define LGP_SMILE_NO 0xE43D // :(

enum ICON_ID
{
  IMG_About,
  IMG_Bookmark,
  IMG_Complete,
  IMG_Delete,
  IMG_DeleteSuccesful,
  IMG_Downloading,
  IMG_Error,
  IMG_Folder,
  IMG_GetInfo,
  IMG_Idle,
  IMG_Log,
  IMG_Logo,
  IMG_New,
  IMG_Pause,
  IMG_Settings,
  IMG_Start,
  IMG_Traffic,
  TOTAL_ICONS_NUM
};

class IconPack
{
public:
  IconPack();
  ~IconPack();
  
  void Setup();
  void Free();
  
  static IconPack * Active;
  
  int data[TOTAL_ICONS_NUM];
};

#endif
