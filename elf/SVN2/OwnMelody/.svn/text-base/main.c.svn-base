#include "..\inc\swilib.h"
#include <stdbool.h>

enum {COUNTRY=0x28, PHONE_OFFICE=0x2A, PHONE_FAX=0x2B, PHONE_MOBILE=0x2C, PHONE_HOME=0x2D, PHONE_FAX2=0x5E};
//---------------------------------------------------------------------------
bool GetABEntry(const char *fname, AB_UNPRES *ur) {
 int f;
 unsigned int size, tmp;
 if ((f=fopen(fname, A_ReadOnly+A_BIN, P_READ, &tmp))==-1)
  return false;

 size=lseek(f, 0, S_END, &tmp, &tmp);
 void *buf=malloc(size);
 if (buf) {
  lseek(f, 0, S_SET, &tmp, &tmp);
  fread(f, buf, size, &tmp);
 }
 fclose(f, &tmp);
 if (!buf)
  return false;
 zeromem(ur, sizeof(AB_UNPRES));
 UnpackABentry(ur, ((char *)buf+4), size-4, 0x28);
 mfree(buf);
 return true;
}
//---------------------------------------------------------------------------
#ifdef X75
int main(int flags, WSHDR *sndPath, WSHDR *sndFName, int _arg3, int CepId, int Msg, const PLAYFILE_OPT *sfo)
#else
int main(int flags, WSHDR *sndPath, WSHDR *sndFName, int CepId, int Msg, const PLAYFILE_OPT *sfo)
#endif
{
 extern char *db_fname[6];//таблица адресов БД в RAM
 char *custom_file=NULL;
 char type=*((char*)FreeRAM()+0x7C);
 AB_UNPRES ur;
 bool found=false;

 if (IsCalling() && (type>=2 && type<=11) && GetABEntry(db_fname[4], &ur)) {//Если идёт звонок и нашёлся контакт и файл
  for (int i=0; i<ur.number_of_records; i++) {//ищем "страну"
   AB_UNPRES_ITEM *r=&ur.record_list[i];
   if (r->no_data!=1 && r->data && r->item_type==COUNTRY) {//данные присутствуют, нашли "страну" ?
    unsigned tmp=wstrlen((WSHDR*)r->data)+1;
    custom_file=malloc(tmp);
    ws_2str((WSHDR*)r->data, custom_file, tmp);
    int f;
    if ((f=fopen(custom_file, A_ReadOnly+A_BIN, P_READ, &tmp))!=-1) {//Файл существует ?
     fclose(f, &tmp);
    }
    else {//файл не существует
     mfree(custom_file);
     custom_file=NULL;
    }
    break;//другой "страны" не будет. выходим из цикла
   }
  }//end for
  FreeUnpackABentry(&ur, mfree_adr());
  if (custom_file!=NULL) {//нашли номер телефона и для контакта указана своя мелодия ?
   char *p=strrchr(custom_file, '\\')+1;
   int len=strlen(p)+1;
   sndFName=AllocWS(len);
   str_2ws(sndFName, p, len);

   *p='\0';
   len=strlen(custom_file)+1;
   sndPath=AllocWS(len);
   str_2ws(sndPath, custom_file, len);

   mfree(custom_file);
   found=true;
  }
 }//IsCalling && GetABEntry ?
#ifdef X75
 int play_id=PlayFile(flags, sndPath, sndFName, _arg3, CepId, Msg, sfo);
#else
 int play_id=PlayFile(flags, sndPath, sndFName, CepId, Msg, sfo);
#endif
 if (found) {
  FreeWS(sndPath);
  FreeWS(sndFName);
 }
 return play_id;
}
