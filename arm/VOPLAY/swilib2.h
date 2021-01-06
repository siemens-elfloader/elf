typedef  unsigned char byte;
typedef  unsigned short word;
typedef  unsigned int dword;

#define PTT_BUTTON 0x27



#pragma swi_number=0x80D6
__swi __arm unsigned int* RamNetOnline();

#ifdef NEWSGOLD
#pragma swi_number=0x1FF
__swi __arm void MEDIA_PLAYLAST();


#pragma swi_number=0x22C
__swi __arm int pdcache_getval(char* ret, int maxlen_of_return_str, char cachetype, char *pd_entry_identifier_class, char  *pd_entry_identifier_sub);
/*
#pragma swi_number=0x22D
__swi __arm int pdcache_setval(char *new_value, char cachetype,  char *pd_entry_identifier_class, char *pd_entry_identifier_sub);
*/
#endif


