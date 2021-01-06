/************************ 
*���� ����:      * 
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
    while (i<size)         //���� �� ����� ����� 
    { 
    strcpy(str,""); 
    j=0; 
    while (((*(mem+i)!='\r'))&&(i<size)) {*(str+j)=*(mem+i); j++;i++;}    //������ ������ �� ����� 
    //������������ ���� ������� 
    if (*str=='[')         //���� �������� ������ 
      { 
   NumOfGroups++;  //� ��� ����� 
      } 
    else 
      {    
       Items[NumOfItems].RunType=*str;      //��� ���������(������ ������) 
       j=2;    //���������� ������ ��� ������� 
       int k=0; 
       while (*(str+j)!='|') {Items[NumOfItems].Command[k++]=*(str+j); j++;}      
       j++;  //����������  '|' 
       k=0; 
       while (*(str+j)!='|') {Items[NumOfItems].Name[k++]=*(str+j); j++;}    //�������� 
       j++;    //����������  '|' 
       NumOfItems++; 
     } 
    i+=2; 
    } 
  } 
  mfree(mem); 
mfree(str); 
  fclose( plhandle, & err ); 
}