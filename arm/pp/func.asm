/*
* Ping-Pong 2009 - 2010
* keys
* (c) Danil_e71
*/
      RSEG CODE:CODE
      PUBLIC kill_data
      CODE32
kill_data
      BX R1

        PUBLIC	ELF_BEGIN
	RSEG	ELFBEGIN:DATA
ELF_BEGIN


defadr	MACRO	a,b
	PUBLIC	a
a	EQU	b
	ENDM

	END
	
