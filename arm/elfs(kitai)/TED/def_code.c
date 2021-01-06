/* ==========================================================================
    File: def_code.c 
    Compiler: Turbo C 2.0 
    Description: library for automatic identification encoding text 
              (ALT, WIN, KOI). M_def_code function for the case of a text 
              in memory function f_def_code when the text file. 
    Description algorithm: http://ivr.webzone.ru/articles/defcod_2/ 
    (c) Ivan Roshchin, Moscow, 2004. 
 ========================================================================= */

#include <stdio.h>

/* Global  */

static int len_;
static unsigned char *p_;
static FILE *f_;

/* Table combinations */

static unsigned char table_2s[128]={0xFF,0xFF,0xFF,0xC7,0xFE,0xBE,0xF7,0xFB,
 0xFD,0xBF,0xF7,0xF9,0xFC,0xBE,0xF1,0x80,0xFF,0xFF,0xF7,0xBB,0xFF,0xFF,0xFF,
 0xCF,0xDE,0xBF,0xD1,0x08,0xFF,0xBF,0xF1,0xBF,0xFF,0xFF,0xFF,0xC7,0x1D,0x3F,
 0x7F,0x81,0xA7,0xB6,0xF2,0x82,0xFF,0xFF,0x75,0xDB,0xFC,0xBF,0xD7,0x9D,0xFF,
 0xAE,0xFB,0xDF,0xFF,0xFF,0xFF,0xC7,0x84,0xB7,0xF3,0x9F,0xFF,0xFF,0xFF,0xDB,
 0xFF,0xBF,0xFF,0xFF,0xFD,0xBF,0xFF,0xFF,0xFF,0xFF,0xE7,0xC7,0x84,0x9E,0xF0,
 0x12,0xBC,0xBF,0xF0,0x84,0xA4,0xBA,0x10,0x10,0xA4,0xBE,0xB8,0x88,0xAC,0xBF,
 0xF7,0x0A,0x84,0x86,0x90,0x08,0x04,0x00,0x00,0x03,0x7F,0xFD,0xF7,0xC1,0x7D,
 0xAE,0x6F,0xCB,0x15,0x3D,0xFC,0x00,0x7F,0x7D,0xE7,0xC2,0x7F,0xFD,0xF7,0xC3};

/* =========================================================================
   Alt2num support functions. 
    Admission: a Russian-code letters in the encoding ALT. 
    Withdrawal: number of the letters (0-31). 
 ========================================================================= */

static int alt2num (int a)
{
 if (a>=0xE0) a-=0x30;
 return (a&31);
}

/* =========================================================================
     Koi2num support functions. 
    Admission: a Russian-code letters in the encoding KOI. 
    Withdrawal: number of the letters (0-31). 
 ========================================================================= */

static int koi2num (int a)
{
 static unsigned char t[32]={30,0,1,22,4,5,20,3,21,8,9,10,11,12,13,14,15,31,
  16,17,18,19,6,2,28,27,7,24,29,25,23,26};

 return (t[a&31]);
}

/* =========================================================================
    Auxiliary functions work_2s-processing combine the two. 
    Admission: c1-number first letter (0-31) 
           c2-number second letter (0-31) 
           I must check-out, I found the combination of earlier 
                   (1 yes, 0 no) 
           buf-addressed array of information encountered together. 
    Withdrawal: 0-specified combination has been met before, 
           1-mix not met before and is a valid, 
           2-combination not met before and is unacceptable. 
 ========================================================================= */

static int work_2s (int c1, int c2, int check, unsigned char buf[128])
{
 int i=(c1<<2)+(c2>>3); /* Number of bytes in the array. */
 int mask=0x80>>(c2&7); /* mask, the number of bits in bytes.*/

 /* If you check = 1, check: if the bit is 0 array buf, 
     thus, this combination has already met earlier. Then go out 
     functions returning 0. If the combination is not met, then mark that 
     it met (obnulyaem a bit array buf). */

 if (check==1)
 {
  if ((buf[i]&mask)==0) return (0);
  buf[i]&=~mask;
 }

 /* Checking, acceptable combination or not. */

 if ((table_2s[i]&mask)!=0) return (1); /* Acceptable. */
 return (2);                            /* unacceptable.*/
}

/* =========================================================================
  Auxiliary functions def_code-definition encoding text. Functions 
    m_def_code f_def_code and only add to this feature. 
    Admission: get_char-pointer to a function that should be called for 
                      another symbol of the text. The function should return or 
                      code symbol, or, when you reach the end of the text, -1. 
           n is the number of different combinations of Russian letters (1-255), which 
               enough for encoding. 
    Withdrawal: 0-text encoding ALT-1 WIN, 2-KOI. 
 ========================================================================= */

