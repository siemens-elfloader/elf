
//Dict 0.5 Rus-eng

//без define
#include "..\mylib.h"
typedef unsigned char byte;
extern int maxcnt; // Всего файлов в 7z архиве
extern int un7zinit(char *buf); // Иниц-я
extern char *un7z(int num); // Получить файл номер num
extern void un7zexit(); // Выход
extern char *un7znext(); // Распаковать следующий un7z файл

char rus[]=\
  "абвгдеёж"\
  "зийклмно"\
   "прстуфхц"\
   "чшщъыьэюя";
unsigned short wscode[]={//0x1f start
  0xd0b0, 0xd0b1, 0xd0b2, 0xd0b3, 0xd0b4, 0xd0b5, 0xd191, 0xd0b6, 
  0xd0b7, 0xd0b8, 0xd0b9, 0xd0ba, 0xd0bb, 0xd0bc, 0xd0bd, 0xd0be, 
  0xd0bf, 0xd180, 0xd181, 0xd182, 0xd183, 0xd184, 0xd185, 0xd186, 
  0xd187, 0xd188, 0xd189, 0xd18a, 0xd18b, 0xd18c, 0xd18d, 0xd18e, 0xd18f, 0
};

char *data=0;
WSHDR *ews;

char *dict=0;
int loaded_dict=-1;
int dict_size=0;

//int icon[]={0x58,0};
const int minus11=-11;

char pt[]="%t";
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


void decode(char *to, byte *from){
  unsigned short i, *p;
  while(*++from){
    if(*from==0xd0 || *from==0xd1){
      p=wscode;
      i=(*from<<8)|*(from+1);
      while(*p && *p!=i) ++p;
      if(*p) *to++=rus[p-wscode];
      if(!*++from) break;
    }else *to++=*from;
  }
  *to=0;
}


void doit(GUI *data){
  EDITCONTROL ec, ec2;
  char word[40];
  byte tmp[256];//8192
  int i,ii,d,len;
//  if (cmd==7)
  {
    ExtractEditControl(data,2,&ec);
    ExtractEditControl(data,4,&ec2);
    ws_2str(ec.pWS, word, 40);
    if(strlen(word)>0 && *word==0x1f){
      decode(tmp,word);
      if((len=strlen(tmp))>0){
              //sprintf(tmp,"%x %x %x %x",word[0],word[1],word[2],word[3]);////
              //  ShowMSG(1,(int)tmp);///////
      if(tmp[0]<'л') d=0;
      else if(tmp[0]<'р') d=1;
      else d=2;
      LoadDict(d);
//        if( *pos==*word && !strcmp(word, pos)){
//          pos+=strlen(pos)+1;
//          break;
//        } pos+=strlen(pos)+1;
      byte *s=(byte*)dict, *ss=(byte*)dict+dict_size;
      while(s<ss){
        ii=*s|(s[1]<<8);
        if(len==s[2] && *tmp==*(char*)(s+4) && !memcmp(tmp, s+4, s[2])){
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
        wsprintf(ec2.pWS, pt, tmp); 
        StoreEditControl(data ,4, &ec2);
      }else{
        wsprintf(ec2.pWS, pt, " "); 
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
//  return(0); //Do standart keys
  //1: close
  return onkey(data, msg->gbsmsg->submess, msg->gbsmsg->msg);
}


HEADER_DESC ed1_hdr={0,0,131,21,NULL,(int)"Rus-Eng cловарь",0x7FFFFFFF};

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

  wsprintf(ews,pt,"Слово для перевода:");
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,pt,"");
  ConstructEditControl(&ec,3,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,pt,"Перевод:");
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,pt,"Введите слово для перевода");
  ConstructEditControl(&ec,1,0x40,ews,256);
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
  un7zexit();
  if(data) mfree(data);
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
    dict=un7z(num);
    if(dict){ 
      dict_size=loadfilesize;
      loaded_dict=num;
    } else{
//      ShowMSG(1,(int)"No dict");
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
  ews=AllocWS(256);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Rus-Eng 0.5 (c)bn",8);
}

int main(char *exename){
  char dummy[sizeof(MAIN_CSM)];
  memcpy(exename+strlen(exename)-3,"dic",4);
  if((data=loadfile(exename)) && un7zinit(data)){
    LockSched();
    UpdateCSMname();
    CreateCSM(&MAINCSM.maincsm,dummy,0);
    UnlockSched();
  }else SUBPROC((void *)Killer);
  return 0;
}
