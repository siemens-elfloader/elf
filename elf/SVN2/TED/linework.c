extern unsigned int STKSZ;

extern unsigned int usp; //Указатель на верхний стек
extern unsigned int dsp; //Указатель на нижний стек
extern char *dstk;
extern char *ustk;

unsigned int bl_us(unsigned int p)
{
  char *u=ustk;
  if (!p) return(p);
  do
  {
    if (!(--p)) break;
  }
  while(u[p-1]);
  return(p);
}

unsigned int bl_ds(unsigned int p)
{
  char *d=dstk;
  if (p==STKSZ) return(p);
  do
  {
    p++;
  }
  while(d[p-1]);
  return(p);
}

//Перенос из верхнего стека в нижний (на строку вверх)
void move_up(void)
{
  unsigned int s=usp;
  unsigned int d=dsp;
  unsigned int c;

  char *ds=dstk;
  char *us=ustk;

  if (!s) return;
  ds[--d]=us[--s]; //Переносим 0
  if (s>256)
  {
    while((c=us[--s])) ds[--d]=c;
    s++;
  }
  else
  {
    while(s)
    {
      if (!(c=us[s-1])) break;
      s--;
      ds[--d]=c;
    }
  }
  usp=s;
  dsp=d;
}

//Перенос из нижнего стека в верхний (на строку вниз)
void move_dw(void)
{
  unsigned int s=dsp;
  unsigned int d=usp;
  char *ds=dstk;
  char *us=ustk;

  if (s==STKSZ) return;
  while((us[d]=ds[s]))
  {
    d++;
    s++;
  }
  d++;
  s++;
  dsp=s;
  usp=d;
}
