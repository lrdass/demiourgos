compile:
	riscv64-unknown-linux-gnu-g++ -g -ffreestanding -O0 -mcmodel=medany  -Wl,--gc-sections \
    -nostartfiles -nostdlib -nodefaultlibs -Wl,-T,virt.lds\
    boot.S trap.S mem.S main.cc uart.h 
debug:
	qemu-system-riscv64 -machine  virt -m 128M -serial mon:stdio -serial null  -nographic -gdb tcp::1234 -kernel a.out -S & \
	xterm -e riscv64-unknown-linux-gnu-gdb  \
	-ex "target remote:1234" -ex "set confirm off" \
	-ex "add-symbol-file ./a.out 0x80000000"
run:
	qemu-system-riscv64 -machine virt -m 128M -serial mon:stdio -serial null  -nographic -kernel a.out -bios none
