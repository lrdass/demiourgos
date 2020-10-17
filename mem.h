#ifndef MEM_H
#define MEM_H
#include "uart.h"

static unsigned int ALLOC_START;
static unsigned short PAGE_SIZE = 4096;

extern "C" unsigned int HEAP_SIZE ;
extern "C" unsigned int  TEXT_END;
extern "C" unsigned int DATA_START;
extern "C" unsigned int DATA_END;
extern "C" unsigned int RODATA_START;
extern "C" unsigned int RODATA_END;
extern "C" unsigned int BSS_START;
extern "C" unsigned int BSS_END;
extern "C" unsigned int KERNEL_STACK_START;
extern "C" unsigned int KERNEL_STACK_END;
extern "C" unsigned int HEAP_START;
extern "C" unsigned int HEAP_SIZE;

namespace Memory{


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
   
}

#endif