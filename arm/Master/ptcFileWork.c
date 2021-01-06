/*
 * 文件名: ptcFileWork.c
 * 作者: BingK(binghelingxi)
 *
 * 最后修改日期: 2008.08.05
 *
 * 作用: 读取*.ptc进行初始化和写入*.ptc
 * 备注: WINTEL_DEBUG为使用在windows中使用编译器进行调试的条件编译项目
 *
 */

#ifdef	WINTEL_DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#else
#include "..\inc\swilib.h"
#include "optionMenu.h"
#endif
#include "getConfig.h"
#include "ptcFileWork.h"
#include "string.h"
#include "main.h"

#define X_CHAR		0x20

#ifdef	WINTEL_DEBUG
#define PATCH_DIR	"E:\\SRC\\SVN\\SieELF\\Master\\Patches\\"
#define PTC_FOLDR	"ptc1\\"
#define PTC_SIZE	(2*1024)
char ptc_buf[PTC_SIZE];
#define mfree free
#endif

#define _percent_08s	"%08s"

int ptcfilesize=0;


//逐个条目进行初始化
void initPatchItem(PATCH_ITEM *ptcitem)
{
	int bpos;
	PATCH_ITEM *pitem=ptcitem;
	while(pitem)
	{
		bpos=pitem->bytePos;
		if(!pitem->itemData)
			goto NEXT_ITEM;
		if(pitem->itemType==TYPE_SUBMENU)
		{
			PATCH_SUBMENU *sitem=(PATCH_SUBMENU *)pitem->itemData;
			initPatchItem(sitem->item);
		}
		if(!bpos)
			goto NEXT_ITEM;
		switch(pitem->itemType)
		{
		case TYPE_CHECKBOX:
			{
				DATA_CHECKBOX *chkbox=(DATA_CHECKBOX *)pitem->itemData;
				chkbox->onoff=ptc_buf[bpos];
				chkbox->onoff=(chkbox->onoff)<<(7-(chkbox->bitPos));
				chkbox->onoff=(chkbox->onoff)>>7;
				chkbox->onoff=(chkbox->onoff)&1;
				break;
			}
		case TYPE_POS:
			{
				DATA_POS *pos=(DATA_POS *)pitem->itemData;
				short *sp=(short *)(ptc_buf+bpos);
				pos->x=ptc_buf[bpos];
				if(ptc_buf[bpos+1]==0x80)
					pos->off=1;
			//	pos->x=*sp;
				pos->y=*(sp+1);
				break;
			}
		case TYPE_BYTE:
			{
				DATA_BYTE *dbyte=(DATA_BYTE *)pitem->itemData;
				dbyte->initData=ptc_buf[bpos];
				break;
			}
		case TYPE_INT:
			{
				DATA_INT *dint=(DATA_INT *)pitem->itemData;
				//读取INT型数据指针的是LDR指令，似乎只能是使用4字节对齐的地址，改用char型处理
				char *p=(ptc_buf+bpos);
				char *p1=(char *)(&dint->initData);
				int i=0;
				for(;i<4;i++)
					p1[i]=p[i];
				break;
			}
		case TYPE_CBOX:
			{
				DATA_CBOX *cbox=(DATA_CBOX *)pitem->itemData;
				cbox->initData=ptc_buf[bpos];
				break;
			}
		case TYPE_COLOR:
			{
				DATA_COLOR *color=(DATA_COLOR *)pitem->itemData;
				char *p=(ptc_buf+bpos);
				int i=0;
				for(;i<4;i++)
					color->color[i]=p[i];
				break;
			}
		case TYPE_ADDRESS:
			{
				DATA_ADDRESS *addr=(DATA_ADDRESS *)pitem->itemData;
				//读取INT型数据指针的是LDR指令，似乎只能是使用4字节对齐的地址，改用char型处理
				char *p=(ptc_buf+bpos);
				char *p1=(char *)(&addr->addr);
				int i=0;
				for(;i<4;i++)
					p1[i]=p[i];
				break;
			}
		case TYPE_STRING:
			{
				DATA_STRING *str=(DATA_STRING *)pitem->itemData;
				if(str->maxlen)
					memcpy(str->string, (ptc_buf+bpos), str->maxlen);
				else
					memcpy(str->string, (ptc_buf+bpos), sizeof(char)*0x10);
				break;
			}
		case TYPE_UNICODE:
			{
				DATA_UNICODE *uni=(DATA_UNICODE *)pitem->itemData;
				if(uni->maxlen)
					memcpy(uni->ustr, (ptc_buf+bpos), sizeof(short)*uni->maxlen);
				else
					memcpy(uni->ustr, (ptc_buf+bpos), sizeof(short)*0x10);
				break;
			}
		case TYPE_HEX:
			{
				DATA_HEX *hex=(DATA_HEX *)pitem->itemData;
				memcpy(hex->hex, (ptc_buf+bpos), (hex->maxlen?hex->maxlen:1));
				//if(hex->maxlen)
				//	memcpy(hex->hex, (ptc_buf+bpos), hex->maxlen);
				//else
				//	memcpy(hex->hex, (ptc_buf+bpos), 0x1);
				break;
			}
		case TYPE_SF:
			{
				DATA_SF *fs=(DATA_SF *)pitem->itemData;
				memcpy(fs->path, (ptc_buf+bpos), fs->maxlen?fs->maxlen:58);
				break;
			}
		case TYPE_SD:
			{
				DATA_SD *sd=(DATA_SD *)pitem->itemData;
				memcpy(sd->path, (ptc_buf+bpos), sd->maxlen?sd->maxlen:58);
				break;
			}
		case TYPE_SL:
			{
				DATA_SL *sl=(DATA_SL *)pitem->itemData;
				sl->initData=ptc_buf[bpos];
				break;
			}
		case TYPE_MS:
			{
				DATA_MS *ms=(DATA_MS *)pitem->itemData;
				//读取INT型数据指针的是LDR指令，似乎只能是使用4字节对齐的地址，改用char型处理
				char *p=(ptc_buf+bpos);
				char *p1=(char *)(&ms->ms);
				int i=0;
				for(;i<4;i++)
					p1[i]=p[i];
				break;
			}
		case TYPE_POSB:
			{
				DATA_POS *pos=(DATA_POS *)pitem->itemData;
				if(ptc_buf[bpos]==0xFF&&ptc_buf[bpos+1]==0xFF)
				{
					pos->off=1;
					pos->x=66;
					pos->y=88;
				}
				else
				{
					pos->x=ptc_buf[bpos];
					pos->y=ptc_buf[bpos+1];
				}
				break;
			}
		case TYPE_BYTES:
			{
				DATA_BYTES *dbytes=(DATA_BYTES *)pitem->itemData;
				memcpy(dbytes->bytes, ptc_buf+bpos, dbytes->len);
				break;
			}
		case TYPE_INTS:
			{
				DATA_INTS *dints=(DATA_INTS *)pitem->itemData;
				memcpy(dints->ints, ptc_buf+bpos, (dints->len)*sizeof(int));
				break;
			}
		case TYPE_CONST:
			{
				DATA_CONST *dconst=(DATA_CONST *)pitem->itemData;
				//读取INT型数据指针的是LDR指令，似乎只能是使用4字节对齐的地址，改用char型处理
				char *p=(ptc_buf+bpos);
				char *p1=(char *)(&dconst->data);
				int i=0;
				for(;i<(dconst->len);i++)
					p1[i]=p[i];
				break;
			}
		}
	NEXT_ITEM:
		pitem=pitem->next;
	}
}

