extern unsigned int STKSZ;

extern unsigned int usp; //��������� �� ������� ����
extern unsigned int dsp; //��������� �� ������ ����
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

//������� �� �������� ����� � ������ (�� ������ �����)
void move_up(void)
{
  unsigned int s=usp;
  unsigned int d=dsp;
  unsigned int c;

  char *ds=dstk;
  char *us=ustk;

  if (!s) return;
  ds[--d]=us[--s]; //��������� 0
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

//������� �� ������� ����� � ������� (�� ������ ����)
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
