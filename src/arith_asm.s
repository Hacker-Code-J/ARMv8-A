
.text

.macro	ADD_SHIFT_macro	r0, r1, r2
	add \r0, \r1, \r2
	lsl	\r0, \r0, #1
.endm

// int32_t add_asm(int32_t dataA, int32_t dataB);
.type	add_asm, %function
.global	add_asm
add_asm:
	add		w0,	w0, w0
	
	ret

	.size add_asm, (. - add_asm)
	

// int64_t add_shift_asm(int32_t dataA, int32_t dataB);
.type	add_shift_asm, %function
.global	add_shift_asm
add_shift_asm:
	ADD_SHIFT_macro x0, x0, x1
	
	ret

	.size add_shift_asm, (. - add_asm)

// uint32_t bn_add_asm(uint64_t *ret, uint64_t *opA, uint64_t *opB, int32_t len)
// x0: ptr of ret, x1: ptr of opA, x2: ptr of opB, w3: len
// x4: ret
// x5: opA
// x6: opB
// x7: counter
.type    bn_add_asm, %function
.global  bn_add_asm
bn_add_asm:
	mov		w7, wzr	

	ldr		x5, [x1, x7, lsl #3]
	ldr		x6, [x2, x7, lsl #3]
	adds 	x4, x5, x6
	str     x4, [x0, x7, lsl #3]
	add 	w7, w7, #1
	
LOOP:
	ldr		x5, [x1, x7, lsl #3]
	ldr		x6, [x2, x7, lsl #3]
	adcs 	x4, x5, x6
	str     x4, [x0, x7, lsl #3]
	add 	w7, w7, #1
	cmp		w3, w7
	bgt		LOOP

END_LOOP:
	adc  	w0, wzr, wzr

	ret
	.size bn_add_asm, (. - bn_add_asm)
