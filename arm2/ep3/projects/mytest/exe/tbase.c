//tbase.� - ������ � ����� ���������� ��� ���������� ����������� ������
//(C)Dimadze

#include "..\..\inc\swilib.h"
#include "tbase.h"



int *trans_base = 0;
int  fiq_irq_value = 0;

void SetTBaseAddress(int *tbase)
{
 trans_base = tbase;
}

void LockOSAction()
{
 LockSched();
 fiq_irq_value = DisableINT();
}

void UnLockOSAction()
{
 EnableINT(fiq_irq_value);
 UnlockSched();
}

char GetByteFromAddress(void *addr)
{
 return *((char *)addr);
}



int ApplyPatch(void *addr, char new_byte)
{
 //�������� �� ����������� ������ ����� � �������� flash
 if (((int)addr >= 0xA0000000) && ((int)addr < 0xA4000000) && trans_base)
 {
  unsigned short element = ((int)addr>>0x14)&0xFFF;
  
  //���� ������� ������� ������� ������ �����������
  if (((trans_base[element])&0xFF) == 0x1E)
   {
    //��������� ������ � 1 �� �� ������ ������� �� 256 ������� �� 4 ��
     
    //������ ������ � ��������� ������ ������
    char *addr_section = (char *)(((int)addr)&0xFFF00000);
    int *coarse_table = (int *)malloc(0x100*4+0xFFF+4);
    
    //����������� �����
    int *coarse_table_a = (int *)(((int)coarse_table + 0xFFF)&0xFFFFF000);
    
    //��������������� ���� ��������
    for (int i = 0; i < 0x100; i++) coarse_table_a[i] = (int)addr_section + 0x1000*i + 0x0E;
    
    //��������� ������������� ����� ������� ��������� ���������
    coarse_table_a[0x100] = (int)coarse_table;
    
    //������ ������ � ��������� ������ ��������
    unsigned short subelement = ((int)addr>>0x0C)&0xFF;
    char *addr_page = (char *)((coarse_table_a[subelement])&0xFFFFF000);
    char *rampage = (char *)malloc(0x1000 + 0xFFF + 4);
    
    //����������� ����� � �������� ���� ���������� flash-��������
    char *rampage_a = (char *)(((int)rampage + 0xFFF)&0xFFFFF000);
    memcpy(rampage_a, addr_page, 0x1000);
    
    //��������� ������������� ����� ��������
    int *rampage_int = (int *)rampage_a;
    rampage_int[0x1000] = (int)rampage;
    
    //��������� ������ � �������� � ��� ������� 
    short patch_byte =  ((int)addr)&0xFFF;
    rampage_a[patch_byte] = new_byte;
    
    LockOSAction();
    
    //���������� � �����
    ExecuteIMB();
    
    //���������� � ������� ������� � ������� �������
    coarse_table_a[subelement] = (int)rampage_a + 0x0E;
    trans_base[element] = (int)coarse_table_a + 0x11;
    
    UnLockOSAction();

    return 1;
   }
    //���� ��� ������ �� ��������
    else
     {
      //��������� ������ ������� ������� ������ � ����� ������
      int *coarse_table = (int *)(((int)trans_base[element])&0xFFFFF000);
      unsigned short subelement = ((int)addr>>0x0C)&0xFF;
      char stat_page = (coarse_table[subelement]&0x0F000000)>>0x18;
      
      //���� flash �������� �� � RAM
      if ((stat_page > 0x00 && stat_page < 0x04) || stat_page == 0x00)
       {
        //������ ������ � ��������� ������ ��������
        char *addr_page = (char *)((coarse_table[subelement])&0xFFFFF000);
        char *rampage = (char *)malloc(0x1000 + 0xFFF + 4);
    
        //����������� ����� � �������� ���� ���������� flash-��������
        char *rampage_a = (char *)(((int)rampage + 0xFFF)&0xFFFFF000);
        memcpy(rampage_a, addr_page, 0x1000);
       
        //��������� ������������� ����� ��������
        int *rampage_int = (int *)rampage_a;
        rampage_int[0x1000] = (int)rampage;
    
        //��������� ������ � �������� � ��� ������� 
        short patch_byte =  ((int)addr)&0xFFF;
        rampage_a[patch_byte] = new_byte;
        
        LockOSAction();
        
        //���������� � �����
        ExecuteIMB();
        //���������� � ������� ������� ������
        coarse_table[subelement] = (int)rampage_a + 0x0E;
        
        UnLockOSAction();
        
        return 1;
       }
      
       //���� flash �������� � RAM
       else
         {
          //��������� ������ ��������
          char *rampage = (char *)((coarse_table[subelement])&0xFFFFF000);
          
          LockOSAction();
          
          //���������� � �����
          ExecuteIMB();
          
          //������������� ������� �� ������
          coarse_table[element] = coarse_table[element]|0xFF0;
          
          //��������� ������ � �������� � ��� ������� 
          short patch_byte =  ((int)addr)&0xFFF;
          rampage[patch_byte] = new_byte;
          
          //���������� ������� �� ������
          coarse_table[subelement] = (int)rampage + 0x0E;
          
          UnLockOSAction();

          return 1;
         }
      
     }
 }
  else return 0;
}

int UndoPatch(void *addr, char old_byte)
{
 
}

