// Закладки
const char *bm_name_idle(int bm)
{
  switch(bm)
  {
    case 0: return BM1NAME;
    case 1: return BM2NAME;
    case 2: return BM3NAME;
    case 3: return BM4NAME;
    case 4: return BM5NAME;
    case 5: return BM6NAME;
    case 6: return BM7NAME;
    case 7: return BM8NAME;
    case 8: return BM9NAME;
    case 9: return BM10NAME;
    case 10: return BM11NAME;
    case 11: return BM12NAME;
    case 12: return BM13NAME;
    case 13: return BM14NAME;
    case 14: return BM15NAME;
  }
  return(0);
}

const char *bm_pic_idle(int bm)
{
  switch(bm)
  {
  case 0: return BM1PIC_ID;
  case 1: return BM2PIC_ID;
  case 2: return BM3PIC_ID;
  case 3: return BM4PIC_ID;
  case 4: return BM5PIC_ID;
  case 5: return BM6PIC_ID;
  case 6: return BM7PIC_ID;
  case 7: return BM8PIC_ID;
  case 8: return BM9PIC_ID;
  case 9: return BM10PIC_ID;
  case 10: return BM11PIC_ID;
  case 11: return BM12PIC_ID;
  case 12: return BM13PIC_ID;
  case 13: return BM14PIC_ID;
  case 14: return BM15PIC_ID;
  }
  return(0);
}

const char *bm_file_idle(int bm)
{
  switch(bm)
  {
  case 0: return BM1FILE_ID;
  case 1: return BM2FILE_ID;
  case 2: return BM3FILE_ID;
  case 3: return BM4FILE_ID;
  case 4: return BM5FILE_ID;
  case 5: return BM6FILE_ID;
  case 6: return BM7FILE_ID;
  case 7: return BM8FILE_ID;
  case 8: return BM9FILE_ID;
  case 9: return BM10FILE_ID;
  case 10: return BM11FILE_ID;
  case 11: return BM12FILE_ID;
  case 12: return BM13FILE_ID;
  case 13: return BM14FILE_ID;
  case 14: return BM15FILE_ID;
  }
  return(0);
}

const char *bm_pic_fr(int bm)
{
  switch(bm)
  {
  case 0: return BM1PIC_FR;
  case 1: return BM2PIC_FR;
  case 2: return BM3PIC_FR;
  case 3: return BM4PIC_FR;
  case 4: return BM5PIC_FR;
  case 5: return BM6PIC_FR;
  case 6: return BM7PIC_FR;
  case 7: return BM8PIC_FR;
  case 8: return BM9PIC_FR;
  case 9: return BM10PIC_FR;
  case 10: return BM11PIC_FR;
  case 11: return BM12PIC_FR;
  case 12: return BM13PIC_FR;
  case 13: return BM14PIC_FR;
  case 14: return BM15PIC_FR;
  }
  return(0);
}

const char *bm_file_fr(int bm)
{
  switch(bm)
  {
  case 0: return BM1FILE_FR;
  case 1: return BM2FILE_FR;
  case 2: return BM3FILE_FR;
  case 3: return BM4FILE_FR;
  case 4: return BM5FILE_FR;
  case 5: return BM6FILE_FR;
  case 6: return BM7FILE_FR;
  case 7: return BM8FILE_FR;
  case 8: return BM9FILE_FR;
  case 9: return BM10FILE_FR;
  case 10: return BM11FILE_FR;
  case 11: return BM12FILE_FR;
  case 12: return BM13FILE_FR;
  case 13: return BM14FILE_FR;
  case 14: return BM15FILE_FR;
  }
  return(0);
}

int RunAction(int bm, int mode)//bm-номер закладки, mode-тип (0-FastRun, 1-IDLE)
{
 const char *s;
 if (mode==0)
  s=bm_file_fr(bm);
 if (mode==1)
  s=bm_file_idle(bm);
 if((s)&&strlen(s))
 {
  if ((s[2]=='\\')&&((s[(strlen(s))-3]=='.')||//Проверяем строку на наличие символов '\\' и '.'
     (s[(strlen(s))-4]=='.')||(s[(strlen(s))-5]=='.')))
     /* Если в строке есть символы '\\' и '.', то запускаем как обычный файл*/
      {
        WSHDR *ws;
        ws=AllocWS(150);
        str_2ws(ws,s,128);
        ExecuteFile(ws,0,0);
        FreeWS(ws);
        return(1);
      }
  if ((s[2]!='\\')&&(s[(strlen(s))-3]!='.')&&
     (s[(strlen(s))-4]!='.')&&(s[(strlen(s))-5]!='.')&&
     (s[0]!='a')&&(s[0]!='A')&&(s[1]!='0'))
    /* Если в строке нет символов '\\' и '.' и первые два символа не А0,
       то запускаем шорткат */
      {
        /*typedef void (*voidfunc)(); 
        voidfunc pp=(voidfunc)GetFunctionPointer((char*)s); 
        if(pp!=0) SUBPROC((void*)pp);*/
        unsigned int* addr = (unsigned int*)GetFunctionPointer((char*)s); 
        if (addr)
        {
          typedef void (*voidfunc)(); 
          #ifdef NEWSGOLD 
            voidfunc pp=(voidfunc)*(addr+4);
          #else 
            voidfunc pp=(voidfunc)addr; 
          #endif 
            SUBPROC((void*)pp);
        }
      }
  if ((s[2]!='\\')&&(s[(strlen(s))-3]!='.')&&
     (s[(strlen(s))-4]!='.')&&(s[(strlen(s))-5]!='.')&&
     ((s[0]=='a')||(s[0]=='A'))&&(s[1]=='0'))
    /* Если в строке нет символов '\\' и '.' и первые два символа А0,
       то запускаем энтрипоинт */
      {
        int entry;
        sscanf(s,"%08X",&entry);
        SUBPROC((void*)entry);
      }
 }
 return(0);
}

