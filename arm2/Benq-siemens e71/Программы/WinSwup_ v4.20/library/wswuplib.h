#ifndef _SWUPLIB_HEADER_
#define _SWUPLIB_HEADER_
/*

                               Siemens AG
                         Mobile Radio Terminals
                            Munich,  Germany

                          COMPANY CONFIDENTIAL
                          All Rights Reserved

.AUTHOR         J. Kuenstner, ICP CD MP RD M 57

.SHORT_DESCR    Interface to the WSWUPLIB-DLL

.SW_COMPONENT   Interface

.SW_TYPE        OTHER_PROCESS

.VERSION        1.39 // DONT FORGET THE DEFINES!!

.DATE           2006-04-26

.STATUS         FIRST_VERSION

.CHANGE_CONTROL

Version |  Date    | Changed by | Reason for Change
--------+----------+------------+-----------------------
  0.1   |XX.03.2000| JKue       |  file created......
--------+----------+------------+-----------------------
  0.2   |10.03.2000| JKue       |  Added this Header
--------+----------+------------+-----------------------
  0.3   |30.06.2000| JKue       |  New Functions for Version-Checks
        |          |            |  and support for Synch-Station
--------+----------+------------+-----------------------
  0.4   |15.07.2000| JKue       |  New Functions for Comport-Checks and
        |          |            |  AMOUNT_OF_SWUP_PORTS increased to 12
--------+----------+------------+-----------------------
  0.5   |18.12.2000| JKue       |  New Call-Back-Functions for checking Mobile-Types and Dates
--------+----------+------------+-----------------------
  0.6   |08.02.2001| JKue       |  Doxygen-Comments
--------+----------+------------+-----------------------
  0.7   |05.05.2001| J.Garrido  |  Sw_info extended
--------+----------+------------+-----------------------
  0.8   |15.05.2001| J.Garrido  |  Sw_info extended removed due lib compatibility
--------+----------+------------+-----------------------
  0.9   |19.05.2001| JKue       |  unknown projects
--------+----------+------------+-----------------------
  1.0   |29.05.2001| JKue       |  Update-Concept for K45
--------+----------+------------+-----------------------
  1.10  |09.06.2001| JKue       |  Init-function with Interface-Version-Check
--------+----------+------------+-----------------------
  1.20  |10.06.2001| JKue       |  Had to change interface of functions WSwup_SetUpdateConceptMode() and
        |          |            |  WSwup_CheckUpdateVoltage()
--------+----------+------------+-----------------------
  1.20  |11.06.2001| JKue       |  still 1.20 : some mor comments on the new update-concept
--------+----------+------------+-----------------------
  1.21  |13.07.2001| JKue       |  File-Debugging-Functionality
--------+----------+------------+-----------------------
  1.22  |17.07.2001| W. Hettich |  new interface for heap method reading xbi data
--------+----------+------------+-------------------------------------------------
  1.23  |07.08.2001| W. Hettich |  close up function for heap lib added
--------+----------+------------+-----------------------
  1.24  |2001-08-08| Schmittu/  |  New Error-Functionality
                     JKue       |
--------+----------+------------+-----------------------
  1.25  |2001-08-29| Schmittu   |  new prototypes : WSwup_SetErrorTextBehaviourToEnduser
        |          |            |  MAX_ENTRIES -> 50
--------+----------+------------+-----------------------
  1.25  |2001-09-06| JKue       |  still 1.25 , only a comment was changed due to
        |          |            |  an html-error for the doxygen-documentation
--------+----------+------------+-----------------------
  1.26  |2001-10-22| JKue       |  new function : WSwup_InstallSoftwareInfoCallBackFunction()
        |          |            |  and the corresponding new callback-funtion
--------+----------+------------+-----------------------
  1.26  |2001-11-23| JKue       |  still 1.26 : Added some comment on
        |          |            |  WSwup_CheckUpdateSuccess()
--------+----------+------------+-----------------------
  1.27  |2002-02-25| JKue       |  Added additional parameter for WSwup_InstallSoftwareInfoCallBackFunction()
        |          |            |  This parameter selects the callbacktime
--------+----------+------------+-----------------------
  1.28  |2002-04-30| LSillge    |  New Functionprototype set PIN for Update added
--------+----------+------------+-----------------------
  1.29  |2002-05-26| J.Garrido  |  Read new file format for signature protection
--------+----------+------------+-----------------------
  1.29  |2002-11-18| JKue       |  still 1.29 : change some wrong comments eg:
                                |   - param ulSpeed in WSwup_SetUpdateConceptMode never existed ...
--------+----------+------------+-----------------------
  1.30  |2004-01-30| J.Garrido  |  Add install bfc callback funtion.Maintain the old interface
        |          |            |   for backwards compatibility.
        |          |            |  Add new fields in sw information structure.
        |          |            |    szInfoDatabaseName
        |          |            |    szInfoBaselineVersion
        |          |            |    szInfoBaselineRelease
        |          |            |    szSwupDllName
--------+----------+------------+-----------------------
  1.31  |2004-08-09| J.Garrido  |  Add new interfaces functions:
                                |   .- WSwup_LookForMobile
                                |   .- WSwup_SearchAvaliableComPort
                                |  Allowing the use of not limited port numbers.
                                | .- Modify interface for WSwup_GetLastError and
                                | WSwup_GetLastErrorString
--------+----------+------------+-----------------------
  1.32  |2002-09-08| J.Garrido  | Remove AMOUNT_OF_SWUP_PORTS, not used.
--------+----------+------------+-----------------------
  1.33  |2005-03-16|L&T INFOTECH| added the interface function prototypes which is used
                                | in SCOUT tool.
--------+----------+------------+-----------------------
  1.34  |2005-04-15|M.Untucht   | added interface for setting com port 
                                | for mobile SW update 
--------+----------+------------+-----------------------
  1.35  |2005-04-26|J.Garrido   | Substitute UINT32 by UINT (windows.h) due compatibility problems                                
---------------------------------------------------------
  1.36  |2005-09-07|R.Szul      | Added function WSwup_PerformSoftwareUpdateDeveloperUSB() which
        |          |            | enables use USB independently in each thread
--------+----------+------------+-----------------------
  1.37  |2005-11-03|K.Gontarz   | Added function WSwup_CheckUpdateVoltageScout()-used in the scout tool; user can specify
        |          |            | if the mobile's voltage is compared with 3,9V or not
--------+----------+------------+-----------------------------------------------
  1.38  |2006-01-19|R.Szul      | Added function WSwup_GetUpdateConceptMode()
--------+----------+------------+-----------------------------------------------
  1.39  |2006-04-26|R.Szul      | Added functions: WSwup_SetLastChanceUpdate,
													WSwup_GetLastChanceUpdate
								  Added external: BOOL g_bLastChanceUpdate;
										
--------+----------+------------+-----------------------------------------------
  
.STILL_TODO

*/

/* INDENT: -nbr -nce -ei -ip -lp -pro -sc -c:33 -cci:3 -cd:33 -ci:3 -cli:3 -cp:0 -d:0 -di:0 -i:3 -l:78 -lc:78 -tabs:3  -tabu */

/**
 * \file wswuplib.h
 * \brief This is the Export-Header for the WSWUPLIB-Library
 *
*/

/*  ***  INCLUDES  ***  ***************************************************** */

/*  ***  DEFINES  ***  ****************************************************** */

/* These two defines must be given to the function WSwup_InitLibrary()
 * The library will the do an equal-check and fail if it is not the same version
 * This is to avoid interface-conflicts, when an old Executable is executed
 * together with a newer DLL with a different interface !
 * So : programmer of the library be careful on interface-changes ( avoid them
 * as far as possible, and if really necessary, the you have to increase the
 * version-defines, which forces the user of the DLL to a new compile with the
 * new interface, because the runtime-check will fail !
 *
 */

#define WSWUPLIB_INTERFACE_VERSION_MAJOR  1  /**< Interface-Version of the whole library ( this file ), must be increased on interface-changes \ingroup initfunction */
#define WSWUPLIB_INTERFACE_VERSION_MINOR  33 /**< Interface-Version of the whole library, minor-number  \ingroup initfunction */

#define AMOUNT_OF_UPDATES           4       /**< amount of parallel updates through different comports */

#define START_COM_SEARCH        0                   /** Reset the com port search process */
#define CONTINUE_COM_SEARCH     !START_COM_SEARCH   /** Continue with the com search process at the last point */

 /**
 * \def  __SWUPLIBDLL__
 * \brief Set this define on compiling the DLL.
 * This is normally done in the IDE on compliling the DLL !
 *
 */



#ifdef COMPLETE_SERVICE_SWUP
  #define SWUPLIBDLLEXIMPORT
#else
  #ifdef __SWUPLIBDLL__                     /*  ( done in the project-settings ! ) */
    #define SWUPLIBDLLEXIMPORT __declspec(dllexport)
  #else
    #define SWUPLIBDLLEXIMPORT __declspec(dllimport)
  #endif
#endif

/*  ***  TYPEDEFS ***  ****************************************************** */
/**
 * An enumeration for all possible Comports, as the number of
 * ports is not limited, don't use it any more
 *
 */
typedef enum
{
    SwupCom1 = 0,       /**< Comport 1  */
    SwupCom2 = 1,       /**< Comport 2  */
    SwupCom3 = 2,       /**< Comport 3  */
    SwupCom4 = 3,       /**< Comport 4  */
    SwupCom5 = 4,       /**< Comport 5  */
    SwupCom6 = 5,       /**< Comport 6  */
    SwupCom7 = 6,       /**< Comport 7  */
    SwupCom8 = 7,       /**< Comport 8  */
    SwupCom9 = 8,       /**< Comport 9  */
    SwupCom10 = 9,      /**< Comport 10 */
    SwupCom11 = 10,     /**< Comport 11 */
    SwupCom12 = 11     /**< Comport 12 */
}t_SwupCom_old;

