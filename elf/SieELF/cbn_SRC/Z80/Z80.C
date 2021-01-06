
//часть inline функципй (типа popw) могут содержать ошибки
//где _pc++ ++ !!!!!!!!!!! не проверялись!!!
//также возможны ошибки из-за убранного &0xff в некоторых местах (для ускорения)

//#pragma optimize=no_code_motion

//z80 emulator
//Взято с http://cbn.narod.ru  (c)bn
//при сборке добавить в проект библ. Zlib (взять из других примеров)
//и #define UNPACK #define NEWSGOLD
// функцию loadfile взять из сорцов словаря, например
// поддержка rar, 7z вырезана

#include "..\swilib.h"

#define public
#define private
#define static
#define protected
#define final
#define boolean char
#define byte char
#define false 0
#define true 1
#define null 0
//#define u16 unsigned short
#define useasm

inline int max(int x, int y){ return (x>y)?x:y;}
inline int min(int x, int y){ return (x<y)?x:y;}

extern void lddrr(void *to, void *from, int size);
extern void ldirr(void *to, void *from, int size);

public final void ex_af_af();
public void reset();

char *Title="Z80 0.88 (c)bn";
void UpdateCSMname();

char filename[128], *file;
//unsigned int err;

const int paramlength=151;
const unsigned char fpstab[]={262/5,262/6,262/7,262/8,262/9,262/10,262/11,262/12,262/13,262/14};
char param[151];
char menu[256];
unsigned char count, redkey, rrkey;

GBSTMR timer;
//WSHDR *info_ws=0;

#define RGB8(R,G,B) (B+(G<<2)+(R<<5))

char help[]=
" Z80 elf 0.88"
"\n1.Load 0-9,#"
"\n2.Save 0-9,#"
"\n3.Fps 0-9:%d"
"\n4.Int 1-5:%d"
"\n7.Rotate"
"\n8.Resize"
"\nLeft:Altern Key"
"\nGreen:Redefine:"
"\nkey:value:Green"
"\ncbn.narod.ru"
"\ncbn@yandex.ru";

private final void execute_id_cb(int op, int z);
public int inb( int port );
private final int execute_cb();
public void outb( int port, int outByte, int tstates );
private final int execute_id();
private final int execute_ed( int local_tstates );
void loadsave(int num, boolean save);
void drawhelp();
//void debsave();

  int  maxx=176>>3;
  boolean ldir=false, fz128=false, fsna=true, fneed128=false, 
    frotate=false, fzxrotate=false, fzxsmall=false;

  volatile int mode=100;
  volatile  int minx=0, miny=0;

extern char *screen;//[width*height]; // Экран 132*176
extern int width, height, screensize;
extern void DrawScreen(); // Функция перерисовки экрана
extern unsigned char C65, S75, EL71;
char scrbuf[192*256];//буфер экрана

  int maxy=132>>3; ///ПОСЧИТАТЬ!
  
  unsigned char *scrrot=null; //free!!!
  unsigned char  *mem=null, *zx=null ;// new byte[ 65536 ]; //free!!

  int newBorder = 7; 
	int t, tm, tmp, temp; //temp
	const int zxpage[]= //page0-7
		{0x10000, 0x14000, 0x8000, 0x18000, 0x1c000, 0x4000, 0x20000, 0x24000};
	const int romstart=0x10000, rompage=0x4000, rombuf1=0x14000,
	  rombuf2=0, rom48size=0x20040, rom128size=0x30000, rom48=0x28000, rom128=0x2c000, rombank=0xc000;
	byte pport=0, trdos=0;//35 offset
	int keylines[8];	// Линии кл.
  //int colors[] = {0,0xee,0xee0000,0xee00ee, // Цвета
  //	  0xee00,0xeeee,0xeeee00,0xeeeeee,
	//  0,0xff,0xff0000,0xff00ff,
	//  0xff00,0xffff,0xffff00,0xffffff};
  byte colors[] = {0,0x2,0xc0,0xc2, // Цвета ? 0x3  0xc3
  	0x18,0x1e,0xd8,0xda, //?1f
	  0,0x3,0xe0,0xe3,
	  0x1c,0x1f,0xfc,0xff};

  int fps=262/6, tst=4;
  int alternate=0;
  byte *tape=null;
	int *tapeidx=null;
	int tapecur=0, tapeptr=0;
	boolean autostart=true, startape=false;//?

	public int zxfilesize=0;
  public int tstatesPerInterrupt=4*20000; //rp.mhz 4000 000


void drawsym(char *out, char c){ // Отобразить символ на экране
  int i,j;
  byte b, *bptr=(char*)mem+((fz128)?rom48:romstart)+0x3d00+((c-=0x20)<=0?0:(c<<3));
  for(j=0;j<8;j++){
    b=*bptr++;
    for(i=0;i<8;i++){
      *out++=(b&0x80)?0xff:3; //colors
      b<<=1;
    }
    out+=width-8;
  }
}

void drawhelp(){
  int i=0,j,x=0,y=0;
//  char *s=help;
  for(j=0;j<10;j++)
    if(fpstab[j]==fps) break;
  if(j==10) j=0;
  sprintf(menu,help,j+5,tst);
  while(menu[i]){
    if(menu[i]=='\n' || x>=width/8){ x=0; ++y;}
    if(y>=height/10) break;
    drawsym((char*)screen+y*width*10+x*8+4,menu[i]);
    ++x;
    ++i;
  }
}

  
//        protected int tstatesPerInterrupt = clockFrequencyInMHz * 2000000) / 50);

	public static final int IM0 = 0;
	public static final int IM1 = 1;
	public static final int IM2 = 2;

	private static final int F_C  = 0x01;
	private static final int F_N  = 0x02;
	private static final int F_PV = 0x04;
	private static final int F_3  = 0x08;
	private static final int F_H  = 0x10;
	private static final int F_5  = 0x20;
	private static final int F_Z  = 0x40;
	private static final int F_S  = 0x80;

	private static final int PF = 0x04;
	private static final int p_ = 0;

	private static final boolean parity[256];
  
  
  void initparity(){  //!!!!!!!
   int i,j;
   boolean p;
   for ( i = 0; i < 256; i++ ) {
			p = true;
			for ( j = 0; j < 8; j++ ) {
				if ( (i & (1<<j)) != 0 ) {
					p = !p;
				}
			}
			parity[ i ] = p;
		}
	}
  


	/** Main Registers */
	protected int        _A = 0, _HL = 0, _B = 0, _C = 0, _DE = 0;
	protected boolean    fS = false, fZ  = false, f5 = false, fH = false;
	protected boolean    f3 = false, fPV = false, fN = false, fC = false;

	/** Alternative registers */
	protected int        _AF_ = 0, _HL_ = 0, _BC_ = 0, _DE_ = 0;

	/** Index registers -  ID is used as temporal register for ix/iy */
	protected int        _IX = 0, _IY = 0, _ID = 0;

	/** Stack Pointer and Program Counter */
	protected int        _SP = 0, _PC = 0;

	/** Interrupt and Refresh registers */
	protected int        _I = 0, _R = 0, _R7 = 0;

	/** Interrupt mode */
	protected boolean    _IFF1 = true, _IFF2 = true;
	protected int        _IM = 2;

	/** the main memory */
//	public final int  mem[] = new int[ 65536 ];

      	/** Access to 8-bit register */
	inline public final int  A() { return _A; }
	inline public final void xA( int bite ) {
		_A = bite;
	}


	/** Access to Flags register */
	inline public final void setZ( boolean f ) { fZ = f; }
	inline public final void setC( boolean f ) { fC = f; }
	inline public final void setS( boolean f ) { fS = f; }
	inline public final void setH( boolean f ) { fH = f; }
	inline public final void setN( boolean f ) { fN = f; }
	inline public final void setPV( boolean f ) {fPV = f;}
	inline public final void set3( boolean f ) { f3 = f; }
	inline public final void set5( boolean f ) { f5 = f; }

	inline public final boolean Zset()  { return fZ; }
	inline public final boolean Cset()  { return fC; }
	inline public final boolean Sset()  { return fS; }
	inline public final boolean Hset()  { return fH; }
	inline public final boolean Nset()  { return fN; }
	inline public final boolean PVset() { return fPV; }
      

	public final int F() {
		return	(Sset()  ? F_S  : 0)  |
			(Zset()  ? F_Z  : 0)  |
			(f5      ? F_5  : 0)  |
			(Hset()  ? F_H  : 0)  |
			(f3      ? F_3  : 0)  |
			(PVset() ? F_PV : 0)  |
			(Nset()  ? F_N  : 0)  |
			(Cset()  ? F_C  : 0);
	}
	public final void xF( int bite ) {
		fS  = (bite & F_S)  != 0;
		fZ  = (bite & F_Z)  != 0;
		f5  = (bite & F_5)  != 0;
		fH  = (bite & F_H)  != 0;
		f3  = (bite & F_3)  != 0;
		fPV = (bite & F_PV) != 0;
		fN  = (bite & F_N)  != 0;
		fC  = (bite & F_C)  != 0;
	}

	inline public final int  B() { return _B; }
	inline public final void xB( int bite ) {
		_B = bite;
	}
	inline public final int  C() { return _C; }
	inline public final void xC( int bite ) {
		_C = bite;
	}

	inline public final int  D() { return (_DE >> 8); }
	inline public final void xD( int bite ) {
		_DE = (bite << 8) | (_DE & 0x00ff);
	}
	inline public final int  E() { return (_DE & 0xff); }
	inline public final void xE( int bite ) {
		_DE = (_DE & 0xff00) | bite;
	}

	inline public final int  H() { return (_HL >> 8); }
	inline public final void xH( int bite ) {
		_HL = (bite << 8) | (_HL & 0x00ff);
	}
	inline public final int  L() { return (_HL & 0xff); }
	inline public final void xL( int bite ) {
		_HL = (_HL & 0xff00) | bite;
	}

        
	/** Access as 16-bit registers*/
	inline public final int  AF() { return (A() << 8) | F(); }
	inline public final void xAF( int word ) {
		xA( word >> 8 );
		xF( word & 0xff );
	}

	inline public final int  BC() { return (B() << 8) | C(); }
	inline public final void xBC( int word ) {
		xB( word >> 8 );
		xC( word & 0xff );
	}

	inline public final int  DE() { return _DE; }
	inline public final void xDE( int word ) {
		_DE = word;
	}

	inline public final int  HL() { return _HL; }
	inline public final void xHL( int word ) {
		_HL = word;
	}

	inline public final int  PC() { return _PC; }
	inline public final void xPC( int word ) {
		_PC = word;
	}

	inline public final int  SP() { return _SP; }
	inline public final void xSP( int word ) {
		_SP = word;
	}

	inline public final int  ID() { return _ID; }
	inline public final void xID( int word ) {
		_ID = word;
	}

	inline public final int  IX() { return _IX; }
	inline public final void xIX( int word ) {
		_IX = word;
	}

	inline public final int  IY() { return _IY; }
	inline public final void xIY( int word ) {
		_IY = word;
	}


	inline public final int  IDH() { return (_ID >> 8); }
	inline public final void xIDH( int bite ) {
		_ID = (bite << 8) | (_ID & 0x00ff);
	}
	inline public final int  IDL() { return (_ID & 0xff); }
	inline public final void xIDL( int bite ) {
		_ID = (_ID & 0xff00) | bite;
	}


	/** Memory refresh register */
	inline public final int  R7() { return _R7; }
	inline public final int  R() { return (_R & 0x7f) | _R7; }
	inline public final void xR( int bite ) {
		_R  = bite;
		_R7 = bite & 0x80;
	}

	inline public final void REFRESH( int t ) {
		_R += t;
	}


	/** Interrupt mode and interrupt register */
	inline public final int  I() { return _I; }
	inline public final void xI( int bite ) {
		_I = bite;
	}

	inline public final boolean IFF1() { return _IFF1; }
	inline public final void xIFF1( boolean iff1 ) {
		_IFF1 = iff1;
	}

	inline public final boolean IFF2() { return _IFF2; }
	inline public final void xIFF2( boolean iff2 ) {
		_IFF2 = iff2;
	}

	inline public final int IM() { return _IM; }
	inline public final void xIM( int im ) {
		_IM = im;
	}



	/** Access to a byte */
	inline private final int peekb( int addr ) {
		return mem[ addr ];
	}
	inline public void pokeb( int addr, int newByte ) {
		mem[ addr ] = newByte;
	}


	/** Access to a Word */
	inline public void pokew( int addr, int word ) {
		pokeb( addr, word & 0xff );
//		addr++;
		pokeb( (addr+1) & 0xffff, word >> 8 );
	}
	inline private final int peekw( int addr ) {
//		int        t = peekb( addr );
//		addr++;
//		return t | (peekb( addr & 0xffff ) << 8);
            return mem[addr] | (mem[(addr+1) & 0xffff] << 8);
	}

	/** Access to Program counter */
/*	inline private final int nxtpcb() {
		int pc = PC();
		int t = peekb( pc );
		xPC( ++pc & 0xffff );
		return t;
	}
	inline private final int nxtpcw() {
		int pc = PC();
		int t = peekb( pc );
		t |= ( peekb( ++pc & 0xffff ) << 8 );
		xPC( ++pc & 0xffff );
		return t;
	}
*/
	inline private final int nxtpcb() {
            return mem[_PC++];
//		int pc = PC();
//		int t = peekb( pc );
//		xPC( ++pc & 0xffff );
//		return t;
	}
	inline private final int nxtpcw() { 
           return mem[_PC++]|(mem[_PC++]<<8); //??ERROR here!!!!!!!!!!
//		int pc = PC();
//		int t = peekb( pc );
//		t |= ( peekb( ++pc & 0xffff ) << 8 );
//		xPC( ++pc & 0xffff );
//		return t;
	}


        
	/** Access to index register */
	inline private final int ID_d() {
		return ((ID()+(byte)nxtpcb()) & 0xffff);
	}


	/** Access to stack */
	inline public final void pushw( int word ) {
//		int        sp = ((SP()-2) & 0xffff);
//		xSP( sp );
		pokew( _SP=(_SP-2)&0xffff, word );
	}
	inline public final int popw() {
          return mem[_SP++]|(mem[_SP++]<<8);
//		int	sp = SP();
//		int	t  = peekb( sp );
//			sp++;
//			t |= (peekb( sp & 0xffff) << 8);
//			xSP( ++sp & 0xffff );
//		return t;
	}


	/** Stack operations for "call" instructions" */
	inline public final void pushpc() { pushw( PC() ); }
	inline public final void poppc()  { xPC( popw() ); }




	/** IO ports  */
