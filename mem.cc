#include "mem.h"

using namespace Memory;

void Memory::init()
{
    
    int num_pages = HEAP_SIZE/PAGE_SIZE;
    Page* page = (Page*)HEAP_START;

    for (int i = 0; i<num_pages; i++) {
        (page+i)->clear();
    }

    ALLOC_START = HEAP_START + num_pages * sizeof(Page);

}


bool Page::is_free(){
    return !this->is_taken();
}
bool Page::is_taken(){
    return this->flags & PageInfo::TAKEN != 0;
}

void Page::clear(){
    this->flags = PageInfo::EMPTY;
}

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

void map(Table& root, unsigned int virt_addr, unsigned int phy_addr, uint64 bits, unsigned int level) 
{
    unsigned short vpn[] = {
        // VPN[0] = vaddr[20:12]
        (virt_addr >> 12) & 0x1ff,
        // VPN[1] = vaddr[29:21]
        (virt_addr >> 21) & 0x1ff,
        // VPN[2] = vaddr[38:30]
        (virt_addr >> 30) & 0x1ff,
    };
    
    unsigned short ppn[] = {
        // PPN[0] = paddr[20:12]
        (phy_addr >> 12) & 0x1ff,
        // PPN[1] = paddr[29:21]
        (phy_addr >> 21) & 0x1ff,
        // PPN[2] = paddr[55:30]
        (phy_addr >> 30) & 0x3ffffff,
    };



}