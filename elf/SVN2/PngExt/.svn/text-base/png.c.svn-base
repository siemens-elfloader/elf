#include "pngext.h"

#define number 4


void* xmalloc(int x,int n)
{
  return malloc(n);
}

void xmfree(int x,void* n)
{
  mfree(n);
}

typedef struct
{
  int file_handler;
  unsigned int errno;
}READ_FILE;

 
void read_data_fn(png_structp png_ptr, png_bytep data, png_size_t length)
{
  READ_FILE*read;
  read=png_get_io_ptr(png_ptr);
  fread(read->file_handler, data, length, &read->errno);
}



IMGHDR* create_imghdr(const char* fname)
{
  READ_FILE read;
  char buf[number];
  if ((read.file_handler=fopen(fname, A_ReadOnly+A_BIN, P_READ, &read.errno))==-1) return 0;

  if (fread(read.file_handler, &buf, number, &read.errno)!=number)
  {
    fclose(read.file_handler, &read.errno);
    return 0;
  }
  
  //png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, (png_voidp)0, 0, 0);
  
    
  png_structp png_ptr = png_create_read_struct_2("1.2.5", (png_voidp)0, 0, 0, (png_voidp)0,(png_malloc_ptr)xmalloc,(png_free_ptr)xmfree);
  if (!png_ptr) return (0);
  
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
  {
    png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
    return (0);
  }
  
  png_infop end_info = png_create_info_struct(png_ptr);
  if (!end_info)
  {
    png_destroy_read_struct(&png_ptr, &info_ptr,(png_infopp)NULL);
    return (0);
  }
  
  if (setjmp(png_jmpbuf(png_ptr)))
  {
    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
    fclose(read.file_handler, &read.errno);
    return (0);
  }
  
  png_set_read_fn(png_ptr, &read, read_data_fn);
  
  png_set_sig_bytes(png_ptr, number);
  
  png_read_info(png_ptr, info_ptr);
  
  png_uint_32 width, height;
  int bit_depth, color_type;
  
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, 0, 0, 0);
  
  if (bit_depth == 16) png_set_strip_16(png_ptr);
  
  if (bit_depth < 8) png_set_packing(png_ptr);
  
  if (color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png_ptr);
  
  if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png_ptr);
  
  if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png_ptr);
  
  png_set_filler(png_ptr,0xFF,PNG_FILLER_AFTER);

    
  png_read_update_info(png_ptr, info_ptr);
  
  png_uint_32 rowbytes = png_get_rowbytes(png_ptr, info_ptr);
  
  char *row=malloc(rowbytes);
  char *img=malloc(width*height);
  
  for (unsigned int y = 0; y<height; y++)
  {
    png_read_row(png_ptr, (png_bytep)row, NULL);
    for (unsigned int x = 0; x<width; x++)
    {
      if (!row[x*4+3])
        img[x+y*width]=0xC0;
      else
        img[x+y*width]=(row[x*4+0] & 0xE0)|((row[x*4+1]>>3)&0x1C)|((row[x*4+2]>>6)&0x3);
    }
  }
  IMGHDR * img_h=malloc(sizeof(IMGHDR));
  img_h->w=width;
  img_h->h=height;
  img_h->bpnum=5;
  img_h->zero=0;
  img_h->bitmap=img;
  
  
  png_read_end(png_ptr, end_info);
  png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
  
  fclose(read.file_handler, &read.errno);
  mfree(row);
  
  return (img_h);
}