//	public void outb( int port, int bite, int tstates ) {
//	}
//	public int inb( int port ) {
//		return 0xff;
//	}

	/** Interrupt manager  */
	inline private static final boolean interruptTriggered( int tstates ) {
		return (tstates >= 0);
	}

	public int interrupt() {
		// If it's not a masking interrupt
		if ( !IFF1() ) {
			return 0;
		}

		switch( IM() ) {
		case 0://IM0:
		case 1://IM1:
			pushpc();
			xIFF1( false );
			xIFF2( false );
			xPC( 56 );
			return 13;
		case 2://IM2:
			pushpc();
			xIFF1( false );
			xIFF2( false );
			int t = (I()<<8) | 0x00ff;
			xPC( peekw(t) );
			return 19;
		}

		return 0;
	}

	private final int in_bc() {
		int        ans = inb( BC() );

		setZ( ans == 0 );
		setS( (ans & F_S)!=0 );
		set3( (ans & F_3)!=0 );
		set5( (ans & F_5)!=0 );
		setPV( parity[ ans ] );
		setN( false );
		setH( false );

		return ans;
	}

	/** Add with carry, altering all flags */
	private final void
	adc_a( int b )
	{
		int a    = A();
		int c    = Cset() ? 1 : 0;
		int wans = a + b + c;
		int ans  = wans & 0xff;

		setS( (ans & F_S)  != 0 );
		set3( (ans & F_3)  != 0 );
		set5( (ans & F_5)  != 0 );
		setZ( (ans)        == 0 );
		setC( (wans&0x100) != 0 );
		setPV( ((a ^ ~b) & (a ^ ans) & 0x80) != 0 );
		setH(  (((a & 0x0f) + (b & 0x0f) + c) & F_H) != 0 );
		setN( false );

		xA( ans );
	}

	/** Add without carry, altering all flags */
	private final void
	add_a( int b )
	{
		int a    = A();
		int wans = a + b;
		int ans  = wans & 0xff;

		setS( (ans & F_S)  != 0 );
		set3( (ans & F_3)  != 0 );
		set5( (ans & F_5)  != 0 );
		setZ( (ans)        == 0 );
		setC( (wans&0x100) != 0 );
		setPV( ((a ^ ~b) & (a ^ ans) & 0x80) != 0 );
		setH(  (((a & 0x0f) + (b & 0x0f)) & F_H) != 0 );
		setN( false );

		xA( ans );
	}
	
	/**Substract with carry, altering all flags */
	private final void
	sbc_a( int b )
	{
		int a    = A();
		int c    = Cset() ? 1 : 0;
		int wans = a - b - c;
		int ans  = wans & 0xff;

		setS( (ans & F_S)  != 0 );
		set3( (ans & F_3)  != 0 );
		set5( (ans & F_5)  != 0 );
		setZ( (ans)        == 0 );
		setC( (wans&0x100) != 0 );
		setPV( ((a ^ b) & (a ^ ans) & 0x80) != 0 );
		setH(  (((a & 0x0f) - (b & 0x0f) - c) & F_H) != 0 );
		setN( true );

		xA( ans );
	}

	/** Subtract without carry - alters all flags */
	private final void
	sub_a( int b )
	{
		int a    = A();
		int wans = a - b;
		int ans  = wans & 0xff;

		setS( (ans & F_S)  != 0 );
		set3( (ans & F_3)  != 0 );
		set5( (ans & F_5)  != 0 );
		setZ( (ans)        == 0 );
		setC( (wans&0x100) != 0 );
		setPV( ((a ^ b) & (a ^ ans) & 0x80) != 0 );
		setH(  (((a & 0x0f) - (b & 0x0f)) & F_H) != 0 );
		setN( true );

		xA( ans );
	}

	/** Left rotation, alters flags H N C 3 5 */
	private final void
	rlc_a()
	{
		int     ans = A();
		boolean c   = (ans & 0x80) != 0;

		if ( c ) {
			ans = (ans << 1)|0x01;
		} else {
			ans <<= 1;
		}
		ans &= 0xff;

		set3( (ans & F_3)  != 0 );
		set5( (ans & F_5)  != 0 );
		setN( false );
		setH( false );
		setC( c );

		xA( ans );
	}

	/** Right rotation, alters flags H N C 3 5 */
	private final void
	rrc_a()
	{
		int     ans = A();
		boolean c   = (ans & 0x01) != 0;

		if ( c ) {
			ans = (ans >> 1)|0x80;
		} else {
			ans >>= 1;
		}

		set3( (ans & F_3)  != 0 );
		set5( (ans & F_5)  != 0 );
		setN( false );
		setH( false );
		setC( c );

		xA( ans );
	}

	/** Left rotation with carry, alters flags H N C 3 5 */
	private final void
	rl_a()
	{
		int     ans = A();
		boolean c   = (ans & 0x80) != 0;

		if ( Cset() ) {
			ans = (ans << 1) | 0x01;
		} else {
			ans <<= 1;
		}

		ans &= 0xff;

		set3( (ans & F_3)  != 0 );
		set5( (ans & F_5)  != 0 );
		setN( false );
		setH( false );
		setC( c );

		xA( ans );
	}

	/** Right rotation with carry, alters flags H N C 3 5 */
	private final void
	rr_a()
	{
		int     ans = A();
		boolean c   = (ans & 0x01) != 0;

		if ( Cset() ) {
			ans = (ans >> 1) | 0x80;
		} else {
			ans >>= 1;
		}

		set3( (ans & F_3)  != 0 );
		set5( (ans & F_5)  != 0 );
		setN( false );
		setH( false );
		setC( c );

		xA( ans );
	}

	/** Compare - alters all flags */
	private final void
	cp_a( int b )
	{
		int a    = A();
		int wans = a - b;
		int ans  = wans & 0xff;

		setS( (ans & F_S) != 0 );
		set3( (b & F_3)   != 0 );
		set5( (b & F_5)   != 0 );
		setN( true );
		setZ( ans == 0 );
		setC( (wans & 0x100)!=0 );
		setH( (((a & 0x0f) - (b & 0x0f)) & F_H) != 0 );
		setPV( ((a ^ b) & (a ^ ans) & 0x80) != 0 );
	}

	/** Bitwise and - alters all flags*/
	private final void
	and_a( int b )
	{
		int ans = A() & b;

		setS( (ans & F_S) != 0 );
		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setH( true );
		setPV( parity[ ans ] );
		setZ( ans == 0 );
		setN( false );
		setC( false );

		xA( ans );
	}

	/** Bitwise or - alters all flags */
	private final void
	or_a( int b )
	{
		int ans = A() | b;

		setS( (ans & F_S) != 0 );
		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setH( false );
		setPV( parity[ ans ] );
		setZ( ans == 0 );
		setN( false );
		setC( false );

		xA( ans );
	}

	/** Bitwise exclusive or - alters all flags */
	private final void
	xor_a( int b )
	{
		int ans = (A() ^ b) & 0xff;

		setS( (ans & F_S) != 0 );
		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setH( false );
		setPV( parity[ ans ] );
		setZ( ans == 0 );
		setN( false );
		setC( false );    

		xA( ans );
	}

	/** Negation (complement 2) - alters all flags */
	private final void
	neg_a()
	{
		int t = A();

		xA( 0 );
		sub_a(t);
	}

	/** Complement-1, alters flags N H 3 5 */
	private final void
	cpl_a()
	{
		int ans = A() ^ 0xff;

		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setH( true );
		setN( true );

		xA( ans );
	}

	/** DAA (Decimal Adjust Accumulator), alters all flags */
	private final void
	daa_a()
	{
		int        ans = A();
		int        incr = 0;
		boolean    carry = Cset();

		if ((Hset()) || ((ans & 0x0f) > 0x09)) {
			incr |= 0x06;
		}
		if (carry || (ans > 0x9f) || ((ans > 0x8f) && ((ans & 0x0f) > 0x09))) {
			incr |= 0x60;
		}
		if (ans > 0x99) {
			carry = true;
		}
		if (Nset()) {
			sub_a(incr);
		} else {
			add_a(incr);
		}

		ans = A();

		setC( carry );
		setPV( parity[ ans ] );
	}

	/** Load a with i */
	private final void
	ld_a_i()
	{
		int ans = I();

		setS( (ans & F_S) != 0 );
		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setZ( ans == 0 );
		setPV( IFF2() );
		setH( false );
		setN( false );

		xA( ans );
	}

	/** Load a with r  */
	private final void
	ld_a_r()
	{
		int ans = R();

		setS( (ans & F_S) != 0 );
		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setZ( ans == 0 );
		setPV( IFF2() );
		setH( false );
		setN( false );

		xA( ans );
	}

	/** Right rotation between A and (HL)*/
	private final void
	rrd_a()
	{
		int ans = A();
		int t   = peekb( HL() );
		int q   = t;

		t   = (t >> 4) | (ans << 4);
		ans = (ans & 0xf0) | (q & 0x0f);
		pokeb( HL(), t );

		setS( (ans & F_S) != 0 );
		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setZ( ans == 0 );
		setPV( IFF2() );
		setH( false );    
		setN( false );        

		xA( ans );
	}

	/** Left rotate between A and (HL) */
	private final void
	rld_a()
	{
		int ans = A();
		int t   = peekb( HL() );
		int q   = t;

		t   = (t << 4) | (ans & 0x0f);
		ans = (ans & 0xf0) | (q >> 4);
		pokeb( HL(), (t & 0xff) );

		setS( (ans & F_S) != 0 );
		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setZ( ans == 0 );
		setPV( IFF2() );
		setH( false );
		setN( false );

		xA( ans );
	}

	/** Test bit, alters all flags except C*/
	private final void
	bit( int b, int r )
	{
		boolean    bitSet = ((r & b) != 0);

		setN( false );
		setH( true );
		set3( (r & F_3) != 0 );
		set5( (r & F_5) != 0 );
		setS( (b == F_S) ? bitSet : false );
		setZ(  !bitSet );
		setPV( !bitSet );
	}

	/** Set flag C (carry), alters flags N H 3 5 C */
	private final void
	scf()
	{
		int        ans = A();

		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setN( false );
		setH( false );
		setC( true );
	}

	/** Complement flag C (carry), alters flags N H 3 5 C */
	private final void
	ccf()
	{
		int        ans = A();

		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setN( false );
		setC( Cset() ? false : true );
	}

	/** Left rotation, alters all flags*/
	private final int
	rlc( int ans )
	{
		boolean c = (ans & 0x80) != 0;

		if ( c ) {
			ans = (ans << 1)|0x01;
		} else {
			ans <<= 1;
		}
		ans &= 0xff;

		setS( (ans & F_S) != 0 );
		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setZ( (ans) == 0 );
		setPV( parity[ ans ] );
		setH( false );
		setN( false );
		setC( c );

		return(ans);
	}

	/** Right rotation, alters all flags*/
	private final int
	rrc( int ans )
	{
		boolean c = (ans & 0x01) != 0;

		if ( c ) {
			ans = (ans >> 1)|0x80;
		} else {
			ans >>= 1;
		}

		setS( (ans & F_S) != 0 );
		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setZ( (ans) == 0 );
		setPV( parity[ ans ] );
		setH( false );
		setN( false );
		setC( c );

		return(ans);
	}

	/** Left rotation with carry, alters all flags*/
	private final int
	rl( int ans )
	{
		boolean c = (ans & 0x80) != 0;

		if ( Cset() ) {
			ans = (ans << 1) | 0x01;
		} else {
			ans <<= 1;
		}
		ans &= 0xff;

		setS( (ans & F_S) != 0 );
		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setZ( (ans) == 0 );
		setPV( parity[ ans ] );
		setH( false );
		setN( false );
		setC( c );

		return(ans);
	}

	/** Right rotation with carry, alters all flags*/
	private final int
	rr( int ans )
	{
		boolean c = (ans & 0x01) != 0;

		if ( Cset() ) {
			ans = (ans >> 1) | 0x80;
		} else {
			ans >>= 1;
		}

		setS( (ans & F_S) != 0 );
		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setZ( (ans) == 0 );
		setPV( parity[ ans ] );
		setH( false );
		setN( false );
		setC( c );

		return(ans);
	}

	/** SLA, alters all flags (probado) */
	private final int
	sla( int ans )
	{
		boolean c = (ans & 0x80) != 0;
		ans = (ans << 1) & 0xff;

		setS( (ans & F_S) != 0 );
		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setZ( (ans) == 0 );
		setPV( parity[ ans ] );
		setH( false );
		setN( false );
		setC( c );

		return(ans);
	}

	/** SLS, alters all flags (Shift Left and Set) */
	private final int
	sls( int ans )
	{
		boolean c = (ans & 0x80) != 0;
		ans = ((ans << 1) | 0x01) & 0xff;

		setS( (ans & F_S) != 0 );
		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setZ( (ans) == 0 );
		setPV( parity[ ans ] );
		setH( false );
		setN( false );
		setC( c );

		return(ans);
	}

	/** SRA (Shift Right Arithmetically), alters all flags*/
	private final int
	sra( int ans )
	{
		boolean c = (ans & 0x01) != 0;
		ans = (ans >> 1) | (ans & 0x80);

		setS( (ans & F_S) != 0 );
		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setZ( (ans) == 0 );
		setPV( parity[ ans ] );
		setH( false );
		setN( false );
		setC( c );

		return(ans);
	}

	/** SRL (Shift Right Logically), alters all flags */
	private final int srl( int ans ) {
		boolean c = (ans & 0x01) != 0;
		ans = ans >> 1;

		setS( (ans & F_S) != 0 );
		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setZ( (ans) == 0 );
		setPV( parity[ ans ] );
		setH( false );
		setN( false );
		setC( c );

		return(ans);
	}

	/** Decrement, alters all flags except C (carry)*/
	private final int dec8( int ans ) {
		boolean    pv = (ans == 0x80);
		boolean    h  = (((ans & 0x0f) - 1) & F_H) != 0;
		ans = (ans - 1) & 0xff;

		setS( (ans & F_S) != 0 );
		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setZ( (ans) == 0 );
		setPV( pv );
		setH( h );
		setN( true );

		return(ans);
	}

	/** Increment, alters all flags except C (carry) */
	private final int inc8( int ans ) {
		boolean    pv = (ans == 0x7f);
		boolean    h  = (((ans & 0x0f) + 1) & F_H) != 0;
		ans = (ans + 1) & 0xff;

		setS( (ans & F_S) != 0 );
		set3( (ans & F_3) != 0 );
		set5( (ans & F_5) != 0 );
		setZ( (ans) == 0 );
		setPV( pv );
		setH( h );
		setN( false );

		return(ans);
	}

	/** Suma con acarreo (no probado) */
	private final int adc16( int a, int b ) {
		int c    = Cset() ? 1 : 0;
		int lans = a + b + c;
		int ans  = lans & 0xffff;

		setS( (ans & (F_S<<8)) != 0 );
		set3( (ans & (F_3<<8)) != 0 );
		set5( (ans & (F_5<<8)) != 0 );
		setZ( (ans) == 0 );
		setC( (lans & 0x10000)!=0 );
		setPV( ((a ^ ~b) & (a ^ ans) & 0x8000)!=0 );
		setH( (((a & 0x0fff) + (b & 0x0fff) + c) & 0x1000)!=0 );
		setN( false );

		return(ans);
	}

	/** Add */
	private final int add16( int a, int b ) {
		int lans = a + b;
		int ans  = lans & 0xffff;

		set3( (ans & (F_3<<8)) != 0 );
		set5( (ans & (F_5<<8)) != 0 );
		setC( (lans & 0x10000)!=0 );
		setH( (((a & 0x0fff) + (b & 0x0fff)) & 0x1000)!=0 );
		setN( false );

		return(ans);
	}

	/** Add with carry */
	private final int sbc16( int a, int b ) {
		int c    = Cset() ? 1 : 0;
		int lans = a - b - c;
		int ans  = lans & 0xffff;

		setS( (ans & (F_S<<8)) != 0 );
		set3( (ans & (F_3<<8)) != 0 );
		set5( (ans & (F_5<<8)) != 0 );
		setZ( (ans) == 0 );
		setC( (lans & 0x10000)!=0 );
		setPV( ((a ^ b) & (a ^ ans) & 0x8000)!=0 );
		setH( (((a & 0x0fff) - (b & 0x0fff) - c) & 0x1000)!=0 );
		setN( true );

		return(ans);
	}

	/** EXX */
	public final void exx() {
		int t;

		t = HL();
		xHL( _HL_ );
		_HL_ = t;

		t = DE();
		xDE( _DE_ );
		_DE_ = t;

		t = BC();
		xBC( _BC_ );
		_BC_ = t;    
	}

	/** EX AF,AF' */
	public final void ex_af_af() {
		int   t;
		t = AF(); xAF( _AF_ ); _AF_ = t;
	}

	/** fast increment : doesn't alter flags */
	private static final int inc16( int a ) { return (a + 1) & 0xffff; }
	private static final int qinc8( int a ) { return (a + 1) & 0xff; }

	/** fast decrement: doesn't alter flags */
	private static final int dec16( int a ) { return (a - 1) & 0xffff; }
	private static final int qdec8( int a ) { return (a - 1) & 0xff; }

	/** Bit toggling */
	private static final int res( int bit, int val ) { return val & ~bit; }
	private static final int set( int bit, int val ) { return val |  bit; }


int       local_tstates;
int b, hl, haltsToInterrupt;
int t, sp;
byte d;


