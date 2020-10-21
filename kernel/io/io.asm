global outb
global inb

; outb - send a byte to an I/O port
; inputs:
; [esp + 8] data byte (1 byte)
; [esp + 4] I/O port (2 bytes)
; [esp + 0] return address
; modifies:
; al (byte to write)
; dx (port to write to)

outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al ; send data to IO port
    ret

; inb - reads a byte to an I/O port
; inputs:
; [esp + 4] I/O port (2 bytes)
; [esp + 0] return address
; modifies:
; dx (port to read from)
; al (return value)

inb:
    mov dx, [esp + 4]
    in al, dx ; read one byte from IO port in low byte of eax
    ret
