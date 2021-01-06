double fabs(double arg)
{
  return(arg < 0 ? -arg : arg);
}


static long sqtab[64] =
{
        0x6cdb2, 0x726d4, 0x77ea3, 0x7d52f, 0x82a85, 0x87eb1, 0x8d1c0, 0x923bd,
        0x974b2, 0x9c4a8, 0xa13a9, 0xa61be, 0xaaeee, 0xafb41, 0xb46bf, 0xb916e,
        0xbdb55, 0xc247a, 0xc6ce3, 0xcb495, 0xcfb95, 0xd41ea, 0xd8796, 0xdcca0,
        0xe110c, 0xe54dd, 0xe9818, 0xedac0, 0xf1cd9, 0xf5e67, 0xf9f6e, 0xfdfef,
        0x01fe0, 0x05ee6, 0x09cfd, 0x0da30, 0x11687, 0x1520c, 0x18cc8, 0x1c6c1,
        0x20000, 0x2388a, 0x27068, 0x2a79e, 0x2de32, 0x3142b, 0x3498c, 0x37e5b,
        0x3b29d, 0x3e655, 0x41989, 0x44c3b, 0x47e70, 0x4b02b, 0x4e16f, 0x51241,
        0x542a2, 0x57296, 0x5a220, 0x5d142, 0x60000, 0x62e5a, 0x65c55, 0x689f2,
};

double sqrt(double arg)
{
        int e, ms;
        double a, t;
        union
        {
                double  d;
                struct
                {
                        long    ms;
                        long    ls;
                };
        } u;

        u.d = arg;
        ms = u.ms;

        /*
         * sign extend the mantissa with
         * exponent. result should be > 0 for
         * normal case.
         */
        e = ms >> 20;
        if(e <= 0) 
        {
                if(e == 0) return 0;
                return 0;
        }

        /*
         * pick up arg/4 by adjusting exponent
         */
        u.ms = ms - (2 << 20);
        a = u.d;

        /*
         * use 5 bits of mantissa and 1 bit
         * of exponent to form table index.
         * insert exponent/2 - 1.
         */
        e = (((e - 1023) >> 1) + 1022) << 20;
        u.ms = *(long*)((char*)sqtab + ((ms >> 13) & 0xfc)) | e;
        u.ls = 0;

        /*
         * three laps of newton
         */
        e = 1 << 20;
        t = u.d;
        u.d = t + a/t;
        u.ms -= e;              /* u.d /= 2; */
        t = u.d;
        u.d = t + a/t;
        u.ms -= e;              /* u.d /= 2; */
        t = u.d;

        return t + a/t;
}










#define DBL_MAX_EXP 1024
static double pow2tab[DBL_MAX_EXP + 1];

static int init(void)
{
        register int    x;
        double          g;

        g = 1;
        for (x = 0; x <DBL_MAX_EXP + 1; x++)
        {
                pow2tab[x] = g;
                g *= 2;
        }
        return 0;
}

#define INIT()          (pow2tab[0]?0:init())
#define pow2(i)         pow2tab[i]
double frexp(double f, int* p)
{
        register int    k;
        register int    x;
        double          g;

        INIT();

        /*
         * normalize
         */

        x = k = DBL_MAX_EXP / 2;
        if (f < 1)
        {
                g = 1.0L / f;
                for (;;)
                {
                        k = (k + 1) / 2;
                        if (g < pow2(x))
                                x -= k;
                        else if (k == 1 && g < pow2(x+1))
                                break;
                        else
                                x += k;
                }
                if (g == pow2(x))
                        x--;
                x = -x;
        }
        else if (f > 1)
        {
                for (;;)
                {
                        k = (k + 1) / 2;
                        if (f > pow2(x))
                                x += k;
                        else if (k == 1 && f > pow2(x-1))
                                break;
                        else
                                x -= k;
                }
                if (f == pow2(x))
                        x++;
        }
        else
                x = 1;
        *p = x;

        /*
         * shift
         */

        x = -x;
        if (x < 0)
                f /= pow2(-x);
        else if (x < DBL_MAX_EXP)
                f *= pow2(x);
        else
                f = (f * pow2(DBL_MAX_EXP - 1)) * pow2(x - (DBL_MAX_EXP - 1));
        return f;
}




#define log2    0.693147180559945309e0
#define ln10o1  .4342944819032518276511
#define sqrto2  0.707106781186547524e0
#define p0      -.240139179559210510e2
#define p1      0.309572928215376501e2
#define p2      -.963769093377840513e1
#define p3      0.421087371217979714e0
#define q0      -.120069589779605255e2
#define q1      0.194809660700889731e2
#define q2      -.891110902798312337e1

double log(double arg)
{
        double x, z, zsq, temp;
        int exp;
        
        if(arg <= 0) return 0;
        x = frexp(arg, &exp);
        while(x < 0.5) 
        {
                x *= 2;
                exp--;
        }
        if(x < sqrto2) 
        {
                x *= 2;
                exp--;
        }

        z = (x-1) / (x+1);
        zsq = z*z;

        temp = ((p3*zsq + p2)*zsq + p1)*zsq + p0;
        temp = temp/(((zsq + q2)*zsq + q1)*zsq + q0);
        temp = temp*z + exp*log2;
        return temp;
}

double log10(double arg)
{
   if(arg <= 0) return 0;
   return log(arg) * ln10o1;
}





