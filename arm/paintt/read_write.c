
#define RES_OK		1
#define FAIL_OPEN	2
#define DO_REWR		3
#define N_FORMAT	10
#define OVER_COLCNT	12
#define N_PTI_VER	12

struct{
	unsigned int sz;
	char *map;
}PALLETE;

void img_from_8_pallete(char *map)
{
	unsigned int i, j;
	p->sl[1].map=malloc(p->sz*4);
	for(i=p->h; i>0; i--)
	{
	  for(j=0; j<p->w; j++)
	  {
		memcpy(p->sl[1].map+((i-1)*p->w+j)*4, PALLETE.map+map[(p->h-i)*p->w+j]*4, 3);
		p->sl[1].map[((i-1)*p->w+j)*4+3]=0xff;
	  }
	}
}

void img_from_16(char *map)
{
	unsigned int i, j;
	unsigned short c2;
	char c32[4]={0,0,0,0xff};
	p->sl[1].map=malloc(p->sz*4);
	for(i=p->h; i>0; i--)
	{
	  for(j=0; j<p->w; j++)
	  {
		c2=map[((p->h-i)*p->w+j)*2]+map[((p->h-i)*p->w+j)*2+1]*0x100;
		c32[2] = (c2 & 0xF800) >> 8;
	    c32[1] = (c2 & 0x07E0) >> 3;
		c32[0] = (c2 & 0x001F) << 3;
		memcpy(p->sl[1].map+((i-1)*p->w+j)*4, c32, 4);
		//p->sl[1].map[((i-1)*p->w+j)*4+3]=0xff;
	  }
	}
}

void img_from_24(char *map)
{
	unsigned int i, j;
	p->sl[1].map=malloc(p->sz*4);
	for(i=p->h; i>0; i--)
	{
	  for(j=0; j<p->w; j++)
	  {
		memcpy(p->sl[1].map+((i-1)*p->w+j)*4, map+((p->h-i)*p->w+j)*3, 3);
		p->sl[1].map[((i-1)*p->w+j)*4+3]=0xff;
	  }
	}
}

void img_from_32(char *map)
{
	unsigned int i;
	p->sl[1].map=malloc(p->sz*4);
	for(i=0; i<p->sz; i++)
	{
		memcpy(p->sl[1].map+i*4, map+i*4, 3);
		p->sl[1].map[i*4+3]=0xff;
	}
}

