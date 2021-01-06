
#include "shared.h"

//static uint8 block[0x4000];
/*
void deinterleave_block(uint8 *src)
{
    int i;
    memcpy(block, src, 0x4000);
    for(i = 0; i < 0x2000; i += 1)
    {
        src[i*2+0] = block[0x2000 + (i)];
        src[i*2+1] = block[0x0000 + (i)];
    }
}
*/
int load_rom(char *filename){
//    uint8 *block, *ptr;
    int i;
    //if(!(cart_rom=(uint8*)loadfile(filename))) return 0;
    if(i=fmapopen(filename, &fmap, 5)) return i;
    if(((cartromsize=loadfilesize) / 512) & 1) return 1;
/*    { //smd
      if(!(block=(uint8*)malloc(0x4000))) return 0;
      memcpy(cart_rom,cart_rom+512, cartromsize-=512);
      for(ptr=cart_rom; ptr<cart_rom+cartromsize; ){//ize / 0x4000); i ++){
        memcpy(block,ptr,0x4000);
        for(i = 0; i < 0x2000; i ++){
          *ptr++=block[0x2000+i];
          *ptr++=block[0x0000+i];
        }
        //deinterleave_block(cart_rom + (i * 0x4000));
      }
      mfree(block);
    }*/
    return 0;
}



