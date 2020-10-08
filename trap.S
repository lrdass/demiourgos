.altmacro
.set NUM_GP_REGS, 32  # Number of registers per context
.set NUM_FP_REGS, 32
.set REG_SIZE, 8   # Register size (in bytes)
.set MAX_CPUS, 8   # Maximum number of CPUs

# Use macros for saving and restoring multiple registers
.macro save_gp i, basereg=t6
	sd	x\i, ((\i)*REG_SIZE)(\basereg)
.endm
.macro load_gp i, basereg=t6
	ld	x\i, ((\i)*REG_SIZE)(\basereg)
.endm
.macro save_fp i, basereg=t6
	fsd	f\i, ((NUM_GP_REGS+(\i))*REG_SIZE)(\basereg)
.endm
.macro load_fp i, basereg=t6
	fld	f\i, ((NUM_GP_REGS+(\i))*REG_SIZE)(\basereg)
.endm


.option norvc
m_trap_vector:
	// salva o registrador de scratch
	csrrw t6, mscratch, t6 # faz swap entre mscratch e t6 atomico
	
	// loopa e salva os registradores
	// salva o contexto 
	.set i, 1
	.rept 30
		save_gp %i
		.set i, i+1
	.endr

	mv t5, t6
	csrr t6, mscratch
	save_gp 31, t5

	csrw mrscratch, t5


	# preparando para voltar para c++
	// se prepara pra chamar m_trap e passar os parametros
	csrr a0, mepc
	csrr a1, mtval
	csrr a2, mcause
	csrr a3, mhartid
	csrr a4, mstatus
	mv a5, t5
	ld sp, 520(a5)
	call m_trap

	# retornamos da trap

	// comecamos a retornar o contexto de execucao
	csrw mepc, a0

	csrr t6, mscratch

	// loop e restaura o contexto
	.set i,1
	.rept 31
		load_gp %i
		.set i, i+1
	.endr

	mret

