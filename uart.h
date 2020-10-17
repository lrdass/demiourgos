
typedef unsigned long long uint64;

class UART {
private:
    uint64 _base_addr = 0x100000000;
public:
    UART(uint64 base_addr):_base_addr(base_addr) {
        this->_init(_base_addr);
    }
private:
    void _init(uint64 base_addr)
    {
        char* ptr = reinterpret_cast<char*>(base_addr);

        // lcr register - word size
        char lcr = (1<<0) | (1<<1);
        *(ptr + 3) = lcr;
        
        // enable fifo and enable buffer interrupt
        *(ptr + 2) = (1 << 0);
        *(ptr + 1 ) = (0 << 0);

        unsigned int divisor = 592;
        char divisor_least = divisor & 0xff;
        char divisor_most = divisor >> 8;

        *(ptr + 3) = (lcr | 1 << 7);

        *(ptr + 0) = divisor_least;
        *(ptr + 1) = divisor_most;
        *(ptr + 3) = lcr;
    }
public:

    void write(char* str){
        int i=0;
        while(str[i] != '\0'){
            this->put(*(str+ i));
            i++;
        }
    }

    char get() {
        char* ptr = reinterpret_cast<char*>(this->_base_addr);
        if(*(ptr+5) & 1 == 0){
            return 0;
        }else{
            return *ptr;
        }
    }

    void put(char character)
    {
        char* ptr = reinterpret_cast<char*>(this->_base_addr);
        *ptr = character;
    }


};

