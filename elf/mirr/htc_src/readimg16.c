
#ifndef _SWILIB_H_
#include "swilib.h"
#define _SWILIB_H_
#endif

#include "readimg16.h"


#define PNG_BYTES_TO_CHECK 8

typedef struct {
  const char *p;
  char *row;
  char *img;
  IMGHDR * img_h;
}PP16;

void *xmalloc16(int x,int n)
{
  return malloc(n);
}

void xmfree16(int x,void* ptr)
{
  mfree(ptr);
}

void read_data_fn16(png_structp png_ptr, png_bytep data, png_size_t length)
{
  PP16 *pp=png_get_io_ptr(png_ptr);
  memcpy(data,pp->p,length);
  pp->p+=length;
}


IMGHDR *read_pngimg16(const char *buf)
{
  PP16 pp;
  IMGHDR * img_hc;
  png_structp png_ptr=NULL;
  png_infop info_ptr=NULL;
  png_uint_32 rowbytes;
  
  pp.p=buf;
  pp.row=NULL;
  pp.img=NULL;
  pp.img_h=NULL;  
  
  if  (!png_check_sig((png_bytep)pp.p,PNG_BYTES_TO_CHECK)) return 0; // не пнг
  pp.p+=PNG_BYTES_TO_CHECK;
  
  png_ptr = png_create_read_struct_2("1.2.5", (png_voidp)0, 0, 0, (png_voidp)0,(png_malloc_ptr)xmalloc16,(png_free_ptr)xmfree16);
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
//=====================================================================  
  png_set_read_fn(png_ptr, &pp, read_data_fn16);
  
  png_set_sig_bytes(png_ptr, PNG_BYTES_TO_CHECK);
  png_read_info(png_ptr, info_ptr);
  
  png_uint_32 width, height;
  int bit_depth, color_type;
  
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, 0, 0, 0);
  
  if (bit_depth < 8) png_set_gray_1_2_4_to_8(png_ptr);
    
  if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png_ptr); 
  
  if (bit_depth == 16) png_set_strip_16(png_ptr);
  
  if (bit_depth < 8) png_set_packing(png_ptr);
  
  if (color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png_ptr);
  
  if (color_type == PNG_COLOR_TYPE_GRAY_ALPHA || color_type == PNG_COLOR_TYPE_GRAY)
    png_set_gray_to_rgb(png_ptr);
  
  png_set_filler(png_ptr,0xFF,PNG_FILLER_AFTER);
  png_read_update_info(png_ptr, info_ptr);
  
  rowbytes = png_get_rowbytes(png_ptr, info_ptr);
  
  pp.row=malloc(rowbytes);
  pp.img_h=img_hc=malloc(sizeof(IMGHDR));
  
  {
    unsigned short *iimg=(unsigned short *)(pp.img=malloc(width*height*sizeof(unsigned short)));
    for (unsigned int y = 0; y<height; y++)
    {
      png_read_row(png_ptr, (png_bytep)pp.row, NULL);
      for (unsigned int x = 0; x<width; x++)
      {
        if (pp.row[x*4+3]<128)
          *iimg++=0xE000;
        else
        {
          unsigned int c=((pp.row[x*4+0]<<8)&0xF800);
          c|=((pp.row[x*4+1]<<3)&0x7E0);
          c|=((pp.row[x*4+2]>>3)&0x1F);
          *iimg++=c;
        }
      }
    }
  }
  pp.img_h->bpnum=8;
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


