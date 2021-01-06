#ifndef __RCEmaps_h__
#define __RCEmaps_h__

/* Copyright (c) Dmitry Kaldin aka Zeus, 2009. */

/* This program is freely distributable without licensing fees and is
provided without guarantee or warrantee expressed or  implied. This
program is -not- in the public domain. */

extern const int DispW,DispH,DispX,DispY;
extern double posX,posY;
extern int *spriteOrder;//array used to sort the sprites
extern double *spriteDistance;//array used to sort the sprites
extern int ChangeMap;

typedef struct
{
	char signature[12];//версия карты
	char reserved1[4];
	short mapWidth;//размер карты
	short mapHeight;//размер карты
	short posX;//стартовая позиция игрока
	short posY;//стартовая позиция игрока
	short objNum;//количество текстур
	unsigned short upColor;
	unsigned short dwnColor;
	char reserved2[2];
}MAPHDR;
typedef struct
{
	char signature[16];
	char reserved1[4];
	char w;
	char h;
	char type;
	char reserved2[9];
}GPFHDR;
typedef struct
{
	char *name;
	char type;
	char *miscbytes;
	char w;
	char h;
	unsigned short *bitmap;
}Object;
typedef struct
{
	double posx;
	double posy;
	int tex;
}Sprite;
typedef struct
{
	Sprite *pointerSprite;
	char type;
	int speed;
	int olddeltax;
	int olddeltay;
	double oldposx;
	double oldposy;
	double newposx;
	double newposy;
}NPC;

MAPHDR CurrentMap;
char *worldMap;
Object *Objects;
Sprite *Sprites;
NPC *NPCs;
int texNum, sprNum, npcNum;

void DestroyMap (void)
{
	for (short i=0;i<CurrentMap.objNum;i++)
	{
		if (Objects[i].name) mfree(Objects[i].name);
		if (Objects[i].bitmap) mfree(Objects[i].bitmap);
		if (Objects[i].miscbytes) mfree(Objects[i].miscbytes);
	}
	if (npcNum) mfree(NPCs);
	if (sprNum)
        {
          if (spriteOrder) mfree(spriteOrder);
	  if (spriteDistance) mfree(spriteDistance);
          if (Sprites) mfree(Sprites);
        }
	if (Objects) mfree(Objects);
	if (worldMap) mfree(worldMap);
}

