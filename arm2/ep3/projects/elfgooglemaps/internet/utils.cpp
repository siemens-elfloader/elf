#include "../include.h"
#include "utils.h"


unsigned int gethostname(const char *name)
{
    unsigned int A,B,C,D;
    sscanf(name,"%d.%d.%d.%d",&A,&B,&C,&D);
    return _htonl(IP_ADDR(A,B,C,D));
}

int get_headersize(char *buf)
{
    unsigned int h_size=0;
    int max_len=strlen(buf);
    while(h_size<max_len-3)
    {
        if(buf[h_size]=='\r'&&
           buf[h_size+1]=='\n'&&
           buf[h_size+2]=='\r'&&
           buf[h_size+3]=='\n')
           return h_size+4;
        h_size++;
    }
    return 0;
}
int is_file_exists(const char *file)
{
    FSTATS fs;
    if(GetFileStats(file,&fs,0)!=-1)return 1;
    return 0;
}

unsigned int get_file_size(const char *file)
{
    FSTATS fs;
    if(GetFileStats(file,&fs,0)==-1)return 0;
    else return fs.size;
}
