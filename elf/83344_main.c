#include "E:\ARM\swilib.h"
int main()
{
unsigned char*mPtr=(unsigned char*)0xA0000000; //��������� ��������� FullFlash(��������)
mPtr+=0x210; //��������� ��������� ������ �����...(�������� ��� � ������ FullFlash) 
char model[5];
char n=0;
for(;n<5;n++)
{
  if (*(mPtr+n)==0x00)
  {  
    *(model+n)='\0';
    break;// ���� ��� ����� �������
  }
  else 
    *(model+n)=*(mPtr+n); //���� ��� ���� �� ����� ;)
}
ShowMSG(1,(int)model);
  return 0;
}