//从*.ptc读取数据，初始化配置
void initPatchConfig(PTC_CONFIG *ptcfg)
{
	char ptcpath[128];
	char ptcid[16];
#ifdef WINTEL_DEBUG
	FILE *fp;
	strcpy(ptcpath, PATCH_DIR);
	strcat(ptcpath, PTC_FOLDR);
	sprintf(ptcid, "%08s", ptcfg->patchInfo->patchID);
	strcat(ptcpath, ptcid);
	strcat(ptcpath, ".ptc");
	fp=fopen(ptcpath, "rb");
	if(!fp)
		return;
	ptcfilesize=fread(ptc_buf, 1, PTC_SIZE, fp);
	fclose(fp);
#else
	int f;
	unsigned int ferr;
	strcpy(ptcpath, PATCH_DIR);
	strcat(ptcpath, PTC_FOLDR);
	sprintf(ptcid, _percent_08s, ptcfg->patchInfo->patchID);
	strcat(ptcpath, ptcid);
	strcat(ptcpath, ".ptc");
	f=fopen(ptcpath, A_BIN+A_ReadOnly, P_READ, &ferr);
	if(f==-1)
		return;
	ptcfilesize=fread(f, ptc_buf, PTC_SIZE, &ferr);
	fclose(f, &ferr);
#endif
	if(ptcfilesize<0)
		return;
	//ptc_buf[ptcfilesize]=0;
	ptcfg->patchonoff=ptc_buf[0];
	initPatchItem(ptcfg->mainitem.item);
}

