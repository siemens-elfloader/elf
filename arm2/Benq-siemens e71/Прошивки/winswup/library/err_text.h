/*                       Munich,  Germany
                     COMPANY CONFIDENTIAL
                     All Rights Reserved

.AUTHOR         U. Schmitt, ICM MP PO8 MCH53

.PROJECT        WINSWUP

.SHORT_DESCR    Interface to the lowlayer-DLL

.SW_COMPONENT

.SW_TYPE

.VERSION        0.7             please increase the two defines !!!

.DATE           2002-09-02

.EXIT_CODES

.STATUS         FIRST_TRY

.CHANGE_CONTROL

Version |  Date    | Changed by | Reason for Change
--------+----------+------------+----------------------------------------------
 0.1    |26.07.2001| Schmittu   | file created
--------+----------+------------+----------------------------------------------
 0.2    |2001-08-21| JKue       | made it compileable ... ( one komma was missing and one comma was a dot )
--------+----------+------------+----------------------------------------------
 0.3    |2001-08-31| J.Garrido  | new error string added for BGJ.
--------+----------+------------+----------------------------------------------
 0.4    |2001-08-28| Schmittu   | new: en_CANT_CONNECT
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
	    |          |            |      en_ALTER_FILE_ALLOC_ERROR,
		|          |            | deleted: en_NO_SPECIAL_ERROR
--------+----------+------------+----------------------------------------------
 0.5    |2001-12-17| Schmittu   | new : en_WAIT_SW_VERSION
--------+----------+------------+----------------------------------------------
 0.6    |2002-04-25| L.Sillge   | new : en_BOOTCORE_MASK, en_BOOTCORE_BAUDRATE
		|          |            |       en_SIG_WRONGHASH, en_SIG_NOSIGNATURE, 
		|          |            |       en_SIG_SIGNREJECT,en_SIG_GENERAL
--------+----------+------------+----------------------------------------------
 0.7    |2002-09-03| D.Dittmer  | Content of ErrorDescription moved to err_text.c.
 		|          |            | Here remain the external declarations enabling multiple import.
--------+----------+------------+----------------------------------------------

.STILL_TODO
*/

/* INDENT: -nbr -nce -ei -ip -lp -pro -sc -c:33 -cci:3 -cd:33 -ci:3 -cli:3 -cp:0 -d:0 -di:0 -i:3 -l:78 -lc:78 -tabs:3  -tabu */



/*********************************************************************************************************/



typedef struct
{
    unsigned int ui_enError;
    unsigned int ui_enAltError;     // if 0 : not relevant
    char * pszDescription;
} t_enumErrorDescription;



extern t_enumErrorDescription ErrorDescription[];
extern size_t ErrorDescriptionSize;
extern size_t t_enumErrorDescriptionSize;
