*------------------------------------------------------------------------------
* PROPACK Unpack Source Code - Sony PSX, Method 2
*
* Copyright (c) 1991-95 Rob Northen Computing, U.K. All Rights Reserved.
*
* Conversion from 68000 by Chris Kirby, Iguana Entertainment Limited.
*
* File: RNC_2.ASM
*
* Date: 16.03.95
*------------------------------------------------------------------------------
* Slightly modified by Adrian Francis - 8.7.99
*
* The source needed changing because asmpsx did not like it!
*------------------------------------------------------------------------------

HEADER_LEN      EQU     18
CRC_POLY        EQU     $A001

INPUT           EQUR    r3	;v1
INPUT_HI        EQUR    r4	;a0
OUTPUT          EQUR    r5	;a1
OUTPUT_HI       EQUR    r6	;a2

LEN             EQUR    r8	;t0
POS             EQUR    r9	;t1
BITBUF          EQUR    r10	;t2
XSP             EQUR    r11	;t3
TEMP            EQUR    r12	;t4
XD0             EQUR    r13	;t5
XA0             EQUR    r14	;t6
EXT             EQUR    r15	;t7
XD1             EQUR    r16	;s0
XA1             EQUR    r17	;s1
TEMP2           EQUR    r18	;s2
POSTOP          EQUR    r19	;s3

		section .text

		global RNC_Unpack

RNC_Unpack

		addiu	sp,sp,-24	;Added 'C'interface	-ADRIAN-
		nop
		sw		ra,0(sp)
		sw		s0,4(sp)
		sw		s1,8(sp)
		sw		s2,12(sp)
		sw		s3,16(sp)

        ;ADDI  r4,r4,9			;Removed - What the hell was this??!!!		-ADRIAN-
        move  XA0,r4          ;source
        move  XA1,r5          ;dest
        LI    XD0,0
        LUI   XSP,(MYSTACK>>16)
        ORI   XSP,MYSTACK&$FFFF
        ADDIU XA0,XA0,4
        LBU   XD0,0(XA0)
        LBU   TEMP,1(XA0)
        LBU   TEMP2,2(XA0)
        LBU   EXT,3(XA0)
        SLL   XD0,XD0,24
        SLL   TEMP,TEMP,16
        SLL   TEMP2,TEMP2,8
        OR    XD0,XD0,TEMP
        OR    XD0,XD0,TEMP2
        OR    XD0,XD0,EXT

        ADDIU XA0,XA0,4

        SW    XD0,0(XSP)
        MOVE  INPUT,XA0
        ADDI  INPUT,INPUT,HEADER_LEN-8

        MOVE  OUTPUT,XA1
        MOVE  OUTPUT_HI,OUTPUT
        ADD   OUTPUT_HI,OUTPUT_HI,XD0

        LBU   XD0,0(XA0)
        LBU   TEMP,1(XA0)
        LBU   TEMP2,2(XA0)
        LBU   EXT,3(XA0)
        SLL   XD0,XD0,24
        SLL   TEMP,TEMP,16
        SLL   TEMP2,TEMP2,8
        OR    XD0,XD0,TEMP
        OR    XD0,XD0,TEMP2
        OR    XD0,XD0,EXT


        ADDU  XA0,XA0,4

        MOVE  INPUT_HI,INPUT
        ADD   INPUT_HI,INPUT_HI,XD0

        SUBI  XSP,XSP,2
        SH    r0,0(XSP)


UNPACK7
        LUI   BITBUF,$FFFF
        ORI   BITBUF,$FF00

        LI    EXT,1

        LBU   BITBUF,0(INPUT)
        ADDI  INPUT,INPUT,1
        ADDU  BITBUF,BITBUF,BITBUF
        ADDU  BITBUF,BITBUF,EXT
        ADDU  BITBUF,BITBUF,BITBUF
        SRL   EXT,BITBUF,8

        J     XLOOP
        ANDI  EXT,EXT,1

FETCH0
        LBU   BITBUF,0(INPUT)
        ADDI  INPUT,INPUT,1
        ADDU  BITBUF,BITBUF,BITBUF
        ADDU  BITBUF,BITBUF,EXT
        SRL   EXT,BITBUF,8
        J     BACK0
        ANDI  EXT,EXT,1
FETCH1
        LBU   BITBUF,0(INPUT)
        ADDI  INPUT,INPUT,1
        ADDU  BITBUF,BITBUF,BITBUF
        ADDU  BITBUF,BITBUF,EXT
        SRL   EXT,BITBUF,8
        J     BACK1
        ANDI  EXT,EXT,1
FETCH2
        LBU   BITBUF,0(INPUT)
        ADDI  INPUT,INPUT,1
        ADDU  BITBUF,BITBUF,BITBUF
        ADDU  BITBUF,BITBUF,EXT
        SRL   EXT,BITBUF,8
        J     BACK2
        ANDI  EXT,EXT,1
