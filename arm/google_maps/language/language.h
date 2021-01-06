#ifndef _LANG_H_
#define _LANG_H_

void lgpInitLangPack(void);
void lgpFreeLangPack(void);

enum LGP_ID
{
  LGP_LoadingMap=0,
  LGP_PressAnyKey,
  LGP_Traffic,
  LGP_State,
  LGP_LoadingCache,
  
  LGP_LangCode, // Пусть всегда будет в конце
  LGP_DATA_NUM
};

extern char * lgpData[LGP_DATA_NUM];

#endif /* _LANG_H_ */