int readBMP(const char *filename)
{
	BMP_HDR rBMP;
	int f, result;
	char *bmap;
	unsigned short sig;
	unsigned int ul, i, k;//, wrsz=0;
	//p=&picp[Pt.np];
	if ((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
	{
		fread(f,&sig,2,&ul);
		fread(f,&rBMP,52,&ul);
		//if((rBMP.biCompression!=0)||(rBMP.biPlanes!=1)) {fclose(f,&ul); return N_FORMAT;}
		p->w=rBMP.img.biWidth;
		p->h=rBMP.img.biHeight;
		p->sz=p->h*p->w;
		switch(rBMP.img.biBitCount)
		{
			case 8:
				if(!rBMP.img.biClrUsed) {fclose(f,&ul); return N_FORMAT;}
				PALLETE.sz=rBMP.img.biClrUsed;
				PALLETE.map=malloc(PALLETE.sz*4);
				fread(f,PALLETE.map,PALLETE.sz*4,&ul);
				lseek(f, rBMP.bmp.offbits, S_SET, &ul, &ul);
				bmap=malloc(p->sz+3);
				k=p->w;
				if(p->w%4) k=k+4-(p->w%4);
				for(i=0; i<p->h; i++)
					fread(f,bmap+p->w*i,k,&ul);
				img_from_8_pallete(bmap);
			  break;
			case 16:
				lseek(f, rBMP.bmp.offbits, S_SET, &ul, &ul);
				bmap=malloc(p->sz*2+3);
				k=(p->w*2);
				if((p->w*2)%4) k=k+4-((p->w*2)%4);
				for(i=0; i<p->h; i++)
					fread(f,bmap+p->w*2*i,k,&ul);
				img_from_16(bmap);
			  break;
			case 24:
				lseek(f, rBMP.bmp.offbits, S_SET, &ul, &ul);
				bmap=malloc(p->sz*3+3);
				k=(p->w*3);
				if((p->w*3)%4) k=k+4-((p->w*3)%4);
				for(i=0; i<p->h; i++)
					fread(f,bmap+p->w*3*i,k,&ul);
				img_from_24(bmap);
			  break;
			case 32:
				lseek(f, rBMP.bmp.offbits, S_SET, &ul, &ul);
				bmap=malloc(p->sz*4);
				for(i=p->h; i>0; i--)
					fread(f,bmap+p->w*4*(i-1),p->w*4,&ul);
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
	p->sl[1].v=p->sl[0].v=1;
	p->sl[1].w=p->sl[0].w=p->w;
	p->sl[1].h=p->sl[0].h=p->h;
	p->sl[0].map=malloc(p->sz*4);
	zeromem(p->sl[0].map, p->sz*4);
	sprintf(p->sl[0].nm, "FON ");
	sprintf(p->sl[1].nm, "SLOY 1 ");
	p->cs=2;
	p->ns=1;
	Pt.i=0;
	fclose(f,&ul);
	return result;
}


int readPTI(const char *filename)
{
	int f, result;
	unsigned short sig;
	unsigned int ul, i;//, wrsz=0;
	//p=&picp[Pt.np];
	if ((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
	{
		fread(f,&sig,4,&ul);
		fread(f,&p->cs,1,&ul);
		fread(f,&p->ns,1,&ul);
		fread(f,&p->w,2,&ul);
		fread(f,&p->h,2,&ul);
		p->sz=p->h*p->w;
		for(i=0; i<p->cs; i++)
		{
			fread(f,&p->sl[i],sizeof(SLOY)-4,&ul);
			p->sl[i].map=malloc(p->sl[i].w*p->sl[i].h*4);
			fread(f,p->sl[i].map,p->sl[i].w*p->sl[i].h*4,&ul);
		}
		result=RES_OK;
	}
	else result=FAIL_OPEN;
	fclose(f,&ul);
	return result;
}


int pic_from_imghdr(IMGHDR *img)
{
	unsigned short c2;
	unsigned int i;
	char c1, c32[4];
	p->w=img->w;
	p->h=img->h;
	p->sz=img->w*img->h;
	p->sl[1].map=malloc(p->sz*4);
	switch(img->bpnum)
	{
		case 5:
			for(i=0; i<img->w*img->h; i++)
			{
				c1=img->bitmap[i];
				if(c1==prz.c8)
				{
					memcpy(p->sl[1].map+i*4, prz.c, 4);
				}
				else
				{
					c32[2] = (c1 & 0xE0);
					c32[1] = (c1 & 0x1C) << 3;
					c32[0] = (c1 & 0x03) << 6;
					memcpy(p->sl[1].map+i*4, c32, 3);
					p->sl[1].map[i*4+3]=0xff;
				}
			}
		 break;
		case 8:
			for(i=0; i<img->w*img->h; i++)
			{
				c2=img->bitmap[i*2]+img->bitmap[i*2+1]*0x100;
				if(c2==prz.c16)
				{
					memcpy(p->sl[1].map+i*4, prz.c, 4);
				}
				else
				{
					c32[2] = (c2 & 0xF800) >> 8;
					c32[1] = (c2 & 0x07E0) >> 3;
					c32[0] = (c2 & 0x001F) << 3;
					memcpy(p->sl[1].map+i*4, c32, 3);
					p->sl[1].map[i*4+3]=0xff;
				}
			}
		 break;
		case 0xA:
			memcpy(p->sl[1].map, img->bitmap, p->sz*4);
		 break;
		default: return FAIL_OPEN;
	}
	mfree(img->bitmap);
	p->sl[1].v=p->sl[0].v=1;
	p->sl[1].w=p->sl[0].w=p->w;
	p->sl[1].h=p->sl[0].h=p->h;
	p->sl[0].map=malloc(p->sz*4);
	zeromem(p->sl[0].map, p->sz*4);
	sprintf(p->sl[0].nm, "FON ");
	sprintf(p->sl[1].nm, "SLOY 1 ");
	p->cs=2;
	p->ns=1;
	Pt.i=0;
	return RES_OK;
}

int readPNG(const char *filename)
{
	int f, result;
	//unsigned short sig;
	unsigned int ul;//, i;
	IMGHDR *tmpimg;
	if ((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
	{
		fclose(f,&ul);
		tmpimg=CreateIMGHDRFromPngFile(filename, 0);
		result=pic_from_imghdr(tmpimg);
		mfree(tmpimg);
	}
	else{ result=FAIL_OPEN;
	fclose(f,&ul);}
	return result;
}

int readGPF(const char *filename, char type)
{
	int f, result, isz, tsz;
	char c1, c32[4];
	signed char cnt;
	unsigned short c2;
	unsigned int ul, i;
	GPF_HDR rgpf;
	GPF2_HDR rgpf2;
	IMGHDR tmpimg;
	if ((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
	{
		lseek(f, 0x10, S_SET, &ul, &ul);
		if(type==0)
		{
			fread(f,&rgpf,0x10,&ul);
			tmpimg.w=rgpf.w;
			tmpimg.h=rgpf.h;
			tmpimg.bpnum=rgpf.type;
		}
		if(type==1)
		{
			fread(f,&rgpf2,0x10,&ul);
			tmpimg.w=rgpf2.w;
			tmpimg.h=rgpf2.h;
			tmpimg.bpnum=rgpf2.type;
		}
		tsz=isz=tmpimg.w*tmpimg.h;
		switch(tmpimg.bpnum)
		{
			case 0x05:
				lseek(f, 0x20, S_SET, &ul, &ul);
				tmpimg.bitmap=malloc(isz);
				fread(f,tmpimg.bitmap,isz,&ul);
				//result=pic_from_imghdr(&tmpimg);
			 break;
			case 0x08:
				lseek(f, 0x20, S_SET, &ul, &ul);
				tmpimg.bitmap=malloc(isz*2);
				fread(f,tmpimg.bitmap,isz*2,&ul);
				//result=pic_from_imghdr(&tmpimg);
			 break;
			case 0x0A:
				lseek(f, 0x20, S_SET, &ul, &ul);
				tmpimg.bitmap=malloc(isz*4);
				fread(f,tmpimg.bitmap,isz*4,&ul);
				//result=pic_from_imghdr(&tmpimg);
			 break;
			case 0x85:
				lseek(f, 0x20, S_SET, &ul, &ul);
				tmpimg.bitmap=malloc(isz);
				tmpimg.bpnum=5;
				do
				{
					fread(f,&cnt,1,&ul);
					if(cnt<0)
					{
						cnt=-cnt;
						fread(f,tmpimg.bitmap+(isz-tsz),cnt,&ul); tsz-=cnt;
					}
					else
					{
						fread(f,&c1,1,&ul);
						for(i=isz-tsz; i<isz-tsz+cnt; i++) tmpimg.bitmap[i]=c1;
						tsz-=cnt;
					}
				}while(tsz>0);
				//result=pic_from_imghdr(&tmpimg);
			 break;
			case 0x88:
				lseek(f, 0x20, S_SET, &ul, &ul);
				tmpimg.bitmap=malloc(isz*2);
				tmpimg.bpnum=8;
				do
				{
					fread(f,&cnt,1,&ul);
					if(cnt<0)
					{
						cnt=-cnt;
						fread(f,tmpimg.bitmap+(isz-tsz)*2,cnt*2,&ul); tsz-=cnt;
					}
					else
					{
						fread(f,&c2,2,&ul);
						for(i=isz-tsz; i<isz-tsz+cnt; i++) memcpy(tmpimg.bitmap+i*2, &c2, 2);
						tsz-=cnt;
					}
				}while(tsz>0);
				//result=pic_from_imghdr(&tmpimg);
			 break;
			case 0x8A:
				lseek(f, 0x20, S_SET, &ul, &ul);
				tmpimg.bitmap=malloc(isz*4);
				tmpimg.bpnum=0xA;
				do
				{
					fread(f,&cnt,1,&ul);
					if(cnt<0)
					{
						cnt=-cnt;
						fread(f,tmpimg.bitmap+(isz-tsz)*4,cnt*4,&ul); tsz-=cnt;
					}
					else
					{
						fread(f,c32,2,&ul);
						for(i=isz-tsz; i<isz-tsz+cnt; i++) memcpy(tmpimg.bitmap+i*4, c32, 4);
						tsz-=cnt;
					}
				}while(tsz>0);
				//result=pic_from_imghdr(&tmpimg);
			 break;
			default: 
				fclose(f,&ul);
			 return N_FORMAT;
		}
		result=pic_from_imghdr(&tmpimg);
		fclose(f,&ul);
	}
	else{ result=FAIL_OPEN;
	fclose(f,&ul);}
	return result;
}


int readDAT(const char *filename, char type)
{
	int f, result, isz, tsz;
	char c1, c32[4];
	signed char cnt;
	unsigned short c2;
	unsigned int ul, i;
	DAT_HDR rdat;
	IMGHDR tmpimg;
	if ((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
	{
		fread(f,&rdat.w,2,&ul);
		fread(f,&rdat.h,2,&ul);
		fread(f,&rdat.type,1,&ul);
		tmpimg.w=rdat.w;
		tmpimg.h=rdat.h;
		tmpimg.bpnum=rdat.type;
		tsz=isz=tmpimg.w*tmpimg.h;
		switch(tmpimg.bpnum)
		{
			case 0x05:
				lseek(f, 5, S_SET, &ul, &ul);
				tmpimg.bitmap=malloc(isz);
				fread(f,tmpimg.bitmap,isz,&ul);
				//result=pic_from_imghdr(&tmpimg);
			 break;
			case 0x08:
				lseek(f, 5, S_SET, &ul, &ul);
				tmpimg.bitmap=malloc(isz*2);
				fread(f,tmpimg.bitmap,isz*2,&ul);
				//result=pic_from_imghdr(&tmpimg);
			 break;
			case 0x0A:
				lseek(f, 5, S_SET, &ul, &ul);
				tmpimg.bitmap=malloc(isz*4);
				fread(f,tmpimg.bitmap,isz*4,&ul);
				//result=pic_from_imghdr(&tmpimg);
			 break;
			case 0x85:
				lseek(f, 5, S_SET, &ul, &ul);
				tmpimg.bitmap=malloc(isz);
				tmpimg.bpnum=5;
				do
				{
					fread(f,&cnt,1,&ul);
					if(cnt<0)
					{
						cnt=-cnt;
						fread(f,tmpimg.bitmap+(isz-tsz),cnt,&ul); tsz-=cnt;
					}
					else
					{
						fread(f,&c1,1,&ul);
						for(i=isz-tsz; i<isz-tsz+cnt; i++) tmpimg.bitmap[i]=c1;
						tsz-=cnt;
					}
				}while(tsz>0);
				//result=pic_from_imghdr(&tmpimg);
			 break;
			case 0x88:
				lseek(f, 5, S_SET, &ul, &ul);
				tmpimg.bitmap=malloc(isz*2);
				tmpimg.bpnum=8;
				do
				{
					fread(f,&cnt,1,&ul);
					if(cnt<0)
					{
						cnt=-cnt;
						fread(f,tmpimg.bitmap+(isz-tsz)*2,cnt*2,&ul); tsz-=cnt;
					}
					else
					{
						fread(f,&c2,2,&ul);
						for(i=isz-tsz; i<isz-tsz+cnt; i++) memcpy(tmpimg.bitmap+i*2, &c2, 2);
						tsz-=cnt;
					}
				}while(tsz>0);
				//result=pic_from_imghdr(&tmpimg);
			 break;
			case 0x8A:
				lseek(f, 5, S_SET, &ul, &ul);
				tmpimg.bitmap=malloc(isz*4);
				tmpimg.bpnum=0xA;
				do
				{
					fread(f,&cnt,1,&ul);
					if(cnt<0)
					{
						cnt=-cnt;
						fread(f,tmpimg.bitmap+(isz-tsz)*4,cnt*4,&ul); tsz-=cnt;
					}
					else
					{
						fread(f,c32,2,&ul);
						for(i=isz-tsz; i<isz-tsz+cnt; i++) memcpy(tmpimg.bitmap+i*4, c32, 4);
						tsz-=cnt;
					}
				}while(tsz>0);
				//result=pic_from_imghdr(&tmpimg);
			 break;
			default: 
				fclose(f,&ul);
			 return N_FORMAT;
		}
		result=pic_from_imghdr(&tmpimg);
		fclose(f,&ul);
	}
	else{ result=FAIL_OPEN;
	fclose(f,&ul);}
	return result;
}


int read_file(const char *filename)
{
	int f;
	unsigned short sig, i=strlen(filename);
	unsigned int ul;
	do
	{
		i--;
	}while(filename[i]!='\\');
	p=&picp[Pt.np];
	sprintf(p->nm, perc_s, filename+i+1);
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
			case 0x89+'P'*0x100:
				fread(f,&sig,2,&ul);
				if(sig=='N'+'G'*0x100)
				{
					fclose(f,&ul);
					return(readPNG(filename));
				}
			 break;
			case 'G'+'r'*0x100:
				lseek(f, 14, S_SET, &ul, &ul);
				fread(f,&sig,2,&ul);
				if(sig=='l'+'e'*0x100)
				{
					fclose(f,&ul);
					return(readGPF(filename,0));
				}
				if(sig=='_'+'2'*0x100)
				{
					fclose(f,&ul);
					return(readGPF(filename,1));
				}
			 break;
			default: 
				fclose(f,&ul);
			 return(readDAT(filename,1));
		}
	}
	fclose(f,&ul);
	return N_FORMAT;
}

int open_file(const char *filename)
{
	int p=read_file(filename);
	if(p!=RES_OK)
	{
		switch(p)
		{
			case FAIL_OPEN:
			    MsgBoxError(1,(int)"Не открывается!!!");
				break;
			case N_PTI_VER:
			    MsgBoxError(1,(int)"Несовпадение версии формата!!!");
				break;
			case N_FORMAT:
			    MsgBoxError(1,(int)"Неподдерживаемый формат!!!");
				break;
			default:
			    MsgBoxError(1,(int)"Неизвестная ошибка!!!");
				break;
		}
		return 0;
	}
	return 1;
}



/////////////////////////////////// Сохранение ///////////////////////////



int CrName() // создание полного имени файла
{
	int f, i;
	unsigned int ul, j1, j2;
	TDate date;
	TTime time; 
	GetDateTime(&date,&time);
	//char w[32];
	
	
	if(!SAVEp.nm) sprintf( SAVEp.nm, "pic_%02i%02i-%i%02i%02i", date.month,date.day, time.hour,time.min,time.sec );
	//else strcpy(bmpsname,fnm);//sprintf( bmpsname, perc_t, fnm);
	strcpy(fname,SAVEp.fl);
	i=strlen(fname);
	if(fname[i-1]==_SLASH) strcpy(fname+i,SAVEp.nm);
	else
	{
		fname[i]=_SLASH;
		strcpy(fname+i+1,SAVEp.nm);
	}
	i=strlen(fname);
	memcpy(&j1, fname+i-4, 4);
	memcpy(&j2, save_ext[SAVEp.type], 4);
	if(j1!=j2) //sprintf( fname+i, "%s", SAVEp.nm, save_ext[SAVEp.type] );
	//else 
	sprintf( fname+i, perc_s, save_ext[SAVEp.type] );

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
	zeromem(tmp_sl.map, tmp_sl.w*tmp_sl.h*4);
	for(k=1; k<p->cs; k++)
	 if(p->sl[k].v)
	   for(i=0; i<tmp_sl.w*tmp_sl.h; i++)
		if(p->sl[k].map[i*4+3]>25)
			memcpy(tmp_sl.map+i*4, p->sl[k].map+i*4, 4);
}

void writePTI()
{
	unsigned int ul, i;
	int f;
		if ((f=fopen(fname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
		{
			fwrite(f,&PTI_id,2,&ul);
			fwrite(f,&PTI_ver,2,&ul);
			if(!SAVEp.btype)
			{
				fwrite(f,&p->cs,1,&ul);
				fwrite(f,&p->ns,1,&ul);
				fwrite(f,&p->w,2,&ul);
				fwrite(f,&p->h,2,&ul);
				for(i=0; i<p->cs; i++)
				{
					fwrite(f,&p->sl[i],sizeof(SLOY)-4,&ul);
					fwrite(f,p->sl[i].map,p->sl[i].w*p->sl[i].h*4,&ul);
					if(i<p->cs-1)
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
				tmp_p=p[0];
				tmp_p.cs=2;
				tmp_p.ns=1;
				memcpy(&tmp_p.sl[0], &p->sl[0], sizeof(SLOY)-4);
				sprintf( tmp_sl.nm, "SLOY 1" );
				tmp_sl.map=malloc(tmp_sl.w*tmp_sl.h*4);
				do_nosl();
				fwrite(f,&tmp_p+16,6,&ul);
				fwrite(f,&p->sl[0],sizeof(SLOY)-4,&ul);
				fwrite(f,p->sl[0].map,tmp_sl.w*tmp_sl.h*4,&ul);
				fwrite(f,&tmp_p.sl[0],sizeof(SLOY)-4,&ul);
				fwrite(f,tmp_p.sl[0].map,tmp_sl.w*tmp_sl.h*4,&ul);
				mfree(tmp_sl.map);
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
			SAVEp.parts=p->cs-1;
			SUBPROC((void*)writePTI);
			return RES_OK;
		}
		else result=FAIL_OPEN;
		fclose(f,&ul);
	}
	return result;
}


struct{
	UINT sz;
	char *buf;
	char *tmp;
} wrBuf;


void do_pallete()
{
	unsigned int i, j, j0, j1=0, j2=0;
	PALLETE.sz=1;
	PALLETE.map=malloc(1024);
	zeromem( PALLETE.map, 1024);
	memcpy( PALLETE.map, white0, 4 );
	for(i=0; i<p->sz; i++ )
	{
		if((char)wrBuf.tmp[i*4+3]>=25)
		{
			memcpy(&j1, wrBuf.tmp+i*4, 3);
			j0=0;
			for(j=0; j<PALLETE.sz; j++)
			{
				memcpy(&j2, PALLETE.map+j*4, 3);
				if(!(j1-j2)) j0++;
			}
			if(!j0)
			{
			  if(PALLETE.sz<0xff)
			  {
				memcpy(PALLETE.map+PALLETE.sz*4, wrBuf.tmp+i*4, 3);
				PALLETE.map[PALLETE.sz*4+3]=0;
				PALLETE.sz++;
			  }
			  else
			  {
				PALLETE.sz=0;
				i=p->sz;
			  }
			}
		}
	}
}



void do_bmp_map( char *tmpbuf, int nstr )
{
	unsigned int i, j, j1=0, j2=0;
	//unsigned short c2;
	switch(SAVEp.btype)
	{
// 8 bit pallete
		case 0:
				for(i=0; i<p->w; i++ )
					if((char)wrBuf.tmp[((p->h-nstr-1)*p->w+i)*4+3]>=25)
					{
						memcpy(&j1, wrBuf.tmp+((p->h-nstr-1)*p->w+i)*4, 3);
						for(j=0; j<PALLETE.sz; j++)
						{
							memcpy(&j2, PALLETE.map+j*4, 3);
							if(!(j1-j2))
							{
								wrBuf.buf[i]=j;
								j=PALLETE.sz;
							}
						}
					}
			
		 break;

// 16 bit
		case 1:
			img_32_16(wrBuf.buf, wrBuf.tmp+(p->h-1-nstr)*p->w*4, p->w, NULL, 555);
		 break;

// 24 bit
		case 2:
			img_32_24(wrBuf.buf, wrBuf.tmp+(p->h-1-nstr)*p->w*4, p->w, NULL);
		 break;

// 32 bit
		case 3:
			memcpy(wrBuf.buf, wrBuf.tmp+(p->h-1-nstr)*p->w*4, p->w*4 );
		 break;
	}
}

BMP_HDR wrBMP;

void writeBMP()
{
	int f;
	unsigned int i, ul;
	wrBuf.sz=p->w*(wrBMP.img.biBitCount/8);
	i=wrBuf.sz%4;
	if(i) wrBuf.sz+=4-i;
	wrBuf.buf=malloc(wrBuf.sz);
	zeromem(wrBuf.buf,wrBuf.sz);
		if ((f=fopen(fname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
	    {
	      fwrite(f,&BMP_id,2,&ul);
	      fwrite(f,&wrBMP,52,&ul);
		  if(!SAVEp.btype) fwrite(f,PALLETE.map,PALLETE.sz*4,&ul);
		  for(i=0; i<p->h; i++)
		  {
			do_bmp_map(wrBuf.tmp, i);
			fwrite(f,wrBuf.buf,wrBuf.sz,&ul);
			// if(i<p->h-1)
			// {
				// gipc.name_to=ipc_my_name;
				// gipc.name_from=ipc_my_name;
				// gipc.data=0;
				// GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_SAVE_PART,&gipc);
			// }
		  }
	    }
	if(!SAVEp.btype) mfree(PALLETE.map);
	mfree(wrBuf.buf);
	mfree(wrBuf.tmp);
	fclose(f,&ul);
	gipc.name_to=ipc_my_name;
	gipc.name_from=ipc_my_name;
	gipc.data=0;
	GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_SAVE_FINISHED,&gipc);
}

int saveBMP(int prm)
{
	int result, f;
	unsigned int i, ul;
	result=CrName();
	if(prm||(result==RES_OK))
	{
		if ((f=fopen(fname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
		{
			fclose(f,&ul);
			wrBMP=Def_BMP;
			wrBMP.img.biWidth=p->w;
			wrBMP.img.biHeight=p->h;
			wrBuf.tmp=malloc(p->sz*4);
			for(i=0; i<p->sz*4; i++) wrBuf.tmp[i]=0xff;
			img_32_a(wrBuf.tmp, p, 0);
			switch(SAVEp.btype)
			{
				case 0:	// 8 bit pallete
					do_pallete();
					if(!PALLETE.sz)
					{
						fclose(f,&ul);
						mfree(PALLETE.map);
						return OVER_COLCNT;
					}
					wrBMP.bmp.size=p->sz+54+PALLETE.sz*4;
					wrBMP.bmp.offbits=54+PALLETE.sz*4;
					wrBMP.img.biBitCount=8;
					wrBMP.img.biClrUsed=PALLETE.sz;
					wrBMP.img.biClrImportant=PALLETE.sz;
				 break;
				case 1:	// 16 bit
					wrBMP.bmp.size=p->sz*2+54;
					wrBMP.img.biBitCount=16;
					wrBMP.img.biClrUsed=0;
					wrBMP.img.biClrImportant=0;
				 break;
				case 2:	// 24 bit
					wrBMP.bmp.size=p->sz*3+54;
					wrBMP.img.biBitCount=24;
					wrBMP.img.biClrUsed=0;
					wrBMP.img.biClrImportant=0;
				 break;
				case 3:	// 32 bit
					wrBMP.bmp.size=p->sz*4+54;
					wrBMP.img.biBitCount=32;
					wrBMP.img.biClrUsed=0;
					wrBMP.img.biClrImportant=0;
					//for(i=0; i<p->h; i++) memcpy(wrpicmap+i*p->w*4, premap+premsz-(i+1)*p->w*4, p->w*4);
				 break;
			}
			SAVEp.parts=p->h;
			SUBPROC((void*)writeBMP);
			return RES_OK;
		}
		else result=FAIL_OPEN;
		fclose(f,&ul);
	}
	return result;
}

void do_gpf_map()
{
	unsigned int i;
	// unsigned int i,k, j, j1=0, j2=0;
	// unsigned short c2;
	wrBuf.tmp=malloc(p->sz*4);
	zeromem(wrBuf.tmp, p->sz*4);
	img_32_a(wrBuf.tmp, p, 0);
	switch(SAVEp.btype)
	{
// 8 bit pallete
		case 0:
			for(i=0; i<p->sz; i++) wrBuf.buf[i]=prz.c8;
			img_32_8(wrBuf.buf, wrBuf.tmp, p->sz, NULL);
		 break;

// 16 bit
		case 1:
			for(i=0; i<p->sz; i++) memcpy(wrBuf.buf+i*2, &prz.c16, 2);
			img_32_16(wrBuf.buf, wrBuf.tmp, p->sz, NULL, 0);
		 break;

// 32 bit
		case 2:
			for(i=0; i<p->sz; i++) memcpy(wrBuf.buf+i*4, prz.c, 4);
			memcpy(wrBuf.buf, wrBuf.tmp, p->sz*4 );
		 break;

	}
	mfree(wrBuf.tmp);
	
	// for(k=1; k<p->cs; k++)
	 // if(p->sl[k].v)
	   // for(i=0; i<tmp_sl.w*tmp_sl.h; i++)
		// if(p->sl[k].map[i*4+3]>25)
			// memcpy(tmp_sl.map+i*4, p->sl[k].map+(p->h-i-1)*4*p->w, 4*p->w );
}

GPF_HDR wrGPF;
GPF2_HDR wrGPF2;

void writeGPF()
{
	int f;
	unsigned int ul;
	//i=wrBuf.sz%4;
	//if(i) wrBuf.sz+=4-i;
		if ((f=fopen(fname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
	    {
	      if(!SAVEp.param)
		  {
			fwrite(f,GPF_id,16,&ul);
			fwrite(f,&wrGPF,sizeof(GPF_HDR),&ul);
			wrBuf.sz=wrGPF.h*wrGPF.w*map_mod[SAVEp.btype+3];
		  }
	      else
		  {
			fwrite(f,GPF2_id,16,&ul);
			fwrite(f,&wrGPF2,sizeof(GPF2_HDR),&ul);
			wrBuf.sz=wrGPF2.h*wrGPF.w*map_mod[SAVEp.btype+3];
		  }
			wrBuf.buf=malloc(wrBuf.sz);
			zeromem(wrBuf.buf, wrBuf.sz);
		  //if(!SAVEp.btype) fwrite(f,PALLETE.map,PALLETE.sz*4,&ul);
			do_gpf_map();
			fwrite(f,wrBuf.buf,wrBuf.sz,&ul);
			// if(i<p->h-1)
			// {
				// gipc.name_to=ipc_my_name;
				// gipc.name_from=ipc_my_name;
				// gipc.data=0;
				// GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_SAVE_PART,&gipc);
			// }
	    }
	//if(!SAVEp.btype) mfree(PALLETE.map);
	mfree(wrBuf.buf);
	fclose(f,&ul);
	gipc.name_to=ipc_my_name;
	gipc.name_from=ipc_my_name;
	gipc.data=0;
	GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_SAVE_FINISHED,&gipc);
}

int saveGPF(int prm)
{
	int result, f;
	unsigned int ul;
	result=CrName();
	if(prm||(result==RES_OK))
	{
		if ((f=fopen(fname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
		{
			fclose(f,&ul);
			if(!SAVEp.param)
			{
				wrGPF=Def_GPF;
				wrGPF.w=p->w;
				wrGPF.h=p->h;
				wrGPF.num=SAVEp.n;
			}
			else
			{
				wrGPF2=Def_GPF2;
				wrGPF2.w=p->w;
				wrGPF2.h=p->h;
				wrGPF2.num=SAVEp.n;
			}
			switch(SAVEp.btype)
			{
				case 0:	// 8 bit pallete
					if(!SAVEp.param) wrGPF.type=5;
					else wrGPF2.type=5;
				 break;
				case 1:	// 16 bit
					if(!SAVEp.param) wrGPF.type=8;
					else wrGPF2.type=8;
				 break;
				case 2:	// 32 bit
					if(!SAVEp.param) wrGPF.type=0xA;
					else wrGPF2.type=0xA;
				 break;
			}
			SAVEp.parts=p->h;
			SUBPROC((void*)writeGPF);
			return RES_OK;
		}
		else result=FAIL_OPEN;
		fclose(f,&ul);
	}
	return result;
}

void do_dat_map()
{
	unsigned int i;
	// unsigned int i,k, j, j1=0, j2=0;
	// unsigned short c2;
	wrBuf.tmp=malloc(p->sz*4);
	zeromem(wrBuf.tmp, p->sz*4);
	img_32_a(wrBuf.tmp, p, 0);
	//switch(SAVEp.btype)
// 8 bit pallete
		//case 0:
		//	for(i=0; i<p->sz; i++) wrBuf.buf[i]=prz.c8;
		//	img_32_8(wrBuf.buf, wrBuf.tmp, p->sz, NULL);
		// break;

// 16 bit
		//case 1:
		//	for(i=0; i<p->sz; i++) memcpy(wrBuf.buf+i*2, &prz.c16, 2);
		//	img_32_16(wrBuf.buf, wrBuf.tmp, p->sz, NULL, 0);
		// break;

// 32 bit
		//case 2:
			for(i=0; i<p->sz; i++) memcpy(wrBuf.buf+i*4, prz.c, 4);
			memcpy(wrBuf.buf, wrBuf.tmp, p->sz*4 );
		// break;

	mfree(wrBuf.tmp);
	
	// for(k=1; k<p->cs; k++)
	 // if(p->sl[k].v)
	   // for(i=0; i<tmp_sl.w*tmp_sl.h; i++)
		// if(p->sl[k].map[i*4+3]>25)
			// memcpy(tmp_sl.map+i*4, p->sl[k].map+(p->h-i-1)*4*p->w, 4*p->w );
}

DAT_HDR wrdat;

void writeDAT()
{
	int f;
	unsigned int ul;
	//i=wrBuf.sz%4;
	//if(i) wrBuf.sz+=4-i;
		if ((f=fopen(fname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
	    {
	      // if(!SAVEp.param)
		  // 
			// fwrite(f,GPF_id,16,&ul);
			// fwrite(f,&wrGPF,sizeof(GPF_HDR),&ul);
			// wrBuf.sz=wrGPF.h*wrGPF.w*map_mod[SAVEp.btype+3];
		  // 
	      // else
		  // 
			// fwrite(f,GPF2_id,16,&ul);
			fwrite(f,&wrdat.w,2,&ul);
			fwrite(f,&wrdat.h,2,&ul);
			fwrite(f,&wrdat.type,1,&ul);
			wrBuf.sz=wrdat.h*wrdat.w*4;
		  //
			wrBuf.buf=malloc(wrBuf.sz);
			zeromem(wrBuf.buf, wrBuf.sz);
		  //if(!SAVEp.btype) fwrite(f,PALLETE.map,PALLETE.sz*4,&ul);
			do_dat_map();
			fwrite(f,wrBuf.buf,wrBuf.sz,&ul);
			// if(i<p->h-1)
			// {
				// gipc.name_to=ipc_my_name;
				// gipc.name_from=ipc_my_name;
				// gipc.data=0;
				// GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_SAVE_PART,&gipc);
			// }
	    }
	//if(!SAVEp.btype) mfree(PALLETE.map);
	mfree(wrBuf.buf);
	fclose(f,&ul);
	gipc.name_to=ipc_my_name;
	gipc.name_from=ipc_my_name;
	gipc.data=0;
	GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_SAVE_FINISHED,&gipc);
}

int saveDAT(int prm)
{
	int result, f;
	unsigned int ul;
	result=CrName();
	if(prm||(result==RES_OK))
	{
		if ((f=fopen(fname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
		{
			fclose(f,&ul);
			// if(!SAVEp.param)
			// {
				//wrdat=Def_GPF;
				wrdat.w=p->w;
				wrdat.h=p->h;
				wrdat.type=10;
				//wrGPF.num=SAVEp.n;
			// }
			// else
			// {
				// wrGPF2=Def_GPF2;
				// wrGPF2.w=p->w;
				// wrGPF2.h=p->h;
				// wrGPF2.num=SAVEp.n;
			// }
			// switch(SAVEp.btype)
			// {
				// case 0:	// 8 bit pallete
					// if(!SAVEp.param) wrGPF.type=5;
					// else wrGPF2.type=5;
				 // break;
				// case 1:	// 16 bit
					// if(!SAVEp.param) wrGPF.type=8;
					// else wrGPF2.type=8;
				 // break;
				// case 2:	// 32 bit
					// if(!SAVEp.param) wrGPF.type=0xA;
					// else wrGPF2.type=0xA;
				 // break;
			// }
			SAVEp.parts=p->h;
			SUBPROC((void*)writeDAT);
			return RES_OK;
		}
		else result=FAIL_OPEN;
		fclose(f,&ul);
	}
	return result;
}