/**
* For backwards compatibility, serial number to be used.
*/
typedef unsigned int t_SwupCom;


/**
 * Different parts of the whole library, for which the user can request version-information.
 * Give one of this values to function WSwup_GiveVersionInformation() and it will return the information
 * about the requested part.
 *
 * \ingroup dllversion
 */
typedef enum
{
    enSwupLibDll,              /**< information about the whole wrapper */
    enSwupSeriDll,             /**< information about the serial DLL    */
    enBootStrapDll,            /**< information about the BootStrapLoader-DLL itself */
    enUpdateSW                 /**< information about the MobileSW-Part that is contained in the BSL-DLL */
} t_InfoSelector;



/**
 * Version-Information for the different parts of the Library.
 * The library itself is split into different DLLs, some of them are
 * loaded on runtime. So the user can call the function WSwup_GiveVersionInformation
 * and will find the information about the different parts
 * in this returned structure.
 *
 * \ingroup dllversion
 */
typedef struct
{
    int  nStructSize;          /**< must be loaded with sizeof( struct ) to avoid Consistency-errors */
    char szDescription[100];   /**< Description,   ex: "BSL-DLL for EGOLD+, Synchstation"     */
    char szDeveloper[10];      /**< the developer, ex: "kuenstnj" / "official"    */
    char szDateTime[18];       /**< Date and Time, ex: "30.06.00 20:15:17 "       */
    int  nVersionMajor;        /**< the Major-Version-Nr  ex: 1  */
    int  nVersionMinor;        /**< the Minor-Version-Nr  ex: 25 */
} t_VersionInformation;


/**
 * Structure with Information about the SW in the XBI-File or the Mobile itself.
 * This Information-Structure will be filled on call of function WSwup_ReadXbiFile and
 * pointers to two of this structs will be given on Consistence-Errors, when eg. the
 * SW already contained in the mobile is newer than the XBI-File that is going to be
 * updated ( see MobileSwUpdateConsistenceProblemCallBack() ).
 *
 * \ingroup filefun
 */
typedef struct
{
    char szProductType[16];   /**< Official Name of the product , ex: S35 , C3I etc      */
    char szProjectName[16];   /**< Develop-Name of the product , ex: epp35a, epp35ci etc */
    char szProductSVN[10];    /**< Official SVN-String, ex: "SVN 1"                      */
    char szCompileDate[9];    /**< Date the SW was compiled, ex: "05.03.00"               */
    char szCompileTime[9];    /**< Time the SW was compiled, ex: "12:31:47"               */
    char szSwType [20];        /**< Type of the SW , ex: "MobSw"                 */
    char szNewSplitIdentifier [16]; /**< Kind of Split, ex: "SplitOnly"          */
    char szCommentAboutSplitEntity [20];  /**< if exist then the header value , ex: "Tegig", if not ?? */
    char szInfoDatabaseName[0x20];/**< CMT/Continuus Database Name (per default : "DB Name") */
    char szInfoBaselineVersion[0x40];/**< CMT/Continuus Baseline Version (per default : "BL Version") */
    char szInfoBaselineRelease[0x40];/**< CMT/Continuus Baseline Release (per default : "BL Release") */
    char szSwupDllName[17];  /**< dll to use for the sw update */

} t_SwInformation;



#define MAX_ENTRIES      50             /**< Amount of entries in the error-"stack" \ingroup  errorfun */
#define NO_PARAM         ""             /**< an empty parameter-list                \ingroup  errorfun */
#define SIZE_OF_PINFO    10             /**< max amount of parameters for errors     \ingroup  errorfun */
#define SIZE_OF_PSTRING  2000           /**< maximum size of a error-string-parameter \ingroup  errorfun */



/**
 * A structure to allow passing of parameters for error-messages from the Lib to the user of the Lib.
 * If you need internationalisation in your application, you have to deal with error-strings
 * yourself outside the library.<br>
 * To allow the library on errors to pass parameters to the user of the library this
 * structure was introduced.<br>
 * You will retrieve a pointer to this structure via call of WSwup_GiveLastError() .
 * The first element in the struct is the error-number itself.
 * The second element is a simplified format-string ( like in printf but without % ) that
 * tells the user of the library how many and in which order additional parameters
 * are stored in the third and fourth elements of the struct.<br>
 * There is only a distinction between strings and numerical integer values ( no floats ),
 * this means for example if the format-string contains something like "dsxs" ,that
 * the first and the third error-parameter ( d and x ) will be stored in
 * t_ErrorStruct.ulParamValue and the second and forth parameter containg two strings
 * are stored in t_ErrorStruct.ucParamString.<br>
 * If you need more information you should have a look at the also provided err_demo.c.
 *
 * \ingroup  errorfun
 *
 */
typedef struct
{
    DWORD           dwErrorNumber;                      /**< the error-enum  */
    unsigned char   ucParamInfo[SIZE_OF_PINFO +1];      /**< info about the validity of the following params + EOS */
    LONG            ulParamValue[5];                    /**< variables that will be inserted in the indicated string at %d,%x,... */
    unsigned char   ucParamString[5][SIZE_OF_PSTRING];  /**< variables that will be inserted in the indicated string at %s */
} t_ErrorStruct;



/* SCOUT */

/** next start mode */
#define NORMAL_MODE			0
#define SERVICE_MODE		1

/**
 * A structure which stores the all the file (XBI, XFS, MAP and DELTA MAP) start
 * info in the heap and the size of each file. This structure used by the SCOUT tool
 *
 * \ingroup  swupfn
 *
 */
typedef struct
{
    unsigned char *pXbiStart;
    unsigned char *pMapStart;
    unsigned char *pXfsStart;
    unsigned char *pDeltaMapStart;
    unsigned long ulXbiLen;
    unsigned long ulMapLen;
    unsigned long ulXfsLen;
    unsigned long ulDeltaMapLen;
}SCOUTFileInfo;



/**
 * A structure which stores Mapping data which is transferred to the Mobile.
 *
 * \ingroup  swupfn
 *
 */
typedef struct strMapData
{
    int     iBlockNumber;
    int     iOffset;
    BYTE    byMemory;
    BYTE    byPStufe;
    BYTE    byService;
    BYTE    byVersion;
    UINT  dwDataSize;
    BYTE    *pbyData;
}MAPDATA;

/**
 * A structure which stores Mapping header Info which is used for identification.
 * it also contains how many blocks need to be transferred to the Mobile.
 *
 * \ingroup  swupfn
 *
 */
typedef struct strMapInfo
{
    int     iProduct;       // Produktnummer
    int     iProvider;      // Provider
    int     iMapVer;        // Mappingversion
    int     iSWVersion;     // Softwareversion
    int     iTime;          // Uhrzeit des Mappings
    int     iDate;          // Datum des Mappings
    DWORD   dwCheckSum;     // Checksumme der Mappingdatei
    int     iNumBlocks;     // Anzahl der Blöcke
    char    *pFileName;     // Pointer to the FileName
}MAPINFO;


typedef void ( *EraseAreaHandler ) ( unsigned long unStartAddr, unsigned long unEndAddr );
typedef void (*EndThread)();
typedef void (*ExtractBitmap)(unsigned char* pucHeap, unsigned char* pTemp, unsigned long ulLen);


/*  ***  EXTERNALS  ***  **************************************************** */

extern BOOL g_bUseSeparateThreadForUpdateFunctions;
extern EndThread g_fnEndThread;
extern ExtractBitmap g_fnExtractBitmap;
extern BOOL g_bLastChanceUpdate;


/*  ***  CONSTANTS ***  ***************************************************** */

/*  ***  VARIABLES  ***  **************************************************** */

/*  ***  PROTOTYPES  ***  *************************************************** */

/*  ***  MODUL COMMENTS  ***  *********************************************** */

/*  ***  FUNCTIONS  ***  **************************************************** */




/***************************************************************************************************************
 *
 *
 *      Init-Functions
 *
 *
 ***************************************************************************************************************/
/**
 * \defgroup initfunction Init-Function for the whole Library/DLL
 */

/*  ------------------------------------------------------------------------
 * WSwup_InitLibrary
 *  ------------------------------------------------------------------------ */
/**
 * This function must be called by every user of the library once on starting.
 * This intention of this function is to make a interface-compatibility-check
 * at runtime, so every user of the library has to call this function once
 * before using the library.<br>
 * The user has to pass the two defines:
 * - WSWUPLIB_INTERFACE_VERSION_MAJOR
 * - WSWUPLIB_INTERFACE_VERSION_MINOR
 *
 * to the function.
 * If the given version is different from the one which the library expects,
 * ( the one it had on its own compile-time )
 * the function will return FALSE and the library will not work.
 * This is to prevent library-users from unexpected runtime-errors in their executables
 * due to a new interface and new DLLs but an old Executable !
 *
 * \param wMajorNumber : must be the given define WSWUPLIB_INTERFACE_VERSION_MAJOR
 * \param wMinorNumber : must be the given define WSWUPLIB_INTERFACE_VERSION_MINOR
 *
 * \retval  TRUE  -> Library is initialised, version-information is ok
 * \retval  FALSE -> version-check failed, library does not work
 *
 * \ingroup initfunction
 *
 */
BOOL SWUPLIBDLLEXIMPORT WSwup_InitLibrary( WORD wMajorNumber, WORD wMinorNumber );




/***************************************************************************************************************
 *
 *
 *      Comport-Information-Functions
 *
 *
 ***************************************************************************************************************/
/**
 * \defgroup comportinfo Comport-Information-Functions
 */

