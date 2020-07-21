global outb

; outb - send a byte to an I/O port
; [esp + 8] data byte
; [esp + 4] I/O port
; [esp + 0] return address

outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al ; send data to IO port
    ret