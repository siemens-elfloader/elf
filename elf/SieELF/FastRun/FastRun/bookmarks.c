extern const char BM1PIC[128];
extern const char BM2PIC[128];
extern const char BM3PIC[128];
extern const char BM4PIC[128];
extern const char BM5PIC[128];
extern const char BM6PIC[128];
extern const char BM7PIC[128];
extern const char BM8PIC[128];
extern const char BM9PIC[128];
extern const char BM10PIC[128];
extern const char BM11PIC[128];
extern const char BM12PIC[128];
extern const char BM13PIC[128];
extern const char BM14PIC[128];
extern const char BM15PIC[128];
extern const char BM1FILE[128];
extern const char BM2FILE[128];
extern const char BM3FILE[128];
extern const char BM4FILE[128];
extern const char BM5FILE[128];
extern const char BM6FILE[128];
extern const char BM7FILE[128];
extern const char BM8FILE[128];
extern const char BM9FILE[128];
extern const char BM10FILE[128];
extern const char BM11FILE[128];
extern const char BM12FILE[128];
extern const char BM13FILE[128];
extern const char BM14FILE[128];
extern const char BM15FILE[128];


const char *bm_pic(int bm)
{
  switch(bm)
  {
  case 0: return BM1PIC;
  case 1: return BM2PIC;
  case 2: return BM3PIC;
  case 3: return BM4PIC;
  case 4: return BM5PIC;
  case 5: return BM6PIC;
  case 6: return BM7PIC;
  case 7: return BM8PIC;
  case 8: return BM9PIC;
  case 9: return BM10PIC;
  case 10: return BM11PIC;
  case 11: return BM12PIC;
  case 12: return BM13PIC;
  case 13: return BM14PIC;
  case 14: return BM15PIC;
  }
  return(0);
}

const char *bm_file(int bm)
{
  switch(bm)
  {
  case 0: return BM1FILE;
  case 1: return BM2FILE;
  case 2: return BM3FILE;
  case 3: return BM4FILE;
  case 4: return BM5FILE;
  case 5: return BM6FILE;
  case 6: return BM7FILE;
  case 7: return BM8FILE;
  case 8: return BM9FILE;
  case 9: return BM10FILE;
  case 10: return BM11FILE;
  case 11: return BM12FILE;
  case 12: return BM13FILE;
  case 13: return BM14FILE;
  case 14: return BM15FILE;
  }
  return(0);
}

int RunBM(int bm)
{
  const char *s=bm_file(bm);
  if (s)
  {
    if (strlen(s))
    {
      WSHDR *ws;
      ws=AllocWS(150);
      str_2ws(ws,s,128);
      ExecuteFile(ws,0,0);
      FreeWS(ws);
      return(1);
    }
  }
  return(0);
}

