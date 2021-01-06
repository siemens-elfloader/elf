#include "math.h"
#include "..\swilib.h"
#define NEWSGOLD //всегда

//char *Title="calc 0.5 (c)ugin";
const char *errors[]={0};
extern unsigned char C65;
int act=0;
char *znprew=" ", *zn=" ";
const int MAX = 100000000, MAXN = 9;
int long_press = 0;
double pi = 3.141592653589793238462643;
int op_count = 0;
int cngf = 0;

//0:  1/x | sin cos tan | x^2 log log10 | sqrt exp 10^x  
//1: chn asin acos atan | sinh cosh tanh | x^3 pi !

// ceil floor fabs atan2(, ) fmod(, ) all_const  ( )

char *op[] = {
  "1/x",  "sin","cos","tan",       "x^2","log","lg10",       "sqrt","exp","10^x",
  "chn",  "asin", "acos", "atan",  "sinh", "cosh", "tanh",   "x^3", " pi", " ! "};
typedef struct
{
  double cc;
  int drb_flag;
  int len_d;
  int len_cc;
  int exp_cc;
  int exp_flag;
  int lock;
} Real;
Real res, resprew, cc, prew;


void oncreate() {}
void onexit() {}
void onclose() {}

int onstart(char *exename, char *fname){
  return 0;  
}

void onredraw() // OnRedraw
{
  DrawRoundedFrame(0,0,(C65?129:131),(C65?129:175),4,4,0,
			GetPaletteAdrByColorIndex(0),
			GetPaletteAdrByColorIndex(20));  
  DrawRoundedFrame(3,3,(C65?126:128),47,4,4,0,
			GetPaletteAdrByColorIndex(0),
			GetPaletteAdrByColorIndex(0));

  WSHDR *ws = AllocWS(256); 
  wsprintf(ws, "del       *       exp");
  DrawString(ws,3, 50,128, 64,SMALL_FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(20));
  wsprintf(ws, "-  =  +");
  DrawString(ws,44, 60,84, 74,SMALL_FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(20));
  wsprintf(ws, " .        /        - ");
  DrawString(ws,3, 71,128, 85,SMALL_FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(20));

  wsprintf(ws, "%s      %s      %s", op[1 + op_count], op[2 + op_count], op[3 + op_count]);
  DrawString(ws,3, 90,128,104,SMALL_FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(20));
  wsprintf(ws, "%s      %s      %s", op[4 + op_count], op[5 + op_count], op[6 + op_count]);
  DrawString(ws,3,110,128,124,SMALL_FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(20));
  wsprintf(ws, "%s      %s      %s", op[7 + op_count], op[8 + op_count], op[9 + op_count]);
  DrawString(ws,3,130,128,144,SMALL_FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(20));

  wsprintf(ws, "pow      %s      #  ", op[0 + op_count]);
  DrawString(ws,3,150,128,164,SMALL_FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(20));
  FreeWS(ws);
}

void printzn(char *oldd, char *newd)
{
  int tpx = 1, tpy = 17, tpx1 = 34, tpy1 = 149;
  WSHDR *ws = AllocWS(256); 
//  wsprintf(ws, "%s\r\n",oldd);
  wsprintf(ws, "     ");
  DrawString(ws,tpx,tpy,tpx1,tpy1,SMALL_FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(0));
  wsprintf(ws, "%s\r\n",newd);
  DrawString(ws,tpx,tpy,tpx1,tpy1,SMALL_FONT,2,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(0));
  FreeWS(ws); 
}

void printfloat(int tpx, int tpy, int tpx1, int tpy1, Real newd)
{
  WSHDR *ws = AllocWS(150);
  char *s0 = malloc(150);

  wsprintf(ws, "                          ");    
  DrawString(ws,tpx,tpy,tpx1,tpy1,MIDDLE_FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(0));

  if (newd.exp_flag && tpy == 29)
  {
    char *t1 = malloc(30); char *t2 = malloc(30);
    strcpy(t1, "%.");
    sprintf(t2, "%de", newd.len_cc - 1);
    strcat(t1, t2);
    sprintf(s0, t1, newd.cc);
    mfree(t1); mfree(t2); 
  }
  else if (newd.drb_flag && tpy == 29 && ((long)newd.len_cc - newd.len_cc) == 0) 
  {
    char *t1 = malloc(30); char *t2 = malloc(30);
    strcpy(t1, "%#.");
    sprintf(t2, "%dg", newd.len_cc);
    strcat(t1, t2);
    sprintf(s0, t1, newd.cc);
    mfree(t1); mfree(t2); 
  }
  else sprintf(s0, "%.9g", newd.cc);
  str_2ws(ws, s0, 128);   
  DrawString(ws,tpx,tpy,tpx1,tpy1,MIDDLE_FONT,2,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(0));

  FreeWS(ws); 
  mfree(s0);
}
int fact(int n)
{
  int r = 1;
  for(int i = 2; i <= n; i++)
    r *= i;
  return r;
}

