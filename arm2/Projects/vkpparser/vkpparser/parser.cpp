#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <memory.h>
#include <string.h>

const char perc_x[]="%X";
char msg[256];//for logs


#define line_end(x) (x==0x0d || x==0x0a)

inline char IsNumber(char c)
{
	return (c >= '0' && c <= '9')?1 : 0;
}


int ApplyNewPatch(int addres, char *oldByte, char *newbyte, int type)
{
   int ods = 0, seek=0;
   int patchnb=0, patchob=0;
   int nds = strlen(newbyte);

   if(nds%2 != 0) return 0;		// не четные данные??? =-O
   if(!oldByte) goto nooldbyte;
   ods = strlen(oldByte);
   if(ods != nds) return 0;		// размер старых данных должен совпадать с новыми данными
   if(ods%2 != 0) return 0;

   if(type==1) goto undo;
   if(type==2) goto undo_r;
   for(int i=0; i<nds; i+=2, seek++)
   {
      sscanf(newbyte+i, "%02x", &patchnb);
      sscanf(oldByte+i, "%02x", &patchob);
                
      //if( GetByteFromAddress((void*)(addres+seek)) != patchob) {
         //ShowMSG(1, (int)"Ќе соответстви€ данных!");
         //return 0;
     // }
      
      if(type!=3)
//      PrePatch((void *)(addres+seek), 0, patchnb);
      //printf("patching... %x\n", patchnb);
   }
   return 1;
   
   undo:
   for(int i=0; i<nds; i+=2, seek++)
   {
      sscanf(newbyte+i, "%02x", &patchnb);
      sscanf(oldByte+i, "%02x", &patchob);
                
//      if( GetByteFromAddress((void*)(addres+seek)) != patchnb) {
         //ShowMSG(1, (int)"Ќе соответстви€ данных!");
         //return 0;
    //  }
                
//      PrePatch((void *)(addres+seek), patchob, 0);
      //printf("patching... %x\n", patchnb);
   }
   //printf("patching addres 0x%X, old data has 0x%s replace to new data 0x%s\n", addres, oldByte, newbyte);

   return 1;
   
   undo_r:
   for(int i=0; i<nds; i+=2, seek++)
   {
      sscanf(newbyte+i, "%02x", &patchnb);
      sscanf(oldByte+i, "%02x", &patchob);
                
      if( GetByteFromAddress((void*)(addres+seek)) != patchnb) {
         //ShowMSG(1, (int)"Ќе соответстви€ данных!");
         //return 0;
      }
                
      PrePatch((void *)(addres+seek), patchob, 0);
      //printf("patching... %x\n", patchnb);
   }
   return 1;
nooldbyte:

    // нету старых данных, отменить невозможно!!!
    if(type==1) return 0;
    for(int i=0; i<nds; i+=2)
    {
       sscanf(newbyte+i, "%02x", &patchnb);
       PrePatch((void *)(addres+seek), 0, patchnb);
       //printf("patching... %x\n", patchnb);
    }

    //printf("patching addres 0x%X, replace to new data 0x%s\n", addres, newbyte);

    return 1;
}


char * getNumber(char *stream, int *n)
{
   if(!IsNumber(*stream)){
      *n = 0;
      return 0;
   }
   
   int ret = 0;
   char *s = stream;
   
   while(!line_end(*s) && *s!=' ') s++;
   
   sscanf(stream, perc_x, &ret);
   s++;
   *n = ret;
   return s;
}


char *parseInBrakets(char *s, char **ret)
{
	char *b =s;
	while(*s!='"' && *(s-1)!='\\' && *s) s++;

	char *data = (char*)malloc((s-b)*2+1);
	*data = 0;
	signed char hex = 0;

	for(int i=0; i< s-b; i++)
	{
		sscanf(b, "%01x", &hex);
		sprintf(data+strlen(data), "%02X\0", hex);
	}

	*ret = data;
	return s;
}


