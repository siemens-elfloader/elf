

#define IPC_DT_NAME "_DeskTop"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

typedef void (*func)();

// typedef struct
// {
//   int mode; //0-normal mode, 1-select mode 
//   int dir_enum; //0x26 by default
//   WSHDR* path_to_file; //path to file
//   WSHDR* file_name; //put cursor to this file
//   int unk5;
//   int is_exact_dir;
//   int unk7_11[5];
//   WSHDR* full_filename;
//   int unk13;
//   int (*user_handler)(void*); //called in select mode
//   void* this_struct_addr;
//   int unk16_26[11]; 
// }NativeExplorerData;

typedef struct{
	char shortcut[0x10];
	int entry;
}SHORTCUTREC;

#pragma swi_number=0x221
__swi __arm void SetCpuClockLow(int const_2);
#pragma swi_number=0x222
__swi __arm void SetCpuClockTempHi(int const_2);
#pragma swi_number=0x5E
__swi __arm int GetMMIMemUsed(void);
/*#pragma swi_number=0x254
__swi __arm int StartNativeExplorer(NativeExplorerData* data);*/
#pragma swi_number=116
__swi __arm SHORTCUTREC *GetShortcutRecordByName(char *szShortcutName);

typedef struct
{
	void *prev,*next;
	RECT p;
	char type, *nm;
	int (*onEnter)();
}DT_MN_POINT;

typedef struct
{
	DT_MN_POINT *first, *last;
}DT_MN;

typedef struct{
	void *prev,*next;
	RECT p;
	char d, *nm, *inf, *img, *fl, cpos, csz;
	void (*onDraw)();
	int (*onEnter)();
	void (*onInf)();
}DT_ICON;

struct{
	DT_ICON *first, *last, *act;
	char inf, foc, cur;
}Dt;

typedef struct{
	char *sig;
	DT_ICON *ic;
}PLG_P;

char perc_t[]="%t",
		black[]={0,0,0,100},
		red[]={0xff,0,0,100},
		white[]={0xff,0xff,0xff,100},
		white0[]={0xff,0xff,0xff,50};


void Ad_MN_Point(DT_MN *menu, DT_MN_POINT *point)
{
	DT_MN_POINT *tmnp=menu->first;
	menu->first=point;
	menu->first->next=tmnp;
	((DT_MN_POINT*)menu->first->next)->prev=menu->first;
}

void DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}





///////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////



IMGHDR* CreateImgHdrByAnyFile (WSHDR * path,short width, short height, int rot){
	unsigned int err=0;
	int msz,uid;
	IMGHDR *tmpimg,*myimg=NULL;  
	WSHDR *ext;
	HObj  mypicObj;
	short pos;
	int len;
	if (!path)goto exit0;
	len=wstrlen(path); 
	pos= wstrrchr(path,len,'.'); 
	if (!pos)goto exit0;

	ext=AllocWS(len-pos);
	wstrcpybypos(ext,path,pos+1,len-pos);
	uid=GetExtUid_ws(ext);      
	FreeWS(ext);
	mypicObj=Obs_CreateObject(uid,0x2d,0x02,0x80A8,1,1,&err);    
	if (err)  return 0;
	err=Obs_SetInput_File(mypicObj,0,path);
	if (err)  goto exit1;  
	if (width!=0){ 
		unsigned short w=width;  
		unsigned short h=height;      
    /*
		err=Obs_GetInfo(mypicObj,0);    
		if (err)  goto exit1;  
		err=Obs_GetInputImageSize(mypicObj,&w,&h);    
		if (err)  goto exit1;  
	*/
		err=Obs_SetOutputImageSize(mypicObj,w,h);
		if (err)  goto exit1;      
		if (rot){  
			err= Obs_SetRotation(mypicObj,rot);
			if (err)  goto exit1;      
		}
		err=Obs_SetScaling(mypicObj,5);
		if (err)  goto exit1;          
	}
	err=Obs_Start(mypicObj);
	if (err)  goto exit1;            
	err=Obs_Output_GetPictstruct(mypicObj,&tmpimg);
	if (err)  goto exit1;             
	msz=CalcBitmapSize (tmpimg->w,tmpimg->h,tmpimg->bpnum);
	myimg=malloc(sizeof(IMGHDR));
	myimg->w=tmpimg->w;
	myimg->h=tmpimg->h;
	myimg->bpnum=tmpimg->bpnum;
	myimg->bitmap=malloc(msz);
	memcpy(myimg->bitmap,tmpimg->bitmap,msz);
exit1:
		Obs_DestroyObject(mypicObj);
exit0:  
		return myimg;
}

