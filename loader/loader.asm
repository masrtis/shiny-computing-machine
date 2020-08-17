global loader
extern kmain
extern _init
extern _fini

MAGIC_NUMBER equ 0x1BADB002
ALIGN_MODULE_LOAD_TO_PAGE_BOUNDARY equ (1 << 0)
PROVIDE_MEMORY_MAP equ (1 << 1)
FLAGS equ (ALIGN_MODULE_LOAD_TO_PAGE_BOUNDARY | PROVIDE_MEMORY_MAP)
CHECKSUM equ -(MAGIC_NUMBER + FLAGS)

KB_SIZE equ 1024

KERNEL_STACK_SIZE equ 16 * KB_SIZE

section .multiboot
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

section .bss
align 16
kernel_stack: ; beginning of stack memory
    resb KERNEL_STACK_SIZE

section .text
align 4

loader:
    mov esp, kernel_stack + KERNEL_STACK_SIZE
    call _init
    call kmain
    call _fini
    cli
.loop:
    hlt
    jmp .loop

