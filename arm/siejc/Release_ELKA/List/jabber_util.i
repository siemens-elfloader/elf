 





typedef long time_t;


typedef int jmp_buf[11];

























































































































































 


























































































 









 




 







 























































 






 

 


 

 


 

 






 

 




























 





 

 





 





 




 

 





 












 

                         







 





typedef unsigned char  Byte;   
typedef unsigned int   uInt;   
typedef unsigned long  uLong;  

   typedef Byte   Bytef;
typedef char   charf;
typedef int    intf;
typedef uInt   uIntf;
typedef uLong  uLongf;

   typedef void const *voidpc;
   typedef void    *voidpf;
   typedef void       *voidp;




 




































 

typedef voidpf (*alloc_func) (voidpf opaque, uInt items, uInt size);
typedef void   (*free_func)  (voidpf opaque, voidpf address);

struct internal_state;

typedef struct z_stream_s {
    Bytef    *next_in;   
    uInt     avail_in;   
    uLong    total_in;   

    Bytef    *next_out;  
    uInt     avail_out;  
    uLong    total_out;  

    char     *msg;       
    struct internal_state  *state;  

    alloc_func zalloc;   
    free_func  zfree;    
    voidpf     opaque;   

    int     data_type;   
    uLong   adler;       
    uLong   reserved;    
} z_stream;

typedef z_stream  *z_streamp;




 
typedef struct gz_header_s {
    int     text;        
    uLong   time;        
    int     xflags;      
    int     os;          
    Bytef   *extra;      
    uInt    extra_len;   
    uInt    extra_max;   
    Bytef   *name;       
    uInt    name_max;    
    Bytef   *comment;    
    uInt    comm_max;    
    int     hcrc;        
    int     done;       
 
} gz_header;

typedef gz_header  *gz_headerp;































 

                         

 



 

 

 

 

 


 

                         

extern const char *  zlibVersion (void);




 





















 


extern int  deflate (z_streamp strm, int flush);


















































































 


extern int  deflateEnd (z_streamp strm);










 




















 


































































































 











 

                         



 


























































 

extern int  deflateSetDictionary (z_streamp strm, const Bytef *dictionary, uInt dictLength);


































 

extern int  deflateCopy (z_streamp dest, z_streamp source);














 

extern int  deflateReset (z_streamp strm);








 

extern int  deflateParams (z_streamp strm, int level, int strategy);
















 

extern int  deflateTune (z_streamp strm, int good_length, int max_lazy, int nice_length, int max_chain);










 

extern uLong  deflateBound (z_streamp strm, uLong sourceLen);





 

extern int  deflatePrime (z_streamp strm, int bits, int value);











 

extern int  deflateSetHeader (z_streamp strm, gz_headerp head);




















 










































 

extern int  inflateSetDictionary (z_streamp strm, const Bytef *dictionary, uInt dictLength);

















 

extern int  inflateSync (z_streamp strm);












 

extern int  inflateCopy (z_streamp dest, z_streamp source);












 

extern int  inflateReset (z_streamp strm);







 

extern int  inflatePrime (z_streamp strm, int bits, int value);











 

extern int  inflateGetHeader (z_streamp strm, gz_headerp head);




































 





















 

typedef unsigned (*in_func) (void *, unsigned char * *);
typedef int (*out_func) (void *, unsigned char *, unsigned);

extern int  inflateBack (z_streamp strm, in_func in, void *in_desc, out_func out, void *out_desc);
































































 

extern int  inflateBackEnd (z_streamp strm);





 

extern uLong  zlibCompileFlags (void);






































 


                         







 

extern int  compress (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen);











 

extern int  compress2 (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen, int level);











 

extern uLong  compressBound (uLong sourceLen);




 

extern int  uncompress (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen);














 


typedef voidp gzFile;

extern gzFile  gzopen  (const char *path, const char *mode);














 

extern gzFile  gzdopen  (int fd, const char *mode);










 

extern int  gzsetparams (gzFile file, int level, int strategy);





 

extern int     gzread  (gzFile file, voidp buf, unsigned len);





 

extern int     gzwrite (gzFile file, voidpc buf, unsigned len);




 

extern int    gzprintf (gzFile file, const char *format, ...);










 

extern int  gzputs (gzFile file, const char *s);




 

extern char *  gzgets (gzFile file, char *buf, int len);






 

extern int     gzputc (gzFile file, int c);



 

extern int     gzgetc (gzFile file);



 

extern int     gzungetc (int c, gzFile file);







 

extern int     gzflush (gzFile file, int flush);







 

extern long     gzseek (gzFile file, long offset, int whence);














 

extern int     gzrewind (gzFile file);




 

extern long     gztell (gzFile file);






 

extern int  gzeof (gzFile file);



 

extern int  gzdirect (gzFile file);



 

extern int     gzclose (gzFile file);




 

extern const char *  gzerror (gzFile file, int *errnum);






 

extern void  gzclearerr (gzFile file);




 

                         





 

extern uLong  adler32 (uLong adler, const Bytef *buf, uInt len);













 

extern uLong  adler32_combine (uLong adler1, uLong adler2, long len2);





 

extern uLong  crc32   (uLong crc, const Bytef *buf, uInt len);













 

extern uLong  crc32_combine (uLong crc1, uLong crc2, long len2);







 


                         



 
extern int  deflateInit_ (z_streamp strm, int level, const char *version, int stream_size);
extern int  inflateInit_ (z_streamp strm, const char *version, int stream_size);
extern int  deflateInit2_ (z_streamp strm, int level, int method, int windowBits, int memLevel, int strategy, const char *version, int stream_size);

 
extern int  inflateBackInit_ (z_streamp strm, int windowBits, unsigned char *window, const char *version, int stream_size);


    struct internal_state {int dummy;};  

extern const char   *  zError           (int);
extern int             inflateSyncPoint (z_streamp z);
extern const uLongf *  get_crc_table    (void);



 








 





 






 

 




















 




 












 


 


 



 









 

































 











 










 






 

 





 


    





 




 














 

 









 






 







 


 





               




 








 




















 


 





 


 



 

 

 






 

 
 




 

 


 

 



 





 












 

 
      
 

#pragma system_include

 
 





 

#pragma system_include




                 



                 










 




                 






























 


#pragma system_include

 
 
 


 

 

 

 

   

 

  #pragma system_include





 






 














 





















 










 




















































































































 


 










 





















 














 















 













 








 












 











 










 









 











 









 









 









 









 














 














 
















 












 








 











 










 









 









 









 









 









 









 









 





 






 







































 













 







                 

                 
 
 



                 





 



                 

                 

                 

                 

 
 


  #pragma system_include


                                 









                 
                                 


  typedef long long _Longlong;
  typedef unsigned long long _ULonglong;

  typedef unsigned short int _Wchart;
  typedef unsigned short int _Wintt;



                 

typedef signed int  _Ptrdifft;
typedef unsigned int     _Sizet;

                 

                 

  typedef struct
  {
    char  *_Ap;
  } __Va_list;

                 


__intrinsic void _Atexit(void (*)(void));


typedef struct _Mbstatet
{        
  unsigned long _Wchar;
  unsigned short _Byte, _State;
} _Mbstatet;

                 


typedef struct _Fpost
{        
  long _Off;     
  _Mbstatet _Wstate;
} _Fpost;



                 
 


                 
















 


#pragma system_include



























































 

 


   


  
  typedef void *_Rmtx;

   
  __intrinsic void _Mtxinit(_Rmtx *m);
  __intrinsic void _Mtxdst(_Rmtx *m);
  __intrinsic void _Mtxlock(_Rmtx *m);
  __intrinsic void _Mtxunlock(_Rmtx *m);

  




  


  typedef unsigned _Once_t;

  








                 


                 
  
  
  __intrinsic void _Locksyslock(unsigned int);
  __intrinsic void _Unlocksyslock(unsigned int);
  
  


                 


                 
 


#pragma inline
static char _LC(char _C)
{   
  return ((_C) | ('a' - 'A'));
}






 
 
 


#pragma system_include



                 
typedef _Sizet size_t;

typedef unsigned int __data_size_t;






                 


                 
  typedef long clock_t;

  

struct tm
{        
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
};

        



      
__intrinsic char * asctime(const struct tm *);
__intrinsic clock_t clock(void);





__intrinsic size_t strftime(char *, size_t, const char *,
        const struct tm *);







 








 

typedef unsigned long png_uint_32;
typedef long png_int_32;
typedef unsigned short png_uint_16;
typedef short png_int_16;
typedef unsigned char png_byte;


 
   typedef size_t png_size_t;








 


 





 

 

 

 


 
typedef png_int_32 png_fixed_point;

 
typedef void             * png_voidp;
typedef png_byte         * png_bytep;
typedef png_uint_32      * png_uint_32p;
typedef png_int_32       * png_int_32p;
typedef png_uint_16      * png_uint_16p;
typedef png_int_16       * png_int_16p;
typedef const char   * png_const_charp;
typedef char             * png_charp;
typedef png_fixed_point  * png_fixed_point_p;


typedef double           * png_doublep;

 
typedef png_byte         *  * png_bytepp;
typedef png_uint_32      *  * png_uint_32pp;
typedef png_int_32       *  * png_int_32pp;
typedef png_uint_16      *  * png_uint_16pp;
typedef png_int_16       *  * png_int_16pp;
typedef const char   *  * png_const_charpp;
typedef char             *  * png_charpp;
typedef png_fixed_point  *  * png_fixed_point_pp;
typedef double           *  * png_doublepp;

 
typedef char             *  *  * png_charppp;

 
 



 
typedef charf *         png_zcharp;
typedef charf *  *   png_zcharpp;
typedef z_stream  *  png_zstreamp;

















 




 




 







 










 



 



 

 

 



 









 



 





 


 


 
extern  const char png_libpng_ver[18];
   

 
 
extern  const int png_pass_start[7];
extern  const int png_pass_inc[7];
extern  const int png_pass_ystart[7];
extern  const int png_pass_yinc[7];
extern  const int png_pass_mask[7];
extern  const int png_pass_dsp_mask[7];


 





 
typedef struct png_color_struct
{
   png_byte red;
   png_byte green;
   png_byte blue;
} png_color;
typedef png_color  * png_colorp;
typedef png_color  *  * png_colorpp;

typedef struct png_color_16_struct
{
   png_byte index;     
   png_uint_16 red;    
   png_uint_16 green;
   png_uint_16 blue;
   png_uint_16 gray;   
} png_color_16;
typedef png_color_16  * png_color_16p;
typedef png_color_16  *  * png_color_16pp;

typedef struct png_color_8_struct
{
   png_byte red;    
   png_byte green;
   png_byte blue;
   png_byte gray;   
   png_byte alpha;  
} png_color_8;
typedef png_color_8  * png_color_8p;
typedef png_color_8  *  * png_color_8pp;




 
typedef struct png_sPLT_entry_struct
{
   png_uint_16 red;
   png_uint_16 green;
   png_uint_16 blue;
   png_uint_16 alpha;
   png_uint_16 frequency;
} png_sPLT_entry;
typedef png_sPLT_entry  * png_sPLT_entryp;
typedef png_sPLT_entry  *  * png_sPLT_entrypp;




 

typedef struct png_sPLT_struct
{
   png_charp name;            
   png_byte depth;            
   png_sPLT_entryp entries;   
   png_int_32 nentries;       
} png_sPLT_t;
typedef png_sPLT_t  * png_sPLT_tp;
typedef png_sPLT_t  *  * png_sPLT_tpp;








 
typedef struct png_text_struct
{
   int  compression;       



 
   png_charp key;           
   png_charp text;         
 
   png_size_t text_length;  
} png_text;
typedef png_text  * png_textp;
typedef png_text  *  * png_textpp;


 






 
typedef struct png_time_struct
{
   png_uint_16 year;  
   png_byte month;    
   png_byte day;      
   png_byte hour;     
   png_byte minute;   
   png_byte second;   
} png_time;
typedef png_time  * png_timep;
typedef png_time  *  * png_timepp;





 
typedef struct png_unknown_chunk_t
{
    png_byte name[5];
    png_byte *data;
    png_size_t size;

     
    png_byte location;  
}
png_unknown_chunk;
typedef png_unknown_chunk  * png_unknown_chunkp;
typedef png_unknown_chunk  *  * png_unknown_chunkpp;







































 
typedef struct png_info_struct
{
    
   png_uint_32 width;        
   png_uint_32 height;       
   png_uint_32 valid;        
   png_uint_32 rowbytes;     
   png_colorp palette;       
   png_uint_16 num_palette;  
   png_uint_16 num_trans;    
   png_byte bit_depth;       
   png_byte color_type;      
    
   png_byte compression_type;  
   png_byte filter_type;     
   png_byte interlace_type;  

    
   png_byte channels;        
   png_byte pixel_depth;     
   png_byte spare_byte;      
   png_byte signature[8];    

   



 

   


 
   float gamma;  

     
     
   png_byte srgb_intent;  

   






 
   int num_text;  
   int max_text;  
   png_textp text;  

   

 
   png_time mod_time;

   




 
   png_color_8 sig_bit;  

   







 
   png_bytep trans;  
   png_color_16 trans_values;  

   




 
   png_color_16 background;

   



 
   png_int_32 x_offset;  
   png_int_32 y_offset;  
   png_byte offset_unit_type;  

   


 
   png_uint_32 x_pixels_per_unit;  
   png_uint_32 y_pixels_per_unit;  
   png_byte phys_unit_type;  

   




 
   png_uint_16p hist;

   




 
   float x_white;
   float y_white;
   float x_red;
   float y_red;
   float x_green;
   float y_green;
   float x_blue;
   float y_blue;

   









 
   png_charp pcal_purpose;   
   png_int_32 pcal_X0;       
   png_int_32 pcal_X1;       
   png_charp pcal_units;     
   png_charpp pcal_params;   
   png_byte pcal_type;       
   png_byte pcal_nparams;    

 
   png_uint_32 free_me;      

    
   png_unknown_chunkp unknown_chunks;
   png_size_t unknown_chunks_num;

    
   png_charp iccp_name;      
   png_charp iccp_profile;   
                             
   png_uint_32 iccp_proflen;   
   png_byte iccp_compression;  

    
   png_sPLT_tp splt_palettes;
   png_uint_32 splt_palettes_num;

   





 
   png_byte scal_unit;          
   double scal_pixel_width;     
   double scal_pixel_height;    
   png_charp scal_s_width;      
   png_charp scal_s_height;     

    
    
   png_bytepp row_pointers;         

   png_fixed_point int_gamma;  

   png_fixed_point int_x_white;
   png_fixed_point int_y_white;
   png_fixed_point int_x_red;
   png_fixed_point int_y_red;
   png_fixed_point int_x_green;
   png_fixed_point int_y_green;
   png_fixed_point int_x_blue;
   png_fixed_point int_y_blue;

} png_info;

typedef png_info  * png_infop;
typedef png_info  *  * png_infopp;

 
 

 
 

 
 

 

 

 

 

 

 

 

 

 

 





 




 
typedef struct png_row_info_struct
{
   png_uint_32 width;  
   png_uint_32 rowbytes;  
   png_byte color_type;  
   png_byte bit_depth;  
   png_byte channels;  
   png_byte pixel_depth;  
} png_row_info;

typedef png_row_info  * png_row_infop;
typedef png_row_info  *  * png_row_infopp;






 
typedef struct png_struct_def png_struct;
typedef png_struct  * png_structp;

typedef void ( *png_error_ptr) (png_structp, png_const_charp);
typedef void ( *png_rw_ptr) (png_structp, png_bytep, png_size_t);
typedef void ( *png_flush_ptr) (png_structp);
typedef void ( *png_read_status_ptr) (png_structp, png_uint_32, int);
typedef void ( *png_write_status_ptr) (png_structp, png_uint_32, int);

typedef void ( *png_progressive_info_ptr) (png_structp, png_infop);
typedef void ( *png_progressive_end_ptr) (png_structp, png_infop);
typedef void ( *png_progressive_row_ptr) (png_structp, png_bytep, png_uint_32, int);

typedef void ( *png_user_transform_ptr) (png_structp, png_row_infop, png_bytep);

typedef int ( *png_user_chunk_ptr) (png_structp, png_unknown_chunkp);
typedef void ( *png_unknown_chunk_ptr) (png_structp);

 

 

typedef png_voidp (*png_malloc_ptr) (png_structp, png_size_t);
typedef void (*png_free_ptr) (png_structp, png_voidp);






 

struct png_struct_def
{
   jmp_buf jmpbuf;             
   png_error_ptr error_fn;     
   png_error_ptr warning_fn;   
   png_voidp error_ptr;        
   png_rw_ptr write_data_fn;   
   png_rw_ptr read_data_fn;    
   png_voidp io_ptr;           

   png_user_transform_ptr read_user_transform_fn;  

   png_user_transform_ptr write_user_transform_fn;  

 
   png_voidp user_transform_ptr;  
   png_byte user_transform_depth;     
   png_byte user_transform_channels;  

   png_uint_32 mode;           
   png_uint_32 flags;          
   png_uint_32 transformations;  

   z_stream zstream;           
   png_bytep zbuf;             
   png_size_t zbuf_size;       
   int zlib_level;             
   int zlib_method;            
   int zlib_window_bits;       
   int zlib_mem_level;         
   int zlib_strategy;          

   png_uint_32 width;          
   png_uint_32 height;         
   png_uint_32 num_rows;       
   png_uint_32 usr_width;      
   png_uint_32 rowbytes;       
   png_uint_32 irowbytes;      
   png_uint_32 iwidth;         
   png_uint_32 row_number;     
   png_bytep prev_row;         
   png_bytep row_buf;          
   png_bytep sub_row;          
   png_bytep up_row;           
   png_bytep avg_row;          
   png_bytep paeth_row;        
   png_row_info row_info;      

   png_uint_32 idat_size;      
   png_uint_32 crc;            
   png_colorp palette;         
   png_uint_16 num_palette;    
   png_uint_16 num_trans;      
   png_byte chunk_name[5];     
   png_byte compression;       
   png_byte filter;            
   png_byte interlaced;        
   png_byte pass;              
   png_byte do_filter;         
   png_byte color_type;        
   png_byte bit_depth;         
   png_byte usr_bit_depth;     
   png_byte pixel_depth;       
   png_byte channels;          
   png_byte usr_channels;      
   png_byte sig_bytes;         

   png_uint_16 filler;            

   png_byte background_gamma_type;
   float background_gamma;
   png_color_16 background;    
   png_color_16 background_1;  

   png_flush_ptr output_flush_fn; 
   png_uint_32 flush_dist;     
   png_uint_32 flush_rows;     

   int gamma_shift;       
   float gamma;           
   float screen_gamma;    

   png_bytep gamma_table;      
   png_bytep gamma_from_1;     
   png_bytep gamma_to_1;       
   png_uint_16pp gamma_16_table;  
   png_uint_16pp gamma_16_from_1;  
   png_uint_16pp gamma_16_to_1;  

   png_color_8 sig_bit;        

   png_color_8 shift;          

   png_bytep trans;            
   png_color_16 trans_values;  

   png_read_status_ptr read_row_fn;    
   png_write_status_ptr write_row_fn;  
   png_progressive_info_ptr info_fn;  
   png_progressive_row_ptr row_fn;    
   png_progressive_end_ptr end_fn;    
   png_bytep save_buffer_ptr;         
   png_bytep save_buffer;             
   png_bytep current_buffer_ptr;      
   png_bytep current_buffer;          
   png_uint_32 push_length;           
   png_uint_32 skip_length;           
   png_size_t save_buffer_size;       
   png_size_t save_buffer_max;        
   png_size_t buffer_size;            
   png_size_t current_buffer_size;    
   int process_mode;                  
   int cur_palette;                   

     png_size_t current_text_size;    
     png_size_t current_text_left;    
     png_charp current_text;          
     png_charp current_text_ptr;      



   png_bytep palette_lookup;          
   png_bytep dither_index;            

   png_uint_16p hist;                 

   png_byte heuristic_method;         
   png_byte num_prev_filters;         
   png_bytep prev_filters;            
   png_uint_16p filter_weights;       
   png_uint_16p inv_filter_weights;   
   png_uint_16p filter_costs;         
   png_uint_16p inv_filter_costs;     


 

   png_uint_32 free_me;        

   png_voidp user_chunk_ptr;
   png_user_chunk_ptr read_user_chunk_fn;  

   int num_chunk_list;
   png_bytep chunk_list;

 
   png_byte rgb_to_gray_status;
    
   png_uint_16 rgb_to_gray_red_coeff;
   png_uint_16 rgb_to_gray_green_coeff;
   png_uint_16 rgb_to_gray_blue_coeff;

 
 
   png_uint_32 mng_features_permitted;

 
   png_fixed_point int_gamma;

 
   png_byte filter_type;


 
   png_byte     mmx_bitdepth_threshold;
   png_uint_32  mmx_rowbytes_threshold;
   png_uint_32  asm_flags;

 
   png_voidp mem_ptr;                 
   png_malloc_ptr malloc_fn;          
   png_free_ptr free_fn;              

 
   png_bytep big_row_buf;          

 
   png_bytep dither_sort;             
   png_bytep index_to_palette;        
                                      
   png_bytep palette_to_index;        
                                      

 
   png_byte compression_type;

   png_uint_32 user_width_max;
   png_uint_32 user_height_max;

};




 
typedef png_structp version_1_2_12;

typedef png_struct  *  * png_structpp;





 

 
extern  png_uint_32  png_access_version_number (void);



 







 
extern  int  png_sig_cmp (png_bytep sig, png_size_t start, png_size_t num_to_check);



 


 




 
extern  png_structp  png_create_write_struct
   (png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn);

extern  png_uint_32  png_get_compression_buffer_size
   (png_structp png_ptr);

extern  void  png_set_compression_buffer_size
   (png_structp png_ptr, png_uint_32 size);

 
extern  int  png_reset_zstream (png_structp png_ptr);

 




extern  png_structp  png_create_write_struct_2
   (png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn, png_voidp mem_ptr, png_malloc_ptr malloc_fn, png_free_ptr free_fn);

 
extern  void  png_write_chunk (png_structp png_ptr, png_bytep chunk_name, png_bytep data, png_size_t length);

 
extern  void  png_write_chunk_start (png_structp png_ptr, png_bytep chunk_name, png_uint_32 length);

 
extern  void  png_write_chunk_data (png_structp png_ptr, png_bytep data, png_size_t length);

 
extern  void  png_write_chunk_end (png_structp png_ptr);

 



 
extern  void  png_info_init (png_infop info_ptr);

extern  void  png_info_init_3 (png_infopp info_ptr, png_size_t png_info_struct_size);

 
extern  void  png_write_info_before_PLTE (png_structp png_ptr, png_infop info_ptr);
extern  void  png_write_info (png_structp png_ptr, png_infop info_ptr);

 




 
 
#pragma diag_suppress=Pe231
extern  void  png_convert_from_struct_tm (png_timep ptime, struct tm * ttime);
#pragma diag_default=Pe231

 
extern  void  png_convert_from_time_t (png_timep ptime, time_t ttime);

 
extern  void  png_set_expand (png_structp png_ptr);
extern  void  png_set_expand_gray_1_2_4_to_8 (png_structp png_ptr);


 


 
extern  void  png_set_bgr (png_structp png_ptr);

 


 
extern  void  png_set_rgb_to_gray (png_structp png_ptr, int error_action, double red, double green );
extern  void  png_set_rgb_to_gray_fixed (png_structp png_ptr, int error_action, png_fixed_point red, png_fixed_point green );
extern  png_byte  png_get_rgb_to_gray_status (png_structp png_ptr);

extern  void  png_build_grayscale_palette (int bit_depth, png_colorp palette);

extern  void  png_set_strip_alpha (png_structp png_ptr);

extern  void  png_set_swap_alpha (png_structp png_ptr);

extern  void  png_set_invert_alpha (png_structp png_ptr);

 


 
 
extern  void  png_set_add_alpha (png_structp png_ptr, png_uint_32 filler, int flags);

 
extern  void  png_set_swap (png_structp png_ptr);

 


 
extern  void  png_set_packswap (png_structp png_ptr);

 
extern  void  png_set_shift (png_structp png_ptr, png_color_8p true_bits);

 
extern  int  png_set_interlace_handling (png_structp png_ptr);

 


 
extern  void  png_set_background (png_structp png_ptr, png_color_16p background_color, int background_gamma_code, int need_expand, double background_gamma);

 


 
extern  void  png_set_dither (png_structp png_ptr, png_colorp palette, int num_palette, int maximum_colors, png_uint_16p histogram, int full_dither);

 
extern  void  png_set_gamma (png_structp png_ptr, double screen_gamma, double default_file_gamma);

 
 
extern  void  png_permit_empty_plte (png_structp png_ptr, int empty_plte_permitted);

 
extern  void  png_set_flush (png_structp png_ptr, int nrows);
 
extern  void  png_write_flush (png_structp png_ptr);

 
extern  void  png_start_read_image (png_structp png_ptr);

 



 
extern  void  png_read_rows (png_structp png_ptr, png_bytepp row, png_bytepp display_row, png_uint_32 num_rows);

 




 



 
extern  void  png_write_row (png_structp png_ptr, png_bytep row);

 
extern  void  png_write_rows (png_structp png_ptr, png_bytepp row, png_uint_32 num_rows);

 
extern  void  png_write_image (png_structp png_ptr, png_bytepp image);

 
extern  void  png_write_end (png_structp png_ptr, png_infop info_ptr);

 



 
extern  void  png_destroy_info_struct (png_structp png_ptr, png_infopp info_ptr_ptr);

 



 
extern void png_read_destroy (png_structp png_ptr, png_infop info_ptr, png_infop end_info_ptr);

 
extern  void  png_destroy_write_struct
   (png_structpp png_ptr_ptr, png_infopp info_ptr_ptr);

 
extern void png_write_destroy (png_structp png_ptr);

 
extern  void  png_set_crc_action (png_structp png_ptr, int crit_action, int ancil_action);









 







 



 
extern  void  png_set_filter (png_structp png_ptr, int method, int filters);





 



 




























 
extern  void  png_set_filter_heuristics (png_structp png_ptr, int heuristic_method, int num_weights, png_doublep filter_weights, png_doublep filter_costs);



 







 
extern  void  png_set_compression_level (png_structp png_ptr, int level);

extern  void  png_set_compression_mem_level
   (png_structp png_ptr, int mem_level);

extern  void  png_set_compression_strategy
   (png_structp png_ptr, int strategy);

extern  void  png_set_compression_window_bits
   (png_structp png_ptr, int window_bits);

extern  void  png_set_compression_method (png_structp png_ptr, int method);








 








 