/** Z80 fetch/execute loop */
#pragma optimize=no_code_motion
  public final void execute() {
		local_tstates = -tstatesPerInterrupt;
                //int tmp;
		//while ( !mode ) {
		//if (  local_tstates>=0) {
		//	local_tstates -= (tstatesPerInterrupt - interrupt());
		//}
                do{
                while(local_tstates < 0){
                ++_R;
                //tmp=mem[_PC];
                //_PC=(_PC+1)&0xffff;
		//switch ( tmp ) {
                
                switch(mem[_PC++]){//(_PC=(_PC+1)&0xffff)-1]){

		case 0:    /* NOP */
		{
			local_tstates += ( 4 );
			break;
		}
		case 8:    /* EX AF,AF' */
		{
			ex_af_af();
			local_tstates += ( 4 );
			break;
		}
		case 16:    /* DJNZ dis */
		{
			// b;

			xB( b = qdec8( B() ) );
			if (b != 0) {
				d = (byte) nxtpcb();
				xPC( (PC()+d)&0xffff );
				local_tstates += ( 13 );
			}
			else {
				xPC( inc16( PC() ) );
				local_tstates += ( 8 );
			}
			break;
		}
		case 24: /* JR dis */
		{
			d = (byte)nxtpcb();
			xPC( (PC()+d)&0xffff );
			local_tstates += ( 12 );
			break;
		}
		/* JR cc,dis */
		case 32:    /* JR NZ,dis */
		{
			if (!Zset()) {
				d = (byte)nxtpcb();
				xPC( (PC()+d)&0xffff );
				local_tstates += ( 12 );
			}
			else {
				xPC( inc16( PC() ) );
				local_tstates += ( 7 );
			}
			break;
		}
		case 40:    /* JR Z,dis */
		{
			if ( Zset()) {
				d = (byte)nxtpcb();
				xPC( (PC()+d)&0xffff );
				local_tstates += ( 12 );
			}
			else {
				xPC( inc16( PC() ) );
				local_tstates += ( 7 );
			}
			break;
		}
		case 48:    /* JR NC,dis */
		{
			if (!Cset()) {
				d = (byte)nxtpcb();
				xPC( (PC()+d)&0xffff );
				local_tstates += ( 12 );
			}
			else {
				xPC( inc16( PC() ) );
				local_tstates += ( 7 );
			}
			break;
		}
		case 56:    /* JR C,dis */
		{
			if ( Cset()) {
				 d = (byte)nxtpcb();
				xPC( (PC()+d)&0xffff );
				local_tstates += ( 12 );
			}
			else {
				xPC( inc16( PC() ) );
				local_tstates += ( 7 );
			}
			break;
		}

		/* LD rr,nn / ADD HL,rr */
		case 1:    /* LD BC(),nn */
		{
			xBC( nxtpcw() );
			local_tstates += ( 10 );
			break;
		}
		case 9:    /* ADD HL,BC */
		{
			xHL( add16( HL(), BC() ) );
			local_tstates += ( 11 );
			break;
		}
		case 17:    /* LD DE,nn */
		{
			xDE( nxtpcw() );
			local_tstates += ( 10 );
			break;
		}
		case 25:    /* ADD HL,DE */
		{
			xHL( add16( HL(), DE() ) );
			local_tstates += ( 11 );
			break;
		}
		case 33:    /* LD HL,nn */
		{
			xHL( nxtpcw() );
			local_tstates += ( 10 );
			break;
		}
		case 41:    /* ADD HL,HL */
		{
			hl = HL();
			xHL( add16( hl, hl ) );
			local_tstates += ( 11 );
			break;
		}
		case 49:    /* LD SP,nn */
		{
			xSP( nxtpcw() );
			local_tstates += ( 10 );
			break;
		}
		case 57:    /* ADD HL,SP */
		{
			xHL( add16( HL(), SP() ) );
			local_tstates += ( 11 );
			break;
		}

		/* LD (**),A/A,(**) */
		case 2:    /* LD (BC),A */
		{ pokeb( BC(), A() ); local_tstates += ( 7 ); break; }
		case 10:    /* LD A,(BC) */
		{xA( peekb( BC() ) ); local_tstates += ( 7 ); break; }
		case 18:    /* LD (DE),A */
		{ pokeb( DE(), A() ); local_tstates += ( 7 ); break; }
		case 26:    /* LD A,(DE) */
		{ xA( peekb( DE() ) ); local_tstates += ( 7 ); break; }
		case 34:    /* LD (nn),HL */
		{ pokew( nxtpcw(), HL() ); local_tstates += ( 16 ); break; }
		case 42:    /* LD HL,(nn) */
		{ xHL( peekw( nxtpcw() ) ); local_tstates += ( 16 ); break; }
		case 50:    /* LD (nn),A */
		{ pokeb( nxtpcw(), A() ); local_tstates += ( 13 ); break; }
		case 58:    /* LD A,(nn) */
		{ xA( peekb( nxtpcw() ) ); local_tstates += ( 13 ); break; }

		/* INC/DEC * */
		case 3:    /* INC BC */
		{ xBC( inc16( BC() ) ); local_tstates += ( 6 ); break; }
		case 11:    /* DEC BC */
		{ xBC( dec16( BC() ) ); local_tstates += ( 6 ); break; }
		case 19:    /* INC DE */
		{ xDE( inc16( DE() ) ); local_tstates += ( 6 ); break; }
		case 27:    /* DEC DE */
		{ xDE( dec16( DE() ) ); local_tstates += ( 6 ); break; }
		case 35:    /* INC HL */
		{ xHL( inc16( HL() ) ); local_tstates += ( 6 ); break; }
		case 43:    /* DEC HL */
		{ xHL( dec16( HL() ) ); local_tstates += ( 6 ); break; }
		case 51:    /* INC SP */
		{ xSP( inc16( SP() ) ); local_tstates += ( 6 ); break; }
		case 59:    /* DEC SP */
		{ xSP( dec16( SP() ) ); local_tstates += ( 6 ); break; }

		/* INC * */
		case 4:    /* INC B */
		{ xB( inc8( B() ) ); local_tstates += ( 4 ); break; }
		case 12:    /* INC C */
		{ xC( inc8( C() ) ); local_tstates += ( 4 ); break; }
		case 20:    /* INC D */
		{ xD( inc8( D() ) ); local_tstates += ( 4 ); break; }
		case 28:    /* INC E */
		{ xE( inc8( E() ) ); local_tstates += ( 4 ); break; }
		case 36:    /* INC H */
		{ xH( inc8( H() ) ); local_tstates += ( 4 ); break; }
		case 44:    /* INC L */
		{ xL( inc8( L() ) ); local_tstates += ( 4 ); break; }
		case 52:    /* INC (HL) */
		{
			 hl = HL();
			pokeb( hl, inc8( peekb( hl ) ) );
			local_tstates += ( 11 );
			break;
		}
		case 60:    /* INC A() */
		{ xA( inc8( A() ) ); local_tstates += ( 4 ); break; }

		/* DEC * */
		case 5:    /* DEC B */
		{ xB( dec8( B() ) ); local_tstates += ( 4 ); break; }
		case 13:    /* DEC C */
		{ xC( dec8( C() ) ); local_tstates += ( 4 ); break; }
		case 21:    /* DEC D */
		{ xD( dec8( D() ) ); local_tstates += ( 4 ); break; }
		case 29:    /* DEC E */
		{ xE( dec8( E() ) ); local_tstates += ( 4 ); break; }
		case 37:    /* DEC H */
		{ xH( dec8( H() ) ); local_tstates += ( 4 ); break; }
		case 45:    /* DEC L */
		{ xL( dec8( L() ) ); local_tstates += ( 4 ); break; }
		case 53:    /* DEC (HL) */
		{
			 hl = HL();
			pokeb( hl, dec8( peekb( hl ) ) );
			local_tstates += ( 11 );
			break;
		}
		case 61:    /* DEC A() */
		{ xA( dec8( A() ) ); local_tstates += ( 4 ); break; }

		/* LD *,N */
		case 6:    /* LD B,n */
		{ xB( nxtpcb() ); local_tstates += ( 7 ); break; }
		case 14:    /* LD C,n */
		{ xC( nxtpcb() ); local_tstates += ( 7 ); break; }
		case 22:    /* LD D,n */
		{ xD( nxtpcb() ); local_tstates += ( 7 ); break; }
		case 30:    /* LD E,n */
		{ xE( nxtpcb() ); local_tstates += ( 7 ); break; }
		case 38:    /* LD H,n */
		{ xH( nxtpcb() ); local_tstates += ( 7 ); break; }
		case 46:    /* LD L,n */
		{ xL( nxtpcb() ); local_tstates += ( 7 ); break; }
		case 54:    /* LD (HL),n */
		{
			pokeb( HL(), nxtpcb() );
			local_tstates += ( 10 );
			break;
		}
		case 62:    /* LD A,n */
		{ xA( nxtpcb() ); local_tstates += ( 7 ); break; }

		/* R**A */
		case 7: /* RLCA */
		{ rlc_a(); local_tstates += ( 4 ); break; }
		case 15: /* RRCA */
		{ rrc_a(); local_tstates += ( 4 ); break; }
		case 23: /* RLA */
		{ rl_a(); local_tstates += ( 4 ); break; }
		case 31: /* RRA */
		{ rr_a(); local_tstates += ( 4 ); break; }
		case 39: /* DAA */
		{ daa_a(); local_tstates += ( 4 ); break; }
		case 47: /* CPL */
		{ cpl_a(); local_tstates += ( 4 ); break; }
		case 55: /* SCF */
		{ scf(); local_tstates += ( 4 ); break; }
		case 63: /* CCF */
		{ ccf(); local_tstates += ( 4 ); break; }

		/* LD B,* */
		case 64:    /* LD B,B */
		{ local_tstates += ( 4 ); break; }
		case 65:    /* LD B,C */
		{ xB( C() ); local_tstates += ( 4 ); break; }
		case 66:    /* LD B,D */
		{ xB( D() ); local_tstates += ( 4 ); break; }
		case 67:    /* LD B,E */
		{ xB( E() ); local_tstates += ( 4 ); break; }
		case 68:    /* LD B,H */
		{ xB( H() ); local_tstates += ( 4 ); break; }
		case 69:    /* LD B,L */
		{ xB( L() ); local_tstates += ( 4 ); break; }
		case 70:    /* LD B,(HL) */
		{ xB( peekb( HL() ) ); local_tstates += ( 7 ); break; }
		case 71:    /* LD B,A */
		{ xB( A() ); local_tstates += ( 4 ); break; }

		/* LD C,* */
		case 72:    /* LD C,B */
		{ xC( B() ); local_tstates += ( 4 ); break; }
		case 73:    /* LD C,C */
		{ local_tstates += ( 4 ); break; }
		case 74:    /* LD C,D */
		{ xC( D() ); local_tstates += ( 4 ); break; }
		case 75:    /* LD C,E */
		{ xC( E() ); local_tstates += ( 4 ); break; }
		case 76:    /* LD C,H */
		{ xC( H() ); local_tstates += ( 4 ); break; }
		case 77:    /* LD C,L */
		{ xC( L() ); local_tstates += ( 4 ); break; }
		case 78:    /* LD C,(HL) */
		{ xC( peekb( HL() ) ); local_tstates += ( 7 ); break; }
		case 79:    /* LD C,A */
		{ xC( A() ); local_tstates += ( 4 ); break; }

		/* LD D,* */
		case 80:    /* LD D,B */
		{ xD( B() ); local_tstates += ( 4 ); break; }
		case 81:    /* LD D,C */
		{ xD( C() ); local_tstates += ( 4 ); break; }
		case 82:    /* LD D,D */
		{ local_tstates += ( 4 ); break; }
		case 83:    /* LD D,E */
		{ xD( E() ); local_tstates += ( 4 ); break; }
		case 84:    /* LD D,H */
		{ xD( H() ); local_tstates += ( 4 ); break; }
		case 85:    /* LD D,L */
		{ xD( L() ); local_tstates += ( 4 ); break; }
		case 86:    /* LD D,(HL) */
		{ xD( peekb( HL() ) ); local_tstates += ( 7 ); break; }
		case 87:    /* LD D,A */
		{ xD( A() ); local_tstates += ( 4 ); break; }

		/* LD E,* */
		case 88:    /* LD E,B */
		{ xE( B() ); local_tstates += ( 4 ); break; }
		case 89:    /* LD E,C */
		{ xE( C() ); local_tstates += ( 4 ); break; }
		case 90:    /* LD E,D */
		{ xE( D() ); local_tstates += ( 4 ); break; }
		case 91:    /* LD E,E */
		{ local_tstates += ( 4 ); break; }
		case 92:    /* LD E,H */
		{ xE( H() ); local_tstates += ( 4 ); break; }
		case 93:    /* LD E,L */
		{ xE( L() ); local_tstates += ( 4 ); break; }
		case 94:    /* LD E,(HL) */
		{ xE( peekb( HL() ) ); local_tstates += ( 7 ); break; }
		case 95:    /* LD E,A */
		{ xE( A() ); local_tstates += ( 4 ); break; }

		/* LD H,* */
		case 96:    /* LD H,B */
		{ xH( B() ); local_tstates += ( 4 ); break; }
		case 97:    /* LD H,C */
		{ xH( C() ); local_tstates += ( 4 ); break; }
		case 98:    /* LD H,D */
		{ xH( D() ); local_tstates += ( 4 ); break; }
		case 99:    /* LD H,E */
		{ xH( E() ); local_tstates += ( 4 ); break; }
		case 100: /* LD H,H */
		{ local_tstates += ( 4 ); break; }
		case 101:    /* LD H,L */
		{ xH( L() ); local_tstates += ( 4 ); break; }
		case 102:    /* LD H,(HL) */
		{ xH( peekb( HL() ) ); local_tstates += ( 7 ); break; }
		case 103:    /* LD H,A */
		{ xH( A() ); local_tstates += ( 4 ); break; }

		/* LD L,* */
		case 104:    /* LD L,B */
		{ xL( B() ); local_tstates += ( 4 ); break; }
		case 105:    /* LD L,C */
		{ xL( C() ); local_tstates += ( 4 ); break; }
		case 106:    /* LD L,D */
		{ xL( D() ); local_tstates += ( 4 ); break; }
		case 107:    /* LD L,E */
		{ xL( E() ); local_tstates += ( 4 ); break; }
		case 108:    /* LD L,H */
		{ xL( H() ); local_tstates += ( 4 ); break; }
		case 109:    /* LD L,L */
		{ local_tstates += ( 4 ); break; }
		case 110:    /* LD L,(HL) */
		{ xL( peekb( HL() ) ); local_tstates += ( 7 ); break; }
		case 111:    /* LD L,A */
		{ xL( A() ); local_tstates += ( 4 ); break; }

		/* LD (HL),* */
		case 112:    /* LD (HL),B */
		{ pokeb( HL(), B() ); local_tstates += ( 7 ); break; }
		case 113:    /* LD (HL),C */
		{ pokeb( HL(), C() ); local_tstates += ( 7 ); break; }
		case 114:    /* LD (HL),D */
		{ pokeb( HL(), D() ); local_tstates += ( 7 ); break; }
		case 115:    /* LD (HL),E */
		{ pokeb( HL(), E() ); local_tstates += ( 7 ); break; }
		case 116:    /* LD (HL),H */
		{ pokeb( HL(), H() ); local_tstates += ( 7 ); break; }
		case 117:    /* LD (HL),L */
		{ pokeb( HL(), L() ); local_tstates += ( 7 ); break; }
		case 118:    /* HALT */
		{ 
			  haltsToInterrupt = (((-local_tstates-1) / 4)+1);
			local_tstates += (haltsToInterrupt*4);
			REFRESH( haltsToInterrupt-1 );
			break;
		}
		case 119:    /* LD (HL),A */
		{ pokeb( HL(), A() ); local_tstates += ( 7 ); break; }

		/* LD A,* */
		case 120:    /* LD A,B */
		{ xA( B() ); local_tstates += ( 4 ); break; }
		case 121:    /* LD A,C */
		{ xA( C() ); local_tstates += ( 4 ); break; }
		case 122:    /* LD A,D */
		{ xA( D() ); local_tstates += ( 4 ); break; }
		case 123:    /* LD A,E */
		{ xA( E() ); local_tstates += ( 4 ); break; }
		case 124:    /* LD A,H */
		{ xA( H() ); local_tstates += ( 4 ); break; }
		case 125:    /* LD A,L */
		{ xA( L() ); local_tstates += ( 4 ); break; }
		case 126:    /* LD A,(HL) */
		{ xA( peekb( HL() ) ); local_tstates += ( 7 ); break; }
		case 127:    /* LD A,A */
		{ local_tstates += ( 4 ); break; }

		/* ADD A,* */
		case 128:    /* ADD A,B */
		{ add_a( B() ); local_tstates += ( 4 ); break; }
		case 129:    /* ADD A,C */
		{ add_a( C() ); local_tstates += ( 4 ); break; }
		case 130:    /* ADD A,D */
		{ add_a( D() ); local_tstates += ( 4 ); break; }
		case 131:    /* ADD A,E */
		{ add_a( E() ); local_tstates += ( 4 ); break; }
		case 132:    /* ADD A,H */
		{ add_a( H() ); local_tstates += ( 4 ); break; }
		case 133:    /* ADD A,L */
		{ add_a( L() ); local_tstates += ( 4 ); break; }
		case 134:    /* ADD A,(HL) */
		{ add_a( peekb( HL() ) ); local_tstates += ( 7 ); break; }
		case 135:    /* ADD A,A */
		{ add_a( A() ); local_tstates += ( 4 ); break; }

		/* ADC A,* */
		case 136:    /* ADC A,B */
		{ adc_a( B() ); local_tstates += ( 4 ); break; }
		case 137:    /* ADC A,C */
		{ adc_a( C() ); local_tstates += ( 4 ); break; }
		case 138:    /* ADC A,D */
		{ adc_a( D() ); local_tstates += ( 4 ); break; }
		case 139:    /* ADC A,E */
		{ adc_a( E() ); local_tstates += ( 4 ); break; }
		case 140:    /* ADC A,H */
		{ adc_a( H() ); local_tstates += ( 4 ); break; }
		case 141:    /* ADC A,L */
		{ adc_a( L() ); local_tstates += ( 4 ); break; }
		case 142:    /* ADC A,(HL) */
		{ adc_a( peekb( HL() ) ); local_tstates += ( 7 ); break; }
		case 143:    /* ADC A,A */
		{ adc_a( A() ); local_tstates += ( 4 ); break; }

		/* SUB * */
		case 144:    /* SUB B */
		{ sub_a( B() ); local_tstates += ( 4 ); break; }
		case 145:    /* SUB C */
		{ sub_a( C() ); local_tstates += ( 4 ); break; }
		case 146:    /* SUB D */
		{ sub_a( D() ); local_tstates += ( 4 ); break; }
		case 147:    /* SUB E */
		{ sub_a( E() ); local_tstates += ( 4 ); break; }
		case 148:    /* SUB H */
		{ sub_a( H() ); local_tstates += ( 4 ); break; }
		case 149:    /* SUB L */
		{ sub_a( L() ); local_tstates += ( 4 ); break; }
		case 150:    /* SUB (HL) */
		{ sub_a( peekb( HL() ) ); local_tstates += ( 7 ); break; }
		case 151:    /* SUB A() */
		{ sub_a( A() ); local_tstates += ( 4 ); break; }

		/* SBC A,* */
		case 152:    /* SBC A,B */
		{ sbc_a( B() ); local_tstates += ( 4 ); break; }
		case 153:    /* SBC A,C */
		{ sbc_a( C() ); local_tstates += ( 4 ); break; }
		case 154:    /* SBC A,D */
		{ sbc_a( D() ); local_tstates += ( 4 ); break; }
		case 155:    /* SBC A,E */
		{ sbc_a( E() ); local_tstates += ( 4 ); break; }
		case 156:    /* SBC A,H */
		{ sbc_a( H() ); local_tstates += ( 4 ); break; }
		case 157:    /* SBC A,L */
		{ sbc_a( L() ); local_tstates += ( 4 ); break; }
		case 158:    /* SBC A,(HL) */
		{ sbc_a( peekb( HL() ) ); local_tstates += ( 7 ); break; }
		case 159:    /* SBC A,A */
		{ sbc_a( A() ); local_tstates += ( 4 ); break; }

		/* AND * */
		case 160:    /* AND B */
		{ and_a( B() ); local_tstates += ( 4 ); break; }
		case 161:    /* AND C */
		{ and_a( C() ); local_tstates += ( 4 ); break; }
		case 162:    /* AND D */
		{ and_a( D() ); local_tstates += ( 4 ); break; }
		case 163:    /* AND E */
		{ and_a( E() ); local_tstates += ( 4 ); break; }
		case 164:    /* AND H */
		{ and_a( H() ); local_tstates += ( 4 ); break; }
		case 165:    /* AND L */
		{ and_a( L() ); local_tstates += ( 4 ); break; }
		case 166:    /* AND (HL) */
		{ and_a( peekb( HL() ) ); local_tstates += ( 7 ); break; }
		case 167:    /* AND A() */
		{ and_a( A() ); local_tstates += ( 4 ); break; }

		/* XOR * */
		case 168:    /* XOR B */
		{ xor_a( B() ); local_tstates += ( 4 ); break; }
		case 169:    /* XOR C */
		{ xor_a( C() ); local_tstates += ( 4 ); break; }
		case 170:    /* XOR D */
		{ xor_a( D() ); local_tstates += ( 4 ); break; }
		case 171:    /* XOR E */
		{ xor_a( E() ); local_tstates += ( 4 ); break; }
		case 172:    /* XOR H */
		{ xor_a( H() ); local_tstates += ( 4 ); break; }
		case 173:    /* XOR L */
		{ xor_a( L() ); local_tstates += ( 4 ); break; }
		case 174:    /* XOR (HL) */
		{ xor_a( peekb( HL() ) ); local_tstates += ( 7 ); break; }
		case 175:    /* XOR A() */
		{ xor_a( A() ); local_tstates += ( 4 ); break; }

		/* OR * */
		case 176:    /* OR B */
		{ or_a( B() ); local_tstates += ( 4 ); break; }
		case 177:    /* OR C */
		{ or_a( C() ); local_tstates += ( 4 ); break; }
		case 178:    /* OR D */
		{ or_a( D() ); local_tstates += ( 4 ); break; }
		case 179:    /* OR E */
		{ or_a( E() ); local_tstates += ( 4 ); break; }
		case 180:    /* OR H */
		{ or_a( H() ); local_tstates += ( 4 ); break; }
		case 181:    /* OR L */
		{ or_a( L() ); local_tstates += ( 4 ); break; }
		case 182:    /* OR (HL) */
		{ or_a( peekb( HL() ) ); local_tstates += ( 7 ); break; }
		case 183:    /* OR A() */
		{ or_a( A() ); local_tstates += ( 4 ); break; }

		/* CP * */
		case 184:    /* CP B */
		{ cp_a( B() ); local_tstates += ( 4 ); break; }
		case 185:    /* CP C */
		{ cp_a( C() ); local_tstates += ( 4 ); break; }
		case 186:    /* CP D */
		{ cp_a( D() ); local_tstates += ( 4 ); break; }
		case 187:    /* CP E */
		{ cp_a( E() ); local_tstates += ( 4 ); break; }
		case 188:    /* CP H */
		{ cp_a( H() ); local_tstates += ( 4 ); break; }
		case 189:    /* CP L */
		{ cp_a( L() ); local_tstates += ( 4 ); break; }
		case 190:    /* CP (HL) */
		{ cp_a( peekb( HL() ) ); local_tstates += ( 7 ); break; }
		case 191:    /* CP A() */
		{ cp_a( A() ); local_tstates += ( 4 ); break; }

		/* RET cc */
		case 192:    /* RET NZ */
		{
			if(!Zset()) {
				poppc();
				local_tstates += ( 11 );
			}
			else {
				local_tstates += ( 5 );
			}
			break;
		}
		case 200:    /* RET Z */
		{
			if(Zset()) {
				poppc();
				local_tstates += ( 11 );
			}
			else {
				local_tstates += ( 5 );
			}
			break;
		}
		case 208:    /* RET NC */
		{
			if(!Cset()) {
				poppc();
				local_tstates += ( 11 );
			}
			else {
				local_tstates += ( 5 );
			}
			break;
		}
		case 216:    /* RET C */
		{
			if(Cset()) {
				poppc();
				local_tstates += ( 11 );
			}
			else {
				local_tstates += ( 5 );
			}
			break;
		}
		case 224:    /* RET PO */
		{
			if(!PVset()) {
				poppc();
				local_tstates += ( 11 );
			}
			else {
				local_tstates += ( 5 );
			}
			break;
		}
		case 232:    /* RET PE */
		{
			if(PVset()) {
				poppc();
				local_tstates += ( 11 );
			}
			else {
				local_tstates += ( 5 );
			}
			break;
		}
		case 240:    /* RET P */
		{
			if(!Sset()) {
				poppc();
				local_tstates += ( 11 );
			}
			else {
				local_tstates += ( 5 );
			}
			break;
		}
		case 248:    /* RET M */
		{
			if(Sset()) {
				poppc();
				local_tstates += ( 11 );
			}
			else {
				local_tstates += ( 5 );
			}
			break;
		}

		/* POP,Various */
		case 193:    /* POP BC */
		{ xBC( popw() ); local_tstates += ( 10 ); break; }
		case 201: /* RET */
		{ poppc(); local_tstates += ( 10 ); break; }
		case 209:    /* POP DE */
		{ xDE( popw() ); local_tstates += ( 10 ); break; }
		case 217:    /* EXX */
		{
			exx();
			local_tstates += ( 4 );
			break;
		}
		case 225:    /* POP HL */
		{ xHL( popw() ); local_tstates += ( 10 ); break; }
		case 233: /* JP (HL) */
		{ xPC( HL() ); local_tstates += ( 4 ); break; }
		case 241:    /* POP AF */
		{ xAF( popw() ); local_tstates += ( 10 ); break; }
		case 249:    /* LD SP,HL */
		{ xSP( HL() ); local_tstates += ( 6 ); break; }

		/* JP cc,nn */
		case 194:    /* JP NZ,nn */
		{
			if(!Zset()) {
				xPC( nxtpcw() );
			}
			else {
				xPC( (PC()+2)&0xffff );
			}
			local_tstates += ( 10 );
			break;
		}
		case 202:    /* JP Z,nn */
		{
			if( Zset()) {
				xPC( nxtpcw() );
			}
			else {
				xPC( (PC()+2)&0xffff );
			}
			local_tstates += ( 10 );
			break;
		}
		case 210:    /* JP NC,nn */
		{
			if(!Cset()) {
				xPC( nxtpcw() );
			}
			else {
				xPC( (PC()+2)&0xffff );
			}
			local_tstates += ( 10 );
			break;
		}
		case 218:    /* JP C,nn */
		{
			if( Cset()) {
				xPC( nxtpcw() );
			}
			else {
				xPC( (PC()+2)&0xffff );
			}
			local_tstates += ( 10 );
			break;
		}
		case 226:    /* JP PO,nn */
		{
			if(!PVset()) {
				xPC( nxtpcw() );
			}
			else {
				xPC( (PC()+2)&0xffff );
			}
			local_tstates += ( 10 );
			break;
		}
		case 234:    /* JP PE,nn */
		{
			if( PVset()) {
				xPC( nxtpcw() );
			}
			else {
				xPC( (PC()+2)&0xffff );
			}
			local_tstates += ( 10 );
			break;
		}
		case 242:    /* JP P,nn */
		{
			if(!Sset()) {
				xPC( nxtpcw() );
			}
			else {
				xPC( (PC()+2)&0xffff );
			}
			local_tstates += ( 10 );
			break;
		}
		case 250:    /* JP M,nn */
		{
			if( Sset()) {
				xPC( nxtpcw() );
			}
			else {
				xPC( (PC()+2)&0xffff );
			}
			local_tstates += ( 10 );
			break;
		}


		/* Various */
		case 195:    /* JP nn */
		{ xPC( peekw( PC() ) ); local_tstates += ( 10 ); break; }
		case 203:    /* prefix CB */
		{ local_tstates += execute_cb(); break; }
		case 211:    /* OUT (n),A */
		{
			outb( nxtpcb(), A(), local_tstates );
			local_tstates += ( 11 );
			break;
		}
		case 219:    /* IN A,(n) */
		{
			xA( inb((A() << 8) | nxtpcb()) );
			local_tstates += ( 11 );
			break;
		}
		case 227:    /* EX (SP),HL */
		{
			t = HL();
			sp = SP();
			xHL( peekw( sp ) );
			pokew( sp, t );
			local_tstates += ( 19 );
			break;
		}
		case 235:    /* EX DE,HL */
		{
			t = HL();
			xHL( DE() );
			xDE( t );
			local_tstates += ( 4 );
			break;
		}
		case 243:    /* DI */
		{
			xIFF1( false );
			xIFF2( false );
			local_tstates += ( 4 );
			break;
		}
		case 251:    /* EI */
		{
			xIFF1( true );
			xIFF2( true );
			local_tstates += ( 4 ); 
			break;
		}

		/* CALL cc,nn */
		case 196: /* CALL NZ,nn */
		{
			if( !Zset() ) {
				 t = nxtpcw();
				pushpc();
				xPC( t );
				local_tstates += ( 17 );
			}
			else {
				xPC( (PC() + 2)&0xffff );
				local_tstates += ( 10 );
			}
			break;
		}
		case 204: /* CALL Z,nn */
		{
			if( Zset() ) {
				 t = nxtpcw();
				pushpc();
				xPC( t );
				local_tstates += ( 17 );
			}
			else {
				xPC( (PC() + 2)&0xffff );
				local_tstates += ( 10 );
			}
			break;
		}
		case 212: /* CALL NC,nn */
		{
			if( !Cset() ) {
				 t = nxtpcw();
				pushpc();
				xPC( t );
				local_tstates += ( 17 );
			}
			else {
				xPC( (PC() + 2)&0xffff );
				local_tstates += ( 10 );
			}
			break;
		}
		case 220: /* CALL C,nn */
		{
			if( Cset() ) {
				 t = nxtpcw();
				pushpc();
				xPC( t );
				local_tstates += ( 17 );
			}
			else {
				xPC( (PC() + 2)&0xffff );
				local_tstates += ( 10 );
			}
			break;
		}
		case 228: /* CALL PO,nn */
		{
			if( !PVset() ) {
				 t = nxtpcw();
				pushpc();
				xPC( t );
				local_tstates += ( 17 );
			}
			else {
				xPC( (PC() + 2)&0xffff );
				local_tstates += ( 10 );
			}
			break;
		}
		case 236: /* CALL PE,nn */
		{
			if( PVset() ) {
				 t = nxtpcw();
				pushpc();
				xPC( t );
				local_tstates += ( 17 );
			}
			else {
				xPC( (PC() + 2)&0xffff );
				local_tstates += ( 10 );
			}
			break;
		}
		case 244: /* CALL P,nn */
		{
			if( !Sset() ) {
				 t = nxtpcw();
				pushpc();
				xPC( t );
				local_tstates += ( 17 );
			}
			else {
				xPC( (PC() + 2)&0xffff );
				local_tstates += ( 10 );
			}
			break;
		}
		case 252: /* CALL M,nn */
		{
			if( Sset() ) {
				 t = nxtpcw();
				pushpc();
				xPC( t );
				local_tstates += ( 17 );
			}
			else {
				xPC( (PC() + 2)&0xffff );
				local_tstates += ( 10 );
			}
			break;
		}

		/* PUSH y otros de ese tipo */
		case 197:    /* PUSH BC */
		{ pushw( BC() ); local_tstates += ( 11 ); break; }
		case 205:    /* CALL nn */
		{
			 t = nxtpcw();
			pushpc();
			xPC( t );
			local_tstates += ( 17 );
			break;
		}
		case 213:    /* PUSH DE */
		{ pushw( DE() ); local_tstates += ( 11 ); break; }
		case 221:    /* prefix IX */
		{
			xID( IX() );
			local_tstates += execute_id();
			xIX( ID() );
			break;
		}
		case 229:    /* PUSH HL */
		{ pushw( HL() ); local_tstates += ( 11 ); break; }
		case 237:    /* prefix ED */
		{ local_tstates += execute_ed( local_tstates ); break; }
		case 245:    /* PUSH AF */
		{ pushw( AF() ); local_tstates += ( 11 ); break; }
		case 253:    /* prefix IY */
		{
			xID( IY() );
			local_tstates += execute_id();
			xIY( ID() );
			break;
		}

		/* op A,N */
		case 198: /* ADD A,N */
		{ add_a(nxtpcb()); local_tstates += ( 7 ); break; }
		case 206: /* ADC A,N */
		{ adc_a(nxtpcb()); local_tstates += ( 7 ); break; }
		case 214: /* SUB N */
		{ sub_a(nxtpcb()); local_tstates += ( 7 ); break; }
		case 222: /* SBC A,N */
		{ sbc_a(nxtpcb()); local_tstates += ( 7 ); break; }
		case 230: /* AND N */
		{ and_a(nxtpcb()); local_tstates += ( 7 ); break; }
		case 238: /* XOR N */
		{ xor_a(nxtpcb()); local_tstates += ( 7 ); break; }
		case 246: /* OR N */
		{ or_a(nxtpcb()); local_tstates += ( 7 ); break; }
		case 254: /* CP N */
		{ cp_a(nxtpcb()); local_tstates += ( 7 ); break; }

		/* RST n */
		case 199:    /* RST 0 */
		{ pushpc(); xPC( 0 ); local_tstates += ( 11 ); break; }
		case 207:    /* RST 8 */
		{ pushpc(); xPC( 8 ); local_tstates += ( 11 ); break; }
		case 215:    /* RST 16 */
		{ pushpc(); xPC( 16 ); local_tstates += ( 11 ); break; }
		case 223:    /* RST 24 */
		{ pushpc(); xPC( 24 ); local_tstates += ( 11 ); break; }
		case 231:    /* RST 32 */
		{ pushpc(); xPC( 32 ); local_tstates += ( 11 ); break; }
		case 239:    /* RST 40 */
		{ pushpc(); xPC( 40 ); local_tstates += ( 11 ); break; }
		case 247:    /* RST 48 */
		{ pushpc(); xPC( 48 ); local_tstates += ( 11 ); break; }
		case 255:    /* RST 56 */
		{ pushpc(); xPC( 56 ); local_tstates += ( 11 ); break; }

		}

		} // main while end
		local_tstates -= (tstatesPerInterrupt - interrupt());

                }while(!mode);
	}

