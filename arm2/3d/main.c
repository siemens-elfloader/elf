#include <math.h>
#include "../inc/swilib.h"
#include "rect_patcher.h"
#include "RCEmaps.h"

extern void kill_data(void *p, void (*func_p)(void *));//This function kill ELF and free memory

//Config
extern void InitConfig();
const int DispX=0, DispY=0;
const int DispW=240,DispH=320;
extern const int Render_Sprites, Render_Floor, Show_FPS;
extern const int dTime1, dTime2;

#ifdef ELKA
#define defFONT  9
WSHDR* ttt = 0;
unsigned int* lcd_ptr;
LCDLAYER *ovr_layer_ptr;
#else
#define defFONT  2
#endif
const int timer_speed=5;



const int minus11=-11;
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

typedef struct
{
	CSM_RAM csm;
	int gui_id;
}MAIN_CSM;

typedef struct
{
	GUI gui;
}MAIN_GUI;

//for screenArray
IMGHDR *img;
unsigned short *screen;
int screensize;
RECT rc;
DRWOBJ drwobj;

//for sprites
double *ZBuffer;//1D Zbuffer
int *spriteOrder;//array used to sort the sprites
double *spriteDistance;//array used to sort the sprites
void combSort(int* order, double* dist, int amount);//function used to sort the sprites

//RCengine's things
double posX, posY;  //x and y start position
double dirX = -1, dirY = 0; //initial direction vector
double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
double moveSpeed, rotSpeed;

int running=0, DoWork=0, Active=0, ChangeMap=0;
int right=0,left=0,up=0,down=0;
int iFps=0, cFps = 0;
TDate date; TTime time;
int lastTime=0, thisTime=0;
GBSTMR timer;
WSHDR *wsn;

void Calculate(void);
void AIprocessing(void);

#pragma optimize=no_code_motion
int NPCrandom(void)
{
	int rnd=-1;
	GetDateTime(&date,&time);
	srand(time.sec);
	return pow(rnd, rand()%10);
}

