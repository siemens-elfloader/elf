

#include "../inc/swilib.h"
#include "parse_oms.h"
#include "additems.h"
#include "string_works.h"
#include "..\inc\zlib.h"
//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>

#pragma inline
unsigned int _rbyte(VIEWDATA *vd)
{
  unsigned char *p=(unsigned char *)(vd->oms+vd->oms_pos);
  unsigned int r=*p++;
  vd->oms_pos+=1;
  return r;
}

static unsigned int _rshort(VIEWDATA *vd)
{
  unsigned char *p=(unsigned char *)(vd->oms+vd->oms_pos);
  unsigned int r=*p++;
  r<<=8;
  r|=*p;
  vd->oms_pos+=2;
  return r;
}

unsigned int _rlong(VIEWDATA *vd)
{
  unsigned char *p=(unsigned char *)(vd->oms+vd->oms_pos);
  unsigned int r=*p++;
  r<<=8;r|=*p++;
  r<<=8;r|=*p++;
  r<<=8;r|=*p;
  vd->oms_pos+=4;
  return r;
}


void* zcalloc(int unk,size_t nelem, size_t elsize)
{
  return (malloc(nelem*elsize));
}

void zcfree(int unk, void* ptr)
{
  mfree(ptr);
}

//static const char slash[]="/";

