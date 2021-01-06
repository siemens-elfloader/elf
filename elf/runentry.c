int strh2int(char* str) 
{ 
int n,c=0; 
while(*str!='\0') 
{ 
if(*str='a') n=*str-('A'- ('9 '+1))-('a'-'A'); 
else if(*str='A') n=*str-('A'-('9 '+1)); 
else n=*str; 
c=c*16+ (n-'0'); 
str++; 
} 
return c; 
} 
void RunEntry(char *entry) 
{ 
// char *entry="0 xA08 D9 B7D"; 
typedef int (*func)(void); 
func ff; 
ff=(func)strh2int(ent ry); 
if (ff!=NULL) SUBPROC((void *)(*ff)); 
}