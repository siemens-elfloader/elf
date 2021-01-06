


    .arm
    .global bcopy64

bcopy64:

    add     r1, r2
    add     r2, r0, r2

_loop:

    ldmfd   r1, {r3, r11}
    stmfd   r2!, {r3, r11}
    sub     r1, #8
    cmp     r0, r2
    bls     _loop
    bx      lr
