Вот так в экстраинфо выводятся акссесуары: 

#pragma swi_number=0x80D0 
__swi __arm char* RamAccPoint(void); 

int* pointer = (int*)RamAccPoint()+2; 
if (*pointer != 0) 
{ 
int* device = (int*)*pointer+3; 
int* id = (int*)*pointer+2; 
if (*id != 0) 
sprintf(buf1, "%s:%s", *device, *id); 
else 
sprintf(buf1, "%s", *device); 
}