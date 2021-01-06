#include "E:\ARM\swilib.h"
int main()
{
unsigned char*mPtr=(unsigned char*)0xA0000000; //Начальный указатель FullFlash(смещение)
mPtr+=0x210; //Начальный указатель модели вроде...(задается как в слитом FullFlash) 
char model[5];
char n=0;
for(;n<5;n++)
{
  if (*(mPtr+n)==0x00)
  {  
    *(model+n)='\0';
    break;// Если все тогда выходим
  }
  else 
    *(model+n)=*(mPtr+n); //Если еще есть то пишем ;)
}
ShowMSG(1,(int)model);
  return 0;
}
