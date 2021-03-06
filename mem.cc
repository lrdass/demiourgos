#include "mem.h"

using namespace Memory;


//alinha o valor em relacao a ordem (4096)
uint64_t Memory::align_val(unsigned int value, unsigned int order)
{
	uint64_t mask = -1 << order;
	uint64_t operation = (1 << order) - 1;	
	return (value + operation) & mask;
}

// descritores de pagina
// seta todos os descritores de pagina, e seta o proximo endereco depois do endereco
// do ultimo descritor de pagina
void Memory::init()
{
    
    int num_pages = HEAP_SIZE/PAGE_SIZE;
    Page* page = (Page*)HEAP_START;

    for (int i = 0; i<num_pages; i++) {
        (page+i)->clear();
    }

    ALLOC_START = align_val(HEAP_START + num_pages * sizeof(Page), PAGE_ORDER);

}


bool Page::is_free(){
    return !this->is_taken();
}
bool Page::is_taken(){
    return (this->flags & PageInfo::TAKEN ) != 0;
}

void Page::clear(){
    this->flags = PageInfo::EMPTY;
}

// queremos paginas continuas
// not taken not taken not taken!!
char* Memory::alloc(unsigned int pages)
{
    int num_pages = HEAP_SIZE/PAGE_SIZE;
    Page* page = reinterpret_cast<Page*>(HEAP_START);

    for (int i = 0; i < num_pages-pages; i++){
        bool found = false;

        if((page+i)->is_free()){
           found = true;
           
           for(int j =0; j < i + pages; j++){
               if((page+j)->is_taken()){
                   found=false;
                   break;
               }
           }

        }

				// se paginas contiguas foram encontradas
				// retorna o endereco para alloc start 
				// i é a descriçao de pagina
        if(found){
            for (int k =0; k < i+pages-1; k++){
                (page+k)->flags |= (PageInfo::TAKEN);
            }

            (page+i+pages-1)->flags |=(PageInfo::TAKEN);
            (page+i+pages-1)->flags |=(PageInfo::LAST);

            return reinterpret_cast<char*>(ALLOC_START + PAGE_SIZE *i);
        }
    }
    return nullptr;
}

void map(Table& root, uint64_t virt_addr, uint64_t phy_addr, uint64_t bits, unsigned int level) 
{
	// should lock
    uint64_t vpn[] = {
        // VPN[0] = vaddr[20:12]
        (virt_addr >> 12) & 0x1ff,
        // VPN[1] = vaddr[29:21]
        (virt_addr >> 21) & 0x1ff,
        // VPN[2] = vaddr[38:30]
        (virt_addr >> 30) & 0x1ff,
    };
    
    uint64_t ppn[] = {
        // PPN[0] = paddr[20:12]
        (phy_addr >> 12) & 0x1ff,
        // PPN[1] = paddr[29:21]
        (phy_addr >> 21) & 0x1ff,
        // PPN[2] = paddr[55:30]
        (phy_addr >> 30) & 0x3ffffff,
    };

}

void unmap(Table& root)
{
    
}
