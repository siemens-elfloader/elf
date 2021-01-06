

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
        mrand();    
                   
                   
}



int mrand(void)
{
        Seed.lo = 0x015a4e35L * Seed.lo + 1;
        return((int)(Seed.lo >> 16) & 0x7fff);
}
