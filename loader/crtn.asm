section .init
    ; gcc appends crtend.o .init section here
    pop ebp
    ret

section .fini
    ; gcc appends crtend.o .fini section here
    pop ebp
    ret
