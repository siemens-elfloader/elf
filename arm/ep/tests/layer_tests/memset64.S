



    .arm
    .global memset64
    @ void memset64(void *dst, void *src, size_t size);
    @ WARNING
    @  size must be divisible by 8

memset64:
    add     r2, r0, r2
    mov     r3, r1

_loop:
    stmdb   r2!, {r1, r3}
    cmp     r0, r2
    bls     _loop
    bx      lr

