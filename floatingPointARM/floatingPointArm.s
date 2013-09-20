	.file	"stub.c"
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"Input 1 = %x \n\000"
	.align	2
.LC1:
	.ascii	"Operator = %c \n\000"
	.align	2
.LC2:
	.ascii	"Input 2 = %x \n\000"
	.text
	.align	2
	.global	process
	.type	process, %function
process:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	sub	fp, ip, #4
	and	r4, r1, #255
	mov	r1, r0
	ldr	r0, .L2
	mov	r5, r2
	mov r7, r1 	
	bl	printf
	mov	r1, r4
	ldr	r0, .L2+4
	mov r8, r1
	bl	printf
	mov	r1, r5
	mov r9, r1
	ldr	r0, .L2+8
	bl	printf

### INSERT YOUR CODE HERE
	### r7 contains the first operand
	### r8 contains the sign (+, -, *)
	### r9 contains the second operand
    mov r5,#1
	mov r5,r5,lsl #23
	
	cmp r7,#0
	beq .zero
	b .zeroend
	
	.zero:
	cmp r9,#0
	moveq r0,#0
	beq .exit
	b .zeroend
	
	.zeroend:
	
	mov r1,r7,lsl #9
    mov r1,r1,lsr #9
	add r1,r5,r1
    ###r1 contains mantisa of first	

	mov r2,r9,lsl #9
    mov r2,r2,lsr #9
	add r2,r5,r2
	###r2 contains mantisa of second
	
	mov r3,r7,lsl #1
    mov r3,r3,lsr #24
	###r3 contains the first exponent
	
	mov r4,r9,lsl #1
    mov r4,r4,lsr #24
	###r4 contains the second exponent
	
	mov r10,r7,lsr #31
	mov r11,r9,lsr #31
	
	###operator calling starts
	cmp r8,#43
	beq .adb
	cmp r8,#42
	beq .ml
	cmp r8,#45
	beq .sbb
	###operator calling ends
	b .exit
	
	.mb1:
	cmp r11,#0
	moveq r6,r11
	cmp r11,#1
	moveq r6,r11
	mov r6,r6,lsl #31
	add r0,r3,r6
	b .exit
	
	.mb2:
	cmp r11,#0
	moveq r6,#1
	cmp r11,#1
	moveq r6,#0
	mov r6,r6,lsl #31
	add r0,r3,r6
	b .exit
	
	.ml:
	cmp r7,#0
	moveq r0,#0
	beq .exit
	
	cmp r9,#0
	moveq r0,#0
	beq .exit
	
	mov r1,r1,lsr #8
	mov r2,r2,lsr #8
	mul r5,r1,r2
	mov r6,r5,lsr #31
	mov r0,r6
	cmp r6,#1
	moveq r5,r5,lsl #1
	moveq r5,r5,lsr #9
	addeq r3,r3,#1
	cmp r6,#0
	moveq r5,r5,lsl #2
	moveq r5,r5,lsr #9
	mov r6,#127
	sub r3,r3,r6
	add r3,r3,r4
	mov r3,r3,lsl #23
	add r3,r3,r5
	cmp r10,#0
	beq .mb1
	cmp r10,#1
	beq .mb2
	b .exit
	
	.sbbr:
	cmp r11,#0
	beq .ad
	cmp r11,#1
	moveq r5,r1
	moveq r1,r2
	moveq r2,r5
	moveq r5,r3
	moveq r3,r4
	moveq r4,r5
	beq .sb
    b .exit
	
	.sbbb:
	cmp r11,#0
	beq .sb
	cmp r11,#1
	beq .ad
	b .exit
	
	.sbb:
	cmp r10,#0
	beq .sbbb
	cmp r10,#1
	beq .sbbr
	b .exit
	
	.adbb:
	cmp r11,#0
	beq .ad
    cmp r11,#1
	moveq r9,r9,lsl #1
	moveq r9,r9,lsr #1
	beq .sb
	b .exit
	
	.adbr:
	cmp r11,#0
	moveq r7,r7,lsl #1
	moveq r7,r7,lsr #1
	moveq r5,r1
	moveq r1,r2
	moveq r2,r5
	moveq r5,r3
	moveq r3,r4
	moveq r4,r5
	beq .sb
    cmp r11,#1
	beq .ad
	b .exit
	
	.adb:
	cmp r10,#0
	beq .adbb
	cmp r10,#1
	beq .adbr
	b .exit
	
	
	.expequal:
	add r0,r1,r2
	mov r6,r0,lsr #24
	cmp r6,#1
	moveq r0,r0,lsr #1
	addeq r3,r3,r6
	mov r0,r0,lsl #9
	mov r0,r0,lsr #9
	mov r10,r3,lsl #23
	add r0,r0,r10
	mov r6,r7,lsr #31
	mov r6,r6,lsl #31
	add r0,r0,r6
	b .exit
	
	.greater:
	@mov r0,r5
	mov r2,r2,lsr r5
	mov r4,r3
	b .expequal
	b .exit
	
	.lesser:
	mov r0,#3
	sub r5,r4,r3
	mov r1,r1,lsr r5
	mov r3,r4
	b .expequal
	b .exit
	
	.ad:
	subs r5,r3,r4
	beq .expequal
	cmp r5,#0
	bgt .greater
	blt .lesser
	b .exit
	
	@.expequalsub1:
   	@add pc,lr,#4
	@b .exit
	
	
	.expequalsub:
	cmp r2,r1
	movgt r5,r1
	movgt r1,r2
	movgt r2,r5
	movgt r6,#1
	movlt r6,#0
	
	sub r0,r1,r2
	cmp r0,#0
	beq .exit
	
    mov r11,#0
	mov r10,r0,lsr #23
	mov r5,r0
	b .loop
	.loop:
	cmp r10,#1
	beq .exit2
	add r11,r11,#1
	mov r5,r0,lsl r11
	mov r10,r5,lsr #23
	b .loop
	
	.exit2:
	mov r0,r5
	mov r0,r0,lsl #9
	mov r0,r0,lsr #9
	sub r3,r3,r11
	mov r10,r3,lsl #23
	add r0,r0,r10
	mov r0,r0,lsl #1
	mov r0,r0,lsr #1
	mov r6,r6,lsl #31
	add r0,r0,r6
	b .exit
	
	.greatersub:
	sub r5,r3,r4
	mov r2,r2,lsr r5
	mov r4,r3
	b .expequalsub
	b .exit
	
	.lessersub:
	sub r5,r4,r3
	mov r1,r1,lsr r5
	mov r3,r4
	b .expequalsub
	b .exit
	
	.sb:
	subs r5,r3,r4
	beq .expequalsub
	cmp r5,#0
	bgt .greatersub
	sub r5,r4,r3
	cmp r5,#0
	bgt .lessersub
	b .exit
	
	
	.exit:
	### Put the final output in r0
