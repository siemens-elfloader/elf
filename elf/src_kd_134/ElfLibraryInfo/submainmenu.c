#include "C:/arm/inc/swilib.h"
#include "elfsubmainmenu.h"
#include "groopmainmenu.h"
#include "main.h"
//===============================================================================================

#pragma inline
void patch_header(HEADER_DESC* head)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}
#pragma inline
void patch_input(INPUTDIA_DESC* inp)
{
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}

//===============================================================================================

#ifdef ELKA
int submain_icon[]={0x0FE,0};
int elfs_icon[]={0x047,0};
#else
#ifdef NEWSGOLD
int submain_icon[]={0x5FD,0};
int elfs_icon[]={0x065,0};
#else
int submain_icon[]={0xFA0,0};
int elfs_icon[]={0xFA0,0};
#endif
#endif

int immenusoftkeys[]={0,1,2};
HEADER_DESC imenuhdr={0,0,131,21,submain_icon,(int)"έλότϋ:",0x7FFFFFFF};

