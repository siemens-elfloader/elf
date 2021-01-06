#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "..\inc\cfg_items.h"
#include "math.h"
#include "libr.h"
char perdddd[]="%d %d %d %d";
char per_d[]="%d";
char per_s[]="%s";
char per_ss[]="%s%s";
char per_ssss[]="%s%s%s%s";
char per_x[]="%X";
char per_0[]="0";

long file_size;
char *channel[4] = { "Stereo", "J-Stereo", "Dual-Ch", "Single-Ch" };
int bitrateee[3][15] = {
          {0,32,64,96,128,160,192,224,256,288,320,352,384,416,448},  
          {0,32,48,56,64,80,96,112,128,160,192,224,256,320,384},
          {0,32,40,48,56,64,80,96,112,128,160,192,224,256,320}
        };

int frequency[3][3] = {
          {44100,48000,32000},
          {22050,24000,12000},
          {11025,12000,8000}
        };
char binary[33];
int mpegver,layerr,bitratee,frame_size=0;
int freqq;
char mpeg_vers[16],layer_vers[16],channell[16];

char *reverse(char *s)    /* REVERSE STRING S IN PLACE */
{
  int c, i, j;
  for(i = 0, j = strlen(s) - 1; i < j; i++, j--)  {
     c = s[i];
     s[i] = s[j];
     s[j] = c;
  }
  return s;
}
char  dec[64]; 
char *dec2bin (unsigned int num)
{
  char bu[64];
  char digits[2] = { '0', '1' };
  int i = 0;
  do {
    bu[i++] = digits[num&1];
    /* if we work with ASCII: s[i]='0'+(num&1); */
  } while (num>>=1);
  bu[i] = '\0';
  strcpy(dec,reverse(bu));
  return dec;
}

int OneOrZero(unsigned int bit)
{
  int bitt;
  if(binary[bit]==0x30) bitt=0;
  if(binary[bit]==0x31) bitt=1;
  return bitt;
}
int GetMPEGv()
{
  int mpgv;
  if(OneOrZero(11)==0)
  {
    if(OneOrZero(12)==0)
    {
      mpgv=1;
    }
    //if(OneOrZero(12)==1)
      //ShowMSG(1,(int)"reserved");
  }
  else{
    if(OneOrZero(11)==1)
    {
      if(OneOrZero(12)==0)
      {
        //ShowMSG(1,(int)"Mpeg v2");
        mpgv=1;
      }
      if(OneOrZero(12)==1)
      {
        //ShowMSG(1,(int)"Mpeg v1");
        mpgv=0;
      }
    }
  }
  return mpgv;
}

