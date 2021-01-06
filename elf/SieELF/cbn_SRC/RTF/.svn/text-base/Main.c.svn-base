
//RTF ъюэтхЁЄхЁ фы  edit.elf

#include "..\swilib.h"

#define maxsize 510	// Max длина строки

int getv(unsigned char c){
  if(c>='a' && c<='f') return c-'a'+10;
  if(c>='0' && c<='9') return c-'0';
  return 0;
}

int j=0;

int main(char *buf, int size){
//  int j=0;
  char *out, *in, *out2;
  out=in=buf;
  while(*++in){
    if(*in=='\\' && in[1]=='\''){
     *out++=(getv((unsigned char)in[2])<<4)+getv((unsigned char)in[3]);
     in+=3;
     if(in[1]=='\\' && in[2]!='\''){
       *out++=' ';
     }else{
     while(*++in && *in!='}' && *in!='\\') *out++=*in;
     --in;
    if(out[-1]=='.') *out++=' ';
     }
    }
   }
   //второй проход
   out2=out;
   in=out=buf;
   while(in<out2){
     switch(*in){
       case 0xd: case 0xa: case 0: case 1: case 2: break;
       default: *out++=*in;
     }
     if(++j>maxsize && *in==' '){
       j=0;
       *out++=0xd; *out++=0xa;
     }
     ++in;
   }
// запись
  return out-buf;
}
