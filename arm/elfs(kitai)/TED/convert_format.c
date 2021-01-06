#include "..\inc\swilib.h"

/*void my_memset(void *dst, int v, unsigned int len)
{
  char *d=(char *)dst;
  if (len)
  {
    do
    {
      *d++=v;
    }
    while(--len);
  }
}*/
#define my_memset memset

extern unsigned long curline; //Outdoor variable counter lines 
extern unsigned int max_x; //Outdoor variable-max. the size of the line 

extern char *dstk;
extern char *ustk;

extern unsigned int FL_loader(int fin, unsigned int p);
extern unsigned int FL_saver(int fs, unsigned int p);

extern int win_dos_koi;
extern const char wintranslation[];
extern const char koi8translation[];

static const char ctype[128]=
{
  2,1,1,1,1,2,1,1, 2,3,1,1,1,1,2,1,
  1,1,1,2,1,1,1,1, 1,1,3,2,3,2,2,2,
  2,1,1,1,1,2,1,1, 2,3,1,1,1,1,2,1,
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
  1,1,1,2,1,1,1,1, 1,1,3,2,3,2,2,2,
  2,2,2,2,2,2,2,2, 0,0,0,0,0,0,0,0,
};

int GetCharType_x(int c)
{
  if (c==' ') return(4); //Space 
  if (c<32) return(5); // End of the line 
  if ((c=='i')||(c=='I')) return 2; //Glasnaya for the Ukrainian
  if (c<128) return(0); //No Russian letter
  switch(win_dos_koi)
  {
  case 1:
    //Win->Dos
    c=wintranslation[c-128];
    break;
  case 2:
    //Koi8->Dos
    c=koi8translation[c-128];
    break;
  }
  if (c<128) return(0); //No Russian letter 
  return(ctype[c-128]);
}

unsigned int def_code (void);

//text formatting procedure 
unsigned int ConvertFormat(int fin,int fs,int fmt)
{
  unsigned int c0;
  unsigned int c1=1; //Start with the passage of characters 
  unsigned int c2=1;
  unsigned int c3=32; //Start with a bullet, once we formatting;

  //unsigned int last_space;

  unsigned int sl;

  register unsigned int s;
  register unsigned int d;
  char ct[256]; //Array to describe the type of character 

  char *ds=dstk;
  register char *us=ustk;

  extern unsigned int STKSZ50;

  int maxstk=STKSZ50;

  d=0;
  us[d]=0;
  sl=0;
  //last_space=0xFFFF;
  s=FL_loader(fin,0xFFFFFFFF);

  if (win_dos_koi==0xFF) win_dos_koi=def_code ();

  //Podgotavlivaem array ct 
  c0=0;
  do
  {
    ct[c0]=GetCharType_x(c0);
  }
  while((++c0)!=sizeof(ct));

#define GetCharType(VAR) (ct[VAR])

  for(;;)
  {
    c0=c1;
    c1=c2;
    c2=c3;
  LSKIP1:
    c3=ds[s++];
    if (s>=maxstk) s=FL_loader(fin,s);
    if (c3==9) c3=' '; //Replace tab for space 
    if (c3==1) c3=' '; //replacement service. characters 
    if ((c3==' ')&&(c2==' ')) goto LSKIP1; //pass gap 
    if ((c3==13)&&(ds[s]==10)) s++; //0D0A->0D
    if ((c3==10)&&(ds[s]==13)) s++; //0A0D->0A
    if (c3==10) c3=13; //0A->0D
    if (c0==0) goto LEOF; //End of text 
    if (fmt==1)
    {
      if ((c0>' ')&&(c1=='-')&&(c2==13)&&(c3>' '))
      {
	//Remove Transfer 
	c1=1;
	c2=1;
	goto LSYM;
      }
      if ((c0>' ')&&(c1==13)&&(c2>' '))
      {
	//replacement of the line of space between words
	c1=' ';
	goto LSYM;
      }
    }
    if (c0==13)
    {
      //In all other cases the transfer line is a paragraph 
      //last_space=0xFFFF;
      sl=0;
      d=FL_saver(fs,d); //oh no Slivaem 
      us[d++]=0; //End of the line 
      curline++;
      if ((c1>' ')&&(fmt==2))
      {
	us[d++]=' '; //If Australia. symbol-letter, adding indentation 

	sl++;
      }
      continue;
    }
  LSYM:
    if (c0!=1)
    {
      us[d]=c0;
      //if ((c0==' ')&&sl) last_space=d; //Zapominaem last gap 
      d++;
      sl++;
      if (sl>max_x)
      {
	//Too long line, looking where the paste transfer 
	unsigned int pp=d+2; //Beginning in the late light App. characters 
	unsigned int pg1=0xFFFFFFFF;
	unsigned int pg2=0xFFFFFFFF;
	int c;
	us[d]=c1;
	us[d+1]=c2;
	us[d+2]=c3;
	for(;;)
	{
	  c=GetCharType(us[pp]);
	  if ((c==5)&&(pp<d))
	  {
	    //No suitable gaps less for a living;
	  L_CUT:
	    d--;
	    d=FL_saver(fs,d);
	    us[d++]=0;
	    us[d++]=c0;
	    sl=1;
	    break;
	  }
	  if ((c==4)&&(pp<d))
	  {
	    //Rezhem on gap 
	    if (us[pp-1]<2) goto L_CUT; //The first gap is not clipped 
	    us[pp]=0; //Obrezaem for space and formatting sign 
	    sl=(d-pp)-1;
	    d=FL_saver(fs,d); //oh no Slivaem 
	    //last_space=0xFFFF;
	    break;
	  }
	  if ((c<1)||(c>3))
	  {
	    pg1=0xFFFFFFFF; //The new floor 
	    pg2=0xFFFFFFFF;
	  }
	  if (c==2)
	  {
	    pg2=pg1;
	    pg1=pp;
	    if (pg2!=0xFFFFFFFF)
	    {
	      //Got two vowels 
	      unsigned int pm=(pg2+pg1+1)>>1;
	      if (GetCharType(us[pm])==3) pm++; //If not divorce letter 
	      c=GetCharType(us[pm-2]);
	      if ((pm<(d-1))&&(c>0)&&(c<4))
	      {
		if (pm==pg2)
		{
		  //If transparent nepostredstvenno right, check whether it is not one 
		  c=GetCharType(us[pg2+1]);
		  if ((c<1)||(c>3)) goto L_NOPERE;
		}
		{
		  //memmove(us+(pm+2),us+pm,d-pm);
		  unsigned int len=d-pm;
		  if (len)
		  {
		    char *d=us+(pm+2)+len-1;
		    char *s=us+pm+len-1;
		    do
		    {
		      *d=*s;
		      d--;
		      s--;
		    }
		    while(--len);
		  }
		}
		us[pm++]='-';
		us[pm++]=0;
		d+=2; //Since pasted 2 character 
		sl=(d-pm);
		d=FL_saver(fs,d); //oh no Slivaem 
		break;
	      L_NOPERE:
		;
	      }
	    }
	  }
	  pp--;
	}
	curline++;
      }
    }
  }
LEOF:
  if (sl) //Not recorded last line 
  {
    us[d++]=0;
    curline++;
  }
  d=FL_saver(fs,d); //oh no Slivaem 
  return(d);
}

