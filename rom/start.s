	.long	0xffffff	/* 00 stack-pointer */
	.long	entry		/* 01 reset vector */
        .long 	Unhandled	/* 02 access fault */
	.long   Unhandled	/* 03 address error */
	.long	Unhandled	/* 04 illegal instruction */
	.long 	Unhandled	/* 05 divide by zero */
	.long	Unhandled	/* 06 CHK, CHK2 instruction */
	.long	Unhandled	/* 07 TRAPV instruction */
	.long	Unhandled	/* 08 Privilege violation */
	.long	Unhandled 	/* 09 Trace */
	.long 	Unhandled	/* 10 Line 1010 emulator */
	.long 	Unhandled	/* 11 Line 1111 emulator */
	.long	Unhandled	/* 12 Uninitialized */
	.long	Unhandled	/* 13 coprocessor protocol violation */
	.long	Unhandled	/* 14 Format error */
	.long 	Unhandled	/* 15 Uninitialized */
	.long	Unhandled	/* 16 Unassigned */
	.long 	Unhandled	/* 17 Unassigned */
	.long 	Unhandled	/* 18 Unassigned */
	.long 	Unhandled	/* 19 Unassigned */
	.long 	Unhandled	/* 20 Unassigned */
	.long	Unhandled	/* 21 Unassigned */
	.long	Unhandled	/* 22 Unassigned */
	.long	Unhandled	/* 23 Unassigned */
	.long 	Unhandled	/* 24 Spurious */
	.long	KEY		/* 25 */
	.long   KEY		/* 26 Level 0 Autovector */
	.long	KEY	/* 27 External interrupt */
	.long	KEY	/* 28 Level 4 Autovector */
	.long   KEY	/* 29 Horizontal Blank */
	.long	KEY	/* 30 Level 6 Autovector */
	.long 	KEY	/* 31 Vertical Blank */
	.long	Unhandled	/* 32 TRAP */
	.long	Unhandled	/* 33 TRAP */
	.long 	Unhandled	/* 34 TRAP */
	.long	Unhandled	/* 35 TRAP */
	.long 	Unhandled	/* 36 TRAP */
	.long 	Unhandled	/* 37 TRAP */
	.long	Unhandled	/* 38 TRAP */
	.long 	Unhandled	/* 39 TRAP */
	.long	Unhandled	/* 40 TRAP */
	.long	Unhandled	/* 41 TRAP */
	.long 	Unhandled	/* 42 TRAP */
	.long 	Unhandled	/* 43 TRAP */
	.long	Unhandled	/* 44 TRAP */
	.long 	Unhandled	/* 45 TRAP */
	.long	Unhandled	/* 46 TRAP */
	.long 	Unhandled	/* 47 TRAP */
	.long 	Unhandled	/* 48 FP Branch or Set on Unordered Condition */
	.long	Unhandled	/* 49 FP Inexact Result */
	.long	Unhandled	/* 50 FP Divide by zero */
	.long	Unhandled	/* 51 FP Underflow */
	.long	Unhandled	/* 52 FP Operand error */
	.long	Unhandled	/* 53 FP Overflow */
	.long	Unhandled	/* 54 FP Signaling NAN */
	.long	Unhandled	/* 55 FP Unimplemented data type */
	.long	Unhandled	/* 56 MMU Configuration error */
	.long	Unhandled	/* 57 MMU Illegal Operation Error */
	.long	Unhandled	/* 58 MMU Access Level Violation error */
	.long	Unhandled	/* 59 Unassigned */
	.long 	Unhandled	/* 60 Unassigned */
	.long 	Unhandled	/* 61 Unassigned */
	.long	Unhandled	/* 62 Unassigned */
	.long	Unhandled 	/* 63 Unassigned */

.org 0x100
data_start:
	.dc.l 0x00000000  /* data start */
data_len:
	.dc.l 0x00000000  /* data len   */

entry:
	
	mov.l #0x410000, %d0
	mov.l %d0, %a0
	mov.l #msg, %d0
	mov.l %d0, %a1
msg_loop:
	mov.b (%a1)+, %d1
	cmp.b #0,     %d1
	beq out_msg_loop
	mov.b %d1,  (%a0)
	jmp msg_loop
out_msg_loop:

/* copy over data segement to 0x800000 */	

	mov.l data_start, %d0
	mov.l %d0, %a0
	mov.l (data_len), %d0
	mov.l #0x800000, %d2
	mov.l %d2, %a2
copy_data:

 	cmp.l #0, %d0
	beq copy_data_out
	sub.l #1, %d0

	mov.l (%a0)+, %d1
	mov.l %d1, (%a2)+

	jmp copy_data;
copy_data_out:

	move	#0, %sr 

	jsr main 

halt:	jmp halt

Unhandled: 
	rte

KEY:
	mov.l #0x410000, %d0
	mov.l %d0, %a0
	mov.b #'D', (%a0)
	rte

CLK:
	mov.l #0x410000, %d0
	mov.l %d0, %a0
	mov.b #'E', (%a0)

	rte

.align 4
msg:
	.ascii "booting...\n"
	.dc.b 0