void OnRedraw(MAIN_GUI *data)//эта функция нужна для перерисовки экрана
{ 
	if (DoWork) 
	{
		AIprocessing();
		Calculate();
#ifdef ELKA
		if (!Show_FPS)
		{
			unsigned short *rsb =  RamScreenBuffer();
			memcpy (rsb,screen,screensize);
			DrawObject2Layer(ovr_layer_ptr,&drwobj);
			UpdateDisplayByLayerPtr(ovr_layer_ptr);//draw screenArray
		}
		else DrawObject(&drwobj);  //Standart method
#else
		DrawObject(&drwobj);//draw screenArray
#endif
		if (!Render_Floor) zeromem(screen,screensize);//clear screenArray
		if (ChangeMap)
		{
			wsprintf(wsn,"To change map press Green Button");
			DrawString(wsn,DispX,DispY,DispW-1,DispH-1,defFONT,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
		}
		if (Show_FPS)
		{
			GetDateTime(&date,&time); thisTime = time.sec;
			if (lastTime!=thisTime) {cFps = iFps; iFps=0; lastTime=thisTime;} else iFps++;
			wsprintf(wsn," %i",cFps);
			DrawString(wsn,DispX,DispY+16,DispW-1,DispH-1,defFONT,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(24));
		}
		if (Active) GBS_StartTimerProc(&timer,timer_speed,OnRedraw);
	}
}
void AIprocessing(void)
{
  	//NPC processing
	for (int z=0; z<npcNum; z++)
	{
		int deltax, deltay;
		if (NPCs[z].type==1) {deltax=NPCs[z].olddeltax; deltay=NPCs[z].olddeltay;} else {if (NPCrandom()<0)deltax=0; else deltax=NPCrandom(); if (NPCrandom()>0)deltay=0; else deltay=NPCrandom();} //начальное направление движения NPC
		
		if (fabs(NPCs[z].pointerSprite->posx - NPCs[z].newposx)<0.1 && fabs(NPCs[z].pointerSprite->posy - NPCs[z].newposy)<0.1)
		{
			char hit=0;
			int pos;
			while (hit == 0)
			{
				
				pos=worldMap[(int)NPCs[z].pointerSprite->posx + deltax + ((int)NPCs[z].pointerSprite->posy + deltay) * CurrentMap.mapWidth];
				if (pos==0) {hit=1; break;}
				else if (deltay==0) {deltax=0; deltay=NPCrandom();}
				else if (deltax==0) {deltax=NPCrandom(); deltay=0;}
				else 
				{
					wsprintf(wsn,"NPC can't find the way to move!");
					DrawString(wsn,DispX,DispY,DispW-1,DispH-1,defFONT,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
					hit=1; deltax=0; deltay=0; break;
				}
			}
			if (hit==1)
			{
				NPCs[z].oldposx=NPCs[z].newposx;
				NPCs[z].oldposy=NPCs[z].newposy;
				
				NPCs[z].newposx+=deltax;
				NPCs[z].newposy+=deltay;
			}
			NPCs[z].olddeltax=deltax;
			NPCs[z].olddeltay=deltay;
		}
		else
		{
			NPCs[z].pointerSprite->posx+=(NPCs[z].newposx-NPCs[z].oldposx)*dTime2*NPCs[z].speed/100;
			NPCs[z].pointerSprite->posy+=(NPCs[z].newposy-NPCs[z].oldposy)*dTime2*NPCs[z].speed/100;
			if (fabs(NPCs[z].pointerSprite->posx - NPCs[z].newposx)<0.01 && fabs(NPCs[z].pointerSprite->posy - NPCs[z].newposy)<0.01)
			{
				NPCs[z].newposx=NPCs[z].pointerSprite->posx;
				NPCs[z].newposy=NPCs[z].pointerSprite->posy;
				
				int tmp=worldMap[(int)NPCs[z].oldposx + (int)NPCs[z].oldposy * CurrentMap.mapWidth];
				worldMap[(int)NPCs[z].oldposx + (int)NPCs[z].oldposy * CurrentMap.mapWidth]=worldMap[(int)NPCs[z].newposx + (int)NPCs[z].newposy * CurrentMap.mapWidth];
				worldMap[(int)NPCs[z].newposx + (int)NPCs[z].newposy * CurrentMap.mapWidth]=tmp;
			}
		}
	}
}
void Calculate()
{
	if(up)
	{
		int NposX=worldMap[(int)(posX + dirX * moveSpeed)+CurrentMap.mapWidth*(int)posY];
		int NposY=worldMap[(int)posX+CurrentMap.mapWidth*(int)(posY + dirY * moveSpeed)];
		if (NposX == 0 || Objects[NposX-1].type==0x03) posX += dirX * moveSpeed;
		if (NposY == 0 || Objects[NposY-1].type==0x03) posY += dirY * moveSpeed;
		if (Objects[NposY-1].type==0x03) ChangeMap=NposY-1; else ChangeMap=0;
	}
	if(down)
	{
		int NposX=worldMap[(int)(posX - dirX * moveSpeed)+CurrentMap.mapWidth*(int)posY];
		int NposY=worldMap[(int)posX+CurrentMap.mapWidth*(int)(posY - dirY * moveSpeed)];
		if (NposX == 0 || Objects[NposX-1].type==0x03) posX -= dirX * moveSpeed;
		if (NposY == 0 || Objects[NposY-1].type==0x03) posY -= dirY * moveSpeed;
		if (Objects[NposY-1].type==0x03) ChangeMap=NposY-1; else ChangeMap=0;
	}
	
	if(right)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	if(left)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}
	if(up||left||down||right)
	for(int x = 0; x < DispW; x++)  //calculate ray position and direction
	{
		double cameraX =  (x + x) / (double)DispW - 1 ; //x-coordinate in camera space
		double rayPosX = posX;
		double rayPosY = posY;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//which box of the map we're in
		int mapX = rayPosX;
		int mapY = rayPosY;
		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		double perpWallDist;
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX,stepY;
		int hit = 0; //was there a wall hit?
		int side = 0; //was a NS or a EW wall hit?
		//length of ray from current position to next x or y-side
		double sideDistX, sideDistY;
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (rayPosX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1 - rayPosX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (rayPosY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1 - rayPosY) * deltaDistY;
		}
		//perform DDA
		int pos;
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			pos=worldMap[mapX+CurrentMap.mapWidth*mapY];
			if (pos > 0 && Objects[pos-1].type==0x01) hit = 1;
		}
		//Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
		else
			perpWallDist = fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);
		//Calculate height of line to draw on screen
		int lineHeight = fabs(DispH / perpWallDist);
		//calculate lowest and highest pixel to fill in current stripe
		int optim1=lineHeight / 1.5;
		int optim2=DispH / 2;
		int drawStartY = -optim1 + optim2;
		int drawEndY = optim1 + optim2;
		int shiftY=0;//для того, чтобы при приближении к стене текстуры правильно скалировалась вертикально
		int drawHeight=drawEndY-drawStartY;
		if(drawStartY < 0){shiftY=-drawStartY; drawStartY = 0;}
		if(drawEndY > DispH) drawEndY = DispH;
		//choose wall texture
		int img;
		if (Objects[pos-1].type!=0x01) img=0; else img = pos-1;
		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 1) wallX = rayPosX + ((mapY - rayPosY + (1 - stepY) / 2) / rayDirY) * rayDirX;
		else wallX = rayPosY + ((mapX - rayPosX + (1 - stepX) / 2) / rayDirX) * rayDirY;
		wallX -= floor(wallX);