extern  void  png_set_error_fn (png_structp png_ptr, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warning_fn);

 
extern  png_voidp  png_get_error_ptr (png_structp png_ptr);





 
extern  void  png_set_write_fn (png_structp png_ptr, png_voidp io_ptr, png_rw_ptr write_data_fn, png_flush_ptr output_flush_fn);

 



 


extern  void  png_set_read_status_fn (png_structp png_ptr, png_read_status_ptr read_row_fn);

extern  void  png_set_write_status_fn (png_structp png_ptr, png_write_status_ptr write_row_fn);

 
extern  void  png_set_mem_fn (png_structp png_ptr, png_voidp mem_ptr, png_malloc_ptr malloc_fn, png_free_ptr free_fn);
 
extern  png_voidp  png_get_mem_ptr (png_structp png_ptr);

extern  void  png_set_read_user_transform_fn (png_structp png_ptr, png_user_transform_ptr read_user_transform_fn);

extern  void  png_set_write_user_transform_fn (png_structp png_ptr, png_user_transform_ptr write_user_transform_fn);

extern  void  png_set_user_transform_info (png_structp png_ptr, png_voidp user_transform_ptr, int user_transform_depth, int user_transform_channels);
 
extern  png_voidp  png_get_user_transform_ptr
   (png_structp png_ptr);

extern  void  png_set_read_user_chunk_fn (png_structp png_ptr, png_voidp user_chunk_ptr, png_user_chunk_ptr read_user_chunk_fn);
extern  png_voidp  png_get_user_chunk_ptr (png_structp png_ptr);



 
extern  void  png_set_progressive_read_fn (png_structp png_ptr, png_voidp progressive_ptr, png_progressive_info_ptr info_fn, png_progressive_row_ptr row_fn, png_progressive_end_ptr end_fn);

 
extern  png_voidp  png_get_progressive_ptr
   (png_structp png_ptr);

 
extern  void  png_process_data (png_structp png_ptr, png_infop info_ptr, png_bytep buffer, png_size_t buffer_size);



 
extern  void  png_progressive_combine_row (png_structp png_ptr, png_bytep old_row, png_bytep new_row);




 
extern  png_voidp  png_malloc_warn (png_structp png_ptr, png_uint_32 size);

 
extern  void  png_free (png_structp png_ptr, png_voidp ptr);


 
extern  void  png_free_data (png_structp png_ptr, png_infop info_ptr, png_uint_32 free_me, int num);

 
extern  void  png_data_freer (png_structp png_ptr, png_infop info_ptr, int freer, png_uint_32 mask);
 
 

extern  png_voidp  png_malloc_default (png_structp png_ptr, png_uint_32 size);
extern  void  png_free_default (png_structp png_ptr, png_voidp ptr);

extern  png_voidp  png_memcpy_check (png_structp png_ptr, png_voidp s1, png_voidp s2, png_uint_32 size);

extern  png_voidp  png_memset_check (png_structp png_ptr, png_voidp s1, int value, png_uint_32 size);


 
extern  void  png_error (png_structp png_ptr, png_const_charp error_message);

 
extern  void  png_chunk_error (png_structp png_ptr, png_const_charp error_message);

 
extern  void  png_warning (png_structp png_ptr, png_const_charp warning_message);

 
extern  void  png_chunk_warning (png_structp png_ptr, png_const_charp warning_message);












 
 



 




 
extern  png_bytepp  png_get_rows (png_structp png_ptr, png_infop info_ptr);

 
extern  void  png_set_rows (png_structp png_ptr, png_infop info_ptr, png_bytepp row_pointers);

 
extern  png_byte  png_get_channels (png_structp png_ptr, png_infop info_ptr);

 
extern  png_uint_32  png_get_image_width (png_structp png_ptr, png_infop info_ptr);

 
extern  png_uint_32  png_get_image_height (png_structp png_ptr, png_infop info_ptr);

 
extern  png_byte  png_get_bit_depth (png_structp png_ptr, png_infop info_ptr);

 
extern  png_byte  png_get_color_type (png_structp png_ptr, png_infop info_ptr);

 
extern  png_byte  png_get_filter_type (png_structp png_ptr, png_infop info_ptr);

 
extern  png_byte  png_get_interlace_type (png_structp png_ptr, png_infop info_ptr);

 
extern  png_byte  png_get_compression_type (png_structp png_ptr, png_infop info_ptr);

 
extern  png_uint_32  png_get_pixels_per_meter (png_structp png_ptr, png_infop info_ptr);
extern  png_uint_32  png_get_x_pixels_per_meter (png_structp png_ptr, png_infop info_ptr);
extern  png_uint_32  png_get_y_pixels_per_meter (png_structp png_ptr, png_infop info_ptr);

 
extern  float  png_get_pixel_aspect_ratio (png_structp png_ptr, png_infop info_ptr);

 
extern  png_int_32  png_get_x_offset_pixels (png_structp png_ptr, png_infop info_ptr);
extern  png_int_32  png_get_y_offset_pixels (png_structp png_ptr, png_infop info_ptr);
extern  png_int_32  png_get_x_offset_microns (png_structp png_ptr, png_infop info_ptr);
extern  png_int_32  png_get_y_offset_microns (png_structp png_ptr, png_infop info_ptr);


 
extern  png_bytep  png_get_signature (png_structp png_ptr, png_infop info_ptr);

extern  png_uint_32  png_get_bKGD (png_structp png_ptr, png_infop info_ptr, png_color_16p *background);

extern  void  png_set_bKGD (png_structp png_ptr, png_infop info_ptr, png_color_16p background);

extern  png_uint_32  png_get_cHRM (png_structp png_ptr, png_infop info_ptr, double *white_x, double *white_y, double *red_x, double *red_y, double *green_x, double *green_y, double *blue_x, double *blue_y);
extern  png_uint_32  png_get_cHRM_fixed (png_structp png_ptr, png_infop info_ptr, png_fixed_point *int_white_x, png_fixed_point *int_white_y, png_fixed_point *int_red_x, png_fixed_point *int_red_y, png_fixed_point *int_green_x, png_fixed_point *int_green_y, png_fixed_point *int_blue_x, png_fixed_point *int_blue_y);

extern  void  png_set_cHRM (png_structp png_ptr, png_infop info_ptr, double white_x, double white_y, double red_x, double red_y, double green_x, double green_y, double blue_x, double blue_y);
extern  void  png_set_cHRM_fixed (png_structp png_ptr, png_infop info_ptr, png_fixed_point int_white_x, png_fixed_point int_white_y, png_fixed_point int_red_x, png_fixed_point int_red_y, png_fixed_point int_green_x, png_fixed_point int_green_y, png_fixed_point int_blue_x, png_fixed_point int_blue_y);

extern  png_uint_32  png_get_gAMA (png_structp png_ptr, png_infop info_ptr, double *file_gamma);
extern  png_uint_32  png_get_gAMA_fixed (png_structp png_ptr, png_infop info_ptr, png_fixed_point *int_file_gamma);

extern  void  png_set_gAMA (png_structp png_ptr, png_infop info_ptr, double file_gamma);
extern  void  png_set_gAMA_fixed (png_structp png_ptr, png_infop info_ptr, png_fixed_point int_file_gamma);

extern  png_uint_32  png_get_hIST (png_structp png_ptr, png_infop info_ptr, png_uint_16p *hist);

extern  void  png_set_hIST (png_structp png_ptr, png_infop info_ptr, png_uint_16p hist);






extern  void  png_set_IHDR (png_structp png_ptr, png_infop info_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int interlace_method, int compression_method, int filter_method);

extern  png_uint_32  png_get_oFFs (png_structp png_ptr, png_infop info_ptr, png_int_32 *offset_x, png_int_32 *offset_y, int *unit_type);

extern  void  png_set_oFFs (png_structp png_ptr, png_infop info_ptr, png_int_32 offset_x, png_int_32 offset_y, int unit_type);

extern  png_uint_32  png_get_pCAL (png_structp png_ptr, png_infop info_ptr, png_charp *purpose, png_int_32 *X0, png_int_32 *X1, int *type, int *nparams, png_charp *units, png_charpp *params);

extern  void  png_set_pCAL (png_structp png_ptr, png_infop info_ptr, png_charp purpose, png_int_32 X0, png_int_32 X1, int type, int nparams, png_charp units, png_charpp params);

extern  png_uint_32  png_get_pHYs (png_structp png_ptr, png_infop info_ptr, png_uint_32 *res_x, png_uint_32 *res_y, int *unit_type);

extern  void  png_set_pHYs (png_structp png_ptr, png_infop info_ptr, png_uint_32 res_x, png_uint_32 res_y, int unit_type);

extern  png_uint_32  png_get_PLTE (png_structp png_ptr, png_infop info_ptr, png_colorp *palette, int *num_palette);

extern  void  png_set_PLTE (png_structp png_ptr, png_infop info_ptr, png_colorp palette, int num_palette);

extern  png_uint_32  png_get_sBIT (png_structp png_ptr, png_infop info_ptr, png_color_8p *sig_bit);

extern  void  png_set_sBIT (png_structp png_ptr, png_infop info_ptr, png_color_8p sig_bit);

extern  png_uint_32  png_get_sRGB (png_structp png_ptr, png_infop info_ptr, int *intent);

extern  void  png_set_sRGB (png_structp png_ptr, png_infop info_ptr, int intent);
extern  void  png_set_sRGB_gAMA_and_cHRM (png_structp png_ptr, png_infop info_ptr, int intent);

extern  png_uint_32  png_get_iCCP (png_structp png_ptr, png_infop info_ptr, png_charpp name, int *compression_type, png_charpp profile, png_uint_32 *proflen);
    

extern  void  png_set_iCCP (png_structp png_ptr, png_infop info_ptr, png_charp name, int compression_type, png_charp profile, png_uint_32 proflen);
    

extern  png_uint_32  png_get_sPLT (png_structp png_ptr, png_infop info_ptr, png_sPLT_tpp entries);

extern  void  png_set_sPLT (png_structp png_ptr, png_infop info_ptr, png_sPLT_tp entries, int nentries);

 
extern  png_uint_32  png_get_text (png_structp png_ptr, png_infop info_ptr, png_textp *text_ptr, int *num_text);







 

extern  void  png_set_text (png_structp png_ptr, png_infop info_ptr, png_textp text_ptr, int num_text);

extern  png_uint_32  png_get_tIME (png_structp png_ptr, png_infop info_ptr, png_timep *mod_time);

extern  void  png_set_tIME (png_structp png_ptr, png_infop info_ptr, png_timep mod_time);

extern  png_uint_32  png_get_tRNS (png_structp png_ptr, png_infop info_ptr, png_bytep *trans, int *num_trans, png_color_16p *trans_values);

extern  void  png_set_tRNS (png_structp png_ptr, png_infop info_ptr, png_bytep trans, int num_trans, png_color_16p trans_values);


extern  png_uint_32  png_get_sCAL (png_structp png_ptr, png_infop info_ptr, int *unit, double *width, double *height);

extern  void  png_set_sCAL (png_structp png_ptr, png_infop info_ptr, int unit, double width, double height);









 
extern  void  png_set_keep_unknown_chunks (png_structp png_ptr, int keep, png_bytep chunk_list, int num_chunks);
extern  void  png_set_unknown_chunks (png_structp png_ptr, png_infop info_ptr, png_unknown_chunkp unknowns, int num_unknowns);
extern  void  png_set_unknown_chunk_location
   (png_structp png_ptr, png_infop info_ptr, int chunk, int location);
extern  png_uint_32  png_get_unknown_chunks (png_structp png_ptr, png_infop info_ptr, png_unknown_chunkpp entries);
 int  png_handle_as_unknown (png_structp png_ptr, png_bytep chunk_name);



 
extern  void  png_set_invalid (png_structp png_ptr, png_infop info_ptr, int mask);

 
extern  void  png_read_png (png_structp png_ptr, png_infop info_ptr, int transforms, png_voidp params);
extern  void  png_write_png (png_structp png_ptr, png_infop info_ptr, int transforms, png_voidp params);





 


extern  png_charp  png_get_copyright (png_structp png_ptr);
extern  png_charp  png_get_header_ver (png_structp png_ptr);
extern  png_charp  png_get_header_version (png_structp png_ptr);
extern  png_charp  png_get_libpng_ver (png_structp png_ptr);

extern  png_uint_32  png_permit_mng_features (png_structp png_ptr, png_uint_32 mng_features_permitted);

 

 




 
extern  png_uint_32  png_get_mmx_flagmask
   (int flag_select, int *compilerID);

 
extern  png_uint_32  png_get_asm_flagmask
   (int flag_select);

 
extern  png_uint_32  png_get_asm_flags
   (png_structp png_ptr);

 
extern  png_byte  png_get_mmx_bitdepth_threshold
   (png_structp png_ptr);

 
extern  png_uint_32  png_get_mmx_rowbytes_threshold
   (png_structp png_ptr);

 
extern  void  png_set_asm_flags
   (png_structp png_ptr, png_uint_32 asm_flags);

 
extern  void  png_set_mmx_thresholds
   (png_structp png_ptr, png_byte mmx_bitdepth_threshold, png_uint_32 mmx_rowbytes_threshold);


 
extern  int  png_mmx_support (void);


 
extern  void  png_set_strip_error_numbers (png_structp png_ptr, png_uint_32 strip_mode);


 
extern  void  png_set_user_limits (png_structp png_ptr, png_uint_32 user_width_max, png_uint_32 user_height_max);
extern  png_uint_32  png_get_user_width_max (png_structp png_ptr);
extern  png_uint_32  png_get_user_height_max (png_structp png_ptr);

 











 

  











 
extern  png_uint_32  png_get_uint_32 (png_bytep buf);
extern  png_uint_16  png_get_uint_16 (png_bytep buf);
extern  png_int_32  png_get_int_32 (png_bytep buf);
extern  png_uint_32  png_get_uint_31
  (png_structp png_ptr, png_bytep buf);
 


 
extern  void  png_save_uint_32
   (png_bytep buf, png_uint_32 i);
extern  void  png_save_int_32
   (png_bytep buf, png_int_32 i);




 
extern  void  png_save_uint_16
   (png_bytep buf, unsigned int i);
 

 





 



 

 























































 




 























































 







  










 



 





 







typedef struct bignum_st
	{
	unsigned long *d;	 
	int top;	 
	 
	int max;	 
	int neg;	 
	int flags;
	} BIGNUM;

 
typedef struct bignum_ctx
	{
	int tos;
	BIGNUM bn[12];
	int flags;
	int depth;
	int pos[12];
	int too_many;
	} BN_CTX;

typedef struct bn_blinding_st
	{
	int init;
	BIGNUM *A;
	BIGNUM *Ai;
	BIGNUM *mod;  
	} BN_BLINDING;

 
typedef struct bn_mont_ctx_st
	{
	int ri;         
	BIGNUM RR;      
	BIGNUM N;       
	BIGNUM Ni;     
 
	unsigned long n0;    
	int flags;
	} BN_MONT_CTX;



 
typedef struct bn_recp_ctx_st
	{
	BIGNUM N;	 
	BIGNUM Nr;	 
	int num_bits;
	int shift;
	int flags;
	} BN_RECP_CTX;







 


 
 

BIGNUM *BN_value_one(void);
char *	BN_options(void);
BN_CTX *BN_CTX_new(void);
void	BN_CTX_init(BN_CTX *c);
void	BN_CTX_free(BN_CTX *c);
void	BN_CTX_start(BN_CTX *ctx);
BIGNUM *BN_CTX_get(BN_CTX *ctx);
void	BN_CTX_end(BN_CTX *ctx);
int     BN_rand(BIGNUM *rnd, int bits, int top,int bottom);
int     BN_pseudo_rand(BIGNUM *rnd, int bits, int top,int bottom);
int	BN_num_bits(const BIGNUM *a);
int	BN_num_bits_word(unsigned long);
BIGNUM *BN_new(void);
void	BN_init(BIGNUM *);
void	BN_clear_free(BIGNUM *a);
BIGNUM *BN_copy(BIGNUM *a, const BIGNUM *b);

int	BN_bn2bin(const BIGNUM *a, unsigned char *to);
BIGNUM *BN_mpi2bn(unsigned char *s,int len,BIGNUM *ret);
int	BN_bn2mpi(const BIGNUM *a, unsigned char *to);
int	BN_sub(BIGNUM *r, const BIGNUM *a, const BIGNUM *b);
int	BN_usub(BIGNUM *r, const BIGNUM *a, const BIGNUM *b);
int	BN_uadd(BIGNUM *r, const BIGNUM *a, const BIGNUM *b);
int	BN_add(BIGNUM *r, const BIGNUM *a, const BIGNUM *b);
int	BN_mod(BIGNUM *rem, const BIGNUM *m, const BIGNUM *d, BN_CTX *ctx);
int	BN_div(BIGNUM *dv, BIGNUM *rem, const BIGNUM *m, const BIGNUM *d,
	       BN_CTX *ctx);
int	BN_mul(BIGNUM *r, BIGNUM *a, BIGNUM *b, BN_CTX *ctx);
int	BN_sqr(BIGNUM *r, BIGNUM *a,BN_CTX *ctx);
unsigned long BN_mod_word(const BIGNUM *a, unsigned long w);
unsigned long BN_div_word(BIGNUM *a, unsigned long w);
int	BN_mul_word(BIGNUM *a, unsigned long w);
int	BN_add_word(BIGNUM *a, unsigned long w);
int	BN_sub_word(BIGNUM *a, unsigned long w);
int	BN_set_word(BIGNUM *a, unsigned long w);
unsigned long BN_get_word(BIGNUM *a);
int	BN_cmp(const BIGNUM *a, const BIGNUM *b);
void	BN_free(BIGNUM *a);
int	BN_is_bit_set(const BIGNUM *a, int n);
int	BN_lshift(BIGNUM *r, const BIGNUM *a, int n);
int	BN_lshift1(BIGNUM *r, BIGNUM *a);
int	BN_exp(BIGNUM *r, BIGNUM *a, BIGNUM *p,BN_CTX *ctx);
int	BN_mod_exp(BIGNUM *r, BIGNUM *a, const BIGNUM *p,
		   const BIGNUM *m,BN_CTX *ctx);
int	BN_mod_exp_mont(BIGNUM *r, BIGNUM *a, const BIGNUM *p,
			const BIGNUM *m, BN_CTX *ctx, BN_MONT_CTX *m_ctx);
int	BN_mod_exp2_mont(BIGNUM *r, BIGNUM *a1, BIGNUM *p1,BIGNUM *a2,
		BIGNUM *p2,BIGNUM *m,BN_CTX *ctx,BN_MONT_CTX *m_ctx);
int	BN_mod_exp_simple(BIGNUM *r, BIGNUM *a, BIGNUM *p,
	BIGNUM *m,BN_CTX *ctx);
int	BN_mask_bits(BIGNUM *a,int n);
int	BN_mod_mul(BIGNUM *ret, BIGNUM *a, BIGNUM *b, const BIGNUM *m, BN_CTX *ctx);
int	BN_print(void *fp, const BIGNUM *a);
int	BN_reciprocal(BIGNUM *r, BIGNUM *m, int len, BN_CTX *ctx);
int	BN_rshift(BIGNUM *r, BIGNUM *a, int n);
int	BN_rshift1(BIGNUM *r, BIGNUM *a);
void	BN_clear(BIGNUM *a);
BIGNUM *BN_dup(const BIGNUM *a);
int	BN_ucmp(const BIGNUM *a, const BIGNUM *b);
int	BN_set_bit(BIGNUM *a, int n);
int	BN_clear_bit(BIGNUM *a, int n);
char *	BN_bn2hex(const BIGNUM *a);
char *	BN_bn2dec(const BIGNUM *a);
int 	BN_hex2bn(BIGNUM **a, const char *str);
int 	BN_dec2bn(BIGNUM **a, const char *str);
int	BN_gcd(BIGNUM *r,BIGNUM *in_a,BIGNUM *in_b,BN_CTX *ctx);
BIGNUM *BN_mod_inverse(BIGNUM *ret,BIGNUM *a, const BIGNUM *n,BN_CTX *ctx);
BIGNUM *BN_generate_prime(BIGNUM *ret,int bits,int safe,BIGNUM *add,
		BIGNUM *rem,void (*callback)(int,int,void *),void *cb_arg);
int	BN_is_prime(const BIGNUM *p,int nchecks,
		void (*callback)(int,int,void *),
		BN_CTX *ctx,void *cb_arg);
int	BN_is_prime_fasttest(const BIGNUM *p,int nchecks,
		void (*callback)(int,int,void *),BN_CTX *ctx,void *cb_arg,
		int do_trial_division);
void	ERR_load_BN_strings(void );

BN_MONT_CTX *BN_MONT_CTX_new(void );
void BN_MONT_CTX_init(BN_MONT_CTX *ctx);
int BN_mod_mul_montgomery(BIGNUM *r,BIGNUM *a,BIGNUM *b,BN_MONT_CTX *mont,
			  BN_CTX *ctx);
int BN_from_montgomery(BIGNUM *r,BIGNUM *a,BN_MONT_CTX *mont,BN_CTX *ctx);
void BN_MONT_CTX_free(BN_MONT_CTX *mont);
int BN_MONT_CTX_set(BN_MONT_CTX *mont,const BIGNUM *modulus,BN_CTX *ctx);
BN_MONT_CTX *BN_MONT_CTX_copy(BN_MONT_CTX *to,BN_MONT_CTX *from);

BN_BLINDING *BN_BLINDING_new(BIGNUM *A,BIGNUM *Ai,BIGNUM *mod);
void BN_BLINDING_free(BN_BLINDING *b);
int BN_BLINDING_update(BN_BLINDING *b,BN_CTX *ctx);
int BN_BLINDING_convert(BIGNUM *n, BN_BLINDING *r, BN_CTX *ctx);
int BN_BLINDING_invert(BIGNUM *n, BN_BLINDING *b, BN_CTX *ctx);

void BN_set_params(int mul,int high,int low,int mont);
int BN_get_params(int which);  

void	BN_RECP_CTX_init(BN_RECP_CTX *recp);
BN_RECP_CTX *BN_RECP_CTX_new(void);
void	BN_RECP_CTX_free(BN_RECP_CTX *recp);
int	BN_RECP_CTX_set(BN_RECP_CTX *recp,const BIGNUM *rdiv,BN_CTX *ctx);
int	BN_mod_mul_reciprocal(BIGNUM *r, BIGNUM *x, BIGNUM *y,
		BN_RECP_CTX *recp,BN_CTX *ctx);
int	BN_mod_exp_recp(BIGNUM *r, const BIGNUM *a, const BIGNUM *p,
			const BIGNUM *m, BN_CTX *ctx);
int	BN_div_recp(BIGNUM *dv, BIGNUM *rem, BIGNUM *m,
		BN_RECP_CTX *recp, BN_CTX *ctx);

 

BIGNUM *bn_expand2(BIGNUM *a, int words);


unsigned long bn_mul_add_words(unsigned long *rp, unsigned long *ap, int num, unsigned long w);
unsigned long bn_mul_words(unsigned long *rp, unsigned long *ap, int num, unsigned long w);
void     bn_sqr_words(unsigned long *rp, unsigned long *ap, int num);
unsigned long bn_div_words(unsigned long h, unsigned long l, unsigned long d);
unsigned long bn_add_words(unsigned long *rp, unsigned long *ap, unsigned long *bp,int num);
unsigned long bn_sub_words(unsigned long *rp, unsigned long *ap, unsigned long *bp,int num);


 


 

 

 

 



 























































 















 

 
 



 





 



 

 
 



 
typedef struct bio_st BIO_dummy;

typedef struct crypto_ex_data_st
	{
	void *sk;
	int dummy;  
	} CRYPTO_EX_DATA;

 
typedef int CRYPTO_EX_new(void *parent, void *ptr, CRYPTO_EX_DATA *ad,
					int idx, long argl, void *argp);
 
typedef void CRYPTO_EX_free(void *parent, void *ptr, CRYPTO_EX_DATA *ad,
					int idx, long argl, void *argp);
 
typedef int CRYPTO_EX_dup(CRYPTO_EX_DATA *to, CRYPTO_EX_DATA *from, void *from_d, 
					int idx, long argl, void *argp);


 

typedef struct crypto_ex_data_func_st
	{
	long argl;	 
	void *argp;	 
	CRYPTO_EX_new *new_func;
	CRYPTO_EX_free *free_func;
	CRYPTO_EX_dup *dup_func;
	} CRYPTO_EX_DATA_FUNCS;





 






 



 

int CRYPTO_mem_ctrl(int mode);
int CRYPTO_is_mem_check_on(void);

 

 




 


const char *SSLeay_version(int type);
unsigned long SSLeay(void);

int CRYPTO_get_new_lockid(char *name);

int CRYPTO_num_locks(void);  
void CRYPTO_lock(int mode, int type,const char *file,int line);
void CRYPTO_set_locking_callback(void (*func)(int mode,int type,
					      const char *file,int line));
void (*CRYPTO_get_locking_callback(void))(int mode,int type,const char *file,
		int line);
void CRYPTO_set_add_lock_callback(int (*func)(int *num,int mount,int type,
					      const char *file, int line));
int (*CRYPTO_get_add_lock_callback(void))(int *num,int mount,int type,
					  const char *file,int line);
void CRYPTO_set_id_callback(unsigned long (*func)(void));
unsigned long (*CRYPTO_get_id_callback(void))(void);
unsigned long CRYPTO_thread_id(void);
const char *CRYPTO_get_lock_name(int type);
int CRYPTO_add_lock(int *pointer,int amount,int type, const char *file,
		    int line);


 
int CRYPTO_set_mem_functions(void *(*m)(size_t),void *(*r)(void *,size_t), void (*f)(void *));
int CRYPTO_set_locked_mem_functions(void *(*m)(size_t), void (*free_func)(void *));
int CRYPTO_set_mem_debug_functions(void (*m)(),void (*r)(),void (*f)(),void (*so)(),long (*go)());
void CRYPTO_get_mem_functions(void *(**m)(size_t),void *(**r)(void *, size_t), void (**f)(void *));
void CRYPTO_get_locked_mem_functions(void *(**m)(size_t), void (**f)(void *));
void CRYPTO_get_mem_debug_functions(void (**m)(),void (**r)(),void (**f)(),void (**so)(),long (**go)());

void *CRYPTO_malloc_locked(int num, const char *file, int line);
void CRYPTO_free_locked(void *);
void *CRYPTO_malloc(int num, const char *file, int line);
void CRYPTO_free(void *);
void *CRYPTO_realloc(void *addr,int num, const char *file, int line);
void *CRYPTO_remalloc(void *addr,int num, const char *file, int line);

