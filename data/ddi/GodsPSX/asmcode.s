
	section	.rdata  
	section	.text   
	section	.data   
	section	.sdata  
	
	section	.sbss	; The bss sections
	section	.bss

	section	.text

	global	Asm_MulFIX
	global	Asm_DivFIX
	global	Asm_ResetPsx
	global	Asm_GetMemAvailable
	global	Asm_GetMemStart
	global	Asm_Rts
	global	Asm_SortPrim
	global	Asm_Random
	global	Asm_SetSeed
	global	Asm_GetSeed

	global	ScreenOn, ScreenOff, SetScreen

;	global	VectorNormal12

	global	AddPrim

;added by Steve D.

	global	HMD_Copy4


HMD_Copy4:
	lw	v0,(a1)
	add	a1,a1,4
	sw	v0,(a0)
	add	a2,a2,-4
	bne	a2,zero,HMD_Copy4
	add	a0,a0,4
	jr	ra
	nop


ScreenOn:
	j	SetScreen
	move	a0,zero
ScreenOff:
	j	SetScreen
	add	a0,zero,1
SetScreen:
	lui	a2,$0300
	lui	a1,$1f80
	add	a1,a1,$1814
	add	a0,a0,a2
	jr	ra
	sw	a0,(a1)

;VectorNormal12:
;	lw	t0,0(a0)
;	lw	t1,4(a0)
;	lw	t2,8(a0)
;	jal	Normal12
;	move	a3,ra
;	sw	t0,0(a0)
;	sw	t1,4(a0)
;	jr	a3
;	sw	t2,8(a0)
;
;Normal12:
;	mtc2	t0,C2_IR1
;	mtc2	t1,C2_IR2
;	mtc2	t2,C2_IR3
;	nop
;	SQR	1
;	mfc2	t3,C2_MAC1
;	mfc2	t4,C2_MAC1
;	mfc2	t5,C2_MAC1
;	add	t3,t3,t4
;	add	v0,t3,t5
;	mtc2	v0,C2_LZCS
;	nop
;	nop
;	mfc2	v1,C2_LZCR
;	add	a1,zero,-2
;	add	v1,v1,a1
;	add	t6,zero,31
;	sub	t6,t6,v1
;	sra	t6,t6,1
;	add	t3,v1,-24
;	bltz	t3,@skp
;	nop
;	beq	zero,zero,@ok
;	sllv	t4,v0,t3
;@skp	addiu	t3,zero,24
;	sub	t3,t3,v1
;	srav	t4,v0,t3
;@ok	add	t4,t4,-64
;	sll	t4,t4,1
;	lu

Asm_MulFIX:
	mult	a0,a1
	mflo	v0
	mfhi	v1
	nop
	nop
	srl	v0,v0,12		; lose unwanted data
	sll	v1,v1,20
	jr	ra
	or	v0,v0,v1


Asm_DivFIX:
	bne	a1,zero,@ok
	move	t0,zero
	jr	ra
	move	v0,zero
@ok	bgez	a0,@ok1
	li	v1,13
	li	t0,-1
	sub	a0,zero,a0
@ok1	move	t1,zero
	bgez	a1,@loop
	move	v0,zero
	li	t1,-1
	sub	a1,zero,a1
	beq	a1,zero,@out
	nop

@loop	divu	a0,a1
	mflo	t2			;Get result of divide
	mfhi	a0			;Get remainder
	sll	v0,v0,1
	sll	a0,a0,1
	add	v1,v1,-1
	bne	v1,zero,@loop
	add	v0,v0,t2

@out	beq	t0,zero,@posa0
	nop
	sub	v0,zero,v0
@posa0	beq	t1,zero,@posa1
	nop
	sub	v0,zero,v0
@posa1	jr	ra
	nop

Asm_ResetPsx:
	lui	a0,$bfc0
	jr	a0
	nop
	
Asm_GetMemAvailable:
	la	v0,sectend(.bss)
	sll	v0,v0,3
	srl	v0,v0,3

	sub	a0,a0,8
	subu	a0,a0,a1
	move	v1,zero
	lui	v1,$8000
	or	a1,a0,v1
	la	v1,RamEnd
	sw	a1,0(v1)
	jr	ra
	subu	v0,a0,v0	;return available ram

	opt	at+

Asm_GetMemStart:
	lw	a1,RamEnd
	la	v0,sectend(.bss)
	addu	a2,a0,v0
	bleu	a2,a1,Asm_Rts
	nop
	move	v0,zero
Asm_Rts	jr	ra
	nop

Asm_SortPrim:
	lw	a3,4(a1)	; get OT
	sll	a2,a2,2	; offset
	add	a3,a3,a2	; Order Table Address
	la	v0,AddPrim
	move	a1,a0	; Prim
	jr	v0
	move	a0,a3

Asm_Random:
	la	a0,Asm_Seed
	lw	v1,(a0)
	li	v0,$41c64e6d
	mult	v0,v1
	mflo	v0
	li	v1,12345
	nop
	addu	v0,v0,v1
	sw	v0,(a0)
	and	v1,v0,$8000
	srl	v0,v0,16
	srl	v1,v1,15
	jr	ra
	addu	v0,v0,v1

Asm_SetSeed:
	la	v1,Asm_Seed
	lw	v0,(v1)
	jr	ra
	sw	a0,(v1)

Asm_GetSeed:
	la	v1,Asm_Seed
	jr	ra
	lw	v0,(v1)





	section	.data

Asm_Seed	dw	$deadface


	section	.bss
RamEnd	dsw	1

	section	.text
