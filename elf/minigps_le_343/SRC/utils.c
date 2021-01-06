#include "swilib.h"
#include "utils.h"
#include <stdarg.h>
#define byte unsigned char

char per_s[]="%s";
char per_ss[]="%s%s";
char file_r[]="r";
char file_w[]="w";
char file_p[]="+";
char file_b[]="b";

void showerror(char *message, int errorcode)
{
  char error[128];
  if (errorcode != 0)
  {
    sprintf(error, "%s: %u", message, errorcode);
  }
  else
  {
    sprintf(error, per_s, message);
  }
    ShowMSG(1,(int)error);
}

void readpos(int hFile, int pos, void *data, int length)
{
  unsigned int errcode = 0;
  lseek(hFile, pos, 0, &errcode, &errcode);
  fread(hFile, data, length, &errcode);
}

void writepos(int hFile, int pos, void *data, int length)
{
  unsigned int errcode = 0;
  lseek(hFile, pos, 0, &errcode, &errcode);
  fwrite(hFile, data, length, &errcode);
}

int get_file_size(char* fname)
{
  int f;
  unsigned int err;
  FSTATS fs;
  if ((f=GetFileStats(fname,&fs,&err))==-1)
    return f;
  return (fs.size);
}

int rgbwidth(int Width, int bits)
{
  if (bits == 24)
  {
    return (Width * 3 + 3) & 0xFFFFFFFC;
  }
  else if (bits == 32)
  {
    return (Width * 4);
  }
   
  return 0;
}

void getrgb(int color, int *r, int *g, int *b)
{
  *r = color % 256;
  *g = (color / 256) % 256;
  *b = color / 256 / 256;
  if (*r < 0)
  {
    *r = 0;
  }
  else if (*r > 255)
  {
    *r = 255;
  }
  
  if (*g < 0)
  {
    *g = 0;
  }
  else if (*g > 255)
  {
    *g = 255;
  }
  
  if (*b < 0)
  {
    *b = 0;
  }
  else if (*b > 255)
  {
    *b = 255;
  }
}

void readposbuffered(int hFile, int pos, void *data, int length, FILEBUFFER *buffer)
{
  if ((*buffer).b_pos < 0)
  {
    readpos(hFile, pos, (*buffer).data, BUFFER_SIZE);
    (*buffer).b_pos = pos;
    memcpy(data, (*buffer).data, length);
  }
  else if ((BUFFER_SIZE < length) || (pos < (*buffer).b_pos))
  {
    readpos(hFile, pos, data, length);
  }
  else if (pos + length > (*buffer).b_pos + BUFFER_SIZE)
  {
    readpos(hFile, pos, (*buffer).data, BUFFER_SIZE);
    (*buffer).b_pos = pos;
    memcpy(data, (*buffer).data, length);
  }
  else if (length == 1)
  {
    byte *bdata = (byte *)data;
    bdata[0] = (*buffer).data[pos - (*buffer).b_pos];
  }
  else
  {
    memcpy(data, (byte *)((int)(*buffer).data + pos - (*buffer).b_pos), length);
  }
}

int read32pos(int hFile, int pos, void *data, int length)
{
  unsigned int errcode = 0;
  lseek(hFile, pos, 0, &errcode, &errcode);
  return fread32(hFile, data, length, &errcode);
}

int fread32(int fh, void *buf, int len, unsigned int *err)
{
  int clen;
  int rlen;
  int total=0;
  while(len)
  {
    clen=len>=0x4000?0x4000:len;
    total+=(rlen=fread(fh, buf, clen, err));
    if (rlen!=clen) break;
    buf=(char *)buf+rlen;
    len-=clen;
  }
  return(total);
}

unsigned int write32pos(int hFile, int pos, void *data, int length)
{
  unsigned int errcode = 0;
  lseek(hFile, pos, 0, &errcode, &errcode);
  return fwrite32(hFile, data, length, &errcode);
}

unsigned int fwrite32(int fh, void *buf, int len, unsigned int *err)
{
  int clen;
  unsigned int wlen;
  int total=0;
  while(len)
  {
    clen=len>=0x4000?0x4000:len;
    total+=(wlen=fwrite(fh, buf, clen, err));
    if (wlen!=clen) break;
    buf=(char *)buf+wlen;
    len-=clen;
  }
  return(total);
}

void str_append(char *string, char *app)
{
  char *tmpstring = (char *)malloc(strlen(string) + 1);
  sprintf(tmpstring, per_s, string);
  sprintf(string, per_ss, tmpstring, app);
  mfree(tmpstring);
}

int open(char *filename, int mode, int perm)
{
  unsigned int errcode = 0;
  return fopen(filename, mode, perm, &errcode);
}

int close(int hFile)
{
  unsigned int errcode = 0;
  fclose(hFile, &errcode);
  return errcode;
}

int checkfile(char *filename)
{
  int hFile = -1;
  hFile = open(filename, A_ReadOnly, P_READ);
  if (hFile == -1)
  {
    return 0;
  }
  close(hFile);
  return 1;
}

int read(int hFile, void *data, int length)
{
  unsigned int errcode = 0;
  int r = fread32(hFile, data, length, &errcode);
  return (r == 0 ? -1 : r);
}

int write(int hFile, void *data, int length)
{
  unsigned int errcode = 0;
  return fwrite32(hFile, data, length, &errcode);
}

int __write(int hFile, void *data, int length)
{
  return write(hFile, data, length);
}

int fprintf(int hFile, const char *fmt, ...)
{
  va_list ap;
  char buf[4096];
  int ret;

  va_start(ap, fmt);
  sprintf(buf, fmt, ap);
  ret = write(hFile, buf, strlen(buf));
  va_end(ap);
  return ret;
}

int dlseek(int hFile, int offset, int mode)
{
  unsigned int errcode = 0;
  return lseek(hFile, offset, mode, &errcode, &errcode);
}

int strpos(char *source, char *search)
{
  int slen = strlen(source);
  int sslen = strlen(search);
  
  if (sslen > slen)
  {
    return -1;
  }
  
  int search_count = (slen - sslen) + 1;
  for (int i = 0; i < search_count; i++)
  {
    int wrong = 0;
    for (int j = 0; j < sslen; j++)
    {
      if (search[j] != source[i + j])
      {
        wrong = 1;
        break;
      }
    }
    if (wrong == 0)
    {
      return i;
    }
  }
  return -1;
}

WSHDR * char2WSHDR(const char *data)
{
  WSHDR *ws0 = AllocWS(strlen(data) + 4 /*???*/);
  str_2ws(ws0, data, strlen(data) * 2);
  return ws0;
}

void str2WSHDR(WSHDR *ws0, const char *data)
{
  str_2ws(ws0, data, strlen(data) * 2);
}
