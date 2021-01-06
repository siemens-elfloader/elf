/*
                          Siemens AG
                     Mobile Radio Terminals
                       Munich,  Germany
                     COMPANY CONFIDENTIAL
                     All Rights Reserved

.AUTHOR         J. Kuenstner, ICP CD MP GSM RD M57

.PROJECT        SWUPDEMO

.SHORT_DESCR    Main-Program for SWUPDEMO


.SW_COMPONENT

.SW_TYPE

.VERSION        1.8

.DATE           2004-08-26

.EXIT_CODES

.STATUS         FIRST_TRY

.CHANGE_CONTROL

Version |  Date    | Changed by | Reason for Change
--------+----------+------------+-----------------------
 1.0    |05.03.2000| Jogi       | Modul created
--------+----------+------------+-----------------------
 1.1    |20.04.2001| Jogi       | New interface to library because of consistence-check-callback !
--------+----------+------------+-----------------------
 1.2    |2001-06-18| Jogi       | New functions for library-init and to to test new update-concept
--------+----------+------------+-----------------------
 1.3    |2001-06-29| W. Hettich | testnew heap method,some ugly testdefines, but lintable now
--------+----------+------------+-----------------------
 1.4    |2001-08-07| W. Hettich | uses new close up function from heaplib
--------+----------+------------+-----------------------
 1.5    |2001-09-07| JKue       | changed to use new error-demo 
--------+----------+------------+-----------------------
 1.6    |2001-09-17| PMackenthun| Sleep() inserted
--------+----------+------------+-----------------------
 1.7    |2004-01-30| J.Garrido  | Use set BFC callbacks function.
--------+----------+------------+-----------------------
 1.8    |2004-08-26| J.Garrido  | Case the comport is not given try to find the mobile.


.STILL_TODO

*/

/* INDENT: -nbr -nce -ei -ip -lp -pro -sc -c:33 -cci:3 -cd:33 -ci:3 -cli:3 -cp:0 -d:0 -di:0 -i:3 -l:78 -lc:78 -tabs:3  -tabu */


/*  ***  INCLUDES  ***  ***************************************************** */

#include <windows.h>
// #include <ansi_c.h>    /* cvi inserted */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>     /* stat */
#include <io.h>           /* access() */

#include "wswuplib.h"
#include "err_demo.h"

/*  ***  DEFINES  ***  ****************************************************** */

/*  ***  TYPEDEFS ***  ****************************************************** */

/*  ***  EXTERNALS  ***  **************************************************** */

/*  ***  CONSTANTS ***  ***************************************************** */

/*  ***  VARIABLES  ***  **************************************************** */

unsigned long ulAmountUpdateData;
unsigned long ulGlobalMaxVal;
volatile BOOL fErrorOccured = FALSE;   /* must be volatile, because otherwise it will be optimized away in the Busy-Loop  */
volatile BOOL fSuccessOccured = FALSE;

/*lint -e528, szErrorMsg: access only by function */
static char szErrorMsg[255] = {'\0'};


/*  ***  PROTOTYPES  ***  *************************************************** */
static BOOL MallocHeapAndReadFile(unsigned char **ppucLocalHeap, unsigned long *pulBytesInHeap, char *pszFileName );

/*  ***  MODUL COMMENTS  ***  *********************************************** */

/*  ***  FUNCTIONS  ***  **************************************************** */
void ShowFileReadProgress( unsigned long ulMaxVal, unsigned long ulAktVal )
{
   printf("Read %ld Bytes of %ld Bytes\r",ulAktVal,ulMaxVal );
}

/*lint -esym(715, unUpdateNr) */
void ShowVoltageCheckProgress( WORD unUpdateNr, unsigned int unMaxCalls, unsigned int unCurrCall )
{
   printf("." );
   if( unCurrCall == unMaxCalls )
   {
      printf("\n");
   }
}
/*lint +esym(715, unUpdateNr) */

/*lint -esym(715, unDlgBoxNumber) */
void ShowUpdateCheckProgress( WORD unDlgBoxNumber, unsigned int unMaxCalls, unsigned int unCurrCall )
{
   if( unCurrCall == 1 )
   {
      printf("Testing new SW " );
   }
   printf("." );
   if( unCurrCall == unMaxCalls )
   {
      printf("\n");
   }
}
/*lint +esym(715, unDlgBoxNumber) */


