

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define line_end(x) (x==0x0d || x==0x0a)

inline char IsNumber(char c)
{
	return (c >= '0' && c <= '9')?1 : 0;
}


inline int ApplyPatch(void *a, char b){
	return 0;
}

inline int UndoPatch(void *a, char b){
	return 0;
}


int ApplyNewPatch(int addres, char *oldByte, char *newbyte, int type)
{
   char flashdata;
   int ods = 0, seek=0;
   int patchnb=0, patchob=0;
   int nds = strlen(newbyte), flash=0;

   if(nds%2 != 0) return 0;		
   if(!oldByte) goto nooldbyte;
   ods = strlen(oldByte);
   if(ods != nds) return 0;	
   if(ods%2 != 0) return 0;

   if(type==1) goto undo;
   if(type==2) goto undo_r;
   for(int i=0; i<nds; i+=2, seek++)
   {
      sscanf(newbyte+i, "%02x", &patchnb);
      sscanf(oldByte+i, "%02x", &patchob);

      //printf("('%X' + %X) %d: '%X'\n", addres, seek, i, patchnb);
      
      if(type!=3)
      {
		  ApplyPatch((void *)(addres+seek), (char)patchnb);
		  printf(" [+] pathing... %x (%c)\n", patchnb, patchnb);
      }
     
      //printf("pathing... %x\n", patchnb);
   }
   
   printf("pathing addres 0x%X, old data has 0x%s replace to new data 0x%s\n", addres, oldByte, newbyte);
   return 1;
   
   undo:
   for(int i=0; i<nds; i+=2, seek++)
   {
      sscanf(newbyte+i, "%02x", &patchnb);
      sscanf(oldByte+i, "%02x", &patchob);
    
	  UndoPatch((void *)(addres+seek), patchob);
      printf(" [-] pathing old data... %x (%c)\n", patchob, patchob);
	  
      //printf("pathing... %x\n", patchnb);
   }
   printf("pathing addres 0x%X, old data has 0x%s replace to new data 0x%s\n", addres, oldByte, newbyte);

   return 1;
   
   undo_r:
   for(int i=0; i<nds; i+=2, seek++)
   {
      sscanf(newbyte+i, "%02x", &patchnb);
      sscanf(oldByte+i, "%02x", &patchob);

	  ApplyPatch((void *)(addres+seek), patchob);
	  printf(" [+-] pathing old data... %x (%c)\n", patchob, patchob);
	  
   }
   printf("pathing addres 0x%X, old data has 0x%s replace to new data 0x%s\n", addres, oldByte, newbyte);
   return 1;
nooldbyte:

    if(type==1) return 0;
    
    for(int i=0; i<nds; i+=2, seek++)
    {
       sscanf(newbyte+i, "%02x", &patchob);
       
       if(type!=3)
       {
		  ApplyPatch((void *)(addres+seek), patchob);
          printf(" [-] pathing no old byte... %x (%c)\n", patchob, patchob);
       }
      //printf("pathing... %x\n", patchnb);
    } 
	printf(" [-] pathing addres 0x%X, old data has 0x%s replace to new data 0x%s\n", addres, oldByte, newbyte);

    //printf("pathing addres 0x%X, replace to new data 0x%s\n", addres, newbyte);

    return 1;
}



char * getNumber(char *stream, int *n)
{  
   int ret = 0;
   char *s = stream, c;
   
   while(!line_end(*s) && *s!=' ') s++;
   
   c = *s;
   *s = 0;
   sscanf(stream, "%x", &ret);
   *s = c;

   s++;
   *n = ret;
   return s;
}


