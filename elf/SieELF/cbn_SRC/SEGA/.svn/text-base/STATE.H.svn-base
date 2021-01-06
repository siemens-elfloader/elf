#ifndef _STATE_H_
#define _STATE_H_

//#define GENZ_SAVESDIR ""
#define STREAM int
#define OPEN_STREAM fopen
#define CLOSE_STREAM fclose
//#define READ_STREAM(a,b,c) fread(c,b,a) //fread(a,1,b,c);
//#define WRITE_STREAM(a,b,c) fwrite(c,b,a) //fwrite(a,1,b,c);

#define READ(val, size) fread(file,val,size,&err)
#define WRITE(val, size) fwrite(file,val,size,&err)

int state_load(int num);
int state_save(int num);
void save_sram(void);
void load_sram(void);

extern char romname[256];

#endif