void CRYPTO_set_mem_debug_options(long bits);
long CRYPTO_get_mem_debug_options(void);

int CRYPTO_push_info_(const char *info, const char *file, int line);
int CRYPTO_pop_info(void);
int CRYPTO_remove_all_info(void);





 
void CRYPTO_dbg_malloc(void *addr,int num,const char *file,int line,int before_p);
void CRYPTO_dbg_realloc(void *addr1,void *addr2,int num,const char *file,int line,int before_p);
void CRYPTO_dbg_free(void *addr,int before_p);








 
void CRYPTO_dbg_set_options(long bits);
long CRYPTO_dbg_get_options(void);

void CRYPTO_mem_leaks(struct bio_st *bio);
 
void CRYPTO_mem_leaks_cb(void (*cb)());

void ERR_load_CRYPTO_strings(void);

 


 

 

 

 




typedef struct rsa_st RSA;

typedef struct rsa_meth_st
	{
	const char *name;
	int (*rsa_pub_enc)(int flen,unsigned char *from,unsigned char *to,
			   RSA *rsa,int padding);
	int (*rsa_pub_dec)(int flen,unsigned char *from,unsigned char *to,
			   RSA *rsa,int padding);
	int (*rsa_priv_enc)(int flen,unsigned char *from,unsigned char *to,
			    RSA *rsa,int padding);
	int (*rsa_priv_dec)(int flen,unsigned char *from,unsigned char *to,
			    RSA *rsa,int padding);
	int (*rsa_mod_exp)(BIGNUM *r0,BIGNUM *I,RSA *rsa);  
	int (*bn_mod_exp)(BIGNUM *r, BIGNUM *a, const BIGNUM *p,
			  const BIGNUM *m, BN_CTX *ctx,
			  BN_MONT_CTX *m_ctx);  
	int (*init)(RSA *rsa);		 
	int (*finish)(RSA *rsa);	 
	int flags;			 
	char *app_data;			 






 
	int (*rsa_sign)(int type, unsigned char *m, unsigned int m_len,
             unsigned char *sigret, unsigned int *siglen, RSA *rsa);
	int (*rsa_verify)(int dtype, unsigned char *m, unsigned int m_len,
             unsigned char *sigbuf, unsigned int siglen, RSA *rsa);

	} RSA_METHOD;

struct rsa_st
	{
	
 
	int pad;
	int version;
	RSA_METHOD *meth;
	BIGNUM *n;
	BIGNUM *e;
	BIGNUM *d;
	BIGNUM *p;
	BIGNUM *q;
	BIGNUM *dmp1;
	BIGNUM *dmq1;
	BIGNUM *iqmp;
	 
	CRYPTO_EX_DATA ex_data;
	int references;
	int flags;

	 
	BN_MONT_CTX *_method_mod_n;
	BN_MONT_CTX *_method_mod_p;
	BN_MONT_CTX *_method_mod_q;

	
 
	char *bignum_data;
	BN_BLINDING *blinding;
	};







 


 



RSA *	RSA_new(void);

int	RSA_size(RSA *);
RSA *	RSA_generate_key(int bits, unsigned long e,void
		(*callback)(int,int,void *),void *cb_arg);
int	RSA_check_key(RSA *);
	 
int	RSA_public_encrypt(int flen, char *from,
		char *to, RSA *rsa,int padding);
int	RSA_private_encrypt(int flen, char *from,
		char *to, RSA *rsa,int padding);
int	RSA_public_decrypt(int flen, unsigned char *from, 
		unsigned char *to, RSA *rsa,int padding);
int	RSA_private_decrypt(int flen, unsigned char *from, 
		unsigned char *to, RSA *rsa,int padding);


int	RSA_flags(RSA *r);

void RSA_set_default_method(RSA_METHOD *meth);
RSA_METHOD *RSA_get_default_method(void);
RSA_METHOD *RSA_get_method(RSA *rsa);
RSA_METHOD *RSA_set_method(RSA *rsa, RSA_METHOD *meth);

 
int RSA_memory_lock(RSA *r);

 
RSA_METHOD *RSA_PKCS1_RSAref(void);

 
RSA_METHOD *RSA_PKCS1_SSLeay(void);

RSA_METHOD *RSA_null_method(void);

void	ERR_load_RSA_strings(void );

RSA *	d2i_RSAPublicKey(RSA **a, unsigned char **pp, long length);
int	i2d_RSAPublicKey(RSA *a, unsigned char **pp);
RSA *	d2i_RSAPrivateKey(RSA **a, unsigned char **pp, long length);
int 	i2d_RSAPrivateKey(RSA *a, unsigned char **pp);


int i2d_Netscape_RSA(RSA *a, unsigned char **pp, int (*cb)());
RSA *d2i_Netscape_RSA(RSA **a, unsigned char **pp, long length, int (*cb)());

 
RSA *d2i_Netscape_RSA_2(RSA **a, unsigned char **pp, long length, int (*cb)());


 


int RSA_verify(int type, unsigned char *m, unsigned int m_len,
	unsigned char *sigbuf, unsigned int siglen, RSA *rsa);


 
int RSA_sign_ASN1_OCTET_STRING(int type, unsigned char *m, unsigned int m_len,
	unsigned char *sigret, unsigned int *siglen, RSA *rsa);
int RSA_verify_ASN1_OCTET_STRING(int type, unsigned char *m, unsigned int m_len,
	unsigned char *sigbuf, unsigned int siglen, RSA *rsa);

int RSA_blinding_on(RSA *rsa, BN_CTX *ctx);
void RSA_blinding_off(RSA *rsa);

int RSA_padding_add_PKCS1_type_1(unsigned char *to,int tlen,
	unsigned char *f,int fl);
int RSA_padding_check_PKCS1_type_1(unsigned char *to,int tlen,
	unsigned char *f,int fl,int rsa_len);
int RSA_padding_add_PKCS1_type_2(unsigned char *to,int tlen,
	unsigned char *f,int fl);
int RSA_padding_check_PKCS1_type_2(unsigned char *to,int tlen,
	unsigned char *f,int fl,int rsa_len);
int RSA_padding_add_PKCS1_OAEP(unsigned char *to,int tlen,
			       unsigned char *f,int fl,unsigned char *p,
			       int pl);
int RSA_padding_check_PKCS1_OAEP(unsigned char *to,int tlen,
				 unsigned char *f,int fl,int rsa_len,
				 unsigned char *p,int pl);
int RSA_padding_add_SSLv23(unsigned char *to,int tlen,
	unsigned char *f,int fl);
int RSA_padding_check_SSLv23(unsigned char *to,int tlen,
	unsigned char *f,int fl,int rsa_len);
int RSA_padding_add_none(unsigned char *to,int tlen,
	unsigned char *f,int fl);
int RSA_padding_check_none(unsigned char *to,int tlen,
	unsigned char *f,int fl,int rsa_len);

int RSA_get_ex_new_index(long argl, void *argp, CRYPTO_EX_new *new_func,
	CRYPTO_EX_dup *dup_func, CRYPTO_EX_free *free_func);
int RSA_set_ex_data(RSA *r,int idx,void *arg);
void *RSA_get_ex_data(RSA *r, int idx);

 


 

 

 

 



 























































 









 



typedef struct SHAstate_st
	{
	unsigned int h0,h1,h2,h3,h4;
	unsigned int Nl,Nh;
	unsigned int data[16];
	int num;
	} SHA_CTX;

void SHA_Init(SHA_CTX *c);
void SHA_Update(SHA_CTX *c, const void *data, unsigned long len);
void SHA_Final(unsigned char *md, SHA_CTX *c);
unsigned char *SHA(const unsigned char *d, unsigned long n,unsigned char *md);
void SHA_Transform(SHA_CTX *c, const unsigned char *data);



unsigned char *SHA1(const unsigned char *d, unsigned long n,unsigned char *md);
void SHA1_Transform(SHA_CTX *c, const unsigned char *data);

 























































 









 



typedef struct MD5state_st
	{
	unsigned int A,B,C,D;
	unsigned int Nl,Nh;
	unsigned int data[(64/4)];
	int num;
	} MD5_CTX;

void MD5_Init(MD5_CTX *c);
void MD5_Update(MD5_CTX *c, const void *data, unsigned long len);
void MD5_Final(unsigned char *md, MD5_CTX *c);
unsigned char *MD5(const unsigned char *d, unsigned long n, unsigned char *md);
void MD5_Transform(MD5_CTX *c, const unsigned char *b);

typedef struct
{
	void *ChanBannerQ; 
}SFN_DATA;


typedef struct {
  int type;
  void *func;
}OBSevent;


















































































































 





















typedef struct{
  int pid_from;
  int msg; 
  void *pkt;
  char unk1;
  char encoding_type;
  char pkt_length;
  char unk2;
  void *data1;
} GBS_USSD_MSG;


typedef unsigned int u_int32_t;
typedef struct{
  unsigned long year;
  unsigned char month;
  unsigned char day;
} TDate;

typedef struct{
  unsigned char hour;
  unsigned char min;
  unsigned char sec;
  unsigned long millisec;
} TTime;

typedef struct{
  unsigned int type;
  unsigned int param2;
  unsigned short param3;
  unsigned short wstr[25];
}StructUSSDStr;

typedef struct{
  void *p1;
  void *p2;
  StructUSSDStr *pussdstr;
}StructUSSD;

typedef struct
{
  void *first;
  void *last;
  void (*data_mfree)(void *);
}LLQ;

typedef struct{
  int param0;
  int param1;
  int param2;
  int param3;
} GBSTMR;

typedef struct{
  int pid_from;
  int msg;
  int submess;
  void *data0;
  void *data1;
} GBS_MSG;

typedef struct{
  void *p;
  int i;
}MUTEX;

typedef struct{
  void *next;
  void *prev;
  void   *constr;
  int id;
  int state;
  int unk1;
  int unk2;
  LLQ gui_ll;
} CSM_RAM;

typedef struct{
  int (*onMessage)(CSM_RAM*,GBS_MSG*);
  void (*onCreate)(CSM_RAM*);
  int zero1;
  int zero2;
  int zero3;
  int zero4;
  void (*onClose)(CSM_RAM*);
  int datasize;
  int statesize;
  const int *states;
} CSM_DESC;

typedef struct{
  int id;
  CSM_RAM *current_msg_processing_csm;
  LLQ csm;
  LLQ cmd;
  LLQ csm_background;
} CSMQ;

typedef struct{
  void *next;
  void *prev;
  int flag1;
  int parent_id;
  int prio;
  int (*proc)(CSMQ *, void *);
  CSMQ *csm_q;
  int id;
  int flag2;
}MMICMD;



typedef struct{
  int under_idle_id;
  int idle_id;
  CSMQ *csm_q;
} CSMROOT;

typedef struct{
  short x;
  short y;
  short x2;
  short y2;
} RECT;

typedef struct{
  char dummy[0x24];
} DRWOBJ;

typedef struct{
  char   id;
  char   cbyte; 
  char   zero;
  int    pen; 
  int    brush; 
  RECT   rc;    
  
  void  *body; 
  int    param0;
  short  param1;
  short  param2;
}DRWOBJ_S;
typedef struct{
int w; 
int h; 
RECT unk_rc; 
RECT rc; 
short *buf; 
int col; 

}LCDLAYER;
typedef struct{
  unsigned short *wsbody;
  void *(*ws_malloc)(int);
  void (*ws_mfree)(void *);
  int isbody_allocated;
  unsigned short maxlen;
  unsigned short unk1;
} WSHDR;

typedef struct
{
  void *next;
  void *prev;
  void *data;
}EDITQ;

typedef struct
{
  void *next;
  void *prev;
}LLIST;

typedef struct
{
  const char *ext;
  int unical_id;
  char enabled_options;
  char obex_path_id;
  short menu_flag;
  const int *icon1;
  const int *icon2;
  int Open_lgpid;	
  int Options_lgpid;	
  int Enter_lgpid;	
  void *proc;
  void *altproc;
}REGEXPLEXT;
typedef struct
{
  char unk0;
  char unk1;
  short pos_index;
}SMS_POS_INDEX_DATA;

typedef struct
{
  void *unk_proc0; 
  void *unk_proc1; 
  short index; 
  char unk[6];
  short unk1; 
  char cnt_all;
  char cnt_received; 
  unsigned short *data_id; 
  short unk2; 
  short unk3; 
  char unk4; 
  char unk5; 
  char type; 
  char new_cnt_data; 
}INDEX_ID_DATA;

typedef struct
{
  void *next;
  void *prev;
  INDEX_ID_DATA *index_id_data;
  
  
  
  
}SMS_DATA_LIST;

typedef struct
{
  SMS_DATA_LIST *first;
  SMS_DATA_LIST *last;
  void *unk_proc; 
}SMS_DATA_LLIST;
typedef struct
{
  SMS_DATA_LLIST in_msg;
  SMS_DATA_LLIST out_msg;
  short unk_0xFFFF;
  short unk_0_1;
  short cnt_msg_in_read;
  short cnt_in_new_sms_dat;
  short cnt_in_new_opwv; 
  short cnt_sms_sent;
  short cnt_sms_draft;
  short unk_0_2;
  short cnt_freespace_data; 
  short cnt_in_data;
  short cnt_new_in_data;
  short cnt_sent_data;
  short cnt_draft_data;
  short unk_0_3; 
}SMS_DATA_ROOT;
typedef struct
{
  int zero;
  unsigned const int *icon1;
  int unical_id;
  char obex_path_id;
  char unk;
  unsigned short menu_flag;
  char enabled_options;
  char not_used[3];
  WSHDR* ext;
  void *proc;
  void *altproc;
  unsigned const int *icon2;
}REGEXPLEXT_ARM_NEW;

typedef struct
{
  RECT *canvas;
  void *methods;
  void *definition;
  char state;
  char unk2;
  char unk3;
  char unk4;
  int color1; 
  int color2;
  LLQ item_ll;
  int unk5;
  char unk6;
  char unk7;
  char unk8;
  char unk9;
  int unk10;
  int flag30; 
}GUI;


typedef struct
{
  char zero;
  char unk1;
  short keys;
  GBS_MSG *gbsmsg;
}GUI_MSG;
















































typedef struct
{
  unsigned short w;
  unsigned short h;
  int bpnum; 
  char *bitmap;
}IMGHDR;

typedef struct
{
  RECT rc;
  int *icon;
  int lgp_id;
  int lgp_null; 
}HEADER_DESC;

typedef struct
{
  int *icon;
  int lgp_id_small;
  int lgp_id_large;
  int zero;
  const int *softkeys; 
  int flag1; 
  int flag2; 
}MENUITEM_DESC;

typedef struct
{
  short key1;
  short key2;
  int lgp_id;
}SOFTKEY_DESC;

typedef struct
{
  const SOFTKEY_DESC *desc;
  int n;
}SOFTKEYSTAB;

typedef void (__interwork *MENUPROCS_DESC)(GUI *);

typedef struct
{
  int flag; 
  int (*onkey)(void *, GUI_MSG *);
  void (*ghook)(void *, int ); 
  void *proc3;
  const int *softkeys; 
  const SOFTKEYSTAB *softkeystab;
  int flags2; 


















  void (*itemproc)(void *, int, void *); 
  const MENUITEM_DESC *items; 
  const MENUPROCS_DESC *procs;
  int n_items; 
}MENU_DESC;

typedef struct
{
  int flag; 
  int (*onkey)(void *, GUI_MSG *);
  void (*ghook)(void *, int ); 
  void *proc3;
  const int *softkeys; 
  const SOFTKEYSTAB *softkeystab;
  int flags2; 
  void (*itemproc)(void *, int, void *); 
  const MENUITEM_DESC *items; 
  const MENUPROCS_DESC *procs;
  int n_items; 
  int n_lines; 
}ML_MENU_DESC;

#pragma pack(1)
typedef struct{
  char unk0[40];
  unsigned int file_size;
  short file_attr;
  unsigned int create_date_time;
  char unk1[2];
  char folder_name[128];
  char unk2;
  char file_name[128];
  char unk3[11];
  short wsfolder_name[128+1];
  short wsfile_name[128+1];
}DIR_ENTRY;
#pragma pack()

typedef struct
{
  char unk1;
  char unk2;
  char unk3;
  char unk4;
  unsigned int size;
  char unk5[28];
  int file_attr;
}FSTATS;


typedef struct
{
  unsigned short ch_number;
  unsigned short ci;
  unsigned short lac;
  char power;
  char c1;
  char c2;
  char unk;
  unsigned short unk2;
}RAMNET;






typedef struct
{
  int one;
  int (*onKey)(GUI *gui, GUI_MSG *msg);
  void (*global_hook_proc)(GUI *gui, int cmd);
  void *locret;
  int zero1;
  const SOFTKEYSTAB *softkeystab;
  RECT rc;
  int font;
  int _100;
  int _101;
  int zero2;






  int zero3;



  int _0x40000000;
}INPUTDIA_DESC;

typedef struct
{
  char type;
  void *user_pointer;
  unsigned short cur_item;
  WSHDR *ws;
}USR_MENU_ITEM;

typedef struct
{
  unsigned short invert;  
  unsigned short bitmask;
  char font;              
  char align;             
  char pen[4];            
  char brush[4];          
}EDITC_OPTIONS;

#pragma pack(2)
typedef struct
{
  char type;
  char unk2[3];
  int flag;
  char zero_cbox;  
  char unk5;
  EDITC_OPTIONS ed_options;
  short maxlen;
  short num_of_items_cbox;
  short start_item_cbox;
  short unk9;
  short unk10;
  short unk11;
  int unk12;
  WSHDR *pWS;
}EDITCONTROL;
#pragma pack()






















 



typedef struct
{
  short field_0;
  char no_data;
  char item_type;
  int field_4;
  void *data;
}AB_UNPRES_ITEM;

typedef struct{
  short NrOfFlds;
  short number_of_records;
  short NrAllocFlds;
  short field_6;
  short NrJ;
  char field_A;
  char field_B;
  AB_UNPRES_ITEM *record_list;
  char EntTp;
  char field_11;
  short EntId;
  int field_14;
  int field_18;
}AB_UNPRES;

#pragma pack(1)
typedef struct
{
  char _1D;
  char format;
  char data_size;
  char _0_1;
  char _0_2;

  char data[128];
}PKT_NUM;
#pragma pack()




typedef struct
{
  unsigned short family; 
  unsigned short port; 
  unsigned int ip; 
  unsigned int unk1;
  unsigned int unk2;
}SOCK_ADDR;

#pragma pack(2)
typedef struct
{
  unsigned short _0x0080;
  unsigned short _0xFFFF;
  unsigned short _0x0000;
}REGSOCKCEPID_DATA;
#pragma pack()

typedef struct
{
  char body[0x204];
}CTX_NAPDEF;

typedef struct
{
  unsigned int len;
  CTX_NAPDEF *ctx_napdef;
  unsigned int zero;
  CTX_NAPDEF napdef;
}NAP_PARAM_CONT;

typedef struct
{
  int zero;
  void *native_profile;
  char _1;
  char _4;
  unsigned short _0;
  NAP_PARAM_CONT *NapParameterContainer;
}LMAN_DATA;


typedef struct{
  unsigned short repeat_num;  
  unsigned short unk;
  int time_between_play;
  int play_first; 
  int volume;
  int unk5;
  int unk6;
  int unk7;
  int unk8;
  int unk9;
}PLAYFILE_OPT;


typedef struct
{
 char data[0xB2];
}PDU;

typedef struct
{
  const char *name_to;
  const char *name_from;
  void *data;
}IPC_REQ;

typedef struct
{
  unsigned short type; 
  WSHDR *wfilename; 
  int unk_08 ; 
  int unk_0C; 
  int unk_10 ; 
  int unk_14 ; 
  long length; 
  int unk_1C; 
  int unk_20 ; 
} TWavLen;


typedef struct
{
  char yearNormBudd; 
  char dateFormat;
  char timeFormat; 
  char timeZone; 
  char isAutoTime1; 
  char isAutoTime2;
}TDateTimeSettings;

typedef struct
{
  unsigned int type;  
  WSHDR *filename;   
  WSHDR *resolution_ws;
  int uid;            
  unsigned short width; 
  unsigned short height;
  WSHDR *duration_mp3_ws;
  unsigned int duration_mp3;
  WSHDR *duration_wav_ws; 
  unsigned int duration_wav;
  WSHDR *tag_title_ws;
  WSHDR *tag_artist_ws;
  WSHDR *tag_album_ws; 
  WSHDR *tag_track_ws; 
  WSHDR *tag_year_ws;  
  WSHDR *unk_tag_2_ws; 
  WSHDR *bitrate_ws;   
  WSHDR *audio_frequency_ws; 
  WSHDR *size_ws;   
} FILE_PROP;

typedef struct
{
  int mode; 
  int dir_enum; 
  WSHDR* path_to_file; 
  WSHDR* file_name; 
  int unk5;
  int is_exact_dir;
  int unk7;
  int unk8;
  int unk9;
  int unk10;
  int unk11;
  WSHDR* full_filename;
  int unk13;
  int (*user_handler)(void*); 
  void* this_struct_addr;
  int unk16;
  int unk17_26[10]; 
}NativeExplorerData;

typedef int  (__interwork MenuSearchCallBack)(void *gui,WSHDR * searchstr);  

#pragma diag_suppress=Ta035

#pragma swi_number=0
__swi __arm void loopback0();



#pragma swi_number=1
__swi __arm void loopback1();



#pragma swi_number=2
__swi __arm void loopback2();



#pragma swi_number=3
__swi __arm void loopback3();



#pragma swi_number=4
__swi __arm void loopback4();



#pragma swi_number=6
__swi __arm int GetAkku(int param1,int param2);



#pragma swi_number=8
__swi __arm long SetIllumination(unsigned char dev,unsigned long param1,unsigned short bright,unsigned long delay);



#pragma swi_number=0x9
__swi __arm void SwitchPhoneOff();



#pragma swi_number=10
__swi __arm int fopen(const char * cFileName, unsigned int iFileFlags, unsigned int iFileMode, unsigned int *ErrorNumber);



#pragma swi_number=11
__swi __arm int fread(int FileHandler, void *cBuffer, int iByteCount, unsigned int *ErrorNumber);



#pragma swi_number=12
__swi __arm unsigned int fwrite(int FileHandler, void const * cBuffer, int iByteCount, unsigned int *ErrorNumber);



#pragma swi_number=13
__swi __arm void fclose(int FileHandler, unsigned int *ErrorNumber);



#pragma swi_number=15
__swi __arm unsigned int lseek(int FileHandler, unsigned int offset, unsigned int origin, unsigned int *ErrorNumber, unsigned int *ErrorNumber2);



#pragma swi_number=16
__swi __arm int mkdir(const char * cFileName, unsigned int *ErrorNumber);



#pragma swi_number=18
__swi __arm int GetFileAttrib(const char *cFileName, unsigned char *cAttribute, unsigned int *ErrorNumber);



#pragma swi_number=19
__swi __arm int SetFileAttrib(const char *cFileName, unsigned char cAttribute, unsigned int *ErrorNumber);



#pragma swi_number=20
__swi __arm void *malloc(unsigned int size);



#pragma swi_number=0x8014
__swi __arm void *malloc_adr(void);

#pragma swi_number=21
__swi __arm void mfree(void *);



#pragma swi_number=0x8015
__swi __arm void *mfree_adr(void);

#pragma swi_number=22
__swi __arm int sprintf(char *buf, const char *str, ...);



#pragma swi_number=23
__swi	__arm	char * strcat (char *,const char *);



#pragma swi_number=24
__swi	__arm	char * strchr (const char *,int);



#pragma swi_number=25
__swi	__arm	int  strcmp (const char *,const char *);



#pragma swi_number=26
__swi	__arm	char * strcpy (char *dest,const char *source);



#pragma swi_number=27
__swi __arm unsigned int strlen(const char *);



#pragma swi_number=28
__swi	__arm	void  wsAppendChar(WSHDR *ws,int wchar);



#pragma swi_number=29
__swi	__arm int wsInsertChar(WSHDR *ws,int wchar,int pos);



#pragma swi_number=30
__swi	__arm IMGHDR *GetPITaddr(int num);



#pragma swi_number=33
__swi __arm int GetImgHeight(int picture);



#pragma swi_number=34
__swi __arm int GetImgWidth(int picture);



#pragma swi_number=35
__swi __arm void DrawImg(unsigned int x, unsigned int y, unsigned int picture);



#pragma swi_number=37
__swi __arm void DrawCanvas(void *data, int x1, int y1, int x2, int y2, int flag_one);



#pragma swi_number=38
__swi __arm void DrawImgBW(unsigned int x, unsigned int y, unsigned int picture, char *pen, char *brush);





#pragma swi_number=0x2C
__swi __arm  int EEFullGetBlockInfo(unsigned int block,int *size,char *version); 

#pragma swi_number=50
__swi __arm void PlaySound(long param1, long param2, long param3, long tone, long param5);



#pragma swi_number=0x0034
__swi __arm void PlaySoundLoop(int _0x2F, int param2, int duration);

#pragma swi_number=0x0035
__swi __arm void AlarmClockRing();



#pragma swi_number=42
__swi __arm int *GetEELiteBlockAddress(short blocknum);



#pragma swi_number=60
__swi __arm int setfilesize(int FileHandler, unsigned int iNewFileSize, unsigned int *ErrorNumber);




#pragma swi_number=0x0041
__swi __arm char GetProvider(WSHDR *ws, int zero);


#pragma swi_number=0x0042
__swi __arm int IsScreenSaver(void);





#pragma swi_number=67
__swi __arm int IsUnlocked(void);



#pragma swi_number=0x45
__swi __arm int GetWavLen(char *filename); 

#pragma swi_number=0x0046
__swi __arm int HasNewSMS(void);



#pragma swi_number=0x0047
__swi __arm int HasFlashSMS(void);



#pragma swi_number=0x4A
__swi __arm short PlayFile(int flags, WSHDR *foldername, WSHDR *filename, int CepId, int Msg, const PLAYFILE_OPT *sfo);



#pragma swi_number=0x004C
__swi __arm int GetMissedCallsCount(void);





#pragma swi_number=77
__swi __arm void GBS_StartTimerProc(void *htimer, long ms, void ptr());





#pragma swi_number=0x4E
__swi __arm int MsgBoxError(int flag, int LgpId);







#pragma swi_number=0x4F
__swi __arm int MsgBoxYesNo(int flag, int LgpID, void CallBackProc(int));







#pragma swi_number=0x50
__swi __arm int MsgBoxOkCancel(int flag, int LgpID, void CallBackProc(int));







