
typedef struct
{
  signed char NESM[6];
  unsigned char tsongs, csong;
  unsigned short load, init, play;
  signed char SongName[32];
  signed char Artist[32];
  signed char Copyright[32];
  unsigned short speednoisedevidersc;
  unsigned char BankSwitch[8];
  unsigned short speedpal;
  unsigned char PNBits, extra, al1, al2, al3, al4;
}
NSFHDR;

//unsigned short speed;

//#define byte unsigned char
extern unsigned char PSG[16];

extern int samplerate;
unsigned short addrmask = 0xFFFF;
NSFHDR NSF_HDR;
typedef  unsigned short WORD;
typedef unsigned char BYTE;


signed long square1devider, square2devider, triangledevider, noisedevider;
unsigned char square1seqpos, square2seqpos, triangleseqpos;
unsigned long square1volume, square2volume, trianglevolume, noisevolume;
signed long square1period, square2period, triangleperiod, square1lencounter, square2lencounter,
     trianglelencounter, noiselencounter;
unsigned char sw1d, sw2d;
unsigned long noiseoutput;
signed short dmcdevider;
unsigned char daccounter;
unsigned char dmcbuffer, dmcbuffercount, dmcsilence;
signed long dmcdmaadr, dmcdatalen;
signed char noiseenvelope, noiseenvdiv;
signed char square1envelope, square1envdiv;
signed char square2envelope, square2envdiv;
unsigned char triabglelinearcounter, twhaltflag;
unsigned short MainClock;
unsigned long randseed;
short frameseqcount, framesequence;
int lastvalue;
signed char square1sweep, sweep1shift, sweep1negative, sq1sweepperiod;
signed char square2sweep, sweep2shift, sweep2negative, sq2sweepperiod;
unsigned char trianglewave[32] =
{
  0xF, 0xE, 0xD, 0xC, 0xB, 0xA, 0x9, 0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1, 0x0, 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
       0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF
};

const signed char squarewave[4] [8] =
{
  -1, 1, -1, -1, -1, -1, -1, -1, -1, 1, 1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, -1, -1, -1, 1, -1, -1, 1, 1, 1, 1, 1
};

const short dmcperiod[16] =
{
  0x1AC, 0x17C, 0x154, 0x140, 0x11E, 0x0FE, 0x0E2, 0x0D6, 0x0BE, 0x0A0, 0x08E, 0x080, 0x06A, 0x054, 0x048, 0x036
};

unsigned short noiseperiod[16] =
{
  4, 8, 16, 32, 64, 96, 128, 160, 202, 254, 380, 508, 762, 1016, 2034, 4068
};


unsigned char lengthtable[32] =
{
  5, 127, 10, 1, 19, 2, 40, 3, 80, 4, 30, 5, 7, 6, 13, 7, 6, 8, 12, 9, 24, 10, 48, 11, 96, 12, 36, 13, 8, 14, 16, 15
};




unsigned short randint( long max )
{
  randseed = randseed * 0x08088405;
  randseed++;
  return ( ( randseed >> 16 ) * max ) >> 16;
}

