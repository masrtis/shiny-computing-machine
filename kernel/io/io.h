#ifndef INCLUDED_IO_H_
#define INCLUDED_IO_H_

/** outb: sends data to provided I/O port. Defined as assembly in io.asm
 * 
 * @param port The I/O port address to send data to
 * @param data Data to send to port
 */
void outb(unsigned short port, unsigned char data);

#endif // INCLUDED_IO_H_
