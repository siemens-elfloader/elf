/*
 * 文件名: getConfig.c
 * 作者: BingK(binghelingxi)
 *
 * 最后修改日期: 2008.08.05
 *
 * 作用: 读取config.txt，并进行解析，储存结果，还提供了一些文字处理函数
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
#endif
#include "getConfig.h"
#include "ptcFileWork.h"
#include "usedstr.h"
#include "string.h"
#include "main.h"


#ifdef	WINTEL_DEBUG
#define PATCH_DIR	"E:\\SRC\\SVN\\SieELF\\Master\\Patches\\"
char cfg_buf[CONFIG_SIZE];
int patch_n=0;
#define mfree free

#else

char cfg_buf[CONFIG_SIZE];
//char *cfg_buf;

#endif

PTC_CONFIG * volatile ptcfgtop=0;


//打开config.txt并载入到cfg_buf
int loadConfig(void)
{
	char cfg_path[128]=PATCH_DIR;
	int size=0;
#ifdef	WINTEL_DEBUG
	FILE *fp;
	strcpy(cfg_path, "E:\\SRC\\SVN\\SieELF\\Master\\Patches\\PTC\\configs.txt");
	fp=fopen(cfg_path, "rb");
	if(!fp)
	{
		cfg_buf[0]=0;
		return 0;
	}
	size=fread(cfg_buf, sizeof(char), CONFIG_SIZE, fp);
	fclose(fp);
#else
	int f;
	unsigned int ferr;
	FSTATS fstat;
	strcat(cfg_path, PTC_FOLDR);
	strcat(cfg_path, "configs.txt");
	if(GetFileStats(cfg_path,&fstat,&ferr)!=-1)
	{
		f=fopen(cfg_path, A_BIN+A_ReadOnly, P_READ, &ferr);
		if(f==-1)
		{
			return 0;
		}
		size=fstat.size;
		if(size<=0)
			return 0;
		//cfg_buf=malloc((size+3)&(~3));
		if(fread(f, cfg_buf, size, &ferr)!=size)
		{
			fclose(f, &ferr);
			//mfree(cfg_buf);
			return 0;
		}
		fclose(f, &ferr);
		cfg_buf[size]=0;
	}
	else
		return 0;
#endif
	return 1;
}
//将一个PTC_CONFIG指针添加到链表，即添加一个补丁
void addPatchConfigList(void)
{
	PTC_CONFIG *ptcfg=malloc(sizeof(PTC_CONFIG));
	ptcfg->prev=0;
	ptcfg->next=0;
	ptcfg->patchonoff=127; //all profile on, patch off 
	ptcfg->patchInfo=0;
	ptcfg->mainitem.smName[0]=0;
	ptcfg->mainitem.item=0;
	ptcfg->needSaveData=0;
	ptcfg->memory=0;
	ptcfg->disableProfile=0;
	ptcfg->offset=0;
	if(!ptcfgtop)
		ptcfgtop=ptcfg;
	else
	{
		PTC_CONFIG *ptcfg_1=ptcfgtop;
		ptcfgtop=ptcfg;
		ptcfg->next=ptcfg_1;
		ptcfg_1->prev=ptcfg;
	}
	patch_n++;
}

//添加作者，版本等信息
void addToPatchInfo(char *pdata)
{
	PATCH_INFO *ptcinfo=malloc(sizeof(PATCH_INFO));
	char *pp=pdata;
	char *p1; //start
	char *p2; //end
	ptcinfo->patchName[0]=0;
	ptcinfo->patchID[0]=0;
	ptcinfo->info=0;
	ptcinfo->author[0]=0;
	ptcinfo->version[0]=0;
	p1=gotoMyStrStart(pp);
	p2=gotoMyStrEnd(pp);
	strnCopyWithEnd(ptcinfo->patchName, p1, p2-p1);
	if((pp=strstrInQuote(pdata, "ver="))||(pp=strstrInQuote(pdata, "version=")))
	{
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(ptcinfo->version, p1, p2-p1);
	}
	if((pp=strstrInQuote(pdata, "cp="))||(pp=strstrInQuote(pdata, "copyright=")))
	{
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(ptcinfo->author, p1, p2-p1);
	}
	if(pp=strstrInQuote(pdata, "id="))
	{
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(ptcinfo->patchID, p1, p2-p1);
	}
	if((pp=strstrInQuote(pdata, "mem="))||(pp=strstrInQuote(pdata, "memory="))) //指定ptc长度
	{
		pp=gotoRealPos(pp);
		str2num(pp, &ptcfgtop->memory, 0,0, 0);
	}
	if((pp=strstrInQuote(pdata, STR_DISPF1))||(pp=strstrInQuote(pdata, STR_DISPF2)))
	{
		ptcfgtop->disableProfile=1;
	}
	ptcfgtop->patchInfo=ptcinfo;
}

//将预置的选项添加到条目
void addPreItemToData(PREPARE_DATA *preData, PREPARE_ITEM *prepareItem)
{
	if(!preData->prepareItem)
		preData->prepareItem=prepareItem;
	else
	{
		PREPARE_ITEM *preItem=preData->prepareItem;
		while(preItem->next) //goto last
			preItem=preItem->next;
		preItem->next=prepareItem;
		prepareItem->prev=preItem;
	}
}

//将条目添加到条目链表
void addItemToConfig(void *item, PATCH_SUBMENU *userPoint, int type, int bytePos, char *name)
{
	PATCH_ITEM *patchItem=malloc(sizeof(PATCH_ITEM));
	patchItem->prev=0;
	patchItem->next=0;
	patchItem->bytePos=bytePos;
	if(name)
	{
		cleanStrByChr(name, '`');
		cleanStrByChr(name, 0xA);
		cleanStrByChr(name, 0xD);
		strcpy(patchItem->itemName, name);
	}
	else
		patchItem->itemName[0]=0;
	patchItem->itemType=type;
	patchItem->itemData=item;
	if(!userPoint->item)
			userPoint->item=patchItem;
	else
	{
		PATCH_ITEM *pItem=userPoint->item;
		while(pItem->next) //goto last
			pItem=pItem->next;
		pItem->next=patchItem;
		patchItem->prev=pItem;
	}
}


//解析预置的选项，及其对应的数据，并添加到条目链表
void addPrepareData(char *pdata)
{
	char *p=pdata;
	char *pp;
	char *p1;
	char *p2;
	char *p3=gotoQuoteEnd(p);
	PREPARE_DATA *preData=malloc(sizeof(PREPARE_DATA));
	preData->useAs[0]=0;
	preData->prepareItem=0;
	p1=gotoMyStrStart(p);
	p2=gotoMyStrEnd(p);
	strnCopyWithEnd(preData->useAs, p1, p2-p1);
	p=p2+1;
	while((p<p3)&&(pp=gotoRealPos(p))&&(pp<p3)&&(p1=gotoMyStrStart(pp)))
	{
		PREPARE_ITEM *prepareItem=malloc(sizeof(PREPARE_ITEM));
		prepareItem->next=0;
		prepareItem->prev=0;
		prepareItem->itemName[0]=0;
		prepareItem->data=0;
		if(*pp=='`')
			p2=gotoMyStrEnd(pp);
		else
			p2=gotoStringEndByChr(pp, '=');
		strnCopyWithEnd(prepareItem->itemName, p1, p2-p1);
		cleanStrByChr(prepareItem->itemName, '`'); //可能是不标准的补丁格式
		if(*p2=='`')
			p=p2+2;
		else
		{
			p=p2+1;
		}
		str2num_char(p, &prepareItem->data, 0xff, 0, 0);
		addPreItemToData(preData, prepareItem);
		while(*p)
		{
			if(*p<=X_CHAR||*p=='`')
				break;
			p++;
		}
		//p=gotoStringEndByChr(p, X_CHAR);
	}
	addItemToConfig(preData, &ptcfgtop->mainitem, TYPE_PRE, 0, NULL);
}

//从预置的选项条目中读取数据到一个CBOX，即选择项
void addPreDataToCBoxItem(DATA_CBOX *cbox, char *p)
{
	//CBOX_ITEM *cboxitem=cbox->cboxitem;
	char *p1;
	char *p2;
	PATCH_ITEM *ptcitem=ptcfgtop->mainitem.item;
	PREPARE_ITEM *preitem=0;
	p=gotoRealPos(p);
	p1=gotoMyStrStart(p);
	p2=gotoMyStrEnd(p);
	while(ptcitem)
	{
		if(ptcitem->itemType==TYPE_PRE)
		{
			PREPARE_DATA *preData=ptcitem->itemData;
			if(!strncmpNoCase(preData->useAs, p1, p2-p1))
			{
				preitem=preData->prepareItem;
				break;
			}
		}
		ptcitem=ptcitem->next;
	}
	while(preitem)
	{
		CBOX_ITEM *tcitem=malloc(sizeof(CBOX_ITEM));
		tcitem->next=0;
		tcitem->prev=0;
		tcitem->data=preitem->data;
		strcpy(tcitem->name, preitem->itemName);
		if(!cbox->cboxitem)
			cbox->cboxitem=tcitem;
		else
		{
			CBOX_ITEM *cbitem=cbox->cboxitem;
			while(cbitem->next)
				cbitem=cbitem->next;
			cbitem->next=tcitem;
			tcitem->prev=cbitem;
		}
		preitem=preitem->next;
	}
}

//将选择项条目添加到选择项链表
void addItemToCBox(DATA_CBOX *cbox, CBOX_ITEM *cboxitem)
{
	if(!cbox->cboxitem)
		cbox->cboxitem=cboxitem;
	else
	{
		CBOX_ITEM *item=cbox->cboxitem;
		while(item->next)
			item=item->next;
		item->next=cboxitem;
		cboxitem->prev=item;
	}
}

//没有使用预置选择项条目，而直接在括号内读取选择项条目
void cboxItemColon(char *pdata, DATA_CBOX *cbox)
{
	//char *p=pdata;
	char *pp=pdata;
	char *p1;
	char *p2;
	char *p3=gotoQuoteEnd(pdata);
	if(*pp=='`')
		pp++;
	pp=gotoRealPos(pp);
	while(*pp && pp<p3 )
	{	
		CBOX_ITEM *cboxitem=malloc(sizeof(CBOX_ITEM));
		cboxitem->data=0;
		cboxitem->name[0]=0;
		cboxitem->next=0;
		cboxitem->prev=0;
		p1=gotoMyStrStart(pp);
		if(*pp=='`')
			p2=gotoMyStrEnd(pp);
		else
			p2=gotoStringEndByChr(pp, '=');
		strnCopyWithEnd(cboxitem->name, p1, p2-p1);
		while(*p2)
		{
			if(*p2=='=')
				break;
			p2++;
		}
		p2=gotoRealPos(p2+1);
		str2num_char(p2, &cboxitem->data, 0xff, 0, 0);
		addItemToCBox(cbox, cboxitem);
		pp=p2;
		while(*pp)
		{
			if(*pp<=X_CHAR||*pp=='`')
				break;
			pp++;
		}
		pp=gotoRealPos(pp);
	}
}


int isThatItem(char *p)
{
	while(*p)
	{
		if(*p>X_CHAR)
		{
			if(*p=='{')
				return 1;
			else
				return 0;
		}
		p--;
	}
	return 0;
}

PATCH_TP *findTemplate(PTC_CONFIG *ptcfg, char *p)
{
	PATCH_ITEM *pitem;
	if(!ptcfg)
		return 0;
	pitem=ptcfg->mainitem.item;
	while(pitem)
	{
		if(pitem->itemType==TYPE_TP)
		{
			PATCH_TP *tpl=(PATCH_TP *)pitem->itemData;
			if(!strncmpNoCase(tpl->useAs, p, strlen(p)))
				return tpl;
		}
		pitem=pitem->next;
	}
	return 0;
}
int isCurrectItem(char *p)
{
	char *s=p;
	while(*s)
	{
		if(*s=='{')
		{
			char *pp=s+1;
			//int i=0;
			pp=gotoRealPos(pp);
			pp=strchrInQuote(pp, ' ')+1;
			pp=gotoRealPos(pp);
			pp=strchrInQuote(pp, ' ');
			while(*pp)
			{
				if(pp==p)
					return 1;
				if(*pp<=' ')
					pp++;
				else
					return 0;
			}
			return 0;
		}
		s--;
	}
	return 0;
}

void subMenuCopy(PATCH_SUBMENU *sbmdst, PATCH_SUBMENU *sbmsrc, int byteBase);
//解析选择项条目
void doItemJob(char *p, PATCH_SUBMENU *subMenu)
{

	char *p1; //start
	char *p2; //end
	char *pp; //temp
	char temp[128];
	int bytePos=0;
	if((p1=strstrInQuote(p, STR_CHKBOX1))||(p1=strstrInQuote(p, STR_CHKBOX2)))
	{
		if(isCurrectItem(p1))
		{
		DATA_CHECKBOX *checkbox=malloc(sizeof(DATA_CHECKBOX));
		checkbox->bitPos=0;
		checkbox->onoff=0;
		pp=gotoRealPos(p1);
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(temp, p1, p2-p1);
		if((p1=strstrInQuote(p, STR_VL))||(p1=strstrInQuote(p, STR_VL1)))
			checkbox->onoff=1;
		pp=gotoRealPos(p+1);
		str2num(pp, &bytePos, 0, 0, 0);
		while(*pp>X_CHAR)
		{
			if(*pp=='.')
			{
				pp++;
				str2num(pp, &checkbox->bitPos, 8, 0, 0);
				break;
			}
			pp++;
		}
		addItemToConfig(checkbox, subMenu, TYPE_CHECKBOX, bytePos+ptcfgtop->offset, temp);
		return;
		}
	}
	if((p1=strstrInQuote(p, STR_XY2)))
	{
		
		if(isCurrectItem(p1))
		{
		DATA_POS *pos=malloc(sizeof(DATA_POS));
		pos->x=0;
		pos->off=0;
		pos->y=0;
		pos->w=0;
		pos->h=0;
		pp=gotoRealPos(p1);
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(temp, p1, p2-p1);
		if(p1=strstrInQuote(p, STR_X))
		{
			pp=gotoRealPos(p1);
			str2num_short(pp, &pos->x, 0xFFF, 0, 0);
		}
		if(p1=strstrInQuote(p, STR_Y))
		{
			pp=gotoRealPos(p1);
			str2num_short(pp, &pos->y, 0xFFF, 0, 0);
		}
		if(p1=strstrInQuote(p, STR_WIDTH))
		{
			pp=gotoRealPos(p1);
			str2num_short(pp, &pos->w, 0xFFF, 0, 0);
		}
		if(p1=strstrInQuote(p, STR_HIGHT))
		{
			pp=gotoRealPos(p1);
			str2num_short(pp, &pos->h, 0xFFF, 0, 0);
		}
		pp=gotoRealPos(p+1);
		str2num(pp, &bytePos, 0, 0, 0);
		addItemToConfig(pos, subMenu, TYPE_POS, bytePos+ptcfgtop->offset, temp);
		return;
		}
	}
	if((p1=strstrInQuote(p, STR_XY1)))
	{
		if(isCurrectItem(p1))
		{
		DATA_POS *pos=malloc(sizeof(DATA_POS));
		pos->x=0;
		pos->off=0;
		pos->y=0;
		pos->w=0;
		pos->h=0;
		pp=gotoRealPos(p1);
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(temp, p1, p2-p1);
		if(p1=strstrInQuote(p, STR_X))
		{
			pp=gotoRealPos(p1);
			str2num_short(pp, &pos->x, 0xFFF, 0, 0);
		}
		if(p1=strstrInQuote(p, STR_Y))
		{
			pp=gotoRealPos(p1);
			str2num_short(pp, &pos->y, 0xFFF, 0, 0);
		}
		if(p1=strstrInQuote(p, STR_WIDTH))
		{
			pp=gotoRealPos(p1);
			str2num_short(pp, &pos->w, 0xFFF, 0, 0);
		}
		if(p1=strstrInQuote(p, STR_HIGHT))
		{
			pp=gotoRealPos(p1);
			str2num_short(pp, &pos->h, 0xFFF, 0, 0);
		}
		pp=gotoRealPos(p+1);
		str2num(pp, &bytePos, 0, 0, 0);
		addItemToConfig(pos, subMenu, TYPE_POSB, bytePos+ptcfgtop->offset, temp);
		return;
		}
	}
	if((p1=strstrInQuote(p, " b "))||(p1=strstrInQuote(p, " byte ")))
	{
		if(isCurrectItem(p1))
		{
		DATA_BYTE *dbyte=malloc(sizeof(DATA_BYTE));
		dbyte->initData=0;
		dbyte->min=127;
		dbyte->min=~(dbyte->min)+1;
	#ifdef	WINTEL_DEBUG
		dbyte->max=127;
	#else
		dbyte->max=0xFF;
	#endif
		pp=gotoRealPos(p1);
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(temp, p1, p2-p1);
		if((p1=strstrInQuote(p, STR_VL))||(p1=strstrInQuote(p, STR_VL1)))
		{
			pp=gotoRealPos(p1);
			str2num_char(pp, &dbyte->initData, dbyte->max, dbyte->min, 0);
		}
		if((p1=strstrInQuote(p, STR_RANGE1))||(p1=strstrInQuote(p, STR_RANGE2)))
		{
			pp=gotoRealPos(p1);
			str2num_char(pp, &dbyte->min, dbyte->max, dbyte->min, 0);
			//while(*pp>='0'&&*pp<='9') //leave min
			//	pp++;
			while(*pp&&*pp!='.')
				pp++;
			while(*pp<'0'||*pp>'9') //to max
				pp++;
			str2num_char(pp, &dbyte->max, dbyte->max, dbyte->min, 0);
		}
		pp=gotoRealPos(p+1);
		str2num(pp, &bytePos, 0, 0, 0);
		addItemToConfig(dbyte, subMenu, TYPE_BYTE, bytePos+ptcfgtop->offset, temp);
		return;
		}
	}
	if((p1=strstrInQuote(p, " int "))||(p1=strstrInQuote(p, " i ")))
	{
		if(isCurrectItem(p1))
		{
		DATA_INT *dint=malloc(sizeof(DATA_INT));
		dint->initData=0;
		dint->max=0xFFFFFFF;
		dint->min=0xFFFFFFF;
		dint->min=~(dint->min);
		pp=gotoRealPos(p1);
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(temp, p1, p2-p1);
		if((p1=strstrInQuote(p, STR_VL))||(p1=strstrInQuote(p, STR_VL1)))
		{
			pp=gotoRealPos(p1);
			str2num(pp, &dint->initData, dint->max, dint->min, 0);
		}
		if((p1=strstrInQuote(p, STR_RANGE1))||(p1=strstrInQuote(p, STR_RANGE2)))
		{
			pp=gotoRealPos(p1);
			str2num(pp, &dint->min, dint->max, dint->min, 0);
			while(*pp>='0'&&*pp<='9') //leave min
				pp++;
			while(*pp<'0'||*pp>'9') //to max
				pp++;
			str2num(pp, &dint->max, dint->max, dint->min, 0);
		}
		pp=gotoRealPos(p+1);
		str2num(pp, &bytePos,0,0, 0);
		addItemToConfig(dint, subMenu, TYPE_INT, bytePos+ptcfgtop->offset, temp);
		return;
		}
	}
	if((p1=strstrInQuote(p, " o "))||(p1=strstrInQuote(p, " option ")))
	{
		if(isCurrectItem(p1))
		{
		DATA_CBOX *cbox=malloc(sizeof(DATA_CBOX));
		cbox->cboxitem=0;
		cbox->initData=0;
		pp=gotoRealPos(p1);
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(temp, p1, p2-p1);
		if(p1=strstrInQuote(p, STR_CHOICE)) //可能是IAR在中文系统的BUG，一个字符串被两次使用之后可能会报错
		{
			addPreDataToCBoxItem(cbox, p1);
		}
		else
		{
			cboxItemColon(p2, cbox);
		}
		if((p1=strstrInQuote(p, STR_VL))||(p1=strstrInQuote(p, STR_VL1)))
		{
			pp=gotoRealPos(p1);
			str2num_char(pp, &cbox->initData,0xFF,0, 0);
		}
		pp=gotoRealPos(p+1);
		str2num(pp, &bytePos,0,0, 0);
		addItemToConfig(cbox, subMenu, TYPE_CBOX, bytePos+ptcfgtop->offset, temp);
		return;
		}
	}
	if((p1=strstrInQuote(p, " co "))||(p1=strstrInQuote(p, " color ")))
	{
		if(isCurrectItem(p1))
		{
		DATA_COLOR *color=malloc(sizeof(DATA_COLOR));
		int *col=(int *)color->color;
		*col=0;
		pp=gotoRealPos(p1);
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(temp, p1, p2-p1);
		if((p1=strstrInQuote(p, STR_VL))||(p1=strstrInQuote(p, STR_VL1)))
		{
			pp=gotoRealPos(p1);
			str2num(pp, col,0,0, 0);
		}
		pp=gotoRealPos(p+1);
		str2num(pp, &bytePos,0,0, 0);
		addItemToConfig(color, subMenu, TYPE_COLOR, bytePos+ptcfgtop->offset, temp);
		return;
		}
	}
	if((p1=strstrInQuote(p, " a "))||(p1=strstrInQuote(p, " address ")))
	{
		if(isCurrectItem(p1))
		{
		DATA_ADDRESS *addr=malloc(sizeof(DATA_ADDRESS));
		addr->addr=0;
		pp=gotoRealPos(p1);
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(temp, p1, p2-p1);
		if((p1=strstrInQuote(p, STR_VL))||(p1=strstrInQuote(p, STR_VL1)))
		{
			pp=gotoRealPos(p1);
			str2num(pp, (int *)&addr->addr,0,0, 0);
		}
		pp=gotoRealPos(p+1);
		str2num(pp, &bytePos,0,0, 0);
		addItemToConfig(addr, subMenu, TYPE_ADDRESS, bytePos+ptcfgtop->offset, temp);
		return;
		}
	}
	if((p1=strstrInQuote(p, " sf "))||(p1=strstrInQuote(p, " selectfile ")))
	{
		if(isCurrectItem(p1))
		{
		DATA_SF *fs=malloc(sizeof(DATA_SF));
		int i=0;
		for(;i<128;i++)
			fs->path[i]=0;
		fs->mask[0]=0;
		fs->maxlen=0;
		pp=gotoRealPos(p1);
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(temp, p1, p2-p1);
		if((p1=strstrInQuote(p, STR_VL))||(p1=strstrInQuote(p, STR_VL1)))
		{
			pp=gotoRealPos(p1);
			p1=gotoMyStrStart(pp);
			p2=gotoMyStrEnd(pp);
			strnCopyWithEnd(fs->path, p1, p2-p1);
		}
		if(p1=strstrInQuote(p, "mask="))
		{
			pp=gotoRealPos(p1);
			p1=gotoMyStrStart(pp);
			p2=gotoMyStrEnd(pp);
			strnCopyWithEnd(fs->mask, p1, p2-p1);
		}
		if((p1=strstrInQuote(p, "ml="))||(p1=strstrInQuote(p, "maxlen=")))
		{
			pp=gotoRealPos(p1);
			str2num(pp, &fs->maxlen,0,0, 0);
		}
		pp=gotoRealPos(p+1);
		str2num(pp, &bytePos,0,0, 0);
		addItemToConfig(fs, subMenu, TYPE_SF, bytePos+ptcfgtop->offset, temp);
		return;
		}
	}
	if((p1=strstrInQuote(p, " sd "))||(p1=strstrInQuote(p, " selectdir ")))
	{
		if(isCurrectItem(p1))
		{
		DATA_SD *sd=malloc(sizeof(DATA_SD));
		sd->path[0]=0;
		sd->maxlen=0;
		pp=gotoRealPos(p1);
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(temp, p1, p2-p1);
		if((p1=strstrInQuote(p, STR_VL))||(p1=strstrInQuote(p, STR_VL1)))
		{
			pp=gotoRealPos(p1);
			p1=gotoMyStrStart(pp);
			p2=gotoMyStrEnd(pp);
			strnCopyWithEnd(sd->path, p1, p2-p1);
		}
		if((p1=strstrInQuote(p, "ml="))||(p1=strstrInQuote(p, "maxlen=")))
		{
			pp=gotoRealPos(p1);
			str2num(pp, &sd->maxlen,0,0, 0);
		}
		pp=gotoRealPos(p+1);
		str2num(pp, &bytePos,0,0, 0);
		addItemToConfig(sd, subMenu, TYPE_SD, bytePos+ptcfgtop->offset, temp);
		return;
		}
	}
	if((p1=strstrInQuote(p, " s "))||(p1=strstrInQuote(p, " string ")))
	{
		if(isCurrectItem(p1))
		{
		DATA_STRING *string=malloc(sizeof(DATA_STRING));
		int i=0;
		string->maxlen=0;
		for(;i<128;i++)
			string->string[i]=0;
		pp=gotoRealPos(p1);
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(temp, p1, p2-p1);
		if((p1=strstrInQuote(p, STR_VL))||(p1=strstrInQuote(p, STR_VL1)))
		{
			pp=gotoRealPos(p1);
			p1=gotoMyStrStart(pp);
			p2=gotoMyStrEnd(pp);
			strnCopyWithEnd(string->string, p1, p2-p1);
		}
		if((p1=strstrInQuote(p, "ml="))||(p1=strstrInQuote(p, "maxlen=")))
		{
			pp=gotoRealPos(p1);
			str2num(pp, &string->maxlen,0,0, 0);
		}
		pp=gotoRealPos(p+1);
		str2num(pp, &bytePos,0,0, 0);
		addItemToConfig(string, subMenu, TYPE_STRING, bytePos+ptcfgtop->offset, temp);
		return;
		}
	}
	if((p1=strstrInQuote(p, " u "))||(p1=strstrInQuote(p, " ustring ")))
	{
		if(isCurrectItem(p1))
		{
		DATA_UNICODE *uni=malloc(sizeof(DATA_UNICODE));
		int j=0;
		uni->maxlen=0;
		for(;j<128;j++)
			uni->ustr[j]=0;
		pp=gotoRealPos(p1);
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(temp, p1, p2-p1);
		if((p1=strstrInQuote(p, STR_VL))||(p1=strstrInQuote(p, STR_VL1)))//添加UNICODE字符
		{
			int i=0;
			unsigned short c, c1;
			pp=gotoRealPos(p1);
			p1=gotoMyStrStart(pp);
			p2=gotoMyStrEnd(pp);
			while((p1<p2)&&(c=*p1++)&&i<127) //max
			{
				if(c<=127)
					uni->ustr[i++]=c;
				else
				{
					c1=*p1++;
					if(c1<=127)
						uni->ustr[i++]=c1;
					else
						uni->ustr[i++]=c1*0x10+c1;
				}
			}
		}
		if((p1=strstrInQuote(p, "ml="))||(p1=strstrInQuote(p, "maxlen=")))
		{
			pp=gotoRealPos(p1);
			str2num(pp, &uni->maxlen,0,0, 0);
		}
		pp=gotoRealPos(p+1);
		str2num(pp, &bytePos,0,0, 0);
		addItemToConfig(uni, subMenu, TYPE_UNICODE, bytePos+ptcfgtop->offset, temp);
		return;
		}
	}
	if((p1=strstrInQuote(p, " h "))||(p1=strstrInQuote(p, " hex ")))
	{
		if(isCurrectItem(p1))
		{
		DATA_HEX *hex=malloc(sizeof(DATA_HEX));
		int i=0;
		for(;i<128;i++)
			hex->hex[i]=0;
		hex->maxlen=0;
		pp=gotoRealPos(p1);
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(temp, p1, p2-p1);
		if((p1=strstrInQuote(p, STR_VL))||(p1=strstrInQuote(p, STR_VL1)))
		{
			unsigned char c, c1;
			i=0;
			pp=gotoRealPos(p1);
			p1=gotoMyStrStart(pp);
			p2=gotoMyStrEnd(pp);
			while((c=*p1++)&& p1<p2)
			{
				if((c>='0'&&c<='9')||(c>='a'&&c<='f')||(c>='A'&&c<='F'))
				{
					c1=*p1++;
					if((c1>='0'&&c1<='9')||(c1>='a'&&c1<='f')||(c1>='A'&&c1<='F'))
						hex->hex[i++]=chr2num(c)*0x10+chr2num(c1);
					else
						break;
				}
				else
					break;
			}
		}
		if((p1=strstrInQuote(p, "ml="))||(p1=strstrInQuote(p, "maxlen=")))
		{
			pp=gotoRealPos(p1);
			str2num(pp, &hex->maxlen,0,0, 0);
		}
		pp=gotoRealPos(p+1);
		str2num(pp, &bytePos,0,0, 0);
		addItemToConfig(hex, subMenu, TYPE_HEX, bytePos+ptcfgtop->offset, temp);
		return;
		}
	}
	if((p1=strstrInQuote(p, STR_SLIDER2))||(p1=strstrInQuote(p, STR_SLIDER1)))
	{
		if(isCurrectItem(p1))
		{
		DATA_SL *sl=malloc(sizeof(DATA_SL));
		sl->initData=0;
		sl->max=0;
		sl->min=0;
		pp=gotoRealPos(p1);
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(temp, p1, p2-p1);
		if((p1=strstrInQuote(p, STR_VL))||(p1=strstrInQuote(p, STR_VL1)))
		{
			pp=gotoRealPos(p1);
			str2num_char(pp, &sl->initData, 0, 0, 0);
		}
		if((p1=strstrInQuote(p, STR_RANGE1))||(p1=strstrInQuote(p, STR_RANGE2)))
		{
			pp=gotoRealPos(p1);
			str2num_char(pp, &sl->min,0,0, 0);
			while(*pp>='0'&&*pp<='9') //leave min
				pp++;
			while(*pp<'0'||*pp>'9') //to max
				pp++;
			str2num_char(pp, &sl->max,0,0, 0);
		}
		pp=gotoRealPos(p+1);
		str2num(pp, &bytePos,0,0, 0);
		addItemToConfig(sl, subMenu, TYPE_SL, bytePos+ptcfgtop->offset, temp);
		return;
		}
	}
	if((p1=strstrInQuote(p, STR_USETEMPLATE1))||(p1=strstrInQuote(p, STR_USRTEMPLATE2)))
	{
		if(isCurrectItem(p1))
		{
		//DATA_USETP *usetp=malloc(sizeof(DATA_USETP));
		//usetp->tpName[0]=0;
		PATCH_TP *tpl;
		pp=gotoRealPos(p1);
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(temp, p1, p2-p1);
		pp=gotoRealPos(p+1);
		str2num(pp, &bytePos,0,0, 0);
		if(tpl=findTemplate(ptcfgtop, temp))
			subMenuCopy(subMenu, (PATCH_SUBMENU *)tpl, bytePos+ptcfgtop->offset);
		return;
		}
	}
	if((p1=strstrInQuote(p, STR_MS1))||(p1=strstrInQuote(p, STR_MS2)))
	{
		if(isCurrectItem(p1))
		{
		DATA_MS *ms=malloc(sizeof(DATA_MS));
		ms->ms=0;
		pp=gotoRealPos(p1);
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(temp, p1, p2-p1);
		if((p1=strstrInQuote(p, STR_VL))||(p1=strstrInQuote(p, STR_VL1)))
		{
			pp=gotoRealPos(p1);
			str2num(pp, (int *)&ms->ms, 0, 0, 0);
		}
		pp=gotoRealPos(p+1);
		str2num(pp, &bytePos,0,0, 0);
		addItemToConfig(ms, subMenu, TYPE_MS, bytePos+ptcfgtop->offset, temp);
		return;
		}
	}
	if((p1=strstrInQuote(p, STR_BYTES1))||(p1=strstrInQuote(p, STR_BYTES2)))
	{
		char *p3=p1;
		while(*p3)
		{
			if(*p3==')')
				break;
			if(*p3=='}')
				return;
			p3++;
		}
		p3++;
		if(isCurrectItem(p3))
		{
		int i=0;
		//char c;
		DATA_BYTES *dbytes=malloc(sizeof(DATA_BYTES));
		dbytes->min=0;
		dbytes->max=127;
		dbytes->len=0;
		for(;i<128;i++)
			dbytes->bytes[i]=0;
		pp=gotoRealPos(p1);
		str2num(pp, &dbytes->len, 0, 0, 0);
		if((dbytes->len)>128)
			dbytes->len=128;
		pp=gotoRealPos(p3);
		p1=gotoMyStrStart(pp);
		p2=gotoMyStrEnd(pp);
		strnCopyWithEnd(temp, p1, p2-p1);
		if((p1=strstrInQuote(p, STR_VL))||(p1=strstrInQuote(p, STR_VL1)))
		{
			//pp=gotoRealPos(p1);
			str2bytes(dbytes->bytes, p1, dbytes->len);
		}
		if((p1=strstrInQuote(p, STR_RANGE1))||(p1=strstrInQuote(p, STR_RANGE2)))
		{
			pp=gotoRealPos(p1);
			str2num_char(pp, &dbytes->min, 0xFF, 0, 0);
			//while(*pp>='0'&&*pp<='9') //leave min
			//	pp++;
			while(*pp&&*pp!='.')
				pp++;
			while(*pp<'0'||*pp>'9') //to max
				pp++;
			str2num_char(pp, &dbytes->max, 0xFF, 0, 0);
		}
		pp=gotoRealPos(p+1);
		str2num(pp, &bytePos, 0, 0, 0);
		addItemToConfig(dbytes, subMenu, TYPE_BYTES, bytePos+ptcfgtop->offset, temp);
		return;
		}
	}
	if((p1=strstrInQuote(p, STR_INTS1))||(p1=strstrInQuote(p, STR_INTS2)))
	{
		char *p3=p1;
		while(*p3)
		{
			if(*p3==')')
				break;
			if(*p3=='}')
				return;
			p3++;
		}
		p3++;
		if(isCurrectItem(p3))
		{
			int i=0;
			//char c;
			DATA_INTS *dints=malloc(sizeof(DATA_INTS));
			dints->min=0;
			dints->max=127;
			dints->len=0;
			for(;i<128;i++)
				dints->ints[i]=0;
			pp=gotoRealPos(p1);
			str2num(pp, &dints->len, 0, 0, 0);
			if((dints->len)>128)
				dints->len=128;
			pp=gotoRealPos(p3);
			p1=gotoMyStrStart(pp);
			p2=gotoMyStrEnd(pp);
			strnCopyWithEnd(temp, p1, p2-p1);
			if((p1=strstrInQuote(p, STR_VL))||(p1=strstrInQuote(p, STR_VL1)))
			{
				str2ints(dints->ints, p1, dints->len);
			}
			if((p1=strstrInQuote(p, STR_RANGE1))||(p1=strstrInQuote(p, STR_RANGE2)))
			{
				pp=gotoRealPos(p1);
				str2num(pp, &dints->min, 0xFF, 0, 0);
				while(*pp&&*pp!='.')
					pp++;
				while(*pp<'0'||*pp>'9') //to max
					pp++;
				str2num(pp, &dints->max, 0xFF, 0, 0);
			}
			pp=gotoRealPos(p+1);
			str2num(pp, &bytePos, 0, 0, 0);
			addItemToConfig(dints, subMenu, TYPE_INTS, bytePos+ptcfgtop->offset, temp);
			return;
		}
	}
	if(p1=strstrInQuote(p, STR_CONST))
	{
		if(isCurrectItem(p1))
		{
			DATA_CONST *dconst=malloc(sizeof(DATA_CONST));
			dconst->data=0;
			dconst->len=1;
			pp=gotoRealPos(p1);
			p1=gotoMyStrStart(pp);
			p2=gotoMyStrEnd(pp);
			strnCopyWithEnd(temp, p1, p2-p1);
			if((p1=strstrInQuote(p, STR_VL))||(p1=strstrInQuote(p, STR_VL1)))
			{
				pp=gotoRealPos(p1);
				str2num(pp, &dconst->data, 0, 0, 0);
			}
			if(p1=strstrInQuote(p, " size="))
			{
				pp=gotoRealPos(p1);
				str2num(pp, &dconst->len, 0, 0, 0);
				if(dconst->len>4)
					dconst->len=4;
			}
			pp=gotoRealPos(p+1);
			str2num(pp, &bytePos,0,0, 0);
			addItemToConfig(dconst, subMenu, TYPE_CONST, bytePos+ptcfgtop->offset, temp);
			return;
		}
	}
}

//解析SUBMENU，子菜单
char *doSubMenuJob(PATCH_SUBMENU *motherMenu, char *pdata)
{
	char *p=pdata;
	char *pp;
	char *p1;
	char *p2;
	PATCH_SUBMENU *subMenu=malloc(sizeof(PATCH_SUBMENU));
	subMenu->item=0;
	subMenu->smName[0]=0;
	p=gotoRealPos(p);
	p1=gotoMyStrStart(p);
	p2=gotoMyStrEnd(p);
	strnCopyWithEnd(subMenu->smName, p1, p2-p1);
	pp=gotoQuoteEnd(p);
	if(!pp)
		goto END;
	p=++pp;
	while(*p)
	{
		if(*p=='{') //sirect string
			break;
		if(*p<0xA) //
			break;
		if((*p>X_CHAR)&&(*p!=',')) //判断是这直接显示的字符
		{
			DATA_DRSTR *drstr=malloc(sizeof(DATA_DRSTR));
			char *p1=p;
			char *p2=gotoQuoteStart(p)-1;
			while(*p2)
			{
				if(*p2>X_CHAR)
					break;
				p2--;
			}
			p2++;
			strnCopyWithEnd(drstr->str, p1, p2-p1);
			addItemToConfig(drstr, subMenu, TYPE_DRSTR, 0, NULL);
			break;
		}
		p++;
	}
	pp=gotoQuoteStart(p);
	if(!pp)
		goto END;
	p=pp;
	if(!*p)
		goto END;
	while(!(strstrInQuote(p, STR_ENDSUBMENU2))&&!(strstrInQuote(p, STR_ENDSUBMENU1)))//判断结尾
	{
		if((p2=strstrInQuote(p, STR_SUBMENU1)))
		{
			p=doSubMenuJob(subMenu, p2);
		}
		else if((p2=strstrInQuote(p, STR_SUBMENU2))&&(isThatItem(p2-3)))
		{
			//if(isThatItem(p2-3))
			{
				if(*p2=='=')
					p2++;
				p=doSubMenuJob(subMenu, p2);
			}
		}
		else
			doItemJob(p, subMenu);
		pp=gotoQuoteEnd(p);
		if(!pp)
			break;
		p=++pp;
		while(*p)
		{
			if(*p=='{') //sirect string
				break;
			if(*p<0xA) //
				break;
			if((*p>X_CHAR)&&(*p!=',')) //判断是这直接显示的字符
			{
				DATA_DRSTR *drstr=malloc(sizeof(DATA_DRSTR));
				char *p1=p;
				char *p2=gotoQuoteStart(p)-1;
				while(*p2)
				{
					if(*p2>X_CHAR)
						break;
					p2--;
				}
				p2++;
				strnCopyWithEnd(drstr->str, p1, p2-p1);
				addItemToConfig(drstr, subMenu, TYPE_DRSTR, 0, NULL);
				break;
			}
			p++;
		}
		pp=gotoQuoteStart(p);
		if(!pp)
			break;
		p=pp;
		if(!*p)
			break;
	}
END:
	addItemToConfig(subMenu, motherMenu, TYPE_SUBMENU, 0, subMenu->smName);
	return (p);
}

//添加补丁信息，特征字符: info
void addInfoToPatchInfo(char *pdata)
{
	char *p=pdata;
	char *pp;
	char *p1;
	char *p2;
	char *info=malloc(256);
	pp=gotoRealPos(p);
	p1=gotoMyStrStart(pp);
	p2=gotoMyStrEnd(pp);
	strnCopyWithEnd(info, p1, p2-p1);
	ptcfgtop->patchInfo->info=info;
}
//判断是否是预置的选择项
int isPrepareItem(char *p)
{
	char c=*p--;
	if(!c)
		return 0;
	c=*p--;
	if(!c)
		return 0;
	c=*p--;
	if(!c)
		return 0;
	//p-=3; //go back
	while(*p)
	{
		if(*p>=X_CHAR)
		{
			if(*p=='{')
				return 1;
			else 
				return 0;
		}
		p--;
	}
	return 0;
}
char *doTemplateWork(char *pdata)
{
	PATCH_TP *tpl=malloc(sizeof(PATCH_TP));
	char *p=pdata;
	char *pp;
	char *p1;
	char *p2;
	tpl->item=0;
	tpl->useAs[0]=0;
	pp=gotoRealPos(p);
	p1=gotoMyStrStart(pp);
	p2=gotoMyStrEnd(pp);
	strnCopyWithEnd(tpl->useAs, p1, p2-p1);
	pp=gotoQuoteEnd(p);
	if(!pp)
		goto END;
	p=++pp;
	while(*p)
	{
		if(*p=='{') //sirect string
			break;
		if(*p<0xA) //
			break;
		if((*p>X_CHAR)&&(*p!=',')) //判断是这直接显示的字符
		{
			DATA_DRSTR *drstr=malloc(sizeof(DATA_DRSTR));
			char *p1=p;
			char *p2=gotoQuoteStart(p)-1;
			while(*p2)
			{
				if(*p2>X_CHAR)
					break;
				p2--;
			}
			p2++;
			strnCopyWithEnd(drstr->str, p1, p2-p1);
			addItemToConfig(drstr, (PATCH_SUBMENU *)tpl, TYPE_DRSTR, 0, NULL);
			break;
		}
		p++;
	}
	pp=gotoQuoteStart(p);
	if(!pp)
		goto END;
	p=pp;
	if(!*p)
		goto END;
	while(!(strstrInQuote(p, STR_ENDTEMPLATE1))&&!(strstrInQuote(p, STR_ENDTEMPLATE2)))
	{
		if((p2=strstrInQuote(p, STR_SUBMENU1)))
		{
			p=doSubMenuJob((PATCH_SUBMENU *)tpl, p2);
		}
		else if((p2=strstrInQuote(p, STR_SUBMENU2))&&(isThatItem(p2-3)))
		{
			//if(isThatItem(p2-3))
			{
				if(*p2=='=')
					p2++;
				p=doSubMenuJob((PATCH_SUBMENU *)tpl, p2);
			}
		}
		else
			doItemJob(p, (PATCH_SUBMENU *)tpl);
		pp=gotoQuoteEnd(p);
		if(!pp)
			break;
		p=++pp;
		while(*p)
		{
			if(*p=='{') //sirect string
				break;
			if(*p<0xA) //
				break;
			if((*p>X_CHAR)&&(*p!=',')) //判断是这直接显示的字符
			{
				DATA_DRSTR *drstr=malloc(sizeof(DATA_DRSTR));
				char *p1=p;
				char *p2=gotoQuoteStart(p)-1;
				while(*p2)
				{
					if(*p2>X_CHAR)
						break;
					p2--;
				}
				p2++;
				strnCopyWithEnd(drstr->str, p1, p2-p1);
				addItemToConfig(drstr, (PATCH_SUBMENU *)tpl, TYPE_DRSTR, 0, NULL);
				break;
			}
			p++;
		}
		pp=gotoQuoteStart(p);
		if(!pp)
			break;
		p=pp;
		if(!*p)
			break;
	}
END:
	addItemToConfig(tpl, &ptcfgtop->mainitem, TYPE_TP, 0, tpl->useAs);
	return (p);
}

void subMenuCopy(PATCH_SUBMENU *sbmdst, PATCH_SUBMENU *sbmsrc, int byteBase)
{
	PATCH_ITEM *pitem;
	int bytePos;
	if(!sbmsrc)
		return;
	pitem=sbmsrc->item;
	while(pitem)
	{
		bytePos=pitem->bytePos;
		switch(pitem->itemType)
		{
		case TYPE_DRSTR:
			{
				DATA_DRSTR *dstr1=(DATA_DRSTR *)pitem->itemData;
				DATA_DRSTR *dstr=malloc(sizeof(DATA_DRSTR));
				strcpy(dstr->str, dstr1->str);
				addItemToConfig(dstr, sbmdst, TYPE_DRSTR, 0, NULL);
				break;
			}
		case TYPE_CHECKBOX:
			{
				DATA_CHECKBOX *chkbox1=(DATA_CHECKBOX *)pitem->itemData;
				DATA_CHECKBOX *chkbox=malloc(sizeof(DATA_CHECKBOX));
				chkbox->bitPos=chkbox1->bitPos;
				chkbox->onoff=chkbox1->onoff;
				addItemToConfig(chkbox, sbmdst, TYPE_CHECKBOX, bytePos+byteBase, pitem->itemName);
				break;
			}
		case TYPE_POS:
			{
				DATA_POS *pos1=(DATA_POS *)pitem->itemData;
				DATA_POS *pos=malloc(sizeof(DATA_POS));
				pos->x=pos1->x;
				pos->off=pos1->off;
				pos->y=pos1->y;
				pos->w=pos1->w;
				pos->h=pos1->h;
				addItemToConfig(pos, sbmdst, TYPE_POS, bytePos+byteBase, pitem->itemName);
				break;
			}
		case TYPE_BYTE:
			{
				DATA_BYTE *dbyte1=(DATA_BYTE *)pitem->itemData;
				DATA_BYTE *dbyte=malloc(sizeof(DATA_BYTE));
				dbyte->initData=dbyte1->initData;
				dbyte->max=dbyte1->max;
				dbyte->min=dbyte1->min;
				addItemToConfig(dbyte, sbmdst, TYPE_BYTE, bytePos+byteBase, pitem->itemName);
				break;
			}
		case TYPE_INT:
			{
				DATA_INT *dint1=(DATA_INT *)pitem->itemData;
				DATA_INT *dint=malloc(sizeof(DATA_INT));
				dint->initData=dint1->initData;
				dint->max=dint1->max;
				dint->min=dint1->min;
				addItemToConfig(dint, sbmdst, TYPE_INT, bytePos+byteBase, pitem->itemName);
				break;
			}
		case TYPE_CBOX:
			{
				DATA_CBOX *cbox1=(DATA_CBOX *)pitem->itemData;
				DATA_CBOX *cbox=malloc(sizeof(DATA_CBOX));
				CBOX_ITEM *cbitem=cbox1->cboxitem;
				CBOX_ITEM *ct;
				CBOX_ITEM *ct2;
				cbox->cboxitem=0;
				cbox->initData=cbox1->initData;
				while(cbitem)
				{
					ct=malloc(sizeof(CBOX_ITEM));
					ct->data=cbitem->data;
					ct->next=0;
					ct->prev=0;
					strcpy(ct->name, cbitem->name);
					if(!cbox->cboxitem)
						cbox->cboxitem=ct;
					else
					{
						ct2=cbox->cboxitem;
						while(ct2->next) //goto last
						{
							ct2=ct2->next;
						}
						ct2->next=ct;
						ct->prev=ct2;
					}
					cbitem=cbitem->next;
				}
				addItemToConfig(cbox, sbmdst, TYPE_CBOX, bytePos+byteBase, pitem->itemName);
				break;
			}
		case TYPE_COLOR:
			{
				DATA_COLOR *color1=(DATA_COLOR *)pitem->itemData;
				DATA_COLOR *color=malloc(sizeof(DATA_COLOR));
				memcpy(color, color1, sizeof(DATA_COLOR));
				addItemToConfig(color, sbmdst, TYPE_COLOR, bytePos+byteBase, pitem->itemName);
				break;
			}
		case TYPE_ADDRESS:
			{
				DATA_ADDRESS *addr1=(DATA_ADDRESS *)pitem->itemData;
				DATA_ADDRESS *addr=malloc(sizeof(DATA_ADDRESS));
				addr->addr=addr1->addr;
				addItemToConfig(addr, sbmdst, TYPE_ADDRESS, bytePos+byteBase, pitem->itemName);
				break;
			}
		case TYPE_STRING:
			{
				DATA_STRING *str1=(DATA_STRING *)pitem->itemData;
				DATA_STRING *str=malloc(sizeof(DATA_STRING));
				str->maxlen=str1->maxlen;
				strcpy(str->string, str1->string);
				addItemToConfig(str, sbmdst, TYPE_STRING, bytePos+byteBase, pitem->itemName);
				break;
			}
		case TYPE_UNICODE:
			{
				DATA_UNICODE *uni1=(DATA_UNICODE *)pitem->itemData;
				DATA_UNICODE *uni=malloc(sizeof(DATA_UNICODE));
				uni->maxlen=uni1->maxlen;
				memcpy(uni->ustr, uni1->ustr, sizeof(short)*128);
				addItemToConfig(uni, sbmdst, TYPE_UNICODE, bytePos+byteBase, pitem->itemName);
				break;
			}
		case TYPE_SUBMENU:
			{
				PATCH_SUBMENU *submenu1=(PATCH_SUBMENU *)pitem->itemData;
				PATCH_SUBMENU *submenu=malloc(sizeof(PATCH_SUBMENU));
				submenu->item=0;
				strcpy(submenu->smName, submenu1->smName);
				subMenuCopy(submenu, submenu1, byteBase);
				addItemToConfig(submenu, sbmdst, TYPE_SUBMENU, bytePos+byteBase, pitem->itemName);
				break;
			}
		case TYPE_HEX:
			{
				DATA_HEX *hex1=(DATA_HEX *)pitem->itemData;
				DATA_HEX *hex=malloc(sizeof(DATA_HEX));
				hex->maxlen=hex1->maxlen;
				memcpy(hex->hex, hex1->hex, 128);
				addItemToConfig(hex, sbmdst, TYPE_HEX, bytePos+byteBase, pitem->itemName);
				break;
			}
		case TYPE_SF:
			{
				DATA_SF *sf1=(DATA_SF *)pitem->itemData;
				DATA_SF *sf=malloc(sizeof(DATA_SF));
				sf->maxlen=sf1->maxlen;
				strcpy(sf->mask, sf1->mask);
				strcpy(sf->path, sf1->path);
				addItemToConfig(sf, sbmdst, TYPE_SF, bytePos+byteBase, pitem->itemName);
				break;
			}
		case TYPE_SD:
			{
				DATA_SD *sd1=(DATA_SD *)pitem->itemData;
				DATA_SD *sd=malloc(sizeof(DATA_SD));
				sd->maxlen=sd1->maxlen;
				strcpy(sd->path,sd1->path);
				addItemToConfig(sd, sbmdst, TYPE_SD, bytePos+byteBase, pitem->itemName);
				break;
			}
		case TYPE_SL:
			{
				DATA_SL *sl1=(DATA_SL *)pitem->itemData;
				DATA_SL *sl=malloc(sizeof(DATA_SL));
				sl->initData=sl1->initData;
				sl->max=sl1->max;
				sl->min=sl1->min;
				addItemToConfig(sl, sbmdst, TYPE_SL, bytePos+byteBase, pitem->itemName);
				break;
			}
		case TYPE_MS:
			{
				DATA_MS *ms1=(DATA_MS *)pitem->itemData;
				DATA_MS *ms=malloc(sizeof(DATA_MS));
				ms->ms=ms1->ms;
				addItemToConfig(ms, sbmdst, TYPE_MS, bytePos+byteBase, pitem->itemName);
				break;
			}
		case TYPE_POSB:
			{
				DATA_POS *pos1=(DATA_POS *)pitem->itemData;
				DATA_POS *pos=malloc(sizeof(DATA_POS));
				pos->x=pos1->x;
				pos->off=pos1->off;
				pos->y=pos1->y;
				pos->w=pos1->w;
				pos->h=pos1->h;
				addItemToConfig(pos, sbmdst, TYPE_POSB, bytePos+byteBase, pitem->itemName);
				break;
			}
		case TYPE_BYTES:
			{
				DATA_BYTES *dbytes1=(DATA_BYTES *)pitem->itemData;
				DATA_BYTES *dbytes=malloc(sizeof(DATA_BYTES));
				memcpy(dbytes, dbytes1, sizeof(DATA_BYTES));
				addItemToConfig(dbytes, sbmdst, TYPE_BYTES, bytePos+byteBase, pitem->itemName);
				break;
			}
		case TYPE_INTS:
			{
				DATA_INTS *dints1=(DATA_INTS *)pitem->itemData;
				DATA_INTS *dints=malloc(sizeof(DATA_INTS));
				memcpy(dints, dints1, sizeof(DATA_INTS));
				addItemToConfig(dints, sbmdst, TYPE_INTS, bytePos+byteBase, pitem->itemName);
				break;
			}
		case TYPE_CONST:
			{
				DATA_CONST *dconst1=(DATA_CONST *)pitem->itemData;
				DATA_CONST *dconst=malloc(sizeof(DATA_CONST));
				dconst->data=dconst1->data;
				dconst->len=dconst1->len;
				addItemToConfig(dconst, sbmdst, TYPE_CONST, bytePos+byteBase, pitem->itemName);
				break;
			}
		}
		pitem=pitem->next;
	}
}
void sortPatchConfigList(void);
int readConfig(int type, char *tp) //type, 1,load one, 0,load all
{
	char *p;
	char *pp; //tmp start
	char *p2; //tmp vol
	if(type&&tp)
	{
		p=tp;
	}
	else
	{
		if(!loadConfig())
			return 0;
		p=cfg_buf;
	}
	p=gotoRealPos(p);
	while(*p)
	{
		pp=gotoQuoteStart(p);
		p=pp;
		if(!pp)
			break;
		//getnextpatch
		if((p2=strstrInQuote(pp, "patch="))||(p2=strstrInQuote(pp, "patch ")))
		{
			if(type)//读取完一个补丁就了事，用于重新载入一个补丁
				goto END;
			addPatchConfigList();
			addToPatchInfo(p2); ////Jump to name
			goto ANYWHERE;
		}
		if((p2=strstrInQuote(pp, "p ")))
		{
			if(isThatItem(p2-3))
			{
				if(type)//读取完一个补丁就了事，用于重新载入一个补丁
					goto END;
				addPatchConfigList();
				addToPatchInfo(p2); ////Jump to name
				goto ANYWHERE;
			}
		}
		if((p2=strstrInQuote(pp, "p=")))
		{
			if(isThatItem(p2-3))
			{
				if(type)//读取完一个补丁就了事，用于重新载入一个补丁
					goto END;
				addPatchConfigList();
				addToPatchInfo(p2); ////Jump to name
				goto ANYWHERE;
			}
		}
		if((p2=strstrInQuote(pp, "of ")))
		{
			if(isThatItem(p2-4))
			{
				char *s=gotoRealPos(p2);
				//if(*s=='-')
				//{
				//	s++;
				//	str2num(s, &ptcfgtop->offset, 0, 0, 0);
				//	ptcfgtop->offset=(-1)*(ptcfgtop->offset);
				//}
				//else
				{
					if(*s=='+')
						s++;
					str2num(s, &ptcfgtop->offset, 0, 0, 0);
				}
				goto ANYWHERE;
			}
		}
		if((p2=strstrInQuote(pp, "offset ")))
		{
			if(isThatItem(p2-8))
			{
				char *s=gotoRealPos(p2);
				//if(*s=='-')
				//{
				//	s++;
				//	str2num(s, &ptcfgtop->offset, 0, 0, 0);
				//	ptcfgtop->offset=0-(ptcfgtop->offset);
				//}
				//else
				{
					if(*s=='+')
						s++;
					str2num(s, &ptcfgtop->offset, 0, 0, 0);
				}
				goto ANYWHERE;
			}
		}
		if((p2=strstrInQuote(pp, "info")))
		{
			if(isThatItem(p2-5))
			{
				addInfoToPatchInfo(p2);
				goto ANYWHERE;
			}
		}
		if((p2=strstrInQuote(pp, STR_CHOICE))||(p2=strstrInQuote(pp, STR_CHOICE1))||(p2=strstrInQuote(pp, STR_CHOICE2)))
		{
			if(isPrepareItem(p2))
			{
				addPrepareData(p2); //Jump to 
				goto ANYWHERE;
			}
			//else
			//	doItemJob(pp, &ptcfgtop->mainitem);
			//goto ANYWHERE;
		}
		if((p2=strstrInQuote(pp, STR_TEMPLATE1)))
		{
			if(isThatItem(p2-3))
			{
				p=doTemplateWork(p2);
				goto ANYWHERE;
			}
		}
		if((p2=strstrInQuote(pp, STR_TEMPLATE2)))
		{
			p=doTemplateWork(p2);       
		}
		else
		{
			if((p2=strstrInQuote(pp, STR_SUBMENU2)))
			{
				if(isThatItem(p2-3))
				{
					if(*p2=='=')
						p2++;
					p=doSubMenuJob(&ptcfgtop->mainitem, p2);
				}
			}
			if((p2=strstrInQuote(pp, STR_SUBMENU1)))
			{
				p=doSubMenuJob(&ptcfgtop->mainitem, p2);
			}
			else
				doItemJob(pp, &ptcfgtop->mainitem);
		}
	ANYWHERE: //执行完成一种数据类型之后,不再对这一行进行解析
		p=gotoQuoteEnd(p);
		if(!p)
			break;
		p++;
		while(*p)
		{
			if(*p=='{')
				break;
			if(*p<0xA) //
				break;
			if((*p>X_CHAR)&&(*p!=',')) //判断是这直接显示的字符
			{
				DATA_DRSTR *drstr=malloc(sizeof(DATA_DRSTR));
				char *p1=p;
				char *p2=gotoQuoteStart(p);
				if(!p2)
					break;
				p2--;
				while(*p2)
				{
					if(*p2>X_CHAR)
						break;
					p2--;
				}
				p2++;
				strnCopyWithEnd(drstr->str, p1, p2-p1);
				addItemToConfig(drstr, &ptcfgtop->mainitem, TYPE_DRSTR, 0, NULL);
				break;
			}
			p++;
		}
	}
	sortPatchConfigList();
END:
	return 1;
}

//释放一个submenu的所有项目
void freeSubMenuItem(PATCH_SUBMENU *subMenuItem)
{
	PATCH_ITEM *patchItem=subMenuItem->item;
	PATCH_ITEM *ptcItem;
	while(patchItem)
	{
		if(patchItem->itemData)
		{
			if(patchItem->itemType==TYPE_PRE)
			{
				PREPARE_DATA *preData=(PREPARE_DATA *)patchItem->itemData;
				PREPARE_ITEM *preItem=preData->prepareItem;
				PREPARE_ITEM *pItem;
				while(preItem)
				{
					pItem=preItem->next;
					mfree(preItem);
					preItem=pItem;
				}
			}
			else if(patchItem->itemType==TYPE_CBOX)
			{
				DATA_CBOX *cbox=(DATA_CBOX *)patchItem->itemData;
				CBOX_ITEM *cboxItem=cbox->cboxitem;
				CBOX_ITEM *cItem;
				while(cboxItem)
				{
					cItem=cboxItem->next;
					mfree(cboxItem);
					cboxItem=cItem;
				}
			}
			mfree(patchItem->itemData);
		}
		ptcItem=patchItem->next;
		mfree(patchItem);
		if(ptcItem)
			ptcItem->prev=0;
		else
			break;
		patchItem=ptcItem;
	}
}

//释放整个补丁
void freePatchItem(PATCH_SUBMENU *subMenuItem)
{
	PATCH_ITEM *patchItem=subMenuItem->item;
	PATCH_ITEM *ptcItem;
	while(patchItem)
	{
		if(patchItem->itemData)
		{
			if(patchItem->itemType==TYPE_PRE)
			{
				PREPARE_DATA *preData=(PREPARE_DATA *)patchItem->itemData;
				PREPARE_ITEM *preItem=preData->prepareItem;
				PREPARE_ITEM *pItem;
				while(preItem)
				{
					pItem=preItem->next;
					mfree(preItem);
					preItem=pItem;
				}
			}
			else if(patchItem->itemType==TYPE_CBOX)
			{
				DATA_CBOX *cbox=(DATA_CBOX *)patchItem->itemData;
				CBOX_ITEM *cboxItem=cbox->cboxitem;
				CBOX_ITEM *cItem;
				while(cboxItem)
				{
					cItem=cboxItem->next;
					mfree(cboxItem);
					cboxItem=cItem;
				}
			}
			else if(patchItem->itemType==TYPE_SUBMENU||patchItem->itemType==TYPE_TP)
			{
				PATCH_SUBMENU *subMenu=(PATCH_SUBMENU *)patchItem->itemData;
				freePatchItem(subMenu);
			}
			mfree(patchItem->itemData);
		}
		ptcItem=patchItem->next;
		mfree(patchItem);
		if(ptcItem)
			ptcItem->prev=0;
		else
			break;
		patchItem=ptcItem;
	}
}

//重新载入一个补丁配置(从config.txt)，并释放老的配置
void reloadThisPatch(PTC_CONFIG *ptcfg)
{
	if(loadConfig())
	{
		char *p;
		if(p=strstr(cfg_buf, ptcfg->patchInfo->patchName))
		{
			PTC_CONFIG *ptc_temp=ptcfgtop;
			PTC_CONFIG *ptc_config=malloc(sizeof(PTC_CONFIG));
			ptc_config->prev=ptcfg->prev;
			ptc_config->next=ptcfg->next;
			ptc_config->patchonoff=127; //all profile on, patch off 
			ptc_config->patchInfo=0;
			ptc_config->mainitem.smName[0]=0;
			ptc_config->mainitem.item=0;
			ptc_config->needSaveData=0;
			ptc_config->memory=0;
			ptc_config->offset=0;
			ptc_config->disableProfile=0;
			ptcfgtop=ptc_config;
			while(*p) //goto Start Pos, maybe '`',
			{
				if((*p==' ')||(*p=='`'))
					break;
				if((*p=='=')||(*p=='{'))
				{
					p++;
					break;
				}
				p--;
			}
			addToPatchInfo(p);
			readConfig(1, p); //reload
			ptcfgtop=ptc_temp;
			ptc_temp=ptcfg->prev;
			if(ptc_temp)
				ptc_temp->next=ptc_config;
			else //top
				ptcfgtop=ptc_config;
			ptc_temp=ptcfg->next;
			if(ptc_temp)
				ptc_temp->prev=ptc_config;
			if(ptcfg->patchInfo->info) //free info
				mfree(ptcfg->patchInfo->info);
			mfree(ptcfg->patchInfo);
			freePatchItem(&ptcfg->mainitem);
			mfree(ptcfg);
		}
	}
}

//交换两个补丁的位置
void swapPatchConfigList(PTC_CONFIG *p1, PTC_CONFIG *p2)
{
	PTC_CONFIG *p1n=p1->next;
	PTC_CONFIG *p1p=p1->prev;
	PTC_CONFIG *p2n=p2->next;
	PTC_CONFIG *p2p=p2->prev;
	PTC_CONFIG *temp=malloc(sizeof(PTC_CONFIG));
	memcpy(temp, p2, sizeof(PTC_CONFIG));
	memcpy(p2, p1, sizeof(PTC_CONFIG));
	memcpy(p1, temp, sizeof(PTC_CONFIG));
	if(p1p)
		p1p->next=p1;
	p1->prev=p1p;
	if(p1n)
		p1n->prev=p1;
	p1->next=p1n;
	if(p2n)
		p2n->prev=p2;
	p2->next=p2n;
	if(p2p)
		p2p->next=p2;
	p2->prev=p2p;
	mfree(temp);
}

//排序补丁，按照补丁名称
void sortPatchConfigList(void)
{
	PTC_CONFIG *ptcfg=ptcfgtop;
	PTC_CONFIG *pcfg;
	while(ptcfg)
	{
		pcfg=ptcfg->next;
		while(pcfg)
		{
			if(strncmpNoCase(ptcfg->patchInfo->patchName, pcfg->patchInfo->patchName, 128)>0)
			{
				swapPatchConfigList(ptcfg, pcfg);
			}
			pcfg=pcfg->next;
		}
		ptcfg=ptcfg->next;
	}
}

//释放所有补丁
void fuckThemAll(void)
{
	PTC_CONFIG *ptcfg=ptcfgtop;
	while(ptcfg)
	{
		if(ptcfg->patchInfo->info) //free info
			mfree(ptcfg->patchInfo->info);
		mfree(ptcfg->patchInfo);
		freePatchItem(&ptcfg->mainitem);
		ptcfgtop=ptcfg->next;
		mfree(ptcfg);
		if(ptcfgtop)
			ptcfgtop->prev=0;
		else
			break;
		ptcfg=ptcfgtop;
	}
}

//找到给定序号的补丁
PTC_CONFIG *getPatchConfigItem(int n)
{
	int i=0;
	PTC_CONFIG *ptcfg=ptcfgtop;
	while(ptcfg)
	{
		if(i==n)
			return ptcfg;
		ptcfg=ptcfg->next;
		i++;
	}
	return 0;
}

//给出所给选择项的最大条目
int getMaxCBoxItem(DATA_CBOX *cbox)
{
	CBOX_ITEM *cboxitem=cbox->cboxitem;
	int i=0;
	while(cboxitem)
	{
		cboxitem=cboxitem->next;
		i++;
	}
	return i;
}

//给出光标所指选择项
CBOX_ITEM *getCurCBoxItem(DATA_CBOX *cbox, int cur)
{
	CBOX_ITEM *cboxitem=cbox->cboxitem;
	int i=0;
	while(cboxitem)
	{
		if(i==cur)
			return cboxitem;
		cboxitem=cboxitem->next;
		i++;
	}
	return 0;
}

//给出初始选择项
CBOX_ITEM *getInitCBoxItem(DATA_CBOX *cbox, int *cur)
{
	CBOX_ITEM *cboxitem=cbox->cboxitem;
	int i=1; //选项是从1开始算的，0为标题
	*cur=i;
	while(cboxitem)
	{
		if(cboxitem->data == cbox->initData)
		{
			*cur=i;
			return cboxitem;
		}
		cboxitem=cboxitem->next;
		i++;
	}
	return 0;
}

//读取并初始化所有补丁配置
int getAllPatchData(void)
{
	PTC_CONFIG *ptcfg;
	if(!readConfig(0, 0))
		return 0;
	ptcfg=ptcfgtop;
	while(ptcfg)
	{
		initPatchConfig(ptcfg);
		ptcfg=ptcfg->next;
	}
	return 1;
}

//设置补丁开关
void setPatchOnOff(PTC_CONFIG *ptcfg, int n) //0-6, profile, 7 patch
{
	if(!ptcfg)
		return;
	if(getPatchOnOff(ptcfg, n))
	{
		ptcfg->patchonoff=(ptcfg->patchonoff)&(~(1<<n));
	}
	else
	{
		ptcfg->patchonoff=(ptcfg->patchonoff)|(1<<n);
	}
}

//读取补丁开关状态
int getPatchOnOff(PTC_CONFIG *ptcfg, int n) //0-6 profile, 7 patch on/off
{
	unsigned char c=ptcfg->patchonoff;
	if(n>7||n<0)
		return 0;
	c=c>>n;
	return (c&1);
}

//检查ptc所对应的补丁是否存在
int isPatchExistedByID(char *patchID)
{
	PTC_CONFIG *ptcfg=ptcfgtop;
	while(ptcfg)
	{
		if(!strncmpNoCase(ptcfg->patchInfo->patchID, patchID, 16))
			return 1;
		ptcfg=ptcfg->next;
	}
	return 0;
}

#ifdef	WINTEL_DEBUG

void showSubMenuItem(PATCH_SUBMENU *subMenuItem)
{
	PATCH_ITEM *patchItem=subMenuItem->item;
	if(subMenuItem->smName[0])
		printf("\nSubMenu: %s\n", subMenuItem->smName);
	while(patchItem)
	{
		if(patchItem->itemName[0])
			printf("ItemName: %s\n", patchItem->itemName);
		if(patchItem->bytePos)
			printf("bytePos: %d\n", patchItem->bytePos);
		switch(patchItem->itemType)
		{
		case TYPE_SUBMENU:
		case TYPE_TP:
			showSubMenuItem((PATCH_SUBMENU *)patchItem->itemData);
			break;
		case TYPE_PRE:
			{
				PREPARE_DATA *preData=(PREPARE_DATA *)patchItem->itemData;
				if(preData)
				{
					PREPARE_ITEM *preItem=preData->prepareItem;
					printf("\nprepareItem: %s\n", preData->useAs);
					while(preItem)
					{
						printf("data: %d\n", preItem->data);
						printf("name: %s\n", preItem->itemName);
						preItem=preItem->next;
					}
				}
				break;
			}
		case TYPE_CHECKBOX:
			{
				DATA_CHECKBOX *chkbox=(DATA_CHECKBOX *)patchItem->itemData;
				if(chkbox)
				{
					printf("ON/OFF: %d\n", chkbox->onoff);
					printf("bitPos: %d\n", chkbox->bitPos);
				}
				break;
			}
		case TYPE_POS:
			{
				DATA_POS *pos=(DATA_POS *)patchItem->itemData;
				if(pos)
				{
					if(pos->off)
						printf("POS is OFF");
					printf("X: %d\n", pos->x);
					printf("Y: %d\n", pos->y);
					printf("W: %d\n", pos->w);
					printf("H: %d\n", pos->h);
				}
				break;
			}
		case TYPE_BYTE:
			{
				DATA_BYTE *dbyte=(DATA_BYTE *)patchItem->itemData;
				if(dbyte)
				{
					printf("initData: %d\n", dbyte->initData);
					printf("min: %d\n", dbyte->min);
					printf("max: %d\n", dbyte->max);
				}
				break;
			}
		case TYPE_INT:
			{
				DATA_INT *dint=(DATA_INT *)patchItem->itemData;
				if(dint)
				{
					printf("initData: %d\n", dint->initData);
					printf("min: %d\n", dint->min);
					printf("max: %d\n", dint->max);
				}
				break;
			}
		case TYPE_CBOX:
			{
				DATA_CBOX *cbox=(DATA_CBOX *)patchItem->itemData;
				if(cbox)
				{
					CBOX_ITEM *citem=cbox->cboxitem;
					printf("initData: %d\n", cbox->initData);
					while(citem)
					{
						printf("cbName: %s\n", citem->name);
						printf("cbData: %d\n", citem->data);
						citem=citem->next;
					}
				}
				break;
			}
		case TYPE_DRSTR:
			{
				DATA_DRSTR *dstr=(DATA_DRSTR *)patchItem->itemData;
				if(dstr)
					printf("DirectString: %s\n", dstr->str);
				break;
			}
		case TYPE_COLOR:
			{
				DATA_COLOR *color=(DATA_COLOR *)patchItem->itemData;
				if(color)
					printf("Color: %08X\n", *(int *)color->color);
				break;
			}
		case TYPE_ADDRESS:
			{
				DATA_ADDRESS *addr=(DATA_ADDRESS *)patchItem->itemData;
				if(addr)
					printf("Addr: %X\n", addr->addr);
				break;
			}
		case TYPE_STRING:
			{
				DATA_STRING *str=(DATA_STRING *)patchItem->itemData;
				if(str)
				{
					printf("String: %s\n", str->string);
					printf("MaxLen: %d\n", str->maxlen);
				}
				break;
			}
		case TYPE_UNICODE:
			{
				DATA_UNICODE *uni=(DATA_UNICODE *)patchItem->itemData;
				if(uni)
				{
					printf("UniStr: %s\n", uni->ustr);
					printf("MaxLen: %d\n", uni->maxlen);
				}
				break;
			}
		case TYPE_HEX:
			{
				DATA_HEX *hex=(DATA_HEX *)patchItem->itemData;
				if(hex)
				{
					unsigned char *s=hex->hex;
					int i=0;
					int max=(hex->maxlen?hex->maxlen:1);
					printf("HexData:");
					for(;i<max;i++)
					{
						printf(PERCENT_02X, s[i]);
					}
					printf("\nMaxLen: %d\n", hex->maxlen);
				}
				break;
			}
		case TYPE_SF:
			{
				DATA_SF *fs=(DATA_SF *)patchItem->itemData;
				printf("FilePath: %s\n", fs->path);
				printf("Mask: %s\n", fs->mask);
				printf("Maxlen: %d\n", fs->maxlen);
				break;
			}
		case TYPE_SL:
			{
				DATA_SL *sl=(DATA_SL *)patchItem->itemData;
				if(sl)
				{
					printf("initData: %d\n", sl->initData);
					printf("min: %d\n", sl->min);
					printf("max: %d\n", sl->max);
				}
				break;
			}
		case TYPE_MS:
			{
				DATA_MS *ms=(DATA_MS *)patchItem->itemData;
				if(ms)
				{
					printf("ms: %d\n", ms->ms);
				}
				break;
			}
		case TYPE_POSB:
			{
				DATA_POS *pos=(DATA_POS *)patchItem->itemData;
				if(pos)
				{
					if(pos->off)
						printf("POS IS OFF");
					printf("X: %d\n", pos->x);
					printf("Y: %d\n", pos->y);
					printf("W: %d\n", pos->w);
					printf("H: %d\n", pos->h);
				}
				break;
			}
		case TYPE_BYTES:
			{
				DATA_BYTES *dbytes=(DATA_BYTES *)patchItem->itemData;
				if(dbytes)
				{
					int i=1;
					printf("type: Bytes\nDATA:\n%d", dbytes->bytes[0]);
					for(;i<dbytes->len;i++)
						printf(",%d",dbytes->bytes[i]);
					printf("\n");
				}
				break;
			}
		case TYPE_INTS:
			{
				DATA_INTS *dints=(DATA_INTS *)patchItem->itemData;
				if(dints)
				{
					int i=1;
					printf("type: Ints\nDATA:\n%d", dints->ints[0]);
					for(;i<dints->len;i++)
						printf(",%d",dints->ints[i]);
					printf("\n");
				}
				break;
			}
		case TYPE_CONST:
			{
				DATA_CONST *dconst=(DATA_CONST *)patchItem->itemData;
				if(dconst)
				{
					printf("Const: %d\n", dconst->data);
					printf("Const, LEN: %d\n", dconst->len);
				}
				break;
			}
		}
		patchItem=patchItem->next;
	}
}
int main(void)
{
	PTC_CONFIG *ptcfg;
	getAllPatchData();
	ptcfg=ptcfgtop;
	while(ptcfg)
	{
		printf("\nname: %s\n", ptcfg->patchInfo->patchName);
		printf("author: %s\n", ptcfg->patchInfo->author);
		printf("Ver: %s\n", ptcfg->patchInfo->version);
		if(ptcfg->patchInfo->info)
			printf("Info: %s\n", ptcfg->patchInfo->info);
		printf("ID: %s\n", ptcfg->patchInfo->patchID);
		if(ptcfg->mainitem.item)
			showSubMenuItem(&ptcfg->mainitem);
		savePatchConfig(ptcfg);
		ptcfg=ptcfg->next;
	}
	fuckThemAll();
	return 0;
}
#endif

