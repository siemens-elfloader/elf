//достаточно просто :-)
int FindSubWord(char *A, char *B)
{
int len,i;
i= 0;
len=strlen(B);
while(A[i]!=0)
{
if(A[i]==B[0])
   if(!memcmp(&A[i],&B[0],len))return(i);
i++;
}
return(-1);
}