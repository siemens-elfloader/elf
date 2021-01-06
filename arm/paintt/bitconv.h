
//inline char rgb_24_8(int color){return ((color>>6)&3)|((color>>11)&0x1C)|((color>>16)&0xE0); }
//inline short rgb_24_16(int color){return ((color>>3)&0x1f)|((color>>5)&0x7e0)|((color>>8)&0xf800); }
//inline char rgb_16_8(short color){return ((color>>3)&3)|((color>>6)&0x1C)|((color>>8)&0xE0); }

inline char BGR_24_8(char *clr) {return((clr[2]&0xE0)|((clr[1]>>3)&0x1C)|((clr[0]>>6)&0x03));}
inline char RGB_24_8(char *clr) {return((clr[0]&0xE0)|((clr[1]>>3)&0x1C)|((clr[2]>>6)&0x03));}

inline short BGR_24_16(char *clr) {return(((clr[2]<<8)&0xF800)|((clr[1]<<3)&0x07E0)|((clr[0]>>3)&0x001F));}
inline short RGB_24_16(char *clr) {return(((clr[0]<<8)&0xF800)|((clr[1]<<3)&0x07E0)|((clr[2]>>3)&0x001F));}

inline short BGR_24_555(char *clr) {return(((clr[2]<<7)&0x7C00)|((clr[1]<<2)&0x03E0)|((clr[0]>>3)&0x001F));}
inline short RGB_24_555(char *clr) {return(((clr[0]<<7)&0x7C00)|((clr[1]<<2)&0x03E0)|((clr[2]>>3)&0x001F));}

inline int RGBA_BGRA(char *clr) {return((clr[3]<<24)+(clr[0]<<16)+(clr[1]<<8)+(clr[2]));}

inline int _16_BGR_32(char *clr)
{
	short c2=clr[0]+clr[1]*0x100;
	return((0xFF<<24)+((c2&0x001F)<<19)+((c2&0x07E0)<<5)+((c2&0xF800)>>8));
}

inline void img_32_8(char *tobuf, char *frombuf, int sz, char bgcol)
{
	unsigned int i;
	char c1;
	//if(sz<0){sz=-sz; tobuf=malloc(sz);}
	for(i=0; i<sz; i++)
	{
		if(frombuf[i*4+3]>25)
		{
			c1=BGR_24_8(frombuf+i*4);
			memcpy(tobuf+i, &c1, 1);
		}
	}
}

inline void img_32_16(char *tobuf, char *frombuf, int sz, short bgcol, short type)
{
	unsigned int i;
	unsigned short c2;
	//if(sz<0){sz=-sz; tobuf=malloc(sz*2);}
	if(type==555)
	{
		for(i=0; i<sz; i++)
		{
			if(frombuf[i*4+3]>25)
			{
				c2=BGR_24_555(frombuf+i*4);
				memcpy(tobuf+i*2, &c2, 2);
			}
		}
	}
	else
	{
		for(i=0; i<sz; i++)
		{
			if(frombuf[i*4+3]>25)
			{
				c2=BGR_24_16(frombuf+i*4);
				memcpy(tobuf+i*2, &c2, 2);
			}
		}
	}
}

inline void img_32_24( char *tobuf, char *frombuf, int sz, char *bgcol)
{
	unsigned int i;
	//if(sz<0){sz=-sz; tobuf=malloc(sz*4);}
	for(i=0; i<sz; i++)
	{
		if(frombuf[i*4+3]>25) memcpy(tobuf+i*3, frombuf+i*4, 3);
		//else memcpy(tobuf+i*3, bgcol, 3);
	}
}



/* Приём.Blue=alpha* Источн.Blue+(1-alpha)* Приём.Blue
Приём.Green=alpha* Источн.Green+(1-alpha)* Приём.Green
Приём.Red=alpha* Источн.Red+(1-alpha)* Приём.Red
Приём.alpha=alpha* Источн.alpha+(1-alpha)* Приём.alpha


pr0=r1-(r1-r0)*a0
r0=pr0+(r1-pr0)*a1 */

