#include "..\inc\swilib.h"
#include "..\inc\zlib.h"

//const int minus11=-11;
char filename[256];

//#define scrsize 10*10
//char scr[scrsize];
//const IMGHDR img = {(unsigned)10,(unsigned)10,5,0,(char*)scr};
//const int maxprogress=10;
//int progress=10;


//extern void *memset(void *mem, int val, int size);
//char *memset(void *mem, int val, int size){
//  char *s=(char*)mem;
//  while(--size>=0) *s++=(char)val;
//  return mem;
//}

//void DrwImg(const IMGHDR *img, int x, int y){
//  RECT rc;
//  DRWOBJ drwobj;
//  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
//  SetPropTo_Obj5(&drwobj,&rc,0,(IMGHDR *)img);
//  SetColor(&drwobj,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
//  DrawObject(&drwobj);
//}
//
//void progressbar(){
//  int i;
//  if(++progress>maxprogress){
//    progress=0;
//    memset(scr,3,scrsize);
//    for(i=1;i<=maxprogress;i++)
//      DrwImg(&img,6+i*10,84);
//    memset(scr,0xe0,scrsize);
//  }else{
//    DrwImg(&img,6+progress*10,84);
//  }
//  REDRAW();
//}

//typedef struct
//{
//  CSM_RAM csm;
//  int gui_id;
//}MAIN_CSM;
//
//typedef struct
//{
//  GUI gui;
//  WSHDR *ws1;
//  WSHDR *ws2;
//  int i1;
//}MAIN_GUI;
//
////#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))
//#define RGB8(R,G,B) (B+(G<<2)+(R<<5))
//
///*const unsigned short img1_bmp[]={
//0x00,0x00,0x00,
//RGB16(31,0,0),RGB16(31,0,0),RGB16(31,0,0),
//RGB16(31,0,0),RGB16(31,0,0),RGB16(31,0,0),
//RGB16(31,0,0),RGB16(31,0,0),RGB16(31,0,0),
//RGB16(31,63,0),RGB16(31,63,0),RGB16(31,63,0),
//0x00,0x00,0x00
//};*/
//
//unsigned char img1_bmp[128*128];
//
//const IMGHDR img1=
//{
//  128,
//  128,
//  5,
//  0,
//  (char *)img1_bmp
//};
//
//DrwImg(IMGHDR *img, int x, int y, int *pen, int *brush)
//{
//  RECT rc;
//  DRWOBJ drwobj;
//  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
//  SetPropTo_Obj5(&drwobj,&rc,0,img);
//  SetColor(&drwobj,pen,brush);
//  DrawObject(&drwobj);
//}
//
//void method0(MAIN_GUI *data)
//{
//  int i;
//  int c;
//  DrawRoundedFrame(0,0,131,175,0,0,0,
//		   GetPaletteAdrByColorIndex(0),
//		   GetPaletteAdrByColorIndex(20));
//  c=data->i1;
//  i=0;
//  do
//  {
//    img1_bmp[i++]=c;
//    if (i&127) c++;
//  }
//  while(i<(128*128));
//  DrwImg((IMGHDR *)&img1,2,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
////  DrawString(ws_filelist,3,3,128,172,11,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
//  wsprintf(data->ws1,"Redraw number %d",++data->i1);
//  DrawString(data->ws1,5,30,121,100,11,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
//}
//
//void method1(MAIN_GUI *data, void *(*malloc_adr)(int))
//{
//  data->ws1=AllocWS(256);
//  data->ws2=AllocWS(256);
//  data->gui.state=1;
//}
//
//void method2(MAIN_GUI *data, void (*mfree_adr)(void *))
//{
//  FreeWS(data->ws1);
//  FreeWS(data->ws2);
//  data->gui.state=0;
//}
//
//void method3(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
//{
//  data->gui.state=2;
//}
//
//void method4(MAIN_GUI *data, void (*mfree_adr)(void *))
//{
//  if (data->gui.state!=2) return;
//  data->gui.state=1;
//}
//
//void testfs(int i, char *fname)
//{
//  int f;
//  unsigned int err;
//  char s[40];
//  if ((f=fopen(fname,A_ReadWrite+A_Append+A_Create,P_READ+P_WRITE,&err))!=-1)
//  {
//    sprintf(s,"%d\r\n",i);
//    fwrite(f,s,strlen(s),&err);
//    fclose(f,&err);
//  }
//}
//
//
//int method5(MAIN_GUI *data, GUI_MSG *msg)
//{
//  DirectRedrawGUI();
//  wsprintf(data->ws2,"MSG:%08X %08X",msg->gbsmsg->msg,msg->gbsmsg->submess);
//  DrawString(data->ws2,5,45,131,55,11,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
//
//  if (msg->gbsmsg->msg==KEY_DOWN)
//  {
//    switch(msg->gbsmsg->submess)
//    {
//    case RIGHT_SOFT:
//      return(1); //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
//    case '8':
//      {
////	void TestMenu(void);
////	TestMenu();
//      }
//      break;
//    case '2':
////      SUBPROC(testfs,data->i1,"4:\\test.txt");
//      break;
//    case '3':
////      CutWSTR(ws_filelist,0);
////      SUBPROC(test_find_file,0,"4:\\ZBin\\Daemons\\*.elf");
//      DirectRedrawGUI();
//      break;
//    case '4':
////      CutWSTR(ws_filelist,0);
//      DirectRedrawGUI();
//      break;
//    case '0':
//      ShowMSG(1,(int)"Нажали '0'");
//      break;
//    case '5':
//      {
////	void TestEdit(void);
////	TestEdit();
//      }
//      break;
//    }
//  }
//  //  method0(data);
//  return(0);
//}
//
//void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
//{
//  mfree_adr(data);
//}
//
//int method8(void){return(0);}
//
//int method9(void){return(0);}
//
//const void * const gui_methods[11]={
//  (void *)method0,	//Redraw
//  (void *)method1,	//Create
//  (void *)method2,	//Close
//  (void *)method3,	//Focus
//  (void *)method4,	//Unfocus
//  (void *)method5,	//OnKey
//  0,
//  (void *)method7,	//Destroy
//  (void *)method8,
//  (void *)method9,
//  0
//};
//
//const RECT Canvas={0,0,131,175};
//
//void maincsm_oncreate(CSM_RAM *data)
//{
//  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
//  MAIN_CSM*csm=(MAIN_CSM*)data;
//  zeromem(main_gui,sizeof(MAIN_GUI));
//  main_gui->gui.canvas=(void *)(&Canvas);
//  main_gui->gui.flag30=2;
//  main_gui->gui.methods=(void *)gui_methods;
//  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
//  csm->csm.state=0;
//  csm->csm.unk1=0;
//  csm->gui_id=CreateGUI(main_gui);
//}
//
//void maincsm_onclose(CSM_RAM *csm)
//{
//  extern void *ELF_BEGIN;
// // FreeWS(ws_filelist);
// // ws_filelist=NULL;
//  ((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
//}
//
//int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
//{
//  MAIN_CSM *csm=(MAIN_CSM*)data;
////  if ((msg->msg==MSG_GUI_DESTOYED)&&((int)msg->data0==csm->gui_id))
////  {
////    csm->csm.state=-3;
////  }
//  return(1);
//}
//
//const CSM_DESC maincsm=
//{
//  maincsm_onmessage,
//  maincsm_oncreate,
//  0,
//  0,
//  0,
//  0,
//  maincsm_onclose,
//  sizeof(MAIN_CSM),
//  1,
//  &minus11
//};


