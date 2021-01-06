/*                       Munich,  Germany
                     COMPANY CONFIDENTIAL
                     All Rights Reserved

.AUTHOR         U. Schmitt, ICM MP PO8 MCH53

.PROJECT        WINSWUP

.SHORT_DESCR    Interface to the lowlayer-DLL

.SW_COMPONENT

.SW_TYPE

.VERSION        1.7

.DATE           2005-04-09

.EXIT_CODES

.STATUS         FIRST_TRY

.CHANGE_CONTROL

Version |  Date  | Changed by | Reason for Change
--------+--------+------------+----------------------------------------------
 0.1    |26.07.01| Schmittu   | file created
--------+----------+------------+----------------------------------------------
 0.2    |31.08.01  | J.Garrido  | en_UNABLE_WRITE_BGJ added
--------+----------+------------+----------------------------------------------
 0.3    |2001-08-31| Schmittu   | new: en_CANT_CONNECT
        |          |            |      en_ERASE_AREA_NOT_OK
        |          |            |      en_MALLOC_REQUEST_FLASH_BLOCKS
        |          |            |      en_INCOMPATIBLE_VERSION
        |          |            |      en_MUTEX
        |          |            |      en_COMPRESS_NOT_SUPPORTED
        |          |            |      en_FLASHBLOCK_SIZE_DEFAULT
        |          |            |      en_INVALID_HANDLE_VALUE
        |          |            |      en_MOBILE_SW_TRANS
        |          |            |      en_TIMEOUT_REQUEST_FLASH_BLOCKS
        |          |            |      en_WAIT_ACK_EOT
        |          |            |      en_DATA_ACCESS
        |          |            |      en_ALTER_CONNECT
        |          |            |      en_ALTER_TRANSMISSION
        |          |            |      en_ALTER_SW_VERSION
        |          |            |      en_ALTER_MOBILE
        |          |            |      en_ALTER_SW
        |          |            |      en_ALTER_MOBILE_DEFECT
        |          |            |      en_ALTER_FILE_ERROR
        |          |            |      en_ALTER_FILE_ALLOC_ERROR
        |          |            | deleted: en_NO_SPECIAL_ERROR
--------+----------+------------+----------------------------------------------
 0.4    |2001-12-17| Schmittu   | en_WAIT_SW_VERSION added
--------+----------+------------+----------------------------------------------
 0.5    |2002-04-25| L.Sillge   | new : en_BOOTCORE_MASK, en_BOOTCORE_BAUDRATE
        |          |            |       en_SIG_WRONGHASH, en_SIG_NOSIGNATURE,
        |          |            |       en_SIG_SIGNREJECT,en_SIG_GENERAL
--------+----------+------------+----------------------------------------------
 0.6    |2002-10-28| L.Sillge   | new : en_SIG_DATA_CORRUPT,en_SW_REJECTED,
--------+----------+------------+----------------------------------------------
 0.7    |2003-09-16| H.G.Weyers | new:  en_BOOTCORE_NOT_ACKNOWLEDGE
--------+----------+------------+----------------------------------------------
 0.8    |2003-09-26| H.G.Weyers | new:  en_ERR_ADDITIONAL_MAP_INFO
--------+----------+------------+----------------------------------------------
 0.9    |2003-10-27| H.G.Weyers | new:  wmobile errors
        |          |            |       en_PROJECT_NOT_SET
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
        |          |            |       en_UNABLE_TO_WRITE_STATISTIC
        |2003-11-10| H.G.Weyers | new:  en_NO_32BIT_FILE
        |          |            |       en_OLD_STRINGIDENTIFICATION
--------+----------+------------+----------------------------------------------
 1.0    |2004-01-30| J.Garrido  | Substitute BFB with BFC
        |          |            | Remove EGOLD reference only SGOLDLITE
--------+----------+------------+----------------------------------------------
 1.1    |2004-03-08| J.Garrido  | New 	en_SIG_NOT_FREEZED
--------+----------+------------+----------------------------------------------
 1.2    |2004-03-23| J.Garrido  | New
        |          |            |       en_BC_INTERFACE_NOT_OK
        |          |            |       en_DEVCON_NOT_OK
        |          |            |       en_CHARGER_PRESENT
        |          |            |       en_BC_HW_INTERFACE_NOT_SUPPORTED
        |          |            |       en_BC_BAUDRATE_NOT_SUPPORTED
        |          |            |       en_MEM_ERROR
--------+----------+------------+----------------------------------------------
 1.3    |2004-12-09| M.Untucht  | New
        |          |            |       en_BFC_POWER_SUPPLY_LESS
--------+----------+------------+----------------------------------------------
 1.4    |2005-03-14| J.Garrido  | New
        |          |            |       en_CMDSEC_ERROR
--------+----------+------------+----------------------------------------------
 1.5    |2005-03-21|L&T Infotech| New   related to Mapping update
        |          |            |       en_MAP_CANNOT_ALLOC
        |          |            |       en_MAP_READ_ERR,
        |          |            |       en_MAP_INIT_ERR,
        |          |            |       en_MAP_BFC_ERR,
        |          |            |       en_MAP_BFC_COMM_ERR,
        |          |            |       en_MAP_SERVICE_ERR,
        |          |            |       en_MAP_INVALID_HW,
        |          |            |       en_MAP_UPDATE_ERR,
        |          |            |       en_MAP_VER_ERR,
--------+----------+------------+----------------------------------------------
 1.6    |2005-03-23| J.Garrido  | New
        |          |            |       en_BFC_UNKNOWN_ANSWER
--------+----------+------------+----------------------------------------------
 1.7    |2005-04-09|P.Mackenthun| New
        |          |            |           en_WAIT_SYSTEM_DATA_UPDATE_ACK,
        |          |            |           en_ERR_SYSTEM_DATA_UPDATE,
--------+----------+------------+----------------------------------------------
 1.8    |2005-09-07| R.Szul     | New
        |          |            |       en_CANT_OPEN_USB
--------+----------+------------+----------------------------------------------
 1.9    |2005-10-05| K.Gontarz  | New
        |          |            |       en_NO_ERROR = 0x000
--------+----------+------------+----------------------------------------------
 2.0    |2005-03-20| K.Gontarz  | New
        |          |            |       en_CANT_FIND_USB
--------+----------+------------+----------------------------------------------
  
.STILL_TODO
*/