//找到最近字节位置的条目
PATCH_ITEM *findNextBposItem(PATCH_ITEM *ptcitem, int bpos)
{
	PATCH_ITEM *pitem=ptcitem;
	PATCH_ITEM *titem=0;
	PATCH_ITEM *item2=0;
	int t=0;
	int t1=0;
	while(pitem)
	{
		if(pitem->itemType==TYPE_SUBMENU)
		{
			PATCH_SUBMENU *submenu=(PATCH_SUBMENU *)pitem->itemData;
			if(submenu&&(item2=findNextBposItem(submenu->item, bpos)))
			{
				if(titem)
				{
					if(titem->bytePos>item2->bytePos)
						titem=item2;
				}
				else
					titem=item2;
			}
			if(titem)
				t=t1=titem->bytePos;
			pitem=pitem->next;
			continue;
		}
		else
			t1=pitem->bytePos;
		if(t1>bpos) //先找到一个大于bpos的值，然后找最近的；
		{
			if(!t)
			{
				t=pitem->bytePos;
				titem=pitem;
			}
			else if(t1>bpos&&t1<t)
			{
				t=t1;
				titem=pitem;
			}
		}
		pitem=pitem->next;
	}
	return titem;
}

//在同一个字节上，找到下一个位的条目，用于CheckBox
PATCH_ITEM *getTheSameBPosCheckBox(PATCH_ITEM *ptcitem, int bpos, int bitpos, int type)
{
	//type 1:the same, 0,larger
	PATCH_ITEM *pitem=ptcitem;
	PATCH_ITEM *titem=0;
	while(pitem)
	{
		if(pitem->itemType==TYPE_SUBMENU)
		{
			PATCH_SUBMENU *submenu=(PATCH_SUBMENU *)pitem->itemData;
			if(submenu)
			{
				titem=getTheSameBPosCheckBox(submenu->item, bpos, bitpos, type);
				if(titem)
					return titem;
			}

		}
		if((pitem->bytePos==bpos)&&(pitem->itemType==TYPE_CHECKBOX))
		{
			DATA_CHECKBOX *chk=(DATA_CHECKBOX *)pitem->itemData;
			if(type)
			{
				if(chk->bitPos==bitpos)
					return pitem;
			}
			if(chk->bitPos>bitpos)
			{
				if(!titem)
					titem=pitem;
				else
				{
					DATA_CHECKBOX *chk1=(DATA_CHECKBOX *)titem->itemData;
					//DATA_CHECKBOX *chk=(DATA_CHECKBOX *)titem->itemData;
					if(chk1->bitPos>chk->bitPos)
						titem=pitem;
				}
			}
		}
		pitem=pitem->next;
	}
	return titem;
}

