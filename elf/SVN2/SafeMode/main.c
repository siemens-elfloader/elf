#include "../inc/swilib.h" 
#include "conf_loader.h"

extern const int b_welcome_message;
extern const char s_welcome_message[128];
extern const int i_questions;
extern const char s_activation_key[128];
extern const char s_path[128];
extern const int b_refresher;
extern const char daemons_path[128];
extern const int active_profile;

WSHDR* run_elf;
int is_safe;
char app_path[512];
char app_exe[512];
char Message[128];
unsigned int err;
int in;

#pragma swi_number=0x00BE
__swi __arm void RunScaner();

#pragma swi_number=0x80E2
__swi __arm char *RamKeyBuffer();

void RefreshMP (int res)
{
  if (!res)
  {
    RunScaner();    
  }
}
    
void ShowWelcome()
{
  if (is_safe == 1)
  {
    if (b_welcome_message == 1)
      {
        ShowMSG(1, (int)s_welcome_message);
      }
  } 
}

void run(int res)
{
  if (!res)
  {
    ExecuteFile(run_elf,0,0); 
  }
}

void runall(int res)
{
  if(!res)
  {
    if (isdir(app_path, &err) == 1)
    {
      sprintf(app_path, "%s%s", app_path, "*.elf");
      DIR_ENTRY dE;
      WSHDR*wS;
      wS=AllocWS(196);
      if (FindFirstFile(&dE,app_path,&err))
      {
        do
        {
          wsprintf(wS,"%s\\%s",dE.folder_name,dE.file_name);
          if ((is_safe == 0) | ((is_safe == 1) & (i_questions == 1)))
          {
            run_elf = wS;  
            run(0);
          }
          if ((is_safe == 1) & (i_questions == 2))
          {
              run_elf=AllocWS(64);
              str_2ws(run_elf,app_exe,strlen(app_exe)+1);  
              ExecuteFile(run_elf, 0, dE.file_name);
              FreeWS(run_elf);
          }
        }while(FindNextFile(&dE,&err));
      }
      FindClose(&dE,&err);
      FreeWS(wS);
    }
    else
    {
      sprintf(Message, "%s%s", app_path, " not found!");
      ShowMSG(1, (int)Message);
    }
  }
  if (i_questions ==2)
  {
    ShowWelcome();
  }
}

int main(const char *exename, const char *filename)
{
  char file[512]  = "";
  char *path=strrchr(exename,'\\');
  int l;
  if (!path) return 0; //‘игн€ кака€-то
  path++;
  l=path-exename;
  memcpy(app_path,exename,l);
    if (strlen(daemons_path) == 0) //провер€ем, если путь пуст, то делаем постаринке
     {
      sprintf(file, "%s%s", app_path, "Daemons\\");
     }
    else //провер€ем, если путь Ќ≈ пуст, то делаем о нашему
     {
      sprintf(file, daemons_path);
     } 
  strcpy(app_exe, exename);  
  InitConfig();
  unsigned int err;
  int f;
  sprintf(file, "%s%s", file, filename);
  if(f=fopen(file,A_ReadOnly+A_BIN,P_READ,&err)!=-1)
  {
    fclose(f,&err);
    sprintf(Message, "%s%s", "Run ", filename);
    sprintf(Message, "%s%s", Message, "?");
    run_elf = AllocWS(64);
    str_2ws(run_elf,file,strlen(file)+1);
    MsgBoxYesNo(1, (int)Message, run);
  }
  else
  {
#ifdef NEWSGOLD 
    if (*RamPressedKey()== *s_activation_key||GetProfile()== active_profile-1) 
#else 
    if (*RamKeyBuffer()== *s_activation_key||GetProfile()== active_profile-1)        
#endif
    {
      is_safe = 1; 
    }
    else
    {
      is_safe = 0;
    }
    // welcome
    if ((is_safe == 1) & (i_questions == 0))
    {
      ShowWelcome();
      return 0;
    }
    // mp
    if (b_refresher == 1)
    {
      if (is_safe == 1)
      {
        MsgBoxYesNo(1, (int)"Apply mp-based patchs?", RefreshMP);
      }
      else
      {
        RefreshMP(0);
      }
    }
    //daemons
    if (strlen(daemons_path) == 0)  //провер€ем, если путь пуст, то делаем постаринке
     {
      sprintf(app_path, "%s%s", app_path, "Daemons\\");
     }
    else  //провер€ем, если путь Ќ≈ пуст, то делаем о нашему
     {
      sprintf(app_path, daemons_path);
     }
    if ((is_safe == 1) & (i_questions == 1)) 
    {
      MsgBoxYesNo(1, (int)"Load deamons?", runall);
      ShowWelcome();
    }
    if ((is_safe == 0) | ((is_safe == 1) & (i_questions == 2)))
    {
      runall(0);
    }
  }
  return 0;
}