static int def_code (int (*get_char)(), int n)
{
 /* The array buf_1 stores information about what combination of letters battle 
     have met in alternative ALT, and the array buf_2-in option WIN.*/

 unsigned char buf_1 [128];
 unsigned char buf_2 [128];

 int bad_1=0;
 int bad_2=0;
 int bad_3=0;
 int all_1=0;
 int all_3=0;  /* all_2=all_3 */

 int c1; int c2=0; /* Characters treated this combination. */
 int i;

 /* Initialization buf_1 and buf_2. */

 for (i=0;i<128;i++) buf_1[i]=0xFF;
 for (i=0;i<128;i++) buf_2[i]=0xFF;

 /* main loop-handling combinations for each of the three options. Cycle 
     running until the earlier text, or in any of the options 
     meet n combinations. */

 while (((c1=c2,c2=(*get_char)())!=-1)&&(all_1<n)&&(all_3<n))
 {
  /* Option ALT. First check whether the current mix of characters 
      codes Russians letters in the encoding ALT. */

  if ((((c1>=0x80)&&(c1<0xB0))||((c1>=0xE0)&&(c1<0xF0)))&&
      (((c2>=0x80)&&(c2<0xB0))||((c2>=0xE0)&&(c2<0xF0))))
  {
   switch (work_2s(alt2num(c1),alt2num(c2),1,buf_1)) /* Obrabotali. */
   {
    case 2: bad_1++;
    case 1: all_1++;
   }
  }
  /* Options WIN and KOI. First check whether the current characters 
      combining codes Russians letters in the code (in both encoding 
      ranges codes Russians letters match). */

  if ((c1&c2)>=0xC0) /*Ekvivalentno conditions (c1> = 0xC0) & & (c2> = 0xC0).  */
  {
   switch (work_2s(c1&31,c2&31,1,buf_2)) /* Obrabotali. */
   {
    case 0: continue; /* If the combination of letters already found in version WIN, 
                          it has already met with option KOI, so 
                          ignore processing option and turn KOI 
                          the next major iteration cycle. */
    case 2: bad_2++;
   }

  /* If the combination of letters had not yet met to form WIN, it certainly 
      not found in version KOI, so it is not specifically check 
      must mean, as work_2s causing property check equal to 0. */

   switch (work_2s(koi2num(c1),koi2num(c2),0,NULL)) /* Obrabotali. */
   {
    case 2: bad_3++;
    case 1: all_3++;
   }
  }
 }

 /* Data collected. Now, if any of the options unacceptable 
     the combination of no more than 1 / 32 of the total number, then think that they are not 
     it was.. */

 if (bad_1<=(all_1>>5)) bad_1=0;
 if (bad_2<=(all_3>>5)) bad_2=0;
 if (bad_3<=(all_3>>5)) bad_3=0;

 /* Obtain result. */

 {
  unsigned int a=((255-bad_1)<<8)+all_1;
  unsigned int b=((255-bad_2)<<8)+all_3;
  unsigned int c=((255-bad_3)<<8)+all_3;

  if ((a>=b)&&(a>=c)) return (0);
  if (b>=c) return (1); else return (2);
 }
}

/* =========================================================================
   Auxiliary functions m_get_char function is called from def_code when 
    one result of m_def_code. 
    Withdrawal: regular text character or -1 if it ended. 
 ========================================================================= */

static int m_get_char()
{
 if (len_==0) return (-1);
 len_--;
 return (*(p_++));
}

/* =========================================================================
Feature m_def_code-definition encoding text is remembered. 
    Admission: p-address text 
           len-length text, 
           n is the number of different combinations of Russian letters (1-255), which 
               enough for encoding. 
    Withdrawal: 0-text encoding ALT-1 WIN, 2-KOI.
 ========================================================================= */

int m_def_code (unsigned char *p, int len, int n)
{
 /* values Prisvaivaem global variables len_ and p_ that will be 
     available from m_get_char functions. */
 len_=len;
 p_=p;
 /* Obtain result. */
 return (def_code(&m_get_char,n));
}

/* =========================================================================
  Auxiliary functions f_get_char function is called from def_code when 
    one result of f_def_code. 
    Withdrawal: regular text character or -1 if it ended. 
 ========================================================================= */

static int f_get_char()
{
 int a=fgetc(f_);
 if (a==EOF) return (-1);
 return (a);
}

/* =========================================================================
    Feature f_def_code-definition encoding text, located in the file. 
    Admission: f-pointer to the structure associated with the file (the current directory 
               entries in the file to indicate the beginning of the file) 
           n is the number of different combinations of Russian letters (1-255), which 
               enough for encoding. 
    Withdrawal: 0-text encoding ALT-1 WIN, 2-KOI. 
 ========================================================================= */

int f_def_code (FILE *f, int n)
{
 /* Prisvaivaem important global variable states, which will be available 
     f_get_char of functions. */
 f_=f;
 /* Obtain result.  */
 return (def_code(&f_get_char,n));
}