//将数据填充到ptc_buf中，为重新写入ptc做准备
void fillItemDataToBuf(PATCH_ITEM *ptcitem)
{
	PATCH_ITEM *pitem;
	int bpos=0;
	if(!ptcitem)
		return;
	while((pitem=findNextBposItem(ptcitem, bpos)))
	{
		bpos=pitem->bytePos;
		switch(pitem->itemType)
		{
		case TYPE_CHECKBOX:
			{
				//int c=ptc_buf[bpos];
				int bitPos;
				PATCH_ITEM *item_2;
				item_2=getTheSameBPosCheckBox(ptcitem, bpos, 0, 1);
				do{
					DATA_CHECKBOX *chkbox=(DATA_CHECKBOX *)item_2->itemData;
					char c=chkbox->onoff;
					bitPos=chkbox->bitPos;
					if(c)
					{
						c=1<<bitPos;
						ptc_buf[bpos]=ptc_buf[bpos]|c;
					}
					else
					{
						c=~(1<<bitPos);
						ptc_buf[bpos]=ptc_buf[bpos]&c;
					}
				}while(item_2=getTheSameBPosCheckBox(ptcitem, bpos, bitPos, 0));
				break;
			}
		case TYPE_SUBMENU:
			{
				PATCH_SUBMENU *sitem=(PATCH_SUBMENU *)pitem->itemData;
				fillItemDataToBuf(sitem->item);
				break;
			}
		case TYPE_POS:
			{
				DATA_POS *pos=(DATA_POS *)pitem->itemData;
				short *sp=(short *)(ptc_buf+bpos);
				unsigned char *xp=(unsigned char *)(ptc_buf+bpos+1);
				char *px=(char *)&pos->x;
				ptc_buf[bpos]=*px;
				if(pos->off)
					*xp=0x80;
				*(sp+1)=pos->y;
				break;
			}
		case TYPE_BYTE:
			{
				DATA_BYTE *dbyte=(DATA_BYTE *)pitem->itemData;
				ptc_buf[bpos]=dbyte->initData;
				break;
			}
		case TYPE_INT:
			{
				DATA_INT *dint=(DATA_INT *)pitem->itemData;
				char *p=ptc_buf+bpos;
				char *p1=(char *)&dint->initData;
				int i=0;
				for(;i<4;i++)
					p[i]=p1[i];
				break;
			}
		case TYPE_CBOX:
			{
				DATA_CBOX *cbox=(DATA_CBOX *)pitem->itemData;
				ptc_buf[bpos]=cbox->initData;
				break;
			}
		case TYPE_COLOR:
			{
				DATA_COLOR *color=(DATA_COLOR *)pitem->itemData;
				char *p=ptc_buf+bpos;
				char *p1=color->color;
				int i=0;
				for(;i<4;i++)
					p[i]=p1[i];
				break;
			}
		case TYPE_ADDRESS:
			{
				DATA_ADDRESS *addr=(DATA_ADDRESS *)pitem->itemData;
				char *p=ptc_buf+bpos;
				char *p1=(char *)&addr->addr;
				int i=0;
				for(;i<4;i++)
					p[i]=p1[i];
				break;
			}
		case TYPE_STRING:
			{
				DATA_STRING *str=(DATA_STRING *)pitem->itemData;
				char *p=ptc_buf+bpos;
				char *p1=str->string;
				strcpy(p, p1);
				break;
			}
		case TYPE_UNICODE:
			{
				DATA_UNICODE *uni=(DATA_UNICODE *)pitem->itemData;
				unsigned short *p=(unsigned short *)(ptc_buf+bpos);
				unsigned short *p1=uni->ustr;
				int i=0;
				int n;
				if(!uni->maxlen)
					n=0x10;
				else
					n=uni->maxlen;
				for(;i<n;i++)
					p[i]=p1[i];
				break;
			}
		case TYPE_HEX:
			{
				DATA_HEX *hex=(DATA_HEX *)pitem->itemData;
				char *p=ptc_buf+bpos;
				char *p1=(char *)hex->hex;
				int i=0;
				int n=(hex->maxlen?hex->maxlen:1);
				//if(!hex->maxlen)
				//	n=0x1;
				//else
				//	n=hex->maxlen;
				for(;i<n;i++)
					p[i]=p1[i];
				break;
			}
		case TYPE_SF:
			{
				DATA_SF *fs=(DATA_SF *)pitem->itemData;
				char *p=ptc_buf+bpos;
				char *p1=fs->path;
				strcpy(p, p1);
				break;
			}
		case TYPE_SD:
			{
				DATA_SD *sd=(DATA_SD *)pitem->itemData;
				char *p=ptc_buf+bpos;
				char *p1=sd->path;
				strcpy(p, p1);
				break;
			}
		case TYPE_SL:
			{
				DATA_SL *sl=(DATA_SL *)pitem->itemData;
				ptc_buf[bpos]=sl->initData;
				break;
			}
		case TYPE_MS:
			{
				DATA_MS *ms=(DATA_MS *)pitem->itemData;
				char *p=ptc_buf+bpos;
				char *p1=(char *)&ms->ms;
				int i=0;
				for(;i<4;i++)
					p[i]=p1[i];
				break;
			}
		case TYPE_POSB:
			{
				DATA_POS *pos=(DATA_POS *)pitem->itemData;
				unsigned char *sp=(unsigned char *)ptc_buf+bpos;
				char *px=(char *)&pos->x;
				char *py=(char *)&pos->y;
				//*sp=*px;
				//*(sp+1)=*py;
				if(pos->off)
				{
					*sp=0xFF;
					*(sp+1)=0xFF;
				}
				else
				{
					ptc_buf[bpos]=*px;
					ptc_buf[bpos+1]=*py;
				}
				break;
			}
		case TYPE_BYTES:
			{
				DATA_BYTES *dbytes=(DATA_BYTES *)pitem->itemData;
				memcpy(ptc_buf+bpos, dbytes->bytes, dbytes->len);
				break;
			}
		case TYPE_INTS:
			{
				DATA_INTS *dints=(DATA_INTS *)pitem->itemData;
				memcpy(ptc_buf+bpos, dints->ints, (dints->len)*sizeof(int));
				break;
			}
		case TYPE_CONST:
			{
				DATA_CONST *dconst=(DATA_CONST *)pitem->itemData;
				char *p=ptc_buf+bpos;
				char *p1=(char *)&dconst->data;
				int i=0;
				for(;i<(dconst->len);i++)
					p[i]=p1[i];
				break;
			}
		}
	}
}