//if(side == 0 && rayDirX > 0) wallX=1.0-wallX; else if(side == 1 && rayDirY < 0) wallX=1.0-wallX;

		//x coordinate on the texture
		int texX = wallX * Objects[img].w;
		if(side == 0 && rayDirX > 0) texX = Objects[img].w - texX - 1; 
		else
			if(side == 1 && rayDirY < 0) texX = Objects[img].w - texX - 1;
			//draw the pixels of the stripe as a vertical line
			for(int y=drawStartY;y<drawEndY;y++) 
			{
  				//int texX=wallX * Objects[img].w;
                                int texY=(Objects[img].h)*(y-drawStartY+shiftY)/drawHeight;                        
				screen[x+y*DispW]=Objects[img].bitmap[texX + Objects[img].w*texY];  //modify screenArray                        
			}
			///////////////////SET THE ZBUFFER FOR THE SPRITE CASTING///////
			ZBuffer[x] = perpWallDist; //perpendicular distance is used
			
			///////////////////FLOOR CASTING////////////////////////////////
			if (Render_Floor)
			{
				for(int y=DispX;y<drawStartY;y++) 
				{
					screen[x+y*DispW]=CurrentMap.upColor;//draw floor
					//memset(screen, CurrentMap.upColor, sizeof());
				}
				for(int y=drawEndY;y<DispH;y++) 
				{
					screen[x+y*DispW]=CurrentMap.dwnColor;//draw ceiling
				}
			}
			
			///////////////END FLOOR CASTING////////////////////////////////
	}
	if(up||left||down||right)
	if (Render_Sprites)///////////////SPRITE CASTING////////////////////////
	{
		//sort sprites from far to close
		for(int i = 0; i < sprNum; i++)
		{
			spriteOrder[i] = i;
			spriteDistance[i] = (posX - Sprites[i].posx) * (posX - Sprites[i].posx) + (posY - Sprites[i].posy) * (posY - Sprites[i].posy); //sqrt not taken, unneeded
		}
		combSort(spriteOrder, spriteDistance, sprNum);
		//after sorting the sprites, do the projection and draw them
		for(int i = 0; i < sprNum; i++)
		{
			//translate sprite position to relative to camera
			double spriteX = Sprites[spriteOrder[i]].posx - posX;
			double spriteY = Sprites[spriteOrder[i]].posy - posY;
			//transform sprite with the inverse camera matrix
			double invDet = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication
			double transformX = invDet * (dirY * spriteX - dirX * spriteY);
			double transformY = invDet * (-planeY * spriteX + planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D       
			int spriteScreenX = (DispW / 2) * (1 + transformX / transformY);
			//calculate height of the sprite on screen
			int spriteHeight = fabs(DispH /transformY); //using "transformY" instead of the real distance prevents fisheye
			//calculate lowest and highest pixel to fill in current stripe
			int drawStartY = -spriteHeight / 2 + DispH / 2 ;
			int drawEndY = spriteHeight / 2 + DispH / 2 ;
			int drawHeight=drawEndY-drawStartY;
			int shiftY=0;
			if(drawStartY < 0) {shiftY=-drawStartY; drawStartY = 0;}
			if(drawEndY > DispH) drawEndY = DispH ;
			//calculate width of the sprite
			int spriteWidth = spriteHeight;
			int drawStartX = -spriteWidth / 2 + spriteScreenX;
			int drawEndX = spriteWidth / 2 + spriteScreenX;
			int drawWidth=drawEndX-drawStartX;
			int shiftX=0;
			if(drawStartX < 0) {shiftX=-drawStartX; drawStartX = 0;}
			if(drawEndX > DispW) drawEndX = DispW;
			//loop through every vertical stripe of the sprite on screen
			for(int x = drawStartX; x < drawEndX; x++)
			{
				if(transformY > 0 && x > 0 && x < DispW && transformY < ZBuffer[x]) 
				{	
					int texX=(Objects[Sprites[spriteOrder[i]].tex].w) * (x-drawStartX+shiftX)/drawWidth;
					
					for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
					{
						int texY=(Objects[Sprites[spriteOrder[i]].tex].h) * (y-drawStartY+shiftY)/drawHeight;
						unsigned short pixel=Objects[Sprites[spriteOrder[i]].tex].bitmap[Objects[Sprites[spriteOrder[i]].tex].w * texY + texX];
						if (pixel!=57344) screen[x+y*DispW]=pixel;  //modify screenArray
					}
				}
			}
		}
	}
}