char *parseInBrakets(char *s, char **ret)
{
	char *b =s, *e;
	while(*s){

		if(line_end(*s)){
			if(*(s-1)=='\\') while(line_end(*s))s++;
		}
		if( *(s) =='"' )
		{
			if( *(s-1) == '\\' ) s+=2;
			else break;
		}
		s++;
	}

	e=s;
	char *data = (char*)malloc((s-b)*2+1);
	*data = 0;
	int size = s-b;
	signed char hex = 0;

	s = b;

	for(int i=0; i< size; i++)
	{
		//printf(" [+] %c\n", *(s+i));
		if(*(s+i)=='\\')
		{
			i++;
			//printf(" [-] %x\n", *(s+i));
			switch(*(s+i))
			{
				case 'n':
					hex = '\n';
					//i++;
					break;
				case 'r':
					hex = '\r';
					//i++;
					break;
				case '\n': case '\r':
					while(line_end(*(s+i)))i++;
					hex = *(s+i);
					break;
				default:
					hex = *(s+i-1);
					break;
			}
		} else hex = *(s+i);

		/*if(*(s+i) == '{'){
			while(*s!='}' && *s) s++;
			continue;
		}*/

		//printf(" -- %c + %02X\n", hex, hex);

		sprintf(data+strlen(data), "%02X\0", hex);
	}

	*ret = data;
	return e+1;
}


#pragma inline
static inline char* reversData(char *d, int ln)
{
	short tempbuf = 0;
	int lt = ln-2;
	ln /= 2;

	for(int i=0; i<ln; i+=2, lt-=2)
	{
		tempbuf = *(short*)(d+i);
		*(short*)(d+i) = *(short*)(d+lt);
		*(short*)(d+lt) = tempbuf;
	}

	return d;
}


char *getInteger(char *s, int ln)
{
	char *ret;
	long long int hex = 0;
	int tm;
	char *d = s, c, sgn;

	sgn = *s;
	s++;
	while(*s==' ')s++;

	c = d[ln];
	d[ln] = 0;
	sscanf(s, "%d", &hex);		// фсё нафиг :crazy:
	d[ln] = c;

	if(sgn=='-')
		hex *= (-1);

	ret = (char*)malloc(25);

	sprintf(ret, "%X\0", hex);

	printf("integer: %d\n", hex);

	tm = strlen(ret);
	if(tm>3) 
	reversData(ret, tm);
	return ret;
}


char *getAddres(char *s, char **ret)
{
	char *b = s, *e;
	char *data;
	char *ndata, tc;
	int dsize = 0, curentsize=0, tm=0;

	while(!line_end(*s)){
		s++;
	}

	

	dsize = s-b+2;
	ndata = (char*)malloc(dsize+3);
	*ndata = 0;
	s=b;
	
	while(!line_end(*s) && *s)
	{
		switch(*s)
		{
			case 0x20:
				goto end;
				break;

			case '"':
				s++;
				e = s;
				s = parseInBrakets(s, &data);		// пропарсим содержимое кавычек
				tm = strlen(data);							// вычислим размер данных

				if(dsize <= tm+curentsize)
					ndata = (char*)realloc(ndata, (dsize=(tm + curentsize+128)));

				memcpy(ndata+curentsize, data, tm);
				curentsize += tm;
				ndata[curentsize] = 0;
				free(data);
				break;

			case ',':
				s++;
				while(*s==' ') s++;
				break;
			case '\\':
				while(!line_end(*s)) s++;
				while(line_end(*s) || *s==' ' && *s) s++;
				break;
			default:
				tc = 0;
				if(*(s+1)=='x' || *(s+1)=='X'){
					s+=2;
					tc = 1;
				} else if(*s=='i'){
					tc = 2; s++;
				}

				e = s;

				while(!line_end(*s) && *s !=',' && *s!=' ' && *s!='"' && *s!='\\' && *s!='x' && *s!='i' && *s) 
					s++;

				
				if(s-e != 2 && *s=='x') // конструкция типа 120x0A0D
					s-=1;
				
				//printf("e: %c\n", *s);
				tm = s-e;


				if((tm + curentsize) >= dsize){
					dsize = (tm + curentsize+2);
					ndata = (char*)realloc(ndata, dsize);
				}

				/*if(tm<20 && tc == 2){
					char *dt = getInteger(e, tm);
					tm = strlen(dt);
					e = dt;
					memcpy(ndata+curentsize, dt, tm);
					free(dt);
				}
				else*/
				memcpy(ndata+curentsize, e, tm);

				if(tc==1)									//переворачиваем
					reversData(ndata+curentsize, tm);
				

				ndata[curentsize+(tm)] = 0;
				curentsize += (tm);
			}
	}
	end:
	*ret = ndata;
	return s;
}


