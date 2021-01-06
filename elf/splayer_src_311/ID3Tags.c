#include "../inc/swilib.h"
#include "main.h"
#include "langpack.h"
// Респект Ganster'у за предоставленный код!
// Структура тегов ID3v1

//ID3TAGDATA *MainTag; // Структура, под которую нужно выделить память, типа MainTag=malloc(sizeof(ID3TAGDATA)); По окончанию работы не забываем память освобождать

/*******************************************************************************
  Чтение ID3v1.
Вход: путь к мр3 - файлу; структура, в которую теги читаем
Выход: флаг присутствия тегов в файле
*******************************************************************************/
int ReadID3v1(WSHDR* fnamews, ID3TAGDATA *tag) // Чтение ID3 v1
{
  char* fname=malloc(256);
  ws_2str(fnamews,fname,256);
 // ws_2str(fnamews,tag->full_name,256);
  unsigned int err;
  int f;
  FSTATS stat;
  zeromem(tag, sizeof(ID3TAGDATA)); // Очищаем память
  f=fopen(fname, A_ReadOnly+A_BIN, P_READ, &err); // Открываем файл для чтения
  GetFileStats(fname, &stat, &err); // Берем размер файла
  lseek(f,(stat.size-128), 0, &err, &err); // Смещаемся на 128 байт с конца
  fread( f, tag->istagg, 3, &err ); // Читаем слово "TAG"
  if((tag->istagg[0]=='T')&&(tag->istagg[1]=='A')&&(tag->istagg[2]=='G'))// Если там действительно написано "TAG",
  {
    tag->present=1; // Значит тег в треке есть
    char *tagtext=malloc(125); // Выделяем память под тег
    fread( f,tagtext, 125, &err ); // Читаем тег в память
    memcpy(tag->title, &tagtext[0],30); // Парсим тег
    memcpy(tag->artist,&tagtext[30],30);
    memcpy(tag->album,&tagtext[60],30);
    memcpy(tag->year,&tagtext[90],4);
    // Прилепим еще это :)   AAA 
    if(tagtext[122]!=0x00)   //  !!При 0х20(пробел) почему то думает что ячейка пуста...!!
    {
      memcpy(tag->comment,&tagtext[94],30);
    }else{
      tag->version1_1=1;   // Определили версию тэгов   AAA
      memcpy(tag->comment,&tagtext[94],28);
      tag->number = tagtext[123];
    }
    tag->genre = tagtext[124];
    mfree(tagtext); // Освобождаем память
  }
  else {tag->present=0; extern const unsigned int SHOW_POPUP; if(SHOW_POPUP) ShowMSG(1,(int)lgpData[LGP_No_Tags]);} // Если проверку не прошли, значит тегов нет
  fclose(f,&err); // Закрываем файл
  mfree(fname);
  REDRAW(); // Перерисовываем экран
  return (tag->present); // Возвращаем флаг присутствия тегов
}
// ReadID3v1(0:\\Music\\1.mp3, MainTag)

/*
void GetTags(WSHDR* fpath){
  if (pcsmid){
    CSM_RAM *csmp=FindCSMbyID(pcsmid);
    if (csmp){
      WSHDR *fn=((WSHDR **)csmp)[0x2C/4];


  
      if (!fn)return;
      if (!fn->wsbody) return;
      if (fn->wsbody[0])        ;
#ifdef ELKA
        WSHDR **wws=((WSHDR ***)csmp)[(0x18C/4)]-1;
 #else
        WSHDR **wws=((WSHDR ***)csmp)[(0x170/4)]-1;
#endif
      if (wws)        {
        WSHDR *tws;
        const char unk[]="Unkhown";
        const char pr[]="%w - %w";
        if (!(tws=wws[2]));else
          if (!(tws->wsbody));else
            if (tws->wsbody[0])      
              wstrcpy(wstag,tws);
             else  wsprintf(wstag,"%t",unk);
        if (!(tws=wws[1]));else
          if (!(tws->wsbody));else
            if (tws->wsbody[0])     
              wsprintf(wstag,pr,wstag,tws);
             else
              wstrcpy(wstag,fn);            
/// new
 
     WSHDR *folder=((WSHDR **)csmp)[0x30/4];      
  WSHDR *fp=((WSHDR **)csmp)[0x12C/4];            //fullpath may be diff on NSG
     
      char *str = malloc(wstrlen(fpath) * 2 + 1);
      ws_2str(fpath, str, wstrlen(fpath) * 2 + 1);
      WSHDR* fn=AllocWS(128);
      const char *p=strrchr(str,'\\')+1;
      str_2ws(fn,p,128);
      
      WSHDR* fn=AllocWS(128);
      short p=wstrrchr(fpath,wstrlen(fpath),'\\')+1;
      wstrncpy(fn,fpath,p);
  FILE_PROP wl;
  zeromem(&wl, sizeof(wl));
  wl.type=0x1800;
  wl.filename=fpath;
  WSHDR *w_0=AllocWS(0x200);
  WSHDR *w_1=AllocWS(0x10);
  WSHDR *w_2=AllocWS(0x10);  
  WSHDR *w_3=AllocWS(0x100);    
  wl.bitrate_ws=w_1;
  wl.audio_frequency_ws=w_2;  
  wl.duration_mp3_ws=w_3;    
  GetFileProp(&wl,fn,folder);
  if (w_3->wsbody[0]){
    wsprintf (w_0,"%w: %w",wstag,w_3);
    wstrcpy (wstag,w_0);
  }
  if (w_1->wsbody[0]){
    wsprintf (w_0,"%w %w",wstag,w_1);
    wstrcpy (wstag,w_0);
  }
  if (w_2->wsbody[0]){
    wsprintf (w_0,"%w %w",wstag,w_2);
    wstrcpy (wstag,w_0);
  }

  FreeWS(w_0);  
  FreeWS(w_1);
  FreeWS(w_2);  
  FreeWS(w_3);                 
  
         //Патчим строку на предмет win1251
        int i=1;
        int c;
        tagw=0;
        while(i<=wstag->wsbody[0])		{
          c=wstag->wsbody[i];
          if (c==0xA8) c=0x401;
          if (c==0xAA) c=0x404;
          if (c==0xAF) c=0x407;
          if (c==0xB8) c=0x451;
          if (c==0xBA) c=0x454;
          if (c==0xBF) c=0x457;
          if ((c>=0xC0)&&(c<0x100)) c+=0x350;
          wstag->wsbody[i++]=c;
          tagw+=GetSymbolWidth(c,cfnt);
        }

    
      }else;
    }
    else    pcsmid=0;
  }
  else  {
    CSM_RAM *p=((void **)CSM_root()->csm_q)[2];
    while(p)
    {
      if (p->constr==pcsmadr) break;
      p=p->next;
    }
    if (p)
      pcsmid=p->id;
  }
};*/