void result(int action)
{
   printzn(znprew,zn);
   resprew = res;
   switch(action)
    {  
    case 0:
      res = cc;
      break;
    case 1:  // +
      res.cc = res.cc + cc.cc;
      break;
    case 2: // -
      res.cc = res.cc - cc.cc;
      break;
    case 3: // *
      res.cc = res.cc * cc.cc;
      break;
    case 4:  // /
      res.cc = res.cc / cc.cc;
      break;
    case 5: // power
      res.cc = pow(res.cc, cc.cc);
      break;
//0:  1/x | sin cos tan | x^2 log log10 | sqrt exp 10^x  
    case 6:
      res.cc = 1 / cc.cc;
      break;
    case 7:
      res.cc = sin(cc.cc * pi / 180);
      if (res.cc < 1e-15) res.cc = 0;
      break;
    case 8:
      res.cc = cos(cc.cc * pi / 180);
      if (res.cc < 1e-15) res.cc = 0;
      break;
    case 9:
      if (fabs(cc.cc * pi / 180)  != 90) res.cc = tan(cc.cc * pi / 180);
      if (res.cc < 1e-15) res.cc = 0;
      break;
    case 10:
      res.cc = cc.cc * cc.cc;
      break;
    case 11:
      res.cc = log(cc.cc);
      break;
    case 12:
      res.cc = log10(cc.cc);
      break;
    case 13:
      res.cc = sqrt(cc.cc);
      break;
    case 14:
      res.cc = exp(cc.cc);
      break;
    case 15:
      res.cc = pow(10, cc.cc);
      break;
//1: chn asin acos atan | sinh cosh tanh | x^3 pi !      
    case 16:
      {
        Real tmp = cc;
        cc = res;
        res = tmp;
        printfloat(3, 45-16, 128, 165-16, cc);
        cngf = 1;
      }
      break;
    case 17:
      res.cc = asin(cc.cc) * 180 / pi;
      break;
    case 18:
      res.cc = acos(cc.cc) * 180 / pi;
      break;
    case 19:
      res.cc = atan(cc.cc) * 180 / pi;
      break;
    case 20:
      res.cc = sinh(cc.cc);
      break;
    case 21:
      res.cc = cosh(cc.cc);
      break;
    case 22:
      res.cc = tanh(cc.cc);
      break;
    case 23:
      res.cc = pow(cc.cc, 3);
      break;
    case 24:
      cc.cc = pi;
      printfloat(3, 45-16, 128, 165-16, cc);
      cngf = 1;
      break;
    case 25:
      res.cc = fact((int)cc.cc);
      break;      
    }
   if ((long)res.cc == res.cc) res.drb_flag = 0; else res.drb_flag = 1;
   if(cc.cc == 0)
     res = resprew;
   printfloat(3, 25-16, 128, 165-16, res);
//   cc = drb_flag = len_d = len_cc = exp_cc = 0;
   if (!cngf) cc.cc = cc.drb_flag = cc.len_d = cc.len_cc = cc.exp_cc = cc.exp_flag = cngf = 0;
   cngf = 0;
}