int ReadPatchLines(char *fname,int type)//чтение vkp файла
{
    char *buf, *number=0;
    FILE* f = fopen(fname, "rb");
    if(!f) return -1;
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);

    buf =(char*)malloc(size+3);
	int rs = fread(buf, 1, size, f);
	fclose(f);
    buf[rs] = '\n';
	buf[rs+1] = 0;
    
    
    /* ------------------------------- */
    int shift = 0;
	unsigned long int caddres=0;
	char *colddata, *cnewdata; // смещение аддреса 
    char *s = buf, *d=0, *e=0, comments=0;
	char *sb[2]={0};
	char enable=false, isold_equal_ff = false;

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
		  if(!memcmp(s, "enable", 6)) enable = true;
		  else enable = false;
		  s+=7;

		  while(*s==' ') s++;
		  if(!memcmp(s, "old_equal_ff", 12)) isold_equal_ff = true;
		  else isold_equal_ff = false;
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

             if(!comments){                          // закончились коментарии
                while(line_end(*s) || *s==0x20 && *s) s++;
                break;
             }
			 s++;
          }
		  continue;
       }
       if(!*s) return 1;


       if(*s == '-' || *s == '+')		// смещение
       {
		  char signedc = *s;
		  s++;
		  while(*s==' ')s++;
          s = getNumber(s, &shift);
          if(signedc=='-') shift = 0xFFFFFFFF-shift+1;
		  printf("shift: %c (%x)\n", signedc, shift);
       }
       
       if(!line_end(*s) && *s!=0x20 && *s!=';' && *s!='/')
       {
		  colddata = 0;
		  cnewdata = 0;
          d = s;
          while(*s!=':' && *s) s++;     // число до двоеточия
          if(!*s) return -1;

		  e = s;
          while(*s==0x20 && *s) s--;		    // пропустим пробелы
		  number = (char*)malloc(s-d+1);
		  memcpy(number, d, s-d);
		  number[s-d] = 0;

		  caddres = 0;
		  sscanf(number, "%x", &caddres);	// адрес записи
		  free(number);

		  if(caddres<0xA0000000) caddres+=0xA0000000;
		  printf("0x%X\n", caddres);
		  s = e+1;
		  while(*s==' ' && *s) s++;
		  d = s;

		  //gggg
		  s = getAddres(s, &colddata);

		  //printf("n: %s\n", colddata);
		  //sscanf(number, "%x", &colddata);		// старые данные
		  skep:
		  s++;
		  while(*s==' ' && line_end(*s) && *s)s++;
		  if(line_end(*s) || !*s || *s==' ')						// нету старых данных =-O
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
		  
		  s = getAddres(s, &cnewdata);

		  printf("addres: '%x'\n", caddres);
		  printf("olddata: '%s'\n", colddata);
		  printf("newdata: '%s'\n", cnewdata);

		  ApplyNewPatch(caddres+shift, colddata, cnewdata, type);
		  free(colddata);
		  free(cnewdata);
       }
noolddata:

	   s++;
    }
    while(*s);

	free(buf);
}




int main()
{
	ReadPatchLines("C:\\test.vkp", 0);

	/*char *ret;

	char data[] = "0D0A0FFF, 0x00, EE\"hello\\n\\world\"0A0D \n";

	printf("%s\n", data);

	getAddres(data, &ret);

	printf("%s\n", ret);

	delete ret;*/

	/*char d[]= "84467440737095516157";
	
	unsigned long long int ret = 0x1122334455667788;
	//sscanf(d, "%20lld", &ret);
	*/
	//printf("%d\n", 0xEA);
	system("pause");
	return 1;
}
