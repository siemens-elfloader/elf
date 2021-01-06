

/****************************************************************************************************************************
iphone_saver.elf (readimg.c)
(с)Mirrr (http://init.org.ua, mirrr@ukr.net)
(с)2008 

Разрешается модифицировать и использовать по вашему усмотрению любой документ из архива,
при условиях:
 - не удаляйте копирайты и адрес сайта, а также данное соглашение из исходных кодов программы.
 - при модификации программы не удаляйте логотип сайта http://init.org.ua, отображаемый один раз при первом запуске эльфа.

Эта программа является свободно распространяемой; Вы можете распространять ее повторно и (или) изменять, 
соблюдая условия Открытого лицензионного соглашения GNU (GNU GPL), опубликованного Фондом свободно распространяемого 
программного обеспечения; либо редакции 2 Соглашения, либо (на ваше усмотрение) любой редакции, выпущенной позже.
Эта программа распространяется в надежде на то, что она окажется полезной, но БЕЗ КАКИХ-ЛИБО ГАРАНТИЙ, 
включая подразумеваемую гарантию КАЧЕСТВА либо ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. 

Подробности содержатся в Открытом лицензионном соглашении GNU.

Вместе с этой программой должен распространяться экземпляр Открытого лицензионного соглашения GNU, если он 
отсутствует, сообщите об этом в Фонд свободно распространяемого программного обеспечения 
(Free Software Foundation, Inc.), 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA 
***************************************************************************************************************************/
















short *screen;
#ifndef _SWILIB_H_
#include "swilib.h"
#define _SWILIB_H_
#endif

//#include "jpeglib/jpeglib.h"
//#include "jpeglib/jerror.h"
#include "readimg.h"

#define PNG_BYTES_TO_CHECK 8

//================================================================================================================================================
typedef struct {
  const char *p;
  char *row;
  char *img;
  IMGHDR * img_h;
}PP;
//================================================================================================================================================
void *xmalloc(int x,int n)
{
  return malloc(n);
}
//================================================================================================================================================
void xmfree(int x,void* ptr)
{
  mfree(ptr);
}
//================================================================================================================================================
void read_data_fn(png_structp png_ptr, png_bytep data, png_size_t length)
{
  PP *pp=png_get_io_ptr(png_ptr);
  memcpy(data,pp->p,length);
  pp->p+=length;
}
//================================================================================================================================================

IMGHDR *read_pngimg(const char *buf)
{
  PP pp;
  pp.p=buf;
  pp.row=NULL;
  pp.img=NULL;
  pp.img_h=NULL;  
  
  IMGHDR * img_hc;
  png_structp png_ptr=NULL;
  png_infop info_ptr=NULL;
  png_uint_32 rowbytes;
  

  
  if  (!png_check_sig((png_bytep)pp.p,PNG_BYTES_TO_CHECK)) return 0; // не пнг
  pp.p+=PNG_BYTES_TO_CHECK;
  
  png_ptr = png_create_read_struct_2("1.2.5", (png_voidp)0, 0, 0, (png_voidp)0,(png_malloc_ptr)xmalloc,(png_free_ptr)xmfree);
  if (!png_ptr) goto L_CLOSE_FILE;
  
  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
  {
    png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
    goto L_CLOSE_FILE;
  }
  
  if (setjmp(png_jmpbuf(png_ptr)))
  {
    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
    goto L_CLOSE_FILE;
  }
  
  png_set_read_fn(png_ptr, &pp, read_data_fn);
  
  png_set_sig_bytes(png_ptr, PNG_BYTES_TO_CHECK);
  png_read_info(png_ptr, info_ptr);
  
  png_uint_32 width, height;
  int bit_depth, color_type;
  
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, 0, 0, 0);
  
  if (bit_depth < 8) png_set_gray_1_2_4_to_8(png_ptr);
  if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))png_set_tRNS_to_alpha(png_ptr); 
  if (bit_depth == 16) png_set_strip_16(png_ptr);
  if (bit_depth < 8) png_set_packing(png_ptr);
  if (color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png_ptr);
  if (color_type == PNG_COLOR_TYPE_GRAY_ALPHA || color_type == PNG_COLOR_TYPE_GRAY) png_set_gray_to_rgb(png_ptr);
  
  png_set_filler(png_ptr,0xFF,PNG_FILLER_AFTER);
  png_read_update_info(png_ptr, info_ptr);
  
  rowbytes = png_get_rowbytes(png_ptr, info_ptr);
  
  pp.row=malloc(rowbytes);
  pp.img_h=img_hc=malloc(sizeof(IMGHDR));
  
  {
    int *iimg=(int *)(pp.img=malloc(width*height*sizeof(int)));
    for (unsigned int y = 0; y<height; y++)
    {
      png_read_row(png_ptr, (png_bytep)pp.row, NULL);
      for (unsigned int x = 0; x<width; x++)
      {
      int c= (pp.row[x*4+3]*0x1000000) + (pp.row[x*4+0]*0x10000) + (pp.row[x*4+1]*0x100) + (pp.row[x*4+2]);
      *iimg++=c;
      }
    }
  }
  pp.img_h->bpnum=0xA;
  pp.img_h->w=width;
  pp.img_h->h=height;
  pp.img_h->bitmap=pp.img;
  
  png_read_end(png_ptr, info_ptr);
  png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
  if (!pp.img)
  {
  L_CLOSE_FILE:
    mfree(pp.row);
    mfree(pp.img);
    mfree(pp.img_h);
    return NULL;
  }
  mfree(pp.row);
  return (img_hc);
}
//

IMGHDR *CreateImgr(int width, int height)
{
  int ensize;
  IMGHDR * img_hc=malloc(sizeof(IMGHDR));
  int *iimg=(int*)malloc(ensize=width*height*sizeof(int));
  img_hc->w=width;
  img_hc->h=height;
  img_hc->bpnum=0xA;
  img_hc->bitmap=(char*)iimg;
  memsetw(iimg,0xFF000000,ensize>>1);
  return (img_hc);  
}

IMGHDR *CreateImgr16(int width, int height)
{
  int ensize;
  IMGHDR * img_hc=malloc(sizeof(IMGHDR));
  short *iimg=(short*)malloc(ensize=width*height*sizeof(short));
  img_hc->w=width;
  img_hc->h=height;
  img_hc->bpnum=8;
  img_hc->bitmap=(char*)iimg;
  memsetw(iimg,0xFF000000,ensize>>1);
  return (img_hc);  
}


