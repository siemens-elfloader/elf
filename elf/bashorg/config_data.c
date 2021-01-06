#include "cfg_items.h"

#define IP_ADDR(A,B,C,D) (((unsigned long)A<<24)|((unsigned long)B<<16)|((unsigned long)C<<8)|((unsigned long)D<<0))


__root const CFG_HDR cfghdr0={CFG_UINT,"Сожрать трафа?",0,60000};
__root const unsigned int limit=3000;

__root const CFG_HDR cfghdr1={CFG_STR_UTF8,"Путь к архиву",0,63};
__root const char hist_path[64]="4:\\bash";

__root const CFG_HDR cfghdr2={CFG_STR_UTF8,"Путь к ресурсам",0,63};
__root const char ic_path[64]="0:\\zbin\\img\\bash";

__root const CFG_HDR cfghdr3={CFG_CHECKBOX,"Рисовать иконки?",0,1};
__root const unsigned int ic=1;

__root const CFG_HDR cfghdr4={CFG_UINT,"Регистрационный код",0,~0};
__root const unsigned int ipp=IP_ADDR(89,111,181,251);


