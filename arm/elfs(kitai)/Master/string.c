/*
 * �ļ���: getConfig.c
 * ����: BingK(binghelingxi)
 *
 * ����޸�����: 2008.07.07
 *
 * ����: �ṩһЩ�ַ�������
 * ��ע: WINTEL_DEBUGΪʹ����windows��ʹ�ñ��������е��Ե�����������Ŀ
 *
 */

#ifdef	WINTEL_DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#else
#include "..\inc\swilib.h"
#endif
#include "usedstr.h"
#include "string.h"
#include "main.h"

#ifndef	WINTEL_DEBUG
int getnumwidth(unsigned int num)
{
	int i=1;
	while(num>=10) 
	{
		num/=10;
		i++;
	}
	return i;  
}

void uni2ws(WSHDR *ws, unsigned short *uni, int maxlen)
{
	unsigned short *p=uni;
	ws->wsbody[0]=0;
	int i=1;
	while(*p && (maxlen==0||p-uni<=maxlen))
	{
		ws->wsbody[i]=*p;
		i++;
		p++;
	}
	ws->wsbody[0]=i-1;
}

void ws2uni(WSHDR *ws, unsigned short *uni, int maxlen)
{
	unsigned short *p=ws->wsbody+1;
	int i=0;
	while(i<ws->wsbody[0]&&(maxlen==0||i<maxlen))
	{
		uni[i]=p[i];
		i++;
	}
	for(;i<maxlen;i++)
		uni[i]=0;
}

void hex2ws(WSHDR *ws, unsigned char *hex, int maxlen)
{
	unsigned char *p=hex;
	ws->wsbody[0]=0;
	WSHDR *tws=AllocWS(8);
	while(p-hex<maxlen)
	{
		wsprintf(tws, PERCENT_02X, *p);
		wstrcat(ws, tws);
		p++;
	}
	FreeWS(tws);
}

/*
int str2hex(char *str, char *hex)
{
	char c, c1;
	int i=0;
	char *p1=str;
	while((c=*p1++))
	{
		if((c>='0'&&c<='9')||(c>='a'&&c<='f')||(c>='A'&&c<='F'))
		{
			c1=*p1++;
			if((c1>='0'&&c1<='9')||(c1>='a'&&c1<='f')||(c1>='A'&&c1<='F'))
				hex[i++]=chr2num(c)*0x10+chr2num(c1);
			else
				break;
		}
		else
			break;
	}
	i=i/2;
	i=i*2;
	hex[i]=0;
	hex[i+1]=0;
	return i;
}
*/
#pragma inline
unsigned short str2short(char *s)
{
	return (((chr2num(s[0]))<<4)+(chr2num(s[1]))+((chr2num(s[2]))<<12)+((chr2num(s[3]))<<8));
}

void uniFormatString2ws(WSHDR *ws, char *s)
{
	int wslen;
	if(!(wslen=isUniFormat(s)/4))
		wsprintf(ws, PERCENT_T, s);
	else
	{
		int i=0;
		unsigned short *p=ws->wsbody+1;
		ws->wsbody[0]=wslen;
		for(;i<wslen;i++)
		{
			p[i]=str2short(s+i*4);
		}
	}
}

int isUniFormat(char *s)
{
	char c;
	int i=0;
	while(c=s[i])
	{
		if((c>='0'&&c<='9')||(c>='A'&&c<='F'))
			i++;
		else
			return 0;
	}
	if(i%4)
		return 0;
	return i;
}

void ws2hex(WSHDR *ws, char *hex, int maxlen)
{
	char s[MAX_WS_LEN];
	int i=0;
	unsigned char c, c1;
	char *p1=s;
	ws_2str(ws, s, maxlen);
	while((c=*p1++))
	{
		if((c>='0'&&c<='9')||(c>='a'&&c<='f')||(c>='A'&&c<='F'))
		{
			c1=*p1++;
			if((c1>='0'&&c1<='9')||(c1>='a'&&c1<='f')||(c1>='A'&&c1<='F'))
				hex[i++]=chr2num(c)*0x10+chr2num(c1);
			else
				hex[i++]=chr2num(c);
		}
		else
			break;
	}
	for(;i<(maxlen/2);i++)
	{
		hex[i]=0;
	}
}

void bytes_2ws(WSHDR *ws, char *bytes, int maxlen)
{
	WSHDR *tws;
	int i=1;
	//int t=bytes[0];
	if(maxlen<=0)
		return;
	tws=AllocWS(8);
	ws->wsbody[0]=0;
	wsprintf(ws,PERCENT_D,bytes[0]);
	for(;i<maxlen;i++)
	{
		//t=bytes[i];
		wsprintf(tws, D_PERCENT_D, bytes[i]);
		wstrcat(ws, tws);
	}
	FreeWS(tws);
}

