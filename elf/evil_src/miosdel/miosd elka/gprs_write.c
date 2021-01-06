#include "..\inc\swilib.h"
extern char gpinfo[];
char gp1info[32];
int result1;
int result2;
int result3;
int janko;

int atoi(char *attr)
{
  int ret=0;
  int neg=1;
  for (int k=0; ; k++)
  {
    if ( attr[k]>0x2F && attr[k]<0x3A) {ret=ret*10+attr[k]-0x30;} else { if ( attr[k]=='-') {neg=-1;} else {return(ret*neg);}}
  }
}

void write_file(char *wer)
{
  volatile int hFile2;
  unsigned int io_error2 = 0;
  unsigned int ul2;
  FSTATS stat2;
  GetFileStats("4:\\zbin\\miosd\\miosd3.file",&stat2,&ul2);
  hFile2 = fopen("4:\\zbin\\miosd\\miosd3.file",A_ReadWrite+A_Create+A_Truncate+ A_BIN,P_READ+P_WRITE, &io_error2);
  if(hFile2!=-1)
  {
    fwrite(hFile2, wer, strlen(wer), &io_error2);
    fclose(hFile2, &io_error2);
  }
}

char txt_in[32];

void write_total()
{
    int f4;
    int fsize4;
    FSTATS stat4;
    unsigned int ul4;

    result1=atoi(gpinfo);
    
    volatile int hFile_ex3;
    unsigned int io_error_ex3 = 0;
    hFile_ex3 = fopen("4:\\zbin\\miosd\\miosd3.file",A_ReadOnly + A_BIN,P_READ, &io_error_ex3);
    if(hFile_ex3!=-1)
    {
      fclose(hFile_ex3, &io_error_ex3);
      GetFileStats("4:\\zbin\\miosd\\miosd3.file",&stat4,&ul4);
      if(stat4.size>0)
      {
        f4=fopen("4:\\zbin\\miosd\\miosd3.file",A_ReadOnly+A_BIN,P_READ,&ul4);
        fsize4=stat4.size;
        char *p4=malloc(fsize4);
        p4[fread(f4,p4,fsize4,&ul4)];
        fclose(f4,&ul4);
        strcpy(gp1info, p4);
        gp1info[fsize4]='\0';
        mfree(p4);
        result2=atoi(gp1info);
        result3=result1+result2;
        sprintf(txt_in, "%d", result3);
        write_file(txt_in);
      }
    }
    else
    {
      result3=result1;
      sprintf(txt_in, "%d", result3);
      write_file(txt_in);
    }
}
