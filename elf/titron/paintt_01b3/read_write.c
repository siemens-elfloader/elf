
#define RES_OK		1
#define FAIL_OPEN	2
#define DO_REWR		3
#define N_FORMAT	10
#define N_PTI_VER	12

static const char *save_ext[]={"pti","bmp"};

struct{
	unsigned int sz;
	char *map;
}PALLETE;

void img_from_8_pallete(char *map)
{
	unsigned int i, j;
	sl[1].p.bitmap=malloc(p1.sz*4);
	for(i=p1.h; i>0; i--)
	{
	  for(j=0; j<p1.w; j++)
	  {
		memcpy(sl[1].p.bitmap+((i-1)*p1.w+j)*4, PALLETE.map+map[(p1.h-i)*p1.w+j]*4, 3);
		sl[1].p.bitmap[((i-1)*p1.w+j)*4+3]=0xff;
	  }
	}
}

void img_from_16(char *map)
{
	unsigned int i, j;
	unsigned short c2;
	char c32[4]={0,0,0,0xff};
	sl[1].p.bitmap=malloc(p1.sz*4);
	for(i=p1.h; i>0; i--)
	{
	  for(j=0; j<p1.w; j++)
	  {
		c2=map[((p1.h-i)*p1.w+j)*2]+map[((p1.h-i)*p1.w+j)*2+1]*0x100;
		c32[2] = (c2 & 0xF800) >> 8;
	    c32[1] = (c2 & 0x07E0) >> 3;
		c32[0] = (c2 & 0x001F) << 3;
		memcpy(sl[1].p.bitmap+((i-1)*p1.w+j)*4, c32, 4);
		//sl[1].p.bitmap[((i-1)*p1.w+j)*4+3]=0xff;
	  }
	}
}

void img_from_24(char *map)
{
	unsigned int i, j;
	sl[1].p.bitmap=malloc(p1.sz*4);
	for(i=p1.h; i>0; i--)
	{
	  for(j=0; j<p1.w; j++)
	  {
		memcpy(sl[1].p.bitmap+((i-1)*p1.w+j)*4, map+((p1.h-i)*p1.w+j)*3, 3);
		sl[1].p.bitmap[((i-1)*p1.w+j)*4+3]=0xff;
	  }
	}
}

void img_from_32(char *map)
{
	unsigned int i;
	sl[1].p.bitmap=malloc(p1.sz*4);
	for(i=0; i<p1.sz; i++)
	{
		memcpy(sl[1].p.bitmap+i*4, map+i*4, 3);
		sl[1].p.bitmap[i*4+3]=0xff;
	}
}

