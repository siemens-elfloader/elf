
int fread32(int fh, void *buf, int len, unsigned int *err){
  int clen, rlen, total=0;
  while(len){
  if (len>16384) clen=16384; else clen=len;
  total+=(rlen=fread(fh, buf, clen, err));
  if (rlen!=clen) break;
  buf=(char*)buf+rlen;
  len-=clen;
  }return(total);
}

int fwrite32(int fh, void *buf, int len, unsigned int *err){
  int clen, rlen, total=0;
  while(len){
  if (len>16384) clen=16384; else clen=len;
  total+=(rlen=fwrite(fh, buf, clen, err));
  if (rlen!=clen) break;
  buf=(char*)buf+rlen;
  len-=clen;
  }return(total);
}