FETCH3
        LBU   BITBUF,0(INPUT)
        ADDI  INPUT,INPUT,1
        ADDU  BITBUF,BITBUF,BITBUF
        ADDU  BITBUF,BITBUF,EXT
        SRL   EXT,BITBUF,8
        J     BACK3
        ANDI  EXT,EXT,1
FETCH4
        LBU   BITBUF,0(INPUT)
        ADDI  INPUT,INPUT,1
        ADDU  BITBUF,BITBUF,BITBUF
        ADDU  BITBUF,BITBUF,EXT
        SRL   EXT,BITBUF,8
        J     BACK4
        ANDI  EXT,EXT,1
FETCH5
        LBU   BITBUF,0(INPUT)
        ADDI  INPUT,INPUT,1
        ADDU  BITBUF,BITBUF,BITBUF
        ADDU  BITBUF,BITBUF,EXT
        SRL   EXT,BITBUF,8
        J     BACK5
        ANDI  EXT,EXT,1
FETCH6
        LBU   BITBUF,0(INPUT)
        ADDI  INPUT,INPUT,1
        ADDU  BITBUF,BITBUF,BITBUF
        ADDU  BITBUF,BITBUF,EXT
        SRL   EXT,BITBUF,8
        J     BACK6
        ANDI  EXT,EXT,1
FETCH7
        LBU   BITBUF,0(INPUT)
        ADDI  INPUT,INPUT,1
        ADDU  BITBUF,BITBUF,BITBUF
        ADDU  BITBUF,BITBUF,EXT
        SRL   EXT,BITBUF,8
        J     BACK7
        ANDI  EXT,EXT,1


RAW
        LI    LEN,3

X4BITS
        ADDU  BITBUF,BITBUF,BITBUF
        SRL   EXT,BITBUF,8
        ANDI  EXT,EXT,1
        ANDI  BITBUF,BITBUF,$FF
        BEQ   r0,BITBUF,FETCH0
        nop


BACK0
        ADDU  POS,POS,POS
        ADDU  POS,POS,EXT
        SRL   EXT,POS,16
        ANDI  EXT,EXT,1

        SUBI  LEN,LEN,1
        BGEZ  LEN,X4BITS
        nop
        ADDI  POS,POS,2

GETRAWREP2
        LBU   TEMP,0(INPUT)
        LBU   TEMP2,1(INPUT)
        SB    TEMP,0(OUTPUT)
        SB    TEMP2,1(OUTPUT)

        LBU   TEMP,2(INPUT)
        LBU   TEMP2,3(INPUT)
        SB    TEMP,2(OUTPUT)
        SB    TEMP2,3(OUTPUT)



        ADDIU INPUT,INPUT,4
        SUBI  POS,POS,1

        BGEZ  POS,GETRAWREP2
        ADDI  OUTPUT,OUTPUT,4

        J     XLOOP
        NOP

GETLEN
        ADDU  BITBUF,BITBUF,BITBUF
        SRL   EXT,BITBUF,8
        ANDI  EXT,EXT,1
        ANDI  BITBUF,BITBUF,$FF
        BEQ   r0,BITBUF,FETCH1
        NOP
BACK1
        ADDU  LEN,LEN,LEN
        ADDU  LEN,LEN,EXT

        ADDU  BITBUF,BITBUF,BITBUF

        SRL   EXT,BITBUF,8
        ANDI  EXT,EXT,1
        ANDI  BITBUF,BITBUF,$FF
        BEQ   r0,BITBUF,FETCH2
        NOP


BACK2
        BEQ   r0,EXT,COPY
        nop
        SUBI  LEN,LEN,1
        ADD   BITBUF,BITBUF,BITBUF
        SRL   EXT,BITBUF,8
        ANDI  EXT,EXT,1
        ANDI  BITBUF,BITBUF,$FF
        BEQ   r0,BITBUF,FETCH3
        NOP

BACK3
        ADDU  LEN,LEN,LEN
        ADDU  LEN,LEN,EXT
        SRL   EXT,LEN,16
        ANDI  EXT,EXT,1

        SUBI  TEMP,LEN,9
        BEQ   r0,TEMP,RAW
        NOP


COPY
        ADDU  BITBUF,BITBUF,BITBUF
        SRL   EXT,BITBUF,8
        ANDI  EXT,EXT,1
        ANDI  BITBUF,BITBUF,$FF
        BEQ   r0,BITBUF,FETCH4
        nop


BACK4
        BEQ   r0,EXT,BYTEDISP2
        nop
        ADDU  BITBUF,BITBUF,BITBUF
        SRL   EXT,BITBUF,8
        ANDI  EXT,EXT,1
        ANDI  BITBUF,BITBUF,$FF
        BEQ   r0,BITBUF,FETCH5
        nop