/*lint -esym(715, unDlgBoxNumber) */
void UpdateSwTransmissionStart( WORD unDlgBoxNumber, unsigned long ulMaxVal )
{
   ulAmountUpdateData = ulMaxVal;
   printf("Transmitting Update-SW" );
}
/*lint +esym(715, unDlgBoxNumber) */

/*lint -esym(715, unDlgBoxNumber) */
void ShowUpdateSwTransmissionProgress( WORD unDlgBoxNumber, unsigned long ulAktVal )
{
   printf( "." );
   if( ulAmountUpdateData == ulAktVal )
   {
      printf("\n");
   }
}
/*lint +esym(715, unDlgBoxNumber) */


/*lint -esym(715, wUpdateNr) */
void ShowFlashBlocksEraseProgress( WORD wUpdateNr, WORD wMaxAmount , WORD wAmountBlocksErased  )
{
   printf( "Erasing %3d of %3d Flashblocks\r", wAmountBlocksErased , wMaxAmount );
   if( wAmountBlocksErased == wMaxAmount )
   {
      printf( "\n" );
   }
}
/*lint +esym(715, wUpdateNr) */


/*lint -esym(715, wDlgBoxNumber) */
void ShowBootStrapProgress( WORD wDlgBoxNumber, WORD wMaxAmount , WORD wCurrAmount  )
{
   if( wCurrAmount == 1 )
   {
      printf("Connecting to Mobile " );
   }
   printf( "." );
   if( wCurrAmount == wMaxAmount )
   {
      printf("\n" );
   }
}
/*lint +esym(715, wDlgBoxNumber) */

/*lint -esym(715, unDlgBoxNumber) */
void StartTransmission( WORD unDlgBoxNumber, unsigned long ulBytesToTransfer  )
{
   ulGlobalMaxVal = ulBytesToTransfer;
}
/*lint +esym(715, unDlgBoxNumber) */


/*lint -esym(715, unDlgBoxNumber) */
void ShowMobileSwTransmissionProgress( WORD unDlgBoxNumber, unsigned long ulAktVal )
{
   printf("Transfering new Mobile-SW %4ld kByte\r" , ulAktVal / 1024 );
   if( ulAktVal == ulGlobalMaxVal )
   {
      printf("\n");
   }
}
/*lint +esym(715, unDlgBoxNumber) */


/*lint -esym(715, wUpdateNr) */
/*lint -esym(715, *pszFlashString) */
void ShowFlashCode( WORD wUpdateNr, WORD wFlashCode , char * pszFlashString )
{
   printf( "Flash-Code %04X\n", wFlashCode  );
}
/*lint +esym(715, *pszFlashString) */
/*lint +esym(715, wUpdateNr) */

/*lint -esym(715, wUpdateNr) */
void UpdateSuccess( WORD wUpdateNr )
{
   printf( "Success occurred \n" );
   fSuccessOccured = TRUE;
}
/*lint +esym(715, wUpdateNr) */


/*lint -esym(715, wUpdateNr) */
void UpdateError( WORD wUpdateNr )
{
   printf( "Error occurred \n" );
   fErrorOccured = TRUE;
}
/*lint +esym(715, wUpdateNr) */

