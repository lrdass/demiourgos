
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

	
	# Save registers (https://github.com/michaeljclark/riscv-probe/blob/master/env/common/crtm.s)
	addi sp, sp, -136
	sd ra, 0(sp)
	sd a0, 8(sp)
	sd a1, 16(sp)
	sd a2, 24(sp)
	sd a3, 32(sp)
	sd a4, 40(sp)
	sd a5, 48(sp)
	sd a6, 56(sp)
	sd a7, 64(sp)
	sd t0, 72(sp)
	sd t1, 80(sp)
	sd t2, 88(sp)
	sd t3, 96(sp)
	sd t4, 104(sp)
	sd t5, 112(sp)
	sd t6, 120(sp)

	csrr	t5, mscratch
	sd t5, 128(sp)

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

	# Restore registers
	ld ra, 0(sp)
	ld a0, 8(sp)
	ld a1, 16(sp)
	ld a2, 24(sp)
	ld a3, 32(sp)
	ld a4, 40(sp)
	ld a5, 48(sp)
	ld a6, 56(sp)
	ld a7, 64(sp)
	ld t0, 72(sp)
	ld t1, 80(sp)
	ld t2, 88(sp)
	ld t3, 96(sp)
	ld t4, 104(sp)
	ld t5, 112(sp)
	ld t6, 120(sp)

	ld t6, 128(sp)

	addi sp, sp, 136
	# m_trap will return the return address via a0.

	csrw	mepc, a0
	# Now load the trap frame back into t6
	csrr	t6, mscratch
	mret

