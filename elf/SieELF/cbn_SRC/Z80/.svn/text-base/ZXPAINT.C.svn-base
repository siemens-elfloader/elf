
//zxpaint
#include "..\swilib.h"
extern char colors[];

void zxrepaint(char *scrbuf, char *mem){ //экран с поворотом
  const int width8=192<<3, maxx=32;
  int x,y,xx,yy,yyy, col1, col2, col3, pal=22528;
	int b, off=16384, off2, off3, scr=192-1, scr2;
	for(yyy=0; yyy<3; yyy++){
	  off3=off;
  	  for(yy=0; yy<8; yy++){
  	    off2=off; scr2=scr;
	    for(xx=0;xx<32;xx++){
	      b=mem[pal++];
	      col3=(b>>3)&0x08;
	      col1=colors[(b & 0x07)|col3];
	      col2=colors[((b>>3)&0x07)|col3];
              for(y=0;y<8;y++){
                b=mem[off];
	        for(x=0;x<8;x++,scr+=192){
	          scrbuf[scr]=((b & 0x80)!=0)?col1:col2;
	          b<<=1;
	        } //x
	        off+=256;
	        scr-=(width8)+1;
	      } //y
	      off-=2047;//(256*8-1);
	      scr+=(width8)+8;
	    } //xx
	    off=off2+32;
	    pal+=32-maxx;
	    scr=scr2-8;
	  } //yy
	  //dminy=0;
	  off=off3+2048;//256*8;
	}
 
}

void zxelpaint(char *s, char *ss){ //for EL
  int j;
  s+=22*240+24;
  for(j=0;j<256;j++){
    memcpy(s,ss,192);
    s+=240;
    ss+=192;
  }
}

void zx65paint(char *s, char *ss){
  int i,j,k=0;
  s+=3*132+2;
  for(j=0;j<170;j++){
    for(i=0;i<64;i++){
      *s++=*ss++;
      *s++=*ss;
      ss+=2;
    }
    s+=4;
    if(++k>2){ k=0; ss+=192;}
  }
}