#pragma optimize=no_code_motion
	private final int execute_ed( int local_tstates ) {

		REFRESH( 1 );

		switch ( nxtpcb() ) {

		case 0:  /* NOP */
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
		case 30:
		case 31:
		case 32:
		case 33:
		case 34:
		case 35:
		case 36:
		case 37:
		case 38:
		case 39:
		case 40:
		case 41:
		case 42:
		case 43:
		case 44:
		case 45:
		case 46:
		case 47:
		case 48:
		case 49:
		case 50:
		case 51:
		case 52:
		case 53:
		case 54:
		case 55:
		case 56:
		case 57:
		case 58:
		case 59:
		case 60:
		case 61:
		case 62:
		case 63:

		case 127:
		case 128:
		case 129:
		case 130:
		case 131:
		case 132:
		case 133:
		case 134:
		case 135:
		case 136:
		case 137:
		case 138:
		case 139:
		case 140:
		case 141:
		case 142:
		case 143:
		case 144:
		case 145:
		case 146:
		case 147:
		case 148:
		case 149:
		case 150:
		case 151:
		case 152:
		case 153:
		case 154:
		case 155:
		case 156:
		case 157:
		case 158:
		case 159:

		case 164:
		case 165:
		case 166:
		case 167:

		case 172:
		case 173:
		case 174:
		case 175:

		case 180:
		case 181:
		case 182:
		case 183:
		{
			return ( 8 );
		}

		/* IN r,(c) */
		case 64:  /* IN B,(c) */
		{ xB( in_bc() ); return ( 12 ); }
		case 72:  /* IN C,(c) */
		{ xC( in_bc() ); return ( 12 ); }
		case 80:  /* IN D,(c) */
		{ xD( in_bc() ); return ( 12 ); }
		case 88:  /* IN E,(c) */
		{ xE( in_bc() ); return ( 12 ); }
		case 96:  /* IN H,(c) */
		{ xH( in_bc() ); return ( 12 ); }
		case 104:  /* IN L,(c) */
		{ xL( in_bc() ); return ( 12 ); }
		case 112:  /* IN (c) */
		{ in_bc(); return ( 12 ); }
		case 120:  /* IN A,(c) */
		{ xA( in_bc() ); return ( 12 ); }

		/* OUT (c),r */
		case 65:  /* OUT (c),B */
		{ outb( BC(), B(), local_tstates ); return ( 12 ); }
		case 73:  /* OUT (c),C */
		{ outb( BC(), C(), local_tstates ); return ( 12 ); }
		case 81:  /* OUT (c),D */
		{ outb( BC(), D(), local_tstates ); return ( 12 ); }
		case 89:  /* OUT (c),E */
		{ outb( BC(), E(), local_tstates ); return ( 12 ); }
		case 97:  /* OUT (c),H */
		{ outb( BC(), H(), local_tstates ); return ( 12 ); }
		case 105:  /* OUT (c),L */
		{ outb( BC(), L(), local_tstates ); return ( 12 ); }
		case 113:  /* OUT (c),0 */
		{ outb( BC(), 0, local_tstates ); return ( 12 ); }
		case 121:  /* OUT (c),A */
		{ outb( BC(), A(), local_tstates ); return ( 12 ); }

		/* SBC/ADC HL,ss */
		case 66:  /* SBC HL,BC */
		{ xHL( sbc16( HL(), BC() ) ); return ( 15 ); }
		case 74:  /* ADC HL,BC */
		{ xHL( adc16( HL(), BC() ) ); return ( 15 ); }
		case 82:  /* SBC HL,DE */
		{ xHL( sbc16( HL(), DE() ) ); return ( 15 ); }
		case 90:  /* ADC HL,DE */
		{ xHL( adc16( HL(), DE() ) ); return ( 15 ); }
		case 98:  /* SBC HL,HL */
		{
			int hl = HL();
			xHL( sbc16( hl, hl ) );
			return ( 15 );
		}
		case 106:  /* ADC HL,HL */
		{
			int hl = HL();
			xHL( adc16( hl, hl ) );
			return ( 15 );
		}
		case 114:  /* SBC HL,SP */
		{ xHL( sbc16( HL(), SP() ) ); return ( 15 ); }
		case 122:  /* ADC HL,SP */
		{ xHL( adc16( HL(), SP() ) ); return ( 15 ); }

		/* LD (nn),ss, LD ss,(nn) */
		case 67:  /* LD (nn),BC */
		{ pokew( nxtpcw(), BC() ); return ( 20 ); }
		case 75:  /* LD BC(),(nn) */
		{ xBC( peekw( nxtpcw() ) ); return ( 20 ); }
		case 83:  /* LD (nn),DE */
		{ pokew( nxtpcw(), DE() ); return ( 20 ); }
		case 91:  /* LD DE,(nn) */
		{ xDE( peekw( nxtpcw() ) ); return ( 20 ); }
		case 99:  /* LD (nn),HL */
		{ pokew( nxtpcw(), HL() ); return ( 20 ); }
		case 107:  /* LD HL,(nn) */
		{ xHL( peekw( nxtpcw() ) ); return ( 20 ); }
		case 115:  /* LD (nn),SP */
		{ pokew( nxtpcw(), SP() ); return ( 20 ); }
		case 123:  /* LD SP,(nn) */
		{ xSP( peekw( nxtpcw() ) ); return ( 20 ); }

		/* NEG */
		case 68:  /* NEG */
		case 76:  /* NEG */
		case 84:  /* NEG */
		case 92:  /* NEG */
		case 100:  /* NEG */
		case 108:  /* NEG */
		case 116:  /* NEG */
		case 124:  /* NEG */
		{ neg_a(); return ( 8 ); }

		/* RETn */
		case 69:  /* RETN */
		case 85:  /* RETN */
		case 101:  /* RETN */
		case 117:  /* RETN */
		{
			xIFF1( IFF2() );
			poppc();
			return ( 14 );
		}
		case 77:  /* RETI */
		case 93:  /* RETI */
		case 109:  /* RETI */
		case 125:  /* RETI */
		{
			poppc();
			return ( 14 );
		}

		/* IM x */
		case 70:  /* IM 0 */
		case 78:  /* IM 0 */
		case 102:  /* IM 0 */
		case 110:  /* IM 0 */
		{ xIM( IM0 ); return ( 8 ); }
		case 86:  /* IM 1 */
		case 118:  /* IM 1 */
		{ xIM( IM1 ); return ( 8 ); }
		case 94:  /* IM 2 */
		case 126:  /* IM 2 */
		{ xIM( IM2 ); return ( 8 ); }

		/* LD A,s / LD s,A / RxD */
		case 71:  /* LD I,A */
		{ xI( A() ); return ( 9 ); }
		case 79:  /* LD R,A */
		{ xR( A() ); return ( 9 ); }
		case 87:  /* LD A,I */
		{ ld_a_i(); return ( 9 ); }
		case 95:  /* LD A,R */
		{ ld_a_r(); return ( 9 ); }
		case 103:  /* RRD */
		{ rrd_a(); return ( 18 ); }
		case 111:  /* RLD */
		{ rld_a(); return ( 18 ); }

		/* xxI */
		case 160:  /* LDI */
		{
			pokeb( DE(), peekb( HL() ) );
			xDE( inc16( DE() ) );
			xHL( inc16( HL() ) );
			xBC( dec16( BC() ) );

			setPV( BC() != 0 );
			setH( false );
			setN( false );

			return ( 16 );
		}
		case 161:  /* CPI */
		{
			boolean    c = Cset();

			cp_a( peekb( HL() ) );
			xHL( inc16( HL() ) );
			xBC( dec16( BC() ) );

			setPV( BC() != 0 );
			setC( c );

			return ( 16 );
		}
		case 162:  /* INI */
		{
			int b;
			pokeb( HL(), inb( BC() ) );
			xB( b = qdec8( B() ) );
			xHL( inc16( HL() ) );

			setZ( b == 0 );
			setN( true );

			return ( 16 );
		}
		case 163:  /* OUTI */
		{
			int b;
			xB( b = qdec8( B() ) );
			outb( BC(), peekb( HL() ), local_tstates );
			xHL( inc16( HL() ) );

			setZ( b == 0 );
			setN( true );

			return ( 16 );
		}

		/* xxD */
		case 168:  /* LDD */
		{
			pokeb( DE(), peekb( HL() ) );
			xDE( dec16( DE() ) );
			xHL( dec16( HL() ) );
			xBC( dec16( BC() ) );

			setPV( BC() != 0 );
			setH( false );
			setN( false );

			return ( 16 );
		}
		case 169:  /* CPD */
		{
			boolean    c = Cset();

			cp_a( peekb( HL() ) );
			xHL( dec16( HL() ) );
			xBC( dec16( BC() ) );

			setPV( BC() != 0 );
			setC( c );

			return ( 16 );
		}
		case 170:  /* IND */
		{
			int b;
			pokeb( HL(), inb( BC() ) );
			xB( b = qdec8( B() ) );
			xHL( dec16( HL() ) );

			setZ( b == 0 );
			setN( true );

			return ( 16 );
		}
		case 171:  /* OUTD */
		{
			int b;
			xB( b = qdec8( B() ) );
			outb( BC(), peekb( HL() ), local_tstates );
			xHL( dec16( HL() ) );

			setZ( b == 0 );
			setN( true );

			return ( 16 );
		}

		/* xxIR */
		case 176:  /* LDIR */
		{
#ifdef useasm
                  if(temp=BC()){
                    ldirr(mem+DE(),mem+HL(),temp);
			xDE( (DE()+temp)&0xffff );
			xHL( (_HL+temp)&0xffff );
			xBC( 0 );
			setH( false );
			setN( false );
			setPV( false );
                    REFRESH(temp<<1);
                  }
                  return 21*temp;
#else
                  int _local_tstates = 0;
			int count, dest, from;

			count = BC();
			dest = DE();
			from = HL();
			REFRESH( -2 );
			do {
				pokeb(dest, peekb(from) );
				from  = inc16( from );
				dest  = inc16( dest );
				count = dec16( count );

				_local_tstates += ( 21 );
				REFRESH( 2 );
				if ( interruptTriggered( _local_tstates ) ) {
					break;
				}
			} while (count != 0);
			if (count != 0) {
				xPC( (PC()-2)&0xffff );
				setH( false );
				setN( false );
				setPV( true );
			}
			else {
				_local_tstates += ( -5 );
				setH( false );
				setN( false );
				setPV( false );
			}
			xDE( dest );
			xHL( from );
			xBC( count );

			return ( _local_tstates );
#endif
		}
		case 177:  /* CPIR */
		{
			boolean    c = Cset();

			cp_a( peekb( HL() ) );
			xHL( inc16( HL() ) );
			xBC( dec16( BC() ) );

			boolean    pv = (BC() != 0);

			setPV( pv );
			setC( c );
			if ( pv && !Zset() ) {
				xPC( (PC()-2)&0xffff );
				return ( 21 );
			}
			return ( 16 );
		}
		case 178:  /* INIR */
		{
			int b;
			pokeb( HL(), inb( BC() ) );
			xB( b = qdec8( B() ) );
			xHL( inc16( HL() ) );

			setZ( true );
			setN( true );
			if (b != 0) {
				xPC( (PC()-2)&0xffff );
				return ( 21 );
			}
			return ( 16 );
		}
		case 179:  /* OTIR */
		{
			int b;
			xB( b = qdec8( B() ) );
			outb( BC(), peekb( HL() ), local_tstates );
			xHL( inc16( HL() ) );

			setZ( true );
			setN( true );
			if (b != 0) {
				xPC( (PC()-2)&0xffff );
				return ( 21 );
			}
			return ( 16 );
		}

		/* xxDR */
		case 184:  /* LDDR */
		{
#ifdef useasm
                  if(temp=BC()){
                    lddrr(mem+DE(),mem+HL(),temp);
			xDE( (DE()-temp)&0xffff );
			xHL( (_HL-temp)&0xffff );
			xBC( 0 );
			setH( false );
			setN( false );
			setPV( false );
                    REFRESH(temp<<1);
                  }
                  return 21*temp;
#else
			int _local_tstates = 0;
			int count, dest, from;

			count = BC();
			dest = DE();
			from = HL();
			REFRESH ( -2 );
			do {
				pokeb(dest, peekb(from));
				from  = dec16( from );
				dest  = dec16( dest );
				count = dec16( count );

				_local_tstates += ( 21 );
				REFRESH( 2 );
				if ( interruptTriggered( _local_tstates ) ) {
					break;
				}
			} while (count != 0);
			if (count != 0) {
				xPC( (PC()-2)&0xffff );
				setH( false );
				setN( false );
				setPV( true );
			}
			else {
				_local_tstates += ( -5 );
				setH( false );
				setN( false );
				setPV( false );
			}
			xDE( dest );
			xHL( from );
			xBC( count );

			return ( _local_tstates );
#endif
		}
		case 185:  /* CPDR */
		{
			boolean    c = Cset();

			cp_a( peekb( HL() ) );
			xHL( dec16( HL() ) );
			xBC( dec16( BC() ) );

			boolean    pv = (BC() != 0);

			setPV( pv );
			setC( c );
			if ( pv && !Zset() ) {
				xPC( (PC()-2)&0xffff );
				return ( 21 );
			}
			return ( 16 );
		}
		case 186:  /* INDR */
		{
			int b;
			pokeb( HL(), inb( BC() ) );
			xB( b = qdec8( B() ) );
			xHL( dec16( HL() ) );

			setZ( true );
			setN( true );
			if (b != 0) {
				xPC( (PC()-2)&0xffff );
				return ( 21 );
			}
			return ( 16 );
		}
		case 187:  /* OTDR */
		{
			int b;
			xB( b = qdec8( B() ) );
			outb( BC(), peekb( HL() ), local_tstates );
			xHL( dec16( HL() ) );

			setZ( true );
			setN( true );
			if (b != 0) {
				xPC( (PC()-2)&0xffff );
				return ( 21 );
			}
			return ( 16 );
		}

		} // swith end

		// NOP
		return ( 8 );
	}
