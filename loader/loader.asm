global loader
extern kmain
extern _init
extern _fini

MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x0
CHECKSUM equ -MAGIC_NUMBER

KERNEL_STACK_SIZE equ 4096

section .bss
align 4
kernel_stack: ; beginning of stack memory
    resb KERNEL_STACK_SIZE

section .text
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

loader:
    mov esp, kernel_stack + KERNEL_STACK_SIZE
    call _init
    call kmain
    call _fini
    cli
.loop:
    hlt
    jmp .loop

