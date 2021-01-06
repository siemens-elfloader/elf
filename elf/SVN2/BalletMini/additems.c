#include "../inc/swilib.h"
#include "view.h"
#include "additems.h"
#include "readimg.h"
#include "string_works.h"
#include "siemens_unicode.h"
#include "file_works.h"
#include "urlstack.h"

#define DP_IS_FRAME (-2)
#define DP_IS_NOINDEX (-1)
#define RAWTEXTCHUNK (16384)
#define REFCACHECHUNK (256)

#define FIRST_UCS2_USER_BITMAP 0xE100

/*static*/ void RawInsertChar(VIEWDATA *vd, int wchar)
{
  if ((vd->rawtext_size%RAWTEXTCHUNK)==0)
  {
    //Дошли до конца куска, реаллоцируем еще кусок
    vd->rawtext=realloc(vd->rawtext,(vd->rawtext_size+RAWTEXTCHUNK)*2);
  }
  //
  vd->rawtext[vd->rawtext_size++]=wchar;
}

void AddNewStyle(VIEWDATA *vd)
{
  if (vd->current_tag_s.bold!=vd->prev_tag_s.bold)
    RawInsertChar(vd,vd->current_tag_s.bold?UTF16_FONT_SMALL_BOLD:UTF16_FONT_SMALL);
//  if (vd->current_tag_s.underline!=vd->prev_tag_s.underline)
//    RawInsertChar(vd,vd->current_tag_s.underline?UTF16_ENA_UNDERLINE:UTF16_DIS_UNDERLINE);
  RawInsertChar(vd,UTF16_INK_RGBA);
  RawInsertChar(vd,(vd->current_tag_s.red<<11)+(vd->current_tag_s.green<<2));
  RawInsertChar(vd,(vd->current_tag_s.blue<<11)+100);
  RawInsertChar(vd,UTF16_PAPER_RGBA);
  RawInsertChar(vd,(vd->current_tag_d.red<<11)+(vd->current_tag_d.green<<2));
  RawInsertChar(vd,(vd->current_tag_d.blue<<11)+100);
  if (vd->current_tag_s.center!=vd->prev_tag_s.center)
    RawInsertChar(vd,vd->current_tag_s.center?UTF16_ENA_CENTER:UTF16_DIS_CENTER);
  if (vd->current_tag_s.right!=vd->prev_tag_s.right)
    RawInsertChar(vd,vd->current_tag_s.right?UTF16_ALIGN_RIGHT:UTF16_ALIGN_LEFT);
}

void AddBeginRef(VIEWDATA *vd)
{
  vd->work_ref.begin=vd->rawtext_size;
  RawInsertChar(vd,UTF16_ENA_INVERT);
}

void AddBeginRefZ(VIEWDATA *vd)
{
  vd->work_ref_Z.begin=vd->rawtext_size;
  RawInsertChar(vd,UTF16_ENA_INVERT);
}

void AddToRefCache(VIEWDATA *vd)
{
  REFCACHE* p;
  if ((vd->ref_cache_size%REFCACHECHUNK)==0)
  {
    vd->ref_cache=realloc(vd->ref_cache,(vd->ref_cache_size+REFCACHECHUNK)*sizeof(REFCACHE));
  }
  p=vd->ref_cache+vd->ref_cache_size;
  memcpy(p,&(vd->work_ref),sizeof(REFCACHE));
  vd->ref_cache_size++;
  memset(&(vd->work_ref),0xFF,sizeof(REFCACHE));
}

void AddEndRef(VIEWDATA *vd)
{
  RawInsertChar(vd,UTF16_DIS_INVERT);
  if (vd->pos_cur_ref==0xFFFFFFFF)
  {
    vd->pos_cur_ref=vd->work_ref.begin;
  }
  vd->work_ref.end = vd->rawtext_size;
  AddToRefCache(vd);
}

void AddTextItem(VIEWDATA *vd, const char *text, int len)
{
  int c;
  while((len--)>0)
  {
    c=*text++;
    if ((c&0xE0)==0xC0)
    {
      if (len>0)
      {
        c&=0x1F;
        c<<=6;
        c|=(*text++)&0x3F;
        len-=1;
      }
    }
    else
      if ((c&0xF0)==0xE0)
      {
        if (len>1)
        {
          c&=0x0F;
          c<<=12;
          c|=((*text++)&0x3F)<<6;
          c|=((*text++)&0x3F)<<0;
          len-=2;
        }
      }
    RawInsertChar(vd,c);
  }
}

void AddBrItem(VIEWDATA *vd)
{
  AddTextItem(vd,"\n",1);
}

void AddPItem(VIEWDATA *vd)
{
  AddTextItem(vd," ",1);
}

void AddPictureItemIndex(VIEWDATA *vd, int index)
{
  int w_char=FIRST_UCS2_USER_BITMAP;
  OMS_DYNPNGLIST *dpl=vd->dynpng_list;
  while(dpl)
  {
    if (dpl->index==index) 
    {
      w_char=dpl->w_char;
      break;
    }
    dpl=dpl->dp.next;
  }
  RawInsertChar(vd,w_char);
}