int fread32(int fh, char *buf, int len, unsigned int *err)
{
int clen;
int rlen; 
int total=0;
while(len)
{
if (len>16384) clen=16384; else clen=len;
total+=(rlen=fread(fh, buf, clen, err));
if (rlen!=clen) break;
buf+=rlen;
len-=clen;
}
return(total);
}

int fwrite32(int fh, char *buf, int len, unsigned int *err)
{
int clen; 
int rlen; 
int total=0;
while(len)
{
if (len>16384) clen=16384; else clen=len;
total+=(rlen=fwrite(fh, buf, clen, err));
if (rlen!=clen) break;
buf+=rlen;
len-=clen;
//progressbar();//add
}
return(total);
}

int unzip(Byte *compr, uLong comprLen, Byte *uncompr, uLong  uncomprLen){
    int err;
    z_stream d_stream; /* decompression stream */
    d_stream.zalloc = (alloc_func)0;
    d_stream.zfree = (free_func)0;
    d_stream.opaque = (voidpf)0;
    d_stream.next_in  = compr;
    d_stream.avail_in = (uInt)comprLen;
    err = inflateInit2(&d_stream,-MAX_WBITS);
    if(err!=Z_OK){ 
   unerr:
//    if(!loadfilenomsg)
//      MessageBox(NULL,"Ошибка распаковки файла!",0,MB_OK); 
      return err;
    }
    d_stream.next_out = uncompr;            /* discard the output */
    d_stream.avail_out = (uInt)uncomprLen;
    err = inflate(&d_stream, 2);
    if(err<0) goto unerr;
    err = inflateEnd(&d_stream);
    if(err<0) goto unerr;
    return 0;
}