//#pragma Z.Vova = optimization activated
int ReadPatchLines(char *fname, int type)//чтение vkp файла
{
    char *buf, *number=0;
    FILE *f = fopen(fname, A_ReadOnly+A_BIN, P_READ, 0);
    if(f==-1) return -1;
    
    int size = lseek(f, 0, S_END,0,0);
    lseek(f, 0, S_SET,0,0);

    buf =(char*)malloc(size+1);
    int rs = fread(f, buf, size,0);
    buf[rs] = ' ';
    buf[rs+1] = 0;
    fclose(f);
    
    /* ------------------------------- */
    int shift = 0, caddres=0;
    char *colddata, *cnewdata; // смещение аддреса 
    char *s = buf, *d=0, *e=0, comments=0;
    char *sb[2]={0};
    char enable=0, isold_equal_ff = 0;
    
    do
    {
       
       if(*s == ';' || (*s=='/' && *(s+1)=='/')) {           // комент
          while(!line_end(*s)) s++;                 // ищем конец строки
          while(line_end(*s) || *s==0x20) s++;      // пропустим все \r \n \x20
          continue;
       }
       
       if(*s == '#'){
          s++;
          while(*s==' ') s++;
          if(memcmp(s, "pragma", 6)) goto endpragma;
          s+=7;

          while(*s==' ') s++;
          if(!memcmp(s, "enable", 6)) enable = 1;
          else enable = 0;
          s+=7;

          while(*s==' ') s++;
          if(!memcmp(s, "old_equal_ff", 12)) isold_equal_ff = 1;
          else isold_equal_ff = 0;
          s+=12;
          endpragma:
          while(!line_end(*s)) s++;
          while(line_end(*s) || *s==0x20) s++;
          continue;
       }
       
       if(*s=='/' && *(s+1)=='*')
       {
          s+=2;
          comments = 1;
          while(*s){
             if(*s=='/' && *(s+1)=='*') {
                s+=2;
                comments++;
             }
             if(*s=='*' && *(s+1)=='/') {
                comments--;
                s+=2;
             }

             if(!comments){                          // ??????????? ??????????
                while(line_end(*s) || *s==0x20 && *s) s++;
                break;
             }
             s++;
          }
          continue;
       }
       if(!*s) return 1;


       if(*s == '-' || *s == '+')		// ????????
       {
          s++;
          while(*s==' ')s++;
          s = getNumber(s, &shift);
          if(*s=='-') shift *= (-1);
       }
       
       if(!line_end(*s) && *s!=0x20 && *s!=';' && *s!='/')
       {
          d = s;
          while(*s!=':' && *s) s++;     // ????? ?? ?????????
          if(!*s) return -1;

          e = s;
          while(*s==0x20 && *s) s--;		    // ????????? ???????
          number = (char*)malloc(s-d+1);
          memcpy(number, d, s-d);
          number[s-d] = 0;

          caddres = 0;
          sscanf(number, "%x", &caddres);	// ????? ??????
          free(number);

          if(caddres<0xA0000000) caddres+=0xA0000000;
          //printf("0x%X\n", caddres);
          s = e+1;
          while(*s==' ' && *s) s++;
          d = s;

          if(*s=='"'){
	          s = parseInBrakets(s, &colddata);
	          goto skep;
          }
          sb[0] = 0;
          tryagain:
          while(!line_end(*s) && *s!=' ' && *s!=',' && *s) s++;

          if(*s==','){								// эта странна€ хрень с конфигом мп %) ADDRE,O_o,SS
	          sb[0] = s-1;
	          s++;
	          while(*s!=',' && *s) s++;
	          s++;
	          while(line_end(*s) || *s==' ' && *s) s++;
	          sb[1] = s;
	          goto tryagain;
          }

          if(sb[0] != 0)
          {
             colddata = (char*)malloc( (sb[0]-d)+(s-sb[1])+1);
             memcpy(colddata, d, sb[0]-d);
             memcpy(colddata+(sb[0]-d), sb[1], (s-sb[1]));

             colddata[(sb[0]-d)+(s-sb[1])] = 0;
          }
          else
          {
             colddata = (char*)malloc(s-d+1);
             memcpy(colddata, d, s-d);
             colddata[s-d] = 0;
          }
                  

          if(colddata[1]=='x' || colddata[1]=='X') { // 0x нада перевернуть
             int ln = strlen(colddata)-2;
             short tempbuf=0;
             int lt = ln;
             memmove(colddata, colddata+2, ln);
             colddata[ln] = 0;

             //printf("s: %s\n", colddata);
             ln /= 2;
             lt-=2;
             for(int i=0; i<ln; i+=2, lt-=2)
             {
                tempbuf = *(short*)(colddata+i);
                *(short*)(colddata+i) = *(short*)(colddata+lt);
                *(short*)(colddata+lt) = tempbuf;
             }
          }

          //sscanf(number, "%x", &colddata);		// старые данные
          skep:
          s++;
          while(*s==' ' && line_end(*s) && *s)s++;
          if(line_end(*s) || !*s || *s==' ')				// нету старых данных =-O
          {
             cnewdata = 0;
             if(isold_equal_ff && enable){
                int l = strlen(colddata);
                cnewdata = (char*)malloc(l+1);

                memset(cnewdata, 'F', l);
                cnewdata[l] = 0;
             }
             ApplyNewPatch(caddres+shift, cnewdata, colddata, type);
             free(colddata);
             if(cnewdata) free(cnewdata);
             goto noolddata;
          }

          d = s;
          while(!line_end(*s) && *s!=' ' && *s) s++;
          cnewdata = (char*)malloc(s-d+1);
          memcpy(cnewdata, d, s-d);
          cnewdata[s-d] = 0;


          if(cnewdata[1]=='x' || cnewdata[1]=='X') {
             int ln = strlen(cnewdata);
             memmove(cnewdata-2, cnewdata, ln);
             cnewdata[ln-2] = 0;
          }
          //sscanf(number, "%x", &cnewdata);		// новые данные

          //printf("addres: '%x'\n", caddres);
          //printf("olddata: '%s'\n", colddata);
          //printf("newdata: '%s'\n", cnewdata);

          ApplyNewPatch(caddres+shift, colddata, cnewdata, type);
          free(colddata);
          free(cnewdata);
       }
noolddata:

	   s++;
    }
    while(*s);
    
    free(buf);
    return 1;
}
