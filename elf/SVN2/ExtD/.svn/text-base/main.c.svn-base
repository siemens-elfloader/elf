#include "../inc/swilib.h"

extern long  strtol (const char *nptr,char **endptr,int base);
extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

CSM_DESC icsmd;
void (*old_icsm_onClose)(CSM_RAM*);

const char empty_str[]="";

const char *uni_elf="";

struct
{
  const char *uni_large;
  int zero_ul;
};

struct
{
  const char *uni_small;
  int zero_us;
};

const char *uni_altelf="";

typedef struct
{
  const char *ext;
  const char *small_png;
  int zero_small;
  const char *large_png;
  int zero_large;
  const char *elf;
  const char *altelf;
}ES;

int ES_num=0;

ES *es=NULL; //Указатель на массив структур
char *CFG=NULL; //Указатель на загруженный extension.cfg

const char default_ext[]="txt";

int do_elf(WSHDR *filename, WSHDR *ext, void *param, int mode)
{
  int i=0;
  char s[128];
  ws_2str(ext,s,126);
  ES *p=es;
  if (!*s) strcpy(s,default_ext);
  do
  {
    if (!strcmp(s,p->ext))
    {
      WSHDR *elfname=AllocWS(256);
      str_2ws(elfname,mode?p->altelf:p->elf,126);
      ws_2str(filename,s,126);
      i=ExecuteFile(elfname,NULL,s);
      FreeWS(elfname);
      return(i);
    }
    p++;
    i++;
  }
  while(i<ES_num);
  return(0);
}

int do_ext(WSHDR *filename, WSHDR *ext, void *param)
{
  return do_elf(filename,ext,param,0);
}

int do_alternate(WSHDR *filename, WSHDR *ext, void *param)
{
  return do_elf(filename,ext,param,1);
}

REGEXPLEXT reg=
#ifdef NEWSGOLD
{
  NULL,
  0x55,
  0xFF,
  8, //Каталог Misc
  MENU_FLAG2,
  NULL,
  NULL,
  (int)"Open",    //LGP "Открыть"
  (int)"AltOpen", //LGP "Опции"
  LGP_DOIT_PIC,
  (void *)do_ext,
  (void *)do_alternate
};
#else
{
  NULL,
  0x55,
  0xFF,           //Опции без "Задать как..."
  7,
  MENU_FLAG2, 
  NULL,
  NULL,
  (void *)do_ext,
  (void *)do_alternate
};
#endif

REGEXPLEXT reg0=
#ifdef NEWSGOLD
{
  empty_str,
  0,
  0xFF,
  8, //Каталог Misc
  MENU_FLAG2,
  NULL,
  NULL,
  (int)"Open",    //LGP "Открыть"
  (int)"AltOpen", //LGP "Опции"
  LGP_DOIT_PIC,
  (void *)do_ext,
  (void *)do_alternate
};
#else
{
  NULL,
  0x7FFFFFFF,
  0,
  7,
  MENU_FLAG2, 
  NULL,
  NULL,
  (void *)do_ext,
  (void *)do_alternate
};
#endif

void UnregAll()
{
  int i=0;
  ES *p=es;
  while(i<ES_num)
  {
    reg.ext=p->ext;
    reg.unical_id=i+0x56;
    UnRegExplorerExt(&reg);
    i++;
    p++;
  }
  UnRegExplorerExt(&reg0);
  mfree(es); //Отпускаем
  mfree(CFG);
}

void MyIDLECSM_onClose(CSM_RAM *data)
{
  extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  extern void *ELF_BEGIN;
  UnregAll();
  seqkill(data,old_icsm_onClose,&ELF_BEGIN,SEQKILLER_ADR());
}

