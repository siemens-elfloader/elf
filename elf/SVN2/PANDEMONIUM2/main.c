#include "include.h" 

extern void InitConfig();

PandemonuimDialog * maincsm;

char basepath[128];

int main(char * exename)
{ 
  InitConfig();
  
  strcpy(basepath,exename);
  strrchr(basepath,'\\')[1]=0;
    
//create csm  
  maincsm = new PandemonuimDialog();
  maincsm->Create();  
  return 0;
}



