#ifndef _ADDR_H_
  #define _ADDR_H_
  
#ifdef E71Cv41
#define RamSMSNum	0xA8F1F519 //1.????8C3C201C????????7068  2.ida 3.-0x153
//*(7168002088847068+18)-153
#define uitostr		0xA050F42C+1 //BFB50C1C69460C22
#define	RamUnuse  0xA8D88E00
#endif

#ifdef S7Cv47
#define RamSMSNum	0xA8E57DED
#define uitostr		0xA01F71AC+1
#define	RamUnuse  0xA8A7F020
#endif
  
#ifdef ELC1v41
#define RamSMSNum	0xA8F1EDCD
#define uitostr		0xA0514FC8+1
#define	RamUnuse  0xA8D88E00
#endif

#ifdef S68Cv51
#define RamSMSNum	0xA8E48239
#define uitostr		0xA01B94D8+1
#define	RamUnuse  0xA8D7B800
#endif

#ifdef M81Cv51
#define RamSMSNum	0xA8ED6AED
#define uitostr		0xA01F687C+1
#define	RamUnuse  0xA8D80010
#endif

#ifdef SL7Cv47
#define RamSMSNum	0xA8E57D7D
#define uitostr		0xA01F71AC+1
#define	RamUnuse  0xA8A7F020
#endif

#ifdef SK6Cv50
#define RamSMSNum	0xA8F40DD9
#define	RamUnuse  0xA80001C0
#endif

#endif

#ifdef C81Cv50
#define RamSMSNum	0xA8ED6AED  //
#define uitostr		0xA01F6758+1
#define	RamUnuse  0xA8ED0730 //Î´¸Ä.Ô­Ê¼S7CV47
#endif