int GetLayer()
{
  int layr;
  if(OneOrZero(13)==0&&OneOrZero(14)==1)
  {
    //ShowMSG(1,(int)"Layer III");
    layr=2;
  }
  if(OneOrZero(13)==1&&OneOrZero(14)==0)
  {
    //ShowMSG(1,(int)"Layer II");
    layr=1;
  }
  if(OneOrZero(13)==1&&OneOrZero(14)==1)
  {
    //ShowMSG(1,(int)"Layer I");
    layr=0;
  }
  return layr;
}
int GetBitrIndex()
{
  int index;
  if(OneOrZero(16)==0&&OneOrZero(17)==0&&OneOrZero(18)==0&&OneOrZero(19)==0)//0000
    index=0;
  if(OneOrZero(16)==0&&OneOrZero(17)==0&&OneOrZero(18)==0&&OneOrZero(19)==1)//0001
    index=1;
  if(OneOrZero(16)==0&&OneOrZero(17)==0&&OneOrZero(18)==1&&OneOrZero(19)==0)//0010
    index=2;
  if(OneOrZero(16)==0&&OneOrZero(17)==0&&OneOrZero(18)==1&&OneOrZero(19)==1)//0011
    index=3;
  if(OneOrZero(16)==0&&OneOrZero(17)==1&&OneOrZero(18)==0&&OneOrZero(19)==0)//0100
    index=4;
  if(OneOrZero(16)==0&&OneOrZero(17)==1&&OneOrZero(18)==0&&OneOrZero(19)==1)//0101
    index=5;
  if(OneOrZero(16)==0&&OneOrZero(17)==1&&OneOrZero(18)==1&&OneOrZero(19)==0)//0110
    index=6;
  if(OneOrZero(16)==0&&OneOrZero(17)==1&&OneOrZero(18)==1&&OneOrZero(19)==1)//0111
    index=7;
  if(OneOrZero(16)==1&&OneOrZero(17)==0&&OneOrZero(18)==0&&OneOrZero(19)==0)//1000
    index=8;
  if(OneOrZero(16)==1&&OneOrZero(17)==0&&OneOrZero(18)==0&&OneOrZero(19)==1)//1001
    index=9;
  if(OneOrZero(16)==1&&OneOrZero(17)==0&&OneOrZero(18)==1&&OneOrZero(19)==0)//1010
    index=10;
  if(OneOrZero(16)==1&&OneOrZero(17)==0&&OneOrZero(18)==1&&OneOrZero(19)==1)//1011
    index=11;
  if(OneOrZero(16)==1&&OneOrZero(17)==1&&OneOrZero(18)==0&&OneOrZero(19)==0)//1100
    index=12;
  if(OneOrZero(16)==1&&OneOrZero(17)==1&&OneOrZero(18)==0&&OneOrZero(19)==1)//1101
    index=13;
  if(OneOrZero(16)==1&&OneOrZero(17)==1&&OneOrZero(18)==1&&OneOrZero(19)==0)//1110
    index=14;
  if(OneOrZero(16)==1&&OneOrZero(17)==1&&OneOrZero(18)==1&&OneOrZero(19)==1)//1111
    index=15; 
  return index;
}

int GetFrequencyInd()
{
  int ind;
  if(OneOrZero(20)==0&&OneOrZero(21)==0)
    ind=0;
  if(OneOrZero(20)==0&&OneOrZero(21)==1)
    ind=1;
  if(OneOrZero(20)==1&&OneOrZero(21)==0)
    ind=2;
  return ind;
}  

int GetChanInd()
{
  int ind;
  if(OneOrZero(24)==0&&OneOrZero(25)==0)
    ind=0;
  if(OneOrZero(20)==0&&OneOrZero(25)==1)
    ind=1;
  if(OneOrZero(24)==1&&OneOrZero(25)==0)
    ind=2;
  if(OneOrZero(24)==1&&OneOrZero(25)==1)
    ind=3;
  return ind;
}  
int GetMLind(unsigned int mpeg, unsigned int layer)
{
  int ind;
  if(mpeg==0&&layer==0)
    ind=0;
  if(mpeg==0&&layer==1)
    ind=1;
  if(mpeg==0&&layer==2)
    ind=2;
  return ind;
}
extern FILEPRP flprp;
void ReadInfoFromHeaders()
{
  int padding;
  //---------------MPEG ver-----------------------------
  mpegver=GetMPEGv();
  if(mpegver==1) sprintf(mpeg_vers,per_s,"MPEG v2");
  if(mpegver==0) sprintf(mpeg_vers,per_s,"MPEG v1");
  //---------------Layer--------------------------------
  layerr=GetLayer();
  if(layerr==2) sprintf(layer_vers,per_s,"Layer III");
  if(layerr==1) sprintf(layer_vers,per_s,"Layer II");
  if(layerr==0) sprintf(layer_vers,per_s,"Layer I");
  //---------------Bitrate------------------------------
  bitratee=bitrateee[GetMLind(mpegver,layerr)][GetBitrIndex()];
  //---------------Frequency----------------------------
  freqq=frequency[mpegver][GetFrequencyInd()];
  //---------------Frame Size---------------------------
  padding=OneOrZero(22);
  if(layerr==0)
    frame_size=(12*bitratee*1000/freqq+padding)*4;
  if(layerr==1||layerr==2)
    frame_size=144*bitratee*1000/freqq+padding;
  //---------------Channel------------------------------
  sprintf(channell,per_s,channel[GetChanInd()]);
}