void combSort(int* order, double* dist, int amount) //sort algorithm
{
	int gap = amount;
	char swapped = 0;
	while(gap > 1 || swapped)
	{
		//shrink factor 1.3
		gap = (gap * 10) / 13;
		if(gap == 9 || gap == 10) gap = 11;
		if (gap < 1) gap = 1;
		swapped = 0;
		for (int i = 0; i < amount - gap; i++)
		{
			int j = i + gap;
			if (dist[i] < dist[j])
			{
				double tmp1=dist[i];
				dist[i]=dist[j];
				dist[j]=tmp1;
				int tmp2=order[i];
				order[i]=order[j];
				order[j]=tmp2;
				swapped = 1;
			}
		}
	}
}
void InitScreen(void)
{
	//for screen Array
	img=malloc(sizeof(IMGHDR));
	img->w=DispW;
	img->h=DispH;
	screensize=DispW*DispH*2;
	img->bpnum=0x8;
	img->bitmap=malloc(screensize);
	screen=(unsigned short *)img->bitmap;
	StoreXYWHtoRECT(&rc,DispX,DispY,DispW,DispH);
	
	ZBuffer=malloc(DispW*sizeof(double));
#ifdef ELKA
	if (!Show_FPS)
	{
		SetPropTo_Obj1(&drwobj,&rc,0,ttt,8,0);
		unsigned int* ovr_ptr = (unsigned int*)Ram_LCD_Overlay_Layer();
	}
	else SetPropTo_Obj5(&drwobj,&rc,0,img);//for screen Array
#else
	SetPropTo_Obj5(&drwobj,&rc,0,img);//for screen Array
#endif
}
void DestroyScreen(void)
{
	if (img->bitmap) mfree(img->bitmap);
	if (img) mfree(img);
	if (ZBuffer) mfree(ZBuffer);
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
    #ifdef ELKA//Если елка,то отключаем иконбар
  DisableIconBar(1);
  #endif
	data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
	running=0;
	GBS_DelTimer(&timer);
	data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Если гуи на верху то опять же делаем что нужно
{
	Active=1;
	data->gui.state=2;
#ifdef ELKA
	DisableIconBar(1);//Если елка,то отключаем иконбар
#endif
	DisableIDLETMR();//отключаем таймер,иначе через 2 минуты эльф закроется
}
void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))//а если гуи не вверху,то можно закрыть эльф например:)
{
	Active=0;
	if (data->gui.state!=2) return;
	data->gui.state=1;
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
	if (!DoWork) return(1);  
	if (msg->gbsmsg->msg==KEY_DOWN)
	{
		switch(msg->gbsmsg->submess)
		{
		case UP_BUTTON:    case '2':up=1; break;
		case DOWN_BUTTON:  case '8':down=1; break;
		case RIGHT_BUTTON: case '6':right=1; break;
		case LEFT_BUTTON:  case '4':left=1; break;
		case ENTER_BUTTON: case '5':
			{
				extern const char *successed_config_filename;                          
				WSHDR *ws;
				ws=AllocWS(150);
				str_2ws(ws,successed_config_filename,128);
				ExecuteFile(ws,0,0);
				FreeWS(ws);
				break;
			}
		case GREEN_BUTTON:  {if (ChangeMap) {char Mname[256]; strcpy (Mname, Objects[ChangeMap].name); DestroyMap(); InitMap(Mname);} break;}
		case RIGHT_SOFT:   case RED_BUTTON: {DoWork=0; break;}
		}
		}
	if (msg->gbsmsg->msg==KEY_UP)
	{
		switch(msg->gbsmsg->submess)
		{
		case UP_BUTTON:    case '2':{up=0;break;}
		case DOWN_BUTTON:  case '8':{down=0;break;}
		case RIGHT_BUTTON: case '6':{right=0;break;}
		case LEFT_BUTTON:  case '4':{left=0;break;}
		}
	}
	
	return 0; 
}

