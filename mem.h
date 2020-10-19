#ifndef MEM_H
#define MEM_H
#include "uart.h"
typedef unsigned long long uint64_t;

// saber onde está o proximo endereco para alocar
static unsigned int ALLOC_START = 0;
// para alinhar as paginas, tem que ser alinhado a 2^12
// ou seja, 3 paginas = 3 ^12 e será multiplo de 4096 
static const unsigned short PAGE_ORDER = 12;
// cada pagina é do tamanho da leitura da MMU 
static unsigned short PAGE_SIZE = 4096;

extern "C" unsigned int HEAP_SIZE ;
extern "C" unsigned int TEXT_END;
extern "C" unsigned int DATA_START;
extern "C" unsigned int DATA_END;
extern "C" unsigned int RODATA_START;
extern "C" unsigned int RODATA_END;
extern "C" unsigned int BSS_START;
extern "C" unsigned int BSS_END;
extern "C" unsigned int KERNEL_STACK_START;
extern "C" unsigned int KERNEL_STACK_END;
extern "C" uint64_t HEAP_START;
extern "C" unsigned int HEAP_SIZE;

namespace Memory{

enum EntryStatus {
	VALID,
	INVALID
};

class Entry{
public:
	uint64_t entry;

	bool is_valid(){return (this->get_entry() & EntryStatus::VALID )!=0;}
	bool is_invalid(){return !this->is_valid();}
	bool is_leaf(){return (this->get_entry() & 0xe) != 0; }
	bool is_branch(){return !this->is_leaf();}
	void set_entry(uint64_t entry){this->entry = entry;}
	uint64_t get_entry(){return this->entry;}
};

struct Table{
	Entry entries[512];
	unsigned short size = 512;
};



enum PageInfo {
    EMPTY = 0,
    TAKEN = 1 << 0,
    LAST = 1 << 1
};

class Page{
public:
    char flags;

    void clear();
    bool is_free();
    bool is_taken();
};

struct FreePages{
    struct FreePages* next;
};

void init();
char* alloc (unsigned int pages);
void dealloc (unsigned int pages);
char* zalloc (unsigned int pages);

uint64_t align_val(unsigned int value, unsigned int order); 

void map(Table& root, uint64_t virt_addr, uint64_t phy_addr, uint64_t bits, unsigned int level );
void unmap(Table& root);
uint64_t virt_to_phys(Table& root, unsigned int virt_addr);



}

#endif
