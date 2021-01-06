

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


#define RGB16_1(R,G,B) ((B>>3)+((G>>2)<<5)+((R>>3)<<11))
#define RGB16_2(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))

#ifndef _SWILIB_H_
#include "swilib.h"
#define _SWILIB_H_
#endif
#include "readimg.h"
//#include "D:\ELF\arm\BalletMini\jpeglib\jpeglib.h"
#include "jpeglib/jpeglib.h"
#include "jpeglib/jerror.h"


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


char SAVE_PATH[128]="0:\\";
void getname(char *dest, const char *ext)
{
  TTime t;
  TDate d;
  GetDateTime(&d,&t);

  char curname[20];
  sprintf(curname, "%02d%02d%02d_%02d%02d%02d.",
          d.year, d.month, d.day, t.hour, t.min, t.sec);

  
  strcpy(dest, SAVE_PATH);
  strcat(dest, strcat(curname, ext)+2);
}

// RGB16_1(R,G,B) ((B>>3)+((G>>2)<<5)+((R>>3)<<11))
/*
void save_jpg( IMGHDR * img1, int JPG_QUAL,  char *fname)
{
  int f;
  unsigned int ul;
  
  
  int scrW = img1->w;
  int scrH = img1->h;
 

  short *tz;
  tz = malloc (img1->w*img1->h*2);  
  for (int i=0; i<img1->w*img1->h; i++){
  tz[i] = RGB16_1((img1->bitmap[i*4+2]),(img1->bitmap[i*4+1]),(img1->bitmap[i*4]));  
  }  
  
  
char *mybuf =(char *)tz; 



  if ((f=fopen(fname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
  {
    jpeg_compress_struct cinfo;
    jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, f);
    cinfo.image_width = scrW;
    cinfo.image_height = scrH;
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, JPG_QUAL, TRUE);
//    cinfo.optimize_coding=TRUE;
//    if(JPG_PR)
      jpeg_simple_progression(&cinfo); //ЧЕ-ТО Я НАКУРАЛЕСИЛ
    jpeg_start_compress(&cinfo, TRUE);
    int row_stride = cinfo.image_width * 2; // JSAMPLEs per row in image_buffer
    JSAMPROW row_pointer[1];
    
    while (cinfo.next_scanline < cinfo.image_height)
    {
//      if(cinfo.global_state==0)
      row_pointer[0] = & mybuf[cinfo.next_scanline * row_stride];
      jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }
    jpeg_finish_compress(&cinfo);
    fclose(f, &ul);
    jpeg_destroy((j_common_ptr)&cinfo);
  }


}
*/

struct my_error_mgr {
  struct jpeg_error_mgr pub;	// "public" fields 

  jmp_buf setjmp_buffer;	// for return to caller 
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
IMGHDR *read_jpgimg(const char *buf, int mod)
{
  int img_w, img_h;
  struct jpeg_decompress_struct cinfo;
  struct my_error_mgr jerr;

  IMGHDR * img_hc;
  unsigned int *img, *iimg;
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
  iimg=img=malloc(img_w*img_h*sizeof(int));
  buffer = (*cinfo.mem->alloc_sarray)  
		((j_common_ptr) &cinfo, JPOOL_IMAGE, img_w*cinfo.output_components, 1);
  
  while (cinfo.output_scanline < img_h) 
  {
    jpeg_read_scanlines(&cinfo, buffer, 1);
    row=buffer[0];
    for (int x=0; x<img_w; x++)
    {
       unsigned int c;
       if (mod==0) c= (255*0x1000000) + ((row[x*3+0])*0x10000) + ((row[x*3+1])*0x100) + ((row[x*3+2]));
       if (mod==1) c= (255*0x1000000) + ((255-row[x*3+0])*0x10000) + ((255-row[x*3+1])*0x100) + ((255-row[x*3+2]));
      *iimg++=c;
      
      
    }
  }
  
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  img_hc->bitmap=(char *)img;
  img_hc->bpnum=10;
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
/*
void RGB_rot(int phi)
{
      int x0,y0,x1,y1;
      int sn=sin(phi);
      int cs=cos(phi);
      short с=RGB16(0,0,0);
      
      for (y1=0;y1<TH;y1++)
      {
        for (x1=0;x1<TW;x1++)
          {
            memcpy(img_data+((y1*TW+x1)*2),&c,2);
            x0 = (int) ((cs * (x1 - xc) + sn * (y1 - yc)) /1000 + xc)+Pxc; //ось иксов
            y0 = (int) (-(sn * (x1 - xc) - cs * (y1 - yc)) /1000+ yc)+Pyc; //ось игреков
            int source= (y0*TW+x0)*2;
            int dest  = (y1*TW+x1)*2;
            if (x0>-1 && x0<TW && y0>-1 && y0<TH)
            {
             memcpy((img_data+dest),(bitbuf+source),2);
            }
          }
      }
}
*/
