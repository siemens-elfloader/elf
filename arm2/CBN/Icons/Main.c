
// ICONS
// ������� ��� ������ ��� ����� Windows

//#define NEWSGOLD //��� ������ ���� ��� ����� ���������
#include "..\swilib.h" // ������� ����. - ����� �� �� ��.��������

int f; //outfile
char filename[128], *file, *ptr, *SGOLD2;

char ext[2048], *extp;  //�� 8 ���� �� ���-� = ����� ����������


void ElfKiller(void){
extern void *ELF_BEGIN;
((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

void make(){ // �������� �� filename
  char *bmp;
  int i;
  if(!(bmp=loadgraph(filename))) return;
  if(*(long*)bmp!=0x200020){ mfree(bmp); return;} //32x32 only!
  memcpy(extp,ptr,strlen(ptr)-4); // �������� ��� ����-�
  for(i=0;i<7;i++,extp++) if(*extp>=0x40 && *extp<0x5b) *extp|=0x20;
  *extp++=0;
  fwrite(f,bmp+4,32*32*2,&err);//2 for highcolor
  mfree(bmp);
}

int main(char *exename, char *fname){
  static DIR_ENTRY dee;
  int off=0;
  extp=ext;
  if(SGOLD2=(char*)malloc(2500000)) mfree(SGOLD2); //�������� SGOLD2
  strcpy(filename,exename);
  strcpy(file=strrchr(filename,'\\')+1,"win386.swp");
do{
  if((f=fopen(filename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))==-1) break;
  fwrite(f,&off,4,&err); //��������� 0
  strcpy(file,"icons\\*.bmp");
  ptr=file+6;
  if(FindFirstFile(&dee,filename,&err)){
    do{
      strcpy(ptr,SGOLD2?dee.file_name:((char*)&dee+169));
      make();
    }while(FindNextFile(&dee,&err));
  }
  FindClose(&dee,&err); 
  off=lseek(f,0,1,&err,&err); //���. �������
  fwrite(f,ext,extp-ext+8,&err); //����� ������ ���� � �����
  lseek(f,0,0,&err,&err); //� ������
  fwrite(f,&off,4,&err); //��������� = �������� ������
  fclose(f,&err);
}while(0);
 SUBPROC((void *)ElfKiller);
 return 0;
}