#pragma optimize=no_code_motion
	private final int execute_cb() {
		REFRESH( 1 );

		switch ( nxtpcb() ) {

		case   0:	/* RLC B */
		{ xB( rlc( B() ) ); return ( 8 ); }
		case   1:	/* RLC C */
		{ xC( rlc( C() ) ); return ( 8 ); }
		case   2:	/* RLC D */
		{ xD( rlc( D() ) ); return ( 8 ); }
		case   3:	/* RLC E */
		{ xE( rlc( E() ) ); return ( 8 ); }
		case   4:	/* RLC H */
		{ xH( rlc( H() ) ); return ( 8 ); }
		case   5:	/* RLC L */
		{ xL( rlc( L() ) ); return ( 8 ); }
		case   6:	/* RLC (HL) */
		{
			int hl = HL();
			pokeb( hl, rlc( peekb( hl ) ) );
			return ( 15 );
		}
		case   7:	/* RLC A */
		{ xA( rlc( A() ) ); return ( 8 ); }

		case   8:	/* RRC B */
		{ xB( rrc( B() ) ); return ( 8 ); }
		case   9:	/* RRC C */
		{ xC( rrc( C() ) ); return ( 8 ); }
		case  10:	/* RRC D */
		{ xD( rrc( D() ) ); return ( 8 ); }
		case  11:	/* RRC E */
		{ xE( rrc( E() ) ); return ( 8 ); }
		case  12:	/* RRC H */
		{ xH( rrc( H() ) ); return ( 8 ); }
		case  13:	/* RRC L */
		{ xL( rrc( L() ) ); return ( 8 ); }
		case  14:	/* RRC (HL) */
		{
			int hl = HL();
			pokeb( hl, rrc( peekb( hl ) ) );
			return ( 15 );
		}
		case  15:	/* RRC A */
		{ xA( rrc( A() ) ); return ( 8 ); }

		case  16:	/* RL B */
		{ xB( rl( B() ) ); return ( 8 ); }
		case  17:	/* RL C */
		{ xC( rl( C() ) ); return ( 8 ); }
		case  18:	/* RL D */
		{ xD( rl( D() ) ); return ( 8 ); }
		case  19:	/* RL E */
		{ xE( rl( E() ) ); return ( 8 ); }
		case  20:	/* RL H */
		{ xH( rl( H() ) ); return ( 8 ); }
		case  21:	/* RL L */
		{ xL( rl( L() ) ); return ( 8 ); }
		case  22:	/* RL (HL) */
		{
			int hl = HL();
			pokeb( hl, rl( peekb( hl ) ) );
			return ( 15 );
		}
		case  23:	/* RL A */
		{ xA( rl( A() ) ); return ( 8 ); }

		case  24:	/* RR B */
		{ xB( rr( B() ) ); return ( 8 ); }
		case  25:	/* RR C */
		{ xC( rr( C() ) ); return ( 8 ); }
		case  26:	/* RR D */
		{ xD( rr( D() ) ); return ( 8 ); }
		case  27:	/* RR E */
		{ xE( rr( E() ) ); return ( 8 ); }
		case  28:	/* RR H */
		{ xH( rr( H() ) ); return ( 8 ); }
		case  29:	/* RR L */
		{ xL( rr( L() ) ); return ( 8 ); }
		case  30:	/* RR (HL) */
		{
			int hl = HL();
			pokeb( hl, rr( peekb( hl ) ) );
			return ( 15 );
		}
		case  31:	/* RR A */
		{ xA( rr( A() ) ); return ( 8 ); }

		case  32:	/* SLA B */
		{ xB( sla( B() ) ); return ( 8 ); }
		case  33:	/* SLA C */
		{ xC( sla( C() ) ); return ( 8 ); }
		case  34:	/* SLA D */
		{ xD( sla( D() ) ); return ( 8 ); }
		case  35:	/* SLA E */
		{ xE( sla( E() ) ); return ( 8 ); }
		case  36:	/* SLA H */
		{ xH( sla( H() ) ); return ( 8 ); }
		case  37:	/* SLA L */
		{ xL( sla( L() ) ); return ( 8 ); }
		case  38:	/* SLA (HL) */
		{
			int hl = HL();
			pokeb( hl, sla( peekb( hl ) ) );
			return ( 15 );
		}
		case  39:	/* SLA A */
		{ xA( sla( A() ) ); return ( 8 ); }

		case  40:	/* SRA B */
		{ xB( sra( B() ) ); return ( 8 ); }
		case  41:	/* SRA C */
		{ xC( sra( C() ) ); return ( 8 ); }
		case  42:	/* SRA D */
		{ xD( sra( D() ) ); return ( 8 ); }
		case  43:	/* SRA E */
		{ xE( sra( E() ) ); return ( 8 ); }
		case  44:	/* SRA H */
		{ xH( sra( H() ) ); return ( 8 ); }
		case  45:	/* SRA L */
		{ xL( sra( L() ) ); return ( 8 ); }
		case  46:	/* SRA (HL) */
		{
			int hl = HL();
			pokeb( hl, sra( peekb( hl ) ) );
			return ( 15 );
		}
		case  47:	/* SRA A */
		{ xA( sra( A() ) ); return ( 8 ); }

		case  48:	/* SLS B */
		{ xB( sls( B() ) ); return ( 8 ); }
		case  49:	/* SLS C */
		{ xC( sls( C() ) ); return ( 8 ); }
		case  50:	/* SLS D */
		{ xD( sls( D() ) ); return ( 8 ); }
		case  51:	/* SLS E */
		{ xE( sls( E() ) ); return ( 8 ); }
		case  52:	/* SLS H */
		{ xH( sls( H() ) ); return ( 8 ); }
		case  53:	/* SLS L */
		{ xL( sls( L() ) ); return ( 8 ); }
		case  54:	/* SLS (HL) */
		{
			int hl = HL();
			pokeb( hl, sls( peekb( hl ) ) );
			return ( 15 );
		}
		case  55:	/* SLS A */
		{ xA( sls( A() ) ); return ( 8 ); }

		case  56:	/* SRL B */
		{ xB( srl( B() ) ); return ( 8 ); }
		case  57:	/* SRL C */
		{ xC( srl( C() ) ); return ( 8 ); }
		case  58:	/* SRL D */
		{ xD( srl( D() ) ); return ( 8 ); }
		case  59:	/* SRL E */
		{ xE( srl( E() ) ); return ( 8 ); }
		case  60:	/* SRL H */
		{ xH( srl( H() ) ); return ( 8 ); }
		case  61:	/* SRL L */
		{ xL( srl( L() ) ); return ( 8 ); }
		case  62:	/* SRL (HL) */
		{
			int hl = HL();
			pokeb( hl, srl( peekb( hl ) ) );
			return ( 15 );
		}
		case  63:	/* SRL A */
		{ xA( srl( A() ) ); return ( 8 ); }

		case  64:	/* BIT 0,B */
		{ bit( 0x01, B() ); return ( 8 ); }
		case  65:	/* BIT 0,C */
		{ bit( 0x01, C() ); return ( 8 ); }
		case  66:	/* BIT 0,D */
		{ bit( 0x01, D() ); return ( 8 ); }
		case  67:	/* BIT 0,E */
		{ bit( 0x01, E() ); return ( 8 ); }
		case  68:	/* BIT 0,H */
		{ bit( 0x01, H() ); return ( 8 ); }
		case  69:	/* BIT 0,L */
		{ bit( 0x01, L() ); return ( 8 ); }
		case  70:	/* BIT 0,(HL) */
		{ bit( 0x01, peekb( HL() ) ); return ( 12 ); }
		case  71:	/* BIT 0,A */
		{ bit( 0x01, A() ); return ( 8 ); }

		case  72:	/* BIT 1,B */
		{ bit( 0x02, B() ); return ( 8 ); }
		case  73:	/* BIT 1,C */
		{ bit( 0x02, C() ); return ( 8 ); }
		case  74:	/* BIT 1,D */
		{ bit( 0x02, D() ); return ( 8 ); }
		case  75:	/* BIT 1,E */
		{ bit( 0x02, E() ); return ( 8 ); }
		case  76:	/* BIT 1,H */
		{ bit( 0x02, H() ); return ( 8 ); }
		case  77:	/* BIT 1,L */
		{ bit( 0x02, L() ); return ( 8 ); }
		case  78:	/* BIT 1,(HL) */
		{ bit( 0x02, peekb( HL() ) ); return ( 12 ); }
		case  79:	/* BIT 1,A */
		{ bit( 0x02, A() ); return ( 8 ); }

		case  80:	/* BIT 2,B */
		{ bit( 0x04, B() ); return ( 8 ); }
		case  81:	/* BIT 2,C */
		{ bit( 0x04, C() ); return ( 8 ); }
		case  82:	/* BIT 2,D */
		{ bit( 0x04, D() ); return ( 8 ); }
		case  83:	/* BIT 2,E */
		{ bit( 0x04, E() ); return ( 8 ); }
		case  84:	/* BIT 2,H */
		{ bit( 0x04, H() ); return ( 8 ); }
		case  85:	/* BIT 2,L */
		{ bit( 0x04, L() ); return ( 8 ); }
		case  86:	/* BIT 2,(HL) */
		{ bit( 0x04, peekb( HL() ) ); return ( 12 ); }
		case  87:	/* BIT 2,A */
		{ bit( 0x04, A() ); return ( 8 ); }

		case  88:	/* BIT 3,B */
		{ bit( 0x08, B() ); return ( 8 ); }
		case  89:	/* BIT 3,C */
		{ bit( 0x08, C() ); return ( 8 ); }
		case  90:	/* BIT 3,D */
		{ bit( 0x08, D() ); return ( 8 ); }
		case  91:	/* BIT 3,E */
		{ bit( 0x08, E() ); return ( 8 ); }
		case  92:	/* BIT 3,H */
		{ bit( 0x08, H() ); return ( 8 ); }
		case  93:	/* BIT 3,L */
		{ bit( 0x08, L() ); return ( 8 ); }
		case  94:	/* BIT 3,(HL) */
		{ bit( 0x08, peekb( HL() ) ); return ( 12 ); }
		case  95:	/* BIT 3,A */
		{ bit( 0x08, A() ); return ( 8 ); }

		case  96:	/* BIT 4,B */
		{ bit( 0x10, B() ); return ( 8 ); }
		case  97:	/* BIT 4,C */
		{ bit( 0x10, C() ); return ( 8 ); }
		case  98:	/* BIT 4,D */
		{ bit( 0x10, D() ); return ( 8 ); }
		case  99:	/* BIT 4,E */
		{ bit( 0x10, E() ); return ( 8 ); }
		case 100:	/* BIT 4,H */
		{ bit( 0x10, H() ); return ( 8 ); }
		case 101:	/* BIT 4,L */
		{ bit( 0x10, L() ); return ( 8 ); }
		case 102:	/* BIT 4,(HL) */
		{ bit( 0x10, peekb( HL() ) ); return ( 12 ); }
		case 103:	/* BIT 4,A */
		{ bit( 0x10, A() ); return ( 8 ); }

		case 104:	/* BIT 5,B */
		{ bit( 0x20, B() ); return ( 8 ); }
		case 105:	/* BIT 5,C */
		{ bit( 0x20, C() ); return ( 8 ); }
		case 106:	/* BIT 5,D */
		{ bit( 0x20, D() ); return ( 8 ); }
		case 107:	/* BIT 5,E */
		{ bit( 0x20, E() ); return ( 8 ); }
		case 108:	/* BIT 5,H */
		{ bit( 0x20, H() ); return ( 8 ); }
		case 109:	/* BIT 5,L */
		{ bit( 0x20, L() ); return ( 8 ); }
		case 110:	/* BIT 5,(HL) */
		{ bit( 0x20, peekb( HL() ) ); return ( 12 ); }
		case 111:	/* BIT 5,A */
		{ bit( 0x20, A() ); return ( 8 ); }

		case 112:	/* BIT 6,B */
		{ bit( 0x40, B() ); return ( 8 ); }
		case 113:	/* BIT 6,C */
		{ bit( 0x40, C() ); return ( 8 ); }
		case 114:	/* BIT 6,D */
		{ bit( 0x40, D() ); return ( 8 ); }
		case 115:	/* BIT 6,E */
		{ bit( 0x40, E() ); return ( 8 ); }
		case 116:	/* BIT 6,H */
		{ bit( 0x40, H() ); return ( 8 ); }
		case 117:	/* BIT 6,L */
		{ bit( 0x40, L() ); return ( 8 ); }
		case 118:	/* BIT 6,(HL) */
		{ bit( 0x40, peekb( HL() ) ); return ( 12 ); }
		case 119:	/* BIT 6,A */
		{ bit( 0x40, A() ); return ( 8 ); }

		case 120:	/* BIT 7,B */
		{ bit( 0x80, B() ); return ( 8 ); }
		case 121:	/* BIT 7,C */
		{ bit( 0x80, C() ); return ( 8 ); }
		case 122:	/* BIT 7,D */
		{ bit( 0x80, D() ); return ( 8 ); }
		case 123:	/* BIT 7,E */
		{ bit( 0x80, E() ); return ( 8 ); }
		case 124:	/* BIT 7,H */
		{ bit( 0x80, H() ); return ( 8 ); }
		case 125:	/* BIT 7,L */
		{ bit( 0x80, L() ); return ( 8 ); }
		case 126:	/* BIT 7,(HL) */
		{ bit( 0x80, peekb( HL() ) ); return ( 12 ); }
		case 127:	/* BIT 7,A */
		{ bit( 0x80, A() ); return ( 8 ); }

		case 128:	/* RES 0,B */
		{ xB( res( 0x01, B() ) ); return ( 8 ); }
		case 129:	/* RES 0,C */
		{ xC( res( 0x01, C() ) ); return ( 8 ); }
		case 130:	/* RES 0,D */
		{ xD( res( 0x01, D() ) ); return ( 8 ); }
		case 131:	/* RES 0,E */
		{ xE( res( 0x01, E() ) ); return ( 8 ); }
		case 132:	/* RES 0,H */
		{ xH( res( 0x01, H() ) ); return ( 8 ); }
		case 133:	/* RES 0,L */
		{ xL( res( 0x01, L() ) ); return ( 8 ); }
		case 134:	/* RES 0,(HL) */
		{
			int hl = HL();
			pokeb( hl, res( 0x01, peekb( hl ) ) );
			return ( 15 );
		}
		case 135:	/* RES 0,A */
		{ xA( res( 0x01, A() ) ); return ( 8 ); }

		case 136:	/* RES 1,B */
		{ xB( res( 0x02, B() ) ); return ( 8 ); }
		case 137:	/* RES 1,C */
		{ xC( res( 0x02, C() ) ); return ( 8 ); }
		case 138:	/* RES 1,D */
		{ xD( res( 0x02, D() ) ); return ( 8 ); }
		case 139:	/* RES 1,E */
		{ xE( res( 0x02, E() ) ); return ( 8 ); }
		case 140:	/* RES 1,H */
		{ xH( res( 0x02, H() ) ); return ( 8 ); }
		case 141:	/* RES 1,L */
		{ xL( res( 0x02, L() ) ); return ( 8 ); }
		case 142:	/* RES 1,(HL) */
		{
			int hl = HL();
			pokeb( hl, res( 0x02, peekb( hl ) ) );
			return ( 15 );
		}
		case 143:	/* RES 1,A */
		{ xA( res( 0x02, A() ) ); return ( 8 ); }

		case 144:	/* RES 2,B */
		{ xB( res( 0x04, B() ) ); return ( 8 ); }
		case 145:	/* RES 2,C */
		{ xC( res( 0x04, C() ) ); return ( 8 ); }
		case 146:	/* RES 2,D */
		{ xD( res( 0x04, D() ) ); return ( 8 ); }
		case 147:	/* RES 2,E */
		{ xE( res( 0x04, E() ) ); return ( 8 ); }
		case 148:	/* RES 2,H */
		{ xH( res( 0x04, H() ) ); return ( 8 ); }
		case 149:	/* RES 2,L */
		{ xL( res( 0x04, L() ) ); return ( 8 ); }
		case 150:	/* RES 2,(HL) */
		{
			int hl = HL();
			pokeb( hl, res( 0x04, peekb( hl ) ) );
			return ( 15 );
		}
		case 151:	/* RES 2,A */
		{ xA( res( 0x04, A() ) ); return ( 8 ); }

		case 152:	/* RES 3,B */
		{ xB( res( 0x08, B() ) ); return ( 8 ); }
		case 153:	/* RES 3,C */
		{ xC( res( 0x08, C() ) ); return ( 8 ); }
		case 154:	/* RES 3,D */
		{ xD( res( 0x08, D() ) ); return ( 8 ); }
		case 155:	/* RES 3,E */
		{ xE( res( 0x08, E() ) ); return ( 8 ); }
		case 156:	/* RES 3,H */
		{ xH( res( 0x08, H() ) ); return ( 8 ); }
		case 157:	/* RES 3,L */
		{ xL( res( 0x08, L() ) ); return ( 8 ); }
		case 158:	/* RES 3,(HL) */
		{
			int hl = HL();
			pokeb( hl, res( 0x08, peekb( hl ) ) );
			return ( 15 );
		}
		case 159:	/* RES 3,A */
		{ xA( res( 0x08, A() ) ); return ( 8 ); }

		case 160:	/* RES 4,B */
		{ xB( res( 0x10, B() ) ); return ( 8 ); }
		case 161:	/* RES 4,C */
		{ xC( res( 0x10, C() ) ); return ( 8 ); }
		case 162:	/* RES 4,D */
		{ xD( res( 0x10, D() ) ); return ( 8 ); }
		case 163:	/* RES 4,E */
		{ xE( res( 0x10, E() ) ); return ( 8 ); }
		case 164:	/* RES 4,H */
		{ xH( res( 0x10, H() ) ); return ( 8 ); }
		case 165:	/* RES 4,L */
		{ xL( res( 0x10, L() ) ); return ( 8 ); }
		case 166:	/* RES 4,(HL) */
		{
			int hl = HL();
			pokeb( hl, res( 0x10, peekb( hl ) ) );
			return ( 15 );
		}
		case 167:	/* RES 4,A */
		{ xA( res( 0x10, A() ) ); return ( 8 ); }

		case 168:	/* RES 5,B */
		{ xB( res( 0x20, B() ) ); return ( 8 ); }
		case 169:	/* RES 5,C */
		{ xC( res( 0x20, C() ) ); return ( 8 ); }
		case 170:	/* RES 5,D */
		{ xD( res( 0x20, D() ) ); return ( 8 ); }
		case 171:	/* RES 5,E */
		{ xE( res( 0x20, E() ) ); return ( 8 ); }
		case 172:	/* RES 5,H */
		{ xH( res( 0x20, H() ) ); return ( 8 ); }
		case 173:	/* RES 5,L */
		{ xL( res( 0x20, L() ) ); return ( 8 ); }
		case 174:	/* RES 5,(HL) */
		{
			int hl = HL();
			pokeb( hl, res( 0x20, peekb( hl ) ) );
			return ( 15 );
		}
		case 175:	/* RES 5,A */
		{ xA( res( 0x20, A() ) ); return ( 8 ); }

		case 176:	/* RES 6,B */
		{ xB( res( 0x40, B() ) ); return ( 8 ); }
		case 177:	/* RES 6,C */
		{ xC( res( 0x40, C() ) ); return ( 8 ); }
		case 178:	/* RES 6,D */
		{ xD( res( 0x40, D() ) ); return ( 8 ); }
		case 179:	/* RES 6,E */
		{ xE( res( 0x40, E() ) ); return ( 8 ); }
		case 180:	/* RES 6,H */
		{ xH( res( 0x40, H() ) ); return ( 8 ); }
		case 181:	/* RES 6,L */
		{ xL( res( 0x40, L() ) ); return ( 8 ); }
		case 182:	/* RES 6,(HL) */
		{
			int hl = HL();
			pokeb( hl, res( 0x40, peekb( hl ) ) );
			return ( 15 );
		}
		case 183:	/* RES 6,A */
		{ xA( res( 0x40, A() ) ); return ( 8 ); }

		case 184:	/* RES 7,B */
		{ xB( res( 0x80, B() ) ); return ( 8 ); }
		case 185:	/* RES 7,C */
		{ xC( res( 0x80, C() ) ); return ( 8 ); }
		case 186:	/* RES 7,D */
		{ xD( res( 0x80, D() ) ); return ( 8 ); }
		case 187:	/* RES 7,E */
		{ xE( res( 0x80, E() ) ); return ( 8 ); }
		case 188:	/* RES 7,H */
		{ xH( res( 0x80, H() ) ); return ( 8 ); }
		case 189:	/* RES 7,L */
		{ xL( res( 0x80, L() ) ); return ( 8 ); }
		case 190:	/* RES 7,(HL) */
		{
			int hl = HL();
			pokeb( hl, res( 0x80, peekb( hl ) ) );
			return ( 15 );
		}
		case 191:	/* RES 7,A */
		{ xA( res( 0x80, A() ) ); return ( 8 ); }

		case 192:	/* SET 0,B */
		{ xB( set( 0x01, B() ) ); return ( 8 ); }
		case 193:	/* SET 0,C */
		{ xC( set( 0x01, C() ) ); return ( 8 ); }
		case 194:	/* SET 0,D */
		{ xD( set( 0x01, D() ) ); return ( 8 ); }
		case 195:	/* SET 0,E */
		{ xE( set( 0x01, E() ) ); return ( 8 ); }
		case 196:	/* SET 0,H */
		{ xH( set( 0x01, H() ) ); return ( 8 ); }
		case 197:	/* SET 0,L */
		{ xL( set( 0x01, L() ) ); return ( 8 ); }
		case 198:	/* SET 0,(HL) */
		{
			int hl = HL();
			pokeb( hl, set( 0x01, peekb( hl ) ) );
			return ( 15 );
		}
		case 199:	/* SET 0,A */
		{ xA( set( 0x01, A() ) ); return ( 8 ); }

		case 200:	/* SET 1,B */
		{ xB( set( 0x02, B() ) ); return ( 8 ); }
		case 201:	/* SET 1,C */
		{ xC( set( 0x02, C() ) ); return ( 8 ); }
		case 202:	/* SET 1,D */
		{ xD( set( 0x02, D() ) ); return ( 8 ); }
		case 203:	/* SET 1,E */
		{ xE( set( 0x02, E() ) ); return ( 8 ); }
		case 204:	/* SET 1,H */
		{ xH( set( 0x02, H() ) ); return ( 8 ); }
		case 205:	/* SET 1,L */
		{ xL( set( 0x02, L() ) ); return ( 8 ); }
		case 206:	/* SET 1,(HL) */
		{
			int hl = HL();
			pokeb( hl, set( 0x02, peekb( hl ) ) );
			return ( 15 );
		}
		case 207:	/* SET 1,A */
		{ xA( set( 0x02, A() ) ); return ( 8 ); }

		case 208:	/* SET 2,B */
		{ xB( set( 0x04, B() ) ); return ( 8 ); }
		case 209:	/* SET 2,C */
		{ xC( set( 0x04, C() ) ); return ( 8 ); }
		case 210:	/* SET 2,D */
		{ xD( set( 0x04, D() ) ); return ( 8 ); }
		case 211:	/* SET 2,E */
		{ xE( set( 0x04, E() ) ); return ( 8 ); }
		case 212:	/* SET 2,H */
		{ xH( set( 0x04, H() ) ); return ( 8 ); }
		case 213:	/* SET 2,L */
		{ xL( set( 0x04, L() ) ); return ( 8 ); }
		case 214:	/* SET 2,(HL) */
		{
			int hl = HL();
			pokeb( hl, set( 0x04, peekb( hl ) ) );
			return ( 15 );
		}
		case 215:	/* SET 2,A */
		{ xA( set( 0x04, A() ) ); return ( 8 ); }

		case 216:	/* SET 3,B */
		{ xB( set( 0x08, B() ) ); return ( 8 ); }
		case 217:	/* SET 3,C */
		{ xC( set( 0x08, C() ) ); return ( 8 ); }
		case 218:	/* SET 3,D */
		{ xD( set( 0x08, D() ) ); return ( 8 ); }
		case 219:	/* SET 3,E */
		{ xE( set( 0x08, E() ) ); return ( 8 ); }
		case 220:	/* SET 3,H */
		{ xH( set( 0x08, H() ) ); return ( 8 ); }
		case 221:	/* SET 3,L */
		{ xL( set( 0x08, L() ) ); return ( 8 ); }
		case 222:	/* SET 3,(HL) */
		{
			int hl = HL();
			pokeb( hl, set( 0x08, peekb( hl ) ) );
			return ( 15 );
		}
		case 223:	/* SET 3,A */
		{ xA( set( 0x08, A() ) ); return ( 8 ); }

		case 224:	/* SET 4,B */
		{ xB( set( 0x10, B() ) ); return ( 8 ); }
		case 225:	/* SET 4,C */
		{ xC( set( 0x10, C() ) ); return ( 8 ); }
		case 226:	/* SET 4,D */
		{ xD( set( 0x10, D() ) ); return ( 8 ); }
		case 227:	/* SET 4,E */
		{ xE( set( 0x10, E() ) ); return ( 8 ); }
		case 228:	/* SET 4,H */
		{ xH( set( 0x10, H() ) ); return ( 8 ); }
		case 229:	/* SET 4,L */
		{ xL( set( 0x10, L() ) ); return ( 8 ); }
		case 230:	/* SET 4,(HL) */
		{
			int hl = HL();
			pokeb( hl, set( 0x10, peekb( hl ) ) );
			return ( 15 );
		}
		case 231:	/* SET 4,A */
		{ xA( set( 0x10, A() ) ); return ( 8 ); }

		case 232:	/* SET 5,B */
		{ xB( set( 0x20, B() ) ); return ( 8 ); }
		case 233:	/* SET 5,C */
		{ xC( set( 0x20, C() ) ); return ( 8 ); }
		case 234:	/* SET 5,D */
		{ xD( set( 0x20, D() ) ); return ( 8 ); }
		case 235:	/* SET 5,E */
		{ xE( set( 0x20, E() ) ); return ( 8 ); }
		case 236:	/* SET 5,H */
		{ xH( set( 0x20, H() ) ); return ( 8 ); }
		case 237:	/* SET 5,L */
		{ xL( set( 0x20, L() ) ); return ( 8 ); }
		case 238:	/* SET 5,(HL) */
		{
			int hl = HL();
			pokeb( hl, set( 0x20, peekb( hl ) ) );
			return ( 15 );
		}
		case 239:	/* SET 5,A */
		{ xA( set( 0x20, A() ) ); return ( 8 ); }

		case 240:	/* SET 6,B */
		{ xB( set( 0x40, B() ) ); return ( 8 ); }
		case 241:	/* SET 6,C */
		{ xC( set( 0x40, C() ) ); return ( 8 ); }
		case 242:	/* SET 6,D */
		{ xD( set( 0x40, D() ) ); return ( 8 ); }
		case 243:	/* SET 6,E */
		{ xE( set( 0x40, E() ) ); return ( 8 ); }
		case 244:	/* SET 6,H */
		{ xH( set( 0x40, H() ) ); return ( 8 ); }
		case 245:	/* SET 6,L */
		{ xL( set( 0x40, L() ) ); return ( 8 ); }
		case 246:	/* SET 6,(HL) */
		{
			int hl = HL();
			pokeb( hl, set( 0x40, peekb( hl ) ) );
			return ( 15 );
		}
		case 247:	/* SET 6,A */
		{ xA( set( 0x40, A() ) ); return ( 8 ); }

		case 248:	/* SET 7,B */
		{ xB( set( 0x80, B() ) ); return ( 8 ); }
		case 249:	/* SET 7,C */
		{ xC( set( 0x80, C() ) ); return ( 8 ); }
		case 250:	/* SET 7,D */
		{ xD( set( 0x80, D() ) ); return ( 8 ); }
		case 251:	/* SET 7,E */
		{ xE( set( 0x80, E() ) ); return ( 8 ); }
		case 252:	/* SET 7,H */
		{ xH( set( 0x80, H() ) ); return ( 8 ); }
		case 253:	/* SET 7,L */
		{ xL( set( 0x80, L() ) ); return ( 8 ); }
		case 254:	/* SET 7,(HL) */
		{
			int hl = HL();
			pokeb( hl, set( 0x80, peekb( hl ) ) );
			return ( 15 );
		}
		case 255:	/* SET 7,A */
		{ xA( set( 0x80, A() ) ); return ( 8 ); }

		} // switch end

		return 0;
	}