/*lint -esym(715, wUpdateNr) */
BOOL AskForConsistenceProblem( WORD wUpdateNr, t_SwInformation * pMobileInfo, t_SwInformation * pNewSwInfo, WORD wErrorComposition )
{
   char szErrorString[1000];
   int c;
   switch( wErrorComposition )
   {
      case CONSISTENCE_PRODUCT_ERROR:
         (void)wsprintf( szErrorString, "You are trying to update a SW for a %s into a %s",pNewSwInfo->szProductType, pMobileInfo->szProductType );
         break;
      case CONSISTENCE_SWVERSION_ERROR:
         (void)wsprintf( szErrorString, "You are trying to update a SW Version %s into a Mobile with %s",pNewSwInfo->szProductSVN, pMobileInfo->szProductSVN );
         break;
      case CONSISTENCE_SWDATE_ERROR:
         (void)wsprintf( szErrorString, "You are trying to update a SW with Date %s into a Mobile with %s",pNewSwInfo->szCompileDate, pMobileInfo->szCompileDate );
         break;
      case ( CONSISTENCE_SWDATE_ERROR | CONSISTENCE_SWVERSION_ERROR ) :
         (void)wsprintf( szErrorString, "You are trying to update a SW Version %s with Date %s into a Mobile with Version %s Date %s",pNewSwInfo->szProductSVN,
                                                                                          pNewSwInfo->szCompileDate,
                                                                                                   pMobileInfo->szProductSVN,
                                                                                                   pMobileInfo->szCompileDate );
         break;
      default:;
   }
   strcat( szErrorString,"\nDo you want to continue ?");
   printf( "%s\nPress y or j to continue, any other key to abort : ", szErrorString  );
   c = getchar();
   c= toupper( c );
   printf("c=\"%c\"\n",c );
   if(( c == 'J' ) || (  c == 'Y' ))
   {
      return TRUE;
   }
   else
   {
      return FALSE;
   }
}
/*lint +esym(715, wUpdateNr) */




void main( int argc, char **argv  )
{
   t_SwupCom MyCom = SwupCom4;
   t_SwInformation InformationAboutSoftware;
   BOOL fLocalErrorOccured ;
   BOOL fLocalSuccessOccured ;
   unsigned long ulBaudRate;
   WORD wUpdateNr = 0;

   unsigned char * pucHeap;
   unsigned long ulBytesInHeap;
   WORD unVoltage;

   char ComName[256];
   char ComDesc[256];
   unsigned int Option = START_COM_SEARCH;
   BOOL found = FALSE;

   if( argc < 3 )
   {
      printf( "Call swupdemo Baudrate File [PortNr]\n");
      exit( 1 );
   }
   
   ulBaudRate = strtoul( argv[1], NULL, 10 );     
   
   if (argc == 4 )
   {
      MyCom = (t_SwupCom)(strtoul( argv[3],NULL,10 ) - 1);
      found = TRUE;
   }
   
   while (!found)
   {	   
       ComName[0] = 0;

       if (!WSwup_SearchAvaliableComPort ( ComName,ComDesc, Option  ))
       {
           printf ("Error looking for pc seial ports\n");
           return;
       }
       if (ComName[0] == 0)
       {
           printf ("No mobile Found\n");
           return;
       }

       sscanf (ComName + 3, "%d", &MyCom);
       MyCom--;

       if (!WSwup_LookForMobile(MyCom, 115200))
       {
		   printf( "Not possible to find the mobile :%d %s %s \n",MyCom,ComName, WSwup_GetLastErrorString( 0 ));		   
       }
       else 
       {
            printf( "found the mobile :%d %s \n",MyCom,ComName);
            found = TRUE;
       }

       Option = CONTINUE_COM_SEARCH;
   }

   printf( "Running SWUPDEMO on Port %d with %ld Baud with File %s\n",  (int)MyCom +1 , ulBaudRate, argv[2] );

   if( WSwup_InitLibrary( WSWUPLIB_INTERFACE_VERSION_MAJOR, WSWUPLIB_INTERFACE_VERSION_MINOR  ) == FALSE )
   {
      printf( "Error on LIB-INIT : %s \n", WSwup_GetLastErrorString( wUpdateNr  ));
      return;
   }
    // uncomment the following line, if you want to compile a SWUP with old behaviour
    // ( old behaviour is impossible for consumer-update with the real library  !!! )
    WSwup_SetUpdateConceptMode( enForceNewConcept );

   /* move file to heap, thats what a customer-tool-programmer has to do  */
   if ( FALSE == MallocHeapAndReadFile( &pucHeap, &ulBytesInHeap, argv[2] ))
      exit(1);

   /* check heap contents and prepare SW-Update */
   if ( WSwup_ReadXbiFileFromHeap( &InformationAboutSoftware,
                                   pucHeap,
                                   ulBytesInHeap ) )
   {
      WSwup_InstallBfcCallBackFunctions(  ShowVoltageCheckProgress, ShowUpdateCheckProgress );

      WSwup_InstallSoftwareUpdateCallBackFunctions(   ShowBootStrapProgress,
                                                      UpdateSwTransmissionStart,
                                                      ShowUpdateSwTransmissionProgress,
                                                      ShowFlashCode,
                                                      ShowFlashBlocksEraseProgress,
                                                      StartTransmission,
                                                      ShowMobileSwTransmissionProgress,
                                                      UpdateSuccess,
                                                      UpdateError,
                                                      AskForConsistenceProblem );
      printf("\nThis SW for %s , %s of %s\n", InformationAboutSoftware.szProductType,
                                            InformationAboutSoftware.szProductSVN,
                                            InformationAboutSoftware.szCompileDate );

      printf( "Checking voltage " );
      if( WSwup_CheckUpdateVoltage( 0 , MyCom , &unVoltage, ulBaudRate  ) != TRUE )
      {
         printf( "Error on Voltage-Check: %s\n", ErrDemo_GetLastErrorString( wUpdateNr ));
         free(pucHeap);
         return;
      }
      if( unVoltage < 3400 )
      {
         printf( "Voltage %d.%03d is to low, please charge", unVoltage / 1000, unVoltage % 1000 );
         free(pucHeap);
         return;
      }
      else
      {
         printf( "Voltage : %d.%03d V\n",unVoltage / 1000 ,unVoltage % 1000 );
         if( WSwup_PerformSoftwareUpdate( wUpdateNr, MyCom, ulBaudRate ) == FALSE )
         {
            printf( "Error on Start Update : %s\n", ErrDemo_GetLastErrorString( wUpdateNr ));
            free(pucHeap);
            return ;
         }
         else
         {
            fLocalErrorOccured = FALSE;
            fLocalSuccessOccured = FALSE;
            while( ( fLocalErrorOccured == FALSE ) && ( fLocalSuccessOccured == FALSE ))
            {
               fLocalErrorOccured = fErrorOccured ;
               fLocalSuccessOccured = fSuccessOccured;
			   Sleep(100);	// give some processor time to other applications
            }
            if( fErrorOccured )
            {
               printf( "Error on Update : %s\n", ErrDemo_GetLastErrorString( wUpdateNr ));
            }
            else
            {
               if( WSwup_CheckUpdateSuccess( wUpdateNr , MyCom ) != TRUE )
               {
                  printf("\nError on testing new SW : %s\n", ErrDemo_GetLastErrorString( wUpdateNr ));
               }
               else
               {
                  printf( "Mobile-SW works ...\n");
               }
            }
         }
      }
   }
   else
   {
      printf( "Error on Reading : %s\n", ErrDemo_GetLastErrorString( wUpdateNr ));
   }
   WSwup_CloseXbiFileHeap( );
   free( pucHeap );
   
}