void ints_2ws(WSHDR *ws, int *ints, int maxlen)
{
	WSHDR *tws;
	int i=1;
	//int t=bytes[0];
	if(maxlen<=0)
		return;
	tws=AllocWS(16);
	ws->wsbody[0]=0;
	wsprintf(ws,PERCENT_D,ints[0]);
	for(;i<maxlen;i++)
	{
		//t=bytes[i];
		wsprintf(tws, D_PERCENT_D, ints[i]);
		wstrcat(ws, tws);
	}
	FreeWS(tws);
}

#endif

#ifndef	WINTEL_DEBUG
#pragma inline=forced
#endif
int toupper(int c)
{
	if ((c>='a')&&(c<='z')) c+='A'-'a';
	return(c);
}

//�Ƚ��ַ����ִ�Сд����
int strncmpNoCase(const char *s1,const char *s2,unsigned int n)
{
	int i;
	int c;
	while(!(i=(c=toupper(*s1++))-toupper(*s2++))&&(--n)) if (!c) break;
	return(i);
}

//�ַ�ת��Ϊ����
int chr2num(char chr)
{
	if(chr>='0'&&chr<='9')
		return (chr-('0'-0));
	if(chr>='A'&&chr<='Z')
		return (chr-('A'-0xA));
	if(chr>='a'&&chr<='z')
		return (chr-('a'-0xA));
	return 0;
}

//ָ���ߵ��ո���λ��
char *gotoRealPos(char *p)
{
	char *pp=p;
	while(*pp)
	{
		if(*pp>X_CHAR)
			break;
		pp++;
	}
	return pp;
}

//�������������ַ���������ֵָ���������ַ�β��
char *strstrInQuote(char *pdata, const char *s)
{
	int len=strlen(s);
	while( *pdata && *pdata!='}' )
	{
		if(!strncmpNoCase(pdata, s, len))
			return (pdata+len);
		pdata++;
	}
	return 0;
}

//�������������ַ�
char *strchrInQuote(char *pdata, char c)
{
	while( *pdata && *pdata!='}' )
	{
		if(*pdata==c)
			return pdata;
		pdata++;
	}
	return 0;
}

//�ߵ����ſ�ͷ
char *gotoQuoteStart(char *pdata)
{
	while(*pdata)
	{
		if(*pdata=='{')
			return pdata;
		pdata++;
	}
	return 0;
}

//�ߵ����Ž�β
char *gotoQuoteEnd(char *pdata)
{
	while(*pdata)
	{
		if(*pdata=='}')
			return pdata;
		pdata++;
	}
	return 0;
}

//�����õ��ַ���Ϊʹ��"`"����������ʱ��������������ߵ���һ��"`"����
char *gotoNextNameQuote(char *pdata)
{
	char *p=pdata;
	while(*pdata)
	{
		if(*pdata=='`')
		{
			p=pdata;
			break;
		}
		pdata++;
	}
	return p;
}

//ָ���ߵ��ƶ����ַ�λ��
char *gotoStringEndByChr(char *p, char chr)
{
	char *pp=p;
	while(*p)
	{
		if(*p==chr || *p=='}' || *p<0xA)
		{
			pp=p;
			break;
		}
		p++;
	}
	return pp;
}

//���������ߵ�"`"֮ǰ��һ��λ�û�ȿո����ַ���
char *gotoMyStrStart(char *p)
{
	p=gotoRealPos(p);
	if(*p=='`')
		return (p+1);
	if(*p==0 || *p=='}')
		return 0;
	return p;
}

//���������ߵ���һ��"`"��ո񼰱ȿո�С���ַ���
char *gotoMyStrEnd(char *p)
{
	if(*p=='`')
	{
		p++;
		return (gotoNextNameQuote(p));
	}
	else
	{
		p=gotoRealPos(p);
		return (gotoStringEndByChr(p, X_CHAR));
	}
}

//strncpy�����ں�������ַ�����ֹ��
void strnCopyWithEnd(char *dst, char *src, int n)
{
	strncpy(dst, src, n);
	dst[n]=0;
}