/*  ------------------------------------------------------------------------
 * WSwup_LookForMobile
 *  ------------------------------------------------------------------------ */
/**
 *    This function look for a siemens telephone on the desired com port with de
 *    desired baudrate.
 *    There is no guaranty, that the update with this baudrate will work !

 * \param ComPort    Desired comport number to be tested ( starting at 0 for "COM1")
 * \param Baudrate   Desired baudrate to be use in the test.
 *
 * \retval  TRUE  a telephone was found
 * \retval  FALSE no compatible telephone found.
 *
 * \ingroup comportinfo
 *
 */
BOOL SWUPLIBDLLEXIMPORT WSwup_LookForMobile(t_SwupCom ComPort, DWORD Baudrate);

/*  ------------------------------------------------------------------------
 * WSwup_SearchAvaliableComPort
 *  ------------------------------------------------------------------------ */
/**
 *    This function looks in the registry for avaliable com ports which supports rs232.
 *    There is no guaranty, that the update with this baudrate will work !
 *    Use it with the Option START_COM_SEARCH for the first call to start up, next ports will be get
 *    by using the option CONTINUE_COM_SEARCH.
 *
 * \param pszComName a string where to place the name of the port ( "COM1", "COM123" )
 * \param pszComDesc a string where to place the desription of the port. Usually in the form
 *                   "device/serial0"
 * \param Option     a integer meaning the start up or the continue of the search.
 *
 * \retval  TRUE  everithing worked properly
 * \retval  FALSE End of search, no more ports avaliable. Or an error is ocurred.
 *
 * \ingroup comportinfo
 *
 */
BOOL SWUPLIBDLLEXIMPORT WSwup_SearchAvaliableComPort ( char *  pszComName,
                               char *  pszComDesc ,unsigned int Option  );

/*  ------------------------------------------------------------------------
 * WSwup_CheckComPortAndSpeed
 *  ------------------------------------------------------------------------ */
/**
 * This function only tries to open the selected comport with the given baudrate.
 *    In all cases ( besides comport already open ) the comport will be closed after this try.
 *    It returns the result from opening the comport, so its possible to determine
 *    if the win-system allows this baudrate on this comport.
 *    There is no guaranty, that the update with this baudrate will work !
 *
 *
 * \param WhichCom  a t_SwupCom-enum, which comport should be tried
 * \param dwBaudrate a dword meaning the Baudrate at which the comport should be tried
 *
 *
 *
 * \retval  TRUE  It is possible ( from WIN-System-side ) to open the Comport at this baudrate
 * \retval  FALSE Either Comport not available or this baudrate not possible
 *
 * \ingroup comportinfo
 *
 */
BOOL SWUPLIBDLLEXIMPORT WSwup_CheckComPortAndSpeed( t_SwupCom WhichCom , DWORD dwBaudrate );

/*  ------------------------------------------------------------------------
 * WSwup_SetDeveloperUSBPortAndSpeed
 *  ------------------------------------------------------------------------ */
/**
 * This function sets the com-port for the mobile SW update.
 *
 * \param BOOL fUSBUpdate sets the use of the virtual com port on USB for the sw transmission. 
 * \param WORD ComPort wich virtual com port has to used for the transmission.
 * \param DWORD Baudrate not really important. The com interface needs a baudrate value.
 *
 * \ingroup comportinfo
 */
void SWUPLIBDLLEXIMPORT WSwup_SetDeveloperUSBPortAndSpeed ( BOOL fUSBUpdate,  WORD ComPort, DWORD Baudrate  );

/***************************************************************************************************************
 *
 *
 * DLL-Version-Information-Functions
 *
 *
 ***************************************************************************************************************/
/**
 * \defgroup dllversion DLL-Version-Information-Functions
 */

/*  ------------------------------------------------------------------------
 * WSwup_GiveVersionInformation
 *  ------------------------------------------------------------------------ */
/**
 * Returns Version Information about the different Parts of WSWUPLIB.
 *           Since the SWUPLIB-functionality is contained in 3 different DLLs,
 *           and one of them is dynamically loaded for different processor-types,
 *           it is possible to retrieve some information about the DLLs.
 *
 *
 * \param WhichInfo a t_InfoSelector , about which part the information is to be retrieved
 *
 * \param pInformation  a ptr to a t_VersionInformation , that will be filled with
 *                                the requested information.
 *                                Attention: pInformation->nStructSize must be filled from the caller with
 *                                           sizeof( t_VersionInformation ) to avoid conflicts on future enhancements
 *
 * \retval  TRUE  Information-struct is filled with info
 * \retval  FALSE Information not available, ex. the DLL is not yet loaded
 *
 * \ingroup dllversion
 */
BOOL SWUPLIBDLLEXIMPORT WSwup_GiveVersionInformation( t_VersionInformation * pInformation, t_InfoSelector WhichInfo  );




/***************************************************************************************************************
 *
 *
 *      Synch-Station specific Functions
 *
 *
 ***************************************************************************************************************/
/**
 * \defgroup synchstation Synch-Station specific Functions
 */

/*  ------------------------------------------------------------------------
 * WSwup_PrepareForUpdateWithSynchStation
 *  ------------------------------------------------------------------------ */
/**
 *
 * Prepares for performing the update via Synch-Station.
 *           The Bootstrap-Loader for a Synch-Station is different to a normal BSL.
 *           Since the Bootstraploader-DLL is dynamically loaded on File-Reading,
 *           this function must be called in advance, to force loading a different,
 *           synch-station-specific DLL on FileReading
 *
 * \param fSynchStationPresent Boolean Flag for presence/absence of Synch-Station
 *
 *
 * \return void
 *
 * \ingroup synchstation
 */
void SWUPLIBDLLEXIMPORT WSwup_PrepareForUpdateWithSynchStation(  BOOL fSynchStationPresent );



/*  ------------------------------------------------------------------------
 * WSwup_ReloadUpdateDll
 *  ------------------------------------------------------------------------ */
/**
 *
 * Reloads the DLL that is responsible for performing the Update.
 *     If - after reading the file - the decision is made, that this update
 *     is via a synch-station, the DLL must be relodaded, in order to get
 *     the correct Bootstraploader.
 *     =>
 *     - call WSwup_PrepareForUpdateWithSynchStation( TRUE )
 *     - call this function
 *
 *
 * \retval  TRUE  Everything is okay
 * \retval  FALSE  something went wrong
 *
 * \ingroup synchstation
 */
BOOL SWUPLIBDLLEXIMPORT WSwup_ReloadUpdateDll( void );



/***************************************************************************************************************
 *
 *
 *      ERROR-Functions, to get information about the last ERROR
 *
 *
 ***************************************************************************************************************/
/**
 * \defgroup errorfun ERROR-Functions, to get information about the last ERROR
 */


/*  ------------------------------------------------------------------------
 * WSwup_GetLastError
 *  ------------------------------------------------------------------------ */
/**
 * Returns an specific Error-Code about last Error on this comport.
 *           Retrieves the last occured Error for the specified COM-Port
 *           ( almost useless, normally use WSwup_GetLastErrorString )
 *           <b>Dont use this function any longer its obsolete and will
 *           be killed in one of the next releases !</b><br>
 *           Either use function WSwup_GetLastErrorString() to get an
 *           english string or use function WSwup_GiveLastError() and deal
 *           with it's information outside the library.
 *
 * \param ComPort ComPort on which the Error cccured
 *
 * \return The Error-Code
 *
 * \ingroup errorfun
 */
DWORD SWUPLIBDLLEXIMPORT WSwup_GetLastError(  WORD wUpdateNr  );

/*  ------------------------------------------------------------------------
 * WSwup_SetErrorTextBehaviourToEnduser
 *  ------------------------------------------------------------------------ */
/**
 * Switches the behaviour of function WSwup_GetLastErrorString() to a less informative behaviour.
 * Has to be called in an enduser-update when not dealing yourself with error-strings, this means
 * when you are hapyy with english text. Normally on an enduser-update you should deal with different
 * languages and interpret the errors outside the library by yourself using function :
 * WSwup_GiveLastError( ) and implement something equal to the swupdemo-error-handling.
 *
 * \param fEndUser   TRUE means enduser
 *                   FALSE means developper
 *
 * \retval none
 *
 * \ingroup errorfun
 *
 */

void SWUPLIBDLLEXIMPORT WSwup_SetErrorTextBehaviourToEnduser( BOOL fEndUser);


/*  ------------------------------------------------------------------------
 * WSwup_GetErrorString
 *  ------------------------------------------------------------------------ */
/**
 * Retrieves the Error-String of the last Error for the given ComPort.
 *
 * \param ComPort ComPort on which the Error cccured
 *
 * \return The Error-Code-String
 *
 * \ingroup errorfun
 */
char SWUPLIBDLLEXIMPORT * WSwup_GetLastErrorString( WORD wUpdateNr  );


/*  ------------------------------------------------------------------------
 * WSwup_GiveLastError
 *  ------------------------------------------------------------------------ */
/**
 * Returns the last Error for the indicated updatenumber with its specific parameters.
 * For a more detailled explanation see a the declaration of \ref t_ErrorStruct or
 * have a look at the also provided err_demo.c<br>
 * <ul>
 * <li> dwErrorNumber  : the Error-number, for corresponding text see err_text.h</li>
 * <li> ucParamInfo    : indicates the kind of the following parameters, e.g. s for string, x,d,i,o,u for numerals, no l...!<br>
 *                       e.g. "sxsd", maximum SIZE_OF_PINFO Entries ( 10 at the moment ), upper and lower chars allowed<br>
 *                       maximum 5 strings and 5 non-strings<br>
 *                       just like %d,%X... in printf, without %</li>
 * <li>ulParamValue   : numeral LONG value</li>
 * <li>ucParamString  : maximum 2000 chars</li>
 * </ul>
 *
 *
 * \param  wUpdateNr : the update-Nr for which you want to retrieve the error-information.
 *
 * \return t_ErrorStruct ->  a pointer to a \ref t_ErrorStruct - structure
 *
 * \ingroup errorfun
 *
 *
 *
 */