//获取要写入的PTC的大小
int getPtcSize(PATCH_ITEM *ptcitem)
{
	PATCH_ITEM *pitem;
	PATCH_ITEM *item=0;
	int bpos=0;
	int ptcsize=1;
	if(!ptcitem)
		return 1;
	while((pitem=findNextBposItem(ptcitem, bpos)))
	{
		bpos=pitem->bytePos;
		item=pitem;
	}
	if(!item)
		return 1;
	ptcsize=item->bytePos;
	switch(item->itemType)
	{
		case TYPE_CHECKBOX:
		case TYPE_BYTE:
		case TYPE_SL:
		case TYPE_CBOX:
			{
				ptcsize++;
				break;
			}
		case TYPE_SUBMENU:
			{
				PATCH_SUBMENU *sitem=(PATCH_SUBMENU *)item->itemData;
				getPtcSize(sitem->item);
				break;
			}
		case TYPE_POS:
		case TYPE_INT:
		case TYPE_MS:
		case TYPE_COLOR:
		case TYPE_ADDRESS:
			{
				ptcsize+=4;
				break;
			}
		case TYPE_POSB:
			{
				ptcsize+=2;
				break;
			}
		case TYPE_STRING:
			{
				DATA_STRING *str=(DATA_STRING *)item->itemData;
				ptcsize+=(str->maxlen?(str->maxlen+1):0x10);
				//if(!str->maxlen)
				//{
				//	ptcsize+=0x10;
				//}
				//else
				//	ptcsize+=str->maxlen+1;
				break;
			}
		case TYPE_UNICODE:
			{
				DATA_UNICODE *uni=(DATA_UNICODE *)item->itemData;
				ptcsize+=(uni->maxlen?(2*(uni->maxlen+1)):0x20);
				//if(!uni->maxlen)
				//	ptcsize+=0x20;
				//else
				//	ptcsize+=uni->maxlen*2;
				break;
			}
		case TYPE_HEX:
			{
				DATA_HEX *hex=(DATA_HEX *)item->itemData;
				ptcsize+=(hex->maxlen?hex->maxlen:1);
				//if(hex->maxlen)
				//	ptcsize+=hex->maxlen;
				//else
				//	ptcsize+=0x1;
				break;
			}
		case TYPE_SF:
			{
				DATA_SF *fs=(DATA_SF *)item->itemData;
				ptcsize+=(fs->maxlen?fs->maxlen:58);
				break;
			}
		case TYPE_SD:
			{
				DATA_SD *sd=(DATA_SD *)item->itemData;
				ptcsize+=(sd->maxlen?sd->maxlen:58);
				break;
			}
		case TYPE_BYTES:
			{
				DATA_BYTES *dbytes=(DATA_BYTES *)item->itemData;
				ptcsize+=dbytes->len;
				break;
			}
		case TYPE_INTS:
			{
				DATA_INTS *dints=(DATA_INTS *)item->itemData;
				ptcsize+=(dints->len)*sizeof(int);
				break;
			}
		case TYPE_CONST:
			{
				DATA_CONST *dconst=(DATA_CONST *)item->itemData;
				ptcsize+=dconst->len;
				break;
			}
		//default :
		//	ptcsize+=4;
	}
	return ptcsize;
}


