#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <string.h>

int loadfilesize=0;

int savefile(char *fname, char *buf, int size){
  FILE *f;
  if((f=fopen(fname,"wb"))==0) return 0;
  fwrite(buf,size,1,f); 
  fclose(f); 
  return 1;
}

char *loadfile(char *filename){ // Загрузить файл, распак-ть
  FILE *f; 
  char *buf=0;
  loadfilesize=0;
  if((f=fopen(filename,"rb"))!=0){
    fseek(f,0,2);
    if(loadfilesize=ftell(f)){
      buf=(char*)malloc(loadfilesize);
	  fseek(f,0,0);
	  fread(buf,loadfilesize,1,f);
    } fclose(f);
  } return buf;
}



int main(int argc, char **argv){
	char *cart_rom, *block, *ptr;
	int i,cartromsize;
	//
	printf("SMD2BIN Converter (c)bn 2007 v0.1");
	if(argc<2){
	    printf("\nUsage: .. file.smd [...]\n");
		return 1;
	}
    if(!(block=(char*)malloc(0x4000))) return 4;
while(*++argv){
	if(!(cart_rom=(char*)loadfile(*argv))) return 2;
    
    if(!(((cartromsize=loadfilesize) / 512) & 1)){
		printf("\nNot SMD File!");
		return 3;
	}

      memcpy(cart_rom,cart_rom+512, cartromsize-=512);
      for(ptr=cart_rom; ptr<cart_rom+cartromsize; ){
        memcpy(block,ptr,0x4000);
        for(i = 0; i < 0x2000; i ++){
          *ptr++=block[0x2000+i];
          *ptr++=block[0x0000+i];
        }
      }
	  strcpy(strrchr(*argv,'.'),".bin");
	  savefile(*argv,cart_rom,cartromsize);
	  free(cart_rom);
	  printf("\n%s",*argv);
}    
	  free(block);
	  return 0;
 }