SWUPLIBDLLEXIMPORT t_ErrorStruct * WSwup_GiveLastError ( WORD wUpdateNr );



/***************************************************************************************************************
 *
 *
 *   BFC-Lib-Functions, used before and after SOFTWARE-Update to check if a
 *   Software-Update is possible and if it was successfull !
 *
 *
 ***************************************************************************************************************/
/**
 * \defgroup bfcfun BFC-Lib-Functions, used before and after SOFTWARE-Update
 */

/**
 * Callbackfunction for VoltageCheck that is performed.
 * On call of function WSwup_CheckUpdateVoltage this callback-function is called several times
 * to allow the user of the library to show the progress.
 * \param wUpdateNr This parameter is the Update-Nr
 * \param unMaxCalls This second Parameter is the Max-Amount of Calls of this CallbackFunction
 * \param unCurrCall this parameter is the current Call-Number. It can happen that not all Callbacks
 * are done !
 * \return void
 * \ingroup bfcfun
 */
typedef void ( * VoltageCheckCallBack ) ( WORD wUpdateNr, unsigned int unMaxCalls, unsigned int unCurrCall );

/**
 * Callbackfunction for UpdateSuccess that is performed after swup.
 * On call of function WSwup_CheckUpdateSuccess this callback-function is called several
 * times to allow the user of the library to show the progress.
 * \param wUpdateNr First Parameter is the Update-Nr
 * \param unMaxCalls Second Parameter is the Max-Amount of Calls of this CallbackFunction
 * \param unCurrCall Third parameter is the current Call-Number. It can happen that not all Callbacks
 * are done !
 * \return void
 * \ingroup bfcfun
 */
typedef void ( * UpdateSuccessCallBack) ( WORD wUpdateNr, unsigned int unMaxCalls, unsigned int unCurrCall );





/*  ------------------------------------------------------------------------
 * WSwup_InstallBfbCallBackFunctions
 *  ------------------------------------------------------------------------ */
/**
 * Call  WSwup_InstallBfcCallBackFunctions. Only for back-compatibility.
 * \param pfnVoltageCheck  Pointer to a CallbackRoutine that is called on Voltage-Check
 * \param pfnSuccessCheck  Pointer to a CallbackRoutine that is called on Update-Success
 *
 * \return void
 *
 * \ingroup bfcfun
 */
void SWUPLIBDLLEXIMPORT WSwup_InstallBfbCallBackFunctions( VoltageCheckCallBack pfnVoltageCheck, UpdateSuccessCallBack pfnSuccessCheck );

/*  ------------------------------------------------------------------------
 * WSwup_InstallBfcCallBackFunctions
 *  ------------------------------------------------------------------------ */

/**
 * Installs the needed callbackfunctions for Pre and Post-Checks via BFC-Library.
 * If the user of the library wants to perform voltagecheck before the software-update
 * itself and wants to perform the updatesuccess-check after the software-update with
 * the functions WSwup_CheckUpdateVoltage and WSwup_CheckUpdateSuccess he first must
 * install the callbackfunctions that will be called from inside the library to
 * show the progress in the different functionalities.
 *
 * \param pfnVoltageCheck  Pointer to a CallbackRoutine that is called on Voltage-Check
 * \param pfnSuccessCheck  Pointer to a CallbackRoutine that is called on Update-Success
 *
 * \return void
 *
 * \ingroup bfcfun
 */
void SWUPLIBDLLEXIMPORT WSwup_InstallBfcCallBackFunctions( VoltageCheckCallBack pfnVoltageCheck, UpdateSuccessCallBack pfnSuccessCheck );

/*  ------------------------------------------------------------------------
 * WSwup_CheckUpdateVoltage
 *  ------------------------------------------------------------------------ */
/**
 * Tries to communicate to a "living" mobile to determine if the voltage is ok.
 *  Switches the Mobile on, if necessary and afterwards switches it off, so
 *  that afterwards the softwareupdate itself can be performed.
 *  Calls several times the pfnVoltageCheck CallbackFunction.<br>
 *  In case this update is an update with the new behaviour ( introduced for
 *  the K45-family ) set via WSwup_SetUpdateConceptMode() this function
 *  has a slightly different behaviour:
 *  - this routine MUST be called, because it initiates the update !
 *  - ( with BootStrapMode this routine is an option )
 *  - it does not try to switch on the mobile, endusers dont have an ignition line.
 *  - due to this : if connection via ping is not possible, this routine fails.
 *  - the filetype is checked, only a complete Mobile-SW can be updated with this new mode
 *  - partitial SW ( Diff/Tegic/Language/... ) will be refused.
 *  - after having pinged and checked the voltage, this routine forces the mobile into
 *    the new update-mode, without really switching off.
 *  - due to this it's necessary to pass the new baudrate-parameter, which will be used for the following
 *    update-procedure itself
 *  - after sucessfully returning from this function, the WSwup_PerformSoftwareUpdate() function must
 *    be called, because the mobile is already in update-mode !
 *
 *
 * \param wUpdateNumber Number of the current Update
 * \param WhichCom      ComPort of this Update
 *
 * \param punVoltage   Pointer to the Voltage in Millivolt
 * \param ulSpeed    the max speed that can be driven on this PC , ( use ADDIDATA-Baudrates even if
 *                    you have a fastboot-card installed )
 *
 * \retval  TRUE  everything is fine
 * \retval  FALSE Some Error occurred, call WSwup_GetLastError() or WSwup_GetLastErrorString()
 *
 * \ingroup bfcfun
 */
BOOL SWUPLIBDLLEXIMPORT WSwup_CheckUpdateVoltage( WORD wUpdateNumber , t_SwupCom WhichCom , unsigned short * punVoltage, unsigned long ulSpeed );

/*  ------------------------------------------------------------------------
 * WSwup_CheckUpdateVoltageScout
 *  ------------------------------------------------------------------------ */
/**
 * Tries to communicate to a "living" mobile to determine if the voltage is ok.
 *  Switches the Mobile on, if necessary and afterwards switches it off, so
 *  that afterwards the softwareupdate itself can be performed.
 *  Calls several times the pfnVoltageCheck CallbackFunction.<br>
 *  In case this update is an update with the new behaviour ( introduced for
 *  the K45-family ) set via WSwup_SetUpdateConceptMode() this function
 *  has a slightly different behaviour:
 *  - this routine MUST be called, because it initiates the update !
 *  - ( with BootStrapMode this routine is an option )
 *  - it does not try to switch on the mobile, endusers dont have an ignition line.
 *  - due to this : if connection via ping is not possible, this routine fails.
 *  - the filetype is checked, only a complete Mobile-SW can be updated with this new mode
 *  - partitial SW ( Diff/Tegic/Language/... ) will be refused.
 *  - after having pinged and checked the voltage, this routine forces the mobile into
 *    the new update-mode, without really switching off.
 *  - due to this it's necessary to pass the new baudrate-parameter, which will be used for the following
 *    update-procedure itself
 *  - after sucessfully returning from this function, the WSwup_PerformSoftwareUpdate() function must
 *    be called, because the mobile is already in update-mode !
 *
 *
 * \param wUpdateNumber Number of the current Update
 * \param WhichCom      ComPort of this Update
 *
 * \param punVoltage   Pointer to the Voltage in Millivolt
 * \param ulSpeed    the max speed that can be driven on this PC , ( use ADDIDATA-Baudrates even if
 *                    you have a fastboot-card installed )
 * \param bCheckVoltResult Get the voltage, check if it's above 3,9V if TRUE; skip the result if bCheckVoltResult==FALSE.
 *
 * \retval  TRUE  everything is fine
 * \retval  FALSE Some Error occurred, call WSwup_GetLastError() or WSwup_GetLastErrorString()
 *
 * \ingroup bfcfun
 */
BOOL SWUPLIBDLLEXIMPORT WSwup_CheckUpdateVoltageScout( WORD wUpdateNumber , t_SwupCom WhichCom , unsigned short * punVoltage, unsigned long ulSpeed,BOOL bCheckVoltResult );
 
/*  ------------------------------------------------------------------------
 * WSwup_CheckUpdateSuccess
 *  ------------------------------------------------------------------------ */
/**
 * Checks if Mobile-SW-Update was successfull.
 * Tries to switch on the Mobile and to ping it, to check if the Mobile-SW is okay.<br>
 * <b>NEW</b>Afterwards the mobile is being switched OFF, to avoid errors
 * with different behaviour between switching on via tool and via key-press.<br>
 * Problems are: AT-C doesnt work correctly, Carkit doesnt work correctly.
 *
 * \param  wUpdateNumber Number of the current Update
 * \param  WhichCom      ComPort of this Update
 *
 *
 * \retval  TRUE  everything is fine
 * \retval  FALSE Some Error occurred, call WSwup_GetLastError() or WSwup_GetLastErrorString()
 *
 * \ingroup bfcfun
 */

BOOL SWUPLIBDLLEXIMPORT WSwup_CheckUpdateSuccess( WORD wUpdateNumber , t_SwupCom WhichCom );




/***************************************************************************************************************
 *
 *
 *      FILE-Functions, read XBI-File , release XBI-File, get Information about XBI-File
 *
 *
 ***************************************************************************************************************/
/**
 * \defgroup filefun FILE-Functions
 */