int InitMap(char *fname)   //Функция загрузки карт, текстур и объектов
{
	//DestroyMap();
  unsigned int err;
	int handle;
	if (fname) handle=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err); else return 0;
	if (handle!=-1) //-1 = error 
	{
		int io=fread(handle,&CurrentMap,sizeof(MAPHDR),&err);// Возвращает число прочитанных байт и ошибку в err 
		int error=0;
		if (strcmp(CurrentMap.signature,"3DElfMapV04"))
		{
			ShowMSG(1,(int)"Неизвестный формат карты!");
			return 0;
		}
		texNum=0,sprNum=0,npcNum=0,ChangeMap=0;
		worldMap=malloc(CurrentMap.mapWidth*CurrentMap.mapHeight);
		posX=CurrentMap.posX;
		posY=CurrentMap.posY;
		
		Objects=malloc(CurrentMap.objNum*sizeof(Object));
		
		for (short i=0;i<CurrentMap.objNum;i++)
		{
			io=fread(handle,&Objects[i].type,1,&err);
			//добываем имя объекта
			char byte;
			io=fread(handle,&byte,1,&err);
			
			char *tmp=malloc(byte+1);
			io=fread(handle,tmp,byte,&err);
			tmp[byte]=0;
			
			char filename[256];
			strcpy(filename, fname);
			strcpy(strrchr(filename,'\\'),0x00);
			strcpy(strrchr(filename,'\\')+1,tmp);
			mfree(tmp);
			
			Objects[i].name=malloc(strlen(filename));
			strcpy(Objects[i].name, filename);
			
			/*char c[64];
			sprintf(c,"%i",strlen(filename));
			ShowMSG(1,(int)c);*/
			char misclen;
			io=fread(handle,&misclen,1,&err);
			if (misclen) 
			{
				Objects[i].miscbytes=malloc(misclen);
				io=fread(handle,Objects[i].miscbytes,misclen,&err);
			}
			else Objects[i].miscbytes=malloc(1);
			
			if (Objects[i].type==0x01 || Objects[i].type==0x02 || Objects[i].type==0x04)
			{
				int grapfFile=fopen(Objects[i].name,A_ReadOnly+A_BIN,P_READ,&err);
				if (grapfFile!=-1) //-1 = error 
				{
					GPFHDR picHDR;
					io=fread(grapfFile,&picHDR,sizeof(picHDR),&err);
					Objects[i].w=picHDR.w;
					Objects[i].h=picHDR.h;
					Objects[i].bitmap=malloc(2*picHDR.w*picHDR.h);
					if (picHDR.type > 0) io=fread(grapfFile,Objects[i].bitmap,2*picHDR.w*picHDR.h,&err);
					fclose(grapfFile,&err);
				}
				else
				{
					Objects[i].w=16;
					Objects[i].h=16;
					Objects[i].bitmap=malloc(2*16*16);
					zeromem(Objects[i].bitmap,2*16*16);
					error++;
				}
				if (Objects[i].type==0x01) texNum++;
			}
			if (Objects[i].type==0x03)
			{
				Objects[i].bitmap=malloc(1);
			}
			//DrawRoundedFrame(DispX,DispY+10,DispW*i/(CurrentMap.objNum-1)-1,DispY+30,0,0,0,GetPaletteAdrByColorIndex(23),GetPaletteAdrByColorIndex(4));REDRAW();
		}
		io=fread(handle,worldMap,CurrentMap.mapWidth*CurrentMap.mapHeight,&err);
		fclose(handle,&err);
		
		for (short i=0;i<CurrentMap.mapWidth;i++)
		{
			for (short j=0;j<CurrentMap.mapHeight;j++)
			{
				int pos=worldMap[i+CurrentMap.mapWidth*j];
				if (pos > 0)
				{
					if (Objects[pos-1].type==0x02 || Objects[pos-1].type==0x04) sprNum++; //подсчёт спрайтов
					if (Objects[pos-1].type==0x04) npcNum++;  //подсчёт ботов
				}
			}
			//DrawRoundedFrame(DispX,DispY+10,DispW*i/(mapWidth-1)-1,DispY+30,0,0,0,GetPaletteAdrByColorIndex(23),GetPaletteAdrByColorIndex(5));REDRAW();
		}
		if (sprNum>0) Sprites=malloc(sprNum*sizeof(Sprite));
		if (npcNum>0) NPCs=malloc(npcNum*sizeof(NPC));
		int cnt1=0, cnt2=0;
		for (short i=0;i<CurrentMap.mapWidth;i++)
		{
			for (short j=0;j<CurrentMap.mapHeight;j++)
			{
				int pos=worldMap[i+CurrentMap.mapWidth*j];
				if (pos > 0)
				{
					if (Objects[pos-1].type==0x02 || Objects[pos-1].type==0x04) {Sprites[cnt1].posx=i+0.5; Sprites[cnt1].posy=j+0.5; Sprites[cnt1].tex=pos-1; cnt1++;}//заполнение спрайтов
					if (Objects[pos-1].type==0x04)  //заполнение ботов
					{
						NPCs[cnt2].pointerSprite=&Sprites[cnt1-1];
						NPCs[cnt2].newposx=NPCs[cnt2].pointerSprite->posx;
						NPCs[cnt2].newposy=NPCs[cnt2].pointerSprite->posy;
						NPCs[cnt2].olddeltax=1;
						NPCs[cnt2].olddeltay=0;
						NPCs[cnt2].speed=Objects[pos-1].miscbytes[0];//ai speed
						NPCs[cnt2].type=Objects[pos-1].miscbytes[4];//ai type of movement
						cnt2++;
					}
				}
			}
			//DrawRoundedFrame(DispX,DispY+10,DispW*i/(mapWidth-1)-1,DispY+30,0,0,0,GetPaletteAdrByColorIndex(23),GetPaletteAdrByColorIndex(6));REDRAW();
		}
		if (sprNum>0) spriteOrder=malloc(sprNum*sizeof(int));
		if (sprNum>0) spriteDistance=malloc(sprNum*sizeof(double));
		if (error)
		{
			char c[128];
			sprintf(c,"Не найдено %i объетов",error);
			ShowMSG(1,(int)c);
		}
		return 1;
        }
		else return 0;
}

#endif					/* __RCEmaps_h__ */