//is_index >= 0 использовать последний
//is_index <0 - задать  принудительно
OMS_DYNPNGLIST *AddToDPngQueue(VIEWDATA *vd, IMGHDR *img, int is_index)
{
  if (img->w > ScreenW()-MARGIN)
    img->w = ScreenW()-MARGIN;
  int wchar, i, index, icon;
  OMS_DYNPNGLIST *dpl;
  OMS_DYNPNGLIST *odp=malloc(sizeof(OMS_DYNPNGLIST));
  odp->dp.next=0;
  odp->dp.img=img;
  dpl=vd->dynpng_list;
  if (!dpl)
  {
    wchar=FIRST_UCS2_USER_BITMAP+1;
    odp->dp.icon=GetPicNByUnicodeSymbol(wchar);
    odp->w_char=wchar;
    if (is_index>=0) odp->index=0;
    else odp->index=is_index;
    LockSched();
    vd->dynpng_list=odp;
    UnlockSched();
    RefreshGUI();
  }
  else
  {
    i=0;
    index=0;
    OMS_DYNPNGLIST *d;
    do
    {
      d=dpl;
      if (is_index>=0 && d->index>=0) index++;
      i++;
    }
    while((dpl=dpl->dp.next));
    if (d->dp.icon != 0xFFFF)
    {
      wchar=FIRST_UCS2_USER_BITMAP+1+i;
      icon = GetPicNByUnicodeSymbol(wchar);
      dpl=vd->dynpng_list;
      do
      {
        if (icon == dpl->dp.icon)
        {
          icon = GetPicNByUnicodeSymbol(++wchar);
          dpl = vd->dynpng_list;
        } 
        else
          dpl = dpl->dp.next;
      }
      while(dpl);
    }
    else
    {
      mfree(odp->dp.img->bitmap);
      mfree(odp->dp.img);
      mfree(odp);
      return 0;
    }
    odp->dp.icon=icon;
    odp->w_char=wchar;
    if (is_index>=0)  odp->index=index;
    else odp->index=is_index;
    LockSched();
    d->dp.next=odp;
    UnlockSched();
  }
  return odp;
}

void AddPictureItem(VIEWDATA *vd, void *picture)
{
  int wchar=FIRST_UCS2_USER_BITMAP;
  IMGHDR *img;
  OMS_DYNPNGLIST *dpl;
  if (picture)
  {
    if ((img=read_pngimg(picture)))
    {
      dpl=AddToDPngQueue(vd, img, 0);
      if (dpl)
        wchar=dpl->w_char;
    }
    else  if ((img=read_jpgimg(picture)))
    {
      dpl=AddToDPngQueue(vd, img, 0);
      if (dpl)
        wchar=dpl->w_char;
    }
  }
  RawInsertChar(vd,wchar);
}

void AddPictureItemRGBA(VIEWDATA *vd, void *picture, int width, int height)
{
  int wchar=FIRST_UCS2_USER_BITMAP;
  IMGHDR *img;
  OMS_DYNPNGLIST *dpl;
  if (picture)
  {
    img=ConvertRGBAToRGB8(picture,width,height);
    if (img)
    {
      dpl=AddToDPngQueue(vd, img, DP_IS_NOINDEX);
      if (dpl)
        wchar=dpl->w_char;
    }
  }
  //Prepare Wide String
  RawInsertChar(vd,wchar);  
}

OMS_DYNPNGLIST *FindOmsFrameBySize(VIEWDATA *vd,int width,int height)
{
  IMGHDR *img;
  OMS_DYNPNGLIST *dpl=vd->dynpng_list;
  while(dpl)
  {
    if (dpl->index==DP_IS_FRAME)
    {
      if ((img=dpl->dp.img))
      {
        if (img->w==width && img->h==height) return (dpl);
      }
    }
    dpl=dpl->dp.next;
  }
  return (dpl);
}

void AddPictureItemFrame(VIEWDATA *vd,int width,int height)
{
  int wchar=FIRST_UCS2_USER_BITMAP;
  IMGHDR *img;
  OMS_DYNPNGLIST *dpl;
  dpl=FindOmsFrameBySize(vd,width,height);
  if (dpl) wchar=dpl->w_char;
  else
  {
    img=CreateFrame(width,height,GetPaletteAdrByColorIndex(3));
    if (img)
    {
      dpl=AddToDPngQueue(vd, img, DP_IS_FRAME);
      if (dpl)
        wchar=dpl->w_char;
    }
  }
  RawInsertChar(vd,wchar);  
}

void AddPictureItemHr(VIEWDATA *vd)
{
  int wchar=FIRST_UCS2_USER_BITMAP;
  IMGHDR *img;
  OMS_DYNPNGLIST *dpl;
  if (!vd->wchar_hr)
  {
    img=CreateDelimiter(ScreenW()-MARGIN,3,GetPaletteAdrByColorIndex(1));
    if (img)
    {
      dpl=AddToDPngQueue(vd, img, DP_IS_NOINDEX);
      if (dpl)
        vd->wchar_hr=wchar=dpl->w_char;
    }
  }
  else wchar=vd->wchar_hr;
  RawInsertChar(vd,wchar);
}