/**
 * Callbackfunction for FileReading.
 * This function is called several times from inside the library during reading of the
 * XBI-File to give the user of the library the possibility to show the read-progress to the
 * enduser.
 * \param ulAmountOfBytesToRead First Parameter the is the Amount of Bytes that are to be read
 * \param ulCurrentRead         Second Parameter is the current amount of bytes Read
 * \return void
 *
 * \ingroup filefun
 *
 */
typedef void ( * FileReadProgressCallBack ) ( unsigned long ulAmountOfBytesToRead, unsigned long ulCurrentRead  );



/**
 * Prepares the WSWUP-Library for updating an "unknown" project.
 * This function must be called before calling of WSwup_ReadXbiFile() in case the
 * development-project is not known to the library. This only happens during development-phase
 * on introduction of new projects. Normally the Library must know all projects to load the right
 * Update-DLL depending on the read in XBI-File. So if a new project is derived from an already known
 * project, this function can be called to tell the library which update-dll shall be loaded, if an
 * specific unknown project happens to be in the XBI-File.
 *
 * \param pszUnknownProjectName           Name of the project that is unknown to library up to now.
 * \param pszDerivedFromKnownProjectName  Name of the project that is known to library and who's update-DLL should be used.
 * \return void
 *
 * \ingroup filefun
 *
 */

void SWUPLIBDLLEXIMPORT WSwup_PrepareForUpdateWithUnknownProject( char * pszUnknownProjectName, char * pszDerivedFromKnownProjectName );



/*  ------------------------------------------------------------------------
 * WSwup_ReadXbiFile
 *  ------------------------------------------------------------------------ */
/**
 * Reads the XBI-File with the given name into memory, so a swup can be performed.
 * Is NOT done in a THREAD, so if the function returns the data is read.
 * Several times during the read-prcess the via function-ptr given callbackfunction
 * is called so that you can show the readprogress to the enduser.
 *
 * \param pszXbiName       Name of the XBI-File to be read with complete path and extension
 * \param pfnReadProgress  Pointer to a callbackfunction to show read progress
 *
 * \param pSwInformation   Pointer to a t_SwInformation Struct where the Information about the
 *                                  SW will be stored by this function
 *
 * \retval TRUE  -> everything is fine
 * \retval FALSE -> Some Error occurred, call WSwup_GetLastFileError()
 *
 * \ingroup filefun
 */
BOOL SWUPLIBDLLEXIMPORT WSwup_ReadXbiFile( t_SwInformation * pSwInformation, FileReadProgressCallBack pfnReadProgress, char * pszXbiName );




/*  ------------------------------------------------------------------------
 * WSwup_ReadXbiFileFromHeap
 *  ------------------------------------------------------------------------ */
/**
 * Checks an XBI-File in heap so a swup can be performed.
 * This is to provide a similiar functionality like function
 * WSwup_ReadXbiFile() .
 * The difference is, that the user of the library has to allocate the
 * needed memory by himself.
 * He also has to read in the input-file as a binary file to the allocated heap.
 * Before end of the program this memory must be freed by the user of the library.
 * <b>Attention:</b> The library uses this heap, so you are
 * not allowed to free this memory before the end of your program.
 *
 *
 * \param pSwInformation   Pointer to a t_SwInformation Struct where the Information about the
 *                                  SW will be stored by this function
 * \param pucMem           Pointer to start of heap with file, read-only access from inside library
 * \param ulBytesInHeap    bytes in heap
 *
 * \retval TRUE  -> everything is fine
 * \retval FALSE -> Some Error occurred, call WSwup_GetLastFileError()
 *
 * \ingroup filefun
 */
BOOL SWUPLIBDLLEXIMPORT WSwup_ReadXbiFileFromHeap( t_SwInformation * pSwInformation,
                                                   unsigned char * pucMem,
                                                   unsigned long ulBytesInHeap );



/*  ------------------------------------------------------------------------
 * WSwup_GivePtrToBinData
 *  ------------------------------------------------------------------------ */
/**
 * once WSwup_ReadXbiFileFromHeap() is successfully called, this function
 * delivers a ptr to start of bin data in heap.
 *
 * Usually there is no need to call this function, the heap ptr
 * is used in right manner internally, but maybe there is some interest...
 *
 * \retval NULL  -> WSwup_ReadXbiFileFromHeap() successfully called ?
 * \retval ptr to bin data in heap
 *
 * \ingroup filefun
 */
unsigned char SWUPLIBDLLEXIMPORT * WSwup_GivePtrToBinData( void );





/*  ------------------------------------------------------------------------
 * WSwup_GetLastFileError
 *  ------------------------------------------------------------------------ */
/**
 * Returns a pointer to a string describing the last error occured on FileReading.
 * Currently the error-strings are hardcoded in english language in the library.
 *
 *
 * \return pointer to a descriptive string about an FileReadError
 *
 * \ingroup errorfun
 *
 */
char SWUPLIBDLLEXIMPORT  * WSwup_GetLastFileError( void );


/*  ------------------------------------------------------------------------
 * WSwup_CloseXbiFile
 *  ------------------------------------------------------------------------ */
/**
 * Releases all memory allocated on WSwup_ReadXbiFile .
 *           Must be called before reading another file, before closing
 *           the program or if an Error occured on WSwup_ReadXbiFile() !
 *
 *
 * \return void
 *
 * \ingroup filefun
 */
void SWUPLIBDLLEXIMPORT WSwup_CloseXbiFile( void );


/*  ------------------------------------------------------------------------
 * WSwup_CloseXbiFile
 *  ------------------------------------------------------------------------ */
/**
 * Releases all memory allocated inside of WSwup_ReadXbiFileFromHeap .
 *           Must be called before:
 *           - closing the program
 *           - before reading another file into your heap
 *           - or if an error occured on WSwup_ReadXbiFileFromHeap() !
 *
 *
 * \return void
 *
 * \ingroup filefun
 */
void SWUPLIBDLLEXIMPORT WSwup_CloseXbiFileHeap( void );


/***************************************************************************************************************
 *
 *
 *      DEBUG-Functions for enabling and disabling OnLine-Debug
 *      I recommend DEBUGVIEW from www.sysinternals.com as viewer
 *      Currently only works in the debug-versions of the DLLs !
 *
 ***************************************************************************************************************/
/**
 * \defgroup debugfun DEBUG-Functions for en/disabling OnLine-Debug
 */

/**
 * Enable one or more of the follwing defines ( combined via | ) to enable debugging for the differnt parts.
 */
#define MAIN_DEBUG_GROUP    0x01    /**< Enable Main-Functionality Debugging \ingroup debugfun */
#define FILE_DEBUG_GROUP    0x02        /**< Enable File-Function Debugging  \ingroup debugfun*/
#define COMM_DEBUG_GROUP    0x04        /**< Enable Debugging on Communciation-Functions \ingroup debugfun */
#define BFC_DEBUG_GROUP      0x08    /**< Enable Debugging on BFC-Communciation-Functions \ingroup debugfun */

/**
 * Debugging-Level
 * \ingroup debugfun
 */
typedef enum
{
    enNoDebug = 0,                          /**< No debugging */
    enLowDebug = 1,                     /**< Low debugging */
    enMidDebug = 2,                     /**< Mid-Range debugging */
    enHighDebug = 3                     /**< Debug everything */
} t_DebugLevel;

/*  ------------------------------------------------------------------------
 * WSwup_EnableOnlineDebugging
 *  ------------------------------------------------------------------------ */
/**
 * Enables Online Debugging on the requested DebugLevel for the requested Groups
 *
 * \param  RequestedDebugLevel   The DebugLevel ( a t_DebugLevel enum )
 * \param  wRequestedDebugGroups a combination of the above Debug-Groups
 *
 * \return void
 *
 * \ingroup debugfun
 */
void SWUPLIBDLLEXIMPORT WSwup_EnableOnlineDebugging( t_DebugLevel RequestedDebugLevel,  WORD wRequestedDebugGroups );


/*  ------------------------------------------------------------------------
 * WSwup_DisableOnlineDebugging
 *  ------------------------------------------------------------------------ */
/**
 * Disables Online Debugging
 *
 * \return void
 *
 * \ingroup debugfun
 */
void SWUPLIBDLLEXIMPORT WSwup_DisableOnlineDebugging( void  );



/*  ------------------------------------------------------------------------
 * WSwup_EnableFileDebugging
 *  ------------------------------------------------------------------------ */
/**
 * Enables File Debugging on the requested DebugLevel for the requested Groups
 *
 * \param  RequestedDebugLevel   The DebugLevel ( a t_DebugLevel enum )
 * \param  wRequestedDebugGroups a combination of the above Debug-Groups
 * \param  szFilePrefix  Name of the files to debug into, without extension !
 *
 * \return void
 *
 * \ingroup debugfun
 */
void SWUPLIBDLLEXIMPORT WSwup_EnableFileDebugging( t_DebugLevel RequestedDebugLevel,  WORD wRequestedDebugGroups,
                                                     char *szFilePrefix  );


/*  ------------------------------------------------------------------------
 * WSwup_DisableFileDebugging
 *  ------------------------------------------------------------------------ */
/**
 * Disables File Debugging
 *
 * \return void
 *
 * \ingroup debugfun
 */
void SWUPLIBDLLEXIMPORT WSwup_DisableFileDebugging( void  );




/***************************************************************************************************************
 *
 *
 *      SOFTWARE-Update-Functions
 *
 *
 ***************************************************************************************************************/
