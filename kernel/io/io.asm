global outb

; outb - send a byte to an I/O port
; [esp + 8] data byte (1 byte)
; [esp + 4] I/O port (2 bytes)
; [esp + 0] return address

outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al ; send data to IO port
    ret