#pragma swi_number=0x8052
__swi __arm char *GetIlluminationDataTable();



#pragma swi_number=0x0054
__swi __arm int StrToInt(char *s, char **endp);

#pragma swi_number=92
__swi __arm unsigned char GetCPUClock();



#pragma swi_number=93
__swi __arm unsigned char GetCPULoad();






#pragma swi_number=95
__swi __arm int GetFreeRamAvail();



#pragma swi_number=107
__swi	__arm	int  FindFirstFile (DIR_ENTRY *DIRENTRY,char *mask,unsigned int *ErrorNumber);



#pragma swi_number=108
__swi	__arm	int  FindNextFile (DIR_ENTRY *DIRENTRY,unsigned int *ErrorNumber);



#pragma swi_number=109
__swi	__arm	int  FindClose (DIR_ENTRY *DIRENTRY,unsigned int *ErrorNumber);



#pragma swi_number=0x06E
__swi	__arm int IsCalling(void);

#pragma swi_number=111
__swi __arm void RefreshGPRSTraffic();



#pragma swi_number=112
__swi __arm int *GetGPRSTrafficPointer();



#pragma swi_number=0x0073
__swi __arm int GetTypeOfCall();



#pragma swi_number=116
__swi __arm void* GetFunctionPointer(const char * _shortcut);

#pragma swi_number=124
__swi __arm unsigned int SetVibration(unsigned int power);



#pragma swi_number=128
__swi __arm int ShowCallList(int list, int zero);



#pragma swi_number=132
__swi __arm int GetFileStats(const char *cFileName, FSTATS * StatBuffer, unsigned int *errornumber);



#pragma swi_number=0x0085
__swi __arm int strcmpi(const char *s1, const char *s2);

#pragma swi_number=0x86
__swi __arm void EEFullReadBlock(int block, void *buf, int offset, int size, int cepid, int msg); 





#pragma swi_number=0x87
__swi __arm void EEFullWriteBlock(int block, void *buf, int offset, int size, int cepid, int msg);





#pragma swi_number=138
__swi __arm int GetFreeFlexSpace(int DriveNum, unsigned int *ErrorNumber);



#pragma swi_number=139
__swi __arm int GetTotalFlexSpace(int DriveNum, unsigned int *ErrorNumber);



#pragma swi_number=140
__swi __arm void RegExplorerExt(REGEXPLEXT const *);



#pragma swi_number=142
__swi __arm int fmove(const char * SourceFileName, const char * DestFileName, unsigned int *ErrorNumber);



#pragma swi_number=143
__swi __arm int rmdir(const char * cDirectory, unsigned int *ErrorNumber);



#pragma swi_number=144
__swi __arm int truncate(int FileHandler, int length, int *errornumber);



#pragma swi_number=145
__swi __arm int isdir(const char * cDirectory, unsigned int *ErrorNumber);



#pragma swi_number=146
__swi __arm void *calloc(size_t nelem, size_t elsize);



#pragma swi_number=148
__swi __arm int ExecuteFile (WSHDR *filepath, WSHDR *mimetype, void *param);



#pragma swi_number=149
__swi __arm int UnRegExplorerExt(REGEXPLEXT const *);



#pragma swi_number=0x99
__swi __arm int PlayMelodyInMem(char Unk_0x11, void * MelAddr, int MelSize, int CepId, int Msg, int Unk_0); 


#pragma swi_number=0x9e
__swi __arm int GetMissedEventCount(unsigned int Event) ;

#pragma swi_number=154
__swi int ChangeVolume(unsigned char Volume);





#pragma swi_number=163
__swi __arm void ws_2str(WSHDR *ws, char *str, unsigned int size);



#pragma swi_number=166
__swi __arm void ResetGPRSTraffic();



#pragma swi_number=170
__swi __arm char *GetCurrentLocale();




#pragma swi_number=171
__swi __arm void loopback171();



#pragma swi_number=180
__swi __arm void GetDateTime(TDate *, TTime *);




#pragma swi_number=181
__swi __arm char GetWeek(TDate*);



#pragma swi_number=182
__swi __arm char GetProfile();



#pragma swi_number=183
__swi __arm char SetProfile(char);



#pragma swi_number=184
__swi __arm int sdiv(int denom,int number);



#pragma swi_number=167
__swi __arm char IsGPRSEnabled();



#pragma swi_number=168
__swi __arm char IsGPRSConnected();



#pragma swi_number=169
__swi __arm void KbdLock();



#pragma swi_number=185
__swi __arm void KbdUnlock();



#pragma swi_number=186
__swi __arm void *realloc(void *ptr, int size);



#pragma swi_number=187
__swi __arm void *memset(void *s, int c, int n);



#pragma swi_number=188
__swi __arm int udiv(unsigned int denom,unsigned int number);



#pragma swi_number=189
__swi __arm  int DivBy10(int divident);



#pragma swi_number=0x00BF
__swi __arm void SpellTime();

#pragma swi_number=0x00C4
__swi __arm void *GetBuffer(int patch_id);

#pragma swi_number=0x00C5
__swi __arm char IsIdleUiOnTop(void);




#pragma swi_number=198
__swi __arm  char GetAkkuCapacity();




#pragma swi_number=0x088
__swi	__arm char GetAccessoryType(void);



#pragma swi_number=0x93
__swi __arm void RebootPhone();



#pragma swi_number=0x80C8
__swi __arm unsigned short *RamCap();


#pragma swi_number=0x80C9
__swi __arm unsigned short *RamLS();

#pragma swi_number=0x80CA
__swi __arm  RAMNET * RamNet();


#pragma swi_number=0x80CC
__swi __arm char * RamMissedCalls();

#pragma swi_number=0x80CD
__swi __arm char * RamMissedSMS();

#pragma swi_number=0x80D4
__swi __arm char * RamMissedMessage();

#pragma swi_number=0x80D8
__swi __arm char * RamMenuAnywhere();

#pragma swi_number=0x80DF
__swi __arm char *RamPressedKey();
 
#pragma swi_number=0x80E0
__swi __arm void * RamScreenBuffer();

#pragma swi_number=0x80E1
__swi	__arm	 unsigned int *RamMPlayer_CtrlCode();



#pragma swi_number=0x80E2
__swi	__arm	 char *RamKeyBuffer();

#pragma swi_number=0x80E4
__swi __arm void *FreeRAM();

#pragma swi_number=0x80F1
__swi __arm void *BuildCanvas(void);

#pragma swi_number=0x80FF
__swi __arm unsigned int AddrLibrary();

#pragma swi_number=0x0100
__swi __arm void GBS_SendMessage(int cepid_to, int msg, ...); 



#pragma swi_number=0x0101
__swi __arm int GBS_ReciveMessage(GBS_MSG *);



#pragma swi_number=0x0102
__swi __arm void GBS_AcceptMessage(void);



#pragma swi_number=0x0103
__swi __arm void GBS_ClearMessage(void);



#pragma swi_number=0x0104
__swi __arm void GBS_PendMessage(GBS_MSG *);



#pragma swi_number=0x0105
__swi __arm void CreateGBSproc(int cepid, const char *name, void (*onMsg)(void), int prio, int unk_zero);



#pragma swi_number=0x8106
__swi __arm CSMROOT *CSM_root();

#pragma swi_number=0x0107
__swi __arm int CreateCSM(const CSM_DESC*,void *,int);



#pragma swi_number=0x0108
__swi	__arm	CSM_RAM * FindCSMbyID (int id);



#pragma swi_number=0x0109
__swi __arm void DoIDLE(void);



#pragma swi_number=0x010A
__swi __arm void *GetConfig(unsigned int id); 

#pragma swi_number=0x810B
__swi __arm void *GetMinAdrScan(); 


#pragma swi_number=0x810C
__swi __arm void *GetMaxAdrScan(); 


#pragma swi_number=0x810D
__swi __arm unsigned short *GetCI();

#pragma swi_number=0x010E
__swi __arm void Vibration(unsigned int power, unsigned int duration); 

#pragma swi_number=0x010F
__swi __arm void freeUSSD();



#pragma swi_number=0x0110
__swi __arm char *wstrcopy(unsigned short *dst, const unsigned short *src);



#pragma swi_number=0x0111
__swi __arm char GetTypeUSSD();



#pragma swi_number=0x0112
__swi __arm unsigned int SetUSSD(StructUSSDStr *);



#pragma swi_number=0x0113
__swi	__arm	char * strpbrk (const char *s1,const char *s2);

#pragma swi_number=0x0113
__swi __arm int strcspn(const char *s1, const char *s2);



#pragma swi_number=0x0114
__swi	__arm	char * strncat (char *dest,const char *substr,int maxSubLen);



#pragma swi_number=0x0115
__swi	__arm	int  strncmp (const char *s1,const char *s2,int n);



#pragma swi_number=0x0116
__swi	__arm	int  strncpy (char *dest,const char *source,int maxlen);



#pragma swi_number=0x0117
__swi	__arm	char * strrchr (const char *s,int c);



#pragma swi_number=0x0118
__swi	__arm	char * strstr (const char *s1,const char *s2);















#pragma swi_number=0x011B
__swi	__arm	int snprintf (char *,int n,const char *format,...);



#pragma swi_number=0x011C
__swi	__arm	int  memcmp (const void *m1,const void *m2,int n);



#pragma swi_number=0x011D
__swi	__arm	void  zeromem (void *dest,int n);




#pragma swi_number=0x011E
__swi	__arm	void * memcpy (void *dest,const void *source,int cnt);



#pragma swi_number=0x011F
__swi	__arm	WSHDR * wstrcpy (WSHDR *wshdr_d,WSHDR *wshdr_s);



#pragma swi_number=0x0120
__swi	__arm	WSHDR * wstrncpy (WSHDR *,WSHDR *,int);



#pragma swi_number=0x0121
__swi	__arm	WSHDR * wstrcat (WSHDR *wshdr_d,WSHDR *wshdr_s);



#pragma swi_number=0x0122
__swi	__arm	WSHDR * wstrncat (WSHDR *wshdr_d,WSHDR *wshdr_s,int n);



#pragma swi_number=0x0123
__swi	__arm	int  wstrlen (WSHDR *wshdr);



#pragma swi_number=0x0124
__swi	__arm	int wsprintf (WSHDR *,const char *format,...);



#pragma swi_number=0x0125
__swi	__arm	WSHDR * AllocWS (int len);



#pragma swi_number=0x0126
__swi	__arm	void  CutWSTR (void *WSHDR,int len);



#pragma swi_number=0x0127
__swi	__arm	WSHDR * CreateLocalWS (WSHDR *wshdr,unsigned short *wsbody,int len);



#pragma swi_number=0x0128
__swi	__arm	int  CreateWS (void *malloc,void *mfree,int len);



#pragma swi_number=0x0129
__swi	__arm	void  FreeWS (WSHDR *wshdr);




#pragma swi_number=0x012A
__swi	__arm	void  DrawObject (DRWOBJ *);



#pragma swi_number=0x02F0
__swi __arm int PushDRWOBJOnLAYER(DRWOBJ_S*, LCDLAYER *);

#pragma swi_number=0x02F1
__swi __arm int LCDRedrawLAYER(LCDLAYER *);

#pragma swi_number=0x012B
__swi	__arm	void  AddKeybMsgHook (void *proc);



#pragma swi_number=0x012C
__swi	__arm	int  AddKeybMsgHook_end (void *proc);



#pragma swi_number=0x012D
__swi	__arm	void  RemoveKeybMsgHook (void *proc);



#pragma swi_number=0x012E
__swi	__arm	char *GetPaletteAdrByColorIndex (int ColorIndex);






#pragma swi_number=0x012F
__swi	__arm	void  getRGBcolor (int ColorIndex,void *dest);



#pragma swi_number=0x0130
__swi	__arm	void  getRGBbyPaletteAdr (int *paletteAdr,void *dest);



#pragma swi_number=0x0131
__swi	__arm	void  setColor (int a,int r,int g,int b,void *dest);



#pragma swi_number=0x0132
__swi __arm void *memmove(void *dest,const void *source,int cnt);




#pragma swi_number=0x0133
__swi	__arm	void  StoreXYWHtoRECT (void *RECT,int x,int y,int w,int h);



#pragma swi_number=0x0134
__swi	__arm	void  StoreXYXYtoRECT (void *RECT,int x,int y,int x2,int y2);



#pragma swi_number=0x0135
__swi	__arm	int  IsGuiOnTop (int id);



#pragma swi_number=0x0136
__swi	__arm	int  CreateGUI_ID (void *gui,int id);



#pragma swi_number=0x0137
__swi	__arm	int  CreateGUI (void *gui);



#pragma swi_number=0x0138
__swi	__arm	int  CreateGUI_30or2 (void *gui);



#pragma swi_number=0x0139
__swi	__arm	int  CreateGUIWithDummyCSM (void *gui,int flag);



#pragma swi_number=0x013A
__swi	__arm	int  CreateGUIWithDummyCSM_30or2 (void *gui,int flag);



#pragma swi_number=0x013B
__swi	__arm	void  GeneralFuncF1 (int cmd);



#pragma swi_number=0x013C
__swi	__arm	void  GeneralFuncF0 (int cmd);

#pragma swi_number=0x013D
__swi	__arm	void  GeneralFunc_flag1 (int id,int cmd);

#pragma swi_number=0x013E
__swi	__arm	void  GeneralFunc_flag0 (int id,int cmd);



#pragma swi_number=0x013F
__swi	__arm	void DirectRedrawGUI (void);



#pragma swi_number=0x0140
__swi	__arm	void  DirectRedrawGUI_ID (int id);



#pragma swi_number=0x0141
__swi	__arm	void PendedRedrawGUI (void);




#pragma swi_number=0x0142
__swi	__arm	CSM_RAM * FindCSM (void *csm_q,int id);



#pragma swi_number=0x0143
__swi	__arm	void  GBS_StartTimer (GBSTMR *tmr,int time,int msg,int unk,int cepid);



#pragma swi_number=0x0144
__swi	__arm	void  GBS_StopTimer (GBSTMR *tmr);



#pragma swi_number=0x0145
__swi	__arm	int GBS_GetCurCepid (void);



#pragma swi_number=0x0146
__swi	__arm	void LockSched(void);



#pragma swi_number=0x0147
__swi	__arm	void UnlockSched(void);



#pragma swi_number=0x0148
__swi	__arm	extern int ShowMSG(int flag, int lgp_id);







#pragma swi_number=0x0149
__swi	__arm	void SetPropTo_Obj1(DRWOBJ *drwobj,void *rect,int rect_flag,WSHDR *wshdr,int font,int text_flag);



#pragma swi_number=0x014A
__swi	__arm	void FreeDrawObject_subobj(DRWOBJ *drwobj);



#pragma swi_number=0x014B
__swi	__arm	void SetColor(DRWOBJ *drwobj, const char *color1, const char *color2);



#pragma swi_number=0x014C
__swi	__arm	void DrawString(WSHDR *WSHDR,int x1,int y1,int x2,int y2,int font,int text_attribute,const char *Pen,const char *Brush);



#pragma swi_number=0x014D
__swi	__arm	GUI *GetTopGUI(void);



#pragma swi_number=0x014E
__swi	__arm	void *FindItemByID(GUI *gui,int id);



#pragma swi_number=0x014F
__swi	__arm	void *GetDataOfItemByID(GUI *gui,int id);



#pragma swi_number=0x0150
__swi	__arm	void DrawRoundedFrame(int x1,int y1,int x2,int y2,int x_round,int y_round,int flags,const char *pen,const char *brush);



#pragma swi_number=0x0151
__swi	__arm	void SetPropTo_Obj5(DRWOBJ *, RECT *, int zero, IMGHDR *Image);



#pragma swi_number=0x0152
__swi	__arm	int CreateMenu(int is_small,int zero1,const MENU_DESC *menu, const HEADER_DESC *hdr,int start_item,int n_items,void *user_pointer,int *to_remove);



#pragma swi_number=0x0153
__swi	__arm	int GBS_RecActDstMessage(GBS_MSG *);



#pragma swi_number=0x0154
__swi	__arm	void KillGBSproc(int cepid);








#pragma swi_number=0x0155
__swi __arm png_structp png_create_read_struct(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn);



#pragma swi_number=0x0156
__swi __arm png_infop png_create_info_struct(png_structp png_ptr);



#pragma swi_number=0x0157
__swi __arm void png_destroy_read_struct(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr, png_infopp end_info_ptr_ptr);



#pragma swi_number=0x0158
__swi __arm void png_set_sig_bytes(png_structp png_ptr,int num_bytes);



#pragma swi_number=0x0159
__swi __arm void png_read_info(png_structp png_ptr, png_infop info_ptr);



#pragma swi_number=0x015A
__swi __arm png_uint_32 png_get_IHDR(png_structp png_ptr,png_infop info_ptr, png_uint_32 *width, png_uint_32 *height, int *bit_depth, int *color_type, int *interlace_method, int *compression_method, int *filter_method);



#pragma swi_number=0x015B
__swi __arm png_voidp png_malloc(png_structp png_ptr, png_uint_32 size);



#pragma swi_number=0x015C
__swi __arm void png_read_image(png_structp png_ptr, png_bytepp image);



#pragma swi_number=0x015D
__swi __arm void png_read_end(png_structp png_ptr, png_infop info_ptr);



#pragma swi_number=0x015E
__swi __arm png_voidp png_get_io_ptr(png_structp png_ptr);



#pragma swi_number=0x015F
__swi __arm png_uint_32 png_get_rowbytes(png_structp png_ptr,png_infop info_ptr);



#pragma swi_number=0x0160
__swi __arm void png_read_row(png_structp png_ptr,png_bytep row,png_bytep dsp_row);



#pragma swi_number=0x0161
__swi __arm void png_init_io(png_structp png_ptr, int fp);







#pragma swi_number=0x0162
__swi __arm int setjmp(jmp_buf jmpbuf);





#pragma swi_number=0x0163
__swi __arm EDITQ *AllocEQueue(void *malloc_a, void *mfree_a);



#pragma swi_number=0x0164
__swi __arm EDITCONTROL *PrepareEditControl(EDITCONTROL *);



#pragma swi_number=0x0165
__swi __arm void ConstructEditControl(EDITCONTROL *EditControl,int type,int flag,WSHDR *ws,int maxlen);



#pragma swi_number=0x0166
__swi __arm int AddEditControlToEditQend(void *EditQ,EDITCONTROL *EditControl,void *malloc_a);



#pragma swi_number=0x0167
__swi __arm int CreateInputTextDialog(const INPUTDIA_DESC *input_desc, const HEADER_DESC *header_desc,void *editq,int do_mfree,void *user_pointer);




#pragma swi_number=0x0168
__swi __arm void SetSoftKey(void *gui,const SOFTKEY_DESC *,int n);



#pragma swi_number=0x0169
__swi __arm int ExtractEditControl(void *guidata,int n,EDITCONTROL *);


#pragma swi_number=0x016A
__swi __arm int StoreEditControl(void *guidata,int n,EDITCONTROL *);

#pragma swi_number=0x016B
__swi __arm int unlink(const char *cFileName,unsigned int *errornumber);



#pragma swi_number=0x016C
__swi __arm int str_2ws(WSHDR *ws,const char *str,unsigned int size);



#pragma swi_number=0x016D
__swi __arm int UnpackABentry(AB_UNPRES *,void *abentry,int filesz,int flag);



#pragma swi_number=0x016E
__swi __arm int FreeUnpackABentry(AB_UNPRES *, void *mfree_adr);



#pragma swi_number=0x016F
__swi __arm int GetTypeOfAB_UNPRES_ITEM(int);



#pragma swi_number=0x0170
__swi __arm int MakeVoiceCall(const char *number,int _0x10, int _0x20C0);



#pragma swi_number=0x0171
__swi __arm void SUBPROC(void *,...); 

#pragma swi_number=0x0172
__swi __arm void REDRAW(void);




#pragma swi_number=0x0173
__swi __arm int socket(int af,int type,int protocol);

#pragma swi_number=0x0174
__swi __arm int connect(int sock,SOCK_ADDR *,int name_length);

#pragma swi_number=0x0175
__swi __arm int bind(int sock,SOCK_ADDR *,int name_length);

#pragma swi_number=0x0176
__swi __arm int closesocket(int socket);

#pragma swi_number=0x0177
__swi __arm int shutdown(int socket,int how);

#pragma swi_number=0x0178
__swi __arm int recv(int socket,void *buf,int len,int flag);

#pragma swi_number=0x0179
__swi __arm int send(int socket,const void *buf,int len,int flag);

#pragma swi_number=0x017A
__swi __arm unsigned short htons(unsigned short);

#pragma swi_number=0x017B
__swi __arm unsigned int htonl(unsigned int);

#pragma swi_number=0x817C
__swi __arm int *socklasterr(void);




#pragma swi_number=0x017D
__swi __arm void SetIDLETMR(int time_ms,int msg);



#pragma swi_number=0x017E
__swi __arm void RestartIDLETMR(void);



#pragma swi_number=0x017F
__swi __arm void DisableIDLETMR(void);



#pragma swi_number=0x0180
__swi __arm int EDIT_GetItemNumInFocusedComboBox(void *gui);



#pragma swi_number=0x0181
__swi __arm void EDIT_SetTextToFocused(void *gui,WSHDR *ws);



#pragma swi_number=0x0182
__swi __arm int EDIT_GetFocus(void *gui);



#pragma swi_number=0x0183
__swi __arm int EDIT_GetUnFocus(void *gui);



#pragma swi_number=0x0184
__swi __arm void ConstructComboBox(EDITCONTROL *EditControl,int type,int attr,WSHDR*,int maxlen,int unk_zero,int num_of_items,int start_item);



#pragma swi_number=0x0185
__swi __arm int GBS_WaitForMsg(const int *msg_list, int msgs_num, GBS_MSG*, int timeout);



#pragma swi_number=0x0186
__swi __arm int RegisterCepidForSocketWork(REGSOCKCEPID_DATA *);



#pragma swi_number=0x0187
__swi __arm int RequestLMANConnect(LMAN_DATA *);



#pragma swi_number=0x8188
__swi __arm int ScreenW(void);


#pragma swi_number=0x8189
__swi __arm int ScreenH(void);


#pragma swi_number=0x818A
__swi __arm int HeaderH(void);


#pragma swi_number=0x818B
__swi __arm int SoftkeyH(void);


#pragma swi_number=0x018C
__swi __arm void GBS_DelTimer(GBSTMR *);



#pragma swi_number=0x018D
__swi __arm int available0(int sock);



#pragma swi_number=0x018E
__swi __arm void GPRS_OnOff(int on, int _1);



#pragma swi_number=0x018F
__swi __arm int GetCurMenuItem(void *gui);



#pragma swi_number=0x0190
__swi __arm void MutexCreate(MUTEX *mtx);



#pragma swi_number=0x0191
__swi __arm void MutexDestroy(MUTEX *mtx);



#pragma swi_number=0x0192
__swi __arm void MutexLock(MUTEX *mtx);



#pragma swi_number=0x0193
__swi __arm void MutexLockEx(MUTEX *mtx, int flag);



#pragma swi_number=0x0194
__swi __arm void MutexUnlock(MUTEX *mtx);



#pragma swi_number=0x0195
__swi __arm void SetMenuItemIcon(void *gui,int item_n,int icon_n);



#pragma swi_number=0x0196
__swi __arm void RefreshGUI(void);



#pragma swi_number=0x0197
__swi __arm void *AllocMenuItem(void *gui);



#pragma swi_number=0x0198
__swi __arm WSHDR *AllocMenuWS(void *gui, int len);



#pragma swi_number=0x0199
__swi __arm void SetMenuItemIconArray(void *gui,void *item,const int *icons);



#pragma swi_number=0x019A
__swi __arm void SetMenuItemText(void *gui,void *item,WSHDR *text,int item_n);



#pragma swi_number=0x019B
__swi __arm void EDIT_SetFocus(void *gui, int item);



#pragma swi_number=0x019C
__swi __arm void SEQKILLER(void *data, void(*next_in_seq)(void *), void *data_to_kill);
#pragma swi_number=0x819C
__swi __arm void *SEQKILLER_ADR();


#pragma swi_number=0x019D
__swi __arm long long getCpuUsedTime_if_ena(void);



#pragma swi_number=0x019E
__swi __arm void StartCpuUsageCount(void);




#pragma swi_number=0x019F
__swi __arm int inflateInit2_ (z_streamp strm, int windowBits,const char *version, int stream_size);



#pragma swi_number=0x01A0
__swi __arm int inflate (z_streamp strm, int flush);



#pragma swi_number=0x01A1
__swi __arm int inflateEnd (z_streamp strm);




#pragma swi_number=0x01A2
__swi __arm int ActivateDialUpProfile(unsigned int cep_id,int profile_num);



#pragma swi_number=0x01A3
__swi __arm int GetCurrentGPRSProfile(void);



#pragma swi_number=0x01A4
__swi __arm int GetDisconnectTime(void);



#pragma swi_number=0x01A5
__swi __arm void RegisterCepIdForCurProfile(unsigned int cep_id,int profile_num,unsigned int csd_or_gprs);



#pragma swi_number=0x01A6
__swi __arm int IsTimerProc(GBSTMR *);



#pragma swi_number=0x1A7
__swi __arm char* Get_CC_NC();







#pragma swi_number=0x1A8
__swi __arm png_structp png_create_read_struct_2(png_const_charp user_png_ver, png_voidp error_ptr,
                                                 png_error_ptr error_fn, png_error_ptr warn_fn, png_voidp mem_ptr,
                                                 png_malloc_ptr malloc_fn, png_free_ptr free_fn);



#pragma swi_number=0x1A9
__swi __arm void png_set_read_fn(png_structp png_ptr, png_voidp io_ptr, png_rw_ptr read_data_fn);



#pragma swi_number=0x1AA
__swi __arm void png_read_update_info(png_structp png_ptr,void *info_ptr);



#pragma swi_number=0x1AB
__swi __arm void png_set_palette_to_rgb(png_structp png_ptr);



#pragma swi_number=0x1AC
__swi __arm png_uint_32 png_get_valid(png_structp png_ptr,png_infop info_ptr, png_uint_32 flag);



#pragma swi_number=0x1AD
__swi __arm void png_set_tRNS_to_alpha(png_structp png_ptr);



#pragma swi_number=0x1AE
__swi __arm void png_set_filler(png_structp png_ptr,png_uint_32 filler, int flags);



#pragma swi_number=0x1AF
__swi __arm void png_set_strip_16(png_structp png_ptr);



#pragma swi_number=0x1B0
__swi __arm void png_set_packing(png_structp png_ptr);