#pragma optimize=no_code_motion
	private final int execute_id() {

		REFRESH( 1 );

		switch ( nxtpcb() ) {

		case  0: /* NOP */
		case  1:
		case  2:
		case  3:
		case  4:
		case  5:
		case  6:
		case  7:
		case  8:

		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
		case 24:

		case 26:
		case 27:
		case 28:
		case 29:
		case 30:
		case 31:
		case 32:

		case 39:
		case 40:

		case 47:
		case 48:
		case 49:
		case 50:
		case 51:

		case 55:
		case 56:

		case 58:
		case 59:
		case 60:
		case 61:
		case 62:
		case 63:
		case 64:
		case 65:
		case 66:
		case 67:

		case 71:
		case 72:
		case 73:
		case 74:
		case 75:

		case 79:
		case 80:
		case 81:
		case 82:
		case 83:

		case 87:
		case 88:
		case 89:
		case 90:
		case 91:

		case 95:

		case 120:
		case 121:
		case 122:
		case 123:

		case 127:
		case 128:
		case 129:
		case 130:
		case 131:

		case 135:
		case 136:
		case 137:
		case 138:
		case 139:

		case 143:
		case 144:
		case 145:
		case 146:
		case 147:

		case 151:
		case 152:
		case 153:
		case 154:
		case 155:

		case 159:
		case 160:
		case 161:
		case 162:
		case 163:

		case 167:
		case 168:
		case 169:
		case 170:
		case 171:

		case 175:
		case 176:
		case 177:
		case 178:
		case 179:

		case 183:
		case 184:
		case 185:
		case 186:
		case 187:

		case 191:
		case 192:
		case 193:
		case 194:
		case 195:
		case 196:
		case 197:
		case 198:
		case 199:
		case 200:
		case 201:
		case 202:

		case 204:
		case 205:
		case 206:
		case 207:
		case 208:
		case 209:
		case 210:
		case 211:
		case 212:
		case 213:
		case 214:
		case 215:
		case 216:
		case 217:
		case 218:
		case 219:
		case 220:
		case 221:
		case 222:
		case 223:
		case 224:

		case 226:

		case 228:

		case 230:
		case 231:
		case 232:

		case 234:
		case 235:
		case 236:
		case 237:
		case 238:
		case 239:
		case 240:
		case 241:
		case 242:
		case 243:
		case 244:
		case 245:
		case 246:
		case 247:
		case 248:
		{
			xPC( dec16( PC() ) );
			REFRESH( -1 );
			return ( 4 );
		}

		case  9: /* ADD ID,BC */
		{ xID( add16( ID(), BC() ) ); return ( 15 ); }
		case 25: /* ADD ID,DE */
		{ xID( add16( ID(), DE() ) ); return ( 15 ); }
		case 41: /* ADD ID,ID */
		{
			int id = ID();
			xID( add16( id, id ) );
			return ( 15 );
		}
		case 57: /* ADD ID,SP */
		{ xID( add16( ID(),SP() ) ); return ( 15 ); }

		case 33: /* LD ID,nn */
		{ xID( nxtpcw() ); return ( 14 ); }
		case 34: /* LD (nn),ID */
		{ pokew( nxtpcw(), ID() ); return ( 20 ); }
		case 42: /* LD ID,(nn) */
		{ xID( peekw( nxtpcw() ) ); return ( 20 ); }
		case 35:/* INC ID */
		{ xID( inc16( ID() ) ); return ( 10 ); }
		case 43:/* DEC ID */
		{ xID( dec16( ID() ) ); return ( 10 ); }
		case 36:/* INC IDH */
		{ xIDH( inc8( IDH() ) ); return ( 8 ); }
		case 44:/* INC IDL */
		{ xIDL( inc8( IDL() ) ); return ( 8 ); }
		case 52:/* INC (ID+d) */
		{
		    int z = ID_d();
		    pokeb( z, inc8( peekb(z) ) );
		    return ( 23 );
		}
		case 37:/* DEC IDH */
		{ xIDH( dec8( IDH() ) ); return ( 8 ); }
		case 45:/* DEC IDL */
		{ xIDL( dec8( IDL() ) ); return ( 8 ); }
		case 53:/* DEC (ID+d) */
		{
		    int z = ID_d();
		    pokeb( z, dec8( peekb(z) ) );
		    return ( 23 );
		}

		case 38: /* LD IDH,n */
		{ xIDH( nxtpcb() ); return ( 11 ); }
		case 46: /* LD IDL,n */
		{ xIDL( nxtpcb() ); return ( 11 ); }
		case 54: /* LD (ID+d),n */
		{ int z = ID_d(); pokeb(z,nxtpcb()); return ( 19 ); }

		case 68: /* LD B,IDH */
		{ xB( IDH() ); return ( 8 ); }
		case 69: /* LD B,IDL */
		{ xB( IDL() ); return ( 8 ); }
		case 70: /* LD B,(ID+d) */
		{ xB( peekb( ID_d() ) ); return ( 19 ); }

		case 76: /* LD C,IDH */
		{ xC( IDH() ); return ( 8 ); }
		case 77: /* LD C,IDL */
		{ xC( IDL() ); return ( 8 ); }
		case 78: /* LD C,(ID+d) */
		{ xC( peekb( ID_d() ) ); return ( 19 ); }

		case 84: /* LD D,IDH */
		{ xD( IDH() ); return ( 8 ); }
		case 85: /* LD D,IDL */
		{ xD( IDL() ); return ( 8 ); }
		case 86: /* LD D,(ID+d) */
		{ xD( peekb( ID_d() ) ); return ( 19 ); }

		case 92: /* LD E,IDH */
		{ xE( IDH() ); return ( 8 ); }
		case 93: /* LD E,IDL */
		{ xE( IDL() ); return ( 8 ); }
		case 94: /* LD E,(ID+d) */
		{ xE( peekb( ID_d() ) ); return ( 19 ); }

		case 96: /* LD IDH,B */
		{ xIDH( B() ); return ( 8 ); }
		case 97: /* LD IDH,C */
		{ xIDH( C() ); return ( 8 ); }
		case 98: /* LD IDH,D */
		{ xIDH( D() ); return ( 8 ); }
		case 99: /* LD IDH,E */
		{ xIDH( E() ); return ( 8 ); }
		case 100: /* LD IDH,IDH */
		{ return ( 8 ); }
		case 101: /* LD IDH,IDL */
		{ xIDH( IDL() ); return ( 8 ); }
		case 102: /* LD H,(ID+d) */
		{ xH( peekb( ID_d() ) ); return ( 19 ); }
		case 103: /* LD IDH,A */
		{ xIDH( A() ); return ( 8 ); }

		case 104: /* LD IDL,B */
		{ xIDL( B() ); return ( 8 ); }
		case 105: /* LD IDL,C */
		{ xIDL( C() ); return ( 8 ); }
		case 106: /* LD IDL,D */
		{ xIDL( D() ); return ( 8 ); }
		case 107: /* LD IDL,E */
		{ xIDL( E() ); return ( 8 ); }
		case 108: /* LD IDL,IDH */
		{ xIDL( IDH() ); return ( 8 ); }
		case 109: /* LD IDL,IDL */
		{ return ( 8 ); }
		case 110: /* LD L,(ID+d) */
		{ xL( peekb( ID_d() ) ); return ( 19 ); }
		case 111: /* LD IDL,A */
		{ xIDL( A() ); return ( 8 ); }

		case 112: /* LD (ID+d),B */
		{ pokeb( ID_d(), B() ); return ( 19 ); }
		case 113: /* LD (ID+d),C */
		{ pokeb( ID_d(), C() ); return ( 19 ); }
		case 114: /* LD (ID+d),D */
		{ pokeb( ID_d(), D() ); return ( 19 ); }
		case 115: /* LD (ID+d),E */
		{ pokeb( ID_d(), E() ); return ( 19 ); }
		case 116: /* LD (ID+d),H */
		{ pokeb( ID_d(), H() ); return ( 19 ); }
		case 117: /* LD (ID+d),L */
		{ pokeb( ID_d(), L() ); return ( 19 ); }
		case 119: /* LD (ID+d),A */
		{ pokeb( ID_d(), A() ); return ( 19 ); }

		case 124: /* LD A,IDH */
		{ xA( IDH() ); return ( 8 ); }
		case 125: /* LD A,IDL */
		{ xA( IDL() ); return ( 8 ); }
		case 126: /* LD A,(ID+d) */
		{ xA( peekb( ID_d() ) ); return ( 19 ); }

		case 132: /* ADD A,IDH */
		{ add_a(IDH()); return ( 8 ); }
		case 133: /* ADD A,IDL */
		{ add_a(IDL()); return ( 8 ); }
		case 134: /* ADD A,(ID+d) */
		{ add_a(peekb( ID_d() )); return ( 19 ); }

		case 140: /* ADC A,IDH */
		{ adc_a(IDH()); return ( 8 ); }
		case 141: /* ADC A,IDL */
		{ adc_a(IDL()); return ( 8 ); }
		case 142: /* ADC A,(ID+d) */
		{ adc_a(peekb( ID_d() )); return ( 19 ); }

		case 148: /* SUB IDH */
		{ sub_a(IDH()); return ( 8 ); }
		case 149: /* SUB IDL */
		{ sub_a(IDL()); return ( 8 ); }
		case 150: /* SUB (ID+d) */
		{ sub_a(peekb( ID_d() )); return ( 19 ); }

		case 156: /* SBC A,IDH */
		{ sbc_a(IDH()); return ( 8 ); }
		case 157: /* SBC A,IDL */
		{ sbc_a(IDL()); return ( 8 ); }
		case 158: /* SBC A,(ID+d) */
		{ sbc_a(peekb( ID_d() )); return ( 19 ); }

		case 164: /* AND IDH */
		{ and_a(IDH()); return ( 8 ); }
		case 165: /* AND IDL */
		{ and_a(IDL()); return ( 8 ); }
		case 166: /* AND (ID+d) */
		{ and_a(peekb( ID_d() )); return ( 19 ); }

		case 172: /* XOR IDH */
		{ xor_a(IDH()); return ( 8 ); }
		case 173: /* XOR IDL */
		{ xor_a(IDL()); return ( 8 ); }
		case 174: /* XOR (ID+d) */
		{ xor_a(peekb( ID_d() )); return ( 19 ); }

		case 180: /* OR IDH */
		{ or_a(IDH()); return ( 8 ); }
		case 181: /* OR IDL */
		{ or_a(IDL()); return ( 8 ); }
		case 182: /* OR (ID+d) */
		{ or_a(peekb( ID_d() )); return ( 19 ); }

		case 188: /* CP IDH */
		{ cp_a(IDH()); return ( 8 ); }
		case 189: /* CP IDL */
		{ cp_a(IDL()); return ( 8 ); }
		case 190: /* CP (ID+d) */
		{ cp_a(peekb( ID_d() )); return ( 19 ); }

		case 225: /* POP ID */
		{ xID( popw() ); return ( 14 ); }

		case 233: /* JP (ID) */
		{ xPC( ID() ); return ( 8 ); }

		case 249: /* LD SP,ID */
		{ xSP( ID() ); return ( 10 ); }

		case 203: /* prefix CB */
		{
			// Obtain index address (offset byte goes first)
			int z = ID_d();
			// opcode comes after offset byte
			int op = nxtpcb();
			execute_id_cb( op, z );
			// BIT instructions take 20 T-States, the rests take 23 T-states

			return ( (( op & 0xc0 ) == 0x40) ? 20 : 23 );
		}

		case 227: /* EX (SP),ID */
		{
			int t = ID();
			int sp = SP();
			xID( peekw( sp ) );
			pokew( sp, t );
			return ( 23 );
		}

		case 229:    /* PUSH ID */
		{ pushw( ID() ); return ( 15 ); }

		} // switch end

		return 0;
	}

