section .init
global _init

_init:
    push ebp
    mov ebp, esp
    ; crtbegin.o .init section appended here by gcc

section .fini
global _fini

_fini:
    push ebp
    mov ebp, esp
    ; crtbegin.o .fini section appended here by gcc
