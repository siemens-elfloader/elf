

IMGHDR *tIMG;

char perc_t[]="%t",
		perc_s[]="%s",
		black[]={0,0,0,100},
		trans_black[]={0,0,0,50},
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



#pragma inline
int infoc(RECT *p, short x, short y)
{
	if((x>=p->x)&&(x<=p->x2)&&(y>=p->y)&&(y<=p->y2)) return 1;
	else return 0;
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
		// ShowMSG(1, (int)"Жопа!!!");
  Obs_DestroyObject(mypicObj);
exit0:  
  return myimg;
}


