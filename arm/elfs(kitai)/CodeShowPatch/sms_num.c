#include "addr.h"

#ifndef WITHOUT_SMS_IN_WIN
__thumb int Hex2Num(char *hex, char *num, int len)@ "CODE_X" //返回长度
{
	int c;
	int i=0,j=0;
	char *p=hex;
	if(*p==0x91)
	{
		p++;
		len-=2; //按+86算
	}
	p++;
	while(i<len)
	{
		c=p[j]%0x10;
		if(c>=0&&c<=9)
			num[i++]=c+'0';
		else
			break;
		if(i>=len)
			break;
		c=p[j]/0x10;
		if(c>=0&&c<=9)
			num[i++]=c+'0';
		else
			break;
		j++;
	}
	num[i]=0;
	return i;
}

__thumb int GetNumFromIncomingPDU(char *num)@ "CODE_X"
{	
	int c;
	int i;
	char *p=(char *)ADDR_IncommingPDU;
	if ( *p++ != 0x11 )
		return 0;
	if ( *p++ != 0x11 )
		return 0;
	if(!(*p++))
		return 0;
	c=*p++; //信息中心长度
	p+=c+1;
	if(p[1]!=0x91&&p[1]!=0xA1) //常规短信
	{
		for(i=1;i<5;i++) //查找下面4字节
		{
			if(p[i]==0x91||p[i]==0xA1)
			{
				p+=i-1; //走到长度位置
				goto GET_L;
			}
		}
		return 0;//未知情况直接放弃
	}
GET_L:
	c=*p++; //号码长度
	if(c)
	{
		return(Hex2Num(p, num, c));
	}
	return 0;
}
#endif

