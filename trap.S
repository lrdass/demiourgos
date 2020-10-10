
.section .text
.global m_trap_vector
# This must be aligned by 4 since the last two bits
# of the mtvec register do not contribute to the address
# of this vector.
.align 4
m_trap_vector:
	# Save registers
	addi sp, sp, -128    # Make some space in the stack
	sd ra, 0(sp)         # Return address
	sd a0, 8(sp)         # Function argument / return value
	sd a1, 16(sp)        # Function argument / return value
	sd a2, 24(sp)        # Function argument
	sd a3, 32(sp)        # Function argument
	sd a4, 40(sp)        # Function argument
	sd a5, 48(sp)        # Function argument
	sd a6, 56(sp)        # Function argument
	sd a7, 64(sp)        # Function argument
	sd t0, 72(sp)        # Temporary / alternate return address
	sd t1, 80(sp)        # Temporary
	sd t2, 88(sp)        # Temporary
	sd t3, 96(sp)        # Temporary
	sd t4, 104(sp)       # Temporary
	sd t5, 112(sp)       # Temporary
	sd t6, 120(sp)       # Temporary

	# Set arguments and call m_trap
	csrr	a0, mepc     # Machine exception pc
	csrr	a1, mtval    # Machine bad address or instruction
	csrr	a2, mcause   # Machine trap cause
	csrr	a3, mhartid  # Machine hart id
	csrr	a4, mstatus  # Machine status
	csrr	a5, mscratch # Scratch resgister for machine trap handlers
	call	m_trap

	# Restore registers
	ld ra, 0(sp)         # Return address
	ld a0, 8(sp)         # Function argument / return value
	ld a1, 16(sp)        # Function argument / return value
	ld a2, 24(sp)        # Function argument
	ld a3, 32(sp)        # Function argument
	ld a4, 40(sp)        # Function argument
	ld a5, 48(sp)        # Function argument
	ld a6, 56(sp)        # Function argument
	ld a7, 64(sp)        # Function argument
	ld t0, 72(sp)        # Temporary / alternate return address
	ld t1, 80(sp)        # Temporary
	ld t2, 88(sp)        # Temporary
	ld t3, 96(sp)        # Temporary
	ld t4, 104(sp)       # Temporary
	ld t5, 112(sp)       # Temporary
	ld t6, 120(sp)       # Temporary

	addi sp, sp, 128
	# m_trap will return the return address via a0.

	# csrw	mepc, a0
	# Now load the trap frame back into t6
	# csrr	t6, mscratch
	mret