/**
 * \defgroup swupfun SOFTWARE-Update-Functions
 * The whole softwareupdate is performed with one functioncall : WSwup_PerformSoftwareUpdate()
 * The function itself terminates directly, it will generate a thread.
 * So it is possible to call the function several times to perform software-updates
 * in parallel on different comports.
 * In the generated thread the following steps are performed:
 * - connection to a switched off mobile with the bootstraploader
 * - transmission of the update-sw
 * - erasure of the flash
 * - transmission of the new mobile-software
 *
 * To allow communication between the library and the mainprogram, the user
 * has to install several callbackfunctions which will be called from inside the
 * library. The callbackfunctions are called in this order :
 * - BootstrapProgressCallBack()
 * - UpdateSwTransmissionStartCallBack()
 * - UpdateSwTransmissionProgressCallBack()
 * - FlashTypeCallBack()
 * - EraseProgressCallBack()
 * - MobileSwTransmissionStartCallBack()
 * - MobileSwTransmissionProgressCallBack()
 * - MobileSwUpdateSuccessCallBack()
 *
 * In case this is an update following the new concept ( introduced for the K45-family )
 * set via WSwup_SetUpdateConceptMode() the following call-back-functions will
 * <b>NOT</b> be called, because these steps are not done from inside the library,
 * the mobile will perform this steps by itself automatically:
 * - BootstrapProgressCallBack()
 * - UpdateSwTransmissionStartCallBack()
 * - UpdateSwTransmissionProgressCallBack()
 *
 * If an error occurs during the update-process the following callbackfunction will
 * be called from inside the library:
 * - MobileSwUpdateErrorCallBack()
 *
 * Before erasure of the flash a consistence-check between the new software and the
 * mobile already in the mobile will be performed.
 * If a consistence-error is detected, the following function will be called:
 * - MobileSwUpdateConsistenceProblemCallBack()
 */


/**
 * Callbackfunction for Bootstraploader
 *
 * \param wUpdateNr,  First Parameter is the Update-Nr
 * \param unMaxCalls  Second Parameter is the Max-Amount of Calls of this CallbackFunction
 * \param unCurrCall  Third parameter is the current Call-Number. It can happen that not all Callbacks
 * are done !
 * \return void
 *
 * \ingroup swupfun
 *
 */
typedef void ( * BootstrapProgressCallBack ) ( WORD wUpdateNr, WORD unMaxCalls, WORD  unCurrCall );


/**
 * Callbackfunction for UpdateSwTransmissionStart.
 * This callbackfunction will be called once before the update-sw is
 * beeing transmitted to mobile. If you want to show the percentage
 * of update-sw beeing transmitted, you have to store the parameter
 * ulBytesToTransfer and compare it against the values given by the
 * calls of the callbackfunction UpdateSwTransmissionProgressCallBack()
 *
 * \param wUpdateNr           First Parameter is the Update-Nr
 * \param ulBytesToTransfer   Second Parameter is the amount of data to be sent
 * \return void
 *
 * \ingroup swupfun
 *
 */
typedef void ( * UpdateSwTransmissionStartCallBack ) ( WORD wUpdateNr, unsigned long ulBytesToTransfer );


/**
 * Callbackfunction for UpdateSwTransmissionProgress.
 * This callbackfunction will be called several times during the transmission of the
 * update-sw. This software is executed in the ram of the mobile and is responsible
 * for the erasure of the flash and the reprogramming of the flash with the new mobile-sw.
 *
 * \param wUpdateNr           First Parameter is the Update-Nr
 * \param ulBytesTransfered   Second Parameter is the current amount of sent data
 * \return void
 *
 * \ingroup swupfun
 */
typedef void ( * UpdateSwTransmissionProgressCallBack ) ( WORD wUpdateNr, unsigned long ulBytesTransfered );


/**
 * Callbackfunction for FlashType.
 * This callbackfunction is called once before the flash is beeing
 * erased and it gives the actual flashcode as parameter.
 *
 * \param wUpdateNr       First Parameter is the Update-Nr
 * \param wFlashId        Second Parameter is the Flash-Code
 * \param pszFlashString  Third Parameter is a string to an Description of the Flash
 * \return void
 *
 * \ingroup swupfun
 */
typedef void ( * FlashTypeCallBack ) ( WORD wUpdateNr, WORD wFlashId, char * pszFlashString );


/**
 * Callbackfunction for EraseProgress.
 * This callbackfunction is called several times during the flash-erase-process.
 *
 * \param wUpdateNr            First Parameter is the Update-Nr
 * \param wAmountFlashBlocks   Second Parameter is the number of flash-blocks to erase
 * \param wCurrentBlock        Third Parameter is the current number of flashblock that is beeing erased
 * \return void
 *
 * \ingroup swupfun
 */
typedef void ( * EraseProgressCallBack ) ( WORD wUpdateNr, WORD wAmountFlashBlocks, WORD wCurrentBlock );


/**
 * Callbackfunction for MobileSwTransmissionStart.
 * This callbackfunction is called from SWUPLIB at the beginning of the update-process.
 * If the application wants to show the percentage of completion, it must
 * save the value given by ulBytesToTransfer for later comparison of the actual value
 * ( given via MobileSwTransmissionProgressCallBack() ) with the stored value.
 *
 * \param wUpdateNr          First Parameter is the Update-Nr
 * \param ulBytesToTransfer  Second Parameter is the amount of data to be sent
 * \return void
 *
 * \ingroup swupfun
 */
typedef void ( * MobileSwTransmissionStartCallBack ) ( WORD wUpdateNr, unsigned long ulBytesToTransfer  );

/**
 * Callbackfunction for MobileSwTransmissionProgress.
 * This callbackfunction is called from SWUPLIB during the update-process to give
 * the user of the Library the possibility to show the current
 * transmission-progress. Compare the given value against the value given by callbackfunction
 * MobileSwTransmissionStartCallBack() to show the percentage of data beeing transmitted.
 *
 * \param wUpdateNr          First Parameter is the Update-Nr
 * \param ulBytesTransfered  Second Parameter is the current amount of sent data
 * \return void
 *
 * \ingroup swupfun
 */
typedef void ( * MobileSwTransmissionProgressCallBack ) ( WORD wUpdateNr, unsigned long ulBytesTransfered  );


/**
 * Callbackfunction for SoftwareUpdateSuccess.
 * This Callbackfunction is called from inside the SWUPLIB if the complete update
 * was successfull.
 *
 * \param wUpdateNr First Parameter is the Update-Nr
 * \return void
 *
 * \ingroup swupfun
 */
typedef void ( * MobileSwUpdateSuccessCallBack ) ( WORD wUpdateNr );

/**
 * Callbackfunction for SoftwareUpdateError.
 * This Callbackfunction is called from inside the SWUPLIB if an error occured
 * inside the Library. Call WSwup_GetLastErrorString() to retrieve an error-description.
 *
 * \param wUpdateNr First Parameter is the Update-Nr
 * \return void
 *
 * \ingroup swupfun
 */
typedef void ( * MobileSwUpdateErrorCallBack ) ( WORD wUpdateNr );



/**
 * Possible Errors on Consistence-Check between Mobile and New SW ( combined via or )
 *
 */
#define CONSISTENCE_PRODUCT_ERROR         0x01  /**< SW and Mobile are different products \ingroup swupfun */
#define CONSISTENCE_SWVERSION_ERROR       0x02  /**< Mobile has newer SVN than the new SW \ingroup swupfun */
#define CONSISTENCE_SWDATE_ERROR          0x04  /**< Mobile has newer SW-Date than the new SW \ingroup swupfun */


/**
 * Callbackfunction for SoftwareUpdateConsistence-Problem.
 * This function is called by the SWUPLIB if there is a consistence-error between
 * the new SW and the SW that is already in Mobile. The user of the LIB can use
 * the parameters to show the enduser the conflict and let the enduser choose a solution.
 * Depending on this choice the returnvalue of this function must be set to TRUE or FALSE.
 *
 * \param wUpdateNr         First Parameter is the Update-Nr
 * \param pMobileInfo       Second Parameter is a pointer to a struct containing the mobile-information
 * \param pNewSwInfo        Third Parameter is a pointer to a struct containing the new-sw-information
 * \param wErrorComposition Fourth Parameter is a composition of the different error-possibilities
 *
 * \retval TRUE  -> must be set to TRUE by the user of the LIB , if SW-Update is allowed
 * \retval FALSE -> must be set to FALSE by the user of the LIB , if SW-Update is NOT allowed
 *
 * \ingroup swupfun
 *
 */
typedef BOOL ( * MobileSwUpdateConsistenceProblemCallBack ) ( WORD wUpdateNr, t_SwInformation * pMobileInfo, t_SwInformation * pNewSwInfo, WORD wErrorComposition );





/*  ------------------------------------------------------------------------
 * WSwup_InstallSoftwareUpdateCallBackFunctions
 *  ------------------------------------------------------------------------ */
/**
 * Installs all the needed callbackfunctions for the whole software-update
 *
 * \param  pfnBootstrapProgress            -> Pointer to a CallbackRoutine that is called on Bootstrap
 * \param  pfnUpdateSwTransmissionStart    -> Pointer to a CallbackRoutine that is called on UpdateSwTransmissionStart
 * \param  pfnUpdateSwTransmissionProgress -> Pointer to a CallbackRoutine that is called during UpdateSwTransmission
 * \param  pfnFlashType                    -> Pointer to a CallbackRoutine that is called for Flash-Type
 * \param  pfnEraseProgress                -> Pointer to a CallbackRoutine that is called on during Erasure of Flash
 * \param  pfnMobileSwTransmissionStart    -> Pointer to a CallbackRoutine that is called on Start of MobileSw-Transmission
 * \param  pfnMobileSwTransmissionProgress -> Pointer to a CallbackRoutine that is called during Progress of MobileSw-Transmission
 * \param  pfnMobileSwUpdateSuccess        -> Pointer to a CallbackRoutine that is called if SW-Update was successfull
 * \param  pfnMobileSwUpdateError          -> Pointer to a CallbackRoutine that is called if SW-Update had an error
 * \param  pfnMobileConsistenceProblem     -> Pointer to a CallbackRoutine that is called if there is a consistence-problem
 * \return void
 *
 * \ingroup swupfun
 *
 */
