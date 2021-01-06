



typedef unsigned int size_t;
typedef unsigned long time_t;
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



#pragma swi_number=0x0035
__swi __arm void AlarmClockRing();



#pragma swi_number=42
__swi __arm int *GetEELiteBlockAddress(short blocknum);



#pragma swi_number=60
__swi __arm int setfilesize(int FileHandler, unsigned int iNewFileSize, unsigned int *ErrorNumber);



#pragma swi_number=0x0042
__swi __arm int IsScreenSaver(void);





#pragma swi_number=67
__swi __arm int IsUnlocked(void);



#pragma swi_number=0x45
__swi __arm int GetWavLen(char *filename); 

#pragma swi_number=0x0046
__swi __arm int HasNewSMS(void);



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
__swi __arm void* GetFunctionPointer(char * _shortcut);

#pragma swi_number=124
__swi __arm unsigned int SetVibration(unsigned int power);



#pragma swi_number=128
__swi __arm int ShowCallList(int list, int zero);



#pragma swi_number=132
__swi __arm int GetFileStats(const char *cFileName, FSTATS * StatBuffer, unsigned int *errornumber);



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

#pragma swi_number=0x80DF
__swi __arm char *RamPressedKey();

#pragma swi_number=0x80E0
__swi __arm void * RamScreenBuffer();

#pragma swi_number=0x80E1
__swi	__arm	 unsigned int *RamMPlayer_CtrlCode();



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
__swi int isnewSGold(void);


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
__swi __arm void *DATA_N_SFB(void);





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





#pragma swi_number=0x1EF
__swi __arm void SetDynIcon(int picture,IMGHDR *img,char *bitmap);





#pragma swi_number=0x1F3
__swi __arm unsigned int GetSessionAge(void);



#pragma swi_number=0x1F5
__swi __arm int sscanf(const char *, const char *, ...);



#pragma swi_number=0x1F6
__swi __arm IMGHDR* GetPitAdrBy0xE200Symbol(int uni_symbol);





#pragma swi_number=0x81FB
__swi __arm char *RamMediaIsPlaying();



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












typedef struct
{
  int type;
  char name[32];
  unsigned int min;
  unsigned int max;
}CFG_HDR;

typedef struct
{
  char cbox_text[32];
}CFG_CBOX_ITEM;







 

typedef struct
{
  void *next;
  int acked;
  unsigned long ID;
  int type;
  char hdr[80]; 
  char text[];
}LOGQ;

typedef struct
{
  void *next;
  void *prev;
  unsigned int isgroup;
  unsigned int uin;
  unsigned int group;
  char name[64];
  unsigned short state;
  unsigned short xstate;

  int bot_msg;

  int just_now;
  int change;
  int isunread;
  int unread_msg;
  int req_add;
  int req_drawack;
  LOGQ *log;
  char *answer;
  LOGQ *last_log;
  int isactive;
  int msg_count;
  char *xtext;
  int req_xtext;
}CLIST;

typedef struct
{
  unsigned long uin;
  unsigned short type;
  unsigned short data_len;
}PKT;

typedef struct
{
  PKT pkt;
  char data[16384];
}TPKT;


enum ISTATUS {IS_OFFLINE,IS_INVISIBLE,IS_AWAY,IS_NA,IS_OCCUPIED,IS_DND,IS_DEPRESSION,IS_EVIL,IS_HOME,IS_LUNCH,
IS_WORK,IS_ONLINE,IS_FFC,IS_MSG,IS_UNKNOWN,IS_GROUP,IS_GROUPOFF,IS_NULLICON,

ICON_ADDCONTACT,
ICON_HEAD,
ICON_LOGO,
ICON_PING,
ICON_SETTINGS,

ICON_ALL_CAN_SEE,
ICON_VISLIST_CAN_SEE,
ICON_INVISLIST_CANNOT_SEE,
ICON_CONTACTLIST_CAN_SEE,
ICON_NOBODY_CAN_SEE,

TOTAL_ICONS,

IS_ANY=0xFFFFFFFF,IS_FILTER_T9KEY=0xFFFFFFFE};























 




void SendAnswer(int dummy, TPKT *p);
void CreateEditChat(CLIST *t);
void set_my_status(void);
void set_my_xstatus(void);
void set_my_xstatus2(void);

void RequestXText(unsigned int uin);

void ReadDefSettings(void);
void WriteDefSettings(void);
extern int connect_state;

int GetIconIndex(CLIST *t);


void FreeLOGQ(LOGQ **pp);


typedef struct
{
  CLIST *ed_contact;
  GUI *ed_chatgui;
  int ed_answer;
  int requested_decrement_total_unread;
  int loaded_templates;
}EDCHAT_STRUCT;