int onkey(unsigned char keycode, int pressed){
  if (long_press == 2)
    long_press = 0;
  else if (pressed == KEY_UP  && long_press != 1)
  {
    if((keycode >= 48) && (keycode <= 57) && (cc.len_cc < 9) && (pressed != LONG_PRESS))
    {
      int zncc = 1;//cc.cc / fabs(cc.cc);
      if (cc.cc < 0) zncc = -1;
      if (cc.drb_flag && !cc.exp_flag)
      {
        cc.len_d++;
        cc.len_cc++;
        cc.cc = cc.cc + zncc * (keycode - 48) / pow(10, cc.len_d);
      }    
      else if (!cc.exp_flag)
      {
        cc.cc = cc.cc * 10 + zncc * (keycode - 48);
        cc.len_cc++;        
      }
      else if (cc.exp_flag)
      {
        cc.cc = fabs(cc.cc);
        int zn_exp = log10(cc.cc) / fabs(log10(cc.cc));
//        if (fabs(cc.cc) < 1) zn_exp = -1;
        cc.exp_cc = fabs(cc.exp_cc);
        cc.cc /= pow(10, (int)log10(cc.cc));
        cc.exp_cc = cc.exp_cc * 10 + (keycode - 48);
        cc.exp_cc -= (int)(cc.exp_cc / 100) * 100;
        cc.exp_cc *= zn_exp;
        cc.cc *= pow(10, (zn_exp<0?cc.exp_cc+1:cc.exp_cc)) * zncc; //???
      }
    }
    else 
    switch(keycode)
    {
    case RIGHT_SOFT: //exp
      if (cc.cc) cc.exp_flag = (cc.exp_flag + 1) % 2;
      break;
    case LEFT_SOFT: //del
      if (!cc.exp_flag)
      {
        if (!cc.cc || ((long)cc.cc == cc.cc && cc.len_d == 0))
        {
          cc.drb_flag = 0;
          cc.len_d = 0;
        }
        if (cc.drb_flag)
        {
          cc.cc = (long)(cc.cc * pow(10, cc.len_d - 1)) / pow(10, cc.len_d - 1);
          cc.len_d--;
        }
        else
          cc.cc = (long)(cc.cc / 10);
        if (!cc.cc) cc.len_cc = 0;
        if (cc.len_cc) cc.len_cc--;
      }
      break;
    case RED_BUTTON:
      if (cc.exp_flag)
      {
        int zn_cc = cc.cc / fabs(cc.cc);
        cc.cc = fabs(cc.cc);
        if (cc.cc/pow(10, (int)log10(cc.cc)) == 1) //?
          cc.cc /= pow(10,(int)log10(cc.cc)*2) * zn_cc;
        else
          cc.cc /= pow(10,(int)log10((fabs(cc.cc)<1?cc.cc/10:cc.cc))*2) * zn_cc;
      }
      else
        if (cc.cc) cc.cc = -cc.cc;
      break;      
    case GREEN_BUTTON:
      cc.drb_flag = 1;
      break;
    case RIGHT_BUTTON:
      result(act);
      act=1;
      znprew=zn;
      zn="+";
      printzn(znprew,zn);
      cc.drb_flag = 0;
      break;
    case LEFT_BUTTON:
      result(act);
      act=2;
      znprew=zn;
      zn="-";
      printzn(znprew,zn);
      cc.drb_flag = 0;
      break;        
    case UP_BUTTON:
      result(act);
      act=3;
      znprew=zn;
      zn="*";
      printzn(znprew,zn);
      cc.drb_flag = 0;
      break;    
    case DOWN_BUTTON:
      result(act);
      act=4;
      znprew=zn;
      zn="/";
      printzn(znprew,zn);
      cc.drb_flag = 0;
      break;
    case '*':
      result(act);
      act=5;
      znprew=zn;
      zn="^";
      printzn(znprew,zn);
      cc.drb_flag = 0;
      break;
    case '#':
      op_count = (op_count + 10) % 20;
      onredraw();
      if (res.cc) printfloat(3, 25-16, 128, 165-16, res);
//      printfloat(3, 45-16, 128, 165-16, cc);
      printzn(znprew,zn);
      break;
    case ENTER_BUTTON:  
      result(act);
      act=0;
      zn="=";
      printzn(znprew,zn); 
      cc.drb_flag = 0;
      break;
    }
  }
  else if (pressed == LONG_PRESS)
  {
    long_press = 2;
    if(keycode >= 48 && keycode <= 57)
    {
      result(keycode - 48 + 6 + op_count);
      act=0;
      znprew=zn;
      zn=op[keycode - 48 + op_count];    
      printzn(znprew,zn);
      cc.drb_flag = 0;
    }
    else 
    switch(keycode)
    {
    case LEFT_SOFT: //del
      cc.cc = cc.drb_flag = cc.len_d = cc.len_cc = cc.exp_cc = cc.exp_flag = 0;
      break;
    case RIGHT_SOFT: //exit
      return(1);
    }
  }
printfloat(3, 45-16, 128, 165-16, cc);
prew = cc;
return(0);  
}
