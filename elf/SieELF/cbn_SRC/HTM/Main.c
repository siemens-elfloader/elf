
//HTML.dll конвертер для edit.elf

#include "..\swilib.h"


#define tagscnt 12
const short tags[tagscnt]={'>p','rb','1h','2h','3h','4h','5h','6h','7h',\
  'h/','it','t/'};	//Теги новых строк
const long spce=0x20200a0d;	//Заменить верхние теги на это
#define maxsize 512	// Max длина строки

// Удалить все теги <> и {} из html-файла
// Вставить пробелы и cr,lf для тегов <p><br><h?></h?><title></title>

int isem(char s){
  return (s==0xd || s==0xa || s==0x9 || s==0x20);
}

int i;

int main(char *buf, int size){
  int j=0;
  char k, *outbuf, *ib, *obb, *ob, *ok;
  ib=outbuf=ob=obb=buf;
//  prepdec2();
// Выкинуть теги  
 do{ 
  while(*ib && *ib!='<' && *ib!='<'){
    *ob++=*ib++;
    // разбить cr,lf через maxsize символов!!!
    if(*ib==0xd) j=0;
    if(++j>maxsize && *ib==' '){
      j=0; 
      *ob++=0xd; *ob++=0xa;
    }
  }
  if(!(k=*ib)) break;
  ++ib;
  if(k=='<'){
    for(i=0;i<tagscnt;i++)
      if((getshort(ib)|0x2020)==tags[i]){
        putint(ob,(long)spce);
        //*(long *)ob=(long )spce;
        ob+=sizeof(long); j=0;
        break;
      }
    k='>';
  }else k='>';
  while(*ib && *ib!=k) ib++;
  if(!*ib) break;
  ++ib;
 }while(*ib);
// Выкинуть &nbsp
  while(++obb<ob-4)
    if(getint(obb)=='psbn'){
      *(obb-1)=' ';
      putint(obb,'    ');
      *(obb+4)=' ';
    }
// Перекодировать в dos
//  decoding(t2able,outbuf,ob-outbuf);

// Второй проход - выкинуть лишние пробелы и 0xd 0xa
  obb=ok=outbuf-1;
  while(++obb<ob-5){
    if(isem(*obb) && isem(obb[1]) && isem(obb[2]) && isem(obb[3]) && isem(obb[4]));
    else *++ok=*obb;
  }
// запись
  return ok-outbuf;
}
