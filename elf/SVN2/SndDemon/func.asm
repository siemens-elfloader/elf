	PUBLIC	ELF_BEGIN
	RSEG	ELFBEGIN:DATA
ELF_BEGIN

	RSEG	CODE:CODE
	PUBLIC	kill_data
	CODE32
kill_data
	BX	R1
        PUBLIC  seqkill
seqkill
        BX      R3



;
defadr	MACRO	a,b
	PUBLIC	a
a	EQU	b
	ENDM

//        defadr  MediaPlayer_GetPlayStatus,0xA06A1F2C //elka
/*
#ifdef EL71v45
       defadr  MediaPlayer_GetPlayStatus,0xA06A1F2C  //EL71v45
#endif       

#ifdef S75v47
       defadr  MediaPlayer_GetPlayStatus,0xA052D0F9  //s75v47
#endif       
*/
         defadr  Mp3, 0xA06F5841
         defadr  Mp32, 0xA06F5839
         defadr RegisterInNetwork, 0xA09C3F47
;        defadr  GBS_WaitForMsg,0xA00925C4
;        defadr  RegisterCepidForSocketWork,0xA09915E5
;        defadr  RequestLMANConnect,0xA09926F5

	END
	