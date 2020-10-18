typedef unsigned long long uint64;
typedef char uint8;

#include "uart.h"
#include "mem.h"

const bool DISABLE_AFTER_FIRST_INTERRUPT = false;

static void print(char* string) {
	UART uart(0x10000000);
	uart.write(string);
}

struct trap_frame{
	uint64 regs[32]; 		// 0 - 255 bytes
	uint64 fregs[32]; 		// 256 - 511 bytes
	uint64 satp; 			// 512 - 519 bytes	
	uint64* trap_stack;		// 520 byte 
	uint64 hartid;			// 528 byte
};


void disable_interrupts() {
	asm("addi sp, sp, -8");
	asm("sd t0, 0(sp)");

	asm("csrr t0, mie");
	asm("andi t0, t0, 0xffffffffffffff7f");
	asm("csrw mie, t0");

	asm("ld t0, 0(sp)");
	asm("addi sp, sp, 8");
}

void add_timer(int seconds) {
	volatile uint64* mtimecmp= reinterpret_cast<uint64*>(0x02004000);
	volatile uint64* mtime =  reinterpret_cast<uint64*>(0x0200bff8);

	*mtimecmp = *mtime + (seconds * 10000000);
}

extern "C" int kmain()
{

	// Memory::init();
	// Memory::alloc(3);	
	
	return 0;
}

extern "C" void m_trap(uint64 epc, uint64 tval,uint64 cause,uint64 hart, uint64 status, trap_frame* trap_frame)
{
	// o bit mais significante da causa diz se é uma interrupcao sincrona ou assincrona
	bool async = false;
	if ((cause >> 63 & 1) == 1){
		async = true;
	} else {
		async = false;
	}

	// os 4 bits menos significantes dizem qual foi o tipo de interrupcao
	unsigned int cause_num = cause & 0xf;
	volatile uint64* mtimecmp= reinterpret_cast<uint64*>(0x02004000);
	volatile uint64* mtime =  reinterpret_cast<uint64*>(0x0200bff8);
	uint64 time = *mtime;
	uint64 timecmp = *mtimecmp;

	if(async) {
		// o tipo 7 é uma interrupcao de timer
		if (cause_num == 7) {
			if (DISABLE_AFTER_FIRST_INTERRUPT) {
				disable_interrupts();
			} else {
				add_timer(2);
			}
		}
	}

	timecmp = *mtimecmp;
}

