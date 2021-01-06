#ifndef LANGUAGE_H_
#define LANGUAGE_H_

#include <string>

void lgpInitLangPack(void);


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

extern std::string lgpData[LGP_DATA_NUM];

#endif
