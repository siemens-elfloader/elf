/*                       Munich,  Germany
                     COMPANY CONFIDENTIAL
                     All Rights Reserved

.AUTHOR         U. Schmitt, ICM MP PO8 MCH53

.PROJECT        WINSWUP

.SHORT_DESCR    Interface to the lowlayer-DLL

.SW_COMPONENT

.SW_TYPE

.VERSION        1.08             please increase the two defines !!!

.DATE           2005-04-09

.EXIT_CODES

.STATUS         FIRST_TRY

.CHANGE_CONTROL

Version |  Date    | Changed by | Reason for Change
--------+----------+------------+----------------------------------------------
 0.1    |2002-09-02| D.Dittmer  | file created, content drawn from err_text.h
--------+----------+------------+----------------------------------------------
 0.2    |2002-10-28| L.Sillge   | entry en_SIG_SW_REJECTED added
--------+----------+------------+----------------------------------------------
 0.3    |2003-01-29| L.Sillge   | entry en_SIG_SW_CORRUPT added
--------+----------+------------+----------------------------------------------
 0.4    |2003-09-18| H.G.Weyers | entry en_BOOTCORE_NOT_ACKNOWLEDGE
--------+----------+------------+----------------------------------------------
 0.5    |2003-09-26| H.G.Weyers | entry en_ERR_ADDITIONAL_MAP_INFO
--------+----------+------------+----------------------------------------------
 0.6    |2003-10-27| H.G.Weyers | entry en_PROJECT_NOT_SET
        |          |            |       en_PROJECT_NOT_SUPPORTED
        |          |            |       en_ADDMAPINFO_WRONG_SIZE
        |          |            |       en_ADDMAPINFO_BUFFER_OVERWRITE
        |          |            |       en_ADDMAPINFO_LEN_NOT_SET
        |          |            |       en_LENCHECK_ILLEGAL_COMMAND
        |          |            |       en_LENCHECK_BUFFER_OVERRUN
        |          |            |       en_LENCHECK_CHECKSUM_INVALID
        |          |            |       en_LENCHECK_ADDRESS_CHECKSUM_INVALID
        |          |            |       en_LENCHECK_INVALID_STATE
        |          |            |       en_LENCHECK
        |          |            |       en_WRONG_BLOCK_OR_ADDRESS
        |2003-11-10| H.G.Weyers | entry en_NO_32BIT_FILE
        |          |            |       en_OLD_STRINGIDENTIFICATION
--------+----------+------------+----------------------------------------------
 0.7    |2003-12-08| H.G.Weyers | modified parameter from  en_BYTE_PROG (%02X%02X%02X%02X) to show 32-Bit address
--------+----------+------------+----------------------------------------------
 0.8    |2004-01-29| J. Garrido | Change any reference to BFB to BFC
        |          |            | Chage en_ONLY_EGOLD to en_ONLY_SGOLDLITE
--------+----------+------------+----------------------------------------------
 0.9    |2004-03-08| J. Garrido | New string for en_BOOTCORE_NOT_ACKNOWLEDGE
        |          |            | Neww error en_SIG_NOT_FREEZED
--------+----------+------------+----------------------------------------------
 1.0    |2004-03-08| J. Garrido | New error:
        |          |            |     en_BC_INTERFACE_NOT_OK
        |          |            |     en_DEVCON_NOT_OK
        |          |            |     en_CHARGER_PRESENT
        |          |            |     en_BC_HW_INTERFACE_NOT_SUPPORTED
        |          |            |     en_BC_BAUDRATE_NOT_SUPPORTED
        |          |            |     en_MEM_ERROR
--------+----------+------------+----------------------------------------------
 1.01   |2004-05-26| J. Garrido | en_DEFAULT_CMD_BLOCKS is now used.Just comment removed
--------+----------+------------+----------------------------------------------
 1.02   |2004-08-26| J. Garrido | change text for en_DEVCON_NOT_OK
--------+----------+------------+----------------------------------------------
 1.03   |2004-09-01| J. Garrido | Correction on text for en_CHARGER_PRESENT
--------+----------+------------+----------------------------------------------
 1.04   |2004-12-09| M. Untucht |New error:
        |          |            |     en_BFC_POWER_SUPPLY_LESS
--------+----------+------------+----------------------------------------------
 1.05   |2004-09-01| J. Garrido | Add  en_CMDSEC_ERROR
--------+----------+------------+----------------------------------------------
 1.06   |2005-03-21|L&T Infotech| Added more error description related to Mapping update
--------+----------+------------+----------------------------------------------
 1.07   |2004-03-23| J. Garrido | Add  en_BFC_UNKNOWN_ANSWER
--------+----------+------------+----------------------------------------------
 1.08   |2005-04-09|P.Mackenthun| Add  en_WAIT_SYSTEM_DATA_UPDATE_ACK, en_ERR_SYSTEM_DATA_UPDATE
--------+----------+------------+----------------------------------------------
 1.09   |2005-09-07|R.Szul      | Add  en_CANT_OPEN_USB
--------+----------+------------+----------------------------------------------
 1.10   |2005-03-20|K.Gontarz   | en_CANT_FIND_USB and en_NO_ERROR added  
--------+----------+------------+----------------------------------------------

.STILL_TODO
*/
/* INDENT: -nbr -nce -ei -ip -lp -pro -sc -c:33 -cci:3 -cd:33 -ci:3 -cli:3 -cp:0 -d:0 -di:0 -i:3 -l:78 -lc:78 -tabs:3  -tabu */



