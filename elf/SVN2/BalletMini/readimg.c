#include "..\inc\swilib.h"
#include "jpeglib/jpeglib.h"
#include "jpeglib/jerror.h"
#include "readimg.h"

#define PNG_BYTES_TO_CHECK 8

typedef struct {
  const char *p;
  char *row;
  char *img;
  IMGHDR * img_h;
}PP;

void *xmalloc(int x,int n)
{
  return malloc(n);
}

void xmfree(int x,void* ptr)
{
  mfree(ptr);
}

void read_data_fn(png_structp png_ptr, png_bytep data, png_size_t length)
{
  PP *pp=png_get_io_ptr(png_ptr);
  memcpy(data,pp->p,length);
  pp->p+=length;
}


IMGHDR *read_pngimg(const char *buf)
{
  PP pp;
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

struct my_error_mgr {
  struct jpeg_error_mgr pub;	/* "public" fields */

  jmp_buf setjmp_buffer;	/* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;

extern void longjmp(jmp_buf, int);
METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
  my_error_ptr myerr = (my_error_ptr) cinfo->err;
  (*cinfo->err->output_message) (cinfo);
  longjmp(myerr->setjmp_buffer, 1);
}

const char jpg_hdr[]={0xFF, 0xD8};
IMGHDR *read_jpgimg(const char *buf)
{
  int img_w, img_h;
  struct jpeg_decompress_struct cinfo;
  struct my_error_mgr jerr;

  IMGHDR * img_hc;
  unsigned short *img, *iimg;
  JSAMPARRAY buffer;
  char *row;
  
  if (memcmp((void *)buf,(void *)jpg_hdr,sizeof(jpg_hdr))) return NULL;
  
  img=0;
  img_hc=0;
  buffer=0;
  zeromem(&cinfo,sizeof(struct jpeg_decompress_struct));
  zeromem(&jerr,sizeof(struct my_error_mgr));
  
  cinfo.err=jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;
  
  if (setjmp(jerr.setjmp_buffer))
  {
    jpeg_destroy_decompress(&cinfo);
    goto L_ERROR;
  }
  jpeg_create_decompress(&cinfo);
  
  jpeg_stdio_src(&cinfo, (void *)buf);
  jpeg_read_header(&cinfo, TRUE);
  jpeg_start_decompress(&cinfo);
  
  img_w=cinfo.output_width;
  img_h=cinfo.output_height;
  
  img_hc=malloc(sizeof(IMGHDR));
  iimg=img=malloc(img_w*img_h*sizeof(unsigned short));
  buffer = (*cinfo.mem->alloc_sarray)  
		((j_common_ptr) &cinfo, JPOOL_IMAGE, img_w*cinfo.output_components, 1);
  
  while (cinfo.output_scanline < img_h) 
  {
    jpeg_read_scanlines(&cinfo, buffer, 1);
    row=buffer[0];
    for (int x=0; x<img_w; x++)
    {
      unsigned int c;
      c=((row[0]<<8)&0xF800);
      c|=((row[1]<<3)&0x7E0);
      c|=((row[2]>>3)&0x1F);
      row+=3;
      *iimg++=c;
    }
  }
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  img_hc->bitmap=(char *)img;
  img_hc->bpnum=8;
  img_hc->w=img_w;
  img_hc->h=img_h;
  if (!img)
  {
  L_ERROR:
    mfree(img_hc);
    img_hc=NULL;
    mfree(img);
  } 
  return img_hc;
}

IMGHDR *ConvertRGBAToRGB8(const char *buf, int width, int height)
{
  IMGHDR * img_hc=malloc(sizeof(IMGHDR));
  unsigned short *iimg=malloc(width*height*sizeof(unsigned short));
  img_hc->w=width;
  img_hc->h=height;
  img_hc->bpnum=8;
  img_hc->bitmap=(char *)iimg;
  
  for (unsigned int y = 0; y<height; y++)
  {
    for (unsigned int x = 0; x<width; x++)
    {
      if (buf[y*width*4+x*4+0]<255)
        *iimg++=0xE000;
      else
      {
        unsigned int c=((buf[y*width*4+x*4+1]<<8)&0xF800);
        c|=((buf[y*width*4+x*4+2]<<3)&0x7E0);
        c|=((buf[y*width*4+x*4+3]>>3)&0x1F);
        *iimg++=c;
      }
    }
  }
  return (img_hc);
}

IMGHDR *CreateFrame(int width, int height, const char *color)
{
  int color_c;
  IMGHDR * img_hc=malloc(sizeof(IMGHDR));
  char *iimg=malloc(width*height);
  img_hc->w=width;
  img_hc->h=height;
  img_hc->bpnum=5;
  img_hc->bitmap=iimg;
  
  if (color[3]<50) color_c=0xC0;
  else
  {
    unsigned char c=color[0]&0xE0;
    c|=(color[1]>>3)&0x1C;
    c|=(color[2]>>6)&0x3;
    color_c=c;
  }
  for (unsigned int y = 0; y<height; y++)
  {
    for (unsigned int x = 0; x<width; x++)
    {
      if (x==0 || y==0 || x==width-1 || y==height-1)
        *iimg++=color_c;
      else
        *iimg++=0xC0;
    }
  }
  return (img_hc);  
}

IMGHDR *CreateDelimiter(int width, int height, const char *color)
{
  int color_c;
  IMGHDR * img_hc=malloc(sizeof(IMGHDR));
  char *iimg=malloc(width*height);
  img_hc->w=width;
  img_hc->h=height;
  img_hc->bpnum=5;
  img_hc->bitmap=iimg;
  
  if (color[3]<50) color_c=0xC0;
  else
  {
    unsigned char c=color[0]&0xE0;
    c|=color[1]&0x1C;
    c|=color[2]&0x3;
    color_c=c;
  }
  for (unsigned int y = 0; y<height; y++)
  {
    for (unsigned int x = 0; x<width; x++)
    {
      if (y==height>>1 && x>3 && x<(width-3))
        *iimg++=color_c;
      else
        *iimg++=0xC0;
    }
  }
  return (img_hc);  
}

IMGHDR *CreateButton(int width, int height)
{
#define RGB16(R, G, B) (((B>>3)&0x1F) | ((G<<3)&0x7E0) | ((R<<8)&0xF800))
  IMGHDR * img_hc=malloc(sizeof(IMGHDR));
  short *iimg=malloc(width*height*2);
  img_hc->w=width;
  img_hc->h=height;
  img_hc->bpnum=8;
  img_hc->bitmap=(char*)iimg;
  
  for (unsigned int y = 0; y<height; y++)
  {
    for (unsigned int x = 0; x<width; x++)
    {
     
      if ((y == 0)|| (y == (height-1))||(x==0)||(x==width-1))
      {
        *iimg++ = 0xE000; //transparent
        continue;
      }
      if ((y == 1)|| (y == (height-2))||(x==1)||(x==width-2))
      {
        *iimg++ = RGB16(88,92,88);
        continue;
      }
      if ((y==2)||(x==2))
      {
        *iimg++ = RGB16(248,252,248);
        continue;
      }
      if ((y == (height-3))||(x==width-3))
      {
        *iimg++ = RGB16(200,204,200);
        continue;
      }
      *iimg++ = RGB16(224,228,224);
    }
  }
  return (img_hc);  
}