void NSF_Init()
{
  daccounter = 64;
  trianglevolume = 16;
 }

 void APUWrite( unsigned short address, unsigned char data )
{
  PSG[address-0x4000]=data;
  //*((unsigned short*)0xA8400000)=address;
  switch ( address )
  {
    //Square1
    //ddle nnnn   duty, loop enoisevolume/disable length, enoisevolume disable, vol/enoisevolume
    case 0x4000:
      sw1d = PSG[0x00] >> 6;
      square1volume = PSG[0x00] & 0x0F;
      //if(PSG[0x00]&32)PSG[0x15]=PSG[0x15]&254;else
      //     PSG[0x15]=PSG[0x15]|1;
    break;
      //eppp nsss   enable sweep, period, negative, shift
    case 0x4001:
      square1sweep = ( PSG[0x01] >> 4 ) & 7;
      sweep1shift = PSG[0x01] & 7;
      sweep1negative = PSG[0x01] & 8;
      sq1sweepperiod = ( PSG[0x01] >> 4 ) & 7;
    break;
      //pppp pppp   period low
    case 0x4002:
      square1period = ( PSG[0x02] + ( ( PSG[0x03] & 7 ) << 8 ) );
    break;
      //llll lppp length index, period high
    case 0x4003:
      square1period = ( PSG[0x02] + ( ( PSG[0x03] & 7 ) << 8 ) );
      square1lencounter = lengthtable[PSG[0x03] >> 3];
      square1devider = 0;
      square1envelope = 15;
      square1envdiv = ( PSG[0x00] & 15 ) + 1;
    break;
      //Square2
      //ddle nnnn   duty, loop enoisevolume/disable length, enoisevolume disable, vol/enoisevolume
    case 0x4004:
      sw2d = PSG[0x04] >> 6;
      square2volume = PSG[0x04] & 0x0F;
      // if(PSG[0x04]&32)PSG[0x15]=PSG[0x15]&253;else
      //      PSG[0x15]=PSG[0x15]|2;
    break;
      //eppp nsss   enable sweep, period, negative, shift
    case 0x4005:
      square2sweep = ( PSG[0x05] >> 4 ) & 7;
      sweep2shift = PSG[0x05] & 7;
      sweep2negative = PSG[0x05] & 8;
      sq2sweepperiod = ( PSG[0x05] >> 4 ) & 7;
    break;
      //pppp pppp   period low
    case 0x4006:
      square2period = ( PSG[0x06] + ( ( PSG[0x07] & 7 ) << 8 ) );
    break;
      //llll lppp length index, period high
    case 0x4007:
      square2period = ( PSG[0x06] + ( ( PSG[0x07] & 7 ) << 8 ) );
      square2lencounter = lengthtable[PSG[0x07] >> 3];
      square2devider = 0;
      square2envelope = 15;
      square2envdiv = ( PSG[0x04] & 15 ) + 1;

    break;
      //Triangle
      //clll llll   conoisedeviderrol, linear counoisedeviderer load
    case 0x4008:
      if ( ( PSG[0x08] & 128 ) > 0 ) trianglelencounter = lengthtable[PSG[0x0B] >> 3];

    break;
      //pppp pppp   period low
    case 0x400A:
      triangleperiod = ( PSG[0x0A] + ( ( PSG[0x0B] & 7 ) << 8 ) );
    break;
      //llll lppp   length index, period high
    case 0x400B:
      triangleperiod = ( PSG[0x0A] + ( ( PSG[0x0B] & 7 ) << 8 ) );
      twhaltflag = 128;
    break;
      //Noise
      //--le nnnn   loop enoisevolume/disable length, enoisevolume disable, vol/enoisevolume period
    case 0x400C:

      noisevolume = PSG[0x0C] & 15;
      //if(PSG[0x0C]&32)PSG[0x15]=PSG[0x15]&247;else
      //      PSG[0x15]=PSG[0x15]|8;
    break;
      //s--- pppp   short mode, period index
    case 0x400E:
      noisedevider = 0;
    break;
      //llll l---   length index
    case 0x400F:
      noiselencounter = lengthtable[PSG[0x0F] >> 3];
      noiseenvelope = 15;
      noiseenvdiv = ( PSG[0x0C] & 15 ) + 1;
    break;
      //DMC
      //il-- ffff   IRQ enable, loop, frequency index
    case 0x4010:


    break;
      //-ddd dddd   DAC
    case 0x4011:
      daccounter = ( PSG[0x11] & 127 );
    break;
      //aaaa aaaa   sample address
    case 0x4012:
      dmcdmaadr = PSG[0x12] * 0x40 + 0xC000;
    break;
      //llll llll   sample length
    case 0x4013:
      dmcdatalen = PSG[0x13] * 0x10 + 1;

    break;
      //Common
      //---d noisedevider21   length ctr enable: DMC, noise, triangle, pulse 2, 1
    case 0x4015:

    break;
      //fd-- ----   5-frame cycle, disable frame inoisedevidererrupt
    case 0x4017:
      framesequence = 0;
      frameseqcount = 0;
    break;

  }
}