### YOUR CODE ENDS HERE

	ldmfd	sp, {r4, r5, fp, sp, pc}
.L3:
	.align	2
.L2:
	.word	.LC0
	.word	.LC1
	.word	.LC2
	.size	process, .-process
	.section	.rodata
	.align	2
	.type	filename.0, %object
	.size	filename.0, 9
filename.0:
	.ascii	"input.txt\000"
	.global	__extendsfdf2
	.section	.rodata.str1.4
	.align	2
.LC3:
	.ascii	"r\000"
	.align	2
.LC4:
	.ascii	"%f %c %f\000"
	.align	2
.LC6:
	.ascii	"Result = %f (float) , %x (hex)\n\000"
	.align	2
.LC5:
	.ascii	"File Not Found \000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 140
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	ip, sp
	stmfd	sp!, {r4, r5, fp, ip, lr, pc}
	sub	fp, ip, #4
	sub	sp, sp, #144
	ldr	r0, .L12
	ldr	r1, .L12+4
	bl	fopen
	subs	r5, r0, #0
	subne	r4, fp, #152
	bne	.L6
	b	.L11
.L8:
	sub	ip, fp, #160
	str	ip, [sp, #0]
	bl	sscanf
.L6:
	mov	r1, #128
	mov	r2, r5
	mov	r0, r4
	bl	fgets
	cmp	r0, #0
	ldr	r1, .L12+8
	sub	r2, fp, #156
	sub	r3, fp, #21
	mov	r0, r4
	bne	.L8
	mov	r0, r5
	bl	fclose
.L9:
	ldr	r2, [fp, #-160]
	ldrb	r1, [fp, #-21]	@ zero_extendqisi2
	ldr	r0, [fp, #-156]
	bl	process
	mov	r4, r0
	bl	__extendsfdf2
	mov	r3, r4
	mov	r2, r1
	mov	r1, r0
	ldr	r0, .L12+12
	bl	printf
	sub	sp, fp, #20
	ldmfd	sp, {r4, r5, fp, sp, pc}
.L11:
	ldr	r0, .L12+16
	bl	puts
	b	.L9
.L13:
	.align	2
.L12:
	.word	filename.0
	.word	.LC3
	.word	.LC4
	.word	.LC6
	.word	.LC5
	.size	main, .-main
	.ident	"GCC: (GNU) 3.4.3"
