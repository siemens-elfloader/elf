/*
* Ping-Pong 2009 - 2010
* save
* (c) Danil_e71
*/

#include "save.h"

void parserecord(int mode)
{
  switch(mode)
  {
  case 1:
  for(int i=0;i<NUM_RECORD;i++)
 {
  if(user.lifetime>record.points[i]||cpu.lifetime>record.points[i])
  {
    for(int a=NUM_RECORD;a>i;a--)
    {
    strcpy(record.name[a],record.name[a-1]);
    record.points[a]=record.points[a-1];
    }
    if(user.lifetime>=record.points[i]&&user.lifetime>=cpu.lifetime)
    {
    strcpy(record.name[i],name);
    record.points[i]=user.lifetime;
    }
    if(cpu.lifetime>record.points[i]&&cpu.lifetime>user.lifetime)
    {
    strcpy(record.name[i],"Cpu");
    record.points[i]=cpu.lifetime;
    }
    break;
  }
}
  break;
  default:
  for(int i=0;i<NUM_RECORD;i++)
{
  strcpy(record.name[i],lang[36]);
  record.points[i]=0;
}  
}
user.lifetime=cpu.lifetime=0;
}

void savedata(int mod)
{
parserecord(mod);
folders=malloc(sizeof(folder)+strlen("data.sys")+1);
strcpy(folders,folder);
strcat(folders,"data.sys");
int f = fopen(folders,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,0);
if(f!=-1)
{
fwrite(f,&langenru,sizeof(langenru),0);
fwrite(f,&saveload,sizeof(saveload),0);
fwrite(f,&mode,sizeof(mode),0);
fwrite(f,&on_off_sound,sizeof(on_off_sound),0);
fwrite(f,&difficult,sizeof(difficult),0);
fwrite(f,&speed_game,sizeof(speed_game),0);
fwrite(f,&lives,sizeof(lives),0);
fwrite(f,&def_vol,sizeof(def_vol),0);
fwrite(f,&vibra,sizeof(vibra),0);
fwrite(f,&record,sizeof(record),0);
fclose(f,0);
}
mfree(folders);
}

void loadNastr()
{
folders=malloc(sizeof(folder)+strlen("data.sys")+1);
strcpy(folders,folder);
strcat(folders,"data.sys");
int f = fopen(folders,A_ReadOnly+A_BIN,P_READ,0);
if(f!=-1)
{
fread(f,&langenru,sizeof(langenru),0);
fread(f,&saveload,sizeof(saveload),0);
fread(f,&mode,sizeof(mode),0);
fread(f,&on_off_sound,sizeof(on_off_sound),0);
fread(f,&difficult,sizeof(difficult),0);
fread(f,&speed_game,sizeof(speed_game),0);
fread(f,&lives,sizeof(lives),0);
fread(f,&def_vol,sizeof(def_vol),0);
fread(f,&vibra,sizeof(vibra),0);
fread(f,&record,sizeof(record),0);
fclose(f,0);
lgpInitLangPack();
T_Load_IMG();
}
else
{
isload=1;
load_lang();
}
mfree(folders);
}

void saveSettings()
{
folders=malloc(sizeof(folder)+strlen("save\\savedata.pp")+1);
strcpy(folders,folder);
strcat(folders,"save\\savedata.pp");
int f = fopen(folders,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,0);
if(f!=-1)
{
fwrite(f,&user,sizeof(Mytype),0);
fwrite(f,&cpu,sizeof(Mytype),0);
fwrite(f,&ball,sizeof(Mytype),0);
fwrite(f,&mode,sizeof(mode),0);
fwrite(f,&on_off_sound,sizeof(on_off_sound),0);
fwrite(f,&AI_line,sizeof(AI_line),0);
fwrite(f,&Time,sizeof(Time),0);
fclose(f,0);
}
mfree(folders);
saveload=2;
RedrawScreen();
}

void loadSettings()
{
folders=malloc(sizeof(folder)+strlen("save\\savedata.pp")+1);
strcpy(folders,folder);
strcat(folders,"save\\savedata.pp");
int f = fopen(folders,A_ReadOnly+A_BIN,P_READ,0);
if(f!=-1)
{
fread(f,&user,sizeof(Mytype),0);
fread(f,&cpu,sizeof(Mytype),0);
fread(f,&ball,sizeof(Mytype),0);
fread(f,&mode,sizeof(mode),0);
fread(f,&on_off_sound,sizeof(on_off_sound),0);
fread(f,&AI_line,sizeof(AI_line),0);
fread(f,&Time,sizeof(Time),0);
fclose(f,0);
saveload=1;
game_new_cont=3;
RedrawScreen();
}
else
{
 RedrawScreen(); 
}
mfree(folders);
}
