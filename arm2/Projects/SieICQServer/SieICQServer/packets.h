#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>


#pragma pack(push, 1)
typedef struct TLV
{
   unsigned short int Type;
   unsigned short int Lenght;
   char*value;
}TLV;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct FLAP

{
unsigned char       Sign,ChID;
unsigned short int  SEQ,Len;
}FLAP;
#pragma pack(1)

#pragma pack(push, 1)
typedef struct FLAP_PACKET
{
FLAP flap;
TLV uin;
TLV pass;
TLV version;
}FLAP_PACKET;
#pragma pack(1)

char *XORPassword(char *dest);
