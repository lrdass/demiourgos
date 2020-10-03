compile:
	riscv64-unknown-linux-gnu-c++ -g -ffreestanding -O0 -Wl,--gc-sections \
    -nostartfiles -nostdlib -nodefaultlibs -Wl,-T,riscv64-virt.ld \
    crt0.s add.cpp
debug:
	qemu-system-riscv64 -machine virt -m 128M -gdb tcp::1234 -kernel a.out
run:
	qemu-system-riscv64 -machine virt -m 128M -kernel a.out