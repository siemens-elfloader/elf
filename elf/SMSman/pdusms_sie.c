
SMS_DATA *SMSD=NULL;


char *_in, *_out, *_draft;

struct{
	char all,d,in,out,df,inf,outf;
}scnt;
    
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

PROCESSOR_MODE void Add2WS(char *data, char *wsbody, int len, char type)
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

// 00		Склеенные короткие сообщения, 8-битная ссылка
// 01		Индикатор специального СМС
// 02		зарезервирован
// 03		Не используется
// 04		8 битовый адрес
// 05		16 битовый адрес
// 06		Параметры для контроля SMSC
// 07		Индикатор источника UDH
// 08		Склеенные короткие сообщения, 16-битная ссылка
// 09		Wireless Control Message Protocol
// 0A		Форматированный текст
// 0B		Предопределенная мелодия
// 0C		Пользовательская мелодия в формате iMelody, максимальная длина 128 байт.
// 0D		Предопределенная мультипликация
// 0E		Большая мультипликация (16*16 раз 4 = 32*4 =128 байтов)
// 0F		Маленькая мультипликация (8*8 раз 4 = 8*4 =32 байта)
// 10		Большой рисунок (32*32 = 128 байтов)
// 11		Маленький рисунок (16*16 = 32 байта)
// 12		Рисунок любого размера
// 13		User prompt indicator
// 14		Extended Object
// 15		Reused Extended Object
// 16		Контроль cжатия
// 17		Object Distribution Indicator
// 18-1F	зарезервировано
// 20		RFC 822 заголовок для E-Mail
// 21		HTTP ссылка
// 22-6F	зарезервировано
// 70-7F	Заголовок программ безопасности (U)SIM
// 80-9F	SME to SME specific use
// A0-BF	зарезервировано
// C0-DF	SC specific use
// E0-FF	зарезервировано


void DoEMS(char *P_data, SMS_DATA *data)
{
// 	char skip=*P_data;
// 	if((skip<5)||(skip>10)) return 0;
	P_data++;
	char t=*P_data;
// 	if(t==0xa) return 1;
// 	if((t==0x2)||(t==0x3)||(t>=0x18&&t<=0x1F)||(t>=0x22&&t<=0x6F)|| (t>=0xA0&&t<=0xBF)||(t>=0xE0&&t<=0xFF)) return 0; // not ems
	switch(t)
	{
	 case 0:
		 P_data+=2;
		 data->sig=*P_data++;
		 data->cnt=*P_data++;
		 data->n=*P_data++;
	   break;
	 case 8:
		 P_data+=2;
		 data->sig=P_data[0]*0x100+P_data[1];
		 P_data+=2;
		 data->cnt=*P_data++;
		 data->n=*P_data++;
	   break;
// 	default:
// 		 return 0; 
	}
// 	return 1;
}

PROCESSOR_MODE void SMS_NotOut(PDU *PDU_data, SMS_DATA *data)//, int oftype)
{
	char *p=(char*)PDU_data;
	char isems, isplus;
	p+=3;
	int c=*p++;
	if(c) //len
		Hex2Num(p, data->SMS_CENTER, c);
	p+=c;
	if((*p>>4)%2) isplus=1;
	else isplus=0;
	if((*p>>6)%2) isems=1;
	else isems=0;
	p+=2;
	c=*p++;
	if(c)
	{
		if(c%2)
		{
			c=c/2+2;
			Hex2Num(p, data->Number, c);
		}
		else
		{
			Hex2Num(p, data->Number, c/2);
			c=c/2+1;
		}
	}
	else p++;
	p+=c+2;//oftype;
// 	p+=oftype;
	c=*p++;
	char ttype=*(p-2);//oftype);
	/*if(c>0xA0)*/if(isplus) c=*p++;
	char skip=*p;
	
	data->cnt=1;
	data->n=1;
	if(isems)
	{
		DoEMS(p,data);
		if(ttype==8)
		{
			p+=skip+1;
			c-=skip+1;
		}
// 		else c-=(skip+1)*8/7+1;
	}
	
	if(ttype==8) Add2WS(p, (char *)data->SMS_TEXT->wsbody, c, ttype);
	else
	{
		GSMTXT_Decode(data->SMS_TEXT,(void*)p,c*7/8+1,ttype, (void*(*)(int))malloc_adr(),(void(*)(void))mfree_adr());
		if(isems)
		{
			c-=(skip+1)*8/7+1;
			unsigned short *tb=malloc(wstrlen(data->SMS_TEXT)*2+2);
			zeromem(tb,wstrlen(data->SMS_TEXT)*2+2);
			tb[0]=c;
			memcpy(tb+1, data->SMS_TEXT->wsbody+(skip+1)*8/7+2, c*2);
			mfree(data->SMS_TEXT->wsbody);
			data->SMS_TEXT->wsbody=tb;
		}
		else
		{
			if(wstrlen(data->SMS_TEXT)>c)
			{
				data->SMS_TEXT->wsbody[0]=c;
				data->SMS_TEXT->wsbody[c+1]=0;
			}
		}
	}
	data->Time[0]=0;
}