void OMS_DataArrived(VIEWDATA *vd, const char *buf, int len)
{
  int i;
  unsigned int k;
  int err;
  char s[128];
  if ((len==0)||(buf==0))
  {
    vd->parse_state=OMS_STOP;
    return;
  }
  vd->loaded_sz+=len;
  if (vd->zs)
  {
  L_ZBEGIN:
    vd->zs->next_in=(Byte *)buf;
    vd->zs->avail_in=len;
  L_ZNEXT:
    vd->zs->next_out=(Byte *)(vd->oms=realloc(vd->oms,vd->oms_size+len))+vd->oms_size;
    vd->zs->avail_out=len;
    err=inflate(vd->zs, Z_NO_FLUSH);
    switch (err)
    {
    case Z_NEED_DICT:
    case Z_DATA_ERROR:
    case Z_MEM_ERROR:
      sprintf(s,"ZLib Err %d\n",err);
      AddTextItem(vd,s,strlen(s));
      AddBrItem(vd);
      vd->parse_state=OMS_STOP;
      return;
    }
    vd->oms_size+=len-vd->zs->avail_out;
  }
  else
  {
    memcpy((vd->oms=realloc(vd->oms,i=vd->oms_size+len))+vd->oms_size,buf,len);
    vd->oms_size=i;
  }
  if (vd->parse_state==OMS_BEGIN)
  {
    vd->oms_wanted=sizeof(OMS_HEADER_COMMON);
    vd->parse_state=OMS_HDR_COMMON;
    vd->loaded_sz-=sizeof(OMS_HEADER_COMMON);
  }
  while(vd->oms_size>=vd->oms_wanted)
  {
    switch(vd->parse_state)
    {
    case OMS_HDR_COMMON:
      memset(&(vd->work_ref),0xFF,sizeof(REFCACHE));
      memset(&(vd->work_ref_Z),0xFF,sizeof(REFCACHE));
      i=_rshort(vd);
      vd->page_sz=_rlong(vd);
      vd->oms_wanted+=sizeof(OMS_HEADER_V2);
      vd->parse_state=OMS_HDR;
      {
        switch(i)
        {
        case 0x0D33:
          vd->oms_wanted-=2;
          break;
        case 0x1833:
          break;
        case 0x0D31:
          vd->oms_wanted-=sizeof(OMS_HEADER_V2)-10; 
          vd->parse_state=OMS_GZIPHDR;
          break;
        case 0x1832:
        L_ZINIT:
          zeromem(vd->zs=malloc(sizeof(z_stream)),sizeof(z_stream));
          vd->zs->zalloc = (alloc_func)zcalloc;
          vd->zs->zfree = (free_func)zcfree;
          vd->zs->opaque = (voidpf)0;
          err = inflateInit2(vd->zs,-MAX_WBITS);
          if(err!=Z_OK)
          {
            sprintf(s,"inflateInit2 err %d\n",err);
            AddTextItem(vd,s,strlen(s));
            AddBrItem(vd);
            vd->parse_state=OMS_STOP;
            return;
          }
         
          i=vd->oms_size-vd->oms_pos;
          if (!i) return; 
          buf=buf+len-i; 
          len=i; 
          vd->oms_size=vd->oms_pos; 
          goto L_ZBEGIN;
        default:
          sprintf(s,"Not supported type %X\n",i);
          AddTextItem(vd,s,strlen(s));
          AddBrItem(vd);
          vd->parse_state=OMS_STOP;
          return;
        }
      }
      break;
    case OMS_GZIPHDR:

      vd->oms_pos=vd->oms_wanted;
      vd->oms_wanted+=sizeof(OMS_HEADER_V2)-2; 
      vd->parse_state=OMS_HDR;
      goto L_ZINIT;
    case OMS_HDR:
      vd->oms_pos=vd->oms_wanted;
      vd->oms_wanted+=2;
      vd->parse_state=OMS_PAGEURL_SIZE;
      break;
    case OMS_PAGEURL_SIZE:
      vd->oms_wanted+=_rshort(vd);
      vd->parse_state=OMS_PAGEURL_DATA;
      break;
    case OMS_PAGEURL_DATA:
      i=vd->oms_wanted-vd->oms_pos;
      //AddTextItem(vd,vd->oms+vd->oms_pos,i);
      //AddBrItem(vd);
      vd->pageurl=(char *)malloc(i+1);
      memcpy(vd->pageurl,vd->oms+vd->oms_pos,i);
      vd->pageurl[i]=NULL;
      vd->oms_pos=vd->oms_wanted;
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAG_NAME:
      // STAGE 1
      //DEBUGV("OMS_TAG_NAME pos:",17);
      //DEBUGS("%i ",vd->oms_pos);
      //DEBUGS("%c\n",vd->oms[vd->oms_pos]);
      switch(i=vd->oms[vd->oms_pos])
      {
      case '+':
        vd->oms_pos++;
	      goto L_NOSTAGE2;
      case 'v':
	      //???
        vd->oms_pos++;
	      goto L_NOSTAGE2;
      case '(':
        //???
        AddPictureItemHr(vd);
        //AddTextItem(vd,"(",1);
        vd->oms_pos++;
	      goto L_NOSTAGE2;
      case ')':
	      //???
        AddPictureItemHr(vd);
        //AddTextItem(vd,")",1);
        vd->oms_pos++;
	      goto L_NOSTAGE2;
      case '$':  //Form end ???
        vd->oms_pos++;
        goto L_NOSTAGE2;
      case 'A':
        vd->oms_wanted+=2;
        break;
      case 'C':    
        vd->work_ref.no_upload=0;
        vd->oms_pos++;
        goto L_NOSTAGE2;
      case 'D':
        vd->oms_wanted+=2;
        break;
      case 'S':    // Style
        vd->oms_wanted+=4;
        break;
      case 'T':    // Text
        vd->oms_wanted+=2;
        break;
      case 'Y':
        vd->oms_wanted+=1;
        break;
      case 'B':
	      AddBrItem(vd);
        vd->oms_pos++;
	      goto L_NOSTAGE2;
      case 'V':
	      AddPItem(vd);
        vd->oms_pos++;
	      goto L_NOSTAGE2;
      case 'I':  // image
        vd->oms_wanted+=8;
        break;
      case 'J':  // picture frame
        vd->oms_wanted+=4;
        break;
      case 'K':  // image by id
        vd->oms_wanted+=6;
        break;
      case 'X':  // Image RGBA
        vd->oms_wanted+=4;
        break;
      case 'h':    // opf 1
        vd->oms_wanted+=2;
        break;
      case 'e':  
      case 'p':
      case 'u':
        vd->oms_wanted+=2;
        break;
      case 'x':
        if ((((OMS_HEADER_COMMON *)vd->oms)->magic&0xFF)==0x0D)
        {
          vd->oms_wanted+=2;
        }
        else
        {
          vd->oms_wanted+=3;
        }
        break;
      case 'c':
      case 'r':
        vd->oms_wanted+=2;
        break;
      case 's': // drop down list
        vd->oms_wanted+=2;
        break;
      case 'o': // drop down list item
        vd->oms_wanted+=2;
        break;
      case 'l': 
        //AddBeginRef(vd);
        //vd->tag_l_count=2;
        //AddTextItem(vd,"<l>",3);
        vd->oms_pos++;
        goto L_NOSTAGE2;
      case 'i':  // image button
        //if (!vd->tag_l_count)
        //{
          AddBeginRef(vd);
          //vd->tag_l_count=1;
        //}
        vd->oms_wanted+=2;
        break;
      case 'k':
        vd->oms_wanted+=3; //Code type and data length
        break;	
      case 'L':  // link
        vd->oms_wanted+=2;
        break;
      case '^':  // wrong tag ?
        vd->oms_wanted+=2;
        break;
      case 'P':  // phone number
        vd->oms_wanted+=2;
        vd->ref_mode_P=1;
        break;
      case 'R':
        vd->oms_wanted+=2;
        break;
      case 'E':  //finish ref
        if (vd->work_ref.tag==_NOREF)
          if (vd->work_ref_Z.tag=='Z')
          {
            memcpy(&(vd->work_ref),&(vd->work_ref_Z),sizeof(REFCACHE));
            memset(&(vd->work_ref_Z),0xFF,sizeof(REFCACHE));
          }
        if (vd->ref_mode_P==0)
          AddEndRef(vd);
        vd->ref_mode_P=0;
        vd->oms_pos++;
	      goto L_NOSTAGE2;
      case 'Q':
        //AddTextItem(vd,"Q",1); // HACK at the end of page we must add invisible ending line
        vd->parse_state=OMS_STOP;
        return;
      case 'Z':
        vd->oms_wanted+=2;
        break;
      case '@':
        vd->oms_wanted+=4;
        break;
      default:
        sprintf(s,"Unknown tag %c\n",i);
        AddTextItem(vd,s,strlen(s));
        AddBrItem(vd);
        vd->parse_state=OMS_STOP;
        return;
      }
      vd->parse_state=OMS_TAG_DATA;
      break;
    case OMS_TAG_DATA:
      //DEBUGV("OMS_TAG_DATA pos:",17);
      //DEBUGS("%i ",vd->oms_pos);
      //DEBUGS("%c\n",vd->oms[vd->oms_pos]);
      i=vd->oms[vd->oms_pos];
      vd->oms_pos++;
      switch(i)
      {
      case 'A':
        i=_rshort(vd);
        //vd->work_ref.tag='A';
        vd->oms_wanted+=i;
        vd->parse_state=OMS_TAGA_STAGE3;
        goto L_STAGE3_WANTED;
      case 'D':
        *((unsigned short *)(&(vd->current_tag_d)))=_rshort(vd);
        AddNewStyle(vd);
        break;
      case 'S':
        vd->prev_tag_s=vd->current_tag_s;
        *((unsigned int *)(&(vd->current_tag_s)))=k=_rlong(vd);
        ((unsigned int *)(vd->S_cache=realloc(vd->S_cache,(vd->S_cache_size+1)*sizeof(TAG_S))))[vd->S_cache_size]=k;
        vd->S_cache_size++;
        AddNewStyle(vd);
        break;
      case 'T':
        i=_rshort(vd);
        vd->oms_wanted+=i;
        vd->parse_state=OMS_TAGT_STAGE3;
        goto L_STAGE3_WANTED;
      case 'Y':
        i=_rbyte(vd);
        vd->prev_tag_s=vd->current_tag_s;
        vd->current_tag_s=vd->S_cache[i];
        AddNewStyle(vd);
        break;
      case 'I':
        vd->iw=_rshort(vd); //width
        vd->ih=_rshort(vd); //heigth
        i=_rshort(vd);
        _rshort(vd);
        vd->oms_wanted+=i;
        vd->parse_state=OMS_TAGI_STAGE3;
        goto L_STAGE3_WANTED;
      case 'J':
        vd->iw=_rshort(vd); //width
        vd->ih=_rshort(vd); //height
        AddPictureItemFrame(vd,vd->iw,vd->ih);
        vd->ref_mode_i--;
        if (!vd->ref_mode_i)
          AddEndRef(vd);
        break;
      case 'K':
        _rshort(vd); //width
        _rshort(vd); //height
        i=_rshort(vd); //index
        AddPictureItemIndex(vd,i);
        vd->ref_mode_i--;
        if (!vd->ref_mode_i)
          AddEndRef(vd);
        break;
      case 'X':
        vd->iw=_rbyte(vd); //width
        vd->ih=_rbyte(vd); //heigth
        i=_rshort(vd);
        vd->oms_wanted+=i;
        vd->parse_state=OMS_TAGX_STAGE3;
        goto L_STAGE3_WANTED;
      case 'h':
        i=(vd->iw=_rshort(vd))+2;
        vd->oms_wanted+=i;
        vd->parse_state=OMS_TAGh_STAGE3;
        goto L_STAGE3_WANTED;
      case 'e':
        i=(vd->iw=_rshort(vd))+2;
        vd->work_ref.tag='e';
        vd->oms_wanted+=i;
        vd->parse_state=OMS_TAGe_STAGE3;
        goto L_STAGE3_WANTED;
      case 'p':
        i=(vd->iw=_rshort(vd))+2;
        AddBeginRef(vd);
        vd->work_ref.tag='p';
        vd->oms_wanted+=i;
        vd->parse_state=OMS_TAGp_STAGE3;
        goto L_STAGE3_WANTED;
      case 'u':
        i=(vd->iw=_rshort(vd))+2;
        AddBeginRef(vd);
        vd->work_ref.tag='u';
        vd->oms_wanted+=i;
        vd->parse_state=OMS_TAGu_STAGE3;
        goto L_STAGE3_WANTED;
      case 'x':
        if ((((OMS_HEADER_COMMON *)vd->oms)->magic&0xFF)!=0x0D) _rbyte(vd);
        i=(vd->iw=_rshort(vd))+2;
        AddBeginRef(vd);
        vd->work_ref.tag='x';
        vd->oms_wanted+=i;
        vd->parse_state=OMS_TAGx_STAGE3;
        goto L_STAGE3_WANTED;
      case 'c':
        i=(vd->iw=_rshort(vd))+2;
        AddBeginRef(vd);
        vd->work_ref.tag='c';
        vd->oms_wanted+=i;
        vd->parse_state=OMS_TAGc_STAGE3;
        goto L_STAGE3_WANTED;
      case 'r':
        i=(vd->iw=_rshort(vd))+2;
        AddBeginRef(vd);
        vd->work_ref.tag='r';
        vd->oms_wanted+=i;
        vd->parse_state=OMS_TAGr_STAGE3;
        goto L_STAGE3_WANTED;
      case 's':
        i=(vd->iw=_rshort(vd))+3;
        AddBeginRef(vd);
        vd->work_ref.tag='s';
        //AddTextItem(vd,"<s>",3);
        vd->oms_wanted+=i;
        vd->parse_state=OMS_TAGs_STAGE3;
        goto L_STAGE3_WANTED;
      case 'o':
        if (vd->tag_o_count)
        {
          vd->tag_o_count--;
          i=(vd->iw=_rshort(vd))+2;
          vd->work_ref.tag='s';
          vd->oms_wanted+=i;
          vd->parse_state=OMS_TAGo_STAGE3;
          goto L_STAGE3_WANTED;
        }
        else
        {
          AddTextItem(vd,"!Illegal <o>!\n",14);
          AddBrItem(vd);
          vd->parse_state=OMS_STOP;
          return;
        }
      case 'i':
        i=(vd->iw=_rshort(vd))+2;
        vd->work_ref.tag='i';
        vd->oms_wanted+=i;
        vd->parse_state=OMS_TAGi_STAGE3;
        goto L_STAGE3_WANTED;
      case 'k':
        vd->ih=_rbyte(vd); //Code type
        i=(vd->iw=_rshort(vd));
        vd->oms_wanted+=i;
        vd->parse_state=OMS_TAGk_STAGE3;
        goto L_STAGE3_WANTED;
      case 'L':
        i=_rshort(vd);
        vd->work_ref.tag='L';
        AddBeginRef(vd);
        vd->oms_wanted+=i;
        vd->parse_state=OMS_TAGL_STAGE3;
        goto L_STAGE3_WANTED;
      case '^':
        i=_rshort(vd);
        vd->work_ref.tag='^';
        //vd->ref_mode=1;//????
        AddBeginRef(vd);
        vd->oms_wanted+=i;
        vd->parse_state=OMS_TAGx5E_STAGE3;
        goto L_STAGE3_WANTED;
      case 'P':
        i=_rshort(vd);
        vd->oms_wanted+=i;
        vd->parse_state=OMS_TAGP_STAGE3;
        goto L_STAGE3_WANTED;
      case 'R':
        i=_rshort(vd);
        AddPictureItemHr(vd);
        break;
      case 'Z':
        i=vd->iw=_rshort(vd);
        vd->work_ref_Z.tag='Z';
        vd->work_ref_Z.id=vd->oms_pos-2;
        AddBeginRefZ(vd);
        vd->oms_wanted+=i;
        vd->parse_state=OMS_TAGZ_STAGE3;
        goto L_STAGE3_WANTED;
      case '@':
        vd->ih=_rshort(vd);
        i=vd->iw=_rshort(vd);
        if (i>0)
        {
          vd->work_ref.id=vd->oms_pos-2;
          vd->work_ref.id2=vd->ih;
          vd->work_ref.tag='@';
          AddBeginRef(vd);
          vd->oms_wanted+=i;
          vd->parse_state=OMS_TAGx40_STAGE3;
          goto L_STAGE3_WANTED;
        }
      default:
        //vd->parse_state=OMS_STOP;
        break;
      }
    L_NOSTAGE2:
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
    L_STAGE3_WANTED:
      break;
    case OMS_TAGA_STAGE3:
      i=vd->oms_wanted-vd->oms_pos;
      //AddTextItem(vd,vd->oms+vd->oms_pos,i);
      vd->oms_pos=vd->oms_wanted;
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAGT_STAGE3:
      i=vd->oms_wanted-vd->oms_pos;
      AddTextItem(vd,vd->oms+vd->oms_pos,i);
      if(!vd->title)
      {
        vd->title=(char *)malloc(i+1);
        memcpy(vd->title,vd->oms+vd->oms_pos,i);
        vd->title[i]=NULL;
        //utf82win(vd->title, vd->title);
        AddBrItem(vd);
      }
      vd->oms_pos=vd->oms_wanted;
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAGI_STAGE3:
      AddPictureItem(vd,(void *)(vd->oms+vd->oms_pos));
      vd->ref_mode_i--;
      if (!vd->ref_mode_i)
        AddEndRef(vd);
      vd->oms_pos=vd->oms_wanted;
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAGX_STAGE3:
      //i=vd->oms_wanted-vd->oms_pos; //Size of picture
      AddPictureItemRGBA(vd,(void *)(vd->oms+vd->oms_pos),vd->iw,vd->ih);
      vd->ref_mode_i--;
      if (!vd->ref_mode_i)
        AddEndRef(vd);
      vd->oms_pos=vd->oms_wanted;
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAGh_STAGE3:
      i=vd->iw;
      //vd->work_ref.form_id1=vd->oms_pos;
      vd->oms_pos+=i;
      i=(vd->ih=_rshort(vd));
      vd->oms_wanted+=i;
      vd->parse_state=OMS_TAGh_STAGE4;
      break;
    case OMS_TAGh_STAGE4:
      i=vd->ih;
      //vd->work_ref.form_id2=vd->oms_pos;
      vd->oms_pos+=i;
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAGe_STAGE3:
      i=vd->iw;
      vd->work_ref.id=vd->oms_pos-2;
      vd->oms_pos+=i;
      i=(vd->ih=_rshort(vd));
      vd->oms_wanted+=i;
      vd->parse_state=OMS_TAGe_STAGE4;
      break;
    case OMS_TAGe_STAGE4:
      i=vd->ih;
      vd->work_ref.value=vd->oms_pos-2;
      //AddEndRef(vd);
      vd->oms_pos+=i;
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAGp_STAGE3:
      i=vd->iw;
      vd->work_ref.id=vd->oms_pos-2;
      vd->oms_pos+=i;
      i=(vd->ih=_rshort(vd));
      vd->oms_wanted+=i;
      vd->parse_state=OMS_TAGp_STAGE4;
      break;
    case OMS_TAGp_STAGE4:
      i=vd->ih;
      vd->work_ref.value=vd->oms_pos-2;
      AddInputItem(vd,vd->oms_pos-2);
      AddEndRef(vd);
      vd->oms_pos+=i;
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAGu_STAGE3:
      i=vd->iw;
      vd->work_ref.id=vd->oms_pos-2;
      vd->oms_pos+=i;
      i=(vd->ih=_rshort(vd));
      vd->oms_wanted+=i;
      vd->parse_state=OMS_TAGu_STAGE4;
      break;
    case OMS_TAGu_STAGE4:
      i=vd->ih;
      vd->work_ref.value=vd->oms_pos-2;
      AddButtonItem(vd,vd->oms+vd->oms_pos,i);
      AddEndRef(vd);
      vd->oms_pos+=i;
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAGx_STAGE3:
      i=vd->iw;
      vd->work_ref.id=vd->oms_pos-2;
      vd->oms_pos+=i;
      i=(vd->ih=_rshort(vd));
      vd->oms_wanted+=i;
      vd->parse_state=OMS_TAGx_STAGE4;
      break;
    case OMS_TAGx_STAGE4:
      i=vd->ih;
      vd->work_ref.value=vd->oms_pos-2;
      AddInputItem(vd,vd->oms_pos-2);
      AddEndRef(vd);
      vd->oms_pos+=i;
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAGc_STAGE3:
      i=vd->iw;
      vd->work_ref.id=vd->oms_pos-2;
      vd->oms_pos+=i;
      i=(vd->ih=_rshort(vd))+1;
      vd->oms_wanted+=i;
      vd->parse_state=OMS_TAGc_STAGE4;
      break;
    case OMS_TAGc_STAGE4:
      i=vd->ih;
      vd->work_ref.value=vd->oms_pos-2;
      vd->oms_pos+=i;
      i=_rbyte(vd);
      AddCheckBoxItem(vd,i);
      AddEndRef(vd);
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAGr_STAGE3:
      i=vd->iw;
      vd->work_ref.id=vd->oms_pos-2;
      vd->oms_pos+=i;
      i=(vd->ih=_rshort(vd))+1;
      vd->oms_wanted+=i;
      vd->parse_state=OMS_TAGr_STAGE4;
      break;
    case OMS_TAGr_STAGE4:
      i=vd->ih;
      vd->work_ref.value=vd->oms_pos-2;
      vd->oms_pos+=i;
      i=_rbyte(vd);
      AddRadioButton(vd,i);
      AddEndRef(vd);
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAGs_STAGE3:
      i=vd->iw;
      vd->work_ref.id=vd->oms_pos-2;
      vd->oms_pos+=i;
      vd->work_ref.multiselect=_rbyte(vd);
      vd->work_ref.data=malloc(vd->tag_o_count=_rshort(vd));
      vd->work_ref.size=0;
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAGo_STAGE3:
      i=vd->iw;
      //AddTextItem(vd,vd->oms+vd->oms_pos,i);
      vd->oms_pos+=i;
      i=vd->ih=_rshort(vd);
      vd->oms_wanted+=i+1;
      vd->parse_state=OMS_TAGo_STAGE4;
      break;
    case OMS_TAGo_STAGE4:
      i=vd->ih;
      //AddTextItem(vd,vd->oms+vd->oms_pos,i);
      //AddBrItem(vd);
      vd->oms_pos+=i;
      if (((char*)vd->work_ref.data)[vd->work_ref.size]=_rbyte(vd)) //checked/unchecked
      {
        vd->work_ref.value=vd->oms_pos-1-vd->ih-2-vd->iw-2;
        vd->work_ref.id2=vd->oms_pos-1-vd->ih-2;
      }
      vd->work_ref.size++;
      if (!vd->tag_o_count)
      {
        AddDropDownList(vd);
        AddEndRef(vd);
      }
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAGi_STAGE3:
      i=vd->iw;
      vd->work_ref.id=vd->oms_pos-2;
      vd->oms_pos+=i;
      i=vd->ih=_rshort(vd);
      vd->oms_wanted+=i;
      vd->parse_state=OMS_TAGi_STAGE4;
      break;
    case OMS_TAGi_STAGE4:
      i=vd->ih;
      vd->work_ref.value=vd->oms_pos-2;
      //AddTextItem(vd,vd->oms+vd->oms_pos,i);
      //if (vd->tag_l_count)
      //{
      //  if (!(--vd->tag_l_count))
      //  {
      //    AddEndRef(vd);
      //  }
      //}
      //else
      //{
      //  AddTextItem(vd,"!Illegal <i>!",13);
      //  AddBrItem(vd);
      //  vd->parse_state=OMS_STOP;
      //  return;
      //}
      vd->oms_pos+=i;
      //_rshort(vd); //unk
      vd->oms_wanted++;
      vd->ref_mode_i=1;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAGk_STAGE3:
      i=vd->iw;
      AddPictureItemHr(vd);
      sprintf(s,vd->ih?"New AuthCode: ":"New AuthPrefix: ",vd->ih);
      AddTextItem(vd,s,strlen(s));
      AddTextItem(vd,vd->oms+vd->oms_pos,i);
      AddPictureItemHr(vd);
      vd->oms_pos=vd->oms_wanted;
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAGL_STAGE3:
      i=vd->oms_wanted-vd->oms_pos;
      vd->work_ref.id=vd->oms_pos-2;
      vd->oms_pos=vd->oms_wanted;
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAGx5E_STAGE3:
      i=vd->oms_wanted-vd->oms_pos;
      vd->work_ref.id=vd->oms_pos-2;
      vd->oms_pos=vd->oms_wanted;
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAGP_STAGE3:
      i=vd->oms_wanted-vd->oms_pos;
      //AddTextItem(vd,vd->oms+vd->oms_pos,i);
      //AddTextItem(vd,slash,1);
      vd->oms_pos=vd->oms_wanted;
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAGZ_STAGE3:
      i=vd->iw;
      //AddBrItem(vd);
      //AddTextItem(vd,vd->oms+vd->oms_pos,i);
      //AddBrItem(vd);
      vd->oms_pos+=i;
      //AddEndRef(vd);
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_TAGx40_STAGE3:
      i=vd->iw;
      AddTextItem(vd,vd->oms+vd->oms_pos,i);
      AddBrItem(vd);
      vd->oms_pos+=i;
      AddEndRef(vd);
      vd->oms_wanted++;
      vd->parse_state=OMS_TAG_NAME;
      break;
    case OMS_STOP:
      return;
    default:
      sprintf(s,"StateMachine failed %u",i);
      AddTextItem(vd,s,strlen(s));
      AddBrItem(vd);
      vd->parse_state=OMS_STOP;
      return;
    }
  }
  if (vd->zs)
  {
    if (vd->zs->avail_out==0) goto L_ZNEXT;
  }
}