void LenSweepC()
{

  if ( ( ( PSG[0x00] & 32 ) == 0 ) && ( square1lencounter > 0 ) )
  {
    square1lencounter--;
  }
  if ( ( ( PSG[0x04] & 32 ) == 0 ) && ( square2lencounter > 0 ) )
  {
    square2lencounter--;
  }
  if ( ( ( PSG[0x08] & 128 ) == 0 ) && ( trianglelencounter > 0 ) )
  {
    trianglelencounter--;
  }
  if ( ( ( PSG[0x0C] & 32 ) == 0 ) && ( noiselencounter > 0 ) )
  {
    noiselencounter--;
  }
  //Sweep
  //Square1
  if ( PSG[0x01] & 128 ) square1sweep -= 1;
  if ( square1sweep < 0 )
  {
    square1sweep = sq1sweepperiod;
    if ( sweep1negative )
      square1period = square1period - ( square1period >> ( sweep1shift + 1 ) );
    else
      square1period = square1period + ( square1period >> ( sweep1shift + 1 ) );
    if ( square1period < 0 ) square1period += 2048;
    if ( square1period > 2047 ) square1period -= 2048;
  }
  //
  //Square2
  if ( PSG[0x05] & 128 ) square2sweep -= 1;
  if ( square2sweep < 0 )
  {
    square2sweep = sq2sweepperiod;
    if ( sweep1negative )
      square2period = square2period - ( square2period >> ( sweep1shift + 1 ) );
    else
      square2period = square2period + ( square2period >> ( sweep1shift + 1 ) );
    if ( square2period < 0 ) square2period += 2048;
    if ( square2period > 2047 ) square2period -= 2048;
  }

}

void EnvLinC()
{
  //Linear counter
  if ( twhaltflag != 0 )
  {
    triabglelinearcounter = PSG[0x08] & 127;
  }
  else
  {
    if ( triabglelinearcounter > 0 )
    {
      triabglelinearcounter--;
    }
  }
  if ( ( PSG[0x08] & 128 ) == 0 )
  {
    twhaltflag = 0;
  }

  //Envelope
  //Noise
  noiseenvdiv--;
  if ( noiseenvdiv <= 0 )
  {
    noiseenvdiv = ( PSG[0x0C] & 15 ) + 1;
    if ( noiseenvelope > 0 ) noiseenvelope--;
    if ( ( noiseenvelope <= 0 ) && ( ( PSG[0x0C] & 32 ) != 0 ) ) noiseenvelope = 15;
  }
  //Square1
  square1envdiv--;
  if ( square1envdiv <= 0 )
  {
    square1envdiv = ( PSG[0x00] & 15 ) + 1;

    if ( square1envelope > 0 ) square1envelope--;
    if ( ( square1envelope <= 0 ) && ( ( PSG[0x00] & 32 ) != 0 ) )
      square1envelope = 15;
  }
  //Square2
  square2envdiv--;
  if ( square2envdiv <= 0 )
  {
    square2envdiv = ( PSG[0x04] & 15 ) + 1;

    if ( square2envelope > 0 ) square2envelope--;
    if ( ( square2envelope <= 0 ) && ( ( PSG[0x04] & 32 ) != 0 ) )
      square2envelope = 15;
  }
}