inline void img_32_a(char *tobuf, PIC_PARAM *pp, char z)
{
	unsigned int i, j, k, zi, zj, xy;
	char qq;
	//int dc;
	//char *tmpbuf=malloc(pp.sz*4);
	//zeromem(tobuf, pp->sz*4);
	if(z==0)
	{
	  for(k=0; k<pp->cs; k++)
	   if(pp->sl[k].v)
		for(i=0; i<pp->sz; i++)
		{
			//tobuf[i*4]  = tobuf[ i*4 ]+((pp->sl[k].map[ i*4 ]-tobuf[ i*4 ])*pp->sl[k].map[i*4+3])/0xff;
			//tobuf[i*4+1]= tobuf[i*4+1]+((pp->sl[k].map[i*4+1]-tobuf[i*4+1])*pp->sl[k].map[i*4+3])/0xff;
			//tobuf[i*4+2]= tobuf[i*4+2]+((pp->sl[k].map[i*4+2]-tobuf[i*4+2])*pp->sl[k].map[i*4+3])/0xff;
			//tobuf[i*4+3]= tobuf[i*4+3]+((0xff-tobuf[i*4+3])*pp->sl[k].map[i*4+3])/0xff;
			
			qq=pp->sl[k].map[ i*4 ]-((pp->sl[k].map[ i*4 ]-tobuf[ i*4 ])*tobuf[i*4+3])/0xff;
			tobuf[ i*4 ]=qq+((pp->sl[k].map[ i*4 ]-qq)*pp->sl[k].map[i*4+3])/0xff;
			qq=pp->sl[k].map[i*4+1]-((pp->sl[k].map[i*4+1]-tobuf[i*4+1])*tobuf[i*4+3])/0xff;
			tobuf[i*4+1]=qq+((pp->sl[k].map[i*4+1]-qq)*pp->sl[k].map[i*4+3])/0xff;
			qq=pp->sl[k].map[i*4+2]-((pp->sl[k].map[i*4+2]-tobuf[i*4+2])*tobuf[i*4+3])/0xff;
			tobuf[i*4+2]=qq+((pp->sl[k].map[i*4+2]-qq)*pp->sl[k].map[i*4+3])/0xff;
			tobuf[i*4+3]= tobuf[i*4+3]+((0xff-tobuf[i*4+3])*pp->sl[k].map[i*4+3])/0xff;
		}
	}
	else
	{
	   for(k=0; k<pp->cs; k++)
		if(pp->sl[k].v)
		 for(j=0; j<pp->h; j++)
		  for(i=0; i<pp->w; i++)
		   for(zj=0; zj<z+1; zj++)
			for(zi=0; zi<z+1; zi++)
			{
				xy=(((j*(z+1)+zj)*pp->w*(z+1))+(i*(z+1)+zi))*4;
				qq=pp->sl[k].map[ (j*p->w+i)*4 ]-((pp->sl[k].map[ (j*p->w+i)*4 ]-tobuf[ xy ])*tobuf[xy+3])/0xff;
				tobuf[ xy ]=qq+((pp->sl[k].map[ (j*p->w+i)*4 ]-qq)*pp->sl[k].map[(j*p->w+i)*4+3])/0xff;
				qq=pp->sl[k].map[(j*p->w+i)*4+1]-((pp->sl[k].map[(j*p->w+i)*4+1]-tobuf[xy+1])*tobuf[xy+3])/0xff;
				tobuf[xy+1]=qq+((pp->sl[k].map[(j*p->w+i)*4+1]-qq)*pp->sl[k].map[(j*p->w+i)*4+3])/0xff;
				qq=pp->sl[k].map[(j*p->w+i)*4+2]-((pp->sl[k].map[(j*p->w+i)*4+2]-tobuf[xy+2])*tobuf[xy+3])/0xff;
				tobuf[xy+2]=qq+((pp->sl[k].map[(j*p->w+i)*4+2]-qq)*pp->sl[k].map[(j*p->w+i)*4+3])/0xff;
				tobuf[xy+3]= tobuf[xy+3]+((0xff-tobuf[xy+3])*pp->sl[k].map[(j*p->w+i)*4+3])/0xff;
			}
	}
	//img_32_16_a(tobuf, tmpbuf, pp.sz, bgcol, 0);
}



