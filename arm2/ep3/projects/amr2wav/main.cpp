/*
* amr2wav
* 2011
*/


#include <swilib.h>
#include "decode.h"



int main(char *exename, char *fname)
 {

    if( decodeOneAmrFile(  "0:\\1.amr" , "0:\1.wav") ) ShowMSG(1,(int)"converted!");
    else  ShowMSG(1,(int)"error");


    return 0;
 }
