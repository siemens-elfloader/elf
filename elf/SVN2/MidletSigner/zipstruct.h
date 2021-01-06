/*Header file generated for C code*/
#ifndef ZIPSTRUCT_H
#define ZIPSTRUCT_H


#define ui32 unsigned int
#define ui16 unsigned short


typedef struct
{
	ui32 signature;
	ui16 version_made_by;
	ui16 version_needed;
	ui16 bitflags;
	ui16 comp_method;
	ui16 lastModFileTime;
	ui16 lastModFileDate;
	ui32 crc_32;
	ui32 comp_size;
	ui32 uncompr_size;
	ui16 fname_len;
	ui16 extra_field_len;
	ui16 fcomment_len;
        ui16 disk_num_start;
	ui16 internal_fattribute;
	ui32 external_fattribute;
	//ui32 relative_offset;
        char relative_offset[4];
	char* file_name;
	char* extra_field;
	char* file_comment;
}FileHeader;

#pragma pack(1)
typedef struct
{
  ui32 signature;  //(0x08074b50)
  ui32 crc32;
  ui32 compr_size;
  ui32 uncompr_size;
}DATA_DESC;
#pragma pack()

#pragma pack(1)
typedef struct
{
	ui16 header_id;
        ui16 data_size;
        //char* data
}EXTRA_FIELD;
#pragma pack()

#pragma pack(1)
typedef struct
{
	ui32 local_signature;  //(0x04034b50)
        ui16 version_to_extract;
        ui16 bit_flag;
        ui16 compr_method;
        ui16 last_mod_file_time;
        ui16 last_mod_file_date;
        ui32 crc32;
	ui32 compr_size;
	ui32 uncompr_size;
	ui16 fname_len;
	ui16 extra_field_len;
	//char* file_name;
}LOCAL_ZIP;
#pragma pack()


#pragma pack(1)
typedef struct
{
  ui32 central_signature;  //0x02014b50
  ui16 version_made_by;
  ui16 version_to_extract;
  ui16 general_purpose_bit_flag;
  ui16 compression_method;
  ui16 last_mod_file_time;
  ui16 last_mod_file_date;
  ui32 crc32;
  ui32 compr_size;
  ui32 uncompr_size;
  ui16 fname_len;
  ui16 extra_field_len;
  ui16 file_comment_length;
  ui16 disk_number_start;
  ui16 internal_file_attributes;
  ui32 external_file_attributes;
  ui32 relative_offset;
}CENTRAL_ZIP;
#pragma pack()  

#endif /*ZIPSTRUCT_H */
