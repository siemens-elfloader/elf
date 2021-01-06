#define MULTIPLIER      0x015a4e35L
#define INCREMENT       1


typedef struct
{
	unsigned lo;
	unsigned hi;
} __seed_t;

static  __seed_t  Seed = { 1, 0 };

int mrand(void);

void msrand(unsigned seed)
{
        Seed.lo = seed;
        Seed.hi = 0;
        mrand();    // primes the seed by using the first number which
                   // is usually not as random as the subsequent numbers
                   // are.
}



int mrand(void)
{
        Seed.lo = MULTIPLIER * Seed.lo + INCREMENT;
        return((int)(Seed.lo >> 16) & 0x7fff);
}

int mrandom(int max)
{
  return mrand()%(max+1);
}