#pragma pack(push)
#pragma pack(1)
typedef struct{
  unsigned char
  vibra_status:1,
  sound_status:1,
  off_contacts:1,
  show_groups:1;
  char def_status;
  char def_xstatus;
  unsigned char sli_state:1;
  unsigned char smartcpu_state:1;
  unsigned char inc_state:1;
  unsigned char ilu_state:1;
  unsigned char remind_state:1;
  unsigned char ping_state:1;
  unsigned char uptime_state:1;
  unsigned char Id3tag_status:1;
}DEF_SETTINGS;
#pragma pack(pop)

extern unsigned long  strtoul (const char *nptr,char **endptr,int base);





















typedef struct
{
  void *next;
  char *pngname;
  IMGHDR * img;
}PNGLIST;

typedef struct
{
  void *next;
  int icon;
  IMGHDR * img;
}DYNPNGICONLIST;

typedef struct
{
  PNGLIST * pltop;
  char *bitmap;
  DYNPNGICONLIST *dyn_pltop;
}PNGTOP_DESC;  





void Add2History(CLIST *CListEx, char *header, char *message, int direction);
void LogStatusChange(CLIST *CListEx);
int GetHistory(CLIST *t, int bufsize);



void ShowMainMenu();





 


void InitConfig();

extern const char *successed_config_filename;
int SaveConfigData(const char *fname);



void DispStatusChangeMenu();


void DispXStatusChangeMenu(void);


void LoadXStatusText(void);
void SaveXStatusText(void);
void FreeXStatusText(void);
char *GetXStatusStr(int n, int *len);















































int CreateManageCLMenu(void);
int CreateAddContactGrpDialog(CLIST *cl_sel);
int CreatePrivateStatusMenu(void);
void SetPrivateStatus(int status);


#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

#pragma inline
void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=(24);
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+(24)-1;
}
#pragma inline
void patch_input(const INPUTDIA_DESC* inp)
{
  ((INPUTDIA_DESC*)inp)->rc.x=0;
  ((INPUTDIA_DESC*)inp)->rc.y=HeaderH()+1+(24);
  ((INPUTDIA_DESC*)inp)->rc.x2=ScreenW()-1;
  ((INPUTDIA_DESC*)inp)->rc.y2=ScreenH()-SoftkeyH()-1;
}



void FreeXText(CLIST *t);
void FreeCLIST(void);
void FillAllOffline(void);

CLIST *FindContactByUin(unsigned int uin);
CLIST *FindGroupByID(unsigned int grp);

CLIST *FindContactByNS(int *i, int si, int act_flag, CLIST *search_contact);
int CountContacts(void);
CLIST *FindContactByN(int i);
int FindContactByContact(CLIST *p);
void SwapContacts(CLIST *first, CLIST *second);
void ChangeContactPos(CLIST *p);
int CompareContacts(CLIST *t, CLIST *p);

void ResortCL(void);
CLIST *AddContactOrGroup(CLIST **top, CLIST *p);
CLIST *AddContact(unsigned int uin, char *name);
CLIST *AddGroup(unsigned int grp, char *name);



int MainMenu_ID;

extern int CurrentStatus;
extern int CurrentXStatus;
extern DYNPNGICONLIST *XStatusesImgList;
extern int *XStatusesIconArray;
extern  int S_ICONS[];
extern const SOFTKEYSTAB menu_skt;
extern int Is_INC_On;
extern int Is_SLI_On;
extern int Is_SMARTCPU_On;
extern int Is_ILU_On;
extern int Is_Double_Vibra_On;
int janis;
extern int Is_PING_On;
extern int Is_UPTIME_On;
extern int Is_Vibra_Enabled;
extern int Is_Id3tag_Enabled;
extern unsigned int Is_Sounds_Enabled; 
extern int Is_Show_Offline;
extern int Is_Show_Groups;


static void ChangeVibraMode(void)
{
  Is_Vibra_Enabled=!(Is_Vibra_Enabled);
  SUBPROC((void*)WriteDefSettings);
  RefreshGUI();
}
static void ChangeId3tagMode(void)
{
  Is_Id3tag_Enabled=!(Is_Id3tag_Enabled);
  SUBPROC((void*)WriteDefSettings);
  RefreshGUI();
  set_my_xstatus();
}

extern int automsg;
extern int msg_away_timer;
extern GBSTMR away_tmr;
extern void away_timer();
extern int main_d;
extern int away_m;
extern const unsigned int AUTO_ENGADE;

static void AutoAwayMSG(void)
{
 if(!automsg)
  {
   automsg=!automsg;
   GBS_StopTimer(&away_tmr);
   msg_away_timer=AUTO_ENGADE;
   away_timer();
   main_d=1;
  }
 else
  {
   msg_away_timer=0;
   away_m=0;
   automsg=!automsg;
  }
 RefreshGUI();
}