// char path[]="0:\\Pictures\\Screensaver\\Beach.jpg";
// method0{
// 	wsprintf(mws,"%s",path);
// 	IMGHDR *img;
// 	img=CreateImgHdrByAnyFile(mws,140,180,90);
// 	DrwImg2(img,0,20);
// 	mfree(img->bitmap);
// 	mfree(img);
// }

















// IMGHDR* CreateIMGHDRFromAnyFile (const char * fpath,short width, short height, int rot){
// 	WSHDR *path=AllocWS(256);
// 	wsprintf(path,"%s",fpath);
// 	unsigned int err=0;
// 	int msz,uid;
// 	IMGHDR *tmpimg,*myimg=NULL;  
// 	WSHDR *ext;
// 	HObj  mypicObj;
// 	short pos;
// 	int len;
// 	if (!path)goto exit0;
// 	len=wstrlen(path); 
// 	pos= wstrrchr(path,len,'.'); 
// 	if (!pos)goto exit0;
// 
// 	ext=AllocWS(len-pos);
// 	wstrcpybypos(ext,path,pos+1,len-pos);
// 	uid=GetExtUid_ws(ext);      
// 	FreeWS(ext);
// 	mypicObj=Obs_CreateObject(uid,0x2d,0x02,0x80A8,1,1,&err);    
// 	if (err)  return 0;
// 	err=Obs_SetInput_File(mypicObj,0,path);
// 	if (err)  goto exit1;  
// 	if (width!=0){ 
// 		unsigned short w=width;  
// 		unsigned short h=height;      
//     /*
// 		err=Obs_GetInfo(mypicObj,0);    
// 		if (err)  goto exit1;  
// 		err=Obs_GetInputImageSize(mypicObj,&w,&h);    
// 		if (err)  goto exit1;  
// 	*/
// 		err=Obs_SetOutputImageSize(mypicObj,w,h);
// 		if (err)  goto exit1;      
// 		if (rot){  
// 			err= Obs_SetRotation(mypicObj,rot);
// 			if (err)  goto exit1;      
// 		}
// 		err=Obs_SetScaling(mypicObj,5);
// 		if (err)  goto exit1;          
// 	}
// 	err=Obs_Start(mypicObj);
// 	if (err)  goto exit1;            
// 	err=Obs_Output_GetPictstruct(mypicObj,&tmpimg);
// 	if (err)  goto exit1;             
// 	msz=CalcBitmapSize (tmpimg->w,tmpimg->h,tmpimg->bpnum);
// 	myimg=malloc(sizeof(IMGHDR));
// 	myimg->w=tmpimg->w;
// 	myimg->h=tmpimg->h;
// 	myimg->bpnum=tmpimg->bpnum;
// 	myimg->bitmap=malloc(msz);
// 	memcpy(myimg->bitmap,tmpimg->bitmap,msz);
// exit1:
// 		Obs_DestroyObject(mypicObj);
// exit0:  
// 		FreeWS(path);
// 		return myimg;
// }

// char path[]="0:\\Pictures\\Screensaver\\Beach.jpg";
// method0{
// 	wsprintf(mws,"%s",path);
// 	IMGHDR *img;
// 	img=CreateImgHdrByAnyFile(mws,140,180,90);
// 	DrwImg2(img,0,20);
// 	mfree(img->bitmap);
// 	mfree(img);
// }



