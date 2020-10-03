.section .init, "ax"            # esse código deve ir para .init e seja alocavel e executavel
.global _start                  # faz o simbolo _start disponivel para o linker. sem ele o ld nao encontraria o simbolo _start que passamos no ENTRY(_start)
_start:                         
    .cfi_startproc              # startproc - endproc sao diretivas que sinalizam o comeco e o fim de uma funçao
    .cfi_undefined ra           # diz ao assembler que o registrador ra nao deve ser restaurado pro valor contido em ra antes da execucao de _start
    .option push                
    .option norelax
    la gp, __global_pointer$    # carrega o global_pointer
    .option pop
    la sp, __stack_top          # load_address carrega o valor de __stack_top para o stack_pointer
    add s0, sp, zero            # "copia" o valor de sp pra s0. s0 fica salvo mesmo depois de chamadas de funcao
    jal zero, main              # jump and link, salva a proxima instrucao no registrador rd e seta o pc para o offset do valor passado
    .cfi_endproc
    .end                        # fim