#pragma swi_number=0x1B1
__swi __arm void png_set_gray_to_rgb(png_structp png_ptr);



#pragma swi_number=0x1B2
__swi __arm int png_check_sig(png_bytep sig, int num);






#pragma swi_number=0x1B3
__swi __arm void DrawLine(int x,int y,int x2,int y2,int type,const char *pen);



#pragma swi_number=0x1B4
__swi __arm void DrawRectangle(int x,int y,int x2,int y2,int flags,const char *pen,const char *brush);



#pragma swi_number=0x81B5
__swi int isNewSGold(void);


#pragma swi_number=0x1B6
__swi __arm int async_gethostbyname(const char *host_name,int ****DNR_RES,int *DNR_ID);




#pragma swi_number=0x1B7
__swi __arm unsigned int str2ip(const char *);




#pragma swi_number=0x81B8
__swi __arm void *EXT_TOP(void);

#pragma swi_number=0x81B9
__swi __arm void *PNG_TOP(void);

#pragma swi_number=0x81BA
__swi __arm void *LIB_TOP(void);

#pragma swi_number=0x81BB
__swi __arm SFN_DATA *DATA_N_SFB(void);





#pragma swi_number=0x1BC
__swi __arm void SHA1_Init(SHA_CTX *c);



#pragma swi_number=0x1BD
__swi __arm void SHA1_Update(SHA_CTX *c, const void *data, unsigned long len);



#pragma swi_number=0x1BE
__swi __arm void SHA1_Final(char *md, SHA_CTX *c);



#pragma swi_number=0x1BF
__swi __arm RSA * RSA_new_method(RSA_METHOD *method);



#pragma swi_number=0x1C0
__swi __arm void RSA_free (RSA *r);



#pragma swi_number=0x1C1
__swi __arm int RSA_sign(int type, char *m, unsigned int m_len, char *sigret, unsigned int *siglen, RSA *rsa);



#pragma swi_number=0x1C2
__swi __arm BIGNUM *BN_bin2bn(const char *s,int len,BIGNUM *ret);






#pragma swi_number=0x1C3
__swi __arm void SetMenuItemCount(void *gui,int n);




#pragma swi_number=0x1C4
__swi __arm void SetCursorToMenuItem(void *gui,int n);




#pragma swi_number=0x1C5
__swi __arm int GetFontYSIZE(int font);




#pragma swi_number=0x1C6
__swi __arm void EDIT_ExtractFocusedControl(void *gui,EDITCONTROL *ec);



#pragma swi_number=0x1C7
__swi __arm int EDIT_StoreControlToFocused(void *gui,EDITCONTROL *ec);



#pragma swi_number=0x1C8
__swi __arm EDITC_OPTIONS *PrepareEditCOptions(EDITC_OPTIONS *ec_options);



#pragma swi_number=0x1C9
__swi __arm void SetInvertToEditCOptions(EDITC_OPTIONS *ec_options, int invert);



#pragma swi_number=0x1CA
__swi __arm void SetFontToEditCOptions(EDITC_OPTIONS *ec_options, int font);



#pragma swi_number=0x1CB
__swi __arm void SetAlignToEditCOptions(EDITC_OPTIONS *ec_options, int align);



#pragma swi_number=0x1CC
__swi __arm void SetPenColorToEditCOptions(EDITC_OPTIONS *ec_options, int pen);



#pragma swi_number=0x1CD
__swi __arm void SetBrushColorToEditCOptions(EDITC_OPTIONS *ec_options, int brush);



#pragma swi_number=0x1CE
__swi __arm void CopyOptionsToEditControl(EDITCONTROL *ec,EDITC_OPTIONS *ec_options);




#pragma swi_number=0x1CF
__swi __arm REGEXPLEXT *get_regextpnt_by_uid(int uid);





#pragma swi_number=0x1D0
__swi __arm int GetExtUid_ws(WSHDR * ext);





#pragma swi_number=0x1D1
__swi __arm void EDIT_RemoveEditControl(void *gui,int n);



#pragma swi_number=0x1D2
__swi __arm void EDIT_InsertEditControl(void *gui,int n,EDITCONTROL *);



#pragma swi_number=0x1D3
__swi __arm int EDIT_GetCursorPos(void *gui);



#pragma swi_number=0x1D4
__swi __arm void EDIT_SetCursorPos(void *gui, int pos);



#pragma swi_number=0x1D5
__swi __arm char *Get_Phone_Info(int InfoIndex);



#pragma swi_number=0x1D6
__swi __arm void png_set_gray_1_2_4_to_8(png_structp png_ptr);



#pragma swi_number=0x1D7
__swi __arm void png_set_invert_mono(png_structp png_ptr);



#pragma swi_number=0x1D8
__swi __arm int EDIT_IsMarkModeActive(void *gui);



#pragma swi_number=0x1D9
__swi __arm int EDIT_GetMarkedText(void *gui,WSHDR *dest);



#pragma swi_number=0x1DA
__swi __arm void SendSMS(WSHDR *ws,const char *num,int cepid,int msg,int flag);



#pragma swi_number=0x81DB
__swi __arm PDU *IncommingPDU(void);


#pragma swi_number=0x1DC
__swi __arm short wstrchr(WSHDR *ws,unsigned int start_pos,unsigned int wchar);



#pragma swi_number=0x1DD
__swi __arm short wstrrchr(WSHDR *ws,unsigned int max_pos,unsigned int wchar);



#pragma swi_number=0x1DE
__swi __arm int EDIT_SetTextToEditControl(void *gui,int n,WSHDR *ws);



#pragma swi_number=0x1DF
__swi __arm void *EDIT_GetUserPointer(void *gui);







#pragma swi_number=0x1E0
__swi __arm void *MenuGetUserPointer(void *gui);





#pragma swi_number=0x1E1
__swi __arm int GetSymbolWidth(int wchar,int font);





#pragma swi_number=0x1E2
__swi __arm  int ws_2utf8( WSHDR *from, char *to , int *result_length, int max_len);



#pragma swi_number=0x1E3
__swi __arm int utf8_2ws(WSHDR *ws,const char *utf8_str, unsigned int maxLen);



#pragma swi_number=0x1E4
__swi __arm int GetPicNByUnicodeSymbol(int wchar);




#pragma swi_number=0x1E5
__swi __arm int EDIT_OpenOptionMenuWithUserItems(void *gui, void (*itemhandler)(USR_MENU_ITEM *item), void *user_pointer, int to_add);



#pragma swi_number=0x1E6
__swi __arm void Menu_SetItemCountDyn(void *gui, int n);





#pragma swi_number=0x1E7
__swi __arm char *GetLastJavaApplication();



#pragma swi_number=0x1E8
__swi __arm int IsNoJava();




#pragma swi_number=0x1E9
__swi __arm IMGHDR *CreateIMGHDRFromPngFile(const char *fname, int type);



#pragma swi_number=0x1EA
__swi __arm int GetMaxDynIcon(void);





#pragma swi_number=0x81EB
__swi __arm char *RAM_IMSI(void);


#pragma swi_number=0x1EC
__swi __arm void FreeDynIcon(int picture);





#pragma swi_number=0x1ED
__swi __arm int IsDynIconBusy(int picture);




#pragma swi_number=0x1EE
__swi __arm int ProgressCalculate(int current, int total);


#pragma swi_number=0x1EF
__swi __arm void SetDynIcon(int picture,IMGHDR *img,char *bitmap);





#pragma swi_number=0x1F3
__swi __arm unsigned int GetSessionAge(void);



#pragma swi_number=0x1F5
__swi __arm int sscanf(const char *, const char *, ...);



#pragma swi_number=0x1F6
__swi __arm IMGHDR* GetPitAdrBy0xE200Symbol(int uni_symbol);





#pragma swi_number=0x1F7
__swi __arm long GetFileSize(char *Filename);


#pragma swi_number=0x1F8
__swi __arm int GetPlayStatus(void);





#pragma swi_number=0x1F9
__swi __arm int SendMP_cmd(unsigned short cmd,short substract);


#pragma swi_number=0x81FB
__swi __arm char *RamMediaIsPlaying();



#pragma swi_number=0x81FA
__swi __arm char *RamVolumeStep();

#pragma swi_number=0x1FC
__swi __arm void CloseCSM(int id);





#pragma swi_number=0x201
__swi __arm void SetProp2ImageOrCanvas(DRWOBJ *, RECT *, int zero, IMGHDR *Image, int bleed_x, int bleed_y);



#pragma swi_number=0x202
__swi __arm void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int flag, char *pen, char *brush);



#pragma swi_number=0x203
__swi __arm void SetPixel(int x,int y,char *color);



#pragma swi_number=0x204
__swi __arm void drawArc(int x1,int y1,int x2,int y2,int a1,int a2,int flag,char *pen,char *brush);



#pragma swi_number=0x205
__swi __arm void SetProp2Square_v1(void);



#pragma swi_number=0x206
__swi __arm void srand(unsigned int seed);



#pragma swi_number=0x207
__swi __arm void DrawScrollString(WSHDR *WSHDR,int x1,int y1,int x2,int y2,int xdisp,int font,int text_attribute,const char *Pen,const char *Brush);



#pragma swi_number=0x208
__swi __arm int Get_WS_width(WSHDR *ws, int font);





#pragma swi_number=0x209
__swi __arm void *FindGUIbyId(int id, CSM_RAM **csm);







#pragma swi_number=0x20A
__swi __arm void EDIT_SetDate(void *gui,int n,TDate *dd);




#pragma swi_number=0x20B
__swi __arm void EDIT_SetTime(void *gui,int n,TTime *tt);



#pragma swi_number=0x20C
__swi __arm void EDIT_GetDate(void *gui,int n,TDate *dd);




#pragma swi_number=0x20D
__swi __arm void EDIT_GetTime(void *gui,int n,TTime *tt);




#pragma swi_number=0x20E
__swi __arm int ConstructEditTime(EDITCONTROL *EditControl,TTime *time);



#pragma swi_number=0x20F
__swi __arm int ConstructEditDate(EDITCONTROL *EditControl,TDate *date);



#pragma swi_number=0x212
__swi __arm int CardExplGetCurItem(void *csm);



#pragma swi_number=0x213
__swi __arm void CardExplGetFName(void *csm, int cur_item, WSHDR *dest);



#pragma swi_number=0x214
__swi __arm void wstrcpybypos(WSHDR *dest,WSHDR *src,int from,int len);



#pragma swi_number=0x215
__swi __arm void wsRemoveChars(WSHDR *ws,int from,int to);





#pragma swi_number=0x216
__swi __arm void wstrcatprintf(WSHDR *,const char *format,...);



#pragma swi_number=0x217
__swi __arm int CreateMultiLinesMenu(int dummy,int dummy2,const ML_MENU_DESC *,const HEADER_DESC *,int to_item,int n);





#pragma swi_number=0x218
__swi __arm void SetMLMenuItemText(void *data,void *item,WSHDR *ws1,WSHDR *ws2,int n);





#pragma swi_number=0x219
__swi __arm void *AllocMLMenuItem(void *data);





#pragma swi_number=0x21A
__swi __arm int EDIT_SetTextInvert(void *gui,int cursor_pos,int len);





#pragma swi_number=0x21B
__swi __arm void EDIT_RemoveTextInvert(void *gui);





#pragma swi_number=0x21C
__swi __arm int EDIT_IsBusy(void *gui);



#pragma swi_number=0x21D
__swi __arm int GSMTXT_Decode(WSHDR *dest,void *pkt,int len,int encoding_type, void *(*malloc_adr)(int), void (*mfree_adr)(void));



#pragma swi_number=0x21E
__swi __arm void FocusGUI(int id);







#pragma swi_number=0x21F
__swi __arm void UnfocusGUI(void);







#pragma swi_number=0x225
__swi __arm int PlayMelody_ChangeVolume(int handle,int volume);





#pragma swi_number=0x226
__swi __arm int PlayMelody_StopPlayback(int handle);





#pragma swi_number=0x227
__swi __arm int PlayMelody_PausePlayback(int handle);





#pragma swi_number=0x228
__swi __arm int PlayMelody_ResumePlayBack(int handle);





#pragma swi_number=0x229
__swi __arm void longjmp(jmp_buf, int);



#pragma swi_number=0x22A
__swi __arm void FreeGSMTXTpkt(void *pkt);





#pragma swi_number=0x8237
__swi __arm char *RamIconBar();



#pragma swi_number=0x822F
__swi __arm  TDateTimeSettings *RamDateTimeSettings(void);


#pragma swi_number=0x230
__swi __arm int GetTimeZoneShift(TDate *, TTime *, int timeZone);


#pragma swi_number=0x238
__swi __arm void SendAutoUSSDack(void);



#pragma swi_number=0x239
__swi __arm int EEFullDeleteBlock(unsigned int block,int cepid,int msg); 





#pragma swi_number=0x23A
__swi __arm  int EEFullCreateBlock(unsigned int block,int size,int version,int cepid,int msg);





#pragma swi_number=0x23B
__swi __arm void DisableIconBar(int disable); 




 
#pragma swi_number=0x23C
__swi __arm int SetCurrentGPRSProfile(int profile);





#pragma swi_number=0x23D
__swi __arm void MD5_Init(MD5_CTX *c);



#pragma swi_number=0x23E
__swi __arm void MD5_Update(MD5_CTX *c, const void *data, unsigned long len); 



#pragma swi_number=0x23F
__swi __arm void MD5_Final(unsigned char *md, MD5_CTX *c);



#pragma swi_number=0x240
__swi __arm char *MD5_Hash(const unsigned char *data, unsigned long n, unsigned char *md); 



#pragma swi_number=0x241
__swi __arm void SetDateTime(TDate *, TTime *);



#pragma swi_number=0x244
__swi __arm int Base64Encode(void *inbuf, int insize, void *outbuf, int outsize);



#pragma swi_number=0x245
__swi __arm int Base64Decode(char *inbuf, int insize, void *outbuf, int outsize, char *_null, int *unk5);



#pragma swi_number=0x246
__swi __arm int GetFileProp(FILE_PROP *wl,WSHDR *file,WSHDR *folder); 






#pragma swi_number=0x24B
__swi __arm void SetMenuSearchCallBack(void *gui, MenuSearchCallBack proc);



#pragma swi_number=0x24C
__swi __arm int  GetPeripheryState (int device, int check_state); 




#pragma swi_number=0x24D
__swi __arm int PlayMelody_SetPosition(int handle, int pos_ms);





#pragma swi_number=0x24E
__swi __arm void* GetPlayObjById(int handle);



#pragma swi_number=0x24F
__swi __arm int GetPlayObjPosition(void *playobj_3D0, int *pos_ms);




#pragma swi_number=0x250
__swi __arm int GetPlayObjDuration(void *playobj_3D0, int *pos_ms);




#pragma swi_number=0x254
__swi __arm int StartNativeExplorer(NativeExplorerData* data);





#pragma swi_number=0x255
__swi __arm void MenuSetUserPointer(void *gui,void *user_pointer);




#pragma swi_number=0x257
__swi __arm char *RamIsSendReceiveBT();


#pragma swi_number=0x258
__swi __arm int CalcBitmapSize(short w,short h, char type);



typedef int HObj; 

#pragma swi_number=0x259
__swi __arm HObj Obs_CreateObject(int uid_in, int uid_out, int prio, int msg_callback, int emb4, int sync,unsigned int *ErrorNumber);




#pragma swi_number=0x25A
__swi __arm int Obs_DestroyObject(HObj hObj);




#pragma swi_number=0x25B
__swi __arm int Obs_SetInput_File (HObj hObj, int unk_zero, WSHDR *path);




#pragma swi_number=0x25C
__swi __arm int Obs_GetInputImageSize (HObj hObj, short *w, short *h);



#pragma swi_number=0x25D
__swi __arm int Obs_SetOutputImageSize (HObj hObj, short w, short h,int size);




#pragma swi_number=0x25E
__swi __arm int Obs_Start(HObj hObj);





#pragma swi_number=0x26E
__swi __arm int Obs_Sound_SetAMRFrmPrBuf(HObj hobj, int nof_frames);


#pragma swi_number=0x26F
__swi __arm int Obs_Sound_SetAMRFormat(HObj hobj, int format);

#pragma swi_number=0x270
__swi __arm int Obs_Sound_SetAMRDTX(HObj hobj, int dtx);

#pragma swi_number=0x271
__swi __arm int Obs_Sound_SetNofChannels(HObj hobj, int num_channels);

#pragma swi_number=0x272
__swi __arm int Obs_Sound_SetAMRMode(HObj hobj, int data_rate);

#pragma swi_number=0x273
__swi __arm int Obs_Sound_SetFIsRecording(HObj hobj, int fIsRecording);

#pragma swi_number=0x274
__swi __arm int Obs_Sound_SetMaxFileSize(HObj hobj, int max_file_size);

#pragma swi_number=0x275
__swi __arm int Obs_Sound_SetRecordingMode(HObj hobj, int RecordingMode);

#pragma swi_number=0x276
__swi __arm int Obs_SetOutput_File (HObj hObj, WSHDR *path);

#pragma swi_number=0x277
__swi __arm int Obs_SetOutput_Uid(HObj hObj, int OutUID);

#pragma swi_number=0x278
__swi __arm int Obs_Sound_SetBitrate(HObj hobj, int bitRate);

#pragma swi_number=0x25F
__swi __arm int Obs_Output_GetPictstruct(HObj hObj, IMGHDR **img); 




#pragma swi_number=0x260
__swi __arm int Obs_Graphics_SetClipping(HObj hObj, short x, short y, short w, short h);




#pragma swi_number=0x261
__swi __arm int Obs_SetRotation(HObj hObj, int angle);



#pragma swi_number=0x262
__swi __arm int Obs_GetInfo (HObj hObj, int unk_0or1);




#pragma swi_number=0x263
__swi __arm int Obs_SetScaling (HObj hObj, int unk5);


#pragma swi_number=0x264
__swi __arm int Obs_TranslateMessageGBS (GBS_MSG *msg, OBSevent *event_handler);


#pragma swi_number=0x265
__swi __arm int Obs_Pause (HObj hObj);


#pragma swi_number=0x266
__swi __arm int Obs_Resume (HObj hObj);


#pragma swi_number=0x267
__swi __arm int Obs_Stop (HObj hObj);


#pragma swi_number=0x268
__swi __arm int Obs_Prepare (HObj hObj);

#pragma swi_number=0x269
__swi __arm int Obs_SetRenderOffset (HObj hObj,short x,short y);

#pragma swi_number=0x26A
__swi __arm int Obs_SetPosition (HObj hObj,int ms);


#pragma swi_number=0x26B
__swi __arm int Obs_Mam_SetPurpose (HObj hObj,char purpose); 

#pragma swi_number=0x26C
__swi __arm int Obs_Sound_SetVolumeEx (HObj hObj, char vol, char delta);

#pragma swi_number=0x26D
__swi __arm int Obs_Sound_GetVolume (HObj hObj, char *vol);

#pragma swi_number=0x279
__swi __arm int Obs_Sound_SetPurpose (HObj hObj,int purpose);

#pragma swi_number=0x223
__swi __arm void SetCpuClockLow();


#pragma swi_number=0x222
__swi __arm void SetCpuClockHi(int param);



#pragma swi_number=0x36 
__swi __arm void SLI_SetState(unsigned char state); 

#pragma swi_number=0x07F 
__swi __arm int rand();

#pragma swi_number=0x07F 
__swi __arm int IsPlayerOn();


#pragma swi_number=0x082
__swi __arm char *GetCurrentTrackFilename();


#pragma swi_number=0x210 
__swi __arm int GetCurGuiID(void);

#pragma swi_number=0x028
__swi __arm int getEELiteMaxID();

#pragma swi_number=0x029
__swi __arm int getEEFullMaxID();

#pragma swi_number=0x02B
__swi __arm int getEELiteBlockSizeVersion(unsigned int iBlock, int *iSize, char *iVersion);

#pragma swi_number=0x02D
__swi __arm int StartWriteEELiteBlock(unsigned int iBlock, unsigned int *iSize, unsigned int *iVersion, int *iReturn);

#pragma swi_number=0x029
__swi __arm int FinishWriteEELiteBlock(unsigned int iBlock, int *iReturn);

#pragma swi_number=0x02F
__swi __arm int DeleteEELiteBlock(unsigned int iBlock, int *iReturn) ;

#pragma swi_number=0x030
__swi __arm int WriteEELiteBlock(unsigned int iBlock, char *cData, unsigned int iBlockStartAddress, unsigned int iLength, int *iReturn);


#pragma swi_number=0x8299
__swi __arm char *RamExtendedCameraState();


#pragma swi_number=0x223 
__swi __arm int IsMediaPlayerInBackground(void);

#pragma swi_number=0x2DB 
__swi __arm void MediaSendCSM_Open(WSHDR*path, WSHDR *file);


#pragma swi_number=0x27 
__swi __arm void AddIconToIconBar(int pic, short *num);

#pragma swi_number=0x2A2 
__swi __arm char *GetLocAddr();


#pragma swi_number=0x2AC
__swi __arm  int DeleteSMS(int index, int _1);

#pragma swi_number=0x2E0
__swi __arm IMGHDR *GetIMGHDRFromThemeCache(int index);






#pragma swi_number=0x2E1
__swi __arm void * RamScreen();


#pragma swi_number=0x2E2
__swi __arm void PlayBack();


#pragma swi_number=0x2C7
__swi __arm int GetSecondsFromDateTimeSince1997(int *result, TDate *date, TTime *time);


#pragma swi_number=0x1FF
__swi __arm void MEDIA_PLAYLAST();

#pragma swi_number=0x81FF
__swi __arm int* MEDIA_PLAYLASTadr();


#pragma swi_number=0x2AE
__swi __arm void *GetHeaderPointer(void *gui);



#pragma swi_number=0x2AF
__swi __arm void SetHeaderText(void *hdr_pointer, WSHDR *txt, void *malloc_adr, void *mfree_adr);












 


#pragma swi_number=0x8300
__swi __arm  int isSGoldX75();

#pragma swi_number=0x0301
__swi __arm  int EDL_load(char *fname);

#pragma swi_number=0x0302
__swi __arm  int EDL_unload(char *name, short version);

#pragma swi_number=0x0303
__swi __arm  int EDL_addlib(void *edl_struct);

#pragma swi_number=0x0304
__swi __arm  int EDL_remove(void *edl_struct);

#pragma swi_number=0x0305
__swi __arm  int EDL_use(char *name, short version, void *func_struct);

#pragma swi_number=0x0306
__swi __arm  int isEDL_exist(char *name, short version);

#pragma swi_number=0x0307
__swi __arm  int isEDL_support(char platform, char *phone, short sw);

#pragma swi_number=0x0308
__swi __arm void *getEDL_baseAddr();

#pragma swi_number=0x0309
__swi __arm  int getEDL_curLibs();

#pragma swi_number=0x030A
__swi __arm  int getEDL_maxLibs();

#pragma swi_number=0x030B
__swi __arm  int SetSWIHookInRAMState();

#pragma swi_number=0x030C
__swi __arm void SetSWINumInCashe(short swinum);

#pragma swi_number=0x030D
__swi __arm  int RunSWIFromCashe(void *R0, ...);

#pragma swi_number=0x030E
__swi __arm  int SetSWIFunc(void *addrfunc, short swinum);

#pragma swi_number=0x030F
__swi __arm  int RepairSWIFunc(short swinum);

#pragma swi_number=0x0310
__swi __arm  int RepairSWILib();

typedef struct { 
  char chip_addr; 
  char unk1;
  char unk2;
  char unk3;
  short nRegister; 
  short cb_data; 
  int (*callback)(void *i2c_msg);
  void *data;
  int size;   
}I2C_MSG;
typedef struct{
  char   id_1;      
  char   cbyte;     
  char   zero;      
  char   pen[4];    
  char   brush[4];  
  RECT   rc;        
  WSHDR *text;      
  int    font;      
  short  align;     
  short  xdisp;     
}DRWOBJ_01;


#pragma swi_number=0x80F5
__swi __arm  LCDLAYER *Ram_LCD_Overlay_Layer();

#pragma swi_number=0x031A
__swi __arm  int DHS_removeProc(void (*dh_proc)(LCDLAYER *));

#pragma swi_number=0x2EC
__swi __arm int i2c_transfer(I2C_MSG *msg);

#pragma swi_number=0x2ED
__swi __arm int i2c_receive(I2C_MSG *msg);

typedef unsigned short	WORD;
typedef long		LONG;
typedef unsigned long	DWORD;

#pragma swi_number=0x0319
__swi __arm  int DHS_addProc(void (*dh_proc)(LCDLAYER *));








 












typedef enum {
	SUB_NONE,
	SUB_TO,
	SUB_FROM,
	SUB_BOTH
} JABBER_SUBSCRIPTION;

typedef enum {
	AFFILIATION_NONE,
	AFFILIATION_OUTCAST,
	AFFILIATION_MEMBER,
	AFFILIATION_ADMIN,
	AFFILIATION_OWNER
} JABBER_GC_AFFILIATION;

typedef enum {
	ROLE_NONE,
	ROLE_VISITOR,
	ROLE_PARTICIPANT,
	ROLE_MODERATOR
} JABBER_GC_ROLE;














 





                        



















typedef struct
{
  int buf_size;
  char* xml_buffer;
} IPC_BUFFER;


typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

typedef enum
{
  JS_NOT_CONNECTED,           
  JS_CONNECTED_STATE,         
  JS_ZLIB_INIT_ACK,           
  JS_ZLIB_STREAM_INIT_ACK,    
  JS_SASL_NEGOTIATION,        
  JS_SASL_NEG_ANS_WAIT,       
  JS_SASL_AUTH_ACK,           
  JS_SASL_NEW_STREAM_ACK,     
  JS_SASL_RESBIND_ACK,        
  JS_SASL_SESS_INIT_ACK,      
  JS_AUTH_OK,                 
  JS_AUTH_ERROR,              
  JS_ONLINE,                  
  JS_ERROR                    
} JABBER_STATE;



typedef enum
{
  MSG_NORMAL, 
  MSG_ME,     
  MSG_CHAT,   
  MSG_GCHAT,   
  MSG_NICKGCHAT,   
  MSG_SYSTEM,  
  MSG_STATUS,   
  MSG_SUBJECT   
} MESS_TYPE;



typedef enum
{
  T_NORMAL,       
  T_VIRTUAL,      
  T_CONF_ROOT,    
  T_CONF_NODE,    
  T_TRANSPORT,    
  T_GROUP         
}RES_TYPE;

typedef struct
{
  MESS_TYPE mtype;
  char *muc_author;
  char *mess;
  void *next;
}LOG_MESSAGE;

