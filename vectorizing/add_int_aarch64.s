    .text
    .global add_int
    .type   add_int, %function
add_int:
    cbz     w2, .Ldone         // if n == 0, return immediately

// x0 = pa, x1 = pb, w2 = n, w3 = x
.Lloop:
    ldr     w4, [x1], #4       // w4 = *pb++; advance pb by 4 bytes
    add     w4, w4, w3         // w4 += x
    str     w4, [x0], #4       // *pa++ = w4; advance pa by 4 bytes
    subs    w2, w2, #1         // n--
    bne     .Lloop             // if (n != 0) repeat

.Ldone:
    ret                        // return

    .size   add_int, .-add_int
