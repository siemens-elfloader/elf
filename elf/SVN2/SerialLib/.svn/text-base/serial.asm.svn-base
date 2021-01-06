  RSEG CODE:CODE:NOROOT(2)

;-----------------------------------------------------------------------
  PUBLIC SetSpeed
  SetSpeed:
; void set_speed(r0=n)
; 0=57600,  1=115200, 2=230400, 3=460800,
; 4=614400, 5=921600, 6=1228800, 7=1600000
; uses r0, r1, r2

        adr r1, iSpeeds
        ldr r1, [r1, r0,LSL#2]

        mov r2, #0xf1000000  ;USART0_CLC
        mov r0, r1, LSR#16
        str r0, [r2, #0x14]  ;USART0_BG
        mov r0, r1, LSL#16
        mov r0, r0, LSR#16
        str r0, [r2, #0x18]  ;USART0_FDV

        bx lr

iSpeeds dcd 0x001901d8 ;57600/0x1d8=122.033898*0x1a=3172.881348
        dcd 0x000c01d8 ;115200/0x1d8=244.067797*13=3172.881361
        dcd 0x000501b4 ;230400/0x1b4=528.440367*0x6=3170.642202
        dcd 0x00000092 ;460800/0x92=3156.164384
        dcd 0x000000c3 ;614400/0xc3=3150.769231
        dcd 0x00000127 ;921600/0x127=3124.067797
        dcd 0x0000018a ;1228800/0x18a=3118.781726
        dcd 0x00000000 ;1600000/0x200=3125
        dcd 0x000001d0 ;1500000/0x1d0=3232.758621
        
;-----------------------------------------------------------------------
  PUBLIC Tx_byte
Tx_byte:

; void tx_byte(r0=byte)
; uses r0, r1, r2

        mov r2, #0xf1000000 ;USART0_CLC
        ldr r1, [r2, #0x20] ;USART0_TXB
        bic r1, r1, #0xff
        orr r1, r0, r1
        str r1, [r2, #0x20] ;USART0_TXB
tx_w
        ldr r1, [r2, #0x68] ;USART0_FCSTAT
        ands r1, r1, #0x02
        beq tx_w

        ldr r1, [r2, #0x70] ;USART0_ICR
        orr r1, r1, #2
        str r1, [r2, #0x70]

        ;b serve_watchdog
        bx lr
        
;-----------------------------------------------------------
  PUBLIC Rx_byte
Rx_byte:

; byte rx_byte()
; uses r0, r1, r2

rx_loop
        mov r1, #0xf1000000
        ldr r0, [r1, #0x68] ;USART0_FCSTAT
        ands r0, r0, #0x04
        beq rx_loop

rx_c
        ldr r0, [r1, #0x70] ;USART0_ICR
        orr r0, r0, #4
        str r0, [r1, #0x70]

        ldr r0, [r1, #0x24] ;USART0_RXB
        and r0, r0, #0xff
        bx lr
          
          
  END