#include "include.h"


#define CHUNK 64

//TDaemonList::

TDaemonList::TDaemonList()
{
  //
  // 5 марта 2009, tridog
  //
  // —овместимость с SafeMode
  //
  unsigned int err;
  extern char * successed_config_filename;
  // »щем вложенную папку Daemons на диске, на котором нашли конфиг
  sprintf(daemon_path, "%c%s", successed_config_filename[0], ":\\ZBin\\daemons\\daemons\\");
  if (!isdir((daemon_path),&err))
  {
    sprintf(daemon_path, "%c%s", successed_config_filename[0], ":\\ZBin\\daemons\\");  
  }
  //
  //
  daemons=NULL;
  count=0;
  reboot_required=0;
  Load();  
};


TDaemonList::~TDaemonList()
{
  if(daemons!=NULL) delete daemons;
};

int TDaemonList::enabled_size()
{
  int s=0;
  for(int i=0;i<count;i++)
    s+=daemons[i].size;
  return s;
};



void TDaemonList::qsort_daemons(TDaemon * a,int N)
{
  if(N<=0) return;
  int i = 0, j = N;
  TDaemon temp;
  char p[128];
  strcpy(p,a[ N>>1].name);
  
  
  do {
    while ( stricmp(a[i].name,p)<0/*a[i] < p*/) i++;
    while ( stricmp(a[j].name,p)>0/*a[j] > p*/) j--;
    if (i <= j) {
      temp = a[i]; a[i] = a[j]; a[j] = temp;
      i++; j--;
    }
  } while ( i<=j );


  // рекурсивные вызовы, если есть, что сортировать 
  if ( j > 0 ) qsort_daemons(a, j);
  if ( N > i ) qsort_daemons(a+i, N-i);
};


void TDaemonList::Load()
{
  count=0;
  total_size=0;
  if(daemons!=NULL) {delete daemons;daemons=NULL;};
  DIR_ENTRY de;
  unsigned int err;
  TDaemon * d;
  
  char name[256];  
  int len;
  
  //enabled ones  
  strcpy(name,daemon_path);
  strcat(name,"*.elf");  
  
  if (FindFirstFile(&de,name,&err))
    {      
    do
      {    
          if(count%CHUNK==0) daemons=(TDaemon*)realloc(daemons,(count+CHUNK)*sizeof(TDaemon));
          d=daemons+count;
          count++;
          len=strrchr(de.file_name,'.')-de.file_name;
          strncpy(d->name,de.file_name,len);        
          d->name[len]=0;
          d->size=de.file_size;
          total_size+=d->size;
          d->mode=MODE_ENABLED_NEW|MODE_ENABLED_OLD;
      }
    while(FindNextFile(&de,&err));
    FindClose(&de,&err);
    qsort_daemons(daemons,count-1);
    };
    
  int lb=count;
  //disabled ones  
  strcpy(name,daemon_path);
  strcat(name,"*.fakk");
  if (FindFirstFile(&de,name,&err))
    {
    do
      {
          if(count%CHUNK==0) daemons=(TDaemon*)realloc(daemons,(count+CHUNK)*sizeof(TDaemon));
          d=daemons+count;
          count++;
          len=strrchr(de.file_name,'.')-de.file_name;
          strncpy(d->name,de.file_name,len);        
          d->name[len]=0;
          d->size=de.file_size;
          total_size+=d->size;
          d->mode=MODE_UPDATEABLE;          
      }
    while(FindNextFile(&de,&err));
    FindClose(&de,&err);
    qsort_daemons(daemons+lb,count-lb-1);  
    };  
};

void TDaemonList::Save(int update)
{
reboot_required=0;
TDaemon * d=daemons;
for(int i=0;i<count;i++,d++)  
  {
  int mode=d->mode;
  if((mode&MODE_ENABLED_NEW?1:0)^(mode&MODE_ENABLED_OLD?1:0))
    {
    char elfpath[192];
    char fakkpath[192];
    unsigned int err;
    strcpy(elfpath,daemon_path);
    strcat(elfpath,d->name);
    strcpy(fakkpath,elfpath);
    strcat(elfpath,".elf");
    strcat(fakkpath,".fakk");    
    if(mode&MODE_ENABLED_NEW)
      {        
      fmove(fakkpath,elfpath,&err);      
      if(update && mode&MODE_UPDATEABLE)
        {
          WSHDR * ws = AllocWS(256);
          str_2ws(ws,elfpath , 256);
          ExecuteFile(ws, 0, 0);
          FreeWS(ws);
        };
      }
    else
      {
      if(update)
        {
        if(mode&MODE_UPDATEABLE)
          {
          ShowMSG(2,(int)"Unsupported action!");
          }
        else
          reboot_required=1;  
        };

      fmove(elfpath,fakkpath,&err);      
      };    
//    if(err)
//      { 
//      static char errbu[256];
//      sprintf(errbu,"'%s'<->'%s' failed!",elfpath,fakkpath);
//      ShowMSG(2,(int)errbu);
//      };
    };
  };
Load();
};




