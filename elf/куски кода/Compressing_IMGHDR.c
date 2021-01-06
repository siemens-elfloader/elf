
// compressing bitmap of IMGHDR struct

void PressImg(IMGHDR *imgsrc, char freemap) // freemap=1 if need mfree(imgsrc->bitmap)
{
  // проверка
	if(!imgsrc) return;
	if(!imgsrc->bitmap) return;
	char c=0;
	switch(imgsrc->bpnum) // формат изображения:
	{
	 case 5: c=1; break; // 8-битный
	 case 8: c=2; break; // 16-битный
	 case 0xA: c=4; break; // 32-битный
	 default: return; // уже сжатый или другой, прерывание функции
	}
	imgsrc->bpnum+=0x80;

  // само сжатие
	int cps=0, tsz;
	unsigned int tc[2];
	unsigned int tmpBufsz=0;
	char *tmpBuf=malloc(imgsrc->h*imgsrc->w*(c+1)); // временный буфер 
	zeromem(tmpBuf, imgsrc->h*imgsrc->w*(c+1));
	while(cps<imgsrc->h*imgsrc->w)
	{
		tsz=0;
		tc[0]=0;
		tc[1]=0;
		memcpy(&tc[0], imgsrc->bitmap+cps*c, c);
		memcpy(&tc[1], imgsrc->bitmap+cps*c+c, c);
		if((tc[0]==tc[1]))
		{
			do
			{
				tsz++;
				tc[0]=0;
				tc[1]=0;
				memcpy(&tc[0], imgsrc->bitmap+(tsz+cps)*c, c);
				memcpy(&tc[1], imgsrc->bitmap+(tsz+cps)*c+c, c);
			}while((tc[0]==tc[1]) && (tsz<127) && ((tsz+cps)<imgsrc->h*imgsrc->w));
			tmpBuf[tmpBufsz]=tsz;
			memcpy(tmpBuf+tmpBufsz+1, imgsrc->bitmap+cps*c, c);
			tmpBufsz+=c+1;
		}
		else
		{
			do
			{
				tsz++;
				tc[0]=0;
				tc[1]=0;
				memcpy(&tc[0], imgsrc->bitmap+(tsz+cps)*c, c);
				memcpy(&tc[1], imgsrc->bitmap+(tsz+cps)*c+c, c);
			}while((tc[0]!=tc[1]) && (tsz<127) && ((tsz+cps)<imgsrc->h*imgsrc->w));
			tmpBuf[tmpBufsz]=0x100-tsz;
			memcpy(tmpBuf+tmpBufsz+1, imgsrc->bitmap+cps*c, tsz*c);
			tmpBufsz+=tsz*c+1;
		}
		cps+=tsz;
	}
	char *buf2=malloc(tmpBufsz);
	memcpy(buf2,tmpBuf,tmpBufsz);
	if(freemap) mfree(imgsrc->bitmap);
	imgsrc->bitmap=buf2;
	mfree(tmpBuf);
}

