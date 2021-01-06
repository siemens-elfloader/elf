
// Find.h поиск файлов по шаблону *.*

#define maxlevel 6
DIR_ENTRY de[maxlevel], dee;
char tmp[maxlevel][256], temp[256], name[256], *etemp, *ename;
#define listsize 32*1024
char list[listsize], *lend=list; //список эльфов
//const char eline[]="\\";

inline void un(){ // Занесение имени файла temp в список
  int i;
  if(lend+(i=strlen(temp)+1)<list+listsize-3){
    memcpy(lend,temp,i);
    lend+=i;
  }
}

void extnn(char *dir, char *ext){ // Найти все эльфы в dir (использ.temp) кончается на '\'
  strcpy(temp,dir);
//  strcat(temp,eline);
  strcat(temp,ext);
  if (FindFirstFile(&dee,temp,&err)){
    do{
      strcpy(strrchr(temp,'\\')+1,SG?dee.file_name:((char*)&dee+169));
      un(); //занести в список
    }while(FindNextFile(&dee,&err));
  }
  FindClose(&dee,&err); 
}


void extn(char *dir, char *ext){ // Найти все эльфы в dir (использ.temp)
  strcpy(temp,dir);
  strcat(temp,eline);
  strcat(temp,ext);
  if (FindFirstFile(&dee,temp,&err)){
    do{
      strcpy(strrchr(temp,'\\')+1,SG?dee.file_name:((char*)&dee+169));
      un(); //занести в список
    }while(FindNextFile(&dee,&err));
  }
  FindClose(&dee,&err); 
}

void find( int level, char *s, char *ext){ // Найти все пути в s (рекурсивно)
  char *path;
  if(level<maxlevel){
    strcpy(path=tmp[level],s);
    extn(path,ext);
    strcat(path,"\\*.*");
    if(FindFirstFile(&de[level],path,&err)){
      do{
      strcpy(strrchr(path,'\\')+1,SG?de[level].file_name:((char*)&de[level]+169));
      if(*((char*)&de[level]+(SG?44:14))&0x10) //44 for newsgold
      //if(isdir(path,&err))
        find(level+1, path, ext);
    }while(FindNextFile(&de[level],&err));
    }
    FindClose(&de[level],&err);
  }
}

inline void reset(){ lend=list;}
