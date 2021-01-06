#include "..\inc\swilib.h"

//#define cnPath //中文目录

__thumb int Hex2Num(char *hex, char *num, int len) //返回长度
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
#define	TYPE_NORMAL 0
#define	TYPE_REPORT 1

char *GetIncomingPDU(void)
{
	return ((char *)IncommingPDU());
}
__thumb int GetNumFromIncomingPDU(char *num, int *type)
{
	int c;
	int i;
	char *p=GetIncomingPDU(); //直接调用函数获得地址
	if ( *p++ != 0x11 )
		return 0;
	if ( *p++ != 0x11 )
		return 0;
	if(!(*p++))
		return 0;
	c=*p++; //信息中心长度
	p+=c+1;
	if(p[1]==0x91||p[1]==0xA1) //常规短信
	{
		*type=TYPE_NORMAL;
	}
	else
	{
		for(i=1;i<5;i++) //查找下面4字节
		{
			if(p[i]==0x91||p[i]==0xA1)
			{
				*type=TYPE_REPORT;
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

#ifdef NEWSGOLD
#define MAX_RECORDS 5000
#define LEVEL1_RN	(41*41)
#define LEVEL2_RN	(41)
#else
#define MAX_RECORDS 1024
#define LEVEL1_RN	(0x20)
#endif

#define NUMBERS_MAX 5

#ifdef NEWSGOLD
#define LAST_NAME 0x23
#define FIRST_NAME 0x24
#define COMPANY_NAME 0x29
#define POST_NAME 0x6F
#define DISPLAY_NAME 0x60
#else
#define NICKNAME 0x12
#define LAST_NAME 0x23
#define FIRST_NAME 0x24
#define STREET 0x25
#define POSTCODE 0x26
#define CITY 0x27
#define COUNTRY 0x28
#define COMPANY_NAME 0x29
#define PHONE_OFFICE 0x2A
#define PHONE_FAX 0x2B
#define PHONE_MOBILE 0x2C
#define PHONE_NUMBER 0x2D
#define E_MAIL 0x2E
#define URL 0x2F
#define PICTURE 0x33
#define E_MAIL2 0x5D
#define PHONE_FAX2 0x5E
#define WALKY_TALKY_ID 0x6D
#endif

typedef struct
{
	WSHDR *name;
	char num[NUMBERS_MAX][32];
}CNTT;


int FindName(WSHDR *wsrc, char *num_needed)
{
#ifdef cnPath  //中文目录
const char *s_ab_main="0:\\““\x1F\xE7\xB3\xBB\xE7\xBB\x9F””\\apo\\addr\\main";
#ifdef NEWSGOLD
const char *s_ab_entry="0:\\““\x1F\xE7\xB3\xBB\xE7\xBB\x9F””\\apo\\addr\\data\\%02d\\%02d\\%02d";
#else
const char *s_ab_entry="0:\\““\x1F\xE7\xB3\xBB\xE7\xBB\x9F””\\apo\\addr\\%02x\\%02x";
#endif
#else //英文目录
const char *s_ab_main="0:\\System\\apo\\addr\\main"; 
#ifdef NEWSGOLD
const char *s_ab_entry="0:\\System\\apo\\addr\\data\\%02d\\%02d\\%02d";
#else
const char *s_ab_entry="0:\\System\\apo\\addr\\%02x\\%02x";
#endif
#endif
	int fin;
	unsigned int ul;
	char recname[128];

	AB_UNPRES ur;
	void *buffer;

#pragma pack(1)
	struct {
#ifdef NEWSGOLD
		long dummy1;
		short dummy2;
		char bitmap[MAX_RECORDS/8];
#else
		long dummy1;
		char bitmap[MAX_RECORDS/8];
#endif
	} ABmain;
#pragma pack()

	unsigned int rec=0;
	int fsz;
	CNTT contact;
	int isFound=0;
	contact.name=AllocWS(32);
	if ((buffer=malloc(65536)))
	{
		zeromem(&ABmain,sizeof(ABmain));
		if ((fin=fopen(s_ab_main, A_ReadOnly+A_BIN, P_READ, &ul))!=-1)
		{
#ifdef ELKA
			if (fread(fin,&ABmain,sizeof(ABmain),&ul)>=194)
#else
			if (fread(fin,&ABmain,sizeof(ABmain),&ul)==sizeof(ABmain))
#endif
			{
				fclose(fin,&ul);
				do
				{
#ifdef NEWSGOLD
					if (ABmain.bitmap[rec>>3]&(0x80>>(rec&7)))
#else
					if (ABmain.bitmap[rec>>3]&(1<<(rec&7)))
#endif
					{
#ifdef NEWSGOLD
						unsigned int rl1;
						unsigned int rl2;
						unsigned int rl3;
						rl1=rec/LEVEL1_RN;
						rl2=(rec%LEVEL1_RN)/LEVEL2_RN;
						rl3=rec%LEVEL2_RN;
						snprintf(recname, 128, s_ab_entry, rl1, rl2, rl3);
#else
						unsigned int rl1=rec/LEVEL1_RN;
						unsigned int r12=rec%LEVEL1_RN;
						snprintf(recname, 128, s_ab_entry, rl1, r12);
#endif
						if ((fin=fopen(recname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
						{
							zeromem(&ur,sizeof(AB_UNPRES));
							fsz=lseek(fin,0,S_END,&ul,&ul);
							lseek(fin,0,S_SET,&ul,&ul);
							fread(fin,buffer,fsz,&ul);
							fclose(fin,&ul);
#ifdef NEWSGOLD
							UnpackABentry(&ur,((char *)buffer+8),fsz,0x28);
#else
							UnpackABentry(&ur,((char *)buffer+4),fsz-4,0x28);
#endif
							int i=0;
							while(i<ur.number_of_records)
							{
								AB_UNPRES_ITEM *r=ur.record_list+i;
								if (r->no_data!=1)
								{
									switch(GetTypeOfAB_UNPRES_ITEM(r->item_type))
									{
										case 0x05:
											if (r->item_type==LAST_NAME)
											{
												if (r->data)
												{
													wstrcpy(contact.name,(WSHDR *)(r->data));
												}
											}
											break;
										case 0x01:
										{
											PKT_NUM *p=(PKT_NUM*)r->data;
											unsigned int n=r->item_type;
											int j;
											unsigned int c;
#ifdef NEWSGOLD
											if (n!=106) n-=0x62;
											else n=4;
											if (n<5)
#else
											switch(r->item_type)
											{
												case PHONE_NUMBER:
													n=0;    break;
												case PHONE_OFFICE:
													n=1;    break;
												case PHONE_MOBILE:
													n=2;    break;
												case PHONE_FAX:
													n=3;    break;
												case PHONE_FAX2:
													n=4;    break;
												default:
													continue;
											}
#endif
											{
												if (p)
												{
													unsigned int c1;
													int m;
													int k=0;
													char *num0=contact.num[n];
													j=0;
													m=0;
													if (p->format==0x91)
														num0[k++]='+';
													while(j<p->data_size)
													{
														if (m&1) {c1=c>>4; j++;}
														else c1=(c=p->data[j])&0x0F;
														if (c1==0x0F) break;
														if (c1==0xA) c1='*';
														else if (c1==0xB) c1='#';
														else if (c1==0xC) c1='+';
														else if (c1==0xD) c1='?';
														else c1+='0';
														num0[k++]=c1;
														m++;
													}
													num0[k]=0;
                                                                                                        //如果一个电话号码是：13810086123的时候，收到10086的短信就会显示姓名出错。
													if(strstr(num0, num_needed))//有BUG
														isFound=1;
												}
											}
											break;
										}
									}
								}
								i++;
							}
							FreeUnpackABentry(&ur,mfree_adr());
						}
						else
							break;
					}
					if(isFound)
					{
						break;
					}
					rec++;
				}
				while(rec<MAX_RECORDS);
			}
			else
			{
				fclose(fin,&ul);
			}
		}
		  mfree(buffer);
	}
	if(isFound)
		wstrcpy(wsrc, contact.name);
	FreeWS(contact.name);
	return (isFound);
}


void AddTheName(WSHDR *wsrc)
{
	char num[32];
	WSHDR *ws;
	char *new_msg;
	int len;
	int type=TYPE_NORMAL; //默认初始化
	if(!(len=GetNumFromIncomingPDU(num, &type)))
		return;
	if(type==TYPE_NORMAL)
	{
		new_msg="新信息!\n来自:\n";
	}
	else
	{
		new_msg="状态报告!\n来自:\n";
	}
	ws=AllocWS(32);
	if(!FindName(ws, len>11?(num+len-11):num))//如果号码大于11位,直接查找后11位,
		str_2ws(ws, num, len);//没找到,输出号码 
	gb2ws(wsrc, new_msg, strlen(new_msg));//new_msg转换到wsrc
	wstrcat(wsrc, ws);
	FreeWS(ws);
}

void AddTheName_N(WSHDR *wsrc, char *num, int len, char *str)
{
	//将区号秀,对方姓名,及原有字符修改,重排
	WSHDR wsname, *wsn;
	unsigned short usname[32];
	WSHDR wscs, *wsc;
	unsigned short uscs[16];
	int i, j;
	unsigned short *p=wsrc->wsbody+1;
	int wslen=wsrc->wsbody[0];
	wsn=CreateLocalWS(&wsname, usname, 32);
	wsc=CreateLocalWS(&wscs, uscs, 16);
	for(i=0;i<wslen;i++)
	{
		if(p[i]==0xD) //查找0xD换行符,如果有刷区号秀的话
		{
			p+=i;
			while(*p<0x20)
			{
				i++;
				p++;
			}
			for(j=0;j<((wslen-i)<16?(wslen-i):16);j++) //copy 区号秀
				wsc->wsbody[j+1]=p[j];
			wsc->wsbody[0]=j;
			break;
		}
	}
	if(!FindName(wsn, len>11?(num+len-11):num))//如果号码大于11位,直接查找后11位,
		str_2ws(wsn, num, len);//没找到,输出号码 
	gb2ws(wsrc, str, strlen(str));
	wstrcat(wsrc, wsn);
	wsAppendChar(wsrc, '\n');
	wstrcat(wsrc, wsc);
}