void savePatchConfig(PTC_CONFIG *ptcfg)
{
	char ptcpath[128];
	char ptcid[16];
	int ptcsize;
#ifdef WINTEL_DEBUG
	FILE *fp;
	int i=0;
	strcpy(ptcpath, PATCH_DIR);
	strcat(ptcpath, PTC_FOLDR);
	sprintf(ptcid, "%08s", ptcfg->patchInfo->patchID);
	strcat(ptcpath, ptcid);
	strcat(ptcpath, ".ptc");
	fp=fopen(ptcpath, "wab");
	if(!fp)
		return;
	for(;i<PTC_SIZE;i++)
		ptc_buf[i]=0;
	ptc_buf[0]=ptcfg->patchonoff;
	fillItemDataToBuf(ptcfg->mainitem.item);
	if(ptcfg->memory)
		ptcsize=ptcfg->memory;
	else
		ptcsize=getPtcSize(ptcfg->mainitem.item);
	fwrite(ptc_buf, 1, ptcsize, fp);
	fclose(fp);
#else
	int f;
	unsigned int ferr;
	strcpy(ptcpath, PATCH_DIR);
	strcat(ptcpath, PTC_FOLDR);
	if(!isdir(ptcpath, &ferr))
		mkdir(ptcpath, &ferr);
	sprintf(ptcid, _percent_08s, ptcfg->patchInfo->patchID);
	strcat(ptcpath, ptcid);
	strcat(ptcpath, ".ptc");
	f=fopen(ptcpath, A_BIN+A_ReadWrite, P_WRITE+P_READ, &ferr);
	if(f==-1)
	{
		f=fopen(ptcpath, A_BIN+A_ReadWrite+A_Create+A_Truncate, P_WRITE+P_READ, &ferr);
		if(f==-1)
			return;
		goto SAVE_DATA;
	}
	if(!ptcfg->needSaveData)
	{
		if(ptcfg->disableProfile)
		{
			if(getPatchOnOff(ptcfg, 7))
				ptcfg->patchonoff=0xFF;
			else
				ptcfg->patchonoff=0;
		}
		fwrite(f, &ptcfg->patchonoff, 1, &ferr);
	}
	else
	{
	SAVE_DATA:
		zeromem(ptc_buf, PTC_SIZE);
		if(ptcfg->disableProfile)
		{
			if(getPatchOnOff(ptcfg, 7))
				ptcfg->patchonoff=0xFF;
			else
				ptcfg->patchonoff=0;
		}
		ptc_buf[0]=ptcfg->patchonoff;
		fillItemDataToBuf(ptcfg->mainitem.item);	
		if(ptcfg->memory)
			ptcsize=ptcfg->memory;
		else
			ptcsize=getPtcSize(ptcfg->mainitem.item);
		fwrite(f, ptc_buf, ptcsize, &ferr);
	}
	fclose(f, &ferr);
#endif
}

void saveAllConfig(void)
{
	PTC_CONFIG *ptcfg=ptcfgtop;
	while(ptcfg)
	{
		savePatchConfig(ptcfg);
		ptcfg=ptcfg->next;
	}
}


