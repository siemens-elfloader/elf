#ifndef _ICONPACK_H_
#define _ICONPACK_H_

enum ICON_ID
{
  IMG_About,
  IMG_Update,
  IMG_Reboot,
  IMG_Config,
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
  int mode_data[8];
};

#endif