signed short GetSound()
{
  int add, tri, squ1, squ2, noise;
  add = tri = squ1 = squ2 = noise = 0;

//  if((NsfSongLen-NsfTime)<0){
 //   AudioActive=0;
 //   return(0);}
    /*
  if ( PSG[0x15] & 16 )
  {
    dmcdevider -= 1792000/16000;
    while ( dmcdevider <= 0 )
    {
      dmcdevider += dmcperiod[PSG[0x10] & 15];
      //
      if ( dmcdatalen > 0 )
      {
        if ( dmcbuffer & 1 )
        {
          if ( daccounter < 126 ) daccounter += 2;
        }
        else
        {
          if ( daccounter > 1 ) daccounter -= 2;
        }
      }

      dmcbuffer = dmcbuffer >> 1;
      dmcbuffercount++;
      if ( dmcbuffercount >= 8 )
      {
        dmcbuffercount = 0;
        if ( dmcdatalen > 0 ) dmcbuffer = vra[dmcdmaadr];
        //if(dmcbuffer==0)dmcsilence=1;else dmcsilence=0;
        dmcdmaadr++;
        if ( dmcdmaadr > 0xFFFF ) dmcdmaadr = 0x8000;
        if ( dmcdatalen > 0 ) dmcdatalen--;
        if ( dmcdatalen <= 0 )
        {
          if ( PSG[0x10] & 64 )
          {
            dmcdmaadr = PSG[0x12] * 0x40 + 0xC000;
            dmcdatalen = PSG[0x13] * 0x10 + 1;
          }
        }
      }
    }
  }
*/
  if ( triangleperiod >= 8 ) triangledevider -= 1792000/16000;
  while ( triangledevider <= 0 )
  {
    triangledevider += triangleperiod + 1;
    if ( ( PSG[0x0A] + ( ( PSG[0x0B] & 7 ) << 8 ) ) > 4 ) triangleseqpos++;
    if ( triangleseqpos >= 32 ) triangleseqpos = 0;
  }

  if ( square1period >= 8 ) square1devider -= 1792000/16000/2;
  while ( square1devider <= 0 )
  {
    square1devider += ( square1period + 1 );
    square1seqpos++;
    if ( square1seqpos >= 8 ) square1seqpos = 0;
  }
  //
  if ( square2period >= 8 ) square2devider -= 1792000/16000/2;
  while ( square2devider <= 0 )
  {
    square2devider += square2period + 1;
    square2seqpos++;
    if ( square2seqpos >= 8 ) square2seqpos = 0;
  }

  noisedevider -= 1792000/16000;
  if ( noisedevider <= 0 )
  {
    noisedevider += noiseperiod[PSG[0x0E] & 15];
    if ( ( PSG[0x0C] & 16 ) == 0 ) noiseoutput = ( randint( 2 ) - 1 ) * noiseenvelope;
    else
      noiseoutput = ( randint( 2 ) - 1 ) * noisevolume;
  }
  //
  if ( ( ( PSG[0x15] & 1 ) == 0 ) || ( square1lencounter != 0 ) )
  {
    if ( ( PSG[0x00] & 16 ) != 0 ) squ1 = squarewave[sw1d] [square1seqpos] * square1volume;
    else
      squ1 = squarewave[sw1d] [square1seqpos] * square1envelope;
  }
  if ( ( ( PSG[0x15] & 2 ) == 0 ) || ( square2lencounter != 0 ) )
  {
    if ( ( PSG[0x04] & 16 ) != 0 ) squ2 = squarewave[sw2d] [square2seqpos] * square2volume;
    else
      squ2 = squarewave[sw2d] [square2seqpos] * square2envelope;
  }
  if ( ( ( ( PSG[0x15] & 4 ) == 0 ) && ( trianglelencounter != 0 ) ) || ( ( triabglelinearcounter != 0 ) ) )
    tri = ( trianglewave[triangleseqpos] - 7 ) * trianglevolume;

  if ( ( ( PSG[0x15] & 8 ) == 0 ) || ( noiselencounter != 0 ) )
  {
    noise = noiseoutput;
  }


  frameseqcount++;
  if ( frameseqcount >= ( samplerate/50 / 4 ) )
  {
    frameseqcount = 0;
    if ( ( PSG[0x17] & 128 ) == 0 )
    //4 steps
    {
      if ( ( framesequence == 1 ) || ( framesequence == 3 ) )
      {
        LenSweepC();
      } //clock length counoisedeviderers and sweep units
      EnvLinC();
      if ( framesequence >= 3 ) framesequence = 0;
    }
    else
    //5 steps
    {
      if ( ( framesequence == 0 ) || ( framesequence == 2 ) )
      {
        LenSweepC();
      } //clock length counoisedeviderers and sweep units
      if ( framesequence < 4 ) EnvLinC();
      if ( framesequence >= 4 ) framesequence = 0;
    }
    framesequence++;
    LenSweepC();
  }

  //
  /*
  MainClock++;
  if ( MainClock >= speed )
  {
    NsfTime+=1;
    MainClock = 0;
    PC = NSF_HDR.play;
    PSG[0x100 + S--] = 0xFF;
    PSG[0x100 + S--] = 0xFF;
    while ( PC > 4 )
    {
      opcode = PSG[PC++];
      instruction[opcode] ();
    }
    //PSG[0x15]=PSG[0x15]&(255-192);
  }  
  */
  add = ( ( squ1 + squ2 ) * 8 + noise * 6 + tri ) * 32;


// if((NsfSongLen-NsfTime)<256)add=add*(NsfSongLen-NsfTime)/256;
  return add;

}
