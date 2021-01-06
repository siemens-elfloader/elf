#ifdef WIN32
/* 
 * File Name:       code.c
 * Author:			Han Josen
 * Start Date:		Dec 03 , 2003
 * Language:        Microsoft Visual C++ 6.0
 * Target:			Codec for AMR file
 * Summary:			This file contains the functions to decompress amr to wav
 *	 
 * Change Note:     
 */

/*
********************************************************************************
*                         INCLUDE FILES
********************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "typedef.h"




/*
********************************************************************************
*                             MAIN PROGRAM 
********************************************************************************
*/
int main (int argc, char *argv[]) 
{
	if( argc < 3 )
		return 0 ;
	decodeOneAmrFile (  argv[1] , argv[2] ) ;		
	_CrtDumpMemoryLeaks();
	return 1;
}


#endif