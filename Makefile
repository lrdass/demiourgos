compile:
	riscv64-unknown-elf-c++ -g -ffreestanding -O0 -Wl,--gc-sections \
    -nostartfiles -nostdlib -nodefaultlibs -Wl,-T,virt.lds\
    boot.S trap.S  main.cc
debug:
	qemu-system-riscv64 -machine virt -m 128M -gdb tcp::1234 -kernel a.out -S -bios none & \
	xterm -e riscv64-unknown-elf-gdb  \
	-ex "target remote:1234" -ex "set confirm off" \
	-ex "add-symbol-file ./a.out 0x80000000"
run:
	qemu-system-riscv64 -machine virt -m 128M -kernel a.out -bios none