int crc()
{
  int ret;
  if(OneOrZero(13)==0&&OneOrZero(0)==1&&OneOrZero(1)==1&&OneOrZero(2)==1&&OneOrZero(3)==1&&OneOrZero(4)==1&&OneOrZero(5)==1&&OneOrZero(6)==1&&OneOrZero(7)==1&&OneOrZero(8)==1&&OneOrZero(9)==1&&OneOrZero(10)==1)
    ret=1;
  else ret=0;
  return ret;
}
char binn[32];
char *bin2_8bytes(char *bin)
{
  int len=strlen(bin);
  if(len==1){sprintf(binn,"0000000%s",bin);binn[8]='\0';}
  if(len==2){sprintf(binn,"000000%s",bin); binn[8]='\0';}
  if(len==3){sprintf(binn,"00000%s",bin);  binn[8]='\0';}
  if(len==4){sprintf(binn,"0000%s",bin);   binn[8]='\0';}
  if(len==5){sprintf(binn,"000%s",bin);    binn[8]='\0';}
  if(len==6){sprintf(binn,"00%s",bin);     binn[8]='\0';}
  if(len==7){sprintf(binn,"0%s",bin);      binn[8]='\0';}
  if(len==8){sprintf(binn,"%s",bin);       binn[8]='\0';}
  return binn;
}

int DetectVBR()
{
  int vbroffset;
  if(OneOrZero(11)==0)
  {
    if (OneOrZero(24)==1 && OneOrZero(25)==1)
      vbroffset=9;
    else
      vbroffset=17;
  }else
  {if(OneOrZero(12)==0)
  {
    if (OneOrZero(24)==1 && OneOrZero(25)==1)
      vbroffset=9;
    else
      vbroffset=17;
  }else
  { if (OneOrZero(24) == 1 && OneOrZero(25) == 1)
      vbroffset=17;
    else
      vbroffset=32;
  }
  }
  return vbroffset;
}

char enc_type[8];
int e_type=0; //0 CBR, 1-VBR
long header_dest_adr;
int allbit;

