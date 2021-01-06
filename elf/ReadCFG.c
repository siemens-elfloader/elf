/************************ 
*файл вида:      * 
*[1]         * 
*F|aaaaa|bbbbbb      * 
*S|ccccccc|dddd   ddddd   * 
*         * 
************************/ 



void LoadParams() 
{ 
  unsigned int err; 
  int plhandle; 
  char *mem; 
  int size; 
  int i,j=0; 
  char *str; 
  char tmp[10]=""; 
  plhandle = fopen( "0:\\Menu.cfg", A_ReadOnly + A_BIN, P_READ, & err ); 
 if ( plhandle==-1 ) 
  { 
    fclose( plhandle, & err ); 
    return; 
  } 
  mem=malloc(10000); 
  str=malloc(256); 
if ((mem!=0)&&(str!=0)) 
  { 
    size=fread(plhandle,mem,9999,&err); 
    i=0; 
    while (i<size)         //пока не конец файлј 
    { 
    strcpy(str,""); 
    j=0; 
    while (((*(mem+i)!='\r'))&&(i<size)) {*(str+j)=*(mem+i); j++;i++;}    //читаем строку из файла 
    //обрабатываем енту строчку 
    if (*str=='[')         //если название группы 
      { 
   NumOfGroups++;  //и все такое 
      } 
    else 
      {    
       Items[NumOfItems].RunType=*str;      //что запускаем(первый символ) 
       j=2;    //пропускаем первые два символа 
       int k=0; 
       while (*(str+j)!='|') {Items[NumOfItems].Command[k++]=*(str+j); j++;}      
       j++;  //пропускаем  '|' 
       k=0; 
       while (*(str+j)!='|') {Items[NumOfItems].Name[k++]=*(str+j); j++;}    //названи€ 
       j++;    //пропускаем  '|' 
       NumOfItems++; 
     } 
    i+=2; 
    } 
  } 
  mfree(mem); 
mfree(str); 
  fclose( plhandle, & err ); 
}