extern void AutobotInit();
extern int autobot;

static void ChangeSoundMode(void)
{
  Is_Sounds_Enabled=!(Is_Sounds_Enabled);
  SUBPROC((void*)WriteDefSettings);
  RefreshGUI();
}

static void ChangeShowOfflineMode(void)
{
  void RecountMenu(CLIST *req);
  Is_Show_Offline=!(Is_Show_Offline);
  SUBPROC((void*)WriteDefSettings);
  RecountMenu(0);
  RefreshGUI();
}

static void ChangeShowGroupsMode(void)
{
  void RecountMenu(CLIST *req);
  Is_Show_Groups=!(Is_Show_Groups);
  SUBPROC((void*)WriteDefSettings);
  ResortCL();
  RecountMenu(0);
  RefreshGUI();
}

static void EditConfig(void)
{
  extern const char *successed_config_filename;
  WSHDR *ws;
  ws=AllocWS(150);
  str_2ws(ws,successed_config_filename,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
  GeneralFuncF1(1);
}

static void Disconnect(void)
{
  extern volatile int disautorecconect;
  disautorecconect=1;
  extern void end_socket(void);
  SUBPROC((void*)end_socket);
  GeneralFuncF1(1);
}

extern int uins;
char hmm1[64];

static void PingToServer(void)
{
  janis=1;
  TPKT *p;
  p=malloc(sizeof(PKT)+sizeof(TTime));
  GetDateTime(0,(TTime *)p->data);
  p->pkt.uin=0;
  p->pkt.type=18;
  p->pkt.data_len=sizeof(TTime);
  SUBPROC((void *)SendAnswer,0,p);
}

static void AboutDlg()
{
  char s[256];
  snprintf(s,255,"NATICQ v2.0\nRevision %d\n(C) by Rst7/CBSIE\nKren\nKibab\nShadow\nSeklth",1845);
  ShowMSG(2, (int)s);
}

static const HEADER_DESC menuhdr={0,0,0,0,0,(int)"Меню",0x7FFFFFFF};

static const int mmenusoftkeys[]={0,1,2};
static const char * const menutexts[22]=
{
  "Статус",
  "X-Статус",
  "Управление списком",
  "Режим Id3tag",
  "Автоответчик",
  "Режим вибры",
  "Режим звука",
  "Popup sender",
  "Режим SLI", 
  "Main msg. mode",
  "Режим Vibra rem.",
  "Режим Ilum.",
  "Auto Ping",
  "Online time",
  "Офф. контакты",
  "Группы",
  "Настройки",
  "Оборвать связь",
  "MSG Info",
  "Пинг",
  "Об эльфе",
  "Автобот"
};










 
static void ChangeSLIMode(void)
{
  Is_SLI_On=!(Is_SLI_On);
  SUBPROC((void*)WriteDefSettings);
  RefreshGUI();
}
static void ChangeSMARTCPUMode(void)
{
  Is_SMARTCPU_On=!(Is_SMARTCPU_On);
  SUBPROC((void*)WriteDefSettings);
  RefreshGUI();
}
static void ChangeINCMode(void)
{
  Is_INC_On=!(Is_INC_On);
  SUBPROC((void*)WriteDefSettings);
  RefreshGUI();
}
static void ChangeILUMode(void)
{
  Is_ILU_On=!(Is_ILU_On);
  SUBPROC((void*)WriteDefSettings);
  RefreshGUI();
}

static void ChangePINGMode(void)
{
  Is_PING_On=!(Is_PING_On);
  SUBPROC((void*)WriteDefSettings);
  RefreshGUI();
}

static void ChangeUPTIMEMode(void)
{
  Is_UPTIME_On=!(Is_UPTIME_On);
  SUBPROC((void*)WriteDefSettings);
  RefreshGUI();
}

int main_count;
int main2_count;

static void MSG_Info(void)
{
  char *info=malloc(64);
  sprintf(info, "sent: %d\n"
          "recv: %d", main2_count, main_count);
  ShowMSG(1,(int)info);
  mfree(info);
}

static void ChangeDoubleVibra(void)
{
  Is_Double_Vibra_On=!(Is_Double_Vibra_On);
  SUBPROC((void*)WriteDefSettings);
  RefreshGUI();
}

static const void *menuprocs[22]=
{
  (void *)DispStatusChangeMenu,
  (void *)DispXStatusChangeMenu,
  (void *)CreateManageCLMenu,
  (void *)ChangeId3tagMode,
  (void *)AutoAwayMSG,
  (void *)ChangeVibraMode,
  (void *)ChangeSoundMode,
  (void *)ChangeINCMode,
  (void *)ChangeSLIMode,
  (void *)ChangeSMARTCPUMode,
  (void *)ChangeDoubleVibra,
  (void *)ChangeILUMode,
  (void *)ChangePINGMode,
  (void *)ChangeUPTIMEMode,
  (void *)ChangeShowOfflineMode,
  (void *)ChangeShowGroupsMode,
  (void *)EditConfig,
  (void *)Disconnect, 
  (void *)MSG_Info,
  (void *)PingToServer,
  (void *)AboutDlg,
  (void *)AutobotInit,
};

static const SOFTKEY_DESC mmenu_sk[]=
{
  {0x0018,0x0000,(int)"Выбор"},
  {0x0001,0x0000,(int)"Назад"},
  {0x003D,0x0000,(int)0x7FFFC0FB}
};

static const SOFTKEYSTAB mmenu_skt=
{
  mmenu_sk,0
};

void tmenu_ghook(void *data, int cmd)
{
  PNGTOP_DESC *pltop=PNG_TOP();
  if (cmd==9)
  {
    pltop->dyn_pltop=0;
  }
  if (cmd==0x0A)
  {
    pltop->dyn_pltop=XStatusesImgList;
    DisableIDLETMR();
  }
}

static int icon_array[2];

static void menuitemhandler(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  extern const char percent_t[];
  ws=AllocMenuWS(data,strlen(menutexts[curitem]));
  wsprintf(ws,percent_t,menutexts[curitem]);
  switch(curitem)
  {
  case 0:
    SetMenuItemIconArray(data,item,S_ICONS+CurrentStatus);
    break;
  case 1:
    SetMenuItemIconArray(data,item,XStatusesIconArray+CurrentXStatus);
    break;
  case 2:
    SetMenuItemIconArray(data,item,S_ICONS+ICON_ADDCONTACT);
    break;
  case 3:
    SetMenuItemIconArray(data,item,icon_array+(Is_Id3tag_Enabled?0:1));
    break;
  case 4:
    SetMenuItemIconArray(data,item,icon_array+(away_m?0:1));
    break;
  case 5:
    SetMenuItemIconArray(data,item,icon_array+(Is_Vibra_Enabled?0:1));
    break;
  case 6:
    SetMenuItemIconArray(data,item,icon_array+(Is_Sounds_Enabled?0:1));
    break;
  case 7:
    SetMenuItemIconArray(data,item,icon_array+(Is_INC_On?0:1));
    break;  
  case 8:
    SetMenuItemIconArray(data,item,icon_array+(Is_SLI_On?0:1));
    break;
  case 9:
    SetMenuItemIconArray(data,item,icon_array+(Is_SMARTCPU_On?0:1));
    break;
  case 10:
    SetMenuItemIconArray(data,item,icon_array+(Is_Double_Vibra_On?0:1));
    break;
  case 11:
    SetMenuItemIconArray(data,item,icon_array+(Is_ILU_On?0:1));
    break;
  case 12:
    SetMenuItemIconArray(data,item,icon_array+(Is_PING_On?0:1));
    break;
  case 13:
    SetMenuItemIconArray(data,item,icon_array+(Is_UPTIME_On?0:1));
    break;  
  case 14:
    SetMenuItemIconArray(data,item,icon_array+(Is_Show_Offline?0:1));
    break;
  case 15:
    SetMenuItemIconArray(data,item,icon_array+(Is_Show_Groups?0:1));
    break;    
  case 16:
    SetMenuItemIconArray(data,item,S_ICONS+ICON_SETTINGS);
    break;
  case 17:
    SetMenuItemIconArray(data,item,S_ICONS+IS_OFFLINE);
    break;
  case 18:
    SetMenuItemIconArray(data,item,S_ICONS+IS_UNKNOWN);
    break;  
  case 19:
    SetMenuItemIconArray(data,item,S_ICONS+ICON_PING);
    break;
  case 20:
    SetMenuItemIconArray(data,item,S_ICONS+IS_UNKNOWN);
    break;
  case 21:
    SetMenuItemIconArray(data,item,icon_array+(autobot?0:1));
    break;
  }
  SetMenuItemText(data, item, ws, curitem);
}

static int tmenu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocs[GetCurMenuItem(data)]))();
  }
  return(0);
}


static const MENU_DESC tmenu=
{
  8,tmenu_keyhook,tmenu_ghook,0,
  mmenusoftkeys,
  &mmenu_skt,
  0x11,
  menuitemhandler,
  0,
  0,
  21
};

void ShowMainMenu()
{
  icon_array[0]=GetPicNByUnicodeSymbol(0xE116);
  icon_array[1]=GetPicNByUnicodeSymbol(0xE117);
  *((int **)(&menuhdr.icon))=S_ICONS+IS_ONLINE;
  patch_header(&menuhdr);
  MainMenu_ID=CreateMenu(0,0,&tmenu,&menuhdr,0,22,0,0);
}
