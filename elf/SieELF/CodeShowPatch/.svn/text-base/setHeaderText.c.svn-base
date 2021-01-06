/*********************************************
SGold短信区号秀
作者：		DaiKangaroo
最后修改:	2009.01.25
简述：
    修改短信界面标题为区号秀
***********************************************/
#include "type_.h"

extern int GetProvAndCity(word *pBSTR, char *pNoStr);
extern WSTRING *AllocWS(int len);
extern void SetHeaderText(void *hdr_pointer, WSTRING *txt, void *malloc_adr, void *mfree_adr);
extern void *GetHeaderPointer(void *gui);

void ChangeHeaderText(void *gui,char *num,void *malloc_adr, void *mfree_adr)
#ifdef SK6Cv50
 @ "CODE_X"
#endif
{
     WSTRING *ws=AllocWS(10);
     GetProvAndCity(ws->pstr, num);
     void *hdr_p=GetHeaderPointer(gui);
     SetHeaderText(hdr_p, ws, malloc_adr, mfree_adr);
}