int readBMP(const char *filename)
{
	BMP_HDR rBMP;
	int f, result;
	char *bmap;
	unsigned short sig;
	unsigned int ul, i, k;//, wrsz=0;
	if ((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
	{
		fread(f,&sig,2,&ul);
		fread(f,&rBMP,52,&ul);
		//if((rBMP.biCompression!=0)||(rBMP.biPlanes!=1)) {fclose(f,&ul); return N_FORMAT;}
		p1.w=rBMP.Width;
		p1.h=rBMP.Height;
		p1.sz=p1.h*p1.w;
		switch(rBMP.biBitCount)
		{
			case 8:
				if(!rBMP.biClrUsed) {fclose(f,&ul); return N_FORMAT;}
				PALLETE.sz=rBMP.biClrUsed;
				PALLETE.map=malloc(PALLETE.sz*4);
				fread(f,PALLETE.map,PALLETE.sz*4,&ul);
				lseek(f, rBMP.offbits, S_SET, &ul, &ul);
				bmap=malloc(p1.sz+3);
				k=p1.w;
				if(p1.w%4) k=k+4-(p1.w%4);
				for(i=0; i<p1.h; i++)
					fread(f,bmap+p1.w*i,k,&ul);
				img_from_8_pallete(bmap);
			  break;
			case 16:
				lseek(f, rBMP.offbits, S_SET, &ul, &ul);
				bmap=malloc(p1.sz*2+3);
				k=(p1.w*2);
				if((p1.w*2)%4) k=k+4-((p1.w*2)%4);
				for(i=0; i<p1.h; i++)
					fread(f,bmap+p1.w*2*i,k,&ul);
				img_from_16(bmap);
			  break;
			case 24:
				lseek(f, rBMP.offbits, S_SET, &ul, &ul);
				bmap=malloc(p1.sz*3+3);
				k=(p1.w*3);
				if((p1.w*3)%4) k=k+4-((p1.w*3)%4);
				for(i=0; i<p1.h; i++)
					fread(f,bmap+p1.w*3*i,k,&ul);
				img_from_24(bmap);
			  break;
			case 32:
				lseek(f, rBMP.offbits, S_SET, &ul, &ul);
				bmap=malloc(p1.sz*4);
				for(i=p1.h; i>0; i--)
					fread(f,bmap+p1.w*4*(i-1),p1.w*4,&ul);
				img_from_32(bmap);
			  break;
			default:
				fclose(f,&ul);
			  return N_FORMAT;
		}
		result=RES_OK;
	}
	else result=FAIL_OPEN;
	mfree(bmap);
	sl[1].v=sl[0].v=1;
	sl[0].p.bitmap=malloc(p1.sz*4);
	zeromem(sl[0].p.bitmap, p1.sz*4);
	p1.sl_cnt=2;
	p1.ac_sl=1;
	p1.inst=0;
	fclose(f,&ul);
	return result;
}


int readPTI(const char *filename)
{
	int f, result;
	unsigned short sig;
	unsigned int ul, i;//, wrsz=0;
	if ((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
	{
		fread(f,&sig,4,&ul);
		fread(f,&p1,sizeof(PIC_PARAM),&ul);
		for(i=0; i<p1.sl_cnt; i++)
		{
			fread(f,&sl[i],sizeof(SLOY)-4,&ul);
			sl[i].p.bitmap=malloc(sl[i].p.w*sl[i].p.h*4);
			fread(f,sl[i].p.bitmap,sl[i].p.w*sl[i].p.h*4,&ul);
		}
		result=RES_OK;
	}
	else result=FAIL_OPEN;
	fclose(f,&ul);
	return result;
}

int read_file(const char *filename)
{
	int f;
	unsigned short sig;
	unsigned int ul;//, i;//, wrsz=0;
	if ((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
	{
		fread(f,&sig,2,&ul);
		switch(sig)
		{
			case 0x4d42:
				fclose(f,&ul);
				return(readBMP(filename));
			case 'P'+'T'*0x100:
				fread(f,&sig,2,&ul);
				if(sig==PTI_ver)
				{
					fclose(f,&ul);
					return(readPTI(filename));
				}
				else
				{
					fclose(f,&ul);
					return(N_PTI_VER);
				}
		}
	}
	fclose(f,&ul);
	return N_FORMAT;
}



/////////////////////////////////// Сохранение ///////////////////////////



int CrName() // создание полного имени файла
{
	int f, i;
	unsigned int ul;
	TDate date;
	TTime time; 
	GetDateTime(&date,&time);
	//char w[32];
	
	
	if(strlen(SAVEp.nm)==0) sprintf( SAVEp.nm, "pic_%02i%02i-%i%02i%02i", date.month,date.day, time.hour,time.min,time.sec );
	//else strcpy(bmpsname,fnm);//sprintf( bmpsname, perc_t, fnm);
	strcpy(fname,SAVE_PATH);
	i=strlen(fname);
	if(fname[i-1]=='\\') sprintf( fname+i, "%s.%s", SAVEp.nm, save_ext[SAVEp.type] );
	else sprintf( fname+i, "\\%s.%s", SAVEp.nm, save_ext[SAVEp.type] );

	//unlink(fname,&ul);
	
	if ((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
	{
		fclose(f,&ul);
		rewr=0;
		return DO_REWR;
	}
	else {fclose(f,&ul); return RES_OK;}
	//return 1;
}

void do_nosl()
{
	unsigned int i,k;
	zeromem(tmp_sl.p.bitmap, tmp_sl.p.w*tmp_sl.p.h*4);
	for(k=1; k<p1.sl_cnt; k++)
	 if(sl[k].v)
	   for(i=0; i<tmp_sl.p.w*tmp_sl.p.h; i++)
		if(sl[k].p.bitmap[i*4+3]>25)
			memcpy(tmp_sl.p.bitmap+i*4, sl[k].p.bitmap+i*4, 4);
}

void writePTI()
{
	unsigned int ul, i;
	int f;
		if ((f=fopen(fname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
		{
			fwrite(f,&PTI_id,2,&ul);
			fwrite(f,&PTI_ver,2,&ul);
			if(!SAVEp.bit)
			{
				fwrite(f,&p1,sizeof(PIC_PARAM),&ul);
				for(i=0; i<p1.sl_cnt; i++)
				{
					fwrite(f,&sl[i],sizeof(SLOY)-4,&ul);
					fwrite(f,sl[i].p.bitmap,sl[i].p.w*sl[i].p.h*4,&ul);
					if(i<p1.sl_cnt-1)
					{
						gipc.name_to=ipc_my_name;
						gipc.name_from=ipc_my_name;
						gipc.data=0;
						GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_SAVE_PART,&gipc);
					}
				}
			}
			else
			{
				tmp_p=p1;
				tmp_p.sl_cnt=2;
				tmp_p.ac_sl=1;
				memcpy(&tmp_sl, &sl[0], sizeof(SLOY)-4);
				sprintf( tmp_sl.nm, "SLOY 1" );
				tmp_sl.p.bitmap=malloc(tmp_sl.p.w*tmp_sl.p.h*4);
				do_nosl();
				fwrite(f,&tmp_p,sizeof(PIC_PARAM),&ul);
				fwrite(f,&sl[0],sizeof(SLOY)-4,&ul);
				fwrite(f,sl[0].p.bitmap,tmp_sl.p.w*tmp_sl.p.h*4,&ul);
				fwrite(f,&tmp_sl,sizeof(SLOY)-4,&ul);
				fwrite(f,tmp_sl.p.bitmap,tmp_sl.p.w*tmp_sl.p.h*4,&ul);
				mfree(tmp_sl.p.bitmap);
			}
			fclose(f,&ul);
		}
	gipc.name_to=ipc_my_name;
	gipc.name_from=ipc_my_name;
	gipc.data=0;
	GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_SAVE_FINISHED,&gipc);
}

int savePTI(int prm)
{
	int f;
	int result;
	unsigned int ul;//, wrsz=0;
	result=CrName();
	if(prm||(result==RES_OK))
	{
		if ((f=fopen(fname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
		{
			fclose(f,&ul);
			SAVEp.parts=p1.sl_cnt-1;
			SUBPROC((void*)writePTI);
			return RES_OK;
		}
		else result=FAIL_OPEN;
		fclose(f,&ul);
	}
	return result;
}



void do_pallete()
{
	unsigned int i, k, j, j0, j1=0, j2=0;
	PALLETE.sz=1;
	PALLETE.map=malloc(1024);
	zeromem( PALLETE.map, 1024);
	memcpy( PALLETE.map, white0, 4 );
	for(i=0; i<p1.sz; i++ )
	{
		k=p1.sl_cnt;
		while(k)
		{
			k--;
			if((char)sl[k].p.bitmap[i*4+3]>=25)
			{
				memcpy(&j1, sl[k].p.bitmap+i*4, 3);
				j0=0;
				for(j=0; j<PALLETE.sz; j++)
				{
					memcpy(&j2, PALLETE.map+j*4, 3);
					if(!(j1-j2)) j0++;
				}
				if(!j0)
				{
					memcpy(PALLETE.map+PALLETE.sz*4, sl[k].p.bitmap+i*4, 3);
					PALLETE.map[PALLETE.sz*4+3]=0;
					PALLETE.sz++;
					k=0;
				}
			}
		}
	}
}



void do_bmp_map(char *buf, int nstr)
{
	unsigned int i,k, j, j1=0, j2=0;
	unsigned short c2;
	switch(SAVEp.bit)
	{
// 8 bit pallete
		case 0:
			if(sl[0].v)
			  for(i=0; i<p1.w; i++ )
				if((char)sl[0].p.bitmap[((p1.h-nstr-1)*p1.w+i)*4+3]>=25)
				{
					memcpy(&j1, sl[0].p.bitmap+((p1.h-nstr-1)*p1.w+i)*4, 3);
					for(j=0; j<PALLETE.sz; j++)
					{
						memcpy(&j2, PALLETE.map+j*4, 3);
						if(j1==j2)
						{
							buf[i]=j;
							j=PALLETE.sz;
						}
					}
				}
			else for(i=0; i<p1.w; i++ ) buf[i]=0;
			
			for(k=1; k<p1.sl_cnt; k++)
			  if(sl[k].v)
				for(i=0; i<p1.w; i++ )
					if((char)sl[k].p.bitmap[((p1.h-nstr-1)*p1.w+i)*4+3]>=25)
					{
						memcpy(&j1, sl[k].p.bitmap+((p1.h-nstr-1)*p1.w+i)*4, 3);
						for(j=0; j<PALLETE.sz; j++)
						{
							memcpy(&j2, PALLETE.map+j*4, 3);
							if(!(j1-j2))
							{
								buf[i]=j;
								j=PALLETE.sz;
							}
						}
					}
			
		 break;

// 16 bit
		case 1:
			  if(sl[0].v)
				for(i=0; i<p1.w; i++ )
				  if((char)sl[0].p.bitmap[((p1.h-nstr-1)*p1.w+i)*4+3]<25)
				  {
						c2=0xffff;
						memcpy(buf+i*2, &c2, 2);
				  }
				  else
				  {
						c2=((sl[0].p.bitmap[((p1.h-nstr-1)*p1.w+i)*4+2]<<8)&0xF800);
						c2|=((sl[0].p.bitmap[((p1.h-nstr-1)*p1.w+i)*4+1]<<3)&0x7E0);
						c2|=((sl[0].p.bitmap[((p1.h-nstr-1)*p1.w+i)*4+0]>>3)&0x1F);
						memcpy(buf+i*2, &c2, 2);
				  }
			  else
				for(i=0; i<p1.w; i++ )
				{
					c2=0xffff;
					memcpy(buf+i*2, &c2, 2);
				}
			for(k=1; k<p1.sl_cnt; k++)
			  if(sl[k].v)
				for(i=0; i<p1.w; i++ )
				  if((char)sl[k].p.bitmap[((p1.h-nstr-1)*p1.w+i)*4+3]>=25)
				  {
						c2=((sl[k].p.bitmap[((p1.h-nstr-1)*p1.w+i)*4+2]<<8)&0xF800);
						c2|=((sl[k].p.bitmap[((p1.h-nstr-1)*p1.w+i)*4+1]<<3)&0x7E0);
						c2|=((sl[k].p.bitmap[((p1.h-nstr-1)*p1.w+i)*4+0]>>3)&0x1F);
						memcpy(buf+i*2, &c2, 2);
				  }
		 break;

// 24 bit
		case 2:
			  if(sl[0].v)
				for(i=0; i<p1.w; i++ )
				  if((char)sl[0].p.bitmap[((p1.h-nstr-1)*p1.w+i)*4+3]<25) memcpy( buf+i*3, white, 3 );
				  else memcpy( buf+i*3, sl[0].p.bitmap+((p1.h-nstr-1)*p1.w+i)*4, 3 );
			  else
				for(i=0; i<p1.w; i++ )
				  memcpy( buf+i*3, white, 3 );
			for(k=1; k<p1.sl_cnt; k++)
			  if(sl[k].v)
				for(i=0; i<p1.w; i++ )
				  if((char)sl[k].p.bitmap[((p1.h-nstr-1)*p1.w+i)*4+3]>=25) memcpy( buf+i*3, sl[k].p.bitmap+((p1.h-nstr-1)*p1.w+i)*4, 3 );
		 break;

// 32 bit
		case 3:
			  if(sl[0].v)
				for(i=0; i<p1.w; i++ )
				  if((char)sl[0].p.bitmap[((p1.h-nstr-1)*p1.w+i)*4+3]>=25) 
					memcpy( buf+i*4, sl[0].p.bitmap+((p1.h-nstr-1)*p1.w+i)*4, 4 );
				  else
					memcpy( buf+i*4, white, 4 );
			  else
				for(i=0; i<p1.w; i++ )
					memcpy( buf+i*4, white, 4 );
			for(k=1; k<p1.sl_cnt; k++)
			  if(sl[k].v)
				for(i=0; i<p1.w; i++ )
				  if((char)sl[k].p.bitmap[((p1.h-nstr-1)*p1.w+i)*4+3]>=25) 
					memcpy( buf+i*4, sl[k].p.bitmap+((p1.h-nstr-1)*p1.w+i)*4, 4 );
		 break;
	}
	
	
	// for(k=1; k<p1.sl_cnt; k++)
	 // if(sl[k].v)
	   // for(i=0; i<tmp_sl.p.w*tmp_sl.p.h; i++)
		// if(sl[k].p.bitmap[i*4+3]>25)
			// memcpy(tmp_sl.p.bitmap+i*4, sl[k].p.bitmap+(p1.h-i-1)*4*p1.w, 4*p1.w );
}

BMP_HDR wrBMP;

void writeBMP()
{
	int f;
	unsigned int i, ul, bufsz=p1.w*(wrBMP.biBitCount/8);
	i=bufsz%4;
	if(i) bufsz+=4-i;
	char *wrbuf=malloc(bufsz);
	zeromem(wrbuf, bufsz);
		if ((f=fopen(fname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
	    {
	      fwrite(f,&BMP_id,2,&ul);
	      fwrite(f,&wrBMP,52,&ul);
		  if(!SAVEp.bit) fwrite(f,PALLETE.map,PALLETE.sz*4,&ul);
		  for(i=0; i<p1.h; i++)
		  {
			do_bmp_map( wrbuf, i );
			fwrite(f,wrbuf,bufsz,&ul);
			// if(i<p1.h-1)
			// {
				// gipc.name_to=ipc_my_name;
				// gipc.name_from=ipc_my_name;
				// gipc.data=0;
				// GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_SAVE_PART,&gipc);
			// }
		  }
	    }
	if(!SAVEp.bit) mfree(PALLETE.map);
	mfree(wrbuf);
	fclose(f,&ul);
	gipc.name_to=ipc_my_name;
	gipc.name_from=ipc_my_name;
	gipc.data=0;
	GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_SAVE_FINISHED,&gipc);
}

int saveBMP(int prm)
{
	int result, f;
	unsigned int ul;
	result=CrName();
	if(prm||(result==RES_OK))
	{
		if ((f=fopen(fname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
		{
			fclose(f,&ul);
			wrBMP=Def_BMP;
			wrBMP.Width=p1.w;
			wrBMP.Height=p1.h;
			switch(SAVEp.bit)
			{
				case 0:	// 8 bit pallete
					do_pallete();
					wrBMP.size=p1.sz+54+PALLETE.sz*4;
					wrBMP.offbits=54+PALLETE.sz*4;
					wrBMP.biBitCount=8;
					wrBMP.biClrUsed=PALLETE.sz;
					wrBMP.biClrImportant=PALLETE.sz;
				 break;
				case 1:	// 16 bit
					wrBMP.size=p1.sz*2+54;
					wrBMP.biBitCount=16;
					wrBMP.biClrUsed=0;
					wrBMP.biClrImportant=0;
				 break;
				case 2:	// 24 bit
					wrBMP.size=p1.sz*3+54;
					wrBMP.biBitCount=24;
					wrBMP.biClrUsed=0;
					wrBMP.biClrImportant=0;
				 break;
				case 3:	// 32 bit
					wrBMP.size=p1.sz*4+54;
					wrBMP.biBitCount=32;
					wrBMP.biClrUsed=0;
					wrBMP.biClrImportant=0;
					//for(i=0; i<p1.h; i++) memcpy(wrpicmap+i*p1.w*4, premap+premsz-(i+1)*p1.w*4, p1.w*4);
				 break;
			}
			SAVEp.parts=p1.h;
			SUBPROC((void*)writeBMP);
			return RES_OK;
		}
		else result=FAIL_OPEN;
		fclose(f,&ul);
	}
	return result;
}