long readframe(char *file)   
{ 
  int type=2;
  int flag=0;
  long ii=0;
  long iii=0;
  int j=0;
  int off=0;
  long header_adr=0;
  int f;
  unsigned int err;
  char vbr[5];
  char bufff[20480];
  char bin1[9],bin2[9],bin3[9],bin4[9];
  if((f=fopen(file, A_ReadOnly, P_READ, &err))==-1)
  {
    ShowMSG(1,(int)"Unable to open file!");
    return 0;
  } 
  else
  {
    file_size=lseek(f,0,S_END,&err,&err);
  a:   
    lseek(f,ii,S_SET,&err,&err);
    fread(f,bufff,20480,&err);
    int bit_num;
    int bit_num2;
    for(j=0;j<20480; j++)
    {
      iii+=1;
      if(j==20479) {off+=1;flag=1;break;}
      bit_num=(int)bufff[j];
      bit_num2=(int)bufff[j+1];
      if(bit_num==255&&(bit_num2==250||bit_num2==251))
      {
        sprintf(bin1,per_s,bin2_8bytes(dec2bin((int)bufff[j])));
        bin1[8]='\0';
        sprintf(bin2,per_s,bin2_8bytes(dec2bin((int)bufff[j+1])));
        bin2[8]='\0';
        sprintf(bin3,per_s,bin2_8bytes(dec2bin((int)bufff[j+2])));
        bin3[8]='\0';
        sprintf(bin4,per_s,bin2_8bytes(dec2bin((int)bufff[j+3])));
        bin4[8]='\0';
        sprintf(binary,per_ssss,bin1,bin2,bin3,bin4);
        binary[32]='\0';
        if(crc()==1)
        {
          lseek(f,iii-1+4+DetectVBR(),S_SET,&err,&err);
          fread(f,vbr,4,&err);
          if(vbr[0]=='X'&&vbr[1]=='i'&&vbr[2]=='n'&&vbr[3]=='g')
            type=0;            
          if(vbr[0]=='V'&&vbr[1]=='B'&&vbr[2]=='R'&&vbr[3]=='I')
            type=1;
          switch(type)
          {
          case 0:
            {
              e_type=1;
              sprintf(enc_type,per_s,"VBR"); 
            }break;
          case 1:
          default:
            {   
              if(DetectVBR()!=32)
              {
                lseek(f,iii-1+4+32,S_SET,&err,&err);
                fread(f,vbr,4,&err);
                if(vbr[0]!='V'&&vbr[1]!='B'&&vbr[2]!='R'&&vbr[3]!='I')
                {
                  e_type=0;
                  sprintf(enc_type,per_s,"CBR");
                  break;
                }
              }
              else
              {
                e_type=0;
                sprintf(enc_type,per_s,"CBR");
                break;
              }              
            }
            e_type=1;
            sprintf(enc_type,per_s,"VBR");
          }
          ReadInfoFromHeaders();
          break;
        }
      }
    }
    if(flag==1){ii+=20479;flag=0;goto a;}
  }
  fclose(f,&err);
  header_adr=iii-off-1;
  return header_adr;
}
int frame=0;
void readframeS(char *file)   
{ 
  int f;
  unsigned int err;
  char buff[5];
  char bin1[9],bin2[9],bin3[9],bin4[9];
  if((f=fopen(file, A_ReadOnly, P_READ, &err))==-1)
  {
    ShowMSG(1,(int)"Unable to open file!");
    return;
  } 
  else
  {
    //for(int  i=0;i<20;i++)
    //{
  a:
    frame++;
      lseek(f,header_dest_adr,S_SET,&err,&err);
      fread(f,buff,4,&err); 
      sprintf(bin1,per_s,bin2_8bytes(dec2bin((int)buff[0])));
      bin1[8]='\0';
      sprintf(bin2,per_s,bin2_8bytes(dec2bin((int)buff[1])));
      bin2[8]='\0';
      sprintf(bin3,per_s,bin2_8bytes(dec2bin((int)buff[2])));
      bin3[8]='\0';
      sprintf(bin4,per_s,bin2_8bytes(dec2bin((int)buff[3])));
      bin4[8]='\0';
      sprintf(binary,per_ssss,bin1,bin2,bin3,bin4);
      ReadInfoFromHeaders();
      allbit=allbit+bitratee;
      header_dest_adr=header_dest_adr+frame_size;
      if(header_dest_adr<file_size/100) goto a;
      else goto eof;
   // }
  }
eof:
  fclose(f,&err);
}

void GetBit(char *fname)
{
  header_dest_adr=readframe(fname);
  if(e_type==1){
  readframeS(fname);
  bitratee=allbit/frame;
  allbit=0;
  }
  sprintf(flprp.mpg_ver,per_s,mpeg_vers);
  sprintf(flprp.layer,per_s,layer_vers);
  sprintf(flprp.bitrate,"%d kbps",bitratee);
  sprintf(flprp.freq,"%d kHz",freqq/1000);
  sprintf(flprp.chanl,per_s,channell);
  frame=0;
}

int fl=0;
int GetTime(char *fname)
{
  int tm=0;
 // int bit=0;
  header_dest_adr=readframe(fname);
  if(e_type==1){
  readframeS(fname);
  bitratee=allbit/frame;
  allbit=0;
  }
  tm=(8*file_size/1000)/bitratee;
  allbit=0;
  fl=0;
  frame=0;
  return tm;
}
