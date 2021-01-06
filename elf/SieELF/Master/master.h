#ifndef _MASTER_H_
#define _MASTER_H_

typedef struct
{
	char patchName[128];
	char patchID[16];
	char version[8];
	char author[32];
	char *info;
}PATCH_INFO;

typedef struct
{
	void *prev;
	void *next;
	char itemName[128];
	char data;
}PREPARE_ITEM;

typedef struct
{
	char useAs[32];
	PREPARE_ITEM *prepareItem;
}PREPARE_DATA;

typedef struct
{
	char str[128];
}DATA_DRSTR;

typedef struct
{
	int bitPos;
	char onoff;
}DATA_CHECKBOX;

typedef struct
{
	short x;
	char off;
	short y;
	short w;
	short h;
}DATA_POS;

//xy2 1 x, 2 onoff,on->00, off->80 3,4 y
//xy 1,x ,2,y, off,ffff, on use default, sw/2, sh/2

typedef struct
{
	char min;
	char max;
	char initData;
}DATA_BYTE;

typedef struct
{
	int min;
	int max;
	int initData;
}DATA_INT;


typedef struct
{
	void *prev;
	void *next;
	char name[128];
	char data;
}CBOX_ITEM;

typedef struct
{
	char initData;
	CBOX_ITEM *cboxitem;
}DATA_CBOX;

typedef struct
{
	char color[4];
}DATA_COLOR;

typedef struct
{
	unsigned int addr;
}DATA_ADDRESS;

typedef struct
{
	char string[128];
	int maxlen;
}DATA_STRING;//if 0, use default 0x10

typedef struct
{
	unsigned short ustr[128]; //max 128
	int maxlen; //if 0, use default 0x10
}DATA_UNICODE;


typedef struct
{
	unsigned char hex[128];
	int maxlen;//if 0, use default 0x1
}DATA_HEX;

typedef struct
{
	char path[128];
	char mask[32];
	int maxlen;//if 0, use default 58
}DATA_SF;

typedef struct
{
	char path[128];
	int maxlen;
}DATA_SD;

typedef struct
{
	char min;
	char max;
	char initData;
}DATA_SL;

typedef struct
{
	unsigned int ms;
}DATA_MS;

typedef struct
{
	char min;
	char max;
	int len;
	char bytes[128];
}DATA_BYTES;

typedef struct
{
	int min;
	int max;
	int len;
	int ints[128];
}DATA_INTS;

typedef struct
{
	int data;
	int len;
}DATA_CONST;

typedef struct
{
	void *prev;
	void *next;
	int bytePos;
	char itemName[128];
	int itemType;
	void *itemData;
}PATCH_ITEM;

typedef struct
{
	char smName[128];
	PATCH_ITEM *item;
}PATCH_SUBMENU;

typedef struct
{
	char useAs[128];
	PATCH_ITEM *item;
}PATCH_TP;

typedef struct
{
	void *prev;
	void *next;
	unsigned char patchonoff;
	int needSaveData;
	int disableProfile;
	int memory;
	int offset;
	PATCH_INFO *patchInfo;
	PATCH_SUBMENU mainitem; //理解为一个submenu
}PTC_CONFIG;

#define TYPE_PRE	0 //choice //data prepare for option/cbox
#define TYPE_DRSTR	1 //direct sring
#define TYPE_CHECKBOX	2 //checkbox
#define TYPE_POS	3 //XY postion
#define TYPE_BYTE	4 //data byte
#define TYPE_INT	5 //data int
#define TYPE_CBOX	6 //CBOX/option
#define TYPE_COLOR	7 //color
#define TYPE_ADDRESS	8 //address
#define TYPE_STRING	9 //String
#define TYPE_UNICODE	10 //unicode
#define TYPE_SUBMENU	11 //submenu
#define TYPE_HEX	12 //hex
#define TYPE_SF		13 //select file
#define TYPE_SD		14 //selectdir
#define TYPE_MS		15 //timeinms
#define TYPE_BYTES	16 //bytes
#define TYPE_SL		17 //slider
#define TYPE_INTS	18 //ints
#define TYPE_TP		19 //template
#define TYPE_POSB	20 //pos in byte //use it the same as pos, except when save
#define TYPE_CONST	21 //const
#endif
