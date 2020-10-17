#ifndef MEM_H
#define MEM_H
#include "uart.h"

#define PAGE_SIZE 4096

namespace Memory{

static unsigned int ALLOC_START;

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