static BOOL MallocHeapAndReadFile(unsigned char **ppucLocalHeap, unsigned long *pulBytesInHeap, char *pszFileName )
{
   FILE *fp;
   unsigned char * pucXbiInHeap;
   struct stat file_stat;
   unsigned long ulFileSize;
   unsigned long ulReadBytes;

   /* get file size */
   if (stat(pszFileName, &file_stat) == 0)
   {
      ulFileSize = (unsigned long) file_stat.st_size;
   }
   else
   {
      return FALSE;
   }

   /* get heap for file to read */
   pucXbiInHeap = ( unsigned char * ) malloc( (size_t) ulFileSize );
   if( pucXbiInHeap == NULL  )
   {
      printf( "\nCould not allocate %lu Bytes for XBI-File", ulFileSize );
      return FALSE;
   }

   /* open file */
   fp = fopen( pszFileName, "rb"  );

   /* read complete file to heap */
   ulReadBytes = fread( pucXbiInHeap, sizeof( unsigned char ), (size_t) ulFileSize, fp );
   if ( ferror(fp) )
   {
      printf("\nfread error!");
      fclose( fp );
      free( pucXbiInHeap );
      return FALSE;
   }
   /* passed end of file */
   if ( feof(fp) )
   {
      fp = fp; // just for debugging cases
   }
   /* all data now in heap , close file */
   fclose( fp );

   /* init parameter out */
   *ppucLocalHeap = pucXbiInHeap;
   *pulBytesInHeap = ulReadBytes;
   return TRUE;
}