//�ַ���ת��Ϊ���֣�int��
void str2num(char *str, int *num, int max, int min, int type)
{
	//type, 1:hex, 0:dec
	int t1=0;
	int t=0;
	int isNa=0;
	if(*str=='-')
	{
		isNa=1;
		str++;
	}
	if((*str=='0'&&*(str+1)=='x')) //hex
	{
		str+=2;
		while((*str>='0')&&(*str<='z'))
		{
			t=(t)*0x10+chr2num(*str);
			if(max<=0||t<=max)
				t1=t;
			else
			{
				t1=max;
				break;
			}
			str++;
		}
	}
	else if((*str=='A')||(*str=='a')||type) //ADDRESS
	{
		while((*str>='0')&&(*str<='z'))
		{
			t=(t)*0x10+chr2num(*str);
			if(max<=0||t<=max)
				t1=t;
			else
			{
				t1=max;
				break;
			}
			str++;
		}
	}
	else //dec
	{
		while((*str>='0')&&(*str<='9'))
		{
			t=(t)*10+chr2num(*str);
			if(max<=0||t<=max)
				t1=t;
			else
			{
				t1=max;
				break;
			}
			str++;
		}
	}
	if(min>(1<<31)) //��СֵС��0
	{
		int c=(~min)+1; //ȡ����ֵ
		if(t1>c&&isNa)
			t1=c;
	}
	else //����0
	{
		if(/*min&&*/(t1<min||isNa))
		{
			t1=min;
			isNa=0;
		}
	}
	if(isNa)
		*num=(~t1)+1;
	else
		*num=t1;
}

//short��
void str2num_short(char *str, short *num, int max, int min, int type)
{
	//type, 1:hex, 0:dec
	int t1=0;
	int t=0;
	short *p=(short *)(&t1);
	if((*str=='0'&&*(str+1)=='x')) //hex
	{
		str+=2;
		while((*str>='0')&&(*str<='z'))
		{
			t=(t)*0x10+chr2num(*str);
			if(max<=0||t<=max)
				t1=t;
			else
			{
				t1=max;
				break;
			}
			str++;
		}
	}
	else if(type) //hex
	{
		while((*str>='0')&&(*str<='z'))
		{
			t=(t)*0x10+chr2num(*str);
			if(max<=0||t<=max)
				t1=t;
			else
			{
				t1=max;
				break;
			}
			str++;
		}
	}
	else //dec
	{
		while((*str>='0')&&(*str<='9'))
		{
			t=(t)*10+chr2num(*str);
			if(max<=0||t<=max)
				t1=t;
			else
			{
				t1=max;
				break;
			}
			str++;
		}
	}
	if(t1>=0&&t1<min)
		t1=min;
	*num=*p;
}

//char��
void str2num_char(char *str, char *num, int max, int min, int type)
{
	//type, 1:hex, 0:dec
	int t1=0;
	int t=0;
	char *p=(char *)(&t1);
	int isNa=0;
	if(*str=='-')
	{
		isNa=1;
		str++;
	}
	if((*str=='0'&&*(str+1)=='x')) //hex with 0x
	{
		str+=2;
		while((*str>='0')&&(*str<='z'))
		{
			t=(t)*0x10+chr2num(*str);
			if(max<=0||t<=max)
				t1=t;
			else
			{
				t1=max;
				break;
			}
			str++;
		}
	}
	else if(type) //hex
	{
		while((*str>='0')&&(*str<='z'))
		{
			t=(t)*0x10+chr2num(*str);
			if(max<=0||t<=max)
				t1=t;
			else
			{
				t1=max;
				break;
			}
			str++;
		}
	}
	else //dec
	{
		while((*str>='0')&&(*str<='9'))
		{
			t=(t)*10+chr2num(*str);
			if(max<=0||t<=max)
				t1=t;
			else
			{
				t1=max;
				break;
			}
			str++;
		}
	}
	if(min>128)//����
	{
		min=256-min; //����ֵ
		if(t1>min&&isNa)
			t1=min;
	}
	else
	{
		if(/*min&&*/(t1<min||isNa))
		{
			t1=min;
			isNa=0;
		}
	}
	if(isNa)
		*num=(~(*p))+1;
	else
		*num=*p;
}

//���һ���ַ����е�ĳ���ַ�
void cleanStrByChr(char *pdata, char chr)
{
	char *p=pdata;
	char *t;
	while(*p)
	{
		if(*p==chr)
		{
			t=p;
			while(*t)
			{
				*t=*(t+1);
				t++;
			}
		}
		p++;
	}
}

void str2bytes(char *bytes, char *str, int maxlen)
{
	int i=0;
	while(i<maxlen)
	{
		str=gotoRealPos(str);
		str2num_char(str, bytes+i, 127, 0, 0);
		if(!(str=strchrInQuote(str+1, ',')))
			break;
		if(!(*str++)) //IAR�������ڴ���while((*str)&&(i<maxlen))��һ��ʱ������,ָ��ǰ����һ��
			break;
		i++;
	}
}

void str2ints(int *ints, char *str, int maxlen)
{
	int i=0;
	while(i<maxlen)
	{
		str=gotoRealPos(str);
		str2num(str, ints+i, 0, 0, 0);
		if(!(str=strchrInQuote(str+1, ',')))
			break;
		if(!(*str++)) //IAR�������ڴ���while((*str)&&(i<maxlen))��һ��ʱ������,ָ��ǰ����һ��
			break;
		i++;
	}
}

