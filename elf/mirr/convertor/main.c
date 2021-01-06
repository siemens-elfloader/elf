#include "swilib.h"
int lenta=0;
unsigned int err=0;

int loadfilesize=0;
int savefile(char *fname, char *buf, int size){
  int f,i;
  if((f=fopen(fname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))==-1) return 0;
  i=fwrite32(f,buf,size,&err); 
  fclose(f,&err); 
  return i;
}

//------------------------------------------------------------------------------

char *loadfile(char *filename){ // Загрузить файл, распак-ть
  int f; unsigned int err;  char *buf=0;
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    if(loadfilesize=lseek(f,0,2,&err,&err)){
      lenta=loadfilesize;
      buf=(char*)malloc(loadfilesize);
      lseek(f,0,0,&err,&err);
      if(fread32(f,buf,loadfilesize,&err)!=loadfilesize){ mfree(buf); buf=0;}
    } fclose(f,&err);
  } return buf;
}
     char *buffu=0;
char *Tfilename0;
char enter[] = "\x0D\x0A";

int Refresh();
  char *p=0;
char *tn;char *TF;
int loadfilesize;


int f;



char *hex(char r){
  char *temp="  ";
int y;
y=r;
if (y==0) return "00";
temp[0]= '0';
if (y>15){temp[0]= '1'; y-=16;}
if (y>15){temp[0]= '2'; y-=16;}
if (y>15){temp[0]= '3'; y-=16;}
if (y>15){temp[0]= '4'; y-=16;}
if (y>15){temp[0]= '5'; y-=16;}
if (y>15){temp[0]= '6'; y-=16;}
if (y>15){temp[0]= '7'; y-=16;}
if (y>15){temp[0]= '8'; y-=16;}
if (y>15){temp[0]= '9'; y-=16;}
if (y>15){temp[0]= 'a'; y-=16;}
if (y>15){temp[0]= 'b'; y-=16;}
if (y>15){temp[0]= 'c'; y-=16;}
if (y>15){temp[0]= 'd'; y-=16;}
if (y>15){temp[0]= 'e'; y-=16;}
if (y>15){temp[0]= 'f'; y-=16;}

temp[1]= '0';
if (y==1){temp[1]= '1';}
if (y==2){temp[1]= '2';}
if (y==3){temp[1]= '3';}
if (y==4){temp[1]= '4';}
if (y==5){temp[1]= '5';}
if (y==6){temp[1]= '6';}
if (y==7){temp[1]= '7';}
if (y==8){temp[1]= '8';}
if (y==9){temp[1]= '9';}
if (y==10){temp[1]= 'a';}
if (y==11){temp[1]= 'b';}
if (y==12){temp[1]= 'c';}
if (y==13){temp[1]= 'd';}
if (y==14){temp[1]= 'e';}
if (y==15){temp[1]= 'f';}
return temp;
}

void hexer(){

    char *out; 
    out = malloc((lenta*4)+21);
    sprintf(out,"char %s[] = \x22",tn);
    for (int i=0; i<lenta; i++){
    //
    sprintf(out,"%s\\x%s",out, hex(buffu[i]));
    }
     sprintf(out,"%s\x22\x3b ",out);   
     sprintf(out,"%s  %s",out,enter); 
    savefile(Tfilename0, out, strlen(out));
        if (out) mfree(out);
        ShowMSG(1,(int)TF);
}


void hexer2(){

    char *out; 
    out = malloc((lenta*4)+21);
    sprintf(out,"char ressurs[] = \x22");
    for (int i=0; i<lenta; i++)
	{
      sprintf(out,"%s\\x%s",out, hex(buffu[i]));
    }
     sprintf(out,"%s\x22\x3b ",out);   
     sprintf(out,"%s  %s",out,enter); 
    savefile("4:\\output.c", out, strlen(out));
        if (out) mfree(out);
       // ShowMSG(1,(int)Tfilename0);
}
//------------------------------------------------------------------------------
int main(char *exename, char *fname)
{
Tfilename0 = malloc(250); char *ext0; char *ext1; char *ext2; char *ext3; tn = malloc(50); char *tn2 = malloc(50);
  
  strcpy(Tfilename0,fname);

  ext1=strrchr(Tfilename0,'.');   //ext1 = позиция первой точки, найденой справа
  ext3=ext1;                      //то-же
  strcpy(ext1,"\x00");            //записываем 0 вместо точки (стираем расширение у Tfilename0)
  ext2=strrchr(Tfilename0,'.');   //ext2 = позиция первой точки, найденой справа у Tfilename0 (второе расширение)
  if (ext2)
  {                      //если второе расширение существует, то..
    ext1=ext2+1;                        //ext1 = позиция после точки
    strcpy(tn2,ext1);                   //tn2 = запоминаем второе расширение
    strcpy(ext2,"_\x00");               // стираем второе расширение у Tfilename0, вместо него "_"
    strcpy(ext1,tn2);                   // записываем расширение назад
  } 
  ext0=strrchr(Tfilename0,'\\')+1;    //ext0 = позиция начала названия файла без путей
  strcpy(tn,ext0);                    //сохраняем в тн название файла без путей и расширения
  
  ext2=ext1+strlen(tn2);              //ext2 = ext1
  strcpy(ext3,".c");
  TF = malloc(350); strcpy (TF, "Cохранено в ");
  ext2= TF+12;
  strcpy (ext2, Tfilename0);
  /**/
 // strcpy(tn2,ext2);
  
 //strcpy(ext0,"\x00");  
  
  
  
  if (fname) {
    
  
  buffu=loadfile(fname);     
    if (buffu){
     SUBPROC ((void *)hexer);
   // hexer();    
    if (buffu) mfree(buffu);  
  
    }
    else ShowMSG(1,(int)"Файл не найден!");/**/
  
  
  
  
  }   
else {
  
  
    buffu=loadfile("4:\\000");     
    if (buffu){
      SUBPROC ((void *)hexer2);
        ShowMSG(1,(int)"Cохранено в 4:\\output.c");
    if (buffu) mfree(buffu);  
  
    }
    else ShowMSG(1,(int)"Файл 4:\\000 не найден!"); }
}
//------------------------------------------------------------------------------





