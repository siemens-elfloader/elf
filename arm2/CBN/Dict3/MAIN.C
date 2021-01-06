
//Dict 0.6 Eng-Rus

#define UNPACK // Распаковка архивов
#define NOZIP  // Кроме zip
#define NORAR  // Кроме rar
#include "..\mylib.h"
typedef unsigned char byte;
//extern int maxcnt; // Всего файлов в 7z архиве
//extern int un7zinit(char *buf); // Иниц-я
//extern char *un7z(int num); // Получить файл номер num
//extern void un7zexit(); // Выход
//extern char *un7znext(); // Распаковать следующий un7z файл

//char *data=0;
#define ewssize 2048
//256 было!!!
WSHDR *ews;
char filename[128], *file;

char *dict=0;
int loaded_dict=-1;
int dict_size=0;

//int icon[]={0x58,0};
const int minus11=-11;

char pt[]="%t";
//const char _percent_t[]="%t";
SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Лев"},
  {0x0001,0x0000,(int)"Прав"},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

void ed1_locret(void){}


void LoadDict(int num);

void ed1_ghook(GUI *data, int cmd){}

void doit(GUI *data){
  EDITCONTROL ec, ec2;
  char word[40], tmp[8192];
  int i,ii,d,len;
//  if (cmd==7)
  {
    ExtractEditControl(data,2,&ec);
    ExtractEditControl(data,4,&ec2);
    ws_2str(ec.pWS, word, 40);
    if((len=strlen(word))>0){
      if((i=*(byte*)word)<'c') d=0;
      else if (i<'e') d=1;
      else if (i<'h') d=2;
      else if (i<'m') d=3;
      else if (i<'p') d=4;      
      else if (i<'s') d=5;
      else if (i<'u') d=6; 
      else d=7;
      LoadDict(d);
//        if( *pos==*word && !strcmp(word, pos)){
//          pos+=strlen(pos)+1;
//          break;
//        } pos+=strlen(pos)+1;
      byte *s=(byte*)dict, *ss=(byte*)dict+dict_size;
//      if(dict){
//        memcpy(tmp,s+4,20);///
//        ShowMSG(1,(int)tmp);/////////
//      }  
      while(s<ss){
        ii=*(byte*)s|(*(byte*)(s+1)<<8);
        if((len==s[2] && *word==*(char*)(s+4) && !memcmp(word, s+4, s[2]))){
        //РУССКИЕ
        //memcpy(tmp,s+4,s[2]);  //русские
        //tmp[s[2]]=0;   //ч2
        //АНГЛИЙСК
          i=s[2]+4;
          memcpy(tmp,s+i,ii-i);
          tmp[ii-i]=0;
          break;
        }
        s+=ii;
      }
      if(s<ss){
        wsprintf(ec2.pWS, pt, tmp); //pt!!
        StoreEditControl(data ,4, &ec2);
      }else{
        wsprintf(ec2.pWS, pt, " ");//Нет вариантов"); 
//        wsprintf(ec2.pWS,"%d",debug); ///////////
        StoreEditControl(data ,4, &ec2);
      }
    }    
    else{
      wsprintf(ec2.pWS, pt, "Введите слово для перевода");
      StoreEditControl(data ,4, &ec2);
    }
  }
}

int onkey(GUI *data, unsigned char keycode, int pressed){
  if(pressed==KEY_DOWN){
    switch(keycode){
    case ENTER_BUTTON: doit(data); return -1;
//    case '7': return 1;
    }
  }
  return 0;
}

int ed1_onkey(GUI *data, GUI_MSG *msg)
{
  //-1 - do redraw
 // return(0); //Do standart keys
  //1: close
    return onkey(data, msg->gbsmsg->submess, msg->gbsmsg->msg);
}


HEADER_DESC ed1_hdr={0,0,131,21,NULL,(int)"Eng-Rus cловарь",0x7FFFFFFF};