int AddPictureItemFile(VIEWDATA *vd, const char *file)
{
  int wchar=FIRST_UCS2_USER_BITMAP;
  IMGHDR *img;
  OMS_DYNPNGLIST *dpl;
	FSTATS fs;
  unsigned int err;
  if (GetFileStats(file,&fs,&err)!=-1)
  {
    if (img=CreateIMGHDRFromPngFile(file, 0))
    {
      dpl=AddToDPngQueue(vd, img, DP_IS_NOINDEX);
      if (dpl)
        wchar=dpl->w_char;
    }
  }
  return wchar;
}

void AddRadioButton(VIEWDATA *vd, int checked)
{
  if (!vd->WCHAR_RADIO_ON)
  {
    char * radio_bttn_clkd = getSymbolicPath("$resources\\radio_bttn_clkd.png");
    vd->WCHAR_RADIO_ON=AddPictureItemFile(vd, radio_bttn_clkd);
    mfree(radio_bttn_clkd);
    char * radio_bttn = getSymbolicPath("$resources\\radio_bttn.png");
    vd->WCHAR_RADIO_OFF=AddPictureItemFile(vd, radio_bttn);
    mfree(radio_bttn);
  }
  RawInsertChar(vd,checked?vd->WCHAR_RADIO_ON:vd->WCHAR_RADIO_OFF);
}

void AddCheckBoxItem(VIEWDATA *vd, int checked)
{
  if (!vd->WCHAR_BUTTON_ON)
  {
    char * button_clkd = getSymbolicPath("$resources\\button_clkd.png");
    vd->WCHAR_BUTTON_ON=AddPictureItemFile(vd, button_clkd);
    mfree(button_clkd);
    char * button = getSymbolicPath("$resources\\button.png");
    vd->WCHAR_BUTTON_OFF=AddPictureItemFile(vd, button);
    mfree(button);
  }
  RawInsertChar(vd,checked?vd->WCHAR_BUTTON_ON:vd->WCHAR_BUTTON_OFF);
}

void AddInputItem(VIEWDATA *vd, unsigned int pos)
{
  if (!vd->WCHAR_TEXT_FORM)
  {
    char * text_form = getSymbolicPath("$resources\\text_form.png");
    vd->WCHAR_TEXT_FORM=AddPictureItemFile(vd, text_form);
    mfree(text_form);
  }
  RawInsertChar(vd,vd->WCHAR_TEXT_FORM);
  WSHDR* saved_text = getUserTextByRefId(vd->work_ref.id);
  if (saved_text)
  {
    vd->work_ref.data=(void *)AllocWS(wstrlen(saved_text));
    wstrcpy((WSHDR *)vd->work_ref.data, saved_text);
  }
  else
  {
    int len=_rshort2(vd->oms+pos);
    vd->work_ref.data=(void *)AllocWS(len);
    char *c=extract_omstr(vd,pos);
    oms2ws(((WSHDR *)vd->work_ref.data),c,len);
    mfree(c);
  }
}

void AddButtonItem(VIEWDATA *vd, const char *text, int len)
{
  int wchar=FIRST_UCS2_USER_BITMAP;
  IMGHDR *img;
  OMS_DYNPNGLIST *dpl;
  int cw = 0;
  vd->work_ref.data=(void *)AllocWS(len);
  oms2ws(((WSHDR *)vd->work_ref.data),text,len);
  int datalen = ((WSHDR *)vd->work_ref.data)->wsbody[0];
  for (int i = 1; i <= datalen; i++)
    cw+=GetSymbolWidth(((WSHDR *)vd->work_ref.data)->wsbody[i],FONT_SMALL);
  cw+=8;
  if (cw > ScreenW() - MARGIN)
  {
    while (cw > ScreenW() - MARGIN)
    {
      cw -= GetSymbolWidth(((WSHDR *)vd->work_ref.data)->wsbody[datalen--],FONT_SMALL);
    }
    ((WSHDR *)vd->work_ref.data)->wsbody[0] = datalen;
    ((WSHDR *)vd->work_ref.data)->wsbody[datalen--] = 0x002E; // "."
    ((WSHDR *)vd->work_ref.data)->wsbody[datalen--] = 0x002E;
    ((WSHDR *)vd->work_ref.data)->wsbody[datalen--] = 0x002E;
  }
  
  img=CreateButton(cw,GetFontYSIZE(FONT_SMALL)+6);
  if (img)
  {
    dpl=AddToDPngQueue(vd, img, DP_IS_NOINDEX);
    if (dpl)
      wchar=dpl->w_char;
  }
  RawInsertChar(vd,wchar);
}

void AddDropDownList(VIEWDATA *vd)
{
  if (!vd->WCHAR_LIST_FORM)
  {
    char * fname = getSymbolicPath("$resources\\list.png");
    vd->WCHAR_LIST_FORM=AddPictureItemFile(vd, fname);
    mfree(fname);
  }
  getUserListByRefId(vd->work_ref.id, &(vd->work_ref.value), &(vd->work_ref.id2));
  RawInsertChar(vd,vd->WCHAR_LIST_FORM);
}