const void * const gui_methods[11]=
{
	(void *)OnRedraw,
		(void *)onCreate,
		(void *)onClose,
		(void *)onFocus,
		(void *)onUnfocus,
		(void *)OnKey,
		0,
		(void *)kill_data,
		0
};

void maincsm_oncreate(CSM_RAM *data)//Вызывается при открытии эльфа,делаем что нужно
{
	//тут хитрые махинации для получения ид гуя чтобы мона было с ним манипулировать
	MAIN_CSM *csm=(MAIN_CSM*)data;
	MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
	zeromem(main_gui,sizeof(MAIN_GUI));
	const RECT Canvas={0,0,0,0};
	patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
	main_gui->gui.canvas=(void *)(&Canvas);
	main_gui->gui.flag30=2;
	main_gui->gui.methods=(void *)gui_methods;
	main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
	csm->csm.state=0;
	csm->csm.unk1=0;
	csm->gui_id=CreateGUI(main_gui);
}

void ElfKiller(void)//освобождаем все занятое место эльфом в оперативе
{
	extern void *ELF_BEGIN;
	kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)//функция закрытия эльфа,тут освобождаем память если нужно и т.п.
{
	running=0;
	DestroyScreen();
	DestroyMap();
	FreeWS(wsn);
#ifdef ELKA
	FreeWS(ttt);
	ttt=0;
#endif
	SUBPROC((void *)ElfKiller);
}

#pragma inline=forced
int toupper(int c)
{
	if ((c>='a')&&(c<='z')) c+='A'-'a';
	return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
	int i;
	int c;
	while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
	return(i);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)//тут вообщем протекают все сообщения поступаемые из эльфа так сказать:)
{
	//сообщение о реконфигурации например,ипц и т.д. и т.п.
	MAIN_CSM *csm=(MAIN_CSM*)data;
	if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
	{
		csm->csm.state=-3;
	}
	if (msg->msg==MSG_RECONFIGURE_REQ)//Елси была реконфигурация,то обновляем настройки эльфа
	{
		extern const char *successed_config_filename;
		if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
		{
			ShowMSG(1,(int)"Конфиг обновлен!");
			InitConfig();
			moveSpeed = (((double)dTime1)/1000) * 5.0; //the constant value is in squares/second
			rotSpeed = (((double)dTime1)/1000) * 3.0; //the constant value is in radians/second
			DestroyScreen();
			InitScreen();
			DrawRoundedFrame(0,0,DispW-1,DispH-1,0,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(0));
		}
	}
	return 1;
}

const struct//это структура цсм,разбираться не надо:)
{
	CSM_DESC maincsm;
	WSHDR maincsm_name;
}MAINCSM =
{
	{
		maincsm_onmessage,
			maincsm_oncreate,
#ifdef NEWSGOLD
			0,
			0,
			0,
			0,
#endif
			maincsm_onclose,
			sizeof(MAIN_CSM),
			1,
			&minus11
	},
	{
			maincsm_name_body,
				NAMECSM_MAGIC1,
				NAMECSM_MAGIC2,
				0x0,
				139
		}
};

int main(char *exename, char *fname)//exename-путь запускаемого эльфа, fname параметр передаваемый эльфу
{
#ifdef ELKA
	const char percent_t[] = "%t";
	ttt = AllocWS(256);
	wsprintf(ttt,percent_t,"");
	lcd_ptr = Ram_Layer_Base_Ptr();
	ovr_layer_ptr = Ram_LCD_Overlay_Layer()-188;
#endif
	SetCpuClockHi(2);
	InitConfig();//инициируем конфиг,тобишь читаем настройки из него
	moveSpeed = (((double)dTime1)/1000) * 5.0; //the constant value is in squares/second
	rotSpeed = (((double)dTime1)/1000) * 3.0; //the constant value is in radians/second
	InitScreen();
	wsn = AllocWS(256);
	
	LockSched();
	MAIN_CSM main_csm;
	wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"RayCEngine v0.4b (c) Zeus");//обновляем имя для хтаска
	CreateCSM(&MAINCSM.maincsm,&main_csm,0);//создаем цсм
	UnlockSched();
	
	if (!fname) 
	{
		DoWork=0;
		ShowMSG(1,(int)"Запустите файл *.rcm");
	}
	else
	{
		if (InitMap(fname)) DoWork=1; else DoWork=0;
	}
	//DrawRoundedFrame(0,0,DispW-1,DispH-1,0,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(0));//Clear start screen
	return 0;
}