#pragma optimize=no_code_motion
	private final void execute_id_cb(int op, int z) {

		switch ( op ) {

		case   0:	/* RLC B */
		{ xB( op = rlc( peekb( z ) ) ); pokeb( z, op ); return; }
		case   1:	/* RLC C */
		{ xC( op = rlc( peekb( z ) ) ); pokeb( z, op ); return; }
		case   2:	/* RLC D */
		{ xD( op = rlc( peekb( z ) ) ); pokeb( z, op ); return; }
		case   3:	/* RLC E */
		{ xE( op = rlc( peekb( z ) ) ); pokeb( z, op ); return; }
		case   4:	/* RLC H */
		{ xH( op = rlc( peekb( z ) ) ); pokeb( z, op ); return; }
		case   5:	/* RLC L */
		{ xL( op = rlc( peekb( z ) ) ); pokeb( z, op ); return; }
		case   6:	/* RLC (HL) */
		{ pokeb( z, rlc( peekb( z ) ) ); return; }
		case   7:	/* RLC A */
		{ xA( op = rlc( peekb( z ) ) ); pokeb( z, op ); return; }

		case   8:	/* RRC B */
		{ xB( op = rrc( peekb( z ) ) ); pokeb( z, op ); return; }
		case   9:	/* RRC C */
		{ xC( op = rrc( peekb( z ) ) ); pokeb( z, op ); return; }
		case  10:	/* RRC D */
		{ xD( op = rrc( peekb( z ) ) ); pokeb( z, op ); return; }
		case  11:	/* RRC E */
		{ xE( op = rrc( peekb( z ) ) ); pokeb( z, op ); return; }
		case  12:	/* RRC H */
		{ xH( op = rrc( peekb( z ) ) ); pokeb( z, op ); return; }
		case  13:	/* RRC L */
		{ xL( op = rrc( peekb( z ) ) ); pokeb( z, op ); return; }
		case  14:	/* RRC (HL) */
		{ pokeb( z, rrc( peekb( z ) ) ); return; }
		case  15:	/* RRC A */
		{ xA( op = rrc( peekb( z ) ) ); pokeb( z, op ); return; }

		case  16:	/* RL B */
		{ xB( op = rl( peekb( z ) ) ); pokeb( z, op ); return; }
		case  17:	/* RL C */
		{ xC( op = rl( peekb( z ) ) ); pokeb( z, op ); return; }
		case  18:	/* RL D */
		{ xD( op = rl( peekb( z ) ) ); pokeb( z, op ); return; }
		case  19:	/* RL E */
		{ xE( op = rl( peekb( z ) ) ); pokeb( z, op ); return; }
		case  20:	/* RL H */
		{ xH( op = rl( peekb( z ) ) ); pokeb( z, op ); return; }
		case  21:	/* RL L */
		{ xL( op = rl( peekb( z ) ) ); pokeb( z, op ); return; }
		case  22:	/* RL (HL) */
		{ pokeb( z, rl( peekb( z ) ) ); return; }
		case  23:	/* RL A */
		{ xA( op = rl( peekb( z ) ) ); pokeb( z, op ); return; }

		case  24:	/* RR B */
		{ xB( op = rr( peekb( z ) ) ); pokeb( z, op ); return; }
		case  25:	/* RR C */
		{ xC( op = rr( peekb( z ) ) ); pokeb( z, op ); return; }
		case  26:	/* RR D */
		{ xD( op = rr( peekb( z ) ) ); pokeb( z, op ); return; }
		case  27:	/* RR E */
		{ xE( op = rr( peekb( z ) ) ); pokeb( z, op ); return; }
		case  28:	/* RR H */
		{ xH( op = rr( peekb( z ) ) ); pokeb( z, op ); return; }
		case  29:	/* RR L */
		{ xL( op = rr( peekb( z ) ) ); pokeb( z, op ); return; }
		case  30:	/* RR (HL) */
		{ pokeb( z, rr( peekb( z ) ) ); return; }
		case  31:	/* RR A */
		{ xA( op = rr( peekb( z ) ) ); pokeb( z, op ); return; }

		case  32:	/* SLA B */
		{ xB( op = sla( peekb( z ) ) ); pokeb( z, op ); return; }
		case  33:	/* SLA C */
		{ xC( op = sla( peekb( z ) ) ); pokeb( z, op ); return; }
		case  34:	/* SLA D */
		{ xD( op = sla( peekb( z ) ) ); pokeb( z, op ); return; }
		case  35:	/* SLA E */
		{ xE( op = sla( peekb( z ) ) ); pokeb( z, op ); return; }
		case  36:	/* SLA H */
		{ xH( op = sla( peekb( z ) ) ); pokeb( z, op ); return; }
		case  37:	/* SLA L */
		{ xL( op = sla( peekb( z ) ) ); pokeb( z, op ); return; }
		case  38:	/* SLA (HL) */
		{ pokeb( z, sla( peekb( z ) ) ); return; }
		case  39:	/* SLA A */
		{ xA( op = sla( peekb( z ) ) ); pokeb( z, op ); return; }

		case  40:	/* SRA B */
		{ xB( op = sra( peekb( z ) ) ); pokeb( z, op ); return; }
		case  41:	/* SRA C */
		{ xC( op = sra( peekb( z ) ) ); pokeb( z, op ); return; }
		case  42:	/* SRA D */
		{ xD( op = sra( peekb( z ) ) ); pokeb( z, op ); return; }
		case  43:	/* SRA E */
		{ xE( op = sra( peekb( z ) ) ); pokeb( z, op ); return; }
		case  44:	/* SRA H */
		{ xH( op = sra( peekb( z ) ) ); pokeb( z, op ); return; }
		case  45:	/* SRA L */
		{ xL( op = sra( peekb( z ) ) ); pokeb( z, op ); return; }
		case  46:	/* SRA (HL) */
		{ pokeb( z, sra( peekb( z ) ) ); return; }
		case  47:	/* SRA A */
		{ xA( op = sra( peekb( z ) ) ); pokeb( z, op ); return; }

		case  48:	/* SLS B */
		{ xB( op = sls( peekb( z ) ) ); pokeb( z, op ); return; }
		case  49:	/* SLS C */
		{ xC( op = sls( peekb( z ) ) ); pokeb( z, op ); return; }
		case  50:	/* SLS D */
		{ xD( op = sls( peekb( z ) ) ); pokeb( z, op ); return; }
		case  51:	/* SLS E */
		{ xE( op = sls( peekb( z ) ) ); pokeb( z, op ); return; }
		case  52:	/* SLS H */
		{ xH( op = sls( peekb( z ) ) ); pokeb( z, op ); return; }
		case  53:	/* SLS L */
		{ xL( op = sls( peekb( z ) ) ); pokeb( z, op ); return; }
		case  54:	/* SLS (HL) */
		{ pokeb( z, sls( peekb( z ) ) ); return; }
		case  55:	/* SLS A */
		{ xA( op = sls( peekb( z ) ) ); pokeb( z, op ); return; }

		case  56:	/* SRL B */
		{ xB( op = srl( peekb( z ) ) ); pokeb( z, op ); return; }
		case  57:	/* SRL C */
		{ xC( op = srl( peekb( z ) ) ); pokeb( z, op ); return; }
		case  58:	/* SRL D */
		{ xD( op = srl( peekb( z ) ) ); pokeb( z, op ); return; }
		case  59:	/* SRL E */
		{ xE( op = srl( peekb( z ) ) ); pokeb( z, op ); return; }
		case  60:	/* SRL H */
		{ xH( op = srl( peekb( z ) ) ); pokeb( z, op ); return; }
		case  61:	/* SRL L */
		{ xL( op = srl( peekb( z ) ) ); pokeb( z, op ); return; }
		case  62:	/* SRL (HL) */
		{ pokeb( z, srl( peekb( z ) ) ); return; }
		case  63:	/* SRL A */
		{ xA( op = srl( peekb( z ) ) ); pokeb( z, op ); return; }

		case  64:	/* BIT 0,B */
		case  65:	/* BIT 0,B */
		case  66:	/* BIT 0,B */
		case  67:	/* BIT 0,B */
		case  68:	/* BIT 0,B */
		case  69:	/* BIT 0,B */
		case  70:	/* BIT 0,B */
		case  71:	/* BIT 0,B */
		{ bit( 0x01, peekb( z ) ); return; }

		case  72:	/* BIT 1,B */
		case  73:	/* BIT 1,B */
		case  74:	/* BIT 1,B */
		case  75:	/* BIT 1,B */
		case  76:	/* BIT 1,B */
		case  77:	/* BIT 1,B */
		case  78:	/* BIT 1,B */
		case  79:	/* BIT 1,B */
		{ bit( 0x02, peekb( z ) ); return; }

		case  80:	/* BIT 2,B */
		case  81:	/* BIT 2,B */
		case  82:	/* BIT 2,B */
		case  83:	/* BIT 2,B */
		case  84:	/* BIT 2,B */
		case  85:	/* BIT 2,B */
		case  86:	/* BIT 2,B */
		case  87:	/* BIT 2,B */
		{ bit( 0x04, peekb( z ) ); return; }

		case  88:	/* BIT 3,B */
		case  89:	/* BIT 3,B */
		case  90:	/* BIT 3,B */
		case  91:	/* BIT 3,B */
		case  92:	/* BIT 3,B */
		case  93:	/* BIT 3,B */
		case  94:	/* BIT 3,B */
		case  95:	/* BIT 3,B */
		{ bit( 0x08, peekb( z ) ); return; }

		case  96:	/* BIT 4,B */
		case  97:	/* BIT 4,B */
		case  98:	/* BIT 4,B */
		case  99:	/* BIT 4,B */
		case 100:	/* BIT 4,B */
		case 101:	/* BIT 4,B */
		case 102:	/* BIT 4,B */
		case 103:	/* BIT 4,B */
		{ bit( 0x10, peekb( z ) ); return; }

		case 104:	/* BIT 5,B */
		case 105:	/* BIT 5,B */
		case 106:	/* BIT 5,B */
		case 107:	/* BIT 5,B */
		case 108:	/* BIT 5,B */
		case 109:	/* BIT 5,B */
		case 110:	/* BIT 5,B */
		case 111:	/* BIT 5,B */
		{ bit( 0x20, peekb( z ) ); return; }

		case 112:	/* BIT 6,B */
		case 113:	/* BIT 6,B */
		case 114:	/* BIT 6,B */
		case 115:	/* BIT 6,B */
		case 116:	/* BIT 6,B */
		case 117:	/* BIT 6,B */
		case 118:	/* BIT 6,B */
		case 119:	/* BIT 6,B */
		{ bit( 0x40, peekb( z ) ); return; }

		case 120:	/* BIT 7,B */
		case 121:	/* BIT 7,B */
		case 122:	/* BIT 7,B */
		case 123:	/* BIT 7,B */
		case 124:	/* BIT 7,B */
		case 125:	/* BIT 7,B */
		case 126:	/* BIT 7,B */
		case 127:	/* BIT 7,B */
		{ bit( 0x80, peekb( z ) ); return; }

		case 128:	/* RES 0,B */
		{ xB( op = res( 0x01, peekb( z ) ) ); pokeb( z, op ); return; }
		case 129:	/* RES 0,C */
		{ xC( op = res( 0x01, peekb( z ) ) ); pokeb( z, op ); return; }
		case 130:	/* RES 0,D */
		{ xD( op = res( 0x01, peekb( z ) ) ); pokeb( z, op ); return; }
		case 131:	/* RES 0,E */
		{ xE( op = res( 0x01, peekb( z ) ) ); pokeb( z, op ); return; }
		case 132:	/* RES 0,H */
		{ xH( op = res( 0x01, peekb( z ) ) ); pokeb( z, op ); return; }
		case 133:	/* RES 0,L */
		{ xL( op = res( 0x01, peekb( z ) ) ); pokeb( z, op ); return; }
		case 134:	/* RES 0,(HL) */
		{ pokeb( z, res( 0x01, peekb( z ) ) ); return; }
		case 135:	/* RES 0,A */
		{ xA( op = res( 0x01, peekb( z ) ) ); pokeb( z, op ); return; }

		case 136:	/* RES 1,B */
		{ xB( op = res( 0x02, peekb( z ) ) ); pokeb( z, op ); return; }
		case 137:	/* RES 1,C */
		{ xC( op = res( 0x02, peekb( z ) ) ); pokeb( z, op ); return; }
		case 138:	/* RES 1,D */
		{ xD( op = res( 0x02, peekb( z ) ) ); pokeb( z, op ); return; }
		case 139:	/* RES 1,E */
		{ xE( op = res( 0x02, peekb( z ) ) ); pokeb( z, op ); return; }
		case 140:	/* RES 1,H */
		{ xH( op = res( 0x02, peekb( z ) ) ); pokeb( z, op ); return; }
		case 141:	/* RES 1,L */
		{ xL( op = res( 0x02, peekb( z ) ) ); pokeb( z, op ); return; }
		case 142:	/* RES 1,(HL) */
		{ pokeb( z, res( 0x02, peekb( z ) ) ); return; }
		case 143:	/* RES 1,A */
		{ xA( op = res( 0x02, peekb( z ) ) ); pokeb( z, op ); return; }

		case 144:	/* RES 2,B */
		{ xB( op = res( 0x04, peekb( z ) ) ); pokeb( z, op ); return; }
		case 145:	/* RES 2,C */
		{ xC( op = res( 0x04, peekb( z ) ) ); pokeb( z, op ); return; }
		case 146:	/* RES 2,D */
		{ xD( op = res( 0x04, peekb( z ) ) ); pokeb( z, op ); return; }
		case 147:	/* RES 2,E */
		{ xE( op = res( 0x04, peekb( z ) ) ); pokeb( z, op ); return; }
		case 148:	/* RES 2,H */
		{ xH( op = res( 0x04, peekb( z ) ) ); pokeb( z, op ); return; }
		case 149:	/* RES 2,L */
		{ xL( op = res( 0x04, peekb( z ) ) ); pokeb( z, op ); return; }
		case 150:	/* RES 2,(HL) */
		{ pokeb( z, res( 0x04, peekb( z ) ) ); return; }
		case 151:	/* RES 2,A */
		{ xA( op = res( 0x04, peekb( z ) ) ); pokeb( z, op ); return; }

		case 152:	/* RES 3,B */
		{ xB( op = res( 0x08, peekb( z ) ) ); pokeb( z, op ); return; }
		case 153:	/* RES 3,C */
		{ xC( op = res( 0x08, peekb( z ) ) ); pokeb( z, op ); return; }
		case 154:	/* RES 3,D */
		{ xD( op = res( 0x08, peekb( z ) ) ); pokeb( z, op ); return; }
		case 155:	/* RES 3,E */
		{ xE( op = res( 0x08, peekb( z ) ) ); pokeb( z, op ); return; }
		case 156:	/* RES 3,H */
		{ xH( op = res( 0x08, peekb( z ) ) ); pokeb( z, op ); return; }
		case 157:	/* RES 3,L */
		{ xL( op = res( 0x08, peekb( z ) ) ); pokeb( z, op ); return; }
		case 158:	/* RES 3,(HL) */
		{ pokeb( z, res( 0x08, peekb( z ) ) ); return; }
		case 159:	/* RES 3,A */
		{ xA( op = res( 0x08, peekb( z ) ) ); pokeb( z, op ); return; }

		case 160:	/* RES 4,B */
		{ xB( op = res( 0x10, peekb( z ) ) ); pokeb( z, op ); return; }
		case 161:	/* RES 4,C */
		{ xC( op = res( 0x10, peekb( z ) ) ); pokeb( z, op ); return; }
		case 162:	/* RES 4,D */
		{ xD( op = res( 0x10, peekb( z ) ) ); pokeb( z, op ); return; }
		case 163:	/* RES 4,E */
		{ xE( op = res( 0x10, peekb( z ) ) ); pokeb( z, op ); return; }
		case 164:	/* RES 4,H */
		{ xH( op = res( 0x10, peekb( z ) ) ); pokeb( z, op ); return; }
		case 165:	/* RES 4,L */
		{ xL( op = res( 0x10, peekb( z ) ) ); pokeb( z, op ); return; }
		case 166:	/* RES 4,(HL) */
		{ pokeb( z, res( 0x10, peekb( z ) ) ); return; }
		case 167:	/* RES 4,A */
		{ xA( op = res( 0x10, peekb( z ) ) ); pokeb( z, op ); return; }

		case 168:	/* RES 5,B */
		{ xB( op = res( 0x20, peekb( z ) ) ); pokeb( z, op ); return; }
		case 169:	/* RES 5,C */
		{ xC( op = res( 0x20, peekb( z ) ) ); pokeb( z, op ); return; }
		case 170:	/* RES 5,D */
		{ xD( op = res( 0x20, peekb( z ) ) ); pokeb( z, op ); return; }
		case 171:	/* RES 5,E */
		{ xE( op = res( 0x20, peekb( z ) ) ); pokeb( z, op ); return; }
		case 172:	/* RES 5,H */
		{ xH( op = res( 0x20, peekb( z ) ) ); pokeb( z, op ); return; }
		case 173:	/* RES 5,L */
		{ xL( op = res( 0x20, peekb( z ) ) ); pokeb( z, op ); return; }
		case 174:	/* RES 5,(HL) */
		{ pokeb( z, res( 0x20, peekb( z ) ) ); return; }
		case 175:	/* RES 5,A */
		{ xA( op = res( 0x20, peekb( z ) ) ); pokeb( z, op ); return; }

		case 176:	/* RES 6,B */
		{ xB( op = res( 0x40, peekb( z ) ) ); pokeb( z, op ); return; }
		case 177:	/* RES 6,C */
		{ xC( op = res( 0x40, peekb( z ) ) ); pokeb( z, op ); return; }
		case 178:	/* RES 6,D */
		{ xD( op = res( 0x40, peekb( z ) ) ); pokeb( z, op ); return; }
		case 179:	/* RES 6,E */
		{ xE( op = res( 0x40, peekb( z ) ) ); pokeb( z, op ); return; }
		case 180:	/* RES 6,H */
		{ xH( op = res( 0x40, peekb( z ) ) ); pokeb( z, op ); return; }
		case 181:	/* RES 6,L */
		{ xL( op = res( 0x40, peekb( z ) ) ); pokeb( z, op ); return; }
		case 182:	/* RES 6,(HL) */
		{ pokeb( z, res( 0x40, peekb( z ) ) ); return; }
		case 183:	/* RES 6,A */
		{ xA( op = res( 0x40, peekb( z ) ) ); pokeb( z, op ); return; }

		case 184:	/* RES 7,B */
		{ xB( op = res( 0x80, peekb( z ) ) ); pokeb( z, op ); return; }
		case 185:	/* RES 7,C */
		{ xC( op = res( 0x80, peekb( z ) ) ); pokeb( z, op ); return; }
		case 186:	/* RES 7,D */
		{ xD( op = res( 0x80, peekb( z ) ) ); pokeb( z, op ); return; }
		case 187:	/* RES 7,E */
		{ xE( op = res( 0x80, peekb( z ) ) ); pokeb( z, op ); return; }
		case 188:	/* RES 7,H */
		{ xH( op = res( 0x80, peekb( z ) ) ); pokeb( z, op ); return; }
		case 189:	/* RES 7,L */
		{ xL( op = res( 0x80, peekb( z ) ) ); pokeb( z, op ); return; }
		case 190:	/* RES 7,(HL) */
		{ pokeb( z, res( 0x80, peekb( z ) ) ); return; }
		case 191:	/* RES 7,A */
		{ xA( op = res( 0x80, peekb( z ) ) ); pokeb( z, op ); return; }

		case 192:	/* SET 0,B */
		{ xB( op = set( 0x01, peekb( z ) ) ); pokeb( z, op ); return; }
		case 193:	/* SET 0,C */
		{ xC( op = set( 0x01, peekb( z ) ) ); pokeb( z, op ); return; }
		case 194:	/* SET 0,D */
		{ xD( op = set( 0x01, peekb( z ) ) ); pokeb( z, op ); return; }
		case 195:	/* SET 0,E */
		{ xE( op = set( 0x01, peekb( z ) ) ); pokeb( z, op ); return; }
		case 196:	/* SET 0,H */
		{ xH( op = set( 0x01, peekb( z ) ) ); pokeb( z, op ); return; }
		case 197:	/* SET 0,L */
		{ xL( op = set( 0x01, peekb( z ) ) ); pokeb( z, op ); return; }
		case 198:	/* SET 0,(HL) */
		{ pokeb( z, set( 0x01, peekb( z ) ) ); return; }
		case 199:	/* SET 0,A */
		{ xA( op = set( 0x01, peekb( z ) ) ); pokeb( z, op ); return; }

		case 200:	/* SET 1,B */
		{ xB( op = set( 0x02, peekb( z ) ) ); pokeb( z, op ); return; }
		case 201:	/* SET 1,C */
		{ xC( op = set( 0x02, peekb( z ) ) ); pokeb( z, op ); return; }
		case 202:	/* SET 1,D */
		{ xD( op = set( 0x02, peekb( z ) ) ); pokeb( z, op ); return; }
		case 203:	/* SET 1,E */
		{ xE( op = set( 0x02, peekb( z ) ) ); pokeb( z, op ); return; }
		case 204:	/* SET 1,H */
		{ xH( op = set( 0x02, peekb( z ) ) ); pokeb( z, op ); return; }
		case 205:	/* SET 1,L */
		{ xL( op = set( 0x02, peekb( z ) ) ); pokeb( z, op ); return; }
		case 206:	/* SET 1,(HL) */
		{ pokeb( z, set( 0x02, peekb( z ) ) ); return; }
		case 207:	/* SET 1,A */
		{ xA( op = set( 0x02, peekb( z ) ) ); pokeb( z, op ); return; }

		case 208:	/* SET 2,B */
		{ xB( op = set( 0x04, peekb( z ) ) ); pokeb( z, op ); return; }
		case 209:	/* SET 2,C */
		{ xC( op = set( 0x04, peekb( z ) ) ); pokeb( z, op ); return; }
		case 210:	/* SET 2,D */
		{ xD( op = set( 0x04, peekb( z ) ) ); pokeb( z, op ); return; }
		case 211:	/* SET 2,E */
		{ xE( op = set( 0x04, peekb( z ) ) ); pokeb( z, op ); return; }
		case 212:	/* SET 2,H */
		{ xH( op = set( 0x04, peekb( z ) ) ); pokeb( z, op ); return; }
		case 213:	/* SET 2,L */
		{ xL( op = set( 0x04, peekb( z ) ) ); pokeb( z, op ); return; }
		case 214:	/* SET 2,(HL) */
		{ pokeb( z, set( 0x04, peekb( z ) ) ); return; }
		case 215:	/* SET 2,A */
		{ xA( op = set( 0x04, peekb( z ) ) ); pokeb( z, op ); return; }

		case 216:	/* SET 3,B */
		{ xB( op = set( 0x08, peekb( z ) ) ); pokeb( z, op ); return; }
		case 217:	/* SET 3,C */
		{ xC( op = set( 0x08, peekb( z ) ) ); pokeb( z, op ); return; }
		case 218:	/* SET 3,D */
		{ xD( op = set( 0x08, peekb( z ) ) ); pokeb( z, op ); return; }
		case 219:	/* SET 3,E */
		{ xE( op = set( 0x08, peekb( z ) ) ); pokeb( z, op ); return; }
		case 220:	/* SET 3,H */
		{ xH( op = set( 0x08, peekb( z ) ) ); pokeb( z, op ); return; }
		case 221:	/* SET 3,L */
		{ xL( op = set( 0x08, peekb( z ) ) ); pokeb( z, op ); return; }
		case 222:	/* SET 3,(HL) */
		{ pokeb( z, set( 0x08, peekb( z ) ) ); return; }
		case 223:	/* SET 3,A */
		{ xA( op = set( 0x08, peekb( z ) ) ); pokeb( z, op ); return; }

		case 224:	/* SET 4,B */
		{ xB( op = set( 0x10, peekb( z ) ) ); pokeb( z, op ); return; }
		case 225:	/* SET 4,C */
		{ xC( op = set( 0x10, peekb( z ) ) ); pokeb( z, op ); return; }
		case 226:	/* SET 4,D */
		{ xD( op = set( 0x10, peekb( z ) ) ); pokeb( z, op ); return; }
		case 227:	/* SET 4,E */
		{ xE( op = set( 0x10, peekb( z ) ) ); pokeb( z, op ); return; }
		case 228:	/* SET 4,H */
		{ xH( op = set( 0x10, peekb( z ) ) ); pokeb( z, op ); return; }
		case 229:	/* SET 4,L */
		{ xL( op = set( 0x10, peekb( z ) ) ); pokeb( z, op ); return; }
		case 230:	/* SET 4,(HL) */
		{ pokeb( z, set( 0x10, peekb( z ) ) ); return; }
		case 231:	/* SET 4,A */
		{ xA( op = set( 0x10, peekb( z ) ) ); pokeb( z, op ); return; }

		case 232:	/* SET 5,B */
		{ xB( op = set( 0x20, peekb( z ) ) ); pokeb( z, op ); return; }
		case 233:	/* SET 5,C */
		{ xC( op = set( 0x20, peekb( z ) ) ); pokeb( z, op ); return; }
		case 234:	/* SET 5,D */
		{ xD( op = set( 0x20, peekb( z ) ) ); pokeb( z, op ); return; }
		case 235:	/* SET 5,E */
		{ xE( op = set( 0x20, peekb( z ) ) ); pokeb( z, op ); return; }
		case 236:	/* SET 5,H */
		{ xH( op = set( 0x20, peekb( z ) ) ); pokeb( z, op ); return; }
		case 237:	/* SET 5,L */
		{ xL( op = set( 0x20, peekb( z ) ) ); pokeb( z, op ); return; }
		case 238:	/* SET 5,(HL) */
		{ pokeb( z, set( 0x20, peekb( z ) ) ); return; }
		case 239:	/* SET 5,A */
		{ xA( op = set( 0x20, peekb( z ) ) ); pokeb( z, op ); return; }

		case 240:	/* SET 6,B */
		{ xB( op = set( 0x40, peekb( z ) ) ); pokeb( z, op ); return; }
		case 241:	/* SET 6,C */
		{ xC( op = set( 0x40, peekb( z ) ) ); pokeb( z, op ); return; }
		case 242:	/* SET 6,D */
		{ xD( op = set( 0x40, peekb( z ) ) ); pokeb( z, op ); return; }
		case 243:	/* SET 6,E */
		{ xE( op = set( 0x40, peekb( z ) ) ); pokeb( z, op ); return; }
		case 244:	/* SET 6,H */
		{ xH( op = set( 0x40, peekb( z ) ) ); pokeb( z, op ); return; }
		case 245:	/* SET 6,L */
		{ xL( op = set( 0x40, peekb( z ) ) ); pokeb( z, op ); return; }
		case 246:	/* SET 6,(HL) */
		{ pokeb( z, set( 0x40, peekb( z ) ) ); return; }
		case 247:	/* SET 6,A */
		{ xA( op = set( 0x40, peekb( z ) ) ); pokeb( z, op ); return; }

		case 248:	/* SET 7,B */
		{ xB( op = set( 0x80, peekb( z ) ) ); pokeb( z, op ); return; }
		case 249:	/* SET 7,C */
		{ xC( op = set( 0x80, peekb( z ) ) ); pokeb( z, op ); return; }
		case 250:	/* SET 7,D */
		{ xD( op = set( 0x80, peekb( z ) ) ); pokeb( z, op ); return; }
		case 251:	/* SET 7,E */
		{ xE( op = set( 0x80, peekb( z ) ) ); pokeb( z, op ); return; }
		case 252:	/* SET 7,H */
		{ xH( op = set( 0x80, peekb( z ) ) ); pokeb( z, op ); return; }
		case 253:	/* SET 7,L */
		{ xL( op = set( 0x80, peekb( z ) ) ); pokeb( z, op ); return; }
		case 254:	/* SET 7,(HL) */
		{ pokeb( z, set( 0x80, peekb( z ) ) ); return; }
		case 255:	/* SET 7,A */
		{ xA( op = set( 0x80, peekb( z ) ) ); pokeb( z, op ); return; }

		} // switch end
	}



////////////////////from spectrum
	public void resetKeyboard() { for(int i=0;i<8;i++) keylines[i]=(byte)0xff;}

	public int inb( int port ) {
		int res = 0xff, i, j;
		if ((port&1)==0) 
  		  for(i=0,j=0x100;i<8;i++,j<<=1)
			if((port & j) == 0) res &= keylines[i]; 
		return(res);
	}
	
	public void outb( int port, int outByte, int tstates ) {
	  if((port & 2)==0 && (port&0x8000)==0){  
	  //if((port==0x7ffd)){
	    if(fz128){
	      if((pport&0x10)!=(outByte&0x10))
          memcpy(mem,mem+(((outByte & 0x10)==0)?rom128:rom48),rompage);
	        //System.arraycopy(mem,((outByte & 0x10)==0)?rom128:rom48,mem,0,rompage);
		  if((pport&7)!=(outByte&7)){
        memcpy(mem+zxpage[pport&7],mem+rombank,rompage);
		    //System.arraycopy(mem,rombank,mem,zxpage[pport&7],rompage);//romstart+rompage*i
        memcpy(mem+rombank,mem+zxpage[outByte&7],rompage);
		    //System.arraycopy(mem,zxpage[outByte&7],mem,rombank,rompage);//romstart+rompage*j
		  }
		  pport=(byte)outByte;
		}
 	  }else if((port&1)==0) newBorder=(outByte & 7);
	}
	
  public boolean loadSNA(unsigned char *zx, int rombuf){// throws Exception {
		if(zxfilesize==131103 && !fz128) return false;//throw new Exception( "" );
		memcpy(mem+16384,zx+rombuf+27,49152);
    //System.arraycopy(zx,rombuf+27,mem,16384, 49152 );
		_I=(zx[rombuf]);
		_HL=( (zx[rombuf+1]) | ((zx[rombuf+2])<<8) );
		_DE=( (zx[rombuf+3]) | ((zx[rombuf+4])<<8) );
		xBC( (zx[rombuf+5]) | ((zx[rombuf+6])<<8) );
		xAF( (zx[rombuf+7]) | ((zx[rombuf+8])<<8) );
		exx();
		ex_af_af();
		_HL=( (zx[rombuf+9])  | ((zx[rombuf+10])<<8) );
		_DE=( (zx[rombuf+11]) | ((zx[rombuf+12])<<8) );
		xBC( (zx[rombuf+13]) | ((zx[rombuf+14])<<8) );
		_IY=( (zx[rombuf+15]) | ((zx[rombuf+16])<<8) );
		_IX=( (zx[rombuf+17]) | ((zx[rombuf+18])<<8) );
		if ((( zx[rombuf+19])& 0x04)!= 0 ) xIFF2( true );	else xIFF2( false );
		_R=( zx[rombuf+20] );
		xAF( (zx[rombuf+21]) | ((zx[rombuf+22])<<8) );
		_SP=(( zx[rombuf+23]) | ((zx[rombuf+24])<<8) );
		switch( zx[rombuf+25]) {
		case 0:	xIM( IM0 );	break;
		case 1:	xIM( IM1 );	break;
		default:xIM( IM2 );	break;
		}
		outb( 254, zx[rombuf+26], 0 ); // border
		xIFF1( IFF2() );
		if(zxfilesize==49179){
		  _R +=( 2 );
		  poppc();
		}else{ //128k
		  _PC=( (zx[rombuf+49179]) | ((zx[rombuf+49180])<<8) );
		  pport=zx[rombuf+49181];
      memcpy(mem+zxpage[pport&7],mem+0xc000,rompage);
		  //System.arraycopy(mem,0xc000,mem,zxpage[pport&7],rompage);
		  trdos=zx[rombuf+49182];
		  int off=49183;
		  for(int i=0;i<8;i++)
		    if(i!=2 && i!=5 && i!=(pport&7)){
          memcpy(mem+zxpage[i],zx+off,rompage);
		      //System.arraycopy(zx,off,mem,zxpage[i],rompage);
		      off+=rompage;
		    }
      memcpy(mem,mem+(((pport & 0x10)==0)?rom128:rom48),rompage);
		  //System.arraycopy(mem,((pport & 0x10)==0)?rom128:rom48,mem,0,rompage);
		}
    return true;
	}
	
	public void reg(int val, unsigned char *zx, int pos){
	  zx[pos]=(byte)val;
	  zx[pos+1]=(byte)(val>>8);
	}

	public void saveSNA(unsigned char *zx, int rombuf){
		exx();
		ex_af_af();
		zx[rombuf]=(byte)_I;
		reg(_HL,zx,rombuf+1);
		reg(_DE,zx,rombuf+3);
		reg(BC(),zx,rombuf+5);
		zx[rombuf+8]=(byte)_A;
		zx[rombuf+7]=(byte)F();
		exx();
		ex_af_af();
		reg(_HL,zx,rombuf+9);
		reg(_DE,zx,rombuf+11);
		reg(BC(),zx,rombuf+13);
		reg(_IY,zx,rombuf+15);
		reg(_IX,zx,rombuf+17);
	    zx[rombuf+19]=(byte)(_IFF2?4:0);
		zx[rombuf+20]=(byte)_R;
		zx[rombuf+22]=(byte)_A;
		zx[rombuf+21]=(byte)F();
		reg(_SP-2,zx,rombuf+23); ///////////////SP-2????????????????
		zx[rombuf+25]=(byte)((_IM==IM0)?0:((_IM==IM1)?1:2));
		zx[rombuf+26]=(byte)newBorder;
    memcpy(zx+rombuf+27,mem+16384,49152);
		//System.arraycopy(mem,16384,zx,rombuf+27, 49152 );
		if(fz128){
		  reg(_PC,zx,rombuf+49179);
		  zx[rombuf+49181]=pport;
		  zx[rombuf+49182]=trdos;
		  int off=49183;
		  for(int i=0;i<8;i++)
		    if(i!=2 && i!=5 && i!=(pport&7)){
          memcpy(zx+off,mem+zxpage[i],rompage);
		      //System.arraycopy(mem,zxpage[i],zx,off,rompage);
		      off+=rompage;
		    }
		}
	    zxfilesize=(fz128)?131103:49179;
	}

  private int loadZ80_page(unsigned char *zx, int i ){ // throws Exception {
		int k, tbyte, blocklen, addr, page;
		unsigned char bite;
		blocklen = (zx[i]) | ((zx[i+1]) << 8);
                i+=2;
		page=(zx[i++])-3;
		if(page<0 || page>7) return -1; //throw new Exception( "Z80 (page): out of range " + page );
		if(fz128){
          addr=zxpage[page];
		}else{
		//pport=2;
		switch(page){
		  case 5: addr = 0x4000; break;
		  case 1: addr = 0x8000; break;
		  case 2: addr = 0xc000; break;
		  default: fneed128=true; return -1; //throw new Exception( "128:" );
		}}
		k=i;
		while ( (i-k < blocklen) )
		  if ( (bite=zx[i++]) != (unsigned char)0xed ) mem[ addr++]= bite;
		  else 
			if ( (bite=zx[i++]) != (unsigned char)0xed ) { mem[addr++]=(unsigned char) 0xed; i--;}
			else {
			  tbyte = zx[i++];
			  bite = zx[i++];
			  while ( (tbyte--) > 0 ) mem[addr++]=bite;
			}	
		if ((addr & 16383) != 0)   return -1;
			//throw new Exception( "Z80 (page): overrun" );
		return i;
	}

  public boolean loadZ80(unsigned char *zx, int rombuf){ // throws Exception {
	  resetKeyboard();
	  //rp.fr128=false;
	  if (zxfilesize == 49179 || zxfilesize==131103 ){ return loadSNA(zx,rombuf); }
	    unsigned char bite;
		boolean compressed = false;
		int i,j, tbyte, addr, size, offset;
		_A=( zx[rombuf] );
		xF( zx[rombuf+1] );
		xBC( (zx[rombuf+2]) | ((zx[rombuf+3])<<8) );
		_HL=( (zx[rombuf+4]) | ((zx[rombuf+5])<<8) );
		_PC=( (zx[rombuf+6]) | ((zx[rombuf+7])<<8) );
		_SP=( (zx[rombuf+8]) | ((zx[rombuf+9])<<8) );
		_I=( zx[rombuf+10] );
		_R=( zx[rombuf+11] );
		tbyte = (zx[rombuf+12]);
		if ( tbyte == 255 ) tbyte = 1;
		outb( 254, ((tbyte >> 1) & 0x07), 0 ); // border
		if ( (tbyte & 0x01) != 0 ) 	xR( R() | 0x80 );
		compressed = ((tbyte & 0x20) != 0);
		_DE=( (zx[rombuf+13]) | ((zx[rombuf+14])<<8) );
		ex_af_af();
		exx();
		xBC( (zx[rombuf+15]) | ((zx[rombuf+16])<<8) );
		_DE=( (zx[rombuf+17]) | ((zx[rombuf+18])<<8) );
		_HL=( (zx[rombuf+19]) | ((zx[rombuf+20])<<8) );
		_A=( zx[rombuf+21]);
		xF( zx[rombuf+22]);
		ex_af_af();
		exx();
		_IY=((zx[rombuf+23]) | ((zx[rombuf+24])<<8) );
		_IX=((zx[rombuf+25]) | ((zx[rombuf+26])<<8) );
		xIFF1( zx[rombuf+27] != 0 );
		xIFF2( zx[rombuf+28] != 0 );
		switch ( zx[rombuf+29] & 0x03 ) {
		case 0:	xIM( IM0 );	break;
		case 1:	xIM( IM1 );	break;
		default:xIM( IM2 );	break;
		}
		if ( _PC == 0 ){ 
			switch( (zx[rombuf+30]) | (zx[rombuf+31]) << 8){
			case 23: size=23; bite=1; break;
			case 54: size=54; bite=6; break;
			case 58: size=58; bite=7; break;
			default: return false;
				//throw new Exception( "Z80 (extended): unsupported type ");
			}
			_PC=( (zx[rombuf+32]) | ((zx[rombuf+33])<<8) );
			if ( (tbyte=(zx[rombuf+34])) > bite ) 
			  return false;//???
        //throw new Exception( "Z80: unsupported type " + tbyte );
			if(fz128) pport=zx[rombuf+35];
			for ( offset = rombuf+32+size, j = 0; j < 8 && offset<rombuf+zxfilesize; j++ ) 
		 	  if((offset = loadZ80_page(zx,offset))==-1) return false;
		}else{
		if (! compressed ){
		  /*if(rp.fz128 && zxfilesize==131104){ //128k snap
		    for(i=0;i<8;i++){
		      j=i; if(j==2) j=-2; else if(j==5) j=-3;
		      System.arraycopy(mem,romstart+rompage*j,zx,32+i*rompage,rompage);
		    } swappage(zx[rombuf+30],false);
		  }else */
      memcpy(mem+16384,zx+rombuf+30,49152 );
		  //System.arraycopy(zx,rombuf+30,mem,16384,49152 );
		}else{
			addr=16384;
			size=rombuf+zxfilesize;
			i = rombuf+30;
			while ( (addr < 65536) && (i < size) )
		  	  if ( (bite=zx[i++]) != (unsigned char)0xed ) mem[ addr++]= bite;
			  else 
				if ( (bite=zx[i++]) != (unsigned char)0xed ) { mem[addr++]=(unsigned char) 0xed; i--;}
				else {
				  tbyte = zx[i++]&0xff;
				  bite = zx[i++];
				  while ( (tbyte--) != 0 ) mem[addr++]=bite;
	}	}	}
	if(fz128){
    memcpy(mem+rombank,mem+zxpage[pport&7],rompage);
	  //System.arraycopy(mem,zxpage[pport&7],mem,rombank,rompage);
    memcpy(mem,mem+(((pport & 0x10)==0)?rom128:rom48),rompage);
	  //System.arraycopy(mem,((pport & 0x10)==0)?rom128:rom48,mem,0,rompage);
    }
  return true;
  }

	public void saveZ80(unsigned char *zx, int rombuf){
		if(fz128 || fsna){ saveSNA(zx,rombuf); return;}
		//int i,j, addr;
		zx[rombuf]=(byte)_A;
		zx[rombuf+1]=(byte)F();
		reg(BC(),zx,rombuf+2);
		reg(_HL,zx,rombuf+4);
		reg(_PC,zx,rombuf+6);
		reg(_SP,zx,rombuf+8);
		zx[rombuf+10]=(byte)_I;
		zx[rombuf+11]=(byte)_R;
		zx[rombuf+12]=(byte)((((_R & 0x80)!=0)?1:0)|((newBorder & 0x07)<<1));
		reg(_DE,zx,13+rombuf);
		ex_af_af();
		exx();
		reg(BC(),zx,15+rombuf);
		reg(_DE,zx,17+rombuf);
		reg(_HL,zx,19+rombuf);
		zx[rombuf+21]=(byte)_A;
		zx[rombuf+22]=(byte)F();
		ex_af_af();
		exx();
		reg(_IY,zx,23+rombuf);
		reg(_IX,zx,25+rombuf);
		zx[rombuf+27]=(byte)(_IFF1?1:0);
		zx[rombuf+28]=(byte)(_IFF2?1:0);
		zx[rombuf+29]=(byte)((_IM==IM0)?0:((_IM==IM1)?1:2));
		memcpy(zx+rombuf+30,mem+16384,49152 );
                zxfilesize=49182;
	}

	/** Reset all registers */
	public void reset() {
		_PC=_SP=_A=_DE=_HL=0;
                xBC( 0 );
		xF( 0 );
		exx();
		ex_af_af();
		_A=_DE=_HL=_IX=_IY=_R=_I=0;
                xBC( 0 );
		xF( 0 );
		xIFF1( false );
		xIFF2( false );
		xIM( IM0 );
		outb( 254, 0xff, 0 );//
		resetKeyboard();//
		pport=0;
	}