typedef struct
{
  JABBER_GC_AFFILIATION aff;
  JABBER_GC_ROLE role;
  char *real_jid;
}CONF_DATA;

typedef char **VCARD;

typedef struct
{
  char* name;                   
  char* full_name;              
  RES_TYPE entry_type;          
  char status;                  
  char compos:1;                  
  char* status_msg;             
  short priority;               
  unsigned int has_unread_msg;  
  unsigned int total_msg_count; 
  LOG_MESSAGE* log;             
  CONF_DATA muc_privs;          
  VCARD vcard;                  
  void* next;                   
} TRESOURCE;

typedef struct
{
  char* JID;
  char IsVisible;             
  int ResourceCount;
  TRESOURCE* res_list;
  char* name;
  JABBER_SUBSCRIPTION subscription;
  char wants_subscription;
  char group;     
  VCARD vcard; 
  void *next;
} CLIST;



typedef struct
{
  char* conf_jid; 
  char* muctema;
  void* next;
}MUC_ITEM;


typedef struct
{
  short priority;
  char status;
  char* message;
}PRESENCE_INFO;

#pragma pack(push)
#pragma pack(1)
typedef struct{
  unsigned char
  vibra_status:1,
  sound_status:1,
  off_contacts:1,
  auto_status:1,
  smiles_status:1;
  char color_name[32];
  short priority;
  char status;
  char status_text[510];
}DEF_SETTINGS;
#pragma pack(pop)


void SendAnswer(char *str);

void Vibrate(int Req_Vibra_Count);

void Play(const char *fname);

void QuitCallbackProc(int decision);

void OpenSettings(void);


void Add2History(CLIST *CListEx, char *header, char *message);
void LogStatusChange(CLIST *CListEx);

void Log(char* module, char* logstr);
void Log_XMLStream(char* logstr, int size);





 






  void CList_RedrawCList();


  void CList_ToggleVisibilityForGroup(int GID);

  int CList_GetVisibilityForGroup(int GID);


  CLIST* CList_FindContactByJID(char* jid);
  

  MUC_ITEM* CList_FindMUCByJID(char* jid);
    

  TRESOURCE* CList_IsResourceInList(char* jid);


  CLIST* CList_AddContact(char* jid,
                          char* name,
                          JABBER_SUBSCRIPTION subscription,
                          char wants_subscription,
                          char group
                          );



  void CList_ChangeContactParams(CLIST* Cont_Ex,
                          char* name,
                          JABBER_SUBSCRIPTION subscription,
                          char wants_subscription,
                          char group);

  void CList_ChangeComposingStatus(TRESOURCE* Res_Ex, char composing);
    

  void CList_MUC_SetRole(char* jid, CONF_DATA priv);


  void CList_AddMessage(char* jid, MESS_TYPE mtype, char* mtext);


  void CList_AddSystemMessage(char* jid, char status, char* status_msg);

  void CList_AddSystemMessageA(char* jid, char status, char* ansi_status_msg);

  TRESOURCE* CList_AddResourceWithPresence(char* jid, char status, char* status_msg, short priority);


  TRESOURCE* CList_GetActiveContact();


  void CList_MakeAllResourcesOFFLINE(CLIST* ClEx);


  void CList_MakeAllContactsOFFLINE();  

  void CList_Destroy();


  void CList_ToggleOfflineDisplay();


  unsigned int CList_GetNumberOfOnlineUsers();


  unsigned int CList_GetNumberOfUsers();


  unsigned int CList_GetNumberOfUsers_Visible();


  unsigned int CList_GetUnreadMessages();


  void nextUnread();


  void MoveCursorTo(TRESOURCE* NewResEx);


  int CList_isGroup(CLIST *cont);
  

  int CList_isMUC(CLIST *cont);


  void CList_Display_Popup_Info(TRESOURCE* ResEx);


  void CList_MoveCursorUp(int flagi);
  void CList_MoveCursorDown(int flagi);

  void CList_MoveCursorHome();
  void CList_MoveCursorEnd();


  void KillMsgList(LOG_MESSAGE* messtop);

  void ParseAnswer(WSHDR *ws, const char *s);
  void ExtractAnswer(WSHDR *ws);





 




typedef struct{
  void *next;
  char *name;
  char *param;
}XMLAttr;


typedef struct{
  void *next;
  void *subnode;
  char *name;
  XMLAttr *attr;
  char *value;
} XMLNode;


void* XMLDecode(char *buf, int size);


void SaveTree(XMLNode *tree);


void DestroyTree(XMLNode *tree);






 
char* XML_Get_Attr_Value(char* req_attr_name, XMLAttr* attr_list);







 
XMLNode* XML_Get_Child_Node_By_Name(XMLNode* node, char* req_node_name);









 
XMLNode* XML_Get_Child_Node_By_Name_And_Attr(XMLNode* node, char* req_node_name, char* req_attr_name, char* req_attr_velue);








typedef enum
{
  ADM_KICK,             
  ADM_BAN,              
  ADM_VOICE_REMOVE,     
  ADM_VOICE_GRANT,      
  ADM_PARTICIPANT,      
  ADM_MEMBER,           
  ADM_MODERATOR,        
  ADM_MODERATOR_REMOVE,  
  ADM_ADMIN,            
  ADM_OWNER             
}MUC_ADMIN;



typedef struct
{
  char status;
  short priority;
  char *txt;
}ONLINEINFO;



 
void Send_Mood(char *mood, char *text);



 
void SendIq(char* to, char* type, char* id, char* xmlns, XMLNode* payload);




 

void Send_Welcome_Packet();

void Send_Welcome_Packet_SASL();



 
void Send_Disconnect();




 
void Send_Auth();




 

void Send_Presence(PRESENCE_INFO *pr_info);

void Send_ShortPresence(char *to,char type);


void Send_Version_Request(char *dest_jid);


void Send_Time_Request(char *dest_jid);

void Send_Vcard_Request(char *dest_jid);


void Send_LastActivity_Request(char *dest_jid);



void Send_DiscoInfo_Request(char *dest_jid);



 

void Send_Roster_Query();

void _sendandfree(char *str);



 
void Process_Iq_Request(XMLNode* nodeEx);




 
void Process_Presence_Change(XMLNode* node);



 
void Process_Incoming_Message(XMLNode* nodeEx);


char* Get_Resource_Name_By_FullJID(char* full_jid);



 
unsigned short GetPresenceIndex(char* presence_str);



 
unsigned short GetAffRoleIndex(char* str);


void MUC_Admin_Command(char* room_name, char* room_jid, MUC_ADMIN cmd, char* reason);

typedef struct
{
  char IsGroupChat;
  char IsAttention;
  char* body;
}IPC_MESSAGE_S;

typedef struct
{
  char* room_nick;
  char* room_name;
  char* pass;
  int mess_num;
}MUC_ENTER_PARAM;


typedef struct
{
  char *bmname;
  char *mucname;
  char *nick;
  char *pass;


  void *next;
}BM_ITEM;


void SendMessage(char* jid, IPC_MESSAGE_S *mess);


void SendComposing(char* jid, IPC_MESSAGE_S *mess);


void CancelComposing(char* jid, IPC_MESSAGE_S *mess);


void MUCList_Destroy();


void Enter_Conference(char *room, char *roomnick, char *roompass, char N_messages);


void Send_Leave_Conference(char* room, char *reason);


void Set_Conference_Topic(char *room, char* topic);



 











 
void* convUTF8_to_ANSI(char* tmp_out, char *UTF8_str, unsigned int size, int* fact);

char* convUTF8_to_ANSI_STR(char *UTF8_str);

void ascii2ws(WSHDR *ws, const char *s);

int utf8_2unicode(const char **res, const char *str);

unsigned int char8to16(int c);


char* str2lower(char *st);


char *utf16_to_utf8(char **s, size_t *len);


int utf8_to_utf16(char *utf8, int cc, char *unicode16);


char* Correct_UTF8_String(char* utf8_jid);


char * ANSI2UTF8(const char * ansi_str, int maxlen);


char *Get_Param_Value(char *ch, char *req, char cut_quotes);

char * Replace_Special_Syms(char *unrep_str);

char * Mask_Special_Syms(const char *unrep_str);



char *stristr(const char *s, const char *find);



int stricmp(const char *s, const char *d);

unsigned int char16to8(unsigned int c);
void utf82win(char*d,const char *s);


long GetIDLETime(TTime intime, TDate indate);

char *utf82filename(char *str);


void CutWSStringWidth(WSHDR *ws, int width, int font);

void remove_bad_chars(char *s);


XMLNode * XML_CreateNode(char *name, char *value);

int XML_Set_Attr_Value(XMLNode *node, char *attr_name, char *attr_value);

char * XML_Get_Node_As_Text(XMLNode *node);






 



void Disp_Info(TRESOURCE* ResEx);
void Disp_From_Disco(char *jid, XMLNode *info);







 




VCARD Create_vCard();


void Free_vCard(VCARD vcard);


char *Get_VCard_Value(VCARD src, char *par_name);


void Process_vCard(char *from, XMLNode *vCard);


void vCard_Photo_Display(char *path);


int Show_vCard(char *jid);






 



void Get_Bookmarks_List();


void KillBMList();


void Process_Bookmarks_Storage(XMLNode* nodeEx);


void Disp_BM_Menu();




void tx_str(char *str);






 


typedef struct
{
  char *name;
  void *next;
}GR_ITEM;


void InitGroupsList();


int AddGroup(char *gr_name);


void KillGroupsList();


int GetGroupID(char *gr_name);


GR_ITEM* GetGroupByID(int gr_id);


char* GetGroupNameByID(int gr_id);


int GetGroupCount(void);






 



typedef struct
{
  char *nonce;
  char *cnonce;
  char *qop;
  char *rsp_auth;
  char *realm;
}SASL_AUTH_DATA;

void Send_Welcome_Packet_SASL();

void SASL_Init_Session();
void Send_Login_Packet();
void Use_Md5_Auth_Report();
void Use_Plain_Auth_Report();
void Process_Auth_Answer(char *challenge, char sendanswer);
void SASL_Open_New_Stream();
void SASL_Bind_Resource();
void Decode_Challenge(char *challenge);
void Destroy_SASL_Ctx();
void SASL_Process_Error(XMLNode *nodeEx);

void Compression_Ask();
void Compression_Init_Stream();




 





















































extern const char JABBER_SERVER[];
extern const char USERNAME[];
extern const char PASSWORD[];
extern const char RESOURCE[];
extern const char CMP_DATE[];
extern const char VERSION_NAME[];
extern const char VERSION_VERS[];
extern const char OS[];
extern const char OS_postfix[];
extern const int USE_SASL;
extern const int DELIVERY_EVENTS;
extern const int COMPOSING_EVENTS;
extern const int USE_ATTENTION;
extern const int DISPLAY_POPUPS;
extern char My_JID_full[];
extern char My_JID[];
extern char logmsg[];

extern GR_ITEM *GR_ROOT;
extern CLIST* cltop;
extern unsigned int NContacts;

extern const int EXT_VERSION_INFO;

MUC_ITEM *muctop = 0;

TTime intimes; 
TDate indates;

unsigned int m_num=0; 

extern JABBER_STATE Jabber_state;
const char* PRESENCES[12] = {"online",
                                     "chat",
                                     "away",
                                     "xa",
                                     "dnd",
                                     "invisible",
                                     "unavailable",
                                     "error",
                                     "subscribe",
                                     "subscribed",
                                     "unsubscribe",
                                     "unsubscribed"};




const char* JABBER_AFFS[] = {"none", "outcast", "member", "admin", "owner"};
const char* JABBER_ROLS[] = {"none", "visitor", "participant", "moderator"};

ONLINEINFO OnlineInfo = {0,0,0};



 

void Send_Mood(char *mood, char *text)
{
  char *reply = malloc(1024);
  char *_from = Mask_Special_Syms(My_JID_full);
  
  char mod0_t[]="<iq type='set' from='%s' id='SieJC_p%d'>"
    "<pubsub xmlns='http://jabber.org/protocol/pubsub'>"
      "<publish node='http://jabber.org/protocol/mood'>"
        "<item><mood xmlns='http://jabber.org/protocol/mood'><%s/>";
  char mod2_t[]="</mood></item></publish></pubsub></iq>";
  
  char modn_t[]="<iq type='set' from='%s' id='SieJC_p%d'>"
    "<pubsub xmlns='http://jabber.org/protocol/pubsub'>"
      "<publish node='http://jabber.org/protocol/mood'>"
        "<item><mood xmlns='http://jabber.org/protocol/mood'/>"
          "</item></publish></pubsub></iq>";  
  if (mood) 
   {
     sprintf(reply, mod0_t, _from, m_num, mood);
     if (strlen(text)>0) 
     {
       char s_t[256];
       snprintf(s_t,256,"<text>%s</text>", text);
       strcat(reply, s_t);
     }
     strcat(reply, mod2_t);
   }
  else sprintf(reply, modn_t,_from ,m_num);
  SUBPROC((void*)_sendandfree, reply);
  m_num++;
  mfree(_from);
  if (text) mfree(text);
}



 
void SendIq(char* to, char* type, char* id, char* xmlns, XMLNode* payload)
{
  XMLNode *iq, *query;
  char *xml;
  char xmlns_t[]="xmlns";
  char query_t[]="query";
  char iq_t[]="iq";
  char id_t[]="id";
  char to_t[]="to";
  char type_t[]="type";

  iq = XML_CreateNode(iq_t, 0);
  if (id)
    XML_Set_Attr_Value(iq, id_t, id);
  if (type)
    XML_Set_Attr_Value(iq, type_t, type);
  if (to)
    XML_Set_Attr_Value(iq, to_t, to);

  if(xmlns)
  {
    query = XML_CreateNode(query_t, 0);  
    XML_Set_Attr_Value(query, xmlns_t, xmlns);
    query->subnode = payload;
    iq->subnode = query;
  } else iq->subnode = payload;
  xml = XML_Get_Node_As_Text(iq);
  _sendandfree(xml);
  DestroyTree(iq);
}



 
void Send_Message(char* to, char* type, char* id, XMLNode* payload)
{
  XMLNode *message;
  char *xml;
  char message_t[]="message";
  char id_t[]="id";
  char to_t[]="to";
  char type_t[]="type";

  message = XML_CreateNode(message_t, 0);
  if (id)
    XML_Set_Attr_Value(message, id_t, id);
  if (type)
    XML_Set_Attr_Value(message, type_t, type);
  if (to)
    XML_Set_Attr_Value(message, to_t, to);

  message->subnode = payload;
  xml = XML_Get_Node_As_Text(message);
  _sendandfree(xml);
  DestroyTree(message);
}



 
void SendPresence(char* to, char* type, char* id, XMLNode* payload)
{
  XMLNode *presence;
  char *xml;
  char presence_t[]="presence";
  char id_t[]="id";
  char to_t[]="to";
  char type_t[]="type";

  presence = XML_CreateNode(presence_t, 0);
  if (id)
    XML_Set_Attr_Value(presence, id_t, id);
  if (type)
    XML_Set_Attr_Value(presence, type_t, type);
  if (to)
    XML_Set_Attr_Value(presence, to_t, to);

  presence->subnode = payload;
  xml = XML_Get_Node_As_Text(presence);
  _sendandfree(xml);
  DestroyTree(presence);
}



 

void Send_Welcome_Packet()
{

  void Send_Welcome_Packet_SASL();
  if(USE_SASL)
  {
    Send_Welcome_Packet_SASL();
    return;
  }
  char streamheader[]="<?xml version='1.0' encoding='UTF-8'?>\n"
    "<stream:stream to='%s' xmlns='jabber:client' xmlns:stream='http://etherx.jabber.org/streams' xml:lang='%s'>";
  char* buf=malloc(256);
  sprintf(buf,streamheader,JABBER_SERVER, "ru");
  SendAnswer(buf);
  mfree(buf);
  LockSched();
  strcpy(logmsg,"Send Welcome");
  UnlockSched();
}


 

void Send_Disconnect()
{
  char streamend[]="</stream:stream>";
  SendAnswer(streamend);
  strcpy(logmsg,"Send Disconnect");
}


char auth_id[] = "SieJC_auth_req";
char rost_id[] = "SieJC_rost_req";
char vreq_id[] = "SieJC_vers_req";
char priv_id[] = "SieJC_priv_req";
char treq_id[] = "SieJC_time_req";
char vcreq_id[] = "SieJC_vcard_req";
char lastact_id[] = "SieJC_lastact_req";



 

void Send_Auth()
{
  sprintf(My_JID, "%s@%s",USERNAME, JABBER_SERVER);
  sprintf(My_JID_full,"%s/%s",My_JID, RESOURCE);
  char* tmpstr = malloc(256);
  XMLNode *xml, *xml_out;
  strcpy(tmpstr, USERNAME);
  char username_t[]="username";
  char password_t[]="password";
  char resource_t[]="resource";
  strcpy(tmpstr, USERNAME);
  xml = XML_CreateNode(username_t, tmpstr);

  strcpy(tmpstr, PASSWORD);
  xml->next = XML_CreateNode(password_t, tmpstr);

  strcpy(tmpstr, RESOURCE);  
  xml_out = XML_CreateNode(resource_t, tmpstr);
  xml_out->next = xml;
  
  SendIq(0, "set", auth_id, "jabber:iq:auth", xml_out);
  mfree(tmpstr);
  LockSched();
  strcpy(logmsg,"Send auth");
  UnlockSched();
}


void _senddicoinforequest(char *dest_jid)
{
  char discoid[]="SieJC_discoinfo";
  char typ[]= "get";
  char iqd[]= "http://jabber.org/protocol/disco#info";
  SendIq(dest_jid, typ, discoid, iqd, 0);
  mfree(dest_jid);
}


void Send_DiscoInfo_Request(char *dest_jid)
{
  char *to=malloc(128);
  strcpy(to, dest_jid);
  SUBPROC((void*)_senddicoinforequest,to);
}


void _sendversionrequest(char *dest_jid)
{
  char typ[]= "get";
  char iq_v[]= "jabber:iq:version";

  SendIq(dest_jid, typ, vreq_id, iq_v, 0);
  mfree(dest_jid);
}


void Send_Version_Request(char *dest_jid)
{
  char *to=malloc(128);
  strcpy(to, dest_jid);
  SUBPROC((void*)_sendversionrequest,to);
}


void _sendtimerequest(char *dest_jid)
{
  char typ[]= "get";
  char iq_v[]= "jabber:iq:time";
  SendIq(dest_jid, typ, treq_id, iq_v, 0);
  mfree(dest_jid);
}


void Send_Time_Request(char *dest_jid)
{
  char *to=malloc(128);
  strcpy(to, dest_jid);
  SUBPROC((void*)_sendtimerequest,to);
}

void _sendvcardrequest(char *to)
{
  char vcard_t[]="vCard";
  char xmlns_t[]="xmlns";
  char typ[]= "get";
  XMLNode *vcard_xml;
  vcard_xml = XML_CreateNode(vcard_t, 0);
  XML_Set_Attr_Value(vcard_xml, xmlns_t, "vcard-temp");
  SendIq(to, typ, vcreq_id, 0, vcard_xml);
  mfree(to);
}


void Send_Vcard_Request(char *dest_jid)
{
  char *to=malloc(128);
  strcpy(to, dest_jid);
  SUBPROC((void*)_sendvcardrequest,to);
}

void _sendlastactivrequest(char *dest_jid)
{
  char typ[]= "get";
  char iq_v[]= "jabber:iq:last";
  SendIq(dest_jid, typ, lastact_id, iq_v, 0);
  mfree(dest_jid);
}

void Send_LastActivity_Request(char *dest_jid)
{
  char *to=malloc(128);
  strcpy(to, dest_jid);
  SUBPROC((void*)_sendlastactivrequest,to);
}



char *Generate_Caps()
{
  char answer[400];
  sprintf(answer, "client/mobile//SieJC %s:%i"
    "<%s"
    "<%s"
    "<%s"
    "<%s"
    "<%s"
    "<%s", VERSION_VERS, 3006, "http://jabber.org/protocol/disco#info", "http://jabber.org/protocol/muc", "jabber:iq:last", "jabber:iq:time", "jabber:iq:version", "urn:xmpp:ping");
      
  if(DELIVERY_EVENTS)
  {
    char xevents_feature[]="<" "urn:xmpp:receipts";
    strcat(answer, xevents_feature);
  }

  if(COMPOSING_EVENTS)
  {
    char xevents_feature[]="<" "http://jabber.org/protocol/chatstates";
    strcat(answer, xevents_feature);
  }

  if(USE_ATTENTION)
  {
    char xevents_feature[]="<" "urn:xmpp:attention:0";
    strcat(answer, xevents_feature);
  }
      
  SHA_CTX ctx;
  char *hash2 = malloc(256);
  zeromem(hash2,256);
  SHA1_Init(&ctx);
  SHA1_Update(&ctx, answer, strlen(answer));
  SHA1_Final(hash2,&ctx);
  char *Result_Resp = malloc(256);
  zeromem(Result_Resp, 256);
  Base64Encode(hash2, strlen(hash2),Result_Resp, 256);
  mfree(hash2);
  return Result_Resp;
}





 

void Send_Presence(PRESENCE_INFO *pr_info)
{
  extern char My_Presence;
  extern const char percent_d[];
  My_Presence = pr_info->status;
  
  
  char *caps_str = Generate_Caps();
  char *tmp_str = malloc(256);
  char* presence = malloc(1024);
  XMLNode *priority=0, *show=0, *status=0, *caps=0, *payload=0;
  char *type = 0;
  char status_t[]="status";
  char show_t[]="show";
  char c_t[]="c";
  char xmlns_t[]="xmlns";
  char node_t[]="node";
  char ver_t[]="ver";
  char hash_t[]="hash";
  char priority_t[]="priority";
  
  if(pr_info->status!=6)
  {
  
  OnlineInfo.status = pr_info->status;
  OnlineInfo.priority = pr_info->priority;
  if(OnlineInfo.txt)mfree(OnlineInfo.txt);
  if(pr_info->message)
  {
    OnlineInfo.txt = malloc(strlen(pr_info->message)+1);
    strcpy(OnlineInfo.txt, pr_info->message);
  }else OnlineInfo.txt = 0;

  if(pr_info->message)
    if(strlen(pr_info->message)>0)status =XML_CreateNode(status_t, pr_info->message);
  if(pr_info->status!=5)
  {
    sprintf(tmp_str, percent_d, pr_info->priority);
    priority = XML_CreateNode(priority_t, tmp_str);
    show = XML_CreateNode(show_t, (char*)PRESENCES[pr_info->status]);
    caps = XML_CreateNode(c_t, 0);
    XML_Set_Attr_Value(caps, xmlns_t, "http://jabber.org/protocol/caps");
    sprintf(tmp_str, "%s %s-r%d", VERSION_NAME, VERSION_VERS, 3006);
    XML_Set_Attr_Value(caps, node_t, tmp_str);
    XML_Set_Attr_Value(caps, ver_t, caps_str);
    XML_Set_Attr_Value(caps, hash_t, "sha-1");
    show->next = caps;
    priority->next = show;
    if(status) status->next = priority;
      else status=priority;
    type = 0;
    payload = status;
  }
  else type = (char*)PRESENCES[5];
  }
  else
  {
    type=(char*)PRESENCES[6];
    if(status) payload = status;
  }
  SendPresence(0, type, 0, payload);


  MUC_ITEM* m_ex = muctop;
  while(m_ex)
  {
    show = XML_CreateNode(show_t, (char*)PRESENCES[pr_info->status]);    
    if(pr_info->message) 
      if(strlen(pr_info->message)>0)
    {
      status =XML_CreateNode(status_t, pr_info->message);
      show->next = status;
    }
    caps = XML_CreateNode(c_t, 0);
    XML_Set_Attr_Value(caps, xmlns_t, "http://jabber.org/protocol/caps");
    sprintf(tmp_str, "%s %s-r%d", VERSION_NAME, VERSION_VERS, 3006);
    XML_Set_Attr_Value(caps, node_t, tmp_str);
    XML_Set_Attr_Value(caps, ver_t, caps_str);
    XML_Set_Attr_Value(caps, hash_t, "sha-1");
    caps->next = show;

    SendPresence(m_ex->conf_jid, 0, 0, caps);
    m_ex=m_ex->next;
  };
  mfree(caps_str);
  mfree(presence);
  mfree(tmp_str);
  if(pr_info->message)mfree(pr_info->message);
  if(pr_info->status==6)
  {
    Send_Disconnect();
  }
  mfree(pr_info);
  LockSched();
  strcpy(logmsg,"Send presence");
  UnlockSched();
}

void Send_ShortPresence(char *to,char type)
{
  SendPresence(to, (char*)PRESENCES[type], 0, 0);
}



 

void Send_Roster_Query()
{
  SendIq(0, "get", rost_id, "jabber:iq:roster", 0);
  LockSched();
  strcpy(logmsg,"Send roster Q");
  UnlockSched();
}


void SendMessage(char* jid, IPC_MESSAGE_S *mess)
{






 
  extern const char percent_d[];
  char* mnum_str = malloc(256);
  XMLNode *body=0, *request=0, *active=0, *attention=0;
  char body_t[]="body";
  char request_t[]="request";
  char xmlns_t[]="xmlns";
  char active_t[]="active";
  char attention_t[]="attention";
  char *type ;
  body = XML_CreateNode(body_t, mess->body);
  if(mess->IsGroupChat)
  {
    type = "groupchat";
  }else type = "chat";
  if (DELIVERY_EVENTS && !mess->IsGroupChat)
  {
    request=XML_CreateNode(request_t, 0);
    XML_Set_Attr_Value(request, xmlns_t, "urn:xmpp:receipts");
  }
  if (COMPOSING_EVENTS && !mess->IsGroupChat)
  {
    active=XML_CreateNode(active_t, 0);
    XML_Set_Attr_Value(active, xmlns_t, "http://jabber.org/protocol/chatstates");
  }
  if(request)
  {
    request->next = active;
  }
  else request = active;

  if (request)  body->next = request;

  if (USE_ATTENTION && mess->IsAttention && !mess->IsGroupChat)
  {
    attention=XML_CreateNode(attention_t, 0);
    XML_Set_Attr_Value(attention, xmlns_t, "urn:xmpp:attention:0");
    attention->next = body;
  } else attention = body;

  sprintf(mnum_str, percent_d, m_num);
  Send_Message(jid, type, mnum_str, attention);
  mfree(mnum_str);
  mfree(mess->body);
  mfree(mess);
  m_num++;
  GetDateTime(&indates, &intimes);
}

 
void SendComposing(char* jid, IPC_MESSAGE_S *mess)
{
  






 
  extern const int COMPOSING_EVENTS;
  if(!COMPOSING_EVENTS)return;
  char *type;
  if(mess->IsGroupChat)
  {
     type = "groupchat";
  }else type = "chat";

  XMLNode *composing;
  char composing_t[]="composing";
  char xmlns_t[]="xmlns";
  char *str=malloc(256);
  extern const char percent_d[];
  
  composing = XML_CreateNode(composing_t, 0);
  XML_Set_Attr_Value(composing, xmlns_t, "http://jabber.org/protocol/chatstates");
  sprintf(str, percent_d, m_num);
  Send_Message(jid, type, str, composing);

  mfree(str);
  mfree(mess);
  m_num++;
}

 
void CancelComposing(char* jid, IPC_MESSAGE_S *mess)
{
  







 
  extern const int COMPOSING_EVENTS;
  if(!COMPOSING_EVENTS)return;
  char *type;
  if(mess->IsGroupChat)
  {
     type = "groupchat";
  }else type = "chat";
  XMLNode *active;
  char active_t[]="active";
  char xmlns_t[]="xmlns";
  char *str=malloc(256);
  extern const char percent_d[];
  active = XML_CreateNode(active_t, 0);
  XML_Set_Attr_Value(active, xmlns_t, "http://jabber.org/protocol/chatstates");
  sprintf(str, percent_d, m_num);
  Send_Message(jid, type, str, active);

  mfree(str);
  mfree(mess);
  m_num++;
}


