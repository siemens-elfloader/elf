/*                        Siemens AG
                     Mobile Radio Terminals
                       Munich,  Germany
                     COMPANY CONFIDENTIAL
                     All Rights Reserved

.AUTHOR         J. Kuenstner, ICP CD MP GSM RD M57

.PROJECT        SWUPDEMO

.SHORT_DESCR    Error-Handling-Demo for SWUPDEMO


.SW_COMPONENT

.SW_TYPE

.VERSION        1.2

.DATE           2002-09-04

.EXIT_CODES

.STATUS         FIRST_TRY

.CHANGE_CONTROL

Version |  Date    | Changed by | Reason for Change
--------+----------+------------+-----------------------
 1.0    |2001-09-06| Jogi       | Modul created
--------+----------+------------+-----------------------
 1.1    |2002-09-03| D. Dittmer | Necessary changes to create the exe-files.
--------+----------+------------+-----------------------
 1.2    |2002-09-04| D. Dittmer | Change some comments for better understanding.
--------+----------+------------+-----------------------

.STILL_TODO

*/

/* INDENT: -nbr -nce -ei -ip -lp -pro -sc -c:33 -cci:3 -cd:33 -ci:3 -cli:3 -cp:0 -d:0 -di:0 -i:3 -l:78 -lc:78 -tabs:3  -tabu */


/*  ***  INCLUDES  ***  ***************************************************** */
#include <windows.h>
#include "wswuplib.h"
#include "werrenum.h"
#include "err_text.h"
#include "err_demo.h"

/*  ***  DEFINES  ***  ****************************************************** */

/*  ***  TYPEDEFS ***  ****************************************************** */

/*  ***  EXTERNALS  ***  **************************************************** */

/*  ***  CONSTANTS ***  ***************************************************** */

/*  ***  VARIABLES  ***  **************************************************** */

static BOOL fEndUserBehaviour =  TRUE;  /**< setting this variable to FALSE causes to more detailed 
                                             error-messages for development.
                                             So in a customer-update this variable has to be set to TRUE */ 

/*  ***  PROTOTYPES  ***  *************************************************** */

/*  ***  MODUL COMMENTS  ***  *********************************************** */


/*  ***  FUNCTIONS  ***  **************************************************** */


  



/**
 *
 * Does a special sprintf with the given information from the new internal error-information.
 *
 * \param pszFinalString : pointer to the destination-string like in sprintf
 * \param pszErrorDescription : pointer to the format-string like in sprintf
 * \param pErrStruct : pointer to the additional error-information
 *
 *
 * \return void
 *
 *
 */

static void SpecialSprintf( char * pszFinalString, char * pszErrorDescription, t_ErrorStruct * pErrStruct )
{
    char * pszDestPtr;      // pointer into the final string
    char * pszErrorFmPtr;   // pointer into the given description
    WORD wOutPutCharCount;  // counts the characters in the output-buffer
    char * pOwnFormatString; // points to our own simplified format-string
    WORD wStringBufferIndex = 0;
    WORD wLongBufferIndex = 0;

    char szFormatBufferForSprintf[20];  // to store the format for sprintf
    char * pszFormBufPtr;               // pointer to the above buffer
    char ch;                            // holds one character while detecting the format-string

    pszDestPtr = pszFinalString; // set the destination-ptr


    pOwnFormatString = pErrStruct->ucParamInfo;

    // loop throug the description until a % is found
    for ( pszErrorFmPtr = pszErrorDescription; *pszErrorFmPtr != '\0'; pszErrorFmPtr++ )
    {
        if ( *pszErrorFmPtr != '%')   // if the character it is not a % send it to the final buffer
        {
            wOutPutCharCount = wsprintf( pszDestPtr, "%c", *pszErrorFmPtr );
            pszDestPtr += wOutPutCharCount;
        }
        else
        {
            pszFormBufPtr = szFormatBufferForSprintf;
                                            // now we have the start of a format-string,
                                            // so copy it to a format-buffer
                                            // and let sprintf do the rest ...


            *pszFormBufPtr++ = *pszErrorFmPtr++;  // store the first % to avoid conflict with end-condition % in while-loop
            do
            {
                ch = (unsigned char ) *pszErrorFmPtr;
                ch = (unsigned char) toupper(ch);
                *pszFormBufPtr++ = *pszErrorFmPtr++;
            }
            // according to K/R 2.nd German Edition , P. 243
            while (  ( ch != 'D') &&
                     ( ch != 'I') &&
                     ( ch != 'O') &&
                     ( ch != 'X') &&
                     ( ch != 'U') &&
                     ( ch != 'C') &&
                     ( ch != 'S') &&
                     ( ch != 'F') &&
                     ( ch != 'E') &&
                     ( ch != 'G') &&
                     ( ch != 'P') &&
                     ( ch != 'N') &&
                     ( ch != '%') );
            pszErrorFmPtr--; // Skip back one char , because we did one ++ to much in the above while-loop
            *pszFormBufPtr = '\0';  // Format-String for sprintf is ready
            // Check for %%, special handling
            if( ch == '%' )
            {
                wOutPutCharCount = wsprintf( pszDestPtr, "%%%%" );
                pszDestPtr += wOutPutCharCount;
            }
            else
            {
                // now go through the simplified own format-buffer and detect where to get the parameter from
                ch = *pOwnFormatString;
                ch = toupper( ch );
                pOwnFormatString++ ;

                switch( ch )
                {
                    case 'S':
                        wOutPutCharCount = wsprintf( pszDestPtr, szFormatBufferForSprintf, pErrStruct->ucParamString[wStringBufferIndex]  );
                        pszDestPtr += wOutPutCharCount;
                        wStringBufferIndex++;
                        break;
                    default:
                        wOutPutCharCount = wsprintf( pszDestPtr, szFormatBufferForSprintf, pErrStruct->ulParamValue[wLongBufferIndex]  );
                        pszDestPtr += wOutPutCharCount;
                        wLongBufferIndex++;
                        break;
                }
            } // end special treat for %%
        } // end format-detection via %
    } // end for-loop
} // end function





