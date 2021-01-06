extern void *memsetw(void *mem, int val, int size); 
//===================================================== Строка_с_шеснатичным_числом -> Int  =====================================
int strh_2int(char* str)
{
  int n,c=0;
  if (*(str+strlen(str)-1)=='h') *(str+strlen(str)-1)='\0';
  while ((*str!='h')&&(*str))
  {
    if ((*str>='a')&&(*str <='f')) n=*str-('A'-('9'+1))-('a'-'A');
    else if ((*str>='A')&&(*str<='F')) n=*str-('A'-('9'+1));
    else if ((*str>='0')&&(*str<='9')) n=*str;
    c=c*16+(n-'0');
    str++;
  }
  return c;
}




//=====================================================  =====================================================
int str2int(const char *str)
{
  int n,c=0;
  while(*str!='\0')
  {
    n=*str;
    c=c*10+(n-'0');
    str++;
  }
  return c;
}





//===================================================== Запускаем файло ======================================================
void RunFile(char *fname)
{
  WSHDR *ws=AllocWS(256);
  str_2ws(ws,fname,strlen(fname)+1);
  ExecuteFile(ws,0,nill);
  FreeWS(ws);
}





//===================================================== Запускаем шерткат ======================================================
void RunShort(char *fname)
{
  int (*ff) (void);
  ff=(int(*)(void))GetFunctionPointer(fname);
  if(ff!=NULL)
    SUBPROC((void*)(*ff));
  else
    ShowMSG(1,(int)"NULL pointer function!");
}





//===================================================== Запускаем энтрик ======================================================
void Run_Entry(char *entry)
{
  typedef int (*func)(void);
  func ff;
  ff=(func)strh_2int(entry);
  if (ff!=NULL) SUBPROC((void *)(*ff));
}





//===================================================== Соединение строк ======================================================
char *concat(char *s1,char *s2)
{
  int l;
  char *str=malloc((l=strlen(s1))+strlen(s2)+1);
  strcpy(str,s1);
  strcpy(str+l,s2);
  return str;
}


//===================================================== Очистка IMGHDR ======================================================


void deleteIMGHDR(IMGHDR *img)
{
  mfree(img->bitmap);
  mfree(img);
}


//===================================================== Создание IMGHDR ======================================================


/*IMGHDR *CreateImgr16(int width, int height)
{
  int ensize;
  IMGHDR * img_hc=malloc(sizeof(IMGHDR));
  short *iimg=(short*)malloc(ensize=width*height*sizeof(short));
  img_hc->w=width;
  img_hc->h=height;
  img_hc->bpnum=8;
  img_hc->bitmap=(char*)iimg;
  memsetw(iimg,00,ensize>>1);
  return (img_hc);  
}*/

//===================================================== Создание IMGHDR ======================================================


/*DrwPngImg(IMGHDR *img, int x, int y)
{
  

  
  
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc, x, y, img->w, img->h);
  SetPropTo_Obj5(&drwobj, &rc, 0, (IMGHDR*)&img);
  DrawObject(&drwobj);
}*/