PROCESSOR_MODE void SMS_In(PDU *PDU_data, SMS_DATA *data)
{
	char *p=(char*)PDU_data;
	char isems;
	p+=3;
	int c=*p++;
	if(c) //len
		Hex2Num(p, data->SMS_CENTER, c);
	p+=c;
	if((*p>>6)%2) isems=1;
	else isems=0;
	p++;
	c=*p++;
	if(c)
	{
		if(c%2)
		{
			c=c/2+2;
			Hex2Num(p, data->Number, c);
		}
		else
		{
			Hex2Num(p, data->Number, c/2);
			c=c/2+1;
		}
	}
	else p++;
	p+=c+1;
	char ttype=*p;
	p++;
	//time
	int i;
	char *pp=data->Time;
// 	data->tm=0;
	for (i=0; i<6; i++)
	{
		data->tm[i]=p[i]%0x10*10+p[i]/0x10;
		*pp++=p[i]%0x10+'0';
		*pp++=p[i]/0x10+'0';
		if(i<2)
			*pp++='.';
		if(i==2)
			*pp++=' ';
		if(i>2&&i<5)
			*pp++=':';
	}
	char tmp=data->Time[0];
	data->Time[0]=data->Time[6];
	data->Time[6]=tmp;
	tmp=data->Time[1];
	data->Time[1]=data->Time[7];
	data->Time[7]=tmp;
	*pp=0;
	p+=7;
	c=*p++;
	char skip=*p;
	
	data->cnt=1;
	data->n=1;
	if(isems)
	{
		DoEMS(p,data);
		if(ttype==8)
		{
			p+=skip+1;
			c-=skip+1;
		}
// 		else c-=(skip+1)*8/7+1;
	}
	
	if(ttype==8) Add2WS(p, (char *)data->SMS_TEXT->wsbody, c, ttype);
	else
	{
		GSMTXT_Decode(data->SMS_TEXT,(void*)p,c*7/8+1,ttype,(void*(*)(int))malloc_adr(),(void(*)(void))mfree_adr());
		if(isems)
		{
			c-=(skip+1)*8/7+1;
			unsigned short *tb=malloc(wstrlen(data->SMS_TEXT)*2+2);
			zeromem(tb,wstrlen(data->SMS_TEXT)*2+2);
			tb[0]=c;
			memcpy(tb+1, data->SMS_TEXT->wsbody+(skip+1)*8/7+2, c*2);
			mfree(data->SMS_TEXT->wsbody);
			data->SMS_TEXT->wsbody=tb;
		}
		else
		{
			if(wstrlen(data->SMS_TEXT)>c)
			{
				data->SMS_TEXT->wsbody[0]=c;
				data->SMS_TEXT->wsbody[c+1]=0;
			}
		}
	}
}

//0 fail, 1, seccess, 2,unk type
PROCESSOR_MODE int PDU_decode(PDU *PDU_data, SMS_DATA *data)
{
	int c;
	char *p=(char*)PDU_data;
	if ( *p++ != 0x11 )
		return 0;
	if ( *p++ != 0x11 )
		return 0;
	c=*p++;
	switch(c)
	{
		case 0x5: // output
			data->type=TYPE_OUT;
			SMS_NotOut(PDU_data, data);//, 0);
			return 1;
		case 0x3: //input
		case 0x1:
			data->type=TYPE_IN;
			SMS_In(PDU_data, data);
			return 1;
		case 0x7:
			data->type=TYPE_DRAFT;
			SMS_NotOut(PDU_data, data);//, 1);
			return 1;
		default:
			return 0;
	}
// 	data->type=TYPE_UNK;
// 	return 2;
}

void GetSMSData(SMS_DATA *data, PDU *sms)
{
	zeromem(data, sizeof(SMS_DATA));
	WSHDR *xws=AllocWS(256);
	data->SMS_TEXT=xws;
	int i=PDU_decode(sms, data);
	if(i!=1)
	{
		FreeWS(xws);
		data->SMS_TEXT=NULL;
	}
}