/*  ------------------------------------------------------------------------
 *
 * ErrDemo_GetLastErrorString
 *
 *  ------------------------------------------------------------------------ */
/**
 * Generates an english errortext, retrieved from the new function WSwup_GiveLastError( ).
 * Therefore it retrieves a pointer to the new error-struct.
 * With the error-number it loops throug the additionally given array with the errortexts to
 * find the right error-text. If an alternate error-number is given ( and behaviour is set to enduser ),
 * it loops once more through the array to find the alternate errortext.
 * This Error-Text is ( via definition ) parameter-free, so the text can be returned.
 * If there is no alternate error-number given there must be a parameter-check and substitution.
 *
 * \param wUpdateNr : the Update-Nr on which the error happened
 *
 *
 * \return pointer to the decoded error-string
 *
 */

char  * ErrDemo_GetLastErrorString( WORD wUpdateNr )
{
    t_ErrorStruct * pMyErrStruct;
    WORD wErrorNumber;
    BOOL fErrorFound;
    WORD wErrArrayIndex;

    static char szDecodedErrorText[2000];


    // retrieve a pointer to the Error-Structure
    pMyErrStruct = WSwup_GiveLastError  ( wUpdateNr );

    // extract the Error-Number from the struct
    wErrorNumber =  ( WORD ) pMyErrStruct->dwErrorNumber;

    // Now loop through the Error-Text-Array to find the right error-text
    fErrorFound = FALSE;
    for( wErrArrayIndex = 0; wErrArrayIndex < ( ErrorDescriptionSize /  t_enumErrorDescriptionSize ) ; ++wErrArrayIndex )
    {
        if( ErrorDescription[wErrArrayIndex].ui_enError  == wErrorNumber )
        {
            fErrorFound = TRUE;
            break;
        }
    }
    // if the error is not found, this means eventually that you are running with an old version of err_text.h ...
    if( !fErrorFound )
    {
        wsprintf( szDecodedErrorText, "Unknown Error Number %d occured", wErrorNumber );
        return szDecodedErrorText;
    }
    // Now check if there is an alternate text ( but only in enduser-behaviour )
    if( fEndUserBehaviour )
    {
        if( ErrorDescription[wErrArrayIndex].ui_enAltError != 0 )
        {
            // set the new alternate error-number
            wErrorNumber = ErrorDescription[wErrArrayIndex].ui_enAltError;

            // and loop once more through the error-array and find the alternate error with its text
            for( wErrArrayIndex = 0; wErrArrayIndex < ( ErrorDescriptionSize / t_enumErrorDescriptionSize ) ; ++wErrArrayIndex )
            {
                if( ErrorDescription[wErrArrayIndex].ui_enError  == wErrorNumber )
                {
                    fErrorFound = TRUE;
                    break;
                }
            }
            // if the error is not found, this means eventually that you are running with an old version of err_text.h ...
            if( !fErrorFound )
            {
                wsprintf( szDecodedErrorText, "Unknown Error Number %d occured", wErrorNumber );
                return szDecodedErrorText;
            }
            else
            {
                return ErrorDescription[wErrArrayIndex].pszDescription;
            }
        }
    }
    // now do the special-sprintf, that analyses the format-strings and gets the parameter-info
    SpecialSprintf( szDecodedErrorText, ErrorDescription[wErrArrayIndex].pszDescription, pMyErrStruct );
    return szDecodedErrorText;
}

