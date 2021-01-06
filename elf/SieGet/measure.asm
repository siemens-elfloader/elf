  RSEG CODE:CODE:NOROOT(2)
  PUBLIC TimeFunc
TimeFunc:
  ;r0 - адрес вызываемой ф-ции
  ;r1 - параметр этой ф-ции
  ;r2 - адрес STM
  stmfd sp!, {r4-r6, lr}
  mov r3, r0
  mov r0, r1
  mov r6, r2
  ldr r4, [r6, #0x10]
  blx r3
  ldr r5, [r6, #0x10]
  sub r0, r5, r4
  ldmfd sp!, {r4-r6, pc}
    
  END