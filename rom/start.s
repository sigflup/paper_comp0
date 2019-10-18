
        dc.l 0xffffff, entry
	.ascii "If you are reading this email pantsbutt@gmail.com           "
        dc.l INT,INT,INT,INT,INT,INT,INT,INT
        dc.l INT,INT,INT,INT,INT,INT,INT,INT
        dc.l INT,INT,INT,INT,INT,INT,INT,INT
        dc.l INT,INT,INT,INT,INT,INT,INT,INT
        dc.l INT,INT,INT,INT,INT,INT,INT,INT
        dc.l INT,INT,INT,INT,INT,INT,INT

.org 0x100
data_start:
	.dc.l 0x00000000  /* data start */
data_len:
	.dc.l 0x00000000  /* data len   */
.align 4
msg:
	.ascii "booting...\n"
	.dc.b 0

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

	jsr main 

halt:	jmp halt


.align 4
INT:
	rte
