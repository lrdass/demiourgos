compile:
	riscv64-unknown-elf-g++ -g -ffreestanding -O0 -mcmodel=medany -o kernel -Wl,--gc-sections \
    -nostartfiles -nostdlib -nodefaultlibs -Wl,-T,virt.lds\
    boot.S trap.S mem.S main.cc uart.h mem.cc
debug:
	qemu-system-riscv64 -machine  virt -m 128M -serial mon:stdio -serial null  -nographic -gdb tcp::1234 -kernel kernel -S & \
	xterm -e riscv64-unknown-elf-gdb --tui \
	-ex "target remote:1234" -ex "set confirm off" \
	-ex "add-symbol-file ./kernel 0x80000000"
run:
	qemu-system-riscv64 -machine virt -m 128M -serial mon:stdio -serial null  -nographic -kernel kernel -bios none