void Killer(void)
{
  extern void *ELF_BEGIN;
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static const char extfile[]="?:\\ZBin\\etc\\extension.cfg";

char *find_eol(char *s)
{
  int c;
  s--;
  do
  {
    s++;
    c=*s;
  }
  while((c)&&(c!=10)&&(c!=13));
  return s;
}

int main(const char *exename)
{
  char *s;
  int c;
  int f;
  unsigned int ul;
  unsigned int size_cfg;

  WSHDR *xws;

  ES *p=NULL;
  int i;
  
  uni_large=empty_str;
  uni_small=empty_str;
  
  ((char *)extfile)[0]=exename[0];
  
  if ((f=fopen(extfile,A_ReadOnly,P_READ,&ul))!=-1)
  {
    size_cfg=lseek(f,0,S_END,&ul,&ul);
    lseek(f,0,S_SET,&ul,&ul);
    s=CFG=malloc(size_cfg+1);
    if (s)
    {
      s[fread(f,s,size_cfg,&ul)]=0;
      //Теперь файл загружен
      while((c=*s)) //Пока не конец файла
      {
	if ((c==10)||(c==13))
	{
	  s++;
	  continue; //Конец строки, опять с начала строки
	}
        if (c==';')
        {
	  //Комментарий
          s=find_eol(s);
          continue;
        }
	if (c=='[')
	{
	  s++;
          p=es=realloc(es,(ES_num+1)*sizeof(ES));
          p+=ES_num;
	  p->ext=s;
	  p->elf=uni_elf;
	  p->altelf=uni_altelf;
	  p->small_png=uni_small;
	  p->large_png=uni_large;
          p->zero_small=0;
          p->zero_large=0;
	  ES_num++;
	  while((c=*s)!=']')
	  {
	    if (c<32) goto LERROR; //Найден символ с кодом меньше 32 в расширении
	    s++;
	  }
          *s++=0; s=find_eol(s); continue;
	}
	if (!strncmp(s,"RUN=",4))
	{
	  s+=4;
	  if (p)
	  {
	    p->elf=s;
	  }
	  else
	  {
	    uni_elf=s;
	  }
          s=find_eol(s); if (*s) {*s++=0; continue;} else break;
	}
	if (!strncmp(s,"SMALL=",6))
	{
	  s+=6;
	  if (p)
	  {
	    p->small_png=s;
	  }
	  else
	  {
	    uni_small=s;
	  }
          s=find_eol(s); if (*s) {*s++=0; continue;} else break;
	}
	if (!strncmp(s,"BIG=",4))
	{
	  s+=4;
	  if (p)
	  {
	    p->large_png=s;
	  }
	  else
	  {
	    uni_large=s;
	  }
          s=find_eol(s); if (*s) {*s++=0; continue;} else break;
	}
	if (!strncmp(s,"ALTRUN=",7))
	{
	  s+=7;
	  if (p)
	  {
	    p->altelf=s;
	  }
	  else
	  {
	    uni_altelf=s;
	  }
          s=find_eol(s); if (*s) {*s++=0; continue;} else break;
	}
      LERROR:
	ShowMSG(1,(int)"ExtD: Parse error!");	
	break;
      }
      i=0;
      p=es;

      REGEXPLEXT* newreg=malloc(sizeof(REGEXPLEXT)); // Регать теперь будем это
      xws=AllocWS(256);

      while(i<ES_num)
      {
	//Убираем уже зарегистрированное расширение
	int id;
	str_2ws(xws,p->ext,255);
	id=GetExtUid_ws(xws);
	if (id)
	{
	  TREGEXPLEXT *pr=get_regextpnt_by_uid(id);
	  if (p)
	  {
#ifdef NEWSGOLD
            memcpy(newreg,pr,sizeof(TREGEXPLEXT));
#else
            newreg->ext=p->ext;
            newreg->unical_id=id;
            newreg->enabled_options=pr->enabled_options;
            newreg->obex_path_id=pr->obex_path_id;
            newreg->menu_flag=pr->menu_flag;
#endif
	    UnRegExplorerExt(newreg);
            // Если в exstension.cfg есть данные - пишем, иначе не трогаем
#ifdef NEWSGOLD
            if(p->small_png != uni_small) newreg->icon1=(int *)&(p->small_png);
            if(p->large_png != uni_large) newreg->icon2=(int *)&(p->large_png);
            if(p->elf != uni_elf) newreg->proc = (void *)do_ext;
	    if(p->altelf != uni_altelf) newreg->altproc = (void *)do_alternate;
#else
            newreg->icon1 = (p->small_png != uni_small) ? (int *)&(p->small_png) : (int*)pr->icon1;
            newreg->icon2 = (p->large_png != uni_large) ? (int *)&(p->large_png) : (int*)pr->icon2;
            newreg->proc = (p->elf != uni_elf) ? (void *)do_ext : pr->proc;
            newreg->altproc = (p->altelf != uni_altelf) ? (void *)do_alternate : pr->altproc;
#endif
	  }
	}
        else
        {
          // Для новых типов
          memcpy(newreg,&reg,sizeof(REGEXPLEXT));
          newreg->ext=p->ext;
	  newreg->icon1=(int *)&(p->small_png);
	  newreg->icon2=(int *)&(p->large_png);
	  newreg->unical_id=0x56+i;
        }
	RegExplorerExt(newreg);
	i++;
	p++;
      }
      FreeWS(xws);
      mfree(newreg);
      
      if (ES_num>0)
      {
        reg0.icon1=(int *)&uni_small;
        reg0.icon2=(int *)&uni_large;
        RegExplorerExt(&reg0);
        //Для выгрузки
        LockSched();
        CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
        memcpy(&icsmd,icsm->constr,sizeof(icsmd));
        old_icsm_onClose=icsmd.onClose;
        icsmd.onClose=MyIDLECSM_onClose;
        icsm->constr=&icsmd;
        UnlockSched();
      }
      else
      {
        LockSched();
        ShowMSG(1,(int)"ExtD: noting to do!");
        UnlockSched();
      }
    }
    else
    {
      LockSched();
      ShowMSG(1,(int)"ExtD: out of memory!");
      UnlockSched();
    }
    fclose(f,&ul);
    if (ES_num>0) return 0;
  }
  else
  {
    LockSched();
    ShowMSG(1,(int)"ExtD: can't open extension.cfg!");
    UnlockSched();
  }
  mfree(CFG);
  mfree(es);
  SUBPROC((void *)Killer);
  return 0;
}