//-------------------------------------------------------------
// Automatic identification code (on the first boot) 
//-------------------------------------------------------------
/* Table combinations*/

static const unsigned char table_2s[128]={0xFF,0xFF,0xFF,0xC7,0xFE,0xBE,0xF7,0xFB,
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
unsigned int alt2num (int a)
{
  if (a>=0xE0) a-=0x30;
  return (a&31);
}
/* =========================================================================
Koi2num support functions. 
Admission: a Russian-code letters in the encoding KOI. 
Withdrawal: number of the letters (0-31).
========================================================================= */
unsigned int koi2num (int a)
{
  static const unsigned char t[32]={30,0,1,22,4,5,20,3,21,8,9,10,11,12,13,14,15,31,
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

unsigned int work_2s (unsigned int c1, unsigned int c2, unsigned int check, unsigned char buf[128])
{
  unsigned int i=(c1<<2)+(c2>>3); /* Number of bytes in the array.*/
  unsigned int mask=0x80>>(c2&7); /* mask, the number of bits in bytes.*/

  /* If you check = 1, check: if the bit is 0 array buf, 
   thus, this combination has already met earlier. Then go out 
   functions returning 0. If the combination is not met, then mark that 
   it met (obnulyaem a bit array buf).*/

  if (check==1)
  {
    if ((buf[i]&mask)==0) return (0);
    buf[i]&=~mask;
  }

  /* Checking, acceptable combination or not.*/

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

unsigned int def_code (void)
{
  /* The array buf_1 stores information about what combination of letters battle 
   have met in alternative ALT, and the array buf_2-in option WIN.*/

  unsigned char buf_1 [128];
  unsigned char buf_2 [128];


  unsigned int s=0;

  unsigned int bad_1=0;
  unsigned int bad_2=0;
  unsigned int bad_3=0;
  unsigned int all_1=0;
  unsigned int all_3=0;  /* all_2=all_3 */

  unsigned int c1;
  unsigned int c2=0; /* Characters treated this combination. */

  /* Initialization buf_1 and buf_2. */

  my_memset(buf_1,0xFF,sizeof(buf_1));
  my_memset(buf_2,0xFF,sizeof(buf_2));

  /* main loop-handling combinations for each of the three options. Cycle 
   running until the earlier text, or in any of the options 
   meet n combinations. */

  while ((s<16384)&&(all_1<255)&&(all_3<255))
  {
    c1=c2;
    if ((c2=dstk[s])==0) break;
    s++;
    /* Option ALT. First check whether the current mix of characters 
     codes Russians letters in the encoding ALT.*/

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

    if ((c1&c2)>=0xC0) /* Ekvivalentno conditions (c1> = 0xC0) & & (c2> = 0xC0).  */
    {
      switch (work_2s(c1&31,c2&31,1,buf_2)) /* Obrabotali.*/
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

      switch (work_2s(koi2num(c1),koi2num(c2),0,NULL)) /* Obrabotali.  */
      {
      case 2: bad_3++;
      case 1: all_3++;
      }
    }
  }

  /* Data collected. Now, if any of the options unacceptable 
   the combination of no more than 1 / 32 of the total number, then think that they are not 
   it was. */

  if (bad_1<=(all_1>>5)) bad_1=0;
  if (bad_2<=(all_3>>5)) bad_2=0;
  if (bad_3<=(all_3>>5)) bad_3=0;

  /* Obtain result.*/

  {
    unsigned int a=((255-bad_1)<<8)+all_1;
    unsigned int b=((255-bad_2)<<8)+all_3;
    unsigned int c=((255-bad_3)<<8)+all_3;

    if ((a>=b)&&(a>=c)) return (0);
    if (b>=c) return (1); else return (2);
  }
}