void SWUPLIBDLLEXIMPORT WSwup_InstallSoftwareUpdateCallBackFunctions(
                               BootstrapProgressCallBack pfnBootstrapProgress,
                               UpdateSwTransmissionStartCallBack  pfnUpdateSwTransmissionStart,
                               UpdateSwTransmissionProgressCallBack pfnUpdateSwTransmissionProgress,
                               FlashTypeCallBack pfnFlashType,
                               EraseProgressCallBack   pfnEraseProgress,
                               MobileSwTransmissionStartCallBack pfnMobileSwTransmissionStart,
                               MobileSwTransmissionProgressCallBack pfnMobileSwTransmissionProgress,
                               MobileSwUpdateSuccessCallBack pfnMobileSwUpdateSuccess,
                               MobileSwUpdateErrorCallBack pfnMobileSwUpdateError,
                               MobileSwUpdateConsistenceProblemCallBack pfnMobileConsistenceProblem);

/**
 * Callback-Time for MobileSwUpdateInfoCallBack()
 * \ingroup swupfun
 */


typedef enum
{
        enInfoCallBackEarlyWithBfc,             /**< Callback will be called when Mobile is normal switched on => no timeouts */
        enInfoCallBackLateDuringUpdate          /**< Callback will be called when mobile is already in update-mode => deal with pc-timeouts ! */
} t_InfoCallBackTime;

/**
 * Callbackfunction for SoftwareUpdateInfo.
 * This function is called by the SWUPLIB <b>independent of and before any consistence-errors</b>
 * if the callbackfunction is installed via function : WSwup_InstallSoftwareInfoCallBackFunction().
 * This  means: If you want to get info about the SW already in Mobile, then you have to install
 * this callbackfuntion. If you want to allow the SW-Update, you must return TRUE to the library.
 * But be prepared: If the library itself detects a conflict between new and old SW,
 * the callbackfunction  MobileSwUpdateConsistenceProblemCallBack()
 * will be called, independant of the call of this callbackfunction !
 * If you want to "deinstall" a previosly registered callbackfunction, call function
 * WSwup_InstallSoftwareInfoCallBackFunction() with a NULL-Parameter.<br>
 * <b>Attention: If you return FALSE with this callback-function, the Update will be stopped,
 * but neither  MobileSwUpdateSuccessCallBack() nor MobileSwUpdateErrorCallBack() will be called,
 * because the library does not know the reason why you stopped the update !<br>
 * This means you have to generate and show an error to enduser by yourself !</b>
 *
 *
 * \param wUpdateNr         First Parameter is the Update-Nr
 * \param pMobileInfo       Second Parameter is a pointer to a struct containing the mobile-information
 * \param pNewSwInfo        Third Parameter is a pointer to a struct containing the new-sw-information
 *
 * \retval TRUE  -> must be set to TRUE by the user of the LIB , if SW-Update is allowed
 * \retval FALSE -> must be set to FALSE by the user of the LIB , if SW-Update is NOT allowed
 *
 * \ingroup swupfun
 *
 */


typedef BOOL ( * MobileSwUpdateInfoCallBack ) ( WORD wUpdateNr, t_SwInformation * pMobileInfo, t_SwInformation * pNewSwInfo );



/*  ------------------------------------------------------------------------
 * WSwup_InstallSoftwareInfoCallBackFunction
 *  ------------------------------------------------------------------------ */
/**
 * Installs the MobileSwUpdateInfoCallBack-Function.
 *
 * \param  pfnMobileSwUpdateInfoCallBack      -> Pointer to a CallbackRoutine that is called to give info about the SW already in Mobile<br>
 *                                           pass a NULL if you want to deinstall a previosly installed callbackfunction.<br>
 *                                           <b>This is the only place in the LIB where NULL as func-ptr is allowed in the moment !</b>
 * \param  WhichCallbackTime              -> a enum of type \ref t_InfoCallBackTime , where you must select, on which time you want this
 *                                           callbackfunction called. There are two possibilities , either you can have this function called during
 *                                           connection-setup with BFC-Communication or you can select to have this function called later, when
 *                                           update is already running.<br>
 *                                           The reason to have these two different times is : on the one hand you have to deal with timeouts
 *                                           when already really in updatemode, this leads to the early test. On the other hand the early test is less
 *                                           "hacker-proof" because the mobile is in a totally different mode and there is at least a very little chance to
 *                                           exchange two mobiles between the two mobile-states. So its up to the user of the library at which time he wants
 *                                           the CallBack-Function.
 *
 * \return void
 *
 * \ingroup swupfun
 *
 */
void SWUPLIBDLLEXIMPORT WSwup_InstallSoftwareInfoCallBackFunction(
                               MobileSwUpdateInfoCallBack pfnMobileSwUpdateInfoCallBack, t_InfoCallBackTime WhichCallbackTime );


/**
 * Behaviour of the Library concerning the new Update-Concept ( xx45 ).
 *
 */
typedef enum
{
    enForceBSLBehaviour,            /**< force old ( Boot-Strap-Loader ) behaviour, only for development possible, not for customer */
    enForceNewConcept,              /**< force new Update-Concept-Behaviour , must be used for customer-update */
    enUpdateConceptAutoDetect       /**< first try new concept, if mobile doesnt answer, try old BSL-concept, only for development possible, not for customer */
}t_UpdateMode;



/*  ------------------------------------------------------------------------
 * WSwup_SetUpdateConceptMode
 *  ------------------------------------------------------------------------ */
/**
 * Tells the library how to perform the Software-Update.
 * In a development-environment it must be still possible do use the old BSL-behaviour, but for
 * a customer-update its necessary to switch to the new update-mode.
 * For development environment it's also possible to do an autodetect, first the new concept is tried
 * and if this fails ( e.x. because its an old project ) then the old BSL-Mode is activated.
 * If you want to use the new mode ( enForceNewConcept, enAutoDetect ) you MUST call this function
 * before WSwup_CheckUpdateVoltage() and you also MUST call function WSwup_CheckUpdateVoltage() !
 *
 * \param  WhichMode  an \ref t_UpdateMode , which tells the library how to behave
 *
 * \retval TRUE  -> everything prepared
 * \retval FALSE ->
 *
 * \ingroup swupfun
 *
 */

BOOL SWUPLIBDLLEXIMPORT  WSwup_SetUpdateConceptMode( t_UpdateMode WhichMode );

/*  ------------------------------------------------------------------------
 * WSwup_GetUpdateConceptMode
 *  ------------------------------------------------------------------------ */
/**
 * Returns update mode set previously by WSwup_SetUpdateConceptMode
 *    enForceBSLBehaviour: Boot-Strap-Loader
 *    enForceNewConcept: new Update-Concept

 * 
 * \ingroup swupfun
 *
 */

t_UpdateMode SWUPLIBDLLEXIMPORT  WSwup_GetUpdateConceptMode( );



/*  ------------------------------------------------------------------------
 * WSwup_PerformSoftwareUpdate
 *  ------------------------------------------------------------------------ */
/**
 * Performs the Software-Update on the given ComPort with the given Baudrate.
 *           Attention: this function creates a thread, so the function itself will
 *           terminate very fast, so that further things can be done.
 *           The communication with the main-program will be done via the above CallbackFunctions
 *
 *
 * \param  wUpdateNr  The current number for the update, up to four are allowed
 * \param  WhichCom   The Comport on which the update shall be progressed
 * \param  ulSpeed    the max speed that can be driven on this PC , ( use ADDIDATA-Baudrates even if
 *                    you have a fastboot-card installed, the mapping is done internally via the INI-FILE
 *
 * \retval TRUE  -> SW-Update is Running ( not finished ! )
 * \retval FALSE -> No Callbacks Installed
 *
 * \ingroup swupfun
 *
 */

BOOL SWUPLIBDLLEXIMPORT  WSwup_PerformSoftwareUpdate( WORD wUpdateNr, t_SwupCom WhichCom, unsigned long ulSpeed );



/*  ------------------------------------------------------------------------
 * WSwup_SetBootPIN
 *  ------------------------------------------------------------------------ */
/**
 *  Save a PIN for an Update, This PIN must be provided by data stored in PICS
 *  and is sended during BSL connect attempt. This PIN is used for disabled BSL
 *  mode devices. If the PIN is correct the mobile will accept the update sw.
 *  A PIN can be reseted by calling this function with unPinSize==0 or
 *  pucBootPIN==NULL
 *
 * \param  wUpdateNr  The current number for the update, up to four are allowed
 * \param  unPinSize  Number of data bytes of Boot PIN (16 Byte(128Bit) in the moment)
 * \param  pucBootPIN Pointer to PIN Data
 *
 *
 * \retval TRUE  -> PIN was set /reseted
 * \retval FALSE -> unPINSize or wUpdateNr data to large/ not supported
 *
 * \ingroup swupfun
 *
 */

BOOL SWUPLIBDLLEXIMPORT WSwup_SetBootPIN(WORD wUpdateNr, unsigned int unPinSize, unsigned char * pucBootPIN);


/*  ------------------------------------------------------------------------
 * CallBack Function
 *  ------------------------------------------------------------------------ */
/**
 * Callbackfunction for ShowMapTransmissionProgressCallBack.
 * This callbackfunction will be called several times during the transmission of the
 * std Mapping/Delta mapping transfer. .
 *
 * \param ulBlocksTransffered  - Second Parameter is the current amount of sent data
 * \return void
 *
 * \ingroup swupfun
 */