/* INDENT: -nbr -nce -ei -ip -lp -pro -sc -c:33 -cci:3 -cd:33 -ci:3 -cli:3 -cp:0 -d:0 -di:0 -i:3 -l:78 -lc:78 -tabs:3  -tabu */

/**
 * Enumerations of errors for information of Main-programm
 */

typedef enum
{
    en_NO_ERROR             = 0x000,

    en_ALREADY_OPEN         = 0x100,                // wseril1.c
    en_CREATE_FILE,
    en_SET_COMMSTATE,
    en_NOT_OPEN,
    en_TIMEOUT,
    en_GET_BAUD,
    en_BAUDRATE,
    en_WRITE_FILE,
    en_READ_FILE,
    en_INVALID_HANDLE_VALUE,

    en_NO_VERSION           = 0x200,                // wseril2.c
    en_DEFAULT_CMD_BLOCKS,
    en_WAIT_ON_CMD_BLOCK,
    en_MAX_BIN_LEN_REACHED,
    en_UNKNOWN_BYTE,
    en_REC_TIMEOUT,
    en_UNKNOWN_CHAR,
    en_UNKNOWN_REC_VALUE,
    en_COMM_ERROR,
    en_CHECK_SUM_ERROR,
    en_CMD_REC,
    en_SERIAL_ERROR,
    en_READ_CMD,
    en_WAIT_FF,

    en_NO_READY_FLASH_ERASE = 0x300,                // wseril3.c
    en_SEND_FLASH_ERASE,
    en_ERASE_AREA_NOT_OK,
    en_MALLOC_REQUEST_FLASH_BLOCKS,
    en_FLASHBLOCK_SIZE_DEFAULT,
    en_TIMEOUT_REQUEST_FLASH_BLOCKS,
    en_SIG_WRONGHASH,
    en_SIG_NOSIGNATURE,
    en_SIG_SIGNREJECT,
    en_SIG_GENERAL,
    en_SIG_SW_CORRUPT,
    en_SIG_SW_REJECTED,
	en_SIG_NOT_FREEZED,


    en_RAM_FF               = 0x400,                // wmob_err.c
    en_RAM_PATTERN,
    en_RAM_00,
    en_RAM_UNKNOWN,
    en_VOLTAGE_RANGE,
    en_CMD_SEQUENCE,
    en_ERASE_NOT_POSSIBLE,
    en_NO_BLOCK,
    en_BYTE_PROG,
    en_FINAL_CHECK,
    en_UNKNOWN_FLASH,
    en_NOT_SUPPORTED,
    en_PROJECT_NOT_SET,
    en_PROJECT_NOT_SUPPORTED,
    en_ADDMAPINFO_WRONG_SIZE,
    en_ADDMAPINFO_BUFFER_OVERWRITE,
    en_ADDMAPINFO_LEN_NOT_SET,
    en_LENCHECK_ILLEGAL_COMMAND,
    en_LENCHECK_BUFFER_OVERRUN,
    en_LENCHECK_CHECKSUM_INVALID,
    en_LENCHECK_ADDRESS_CHECKSUM_INVALID,
    en_LENCHECK_INVALID_STATE,
    en_LENCHECK,
    en_WRONG_BLOCK_OR_ADDRESS,
    en_UNABLE_TO_WRITE_STATISTIC,
    en_UNKNOWN_ERROR,

    en_BFC_NO_CALLBACK      = 0x500,                // wbfbtool.c
    en_BFC_COMM_NOT_OPEN,
    en_BFC_MOBILE_NO_SWITCHON,
    en_BFC_MOBILE_NO_PING,
    en_THIS_FILE_NO_NEW_UPDATE,
    en_BFC_NO_NEW_UPDATE,
    en_BFC_READY_FALSE,
    en_CUSTOMER_REBOOT,
    en_PUT_COUNT,

	en_BC_INTERFACE_NOT_OK,
    en_DEVCON_NOT_OK,
    en_CHARGER_PRESENT,
    en_BC_HW_INTERFACE_NOT_SUPPORTED,
    en_BC_BAUDRATE_NOT_SUPPORTED,
    en_MEM_ERROR,
	en_CMDSEC_ERROR,
    en_BFC_POWER_SUPPLY_LESS,                       //power supply check
	en_BFC_UNKNOWN_ANSWER,

    en_NO_DATE_TIME         = 0x600,                // swupwork.c
    en_WRONG_DATE_TIME,
    en_NO_REQUEST,
    en_ERR_SEND_UPDATE,
    en_CANT_OPEN,
    en_ERR_WAIT_FLASH_CODE,
    en_UNKNOWN_FLASH_CODE,
    en_WAIT_FLASH_SIZE,
    en_WRONG_FLASH_SIZE,
    en_NO_SPECIAL_ERROR,
    en_NO_UPDATE,
    en_INCOMPATIBLE,
    en_INCOMPATIBLE_VERS,
    en_WAIT_SPLIT_ID_ANSWER,
    en_WRONG_SPLIT_ID,
    en_MALLOC_ERROR,
    en_ENABLE_FLASHBLOCK,
    en_WAIT_COMPRESS_ANSWER,
    en_WAIT_LANGINFO_ANSWER,
    en_WAIT_CALC_SPLIT_INFO_ANSWER,
    en_WAIT_STAT_DATA,
    en_SW_PROJECT,
    en_CANT_CONNECT,
    en_INCOMPATIBLE_VERSION,
    en_MUTEX,
    en_COMPRESS_NOT_SUPPORTED,
    en_MOBILE_SW_TRANS,
    en_WAIT_ACK_EOT,
    en_UNABLE_WRITE_BGJ,
    en_WAIT_SW_VERSION,
    en_BOOTCORE_MASK,
    en_BOOTCORE_BAUDRATE,
    en_ERR_ADDITIONAL_MAP_INFO,
    en_WAIT_SYSTEM_DATA_UPDATE_ACK,
    en_ERR_SYSTEM_DATA_UPDATE,
    en_CANT_FIND_USB,
    en_CANT_OPEN_USB,

    en_SCAN_PROJECTS        = 0x700,                // dyna_dll.c
    en_DLL_OUT_OF_DATE,
    en_LOAD_FAILED,

    en_LIB_EXE_DIFF         = 0x800,                // hehawrap.c / fihawrap.c
    en_FILE_READ,
    en_INIT_READ,
    en_CHK_SUM,
    en_HEAP_NOT_INI,
    en_HEAP_LEN,
    en_STRANGE_ERROR,
    en_ONLY_SGOLDLITE,
    en_NO_SW,
    en_READ_XBI,
    en_OUTDATED,
    en_OPEN_FILE,
    en_XBI_LEN,
    en_NO_SIEMENS,
    en_FILE_SIZE,
    en_CANT_ALLOC,

    en_CANT_ADD             = 0x900,                // heaphand.c / filehand.c
    en_CANT_COPY,
    en_CANT_MALLOC,
    en_MORE_INFO,
    en_LOCATER_ENTRY,
    en_SPLIT_INSERT,
    en_HEAP_CORRUPT,
    en_MEM_ALLOC,
    en_HEAP_INCON,
    en_FSEEK,
    en_FREAD,
    en_DESTROYED,
    en_STAT_FILE,
    en_READ_KENNUNG,
    en_COUNT_BYTES,
    en_NO_READ_ACCESS,
    en_FIND_FILE,
    en_DATA_ACCESS,
    en_NO_32BIT_FILE,
    en_OLD_STRINGIDENTIFICATION,

    en_OPEN_COMPORT         = 0xA00,                // swup_eg.c
    en_REC_BLOCK1,
    en_WRONG_BLOCK1,
    en_REC_BLOCK2,
    en_WRONG_BLOCK2,
    en_REC_BLOCK3,
    en_WRONG_BLOCK3,
    en_REC_BLOCK4,
    en_WRONG_BLOCK4,
    en_REC_BAUD_BLOCK,
    en_WRONG_BAUD_BLOCK,
    en_CHANGE_SPEED,
    en_REC_PING,
    en_WRONG_PING,
    en_REC_FALLBACK,
    en_WRONG_FALLBACK,
    en_REC_SYNC_BYTE,
    en_WRONG_SYNC_BYTE,
    en_REC_BLOCK5K,
    en_WRONG_BLOCK5K,

    en_BOOTCORE_NOT_ACKNOWLEDGE = 0xB00,            // swup_sg.c


    en_MAP_CANNOT_ALLOC = 0xC00,					//map update-scout
    en_MAP_READ_ERR,
    en_MAP_INIT_ERR,
    en_MAP_BFC_ERR,
    en_MAP_BFC_COMM_ERR,
    en_MAP_SERVICE_ERR,
    en_MAP_INVALID_HW,
    en_MAP_UPDATE_ERR,
    en_MAP_VER_ERR,

    en_ALTER_CONNECT        = 0XF00,                // for alternative texts
    en_ALTER_TRANSMISSION,
    en_ALTER_SW_VERSION,
    en_ALTER_MOBILE,
    en_ALTER_SW,
    en_ALTER_MOBILE_DEFECT,
    en_ALTER_FILE_ERROR,
    en_ALTER_FILE_ALLOC_ERROR,


    en_OVERFLOW             = 0xFFF

} t_en_Error;