void Report_VersionInfo(char* id, char *to)
{
  char answer[200];
  char *ph_model = Get_Phone_Info(9);
  char *ph_sw = Get_Phone_Info(7);
  XMLNode *xml_name=0, *xml_version, *xml_os;
  char name_t[]="name";
  char version_t[]="version";
  char os_t[]="os";
  
  strcpy(answer, VERSION_NAME);
  xml_name = XML_CreateNode(name_t, answer);
  
  sprintf(answer, "%s-r%d (%s)", VERSION_VERS, 3006, CMP_DATE);
  xml_version = XML_CreateNode(version_t, answer);
  
  
  #pragma swi_number=0x41
  __swi __arm char GetProvider(WSHDR* name, int unk_1);

  #pragma swi_number=0x2C2
  __swi __arm int GetSubprovider(WSHDR* ws);
  
  
  
  if(EXT_VERSION_INFO)
  {
    WSHDR* prov = AllocWS(128);
    GetSubprovider(prov);
    if(!prov->wsbody[0]) GetProvider(prov, 1);
    char provider[128];
    ws_2str(prov, provider, 128);
    FreeWS(prov);
    RAMNET *net_data = RamNet();
    sprintf(answer, "SIE-%s/%s %s (%s:%ddB BAT:%d%s RAM:%dKb)", ph_model, ph_sw, OS, provider, net_data->power, *RamCap(), "%", GetFreeRamAvail()/1000);
  }
  else sprintf(answer, "SIE-%s/%s %s%s", ph_model, ph_sw, OS, OS_postfix);
  
  
  xml_os = XML_CreateNode(os_t, answer);
  xml_version->next = xml_os;
  xml_name->next = xml_version;
  SendIq(to, "result", id, "jabber:iq:version", xml_name);

  mfree(id);
  mfree(to);
}

void Report_TimeInfo(char* id, char *to)
{




 
  char answer[200];
  TTime reqt;
  TDate reqd;
  GetDateTime(&reqd, &reqt);
  int total=GetTimeZoneShift(&reqd, &reqt, RamDateTimeSettings()->timeZone);
  int hour=0;
  char znak[]="+";
  if (total<0)
  {
    total=total*(-1);
    znak[0]='-';
  };
  while(total>59)
  {
    total=total-60;
    hour++;
  };

  XMLNode *xml_utc=0, *xml_tz, *xml_display;
  char utc_t[]="utc";
  char tz_t[]="tz";
  char display_t[]="display";
  
  sprintf(answer, "%04d%02d%02dT%02d:%02d:%02d", reqd.year,reqd.month,reqd.day,reqt.hour,reqt.min,reqt.sec);
  xml_utc = XML_CreateNode(utc_t, answer);
  
  sprintf(answer, "%s%02d:%02d",znak, hour, total);
  xml_tz = XML_CreateNode(tz_t, answer);

  sprintf(answer, "%02d-%02d-%04d %02d:%02d:%02d",reqd.day,reqd.month,reqd.year,reqt.hour,reqt.min,reqt.sec);
  xml_display = XML_CreateNode(display_t, answer);
  
  xml_utc->next = xml_display;
  xml_tz->next = xml_utc;
  SendIq(to, "result", id, "jabber:iq:time", xml_tz);  
  mfree(id);
  mfree(to);
};

void Report_IDLEInfo(char* id, char *to)
{




 
  extern const char percent_d[];
  XMLNode *query;
  char xmlns_t[]="xmlns";
  char query_t[]="query";
  char seconds_t[]="seconds";

  query = XML_CreateNode(query_t, 0);  
  XML_Set_Attr_Value(query, xmlns_t, "jabber:iq:last");
  char* timestr=malloc(512);
  sprintf(timestr, percent_d, GetIDLETime(intimes, indates));

  XML_Set_Attr_Value(query, seconds_t, timestr);
  mfree(timestr);
  SendIq(to, "result", id, 0, query);

  mfree(to);
  mfree(id);
}


void Report_DiscoInfo(char* id, char *to)
{
  XMLNode *tmp, *out, *cur;
  char feature_t[]="feature";
  char var_t[]="var";
  char identity_t[]="identity";
  char category_t[]="category";
  char type_t[]="type";
  char phone_t[]="phone";
  char client_t[]="client";
  cur = XML_CreateNode(identity_t, 0);
  XML_Set_Attr_Value(cur, category_t, client_t);
  XML_Set_Attr_Value(cur, type_t, phone_t);
  out = cur;

  char *FeaturesList[9]={
  "http://jabber.org/protocol/disco#info",
  "jabber:iq:version",
  "http://jabber.org/protocol/muc",
  "jabber:iq:time",
  "jabber:iq:last",
  "urn:xmpp:ping",
  "urn:xmpp:receipts",
  "urn:xmpp:attention:0",
  "http://jabber.org/protocol/chatstates"};
  
  int featurescount;
  for(featurescount=0; featurescount<10; featurescount++)
  {
  if ((featurescount<6)||(featurescount==6 && DELIVERY_EVENTS)
  ||(featurescount==7 && USE_ATTENTION)||(featurescount==8 && COMPOSING_EVENTS))
   {
    cur = XML_CreateNode(feature_t, 0);
    XML_Set_Attr_Value(cur, var_t, FeaturesList[featurescount]);
      tmp=out;
      if(tmp)
        while(tmp->next)tmp = tmp->next;
      if(tmp)
      {
        tmp->next = cur;
      }
      else out = cur;
   }
  }
  SendIq(to, "result", id, "http://jabber.org/protocol/disco#info", out);
  mfree(id);
  mfree(to);
}

void Report_PING(char* id, char *to)
{


 
  SendIq(to, "result", id, 0, 0);
  mfree(to);
  mfree(id);
}

JABBER_SUBSCRIPTION GetSubscrType(char* subs)
{
  if(!subs)return SUB_NONE;
  if(!strcmp(subs,"none"))return SUB_NONE;
  if(!strcmp(subs,"both"))return SUB_BOTH;
  if(!strcmp(subs,"to"))return SUB_TO;
  if(!strcmp(subs,"from"))return SUB_FROM;

  return SUB_NONE;
}

char* Get_Resource_Name_By_FullJID(char* full_jid)
{
  char* pre_res = strstr(full_jid, "/");
  char* res_name = pre_res==0 ? 0 : pre_res +1;
  return res_name;
}


void Send_Initial_Presence_Helper()
{
  PRESENCE_INFO *pr_info = malloc(sizeof(PRESENCE_INFO));
  pr_info->priority = OnlineInfo.priority;
  pr_info->status=OnlineInfo.status;
  int len;
  if(OnlineInfo.txt)
  {
  if(len = strlen(OnlineInfo.txt))
  {
  char *msg = malloc(len+1);
  strcpy(msg, OnlineInfo.txt);
  msg[len]='\0';
  pr_info->message =msg;
    
  }
  }else
  pr_info->message = 0;
  Send_Presence(pr_info);

  Jabber_state = JS_ONLINE;
}


void _enterconference(MUC_ENTER_PARAM *param)
{
  char *tmp_str = malloc(256);
  XMLNode *history, *xml_x, *password, *show, *status;
  char history_t[]="history";
  char show_t[]="show";
  char status_t[]="status";
  char password_t[]="password";
  char x_t[]="x";
  char xmlns_t[]="xmlns";
  char maxstanzas_t[]="maxstanzas";
  extern const char percent_d[];
  char slash_t[]="/";
  history = XML_CreateNode(history_t, 0);
  sprintf(tmp_str, percent_d, param->mess_num);
  XML_Set_Attr_Value(history, maxstanzas_t, tmp_str);
  if(param->pass)
  {
    password=XML_CreateNode(password_t, param->pass);
    history->next=password;
  }
  xml_x = XML_CreateNode(x_t, 0);
  XML_Set_Attr_Value(xml_x, xmlns_t, "http://jabber.org/protocol/muc");
  xml_x->subnode=history;

  char *stext;
  extern char empty_str[];
  if(OnlineInfo.txt){stext= OnlineInfo.txt;}else{stext = empty_str;}
  show = XML_CreateNode(show_t, (char*)PRESENCES[OnlineInfo.status]);
  if (stext)
    if(strlen(stext)>0)
    {
      status = XML_CreateNode(status_t, stext);
      xml_x->next = status;
    }
  show->next = xml_x;
  strcpy(tmp_str, param->room_name);
  strcat(tmp_str, slash_t);
  strcat(tmp_str, param->room_nick);
  SendPresence(tmp_str, 0, 0, show);
  mfree(tmp_str);
  mfree(param->room_nick);
  mfree(param->room_name);
  if(param->pass)mfree(param->pass);
  mfree(param);
}




void Enter_Conference(char *room, char *roomnick, char *roompass, char N_messages)
{

  
  
  char IsAlreadyInList = 0;
  MUC_ITEM* m_ex = muctop;
  if(muctop)
  {
    while(m_ex)
    {
      if(stristr(m_ex->conf_jid, room)==m_ex->conf_jid)
      {
        IsAlreadyInList=1;
        break;
      }
      m_ex=m_ex->next;
    };
  }

  CLIST* Conference = CList_FindContactByJID(room);
  if(!IsAlreadyInList)
  {
    
    if(!Conference)
    {
      CList_AddContact(room,room, SUB_BOTH, 0, 129);
    }




  }
  if((Conference)&&(m_ex))
    if(Conference->res_list)
      if((Conference->res_list->status==0)&&(!strcmp(Get_Resource_Name_By_FullJID(m_ex->conf_jid),roomnick))) return; 

  
  MUC_ENTER_PARAM* par = malloc(sizeof(MUC_ENTER_PARAM));



  par->room_nick =malloc(strlen(roomnick)*2);
  par->room_name = malloc(strlen(room)*2);
  strcpy(par->room_nick, roomnick);
  strcpy(par->room_name, room);
  if(roompass)
  {
    par->pass = malloc(strlen(roompass)*2);
    strcpy(par->pass, roompass);
  }
  else par->pass = 0;
  
  if(!IsAlreadyInList)
  {
    par->mess_num=N_messages;
  }
  else par->mess_num=0;   
  SUBPROC((void*)_enterconference, par);

  if(!IsAlreadyInList)
  {
    
    MUC_ITEM* mi = malloc(sizeof(MUC_ITEM));
    mi->conf_jid = malloc(strlen(par->room_name)*2+strlen(par->room_nick)*2+2);
    sprintf(mi->conf_jid, "%s/%s", par->room_name, par->room_nick);
    mi->muctema=0;
    mi->next=0;
    m_ex = muctop;
    if(muctop)
    {
      while(m_ex->next){m_ex=m_ex->next;};
      m_ex->next = mi;
    }
    else
    {
      muctop = mi;
    }
  }
  else
  {
    
    int len = strlen(par->room_name)+strlen(par->room_nick)+2;
    m_ex->conf_jid = realloc(m_ex->conf_jid, len);
    snprintf(m_ex->conf_jid, len, "%s/%s", par->room_name, par->room_nick);
  }
}

struct muc_hlp_data {
  char *conf_jid;
  char *aux0;
};


void _leaveconference(struct muc_hlp_data *ld)
{
  extern const char DEFTEX_MUCOFFLINE[];

  char *msg=0;
  unsigned int l;
  if (!ld->aux0) {
    int len;
    if(len = strlen(DEFTEX_MUCOFFLINE))
      {
	msg = malloc(len+1);
	strcpy(msg, DEFTEX_MUCOFFLINE);
	msg[len]='\0';
      } else Send_ShortPresence(ld->conf_jid, 6);
  } else {
    l = strlen(ld->aux0);
    msg = malloc(l*2 + 1);
    strcpy(msg, ld->aux0);
    mfree(ld->aux0);
  }

  if (msg) {
    char status_t[]="status";
    XMLNode *status = XML_CreateNode(status_t, msg);
    SendPresence(ld->conf_jid, (char*)PRESENCES[6], 0, status);
    mfree(msg);
  }

  mfree(ld->conf_jid);
  mfree(ld);
}



 
void Muc_Ctl(char *room, char *str, void(proc)(struct muc_hlp_data*))
{
  struct muc_hlp_data *ld;
  unsigned int l;

  if (!room || !proc) return;  

  ld = malloc(sizeof(struct muc_hlp_data));
  ld->conf_jid = malloc(strlen(room)*2+1);
  strcpy(ld->conf_jid, room);

  if (str && (l = strlen(str))) {
    ld->aux0 = malloc(l*2+1);
    strcpy(ld->aux0, str);
  } else ld->aux0 = 0;
  
  SUBPROC((void*)proc, ld);

  return;
}


void _setconferencetopic(struct muc_hlp_data *ld)
{
  XMLNode *subject;
  char subject_t[]="subject";
  extern const char percent_d[];
  char *type = "groupchat";

  if (!ld->aux0 || !(strlen(ld->aux0)))
    goto _free;
  
  subject = XML_CreateNode(subject_t, ld->aux0);
  Send_Message(ld->conf_jid, type, 0, subject);

 _free:
  mfree(ld->conf_jid);
  mfree(ld);
}


void Send_Leave_Conference(char* room, char *reason)
{

  Muc_Ctl(room, reason, _leaveconference);
}


void Set_Conference_Topic(char *room, char* topic)
{

  Muc_Ctl(room, topic, _setconferencetopic);
}

void Leave_Conference(char* room)
{
  
  MUC_ITEM* m_ex = CList_FindMUCByJID(room);

  MUC_ITEM* m_ex2 = muctop;
  if(muctop==m_ex && muctop!=0)
  {
    mfree(m_ex->conf_jid);
    if(m_ex->muctema)mfree(m_ex->muctema);
    muctop=m_ex->next;
    mfree(m_ex);
  }
  while(m_ex2)
  {
    if(m_ex2->next==m_ex)
    {
      m_ex2->next = m_ex->next;   
      mfree(m_ex->conf_jid);
      mfree(m_ex);
      break;
    }
    m_ex2 = m_ex2->next;
  }
  ShowMSG(1,(int)"Выход из MUC выполнен!");
}



void MUCList_Destroy()
{
  LockSched();
  MUC_ITEM* cl=muctop;
  muctop=0;
  while(cl)
  {
    MUC_ITEM *p;
    mfree(cl->conf_jid);
    if(cl->muctema)mfree(cl->muctema);
    p=cl;
    cl=(MUC_ITEM*)(cl->next);
    mfree(p);
    p=0;
  }
  UnlockSched();
}




void Send_Presence_MMIStub()
{
  SUBPROC((void*)Send_Initial_Presence_Helper);
}



void ChangeRoster(XMLNode* items)
{
  XMLNode* rostEx = items;
  CLIST* Cont_Ex;
  char *name;
  char* w_subscr;
  char aname[]="jid";  
  char asub[]="subscribe";
  char aask[]="ask";
  char* jid;
  int gr_id;
  char w_subscr_flag;
  while(rostEx)
  {
    jid = XML_Get_Attr_Value(aname,rostEx->attr);
    JABBER_SUBSCRIPTION r_subscr=GetSubscrType(XML_Get_Attr_Value("subscription",rostEx->attr));
    name = XML_Get_Attr_Value("name",rostEx->attr);
    w_subscr = XML_Get_Attr_Value(aask,rostEx->attr);
    if(w_subscr)
    {
      w_subscr_flag = !strcmp(w_subscr, asub) ? 1: 0;
    }
    else
    {
      w_subscr_flag = 0;
    }
    XMLNode *group = XML_Get_Child_Node_By_Name(rostEx, "group");
    if(group)
    {
      if(!(gr_id = GetGroupID(group->value)))
      {
        gr_id = AddGroup(group->value);
      }
    }
    else gr_id = 0;
    Cont_Ex = CList_FindContactByJID(jid);
    if(Cont_Ex)
    {
      CList_ChangeContactParams(Cont_Ex,name,r_subscr, w_subscr_flag,gr_id);
    }
    else
    { 
     CList_AddContact(jid, name,r_subscr, w_subscr_flag, gr_id);
    }
    rostEx=rostEx->next;
  }
}

void FillRoster(XMLNode* items)
{
  XMLNode* rostEx = items;
  int i=0;
  char* name;
  char* w_subscr;
  char w_subscr_flag;
  while(rostEx)
  {
    JABBER_SUBSCRIPTION r_subscr=GetSubscrType(XML_Get_Attr_Value("subscription",rostEx->attr));
    name = XML_Get_Attr_Value("name",rostEx->attr);
    w_subscr = XML_Get_Attr_Value("ask",rostEx->attr);
    if(w_subscr)
    {
      w_subscr_flag = !strcmp(w_subscr, "subscribe") ? 1: 0;
    }
    else
    {
      w_subscr_flag = 0;
    }
    
    XMLNode *group = XML_Get_Child_Node_By_Name(rostEx, "group");
    int gr_id;
    if(group)
    {
      if(!(gr_id = GetGroupID(group->value)))
      {
        gr_id = AddGroup(group->value);
      }
    }
    else gr_id = 0;

    CList_AddContact(XML_Get_Attr_Value("jid",rostEx->attr),
                          name,
                          r_subscr,
                          w_subscr_flag,
                          gr_id
                          );
   

   rostEx=rostEx->next;
   i++;
  }

  
  GR_ITEM *tmp_gpointer=GR_ROOT;
  CLIST *tmp_cpointer=cltop;
  int cur_gid=-1, this_grid;   


  
  while(tmp_cpointer->next)
  {
    this_grid = ((CLIST*)tmp_cpointer->next)->group;
    
    if(cur_gid!=this_grid)
    {
      tmp_gpointer = GetGroupByID(this_grid);
      cur_gid = this_grid;
      
      CLIST *gr_pscontact = malloc(sizeof(CLIST));
      gr_pscontact->name = malloc(strlen(tmp_gpointer->name)+1);
      gr_pscontact->JID = malloc(strlen(tmp_gpointer->name)+2+(strlen(My_JID_full)));
      strcpy(gr_pscontact->name, tmp_gpointer->name);
      strcpy(gr_pscontact->JID, tmp_gpointer->name);
      strcat(gr_pscontact->JID, "@"); 
      strcat(gr_pscontact->JID, My_JID_full);
      gr_pscontact->subscription = SUB_BOTH;
      gr_pscontact->wants_subscription = 0;
      gr_pscontact->group = cur_gid;
      gr_pscontact->IsVisible = 1;
      gr_pscontact->ResourceCount=1;
      gr_pscontact->next=tmp_cpointer->next;  
      gr_pscontact->vcard=0; 
      tmp_cpointer->next = gr_pscontact;

      
      TRESOURCE* ResEx = malloc(sizeof(TRESOURCE));
      ResEx->vcard = 0;
      ResEx->log=0;
      ResEx->next=0;
      ResEx->status_msg=0;
      ResEx->muc_privs.real_jid=0;
      ResEx->status = 0;
      ResEx->has_unread_msg=0;
      ResEx->total_msg_count=0;
      ResEx->entry_type=T_GROUP;
      ResEx->name = 0;
      ResEx->full_name = malloc(strlen(tmp_gpointer->name)+2+(strlen(My_JID_full)));
      strcpy(ResEx->full_name, tmp_gpointer->name);
      strcat(ResEx->full_name, "@");
      strcat(ResEx->full_name, My_JID_full);
      
      gr_pscontact->res_list = ResEx;
      NContacts++;
      tmp_cpointer = tmp_cpointer->next;
    }
    tmp_cpointer = tmp_cpointer->next;
  }

}





 







 


void Send_Feature_Not_Implemented(char *to, char *id)
{
  if(!to || !id)return;
  XMLNode *error, *feature;
  char error_t[]="error";
  char type_t[]="type";
  char cancel_t[]="cancel";
  char featureni_t[]="feature-not-implemented";
  char xmlns_t[]="xmlns";
  char urnietf_t[]="urn:ietf:params:xml:ns:xmpp-stanzas";
  
  feature = XML_CreateNode(featureni_t, 0);
  XML_Set_Attr_Value(feature, xmlns_t, urnietf_t);
  error = XML_CreateNode(error_t, 0);
  XML_Set_Attr_Value(error, type_t, cancel_t);
  error->subnode = feature;
  SendIq(to, "error", id, 0, error);
}

