

#include "swilib.h"
int lent=0;

char *loadfiles(char *filename){ // Загрузить файл, распак-ть
  int f; unsigned int err;  char *buf=0;
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    if(loadfilesize=lseek(f,0,2,&err,&err)){
      lent=loadfilesize;
      buf=(char*)malloc(loadfilesize);
      lseek(f,0,0,&err,&err);
      if(fread32(f,buf,loadfilesize,&err)!=loadfilesize){ mfree(buf); buf=0;}
    } fclose(f,&err);
  } return buf;
}

int savefiles(char *fname, char *buf, int size){
  int f,i;
  if((f=fopen(fname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))==-1) return 0;
  i=fwrite32(f,buf,size,&err); 
  fclose(f,&err); 
  return i;
}

int isfile (char *names){
int f;
unsigned int err;
 f = fopen(names, A_ReadOnly, P_READ, &err ); 
   fclose(f,&err); 
 if ( f==-1 ) return 0; 
 else return 1;
}

int test_dir(){
  
char folder_01[]="4:\\ZBin\\";
char folder_02[]="0:\\ZBin\\";
char folder_03[]="4:\\ZBin\\Rebel+\\";
char folder_04[]="0:\\ZBin\\Rebel+\\";
char folder_05[]="CRebel+\\register\\";
char folder_06[]="0:\\ZBin\\Rebel+\\register\\";

char * file_reg_01="reg_slot.";






unsigned int error_dir; //ошибка
char disc_zbin = '4';   //диск на котором папка збин
int slots_val = 0;
int post = 1;           //равен единице, пока слот найден



if (isdir(folder_01,&error_dir)) {
if (!(isdir(folder_03,&error_dir))) mkdir(folder_03,&error_dir); 
if (!(isdir(folder_05,&error_dir))) mkdir(folder_05,&error_dir); 
}
else if (isdir(folder_02,&error_dir)){
if (!(isdir(folder_04,&error_dir))) mkdir(folder_04,&error_dir); 
if (!(isdir(folder_06,&error_dir))) mkdir(folder_06,&error_dir); 
char disc_zbin = '0';
}


while (slots_val<99 &&  post==1){





}





return error_dir;
}