BACK5
        ADDU  POS,POS,POS
        ADDU  POS,POS,EXT

        ADDU  BITBUF,BITBUF,BITBUF
        SRL   EXT,BITBUF,8
        ANDI  EXT,EXT,1
        ANDI  BITBUF,BITBUF,$FF
        BEQ   r0,BITBUF,FETCH6
        nop

BACK6
        BNE   r0,EXT,BIGDISP
        NOP
        BNE   r0,POS,BYTEDISP
        nop
        ADDI  POS,POS,1

ANOTHER
        ADDU  BITBUF,BITBUF,BITBUF
        SRL   EXT,BITBUF,8
        ANDI  EXT,EXT,1
        ANDI  BITBUF,BITBUF,$FF
        BEQ   r0,BITBUF,FETCH7
        nop

BACK7
        ADDU  POS,POS,POS
        ADDU  POS,POS,EXT
        SRL   EXT,POS,16
        ANDI  EXT,EXT,1

BYTEDISP
        SLL   TEMP,POS,8
        ANDI  TEMP,TEMP,$FF00
        SRL   POS,POS,8
        OR    POS,POS,TEMP


BYTEDISP2
        ANDI  POSTOP,POS,$FF00

        LBU   POS,0(INPUT)

        ADDIU INPUT,INPUT,1
        OR    POS,POS,POSTOP
        MOVE  XA0,OUTPUT
        SUB   XA0,XA0,POS
        SUBI  XA0,XA0,1
        ANDI  EXT,LEN,1
        SRL   LEN,LEN,1
        BEQ   r0,EXT,BYTEDISP3
        nop

        LBU   TEMP,0(XA0)
        ADDI  XA0,XA0,1
        SB    TEMP,0(OUTPUT)
        ADDI  OUTPUT,OUTPUT,1


BYTEDISP3
        SUBI  LEN,LEN,1
        BNE   r0,POS,BYTEDISP5
        NOP

        ANDI  POSTOP,POS,$FF00
        LBU   POS,0(XA0)
        NOP
        OR    POS,POS,POSTOP
BYTEDISP4
        SB    POS,0(OUTPUT)
        SUBI  LEN,LEN,1
        SB    POS,1(OUTPUT)

        BGEZ  LEN,BYTEDISP4
        ADDI  OUTPUT,OUTPUT,2

        J     XLOOP
        NOP
BYTEDISP5
        LBU   TEMP2,1(XA0)
        LBU   TEMP,0(XA0)
        SB    TEMP2,1(OUTPUT)
        SB    TEMP,0(OUTPUT)

        ADDI  XA0,XA0,2

        SUBI  LEN,LEN,1
        BGEZ  LEN,BYTEDISP5
        ADDI  OUTPUT,OUTPUT,2

        J     XLOOP
        NOP


GETBITS
        LBU   BITBUF,0(INPUT)
        ADDI  INPUT,INPUT,1
        ADDU  BITBUF,BITBUF,BITBUF
        ADDU  BITBUF,BITBUF,EXT
        SRL   EXT,BITBUF,8
        ANDI  EXT,EXT,1
        BNE   r0,EXT,STRING
        NOP

XBYTE
        LBU   TEMP,0(INPUT)
        ADDI  INPUT,INPUT,1
        SB    TEMP,0(OUTPUT)
        ADDI  OUTPUT,OUTPUT,1


XLOOP
        ADDU  BITBUF,BITBUF,BITBUF
        SRL   EXT,BITBUF,8
        ANDI  EXT,EXT,1
        BNE   r0,EXT,CHKZ
        nop

        LBU   TEMP,0(INPUT)
        ADDI  INPUT,INPUT,1
        SB    TEMP,0(OUTPUT)
        ADDI  OUTPUT,OUTPUT,1

        ADDU  BITBUF,BITBUF,BITBUF
        SRL   EXT,BITBUF,8
        ANDI  EXT,EXT,1
        BEQ   r0,EXT,XBYTE
        nop
CHKZ
        ANDI  BITBUF,BITBUF,$FF
        BEQ   r0,BITBUF,GETBITS
        nop


STRING
        LI    LEN,2
        LI    POS,0

        ADDU  BITBUF,BITBUF,BITBUF
        SRL   EXT,BITBUF,8
        ANDI  EXT,EXT,1
        ANDI  BITBUF,BITBUF,$FF
        BEQ   r0,BITBUF,FETCH8
        nop


BACK8
        BEQ   r0,EXT,GETLEN
        nop

SMALLS
        ADDU  BITBUF,BITBUF,BITBUF
        SRL   EXT,BITBUF,8
        ANDI  EXT,EXT,1

        ANDI  BITBUF,BITBUF,$FF
        BEQ   r0,BITBUF,FETCH9
        nop