void Send_Service_Unavailable(char *to, char *id)
{
  if(!to || !id)return;
  XMLNode *error, *feature;
  char error_t[]="error";
  char type_t[]="type";
  char cancel_t[]="cancel";
  char serviceun_t[]="service-unavailable";
  char xmlns_t[]="xmlns";
  char urnietf_t[]="urn:ietf:params:xml:ns:xmpp-stanzas";
  
  feature = XML_CreateNode(serviceun_t, 0);
  XML_Set_Attr_Value(feature, xmlns_t, urnietf_t);
  error = XML_CreateNode(error_t, 0);
  XML_Set_Attr_Value(error, type_t, cancel_t);
  error->subnode = feature;
  SendIq(to, "error", id, 0, error);
}



 
void Process_Iq_Request(XMLNode* nodeEx)
{
  char* iqtype = 0;
  char* id = 0;
  char *from = 0;
  char gget[]= "get";
  char gres[]= "result";
  char gerr[]= "error";
  char gset[]= "set";
  const char iq_version[]= "jabber:iq:version";
  const char disco_info[]= "http://jabber.org/protocol/disco#info";

  iqtype = XML_Get_Attr_Value("type",nodeEx->attr);
  from = XML_Get_Attr_Value("from",nodeEx->attr);
  id = XML_Get_Attr_Value("id",nodeEx->attr);


if(!iqtype) return;

if(!strcmp(gget,iqtype)) 
{
  XMLNode* query;
  char* q_type;
  if(query = XML_Get_Child_Node_By_Name(nodeEx, "query"))
  if(q_type = XML_Get_Attr_Value("xmlns", query->attr))
  {
  
  if(!strcmp(q_type,iq_version))
  {
    
    if(from)
    {
        
        

      char* loc_id = 0;
      if(id)
        {
          loc_id=malloc(strlen(id)+1);
          strcpy(loc_id,id);
        }
        char* loc_from=malloc(strlen(from)+1);
        strcpy(loc_from,from);
        SUBPROC((void*)Report_VersionInfo,loc_id, loc_from);
        return;
    }
  } 

  if(!strcmp(q_type,"jabber:iq:time"))
  {
    
    if(from)
    {
        
        

      char* loc_id = 0;
      if(id)
        {
          loc_id=malloc(strlen(id)+1);
          strcpy(loc_id,id);
        }
        char* loc_from=malloc(strlen(from)+1);
        strcpy(loc_from,from);
        SUBPROC((void*)Report_TimeInfo,loc_id, loc_from);
        return;
    }
  }

  if(!strcmp(q_type,"jabber:iq:last"))    
  {
    if(from)
    {
      char* loc_id = 0;
      if(id)
        {
          loc_id=malloc(strlen(id)+1);
          strcpy(loc_id,id);
        }
        char* loc_from=malloc(strlen(from)+1);
        strcpy(loc_from,from);
        SUBPROC((void*)Report_IDLEInfo, loc_id, loc_from);
        return;
    }
  } 

  
  if(!strcmp(q_type,disco_info))
  {
    
    if(from)
    {
        
        

      char* loc_id = 0;
      if(id)
        {
          loc_id=malloc(strlen(id)+1);
          strcpy(loc_id,id);
        }
        char* loc_from=malloc(strlen(from)+1);
        strcpy(loc_from,from);
        SUBPROC((void*)Report_DiscoInfo,loc_id, loc_from);
        return;
    }
  }
 } 
 
   if(query = XML_Get_Child_Node_By_Name(nodeEx, "ping"))
    if (q_type = XML_Get_Attr_Value("xmlns", query->attr))
  if(!strcmp(q_type,"urn:xmpp:ping"))    
  {
    if(from)
    {
      char* loc_id = 0;
      if(id)
        {
          loc_id=malloc(strlen(id)+1);
          strcpy(loc_id,id);
        }
        char* loc_from=malloc(strlen(from)+1);
        strcpy(loc_from,from);
        SUBPROC((void*)Report_PING, loc_id, loc_from);
        return;
    }
  } 

  
  Send_Feature_Not_Implemented(from, id);
}



if(!strcmp(gres,iqtype))
{
  char bind_id[]="SieJC_bind_req";
  char sess_id[]="SieJC_sess_req";
  char disco_id[]="SieJC_discoinfo";

  if(!strcmp(id, bind_id))
  {
    Jabber_state = JS_SASL_SESS_INIT_ACK;
    SASL_Init_Session();
    return;
  }

  if(!strcmp(id,auth_id) || !strcmp(id, sess_id))   
  {
    Jabber_state = JS_AUTH_OK;
    if(!cltop)
    {
      CList_AddContact(My_JID, "(Me)", SUB_BOTH,0,0);
      SUBPROC((void*)Send_Roster_Query);
    }
    else Send_Presence_MMIStub();
    return;
  }

  if(!strcmp(id,rost_id))   
  {
    XMLNode* query;
    if(!(query = XML_Get_Child_Node_By_Name(nodeEx, "query")))return;
    char* q_type = XML_Get_Attr_Value("xmlns", query->attr);
    if(!q_type)return;
    if(!strcmp(q_type,"jabber:iq:roster"))
    {
      
      FillRoster(query->subnode);
        
      extern GBSTMR TMR_Send_Presence;
      GBS_StartTimerProc(&TMR_Send_Presence, 216*1, Send_Presence_MMIStub);
      return;
    }
  }

  if(!strcmp(id,vreq_id))   
  {
    XMLNode* query;
    if(!(query = XML_Get_Child_Node_By_Name(nodeEx, "query")))return;
    char* q_type = XML_Get_Attr_Value("xmlns", query->attr);
    if(!q_type)return;
    if(!strcmp(q_type,"jabber:iq:version"))
    {
      char no_os[]="(no data)";
      char* vers_os_str;
      XMLNode *cl_name=XML_Get_Child_Node_By_Name(query, "name");
      XMLNode *cl_version=XML_Get_Child_Node_By_Name(query, "version");
      XMLNode *cl_os=XML_Get_Child_Node_By_Name(query, "os");
      if(cl_os)
      {
        vers_os_str = cl_os->value;
      }
      else
      {
        vers_os_str=no_os;
      }
      
      char *reply=malloc(512);
      snprintf(reply, 512,"Version Info:\nName:%s\nVersion:%s\nOS:%s",cl_name->value, cl_version->value, vers_os_str);
      CList_AddMessage(from, MSG_SYSTEM, reply);
      mfree(reply);
      return;
    }
  }

    if(!strcmp(id,lastact_id))   
  {
    XMLNode* query;
    if(!(query = XML_Get_Child_Node_By_Name(nodeEx, "query")))return;
    char* q_type = XML_Get_Attr_Value("xmlns", query->attr);
    if(!q_type)return;
    if(!strcmp(q_type,"jabber:iq:last"))
    {
      char *cl_sec=XML_Get_Attr_Value("seconds", query->attr);
      
      char *reply=malloc(512);
      unsigned int nsec, nmin, nhr, nd;
      extern const char percent_d[];
      sscanf(cl_sec, percent_d, &nsec);
      nmin = udiv(60, nsec);
      nsec -= nmin*60;
      nhr = udiv(60, nmin);
      nmin -= nhr*60;
      nd = udiv(24, nhr);
      nhr -= nd*24;
      snprintf(reply, 512,"IDLE: %d d. %d hr. %d min. %d sec.", nd, nhr, nmin, nsec);
      CList_AddMessage(from, MSG_SYSTEM, reply);
      mfree(reply);
      return;
    }
  }

    if(!strcmp(id,treq_id))   
  {
    XMLNode* query;
    if(!(query = XML_Get_Child_Node_By_Name(nodeEx, "query")))return;
    char* q_type = XML_Get_Attr_Value("xmlns", query->attr);
    if(!q_type)return;
    if(!strcmp(q_type,"jabber:iq:time"))
    {
      char no_display[]="(no data)";
      char* display_str;
      char* tz_str;
      XMLNode *cl_utc=XML_Get_Child_Node_By_Name(query, "utc");
      XMLNode *cl_tz=XML_Get_Child_Node_By_Name(query, "tz");
      XMLNode *cl_display=XML_Get_Child_Node_By_Name(query, "display");
      if(cl_display)
      {
        display_str = cl_display->value;
      }
      else
      {
        display_str=no_display;
      }
      if(cl_tz)
      {
        tz_str = cl_tz->value;
      }
      else
      {
        tz_str=no_display;
      }
      
      char *reply=malloc(512);
      snprintf(reply, 512,"Time Info:\nUTC:%s\nTime Zone:%s\n:>%s",cl_utc->value, tz_str, display_str);
      CList_AddMessage(from, MSG_SYSTEM, reply);
      mfree(reply);
      return;
    }
  }
  if(!strcmp(id,vcreq_id))   
  {
    XMLNode* vcard;
    if(!(vcard = XML_Get_Child_Node_By_Name(nodeEx, "vCard")))return;
    char* v_type = XML_Get_Attr_Value("xmlns", vcard->attr);
    if(!v_type)return;
    if(!strcmp(v_type,"vcard-temp"))Process_vCard(from, vcard);
  }

  if(!strcmp(id,disco_id))   
  {
    XMLNode* query;
    if(!(query = XML_Get_Child_Node_By_Name(nodeEx, "query")))return;
    char* q_type = XML_Get_Attr_Value("xmlns", query->attr);
    if(!q_type)return;
    if(!strcmp(q_type,"http://jabber.org/protocol/disco#info"))
    {
      Disp_From_Disco(from, query);
    }
  }

  if(!strcmp(id,priv_id))
  {
    XMLNode* query;
    if(!(query = XML_Get_Child_Node_By_Name(nodeEx, "query")))return;
    char* q_type = XML_Get_Attr_Value("xmlns", query->attr);
    if(!q_type)return;
    if(!strcmp(q_type,"jabber:iq:private"))
    {
      XMLNode *bm = XML_Get_Child_Node_By_Name(query, "storage");
      if(!bm)return;
      char *xmlns = XML_Get_Attr_Value("xmlns", bm->attr);
      if(!xmlns)return;
      if(!strcmp(xmlns, "storage:bookmarks"))Process_Bookmarks_Storage(bm);
      return;
    }
  }
}

if(!strcmp(gset,iqtype))
{
    XMLNode* query;
    if(query = XML_Get_Child_Node_By_Name(nodeEx, "query"))
    {
    char* q_type = XML_Get_Attr_Value("xmlns", query->attr);
    if(!q_type)return;

    if(!strcmp(q_type,"jabber:iq:roster"))
    {
      
      ChangeRoster(query->subnode);
      return;
    }
    }
    Send_Service_Unavailable(from, id);
}

if(!strcmp(gerr,iqtype)) 
{

  
  XMLNode* error = XML_Get_Child_Node_By_Name(nodeEx, "error");
  if(!error)return;
  char* errcode = XML_Get_Attr_Value("code", error->attr);

  if(errcode)
  {
    int errcode_n=0;
    extern const char percent_d[];
    sscanf(errcode,percent_d,&errcode_n);
    {
    switch (errcode_n)
      {
      case 302: sprintf(logmsg,"Redirect"); break;
      case 400: sprintf(logmsg,"Bad request"); break;
      case 401: sprintf(logmsg,"Unauthorized"); break;
      case 402: sprintf(logmsg,"Payment required"); break;
      case 403: sprintf(logmsg,"Forbidden"); break;
      case 404: sprintf(logmsg,"Not found"); break;
      case 405: sprintf(logmsg,"Not allowed"); break;
      case 406: sprintf(logmsg,"Not acceptable"); break;
      case 407: sprintf(logmsg,"Registration required"); break;
      case 408: sprintf(logmsg,"Request timeout"); break;
      case 409: sprintf(logmsg,"Conflict"); break;
      case 500: sprintf(logmsg,"Internal server error"); break;
      case 501: sprintf(logmsg,"Not mplemented"); break;
      case 502: sprintf(logmsg,"Remote server error"); break;
      case 503: sprintf(logmsg,"Service unavailable"); break;
      case 504: sprintf(logmsg,"Remote server timeout"); break;
      default:sprintf(logmsg,"ERR:%s",errcode);
      }
      MsgBoxError(1,(int)logmsg);
    }
  }
  
  if(!strcmp(id,auth_id))
  {
    Jabber_state = JS_AUTH_ERROR;
    strcat(logmsg,"\nAuth error!");
    MsgBoxError(1,(int)logmsg);
    extern void end_socket(void);
    SUBPROC((void*)end_socket);
  }
}
}


 
void Process_Presence_Change(XMLNode* node)
 {
  
   extern const char percent_d[];
   extern const int SHOWSTAT_MUCINOUT;
   extern const int SHOWSTAT_MUCCHANGESTAT;
   
char loc_actor[]="actor";
char loc_jid[]="jid";
char loc_reason[]="reason";
char loc_xmlns[]="xmlns";
char loc_x[]="x";
int priority = 0;

  CONF_DATA priv;
  char Req_Set_Role=0;
  char *real_jid = 0;
  char* from = XML_Get_Attr_Value("from",node->attr);
  if(!from)return;

  char status;
  char* msg=0;
  char* pr_type = XML_Get_Attr_Value("type",node->attr);
  if(pr_type)
  {
    status = GetPresenceIndex(pr_type);
  }
  else
  {
    XMLNode* status_node = XML_Get_Child_Node_By_Name(node,"show");
    if(!status_node)
    {
      status = 0;
      extern const char sndOnline[64];
      
      SUBPROC((void *)Play, sndOnline);
    }
    else
    {
      status = GetPresenceIndex(status_node->value);
    }

    XMLNode* statusmsg_node = XML_Get_Child_Node_By_Name(node,"status");
    if(statusmsg_node)msg = statusmsg_node->value;

    XMLNode* prio_node = XML_Get_Child_Node_By_Name(node,"priority");
    if(prio_node)
     sscanf(prio_node->value,percent_d,&priority);
  }

   
   XMLNode *x_node;

    if(x_node = XML_Get_Child_Node_By_Name_And_Attr(node,loc_x, loc_xmlns, "http://jabber.org/protocol/muc")) 
    {
      CLIST* Conference = CList_FindContactByJID(from);
      
      XMLNode* err_node = XML_Get_Child_Node_By_Name(node,"error");
      if(err_node)  
      {
        
        XMLNode* err_desc = XML_Get_Child_Node_By_Name(err_node,"text");
        if(err_desc)
        {
          if(err_desc->value)msg = err_desc->value;
          if (DISPLAY_POPUPS)
          {
            char *ansi_r = convUTF8_to_ANSI_STR(err_desc->value);
            MsgBoxError(1,(int)ansi_r);
            mfree(ansi_r);
          }
          CList_AddSystemMessage(Conference->JID,6, err_desc->value);
        }
        else
        {
          char q[40];
          char *code = XML_Get_Attr_Value("code",err_node->attr);
          sprintf(q,"ERR %s",code);
          MsgBoxError(1,(int)q);
        }
      }
    }


static char r[512];       

    if(x_node = XML_Get_Child_Node_By_Name_And_Attr(node,loc_x, loc_xmlns, "http://jabber.org/protocol/muc#user")) 
    {

      
      CLIST* Conference = CList_FindContactByJID(from);
      if(!Conference)
      {
        return;
      }
      MUC_ITEM *MucClist = CList_FindMUCByJID(Conference->JID);
      if (!MucClist) return; 
      char* nick = Get_Resource_Name_By_FullJID(from);

      
      
      XMLNode* item = XML_Get_Child_Node_By_Name(x_node,"item");
      if(status!=6) 
      {
        TRESOURCE* ResEx = CList_IsResourceInList(from);
        char* affiliation = XML_Get_Attr_Value("affiliation", item->attr);
        char* role =  XML_Get_Attr_Value("role", item->attr);
        real_jid = XML_Get_Attr_Value(loc_jid, item->attr);
        priv.aff = (JABBER_GC_AFFILIATION)GetAffRoleIndex(affiliation);
        priv.role = (JABBER_GC_ROLE)GetAffRoleIndex(role);

        if(ResEx)
        {

        if(ResEx->status!=6)
        {
          if(!(ResEx->muc_privs.aff==priv.aff && ResEx->muc_privs.role==priv.role))
          {
            sprintf(r, "%s is now %s and %s [%d->%d, %d->%d]", nick, affiliation, role, ResEx->muc_privs.aff, priv.aff, ResEx->muc_privs.role, priv.role);
            Req_Set_Role = 1;
          }
          else
          {
            if(msg)
            {
              snprintf(r, 512, "%s changed status to %s (%s)", nick, PRESENCES[status], msg);
            }
            else
            {
              sprintf(r, "%s changed status to %s", nick, PRESENCES[status]);
            }
          }
        }
        else if(real_jid)  
        {
          sprintf(r, "%s (%s) joined as %s and %s", nick, real_jid, affiliation, role);
          Req_Set_Role = 1;
        }
        else
        {
          sprintf(r, "%s joined as %s and %s", nick, affiliation, role);
          Req_Set_Role = 1;
        }

        }
        else 
        {
          if(real_jid)
        {
          sprintf(r, "%s (%s) joined as %s and %s", nick, real_jid, affiliation, role);
          Req_Set_Role = 1;
        }
        else
        {
          sprintf(r, "%s joined as %s and %s", nick, affiliation, role);
          Req_Set_Role = 1;
        }
        };

        char* my_nick = Get_Resource_Name_By_FullJID(MucClist->conf_jid);
        if ((!strcmp(nick,my_nick))&&(Conference->res_list->status==6)) 
        {
          Conference->res_list->status=0;
          ShowMSG(1,(int)"Конференция создана успешно");
        };
        if((SHOWSTAT_MUCINOUT&&Req_Set_Role)||(SHOWSTAT_MUCCHANGESTAT&&!Req_Set_Role))
         CList_AddSystemMessage(Conference->JID,0, r);
      }


      if(status==6) 
      {
        XMLNode* statusmsg_node = XML_Get_Child_Node_By_Name(node,"status");
        if (!statusmsg_node)
          sprintf(r, "%s left us", nick);
        else 
        {
         if(statusmsg_node->value) sprintf(r, "%s left us (%s)", nick, statusmsg_node->value);
           else sprintf(r, "%s left us", nick);
        }

        char* my_nick = Get_Resource_Name_By_FullJID(MucClist->conf_jid);
        if (!strcmp(nick,my_nick)) 
        {
          Leave_Conference(Conference->JID);
          CList_MakeAllResourcesOFFLINE(Conference);
        };
        extern const char sndOffline[64];
        
        SUBPROC((void *)Play, sndOffline);
        if(SHOWSTAT_MUCINOUT)
          CList_AddSystemMessage(Conference->JID,6, r);
        priv.role = ROLE_NONE;
        priv.aff  = AFFILIATION_NONE;
        Req_Set_Role = 1;
      }

      
      XMLNode* sstatus = XML_Get_Child_Node_By_Name(x_node,"status");
      if(sstatus)  
      {
        
        char* st_code=XML_Get_Attr_Value("code", sstatus->attr);
        int errcode_n=0;
        extern const char percent_d[];
        sscanf(st_code,percent_d,&errcode_n);
        
        switch (errcode_n)
        {
         case 307:  sprintf(r, "%s was kicked!",nick); break; 
         case 301: sprintf(r, "%s was BANNED! ", nick); break;
         case 322: sprintf(r, "%s was kicked, because room became member-only!", nick); break; 
         case 303: sprintf(r, "%s is now known as %s", nick,  XML_Get_Attr_Value("nick", item->attr)); break; 
         case 201: sprintf(r, "New MUC created. Owner-%s", nick); break; 
         default: sprintf(r,"%s - [unknow action(%s)]",nick, st_code);
        }
        XMLNode* item = XML_Get_Child_Node_By_Name(x_node,"item");
        if(item)
        {
          XMLNode* actor = XML_Get_Child_Node_By_Name(item,loc_actor); 
          if(actor)strcat(r, XML_Get_Attr_Value(loc_jid, actor->attr));

          XMLNode* reason = XML_Get_Child_Node_By_Name(item,loc_reason); 
          if(reason)
          {
            strcat(r, "; Reason: ");
            int l = strlen(r);
            if(512-l-1>0)strncat(r, reason->value, 512-l-1);
          }
        }
        if(DISPLAY_POPUPS)
        {
          char *ansi_r = convUTF8_to_ANSI_STR(r);
          MsgBoxError(1,(int)ansi_r);
          mfree(ansi_r);
        }
        CList_AddSystemMessage(Conference->JID,status, r);
        msg = r;
      }

    }

  TRESOURCE *ResEx = CList_AddResourceWithPresence(from, status, msg, priority);
  if(Req_Set_Role) CList_MUC_SetRole(from, priv);
  if(real_jid)
  {
    ResEx->muc_privs.real_jid = malloc(strlen(real_jid)+1);
    strcpy(ResEx->muc_privs.real_jid, real_jid);
  }
}

MESS_TYPE Get_Message_Type(char* mess_type_str)
{
  char m_chat[]= "chat";
  char m_gchat[]= "groupchat";
  char m_error[]= "error";
  if(!mess_type_str)return MSG_NORMAL;
  if(!strcmp(mess_type_str,m_chat ))return MSG_CHAT;
  if(!strcmp(mess_type_str,m_gchat ))return MSG_GCHAT;
  if(!strcmp(mess_type_str,m_error ))return MSG_STATUS;
  return MSG_NORMAL;
}


void _mucadmincmd(char* room, XMLNode* iq_payload)
{
  char admin_iqid[]="SieJC_adm";
  char iqtypeset[]= "set";
  SendIq(room, iqtypeset, admin_iqid, "http://jabber.org/protocol/muc#admin", iq_payload);
  mfree(room);
}


void MUC_Admin_Command(char* room_name, char* room_jid, MUC_ADMIN cmd, char* reason)
{
  char *_room_name=malloc(strlen(room_name)+1);
  strcpy(_room_name,room_name);
  char it[20];
  char val[20];
  char aff[]="affiliation";
  char role[]="role";
  switch(cmd)
  {
  case ADM_KICK:
    {
      strcpy(it,role);
      strcpy(val,JABBER_ROLS[ROLE_NONE]);
      break;
    }
  case ADM_VOICE_REMOVE:
    {
      strcpy(it,role);
      strcpy(val,JABBER_ROLS[ROLE_VISITOR]);
      break;
    }
  case ADM_VOICE_GRANT:
    {
      strcpy(it,role);
      strcpy(val,JABBER_ROLS[ROLE_PARTICIPANT]);
      break;
    }
  case ADM_PARTICIPANT:
    {
      strcpy(it,aff);
      strcpy(val,JABBER_AFFS[AFFILIATION_NONE]);
      break;
    }
  case ADM_MEMBER:
    {
      strcpy(it,aff);
      strcpy(val,JABBER_AFFS[AFFILIATION_MEMBER]);
      break;
    }
  case ADM_MODERATOR:
    {
      strcpy(it,role);
      strcpy(val,JABBER_ROLS[ROLE_MODERATOR]);
      break;
    }
 case ADM_MODERATOR_REMOVE:
    {
      strcpy(it,role);
      strcpy(val,JABBER_ROLS[ROLE_PARTICIPANT]);
      break;
    }
  case ADM_ADMIN:
    {
      strcpy(it,aff);
      strcpy(val,JABBER_AFFS[AFFILIATION_ADMIN]);
      break;
    }
  case ADM_OWNER:
    {
      strcpy(it,aff);
      strcpy(val,JABBER_AFFS[AFFILIATION_OWNER]);
      break;
    }
  case ADM_BAN:
    {
      strcpy(it,aff);
      strcpy(val,JABBER_AFFS[AFFILIATION_OUTCAST]);
      break;
    }
  }
  
  XMLNode *xml_item, *xml_reason;
  char item_t[]="item";
  char nick_t[]="nick";
  char reason_t[]="reason";

  xml_item = XML_CreateNode(item_t, 0);
  xml_reason = XML_CreateNode(reason_t, reason);
  XML_Set_Attr_Value(xml_item, it, val);
  XML_Set_Attr_Value(xml_item, nick_t, room_jid);
  xml_item->subnode = xml_reason;
  SUBPROC((void*)_mucadmincmd, _room_name, xml_item);
}

static void Report_Delivery(char *mess_id, char *to)
{








 
  XMLNode *received;
  char received_t[]="received";
  char xmlns_t[]="xmlns";  
  received = XML_CreateNode(received_t, 0);
  XML_Set_Attr_Value(received, xmlns_t, "urn:xmpp:receipts");
  Send_Message(to, 0, mess_id, received);
}



 
void Process_Incoming_Message(XMLNode* nodeEx)
{
  char Is_subj=0;
  char from[]="from";
  char c_xmlns[]="xmlns";
  char c_id[]="id";
  extern const int BOLD_NICK_INMUC;
  
  char *chr_from = XML_Get_Attr_Value(from,nodeEx->attr);
    XMLNode* xnode = XML_Get_Child_Node_By_Name(nodeEx,"x");
    if(xnode)
    {
      char *xmlns = XML_Get_Attr_Value(c_xmlns,xnode->attr);
      if(xmlns)
      {
      if(!strcmp(xmlns,"http://jabber.org/protocol/muc#user")) 
      {
       XMLNode *invite =  XML_Get_Child_Node_By_Name(xnode,"invite");
       if(invite)
       {
        MUC_ITEM* muct = CList_FindMUCByJID(chr_from); 
        if(!muct) 
        {
          CList_AddContact(chr_from,chr_from, SUB_BOTH, 0, 129);
        }
       }
      } 

     }
    }

  
   XMLNode *attention =  XML_Get_Child_Node_By_Name(nodeEx,"attention");
   if(attention && USE_ATTENTION)
   {
     char *xmlnsa = XML_Get_Attr_Value(c_xmlns,attention->attr);
     if (xmlnsa)
       if(!strcmp(xmlnsa,"urn:xmpp:attention:0")) 
       {
         
         Vibrate(2);
       }
   } 

    
    if(DELIVERY_EVENTS)
    {
    xnode = XML_Get_Child_Node_By_Name(nodeEx,"request");
    if(xnode)
      {
      char *xmlns = XML_Get_Attr_Value(c_xmlns,xnode->attr);
      if(xmlns)
       {
       if(!strcmp(xmlns,"urn:xmpp:receipts"))
        {
          char *id = XML_Get_Attr_Value(c_id, nodeEx->attr);
          if(id)Report_Delivery(id, chr_from);
        }
       }
      }
    xnode = XML_Get_Child_Node_By_Name(nodeEx,"received");
    if(xnode)
    {
      char *xmlns = XML_Get_Attr_Value(c_xmlns,xnode->attr);
      if(xmlns)
      if(!strcmp(xmlns,"urn:xmpp:receipts"))
      {
        TRESOURCE* Res_ex = CList_IsResourceInList(chr_from);
        if(Res_ex)
        if((Res_ex->entry_type == T_NORMAL)||(Res_ex->entry_type == T_CONF_NODE))
        {
          
          
        }
      }
    }
    }
    
    if(COMPOSING_EVENTS)
    {
    xnode = XML_Get_Child_Node_By_Name(nodeEx,"composing");
    if(xnode)
    {
      char *xmlns = XML_Get_Attr_Value(c_xmlns,xnode->attr);
      if(xmlns)
      if(!strcmp(xmlns,"http://jabber.org/protocol/chatstates"))
      {
        TRESOURCE* Res_ex = CList_IsResourceInList(chr_from);
        if(Res_ex)
        if((Res_ex->entry_type == T_NORMAL)||(Res_ex->entry_type == T_CONF_NODE))
        CList_ChangeComposingStatus(Res_ex, 1);
      }
    }
    xnode = XML_Get_Child_Node_By_Name(nodeEx,"active");
    if(xnode)
    {
      char *xmlns = XML_Get_Attr_Value(c_xmlns,xnode->attr);
      if(xmlns)
      if(!strcmp(xmlns,"http://jabber.org/protocol/chatstates"))
      {
        TRESOURCE* Res_ex = CList_IsResourceInList(chr_from);
        if(Res_ex)
        if((Res_ex->entry_type == T_NORMAL)||(Res_ex->entry_type == T_CONF_NODE))
        CList_ChangeComposingStatus(Res_ex, 0);
      }
    }
    }

  XMLNode* msgnode = XML_Get_Child_Node_By_Name(nodeEx,"body");
  XMLNode* msgsubject = XML_Get_Child_Node_By_Name(nodeEx,"subject");
  XMLNode* msgerror = XML_Get_Child_Node_By_Name(nodeEx,"error");
  if(!msgnode)
  {
    msgnode = msgsubject;
    Is_subj = 1;
  }
  if(msgsubject && !msgerror) 
  {
    MUC_ITEM* TmpMUC = CList_FindMUCByJID(CList_FindContactByJID(chr_from)->JID);
      if(TmpMUC)
      {
       if(TmpMUC->muctema) mfree(TmpMUC->muctema);
       TmpMUC->muctema = malloc(strlen(msgsubject->value)*2+1);
       strcpy(TmpMUC->muctema ,msgsubject->value);
      }
  }
  if(msgerror)
  {
   XMLNode* texterror = XML_Get_Child_Node_By_Name(msgerror,"text");
    if(texterror)
      if(texterror->value)
        if(strlen(texterror->value))
          msgnode = texterror;
  }
  
  if(msgnode)
  if(msgnode->value)
  {
    MESS_TYPE msgtype = Get_Message_Type(XML_Get_Attr_Value("type",nodeEx->attr));

    
    if((msgtype!=MSG_GCHAT)&&(msgtype!=MSG_NICKGCHAT))
    {
      if(DISPLAY_POPUPS)
      {
        char* m = malloc(128+5+strlen(msgnode->value));
        sprintf(m,"%s: %s", chr_from, msgnode->value);
        
        char *ansi_m = m;
        utf82win(ansi_m, ansi_m);
        ShowMSG(1,(int)ansi_m);
        mfree(m);
        
      }
      extern const char sndPM[];
      SUBPROC((void *)Play,sndPM);
    }
      else
        {
          if(BOLD_NICK_INMUC)
          if(msgtype==MSG_GCHAT)
          {
          CLIST* clMuc = CList_FindContactByJID(chr_from);
          if(clMuc)
          {
            MUC_ITEM* TmpMUC = CList_FindMUCByJID(clMuc->JID);
            if (TmpMUC)
            {
              char* my_nick = Get_Resource_Name_By_FullJID(TmpMUC->conf_jid);
              if (strstr(msgnode->value, my_nick))
              {
                if(strcmp(Get_Resource_Name_By_FullJID(chr_from), my_nick)) 
                  msgtype=MSG_NICKGCHAT;
              }
            }
          }
          }
          extern const char sndConf[];
          SUBPROC((void *)Play,sndConf);
        }
    if(Is_subj)
    {
      msgtype = MSG_SUBJECT;
    }
    
    if (!msgerror)
    CList_AddMessage(chr_from, msgtype, msgnode->value);
    else
    {
      char r[512];
      sprintf(r, "Error: %s", msgnode->value);
      CList_AddSystemMessage(chr_from, 7, r);
    }
    extern volatile int vibra_count;
    Vibrate(1);
  }
}



 
unsigned short GetPresenceIndex(char* presence_str)
{
  if(!presence_str)return 0;
  for(int i=0;i<12;i++)
  {
    if(!strcmp(presence_str, PRESENCES[i]))return i;
  }
  return 0;
}



 
unsigned short GetAffRoleIndex(char* str)
{
  if(!str)return 0;
  int i;
  for(i=0;i<5;i++)
  {
    if(!strcmp(str, JABBER_AFFS[i]))return i;
  }
  for(i=0;i<4;i++)
  {
    if(!strcmp(str, JABBER_ROLS[i]))return i;
  }

  return 0;
}



void _sendandfree(char *str)
{
  SendAnswer(str);
  mfree(str);
}