typedef void ( * ShowMapTransmissionProgressCallBack ) ( unsigned int uiTotalBlocks, unsigned int uiBlocksTransffered );

/*  ------------------------------------------------------------------------
 * WSwup_InstallMapInfoCallBackFunction
 *  ------------------------------------------------------------------------ */
/**
 * Call  WSwup_InstallMapInfoCallBackFunction. Only for back-compatibility.
 * \param pfnUpdateMapSuccess           Pointer to a CallbackRoutine that is called after success map update
 * \param pfnUpdateMapFailure           Pointer to a CallbackRoutine that is called whenever there is error
 * \param pfnMapTransmissionProgress    Pointer to a CallbackRoutine that is called during the map update
 *
 * \return void
 *
 * \ingroup
 */
void SWUPLIBDLLEXIMPORT WSwup_InstallMapInfoCallBackFunction(
                        MobileSwUpdateSuccessCallBack       pfnUpdateMapSuccess,
                        MobileSwUpdateErrorCallBack         pfnUpdateMapFailure,
                        ShowMapTransmissionProgressCallBack pfnMapTransmissionProgress);

/*  ------------------------------------------------------------------------
 * WSwup_SetNextStartMode
 *  ------------------------------------------------------------------------ */
/**
 * Sets the Next start up type after the current SW update.
 * by default : NORMAL MODE . for SCOUT Tool , to update the MAP/Delta map, it should be SERVICE MODE
 * \param Which_Mode : after the current update, which mode the Mobile has to boot.
 *                     0 - NORMAL MODE
 *                     1 - SERVICE MODE
 *
 * \retval  TRUE  always
 */
BOOL SWUPLIBDLLEXIMPORT WSwup_SetNextStartMode(BOOL Which_Mode);

/*  ------------------------------------------------------------------------
 * WSwup_PerformMapUpdate
 *  ------------------------------------------------------------------------ */
/**
 * Call  WSwup_PerformMapUpdate. This is the function will be called from the application for the
 * map update.
 * \param pMapStart  Pointer to starting location of the mapping data.
 * \param WhichCom   on Which comport the data transfer need to happen
 * \param MapInfo    pointer to the structure where all the map data copied.
 *
 * \return BOOL
 * \retval TRUE  -> SW-Update is Running ( not finished ! )
 * \retval FALSE -> No Callbacks Installed
 * \ingroup
 */
BOOL SWUPLIBDLLEXIMPORT WSwup_PerformMapUpdate( char* pMapStart,
                                                t_SwupCom WhichCom,
                                                MAPINFO* MapInfo);

/*  ------------------------------------------------------------------------
 * WSwup_ReadMapHeaderFromHeap
 *  ------------------------------------------------------------------------ */
/**
 * Call  WSwup_ReadMapHeaderFromHeap will read the mapping information from the heap
 * and updates the Mapinfo strcuture.
 *
 * \param pMapStart  Pointer to starting location of the mapping data.
 * \param ulMapLen   Length of the Map file
 * \param MapInfo    pointer to the structure where all the map data to be copied.
 *
 * \return BOOL
 * \retval 0  -> Success read
 * \retval -1 -> Internal error happened
 * \ingroup
 */
int SWUPLIBDLLEXIMPORT WSwup_ReadMapHeaderFromHeap(char* pMapStart,
                              unsigned long ulMapLen,
                              MAPINFO* MapInfo);

/*  ------------------------------------------------------------------------
 * WSwup_GetHeapInfo
 *  ------------------------------------------------------------------------ */
/**
 * Call  WSwup_GetHeapInfo will update the all the file size and their starting position
 * to the pScoutHeapInfo structure.
 *
 * \param pucHeap    Pointer where all the information is stored.
 * \param ulMapLen   Length of the Heap
 * \param MapInfo    pointer to the structure where all file Length and file location will be
 *                   stored.
 *
 * \return void
 *
 * \ingroup
 */
void SWUPLIBDLLEXIMPORT WSwup_GetHeapInfo(unsigned char *pucHeap, unsigned long ulHeapSize, SCOUTFileInfo * pScoutHeapInfo);

/*  ------------------------------------------------------------------------
 * WSwup_MallocHeapAndReadFile
 *  ------------------------------------------------------------------------ */
/**
 * Call  WSwup_MallocHeapAndReadFile will read the given file (exe) and put all the contents
 * in the RAM area. and it will update the length of the heap also.
 *
 * \param ppucLocalHeap     Pointer to the heap location where the SCOUT contents are stored.
 * \param pulBytesInHeap    Length of the Heap
 * \param pszFileName       Pointer to string (File name)
 * \param pfnReadProgress   Function pointer to show the file read progress bar.
 *
 * \return  BOOL
 * \retval  TRUE            if the File read properly..
 * \retval  FALSE           if file contents read is failed
 * \ingroup
 */
BOOL SWUPLIBDLLEXIMPORT WSwup_MallocHeapAndReadFile(unsigned char **ppucLocalHeap,
                                  unsigned long *pulBytesInHeap,
                                  char *pszFileName,
                                  FileReadProgressCallBack pfnReadProgress );



/*  ------------------------------------------------------------------------
 * WSwup_PerformSoftwareUpdateDeveloperUSB
 *  ------------------------------------------------------------------------ */
/**
 * Performs the Software-Update on the given ComPort with the given Baudrate.
 *           Attention: this function creates a thread, so the function itself will
 *           terminate very fast, so that further things can be done.
 *           The communication with the main-program will be done via the above CallbackFunctions
 *
 *
 * \param  wUpdateNr  The current number for the update, up to four are allowed
 * \param  WhichCom   The Comport on which the update shall be progressed
 * \param  ulSpeed    the max speed that can be driven on this PC , ( use ADDIDATA-Baudrates even if
 *                    you have a fastboot-card installed, the mapping is done internally via the INI-FILE
 * \param  bUseUSB    Enables or disables update via USB
 *
 * \retval TRUE  -> SW-Update is Running ( not finished ! )
 * \retval FALSE -> No Callbacks Installed
 *
 * \ingroup swupfun
 *
 */

BOOL SWUPLIBDLLEXIMPORT  WSwup_PerformSoftwareUpdateDeveloperUSB( WORD wUpdateNr, t_SwupCom WhichCom, unsigned long ulSpeed, BOOL bUseUSB );

/*  ------------------------------------------------------------------------
 * WSwup_InstallEraseAraeaHandler
 *  ------------------------------------------------------------------------ */
/**
 * Gives opportunity to catch erase area(s) during reading mobile-sw's header.
 * Use of this function is optional, by default handler is set to NULL.
 * Call this function before 'WSwup_MallocHeapAndReadFile'
 *
 * \param  pfEraseArea  Pointer to erase area handler
 * 
 * 
 *
 * \ingroup swupfun
 *
 */

void SWUPLIBDLLEXIMPORT  WSwup_InstallEraseAraeaHandler(EraseAreaHandler pfEraseArea);


/*  ------------------------------------------------------------------------
 * WSwup_InstallEndThreadFunction
 *  ------------------------------------------------------------------------ */
/**
 * Call this function when you want to use your own function which ends thread,
 * when you use MFC thread for example.
 * This function must be called after 'WSwup_InitLibrary', cause there is default 
 * ending thread function '_endthread' installed.
 *
 * \param  fnEndThread   Pointer to function which ends thread
 * 
 *
 * \ingroup swupfun
 *
 */

void SWUPLIBDLLEXIMPORT WSwup_InstallEndThreadFunction(EndThread fnEndThread);

/*  ------------------------------------------------------------------------
 * WSwup_UseSeparateThreadForUpdateFunctions
 *  ------------------------------------------------------------------------ */
/** 
 * Call this function when you want to change of internal behaviour of WSwup_PerformSoftwareUpdate 
 * and WSwup_PerformMapUpdate functions. 
 * Setting bSet to TRUE causes creation of new thread in which update functions 
 * runs (default). Additionaly ending thread function is being called at the end of update functions.
 *
 * Setting bSet to FALSE causes run update function in the same thread as update functions, it is 
 * useful when update functions are called from separate thread and there is no need to create 
 * another one. No ending thread function is being called at the end of update functions.
 * 
 *
 * \param  bSet  Determines internal WSwup_PerformSoftwareUpdate behavior
 * 
 *
 * \ingroup swupfun
 *
 */


void SWUPLIBDLLEXIMPORT WSwup_UseSeparateThreadForUpdateFunctions(BOOL bSet);


/*  ------------------------------------------------------------------------
 * WSwup_InstallExtractBitmapFunction
 *  ------------------------------------------------------------------------ */
/**
 * Call this function when you want to install function which extracts bitmap from bundle
 *
 * \param  fnExtractBitmap   Pointer to function which extracts bitmap from bundle
 * 
 *
 * \ingroup swupfun
 *
 */

void SWUPLIBDLLEXIMPORT WSwup_InstallExtractBitmapFunction(ExtractBitmap fnExtractBitmap);

/*  ------------------------------------------------------------------------
 * WSwup_SetLastChanceUpdate
 *  ------------------------------------------------------------------------ */
/**
 * Call this function with TRUE when mobile does not start (mobile's software failes and user has to boot
 *  device manually ) and is not connected to Bootadapter
 *
 * \param  bSet TRUE - use last chance update, FALSE use standard update
 * 
 *
 * \ingroup swupfun
 *
 */

void SWUPLIBDLLEXIMPORT WSwup_SetLastChanceUpdate(BOOL bSet);


BOOL SWUPLIBDLLEXIMPORT WSwup_GetLastChanceUpdate();




#endif // _SWUPLIB_HEADER_