/*********************************************************************************************************/
#include "forcelib.h"

#define ERR_TEXT_VERS_MAJOR  1
#define ERR_TEXT_VERS_MINOR  08
#define ERR_TEXT_DEVELOPER   "Garrido"


#include <windows.h>
#include "werrenum.h"
#include "err_text.h"



t_enumErrorDescription ErrorDescription[] =
{
	 { en_NO_ERROR ,				  en_ALTER_CONNECT , "Success"},
                                    // wseril1.c
    { en_ALREADY_OPEN ,         en_ALTER_CONNECT , "ComPort is alrady open"},
    { en_CREATE_FILE ,          en_ALTER_CONNECT , "ComOpen : error on CreateFile"},
    { en_SET_COMMSTATE ,        en_ALTER_TRANSMISSION , "Error on Changing Com-State"},
    { en_NOT_OPEN ,             en_ALTER_CONNECT , "ComPort is not open"},
    { en_TIMEOUT ,              en_ALTER_CONNECT , "Error on Changing Timeout"},
    { en_GET_BAUD ,             en_ALTER_CONNECT , "Error on getting baudrate"},
    { en_BAUDRATE ,             en_ALTER_CONNECT , "Error on configuring, false baudrate"},
    { en_WRITE_FILE ,           en_ALTER_CONNECT , "Error on WriteFile"},
    { en_READ_FILE ,            en_ALTER_CONNECT , "Error on ReadFile"},
    { en_INVALID_HANDLE_VALUE , en_ALTER_CONNECT , "Invalid Handle for Com-Port"},

                                    // wseril2.c
    { en_NO_VERSION ,           0 , "No version number of Serial Low-DLL available"},
    { en_DEFAULT_CMD_BLOCKS ,   en_ALTER_TRANSMISSION , "Error in HandleDefaultCmdBlocks"},
    { en_WAIT_ON_CMD_BLOCK ,    en_ALTER_TRANSMISSION , "Error on waiting for CMD-Block"},
    { en_MAX_BIN_LEN_REACHED ,  en_ALTER_TRANSMISSION , "Maximum Bin-length reached"},
    { en_UNKNOWN_BYTE ,         en_ALTER_TRANSMISSION , "Unknown Byte %02X received"},
    { en_REC_TIMEOUT ,          en_ALTER_TRANSMISSION , "Receive-Timeout, nothing received"},
    { en_UNKNOWN_CHAR ,         en_ALTER_TRANSMISSION , "Unknown character received, now flushing inbuf"},
    { en_UNKNOWN_REC_VALUE ,    en_ALTER_TRANSMISSION , "Unknown retval %d from ReceiveValue Value received = %02Xh"},
    { en_COMM_ERROR ,           en_ALTER_TRANSMISSION , "Aborting due to transmission-error"},
    { en_CHECK_SUM_ERROR ,      en_ALTER_TRANSMISSION , "Check sum error"},
    { en_CMD_REC ,              en_ALTER_TRANSMISSION , "Unexpected Cmd-Block received"},
    { en_SERIAL_ERROR ,         en_ALTER_TRANSMISSION , "Error on serial interface"},
    { en_READ_CMD ,             en_ALTER_TRANSMISSION , "Error on read CMD-Block"},		// not used
    { en_WAIT_FF ,              en_ALTER_TRANSMISSION , "Timeout on waiting for FF"},

                                    // wseril3.c
    { en_NO_READY_FLASH_ERASE , en_ALTER_TRANSMISSION , "Error on waiting for FlashBlock-EraseReady"},
    { en_SEND_FLASH_ERASE ,     en_ALTER_TRANSMISSION , "Error on sending Erase-Flash-Block-CMD"},
    { en_ERASE_AREA_NOT_OK ,    en_ALTER_SW_VERSION , "Wrong Erase-Address, not possible from %lXh to %lXh"},
    { en_MALLOC_REQUEST_FLASH_BLOCKS , 0 , "No memory on malloc for Flash-Areas"},
    { en_FLASHBLOCK_SIZE_DEFAULT , en_ALTER_TRANSMISSION , "Unknown Answer from Mobile on request for Erase-Area"},
    { en_TIMEOUT_REQUEST_FLASH_BLOCKS , en_ALTER_TRANSMISSION , "Timeout-Error waiting for Test-Area-ACK"},

                                    // wmob_err.c
    { en_RAM_FF ,               en_ALTER_MOBILE_DEFECT , "Error on RAM-Test with FF"},
    { en_RAM_PATTERN ,          en_ALTER_MOBILE_DEFECT , "Error on RAM-Test with pattern"},
    { en_RAM_00 ,               en_ALTER_MOBILE_DEFECT , "Error on RAM-Test with 00"},
    { en_RAM_UNKNOWN ,          en_ALTER_MOBILE_DEFECT , "Unknown Error on RAM-Test"},
    { en_VOLTAGE_RANGE ,        0 , "Erase-Error Block %d : Vpp voltage range"},
    { en_CMD_SEQUENCE ,         0 , "Erase-Error Block %d : Error in the command sequence"},
    { en_ERASE_NOT_POSSIBLE ,   0 , "Erase-Error Block %d : Erase not possible"},
    { en_NO_BLOCK ,             0 , "Erase-Error Block %d : Block does not exist"},
    { en_BYTE_PROG ,            0 , "Byte-Program-Error Nr:  %d on adress %02X%02X%02X%02X"},
    { en_FINAL_CHECK ,          0 , "Check-sum-error final test"},
    { en_UNKNOWN_FLASH ,        0,  "Unknown flash"},
    { en_NOT_SUPPORTED ,        0 , "Function not supported until now in Mobile"},
    { en_PROJECT_NOT_SET ,            0 , "Project id was not send, so no flash configuration was set and no memory is available"},/* new!*/
    { en_PROJECT_NOT_SUPPORTED,       0 , "No flash mapping and constants available in uploadsw for the requested project id"},	/* new!*/
    { en_ADDMAPINFO_WRONG_SIZE,       0 , "The internal structure length fit not to requested mapinfo length"},					/* new!*/
    { en_ADDMAPINFO_BUFFER_OVERWRITE, 0 , "The size of transfered additional map info fits not to previous send length"},	/* new!*/
    { en_ADDMAPINFO_LEN_NOT_SET,      0 , "No len info was send before additional map info was send"},						/* new!*/
    { en_LENCHECK_ILLEGAL_COMMAND,    0 , "The lencheck file format contains wrong data (illegal command)"},				/* new!*/
    { en_LENCHECK_BUFFER_OVERRUN,     0 , "The lencheck file format contains wrong data (buffer overrun)"},					/* new!*/
    { en_LENCHECK_CHECKSUM_INVALID,   0 , "The lencheck file format contains wrong data (checksum invalid)"},				/* new!*/
    { en_LENCHECK_ADDRESS_CHECKSUM_INVALID, 0 , "The lencheck file format contains wrong data (address checksum invalid)"},	/* new!*/
    { en_LENCHECK_INVALID_STATE,      0 , "The lencheck file format contains wrong data (invalid state)"},					/* new!*/
    { en_LENCHECK,                    0 , "The lencheck file format contains wrong data"},									/* new!*/
    { en_WRONG_BLOCK_OR_ADDRESS,      0 , "Block number or an address is not in flash space"},								/* new!*/
    { en_UNABLE_TO_WRITE_STATISTIC,   0 , "Unable to write statistic"},														/* new!*/
    { en_UNKNOWN_ERROR ,              0 , "Unknown Mobile-Error: %02X"},

    // wbfbtool.c
    { en_BFC_NO_CALLBACK ,      0 , "No CallBackFunctions for BFC-Lib installed"},
    { en_BFC_COMM_NOT_OPEN ,    0 , "Could not open Comport for BFC-Lib, maybe Comport is in use"},
    { en_BFC_MOBILE_NO_SWITCHON,0 , "Could not switch on Mobile"},
    { en_BFC_MOBILE_NO_PING ,   en_ALTER_CONNECT , "Could not Ping Mobile"},
    { en_THIS_FILE_NO_NEW_UPDATE ,  0 , "This file can\'t be updated with new concept"},
    { en_BFC_NO_NEW_UPDATE ,    0 , "No answer from Mobile, maybe not with new Update-Concept ?"},
    { en_BFC_READY_FALSE ,      0 , "BFC : ready and false"},		// not used
    { en_CUSTOMER_REBOOT ,      0 , "Error on requesting customer reboot"}, // not used
    { en_PUT_COUNT ,            0 , "Error on requesting put count"}, // not used
    { en_BC_INTERFACE_NOT_OK,   0 , "Wrong bootcore interface version"},
    { en_DEVCON_NOT_OK,	en_ALTER_CONNECT, "Update not supported with plugged cable"},
    { en_CHARGER_PRESENT,	0, "Simultaneous updating and charging could be dangerous, please remove charger and try again"},
    { en_BC_HW_INTERFACE_NOT_SUPPORTED, en_ALTER_CONNECT, "Update not allow with this device"},
    { en_BC_BAUDRATE_NOT_SUPPORTED, en_ALTER_CONNECT, "Baudrate not supported"},
    { en_MEM_ERROR, en_ALTER_SW, "Mobile Out of Memory"},
	{ en_CMDSEC_ERROR, en_ALTER_SW, "Wrong command sequence by switching in Update mode"},
    { en_BFC_POWER_SUPPLY_LESS,0,  "Battery power is too low. Please charge fully!"},
    { en_BFC_UNKNOWN_ANSWER ,  0 , "Unknown BFC answer from mobile, service not supported from mobile"},

    // swupwork.c
    { en_NO_DATE_TIME ,         en_ALTER_SW_VERSION , "No Date/Time-Info available, impossible to DIFF-Swup"},
    { en_WRONG_DATE_TIME ,      en_ALTER_SW_VERSION , "Wrong Date/Time for DIFF-SWUP ! XDI must fit exactly to SW in Mobile"},
    { en_NO_REQUEST ,           en_ALTER_TRANSMISSION , "No Request for Update-SW after Bootstraploader"},
    { en_ERR_SEND_UPDATE ,      0 , "Error on requesting update-sw"},
    { en_CANT_OPEN ,            en_ALTER_TRANSMISSION , "Opening Comport %d with Speed %d Baud not possible"},
    
	 { en_CANT_FIND_USB ,        en_ALTER_TRANSMISSION , "Not possible to find USB Comport"},
    { en_CANT_OPEN_USB ,        en_ALTER_TRANSMISSION , "Opening USB Comport not possible"},
    

    { en_ERR_WAIT_FLASH_CODE ,  en_ALTER_TRANSMISSION , "Error on waiting for Flash-Code"},
    { en_UNKNOWN_FLASH_CODE ,   0 , "Unknown Flashcode %02X%02X"},
    { en_WAIT_FLASH_SIZE ,      en_ALTER_TRANSMISSION , "Error on Requesting Flash-Size"},
    { en_WRONG_FLASH_SIZE ,     en_ALTER_SW_VERSION , "Error : you are trying to update a SW for %ld Bytes into a Mobile with only space for %ld Bytes !"},
    { en_NO_UPDATE ,            en_ALTER_SW_VERSION , "Error : Update of %s SW not possible into a %s !"},
    { en_INCOMPATIBLE ,         en_ALTER_SW_VERSION , "Error : SW-Date and Version are incompatible, Mobile : %s  Date : %s  <=>  File : %s  Date : %s !"},
    { en_INCOMPATIBLE_VERS ,    en_ALTER_SW_VERSION , "Error : SW-Version is incompatible, Mobile: %s <=> File: %s !"},
    { en_WAIT_SPLIT_ID_ANSWER , 0 , "Error on waiting for Split-ID-Answer"},
    { en_WRONG_SPLIT_ID ,       0 , "Wrong Split-ID, SW and LanguageGroup dont fit together"},
    { en_MALLOC_ERROR ,         0 , "Malloc error"},			// not used
    { en_ENABLE_FLASHBLOCK ,    0 , "Error on enabling flash block"},
    { en_WAIT_COMPRESS_ANSWER , 0 , "Error on waiting for Compression-Answer"},
    { en_WAIT_LANGINFO_ANSWER , 0 , "Error on waiting for LanguageGroup-Answer"},
    { en_WAIT_CALC_SPLIT_INFO_ANSWER , 0 , "Error on waiting for Splitinfo answer"},
    { en_WAIT_STAT_DATA ,       0 , "Error on waiting for Stat-Data"},
    { en_SW_PROJECT ,           0 , "No Update-SW found for Project : %s SVN %2X %s SynchStation"},
    { en_UNABLE_WRITE_BGJ,      0 , "Unable to write BGJ"},
    { en_CANT_CONNECT ,         en_ALTER_CONNECT , "Cant connect to Mobile with BootstrapLoader on Com %d"},
    { en_INCOMPATIBLE_VERSION , 0 , "Library and Executable have different Interface-Versions !"},
    { en_MUTEX ,                0 , "Error opening Mutex. Update Nr: %d"},
    { en_COMPRESS_NOT_SUPPORTED, 0, "Error : Compression/ Algorithm not supported"},
    { en_MOBILE_SW_TRANS ,      en_ALTER_TRANSMISSION , "Error on Transmission"},
    { en_WAIT_ACK_EOT ,         en_ALTER_TRANSMISSION , "Error on waiting for Ack EOT"},
    { en_WAIT_SW_VERSION ,      en_ALTER_TRANSMISSION , "Error on waiting for SW-Version"},
    { en_ERR_ADDITIONAL_MAP_INFO ,      en_ALTER_TRANSMISSION , "Error: AdditionalMapInfo on Comport %d \n"},
    { en_WAIT_SYSTEM_DATA_UPDATE_ACK ,  0 , "Error on waiting for acknowlegde of system data update"},
    { en_ERR_SYSTEM_DATA_UPDATE ,       0 , "System data update error"},

                                    // dyna_dll.c
    { en_SCAN_PROJECTS ,        0 , "Error on ScanDirectoryForAvailableProjects"},
    { en_DLL_OUT_OF_DATE ,      en_ALTER_SW_VERSION , "DLL is out of date, get a new package !"},
    { en_LOAD_FAILED ,          0 , "Load failed : %s"},

                                    // hehawrap.c / fihawrap.c
    { en_LIB_EXE_DIFF ,         0 , "Library and Executable have different Interface-Versions, Executable must be compiled new !"},
    { en_FILE_READ ,            en_ALTER_FILE_ERROR , "Alread a file read ! Please release first !"},
    { en_INIT_READ ,            en_ALTER_FILE_ERROR , "Error occured Initialization for READ : %d"},
    { en_CHK_SUM ,              en_ALTER_FILE_ERROR , "ChecksummError in HEADER of XBI-File"},
    { en_HEAP_NOT_INI ,         en_ALTER_FILE_ERROR , "HeapLib not initialized !"},
    { en_HEAP_LEN ,             en_ALTER_FILE_ERROR , "Data len in heap zero, HeapLib initialized ?"},
    { en_STRANGE_ERROR ,        en_ALTER_FILE_ERROR , "Strange Error :-)) Number %d !"},
    { en_ONLY_SGOLDLITE ,       en_ALTER_FILE_ERROR , "Currently only SGOLDLite-Projects supported !"},
    { en_NO_SW ,                en_ALTER_FILE_ERROR , "No Update-SW found !"},
    { en_READ_XBI ,             en_ALTER_FILE_ERROR , "Some Error : %d occured on reading XBI-Data"},
    { en_OUTDATED ,             en_ALTER_FILE_ERROR , "Your version of WINSWUP/LIBRARY is outdated ! Software-Update not possible ! Get a new version !"},
    { en_OPEN_FILE ,            en_ALTER_FILE_ERROR , "Can't open file %s"},
    { en_XBI_LEN ,              en_ALTER_FILE_ERROR , "XBI-Length 0 !"},
    { en_NO_SIEMENS ,           en_ALTER_MOBILE , "Not a Siemens-Mobile-Phones-File"},
    { en_FILE_SIZE ,            en_ALTER_FILE_ERROR , "Error occured during FileSize-Detection : %d"},
    { en_CANT_ALLOC ,           en_ALTER_FILE_ALLOC_ERROR , "Could not allocate %lu Bytes for XBI-File"},

                                    // heaphand.c / filehand.c
    { en_CANT_ADD ,             en_ALTER_FILE_ERROR  , "Can't add element for erase info!"},
    { en_CANT_COPY ,            en_ALTER_FILE_ERROR  , "Could not copy element to list!"},
    { en_CANT_MALLOC ,          en_ALTER_FILE_ERROR  , "Can't malloc heap for add. map info!"},
    { en_MORE_INFO ,            en_ALTER_FILE_ERROR  , "More map info in xbi header than expected!"},
    { en_LOCATER_ENTRY ,        en_ALTER_FILE_ALLOC_ERROR , "Error mallocing heap for locater entry!"},
    { en_SPLIT_INSERT ,         en_ALTER_FILE_ALLOC_ERROR , "SplitElementInsert returns error!"},
    { en_HEAP_CORRUPT ,         en_ALTER_FILE_ERROR , "Heap data corrupt at location %d"},
    { en_MEM_ALLOC ,            en_ALTER_FILE_ERROR , "Heapchk: no memory allocated!"},
    { en_HEAP_INCON ,           en_ALTER_FILE_ERROR , "Heapchk: detected inconsistency!"},
    { en_FSEEK ,                en_ALTER_FILE_ERROR , "Error on data access"},
    { en_FREAD ,                en_ALTER_FILE_ERROR , "Read error in file %s!"},
    { en_DESTROYED ,            en_ALTER_FILE_ERROR , "Data file destroyed at %lu"},
    { en_STAT_FILE ,            en_ALTER_FILE_ERROR , "Error on file access"},
    { en_READ_KENNUNG ,         en_ALTER_FILE_ERROR , "ReadKennung returned: %d"},
    { en_COUNT_BYTES ,          en_ALTER_FILE_ERROR , "Error: CountXbiHeaderBytes returnes %d"},
    { en_NO_READ_ACCESS ,       en_ALTER_FILE_ERROR , "No read access to file %s"},
    { en_FIND_FILE ,            en_ALTER_FILE_ERROR , "Can't find file %s"},
    { en_DATA_ACCESS ,          en_ALTER_FILE_ERROR , "Error on data access"},
    { en_NO_32BIT_FILE,         en_ALTER_FILE_ERROR , "Error file: Error on reading XBI-header"},
    { en_OLD_STRINGIDENTIFICATION,  en_ALTER_FILE_ERROR , "Error old 24-Bit file: Please select a 32-Bit file for SGOLD"},

                                    // swup_eg.c
    { en_OPEN_COMPORT ,         en_ALTER_CONNECT , "Opening Comport %d with Speed %d Baud not possible"},
    { en_REC_BLOCK1 ,           en_ALTER_TRANSMISSION , "Nothing received after BOT-Block1"},
    { en_WRONG_BLOCK1 ,         en_ALTER_TRANSMISSION , "Wrong Char %02X received after BOT-Block1"},
    { en_REC_BLOCK2 ,           en_ALTER_TRANSMISSION , "Nothing received after BOT-Block2, perhaps device protected"},
    { en_WRONG_BLOCK2 ,         en_ALTER_TRANSMISSION , "Wrong Char %02X received after BOT-Block2"},
    { en_REC_BLOCK3 ,           en_ALTER_TRANSMISSION , "Nothing received after BOT-Block3"},
    { en_WRONG_BLOCK3 ,         en_ALTER_TRANSMISSION , "Wrong Char %02X received after BOT-Block3"},
    { en_REC_BLOCK4 ,           en_ALTER_TRANSMISSION , "Nothing received after BOT-Block4"},
    { en_WRONG_BLOCK4 ,         en_ALTER_TRANSMISSION , "Wrong Char %02X received after BOT-Block4"},
    { en_REC_BAUD_BLOCK ,       en_ALTER_TRANSMISSION , "Nothing received after Baud-BOT-Block"},
    { en_WRONG_BAUD_BLOCK ,     en_ALTER_TRANSMISSION , "Wrong Char %02X received after Baud-BOT-Block"},
    { en_CHANGE_SPEED ,         en_ALTER_TRANSMISSION , "Changing Speed on Comport %d to %d Baud not possible, possible errors: wrong Baudrate / not installed driver/ wrong serialcard ?"},
    { en_REC_PING ,             en_ALTER_TRANSMISSION , "Nothing received after Baud-Ping"},
    { en_WRONG_PING ,           en_ALTER_TRANSMISSION , "Wrong char %02X received after Baud-Ping"},
    { en_REC_FALLBACK ,         en_ALTER_TRANSMISSION , "Nothing received after fallback to 57kBaud"},
    { en_WRONG_FALLBACK ,       en_ALTER_TRANSMISSION , "Wrong char %02X after fallback to 57kBaud"},
    { en_REC_SYNC_BYTE ,        en_ALTER_TRANSMISSION , "Nothing received after synch-byte"},
    { en_WRONG_SYNC_BYTE ,      en_ALTER_TRANSMISSION , "Wrong char %02X after synch-byte"},
    { en_REC_BLOCK5K ,          en_ALTER_TRANSMISSION , "Nothing received after BOT-Block 5k"},
    { en_WRONG_BLOCK5K ,        en_ALTER_TRANSMISSION , "Wrong char %02X after BOT-Block 5k"},

    { en_ALTER_CONNECT ,        0 , "Cant connect mobile !\nCheck if attached correctly or switch baudrate or comport"},
    { en_ALTER_TRANSMISSION ,   0 , "Cant connect mobile !\nCheck if attached correctly"},
    { en_ALTER_SW_VERSION ,     0 , "Update not possible !\nWrong SW-version"},
    { en_ALTER_MOBILE ,         0 , "Update not possible !\nWrong mobile"},
    { en_ALTER_SW ,             0 , "Update not possible !\nSW defect"},
    { en_ALTER_MOBILE_DEFECT ,  0 , "Mobile defect"},
    { en_ALTER_FILE_ERROR,      0 , "Error on reading new Mobile-SW" },
    { en_ALTER_FILE_ALLOC_ERROR, 0 , "Error on reading new Mobile-SW, not enough memory" },

    { en_BOOTCORE_MASK,         0 , "No Bootcore detected"},
    { en_BOOTCORE_BAUDRATE,     0 , "Bootcore does't support selected baudrate"},
    { en_BOOTCORE_NOT_ACKNOWLEDGE,     0 , "Device protected. Only secure update allowed"},

    { en_SIG_WRONGHASH ,        0 , "Mobile requested signature, but software doesn't support it"},
    { en_SIG_NOSIGNATURE,       0 , "Mobile requested signature, but signature data are not available"},
    { en_SIG_NOT_FREEZED,       0 , "Secured update not possible, device not prepared."},
    { en_SIG_SIGNREJECT,        0 , "Software signature was rejected"},
    { en_SIG_GENERAL,           0 , "Software signature negotiation failure (%02X)"},
    { en_SIG_SW_REJECTED,       0 , "Software update denied by mobile"},
    { en_SIG_SW_CORRUPT,        0 , "Update aborted, corrupt software was reported by mobile"},

								//map update - scout 
    { en_MAP_CANNOT_ALLOC,      0 , "MAP Init: Could not able to allocate the Memory"},
    { en_MAP_READ_ERR,          0 , "MAP Init: Could not able to read the Map Info from Heap"},
    { en_MAP_INIT_ERR,          0 , "MAP Init Error: Mapping Block is Missing"},
    { en_MAP_BFC_ERR,           0 , "MAP Init: BFC Error - BFC Initialisation is failed"},
    { en_MAP_BFC_COMM_ERR,      0 , "MAP Init: BFC Error - Opening the COM port is failed"},
    { en_MAP_SERVICE_ERR,       0 , "MAP Init: Could not switch the Mobile in to service Mode"},
    { en_MAP_INVALID_HW,        0 , "MAP Init: The Connected Mobile's ID is not valid for this mapping Update. Please contact Siemens Mobile Phones\n"},
    { en_MAP_UPDATE_ERR,        0 , "MAP Init: Could not able to send the Mapping information to the Mobile..\n"},
    { en_MAP_VER_ERR,           0 , "MAP Init: Could not able to write the Mapping version to the Mobile..\n"},
								
								//default
    { en_OVERFLOW ,             0 , "Overflow on error list"}
};



size_t ErrorDescriptionSize = sizeof (ErrorDescription);
size_t t_enumErrorDescriptionSize = sizeof (t_enumErrorDescription);