extern void kill_data(void *p, void (*func_p)(void *));

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

int getint(char *ptr){
  return ptr[0]|(ptr[1]<<8)|((ptr[2])<<16)|((ptr[3])<<24);
}

void prepname(char *file){
  unsigned int err;
  do{
    while(*++file && *file!='/');
    if(!*file) break;
    *file=0;
    mkdir(filename,&err);
    *file='\\';
  }while(1);
//  char *s=file+strlen(file);
//  while(--s>file && *s!='/');
//  if(s>file){
//    do{ 
//      *file++=*++s;
//    } while(*s!=0);
//  }
}

int main(char *exename, char *fname)
{
  int in,out;
  int packsize=1, unpacksize=2, filenamesize=3;
  unsigned int err;
  char *buf, *file=filename;
////// // char dummy[sizeof(MAIN_CSM)];
  if(fname && (in=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    strcpy(filename,fname);
    file=filename+strlen(filename);
    while(--file>filename && *file!='.');
    *file=0;
    mkdir(filename,&err);
    *file++='\\';
    while(1){
      if(fread(in,file,30,&err)!=30) break;
      if(getint(file)!=0x4034b50) break;
      packsize=getint(file+18);
      unpacksize=getint(file+22);
      filenamesize=getint(file+26);
      fread(in,file,filenamesize,&err);
      file[filenamesize]=0;
      if(file[filenamesize-1]!='/'){
        if((buf=(char*)malloc((packsize==unpacksize)?packsize:(packsize+unpacksize)))!=NULL){
          fread32(in,buf,packsize,&err);
          prepname(file);
          if ((out=fopen(filename,A_ReadWrite+A_BIN+A_Create,P_READ+P_WRITE,&err))!=-1){
            if(packsize==unpacksize){
              fwrite32(out,buf,packsize,&err);
            }else{
              unzip((Byte*)buf,packsize,(Byte*)(buf+packsize),unpacksize);
              fwrite32(out,buf+packsize,unpacksize,&err);
            }
            fclose(out,&err);
          }
          mfree(buf);
        }
      }
    }
////////  CreateCSM(&maincsm,dummy,0);  
  fclose(in,&err);
 }
/////// // FreeWS(ws_filelist);
/////// // ws_filelist=NULL;
// progress=maxprogress-1;
// progressbar();
 SUBPROC((void *)ElfKiller);
 return (0);
}


//      sprintf(filename,"\n%d %d %d",packsize,unpacksize,filenamesize);
//   out=fopen("0:\\ZBin\\123",A_ReadWrite+A_BIN+A_Append+A_Create,P_READ+P_WRITE,&err);
//   fwrite(out,filename,100,&err);
//   fclose(out,&err);


//  out=fopen("0:\\ZBin\\123",A_ReadWrite+A_BIN+A_Append+A_Create,P_READ+P_WRITE,&err);
//  fwrite32(out,filename,100,&err);
//  fclose(out,&err);
  //fread32(in,filename,100,&err);
