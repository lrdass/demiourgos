
.section .text
.global m_trap_vector
# This must be aligned by 4 since the last two bits
# of the mtvec register do not contribute to the address
# of this vector.
.align 4
m_trap_vector:
	# All registers are volatile here, we need to save them
	# before we do anything.
	# csrrw	t6, mscratch, t6
	# csrrw will atomically swap t6 into mscratch and the old
	# value of mscratch into t6. This is nice because we just
	# switched values and didn't destroy anything -- all atomically!
	# in cpu.rs we have a structure of:
	#  32 gp regs		0
	#  32 fp regs		256
	# We use t6 as the temporary register because it is the very
	# bottom register (x31)

	
	# TODO - Precisa salvar tudo isso? Ver guia pratico pagina 111 (136 do pdf)
	sd x5 , 0(sp)   
	sd x6 , 8(sp)   
	sd x7 , 16(sp)   
	sd x8 , 24(sp)   
	sd x9 , 32(sp)   
	sd x10 , 40(sp)   
	sd x11 , 48(sp)   
	sd x12 , 56(sp)   
	sd x13 , 64(sp)   
	sd x14, 72(sp)   
	sd x15, 80(sp)   
	sd x16, 88(sp)   
	sd x17, 96(sp)   
	sd x18, 104(sp)   
	sd x19, 112(sp)   
	sd x20, 120(sp)   
	sd x21, 128(sp)   
	sd x22, 136(sp)   
	sd x23, 144(sp)   
	sd x24, 152(sp)   
	sd x25, 160(sp)   
	sd x26, 168(sp)   
	sd x27, 176(sp)   
	sd x28, 184(sp)   
	sd x29, 192(sp)   
	sd x30, 200(sp)   
	sd x31, 208(sp)   

	csrr	t5, mscratch
	sd t5, 216(sp)

	# Save the actual t6 register, which we swapped into
	# mscratch

	# messed with us here.
	# csrw	mie, zero

	csrr	a0, mepc
	csrr	a1, mtval
	csrr	a2, mcause
	csrr	a3, mhartid
	csrr	a4, mstatus
	csrr	a5, mscratch
	call	m_trap

	#voltamos da trap, desempilhamos o contexto
	
	# TODO - Nao deveria ser o mesmo offset usado para empilhar?
	# i.e. ld x5, 0(sp) ; ld x6, 8(sp) ; ...
	ld x5 , 208(sp)   
	ld x6, 200(sp)   
	ld x7, 192(sp)   
	ld x8, 184(sp)   
	ld x9, 176(sp)   
	ld x10, 168(sp)   
	ld x11, 160(sp)   
	ld x12, 152(sp)   
	ld x13, 144(sp)   
	ld x14, 136(sp)   
	ld x15, 128(sp)   
	ld x16, 120(sp)   
	ld x17, 112(sp)   
	ld x18, 104(sp)   
	ld x19, 96(sp)   
	ld x20, 88(sp)   
	ld x21, 80(sp)   
	ld x22, 72(sp)   
	ld x23, 64(sp)   
	ld x24, 56(sp)   
	ld x25, 48(sp)   
	ld x26, 40(sp)   
	ld x27, 32(sp)   
	ld x28, 24(sp)   
	ld x29, 16(sp)   
	ld x30, 8(sp)   
	ld x31, 0(sp)   

	ld t6, 216(sp)

	# m_trap will return the return address via a0.

	csrw	mepc, a0
	# Now load the trap frame back into t6
	csrr	t6, mscratch
	mret