INPUTDIA_DESC ed1_desc=
{
  1,
  ed1_onkey,
  ed1_ghook,
  (void *)ed1_locret,
  0,
  &menu_skt,
  {0,22,131,153},
  4,
  100,
  101,
  0,

//  0x00000001 - Выровнять по правому краю
//  0x00000002 - Выровнять по центру
//  0x00000004 - Инверсия знакомест
//  0x00000008 - UnderLine
//  0x00000020 - Не переносить слова
//  0x00000200 - bold
  0,

//  0x00000002 - ReadOnly
//  0x00000004 - Не двигается курсор
//  0x40000000 - Поменять местами софт-кнопки
  0
};

int create_ed(void)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;

  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());

  wsprintf(ews,pt, "Слово для перевода:");
  ConstructEditControl(&ec,1,0x40,ews,ewssize);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,pt,"");
  ConstructEditControl(&ec,3,0x40,ews,ewssize);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,pt,"Перевод:");
  ConstructEditControl(&ec,1,0x40,ews,ewssize);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,pt,"Введите слово для перевода");
  ConstructEditControl(&ec,1,0x40,ews,ewssize);
  AddEditControlToEditQend(eq,&ec,ma);

  return CreateInputTextDialog(&ed1_desc,&ed1_hdr,eq,1,0);
}

//void ErrorMsg(const char *msg)
//{
//  LockSched();
//  ShowMSG(1,(int)msg);
//  UnlockSched();
//}

void Killer(void)
{
  extern void *ELF_BEGIN;
  extern void kill_data(void *p, void (*func_p)(void *));
  //un7zexit();
//  if(data) mfree(data);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

//int loadfilesize=0;

//char *loadfile(char *filename){ // Загрузить файл, распак-ть
//  int f; unsigned int err;  char *buf=0;
//  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
//    if(loadfilesize=lseek(f,0,2,&err,&err)){
//      buf=(char*)malloc(loadfilesize);
//      lseek(f,0,0,&err,&err);
//      if(fread(f,buf,loadfilesize,&err)!=loadfilesize){ mfree(buf); buf=0;}
//    } fclose(f,&err);
////    extern char *unzip(char *buf);
//    if(buf && loadfilesize>4){
////      if(*(int*)buf==0x4034b50) buf=unzip(buf); //unzip
//    }
//  } return buf;
//}

void LoadDict(int num){
  if (loaded_dict!=num){
    if(dict) mfree(dict);
    *file=num+'0';
    if(dict=loadfile(filename)){
      dict_size=loadfilesize;
      loaded_dict=num;
    }else{
//      ShowMSG(1,(int)"No Dict");//
      dict_size=0;
      loaded_dict=-1;
//      debug=-1-maxcnt;
    }
//    if (dict != 0)
//      mfree(dict);
//    char fname[40];
//    sprintf(fname, "0:\\ZBin\\dictionary\\dict\\%d.zip", num);
//    if(!(dict=loadfile(fname))){
//      *fname='4';
//      dict=loadfile(fname);
//    }
//    dict_size=loadfilesize;
//    if(dict) loaded_dict=num;
//    else loaded_dict=0;
  }
}

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  ews=AllocWS(ewssize);
  csm->gui_id=create_ed();
//  LoadDict(3);
}

void maincsm_onclose(CSM_RAM *csm)
{
  FreeWS(ews);
  if(dict) mfree(dict);
  SUBPROC((void *)Killer);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->gui_id)
    {
      /*if (ed1_desc._0x40000000)
      {
	ed1_desc._0x40000000<<=1;
	csm->gui_id=create_ed();
      }
      else*/
      {
	csm->csm.state=-3;
      }
    }
  }
  return(1);
}

unsigned short maincsm_name_body[140];

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

void UpdateCSMname(void){
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Eng-Rus (c)bn");
}

int main(char *exename){
  char dummy[sizeof(MAIN_CSM)];
  strcpy(filename,exename);
  file=filename+strlen(filename)-4;
  memcpy(file,"0.dic",6);
//  if((data=loadfile(exename)) && un7zinit(data)){
    LockSched();
    UpdateCSMname();
    CreateCSM(&MAINCSM.maincsm,dummy,0);
    UnlockSched();
//  }else SUBPROC((void *)Killer);
  return 0;
}
