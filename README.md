# RISC-V Timers Configuration and Interrupt Triggering

Project about timers configuration and interrupt triggering on RISC-V for the class of Operating Systems 2 at UFSC.

## Compiling

To compile, you'll need [qemu](https://www.qemu.org/), which can be downloaded following [these instructions](https://www.qemu.org/download/). Depending on your OS, you might need to install an additional package to have access to the `virt` machine of `qemu-system-riscv`.


You'll also need the RISC-V toolchain. You can either [compile it from source](https://github.com/riscv/riscv-gnu-toolchain) or [download a prebuilt version](https://www.sifive.com/software).
Once you have all of this setup, you can compile the project with `make compile`. This will generate `a.out`, the result of the compilation.

## Debugging

To debug the project, you first need to [compile the project](##Compiling).

Once the project is compiled, you can run `make debug` to start the project in debug mode, which will need `xterm` installed on your machine. This will start `qemu` and connect it to `xterm` running `gdb`, and from there, you can use `gdb` as usual.

## Running

To run the project, you first need to [compile the project](##Compiling).

Once the project is compiled, you can run `make run` to start the project in run mode, although this is not really useful, since the project has no printing capability, and won't show anything on the screen.

## Authors

Lucas Rodrigo da Silva Suppes - (16105153)

Henrique da Cunha Buss - (18102714)

Pablo Strapasson - (16100740)


## References
[RISC-V from scratch](https://twilco.github.io/riscv-from-scratch/2019/03/10/riscv-from-scratch-1.html)

[CSRs](https://book.rvemu.app/control-and-status-registers)

[RISC-V guia prático](http://riscvbook.com/portuguese/)

[RISC-V Examples](https://github.com/michaeljclark/riscv-probe)