BACK9

        BEQ   r0,EXT,BYTEDISP2
        nop
        ADDI  LEN,LEN,1
        ADD   BITBUF,BITBUF,BITBUF
        SRL   EXT,BITBUF,8
        ANDI  EXT,EXT,1

        ANDI  BITBUF,BITBUF,$FF
        BEQ   r0,BITBUF,FETCH10
        nop

BACK10
        BEQ   r0,EXT,COPY
        nop

        LBU   LEN,0(INPUT)
        ADDI  INPUT,INPUT,1
        NOP
        BEQ   r0,LEN,OVERNOUT
        ADDI  LEN,LEN,8
        J     COPY
        NOP

BIGDISP
        ADDU  BITBUF,BITBUF,BITBUF
        SRL   EXT,BITBUF,8
        ANDI  EXT,EXT,1

        ANDI  BITBUF,BITBUF,$FF
        BEQ   r0,BITBUF,FETCH11
        nop

BACK11
        ADDU  POS,POS,POS
        ADDU  POS,POS,EXT
        SRL   EXT,POS,16
        ANDI  EXT,EXT,1
        ORI   POS,POS,4

        ADDU  BITBUF,BITBUF,BITBUF
        SRL   EXT,BITBUF,8
        ANDI  EXT,EXT,1

        ANDI  BITBUF,BITBUF,$FF
        BEQ   r0,BITBUF,FETCH12
        nop

BACK12
        BNE   r0,EXT,BYTEDISP
        NOP
        J     ANOTHER
        NOP

FETCH8
        LBU   BITBUF,0(INPUT)
        ADDI  INPUT,INPUT,1
        ADDU  BITBUF,BITBUF,BITBUF
        ADDU  BITBUF,BITBUF,EXT
        SRL   EXT,BITBUF,8
        J     BACK8
        ANDI  EXT,EXT,1
FETCH9
        LBU   BITBUF,0(INPUT)
        ADDI  INPUT,INPUT,1
        ADDU  BITBUF,BITBUF,BITBUF
        ADDU  BITBUF,BITBUF,EXT
        SRL   EXT,BITBUF,8
        J     BACK9
        ANDI  EXT,EXT,1
FETCH10
        LBU   BITBUF,0(INPUT)
        ADDI  INPUT,INPUT,1
        ADDU  BITBUF,BITBUF,BITBUF
        ADDU  BITBUF,BITBUF,EXT
        SRL   EXT,BITBUF,8
        J     BACK10
        ANDI  EXT,EXT,1
FETCH11
        LBU   BITBUF,0(INPUT)
        ADDI  INPUT,INPUT,1
        ADDU  BITBUF,BITBUF,BITBUF
        ADDU  BITBUF,BITBUF,EXT
        SRL   EXT,BITBUF,8
        J     BACK11
        ANDI  EXT,EXT,1
FETCH12
        LBU   BITBUF,0(INPUT)
        ADDI  INPUT,INPUT,1
        ADDU  BITBUF,BITBUF,BITBUF
        ADDU  BITBUF,BITBUF,EXT
        SRL   EXT,BITBUF,8
        J     BACK12
        ANDI  EXT,EXT,1

OVERNOUT
        ADDU  BITBUF,BITBUF,BITBUF
        SRL   EXT,BITBUF,8
        ANDI  EXT,EXT,1
        ANDI  BITBUF,BITBUF,$FF
        BNE   r0,BITBUF,CHECK4END
        nop

        LBU   BITBUF,0(INPUT)
        ADDI  INPUT,INPUT,1
        ADDU  BITBUF,BITBUF,BITBUF
        ADDU  BITBUF,BITBUF,EXT
        SRL   EXT,BITBUF,8
        ANDI  EXT,EXT,1

CHECK4END
        BNE   r0,EXT,XLOOP
        nop

        LHU   XD0,0(XSP)
        ADDI  XSP,XSP,2
        BEQ   r0,XD0,UNPACK9
        nop

UNPACK8
        LH    XD1,0(XSP)
        ADDI  XSP,XSP,2
        SB    XD1,0(OUTPUT)
        ADDI  OUTPUT,OUTPUT,1
        SUBI  XD0,XD0,1
        BNE   r0,XD0,UNPACK8
        nop

UNPACK9
        J     UNPACK11
        NOP
UNPACK10
        SW    XD1,0(XSP)

UNPACK11
		lw		s0,4(sp)	
		lw		s1,8(sp)
		lw		s2,12(sp)
		lw		s3,16(sp)
		lw		ra,0(sp)
		nop
		addiu	sp,sp,24

        J     ra
        nop

        CNOP  0,4

		section .data

        DW    0,0,0,0,0,0,0,0,0,0,0,0
MYSTACK DW    0

