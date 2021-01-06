extern unsigned long curline;

extern char *dstk;
extern char *ustk;

extern unsigned int FL_loader(int fin, unsigned int p);
extern unsigned int FL_saver(int fs, unsigned int p);

unsigned int ConvertSimple(int fin,int fs)
{
  unsigned int s;
  unsigned int sym;
  unsigned int d=0;
  unsigned int i=0;
  unsigned int eolsymb=0;

  char *ds=dstk;
  char *us=ustk;

  extern unsigned int STKSZ50;

  int maxstk=STKSZ50;

  s=FL_loader(fin,0xFFFFFFFF);
  while((sym=ds[s++]))
  {
    if (s>=maxstk) s=FL_loader(fin,s);
    switch(sym)
    {
    case 0x0D:
    case 0x0A:
      if (eolsymb==sym)
      {
	goto LEOL;
      }
      if (eolsymb) break; //Пропустили второе окончание строки
      eolsymb=sym; //Определили конец строки
    LEOL:
      curline++;
      i=0; //Начало строки
      us[d++]=0;
      break;
    case 0x01:
    case 0x09:
      sym=' '; //Пока преобразовали табуляцию в пробел
    default:
      us[d++]=sym;
      i++;
      if (i>255)
      {
	goto LEOL; //Слишком длинная строка
      }
      break;
    }
    if (d>=maxstk) d=FL_saver(fs,d);
  }
  if (i)
  {
    //Незавершенная строка
    us[d++]=0;
    curline++;
  }
  if (d>=maxstk) d=FL_saver(fs,d);
  return(d);
}





