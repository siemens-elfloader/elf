
#include "..\inc\swilib.h"

#define TYPE_OUT	0
#define TYPE_IN		1
#define TYPE_UNK	2
#define TYPE_DRAFT	3

#ifdef VKP
#define PROCESSOR_MODE __thumb
#else
#define PROCESSOR_MODE __arm
#endif

typedef struct
{
	int type;
	char SMS_CENTER[32];
	char Number[32];
	char Time[32];
	WSHDR *SMS_TEXT;
}SMS_DATA;

PROCESSOR_MODE void Hex2Num(char *hex, char *num, int len)
{
	int c;
	int i=0,j;
	char *p=hex;
	if(*p==0x91)
	{
		num[i]='+';
		i++;
	}
	p++;
	for (j=0; j<len; j++)
	{
		c=p[j]%0x10;
		if(c>=0&&c<=9)
			num[i]=c+'0';
		else
			break;
		i++;
		c=p[j]/0x10;
		if(c>=0&&c<=9)
			num[i]=c+'0';
		else
			break;
		i++;
	}
	num[i]=0;
}

PROCESSOR_MODE void Add2WS(char *data, char *wsbody, int len)
{
	int i;
	for(i=0; i<len; i+=2)
	{
		wsbody[i+2]=data[i+1];
		wsbody[i+3]=data[i];
	}
	unsigned short *p=(unsigned short *)wsbody;
	*p=len/2;
}

PROCESSOR_MODE void SMS_NotOut(char *PDU_data, SMS_DATA *data, int oftype)
{
	char *p=PDU_data;
	int c=*p++;
	if(c) //len
		Hex2Num(p, data->SMS_CENTER, c);
	p+=c+2;
	c=*p++;
	if(c)
	{
		if(c%2)
			c=c/2+2;
		else
			c=c/2+1;
		Hex2Num(p, data->Number, c);
	}
	p+=c+oftype;
	c=*p++;
	Add2WS(p, (char *)data->SMS_TEXT->wsbody, c);
	data->Time[0]=0;
}

PROCESSOR_MODE void SMS_In(char *PDU_data, SMS_DATA *data)
{
	char *p=PDU_data;
	int c=*p++;
	if(c) //len
		Hex2Num(p, data->SMS_CENTER, c);
	p+=c+1;
	c=*p++;
	if(c)
	{
		if(c%2)
			c=c/2+2;
		else
			c=c/2+1;
		Hex2Num(p, data->Number, c);
	}
	p+=c+2;
	//time
	int i;
	char *pp=data->Time;
	for (i=0; i<6; i++)
	{
		*pp++=p[i]%0x10+'0';
		*pp++=p[i]/0x10+'0';
		if(i<2)
			*pp++='-';
		if(i==2)
			*pp++=' ';
		if(i>2&&i<5)
			*pp++=':';
	}
	*pp=0;
	p+=7;
	c=*p++;
	Add2WS(p, (char *)data->SMS_TEXT->wsbody, c);
}
//0 fail, 1, seccess, 2,unk type
PROCESSOR_MODE int PDU_decode(char *PDU_data, SMS_DATA *data)
{
	int c;
	char *p=PDU_data;
	if ( *p++ != 0x11 )
		return 0;
	if ( *p++ != 0x11 )
		return 0;
	c=*p++;
	switch(c)
	{
		case 0x5:
			data->type=TYPE_OUT;
			SMS_NotOut(p, data, 2);
			return 1;
		case 0x3: //未查看
		case 0x1:
			data->type=TYPE_IN;
			SMS_In(p, data);
			return 1;
		case 0x7:
			data->type=TYPE_DRAFT;
			SMS_NotOut(p, data, 3);
			return 1;
	}
	data->type=TYPE_UNK;
	return 2;
}

void GetSMSData(WSHDR *the_ws)
{
	SMS_DATA data;
	zeromem(&data, sizeof(SMS_DATA));
	WSHDR *xws=AllocWS(256);
	data.SMS_TEXT=xws;
	int i=PDU_decode((char *)IncommingPDU(), &data);
	if(i==0)
	{
		wsprintf(the_ws, "Read PDU error!");
	}
	else if(i==1)
	{
		char out[]="发送到:\n";
		char in[]="来自:\n";
		char type_out[]="类型: 去短信";
		char type_in[]="类型: 来短信";
		char type_draft[]="类型: 草稿";
		char *p_io;
		char oth[128];
		if(data.type==TYPE_OUT)
		{
			p_io=type_out;
			strcpy(oth, out);
			strcat(oth, data.Number);
		}
		else if(data.type==TYPE_IN)
		{
			p_io=type_in;
			strcpy(oth, in);
			strcat(oth, data.Number);
			strcat(oth, "\n时间:\n");
			strcat(oth, data.Time);
		}
		else
		{
			p_io=type_draft;
			strcpy(oth, out);
			strcat(oth, data.Number);
		}
		
		//wsprintf(the_ws, "%t\n%t\n%s\n%t\n%t", p_io, "信息中心:", data.SMS_CENTER, oth, "内容:\n");
		wsprintf(the_ws, "%t\n%t\n%t", p_io, oth, "内容:\n");
		wstrcat(the_ws, data.SMS_TEXT);
	}
	else
		wsprintf(the_ws, "Unknow Type!");
	FreeWS(xws);
}

