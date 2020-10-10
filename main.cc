typedef unsigned long long uint64;

struct trap_frame{
	uint64 regs[32]; 		// 0 - 255 bytes
	uint64 fregs[32]; 	// 256 - 511 bytes
	uint64 satp; 				// 512 - 519 bytes	
	uint64* trap_stack; // 520 byte 
	uint64 hartid;			// 528 byte
};

void add_timer(int seconds) {
	volatile uint64* mtimecmp= reinterpret_cast<uint64*>(0x02004000);
	volatile uint64* mtime =  reinterpret_cast<uint64*>(0x0200bff8);

	*mtimecmp = *mtime + (seconds * 10000000);
}

extern "C" int kmain(){

	// disparar interrupcao de timer	
	add_timer(10);
	
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
		if (cause_num == 7){
			add_timer(20);
		}
	}

	timecmp = *mtimecmp;
}

