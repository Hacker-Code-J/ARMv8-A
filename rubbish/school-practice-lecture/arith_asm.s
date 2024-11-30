
.text

.macro ADD_SHIFT_macro r0, r1, r2
    add \r0, \r1, \r2
    lsl \r0, \r0, #1
.endm

// int32_t add_asm(int32_t data1, int32_t data2);
.type       add_asm, %function
.global     add_asm
add_asm:
    add     w0, w0, w1

    ret

    .size add_asm, (. - add_asm)

// int64_t add_shift_asm(int32_t data1, int32_t data2);
.type       add_shift_asm, %function
.global     add_shift_asm
add_shift_asm:
    ADD_SHIFT_macro x0, x0, x1

    ret

    .size add_shift_asm, (. - add_shift_asm)