public void zxpaintrotate() { // основной мелкий
    int x,y,xx,yy,yyy, col1, col2, col3, pal=22528, width4=width<<2, width_4=width-4;
	int b, off=16384, off2, off3, scr=0, scr2;
	for(yyy=0;yyy<3;yyy++){
	  off3=off;
  	  for(yy=0;yy<8;yy++){
  	    off2=off; scr2=scr;
	    for(xx=0;xx<32;xx++){
	      b=mem[pal++];
	      col3=(b>>3)&0x08;
	      col1=colors[(b & 0x07)|col3];
	      col2=colors[((b>>3)&0x07)|col3];
              for(y=0;y<4;y++){
                b=mem[off];
	        for(x=0;x<4;x++,scr++){
	          screen[scr]=((b & 0x80)!=0)?col1:col2;
	          b<<=2;
	        } //x
	        off+=512;
	        scr+=width_4;//124; //128-4
	      } //y
	      off-=2047; //(512*4-1);
	      scr-=width4-4;//508;  //(128*4-4);
	    } //xx
	    off=off2+32;
	    scr=scr2+width4;//512; //128*4;
	  } //yy
	  off=off3+2048; //256*8;
	}
}

public void zxpaintsmall() { // повернуто мелкий (с65 только)
	int x,y,xx,yy,yyy, col1, col2, col3, pal=22528;
	int b, off=16384, off2, off3, scr=width-1, width4=width<<2, scr2;
	if(frotate) for(b=0;b<screensize;b++) screen[b]=0; // ·РЫШвм дЮЭ
	for(yyy=0;yyy<3;yyy++){//3
	  off3=off;
  	  for(yy=0;yy<8;yy++){
  	    off2=off; scr2=scr;
	    for(xx=0;xx<32;xx++){
	      b=mem[pal++];
	      col3=(b>>3)&0x08;
	      col1=colors[(b & 0x07)|col3];
	      col2=colors[((b>>3)&0x07)|col3];
          for(y=0;y<4;y++){
            b=mem[off];
	        for(x=0;x<4;x++,scr+=width){
	          screen[scr]=((b & 0x80)!=0)?col1:col2;
	          b<<=2;
	        } //x
	        off+=512;
	        scr-=(width4)+1;
	      } //y
	      off-=2047; //(512*4-1);
	      scr+=(width4)+4;
	    } //xx
	    off=off2+32;
	    scr=scr2-4;
	  } //yy
	  off=off3+2048;//256*8;
	}
}

public void zxpaint() { // повернуто с "окошком"
	int x,y,xx,yy,yyy, col1, col2, col3, pal=22528+minx, dminy=miny, dy;
	int b, off=16384+minx, off2, off3, scr=width-1, width8=width<<3, scr2;
	for(yyy=dy=0;yyy<3 && dy<=maxy; yyy++){
	  off3=off;
	  if(dminy>0){
	    off+=dminy<<5;
	    pal+=dminy<<5;
	  }
  	  for(yy=0;yy<8-dminy && ++dy<=maxy; yy++){
  	    off2=off; scr2=scr;
	    for(xx=0;xx<maxx;xx++){//32
	      b=mem[pal++];
	      col3=(b>>3)&0x08;
	      col1=colors[(b & 0x07)|col3];
	      col2=colors[((b>>3)&0x07)|col3];
          for(y=0;y<8;y++){
            b=mem[off];
	        for(x=0;x<8;x++,scr+=width){
	          screen[scr]=((b & 0x80)!=0)?col1:col2;
	          b<<=1;
	        } //x
	        off+=256;
	        scr-=(width8)+1;
	      } //y
	      off-=2047;//(256*8-1);
	      scr+=(width8)+8;
	    } //xx
	    off=off2+32;
	    pal+=32-maxx;
	    scr=scr2-8;
	  } //yy
	  dminy=0;
	  off=off3+2048;//256*8;
	}
}


 void rotate(){ // Повернуть экран
  int i,j,k,l;
  if(C65){// && width==height){ //90 поворот на c65
    if(scrrot==null) scrrot=malloc(screensize);
    memcpy(scrrot,screen,screensize);
    l=0;
    for(j=0;j<width;j++){
      k=width-1-j;
      for(i=0;i<width;i++,l++,k+=width)
        screen[l]=scrrot[k];
    }
//    if(width==130){//fzx&&
      l=width-4;
      for(i=0;i<height;i++,l+=width)
        screen[l]=screen[l+1]=screen[l+2]=screen[l+3]=0;
      l=128*width;//screenlength;
      i=width<<2;
//      i=width+width;
      do screen[l++]=0;
      while(--i>0);
  }else
  for(i=(screensize>>1),j=i-1;i>0;){
    k=screen[--i]; screen[i]=screen[++j]; screen[j]=k;
  }
}

extern void zxrepaint(char *scrbuf, char *scr); // Повернутый экран
extern void zxelpaint(char *s, char *ss); //for EL
extern void zx65paint(char *s, char *ss); //x65


void onredraw(void){
  if(!mode){
    if(fzxrotate){ 
      zxpaintrotate(); 
    }else{ 
      if(!fzxsmall){ 
        if(C65) zxpaintsmall(); 
        else{
          zxrepaint(scrbuf,(char*)mem);
          if(EL71) zxelpaint(screen,scrbuf);
          else zx65paint(screen,scrbuf);
        }
      }else zxpaint(); //сюда тож
    }
    if(frotate && !fzxrotate) rotate();
  }else if(mode==99) drawhelp();
}

boolean loadini(){
  int f;
  char *ptr;
  *(ptr=file)='i'; *++ptr='n'; *++ptr='i'; *++ptr=0;
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))==-1) return false;
  if(fread(f, param, paramlength, &err)!=paramlength){ fclose(f,&err); return false;}
  fclose(f,&err);
  minx=param[95];
  miny=param[96];
  if(!(fps=(unsigned)param[97])) fps=262/6;
  if(!(tst=(unsigned)param[98])) tst=4;
  tstatesPerInterrupt=tst*20000;
  f=(unsigned)param[99];
  ldir=f&0x1;
//  fc65=f&0x2;
  frotate=f&0x4;
  fzxrotate=f&0x8;
  fzxsmall=f&0x10;
  maxx=(C65?130:height)>>3; //???
  return true;
}

boolean saveini(){
  int f;
  char *ptr;
  *(ptr=file)='i'; *++ptr='n'; *++ptr='i'; *++ptr=0;
  if((f=fopen(filename,A_ReadWrite+A_BIN+A_Create,P_READ+P_WRITE,&err))==-1) return false;

  param[95]=(char)minx;
  param[96]=(char)miny;
  param[97]=(char)fps;
  param[98]=(char)tst;
  param[99]=(ldir?0x1:0)|(frotate?0x4:0)|(fzxrotate?0x8:0)|(fzxsmall?0x10:0);
  
  fwrite(f, param, paramlength, &err);
  fclose(f,&err);
  return true;
}

boolean loadrom(){
  int f;
  char *ptr;
  if(fz128){ //128k
    if(mem && zx) return true;
    if(!mem) zx=malloc( rom48size );
    else{ zx=mem; mem=null;}
    mem=malloc( rom128size );
  }else{ //48k
    if(mem && !zx) return true;
    if(!zx) mem=malloc( rom48size );
    else{ mem=zx; zx=null;}
  }
  reset();    
    *(ptr=file)='4'; *++ptr='8'; *++ptr=0;
    if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))==-1) return false;
    if(fz128){
      if(fread(f, mem+rom48, rompage, &err)!=rompage){ fclose(f,&err); return false;}
      fclose(f,&err);
      *(ptr=file)='1'; *++ptr='2'; *++ptr='8'; *++ptr=0;
      if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))==-1) return false;
      if(fread(f, mem+rom128, rompage, &err)!=rompage){ fclose(f,&err); return false;}
      memcpy(mem,mem+rom128,rompage);
    }else{
      if(fread(f, mem+romstart, rompage, &err)!=rompage){ fclose(f,&err); return false;}
      memcpy(mem,mem+romstart,rompage);
    }
    fclose(f,&err);
    return true;
}

//int z80startret=0;

public boolean z80start(boolean isz80){
  if(mem==null) loadrom();
  if(isz80){
//    memcpy(mem,mem+(fz128?(((pport & 0x10)==0)?rom128:rom48):romstart),rompage);
      memcpy(mem,mem+romstart,rompage);
    //System.arraycopy(mem,fz128?(((pport & 0x10)==0)?rom128:rom48):romstart,mem,0,rompage);
    fneed128=false;
    if(!loadZ80((fz128)?zx:mem,(fz128)?0:rombuf1)){
//      if(!fneed128){ return false;}
      fneed128=true;
      fz128=true; loadrom();
      memcpy(zx,zx+rombuf1,zxfilesize);
      if(!loadZ80((fz128)?zx:mem,(fz128)?0:rombuf1)) return false;
    }
  }
  resetKeyboard();
  for(int i=0;i<screensize;i++) screen[i]=0; // Залить фон  
//  znostop=true;
//  thread.start();

//  repaint();
  return true;
}

boolean z80zipload(char *fname){
   char *buf;
   if(!(buf=loadfile(fname))) return false;
   if(fz128){ fz128=false; if(!loadrom()){ mfree(buf); return false;}}
   if(!fz128 && loadfilesize>rom48size-rombuf1){ 
     fz128=true; if(!loadrom()){ mfree(buf); return false;}
   }
   memcpy(fz128?zx:(mem+rombuf1),buf,zxfilesize=loadfilesize);
   mfree(buf);
   return true;
}

boolean z80load(int f){
   int size=lseek(f,0,2,&err,&err);
   if(fz128){ fz128=false; if(!loadrom()) return false;} 
   if(!fz128 && size>rom48size-rombuf1){ 
     fz128=true; if(!loadrom()) return false;
   }
   lseek(f,0,0,&err,&err);
   if((zxfilesize=fread32(f,fz128?zx:(mem+rombuf1),size,&err))!=size) return false; //?????
   return true;
}

void cls(){
  memset(screen,0,screensize);
//  for(int i=0;i<screensize;i++) screen[i]=0; // Залить фон  
}
///////////////////////////////////////////////////
//////////////////////////////////////////////////
volatile int xx=0, yy=0;

void timer_proc(void){
  if(!mode){
    REDRAW();
  }
  GBS_StartTimerProc(&timer,fps,timer_proc);
}

void start(){
  mode=0;
  cls();
  SUBPROC((void *)execute);
}


void oncreate(){
//   mode=0;
//   SUBPROC((void *)execute);
   start();
   GBS_StartTimerProc(&timer,262/20,timer_proc);
}


void key(int keyCode, int press){
  keyCode=param[100+alternate+keyCode-'0'];
  if(press) keylines[(keyCode>>4)&0x7]&=~(1<<(keyCode&0x7));
  else      keylines[(keyCode>>4)&0x7]|=(1<<(keyCode&0x7));
}

void getkkk(){ //count redkey
  if(!(redkey-='0'))  redkey=10;
  --count; --count;
  if(--redkey<6) param[100+alternate+rrkey-'0'] = param[redkey*4+(count%4)] ;
  else param[100+alternate+rrkey-'0'] = param[24+(redkey-6)*5+(count%5)] ;
}

//int method5(MAIN_GUI *data, GUI_MSG *msg)
int onkey(unsigned char keycode, int pressed){
  switch(pressed){
  case KEY_UP: // Клавиша отпущена
    if(!mode){
      if(keycode>='0' && keycode<='9') key(keycode,false);
      switch(keycode){
      case LEFT_BUTTON:if(miny<8) ++miny; break;
      case RIGHT_BUTTON: if(miny>0) --miny; break;
      case UP_BUTTON: if(minx>0) --minx; break;
      case DOWN_BUTTON:  if(minx<10) ++minx; break;
      }
    }return 0;
  case KEY_DOWN: case LONG_PRESS: // Кл. нажата или удерживается
  if(keycode==RED_BUTTON)  return(1); //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
  switch(mode){
  case 6: //redefine keys
    if(keycode>='0' && keycode<='9'){ 
      if(!count){ rrkey=keycode; ++count;}
      else{ redkey=keycode; ++count;}
    }else{
      if(count>0)  getkkk();
      start();
    }
    break;
  case 0: //zx starting
    if(keycode>='0' && keycode<='9') key(keycode,true);
    switch(keycode){
    case RIGHT_SOFT: 
      mode=99;
      onredraw(); DrawScreen();
      return 0;
      //for(i=0;i<screenlength;i++) screen[i]=0xff;
      //draw menu
      //break;
    case LEFT_SOFT: if(alternate) alternate=0; else alternate=17; break;
    case GREEN_BUTTON: mode=6; count=0; break; //redefine
    case LEFT_BUTTON:if(miny<8) ++miny; break;
    case RIGHT_BUTTON: if(miny>0) --miny; break;
    case UP_BUTTON: if(minx>0) --minx; break;
    case DOWN_BUTTON:  if(minx<10) ++minx; break;
    }break;
  case 1: //Load
    loadsave(keycode, false);
    loadZ80(fz128?zx:mem,fz128?0:rombuf1);
    start(); break;
  case 2: //Save
    saveZ80((fz128)?zx:mem,(fz128)?0:rombuf1);
    loadsave(keycode, true);
    start(); break;  
  case 3: //fps
    if(keycode>='0' && keycode<='9'){
      //fps=262/(keycode=='0'?20:((keycode-'0')*2)); //ДЕЛЕНИЯ НЕТ???????????????
      fps=fpstab[keycode-'0'];
    }start(); break;
  case 4: //interrupt
    if(keycode>'0' && keycode<'6'){
      tst=(keycode-'0');
      tstatesPerInterrupt=tst*20000;
    }start(); break;
  case 99: //main menu
    switch(keycode){
    case '1': mode=1; break;  //Load
    case '2': mode=2; break;  //Save
    case '3': mode=3; break; //fps
    case '4': mode=4; break; //interrupt
//    case '5': ldir=!ldir; start(); break; //optimize
//    case '6': cls(); fc65=!fc65; //fc65
//      minx=miny=0;
//      maxx=(fc65?130:176)>>3;
//      start(); break; 
    case '7': cls();
      if(fzxrotate) frotate=!frotate;
      fzxrotate=!fzxrotate;
      start(); break;
    case '8': cls(); fzxsmall=!fzxsmall; start(); break;
    case '0': return(1);
    default: start(); break;
    }break;
  default: start(); break;
  }
//  onredraw(); DrawScreen();
  }
  return 0;
}

void onexit(){
  if(mem) mfree(mem);
  if(zx) mfree(zx);
  if(scrrot) mfree(scrrot);
}

void onclose(){
  mode=100;
//  debsave();//!!!!!!!!
  GBS_DelTimer(&timer);
  saveini();
}

void loadsave(int num, boolean save){
  char *ptr;
  int f;
  if(num<'0' || num>'9') return;
  *(file-1)=(byte)num; *(ptr=file)='.'; *++ptr='z'; *++ptr='8'; *++ptr='0'; *++ptr=0;
  if(!save){ //load
    f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err);
    *(file-1)='.';
    if(f==-1) return;
    if(!z80load(f)){ fclose(f,&err); return;}
    fclose(f,&err);
    if(!z80start(true)) return; 
  }else{ //save
    f=fopen(filename,A_ReadWrite+A_BIN+A_Create,P_READ+P_WRITE,&err);
    *(file-1)='.';
    if (f==-1) return;
    saveZ80((fz128)?zx:mem,(fz128)?0:rombuf1); 
    fwrite32(f,(fz128)?zx:mem+((fz128)?0:rombuf1),zxfilesize,&err);
    //file.truncate(handle,i);
    fclose(f,&err);
  }
}

const char *errors[]={
  "",
  "Щелкните на .z80 файл",
  "Файл настроек .ini не найден!",
  "Не могу загрузить ром",
  "Ошибка загрузки",
  "128k Roms not supported!"
};

int onstart(char *exename, char *fname){
    if(!fname) return 1;
    maxy=width>>3;
    fz128=false;
    initparity(); //!!!
    strcpy(filename,exename);
    file=filename+strlen(filename);
    while(file>filename && *--file!='.');
    ++file;
    if(!loadini()) return 2;
    if(!loadrom()) return 3;
    if(!z80zipload(fname)) return 4;
    if(!z80start(true)) return 5; 
    return 0; 
}

//void debsave(){
//  char *ptr;
//  int f;
//  *(ptr=file)='l'; *++ptr='o'; *++ptr='g'; *++ptr=0;
//  f=fopen(filename,A_ReadWrite+A_BIN+A_Create,P_READ+P_WRITE,&err);
//  if (f==-1) return;
//  fwrite(f,mem+0x10000,debpos-0x10000,&err);
//  fclose(f,&err);
//}
