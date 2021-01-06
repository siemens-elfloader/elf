//------------------------------------------------------------------------------
void debugWrite(char* stringg, char* file, int len)
{
 int ff; 
 char s[2];
 unsigned int err;
 if(fopen(file, A_ReadOnly, 0, &err) != -1)
 {
   ff = fopen(file,A_ReadWrite + A_Append + A_BIN, P_READ + P_WRITE, & err);
   lseek(ff,0,S_END,&err,&err);
 }
 else
 {
   ff = fopen(file,A_ReadWrite + A_BIN + A_Create + A_Truncate, P_READ + P_WRITE, & err);
 }
 fwrite(ff, stringg, len, &err);
 s[0] = 0x0D; s[1] = 0x0A;
 fwrite(ff, s, 2, &err);
 fclose(ff, &err);
}
//------------------------------------------------------------------------------

