#ifndef __SIEMENS_H__
#define __SIEMENS_H__

struct ITEMSDATA
{
   unsigned long const *pIconIDList;
   unsigned long StrID_NormalMenu;
   unsigned long StrID_CapsMenu;
   unsigned long Zero1;
   unsigned long pUnk2;
   unsigned long ItemType;
   unsigned long ItemConditionCode;
};

struct MENUSTRUCT
{
   unsigned long pUnk1;
   void* OnKeyPress;
   void* OnMessage;
   unsigned long pUnk2;
   unsigned long pUnkData1;
   unsigned long pUnkData2;
   unsigned short Unk1;
   unsigned short Unk2;
   void* OnAppearItem;
   /*const*/ struct ITEMSDATA* ItemsData;
   const unsigned long *ItemsHandler;
   unsigned long ItemsCount;
};

struct MENUFRAME
{
   unsigned short x1;
   unsigned short y1;
   unsigned short x2;
   unsigned short y2;
   const unsigned long *IconRef;
   unsigned long StrID_header;
   unsigned long anonymous_4;
};

#endif
